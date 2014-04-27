#pragma once
#include "atltypes.h"
#include <vector>

// CElement command target

#pragma once

// CElement command target

class CElement : public CObject
{
	DECLARE_SERIAL(CElement)
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
		virtual void Serialize(CArchive& ar);  // Serialize function for the class

	protected:
		CElement();			// Here to prevent it from being called
	
};

class CLine : public CElement
{
	
	DECLARE_SERIAL(CLine)
	public:
		virtual ~CLine(void);
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr);
		virtual void Move(const CSize & aSize); // Function to move an element
	
		// Constructor for a line object
		CLine(const CPoint& start, const CPoint& end, COLORREF aColor, int aPenStyle, int penWidth);
		virtual void Serialize(CArchive& ar);  // Serialize function for the class

	protected:
		CPoint m_StartPoint; // Start point of line
		CPoint m_EndPoint; // End point of line
	
		CLine(void);

};

class CRectangle : public CElement
{
	
	DECLARE_SERIAL(CRectangle)
	public:
		virtual ~CRectangle(void);
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr); // Function to display a rectangle
		virtual void Move(const CSize & aSize); // Function to move an element

		// Constructor for a rectangle object
		CRectangle(const CPoint& start, const CPoint& end, COLORREF aColor, int aPenStyle, int penWidth);
		virtual void Serialize(CArchive& ar);  // Serialize function for the class

	protected:
		CRectangle(void);	// Default constructor - should not be used

};

class CCircle : public CElement
{
	
	DECLARE_SERIAL(CCircle)
	public:
		virtual ~CCircle(void);
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr); // Function to display a rectangle
		virtual void Move(const CSize & aSize); // Function to move an element

		// Constructor for a rectangle object
		CCircle(const CPoint& start, const CPoint& end, COLORREF aColor, int aPenStyle, int penWidth);
		virtual void Serialize(CArchive& ar);  // Serialize function for the class

	protected:
		CCircle(void);


};

class CCurve : public CElement
{
	
	DECLARE_SERIAL(CCurve)
	public:
		virtual ~CCurve(void);
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr); // Function to display a curve
		virtual void Move(const CSize & aSize); // Function to move an element

		// Constructor for a curve object
		CCurve(const CPoint& first, const CPoint& second, COLORREF aColor, int aPenStyle, int penWidth);
		void AddSegment(const CPoint& point); // Add a segment to the curve
		virtual void Serialize(CArchive& ar);  // Serialize function for the class

	protected:
		std::vector<CPoint> m_Points; // Points defi ning the curve
		CCurve(void);
};

class CEllipse : public CElement
{

	DECLARE_SERIAL(CEllipse)
	public:
		virtual ~CEllipse(void);
		virtual void Draw(CDC* pDC, CElement* pElement=nullptr); // Function to display a rectangle
		virtual void Move(const CSize & aSize); // Function to move an element

		// Constructor for a rectangle object
		CEllipse(const CPoint& center, const CPoint& end, COLORREF aColor, int aPenStyle, int penWidth);
		virtual void Serialize(CArchive& ar);  // Serialize function for the class

	protected:
		CEllipse(void);	// Default constructor - should not be used

};

class CText: public CElement
{
	
	DECLARE_SERIAL(CText)
	public:
		// Function to display a text element
		virtual void Draw(CDC* pDC, CElement* pElement=0);
		// Constructor for a text element
		CText(const CString & aString, const CRect & rect, COLORREF aColor);
		virtual void Move(const CSize & size); // Move a text element
		virtual void Serialize(CArchive& ar);  // Serialize function for the class

	protected:
		CString m_String; // Text to be displayed
		CText(){} // Default constructor
};