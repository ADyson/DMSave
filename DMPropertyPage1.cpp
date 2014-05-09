// DMPropertyPage1.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"
#include "DMPropertyPage1.h"


// CDMPropertyPage1 dialog

IMPLEMENT_DYNAMIC(CDMPropertyPage1, CPropertyPage)
CDMPropertyPage1::CDMPropertyPage1()
	: CPropertyPage(CDMPropertyPage1::IDD)
{
}

CDMPropertyPage1::~CDMPropertyPage1()
{
}

void CDMPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDMPropertyPage1, CPropertyPage)
	ON_BN_CLICKED(IDC_ONIONS_BUTTON, OnBnClickedOnionsButton)
END_MESSAGE_MAP()


// CDMPropertyPage1 message handlers

#include "PropSheetChildTest.h"
void CDMPropertyPage1::OnBnClickedOnionsButton()
{
	GTN_AFX_MANAGE_STATE()
	// TODO: Add your control notification handler code here
	CPropSheetChildTest myPropSheetChildTest("test", this);
	myPropSheetChildTest.DoModal();
}
