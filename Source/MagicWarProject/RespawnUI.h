// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UUiUserWidget.h"
#include "RespawnUI.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWARPROJECT_API URespawnUI : public UUUiUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Settings")
		void ActiveCounter();

	UFUNCTION(BlueprintImplementableEvent, Category = "Settings")
		void CounterRespawn(float Time);

	UFUNCTION(BlueprintImplementableEvent, Category = "Settings")
		void FinishCounter();
};
