// DrawFilling.h: interface for the CDrawFilling class.
// Do filling
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWFILLING_H__B68DC789_0A81_48F3_8D4E_5F7FFC0C21E7__INCLUDED_)
#define AFX_DRAWFILLING_H__B68DC789_0A81_48F3_8D4E_5F7FFC0C21E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObject.h"

class CDrawFilling : public CDrawObject  
{
public:
	CDrawFilling();
	CDrawFilling(const CPoint& pBegin, const CPoint& pEnd);
	virtual ~CDrawFilling();

	BOOL Draw(CDC* pDC);	// Do filling
};

#endif // !defined(AFX_DRAWFILLING_H__B68DC789_0A81_48F3_8D4E_5F7FFC0C21E7__INCLUDED_)
