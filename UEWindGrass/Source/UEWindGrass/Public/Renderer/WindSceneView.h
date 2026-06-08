// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneViewExtension.h"


class UUEWindGrassData;

class UEWINDGRASS_API FWindSceneView : public FSceneViewExtensionBase
{
public:
	FWindSceneView(const FAutoRegister& AutoRegister);
	virtual ~FWindSceneView() override;
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void PreInitViews_RenderThread(FRDGBuilder& GraphBuilder);
	
	void SetGrassData(UWorld* InWorld, UUEWindGrassData* InGrassSpec);
private:
	UPROPERTY(BlueprintAssignable)
	TWeakObjectPtr<UWorld> World;
	UPROPERTY(BlueprintAssignable)
	TObjectPtr<UUEWindGrassData> GrassSpec;
};
