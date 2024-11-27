// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SteamAudioHelperStyle.h"

class FSteamAudioHelperCommands : public TCommands<FSteamAudioHelperCommands>
{
public:

	FSteamAudioHelperCommands()
		: TCommands<FSteamAudioHelperCommands>(TEXT("SteamAudioHelper"), NSLOCTEXT("Contexts", "SteamAudioHelper", "SteamAudioHelper Plugin"), NAME_None, FSteamAudioHelperStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
