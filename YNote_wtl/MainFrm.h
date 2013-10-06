/**
 * @file    MainFrame.h
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#pragma once
#include "resource.h"
#include "AboutDlg.h"
#include "CustomSplitterWindowT.h"
#include "LeftView.h"
#include "MiddleView.h"
#include "RightView.h"

class CMainController;

/**
 * @class   CMainFrame
 * @brief   main frame
 */
class CMainFrame : 
	public CFrameWindowImpl<CMainFrame>, 
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, 
    public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
        REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

    CMainFrame();

    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnIdle();

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	
    LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
    CCommandBarCtrl m_CmdBar;

    /// ·Ö¸î´°¿Ú
    CVerCustomSplitterWindow m_wndVerSplit1;
    CVerCustomSplitterWindow m_wndVerSplit2;

    /// Ê÷ÐÎ¿Ø¼þÈÝÆ÷
    CLeftView m_wndLeftView;

    /// ÁÐ±í¿Ø¼þÈÝÆ÷
    CMiddleView m_wndMiddleView;

    /// ±à¼­Æ÷¿Ø¼þÈÝÆ÷
    CRightView m_wndRightView;

    CMainController *m_pMainController;
};
