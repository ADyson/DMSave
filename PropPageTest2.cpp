// PropPageTest2.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"
#include "PropPageTest2.h"


// CPropPageTest2 dialog

IMPLEMENT_DYNAMIC(CPropPageTest2, CPropertyPage)
CPropPageTest2::CPropPageTest2()
	: CPropertyPage(CPropPageTest2::IDD)
{
}

CPropPageTest2::~CPropPageTest2()
{
}

void CPropPageTest2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropPageTest2, CPropertyPage)
END_MESSAGE_MAP()


// CPropPageTest2 message handlers
