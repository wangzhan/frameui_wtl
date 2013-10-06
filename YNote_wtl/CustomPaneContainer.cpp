/**
 * @file    CustomPaneContainer.cpp
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#include "stdafx.h"
#include "CustomPaneContainer.h"


CCustomPaneContainer::CCustomPaneContainer(void)
    : m_bColoredHeader(false)
{
}

void CCustomPaneContainer::EnableColoredHeader ( bool bEnable )
{
    if ( bEnable != m_bColoredHeader )
    {
        m_bColoredHeader = bEnable;
        RedrawWindow();
    }
}

BOOL CCustomPaneContainer::GetToolTipText(LPNMHDR lpnmh)
{
    NMTTDISPINFOA* pnmdiA = (NMTTDISPINFOA*) lpnmh;
    NMTTDISPINFOW* pnmdiW = (NMTTDISPINFOW*) lpnmh;

    if ( lpnmh->code == TTN_GETDISPINFOA )
    {
        pnmdiA->lpszText = "Head title";
        pnmdiA->uFlags |= TTF_DI_SETITEM;
    }
    else
    {
        pnmdiW->lpszText = L"Head title";
        pnmdiW->uFlags |= TTF_DI_SETITEM;
    }

    return 0;
}

void CCustomPaneContainer::DrawPaneTitle ( CDCHandle dc )
{
    RECT rect;

    // If we're not using a colored header, let the base class do the
    // default drawing.
    if ( !m_bColoredHeader )
    {
        CPaneContainerImpl<CCustomPaneContainer>::DrawPaneTitle ( dc );
        return;
    }

    GetClientRect(&rect);

    if ( IsVertical() )
    {
        TRIVERTEX tv[] = { { rect.left, rect.top, 0xff00 },
        { rect.left + m_cxyHeader, rect.bottom, 0, 0xff00 } };
        GRADIENT_RECT gr = { 0, 1 };

        dc.GradientFill ( tv, 2, &gr, 1, GRADIENT_FILL_RECT_V );
    }
    else
    {
        TRIVERTEX tv[] = { { rect.left, rect.top, 0xff00 },
        { rect.right, rect.top + m_cxyHeader, 0, 0xff00 } };
        GRADIENT_RECT gr = { 0, 1 };

        dc.GradientFill ( tv, 2, &gr, 1, GRADIENT_FILL_RECT_H );

        rect.bottom = rect.top + m_cxyHeader;

        // draw title only for horizontal pane container
        dc.SaveDC();

        dc.SetTextColor ( RGB(255,255,255) );
        dc.SetBkMode ( TRANSPARENT );
        dc.SelectFont ( GetTitleFont() );

        rect.left += m_cxyTextOffset;
        rect.right -= m_cxyTextOffset;

        if ( m_tb.m_hWnd != NULL )
            rect.right -= m_cxToolBar;

        dc.DrawText ( m_szTitle, -1, &rect, 
            DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS );

        dc.RestoreDC(-1);
    }
}
