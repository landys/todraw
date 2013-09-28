// DrawObject.cpp: implementation of the CDrawObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ToDraw.h"
#include "DrawObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawObject::CDrawObject() : m_PenColor(RGB(0, 0, 0)), m_BrushColor(RGB(0, 0, 0)),
	m_BackgroundColor(RGB(255, 255, 255)), m_PenWidth(1), m_FillFlag(FALSE),
	m_pBegin((0, 0)), m_pEnd((0, 0)), m_pInit((0, 0)), m_pHelp1((0, 0)), m_pHelp2((0, 0)),
	m_PenStyle(PS_SOLID)
{

}

CDrawObject::CDrawObject(const CPoint& pBegin, const CPoint& pEnd,
						 const CPoint& pHelp1 /* = (0, 0) */, const CPoint& pHelp2 /* = (0, 0) */) : 
	m_PenColor(RGB(0, 0, 0)), m_BrushColor(RGB(0, 0, 0)),
	m_BackgroundColor(RGB(255, 255, 255)), m_PenWidth(1), m_FillFlag(FALSE),
	m_pBegin(pBegin), m_pEnd(pEnd), m_pInit(pBegin), 
	m_PenStyle(PS_SOLID), m_pHelp1(pHelp1), m_pHelp2(pHelp2)
{

}

CDrawObject::~CDrawObject()
{

}
