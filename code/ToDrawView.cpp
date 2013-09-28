// ToDrawView.cpp : implementation of the CToDrawView class
//

#include "stdafx.h"
#include "ToDraw.h"

#include "PropertyDialog.h"

#include "ToDrawDoc.h"
#include "ToDrawView.h"

#include "Draw.h"

#include "MainFrm.h"

#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToDrawView

IMPLEMENT_DYNCREATE(CToDrawView, CScrollView)

BEGIN_MESSAGE_MAP(CToDrawView, CScrollView)
	//{{AFX_MSG_MAP(CToDrawView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETCURSOR()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_IMAGE_CLEAR, OnImageClear)
	ON_COMMAND(ID_IMAGE_PROPERTY, OnImageProperty)
	ON_COMMAND(ID_COLOR_CUSTOM, OnColorCustom)
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_IMAGE_PROPERTY, OnUpdateImageProperty)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)

	ON_COMMAND_RANGE(ID_LINE, ID_SAMPLING, OnToolBox)	// Messages for controls of ToolBox
	ON_UPDATE_COMMAND_UI_RANGE(ID_LINE, ID_SAMPLING, OnUpdateToolBox)

	ON_COMMAND_RANGE(ID_BLACK, ID_RED, OnColorBox)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BLACK, ID_RED, OnUpdateColorBox)

	ON_COMMAND_RANGE(ID_ONEPIXEL, ID_PS_DASHDOTDOT, OnToolStyleBox)
	ON_UPDATE_COMMAND_UI_RANGE(ID_ONEPIXEL, ID_PS_DASHDOTDOT, OnUpdateToolStyleBox)

	ON_REGISTERED_MESSAGE(CToDrawView::m_UserMsg, MyMessageHandler)	// Registered message for property page dialog
END_MESSAGE_MAP()


UINT CToDrawView::m_UserMsg = RegisterWindowMessage(CPROPERTYDIALOG_MSG);

/////////////////////////////////////////////////////////////////////////////
// CToDrawView construction/destruction

CToDrawView::CToDrawView() : m_pLMouseDown(FALSE), m_pDlg(0)
{
	// TODO: add construction code here

}

CToDrawView::~CToDrawView()
{
}

BOOL CToDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	//cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// make the background of view gray
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW |CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_GRAYTEXT));

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CToDrawView drawing


void CToDrawView::OnDraw(CDC* pDC)
{
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	
	CPoint pOrig = GetScrollPosition();	// Get original point of screen

	// Copy image stored in memory to screen here
	if (pDoc->m_isSelected)
	{
		CDC dcMem;
		dcMem.CreateCompatibleDC(NULL);
		dcMem.SelectObject(&pDoc->m_bmpBuf);

		CRect rect;
		GetClientRect(&rect);
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, pOrig.x, pOrig.y, SRCCOPY);
	}
	else
	{
		CDC dcMemSave;
		CBitmap *pOldBitmap = NULL;
		dcMemSave.CreateCompatibleDC(NULL);
		pOldBitmap = dcMemSave.SelectObject(&pDoc->m_bmpSave);
		CRect rect;
		GetClientRect(&rect);
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemSave, pOrig.x, pOrig.y, SRCCOPY);

		dcMemSave.SelectObject(pOldBitmap);
		dcMemSave.DeleteDC();
	}
}

void CToDrawView::OnInitialUpdate()	///////////// PlgBlt()
{
	CScrollView::OnInitialUpdate();

	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CSize sizeTotal;

	// TODO: calculate the total size of this view

	sizeTotal.cx = STD_SCROLLED_WIDTH;
	sizeTotal.cy = STD_SCROLLED_HEIGHT;
	CSize sizePage = CSize(sizeTotal.cx/2, sizeTotal.cy/2);
	CSize sizeLine = CSize(sizeTotal.cx/10, sizeTotal.cy/10);
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);	// Initial scroll size

	if (pDoc->m_Init)	// For multiview, if having initialized, return
	{
		return;
	}

	pDoc->m_Init = TRUE;

	// Initialize memory for storing picture
	CClientDC dc(this);
	pDoc->m_bmpBuf.DeleteObject();
	pDoc->m_bmpBuf.CreateCompatibleBitmap(&dc, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height());
	
	if (!pDoc->m_Saved)
	{
		pDoc->m_bmpSave.DeleteObject();
		pDoc->m_bmpSave.CreateCompatibleBitmap(&dc, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height());
	}

	CDC dcMemSave;
	dcMemSave.CreateCompatibleDC(NULL);
	dcMemSave.SelectObject(&pDoc->m_bmpSave);
	
	if (!pDoc->m_Saved)
	{
		dcMemSave.PatBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), WHITENESS);
	}
	
	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);
	dcMem.SelectObject(&pDoc->m_bmpBuf);
	dcMem.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);
	
	pDoc->m_bmpSave.GetBitmap(&(pDoc->m_bmpInfo));

	OnImageProperty();	// Show property page dialog
}

/////////////////////////////////////////////////////////////////////////////
// CToDrawView printing

BOOL CToDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CToDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CToDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CToDrawView diagnostics

#ifdef _DEBUG
void CToDrawView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToDrawView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToDrawDoc* CToDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToDrawDoc)));
	return (CToDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToDrawView message handlers

BOOL CToDrawView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CToDrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CToDrawDoc* pDoc = GetDocument();	// Get point to document
	ASSERT_VALID(pDoc);

	m_pLMouseDown = TRUE;
	SetCapture();

	CDC* pDC = GetDC();

	CDC dcMemSave;
	dcMemSave.CreateCompatibleDC(NULL);
	dcMemSave.SelectObject(&pDoc->m_bmpSave);

	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);
	dcMem.SelectObject(&pDoc->m_bmpBuf);

	dcMem.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);
	dcMem.SetBkColor(pDoc->m_BackgroundColor);
	dcMem.SetBkMode(pDoc->m_BackgroundMode);
	dcMem.SetROP2(R2_COPYPEN);

	CPoint pOrig = GetScrollPosition();
	point += pOrig;	// Change screen point to logical point
	
	switch (pDoc->m_Mode)	// Check draw mode
	{
	case DRAW_SELECT:	// Selete something
		if (!pDoc->m_isSelected)
		{
			pDoc->m_isDrawOn = TRUE;
			pDoc->m_isInSelect = FALSE;
			pDoc->m_pDrawObject = new CDrawSelect(point, point);
			pDoc->m_pDrawObject->m_FillFlag = pDoc->m_isSelected;			
		}
		else
		{
			pDoc->m_isDrawOn = FALSE;

			CDC dcMemSelect;
			dcMemSelect.CreateCompatibleDC(NULL);
			dcMemSelect.SelectObject(&pDoc->m_bmpSelect);
			
			if (point.x >= pDoc->m_SelectRect.left && point.x <= pDoc->m_SelectRect.right && point.y >= pDoc->m_SelectRect.top && point.y <= pDoc->m_SelectRect.bottom)
			{
				pDoc->m_SelectPoint = point;
				pDoc->m_isInSelect = TRUE;
			
				dcMem.BitBlt(pDoc->m_SelectRect.left, pDoc->m_SelectRect.top, pDoc->m_SelectRect.Width(), pDoc->m_SelectRect.Height(), &dcMemSelect, 0, 0, SRCCOPY);
				CRect rect;
				GetClientRect(&rect);
				pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, pOrig.x, pOrig.y, SRCCOPY);

			}
			else
			{
				dcMemSave.BitBlt(pDoc->m_SelectRect.left, pDoc->m_SelectRect.top, pDoc->m_SelectRect.Width(), pDoc->m_SelectRect.Height(), &dcMemSelect, 0, 0, SRCCOPY);
				CRect rect;
				GetClientRect(&rect);
				pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemSave, pOrig.x, pOrig.y, SRCCOPY);

				delete pDoc->m_pDrawObject;
				pDoc->m_pDrawObject = 0;

				pDoc->m_pDrawObject = new CDrawSelect(point, point);
				pDoc->m_isInSelect = FALSE;
				pDoc->m_isDrawOn = TRUE;
				pDoc->m_isSelected = FALSE;
				pDoc->m_pDrawObject->m_FillFlag = pDoc->m_isSelected;
			}
		}
		break;
	case DRAW_ERASER:	// Erase something
		pDoc->m_pDrawObject = new CDrawLine(point, point);
		pDoc->m_pDrawObject->m_PenWidth = 4 * pDoc->m_PenWidth;
		pDoc->m_pDrawObject->m_PenColor = pDoc->m_BackgroundColor;
		pDoc->m_pDrawObject->m_PenStyle = PS_SOLID;
		break;
	case DRAW_FILLING:
		{
			pDoc->m_pDrawObject = new CDrawFilling(point, point);
			pDoc->m_pDrawObject->m_BrushColor = pDoc->m_PenColor;
			// use m_PenColor to mark surface color
			pDoc->m_pDrawObject->m_PenColor = pDC->GetPixel(point);
			pDoc->m_pDrawObject->Draw(&dcMem);
			dcMemSave.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
			CRect rect;
			GetClientRect(&rect);
			pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemSave, pOrig.x, pOrig.y, SRCCOPY);

			delete pDoc->m_pDrawObject;
			pDoc->m_pDrawObject = 0;
		}
		break;
	case DRAW_SAMPLING:	// Get color information of the point
		pDoc->m_PenColor = pDC->GetPixel(point);
		break;
	case DRAW_PEN:	// Draw freely using a pen
		pDoc->m_pDrawObject = new CDrawLine(point, point);
		break;
	case DRAW_BRUSH:	// Draw freely using a brush
		pDoc->m_pDrawObject = new CDrawLine(point, point);
		pDoc->m_pDrawObject->m_PenWidth = 8 * pDoc->m_PenWidth;
		break;
	case DRAW_LINE:	// Draw line
		pDoc->m_pDrawObject = new CDrawLine(point, point);
		break;	
	case DRAW_CURVE:	// Draw Bezier curve
		pDoc->m_MouseDownTime++;

		switch (pDoc->m_MouseDownTime)	// For there must be at least four point
		{
		case 1:
			pDoc->m_pDrawObject = new CDrawCurve(point, point);
			break;
		case 2:
			{
				pDoc->m_pDrawObject->m_pHelp1 = point;
				pDoc->m_pDrawObject->m_pHelp2 = point;
				pDoc->m_pDrawObject->Draw(&dcMem);
				
				CRect rect;
				GetClientRect(&rect);
				CPoint pOrig = GetScrollPosition();
				pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, pOrig.x, pOrig.y, SRCCOPY);
			}
			break;
		case 3:
			{
				pDoc->m_pDrawObject->m_pHelp2 = point;
				pDoc->m_pDrawObject->Draw(&dcMem);
				
				CRect rect;
				GetClientRect(&rect);
				CPoint pOrig = GetScrollPosition();
				pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, pOrig.x, pOrig.y, SRCCOPY);
			}
			break;
		}
		break;
	case DRAW_RECTANGLE:	// Draw rectangle
		pDoc->m_pDrawObject = new CDrawRect(point, point);
		pDoc->m_pDrawObject->m_FillFlag = pDoc->m_FillFlag;
		break;
	case DRAW_POLYGON:	// Draw polygon
		if (!pDoc->m_isDrawOn)
		{
			pDoc->m_isDrawOn = TRUE;
			pDoc->m_pDrawObject = new CDrawPoly(point, point);
		}
		else
		{
			pDoc->m_pDrawObject->m_pEnd = point;

			pDoc->m_pDrawObject->Draw(&dcMem);
			
			CRect rect;
			GetClientRect(&rect);
			CPoint pOrig = GetScrollPosition();
			pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, pOrig.x, pOrig.y, SRCCOPY);
		}
		break;
	case DRAW_ELLIPSE:	// Draw ellipse
		pDoc->m_pDrawObject = new CDrawEllipse(point, point);
		pDoc->m_pDrawObject->m_FillFlag = pDoc->m_FillFlag;
		break;
	case DRAW_ROUNDRECT:	// Draw round rectangle
		pDoc->m_pDrawObject = new CDrawRoundRect(point, point, 20, 20);
		pDoc->m_pDrawObject->m_FillFlag = pDoc->m_FillFlag;
		break;
	}

	if (pDoc->m_pDrawObject)	// If the draw object not destroyed, do something here
	{
		pDoc->m_pDrawObject->m_BackgroundColor = pDoc->m_BackgroundColor;
		pDoc->m_pDrawObject->m_BrushColor = pDoc->m_BrushColor;
		if (pDoc->m_Mode != DRAW_ERASER)
		{
			pDoc->m_pDrawObject->m_PenColor = pDoc->m_PenColor;
			pDoc->m_pDrawObject->m_PenStyle = pDoc->m_PenStyle;
			if (pDoc->m_Mode != DRAW_BRUSH)
			{
				pDoc->m_pDrawObject->m_PenWidth = pDoc->m_PenWidth;
			}
		}
	}

	CScrollView::OnLButtonDown(nFlags, point);
}

void CToDrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CDC* pDC = GetDC();

	CPoint pOrig = GetScrollPosition();
	point += pOrig;		// Change screen point to logical point
	
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// Update status bar
	if (point.x <= pDoc->m_CanvasRect.right && point.y <= pDoc->m_CanvasRect.bottom)
	{
		CMainFrame* pMf = static_cast<CMainFrame*>(::AfxGetMainWnd());
		pMf->UpdateStatusBar(point);
	}

	if (m_pLMouseDown)
	{
		CDC dcMemSave;
		dcMemSave.CreateCompatibleDC(NULL);
		dcMemSave.SelectObject(&pDoc->m_bmpSave);

		CDC dcMem;
		dcMem.CreateCompatibleDC(NULL);
		dcMem.SelectObject(&pDoc->m_bmpBuf);

		dcMem.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);
		dcMem.SetBkColor(pDoc->m_BackgroundColor);
		dcMem.SetBkMode(pDoc->m_BackgroundMode);
		dcMem.SetROP2(R2_COPYPEN);

		switch (pDoc->m_Mode)
		{
		case DRAW_SELECT:	// Select something
			if (pDoc->m_isDrawOn)
			{
				pDoc->m_pDrawObject->m_pEnd = point;
				pDoc->m_pDrawObject->Draw(&dcMem);
			}
			else if (pDoc->m_isInSelect)
			{
				CDC dcMemSelect;
				dcMemSelect.CreateCompatibleDC(NULL);
				dcMemSelect.SelectObject(&pDoc->m_bmpSelect);
				dcMem.BitBlt(pDoc->m_SelectRect.left+point.x-pDoc->m_SelectPoint.x, pDoc->m_SelectRect.top+point.y-pDoc->m_SelectPoint.y, pDoc->m_SelectRect.Width(), pDoc->m_SelectRect.Height(), &dcMemSelect, 0, 0, SRCCOPY);
				
				pDoc->SetModifiedFlag();
			}
			break;
		case DRAW_ERASER:	// Erase something
			pDoc->m_pDrawObject->m_pEnd = point;
			pDoc->m_pDrawObject->Draw(&dcMem);
			dcMemSave.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
			pDoc->m_pDrawObject->m_pBegin = point;
			break;
		case DRAW_FILLING:	// Fill a region
			break;
		case DRAW_SAMPLING:	// Get color information of the poin
			pDoc->m_PenColor = pDC->GetPixel(point);
			break;
		case DRAW_PEN:	// Draw freely using a pen
			pDoc->m_pDrawObject->m_pEnd = point;
			pDoc->m_pDrawObject->Draw(&dcMem);
			dcMemSave.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
			pDoc->m_pDrawObject->m_pBegin = point;
			break;
		case DRAW_BRUSH:	// Draw freely using a brush
			pDoc->m_pDrawObject->m_pEnd = point;
			pDoc->m_pDrawObject->Draw(&dcMem);
			dcMemSave.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
			pDoc->m_pDrawObject->m_pBegin = point;
			break;		
		case DRAW_CURVE:	// Draw Bezier curve
			switch (pDoc->m_MouseDownTime)
			{
			case 1:
				pDoc->m_pDrawObject->m_pEnd = point;
				pDoc->m_pDrawObject->Draw(&dcMem);
				break;
			case 2:
				pDoc->m_pDrawObject->m_pHelp1 = point;
				pDoc->m_pDrawObject->m_pHelp2 = point;
				pDoc->m_pDrawObject->Draw(&dcMem);
				break;
			case 3:
				pDoc->m_pDrawObject->m_pHelp2 = point;
				pDoc->m_pDrawObject->Draw(&dcMem);
				break;
			}
			break;
		case DRAW_LINE:	// Line
		case DRAW_RECTANGLE:	// Rectangle
		case DRAW_POLYGON:	// Polygon
		case DRAW_ELLIPSE:	// Ellipse
		case DRAW_ROUNDRECT:	// Round rectangle
			pDoc->m_pDrawObject->m_pEnd = point;
			pDoc->m_pDrawObject->Draw(&dcMem);
			break;
		}

		// Copy memory to screen
		CRect rect;
		GetClientRect(&rect);
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, pOrig.x, pOrig.y, SRCCOPY);
	}

	CScrollView::OnMouseMove(nFlags, point);
}

void CToDrawView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (m_pLMouseDown)
	{
		m_pLMouseDown = FALSE;
		ReleaseCapture();

		CToDrawDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		CDC* pDC = GetDC();
		
		CDC dcMemSave;
		dcMemSave.CreateCompatibleDC(NULL);
		dcMemSave.SelectObject(&pDoc->m_bmpSave);

		CDC dcMem;
		dcMem.CreateCompatibleDC(NULL);
		dcMem.SelectObject(&pDoc->m_bmpBuf);

		dcMem.SetBkMode(pDoc->m_BackgroundMode);

		CPoint pOrig = GetScrollPosition();
		point += pOrig;	// Change screen point to logical point

		switch (pDoc->m_Mode)
		{
		case DRAW_SELECT:
			{
				CDC dcMemSelect;
				dcMemSelect.CreateCompatibleDC(NULL);
				dcMemSelect.SelectObject(&pDoc->m_bmpSelect); 

				if (pDoc->m_isDrawOn)
				{
					pDoc->m_isDrawOn = FALSE;
					pDoc->m_isSelected = TRUE;
					
					pDoc->m_pDrawObject->m_pEnd = point;
					pDoc->m_pDrawObject->m_FillFlag = pDoc->m_isSelected;
					dcMem.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);
					
					pDoc->m_pDrawObject->Draw(&dcMem);
					
					// Get selected region here
					CPoint p1(pDoc->m_pDrawObject->m_pBegin);
					CPoint p2(pDoc->m_pDrawObject->m_pEnd);
					if (p1.x > p2.x)	// Make p1 the lefttop point, and p2 the rightbottom point
					{
						p1.x ^= p2.x ^= p1.x ^= p2.x;
					}
					if (p1.y > p2.y)
					{
						p1.y ^= p2.y ^= p1.y ^= p2.y;
					}
					pDoc->m_SelectRect = CRect(p1, p2);

					pDoc->m_bmpSelect.DeleteObject();
					pDoc->m_bmpSelect.CreateCompatibleBitmap(pDC, pDoc->m_SelectRect.Width(), pDoc->m_SelectRect.Height()); 
					dcMemSelect.SelectObject(&pDoc->m_bmpSelect); 
					dcMemSelect.BitBlt(0, 0, pDoc->m_SelectRect.Width(), pDoc->m_SelectRect.Height(), &dcMemSave, pDoc->m_SelectRect.left, pDoc->m_SelectRect.top, SRCCOPY);
					
					CBrush Brush(pDoc->m_BackgroundColor);
					CBrush* pOldBrush = dcMemSave.SelectObject(&Brush);
					CRgn Rgn;
					Rgn.CreateRectRgn(pDoc->m_SelectRect.left, pDoc->m_SelectRect.top, pDoc->m_SelectRect.right, pDoc->m_SelectRect.bottom);
					dcMemSave.FillRgn(&Rgn, &Brush);
					dcMemSave.SelectObject(pOldBrush);
				}
				else
				{
					pDoc->m_pDrawObject->m_pBegin += (point - pDoc->m_SelectPoint);
					pDoc->m_pDrawObject->m_pEnd += (point - pDoc->m_SelectPoint);
					pDoc->m_pDrawObject->Draw(&dcMem);

					CPoint p1(pDoc->m_pDrawObject->m_pBegin);
					CPoint p2(pDoc->m_pDrawObject->m_pEnd);
					if (p1.x > p2.x)	// Make p1 the lefttop point, and p2 the rightbottom point
					{
						p1.x ^= p2.x ^= p1.x ^= p2.x;
					}
					if (p1.y > p2.y)
					{
						p1.y ^= p2.y ^= p1.y ^= p2.y;
					}
					pDoc->m_SelectRect = CRect(p1, p2);
				}
				CRect rect;
				GetClientRect(&rect);
				pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, pOrig.x, pOrig.y, SRCCOPY);
		
				pDoc->UpdateAllViews(this);
				return;	// It should return here to skip something below
			}
		case DRAW_CURVE:
			if (pDoc->m_MouseDownTime == 3)
			{
				pDoc->m_MouseDownTime = 0;
				delete pDoc->m_pDrawObject;
				pDoc->m_pDrawObject = 0;
				break;
			}
			else
			{
				pDoc->SetModifiedFlag();
				pDoc->UpdateAllViews(this);
				return;	// It should return here to skip something below
			}
		case DRAW_POLYGON:
			pDoc->m_pDrawObject->m_pBegin = point;
			break;
		case DRAW_SAMPLING:
			pDoc->m_Mode = DRAW_PEN;
			break;
		case DRAW_ERASER:
		case DRAW_FILLING:
		case DRAW_PEN:
		case DRAW_BRUSH:
		case DRAW_LINE:		
		case DRAW_RECTANGLE:
		case DRAW_ELLIPSE:
		case DRAW_ROUNDRECT:
			delete pDoc->m_pDrawObject;
			pDoc->m_pDrawObject = 0;
			break;
		}

		dcMemSave.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
		pDoc->SetModifiedFlag();

		// Copy memory to screen
		CRect rect;
		GetClientRect(&rect);
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemSave, pOrig.x, pOrig.y, SRCCOPY);
		
		pDoc->UpdateAllViews(this);	// Update all views of the document
	}

	CScrollView::OnLButtonUp(nFlags, point);
}

void CToDrawView::OnLButtonDblClk(UINT nFlags, CPoint point)	// Indeed just for completing drawing polygon, here
{
	// TODO: Add your message handler code here and/or call default
	
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC* pDC = GetDC();

	CDC dcMemSave;
	dcMemSave.CreateCompatibleDC(NULL);
	dcMemSave.SelectObject(&pDoc->m_bmpSave);

	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);
	dcMem.SelectObject(&pDoc->m_bmpBuf);

	dcMem.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);
	dcMem.SetBkColor(pDoc->m_BackgroundColor);
	dcMem.SetBkMode(pDoc->m_BackgroundMode);
	dcMem.SetROP2(R2_COPYPEN);

	CRect rect;
	GetClientRect(&rect);
	CPoint pOrig = GetScrollPosition();
	point += pOrig;

	pDoc->m_pDrawObject->m_pEnd = point;

	switch (pDoc->m_Mode)
	{
	case DRAW_SELECT:
	case DRAW_ERASER:
	case DRAW_FILLING:
	case DRAW_SAMPLING:
	case DRAW_PEN:
	case DRAW_BRUSH:
	case DRAW_LINE:		
	case DRAW_CURVE:
	case DRAW_RECTANGLE:
	case DRAW_ELLIPSE:
	case DRAW_ROUNDRECT:
		break;
	case DRAW_POLYGON:
		pDoc->m_pDrawObject->m_pBegin = pDoc->m_pDrawObject->m_pInit;
		pDoc->m_pDrawObject->m_pEnd = point;
		pDoc->m_pDrawObject->Draw(&dcMem);
		
		dcMemSave.BitBlt(0, 0, pDoc->m_bmpInfo.bmWidth, pDoc->m_bmpInfo.bmHeight, &dcMem, 0, 0, SRCCOPY);
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemSave, pOrig.x, pOrig.y, SRCCOPY);
		
		delete pDoc->m_pDrawObject;
		pDoc->m_pDrawObject = 0;
		pDoc->m_isDrawOn = FALSE;
	
		pDoc->SetModifiedFlag();
		break;
	}

	pDoc->UpdateAllViews(this);	// Update all view

	CScrollView::OnLButtonDblClk(nFlags, point);
}

UINT CToDrawView::IDtoDrawMode(UINT nID) const	// Get ID of diffient objects, return a mark of it
{
	switch (nID)
	{
	case ID_SELECT:
		return DRAW_SELECT;
	case ID_ERASER:
		return DRAW_ERASER;
	case ID_FILLING:
		return DRAW_FILLING;
	case ID_SAMPLING:
		return DRAW_SAMPLING;
	case ID_PEN:
		return DRAW_PEN;
	case ID_BRUSH:
		return DRAW_BRUSH;
	case ID_LINE:
		return DRAW_LINE;
	case ID_CURVE:
		return DRAW_CURVE;
	case ID_RECTANGLE:
		return DRAW_RECTANGLE;
	case ID_POLYGON:
		return DRAW_POLYGON;
	case ID_ELLIPSE:
		return DRAW_ELLIPSE;
	case ID_ROUNDRECT:
		return DRAW_ROUNDRECT;
	default:
		return DRAW_SELECT;
	}
}

void CToDrawView::OnToolBox(UINT nID)	// Response message on tool box
{
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC* pDC = GetDC();

	CDC dcMemSave;
	dcMemSave.CreateCompatibleDC(NULL);
	dcMemSave.SelectObject(&pDoc->m_bmpSave);

	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);
	dcMem.SelectObject(&pDoc->m_bmpBuf);

	dcMem.SetBkColor(pDoc->m_BackgroundColor);
	dcMem.SetBkMode(pDoc->m_BackgroundMode);
	dcMem.SetROP2(R2_COPYPEN);

	CPoint pOrig = GetScrollPosition();	// Get original point of screen

	// Here before choose to draw another thing, complete draw things before
	switch (pDoc->m_Mode)
	{
	case DRAW_SELECT:
		{
			dcMem.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);
			CDC dcMemSelect;
			dcMemSelect.CreateCompatibleDC(NULL);
			dcMemSelect.SelectObject(&pDoc->m_bmpSelect);
			dcMem.BitBlt(pDoc->m_SelectRect.left, pDoc->m_SelectRect.top, pDoc->m_SelectRect.Width(), pDoc->m_SelectRect.Height(), &dcMemSelect, 0, 0, SRCCOPY);
			dcMemSave.BitBlt(0, 0, pDoc->m_bmpInfo.bmWidth, pDoc->m_bmpInfo.bmHeight, &dcMem, 0, 0, SRCCOPY);
			CRect rect;
			GetClientRect(&rect);
			pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemSave, pOrig.x, pOrig.y, SRCCOPY);
		}
		break;
	case DRAW_ERASER:
	case DRAW_FILLING:
	case DRAW_SAMPLING:
	case DRAW_PEN:
	case DRAW_BRUSH:
	case DRAW_LINE:
	case DRAW_RECTANGLE:
	case DRAW_ELLIPSE:
	case DRAW_ROUNDRECT:
		break;
	case DRAW_CURVE:
		if (pDoc->m_MouseDownTime > 0)
		{
			pDoc->m_MouseDownTime = 0;
			dcMemSave.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
			delete pDoc->m_pDrawObject;
			pDoc->m_pDrawObject = 0;
		}
		break;
	case DRAW_POLYGON:
		dcMem.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);
		if (pDoc->m_isDrawOn)
		{
			pDoc->m_pDrawObject->m_pBegin = pDoc->m_pDrawObject->m_pInit;
			pDoc->m_pDrawObject->Draw(&dcMem);
			
			dcMemSave.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
			CRect rect;
			GetClientRect(&rect);
			pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemSave, pOrig.x, pOrig.y, SRCCOPY);

			delete pDoc->m_pDrawObject;
			pDoc->m_pDrawObject = 0;
			pDoc->m_isDrawOn = FALSE;
		
			pDoc->SetModifiedFlag();
		}
		break;
	}

	pDoc->m_Mode = IDtoDrawMode(nID);

	delete pDoc->m_pDrawObject;
	pDoc->m_pDrawObject = 0;
	pDoc->m_isDrawOn = FALSE;
	pDoc->m_isSelected = FALSE;
	pDoc->m_isInSelect = FALSE;
	pDoc->m_MouseDownTime = 0;
}

void CToDrawView::OnUpdateToolBox(CCmdUI* pCmdUI)
{
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetCheck(pDoc->m_Mode == IDtoDrawMode(pCmdUI->m_nID));
}

UINT CToDrawView::IDtoPenColor(UINT nID) const	// Get ID of diffient colors, return the color
{
	switch (nID)
	{
	case ID_BLACK:
		return COLOR_BLACK;
	case ID_WHITE:
		return COLOR_WHITE;
	case ID_GREEN:
		return COLOR_GREEN;
	case ID_BLUE:
		return COLOR_BLUE;
	case ID_DARKGREEN:
		return COLOR_DARKGREEN;
	case ID_YELLOW:
		return COLOR_YELLOW;
	case ID_PINK:
		return COLOR_PINK;
	case ID_DRAKRED:
		return COLOR_DARKRED;
	case ID_GRAY:
		return COLOR_GRAY;
	case ID_PURPLE:
		return COLOR_PURPLE;
	case ID_DARKYELLOW:
		return COLOR_DARKYELLOW;
	case ID_CYAN:
		return COLOR_CYAN;
	case ID_DARKCYAN:
		return COLOR_DARKCYAN;
	case ID_DARKBLUE:
		return COLOR_DARKBLUE;
	case ID_DARKGRAY:
		return COLOR_DARKGRAY;
	case ID_RED:
		return COLOR_RED;
	default:
		return COLOR_BLACK;
	}
}

void CToDrawView::OnColorBox(UINT nID)	// Response message of color box
{
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_PenColor = IDtoPenColor(nID);
	pDoc->m_BrushColor = pDoc->m_PenColor;
	m_pDlg->m_FrColor = pDoc->m_PenColor;
	if (m_pDlg)	// Update property box
	{
		m_pDlg->m_ctrFrColor.Invalidate();
		CPaintDC dcFr(&m_pDlg->m_ctrFrColor);
		CRect rectFr;
		m_pDlg->m_ctrFrColor.GetClientRect(&rectFr);
		CBrush brushFr(m_pDlg->m_FrColor);
		dcFr.FillRect(&rectFr, &brushFr);
	}
}

void CToDrawView::OnUpdateColorBox(CCmdUI* pCmdUI)
{
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->SetCheck(pDoc->m_PenColor == IDtoPenColor(pCmdUI->m_nID));
}

void CToDrawView::OnToolStyleBox(UINT nID)	// Response message of tool style box
{
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch(nID)
	{
	case ID_ONEPIXEL:
		pDoc->m_PenWidth = 1;
		break;
	case ID_TWOPIXEL:
		pDoc->m_PenWidth = 2;
		break;
	case ID_FOURPIXEL:
		pDoc->m_PenWidth = 4;
		break;
	case ID_SIXPIXEL:
		pDoc->m_PenWidth = 6;
		break;
	case ID_EMPTY:
		pDoc->m_FillFlag = FALSE;
		break;
	case ID_FULL:
		pDoc->m_FillFlag = TRUE;
		break;
	case ID_PS_SOLID:
		pDoc->m_PenStyle = PS_SOLID;
		break;
	case ID_PS_DOT:
		pDoc->m_PenStyle = PS_DOT;
		break;
	case ID_PS_DASH:
		pDoc->m_PenStyle = PS_DASH;
		break;
	case ID_PS_DASHDOT:
		pDoc->m_PenStyle = PS_DASHDOT;
		break;
	case ID_PS_DASHDOTDOT:
		pDoc->m_PenStyle = PS_DASHDOTDOT;
		break;
	}
}

void CToDrawView::OnUpdateToolStyleBox(CCmdUI* pCmdUI)
{
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch(pCmdUI->m_nID)
	{
	case ID_ONEPIXEL:
		pCmdUI->SetCheck(pDoc->m_PenWidth == 1);
		break;
	case ID_TWOPIXEL:
		pCmdUI->SetCheck(pDoc->m_PenWidth == 2);
		break;
	case ID_FOURPIXEL:
		pCmdUI->SetCheck(pDoc->m_PenWidth == 4);
		break;
	case ID_SIXPIXEL:
		pCmdUI->SetCheck(pDoc->m_PenWidth == 6);
		break;
	case ID_EMPTY:
		pCmdUI->SetCheck(pDoc->m_FillFlag == FALSE);
		break;
	case ID_FULL:
		pCmdUI->SetCheck(pDoc->m_FillFlag == TRUE);
		break;
	case ID_PS_SOLID:
		pCmdUI->SetCheck(pDoc->m_PenStyle == PS_SOLID);
		break;
	case ID_PS_DOT:
		pCmdUI->SetCheck(pDoc->m_PenStyle == PS_DOT);
		break;
	case ID_PS_DASH:
		pCmdUI->SetCheck(pDoc->m_PenStyle == PS_DASH);
		break;
	case ID_PS_DASHDOT:
		pCmdUI->SetCheck(pDoc->m_PenStyle == PS_DASHDOT);
		break;
	case ID_PS_DASHDOTDOT:
		pCmdUI->SetCheck(pDoc->m_PenStyle == PS_DASHDOTDOT);
		break;
	}
}

BOOL CToDrawView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default

	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch (pDoc->m_Mode)
	{
	case DRAW_SELECT:
		break;
	case DRAW_ERASER:
	case DRAW_FILLING:
	case DRAW_SAMPLING:
	case DRAW_PEN:
	case DRAW_BRUSH:
	case DRAW_LINE:		
	case DRAW_CURVE:
	case DRAW_RECTANGLE:
	case DRAW_POLYGON:
	case DRAW_ELLIPSE:
	case DRAW_ROUNDRECT:
		HCURSOR HCursor;
		HCursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
		SetCursor(HCursor);

		return TRUE;	// Should be return here
	}
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CToDrawView::OnContextMenu(CWnd* pWnd, CPoint point) // Pop up context menu
{
	// TODO: Add your message handler code here
	
	CMenu menu;

	VERIFY(menu.LoadMenu(IDR_CONTEXT_MENU));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CToDrawView::OnImageClear() // Response to clear image use background color
{
	// TODO: Add your command handler code here
	
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CPoint pOrig = GetScrollPosition();	// Get original point of screen

	CDC* pDC = GetDC();

	CDC dcMemSave;
	dcMemSave.CreateCompatibleDC(NULL);
	dcMemSave.SelectObject(pDoc->m_bmpSave);

	CBrush Brush(pDoc->m_BackgroundColor);
	CBrush* pOldBrush = dcMemSave.SelectObject(&Brush);
	CRgn Rgn;
	Rgn.CreateRectRgn(pDoc->m_CanvasRect.left, pDoc->m_CanvasRect.top, pDoc->m_CanvasRect.right, pDoc->m_CanvasRect.bottom);
	dcMemSave.FillRgn(&Rgn, &Brush);
	dcMemSave.SelectObject(pOldBrush);

	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemSave, pOrig.x, pOrig.y, SRCCOPY);

	delete pDoc->m_pDrawObject;
	pDoc->m_pDrawObject = 0;

	pDoc->m_isDrawOn = FALSE;
	pDoc->m_isSelected = FALSE;
	pDoc->m_isInSelect = FALSE;
}


void CToDrawView::OnImageProperty()	// response property page message
{
	// TODO: Add your command handler code here
	
	if (m_pDlg)
	{
		return;
	}

	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	m_pDlg = new CPropertyDialog(this);
	m_pDlg->Create(IDD_PROPPAGE);

	CRect rect;
	m_pDlg->GetClientRect(&rect);
	CPoint point(580, 20);
	m_pDlg->ClientToScreen(&point);

	m_pDlg->SetWindowPos(m_pDlg->GetParent(), point.x, point.y, rect.Width()+8, rect.Height()+25, SWP_SHOWWINDOW);
	m_pDlg->ShowWindow(SW_RESTORE);

	CPaintDC dcBk(&m_pDlg->m_ctrBkColor);
	CRect rectBk;
	m_pDlg->m_ctrBkColor.GetClientRect(&rectBk);
	m_pDlg->m_BkColor = pDoc->m_BackgroundColor;
	CBrush brushBk(m_pDlg->m_BkColor);
	dcBk.FillRect(&rectBk, &brushBk);

	CPaintDC dcFr(&m_pDlg->m_ctrFrColor);
	CRect rectFr;
	m_pDlg->m_ctrFrColor.GetClientRect(&rectFr);
	m_pDlg->m_FrColor = pDoc->m_PenColor;
	CBrush brushFr(m_pDlg->m_FrColor);
	dcFr.FillRect(&rectFr, &brushFr);

	m_pDlg->m_nHeight = pDoc->m_CanvasRect.Height();
	m_pDlg->m_nWidth = pDoc->m_CanvasRect.Width();
	m_pDlg->UpdateData(FALSE);
}

void CToDrawView::OnColorCustom() 
{
	// TODO: Add your command handler code here
	
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		pDoc->m_PenColor = dlg.GetColor();
		pDoc->m_BrushColor = pDoc->m_PenColor; 
	}
}

LRESULT CToDrawView::MyMessageHandler(WPARAM wParam, LPARAM lParam)	// Response message of controls of property page
{
	CToDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	switch (wParam)
	{
		case TD_APPLY:	// Apply the change here
			if (static_cast<UINT>(pDoc->m_CanvasRect.Width()) != m_pDlg->m_nWidth || static_cast<UINT>(pDoc->m_CanvasRect.Height()) != m_pDlg->m_nHeight)
			{	// Change ths size of Canvas here

				CPoint pOrig = GetScrollPosition();	// Get original point of screen

				CDC* pDC = GetDC();

				CBitmap bmpSave;
				bmpSave.CreateCompatibleBitmap(pDC, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height());
				
				CBitmap bmpBuf;
				bmpBuf.CreateCompatibleBitmap(pDC, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height());

				CDC dcMemSaveTemp;
				dcMemSaveTemp.CreateCompatibleDC(NULL);
				dcMemSaveTemp.SelectObject(bmpSave);

				CDC dcMemTemp;
				dcMemTemp.CreateCompatibleDC(NULL);
				dcMemTemp.SelectObject(bmpBuf);

				CDC dcMemSave;
				dcMemSave.CreateCompatibleDC(NULL);
				dcMemSave.SelectObject(&pDoc->m_bmpSave);

				CDC dcMem;
				dcMem.CreateCompatibleDC(NULL);
				dcMem.SelectObject(&pDoc->m_bmpBuf);
				
				// Complete draw task first here
				switch (pDoc->m_Mode)
				{
				case DRAW_SELECT:
					{
						dcMem.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);
						CDC dcMemSelect;
						dcMemSelect.CreateCompatibleDC(NULL);
						dcMemSelect.SelectObject(&pDoc->m_bmpSelect);
						dcMem.BitBlt(pDoc->m_SelectRect.left, pDoc->m_SelectRect.top, pDoc->m_SelectRect.Width(), pDoc->m_SelectRect.Height(), &dcMemSelect, 0, 0, SRCCOPY);
						dcMemSave.BitBlt(0, 0, pDoc->m_bmpInfo.bmWidth, pDoc->m_bmpInfo.bmHeight, &dcMem, 0, 0, SRCCOPY);
					}
					break;
				case DRAW_ERASER:
				case DRAW_FILLING:
				case DRAW_SAMPLING:
				case DRAW_PEN:
				case DRAW_BRUSH:
				case DRAW_LINE:
				case DRAW_RECTANGLE:
				case DRAW_ELLIPSE:
				case DRAW_ROUNDRECT:
					break;
				case DRAW_CURVE:
					if (pDoc->m_MouseDownTime > 0)
					{
						pDoc->m_MouseDownTime = 0;
						dcMemSave.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
					}
					break;
				case DRAW_POLYGON:
					dcMem.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);
					if (pDoc->m_isDrawOn)
					{
						pDoc->m_pDrawObject->m_pBegin = pDoc->m_pDrawObject->m_pInit;
						pDoc->m_pDrawObject->Draw(&dcMem);
						
						dcMemSave.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
					}
					break;
				}
				
				// Adjust size of memory to story image
				dcMemSaveTemp.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);
				dcMemTemp.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
				
				pDoc->m_bmpSave.DeleteObject();
				pDoc->m_bmpSave.CreateCompatibleBitmap(pDC, m_pDlg->m_nWidth, m_pDlg->m_nHeight);
				
				pDoc->m_bmpBuf.DeleteObject();
				pDoc->m_bmpBuf.CreateCompatibleBitmap(pDC, m_pDlg->m_nWidth, m_pDlg->m_nHeight);
				
				dcMemSave.SelectObject(&pDoc->m_bmpSave);
				dcMem.SelectObject(&pDoc->m_bmpBuf);
				
				CRect rect;
				rect.SetRect(0, 0, m_pDlg->m_nWidth, m_pDlg->m_nHeight);
				CBrush brush(pDoc->m_BackgroundColor);
				dcMemSave.FillRect(&rect, &brush);
				dcMem.FillRect(&rect, &brush);
				dcMemSave.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemSaveTemp, 0, 0, SRCCOPY);
				dcMem.BitBlt(0, 0, pDoc->m_CanvasRect.Width(), pDoc->m_CanvasRect.Height(), &dcMemTemp, 0, 0, SRCCOPY);
				
				pDoc->m_bmpSave.GetBitmap(&(pDoc->m_bmpInfo));

				pDoc->m_CanvasRect.right = m_pDlg->m_nWidth;
				pDoc->m_CanvasRect.bottom = m_pDlg->m_nHeight;
				
				pDoc->SetModifiedFlag(TRUE);
				pDoc->m_Saved = FALSE;

				// Resize scroll region here
				CSize sizeTotal;
				sizeTotal.cx = m_pDlg->m_nWidth + 100;
				sizeTotal.cy = m_pDlg->m_nHeight + 150;
				SetScrollSizes(MM_TEXT, sizeTotal);
				
				delete pDoc->m_pDrawObject;
				pDoc->m_pDrawObject = 0;
				pDoc->m_isDrawOn = FALSE;
				pDoc->m_isSelected = FALSE;
				pDoc->m_isInSelect = FALSE;
				pDoc->m_MouseDownTime = 0;

				// Copy image from memory to screen
				Invalidate();
				CRect rect2;
				GetClientRect(&rect2);
				pDC->BitBlt(0, 0, rect2.Width(), rect2.Height(), &dcMem, pOrig.x, pOrig.y, SRCCOPY);
				
				pDoc->UpdateAllViews(this);	// Update all views
			}
			break;
		case TD_CANCEL:
			m_pDlg = 0;
			break;
		case TD_BKCOLOR:	// Apply Background color
			{
				CColorDialog dlg(m_pDlg->m_BkColor);

				if (dlg.DoModal() == IDOK)
				{
					m_pDlg->m_BkColor = dlg.GetColor();

					m_pDlg->m_ctrBkColor.Invalidate();
					CPaintDC dcBk(&m_pDlg->m_ctrBkColor);
					CRect rectBk;
					m_pDlg->m_ctrBkColor.GetClientRect(&rectBk);
					CBrush brushBk(m_pDlg->m_BkColor);
					dcBk.FillRect(&rectBk, &brushBk);

					CButton* pcb = static_cast<CButton*>(m_pDlg->GetDlgItem(IDC_APPLY));
					pcb->EnableWindow();
					pcb->SetFocus();
					pDoc->m_BackgroundColor = m_pDlg->m_BkColor;
					pDoc->m_PenColor = m_pDlg->m_FrColor;
					pDoc->m_BrushColor = m_pDlg->m_FrColor;
				}
			}
			break;
		case TD_FRCOLOR:	// Apply Pencolor and Brushcolor
			{
				CColorDialog dlg(m_pDlg->m_FrColor);

				if (dlg.DoModal() == IDOK)
				{
					m_pDlg->m_FrColor = dlg.GetColor();

					m_pDlg->m_ctrFrColor.Invalidate();
					CPaintDC dcFr(&m_pDlg->m_ctrFrColor);
					CRect rectFr;
					m_pDlg->m_ctrFrColor.GetClientRect(&rectFr);
					CBrush brushFr(m_pDlg->m_FrColor);
					dcFr.FillRect(&rectFr, &brushFr);
					
					CButton* pcb = static_cast<CButton*>(m_pDlg->GetDlgItem(IDC_APPLY));
					pcb->EnableWindow();
					pcb->SetFocus();
					pDoc->m_BackgroundColor = m_pDlg->m_BkColor;
					pDoc->m_PenColor = m_pDlg->m_FrColor;
					pDoc->m_BrushColor = m_pDlg->m_FrColor;
				}
			}
			break;
	}
	return TRUE;
}

void CToDrawView::OnDestroy()
{
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here

	if (this->m_pDlg)	// Destroy property page dialog here
	{
		delete this->m_pDlg;
		this->m_pDlg = 0;
	}
}

void CToDrawView::OnUpdateImageProperty(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

	pCmdUI->SetCheck(m_pDlg != 0);
}

BOOL CToDrawView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (!CScrollView::OnScroll(nScrollCode, nPos, bDoScroll))
	{
		return FALSE;
	}

	CDC* pDC = GetDC();
	OnDraw(pDC);

	return TRUE;
}

BOOL CToDrawView::OnEraseBkgnd(CDC* pDC) 
{
	return CScrollView::OnEraseBkgnd(pDC);

	// The below commented codes were used to make the background
	// not glinted. It does. But something was wrong when with 
	// splited window. Pitty!
	
// 	CToDrawDoc* pDoc = GetDocument();
// 	ASSERT_VALID(pDoc);
// 
// 	CRect rect;
// 	GetClientRect(&rect);
// 	CRgn rgn1;
// 	rgn1.CreateRectRgnIndirect(&rect);
// 	CRgn rgn2;
// 	rgn2.CreateRectRgnIndirect(&pDoc->m_CanvasRect);
// 	CRgn rgn;
// 	int ret = rgn1.CombineRgn(&rgn1, &rgn2, RGN_DIFF);
// 	if (ret != ERROR && ret != NULLREGION)
// 	{
// 		CBrush brush;
// 		brush.CreateSolidBrush(GetSysColor(COLOR_3DSHADOW));
// 		pDC->FillRgn(&rgn1, &brush);
// 	}
//	return TRUE;
}
