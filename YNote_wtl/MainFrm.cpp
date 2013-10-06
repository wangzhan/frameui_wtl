/**
 * @file    MainFrame.cpp
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#include "stdafx.h"
#include "MainFrm.h"
#include "MainController.h"

CMainFrame::CMainFrame()
{
    m_pMainController = new CMainController();
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
    if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
        return TRUE;

    return (m_wndLeftView.PreTranslateMessage(pMsg) || 
        m_wndMiddleView.PreTranslateMessage(pMsg) || 
        m_wndRightView.PreTranslateMessage(pMsg));
}

BOOL CMainFrame::OnIdle()
{
    UIUpdateToolBar();
    return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // create command bar window
    HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
    // attach menu
    m_CmdBar.AttachMenu(GetMenu());
    // load command bar images
    m_CmdBar.LoadImages(IDR_MAINFRAME);
    // remove old menu
    SetMenu(NULL);

    HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

    CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
    AddSimpleReBarBand(hWndCmdBar);
    AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

    CreateSimpleStatusBar();

    UIAddToolBar(hWndToolBar);
    UISetCheck(ID_VIEW_TOOLBAR, 1);
    UISetCheck(ID_VIEW_STATUS_BAR, 1);

    // register object for message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);

    // Create the splitter windows.
    const DWORD dwSplitStyle = CHILD_WND_STYLE;

    m_wndVerSplit1.Create (*this, rcDefault, NULL, dwSplitStyle);
    m_wndVerSplit1.m_bFullDrag = false;
    m_wndVerSplit1.m_cxyMin = 200;
    m_wndVerSplit1.SetSplitterPos(200);

    m_wndVerSplit2.Create(m_wndVerSplit1, rcDefault, NULL, dwSplitStyle);
    m_wndVerSplit2.m_bFullDrag = false;
    m_wndVerSplit2.m_cxyMin = 200;
    m_wndVerSplit2.SetSplitterPos(200);

    // Create splitter view
    const DWORD dwViewStyle = CHILD_WND_STYLE;
    const DWORD dwViewStyleEx = WS_EX_CLIENTEDGE;
    m_wndLeftView.Create(m_wndVerSplit1, rcDefault, NULL, dwViewStyle, dwViewStyleEx);
    m_wndMiddleView.Create(m_wndVerSplit2, rcDefault, NULL, dwViewStyle, dwViewStyleEx);
    m_wndRightView.Create(m_wndVerSplit2, rcDefault, NULL, dwViewStyle, dwViewStyleEx);

    m_wndVerSplit1.SetSplitterPanes(m_wndLeftView, m_wndVerSplit2);
    m_wndVerSplit2.SetSplitterPanes(m_wndMiddleView, m_wndRightView);
    m_hWndClient = m_wndVerSplit1;

    // Set the splitter as the client area window, and resize the splitter 
    // to match the frame size.
    UpdateLayout();

    return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
    // unregister message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->RemoveMessageFilter(this);
    pLoop->RemoveIdleHandler(this);

    delete m_pMainController;
    m_pMainController = NULL;

    bHandled = FALSE;
    return 1;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    PostMessage(WM_CLOSE);
    return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: add code to initialize document

    return 0;
}

LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    static BOOL bVisible = TRUE;	// initially visible
    bVisible = !bVisible;
    CReBarCtrl rebar = m_hWndToolBar;
    int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
    rebar.ShowBand(nBandIndex, bVisible);
    UISetCheck(ID_VIEW_TOOLBAR, bVisible);
    UpdateLayout();
    return 0;
}

LRESULT CMainFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
    ::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
    UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
    UpdateLayout();
    return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    CAboutDlg dlg;
    dlg.DoModal();
    return 0;
}
