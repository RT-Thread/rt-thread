/******************************************************************************
**
** \file      gd_wdog.h
**
** \brief     DEMO test application.
**
**            (C) Goke Microelectronics China 2002 - 2007
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Id: gd_wdog.h,v 1.8 2007/01/04 15:13:22 mneuma Exp $
**
******************************************************************************/

#ifndef _GD_WDOG_H_
#define _GD_WDOG_H_
#include <gtypes.h>
#include <gmodids.h>


//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
#define GD_WDOG_INTENABLE  0x05
#define GD_WDOG_RSTENABLE  0x03

#ifdef __cplusplus
extern "C" {
#endif
GERR GD_Wdog_Init(void);
GERR GD_Wdog_Enable(U32 index);
GERR GD_Wdog_Disable(void);
GERR GD_Wdog_ClrTimeout(void);
GERR GD_Wdog_GetTimeout(void);
GERR GD_Wdog_GetValue(void);
GERR GD_Wdog_LoadValue(U32 index);
GERR GD_Wdog_Enable_Reset(void);

#ifdef __cplusplus
}
#endif



#endif /* _GD_WDOG_H_ */

