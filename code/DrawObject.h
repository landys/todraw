// DrawObject.h: interface for the CDrawObject class.
// The base class of all draw class
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWOBJECT_H__8C1A915F_843F_4DE7_AA5E_502E7699E6FF__INCLUDED_)
#define AFX_DRAWOBJECT_H__8C1A915F_843F_4DE7_AA5E_502E7699E6FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDrawObject : public CObject  
{
public:
	CDrawObject();
	CDrawObject(const CPoint& pBegin, const CPoint& pEnd, const CPoint& pHelp1 = (0, 0), const CPoint& pHelp2 = (0, 0));
	virtual ~CDrawObject() = 0;
	
	virtual BOOL Draw(CDC* pDC) = 0;	// Draw something in inherited class

public:	// Attribute
	COLORREF m_PenColor;	// Pen color
	COLORREF m_BrushColor;	// Brush color
	COLORREF m_BackgroundColor;	// Background color
	int m_PenStyle;	// Pen style
	int m_PenWidth;	// Pen width
	BOOL m_FillFlag;	// Check whether to fill in the picture

	CPoint m_pBegin;	// Begin point when drawing
	CPoint m_pEnd;	// End point
	CPoint m_pInit;	// Initial point of a drawing needed like polygon
	CPoint m_pHelp1;	// Assistant point 1
	CPoint m_pHelp2;	// Assistant point 2
};

#endif // !defined(AFX_DRAWOBJECT_H__8C1A915F_843F_4DE7_AA5E_502E7699E6FF__INCLUDED_)
