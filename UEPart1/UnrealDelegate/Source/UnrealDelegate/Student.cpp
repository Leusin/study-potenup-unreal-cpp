// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
{
	Name = TEXT("김주영");
	Year = 1;
	Id = 1;
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%s님이 공부 합니다."), *Name)
}

void UStudent::GetNotification(const FString& School, const FString& NewCourseInfo)
{
	UE_LOG(LogTemp, Log,
		TEXT("[Student] %s님이 %s로부터 받은 메시지: %s"),
		*Name, *School, *NewCourseInfo);
}