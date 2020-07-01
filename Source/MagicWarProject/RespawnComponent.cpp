// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnComponent.h"
#include "TimerManager.h"
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
}


void URespawnComponent::RespawnServerRPC_Implementation(AUnit* UnitParam)
{
	if (UnitParam->Respawn)
		UnitParam->Respawn->CounterRespawn++;
}

void URespawnComponent::RespawnNetMulticastRPC_Implementation(AUnit* UnitParam)
{
	if (UnitParam->Damageable) 
		UnitParam->Damageable->ResetLife();

	UnitParam->ViewRespawn();
}

void URespawnComponent::CheckRespawn()
{
	if (CounterRespawn >= MaxRespawn) 
		return;

	CounterRespawn++;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &URespawnComponent::FinishRespawn, TimeWaitRespawn, false);
	ChangeUI(true);
// 	if (RespawnUI) 
// 	{
// 		FString fstringVar = Unit->GetName();
// 		UE_LOG(LogTemp, Warning, TEXT("000 ACTIVE COUNTER UI, %s"), *fstringVar);
// 		RespawnUI->ActiveCounter(TimeWaitRespawn);
// 	}
}

void URespawnComponent::FinishRespawn()
{
	ChangeUI(false);
	RespawnNetMulticastRPC(Unit);
}

void URespawnComponent::ChangeUI(bool ActiveUIParam)
{
	if (RespawnUI) {
		FString fstringVar = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("000 COUNTER UI, %s"), *fstringVar);

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
	
}


// Called every frame
void URespawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

