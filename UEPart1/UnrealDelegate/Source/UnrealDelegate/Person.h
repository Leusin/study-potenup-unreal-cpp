// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LessonInterface.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UPerson : public UObject, public ILessonInterface
{
	GENERATED_BODY()
	
public:
	UPerson();

	virtual void DoLesson() override;

	FORCEINLINE const FString& GetName() const { return Name; };
	FORCEINLINE void SetName(const FString& InName) { Name = InName; };

protected:
	
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;

private:
};
