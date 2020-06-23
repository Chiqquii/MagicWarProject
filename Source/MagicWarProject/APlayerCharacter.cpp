// Fill out your copyright notice in the Description page of Project Settings.


#include "APlayerCharacter.h"

// Sets default values
AAPlayerCharacter::AAPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	health = MaxHealth;

	if (skins.Num() > 0) 
	{
		auto randomSkin = FMath::RandRange(0, skins.Num());
		GetMesh()->SetSkeletalMesh(skins[randomSkin]);
	}
}

// Called every frame
void AAPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAPlayerCharacter::CallShoot);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AAPlayerCharacter::CameraRotation);

}

void AAPlayerCharacter::CallShoot()
{
	if (Role == ENetRole::ROLE_Authority)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Server!"));
		ServerShoot();
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Client!"));
		ClientShoot();
	}
}

void AAPlayerCharacter::Shoot()
{
	if (CurrentWeapon != NULL)
	{
		CurrentWeapon->Fire(this);
	}
}

void AAPlayerCharacter::TakeDamage()
{

}

void AAPlayerCharacter::MoveForward(float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis);
}

void AAPlayerCharacter::MoveRight(float Axis)
{
	AddMovementInput(GetActorRightVector(), Axis);
}

void AAPlayerCharacter::CameraRotation(float Axis)
{
	AddControllerYawInput(Axis);
}

void AAPlayerCharacter::ClientShoot_Implementation()
{
	//Shoot();

	ServerShoot();
}

void AAPlayerCharacter::ServerShoot_Implementation()
{
	Shoot();

	NetMulticastShoot();
}

void AAPlayerCharacter::NetMulticastShoot_Implementation()
{
	if (Role == ENetRole::ROLE_Authority)
		return;

	Shoot();
}
