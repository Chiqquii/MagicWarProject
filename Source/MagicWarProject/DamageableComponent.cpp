// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableComponent.h"
#include "MagicWarGameMode.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UDamageableComponent::UDamageableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UDamageableComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDamageableComponent, Health);
}


// Called when the game starts
void UDamageableComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Owner = Cast<AUnit>(GetOwner());
	if (Owner) {
		Owner->Damageable = this;
		Unit = Owner;
	}

	ResetLife();
}


// Called every frame
void UDamageableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageableComponent::Damage(float damage)
{
	if (Unit && Unit->DeathUnit) return;

	FString fstringVar = Unit->GetName();
	FString fstringOwner = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("000 UNIT DAMAGE, %s"), *fstringVar);
	UE_LOG(LogTemp, Warning, TEXT("000 OWNER DAMAGE, %s"), *fstringOwner);

	Health -= damage;

	if (Health <= 0) 
	{
		Health = 0;

		Kill();
	}
}

void UDamageableComponent::Kill()
{
	FString fstringVar = Unit->GetName();
	UE_LOG(LogTemp, Warning, TEXT("000 Text, %s"), *fstringVar);

	if (Unit) {
		Unit->DeathUnit = true;
		DeathServerRPC(Unit);
		DeathNetMulticastRPC(Unit);
	}

// 	AMagicWarGameMode* GM = Cast<AMagicWarGameMode>(GetWorld()->GetAuthGameMode());
// 	if (GM)
// 	{
// 		GM->OnActorKilled.Broadcast();
// 	}
// 
// 	GetOwner()->Destroy(true);
}

void UDamageableComponent::DeathServerRPC_Implementation(AUnit* UnitParam)
{
	UE_LOG(LogTemp, Warning, TEXT("000 KILL"));

	if (UnitParam->Respawn)
		UnitParam->Respawn->CheckRespawn();
}

void UDamageableComponent::DeathNetMulticastRPC_Implementation(AUnit* UnitParam)
{
// 	if (UnitParam->Role == ENetRole::ROLE_Authority)
// 		return;

	UnitParam->ViewDeath();
}


void UDamageableComponent::ResetLife()
{
	UE_LOG(LogTemp, Warning, TEXT("000 Reset"));
	Health = MaxHealth;

	if(Unit)
		Unit->DeathUnit = false;
}

