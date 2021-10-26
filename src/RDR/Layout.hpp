#pragma once
#include <stdint.h>

class gohLayout
{
public:
   void* m_vmt;                  // 0x0000 
   gohLayout* m_gohLayout;       // 0x0004 
   gohLayout* m_gohLayout2;      // 0x0008 
   char _0x000C[12];
   uintptr_t* _0x0018;           // 0x0018 
   char _0x001C[12];
   char m_layoutName[32];        // 0x0028 
   char _0x0048[4];
   uintptr_t* m_layoutType;      // 0x004C 
   char _0x0050[48];
   uintptr_t* m_gohSimplePoint;  // 0x0080 
   uintptr_t* m_gohSimplePoint2; // 0x0084 
   char _0x0088[16];
   uintptr_t* m_horseModelName;  // 0x0098 
   char _0x009C[12];
   const char* layout_name;      // 0x00A8 
   uintptr_t* _0x00AC;           // 0x00AC 
   char _0x00B0[32];
}; // Size=0x00D0