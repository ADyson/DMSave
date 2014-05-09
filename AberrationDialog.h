#pragma once
#include "numedit.h"


// CAberrationDialog dialog

class CAberrationDialog : public CDialog
{
	DECLARE_DYNAMIC(CAberrationDialog)

public:
	CAberrationDialog(std::string a2magin,std::string a2angin, bool a2checkin,
					  std::string b2magin,std::string b2angin, bool b2checkin, 
					  std::string a3magin,std::string a3angin, bool a3checkin, 
					  std::string c3magin, bool c3checkin, 
					  std::string s3magin,std::string s3angin, bool s3checkin, 
					  std::string b3magin,std::string b3angin, bool b3checkin, 
					  std::string a4magin,std::string a4angin, bool a4checkin,
					  std::string s4magin,std::string s4angin, bool s4checkin, 
					  std::string a5magin,std::string a5angin, bool a5checkin,
					  std::string s5magin,std::string s5angin, bool s5checkin, 
					  CWnd* pParent = NULL);   // standard constructor
	virtual ~CAberrationDialog();
	virtual void OnOK();
	

// Dialog Data
	enum { IDD = IDD_ABDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	CWnd* mParent;
	
	DECLARE_MESSAGE_MAP()
	CString a2mag;
	CString a2ang;
	BOOL a2check;
	CNumEdit m_a2mag;
	CNumEdit m_a2ang;

	CNumEdit m_b2mag;
	CString b2mag;
	CNumEdit m_b2ang;
	CString b2ang;
	BOOL b2check;

	CNumEdit m_a3mag;
	CString a3mag;
	CNumEdit m_a3ang;
	CString a3ang;
	BOOL a3check;

	CNumEdit m_c3mag;
	CString c3mag;
	BOOL c3check;

	CNumEdit m_s3mag;
	CString s3mag;
	CNumEdit m_s3ang;
	CString s3ang;
	BOOL s3check;

	CNumEdit m_b3mag;
	CString b3mag;
	CNumEdit m_b3ang;
	CString b3ang;
	BOOL b3check;

	CNumEdit m_a4mag;
	CString a4mag;
	CNumEdit m_a4ang;
	CString a4ang;
	BOOL a4check;

	CNumEdit m_s4mag;
	CString s4mag;
	CNumEdit m_s4ang;
	CString s4ang;
	BOOL s4check;

	CNumEdit m_a5mag;
	CString a5mag;
	CNumEdit m_a5ang;
	CString a5ang;
	BOOL a5check;

	CNumEdit m_s5mag;
	CString s5mag;
	CNumEdit m_s5ang;
	CString s5ang;
	BOOL s5check;
};
