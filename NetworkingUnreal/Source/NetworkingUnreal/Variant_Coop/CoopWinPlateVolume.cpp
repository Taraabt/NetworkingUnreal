#include "Variant_Coop/CoopWinPlateVolume.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Variant_Coop/CoopPuzzleGameState.h"
#include "UObject/ConstructorHelpers.h"

ACoopWinPlateVolume::ACoopWinPlateVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	bAlwaysRelevant = true;



	TriggerBox = CreateDefaultSubobject<UBoxComponent>(
		TEXT("TriggerBox")
	);

	RootComponent = TriggerBox;

	TriggerBox->SetCollisionProfileName(
		TEXT("Trigger")
	);

	TriggerBox->SetBoxExtent(
		FVector(170.0f, 170.0f, 80.0f)
	);

	TriggerBox->SetGenerateOverlapEvents(true);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(
		this,
		&ACoopWinPlateVolume::OnTriggerBeginOverlap
	);

	TriggerBox->OnComponentEndOverlap.AddDynamic(
		this,
		&ACoopWinPlateVolume::OnTriggerEndOverlap
	);


	VisualPad = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("VisualPad")
	);

	VisualPad->SetupAttachment(RootComponent);

	VisualPad->SetCollisionProfileName(
		TEXT("NoCollision")
	);

	VisualPad->SetGenerateOverlapEvents(false);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> PadMesh(
		TEXT(
			"/Game/LevelPrototyping/Meshes/"
			"SM_ChamferCube.SM_ChamferCube"
		)
	);

	if (PadMesh.Succeeded())
	{
		VisualPad->SetStaticMesh(
			PadMesh.Object
		);
	}


	VisualPad->SetRelativeScale3D(
		FVector(2.5f, 2.5f, 0.18f)
	);
}

void ACoopWinPlateVolume::SetPlateIndex(
	int32 InPlateIndex
)
{
	PlateIndex = InPlateIndex;
}

void ACoopWinPlateVolume::OnTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{

	if (!HasAuthority())
	{
		return;
	}

	if (!OtherActor)
	{
		return;
	}

	ACharacter* PlayerCharacter =
		Cast<ACharacter>(OtherActor);

	if (!PlayerCharacter)
	{
		return;
	}

	if (!PlayerCharacter->IsPlayerControlled())
	{
		return;
	}


	if (
		CurrentOccupant.IsValid() &&
		CurrentOccupant.Get() != PlayerCharacter
		)
	{
		return;
	}

	CurrentOccupant = PlayerCharacter;

	NotifyGameState();
}

void ACoopWinPlateVolume::OnTriggerEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{

	if (!HasAuthority())
	{
		return;
	}

	if (!OtherActor)
	{
		return;
	}


	if (
		CurrentOccupant.IsValid() &&
		CurrentOccupant.Get() == OtherActor
		)
	{
		CurrentOccupant.Reset();
		NotifyGameState();
	}
}

void ACoopWinPlateVolume::NotifyGameState()
{

	if (!PuzzleGameState)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			PuzzleGameState =
				World->GetGameState<ACoopPuzzleGameState>();
		}
	}

	if (PuzzleGameState)
	{
		PuzzleGameState->RegisterPlateOccupant(
			PlateIndex,
			CurrentOccupant.Get()
		);
	}
}