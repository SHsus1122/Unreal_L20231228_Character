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

	// BBC ĳ������ Ʈ�������� SpringArm �̶�� �̸����� SprinArmComponent �� �߰��մϴ�.
	// �׸��� �ش� ������Ʈ�� RootComponent �� �ڽ����� ���Դϴ�.
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	// ���� ����� �����ϰ� CameraComponent �� �߰��ϵ� �̸��� Camera �� SpringArm �� �ڽ����� �մϴ�.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	// ĳ������ �ʱ� ��ġ�� ����
	// �̴� ĳ������ Mesh �� ������� ��ġ�� �����ϴ� �ڵ��Դϴ�. �̸� ���� �⺻��(�⺻ ��ǥ)�� �����մϴ�.
	// SetRelativeLocation - ������� ��ġ ������ ���� �Լ��Դϴ�.
	// -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()
	// �̴� ĸ�� ������Ʈ�� �������� �ݿ��� ĸ���� �� ���̸� �� ���� ĸ���� ������ ���� �����Ͽ� �°� ����մϴ�. 
	// ���� �� �տ� - ��ȣ�� �ִµ� ��ó�� ���� ���� �ش� ������Ʈ�� ���� ��ġ���� �Ʒ������� �ڽ��� ������ �� ��ŭ �̵��մϴ�.
	// �̸� ���ؼ� ĳ������ �޽ø� ĸ���� �Ʒ��ʿ� ��Ȯ�� ��ġ��Ű�� �մϴ�.
	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	// ĳ���� �ʱ� ȸ����(Pitch, Yaw, Roll)
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
// �Ʒ��� �Լ��� ���ؼ� �÷��̾� �Է� ��ҿ� �Է� ���ε��� �����մϴ�.
void ABBC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ����ȯ�� ���ؼ� PlayerInputComponent �� UEnhancedInputComponent ������ ĳ���� �մϴ�.
	// ��, ���� �Է� ����� �����ϴ� Ŀ���� �Է� ������Ʈ Ŭ������ UEnhancedInputComponent ��ĳ���� �մϴ�.
	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UEIC)
	{
		// ��ӹ��� ACharacter �� Jump ������ �Լ��� �̹� �ֱ� ������ ABBC::Jump �Լ��� ������ �ʾƵ� �˴ϴ�.
		// �Ʒ�ó�� �츮�� ���� �׼ǿ� ���ε��� �ɾ��ְ� ȣ���Ű�� �ڵ带 �ۼ��մϴ�.
		UEIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ABBC::Jump);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ABBC::StopJumping);

		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABBC::Move);
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABBC::Look);

	}
}

void ABBC::Move(const FInputActionValue& Value)
{
	// �Է°� Value �� ���� 2��(X, Y)������ ���� �����մϴ�.
	FVector2d Dir = Value.Get<FVector2D>();

	// ���� ��Ʈ�ѷ��� ȸ�� ���� �����ͼ� �̸� Yaw ���� ����� ĳ���Ͱ� �ٶ󺸴� ������ ���մϴ�.
	// ��, Yaw �� �ش��ϴ� �� �ܿ��� 0�� ���� ������ Yaw ������ ���ϱ� ���ؼ� �Դϴ�.
	FRotator CameraRotation = GetControlRotation();
	FRotator DirectionRotation = FRotator(0, CameraRotation.Yaw, 0);

	// ���� ������ ���� �������� ĳ���Ͱ� �����ϴ� ������ ���Ͱ��� ���������� �̵��ϴ� ���Ͱ��� ���ϰ� �˴ϴ�.
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(DirectionRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(DirectionRotation);

	// ���������� ���� ������ ���Ϳ� ���� �̵� �Է� Dir.Y �� ���ؼ� �̵����� �߰����ݴϴ�.
	// �ι�° �ڵ�� ���� ������ ���Ϳ� �¿� �̵� �Է� Dir.X �� ���ؼ� �̵����� �߰����ݴϴ�.
	AddMovementInput(ForwardVector, Dir.Y);
	AddMovementInput(RightVector, Dir.X);
}

void ABBC::Look(const FInputActionValue& Value)
{
	// ��ó�� �̹����� ĳ������ ȸ���� ���ؼ� �Է°����κ��� ���� �����մϴ�.
	FVector2d Rotation = Value.Get<FVector2D>();

	// ���Ŀ� �Ʒ�ó�� Yaw �� ����, Pitch �� ���� �̵����� �߰����ݴϴ�.
	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}

