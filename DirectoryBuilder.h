#pragma once

#include "c:\program files (x86)\microsoft visual studio 9.0\vc\atlmfc\include\afxwin.h"
#include "afxcmn.h"



// DirectoryBuilder dialog

class DirectoryBuilder : public CDialog
{
	DECLARE_DYNAMIC(DirectoryBuilder)

public:
	DirectoryBuilder(CWnd* pParent = NULL);   // standard constructor
	DirectoryBuilder(int a, int b, int c, CWnd* pParent = NULL);
	virtual ~DirectoryBuilder();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()
public:
	int a,b,c;

	virtual BOOL Create(UINT templateID, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	CWnd* mParent;
	CComboBox path1;
	CComboBox path2;
	CComboBox path3;
	afx_msg void OnBnClickedOk();
};
