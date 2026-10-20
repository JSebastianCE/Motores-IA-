#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PedestrianCharacter.generated.h"

UCLASS()
class MOTORES_2_API APedestrianCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APedestrianCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 160.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrossingSpeed = 190.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};