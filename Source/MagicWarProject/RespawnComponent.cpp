// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnComponent.h"
#include "TimerManager.h"
#include "RespawnUI.h"
// Sets default values for this component's properties
URespawnComponent::URespawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void URespawnComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URespawnComponent, CounterRespawn);
	DOREPLIFETIME(URespawnComponent, MaxRespawn);
	DOREPLIFETIME(URespawnComponent, RespawnUI);
}


void URespawnComponent::RespawnNetMulticastRPC_Implementation(AUnit* UnitParam)
{
	if (UnitParam->Damageable) 
		UnitParam->Damageable->ResetLife();

	UnitParam->ViewRespawn();

	if (UnitParam->Role == ROLE_Authority) {

		UE_LOG(LogTemp, Warning, TEXT("000 COUNTER UI SERVER"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("000 COUNTER UI CLIENT"));

	if(UnitParam->Respawn && UnitParam->Respawn->RespawnUI)
		UnitParam->Respawn->RespawnUI->FinishCounter();
}

void URespawnComponent::ActiveRespawnNetMulticastRPC_Implementation(AUnit* UnitParam)
{
	if (UnitParam->Role == ROLE_Authority) {

		UE_LOG(LogTemp, Warning, TEXT("000 COUNTER UI SERVER"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("000 COUNTER UI CLIENT"));

	if (UnitParam->Respawn && UnitParam->Respawn->RespawnUI)
		UnitParam->Respawn->RespawnUI->ActiveCounter(UnitParam->Respawn->TimeWaitRespawn);
}

void URespawnComponent::CheckRespawn()
{
	if (CounterRespawn >= MaxRespawn) 
		return;

	CounterRespawn++;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &URespawnComponent::FinishRespawn, TimeWaitRespawn, false);
	ActiveRespawnNetMulticastRPC(Unit);
// 	if (RespawnUI) 
// 	{
// 		FString fstringVar = Unit->GetName();
// 		UE_LOG(LogTemp, Warning, TEXT("000 ACTIVE COUNTER UI, %s"), *fstringVar);
// 		RespawnUI->ActiveCounter(TimeWaitRespawn);
// 	}
}

void URespawnComponent::FinishRespawn()
{
	//ChangeUI(false);
	RespawnNetMulticastRPC(Unit);
}

void URespawnComponent::ChangeUI(bool ActiveUIParam)
{
	//URespawnUI* reUI = Cast<URespawnUI>(GetOwner()->GetComponentByClass(URespawnUI::StaticClass()));

	if (RespawnUI) {
// 		FString fstringVar = GetOwner()->Role.GetValue();
// 		UE_LOG(LogTemp, Warning, TEXT("000 COUNTER UI, %s"), *fstringVar);

		if (GetOwner()->Role == ROLE_Authority) {

			UE_LOG(LogTemp, Warning, TEXT("000 COUNTER UI SERVER"));
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("000 COUNTER UI CLIENT"));

		if (ActiveUIParam)
			RespawnUI->ActiveCounter(TimeWaitRespawn);
		else
			RespawnUI->FinishCounter();
	}
}


// Called when the game starts
void URespawnComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Owner = Cast<AUnit>(GetOwner());
	if (Owner) {
		Owner->Respawn = this;
		Unit = Owner;
	}
	ChangeUI(true);
}


// Called every frame
void URespawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

