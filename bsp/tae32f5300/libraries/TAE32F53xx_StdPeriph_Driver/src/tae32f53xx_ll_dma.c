/**
  ******************************************************************************
  * @file    tae32f53xx_ll_dma.c
  * @author  MCD Application Team
  * @brief   DMA LL Module Driver.
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


#define DBG_TAG             "DMA LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae32f53xx_dbg.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @defgroup DMA_LL DMA LL
  * @brief    DMA LL module driver
  * @{
  */

#ifdef LL_DMA_MODULE_ENABLED

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/** @defgroup DMA_LL_Private_Types DMA LL Private Types
  * @brief    DMA LL Private Types
  * @{
  */

/**
  * @brief DMA LL config type definition
  */
typedef struct __DMA_LLCfgTypeDef {
    DMA_SrcBurstLenETypeDef src_burst;      /*!< source burst length        */
    DMA_DstBurstLenETypeDef dst_burst;      /*!< destinationd burst length  */
    uint16_t max_burst;
} DMA_LLCfgTypeDef;

/**
  * @brief DMA channel control type definition
  */
typedef struct __DMA_ChCtrlTypeDef {
    DMA_StateETypeDef state;                /*!< channel state */
    void *end_arg;                          /*!< argument of transfer complete callback fucntion    */
    DMA_IRQCallback end_callback;           /*!< transfer complete callback fucntion                */
    void *err_arg;                          /*!< argument of transfer error callback fucntion       */
    DMA_IRQCallback err_callback;           /*!< transfer error callback fucntion                   */
} DMA_ChCtrlTypeDef;

/**
  * @brief DMA Private control type definition
  */
typedef struct __DMA_PriCtrlTypeDef {
    uint8_t ch_used;                        /*!< channel used variable  */
    DMA_ChCtrlTypeDef ch_ctrl[DMA_CHN_NB];  /*!< channel control params */
} DMA_PriCtrlTypeDef;

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup DMA_LL_Private_Variables DMA LL Private Variables
  * @brief    DMA LL Private Variables
  * @{
  */

/**
  * @brief DMA LL config default
  */
static const DMA_LLCfgTypeDef dma_ll_cfg_def = {
    .src_burst = DMA_SRC_BURST_LEN_1,   /*!< source burst default 1             */
    .dst_burst = DMA_DST_BURST_LEN_1,   /*!< destination burst default 1        */
    .max_burst = 0x0,                   /*!< max burst defalut 0x0 (no limit)   */
};


/**
  * @brief DMA private control global variable
  */
static DMA_PriCtrlTypeDef dma_pri_ctrl;

/**
  * @}
  */


/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Functions DMA LL Exported Functions
  * @brief    DMA LL Exported Functions
  * @{
  */

/** @defgroup DMA_LL_Exported_Functions_Group1 DMA Init Function
  * @brief    DMA Init function
  * @{
  */

/**
  * @brief  DMA LL init
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to init
  * @param  user_cfg user config pointer
  * @return Status of the Initialization
  */
LL_StatusETypeDef LL_DMA_Init(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch, DMA_UserCfgTypeDef *user_cfg)
{
    DMA_LLCfgTypeDef *ll_cfg = (DMA_LLCfgTypeDef *)&dma_ll_cfg_def;

    //Check config params to be valid
    if (Instance == NULL || ch >= DMA_CHANNEL_NUM || user_cfg == NULL) {
        LOG_E("Init Params config error!\n");
        return LL_ERROR;
    }

    //Burst config
    __LL_DMA_SrcBurstLen_Set(Instance, ch, ll_cfg->src_burst);
    __LL_DMA_DstBurstLen_Set(Instance, ch, ll_cfg->dst_burst);
    __LL_DMA_BurstLenMax_Set(Instance, ch, ll_cfg->max_burst);

    //User config
    __LL_DMA_TransType_Set(Instance, ch, user_cfg->trans_type);
    __LL_DMA_SrcAddrMode_Set(Instance, ch, user_cfg->src_addr_mode);
    __LL_DMA_DstAddrMode_Set(Instance, ch, user_cfg->dst_addr_mode);
    __LL_DMA_SrcTransWidth_Set(Instance, ch, user_cfg->src_data_width);
    __LL_DMA_DstTransWidth_Set(Instance, ch, user_cfg->dst_data_width);

    //Source and destination handshake mode config
    if (user_cfg->trans_type == DMA_TRANS_TYPE_P2M || user_cfg->trans_type == DMA_TRANS_TYPE_P2P) {
        __LL_DMA_SrcHandshakeMode_Clr(Instance, ch);
    } else {
        __LL_DMA_SrcHandshakeMode_Set(Instance, ch);
    }

    if (user_cfg->trans_type == DMA_TRANS_TYPE_M2P || user_cfg->trans_type == DMA_TRANS_TYPE_P2P) {
        __LL_DMA_DstHandshakeMode_Clr(Instance, ch);
    } else {
        __LL_DMA_DstHandshakeMode_Set(Instance, ch);
    }

    //Channel priority config to default
    if (ch == DMA_CHANNEL_0) {
        __LL_DMA_ChannelPriLow_Set(Instance, ch);
    } else if (ch == DMA_CHANNEL_1) {
        __LL_DMA_ChannelPriHigh_Set(Instance, ch);
    }

    //Source and destination handshake interface config
    if (user_cfg->src_hs_ifc != DMA_SRC_HANDSHAKE_IFC_MEMORY) {
        __LL_DMA_SrcHandshakeIfc_Set(Instance, ch, user_cfg->src_hs_ifc);
    }

    if (user_cfg->dst_hs_ifc != DMA_DST_HANDSHAKE_IFC_MEMORY) {
        __LL_DMA_DstHandshakeIfc_Set(Instance, ch, user_cfg->dst_hs_ifc);
    }

    //Peripheral enable
    __LL_DMA_Periph_En(Instance);

    //IRQ callback config
    dma_pri_ctrl.ch_ctrl[ch].end_callback = user_cfg->end_callback;
    dma_pri_ctrl.ch_ctrl[ch].end_arg = user_cfg->end_arg;
    dma_pri_ctrl.ch_ctrl[ch].err_callback = user_cfg->err_callback;
    dma_pri_ctrl.ch_ctrl[ch].err_arg = user_cfg->err_arg;

    //Update channel state to Ready
    dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_READY;

    return LL_OK;
}

/**
  * @brief  DMA LL deinit
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to deinit
  * @return Status of the DeInitialization
  */
LL_StatusETypeDef LL_DMA_DeInit(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch)
{
    uint8_t i;

    //Check config params to be valid
    if (Instance == NULL || ch >= DMA_CHANNEL_NUM) {
        LOG_E("Deinit Params config error!\n");
        return LL_ERROR;
    }

    //IRQ callback deinit
    dma_pri_ctrl.ch_ctrl[ch].end_callback = NULL;
    dma_pri_ctrl.ch_ctrl[ch].end_arg = NULL;
    dma_pri_ctrl.ch_ctrl[ch].err_callback = NULL;
    dma_pri_ctrl.ch_ctrl[ch].err_arg = NULL;

    //Update channel state to Reset
    dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_RESET;

    //Peripheral disable when all channels close
    for (i = 0; i < DMA_CHANNEL_NUM; i++) {
        if (dma_pri_ctrl.ch_ctrl[i].state != DMA_STATE_RESET) {
            break;
        }
    }

    if (i == DMA_CHANNEL_NUM) {
        __LL_DMA_Periph_Dis(Instance);
    }

    return LL_OK;
}

/**
  * @}
  */


/** @defgroup DMA_LL_Exported_Functions_Group2 DMA Channel Management Functions
  * @brief    DMA Channel Management Functions
  * @{
  */

/**
  * @brief  DMA LL channel request
  * @param  None
  * @return DMA_ChannelETypeDef
  */
DMA_ChannelETypeDef LL_DMA_ChannelRequest(void)
{
    uint8_t i;
    DMA_ChannelETypeDef avl_ch = DMA_CHANNEL_INVALID;

    //Search available channel
    for (i = 0; i < DMA_CHANNEL_NUM; i++) {
        if (!READ_BIT(dma_pri_ctrl.ch_used, BIT(i)) && (dma_pri_ctrl.ch_ctrl[i].state == DMA_STATE_RESET)) {
            SET_BIT(dma_pri_ctrl.ch_used, BIT(i));
            avl_ch = (DMA_ChannelETypeDef)i;
            break;
        }
    }

    return avl_ch;
}

/**
  * @brief  DMA LL request specific channel
  * @param  ch specific channel to request
  * @return DMA_ChannelETypeDef
  */
DMA_ChannelETypeDef LL_DMA_ChReqSpecific(DMA_ChannelETypeDef ch)
{
    if (ch < DMA_CHANNEL_NUM && !READ_BIT(dma_pri_ctrl.ch_used, BIT(ch)) && (dma_pri_ctrl.ch_ctrl[ch].state == DMA_STATE_RESET)) {
        SET_BIT(dma_pri_ctrl.ch_used, BIT(ch));
    } else {
        ch = DMA_CHANNEL_INVALID;
    }

    return ch;
}

/**
  * @brief  DMA LL channel release
  * @param  ch channel to release
  * @return None
  */
void LL_DMA_ChannelRelease(DMA_ChannelETypeDef ch)
{
    if (dma_pri_ctrl.ch_ctrl[ch].state == DMA_STATE_RESET) {
        CLEAR_BIT(dma_pri_ctrl.ch_used, BIT(ch));
    }
}
/**
  * @}
  */


/** @defgroup DMA_LL_Exported_Functions_Group3 DMA Start and Stop Functions
  * @brief    DMA Start and Stop Functions
  * @{
  */

/**
  * @brief  DMA LL start in CPU mode
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to start
  * @param  src_addr source address
  * @param  dst_addr destination address
  * @param  data_len transfer data length
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_DMA_Start_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch,
                                   uint32_t src_addr, uint32_t dst_addr, uint32_t data_len)
{
    uint8_t src_data_width;
    uint32_t block_size;

    if (ch >= DMA_CHANNEL_NUM) {
        LOG_E("Invalid ch-[%d]!\n", ch);
        return LL_ERROR;
    }

    //Config block size, which is associate to data length
    src_data_width = __LL_DMA_SrcTransWidth_Get(Instance, ch);

    if (src_data_width > 2) {
        LOG_E("Source data width config error-[%d]!\n", src_data_width);
        return LL_ERROR;
    }

    src_data_width = BIT(src_data_width);
    block_size = data_len / src_data_width;

    if (block_size > LL_DMA_BLOCK_SIZE_MAX) {
        LOG_E("Block size max is %d, while now is %d!\n", LL_DMA_BLOCK_SIZE_MAX, block_size);
        return LL_ERROR;
    }

    __LL_DMA_BlockTransCnt_Set(Instance, ch, block_size);

    //Check and update channel state
    if (dma_pri_ctrl.ch_ctrl[ch].state != DMA_STATE_READY) {
        LOG_E("Channel state-[%d] isn't in Ready!\n", dma_pri_ctrl.ch_ctrl[ch].state);
        return LL_ERROR;
    }

    dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_BUSY;

    //Config source and destination peripheral bus master 1/2
    if (src_addr >= LL_DMA_SRMBC_ADDR_START && src_addr <= LL_DMA_SRMBC_ADDR_END) { //SRAMB & SRAMC
        __LL_DMA_SrcPeriphBus_Set(Instance, ch, DMA_SRC_PERIPH_BUS_AHB_MST2);
    } else {                                                                        //SRAMA & Peripheral & Flash
        __LL_DMA_SrcPeriphBus_Set(Instance, ch, DMA_SRC_PERIPH_BUS_AHB_MST1);
    }

    if (dst_addr >= LL_DMA_SRMBC_ADDR_START && dst_addr <= LL_DMA_SRMBC_ADDR_END) { //SRAMB & SRAMC
        __LL_DMA_DstPeriphBus_Set(Instance, ch, DMA_DST_PERIPH_BUS_AHB_MST2);
    } else {                                                                        //SRAMA & Peripheral & Flash
        __LL_DMA_DstPeriphBus_Set(Instance, ch, DMA_DST_PERIPH_BUS_AHB_MST1);
    }

    //source and destination address config
    __LL_DMA_SrcAddr_Set(Instance, ch, src_addr);
    __LL_DMA_DstAddr_Set(Instance, ch, dst_addr);

    //Channel enable
    if (ch == DMA_CHANNEL_0) {
        __LL_DMA_Ch0_En(Instance);
    } else if (ch == DMA_CHANNEL_1) {
        __LL_DMA_Ch1_En(Instance);
    }

    return LL_OK;
}

/**
  * @brief  DMA LL start in interrupt mode
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to start
  * @param  src_addr source address
  * @param  dst_addr destination address
  * @param  data_len transfer data length
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_DMA_Start_IT(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch,
                                  uint32_t src_addr, uint32_t dst_addr, uint32_t data_len)
{
    //Channel interrupt enable
    __LL_DMA_Channel_Int_En(Instance, ch);

    //Channel transfer complete and error interrupt enable
    if (ch == DMA_CHANNEL_0) {
        __LL_DMA_Ch0TransCom_Int_En(Instance);
        __LL_DMA_Ch0TransErr_Int_En(Instance);
    } else if (ch == DMA_CHANNEL_1) {
        __LL_DMA_Ch1TransCom_Int_En(Instance);
        __LL_DMA_Ch1TransErr_Int_En(Instance);
    }

    return LL_DMA_Start_CPU(Instance, ch, src_addr, dst_addr, data_len);
}

/**
  * @brief  DMA LL Stop in CPU mode
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to stop
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_DMA_Stop_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch)
{
    //Check and update channel state
    if (dma_pri_ctrl.ch_ctrl[ch].state == DMA_STATE_RESET) {
        LOG_E("Channel state is in RESET!\n");
        return LL_ERROR;
    }

    dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_READY;

    //Channel disable
    if (ch == DMA_CHANNEL_0) {
        __LL_DMA_Ch0_Dis(Instance);
    } else if (ch == DMA_CHANNEL_1) {
        __LL_DMA_Ch1_Dis(Instance);
    }

    return LL_OK;
}

/**
  * @brief  DMA LL Stop in interrupt mode
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to stop
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_DMA_Stop_IT(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch)
{
    LL_StatusETypeDef ret;

    ret = LL_DMA_Stop_CPU(Instance, ch);

    if (ret != LL_OK) {
        return ret;
    }

    //Channel interrupt disable
    __LL_DMA_Channel_Int_Dis(Instance, ch);

    //Channel transfer complete and error interrupt disable
    if (ch == DMA_CHANNEL_0) {
        __LL_DMA_Ch0TransCom_Int_Dis(Instance);
        __LL_DMA_Ch0TransErr_Int_Dis(Instance);
    } else if (ch == DMA_CHANNEL_1) {
        __LL_DMA_Ch1TransCom_Int_Dis(Instance);
        __LL_DMA_Ch1TransErr_Int_Dis(Instance);
    }

    return LL_OK;
}

/**
  * @brief  DMA LL wait for transfer complete in CPU mode
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to wait for transfer complete
  * @return LL_StatusETypeDef
  */
LL_StatusETypeDef LL_DMA_WaitComplete_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch, uint32_t timeout)
{
    uint32_t tickstart;
    LL_StatusETypeDef ret = LL_ERROR;

    //Check  channel state
    if (dma_pri_ctrl.ch_ctrl[ch].state != DMA_STATE_BUSY) {
        LOG_E("Channel state-[%d] isn't in Busy!\n", dma_pri_ctrl.ch_ctrl[ch].state);
        return LL_ERROR;
    }

    tickstart = LL_GetTick();

    switch (ch) {
        case DMA_CHANNEL_0:
            while (!__LL_DMA_Ch0TransErrSta_Get(Instance)) {    //transfer normal, no error
                if (__LL_DMA_Ch0TransComSta_Get(Instance)) {    //transfer complete
                    //Clear complete status
                    __LL_DMA_Ch0TransComSta_Clr(Instance);
                    ret = LL_OK;
                    break;
                }

                if ((LL_GetTick() - tickstart) > timeout) {     //transfer timeout
                    ret = LL_TIMEOUT;
                    break;
                }
            }

            //Clear error status
            __LL_DMA_Ch0TransErrSta_Clr(Instance);

            //Update channel state to Ready
            dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_READY;

            break;

        case DMA_CHANNEL_1:
            while (!__LL_DMA_Ch1TransErrSta_Get(Instance)) {    //transfer normal, no error
                if (__LL_DMA_Ch1TransComSta_Get(Instance)) {    //transfer complete
                    //Clear complete status
                    __LL_DMA_Ch1TransComSta_Clr(Instance);
                    ret = LL_OK;
                    break;
                }

                if ((LL_GetTick() - tickstart) > timeout) {     //transfer timeout
                    ret = LL_TIMEOUT;
                    break;
                }
            }

            //Clear error status
            __LL_DMA_Ch1TransErrSta_Clr(Instance);

            //Update channel state to Ready
            dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_READY;

            break;

        default:
            break;;
    }

    return ret;
}

/**
  * @}
  */


/** @defgroup DMA_LL_Exported_Functions_Interrupt DMA Interrupt handler and call back
  * @brief    DMA Interrupt handler and call back
  * @{
  */

/**
  * @brief  DMA IRQ Handler
  * @param  Instance Specifies DMA peripheral
  * @return None
  */
void LL_DMA_IRQHandler(DMA_TypeDef *Instance)
{
    //Transfer complete interrupt handler
    if (__LL_DMA_Ch0TransComIntSta_Get(Instance)) {         //Channel 0 transfer complete interrupt
        //Disable interrupt in single mode
        __LL_DMA_Ch0TransCom_Int_Dis(Instance);
        __LL_DMA_Ch0TransErr_Int_Dis(Instance);

        //Clear pending
        __LL_DMA_Ch0TransComSta_Clr(Instance);

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].state = DMA_STATE_READY;

        //Interrupt callback
        if (dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].end_callback) {
            dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].end_callback(dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].end_arg);
        }

    }

    if (__LL_DMA_Ch1TransComIntSta_Get(Instance)) {         //Channel 1 transfer complete interrupt
        //Disable interrupt in single mode
        __LL_DMA_Ch1TransCom_Int_Dis(Instance);
        __LL_DMA_Ch1TransErr_Int_Dis(Instance);

        //Clear pending
        __LL_DMA_Ch1TransComSta_Clr(Instance);

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].state = DMA_STATE_READY;

        //Interrupt callback
        if (dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].end_callback) {
            dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].end_callback(dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].end_arg);
        }

    }


    //Transfer error interrupt handler
    if (__LL_DMA_Ch0TransErrIntSta_Get(Instance)) {         //Channel 0 transfer error interrupt
        //Disable interrupt in single mode
        __LL_DMA_Ch0TransCom_Int_Dis(Instance);
        __LL_DMA_Ch0TransErr_Int_Dis(Instance);

        //Clear pending
        __LL_DMA_Ch0TransErrSta_Clr(Instance);

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].state = DMA_STATE_READY;

        //Interrupt callback
        if (dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].err_callback) {
            dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].err_callback(dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].err_arg);
        }

    }

    if (__LL_DMA_Ch1TransErrIntSta_Get(Instance)) {         //Channel 1 transfer error interrupt
        //Disable interrupt in single mode
        __LL_DMA_Ch1TransCom_Int_Dis(Instance);
        __LL_DMA_Ch1TransErr_Int_Dis(Instance);

        //Clear pending
        __LL_DMA_Ch1TransErrSta_Clr(Instance);

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].state = DMA_STATE_READY;

        //Interrupt callback
        if (dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].err_callback) {
            dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].err_callback(dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].err_arg);
        }

    }


    //Block transfer complete interrupt handler
    if (__LL_DMA_Ch0BlockTransComIntSta_Get(Instance)) {    //Channel 0 block transfer complete interrupt
        __LL_DMA_Ch0BlockTransComSta_Clr(Instance);
        //:TODO: according to need

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].state = DMA_STATE_READY;
    }

    if (__LL_DMA_Ch1BlockTransComIntSta_Get(Instance)) {    //Channel 1 block transfer complete interrupt
        __LL_DMA_Ch1BlockTransComSta_Clr(Instance);
        //:TODO: according to need

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].state = DMA_STATE_READY;
    }


    //Source transfer complete interrupt handler
    if (__LL_DMA_Ch0SrcTransComIntSta_Get(Instance)) {      //Channel 0 source transfer complete interrupt
        __LL_DMA_Ch0SrcTransComSta_Clr(Instance);
        //:TODO: according to need

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].state = DMA_STATE_READY;
    }

    if (__LL_DMA_Ch1SrcTransComIntSta_Get(Instance)) {      //Channel 1 source transfer complete interrupt
        __LL_DMA_Ch1SrcTransComSta_Clr(Instance);
        //:TODO: according to need

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].state = DMA_STATE_READY;
    }


    //Destination transfer complete interrupt handler
    if (__LL_DMA_Ch0DstTransComIntSta_Get(Instance)) {      //Channel 0 destination transfer complete interrupt
        __LL_DMA_Ch0DstTransComSta_Clr(Instance);
        //:TODO: according to need

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_0].state = DMA_STATE_READY;
    }

    if (__LL_DMA_Ch1DstTransComIntSta_Get(Instance)) {      //Channel 1 destination transfer complete interrupt
        __LL_DMA_Ch1DstTransComSta_Clr(Instance);
        //:TODO: according to need

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[DMA_CHANNEL_1].state = DMA_STATE_READY;
    }
}

/**
  * @}
  */

/**
  * @}
  */


/* Private functions ---------------------------------------------------------*/


#endif  /* LL_DMA_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

