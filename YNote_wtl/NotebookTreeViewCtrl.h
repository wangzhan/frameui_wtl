/**
 * @file    NotebookTreeViewCtrl.h
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#pragma once

/**
 * @class   CNotebookTreeViewCtrl
 * @brief   notebook tree view control
 */
class CNotebookTreeViewCtrl : public CWindowImpl<CNotebookTreeViewCtrl, CTreeViewCtrlEx>,
    public CCustomDraw<CNotebookTreeViewCtrl>
{
public:
    BEGIN_MSG_MAP(CNotebookTreeViewCtrl)
        MSG_WM_CREATE(OnCreate)
        REFLECTED_NOTIFY_CODE_HANDLER_EX(TVN_ITEMEXPANDING, OnItemExpanding)
        REFLECTED_NOTIFY_CODE_HANDLER_EX(TVN_SELCHANGED, OnSelChanged)
        CHAIN_MSG_MAP_ALT(CCustomDraw<CNotebookTreeViewCtrl>, 1)
        DEFAULT_REFLECTION_HANDLER()
    END_MSG_MAP()

    LRESULT OnCreate(LPCREATESTRUCT pStruct);

    LRESULT OnSelChanged(NMHDR* phdr);
    LRESULT OnItemExpanding(NMHDR* phdr);

    DWORD OnPrePaint(int idCtrl, LPNMCUSTOMDRAW lpNMCD);
    DWORD OnItemPrePaint(int idCtrl, LPNMCUSTOMDRAW lpNMCD);
    DWORD DrawItem(NMTVCUSTOMDRAW* pnmtv, CBitmap &bitmap);

private:
    CBitmap m_bitmapNotebookGroup;
    CBitmap m_bitmapNotebook;
};
