#include "Game.hpp"

GameVariables* g_GameVariables;

template <typename T>
void SetPat(const char* name, const char* pattern, const char* mask, T* out, 
   int32_t relativeOffset = 0x00,
   bool getFromHighLow = false, int32_t highAdditive = 0x00, int32_t lowAdditive = 0x00)
{
   uintptr_t ptr = FindPatternInTextSegment((uint8_t*)pattern, mask);
   if (ptr == 0)
   {
      printf("Failed to find %s pattern.\n", name);
      *out = 0;
      return;
   }

   ptr = ptr + relativeOffset;

   if (getFromHighLow)
      ptr = ReadHighLow(ptr, highAdditive, lowAdditive);

   printf("found ptr %s at 0x%X\n", name, ptr);

   *out = (T)ptr;
}

template <typename T>
void SetFn(const char* name, const char* pattern, const char* mask, T* out, 
   int32_t relativeOffset = 0x00, bool resolveBranch = false)
{
   uintptr_t ptr = FindPatternInTextSegment((uint8_t*)pattern, mask);
   if (ptr == 0)
   {
      printf("Failed to find %s pattern.\n", name);
      *out = nullptr;
      return;
   }

   static uint32_t opd[2]{};

   ptr = ptr + relativeOffset;

   if (resolveBranch)
      opd[0] = ResolveBranch(ptr);
   else
      opd[0] = ptr;

   opd[1] = GetCurrentToc();

   printf("found func %s at 0x%X\n", name, opd[0]);

   *out = (T)opd;
}

bool GameVariables::FindSignatures()
{
   // Signatures are from 1.01 update PS3   BLES01294-[Red Dead Redemption Game Of The Year]

   SetPat<uintptr_t>("NativeRegistration",
      "\xF8\x21\x00\x00\x60\x64\x00\x00\x38\xA0\x00\x00\x38\xC0\x00\x00", "xx??xx??xx??xx??",
      &pNativeRegistration,
      0x00,
      true, 0x34, 0x3C);

   SetFn<OSKInit_t>("OSKInit",
      "\x3C\x80\x00\x00\x38\xA0\x00\x00\x80\xC4\x00\x00\x90\xC3\x00\x00\x80\x84\x00\x00\xB0\xA3\x00\x00", "xx??xx??xx??xx??xx??xx??",
      &OSKInit);

   SetFn<OSKTitle_t>("OSKTitle",
      "\x80\xBD\x00\x00\x63\xA3\x00\x00\x38\x80\x00\x00\x80\xA5\x00\x00\x80\xA5\x00\x00\x7C\xA9\x03\xA6\x4E\x9E\x04\x21\x60\x7D\x00\x00\x2C\x1D\x00\x00\x41\x00\x00\x00\x2C\x1D\x00\x00\x40\x00\x00\x00\x3C\x80\x00\x00\x63\xC3\x00\x00\x30\x84\x00\x00", "xx??xx??xx??xx??xx??xxxxxxxxxx??xx??x???xx??x???xx??xx??xx??",
      &OSKTitle,
      0x3C, true);

   SetFn<OSKDescription_t>("OSKDescription",
      "\x80\xBD\x00\x00\x63\xA3\x00\x00\x38\x80\x00\x00\x80\xA5\x00\x00\x80\xA5\x00\x00\x7C\xA9\x03\xA6\x4E\x9E\x04\x21\x60\x7D\x00\x00\x2C\x1D\x00\x00\x41\x00\x00\x00\x2C\x1D\x00\x00\x40\x00\x00\x00\x3C\x80\x00\x00\x63\xC3\x00\x00\x30\x84\x00\x00", "xx??xx??xx??xx??xx??xxxxxxxxxx??xx??x???xx??x???xx??xx??xx??",
      &OSKDescription,
      0x4C, true);

   SetFn<DisplayOSK_t>("DisplayOSK",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\xF8\x01\x00\x00\xFB\xC1\x00\x00\xFB\xE1\x00\x00\x60\x7E\x00\x00\x60\x9F\x00\x00\x60\xA3\x00\x00\x88\x9E\x00\x00", "xx??xxxxxx??xx??xx??xx??xx??xx??xx??",
      &DisplayOSK);

   SetPat<uintptr_t>("pRDRUIGame",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\xF8\x01\x00\x00\xFB\xE1\x00\x00\x7C\x9F\x07\x74", "xx??xxxxxx??xx??xxxx",
      &pRDRUIGame,
      0x00,
      true, 0x20, 0x24);

   SetPat<uintptr_t**>("pGlobalVars",
      "\x7C\x63\x07\xB4\x4B\x00\x00\x00\x3C\x80\x00\x00\x80\xA3\x00\x08\x80\xC3\x00\x10\x30\xFF\x00\x04\x80\x7F\x00\x58", "xxxxx???xx??xx?xxx?xxx?xxx?x",
      &pGlobalVars,
      0x00,
      true, 0x8, 0x1C);

   SetFn<RegisterNative_t>("RegisterNative",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\xF8\x01\x00\x00\xFB\x61\x00\x00\x28\x03\x00\x00", "xx??xxxxxx??xx??xx??",
      &RegisterNative);

   SetPat<uint32_t>("VmOpCode44_NativeCall",
      "\x90\xA1\x00\x00\x92\x01\x00\x00\x80\x86\x00\x00\x7C\x89\x03\xA6\x4E\x9E\x04\x21", "xx??xx??xx??xxxxxxxx",
      &VmOpCode44_bcctrl,
      0x10);

   SetFn<ParseScrInstructions_t>("ParseScrInstructions",
      "\x30\xFF\x00\x00\x80\x7F\x00\x00\x80\x84\x00\x00\x48\x00\x00\x00", "xx??xx??xx??x???",
      &ParseScrInstructions,
      0xC, true);

   SetFn<GetScrProgramFromHash_t>("GetScrProgramFromHash",
      "\x80\x7F\x00\x00\x93\xFD\x00\x00\x7C\x63\x07\xB4\x4B\x00\x00\x00", "xx??xx??xxxxx???",
      &GetScrProgramFromHash,
      0xC, true);

   SetFn<SetVectorResults_t>("RAGE_SetVectorResults",
      "\x88\x6E\x00\x00\x7C\x9A\xC8\x10\x33\x9C\x00\x03\x54\x63\x10\x3A\x78\x84\x17\x64\x7F\xC4\xF0\x10", "xx??xxxxxx?xxxxxxxxxxxxx",
      &RAGE_SetVectorResults,
      -0x4, true);

   SetPat<uint32_t>("pHasInfiniteHorseStamina",
      "\x3C\x80\x00\x00\x3C\xC0\x00\x00\xFF\xE0\x10\x90\xFB\xE1\x00\x00", "xx??xx??xxxxxx??",
      &pHasInfiniteHorseStamina,
      0x00,
      true, 0x4, 0x20);

   SetPat<uintptr_t>("pBlazingGuns",
      "\x7C\x1D\xD8\x00\x60\x9A\x00\x00\x90\xFF\x00\x00\xFB\xC1\x00\x00\x60\x83\x00\x00\x40\x00\x00\x00", "xxx?xx??xx??xx??xx??x???",
      &pBlazingGuns,
      0x00,
      true, 0x18, 0x1C);

   SetFn<RemoteExplosionEvent_SetExplosion_t>("RemoteExplosionEvent_SetExplosion",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\xF8\x01\x00\x00\xFB\xC1\x00\x00\x60\x7E\x00\x00\x60\x83\x00\x00\xFB\xE1\x00\x00\xFB\xA1\x00\x88\xFB\x81\x00\x00\x80\x9E\x00\x00", "xx??xxxxxx??xx??xx??xx??xx??xx?xxx??xx??",
      &RemoteExplosionEvent_SetExplosion);

   SetFn<GetSnuGamerList_t>("GetSnuGamerList",
      "\x10\x40\x03\x8C\xFB\xC1\x00\x00\x60\x9F\x00\x00\x60\x7E\x00\x00\xFB\xA1\x00\x00\x7C\x40\xF9\xCE\x4B\x00\x00\x00", "xxxxxx??xx??xx??xx??xxxxx???",
      &GetSnuGamerList,
      0x18, true);

   SetFn<IsSnuGamerListValid_t>("IsSnuGamerListValid",
      "\x10\x40\x03\x8C\xFB\xC1\x00\x00\x60\x9F\x00\x00\x60\x7E\x00\x00\xFB\xA1\x00\x00\x7C\x40\xF9\xCE\x4B\x00\x00\x00", "xxxxxx??xx??xx??xx??xxxxx???",
      &IsSnuGamerListValid,
      0x2C, true);

   // has 2 occurrences but it is the first one
   SetFn<GetSagActorAddress_t>("GetSagActorAddress",
      "\x60\x65\x00\x00\x80\xC4\x00\x00\x38\x60\x00\x00\x54\xC7\x00\x00\x30\xC6\x00\x00\x80\xA5\x00\x00", "xx??xx??xx??xx??xx??xx??",
      &GetSagActorAddress);

   SetFn<printf_t>("printf",
      "\xFB\xA1\x00\x00\xF8\x01\x00\x00\x7C\x7D\x1B\x78\x38\x01\x00\x00", "xx??xx??xxxxxx??",
      &__printf,
      -0x10);

   SetFn<sprintf_t>("sprintf",
      "\x60\x65\x00\x00\x30\x61\x00\x00\x63\xE6\x00\x00", "xx??xx??xx??",
      &__sprintf,
      0xC, true);

   SetFn<snprintf_t>("snprintf",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\x2F\x84\x00\x00", "xx??xxxxxx??",
      &__snprintf);

   SetFn<vsnprintf_t>("vsnprintf",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\xFA\xC1\x00\x00\x3A\xC1\x00\x00", "xx??xxxxxx??xx??",
      &__vsnprintf);

   SetFn<sscanf_t>("sscanf",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\x39\x61\x00\x00", "xx??xxxxxx??",
      &__sscanf);

   SetFn<strncpy_t>("strncpy",
      "\x7C\x69\x23\x78\x7C\x87\x23\x78", "xxxxxxxx",
      &__strncpy);

   SetFn<strtol_t>("strtol",
      "\x7D\x80\x00\x26\x2E\x06\x00\x00\xF8\x21\x00\x00\xF9\xE1\x00\x00", "xxxxxx??xx??xx??",
      &__strtol,
      -0x8);

   SetFn<strtok_t>("strtok",
      "\x2C\x23\x00\x00\x7C\x08\x02\xA6\x3D\x2D\x00\x00", "xx??xxxxxx??",
      &__strtok);

   // has 2 occurrences but it is the first one
   SetFn<strcat_t>("strcat",
      "\x78\x67\x00\x20\x54\x63\x00\x38\x78\xE0\x07\x60\x2F\xA0\x00\x00\x41\x9E\x00\x90", "xxxxxxxxxxxxxx??xxxx",
      &__strcat);

   // has 2 occurrences but it is the first one
   SetFn<malloc_t>("malloc",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\xF8\x01\x00\x00\x60\x64\x00\x00\x80\x6D\x00\x00\x38\xA0\x00\x00\x38\xC0\x00\x00\x80\xE3\x00\x00", "xx??xxxxxx??xx??xx??xx??xx??xx??",
      &__malloc);

   SetFn<rand_t>("rand",
      "\x3C\xED\x00\x00\x39\x27\x00\x00", "xx??xx??",
      &__rand);

   SetFn<exit_t>("exit",
      "\x7F\x84\x28\x40\x38\x60\x00\x00\x40\x9C\x00\x08", "xxxxxx??xxxx",
      &__exit,
      -0x14);

   SetFn<localtime_t>("localtime",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\xFB\x81\x00\x00\xFB\xA1\x00\x00\x7C\x7C\x1B\x78", "xx??xxxxxx??xx??xxxx",
      &__localtime);

   SetFn<wcslen_t>("wcslen",
      "\xA0\x03\x00\x00\x39\x60\x00\x00\x7C\x69\x1B\x78", "xx??xx??xxxx",
      &__wcslen);

   SetFn<fopen_t>("fopen",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\xFB\x81\x00\x00\x7C\x7C\x1B\x78", "xx??xxxxxx??xxxx",
      &__fopen);

   SetFn<fread_t>("fread",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\xFB\x21\x00\x00\xFB\x01\x00\x00", "xx??xxxxxx??xx??",
      &__fread);

   SetFn<fseek_t>("fseek",
      "\x63\xC3\x00\x00\x38\x80\x00\x00\x38\xA0\x00\x02", "xx??xx??xx?x",
      &__fseek,
      0xC, true);

   SetFn<ftell_t>("ftell",
      "\x38\xA0\x00\x02\x48\x00\x00\x00\x63\xC3\x00\x00", "xx?xx???xx??",
      &__ftell,
      0xC, true);

   SetFn<fwrite_t>("fwrite",
      "\xF8\x21\x00\x00\x7C\x08\x02\xA6\xFA\xC1\x00\x00\xFA\xE1\x00\x00", "xx??xxxxxx??xx??",
      &__fwrite);

   SetFn<fflush_t>("fflush",
      "\x2F\x83\x00\x00\x7C\x08\x02\xA6\xF8\x21\x00\x00\xFB\xC1\x00\x00\xFB\xA1\x00\x00", "xx??xxxxxx??xx??xx??",
      &__fflush);

   SetFn<fprintf_t>("fprintf",
      "\xFB\x81\x00\x00\xFB\xA1\x00\x00\x7C\x9C\x23\x78", "xx??xx??xxxx",
      &__fprintf,
      -0x10);

   SetFn<fclose_t>("fclose",
      "\xF8\x01\x00\x00\xA0\x03\x00\x00\x78\x7C\x00\x20", "xx??xx??xxxx",
      &__fclose,
      -0xC);

   bool found = pNativeRegistration
      && pRDRUIGame
      && RegisterNative
      && ParseScrInstructions
      && GetScrProgramFromHash
      && pGlobalVars
      && GetSnuGamerList
      && __printf
      && __sprintf
      && __snprintf;

   return found;
}