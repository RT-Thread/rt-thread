/*
*******************************************************************************
**
** \file      gd_int_priv.h
**
** \brief     INT driver (private header file).
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
#ifndef GD_INT_PRIV_H
#define GD_INT_PRIV_H

#include <gtypes.h>
#include <gmodids.h>

/*---------------------------------------------------------------------------*/
/* private defines (used by more than one driver module)                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* private datatypes (used by more than one driver module)                   */
/*---------------------------------------------------------------------------*/
typedef struct
{
    U32    instructionWord; // just place holder for JAL code
    void (*fct)();          // the real interrupt serving function
}
VECTOR_ENTRY_TYPE_S;


/*---------------------------------------------------------------------------*/
/* private data (used by more than one driver module)                        */
/*---------------------------------------------------------------------------*/

#if defined( GD_INT_PRIV_C )
    GD_INT_HANDLER_F DriverFuncTable[GD_VIC_INSTANCES * GD_INT_VEC_OFFSET] = {NULL};
#else
    extern GD_INT_HANDLER_F DriverFuncTable[GD_VIC_INSTANCES * GD_INT_VEC_OFFSET];
#endif

/*---------------------------------------------------------------------------*/
/* function prototypes                                                       */
/*---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

void _exit_halt( void );

#ifdef __cplusplus
}
#endif

#endif /* _GD_INT_PRIV_H_ */
/* end of gd_int_priv.h */
