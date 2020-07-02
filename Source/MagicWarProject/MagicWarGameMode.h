// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Unit.h"
#include "APlayerCharacter.h"
#include "EnemyCharacter.h"
#include "Net/UnrealNetwork.h"
#include "MagicWarGameMode.generated.h"

UCLASS()
class MAGICWARPROJECT_API AMagicWarGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Time;

	UPROPERTY()
		bool FinishGame;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array")
	TArray<AAPlayerCharacter*> PlayersDeath;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Array")
	TArray<AEnemyCharacter*> EnemiesDeath;

	UFUNCTION()
		void CheckGameOver();

	UFUNCTION()
		void CheckWin();
	
public:

	UFUNCTION()
		void CallKillUnit(AUnit* UnitDeath);
};
