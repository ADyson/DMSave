// DirectoryBuilder.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"
#include "DirectoryBuilder.h"
#include "DMOperator.h"


// DirectoryBuilder dialog

IMPLEMENT_DYNAMIC(DirectoryBuilder, CDialog)

DirectoryBuilder::DirectoryBuilder(CWnd* pParent /*=NULL*/)
	: CDialog(DirectoryBuilder::IDD, pParent)
{
	a=1;
	b=0;
	c=2;
	mParent = pParent;
}

DirectoryBuilder::DirectoryBuilder(int a, int b, int c, CWnd* pParent /*=NULL*/)
	: CDialog(DirectoryBuilder::IDD, pParent)
{
	this->a=a;
	this->b=b;
	this->c=c;

	mParent = pParent;
}

DirectoryBuilder::~DirectoryBuilder()
{
}

BOOL DirectoryBuilder::Create(UINT templateID, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base clase
	return CDialog::Create(IDD, pParentWnd);
}

void DirectoryBuilder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, path1);
	DDX_Control(pDX, IDC_COMBO2, path2);
	DDX_Control(pDX, IDC_COMBO3, path3);
}


BEGIN_MESSAGE_MAP(DirectoryBuilder, CDialog)
	ON_BN_CLICKED(IDOK, &DirectoryBuilder::OnBnClickedOk)
END_MESSAGE_MAP()


// DirectoryBuilder message handlers


void DirectoryBuilder::OnBnClickedOk()
{
	CDMOperator* pp = (CDMOperator*)mParent;

	pp->pathorder[0] = path1.GetCurSel();
	pp->pathorder[1] = path2.GetCurSel();
	pp->pathorder[2] = path3.GetCurSel();

	pp->SavePathOrder();

	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

BOOL DirectoryBuilder::OnInitDialog()
{
	CDialog::OnInitDialog();

	path1.AddString("Date");
	path2.AddString("Date");
	path3.AddString("Date");

	path1.AddString("Specimen");
	path2.AddString("Specimen");
	path3.AddString("Specimen");

	path1.AddString("Area");
	path2.AddString("Area");
	path3.AddString("Area");

	path1.SetCurSel(a);
	path2.SetCurSel(b);
	path3.SetCurSel(c);

	return TRUE;
}
