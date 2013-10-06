/**
 * @file    NoteAttrBar.cpp
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#include "stdafx.h"
#include "NoteAttrBar.h"


CNoteAttrBar::CNoteAttrBar() : 
    m_crText(RGB(0,0,0)),
    m_crBkgnd(RGB(153,255,0)),
    m_iAttrBarHeight(80)
{

}

BOOL CNoteAttrBar::PreTranslateMessage(MSG* pMsg)
{
    pMsg;
    return FALSE;
}

LRESULT CNoteAttrBar::OnCreate(LPCREATESTRUCT lpcs)
{
    SetMsgHandled(false);
    return 0;
}

void CNoteAttrBar::OnDestroy()
{
    SetMsgHandled(false);
}

LRESULT CNoteAttrBar::OnEraseBkgnd(HDC hdc)
{
    return 1;   // OnPaint will draw the whole window
}

void CNoteAttrBar::OnSize(UINT uiParam, _WTYPES_NS::CSize size)
{
    SetMsgHandled(FALSE);
}

LRESULT CNoteAttrBar::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CPaintDC dc(m_hWnd);
    CRect    rc;
    CString  sTime;

    // Get our window's client area.
    GetClientRect ( rc );

    // Build the string to show in the window.
    sTime.Format ( _T("note attr"));

    // Set up the DC and draw the text.
    dc.SaveDC();

    dc.SetBkColor ( m_crBkgnd );
    dc.SetTextColor ( m_crText );
    dc.ExtTextOut ( 0, 0, ETO_OPAQUE, rc, sTime, sTime.GetLength(), NULL );

    // Restore the DC.
    dc.RestoreDC(-1);
    return 0;
}

int CNoteAttrBar::GetFixHeight() const
{
    return m_iAttrBarHeight;
}
