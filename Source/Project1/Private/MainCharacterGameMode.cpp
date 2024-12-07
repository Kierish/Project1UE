// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterGameMode.h"
#include "MainCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMainCharacterGameMode::AMainCharacterGameMode() : Super()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/MainCharacter/Blueprints/BP_MainCharacter"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;
}
