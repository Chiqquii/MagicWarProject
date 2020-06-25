// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UUiUserWidget.h"
#include "DamageableUI.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWARPROJECT_API UDamageableUI : public UUUiUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Settings")
		void ChangeHealth(float Health, float MaxHealth);
};
