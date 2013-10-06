/**
 * @file    RightView.h
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#pragma once
#include "EditorViewCtrl.h"

/**
 * @class   CRightView
 * @brief   right view
 */
class CRightView : public CWindowImpl<CRightView>
{
public:
    DECLARE_WND_CLASS(NULL)

    BEGIN_MSG_MAP(CRightView)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_ERASEBKGND(OnEraseBkgnd)
        MSG_WM_SIZE(OnSize)
        FORWARD_NOTIFICATIONS()
    END_MSG_MAP()

    CRightView();

    BOOL PreTranslateMessage(MSG* pMsg);
    LRESULT OnCreate ( LPCREATESTRUCT lpcs );
    void OnDestroy();

    void OnSize(UINT uiParam, _WTYPES_NS::CSize size);

    LRESULT OnEraseBkgnd (HDC hdc);
    LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

protected:
    COLORREF   m_crText, m_crBkgnd;

    CEditorViewCtrl m_ctrlEditorView;
};
