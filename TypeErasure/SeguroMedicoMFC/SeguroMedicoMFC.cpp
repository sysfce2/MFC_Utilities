
// SeguroMedicoMFC.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "SeguroMedicoMFC.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "ClaimDlg.h"
#include "SeguroMedicoMFCDoc.h"
#include "SeguroMedicoMFCView.h"
#include "MainView.h"

#include "Data.h"
#include "DateCalculator.h"
#include "DoctorDlg.h"
#include "INSResponseDlg.h"
#include "INSResponseLineDlg.h"
#include "InvoiceDlg.h"
#include "MedicationDlg.h"
#include "PatientDlg.h"
#include "SpecialtyDlg.h"
#include "INSResponseDoc.h"
#include "INSResponseView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSeguroMedicoMFCApp

BEGIN_MESSAGE_MAP(CSeguroMedicoMFCApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CSeguroMedicoMFCApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_SPECIALTYDLG, &CSeguroMedicoMFCApp::OnFileSpecialtydlg)
	ON_COMMAND(ID_FILE_DOCTORDLG, &CSeguroMedicoMFCApp::OnFileDoctordlg)
	ON_COMMAND(ID_FILE_PATIENTDLG, &CSeguroMedicoMFCApp::OnFilePatientdlg)
	ON_COMMAND(ID_FILE_MEDICATIONDLG, &CSeguroMedicoMFCApp::OnFileMedicationdlg)
	ON_COMMAND(ID_FILE_CLAIMDLG, &CSeguroMedicoMFCApp::OnFileClaimdlg)
	ON_COMMAND(ID_FILE_INVOICEDLG, &CSeguroMedicoMFCApp::OnFileInvoicedlg)
	ON_COMMAND(ID_FILE_INSRESPONSEDLG, &CSeguroMedicoMFCApp::OnFileInsresponsedlg)
	ON_COMMAND(ID_FILE_INSRESPONSELINEDLG, &CSeguroMedicoMFCApp::OnFileInsresponselinedlg)
	ON_COMMAND(ID_FILE_DATECALCULATOR, &CSeguroMedicoMFCApp::OnFileDatecalculator)
END_MESSAGE_MAP()


// CSeguroMedicoMFCApp construction

CSeguroMedicoMFCApp::CSeguroMedicoMFCApp() noexcept
{
	m_bHiColorIcons = TRUE;

	// m_bLoadWindowPlacement = false;	// JDH for newer MFC
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("SeguroMedicoMFC.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CSeguroMedicoMFCApp object

CSeguroMedicoMFCApp theApp;


// CSeguroMedicoMFCApp initialization

BOOL CSeguroMedicoMFCApp::InitInstance()
{
	Storage::initialize();
	// Storage::upgrade_database();
	// return false;
	//Storage::fill_db_with_test_data();

	//auto claim = Storage::getStorage().get<Claim>(1);
	auto claims = Storage::getStorage().get_all<Claim>(order_by(&Claim::submission_date));
	
	std::cout << std::boolalpha;

	constexpr auto mdl{ std::chrono::June / std::chrono::last };
	std::cout << (mdl == std::chrono::month_day_last(std::chrono::month(6))) << ' ';

	constexpr auto ymwdl{ std::chrono::year(2023) /
						  std::chrono::December /
						  std::chrono::Tuesday[std::chrono::last]
	};
	std::cout << (ymwdl == std::chrono::year_month_weekday_last(
		std::chrono::year(2023),
		std::chrono::month(12),
		std::chrono::weekday_last(std::chrono::Tuesday))
		) << '\n';

	
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(16);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	{
		CMultiDocTemplate* pDocTemplate;
		pDocTemplate = new CMultiDocTemplate(IDR_SeguroMedicoMFCTYPE,
			RUNTIME_CLASS(CSeguroMedicoMFCDoc),
			RUNTIME_CLASS(CChildFrame), // custom MDI child frame
			RUNTIME_CLASS(MainView));
		//		RUNTIME_CLASS(CSeguroMedicoMFCView));
		if (!pDocTemplate)
			return FALSE;
		AddDocTemplate(pDocTemplate);
	}
	{
		CMultiDocTemplate* pDocTemplate;
		pDocTemplate = new CMultiDocTemplate(IDR_INSResponseMFCTYPE,
			RUNTIME_CLASS(INSResponseDoc),
			RUNTIME_CLASS(CChildFrame), // custom MDI child frame
			RUNTIME_CLASS(INSResponseView));
		if (!pDocTemplate)
			return FALSE;
		AddDocTemplate(pDocTemplate);
	}

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	// AfxSetResourceHandle(::AfxGetInstanceHandle());

	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CSeguroMedicoMFCApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	Storage::backup_db();
	
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CSeguroMedicoMFCApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CSeguroMedicoMFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSeguroMedicoMFCApp customization load/save methods

void CSeguroMedicoMFCApp::PreLoadState()
{
	m_bLoadWindowPlacement = false;

	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CSeguroMedicoMFCApp::LoadCustomState()
{
}

void CSeguroMedicoMFCApp::SaveCustomState()
{
}

// CSeguroMedicoMFCApp message handlers





void CSeguroMedicoMFCApp::OnFileSpecialtydlg()
{
	// TODO: Add your command handler code here
	SpecialtyDlg dlg;
	dlg.DoModal();
}



void CSeguroMedicoMFCApp::OnFileDoctordlg()
{
	// TODO: Add your command handler code here
	DoctorDlg dlg;
	dlg.DoModal();
}


void CSeguroMedicoMFCApp::OnFilePatientdlg()
{
	// TODO: Add your command handler code here
	PatientDlg dlg;
	dlg.DoModal();
}


void CSeguroMedicoMFCApp::OnFileMedicationdlg()
{
	// TODO: Add your command handler code here
	MedicationDlg dlg;
	dlg.DoModal();
}


void CSeguroMedicoMFCApp::OnFileClaimdlg()
{
	// TODO: Add your command handler code here
	ClaimDlg dlg;
	dlg.DoModal();
}


void CSeguroMedicoMFCApp::OnFileInvoicedlg()
{
	// TODO: Add your command handler code here
	InvoiceDlg dlg;
	dlg.DoModal();
}


void CSeguroMedicoMFCApp::OnFileInsresponsedlg()
{
	// TODO: Add your command handler code here
	INSResponseDlg dlg;
	dlg.DoModal();
}


void CSeguroMedicoMFCApp::OnFileInsresponselinedlg()
{
	// TODO: Add your command handler code here
	INSResponseLineDlg dlg;
	dlg.DoModal();
	
}


void CSeguroMedicoMFCApp::OnFileDatecalculator()
{
	// TODO: Add your command handler code here
	DateCalculator dlg;
	dlg.DoModal();
}
