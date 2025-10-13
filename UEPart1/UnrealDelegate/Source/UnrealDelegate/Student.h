// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UStudent : public UPerson
{
	GENERATED_BODY()
	
public:
	UStudent();

	virtual void DoLesson() override;

	void GetNotification(const FString& InSchoolName, const FString& InInformation);

private:

	UPROPERTY()
	int32 Id;
};
