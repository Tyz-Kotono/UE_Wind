// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UEWindGrassData.generated.h"

/**
 * 
 */
UCLASS()
class UEWINDGRASS_API UUEWindGrassData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float MinPoint;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float GrassCurve;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float CenterWidth;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	float ButtonWidth;
	UPROPERTY(BlueprintReadWrite, editAnywhere)
	TObjectPtr<UTextureRenderTarget2D> PositionRT;
};
