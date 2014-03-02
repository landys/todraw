// PropertyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ToDraw.h"
#include "Draw.h"
#include "PropertyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyDialog dialog


CPropertyDialog::CPropertyDialog(CWnd *pWnd, CWnd* pParent /*=NULL*/)
	: CDialog(CPropertyDialog::IDD, pParent), m_pWnd(pWnd)
{
	//{{AFX_DATA_INIT(CPropertyDialog)
	m_nHeight = 0;
	m_nWidth = 0;
	//}}AFX_DATA_INIT
	
	m_BkColor = RGB(255, 255, 255);
	m_FrColor = RGB(0, 0, 0);

	m_UserMsg = ::RegisterWindowMessage(CPROPERTYDIALOG_MSG);
}


void CPropertyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyDialog)
	DDX_Control(pDX, IDC_FRCOLOR, m_ctrFrColor);
	DDX_Control(pDX, IDC_BKCOLOR, m_ctrBkColor);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDV_MinMaxUInt(pDX, m_nHeight, 1, 9999);
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDV_MinMaxUInt(pDX, m_nWidth, 1, 9999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyDialog, CDialog)
	//{{AFX_MSG_MAP(CPropertyDialog)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_BN_CLICKED(IDC_BKCOLOR, OnBkcolor)
	ON_BN_CLICKED(IDC_FRCOLOR, OnFrcolor)
	ON_EN_CHANGE(IDC_WIDTH, EnableApplyButton)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_EN_CHANGE(IDC_HEIGHT, EnableApplyButton)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyDialog message handlers

BOOL CPropertyDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CButton* pcb = (CButton*)GetDlgItem(IDC_APPLY);
	pcb->EnableWindow(FALSE);	// Disable the apply botton

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertyDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	delete this;	// Delete dialog

	CDialog::PostNcDestroy();
}

void CPropertyDialog::OnApply() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	m_pWnd->SendMessage(m_UserMsg, TD_APPLY);	// Send user defined message

	CButton* pcb = (CButton*)GetDlgItem(IDC_APPLY);
	pcb->EnableWindow(FALSE);
}

void CPropertyDialog::OnCancel() 
{
	// TODO: Add your control notification handler code here
	
	m_pWnd->SendMessage(m_UserMsg, TD_CANCEL);
	DestroyWindow();
}


void CPropertyDialog::OnBkcolor() 
{
	// TODO: Add your control notification handler code here
	
	m_pWnd->SendMessage(m_UserMsg, TD_BKCOLOR);
}

void CPropertyDialog::OnFrcolor() 
{
	// TODO: Add your control notification handler code here
	
	m_pWnd->SendMessage(m_UserMsg, TD_FRCOLOR);
}

void CPropertyDialog::EnableApplyButton() 
{
	CButton* pcb = (CButton*)GetDlgItem(IDC_APPLY);

	if (pcb)
	{
		pcb->EnableWindow(TRUE);
		//pcb->SetFocus();
	}
}

void CPropertyDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	m_ctrBkColor.Invalidate();
	CPaintDC dcBk(&m_ctrBkColor);
	CRect rectBk;
	m_ctrBkColor.GetClientRect(&rectBk);
	CBrush brushBk(m_BkColor);
	dcBk.FillRect(&rectBk, &brushBk);

	m_ctrFrColor.Invalidate();
	CPaintDC dcFr(&m_ctrFrColor);
	CRect rectFr;
	m_ctrFrColor.GetClientRect(&rectFr);
	CBrush brushFr(m_FrColor);
	dcFr.FillRect(&rectFr, &brushFr);
}
