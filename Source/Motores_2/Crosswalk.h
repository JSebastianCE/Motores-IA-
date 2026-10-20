#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Crosswalk.generated.h"

class APedestrianTrafficLight;

UCLASS()
class MOTORES_2_API ACrosswalk : public AActor
{
	GENERATED_BODY()

public:
	ACrosswalk();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootComp;

	// Cajas de colisión para detectar peatones en la acera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crosswalk")
	UBoxComponent* WaitingZoneSideA;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crosswalk")
	UBoxComponent* WaitingZoneSideB;

	// Destinos al cruzar (Punto B es la meta si vienes de A, y viceversa)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crosswalk")
	USceneComponent* ExitPointSideA;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crosswalk")
	USceneComponent* ExitPointSideB;

	// Semáforo asociado
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosswalk")
	APedestrianTrafficLight* LinkedTrafficLight;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnWaitingZoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWaitingZoneEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};