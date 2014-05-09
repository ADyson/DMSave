#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDMOperator dialog

class CDMOperator : public CDialog
{
	DECLARE_DYNCREATE(CDMOperator)

public:
	CDMOperator(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDMOperator();
	int pathSet;
	std::string filepath;

	std::string OperatorName;
	std::string SpecimenName;
	std::string AreaNumber;



// Dialog Data
	enum { IDD = IDD_OPERATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(UINT templateID, CWnd* pParentWnd = NULL);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CSpinButtonCtrl m_Spin;
	CComboBox m_OperatorCombo;
	CEdit m_Specimen;
	CEdit m_Area;
	CEdit m_desc;
	CString desc;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEditUpdate();
	afx_msg void OnEditUpdateSpecimen();
	afx_msg void OnEditUpdateArea();
	afx_msg void OnComboChange();

	void UpdateVals(std::string a2magout,std::string a2angout,bool a2checkout,
					std::string b2magout,std::string b2angout,bool b2checkout,
					std::string a3magout,std::string a3angout,bool a3checkout,
					std::string c3magout,bool c3checkout,
					std::string s3magout,std::string s3angout,bool s3checkout,
					std::string b3magout,std::string b3angout,bool b3checkout,
					std::string a4magout,std::string a4angout,bool a4checkout,
					std::string s4magout,std::string s4angout,bool s4checkout,
					std::string a5magout,std::string a5angout,bool a5checkout,
					std::string s5magout,std::string s5angout,bool s5checkout
					
					);

	void AddAberrationTags(DM::TagGroup imagetags);

	std::string a2mag;
	std::string a2ang;
	bool a2check;
	std::string b2mag;
	std::string b2ang;
	bool b2check;
	std::string a3mag;
	std::string a3ang;
	bool a3check;
	std::string c3mag;
	bool c3check;
	std::string s3mag;
	std::string s3ang;
	bool s3check;
	std::string b3mag;
	std::string b3ang;
	bool b3check;
	std::string a4mag;
	std::string a4ang;
	bool a4check;
	std::string s4mag;
	std::string s4ang;
	bool s4check;
	std::string a5mag;
	std::string a5ang;
	bool a5check;
	std::string s5mag;
	std::string s5ang;
	bool s5check;
};
