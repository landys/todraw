// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ToDraw.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_TOOLBOX, OnViewToolbox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLBOX, OnUpdateViewToolbox)
	ON_COMMAND(ID_VIEW_COLORBOX, OnViewColorbox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COLORBOX, OnUpdateViewColorbox)
	ON_COMMAND(ID_VIEW_TOOLSTYLEBOX, OnViewToolstylebox)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOOLSTYLEBOX, OnUpdateViewToolstylebox)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CURSOR_POSITION,	// Cursor position showed in status bar
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Status bar
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	int nIndex = 0;
	nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_CURSOR_POSITION);
	m_wndStatusBar.SetPaneInfo(nIndex, ID_INDICATOR_CURSOR_POSITION, SBPS_NORMAL, 90);

	EnableDocking(CBRS_ALIGN_ANY);

	// Tool bar
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT , WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);
	DockControlBar(&m_wndToolBar);

	// Tool box
	if (!m_wndToolBox.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBox.LoadToolBar(IDR_TOOLBOX))
	{
		TRACE0("Failed to create ToolBox\n");
		return -1;      // fail to create
	}
	m_wndToolBox.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
	DockControlBar(&m_wndToolBox);
	
	// Color box
	if (!m_wndColorBox.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndColorBox.LoadToolBar(IDR_COLORBOX))
	{
		TRACE0("Failed to create ColorBox\n");
		return -1;      // fail to create
	}
	m_wndColorBox.EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndColorBox);

	// Tool style box
	if (!m_wndToolStyleBox.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolStyleBox.LoadToolBar(IDR_TOOLSTYLEBOX))
	{
		TRACE0("Failed to create ToolStyleBox\n");
		return -1;      // fail to create
	}
	m_wndToolStyleBox.EnableDocking(CBRS_ALIGN_BOTTOM);
	DockControlBarLeftOf(&m_wndToolStyleBox, &m_wndColorBox);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf)
{	// Dock a bar right of another bar
	CRect rect;
	DWORD dw;
	UINT n;

	RecalcLayout();
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(2,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;
	DockControlBar(Bar,n,&rect);
}

void CMainFrame::OnViewToolbox() 
{
	// TODO: Add your command handler code here
	
	if (m_wndToolBox.IsWindowVisible())
	{
		ShowControlBar(&m_wndToolBox, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolBox, TRUE, FALSE);
	}
}

void CMainFrame::OnUpdateViewToolbox(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck(m_wndToolBox.IsWindowVisible());
}


void CMainFrame::OnViewColorbox() 
{
	// TODO: Add your command handler code here
	
	if (m_wndColorBox.IsWindowVisible())
	{
		ShowControlBar(&m_wndColorBox, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndColorBox, TRUE, FALSE);
	}
}

void CMainFrame::OnUpdateViewColorbox(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck(m_wndColorBox.IsWindowVisible());
}

void CMainFrame::OnViewToolstylebox() 
{
	// TODO: Add your command handler code here
	
	if (m_wndToolStyleBox.IsWindowVisible())
	{
		ShowControlBar(&m_wndToolStyleBox, FALSE, FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolStyleBox, TRUE, FALSE);
	}
}

void CMainFrame::OnUpdateViewToolstylebox(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
	pCmdUI->SetCheck(m_wndToolStyleBox.IsWindowVisible());
}

void CMainFrame::UpdateStatusBar(CPoint point)	// Update point on the status bar	
{
	CString strPoint;
	strPoint.Format(_T("%d,%d"), point.x, point.y);

	int nIndex = 0;
	nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_CURSOR_POSITION);
	
	m_wndStatusBar.SetPaneText(nIndex, strPoint);
}