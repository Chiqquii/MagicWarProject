// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileStorm.h"

void AProjectileStorm::IntroStorm(UPrimitiveComponent* OverlappedComp, AActor* OtherActor)
{
	if (Cast<AUnit>(OtherActor) && Cast<AUnit>(OtherActor)->DeathUnit)
		return;

	auto damageable = OtherActor->FindComponentByClass<UDamageableComponent>();

	if (Character && Character->Points)
	{
		auto points = OtherActor->FindComponentByClass<UPointsComponent>();

		if (points)
		{
			Character->Points->AddPoints(FMath::FloorToInt(points->PointsToGive * MultiplyPoints));
		}
	}

	if (damageable)
		damageable->Damage(Damage);
}