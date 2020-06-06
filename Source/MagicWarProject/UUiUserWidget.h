// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UUiUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAGICWARPROJECT_API UUUiUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* ProgessBar_Health;
	
};
