// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));

	InitialLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f, 0.0f, 0.0f);

	InitialDirection = FVector(0.0f, 0.0f, 0.0f);

	bInitializeFloaterLocations = false;
	bShouldFloat = false;

	InitialForce = FVector(2000000.f, 0.0f, 0.0f);
	InitialTorque = FVector(2000000.f, 0.0f, 0.0f);

	RunningTime = 0.f;

	Amplitude = 0.f;
	Period = 0.f;
	PhaseShift = 0.f;
	VerticalShift = 0.f;
}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();

	float InitialX = FMath::FRandRange(-500.f, 500.f);
	float InitialY = FMath::FRandRange(-500.f, 500.f);
	float InitialZ = FMath::FRandRange(0.f, 500.f);

	InitialLocation.X = InitialX;
	InitialLocation.Y = InitialY;
	InitialLocation.Z = InitialZ;

	
	PlacedLocation = GetActorLocation();

	if (bInitializeFloaterLocations)
	{
		SetActorLocation(InitialLocation);
	}


	BaseZLocation = PlacedLocation.Z;
	// StaticMesh->AddForce(InitialForce);
	// StaticMesh->AddTorqueInRadians(InitialTorque);

}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldFloat)
	{	
		FVector NewLocation = GetActorLocation();

		NewLocation.Z = BaseZLocation + Amplitude * FMath::Sin(Period * RunningTime - PhaseShift) + VerticalShift; // Period = 2 * PI / ABS(B)

		SetActorLocation(NewLocation);
		RunningTime += DeltaTime;
		//UE_LOG(LogTemp, Warning, TEXT("Hit location: X = %f, Y = %f, Z = %f"), HitLocation.X, HitLocation.Y, HitLocation.Z);
	}

	
}
