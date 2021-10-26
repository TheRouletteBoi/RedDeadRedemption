#include "NativeMemory.hpp"

namespace NativeMemory
{
   bool HasInfiniteHorseStamina()
   {
      return *(bool*)(g_GameVariables->pHasInfiniteHorseStamina);
   }

   bool HasBlazingGuns()
   {
      return *(bool*)(g_GameVariables->pBlazingGuns + 0x5340);
   }

   bool IsValidPlayer(uint8_t index)
   {
      return (index != 0xFF) && (index < MAX_PLAYERS);
   }

   snuGamer* GetSnuGamerFromPlayerIndex(uint8_t index)
   {
      snuGamer* gamer = nullptr;

      uintptr_t gamerList = g_GameVariables->GetSnuGamerList();
      if (!gamerList || !g_GameVariables->IsSnuGamerListValid(gamerList))
         return nullptr;

      if (IsValidPlayer(index))
         gamer = *(snuGamer**)(gamerList + 0x18 * index + 0x10);

      return gamer;
   }

   uintptr_t GetGamerInfoFromPlayerIndex(uint8_t index)
   {
      uintptr_t gamerList = g_GameVariables->GetSnuGamerList();
      if (!gamerList || !g_GameVariables->IsSnuGamerListValid(gamerList))
         return 0;

      snuGamer* gamer = nullptr;
      if (IsValidPlayer(index))
         gamer = *(snuGamer**)(gamerList + 0x18 * index + 0x10);

      if (gamer)
         return reinterpret_cast<uintptr_t>(gamer + 0x18);

      return 0;
   }

   sagActor* GetActorAddress(int32_t actor)
   {
      NativeContext cxt;
      cxt.Push(actor);

      uint32_t r4[4]{};
      r4[0] = 0; // 0 or 1 depending on the native
      return (sagActor*)g_GameVariables->GetSagActorAddress(&cxt, &r4);
   }

}