// ToDrawDoc.cpp : implementation of the CToDrawDoc class
//

#include "stdafx.h"
#include "ToDraw.h"

#include "ToDrawDoc.h"

#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToDrawDoc

IMPLEMENT_DYNCREATE(CToDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CToDrawDoc, CDocument)
	//{{AFX_MSG_MAP(CToDrawDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToDrawDoc construction/destruction

CToDrawDoc::CToDrawDoc() : m_PenColor(RGB(0, 0, 0)), m_BrushColor(RGB(0, 0, 0)),
	m_BackgroundColor(RGB(255, 255, 255)), m_PenWidth(1), m_FillFlag(FALSE),
	m_CanvasRect(CRect(0, 0, STD_WIDTH, STD_HEIGHT)), m_Mode(DRAW_SELECT),
	m_pDrawObject(0), m_isDrawOn(FALSE), m_BackgroundMode(OPAQUE),
	m_Saved(FALSE), m_FileName(""), m_isSelected(FALSE), m_SelectRect(CRect(0, 0, 0, 0)),
	m_PenStyle(PS_SOLID), m_isInSelect(FALSE), m_MouseDownTime(0), m_Init(FALSE)
{
	// TODO: add one-time construction code here

}

CToDrawDoc::~CToDrawDoc()
{
}

BOOL CToDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CToDrawDoc serialization

void CToDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CToDrawDoc diagnostics

#ifdef _DEBUG
void CToDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToDrawDoc commands

BOOL CToDrawDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//return CDocument::OnSaveDocument(lpszPathName);

	return SaveBmp(lpszPathName);	// Save bitmap file
}

BOOL CToDrawDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (!CDocument::SaveModified())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CToDrawDoc::OpenBmp(LPCTSTR lpszPathName)	// Open bitmap file
{
	m_FileName = lpszPathName;
	HBITMAP hbmp = (HBITMAP)LoadImage(NULL, _T(m_FileName), IMAGE_BITMAP,
		0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	
	m_bmpSave.Attach(hbmp);

	m_bmpSave.GetBitmap(&m_bmpInfo);
	
	m_CanvasRect.left = 0;
	m_CanvasRect.right = m_bmpInfo.bmWidth;
	m_CanvasRect.top = 0;
	m_CanvasRect.bottom = m_bmpInfo.bmHeight;
	m_Saved = TRUE;

	return TRUE;
}

BOOL CToDrawDoc::SaveBmp(LPCTSTR lpszPathName)	// Save bitmap file
{
	CDC dcMemSave;
	dcMemSave.CreateCompatibleDC(NULL);
	dcMemSave.SelectObject(&m_bmpSave);

	CDC dcMem;
	dcMem.CreateCompatibleDC(NULL);
	dcMem.SelectObject(&m_bmpBuf);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dcMemSave, m_CanvasRect.Width(), m_CanvasRect.Height());

	CDC dcMemTemp;
	dcMemTemp.CreateCompatibleDC(NULL);
	CBitmap* pOldBmp = dcMemTemp.SelectObject(&bmp);
	dcMemTemp.BitBlt(0, 0, m_CanvasRect.Width(), m_CanvasRect.Height(), &dcMemSave, 0, 0, SRCCOPY);

	if (m_isSelected)
	{
		CDC dcMemSelect;
		dcMemSelect.CreateCompatibleDC(NULL);
		dcMemSelect.SelectObject(&m_bmpSelect);
		
		dcMemTemp.BitBlt(m_SelectRect.left, m_SelectRect.top, m_SelectRect.Width(), m_SelectRect.Height(), &dcMemSelect, 0, 0, SRCCOPY);
	}
	if (m_MouseDownTime > 0)
	{
		dcMemTemp.BitBlt(0, 0, m_CanvasRect.Width(), m_CanvasRect.Height(), &dcMem, 0, 0, SRCCOPY);
	}

	bmp.GetBitmap(&(m_bmpInfo));
	DWORD size = m_bmpInfo.bmWidthBytes * m_bmpInfo.bmHeight;
	LPSTR lpData = (LPSTR)GlobalAllocPtr(GPTR, size);

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	bih.biBitCount = m_bmpInfo.bmBitsPixel;
	bih.biClrImportant = 0;
	bih.biClrUsed = 0;
	bih.biCompression = 0;
	bih.biHeight = m_bmpInfo.bmHeight;
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = size;
	bih.biWidth = m_bmpInfo.bmWidth;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;

	
	GetDIBits(dcMemTemp, bmp, 0, bih.biHeight, lpData, (BITMAPINFO*)&bih, DIB_RGB_COLORS);
	// m_bmpTemp.GetBitmapBits(size,lpData);
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType = ((WORD)('M'<< 8)|'B');
	bfh.bfSize = 54 + size;
	bfh.bfOffBits = 54;

	CFile bf;
	if(bf.Open(lpszPathName, CFile::modeCreate | CFile::modeWrite))
	{
		bf.WriteHuge(&bfh, sizeof(BITMAPFILEHEADER));
		bf.WriteHuge(&bih, sizeof(BITMAPINFOHEADER));
		bf.WriteHuge(lpData, size);
		bf.Close();

		SetModifiedFlag(FALSE);
	}
	GlobalFreePtr(lpData);
	
	dcMemTemp.SelectObject(pOldBmp);
	bmp.DeleteObject();
	m_Saved = TRUE;

	return TRUE;
}


BOOL CToDrawDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	//if (!CDocument::OnOpenDocument(lpszPathName))
	//	return FALSE;
	
	// TODO: Add your specialized creation code here

	return OpenBmp(lpszPathName);	// Open bitmap file
}
