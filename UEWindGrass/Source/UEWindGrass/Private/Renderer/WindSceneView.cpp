// Fill out your copyright notice in the Description page of Project Settings.


#include "Renderer/WindSceneView.h"

#include "Shader/WindGrassInterface.h"

FWindSceneView::FWindSceneView(const FAutoRegister& AutoRegister) : FSceneViewExtensionBase(AutoRegister)
{
}

FWindSceneView::~FWindSceneView()
{
}

void FWindSceneView::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
	FSceneViewExtensionBase::SetupViewFamily(InViewFamily);
}

void FWindSceneView::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
	FSceneViewExtensionBase::SetupView(InViewFamily, InView);
}

void FWindSceneView::BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
	FSceneViewExtensionBase::BeginRenderViewFamily(InViewFamily);
}

void FWindSceneView::PreInitViews_RenderThread(FRDGBuilder& GraphBuilder)
{
	FSceneViewExtensionBase::PreInitViews_RenderThread(GraphBuilder);
	if (GrassSpec)
	{
		UWindGrassInterface::ComputerProceduralGrass_RenderThread(GraphBuilder, GrassSpec);
	}
}

void FWindSceneView::SetGrassData(UWorld* InWorld, UUEWindGrassData* InGrassSpec)
{
	GrassSpec = InGrassSpec;
	World = InWorld;
}
