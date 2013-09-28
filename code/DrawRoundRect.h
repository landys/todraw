// DrawRoundRect.h: interface for the CDrawRoundRect class.
// Round rectangle
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWROUNDRECT_H__2B1D083D_BF00_44C6_B185_672B514861B0__INCLUDED_)
#define AFX_DRAWROUNDRECT_H__2B1D083D_BF00_44C6_B185_672B514861B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObject.h"

class CDrawRoundRect : public CDrawObject  
{
public:
	CDrawRoundRect();
	CDrawRoundRect(const CPoint& pBegin, const CPoint& pEnd, const int& RoundWidth, const int& RoundHeight);
	virtual ~CDrawRoundRect();

	BOOL Draw(CDC* pDC);
private:
	int m_RoundWidth;	// Round corner width
	int m_RoundHeight;	// Round corner height
};

#endif // !defined(AFX_DRAWROUNDRECT_H__2B1D083D_BF00_44C6_B185_672B514861B0__INCLUDED_)
