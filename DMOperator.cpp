// DMDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"
#include "DMOperator.h"
#include "AberrationDialog.h"
#include "DirectoryBuilder.h"
#include "shlobj.h"
#include <sstream>
#include "boost\lexical_cast.hpp"


enum NameBlocks
{
	Date,
	Specimen,
	Area
};

template<class T>
    T fromString(const std::string& s)
{
     std::istringstream stream (s);
     T t;
     stream >> t;
     return t;
}

 bool GetFolder(std::string& folderpath, const char* szCaption = NULL, HWND hOwner = NULL)
{
	bool retVal = false;

	// The BROWSEINFO struct tells the shell 
	// how it should display the dialog.
	BROWSEINFO bi;
	memset(&bi, 0, sizeof(bi));

	bi.ulFlags   = BIF_USENEWUI;
	bi.hwndOwner = hOwner;
	bi.lpszTitle = szCaption;

	// must call this if using BIF_USENEWUI
	::OleInitialize(NULL);

	// Show the dialog and get the itemIDList for the selected folder.
	LPITEMIDLIST pIDL = ::SHBrowseForFolder(&bi);

	if(pIDL != NULL)
	{
	   // Create a buffer to store the path, then get the path.
	   char buffer[_MAX_PATH] = {'\0'};
	   if(::SHGetPathFromIDList(pIDL, buffer) != 0)
	   {
		   // Set the string value.
		   folderpath = buffer;
		   retVal = true;
	   }       

	   // free the item id list
	   CoTaskMemFree(pIDL);
	}

	::OleUninitialize();

	return retVal;
}

 std::string FormattedMag(float mag)
{
			if ( mag < 1000000 )
			{
				std::stringstream out;
				out << mag/1000;
				out << "k" ;
				return out.str();
			}
			
			else 
			{
				std::stringstream out;
				out << mag/1000000;
				out << "M" ;
				return out.str();
			};
}


std::string FormattedMagED(float mag)
{
				std::stringstream out;
				out << "ED";
				out << mag/10;
				out << "cm" ;
				return out.str();
}


// CDMOperator dialog 

IMPLEMENT_DYNCREATE(CDMOperator, CDialog)
CDMOperator::CDMOperator(CWnd* pParent /*=NULL*/)
	: CDialog(CDMOperator::IDD, pParent)
{
}

CDMOperator::~CDMOperator()
{
	DigitalMicrograph::TagGroup pers;
	pers = DigitalMicrograph::GetPersistentTagGroup();

	pers.DeleteTagWithLabel("Operator Panel:Area");
	pers.DeleteTagWithLabel("Operator Panel:filepath");
}

void CDMOperator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPINAREABUTTON, m_Spin);
	DDX_Control(pDX, IDC_COMBO1, m_OperatorCombo);
	DDX_Control(pDX, IDC_SPECIMENEDIT, m_Specimen);
	DDX_Control(pDX, IDC_AREAEDITSPIN, m_Area);
	DDX_Control(pDX, IDC_EDIT2, m_desc);
	DDX_Text(pDX,IDC_EDIT2,desc);
}


BEGIN_MESSAGE_MAP(CDMOperator, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON2, &CDMOperator::OnBnClickedButton2)
	ON_CBN_EDITUPDATE(IDC_COMBO1, OnEditUpdate)
	ON_EN_UPDATE(IDC_SPECIMENEDIT, OnEditUpdateSpecimen)
	ON_EN_UPDATE(IDC_AREAEDITSPIN, OnEditUpdateArea)
	ON_CBN_SELCHANGE(IDC_COMBO1,OnComboChange)
	ON_BN_CLICKED(IDC_BUTTON4, &CDMOperator::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDMOperator::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDMDialog message handlers

BOOL CDMOperator::Create(UINT templateID, CWnd* pParentWnd)
{
	// TODO: Add your specialized code here and/or call the base clase
	return CDialog::Create(IDD, pParentWnd);
}

BOOL CDMOperator::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        if ((pMsg->wParam == VK_RETURN) || (pMsg->wParam == VK_ESCAPE))
            pMsg->wParam = VK_TAB;
    }
    return CDialog::PreTranslateMessage(pMsg);
}



BOOL CDMOperator::OnInitDialog()
{
	// No Folder Specified Yet
	pathSet = 0;

	CDialog::OnInitDialog();

	m_Spin.SetRange(1, 40);
	m_Spin.SetPos(1);

	// Check if the number of operators has been set, if not set it to zero;
	DigitalMicrograph::TagGroup pers;
	pers = DigitalMicrograph::GetPersistentTagGroup();


	DigitalMicrograph::String NumUsersDM;
	//std::string NumUsers;
	
	pathorder = new int[3];

	pathorder[0] = NameBlocks::Specimen;
	pathorder[1] = NameBlocks::Date;
	pathorder[2] = NameBlocks::Area;


	if (DigitalMicrograph::TagGroupDoesTagExist(pers,"Operator Panel:Users"))
	{
		DigitalMicrograph::TagGroupGetTagAsString(pers,"Operator Panel:Users",NumUsersDM);
	}
	else
	{
		DigitalMicrograph::TagGroupSetTagAsString(pers,"Operator Panel:Users","0");
		NumUsersDM = "0";
	}

	try
	{
		NumUsers = boost::lexical_cast<int>(NumUsersDM);
	}
	catch(...)
	{
		NumUsers=0;
	}


	// TODO:  Add extra initialization here
	ModifyStyle(0, WS_GROUP | WS_TABSTOP);

	// Get list of installed operators and there custom settings...
	for(int i = 0; i < NumUsers; i++)
	{
		std::string usertagpath = "Operator Panel:UserDirs:"+boost::lexical_cast<std::string>(i);
		std::string usertagpath2 = "Operator Panel:UserNames:"+boost::lexical_cast<std::string>(i);

		std::string usertagpath3 = "Operator Panel:UserPathOrders:"+boost::lexical_cast<std::string>(i)+":0";
		std::string usertagpath4 = "Operator Panel:UserPathOrders:"+boost::lexical_cast<std::string>(i)+":1";
		std::string usertagpath5 = "Operator Panel:UserPathOrders:"+boost::lexical_cast<std::string>(i)+":2";
		
		DigitalMicrograph::String UserName;
		DigitalMicrograph::String UserDirectory;
		DigitalMicrograph::String UserPathOrder1;
		DigitalMicrograph::String UserPathOrder2;
		DigitalMicrograph::String UserPathOrder3;

		DigitalMicrograph::TagGroupGetTagAsString(pers,usertagpath2.c_str(),UserName);
		DigitalMicrograph::TagGroupGetTagAsString(pers,usertagpath.c_str(),UserDirectory);
		DigitalMicrograph::TagGroupGetTagAsString(pers,usertagpath3.c_str(),UserPathOrder1);
		DigitalMicrograph::TagGroupGetTagAsString(pers,usertagpath4.c_str(),UserPathOrder2);
		DigitalMicrograph::TagGroupGetTagAsString(pers,usertagpath5.c_str(),UserPathOrder3);

		UserNames.push_back(UserName);
		UserDirectories.push_back(UserDirectory);
		
		std::vector<int> temppathorder;
		temppathorder.push_back(boost::lexical_cast<int>(UserPathOrder1));
		temppathorder.push_back(boost::lexical_cast<int>(UserPathOrder2));
		temppathorder.push_back(boost::lexical_cast<int>(UserPathOrder3));
					
		UserPathOrders.push_back(temppathorder);
	}


	InsertSavedNames();
	//Default aberrations to zero is uneccessary?

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDMOperator::InsertSavedNames()
{
	DigitalMicrograph::TagGroup pers;
	pers = DigitalMicrograph::GetPersistentTagGroup();

	for(int i = 0; i < NumUsers; i++)
	{
		m_OperatorCombo.AddString(UserNames[i].c_str());
	}
	
}

void CDMOperator::LoadCustomDirectory(int user)
{
	DigitalMicrograph::TagGroup pers;
	pers = DigitalMicrograph::GetPersistentTagGroup();

	filepath = UserDirectories[user];
	DigitalMicrograph::TagGroupSetTagAsString(pers,"Operator Panel:filepath",filepath);
	pathSet=TRUE;
}

// This button implements the save image code, which auto tags and
// saves images to a relevant directory structure.
void CDMOperator::OnBnClickedButton3()
{
	
	UpdateData(TRUE);

	//CWnd* pWnd=GetParent();
	//BOOL success=pWnd->ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	// First check to see if we have set the root directory
	if(pathSet==0)
	{
		DM::OpenAndSetProgressWindow("Root Directory","Not Specified",":(");
		return;
	}

	// Now make sure the directory actually exists (could be removable media)
	if(!DM::DoesDirectoryExist( filepath ))
	{
		DM::OpenAndSetProgressWindow("Root Directory","Not Available",":(");
		return;
	}

	//Good to go

	// Find out todays date
	CTime theTime;
	
	theTime = CTime::GetCurrentTime();

	CString date = theTime.Format( "%d %B %Y" );

	std::string datestring = ((LPCTSTR)date);


	std::vector<std::string> pathbuilder;

	pathbuilder.push_back(datestring);
	pathbuilder.push_back(SpecimenName);
	pathbuilder.push_back("Area "+AreaNumber);
	
	// Path order set to default or changed via dialog...
	
	if(!DM::DoesDirectoryExist(filepath+"\\"+pathbuilder[pathorder[0]]))
		DM::CreateDirectory(filepath+"\\"+pathbuilder[pathorder[0]]);
		
	if(!DM::DoesDirectoryExist(filepath+"\\"+pathbuilder[pathorder[0]]+"\\"+pathbuilder[pathorder[1]]))
		DM::CreateDirectory(filepath+"\\"+pathbuilder[pathorder[0]]+"\\"+pathbuilder[pathorder[1]]);
			
	if(!DM::DoesDirectoryExist(filepath+"\\"+pathbuilder[pathorder[0]]+"\\"+pathbuilder[pathorder[1]]+"\\"+pathbuilder[pathorder[2]]))
		DM::CreateDirectory(filepath+"\\"+pathbuilder[pathorder[0]]+"\\"+pathbuilder[pathorder[1]]+"\\"+pathbuilder[pathorder[2]]);

	DM::Image frontim;
	
	if(!GetFrontImage( frontim ))
	{
		DM::OpenAndSetProgressWindow("No Front Image","",":(");
		return;
	}

	// Continue with Front Image

	// Get Data from Tags in Image
	
	DM::TagGroup pers;

	try
	{
		 pers =  DM::ImageGetTagGroup(frontim);
	}
	catch(...)
	{
		DM::OpenAndSetProgressWindow("Can't Get Image Tag Group","",":(");
		return;
	}

	DM::String indicatedMagG;
	std::string indicatedMag;
	DM::TagGroupGetTagAsString(pers,"Microscope Info:Indicated Magnification",indicatedMagG);
	indicatedMag=indicatedMagG;
	float numberMag = fromString<float>(indicatedMag);
	

	DM::String acqTimeG;
	std::string acqTime;
	DM::TagGroupGetTagAsString(pers,"DataBar:Acquisition Time",acqTimeG);
	acqTime=acqTimeG;

	DM::String acqDateG;
	std::string acqDate;
	DM::TagGroupGetTagAsString(pers,"DataBar:Acquisition Date",acqDateG);
	acqDate=acqDateG;

	DM::String operationModeG;
	std::string operationMode;
	DM::TagGroupGetTagAsString(pers,"Microscope Info:Operation Mode",operationModeG);
	operationMode=operationModeG;

	DM::String voltageG;
	std::string voltage;
	DM::TagGroupGetTagAsString(pers,"Microscope Info:Voltage",voltageG);
	voltage = voltageG;

	DM::String expTimeG;
	std::string expTime;
	DM::TagGroupGetTagAsString(pers,"DataBar:Exposure Time (s)",expTimeG);
	expTime=expTimeG;

	DM::String binningG;
	std::string binning;
	DM::TagGroupGetTagAsString(pers,"DataBar:Binning",binningG);
	binning = binningG;


	try
	{
		// Now add data to extra Image Tags
		DM::TagGroupSetTagAsString(pers,"Microscope Info:Operator",OperatorName);
		DM::TagGroupSetTagAsString(pers,"Microscope Info:Specimen",SpecimenName);
		DM::TagGroupSetTagAsString(pers,"Operator Panel:Area",AreaNumber);
		// This might have been changed in newer version 2.30?
		//DM::TagGroupSetTagAsString(pers,"Microscope Info:Items:[1]:Value",OperatorName);
		//DM::TagGroupSetTagAsString(pers,"Microscope Info:Items:[0]:Value",SpecimenName);
	}
	catch(...)
	{
		DM::OpenAndSetProgressWindow("Problem Adding Image Tags","","");
		return;
	}


	// Count number of files already in directory
	DM::TagGroup FilesInDir = DM::GetFilesInDirectory(filepath+"\\"+pathbuilder[pathorder[0]]+"\\"+pathbuilder[pathorder[1]]+"\\"+pathbuilder[pathorder[2]], 1 );
	int Files = DM::TagGroupCountTags(FilesInDir);
	Files++;

	std::stringstream numoffiles;
	numoffiles << Files;

	AddAberrationTags(pers);

	frontim.SetDescriptionText(desc);
	
	std::string description;

	// Only add dashes if description isnt blank...
	if(desc=="")
	{
		description="";
	}
	else
	{
		description = " - "+desc;
	}

	frontim.NotifyTagsChanged();


	if(operationMode=="IMAGING")
		{
			std::string formattedMagnification = FormattedMag(numberMag); 
			std::string nameImg = filepath+"\\"+pathbuilder[pathorder[0]]+"\\"+pathbuilder[pathorder[1]]+"\\"+pathbuilder[pathorder[2]]+"\\"+numoffiles.str()+" - "+SpecimenName+description+" - "+formattedMagnification+" - b"+binning+" - "+expTime+"s";
			frontim.SetName(numoffiles.str()+" - "+acqTime+" "+acqDate+" - "+SpecimenName+description+" - "+formattedMagnification+" - b"+binning+" - "+expTime+"s");
			DM::SaveAsGatan(frontim,nameImg);//Save the image
			DM::OpenAndSetProgressWindow("          Image Saved","","                   :)");

		}

	else if(operationMode=="DIFFRACTION")
		{
			std::string formattedMagnification = FormattedMagED(numberMag); 
			std::string nameImg = filepath+"\\"+pathbuilder[pathorder[0]]+"\\"+pathbuilder[pathorder[1]]+"\\"+pathbuilder[pathorder[2]]+"\\"+numoffiles.str()+" - "+SpecimenName+description+" - "+formattedMagnification+" - b"+binning+" - "+expTime+"s";
			frontim.SetName(numoffiles.str()+" - "+acqTime+" "+acqDate+" - "+SpecimenName+description+" - "+formattedMagnification+" - b"+binning+" - "+expTime+"s");
			DM::SaveAsGatan(frontim,nameImg); //Save the image
			DM::OpenAndSetProgressWindow("          Image Saved","","                   :)");

		}
	
	else if(operationMode=="SCANNING")
		{
			std::string formattedMagnification = FormattedMag(numberMag); 
			std::string nameImg = filepath+"\\"+pathbuilder[pathorder[0]]+"\\"+pathbuilder[pathorder[1]]+"\\"+pathbuilder[pathorder[2]]+"\\"+numoffiles.str()+" - "+SpecimenName+description+" - "+formattedMagnification;
			frontim.SetName(numoffiles.str()+" - "+acqTime+" "+acqDate+" - "+SpecimenName+description+" - "+formattedMagnification);
			DM::SaveAsGatan(frontim,nameImg);//Save the image
			DM::OpenAndSetProgressWindow("          Image Saved","","                   :)");
		}

	else
		{
			DM::OpenAndSetProgressWindow("Unsupported Operation Mode","","");
		}

	DM::ImageDocument imdoc = frontim.GetOrCreateImageDocument();
	imdoc.Clean();

	//Reset description text
	desc="";
	m_desc.SetWindowTextA("");

}

// Launch aberration dialog
void CDMOperator::OnBnClickedButton1()
{
	CAberrationDialog dlg(a2mag,a2ang,a2check,
						  b2mag,b2ang,b2check,
						  a3mag,a3ang,a3check,
						  c3mag,c3check,
						  s3mag,s3ang,s3check,
						  b3mag,b3ang,b3check,
						  a4mag,a4ang,a4check,
						  s4mag,s4ang,s4check,
						  a5mag,a5ang,a5check,
						  s5mag,s5ang,s5check,
						  this);
	dlg.DoModal();

}

void CDMOperator::OnPaint()
{
	/*
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	dc.SelectStockObject(WHITE_BRUSH);
	dc.DrawText("Bla Bla Bla", CRect(0, 0, 50, 50), 0); 

	cide << __FUNCTION__ << std::endl;
	*/
	CDialog::OnPaint();
}

BOOL CDMOperator::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

//std::ostream& operator<<(std::ostream& os, const CRect& rect)
//{
//	return os << "Rect=(" << rect.TopLeft().x << ", " << rect.TopLeft().y << ", " << rect.BottomRight().x << ", " << rect.BottomRight().y << ")";
//}

void CDMOperator::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	std::string szPath("");

	if (GetFolder(szPath, "Select a folder.") == true) 
	{
		pathSet = 1;

		DM::TagGroup pers = DM::GetPersistentTagGroup();
		DM::TagGroupSetTagAsString(pers,"Operator Panel:filepath",szPath);

		filepath = szPath;
	}

	// Check for a user with the same name as this user...
	// If so update their directory
	bool found = false;
	int index = 0;

	for(int i = 0; i < NumUsers; i++)
	{
		if(UserNames[i] == OperatorName)
		{
			found = true;
			index = i;
		}
	}
	
	DigitalMicrograph::TagGroup pers = DigitalMicrograph::GetPersistentTagGroup();

	if(found)
	{
		std::string usertagpath = "Operator Panel:UserDirs:"+boost::lexical_cast<std::string>(index);
		UserDirectories[index] = filepath;
		DigitalMicrograph::TagGroupSetTagAsString(pers,usertagpath.c_str(),filepath);
	}
}

void CDMOperator::OnEditUpdate()
{
	
	CString Operator;

	GetDlgItemText(IDC_COMBO1,Operator);

	std::string Operator2((LPCTSTR)Operator);

	// No Need to Spam Results Window
	//DM::Result("Operator is "+Operator2+"\n");


	DM::TagGroup pers = DM::GetPersistentTagGroup();
	DM::TagGroupSetTagAsString(pers,"Microscope Info:Operator",Operator2);

	OperatorName = Operator2;

}

void CDMOperator::OnComboChange()
{
	// Maybe need some check to make sure selection makes sense
	int item = m_OperatorCombo.GetCurSel();

	if(item!= CB_ERR)
	{
		CString Operator;

		m_OperatorCombo.GetLBText(item,Operator);

		std::string Operator2((LPCTSTR)Operator);

		// No Need to Spam Results Window
		//DM::Result("Operator is "+Operator2+"\n");

		DM::TagGroup pers = DM::GetPersistentTagGroup();
		DM::TagGroupSetTagAsString(pers,"Microscope Info:Operator",Operator2);

		OperatorName = Operator2;
	}

	// Set directory to users saved directory if user picked from combobox
	LoadCustomDirectory(item);
	LoadPathOrder(item);

}

void CDMOperator::OnEditUpdateSpecimen()
{
	
	CString Specimen;

	GetDlgItemText(IDC_SPECIMENEDIT,Specimen);

	std::string Specimen2((LPCTSTR)Specimen);

	// No Need to Spam Results Window
	//DM::Result("Operator is "+Operator2+"\n");


	DM::TagGroup pers = DM::GetPersistentTagGroup();
	DM::TagGroupSetTagAsString(pers,"Microscope Info:Specimen",Specimen2);

	SpecimenName = Specimen2;

}

void CDMOperator::OnEditUpdateArea()
{
	
	CString Area;

	GetDlgItemText(IDC_AREAEDITSPIN,Area);

	std::string Area2((LPCTSTR)Area);

	// No Need to Spam Results Window
	//DM::Result("Operator is "+Operator2+"\n");


	DM::TagGroup pers = DM::GetPersistentTagGroup();
	DM::TagGroupSetTagAsString(pers,"Operator Panel:Area",Area2);

	AreaNumber = Area2;

	

}

void CDMOperator::UpdateVals(std::string a2magout,std::string a2angout,bool a2checkout,
							 std::string b2magout,std::string b2angout,bool b2checkout,
							 std::string a3magout,std::string a3angout,bool a3checkout,
							 std::string c3magout,bool c3checkout,
							 std::string s3magout,std::string s3angout,bool s3checkout,
							 std::string b3magout,std::string b3angout,bool b3checkout,
							 std::string a4magout,std::string a4angout,bool a4checkout,
							 std::string s4magout,std::string s4angout,bool s4checkout,
							 std::string a5magout,std::string a5angout,bool a5checkout,
							 std::string s5magout,std::string s5angout,bool s5checkout
							 )
{

	DM::TagGroup pers = DM::GetPersistentTagGroup();


	a2check=a2checkout;

	if(a2check)
	{
		a2mag=a2magout;
		a2ang=a2angout;
	}
	else
	{
		a2mag="";
		a2ang="";
	}

	b2check=b2checkout;

	if(b2check)
	{
		b2mag=b2magout;
		b2ang=b2angout;
	}
	else
	{
		b2mag="";
		b2ang="";
	}

	a3check=a3checkout;

	if(a3check)
	{
		a3mag=a3magout;
		a3ang=a3angout;
	}
	else
	{
		a3mag="";
		a3ang="";
	}

	c3check=c3checkout;

	if(c3check)
	{
		c3mag=c3magout;
	}
	else
	{
		c3mag="";
	}

		s3check=s3checkout;

	if(s3check)
	{
		s3mag=s3magout;
		s3ang=s3angout;
	}
	else
	{
		s3mag="";
		s3ang="";
	}

	b3check=b3checkout;

	if(b3check)
	{
		b3mag=b3magout;
		b3ang=b3angout;
	}
	else
	{
		b3mag="";
		b3ang="";
	}

	a4check=a4checkout;

	if(a4check)
	{
		a4mag=a4magout;
		a4ang=a4angout;
	}
	else
	{
		a4mag="";
		a4ang="";
	}

		s4check=s4checkout;

	if(s4check)
	{
		s4mag=s4magout;
		s4ang=s4angout;
	}
	else
	{
		s4mag="";
		s4ang="";
	}

		a5check=a5checkout;

	if(a5check)
	{
		a5mag=a5magout;
		a5ang=a5angout;
	}
	else
	{
		a5mag="";
		a5ang="";
	}

			s5check=s5checkout;

	if(s5check)
	{
		s5mag=s5magout;
		s5ang=s5angout;
	}
	else
	{
		s5mag="";
		s5ang="";
	}

	AddAberrationTags(DM::GetPersistentTagGroup());
}

void CDMOperator::AddAberrationTags(DM::TagGroup imagetags)
{
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:A2(Mag)",a2mag);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:A2(Angle)",a2ang);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:B2(Mag)",b2mag);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:B2(Angle)",b2ang);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:A3(Mag)",a3mag);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:A3(Angle)",a3ang);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:C3(Mag)",c3mag);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:S3(Mag)",s3mag);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:S3(Angle)",s3ang);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:B3(Mag)",b3mag);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:B3(Angle)",b3ang);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:A4(Mag)",a4mag);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:A4(Angle)",a4ang);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:S4(Mag)",s4mag);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:S4(Angle)",s4ang);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:A5(Mag)",a5mag);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:A5(Angle)",a5ang);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:S5(Mag)",s5mag);
	DM::TagGroupSetTagAsString(imagetags,"Aberrations:S5(Angle)",s5ang);

};


// This button adds current settings as a new user...
void CDMOperator::OnBnClickedButton4()
{
	// Check for a user with the same name as this user...
	bool found = false;
	int index = 0;

	for(int i = 0; i < NumUsers; i++)
	{
		if(UserNames[i] == OperatorName)
		{
			found = true;
			index = i;
		}
	}
	
	DigitalMicrograph::TagGroup pers = DigitalMicrograph::GetPersistentTagGroup();

	if(found)
	{
		std::string usertagpath = "Operator Panel:UserDirs:"+boost::lexical_cast<std::string>(index);
		UserDirectories[index] = filepath;
		DigitalMicrograph::TagGroupSetTagAsString(pers,usertagpath.c_str(),filepath);
	}
	else
	{
		NumUsers++;
		UserNames.push_back(OperatorName);
		UserDirectories.push_back(filepath);

		std::vector<int>temppathorder;
		temppathorder.push_back(1);
		temppathorder.push_back(0);
		temppathorder.push_back(2);

		UserPathOrders.push_back(temppathorder);


		std::string usertagpath = "Operator Panel:UserDirs:"+boost::lexical_cast<std::string>(NumUsers-1);
		DigitalMicrograph::TagGroupSetTagAsString(pers,usertagpath.c_str(),filepath);

		std::string usertagpath2 = "Operator Panel:UserNames:"+boost::lexical_cast<std::string>(NumUsers-1);
		DigitalMicrograph::TagGroupSetTagAsString(pers,usertagpath2.c_str(),OperatorName);

		std::string usertagpath3 = "Operator Panel:Users";
		DigitalMicrograph::TagGroupSetTagAsString(pers,usertagpath3.c_str(),boost::lexical_cast<std::string>(NumUsers));

		m_OperatorCombo.AddString(OperatorName.c_str());
	}

	// Add Path Order
	SavePathOrder();
}

void CDMOperator::SavePathOrder()
{
	DigitalMicrograph::TagGroup pers = DigitalMicrograph::GetPersistentTagGroup();

	bool found = false;
	int index = 0;

	for(int i = 0; i < NumUsers; i++)
	{
		if(UserNames[i] == OperatorName)
		{
			found = true;
			index = i;
		}
	}
	
	if(found)
	{
		std::string usertagpath = "Operator Panel:UserPathOrders:"+boost::lexical_cast<std::string>(index)+":0";
		std::string usertagpath1 = "Operator Panel:UserPathOrders:"+boost::lexical_cast<std::string>(index)+":1";
		std::string usertagpath2 = "Operator Panel:UserPathOrders:"+boost::lexical_cast<std::string>(index)+":2";
		
		UserPathOrders[index][0] = pathorder[0];
		UserPathOrders[index][1] = pathorder[1];
		UserPathOrders[index][2] = pathorder[2];

		DigitalMicrograph::TagGroupSetTagAsString(pers,usertagpath.c_str(),boost::lexical_cast<std::string>(pathorder[0]));
		DigitalMicrograph::TagGroupSetTagAsString(pers,usertagpath1.c_str(),boost::lexical_cast<std::string>(pathorder[1]));
		DigitalMicrograph::TagGroupSetTagAsString(pers,usertagpath2.c_str(),boost::lexical_cast<std::string>(pathorder[2]));
	}

}

void CDMOperator::LoadPathOrder(int user)
{
	DigitalMicrograph::TagGroup pers;
	pers = DigitalMicrograph::GetPersistentTagGroup();

	pathorder[0] = UserPathOrders[user][0];
	pathorder[1] = UserPathOrders[user][1];
	pathorder[2] = UserPathOrders[user][2];
}

void CDMOperator::OnBnClickedButton5()
{
	DirectoryBuilder dlg(pathorder[0],pathorder[1],pathorder[2],this);

	dlg.DoModal();
	// TODO: Add your control notification handler code here
}
