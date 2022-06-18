#pragma once
#include <stdint.h>

#define CONTENT_MAIN             0x25E94D18    // content/main
#define PR_FRONTIER              0x4377FE36    // $/content/frontier/pr_frontier
#define DESIGNERDEFINED_PLAYER   0xE47D3366    // $/content/scripting/designerdefined/player

namespace rage
{
   enum class eThreadState : std::uint32_t
   {
      ThreadStateIdle,
      ThreadStateRunning,
      ThreadStateKilled,
      ThreadState3,
      ThreadState4,			// Sets opsToExecute to 1100000, and state to Idle in CallNative
   };

   class sagFullScriptContext
   {
   public:
      void* m_vmt;                        // 0x00
      char _0x04[0x14];
      uint32_t _0x18;
      uint32_t _0x1C;
      uint32_t _0x20;
      uint32_t _0x24;
      char _0x28[0xC];
      sagFullScriptContext* _0x34;
      sagFullScriptContext* _0x38;
      uint32_t _0x3C;
      sagFullScriptContext* _0x40;
      char m_name[0x28];                  // 0x44
   };

   class scrThread
   {
   public:
      void* m_vmt;                                    // 0x00
      uint32_t m_threadId;                            // 0x04
      uint32_t m_scriptHash;                          // 0x08
      eThreadState m_state;                           // 0x0C
      uint32_t m_instructionPointer;                  // 0x10
      uint32_t m_framePointer;                        // 0x14
      uint32_t m_stackPointer;                        // 0x18
      float m_timer_a;                                // 0x1C
      float m_timer_b;                                // 0x20
      float m_timer_c;                                // 0x24 WAIT timer
      char _0x28[8];
      sagFullScriptContext* m_sagFullScriptContext;   // 0x30
      char _0x34[36];
      uintptr_t* m_stack;                             // 0x58
      char _0x5C[12];
      const char* m_exitMessage;                      // 0x68
      char _0x6C[20];
   };

   namespace NoVmt
   {
      class scrThread
      {
      public:
         uint32_t m_threadId;                            // 0x00
         uint32_t m_scriptHash;                          // 0x04
         eThreadState m_state;                           // 0x08
         uint32_t m_instructionPointer;                  // 0x0C
         uint32_t m_framePointer;                        // 0x10
         uint32_t m_stackPointer;                        // 0x14
         float m_timer_a;                                // 0x18
         float m_timer_b;                                // 0x1C
         float m_timer_c;                                // 0x20 WAIT timer
         char _0x24[8];
         sagFullScriptContext* m_sagFullScriptContext;   // 0x2C
         char _0x30[36];
         uintptr_t* m_stack;                             // 0x54
         char _0x58[12];
         const char* m_exitMessage;                      // 0x64
         char _0x68[20];
      };
   }
}