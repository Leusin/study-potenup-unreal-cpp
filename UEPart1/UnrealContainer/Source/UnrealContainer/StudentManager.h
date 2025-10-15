// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Forward Declaration.
class UStudent;

class UNREALCONTAINER_API FStudentManager : public FGCObject
{
public:

    // 의존성 주입 (Dependency Injection).
    FStudentManager(UStudent* InStudent) : SafeStudent(InStudent) {}

    virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
    virtual FString GetReferencerName() const override
    {
        return TEXT("FStudentManager");
    }

    const UStudent* GetStudent() const { return SafeStudent; }

private:
    UStudent* SafeStudent = nullptr;
};