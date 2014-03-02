#if !defined(AFX_PROPERTYDIALOG_H__58F5848D_4211_41AE_BB80_8E0082366449__INCLUDED_)
#define AFX_PROPERTYDIALOG_H__58F5848D_4211_41AE_BB80_8E0082366449__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyDialog.h : header file
//

#define CPROPERTYDIALOG_MSG "Property_Msg"	// User defined message
#define TD_APPLY 1	// More information for user defined message
#define TD_CANCEL 2
#define TD_BKCOLOR 3
#define TD_FRCOLOR 4

/////////////////////////////////////////////////////////////////////////////
// CPropertyDialog dialog

class CPropertyDialog : public CDialog
{
// Construction
public:
	CPropertyDialog(CWnd *pWnd, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropertyDialog)
	enum { IDD = IDD_PROPPAGE };
	CStatic	m_ctrFrColor;
	CStatic	m_ctrBkColor;
	UINT	m_nHeight;
	UINT	m_nWidth;
	//}}AFX_DATA

	COLORREF m_BkColor;	// Color of a static control for background color
	COLORREF m_FrColor;	// Color of a static control for foreground color	
protected:
	CWnd * m_pWnd;
	UINT m_UserMsg;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertyDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnApply();
	afx_msg void OnCancel();
	afx_msg void OnBkcolor();
	afx_msg void OnFrcolor();
	afx_msg void EnableApplyButton(); 
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYDIALOG_H__58F5848D_4211_41AE_BB80_8E0082366449__INCLUDED_)
