#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PedestrianTrafficLight.generated.h"

UENUM(BlueprintType)
enum class EPedestrianLightState : uint8
{
  Walk,
  Warning,
  DontWalk
};

UCLASS()
class MOTORES_2_API APedestrianTrafficLight : public AActor
{
  GENERATED_BODY()

public:
  APedestrianTrafficLight();

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Traffic Light")
  EPedestrianLightState CurrentState;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Light")
  float WalkDuration = 5.0f;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Light")
  float WarningDuration = 2.0f;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Light")
  float DontWalkDuration = 5.0f;

  // Función matemática para verificar si hay tiempo suficiente para cruzar
  UFUNCTION(BlueprintCallable, Category = "Traffic Light")
  bool IsSafeToStartCrossing(float EstimatedCrossingTime) const;

  // Evento que implementaremos en Blueprint para cambiar el color
  UFUNCTION(BlueprintImplementableEvent, Category = "Traffic Light")
  void UpdateVisual();

protected:
  virtual void BeginPlay() override;
  void ChangeState();

  FTimerHandle LightTimerHandle;
};