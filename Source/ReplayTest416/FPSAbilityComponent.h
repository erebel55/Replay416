#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSAbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REPLAYTEST416_API UFPSAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPSAbilityComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

    virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void Start(int32 Index);

    void StartAbility(int32 Index);

    UFUNCTION(Reliable, Server, WithValidation)
    void ServerStartAbility(int32 Index);

    UFUNCTION(Reliable, NetMulticast)
    void MulticastStartAbility(int32 Index);

    UPROPERTY()
    class AFPSCharacter* OwningCharacter;

    UPROPERTY(Transient, Replicated, BlueprintReadOnly, Category = Abilities)
    class UFPSAbilitySet* AbilitySet;

protected:

    UPROPERTY(EditDefaultsOnly, Category = Abilities)
    TSubclassOf<class UFPSAbilitySet> DefaultAbilitySetClass;
	
};
