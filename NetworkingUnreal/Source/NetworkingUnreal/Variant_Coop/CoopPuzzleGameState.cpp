
#include "Variant_Coop/CoopPuzzleGameState.h"

#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "NetworkingUnreal.h"

ACoopPuzzleGameState::ACoopPuzzleGameState()
{

	bReplicates = true;
}

void ACoopPuzzleGameState::RegisterPlateOccupant(int32 PlateIndex, ACharacter* Occupant)
{
	if (!HasAuthority() || bHasWon)
	{
		return;
	}

	if (PlateIndex == 0)
	{
		LeftPlateOccupant = Occupant;
	}
	else if (PlateIndex == 1)
	{
		RightPlateOccupant = Occupant;
	}

	EvaluateVictory();
}

void ACoopPuzzleGameState::EvaluateVictory()
{
	if (bHasWon)
	{
		return;
	}

	ACharacter* LeftCharacter = LeftPlateOccupant.Get();
	ACharacter* RightCharacter = RightPlateOccupant.Get();

	if (LeftCharacter && RightCharacter && LeftCharacter != RightCharacter)
	{
		bHasWon = true;
		ForceNetUpdate();
		OnRep_HasWon();
	}
}

void ACoopPuzzleGameState::OnRep_HasWon()
{
	if (bHasWon)
	{
		ShowVictoryMessage();
	}
}

void ACoopPuzzleGameState::ShowVictoryMessage() const
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			8.0f,
			FColor::Yellow,
			TEXT("Hai vinto\nYou won"));
	}

	UE_LOG(LogNetworkingUnreal, Log, TEXT("Co-op win condition completed."));
}

void ACoopPuzzleGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACoopPuzzleGameState, bHasWon);
}
