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

	UFUNCTION(BlueprintImplementableEvent)
		void ActiveCounter(float MaxTimeParam);

	UFUNCTION(BlueprintImplementableEvent)
		void FinishCounter();

	UFUNCTION(BlueprintImplementableEvent)
		void RemainingComebacks(int ComebacksParam);
};
