/**
 * @file    NoteListViewCtrl.h
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#pragma once


typedef CWinTraitsOR<WS_BORDER | LVS_REPORT | LVS_SINGLESEL | 
    LVS_NOSORTHEADER | LVS_SHOWSELALWAYS /*| LVS_OWNERDRAWFIXED*/> CListTraits;

/**
 * @class   CNoteListViewCtrl
 * @brief   note list view control
 */
class CNoteListViewCtrl : public CWindowImpl<CNoteListViewCtrl, CListViewCtrl, CListTraits>,
    public COwnerDraw<CNoteListViewCtrl>
{
public:
    DECLARE_WND_SUPERCLASS(NULL, WC_LISTVIEW)

    BEGIN_MSG_MAP_EX(CNoteListViewCtrl)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        CHAIN_MSG_MAP_ALT(COwnerDraw<CNoteListViewCtrl>, 1)
        DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()

    CNoteListViewCtrl();
    ~CNoteListViewCtrl();

    // Message handlers
    LRESULT OnCreate(LPCREATESTRUCT pStruct);
    void OnDestroy();

    // Notification handlers
    void DrawItem(LPDRAWITEMSTRUCT lpdis);
    void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
    void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

    DWORD DrawItemEx(LPDRAWITEMSTRUCT lpdis);

private:
    CBitmap m_bitmap;
};
