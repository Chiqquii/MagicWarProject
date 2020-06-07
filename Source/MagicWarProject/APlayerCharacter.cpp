// Fill out your copyright notice in the Description page of Project Settings.


#include "APlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

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

	MaxHealth = 100;

	health = MaxHealth;

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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAPlayerCharacter::Shoot);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AAPlayerCharacter::CameraRotation);

}

void AAPlayerCharacter::Shoot()
{
	FCollisionQueryParams* QueryParams = new FCollisionQueryParams();
	QueryParams->AddIgnoredActor(GetOwner());
	QueryParams->AddIgnoredActor(this);
	QueryParams->bTraceComplex = true;//Lo vamos a usar para saber donde le pegamos y poder hacer lo de los puntos;
	FHitResult hit;

	if (GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), GetActorForwardVector() * 10000, ECC_Visibility))
	{
		health -= 10;
	}


	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorForwardVector() * 10000, FColor::Green, 1.0f, 0, 1.0f);
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

