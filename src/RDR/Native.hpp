#pragma once
#include <stdint.h>
#include "../RDR/Vector.hpp"

namespace rage
{
   #pragma pack(push, 1)
   struct scrNativeCallContext
   {
   public:
      template <typename T>
      T& GetArg(std::size_t index)
      {
         return *reinterpret_cast<T*>(reinterpret_cast<std::uint32_t*>(m_Args) + index);
      }
      template <typename T>
      void SetArg(std::size_t index, T& value)
      {
         *reinterpret_cast<T*>(reinterpret_cast<std::uint32_t*>(m_Args) + index) = value;
      }
      template <typename T>
      void SetReturnValue(T& value)
      {
         *reinterpret_cast<T*>(m_Return) = value;
      }

      void* m_Return;					// 0x00
      std::uint32_t m_ArgCount;		// 0x04
      void* m_Args;						// 0x08
      std::uint32_t m_DataCount;		// 0x0C
      scrVector* m_LocalVectors[4];	// 0x10
      scrVector m_VectorResults[4];	// 0x18 expected 0x20
   };
   #pragma pack(pop)

   using scrNativeHash = uint32_t;
   using scrNativeHandler = void(*)(scrNativeCallContext*);

   #pragma pack(push, 1)
   struct scrNativeRegistration
   {
      scrNativeHash m_Hash;
      scrNativeHandler m_Handler;
   };
   #pragma pack(pop)
}


using Void = std::uint32_t;
using BOOL = std::int32_t;
using Any = std::uint32_t;
using Hash = std::uint32_t;
using Actor = std::int32_t;
using Player = std::int32_t;
using Controller = std::int32_t;
using Interior = std::int32_t;
using Ped = Actor;
using Vehicle = Actor;
using Cam = std::int32_t;
using Object = Actor;
using Layout = Object;
using Blip = std::int32_t;
using Camera = Actor;
using ScrHandle = Actor;
using Iterator = std::int32_t;
using IterationSet = std::int32_t;
using GUIWindow = std::int32_t;
using Vector3 = rage::scrVector;