/**
 * @file    EditorViewCtrl.h
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#pragma once
#include "NoteTitleBar.h"
#include "NoteAttrBar.h"
#include "EditorContainer.h"

/**
 * @class   CEditorViewCtrl
 * @brief   editor view ctrl
 */
class CEditorViewCtrl : public CWindowImpl<CEditorViewCtrl>
{
public:
    DECLARE_WND_CLASS(NULL)

    BEGIN_MSG_MAP(CEditorViewCtrl)
        MESSAGE_HANDLER(WM_PAINT, OnPaint)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_ERASEBKGND(OnEraseBkgnd)
        MSG_WM_SIZE(OnSize)
        FORWARD_NOTIFICATIONS()
    END_MSG_MAP()

    CEditorViewCtrl();

    BOOL PreTranslateMessage(MSG* pMsg);
    LRESULT OnCreate(LPCREATESTRUCT lpcs);
    void OnDestroy();

    void OnSize(UINT uiParam, _WTYPES_NS::CSize size);

    LRESULT OnEraseBkgnd (HDC hdc);
    LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

private:
    COLORREF   m_crText, m_crBkgnd;

    CNoteTitleBar m_viewNoteTitleBar;
    CNoteAttrBar m_viewNoteAttr;
    CEditorContainer m_viewEditorContainer;
};
