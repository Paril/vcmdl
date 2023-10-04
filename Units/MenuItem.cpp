#include "stdafx.h"

#include "MenuItem.h"


CMenuItem::CMenuItem()
{
   m_hMenu = NULL;
   m_IDItem = 0;
}

CMenuItem::CMenuItem(CWnd *Wnd, UINT IDItem)
{
   if (Wnd)
      m_hMenu = Wnd->GetMenu()->m_hMenu;

   m_IDItem = IDItem;
}

CMenuItem::CMenuItem(CMenu *Menu, UINT IDItem)
{
   if (Menu)
      m_hMenu = Menu->m_hMenu;

   m_IDItem = IDItem;
}

CMenuItem::CMenuItem(HMENU Menu, UINT IDItem)
{
   m_hMenu = Menu;
   m_IDItem = IDItem;
}

CMenuItem::~CMenuItem()
{
}

void CMenuItem::SetItem(HMENU hMenu, UINT IDItem)
{
   m_hMenu = hMenu;
   m_IDItem = IDItem;

//   GetMenuItemInfo(m_hMenu, m_IDItem, FALSE, &m_ItemInfo);
}

void CMenuItem::SetShortcut(CString Key)
{
   MENUITEMINFO   Info;
   char           MenuCaption[128];

   Info.cbSize = sizeof(MENUITEMINFO);
   Info.fMask = MIIM_TYPE;
   Info.fType = MFT_STRING;
   Info.dwTypeData = MenuCaption;
   Info.cch = 127;

   GetMenuItemInfo(m_hMenu, m_IDItem, FALSE, &Info);

   // search thorugh the menu item string, and look for the tab character
   // replacing it with a null, so the correct shortcut can be appended

   {
      char  *S;
      S = MenuCaption;
      while (*S)
      {
         if (*S == '\t')
         {
            *S = '\x0';
            break;
         }
         S++;         
      }
   }

   strcat(MenuCaption, "\t");
   strcat(MenuCaption, (LPCTSTR)Key);

   SetMenuItemInfo(m_hMenu, m_IDItem, FALSE, &Info);

   return;
}

void CMenuItem::SetCaption(CString Caption)
{
   MENUITEMINFO   Info;
   char           MenuCaption[128], *ShortCutStr;

   Info.cbSize = sizeof(MENUITEMINFO);
   Info.fMask = MIIM_TYPE;
   Info.fType = MFT_STRING;
   Info.dwTypeData = MenuCaption;
   Info.cch = 127;

   GetMenuItemInfo(m_hMenu, m_IDItem, FALSE, &Info);

   // search thorugh the menu item string, and look for the tab character
   // replacing it with a null, so the correct shortcut can be appended

   ShortCutStr = NULL;
   {
      char  *S;
      S = MenuCaption;
      while (*S)
      {
         if (*S == '\t')
         {
            *S = '\x0';
            ShortCutStr = S + 1;
            break;
         }
         S++;         
      }
   }

   if (ShortCutStr)
      Caption = Caption + CString("\t") + CString(ShortCutStr);

   ::ModifyMenu(m_hMenu, m_IDItem, MF_BYCOMMAND | MF_STRING, m_IDItem, (LPCTSTR)Caption);
}

void CMenuItem::SetEnabled(BOOL Enabled)
{
   UINT Flag, Res;

   if (Enabled)
      Flag = MF_ENABLED;
   else
      Flag = MF_GRAYED;

   Res = ::EnableMenuItem(m_hMenu, m_IDItem, MF_BYCOMMAND | Flag);
}

bool CMenuItem::Valid()
{
   if (m_hMenu == NULL || m_IDItem == NULL)
      return false;

   return true;
}
