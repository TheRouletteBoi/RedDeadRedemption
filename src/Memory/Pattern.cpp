#include "../Memory/Pattern.hpp"

bool DataCompare(const uint8_t* pbData, const uint8_t* pbMask, const char* szMask)
{
   for (; *szMask; ++szMask, ++pbData, ++pbMask)
   {
      if (*szMask == 'x' && *pbData != *pbMask)
      {
         return false;
      }
   }
   return (*szMask == NULL);
}

uintptr_t FindPattern(uintptr_t address, uint32_t length, uint8_t* bytes, const char* mask)
{
   for (uint32_t i = 0; i < length; i++)
      if (DataCompare((uint8_t*)(address + i), bytes, mask))
         return (uintptr_t)(address + i);

   return 0;
}

uintptr_t FindPattern(uintptr_t address, uint32_t length, uint8_t* bytes, const char* mask, int occurancesIndex)
{
    uint32_t numFound = 0;
    for (uint32_t i = 0; i < length; i++)
    {
        if (DataCompare((uint8_t*)(address + i), bytes, mask))
        {
            if (numFound == occurancesIndex)
                return (uintptr_t)(address + i);
            numFound++;
        }
    }
    return 0;
}

void FindPatternWithOccurances(uintptr_t address, uint32_t length, uint8_t* bytes, const char* mask, uintptr_t* occurances)
{
    uint32_t numFound = 0;
    const uint32_t maxOccurances = ARRAYSIZE(occurances);
    for (uint32_t i = 0; i < length; i++)
        if (DataCompare((uint8_t*)(address + i), bytes, mask))
            if (numFound < maxOccurances)
                occurances[numFound++] = (uintptr_t)(address + i);

    if (numFound == 0)
        memset(occurances, 0, maxOccurances * sizeof(uintptr_t));
}

uintptr_t FindPatternInTextSegment(uint8_t* bytes, const char* mask)
{
   uintptr_t address = FindPattern(gBaseAddress, gInfo_SizeOfImage, bytes, mask);
   if (address == 0)
      return 0;

   return address;
}

uintptr_t FindPatternInTextSegment(uint8_t* bytes, const char* mask, int occurancesIndex)
{
    uintptr_t address = FindPattern(gBaseAddress, gInfo_SizeOfImage, bytes, mask, occurancesIndex);
    if (address == 0)
        return 0;

    return address;
}

void FindPatternInTextSegmentWithOccurances(uint8_t* bytes, const char* mask, uintptr_t* occurances)
{
    FindPatternWithOccurances(gBaseAddress, gInfo_SizeOfImage, bytes, mask, occurances);
}

uint32_t ReadHighLow(uint32_t address, uint32_t highAdditive, uint32_t lowAdditive)
{
   uint32_t returnAddr = (((uint16_t)(*(uint32_t*)(address + highAdditive)) << 16) | (uint16_t)(*(uint32_t*)(address + lowAdditive)));
   uint32_t returnFinal = (returnAddr & 0x8000) ? returnAddr - 0x10000 : returnAddr;
   return returnFinal;
}

uint32_t ResolveBranch(uint32_t branchAddress)
{
   uint32_t instruction = *(uint32_t*)(branchAddress);
   int32_t offset = instruction & 0x3FFFFFC;

   if (offset & (1 << 25))
      offset |= ~0x03FFFFFF;

   return branchAddress + offset;
}