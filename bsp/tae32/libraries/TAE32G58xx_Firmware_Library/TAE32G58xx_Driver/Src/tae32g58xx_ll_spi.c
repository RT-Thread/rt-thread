/**
  ******************************************************************************
  * @file    tae32g58xx_ll_spi.c
  * @author  MCD Application Team
  * @brief   SPI LL module driver
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
#include <string.h>


#define DBG_TAG             "SPI LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup SPI_LL SPI LL
  * @brief    SPI LL module driver
  * @{
  */

#ifdef LL_SPI_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/** @defgroup SPI_LL_Private_Types SPI LL Private Types
  * @brief    SPI LL Private Types
  * @{
  */

/**
  * @brief SPI IRQ callback function type definition
  */
typedef void (*SPI_LLIRQCallback)(SPI_TypeDef *Instance);

/**
  * @brief  SPI Transmission definition
  */
typedef struct __SPI_TransTypeDef {
    uint8_t *buf;                   /*!< SPI Transmission Buffer Pointer    */
    uint16_t size;                  /*!< SPI Transmission Buffer Size       */
    uint16_t cnt;                   /*!< SPI Transmission Counter           */
    SPI_LLIRQCallback isr;          /*!< Interrupt Service Routine          */
    SPI_StateETypeDef state;        /*!< SPI Transmission State             */
#ifdef LL_DMA_MODULE_ENABLED
    DMA_ChannelETypeDef dma_ch;     /*!< SPI Transmission DMA Channel       */
#endif
} SPI_TransTypeDef;

/**
  * @brief SPI handle Structure definition
  */
typedef struct __SPI_HandleTypeDef {
    SPI_RoleETypeDef role;                  /*!< SPI Role                       */

    volatile SPI_TransTypeDef tx_ctrl;      /*!< SPI Transmission Tx Control    */
    volatile SPI_TransTypeDef rx_ctrl;      /*!< SPI Transmission Rx Control    */

    SPI_UserCallbackTypeDef user_callback;  /*!< User Callback                  */
} SPI_HandleTypeDef;

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup SPI_LL_Private_Variables SPI LL Private Variables
  * @brief    SPI LL Private Variables
  * @{
  */

/**
  * @brief Default SPI LL Config
  */
static const SPI_LLCfgTypeDef spi_ll_cfg_def = {
    .wire_mode = SPI_WIRE_MODE_4,
    .cs_mode = SPI_CS_MODE_CONTINUE,
    .cs_pol = SPI_CS_POL_INACT_HIGH,
    .cs_input_mode = SPI_CS_INPUT_MODE_GPIO,
    .bit_order = SPI_BIT_ORDER_MSB,

    .cs_sw_out_en = true,
    .mosi_miso_swap_en = false,
    .tx_fifo_empty_thres = 1,   // 0~15
    .rx_fifo_full_thres = 1,    // 1~16
    .mst_rx_delay = 0,          // 0~7
    .mst_ss_idleness = 1,       //1~32
    .mst_inter_dat_idleness = 1,//1~32, while 1 means no delay

    .loopback_en = false,
};

/**
  * @brief SPI Handle global variable
  */
static SPI_HandleTypeDef spi_hdl_global[SPI_INSTANCE_NUMS];

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup SPI_LL_Private_Functions SPI LL Private Functions
  * @brief    SPI LL Private Functions
  * @{
  */
static SPI_HandleTypeDef *SPI_Handle_Get(SPI_TypeDef *Instance);

static void SPI_CloseRx_ISR(SPI_TypeDef *Instance);

static void SPI_TxISR_8BIT(SPI_TypeDef *Instance);
static void SPI_TxISR_16BIT(SPI_TypeDef *Instance);
static void SPI_RxISR_8BIT(SPI_TypeDef *Instance);
static void SPI_RxISR_16BIT(SPI_TypeDef *Instance);
static void SPI_TxDone_ISR(SPI_TypeDef *Instance);

#ifdef LL_DMA_MODULE_ENABLED
    static DMA_ChannelETypeDef SPI_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg);
    static void SPI_DMA_DeInit(DMA_ChannelETypeDef ch);
    static void SPI_DMATransmitCplt(SPI_TypeDef *Instance);
    static void SPI_DMAReceiveCplt(SPI_TypeDef *Instance);
    static void SPI_DMAHalfTransmitCplt(SPI_TypeDef *Instance);
    static void SPI_DMAHalfReceiveCplt(SPI_TypeDef *Instance);
    static void SPI_DMATransmitError(SPI_TypeDef *Instance);
    static void SPI_DMAReceiveError(SPI_TypeDef *Instance);
#endif
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup SPI_LL_Exported_Functions SPI LL Exported Functions
  * @brief    SPI LL Exported Functions
  * @{
  */

/** @defgroup SPI_LL_Exported_Functions_Group1 SPI Init and DeInit Function
  * @brief    SPI Init and DeInit function
  * @{
  */

/**
  * @brief  SPI LL Init
  * @param  Instance Specifies SPI peripheral
  * @param  user_cfg SPI User Config Pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_SPI_Init(SPI_TypeDef *Instance, SPI_UserCfgTypeDef *user_cfg)
{
    SPI_HandleTypeDef *spi_hdl;
    SPI_LLCfgTypeDef *ll_cfg;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));
    assert_param(user_cfg != NULL);
    assert_param(user_cfg->baudrate);

    if (!IS_SPI_ALL_INSTANCE(Instance) || user_cfg == NULL || !user_cfg->baudrate) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    } else if (spi_hdl->tx_ctrl.state != SPI_STATE_RESET || spi_hdl->rx_ctrl.state != SPI_STATE_RESET) {
        LOG_E("This SPI[0x%08" PRIx32 "] is being used!\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    spi_hdl->tx_ctrl.state = SPI_STATE_BUSY;
    spi_hdl->rx_ctrl.state = SPI_STATE_BUSY;

    //LL config pointer config
    LL_FUNC_ALTER(user_cfg->ll_cfg == NULL, ll_cfg = (SPI_LLCfgTypeDef *)&spi_ll_cfg_def, ll_cfg = user_cfg->ll_cfg);

    /* Init the low level hardware eg. Clock, NVIC */
    LL_SPI_MspInit(Instance);
    __LL_SPI_CS_SwOut_Inactive(Instance);

    //Module disable and TX/RX FIFO reset
    __LL_SPI_Dis(Instance);
    __LL_SPI_TxFIFO_Reset(Instance);
    __LL_SPI_RxFIFO_Reset(Instance);

    //LL Config
    __LL_SPI_WireMode_Set(Instance, ll_cfg->wire_mode);
    __LL_SPI_CSMode_Set(Instance, ll_cfg->cs_mode);
    __LL_SPI_CSPol_Set(Instance, ll_cfg->cs_pol);
    __LL_SPI_BitOrder_Set(Instance, ll_cfg->bit_order);
    __LL_SPI_TxFIFOEmptyThres_Set(Instance, ll_cfg->tx_fifo_empty_thres);
    __LL_SPI_RxFIFOFullThres_Set(Instance, ll_cfg->rx_fifo_full_thres);
    __LL_SPI_Mst_RxDelay_Set(Instance, ll_cfg->mst_rx_delay);
    __LL_SPI_CS_SlvInputMode_Set(Instance, ll_cfg->cs_input_mode);
    __LL_SPI_Mst_SSIdleness_Set(Instance, ll_cfg->mst_ss_idleness);
    __LL_SPI_Mst_InterDatIdleness_Set(Instance, ll_cfg->mst_inter_dat_idleness);
    LL_FUNC_ALTER(ll_cfg->cs_sw_out_en, __LL_SPI_CS_SwOut_En(Instance), __LL_SPI_CS_SwOut_Dis(Instance));
    LL_FUNC_ALTER(ll_cfg->mosi_miso_swap_en, __LL_SPI_MOSI_MISO_Swap_En(Instance), __LL_SPI_MOSI_MISO_Swap_Dis(Instance));

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_SPI))) {
        if ((ll_cfg->wire_mode == SPI_WIRE_MODE_4) && (__LL_SPI_WireMode_Get(Instance) == SPI_WIRE_MODE_4)) {
            LL_FUNC_ALTER(ll_cfg->loopback_en, __LL_SPI_Loopback_En(Instance), __LL_SPI_Loopback_Dis(Instance));
        } else {
            __LL_SPI_Loopback_Dis(Instance);
        }
    }

    //User Config
    __LL_SPI_Role_Set(Instance, user_cfg->role);
    __LL_SPI_SclkPhase_Set(Instance, user_cfg->sclk_phase);
    __LL_SPI_SclkPolarity_Set(Instance, user_cfg->sclk_pol);
    __LL_SPI_SerialDataLen_Set(Instance, user_cfg->data_width);
    __LL_SPI_BaudRate_Set(Instance, LL_RCU_APB1ClkGet() / user_cfg->baudrate / 2);

    //All Interrupt Pending Clear
    __LL_SPI_AllIntPnd_Clr(Instance);

    //SPI Enable
    __LL_SPI_En(Instance);

    //SPI Handle Init
    spi_hdl->role = user_cfg->role;
    spi_hdl->tx_ctrl.state = SPI_STATE_READY;
    spi_hdl->rx_ctrl.state = SPI_STATE_READY;
    spi_hdl->user_callback = user_cfg->user_callback;

    return LL_OK;
}

/**
  * @brief  SPI LL DeInit
  * @param  Instance Specifies SPI peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_SPI_DeInit(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));

    if (!IS_SPI_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    } else if (spi_hdl->tx_ctrl.state == SPI_STATE_BUSY_TX || spi_hdl->rx_ctrl.state == SPI_STATE_BUSY_RX) {
        LOG_E("This SPI[0x%08" PRIx32 "] is being used!\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    spi_hdl->tx_ctrl.state = SPI_STATE_BUSY;
    spi_hdl->rx_ctrl.state = SPI_STATE_BUSY;

    //Module disable
    __LL_SPI_Dis(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_SPI_MspDeInit(Instance);

    memset((void *)spi_hdl, 0, sizeof(SPI_HandleTypeDef));
    spi_hdl->tx_ctrl.state = SPI_STATE_RESET;
    spi_hdl->rx_ctrl.state = SPI_STATE_RESET;

    return LL_OK;
}

/**
  * @brief  SPI LL Reset
  * @param  Instance Specifies SPI peripheral
  * @return Status of the Reset
  */
LL_StatusETypeDef LL_SPI_Reset(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;
    IRQn_Type irq_num;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));

    if (!IS_SPI_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    irq_num = GET_SPI_IRQ_NUMBER(Instance);
    if (irq_num < 0) {
        LOG_E("SPI IRQ does not exist!\n");
        return LL_ERROR;
    }

    //Clear pending and interrupt disable
    __disable_irq();
    __LL_SPI_Dis(Instance);
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        CLEAR_BIT(Instance->INTEN, 0xfffUL);
        SET_BIT(Instance->INT, 0xfffUL);
    } else {
        CLEAR_BIT(Instance->INTEN, 0xf3fUL);
        SET_BIT(Instance->INT, 0xf3fUL);
    }
    NVIC_ClearPendingIRQ(irq_num);
    NVIC_DisableIRQ(irq_num);
    __enable_irq();

    spi_hdl->tx_ctrl.state = SPI_STATE_BUSY;
    spi_hdl->rx_ctrl.state = SPI_STATE_BUSY;

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_SPI_MspDeInit(Instance);

    memset((void *)spi_hdl, 0, sizeof(SPI_HandleTypeDef));
    spi_hdl->tx_ctrl.state = SPI_STATE_RESET;
    spi_hdl->rx_ctrl.state = SPI_STATE_RESET;

    return LL_OK;
}

/**
  * @brief  Initializes the SPI MSP
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_MspInit(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the SPI MSP
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_MspDeInit(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_MspDeInit could be implemented in the user file
     */
}

/**
  * @brief  Register an User SPI Callback
  * @note   User can register callback only in SPI Ready State
  * @param  Instance Specifies SPI peripheral
  * @param  CallbackID ID of the callback to be registered
  * @param  pCallback pointer to the Callback function
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_RegisterCallback(SPI_TypeDef *Instance, SPI_UserCallbackIdETypeDef CallbackID, SPI_UserCallback pCallback)
{
    SPI_HandleTypeDef *spi_hdl;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));

    if (!IS_SPI_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //Check callback pointer valid or not
    if (pCallback == NULL) {
        LOG_E("The callback pointer which to be registered is NULL!\n");
        return LL_INVALID;
    }

    //Register user callback
    switch (CallbackID) {
        case SPI_TX_CPLT_CB_ID:
            if (spi_hdl->tx_ctrl.state != SPI_STATE_READY) {
                LOG_E("This SPI[0x%08" PRIx32 "] Tx isn't in Ready state, can't register Tx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            spi_hdl->user_callback.TxCpltCallback = pCallback;
            break;

        case SPI_RX_CPLT_CB_ID:
            if (spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
                LOG_E("This SPI[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Rx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            spi_hdl->user_callback.RxCpltCallback = pCallback;
            break;

        case SPI_TX_HALF_CPLT_CB_ID:
            if (spi_hdl->tx_ctrl.state != SPI_STATE_READY) {
                LOG_E("This SPI[0x%08" PRIx32 "] Tx isn't in Ready state, can't register Tx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            spi_hdl->user_callback.TxHalfCpltCallback = pCallback;
            break;

        case SPI_RX_HALF_CPLT_CB_ID:
            if (spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
                LOG_E("This SPI[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Rx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            spi_hdl->user_callback.RxHalfCpltCallback = pCallback;
            break;

        case SPI_ERROR_CB_ID:
            if (spi_hdl->tx_ctrl.state != SPI_STATE_READY || spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
                LOG_E("This SPI[0x%08" PRIx32 "] Tx&Rx are both not in Ready state, can't register Error callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            spi_hdl->user_callback.ErrorCallback = pCallback;
            break;

        default:
            LOG_E("SPI user callback ID-[%d] is Invalid!\n", CallbackID);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @brief  UnRegister an User SPI Callback
  * @note   User can unregister callback only in SPI Ready State
  * @param  Instance Specifies SPI peripheral
  * @param  CallbackID ID of the callback to be unregistered
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_UnRegisterCallback(SPI_TypeDef *Instance, SPI_UserCallbackIdETypeDef CallbackID)
{
    SPI_HandleTypeDef *spi_hdl;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));

    if (!IS_SPI_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //UnRegister user callback
    switch (CallbackID) {
        case SPI_TX_CPLT_CB_ID:
            if (spi_hdl->tx_ctrl.state != SPI_STATE_READY) {
                LOG_E("This SPI[0x%08" PRIx32 "] Tx isn't in Ready state, can't unregister Tx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            spi_hdl->user_callback.TxCpltCallback = NULL;
            break;

        case SPI_RX_CPLT_CB_ID:
            if (spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
                LOG_E("This SPI[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Rx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            spi_hdl->user_callback.RxCpltCallback = NULL;
            break;

        case SPI_TX_HALF_CPLT_CB_ID:
            if (spi_hdl->tx_ctrl.state != SPI_STATE_READY) {
                LOG_E("This SPI[0x%08" PRIx32 "] Tx isn't in Ready state, can't unregister Tx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            spi_hdl->user_callback.TxHalfCpltCallback = NULL;
            break;

        case SPI_RX_HALF_CPLT_CB_ID:
            if (spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
                LOG_E("This SPI[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Rx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            spi_hdl->user_callback.RxHalfCpltCallback = NULL;
            break;

        case SPI_ERROR_CB_ID:
            if (spi_hdl->tx_ctrl.state != SPI_STATE_READY || spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
                LOG_E("This SPI[0x%08" PRIx32 "] Tx&Rx are both not in Ready state, can't unregister Error callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            spi_hdl->user_callback.ErrorCallback = NULL;
            break;

        default:
            LOG_E("SPI user callback ID-[%d] is Invalid!\n", CallbackID);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup SPI_LL_Exported_Functions_Group2 SPI Read Write Functions
  * @brief    SPI Read Write Functions
  * @{
  */

/**
  * @brief  Transmit an amount of data in CPU blocking mode
  * @param  Instance Specifies SPI peripheral
  * @param  buf  transmit buffer pointer
  * @param  size amount of data to be sent
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_Transmit_CPU(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    SPI_HandleTypeDef *spi_hdl;
    SPI_DataWidthETypeDef data_width;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_SPI_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //Tx/Rx State check
    if (spi_hdl->role == SPI_ROLE_MASTER) {
        if (spi_hdl->tx_ctrl.state != SPI_STATE_READY || spi_hdl->rx_ctrl.state == SPI_STATE_BUSY_RX) {
            LOG_E("This SPI[0x%08" PRIx32 "] Tx isn't in READY state or Rx is Ongoing, can't start transmit!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    } else {
        if (spi_hdl->tx_ctrl.state != SPI_STATE_READY) {
            LOG_E("This SPI[0x%08" PRIx32 "] Tx isn't in READY state, can't start transmit!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    }

    //Transmit config
    spi_hdl->tx_ctrl.state = SPI_STATE_BUSY_TX;
    spi_hdl->tx_ctrl.buf = buf;
    spi_hdl->tx_ctrl.size = size;
    spi_hdl->tx_ctrl.cnt = 0;
    spi_hdl->tx_ctrl.isr = NULL;

    //Tx Enable, Start transmit
    __LL_SPI_Tx_En(Instance);
    __LL_SPI_TxFIFO_Reset(Instance);
    __LL_SPI_TxDoneIntPnd_Clr(Instance);
    __LL_SPI_Mst_TxRxCnt_Set(Instance, size);
    __LL_SPI_Mst_TxRx_Start(Instance);
    data_width = (SPI_DataWidthETypeDef)__LL_SPI_SerialDataLen_Get(Instance);
    tickstart = LL_GetTick();

    //Transmit loop
    while (spi_hdl->tx_ctrl.cnt < spi_hdl->tx_ctrl.size) {
        //if CPU has been broken a long time by Interrupt, the TxDone flag maybe set
        if (__LL_SPI_IsTxDoneIntPnd(Instance)) {
            __LL_SPI_TxDoneIntPnd_Clr(Instance);
        }

        //Wait TxFIFO to be not full
        while (__LL_SPI_IsTxFIFOFull(Instance)) {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                ret = LL_TIMEOUT;
                goto exit;
            }
        }

        //Write data to TxFIFO
        if (data_width <= SPI_DATA_WIDTH_8BIT) {    //Transmit data in 8 Bit mode
            __LL_SPI_DAT_Write(Instance, *spi_hdl->tx_ctrl.buf);
            spi_hdl->tx_ctrl.buf++;
        } else {                                    //Transmit data in 16 Bit mode
            __LL_SPI_DAT_Write(Instance, *(uint16_t *)spi_hdl->tx_ctrl.buf);
            spi_hdl->tx_ctrl.buf += 2;
        }

        spi_hdl->tx_ctrl.cnt++;
    }

    //Wait for transmit complete
    while (!__LL_SPI_IsTxDoneIntPnd(Instance)) {
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            LOG_E("<%s> timeout!\n", __FUNCTION__);
            ret = LL_TIMEOUT;
            goto exit;
        }
    }

    //Clear TX Done Pending
    __LL_SPI_TxDoneIntPnd_Clr(Instance);

    ret = LL_OK;

exit:
    //Stop transmit and Tx Disable
    __LL_SPI_Mst_TxRx_Stop(Instance);
    __LL_SPI_Tx_Dis(Instance);
    spi_hdl->tx_ctrl.state = SPI_STATE_READY;

    return ret;
}

/**
  * @brief  Receive an amount of data in CPU blocking mode
  * @param  Instance Specifies SPI peripheral
  * @param  buf  Receive buffer pointer
  * @param  size amount of data to be received
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_Receive_CPU(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    SPI_HandleTypeDef *spi_hdl;
    SPI_DataWidthETypeDef data_width;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_SPI_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //Tx/Rx State check
    if (spi_hdl->role == SPI_ROLE_MASTER) {
        if (spi_hdl->rx_ctrl.state != SPI_STATE_READY || spi_hdl->tx_ctrl.state == SPI_STATE_BUSY_TX) {
            LOG_E("This SPI[0x%08" PRIx32 "] Rx isn't in READY state or Tx is Ongoing, can't start receive!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    } else {
        if (spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
            LOG_E("This SPI[0x%08" PRIx32 "] Rx isn't in READY state, can't start receive!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    }

    //Receive config
    spi_hdl->rx_ctrl.state = SPI_STATE_BUSY_RX;
    spi_hdl->rx_ctrl.buf = buf;
    spi_hdl->rx_ctrl.size = size;
    spi_hdl->rx_ctrl.cnt = 0;
    spi_hdl->rx_ctrl.isr = NULL;

    //Rx Enable and Start receive
    __LL_SPI_Rx_En(Instance);
    __LL_SPI_RxFIFO_Reset(Instance);
    __LL_SPI_RxDoneIntPnd_Clr(Instance);
    __LL_SPI_Mst_TxRxCnt_Set(Instance, size);
    __LL_SPI_Mst_TxRx_Start(Instance);
    data_width = (SPI_DataWidthETypeDef)__LL_SPI_SerialDataLen_Get(Instance);
    tickstart = LL_GetTick();

    //Receive loop
    while (spi_hdl->rx_ctrl.cnt < spi_hdl->rx_ctrl.size) {
        //Wait RxFIFO to be not empty
        while (__LL_SPI_IsRxFIFOEmpty(Instance)) {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                ret = LL_TIMEOUT;
                goto exit;
            }
        }

        //Read data from RxFIFO
        if (data_width <= SPI_DATA_WIDTH_8BIT) {    //Receive data in 8 Bit mode
            *spi_hdl->rx_ctrl.buf = (uint8_t)__LL_SPI_DAT_Read(Instance);
            spi_hdl->rx_ctrl.buf++;
        } else {                                    //Receive data in 16 Bit mode
            *(uint16_t *)spi_hdl->rx_ctrl.buf = (uint16_t)__LL_SPI_DAT_Read(Instance);
            spi_hdl->rx_ctrl.buf += 2;
        }

        spi_hdl->rx_ctrl.cnt++;
    }

    //Clear RX Done Pending
    if (__LL_SPI_IsRxDoneIntPnd(Instance)) {
        __LL_SPI_RxDoneIntPnd_Clr(Instance);
    }

    ret = LL_OK;

exit:
    //Stop receive and Rx Disable
    __LL_SPI_Mst_TxRx_Stop(Instance);
    __LL_SPI_Rx_Dis(Instance);
    spi_hdl->rx_ctrl.state = SPI_STATE_READY;

    return ret;
}

/**
  * @brief  Transmit and Receive an amount of data in Full Duplex CPU blocking mode
  * @param  Instance Specifies SPI peripheral
  * @param  tx_buf  transmit buffer pointer
  * @param  rx_buf  receive buffer pointer
  * @param  size    amount of data to be sent/received
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_TransmitReceive_CPU(SPI_TypeDef *Instance, uint8_t *tx_buf, uint8_t *rx_buf,
        uint16_t size, uint32_t timeout)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    SPI_HandleTypeDef *spi_hdl;
    SPI_DataWidthETypeDef data_width;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));
    assert_param(tx_buf != NULL);
    assert_param(rx_buf != NULL);
    assert_param(size);

    if (!IS_SPI_ALL_INSTANCE(Instance) || tx_buf == NULL || rx_buf == NULL || !size) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //Tx/Rx State check
    if (spi_hdl->tx_ctrl.state != SPI_STATE_READY || spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
        LOG_E("This SPI[0x%08" PRIx32 "] Tx/Rx isn't in READY state, can't start transmit/receive!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit/receive config
    spi_hdl->tx_ctrl.state = SPI_STATE_BUSY_TX;
    spi_hdl->tx_ctrl.buf = tx_buf;
    spi_hdl->tx_ctrl.size = size;
    spi_hdl->tx_ctrl.cnt = 0;
    spi_hdl->tx_ctrl.isr = NULL;

    spi_hdl->rx_ctrl.state = SPI_STATE_BUSY_RX;
    spi_hdl->rx_ctrl.buf = rx_buf;
    spi_hdl->rx_ctrl.size = size;
    spi_hdl->rx_ctrl.cnt = 0;
    spi_hdl->rx_ctrl.isr = NULL;

    //Tx/Rx Enable and Start transmit
    __LL_SPI_Tx_En(Instance);
    __LL_SPI_Rx_En(Instance);
    __LL_SPI_TxFIFO_Reset(Instance);
    __LL_SPI_RxFIFO_Reset(Instance);
    __LL_SPI_TxDoneIntPnd_Clr(Instance);
    __LL_SPI_RxDoneIntPnd_Clr(Instance);
    __LL_SPI_Mst_TxRxCnt_Set(Instance, size);
    __LL_SPI_Mst_TxRx_Start(Instance);
    data_width = (SPI_DataWidthETypeDef)__LL_SPI_SerialDataLen_Get(Instance);
    tickstart = LL_GetTick();

    //Transmit/receive loop
    while (spi_hdl->tx_ctrl.cnt < spi_hdl->tx_ctrl.size || spi_hdl->rx_ctrl.cnt < spi_hdl->rx_ctrl.size) {
        //if CPU has been broken a long time by Interrupt, the TxDone flag maybe set
        if (__LL_SPI_IsTxDoneIntPnd(Instance)) {
            __LL_SPI_TxDoneIntPnd_Clr(Instance);
        }

        //Wait TxFIFO to be not full
        if (!__LL_SPI_IsTxFIFOFull(Instance) && spi_hdl->tx_ctrl.cnt < spi_hdl->tx_ctrl.size) {
            if (data_width <= SPI_DATA_WIDTH_8BIT) {    //Transmit data in 8 Bit mode
                __LL_SPI_DAT_Write(Instance, *spi_hdl->tx_ctrl.buf);
                spi_hdl->tx_ctrl.buf++;
            } else {                                    //Transmit data in 16 Bit mode
                __LL_SPI_DAT_Write(Instance, *(uint16_t *)spi_hdl->tx_ctrl.buf);
                spi_hdl->tx_ctrl.buf += 2;
            }

            spi_hdl->tx_ctrl.cnt++;
        }

        //Read data from RxFIFO
        if (!__LL_SPI_IsRxFIFOEmpty(Instance) && spi_hdl->rx_ctrl.cnt < spi_hdl->rx_ctrl.size) {
            if (data_width <= SPI_DATA_WIDTH_8BIT) {    //Receive data in 8 Bit mode
                *spi_hdl->rx_ctrl.buf = (uint8_t)__LL_SPI_DAT_Read(Instance);
                spi_hdl->rx_ctrl.buf++;
            } else {                                    //Receive data in 16 Bit mode
                *(uint16_t *)spi_hdl->rx_ctrl.buf = (uint16_t)__LL_SPI_DAT_Read(Instance);
                spi_hdl->rx_ctrl.buf += 2;
            }

            spi_hdl->rx_ctrl.cnt++;
        }

        //Check whether operation timeout or not
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            LOG_E("<%s> timeout!\n", __FUNCTION__);
            LOG_E("Can't send or receive Within a predetermined time!\n");
            LOG_E("It has sent %d numbers data!\n", spi_hdl->tx_ctrl.cnt);
            LOG_E("It has received %d numbers data!\n", spi_hdl->rx_ctrl.cnt);
            ret = LL_TIMEOUT;
            goto exit;
        }
    }

    //Clear TX Done Pending
    if (__LL_SPI_IsTxDoneIntPnd(Instance)) {
        __LL_SPI_TxDoneIntPnd_Clr(Instance);
    }

    //Clear RX Done Pending
    if (__LL_SPI_IsRxDoneIntPnd(Instance)) {
        __LL_SPI_RxDoneIntPnd_Clr(Instance);
    }

    ret = LL_OK;

exit:
    //Stop transmit/receive and Tx/Rx Disable
    __LL_SPI_Mst_TxRx_Stop(Instance);
    __LL_SPI_Tx_Dis(Instance);
    __LL_SPI_Rx_Dis(Instance);
    spi_hdl->tx_ctrl.state = SPI_STATE_READY;
    spi_hdl->rx_ctrl.state = SPI_STATE_READY;

    return ret;
}

/**
  * @brief  Transmit an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies SPI peripheral
  * @param  buf  transmit buffer pointer
  * @param  size amount of data to be sent
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_Transmit_IT(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size)
{
    SPI_HandleTypeDef *spi_hdl;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_SPI_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //Tx/Rx State check
    if (spi_hdl->role == SPI_ROLE_MASTER) {
        if (spi_hdl->tx_ctrl.state != SPI_STATE_READY || spi_hdl->rx_ctrl.state == SPI_STATE_BUSY_RX) {
            LOG_E("This SPI[0x%08" PRIx32 "] Tx isn't in READY state or Rx is Ongoing, can't start transmit!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    } else {
        if (spi_hdl->tx_ctrl.state != SPI_STATE_READY) {
            LOG_E("This SPI[0x%08" PRIx32 "] Tx isn't in READY state, can't start transmit!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    }

    //Transmit config
    spi_hdl->tx_ctrl.state = SPI_STATE_BUSY_TX;
    spi_hdl->tx_ctrl.buf = buf;
    spi_hdl->tx_ctrl.size = size;
    spi_hdl->tx_ctrl.cnt = 0;

    if ((SPI_DataWidthETypeDef)__LL_SPI_SerialDataLen_Get(Instance) <= SPI_DATA_WIDTH_8BIT) {   //Transmit data in 8 Bit mode
        spi_hdl->tx_ctrl.isr = SPI_TxISR_8BIT;
    } else {                                                                                    //Transmit data in 16 Bit mode
        spi_hdl->tx_ctrl.isr = SPI_TxISR_16BIT;
    }

    //Tx Enable and Start transmit
    __LL_SPI_Tx_En(Instance);
    __LL_SPI_TxFIFO_Reset(Instance);
    __LL_SPI_TxDoneIntPnd_Clr(Instance);
    __LL_SPI_Mst_TxRxCnt_Set(Instance, size);
    __LL_SPI_Mst_TxRx_Start(Instance);

    //Enable TxFIFO Empty interrupt
    __LL_SPI_TxFIFOEmpty_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies SPI peripheral
  * @param  buf  receive buffer pointer
  * @param  size amount of data to be received
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_Receive_IT(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size)
{
    SPI_HandleTypeDef *spi_hdl;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_SPI_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //Tx/Rx State check
    if (spi_hdl->role == SPI_ROLE_MASTER) {
        if (spi_hdl->rx_ctrl.state != SPI_STATE_READY || spi_hdl->tx_ctrl.state == SPI_STATE_BUSY_TX) {
            LOG_E("This SPI[0x%08" PRIx32 "] Rx isn't in READY state or Tx is Ongoing, can't start receive!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    } else {
        if (spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
            LOG_E("This SPI[0x%08" PRIx32 "] Rx isn't in READY state, can't start receive!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    }

    //Receive config
    spi_hdl->rx_ctrl.state = SPI_STATE_BUSY_RX;
    spi_hdl->rx_ctrl.buf = buf;
    spi_hdl->rx_ctrl.size = size;
    spi_hdl->rx_ctrl.cnt = 0;

    if ((SPI_DataWidthETypeDef)__LL_SPI_SerialDataLen_Get(Instance) <= SPI_DATA_WIDTH_8BIT) {   //Receive data in 8 Bit mode
        spi_hdl->rx_ctrl.isr = SPI_RxISR_8BIT;
    } else {                                                                                    //Receive data in 16 Bit mode
        spi_hdl->rx_ctrl.isr = SPI_RxISR_16BIT;
    }

    //Rx Enable and Start receive
    __LL_SPI_Rx_En(Instance);
    __LL_SPI_RxFIFO_Reset(Instance);
    __LL_SPI_RxDoneIntPnd_Clr(Instance);
    __LL_SPI_Mst_TxRxCnt_Set(Instance, size);
    __LL_SPI_Mst_TxRx_Start(Instance);

    //Enable RxFIFO Full interrupt
    __LL_SPI_RxFIFOFull_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  Transmit and Receive an amount of data in Full Duplex non-blocking mode with Interrupt
  * @param  Instance Specifies SPI peripheral
  * @param  tx_buf  transmit buffer pointer
  * @param  rx_buf  receive buffer pointer
  * @param  size    amount of data to be sent/received
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_TransmitReceive_IT(SPI_TypeDef *Instance, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size)
{
    SPI_HandleTypeDef *spi_hdl;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));
    assert_param(tx_buf != NULL);
    assert_param(rx_buf != NULL);
    assert_param(size);

    if (!IS_SPI_ALL_INSTANCE(Instance) || tx_buf == NULL || rx_buf == NULL || !size) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //Tx/Rx State check
    if (spi_hdl->tx_ctrl.state != SPI_STATE_READY || spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
        LOG_E("This SPI[0x%08" PRIx32 "] Tx/Rx isn't in READY state, can't start transmit/receive!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit/receive config
    spi_hdl->tx_ctrl.state = SPI_STATE_BUSY_TX;
    spi_hdl->tx_ctrl.buf = tx_buf;
    spi_hdl->tx_ctrl.size = size;
    spi_hdl->tx_ctrl.cnt = 0;

    spi_hdl->rx_ctrl.state = SPI_STATE_BUSY_RX;
    spi_hdl->rx_ctrl.buf = rx_buf;
    spi_hdl->rx_ctrl.size = size;
    spi_hdl->rx_ctrl.cnt = 0;

    if ((SPI_DataWidthETypeDef)__LL_SPI_SerialDataLen_Get(Instance) <= SPI_DATA_WIDTH_8BIT) {   //Transmit/Receive data in 8 Bit mode
        spi_hdl->tx_ctrl.isr = SPI_TxISR_8BIT;
        spi_hdl->rx_ctrl.isr = SPI_RxISR_8BIT;
    } else {                                                                                    //Transmit/Receive data in 16 Bit mode
        spi_hdl->tx_ctrl.isr = SPI_TxISR_16BIT;
        spi_hdl->rx_ctrl.isr = SPI_RxISR_16BIT;
    }

    //Tx/Rx Enable and Start transmit
    __LL_SPI_Tx_En(Instance);
    __LL_SPI_Rx_En(Instance);
    __LL_SPI_TxFIFO_Reset(Instance);
    __LL_SPI_RxFIFO_Reset(Instance);
    __LL_SPI_TxDoneIntPnd_Clr(Instance);
    __LL_SPI_RxDoneIntPnd_Clr(Instance);
    __LL_SPI_Mst_TxRxCnt_Set(Instance, size);
    __LL_SPI_Mst_TxRx_Start(Instance);

    //Enable RxFIFO Full interrupt
    __LL_SPI_RxFIFOFull_INT_En(Instance);

    //Enable TxFIFO Empty interrupt last
    __LL_SPI_TxFIFOEmpty_INT_En(Instance);

    return LL_OK;
}

#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  Transmit an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies SPI peripheral
  * @param  buf  transmit buffer pointer
  * @param  size amount of data to be sent
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_Transmit_DMA(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size)
{
    uint32_t dma_size;
    SPI_HandleTypeDef *spi_hdl;
    DMA_UserCfgTypeDef dma_user_cfg;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_SPI_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //Tx/Rx State check
    if (spi_hdl->role == SPI_ROLE_MASTER) {
        if (spi_hdl->tx_ctrl.state != SPI_STATE_READY || spi_hdl->rx_ctrl.state == SPI_STATE_BUSY_RX) {
            LOG_E("This SPI[0x%08" PRIx32 "] Tx isn't in READY state or Rx is Ongoing, can't start transmit!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    } else {
        if (spi_hdl->tx_ctrl.state != SPI_STATE_READY) {
            LOG_E("This SPI[0x%08" PRIx32 "] Tx isn't in READY state, can't start transmit!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    }

    //DMA Init
    memset((void *)&dma_user_cfg, 0x0, sizeof(dma_user_cfg));

    if ((SPI_DataWidthETypeDef)__LL_SPI_SerialDataLen_Get(Instance) <= SPI_DATA_WIDTH_8BIT) {   //Transmit data in 8 Bit mode
        dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
        dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;
        dma_size = size;
    } else {                                                                                    //Transmit data in 16 Bit mode
        dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_16b;
        dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_16b;
        dma_size = size * 2;
    }

    dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_FIX;
    dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == SPI0) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_SPI0_TX;
    } else if (Instance == SPI1) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_SPI1_TX;
    } else {
        LOG_E("SPI DMA destination handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Transmit Default Config
    dma_user_cfg.trans_type = DMA_TRANS_TYPE_M2P;
    dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_INC;
    dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    dma_user_cfg.end_callback = (DMA_IRQCallback)SPI_DMATransmitCplt;
    dma_user_cfg.end_arg = Instance;
    dma_user_cfg.err_callback = (DMA_IRQCallback)SPI_DMATransmitError;
    dma_user_cfg.err_arg = Instance;
    dma_user_cfg.half_callback = (DMA_IRQCallback)SPI_DMAHalfTransmitCplt;
    dma_user_cfg.half_arg = Instance;

    spi_hdl->tx_ctrl.dma_ch = SPI_DMA_Init(&dma_user_cfg);

    if (spi_hdl->tx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("SPI transmit request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Transmit config
    spi_hdl->tx_ctrl.state = SPI_STATE_BUSY_TX;
    spi_hdl->tx_ctrl.buf = buf;
    spi_hdl->tx_ctrl.size = dma_size;
    spi_hdl->tx_ctrl.cnt = 0;
    spi_hdl->tx_ctrl.isr = NULL;

    //Enable Tx DMA Requset
    __LL_SPI_TxDMA_En(Instance);

    //Tx Enable and Start transmit
    __LL_SPI_Tx_En(Instance);
    __LL_SPI_TxFIFO_Reset(Instance);
    __LL_SPI_TxDoneIntPnd_Clr(Instance);
    __LL_SPI_Mst_TxRxCnt_Set(Instance, size);
    __LL_SPI_Mst_TxRx_Start(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, spi_hdl->tx_ctrl.dma_ch, (uint32_t)buf, (uint32_t)&Instance->TDR, dma_size);

    return LL_OK;
}

/**
  * @brief  Receive an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies SPI peripheral
  * @param  buf  receive buffer pointer
  * @param  size amount of data to be received
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_Receive_DMA(SPI_TypeDef *Instance, uint8_t *buf, uint16_t size)
{
    uint32_t dma_size;
    SPI_HandleTypeDef *spi_hdl;
    DMA_UserCfgTypeDef dma_user_cfg;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));
    assert_param(buf != NULL);
    assert_param(size);

    if (!IS_SPI_ALL_INSTANCE(Instance) || buf == NULL || !size) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //Tx/Rx State check
    if (spi_hdl->role == SPI_ROLE_MASTER) {
        if (spi_hdl->rx_ctrl.state != SPI_STATE_READY || spi_hdl->tx_ctrl.state == SPI_STATE_BUSY_TX) {
            LOG_E("This SPI[0x%08" PRIx32 "] Rx isn't in READY state or Tx is Ongoing, can't start receive!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    } else {
        if (spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
            LOG_E("This SPI[0x%08" PRIx32 "] Rx isn't in READY state, can't start receive!\n", (uint32_t)Instance);
            return LL_FAILED;
        }
    }

    //DMA Init
    memset((void *)&dma_user_cfg, 0x0, sizeof(dma_user_cfg));

    if ((SPI_DataWidthETypeDef)__LL_SPI_SerialDataLen_Get(Instance) <= SPI_DATA_WIDTH_8BIT) {   //Transmit data in 8 Bit mode
        dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
        dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;
        dma_size = size;
    } else {                                                                                    //Transmit data in 16 Bit mode
        dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_16b;
        dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_16b;
        dma_size = size * 2;
    }

    dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_FIX;
    dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == SPI0) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_SPI0_RX;
    } else if (Instance == SPI1) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_SPI1_RX;
    } else {
        LOG_E("SPI DMA source handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Receive Default Config
    dma_user_cfg.trans_type = DMA_TRANS_TYPE_P2M;
    dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_INC;
    dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    dma_user_cfg.end_callback = (DMA_IRQCallback)SPI_DMAReceiveCplt;
    dma_user_cfg.end_arg = Instance;
    dma_user_cfg.err_callback = (DMA_IRQCallback)SPI_DMAReceiveError;
    dma_user_cfg.err_arg = Instance;
    dma_user_cfg.half_callback = (DMA_IRQCallback)SPI_DMAHalfReceiveCplt;
    dma_user_cfg.half_arg = Instance;

    spi_hdl->rx_ctrl.dma_ch = SPI_DMA_Init(&dma_user_cfg);

    if (spi_hdl->rx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("SPI receive request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Receive config
    spi_hdl->rx_ctrl.state = SPI_STATE_BUSY_RX;
    spi_hdl->rx_ctrl.buf = buf;
    spi_hdl->rx_ctrl.size = dma_size;
    spi_hdl->rx_ctrl.cnt = 0;
    spi_hdl->rx_ctrl.isr = NULL;

    //Enable Rx DMA Requset
    __LL_SPI_RxDMA_En(Instance);

    //Rx Enable and Start receive
    __LL_SPI_Rx_En(Instance);
    __LL_SPI_RxFIFO_Reset(Instance);
    __LL_SPI_RxDoneIntPnd_Clr(Instance);
    __LL_SPI_Mst_TxRxCnt_Set(Instance, size);
    __LL_SPI_Mst_TxRx_Start(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, spi_hdl->rx_ctrl.dma_ch, (uint32_t)&Instance->RDR, (uint32_t)buf, dma_size);

    return LL_OK;
}

/**
  * @brief  Transmit and Receive an amount of data in Full Duplex non-blocking mode with DMA
  * @param  Instance Specifies SPI peripheral
  * @param  tx_buf  transmit buffer pointer
  * @param  rx_buf  receive buffer pointer
  * @param  size    amount of data to be sent/received
  * @return LL Status
  */
LL_StatusETypeDef LL_SPI_TransmitReceive_DMA(SPI_TypeDef *Instance, uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size)
{
    uint32_t tx_dma_size, rx_dma_size;
    SPI_HandleTypeDef *spi_hdl;
    DMA_UserCfgTypeDef tx_dma_user_cfg, rx_dma_user_cfg;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));
    assert_param(tx_buf != NULL);
    assert_param(rx_buf != NULL);
    assert_param(size);

    if (!IS_SPI_ALL_INSTANCE(Instance) || tx_buf == NULL || rx_buf == NULL || !size) {
        return LL_INVALID;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return LL_ERROR;
    }

    //Tx/Rx State check
    if (spi_hdl->tx_ctrl.state != SPI_STATE_READY || spi_hdl->rx_ctrl.state != SPI_STATE_READY) {
        LOG_E("This SPI[0x%08" PRIx32 "] Tx/Rx isn't in READY state, can't start transmit/receive!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit/Receive DMA Init
    memset((void *)&tx_dma_user_cfg, 0x0, sizeof(tx_dma_user_cfg));
    memset((void *)&rx_dma_user_cfg, 0x0, sizeof(rx_dma_user_cfg));

    if ((SPI_DataWidthETypeDef)__LL_SPI_SerialDataLen_Get(Instance) <= SPI_DATA_WIDTH_8BIT) {   //Transmit/Receive data in 8 Bit mode
        tx_dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
        tx_dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;
        rx_dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
        rx_dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;
        tx_dma_size = size;
        rx_dma_size = size;
    } else {                                                                                    //Transmit/Receive data in 16 Bit mode
        tx_dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_16b;
        tx_dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_16b;
        rx_dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_16b;
        rx_dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_16b;
        tx_dma_size = size * 2;
        rx_dma_size = size * 2;
    }

    tx_dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_FIX;
    rx_dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_FIX;
    tx_dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;
    rx_dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == SPI0) {
        tx_dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_SPI0_TX;
        rx_dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_SPI0_RX;
    } else if (Instance == SPI1) {
        tx_dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_SPI1_TX;
        rx_dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_SPI1_RX;
    } else {
        LOG_E("SPI DMA source and destination handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Transmit Default Config
    tx_dma_user_cfg.trans_type = DMA_TRANS_TYPE_M2P;
    tx_dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_INC;
    tx_dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    //DMA Receive Default Config
    rx_dma_user_cfg.trans_type = DMA_TRANS_TYPE_P2M;
    rx_dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_INC;
    rx_dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    tx_dma_user_cfg.end_callback = (DMA_IRQCallback)SPI_DMATransmitCplt;
    tx_dma_user_cfg.end_arg = Instance;
    tx_dma_user_cfg.err_callback = (DMA_IRQCallback)SPI_DMATransmitError;
    tx_dma_user_cfg.err_arg = Instance;
    tx_dma_user_cfg.half_callback = (DMA_IRQCallback)SPI_DMAHalfTransmitCplt;
    tx_dma_user_cfg.half_arg = Instance;

    rx_dma_user_cfg.end_callback = (DMA_IRQCallback)SPI_DMAReceiveCplt;
    rx_dma_user_cfg.end_arg = Instance;
    rx_dma_user_cfg.err_callback = (DMA_IRQCallback)SPI_DMAReceiveError;
    rx_dma_user_cfg.err_arg = Instance;
    rx_dma_user_cfg.half_callback = (DMA_IRQCallback)SPI_DMAHalfReceiveCplt;
    rx_dma_user_cfg.half_arg = Instance;

    spi_hdl->tx_ctrl.dma_ch = SPI_DMA_Init(&tx_dma_user_cfg);

    if (spi_hdl->tx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("SPI transmit request DMA channel Failed!\n");
        return LL_ERROR;
    }

    spi_hdl->rx_ctrl.dma_ch = SPI_DMA_Init(&rx_dma_user_cfg);

    if (spi_hdl->rx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        SPI_DMA_DeInit(spi_hdl->tx_ctrl.dma_ch);
        LOG_E("SPI receive request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Transmit/Receive config
    spi_hdl->tx_ctrl.state = SPI_STATE_BUSY_TX;
    spi_hdl->tx_ctrl.buf = tx_buf;
    spi_hdl->tx_ctrl.size = tx_dma_size;
    spi_hdl->tx_ctrl.cnt = 0;
    spi_hdl->tx_ctrl.isr = NULL;

    spi_hdl->rx_ctrl.state = SPI_STATE_BUSY_RX;
    spi_hdl->rx_ctrl.buf = rx_buf;
    spi_hdl->rx_ctrl.size = rx_dma_size;
    spi_hdl->rx_ctrl.cnt = 0;
    spi_hdl->rx_ctrl.isr = NULL;

    //Enable Tx/Rx DMA Requset
    __LL_SPI_TxDMA_En(Instance);
    __LL_SPI_RxDMA_En(Instance);

    //Tx/Rx Enable and Start transmit
    __LL_SPI_Tx_En(Instance);
    __LL_SPI_Rx_En(Instance);
    __LL_SPI_TxFIFO_Reset(Instance);
    __LL_SPI_RxFIFO_Reset(Instance);
    __LL_SPI_TxDoneIntPnd_Clr(Instance);
    __LL_SPI_RxDoneIntPnd_Clr(Instance);
    __LL_SPI_Mst_TxRxCnt_Set(Instance, size);
    __LL_SPI_Mst_TxRx_Start(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, spi_hdl->tx_ctrl.dma_ch, (uint32_t)tx_buf, (uint32_t)&Instance->TDR, tx_dma_size);
    LL_DMA_Start_IT(DMA, spi_hdl->rx_ctrl.dma_ch, (uint32_t)&Instance->RDR, (uint32_t)rx_buf, rx_dma_size);

    return LL_OK;
}

#endif

/**
  * @}
  */


/** @defgroup SPI_LL_Exported_Functions_Interrupt SPI Interrupt Handler and Callback
  * @brief    SPI Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  SPI IRQ Handler
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
void LL_SPI_IRQHandler(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));

    if (!IS_SPI_ALL_INSTANCE(Instance)) {
        return;
    }

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_SPI_AllIntEn_Get(Instance);
    int_pending = __LL_SPI_AllIntPnd_Get(Instance);


    //RxFIFO Full Interrupt Pending
    if ((int_en & SPI0_INTEN_RXFIE_Msk) && (int_pending & SPI0_INT_RXFI_Msk)) {
        //Interrupt Pending auto clear

        if (spi_hdl->rx_ctrl.isr) {
            spi_hdl->rx_ctrl.isr(Instance);
        }

        //Callback
        LL_SPI_RxFullCallback(Instance);
    }

    //TxFIFO Empty Interrupt Pending
    if ((int_en & SPI0_INTEN_TXEIE_Msk) && (int_pending & SPI0_INT_TXEI_Msk)) {
        //Interrupt Pending auto clear

        if (spi_hdl->tx_ctrl.isr) {
            spi_hdl->tx_ctrl.isr(Instance);
        }

        //Callback
        LL_SPI_TxEmptyCallback(Instance);
    }

    //RxFIFO Overflow Interrupt Pending
    if ((int_en & SPI0_INTEN_RXOFIE_Msk) && (int_pending & SPI0_INT_RXOFI_Msk)) {
        //Clear Interrupt Pending
        __LL_SPI_RxOverflowIntPnd_Clr(Instance);

        //Callback
        LL_SPI_RxOverflowCallback(Instance);
    }

    //RxFIFO Underflow Interrupt Pending
    if ((int_en & SPI0_INTEN_RXUFIE_Msk) && (int_pending & SPI0_INT_RXUFI_Msk)) {
        //Clear Interrupt Pending
        __LL_SPI_RxUnderflowIntPnd_Clr(Instance);

        //Callback
        LL_SPI_RxUnderflowCallback(Instance);
    }

    //TxFIFO Overflow Interrupt Pending
    if ((int_en & SPI0_INTEN_TXOFIE_Msk) && (int_pending & SPI0_INT_TXOFI_Msk)) {
        //Clear Interrupt Pending
        __LL_SPI_TxOverflowIntPnd_Clr(Instance);

        //Callback
        LL_SPI_TxOverflowCallback(Instance);
    }

    //Slave TxFIFO Underflow Interrupt Pending
    if ((int_en & SPI0_INTEN_TXUFIE_Msk) && (int_pending & SPI0_INT_TXUFI_Msk)) {
        //Clear Interrupt Pending
        __LL_SPI_Slv_TxUnderflowIntPnd_Clr(Instance);

        //Callback
        LL_SPI_Slv_TxUnderflowCallback(Instance);
    }

    //Tx Done Interrupt Pending
    if ((int_en & SPI0_INTEN_TXDEIE_Msk) && (int_pending & SPI0_INT_TXDEI_Msk)) {
        //Clear Interrupt Pending
        __LL_SPI_TxDoneIntPnd_Clr(Instance);

        if (spi_hdl->tx_ctrl.cnt >= spi_hdl->tx_ctrl.size && spi_hdl->tx_ctrl.isr) {
            spi_hdl->tx_ctrl.isr(Instance);
        }

        //Callback
        LL_SPI_TxDoneCallback(Instance);
    }

    //Rx Done Interrupt Pending
    if ((int_en & SPI0_INTEN_RXDEIE_Msk) && (int_pending & SPI0_INT_RXDEI_Msk)) {
        //Clear Interrupt Pending
        __LL_SPI_RxDoneIntPnd_Clr(Instance);

        //Callback
        LL_SPI_RxDoneCallback(Instance);
    }

    //Tx Complete Interrupt Pending
    if ((int_en & SPI0_INTEN_TXCIE_Msk) && (int_pending & SPI0_INT_TXCI_Msk)) {
        //Clear Interrupt Pending
        __LL_SPI_TxCpltIntPnd_Clr(Instance);

        //Callback
        LL_SPI_TxCpltCallback(Instance);
    }

    //Rx Complete Interrupt Pending
    if ((int_en & SPI0_INTEN_RXCIE_Msk) && (int_pending & SPI0_INT_RXCI_Msk)) {
        //Clear Interrupt Pending
        __LL_SPI_RxCpltIntPnd_Clr(Instance);

        //Callback
        LL_SPI_RxCpltCallback(Instance);
    }

    //The following features are available for later versions
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        return;
    }

    //Transmission Mode Fault Interrupt Pending
    if ((int_en & SPI0_INTEN_MDFIE_Msk) && (int_pending & SPI0_INT_MDFI_Msk)) {
        //Clear Interrupt Pending
        __LL_SPI_TransModeFaultIntPnd_Clr(Instance);

        //Callback
        LL_SPI_TransModeFaultCallback(Instance);
    }

    //Transmission Operation Fault Interrupt Pending
    if ((int_en & SPI0_INTEN_OPFIE_Msk) && (int_pending & SPI0_INT_OPFI_Msk)) {
        //Clear Interrupt Pending
        __LL_SPI_TransOptFaultIntPnd_Clr(Instance);

        //Callback
        LL_SPI_TransOptFaultCallback(Instance);
    }    
}

/**
  * @brief  SPI Transmission Mode Fault Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_TransModeFaultCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_TransModeFaultCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI Transmission Operation Fault Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_TransOptFaultCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_TransOptFaultCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI RxFIFO Full Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_RxFullCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_RxFullCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI TxFIFO Empty Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_TxEmptyCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_TxEmptyCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI RxFIFO Overflow Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_RxOverflowCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_RxOverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI RxFIFO Underflow Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_RxUnderflowCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_RxUnderflowCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI TxFIFO Overflow Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_TxOverflowCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_TxOverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI Slave TxFIFO Underflow Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_Slv_TxUnderflowCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_Slv_TxUnderflowCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI Tx Done Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_TxDoneCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_TxDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI Rx Done Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_RxDoneCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_RxDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI Tx Complete Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_TxCpltCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_TxCpltCallback could be implemented in the user file
     */
}

/**
  * @brief  SPI Rx Complete Interrupt Callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
__WEAK void LL_SPI_RxCpltCallback(SPI_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SPI_RxCpltCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup SPI_LL_Private_Functions
  * @{
  */

/**
  * @brief  SPI Handle Get
  * @param  Instance Specifies SPI peripheral
  * @return SPI_HandleTypeDef pointer
  */
static SPI_HandleTypeDef *SPI_Handle_Get(SPI_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_SPI_ALL_INSTANCE(Instance));

    if (Instance == SPI0) {
        return &spi_hdl_global[SPI_INSTANCE_0];
    } else if (Instance == SPI1) {
        return &spi_hdl_global[SPI_INSTANCE_1];
    }

    return NULL;
}

/**
  * @brief  Handle the data 8-bit transmit in Interrupt mode
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_TxISR_8BIT(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    //Write data to TxFIFO until full according to Slave
    while (!__LL_SPI_IsTxFIFOFull(Instance) && spi_hdl->tx_ctrl.cnt < spi_hdl->tx_ctrl.size) {
        //if TxDone flag has been set before write data to TxFIFO, clear it
        if (__LL_SPI_IsTxDoneIntPnd(Instance)) {
            __LL_SPI_TxDoneIntPnd_Clr(Instance);
        }

        __LL_SPI_DAT_Write(Instance, *spi_hdl->tx_ctrl.buf);
        spi_hdl->tx_ctrl.buf++;
        spi_hdl->tx_ctrl.cnt++;
    }

    //Tx Complete
    if (spi_hdl->tx_ctrl.cnt >= spi_hdl->tx_ctrl.size) {
        //Disable TxFIFO Empty interrupt
        __LL_SPI_TxFIFOEmpty_INT_Dis(Instance);

        //Switch isr to TxDone ISR
        spi_hdl->tx_ctrl.isr = SPI_TxDone_ISR;

        //Enable Tx Done Interrupt
        __LL_SPI_TxDone_INT_En(Instance);
    }
}

/**
  * @brief  Handle the data 16-bit transmit in Interrupt mode
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_TxISR_16BIT(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    //Write data to TxFIFO until full according to Slave
    while (!__LL_SPI_IsTxFIFOFull(Instance) && spi_hdl->tx_ctrl.cnt < spi_hdl->tx_ctrl.size) {
        //if TxDone flag has been set before write data to TxFIFO, clear it
        if (__LL_SPI_IsTxDoneIntPnd(Instance)) {
            __LL_SPI_TxDoneIntPnd_Clr(Instance);
        }

        __LL_SPI_DAT_Write(Instance, *(uint16_t *)spi_hdl->tx_ctrl.buf);
        spi_hdl->tx_ctrl.buf += 2;
        spi_hdl->tx_ctrl.cnt++;
    }

    //Tx Complete
    if (spi_hdl->tx_ctrl.cnt >= spi_hdl->tx_ctrl.size) {
        //Disable TxFIFO Empty interrupt
        __LL_SPI_TxFIFOEmpty_INT_Dis(Instance);

        //Switch isr to TxDone ISR
        spi_hdl->tx_ctrl.isr = SPI_TxDone_ISR;

        //Enable Tx Done Interrupt
        __LL_SPI_TxDone_INT_En(Instance);
    }
}

/**
  * @brief  Handle the data 8-bit receive in Interrupt mode
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_RxISR_8BIT(SPI_TypeDef *Instance)
{
    uint8_t rx_fifo_trig_lvl;
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    rx_fifo_trig_lvl = __LL_SPI_RxFIFOFullThres_Get(Instance);

    //Read data from RxFIFO
    while (rx_fifo_trig_lvl-- && spi_hdl->rx_ctrl.cnt < spi_hdl->rx_ctrl.size) {
        *spi_hdl->rx_ctrl.buf = (uint8_t)__LL_SPI_DAT_Read(Instance);
        spi_hdl->rx_ctrl.buf++;
        spi_hdl->rx_ctrl.cnt++;
    }

    //Rx Complete
    if (spi_hdl->rx_ctrl.cnt >= spi_hdl->rx_ctrl.size) {
        SPI_CloseRx_ISR(Instance);
    }
}

/**
  * @brief  Handle the data 16-bit receive in Interrupt mode
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_RxISR_16BIT(SPI_TypeDef *Instance)
{
    uint8_t rx_fifo_trig_lvl;
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    rx_fifo_trig_lvl = __LL_SPI_RxFIFOFullThres_Get(Instance);

    //Read data from RxFIFO
    while (rx_fifo_trig_lvl-- && spi_hdl->rx_ctrl.cnt < spi_hdl->rx_ctrl.size) {
        *(uint16_t *)spi_hdl->rx_ctrl.buf = (uint16_t)__LL_SPI_DAT_Read(Instance);
        spi_hdl->rx_ctrl.buf += 2;
        spi_hdl->rx_ctrl.cnt++;
    }

    //Rx Complete
    if (spi_hdl->rx_ctrl.cnt >= spi_hdl->rx_ctrl.size) {
        SPI_CloseRx_ISR(Instance);
    }
}

/**
  * @brief  SPI TxDone Interrupt Service Routine
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_TxDone_ISR(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    if (spi_hdl->tx_ctrl.cnt >= spi_hdl->tx_ctrl.size) {
        //Disable Tx Done Interrupt
        __LL_SPI_TxDone_INT_Dis(Instance);

        //Tx Disable
        __LL_SPI_Tx_Dis(Instance);
        spi_hdl->tx_ctrl.isr = NULL;
        spi_hdl->tx_ctrl.state = SPI_STATE_READY;

        //Tx Complete Callback
        if (spi_hdl->user_callback.TxCpltCallback) {
            spi_hdl->user_callback.TxCpltCallback();
        }
    }
}

/**
  * @brief  Handle the end of the RX transaction
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_CloseRx_ISR(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    //Disable RxFIFO Full interrupt
    __LL_SPI_RxFIFOFull_INT_Dis(Instance);

    //Rx Disable
    __LL_SPI_Rx_Dis(Instance);
    spi_hdl->rx_ctrl.isr = NULL;
    spi_hdl->rx_ctrl.state = SPI_STATE_READY;

    //Clear RX Done Pending
    if (__LL_SPI_IsRxDoneIntPnd(Instance)) {
        __LL_SPI_RxDoneIntPnd_Clr(Instance);
    }

    //Rx Complete Callback
    if (spi_hdl->user_callback.RxCpltCallback) {
        spi_hdl->user_callback.RxCpltCallback();
    }
}

#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  SPI DMA Init
  * @param  dma_user_cfg user dma config pointer
  * @return DMA_ChannelETypeDef
  */
static DMA_ChannelETypeDef SPI_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg)
{
    LL_StatusETypeDef ret;
    DMA_ChannelETypeDef ch;

    if (dma_user_cfg == NULL) {
        return DMA_CHANNEL_INVALID;
    }

    //User DMA channel request
    ch = LL_DMA_ChannelRequest();

    if (ch == DMA_CHANNEL_INVALID) {
        LOG_E("Requset DMA channel Fail!\n");
        return DMA_CHANNEL_INVALID;
    }

    //User DMA init
    ret = LL_DMA_Init(DMA, ch, dma_user_cfg);

    if (ret != LL_OK) {
        LOG_E("DMA LL init fail!\n");
        LL_DMA_ChannelRelease(ch);
        return DMA_CHANNEL_INVALID;
    }

    return ch;
}

/**
  * @brief  SPI DMA DeInit
  * @param  ch DMA channel to Deinit
  * @return None
  */
static void SPI_DMA_DeInit(DMA_ChannelETypeDef ch)
{
    if (ch == DMA_CHANNEL_INVALID) {
        return;
    }

    LL_DMA_Stop_IT(DMA, ch);
    LL_DMA_DeInit(DMA, ch);
    LL_DMA_ChannelRelease(ch);
}

/**
  * @brief  DMA SPI transmit process complete callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_DMATransmitCplt(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    //Disable Tx DMA Request
    __LL_SPI_TxDMA_Dis(Instance);

    //DMA DeInit
    SPI_DMA_DeInit(spi_hdl->tx_ctrl.dma_ch);
    spi_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    spi_hdl->tx_ctrl.cnt = spi_hdl->tx_ctrl.size;

    //Switch isr to TxDone ISR
    spi_hdl->tx_ctrl.isr = SPI_TxDone_ISR;

    //Enable Tx Done Interrupt
    __LL_SPI_TxDone_INT_En(Instance);
}

/**
  * @brief  DMA SPI receive process complete callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_DMAReceiveCplt(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    //Disable Rx DMA Request
    __LL_SPI_RxDMA_Dis(Instance);

    //DMA DeInit
    SPI_DMA_DeInit(spi_hdl->rx_ctrl.dma_ch);
    spi_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;

    //Clear RX Done Pending
    if (__LL_SPI_IsRxDoneIntPnd(Instance)) {
        __LL_SPI_RxDoneIntPnd_Clr(Instance);
    }

    //Rx Disable
    __LL_SPI_Rx_Dis(Instance);
    spi_hdl->rx_ctrl.cnt = spi_hdl->rx_ctrl.size;
    spi_hdl->rx_ctrl.state = SPI_STATE_READY;

    //Rx Complete Callback
    if (spi_hdl->user_callback.RxCpltCallback) {
        spi_hdl->user_callback.RxCpltCallback();
    }
}

/**
  * @brief  DMA SPI half transmit process complete callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_DMAHalfTransmitCplt(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    //Tx Half Complete Callback
    if (spi_hdl->user_callback.TxHalfCpltCallback) {
        spi_hdl->user_callback.TxHalfCpltCallback();
    }
}

/**
  * @brief  DMA SPI half receive process complete callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_DMAHalfReceiveCplt(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    //Rx Half Complete Callback
    if (spi_hdl->user_callback.RxHalfCpltCallback) {
        spi_hdl->user_callback.RxHalfCpltCallback();
    }
}

/**
  * @brief  DMA SPI transmit process error callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_DMATransmitError(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    //Disable Tx DMA Request
    __LL_SPI_TxDMA_Dis(Instance);

    //Stop Tx and Tx Disable
    __LL_SPI_Mst_TxRx_Stop(Instance);
    __LL_SPI_Tx_Dis(Instance);

    //DMA DeInit
    SPI_DMA_DeInit(spi_hdl->tx_ctrl.dma_ch);

    spi_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    spi_hdl->tx_ctrl.state = SPI_STATE_READY;

    if (spi_hdl->user_callback.ErrorCallback) {
        spi_hdl->user_callback.ErrorCallback();
    }
}

/**
  * @brief  DMA SPI receive process error callback
  * @param  Instance Specifies SPI peripheral
  * @return None
  */
static void SPI_DMAReceiveError(SPI_TypeDef *Instance)
{
    SPI_HandleTypeDef *spi_hdl;

    //SPI handle get
    spi_hdl = SPI_Handle_Get(Instance);

    if (spi_hdl == NULL) {
        LOG_E("Get SPI handle error!\n");
        return;
    }

    //Disable Rx DMA Request
    __LL_SPI_RxDMA_Dis(Instance);

    //Stop Rx and Rx Disable
    __LL_SPI_Mst_TxRx_Stop(Instance);
    __LL_SPI_Rx_Dis(Instance);

    //DMA DeInit
    SPI_DMA_DeInit(spi_hdl->rx_ctrl.dma_ch);

    spi_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    spi_hdl->rx_ctrl.state = SPI_STATE_READY;

    if (spi_hdl->user_callback.ErrorCallback) {
        spi_hdl->user_callback.ErrorCallback();
    }
}

#endif

/**
  * @}
  */


#endif  /* LL_SPI_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

