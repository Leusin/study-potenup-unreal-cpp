// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include <vector>
#include <string>

void UMyGameInstance::Init()
{
	Super::Init();

	TCHAR LogCharArray[] = TEXT("Hello Unreal");
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArray);

	FString LogCharString = LogCharArray;
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);

	const TCHAR* LogCharPointer = *LogCharString;
	TCHAR* LogCharDataPointer = LogCharString.GetCharArray().GetData();
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharPointer);

	// 문자열 복사
	TCHAR LogCharArrayWithSize[100] = {};
	FCString::Strcpy(LogCharArrayWithSize, LogCharString.Len(), *LogCharString);

	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArrayWithSize);

	// 변환
	int32 IntValue = 32;
	float FloatValue = 3.141592f;

	FString FloatIntString = FString::Printf(
		TEXT("INT:%d FLOAT:%f"), IntValue, FloatValue
	);

	// FString에서 TCHAR를 가져오는 방법.
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);

	// 개별 숫자를 문자열로 변환하는 함수 활용.
	FString FloatString = FString::SanitizeFloat(FloatValue);
	FString IntString = FString::FromInt(IntValue);

	UE_LOG(
		LogTemp,
		Log,
		TEXT("FloatString: %s, IntString: %s"),
		*FloatString,
		*IntString
	);

	//
	// FName 의 특징 살펴보기
	//
	
	//FName Key1(TEXT(""));
	// FName 의 특징 살펴보기
	FName Key1(TEXT("PELVIS"));
	FName Key2(TEXT("pelvis"));

	// 비교 결과 확인
	FString Result = (Key1 == Key2) ? TEXT("같음") : TEXT("다름");
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s"), *Result)
	/**
	* 출력 결과
	* LogTemp: FName 비교 결과: 같음
	*/

	// 값이 있는지 비교
	for (int i = 0; i < 1000; ++i)
	{
		// Nmae 풀에 검색하는 과정이 있어 반복 횟수가 많은 경우 부하가 있을 수 있음
		/* const static */ FName SearchInNamePool = FName(TEXT("pelvis"));
	}
}
