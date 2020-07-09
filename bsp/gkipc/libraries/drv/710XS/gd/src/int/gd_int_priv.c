/*
*******************************************************************************
**
** \file      gd_int_priv.c
**
** \brief     INT driver (private functions).
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
*******************************************************************************
*/
#define GD_INT_PRIV_C 1

#include <gtypes.h>
#include "gd_int.h"
#include "gd_int_priv.h"

// this C file simply acts as container for the shared local variables
// defined in gd_int_priv.h

U32 IntBaseVectTable()
{
    return 0;
}
U32 IntBaseFuncTable()
{
    return 0;
}
void _exit_halt( void )
{
}


