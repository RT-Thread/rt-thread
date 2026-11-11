/**
  ******************************************************************************
  * @file    tae32f53xx_ll_usb.c
  * @author  MCD Application Team
  * @brief   USB LL Module Driver.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll.h"


#define DBG_TAG             "USB LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup USB_LL USB LL
  * @brief    USB LL Module Driver.
  * @{
  */


#ifdef LL_USB_MODULE_ENABLED


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup USB_LL_Exported_Functions USB LL Exported Functions
  * @brief    USB LL Exported Functions
  * @{
  */

/** @defgroup USB_LL_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and Configuration functions
  *
  @verbatim
  ===============================================================================
              ##### Initialization and de-initialization functions #####
  ===============================================================================
   [..]
     This section provides functions allowing to initialize and de-initialize the USB
     to be ready for use.

  @endverbatim
  * @{
  */

/**
  * @brief  Initializes the USB peripheral
  * @param  Instance Specifies USB peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_USB_Init(USB_TypeDef *Instance)
{
    /* Init the low level hardware eg. Clock, NVIC */
    LL_USB_MspInit(Instance);

    //USB Hardware Config
    __LL_USB_DMOutputHardware(Instance);
    __LL_USB_DPOutputHardware(Instance);
    __LL_USB_DMInputHardware(Instance);
    __LL_USB_DPInputHardware(Instance);

    __LL_USB_DMPullDownDisable(Instance);
    __LL_USB_DMPullUpNormal(Instance);
    __LL_USB_DPPullDownDisable(Instance);
    __LL_USB_DPPullUpNormal(Instance);

    __LL_USB_VbusValidThreshold_Set(Instance);
    __LL_USB_VbusAboveAdevSessThres_Set(Instance);
    __LL_USB_VbusAboveSessEndThres_Set(Instance);
    __LL_USB_MiniABConnectorID_Set(Instance);
    __LL_USB_PHY_En(Instance);

    //USB Power Control
    __LL_USB_SoftConn_En(Instance);
    __LL_USB_HighSpeed_Dis(Instance);
    __LL_USB_SuspendDMOut_En(Instance);

    //USB Detect Interrupt Config
    __LL_USB_DebouceMax_Set(Instance, 0x80);
    __LL_USB_Conn_Clr(Instance);
    __LL_USB_Conn_Int_En(Instance);
    __LL_USB_Disconn_Clr(Instance);
    __LL_USB_Disconn_Int_En(Instance);

    //USB Interrupt Enable
    __LL_USB_Int_EN(Instance, USB_CTRL_INT_ALL_Msk);
    __LL_USB_EP0AndEPxTX_Int_EN(Instance, EP_NUM_0);

    //USB INT Send To CPU Config
    __LL_USB_INTSendToCPU_En(Instance, USB_CTRL_INT_TO_CPU_Msk);
    __LL_USB_INTSendToCPU_En(Instance, USB_EP_INT_TO_CPU_Msk);
    __LL_USB_INTSendToCPU_En(Instance, USB_LPM_INT_TO_CPU_Msk);

    return LL_OK;
}

/**
  * @brief  DeInitializes the USB peripheral
  * @param  Instance Specifies USB peripheral
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_USB_DeInit(USB_TypeDef *Instance)
{
    //USB INT Send To CPU Config
    __LL_USB_INTSendToCPU_Dis(Instance, USB_CTRL_INT_TO_CPU_Msk);
    __LL_USB_INTSendToCPU_Dis(Instance, USB_EP_INT_TO_CPU_Msk);
    __LL_USB_INTSendToCPU_Dis(Instance, USB_LPM_INT_TO_CPU_Msk);

    //USB Interrupt Disable
    __LL_USB_Int_Dis(Instance, USB_CTRL_INT_ALL_Msk);
    __LL_USB_EP0AndEPxTX_Int_Dis(Instance, EP_NUM_0);

    //USB Detect Interrupt Config
    __LL_USB_Conn_Clr(Instance);
    __LL_USB_Conn_Int_Dis(Instance);
    __LL_USB_Disconn_Clr(Instance);
    __LL_USB_Disconn_Int_Dis(Instance);

    //USB Power Control
    __LL_USB_SoftConn_Dis(Instance);
    __LL_USB_SuspendDMOut_Dis(Instance);

    //USB Hardware Config
    __LL_USB_DMOutputNormal(Instance);
    __LL_USB_DPOutputNormal(Instance);
    __LL_USB_DMInputNormal(Instance);
    __LL_USB_DPInputNormal(Instance);
    __LL_USB_DMPullDownNormal(Instance);
    __LL_USB_DMPullUpNormal(Instance);
    __LL_USB_DPPullDownNormal(Instance);
    __LL_USB_DPPullUpNormal(Instance);

    __LL_USB_VbusValidThreshold_Clr(Instance);
    __LL_USB_VbusAboveAdevSessThres_Clr(Instance);
    __LL_USB_VbusAboveSessEndThres_Clr(Instance);
    __LL_USB_MiniABConnectorID_Clr(Instance);
    __LL_USB_PHY_Dis(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_USB_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the USB MSP.
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_MspInit(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the USB MSP
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_MspDeInit(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_MspDeInit could be implemented in the user file
     */
}
/**
  * @}
  */


/** @defgroup USB_LL_Exported_Functions_Group2 USB Controler Initerrupt Management
  * @brief    USB Controler Initerrupt Management
    *
  @verbatim
  ==============================================================================
                        ##### IRQ handler management #####
  ==============================================================================
  [..]
    This section provides USB Controler IRQ handler function.
  @endverbatim
  * @{
  */

/**
  * @brief  LL USB Controler IRQ Handler
  * @param  Instance Specifies USB peripheral
  * @return None
  */
void LL_USB_CtrlIRQHandler(USB_TypeDef *Instance)
{
    uint8_t usb_ctrl_int_sta = __LL_USB_IntSta_Get(Instance);

    if (usb_ctrl_int_sta & USB_SUSPEND_INT_STA_Msk) {
        LL_USB_CtrlSuspendCallback(Instance);
    }

    if (usb_ctrl_int_sta & USB_RESUME_INT_STA_Msk) {
        LL_USB_CtrlResumeCallback(Instance);
    }

    if (usb_ctrl_int_sta & USB_RST_INT_STA_Msk) {
        LL_USB_CtrlResetCallback(Instance);
    }

    if (usb_ctrl_int_sta & USB_SOF_INT_STA_Msk) {
        LL_USB_CtrlSofCallback(Instance);
    }

    if (usb_ctrl_int_sta & USB_SESS_END_INT_STA_Msk) {
        LL_USB_CtrlSessEndCallback(Instance);
    }
}

/**
  * @brief  USB Controler Suspend Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_CtrlSuspendCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_CtrlSuspendCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Controler Resume Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_CtrlResumeCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_CtrlResumeCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Controler Reset Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_CtrlResetCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_CtrlResetCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Controler SOF Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_CtrlSofCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_CtrlSofCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Controler Session End Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_CtrlSessEndCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_CtrlSessEndCallback could be implemented in the USB Middleware file
     */
}
/**
  * @}
  */


/** @defgroup USB_LL_Exported_Functions_Group3 USB Detect Initerrupt Management
  * @brief    USB Detect Initerrupt Management
    *
  @verbatim
  ==============================================================================
                        ##### IRQ handler management #####
  ==============================================================================
  [..]
    This section provides USB Detect IRQ handler function.
  @endverbatim
  * @{
  */

/**
  * @brief  LL USB Detect IRQ Handler
  * @param  Instance Specifies USB peripheral
  * @return None
  */
void LL_USB_DetIRQHandler(USB_TypeDef *Instance)
{
    if (__LL_USB_IsConn(Instance)) {
        __LL_USB_Conn_Clr(Instance);
        LL_USB_DetConnectCallback(Instance);
    }

    if (__LL_USB_IsDisconn(Instance)) {
        __LL_USB_Disconn_Clr(Instance);
        LL_USB_DetDisonnectCallback(Instance);
    }
}

/**
  * @brief  USB Detect Connect Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_DetConnectCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_DetConnectCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Detect Disconnect Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_DetDisonnectCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_DetDisonnectCallback could be implemented in the USB Middleware file
     */
}
/**
  * @}
  */


/** @defgroup USB_LL_Exported_Functions_Group4 USB Endpoint Initerrupt Management
  * @brief    USB Endpoint Initerrupt Management
    *
  @verbatim
  ==============================================================================
                        ##### IRQ handler management #####
  ==============================================================================
  [..]
    This section provides USB Endpoint IRQ handler function.
  @endverbatim
  * @{
  */

/**
  * @brief  LL USB Endpoint IRQ Handler
  * @param  Instance Specifies USB peripheral
  * @return None
  */
void LL_USB_EpIRQHandler(USB_TypeDef *Instance)
{
    uint8_t ep0_epxtx_int_sta, epx_rx_int_sta;

    //Get all endpoint interrupt status
    epx_rx_int_sta = __LL_USB_EPx_RXIntSta_Get(Instance);
    ep0_epxtx_int_sta = __LL_USB_EP0AndEPxTX_IntSta_Get(Instance);

    if (ep0_epxtx_int_sta & USB_EP0_INT_STA_Msk) {              /* Endpoint 0 Interrupt */
        //USB Endpoint Index Set
        __LL_USB_EPIndex_Set(Instance, EP_NUM_0);

        if (__LL_USB_IsSetupPacket(Instance) && __LL_USB_EP0_IsRXPktRdy(Instance)) {        //Endpoint 0 Setup
            LL_USB_Ep0SetupCallback(Instance);
        } else if (__LL_USB_IsInPacket(Instance)) {                                         //Endpoint 0 IN
            LL_USB_Ep0InCallback(Instance);
        } else if (__LL_USB_IsOutPacket(Instance) && __LL_USB_EP0_IsRXPktRdy(Instance)) {   //Endpoint 0 OUT
            LL_USB_Ep0OutCallback(Instance);
        }
    } else if (ep0_epxtx_int_sta & USB_TX_EP1_INT_STA_Msk) {    /* Endpoint 1 IN Interrupt */
        //USB Endpoint Index Set
        __LL_USB_EPIndex_Set(Instance, EP_NUM_1);
        LL_USB_Ep1InCallback(Instance);
    } else if (ep0_epxtx_int_sta & USB_TX_EP2_INT_STA_Msk) {    /* Endpoint 2 IN Interrupt */
        //USB Endpoint Index Set
        __LL_USB_EPIndex_Set(Instance, EP_NUM_2);
        LL_USB_Ep2InCallback(Instance);
    } else if (epx_rx_int_sta & USB_RX_EP1_INT_STA_Msk) {       /* Endpoint 1 OUT Interrupt */
        //USB Endpoint Index Set
        __LL_USB_EPIndex_Set(Instance, EP_NUM_1);
        LL_USB_Ep1OutCallback(Instance);
    } else if (epx_rx_int_sta & USB_RX_EP2_INT_STA_Msk) {       /* Endpoint 2 OUT Interrupt */
        //USB Endpoint Index Set
        __LL_USB_EPIndex_Set(Instance, EP_NUM_2);
        LL_USB_Ep2OutCallback(Instance);
    }
}

/**
  * @brief  USB Endpoint 0 Setup Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_Ep0SetupCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_Ep0SetupCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Endpoint 0 In Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_Ep0InCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_Ep0InCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Endpoint 0 Out Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_Ep0OutCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_Ep0OutCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Endpoint 1 In Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_Ep1InCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_Ep1InCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Endpoint 1 Out Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_Ep1OutCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_Ep1OutCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Endpoint 2 In Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_Ep2InCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_Ep2InCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Endpoint 2 Out Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_Ep2OutCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_Ep2OutCallback could be implemented in the USB Middleware file
     */
}
/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif /* LL_USB_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

