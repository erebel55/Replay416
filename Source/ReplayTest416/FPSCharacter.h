#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

UCLASS()
class REPLAYTEST416_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities)
    class UFPSAbilityComponent* AbilityComponent;

    void StartAbility();

    // Third person camera
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera)
    class UCameraComponent* ThirdPersonCameraComponent;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera)
    class USpringArmComponent* ThirdPersonCameraArm;
};
