#pragma once


// CDMPropertyPage2 dialog

class CDMPropertyPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CDMPropertyPage2)

public:
	CDMPropertyPage2();
	virtual ~CDMPropertyPage2();

// Dialog Data
	enum { IDD = IDD_DMPROPERTYPAGE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCarrotsButton();
};
