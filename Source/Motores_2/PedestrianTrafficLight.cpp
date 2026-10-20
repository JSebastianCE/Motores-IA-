#include "PedestrianTrafficLight.h"
#include "TimerManager.h"

APedestrianTrafficLight::APedestrianTrafficLight()
{
  PrimaryActorTick.bCanEverTick = false;
  CurrentState = EPedestrianLightState::DontWalk;
}

void APedestrianTrafficLight::BeginPlay()
{
  Super::BeginPlay();
  ChangeState();
}

void APedestrianTrafficLight::ChangeState()
{
  float NextTimerDuration = 0.0f;

  switch (CurrentState)
  {
  case EPedestrianLightState::Walk:
    CurrentState = EPedestrianLightState::Warning;
    NextTimerDuration = WarningDuration;
    break;
  case EPedestrianLightState::Warning:
    CurrentState = EPedestrianLightState::DontWalk;
    NextTimerDuration = DontWalkDuration;
    break;
  case EPedestrianLightState::DontWalk:
    CurrentState = EPedestrianLightState::Walk;
    NextTimerDuration = WalkDuration;
    break;
  }

  UpdateVisual(); // Llama al Blueprint para actualizar los materiales
  GetWorld()->GetTimerManager().SetTimer(LightTimerHandle, this, &APedestrianTrafficLight::ChangeState, NextTimerDuration, false);
}

bool APedestrianTrafficLight::IsSafeToStartCrossing(float EstimatedCrossingTime) const
{
  // Si no está en verde, no es seguro
  if (CurrentState != EPedestrianLightState::Walk)
  {
    return false;
  }

  // Obtenemos cuánto tiempo le sobra al estado Walk
  float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(LightTimerHandle);

  // Es seguro si el tiempo restante es mayor o igual al tiempo que tarda el peatón en cruzar
  return RemainingTime >= EstimatedCrossingTime;
}