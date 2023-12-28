// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "InputActionValue.h"

#include "BBPC.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class L20231228_CHARACTER_API ABBPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	// 커스텀 InputMappingContext 를 사용하기 위해 변수(속성)를 추가
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Data")
	TObjectPtr<UInputMappingContext> DefaultIMC;
	
	virtual void BeginPlay() override;
};
