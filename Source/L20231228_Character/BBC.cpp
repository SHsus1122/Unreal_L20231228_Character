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

	// BBC 캐릭터의 트리구조에 SpringArm 이라는 이름으로 SprinArmComponent 를 추가합니다.
	// 그리고 해당 컴포넌트는 RootComponent 의 자식으로 붙입니다.
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	// 위의 설명과 동일하게 CameraComponent 를 추가하되 이름은 Camera 로 SpringArm 의 자식으로 합니다.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	// 캐릭터의 초기 위치값 지정
	// 이는 캐릭터의 Mesh 의 상대적인 위치를 조정하는 코드입니다. 이를 통해 기본값(기본 좌표)을 변경합니다.
	// SetRelativeLocation - 상대적인 위치 조정을 위한 함수입니다.
	// -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()
	// 이는 캡슐 컴포넌트의 스케일이 반영된 캡슐의 반 높이를 얻어서 현재 캡슐의 높이의 반을 스케일에 맞게 계산합니다. 
	// 이후 맨 앞에 - 부호가 있는데 이처럼 값을 빼서 해당 오브젝트를 현재 위치에서 아래쪽으로 자신의 높이의 반 만큼 이동합니다.
	// 이를 통해서 캐릭터의 메시를 캡슐의 아래쪽에 정확히 위치시키게 합니다.
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
// 아래의 함수를 통해서 플레이어 입력 요소에 입력 바인딩을 설정합니다.
void ABBC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 형변환을 통해서 PlayerInputComponent 를 UEnhancedInputComponent 형으로 캐스팅 합니다.
	// 즉, 향상된 입력 기능을 제공하는 커스텀 입력 컴포넌트 클래스인 UEnhancedInputComponent 로캐스팅 합니다.
	UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UEIC)
	{
		// 상속받은 ACharacter 에 Jump 관련한 함수는 이미 있기 때문에 ABBC::Jump 함수를 만들지 않아도 됩니다.
		// 아래처럼 우리가 만든 액션에 바인딩을 걸어주고 호출시키는 코드를 작성합니다.
		UEIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ABBC::Jump);
		UEIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ABBC::StopJumping);

		UEIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABBC::Move);
		UEIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABBC::Look);

	}
}

void ABBC::Move(const FInputActionValue& Value)
{
	// 입력값 Value 로 부터 2축(X, Y)형태의 값을 추출합니다.
	FVector2d Dir = Value.Get<FVector2D>();

	// 현재 컨트롤러의 회전 값을 가져와서 이를 Yaw 값만 사용해 캐릭터가 바라보는 방향을 구합니다.
	// 즉, Yaw 에 해당하는 값 외에는 0을 넣은 이유는 Yaw 값만을 구하기 위해서 입니다.
	FRotator CameraRotation = GetControlRotation();
	FRotator DirectionRotation = FRotator(0, CameraRotation.Yaw, 0);

	// 이제 가져온 값을 바탕으로 캐릭터가 전진하는 방향의 벡터값과 오른쪽으로 이동하는 벡터값을 구하게 됩니다.
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(DirectionRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(DirectionRotation);

	// 최종적으로 전진 방향의 벡터와 전후 이동 입력 Dir.Y 를 곱해서 이동값을 추가해줍니다.
	// 두번째 코드는 우측 방향의 벡터와 좌우 이동 입력 Dir.X 를 곱해서 이동값을 추가해줍니다.
	AddMovementInput(ForwardVector, Dir.Y);
	AddMovementInput(RightVector, Dir.X);
}

void ABBC::Look(const FInputActionValue& Value)
{
	// 위처럼 이번에는 캐릭터의 회전을 위해서 입력값으로부터 값을 추출합니다.
	FVector2d Rotation = Value.Get<FVector2D>();

	// 이후에 아래처럼 Yaw 에 대한, Pitch 에 대한 이동값을 추가해줍니다.
	AddControllerYawInput(Rotation.X);
	AddControllerPitchInput(Rotation.Y);
}

