// Fill out your copyright notice in the Description page of Project Settings.


#include "ABFountain.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
AABFountain::AABFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ---
	// 컴포넌트 생성
	// ---
	/* 복습:
	UObject 는 서브 오브젝트를 가질 수 있으며 두 가지 방법이 있다.
	- 필수 포함: CDO에 언리얼 오브젝트를 CreateDefaultSubobject()로 생성
	- 선택 포함: CDO에 빈 포인터만 넣고 언리얼 오브젝트를 NewObject()로 생성
	*/
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));

	// ---
	// 컴포넌트 계층 구조 설정
	// ---
	/*
	 Body
		└ Water
		└ Light
	*/
	RootComponent = Body;
	Water->SetupAttachment(Body);
	Light->SetupAttachment(Body);

	// ---
	// 에셋 지정
	// ---
	//Body
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FountainBodyMesh(TEXT("/Game/ArenaBattle/Environment/Props/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	if (FountainBodyMesh.Succeeded())
	{
		Body->SetStaticMesh(FountainBodyMesh.Object);
	}
	// Water
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FountainWatherMesh(TEXT("/Game/ArenaBattle/Environment/Props/SM_Plains_Fountain_02.SM_Plains_Fountain_02"));
	if (FountainWatherMesh.Succeeded())
	{
		Water->SetStaticMesh(FountainWatherMesh.Object);
	}

	// ---
	// 기타 개별 옵션
	// ---
	// Wather 상대 위치 설정
	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 140.0f));
	// Light
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	Light->SetAttenuationRadius(250.0f);
}

// Called when the game starts or when spawned
void AABFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

