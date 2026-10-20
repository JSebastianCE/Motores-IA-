#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PedestrianWaitingPoint.generated.h"

UCLASS()
class MOTORES_2_API APedestrianWaitingPoint : public AActor
{
	GENERATED_BODY()

public:
	APedestrianWaitingPoint();

	// Booleano para evitar que las IA se superpongan
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Waiting Point")
	bool bIsOccupied;

	// Referencia al punto correspondiente al otro lado de la calle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waiting Point")
	APedestrianWaitingPoint* CorrespondingExitPoint;
};