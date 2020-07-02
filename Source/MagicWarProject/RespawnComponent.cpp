// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnComponent.h"
#include "TimerManager.h"
#include "RespawnUI.h"
#include "MagicWarGameMode.h"
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

	if(UnitParam->Respawn && UnitParam->Respawn->RespawnUI)
		UnitParam->Respawn->RespawnUI->FinishCounter();
}

void URespawnComponent::ActiveRespawnNetMulticastRPC_Implementation(AUnit* UnitParam)
{

	if (UnitParam->Respawn && UnitParam->Respawn->RespawnUI)
		UnitParam->Respawn->RespawnUI->ActiveCounter(UnitParam->Respawn->TimeWaitRespawn);
}

void URespawnComponent::CheckRespawn()
{
	if (CounterRespawn >= MaxRespawn)
	{
		DeathUnitServerRPC(Unit);
		return;
	}

	CounterRespawn++;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &URespawnComponent::FinishRespawn, TimeWaitRespawn, false);
	ActiveRespawnNetMulticastRPC(Unit);
	if (RespawnUI)
		RespawnUI->RemainingComebacks(MaxRespawn - CounterRespawn);
}

void URespawnComponent::DeathUnitServerRPC_Implementation(AUnit* UnitParam)
{
	AMagicWarGameMode* GM = Cast<AMagicWarGameMode>(GetWorld()->GetAuthGameMode());

	if (GM)
		GM->CallKillUnit(UnitParam);
}



void URespawnComponent::FinishRespawn()
{
	RespawnNetMulticastRPC(Unit);
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

	if (RespawnUI)
		RespawnUI->RemainingComebacks(MaxRespawn - CounterRespawn);
}


// Called every frame
void URespawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

