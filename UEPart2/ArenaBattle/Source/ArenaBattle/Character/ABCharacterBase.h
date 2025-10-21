// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ABCharacterBase.generated.h"

// 캐릭터 타입 열거형
UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder, 
	Quater
};

UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();

protected:
	// 컨트롤 데이터 설정
	virtual void SetCharacterControlData(const class UABCharacterControlData* InCharacterControlData);

protected:
	// 열거형 타입
	UPROPERTY(EditAnywhere, Category = CharacterControl, meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UABCharacterControlData*> CharacterControlManager;
};
