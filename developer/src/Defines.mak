!IFNDEF KEYMAN_ROOT
!error KEYMAN_ROOT must be defined
!ENDIF

WINDOWS_ROOT=$(KEYMAN_ROOT)\windows
WINDOWS_PROGRAM=$(WINDOWS_ROOT)\bin

COMMON_ROOT=$(KEYMAN_ROOT)\common\windows\delphi

DEVELOPER_ROOT=$(KEYMAN_ROOT)\developer
DEVELOPER_PROGRAM=$(DEVELOPER_ROOT)\bin
DEVELOPER_OUTLIB=$(DEVELOPER_ROOT)\lib
DEVELOPER_DEBUGPATH=$(DEVELOPER_ROOT)\debug

KEYMAN_MODELCOMPILER_ROOT=$(DEVELOPER_ROOT)\src\kmlmc

# Temporary import of windows/src/Defines.mak
# TODO: include COMMON_ROOT's defines.mak instead
!include $(WINDOWS_ROOT)\src\Defines.mak