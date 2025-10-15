// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// 직렬화 처리를 위한 구조체.
struct FStudentData
{
    FStudentData() {}
    FStudentData(int32 InOrder, const FString& InName)
        : Order(InOrder), Name(InName)
    {
    }

    // 직렬화 처리 연산자 오버로딩.
    friend FArchive& operator<<(
        FArchive& Archive,
        FStudentData& InStudentData)
    {
        Archive << InStudentData.Order;
        Archive << InStudentData.Name;

        return Archive;
    }

    int32 Order = -1;
    FString Name = TEXT("기본이름");
};

/**
 * 
 */
UCLASS()
class UNREALSERIALIZATION_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
    UMyGameInstance();

    void Init() override;
};
