// DrawSelect.h: interface for the CDrawSelect class.
// Draw selected retangle
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWSELECT_H__4F7F96E9_5A37_4E05_B4F3_19A8E3975978__INCLUDED_)
#define AFX_DRAWSELECT_H__4F7F96E9_5A37_4E05_B4F3_19A8E3975978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObject.h"

class CDrawSelect : public CDrawObject  
{
public:
	CDrawSelect();
	CDrawSelect(const CPoint& pBegin, const CPoint& pEnd);
	virtual ~CDrawSelect();

	BOOL Draw(CDC* pDC);	// Draw selected retangle
};

#endif // !defined(AFX_DRAWSELECT_H__4F7F96E9_5A37_4E05_B4F3_19A8E3975978__INCLUDED_)
