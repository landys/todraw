// DrawEllipse.h: interface for the CDrawEllipse class.
// Ellipse
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWELLIPSE_H__EF1D9067_DBFD_4F04_94F5_8619A855154E__INCLUDED_)
#define AFX_DRAWELLIPSE_H__EF1D9067_DBFD_4F04_94F5_8619A855154E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObject.h"

class CDrawEllipse : public CDrawObject  
{
public:
	CDrawEllipse();
	CDrawEllipse(const CPoint& pBegin, const CPoint& pEnd);
	virtual ~CDrawEllipse();

	BOOL Draw(CDC* pDC);	// Draw ellipse
};

#endif // !defined(AFX_DRAWELLIPSE_H__EF1D9067_DBFD_4F04_94F5_8619A855154E__INCLUDED_)
