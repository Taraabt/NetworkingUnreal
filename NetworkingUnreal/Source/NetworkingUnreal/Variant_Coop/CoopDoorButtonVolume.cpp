#include "Variant_Coop/CoopDoorButtonVolume.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "Materials/MaterialInterface.h"
#include "Variant_Coop/CoopSlidingDoor.h"
#include "UObject/ConstructorHelpers.h"

ACoopDoorButtonVolume::ACoopDoorButtonVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	bAlwaysRelevant = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetBoxExtent(FVector(90.0f, 90.0f, 70.0f));

	TriggerBox->OnComponentBeginOverlap.AddDynamic(
		this,
		&ACoopDoorButtonVolume::OnTriggerBeginOverlap
	);

	TriggerBox->OnComponentEndOverlap.AddDynamic(
		this,
		&ACoopDoorButtonVolume::OnTriggerEndOverlap
	);

	VisualButton = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("VisualButton")
	);

	VisualButton->SetupAttachment(RootComponent);
	VisualButton->SetCollisionProfileName(TEXT("NoCollision"));

	InstructionText = CreateDefaultSubobject<UTextRenderComponent>(
		TEXT("InstructionText")
	);

	InstructionText->SetupAttachment(RootComponent);

	InstructionText->SetHorizontalAlignment(EHTA_Left);

	InstructionText->SetTextRenderColor(
		FColor(255, 140, 40)
	);

	InstructionText->SetWorldSize(28.0f);

	InstructionText->SetText(
		FText::FromString(
			TEXT("Bump to toggle\nDoor")
		)
	);

	InstructionText->SetRelativeLocation(
		FVector(120.0f, 0.0f, 90.0f)
	);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ButtonMesh(
		TEXT(
			"/Game/LevelPrototyping/Meshes/"
			"SM_ChamferCube.SM_ChamferCube"
		)
	);

	if (ButtonMesh.Succeeded())
	{
		VisualButton->SetStaticMesh(
			ButtonMesh.Object
		);
	}


	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FlatMaterial(
		TEXT(
			"/Game/LevelPrototyping/Materials/"
			"M_FlatCol.M_FlatCol"
		)
	);

	if (FlatMaterial.Succeeded())
	{
		VisualButton->SetMaterial(
			0,
			FlatMaterial.Object
		);
	}

	VisualButton->SetRelativeScale3D(
		FVector(0.8f, 0.8f, 0.3f)
	);
}

void ACoopDoorButtonVolume::SetTargetDoor(
	ACoopSlidingDoor* InDoor
)
{
	TargetDoor = InDoor;
}

void ACoopDoorButtonVolume::OnTriggerBeginOverlap(
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

	if (
		!PlayerCharacter ||
		!PlayerCharacter->IsPlayerControlled()
		)
	{
		return;
	}

	if (
		TouchingPlayers.Contains(
			TWeakObjectPtr<ACharacter>(
				PlayerCharacter
			)
		)
		)
	{
		return;
	}

	TouchingPlayers.Add(
		TWeakObjectPtr<ACharacter>(
			PlayerCharacter
		)
	);

	if (TargetDoor)
	{
		TargetDoor->SetOpen(
			!TargetDoor->IsOpen()
		);
	}
}

void ACoopDoorButtonVolume::OnTriggerEndOverlap(
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

	if (PlayerCharacter)
	{
		TouchingPlayers.Remove(
			TWeakObjectPtr<ACharacter>(
				PlayerCharacter
			)
		);
	}
}