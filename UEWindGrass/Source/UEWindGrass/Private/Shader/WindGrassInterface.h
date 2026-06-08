// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RenderGraphBuilder.h"


class FGlobalShaderMap;
class UUEWindGrassData;

class UEWINDGRASS_API UWindGrassInterface
{
public:
	static void ComputerProceduralGrass_RenderThread(
		FRDGBuilder& GraphBuilder,
		UUEWindGrassData* InGrassSpec);
	
	static void Grass_RenderThread(
		FRDGBuilder& GraphBuilder,
		const FGlobalShaderMap* ShaderMap,
		uint32 Resolution,
		const UUEWindGrassData* GrassSpec,
		FRDGTextureRef OutputPositionTexture);
};
