/**
  ******************************************************************************
  * @file    tae32g58xx_ll_usb.c
  * @author  MCD Application Team
  * @brief   USB LL module driver
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
#include "tae32g58xx_ll.h"


#define DBG_TAG             "USB LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup USB_LL USB LL
  * @brief    USB LL module driver
  * @{
  */

#ifdef LL_USB_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/** @defgroup USB_LL_Private_Types USB LL Private Types
  * @brief    USB LL Private Types
  * @{
  */

/**
  * @brief USB LL Handle Definition
  */
typedef struct __USB_HandleTypeDef {
    volatile USB_LL_IRQCbTypeDef *irq_cb;
} USB_HandleTypeDef;

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup USB_LL_Private_Variables USB LL Private Variables
  * @brief    USB LL Private Variables
  * @{
  */

/**
  * @brief USB LL Handle global variable
  */
static USB_HandleTypeDef usb_hdl_global[USB_INSTANCE_NUMS];

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup USB_LL_Private_Functions USB LL Private Functions
  * @brief    USB LL Private Functions
  * @{
  */
static USB_HandleTypeDef *USB_Handle_Get(USB_TypeDef *Instance);
static void USB_EpMaxPktSizeCfg(USB_TypeDef *Instance, USB_EpDirETypeDef ep_dir, uint32_t ep_max_pl);
__STATIC_INLINE void USB_EpIntCfg(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, USB_EpDirETypeDef ep_dir, bool ep_int_en);
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/** @defgroup USB_LL_Exported_Variables USB LL Exported Variables
  * @brief    USB LL Exported Variables
  * @{
  */

/**
  * @brief USB LL Driver Interface Const Definition
  */
const USB_LL_DrvTypeDef usb_ll_drv = {
    //Endpoint Operation Interface
    .EpCfg       = LL_USB_EpCfg,
    .EpFIFOFlush = LL_USB_EpFIFOFlush,
    .EpFIFORead  = LL_USB_EpFIFORead,
    .EpFIFOWrite = LL_USB_EpFIFOWrite,

    //Setup Operation Interface
    .SetupStallSet   = LL_USB_SetupStallSet,
    .SetupStallClr   = LL_USB_SetupStallClr,
    .SetupDataEndSet = LL_USB_SetupDataEndSet,
    .SetupAddrSet    = LL_USB_SetupAddrSet,
};

/**
  * @}
  */


/* Exported Functions --------------------------------------------------------*/
/** @defgroup USB_LL_Exported_Functions USB LL Exported Functions
  * @brief    USB LL Exported Functions
  * @{
  */

/** @defgroup USB_LL_Exported_Functions_Group1 USB Init and DeInit Functions
  * @brief    USB Init and DeInit Functions
  * @{
  */

/**
  * @brief  USB LL Init
  * @param  Instance Specifies USB peripheral
  * @param  irq_cb Optional IRQ Callback pointer
  * @note   IRQ Callback pointer is designed for USB Core normally, when user not use, please set it to NULL
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_USB_Init(USB_TypeDef *Instance, USB_LL_IRQCbTypeDef *irq_cb)
{
    USB_HandleTypeDef *usb_hdl;

    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (!IS_USB_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //USB handle get
    usb_hdl = USB_Handle_Get(Instance);

    if (usb_hdl == NULL) {
        LOG_E("Get USB handle error!\n");
        return LL_ERROR;
    }

    //USB handle Init
    usb_hdl->irq_cb = irq_cb;

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

    //USB Detect Interrupt Enable
    __LL_USB_DebouceMax_Set(Instance, 0x80);
    __LL_USB_InsertDetIntPnd_Clr(Instance);
    __LL_USB_InsertDet_INT_En(Instance);
    __LL_USB_UnplugDetIntPnd_Clr(Instance);
    __LL_USB_UnplugDet_INT_En(Instance);

    //USB Power Interrupt Enable
    __LL_USB_PeriphDisconn_INT_En(Instance);
    __LL_USB_SOF_INT_En(Instance);
    __LL_USB_Rst_INT_En(Instance);
    __LL_USB_Resume_INT_En(Instance);
    __LL_USB_Suspend_INT_En(Instance);

    //USB Endpoint 0 Interrupt Enable
    __LL_USB_Ep0_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  USB LL DeInit
  * @param  Instance Specifies USB peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_USB_DeInit(USB_TypeDef *Instance)
{
    USB_HandleTypeDef *usb_hdl;

    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (!IS_USB_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //USB handle get
    usb_hdl = USB_Handle_Get(Instance);

    if (usb_hdl == NULL) {
        LOG_E("Get USB handle error!\n");
        return LL_ERROR;
    }

    //USB handle DeInit
    usb_hdl->irq_cb = NULL;

    //USB Endpoint 0 Interrupt Disable
    __LL_USB_Ep0_INT_Dis(Instance);

    //USB Power Interrupt Disable
    __LL_USB_PeriphDisconn_INT_Dis(Instance);
    __LL_USB_SOF_INT_Dis(Instance);
    __LL_USB_Rst_INT_Dis(Instance);
    __LL_USB_Resume_INT_Dis(Instance);
    __LL_USB_Suspend_INT_Dis(Instance);

    //USB Detect Interrupt Disable
    __LL_USB_InsertDet_INT_Dis(Instance);
    __LL_USB_InsertDetIntPnd_Clr(Instance);
    __LL_USB_UnplugDet_INT_Dis(Instance);
    __LL_USB_UnplugDetIntPnd_Clr(Instance);

    //USB Power Control
    __LL_USB_SoftConn_Dis(Instance);

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
  * @brief  Initializes the USB MSP
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


/** @defgroup USB_LL_Exported_Functions_Group2 USB Endpoint Operation Functions
  * @brief    USB Endpoint Operation Functions
  * @{
  */

/**
  * @brief  LL USB Endpoint Config
  * @param  Instance Specifies USB peripheral
  * @param  ep_cfg Endpoint Config Pointer
  * @param  ep_en  Endpoint Enable/Disable
  * @return LL Status
  */
LL_StatusETypeDef LL_USB_EpCfg(USB_TypeDef *Instance, USB_EpCfgTypeDef *ep_cfg, bool ep_en)
{
    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));
    assert_param(ep_cfg != NULL);
    assert_param(ep_cfg->ep_num < EP_NUMS);

    if (!IS_USB_ALL_INSTANCE(Instance) || ep_cfg == NULL || ep_cfg->ep_num >= EP_NUMS) {
        return LL_INVALID;
    }

    //USB Endpoint Index Set
    __LL_USB_EPIndex_Set(Instance, ep_cfg->ep_num);

    //USB Endpoint Common Config
    if (ep_en) {
        if (ep_cfg->ep_dir == EP_DIR_OUT) {
            __LL_USB_EPx_TX_En(Instance);
            __LL_USB_EPx_TXMaxPayload_Set(Instance, ep_cfg->ep_max_pl);
            LL_FUNC_ALTER(ep_cfg->ep_type == EP_TYPE_ISOC, __LL_USB_EPx_TXISO_En(Instance), __LL_USB_EPx_TXISO_Dis(Instance));
        } else {
            __LL_USB_EPx_RX_En(Instance);
            __LL_USB_EPx_RXMaxPayload_Set(Instance, ep_cfg->ep_max_pl);
            LL_FUNC_ALTER(ep_cfg->ep_type == EP_TYPE_ISOC, __LL_USB_EPx_RXISO_En(Instance), __LL_USB_EPx_RXISO_Dis(Instance));
        }

    } else {

        if (ep_cfg->ep_dir == EP_DIR_OUT) {
            __LL_USB_EPx_TXMaxPayload_Set(Instance, 0x00);
            __LL_USB_EPx_TXISO_Dis(Instance);
        } else {
            __LL_USB_EPx_RXMaxPayload_Set(Instance, 0x00);
            __LL_USB_EPx_RXISO_Dis(Instance);
        }
    }

    //USB Endpoint Interrupt Config
    USB_EpIntCfg(Instance, ep_cfg->ep_num, ep_cfg->ep_dir, ep_en);

    //USB Endpoint Maximum Packet Size Config
    USB_EpMaxPktSizeCfg(Instance, ep_cfg->ep_dir, ep_en ? ep_cfg->ep_max_pl : 0);

    return LL_OK;
}

/**
  * @brief  LL USB Endpoint FIFO Flush
  * @param  Instance Specifies USB peripheral
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @param  ep_dir USB_EpDirETypeDef Type Endpoint Direction
  * @return LL Status
  */
LL_StatusETypeDef LL_USB_EpFIFOFlush(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, USB_EpDirETypeDef ep_dir)
{
    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));
    assert_param(ep_num < EP_NUMS);

    if (!IS_USB_ALL_INSTANCE(Instance) || ep_num >= EP_NUMS) {
        return LL_INVALID;
    }

    //USB Endpoint Index Set
    __LL_USB_EPIndex_Set(Instance, ep_num);

    //Endpoint FIFO Flush
    if (ep_num == EP_NUM_0) {
        if ((ep_dir == EP_DIR_OUT && __LL_USB_EP0_IsTXPktRdy(Instance)) ||
            (ep_dir == EP_DIR_IN && __LL_USB_EP0_IsRXPktRdy(Instance))) {
            __LL_USB_EP0_FlushFIFO(Instance);
            return LL_OK;
        }
    } else {
        if (ep_dir == EP_DIR_OUT && __LL_USB_EPx_IsTXPktRdy(Instance)) {
            __LL_USB_EPx_TXFlushFIFO(Instance);
            return LL_OK;
        } else if (ep_dir == EP_DIR_IN && __LL_USB_EPx_IsRXPktRdy(Instance)) {
            __LL_USB_EPx_RXFlushFIFO(Instance);
            return LL_OK;
        }
    }

    return LL_FAILED;
}

/**
  * @brief  LL USB Read Chunk Data from Endpoint Rx FIFO
  * @param  Instance Specifies USB peripheral
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @param  buf The Read Buffer Pointer
  * @param  len Read Data Length in byte unit
  * @return The Data Length that Read Success in byte unit
  */
uint32_t LL_USB_EpFIFORead(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, uint8_t *buf, uint32_t len)
{
    uint32_t i, rx_cnt, read_len;

    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));
    assert_param(ep_num < EP_NUMS);
    assert_param(!len || buf != NULL);

    if (!IS_USB_ALL_INSTANCE(Instance) || ep_num >= EP_NUMS || (len && buf == NULL)) {
        return 0;
    }

    //USB Endpoint Index Set
    __LL_USB_EPIndex_Set(Instance, ep_num);

    //Check Read Data Lengh
    rx_cnt = __LL_USB_RXCount_Get(Instance);
    read_len = LL_MIN(rx_cnt, len);

    //USB Endpoint Read Data
    for (i = 0; i < read_len; i++) {
        buf[i] = __LL_USB_EPFIFOReadByte(Instance, ep_num);
    }

    //Read End, Clear FIFO/RxPktRdy
    if (read_len >= rx_cnt) {
        if (ep_num == EP_NUM_0) {
            __LL_USB_EP0_FlushFIFO(Instance);
            __LL_USB_EP0_RXPktRdy_Clr(Instance);
        } else {
            __LL_USB_EPx_RXFlushFIFO(Instance);
            __LL_USB_EPx_RXPktRdy_Clr(Instance);
        }
    }

    return read_len;
}

/**
  * @brief  LL USB Write Chunk Data to Endpoint Tx FIFO
  * @param  Instance Specifies USB peripheral
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @param  buf The Write Buffer Pointer
  * @param  len Write Data Length in byte unit
  * @return The Data Length that Write Success in byte unit
  */
uint32_t LL_USB_EpFIFOWrite(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, uint8_t *buf, uint32_t len)
{
    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));
    assert_param(ep_num < EP_NUMS);
    assert_param(!len || buf != NULL);

    if (!IS_USB_ALL_INSTANCE(Instance) || ep_num >= EP_NUMS || (len && buf == NULL)) {
        return 0;
    }

    //USB Endpoint Index Set
    __LL_USB_EPIndex_Set(Instance, ep_num);

    //USB Endpoint Write Data
    for (uint32_t i = 0; i < len; i++) {
        __LL_USB_EPFIFOWriteByte(Instance, ep_num, buf[i]);
    }

    //USB Valid Buffer To Transfer
    if (ep_num == EP_NUM_0) {
        __LL_USB_EP0_TXPktRdy_Set(Instance);
    } else {
        __LL_USB_EPx_TXPktRdy_Set(Instance);
    }

    return len;
}


/** @defgroup USB_LL_Exported_Functions_Group3 USB Setup Operation Functions
  * @brief    USB Setup Operation Functions
  * @{
  */

/**
  * @brief  LL USB Setup Stall Set
  * @param  Instance Specifies USB peripheral
  * @return None
  */
void LL_USB_SetupStallSet(USB_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (!IS_USB_ALL_INSTANCE(Instance)) {
        return;
    }

    __LL_USB_EP0_DataEnd_Set(Instance);
    __LL_USB_EP0_SendStall_Set(Instance);
}

/**
  * @brief  LL USB Setup Stall Clear
  * @param  Instance Specifies USB peripheral
  * @return None
  */
void LL_USB_SetupStallClr(USB_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (!IS_USB_ALL_INSTANCE(Instance)) {
        return;
    }

    //Sent Stall Clear
    __LL_USB_EP0_SentStall_Clr(Instance);
}

/**
  * @brief  LL USB Setup Data End Set
  * @param  Instance Specifies USB peripheral
  * @return None
  */
void LL_USB_SetupDataEndSet(USB_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (!IS_USB_ALL_INSTANCE(Instance)) {
        return;
    }

    //Data End Set
    __LL_USB_EP0_DataEnd_Set(Instance);
}

/**
  * @brief  LL USB Setup Address Set
  * @param  Instance Specifies USB peripheral
  * @param  addr USB Device Function Address
  * @return None
  */
void LL_USB_SetupAddrSet(USB_TypeDef *Instance, uint8_t addr)
{
    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (!IS_USB_ALL_INSTANCE(Instance)) {
        return;
    }

    //Function Address Set
    __LL_USB_FuncAddr_Set(Instance, addr);
}

/**
  * @}
  */

/**
  * @}
  */


/** @defgroup USB_LL_Exported_Functions_Interrupt USB Interrupt Handler and Callback
  * @brief    USB Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  LL USB Power IRQ Handler
  * @param  Instance Specifies USB peripheral
  * @return None
  */
void LL_USB_PowerIRQHandler(USB_TypeDef *Instance)
{
    USB_HandleTypeDef *usb_hdl;
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (!IS_USB_ALL_INSTANCE(Instance)) {
        return;
    }

    //USB handle get
    usb_hdl = USB_Handle_Get(Instance);

    if (usb_hdl == NULL) {
        LOG_E("Get USB handle error!\n");
        return;
    }

    //Get all Power Interrupt Enable and Pending
    int_en = __LL_USB_PowerAllIntEn_Get(Instance);
    int_pending = __LL_USB_PowerAllIntPending_Get(Instance);

    //Suspend Interrupt Handler
    if ((int_en & USB_USBINTREN_SUSPENDINTEN_Msk) && (int_pending & USB_USBINTR_SUSPEND_Msk)) {
        //Interrupt Pending auto clear

        //Callback
        LL_USB_PowerSuspendCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->PowerSuspend, usb_hdl->irq_cb->PowerSuspend(Instance), (void)0U);
    }

    //Resume Interrupt Handler
    if ((int_en & USB_USBINTREN_RESUMEINTEN_Msk) && (int_pending & USB_USBINTR_RESUME_Msk)) {
        //Interrupt Pending auto clear

        //Callback
        LL_USB_PowerResumeCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->PowerResume, usb_hdl->irq_cb->PowerResume(Instance), (void)0U);
    }

    //Reset Interrupt Handler
    if ((int_en & USB_USBINTREN_RESETINTEN_Msk) && (int_pending & USB_USBINTR_RESET_Msk)) {
        //Interrupt Pending auto clear

        //Callback
        LL_USB_PowerResetCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->PowerReset, usb_hdl->irq_cb->PowerReset(Instance), (void)0U);
    }

    //SOF Interrupt Handler
    if ((int_en & USB_USBINTREN_SOFINTEN_Msk) && (int_pending & USB_USBINTR_SOF_Msk)) {
        //Interrupt Pending auto clear

        //Callback
        LL_USB_PowerSOFCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->PowerSOF, usb_hdl->irq_cb->PowerSOF(Instance), (void)0U);
    }

    //Peripheral Disconnect Interrupt Handler
    if ((int_en & USB_USBINTREN_DISCONINTEN_Msk) && (int_pending & USB_USBINTR_DISCON_Msk)) {
        //Interrupt Pending auto clear

        //Callback
        LL_USB_PowerDisconnCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->PowerDisconn, usb_hdl->irq_cb->PowerDisconn(Instance), (void)0U);
    }
}

/**
  * @brief  USB Power Suspend Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_PowerSuspendCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_PowerSuspendCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Power Resume Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_PowerResumeCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_PowerResumeCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Power Reset Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_PowerResetCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_PowerResetCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Power SOF Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_PowerSOFCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_PowerSOFCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Power Peripheral Disconnect Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_PowerDisconnCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_PowerDisconnCallback could be implemented in the USB Middleware file
     */
}


/**
  * @brief  LL USB Detect IRQ Handler
  * @param  Instance Specifies USB peripheral
  * @return None
  */
void LL_USB_DetIRQHandler(USB_TypeDef *Instance)
{
    USB_HandleTypeDef *usb_hdl;

    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (!IS_USB_ALL_INSTANCE(Instance)) {
        return;
    }

    //USB handle get
    usb_hdl = USB_Handle_Get(Instance);

    if (usb_hdl == NULL) {
        LOG_E("Get USB handle error!\n");
        return;
    }

    //Insert Detect Interrupt Handler
    if (__LL_USB_IsInsertDetIntEn(Instance) && __LL_USB_IsInsertDetIntPnd(Instance)) {
        //Clear Interrupt Pending
        __LL_USB_InsertDetIntPnd_Clr(Instance);

        //Callback
        LL_USB_DetInsertCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->DetInsert, usb_hdl->irq_cb->DetInsert(Instance), (void)0U);
    }

    //Unplug Detect Interrupt Handler
    if (__LL_USB_IsUnplugDetIntEn(Instance) && __LL_USB_IsUnplugDetIntPnd(Instance)) {
        //Clear Interrupt Pending
        __LL_USB_UnplugDetIntPnd_Clr(Instance);

        //Callback
        LL_USB_DetUnplugCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->DetUnplug, usb_hdl->irq_cb->DetUnplug(Instance), (void)0U);
    }
}

/**
  * @brief  USB Detect Insert Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_DetInsertCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_DetInsertCallback could be implemented in the USB Middleware file
     */
}

/**
  * @brief  USB Detect Unplug Interrupt Callback
  * @param  Instance Specifies USB peripheral
  * @return None
  */
__WEAK void LL_USB_DetUnplugCallback(USB_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_USB_DetUnplugCallback could be implemented in the USB Middleware file
     */
}


/**
  * @brief  LL USB Endpoint IRQ Handler
  * @param  Instance Specifies USB peripheral
  * @return None
  */
void LL_USB_EpIRQHandler(USB_TypeDef *Instance)
{
    uint8_t ep_idx;
    USB_HandleTypeDef *usb_hdl;
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (!IS_USB_ALL_INSTANCE(Instance)) {
        return;
    }

    //USB handle get
    usb_hdl = USB_Handle_Get(Instance);

    if (usb_hdl == NULL) {
        LOG_E("Get USB handle error!\n");
        return;
    }

    //Get current endpoint index and save
    ep_idx = __LL_USB_EPIndex_Get(Instance);

    //Get all endpoint Interrupt Enable and Pending
    int_en = __LL_USB_EpAllIntEn_Get(Instance);
    int_pending = __LL_USB_EpAllIntPending_Get(Instance);


    //Endpoint 0 Interrupt Handler
    if ((int_en & USB_EPINTREN_EP0INTEN_Msk) && (int_pending & USB_EPINTR_EP0INT_Msk)) {
        //USB Endpoint Index Set
        __LL_USB_EPIndex_Set(Instance, EP_NUM_0);

        if (__LL_USB_IsSetupPacket(Instance) && __LL_USB_EP0_IsRXPktRdy(Instance)) {        //Endpoint 0 Setup
            LL_USB_Ep0SetupCallback(Instance);
            LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->Ep0Setup, usb_hdl->irq_cb->Ep0Setup(Instance), (void)0U);
        } else if (__LL_USB_IsInPacket(Instance)) {                                         //Endpoint 0 IN
            LL_USB_Ep0InCallback(Instance);
            LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->EpxIn[0], usb_hdl->irq_cb->EpxIn[0](Instance), (void)0U);
        } else if (__LL_USB_IsOutPacket(Instance) && __LL_USB_EP0_IsRXPktRdy(Instance)) {   //Endpoint 0 OUT
            LL_USB_Ep0OutCallback(Instance);
            LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->EpxOut[0], usb_hdl->irq_cb->EpxOut[0](Instance), (void)0U);
        }
    }

    //Endpoint 1 IN Interrupt Handler
    if ((int_en & USB_EPINTREN_EP1TXINTEN_Msk) && (int_pending & USB_EPINTR_EP1TXINT_Msk)) {
        //USB Endpoint Index Set
        __LL_USB_EPIndex_Set(Instance, EP_NUM_1);
        LL_USB_Ep1InCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->EpxIn[1], usb_hdl->irq_cb->EpxIn[1](Instance), (void)0U);
    }

    //Endpoint 2 IN Interrupt Handler
    if ((int_en & USB_EPINTREN_EP2TXINTEN_Msk) && (int_pending & USB_EPINTR_EP2TXINT_Msk)) {
        //USB Endpoint Index Set
        __LL_USB_EPIndex_Set(Instance, EP_NUM_2);
        LL_USB_Ep2InCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->EpxIn[2], usb_hdl->irq_cb->EpxIn[2](Instance), (void)0U);
    }

    //Endpoint 1 OUT Interrupt Handler
    if ((int_en & USB_EPINTREN_EP1RXINTEN_Msk) && (int_pending & USB_EPINTR_EP1RXINT_Msk)) {
        //USB Endpoint Index Set
        __LL_USB_EPIndex_Set(Instance, EP_NUM_1);
        LL_USB_Ep1OutCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->EpxOut[1], usb_hdl->irq_cb->EpxOut[1](Instance), (void)0U);
    }

    //Endpoint 2 OUT Interrupt Handler
    if ((int_en & USB_EPINTREN_EP2RXINTEN_Msk) && (int_pending & USB_EPINTR_EP2RXINT_Msk)) {
        //USB Endpoint Index Set
        __LL_USB_EPIndex_Set(Instance, EP_NUM_2);
        LL_USB_Ep2OutCallback(Instance);
        LL_FUNC_ALTER(usb_hdl->irq_cb && usb_hdl->irq_cb->EpxOut[2], usb_hdl->irq_cb->EpxOut[2](Instance), (void)0U);
    }


    //USB Endpoint Index Restore
    __LL_USB_EPIndex_Set(Instance, ep_idx);
}

/**
  * @brief  USB Endpoint 0 Setup Interrupt Callback
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
  * @brief  USB Endpoint 0 In Interrupt Callback
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
  * @brief  USB Endpoint 0 Out Interrupt Callback
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
  * @brief  USB Endpoint 1 In Interrupt Callback
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
  * @brief  USB Endpoint 1 Out Interrupt Callback
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
  * @brief  USB Endpoint 2 In Interrupt Callback
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
  * @brief  USB Endpoint 2 Out Interrupt Callback
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


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup USB_LL_Private_Functions
  * @{
  */

/**
  * @brief  USB Handle Get
  * @param  Instance Specifies USB peripheral
  * @return USB_HandleTypeDef pointer
  */
static USB_HandleTypeDef *USB_Handle_Get(USB_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (Instance == USB) {
        return &usb_hdl_global[USB_INSTANCE_0];
    }

    return NULL;
}

/**
  * @brief  USB Endpoint Maximum Packet Size Config
  * @param  Instance Specifies USB peripheral
  * @param  ep_dir USB_EpDirETypeDef Type Endpoint Direction
  * @param  ep_max_pl Endpoint maximum payload
  * @return None
  */
static void USB_EpMaxPktSizeCfg(USB_TypeDef *Instance, USB_EpDirETypeDef ep_dir, uint32_t ep_max_pl)
{
    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));

    if (!IS_USB_ALL_INSTANCE(Instance)) {
        return;
    }

    const uint16_t max_pkt_size_array[][2] = {
        { 8,   USB_EP_MAX_PKT_SIZE_8Bytes   },
        { 16,  USB_EP_MAX_PKT_SIZE_16Bytes  },
        { 32,  USB_EP_MAX_PKT_SIZE_32Bytes  },
        { 64,  USB_EP_MAX_PKT_SIZE_64Bytes  },
        { 128, USB_EP_MAX_PKT_SIZE_128Bytes },
        { 256, USB_EP_MAX_PKT_SIZE_256Bytes },
    };

    for (uint8_t i = 0; i < ARRAY_SIZE(max_pkt_size_array); i++) {
        if (max_pkt_size_array[i][0] < ep_max_pl) {
            continue;
        }

        if (ep_dir == EP_DIR_OUT) {
            __LL_USB_TxEpMaxPktSize_Set(Instance, max_pkt_size_array[i][1]);
        } else {
            __LL_USB_RxEpMaxPktSize_Set(Instance, max_pkt_size_array[i][1]);
        }

        break;
    }
}

/**
  * @brief  USB Endpoint Interrupt Config
  * @param  Instance Specifies USB peripheral
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @param  ep_dir USB_EpDirETypeDef Type Endpoint Direction
  * @param  ep_int_en Endpoint Interrrupt Enable/Disable
  * @return None
  */
__STATIC_INLINE void USB_EpIntCfg(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, USB_EpDirETypeDef ep_dir, bool ep_int_en)
{
    //Assert param
    assert_param(IS_USB_ALL_INSTANCE(Instance));
    assert_param(ep_num < EP_NUMS);

    if (!IS_USB_ALL_INSTANCE(Instance) || ep_num >= EP_NUMS) {
        return;
    }

    //Endpoint Interrupt Enable/Disable
    switch (ep_num) {
        case EP_NUM_0:
            LL_FUNC_ALTER(ep_int_en, __LL_USB_Ep0_INT_En(Instance), __LL_USB_Ep0_INT_Dis(Instance));
            break;

        case EP_NUM_1:
            if (ep_dir == EP_DIR_OUT) {
                LL_FUNC_ALTER(ep_int_en, __LL_USB_Ep1Tx_INT_En(Instance), __LL_USB_Ep1Tx_INT_Dis(Instance));
            } else {
                LL_FUNC_ALTER(ep_int_en, __LL_USB_Ep1Rx_INT_En(Instance), __LL_USB_Ep1Rx_INT_Dis(Instance));
            }

            break;

        case EP_NUM_2:
            if (ep_dir == EP_DIR_OUT) {
                LL_FUNC_ALTER(ep_int_en, __LL_USB_Ep2Tx_INT_En(Instance), __LL_USB_Ep2Tx_INT_Dis(Instance));
            } else {
                LL_FUNC_ALTER(ep_int_en, __LL_USB_Ep2Rx_INT_En(Instance), __LL_USB_Ep2Rx_INT_Dis(Instance));
            }

            break;

        default:
            LOG_E("--->%s endpoint number error: %d\n", __FUNCTION__, ep_num);
            break;
    }
}

/**
  * @}
  */


#endif  /* LL_USB_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

