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

private:
	TArray<FStudentData> StudentsData;

	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;

	TMap<int32, FString> StudentsMap;
};
