#pragma once

namespace rage
{
#pragma pack(push, 1)
   struct scrVector
   {
   public:
      scrVector() = default;
      scrVector(float x, float y, float z) :
         x(x), y(y), z(z)
      {}
   public:
      float x{};
      float y{};
      float z{};
   private:
      char padding[4];
   };
#pragma pack(pop)
}