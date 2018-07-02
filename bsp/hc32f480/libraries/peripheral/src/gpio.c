/******************************************************************************
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
/** \file gpio.c
 **
 ** A detailed description is available at
 ** @link GpioGroup Gpio description @endlink
 **
 **   - 2017-03-07  1.0  Zhangxl First version for Device Driver Library of Gpio.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "gpio.h"

/**
 *******************************************************************************
 ** \addtogroup GpioGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief   Port init
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be
 **                                   any value of @ref en_port_t
 ** \param   [in]  u16Pin             GPIO pin index, This parameter can be
 **                                   any value of @ref en_pin_t
 ** \param   [in]  stcPortInit        Structure of port configure
 **
 ** \retval  none
 **
 ******************************************************************************/
void Port_Init(en_port_t enPort, uint16_t u16Pin, stc_port_init_t stcPortInit)
{
    stc_port_pcr000_field_t *PCRx;
    stc_port_pfsr000_field_t * PFSRx;
    uint8_t u8PinPos = 0;

    Port_Unlock();

    for (u8PinPos = 0; u8PinPos < 16; u8PinPos ++)
    {
        if (u16Pin & (1<<u8PinPos))
        {
            PCRx = (stc_port_pcr000_field_t *)((uint32_t)(&M4_PORT->PCR000) \
                    + enPort * 0x40 + u8PinPos * 0x04);
            PFSRx = (stc_port_pfsr000_field_t *)((uint32_t)(&M4_PORT->PFSR000) \
                    + enPort * 0x40 + u8PinPos * 0x04);

            /* External interrupt input enable setting */
            PCRx->INTE = stcPortInit.bPinExIntEn;

            /* In_Out invert setting */
            PCRx->INVE = stcPortInit.bPinIvtEn;

            /* Pin pull-up setting */
            PCRx->PUU = stcPortInit.bPuEn;

            /* CMOS/OD output setting */
            PCRx->NOD = stcPortInit.enPinOType;

            /* Pin drive mode setting */
            PCRx->DRV = stcPortInit.enPinDrv;

            /* Pin mode setting */
            switch (stcPortInit.enPinMode)
            {
                case Pin_Mode_In:
                    PCRx->DDIS = 0;
                    PCRx->POUTE = 0;
                break;
                case Pin_Mode_Out:
                    PCRx->DDIS = 0;
                    PCRx->POUTE = 1;
                break;
                case Pin_Mode_Ana:
                    PCRx->DDIS = 1;
                break;
                default:
                break;
            }
            /* Sub function enable setting */
            PFSRx->BFE = stcPortInit.bPinSubFuncEn;

            /* Set to GPIO function */
            PFSRx->FSEL = Func_Gpio;
        }
    }

    Port_Lock();
}

void Port_DeInit(en_port_t enPort, uint16_t u16Pin)
{
  //todo
}


/**
 *******************************************************************************
 ** \brief   Port Public Setting
 **
 ** \param   [in]  stcPortPubSet      Structure of public setting (PCCR)
 **
 ** \retval  none
 **
 ******************************************************************************/
void Port_PubSetting(stc_port_pub_set_t stcPortPubSet)
{
    Port_Unlock();

    /* PCCR setting */
    /* Sub function setting */
    M4_PORT->PCCR_f.BFSEL = stcPortPubSet.enSubFuncSel;

    /* PIDRx, PCRxy read wait cycle setting */
    M4_PORT->PCCR_f.NORDWAIT = stcPortPubSet.bNoRDWait;

    /* Input MOS on */
    M4_PORT->PCCR_f.PINAE = stcPortPubSet.bInMOSOn;

    Port_Lock();
}


/**
 *******************************************************************************
 ** \brief   PCCR, PCRxy, PFSRxy write enable
 **
 ** \param   none
 **
 ** \retval  none
 **
 ******************************************************************************/
void Port_Unlock(void)
{
    M4_PORT->PWPR = 0xA501;
}

/**
 *******************************************************************************
 ** \brief   PCCR, PCRxy, PFSRxy write disable
 **
 ** \param   none
 **
 ** \retval  none
 **
 ******************************************************************************/
void Port_Lock(void)
{
    M4_PORT->PWPR = 0xA500;
}

/**
 *******************************************************************************
 ** \brief   Read Port value
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be
 **                                   any value of @ref en_port_t
 **
 ** \retval  The output port value
 **
 ******************************************************************************/
uint16_t Port_GetData(en_port_t enPort)
{
    uint32_t *PIDRx;
    PIDRx = (uint32_t *)((uint32_t)(&M4_PORT->PIDR0) + 0x10 * enPort);
    return *PIDRx;
}

/**
 *******************************************************************************
 ** \brief   Read Pin value
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be
 **                                   any value of @ref en_port_t
 ** \param   [in]  u16Pin             GPIO pin index, This parameter can be
 **                                   any value of @ref en_pin_t
 ** \retval  The output port pin value
 **
 ******************************************************************************/
boolean_t Port_GetBits(en_port_t enPort, en_pin_t enPin)
{
    uint32_t *PIDRx;
    PIDRx = (uint32_t *)((uint32_t)(&M4_PORT->PIDR0) + 0x10 * enPort);
    return !!(*PIDRx & (enPin));
}

/**
 *******************************************************************************
 ** \brief   Set Port value
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be
 **                                   any value of @ref en_port_t
 ** \param   [in]  u16Data            Output data
 **
 ** \retval  none
 **
 ******************************************************************************/
void Port_SetPortData(en_port_t enPort, uint16_t u16Data)
{
    uint32_t *PODRx;
    PODRx = (uint32_t *)((uint32_t)(&M4_PORT->PODR0) + 0x10 * enPort);
    *PODRx = u16Data;
}

/**
 *******************************************************************************
 ** \brief   Port Pin Output enable
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be
 **                                   any value of @ref en_port_t
 ** \param   [in]  u16Pin             GPIO pin index, This parameter can be
 **                                   any value of @ref en_pin_t
 ** \retval  none
 **
 ******************************************************************************/
void Port_OE(en_port_t enPort, uint16_t enPin)
{
    uint32_t *POERx;
    POERx = (uint32_t *)((uint32_t)(&M4_PORT->POER0) + 0x10 * enPort);
    *POERx = enPin;
}

/**
 *******************************************************************************
 ** \brief   Set Port Pin
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be
 **                                   any value of @ref en_port_t
 ** \param   [in]  u16Pin             GPIO pin index, This parameter can be
 **                                   any value of @ref en_pin_t
 ** \retval  None
 **
 ******************************************************************************/
void Port_SetBits(en_port_t enPort, uint16_t enPin)
{
    uint32_t *POSRx;
    POSRx = (uint32_t *)((uint32_t)(&M4_PORT->POSR0) + 0x10 * enPort);
    *POSRx = enPin;
}

/**
 *******************************************************************************
 ** \brief   Reset Port Pin
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be
 **                                   any value of @ref en_port_t
 ** \param   [in]  u16Pin             GPIO pin index, This parameter can be
 **                                   any value of @ref en_pin_t
 ** \retval  None
 **
 ******************************************************************************/
void Port_ResetBits(en_port_t enPort, uint16_t enPin)
{
    uint32_t *PORRx;
    PORRx = (uint32_t *)((uint32_t)(&M4_PORT->PORR0) + 0x10 * enPort);
    *PORRx = enPin;
}

/**
 *******************************************************************************
 ** \brief   Toggle Port Pin
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be
 **                                   any value of @ref en_port_t
 ** \param   [in]  u16Pin             GPIO pin index, This parameter can be
 **                                   any value of @ref en_pin_t
 ** \retval  None
 **
 ******************************************************************************/
void Port_Toggle(en_port_t enPort, uint16_t enPin)
{
    uint32_t *POTRx;
    POTRx = (uint32_t *)((uint32_t)(&M4_PORT->POTR0) + 0x10 * enPort);
    *POTRx = enPin;
}

/**
 *******************************************************************************
 ** \brief   Set Port Pin function
 **
 ** \param   [in]  enPort             GPIO port index, This parameter can be
 **                                   any value of @ref en_port_t
 ** \param   [in]  u16Pin             GPIO pin index, This parameter can be
 **                                   any value of @ref en_pin_t
 ** \param   [in]  enFuncSel          Function selection, This parameter can be
 **                                   any value of @ref en_port_func_t
 **
 ** \param   [in] enNewState          The new state of the gpio function.
 ** \arg     Enable                   Enable.
 ** \arg     Disable                  Disable.
 **
 ** \retval  None
 **
 ******************************************************************************/
void Port_SetFunc(en_port_t enPort, uint16_t u16Pin, en_port_func_t enFuncSel, en_functional_state_t enNewState)
{
    stc_port_pfsr000_field_t *PFSRx;
    uint8_t u8PinPos = 0;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    for (u8PinPos = 0; u8PinPos < 16; u8PinPos ++)
    {
        if (u16Pin & (1<<u8PinPos))
        {
            PFSRx = (stc_port_pfsr000_field_t *)((uint32_t)(&M4_PORT->PFSR000) \
                    + 0x40 * enPort + 0x4 * u8PinPos);
            PFSRx->FSEL = enFuncSel;

            PFSRx->BFE = (Enable == enNewState ? Set : Reset);
        }
    }
}

/**
 *******************************************************************************
 ** \brief   Set global sub-function
 **
 ** \param   [in]  enFuncSel          Function selection, This parameter can be
 **                                   any value of @ref en_port_func_t
 **
 ** \retval  None
 **
 ******************************************************************************/
void Port_SetSubFunc(en_port_func_t enFuncSel)
{
    M4_PORT->PCCR_f.BFSEL = enFuncSel;
}

//@} // GpioGroup

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
