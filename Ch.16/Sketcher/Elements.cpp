// Element.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "Elements.h"


// CElement

CElement::CElement()
{
}

CElement::~CElement()
{
}


// CElement member functions


CLine::CLine(void)
{
}

// CLine class constructor
CLine::CLine(const CPoint & start, const CPoint & end, COLORREF aColor): m_StartPoint(start), m_EndPoint(end)
{
	m_PenWidth = 1; // Set pen width
	m_Color = aColor; // Set line color
}


CLine::~CLine(void)
{
}

// Draw a CLine object
void CLine::Draw(CDC* pDC)
{
	
	// Create a pen for this object and
	// initialize it to the object color and line width m_PenWidth
	CPen aPen;
	if(!aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color))
	{
		// Pen creation failed. Abort the program
		AfxMessageBox(_T("Pen creation failed drawing a line"), MB_OK);
		AfxAbort();
	}
	
	CPen* pOldPen = pDC-> SelectObject( & aPen); // Select the pen
	
	// Now draw the line
	pDC-> MoveTo(m_StartPoint);
	pDC-> LineTo(m_EndPoint);
	pDC-> SelectObject(pOldPen); // Restore the old pen

}


CRectangle::CRectangle(void)
{
}


CRectangle::~CRectangle(void)
{
}


CCircle::CCircle(void)
{
}


CCircle::~CCircle(void)
{
}


CCurve::CCurve(void)
{
}


CCurve::~CCurve(void)
{
}
