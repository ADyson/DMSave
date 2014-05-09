#pragma once

#include <string>

// CTestDialog1 dialog

class CTestDialog1 : public CDialog
{
	DECLARE_DYNAMIC(CTestDialog1)

public:
	CTestDialog1( const std::string &str_val_1, CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestDialog1();

// Dialog Data
	enum { IDD = IDD_TESTDIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString m_StringValue1;
};
