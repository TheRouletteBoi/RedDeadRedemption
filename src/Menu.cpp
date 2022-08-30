#include "RDR/Enums.hpp"
#include "Menu.hpp"

Menu g_Menu;
Keyboard g_keyboard;

Menu::Menu(Function mainSubmenu) : m_MainMenu(mainSubmenu)
{

}

void Menu::OnGameTick()
{
   if (!IsInitialized())
      Initialize();

   Tick();
}

bool Menu::IsInitialized()
{
   return m_Initialized;
}

void Menu::Initialize()
{
   if (m_OnMain != nullptr)
      m_OnMain();

   m_Initialized = true;
}

void Menu::RegisterOnMain(Function onMain)
{
   m_OnMain = onMain;
}

bool Menu::IsEnterPressed()
{
   if (GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_RDOWN, 1, 0))
   {
      AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_SELECT_MASTER");
      return true;
   }

   return false;
}

bool Menu::IsLeftPressed()
{
   if (GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_LEFT, 1, 0))
   {
      AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_NAV_LEFT_MASTER");
      return true;
   }

   return false;
}

bool Menu::IsRightPressed()
{
   if (GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_RIGHT, 1, 0))
   {
      AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_NAV_RIGHT_MASTER");
      return true;
   }

   return false;
}

bool Menu::IsLeftOrRightPressed()
{
   if (GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_LEFT, 1, 0) || GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_RIGHT, 1, 0))
   {
      AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_NAV_RIGHT_MASTER");
      return true;
   }

   return false;
}

bool Menu::IsSquarePressed()
{
   if (GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_RLEFT, 1, 0))
   {
      AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_SELECT_MASTER");
      return true;
   }

   return false;
}

bool Menu::IsBinds()
{
   return (GAME::IS_BUTTON_DOWN(0, INPUT_FRONTEND_RS, 1, 0) && GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_LEFT, 1, 0))
      || (GAME::IS_BUTTON_DOWN(0, INPUT_FRONTEND_LEFT, 1, 0) && GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_RS, 1, 0));
}

void Menu::OpenKeyboard(KeyboardHandler handler)
{
   g_keyboard.Display("", "", 500);
   m_KeyboardHandler = handler;
   m_KeyboardActive = true;
}

void Menu::UpdateDrawing()
{
   m_TotalOptions = m_PrintingOption;
   m_PrintingOption = 0;

   if (m_CurrentMenu != nullptr)
      m_CurrentMenu();

   if (m_SubmenuDelay != nullptr)
   {
      EnterSubmenu(m_SubmenuDelay);
      m_SubmenuDelay = nullptr;
   }

   DrawMenuCount();

   HUD::_HUD_CLEAR_PRINTS();     // required but this also blocks from subtitles from showing up
   HUD::HUD_CLEAR_HELP_QUEUE();  // remove queue messages so the menu doesn't overlay
   HUD::PRINT_HELP_B(m_MenuOptionText, 1, 0, 1, 0, 0, 0, 0);
}

void Menu::UpdateKeyboard()
{
   if (m_KeyboardActive)
   {
      Keyboard::Status status = g_keyboard.Update();
      if (status == Keyboard::Status::Active)
      {
         if (m_KeyboardHandler != nullptr)
            m_KeyboardHandler(g_keyboard.GetResult());
         m_KeyboardActive = false;
      }
      else if (status == Keyboard::Status::Canceled || status == Keyboard::Status::NotActive)
      {
         m_KeyboardActive = false;
      }
   }
}

void Menu::UpdateButtons()
{
   if (GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_RRIGHT, 1, 0))
   {
      if (m_CurrentMenu == m_MainMenu)
         OnClose();
      else
         OnBack();
   }
   if (GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_UP, 1, 0))
   {
      OnScrollUp();
   }
   if (GAME::IS_BUTTON_PRESSED(0, INPUT_FRONTEND_DOWN, 1, 0))
   {
      OnScrollDown();
   }

   if (IsBinds())
      OnClose();
}

void Menu::WhileOpen()
{
   UpdateDrawing();
   UpdateKeyboard();
   UpdateButtons();
}

void Menu::WhileClosed()
{
   if (IsBinds())
      OnOpen();
}

void Menu::OnOpen()
{
   m_Opened = true;
   m_CurrentMenu = (m_SavedMenu == nullptr) ? m_MainMenu : m_SavedMenu;
   m_SubmenuLevel = (m_SavedMenu == nullptr) ? 0 : m_SavedSubmenuLevel;
   m_CurrentOption = (m_SavedMenu == nullptr) ? 1 : m_SavedCurrentOption;

   AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_SELECT_MASTER");
}

void Menu::OnClose()
{
   m_Opened = false;
   m_SavedMenu = m_CurrentMenu;
   m_SavedSubmenuLevel = m_SubmenuLevel;
   m_SavedCurrentOption = m_CurrentOption;

   AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_BACK_MASTER");
}

void Menu::OnBack()
{
   m_SubmenuLevel--;
   //m_LastOption[m_SubmenuLevel] = m_CurrentOption;
   m_CurrentMenu = m_LastSubmenu[m_SubmenuLevel];
   m_CurrentOption = m_LastOption[m_SubmenuLevel];

   AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_BACK_MASTER");
}

void Menu::OnScrollUp()
{
   m_CurrentOption--;
   if (m_CurrentOption < 1)
   {
      m_CurrentOption = m_TotalOptions;
   }
   AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_NAV_UP_MASTER");
}

void Menu::OnScrollDown()
{
   m_CurrentOption++;
   if (m_CurrentOption > m_TotalOptions)
   {
      m_CurrentOption = 1;
   }
   AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_NAV_DOWN_MASTER");
}

void Menu::DrawMenuOption(const char* text)
{
   char activeColor[300];
   snprintf(activeColor, sizeof(activeColor), "%s%s%s", hovered() ? "<blue>" : "<grey>", text, hovered() ? "</blue>" : "</grey>");
   strncat(m_MenuOptionText, activeColor, sizeof(activeColor));
}

void Menu::DrawMenuToggle(bool var)
{
   strncat(m_MenuOptionText, var ? " <green>On</green>" : " <red>Off</red>", 30);
}

void Menu::DrawMenuTextScroller(const char* var)
{
   char leftRightText[300];
   snprintf(leftRightText, sizeof(leftRightText), 
      " <dpadleft> %s%s%s <dpadright>", 
      hovered() ? "<blue>" : "<grey>", 
      var, 
      hovered() ? "</blue>" : "</grey>");
   strncat(m_MenuOptionText, leftRightText, sizeof(leftRightText));
}

void Menu::DrawMenuCount()
{
   char optionCountStr[30];
   snprintf(optionCountStr, sizeof(optionCountStr), "<red>(%d/%d)</red>", m_CurrentOption, m_TotalOptions);
   strncat(m_MenuOptionText, optionCountStr, sizeof(optionCountStr));
}

bool Menu::pressed()
{
   if (hovered())
   {
      return IsEnterPressed();
   }
   return false;
}

void Menu::EnterSubmenu(Function submenu)
{
   if (submenu == nullptr)
      return;

   m_LastSubmenu[m_SubmenuLevel] = m_CurrentMenu;
   m_LastOption[m_SubmenuLevel] = m_CurrentOption;
   m_CurrentMenu = submenu;
   m_CurrentOption = 1;
   m_SubmenuLevel++;
}

void Menu::ChangeSubmenu(Function submenu)
{
   if (submenu != nullptr)
      m_SubmenuDelay = submenu;
}

bool Menu::hovered()
{
   return m_CurrentOption == m_PrintingOption;
}

void Menu::banner(const char* text)
{
   char titleColor[200];
   snprintf(titleColor, sizeof(titleColor), "<red>%s</red>", text);
   strncpy(m_MenuOptionText, titleColor, sizeof(titleColor));
   strncat(m_MenuOptionText, " \n", 5);
}

Menu& Menu::end()
{
   strncat(m_MenuOptionText, " \n", 5);
   m_MenuOptionText[maxMenuCharacterLimit - 1] = 0; // null terminator
   return *this;
}

Menu& Menu::submenu(Function sub)
{
   if (pressed())
   {
      ChangeSubmenu(sub);
   }
   return *this;
}

Menu& Menu::option(const char* text)
{
   m_PrintingOption++;
   DrawMenuOption(text);
   return *this;
}

Menu& Menu::toggle(bool& var)
{
   DrawMenuToggle(var);

   if (pressed())
   {
      var ^= 1;
   }

   return *this;
}

Menu& Menu::toggle(bool& var, Function onEnable, Function onDisable)
{
   DrawMenuToggle(var);

   if (pressed())
   {
      var ^= 1;

      if (var)
      {
         if (onEnable != nullptr)
            onEnable();
      }
      else
      {
         if (onDisable != nullptr)
            onDisable();
      }
   }

   return *this;
}

Menu& Menu::local(bool var)
{
   DrawMenuToggle(var);
   return *this;
}

Menu& Menu::action(OptionAction opt, Function fn)
{
   if (hovered())
   {
      if (opt == OptionAction::EnterPress && IsEnterPressed())
      {
         fn();
         return *this;
      }
      else if (opt == OptionAction::LeftPress && IsLeftPressed())
      {
         fn();
         return *this;
      }
      else if (opt == OptionAction::RightPress && IsRightPressed())
      {
         fn();
         return *this;
      }
      else if (opt == OptionAction::LeftOrRightPress && IsLeftOrRightPressed())
      {
         fn();
         return *this;
      }
      else if (opt == OptionAction::SquarePress && IsSquarePressed())
      {
         fn();
         return *this;
      }
   }
   return *this;
}

Menu& Menu::scroller(const char** display, int& index, int numItems)
{
   processOptionItemControls<int>(index, 0, numItems, 1);

   if (index > numItems || index < 0)
      return *this;

   DrawMenuTextScroller(display[index]);
   return *this;
}

Menu& Menu::keyboard(KeyboardHandler handler)
{
   if (pressed())
   {
      OpenKeyboard(handler);
   }
   return *this;
}

void Menu::ShowSubtitle(const char* text, float duration)
{
   HUD::_HUD_CLEAR_PRINTS();
   HUD::_PRINT_SUBTITLE(text, duration, true, 2, 1, 0, 0, 0);
}

void Menu::Tick()
{
   UpdateUI();
}

void Menu::UpdateUI()
{
   if (m_Opened)
   {
      WhileOpen();
   }
   else
   {
      WhileClosed();
   }
}