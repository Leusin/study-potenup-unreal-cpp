// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"

// Declare Delegate.
DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSigniture, const FString& /*SchoolName*/, const FString& /*Information*/);

/**
 *
 */
UCLASS()
class UNREALDELEGATE_API UCourseInfo : public UObject
{
    GENERATED_BODY()

public:

    // 생성자.
    UCourseInfo();

    // 학사 정보 변경 함수.
    void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContent);

    // 학사 정보 발행을 위한 델리게이트.
    FCourseInfoOnChangedSigniture OnChanged;

private:
    // 학사 정보.
    FString Contents;
};