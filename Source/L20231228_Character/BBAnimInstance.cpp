// Fill out your copyright notice in the Description page of Project Settings.


#include "BBAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBBAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Super 는 부모 함수를 호출 해서 재정의 하기위한 작업입니다.
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 해당 폰의 소유자가 현재 Owner 가 맞는지 가져와서 검증 후에 작업을 합니다.
	ACharacter* MyCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (IsValid(MyCharacter))
	{
		// Velocity 는 방향을 포함한 속도이며, Scalar 는 크기만을 가지고 있습니다.
		// Velocity 와 비교해서 설명하자면 Scalar 방식으로 가져오면 방향성을 못 가져옵니다.
		// 그래서 아래처럼 해서 속도와 방향을 구하도록 해줍니다. 즉, Size2D 로 하면 Z 축을 제외하고 속도를 계산합니다.
		Speed = MyCharacter->GetCharacterMovement()->Velocity.Size2D();
	}
}
