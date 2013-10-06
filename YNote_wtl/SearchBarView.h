/**
 * @file    SearchBarView.h
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#pragma once

/**
 * @class   CSearchBarView
 * @brief   search bar view
 */
class CSearchBarView : public CWindowImpl<CSearchBarView>
{
public:
    DECLARE_WND_CLASS(NULL)

    BEGIN_MSG_MAP(CSearchBarView)
        //MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        //MSG_WM_ERASEBKGND(OnEraseBkgnd)
        MSG_WM_SIZE(OnSize)
        COMMAND_CODE_HANDLER_EX(BN_CLICKED, OnClicked)
        FORWARD_NOTIFICATIONS()
    END_MSG_MAP()

    CSearchBarView();

    BOOL PreTranslateMessage(MSG* pMsg);
    LRESULT OnCreate ( LPCREATESTRUCT lpcs );
    void OnDestroy();

    void OnSize(UINT uiParam, _WTYPES_NS::CSize size);

    LRESULT OnEraseBkgnd (HDC hdc);
    LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    void OnClicked(UINT uiCode, int iID, CWindow hWndFrom);

    int GetFixHeight() const;

protected:
    COLORREF   m_crText, m_crBkgnd;
    const int m_iHeight;

    CEdit m_ctrlEditorView;
    CBitmapButton m_btnSearch;
};
