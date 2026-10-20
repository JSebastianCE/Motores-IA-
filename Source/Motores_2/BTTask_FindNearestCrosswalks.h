#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNearestCrosswalks.generated.h"

UCLASS()
class MOTORES_2_API UBTTask_FindNearestCrosswalks : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindNearestCrosswalks();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector CrosswalkKey;
};