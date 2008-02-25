/*
 * Copyright (C) 2006-2008 Christian Kindahl, christian dot kindahl at gmail dot com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "stdafx.h"
#include "../../Source/Common/StringUtil.h"
#include "../../Source/Common/FileManager.h"
#include "Settings.h"

typedef struct _stack_t {
	struct _stack_t *pNext;
	char szText[1];				// This should be the length of iStringSize.
} stack_t;

BOOL APIENTRY DllMain(HANDLE hModule, 
                      DWORD  ul_reason_for_call, 
                      LPVOID lpReserved)
{
    return TRUE;
}

bool GetConfigPath(TCHAR *szConfigPath)
{
#ifdef UNICODE
	if (!SUCCEEDED(SHGetFolderPath(HWND_DESKTOP,CSIDL_APPDATA | CSIDL_FLAG_CREATE,NULL,
		SHGFP_TYPE_CURRENT,szConfigPath)))
		return false;
#else	// Win 9x.
	if (!SUCCEEDED(SHGetSpecialFolderPath(HWND_DESKTOP,szConfigPath,CSIDL_APPDATA,true)))
		return false;
#endif
	IncludeTrailingBackslash(szConfigPath);
	lstrcat(szConfigPath,_T("InfraRecorder\\"));

	// Create the file path if it doesn't exist.
	fs_createpath(szConfigPath);

	lstrcat(szConfigPath,_T("Settings.xml"));
	return true;
}

void __declspec(dllexport) CreateConfig(HWND hWndParent,int iStringSize,
										char *szVariables,stack_t **ppStackTop)
{
	// The config file name is on the top of the stack.
	TCHAR szConfigFileName[MAX_PATH];
	stack_t *pStackEntry = *ppStackTop;
	//CharToTChar(pStackEntry->szText,szConfigFileName);

	// UPDATE: The first is now ignored since the configuration file is
	// stored in a common place.
	GetConfigPath(szConfigFileName);

	pStackEntry = pStackEntry->pNext;
	CharToTChar(pStackEntry->szText,g_LanguageSettings.m_szLanguageFile);

	// Only create new config file if one does not already exist.
	if (!fs_fileexists(szConfigFileName))
	{
		// Save the config file.
		CXMLProcessor XML;

		XML.AddElement(_T("InfraRecorder"),_T(""),true);
			XML.AddElement(_T("Settings"),_T(""),true);
				g_LanguageSettings.Save(&XML);
			XML.LeaveElement();
		XML.LeaveElement();

		XML.Save(szConfigFileName);
	}
}
