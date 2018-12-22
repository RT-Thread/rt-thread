/*
*******************************************************************************
**
** \file      gd_pwm.c
**
** \brief     Generic pwm   device driver (core functions).
**
**              (C) Goke Microelectronics China 2007 - 2010
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. HUNAN GOFORTUNE SEMICONDUCTOR
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
** \version   $Id: gd_spi.c,v 1.2 2013/11/21 09:28:00
**
*******************************************************************************
*/
#include <stdio.h>
#include <string.h>

#include <gtypes.h>
#include "gh_pwm.h"
#include "gd_pwm.h"
#include "gd_gpio.h"
#include "gh_debug_rct.h"
#include "gd_timer.h"
//#define DEBUG_PRINT
#define AMPLIFICATION (1000)

#ifdef DEBUG_PRINT
#include <gm_lib/gm_debug.h>
#endif
/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/
static GD_HANDLE Gpiohandle[GD_PWM_COUNT];

/*!
*******************************************************************************
**
** \brief  Reset PWM registers.
**
**         This function initializes the PWM driver by reset the PWM registers to default value (0x0)
**
**
** \return
**         - #GD_OK if successful
******************************************************************************/
GERR GD_PWM_Init()
{
    U8 channel;

    GH_PLL_set_SCALER_PWM(0x20);
    for (channel = 0; channel < GD_PWM_COUNT; channel++)
    {
        GH_PWM_set_Enable_enb(channel, 0);
        GH_PWM_set_Control(channel, 0);
        GH_PWM_set_Control1(channel, 0);
        GH_PWM_set_Mode_mode(channel, 0);
        GH_PWM_set_Mode_divider(channel, 0);
        GD_PWM_Set_Clock_Divider(channel, 1);
    }
    
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Set PWM logic high level, logic low level count.
**
**         This function can set PWM output frequency by specifying high level count and low level count,
** the PWM output frequency is caculated by output frequency=input frequency/(highLevelCnt+lowLevelCnt).
** Also, the PWM duty is highLevelCnt/(highLevelCnt+lowLevelCnt). The highLevelCnt/lowLevelCnt value should
** be 1~65536.
**
**\param channel The PWM channel that specified.
**\param highLevelCnt The PWM high level count.
**\param lowLevelCnt The PWM low level count.
**
** \return
**         - #GD_OK if successful
******************************************************************************/
GERR GD_PWM_Cycle(U8 channel, U32 highLevelCnt, U32 lowLevelCnt)
{
    GH_PWM_CONTROL_S pwm_control;
    GD_PWM_MODE_E mode;
    U32 pwmDiv = 0;
    U16 highLevelReg = 0;
    U16 lowLevelReg = 0;

    if (highLevelCnt < 1 || highLevelCnt > 65536 || lowLevelCnt < 1 || lowLevelCnt > 65536)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM highLevelCnt/lowLevelCnt is invalid!\n");
#endif   
        return GD_ERR_BAD_PARAMETER;
    }
    highLevelReg = (U16)(highLevelCnt - 1);
    lowLevelReg = (U16)(lowLevelCnt - 1);
    
    mode = (U8)GH_PWM_get_Mode_mode(channel);
    if(mode==GD_NORMAL_SPEED)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM work in normal mode\n");
#endif
        GH_PWM_set_Mode(channel,0);
        GH_PWM_set_Mode_divider(channel,pwmDiv);
        pwm_control.bitc.xon = highLevelReg;
        pwm_control.bitc.xoff = lowLevelReg;
        GH_PWM_set_Control(channel,pwm_control.all);
    }
    else if(mode==GD_SYNC_SPEED)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM work in sync mode\n");
#endif
        GH_PWM_set_Mode(channel,1);
        GH_PWM_set_Mode_divider(channel,pwmDiv);
        pwm_control.bitc.xon = highLevelReg;
        pwm_control.bitc.xoff = lowLevelReg;
        GH_PWM_set_Control(channel,pwm_control.all);
    }
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Set PWM mode
**
**         This function set pwm to normal speed mode or sync speed mode
**
**\param channel The PWM channel that specified.
**\param mode The PWM mode: 0 - Normal Speed Mode; 1 - Sync Speed Mode.
**
** \return
**         - #GD_OK if successful
******************************************************************************/
GERR GD_PWM_Set_Mode(U8 channel, U8 mode)
{
    if (channel >= GD_PWM_COUNT)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM channel has exceed the max channel number that can be set!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }
    if ((mode != 0) && (mode != 1))
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM mode invalid, it should be 0 or 1!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }
    if (GD_NORMAL_SPEED == mode)
    {
        GH_PWM_set_Mode_mode(channel, 0);
    }
    else
    {
        GH_PWM_set_Mode_mode(channel, 1);
    }
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Get PWM mode
**
**         This function get pwm mode. The mode is normal speed mode or sync speed mode.
**
**\param channel The PWM channel that specified.
**\param mode The pointer to get PWM mode: 0 - Normal Speed Mode; 1 - Sync Speed Mode.
**
** \return
**         - #GD_OK if successful
******************************************************************************/
GERR GD_PWM_Get_Mode(U8 channel, GD_PWM_MODE_E *mode)
{
    if (channel >= GD_PWM_COUNT)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM channel has exceed the max channel number that can be set!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }
    
    *mode = GH_PWM_get_Mode_mode(channel);
    
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Set PWM speed
**
**         This function set pwm divider in sync speed mode. 
**
**\param channel The PWM channel that specified.
**\param speed The PWM divider in sync speed mode.
**
** \return
**         - #GD_OK if successful
******************************************************************************/
GERR GD_PWM_Set_Speed(U8 channel, U16 speed)
{
    if (channel >= GD_PWM_COUNT)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM channel has exceed the max channel number that can be set!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    GH_PWM_set_Mode_divider(channel, speed);
    
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Get PWM speed
**
**         This function get pwm divider in sync speed mode. 
**
**\param channel The PWM channel that specified.
**\param speed The pointer to get PWM divider in sync speed mode.
**
** \return
**         - #GD_OK if successful
******************************************************************************/
GERR GD_PWM_Get_Speed(U8 channel, U16 *speed)
{
    if (channel >= GD_PWM_COUNT)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM channel has exceed the max channel number that can be set!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    *speed = GH_PWM_get_Mode_divider(channel);
    
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Enable or disable PWM output.
**
**         This function enbale or disable PWM output.
**
** \param channel The PWM channel that specified.
** \param enable Turn on PWM output if enable is 1, or turn off PWM output if enable is 0.
**
** \return
**         - #GD_OK if successful
******************************************************************************/
GERR  GD_PwmOnOff(U8 channel,U32 enable)
{
    if (enable == 0)
    {
        GH_PWM_set_Enable_enb(channel,0);
#ifdef DEBUG_PRINT
        GM_Printf("Set PWM%d OFF\n",channel);
#endif
    }
    else
    {
        GH_PWM_set_Enable_enb(channel,1);
#ifdef DEBUG_PRINT
        GM_Printf("Set PWM%d ON\n",channel);
#endif
    }
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Configure GPIO for PWM
**
**         This function configure GPIO for PWM.
**
** \param channel The PWM channel that specified.
** \param ioNumber The GPIO number configured for this PWM channel.
**
** \return
**         - #GD_OK if successful
******************************************************************************/
GERR  GD_PWM_Open(U8 channel,U32 ioNumber)
{
#ifdef DEBUG_PRINT
    printf("Set PWM%d ON \n",channel);
#endif
    if (channel >= GD_PWM_COUNT)
    {
#ifdef DEBUG_PRINT
        printf("PWM channel has exceed the max channel number that can be set!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    switch(channel)
    {
        case 0:
            GD_GPIO_Open(ioNumber,GD_GPIO_TYPE_OUTPUT_PWM0_OUT,NULL,&Gpiohandle[channel]);
            break;
        case 1:
            GD_GPIO_Open(ioNumber,GD_GPIO_TYPE_OUTPUT_PWM1_OUT,NULL,&Gpiohandle[channel]);
            break;
        case 2:
            GD_GPIO_Open(ioNumber,GD_GPIO_TYPE_OUTPUT_PWM2_OUT,NULL,&Gpiohandle[channel]);
            break;
        case 3:
            GD_GPIO_Open(ioNumber,GD_GPIO_TYPE_OUTPUT_PWM3_OUT,NULL,&Gpiohandle[channel]);
            break;
        case 4:
            GD_GPIO_Open(ioNumber,GD_GPIO_TYPE_OUTPUT_PWM4_OUT,NULL,&Gpiohandle[channel]);
            break;
        case 5:
            GD_GPIO_Open(ioNumber,GD_GPIO_TYPE_OUTPUT_PWM5_OUT,NULL,&Gpiohandle[channel]);
            break;
        case 6:
            GD_GPIO_Open(ioNumber,GD_GPIO_TYPE_OUTPUT_PWM6_OUT,NULL,&Gpiohandle[channel]);
            break;
        case 7:
            GD_GPIO_Open(ioNumber,GD_GPIO_TYPE_OUTPUT_PWM7_OUT,NULL,&Gpiohandle[channel]);
            break;
        default:
            break;
    }
    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Disable PWM output
**
**         This function disable the PWM output.
**
** \param channel The PWM channel that specified.
**
** \return
**         - #GD_OK if successful
******************************************************************************/
GERR GD_PWM_Close( U8 channel )
{
    GH_PWM_set_Enable_enb(channel,0);
    GD_GPIO_Close(&Gpiohandle[channel]);
    return( GD_OK );
}

/* set pwm duty rate */
GERR GD_PWM_Set_Duty(GD_PWM_DUTY_S *pwm_duty)
{
    U32 mode;
    GH_PWM_CONTROL_S pwm_control0;
    GH_PWM_CONTROL1_S pwm_control1;

    mode = GH_PWM_get_Mode_mode(pwm_duty->channel);
    if(mode == GD_NORMAL_SPEED)
    {
        pwm_control0.bitc.xon = pwm_duty->xon;
        pwm_control0.bitc.xoff  = pwm_duty->xoff;
        GH_PWM_set_Control(pwm_duty->channel,pwm_control0.all);
    }
    else if(mode == GD_SYNC_SPEED)
    {
        pwm_control1.bitc.xon = pwm_duty->xon;
        pwm_control1.bitc.xoff  = pwm_duty->xoff;
        GH_PWM_set_Control1(pwm_duty->channel,pwm_control1.all);
    }
    return GD_OK;
}

/* get pwm duty rate */
GERR GD_PWM_Get_Duty(GD_PWM_DUTY_S *pwm_duty)
{
    U32 mode = 0;
    GH_PWM_CONTROL_S pwm_control0;
    GH_PWM_CONTROL1_S pwm_control1;

    mode = GH_PWM_get_Mode_mode(pwm_duty->channel);
    if(mode == GD_NORMAL_SPEED)
    {
        pwm_control0.all = GH_PWM_get_Control(pwm_duty->channel);
        pwm_duty->xon  = pwm_control0.bitc.xon;
        pwm_duty->xoff = pwm_control0.bitc.xoff;
    }
    else if(mode == GD_SYNC_SPEED)
    {
        pwm_control1.all = GH_PWM_get_Control1(pwm_duty->channel);
        pwm_duty->xon  = pwm_control1.bitc.xon;
        pwm_duty->xoff = pwm_control1.bitc.xoff;
    }

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Set PWM Parameters
**
**         This function set PWM parameters that includes channel, range, frequency, and duty cycle.
**
** \param channel The PWM channel that specified.
** \param frequency The PWM output frequency that specified, the unit is Hz.
** \param range The PWM output adjustable range. For example, if range is 100, the PWM duty cycle
** can be set from 1% to 99%.
** \param duty The PWM duty cycle that specified.
** \return
**         - #GD_PWM_NO_ERR if successful
******************************************************************************/
GD_PWM_ERROR_CODE_E GD_PWM_Set_Param(U8 channel, U32 frequency, U32 range, U32 duty)
{
    U32 mode;
    U32 total;
    U32 pwmDiv;
    U32 clkPwm;
    U32 maxClkPwm;
    U32 minClkPwm;
    U32 apbClk;
    U64 multiple;
    U32 highLevelCnt;
    U32 lowLevelCnt;

    if (channel >= GD_PWM_COUNT)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM channel has exceed the max channel number that can be set!\n");
#endif
        return GD_PWM_ERR_NOT_SUPPORTED_CHANNEL;
    }
    if (frequency == 0)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM frequency can not be 0!\n");
#endif
        return GD_PWM_ERR_NOT_SUPPORTED_FREQUENCY;
    }
    if (range <= 1)
    {
#ifdef DEBUG_PRINT
        GM_Printf("The range is too small!\n");
#endif
        return GD_PWM_ERR_NOT_SUPPORTED_RANGE;
    }
    if ((duty == 0) || (duty >= range))
    {
#ifdef DEBUG_PRINT
        GM_Printf("The PWM duty can not be 0, or exceed the max range value!\n");
#endif
        if (duty == 0)
        {
            GD_GPIO_Write(Gpiohandle[channel], 0);
        }
        if (duty == range)
        {
            GD_GPIO_Write(Gpiohandle[channel], 1);
        }
        return GD_PWM_ERR_WRONG_DUTY_CONFIGURATION;
    }
    
    pwmDiv = GH_PLL_get_SCALER_PWM();
    apbClk = GD_GET_APB_ClkHz();
    clkPwm = apbClk / pwmDiv;
    maxClkPwm = clkPwm / 2;
    minClkPwm = clkPwm / (65536 * 2);
    if (frequency > maxClkPwm)
    {
        GH_PLL_set_SCALER_PWM(0x1);
        clkPwm = apbClk;
        maxClkPwm = clkPwm / 2;
        if (frequency > maxClkPwm)
        {
#ifdef DEBUG_PRINT
            GM_Printf("PWM frequency exceed the maximum pwm frequency that can be set!\n");
#endif
            return GD_PWM_ERR_NOT_SUPPORTED_FREQUENCY;
        }
    }
    if (frequency < minClkPwm)
    {
        GH_PLL_set_SCALER_PWM(1000);
        clkPwm = apbClk / 1000;
        minClkPwm = clkPwm / (65536 * 2);
        if (minClkPwm == 0)
        {
            minClkPwm = 1;
        }
        if (frequency < minClkPwm)
        {
#ifdef DEBUG_PRINT
            GM_Printf("PWM frequency exceed the minimum pwm frequency that can be set!\n");
#endif
            return GD_PWM_ERR_NOT_SUPPORTED_FREQUENCY;
        }
    }

    total = clkPwm / frequency;
    multiple = total * AMPLIFICATION / range;
    if ((multiple / AMPLIFICATION) < 1)
    {
#ifdef DEBUG_PRINT
        GM_Printf("Err: PWM range is too large, less than range %d is suggested!\n", total);
#endif
        //return GD_PWM_ERR_RANGE_EXCEED_LIMIT;
        range = total;
        duty = total / 2;
        highLevelCnt = duty;
    }
    else
    {
        highLevelCnt = duty * multiple / AMPLIFICATION;
    }
    lowLevelCnt = total - highLevelCnt;
    
    if (highLevelCnt > 0xFFFF)
    {
        duty = total / 2;
        highLevelCnt = duty;
        lowLevelCnt = total - highLevelCnt;
    }
    
    mode = GH_PWM_get_Mode_mode(channel);
    if(mode == GD_NORMAL_SPEED)
    {
        GH_PWM_set_Control_xon(channel, (U16)(highLevelCnt - 1));
        GH_PWM_set_Control_xoff(channel, (U16)(lowLevelCnt - 1));
    }
    else
    {
        GH_PWM_set_Control1_xon(channel, (U16)(highLevelCnt - 1));
        GH_PWM_set_Control1_xoff(channel, (U16)(lowLevelCnt - 1));
    }
    return GD_PWM_NO_ERR;
}

/*!
*******************************************************************************
**
** \brief  Get PWM Parameters
**
**         This function get PWM parameters that includes frequency, and duty cycle.
**
** \param channel The PWM channel that specified.
** \param frequency The current PWM output frequency, the unit is Hz.
** \param duty The current PWM duty cycle, the unit is %.
** \return
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if input parameter is invalid
******************************************************************************/
GERR GD_PWM_Get_Param(U8 channel, U32 *frequency, U32 *duty)
{
    GD_PWM_MODE_E mode;
    U32 currentDuty = 0;
    U32 currentFrequency = 0;
    U32 total;
    U32 pwmDiv;
    U32 clkPwm;
    U32 apbClk;
    U16 highLevelCnt;
    U16 lowLevelCnt;

    if (channel >= GD_PWM_COUNT)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM channel has exceed the max channel number that can be set!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }
    if ((frequency == NULL) || (duty == NULL))
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM frequency and duty are pointers to get PWM params, they can not be NULL!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    pwmDiv = GH_PLL_get_SCALER_PWM();
    apbClk = GD_GET_APB_ClkHz();
    clkPwm = apbClk / pwmDiv;
    
    mode = GH_PWM_get_Mode_mode(channel);
    if(mode == GD_NORMAL_SPEED)
    {
        highLevelCnt = GH_PWM_get_Control_xon(channel) + 1;
        lowLevelCnt = GH_PWM_get_Control_xoff(channel) + 1;
    }
    else
    {
        highLevelCnt = GH_PWM_get_Control1_xon(channel) + 1;
        lowLevelCnt = GH_PWM_get_Control1_xoff(channel) + 1;
    }

    total = highLevelCnt + lowLevelCnt;
    currentFrequency = clkPwm / total;
    currentDuty = highLevelCnt * 100 / total;
    *frequency = currentFrequency;
    *duty = currentDuty;

    return GD_OK;
}

/*!
*******************************************************************************
**
** \brief  Get PWM status
**
**         This function get PWM status that indicates PWM is currently enable or disable.
**
** \param channel The PWM channel that specified.
** \param status The pointer which to get the currenty PWM status.
** \return
**         - #GD_OK if successful
**         - #GD_ERR_BAD_PARAMETER if input parameter is invalid
******************************************************************************/
GERR GD_PWM_Get_Status(U8 channel, U32 *status)
{
    if (NULL == status)
    {
        return GD_ERR_BAD_PARAMETER;
    }
    
    *status = GH_PWM_get_Enable_enb(channel);
    return GD_OK;
}

/*---------------------------------------------------------------------------*/
/* Set PWM clock divider:                                                                                               */
/* 1-    Support down to 16Hz PWM output (PWM clock frequency: 2.156MHz)                       */
/* 2-    Support down to 1Hz PWM output ((PWM clock frequency: 10KHz)                     */
/* 3-    Support up to 34.5MHz PWM output ((PWM clock frequency: 34.5MHz)                     */
/*---------------------------------------------------------------------------*/
GERR GD_PWM_Set_Clock_Divider(U8 channel, U8 divider)
{
    if (channel >= GD_PWM_COUNT)
    {
#ifdef DEBUG_PRINT
        GM_Printf("PWM channel has exceed the max channel number that can be set!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }
    if ((divider < 1) || (divider > 3))
    {
#ifdef DEBUG_PRINT
        GM_Printf("Invalid divider argument! Divider should between 1 to 3.\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    if (GH_PWM_get_Enable_enb(channel))
    {
        GH_PWM_set_Enable_enb(channel, 0);
    }
    
    if (divider == 1)
    {
        GH_PLL_set_SCALER_PWM(0x20);
#ifdef DEBUG_PRINT
        GM_Printf("Set PWM clock to 2.156MHz\n");
#endif
    }
    else if (divider == 2)
    {
        GH_PLL_set_SCALER_PWM(0x1AF4);
#ifdef DEBUG_PRINT
        GM_Printf("Set PWM clock to 10KHz\n");
#endif
    }
    else
    {
        GH_PLL_set_SCALER_PWM(0x1);
#ifdef DEBUG_PRINT
        GM_Printf("Set PWM clock to 34.5MHz\n");
#endif
    }

    return GD_OK;
}

