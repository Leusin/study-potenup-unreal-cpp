// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ABAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UABAnimInstance::UABAnimInstance()
{
	// 이동을 판단할 때 사용 기준 값
	MoveingThreshold = 3.0f;

	// 점프 중인지 판단할 기준값 
	JumpingThreshold = 100.0f;
}

void UABAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 애니메이션 재생에 사용될 기준값 설정
	if (Movement)
	{
		// 캐릭터 무브먼트 컴포넌트의 현재 속도(방향 + 빠르기)
		Velocity = Movement->Velocity;

		// 지면에서의 이동 빠르기 구하기
		// 블랜드(섞는다) 스페이스에서 사용할 값
		GroundSpeed = Velocity.Size2D();

		// 이동/정지 상태 설정
		bIsIdle = GroundSpeed < MoveingThreshold;

		// 공중에 떠 있는지 확인
		bIsFalling = Movement->IsFalling();

		// 점프 중인지 판단
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshold);
	}
}
