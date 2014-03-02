// DrawFilling.cpp: implementation of the CDrawFilling class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToDraw.h"
#include "DrawFilling.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawFilling::CDrawFilling()
{

}

CDrawFilling::CDrawFilling(const CPoint& pBegin, const CPoint& pEnd) : CDrawObject(pBegin, pEnd)
{

}

CDrawFilling::~CDrawFilling()
{

}

BOOL CDrawFilling::Draw(CDC* pDC)
{
	CBrush Brush(m_BrushColor);
	CBrush* pOldBrush = pDC->SelectObject(&Brush);

	// use m_PenColor to mark surface color
	if (pDC->ExtFloodFill(m_pBegin.x, m_pBegin.y, m_PenColor, FLOODFILLSURFACE))
	{
		pDC->SelectObject(pOldBrush);
		return FALSE;
	}
	pDC->SelectObject(pOldBrush);
	return TRUE;
}
