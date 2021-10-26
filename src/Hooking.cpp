#include "Hooking.hpp"

#ifdef _DEBUG
DetourHook* registerNativeHk;
void RegisterNativeHook(uint32_t nativeHash, uint32_t nativeFunctionOpd)
{
   printf("Function Hash = 0x%08X, Function Opd = 0x%08X\n", nativeHash, nativeFunctionOpd);

   registerNativeHk->GetOriginal<void>(nativeHash, nativeFunctionOpd);
}

void VmOpCode44_NativeCallHook(NativeContext* context, uintptr_t funcAddr)
{
   rage::NoVmt::scrThread* thrd = reinterpret_cast<rage::NoVmt::scrThread*>(static_cast<uintptr_t>(__reg(17)));
   rage::scrProgram* pro = reinterpret_cast<rage::scrProgram*>(g_GameVariables->GetScrProgramFromHash(thrd->m_scriptHash));
   rage::scrPageTable* page = reinterpret_cast<rage::scrPageTable*>(static_cast<uintptr_t>(__reg(19)));

   printf("NATIVE WATCHER\n");
   //printf("%s called { 0x%08X at 0x%X }\n", pro->m_name, page->m_nativeHashes[NativeOffset], page->m_pageLocation[PageOffset]);
   printf("0x%X has %d params %d are *out params\n", funcAddr, context->m_ArgCount, context->m_DataCount);

   GameCall<void>(funcAddr, context);
}
#endif

DetourHook* parseScrInstructionsHk;
int g_coreTimer{};
uint32_t ParseScrInstructionsHook(uintptr_t scriptStack, uintptr_t** globalBase, uintptr_t scrPageTable, uint32_t r6, rage::NoVmt::scrThread* scrThread)
{
#ifdef _DEBUG
   rage::scrProgram* program = (rage::scrProgram*)g_GameVariables->GetScrProgramFromHash(scrThread->m_scriptHash);
   printf("name %s > hash 0x%08X > state %d\n", program->m_name, scrThread->m_scriptHash, scrThread->m_state);
#endif

   if (scrThread->m_scriptHash == PR_FRONTIER
      && scrThread->m_state == rage::eThreadState::ThreadStateRunning)
   {
      //if (g_coreTimer + 1 < HUD::HUD_TIMER_GET())
      //{
         g_Menu.OnGameTick();
         g_Helper.Update();

      //   g_coreTimer = HUD::HUD_TIMER_GET();
      //}
   }

   return parseScrInstructionsHk->GetOriginal<uint32_t>(scriptStack, globalBase, scrPageTable, r6, scrThread);
}

DetourHook* remoteExplosionEvent_SetExplosionHk;
void RemoteExplosionEvent_SetExplosionHook(uintptr_t netProjectile_RemoteExplosionEvent, uintptr_t netObjectManager, uint64_t uuid)
{
   if (g_Helper.m_ExplosionProtection)
      return;

   remoteExplosionEvent_SetExplosionHk->GetOriginal<void>(netProjectile_RemoteExplosionEvent, netObjectManager, uuid);
}

void HookingInitiate()
{
#ifdef _DEBUG
   PatchInBranch(g_GameVariables->VmOpCode44_bcctrl, *(uint32_t*)(VmOpCode44_NativeCallHook), true);
#endif

   parseScrInstructionsHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->ParseScrInstructions),
      (uintptr_t)ParseScrInstructionsHook);

   remoteExplosionEvent_SetExplosionHk = new DetourHook(
      *(uint32_t*)(g_GameVariables->RemoteExplosionEvent_SetExplosion), 
      (uintptr_t)RemoteExplosionEvent_SetExplosionHook);
}

void HookingRemoveAll()
{
#ifdef _DEBUG
   delete registerNativeHk;
#endif
   delete parseScrInstructionsHk;
   delete remoteExplosionEvent_SetExplosionHk;
}