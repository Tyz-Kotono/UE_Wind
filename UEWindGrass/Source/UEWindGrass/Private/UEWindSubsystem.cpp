// Fill out your copyright notice in the Description page of Project Settings.


#include "UEWindSubsystem.h"

void UUEWindSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	SceneView = FSceneViewExtensions::NewExtension<FWindSceneView>();
}

void UUEWindSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UUEWindSubsystem::SetGrassContext(UUEWindGrassData* Data)
{
	if (SceneView)
	{
		SceneView->SetGrassData(GetWorld(), Data);
	}
}
