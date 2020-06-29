// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageableUI.h"
#include "RespawnComponent.h"
#include "DamageableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICWARPROJECT_API UDamageableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
		float Health;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class UDamageableUI* DamageableUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class URespawnComponent* RespawnComponent;

	UFUNCTION(BlueprintCallable)
	void Damage(float damage);

	UFUNCTION(BlueprintCallable)
	void Kill();

	UFUNCTION(BlueprintCallable)
	void Respawn();

	UFUNCTION(BlueprintCallable)
	void ResetLife();
};
