@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by TODRAW.HPJ. >"hlp\ToDraw.hm"
echo. >>"hlp\ToDraw.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ToDraw.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ToDraw.hm"
echo. >>"hlp\ToDraw.hm"
echo // Prompts (IDP_*) >>"hlp\ToDraw.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ToDraw.hm"
echo. >>"hlp\ToDraw.hm"
echo // Resources (IDR_*) >>"hlp\ToDraw.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ToDraw.hm"
echo. >>"hlp\ToDraw.hm"
echo // Dialogs (IDD_*) >>"hlp\ToDraw.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ToDraw.hm"
echo. >>"hlp\ToDraw.hm"
echo // Frame Controls (IDW_*) >>"hlp\ToDraw.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ToDraw.hm"
REM -- Make help for Project TODRAW


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\ToDraw.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ToDraw.hlp" goto :Error
if not exist "hlp\ToDraw.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ToDraw.hlp" Debug
if exist Debug\nul copy "hlp\ToDraw.cnt" Debug
if exist Release\nul copy "hlp\ToDraw.hlp" Release
if exist Release\nul copy "hlp\ToDraw.cnt" Release
echo.
goto :done

:Error
echo hlp\ToDraw.hpj(1) : error: Problem encountered creating help file

:done
echo.
