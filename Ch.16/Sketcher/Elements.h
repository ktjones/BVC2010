#pragma once

// CElement command target

#pragma once

// CElement command target

class CElement : public CObject
{
	protected:
		int m_PenWidth;		// Pen Width
		COLORREF m_Color;	// Color of an element

	public:
		virtual ~CElement();
		virtual void Draw(CDC* pDC) {}	// Virtual draw operation
		CRect GetBoundRect() const;		// Get the bounding rectangle for an element

	protected:
		CElement();			// Here to prevent it from being called

};

class CLine : public CElement
{
	public:
		virtual ~CLine(void);
		virtual void Draw(CDC* pDC);
	
		// Constructor for a line object
		CLine(const CPoint& start, const CPoint& end, COLORREF aColor);

	protected:
		CPoint m_StartPoint; // Start point of line
		CPoint m_EndPoint; // End point of line
	
		CLine(void);

};

class CRectangle : public CElement
{
	public:
		CRectangle(void);
		virtual ~CRectangle(void);
};

class CCircle : public CElement
{
	public:
		CCircle(void);
		virtual ~CCircle(void);
};

class CCurve : public CElement
{
	public:
		CCurve(void);
		virtual ~CCurve(void);
};


