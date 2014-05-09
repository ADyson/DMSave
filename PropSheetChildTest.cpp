// PropSheetChildTest.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"
#include "PropSheetChildTest.h"


// CPropSheetChildTest

IMPLEMENT_DYNAMIC(CPropSheetChildTest, CPropertySheet)
CPropSheetChildTest::CPropSheetChildTest(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CPropSheetChildTest::CPropSheetChildTest(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_Page1);
	AddPage(&m_Page2);
}

CPropSheetChildTest::~CPropSheetChildTest()
{
}


BEGIN_MESSAGE_MAP(CPropSheetChildTest, CPropertySheet)
END_MESSAGE_MAP()


// CPropSheetChildTest message handlers
