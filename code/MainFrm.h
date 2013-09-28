// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__5DD024DC_1CB9_45F4_8A12_369494C572C5__INCLUDED_)
#define AFX_MAINFRM_H__5DD024DC_1CB9_45F4_8A12_369494C572C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	void DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf);	// Dock bar right of another bar
	void UpdateStatusBar(CPoint point);	// Update point on the status bar

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar	m_wndToolBox;	// User defined
	CToolBar	m_wndColorBox;	// User defined
	CToolBar	m_wndToolStyleBox;	// User defined

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewToolbox();
	afx_msg void OnUpdateViewToolbox(CCmdUI* pCmdUI);
	afx_msg void OnViewColorbox();
	afx_msg void OnUpdateViewColorbox(CCmdUI* pCmdUI);
	afx_msg void OnViewToolstylebox();
	afx_msg void OnUpdateViewToolstylebox(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__5DD024DC_1CB9_45F4_8A12_369494C572C5__INCLUDED_)
