// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWarGameState.h"
#include "Net/UnrealNetwork.h"


void AMagicWarGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMagicWarGameState, Time);

}

void AMagicWarGameState::CounterTime(float DeltaTime)
{
	Time += DeltaTime;
}