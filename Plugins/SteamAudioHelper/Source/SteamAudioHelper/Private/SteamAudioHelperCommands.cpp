// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteamAudioHelperCommands.h"

#define LOCTEXT_NAMESPACE "FSteamAudioHelperModule"

void FSteamAudioHelperCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "SteamAudioHelper", "Add Steam Audio Static Geometry to all selected actors", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
