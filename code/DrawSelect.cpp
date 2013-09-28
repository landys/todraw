// DrawSelect.cpp: implementation of the CDrawSelect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToDraw.h"
#include "DrawSelect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawSelect::CDrawSelect()
{

}

CDrawSelect::CDrawSelect(const CPoint& pBegin, const CPoint& pEnd) : CDrawObject(pBegin, pEnd)
{

}

CDrawSelect::~CDrawSelect()
{

}

BOOL CDrawSelect::Draw(CDC* pDC)
{
	CPen Pen;
	CPen* pOldPen = 0;
	if (m_FillFlag)	// use m_FillFlag to mark if having selected
	{
		Pen.CreatePen(PS_DASH, 1, RGB(120, 120, 120));
		pOldPen = pDC->SelectObject(&Pen);

		pDC->MoveTo(m_pBegin);	// Indeed just draw four lines to make a retangle here
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
	else
	{
		Pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		pOldPen = pDC->SelectObject(&Pen);

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
