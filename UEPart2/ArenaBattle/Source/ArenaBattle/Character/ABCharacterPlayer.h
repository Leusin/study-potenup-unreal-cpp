// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ABCharacterBase.h"
#include "InputActionValue.h"
#include "ABCharacterPlayer.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLE_API AABCharacterPlayer : public AABCharacterBase
{
	GENERATED_BODY()

public:
	AABCharacterPlayer();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 캐릭터 컨트롤 변경 시 사용할 편의 함수
	void SetCharacterControl(ECharacterControlType NewCharacterControlType);

	// 컨트롤 데이터 설정
	virtual void SetCharacterControlData(const class UABCharacterControlData* InCharacterControlData) override;

protected:
	
	// 캐릭터 컨트롤 변경 입력 처리 함수
	void ChangeCharacterControl();

	// 키보드 이동 처리
	void ShoulderMove(const FInputActionValue& Value);

	// 마우스 회전 처리
	void ShoulderLook(const FInputActionValue& Value);

	// QuaterM 모드일 때 이동
	void QuaterMove(const FInputActionValue& Value);

	// 컴포넌트 구성
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SprintArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderMoveAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShoulderLookAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuaterMoveAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	// 쿼터뷰일 때 이동 로직 처리
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChangeControlAction;

	// 현재 사용 중인 캐릭터 컨트롤 타입 변수
	UPROPERTY(VisibleAnywhere, Category = CharacterControl, meta = (AllowPrivateAccess = "true"))
	ECharacterControlType CurrentCharacterControlType;
};
