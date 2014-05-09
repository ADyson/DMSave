// DMPropertyPage2.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"
#include "DMPropertyPage2.h"
#include "TestDialog1.h"

// CDMPropertyPage2 dialog

IMPLEMENT_DYNAMIC(CDMPropertyPage2, CPropertyPage)
CDMPropertyPage2::CDMPropertyPage2()
	: CPropertyPage(CDMPropertyPage2::IDD)
{
}

CDMPropertyPage2::~CDMPropertyPage2()
{
}

void CDMPropertyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDMPropertyPage2, CPropertyPage)
	ON_BN_CLICKED(IDC_CARROTS_BUTTON, OnBnClickedCarrotsButton)
END_MESSAGE_MAP()


// CDMPropertyPage2 message handlers

void CDMPropertyPage2::OnBnClickedCarrotsButton()
{
	GTN_AFX_MANAGE_STATE()
	CTestDialog1 dlg( "Carrots" );
	dlg.DoModal();
}
