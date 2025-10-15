// Fill out your copyright notice in the Description page of Project Settings.

#include "StudentManager.h"
#include "Student.h"

void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
    // 참조 관리 오브젝트에 목록 추가.
    if (SafeStudent->IsValidLowLevel())
    {
        Collector.AddReferencedObject(SafeStudent);
    }
}