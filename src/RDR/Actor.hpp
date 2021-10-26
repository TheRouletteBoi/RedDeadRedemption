#pragma once
#include <stdint.h>

class actorType
{
public:
   void* m_vmt;               // 0x0000 
   char _0x0004[4];
   uintptr_t* _0x0008;        // 0x0008 
   char _0x000C[68];
   uintptr_t* m_templateName; // 0x0050 
   char _0x0054[140];
}; // Size=0x00E0

class sagActor
{
public:
   void* m_vmt; // 0x0000 
   char _0x0004[4];
   actorType* m_actorType; // 0x0008 
   char _0x000C[16];
   uintptr_t* m_animAnimatorComponent; // 0x001C 
   uintptr_t* m_bhBehaviorComponent; // 0x0020 
   char _0x0024[4];
   uintptr_t* m_entEntityComponent; // 0x0028 
   char _0x002C[4];
   uintptr_t* m_mvrMoverSimComponent; // 0x0030 
   char _0x0034[4];
   uintptr_t* m_invInventoryComponent; // 0x0038 
   uintptr_t* m_motCapabilitiesComponent; // 0x003C 
   char _0x0040[4];
   uintptr_t* m_mvrMoverSimComponent2; // 0x0044 
   uintptr_t* m_netActorComponent; // 0x0048 
   uintptr_t* m_bipedIKComponent; // 0x004C 
   char _0x0050[4];
   uintptr_t* m_secondaryMotionComponent; // 0x0054 
   uintptr_t* m_sagCreatureComponent; // 0x0058 
   uintptr_t* m_tgtReticleComponent; // 0x005C 
   uintptr_t* m_tgtTargetComponent; // 0x0060 
   uintptr_t* m_sagCreatureAudioComponent; // 0x0064 
   char _0x0068[4];
   uintptr_t m_sagCameraComponent; // 0x006C 
   char _0x0070[12];
   sagActor* m_sagActor; //0x007C 
   char _0x0080[4];
   sagActor* m_sagActor2; //0x0084 
   char _0x0088[16];
   uint8_t m_playerFlag; //0x0098 
   uint8_t m_0x99; //0x0099 
   uint8_t m_0x9A; //0x009A 
   uint8_t m_0x9B; //0x009B 
   char _0x009C[92];
   uintptr_t* m_sagLayout; //0x00F8 
   char _0x00FC[100];
}; // Size=0x0160