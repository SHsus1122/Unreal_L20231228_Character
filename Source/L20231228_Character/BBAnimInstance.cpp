// Fill out your copyright notice in the Description page of Project Settings.


#include "BBAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBBAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// Super �� �θ� �Լ��� ȣ�� �ؼ� ������ �ϱ����� �۾��Դϴ�.
	Super::NativeUpdateAnimation(DeltaSeconds);

	// �ش� ���� �����ڰ� ���� Owner �� �´��� �����ͼ� ���� �Ŀ� �۾��� �մϴ�.
	ACharacter* MyCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (IsValid(MyCharacter))
	{
		// Velocity �� ������ ������ �ӵ��̸�, Scalar �� ũ�⸸�� ������ �ֽ��ϴ�.
		// Velocity �� ���ؼ� �������ڸ� Scalar ������� �������� ���⼺�� �� �����ɴϴ�.
		// �׷��� �Ʒ�ó�� �ؼ� �ӵ��� ������ ���ϵ��� ���ݴϴ�. ��, Size2D �� �ϸ� Z ���� �����ϰ� �ӵ��� ����մϴ�.
		Speed = MyCharacter->GetCharacterMovement()->Velocity.Size2D();
	}
}
