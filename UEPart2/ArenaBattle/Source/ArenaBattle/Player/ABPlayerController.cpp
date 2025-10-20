// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABPlayerController.h"

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 입력 모드 전환
	// 기본 입력 상태가 뷰포트에 흡수되도록(마우스 포인터 안보이도록)
	FInputModeGameOnly GameOnlyInputMode; // 게임 전용 입력 모드로 설정
	SetInputMode(GameOnlyInputMode);
}
