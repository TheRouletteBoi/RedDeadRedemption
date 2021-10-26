#include <cellstatus.h>
#include <sys/prx.h>
#include <sys/ppu_thread.h>
#include <sys/timer.h>
#include <cell/pad.h>
#include "Util/NewDeleteOverride.hpp"
#include "Util/TimeHelpers.hpp"
#include "Game.hpp"
#include "Hooking.hpp"
#include "Invoker.hpp"
#include "Submenus.hpp"
#include "Helpers.hpp"

SYS_MODULE_INFO( RedDeadRedemption, 0, 1, 1);
SYS_MODULE_START( RedDeadRedemption_Main );
SYS_MODULE_STOP( RedDeadRedemption_Stop );


/***
* Knowns Bugs
* Model Changer gets stuck in place. Resolve by using a different native or some parameter
* 
* 
* TODO
* Add infinite text scrolling
* Add Log to file for hen users and maybe have a limit in case a 1GB file is logged 
* 
* 
* NOTES
* rdr2_layer0.rpf             contains mainly texture. I saw model objects like trees, buildings, also .dds files
* MoOutfitsPack_PS3_ult.dat   contains script files. this one contains the most scripts so far
* 
*/ 

sys_ppu_thread_t gRedDeadRedemptionThreadId = SYS_PPU_THREAD_ID_INVALID;


CDECL_BEGIN
int RedDeadRedemption_Main(int argc, char* argv[])
{
   sys_ppu_thread_create(&gRedDeadRedemptionThreadId, [](uint64_t arg)
   {
#ifdef _DEBUG
      registerNativeHk = new DetourHook(0x84F324, (uintptr_t)RegisterNativeHook);
#endif

      sleep_for(10000);

      g_GameVariables = new GameVariables();
      g_Invoker = new Invoker();
      g_Menu = Menu(MainSubmenu);
      g_Helper = Helpers();

      if (!g_GameVariables->FindSignatures())
      {
         sys_ppu_thread_exit(0);
         return;
      }

      HookingInitiate();

      g_Menu.RegisterOnMain([]
      {
         printf("Natives here will only get called once\n");
      });



      sys_ppu_thread_exit(0);

   }, 0, 3000, 8192, SYS_PPU_THREAD_CREATE_JOINABLE, "RedDeadRedemption");

   return 0;
}

int RedDeadRedemption_Stop(int argc, char* argv[])
{
   uint64_t retVal;
   sys_ppu_thread_join(gRedDeadRedemptionThreadId, &retVal);

   delete g_GameVariables;
   delete g_Invoker;
   HookingRemoveAll();

   return 0;
}
CDECL_END