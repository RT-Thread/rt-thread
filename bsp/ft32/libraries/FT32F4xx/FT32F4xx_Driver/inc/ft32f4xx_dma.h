/**
  ******************************************************************************
  * @file         ft32f4xx_dma.h
  * @author       FMD AE
  * @brief        This file contains all the functions prototypes for the DMA firmware
  *               library.
  * @version      V1.0.0
  * @data         2025-04-15
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_DMA_H
#define __FT32F4XX_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


/** @addtogroup DMA
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/**
  * @brief  DMA Init structures definition
  */
typedef struct
{
    uint32_t SrcAddress;              /*!< Specifies the source address for DMAy Channelx. */
    uint32_t DstAddress;              /*!< Specifies the destination address for DMAy Channelx. */

    uint32_t BlockTransSize;          /*!< Specifies the block transfer size for DMAy Channelx.
                                         This parameter must be a number between 1 and 65535
                                         @ref DMA_block_transfer_size */

    uint32_t SrcDstMasterSel;         /*!< Specifies the source/destination master select for DMAy Channelx.
                                         This parameter can be a value of @ref DMA_src_dst_master_select  */

    uint32_t TransferTypeFlowCtl;     /*!< Specifies the transfer type and flow control for DMAy Channelx.
                                         This parameter can be a value of @ref DMA_trans_type_flow_control  */

    uint32_t SrcBurstTransferLength;  /*!< Specifies the source burst transaction length for DMAy Channelx.
                                      The number of data with a width of DMA_SrcTransWidth.
                                      This parameter can be a value of @ref DMA_src_burst_trans_length  */

    uint32_t DstBurstTransferLength;  /*!< Specifies the destination burst transaction length for DMAy Channelx.
                                      The number of data with a width of DMA_DstTransWidth.
                                      This parameter can be a value of @ref DMA_dst_burst_trans_length  */

    uint32_t SrcAddrMode;             /*!< Specifies the source address increment for DMAy Channelx.
                                         This parameter can be a value of @ref DMA_src_addr_increment_mode  */

    uint32_t DstAddrMode;             /*!< Specifies the destination address increment for DMAy Channelx.
                                         This parameter can be a value of @ref DMA_dst_addr_increment_mode  */

    uint32_t SrcTransferWidth;        /*!< Specifies the srouce transfer width for DMAy Channelx.
                                      This parameter can be a value of @ref DMA_src_trans_width  */

    uint32_t DstTransferWidth;        /*!< Specifies the destination transfer width for DMAy Channelx.
                                      This parameter can be a value of @ref DMA_dst_trans_width  */


    uint32_t DstHardwareInterface;    /*!< Specifies a hardware handshaking interface to the destination of DMAy Channelx
                                         if the CFGx.HS_SEL_DST field is 0.
                                         Each channel is equipped with 8 destination hardware handshaking interfaces, such as:
                                           DMA_DST_HARDWARE_INTERFACE_0
                                           ...
                                           DMA_DST_HARDWARE_INTERFACE_7
                                         By configuring the DstHsIfPeriphSel field, each destination hardware handshaking interface
                                         can be selectively assigned to support up to 8 peripheral requests. For example,
                                         DMA_DST_HARDWARE_INTERFACE_0 of DMA1 provieds configurable options inculding:
                                           SPI3_RX
                                           I2C1_RX
                                           TIM4_CH1
                                           LPUART_RX
                                           UART5_RX
                                           TIM5_CH3
                                           TIM5_UP
                                         This parameter can be a value of @ref DMA_dst_hardware_interface  */

    uint32_t SrcHardwareInterface;    /*!< Specifies a hardware handshaking interface to the source of DMAy Channelx
                                         if the CFGx.HS_SEL_SRC field is 0.
                                         Each channel is equipped with 8 source hardware handshaking interfaces, such as:
                                           DMA_SRC_HARDWARE_INTERFACE_0
                                           ...
                                           DMA_SRC_HARDWARE_INTERFACE_7
                                         By configuring the SrcHsIfPeriphSel field, each source hardware handshaking interface
                                         can be selectively assigned to support up to 8 peripheral requests. For example,
                                         DMA_SRC_HARDWARE_INTERFACE_0 of DMA2 provieds configurable options inculding:
                                           ADC1
                                           ADC3
                                           SPI1_RX
                                           SPDIF_CB
                                           TIM1_TRIG
                                         This parameter can be a value of @ref DMA_src_hardware_interface  */

    FunctionalState FIFOMode;         /*!< Specifies the FIFO mode select for DMAy Channelx.
                                         This parameter can be set to ENABLE or DISABLE. */

    FunctionalState FlowCtlMode;      /*!< Specifies the flow control mode for DMAy Channelx.
                                         This parameter can be set to ENABLE or DISABLE. */

    FunctionalState ReloadDst;        /*!< Specifies the automatic destination reload for DMAy Channelx.
                                         This parameter can be set to ENABLE or DISABLE. */

    FunctionalState ReloadSrc;        /*!< Specifies the automatic source reload for DMAy Channelx.
                                         This parameter can be set to ENABLE or DISABLE. */

    uint32_t MaxBurstLength;          /*!< Specifies the maximum AMBA burst length for DMAy Channelx.
                                         A value of 0 indicates that software is not limiting the
                                         maximum AMBA burst length for DMA transfers on this channel.
                                         This parameter can be a number greater than the maximum values
                                         of src_burst_size_bytes and dst_burst_size_bytes.
                                          +src_burst_size_bytes=SRC_MSIZE*SRC_TR_WIDTH;
                                          +dst_burst_size_bytes=DST_MSIZE*DST_TR_WIDTH.  */

    uint32_t SrcHsIfPol;              /*!< Specifies the source handshaking interface polarity for DMAy Channelx.
                                         This parameter can be a value of @ref DMA_src_hs_if_polarity  */

    uint32_t DstHsIfPol;              /*!< Specifies the destination handshaking interface polarity for DMAy Channelx.
                                         This parameter can be a value of @ref DMA_dst_hs_if_polarity  */

    uint32_t SrcHsSel;                /*!< Specifies the source software or handware handshaking select for DMAy Channelx.
                                         This parameter can be a value of @ref DMA_src_hs_select  */

    uint32_t DstHsSel;                /*!< Specifies the destination software or handware handshaking select for DMAy Channelx.
                                         This parameter can be a value of @ref DMA_dst_hs_select  */

    uint32_t Polarity;                /*!< Specifies the channel polarity for DMAy Channelx.
                                         This parameter can be a value of @ref DMA_channel_polarity  */

    uint32_t SrcHsIfPeriphSel;        /*!< Specifies the peripheral request for the handshake interface.
                                      This parameter can be a value of @ref DMA_src_handshake_interface_channel_select */

    uint32_t DstHsIfPeriphSel;        /*!< Specifies the peripheral request for the handshake interface.
                                      This parameter can be a value of @ref DMA_dst_handshake_interface_channel_select */

} DMA_InitTypeDef;


/**
  * @brief  DMA base address and channel index definition
  */
typedef struct
{
    DMA_TypeDef *BaseAddress;
    uint32_t     ChannelIndex;
} DMA_BaseAddressAndChannelIndex;


/**
  * @brief  DMA Software Request definition
  */
typedef enum
{
    DMA_SW_REQUEST_SRC     =  0x00U, //
    DMA_SW_REQUEST_DST     =  0x01U,
    DMA_SW_REQUEST_SRC_SGL =  0x02U,
    DMA_SW_REQUEST_DST_SGL =  0x03U,
    DMA_SW_REQUEST_SRC_LST =  0x04U,
    DMA_SW_REQUEST_DST_LST =  0x05U
} DMA_SoftwareRequestTypeDef;

#define IS_DMA_SOFTWARE_REQUEST(TYPE) (((TYPE) == DMA_SW_REQUEST_SRC)     || \
                                       ((TYPE) == DMA_SW_REQUEST_DST)     || \
                                       ((TYPE) == DMA_SW_REQUEST_SRC_SGL) || \
                                       ((TYPE) == DMA_SW_REQUEST_DST_SGL) || \
                                       ((TYPE) == DMA_SW_REQUEST_SRC_LST) || \
                                       ((TYPE) == DMA_SW_REQUEST_DST_LST) )

/**
  * @brief  DMA_interrupts_definition DMA_IT
  */
#define  DMA_IT_TFR    0x01U
#define  DMA_IT_BLOCK  0x02U
#define  DMA_IT_SRC    0x04U
#define  DMA_IT_DST    0x08U
#define  DMA_IT_ERR    0x10U

#define IS_DMA_IT(TYPE) (((TYPE) == DMA_IT_TFR)   || \
                         ((TYPE) == DMA_IT_BLOCK) || \
                         ((TYPE) == DMA_IT_SRC)   || \
                         ((TYPE) == DMA_IT_DST)   || \
                         ((TYPE) == DMA_IT_ERR))


/**
  * @brief  DMA_interrupts_flag_definition DMA_FLAG
  */
#define  DMA_FLAG_TFR    0x01U
#define  DMA_FLAG_BLOCK  0x02U
#define  DMA_FLAG_SRC    0x04U
#define  DMA_FLAG_DST    0x08U
#define  DMA_FLAG_ERR    0x10U

#define IS_DMA_FLAG(FLAG) (((FLAG) == DMA_FLAG_TFR)   || \
                           ((FLAG) == DMA_FLAG_BLOCK) || \
                           ((FLAG) == DMA_FLAG_SRC)   || \
                           ((FLAG) == DMA_FLAG_DST)   || \
                           ((FLAG) == DMA_FLAG_ERR))


/**
  * @brief  Enable the specified DMA.
  * @param  DMAx DMA base address
  * @retval None
  */
#define DMA_ENABLE(DMAx)    ((DMAx)->DMACFG |=  DMA_DMACFG_DMA_EN)


/**
  * @brief  Disable the specified DMA.
  * @param  DMAx DMA base address
  * @retval None
  */
#define DMA_DISABLE(DMAx)    ((DMAx)->DMACFG &=  ~DMA_DMACFG_DMA_EN)


/** @defgroup  DMA_block_transfer_size
  * @{
  */
#define IS_DMA_BLOCK_TRANSFER_SIZE(SIZE) (((SIZE) >= 0x1U) && ((SIZE) <= 0xFFFFU))

/**
  * @}
  */


/** @defgroup  DMA_src_dst_master_select
  * @{
  */
#define DMA_SRCMASTER1_DSTMASTER1  0U
#define DMA_SRCMASTER1_DSTMASTER2  DMA_CTL_DMS
#define DMA_SRCMASTER2_DSTMASTER1  DMA_CTL_SMS
#define DMA_SRCMASTER2_DSTMASTER2  (DMA_CTL_SMS | DMA_CTL_DMS)

#define IS_DMA_SRC_DST_MASTER_SEL(MASTER) (((MASTER) == DMA_SRCMASTER1_DSTMASTER1) || \
                                           ((MASTER) == DMA_SRCMASTER1_DSTMASTER2) || \
                                           ((MASTER) == DMA_SRCMASTER2_DSTMASTER1) || \
                                           ((MASTER) == DMA_SRCMASTER2_DSTMASTER2))
/**
  * @}
  */

/** @defgroup  DMA_trans_type_flow_control
  * @{
  */
#define DMA_TRANSFERTYPE_FLOWCTL_M2M_DMA     0U
#define DMA_TRANSFERTYPE_FLOWCTL_M2P_DMA     DMA_CTL_TT_FC_0
#define DMA_TRANSFERTYPE_FLOWCTL_P2M_DMA     DMA_CTL_TT_FC_1
#define DMA_TRANSFERTYPE_FLOWCTL_P2P_DMA     (DMA_CTL_TT_FC_0 | DMA_CTL_TT_FC_1)
#define DMA_TRANSFERTYPE_FLOWCTL_P2M_PRE     DMA_CTL_TT_FC_2
#define DMA_TRANSFERTYPE_FLOWCTL_P2P_SRCPRE  (DMA_CTL_TT_FC_0 | DMA_CTL_TT_FC_2)
#define DMA_TRANSFERTYPE_FLOWCTL_M2P_PRE     (DMA_CTL_TT_FC_1 | DMA_CTL_TT_FC_2)
#define DMA_TRANSFERTYPE_FLOWCTL_P2P_DSTPRE  DMA_CTL_TT_FC

#define IS_DMA_TRANS_TYPE_FLOW_CTL(TYPE) (((TYPE) == DMA_TRANSFERTYPE_FLOWCTL_M2M_DMA   ) || \
                                          ((TYPE) == DMA_TRANSFERTYPE_FLOWCTL_M2P_DMA   ) || \
                                          ((TYPE) == DMA_TRANSFERTYPE_FLOWCTL_P2M_DMA   ) || \
                                          ((TYPE) == DMA_TRANSFERTYPE_FLOWCTL_P2P_DMA   ) || \
                                          ((TYPE) == DMA_TRANSFERTYPE_FLOWCTL_P2M_PRE   ) || \
                                          ((TYPE) == DMA_TRANSFERTYPE_FLOWCTL_P2P_SRCPRE) || \
                                          ((TYPE) == DMA_TRANSFERTYPE_FLOWCTL_M2P_PRE   ) || \
                                          ((TYPE) == DMA_TRANSFERTYPE_FLOWCTL_P2P_DSTPRE))
/**
  * @}
  */


/** @defgroup  DMA_src_burst_trans_length
  * @{
  */
#define DMA_SRC_BURSTTRANSFERLENGTH_1         0U
#define DMA_SRC_BURSTTRANSFERLENGTH_4         DMA_CTL_SRC_MSIZE_0
#define DMA_SRC_BURSTTRANSFERLENGTH_8         DMA_CTL_SRC_MSIZE_1
#define DMA_SRC_BURSTTRANSFERLENGTH_16        DMA_CTL_SRC_MSIZE

#define IS_DMA_SRC_BURST_TRANS_LENGTH(LENGTH) (((LENGTH) == DMA_SRC_BURSTTRANSFERLENGTH_1 ) || \
                                               ((LENGTH) == DMA_SRC_BURSTTRANSFERLENGTH_4 ) || \
                                               ((LENGTH) == DMA_SRC_BURSTTRANSFERLENGTH_8 ) || \
                                               ((LENGTH) == DMA_SRC_BURSTTRANSFERLENGTH_16))
/**
  * @}
  */


/** @defgroup  DMA_dst_burst_trans_length
  * @{
  */
#define DMA_DST_BURSTTRANSFERLENGTH_1            0U
#define DMA_DST_BURSTTRANSFERLENGTH_4            DMA_CTL_SRC_MSIZE_0
#define DMA_DST_BURSTTRANSFERLENGTH_8            DMA_CTL_SRC_MSIZE_1
#define DMA_DST_BURSTTRANSFERLENGTH_16           DMA_CTL_DEST_MSIZE

#define IS_DMA_DST_BURST_TRANS_LENGTH(LENGTH) (((LENGTH) == DMA_DST_BURSTTRANSFERLENGTH_1 ) || \
                                               ((LENGTH) == DMA_DST_BURSTTRANSFERLENGTH_4 ) || \
                                               ((LENGTH) == DMA_DST_BURSTTRANSFERLENGTH_8 ) || \
                                               ((LENGTH) == DMA_DST_BURSTTRANSFERLENGTH_16))
/**
  * @}
  */


/** @defgroup  DMA_src_addr_increment_mode
  * @{
  */
#define DMA_SRC_ADDRMODE_INC         0U
#define DMA_SRC_ADDRMODE_DEC         DMA_CTL_SINC_0
#define DMA_SRC_ADDRMODE_HOLD        DMA_CTL_SINC_1

#define IS_DMA_SRC_ADDR_MODE(MODE) (((MODE) == DMA_SRC_ADDRMODE_INC ) || \
                                    ((MODE) == DMA_SRC_ADDRMODE_DEC ) || \
                                    ((MODE) == DMA_SRC_ADDRMODE_HOLD))
/**
  * @}
  */


/** @defgroup  DMA_dst_addr_increment_mode
  * @{
  */
#define DMA_DST_ADDRMODE_INC         0U
#define DMA_DST_ADDRMODE_DEC         DMA_CTL_DINC_0
#define DMA_DST_ADDRMODE_HOLD        DMA_CTL_DINC_1

#define IS_DMA_DST_ADDR_MODE(MODE) (((MODE) == DMA_DST_ADDRMODE_INC ) || \
                                    ((MODE) == DMA_DST_ADDRMODE_DEC ) || \
                                    ((MODE) == DMA_DST_ADDRMODE_HOLD))
/**
  * @}
  */


/** @defgroup  DMA_src_trans_width
  * @{
  */
#define DMA_SRC_TRANSFERWIDTH_8BITS          0U
#define DMA_SRC_TRANSFERWIDTH_16BITS         DMA_CTL_SRC_TR_WIDTH_0
#define DMA_SRC_TRANSFERWIDTH_32BITS         DMA_CTL_SRC_TR_WIDTH_1

#define IS_DMA_SRC_TRANS_WIDTH(WIDTH) (((WIDTH) == DMA_SRC_TRANSFERWIDTH_8BITS ) || \
                                       ((WIDTH) == DMA_SRC_TRANSFERWIDTH_16BITS) || \
                                       ((WIDTH) == DMA_SRC_TRANSFERWIDTH_32BITS))
/**
  * @}
  */


/** @defgroup  DMA_dst_trans_width
  * @{
  */
#define DMA_DST_TRANSFERWIDTH_8BITS          0U
#define DMA_DST_TRANSFERWIDTH_16BITS         DMA_CTL_DST_TR_WIDTH_0
#define DMA_DST_TRANSFERWIDTH_32BITS         DMA_CTL_DST_TR_WIDTH_1

#define IS_DMA_DST_TRANS_WIDTH(WIDTH) (((WIDTH) == DMA_DST_TRANSFERWIDTH_8BITS ) || \
                                       ((WIDTH) == DMA_DST_TRANSFERWIDTH_16BITS) || \
                                       ((WIDTH) == DMA_DST_TRANSFERWIDTH_32BITS))
/**
  * @}
  */


/** @defgroup  DMA_dst_hardware_interface
  * @{
  */
#define DMA_DST_HARDWARE_INTERFACE_0    0U
#define DMA_DST_HARDWARE_INTERFACE_1    1U
#define DMA_DST_HARDWARE_INTERFACE_2    2U
#define DMA_DST_HARDWARE_INTERFACE_3    3U
#define DMA_DST_HARDWARE_INTERFACE_4    4U
#define DMA_DST_HARDWARE_INTERFACE_5    5U
#define DMA_DST_HARDWARE_INTERFACE_6    6U
#define DMA_DST_HARDWARE_INTERFACE_7    7U

#define IS_DMA_DST_HW_IF(IF) (((IF) == DMA_DST_HARDWARE_INTERFACE_0) || \
                              ((IF) == DMA_DST_HARDWARE_INTERFACE_1) || \
                              ((IF) == DMA_DST_HARDWARE_INTERFACE_2) || \
                              ((IF) == DMA_DST_HARDWARE_INTERFACE_3) || \
                              ((IF) == DMA_DST_HARDWARE_INTERFACE_4) || \
                              ((IF) == DMA_DST_HARDWARE_INTERFACE_5) || \
                              ((IF) == DMA_DST_HARDWARE_INTERFACE_6) || \
                              ((IF) == DMA_DST_HARDWARE_INTERFACE_7))
/**
  * @}
  */


/** @defgroup  DMA_src_hardware_interface
  * @{
  */
#define DMA_SRC_HARDWARE_INTERFACE_0    0U
#define DMA_SRC_HARDWARE_INTERFACE_1    1U
#define DMA_SRC_HARDWARE_INTERFACE_2    2U
#define DMA_SRC_HARDWARE_INTERFACE_3    3U
#define DMA_SRC_HARDWARE_INTERFACE_4    4U
#define DMA_SRC_HARDWARE_INTERFACE_5    5U
#define DMA_SRC_HARDWARE_INTERFACE_6    6U
#define DMA_SRC_HARDWARE_INTERFACE_7    7U

#define IS_DMA_SRC_HW_IF(IF) (((IF) == DMA_SRC_HARDWARE_INTERFACE_0) || \
                              ((IF) == DMA_SRC_HARDWARE_INTERFACE_1) || \
                              ((IF) == DMA_SRC_HARDWARE_INTERFACE_2) || \
                              ((IF) == DMA_SRC_HARDWARE_INTERFACE_3) || \
                              ((IF) == DMA_SRC_HARDWARE_INTERFACE_4) || \
                              ((IF) == DMA_SRC_HARDWARE_INTERFACE_5) || \
                              ((IF) == DMA_SRC_HARDWARE_INTERFACE_6) || \
                              ((IF) == DMA_SRC_HARDWARE_INTERFACE_7))
/**
  * @}
  */


///** @defgroup  DMA_fifo_mode_select
//  * @{
//  */
//#define DMA_FIFOMODE_DISABLE  0U
//#define DMA_FIFOMODE_ENABLE   1U
////#define DMA_FIFOMODE_ENABLE   DMA_CFG_FIFO_MODE
//
//#define IS_DMA_FIFO_MODE_STATE(STATE) (((STATE) == DMA_FIFOMODE_DISABLE) || \
//                                       ((STATE) == DMA_FIFOMODE_ENABLE ))
///**
//  * @}
//  */


///** @defgroup  DMA_fc_mode
//  * @{
//  */
//#define DMA_FLOWCTLMODE_DISABLE  0U
//#define DMA_FLOWCTLMODE_ENABLE   1U
////#define DMA_FLOWCTLMODE_ENABLE   DMA_CFG_FCMODE
//
//#define IS_DMA_FCMODE_STATE(STATE) (((STATE) == DMA_FLOWCTLMODE_DISABLE) || \
//                                    ((STATE) == DMA_FLOWCTLMODE_ENABLE ))
///**
//  * @}
//  */


///** @defgroup  DMA_reload_destination
//  * @{
//  */
//#define DMA_RELOADDST_DISABLE  0U
//#define DMA_RELOADDST_ENABLE   1U
//
//#define IS_DMA_RELOAD_DST_STATE(STATE) (((STATE) == DMA_RELOADDST_DISABLE) || \
//                                        ((STATE) == DMA_RELOADDST_ENABLE ))
///**
//  * @}
//  */
//
//
///** @defgroup  DMA_reload_source
//  * @{
//  */
//#define DMA_RELOADSRC_DISABLE  0U
//#define DMA_RELOADSRC_ENABLE   1U
//
//#define IS_DMA_RELOAD_SRC_STATE(STATE) (((STATE) == DMA_RELOADSRC_DISABLE) || \
//                                        ((STATE) == DMA_RELOADSRC_ENABLE ))
///**
//  * @}
//  */


/** @defgroup  DMA_src_hs_if_polarity
  * @{
  */
#define DMA_SRCHSIFPOL_HIGH  0U
#define DMA_SRCHSIFPOL_LOW   1U

#define IS_DMA_SRC_HS_IF_POL(MODE) (((MODE) == DMA_SRCHSIFPOL_HIGH) || \
                                    ((MODE) == DMA_SRCHSIFPOL_LOW ))
/**
  * @}
  */


/** @defgroup  DMA_dst_hs_if_polarity
  * @{
  */
#define DMA_DSTHSIFPOL_HIGH  0U
#define DMA_DSTHSIFPOL_LOW   1U

#define IS_DMA_DST_HS_IF_POL(MODE) (((MODE) == DMA_DSTHSIFPOL_HIGH) || \
                                    ((MODE) == DMA_DSTHSIFPOL_LOW ))
/**
  * @}
  */


/** @defgroup  DMA_src_hs_select
  * @{
  */
#define DMA_SRCHSSEL_HARDWARE  0U
#define DMA_SRCHSSEL_SOFTWARE  1U

#define IS_DMA_SRC_HS_SEL(MODE) (((MODE) == DMA_SRCHSSEL_HARDWARE) || \
                                 ((MODE) == DMA_SRCHSSEL_SOFTWARE))
/**
  * @}
  */


/** @defgroup  DMA_dst_hs_select
  * @{
  */
#define DMA_DSTHSSEL_HARDWARE  0U
#define DMA_DSTHSSEL_SOFTWARE  1U

#define IS_DMA_DST_HS_SEL(MODE) (((MODE) == DMA_DSTHSSEL_HARDWARE) || \
                                 ((MODE) == DMA_DSTHSSEL_SOFTWARE))
/**
  * @}
  */


/** @defgroup  DMA_channel_suspend
  * @{
  */
#define DMA_CHANNELSUSPEND_DISABLE  0U
#define DMA_CHANNELSUSPEND_ENABLE   1U

#define IS_DMA_CHANNEL_SUSPEND_STATE(STATE) (((STATE) == DMA_CHANNELSUSPEND_DISABLE) || \
                                             ((STATE) == DMA_CHANNELSUSPEND_ENABLE ))
/**
  * @}
  */


/** @defgroup  DMA_channel_polarity
  * @{
  */
#define DMA_CH_POLARITY_0  0U
#define DMA_CH_POLARITY_1  1U
#define DMA_CH_POLARITY_2  2U
#define DMA_CH_POLARITY_3  3U
#define DMA_CH_POLARITY_4  4U
#define DMA_CH_POLARITY_5  5U
#define DMA_CH_POLARITY_6  6U
#define DMA_CH_POLARITY_7  7U

#define IS_DMA_CHANNEL_POLARITY(POLARITY) (((POLARITY) == DMA_CH_POLARITY_0) || \
                                           ((POLARITY) == DMA_CH_POLARITY_1) || \
                                           ((POLARITY) == DMA_CH_POLARITY_2) || \
                                           ((POLARITY) == DMA_CH_POLARITY_3) || \
                                           ((POLARITY) == DMA_CH_POLARITY_4) || \
                                           ((POLARITY) == DMA_CH_POLARITY_5) || \
                                           ((POLARITY) == DMA_CH_POLARITY_6) || \
                                           ((POLARITY) == DMA_CH_POLARITY_7))
/**
  * @}
  */


/** @defgroup  DMA_enable
  * @{
  */
#define DMA_Disable  ((uint64_t)0x0000000000000000)
#define DMA_Enable   ((uint64_t)0x0000000000000001)

#define IS_DMA_ENABLE(STATUS) (((STATUS) == DMA_Disable) || ((STATUS) == DMA_Enable))
/**
  * @}
  */


/** @defgroup  DMA_channel_enable_write
  * @{
  */
#define DMA_ChannelEnable_EN_0  ((uint64_t)0x0000000000000100)
#define DMA_ChannelEnable_EN_1  ((uint64_t)0x0000000000000200)
#define DMA_ChannelEnable_EN_2  ((uint64_t)0x0000000000000400)
#define DMA_ChannelEnable_EN_3  ((uint64_t)0x0000000000000800)
#define DMA_ChannelEnable_EN_4  ((uint64_t)0x0000000000001000)
#define DMA_ChannelEnable_EN_5  ((uint64_t)0x0000000000002000)
#define DMA_ChannelEnable_EN_6  ((uint64_t)0x0000000000004000)
#define DMA_ChannelEnable_EN_7  ((uint64_t)0x0000000000008000)

#define IS_DMA_CHANNEL_ENABLE_EN(CHANNEL) (((CHANNEL) == DMA_ChannelEnable_EN_0) || \
                                           ((CHANNEL) == DMA_ChannelEnable_EN_1) || \
                                           ((CHANNEL) == DMA_ChannelEnable_EN_2) || \
                                           ((CHANNEL) == DMA_ChannelEnable_EN_3) || \
                                           ((CHANNEL) == DMA_ChannelEnable_EN_4) || \
                                           ((CHANNEL) == DMA_ChannelEnable_EN_5) || \
                                           ((CHANNEL) == DMA_ChannelEnable_EN_6) || \
                                           ((CHANNEL) == DMA_ChannelEnable_EN_7))

/**
  * @}
  */

/** @defgroup  DMA_channel_enable
  * @{
  */
#define DMA_ChannelEnable_0  ((uint64_t)0x0000000000000001)
#define DMA_ChannelEnable_1  ((uint64_t)0x0000000000000002)
#define DMA_ChannelEnable_2  ((uint64_t)0x0000000000000004)
#define DMA_ChannelEnable_3  ((uint64_t)0x0000000000000008)
#define DMA_ChannelEnable_4  ((uint64_t)0x0000000000000010)
#define DMA_ChannelEnable_5  ((uint64_t)0x0000000000000020)
#define DMA_ChannelEnable_6  ((uint64_t)0x0000000000000040)
#define DMA_ChannelEnable_7  ((uint64_t)0x0000000000000080)

#define IS_DMA_CHANNEL_ENABLE(CHANNEL) (((CHANNEL) == DMA_ChannelEnable_0) || \
                                        ((CHANNEL) == DMA_ChannelEnable_1) || \
                                        ((CHANNEL) == DMA_ChannelEnable_2) || \
                                        ((CHANNEL) == DMA_ChannelEnable_3) || \
                                        ((CHANNEL) == DMA_ChannelEnable_4) || \
                                        ((CHANNEL) == DMA_ChannelEnable_5) || \
                                        ((CHANNEL) == DMA_ChannelEnable_6) || \
                                        ((CHANNEL) == DMA_ChannelEnable_7))

/**
  * @}
  */

/** @defgroup  DMA_src_handshake_interface_channel_select
  * @{
  */
#define DMA_SRC_HANDSHAKE_INTERFACE_SEL_0  0U
#define DMA_SRC_HANDSHAKE_INTERFACE_SEL_1  1U
#define DMA_SRC_HANDSHAKE_INTERFACE_SEL_2  2U
#define DMA_SRC_HANDSHAKE_INTERFACE_SEL_3  3U
#define DMA_SRC_HANDSHAKE_INTERFACE_SEL_4  4U
#define DMA_SRC_HANDSHAKE_INTERFACE_SEL_5  5U
#define DMA_SRC_HANDSHAKE_INTERFACE_SEL_6  6U
#define DMA_SRC_HANDSHAKE_INTERFACE_SEL_7  7U

#define IS_DMA_SRC_HANDSHAKE_INTERFACE_SEL(CH) (((CH) == DMA_SRC_HANDSHAKE_INTERFACE_SEL_0) || \
                                                ((CH) == DMA_SRC_HANDSHAKE_INTERFACE_SEL_1) || \
                                                ((CH) == DMA_SRC_HANDSHAKE_INTERFACE_SEL_2) || \
                                                ((CH) == DMA_SRC_HANDSHAKE_INTERFACE_SEL_3) || \
                                                ((CH) == DMA_SRC_HANDSHAKE_INTERFACE_SEL_4) || \
                                                ((CH) == DMA_SRC_HANDSHAKE_INTERFACE_SEL_5) || \
                                                ((CH) == DMA_SRC_HANDSHAKE_INTERFACE_SEL_6) || \
                                                ((CH) == DMA_SRC_HANDSHAKE_INTERFACE_SEL_7) )

/**
  * @}
  */

/** @defgroup  DMA_dst_handshake_interface_channel_select
  * @{
  */
#define DMA_DST_HANDSHAKE_INTERFACE_SEL_0  0U
#define DMA_DST_HANDSHAKE_INTERFACE_SEL_1  1U
#define DMA_DST_HANDSHAKE_INTERFACE_SEL_2  2U
#define DMA_DST_HANDSHAKE_INTERFACE_SEL_3  3U
#define DMA_DST_HANDSHAKE_INTERFACE_SEL_4  4U
#define DMA_DST_HANDSHAKE_INTERFACE_SEL_5  5U
#define DMA_DST_HANDSHAKE_INTERFACE_SEL_6  6U
#define DMA_DST_HANDSHAKE_INTERFACE_SEL_7  7U

#define IS_DMA_DST_HANDSHAKE_INTERFACE_SEL(CH) (((CH) == DMA_DST_HANDSHAKE_INTERFACE_SEL_0) || \
                                                ((CH) == DMA_DST_HANDSHAKE_INTERFACE_SEL_1) || \
                                                ((CH) == DMA_DST_HANDSHAKE_INTERFACE_SEL_2) || \
                                                ((CH) == DMA_DST_HANDSHAKE_INTERFACE_SEL_3) || \
                                                ((CH) == DMA_DST_HANDSHAKE_INTERFACE_SEL_4) || \
                                                ((CH) == DMA_DST_HANDSHAKE_INTERFACE_SEL_5) || \
                                                ((CH) == DMA_DST_HANDSHAKE_INTERFACE_SEL_6) || \
                                                ((CH) == DMA_DST_HANDSHAKE_INTERFACE_SEL_7) )

/**
  * @}
  */


/** @defgroup DMA_Instances_definition
  * @{
  */
#define IS_DMA_ALL_INSTANCE(INSTANCE) (((INSTANCE) == DMA1_Channel0) || \
                                       ((INSTANCE) == DMA1_Channel1) || \
                                       ((INSTANCE) == DMA1_Channel2) || \
                                       ((INSTANCE) == DMA1_Channel3) || \
                                       ((INSTANCE) == DMA1_Channel4) || \
                                       ((INSTANCE) == DMA1_Channel5) || \
                                       ((INSTANCE) == DMA1_Channel6) || \
                                       ((INSTANCE) == DMA1_Channel7) || \
                                       ((INSTANCE) == DMA2_Channel0) || \
                                       ((INSTANCE) == DMA2_Channel1) || \
                                       ((INSTANCE) == DMA2_Channel2) || \
                                       ((INSTANCE) == DMA2_Channel3) || \
                                       ((INSTANCE) == DMA2_Channel4) || \
                                       ((INSTANCE) == DMA2_Channel5) || \
                                       ((INSTANCE) == DMA2_Channel6) || \
                                       ((INSTANCE) == DMA2_Channel7))
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


/* Function used to set the DMA configuration to the default reset state ******/
void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);

/* Initialization and Configuration functions *********************************/
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* Init);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);

/* DMA and channel enable functions *********************************/
void DMA_Channel_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);

/* Data Counter function******************************************************/
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);

/* DMA software request function **********************************/
void DMA_SoftWare_Request(DMA_Channel_TypeDef* DMAy_Channelx, DMA_SoftwareRequestTypeDef SoftwareRequest);

/* DMA base address and channel index calculate function **********************************/
DMA_BaseAddressAndChannelIndex CalBaseAddressAndChannelIndex(DMA_Channel_TypeDef* DMAy_Channelx);

/* Interrupts and flags management functions **********************************/
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t DMA_IT, FunctionalState NewState);
void DMA_ClearFlagStatus(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t DMA_IT);
ITStatus DMA_GetITStatus(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t DMA_IT);
FlagStatus DMA_GetFlagStatus(DMA_Channel_TypeDef* DMAy_Channelx, uint8_t DMA_FLAG);


/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_DMA_H */


/************************ (C) COPYRIGHT FMD *****END OF FILE****/
