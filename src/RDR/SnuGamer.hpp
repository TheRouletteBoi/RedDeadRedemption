#pragma once
#include <stdint.h>

class snuGamer
{
public:
   void* m_vmt; //0x0000 
   char _0x0004[20];
   uint32_t m_gamerInfo; //0x0018 
   char _0x001C[32];
   uint32_t m_localIP;     // 0x003C 
   uint64_t m_peerToken;   // 0x0040 
   uint64_t m_hostToken;   // 0x0048 
   char _0x0050[4];
   uint32_t m_publicIP;    // 0x0054 
   char _0x0058[116];
   char m_name[20];        // 0x00CC 
   char _0x00E0[520];
   uintptr_t* m_0x02E8;    // 0x02E8 
   char _0x02EC[28];
}; // Size=0x0308

class RdR2NetClient
{
public:
   void* m_vmt;            // 0x0000 
   char _0x0004[4];
   uint64_t m_peerToken;   // 0x0008 
   char _0x0010[44];
   uintptr_t* m_0x3C;      // 0x003C 
   uintptr_t* m_0x40;      // 0x0040 
   char _0x0044[28];
}; // Size=0x0060