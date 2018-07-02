/*****************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
 *
 * This software is owned and published by:
 * Huada Semiconductor Co.,Ltd ("HDSC").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with HDSC
 * components. This software is licensed by HDSC to be adapted only
 * for use in systems utilizing HDSC components. HDSC shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein. HDSC is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * Disclaimer:
 * HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 */
/******************************************************************************/
/** \file gpio.h
 **
 ** A detailed description is available at
 ** @link GpioGroup Gpio description @endlink
 **
 **   - 2018-03-07  1.0  Zhangxl First version for Device Driver Library of Gpio.
 **
 ******************************************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f480.h"
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup GpioGroup General Purpose Input/Output(GPIO)
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
  /**
 *******************************************************************************
 ** \brief GPIO Configuration Mode enumeration
 **
 ******************************************************************************/
typedef enum
{
    Pin_Mode_In  = 0,   /*!< GPIO Input mode     */
    Pin_Mode_Out = 1,   /*!< GPIO Output mode    */
    Pin_Mode_Ana = 2,   /*!< GPIO Analog mode    */
}en_pin_mode_t;

/**
 *******************************************************************************
 ** \brief GPIO Drive Capacity enumeration
 **
 ******************************************************************************/
typedef enum
{
    Pin_Drv_L = 0,  /*!< Low Drive Capacity     */
    Pin_Drv_M = 1,  /*!< Middle Drive Capacity  */
    Pin_Drv_H = 2,  /*!< High Drive Capacity    */
}en_pin_drv_t;

/**
 *******************************************************************************
 ** \brief GPIO Output Type enumeration
 **
 ******************************************************************************/
typedef enum
{
    Pin_OType_Cmos = 0, /*!< CMOS        */
    Pin_OType_Od   = 1, /*!< Open Drain  */
}en_pin_o_type_t;

/**
 *******************************************************************************
 ** \brief GPIO Port Index enumeration
 **
 ******************************************************************************/
typedef enum en_port
{
    Port0 = 0,
    Port1 = 1,
    Port2 = 2,
    Port3 = 3,
    Port4 = 4,
    Port5 = 5,
    Port6 = 6,
    Port7 = 7,
}en_port_t;

/**
 *******************************************************************************
 ** \brief GPIO Pin Index enumeration
 **
 ******************************************************************************/
typedef enum en_pin
{
    Pin00 = (1 <<  0),
    Pin01 = (1 <<  1),
    Pin02 = (1 <<  2),
    Pin03 = (1 <<  3),
    Pin04 = (1 <<  4),
    Pin05 = (1 <<  5),
    Pin06 = (1 <<  6),
    Pin07 = (1 <<  7),
    Pin08 = (1 <<  8),
    Pin09 = (1 <<  9),
    Pin10 = (1 << 10),
    Pin11 = (1 << 11),
    Pin12 = (1 << 12),
    Pin13 = (1 << 13),
    Pin14 = (1 << 14),
    Pin15 = (1 << 15),
    PinAll= 0xFFFF,
}en_pin_t;

/**
 *******************************************************************************
 ** \brief GPIO Function enumeration
 **
 ******************************************************************************/
typedef enum en_port_func
{
    Func_Gpio   = 0,
    Func_Misc   = 1,
    Func_Evt    = 2,
    Func_Tm24   = 3,
    Func_Tm6    = 4,
    Func_SciEven= 5,
    Func_SciOdd = 6,
    Func_Msc    = 7,
    Func_Spi    = 8,
    Func_Qspi   = 9,
    Func_I2cCan = 10,
    Func_Eth    = 11,
    Func_Usb    = 12,
    Func_Jtag   = 13,
    Func_Exmc   = 15,
}en_port_func_t;

/**
 *******************************************************************************
 ** \brief GPIO init structure definition
 **
 ******************************************************************************/
typedef struct
{
    en_pin_mode_t   enPinMode;
    boolean_t       bPinExIntEn;
    boolean_t       bPinIvtEn;
    boolean_t       bPuEn;
    en_pin_drv_t    enPinDrv;
    en_pin_o_type_t enPinOType;
    boolean_t       bPinSubFuncEn;
}stc_port_init_t;

/**
 *******************************************************************************
 ** \brief GPIO public setting structure definition
 **
 ******************************************************************************/
typedef struct
{
    en_port_func_t  enSubFuncSel;
    boolean_t       bNoRDWait;
    boolean_t       bInMOSOn;
}stc_port_pub_set_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern void Port_Init(en_port_t enPort, uint16_t u16Pin, stc_port_init_t stcPortInit);
extern void Port_DeInit(en_port_t enPort, uint16_t u16Pin);
extern void Port_Unlock(void);
extern void Port_Lock(void);
extern void Port_PubSetting(stc_port_pub_set_t stcPortPubSet);
extern uint16_t Port_GetData(en_port_t enPort);
extern boolean_t Port_GetBits(en_port_t enPort, en_pin_t enPin);
extern void Port_SetPortData(en_port_t enPort, uint16_t u16Data);
extern void Port_OE(en_port_t enPort, uint16_t enPin);
extern void Port_SetBits(en_port_t enPort, uint16_t enPin);
extern void Port_ResetBits(en_port_t enPort, uint16_t enPin);
extern void Port_Toggle(en_port_t enPort, uint16_t enPin);
void Port_SetFunc(en_port_t enPort, uint16_t u16Pin, en_port_func_t enFuncSel, en_functional_state_t enNewState);
void Port_SetSubFunc(en_port_func_t enFuncSel);

//@} // GpioGroup

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H_ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
