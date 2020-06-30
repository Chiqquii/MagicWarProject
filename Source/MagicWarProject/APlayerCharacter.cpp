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

// 	if (skins.Num() > 0) 
// 	{
// 		auto randomSkin = FMath::RandRange(0, skins.Num());
// 		GetMesh()->SetSkeletalMesh(skins[randomSkin]);
// 	}
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

	DECLARE_DELEGATE_OneParam(CallShoot, AAPlayerCharacter*);
	PlayerInputComponent->BindAction<CallShoot>("Fire", IE_Pressed, this, &AAPlayerCharacter::CallShoot, this);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AAPlayerCharacter::CameraRotation);

}

void AAPlayerCharacter::CallShoot(AAPlayerCharacter* Character)
{
	if (DeathUnit || !CurrentWeapon)
		return;

	ServerShoot(Character);
}

void AAPlayerCharacter::Shoot(AAPlayerCharacter* Character)
{
	Character->CurrentWeapon->Fire(Character);
	NetMulticastShoot();
}

void AAPlayerCharacter::MoveForward(float Axis)
{
	if (DeathUnit) return;

	AddMovementInput(GetActorForwardVector(), Axis);
}

void AAPlayerCharacter::MoveRight(float Axis)
{
	if (DeathUnit) return;

	AddMovementInput(GetActorRightVector(), Axis);
}

void AAPlayerCharacter::CameraRotation(float Axis)
{
	if (DeathUnit) return;

	AddControllerYawInput(Axis);
}

void AAPlayerCharacter::ServerShoot_Implementation(AAPlayerCharacter* Character)
{
	Shoot(Character);
}

void AAPlayerCharacter::NetMulticastShoot_Implementation()
{
	ViewAttack();
}
