// ToDrawDoc.h : interface of the CToDrawDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TODRAWDOC_H__BB64B9B9_B77B_482F_9C79_B178B8D958D7__INCLUDED_)
#define AFX_TODRAWDOC_H__BB64B9B9_B77B_482F_9C79_B178B8D958D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Draw.h"

class CToDrawDoc : public CDocument
{
protected: // create from serialization only
	CToDrawDoc();
	DECLARE_DYNCREATE(CToDrawDoc)

// Attributes
public:
	CRect m_CanvasRect;	// Canvas to draw

	int m_PenStyle;	// Pen style
	COLORREF m_PenColor;	// Pen color
	COLORREF m_BrushColor;	// Brush color
	COLORREF m_BackgroundColor;	// Background color
	int m_BackgroundMode;	// Background mode
	int m_PenWidth;	// Pen width
	BOOL m_FillFlag;	// Use for check if it should be filled
	BOOL m_isDrawOn;	// Mark whether drawing
	BOOL m_isSelected;	// Mark whether a region is selected
	BOOL m_isInSelect;	// Mark whether the cursor is in the selected area
	CRect m_SelectRect;	// Selected region
	CPoint m_SelectPoint;	// Point of cursor before move selected region
	CBitmap m_bmpSelect;	// bitmap in memory to save selected region

	CBitmap m_bmpBuf;	// A memory buffer for drawing, all draw here, then copy to another memory buffer
	
	CBitmap m_bmpSave;	// A memory buffer to store draw before copying to screen
	BITMAP m_bmpInfo;	// Bitmap information

	UINT m_Mode;	// Different things to be drawn, like a line, a curve, ect.

	CDrawObject* m_pDrawObject;	// A point to a drawn object

	BOOL m_Saved;	// mark whether saved
	CString m_FileName;	// File name including path

	int m_MouseDownTime;	// For drawing Beazier curve, count times of mouse down

	BOOL m_Init;	// For multiview, mark whether some argumenta have been initialed

// Operations
public:
	BOOL OpenBmp(LPCTSTR lpszPathName);	// Open bitmap file
	BOOL SaveBmp(LPCTSTR lpszPathName);	// Save bitmap file
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToDrawDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CToDrawDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TODRAWDOC_H__BB64B9B9_B77B_482F_9C79_B178B8D958D7__INCLUDED_)
