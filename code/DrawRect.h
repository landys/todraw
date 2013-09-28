// DrawRect.h: interface for the CDrawRect class.
// Rectangle
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWRECT_H__979F5D96_2D5E_4C60_9C31_6D8458EAD605__INCLUDED_)
#define AFX_DRAWRECT_H__979F5D96_2D5E_4C60_9C31_6D8458EAD605__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObject.h"

class CDrawRect : public CDrawObject  
{
public:
	CDrawRect();
	CDrawRect(const CPoint& pBegin, const CPoint& pEnd);
	virtual ~CDrawRect();

	BOOL Draw(CDC* pDC);	// Draw rectangle
};

#endif // !defined(AFX_DRAWRECT_H__979F5D96_2D5E_4C60_9C31_6D8458EAD605__INCLUDED_)
