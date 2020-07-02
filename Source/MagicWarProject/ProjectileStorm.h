// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ProjectileStorm.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWARPROJECT_API AProjectileStorm : public AProjectile
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MultiplyPoints;

public:

	UFUNCTION(BlueprintCallable)
	void IntroStorm(UPrimitiveComponent* OverlappedComp, AActor* OtherActor);
};
