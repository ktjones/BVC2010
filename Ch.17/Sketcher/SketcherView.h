
// SketcherView.h : interface of the CSketcherView class
//

#pragma once
#include "atltypes.h"
#include "Elements.h"


class CSketcherView : public CScrollView
{
	protected: // create from serialization only
		CSketcherView();
		DECLARE_DYNCREATE(CSketcherView)

	// Attributes
	public:
		CSketcherDoc* GetDocument() const;

	// Operations
	public:

	protected:
		CElement* CreateElement(void) const;	//Create a new element on the heap

	// Overrides
	public:
		virtual void OnDraw(CDC* pDC);  // overridden to draw this view
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
		virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
		virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
		virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
	public:
		virtual ~CSketcherView();
	#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
	#endif

	protected:

	// Generated message map functions
	protected:
		afx_msg void OnFilePrintPreview();
		afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
		DECLARE_MESSAGE_MAP()
	public:
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	protected:
		// Points
		CPoint m_FirstPoint;
		CPoint m_SecondPoint;
		// Pointer to temporary element
		CElement* m_pTempElement;
		// Pointer to an object selected by the mouse
		CElement* m_pSelected;

		virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in SketcherView.cpp
inline CSketcherDoc* CSketcherView::GetDocument() const
   { return reinterpret_cast<CSketcherDoc*>(m_pDocument); }
#endif

