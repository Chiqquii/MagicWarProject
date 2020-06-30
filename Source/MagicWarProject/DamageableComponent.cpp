// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageableComponent.h"
#include "MagicWarGameMode.h"
#include "Engine/Engine.h"
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
	Health -= damage;

	if (Health <= 0) 
	{
		Health = 0;

		Respawn();
	}
}

void UDamageableComponent::Kill()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("KILL"));

	AMagicWarGameMode* GM = Cast<AMagicWarGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->OnActorKilled.Broadcast();
	}

	GetOwner()->Destroy(true);
}

void UDamageableComponent::Respawn()
{
	if (RespawnComponent == nullptr || RespawnComponent->CounterRespawn >= RespawnComponent->MaxRespawn)
	{
		Kill();
		return;
	}

// 	RespawnComponent->CounterRespawn++;
// 	RespawnComponent->RespawnUI->ActiveCounter();
// 
// 	auto Counter = 0;
// 
// 	while (RespawnComponent->CounterRespawn < RespawnComponent->MaxRespawn)
// 	{
// 		Counter += GetWorld()->DeltaTimeSeconds;
// 
// 		RespawnComponent->RespawnUI->CounterRespawn(Counter);
// 	}
// 
// 	RespawnComponent->RespawnUI->FinishCounter();

	ResetLife();
}

void UDamageableComponent::ResetLife()
{
	Health = MaxHealth;
}

