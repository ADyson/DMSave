// DMPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"
#include "DMPropertySheet.h"


// CDMPropertySheet

IMPLEMENT_DYNCREATE(CDMPropertySheet, CPropertySheet)
//IMPLEMENT_DYNAMIC(CDMPropertySheet, CPropertySheet)
CDMPropertySheet::CDMPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CDMPropertySheet::CDMPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CDMPropertySheet::~CDMPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CDMPropertySheet, CPropertySheet)
END_MESSAGE_MAP()


// CDMPropertySheet message handlers

/*
 *	It the property sheet is attached to an existing DM floating window, the window will expand
 *	to accommodate the new panel. CPropertySheets are set to the maximum size of the child
 *	CPropertyPages, however, the minimum size is the width of the four standard property page
 *	buttons- 'help, apply, ok, cancel'. For narrow property pages we override this default
 *	minimum in OnInitDialog.
 */

BOOL CDMPropertySheet::OnInitDialog() 
{
	HWND hWnd = (HWND)::GetDlgItem(m_hWnd, AFX_IDC_TAB_CONTROL);
	ASSERT(hWnd != NULL);

	CRect rectOld;
	::GetWindowRect(hWnd, &rectOld);
	ScreenToClient(rectOld);
	int nCy = rectOld.Width()/2;
	rectOld.right -= nCy;

	// move tab control
	::SetWindowPos(hWnd, NULL, 0, 0,rectOld.Width(), rectOld.Height(), SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	GetWindowRect(&rectOld);
	rectOld.right -= nCy;
	SetWindowPos(NULL, 0, 0, rectOld.Width(), rectOld.Height(),SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	return CPropertySheet::OnInitDialog();
}
