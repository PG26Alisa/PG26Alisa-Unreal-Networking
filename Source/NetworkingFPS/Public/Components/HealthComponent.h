// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthEventSignature, UHealthComponent*, HealthComponent, float, OldHealth, float, NewHealth);

UCLASS( ClassGroup=(StatComponents), Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent) )
class NETWORKINGFPS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_Health", Category = "Health Component")
	float Health;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Health Component")
	float OldHealth;

	UPROPERTY(BlueprintReadOnly, Replicated, EditAnywhere, Category = "Health Component")
	float MaxHealth;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float NormalizedHealth() const;

	// Required for Networked Properties
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintNativeEvent)
	void OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnRep_Health();

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, Category = "Health Component")
	FHealthEventSignature OnHealthUpdated;	
		
};
