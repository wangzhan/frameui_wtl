/**
 * @file    EditorContainer.cpp
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#include "stdafx.h"
#include "EditorContainer.h"
#include "client_handler.h"

CEditorContainer::CEditorContainer() : 
    m_crText(RGB(0,0,0)),
    m_crBkgnd(RGB(153,0,255)),
    m_pClientHandler(NULL)
{
}

BOOL CEditorContainer::PreTranslateMessage(MSG* pMsg)
{
    pMsg;
    return FALSE;
}

LRESULT CEditorContainer::OnCreate(LPCREATESTRUCT lpcs)
{
    // Create the client handler
    m_pClientHandler = new ClientHandler();
    m_pClientHandler->SetMainHwnd(*this);

    CefWindowInfo info;
    CefBrowserSettings settings;

    RECT rect;
    GetClientRect(&rect);
    info.SetAsChild(*this, rect);

    // Create the new child browser window
    CefBrowser::CreateBrowser(
        info,
        static_cast<CefRefPtr<CefClient>>(m_pClientHandler),
        m_pClientHandler->GetStartupURL(), 
        settings
        );

    SetMsgHandled(false);
    return 0;
}

void CEditorContainer::OnDestroy()
{
    SetMsgHandled(false);
}

LRESULT CEditorContainer::OnEraseBkgnd(HDC hdc)
{
    return 1;   // OnPaint will draw the whole window
}

void CEditorContainer::OnSize(UINT uiParam, _WTYPES_NS::CSize size)
{
    if ((m_pClientHandler != NULL) && (m_pClientHandler->GetBrowserHwnd() != NULL))
    {
        ::SetWindowPos(m_pClientHandler->GetBrowserHwnd(), NULL, 0, 0, size.cx, size.cy, 0);
    }

    SetMsgHandled(FALSE);
}

LRESULT CEditorContainer::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CPaintDC dc(m_hWnd);
    CRect    rc;
    CString  sTime;

    // Get our window's client area.
    GetClientRect ( rc );

    // Build the string to show in the window.
    sTime.Format ( _T("I was there"));

    // Set up the DC and draw the text.
    dc.SaveDC();

    dc.SetBkColor ( m_crBkgnd );
    dc.SetTextColor ( m_crText );
    dc.ExtTextOut ( 0, 0, ETO_OPAQUE, rc, sTime, sTime.GetLength(), NULL );

    // Restore the DC.
    dc.RestoreDC(-1);
    return 0;
}
