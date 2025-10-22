// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UABAnimInstance();

protected:
	// 애니메이션 초기화할 때 실행되는 함수
	virtual void NativeInitializeAnimation() override;

	// 애니메이션 업데이트할 때 프레임마다 실행되는 함수
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	// 애니메이션 블루프린트에서 사용할 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> Movement;

	// 캐릭터 이동 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	FVector Velocity;

	// 캐릭터 이동 속력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float GroundSpeed;

	// 이동 하지는지 멈춰있는지 확인 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	uint8 bIsIdle : 1;

	// 이동 여부를 판단할 때 사용할 문턱 값
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float MoveingThreshold;
};
