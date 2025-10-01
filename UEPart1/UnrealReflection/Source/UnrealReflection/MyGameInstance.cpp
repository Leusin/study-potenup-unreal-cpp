// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

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
	ensureMsgf(ClassRuntime != ClassCompile, TEXT("일부러 발생시킨 오류"));

	// 두 타입 비교 
	FString Result = (ClassRuntime == ClassCompile) ? TEXT("같음") : TEXT("다름");

	UE_LOG(LogTemp, Log, TEXT("클래스 비교 결과: %s"), *Result);
	/*클래스 비교 결과: 같음*/

	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름: %s"), *ClassRuntime->GetName());

	// 값 출력
	SchoolName = TEXT("포텐업");
	UE_LOG(LogTemp, Log, TEXT("학교 이름: %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본값: %s"), *GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("====================================="))
}
