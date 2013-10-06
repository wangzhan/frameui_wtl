/**
 * @file    SearchBarView.cpp
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#include "stdafx.h"
#include "SearchBarView.h"
#include "resource.h"

CSearchBarView::CSearchBarView() : 
    m_crText(RGB(0,0,0)),
    m_crBkgnd(RGB(153,0,255)),
    m_iHeight(40)
{

}

BOOL CSearchBarView::PreTranslateMessage(MSG* pMsg)
{
    pMsg;
    return FALSE;
}

LRESULT CSearchBarView::OnCreate(LPCREATESTRUCT lpcs)
{
    ATLVERIFY(m_ctrlEditorView.Create(*this, rcDefault, NULL, CHILD_WND_STYLE));
    m_ctrlEditorView.ModifyStyle(0, ES_LEFT | ES_AUTOHSCROLL | ES_VERTICAL);

    // Set up the bitmap buttons.
    ATLVERIFY(m_btnSearch.Create(*this, rcDefault, NULL, CHILD_WND_STYLE));

    CImageList iml;
    iml.CreateFromImage(IDB_BITMAP3, 40, 0, CLR_NONE, IMAGE_BITMAP, 
        LR_LOADTRANSPARENT | LR_LOADMAP3DCOLORS | LR_CREATEDIBSECTION);
    m_btnSearch.SetImageList(iml.Detach());
    m_btnSearch.SetImages(0, 3, 1, 2);
    m_btnSearch.SetBitmapButtonExtendedStyle(BMPBTN_HOVER, BMPBTN_HOVER);

    SetMsgHandled(false);
    return 0;
}

void CSearchBarView::OnDestroy()
{
    SetMsgHandled(false);
}

LRESULT CSearchBarView::OnEraseBkgnd(HDC hdc)
{
    return 1;   // OnPaint will draw the whole window
}

void CSearchBarView::OnSize(UINT uiParam, _WTYPES_NS::CSize size)
{
    m_ctrlEditorView.SetWindowPos(NULL, 0, 0, size.cx - m_iHeight, size.cy, 0);
    m_btnSearch.SetWindowPos(NULL, size.cx - m_iHeight, 0, m_iHeight, m_iHeight, 0);
}

LRESULT CSearchBarView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
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

void CSearchBarView::OnClicked(UINT uiCode, int iID, CWindow hWndFrom)
{
    SetMsgHandled(FALSE);
}

int CSearchBarView::GetFixHeight() const
{
    return m_iHeight;
}

