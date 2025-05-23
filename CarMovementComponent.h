// CarMovementComponent.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CarMovementComponent.generated.h"

UCLASS(ClassGroup = Movement, meta = (BlueprintSpawnableComponent))
class BS_API UCarMovementComponent : public UPawnMovementComponent
{
    GENERATED_BODY()

public:
    UCarMovementComponent();

    virtual void InitializeComponent() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void SetInputVector(const FVector& Input);

    /** Ayarlanabilir parametreler */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Acceleration = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MaxSpeed = 1200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Friction = 4.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bOrientRotationToMovement = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float RotationInterpSpeed = 5.0f;

    UPROPERTY(BlueprintReadWrite)
    FVector InputVector;

    UPROPERTY(BlueprintReadWrite)
    FVector CarVelocity;


};
