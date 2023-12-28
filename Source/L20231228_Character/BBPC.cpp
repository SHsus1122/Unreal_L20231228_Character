// Fill out your copyright notice in the Description page of Project Settings.


#include "BBPC.h"
#include "EnhancedInputSubsystems.h"

void ABBPC::BeginPlay()
{
	Super::BeginPlay();

	// SubSystem 이란?
	//  - 언리얼 엔진에서 엔진이나 게임에서 사용하는 특정 기능을 구현하고 관리하는데 사용되는 모듈입니다.
	//    이를 통해 엔진의 여러 부분간에 특정 기능을 공유하고 확장 가능성을 제공합니다.
	// 즉, 아래에서 말하는 UEnhancedInputLocalPlayerSubsystem 는 향상된 입력을 제공하는 SubSystem 클래스로 
	// 로컬 플레이어의 입력을 향상시키는 기능을 제공합니다. 이를 통해 MappingContext 를 추가하고 관리합니다.

	// 아래의 코드는 SubSystem 으로부터 Localplayer 정보를 가져오는 코드입니다.
	// ULocalPlayer 클래스로의 서브시스템을 가져와서 이곳에서 현재 로컬플레이어 정보를 가져옵니다.
	UEnhancedInputLocalPlayerSubsystem* SubSystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	// 이후 얻은 서브시스템이 유효하고, DefaultIMC 가 유효한 경우에 로직을 이어갑니다.
	if (SubSystem && DefaultIMC)
	{
		// MappingContext 인 DefaultIMC 를 서브 시스템에 추가합니다.
		// 이후 이를 통해 입력 매핑을 효과적으로 정의하고 관리하게 되며, 0 은 컨텍스트의 우선순위입니다.
		// 이는 더 높은 우선순위의 컨텍스트가 현재 활성화된 경우에만 해당 컨텍스트를 사용하게 합니다.
		SubSystem->AddMappingContext(DefaultIMC, 0);
	}
}
