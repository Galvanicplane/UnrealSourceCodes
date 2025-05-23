#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "BaseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

// Sadece FDialogue yapısını tutuyoruz çünkü ileride lazım olabilir.
USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SpeechText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextIndex = -1;
};



UCLASS()
class GJ_API ABaseCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

public:
	// Normal Movement Fonksiyonları Kalıyor
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void OnWalkTriggered(const FInputActionValue& Value);
	void JumpPressed();
	void JumpReleased();

	void UseAbility();
	void RandomEvent();


	// Interaction Fonksiyonları
	void InAttack();
	void InInteract();
	

	// Bunlar override edilecek, şimdilik boşlar
	virtual void MakeAttack();
	virtual void MakeInteract();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAAAA")
	void TakeAttack(int32 TakenDamage);
	virtual void TakeAttack_Implementation(int32 TakenDamage);

	UFUNCTION(BlueprintCallable)
	void TakeInteract();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina=100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10;


	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAAAA")
	void OnRain();
	virtual void OnRain_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAAAA")
	void OnHeat();
	virtual void OnHeat_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAAAA")
	void OnWind();
	virtual void OnWind_Implementation();
	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAAAA")
	void InAbility();
	virtual void InAbility_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAAAA")
	void MakeEvent();
	virtual void MakeEvent_Implementation();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAAAA")
	void Die();
	virtual void Die_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAAAA")
	void Tired();
	virtual void Tired_Implementation();


	

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Walk;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Attack;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Ability;

	// Sadece BoxCollision kalıyor, SphereCollision kaldırıldı
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* BoxComponent;

	// Overlap Aktörünü tutacak
	UPROPERTY()
	ABaseCharacter* OverlappingCharacter;

	// Overlap Eventleri
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                       bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
