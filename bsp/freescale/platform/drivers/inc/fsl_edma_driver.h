/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_EDMA_DRIVER_H__)
#define __FSL_EDMA_DRIVER_H__

#include <stdint.h>
#include "fsl_device_registers.h"
#include "fsl_edma_request.h"
#include "fsl_edma_hal.h"
#include "fsl_dmamux_hal.h"
#include "fsl_os_abstraction.h"
#if FSL_FEATURE_SOC_EDMA_COUNT

/*!
 * @addtogroup edma_driver
 * @{
 */

/*! @brief Array for the eDMA module register base address. */
extern DMA_Type * const g_edmaBase[];

/*! @brief Array for DMAMUX module register base address. */
extern DMAMUX_Type * const g_dmamuxBase[];

/*! @brief Two dimensional array for eDMA channel interrupt vector number. */
extern const IRQn_Type g_edmaIrqId[DMA_INSTANCE_COUNT][FSL_FEATURE_EDMA_MODULE_CHANNEL];

#if !defined FSL_FEATURE_EDMA_HAS_ERROR_IRQ
/*! @brief Array for eDMA module's error interrupt vector number. */
extern const IRQn_Type g_edmaErrIrqId[DMA_INSTANCE_COUNT];
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Macro for the memory size needed for the software TCD.
 *
 * Software TCD is aligned to 32 bytes. To make sure the software TCD can meet the
 * eDMA module requirement, allocate memory with extra 32 bytes.
 */
#define STCD_SIZE(number)           ((number + 1) * 32)
#define STCD_ADDR(address)          (edma_software_tcd_t *)(((uint32_t)address + 32) & ~0x1FU)

/*!
 * @brief The user configuration structure for the eDMA driver.
 *
 * Use an instance of this structure with the EDMA_DRV_Init() function. This allows the user to configure
 * settings of the EDMA peripheral with a single function call.
 * @internal gui name="Configuration" id="edmaCfg"
 */
typedef struct EDMAUserConfig {
    edma_channel_arbitration_t chnArbitration;  /*!< eDMA channel arbitration. @internal gui name="Channel arbitration" id="ChnArbitration" */
#if FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 0x1U
    edma_group_arbitration_t groupArbitration;  /*!< eDMA group arbitration. @internal gui name="Group arbitration" id="GroupArbitration" */
    edma_group_priority_t groupPriority;        /*!< eDMA group priority. It is used while eDMA
                                                     group arbitration is set to fixed priority. @internal gui name="Group priority" id="GroupPriority" */
#endif
    bool notHaltOnError;
    /*!<  Any error causes the HALT bit to set. Subsequently, all service requests are ignored until the HALT bit is cleared.
    @internal gui name="Set HALT on Error" id="HaltOnError" */
} edma_user_config_t;

/*!
 * @brief Channel status for eDMA channel.
 *
 * A structure describing the eDMA channel status. The user can get the status by callback parameter
 * or by calling EDMA_DRV_getStatus() function.
 */
typedef enum _edma_chn_status {
    kEDMAChnNormal = 0U,           /*!< eDMA channel is occupied. */
    kEDMAChnIdle,                  /*!< eDMA channel is idle. */
    kEDMAChnError                  /*!< An error occurs in the eDMA channel. */
} edma_chn_status_t;


/*!
 * @brief Definition for the eDMA channel callback function.
 *
 * Prototype for the callback function registered in the eDMA driver.
 */
typedef void (*edma_callback_t)(void *parameter, edma_chn_status_t status);

/*! @brief Macro to get the eDMA physical module indicator from the virtual channel indicator. */
#define VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(chn)     g_edmaBase[chn/FSL_FEATURE_EDMA_MODULE_CHANNEL]

/*! @brief Macro to get the eDMA physical channel indicator from the virtual channel indicator. */
#define VIRTUAL_CHN_TO_EDMA_CHN(chn)                (chn%FSL_FEATURE_EDMA_MODULE_CHANNEL)

/*! @brief Macro to get the DMAMUX physical module indicator from the virtual channel indicator. */
#define VIRTUAL_CHN_TO_DMAMUX_MODULE_REGBASE(chn)   g_dmamuxBase[chn/FSL_FEATURE_DMAMUX_MODULE_CHANNEL]

/*! @brief Macro to get the DMAMUX physical channel indicator from the virtual channel indicator. */
#define VIRTUAL_CHN_TO_DMAMUX_CHN(chn)          (chn%FSL_FEATURE_DMAMUX_MODULE_CHANNEL)

/*! @brief Data structure for the eDMA channel. */
typedef struct EDMAChnState {
    uint8_t channel;                /*!< Virtual channel indicator. */
    edma_callback_t callback;       /*!< Callback function pointer for the eDMA channel. It will
                                         be called at the eDMA channel complete and eDMA channel
                                         error. */
    void *parameter;                /*!< Parameter for the callback function pointer. */
    volatile edma_chn_status_t status;   /*!< eDMA channel status. */
} edma_chn_state_t;

/*! @brief enum type for channel allocation.  */
typedef enum _edma_chn_state_type {
    kEDMAInvalidChannel = 0xFFU, /*!< Macros indicate the failure of the channel request. */
    kEDMAAnyChannel = 0xFEU      /*!< Macros used when requesting channel dynamically. */
} edma_chn_state_type_t;

/*! @brief A type for the DMA transfer. */
typedef enum _edma_transfer_type {
    kEDMAPeripheralToMemory,        /*!< Transfer from peripheral to memory */
    kEDMAMemoryToPeripheral,        /*!< Transfer from memory to peripheral */
    kEDMAMemoryToMemory,            /*!< Transfer from memory to memory */
} edma_transfer_type_t;

/*! @brief Data structure for configuring a discrete memory transfer. */
typedef struct EDMAScatterGatherList {
    uint32_t address;           /*!< Address of buffer. */
    uint32_t length;            /*!< Length of buffer. */
} edma_scatter_gather_list_t;

/*!
 * @brief Runtime state structure for the eDMA driver.
 *
 * This structure holds data that is used by the eDMA peripheral driver to manage
 * multi eDMA channels.
 * The user passes the memory for this run-time state structure and the eDMA
 * driver populates the members.
 */
typedef struct EDMAState {
#if (USE_RTOS)
    mutex_t lock;       /*!< Lock for channel allocation and release. */
#endif
    edma_chn_state_t * volatile chn[FSL_FEATURE_EDMA_DMAMUX_CHANNELS];     /*!< Pointer array storing
                                                                             channel state.  */
} edma_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
  * @name eDMA Peripheral Driver
  * @{
  */

/*!
  * @name eDMA peripheral driver module level functions
  * @{
  */

/*!
 * @brief Initializes all eDMA modules in an SOC.
 *
 * This function initializes the run-time state structure to provide the eDMA channel allocation
 * release, protect, and track the state for channels. This function also opens the clock to the eDMA
 * modules, resets the eDMA modules, initializes the module to user-defined settings and default
 * settings.
 * This is an example to set up the edma_state_t and the edma_user_config_t parameters and to call
 * the EDMA_DRV_Init function by passing in these parameters.
   @code
   edma_state_t state;    <- The user simply allocates memory for this structure.
   edma_user_config_t userConfig;    <- The user fills out members for this structure.

   userConfig.chnArbitration = kEDMAChnArbitrationRoundrobin;
#if (FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 0x1U)
   //configuration for 2 lines below only valid for SoCs with more than on group.
   userConfig.groupArbitration = kEDMAGroupArbitrationFixedPriority;
   userConfig.groupPriority = kEDMAGroup0PriorityHighGroup1PriorityLow;
#endif
   userCOnfig.notHaltOnError = false;    <- The default setting is false, means eDMA halt on error.

   EDMA_DRV_Init(&state, &userConfig);

   @endcode
 *
 * @param edmaState The pointer to the eDMA peripheral driver state structure. The user passes
 * the memory for this run-time state structure and the eDMA peripheral driver populates the
 * members. This run-time state structure keeps track of the eDMA channels status. The memory must
 * be kept valid before calling the EDMA_DRV_DeInit.
 * @param userConfig User configuration structure for eDMA peripheral drivers. The user populates the
 * members of this structure and passes the pointer of this structure into the function.
 *
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */
edma_status_t EDMA_DRV_Init(edma_state_t *edmaState, const edma_user_config_t *userConfig);

/*!
 * @brief Shuts down all eDMA modules.
 *
 * This function resets the eDMA modules to reset state, gates the clock, and disables the interrupt
 * to the core.
 *
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */
edma_status_t EDMA_DRV_Deinit(void);

/* @} */

/*!
  * @name eDMA peripheral driver channel management functions
  * @{
  */

/*!
 * @brief Requests an eDMA channel dynamically or statically.
 *
 * This function allocates the eDMA channel according to the required channel allocation and
 * corresponding to the eDMA hardware request, initializes the channel state memory provided by user and fills
 * out the members. This functions also sets up the hardware request configuration according to the
 * user's requirements.
 *
 * For Kinetis devices, a hardware request can be mapped to eDMA channels and used for the channel trigger.
 * Some hardware requests can only be mapped to a limited channels. For example, the
 * Kinetis K70FN1M0VMJ15 device eDMA module has 2 eDMA channel groups. The first group consists of the channel
 * 0 - 15. The second group consists of channel 16 - 31. The hardware request UART0-Receive can be
 * only mapped to group 1. Therefore, the hardware request is one of the parameter that the user needs to provide
 * for the channel request. Channel needn't be triggered by the peripheral hardware request. The user can
 * provide the ALWAYSON type hardware request to trigger the channel continuously.
 *
 * This function provides two ways to allocate an eDMA channel: statically and dynamically.
 * In a static allocation, the user provides the required channel number and eDMA driver tries to allocate the
 * required channel to the user. If the channel is not occupied, the eDMA driver is
 * successfully assigned to the user. If the channel is already occupied, the user
 * gets the return value kEDMAInvalidChn.
 * This is an example to request a channel statically:
    @code
    uint32_t channelNumber = 14;  <- Try to allocate the channel 14
    edma_chn_state_t chn; <- The user simply allocates memory for this structure.

    if ( kEDMAInvalidChannel == EDMA_DRV_RequestChannel(channel, kDmaRequestMux0AlwaysOn54, chn))
    {
        printf("request channel %d failed!\n", channel);
    }

    @endcode
 * In a dynamic allocation, any of the free eDMA channels are available for use. eDMA driver
 * assigns the first free channel to the user.
 * This is an example for user to request a channel dynamically :
    @code
    uint32_t channel;    <- Store the allocated channel number.
    edma_chn_state_t chn;    <- The user simply allocates memory for this structure.

    channel = EDMA_DRV_RequestChannel(kEDMAAnyChannel, kDmaRequestMux0AlwaysOn54, chn);

    if (channel == kEDMAInvalidChannel)
    {
        printf("request channel %d failed!\n", channel);
    }
    else
    {
        printf("Channel %d is successfully allocated! /n", channel);
    }

    @endcode
 *
 * @param channel Requested channel number. If the channel is assigned with the kEDMAAnyChannel, the eDMA driver
 * allocates the channel dynamically. If the channel is assigned with a valid channel number, the eDMA driver
 * allocates that channel.
 * @param source eDMA hardware request number.
 * @param chn The pointer to the eDMA channel state structure. The user passes the memory for this
 * run-time state structure. The eDMA peripheral driver populates the members. This run-time
 * state structure keeps tracks of the eDMA channel status. The memory must be kept valid before
 * calling the EDMA_DRV_ReleaseChannel().
 *
 * @return Successfully allocated channel number or the kEDMAInvalidChannel indicating that the request is
 * failed.
 */
uint8_t EDMA_DRV_RequestChannel(
                uint8_t channel, dma_request_source_t source, edma_chn_state_t *chn);

/*!
 * @brief Releases an eDMA channel.
 *
 * This function stops the eDMA channel and disables the interrupt of this channel. The channel state
 * structure can be released after this function is called.
 *
 * @param chn The pointer to the channel state structure.
 *
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */
edma_status_t EDMA_DRV_ReleaseChannel(edma_chn_state_t *chn);

/* @} */

/*!
  * @name eDMA peripheral driver transfer setup functions
  * @{
  */
/*!
 * @brief Sets the descriptor basic transfer for the descriptor.
 *
 * This function sets up the basic transfer for the descriptor. The minor loop setting is not
 * used  because the minor loop configuration impacts the global eDMA setting.
 * The source minor loop offset is relevant to the destination minor loop offset. For these reasons, the minor
 * loop offset configuration is treated as an advanced configuration. The user can call the
 * EDMA_HAL_STCDSetMinorLoopOffset() function to configure the minor loop offset feature.
 *
 * @param channel Virtual channel number.
 * @param chn The pointer to the channel state structure.
 * @param stcd The pointer to the descriptor.
 * @param config Configuration for the basic transfer.
 * @param enableInt Enables (true) or Disables (false) interrupt on TCD complete.
 * @param disableDmaRequest Disables (true) or Enable (false) DMA request on TCD complete.
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */

static inline edma_status_t EDMA_DRV_PrepareDescriptorTransfer(
                                edma_chn_state_t *chn, edma_software_tcd_t *stcd,
                                edma_transfer_config_t *config,
                                bool enableInt, bool disableDmaRequest)

{
    EDMA_HAL_STCDSetBasicTransfer(
            VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(chn->channel), stcd, config, enableInt, disableDmaRequest);

    return kStatus_EDMA_Success;

}

/*!
 * @brief Configures the memory address for the next transfer TCD for the software TCD.
 *
 *
 * This function enables the scatter/gather feature for the software TCD and configures the next
 * TCD address.This address points to the beginning of a 0-modulo-32 byte region containing
 * the next transfer TCD to be loaded into this channel. The channel reload is performed as the
 * major iteration count completes. The scatter/gather address must be 0-modulo-32-byte. Otherwise,
 * a configuration error is reported.
 *
 * @param stcd The pointer to the software TCD, which needs to link to the software TCD. The
 * address needs to be aligned to 32 bytes.
 * @param nextStcd The pointer to the software TCD, which is to be linked to the software TCD. The
 * address needs to be aligned to 32 bytes.
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */
static inline edma_status_t EDMA_DRV_PrepareDescriptorScatterGather(
                                edma_software_tcd_t *stcd,
                                edma_software_tcd_t *nextStcd)
{
    EDMA_HAL_STCDSetScatterGatherLink(stcd, nextStcd);
    return kStatus_EDMA_Success;
}

/*!
 * @brief Configures the major channel link the software TCD.
 *
 * If the major link is enabled, after the major loop counter is exhausted, the eDMA engine initiates a
 * channel service request at the channel defined by these six bits by setting that channel start
 * bits.
 *
 * @param stcd The pointer to the software TCD. The address need to be aligned to 32 bytes.
 * @param linkChn Channel number for major link
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */
static inline edma_status_t EDMA_DRV_PrepareDescriptorChannelLink(
                                edma_software_tcd_t *stcd, uint32_t linkChn)
{
    EDMA_HAL_STCDSetChannelMajorLink(stcd, linkChn, true);
    return kStatus_EDMA_Success;
}

/*!
 * @brief Configures the minor channel link the software TCD.
 *
 * If the minor link is enabled, after the minor loop counter is exhausted, the eDMA engine initiates a
 * channel service request at the channel defined by these six bits by setting that channel start
 * bits.
 *
 * @param stcd The pointer to the software TCD. The address need to be aligned to 32 bytes.
 * @param linkChn Channel number for minor link
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */
static inline edma_status_t EDMA_DRV_PrepareDescriptorMinorLink(
                                edma_software_tcd_t *stcd, uint32_t linkChn)
{
    EDMA_HAL_STCDSetChannelMinorLink(stcd, linkChn, true);
    return kStatus_EDMA_Success;
}

/*!
 * @brief Triggers the eDMA channel.
 *
 * @param chn The pointer to the channel state structure.
 * @return kStatus_EDMA_Success.
 */
static inline edma_status_t EDMA_DRV_TriggerChannelStart(edma_chn_state_t *chn)
{
    EDMA_HAL_TriggerChannelStart(VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(chn->channel),
                                            (edma_channel_indicator_t)chn->channel);
    return kStatus_EDMA_Success;
}

/*!
 * @brief Copies the software TCD configuration to the hardware TCD.
 *
 * @param chn The pointer to the channel state structure.
 * @param stcd memory pointing to the software TCD.
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */
edma_status_t EDMA_DRV_PushDescriptorToReg(edma_chn_state_t *chn, edma_software_tcd_t *stcd);

/*!
 * @brief Configures the DMA transfer in a scatter-gather mode.
 *
 * This function configures the descriptors in a loop chain. The user passes a block of memory into this
 * function and the memory is divided into the "period" sub blocks. The DMA driver  configures the "period"
 * descriptors. Each descriptor stands for a sub block. The DMA driver  transfers data from the first
 * descriptor to the last descriptor. Then, the DMA driver  wraps to the first descriptor to continue
 * the loop. The interrupt handler is called every time a descriptor is completed.
 * The user can get a transfer status of a descriptor by calling the edma_get_descriptor_status() function in the interrupt handler or any
 * other task context. At the same
 * time, calling the edma_update_descriptor() function notifies the DMA driver that the content belonging to
 * a descriptor is already updated and the DMA needs to count it as and underflow next time it
 * loops to this descriptor.
 * This is an example that describes how to use this interface in audio playback case:
 * 1. Use a ping-pong buffer to transfer the data, the size of the each buffer is 1024 bytes.
 * 2. Each DMA request needs to transfer 8 bytes.
 * 3. The audio data is 16 bit.
   @code
   edma_chn_state_t chn; <--- Simply allocates the structure.
   edma_software_tcd_t stcd[2]; <-- Need 32 bytes aligned, two buffer block, needs 2 TCD.
   uint32_t srcAddr = buffer; <----Start address of the buffer.
   uint32_t destAddr = SAI_TDR; <-----Destination address, usually SAI TDR register.

   EDMA_DRV_ConfigLoopTransfer(&chn, stcd, kEDMAMemoryToPeripheral, srcAddr, destAddr,
   kEDMATransferSize_2Bytes, 8, 2048, 2) ;

   @endcode
 * @param chn The pointer to the channel state structure.
 * @param stcd Memory pointing to software TCDs. The user must prepare this memory block. The required
 * memory size is equal to a "period" * size of(edma_software_tcd_t). At the same time, the "stcd"
 * must align with 32 bytes. If not, an error occurs in the eDMA driver.
 * @param type Transfer type.
 * @param srcAddr A source register address or a source memory address.
 * @param destAddr A destination register address or a destination memory address.
 * @param size Bytes to be transferred on every DMA write/read. Source/Dest share the same write/read
 * size.
 * @param bytesOnEachRequest Bytes to be transferred in each DMA request.
 * @param totalLength Total bytes to be transferred in a loop cycle. In audio case, it means the total buffer size.
 * @param number The number of the TCDs, usually in audio case, it means the buffer block number.
 *
 * @return An error code of kStatus_EDMA_Success
 */
edma_status_t EDMA_DRV_ConfigLoopTransfer(
                            edma_chn_state_t *chn, edma_software_tcd_t *stcd,
                            edma_transfer_type_t type,
                            uint32_t srcAddr, uint32_t destAddr, uint32_t size,
                            uint32_t bytesOnEachRequest, uint32_t totalLength, uint8_t number);

/*!
 * @brief Configures the DMA transfer in a scatter-gather mode.
 *
 * This function configures the descriptors into a single-ended chain. The user passes blocks of memory into
 * this function. The interrupt is triggered only when the last memory block is completed. The memory block
 * information is passed with the edma_scatter_gather_list_t data structure, which can tell
 * the memory address and length.
 * The DMA driver configures the descriptor for each memory block, transfers the descriptor from the
 * first one to the last one, and stops.
 *
 * @param chn The pointer to the channel state structure.
 * @param stcd Memory pointing to software TCDs. The user must prepare this memory block. The required
 * memory size is equal to the "number" * size of(edma_software_tcd_t). At the same time, the "stcd"
 * must align with 32 bytes. If not, an error occurs in the eDMA driver.
 * @param type Transfer type.
 * @param size Bytes to be transferred on each DMA write/read. Source/Dest share the same write/read
 * size.
 * @param bytesOnEachRequest Bytes to be transferred in each DMA request.
 * @param srcList Data structure storing the address and length to be transferred for source
 * memory blocks. If the source memory is peripheral, the length is not used.
 * @param destList Data structure storing the address and length to be transferred for destination
 * memory blocks. If in the memory-to-memory transfer mode, the user must ensure that the length of
 * the destination scatter gather list is equal to the source scatter gather list. If the destination memory is a
 * peripheral register, the length is not used.
 * @param number The number of TCD memory blocks contained in the scatter gather list.
 *
 * @return An error code of kStatus_EDMA_Success
 */
edma_status_t EDMA_DRV_ConfigScatterGatherTransfer(
                        edma_chn_state_t *chn, edma_software_tcd_t *stcd,
                        edma_transfer_type_t type,
                        uint32_t size, uint32_t bytesOnEachRequest,
                        edma_scatter_gather_list_t *srcList, edma_scatter_gather_list_t *destList,
                        uint8_t number);

/* @} */

/*!
  * @name eDMA Peripheral driver channel operation functions
  * @{
  */
/*!
 * @brief Starts an eDMA channel.
 *
 * This function enables the eDMA channel DMA request.
 *
 * @param chn The pointer to the channel state structure.
 *
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */
edma_status_t EDMA_DRV_StartChannel(edma_chn_state_t *chn);

/*!
 * @brief Stops the eDMA channel.
 *
 * This function disables the eDMA channel DMA request.
 *
 * @param chn The pointer to the channel state structure.
 *
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */
edma_status_t EDMA_DRV_StopChannel(edma_chn_state_t *chn);

/* @} */

/*!
  * @name eDMA Peripheral callback and interrupt functions
  * @{
  */

/*!
 * @brief Registers the callback function and the parameter for eDMA channel.
 *
 * This function registers the callback function and the parameter into the eDMA channel state structure.
 * The callback function is called when the channel is complete or a channel error occurs. The eDMA
 * driver passes the channel status to this callback function to indicate whether it is caused by the
 * channel complete event or the channel error event.
 *
 * To un-register the callback function, set the callback function to "NULL" and call this
 * function.
 *
 * @param chn The pointer to the channel state structure.
 * @param callback The pointer to the callback function.
 * @param parameter The pointer to the callback function's parameter.
 *
 * @return An eDMA error codes or kStatus_EDMA_Success.
 */
edma_status_t EDMA_DRV_InstallCallback(
        edma_chn_state_t *chn, edma_callback_t callback, void *parameter);

/*!
 * @brief IRQ Handler for eDMA channel interrupt.
 *
 * This function is provided as the default flow for eDMA channel interrupt. This function clears the
 * status and calls the callback functions.
 * The user can add this function into the hardware interrupt entry and implement a
 * custom interrupt action function.
 *
 * @param channel Virtual channel number.
 */
void EDMA_DRV_IRQHandler(uint8_t channel);

/*!
 * @brief ERROR IRQ Handler for eDMA channel interrupt.
 *
 * This function is provided as the default action for eDMA module error interrupt. This function
 * clears status, stops the error on a eDMA channel, and calls the eDMA channel callback function if the
 * error eDMA channel is already requested.
 * The user can add this function into the eDMA error interrupt entry and implement a custom
 * interrupt action function.
 *
 * @param instance eDMA module indicator.
 */
void EDMA_DRV_ErrorIRQHandler(uint8_t instance);

/* @} */

/*!
  * @name eDMA Peripheral driver miscellaneous functions
  * @{
  */
/*!
 * @brief Gets the eDMA channel status.
 *
 * @param chn The pointer to the channel state structure.
 *
 * @return Channel status.
 */
static inline edma_chn_status_t EDMA_DRV_GetChannelStatus(edma_chn_state_t *chn)
{
    return chn->status;
}

/*!
 * @brief Gets the unfinished bytes for the eDMA channel current TCD.
 *
 * This function checks the TCD (Task Control Descriptor) status for a specified eDMA channel and returns
 * the bytes that have not finished.
 * This function can only be used for one TCD scenario.
 *
 * @param chn The pointer to the channel state structure.
 *
 * @return Bytes already transferred for the current TCD.
 */
static inline uint32_t EDMA_DRV_GetUnfinishedBytes(edma_chn_state_t *chn)
{
    uint32_t channel = chn->channel;

    return EDMA_HAL_HTCDGetUnfinishedBytes(
                    VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel),
                    VIRTUAL_CHN_TO_EDMA_CHN(channel));
}

/*!
 * @brief Gets the bytes already transferred for the eDMA channel current TCD.
 *
 * This function checks the TCD (Task Control Descriptor) status for a specified eDMA channel and returns
 * the bytes that remain to the user.
 * This function can only be used for one TCD scenario.
 *
 * @param chn The pointer to the channel state structure.
 *
 * @return Bytes already transferred for the current TCD.
 */
static inline uint32_t EDMA_DRV_GetFinishedBytes(edma_chn_state_t *chn)
{
    uint32_t channel = chn->channel;

    return EDMA_HAL_HTCDGetFinishedBytes(
                    VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel),
                    VIRTUAL_CHN_TO_EDMA_CHN(channel));
}

/* @} */


/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif /* __FSL_EDMA_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

