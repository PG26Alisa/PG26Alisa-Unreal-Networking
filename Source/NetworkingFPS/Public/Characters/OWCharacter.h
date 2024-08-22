// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OWCharacter.generated.h"

class UHealthComponent;
class ABullet;

UCLASS()
class NETWORKINGFPS_API AOWCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOWCharacter();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shooting")
	TSubclassOf<ABullet> BulletClassToSpawn;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Shooting")
	FName SocketToSpawnBulletFrom;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shooting", meta = (MakeEditWidget))
	FVector BulletSpawnPoint;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Shoot();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SprintStart();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SprintEnd();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sprinting")
	float RunSpeed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sprinting")
	float SprintSpeed;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Dashing();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dashing")
	float DashDistance;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void PlayVFX();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void PlayVFX_Multicast();


	UFUNCTION(BlueprintImplementableEvent)
	void OnVFXPlayed();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health Component")
	TObjectPtr<UHealthComponent> HealthComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
