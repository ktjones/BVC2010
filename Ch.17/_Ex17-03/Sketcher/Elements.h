#pragma once
#include "atltypes.h"
#include <vector>

// CElement command target

#pragma once

// CElement command target

class CElement : public CObject
{
	protected:
		int m_PenWidth;		// Pen Width
		int m_LineStyle;	// Line Style
		COLORREF m_Color;	// Color of an element
		CRect m_EnclosingRect;	// Rectangle enclosing an element

	public:
		virtual ~CElement();
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr) {}	// Virtual draw operation
		CRect GetBoundRect() const;		// Get the bounding rectangle for an element
		virtual void Move(const CSize & aSize){} // Move an element

	protected:
		CElement();			// Here to prevent it from being called
	
};

class CLine : public CElement
{
	public:
		virtual ~CLine(void);
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr);
		virtual void Move(const CSize & aSize); // Function to move an element
	
		// Constructor for a line object
		CLine(const CPoint& start, const CPoint& end, COLORREF aColor, int aPenStyle);


	protected:
		CPoint m_StartPoint; // Start point of line
		CPoint m_EndPoint; // End point of line
	
		CLine(void);

};

class CRectangle : public CElement
{
	public:
		virtual ~CRectangle(void);
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr); // Function to display a rectangle
		virtual void Move(const CSize & aSize); // Function to move an element

		// Constructor for a rectangle object
		CRectangle(const CPoint& start, const CPoint& end, COLORREF aColor, int aPenStyle);

	protected:
		CRectangle(void);	// Default constructor - should not be used

};

class CCircle : public CElement
{
	public:
		virtual ~CCircle(void);
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr); // Function to display a rectangle
		virtual void Move(const CSize & aSize); // Function to move an element

		// Constructor for a rectangle object
		CCircle(const CPoint& start, const CPoint& end, COLORREF aColor, int aPenStyle);

	protected:
		CCircle(void);


};

class CCurve : public CElement
{
	public:
		virtual ~CCurve(void);
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr); // Function to display a curve
		virtual void Move(const CSize & aSize); // Function to move an element

		// Constructor for a curve object
		CCurve(const CPoint& first, const CPoint& second, COLORREF aColor, int aPenStyle);
		void AddSegment(const CPoint& point); // Add a segment to the curve

	protected:
		//std::vector<CPoint> m_Points; // Points defining the curve
		CArray<CPoint, const CPoint &> m_APoints;		// Points defining the curve

		CCurve(void);
};

class CEllipse : public CElement
{

	public:
		virtual ~CEllipse(void);
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr); // Function to display a rectangle
		virtual void Move(const CSize & aSize); // Function to move an element

		// Constructor for a rectangle object
		CEllipse(const CPoint& center, const CPoint& end, COLORREF aColor, int aPenStyle);

	protected:
		CEllipse(void);	// Default constructor - should not be used

};
