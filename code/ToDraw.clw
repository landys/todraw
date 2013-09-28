; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPropertyDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ToDraw.h"
LastPage=0

ClassCount=7
Class1=CToDrawApp
Class2=CToDrawDoc
Class3=CToDrawView
Class4=CMainFrame

ResourceCount=16
Resource1=IDR_MAINFRAME
Resource2=IDR_TOOLBOX
Resource3=IDR_TODRAWTYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDR_TOOLSTYLEBOX (English (U.S.))
Resource5=IDR_COLORBOX (English (U.S.))
Resource6=IDR_COLORBOX
Resource7=IDR_TOOLBOX (English (U.S.))
Resource8=IDD_ABOUTBOX
Resource9=IDR_TOOLSTYLEBOX
Resource10=IDR_CONTEXT_MENU
Class7=CPropertyDialog
Resource11=IDD_PROPPAGE
Resource12=IDR_MAINFRAME (English (U.S.))
Resource13=IDD_ABOUTBOX (English (U.S.))
Resource14=IDR_TODRAWTYPE (English (U.S.))
Resource15=IDR_CONTEXT_MENU (English (U.S.))
Resource16=IDD_PROPPAGE (English (U.S.))

[CLS:CToDrawApp]
Type=0
HeaderFile=ToDraw.h
ImplementationFile=ToDraw.cpp
Filter=N
LastObject=CToDrawApp

[CLS:CToDrawDoc]
Type=0
HeaderFile=ToDrawDoc.h
ImplementationFile=ToDrawDoc.cpp
Filter=N
LastObject=CToDrawDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CToDrawView]
Type=0
HeaderFile=ToDrawView.h
ImplementationFile=ToDrawView.cpp
Filter=M
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CToDrawView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=CChildFrame
BaseClass=CMDIChildWnd
VirtualFilter=mfWC


[CLS:CAboutDlg]
Type=0
HeaderFile=ToDraw.cpp
ImplementationFile=ToDraw.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_VIEW_TOOLBOX
Command8=ID_VIEW_COLORBOX
Command9=ID_VIEW_TOOLSTYLEBOX
Command10=ID_HELP_FINDER
Command11=ID_APP_ABOUT
CommandCount=11

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_APP_ABOUT
Command5=ID_CONTEXT_HELP
CommandCount=5

[MNU:IDR_TODRAWTYPE]
Type=1
Class=CToDrawView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_VIEW_TOOLBOX
Command11=ID_VIEW_COLORBOX
Command12=ID_VIEW_TOOLSTYLEBOX
Command13=ID_IMAGE_PROPERTY
Command14=ID_WINDOW_NEW
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
Command18=ID_WINDOW_SPLIT
Command19=ID_IMAGE_CLEAR
Command20=ID_IMAGE_PROPERTY
Command21=ID_COLOR_CUSTOM
Command22=ID_HELP_FINDER
Command23=ID_APP_ABOUT
CommandCount=23

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[MNU:IDR_TODRAWTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_VIEW_TOOLBOX
Command11=ID_VIEW_COLORBOX
Command12=ID_VIEW_TOOLSTYLEBOX
Command13=ID_IMAGE_PROPERTY
Command14=ID_WINDOW_NEW
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
Command18=ID_WINDOW_SPLIT
Command19=ID_IMAGE_CLEAR
Command20=ID_IMAGE_PROPERTY
Command21=ID_COLOR_CUSTOM
Command22=ID_HELP_FINDER
Command23=ID_APP_ABOUT
CommandCount=23

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_APP_ABOUT
Command5=ID_CONTEXT_HELP
CommandCount=5

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_VIEW_TOOLBOX
Command8=ID_VIEW_COLORBOX
Command9=ID_VIEW_TOOLSTYLEBOX
Command10=ID_HELP_FINDER
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_TOOLBOX]
Type=1
Class=?
Command1=ID_SELECT
Command2=ID_LINE
Command3=ID_CURVE
Command4=ID_ELLIPSE
Command5=ID_RECTANGLE
Command6=ID_ROUNDRECT
Command7=ID_POLYGON
Command8=ID_PEN
Command9=ID_BRUSH
Command10=ID_ERASER
Command11=ID_FILLING
Command12=ID_SAMPLING
CommandCount=12

[TB:IDR_COLORBOX]
Type=1
Class=?
Command1=ID_BLACK
Command2=ID_WHITE
Command3=ID_DARKGRAY
Command4=ID_GRAY
Command5=ID_DRAKRED
Command6=ID_RED
Command7=ID_PURPLE
Command8=ID_PINK
Command9=ID_DARKYELLOW
Command10=ID_YELLOW
Command11=ID_DARKGREEN
Command12=ID_GREEN
Command13=ID_DARKCYAN
Command14=ID_CYAN
Command15=ID_DARKBLUE
Command16=ID_BLUE
CommandCount=16

[MNU:IDR_CONTEXT_MENU]
Type=1
Class=?
Command1=ID_IMAGE_PROPERTY
Command2=ID_IMAGE_CLEAR
Command3=ID_FILE_SAVE
CommandCount=3

[TB:IDR_TOOLSTYLEBOX]
Type=1
Class=?
Command1=ID_PS_SOLID
Command2=ID_PS_DASH
Command3=ID_PS_DOT
Command4=ID_PS_DASHDOT
Command5=ID_PS_DASHDOTDOT
Command6=ID_ONEPIXEL
Command7=ID_TWOPIXEL
Command8=ID_FOURPIXEL
Command9=ID_SIXPIXEL
Command10=ID_EMPTY
Command11=ID_FULL
CommandCount=11

[CLS:CPropertyDialog]
Type=0
HeaderFile=PropertyDialog.h
ImplementationFile=PropertyDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CPropertyDialog
VirtualFilter=dWC

[DLG:IDD_PROPPAGE]
Type=1
Class=CPropertyDialog
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_WIDTH,edit,1350574080
Control6=IDC_HEIGHT,edit,1350574080
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_APPLY,button,1342259200
Control10=IDC_CANCEL,button,1342259201
Control11=IDC_BKCOLOR,static,1342181643
Control12=IDC_FRCOLOR,static,1342181643

[TB:IDR_TOOLBOX (English (U.S.))]
Type=1
Class=?
Command1=ID_SELECT
Command2=ID_LINE
Command3=ID_CURVE
Command4=ID_ELLIPSE
Command5=ID_RECTANGLE
Command6=ID_ROUNDRECT
Command7=ID_POLYGON
Command8=ID_PEN
Command9=ID_BRUSH
Command10=ID_ERASER
Command11=ID_FILLING
Command12=ID_SAMPLING
CommandCount=12

[TB:IDR_COLORBOX (English (U.S.))]
Type=1
Class=?
Command1=ID_BLACK
Command2=ID_WHITE
Command3=ID_DARKGRAY
Command4=ID_GRAY
Command5=ID_DRAKRED
Command6=ID_RED
Command7=ID_PURPLE
Command8=ID_PINK
Command9=ID_DARKYELLOW
Command10=ID_YELLOW
Command11=ID_DARKGREEN
Command12=ID_GREEN
Command13=ID_DARKCYAN
Command14=ID_CYAN
Command15=ID_DARKBLUE
Command16=ID_BLUE
CommandCount=16

[TB:IDR_TOOLSTYLEBOX (English (U.S.))]
Type=1
Class=?
Command1=ID_PS_SOLID
Command2=ID_PS_DASH
Command3=ID_PS_DOT
Command4=ID_PS_DASHDOT
Command5=ID_PS_DASHDOTDOT
Command6=ID_ONEPIXEL
Command7=ID_TWOPIXEL
Command8=ID_FOURPIXEL
Command9=ID_SIXPIXEL
Command10=ID_EMPTY
Command11=ID_FULL
CommandCount=11

[MNU:IDR_CONTEXT_MENU (English (U.S.))]
Type=1
Class=?
Command1=ID_IMAGE_PROPERTY
Command2=ID_IMAGE_CLEAR
Command3=ID_FILE_SAVE
CommandCount=3

[DLG:IDD_PROPPAGE (English (U.S.))]
Type=1
Class=?
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_WIDTH,edit,1350574080
Control6=IDC_HEIGHT,edit,1350574080
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_APPLY,button,1342259201
Control10=IDC_CANCEL,button,1342259200
Control11=IDC_BKCOLOR,static,1342181643
Control12=IDC_FRCOLOR,static,1342181643

