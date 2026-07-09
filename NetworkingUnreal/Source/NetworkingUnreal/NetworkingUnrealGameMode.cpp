#include "NetworkingUnrealGameMode.h"

#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"

#include "Variant_Coop/CoopPuzzleGameState.h"

ANetworkingUnrealGameMode::ANetworkingUnrealGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassFinder(
        TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter")
    );

    if (DefaultPawnClassFinder.Succeeded())
    {
        DefaultPawnClass = DefaultPawnClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(
        TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonPlayerController")
    );

    if (PlayerControllerClassFinder.Succeeded())
    {
        PlayerControllerClass = PlayerControllerClassFinder.Class;
    }

    GameStateClass = ACoopPuzzleGameState::StaticClass();
}