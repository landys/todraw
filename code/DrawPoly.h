// DrawPoly.h: interface for the CDrawPoly class.
// Polygon
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWPOLY_H__AF67A11A_A17C_45F3_A06F_69D30B4A8FAE__INCLUDED_)
#define AFX_DRAWPOLY_H__AF67A11A_A17C_45F3_A06F_69D30B4A8FAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObject.h"

class CDrawPoly : public CDrawObject  
{
public:
	CDrawPoly();
	CDrawPoly(const CPoint& pBegin, const CPoint& pEnd);
	virtual ~CDrawPoly();
	
	BOOL Draw(CDC* pDC);	// Draw polygon
};

#endif // !defined(AFX_DRAWPOLY_H__AF67A11A_A17C_45F3_A06F_69D30B4A8FAE__INCLUDED_)
