/**
 * @file    CustomPaneContainer.h
 * @author  Zhan WANG <wangzhan.1985@gmail.com>
 */
#pragma once

 /**
  * @class   CCustomPaneContainer
  * @brief   custom pane container
  */
class CCustomPaneContainer : public CPaneContainerImpl<CCustomPaneContainer>
{
public:
    DECLARE_WND_CLASS_EX(_T("CustomPaneContainer"), 0, -1)

    CCustomPaneContainer();

    // Operations
    void EnableColoredHeader ( bool bEnable = true );

    // Overrides
    BOOL GetToolTipText(LPNMHDR lpnmh);
    void DrawPaneTitle(CDCHandle dc);

    // NOTE: There is a bug in CPaneContainer that prevents this from being
    // called after you switch the container to vertical mode. Change
    // CalcSize() to pT->CalcSize() in CPaneContainer::SetPaneContainerExtendedStyle()
    void CalcSize() { m_cxyHeader = 40; }

protected:
    bool m_bColoredHeader;
};
