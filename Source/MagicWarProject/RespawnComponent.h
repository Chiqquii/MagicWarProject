// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnUI.h"
#include "Unit.h"
#include "Net/UnrealNetwork.h"
#include "RespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICWARPROJECT_API URespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URespawnComponent();

	UFUNCTION(Server, Reliable)
	void RespawnServerRPC(AUnit* UnitParam);

	UFUNCTION(NetMulticast, Reliable)
	void RespawnNetMulticastRPC(AUnit* UnitParam);

	UFUNCTION()
	void CheckRespawn();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void FinishRespawn();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		class AUnit* Unit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		URespawnUI* RespawnUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float TimeWaitRespawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Settings")
	int CounterRespawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "Settings")
	int MaxRespawn;
};
