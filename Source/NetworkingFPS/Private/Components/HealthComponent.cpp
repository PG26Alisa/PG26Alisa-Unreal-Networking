// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100.0f;

	SetIsReplicatedByDefault(true);

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (TObjectPtr<AActor> OwningActor = GetOwner())
	{
		if (OwningActor->HasAuthority())
		{
			OldHealth = MaxHealth;
			Health = MaxHealth;

			OnRep_Health();

			OwningActor->OnTakeAnyDamage.AddUniqueDynamic(this, &ThisClass::OnDamageTaken);
		}
	}
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHealthComponent::NormalizedHealth() const
{
	return UKismetMathLibrary::NormalizeToRange(Health, 0.0f, MaxHealth);
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
	DOREPLIFETIME(UHealthComponent, OldHealth);
	DOREPLIFETIME(UHealthComponent, MaxHealth);
}

void UHealthComponent::OnRep_Health()
{
	if (OnHealthUpdated.IsBound())
	{
		OnHealthUpdated.Broadcast(this, OldHealth, Health);
	}
}

void UHealthComponent::OnDamageTaken_Implementation(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                                    AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamagedActor == GetOwner())
	{
		OldHealth = Health;
		Health = Health - Damage;
		OnRep_Health();
	}
}

