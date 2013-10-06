/**
 * @file    EditorViewCtrl.cpp
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#include "stdafx.h"
#include "EditorViewCtrl.h"


CEditorViewCtrl::CEditorViewCtrl() : 
    m_crText(RGB(0,0,0)),
    m_crBkgnd(RGB(153,0,255))
{
}

BOOL CEditorViewCtrl::PreTranslateMessage(MSG* pMsg)
{
    pMsg;
    return FALSE;
}

LRESULT CEditorViewCtrl::OnCreate(LPCREATESTRUCT lpcs)
{
    ATLVERIFY(m_viewNoteTitleBar.Create(*this, rcDefault, NULL, CHILD_WND_STYLE));
    ATLVERIFY(m_viewNoteAttr.Create(*this, rcDefault, NULL, CHILD_WND_STYLE));
    ATLVERIFY(m_viewEditorContainer.Create(*this, rcDefault, NULL, CHILD_WND_STYLE));

    SetMsgHandled(false);
    return 0;
}

void CEditorViewCtrl::OnDestroy()
{
    SetMsgHandled(false);
}

void CEditorViewCtrl::OnSize(UINT uiParam, _WTYPES_NS::CSize size)
{
    int iTop = 0;
    m_viewNoteTitleBar.SetWindowPos(NULL, 0, iTop, size.cx, m_viewNoteTitleBar.GetFixHeight(), 0);
    iTop += m_viewNoteTitleBar.GetFixHeight();
    m_viewNoteAttr.SetWindowPos(NULL, 0, iTop, size.cx, m_viewNoteAttr.GetFixHeight(), 0);
    iTop += m_viewNoteAttr.GetFixHeight();
    m_viewEditorContainer.SetWindowPos(NULL, 0, iTop, size.cx, size.cy - iTop, 0);
}

LRESULT CEditorViewCtrl::OnEraseBkgnd(HDC hdc)
{
    return 1;   // OnPaint will draw the whole window
}

LRESULT CEditorViewCtrl::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
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
