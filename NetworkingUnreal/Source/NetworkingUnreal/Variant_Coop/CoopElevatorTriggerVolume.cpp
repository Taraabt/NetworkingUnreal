#include "Variant_Coop/CoopElevatorTriggerVolume.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "Variant_Coop/CoopElevatorPlatform.h"
#include "UObject/ConstructorHelpers.h"

ACoopElevatorTriggerVolume::ACoopElevatorTriggerVolume()
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
		FVector(160.0f, 160.0f, 120.0f)
	);

	TriggerBox->SetGenerateOverlapEvents(true);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(
		this,
		&ACoopElevatorTriggerVolume::OnTriggerBeginOverlap
	);

	TriggerBox->OnComponentEndOverlap.AddDynamic(
		this,
		&ACoopElevatorTriggerVolume::OnTriggerEndOverlap
	);

	VisualPad = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("VisualPad")
	);

	VisualPad->SetupAttachment(RootComponent);

	VisualPad->SetCollisionProfileName(
		TEXT("NoCollision")
	);

	VisualPad->SetGenerateOverlapEvents(false);

	InstructionText = CreateDefaultSubobject<UTextRenderComponent>(
		TEXT("InstructionText")
	);

	InstructionText->SetupAttachment(RootComponent);

	InstructionText->SetHorizontalAlignment(
		EHTA_Left
	);

	InstructionText->SetTextRenderColor(
		FColor(255, 140, 40)
	);

	InstructionText->SetWorldSize(
		32.0f
	);

	InstructionText->SetText(
		FText::FromString(
			TEXT("Stay here\nto activate\nElevator")
		)
	);

	InstructionText->SetRelativeLocation(
		FVector(0.0f, -220.0f, 150.0f)
	);

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
		FVector(3.5f, 3.5f, 0.25f)
	);
}

void ACoopElevatorTriggerVolume::SetPlatform(
	ACoopElevatorPlatform* InPlatform
)
{
	TargetPlatform = InPlatform;

	SyncPlatform();
}

void ACoopElevatorTriggerVolume::OnTriggerBeginOverlap(
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

	OverlappingPlayers.Add(
		TWeakObjectPtr<ACharacter>(PlayerCharacter)
	);

	SyncPlatform();
}

void ACoopElevatorTriggerVolume::OnTriggerEndOverlap(
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

	ACharacter* PlayerCharacter =
		Cast<ACharacter>(OtherActor);

	if (!PlayerCharacter)
	{
		return;
	}

	OverlappingPlayers.Remove(
		TWeakObjectPtr<ACharacter>(PlayerCharacter)
	);

	SyncPlatform();
}

void ACoopElevatorTriggerVolume::SyncPlatform()
{
	if (TargetPlatform)
	{
		TargetPlatform->SetOpen(
			OverlappingPlayers.Num() > 0
		);
	}
}