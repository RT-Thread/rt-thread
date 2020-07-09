/*!
*******************************************************************************
**
** \file      gh_lib_cfg.h
**
** \brief     FH Library Configuration
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
******************************************************************************/
#ifndef _GH_LIB_CFG_H
#define _GH_LIB_CFG_H

#include "gtypes.h"

/*!
*******************************************************************************
**
** \brief Defines level of inlining.
**
**        This defines sets the level of inlining the register access
**        functions. The following levels are possible:
**        - 0 -> no inlining
**        - 1 -> only functions which do not use mirror variables are inlined
**        - 2 -> all functions are inlined
**
** \note  For Metaware compilers inlining takes affect only if -Hi or
**        an optimisation level greater than 3 is set (-O4) and the switch
**        -g is disabled. If DEBUG is enabled GH_INLINE_LEVEL will be set to 0
**        automatically in each FH header file.
**
******************************************************************************/
#ifndef GH_INLINE_LEVEL
#define GH_INLINE_LEVEL 0
#endif

/*!
*******************************************************************************
**
** \brief Defines the keyword to provoke inlining.
**
******************************************************************************/
#ifndef GH_INLINE
#define GH_INLINE GINLINE
#endif

#endif /* _GH_LIB_CFG_H */
