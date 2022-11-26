#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    springArm->SetupAttachment(RootComponent);

    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera->SetupAttachment(springArm);
}
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this, &ATank::Fire);
}
void ATank::BeginPlay()
{
	Super::BeginPlay();

    tankPlayerController = Cast<APlayerController>(GetController());
    
}
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(tankPlayerController)
    {
        FHitResult hit;
        tankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit);
        DrawDebugSphere(GetWorld(),hit.ImpactPoint,5.0f,8,FColor::Red,false,-1.0f);
        RotateTurret(hit.ImpactPoint);
    }

}
void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}
void ATank::Move(float value)
{
    FVector deltaLocation = FVector::ZeroVector;
    deltaLocation.X = value * speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(deltaLocation, true);
}
void ATank::Turn(float value)
{
    FRotator deltaRotation = FRotator::ZeroRotator;
    deltaRotation.Yaw = value * turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(deltaRotation, true);
}