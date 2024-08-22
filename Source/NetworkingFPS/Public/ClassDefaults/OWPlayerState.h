// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OWPlayerState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreEventSignature, float, Score);

UCLASS()
class NETWORKINGFPS_API AOWPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void AddScore(const float ScoreToAdd);

	virtual void OnRep_Score() override;

	UPROPERTY(BlueprintReadOnly, BlueprintAssignable)
	FScoreEventSignature OnScoreUpdated;
	
};
