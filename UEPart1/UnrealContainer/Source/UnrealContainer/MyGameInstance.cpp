// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h"

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
	int32 CArray[]  = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
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

}
