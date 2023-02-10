// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_WZ_PatrolPoint.h"
#include "Components/ActorComponent.h"
#include "AC_WZ_PatrolComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WATCHZONE_API UAC_WZ_PatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_WZ_PatrolComponent();

	UPROPERTY(EditAnywhere)
	int32 CurrentPatrolPoint;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AA_WZ_PatrolPoint*> PatrolPoints;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	TArray<AA_WZ_PatrolPoint*> GetPatrolPoints();
};
