// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class UNREALINTERFACE_API UStudent : public UPerson
{
	GENERATED_BODY()
	
public:
	UStudent();

private:

	UPROPERTY()
	int32 Id;
};
