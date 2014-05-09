#pragma once


// CDMPropertyPage1 dialog

class CDMPropertyPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CDMPropertyPage1)

public:
	CDMPropertyPage1();
	virtual ~CDMPropertyPage1();

// Dialog Data
	enum { IDD = IDD_DMPROPERTYPAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOnionsButton();
};
