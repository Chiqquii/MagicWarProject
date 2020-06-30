// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnComponent.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
// Sets default values for this component's properties
URespawnComponent::URespawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// void URespawnComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
// 
// 	DOREPLIFETIME(URespawnComponent, CounterRespawn);
// 	DOREPLIFETIME(URespawnComponent, MaxRespawn);
// }


void URespawnComponent::RespawnServerRPC_Implementation(AUnit* UnitParam)
{
	UE_LOG(LogTemp, Warning, TEXT("000 START RESPAWN"));

	if (UnitParam->Respawn)
		UnitParam->Respawn->CounterRespawn++;

	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	TimerDel.BindUFunction(this, FName("Respawn"), UnitParam);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, TimeWaitRespawn, false);
}

void URespawnComponent::RespawnNetMulticastRPC_Implementation(AUnit* UnitParam)
{
	UnitParam->ViewRespawn();
}

void URespawnComponent::CheckRespawn()
{
	UE_LOG(LogTemp, Warning, TEXT("000 Check respawn"));

	if (CounterRespawn >= MaxRespawn) return;

	if(Unit)
		RespawnServerRPC(Unit);
}

void URespawnComponent::Respawn(AUnit* UnitParam)
{
	UE_LOG(LogTemp, Warning, TEXT("000 RESET LIFEEEE"));
	if (UnitParam->Damageable)
		UnitParam->Damageable->ResetLife();

	RespawnNetMulticastRPC(UnitParam);
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

