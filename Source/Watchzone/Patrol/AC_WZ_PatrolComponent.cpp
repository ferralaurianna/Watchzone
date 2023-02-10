// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_WZ_PatrolComponent.h"


// Sets default values for this component's properties
UAC_WZ_PatrolComponent::UAC_WZ_PatrolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_WZ_PatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_WZ_PatrolComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<AA_WZ_PatrolPoint*> UAC_WZ_PatrolComponent::GetPatrolPoints()
{
	return PatrolPoints;
}


