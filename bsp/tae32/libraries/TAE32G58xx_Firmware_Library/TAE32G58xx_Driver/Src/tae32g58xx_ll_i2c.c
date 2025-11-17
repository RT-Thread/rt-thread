/**
  ******************************************************************************
  * @file    tae32g58xx_ll_i2c.c
  * @author  MCD Application Team
  * @brief   I2C LL module driver
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


#define DBG_TAG             "I2C LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup I2C_LL I2C LL
  * @brief    I2C LL module driver
  * @{
  */

#ifdef LL_I2C_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/** @defgroup I2C_LL_Private_Constants I2C LL Private Constants
  * @brief    I2C LL Private Constants
  * @{
  */

/**
  * @brief I2C Defaul Timeout definition in ms Unit
  */
#define I2C_DEFAULT_TIMEOUT                 (25)

/**
  * @brief I2C Slave Wait for Master Start Timeout definition in ms Unit
  * @note  Only use in Interrupt and DMA transmit mode
  */
#define I2C_SLV_WAIT_FOR_MST_START_TIMEOUT  (30000)

/**
  * @}
  */


/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/** @defgroup I2C_LL_Private_Types I2C LL Private Types
  * @brief    I2C LL Private Types
  * @{
  */

/**
  * @brief I2C IRQ callback function type definition
  */
typedef void (*I2C_LLIRQCallback)(I2C_TypeDef *Instance);

/**
  * @brief  I2C Transmission definition
  */
typedef struct __I2C_TransTypeDef {
    uint8_t *buf;                   /*!< I2C Transmission Buffer Pointer    */
    uint16_t size;                  /*!< I2C Transmission Buffer Size       */
    uint16_t cnt;                   /*!< I2C Transmission Counter           */
    I2C_LLIRQCallback isr;          /*!< Interrupt Service Routine          */
    I2C_StateETypeDef state;        /*!< I2C Transmission State             */
#ifdef LL_DMA_MODULE_ENABLED
    DMA_ChannelETypeDef dma_ch;     /*!< I2C Transmission DMA Channel       */
#endif
} I2C_TransTypeDef;

/**
  * @brief I2C handle Structure definition
  */
typedef struct __I2C_HandleTypeDef {
    I2C_RoleETypeDef  role;                 /*!< I2C role                       */

    volatile I2C_TransTypeDef tx_ctrl;      /*!< I2C Transmission Tx Control    */
    volatile I2C_TransTypeDef rx_ctrl;      /*!< I2C Transmission Rx Control    */

    I2C_UserCallbackTypeDef user_callback;  /*!< User Callback                  */
} I2C_HandleTypeDef;

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup I2C_LL_Private_Variables I2C LL Private Variables
  * @brief    I2C LL Private Variables
  * @{
  */

/**
  * @brief Default I2C LL Config
  */
static const I2C_LLCfgTypeDef i2c_ll_cfg_def = {
    .tx_fifo_empty_thres = 0,   // 0~15
    .rx_fifo_full_thres  = 1,   // 1~16
    .mst_tmext_timing = 0x4f,
    .slv_tsext_timing = 0x7a2,
    .rcv_clk_strch_en = false,
    .rcv_clk_strch_mode = I2C_RCV_CLK_STRCH_MODE_NON_EMPTY,
    .slv_opt_addr_en = false,
    .slv_opt_addr = 0,
    .slv_opt_addr_mask = 0,
    .timing_cfg_en = true,
    .timing_cfg_auto_set = false,
    .spike_suppr_limit = 0,                        
    .slv_data_setup_time = 0x18,                        
    .data_setup_time = 0,                           
    .data_hold_time = 2,                           
};

/**
  * @brief I2C Handle global variable
  */
static I2C_HandleTypeDef i2c_hdl_global[I2C_INSTANCE_NUMS];

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/** @defgroup I2C_LL_Private_Functions I2C LL Private Functions
  * @brief    I2C LL Private Functions
  * @{
  */
static I2C_HandleTypeDef *I2C_Handle_Get(I2C_TypeDef *Instance);

static void I2C_Read_ISR(I2C_TypeDef *Instance);
static void I2C_Write_ISR(I2C_TypeDef *Instance);

#ifdef LL_DMA_MODULE_ENABLED
    static DMA_ChannelETypeDef I2C_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg);
    static void I2C_DMA_DeInit(DMA_ChannelETypeDef ch);
    static void I2C_Write_DMACplt(I2C_TypeDef *Instance);
    static void I2C_Read_DMACplt(I2C_TypeDef *Instance);
    static void I2C_Write_DMAHalfCplt(I2C_TypeDef *Instance);
    static void I2C_Read_DMAHalfCplt(I2C_TypeDef *Instance);
    static void I2C_Write_DMAError(I2C_TypeDef *Instance);
    static void I2C_Read_DMAError(I2C_TypeDef *Instance);
#endif
/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @defgroup I2C_LL_Exported_Functions I2C LL Exported Functions
  * @brief    I2C LL Exported Functions
  * @{
  */

/** @defgroup I2C_LL_Exported_Functions_Group1 I2C Init and DeInit Functions
  * @brief    I2C Init and DeInit Functions
  * @{
  */

/**
  * @brief  I2C LL Init
  * @param  Instance Specifies I2C peripheral
  * @param  user_cfg user config pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_I2C_Init(I2C_TypeDef *Instance, I2C_UserCfgTypeDef *user_cfg)
{
    bool dcn_3_is = false;
    uint32_t baudrate_cnt;
    I2C_HandleTypeDef *i2c_hdl;
    I2C_LLCfgTypeDef *ll_cfg;
    uint32_t spk_pclk_cnt;
    volatile double hold_pclk_tmp;
    uint32_t hold_pclk_cnt;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(user_cfg != NULL);
    assert_param(user_cfg->baudrate);

    if (!IS_I2C_ALL_INSTANCE(Instance) || user_cfg == NULL || !user_cfg->baudrate) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->tx_ctrl.state != I2C_STATE_RESET || i2c_hdl->rx_ctrl.state != I2C_STATE_RESET) {
        LOG_E("This I2C[0x%08" PRIx32 "] is being used!\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    i2c_hdl->tx_ctrl.state = I2C_STATE_BUSY;
    i2c_hdl->rx_ctrl.state = I2C_STATE_BUSY;

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) { 
        dcn_3_is = true;
    }

    //LL config pointer config
    LL_FUNC_ALTER(user_cfg->ll_cfg == NULL, ll_cfg = (I2C_LLCfgTypeDef *)&i2c_ll_cfg_def, ll_cfg = user_cfg->ll_cfg);
    baudrate_cnt = LL_RCU_APB0ClkGet() / user_cfg->baudrate / 2;

    /* Init the low level hardware eg. Clock, NVIC */
    LL_I2C_MspInit(Instance);

    //Module disable and TX/RX FIFO reset
    __LL_I2C_Disable(Instance);
    __LL_I2C_TxFIFO_Reset(Instance);
    __LL_I2C_RxFIFO_Reset(Instance);

    //LL Config
    __LL_I2C_TxFIFOEmptyThres_Set(Instance, ll_cfg->tx_fifo_empty_thres);
    __LL_I2C_RxFIFOFullThres_Set(Instance, ll_cfg->rx_fifo_full_thres);
    __LL_I2C_MST_TmextTiming_Set(Instance, ll_cfg->mst_tmext_timing);
    __LL_I2C_SLV_TsextTiming_Set(Instance, ll_cfg->slv_tsext_timing);

    if (dcn_3_is && (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_I2C))) {
        __LL_I2C_RxDatSCLStrchMode_Set(Instance, ll_cfg->rcv_clk_strch_mode);
        if (user_cfg->role == I2C_ROLE_SLAVE) {
            __LL_I2C_SLV_SCLStrchDis_Release(Instance);
        }

        LL_FUNC_ALTER(ll_cfg->rcv_clk_strch_en == true, __LL_I2C_RxDatSCLStrch_En(Instance), __LL_I2C_RxDatSCLStrch_Dis(Instance));

        __LL_I2C_SLV_OptSlvAddr_Set(Instance, ll_cfg->slv_opt_addr);
        __LL_I2C_SLV_OptSlvAddrMask_Set(Instance, ll_cfg->slv_opt_addr_mask);
        LL_FUNC_ALTER(ll_cfg->slv_opt_addr_en == true, __LL_I2C_SLV_OptSlvAddr_En(Instance), __LL_I2C_SLV_OptSlvAddr_Dis(Instance));
    } 

    //User Config
    if (!dcn_3_is) { 
        LL_FUNC_ALTER(user_cfg->role == I2C_ROLE_MASTER, __LL_I2C_MasterRole_Set(Instance), __LL_I2C_SlaveRole_Set(Instance));  
    }

    LL_FUNC_ALTER(user_cfg->addr_mode == I2C_ADDR_7BIT, __LL_I2C_7bAddr_Set(Instance), __LL_I2C_10bAddr_Set(Instance));
    __LL_I2C_SCLHighLowCnt_Set(Instance, baudrate_cnt, baudrate_cnt);
    __LL_I2C_SLV_SAR_Set(Instance, user_cfg->slave_addr);

    if (ll_cfg->timing_cfg_en) {
        if (dcn_3_is) { 
            if (ll_cfg->timing_cfg_auto_set) {
                spk_pclk_cnt = 50UL / (1000000000UL / LL_RCU_APB0ClkGet());
                if (spk_pclk_cnt >= 0x05UL) {
                    __LL_I2C_SpikeSupprLimit_Set(Instance, 0x05UL);
                    spk_pclk_cnt = 5;
                } else {
                    __LL_I2C_SpikeSupprLimit_Set(Instance, (spk_pclk_cnt > (baudrate_cnt - 1)) ? (baudrate_cnt - 1) : (spk_pclk_cnt));
                }

                hold_pclk_tmp = (((double)LL_RCU_APB0ClkGet()) / ((double)user_cfg->baudrate) / 2.0 - (4.0 + spk_pclk_cnt)) * 1000.0 / 3.0;
                hold_pclk_tmp = hold_pclk_tmp / 1000.0;
                hold_pclk_cnt = (hold_pclk_tmp > 0) ? hold_pclk_tmp : (LL_RCU_APB0ClkGet() / user_cfg->baudrate / 6);
                if ((hold_pclk_cnt - 1) >= 0xffUL) {
                    __LL_I2C_TxTransmitDelay_Set(Instance, 0xffUL);     
                    __LL_I2C_RxCaptureDelay_Set(Instance, 0xffUL); 
                } else {
                    __LL_I2C_TxTransmitDelay_Set(Instance, hold_pclk_cnt - 1);     
                    __LL_I2C_RxCaptureDelay_Set(Instance, hold_pclk_cnt - 1); 
                }
                __LL_I2C_SCLHighLowCnt_Set(Instance, hold_pclk_cnt * 3 , hold_pclk_cnt);

                __LL_I2C_SLV_TxTransmitDelay_Set(Instance, i2c_ll_cfg_def.slv_data_setup_time);

            } else {
                __LL_I2C_SpikeSupprLimit_Set(Instance, ll_cfg->spike_suppr_limit);
                __LL_I2C_SLV_TxTransmitDelay_Set(Instance, ll_cfg->slv_data_setup_time);
                __LL_I2C_RxCaptureDelay_Set(Instance, ll_cfg->data_setup_time);            
                __LL_I2C_TxTransmitDelay_Set(Instance, ll_cfg->data_hold_time);                
            }        
        } else {
            //Data Hold Time Config to Fix Slave Timing
            __LL_I2C_TxTransmitDelay_Set(Instance, 2);
        }
    }  

    //All Interrupt Pending Clear
    __LL_I2C_AllIntPnd_Clr(Instance);

    //I2C Enable
    __LL_I2C_Enable(Instance);

    //I2C Handle Init
    if (dcn_3_is) { 
        //This parameter does not update in real-time and requires manual updating by the user
        i2c_hdl->role = (I2C_RoleETypeDef)__LL_I2C_CurrRole_Get(Instance);
    } else {
        i2c_hdl->role = user_cfg->role;        
    }

    i2c_hdl->tx_ctrl.state = I2C_STATE_READY;
    i2c_hdl->rx_ctrl.state = I2C_STATE_READY;
    i2c_hdl->user_callback = user_cfg->user_callback;

    return LL_OK;
}

/**
  * @brief  I2C LL DeInit
  * @param  Instance Specifies I2C peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_I2C_DeInit(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if (!IS_I2C_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->tx_ctrl.state == I2C_STATE_BUSY_TX || i2c_hdl->rx_ctrl.state == I2C_STATE_BUSY_RX) {
        LOG_E("This I2C[0x%08" PRIx32 "] is being used!\n", (uint32_t)Instance);
        return LL_BUSY;
    }

    i2c_hdl->tx_ctrl.state = I2C_STATE_BUSY;
    i2c_hdl->rx_ctrl.state = I2C_STATE_BUSY;

    //I2C Module Disable
    __LL_I2C_Disable(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_I2C_MspDeInit(Instance);

    memset((void *)i2c_hdl, 0, sizeof(I2C_HandleTypeDef));
    i2c_hdl->tx_ctrl.state = I2C_STATE_RESET;
    i2c_hdl->rx_ctrl.state = I2C_STATE_RESET;

    return LL_OK;
}

/**
  * @brief  I2C LL Reset
  * @param  Instance Specifies I2C peripheral
  * @return Status of the Reset
  */
LL_StatusETypeDef LL_I2C_Reset(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;
    IRQn_Type irq_num;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if (!IS_I2C_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    }

    irq_num = GET_I2C_IRQ_NUMBER(Instance);
    if (irq_num < 0) {
        LOG_E("I2C IRQ does not exist!\n");
        return LL_ERROR;
    }

    //Clear pending and interrupt disable
    __disable_irq();
    __LL_I2C_Disable(Instance);
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        CLEAR_BIT(Instance->INTREN, 0xffffffUL);
        SET_BIT(Instance->INTR, 0xbffffcUL);
    } else {
        CLEAR_BIT(Instance->INTREN, 0x7fffffUL);
        SET_BIT(Instance->INTR, 0x3ffffcUL);
    }
    NVIC_ClearPendingIRQ(irq_num);
    NVIC_DisableIRQ(irq_num);
    __enable_irq();

    i2c_hdl->tx_ctrl.state = I2C_STATE_BUSY;
    i2c_hdl->rx_ctrl.state = I2C_STATE_BUSY;

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_I2C_MspDeInit(Instance);

    memset((void *)i2c_hdl, 0, sizeof(I2C_HandleTypeDef));
    i2c_hdl->tx_ctrl.state = I2C_STATE_RESET;
    i2c_hdl->rx_ctrl.state = I2C_STATE_RESET;

    return LL_OK;
}

/**
  * @brief  Initializes the I2C MSP
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_MspInit(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_MspInit could be implemented in the user file
     */
}

/**
  * @brief  DeInitializes the I2C MSP
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_MspDeInit(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_MspDeInit could be implemented in the user file
     */
}

/**
  * @brief  Register an User I2C Callback
  * @note   User can register callback only in I2C Ready State
  * @param  Instance Specifies I2C peripheral
  * @param  CallbackID ID of the callback to be registered
  * @param  pCallback pointer to the Callback function
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_RegisterCallback(I2C_TypeDef *Instance, I2C_UserCallbackIdETypeDef CallbackID, I2C_UserCallback pCallback)
{
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if (!IS_I2C_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    }

    //Check callback pointer valid or not
    if (pCallback == NULL) {
        LOG_E("The callback pointer which to be registered is NULL!\n");
        return LL_INVALID;
    }

    //Register user callback
    switch (CallbackID) {
        case I2C_TX_CPLT_CB_ID:
            if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY) {
                LOG_E("This I2C[0x%08" PRIx32 "] Tx isn't in Ready state, can't register Tx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            i2c_hdl->user_callback.TxCpltCallback = pCallback;
            break;

        case I2C_RX_CPLT_CB_ID:
            if (i2c_hdl->rx_ctrl.state != I2C_STATE_READY) {
                LOG_E("This I2C[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Rx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            i2c_hdl->user_callback.RxCpltCallback = pCallback;
            break;

        case I2C_TX_HALF_CPLT_CB_ID:
            if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY) {
                LOG_E("This I2C[0x%08" PRIx32 "] Tx isn't in Ready state, can't register Tx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            i2c_hdl->user_callback.TxHalfCpltCallback = pCallback;
            break;

        case I2C_RX_HALF_CPLT_CB_ID:
            if (i2c_hdl->rx_ctrl.state != I2C_STATE_READY) {
                LOG_E("This I2C[0x%08" PRIx32 "] Rx isn't in Ready state, can't register Rx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            i2c_hdl->user_callback.RxHalfCpltCallback = pCallback;
            break;

        case I2C_ERROR_CB_ID:
            if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY || i2c_hdl->rx_ctrl.state != I2C_STATE_READY) {
                LOG_E("This I2C[0x%08" PRIx32 "] Tx&Rx are both not in Ready state, can't register Error callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            i2c_hdl->user_callback.ErrorCallback = pCallback;
            break;

        default:
            LOG_E("I2C user callback ID-[%d] is Invalid!\n", CallbackID);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @brief  UnRegister an User I2C Callback
  * @note   User can unregister callback only in I2C Ready State
  * @param  Instance Specifies I2C peripheral
  * @param  CallbackID ID of the callback to be unregistered
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_UnRegisterCallback(I2C_TypeDef *Instance, I2C_UserCallbackIdETypeDef CallbackID)
{
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if (!IS_I2C_ALL_INSTANCE(Instance)) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    }

    //UnRegister user callback
    switch (CallbackID) {
        case I2C_TX_CPLT_CB_ID:
            if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY) {
                LOG_E("This I2C[0x%08" PRIx32 "] Tx isn't in Ready state, can't unregister Tx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            i2c_hdl->user_callback.TxCpltCallback = NULL;
            break;

        case I2C_RX_CPLT_CB_ID:
            if (i2c_hdl->rx_ctrl.state != I2C_STATE_READY) {
                LOG_E("This I2C[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Rx Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            i2c_hdl->user_callback.RxCpltCallback = NULL;
            break;

        case I2C_TX_HALF_CPLT_CB_ID:
            if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY) {
                LOG_E("This I2C[0x%08" PRIx32 "] Tx isn't in Ready state, can't unregister Tx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            i2c_hdl->user_callback.TxHalfCpltCallback = NULL;
            break;

        case I2C_RX_HALF_CPLT_CB_ID:
            if (i2c_hdl->rx_ctrl.state != I2C_STATE_READY) {
                LOG_E("This I2C[0x%08" PRIx32 "] Rx isn't in Ready state, can't unregister Rx Half Complete callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            i2c_hdl->user_callback.RxHalfCpltCallback = NULL;
            break;

        case I2C_ERROR_CB_ID:
            if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY || i2c_hdl->rx_ctrl.state != I2C_STATE_READY) {
                LOG_E("This I2C[0x%08" PRIx32 "] Tx&Rx are both not in Ready state, can't unregister Error callback!\n", (uint32_t)Instance);
                return LL_FAILED;
            }

            i2c_hdl->user_callback.ErrorCallback = NULL;
            break;

        default:
            LOG_E("I2C user callback ID-[%d] is Invalid!\n", CallbackID);
            return LL_INVALID;
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup I2C_LL_Exported_Functions_Group2 I2C Read Write Functions
  * @brief    I2C Read Write Functions
  * @{
  */

/**
  * @brief  I2C Master Read an amount of data in CPU blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_MasterRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->rx_ctrl.state != I2C_STATE_READY || i2c_hdl->tx_ctrl.state == I2C_STATE_BUSY_TX) {
        LOG_E("This I2C[0x%08" PRIx32 "] Rx isn't in READY state or Tx is Ongoing, can't start Read operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    i2c_hdl->rx_ctrl.state = I2C_STATE_BUSY_RX;
    i2c_hdl->rx_ctrl.buf = frame->buf;
    i2c_hdl->rx_ctrl.size = frame->buf_len;
    i2c_hdl->rx_ctrl.cnt = 0;
    i2c_hdl->rx_ctrl.isr = NULL;

    //Clear RxFIFO and interrupt pending which will be used following
    __LL_I2C_RxFIFO_Reset(Instance);
    __LL_I2C_MST_TxRxDone_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);
    tickstart = LL_GetTick();

    //TAR config
    __LL_I2C_MST_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_StartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_StartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_StartAddr32b(Instance, frame->mem_addr);
    }

    /*** First transmit (TAR+)memory address if need ***/
    if (frame->mem_addr_size != I2C_MEMADDR_SIZE_INVALID) {
        //Wait for Master TX/RX Done
        while (!__LL_I2C_MST_IsTxRxDone(Instance)) {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                ret = LL_TIMEOUT;
                goto exit;
            }
        }

        //Clear Master TX/RX Done Pending
        __LL_I2C_MST_TxRxDone_Clr(Instance);
    }

    /*** Second Start to read data ***/
    __LL_I2C_Timing_StartReadStop(Instance, frame->buf_len);

    //Read data loop
    while (i2c_hdl->rx_ctrl.cnt < i2c_hdl->rx_ctrl.size) {
        if (!__LL_I2C_IsRxFIFOEmpty(Instance)) {
            *i2c_hdl->rx_ctrl.buf = (uint8_t)__LL_I2C_Dat_Read(Instance);
            i2c_hdl->rx_ctrl.buf++;
            i2c_hdl->rx_ctrl.cnt++;
        } else {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                ret = LL_TIMEOUT;
                goto exit;
            }
        }
    }

    //Wait for Stop Detect
    while (!__LL_I2C_IsDetStop(Instance)) {
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            LOG_E("<%s> timeout!\n", __FUNCTION__);
            ret = LL_TIMEOUT;
            goto exit;
        }
    }

    //Clear Stop Detect and Tx Done interrupt Pending
    __LL_I2C_DetStop_Clr(Instance);
    __LL_I2C_MST_TxRxDone_Clr(Instance);

    ret = LL_OK;

exit:
    i2c_hdl->rx_ctrl.state = I2C_STATE_READY;
    return ret;
}

/**
  * @brief  I2C Master Write an amount of data in CPU blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_MasterWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY || i2c_hdl->rx_ctrl.state == I2C_STATE_BUSY_RX) {
        LOG_E("This I2C[0x%08" PRIx32 "] Tx isn't in READY state or Rx is Ongoing, can't start Write operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    i2c_hdl->tx_ctrl.state = I2C_STATE_BUSY_TX;
    i2c_hdl->tx_ctrl.buf = frame->buf;
    i2c_hdl->tx_ctrl.size = frame->buf_len;
    i2c_hdl->tx_ctrl.cnt = 0;
    i2c_hdl->tx_ctrl.isr = NULL;

    //Clear TxFIFO and interrupt pending which will be used following
    __LL_I2C_TxFIFO_Reset(Instance);
    __LL_I2C_MST_TxRxDone_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);
    tickstart = LL_GetTick();

    //TAR config
    __LL_I2C_MST_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_StartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_StartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_StartAddr32b(Instance, frame->mem_addr);
    }

    /*** First transmit (TAR+)memory address if need, Second continue to write data ***/
    if (frame->mem_addr_size != I2C_MEMADDR_SIZE_INVALID) {
        //Wait for Master TX/RX Done
        while (!__LL_I2C_MST_IsTxRxDone(Instance)) {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                ret = LL_TIMEOUT;
                goto exit;
            }
        }

        //Clear Master TX/RX Done Pending
        __LL_I2C_MST_TxRxDone_Clr(Instance);

        //Continue Write data, don't need Restart signgal
        __LL_I2C_Timing_WriteStop(Instance, frame->buf_len);
    } else {
        //No need to send memory address, so need Start signal to start write data
        __LL_I2C_Timing_StartWriteStop(Instance, frame->buf_len);
    }

    //Write data loop
    while (i2c_hdl->tx_ctrl.cnt < i2c_hdl->tx_ctrl.size) {
        if (!__LL_I2C_IsTxFIFOFull(Instance)) {
            __LL_I2C_Dat_Write(Instance, *i2c_hdl->tx_ctrl.buf);
            i2c_hdl->tx_ctrl.buf++;
            i2c_hdl->tx_ctrl.cnt++;
        } else {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                ret = LL_TIMEOUT;
                goto exit;
            }
        }
    }

    //Wait for Stop Detect
    while (!__LL_I2C_IsDetStop(Instance)) {
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            LOG_E("<%s> timeout!\n", __FUNCTION__);
            ret = LL_TIMEOUT;
            goto exit;
        }
    }

    //Clear Stop Detect and Tx Done interrupt Pending
    __LL_I2C_DetStop_Clr(Instance);
    __LL_I2C_MST_TxRxDone_Clr(Instance);

    ret = LL_OK;

exit:
    i2c_hdl->tx_ctrl.state = I2C_STATE_READY;
    return ret;
}

/**
  * @brief  I2C Slave Read an amount of data in CPU blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_SlaveRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->rx_ctrl.state != I2C_STATE_READY) {
        LOG_E("This I2C[0x%08" PRIx32 "] Rx isn't in READY state, can't start Read operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    i2c_hdl->rx_ctrl.state = I2C_STATE_BUSY_RX;
    i2c_hdl->rx_ctrl.buf = frame->buf;
    i2c_hdl->rx_ctrl.size = frame->buf_len;
    i2c_hdl->rx_ctrl.cnt = 0;
    i2c_hdl->rx_ctrl.isr = NULL;

    //Clear RxFIFO and interrupt pending which will be used following
    __LL_I2C_RxFIFO_Reset(Instance);
    __LL_I2C_SLV_RxAddrAndCmdIsSlvRX_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);
    tickstart = LL_GetTick();

    // Wait for Master Start transmit
    while (!__LL_I2C_SLV_IsRxAddrAndCmdIsSlvRX(Instance)) {
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            LOG_E("<%s> timeout!\n", __FUNCTION__);
            ret = LL_TIMEOUT;
            goto exit;
        }
    }

    //Clear Slave Rx Pending
    __LL_I2C_SLV_RxAddrAndCmdIsSlvRX_Clr(Instance);

    //Read data loop
    while (i2c_hdl->rx_ctrl.cnt < i2c_hdl->rx_ctrl.size) {
        if (!__LL_I2C_IsRxFIFOEmpty(Instance)) {
            *i2c_hdl->rx_ctrl.buf = (uint8_t)__LL_I2C_Dat_Read(Instance);
            i2c_hdl->rx_ctrl.buf++;
            i2c_hdl->rx_ctrl.cnt++;
        } else {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                ret = LL_TIMEOUT;
                goto exit;
            }
        }
    }

    //Wait for Stop Detect
    while (!__LL_I2C_IsDetStop(Instance)) {
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            LOG_E("<%s> timeout!\n", __FUNCTION__);
            ret = LL_TIMEOUT;
            goto exit;
        }
    }

    //Clear Stop Detect Pending
    __LL_I2C_DetStop_Clr(Instance);

    ret = LL_OK;

exit:
    i2c_hdl->rx_ctrl.state = I2C_STATE_READY;
    return ret;
}

/**
  * @brief  I2C Slave Write an amount of data in CPU blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_SlaveWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret;
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY) {
        LOG_E("This I2C[0x%08" PRIx32 "] Tx isn't in READY state, can't start Write operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    i2c_hdl->tx_ctrl.state = I2C_STATE_BUSY_TX;
    i2c_hdl->tx_ctrl.buf = frame->buf;
    i2c_hdl->tx_ctrl.size = frame->buf_len;
    i2c_hdl->tx_ctrl.cnt = 0;
    i2c_hdl->tx_ctrl.isr = NULL;

    //Clear TxFIFO and interrupt pending which will be used following
    __LL_I2C_TxFIFO_Reset(Instance);
    __LL_I2C_SLV_RxAddrAndCmdIsSlvTX_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);
    tickstart = LL_GetTick();

    // Wait for Master Start transmit
    while (!__LL_I2C_SLV_IsRxAddrAndCmdIsSlvTX(Instance)) {
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            LOG_E("<%s> timeout!\n", __FUNCTION__);
            ret = LL_TIMEOUT;
            goto exit;
        }
    }

    //Clear Slave Tx Pending
    __LL_I2C_SLV_RxAddrAndCmdIsSlvTX_Clr(Instance);

    //Write data loop
    while (i2c_hdl->tx_ctrl.cnt < i2c_hdl->tx_ctrl.size) {
        if (!__LL_I2C_IsTxFIFOFull(Instance)) {
            __LL_I2C_Dat_Write(Instance, *i2c_hdl->tx_ctrl.buf);
            i2c_hdl->tx_ctrl.buf++;
            i2c_hdl->tx_ctrl.cnt++;
        } else {
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                ret = LL_TIMEOUT;
                goto exit;
            }
        }
    }

    //Wait for Stop Detect
    while (!__LL_I2C_IsDetStop(Instance)) {
        if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {
            LOG_E("<%s> timeout!\n", __FUNCTION__);
            ret = LL_TIMEOUT;
            goto exit;
        }
    }

    //Clear Stop Detect Pending
    __LL_I2C_DetStop_Clr(Instance);

    ret = LL_OK;

exit:
    i2c_hdl->tx_ctrl.state = I2C_STATE_READY;
    return ret;
}

/**
  * @brief  SMBUS Master Read an amount of data in CPU blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_MasterRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    frame->mem_addr_size = I2C_MEMADDR_SIZE_8BIT;
    frame->mem_addr = frame->smbus_cmd;

    return LL_I2C_MasterRead_CPU(Instance, frame, timeout);
}

/**
  * @brief  SMBUS Master Write an amount of data in CPU blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_MasterWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    frame->mem_addr_size = I2C_MEMADDR_SIZE_8BIT;
    frame->mem_addr = frame->smbus_cmd;

    return LL_I2C_MasterWrite_CPU(Instance, frame, timeout);
}

/**
  * @brief  SMBUS Slave Read an amount of data in CPU blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_SlaveRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    return LL_I2C_SlaveRead_CPU(Instance, frame, timeout);
}

/**
  * @brief  SMBUS Slave Write an amount of data in CPU blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @param  timeout timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_SlaveWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t timeout)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    return LL_I2C_SlaveWrite_CPU(Instance, frame, timeout);
}


/**
  * @brief  I2C Master Read an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_MasterRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    uint32_t tickstart;
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->rx_ctrl.state != I2C_STATE_READY || i2c_hdl->tx_ctrl.state == I2C_STATE_BUSY_TX) {
        LOG_E("This I2C[0x%08" PRIx32 "] Rx isn't in READY state or Tx is Ongoing, can't start Read operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    i2c_hdl->rx_ctrl.state = I2C_STATE_BUSY_RX;
    i2c_hdl->rx_ctrl.buf = frame->buf;
    i2c_hdl->rx_ctrl.size = frame->buf_len;
    i2c_hdl->rx_ctrl.cnt = 0;
    i2c_hdl->rx_ctrl.isr = I2C_Read_ISR;

    //Clear RxFIFO and interrupt pending which will be used following
    __LL_I2C_RxFIFO_Reset(Instance);
    __LL_I2C_MST_TxRxDone_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);
    tickstart = LL_GetTick();

    //TAR config
    __LL_I2C_MST_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_StartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_StartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_StartAddr32b(Instance, frame->mem_addr);
    }

    /*** First transmit (TAR+)memory address if need ***/
    if (frame->mem_addr_size != I2C_MEMADDR_SIZE_INVALID) {
        //Wait for Master TX/RX Done
        while (!__LL_I2C_MST_IsTxRxDone(Instance)) {
            if ((LL_GetTick() - tickstart) > I2C_DEFAULT_TIMEOUT) {
                i2c_hdl->rx_ctrl.state = I2C_STATE_READY;
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                return LL_TIMEOUT;
            }
        }

        //Clear Master TX/RX Done Pending
        __LL_I2C_MST_TxRxDone_Clr(Instance);
    }

    /*** Second Start to read data ***/
    __LL_I2C_Timing_StartReadStop(Instance, frame->buf_len);

    //Enable RxFIFO Full interrupt
    __LL_I2C_RxFIFOFull_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  I2C Master Write an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_MasterWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    uint32_t tickstart;
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY || i2c_hdl->rx_ctrl.state == I2C_STATE_BUSY_RX) {
        LOG_E("This I2C[0x%08" PRIx32 "] Tx isn't in READY state or Rx is Ongoing, can't start Write operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    i2c_hdl->tx_ctrl.state = I2C_STATE_BUSY_TX;
    i2c_hdl->tx_ctrl.buf = frame->buf;
    i2c_hdl->tx_ctrl.size = frame->buf_len;
    i2c_hdl->tx_ctrl.cnt = 0;
    i2c_hdl->tx_ctrl.isr = I2C_Write_ISR;

    //Clear TxFIFO and interrupt pending which will be used following
    __LL_I2C_TxFIFO_Reset(Instance);
    __LL_I2C_MST_TxRxDone_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);
    tickstart = LL_GetTick();

    //TAR config
    __LL_I2C_MST_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_StartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_StartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_StartAddr32b(Instance, frame->mem_addr);
    }

    /*** First transmit (TAR+)memory address if need, Second continue to write data ***/
    if (frame->mem_addr_size != I2C_MEMADDR_SIZE_INVALID) {
        //Wait for Master TX/RX Done
        while (!__LL_I2C_MST_IsTxRxDone(Instance)) {
            if ((LL_GetTick() - tickstart) > I2C_DEFAULT_TIMEOUT) {
                i2c_hdl->tx_ctrl.state = I2C_STATE_READY;
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                return LL_TIMEOUT;
            }
        }

        //Clear Master TX/RX Done Pending
        __LL_I2C_MST_TxRxDone_Clr(Instance);

        //Continue Write data, don't need Restart signgal
        __LL_I2C_Timing_WriteStop(Instance, frame->buf_len);
    } else {
        //No need to send memory address, so need Start signal to start write data
        __LL_I2C_Timing_StartWriteStop(Instance, frame->buf_len);
    }

    //Enable TxFIFO Empty interrupt
    __LL_I2C_TxFIFOEmpty_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  I2C Slave Read an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_SlaveRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->rx_ctrl.state != I2C_STATE_READY) {
        LOG_E("This I2C[0x%08" PRIx32 "] Rx isn't in READY state, can't start Read operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    i2c_hdl->rx_ctrl.state = I2C_STATE_BUSY_RX;
    i2c_hdl->rx_ctrl.buf = frame->buf;
    i2c_hdl->rx_ctrl.size = frame->buf_len;
    i2c_hdl->rx_ctrl.cnt = 0;
    i2c_hdl->rx_ctrl.isr = I2C_Read_ISR;

    //Clear RxFIFO and interrupt pending which will be used following
    __LL_I2C_RxFIFO_Reset(Instance);
    __LL_I2C_SLV_RxAddrAndCmdIsSlvRX_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);

    //Enable RxFIFO Full interrupt
    __LL_I2C_RxFIFOFull_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  I2C Slave Write an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_SlaveWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    I2C_HandleTypeDef *i2c_hdl;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY) {
        LOG_E("This I2C[0x%08" PRIx32 "] Tx isn't in READY state, can't start Write operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //Transmit config
    i2c_hdl->tx_ctrl.state = I2C_STATE_BUSY_TX;
    i2c_hdl->tx_ctrl.buf = frame->buf;
    i2c_hdl->tx_ctrl.size = frame->buf_len;
    i2c_hdl->tx_ctrl.cnt = 0;
    i2c_hdl->tx_ctrl.isr = I2C_Write_ISR;

    //Clear TxFIFO and interrupt pending which will be used following
    __LL_I2C_TxFIFO_Reset(Instance);
    __LL_I2C_SLV_RxAddrAndCmdIsSlvTX_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);

    //Enable TxFIFO Empty interrupt
    __LL_I2C_TxFIFOEmpty_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  SMBUS Master Read an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_MasterRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    frame->mem_addr_size = I2C_MEMADDR_SIZE_8BIT;
    frame->mem_addr = frame->smbus_cmd;

    return LL_I2C_MasterRead_IT(Instance, frame);
}

/**
  * @brief  SMBUS Master Write an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  frame Write frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_MasterWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    frame->mem_addr_size = I2C_MEMADDR_SIZE_8BIT;
    frame->mem_addr = frame->smbus_cmd;

    return LL_I2C_MasterWrite_IT(Instance, frame);
}

/**
  * @brief  SMBUS Slave Read an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_SlaveRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    return LL_I2C_SlaveRead_IT(Instance, frame);
}

/**
  * @brief  SMBUS Slave Write an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_SlaveWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    return LL_I2C_SlaveWrite_IT(Instance, frame);
}


#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  I2C Master Read an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_MasterRead_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    uint32_t tickstart;
    I2C_HandleTypeDef *i2c_hdl;
    DMA_UserCfgTypeDef dma_user_cfg;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->rx_ctrl.state != I2C_STATE_READY || i2c_hdl->tx_ctrl.state == I2C_STATE_BUSY_TX) {
        LOG_E("This I2C[0x%08" PRIx32 "] Rx isn't in READY state or Tx is Ongoing, can't start Read operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //DMA Init
    memset((void *)&dma_user_cfg, 0x0, sizeof(dma_user_cfg));
    dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
    dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;

    dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_FIX;
    dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == I2C0) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_I2C0_RX;
    } else if (Instance == I2C1) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_I2C1_RX;
    } else if (Instance == I2C2) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_I2C2_RX;
    } else {
        LOG_E("I2C DMA source handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Receive Default Config
    dma_user_cfg.trans_type = DMA_TRANS_TYPE_P2M;
    dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_INC;
    dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    dma_user_cfg.end_callback = (DMA_IRQCallback)I2C_Read_DMACplt;
    dma_user_cfg.end_arg = Instance;
    dma_user_cfg.err_callback = (DMA_IRQCallback)I2C_Read_DMAError;
    dma_user_cfg.err_arg = Instance;
    dma_user_cfg.half_callback = (DMA_IRQCallback)I2C_Read_DMAHalfCplt;
    dma_user_cfg.half_arg = Instance;

    i2c_hdl->rx_ctrl.dma_ch = I2C_DMA_Init(&dma_user_cfg);

    if (i2c_hdl->rx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("I2C read request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Transmit config
    i2c_hdl->rx_ctrl.state = I2C_STATE_BUSY_RX;
    i2c_hdl->rx_ctrl.buf = frame->buf;
    i2c_hdl->rx_ctrl.size = frame->buf_len;
    i2c_hdl->rx_ctrl.cnt = 0;
    i2c_hdl->rx_ctrl.isr = NULL;

    //Clear RxFIFO and interrupt pending which will be used following
    __LL_I2C_RxFIFO_Reset(Instance);
    __LL_I2C_MST_TxRxDone_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);
    tickstart = LL_GetTick();

    //TAR config
    __LL_I2C_MST_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_StartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_StartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_StartAddr32b(Instance, frame->mem_addr);
    }

    /*** First transmit (TAR+)memory address if need ***/
    if (frame->mem_addr_size != I2C_MEMADDR_SIZE_INVALID) {
        //Wait for Master TX/RX Done
        while (!__LL_I2C_MST_IsTxRxDone(Instance)) {
            if ((LL_GetTick() - tickstart) > I2C_DEFAULT_TIMEOUT) {
                I2C_DMA_DeInit(i2c_hdl->rx_ctrl.dma_ch);
                i2c_hdl->rx_ctrl.state = I2C_STATE_READY;
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                return LL_TIMEOUT;
            }
        }

        //Clear Master TX/RX Done Pending
        __LL_I2C_MST_TxRxDone_Clr(Instance);
    }

    /*** Second Start to read data ***/
    __LL_I2C_Timing_StartReadStop(Instance, frame->buf_len);

    //Enable Rx DMA Requset
    __LL_I2C_RxDMA_En(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, i2c_hdl->rx_ctrl.dma_ch, (uint32_t)&Instance->RXDATA, (uint32_t)i2c_hdl->rx_ctrl.buf, i2c_hdl->rx_ctrl.size);

    return LL_OK;
}

/**
  * @brief  I2C Master Write an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_MasterWrite_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    uint32_t tickstart;
    I2C_HandleTypeDef *i2c_hdl;
    DMA_UserCfgTypeDef dma_user_cfg;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY || i2c_hdl->rx_ctrl.state == I2C_STATE_BUSY_RX) {
        LOG_E("This I2C[0x%08" PRIx32 "] Tx isn't in READY state or Rx is Ongoing, can't start Write operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //DMA Init
    memset((void *)&dma_user_cfg, 0x0, sizeof(dma_user_cfg));
    dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
    dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;

    dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_FIX;
    dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == I2C0) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_I2C0_TX;
    } else if (Instance == I2C1) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_I2C1_TX;
    } else if (Instance == I2C2) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_I2C2_TX;
    } else {
        LOG_E("I2C DMA destination handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Transmit Default Config
    dma_user_cfg.trans_type = DMA_TRANS_TYPE_M2P;
    dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_INC;
    dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    dma_user_cfg.end_callback = (DMA_IRQCallback)I2C_Write_DMACplt;
    dma_user_cfg.end_arg = Instance;
    dma_user_cfg.err_callback = (DMA_IRQCallback)I2C_Write_DMAError;
    dma_user_cfg.err_arg = Instance;
    dma_user_cfg.half_callback = (DMA_IRQCallback)I2C_Write_DMAHalfCplt;
    dma_user_cfg.half_arg = Instance;

    i2c_hdl->tx_ctrl.dma_ch = I2C_DMA_Init(&dma_user_cfg);

    if (i2c_hdl->tx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("I2C write request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Transmit config
    i2c_hdl->tx_ctrl.state = I2C_STATE_BUSY_TX;
    i2c_hdl->tx_ctrl.buf = frame->buf;
    i2c_hdl->tx_ctrl.size = frame->buf_len;
    i2c_hdl->tx_ctrl.cnt = 0;
    i2c_hdl->tx_ctrl.isr = NULL;

    //Clear TxFIFO and interrupt pending which will be used following
    __LL_I2C_TxFIFO_Reset(Instance);
    __LL_I2C_MST_TxRxDone_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);
    tickstart = LL_GetTick();

    //TAR config
    __LL_I2C_MST_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_StartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_StartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_StartAddr32b(Instance, frame->mem_addr);
    }

    /*** First transmit (TAR+)memory address if need, Second continue to write data ***/
    if (frame->mem_addr_size != I2C_MEMADDR_SIZE_INVALID) {
        //Wait for Master TX/RX Done
        while (!__LL_I2C_MST_IsTxRxDone(Instance)) {
            if ((LL_GetTick() - tickstart) > I2C_DEFAULT_TIMEOUT) {
                I2C_DMA_DeInit(i2c_hdl->tx_ctrl.dma_ch);
                i2c_hdl->tx_ctrl.state = I2C_STATE_READY;
                LOG_E("<%s> timeout!\n", __FUNCTION__);
                return LL_TIMEOUT;
            }
        }

        //Clear Master TX/RX Done Pending
        __LL_I2C_MST_TxRxDone_Clr(Instance);

        //Continue Write data, don't need Restart signgal
        __LL_I2C_Timing_WriteStop(Instance, frame->buf_len);
    } else {
        //No need to send memory address, so need Start signal to start write data
        __LL_I2C_Timing_StartWriteStop(Instance, frame->buf_len);
    }

    //Enable Tx DMA Requset
    __LL_I2C_TxDMA_En(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, i2c_hdl->tx_ctrl.dma_ch, (uint32_t)i2c_hdl->tx_ctrl.buf, (uint32_t)&Instance->TXDATA, i2c_hdl->tx_ctrl.size);

    return LL_OK;
}

/**
  * @brief  I2C Slave Read an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_SlaveRead_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    I2C_HandleTypeDef *i2c_hdl;
    DMA_UserCfgTypeDef dma_user_cfg;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->rx_ctrl.state != I2C_STATE_READY) {
        LOG_E("This I2C[0x%08" PRIx32 "] Rx isn't in READY state, can't start Read operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //DMA Init
    memset((void *)&dma_user_cfg, 0x0, sizeof(dma_user_cfg));
    dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
    dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;

    dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_FIX;
    dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == I2C0) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_I2C0_RX;
    } else if (Instance == I2C1) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_I2C1_RX;
    } else if (Instance == I2C2) {
        dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_I2C2_RX;
    } else {
        LOG_E("I2C DMA source handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Receive Default Config
    dma_user_cfg.trans_type = DMA_TRANS_TYPE_P2M;
    dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_INC;
    dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    dma_user_cfg.end_callback = (DMA_IRQCallback)I2C_Read_DMACplt;
    dma_user_cfg.end_arg = Instance;
    dma_user_cfg.err_callback = (DMA_IRQCallback)I2C_Read_DMAError;
    dma_user_cfg.err_arg = Instance;
    dma_user_cfg.half_callback = (DMA_IRQCallback)I2C_Read_DMAHalfCplt;
    dma_user_cfg.half_arg = Instance;

    i2c_hdl->rx_ctrl.dma_ch = I2C_DMA_Init(&dma_user_cfg);

    if (i2c_hdl->rx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("I2C read request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Transmit config
    i2c_hdl->rx_ctrl.state = I2C_STATE_BUSY_RX;
    i2c_hdl->rx_ctrl.buf = frame->buf;
    i2c_hdl->rx_ctrl.size = frame->buf_len;
    i2c_hdl->rx_ctrl.cnt = 0;
    i2c_hdl->rx_ctrl.isr = NULL;

    //Clear RxFIFO and interrupt pending which will be used following
    __LL_I2C_RxFIFO_Reset(Instance);
    __LL_I2C_SLV_RxAddrAndCmdIsSlvRX_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);

    //Enable Rx DMA Requset
    __LL_I2C_RxDMA_En(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, i2c_hdl->rx_ctrl.dma_ch, (uint32_t)&Instance->RXDATA, (uint32_t)i2c_hdl->rx_ctrl.buf, i2c_hdl->rx_ctrl.size);

    return LL_OK;
}

/**
  * @brief  I2C Slave Write an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_SlaveWrite_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    I2C_HandleTypeDef *i2c_hdl;
    DMA_UserCfgTypeDef dma_user_cfg;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return LL_ERROR;
    } else if (i2c_hdl->tx_ctrl.state != I2C_STATE_READY) {
        LOG_E("This I2C[0x%08" PRIx32 "] Tx isn't in READY state, can't start Write operation!\n", (uint32_t)Instance);
        return LL_FAILED;
    }

    //DMA Init
    memset((void *)&dma_user_cfg, 0x0, sizeof(dma_user_cfg));
    dma_user_cfg.src_data_width = DMA_TRANS_WIDTH_8b;
    dma_user_cfg.dst_data_width = DMA_TRANS_WIDTH_8b;

    dma_user_cfg.dst_addr_mode = DMA_ADDR_MODE_FIX;
    dma_user_cfg.trans_mode = DMA_TRANS_MODE_SINGLE;

    if (Instance == I2C0) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_I2C0_TX;
    } else if (Instance == I2C1) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_I2C1_TX;
    } else if (Instance == I2C2) {
        dma_user_cfg.dst_hs_ifc = DMA_HANDSHAKE_IFC_I2C2_TX;
    } else {
        LOG_E("I2C DMA destination handshake interface auto config error!\n");
        return LL_ERROR;
    }

    //DMA Transmit Default Config
    dma_user_cfg.trans_type = DMA_TRANS_TYPE_M2P;
    dma_user_cfg.src_addr_mode = DMA_ADDR_MODE_INC;
    dma_user_cfg.src_hs_ifc = DMA_HANDSHAKE_IFC_MEMORY;

    dma_user_cfg.end_callback = (DMA_IRQCallback)I2C_Write_DMACplt;
    dma_user_cfg.end_arg = Instance;
    dma_user_cfg.err_callback = (DMA_IRQCallback)I2C_Write_DMAError;
    dma_user_cfg.err_arg = Instance;
    dma_user_cfg.half_callback = (DMA_IRQCallback)I2C_Write_DMAHalfCplt;
    dma_user_cfg.half_arg = Instance;

    i2c_hdl->tx_ctrl.dma_ch = I2C_DMA_Init(&dma_user_cfg);

    if (i2c_hdl->tx_ctrl.dma_ch == DMA_CHANNEL_INVALID) {
        LOG_E("I2C write request DMA channel Failed!\n");
        return LL_ERROR;
    }

    //Transmit config
    i2c_hdl->tx_ctrl.state = I2C_STATE_BUSY_TX;
    i2c_hdl->tx_ctrl.buf = frame->buf;
    i2c_hdl->tx_ctrl.size = frame->buf_len;
    i2c_hdl->tx_ctrl.cnt = 0;
    i2c_hdl->tx_ctrl.isr = NULL;

    //Clear TxFIFO and interrupt pending which will be used following
    __LL_I2C_TxFIFO_Reset(Instance);
    __LL_I2C_SLV_RxAddrAndCmdIsSlvTX_Clr(Instance);
    __LL_I2C_DetStop_Clr(Instance);

    //Enable Tx DMA Requset
    __LL_I2C_TxDMA_En(Instance);

    //Start DMA Transmission in Interrupt mode
    LL_DMA_Start_IT(DMA, i2c_hdl->tx_ctrl.dma_ch, (uint32_t)i2c_hdl->tx_ctrl.buf, (uint32_t)&Instance->TXDATA, i2c_hdl->tx_ctrl.size);

    return LL_OK;
}

/**
  * @brief  SMBUS Master Read an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_MasterRead_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    frame->mem_addr_size = I2C_MEMADDR_SIZE_8BIT;
    frame->mem_addr = frame->smbus_cmd;

    return LL_I2C_MasterRead_DMA(Instance, frame);
}

/**
  * @brief  SMBUS Master Write an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_MasterWrite_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    frame->mem_addr_size = I2C_MEMADDR_SIZE_8BIT;
    frame->mem_addr = frame->smbus_cmd;

    return LL_I2C_MasterWrite_DMA(Instance, frame);
}

/**
  * @brief  SMBUS Slave Read an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_SlaveRead_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    return LL_I2C_SlaveRead_DMA(Instance, frame);
}

/**
  * @brief  SMBUS Slave Write an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @return LL Status
  */
LL_StatusETypeDef LL_SMBUS_SlaveWrite_DMA(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    assert_param(frame != NULL);
    assert_param(frame->buf != NULL);
    assert_param(frame->buf_len);

    if (!IS_I2C_ALL_INSTANCE(Instance) || frame == NULL || frame->buf == NULL || !frame->buf_len) {
        return LL_INVALID;
    }

    return LL_I2C_SlaveWrite_DMA(Instance, frame);
}

#endif

/**
  * @}
  */


/** @defgroup I2C_LL_Exported_Functions_Group3 I2C Read Write Functions Extension
  * @brief    I2C Read Write Functions Extension
  * @{
  */

/**
  * @brief  Transmits in master mode an amount of data in blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Master_Transmit(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_MasterWrite_CPU(Instance, &frame, Timeout);
}

/**
  * @brief  Receives in master mode an amount of data in blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be received
  * @param  Timeout Timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Master_Receive(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_MasterRead_CPU(Instance, &frame, Timeout);
}

/**
  * @brief  Transmits in slave mode an amount of data in blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Slave_Transmit(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_SlaveWrite_CPU(Instance, &frame, Timeout);
}

/**
  * @brief  Receive in slave mode an amount of data in blocking mode
  * @param  Instance Specifies I2C peripheral
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be received
  * @param  Timeout Timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Slave_Receive(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_SlaveRead_CPU(Instance, &frame, Timeout);
}


/**
  * @brief  Transmit in master mode an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Master_Transmit_IT(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_MasterWrite_IT(Instance, &frame);
}

/**
  * @brief  Receive in master mode an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be received
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Master_Receive_IT(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_MasterRead_IT(Instance, &frame);
}

/**
  * @brief  Transmit in slave mode an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Slave_Transmit_IT(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_SlaveWrite_IT(Instance, &frame);
}

/**
  * @brief  Receive in slave mode an amount of data in non-blocking mode with Interrupt
  * @param  Instance Specifies I2C peripheral
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be received
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Slave_Receive_IT(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_SlaveRead_IT(Instance, &frame);
}


#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  Transmit in master mode an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Master_Transmit_DMA(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_MasterWrite_DMA(Instance, &frame);
}

/**
  * @brief  Receive in master mode an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be received
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Master_Receive_DMA(I2C_TypeDef *Instance, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_MasterRead_DMA(Instance, &frame);
}

/**
  * @brief  Transmit in slave mode an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Slave_Transmit_DMA(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_SlaveWrite_DMA(Instance, &frame);
}

/**
  * @brief  Receive in slave mode an amount of data in non-blocking mode with DMA
  * @param  Instance Specifies I2C peripheral
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be received
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Slave_Receive_DMA(I2C_TypeDef *Instance, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.buf = pData;
    frame.buf_len = Size;
    frame.mem_addr_size = I2C_MEMADDR_SIZE_INVALID;

    return LL_I2C_SlaveRead_DMA(Instance, &frame);
}

#endif


/**
  * @brief  Write an amount of data in blocking mode to a specific memory address
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be written
  * @param  Timeout Timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Mem_Write(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                   I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.mem_addr = MemAddress;
    frame.mem_addr_size = MemAddSize;
    frame.buf = pData;
    frame.buf_len = Size;

    return LL_I2C_MasterWrite_CPU(Instance, &frame, Timeout);
}

/**
  * @brief  Read an amount of data in blocking mode from a specific memory address
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be read
  * @param  Timeout Timeout duration
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Mem_Read(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                  I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.mem_addr = MemAddress;
    frame.mem_addr_size = MemAddSize;
    frame.buf = pData;
    frame.buf_len = Size;

    return LL_I2C_MasterRead_CPU(Instance, &frame, Timeout);
}

/**
  * @brief  Write an amount of data in non-blocking mode with Interrupt to a specific memory address
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be written
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Mem_Write_IT(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                      I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.mem_addr = MemAddress;
    frame.mem_addr_size = MemAddSize;
    frame.buf = pData;
    frame.buf_len = Size;

    return LL_I2C_MasterWrite_IT(Instance, &frame);
}

/**
  * @brief  Read an amount of data in non-blocking mode with Interrupt from a specific memory address
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be Read
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Mem_Read_IT(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                     I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.mem_addr = MemAddress;
    frame.mem_addr_size = MemAddSize;
    frame.buf = pData;
    frame.buf_len = Size;

    return LL_I2C_MasterRead_IT(Instance, &frame);
}

#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  Write an amount of data in non-blocking mode with DMA to a specific memory address
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be written
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Mem_Write_DMA(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                       I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.mem_addr = MemAddress;
    frame.mem_addr_size = MemAddSize;
    frame.buf = pData;
    frame.buf_len = Size;

    return LL_I2C_MasterWrite_DMA(Instance, &frame);
}

/**
  * @brief  Read an amount of data in non-blocking mode with DMA from a specific memory address
  * @param  Instance Specifies I2C peripheral
  * @param  DevAddress Target device address
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be Read
  * @return LL Status
  */
LL_StatusETypeDef LL_I2C_Mem_Read_DMA(I2C_TypeDef *Instance, uint16_t DevAddress, uint32_t MemAddress,
                                      I2C_MemAddrSizeETypeDef MemAddSize, uint8_t *pData, uint16_t Size)
{
    I2C_FrameTypeDef frame;

    if (pData == NULL) {
        return LL_INVALID;
    }

    memset((void *)&frame, 0x0, sizeof frame);
    frame.target_addr = DevAddress;
    frame.mem_addr = MemAddress;
    frame.mem_addr_size = MemAddSize;
    frame.buf = pData;
    frame.buf_len = Size;

    return LL_I2C_MasterRead_DMA(Instance, &frame);
}

#endif

/**
  * @}
  */


/** @defgroup I2C_LL_Exported_Functions_Interrupt I2C Interrupt Handler and Callback
  * @brief    I2C Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  I2C IRQ Handler
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
void LL_I2C_IRQHandler(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;
    uint32_t int_en, int_pending;

    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if (!IS_I2C_ALL_INSTANCE(Instance)) {
        return;
    }

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    //All Interrupt Enalbe and Pending Get
    int_en = __LL_I2C_AllIntEn_Get(Instance);
    int_pending = __LL_I2C_AllIntPnd_Get(Instance);


    //RxFIFO Full Interrupt Pending
    if ((int_en & I2C0_INTREN_RXFIE_Msk) && (int_pending & I2C0_INTR_RXFI_Msk)) {
        //Interrupt Pending auto clear

        if (i2c_hdl->rx_ctrl.isr) {
            i2c_hdl->rx_ctrl.isr(Instance);
        }

        //Callback
        LL_I2C_RxFullCallback(Instance);
    }

    //TxFIFO Empty Interrupt Pending
    if ((int_en & I2C0_INTREN_TXEIE_Msk) && (int_pending & I2C0_INTR_TXEI_Msk)) {
        //Interrupt Pending auto clear

        if (i2c_hdl->tx_ctrl.isr) {
            i2c_hdl->tx_ctrl.isr(Instance);
        }

        //Callback
        LL_I2C_TxEmptyCallback(Instance);
    }

    //RxFIFO Overflow Interrupt Pending
    if ((int_en & I2C0_INTREN_RXOFIE_Msk) && (int_pending & I2C0_INTR_RXOFI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_RxFIFOOverflow_Clr(Instance);

        //Callback
        LL_I2C_RxOverflowCallback(Instance);
    }

    //RxFIFO Underflow Interrupt Pending
    if ((int_en & I2C0_INTREN_RXUFIE_Msk) && (int_pending & I2C0_INTR_RXUFI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_RxFIFOUnderflow_Clr(Instance);

        //Callback
        LL_I2C_RxUnderflowCallback(Instance);
    }

    //TxFIFO Overflow Interrupt Pending
    if ((int_en & I2C0_INTREN_TXOFIE_Msk) && (int_pending & I2C0_INTR_TXOFI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_TxFIFOOverflow_Clr(Instance);

        //Callback
        LL_I2C_TxOverflowCallback(Instance);
    }

    //Arbitration Fail Interrupt Pending
    if ((int_en & I2C0_INTREN_ARBFIE_Msk) && (int_pending & I2C0_INTR_ARBFI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_ArbFail_Clr(Instance);

        //Callback
        LL_I2C_ArbFailCallback(Instance);
    }

    //Bus Error Interrupt Pending
    if ((int_en & I2C0_INTREN_BUSEIE_Msk) && (int_pending & I2C0_INTR_BUSEI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_BusErr_Clr(Instance);

        //Callback
        LL_I2C_BusErrCallback(Instance);
    }

    //Master TxRx Done Interrupt Pending
    if ((int_en & I2C0_INTREN_MDEIE_Msk) && (int_pending & I2C0_INTR_MDEI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_MST_TxRxDone_Clr(Instance);

        //Callback
        LL_I2C_MST_TxRxDoneCallback(Instance);
    }

    //Slave Rx Address and Command is Slave TX Interrupt Pending
    if ((int_en & I2C0_INTREN_TXADIE_Msk) && (int_pending & I2C0_INTR_TXADI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_SLV_RxAddrAndCmdIsSlvTX_Clr(Instance);

        //Callback
        LL_I2C_SLV_RxAddrAndCmdIsSlvTXCallback(Instance);
    }

    //Slave Rx Address and Command is Slave RX Interrupt Pending
    if ((int_en & I2C0_INTREN_RXADIE_Msk) && (int_pending & I2C0_INTR_RXADI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_SLV_RxAddrAndCmdIsSlvRX_Clr(Instance);

        //Callback
        LL_I2C_SLV_RxAddrAndCmdIsSlvRXCallback(Instance);
    }

    //Detect Start Interrupt Pending
    if ((int_en & I2C0_INTREN_STDETIE_Msk) && (int_pending & I2C0_INTR_STDETI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_DetStart_Clr(Instance);

        //Callback
        LL_I2C_DetStartCallback(Instance);
    }

    //Detect Stop Interrupt Pending
    if ((int_en & I2C0_INTREN_SPDETIE_Msk) && (int_pending & I2C0_INTR_SPETI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_DetStop_Clr(Instance);

        if (i2c_hdl->tx_ctrl.cnt >= i2c_hdl->tx_ctrl.size && i2c_hdl->tx_ctrl.isr) {
            i2c_hdl->tx_ctrl.isr(Instance);
        }

        if (i2c_hdl->rx_ctrl.cnt >= i2c_hdl->rx_ctrl.size && i2c_hdl->rx_ctrl.isr) {
            i2c_hdl->rx_ctrl.isr(Instance);
        }

        //Callback
        LL_I2C_DetStopCallback(Instance);
    }

    //Detect Restart Interrupt Pending
    if ((int_en & I2C0_INTREN_RSDETIE_Msk) && (int_pending & I2C0_INTR_RSDETI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_DetRestart_Clr(Instance);

        //Callback
        LL_I2C_DetRestartCallback(Instance);
    }

    //Rx NACK Interrupt Pending
    if ((int_en & I2C0_INTREN_NACKIE_Msk) && (int_pending & I2C0_INTR_NACKI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_RxNACK_Clr(Instance);

        //Callback
        LL_I2C_RxNACKCallback(Instance);
    }

    //Master Detect Alert Signal Interrupt Pending
    if ((int_en & I2C0_INTREN_ALDETIE_Msk) && (int_pending & I2C0_INTR_ALDETI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_MST_DetAlertSig_Clr(Instance);

        //Callback
        LL_I2C_MST_DetAlertSigCallback(Instance);
    }

    //Master Tmext Timeout Interrupt Pending
    if ((int_en & I2C0_INTREN_MEXTOIE_Msk) && (int_pending & I2C0_INTR_MEXTOI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_MST_TmextTimeout_Clr(Instance);

        //Callback
        LL_I2C_MST_TmextTimeoutCallback(Instance);
    }

    //Slave Tsext Timeout Interrupt Pending
    if ((int_en & I2C0_INTREN_SEXTOIE_Msk) && (int_pending & I2C0_INTR_SEXTOI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_SLV_TsextTimeout_Clr(Instance);

        //Callback
        LL_I2C_SLV_TsextTimeoutCallback(Instance);
    }

    //Rx PEC Error Interrupt Pending
    if ((int_en & I2C0_INTREN_PECRXIE_Msk) && (int_pending & I2C0_INTR_PECRXI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_RxPECErr_Clr(Instance);

        //Callback
        LL_I2C_RxPECErrCallback(Instance);
    }

    //Slave Rx General Call Interrupt Pending
    if ((int_en & I2C0_INTREN_RXGCIE_Msk) && (int_pending & I2C0_INTR_RXGCI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_SLV_RxGenCall_Clr(Instance);

        //Callback
        LL_I2C_SLV_RxGenCallCallback(Instance);
    }

    //Master Tx Address Done Interrupt Pending
    if ((int_en & I2C0_INTREN_MTXAIE_Msk) && (int_pending & I2C0_INTR_MTXAI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_MST_TxAddrDone_Clr(Instance);

        //Callback
        LL_I2C_MST_TxAddrDoneCallback(Instance);
    }

    //Slave Wait Tx Data Interrupt Pending
    if ((int_en & I2C0_INTREN_SWTXIE_Msk) && (int_pending & I2C0_INTR_SWTXI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_SLV_WaitTxDat_Clr(Instance);

        //Callback
        LL_I2C_SLV_WaitTxDatCallback(Instance);
    }

    //Master On Hold Interrupt Pending
    if ((int_en & I2C0_INTREN_MOHIE_Msk) && (int_pending & I2C0_INTR_MOHI_Msk)) {
        //Interrupt Pending auto clear

        //Callback
        LL_I2C_MST_OnHoldCallback(Instance);
    }

    //The following features are available for later versions
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        return;
    }

    //Bus Timeout Interrupt Pending
    if ((int_en & I2C0_INTREN_BTOIE_Msk) && (int_pending & I2C0_INTR_BTOI_Msk)) {
        //Clear Interrupt Pending
        __LL_I2C_BusTimeoutPnd_Clr(Instance);

        //Callback
        LL_I2C_BusTimeoutCallback(Instance);
    }
}

/**
  * @brief  I2C RxFIFO Full Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_RxFullCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_RxFullCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C TxFIFO Empty Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_TxEmptyCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_TxEmptyCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C RxFIFO Overflow Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_RxOverflowCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_RxOverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C RxFIFO Underflow Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_RxUnderflowCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_RxUnderflowCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C TxFIFO Overflow Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_TxOverflowCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_TxOverflowCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Arbitration Fail Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_ArbFailCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_ArbFailCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Bus Error Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_BusErrCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_BusErrCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Master TxRx Done Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_MST_TxRxDoneCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_MST_TxRxDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Slave Rx Address and Command is Slave TX Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_SLV_RxAddrAndCmdIsSlvTXCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_SLV_RxAddrAndCmdIsSlvTXCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Slave Rx Address and Command is Slave RX Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_SLV_RxAddrAndCmdIsSlvRXCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_SLV_RxAddrAndCmdIsSlvRXCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Detect Start Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_DetStartCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_DetStartCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Detect Stop Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_DetStopCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_DetStopCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Detect Restart Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_DetRestartCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_DetRestartCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Rx NACK Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_RxNACKCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_RxNACKCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Master Detect Alert Signal Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_MST_DetAlertSigCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_MST_DetAlertSigCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Master Tmext Timeout Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_MST_TmextTimeoutCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_MST_TmextTimeoutCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Slave Tsext Timeout Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_SLV_TsextTimeoutCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_SLV_TsextTimeoutCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Rx PEC Error Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_RxPECErrCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_RxPECErrCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Slave Rx General Call Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_SLV_RxGenCallCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_SLV_RxGenCallCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Master Tx Address Done Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_MST_TxAddrDoneCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_MST_TxAddrDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Slave Wait Tx Data Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_SLV_WaitTxDatCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_SLV_WaitTxDatCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Master On Hold Interrupt Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_MST_OnHoldCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_MST_OnHoldCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C Bus Timeout Interrupt Interrupt Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_BusTimeoutCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);

    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_BusTimeoutCallback could be implemented in the user file
     */
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/
/** @addtogroup I2C_LL_Private_Functions
  * @{
  */

/**
  * @brief  I2C Handle Get
  * @param  Instance Specifies I2C peripheral
  * @return I2C_HandleTypeDef pointer
  */
static I2C_HandleTypeDef *I2C_Handle_Get(I2C_TypeDef *Instance)
{
    //Assert param
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if (Instance == I2C0) {
        return &i2c_hdl_global[I2C_INSTANCE_0];
    } else if (Instance == I2C1) {
        return &i2c_hdl_global[I2C_INSTANCE_1];
    } else if (Instance == I2C2) {
        return &i2c_hdl_global[I2C_INSTANCE_2];
    }

    return NULL;
}

/**
  * @brief  I2C Read Detect Stop Interrupt Service Routine
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
static void I2C_Read_DetStop_ISR(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    if (i2c_hdl->rx_ctrl.cnt >= i2c_hdl->rx_ctrl.size) {
        //Disable Detect Stop Interrupt and clear Tx Done
        __LL_I2C_DetStop_INT_Dis(Instance);
        __LL_I2C_MST_TxRxDone_Clr(Instance);

        i2c_hdl->rx_ctrl.isr = NULL;
        i2c_hdl->rx_ctrl.state = I2C_STATE_READY;

        //Rx Complete Callback
        if (i2c_hdl->user_callback.RxCpltCallback) {
            i2c_hdl->user_callback.RxCpltCallback();
        }
    }
}

/**
  * @brief  I2C read data handle in Interrupt mode
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
static void I2C_Read_ISR(I2C_TypeDef *Instance)
{
    uint8_t rx_fifo_trig_lvl;
    I2C_HandleTypeDef *i2c_hdl;

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    rx_fifo_trig_lvl = __LL_I2C_RxFIFOFullThres_Get(Instance);

    //Read data from RxFIFO
    while (rx_fifo_trig_lvl-- && i2c_hdl->rx_ctrl.cnt < i2c_hdl->rx_ctrl.size) {
        *i2c_hdl->rx_ctrl.buf = (uint8_t)__LL_I2C_Dat_Read(Instance);
        i2c_hdl->rx_ctrl.buf++;
        i2c_hdl->rx_ctrl.cnt++;
    }

    //Read Complete
    if (i2c_hdl->rx_ctrl.cnt >= i2c_hdl->rx_ctrl.size) {
        //Disable RxFIFO Full interrupt
        __LL_I2C_RxFIFOFull_INT_Dis(Instance);

        //Switch isr to Detect Stop ISR
        i2c_hdl->rx_ctrl.isr = I2C_Read_DetStop_ISR;

        //Detect Stop Interrupt Enable
        __LL_I2C_DetStop_INT_En(Instance);
    }
}

/**
  * @brief  I2C Write Detect Stop Interrupt Service Routine
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
static void I2C_Write_DetStop_ISR(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    if (i2c_hdl->tx_ctrl.cnt >= i2c_hdl->tx_ctrl.size) {
        //Disable Detect Stop Interrupt and clear Tx Done
        __LL_I2C_DetStop_INT_Dis(Instance);
        __LL_I2C_MST_TxRxDone_Clr(Instance);

        i2c_hdl->tx_ctrl.isr = NULL;
        i2c_hdl->tx_ctrl.state = I2C_STATE_READY;

        //Tx Complete Callback
        if (i2c_hdl->user_callback.TxCpltCallback) {
            i2c_hdl->user_callback.TxCpltCallback();
        }
    }
}

/**
  * @brief  I2C write data handle in Interrupt mode
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
static void I2C_Write_ISR(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    //Write data to TxFIFO
    if (!__LL_I2C_IsTxFIFOFull(Instance) && i2c_hdl->tx_ctrl.cnt < i2c_hdl->tx_ctrl.size) {
        __LL_I2C_Dat_Write(Instance, *i2c_hdl->tx_ctrl.buf);
        i2c_hdl->tx_ctrl.buf++;
        i2c_hdl->tx_ctrl.cnt++;
    }

    //Tx Complete
    if (i2c_hdl->tx_ctrl.cnt >= i2c_hdl->tx_ctrl.size) {
        //Disable TxFIFO Empty interrupt
        __LL_I2C_TxFIFOEmpty_INT_Dis(Instance);

        //Switch isr to Detect Stop ISR
        i2c_hdl->tx_ctrl.isr = I2C_Write_DetStop_ISR;

        //Detect Stop Interrupt Enable
        __LL_I2C_DetStop_INT_En(Instance);
    }
}


#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  I2C DMA Init
  * @param  dma_user_cfg user dma config pointer
  * @return DMA_ChannelETypeDef
  */
static DMA_ChannelETypeDef I2C_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg)
{
    LL_StatusETypeDef ret;
    DMA_ChannelETypeDef ch;

    if (dma_user_cfg == NULL) {
        return DMA_CHANNEL_INVALID;
    }

    /* User DAM channel request */
    ch = LL_DMA_ChannelRequest();

    if (ch == DMA_CHANNEL_INVALID) {
        LOG_E("Requset DMA channel Fail!\n");
        return DMA_CHANNEL_INVALID;
    }

    /* User DMA init */
    ret = LL_DMA_Init(DMA, ch, dma_user_cfg);

    if (ret != LL_OK) {
        LOG_E("DMA LL init fail!\n");
        LL_DMA_ChannelRelease(ch);
        return DMA_CHANNEL_INVALID;
    }

    return ch;
}

/**
  * @brief  I2C DMA DeInit
  * @param  ch DMA channel to Deinit
  * @return None
  */
static void I2C_DMA_DeInit(DMA_ChannelETypeDef ch)
{
    if (ch == DMA_CHANNEL_INVALID) {
        return;
    }

    LL_DMA_Stop_IT(DMA, ch);
    LL_DMA_DeInit(DMA, ch);
    LL_DMA_ChannelRelease(ch);
}

/**
  * @brief  I2C Write with DMA process complete callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
static void I2C_Write_DMACplt(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    //Disable Tx DMA Request
    __LL_I2C_TxDMA_Dis(Instance);

    //DMA DeInit
    I2C_DMA_DeInit(i2c_hdl->tx_ctrl.dma_ch);
    i2c_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    i2c_hdl->tx_ctrl.cnt = i2c_hdl->tx_ctrl.size;

    //Switch isr to Detect Stop ISR
    i2c_hdl->tx_ctrl.isr = I2C_Write_DetStop_ISR;

    //Detect Stop Interrupt Enable
    __LL_I2C_DetStop_INT_En(Instance);
}

/**
  * @brief  I2C Read with DMA process complete callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
static void I2C_Read_DMACplt(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    //Disable Rx DMA Request
    __LL_I2C_RxDMA_Dis(Instance);

    //DMA DeInit
    I2C_DMA_DeInit(i2c_hdl->rx_ctrl.dma_ch);
    i2c_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    i2c_hdl->rx_ctrl.cnt = i2c_hdl->rx_ctrl.size;

    //Switch isr to Detect Stop ISR
    i2c_hdl->rx_ctrl.isr = I2C_Read_DetStop_ISR;

    //Detect Stop Interrupt Enable
    __LL_I2C_DetStop_INT_En(Instance);
}

/**
  * @brief  I2C Write with DMA process half complete callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
static void I2C_Write_DMAHalfCplt(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    //Tx Half Complete Callback
    if (i2c_hdl->user_callback.TxHalfCpltCallback) {
        i2c_hdl->user_callback.TxHalfCpltCallback();
    }
}

/**
  * @brief  I2C Read with DMA process half complete callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
static void I2C_Read_DMAHalfCplt(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    //Rx Half Complete Callback
    if (i2c_hdl->user_callback.RxHalfCpltCallback) {
        i2c_hdl->user_callback.RxHalfCpltCallback();
    }
}

/**
  * @brief  I2C Write with DMA error callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
static void I2C_Write_DMAError(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    //Disable Tx DMA Request
    __LL_I2C_TxDMA_Dis(Instance);

    //Tx DMA DeInit
    I2C_DMA_DeInit(i2c_hdl->tx_ctrl.dma_ch);

    i2c_hdl->tx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    i2c_hdl->tx_ctrl.state = I2C_STATE_READY;

    if (i2c_hdl->user_callback.ErrorCallback) {
        i2c_hdl->user_callback.ErrorCallback();
    }
}

/**
  * @brief  I2C Read with DMA error callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
static void I2C_Read_DMAError(I2C_TypeDef *Instance)
{
    I2C_HandleTypeDef *i2c_hdl;

    //I2C handle get
    i2c_hdl = I2C_Handle_Get(Instance);

    if (i2c_hdl == NULL) {
        LOG_E("Get I2C handle error!\n");
        return;
    }

    //Disable Rx DMA Request
    __LL_I2C_RxDMA_Dis(Instance);

    //Rx DMA DeInit
    I2C_DMA_DeInit(i2c_hdl->rx_ctrl.dma_ch);

    i2c_hdl->rx_ctrl.dma_ch = DMA_CHANNEL_INVALID;
    i2c_hdl->rx_ctrl.state = I2C_STATE_READY;

    if (i2c_hdl->user_callback.ErrorCallback) {
        i2c_hdl->user_callback.ErrorCallback();
    }
}

#endif

/**
  * @}
  */

#endif  /* LL_I2C_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

