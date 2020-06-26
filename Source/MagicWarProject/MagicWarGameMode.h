// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RespawnComponent.h"
#include "MagicWarGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWARPROJECT_API AMagicWarGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(Replicated, BlueprintReadWrite)
		float Time;
	
public:

// 	UFUNCTION(Client, Reliable)
// 	void ClientTimer();
// 
// 	UFUNCTION(Server, Reliable)
// 	void ServerTimer();
// 
// 	UFUNCTION(NetMulticast, Reliable)
// 	void NetMulticastTimer();

	UFUNCTION(BlueprintCallable)
	void CounterTime(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	bool Respawn(class URespawnComponent* RespawnComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeRespawn;

};
