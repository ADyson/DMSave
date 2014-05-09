// TemplateMFCDialogPlugIn.cpp : Defines the initialization routines for the DLL.
//
#define _GATAN_USE_STL_STRING

#include "stdafx.h"
#include "TemplateMFCDialogPlugIn.h"

#include "DMPluginMain.h"
extern AFX_EXTENSION_MODULE gPlugInExtensionModule = { NULL, NULL };

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CTemplateMFCDialogPlugInApp::Start(void)
{
	// Width 3 for right sidebar Width 2 for left sidebar
	fMFCPaletteHandle1=RegisterMFCPalette("Operator Panel", GetPlugInOSHandle(), RUNTIME_CLASS(CDMOperator),3);
//	fMFCPaletteHandle2=RegisterMFCPalette("Rhubarb", GetPlugInOSHandle(), RUNTIME_CLASS(CDMPropertySheet));
}
void CTemplateMFCDialogPlugInApp::End(void)
{
	UnregisterMFCPalette(fMFCPaletteHandle1);
//	UnregisterMFCPalette(fMFCPaletteHandle2);
}

// The one and only CTemplateMFCDialogPlugInApp object

CTemplateMFCDialogPlugInApp theApp;

