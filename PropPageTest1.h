#pragma once


// CPropPageTest1 dialog

class CPropPageTest1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropPageTest1)

public:
	CPropPageTest1();
	virtual ~CPropPageTest1();

// Dialog Data
	enum { IDD = IDD_PROPPAGETEST1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
