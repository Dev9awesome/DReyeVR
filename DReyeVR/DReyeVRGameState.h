#pragma once

#include "Carla/Actor/DReyeVRCustomActor.h" // ADReyeVRCustomActor
#include "Carla/Game/CarlaGameModeBase.h"   // ACarlaGameModeBase
#include "Carla/Sensor/DReyeVRData.h"       // DReyeVR::
#include "DReyeVRPawn.h"                    // ADReyeVRPawn
#include "DReyeVRUtils.h"                   // SafePtrGet<T>
#include <unordered_map>                    // std::unordered_map

#include "DReyeVRGameMode.generated.h"

class AEgoVehicle;

UCLASS()
class ADReyeVRGameState : public AGameState
{
    GENERATED_UCLASS_BODY()

  public:
    ADReyeVRGameState();


    APawn *GetSpectator();
    AEgoVehicle *GetEgoVehicle();
    APlayerController *GetPlayer();
    ADReyeVRPawn *GetPawn();

    void SetEgoVehicle(AEgoVehicle *Ego);

    // input handling
    void SetupPlayerInputComponent();

    // EgoVehicle functions
    void PossessEgoVehicle();
    void PossessSpectator();
    void HandoffDriverToAI();
    

  private:
    // for handling inputs and possessions
    void SetupDReyeVRPawn();
    void SetupSpectator();
    bool SetupEgoVehicle();
    void SpawnEgoVehicle(const FTransform &SpawnPt);

    // TWeakObjectPtr's allow us to check if the underlying object is alive
    // in case it was destroyed by someone other than us (ex. garbage collection)
    TWeakObjectPtr<class APlayerController> Player;
    TWeakObjectPtr<class ADReyeVRPawn> DReyeVR_Pawn;
    TWeakObjectPtr<class APawn> SpectatorPtr;
    TWeakObjectPtr<class AEgoVehicle> EgoVehiclePtr;

    // for toggling bw spectator mode
    bool bIsSpectating = true;

    // for audio control
    float EgoVolumePercent;
    float NonEgoVolumePercent;
    float AmbientVolumePercent;

    bool bDoSpawnEgoVehicleTransform = false; // whether or not to use provided SpawnEgoVehicleTransform
    FTransform SpawnEgoVehicleTransform;

};