#pragma once
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "Memory/Pattern.hpp"

class GameVariables
{
public:
   using OSKInit_t = void(*)(uintptr_t keyboardContext);
   OSKInit_t OSKInit{};

   using OSKTitle_t = void(*)(uintptr_t keyboardContext, const char* title);
   OSKTitle_t OSKTitle{};

   using OSKDescription_t = void(*)(uintptr_t keyboardContext, const char* description);
   OSKDescription_t OSKDescription{};

   using DisplayOSK_t = bool(*)(uintptr_t keyboardContext, uint32_t textView, uint32_t saveLastInput);
   DisplayOSK_t DisplayOSK{};

   using RegisterNative_t = void(*)(uint32_t nativeHash, uint32_t nativeFuntion);
   RegisterNative_t RegisterNative{};

   using ParseScrInstructions_t = uint32_t(*)(uintptr_t scriptStack, uintptr_t** globalBase, uintptr_t scrPageTable, uint32_t r6, uintptr_t scrThread);
   ParseScrInstructions_t ParseScrInstructions{};

   using GetScrProgramFromHash_t = uintptr_t(*)(uint32_t scriptHash);
   GetScrProgramFromHash_t GetScrProgramFromHash{};

   using SetVectorResults_t = void(*)(void* context);
   SetVectorResults_t RAGE_SetVectorResults{};

   using RemoteExplosionEvent_SetExplosion_t = void(*)(uintptr_t netProjectile_RemoteExplosionEvent, uintptr_t netObjectManager, uint64_t uuid);
   RemoteExplosionEvent_SetExplosion_t RemoteExplosionEvent_SetExplosion{};

   using GetSnuGamerList_t = uintptr_t(*)();
   GetSnuGamerList_t GetSnuGamerList{};

   using IsSnuGamerListValid_t = bool(*)(uintptr_t gamerList);
   IsSnuGamerListValid_t IsSnuGamerListValid{};

   using GetSagActorAddress_t = uintptr_t(*)(void* nativeContext, void* outBuf);
   GetSagActorAddress_t GetSagActorAddress{};

   using printf_t = int(*)(const char* format, ...);
   printf_t __printf{};

   using sprintf_t = int(*)(char* buffer, const char* format, ...);
   sprintf_t __sprintf{};

   using snprintf_t = int(*)(char* buffer, int size, const char* format, ...);
   snprintf_t __snprintf{};

   using vsnprintf_t = int(*)(char* s, size_t n, const char* format, va_list arg);
   vsnprintf_t __vsnprintf{};

   using sscanf_t = int(*)(const char* str, const char* format, ...);
   sscanf_t __sscanf{};

   using strncpy_t = char*(*)(char* destination, const char* source, size_t num);
   strncpy_t __strncpy{};

   using strtol_t = long int(*)(const char* str, char** endptr, int base);
   strtol_t __strtol{};

   using strtok_t = char*(*)(char* str, const char* delim);
   strtok_t __strtok{};

   using strcat_t = char*(*)(char* destination, const char* source);
   strcat_t __strcat{};

   using malloc_t = void*(*)(size_t size);
   malloc_t __malloc{};

   using rand_t = int(*)();
   rand_t __rand{};

   using exit_t = void(*)(int status);
   exit_t __exit{};

   using localtime_t = struct tm*(*)(const time_t* timer);
   localtime_t __localtime{};

   using wcslen_t = size_t(*)(const wchar_t* str);
   wcslen_t __wcslen{};

   using fopen_t = FILE*(*)(const char* filename, const char* mode);
   fopen_t __fopen{};

   using fread_t = size_t(*)(void* ptr, size_t size, size_t count, FILE* stream);
   fread_t __fread{};

   using fseek_t = int(*)(FILE* stream, long int offset, int origin);
   fseek_t __fseek{};

   using ftell_t = long int(*)(FILE* stream);
   ftell_t __ftell{};

   using fwrite_t = size_t(*)(const void* ptr, size_t size, size_t count, FILE* stream);
   fwrite_t __fwrite{};

   using fflush_t = int(*)(FILE* stream);
   fflush_t __fflush{};

   using fprintf_t = int(*)(FILE* stream, const char* format, ...);
   fprintf_t __fprintf{};

   using fclose_t = int(*)(FILE* stream);
   fclose_t __fclose{};

   bool FindSignatures();




   uintptr_t pNativeRegistration{};
   uintptr_t pRDRUIGame{};
   uintptr_t** pGlobalVars{};
   uint32_t VmOpCode44_bcctrl{};
   uint32_t pHasInfiniteHorseStamina{};
   uintptr_t pBlazingGuns{};
};

extern GameVariables* g_GameVariables;