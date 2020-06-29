// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UUiUserWidget.h"
#include "DamageableComponent.h"
#include "DamageableUI.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWARPROJECT_API UDamageableUI : public UUUiUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UDamageableComponent* DamageableComponent;
};
