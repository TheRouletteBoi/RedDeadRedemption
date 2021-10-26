#pragma once
#include "Natives.hpp"
#include "Keyboard.hpp"

using Function = void(*)();
using KeyboardHandler = void(*)(const std::string&);

enum class OptionAction
{
   EnterPress,
   LeftPress,
   RightPress,
   LeftOrRightPress,
   SquarePress
};

class Menu
{
public:
   explicit Menu() = default;
   explicit Menu(Function mainSubmenu);
   ~Menu() noexcept = default;

   void RegisterOnMain(Function onMain);
   void OnGameTick();
   void ShowSubtitle(const char* text, float duration = 5.0f);

   bool IsEnterPressed();
   bool IsLeftPressed();
   bool IsRightPressed();
   bool IsLeftOrRightPressed();
   bool IsSquarePressed();
   bool pressed();
   bool hovered();
   void ChangeSubmenu(Function submenu);
   void banner(const char* text);
   Menu& submenu(Function sub);
   Menu& option(const char* text);
   Menu& end();
   Menu& toggle(bool& var);
   Menu& toggle(bool& var, Function onEnable, Function onDisable);
   Menu& local(bool var);
   Menu& action(OptionAction opt, Function fn);
   Menu& scroller(const char** display, int& index, int numItems);
   Menu& keyboard(KeyboardHandler handler);
   template<typename F, typename... Args>
   Menu& call(F fn, Args&&... args)
   {
      if (pressed())
      {
         fn(args...);
      }
      return *this;
   }

private:
   bool IsInitialized();
   void Initialize();
   void Tick();
   void UpdateUI();
   bool IsBinds();
   void OpenKeyboard(KeyboardHandler handler);
   void UpdateDrawing();
   void UpdateKeyboard();
   void UpdateButtons();
   void WhileOpen();
   void WhileClosed();
   void OnOpen();
   void OnClose();
   void OnBack();
   void OnScrollUp();
   void OnScrollDown();
   void DrawMenuOption(const char* text);
   void DrawMenuToggle(bool var);
   void DrawMenuTextScroller(const char* var);
   void DrawMenuCount();
   void EnterSubmenu(Function submenu);
   template <typename T>
   void processOptionItemControls(T& var, T min, T max, T step)
   {
      if (hovered())
      {
         if (IsLeftPressed())
         {
            if (var <= min)
               var = max;
            else
               var -= step;
         }

         if (var < min)
            var = max;

         if (IsRightPressed())
         {
            if (var >= max)
               var = min;
            else
               var += step;
         }

         if (var > max)
            var = min;
      }
   }
   

public:
   size_t m_CurrentOption = 0;


private:
   bool m_Initialized{};
   bool m_Opened{};
   Function m_OnMain{};
   Function m_MainMenu{};
   Function m_CurrentMenu{};
   Function m_SavedMenu{};
   Function m_SubmenuDelay{};
   static const unsigned maxSubmenuLevels = 50;
   Function m_LastSubmenu[maxSubmenuLevels]{};
   size_t m_LastOption[maxSubmenuLevels]{};
   int m_SavedSubmenuLevel = 0;
   size_t m_SavedCurrentOption = 1;
   int m_SubmenuLevel = 0;
   size_t m_PrintingOption = 0;
   size_t m_TotalOptions = 0;
   static const int maxMenuCharacterLimit = 1000;
   char m_MenuOptionText[maxMenuCharacterLimit]{};

   // Keyboard
   bool m_KeyboardActive{};
   KeyboardHandler m_KeyboardHandler{};

};

extern Menu g_Menu;