// DrawRoundRect.cpp: implementation of the CDrawRoundRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToDraw.h"
#include "DrawRoundRect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawRoundRect::CDrawRoundRect()
{

}

CDrawRoundRect::~CDrawRoundRect()
{

}

CDrawRoundRect::CDrawRoundRect(const CPoint& pBegin, const CPoint& pEnd, const int& RoundWidth, const int& RoundHeight) : 
	CDrawObject(pBegin, pEnd), m_RoundWidth(RoundWidth), m_RoundHeight(RoundHeight)
{

}

CDrawRoundRect::Draw(CDC* pDC)
{ 
	CPen Pen(m_PenStyle, m_PenWidth, m_PenColor);
	CPen* pOldPen = pDC->SelectObject(&Pen);
	
	if (m_FillFlag)
	{
		CBrush Brush(m_BrushColor);
		CBrush* pOldBrush = pDC->SelectObject(&Brush);
		CRgn Rgn;
		Rgn.CreateRoundRectRgn(m_pBegin.x, m_pBegin.y, m_pEnd.x, m_pEnd.y, m_RoundWidth, m_RoundHeight);
		pDC->FillRgn(&Rgn, &Brush);
		pDC->SelectObject(pOldBrush);
	}
	else	// Draw two times, first draw mask, then draw what you want
	{
		CPen tmpPen(m_PenStyle, m_PenWidth, RGB(0, 0, 0));
		pDC->SelectObject(&tmpPen);
		CBrush tmpBrush(RGB(255, 255, 255));
		CBrush* pOldBrush = pDC->SelectObject(&tmpBrush);
		int OldROP2 = pDC->SetROP2(R2_MASKPEN);
		if (!pDC->RoundRect(m_pBegin.x, m_pBegin.y, m_pEnd.x, m_pEnd.y, m_RoundWidth, m_RoundHeight))
		{
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			pDC->SetROP2(OldROP2);
			return FALSE;
		}

		pDC->SelectObject(&Pen);
		CBrush tmp2Brush(RGB(0, 0, 0));
		pDC->SelectObject(&tmp2Brush);
		pDC->SetROP2(R2_MERGEPEN);
		if (!pDC->RoundRect(m_pBegin.x, m_pBegin.y, m_pEnd.x, m_pEnd.y, m_RoundWidth, m_RoundHeight))
		{
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			pDC->SetROP2(OldROP2);
			return FALSE;
		}

		pDC->SelectObject(pOldBrush);
		pDC->SetROP2(OldROP2);
	}

	pDC->SelectObject(pOldPen);

	return TRUE;
}
