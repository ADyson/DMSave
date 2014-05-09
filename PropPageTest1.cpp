// PropPageTest1.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"
#include "PropPageTest1.h"


// CPropPageTest1 dialog

IMPLEMENT_DYNAMIC(CPropPageTest1, CPropertyPage)
CPropPageTest1::CPropPageTest1()
	: CPropertyPage(CPropPageTest1::IDD)
{
}

CPropPageTest1::~CPropPageTest1()
{
}

void CPropPageTest1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropPageTest1, CPropertyPage)
END_MESSAGE_MAP()


// CPropPageTest1 message handlers
