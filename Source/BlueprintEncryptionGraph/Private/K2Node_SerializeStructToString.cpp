// Copyright 2022 Chris Ringenberg https://www.ringenberg.dev/

#include "K2Node_SerializeStructToString.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintJwtLibrary.h"

#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "K2Node_SerializeStructToString"

UK2Node_SerializeStructToString::UK2Node_SerializeStructToString()
{
	FunctionReference.SetExternalMember(
		GET_FUNCTION_NAME_CHECKED(UBlueprintJwtLibrary, SerializeStructToString),
		UBlueprintJwtLibrary::StaticClass());
}

void UK2Node_SerializeStructToString::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();

	struct FPinStatics
	{
		int32 InputStructPinIndex = -1;
		int32 OutputStringIndex = -1;

		FPinStatics(const TArray<UEdGraphPin*>& InPins)
		{
			InputStructPinIndex = FindPinByName(InPins, TEXT("Struct"));
			OutputStringIndex = FindPinByName(InPins, TEXT("OutJsonString"));
		}

		static int32 FindPinByName(const TArray<UEdGraphPin*>& InPins, const FName& InName)
		{
			return InPins.IndexOfByPredicate([&InName](const UEdGraphPin* InPin)->bool
			{
				return InPin->GetFName() == InName;
			});
		}
		
	} static PinInfo{Pins};

	UEdGraphPin* InputStructPin = GetPinAt(PinInfo.InputStructPinIndex);
	check(InputStructPin);

	UEdGraphPin* OutputStringPin = GetPinAt(PinInfo.OutputStringIndex);
	check(OutputStringPin);
	
}

FText UK2Node_SerializeStructToString::GetTooltipText() const
{
	return LOCTEXT("TooltipText", "Converts a Structure to a JSON string that can be used as a JWT payload.");
}

bool UK2Node_SerializeStructToString::IsNodePure() const
{
	return false;
}

void UK2Node_SerializeStructToString::GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const
{
	const UClass* ActionKey = GetClass();
	if (InActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		InActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}

FText UK2Node_SerializeStructToString::GetMenuCategory() const
{
	static FText MenuCategory = LOCTEXT("MenuCategory", "Blueprint Encryption | Utils");
	return MenuCategory;
}

void UK2Node_SerializeStructToString::NotifyInputChanged() const
{
	if (UBlueprint* BP = GetBlueprint())
	{
		FBlueprintEditorUtils::MarkBlueprintAsModified(BP);
	}

	UEdGraph* Graph = GetGraph();
	Graph->NotifyGraphChanged();
}

#undef LOCTEXT_NAMESPACE