/*
*******************************************************************************
**
** \file      gd_int_handler.c
**
** \brief     INT driver (core functions).
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
//#define GD_INT_HANDLER_C 1
#include <stdio.h>
#include <string.h>

#include <gtypes.h>
#include "gd_int.h"
#include "gd_int_priv.h"

/*!
********************************************************************************
**
** \brief Sets an interrupt handler
**
** This function sets the given interrupt handler for the given interrupt
** vector.
**
** \param vector  The interrupt vector to access
** \param handler The interrupt handler to store for the given interrupt vector.
**
********************************************************************************
*/
void GD_INT_SetHandler(S8 vector, GD_INT_HANDLER_F handler)
{
    if ( vector >= 0 && vector <= GD_INT_LAST_IRQ )
    {
        DriverFuncTable[vector] = handler;
    }
}

/*!
********************************************************************************
**
** \brief Retrieve an interrupt handler
**
** This function retrieves the interrupt handler for the given interrupt
** vector.
**
** \param vector  The interrupt vector to access
**
** \return
** - The interrupt handler stored for the given interrupt vector
**
********************************************************************************
*/
GD_INT_HANDLER_F GD_INT_GetHandler(S8 vector)
{

    if ( vector >= 0 && vector <= GD_INT_LAST_IRQ )
    {
        return(DriverFuncTable[vector]);
    }
    return( 0 );
}


