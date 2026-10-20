#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PedestrianAIController.generated.h"

// Declaraciones anticipadas para evitar dependencias circulares
class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class MOTORES_2_API APedestrianAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Se ejecuta cuando el controlador toma control del peatón
	virtual void OnPossess(APawn* InPawn) override;

	// Permite asignar el Behavior Tree desde el Blueprint en el editor
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	// Función para que el Manager le asigne a dónde ir
	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetDestination(AActor* NewDestination);

	// Función para consultar a dónde va actualmente
	UFUNCTION(BlueprintCallable, Category = "AI")
	AActor* GetDestination() const;

protected:
	// Referencia guardada a la memoria de la IA para acceso rápido
	UPROPERTY()
	UBlackboardComponent* PedestrianBlackboard;
};