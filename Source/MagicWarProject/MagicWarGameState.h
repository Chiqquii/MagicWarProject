// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MagicWarGameState.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWARPROJECT_API AMagicWarGameState : public AGameStateBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
		float Time;

public:

	UFUNCTION(BlueprintCallable)
		void CounterTime(float DeltaTime);
};
