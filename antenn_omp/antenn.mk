code_size = 386

compiler_optionsO =  -j -mf -e25 -d2 -zq -od -bt=dos -4r -fpi -fp3 -otlranmi -zp8
compiler_options =  -j -mf -s -e25 -zq -od -bt=dos -4r -fpi -fp3 -otlranmi -zp8
link_optionsO = d all SYS dos4g op m op st=51000 op maxe=25 op q op symf
link_options = SYS dos4g op m op st=51000 op maxe=25 op q op symf

LIB=c:\scitech\lib\dos32\wc11\dos4gw\pmode.lib,&
    c:\scitech\lib\dos32\wc11\mvis.lib,&
    c:\scitech\lib\dos32\wc11\mglcpp.lib,&
    c:\scitech\lib\dos32\wc11\tech.lib,&
    c:\scitech\lib\dos32\wc11\mglfx.lib,&
    c:\scitech\lib\dos32\wc11\ztimer.lib


object_files = &
  DRAWSPAC.OBJ &
  MYCOLOR.OBJ &
  DRAWELL.OBJ &
  DRAWDGR.OBJ &
  FILDINIT.OBJ &
  INIT_GR.OBJ &
  GRRAZ.OBJ &
  SAVEBMP.OBJ &
  TRANT.OBJ &
  SI.OBJ &
  RESIST.OBJ &
  RECANT.OBJ &
  REBEAM.OBJ &
  LOOP.OBJ &
  GET_ANT.OBJ &
  FM.OBJ &
  ELLIPS.OBJ &
  DIPOLE.OBJ &
  CI.OBJ &
  BS.OBJ &
  BEAM.OBJ &
  ANTVISUL.OBJ

antenn.exe : $(object_files) .AUTODEPEND
 @%write $^*.lk1 FIL {$(object_files)}
 @%write $^*.lk1 LIBR $(LIB)
 @%append $^*.lk1
 #*wlink name $^* $(link_options) @$^*.lk1
 *wlink @pmodew.lnk system pmodew name $^*  @$^*.lk1

DRAWSPAC.OBJ : DRAWSPAC.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

MYCOLOR.OBJ : ..\..\DRAW\MYCOLOR.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

DRAWELL.OBJ : DRAWELL.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

DRAWDGR.OBJ : DRAWDGR.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

FILDINIT.OBJ : FILDINIT.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

INIT_GR.OBJ : ..\..\DRAW\INIT_GR.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

GRRAZ.OBJ : ..\..\DRAW\GRRAZ.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

SAVEBMP.OBJ : ..\..\DRAW\SAVEBMP.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

TRANT.OBJ : TRANT.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

SI.OBJ : SI.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

RESIST.OBJ : RESIST.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

RECANT.OBJ : RECANT.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

REBEAM.OBJ : REBEAM.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

LOOP.OBJ : LOOP.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

GET_ANT.OBJ : GET_ANT.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

FM.OBJ : FM.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

ELLIPS.OBJ : ELLIPS.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

DIPOLE.OBJ : DIPOLE.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

CI.OBJ : CI.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

BS.OBJ : BS.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

BEAM.OBJ : BEAM.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*

ANTVISUL.OBJ : ANTVISUL.CPP .AUTODEPEND
  *wpp$(code_size) $(compiler_options) $[*