// Fill out your copyright notice in the Description page of Project Settings.


#include "BBPC.h"
#include "EnhancedInputSubsystems.h"

void ABBPC::BeginPlay()
{
	Super::BeginPlay();

	// SubSystem ���κ��� Localplayer ������ �������� �ڵ�
	UEnhancedInputLocalPlayerSubsystem* SubSystem = 
		ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem && DefaultIMC)
	{
		SubSystem->AddMappingContext(DefaultIMC, 0);
	}
}
