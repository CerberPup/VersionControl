
!include "MUI2.nsh"
!include "FileFunc.nsh"
!include "LogicLib.nsh"
!include "x64.nsh"

!define PRODUCT_NAME "Patch Tool"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "Wojciech Wrona"
;--------------------------------
;General

  ;Name and file
  Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
  OutFile "PT_Setup.exe"
  
  ;Default installation folder
  InstallDir "C:\Program Files\PatchTool"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\${PRODUCT_NAME}" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !define MUI_STARTMENUPAGE_DEFAULTFOLDER "${PRODUCT_NAME}"
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_NAME}"
  !insertmacro MUI_PAGE_INSTFILES
  !define MUI_FINISHPAGE_RUN "$INSTDIR\PatchTool.exe"
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
  !insertmacro MUI_LANGUAGE "Polish"

;--------------------------------
;Installer Sections
!define ARP "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"

Section "Program" SecDummy

  SetOutPath "$INSTDIR"
  File /r "D:\git\VersionControll\install\x64\*"

  SetOutPath "$INSTDIR"
  CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\PatchTool.exe"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  
  ${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
  IntFmt $0 "0x%08X" $0
  WriteRegDWORD HKLM "${ARP}" "EstimatedSize" "$0"
  ;Store installation folder
  WriteRegStr HKCU "Software\${PRODUCT_NAME}" "" $INSTDIR
  WriteRegStr HKLM "${ARP}" "DisplayName" "Patch Tool"
  WriteRegStr HKLM "${ARP}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr HKLM "${ARP}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr HKLM "${ARP}" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  SetOutPath "$INSTDIR"
SectionEnd

;Section "Python 2.7" SecPython
;
;  SetOutPath "$INSTDIR\PythonInstall"
;  ${If} ${RunningX64}
;  DetailPrint "64-bit Windows"
;  File "D:\git\Projekt-PP\python-2.7.15.amd64.msi"
;  ExecWait '"$SYSDIR\msiExec" /i "$INSTDIR\PythonInstall\python-2.7.15.amd64.msi"'
;  ${Else}
;  DetailPrint "32-bit Windows"
;  File "D:\git\Projekt-PP\python-2.7.15.msi"
;  ExecWait '"$SYSDIR\msiExec" /i "$INSTDIR\PythonInstall\python-2.7.15.msi"'
;  ${EndIf} 
;  SetOutPath "$INSTDIR"
;SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecDummy ${LANG_POLISH} "Główny program"
;  LangString DESC_SecPython ${LANG_POLISH} "Python 2.7. Zaznacz podczas instalacji dodanie zmiennych środowiskowych."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecDummy} $(DESC_SecDummy)
;  !insertmacro MUI_DESCRIPTION_TEXT ${SecPython} $(DESC_SecPython)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...

  RMDir /r "$INSTDIR\*"
  Delete "$INSTDIR\Uninstall.exe"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk"
  RMDir "$SMPROGRAMS\${PRODUCT_NAME}"
  RMDir /r "$INSTDIR"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
  DeleteRegKey /ifempty HKCU "Software\${PRODUCT_NAME}"

SectionEnd