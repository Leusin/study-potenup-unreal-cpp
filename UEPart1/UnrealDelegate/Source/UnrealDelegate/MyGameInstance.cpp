// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "CourseInfo.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	SchoolName = TEXT("대리자 학교");

	// 학사 정보 객체 생성
	CourseInfo = NewObject<UCourseInfo>(this);

	UE_LOG(LogTemp, Log, TEXT("====================================="));

	// 학생 객체 생성

	UStudent* Student1 = NewObject<UStudent>();
	Student1->SetName(TEXT("김학생"));

	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("이학생"));

	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("박학생"));

	// 메시지 구독

	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);

	// 테스트 메시지 발행
	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("준비 땅"));

	/// 출력 결과
	/* 
	LogTemp: =====================================
	LogTemp: [CourseInfo] 학사 정보가 변경되어 알림을 발송합니다.
	LogTemp: [Student] 박학생님이 대리자 학교로부터 받은 메시지: 준비 땅
	LogTemp: [Student] 이학생님이 대리자 학교로부터 받은 메시지: 준비 땅
	LogTemp: [Student] 김학생님이 대리자 학교로부터 받은 메시지: 준비 땅
	*/

	UE_LOG(LogTemp, Log, TEXT("====================================="))
}
