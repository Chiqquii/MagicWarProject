// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWarGameMode.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"

void AMagicWarGameMode::CounterTime(float DeltaTime)
{
	Time += DeltaTime;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT(" %s"), Time);
	UE_LOG(LogTemp, Warning, TEXT("Text, %d"), Time);
}
