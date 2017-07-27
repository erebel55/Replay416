#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FPSAbilitySet.generated.h"

UCLASS(Blueprintable)
class REPLAYTEST416_API UFPSAbilitySet : public UObject
{
	GENERATED_BODY()

public:
    // Constructor
    UFPSAbilitySet();

    virtual void PostInitProperties() override;
	
    // Enable UObject Replication
    bool IsSupportedForNetworking() const override;
    virtual bool ReplicateSubobjects(class UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);
	
    UPROPERTY(EditDefaultsOnly, Category = Abilities)
    TArray<TSubclassOf<class UFPSAbility>> DefaultAbilityClasses;

    UPROPERTY(Transient, Replicated, BlueprintReadOnly, Category = Abilities)
    TArray<class UFPSAbility*> Abilities;
	
};
