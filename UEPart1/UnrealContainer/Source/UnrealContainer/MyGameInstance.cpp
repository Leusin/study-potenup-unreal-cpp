// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"

// 랜덤으로 이름 만드는 함수
static FString MakeRandomName()
{
	static TCHAR FirstChar[] = TEXT("김이박최");
	static TCHAR MiddkeChar[] = TEXT("가나다라");
	static TCHAR LastChar[] = TEXT("마바사아");

	// 랜덤 이름 생성
	TArray<TCHAR> RandomArray;
	RandomArray.SetNum(3);
	RandomArray[0] = FirstChar[FMath::RandRange(0, 3)];;
	RandomArray[1] = MiddkeChar[FMath::RandRange(0, 3)];;
	RandomArray[2] = LastChar[FMath::RandRange(0, 3)];;

	//생성된 이름 반환
	return RandomArray.GetData();
}


void UMyGameInstance::Init()
{
	Super::Init();

	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	// 값 채우기
	for (int32 i = 0; i <= ArrayNum; ++i)
	{
		Int32Array.Add(i);
	}

	/**
	Int32Array = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
	*/


	// 조건부 제거
	Int32Array.RemoveAll([](int32 Val) { return Val % 2 == 0; });

	/**
	Int32Array = { 1, 3, 5, 7, 9 }
	*/


	Int32Array += {2, 4, 6, 8, 10};

	/**
	Int32Array = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 }
	*/


	// 비교 배열 선언
	int32 CArray[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	TArray<int32> Int32ArrayComprare;

	// 비교 메모리의 초기 크기 지정
	Int32ArrayComprare.AddUninitialized(ArrayNum);

	// 메모리 복사
	FMemory::Memcpy(Int32ArrayComprare.GetData(), CArray, sizeof(int32) * ArrayNum);

	// 비교
	ensureAlways(Int32Array == Int32ArrayComprare);

	// 합계 구하기
	int32 Sum = 0;
	for (const int32& Item : Int32Array)
	{
		Sum += Item;
	}

	// 알고리즘 활용(합계)
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensureAlways(Int32Array == Int32ArrayComprare);

	// TSet 사용
	TSet<int32> Int32Set;
	for (int32 i = 0; i <= ArrayNum; ++i)
	{
		Int32Set.Add(ArrayNum - i);
	}

	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);


	/// 언리얼 구조체

	// 학생 데이터 생성
	const int32 StudentNum = 300;
	for (int32 i = 0; i < StudentNum; i++)
	{
		StudentsData.Emplace(FStudentData(MakeRandomName(), i));
	}

	// 학생 데이터를 TArray로 변환(Transform)
	TArray<FString> AllStudentsName;
	Algo::Transform(StudentsData, AllStudentsName,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	// 이름 몇 개인지 출력
	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수 : %d"), AllStudentsName.Num());

	/*
		LogTemp: 모든 학생 이름의 수 : 300
	*/


	/// 언리얼 TMap

	// 이름을 키로 갖는 Map 생성
	TMap<FString, int32> StudentsMapByUniqueName;
	Algo::Transform(StudentsData, StudentsMapByUniqueName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		});

	UE_LOG(LogTemp, Log, TEXT("고유한 학생 이름 수 : %d"), StudentsMapByUniqueName.Num());

	/*
		LogTemp: 고유한 학생 이름 수 : 64
	*/

	const FString TargetName(TEXT("김가마"));
	int32* Order = StudentsMapByUniqueName.Find(TargetName);

	if (Order)
	{
		UE_LOG(LogTemp, Log, TEXT("%s 이름을 가진 학생 순번 %d"), *TargetName, *Order);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s 학생 없음"), *TargetName);
	}

	/*
		LogTemp: 김가마 이름을 가진 학생 순번 193
	*/

	/// 언리얼 TMultiMap
	TMultiMap<FString, int32> StudentsMapByName;
	
	// 변환
	Algo::Transform(StudentsData, StudentsMapByName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		});

	// 검색.
	TArray<int32> AllOrders;
	StudentsMapByName.MultiFind(TargetName, AllOrders);

	// 검색된 학생 수 출력.
	UE_LOG(LogTemp, Log, TEXT("이름이 %s인 학생 수: %d"), *TargetName, AllOrders.Num());

	/*
		LogTemp: 이름이 김가마인 학생 수: 5
	*/
}
