// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWarGameMode.h"
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"


void AMagicWarGameMode::CallKillUnit(AUnit* UnitDeath)
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

void AMagicWarGameMode::CheckGameOver()
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
			PD->GameOverNetMulticastRPC();
		}
	}		
}

void AMagicWarGameMode::CheckWin()
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
				FString NameCharacter = Character->GetName();
				UE_LOG(LogTemp, Warning, TEXT("000 WIN, %s"));
				Character->WinNetMulticastRPC(Record);
			}
		}

	}
}

