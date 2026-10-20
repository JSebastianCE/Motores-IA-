#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsSafeToCross.generated.h"

UCLASS()
class MOTORES_2_API UBTD_IsSafeToCross : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_IsSafeToCross();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
	// Llave para recibir el cruce actual desde el Blackboard
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector CrosswalkKey;
};