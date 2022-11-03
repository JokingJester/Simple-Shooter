// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingCharacter.h"
#include "Gun.h"

// Sets default values
AShootingCharacter::AShootingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShootingCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	  
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_rSocket"));
	Gun->SetOwner(this);
	
}

// Called every frame
void AShootingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AShootingCharacter::IsDead() const
{
	return Health <= 0;
}

// Called to bind functionality to input
void AShootingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this, &AShootingCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this, &AShootingCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp",this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight",this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpRate",this, &AShootingCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("LookRightRate",this, &AShootingCharacter::LookRightRate);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &AShootingCharacter::Shoot);
}

float AShootingCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	return DamageToApply;
}

void AShootingCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);

}

void AShootingCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShootingCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShootingCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShootingCharacter::Shoot()
{
	Gun->PullTrigger();
}

