#pragma once
#include "RDR/SnuGamer.hpp"
#include "RDR/Enums.hpp"
#include "RDR/Actor.hpp"
#include "Invoker.hpp"
#include "Game.hpp"


namespace NativeMemory
{
   bool IsValidPlayer(uint8_t index);
   snuGamer* GetSnuGamerFromPlayerIndex(uint8_t index);
   uintptr_t GetGamerInfoFromPlayerIndex(uint8_t index);
   sagActor* GetActorAddress(int32_t actor);

   bool HasInfiniteHorseStamina();
   bool HasBlazingGuns();
}