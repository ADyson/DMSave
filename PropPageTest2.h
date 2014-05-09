#pragma once


// CPropPageTest2 dialog

class CPropPageTest2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropPageTest2)

public:
	CPropPageTest2();
	virtual ~CPropPageTest2();

// Dialog Data
	enum { IDD = IDD_PROPPAGETEST2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
