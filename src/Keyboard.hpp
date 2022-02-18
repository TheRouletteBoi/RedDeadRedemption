#pragma once
#include <string>
#include "Game.hpp"

class Keyboard
{
public:
   enum Status { Unk = 0, Active = 1, Canceled = 2, NotActive = 3 };
public:
   bool Display(const char* title, const char* description, int maxLength)
   {
      if (IsRunning())
      {
         // attempt to modify the max length 
         // int len =  + maxLength;
         // *(uint32_t *)(0x10B758) = 0x38C00064;
         
         // 47 characters is the max
         if (maxLength > 47)
            maxLength = 47; // set to 47 even if it's set to a higher number

         g_GameVariables->OSKInit(keyboardContext);
         g_GameVariables->OSKTitle(keyboardContext, "RDR2_KEYBOARD_TITLE");
         g_GameVariables->OSKDescription(keyboardContext, "RDR2_KEYBOARD_DESCRIPTION");
         return g_GameVariables->DisplayOSK(keyboardContext, 0, 1);
      }

      return false;
   }

   Status Update()
   {
      if (IsRunning())
      {
         switch (keyboardStatus)
         {
         case 0x00000000:
            return Unk;
         case 0x00000001: // keyboard active
            return Active;
         case 0x00000002: // keyboard canceled
            return Canceled;
         case 0xFFFFFFFF: // keyboard isn't active
            return NotActive;
         }
      }

      return NotActive;
   }

   std::string GetResult()
   {
      if (IsRunning())
      {
         std::wstring keyboardResult = std::wstring((const wchar_t*)(keyboardContext + 0x1C0));
         std::string text(keyboardResult.begin(), keyboardResult.end());
         return text;
      }

      return "";
   }

private:
   bool IsRunning()
   {
      keyboardInfo = *(uintptr_t*)(g_GameVariables->pRDRUIGame);
      keyboardContext = (keyboardInfo + 0x20);
      keyboardStatus = *(int32_t*)(keyboardContext + 0x228);

      return (keyboardInfo != 0);
   }

private:
   uintptr_t keyboardInfo;
   uintptr_t keyboardContext;
   int32_t keyboardStatus;
};