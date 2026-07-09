#include "Variant_Coop/CoopMovingBlockActor.h"

#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Net/UnrealNetwork.h"

ACoopMovingBlockActor::ACoopMovingBlockActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);
	SetNetUpdateFrequency(60.0f);
	SetMinNetUpdateFrequency(30.0f);
	bAlwaysRelevant = true;

	RootComponent = MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
	MeshComponent->SetGenerateOverlapEvents(false);
	MeshComponent->SetMobility(EComponentMobility::Movable);
}

void ACoopMovingBlockActor::BeginPlay()
{
	Super::BeginPlay();

	ClosedLocation = GetActorLocation();
	OpenLocation = ClosedLocation + OpenOffset;

	if (BaseMaterial)
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		if (DynamicMaterial)
		{
			DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), TintColor);
			DynamicMaterial->SetVectorParameterValue(TEXT("Base Color"), TintColor);
			DynamicMaterial->SetVectorParameterValue(TEXT("Color"), TintColor);
			MeshComponent->SetMaterial(0, DynamicMaterial);
		}
	}
}

void ACoopMovingBlockActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!HasAuthority())
	{
		return;
	}

	const FVector TargetLocation = bOpen ? OpenLocation : ClosedLocation;
	const FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), TargetLocation, DeltaSeconds, MoveSpeed);
	SetActorLocation(NewLocation);
}

void ACoopMovingBlockActor::SetOpen(bool bNewOpen)
{
	if (!HasAuthority())
	{
		return;
	}

	if (bOpen == bNewOpen)
	{
		return;
	}

	bOpen = bNewOpen;
	ForceNetUpdate();
	OnRep_OpenState();
}

void ACoopMovingBlockActor::OnRep_OpenState()
{

}

void ACoopMovingBlockActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACoopMovingBlockActor, bOpen);
}
