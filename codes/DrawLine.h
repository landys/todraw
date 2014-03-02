// DrawLine.h: interface for the CDrawLine class.
// Line
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWLINE_H__F07DB781_B39B_4AF6_80E2_E9E703F21667__INCLUDED_)
#define AFX_DRAWLINE_H__F07DB781_B39B_4AF6_80E2_E9E703F21667__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObject.h"

class CDrawLine : public CDrawObject  
{
public:
	CDrawLine();
	CDrawLine(const CPoint& pBegin, const CPoint& pEnd);
	virtual ~CDrawLine();
	
	BOOL Draw(CDC* pDC);	// Draw line	
};

#endif // !defined(AFX_DRAWLINE_H__F07DB781_B39B_4AF6_80E2_E9E703F21667__INCLUDED_)
