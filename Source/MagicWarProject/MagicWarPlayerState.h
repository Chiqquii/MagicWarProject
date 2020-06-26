// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MagicWarPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWARPROJECT_API AMagicWarPlayerState : public APlayerState
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintCallable)
		void AddScore(float ScoreDelta);
};
