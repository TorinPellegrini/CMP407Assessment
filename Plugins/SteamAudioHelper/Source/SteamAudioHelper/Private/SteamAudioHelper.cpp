// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteamAudioHelper.h"

#include "Selection.h"
#include "SteamAudioGeometryComponent.h"
#include "SteamAudioHelperStyle.h"
#include "SteamAudioHelperCommands.h"
#include "SubobjectDataSubsystem.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Engine/StaticMeshActor.h"

static const FName SteamAudioHelperTabName("SteamAudioHelper");

#define LOCTEXT_NAMESPACE "FSteamAudioHelperModule"

void FSteamAudioHelperModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSteamAudioHelperStyle::Initialize();
	FSteamAudioHelperStyle::ReloadTextures();

	FSteamAudioHelperCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSteamAudioHelperCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FSteamAudioHelperModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSteamAudioHelperModule::RegisterMenus));
}

void FSteamAudioHelperModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FSteamAudioHelperStyle::Shutdown();

	FSteamAudioHelperCommands::Unregister();
}

void FSteamAudioHelperModule::PluginButtonClicked()
{
	USelection* SelectedActors = GEditor->GetSelectedActors();

	TArray<AStaticMeshActor*> StaticMeshActors;

	for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
	{
		AStaticMeshActor* Actor = Cast<AStaticMeshActor>(*Iter);
		if (Actor)
		{
			TArray<FSubobjectDataHandle> Objects;
			USubobjectDataSubsystem::Get()->GatherSubobjectData(Actor, Objects);
			FAddNewSubobjectParams AddNewSubobjectParams;
			AddNewSubobjectParams.AssetOverride = Actor;
			AddNewSubobjectParams.NewClass = USteamAudioGeometryComponent::StaticClass();
			AddNewSubobjectParams.ParentHandle = Objects[0];
			FText FailReason;
			USubobjectDataSubsystem::Get()->AddNewSubobject(AddNewSubobjectParams, FailReason);
		}
	}

	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Operation complete, make sure to double check if components have been added"));
}

void FSteamAudioHelperModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FSteamAudioHelperCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSteamAudioHelperCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSteamAudioHelperModule, SteamAudioHelper)