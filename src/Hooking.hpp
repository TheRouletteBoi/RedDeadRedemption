#pragma once
#include "Util/Exports.hpp"
#include "Memory/DetourHook.hpp"
#include "RDR/ScriptThread.hpp"
#include "RDR/ScriptProgram.hpp"
#include "Game.hpp"
#include "Invoker.hpp"
#include "Menu.hpp"
#include "Helpers.hpp"

#ifdef _DEBUG
extern Detour* registerNativeHk;
/***
 * Dump all Natives Hashes
 * NOTE: hook must be called on startup because that's when the game registers the natives
 */
void RegisterNativeHook(uint32_t nativeHash, uint32_t nativeFunctionOpd);
#endif


void HookingInitiate();
void HookingRemoveAll();