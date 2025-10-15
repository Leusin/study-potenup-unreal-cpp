// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

// 구조체 선언
USTRUCT(Atomic, BlueprintType/*,NoExport*/)
struct FStudentData
{
	GENERATED_BODY()

	FStudentData()
		: Name(TEXT("김주영")), Order(-1)
	{

	}

	FStudentData(const FString& InName, int32 InOrder)
		: Name(InName), Order(InOrder)
	{

	}

	// TSet 구조체를 위한 ==(동등 비교 연산자) 함수
	// 이항 연산자이기 때문에 피연산자 2개 필요로. 
	// friend 키워드가 없다면 피연산자를 자신 타입으로 암묵적 판단 
	bool operator==(const FStudentData& InOther) const
	{
		return Order == InOther.Order;
	}

	friend FORCEINLINE int32 GetTypeHash(const FStudentData& InStudentData)
	{
		//return GetTypeHash(InStudentData.Order);
		return GetTypeHash(InStudentData.Name);
	}

public:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;
};

/**
 * 
 */
UCLASS()
class UNREALCONTAINER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	virtual void Shutdown() override;

private:

	TObjectPtr<class UStudent> NonPropStudent;

	UPROPERTY()
	TObjectPtr<class UStudent> PropStudent;

	TArray<TObjectPtr<class UStudent>> NonPropStudents;

	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> PropStudents;

	// 일반 클래스
	class FStudentManager* StudentManager = nullptr;

	//TArray<FStudentData> StudentsData;

	//UPROPERTY()
	//TArray<TObjectPtr<class UStudent>> Students;

	//TMap<int32, FString> StudentsMap;
};
