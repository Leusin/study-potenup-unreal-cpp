// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("====================================="));

	// 언리얼 배열 사용해보기 
	TArray<UPerson*> Persons = { NewObject<UStudent>(), NewObject<UTeacher>(), NewObject<UStaff>() };

	for (const auto Person : Persons)
	{
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);

		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("> %s님 수업에 입장하셨습니다."), *Person->GetName())
			LessonInterface->DoLesson();
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("> %s님 은 수업에 참여할 수 없습니다."), *Person->GetName())
		}
	}

	UE_LOG(LogTemp, Log, TEXT("====================================="))
}
