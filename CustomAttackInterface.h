#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CustomAttackInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCustomAttackInterface : public UInterface
{
    GENERATED_BODY()
};

class GJ_API ICustomAttackInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Attack")
    void Attack(AActor* Attacker);
};
