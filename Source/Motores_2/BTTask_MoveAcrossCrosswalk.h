#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveAcrossCrosswalk.generated.h"

UCLASS()
class MOTORES_2_API UBTTask_MoveAcrossCrosswalk : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MoveAcrossCrosswalk();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector WaitPointKey;
};