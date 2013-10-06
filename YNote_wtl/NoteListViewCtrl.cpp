/**
 * @file    NoteListViewCtrl.cpp
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#include "stdafx.h"
#include "NoteListViewCtrl.h"
#include "resource.h"

CNoteListViewCtrl::CNoteListViewCtrl(void)
{
}


CNoteListViewCtrl::~CNoteListViewCtrl(void)
{
}

LRESULT CNoteListViewCtrl::OnCreate(LPCREATESTRUCT pStruct)
{
    m_bitmap.LoadBitmapW(IDB_BITMAP1);
    SetMsgHandled(FALSE);
    return 0;
}

void CNoteListViewCtrl::OnDestroy()
{
}

void CNoteListViewCtrl::DrawItem(LPDRAWITEMSTRUCT lpdis)
{
    DrawItemEx(lpdis);
}

void CNoteListViewCtrl::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
{
    SetMsgHandled(FALSE);
}

void CNoteListViewCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    lpMeasureItemStruct->itemHeight = 40;
}

DWORD CNoteListViewCtrl::DrawItemEx(LPDRAWITEMSTRUCT lpdis)
{   
    CString strText = _T("123");
    RECT rcPaint = lpdis->rcItem;
    CDCHandle dc = lpdis->hDC;
    CDC dcMem;
    CSize size;
    m_bitmap.GetSize(size);

    dcMem.CreateCompatibleDC ( dc );
    dc.SaveDC();
    dcMem.SaveDC();

    // Draw the icon
    dcMem.SelectBitmap(m_bitmap);
    dc.StretchBlt(rcPaint.left, rcPaint.top, rcPaint.bottom - rcPaint.top, rcPaint.bottom - rcPaint.top, 
                  dcMem, 0, 0, size.cx, size.cy, SRCCOPY);

    // Draw the text
    dc.TextOutW(rcPaint.left + rcPaint.bottom - rcPaint.top + 3, rcPaint.top, strText);

    dcMem.RestoreDC(-1);
    dc.RestoreDC(-1);
    return CDRF_SKIPDEFAULT;
}
