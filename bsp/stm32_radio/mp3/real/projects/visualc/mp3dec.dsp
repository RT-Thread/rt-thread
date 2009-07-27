# Microsoft Developer Studio Project File - Name="mp3dec" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mp3dec - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mp3dec.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mp3dec.mak" CFG="mp3dec - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mp3dec - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mp3dec - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mp3dec - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release"
# PROP Intermediate_Dir "rel_obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\..\..\..\..\common\include" /I "..\.." /I "..\..\..\pub" /I "..\..\..\..\..\..\..\common\runtime\pub" /D "NDEBUG" /D "REL_ENABLE_ASSERTS" /D "_WINDOWS" /D "_LIB" /D "WIN32" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "mp3dec - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug"
# PROP Intermediate_Dir "debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\..\..\..\common\include" /I "..\.." /I "..\..\..\pub" /I "..\..\..\..\..\..\..\common\runtime\pub" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "_WINDOWS" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "mp3dec - Win32 Release"
# Name "mp3dec - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "general"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\mp3dec.c
# End Source File
# Begin Source File

SOURCE=..\..\..\mp3tabs.c
# End Source File
# End Group
# Begin Group "csource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\bitstream.c
# End Source File
# Begin Source File

SOURCE=..\..\buffers.c
# End Source File
# Begin Source File

SOURCE=..\..\dct32.c
# End Source File
# Begin Source File

SOURCE=..\..\dequant.c
# End Source File
# Begin Source File

SOURCE=..\..\dqchan.c
# End Source File
# Begin Source File

SOURCE=..\..\huffman.c
# End Source File
# Begin Source File

SOURCE=..\..\hufftabs.c
# End Source File
# Begin Source File

SOURCE=..\..\imdct.c
# End Source File
# Begin Source File

SOURCE=..\..\polyphase.c
# End Source File
# Begin Source File

SOURCE=..\..\scalfact.c
# End Source File
# Begin Source File

SOURCE=..\..\stproc.c
# End Source File
# Begin Source File

SOURCE=..\..\subband.c
# End Source File
# Begin Source File

SOURCE=..\..\trigtabs.c
# End Source File
# End Group
# End Group
# End Target
# End Project
