// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MagicWarGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWARPROJECT_API AMagicWarGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void CounterTime(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Time;

};
