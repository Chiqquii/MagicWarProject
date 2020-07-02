// Fill out your copyright notice in the Description page of Project Settings.


#include "ConditionalUnitComponent.h"

// Sets default values for this component's properties
UConditionalUnitComponent::UConditionalUnitComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UConditionalUnitComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UConditionalUnitComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UConditionalUnitComponent::CallKillUnit(AUnit* UnitDeath)
{
	if (FinishGame) return;

	AAPlayerCharacter* Character = Cast<AAPlayerCharacter>(UnitDeath);

	if (Character)
	{
		PlayersDeath.AddUnique(Character);
		CheckGameOver();
	}
	else
	{
		AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(UnitDeath);

		if (Enemy)
		{
			EnemiesDeath.AddUnique(Enemy);
			CheckWin();
		}
	}
}

void UConditionalUnitComponent::CheckGameOver()
{
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAPlayerCharacter::StaticClass(), AllPlayers);

	if (PlayersDeath.Num() >= AllPlayers.Num())
	{
		FinishGame = true;

		for (AAPlayerCharacter* PD : PlayersDeath)
		{
			//FString NameCharacter = PD->GetName();
			UE_LOG(LogTemp, Warning, TEXT("000 GAME OVER, %s"));
			PD->ViewGameOver();
		}
	}
}

void UConditionalUnitComponent::CheckWin()
{
	TArray<AActor*> AllEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), AllEnemies);

	if (EnemiesDeath.Num() >= AllEnemies.Num())
	{
		FinishGame = true;

		TArray<AActor*> AllPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAPlayerCharacter::StaticClass(), AllPlayers);
		int Record = 0;

		for (AActor* Actor : AllPlayers)
		{
			auto Character = Cast<AAPlayerCharacter>(Actor);

			if (Character)
			{
				if (Character->Points && Record < Character->Points->TotalPoints())
					Record = Character->Points->TotalPoints();
			}
		}

		for (AActor* Actor : AllPlayers)
		{
			auto Character = Cast<AAPlayerCharacter>(Actor);

			if (Character)
			{
				//FString NameCharacter = Character->GetName();
				//UE_LOG(LogTemp, Warning, TEXT("000 WIN, %s"));
				CallWinGameNetMulticastRPC(Record, Character);
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("000 WINNNN"));
		//CallWinGameNetMulticastRPC(Record);
	}
}

void UConditionalUnitComponent::CallWinGameNetMulticastRPC_Implementation(int MaxPoints, AAPlayerCharacter* CharacterParam)
{
	FString fstringVar = CharacterParam->GetName();
	UE_LOG(LogTemp, Warning, TEXT("000 WIN, %s"), *fstringVar);
	CharacterParam->ViewWin(MaxPoints);
}

