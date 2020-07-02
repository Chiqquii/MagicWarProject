// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PointsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICWARPROJECT_API UPointsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPointsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Points)
	int Points;

	UFUNCTION()
	void OnRep_Points();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	bool IgnoreAddPoints;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
	int PointsToGive;

	UFUNCTION(BlueprintCallable)
	int TotalPoints();

	UFUNCTION(BlueprintCallable)
	void AddPoints(int Point);

	UFUNCTION(BlueprintImplementableEvent)
	void PointsBPEvent(int Point);
};
