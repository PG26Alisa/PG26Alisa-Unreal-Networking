// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassDefaults/OWPlayerState.h"

void AOWPlayerState::AddScore_Implementation(const float ScoreToAdd)
{
	SetScore(GetScore()+ScoreToAdd);
	//Score += ScoreToAdd;
	OnRep_Score();
}

void AOWPlayerState::OnRep_Score()
{
	Super::OnRep_Score();
	if(OnScoreUpdated.IsBound())
	{
		OnScoreUpdated.Broadcast(GetScore());
		//OnScoreUpdated.Broadcast(Score);
	}
}
