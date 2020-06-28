// Fill out your copyright notice in the Description page of Project Settings.


#include "PointsComponent.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UPointsComponent::UPointsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPointsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UPointsComponent::OnRep_Points()
{
	PointsBPEvent(Points);
}

// Called every frame
void UPointsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPointsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPointsComponent, Points);

}

void UPointsComponent::AddPoints(int Point)
{
	Points += Point;
}

