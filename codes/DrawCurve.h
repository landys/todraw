// DrawCurve.h: interface for the CDrawCurve class.
// Bezier Curve
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWCURVE_H__72A1800D_1B58_4C62_BC21_BE95C8424440__INCLUDED_)
#define AFX_DRAWCURVE_H__72A1800D_1B58_4C62_BC21_BE95C8424440__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObject.h"

class CDrawCurve : public CDrawObject  
{
public:
	CDrawCurve();
	CDrawCurve(const CPoint& pBegin, const CPoint& pEnd);
	virtual ~CDrawCurve();

	BOOL Draw(CDC* pDC);	// Draw Bezier curve
};

#endif // !defined(AFX_DRAWCURVE_H__72A1800D_1B58_4C62_BC21_BE95C8424440__INCLUDED_)
