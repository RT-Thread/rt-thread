/*!
 * @file        usbd_interrupt.c
 *
 * @brief       USB interrupt service routine
 *
 * @version     V1.0.0
 *
 * @date        2021-12-06
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "usbd_init.h"

static void USBD_LowPriorityProc(void);

static void USBD_ResetIsrHandler(void);
static void USBD_SuspendIsrHandler(void);
static void USBD_ResumeIsrHandler(void);

/*!
 * @brief       USB interrupt service routine
 *
 * @param       None
 *
 * @retval      None
 */
#ifdef APM32F0xx_USB
    void USB_IRQHandler(void)

#else //!< APM32F10x_USB
    #if USB_SELECT == USB1
        void USBD1_LP_CAN1_RX0_IRQHandler(void)
    #else
        void USB2_LP_IRQHandler(void)
    #endif
#endif
{
#if (USB_INT_SOURCE & USBD_INT_CTR)
    if (USBD_ReadIntFlag(USBD_INT_CTR))
    {
        USBD_LowPriorityProc();
    }
#endif

#if (USB_INT_SOURCE & USBD_INT_RST)
    if (USBD_ReadIntFlag(USBD_INT_RST))
    {
        USBD_ClearIntFlag(USBD_INT_RST);
        USBD_ResetIsrHandler();
    }
#endif

#if USB_INT_SOURCE & USBD_INT_PMAOU
    if (USB_ReadIntFlag(USB_INT_PMAOU))
    {
        USB_ClearIntFlag(USB_INT_PMAOU);
    }
#endif

#if USB_INT_SOURCE & USBD_INT_ERR

    if (USB_ReadIntFlag(USB_INT_ERROR))
    {
        USB_ClearIntFlag(USB_INT_ERROR);
    }
#endif

#if USB_INT_SOURCE & USBD_INT_WKUP
    if (USBD_ReadIntFlag(USBD_INT_WKUP))
    {
        USBD_ResumeIsrHandler();
        USBD_ClearIntFlag(USBD_INT_WKUP);
    }
#endif

#if USB_INT_SOURCE & USBD_INT_SUS
    if (USBD_ReadIntFlag(USBD_INT_SUS))
    {
        USBD_SuspendIsrHandler();
        USBD_ClearIntFlag(USBD_INT_SUS);
    }
#endif

#if USB_INT_SOURCE & USBD_INT_SOF
    if (USB_ReadIntFlag(USB_INT_SOF))
    {
        USB_ClearIntFlag(USB_INT_SOF);
    }
#endif

#if USB_INT_SOURCE & USBD_INT_ESOF
    if (USB_ReadIntFlag(USB_INT_ESOF))
    {
        USB_ClearIntFlag(USB_INT_ESOF);
    }
#endif
}

/*!
 * @brief       USB low priority process
 *
 * @param       None
 *
 * @retval      None
 */
static void USBD_LowPriorityProc(void)
{
    USBD_EP_T ep;

    while (USBD_ReadIntFlag(USBD_INT_CTR))
    {
        ep = (USBD_EP_T)USBD_ReadEP();

        /** Endpoint 0 */
        if (ep == 0)
        {
            USBD_SetEPTxRxStatus(USBD_EP_0, USBD_EP_STATUS_NAK, USBD_EP_STATUS_NAK);

            /** Control in */
            if (USBD_ReadDir() == 0)
            {
                USBD_ResetEPTxFlag(USBD_EP_0);
                USBD_CtrlInProcess();
            }
            else
            {
                /** Setup */
                if (USBD_ReadEPSetup(USBD_EP_0) == SET)
                {
                    USBD_ResetEPRxFlag(USBD_EP_0);
                    USBD_SetupProcess();
                }
                /** Control out */
                else
                {
                    USBD_ResetEPRxFlag(USBD_EP_0);
                    USBD_CtrlOutProcess();
                }
            }
        }
        /** Transfer Handler Except endpoint 0 */
        else
        {
            if (USBD_ReadEPRxFlag(ep))
            {
                USBD_ResetEPRxFlag(ep);
                USBD_DataOutProcess(ep);
            }

            if (USBD_ReadEPTxFlag(ep))
            {
                USBD_ResetEPTxFlag(ep);
                USBD_DataInProcess(ep);
            }
        }
    }
}


/*!
 * @brief      USB Device Reset
 *
 * @param      None
 *
 * @retval     None
 */
static void USBD_ResetIsrHandler(void)
{
    uint8_t i;
    USBD_EPConfig_T epConfig;

    g_usbDev.configurationNum = USB_CONFIGURATION_NUM;
    g_usbDev.curConfiguration = 0;
    g_usbDev.curInterface = 0;
    g_usbDev.curAlternateSetting = 0;
    g_usbDev.curFeature = 0;
    g_usbDev.ctrlState = USBD_CTRL_STATE_WAIT_SETUP;

    g_usbDev.inBuf[USBD_EP_0].maxPackSize = USB_EP0_PACKET_SIZE;
    g_usbDev.outBuf[USBD_EP_0].maxPackSize = USB_EP0_PACKET_SIZE;

    USBD_SetBufferTable(USB_BUFFER_TABLE_ADDR);

    /** Endpoint 0 IN */
    epConfig.epNum = USBD_EP_0;
    epConfig.epType = USBD_EP_TYPE_CONTROL;
    epConfig.epKind = DISABLE;
    epConfig.epBufAddr = USB_EP0_TX_ADDR;
    epConfig.maxPackSize = g_usbDev.inBuf[USBD_EP_0].maxPackSize;
    epConfig.epStatus = USBD_EP_STATUS_NAK;
    USBD_OpenInEP(&epConfig);

    /** Endpoint 0 OUT */
    epConfig.epBufAddr = USB_EP0_RX_ADDR;
    epConfig.maxPackSize = g_usbDev.outBuf[USBD_EP_0].maxPackSize;
    epConfig.epStatus = USBD_EP_STATUS_VALID;
    USBD_OpenOutEP(&epConfig);

    if (g_usbDev.resetHandler)
    {
        g_usbDev.resetHandler();
    }

    for (i = 0; i < USB_EP_MAX_NUM; i++)
    {
        USBD_SetEpAddr((USBD_EP_T)i, i);
    }

    USBD_SetDeviceAddr(0);
    USBD_Enable();
}

/*!
 * @brief       USB Suspend
 *
 * @param       None
 *
 * @retval      None
 */
static void USBD_SuspendIsrHandler(void)
{
    uint8_t i;
    uint16_t bakEP[8];
#if USB_LOW_POWER_SWITCH
    uint32_t bakPwrCR;
    uint32_t tmp;
#endif

    for (i = 0; i < 8; i++)
    {
        bakEP[i] = (uint16_t)USBD->EP[i].EP;
    }

    USBD_EnableInterrupt(USBD_INT_RST);

    USBD_SetForceReset();
    USBD_ResetForceReset();

    while (USBD_ReadIntFlag(USBD_INT_RST) == RESET);

    for (i = 0; i < 8; i++)
    {
        USBD->EP[i].EP = bakEP[i];
    }

    USBD_SetForceSuspend();

#if USB_LOW_POWER_SWITCH
    USBD_SetLowerPowerMode();

    bakPwrCR = PMU->CTRL;
    tmp = PMU->CTRL;
    tmp &= (uint32_t)0xfffffffc;
    tmp |= PMU_REGULATOR_LOWPOWER;
    PMU->CTRL = tmp;

    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    if (USBD_ReadIntFlag(USBD_INT_WKUP) == RESET)
    {
        __WFI();
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
    else
    {
        USBD_ClearIntFlag(USBD_INT_WKUP);
        USBD_ResetForceSuspend();
        PMU->CTRL = bakPwrCR;
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
    }
#endif
}

/*!
 * @brief       Resume
 *
 * @param       None
 *
 * @retval      None
 */
static void USBD_ResumeIsrHandler(void)
{
#if USB_LOW_POWER_SWITCH
    USBD_ResetLowerPowerMode();
#endif

    SystemInit();

    USBD_SetRegCTRL(USB_INT_SOURCE);
}

#ifndef APM32F0xx_USB
/*!
 * @brief       USB High priority process
 *
 * @param       None
 *
 * @retval      None
 */
static void USBD_HighPriorityProc(void)
{
    USBD_EP_T ep;

    while (USBD_ReadIntFlag(USBD_INT_CTR))
    {
        USBD_ClearIntFlag(USBD_INT_CTR);

        ep = USBD_ReadEP();

        if (USBD_ReadEPRxFlag(ep))
        {
            USBD_ResetEPRxFlag(ep);

            g_usbDev.outEpHandler(ep);
        }

        if (USBD_ReadEPTxFlag(ep))
        {
            USBD_ResetEPTxFlag(ep);

            g_usbDev.inEpHandler(ep);
        }
    }
}

#if USB_SELECT == USB1
    void USBD1_HP_CAN1_TX_IRQHandler(void)
#else
    void USB2_HP_IRQHandler(void)
#endif
{
    USBD_HighPriorityProc();
}

#endif
