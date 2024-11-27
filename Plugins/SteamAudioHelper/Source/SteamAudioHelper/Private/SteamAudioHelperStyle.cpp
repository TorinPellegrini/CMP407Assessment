// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteamAudioHelperStyle.h"
#include "SteamAudioHelper.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FSteamAudioHelperStyle::StyleInstance = nullptr;

void FSteamAudioHelperStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FSteamAudioHelperStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FSteamAudioHelperStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SteamAudioHelperStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FSteamAudioHelperStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("SteamAudioHelperStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("SteamAudioHelper")->GetBaseDir() / TEXT("Resources"));

	Style->Set("SteamAudioHelper.PluginAction", new IMAGE_BRUSH_SVG(TEXT("Icon"), Icon20x20));
	return Style;
}

void FSteamAudioHelperStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FSteamAudioHelperStyle::Get()
{
	return *StyleInstance;
}
