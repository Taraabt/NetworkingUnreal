#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CoopPuzzleGameState.generated.h"

class ACharacter;
class FLifetimeProperty;

UCLASS()
class ACoopPuzzleGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	ACoopPuzzleGameState();

	void RegisterPlateOccupant(int32 PlateIndex, ACharacter* Occupant);

protected:

	UPROPERTY(ReplicatedUsing = OnRep_HasWon)
	bool bHasWon = false;

	TWeakObjectPtr<ACharacter> LeftPlateOccupant;

	TWeakObjectPtr<ACharacter> RightPlateOccupant;

	UFUNCTION()
	void OnRep_HasWon();

	void EvaluateVictory();

	void ShowVictoryMessage() const;

public:

	UFUNCTION(BlueprintPure, Category="Coop Puzzle")
	bool HasWon() const { return bHasWon; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
