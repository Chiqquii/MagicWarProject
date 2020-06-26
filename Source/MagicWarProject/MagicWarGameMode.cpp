// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWarGameMode.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"

void AMagicWarGameMode::CounterTime(float DeltaTime)
{
	Time += DeltaTime;
}

bool AMagicWarGameMode::Respawn(class URespawnComponent* RespawnComponent)
{
	if (RespawnComponent->CounterRespawn >= RespawnComponent->MaxRespawn)
	{
		return false;
	}

	RespawnComponent->CounterRespawn++;
	RespawnComponent->RespawnUI->ActiveCounter();

	auto Counter = 0;

	while (Counter < TimeRespawn)
	{
		Counter += GetWorld()->DeltaTimeSeconds;

		RespawnComponent->RespawnUI->CounterRespawn(Counter);
	}

	RespawnComponent->RespawnUI->FinishCounter();
	return true;
}

