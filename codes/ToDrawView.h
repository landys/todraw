// ToDrawView.h : interface of the CToDrawView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TODRAWVIEW_H__1CFAAB72_2447_4130_B51B_4CF7CBE07723__INCLUDED_)
#define AFX_TODRAWVIEW_H__1CFAAB72_2447_4130_B51B_4CF7CBE07723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PropertyDialog.h"

class CToDrawView : public CScrollView
{
protected: // create from serialization only
	CToDrawView();
	DECLARE_DYNCREATE(CToDrawView)

// Attributes
public:
	CToDrawDoc* GetDocument();

private:
	BOOL m_pLMouseDown;	// Mark whether mouse down
	HCURSOR m_HCursor;	// Store diffient cursors

	CPropertyDialog* m_pDlg;	// A point to a user defined cursor

	static UINT m_UserMsg;	// User defined message

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToDrawView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	UINT IDtoDrawMode(UINT nID) const;	// Get ID of diffient objects, return a mark of it
	UINT IDtoPenColor(UINT nID) const;	// Get ID of diffient colors, return the color

// Generated message map functions
protected:
	//{{AFX_MSG(CToDrawView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnImageClear();
	afx_msg void OnImageProperty();
	afx_msg void OnColorCustom();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateImageProperty(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg void OnToolBox(UINT nID);	// Response toolbox message
	afx_msg void OnUpdateToolBox(CCmdUI* pCmdUI);

	afx_msg void OnColorBox(UINT nID);	// Response colorbox message
	afx_msg void OnUpdateColorBox(CCmdUI* pCmdUI);

	afx_msg void OnToolStyleBox(UINT nID);	// Response toolstylebox message
	afx_msg void OnUpdateToolStyleBox(CCmdUI* pCmdUI);

	afx_msg LRESULT MyMessageHandler(WPARAM wParam, LPARAM lParam);	// Response function of user defined dialog

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ToDrawView.cpp
inline CToDrawDoc* CToDrawView::GetDocument()
   { return (CToDrawDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TODRAWVIEW_H__1CFAAB72_2447_4130_B51B_4CF7CBE07723__INCLUDED_)
