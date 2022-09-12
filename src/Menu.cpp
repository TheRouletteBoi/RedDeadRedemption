#include "RDR/Enums.hpp"
#include "Menu.hpp"

Menu g_Menu;
Keyboard g_keyboard;

Menu::Menu(Function mainSubmenu) : m_MainMenu(mainSubmenu)
{

}

void Menu::OnUpdate()
{
   if (!IsInitialized())
      Initialize();

   UpdateUI();
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

void SetCursorIndex(int index)
{
    uintptr_t gamerList = g_GameVariables->GetHudGamerList();

    if (!gamerList)
        return;
    
    *(int*)(gamerList + 0x30) = index;
}

int GetCursorIndex()
{
    return UI::UI_GET_SELECTED_INDEX("HudGamerList", false);
}

void Menu::UpdateDrawing()
{
    m_TotalOptions = m_PrintingOption;
    m_PrintingOption = -1;

    DrawHeader();

    if (m_CurrentMenu != nullptr)
        m_CurrentMenu();

    if (m_SubmenuDelay != nullptr)
    {
        EnterSubmenu(m_SubmenuDelay);
        m_SubmenuDelay = nullptr;
    }



    UI::UI_FOCUS("HudGamerList");
    UI::UI_REFRESH("HudGamerList");

    HUD::HUD_CLEAR_HELP_QUEUE(); // Gets ride of PRINT_HELP
    DECORATOR::DECOR_SET_BOOL(PLAYER::GET_PLAYER_ACTOR(PLAYER::GET_LOCAL_SLOT()), "DISABLE_HORSE_WHISTLE", true); // Disables whistling when menu is open
    AUDIO::CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH(PLAYER::GET_PLAYER_ACTOR(PLAYER::GET_LOCAL_SLOT())); // Disables speeches when menu is open (animation is still visible)
    ACTOR::_ACTOR_ALLOW_BUMP_REACTIONS(PLAYER::GET_PLAYER_ACTOR(PLAYER::GET_LOCAL_SLOT()), false); // Disables bump reactions

    if (GAME::GET_STICK_X(0, false, 0) > 0.2f
        || GAME::GET_STICK_X(0, false, 0) < -0.2f
        || GAME::GET_STICK_Y(0, false, 0) > 0.2f
        || GAME::GET_STICK_Y(0, false, 0) < -0.2f)
        PLAYER::SET_PLAYER_CONTROL(0, true, false, false);
    else
        PLAYER::SET_PLAYER_CONTROL(0, false, true, true);
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
   m_CurrentOption = (m_SavedMenu == nullptr) ? 0 : m_SavedCurrentOption;
   SetCursorIndex(m_CurrentOption);


   UI::UI_PUSH("HudGamerList");
   UI::UI_INCLUDE("HudGamerList");
   UI::UI_ENABLE("HudGamerList");
   UI::UI_ACTIVATE("HudGamerList");
   HUD::UI_ENTER("HudGamerList");
   UI::UI_FOCUS("HudGamerList");
   UI::UI_REFRESH("HudGamerList");
   AUDIO::PLAY_SOUND_FRONTEND("HUD_MP_UNLOCK_MASTER");
   m_InstructionsTextContext = SOCIALCLUB::ADD_SCRIPT_USE_CONTEXT("Generic_Dbuffer128_1", 0, 11, 0, 0, 0, 0, -1, 0);

   if (DECORATOR::DECOR_CHECK_EXIST(PLAYER::GET_PLAYER_ACTOR(PLAYER::GET_LOCAL_SLOT()), "DISABLE_HORSE_WHISTLE"))
       DECORATOR::DECOR_REMOVE(PLAYER::GET_PLAYER_ACTOR(PLAYER::GET_LOCAL_SLOT()), "DISABLE_HORSE_WHISTLE");


   AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_SELECT_MASTER");
}

void Menu::OnClose()
{
   m_Opened = false;
   m_SavedMenu = m_CurrentMenu;
   m_SavedSubmenuLevel = m_SubmenuLevel;
   m_SavedCurrentOption = m_CurrentOption;
   SetCursorIndex(m_SavedCurrentOption);


   NET4::NET_PLAYER_LIST_RESET();
   ACTOR::_ACTOR_ALLOW_BUMP_REACTIONS(PLAYER::GET_PLAYER_ACTOR(PLAYER::GET_LOCAL_SLOT()), true);

   if (SOCIALCLUB::IS_SCRIPT_USE_CONTEXT_VALID(m_InstructionsTextContext))
       SOCIALCLUB::RELEASE_SCRIPT_USE_CONTEXT(m_InstructionsTextContext);

   PLAYER::SET_PLAYER_CONTROL(0, true, false, false);
   if (UI::UI_ISFOCUSED("HudGamerList"))
       UI::UI_UNFOCUS("HudGamerList");
   else
   {
       UI::UI_FOCUS("HudGamerList");
       UI::UI_RESTORE("HudGamerList");
       UI::UI_REFRESH("HudGamerList");
   }

   // Basically while menu is not opened and playerlist is focused
   if (UI::UI_ISFOCUSED("HudGamerList"))
   {
       // Make sure the bottom right message is removed, this should've already been handled by ShutdownMenu()
       if (SOCIALCLUB::IS_SCRIPT_USE_CONTEXT_VALID(m_InstructionsTextContext))
           SOCIALCLUB::RELEASE_SCRIPT_USE_CONTEXT(m_InstructionsTextContext);

       // Remove all the remaining items, this should've already been handled by ShutdownMenu()
       NET4::NET_PLAYER_LIST_RESET();

       // Fix the playerlist and add its original title
       if (NET4::NET_GET_FREE_ROAM_MODE() == 1)
           UI::UI_SET_STRING_FORMAT("Generic_Dbuffer64_0", "%s", "Hardcore Free Roam", NULL, NULL);
       else if (NET4::NET_GET_FREE_ROAM_MODE() == 2)
           UI::UI_SET_STRING_FORMAT("Generic_Dbuffer64_0", "%s", "Friendly Free Roam", NULL, NULL);
       else
           UI::UI_SET_STRING_FORMAT("Generic_Dbuffer64_0", "%s", "Free Roam", NULL, NULL);
       NET4::NET_PLAYER_LIST_SET_TITLE("Generic_Dbuffer64_0");

       // Make sure the playerlist doesn't get fucked up with random messages from our menu
       UI::UI_SET_STRING("Generic_Dbuffer128_0", "");
       NET4::NET_PLAYER_LIST_SET_DESCRIPTION("Generic_Dbuffer128_0");

       // UI_DISABLE_INPUT("HudGamerList"); //Disable all inputs from the playerlist - not needed anymore
       UI::UI_UNFOCUS("HudGamerList");
   }


   AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_BACK_MASTER");
}

void Menu::OnBack()
{
   m_SubmenuLevel--;
   //m_LastOption[m_SubmenuLevel] = m_CurrentOption;
   m_CurrentMenu = m_LastSubmenu[m_SubmenuLevel];
   m_CurrentOption = m_LastOption[m_SubmenuLevel];
   SetCursorIndex(m_CurrentOption);

   AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_BACK_MASTER");
}

void Menu::OnScrollUp()
{
   m_CurrentOption--;
   SetCursorIndex(m_CurrentOption);
   if (m_CurrentOption < 0)
   {
      m_CurrentOption = m_TotalOptions;
      SetCursorIndex(m_CurrentOption);
   }
   AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_NAV_UP_MASTER");
}

void Menu::OnScrollDown()
{
   m_CurrentOption++;
   SetCursorIndex(m_CurrentOption);
   if (m_CurrentOption > m_TotalOptions)
   {
      m_CurrentOption = 0;
      SetCursorIndex(m_CurrentOption);
   }
   AUDIO::PLAY_SOUND_FRONTEND("HUD_MENU_NAV_DOWN_MASTER");
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
   m_CurrentOption = 0;
   SetCursorIndex(m_CurrentOption);
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

void Menu::title(const char* text)
{
    UI::UI_SET_STRING_FORMAT("Generic_Dbuffer128_0", "%s", text, NULL, NULL);
    NET4::NET_PLAYER_LIST_SET_DESCRIPTION("Generic_Dbuffer128_0");
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

   //DrawMenuTextScroller(display[index]);
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
   HUD::HUD_CLEAR_OBJECTIVE_QUEUE();
   HUD::_PRINT_SUBTITLE(text, duration, true, 2, 1, 0, 0, 0);
}

void Menu::DrawHeader()
{
    // Clear menu items
    NET4::NET_PLAYER_LIST_RESET();

    UI::UI_SET_STRING_FORMAT("Generic_Dbuffer64_0", "%s", "RouLetteBoiMenu 2.0", NULL, NULL);
    NET4::NET_PLAYER_LIST_SET_TITLE("Generic_Dbuffer64_0");
}

void Menu::DrawMenuOption(const char* text)
{
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s%s", "<blue>", text); // Other items
    NET4::NET_PLAYER_LIST_ADD_ITEM(buffer, 0); // Draw item text at defined menu slot
    NET4::_NET_PLAYER_LIST_SET_ITEM_COLOR(10); // Use defined scrollbar color (have to be used for each items)
    NET4::NET_PLAYER_LIST_SET_TEMPLATE(4); // Set up the menu style
    //NET4::NET_PLAYER_LIST_SET_HEADER(1, "");
    //NET4::NET_PLAYER_LIST_SET_HEADER(2, "");
    //NET4::NET_PLAYER_LIST_SET_HEADER(3, "");
    //NET4::NET_PLAYER_LIST_SET_HEADER(4, "");
    UI::UI_DISABLE_INPUT("HudGamerList"); // Disable all UI inputs
}

void Menu::DrawMenuToggle(bool var)
{
    NET4::_NET_PLAYER_LIST_SET_RIGHT_TEXT(0, var ? "[<green>ON</green>]" : "[<red>OFF</red>]");
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