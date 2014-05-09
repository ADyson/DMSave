// TestDialog1.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"
#include "TestDialog1.h"


// CTestDialog1 dialog

IMPLEMENT_DYNAMIC(CTestDialog1, CDialog)
CTestDialog1::CTestDialog1( const std::string &str_val_1, CWnd* pParent /*=NULL*/)
	: CDialog(CTestDialog1::IDD, pParent)
	, m_StringValue1( str_val_1.c_str() )
{
}

CTestDialog1::~CTestDialog1()
{
}

void CTestDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Text( pDX, IDC_STRING_VALUE_1_EDIT, m_StringValue1 );
}


BEGIN_MESSAGE_MAP(CTestDialog1, CDialog)
END_MESSAGE_MAP()


// CTestDialog1 message handlers
