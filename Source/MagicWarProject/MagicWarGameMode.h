// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RespawnComponent.h"
#include "MagicWarGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActorKilled);

UCLASS()
class MAGICWARPROJECT_API AMagicWarGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Time;
	
public:

	UPROPERTY(BlueprintAssignable)
	FOnActorKilled OnActorKilled;
};
