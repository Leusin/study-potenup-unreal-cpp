// Fill out your copyright notice in the Description page of Project Settings.


#include "CourseInfo.h"

UCourseInfo::UCourseInfo()
{
    Contents = TEXT("기본 학사 정보");
}

void UCourseInfo::ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents)
{
    // 내용 설정.
    Contents = InNewContents;

    // 이벤트 발행.
    UE_LOG(LogTemp, Log, TEXT("[CourseInfo] 학사 정보가 변경되어 알림을 발송합니다."));
    OnChanged.Broadcast(InSchoolName, Contents);
}