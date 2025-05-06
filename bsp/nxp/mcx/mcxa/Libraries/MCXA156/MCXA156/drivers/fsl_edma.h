/*
 * Copyright 2022-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_EDMA_H_
#define FSL_EDMA_H_

#include "fsl_common.h"
#include "fsl_edma_core.h"
/*!
 * @addtogroup edma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief eDMA driver version */
#define FSL_EDMA_DRIVER_VERSION (MAKE_VERSION(2, 10, 0)) /*!< Version 2.10.0. */
/*! @} */

/*! @brief eDMA driver name */
#ifndef FSL_EDMA_DRIVER_EDMA4
#define FSL_EDMA_DRIVER_EDMA4 (1)
#endif

/*!@brief Macro used for allocate edma TCD */
#define EDMA_ALLOCATE_TCD(name, number) AT_NONCACHEABLE_SECTION_ALIGN(edma_tcd_t name[number], EDMA_TCD_ALIGN_SIZE)

/*! @brief _edma_transfer_status eDMA transfer status */
enum
{
    kStatus_EDMA_QueueFull = MAKE_STATUS(kStatusGroup_EDMA, 0), /*!< TCD queue is full. */
    kStatus_EDMA_Busy      = MAKE_STATUS(kStatusGroup_EDMA, 1), /*!< Channel is busy and can't handle the
                                                                     transfer request. */
};

/*! @brief Compute the offset unit from DCHPRI3 */
#define DMA_DCHPRI_INDEX(channel) (((channel) & ~0x03U) | (3U - ((channel)&0x03U)))

/*! @brief eDMA transfer configuration */
typedef enum _edma_transfer_size
{
    kEDMA_TransferSize1Bytes = 0x0U, /*!< Source/Destination data transfer size is 1 byte every time */
    kEDMA_TransferSize2Bytes = 0x1U, /*!< Source/Destination data transfer size is 2 bytes every time */
    kEDMA_TransferSize4Bytes = 0x2U, /*!< Source/Destination data transfer size is 4 bytes every time */
#if (defined(FSL_FEATURE_EDMA_SUPPORT_8_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_8_BYTES_TRANSFER)
    kEDMA_TransferSize8Bytes = 0x3U, /*!< Source/Destination data transfer size is 8 bytes every time */
#endif
#if (defined(FSL_FEATURE_EDMA_SUPPORT_16_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_16_BYTES_TRANSFER)
    kEDMA_TransferSize16Bytes = 0x4U, /*!< Source/Destination data transfer size is 16 bytes every time */
#endif
    kEDMA_TransferSize32Bytes = 0x5U, /*!< Source/Destination data transfer size is 32 bytes every time */
#if (defined(FSL_FEATURE_EDMA_SUPPORT_64_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_64_BYTES_TRANSFER)
    kEDMA_TransferSize64Bytes = 0x6U, /*!< Source/Destination data transfer size is 64 bytes every time */
#endif
#if (defined(FSL_FEATURE_EDMA_SUPPORT_128_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_128_BYTES_TRANSFER)
    kEDMA_TransferSize128Bytes = 0x7U, /*!< Source/Destination data transfer size is 128 bytes every time */
#endif
} edma_transfer_size_t;

/*! @brief eDMA modulo configuration */
typedef enum _edma_modulo
{
    kEDMA_ModuloDisable = 0x0U, /*!< Disable modulo */
    kEDMA_Modulo2bytes,         /*!< Circular buffer size is 2 bytes. */
    kEDMA_Modulo4bytes,         /*!< Circular buffer size is 4 bytes. */
    kEDMA_Modulo8bytes,         /*!< Circular buffer size is 8 bytes. */
    kEDMA_Modulo16bytes,        /*!< Circular buffer size is 16 bytes. */
    kEDMA_Modulo32bytes,        /*!< Circular buffer size is 32 bytes. */
    kEDMA_Modulo64bytes,        /*!< Circular buffer size is 64 bytes. */
    kEDMA_Modulo128bytes,       /*!< Circular buffer size is 128 bytes. */
    kEDMA_Modulo256bytes,       /*!< Circular buffer size is 256 bytes. */
    kEDMA_Modulo512bytes,       /*!< Circular buffer size is 512 bytes. */
    kEDMA_Modulo1Kbytes,        /*!< Circular buffer size is 1 K bytes. */
    kEDMA_Modulo2Kbytes,        /*!< Circular buffer size is 2 K bytes. */
    kEDMA_Modulo4Kbytes,        /*!< Circular buffer size is 4 K bytes. */
    kEDMA_Modulo8Kbytes,        /*!< Circular buffer size is 8 K bytes. */
    kEDMA_Modulo16Kbytes,       /*!< Circular buffer size is 16 K bytes. */
    kEDMA_Modulo32Kbytes,       /*!< Circular buffer size is 32 K bytes. */
    kEDMA_Modulo64Kbytes,       /*!< Circular buffer size is 64 K bytes. */
    kEDMA_Modulo128Kbytes,      /*!< Circular buffer size is 128 K bytes. */
    kEDMA_Modulo256Kbytes,      /*!< Circular buffer size is 256 K bytes. */
    kEDMA_Modulo512Kbytes,      /*!< Circular buffer size is 512 K bytes. */
    kEDMA_Modulo1Mbytes,        /*!< Circular buffer size is 1 M bytes. */
    kEDMA_Modulo2Mbytes,        /*!< Circular buffer size is 2 M bytes. */
    kEDMA_Modulo4Mbytes,        /*!< Circular buffer size is 4 M bytes. */
    kEDMA_Modulo8Mbytes,        /*!< Circular buffer size is 8 M bytes. */
    kEDMA_Modulo16Mbytes,       /*!< Circular buffer size is 16 M bytes. */
    kEDMA_Modulo32Mbytes,       /*!< Circular buffer size is 32 M bytes. */
    kEDMA_Modulo64Mbytes,       /*!< Circular buffer size is 64 M bytes. */
    kEDMA_Modulo128Mbytes,      /*!< Circular buffer size is 128 M bytes. */
    kEDMA_Modulo256Mbytes,      /*!< Circular buffer size is 256 M bytes. */
    kEDMA_Modulo512Mbytes,      /*!< Circular buffer size is 512 M bytes. */
    kEDMA_Modulo1Gbytes,        /*!< Circular buffer size is 1 G bytes. */
    kEDMA_Modulo2Gbytes,        /*!< Circular buffer size is 2 G bytes. */
} edma_modulo_t;

#if defined FSL_FEATURE_EDMA_HAS_BANDWIDTH && FSL_FEATURE_EDMA_HAS_BANDWIDTH
/*! @brief Bandwidth control */
typedef enum _edma_bandwidth
{
    kEDMA_BandwidthStallNone   = 0x0U, /*!< No eDMA engine stalls. */
    kEDMA_BandwidthStall4Cycle = 0x2U, /*!< eDMA engine stalls for 4 cycles after each read/write. */
    kEDMA_BandwidthStall8Cycle = 0x3U, /*!< eDMA engine stalls for 8 cycles after each read/write. */
} edma_bandwidth_t;
#endif

/*! @brief Channel link type */
typedef enum _edma_channel_link_type
{
    kEDMA_LinkNone = 0x0U, /*!< No channel link  */
    kEDMA_MinorLink,       /*!< Channel link after each minor loop */
    kEDMA_MajorLink,       /*!< Channel link while major loop count exhausted */
} edma_channel_link_type_t;

/*!@brief _edma_channel_status_flags eDMA channel status flags. */
enum
{
    kEDMA_DoneFlag      = 0x1U, /*!< DONE flag, set while transfer finished, CITER value exhausted*/
    kEDMA_ErrorFlag     = 0x2U, /*!< eDMA error flag, an error occurred in a transfer */
    kEDMA_InterruptFlag = 0x4U, /*!< eDMA interrupt flag, set while an interrupt occurred of this channel */
};

/*! @brief _edma_error_status_flags eDMA channel error status flags. */
enum
{
    kEDMA_DestinationBusErrorFlag = DMA_ERR_DBE_FLAG, /*!< Bus error on destination address */
    kEDMA_SourceBusErrorFlag      = DMA_ERR_SBE_FLAG, /*!< Bus error on the source address */
    kEDMA_ScatterGatherErrorFlag  = DMA_ERR_SGE_FLAG, /*!< Error on the Scatter/Gather address, not 32byte aligned. */
    kEDMA_NbytesErrorFlag         = DMA_ERR_NCE_FLAG, /*!< NBYTES/CITER configuration error */
    kEDMA_DestinationOffsetErrorFlag  = DMA_ERR_DOE_FLAG, /*!< Destination offset not aligned with destination size */
    kEDMA_DestinationAddressErrorFlag = DMA_ERR_DAE_FLAG, /*!< Destination address not aligned with destination size */
    kEDMA_SourceOffsetErrorFlag       = DMA_ERR_SOE_FLAG, /*!< Source offset not aligned with source size */
    kEDMA_SourceAddressErrorFlag      = DMA_ERR_SAE_FLAG, /*!< Source address not aligned with source size*/
    kEDMA_ErrorChannelFlag = DMA_ERR_ERRCHAN_FLAG,        /*!< Error channel number of the cancelled channel number */
#if defined(FSL_FEATURE_EDMA_HAS_PRIORITY_ERROR) && (FSL_FEATURE_EDMA_HAS_PRIORITY_ERROR > 1)
    kEDMA_ChannelPriorityErrorFlag = DMA_ERR_CPE_FLAG,    /*!< Channel priority is not unique. */
#endif
    kEDMA_TransferCanceledFlag = DMA_ERR_ECX_FLAG,        /*!< Transfer cancelled */
#if defined(FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT) && (FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 1)
    kEDMA_GroupPriorityErrorFlag = DMA_ERR_GPE_FLAG,      /*!< Group priority is not unique. */
#endif
    kEDMA_ValidFlag = (int)DMA_ERR_FLAG,                  /*!< No error occurred, this bit is 0. Otherwise, it is 1. */
};

/*! @brief _edma_interrupt_enable eDMA interrupt source */
enum
{
    kEDMA_ErrorInterruptEnable = 0x1U,                  /*!< Enable interrupt while channel error occurs. */
    kEDMA_MajorInterruptEnable = DMA_CSR_INTMAJOR_MASK, /*!< Enable interrupt while major count exhausted. */
    kEDMA_HalfInterruptEnable  = DMA_CSR_INTHALF_MASK,  /*!< Enable interrupt while major count to half value. */
};

/*! @brief eDMA transfer type */
typedef enum _edma_transfer_type
{
    kEDMA_MemoryToMemory = 0x0U,  /*!< Transfer from memory to memory */
    kEDMA_PeripheralToMemory,     /*!< Transfer from peripheral to memory */
    kEDMA_MemoryToPeripheral,     /*!< Transfer from memory to peripheral */
    kEDMA_PeripheralToPeripheral, /*!< Transfer from Peripheral to peripheral */
} edma_transfer_type_t;

/*! @brief eDMA channel priority configuration */
typedef struct _edma_channel_Preemption_config
{
    bool enableChannelPreemption; /*!< If true: a channel can be suspended by other channel with higher priority */
    bool enablePreemptAbility;    /*!< If true: a channel can suspend other channel with low priority */
    uint8_t channelPriority;      /*!< Channel priority */
} edma_channel_Preemption_config_t;

/*! @brief eDMA minor offset configuration */
typedef struct _edma_minor_offset_config
{
    bool enableSrcMinorOffset;  /*!< Enable(true) or Disable(false) source minor loop offset. */
    bool enableDestMinorOffset; /*!< Enable(true) or Disable(false) destination minor loop offset. */
    uint32_t minorOffset;       /*!< Offset for a minor loop mapping. */
} edma_minor_offset_config_t;

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG && FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG
#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_MEMORY_ATTRIBUTE && FSL_FEATURE_EDMA_HAS_CHANNEL_MEMORY_ATTRIBUTE
/*! @brief eDMA channel memory attribute */
typedef enum edma_channel_memory_attribute
{
    kEDMA_ChannelNoWriteNoReadNoCacheNoBuffer =
        0x0U, /*!< No write allocate, no read allocate, non-cacheable, non-bufferable. */
    kEDMA_ChannelNoWriteNoReadNoCacheBufferable,   /*!< No write allocate, no read allocate, non-cacheable, bufferable.
                                                    */
    kEDMA_ChannelNoWriteNoReadCacheableNoBuffer,   /*!< No write allocate, no read allocate, cacheable, non-bufferable.
                                                    */
    kEDMA_ChannelNoWriteNoReadCacheableBufferable, /*!< No write allocate, no read allocate, cacheable, bufferable. */
    kEDMA_ChannelNoWriteReadNoCacheNoBuffer,   /*!< No write allocate, read allocate, non-cacheable, non-bufferable. */
    kEDMA_ChannelNoWriteReadNoCacheBufferable, /*!< No write allocate, read allocate, non-cacheable, bufferable. */
    kEDMA_ChannelNoWriteReadCacheableNoBuffer, /*!< No write allocate, read allocate, cacheable, non-bufferable. */
    kEDMA_ChannelNoWriteReadCacheableBufferable, /*!< No write allocate, read allocate, cacheable, bufferable. */
    kEDMA_ChannelWriteNoReadNoCacheNoBuffer,   /*!< write allocate, no read allocate, non-cacheable, non-bufferable. */
    kEDMA_ChannelWriteNoReadNoCacheBufferable, /*!< write allocate, no read allocate, non-cacheable, bufferable. */
    kEDMA_ChannelWriteNoReadCacheableNoBuffer, /*!< write allocate, no read allocate, cacheable, non-bufferable. */
    kEDMA_ChannelWriteNoReadCacheableBufferable, /*!< write allocate, no read allocate, cacheable, bufferable. */
    kEDMA_ChannelWriteReadNoCacheNoBuffer,       /*!< write allocate, read allocate, non-cacheable, non-bufferable. */
    kEDMA_ChannelWriteReadNoCacheBufferable,     /*!< write allocate, read allocate, non-cacheable, bufferable. */
    kEDMA_ChannelWriteReadCacheableNoBuffer,     /*!< write allocate, read allocate, cacheable, non-bufferable. */
    kEDMA_ChannelWriteReadCacheableBufferable,   /*!< write allocate, read allocate, cacheable, bufferable. */
} edma_channel_memory_attribute_t;
#endif

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE && FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE
/*! @brief eDMA4 channel swap size */
typedef enum _edma_channel_swap_size
{
    kEDMA_ChannelSwapDisabled       = 0x0U,  /*!< Swap is disabled. */
    kEDMA_ChannelReadWith8bitSwap   = 0x1U,  /*!< Swap occurs with respect to the read 8bit. */
    kEDMA_ChannelReadWith16bitSwap  = 0x2U,  /*!< Swap occurs with respect to the read 16bit. */
    kEDMA_ChannelReadWith32bitSwap  = 0x3U,  /*!< Swap occurs with respect to the read 32bit. */
    kEDMA_ChannelWriteWith8bitSwap  = 0x9U,  /*!< Swap occurs with respect to the write 8bit. */
    kEDMA_ChannelWriteWith16bitSwap = 0x10U, /*!< Swap occurs with respect to the write 16bit. */
    kEDMA_ChannelWriteWith32bitSwap = 0x11U, /*!< Swap occurs with respect to the write 32bit. */
} edma_channel_swap_size_t;
#endif

/*! @brief eDMA channel system bus information, _edma_channel_sys_bus_info*/
enum
{
#if !(defined(FSL_FEATURE_EDMA_HAS_NO_CH_SBR_ATTR) && FSL_FEATURE_EDMA_HAS_NO_CH_SBR_ATTR)
    kEDMA_AttributeOutput = DMA_CH_SBR_ATTR_MASK, /*!< DMA's AHB system bus attribute output value. */
#endif

    kEDMA_PrivilegedAccessLevel = DMA_CH_SBR_PAL_MASK, /*!< Privileged Access Level for DMA transfers. 0b - User
                                                          protection level; 1b - Privileged protection level. */
    kEDMA_MasterId =
        DMA_CH_SBR_MID_MASK, /*!< DMA's master ID when channel is active and master ID replication is enabled. */
};

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE && FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE
/*! @brief eDMA4 channel access type */
typedef enum _edma_channel_access_type
{
    kEDMA_ChannelDataAccess        = 0x0U, /*!< Data access for eDMA4 transfers. */
    kEDMA_ChannelInstructionAccess = 0x1U, /*!< Instruction access for eDMA4 transfers. */
} edma_channel_access_type_t;
#endif

/*! @brief eDMA4 channel protection level */
typedef enum _edma_channel_protection_level
{
    kEDMA_ChannelProtectionLevelUser       = 0x0U, /*!< user protection level for eDMA transfers. */
    kEDMA_ChannelProtectionLevelPrivileged = 0x1U, /*!< Privileged protection level eDMA transfers. */
} edma_channel_protection_level_t;

#if !(defined(FSL_FEATURE_EDMA_HAS_NO_CH_SBR_SEC) && FSL_FEATURE_EDMA_HAS_NO_CH_SBR_SEC)

/*! @brief eDMA4 channel security level */
typedef enum _edma_channel_security_level
{
    kEDMA_ChannelSecurityLevelNonSecure = 0x0U, /*!< non secure  level for eDMA transfers. */
    kEDMA_ChannelSecurityLevelSecure    = 0x1U, /*!< secure level for eDMA transfers. */
} edma_channel_security_level_t;
#endif

/*! @brief eDMA4 channel configuration*/
typedef struct _edma_channel_config
{
    edma_channel_Preemption_config_t channelPreemptionConfig; /*!< channel preemption configuration */

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_MEMORY_ATTRIBUTE && FSL_FEATURE_EDMA_HAS_CHANNEL_MEMORY_ATTRIBUTE
    edma_channel_memory_attribute_t channelReadMemoryAttribute;  /*!< channel memory read attribute configuration */
    edma_channel_memory_attribute_t channelWriteMemoryAttribute; /*!< channel memory write attribute configuration */
#endif

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE && FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE
    edma_channel_swap_size_t channelSwapSize; /*!< channel swap size configuration */
#endif

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE && FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE
    edma_channel_access_type_t channelAccessType; /*!< channel access type configuration */
#endif

    uint8_t channelDataSignExtensionBitPosition; /*!< channel data sign extension bit psition configuration */

#if (defined FSL_FEATURE_EDMA_HAS_CHANNEL_MUX && FSL_FEATURE_EDMA_HAS_CHANNEL_MUX) || (defined FSL_FEATURE_EDMA_HAS_MP_CHANNEL_MUX && FSL_FEATURE_EDMA_HAS_MP_CHANNEL_MUX)
    int channelRequestSource; /*!< hardware service request source for the channel */
#endif

    bool enableMasterIDReplication;                  /*!< enable master ID replication */
#if !(defined(FSL_FEATURE_EDMA_HAS_NO_CH_SBR_SEC) && FSL_FEATURE_EDMA_HAS_NO_CH_SBR_SEC)
    edma_channel_security_level_t securityLevel;     /*!< security level */
#endif
    edma_channel_protection_level_t protectionLevel; /*!< protection level */

} edma_channel_config_t;
#endif

/*!
 * @brief eDMA TCD.
 *
 * This structure is same as TCD register which is described in reference manual,
 * and is used to configure the scatter/gather feature as a next hardware TCD.
 */
typedef edma_core_tcd_t edma_tcd_t;

/*! @brief edma4 channel transfer configuration
 *
 * The transfer configuration structure support full feature configuration of the transfer control descriptor.
 *
 * @note User should pay attention to the transfer size alignment limitation
 *       1. the bytesEachRequest should align with the  srcWidthOfEachTransfer and the dstWidthOfEachTransfer
 *          that is to say bytesEachRequest % srcWidthOfEachTransfer should be 0
 *       2. the srcOffsetOfEachTransfer and dstOffsetOfEachTransfer must be aligne with transfer width
 *       3. the totalBytes should align with the bytesEachRequest
 *       4. the srcAddr should align with the srcWidthOfEachTransfer
 *       5. the dstAddr should align with the dstWidthOfEachTransfer
 *       6. the srcAddr should align with srcAddrModulo if modulo feature is enabled
 *       7. the dstAddr should align with dstAddrModulo if modulo feature is enabled
 *       If anyone of above condition can not be satisfied, the edma4 interfaces will generate assert error.
 *
 * 1.To perform a simple transfer, below members should be initialized at least
 * .srcAddr - source address
 * .dstAddr - destination address
 * .srcWidthOfEachTransfer - data width of source address
 * .dstWidthOfEachTransfer - data width of destination address, normally it should be as same as
 * srcWidthOfEachTransfer .bytesEachRequest - bytes to be transferred in each DMA request .totalBytes - total
 * bytes to be transferred .srcOffsetOfEachTransfer - offset value in bytes unit to be applied to source address as
 * each source read is completed .dstOffsetOfEachTransfer - offset value in bytes unit to be applied to destination
 * address as each destination write is completed enablchannelRequest - channel request can be enabled together with
 * transfer configure submission
 *
 * 2.The transfer configuration structure also support advance feature:
 * Programmable source/destination address range(MODULO)
 * Programmable minor loop offset
 * Programmable major loop offset
 * Programmable channel chain feature
 * Programmable channel transfer control descriptor link feature
 *
 */
typedef struct _edma_transfer_config
{
    uint32_t srcAddr;                      /*!< Source data address. */
    uint32_t destAddr;                     /*!< Destination data address. */
    edma_transfer_size_t srcTransferSize;  /*!< Source data transfer size. */
    edma_transfer_size_t destTransferSize; /*!< Destination data transfer size. */
    int16_t srcOffset;                     /*!< Sign-extended offset value in byte unit applied to the current source
                                                address to form the next-state   value as each source read is completed */
    int16_t destOffset;              /*!< Sign-extended offset value in byte unit applied to the current destination
                         address to form the next-state value as each destination write is completed. */
    uint32_t minorLoopBytes;         /*!< bytes in each minor loop or each request
                                      * range: 1 - (2^30 -1) when minor loop mapping is enabled
                                      * range: 1 - (2^10 - 1) when minor loop mapping is enabled and source or dest minor
                                      * loop offset is enabled
                                      * range: 1 - (2^32 - 1) when minor loop mapping is disabled
                                      */
    uint32_t majorLoopCounts;        /*!< minor loop counts in each major loop, should be 1 at least for each
                                      * transfer range: (0 - (2^15 - 1)) when minor loop channel link is
                                      * disabled range: (0 - (2^9 - 1)) when minor loop channel link is enabled
                                      * total bytes in a transfer = minorLoopCountsEachMajorLoop *
                                      * bytesEachMinorLoop
                                      */

    uint16_t enabledInterruptMask;   /*!< channel interrupt to enable, can be OR'ed value of _edma_interrupt_enable */

    edma_modulo_t srcAddrModulo;     /*!< source circular data queue range */
    int32_t srcMajorLoopOffset;      /*!< source major loop offset */

    edma_modulo_t dstAddrModulo;     /*!< destination circular data queue range */
    int32_t dstMajorLoopOffset;      /*!< destination major loop offset */

    bool enableSrcMinorLoopOffset;   /*!< enable source minor loop offset */
    bool enableDstMinorLoopOffset;   /*!< enable dest minor loop offset */
    int32_t minorLoopOffset;         /*!< burst offset, the offset will be applied after minor loop update */

    bool enableChannelMajorLoopLink; /*!< channel link when major loop complete */
    uint32_t majorLoopLinkChannel;   /*!< major loop link channel number */

    bool enableChannelMinorLoopLink; /*!< channel link when minor loop complete */
    uint32_t minorLoopLinkChannel;   /*!< minor loop link channel number */

    edma_tcd_t *linkTCD;             /*!< pointer to the link transfer control descriptor */
} edma_transfer_config_t;

/*! @brief eDMA global configuration structure.*/
typedef struct _edma_config
{
#if defined FSL_FEATURE_EDMA_HAS_CONTINUOUS_LINK_MODE && FSL_FEATURE_EDMA_HAS_CONTINUOUS_LINK_MODE
    bool enableContinuousLinkMode; /*!< Enable (true) continuous link mode. Upon minor loop completion, the channel
                                        activates again if that channel has a minor loop channel link enabled and
                                        the link channel is itself. */
#endif

#if defined FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION && FSL_FEATURE_EDMA_HAS_GLOBAL_MASTER_ID_REPLICATION
    bool enableMasterIdReplication; /*!< Enable (true) master ID replication. If Master ID replication is disabled, the
                                        privileged protection level (supervisor mode) for eDMA4 transfers is used. */
#endif

    bool enableGlobalChannelLink; /*!< Enable(true) channel linking is available and controlled by each channel's link
                                     settings. */

    bool enableHaltOnError;       /*!< Enable (true) transfer halt on error. Any error causes the HALT bit to set.
                                Subsequently, all service requests are ignored until the HALT bit is cleared.*/

    bool enableDebugMode;         /*!< Enable(true) eDMA4 debug mode. When in debug mode, the eDMA4 stalls the start of
                                       a new channel. Executing channels are allowed to complete. */

    bool enableRoundRobinArbitration; /*!< Enable(true) channel linking is available and controlled by each channel's
                                     link settings. */
#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG && FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG
    edma_channel_config_t *channelConfig[FSL_FEATURE_EDMA_MODULE_CHANNEL]; /*!< channel preemption configuration */
#endif
} edma_config_t;

/*! @brief Callback for eDMA */
struct _edma_handle;

/*! @brief Define callback function for eDMA.
 *
 * This callback function is called in the EDMA interrupt handle.
 * In normal mode, run into callback function means the transfer users need is done.
 * In scatter gather mode, run into callback function means a transfer control block (tcd) is finished. Not
 * all transfer finished, users can get the finished tcd numbers using interface EDMA_GetUnusedTCDNumber.
 *
 * @param handle EDMA handle pointer, users shall not touch the values inside.
 * @param userData The callback user parameter pointer. Users can use this parameter to involve things users need to
 *                 change in EDMA callback function.
 * @param transferDone If the current loaded transfer done. In normal mode it means if all transfer done. In scatter
 *                     gather mode, this parameter shows is the current transfer block in EDMA register is done. As the
 *                     load of core is different, it will be different if the new tcd loaded into EDMA registers while
 *                     this callback called. If true, it always means new tcd still not loaded into registers, while
 *                     false means new tcd already loaded into registers.
 * @param tcds How many tcds are done from the last callback. This parameter only used in scatter gather mode. It
 *             tells user how many tcds are finished between the last callback and this.
 */
typedef void (*edma_callback)(struct _edma_handle *handle, void *userData, bool transferDone, uint32_t tcds);

/*! @brief eDMA transfer handle structure */
typedef struct _edma_handle
{
    edma_callback callback; /*!< Callback function for major count exhausted. */
    void *userData;         /*!< Callback function parameter. */

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG && FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG
    EDMA_ChannelType *channelBase; /*!< eDMA peripheral channel base address. */
#endif
    EDMA_Type *base;               /*!< eDMA peripheral base address*/
    EDMA_TCDType *tcdBase;         /*!< eDMA peripheral tcd base address. */

    edma_tcd_t *tcdPool;           /*!< Pointer to memory stored TCDs. */
    uint32_t channel;              /*!< eDMA channel number. */

    volatile int8_t header; /*!< The first TCD index. Should point to the next TCD to be loaded into the eDMA engine. */
    volatile int8_t tail;   /*!< The last TCD index. Should point to the next TCD to be stored into the memory pool. */
    volatile int8_t tcdUsed; /*!< The number of used TCD slots. Should reflect the number of TCDs can be used/loaded in
                                the memory. */
    volatile int8_t tcdSize; /*!< The total number of TCD slots in the queue. */
} edma_handle_t;
/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name eDMA initialization and de-initialization
 * @{
 */

/*!
 * @brief Initializes the eDMA peripheral.
 *
 * This function ungates the eDMA clock and configures the eDMA peripheral according
 * to the configuration structure.
 *
 * @param base eDMA peripheral base address.
 * @param config A pointer to the configuration structure, see "edma_config_t".
 * @note This function enables the minor loop map feature.
 */
void EDMA_Init(EDMA_Type *base, const edma_config_t *config);

/*!
 * @brief Deinitializes the eDMA peripheral.
 *
 * This function gates the eDMA clock.
 *
 * @param base eDMA peripheral base address.
 */
void EDMA_Deinit(EDMA_Type *base);

/*!
 * @brief Push content of TCD structure into hardware TCD register.
 *
 * @param base EDMA peripheral base address.
 * @param channel EDMA channel number.
 * @param tcd Point to TCD structure.
 */
void EDMA_InstallTCD(EDMA_Type *base, uint32_t channel, edma_tcd_t *tcd);

/*!
 * @brief Gets the eDMA default configuration structure.
 *
 * This function sets the configuration structure to default values.
 * The default configuration is set to the following values.
 * @code
 *   config.enableContinuousLinkMode = false;
 *   config.enableHaltOnError = true;
 *   config.enableRoundRobinArbitration = false;
 *   config.enableDebugMode = false;
 * @endcode
 *
 * @param config A pointer to the eDMA configuration structure.
 */
void EDMA_GetDefaultConfig(edma_config_t *config);

#if defined(FSL_FEATURE_DMA_HAS_CONTINUOUS_CHANNEL_LINK) && FSL_FEATURE_DMA_HAS_CONTINUOUS_CHANNEL_LINK
/*!
 * @brief Enable/Disable continuous channel link mode.
 *
 * @note Do not use continuous link mode with a channel linking to itself if there is only one minor loop
 * iteration per service request, for example, if the channel's NBYTES value is the same as either
 * the source or destination size. The same data transfer profile can be achieved by simply
 * increasing the NBYTES value, which provides more efficient, faster processing.
 *
 * @param base EDMA peripheral base address.
 * @param enable true is enable, false is disable.
 */
static inline void EDMA_EnableContinuousChannelLinkMode(EDMA_Type *base, bool enable)
{
    if (enable)
    {
        EDMA_BASE(base)->CR |= DMA_CR_CLM_MASK;
    }
    else
    {
        EDMA_BASE(base)->CR &= ~DMA_CR_CLM_MASK;
    }
}
#endif

#if defined(FSL_FEATURE_DMA_HAS_MINOR_LOOP_MAPPING) && FSL_FEATURE_DMA_HAS_MINOR_LOOP_MAPPING
/*!
 * @brief Enable/Disable minor loop mapping.
 *
 * The TCDn.word2 is redefined to include individual enable fields, an offset field, and the
 * NBYTES field.
 *
 * @param base EDMA peripheral base address.
 * @param enable true is enable, false is disable.
 */
static inline void EDMA_EnableMinorLoopMapping(EDMA_Type *base, bool enable)
{
    if (enable)
    {
        EDMA_BASE(base)->CR |= DMA_CR_EMLM_MASK;
    }
    else
    {
        EDMA_BASE(base)->CR &= ~DMA_CR_EMLM_MASK;
    }
}
#endif

/*! @} */
/*!
 * @name eDMA Channel Operation
 * @{
 */

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG && FSL_FEATURE_EDMA_HAS_CHANNEL_CONFIG
/*!
 * @brief EDMA Channel initialization
 *
 * @param base eDMA4 peripheral base address.
 * @param channel eDMA4 channel number.
 * @param channelConfig pointer to user's eDMA4 channel config structure, see edma_channel_config_t for detail.
 */
void EDMA_InitChannel(EDMA_Type *base, uint32_t channel, edma_channel_config_t *channelConfig);

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_MEMORY_ATTRIBUTE && FSL_FEATURE_EDMA_HAS_CHANNEL_MEMORY_ATTRIBUTE
/*!
 * @brief Set channel memory attribute.
 *
 * @param base eDMA4 peripheral base address.
 * @param channel eDMA4 channel number.
 * @param writeAttribute Attributes associated with a write transaction.
 * @param readAttribute Attributes associated with a read transaction.
 */
static inline void EDMA_SetChannelMemoryAttribute(EDMA_Type *base,
                                                  uint32_t channel,
                                                  edma_channel_memory_attribute_t writeAttribute,
                                                  edma_channel_memory_attribute_t readAttribute)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

    if (0U != (uint32_t)FSL_FEATURE_EDMA_INSTANCE_HAS_CHANNEL_MEMORY_ATTRIBUTEn(base))
    {
#if defined FSL_FEATURE_EDMA_HAS_MP_CHANNEL_MUX && FSL_FEATURE_EDMA_HAS_MP_CHANNEL_MUX
        if ((uint32_t)FSL_FEATURE_EDMA_INSTANCE_HAS_MP_CHANNEL_MUXn(base) == 1U)
        {
            EDMA_CHANNEL_BASE(base, channel)->CH_REGS.EDMA5_REG.CH_MATTR =
                DMA_CH_MATTR_WCACHE(writeAttribute) | DMA_CH_MATTR_RCACHE(readAttribute);
        }
        else
#endif
        {
            EDMA_CHANNEL_BASE(base, channel)->CH_REGS.EDMA4_REG.CH_MATTR =
                DMA_CH_MATTR_WCACHE(writeAttribute) | DMA_CH_MATTR_RCACHE(readAttribute);
        }
    }
}
#endif

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_SIGN_EXTENSION && FSL_FEATURE_EDMA_HAS_CHANNEL_SIGN_EXTENSION
/*!
 * @brief Set channel sign extension.
 *
 * @param base eDMA4 peripheral base address.
 * @param channel eDMA4 channel number.
 * @param position A non-zero value specifing the sign extend bit position.
 *                 If 0, sign extension is disabled.
 */
static inline void EDMA_SetChannelSignExtension(EDMA_Type *base, uint32_t channel, uint8_t position)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

    if (0U != (uint32_t)FSL_FEATURE_EDMA_INSTANCE_HAS_CHANNEL_SIGN_EXTENSIONn(base))
    {
        EDMA_CHANNEL_BASE(base, channel)->CH_CSR =
            (EDMA_CHANNEL_BASE(base, channel)->CH_CSR & (~DMA_CH_CSR_SIGNEXT_MASK)) |
            ((uint32_t)position << DMA_CH_CSR_SIGNEXT_SHIFT);
    }
}
#endif

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE && FSL_FEATURE_EDMA_HAS_CHANNEL_SWAP_SIZE
/*!
 * @brief Set channel swap size.
 *
 * @param base eDMA4 peripheral base address.
 * @param channel eDMA4 channel number.
 * @param swapSize Swap occurs with respect to the specified transfer size.
 *                 If 0, swap is disabled.
 */
static inline void EDMA_SetChannelSwapSize(EDMA_Type *base, uint32_t channel, edma_channel_swap_size_t swapSize)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

    if (0U != (uint32_t)FSL_FEATURE_EDMA_INSTANCE_HAS_CHANNEL_SWAP_SIZEn(base))
    {
        EDMA_CHANNEL_BASE(base, channel)->CH_CSR =
            (EDMA_CHANNEL_BASE(base, channel)->CH_CSR & (~DMA_CH_CSR_SWAP_MASK)) |
            ((uint32_t)swapSize << DMA_CH_CSR_SWAP_SHIFT);
    }
}
#endif

#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE && FSL_FEATURE_EDMA_HAS_CHANNEL_ACCESS_TYPE
/*!
 * @brief Set channel access type.
 *
 * @param base eDMA4 peripheral base address.
 * @param channel eDMA4 channel number.
 * @param channelAccessType eDMA4's transactions type on the system bus when the channel is active.
 */
static inline void EDMA_SetChannelAccessType(EDMA_Type *base,
                                             uint32_t channel,
                                             edma_channel_access_type_t channelAccessType)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

    if (0U != (uint32_t)FSL_FEATURE_EDMA_INSTANCE_HAS_CHANNEL_ACCESS_TYPEn(base))
    {
#if defined FSL_FEATURE_EDMA_HAS_PROT_REGISTER && FSL_FEATURE_EDMA_HAS_PROT_REGISTER
        if (FSL_FEATURE_EDMA_INSTANCE_HAS_PROT_REGISTERn(base) == 1)
        {
            EDMA_MP_BASE(base)->MP_REGS.EDMA5_REG.CH_PROT[channel] =
                (EDMA_MP_BASE(base)->MP_REGS.EDMA5_REG.CH_PROT[channel] & (~DMA_CH_SBR_INSTR_MASK)) |
                ((uint32_t)channelAccessType << DMA_CH_SBR_INSTR_SHIFT);
        }
        else
#endif
        {
            EDMA_CHANNEL_BASE(base, channel)->CH_SBR =
                (EDMA_CHANNEL_BASE(base, channel)->CH_SBR & (~DMA_CH_SBR_INSTR_MASK)) |
                ((uint32_t)channelAccessType << DMA_CH_SBR_INSTR_SHIFT);
        }
    }
}
#endif

#if (defined FSL_FEATURE_EDMA_HAS_CHANNEL_MUX && FSL_FEATURE_EDMA_HAS_CHANNEL_MUX) || \
    (defined FSL_FEATURE_EDMA_HAS_MP_CHANNEL_MUX && FSL_FEATURE_EDMA_HAS_MP_CHANNEL_MUX)
/*!
 * @brief Set channel request source.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param channelRequestSource eDMA hardware service request source for the channel. User need to use
 *                             the dma_request_source_t type as the input parameter. Note that devices
 *                             may use other enum type to express dma request source and User can fined it in
 *                             SOC header or fsl_edma_soc.h.
 */
static inline void EDMA_SetChannelMux(EDMA_Type *base, uint32_t channel, int32_t channelRequestSource)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

    if ((uint32_t)FSL_FEATURE_EDMA_INSTANCE_HAS_CHANNEL_MUXn(base) == 1U)
    {
        /* Reset channel mux */
#if defined FSL_FEATURE_EDMA_HAS_MP_CHANNEL_MUX && FSL_FEATURE_EDMA_HAS_MP_CHANNEL_MUX
        if ((uint32_t)FSL_FEATURE_EDMA_INSTANCE_HAS_MP_CHANNEL_MUXn(base) == 1U)
        {
            EDMA_MP_BASE(base)->MP_REGS.EDMA5_REG.CH_MUX[channel] = DMA_CH_MUX_SOURCE(0);
            EDMA_MP_BASE(base)->MP_REGS.EDMA5_REG.CH_MUX[channel] = DMA_CH_MUX_SOURCE(channelRequestSource);
        }
        else
#endif
        {
#if defined FSL_FEATURE_EDMA_HAS_CHANNEL_MUX && FSL_FEATURE_EDMA_HAS_CHANNEL_MUX
            EDMA_CHANNEL_BASE(base, channel)->CH_REGS.EDMA4_REG.CH_MUX = DMA_CH_MUX_SOURCE(0);
            EDMA_CHANNEL_BASE(base, channel)->CH_REGS.EDMA4_REG.CH_MUX = DMA_CH_MUX_SOURCE(channelRequestSource);
#endif
        }
    }
}
#endif

/*!
 * @brief Gets the channel identification and attribute information on the system bus interface.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @return The mask of the channel system bus information. Users need to use the
 *         _edma_channel_sys_bus_info type to decode the return variables.
 */
static inline uint32_t EDMA_GetChannelSystemBusInformation(EDMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

    return EDMA_CHANNEL_BASE(base, channel)->CH_SBR;
}

/*!
 * @brief Set channel master ID replication.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param enable true is enable, false is disable.
 */
static inline void EDMA_EnableChannelMasterIDReplication(EDMA_Type *base, uint32_t channel, bool enable)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

#if defined FSL_FEATURE_EDMA_HAS_PROT_REGISTER && FSL_FEATURE_EDMA_HAS_PROT_REGISTER
    if (FSL_FEATURE_EDMA_INSTANCE_HAS_PROT_REGISTERn(base) == 1)
    {
        if (enable)
        {
            EDMA_MP_BASE(base)->MP_REGS.EDMA5_REG.CH_PROT[channel] |= DMA_CH_SBR_EMI_MASK;
        }
        else
        {
            EDMA_MP_BASE(base)->MP_REGS.EDMA5_REG.CH_PROT[channel] &= ~DMA_CH_SBR_EMI_MASK;
        }
    }
    else
#endif
    {
        if (enable)
        {
            EDMA_CHANNEL_BASE(base, channel)->CH_SBR |= DMA_CH_SBR_EMI_MASK;
        }
        else
        {
            EDMA_CHANNEL_BASE(base, channel)->CH_SBR &= ~DMA_CH_SBR_EMI_MASK;
        }
    }
}

#if !(defined(FSL_FEATURE_EDMA_HAS_NO_CH_SBR_SEC) && FSL_FEATURE_EDMA_HAS_NO_CH_SBR_SEC)
/*!
 * @brief Set channel security level.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param level security level.
 */
static inline void EDMA_SetChannelSecurityLevel(EDMA_Type *base, uint32_t channel, edma_channel_security_level_t level)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

#if defined FSL_FEATURE_EDMA_HAS_PROT_REGISTER && FSL_FEATURE_EDMA_HAS_PROT_REGISTER
    if (FSL_FEATURE_EDMA_INSTANCE_HAS_PROT_REGISTERn(base) == 1)
    {
        if (level == kEDMA_ChannelSecurityLevelSecure)
        {
            EDMA_MP_BASE(base)->MP_REGS.EDMA5_REG.CH_PROT[channel] |= DMA_CH_SBR_SEC_MASK;
        }
        else
        {
            EDMA_MP_BASE(base)->MP_REGS.EDMA5_REG.CH_PROT[channel] &= ~DMA_CH_SBR_SEC_MASK;
        }
    }
    else
#endif
    {
        if (level == kEDMA_ChannelSecurityLevelSecure)
        {
            EDMA_CHANNEL_BASE(base, channel)->CH_SBR |= DMA_CH_SBR_SEC_MASK;
        }
        else
        {
            EDMA_CHANNEL_BASE(base, channel)->CH_SBR &= ~DMA_CH_SBR_SEC_MASK;
        }
    }
}
#endif

/*!
 * @brief Set channel security level.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param level security level.
 */
static inline void EDMA_SetChannelProtectionLevel(EDMA_Type *base,
                                                  uint32_t channel,
                                                  edma_channel_protection_level_t level)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

#if defined FSL_FEATURE_EDMA_HAS_PROT_REGISTER && FSL_FEATURE_EDMA_HAS_PROT_REGISTER
    if (FSL_FEATURE_EDMA_INSTANCE_HAS_PROT_REGISTERn(base) == 1)
    {
        if (level == kEDMA_ChannelProtectionLevelPrivileged)
        {
            EDMA_MP_BASE(base)->MP_REGS.EDMA5_REG.CH_PROT[channel] |= DMA_CH_SBR_PAL_MASK;
        }
        else
        {
            EDMA_MP_BASE(base)->MP_REGS.EDMA5_REG.CH_PROT[channel] &= ~DMA_CH_SBR_PAL_MASK;
        }
    }
    else
#endif
    {
        if (level == kEDMA_ChannelProtectionLevelPrivileged)
        {
            EDMA_CHANNEL_BASE(base, channel)->CH_SBR |= DMA_CH_SBR_PAL_MASK;
        }
        else
        {
            EDMA_CHANNEL_BASE(base, channel)->CH_SBR &= ~DMA_CH_SBR_PAL_MASK;
        }
    }
}

#endif
/*!
 * @brief Sets all TCD registers to default values.
 *
 * This function sets TCD registers for this channel to default values.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @note This function must not be called while the channel transfer is ongoing
 *       or it causes unpredictable results.
 * @note This function enables the auto stop request feature.
 */
void EDMA_ResetChannel(EDMA_Type *base, uint32_t channel);

/*!
 * @brief Configures the eDMA transfer attribute.
 *
 * This function configures the transfer attribute, including source address, destination address,
 * transfer size, address offset, and so on. It also configures the scatter gather feature if the
 * user supplies the TCD address.
 * Example:
 * @code
 *  edma_transfer_t config;
 *  edma_tcd_t tcd;
 *  config.srcAddr = ..;
 *  config.destAddr = ..;
 *  ...
 *  EDMA_SetTransferConfig(DMA0, channel, &config, &stcd);
 * @endcode
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param config Pointer to eDMA transfer configuration structure.
 * @param nextTcd Point to TCD structure. It can be NULL if users
 *                do not want to enable scatter/gather feature.
 * @note If nextTcd is not NULL, it means scatter gather feature is enabled
 *       and DREQ bit is cleared in the previous transfer configuration, which
 *       is set in the eDMA_ResetChannel.
 */
void EDMA_SetTransferConfig(EDMA_Type *base,
                            uint32_t channel,
                            const edma_transfer_config_t *config,
                            edma_tcd_t *nextTcd);

/*!
 * @brief Configures the eDMA minor offset feature.
 *
 * The minor offset means that the signed-extended value is added to the source address or destination
 * address after each minor loop.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param config A pointer to the minor offset configuration structure.
 */
void EDMA_SetMinorOffsetConfig(EDMA_Type *base, uint32_t channel, const edma_minor_offset_config_t *config);

/*!
 * @brief Configures the eDMA channel preemption feature.
 *
 * This function configures the channel preemption attribute and the priority of the channel.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number
 * @param config A pointer to the channel preemption configuration structure.
 */
void EDMA_SetChannelPreemptionConfig(EDMA_Type *base, uint32_t channel, const edma_channel_Preemption_config_t *config);

/*!
 * @brief Sets the channel link for the eDMA transfer.
 *
 * This function configures either the minor link or the major link mode. The minor link means that the channel link is
 * triggered every time CITER decreases by 1. The major link means that the channel link is triggered when the CITER is
 * exhausted.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param type A channel link type, which can be one of the following:
 *   @arg kEDMA_LinkNone
 *   @arg kEDMA_MinorLink
 *   @arg kEDMA_MajorLink
 * @param linkedChannel The linked channel number.
 * @note Users should ensure that DONE flag is cleared before calling this interface, or the configuration is invalid.
 */
void EDMA_SetChannelLink(EDMA_Type *base, uint32_t channel, edma_channel_link_type_t type, uint32_t linkedChannel);

#if defined FSL_FEATURE_EDMA_HAS_BANDWIDTH && FSL_FEATURE_EDMA_HAS_BANDWIDTH
/*!
 * @brief Sets the bandwidth for the eDMA transfer.
 *
 * Because the eDMA processes the minor loop, it continuously generates read/write sequences
 * until the minor count is exhausted. The bandwidth forces the eDMA to stall after the completion of
 * each read/write access to control the bus request bandwidth seen by the crossbar switch.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param bandWidth A bandwidth setting, which can be one of the following:
 *     @arg kEDMABandwidthStallNone
 *     @arg kEDMABandwidthStall4Cycle
 *     @arg kEDMABandwidthStall8Cycle
 */
void EDMA_SetBandWidth(EDMA_Type *base, uint32_t channel, edma_bandwidth_t bandWidth);
#endif

/*!
 * @brief Sets the source modulo and the destination modulo for the eDMA transfer.
 *
 * This function defines a specific address range specified to be the value after (SADDR + SOFF)/(DADDR + DOFF)
 * calculation is performed or the original register value. It provides the ability to implement a circular data
 * queue easily.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param srcModulo A source modulo value.
 * @param destModulo A destination modulo value.
 */
void EDMA_SetModulo(EDMA_Type *base, uint32_t channel, edma_modulo_t srcModulo, edma_modulo_t destModulo);

#if defined(FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT) && FSL_FEATURE_EDMA_ASYNCHRO_REQUEST_CHANNEL_COUNT
/*!
 * @brief Enables an async request for the eDMA transfer.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param enable The command to enable (true) or disable (false).
 */
static inline void EDMA_EnableAsyncRequest(EDMA_Type *base, uint32_t channel, bool enable)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

#if defined FSL_EDMA_SOC_IP_EDMA && FSL_EDMA_SOC_IP_EDMA
    EDMA_BASE(base)->EARS &= ~((uint32_t)1U << channel);
    EDMA_BASE(base)->EARS |= ((uint32_t)(true == enable ? 1U : 0U) << channel);
#else
    if (enable)
    {
        EDMA_CHANNEL_BASE(base, channel)->CH_CSR |= DMA_CH_CSR_EARQ_MASK;
    }
    else
    {
        EDMA_CHANNEL_BASE(base, channel)->CH_CSR &= ~DMA_CH_CSR_EARQ_MASK;
    }
#endif
}
#endif

/*!
 * @brief Enables an auto stop request for the eDMA transfer.
 *
 * If enabling the auto stop request, the eDMA hardware automatically disables the hardware channel request.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param enable The command to enable (true) or disable (false).
 */
static inline void EDMA_EnableAutoStopRequest(EDMA_Type *base, uint32_t channel, bool enable)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

    if (enable)
    {
        EDMA_TCD_CSR(EDMA_TCD_BASE(base, channel), EDMA_TCD_TYPE(base)) |= DMA_CSR_DREQ_MASK;
    }
    else
    {
        EDMA_TCD_CSR(EDMA_TCD_BASE(base, channel), EDMA_TCD_TYPE(base)) &= ~(uint16_t)DMA_CSR_DREQ_MASK;
    }
}

/*!
 * @brief Enables the interrupt source for the eDMA transfer.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_EnableChannelInterrupts(EDMA_Type *base, uint32_t channel, uint32_t mask);

/*!
 * @brief Disables the interrupt source for the eDMA transfer.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param mask The mask of the interrupt source to be set. Use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_DisableChannelInterrupts(EDMA_Type *base, uint32_t channel, uint32_t mask);

/*!
 * @brief Configures the eDMA channel TCD major offset feature.
 *
 * Adjustment value added to the source address at the completion of the major iteration count
 *
 * @param base eDMA peripheral base address.
 * @param channel edma channel number.
 * @param sourceOffset source address offset will be applied to source address after major loop done.
 * @param destOffset destination address offset will be applied to source address after major loop done.
 */
void EDMA_SetMajorOffsetConfig(EDMA_Type *base, uint32_t channel, int32_t sourceOffset, int32_t destOffset);

/*! @} */
/*!
 * @name eDMA TCD Operation
 * @{
 */
/*!
 * @brief Sets TCD fields according to the user's channel transfer configuration structure, @ref
 * edma_transfer_config_t.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_ConfigChannelSoftwareTCDExt
 *
 * Application should be careful about the TCD pool buffer storage class,
 * - For the platform has cache, the software TCD should be put in non cache section
 * - The TCD pool buffer should have a consistent storage class.
 *
 * @param tcd Pointer to the TCD structure.
 * @param transfer channel transfer configuration pointer.
 *
 * @note This function enables the auto stop request feature.
 */
void EDMA_ConfigChannelSoftwareTCD(edma_tcd_t *tcd, const edma_transfer_config_t *transfer);

/*!
 * @brief Sets all fields to default values for the TCD structure.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_TcdResetExt
 *
 * This function sets all fields for this TCD structure to default value.
 *
 * @param tcd Pointer to the TCD structure.
 * @note This function enables the auto stop request feature.
 */
void EDMA_TcdReset(edma_tcd_t *tcd);

/*!
 * @brief Configures the eDMA TCD transfer attribute.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_TcdSetTransferConfigExt
 *
 * The TCD is a transfer control descriptor. The content of the TCD is the same as the hardware TCD registers.
 * The TCD is used in the scatter-gather mode.
 * This function configures the TCD transfer attribute, including source address, destination address,
 * transfer size, address offset, and so on. It also configures the scatter gather feature if the
 * user supplies the next TCD address.
 * Example:
 * @code
 *   edma_transfer_t config = {
 *   ...
 *   }
 *   edma_tcd_t tcd __aligned(32);
 *   edma_tcd_t nextTcd __aligned(32);
 *   EDMA_TcdSetTransferConfig(&tcd, &config, &nextTcd);
 * @endcode
 *
 * @param tcd Pointer to the TCD structure.
 * @param config Pointer to eDMA transfer configuration structure.
 * @param nextTcd Pointer to the next TCD structure. It can be NULL if users
 *                do not want to enable scatter/gather feature.
 * @note TCD address should be 32 bytes aligned or it causes an eDMA error.
 * @note If the nextTcd is not NULL, the scatter gather feature is enabled
 *       and DREQ bit is cleared in the previous transfer configuration, which
 *       is set in the EDMA_TcdReset.
 */
void EDMA_TcdSetTransferConfig(edma_tcd_t *tcd, const edma_transfer_config_t *config, edma_tcd_t *nextTcd);

/*!
 * @brief Configures the eDMA TCD minor offset feature.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_TcdSetMinorOffsetConfigExt
 *
 * A minor offset is a signed-extended value added to the source address or a destination
 * address after each minor loop.
 *
 * @param tcd A point to the TCD structure.
 * @param config A pointer to the minor offset configuration structure.
 */
void EDMA_TcdSetMinorOffsetConfig(edma_tcd_t *tcd, const edma_minor_offset_config_t *config);

/*!
 * @brief Sets the channel link for the eDMA TCD.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_TcdSetChannelLinkExt
 *
 * This function configures either a minor link or a major link. The minor link means the channel link is
 * triggered every time CITER decreases by 1. The major link means that the channel link  is triggered when the CITER is
 * exhausted.
 *
 * @note Users should ensure that DONE flag is cleared before calling this interface, or the configuration is invalid.
 * @param tcd Point to the TCD structure.
 * @param type Channel link type, it can be one of:
 *   @arg kEDMA_LinkNone
 *   @arg kEDMA_MinorLink
 *   @arg kEDMA_MajorLink
 * @param linkedChannel The linked channel number.
 */
void EDMA_TcdSetChannelLink(edma_tcd_t *tcd, edma_channel_link_type_t type, uint32_t linkedChannel);

#if defined FSL_FEATURE_EDMA_HAS_BANDWIDTH && FSL_FEATURE_EDMA_HAS_BANDWIDTH
/*!
 * @brief Sets the bandwidth for the eDMA TCD.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_TcdSetBandWidthExt
 *
 * Because the eDMA processes the minor loop, it continuously generates read/write sequences
 * until the minor count is exhausted. The bandwidth forces the eDMA to stall after the completion of
 * each read/write access to control the bus request bandwidth seen by the crossbar switch.
 * @param tcd A pointer to the TCD structure.
 * @param bandWidth A bandwidth setting, which can be one of the following:
 *     @arg kEDMABandwidthStallNone
 *     @arg kEDMABandwidthStall4Cycle
 *     @arg kEDMABandwidthStall8Cycle
 */
static inline void EDMA_TcdSetBandWidth(edma_tcd_t *tcd, edma_bandwidth_t bandWidth)
{
    assert(tcd != NULL);

    EDMA_TCD_CSR(tcd, kEDMA_EDMA4Flag) =
        (uint16_t)((EDMA_TCD_CSR(tcd, kEDMA_EDMA4Flag) & (~DMA_CSR_BWC_MASK)) | DMA_CSR_BWC(bandWidth));
}
#endif

/*!
 * @brief Sets the source modulo and the destination modulo for the eDMA TCD.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_TcdSetModuloExt
 *
 * This function defines a specific address range specified to be the value after (SADDR + SOFF)/(DADDR + DOFF)
 * calculation is performed or the original register value. It provides the ability to implement a circular data
 * queue easily.
 *
 * @param tcd A pointer to the TCD structure.
 * @param srcModulo A source modulo value.
 * @param destModulo A destination modulo value.
 */
void EDMA_TcdSetModulo(edma_tcd_t *tcd, edma_modulo_t srcModulo, edma_modulo_t destModulo);

/*!
 * @brief Sets the auto stop request for the eDMA TCD.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_TcdEnableAutoStopRequestExt
 *
 * If enabling the auto stop request, the eDMA hardware automatically disables the hardware channel request.
 *
 * @param tcd A pointer to the TCD structure.
 * @param enable The command to enable (true) or disable (false).
 */
static inline void EDMA_TcdEnableAutoStopRequest(edma_tcd_t *tcd, bool enable)
{
    assert(tcd != NULL);

    EDMA_TCD_CSR(tcd, kEDMA_EDMA4Flag) = (uint16_t)((EDMA_TCD_CSR(tcd, kEDMA_EDMA4Flag) & (~DMA_CSR_DREQ_MASK)) |
                                                    DMA_CSR_DREQ((true == enable ? 1U : 0U)));
}

/*!
 * @brief Enables the interrupt source for the eDMA TCD.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_TcdEnableInterruptsExt
 *
 * @param tcd Point to the TCD structure.
 * @param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_TcdEnableInterrupts(edma_tcd_t *tcd, uint32_t mask);

/*!
 * @brief Disables the interrupt source for the eDMA TCD.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_TcdDisableInterruptsExt
 *
 * @param tcd Point to the TCD structure.
 * @param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_TcdDisableInterrupts(edma_tcd_t *tcd, uint32_t mask);

/*!
 * @brief Configures the eDMA TCD major offset feature.
 *
 * @Note This API only supports EDMA4 TCD type. It can be used to support all types with extension API @ref
 * EDMA_TcdSetMajorOffsetConfigExt
 *
 * Adjustment value added to the source address at the completion of the major iteration count
 *
 * @param tcd A point to the TCD structure.
 * @param sourceOffset source address offset wiil be applied to source address after major loop done.
 * @param destOffset destination address offset will be applied to source address after major loop done.
 */
void EDMA_TcdSetMajorOffsetConfig(edma_tcd_t *tcd, int32_t sourceOffset, int32_t destOffset);

/*!
 * @brief Sets TCD fields according to the user's channel transfer configuration structure, @ref
 * edma_transfer_config_t.
 *
 * Application should be careful about the TCD pool buffer storage class,
 * - For the platform has cache, the software TCD should be put in non cache section
 * - The TCD pool buffer should have a consistent storage class.
 *
 * @param base eDMA peripheral base address.
 * @param tcd Pointer to the TCD structure.
 * @param transfer channel transfer configuration pointer.
 *
 * @note This function enables the auto stop request feature.
 */
void EDMA_ConfigChannelSoftwareTCDExt(EDMA_Type *base, edma_tcd_t *tcd, const edma_transfer_config_t *transfer);

/*!
 * @brief Sets all fields to default values for the TCD structure.
 *
 * This function sets all fields for this TCD structure to default value.
 *
 * @param base eDMA peripheral base address.
 * @param tcd Pointer to the TCD structure.
 * @note This function enables the auto stop request feature.
 */
void EDMA_TcdResetExt(EDMA_Type *base, edma_tcd_t *tcd);

/*!
 * @brief Configures the eDMA TCD transfer attribute.
 *
 * The TCD is a transfer control descriptor. The content of the TCD is the same as the hardware TCD registers.
 * The TCD is used in the scatter-gather mode.
 * This function configures the TCD transfer attribute, including source address, destination address,
 * transfer size, address offset, and so on. It also configures the scatter gather feature if the
 * user supplies the next TCD address.
 * Example:
 * @code
 *   edma_transfer_t config = {
 *   ...
 *   }
 *   edma_tcd_t tcd __aligned(32);
 *   edma_tcd_t nextTcd __aligned(32);
 *   EDMA_TcdSetTransferConfig(&tcd, &config, &nextTcd);
 * @endcode
 *
 * @param base eDMA peripheral base address.
 * @param tcd Pointer to the TCD structure.
 * @param config Pointer to eDMA transfer configuration structure.
 * @param nextTcd Pointer to the next TCD structure. It can be NULL if users
 *                do not want to enable scatter/gather feature.
 * @note TCD address should be 32 bytes aligned or it causes an eDMA error.
 * @note If the nextTcd is not NULL, the scatter gather feature is enabled
 *       and DREQ bit is cleared in the previous transfer configuration, which
 *       is set in the EDMA_TcdReset.
 */
void EDMA_TcdSetTransferConfigExt(EDMA_Type *base,
                                  edma_tcd_t *tcd,
                                  const edma_transfer_config_t *config,
                                  edma_tcd_t *nextTcd);

/*!
 * @brief Configures the eDMA TCD minor offset feature.
 *
 * A minor offset is a signed-extended value added to the source address or a destination
 * address after each minor loop.
 *
 * @param base eDMA peripheral base address.
 * @param tcd A point to the TCD structure.
 * @param config A pointer to the minor offset configuration structure.
 */
void EDMA_TcdSetMinorOffsetConfigExt(EDMA_Type *base, edma_tcd_t *tcd, const edma_minor_offset_config_t *config);

/*!
 * @brief Sets the channel link for the eDMA TCD.
 *
 * This function configures either a minor link or a major link. The minor link means the channel link is
 * triggered every time CITER decreases by 1. The major link means that the channel link  is triggered when the CITER is
 * exhausted.
 *
 * @note Users should ensure that DONE flag is cleared before calling this interface, or the configuration is invalid.
 * @param base eDMA peripheral base address.
 * @param tcd Point to the TCD structure.
 * @param type Channel link type, it can be one of:
 *   @arg kEDMA_LinkNone
 *   @arg kEDMA_MinorLink
 *   @arg kEDMA_MajorLink
 * @param linkedChannel The linked channel number.
 */
void EDMA_TcdSetChannelLinkExt(EDMA_Type *base, edma_tcd_t *tcd, edma_channel_link_type_t type, uint32_t linkedChannel);

#if defined FSL_FEATURE_EDMA_HAS_BANDWIDTH && FSL_FEATURE_EDMA_HAS_BANDWIDTH
/*!
 * @brief Sets the bandwidth for the eDMA TCD.
 *
 * Because the eDMA processes the minor loop, it continuously generates read/write sequences
 * until the minor count is exhausted. The bandwidth forces the eDMA to stall after the completion of
 * each read/write access to control the bus request bandwidth seen by the crossbar switch.
 * @param base eDMA peripheral base address.
 * @param tcd A pointer to the TCD structure.
 * @param bandWidth A bandwidth setting, which can be one of the following:
 *     @arg kEDMABandwidthStallNone
 *     @arg kEDMABandwidthStall4Cycle
 *     @arg kEDMABandwidthStall8Cycle
 */
static inline void EDMA_TcdSetBandWidthExt(EDMA_Type *base, edma_tcd_t *tcd, edma_bandwidth_t bandWidth)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    EDMA_TCD_CSR(tcd, EDMA_TCD_TYPE(base)) =
        (uint16_t)((EDMA_TCD_CSR(tcd, EDMA_TCD_TYPE(base)) & (~DMA_CSR_BWC_MASK)) | DMA_CSR_BWC(bandWidth));
}
#endif

/*!
 * @brief Sets the source modulo and the destination modulo for the eDMA TCD.
 *
 * This function defines a specific address range specified to be the value after (SADDR + SOFF)/(DADDR + DOFF)
 * calculation is performed or the original register value. It provides the ability to implement a circular data
 * queue easily.
 *
 * @param base eDMA peripheral base address.
 * @param tcd A pointer to the TCD structure.
 * @param srcModulo A source modulo value.
 * @param destModulo A destination modulo value.
 */
void EDMA_TcdSetModuloExt(EDMA_Type *base, edma_tcd_t *tcd, edma_modulo_t srcModulo, edma_modulo_t destModulo);

/*!
 * @brief Sets the auto stop request for the eDMA TCD.
 *
 * If enabling the auto stop request, the eDMA hardware automatically disables the hardware channel request.
 *
 * @param base eDMA peripheral base address.
 * @param tcd A pointer to the TCD structure.
 * @param enable The command to enable (true) or disable (false).
 */
static inline void EDMA_TcdEnableAutoStopRequestExt(EDMA_Type *base, edma_tcd_t *tcd, bool enable)
{
    assert(tcd != NULL);
    assert(((uint32_t)tcd & 0x1FU) == 0U);

    EDMA_TCD_CSR(tcd, EDMA_TCD_TYPE(base)) = (uint16_t)((EDMA_TCD_CSR(tcd, EDMA_TCD_TYPE(base)) & (~DMA_CSR_DREQ_MASK)) |
                                                       DMA_CSR_DREQ((true == enable ? 1U : 0U)));
}

/*!
 * @brief Enables the interrupt source for the eDMA TCD.
 *
 * @param base eDMA peripheral base address.
 * @param tcd Point to the TCD structure.
 * @param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_TcdEnableInterruptsExt(EDMA_Type *base, edma_tcd_t *tcd, uint32_t mask);

/*!
 * @brief Disables the interrupt source for the eDMA TCD.
 *
 * @param base eDMA peripheral base address.
 * @param tcd Point to the TCD structure.
 * @param mask The mask of interrupt source to be set. Users need to use
 *             the defined edma_interrupt_enable_t type.
 */
void EDMA_TcdDisableInterruptsExt(EDMA_Type *base, edma_tcd_t *tcd, uint32_t mask);

/*!
 * @brief Configures the eDMA TCD major offset feature.
 *
 * Adjustment value added to the source address at the completion of the major iteration count
 *
 * @param base eDMA peripheral base address.
 * @param tcd A point to the TCD structure.
 * @param sourceOffset source address offset wiil be applied to source address after major loop done.
 * @param destOffset destination address offset will be applied to source address after major loop done.
 */
void EDMA_TcdSetMajorOffsetConfigExt(EDMA_Type *base, edma_tcd_t *tcd, int32_t sourceOffset, int32_t destOffset);

/*! @} */
/*!
 * @name eDMA Channel Transfer Operation
 * @{
 */

/*!
 * @brief Enables the eDMA hardware channel request.
 *
 * This function enables the hardware channel request.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 */
static inline void EDMA_EnableChannelRequest(EDMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

#if defined FSL_EDMA_SOC_IP_EDMA && FSL_EDMA_SOC_IP_EDMA
    EDMA_BASE(base)->SERQ = DMA_SERQ_SERQ(channel);
#else
    EDMA_CHANNEL_BASE(base, channel)->CH_CSR |= DMA_CH_CSR_ERQ_MASK;
#endif
}

/*!
 * @brief Disables the eDMA hardware channel request.
 *
 * This function disables the hardware channel request.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 */
static inline void EDMA_DisableChannelRequest(EDMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

#if defined FSL_EDMA_SOC_IP_EDMA && FSL_EDMA_SOC_IP_EDMA
    EDMA_BASE(base)->CERQ = DMA_CERQ_CERQ(channel);
#else
    EDMA_CHANNEL_BASE(base, channel)->CH_CSR &= ~DMA_CH_CSR_ERQ_MASK;
#endif
}

/*!
 * @brief Starts the eDMA transfer by using the software trigger.
 *
 * This function starts a minor loop transfer.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 */
static inline void EDMA_TriggerChannelStart(EDMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_EDMA_INSTANCE_CHANNELn(base));

#if defined FSL_EDMA_SOC_IP_EDMA && FSL_EDMA_SOC_IP_EDMA
    EDMA_BASE(base)->SSRT = DMA_SSRT_SSRT(channel);
#else
    EDMA_TCD_CSR(EDMA_TCD_BASE(base, channel), EDMA_TCD_TYPE(base)) |= DMA_CSR_START_MASK;
#endif
}

/*! @} */
/*!
 * @name eDMA Channel Status Operation
 * @{
 */

/*!
 * @brief Gets the remaining major loop count from the eDMA current channel TCD.
 *
 * This function checks the TCD (Task Control Descriptor) status for a specified
 * eDMA channel and returns the number of major loop count that has not finished.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @return Major loop count which has not been transferred yet for the current TCD.
 * @note 1. This function can only be used to get unfinished major loop count of transfer without
 *          the next TCD, or it might be inaccuracy.
 *       2. The unfinished/remaining transfer bytes cannot be obtained directly from registers while
 *          the channel is running.
 *          Because to calculate the remaining bytes, the initial NBYTES configured in DMA_TCDn_NBYTES_MLNO
 *          register is needed while the eDMA IP does not support getting it while a channel is active.
 *          In another word, the NBYTES value reading is always the actual (decrementing) NBYTES value the dma_engine
 *          is working with while a channel is running.
 *          Consequently, to get the remaining transfer bytes, a software-saved initial value of NBYTES (for example
 *          copied before enabling the channel) is needed. The formula to calculate it is shown below:
 *          RemainingBytes = RemainingMajorLoopCount * NBYTES(initially configured)
 */
uint32_t EDMA_GetRemainingMajorLoopCount(EDMA_Type *base, uint32_t channel);

/*!
 * @brief Gets the eDMA channel error status flags.
 *
 * @param base eDMA peripheral base address.
 * @return The mask of error status flags. Users need to use the
 *         _edma_error_status_flags type to decode the return variables.
 */
static inline uint32_t EDMA_GetErrorStatusFlags(EDMA_Type *base)
{
#if defined FSL_EDMA_SOC_IP_EDMA && FSL_EDMA_SOC_IP_EDMA
    return EDMA_BASE(base)->ES;
#else
    return EDMA_MP_BASE(base)->MP_ES;
#endif
}

/*!
 * @brief Gets the eDMA channel status flags.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @return The mask of channel status flags. Users need to use the
 *         _edma_channel_status_flags type to decode the return variables.
 */
uint32_t EDMA_GetChannelStatusFlags(EDMA_Type *base, uint32_t channel);

/*!
 * @brief Clears the eDMA channel status flags.
 *
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 * @param mask The mask of channel status to be cleared. Users need to use
 *             the defined _edma_channel_status_flags type.
 */
void EDMA_ClearChannelStatusFlags(EDMA_Type *base, uint32_t channel, uint32_t mask);

/*! @} */
/*!
 * @name eDMA Transactional Operation
 */

/*!
 * @brief Creates the eDMA handle.
 *
 * This function is called if using the transactional API for eDMA. This function
 * initializes the internal state of the eDMA handle.
 *
 * @param handle eDMA handle pointer. The eDMA handle stores callback function and
 *               parameters.
 * @param base eDMA peripheral base address.
 * @param channel eDMA channel number.
 */
void EDMA_CreateHandle(edma_handle_t *handle, EDMA_Type *base, uint32_t channel);

/*!
 * @brief Installs the TCDs memory pool into the eDMA handle.
 *
 * This function is called after the EDMA_CreateHandle to use scatter/gather feature. This function shall only be used
 * while users need to use scatter gather mode. Scatter gather mode enables EDMA to load a new transfer control block
 * (tcd) in hardware, and automatically reconfigure that DMA channel for a new transfer.
 * Users need to prepare tcd memory and also configure tcds using interface EDMA_SubmitTransfer.
 *
 * @param handle eDMA handle pointer.
 * @param tcdPool A memory pool to store TCDs. It must be 32 bytes aligned.
 * @param tcdSize The number of TCD slots.
 */
void EDMA_InstallTCDMemory(edma_handle_t *handle, edma_tcd_t *tcdPool, uint32_t tcdSize);

/*!
 * @brief Installs a callback function for the eDMA transfer.
 *
 * This callback is called in the eDMA IRQ handler. Use the callback to do something after
 * the current major loop transfer completes. This function will be called every time one tcd finished transfer.
 *
 * @param handle eDMA handle pointer.
 * @param callback eDMA callback function pointer.
 * @param userData A parameter for the callback function.
 */
void EDMA_SetCallback(edma_handle_t *handle, edma_callback callback, void *userData);

/*!
 * @brief Prepares the eDMA transfer structure configurations.
 *
 * This function prepares the transfer configuration structure according to the user input.
 *
 * @param config The user configuration structure of type edma_transfer_t.
 * @param srcAddr eDMA transfer source address.
 * @param srcWidth eDMA transfer source address width(bytes).
 * @param srcOffset source address offset.
 * @param destAddr eDMA transfer destination address.
 * @param destWidth eDMA transfer destination address width(bytes).
 * @param destOffset destination address offset.
 * @param bytesEachRequest eDMA transfer bytes per channel request.
 * @param transferBytes eDMA transfer bytes to be transferred.
 * @note The data address and the data width must be consistent. For example, if the SRC
 *       is 4 bytes, the source address must be 4 bytes aligned, or it results in
 *       source address error (SAE).
 *       User can check if 128 bytes support is available for specific instance by
 *       FSL_FEATURE_EDMA_INSTANCE_SUPPORT_128_BYTES_TRANSFERn.
 */
void EDMA_PrepareTransferConfig(edma_transfer_config_t *config,
                                void *srcAddr,
                                uint32_t srcWidth,
                                int16_t srcOffset,
                                void *destAddr,
                                uint32_t destWidth,
                                int16_t destOffset,
                                uint32_t bytesEachRequest,
                                uint32_t transferBytes);

/*!
 * @brief Prepares the eDMA transfer structure.
 *
 * This function prepares the transfer configuration structure according to the user input.
 *
 * @param config The user configuration structure of type edma_transfer_t.
 * @param srcAddr eDMA transfer source address.
 * @param srcWidth eDMA transfer source address width(bytes).
 * @param destAddr eDMA transfer destination address.
 * @param destWidth eDMA transfer destination address width(bytes).
 * @param bytesEachRequest eDMA transfer bytes per channel request.
 * @param transferBytes eDMA transfer bytes to be transferred.
 * @param type eDMA transfer type.
 * @note The data address and the data width must be consistent. For example, if the SRC
 *       is 4 bytes, the source address must be 4 bytes aligned, or it results in
 *       source address error (SAE).
 */
void EDMA_PrepareTransfer(edma_transfer_config_t *config,
                          void *srcAddr,
                          uint32_t srcWidth,
                          void *destAddr,
                          uint32_t destWidth,
                          uint32_t bytesEachRequest,
                          uint32_t transferBytes,
                          edma_transfer_type_t type);

/*!
 * @brief Prepares the eDMA transfer content descriptor.
 *
 * This function prepares the transfer content descriptor structure according to the user input.
 *
 * @param handle eDMA handle pointer.
 * @param tcd Pointer to eDMA transfer content descriptor structure.
 * @param srcAddr eDMA transfer source address.
 * @param srcWidth eDMA transfer source address width(bytes).
 * @param srcOffset source address offset.
 * @param destAddr eDMA transfer destination address.
 * @param destWidth eDMA transfer destination address width(bytes).
 * @param destOffset destination address offset.
 * @param bytesEachRequest eDMA transfer bytes per channel request.
 * @param transferBytes eDMA transfer bytes to be transferred.
 * @param nextTcd eDMA transfer linked TCD address.
 *
 * @note The data address and the data width must be consistent. For example, if the SRC
 *       is 4 bytes, the source address must be 4 bytes aligned, or it results in
 *       source address error (SAE).
 */
void EDMA_PrepareTransferTCD(edma_handle_t *handle,
                             edma_tcd_t *tcd,
                             void *srcAddr,
                             uint32_t srcWidth,
                             int16_t srcOffset,
                             void *destAddr,
                             uint32_t destWidth,
                             int16_t destOffset,
                             uint32_t bytesEachRequest,
                             uint32_t transferBytes,
                             edma_tcd_t *nextTcd);

/*!
 * @brief Submits the eDMA transfer content descriptor.
 *
 * This function submits the eDMA transfer request according to the transfer content descriptor.
 * In scatter gather mode, call this function will add a configured tcd to the circular list of tcd pool.
 * The tcd pools is setup by call function EDMA_InstallTCDMemory before.
 *
 * Typical user case:
 * 1. submit single transfer
 * @code
 * edma_tcd_t tcd;
 * EDMA_PrepareTransferTCD(handle, tcd, ....)
 * EDMA_SubmitTransferTCD(handle, tcd)
 * EDMA_StartTransfer(handle)
 * @endcode
 *
 * 2. submit static link transfer,
 * @code
 * edma_tcd_t tcd[2];
 * EDMA_PrepareTransferTCD(handle, &tcd[0], ....)
 * EDMA_PrepareTransferTCD(handle, &tcd[1], ....)
 * EDMA_SubmitTransferTCD(handle, &tcd[0])
 * EDMA_StartTransfer(handle)
 * @endcode
 *
 * 3. submit dynamic link transfer
 * @code
 * edma_tcd_t tcdpool[2];
 * EDMA_InstallTCDMemory(&g_DMA_Handle, tcdpool, 2);
 * edma_tcd_t tcd;
 * EDMA_PrepareTransferTCD(handle, tcd, ....)
 * EDMA_SubmitTransferTCD(handle, tcd)
 * EDMA_PrepareTransferTCD(handle, tcd, ....)
 * EDMA_SubmitTransferTCD(handle, tcd)
 * EDMA_StartTransfer(handle)
 * @endcode
 *
 * 4. submit loop transfer
 * @code
 * edma_tcd_t tcd[2];
 * EDMA_PrepareTransferTCD(handle, &tcd[0], ...,&tcd[1])
 * EDMA_PrepareTransferTCD(handle, &tcd[1], ..., &tcd[0])
 * EDMA_SubmitTransferTCD(handle, &tcd[0])
 * EDMA_StartTransfer(handle)
 * @endcode
 *
 * @param handle eDMA handle pointer.
 * @param tcd Pointer to eDMA transfer content descriptor structure.
 *
 * @retval kStatus_EDMA_Success It means submit transfer request succeed.
 * @retval kStatus_EDMA_QueueFull It means TCD queue is full. Submit transfer request is not allowed.
 * @retval kStatus_EDMA_Busy It means the given channel is busy, need to submit request later.
 */
status_t EDMA_SubmitTransferTCD(edma_handle_t *handle, edma_tcd_t *tcd);

/*!
 * @brief Submits the eDMA transfer request.
 *
 * This function submits the eDMA transfer request according to the transfer configuration structure.
 * In scatter gather mode, call this function will add a configured tcd to the circular list of tcd pool.
 * The tcd pools is setup by call function EDMA_InstallTCDMemory before.
 *
 * @param handle eDMA handle pointer.
 * @param config Pointer to eDMA transfer configuration structure.
 * @retval kStatus_EDMA_Success It means submit transfer request succeed.
 * @retval kStatus_EDMA_QueueFull It means TCD queue is full. Submit transfer request is not allowed.
 * @retval kStatus_EDMA_Busy It means the given channel is busy, need to submit request later.
 */
status_t EDMA_SubmitTransfer(edma_handle_t *handle, const edma_transfer_config_t *config);

/*!
 * @brief Submits the eDMA scatter gather transfer configurations.
 *
 * The function is target for submit loop transfer request,
 * the ring transfer request means that the transfer request TAIL is link to HEAD, such as,
 * A->B->C->D->A, or A->A
 *
 * To use the ring transfer feature, the application should allocate several transfer object, such as
 * @code
 * edma_channel_transfer_config_t transfer[2];
 * EDMA_TransferSubmitLoopTransfer(psHandle, &transfer, 2U);
 * @endcode
 * Then eDMA driver will link transfer[0] and transfer[1] to each other
 *
 * @note Application should check the return value of this function to avoid transfer request
 * submit failed
 *
 * @param handle eDMA handle pointer
 * @param transfer pointer to user's eDMA channel configure structure, see edma_channel_transfer_config_t for detail
 * @param transferLoopCount the count of the transfer ring, if loop count is 1, that means that the one will link to
 * itself.
 *
 * @retval #kStatus_Success It means submit transfer request succeed
 * @retval #kStatus_EDMA_Busy channel is in busy status
 * @retval #kStatus_InvalidArgument Invalid Argument
 */
status_t EDMA_SubmitLoopTransfer(edma_handle_t *handle, edma_transfer_config_t *transfer, uint32_t transferLoopCount);

/*!
 * @brief eDMA starts transfer.
 *
 * This function enables the channel request. Users can call this function after submitting the transfer request
 * or before submitting the transfer request.
 *
 * @param handle eDMA handle pointer.
 */
void EDMA_StartTransfer(edma_handle_t *handle);

/*!
 * @brief eDMA stops transfer.
 *
 * This function disables the channel request to pause the transfer. Users can call EDMA_StartTransfer()
 * again to resume the transfer.
 *
 * @param handle eDMA handle pointer.
 */
void EDMA_StopTransfer(edma_handle_t *handle);

/*!
 * @brief eDMA aborts transfer.
 *
 * This function disables the channel request and clear transfer status bits.
 * Users can submit another transfer after calling this API.
 *
 * @param handle DMA handle pointer.
 */
void EDMA_AbortTransfer(edma_handle_t *handle);

/*!
 * @brief Get unused TCD slot number.
 *
 * This function gets current tcd index which is run. If the TCD pool pointer is NULL, it will return 0.
 *
 * @param handle DMA handle pointer.
 * @return The unused tcd slot number.
 */
static inline uint32_t EDMA_GetUnusedTCDNumber(edma_handle_t *handle)
{
    int8_t tmpTcdSize = handle->tcdSize;
    int8_t tmpTcdUsed = handle->tcdUsed;
    return ((uint32_t)tmpTcdSize - (uint32_t)tmpTcdUsed);
}

/*!
 * @brief Get the next tcd address.
 *
 * This function gets the next tcd address. If this is last TCD, return 0.
 *
 * @param handle DMA handle pointer.
 * @return The next TCD address.
 */
static inline uint32_t EDMA_GetNextTCDAddress(edma_handle_t *handle)
{
    return (uint32_t)(EDMA_TCD_DLAST_SGA(handle->tcdBase, EDMA_TCD_TYPE(handle->base)));
}

/*!
 * @brief eDMA IRQ handler for the current major loop transfer completion.
 *
 * This function clears the channel major interrupt flag and calls
 * the callback function if it is not NULL.
 *
 * Note:
 * For the case using TCD queue, when the major iteration count is exhausted, additional operations are performed.
 * These include the final address adjustments and reloading of the BITER field into the CITER.
 * Assertion of an optional interrupt request also occurs at this time, as does a possible fetch of a new TCD from
 * memory using the scatter/gather address pointer included in the descriptor (if scatter/gather is enabled).
 *
 * For instance, when the time interrupt of TCD[0] happens, the TCD[1] has already been loaded into the eDMA engine.
 * As sga and sga_index are calculated based on the DLAST_SGA bitfield lies in the TCD_CSR register, the sga_index
 * in this case should be 2 (DLAST_SGA of TCD[1] stores the address of TCD[2]). Thus, the "tcdUsed" updated should be
 * (tcdUsed - 2U) which indicates the number of TCDs can be loaded in the memory pool (because TCD[0] and TCD[1] have
 * been loaded into the eDMA engine at this point already.).
 *
 * For the last two continuous ISRs in a scatter/gather process, they  both load the last TCD (The last ISR does not
 * load a new TCD) from the memory pool to the eDMA engine when major loop completes.
 * Therefore, ensure that the header and tcdUsed updated are identical for them.
 * tcdUsed are both 0 in this case as no TCD to be loaded.
 *
 * See the "eDMA basic data flow" in the eDMA Functional description section of the Reference Manual for
 * further details.
 *
 * @param handle eDMA handle pointer.
 */
void EDMA_HandleIRQ(edma_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /*FSL_EDMA_H_*/
