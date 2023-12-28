// Fill out your copyright notice in the Description page of Project Settings.


#include "BBPC.h"
#include "EnhancedInputSubsystems.h"

void ABBPC::BeginPlay()
{
	Super::BeginPlay();

	// SubSystem 으로부터 Localplayer 정보를 가져오는 코드
	UEnhancedInputLocalPlayerSubsystem* SubSystem = 
		ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (SubSystem && DefaultIMC)
	{
		SubSystem->AddMappingContext(DefaultIMC, 0);
	}
}
