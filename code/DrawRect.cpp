// DrawRect.cpp: implementation of the CDrawRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToDraw.h"
#include "DrawRect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawRect::CDrawRect()
{

}

CDrawRect::CDrawRect(const CPoint& pBegin, const CPoint& pEnd) : CDrawObject(pBegin, pEnd)
{

}

CDrawRect::~CDrawRect()
{

}

BOOL CDrawRect::Draw(CDC* pDC)
{
	CPen Pen(m_PenStyle, m_PenWidth, m_PenColor);
	CPen* pOldPen = pDC->SelectObject(&Pen);
		
	if (m_FillFlag)
	{
		CBrush Brush(m_BrushColor);
		CBrush* pOldBrush = pDC->SelectObject(&Brush);
		CRgn Rgn;
		Rgn.CreateRectRgn(m_pBegin.x, m_pBegin.y, m_pEnd.x, m_pEnd.y);
		pDC->FillRgn(&Rgn, &Brush);
		pDC->SelectObject(pOldBrush);
	}
	else	// Indeed, draw four lines
	{
		pDC->MoveTo(m_pBegin);
		if (!pDC->LineTo(m_pEnd.x, m_pBegin.y))
		{
			pDC->SelectObject(pOldPen);
			return FALSE;
		}
		if (!pDC->LineTo(m_pEnd))
		{
			pDC->SelectObject(pOldPen);
			return FALSE;
		}
		if (!pDC->LineTo(m_pBegin.x, m_pEnd.y))
		{
			pDC->SelectObject(pOldPen);
			return FALSE;
		}
		if (!pDC->LineTo(m_pBegin))
		{
			pDC->SelectObject(pOldPen);
			return FALSE;
		}
	}
	pDC->SelectObject(pOldPen);
	return TRUE;
}
