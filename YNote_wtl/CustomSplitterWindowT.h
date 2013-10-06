/**
 * @file    CustomSplitterWindowT.h
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#pragma once

 /**
  * @class   CCustomSplitterWindowT
  * @brief   custom splitter window
  */
template <bool t_bVertical = true>
class CCustomSplitterWindowT : public CSplitterWindowImpl<CCustomSplitterWindowT<t_bVertical>, t_bVertical>
{
public:
    DECLARE_WND_CLASS_EX(_T("CustomSplitterWindowT"), CS_DBLCLKS, COLOR_WINDOW)

    CCustomSplitterWindowT() : m_bPatternBar(false)
    { }

    // Operations
    void EnablePatternBar ( bool bEnable = true )
    {
        if ( bEnable != m_bPatternBar )
        {
            m_bPatternBar = bEnable;
            UpdateSplitterLayout();
        }
    }

    // Overrideables
    void DrawSplitterBar(CDCHandle dc)
    {
        RECT rect;

        // If we're not using a colored bar, let the base class do the
        // default drawing.
        if ( !m_bPatternBar )
        {
            CSplitterWindowImpl<CCustomSplitterWindowT<t_bVertical>, t_bVertical>::DrawSplitterBar(dc);
            return;
        }

        // Create a brush to paint with, if we haven't already done so.
        if ( m_br.IsNull() )
            m_br.CreateHatchBrush ( HS_DIAGCROSS, 
            t_bVertical ? RGB(255,0,0) : RGB(0,0,255) );

        if ( GetSplitterBarRect ( &rect ) )
        {
            dc.FillRect ( &rect, m_br );

            // draw 3D edge if needed
            if ( (GetExStyle() & WS_EX_CLIENTEDGE) != 0)
                dc.DrawEdge(&rect, EDGE_RAISED, t_bVertical ? (BF_LEFT | BF_RIGHT) : (BF_TOP | BF_BOTTOM));
        }
    }

protected:
    CBrush m_br;
    bool   m_bPatternBar;
};

typedef CCustomSplitterWindowT<true>    CVerCustomSplitterWindow;
typedef CCustomSplitterWindowT<false>   CHorCustomSplitterWindowT;
