#pragma once
#include <stdint.h>
#include <stdio.h>
#include <ppu_asm_intrinsics.h> // __ALWAYS_INLINE
#include <sys/process.h>

struct opd_s
{
   uint32_t func;
   uint32_t toc;
};

struct importStub_s
{
   int16_t ssize;
   int16_t header1;
   int16_t header2;
   int16_t imports;
   int32_t zero1;
   int32_t zero2;
   const char* name;
   uint32_t* fnid;
   opd_s** stub;
   int32_t zero3;
   int32_t zero4;
   int32_t zero5;
   int32_t zero6;
};

struct exportStub_s
{
   int16_t ssize;
   int16_t header1;
   int16_t header2;
   int16_t exports; // number of exports
   int32_t zero1;
   int32_t zero2;
   const char* name;
   uint32_t* fnid;
   opd_s** stub;
};

uint32_t GetCurrentToc();

uint32_t sys_dbg_write_process_memory(uint32_t pid, void* address, const void* data, size_t size);

uint32_t sys_hen_write_process_memory(uint32_t pid, void* address, const void* data, size_t size);

uint32_t WriteProcessMemory(uint32_t pid, void* address, const void* data, size_t size);

void PatchInBranch(uint32_t address, uint32_t destination, bool linked);

template <typename R, typename... TArgs>
__ALWAYS_INLINE R GameCall(std::uint32_t addr, TArgs... args)
{
   volatile opd_s opd = { addr, GetCurrentToc() };
   R(*func)(TArgs...) = (R(*)(TArgs...))&opd;
   return func(args...);
}