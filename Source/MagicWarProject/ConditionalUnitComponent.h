// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Unit.h"
#include "APlayerCharacter.h"
#include "EnemyCharacter.h"
#include "ConditionalUnitComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICWARPROJECT_API UConditionalUnitComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UConditionalUnitComponent();

	UFUNCTION(NetMulticast, Reliable)
		void CallWinGameNetMulticastRPC(int MaxPoints, AAPlayerCharacter* CharacterParam);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void CallKillUnit(AUnit* UnitDeath);
};
