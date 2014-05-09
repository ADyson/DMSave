#pragma once

#include "PropPageTest1.h"
#include "PropPageTest2.h"

// CPropSheetChildTest

class CPropSheetChildTest : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropSheetChildTest)

public:
	CPropSheetChildTest(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPropSheetChildTest(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CPropSheetChildTest();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CPropPageTest1 m_Page1;
	CPropPageTest2 m_Page2;

};


