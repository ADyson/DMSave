#pragma once

#include "DMPropertyPage1.h"
#include "DMPropertyPage2.h"

// CDMPropertySheet

class CDMPropertySheet : public CPropertySheet
{
	//DECLARE_DYNAMIC(CDMPropertySheet)
	DECLARE_DYNCREATE(CDMPropertySheet)

public:
	CDMPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDMPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDMPropertySheet():CPropertySheet("")
	{
		AddPage(&m_Page1);
		AddPage(&m_Page2);
	}
	virtual ~CDMPropertySheet();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CDMPropertyPage1 m_Page1;
	CDMPropertyPage2 m_Page2;
public:
	virtual BOOL OnInitDialog();
};


