// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"

UMyGameInstance::UMyGameInstance()
{
	// 기본 값은 CDO 라는 템플릿 객체에 저장
	SchoolName = TEXT("기본 학교 이름");
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("====================================="));

	// 클래스 정보
	// 런타임 클래스 정보는 GetClass() 함수 사용
	UClass* ClassRuntime = GetClass();
	UClass* ClassCompile = UMyGameInstance::StaticClass();

	// 어서트
	// 1) check
	check(ClassRuntime == ClassCompile);
	// 2) ensure
	ensure(ClassRuntime == ClassCompile);
	ensureMsgf(ClassRuntime == ClassCompile, TEXT("일부러 발생시킨 오류"));

	// 두 타입 비교 
	FString Result = (ClassRuntime == ClassCompile) ? TEXT("같음") : TEXT("다름");

	UE_LOG(LogTemp, Log, TEXT("클래스 비교 결과: %s"), *Result);
	/*클래스 비교 결과: 같음*/

	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름: %s"), *ClassRuntime->GetName());

	// 값 출력
	SchoolName = TEXT("포텐업");
	UE_LOG(LogTemp, Log, TEXT("학교 이름: %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본값: %s"), *GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName);

	/// 출력 결과
	/*
	LogTemp: 클래스 비교 결과: 같음
	LogTemp: 학교를 담당하는 클래스 이름: MyGameInstance
	LogTemp: 학교 이름: 포텐업
	LogTemp: 학교 이름 기본값: 기본 학교 이름
	*/

	UE_LOG(LogTemp, Log, TEXT("====================================="))

	// 학생 선생님 객체 생성
	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	// 프로그래머가 정의한 GET SET 사용
	Student->SetName(TEXT("학생1"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름: %s"), *Student->GetName());

	// 언리얼 리플렉션을 통한 프로퍼티 사용
	FString CurrentTeacherName;
	FString NewTeacherName(TEXT("존카멕"));
	// Name 프로퍼티 변수 가져오기
	FProperty* NameProperty = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));

	if (NameProperty /* != nullptr*/)
	{
		NameProperty->GetValue_InContainer(Teacher, &CurrentTeacherName);

		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름: %s"), *CurrentTeacherName);

		NameProperty->SetValue_InContainer(Teacher, &NewTeacherName);

		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름: %s"), *Teacher->GetName());
	}

	/// 출력 결과
	/*
	LogTemp: 새로운 학생 이름: 학생1
	LogTemp: 현재 선생님 이름: 장세윤
	LogTemp: 새로운 선생님 이름: 존카멕
	*/

	UE_LOG(LogTemp, Log, TEXT("====================================="))

	// 함수 호출
	Student->DoLesson();
	
	// 리플렉션을 활용한 함수 간접 호출
	UFunction* DoLessionFuction = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));

	if (DoLessionFuction)
	{
		Teacher->ProcessEvent(DoLessionFuction, nullptr);
	}

	/// 출력 결과
	/*
	LogTemp: 학생1님이 수업에 참여합니다.
	LogTemp: 1학년 1번 학생1님이 수업을 듣습니다.
	LogTemp: 존카멕님이 수업에 참여합니다.
	LogTemp: 14년차 선생님이 존카멕님이 수업을 진행합니다.
	*/

	UE_LOG(LogTemp, Log, TEXT("====================================="))
}
