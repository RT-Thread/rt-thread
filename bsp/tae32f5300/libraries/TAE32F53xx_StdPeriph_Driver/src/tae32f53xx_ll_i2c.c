/**
  ******************************************************************************
  * @file    tae32f53xx_ll_i2c.c
  * @author  MCD Application Team
  * @brief   I2C LL Module Driver.
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

#define DBG_TAG             "I2C"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup I2C_LL I2C LL
  * @brief    I2C LL Module Driver
  * @{
  */

#ifdef LL_I2C_MODULE_ENABLED

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/** @defgroup I2C_LL_Private_Types I2C LL Private Types
  * @brief    I2C LL Private Types
  * @{
  */

/**
  * @brief I2C LL Config Type Definition
  */

typedef struct __I2C_LLCfgTypeDef {
    bool restart_en;            /*!< Restart enable             */
    bool rxfifo_full_hold_en;   /*!< RXFIFO full hold enable    */
    bool slv_nack_en;           /*!< Slave NACK enable          */
    bool ack_gen_call_en;       /*!< ACK genaral call enable    */
    uint8_t  sda_setup;         /*!< SDA setup time             */
} I2C_LLCfgTypeDef;


/**
  * @}
  */


/* Private macro -------------------------------------------------------------*/
/** @defgroup I2C_LL_Private_Macros I2C LL Private Macros
  * @brief    I2C LL Private Macros
  * @{
  */

/**
  * @brief  I2C Function Alternative
  * @param  flag Condition Flag
  * @param  func_t True Funciton
  * @param  func_f False Function
  * @return None
  */
#define I2C_FUNC_ALTER(flag, func_t, func_f)    \
        do{                                     \
            if((flag)) {                        \
                func_t;                         \
            } else {                            \
                func_f;                         \
            }                                   \
        } while(0)

/**
  * @}
  */


/* Private variables ---------------------------------------------------------*/
/** @defgroup I2C_LL_Private_Variables I2C LL Private Variables
  * @brief    I2C LL Private Variables
  * @{
  */

/**
  * @brief Default I2C Hardware Config
  */
static const I2C_LLCfgTypeDef i2c_ll_cfg_def = {
    .restart_en = true,
    .rxfifo_full_hold_en = false,
    .slv_nack_en = false,
    .ack_gen_call_en = true,
    .sda_setup = 0x64,
};

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/
/** @addtogroup I2C_LL_Private_Functions I2C LL Private function
  * @brief    I2C LL Private function
  * @{
  */

#ifdef LL_DMA_MODULE_ENABLED

    static DMA_ChannelETypeDef LL_I2C_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg);
    static LL_StatusETypeDef LL_I2C_DMA_Deinit(DMA_ChannelETypeDef ch);
    static void LL_I2C_DMA_TXCHEndCallback(void *arg);
    static void LL_I2C_DMA_RXCHEndCallback(void *arg);
    static void LL_I2C_DMA_TXCHErrorCallBck(void *arg);
    static void LL_I2C_DMA_RXCHErrorCallBck(void *arg);

#endif
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup I2C_LL_Exported_Functions I2C LL Exported Functions
  * @brief    I2C LL Exported Functions
  * @{
  */

/** @defgroup I2C_LL_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and de-initialization functions
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
    uint32_t baudrate_cnt;
    I2C_LLCfgTypeDef *ll_cfg = (I2C_LLCfgTypeDef *)&i2c_ll_cfg_def;

    /* Init the low level hardware eg. Clock, NVIC */
    LL_I2C_MspInit(Instance);

    /* Disable all interrupt*/
    CLEAR_REG(Instance->INTRMS);

    /* I2C LL Config */
    //I2C Restart Enable/Disable
    I2C_FUNC_ALTER(ll_cfg->restart_en, __LL_I2C_MST_Restart_En(Instance), __LL_I2C_MST_Restart_Dis(Instance));

    //I2C RXFIFO Full Hold Control
    I2C_FUNC_ALTER(ll_cfg->rxfifo_full_hold_en, __LL_I2C_RxFIFOFullHold_En(Instance), __LL_I2C_RxFIFOFullHold_Dis(Instance));

    //I2C Slave NACK Config
    I2C_FUNC_ALTER(ll_cfg->slv_nack_en, __LL_I2C_SLV_ForceDataNoAck_Set(Instance), __LL_I2C_SLV_ForceDataNoAck_Clr(Instance));

    //I2C ACK Gen Call Config
    I2C_FUNC_ALTER(ll_cfg->ack_gen_call_en, __LL_I2C_AckGenCall_En(Instance), __LL_I2C_AckGenCall_Dis(Instance));

    //I2C Spike Filtered Cnt Config
    __LL_I2C_FsSpkLen_Set(Instance, (uint32_t)50000000 / LL_SYSCTRL_SysclkGet());

    //I2C SDA Timing Config
    __LL_I2C_SDATxHold_Set(Instance, READ_REG(Instance->SSLCNT) >> 1);
    __LL_I2C_SDARxHold_Set(Instance, READ_REG(Instance->SSLCNT) >> 1);
    __LL_I2C_SDA_Setup_Set(Instance, ll_cfg->sda_setup);


    /* I2C user config */
    //I2C Role Mode Config
    I2C_FUNC_ALTER(user_cfg->role == I2C_ROLE_MASTER, __LL_I2C_MASTER_Mode_En(Instance), __LL_I2C_MASTER_Mode_Dis(Instance));
    I2C_FUNC_ALTER(user_cfg->role == I2C_ROLE_MASTER, __LL_I2C_SLAVE_Mode_Dis(Instance), __LL_I2C_SLAVE_Mode_En(Instance));

    //I2C Address Mode Config
    if (user_cfg->role == I2C_ROLE_SLAVE) {
        I2C_FUNC_ALTER(user_cfg->addr_mode == I2C_ADDR_7BIT, __LL_I2C_SLV_7bAddr_Set(Instance), __LL_I2C_SLV_10bAddr_Set(Instance));
    }

    //I2C Speed Mode and Baudrate Config
    assert_param(user_cfg->baudrate);
    baudrate_cnt = LL_SYSCTRL_APB0ClkGet() / user_cfg->baudrate / 2;

    if (user_cfg->baudrate <= I2C_SS_SPEED_MAX) {               //standard speed
        __LL_I2C_Speed_Set(Instance, I2C_SPEED_STD);
        __LL_I2C_SS_SCLHcnt_Set(Instance, baudrate_cnt);
        __LL_I2C_SS_SCLLcnt_Set(Instance, baudrate_cnt);
    } else if (user_cfg->baudrate <= I2C_FS_SPEED_MAX) {        //fast speed
        __LL_I2C_Speed_Set(Instance, I2C_SPEED_FAST);
        __LL_I2C_FS_SCLHcnt_Set(Instance, baudrate_cnt);
        __LL_I2C_FS_SCLLcnt_Set(Instance, baudrate_cnt);
    } else if (user_cfg->baudrate <= I2C_FS_PLUS_SPEED_MAX) {   //fast plus speed
        __LL_I2C_Speed_Set(Instance, I2C_SPEED_FAST);
        __LL_I2C_FS_SCLHcnt_Set(Instance, baudrate_cnt);
        __LL_I2C_FS_SCLLcnt_Set(Instance, baudrate_cnt);
    } else if (user_cfg->baudrate <= I2C_HS_SPEED_MAX) {        //high speed
        LOG_E("Don't support High Speed mode!\n");
        return LL_ERROR;
    } else {
        LOG_E("Invalid baudrate params: %d\n", user_cfg->baudrate);
        return LL_ERROR;
    }

    //I2C Slave Address Config
    __LL_I2C_SAR_Set(Instance, user_cfg->slave_addr);

    //I2C TXFIFO Transmit Data Enable
    __LL_I2C_MST_TxCmdBlock_Clr(Instance);

    if (user_cfg->smbus_enable == ENABLE) {
        __LL_I2C_SMBUS_ClkLowMextTimeout_Set(Instance, user_cfg->smbus_master_extend_clk);
        __LL_I2C_SMBUS_ClkLowSextTimeout_Set(Instance, user_cfg->smbus_slaver_extend_clk);
    }

    //I2C Module Enable
    __LL_I2C_Enable(Instance);

    return LL_OK;
}

/**
  * @brief  I2C LL DeInit
  * @param  Instance Specifies I2C peripheral
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_I2C_DeInit(I2C_TypeDef *Instance)
{
    //I2C Module Disable
    __LL_I2C_Disable(Instance);

    //I2C TXFIFO Transmit Data Disable
    __LL_I2C_MST_TxCmdBlock_Set(Instance);

    /* DeInit the low level hardware eg. Clock, NVIC */
    LL_I2C_MspDeInit(Instance);

    return LL_OK;
}

/**
  * @brief  Initializes the I2C MSP.
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
  * @}
  */


/** @defgroup I2C_LL_Exported_Functions_Group2 Read Write Functions
  * @brief    Read Write Functions
  * @{
  */

/**
  * @brief  I2C LL Master Read by CPU
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @return success read length
  */
uint32_t LL_I2C_MasterRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    uint32_t w_cnt = 0, r_cnt = 0;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    //TAR config
    __LL_I2C_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_RestartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_RestartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_RestartAddr32b(Instance, frame->mem_addr);
    }

    if (frame->buf_len == 1) {
        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //start+TAR, read, then stop
        __LL_I2C_Timing_RestartReadStop(Instance);
    } else {
        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //start+TAR, read
        __LL_I2C_Timing_RestartRead(Instance);

        //read data loop
        for (w_cnt = 0; w_cnt < frame->buf_len - 2; w_cnt++) {
            //wait TXFIFO not full
            while (!__LL_I2C_IsTxFIFONotFull(Instance));

            //Read, send the read signal actually acts as ii_clk
            __LL_I2C_Timing_Read(Instance);

            /* wait RXFIFO not empty */
            while (!__LL_I2C_IsRxFIFONotEmpty(Instance));

            *frame->buf++ = __LL_I2C_DAT_Read(Instance);
            r_cnt++;
        }

        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //read last byte, then stop
        __LL_I2C_Timing_ReadStop(Instance);
    }

    //read remain data
    for (; r_cnt < frame->buf_len; r_cnt++) {
        while (!__LL_I2C_IsRxFIFONotEmpty(Instance));

        *frame->buf++ = __LL_I2C_DAT_Read(Instance);
    }

    /* wait for last data sent */
    while (!__LL_I2C_IsStopDet_Raw(Instance));

    return r_cnt;
}


/**
  * @brief  I2C LL Slave Read by CPU
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
    @param  Timeout Limited operation time
    @note   The slave cannot initiate a read operation, it can only respond to the read request of the master
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_I2C_SlaveRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    while (frame->buf_len > 0U) {
        /* Wait until ReadReq flag is set */
        tickstart = LL_GetTick();

        /* wait RXFIFO not empty */
        while (!__LL_I2C_IsRxFIFONotEmpty(Instance)) {
            if ((LL_GetTick() - tickstart) > Timeout) {
                return LL_TIMEOUT;
            }
        }

        /* Clear ReadReq bit */
        __LL_I2C_SLV_ReadReqRawIntSta_Clr(Instance);

        *frame->buf++ = __LL_I2C_DAT_Read(Instance);
        frame->buf_len--;
    }

    return LL_OK;
}

/**
  * @brief  I2C LL Master Write by CPU
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @return success write length
  */
uint32_t LL_I2C_MasterWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    uint32_t w_cnt = 0;
    bool need_start = false;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    //TAR config
    __LL_I2C_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_RestartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_RestartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_RestartAddr32b(Instance, frame->mem_addr);
    } else {
        need_start = true;
    }

    //write data loop
    for (w_cnt = 0; w_cnt < frame->buf_len - 1; w_cnt++) {
        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //write data
        if (need_start == true) {
            need_start = false;
            __LL_I2C_Timing_RestartWrite(Instance, *frame->buf++);
        } else {
            __LL_I2C_Timing_Write(Instance, *frame->buf++);
        }
    }

    //wait TXFIFO not full
    while (!__LL_I2C_IsTxFIFONotFull(Instance));

    //write last byte, then stop
    if (need_start == true) {
        need_start = false;
        __LL_I2C_Timing_RestartWriteStop(Instance, *frame->buf++);
    } else {
        __LL_I2C_Timing_WriteStop(Instance, *frame->buf++);
    }

    w_cnt++;

    /* wait for last data sent */
    while (__LL_I2C_SLV_IsActivity(Instance));

    return w_cnt;
}


/**
  * @brief  I2C LL Slave Write by CPU
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
    @note   The slave cannot initiate a write request actively, and can only write after the master sends a read command
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_I2C_SlaveWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    while (frame->buf_len > 0U) {
        /* Wait until ReadReq flag is set */
        tickstart = LL_GetTick();

        while (!__LL_I2C_SLV_IsReadReq_Raw(Instance)) {
            if ((LL_GetTick() - tickstart) > Timeout) {
                return LL_TIMEOUT;
            }
        }

        /* I2C Slave Read Request Interrupt Status Clear */
        __LL_I2C_SLV_ReadReqRawIntSta_Clr(Instance);

        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        __LL_I2C_DAT_Write(Instance, *frame->buf++);
        frame->buf_len--;
    }

    //wait slave is not active,to sure data has been sent
    while (__LL_I2C_SLV_IsActivity(Instance));

    return LL_OK;
}


/**
  * @brief  I2C LL Smbus Write by CPU
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @return success write length
  */
uint32_t LL_SMBUS_MasterWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    uint32_t w_cnt = 0;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    //TAR config
    __LL_I2C_TAR_Set(Instance, frame->target_addr);

    //start and send Smbus Command
    __LL_I2C_Timing_RestartAddr8b(Instance, (frame->command & 0xffUL));

    //write data loop
    for (w_cnt = 0; w_cnt < frame->buf_len - 1; w_cnt++) {
        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        __LL_I2C_Timing_Write(Instance, *frame->buf++);
    }

    //wait TXFIFO not full
    while (!__LL_I2C_IsTxFIFONotFull(Instance));

    //write last byte, then stop
    __LL_I2C_Timing_WriteStop(Instance, *frame->buf++);
    w_cnt++;

    /* wait for last data to be sent */
    while (!__LL_I2C_IsStopDet_Raw(Instance));

    return w_cnt;
}


/**
  * @brief  I2C LL Slave Read by CPU
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
    @param  Timeout Limited operation time
    @note   The first command received by the slave is the command sent by the master, not the actual information
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SMBUS_SlaveRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    while (frame->buf_len > 0U) {
        /* Wait until RxFIFO is not empty */
        tickstart = LL_GetTick();

        while (!__LL_I2C_IsRxFIFONotEmpty(Instance)) {
            if ((LL_GetTick() - tickstart) > Timeout) {
                return LL_TIMEOUT;
            }
        }

        *frame->buf++ = __LL_I2C_DAT_Read(Instance);
        frame->buf_len--;
    }

    return LL_OK;
}

/**
  * @brief  I2C LL Smbus Read by CPU
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
  * @return success read length
  */
uint32_t LL_SMBUS_MasterRead_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    uint32_t w_cnt = 0, r_cnt = 0;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    //TAR config
    __LL_I2C_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    __LL_I2C_Timing_RestartAddr8b(Instance, (frame->command & 0xffUL));

    if (frame->buf_len == 1) {
        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //start+TAR, read, then stop
        __LL_I2C_Timing_RestartReadStop(Instance);
    } else {
        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //start+TAR, read
        __LL_I2C_Timing_RestartRead(Instance);

        //read data loop
        for (w_cnt = 0; w_cnt < frame->buf_len - 2; w_cnt++) {
            //wait TXFIFO not full
            while (!__LL_I2C_IsTxFIFONotFull(Instance));

            //Read, send the read signal actually acts as ii_clk
            __LL_I2C_Timing_Read(Instance);

            /* wait RXFIFO not empty */
            while (!__LL_I2C_IsRxFIFONotEmpty(Instance));

            *frame->buf++ = __LL_I2C_DAT_Read(Instance);
            r_cnt++;
        }

        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //read last byte, then stop
        __LL_I2C_Timing_ReadStop(Instance);
    }

    //read remain data
    for (; r_cnt < frame->buf_len; r_cnt++) {
        while (!__LL_I2C_IsRxFIFONotEmpty(Instance));

        *frame->buf++ = __LL_I2C_DAT_Read(Instance);
    }

    /* wait for last data sent */
    while (!__LL_I2C_IsStopDet_Raw(Instance));

    return r_cnt;
}


/**
  * @brief  I2C LL Smbus Write by CPU
  * @param  Instance Specifies I2C peripheral
  * @param  frame write frame pointer
  * @param  Timeout Limited operation time
    @note   The slave cannot initiate a write operation, it can only respond to the read request of the master
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SMBUS_SlaveWrite_CPU(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;

    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    while (frame->buf_len > 0U) {
        /* Wait until ReadReq flag is set */
        tickstart = LL_GetTick();

        while (!__LL_I2C_SLV_IsReadReq_Raw(Instance)) {
            if ((LL_GetTick() - tickstart) > Timeout) {
                return LL_TIMEOUT;
            }
        }

        /* I2C Slave Read Request Interrupt Status Clear */
        __LL_I2C_SLV_ReadReqRawIntSta_Clr(Instance);

        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        __LL_I2C_DAT_Write(Instance, *frame->buf++);
        frame->buf_len--;
    }

    //wait slave is not active,to sure data has been sent
    while (__LL_I2C_SLV_IsActivity(Instance));

    return LL_OK;
}


/**
  * @brief  I2C LL Master Write by interrupt
  * @param  Instance Specifies I2C peripheral
    @note   Put the user code in LL_I2C_TxEmptyCallback
  * @return None
  */
LL_StatusETypeDef LL_SMBUS_MasterWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    __LL_I2C_TxEmpty_INT_Dis(Instance);
    //TAR config
    __LL_I2C_TAR_Set(Instance, frame->target_addr);
    //start and send Smbus Command
    __LL_I2C_Timing_RestartAddr8b(Instance, (frame->command & 0xffUL));

    if (frame->buf_len > 1) {
        //write data
        frame->XferCount = frame->buf_len - 1;

        /* I2C TX Empty Interrupt Enable */
        __LL_I2C_TxEmpty_INT_En(Instance);
    } else {
        __LL_I2C_Timing_WriteStop(Instance, *frame->buf);
    }

    return LL_OK;
}

/**
  * @brief  I2C LL Master Read by interrupt
  * @param  Instance Specifies I2C peripheral
    @note   Put the user code in LL_I2C_RxFullCallback
  * @return None
  */
LL_StatusETypeDef LL_SMBUS_MasterRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    __LL_I2C_TxEmpty_INT_Dis(Instance);

    //TAR config
    __LL_I2C_TAR_Set(Instance, frame->target_addr);
    //start and send read memory address if has memory address to send
    __LL_I2C_Timing_RestartAddr8b(Instance, (frame->command & 0xffUL));

    frame->XferCount = frame->buf_len;

    /* I2C RX Full Interrupt Enable */
    __LL_I2C_RxFull_INT_En(Instance);

    if (frame->buf_len == 1) {
        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //start+TAR, read, then stop
        __LL_I2C_Timing_RestartReadStop(Instance);
    } else {
        //start+TAR, read
        __LL_I2C_Timing_RestartRead(Instance);
        frame->clk_cnt = frame->buf_len - 2;
        frame->XferCount = frame->buf_len;
        /* I2C TX Empty Interrupt Enable */
        __LL_I2C_TxEmpty_INT_En(Instance);
    }

    return LL_OK;
}


/**
  * @brief  I2C LL Slave Write by interrupt
  * @param  Instance Specifies I2C peripheral
    @note   The read operation of the corresponding Master from the Slave, and the data is sent to the Master
            Put the user code in LL_I2C_SlvReadReqCallback
  * @return None
  */
LL_StatusETypeDef LL_SMBUS_SlaveWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->XferCount = frame->buf_len;
    /* I2C Slave Read Request Interrupt Enable */
    __LL_I2C_SLV_ReadReq_INT_En(Instance);

    return LL_OK;
}

/**
  * @brief  I2C LL Slave Write by interrupt
  * @param  Instance Specifies I2C peripheral
    @note   Write operation of the corresponding Master from the slave to save the data
            Put the user code in LL_I2C_SlvReadReqCallback
  * @return None
  */
LL_StatusETypeDef LL_SMBUS_SlaveRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->XferCount = frame->buf_len;
    /* I2C RX Full Interrupt Enable */
    __LL_I2C_RxFull_INT_En(Instance);

    return LL_OK;
}


/**
  * @brief  I2C LL Master Write by interrupt
  * @param  Instance Specifies I2C peripheral
    @note   Put the user code in LL_I2C_TxEmptyCallback
  * @return None
  */
LL_StatusETypeDef LL_I2C_MasterWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    bool need_start = false;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    __LL_I2C_TxEmpty_INT_Dis(Instance);
    //TAR config
    __LL_I2C_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_RestartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_RestartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_RestartAddr32b(Instance, frame->mem_addr);
    } else {
        need_start = true;
    }

    if (frame->buf_len > 1) {
        //write data
        if (need_start == true) {
            need_start = false;
            __LL_I2C_Timing_RestartWrite(Instance, *frame->buf++);
            frame->XferCount = frame->buf_len - 2;
        } else {
            frame->XferCount = frame->buf_len - 1;
        }
    }

    //write last byte, then stop
    if (need_start == true) {
        need_start = false;

        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        __LL_I2C_Timing_RestartWriteStop(Instance, *frame->buf);
    } else {
        /* I2C TX Empty Interrupt Enable */
        __LL_I2C_TxEmpty_INT_En(Instance);
    }

    return LL_OK;
}



/**
  * @brief  I2C LL Slave Write by interrupt
  * @param  Instance Specifies I2C peripheral
    @note   The read operation of the corresponding Master from the Slave, and the data is sent to the Master
            Put the user code in LL_I2C_SlvReadReqCallback
  * @return None
  */
LL_StatusETypeDef LL_I2C_SlaveWrite_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->XferCount = frame->buf_len;

    /* I2C Slave Read Request Interrupt Enable */
    __LL_I2C_SLV_ReadReq_INT_En(Instance);

    return LL_OK;
}


/**
  * @brief  I2C LL Master Read by interrupt
  * @param  Instance Specifies I2C peripheral
    @note   Put the user code in LL_I2C_RxFullCallback
  * @return None
  */
LL_StatusETypeDef LL_I2C_MasterRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    __LL_I2C_TxEmpty_INT_Dis(Instance);
    //TAR config
    __LL_I2C_TAR_Set(Instance, frame->target_addr);
    /* I2C RX Full Interrupt Enable */
    __LL_I2C_RxFull_INT_En(Instance);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_RestartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_RestartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_RestartAddr32b(Instance, frame->mem_addr);
    }

    if (frame->buf_len == 1) {
        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //start+TAR, read, then stop
        __LL_I2C_Timing_RestartReadStop(Instance);
    } else {
        //start+TAR, read
        __LL_I2C_Timing_RestartRead(Instance);
        frame->clk_cnt = frame->buf_len - 2;
        frame->XferCount = frame->buf_len;
        /* I2C TX Empty Interrupt Enable */
        __LL_I2C_TxEmpty_INT_En(Instance);
    }

    return LL_OK;

}

/**
  * @brief  I2C LL Slave Write by interrupt
  * @param  Instance Specifies I2C peripheral
    @note   Write operation of the corresponding Master from the slave to save the data
            Put the user code in LL_I2C_SlvReadReqCallback
  * @return None
  */
LL_StatusETypeDef LL_I2C_SlaveRead_IT(I2C_TypeDef *Instance, I2C_FrameTypeDef *frame)
{
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->XferCount = frame->buf_len;
    /* I2C RX Full Interrupt Enable */
    __LL_I2C_RxFull_INT_En(Instance);

    return LL_OK;
}

#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  I2C LL Slave Write by DMA
  * @param  Instance Specifies I2C peripheral
  * @param  dma_user_cfg user dma config pointer
  * @param  frame write frame pointer
  * @param  Timeout Limited operation time
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_I2C_MasterWrite_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
        I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    bool need_start = false;
    frame->dma_tx_ch = DMA_CHANNEL_INVALID;
    uint32_t tickstart;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->Instance = Instance;
    frame->TXdma_status = IIC_DMA_STATE_RESET;

    dma_user_cfg->end_arg = (void *)frame;
    dma_user_cfg->end_callback = LL_I2C_DMA_TXCHEndCallback;
    dma_user_cfg->err_arg = (void *)frame;
    dma_user_cfg->err_callback = LL_I2C_DMA_TXCHErrorCallBck;

    /* Wait until I2C DMA Init ok */
    tickstart = LL_GetTick();

    while (frame->dma_tx_ch == DMA_CHANNEL_INVALID) {
        frame->dma_tx_ch = LL_I2C_DMA_Init(dma_user_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    frame->TXdma_status = IIC_DMA_STATE_READY;

    /* TAR config */
    __LL_I2C_TAR_Set(Instance, frame->target_addr);

    /* Send read memory address wiht start singal if user has memory address to send */
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_RestartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_RestartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_RestartAddr32b(Instance, frame->mem_addr);
    } else {
        need_start = true;
    }

    /* Enable Transmit DMA func */
    __LL_I2C_TxDMA_En(Instance);

    /* The first data must sent with start singal and the last data should sent with stop singal,
       Remaining data can sent by DMA*/
    if (need_start == true) {
        need_start = false;

        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        __LL_I2C_Timing_RestartWrite(Instance, *frame->buf++);

        if (frame->buf_len > 2) {
            LL_DMA_Start_IT(DMA, frame->dma_tx_ch, (uint32_t)frame->buf, (uint32_t)&Instance->DCMD, frame->buf_len - 1);
            frame->TXdma_status = IIC_DMA_STATE_BUSY;
        } else {
            __LL_I2C_Timing_RestartWriteStop(Instance, *(frame->buf + frame->buf_len - 1));
        }

    } else {
        if (frame->buf_len >= 2) {
            LL_DMA_Start_IT(DMA, frame->dma_tx_ch, (uint32_t)frame->buf, (uint32_t)&Instance->DCMD, frame->buf_len - 1);
            frame->TXdma_status = IIC_DMA_STATE_BUSY;
        } else {
            __LL_I2C_Timing_WriteStop(Instance, *(frame->buf + frame->buf_len - 1));
        }
    }

    return LL_OK;
}


/**
  * @brief  I2C LL Master Read by DMA
  * @param  Instance Specifies I2C peripheral
  * @param  dma_user_cfg user dma config pointer
  * @param  frame Read frame pointer
  * @param  Timeout Limited operation time
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_I2C_MasterRead_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
                                        I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;
    uint32_t clk_cmd = I2C_CMD_READ;
    DMA_UserCfgTypeDef dma_masterclk_cfg;
    frame->dma_tx_ch = DMA_CHANNEL_INVALID;
    frame->dma_rx_ch = DMA_CHANNEL_INVALID;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->Instance = Instance;
    frame->TXdma_status = IIC_DMA_STATE_RESET;
    frame->RXdma_status = IIC_DMA_STATE_RESET;

    dma_user_cfg->end_arg = (void *)frame;
    dma_user_cfg->end_callback = LL_I2C_DMA_RXCHEndCallback;
    dma_user_cfg->err_arg = (void *)frame;
    dma_user_cfg->err_callback = LL_I2C_DMA_RXCHErrorCallBck;

    /* Wait for DMA chn init successful */
    tickstart = LL_GetTick();

    while (frame->dma_rx_ch == DMA_CHANNEL_INVALID) {
        frame->dma_rx_ch = LL_I2C_DMA_Init(dma_user_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    frame->TXdma_status = IIC_DMA_STATE_READY;

    /* Need a DMA chanl send clock singal to Keep communication with slave */
    dma_masterclk_cfg.trans_type = DMA_TRANS_TYPE_M2P;
    dma_masterclk_cfg.src_addr_mode = DMA_SRC_ADDR_MODE_FIX;
    dma_masterclk_cfg.dst_addr_mode = DMA_DST_ADDR_MODE_FIX;
    dma_masterclk_cfg.src_data_width = DMA_SRC_TRANS_WIDTH_16b;
    dma_masterclk_cfg.dst_data_width = DMA_DST_TRANS_WIDTH_16b;
    dma_masterclk_cfg.src_hs_ifc = DMA_SRC_HANDSHAKE_IFC_MEMORY;

    if (Instance == I2C0) {
        dma_masterclk_cfg.dst_hs_ifc = DMA_DST_HANDSHAKE_IFC_I2C0_TX;
    } else {
        dma_masterclk_cfg.dst_hs_ifc = DMA_DST_HANDSHAKE_IFC_I2C1_TX;
    }

    dma_masterclk_cfg.end_arg = (void *)frame;
    dma_masterclk_cfg.end_callback = LL_I2C_DMA_TXCHEndCallback;
    dma_masterclk_cfg.err_arg = (void *)frame;
    dma_masterclk_cfg.err_callback = LL_I2C_DMA_TXCHErrorCallBck;

    /* Wait for DMA chn init successful */
    tickstart = LL_GetTick();

    while (frame->dma_tx_ch == DMA_CHANNEL_INVALID) {
        frame->dma_tx_ch = LL_I2C_DMA_Init(&dma_masterclk_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    frame->RXdma_status = IIC_DMA_STATE_READY;

    /* TAR config */
    __LL_I2C_TAR_Set(Instance, frame->target_addr);

    //start and send read memory address if has memory address to send
    if (frame->mem_addr_size == I2C_MEMADDR_SIZE_8BIT) {
        __LL_I2C_Timing_RestartAddr8b(Instance, (frame->mem_addr & 0xffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_16BIT) {
        __LL_I2C_Timing_RestartAddr16b(Instance, (frame->mem_addr & 0xffffUL));
    } else if (frame->mem_addr_size == I2C_MEMADDR_SIZE_32BIT) {
        __LL_I2C_Timing_RestartAddr32b(Instance, frame->mem_addr);
    }

    /* Enable Transmit/Receive DMA func */
    __LL_I2C_RxDMA_En(Instance);
    __LL_I2C_TxDMA_En(Instance);

    if (frame->buf_len == 1) {
        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //start+TAR, read, then stop
        __LL_I2C_Timing_RestartReadStop(Instance);

        /* Get the last data */
        while (!__LL_I2C_IsRxFIFONotEmpty(Instance));

        *(frame->buf + frame->buf_len - 1) = __LL_I2C_DAT_Read(Instance);

        /* wait for last data sent */
        while (!__LL_I2C_IsStopDet_Raw(Instance));

    } else {

        //start+TAR, read
        __LL_I2C_Timing_RestartRead(Instance);
        /* Indicates how many clk needs to be sent */
        frame->clk_cnt = frame->buf_len - 1;
        /* Master should sent clk to Keep communication with slave,and READ_CMD is U16,means U8 Multiply 2,
           The first data has not save yet,but the clock has been sent. And the last read command need sent
           with Stop Command,so that the length of ch1 is 2*(buf_len -2),and chn0 is buf_len */
        LL_DMA_Start_IT(DMA, frame->dma_tx_ch, (uint32_t)&clk_cmd, (uint32_t)&Instance->DCMD, 2 * (frame->buf_len - 2));
        LL_DMA_Start_IT(DMA, frame->dma_rx_ch, (uint32_t)&Instance->DCMD, (uint32_t)frame->buf, frame->buf_len);

        frame->TXdma_status = IIC_DMA_STATE_BUSY;
        frame->RXdma_status = IIC_DMA_STATE_BUSY;
    }

    /* Return Status */
    return LL_OK;


}


/**
  * @brief  I2C LL Slave Read by DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame Read frame pointer
  * @param  Timeout Limited operation time
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_I2C_SlaveWrite_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
                                        I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;
    frame->dma_tx_ch = DMA_CHANNEL_INVALID;

    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->Instance = Instance;
    frame->TXdma_status = IIC_DMA_STATE_RESET;

    dma_user_cfg->end_arg = (void *)frame;
    dma_user_cfg->end_callback = LL_I2C_DMA_TXCHEndCallback;
    dma_user_cfg->err_arg = (void *)frame;
    dma_user_cfg->err_callback = LL_I2C_DMA_TXCHErrorCallBck;

    /* Wait for DMA chn init successful */
    tickstart = LL_GetTick();

    while (frame->dma_tx_ch == DMA_CHANNEL_INVALID) {
        frame->dma_tx_ch = LL_I2C_DMA_Init(dma_user_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    /* Wait for I2C Slave Read Request Interrupt Status Set */
    tickstart = LL_GetTick();

    while (!__LL_I2C_SLV_IsReadReq_Raw(Instance)) {
        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    /* Enable Transmit DMA func */
    __LL_I2C_TxDMA_En(Instance);
    /* DMA work */
    LL_DMA_Start_IT(DMA, frame->dma_tx_ch, (uint32_t)frame->buf, (uint32_t)&Instance->DCMD, frame->buf_len);
    frame->TXdma_status = IIC_DMA_STATE_BUSY;

    return LL_OK;
}

/**
  * @brief  I2C LL Slave Write by DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame Write frame pointer
  * @param  Timeout Limited operation time
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_I2C_SlaveRead_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
                                       I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;
    frame->dma_rx_ch = DMA_CHANNEL_INVALID;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));
    frame->Instance = Instance;
    frame->RXdma_status = IIC_DMA_STATE_RESET;

    dma_user_cfg->end_arg = (void *)frame;
    dma_user_cfg->end_callback = LL_I2C_DMA_RXCHEndCallback;
    dma_user_cfg->err_arg = (void *)frame;
    dma_user_cfg->err_callback = LL_I2C_DMA_RXCHErrorCallBck;

    /* Wait for DMA chn init successful */
    tickstart = LL_GetTick();

    while (frame->dma_rx_ch == DMA_CHANNEL_INVALID) {
        frame->dma_rx_ch = LL_I2C_DMA_Init(dma_user_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    /* Wait until ReadFIFO is full */
    tickstart = LL_GetTick();

    while (!__LL_I2C_IsRxFIFONotEmpty(Instance)) {
        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    /* Enable Receive DMA func */
    __LL_I2C_RxDMA_En(Instance);
    /* DMA work */
    LL_DMA_Start_IT(DMA, frame->dma_rx_ch, (uint32_t)&Instance->DCMD, (uint32_t)frame->buf, frame->buf_len);
    frame->RXdma_status = IIC_DMA_STATE_BUSY;

    return LL_OK;
}


/**
  * @brief  I2C LL SMBUS Master Write by DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame Write frame pointer
  * @param  Timeout Limited operation time
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SMBUS_MasterWrite_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
        I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;
    frame->dma_tx_ch = DMA_CHANNEL_INVALID;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->Instance = Instance;
    frame->TXdma_status = IIC_DMA_STATE_RESET;

    dma_user_cfg->end_arg = (void *)frame;
    dma_user_cfg->end_callback = LL_I2C_DMA_TXCHEndCallback;
    dma_user_cfg->err_arg = (void *)frame;
    dma_user_cfg->err_callback = LL_I2C_DMA_TXCHErrorCallBck;

    /* Wait until ReadReq flag is set */
    tickstart = LL_GetTick();

    while (frame->dma_tx_ch == DMA_CHANNEL_INVALID) {
        frame->dma_tx_ch = LL_I2C_DMA_Init(dma_user_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    frame->TXdma_status = IIC_DMA_STATE_READY;

    //TAR config
    __LL_I2C_TAR_Set(Instance, frame->target_addr);

    //start and send Smbus Command
    __LL_I2C_Timing_RestartAddr8b(Instance, (frame->command & 0xffUL));

    /* Enable Transmit DMA func */
    __LL_I2C_TxDMA_En(Instance);
    /* DMA work */
    LL_DMA_Start_IT(DMA, frame->dma_tx_ch, (uint32_t)frame->buf, (uint32_t)&Instance->DCMD, frame->buf_len - 1);
    frame->TXdma_status = IIC_DMA_STATE_BUSY;

    return LL_OK;
}

/**
  * @brief  I2C LL SMBUS Master Write by DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame Read frame pointer
  * @param  Timeout Limited operation time
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SMBUS_MasterRead_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
        I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;
    uint32_t clk_cmd = I2C_CMD_READ;
    DMA_UserCfgTypeDef dma_masterclk_cfg;
    frame->dma_tx_ch = DMA_CHANNEL_INVALID;
    frame->dma_rx_ch = DMA_CHANNEL_INVALID;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->Instance = Instance;
    frame->TXdma_status = IIC_DMA_STATE_RESET;
    frame->RXdma_status = IIC_DMA_STATE_RESET;

    dma_user_cfg->end_arg = (void *)frame;
    dma_user_cfg->end_callback = LL_I2C_DMA_RXCHEndCallback;
    dma_user_cfg->err_arg = (void *)frame;
    dma_user_cfg->err_callback = LL_I2C_DMA_RXCHErrorCallBck;

    /* Wait for DMA chn init successful */
    tickstart = LL_GetTick();

    while (frame->dma_rx_ch == DMA_CHANNEL_INVALID) {
        frame->dma_rx_ch = LL_I2C_DMA_Init(dma_user_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    frame->TXdma_status = IIC_DMA_STATE_READY;
    /* Need a DMA chanl send clock singal to Keep communication with slave */
    dma_masterclk_cfg.trans_type = DMA_TRANS_TYPE_M2P;
    dma_masterclk_cfg.src_addr_mode = DMA_SRC_ADDR_MODE_FIX;
    dma_masterclk_cfg.dst_addr_mode = DMA_DST_ADDR_MODE_FIX;
    dma_masterclk_cfg.src_data_width = DMA_SRC_TRANS_WIDTH_16b;
    dma_masterclk_cfg.dst_data_width = DMA_DST_TRANS_WIDTH_16b;
    dma_masterclk_cfg.src_hs_ifc = DMA_SRC_HANDSHAKE_IFC_MEMORY;

    if (Instance == I2C0) {
        dma_masterclk_cfg.dst_hs_ifc = DMA_DST_HANDSHAKE_IFC_I2C0_TX;
    } else {
        dma_masterclk_cfg.dst_hs_ifc = DMA_DST_HANDSHAKE_IFC_I2C1_TX;
    }

    dma_masterclk_cfg.end_arg = (void *)frame;
    dma_masterclk_cfg.end_callback = LL_I2C_DMA_TXCHEndCallback;
    dma_masterclk_cfg.err_arg = (void *)frame;
    dma_masterclk_cfg.err_callback = LL_I2C_DMA_TXCHErrorCallBck;

    /* Wait for DMA chn init successful */
    tickstart = LL_GetTick();

    while (frame->dma_tx_ch == DMA_CHANNEL_INVALID) {
        frame->dma_tx_ch = LL_I2C_DMA_Init(&dma_masterclk_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    frame->RXdma_status = IIC_DMA_STATE_READY;
    //TAR config
    __LL_I2C_TAR_Set(Instance, frame->target_addr);

    //start and send Smbus command
    __LL_I2C_Timing_RestartAddr8b(Instance, (frame->command & 0xffUL));

    /* Enable Transmit/Receive DMA func */
    __LL_I2C_RxDMA_En(Instance);
    __LL_I2C_TxDMA_En(Instance);

    if (frame->buf_len == 1) {
        //wait TXFIFO not full
        while (!__LL_I2C_IsTxFIFONotFull(Instance));

        //start+TAR, read, then stop
        __LL_I2C_Timing_RestartReadStop(Instance);

        /* Get the last data */
        while (!__LL_I2C_IsRxFIFONotEmpty(Instance));

        *(frame->buf + frame->buf_len - 1) = __LL_I2C_DAT_Read(Instance);

        /* wait for last data sent */
        while (!__LL_I2C_IsStopDet_Raw(Instance));

    } else {
        //start+TAR, read
        __LL_I2C_Timing_RestartRead(Instance);
        /* Indicates how many clk needs to be sent */
        frame->clk_cnt = frame->buf_len - 1;

        /* Master should sent clk to Keep communication with slave,and READ_CMD is U16,means U8 Multiply 2,
           The first data has not save yet,but the clock has been sent. And the last read command need sent
           with Stop Command,so that the length of ch1 is 2*(buf_len -2),and chn0 is buf_len */
        LL_DMA_Start_IT(DMA, frame->dma_tx_ch, (uint32_t)&clk_cmd, (uint32_t)&Instance->DCMD, 2 * (frame->buf_len - 2));
        LL_DMA_Start_IT(DMA, frame->dma_rx_ch, (uint32_t)&Instance->DCMD, (uint32_t)frame->buf, frame->buf_len);
        frame->TXdma_status = IIC_DMA_STATE_BUSY;
        frame->RXdma_status = IIC_DMA_STATE_BUSY;
    }

    /* Return Status */
    return LL_OK;
}

/**
  * @brief  I2C LL Slave Write by DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame read frame pointer
    @param  Timeout Limited operation time
    @note   The first command received by the slave is the command sent by the master, not the actual information
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SMBUS_SlaveWrite_DMA(I2C_TypeDef *Instance,  DMA_UserCfgTypeDef *dma_user_cfg,
        I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;
    frame->dma_tx_ch = DMA_CHANNEL_INVALID;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->Instance = Instance;
    frame->TXdma_status = IIC_DMA_STATE_RESET;

    dma_user_cfg->end_arg = (void *)frame;
    dma_user_cfg->end_callback = LL_I2C_DMA_TXCHEndCallback;
    dma_user_cfg->err_arg = (void *)frame;
    dma_user_cfg->err_callback = LL_I2C_DMA_TXCHErrorCallBck;

    /* Wait for DMA chn init successful */
    tickstart = LL_GetTick();

    while (frame->dma_tx_ch == DMA_CHANNEL_INVALID) {
        frame->dma_tx_ch = LL_I2C_DMA_Init(dma_user_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    /* Wait until ReadReq flag is set */
    tickstart = LL_GetTick();

    /* Make sure slave readreq flag is set, it can't be clear when transmit by DMA */
    while (!__LL_I2C_SLV_IsReadReq_Raw(Instance)) {
        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    /* Enable Transmit DMA func */
    __LL_I2C_TxDMA_En(Instance);

    /* DMA work */
    LL_DMA_Start_IT(DMA, frame->dma_tx_ch, (uint32_t)frame->buf, (uint32_t)&Instance->DCMD, frame->buf_len);
    frame->TXdma_status = IIC_DMA_STATE_BUSY;
    /* Return Status */
    return LL_OK;
}


/**
  * @brief  I2C LL SMBUS Slave Read by DMA
  * @param  Instance Specifies I2C peripheral
  * @param  frame Wrute frame pointer
  * @param  Timeout Limited operation time
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_SMBUS_SlaveRead_DMA(I2C_TypeDef *Instance, DMA_UserCfgTypeDef *dma_user_cfg,
        I2C_FrameTypeDef *frame, uint32_t Timeout)
{
    uint32_t tickstart;
    frame->dma_rx_ch = DMA_CHANNEL_INVALID;
    /* Check the I2C initiation struct allocation */
    assert_param(IS_I2C_ALL_INSTANCE(Instance));

    if ((frame->buf == NULL) || (frame->buf_len == 0U)) {
        return LL_ERROR;
    }

    frame->Instance = Instance;
    frame->RXdma_status = IIC_DMA_STATE_RESET;

    dma_user_cfg->end_arg = (void *)frame;
    dma_user_cfg->end_callback = LL_I2C_DMA_TXCHEndCallback;
    dma_user_cfg->err_arg = (void *)frame;
    dma_user_cfg->err_callback = LL_I2C_DMA_TXCHErrorCallBck;

    /* Wait for DMA chn init successful */
    tickstart = LL_GetTick();

    while (frame->dma_tx_ch == DMA_CHANNEL_INVALID) {
        frame->dma_tx_ch = LL_I2C_DMA_Init(dma_user_cfg);

        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    /* Wait until ReadReq flag is set */
    tickstart = LL_GetTick();

    while (!__LL_I2C_SLV_IsReadReq_Raw(Instance)) {
        if ((LL_GetTick() - tickstart) > Timeout) {
            return LL_TIMEOUT;
        }
    }

    /* I2C Slave Read Request Interrupt Status Clear */
    __LL_I2C_SLV_ReadReqRawIntSta_Clr(Instance);

    /* Enable Receive DMA func */
    __LL_I2C_RxDMA_En(Instance);
    /* DMA work */
    LL_DMA_Start_IT(DMA, frame->dma_rx_ch, (uint32_t)&Instance->DCMD, (uint32_t)frame->buf, frame->buf_len);
    frame->RXdma_status = IIC_DMA_STATE_BUSY;

    /* Return Status */
    return LL_OK;
}
#endif
/**
  * @}
  */

/** @defgroup I2C_LL_Exported_Functions_Group3 Interrupt handler and call back
  * @brief    Interrupt handler and call back
  * @{
  */

/**
  * @brief  I2C IRQ Handler
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
void LL_I2C_IRQHandler(I2C_TypeDef *Instance, I2C_FrameTypeDef *irq_frame)
{
    uint32_t i2c_int_sta = __LL_I2C_IntSta_Get(Instance);

    if (i2c_int_sta & I2C_SCL_STK_AT_LOW_INT_STA_Msk) {
        LL_I2C_SCLStuckAtLowCallback(Instance);
    }

    if (i2c_int_sta & I2C_MST_ON_HOLD_INT_STA_Msk) {
        LL_I2C_MstOnHoldCallback(Instance);
    }

    if (i2c_int_sta & I2C_RESTART_DET_INT_STA_Msk) {
        LL_I2C_SlvRestartDetCallback(Instance);
    }

    if (i2c_int_sta & I2C_GEN_CALL_INT_STA_Msk) {
        __LL_I2C_SLV_GenCallRawIntSta_Clr(Instance);
        LL_I2C_SlvGenCallCallback(Instance);
    }

    if (i2c_int_sta & I2C_START_DET_INT_STA_Msk) {
        __LL_I2C_StartDetRawIntSta_Clr(Instance);
        LL_I2C_StartDetCallback(Instance);
    }

    if (i2c_int_sta & I2C_STOP_DET_INT_STA_Msk) {
        __LL_I2C_StopDetRawIntSta_Clr(Instance);
        LL_I2C_StopDetCallback(Instance);
    }

    if (i2c_int_sta & I2C_ACTIVITY_INT_STA_Msk) {
        __LL_I2C_ActivityRawIntSta_Clr(Instance);
        LL_I2C_ActivityCallback(Instance);
    }

    if (i2c_int_sta & I2C_RX_DONE_INT_STA_Msk) {
        __LL_I2C_SLV_RxDoneRawIntSta_Clr(Instance);
        LL_I2C_SlvRxDoneCallback(Instance);
    }

    if (i2c_int_sta & I2C_TX_ABRT_INT_STA_Msk) {
        __LL_I2C_TxAbortRawIntSta_Clr(Instance);
        LL_I2C_TxAbortCallback(Instance);
    }

    if (i2c_int_sta & I2C_RD_REQ_INT_STA_Msk) {
        __LL_I2C_SLV_ReadReqRawIntSta_Clr(Instance);

        if ((irq_frame != NULL) && (irq_frame->buf_len != NULL)) {

            //wait TXFIFO not full
            while (!__LL_I2C_IsTxFIFONotFull(Instance));

            __LL_I2C_DAT_Write(Instance, *irq_frame->buf++);
            irq_frame->XferCount--;

            if (irq_frame->XferCount == 0x0UL) {
                /* I2C Slave Read Request Interrupt Disable */
                __LL_I2C_SLV_ReadReq_INT_Dis(Instance);
                irq_frame->buf = NULL;
            }

        }

        LL_I2C_SlvReadReqCallback(Instance);
    }

    if (i2c_int_sta & I2C_TX_EMPTY_INT_STA_Msk) {
        //Auto clear according to TXFIFO status
        if ((irq_frame != NULL) && (irq_frame->buf_len != NULL)) {
            //wait TXFIFO not full
            while (!__LL_I2C_IsTxFIFONotFull(Instance));

            if (irq_frame->clk_cnt == 0x0UL) {
                /* Write data to DCMD */
                __LL_I2C_DAT_Write(Instance, *irq_frame->buf++);

                irq_frame->XferCount--;

                /* wait for transmit finish by interrupt */
                if (irq_frame->XferCount == 0x0UL) {
                    __LL_I2C_Timing_WriteStop(Instance, *irq_frame->buf);
                    /* I2C TX Empty Interrupt Disable */
                    __LL_I2C_TxEmpty_INT_Dis(Instance);
                    irq_frame->buf = NULL;
                }
            } else {
                //Read, send the read signal actually acts as ii_clk
                __LL_I2C_Timing_Read(Instance);
                irq_frame->clk_cnt --;

                if (irq_frame->clk_cnt == 0) {
                    //read last byte, then stop
                    __LL_I2C_Timing_ReadStop(Instance);
                    /* I2C TX Empty Interrupt Disable */
                    __LL_I2C_TxEmpty_INT_Dis(Instance);

                }
            }
        }

        LL_I2C_TxEmptyCallback(Instance);
    }

    if (i2c_int_sta & I2C_TX_OVER_INT_STA_Msk) {
        __LL_I2C_TxOverRawIntSta_Clr(Instance);
        LL_I2C_TxOverCallback(Instance);
    }

    if (i2c_int_sta & I2C_RX_FULL_INT_STA_Msk) {
        //Auto clear according to RXFIFO status
        if ((irq_frame != NULL) && (irq_frame->buf_len != NULL)) {
            /* wait RXFIFO not empty */
            while (!__LL_I2C_IsRxFIFONotEmpty(Instance));

            /* Read data from DCMD */
            *irq_frame->buf++ = __LL_I2C_DAT_Read(Instance);
            irq_frame->XferCount--;

            if (irq_frame->XferCount == 0) {
                /* I2C RX Full Interrupt Disable */
                __LL_I2C_RxFull_INT_Dis(Instance);
                irq_frame->buf = NULL;
            }
        }

        LL_I2C_RxFullCallback(Instance);
    }

    if (i2c_int_sta & I2C_RX_OVER_INT_STA_Msk) {
        __LL_I2C_RxOverRawIntSta_Clr(Instance);
        LL_I2C_RxOverCallback(Instance);
    }

    if (i2c_int_sta & I2C_RX_UNDER_INT_STA_Msk) {
        __LL_I2C_RxUnderRawIntSta_Clr(Instance);
        LL_I2C_RxUnderCallback(Instance);
    }

    if (__LL_I2C_SMBUS_IsMstClkExtendTimeout(Instance)) {
        __LL_I2C_SMBUS_MstClkExtendTimeoutRawIntSta_Clr(Instance);
        LL_SMBUS_MstClkExtTimeoutCallback(Instance);
    }

    if (__LL_I2C_SMBUS_IsSlvClkExtendTimeout(Instance)) {
        __LL_I2C_SMBUS_SlvClkExtendTimeoutRawIntSta_Clr(Instance);
        LL_SMBUS_SlvClkExtTimeoutCallback(Instance);
    }
}

/**
  * @brief  I2C SCL stuck at low interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_SCLStuckAtLowCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_SCLStuckAtLowCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C master on hold interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_MstOnHoldCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_MstOnHoldCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C slave restart detect interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_SlvRestartDetCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_SlvRestartDetCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C slave genaral call interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_SlvGenCallCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_SlvGenCallCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C start detect interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_StartDetCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_StartDetCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C stop detect interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_StopDetCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_StopDetCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C activity interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_ActivityCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_ActivityCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C slave rx done interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_SlvRxDoneCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_SlvRxDoneCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C tx abort interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_TxAbortCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_TxAbortCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C slave read request interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_SlvReadReqCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_SlvReadReqCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C tx empty interrupt callback
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
  * @brief  I2C tx over interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_TxOverCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_TxOverCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C rx full interrupt callback
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
  * @brief  I2C rx over interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_RxOverCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_RxOverCallback could be implemented in the user file
     */
}

/**
  * @brief  I2C rx under interrupt callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_I2C_RxUnderCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_I2C_RxUnderCallback could be implemented in the user file
     */
}
/**
  * @}
  */


/**
  * @brief  SMBUS SlvClkExtendTimeout Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_SMBUS_SlvClkExtTimeoutCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SMBUS_SlvClkExtTimeoutCallback could be implemented in the user file
     */

}

/**
  * @brief  SMBUS MstClkExtendTimeout Callback
  * @param  Instance Specifies I2C peripheral
  * @return None
  */
__WEAK void LL_SMBUS_MstClkExtTimeoutCallback(I2C_TypeDef *Instance)
{
    /* Prevent unused argument(s) compilation warning */
    LL_UNUSED(Instance);
    /* NOTE: This function should not be modified, when the callback is needed,
             the LL_SMBUS_MstClkExtTimeoutCallback could be implemented in the user file
     */

}


/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup I2C_LL_Private_Functions I2C LL Private function
  * @brief    I2C LL Private function
  * @{
  */
#ifdef LL_DMA_MODULE_ENABLED

/**
  * @brief  I2C LL DMA Init
  * @param  dma_user_cfg user dma config pointer
  * @param  Timeout Limited operation time
  * @return DMA_ChannelETypeDef
  */
static DMA_ChannelETypeDef LL_I2C_DMA_Init(DMA_UserCfgTypeDef *dma_user_cfg)
{
    DMA_ChannelETypeDef ch = DMA_CHANNEL_INVALID;
    int ret;

    /* User DAM channel request */
    ch = LL_DMA_ChannelRequest();

    if (ch == DMA_CHANNEL_INVALID) {
        LOG_E("Requset DMA channel Fail!\n");
        return DMA_CHANNEL_INVALID;
    }

    /* User DMA init */
    ret = LL_DMA_Init(DMA, ch, dma_user_cfg);

    if (ret) {
        LOG_E("DMA LL init fail!\n");
        LL_DMA_ChannelRelease(ch);
        ch = DMA_CHANNEL_INVALID;
        return DMA_CHANNEL_INVALID;
    }

    return ch;
}


/**
  * @brief  I2C LL DMA Deinit
  * @param  Instance Specifies I2C peripheral
  * @param  frame frame pointer
  * @return LL_StatusETypeDef
  */
static LL_StatusETypeDef LL_I2C_DMA_Deinit(DMA_ChannelETypeDef ch)
{
    /* DMA stop work */
    LL_DMA_Stop_IT(DMA, ch);

    /* Deinit DMA after tranfer completed */
    LL_DMA_DeInit(DMA, ch);

    /* DMA LL channel release */
    LL_DMA_ChannelRelease(ch);

    return LL_OK;
}


/**
  * @brief  I2C DMA TX Channel complete callback
  * @param  arg Unlimited parameter
  * @return None
  */
static void LL_I2C_DMA_TXCHEndCallback(void *arg)
{
    I2C_FrameTypeDef *p_frame = ((I2C_FrameTypeDef *)arg);

    /* The last frame of the Master needs to be sent with stop */
    if (__LL_I2C_IsMasterMode(p_frame->Instance) == ENABLE) {
        if (p_frame->clk_cnt != 0) {
            __LL_I2C_Timing_ReadStop(p_frame->Instance);
        } else {
            __LL_I2C_Timing_WriteStop(p_frame->Instance, *(p_frame->buf + p_frame->buf_len - 1));
        }

        /* wait for last data sent */
        while (!__LL_I2C_IsStopDet_Raw(p_frame->Instance));
    } else {
        /* Clear ReadReqRaw Status*/
        __LL_I2C_SLV_ReadReqRawIntSta_Clr(p_frame->Instance);
        p_frame->clk_cnt = 0;

        /* wait for last data sent */
        while (!__LL_I2C_MST_IsOnHold_Raw(p_frame->Instance));
    }

    /* I2C LL DMA Deinit */
    LL_I2C_DMA_Deinit(p_frame->dma_tx_ch);

    /* Disable Transmit DMA func */
    p_frame->dma_tx_ch = DMA_CHANNEL_INVALID;

    /* process has been finished */
    p_frame->TXdma_status = IIC_DMA_STATE_FINISH;

    /* Disable Transmit DMA func */
    __LL_I2C_TxDMA_Dis(p_frame->Instance);
}

/**
  * @brief  I2C DMA RX Channel complete callback
  * @param  arg Unlimited parameter
  * @return None
  */
static void LL_I2C_DMA_RXCHEndCallback(void *arg)
{
    I2C_FrameTypeDef *p_frame = ((I2C_FrameTypeDef *)arg);

    /* wait for last data sent */
    while (!__LL_I2C_IsStopDet_Raw(p_frame->Instance));

    /* I2C LL DMA Deinit */
    LL_I2C_DMA_Deinit(p_frame->dma_rx_ch);

    p_frame->dma_rx_ch = DMA_CHANNEL_INVALID;

    /* process has been finished */
    p_frame->RXdma_status = IIC_DMA_STATE_FINISH;

    /* Disable Receive DMA func */
    __LL_I2C_RxDMA_Dis(p_frame->Instance);

}

/**
  * @brief  I2C DMA TX Channel Error callback
  * @param  arg Unlimited parameter
  * @return None
  */
static void LL_I2C_DMA_TXCHErrorCallBck(void *arg)
{
    I2C_FrameTypeDef *p_frame = ((I2C_FrameTypeDef *)arg);

    /* I2C LL DMA Deinit */
    LL_I2C_DMA_Deinit(p_frame->dma_tx_ch);
    p_frame->dma_tx_ch = DMA_CHANNEL_INVALID;

    /* process has been Error */
    p_frame->TXdma_status = IIC_DMA_STATE_ERROR;

    /* Disable Transmit DMA func */
    __LL_I2C_TxDMA_Dis(p_frame->Instance);
}

/**
  * @brief  I2C DMA RX Channel Error callback
  * @param  arg Unlimited parameter
  * @return None
  */
static void LL_I2C_DMA_RXCHErrorCallBck(void *arg)
{
    I2C_FrameTypeDef *p_frame = ((I2C_FrameTypeDef *)arg);

    /* I2C LL DMA Deinit */
    LL_I2C_DMA_Deinit(p_frame->dma_rx_ch);
    p_frame->dma_rx_ch = DMA_CHANNEL_INVALID;

    /* process has been Error */
    p_frame->RXdma_status = IIC_DMA_STATE_ERROR;

    /* Disable Transmit DMA func */
    __LL_I2C_RxDMA_Dis(p_frame->Instance);
}


#endif  /*!< LL_DMA_MODULE_ENABLED */
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

