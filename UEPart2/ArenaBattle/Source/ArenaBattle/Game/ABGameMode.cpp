// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "Player/ABPlayerController.h"

AABGameMode::AABGameMode()
{
	// SetDefault Pawn Class
	static ConstructorHelpers::FClassFinder<APawn> ABCharacterClassRef(TEXT("/Script/ArenaBattle.ABCharacterPlayer"));

	if (ABCharacterClassRef.Succeeded())
	{
		DefaultPawnClass = ABCharacterClassRef.Class;
	}

	// Set Player Contoller Class
	//PlayerControllerClass = AABPlayerController::StaticClass();
	//static ConstructorHelpers::FClassFinder<APawn> PlayerControllerClassRef(TEXT("/Script/ArenaBattle.ABCharacterPlayer"));

	//if (PlayerControllerClassRef.Succeeded())
	//{
	//	PlayerControllerClass = PlayerControllerClassRef.Class;
	//}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(
		TEXT("/Script/ArenaBattle.ABPlayerController")
	);
	if (PlayerControllerClassRef.Succeeded())
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
