
// Ex1_04View.cpp : implementation of the CEx1_04View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Ex1_04.h"
#endif

#include "Ex1_04Doc.h"
#include "Ex1_04View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx1_04View

IMPLEMENT_DYNCREATE(CEx1_04View, CView)

BEGIN_MESSAGE_MAP(CEx1_04View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEx1_04View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CEx1_04View construction/destruction

CEx1_04View::CEx1_04View()
{
	// TODO: add construction code here

}

CEx1_04View::~CEx1_04View()
{
}

BOOL CEx1_04View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx1_04View drawing

void CEx1_04View::OnDraw(CDC* /*pDC*/)
{
	CEx1_04Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CEx1_04View printing


void CEx1_04View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEx1_04View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx1_04View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx1_04View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CEx1_04View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEx1_04View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEx1_04View diagnostics

#ifdef _DEBUG
void CEx1_04View::AssertValid() const
{
	CView::AssertValid();
}

void CEx1_04View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx1_04Doc* CEx1_04View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx1_04Doc)));
	return (CEx1_04Doc*)m_pDocument;
}
#endif //_DEBUG


// CEx1_04View message handlers
