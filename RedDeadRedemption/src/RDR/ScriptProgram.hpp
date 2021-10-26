#pragma once
#include <stdint.h>

namespace rage
{
   class scrProgram
   {
   public:
      const char* m_name;  // 0x00
      uint32_t m_hash;     // 0x04
      // TODO...
   };

   class scrPageTable
   {
   public:
      void* m_vmt;
      uintptr_t* m_0x0004;
      uintptr_t* m_0x0008;
      uint32_t m_0x000C;
      char _0x0010[4];
      uint32_t _0x0014;
      uintptr_t* m_0x018;
      uint32_t m_nameHash;       // 0x1C
      uint32_t m_0x0020;
      uint32_t* m_nativeHashes;
      char _0x0028[8];
   };
}