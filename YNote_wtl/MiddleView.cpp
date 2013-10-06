/**
 * @file    MiddleView.cpp
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#include "stdafx.h"
#include "MiddleView.h"


CMiddleView::CMiddleView() : 
    m_crText(RGB(0,0,0)),
    m_crBkgnd(RGB(153,255,0))
{
}

BOOL CMiddleView::PreTranslateMessage(MSG* pMsg)
{
    pMsg;
    return FALSE;
}

LRESULT CMiddleView::OnCreate(LPCREATESTRUCT lpcs)
{
    ATLVERIFY(m_ctrlNoteListView.Create(*this, rcDefault, NULL, CHILD_WND_STYLE));

    m_ctrlNoteListView.ModifyStyle(0, LVS_NOCOLUMNHEADER);
    m_ctrlNoteListView.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);

    m_ctrlNoteListView.InsertColumn(0, _T("listview"), LVCFMT_CENTER);
    m_ctrlNoteListView.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

    m_ctrlNoteListView.InsertItem(0, _T("nihaoa"));
    m_ctrlNoteListView.SetItemData(0, 1);
    m_ctrlNoteListView.InsertItem(1, _T("haha"));

    ATLVERIFY(m_viewSearchBar.Create(*this, rcDefault));

    SetMsgHandled(false);
    return 0;
}

void CMiddleView::OnDestroy()
{
    SetMsgHandled(false);
}

LRESULT CMiddleView::OnEraseBkgnd(HDC hdc)
{
    return 1;   // OnPaint will draw the whole window
}

void CMiddleView::OnSize(UINT uiParam, _WTYPES_NS::CSize size)
{
    m_viewSearchBar.SetWindowPos(NULL, 0, 0, size.cx, m_viewSearchBar.GetFixHeight(), 0);
    m_ctrlNoteListView.SetWindowPos(NULL, 0, m_viewSearchBar.GetFixHeight(), size.cx, size.cy - m_viewSearchBar.GetFixHeight(), 0);
}

LRESULT CMiddleView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CPaintDC dc(m_hWnd);
    CRect    rc;
    CString  sTime;

    // Get our window's client area.
    GetClientRect ( rc );

    // Build the string to show in the window.
    sTime.Format ( _T("Clock stopped on"));

    // Set up the DC and draw the text.
    dc.SaveDC();

    dc.SetBkColor ( m_crBkgnd );
    dc.SetTextColor ( m_crText );
    dc.ExtTextOut ( 0, 0, ETO_OPAQUE, rc, sTime, sTime.GetLength(), NULL );

    // Restore the DC.
    dc.RestoreDC(-1);
    return 0;
}
