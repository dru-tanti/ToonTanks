// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"


void APlayerControllerBase::SetPlayerEnableState(bool EnableState)  {
   if(EnableState) {
      GetPawn()->EnableInput(this);
   } else {
      GetPawn()->DisableInput(this);
   }

   bShowMouseCursor = EnableState;
}
