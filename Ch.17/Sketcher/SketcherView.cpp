
// SketcherView.cpp : implementation of the CSketcherView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#endif

#include "SketcherDoc.h"
#include "SketcherView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherView

IMPLEMENT_DYNCREATE(CSketcherView, CScrollView)

BEGIN_MESSAGE_MAP(CSketcherView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSketcherView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CSketcherView construction/destruction

CSketcherView::CSketcherView(): m_FirstPoint(CPoint(0,0)), m_SecondPoint(CPoint(0,0)), m_pTempElement(nullptr), m_pSelected(nullptr)
{
	// TODO: add construction code here

}

CSketcherView::~CSketcherView()
{
}

BOOL CSketcherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSketcherView drawing

void CSketcherView::OnDraw(CDC* pDC)
{
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
	return;
	
	CElement* pElement(nullptr);
	for(auto iter = pDoc->begin() ; iter != pDoc->end() ; ++iter)
	{
		pElement = *iter;
		if(pDC->RectVisible(pElement->GetBoundRect())) // If the element is visible
		pElement->Draw(pDC); // ...draw it
	}
	
}

// CSketcherView printing

void CSketcherView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSketcherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSketcherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSketcherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSketcherView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSketcherView::OnContextMenu(CWnd* pWnd, CPoint point)
{

#ifndef SHARED_HANDLERS
	
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
	if(m_pSelected)
	{
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_ELEMENT_MENU,point.x, point.y, this);
	}
	else
	{
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_NOELEMENT_MENU,point.x, point.y, this);
	}


#endif

}

// CSketcherView diagnostics

#ifdef _DEBUG
void CSketcherView::AssertValid() const
{
	CView::AssertValid();
}

void CSketcherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketcherDoc* CSketcherView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketcherDoc)));
	return (CSketcherDoc*)m_pDocument;
}
#endif //_DEBUG

// CSketcherView message handlers

void CSketcherView::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	if(this == GetCapture())
	{
		ReleaseCapture(); // Stop capturing mouse messages
	}

	// If there is an element, add it to the document
	if(m_pTempElement)
	{
		// Call a document class function to store the element
		// pointed to by m_pTempElement in the document object
		GetDocument()->AddElement(m_pTempElement);
		
		GetDocument()->UpdateAllViews(nullptr, 0, m_pTempElement); // Tell the views
		m_pTempElement = nullptr; // Reset the element pointer

	}

}

void CSketcherView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	CClientDC aDC(this); // Create a device context
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&point); // Convert point to logical coordinatesm_FirstPoint = point; // Record the cursor position
	m_FirstPoint = point; // Record the cursor position
	SetCapture(); // Capture subsequent mouse messages

}

void CSketcherView::OnMouseMove(UINT nFlags, CPoint point)
{
	// Define a Device Context object for the view
	CClientDC aDC(this); // DC is for this view
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&point); // Convert point to logical coordinates

	if((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		m_SecondPoint = point; // Save the current cursor position

		if(m_pTempElement)
		{
			if(CURVE == GetDocument()->GetElementType()) // Is it a curve?
			{ // We are drawing a curve so add a segment to the existing curve
				static_cast<CCurve*>(m_pTempElement)->AddSegment(m_SecondPoint);
				m_pTempElement->Draw(&aDC); // Now draw it
				return; // We are done
			}

			// If we get to here it�s not a curve so
			// redraw the old element so it disappears from the view
			aDC.SetROP2(R2_NOTXORPEN); // Set the drawing mode
			m_pTempElement->Draw(&aDC); // Redraw the old element
			delete m_pTempElement; // Delete the old element
			m_pTempElement = nullptr; // Reset the pointer
		}

		// Create a temporary element of the type and color that
		// is recorded in the document object, and draw it
		m_pTempElement = CreateElement(); // Create a new element
		m_pTempElement->Draw(&aDC); // Draw the element
	}
}

CElement* CSketcherView::CreateElement(void) const
{

	// Get a pointer to the document for this view
	CSketcherDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc); // Verify the pointer is good
	
	// Now select the element using the type stored in the document
	switch(pDoc->GetElementType())
	{
		case RECTANGLE:
			return new CRectangle(m_FirstPoint, m_SecondPoint,pDoc->GetElementColor(),pDoc->GetElementPenStyle());

		case CIRCLE:
			return new CCircle(m_FirstPoint, m_SecondPoint, pDoc->GetElementColor(),pDoc->GetElementPenStyle());

		case CURVE:
			return new CCurve(m_FirstPoint, m_SecondPoint, pDoc->GetElementColor(),pDoc->GetElementPenStyle());

		case LINE:
			return new CLine(m_FirstPoint, m_SecondPoint, pDoc->GetElementColor(),pDoc->GetElementPenStyle());
		
		case ELLIPSE:
			return new CEllipse(m_FirstPoint, m_SecondPoint, pDoc->GetElementColor(),pDoc->GetElementPenStyle());

		default:
			// Something's gone wrong
			AfxMessageBox(_T("Bad Element code"), MB_OK);
			AfxAbort();
		
		return nullptr;
	}

}

void CSketcherView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// Invalidate the area corresponding to the element pointed to
	// if there is one, otherwise invalidate the whole client area
	if(pHint)
	{
		CClientDC aDC(this); // Create a device context
		OnPrepareDC(&aDC); // Get origin adjusted
		
		// Get the enclosing rectangle and convert to client coordinates
		CRect aRect = static_cast<CElement*>(pHint)->GetBoundRect();
		aDC.LPtoDP(aRect);
		InvalidateRect(aRect); // Get the area redrawn
	}
	else
	{
		InvalidateRect(nullptr);
	}
}

void CSketcherView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// Define document size
	CSize DocSize(3000,3000);

	// Set mapping mode and document size
	SetScrollSizes(MM_LOENGLISH, DocSize);

}
