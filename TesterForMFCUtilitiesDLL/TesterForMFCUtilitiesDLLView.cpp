
// TesterForMFCUtilitiesDLLView.cpp : implementation of the CTesterForMFCUtilitiesDLLView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TesterForMFCUtilitiesDLL.h"
#endif

#include "TesterForMFCUtilitiesDLLDoc.h"
#include "TesterForMFCUtilitiesDLLView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//namespace View
//{

	// CTesterForMFCUtilitiesDLLView

	IMPLEMENT_DYNCREATE(CTesterForMFCUtilitiesDLLView, CFormView)

	BEGIN_MESSAGE_MAP(CTesterForMFCUtilitiesDLLView, CFormView)
		// Standard printing commands
		ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTesterForMFCUtilitiesDLLView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
	END_MESSAGE_MAP()

	// CTesterForMFCUtilitiesDLLView construction/destruction

	CTesterForMFCUtilitiesDLLView::CTesterForMFCUtilitiesDLLView() noexcept
		: CFormView(IDD_TESTERFORMFCUTILITIESDLL_FORM), 
		m_pCatGridController{ std::make_unique<BasicCategoryGridController>(m_myFirstGridFromADLL) }
	{
		// TODO: add construction code here

	}

	CTesterForMFCUtilitiesDLLView::~CTesterForMFCUtilitiesDLLView()
	{
	}

	void CTesterForMFCUtilitiesDLLView::DoDataExchange(CDataExchange* pDX)
	{
		CFormView::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_GRID_CTRL, m_myFirstGridFromADLL);
	}

	BOOL CTesterForMFCUtilitiesDLLView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: Modify the Window class or styles here by modifying
		//  the CREATESTRUCT cs

		return CFormView::PreCreateWindow(cs);
	}

	void CTesterForMFCUtilitiesDLLView::OnInitialUpdate()
	{
		CFormView::OnInitialUpdate();
		m_pCatGridController->OnInitialUpdate();
		ResizeParentToFit();
	}


	// CTesterForMFCUtilitiesDLLView printing


	void CTesterForMFCUtilitiesDLLView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CTesterForMFCUtilitiesDLLView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// default preparation
		return DoPreparePrinting(pInfo);
	}

	void CTesterForMFCUtilitiesDLLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: add extra initialization before printing
	}

	void CTesterForMFCUtilitiesDLLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: add cleanup after printing
	}

	void CTesterForMFCUtilitiesDLLView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
	{
		// TODO: add customized printing code here
	}

	void CTesterForMFCUtilitiesDLLView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void CTesterForMFCUtilitiesDLLView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CTesterForMFCUtilitiesDLLView diagnostics

#ifdef _DEBUG
	void CTesterForMFCUtilitiesDLLView::AssertValid() const
	{
		CFormView::AssertValid();
	}

	void CTesterForMFCUtilitiesDLLView::Dump(CDumpContext& dc) const
	{
		CFormView::Dump(dc);
	}

	Controller::CTesterForMFCUtilitiesDLLDoc* CTesterForMFCUtilitiesDLLView::GetDocument() const // non-debug version is inline
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Controller::CTesterForMFCUtilitiesDLLDoc)));
		return (Controller::CTesterForMFCUtilitiesDLLDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CTesterForMFCUtilitiesDLLView message handlers

//}