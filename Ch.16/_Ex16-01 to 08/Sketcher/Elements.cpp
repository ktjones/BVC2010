// Element.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "Elements.h"
#include <cmath>


// CElement

CElement::CElement()
{
}

CElement::~CElement()
{
}


// CElement member functions

// Get the bounding rectangle for an element
CRect CElement::GetBoundRect() const
{
	CRect boundingRect(m_EnclosingRect); // Object to store bounding rectangle
	
	// Increase the rectangle by the pen width and return it
	boundingRect.InflateRect(m_PenWidth, m_PenWidth);
	
	return boundingRect;
	
}


// CLine

CLine::CLine(void)
{
}

// CLine class constructor
CLine::CLine(const CPoint & start, const CPoint & end, COLORREF aColor, int aPenStyle): m_StartPoint(start), m_EndPoint(end)
{
	
	m_PenWidth = 1; // Set pen width
	m_LineStyle = aPenStyle;
	m_Color = aColor; // Set line color

	// Defi ne the enclosing rectangle
	m_EnclosingRect = CRect(start, end);
	m_EnclosingRect.NormalizeRect();

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
	if(!aPen.CreatePen(m_LineStyle, m_PenWidth, m_Color))
	{
		// Pen creation failed. Abort the program
		AfxMessageBox(_T("Pen creation failed drawing a line"), MB_OK);
		AfxAbort();
	}
	
	CPen* pOldPen = pDC->SelectObject(& aPen); // Select the pen
	
	// Now draw the line
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);
	pDC->SelectObject(pOldPen); // Restore the old pen

}

// CRectangle

CRectangle::CRectangle(void)
{
}

// CRectangle class constructor
CRectangle::CRectangle(const CPoint & start, const CPoint & end, COLORREF aColor, int aPenStyle)
{
	
	m_Color = aColor; // Set rectangle color
	m_LineStyle = aPenStyle;
	m_PenWidth = 1; // Set pen width
	
	// Define the enclosing rectangle
	m_EnclosingRect = CRect(start, end);
	m_EnclosingRect.NormalizeRect();

}

CRectangle::~CRectangle(void)
{
}

// Draw a CRectangle object
void CRectangle::Draw(CDC* pDC)
{
	
	// Create a pen for this object and
	// initialize it to the object color and line width of m_PenWidth
	CPen aPen;
	if(!aPen.CreatePen(m_LineStyle, m_PenWidth, m_Color))
	{
		// Pen creation failed
		AfxMessageBox(_T("Pen creation failed drawing a rectangle"), MB_OK);
		AfxAbort();
	}
	
	// Select the pen
	CPen* pOldPen = pDC->SelectObject( & aPen);
	
	// Select the brush
	CBrush* pOldBrush=(CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	
	// Now draw the rectangle
	pDC->Rectangle(m_EnclosingRect);
	pDC->SelectObject(pOldBrush); // Restore the old brush
	pDC->SelectObject(pOldPen); // Restore the old pen

}

// CCircle

CCircle::CCircle(void)
{
}

CCircle::CCircle(const CPoint& start, const CPoint& end, COLORREF aColor, int aPenStyle)
{
	
	// First calculate the radius
	// We use floating point because that is required by
	// the library function (in cmath) for calculating a square root.
	long radius = static_cast <long>(sqrt(static_cast <double>((end.x-start.x)*(end.x-start.x)+(end.y-start.y)*(end.y-start.y))));

	// Now calculate the rectangle enclosing
	// the circle assuming the MM_TEXT mapping mode
	m_EnclosingRect = CRect(start.x-radius, start.y-radius,start.x+radius, start.y+radius);
	m_EnclosingRect.NormalizeRect(); // Normalize-in case it's not MM_TEXT
	m_Color = aColor; // Set the color for the circle
	m_PenWidth = 1; // Set pen width to 1
	m_LineStyle = aPenStyle;

}

CCircle::~CCircle(void)
{
}

// Draw a circle
void CCircle::Draw(CDC* pDC)
{
	
	// Create a pen for this object and
	// initialize it to the object color and line width of m_PenWidth
	CPen aPen;
	
	if(!aPen.CreatePen(m_LineStyle, m_PenWidth, m_Color))
	{
		// Pen creation failed
		AfxMessageBox(_T("Pen creation failed drawing a circle"), MB_OK);
		AfxAbort();
	}
	
	// Select the pen
	CPen* pOldPen = pDC-> SelectObject(& aPen); 
	
	// Select a null brush
	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	
	// Now draw the circle
	pDC->Ellipse(m_EnclosingRect);
	pDC->SelectObject(pOldPen); // Restore the old pen
	pDC->SelectObject(pOldBrush); // Restore the old brush

}

// Curve

CCurve::CCurve(void)
{
}

CCurve::CCurve(const CPoint& first, const CPoint& second, COLORREF aColor, int aPenStyle)
{

	// Store the points
	m_Points.push_back(first);
	m_Points. push_back(second);
	m_Color = aColor;
	m_EnclosingRect = CRect(min(first.x, second.x), min(first.y, second.y),max(first.x, second.x), max(first.y, second.y));
	m_PenWidth = 1;
	m_LineStyle = aPenStyle;

}

CCurve::~CCurve(void)
{
}

// Draw a curve
void CCurve::Draw(CDC* pDC)
{
	// Create a pen for this object and
	// initialize it to the object color and line width of m_PenWidth
	CPen aPen;
	
	if(!aPen.CreatePen(m_LineStyle, m_PenWidth, m_Color))
	{
		// Pen creation failed
		AfxMessageBox(_T("Pen creation failed drawing a curve"), MB_OK);
		AfxAbort();
	}
	
	// Select the pen
	CPen* pOldPen = pDC->SelectObject(& aPen);

	// Now draw the curve
	pDC->MoveTo(m_Points[0]);
	
	for(size_t i=1; i<m_Points.size(); ++i)
	{
		pDC->LineTo(m_Points[i]);
	}
	
	pDC->SelectObject(pOldPen); // Restore the old pen
}

// Add a segment to the curve
void CCurve::AddSegment(const CPoint& point)
{
	
	m_Points.push_back(point); // Add the point to the end
	
	// Modify the enclosing rectangle for the new point
	m_EnclosingRect=CRect(min(point.x,m_EnclosingRect.left),min(point.y,m_EnclosingRect.top),max(point.x,m_EnclosingRect.right),max(point.y,m_EnclosingRect.bottom));

}


// CEllipse

CEllipse::CEllipse(void)
{
}

CEllipse::CEllipse(const CPoint& center, const CPoint& end, COLORREF aColor, int aPenStyle)
{
	
	// First calculate the left rect coords (start)
	// We use floating point because that is required by
	// the library function (in cmath) for calculating a square root.
	
	CPoint start(center);
	start.Offset(center.x-end.x,center.y-end.y);

	// Now calculate the rectangle enclosing
	// the circle assuming the MM_TEXT mapping mode
	

	m_EnclosingRect = CRect(start,end);
	m_EnclosingRect.NormalizeRect(); // Normalize-in case it's not MM_TEXT
	m_Color = aColor; // Set the color for the circle
	m_PenWidth = 1; // Set pen width to 1
	m_LineStyle = aPenStyle;

}

CEllipse::~CEllipse(void)
{
}

// Draw a circle
void CEllipse::Draw(CDC* pDC)
{
	
	// Create a pen for this object and
	// initialize it to the object color and line width of m_PenWidth
	CPen aPen;
	
	if(!aPen.CreatePen(m_LineStyle, m_PenWidth, m_Color))
	{
		// Pen creation failed
		AfxMessageBox(_T("Pen creation failed drawing a circle"), MB_OK);
		AfxAbort();
	}
	
	// Select the pen
	CPen* pOldPen = pDC->SelectObject(& aPen); 
	
	// Select a null brush
	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	
	// Now draw the circle
	pDC->Ellipse(m_EnclosingRect);
	pDC->SelectObject(pOldPen); // Restore the old pen
	pDC->SelectObject(pOldBrush); // Restore the old brush

}


