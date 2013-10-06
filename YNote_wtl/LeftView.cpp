/**
 * @file    LeftView.cpp
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#include "stdafx.h"
#include "LeftView.h"
#include "resource.h"

CLeftView::CLeftView() : 
    m_crText(RGB(0,0,0)),
    m_crBkgnd(RGB(255,153,0))
{

}

BOOL CLeftView::PreTranslateMessage(MSG* pMsg)
{
    pMsg;
    return FALSE;
}

LRESULT CLeftView::OnCreate(LPCREATESTRUCT lpcs)
{
    if (m_ctrlNotebookTreeView.Create(*this, rcDefault, NULL, CHILD_WND_STYLE) == NULL)
    {
        ATLASSERT(FALSE);
    }
    m_ctrlNotebookTreeView.ModifyStyle(NULL, TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_EDITLABELS | TVS_FULLROWSELECT);

    CTreeItem treeItem = m_ctrlNotebookTreeView.InsertItem(_T("Notebook1"), TVI_ROOT, TVI_LAST);
    treeItem.SetData(1);
    CTreeItem subTreeItem = treeItem.AddTail(_T("subnotebook"), 0);
    subTreeItem.SetData(2);
    treeItem.Expand();

    SetMsgHandled(false);
    return 0;
}

void CLeftView::OnDestroy()
{
    SetMsgHandled(false);
}

void CLeftView::OnSize(UINT uiParam, _WTYPES_NS::CSize size)
{
    m_ctrlNotebookTreeView.SetWindowPos(NULL, 0, 0, size.cx, size.cy, 0);
}

LRESULT CLeftView::OnEraseBkgnd(HDC hdc)
{
    return 1;   // OnPaint will draw the whole window
}

LRESULT CLeftView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CPaintDC dc(m_hWnd);
    CRect    rc;
    CString  sTime;

    // Get our window's client area.
    GetClientRect ( rc );

    // Build the string to show in the window.
    sTime.Format ( _T("Clock stopped on "));

    // Set up the DC and draw the text.
    dc.SaveDC();

    dc.SetBkColor ( m_crBkgnd );
    dc.SetTextColor ( m_crText );
    dc.ExtTextOut ( 0, 0, ETO_OPAQUE, rc, sTime, sTime.GetLength(), NULL );

    // Restore the DC.
    dc.RestoreDC(-1);
    return 0;
}
