// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OWCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Actors/Bullet.h"
#include "Components/HealthComponent.h"
#include "Engine.h"

// Sets default values
AOWCharacter::AOWCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

void AOWCharacter::SprintStart_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AOWCharacter::SprintEnd_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AOWCharacter::Shoot_Implementation()
{
	FActorSpawnParameters SpawnParamters;
	SpawnParamters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParamters.Owner = this;

	if (TObjectPtr<UWorld> World = GetWorld())
	{
		const FVector LoactionToSpawn = GetActorLocation() + BulletSpawnPoint;
		if (IsValid(BulletClassToSpawn))
		{
			World->SpawnActor<ABullet>(BulletClassToSpawn, LoactionToSpawn, GetActorRotation(), SpawnParamters);
		}
	}
}

void AOWCharacter::PlayVFX_Implementation()
{
	PlayVFX_Multicast();
}

void AOWCharacter::PlayVFX_Multicast_Implementation()
{
	OnVFXPlayed();
}

void AOWCharacter::Dashing_Implementation()
{
	const FVector ForwardDir = this->GetActorRotation().Vector();
	LaunchCharacter(ForwardDir * DashDistance, true, true);
}

// Called when the game starts or when spawned
void AOWCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOWCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

