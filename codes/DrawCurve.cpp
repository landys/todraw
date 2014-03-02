// DrawCurve.cpp: implementation of the CDrawCurve class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToDraw.h"
#include "DrawCurve.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawCurve::CDrawCurve()
{

}

CDrawCurve::CDrawCurve(const CPoint& pBegin, const CPoint& pEnd) : 
	CDrawObject(pBegin, pEnd, pBegin, pBegin)
{

}

CDrawCurve::~CDrawCurve()
{

}

BOOL CDrawCurve::Draw(CDC* pDC)
{
	CPen Pen(m_PenStyle, m_PenWidth, m_PenColor);
	CPen* pOldPen = pDC->SelectObject(&Pen);
	
	CPoint pt[] = {m_pBegin, m_pHelp1, m_pHelp2, m_pEnd};	// Use two assistant points
	if (!pDC->PolyBezier(pt, 4))	// Draw Bezier curve
	{
		pDC->SelectObject(pOldPen);
		return FALSE;
	}
	pDC->SelectObject(pOldPen);
	return TRUE;
}
