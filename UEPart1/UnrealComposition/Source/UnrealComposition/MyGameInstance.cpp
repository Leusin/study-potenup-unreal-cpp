// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"

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
		// 구성원이 소유한 카드 가져오기
		const UCard* OwnCard = Person->GetCard();
		check(OwnCard);

		// 카드 정보 출력
		//UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드: %d. "), *Person->GetName(), OwnCard->GetCardType())

		// 열거형 문자열 출력
		// 열거형 정보 가져오기
		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/UnrealComposition.ECardType"));
		/**
		* /Engine == 설치된 엔진 경로
		* /Game == 프로젝트 경로/Content/
		* /Script == 프로젝트 경로/Script/
		*/

		if (CardEnumType)
		{
			// DisplayName 가벼오기
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)OwnCard->GetCardType()).ToString();

			UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드: %s"), *Person->GetName(), *CardMetaData);
		}
	}

	/// 출력 결과
	/*
	LogTemp: 김주영님이 소유한 카드: For Student
	LogTemp: 장세윤님이 소유한 카드: For Techer
	LogTemp: 김직원님이 소유한 카드: For Staff
	*/

	UE_LOG(LogTemp, Log, TEXT("====================================="))
}
