#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FPSAbility.generated.h"

USTRUCT()
struct FFPSAbilityAnimation
{
    GENERATED_BODY()

    // Third person animation played on pawn
    UPROPERTY(EditDefaultsOnly, Category = Animation)
    UAnimMontage* Pawn3P;
};

UCLASS(Blueprintable, BlueprintType)
class REPLAYTEST416_API UFPSAbility : public UObject
{
	GENERATED_BODY()

public:
    // Constructor
    UFPSAbility();

    virtual void PostInitProperties() override;

    // Enable UObject Replication
    bool IsSupportedForNetworking() const override;
	
    UFUNCTION(BlueprintCallable, Category = Ability)
    void Start();

    UFUNCTION(BlueprintCallable, Category = Ability)
    void Execute();

    UFUNCTION(BlueprintCallable, Category = Ability)
    void End();

    UPROPERTY(BlueprintReadOnly, Category = Ability)
    class UFPSAbilityComponent* AbilityComponent;

    UPROPERTY(BlueprintReadOnly, Category = Ability)
    class AFPSCharacter* Character;

    UPROPERTY(Transient, Replicated)
    uint32 ID;

    UPROPERTY(Transient, Replicated, EditDefaultsOnly, Category = Animation)
    FFPSAbilityAnimation Animation;
};
