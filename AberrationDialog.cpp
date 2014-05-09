// AberrationDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"
#include "AberrationDialog.h"
#include "DMOperator.h"


// CAberrationDialog dialog

IMPLEMENT_DYNAMIC(CAberrationDialog, CDialog)

CAberrationDialog::CAberrationDialog(std::string a2magin,std::string a2angin, bool a2checkin,
									 std::string b2magin,std::string b2angin, bool b2checkin,
									 std::string a3magin,std::string a3angin, bool a3checkin,
									 std::string c3magin, bool c3checkin,
									 std::string s3magin,std::string s3angin, bool s3checkin,
									 std::string b3magin,std::string b3angin, bool b3checkin,
									 std::string a4magin,std::string a4angin, bool a4checkin,
									 std::string s4magin,std::string s4angin, bool s4checkin,
									 std::string a5magin,std::string a5angin, bool a5checkin,
									 std::string s5magin,std::string s5angin, bool s5checkin,
									 CWnd* pParent /*=NULL*/)
	: CDialog(CAberrationDialog::IDD, pParent)
{
	mParent = pParent;
	a2mag=a2magin.c_str();
	a2ang=a2angin.c_str();
	a2check=a2checkin;
	b2mag=b2magin.c_str();
	b2ang=b2angin.c_str();
	b2check=b2checkin;
	a3mag=a3magin.c_str();
	a3ang=a3angin.c_str();
	a3check=a3checkin;
	c3mag=c3magin.c_str();
	c3check=c3checkin;
	s3mag=s3magin.c_str();
	s3ang=s3angin.c_str();
	s3check=s3checkin;
	b3mag=b3magin.c_str();
	b3ang=b3angin.c_str();
	b3check=b3checkin;
	a4mag=a4magin.c_str();
	a4ang=a4angin.c_str();
	a4check=a4checkin;
	s4mag=s4magin.c_str();
	s4ang=s4angin.c_str();
	s4check=s4checkin;
	a5mag=a5magin.c_str();
	a5ang=a5angin.c_str();
	a5check=a5checkin;
	s5mag=s5magin.c_str();
	s5ang=s5angin.c_str();
	s5check=s5checkin;
}

CAberrationDialog::~CAberrationDialog()
{
}

void CAberrationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_A2ANG, a2ang);
	DDX_Check(pDX, IDC_CHECKA2, a2check);
	DDX_Control(pDX, IDC_A2MAG, m_a2mag);
	DDX_Text(pDX, IDC_A2MAG, a2mag);
	DDX_Control(pDX, IDC_A2ANG, m_a2ang);

	DDX_Control(pDX, IDC_B2MAG, m_b2mag);
	DDX_Text(pDX, IDC_B2MAG, b2mag);
	DDX_Control(pDX, IDC_B2ANG, m_b2ang);
	DDX_Text(pDX, IDC_B2ANG, b2ang);
	DDX_Check(pDX, IDC_CHECKB2, b2check);

	DDX_Control(pDX, IDC_A3MAG, m_a3mag);
	DDX_Text(pDX, IDC_A3MAG, a3mag);
	DDX_Control(pDX, IDC_A3ANG, m_a3ang);
	DDX_Text(pDX, IDC_A3ANG, a3ang);
	DDX_Check(pDX, IDC_CHECKA3, a3check);

	DDX_Control(pDX, IDC_C3MAG, m_c3mag);
	DDX_Text(pDX, IDC_C3MAG, c3mag);
	DDX_Check(pDX, IDC_CHECKC3, c3check);

	DDX_Text(pDX, IDC_S3ANG, s3ang);
	DDX_Check(pDX, IDC_CHECKS3, s3check);
	DDX_Control(pDX, IDC_S3MAG, m_s3mag);
	DDX_Text(pDX, IDC_S3MAG, s3mag);
	DDX_Control(pDX, IDC_S3ANG, m_s3ang);

	DDX_Text(pDX, IDC_B3ANG, b3ang);
	DDX_Check(pDX, IDC_CHECKB3, b3check);
	DDX_Control(pDX, IDC_B3MAG, m_b3mag);
	DDX_Text(pDX, IDC_B3MAG, b3mag);
	DDX_Control(pDX, IDC_B3ANG, m_b3ang);

	DDX_Text(pDX, IDC_A4ANG, a4ang);
	DDX_Check(pDX, IDC_CHECKA4, a4check);
	DDX_Control(pDX, IDC_A4MAG, m_a4mag);
	DDX_Text(pDX, IDC_A4MAG, a4mag);
	DDX_Control(pDX, IDC_A4ANG, m_a4ang);

	DDX_Text(pDX, IDC_A5ANG, a5ang);
	DDX_Check(pDX, IDC_CHECKA5, a5check);
	DDX_Control(pDX, IDC_A5MAG, m_a5mag);
	DDX_Text(pDX, IDC_A5MAG, a5mag);
	DDX_Control(pDX, IDC_A5ANG, m_a5ang);

	DDX_Text(pDX, IDC_S4ANG, s4ang);
	DDX_Check(pDX, IDC_CHECKS4, s4check);
	DDX_Control(pDX, IDC_S4MAG, m_s4mag);
	DDX_Text(pDX, IDC_S4MAG, s4mag);
	DDX_Control(pDX, IDC_S4ANG, m_s4ang);

	DDX_Text(pDX, IDC_S5ANG, s5ang);
	DDX_Check(pDX, IDC_CHECKS5, s5check);
	DDX_Control(pDX, IDC_S5MAG, m_s5mag);
	DDX_Text(pDX, IDC_S5MAG, s5mag);
	DDX_Control(pDX, IDC_S5ANG, m_s5ang);
}

void CAberrationDialog::OnOK() 
{
   // TODO: Add extra validation here
   
   // Ensure that your UI got the necessary input 
   // from the user before closing the dialog. The 
   // default OnOK will close this.
   //if ( m_nMyValue == 0 ) // Is a particular field still empty?
   //{
    //  AfxMessageBox("Please enter a value for MyValue");
     // return; // Inform the user that he can't close the dialog without
              // entering the necessary values and don't close the 
              // dialog.
   //}

	UpdateData(true);


	((CDMOperator*)mParent)->UpdateVals
		(
		((LPCTSTR)a2mag),((LPCTSTR)a2ang),a2check,
		((LPCTSTR)b2mag),((LPCTSTR)b2ang),b2check,
		((LPCTSTR)a3mag),((LPCTSTR)a3ang),a3check,
		((LPCTSTR)c3mag),c3check,
		((LPCTSTR)s3mag),((LPCTSTR)s3ang),s3check,
		((LPCTSTR)b3mag),((LPCTSTR)b3ang),b3check,
		((LPCTSTR)a4mag),((LPCTSTR)a4ang),a4check,
		((LPCTSTR)s4mag),((LPCTSTR)s4ang),s4check,
		((LPCTSTR)a5mag),((LPCTSTR)a5ang),a5check,
		((LPCTSTR)s5mag),((LPCTSTR)s5ang),s5check
		
		);

   CDialog::OnOK(); // This will close the dialog and DoModal will return.
}

BEGIN_MESSAGE_MAP(CAberrationDialog, CDialog)
END_MESSAGE_MAP()


// CAberrationDialog message handlers
