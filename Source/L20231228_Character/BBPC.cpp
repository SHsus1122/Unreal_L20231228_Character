// Fill out your copyright notice in the Description page of Project Settings.


#include "BBPC.h"
#include "EnhancedInputSubsystems.h"

void ABBPC::BeginPlay()
{
	Super::BeginPlay();

	// SubSystem �̶�?
	//  - �𸮾� �������� �����̳� ���ӿ��� ����ϴ� Ư�� ����� �����ϰ� �����ϴµ� ���Ǵ� ����Դϴ�.
	//    �̸� ���� ������ ���� �κа��� Ư�� ����� �����ϰ� Ȯ�� ���ɼ��� �����մϴ�.
	// ��, �Ʒ����� ���ϴ� UEnhancedInputLocalPlayerSubsystem �� ���� �Է��� �����ϴ� SubSystem Ŭ������ 
	// ���� �÷��̾��� �Է��� ����Ű�� ����� �����մϴ�. �̸� ���� MappingContext �� �߰��ϰ� �����մϴ�.

	// �Ʒ��� �ڵ�� SubSystem ���κ��� Localplayer ������ �������� �ڵ��Դϴ�.
	// ULocalPlayer Ŭ�������� ����ý����� �����ͼ� �̰����� ���� �����÷��̾� ������ �����ɴϴ�.
	UEnhancedInputLocalPlayerSubsystem* SubSystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	// ���� ���� ����ý����� ��ȿ�ϰ�, DefaultIMC �� ��ȿ�� ��쿡 ������ �̾�ϴ�.
	if (SubSystem && DefaultIMC)
	{
		// MappingContext �� DefaultIMC �� ���� �ý��ۿ� �߰��մϴ�.
		// ���� �̸� ���� �Է� ������ ȿ�������� �����ϰ� �����ϰ� �Ǹ�, 0 �� ���ؽ�Ʈ�� �켱�����Դϴ�.
		// �̴� �� ���� �켱������ ���ؽ�Ʈ�� ���� Ȱ��ȭ�� ��쿡�� �ش� ���ؽ�Ʈ�� ����ϰ� �մϴ�.
		SubSystem->AddMappingContext(DefaultIMC, 0);
	}
}
