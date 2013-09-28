// DrawPoly.cpp: implementation of the CDrawPoly class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToDraw.h"
#include "DrawPoly.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawPoly::CDrawPoly()
{

}

CDrawPoly::CDrawPoly(const CPoint& pBegin, const CPoint& pEnd) :
	CDrawObject(pBegin, pEnd)
{

}

CDrawPoly::~CDrawPoly()
{

}

BOOL CDrawPoly::Draw(CDC* pDC)	// Indeed, draw line here
{
	CPen Pen(m_PenStyle, m_PenWidth, m_PenColor);

	CPen* pOldPen = pDC->SelectObject(&Pen);
	
	pDC->MoveTo(m_pBegin);
	if (!pDC->LineTo(m_pEnd))
	{
		pDC->SelectObject(pOldPen);
		return FALSE;
	}
	pDC->SelectObject(pOldPen);
	return TRUE;
}
