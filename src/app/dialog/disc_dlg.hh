/*
 * InfraRecorder - CD/DVD burning software
 * Copyright (C) 2006-2012 Christian Kindahl
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <ckmmc/device.hh>
#include "disc_general_page.hh"

class CDiscDlg : public CPropertySheetImpl<CDiscDlg>
{
private:
    bool m_bCentered;

    CDiscGeneralPage m_GeneralPage;

public:
    CDiscDlg(const TCHAR *szTitle,const TCHAR *szDiscLabel,ckmmc::Device &Device);
    ~CDiscDlg();

    BEGIN_MSG_MAP(CDiscDlg)
        MESSAGE_HANDLER(WM_SHOWWINDOW,OnShowWindow)
        CHAIN_MSG_MAP(CPropertySheetImpl<CDiscDlg>)
    END_MSG_MAP()

    LRESULT OnShowWindow(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
};
