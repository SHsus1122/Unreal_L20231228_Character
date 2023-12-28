// Fill out your copyright notice in the Description page of Project Settings.


#include "BBC.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "kismet/KismetMathLibrary.h"

// Sets default values
ABBC::ABBC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	// 캐릭터 초기 위치값 지정
	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	// 캐릭터 초기 회전값(Pitch, Yaw, Roll)
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
}

// Called when the game starts or when spawned
void ABBC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABBC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABBC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UEIC)
	{
		// 상속받은 ACharacter 에 Jump 관련한 함수는 이미 있기 때문에 ABBC::Jump 함수를 만들지 않아도 됩니다.
		UEIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ABBC::Jump);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ABBC::StopJumping);

		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABBC::Move);
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABBC::Look);

	}
}

void ABBC::Move(const FInputActionValue& Value)
{
	FVector2d Dir = Value.Get<FVector2D>();

	// 캐릭터 기준으로 방향 구하기
	FRotator CameraRotation = GetControlRotation();
	FRotator DirectionRotation = FRotator(0, CameraRotation.Yaw, 0);

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(DirectionRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(DirectionRotation);

	AddMovementInput(ForwardVector, Dir.Y);
	AddMovementInput(RightVector, Dir.X);
}

void ABBC::Look(const FInputActionValue& Value)
{
	FVector2d Rotation = Value.Get<FVector2D>();

	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}

