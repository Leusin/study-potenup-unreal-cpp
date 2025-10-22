// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// 입력
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "ABCharacterControlData.h"

AABCharacterPlayer::AABCharacterPlayer()
{
	// ---
	// 기본 컴포넌트 설정
	// ---
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;

	// 메시 컴포넌트 설정.
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	
	// 애셋 지정.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Barbarous.SK_CharM_Barbarous"));
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CharaterAnim(TEXT("/Game/ArenaBattle/Animation/ABP_ABCharacter.ABP_ABCharacter_C"));
	if (CharaterAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(CharaterAnim.Class);
	}

	// ---
	// 컴포넌트 생성
	// --- 
	SprintArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// ---
	// 계층 구조 설정
	// ---
	/*
	SprintArm
	 └ Camera
	*/

	// Root
	SprintArm->SetupAttachment(RootComponent);
	// Scnene
	Camera->SetupAttachment(SprintArm);

	// ---
	// 컴포넌트 기타 세부 설정
	// ---
	SprintArm->TargetArmLength = 500.0f;
	SprintArm->bUsePawnControlRotation = true;


	// ---
	// 입력 설정
	// ---
	
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Game/ArenaBattle/Input/Actions/IA_ShoulderMove.IA_ShoulderMove"));
	if (MoveActionRef.Succeeded())
	{
		ShoulderMoveAction = MoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Game/ArenaBattle/Input/Actions/IA_ShoulderLook.IA_ShoulderLook"));
	if (LookActionRef.Succeeded())
	{
		ShoulderLookAction = LookActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> QuaterMoveActionRef(TEXT("/Game/ArenaBattle/Input/Actions/IA_QuaterMove.IA_QuaterMove"));
	if (QuaterMoveActionRef.Succeeded())
	{
		QuaterMoveAction = QuaterMoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Game/ArenaBattle/Input/Actions/IA_Jump.IA_Jump"));
	if (JumpActionRef.Succeeded())
	{
		JumpAction = JumpActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ChangeControlActionRef(TEXT("/Game/ArenaBattle/Input/Actions/IA_ChangeControl.IA_ChangeControl"));
	if (ChangeControlActionRef.Succeeded())
	{
		ChangeControlAction = ChangeControlActionRef.Object;
	}

	// 초기 캐릭터 컨트롤 타입 설정
	CurrentCharacterControlType = ECharacterControlType::Shoulder;
}

void AABCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	// 초기 입력 컨트롤 설정
	SetCharacterControl(CurrentCharacterControlType);
}

// 플레이어에 의해 소유당할 때 호출되는 함수
void AABCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 향상된 입력 시스템을 처리하는 컴포넌트로 형 변환
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		// 바인딩
		EnhancedInputComponent->BindAction(ShoulderMoveAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ShoulderMove);
		EnhancedInputComponent->BindAction(ShoulderLookAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::ShoulderLook);
		EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &AABCharacterPlayer::QuaterMove);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AABCharacterPlayer::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AABCharacterPlayer::StopJumping);

		EnhancedInputComponent->BindAction(ChangeControlAction, ETriggerEvent::Started, this, &AABCharacterPlayer::ChangeCharacterControl);
	}
}

void AABCharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)
{
	// 변경할 컨트롤 데이터 에셋 로드
	UABCharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];
	check(NewCharacterControl);

	// 데이터 에셋을 전달해 함수 호출
	SetCharacterControlData(NewCharacterControl);

	// 입력 매핑 컨텍스트 관련 처리
	
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
		}
	}

	// 열거형 값 없데이트
	CurrentCharacterControlType = NewCharacterControlType;
}

void AABCharacterPlayer::SetCharacterControlData(const UABCharacterControlData* InCharacterControlData)
{
	Super::SetCharacterControlData(InCharacterControlData);

	SprintArm->TargetArmLength = InCharacterControlData->TargetArmLength;
	SprintArm->SetRelativeRotation(InCharacterControlData->RelativeRotation);
	SprintArm->bDoCollisionTest = InCharacterControlData->bDoCollisionTest;
	SprintArm->bUsePawnControlRotation = InCharacterControlData->bUsePawnControlRotation;
	SprintArm->bInheritPitch = InCharacterControlData->bInheritPitch;
	SprintArm->bInheritYaw = InCharacterControlData->bInheritYaw;
	SprintArm->bInheritRoll = InCharacterControlData->bInheritRoll;
	
}

void AABCharacterPlayer::ChangeCharacterControl()
{
	if (CurrentCharacterControlType == ECharacterControlType::Quater)
	{
		SetCharacterControl(ECharacterControlType::Shoulder);
	}
	else if (CurrentCharacterControlType == ECharacterControlType::Shoulder)
	{
		SetCharacterControl(ECharacterControlType::Quater);
	}
	else
	{
		// 예외처리하면 좋음. 근데 여기까지 올 일 없음
	}
}

void AABCharacterPlayer::ShoulderMove(const FInputActionValue& Value)
{
	// 입력 값 읽어오기
	FVector2D Movement = Value.Get<FVector2D>();

	UE_LOG(LogTemp, Log, TEXT("Move: %s"), *Movement.ToString());

	// 이동할 방향 만들기
	// 카메라가 바라보는 방향(컨트롤러 방향)을 기준으로 이동 방향 만들기
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	// 앞
	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// 우
	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 무부먼트에 입력 전달하기
	// 크기 1인 숫자를 곱하는 행위는 회전(방향 벡터)
	AddMovementInput(ForwardVector, Movement.Y);
	AddMovementInput(RightVector, Movement.X);
}

void AABCharacterPlayer::ShoulderLook(const FInputActionValue& Value)
{
	// 입력값 읽어오기
	FVector2D LookValue = Value.Get<FVector2D>();

	// 컨트롤러에 회전 적용
	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(-LookValue.Y);

}

void AABCharacterPlayer::QuaterMove(const FInputActionValue& Value)
{
	// 입력 값 읽어오기
	FVector2D Movement = Value.Get<FVector2D>();

	// 입력 값을 사용해 이동 방향 만들기
	FVector MoveDirection(Movement.Y, Movement.X, 0.0f);

	// 입력 크기
	float MovementVectorSizeSquared = FMath::Min(1.0f, Movement.Size());

	// 이동 단위 벡터 만들기
	MoveDirection.Normalize();

	// 캐릭터가 이용하는 방향에 맞게 컨트롤러 회전 설정
	Controller->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator());

	// 이동 적용
	AddMovementInput(MoveDirection, MovementVectorSizeSquared);
}
