/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-11     QT-one       first version
 */

#include "ht32_usbd_int.h"

#ifdef RT_USING_USB_DEVICE
//#include "ht32_usbd_core.h"



static void USBPLL_Configuration(void);
static void USBVRG_Configuration(void);
static void Suspend(u32 uPara);


static USBDCore_TypeDef *int_p_usbd_code;
static USBD_Driver_TypeDef gUSBDriver;
static u32 gIsLowPowerAllowed = TRUE;

/*
    为了不破坏原本的usb_code文件中的USB中断回调函数
    此处重构USB中断回调函数
    除了重构USB的中断回调函数以外，还需要重写一些中断回调功能函数
*/
/*
    RTT的USB中断回调过程如下
    USB中断函数 -> USB中断回调函数 -> USB相关功能回调函数
    -> RTT的USB相关功能回调函数 -> 结束USB中断

    RTT的USB程序运行流程（RTT的USB线程运行流程）
    USB线程阻塞等待USB获取到消息队列中的消息
    -> USB中断通过回调函数将接收到的消息传给USB的消息队列
    -> RTT的USB相关功能回调函数获取到USB中断的消息，并设置USB消息队列的状态
    -> USB退出中断，USB获取到消息后，线程阻塞被解除
    -> USB线程根据获取的状态执行对应的功能
    -> USB线程通过USB操作接口实现对应的功能

*/
/*
    根据RTT的USB中断回调过程和RTT的USB线程执行过程
    得出完成USB驱动需要实现的两个重要部分
    1、USB线程实现功能所需要的调用到的USB操作接口函数
    2、USB中断回调过程使用到的RTT的USB驱动的函数的相关衔接部分

    除了以上两个比较重要的功能外，还需要完成以下的一些必要部分
    1、USB初始化函数
    2、USB设备注册函数

    完成以上功能主要涉及到两个文件为：
    1、drv_usbd.c
    2、ht32_usbd_int.c

    对两个文件的内容分配以及文件依赖如下：
    drv_usbd.c
        主要负责实现USB的操作接口的实现
        以及初始化函数和USB设备注册函数
        由于自定义的USB内核挂载点在该文件中
        所以USB的中断函数也会写在该文件中
        依赖：
            ht32_usbd_core.c
            ht32_usbd_int.c
            以及RTT的相关文件

    ht32_usbd_int.c
        主要负责实现USB中断回调以及回调函数
        中和RTT的USB驱动函数相关衔接部分
        该文件还会包含USB的初始配置函数以及
        USB的休眠与唤醒的相关函数
        依赖：
            ht32_usbd_core.c
            以及RTT的相关文件
*/

/* 帧起始（SOF）中断回调 */
void usbd_sof_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_sof_handler(udcd);
}
/* USB复位中断 */
void usbd_reset_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_reset_handler(udcd);
}

/* USB暂停(断开连接)中断 */
void usbd_suspend_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_disconnect_handler(udcd);
}

/* USB恢复（重新连接）中断 */
void usbd_resume_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_connect_handler(udcd);
}

/* USB端点0中断 */
/* 端点0控制中断 */
void usbd_setup_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_ep0_setup_handler(udcd, (struct urequest *)&pCore->Device.Request);
}

/* 端点0输入中断（可以归入其他端点输入中断） */
void usbd_ep0_in_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_ep0_in_handler(udcd);
}

/* 端点0输出中断（可以归入其他端点输出中断） */
void usbd_ep0_out_callback(USBDCore_TypeDef *pCore)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_ep0_out_handler(udcd, pCore->Device.Transfer.sByteLength);
}

/* USB其他端点中断 */
/* 其他端点输入中断 */
void usbd_ep_in_callback(USBDCore_TypeDef *pCore, USBD_EPTn_Enum EPTn)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_ep_in_handler(udcd, EPTn | 0x80, pCore->Device.Transfer.sByteLength);
}

/* 其他端点输出中断 */
void usbd_ep_out_callback(USBDCore_TypeDef *pCore, USBD_EPTn_Enum EPTn)
{
    udcd_t udcd = (udcd_t)pCore->pdata;
    rt_usbd_ep_out_handler(udcd, EPTn, pCore->Device.Transfer.sByteLength);
}




//rt_err_t rt_usbd_set_feature(udevice_t device, rt_uint16_t value, rt_uint16_t index);
//rt_err_t rt_usbd_clear_feature(udevice_t device, rt_uint16_t value, rt_uint16_t index);
//rt_err_t rt_usbd_ep_set_stall(udevice_t device, uep_t ep);
//rt_err_t rt_usbd_ep_clear_stall(udevice_t device, uep_t ep);
//rt_err_t rt_usbd_ep0_set_stall(udevice_t device);
//rt_err_t rt_usbd_ep0_clear_stall(udevice_t device);


/*********************************************************************************************************//**
  * @brief  Configure USB.
  * @retval None
  ***********************************************************************************************************/
static void USB_Configuration(USBDCore_TypeDef *pCore)
{
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.USBD       = 1;
    CKCUClock.Bit.EXTI       = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
    
    int_p_usbd_code = pCore;

#if (LIBCFG_CKCU_USB_PLL)
    USBPLL_Configuration();
#endif

#if (LIBCFG_PWRCU_VREG)
    USBVRG_Configuration();                               /* Voltage of USB setting                           */
#endif

    pCore->pDriver = (u32 *)&gUSBDriver;                /* Initiate memory pointer of USB driver            */
    pCore->Power.CallBack_Suspend.func  = Suspend;      /* Install suspend call back function into USB core */

//    gUSBCore.pDriver = (u32 *)&gUSBDriver;                /* Initiate memory pointer of USB driver            */
//    gUSBCore.Power.CallBack_Suspend.func  = Suspend;      /* Install suspend call back function into USB core */
    //gUSBCore.Power.CallBack_Suspend.uPara = (u32)NULL;
    
    /* 描述符初始化 */
//    USBDDesc_Init(&pCore->Device.Desc);                 /* Initiate memory pointer of descriptor            */
    /* USB类初始化 */
//    USBDClass_Init(&(pCore->Class));                      /* Initiate USB Class layer                         */
    /* USB内核初始化 */
    USBDCore_Init(pCore);                             /* Initiate USB Core layer                          */

    /* !!! NOTICE !!!
       Must turn on if the USB clock source is from HSI (PLL clock Source)
    */
#if 0
    {
        /* Turn on HSI auto trim function                                                                       */
        CKCU_HSIAutoTrimClkConfig(CKCU_ATC_USB);
        CKCU_HSIAutoTrimCmd(ENABLE);
    }
#endif

    NVIC_EnableIRQ(USB_IRQn);                             /* Enable USB device interrupt                      */
}

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
    CKCUClock.Bit.BKP                   = 1;
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
        
        if ((int_p_usbd_code->Info.CurrentStatus == USB_STATE_SUSPENDED) && ((HT_USB->CSR & 0xC0) == 0x40))   // D+ = 1, D- = 0
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



















#endif /* RT_USING_USB_DEVICE */
