/**
 * @file    NotebookTreeViewCtrl.cpp
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#include "stdafx.h"
#include "NotebookTreeViewCtrl.h"
#include "resource.h"

LRESULT CNotebookTreeViewCtrl::OnCreate(LPCREATESTRUCT pStruct)
{
    m_bitmapNotebookGroup.LoadBitmap(IDB_BITMAP1);
    m_bitmapNotebook.LoadBitmapW(IDB_BITMAP2);

    SetMsgHandled(FALSE);
    return 0;
}

LRESULT CNotebookTreeViewCtrl::OnItemExpanding(NMHDR* phdr)
{
    NMTREEVIEW* pnmtv = (NMTREEVIEW*) phdr;

    if ( pnmtv->action & TVE_COLLAPSE )
        return FALSE;    // allow it
    else
        return FALSE;   // allow it
}

DWORD CNotebookTreeViewCtrl::OnPrePaint(int idCtrl, LPNMCUSTOMDRAW lpNMCD)
{
    return CDRF_NOTIFYITEMDRAW;
}

DWORD CNotebookTreeViewCtrl::OnItemPrePaint(int idCtrl, LPNMCUSTOMDRAW lpNMCD)
{
    NMTVCUSTOMDRAW* pnmtv = (NMTVCUSTOMDRAW*) lpNMCD;

    switch ( lpNMCD->lItemlParam )
    {
    case 1:
        pnmtv->clrText = RGB(255,0,255);
        // TODO: reserve
        //return DrawItem(pnmtv, m_bitmapNotebookGroup);
        break;

    case 2:
        pnmtv->clrText = RGB(0,0,255);
        // TODO: reserve
        //return DrawItem(pnmtv, m_bitmapNotebook);
        break;

    case 3:
        pnmtv->clrText = RGB(0,0,255);
        break;

    case 4:
        pnmtv->clrText = RGB(196,196,196);
        break;
    }

    return CDRF_DODEFAULT;
}

LRESULT CNotebookTreeViewCtrl::OnSelChanged(NMHDR* phdr)
{
    NMTREEVIEW* pnmtv = (NMTREEVIEW*)phdr;
    return 0;
}

DWORD CNotebookTreeViewCtrl::DrawItem(NMTVCUSTOMDRAW* pnmtv, CBitmap &bitmap)
{
    CString strText = _T("123");
    RECT rcPaint = pnmtv->nmcd.rc;
    CDCHandle dc = pnmtv->nmcd.hdc;
    CDC dcMem;
    CSize size;
    bitmap.GetSize(size);

    dcMem.CreateCompatibleDC ( dc );
    dc.SaveDC();
    dcMem.SaveDC();

    // Draw the icon
    dcMem.SelectBitmap(bitmap);
    dc.StretchBlt(rcPaint.left, rcPaint.top, rcPaint.bottom - rcPaint.top, rcPaint.bottom - rcPaint.top, 
        dcMem, 0, 0, size.cx, size.cy, SRCCOPY);

    // Draw the text
    dc.SetBkColor(pnmtv->clrTextBk);
    dc.SetTextColor(pnmtv->clrText);
    dc.TextOutW(rcPaint.left + rcPaint.bottom - rcPaint.top + 3, rcPaint.top, strText);

    dcMem.RestoreDC(-1);
    dc.RestoreDC(-1);
    return CDRF_SKIPDEFAULT;
}
