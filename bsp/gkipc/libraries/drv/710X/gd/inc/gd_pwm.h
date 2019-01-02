/*!
*******************************************************************************
**
** \file      gd_pwm.h
**
** \brief     pwm driver.
**
**            The driver provides functions to use the GK7101's PWM
**            interface.
**
**           Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version
**
******************************************************************************/
#ifndef _GD_PWM_H_
#define _GD_PWM_H_
#endif
#include <gtypes.h>
#include <gmodids.h>

/*---------------------------------------------------------------------------*/
/* types, enums and structures                                               */
/*---------------------------------------------------------------------------*/
/*!
*******************************************************************************
**
** \brief PWM channel number.
**
**
******************************************************************************/
#define GD_PWM_COUNT       4
/*!
*******************************************************************************
**
** \brief PWM operition modes.
**
** \sa    GD_PWM_INIT_PARAMS_S
**
******************************************************************************/
typedef enum
{
    GD_NORMAL_SPEED,
    GD_SYNC_SPEED,
}GD_PWM_MODE_E;

typedef struct
{
    U8   channel;    /* 0 ~ 3 */
    U16  xon;        /* 0x00 ~ 0xffff */
    U16  xoff;       /* 0x00 ~ 0xffff */
}GD_PWM_DUTY_S;

typedef enum
{
    GD_PWM_NO_ERR = 0,
    GD_PWM_ERR_NOT_SUPPORTED_CHANNEL,
    GD_PWM_ERR_NOT_SUPPORTED_FREQUENCY,
    GD_PWM_ERR_NOT_SUPPORTED_RANGE,
    GD_PWM_ERR_WRONG_DUTY_CONFIGURATION,
    GD_PWM_ERR_RANGE_EXCEED_LIMIT,
}GD_PWM_ERROR_CODE_E;

GERR GD_PWM_Init();
GERR GD_PWM_Cycle(U8 channel, U32 highLevelCnt, U32 lowLevelCnt);
GERR GD_PWM_Set_Mode(U8 channel, U8 mode);
GERR GD_PWM_Get_Mode(U8 channel, GD_PWM_MODE_E *mode);
GERR GD_PwmOnOff(U8 channel,U32 on);
GERR GD_PWM_Open(U8 channel,U32 iomode);
GERR GD_PWM_Close(U8 channel);
GD_PWM_ERROR_CODE_E GD_PWM_Set_Param(U8 channel, U32 frequency, U32 range, U32 duty);
GERR GD_PWM_Get_Param(U8 channel, U32 *frequency, U32 *duty);
GERR GD_PWM_Get_Status(U8 channel, U32 *status);
GERR GD_PWM_Set_Clock_Divider(U8 channel, U8 divider);




