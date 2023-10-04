#ifndef MENUITEM_H
#define MENUITEM_H

class CMenuItem
{
protected:
   MENUITEMINFO   m_ItemInfo;
	HMENU          m_hMenu;
	UINT           m_IDItem;

public:
   CMenuItem();
   CMenuItem(CWnd *Wnd, UINT IDItem);
   CMenuItem(CMenu *Menu, UINT IDItem);
   CMenuItem(HMENU Menu, UINT IDItem);
   ~CMenuItem();

	void SetItem(HMENU hMenu, UINT IDItem);
   void SetShortcut(CString Key);
   void SetCaption(CString Caption);
   void SetEnabled(BOOL Enabled);

   HMENU GetHandle() { return m_hMenu;};
   UINT  GetID() { return m_IDItem;};

   bool Valid();
};

WORD TextToShortCut(CString SC);


#endif