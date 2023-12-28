// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BBC.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;

UCLASS()
class L20231228_CHARACTER_API ABBC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABBC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
};
