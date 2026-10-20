#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ChooseRandomDestination.generated.h"

UCLASS()
class MOTORES_2_API UBTTask_ChooseRandomDestination : public UBTTask_BlackboardBase
{
  GENERATED_BODY()

public:
  UBTTask_ChooseRandomDestination();

  virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
  float SearchRadius;

  // Probabilidad de que decida cruzar (0.0 a 1.0)
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
  float CrossProbability;

  // Llave del Blackboard que activaremos
  UPROPERTY(EditAnywhere, Category = "Blackboard")
  struct FBlackboardKeySelector NeedsToCrossKey;
};