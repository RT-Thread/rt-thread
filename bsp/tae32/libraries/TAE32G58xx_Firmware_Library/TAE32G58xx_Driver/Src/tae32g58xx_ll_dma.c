/**
  ******************************************************************************
  * @file    tae32g58xx_ll_dma.c
  * @author  MCD Application Team
  * @brief   DMA LL module driver
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


#define DBG_TAG             "DMA LL"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @defgroup DMA_LL DMA LL
  * @brief    DMA LL module driver
  * @{
  */

#ifdef LL_DMA_MODULE_ENABLED

/* Private Constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Private Types -------------------------------------------------------------*/
/** @defgroup DMA_LL_Private_Types DMA LL Private Types
  * @brief    DMA LL Private Types
  * @{
  */

/**
  * @brief DMA channel control type definition
  */
typedef struct __DMA_ChCtrlTypeDef {
    DMA_StateETypeDef state;                /*!< Channel state                                      */
    void *end_arg;                          /*!< Argument of transfer complete callback fucntion    */
    DMA_IRQCallback end_callback;           /*!< Transfer complete callback fucntion                */
    void *err_arg;                          /*!< Argument of transfer error callback fucntion       */
    DMA_IRQCallback err_callback;           /*!< Transfer error callback fucntion                   */
    void *half_arg;                         /*!< Argument of transfer half callback fucntion        */
    DMA_IRQCallback half_callback;          /*!< Transfer half callback fucntion                    */
} DMA_ChCtrlTypeDef;

/**
  * @brief DMA Private control type definition
  */
typedef struct __DMA_PriCtrlTypeDef {
    uint8_t ch_used;                                /*!< Channel used variable  */
    DMA_ChCtrlTypeDef ch_ctrl[DMA_CHANNEL_NUMS];    /*!< Channel control params */
} DMA_PriCtrlTypeDef;

/**
  * @}
  */


/* Private Variables ---------------------------------------------------------*/
/** @defgroup DMA_LL_Private_Variables DMA LL Private Variables
  * @brief    DMA LL Private Variables
  * @{
  */

/**
  * @brief DMA LL config default
  */
static const DMA_LLCfgTypeDef dma_ll_cfg_def = {
    .src_burst      = DMA_BURST_LEN_1,          /*!< Source burst default 1                         */
    .dst_burst      = DMA_BURST_LEN_1,          /*!< Destination burst default 1                    */
    .src_periph_bus = DMA_PERIPH_BUS_AHB_MST1,  /*!< Source peripheral bus default AHB Master1      */
    .dst_periph_bus = DMA_PERIPH_BUS_AHB_MST2,  /*!< Destination peripheral bus default AHB Master2 */
};


/**
  * @brief DMA private control global variable
  */
static DMA_PriCtrlTypeDef dma_pri_ctrl;

/**
  * @}
  */


/* Private Function Prototypes -----------------------------------------------*/
/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
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
    DMA_LLCfgTypeDef *ll_cfg;
    uint16_t hs_ifc_src, hs_ifc_dst;
    bool src_ifc_mux_en, dst_ifc_mux_en;

    //Assert param
    assert_param(IS_DMA_ALL_INSTANCE(Instance));
    assert_param(__LL_DMA_IsChannelValid(ch));
    assert_param(user_cfg != NULL);

    if (!IS_DMA_ALL_INSTANCE(Instance) || !__LL_DMA_IsChannelValid(ch) || user_cfg == NULL) {
        return LL_INVALID;
    }

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) < 3) {
        if ((user_cfg->src_hs_ifc > DMA_HANDSHAKE_IFC_PDM3_RX) ||
            (user_cfg->dst_hs_ifc > DMA_HANDSHAKE_IFC_PDM3_RX)) {
            LOG_E("The hardware version no support this enum!\n");
            return LL_FAILED;
        }
    }

    //LL config pointer config
    LL_FUNC_ALTER(user_cfg->ll_cfg == NULL, ll_cfg = (DMA_LLCfgTypeDef *)&dma_ll_cfg_def, ll_cfg = user_cfg->ll_cfg);

    //Burst config
    __LL_DMA_SrcBurstLen_Set(Instance, ch, ll_cfg->src_burst);
    __LL_DMA_DstBurstLen_Set(Instance, ch, ll_cfg->dst_burst);
    __LL_DMA_SrcPeriphBus_Set(Instance, ch, ll_cfg->src_periph_bus);
    __LL_DMA_DstPeriphBus_Set(Instance, ch, ll_cfg->dst_periph_bus);

    //User config
    __LL_DMA_TransType_Set(Instance, ch, user_cfg->trans_type);
    __LL_DMA_TransMode_Set(Instance, ch, user_cfg->trans_mode);
    __LL_DMA_SrcAddrMode_Set(Instance, ch, user_cfg->src_addr_mode);
    __LL_DMA_DstAddrMode_Set(Instance, ch, user_cfg->dst_addr_mode);
    __LL_DMA_SrcTransWidth_Set(Instance, ch, user_cfg->src_data_width);
    __LL_DMA_DstTransWidth_Set(Instance, ch, user_cfg->dst_data_width);

    //Source and destination handshake interface config
    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        if (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_DMA)) {
            src_ifc_mux_en = user_cfg->src_hs_ifc_mux_en;
            dst_ifc_mux_en = user_cfg->dst_hs_ifc_mux_en;
        } else {
            src_ifc_mux_en = false;
            dst_ifc_mux_en = false;
        }

        if (src_ifc_mux_en == false) {
            if ((user_cfg->src_hs_ifc >= DMA_HANDSHAKE_IFC_I2C0_TX) && 
                (user_cfg->src_hs_ifc < DMA_HANDSHAKE_IFC_PDM0_RX)) {
				__LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
                __LL_SYSCTRL_DmaReqCfg_Reset(SYSCTRL, user_cfg->src_hs_ifc);
                __LL_DMA_SrcHandshakeIfc_Set(Instance, ch, user_cfg->src_hs_ifc);
                __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);
            } else if ((user_cfg->src_hs_ifc == DMA_HANDSHAKE_IFC_PDM0_RX) || 
                (user_cfg->src_hs_ifc == DMA_HANDSHAKE_IFC_PDM1_RX) ||
                (user_cfg->src_hs_ifc == DMA_HANDSHAKE_IFC_PDM2_RX) ||
                (user_cfg->src_hs_ifc == DMA_HANDSHAKE_IFC_PDM3_RX)) {
                __LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
                __LL_SYSCTRL_DmaReqCfg_Set(SYSCTRL, user_cfg->src_hs_ifc);
                __LL_DMA_SrcHandshakeIfc_Set(Instance, ch, user_cfg->src_hs_ifc);
                __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);             
            } else if ((user_cfg->src_hs_ifc >= DMA_HANDSHAKE_IFC_HRPWM_SLV7) &&
                (user_cfg->src_hs_ifc <= DMA_HANDSHAKE_IFC_HRPWM_MST)) {
                hs_ifc_src = user_cfg->src_hs_ifc - LL_DMA_HS_IFC_COVER_AMEND;
				__LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
                __LL_SYSCTRL_DmaReqCfg_Reset(SYSCTRL, hs_ifc_src);                
                __LL_DMA_SrcHandshakeIfc_Set(Instance, ch, hs_ifc_src);
                __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);                   
            } else if ((user_cfg->src_hs_ifc >= DMA_HANDSHAKE_IFC_MUXA_ADC3) &&
                (user_cfg->src_hs_ifc <= DMA_HANDSHAKE_IFC_MUXA_PDM3_RX)) {
                __LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
                hs_ifc_src = user_cfg->src_hs_ifc - LL_DMA_HS_IFC_MUX_AMEND;
                __LL_SYSCTRL_DmaReqCfg_Set(SYSCTRL, hs_ifc_src);
                __LL_DMA_SrcHandshakeIfc_Set(Instance, ch, hs_ifc_src);
                __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);                  
            } else if (user_cfg->src_hs_ifc != DMA_HANDSHAKE_IFC_MEMORY) {
                __LL_DMA_SrcHandshakeIfc_Set(Instance, ch, user_cfg->src_hs_ifc);
            }
        } else {
            #if 0
            if ((user_cfg->src_hs_ifc_mux >= DMA_HANDSHAKE_IFC_MUX_ADC3) &&
                (user_cfg->src_hs_ifc_mux <= DMA_HANDSHAKE_IFC_MUX_PDM3_RX)) {
            #else
            if (user_cfg->src_hs_ifc_mux != DMA_HANDSHAKE_IFC_MUX_MEMORY) {
            #endif
                __LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
                __LL_SYSCTRL_DmaReqCfg_Set(SYSCTRL, user_cfg->src_hs_ifc_mux);
                __LL_DMA_SrcHandshakeIfc_Set(Instance, ch, user_cfg->src_hs_ifc_mux); 
                __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);      
            }
        }

        if (dst_ifc_mux_en == false) {
            if ((user_cfg->dst_hs_ifc >= DMA_HANDSHAKE_IFC_I2C0_TX) && 
                (user_cfg->dst_hs_ifc < DMA_HANDSHAKE_IFC_PDM0_RX)) {
                __LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
                __LL_SYSCTRL_DmaReqCfg_Reset(SYSCTRL, user_cfg->dst_hs_ifc);
                __LL_DMA_DstHandshakeIfc_Set(Instance, ch, user_cfg->dst_hs_ifc);
                __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);
            } else if ((user_cfg->dst_hs_ifc == DMA_HANDSHAKE_IFC_PDM0_RX) || 
                (user_cfg->dst_hs_ifc == DMA_HANDSHAKE_IFC_PDM1_RX) ||
                (user_cfg->dst_hs_ifc == DMA_HANDSHAKE_IFC_PDM2_RX) ||
                (user_cfg->dst_hs_ifc == DMA_HANDSHAKE_IFC_PDM3_RX)) {
				__LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
                __LL_SYSCTRL_DmaReqCfg_Set(SYSCTRL, user_cfg->dst_hs_ifc);
                __LL_DMA_DstHandshakeIfc_Set(Instance, ch, user_cfg->dst_hs_ifc);
                __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);                
            } else if ((user_cfg->dst_hs_ifc >= DMA_HANDSHAKE_IFC_HRPWM_SLV7) &&
                (user_cfg->dst_hs_ifc <= DMA_HANDSHAKE_IFC_HRPWM_MST)) {
                hs_ifc_dst = user_cfg->dst_hs_ifc - LL_DMA_HS_IFC_COVER_AMEND;
				__LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
                __LL_SYSCTRL_DmaReqCfg_Reset(SYSCTRL, hs_ifc_dst);           
                __LL_DMA_DstHandshakeIfc_Set(Instance, ch, hs_ifc_dst);
                __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);                
            } else if ((user_cfg->dst_hs_ifc >= DMA_HANDSHAKE_IFC_MUXA_ADC3) &&
                (user_cfg->dst_hs_ifc <= DMA_HANDSHAKE_IFC_MUXA_PDM3_RX)) {
                __LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
                hs_ifc_dst = user_cfg->dst_hs_ifc - LL_DMA_HS_IFC_MUX_AMEND;
                __LL_SYSCTRL_DmaReqCfg_Set(SYSCTRL, hs_ifc_dst);
                __LL_DMA_DstHandshakeIfc_Set(Instance, ch, hs_ifc_dst);
                __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);                 
            } else if (user_cfg->dst_hs_ifc != DMA_HANDSHAKE_IFC_MEMORY) {
                __LL_DMA_DstHandshakeIfc_Set(Instance, ch, user_cfg->dst_hs_ifc);
            }
        } else {
            #if 0
            if ((user_cfg->dst_hs_ifc_mux >= DMA_HANDSHAKE_IFC_MUX_ADC3) &&
                (user_cfg->dst_hs_ifc_mux <= DMA_HANDSHAKE_IFC_MUX_PDM3_RX)) {
            #else
            if (user_cfg->dst_hs_ifc_mux != DMA_HANDSHAKE_IFC_MUX_MEMORY) {
            #endif
				__LL_SYSCTRL_SysRegWrite_Unlock(SYSCTRL);
                __LL_SYSCTRL_DmaReqCfg_Set(SYSCTRL, user_cfg->dst_hs_ifc_mux);
                __LL_DMA_DstHandshakeIfc_Set(Instance, ch, user_cfg->dst_hs_ifc_mux);
                __LL_SYSCTRL_SysRegWrite_Lock(SYSCTRL);   
            }     
        }
    } else {
        if (user_cfg->src_hs_ifc != DMA_HANDSHAKE_IFC_MEMORY) {
            __LL_DMA_SrcHandshakeIfc_Set(Instance, ch, user_cfg->src_hs_ifc);
        }

        if (user_cfg->dst_hs_ifc != DMA_HANDSHAKE_IFC_MEMORY) {
            __LL_DMA_DstHandshakeIfc_Set(Instance, ch, user_cfg->dst_hs_ifc);
        }        
    }

    //IRQ callback config
    dma_pri_ctrl.ch_ctrl[ch].end_callback = user_cfg->end_callback;
    dma_pri_ctrl.ch_ctrl[ch].end_arg = user_cfg->end_arg;
    dma_pri_ctrl.ch_ctrl[ch].err_callback = user_cfg->err_callback;
    dma_pri_ctrl.ch_ctrl[ch].err_arg = user_cfg->err_arg;
    dma_pri_ctrl.ch_ctrl[ch].half_callback = user_cfg->half_callback;
    dma_pri_ctrl.ch_ctrl[ch].half_arg = user_cfg->half_arg;

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
    //Assert param
    assert_param(IS_DMA_ALL_INSTANCE(Instance));
    assert_param(__LL_DMA_IsChannelValid(ch));

    if (!IS_DMA_ALL_INSTANCE(Instance) || !__LL_DMA_IsChannelValid(ch)) {
        return LL_INVALID;
    }

    //IRQ callback deinit
    dma_pri_ctrl.ch_ctrl[ch].end_callback = NULL;
    dma_pri_ctrl.ch_ctrl[ch].end_arg = NULL;
    dma_pri_ctrl.ch_ctrl[ch].err_callback = NULL;
    dma_pri_ctrl.ch_ctrl[ch].err_arg = NULL;
    dma_pri_ctrl.ch_ctrl[ch].half_callback = NULL;
    dma_pri_ctrl.ch_ctrl[ch].half_arg = NULL;

    //Update channel state to Reset
    dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_RESET;

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        __LL_DMA_Ch_Dis(Instance, ch);
        while (__LL_DMA_IsChEn(Instance, ch));
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
    for (i = 0; i < DMA_CHANNEL_NUMS; i++) {
        if (!READ_BIT(dma_pri_ctrl.ch_used, BIT(i)) && dma_pri_ctrl.ch_ctrl[i].state == DMA_STATE_RESET) {
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
    //Assert param
    assert_param(__LL_DMA_IsChannelValid(ch));

    if (!__LL_DMA_IsChannelValid(ch)) {
        return DMA_CHANNEL_INVALID;
    }

    if (!READ_BIT(dma_pri_ctrl.ch_used, BIT(ch)) && dma_pri_ctrl.ch_ctrl[ch].state == DMA_STATE_RESET) {
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
    //Assert param
    assert_param(__LL_DMA_IsChannelValid(ch));

    if (!__LL_DMA_IsChannelValid(ch)) {
        return;
    }

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
  * @return LL Status
  */
LL_StatusETypeDef LL_DMA_Start_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch,
                                   uint32_t src_addr, uint32_t dst_addr, uint32_t data_len)
{
    uint8_t src_data_width;
    uint32_t block_size;

    //Assert param
    assert_param(IS_DMA_ALL_INSTANCE(Instance));
    assert_param(__LL_DMA_IsChannelValid(ch));
    assert_param(data_len);

    if (!IS_DMA_ALL_INSTANCE(Instance) || !__LL_DMA_IsChannelValid(ch) || !data_len) {
        return LL_INVALID;
    }

    //Check and update channel state
    if (dma_pri_ctrl.ch_ctrl[ch].state != DMA_STATE_READY) {
        LOG_E("Channel state-[%d] isn't in Ready!\n", dma_pri_ctrl.ch_ctrl[ch].state);
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
        LOG_E("Block size max is %u, while now is %" PRIu32 "!\n", LL_DMA_BLOCK_SIZE_MAX, block_size);
        return LL_ERROR;
    }

    __LL_DMA_BlockTransCnt_Set(Instance, ch, block_size);

#ifdef LL_EFLASH_MODULE_ENABLED

    //EFLASH Double Bank map Bank1 address convert
    if (src_addr >= EFLASH_MEM_BASE && src_addr < EFLASH_MEM_BASE + LL_EFLASH_ChipSize_Get(EFLASH)) {
        if ((EFLASH_BankModeETypeDef)__LL_EFLASH_BankMode_Get(EFLASH) == EFLASH_BANK_MODE_DOUBLE &&
            (EFLASH_BankAddrMapETypeDef)__LL_EFLASH_BankAddrMap_Get(EFLASH) == EFLASH_BANK_ADDR_MAP_BANK1) {
            uint32_t eflash_chip_size = LL_EFLASH_ChipSize_Get(EFLASH);

            if (src_addr < EFLASH_MEM_BASE + eflash_chip_size / 2) {
                if (src_addr + data_len > EFLASH_MEM_BASE + eflash_chip_size / 2) {
                    LOG_E("EFLASH Dobule bank mapping bank1 mode can't read data with DMA span two bank!");
                    return LL_INVALID;
                }

                src_addr += eflash_chip_size / 2;
            } else {
                if (src_addr + data_len > EFLASH_MEM_BASE + eflash_chip_size) {
                    LOG_E("EFLASH Dobule bank mapping bank1 mode can't read data with DMA span two bank!");
                    return LL_INVALID;
                }

                src_addr -= eflash_chip_size / 2;
            }
        }
    }

#endif

    //source and destination address config
    __LL_DMA_SrcAddr_Set(Instance, ch, src_addr);
    __LL_DMA_DstAddr_Set(Instance, ch, dst_addr);

    //Update channel state to Busy
    dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_BUSY;

    //Channel enable
    __LL_DMA_Ch_En(Instance, ch);

    return LL_OK;
}

/**
  * @brief  DMA LL start in interrupt mode
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to start
  * @param  src_addr source address
  * @param  dst_addr destination address
  * @param  data_len transfer data length
  * @return LL Status
  */
LL_StatusETypeDef LL_DMA_Start_IT(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch,
                                  uint32_t src_addr, uint32_t dst_addr, uint32_t data_len)
{
    //Assert param
    assert_param(IS_DMA_ALL_INSTANCE(Instance));
    assert_param(__LL_DMA_IsChannelValid(ch));
    assert_param(data_len);

    if (!IS_DMA_ALL_INSTANCE(Instance) || !__LL_DMA_IsChannelValid(ch) || !data_len) {
        return LL_INVALID;
    }

    //Channel interrupt pending all clear
    __LL_DMA_AllTransIntPnd_Clr(Instance, ch);

    //Channel interrupt enable
    __LL_DMA_TransCom_Int_En(Instance, ch);
    __LL_DMA_TransErr_Int_En(Instance, ch);
    __LL_DMA_TransHalf_Int_En(Instance, ch);

    return LL_DMA_Start_CPU(Instance, ch, src_addr, dst_addr, data_len);
}

/**
  * @brief  DMA LL Stop in CPU mode
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to stop
  * @return LL Status
  */
LL_StatusETypeDef LL_DMA_Stop_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch)
{
    //Assert param
    assert_param(IS_DMA_ALL_INSTANCE(Instance));
    assert_param(__LL_DMA_IsChannelValid(ch));

    if (!IS_DMA_ALL_INSTANCE(Instance) || !__LL_DMA_IsChannelValid(ch)) {
        return LL_INVALID;
    }

    //Check and update channel state
    if (dma_pri_ctrl.ch_ctrl[ch].state == DMA_STATE_RESET) {
        LOG_E("Channel state is in Reset!\n");
        return LL_ERROR;
    }

    //Channel disable
    __LL_DMA_Ch_Dis(Instance, ch);

    //Update channel state to Ready
    dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_READY;

    return LL_OK;
}

/**
  * @brief  DMA LL Stop in interrupt mode
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to stop
  * @return LL Status
  */
LL_StatusETypeDef LL_DMA_Stop_IT(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch)
{
    LL_StatusETypeDef ret;

    //Assert param
    assert_param(IS_DMA_ALL_INSTANCE(Instance));
    assert_param(__LL_DMA_IsChannelValid(ch));

    if (!IS_DMA_ALL_INSTANCE(Instance) || !__LL_DMA_IsChannelValid(ch)) {
        return LL_INVALID;
    }

    ret = LL_DMA_Stop_CPU(Instance, ch);

    if (ret != LL_OK) {
        return ret;
    }

    //Channel interrupt disable
    __LL_DMA_TransCom_Int_Dis(Instance, ch);
    __LL_DMA_TransErr_Int_Dis(Instance, ch);
    __LL_DMA_TransHalf_Int_Dis(Instance, ch);

    //Channel interrupt pending all clear
    __LL_DMA_AllTransIntPnd_Clr(Instance, ch);

    return LL_OK;
}

/**
  * @brief  DMA LL wait for transfer complete in CPU mode
  * @param  Instance Specifies DMA peripheral
  * @param  ch channel to wait for transfer complete
  * @param  timeout timeout count in ms Unit
  * @return LL Status
  */
LL_StatusETypeDef LL_DMA_WaitComplete_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch, uint32_t timeout)
{
    bool cplt_flag = false;
    uint32_t tickstart;
    LL_StatusETypeDef ret = LL_ERROR;

    //Assert param
    assert_param(IS_DMA_ALL_INSTANCE(Instance));
    assert_param(__LL_DMA_IsChannelValid(ch));

    if (!IS_DMA_ALL_INSTANCE(Instance) || !__LL_DMA_IsChannelValid(ch)) {
        return LL_INVALID;
    }

    //Check channel state
    if (dma_pri_ctrl.ch_ctrl[ch].state != DMA_STATE_BUSY) {
        LOG_E("Channel state-[%d] isn't in Busy!\n", dma_pri_ctrl.ch_ctrl[ch].state);
        return LL_ERROR;
    }

    tickstart = LL_GetTick();

    if (__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) {
        while (!__LL_DMA_IsTransErrIntPnd(Instance, ch)) {  //Transfer normal, no error
            if (__LL_DMA_IsTransCpltIntPnd(Instance, ch)) { 
                //Clear complete status
                __LL_DMA_TransCpltIntPnd_Clr(Instance, ch);
                cplt_flag = true;
            }

            if ((!__LL_DMA_IsTransBusy(Instance, ch)) && cplt_flag) {
                ret = LL_OK;
                break;                
            }

            //Transfer timeout
            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {     
                ret = LL_TIMEOUT;
                break;
            }
        }   

        //Clear error and half complete status
        __LL_DMA_TransErrIntPnd_Clr(Instance, ch);
        __LL_DMA_TransHalfCpltIntPnd_Clr(Instance, ch);   
    } else {
        while (!__LL_DMA_IsTransErrIntPnd(Instance, ch)) {  //Transfer normal, no error
            if (__LL_DMA_IsTransCpltIntPnd(Instance, ch)) { //Transfer complete
                //Clear complete status
                __LL_DMA_TransCpltIntPnd_Clr(Instance, ch);
                ret = LL_OK;
                break;
            }

            if (timeout != LL_WAIT_FOREVER && (LL_GetTick() - tickstart) > timeout) {     //Transfer timeout
                ret = LL_TIMEOUT;
                break;
            }
        }

        //Clear error and half complete status
        __LL_DMA_TransErrIntPnd_Clr(Instance, ch);
        __LL_DMA_TransHalfCpltIntPnd_Clr(Instance, ch);        
    }

    //Update channel state to Ready except TIMEOUT which should keep BUSY state
    if (ret != LL_TIMEOUT) {
        dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_READY;
    }

    return ret;
}

/**
  * @}
  */


/** @defgroup DMA_LL_Exported_Functions_Interrupt DMA Interrupt Handler and Callback
  * @brief    DMA Interrupt Handler and Callback
  * @{
  */

/**
  * @brief  DMA IRQ Handler
  * @param  Instance Specifies DMA peripheral
  * @param  ch DMA Channel
  * @return None
  */
void LL_DMA_IRQHandler(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch)
{
    bool continue_en = false;

    //Assert param
    assert_param(IS_DMA_ALL_INSTANCE(Instance));
    assert_param(__LL_DMA_IsChannelValid(ch));

    if (!IS_DMA_ALL_INSTANCE(Instance) || !__LL_DMA_IsChannelValid(ch)) {
        return;
    }

    //Channel Continue Mode Get
    continue_en = ((DMA_TransModeETypeDef)__LL_DMA_TransMode_Get(Instance, ch) == DMA_TRANS_MODE_CONTINUE);

    //Channel Transfer half interrupt handler
    if (__LL_DMA_IsTransHalfCpltIntPnd(Instance, ch)) {
        //Disable Interrupt in single mode
        if (!continue_en) {
            __LL_DMA_TransHalf_Int_Dis(Instance, ch);
        }

        //Clear pending
        __LL_DMA_TransHalfCpltIntPnd_Clr(Instance, ch);

        //Interrupt callback
        if (dma_pri_ctrl.ch_ctrl[ch].half_callback) {
            dma_pri_ctrl.ch_ctrl[ch].half_callback(dma_pri_ctrl.ch_ctrl[ch].half_arg);
        }
    }

    //Channel Transfer complete interrupt handler
    if (__LL_DMA_IsTransCpltIntPnd(Instance, ch)) {
        //Disable Interrupt in single mode
        if (!continue_en) {
            __LL_DMA_TransCom_Int_Dis(Instance, ch);
            __LL_DMA_TransErr_Int_Dis(Instance, ch);
            __LL_DMA_TransHalf_Int_Dis(Instance, ch);
        }

        //Clear pending
        __LL_DMA_TransCpltIntPnd_Clr(Instance, ch);

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_READY;

        //Interrupt callback
        if (dma_pri_ctrl.ch_ctrl[ch].end_callback) {
            dma_pri_ctrl.ch_ctrl[ch].end_callback(dma_pri_ctrl.ch_ctrl[ch].end_arg);
        }
    }

    //Channel Transfer error interrupt handler
    if (__LL_DMA_IsTransErrIntPnd(Instance, ch)) {
        //Disable Interrupt when error occured
        __LL_DMA_TransCom_Int_Dis(Instance, ch);
        __LL_DMA_TransErr_Int_Dis(Instance, ch);
        __LL_DMA_TransHalf_Int_Dis(Instance, ch);

        //Clear pending
        __LL_DMA_TransErrIntPnd_Clr(Instance, ch);

        //Update channel state to Ready
        dma_pri_ctrl.ch_ctrl[ch].state = DMA_STATE_READY;

        //Interrupt callback
        if (dma_pri_ctrl.ch_ctrl[ch].err_callback) {
            dma_pri_ctrl.ch_ctrl[ch].err_callback(dma_pri_ctrl.ch_ctrl[ch].err_arg);
        }
    }
}

/**
  * @}
  */

/**
  * @}
  */


/* Private Functions ---------------------------------------------------------*/


#endif  /* LL_DMA_MODULE_ENABLED */


/**
  * @}
  */

/**
  * @}
  */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

