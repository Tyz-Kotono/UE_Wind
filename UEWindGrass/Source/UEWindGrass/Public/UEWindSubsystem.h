// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Renderer/WindSceneView.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UEWindSubsystem.generated.h"

class UUEWindGrassData;
/**
 * 
 */
UCLASS()
class UEWINDGRASS_API UUEWindSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
private:
	TSharedPtr<FWindSceneView, ESPMode::ThreadSafe> SceneView;
	UFUNCTION(BlueprintCallable)
	void SetGrassContext(UUEWindGrassData* Data);
};
