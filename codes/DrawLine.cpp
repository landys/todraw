// DrawLine.cpp: implementation of the CDrawLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToDraw.h"
#include "DrawLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawLine::CDrawLine()
{

}

CDrawLine::CDrawLine(const CPoint& pBegin, const CPoint& pEnd) : 
	CDrawObject(pBegin, pEnd)
{

}

CDrawLine::~CDrawLine()
{

}

BOOL CDrawLine::Draw(CDC* pDC)
{
	CPen Pen(m_PenStyle, m_PenWidth, m_PenColor);
	CPen* pOldPen = pDC->SelectObject(&Pen);
	CBrush Brush(m_BrushColor);
	CBrush* pOldBrush = pDC->SelectObject(&Brush);
	pDC->MoveTo(m_pBegin);
	if (!pDC->LineTo(m_pEnd))
	{
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
		return FALSE;
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	return TRUE;
}