#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ReserveWaitingPoint.generated.h"

UCLASS()
class MOTORES_2_API UBTTask_ReserveWaitingPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ReserveWaitingPoint();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector CrosswalkKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector TargetDestinationKey;
};