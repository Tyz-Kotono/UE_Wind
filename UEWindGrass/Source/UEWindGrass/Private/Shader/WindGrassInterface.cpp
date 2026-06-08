// Fill out your copyright notice in the Description page of Project Settings.


#include "WindGrassInterface.h"

#include "GlobalShader.h"
#include "RenderGraphUtils.h"
#include "TextureResource.h"
#include "Data/UEWindGrassData.h"

class FWindGrassCS : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FWindGrassCS, Global, UEWINDGRASS_API);

	SHADER_USE_PARAMETER_STRUCT(FWindGrassCS, FGlobalShader)
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters,)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, GrassPositionTexture2D)
	END_SHADER_PARAMETER_STRUCT()

public:
	static constexpr uint32 NumThreadsX = 16;
	static constexpr uint32 NumThreadsY = 16;

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,
	                                         FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		OutEnvironment.SetDefine("NUM_THREADS_X", NumThreadsX);
		OutEnvironment.SetDefine("NUM_THREADS_Y", NumThreadsY);
	}
};

IMPLEMENT_GLOBAL_SHADER(FWindGrassCS, "/UEWindGrass/ProceduralGrass.usf",
                        "ProceduralGrassMain",
                        SF_Compute);


void UWindGrassInterface::ComputerProceduralGrass_RenderThread(
	FRDGBuilder& GraphBuilder,
	UUEWindGrassData* GrassSpec)
{
	if (!GrassSpec->PositionRT)
	{
		return;
	}

	auto GrassPositionRT = GrassSpec->PositionRT.Get();
	FTextureRenderTargetResource* PositionRTResource = GrassPositionRT->GetRenderTargetResource();

	if (!PositionRTResource)
	{
		return;
	}
	// === 外部 RT ===
	FRDGTextureRef RDGPositionTexture = GraphBuilder.RegisterExternalTexture(
		CreateRenderTarget(PositionRTResource->GetRenderTargetTexture(), TEXT("GrassPositionRT"))
	);
	const int32 Resolution = GrassPositionRT->SizeX;
	if (Resolution <= 0 || GrassPositionRT->SizeY != Resolution|| GrassPositionRT->GetFormat() != PF_FloatRGBA)
	{
		return;
	}

	//TODO
	// === 输出 RT ===  Resolution
	FRDGTextureDesc OutputDesc = FRDGTextureDesc::Create2D(
		FIntPoint(Resolution, Resolution),
		PF_FloatRGBA,
		FClearValueBinding::Black,
		TexCreate_ShaderResource | TexCreate_UAV
	);

	FRDGTextureRef RDGOutputPosition = GraphBuilder.CreateTexture(OutputDesc, TEXT("GrassPositionOutput"));

	const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

	// === Compute Pass ===
	Grass_RenderThread(
		GraphBuilder,
		GlobalShaderMap,
		Resolution,
		GrassSpec,
		RDGOutputPosition
	);
	
	AddCopyTexturePass(GraphBuilder, RDGOutputPosition, RDGPositionTexture);
}

void UWindGrassInterface::Grass_RenderThread(FRDGBuilder& GraphBuilder, const FGlobalShaderMap* ShaderMap,
                                             uint32 Resolution, const UUEWindGrassData* GrassSpec,
                                             FRDGTextureRef OutputPositionTexture)
{
	RDG_EVENT_SCOPE(GraphBuilder, "UEWindGrass");
	TShaderMapRef<FWindGrassCS> ComputeShader(ShaderMap);
	FWindGrassCS::FParameters* Parameters =
		GraphBuilder.AllocParameters<FWindGrassCS::FParameters>();

	Parameters->GrassPositionTexture2D = GraphBuilder.CreateUAV(OutputPositionTexture);

	const FIntVector GroupCount(
		FMath::DivideAndRoundUp(Resolution, FWindGrassCS::NumThreadsX),
		FMath::DivideAndRoundUp(Resolution, FWindGrassCS::NumThreadsY),
		1
	);

	FComputeShaderUtils::AddPass(
		GraphBuilder,
		RDG_EVENT_NAME("UEWindGrass"),
		ComputeShader,
		Parameters,
		FIntVector(1, 1, 1)
		// GroupCount
	);
}
