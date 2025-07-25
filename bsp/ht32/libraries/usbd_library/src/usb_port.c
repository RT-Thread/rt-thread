/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-09     QT-one       first version
 */

#include "usb_port.h"

/* Global variables ----------------------------------------------------------------------------------------*/
USBDCore_TypeDef *gUSBCore;
USBD_Driver_TypeDef gUSBDriver;
u32 gIsLowPowerAllowed = TRUE;

#if (LIBCFG_CKCU_USB_PLL)
/*********************************************************************************************************//**
 * @brief  Configure USB PLL
 * @retval None
 ************************************************************************************************************/
static void USBPLL_Configuration(void)
{
    {
        /* USB PLL configuration                                                                                */

        /* !!! NOTICE !!!
           Notice that the local variable (structure) did not have an initial value.
           Please confirm that there are no missing members in the parameter settings below in this function.
        */
        CKCU_PLLInitTypeDef PLLInit;

        PLLInit.ClockSource = CKCU_PLLSRC_HSE;  // CKCU_PLLSRC_HSE or CKCU_PLLSRC_HSI
#if (LIBCFG_CKCU_USB_PLL_96M)
        PLLInit.CFG = CKCU_USBPLL_8M_96M;
#else
        PLLInit.CFG = CKCU_USBPLL_8M_48M;
#endif
        PLLInit.BYPASSCmd = DISABLE;
        CKCU_USBPLLInit(&PLLInit);
    }

    CKCU_USBPLLCmd(ENABLE);

    while (CKCU_GetClockReadyStatus(CKCU_FLAG_USBPLLRDY) == RESET);
    CKCU_USBClockConfig(CKCU_CKUSBPLL);
}
#endif

#if (LIBCFG_PWRCU_VREG)
/*********************************************************************************************************//**
 * @brief  Configure USB Voltage
 * @retval None
 ************************************************************************************************************/
static void USBVRG_Configuration(void)
{
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.BKP = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    PWRCU_SetVREG(PWRCU_VREG_3V3);

    /* !!! NOTICE !!!
       USB LDO should be enabled (PWRCU_VREG_ENABLE) if the MCU VDD > 3.6 V.
    */
    PWRCU_VREGConfig(PWRCU_VREG_BYPASS);
}
#endif

#define REMOTE_WAKEUP      (0)
/*********************************************************************************************************//**
  * @brief  Suspend call back function which enter DeepSleep1
  * @param  uPara: Parameter for Call back function
  * @retval None
  ***********************************************************************************************************/
static void Suspend(u32 uPara)
{
#if (REMOTE_WAKEUP == 1)
    u32 IsRemoteWakeupAllowed;
#endif

    if (gIsLowPowerAllowed)
    {

#if (REMOTE_WAKEUP == 1)
        /* Disable EXTI interrupt to prevent interrupt occurred after wakeup                                    */
        EXTI_IntConfig(KEY1_BUTTON_EXTI_CHANNEL, DISABLE);
        IsRemoteWakeupAllowed = USBDCore_GetRemoteWakeUpFeature(&gUSBCore);

        if (IsRemoteWakeupAllowed == TRUE)
        {
            /* Enable EXTI wake event and clear wakeup flag                                                       */
            EXTI_WakeupEventConfig(KEY1_BUTTON_EXTI_CHANNEL, EXTI_WAKEUP_LOW_LEVEL, ENABLE);
            EXTI_ClearWakeupFlag(KEY1_BUTTON_EXTI_CHANNEL);
        }
#endif

        __DBG_USBPrintf("%06ld >DEEPSLEEP\r\n", ++__DBG_USBCount);

        // Add your procedure here which disable related IO to reduce power consumption
        // ..................
        //

        if ((gUSBCore->Info.CurrentStatus == USER_USB_STATE_SUSPENDED) && ((HT_USB->CSR & 0xC0) == 0x40))   // D+ = 1, D- = 0
        {
            /* For Bus powered device, you must enter DeepSleep1 when device has been suspended. For self-powered */
            /* device, you may decide to enter DeepSleep1 or not depended on your application.                    */

            /* For the convenient during debugging and evaluation stage, the USBDCore_LowPower() is map to a null */
            /* function by default. In the real product, you must map this function to the low power function of  */
            /* firmware library by setting USBDCORE_ENABLE_LOW_POWER as 1 (in the ht32fxxxx_usbdconf.h file).     */
            USBDCore_LowPower();
        }

        // Add your procedure here which recovery related IO for application
        // ..................
        //

        __DBG_USBPrintf("%06ld <DEEPSLEEP\r\n", ++__DBG_USBCount);

#if (REMOTE_WAKEUP == 1)
        if (EXTI_GetWakeupFlagStatus(KEY1_BUTTON_EXTI_CHANNEL) == SET)
        {
            __DBG_USBPrintf("%06ld WAKEUP\r\n", ++__DBG_USBCount);
            if (IsRemoteWakeupAllowed == TRUE && USBDCore_IsSuspend(&gUSBCore) == TRUE)
            {
                USBDCore_TriggerRemoteWakeup();
            }
        }

        if (IsRemoteWakeupAllowed == TRUE)
        {
            /* Disable EXTI wake event and clear wakeup flag                                                      */
            EXTI_WakeupEventConfig(KEY1_BUTTON_EXTI_CHANNEL, EXTI_WAKEUP_LOW_LEVEL, DISABLE);
            EXTI_ClearWakeupFlag(KEY1_BUTTON_EXTI_CHANNEL);
        }

        /* Clear EXTI edge flag and enable EXTI interrupt                                                       */
        EXTI_ClearEdgeFlag(KEY1_BUTTON_EXTI_CHANNEL);
        EXTI_IntConfig(KEY1_BUTTON_EXTI_CHANNEL, ENABLE);
#endif
    }

    return;
}
/*********************************************************************************************************//**
  * @brief  Configure USB.
  * @retval None
  ***********************************************************************************************************/
void USB_Configuration(USBDCore_TypeDef *pCore)
{

    /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.USBD = 1;
    CKCUClock.Bit.EXTI = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    gUSBCore = pCore;

#if (LIBCFG_CKCU_USB_PLL)
    USBPLL_Configuration();
#endif

#if (LIBCFG_PWRCU_VREG)
    USBVRG_Configuration();                               /* Voltage of USB setting                           */
#endif

    /* !!! NOTICE !!!
       Must turn on if the USB clock source is from HSI (PLL clock Source)
    */
#if 0

    /* Turn on HSI auto trim function                                                                       */
    CKCU_HSIAutoTrimClkConfig(CKCU_ATC_USB);
    CKCU_HSIAutoTrimCmd(ENABLE);

#endif


    /* USB Descriptor, Core, and Class initialization                                                       */
    gUSBCore->pDriver = (u32 *)&gUSBDriver;              /* Initiate memory pointer of USB driver            */
    gUSBCore->Power.CallBack_Suspend.func  = Suspend;    /* Install suspend call back function into USB core */

//    USBDDesc_Init(&gUSBCore.Device.Desc);               /* Initiate memory pointer of descriptor            */
//    USBDClass_Init(&gUSBCore.Class);                    /* Initiate USB Class layer                         */
    USBDCore_Init(gUSBCore);                           /* Initiate USB Core layer                          */

    NVIC_SetPriority(USB_IRQn,0);
    NVIC_EnableIRQ(USB_IRQn);                             /* Enable USB device interrupt                      */

    HT32F_DVB_USBConnect();

}








