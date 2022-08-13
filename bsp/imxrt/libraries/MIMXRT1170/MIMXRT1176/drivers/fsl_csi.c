/*
 * Copyright 2017-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_csi.h"
#if CSI_DRIVER_FRAG_MODE
#include "fsl_cache.h"
#endif

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#include "fsl_memory.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Macro remap. */
#if (!defined(CSI_CR3_TWO_8BIT_SENSOR_MASK) && defined(CSI_CR3_SENSOR_16BITS_MASK))
#define CSI_CR3_TWO_8BIT_SENSOR_MASK CSI_CR3_SENSOR_16BITS_MASK
#endif

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.csi"
#endif

/* Two frame buffer loaded to CSI register at most. */
#define CSI_MAX_ACTIVE_FRAME_NUM 2U

/* CSI driver only support RGB565 and YUV422 in fragment mode, 2 bytes per pixel. */
#define CSI_FRAG_INPUT_BYTES_PER_PIXEL 2U

#if defined(FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET) && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#define CSI_ADDR_CPU_2_IP(addr) (MEMORY_ConvertMemoryMapAddress((uint32_t)(addr), kMEMORY_Local2DMA))
#define CSI_ADDR_IP_2_CPU(addr) (MEMORY_ConvertMemoryMapAddress((uint32_t)(addr), kMEMORY_DMA2Local))
#else
#define CSI_ADDR_CPU_2_IP(addr) (addr)
#define CSI_ADDR_IP_2_CPU(addr) (addr)
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */

/*!
 * @brief Used for conversion between `void*` and `uint32_t`.
 */
typedef union pvoid_to_u32
{
    void *pvoid;
    uint32_t u32;
} pvoid_to_u32_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the instance from the base address
 *
 * @param base CSI peripheral base address
 *
 * @return The CSI module instance
 */
static uint32_t CSI_GetInstance(CSI_Type *base);

#if !CSI_DRIVER_FRAG_MODE
/*!
 * @brief Get the delta value of two index in queue.
 *
 * @param startIdx Start index.
 * @param endIdx End index.
 *
 * @return The delta between startIdx and endIdx in queue.
 */
static uint8_t CSI_TransferGetQueueDelta(uint8_t startIdx, uint8_t endIdx);

/*!
 * @brief Increase a index value in queue.
 *
 * This function increases the index value in the queue, if the index is out of
 * the queue range, it is reset to 0.
 *
 * @param idx The index value to increase.
 *
 * @return The index value after increase.
 */
static uint8_t CSI_TransferIncreaseQueueIdx(uint8_t idx);

/*!
 * @brief Get the empty frame buffer count in queue.
 *
 * @param base CSI peripheral base address
 * @param handle Pointer to CSI driver handle.
 *
 * @return Number of the empty frame buffer count in queue.
 */
static uint32_t CSI_TransferGetEmptyBufferCount(csi_handle_t *handle);

/*!
 * @brief Get the empty frame buffer.
 *
 * This function should only be called when frame buffer count larger than 0.
 *
 * @param handle Pointer to CSI driver handle.
 *
 * @return Empty buffer
 */
static uint32_t CSI_TransferGetEmptyBuffer(csi_handle_t *handle);

/*!
 * @brief Put the empty frame buffer.
 *
 * @param handle Pointer to CSI driver handle.
 * @param buffer The empty buffer to put.
 */
static void CSI_TransferPutEmptyBuffer(csi_handle_t *handle, uint32_t buffer);

/*!
 * @brief Get the RX frame buffer address.
 *
 * @param base CSI peripheral base address.
 * @param index Buffer index.
 * @return Frame buffer address.
 */
static uint32_t CSI_GetRxBufferAddr(CSI_Type *base, uint8_t index);

/* Typedef for interrupt handler. */
typedef void (*csi_isr_t)(CSI_Type *base, csi_handle_t *handle);

#else

/* Typedef for interrupt handler to work in fragment mode. */
typedef void (*csi_isr_t)(CSI_Type *base, csi_frag_handle_t *handle);
#endif /* CSI_DRIVER_FRAG_MODE */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to CSI bases for each instance. */
static CSI_Type *const s_csiBases[] = CSI_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to CSI clocks for each CSI submodule. */
static const clock_ip_name_t s_csiClocks[] = CSI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/* Array for the CSI driver handle. */
#if !CSI_DRIVER_FRAG_MODE
static csi_handle_t *s_csiHandle[ARRAY_SIZE(s_csiBases)];
#else
static csi_frag_handle_t *s_csiHandle[ARRAY_SIZE(s_csiBases)];
#endif

/* Array of CSI IRQ number. */
static const IRQn_Type s_csiIRQ[] = CSI_IRQS;

/* CSI ISR for transactional APIs. */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
static csi_isr_t s_csiIsr = (csi_isr_t)DefaultISR;
#else
static csi_isr_t s_csiIsr;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t CSI_GetInstance(CSI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_csiBases); instance++)
    {
        if (s_csiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_csiBases));

    return instance;
}

#if !CSI_DRIVER_FRAG_MODE
static uint8_t CSI_TransferGetQueueDelta(uint8_t startIdx, uint8_t endIdx)
{
    uint8_t ret;

    if (endIdx >= startIdx)
    {
        ret = endIdx - startIdx;
    }
    else
    {
        ret = (uint8_t)(endIdx + CSI_DRIVER_ACTUAL_QUEUE_SIZE - startIdx);
    }

    return ret;
}

static uint8_t CSI_TransferIncreaseQueueIdx(uint8_t idx)
{
    uint8_t ret;

    /*
     * Here not use the method:
     * ret = (idx+1) % CSI_DRIVER_ACTUAL_QUEUE_SIZE;
     *
     * Because the mod function might be slow.
     */

    ret = idx + 1U;

    if (ret >= CSI_DRIVER_ACTUAL_QUEUE_SIZE)
    {
        ret = 0U;
    }

    return ret;
}

static uint32_t CSI_TransferGetEmptyBufferCount(csi_handle_t *handle)
{
    return handle->emptyBufferCnt;
}

static uint32_t CSI_TransferGetEmptyBuffer(csi_handle_t *handle)
{
    pvoid_to_u32_t buf;

    buf.pvoid = handle->emptyBuffer;
    handle->emptyBufferCnt--;
    handle->emptyBuffer = *(void **)(buf.pvoid);

    return buf.u32;
}

static void CSI_TransferPutEmptyBuffer(csi_handle_t *handle, uint32_t buffer)
{
    pvoid_to_u32_t buf;
    buf.u32 = buffer;

    *(void **)(buf.pvoid) = handle->emptyBuffer;
    handle->emptyBuffer   = buf.pvoid;
    handle->emptyBufferCnt++;
}

static uint32_t CSI_GetRxBufferAddr(CSI_Type *base, uint8_t index)
{
    uint32_t addr;

    if (index != 0U)
    {
        addr = CSI_REG_DMASA_FB2(base);
    }
    else
    {
        addr = CSI_REG_DMASA_FB1(base);
    }

    return CSI_ADDR_IP_2_CPU(addr);
}

#endif /* CSI_DRIVER_FRAG_MODE */

/*!
 * brief Initialize the CSI.
 *
 * This function enables the CSI peripheral clock, and resets the CSI registers.
 *
 * param base CSI peripheral base address.
 * param config Pointer to the configuration structure.
 *
 * retval kStatus_Success Initialize successfully.
 * retval kStatus_InvalidArgument Initialize failed because of invalid argument.
 */
status_t CSI_Init(CSI_Type *base, const csi_config_t *config)
{
    assert(NULL != config);
    uint32_t reg;
    uint32_t imgWidth_Bytes;
    uint8_t busCyclePerPixel;

    imgWidth_Bytes = (uint32_t)config->width * (uint32_t)config->bytesPerPixel;

    /* The image width and frame buffer pitch should be multiple of 8-bytes. */
    if ((0U != (imgWidth_Bytes & 0x07U)) || (0U != ((uint32_t)config->linePitch_Bytes & 0x07U)))
    {
        return kStatus_InvalidArgument;
    }

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = CSI_GetInstance(base);
    CLOCK_EnableClock(s_csiClocks[instance]);
#endif

    CSI_Reset(base);

    /* Configure CSICR1. CSICR1 has been reset to the default value, so could write it directly. */
    reg = ((uint32_t)config->workMode) | config->polarityFlags | CSI_CR1_FCC_MASK;

    if (config->useExtVsync)
    {
        reg |= CSI_CR1_EXT_VSYNC_MASK;
    }

    CSI_REG_CR1(base) = reg;

    /*
     * Generally, CSIIMAG_PARA[IMAGE_WIDTH] indicates how many data bus cycles per line.
     * One special case is when receiving 24-bit pixels through 8-bit data bus.
     * In this case, the CSIIMAG_PARA[IMAGE_WIDTH] should be set to the pixel number per line.
     */
    if ((kCSI_DataBus8Bit == config->dataBus) && (2U == config->bytesPerPixel))
    {
        busCyclePerPixel = 2U;
    }
    else
    {
        busCyclePerPixel = 1U;
    }

    if (4U == config->bytesPerPixel)
    {
        CSI_REG_CR18(base) |= CSI_CR18_PARALLEL24_EN_MASK;
    }

    if (kCSI_DataBus16Bit == config->dataBus)
    {
        CSI_REG_CR3(base) |= CSI_CR3_TWO_8BIT_SENSOR_MASK;
    }

    /* Image parameter. */
    CSI_REG_IMAG_PARA(base) =
        (((uint32_t)config->width * (uint32_t)busCyclePerPixel) << CSI_IMAG_PARA_IMAGE_WIDTH_SHIFT) |
        ((uint32_t)(config->height) << CSI_IMAG_PARA_IMAGE_HEIGHT_SHIFT);

    /* The CSI frame buffer bus is 8-byte width. */
    CSI_REG_FBUF_PARA(base) = (uint32_t)((config->linePitch_Bytes - imgWidth_Bytes) / 8U)
                              << CSI_FBUF_PARA_FBUF_STRIDE_SHIFT;

    /* Enable auto ECC. */
    CSI_REG_CR3(base) |= CSI_CR3_ECC_AUTO_EN_MASK;

    /*
     * For better performance.
     * The DMA burst size could be set to 16 * 8 byte, 8 * 8 byte, or 4 * 8 byte,
     * choose the best burst size based on bytes per line.
     */
    if (0U == (imgWidth_Bytes % (8U * 16U)))
    {
        CSI_REG_CR2(base) = CSI_CR2_DMA_BURST_TYPE_RFF(3U);
        CSI_REG_CR3(base) = (CSI_REG_CR3(base) & ~CSI_CR3_RxFF_LEVEL_MASK) | ((2U << CSI_CR3_RxFF_LEVEL_SHIFT));
    }
    else if (0U == (imgWidth_Bytes % (8U * 8U)))
    {
        CSI_REG_CR2(base) = CSI_CR2_DMA_BURST_TYPE_RFF(2U);
        CSI_REG_CR3(base) = (CSI_REG_CR3(base) & ~CSI_CR3_RxFF_LEVEL_MASK) | ((1U << CSI_CR3_RxFF_LEVEL_SHIFT));
    }
    else
    {
        CSI_REG_CR2(base) = CSI_CR2_DMA_BURST_TYPE_RFF(1U);
        CSI_REG_CR3(base) = (CSI_REG_CR3(base) & ~CSI_CR3_RxFF_LEVEL_MASK) | ((0U << CSI_CR3_RxFF_LEVEL_SHIFT));
    }

    CSI_ReflashFifoDma(base, kCSI_RxFifo);

    return kStatus_Success;
}

/*!
 * brief De-initialize the CSI.
 *
 * This function disables the CSI peripheral clock.
 *
 * param base CSI peripheral base address.
 */
void CSI_Deinit(CSI_Type *base)
{
    /* Disable transfer first. */
    CSI_Stop(base);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = CSI_GetInstance(base);
    CLOCK_DisableClock(s_csiClocks[instance]);
#endif
}

/*!
 * brief Reset the CSI.
 *
 * This function resets the CSI peripheral registers to default status.
 *
 * param base CSI peripheral base address.
 */
void CSI_Reset(CSI_Type *base)
{
    uint32_t csisr;

    /* Disable transfer first. */
    CSI_Stop(base);

    /* Disable DMA request. */
    CSI_REG_CR3(base) = 0U;

    /* Reset the fame count. */
    CSI_REG_CR3(base) |= CSI_CR3_FRMCNT_RST_MASK;
    while (0U != (CSI_REG_CR3(base) & CSI_CR3_FRMCNT_RST_MASK))
    {
    }

    /* Clear the RX FIFO. */
    CSI_ClearFifo(base, kCSI_AllFifo);

    /* Reflash DMA. */
    CSI_ReflashFifoDma(base, kCSI_AllFifo);

    /* Clear the status. */
    csisr            = CSI_REG_SR(base);
    CSI_REG_SR(base) = csisr;

    /* Set the control registers to default value. */
    CSI_REG_CR1(base) = CSI_CR1_HSYNC_POL_MASK | CSI_CR1_EXT_VSYNC_MASK;
    CSI_REG_CR2(base) = 0U;
    CSI_REG_CR3(base) = 0U;
#if defined(CSI_CR18_CSI_LCDIF_BUFFER_LINES)
    CSI_REG_CR18(base) = CSI_CR18_AHB_HPROT(0x0DU) | CSI_CR18_CSI_LCDIF_BUFFER_LINES(0x02U);
#else
    CSI_REG_CR18(base) = CSI_CR18_AHB_HPROT(0x0DU);
#endif
    CSI_REG_FBUF_PARA(base) = 0U;
    CSI_REG_IMAG_PARA(base) = 0U;
}

/*!
 * brief Get the default configuration for to initialize the CSI.
 *
 * The default configuration value is:
 *
 * code
    config->width = 320U;
    config->height = 240U;
    config->polarityFlags = kCSI_HsyncActiveHigh | kCSI_DataLatchOnRisingEdge;
    config->bytesPerPixel = 2U;
    config->linePitch_Bytes = 320U * 2U;
    config->workMode = kCSI_GatedClockMode;
    config->dataBus = kCSI_DataBus8Bit;
    config->useExtVsync = true;
   endcode
 *
 * param config Pointer to the CSI configuration.
 */
void CSI_GetDefaultConfig(csi_config_t *config)
{
    assert(NULL != config);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->width           = 320U;
    config->height          = 240U;
    config->polarityFlags   = (uint32_t)kCSI_HsyncActiveHigh | (uint32_t)kCSI_DataLatchOnRisingEdge;
    config->bytesPerPixel   = 2U;
    config->linePitch_Bytes = 320U * 2U;
    config->workMode        = kCSI_GatedClockMode;
    config->dataBus         = kCSI_DataBus8Bit;
    config->useExtVsync     = true;
}

/*!
 * brief Set the RX frame buffer address.
 *
 * param base CSI peripheral base address.
 * param index Buffer index.
 * param addr Frame buffer address to set.
 */
void CSI_SetRxBufferAddr(CSI_Type *base, uint8_t index, uint32_t addr)
{
    addr = CSI_ADDR_CPU_2_IP(addr);

    if (0U != index)
    {
        CSI_REG_DMASA_FB2(base) = addr;
    }
    else
    {
        CSI_REG_DMASA_FB1(base) = addr;
    }
}

/*!
 * brief Clear the CSI FIFO.
 *
 * This function clears the CSI FIFO.
 *
 * param base CSI peripheral base address.
 * param fifo The FIFO to clear.
 */
void CSI_ClearFifo(CSI_Type *base, csi_fifo_t fifo)
{
    uint32_t cr1;
    uint32_t mask = 0U;

    /* The FIFO could only be cleared when CSICR1[FCC] = 0, so first clear the FCC. */
    cr1               = CSI_REG_CR1(base);
    CSI_REG_CR1(base) = (cr1 & ~CSI_CR1_FCC_MASK);

    if (0U != ((uint32_t)fifo & (uint32_t)kCSI_RxFifo))
    {
        mask |= CSI_CR1_CLR_RXFIFO_MASK;
    }

    if (0U != ((uint32_t)fifo & (uint32_t)kCSI_StatFifo))
    {
        mask |= CSI_CR1_CLR_STATFIFO_MASK;
    }

    CSI_REG_CR1(base) = (cr1 & ~CSI_CR1_FCC_MASK) | mask;

    /* Wait clear completed. */
    while (0U != (CSI_REG_CR1(base) & mask))
    {
    }

    /* Recover the FCC. */
    CSI_REG_CR1(base) = cr1;
}

/*!
 * brief Reflash the CSI FIFO DMA.
 *
 * This function reflashes the CSI FIFO DMA.
 *
 * For RXFIFO, there are two frame buffers. When the CSI module started, it saves
 * the frames to frame buffer 0 then frame buffer 1, the two buffers will be
 * written by turns. After reflash DMA using this function, the CSI is reset to
 * save frame to buffer 0.
 *
 * param base CSI peripheral base address.
 * param fifo The FIFO DMA to reflash.
 */
void CSI_ReflashFifoDma(CSI_Type *base, csi_fifo_t fifo)
{
    uint32_t cr3 = 0U;

    if (0U != ((uint32_t)fifo & (uint32_t)kCSI_RxFifo))
    {
        cr3 |= CSI_CR3_DMA_REFLASH_RFF_MASK;
    }

    if (0U != ((uint32_t)fifo & (uint32_t)kCSI_StatFifo))
    {
        cr3 |= CSI_CR3_DMA_REFLASH_SFF_MASK;
    }

    CSI_REG_CR3(base) |= cr3;

    /* Wait clear completed. */
    while (0U != (CSI_REG_CR3(base) & cr3))
    {
    }
}

/*!
 * brief Enable or disable the CSI FIFO DMA request.
 *
 * param base CSI peripheral base address.
 * param fifo The FIFO DMA reques to enable or disable.
 * param enable True to enable, false to disable.
 */
void CSI_EnableFifoDmaRequest(CSI_Type *base, csi_fifo_t fifo, bool enable)
{
    uint32_t cr3 = 0U;

    if (0U != ((uint32_t)fifo & (uint32_t)kCSI_RxFifo))
    {
        cr3 |= CSI_CR3_DMA_REQ_EN_RFF_MASK;
    }

    if (0U != ((uint32_t)fifo & (uint32_t)kCSI_StatFifo))
    {
        cr3 |= CSI_CR3_DMA_REQ_EN_SFF_MASK;
    }

    if (enable)
    {
        CSI_REG_CR3(base) |= cr3;
    }
    else
    {
        CSI_REG_CR3(base) &= ~cr3;
    }
}

/*!
 * brief Enables CSI interrupt requests.
 *
 * param base CSI peripheral base address.
 * param mask The interrupts to enable, pass in as OR'ed value of ref _csi_interrupt_enable.
 */
void CSI_EnableInterrupts(CSI_Type *base, uint32_t mask)
{
    CSI_REG_CR1(base) |= (mask & CSI_CR1_INT_EN_MASK);
    CSI_REG_CR3(base) |= (mask & CSI_CR3_INT_EN_MASK);
    CSI_REG_CR18(base) |= ((mask & CSI_CR18_INT_EN_MASK) >> 6U);
}

/*!
 * brief Disable CSI interrupt requests.
 *
 * param base CSI peripheral base address.
 * param mask The interrupts to disable, pass in as OR'ed value of ref _csi_interrupt_enable.
 */
void CSI_DisableInterrupts(CSI_Type *base, uint32_t mask)
{
    CSI_REG_CR1(base) &= ~(mask & CSI_CR1_INT_EN_MASK);
    CSI_REG_CR3(base) &= ~(mask & CSI_CR3_INT_EN_MASK);
    CSI_REG_CR18(base) &= ~((mask & CSI_CR18_INT_EN_MASK) >> 6U);
}

#if !CSI_DRIVER_FRAG_MODE
/*!
 * brief Initializes the CSI handle.
 *
 * This function initializes CSI handle, it should be called before any other
 * CSI transactional functions.
 *
 * param base CSI peripheral base address.
 * param handle Pointer to the handle structure.
 * param callback Callback function for CSI transfer.
 * param userData Callback function parameter.
 *
 * retval kStatus_Success Handle created successfully.
 */
status_t CSI_TransferCreateHandle(CSI_Type *base,
                                  csi_handle_t *handle,
                                  csi_transfer_callback_t callback,
                                  void *userData)
{
    assert(NULL != handle);
    uint32_t instance;

    (void)memset(handle, 0, sizeof(*handle));

    /* Set the callback and user data. */
    handle->callback = callback;
    handle->userData = userData;

    /* Get instance from peripheral base address. */
    instance = CSI_GetInstance(base);

    /* Save the handle in global variables to support the double weak mechanism. */
    s_csiHandle[instance] = handle;

    s_csiIsr = CSI_TransferHandleIRQ;

    /* Enable interrupt. */
    (void)EnableIRQ(s_csiIRQ[instance]);

    return kStatus_Success;
}

/*!
 * brief Start the transfer using transactional functions.
 *
 * When the empty frame buffers have been submit to CSI driver using function
 * ref CSI_TransferSubmitEmptyBuffer, user could call this function to start
 * the transfer. The incoming frame will be saved to the empty frame buffer,
 * and user could be optionally notified through callback function.
 *
 * param base CSI peripheral base address.
 * param handle Pointer to the handle structure.
 *
 * retval kStatus_Success Started successfully.
 * retval kStatus_CSI_NoEmptyBuffer Could not start because no empty frame buffer in queue.
 */
status_t CSI_TransferStart(CSI_Type *base, csi_handle_t *handle)
{
    assert(NULL != handle);

    uint32_t emptyBufferCount;

    emptyBufferCount = CSI_TransferGetEmptyBufferCount(handle);

    if (emptyBufferCount < 2U)
    {
        return kStatus_CSI_NoEmptyBuffer;
    }

    /*
     * Write to memory from first completed frame.
     * DMA base addr switch at the edge of the first data of each frame, thus
     * if one frame is broken, it could be reset at the next frame.
     */
    CSI_REG_CR18(base) = (CSI_REG_CR18(base) & ~CSI_CR18_MASK_OPTION_MASK) | CSI_CR18_MASK_OPTION(0) |
                         CSI_CR18_BASEADDR_SWITCH_SEL_MASK | CSI_CR18_BASEADDR_SWITCH_EN_MASK;

    /* Load the frame buffer to CSI register, there are at least two empty buffers. */
    CSI_REG_DMASA_FB1(base) = CSI_ADDR_CPU_2_IP(CSI_TransferGetEmptyBuffer(handle));
    CSI_REG_DMASA_FB2(base) = CSI_ADDR_CPU_2_IP(CSI_TransferGetEmptyBuffer(handle));

    handle->activeBufferNum = CSI_MAX_ACTIVE_FRAME_NUM;

    /* After reflash DMA, the CSI saves frame to frame buffer 0. */
    CSI_ReflashFifoDma(base, kCSI_RxFifo);

    handle->transferStarted = true;

    CSI_EnableInterrupts(
        base, (uint32_t)kCSI_RxBuffer1DmaDoneInterruptEnable | (uint32_t)kCSI_RxBuffer0DmaDoneInterruptEnable);

    CSI_Start(base);

    return kStatus_Success;
}

/*!
 * brief Stop the transfer using transactional functions.
 *
 * The driver does not clean the full frame buffers in queue. In other words, after
 * calling this function, user still could get the full frame buffers in queue
 * using function ref CSI_TransferGetFullBuffer.
 *
 * param base CSI peripheral base address.
 * param handle Pointer to the handle structure.
 *
 * retval kStatus_Success Stoped successfully.
 */
status_t CSI_TransferStop(CSI_Type *base, csi_handle_t *handle)
{
    assert(NULL != handle);
    uint8_t activeBufferNum;
    uint8_t bufIdx;

    CSI_Stop(base);
    CSI_DisableInterrupts(
        base, (uint32_t)kCSI_RxBuffer1DmaDoneInterruptEnable | (uint32_t)kCSI_RxBuffer0DmaDoneInterruptEnable);

    activeBufferNum = handle->activeBufferNum;

    handle->transferStarted = false;
    handle->activeBufferNum = 0;

    /*
     * Put active buffers to empty queue.
     *
     * If there is only one active frame buffers, then FB0 and FB1 use the same address,
     * put FB0 to empty buffer queue is OK.
     */
    for (bufIdx = 0; bufIdx < activeBufferNum; bufIdx++)
    {
        CSI_TransferPutEmptyBuffer(handle, CSI_GetRxBufferAddr(base, bufIdx));
    }

    return kStatus_Success;
}

/*!
 * brief Submit empty frame buffer to queue.
 *
 * This function could be called before ref CSI_TransferStart or after ref
 * CSI_TransferStart. If there is no room in queue to store the empty frame
 * buffer, this function returns error.
 *
 * param base CSI peripheral base address.
 * param handle Pointer to the handle structure.
 * param frameBuffer Empty frame buffer to submit.
 *
 * retval kStatus_Success Started successfully.
 * retval kStatus_CSI_QueueFull Could not submit because there is no room in queue.
 */
status_t CSI_TransferSubmitEmptyBuffer(CSI_Type *base, csi_handle_t *handle, uint32_t frameBuffer)
{
    uint32_t csicr1;

    /* Disable the interrupt to protect the index information in handle. */
    csicr1 = CSI_REG_CR1(base);

    CSI_REG_CR1(base) = (csicr1 & ~(CSI_CR1_FB2_DMA_DONE_INTEN_MASK | CSI_CR1_FB1_DMA_DONE_INTEN_MASK));

    /* Save the empty frame buffer address to queue. */
    CSI_TransferPutEmptyBuffer(handle, frameBuffer);

    CSI_REG_CR1(base) = csicr1;

    return kStatus_Success;
}

/*!
 * brief Get one full frame buffer from queue.
 *
 * After the transfer started using function ref CSI_TransferStart, the incoming
 * frames will be saved to the empty frame buffers in queue. This function gets
 * the full-filled frame buffer from the queue. If there is no full frame buffer
 * in queue, this function returns error.
 *
 * param base CSI peripheral base address.
 * param handle Pointer to the handle structure.
 * param frameBuffer Full frame buffer.
 *
 * retval kStatus_Success Started successfully.
 * retval kStatus_CSI_NoFullBuffer There is no full frame buffer in queue.
 */
status_t CSI_TransferGetFullBuffer(CSI_Type *base, csi_handle_t *handle, uint32_t *frameBuffer)
{
    uint32_t csicr1;
    status_t status;
    uint8_t queueReadIdx;
    uint8_t queueWriteIdx;

    queueReadIdx  = handle->queueReadIdx;
    queueWriteIdx = handle->queueWriteIdx;

    /* No full frame buffer. */
    if (queueReadIdx == queueWriteIdx)
    {
        status = kStatus_CSI_NoFullBuffer;
    }
    else
    {
        /* Disable the interrupt to protect the index information in handle. */
        csicr1 = CSI_REG_CR1(base);

        CSI_REG_CR1(base) = (csicr1 & ~(CSI_CR1_FB2_DMA_DONE_INTEN_MASK | CSI_CR1_FB1_DMA_DONE_INTEN_MASK));

        *frameBuffer = handle->frameBufferQueue[handle->queueReadIdx];

        handle->queueReadIdx = CSI_TransferIncreaseQueueIdx(handle->queueReadIdx);

        CSI_REG_CR1(base) = csicr1;

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief CSI IRQ handle function.
 *
 * This function handles the CSI IRQ request to work with CSI driver transactional
 * APIs.
 *
 * param base CSI peripheral base address.
 * param handle CSI handle pointer.
 */
void CSI_TransferHandleIRQ(CSI_Type *base, csi_handle_t *handle)
{
    uint8_t queueWriteIdx;
    uint8_t queueReadIdx;
    uint8_t dmaDoneBufferIdx;
    uint32_t frameBuffer;
    uint32_t csisr = CSI_REG_SR(base);

    /* Clear the error flags. */
    CSI_REG_SR(base) = csisr;

    /*
     * If both frame buffer 0 and frame buffer 1 flags assert, driver does not
     * know which frame buffer ready just now, so skip them.
     */
    if ((csisr & (CSI_SR_DMA_TSF_DONE_FB2_MASK | CSI_SR_DMA_TSF_DONE_FB1_MASK)) ==
        (CSI_SR_DMA_TSF_DONE_FB2_MASK | CSI_SR_DMA_TSF_DONE_FB1_MASK))
    {
        ; /* Skip the frames. */
    }
    else if (0U != (csisr & (CSI_SR_DMA_TSF_DONE_FB2_MASK | CSI_SR_DMA_TSF_DONE_FB1_MASK)))
    {
        if (0U != (csisr & CSI_SR_DMA_TSF_DONE_FB2_MASK))
        {
            dmaDoneBufferIdx = 1;
        }
        else
        {
            dmaDoneBufferIdx = 0;
        }

        if (handle->activeBufferNum == CSI_MAX_ACTIVE_FRAME_NUM)
        {
            queueWriteIdx = handle->queueWriteIdx;
            queueReadIdx  = handle->queueReadIdx;

            if (CSI_TransferGetQueueDelta(queueReadIdx, queueWriteIdx) < CSI_DRIVER_QUEUE_SIZE)
            {
                /* Put the full frame buffer to full buffer queue. */
                frameBuffer                             = CSI_GetRxBufferAddr(base, dmaDoneBufferIdx);
                handle->frameBufferQueue[queueWriteIdx] = frameBuffer;

                handle->queueWriteIdx = CSI_TransferIncreaseQueueIdx(queueWriteIdx);

                handle->activeBufferNum--;

                if (NULL != handle->callback)
                {
                    handle->callback(base, handle, kStatus_CSI_FrameDone, handle->userData);
                }
            }
            else
            {
            }
        }

        /*
         * User may submit new frame buffer in callback, so recheck activeBufferNum here,
         * if there is only one active buffer in CSI device, the two buffer registers
         * are both set to the frame buffer address.
         */
        if (handle->activeBufferNum < CSI_MAX_ACTIVE_FRAME_NUM)
        {
            if (CSI_TransferGetEmptyBufferCount(handle) > 0U)
            {
                /* Get the empty frameBuffer, and submit to CSI device. */
                CSI_SetRxBufferAddr(base, dmaDoneBufferIdx, CSI_TransferGetEmptyBuffer(handle));
                handle->activeBufferNum++;
            }
            else
            {
                /* If there is only one active frame buffer, then the two CSI
                 * output buffer address are all set to this frame buffer.
                 */
                frameBuffer = CSI_GetRxBufferAddr(base, dmaDoneBufferIdx ^ 1U);
                CSI_SetRxBufferAddr(base, dmaDoneBufferIdx, frameBuffer);
            }
        }
    }
    else
    {
    }
}

#else /* CSI_DRIVER_FRAG_MODE */

#if defined(__CC_ARM)
__asm void CSI_ExtractYFromYUYV(void *datBase, const void *dmaBase, size_t count)
{
    /* clang-format off */
    push    {r4-r7, lr}
10
    LDMIA    R1!, {r3-r6}
    bfi      r7, r3, #0, #8  /* Y0 */
    bfi      ip, r5, #0, #8  /* Y4 */
    lsr      r3, r3, #16
    lsr      r5, r5, #16
    bfi      r7, r3, #8, #8  /* Y1 */
    bfi      ip, r5, #8, #8  /* Y5 */
    bfi      r7, r4, #16, #8 /* Y2 */
    bfi      ip, r6, #16, #8 /* Y6 */
    lsr      r4, r4, #16
    lsr      r6, r6, #16
    bfi      r7, r4, #24, #8 /* Y3 */
    bfi      ip, r6, #24, #8 /* Y7 */
    STMIA    r0!, {r7, ip}
    subs     r2, #8
    bne      %b10
    pop      {r4-r7, pc}
    /* clang-format on */
}

__asm void CSI_ExtractYFromUYVY(void *datBase, const void *dmaBase, size_t count)
{
    /* clang-format off */
    push    {r4-r7, lr}
10
    LDMIA    R1!, {r3-r6}
    lsr      r3, r3, #8
    lsr      r5, r5, #8
    bfi      r7, r3, #0, #8  /* Y0 */
    bfi      ip, r5, #0, #8  /* Y4 */
    lsr      r3, r3, #16
    lsr      r5, r5, #16
    bfi      r7, r3, #8, #8  /* Y1 */
    bfi      ip, r5, #8, #8  /* Y5 */
    lsr      r4, r4, #8
    lsr      r6, r6, #8
    bfi      r7, r4, #16, #8 /* Y2 */
    bfi      ip, r6, #16, #8 /* Y6 */
    lsr      r4, r4, #16
    lsr      r6, r6, #16
    bfi      r7, r4, #24, #8 /* Y3 */
    bfi      ip, r6, #24, #8 /* Y7 */
    STMIA    r0!, {r7, ip}
    subs     r2, #8
    bne      %b10
    pop      {r4-r7, pc}
    /* clang-format on */
}

#elif (defined(__GNUC__) || defined(__ICCARM__)) || defined(__ARMCC_VERSION)
#if defined(__ICCARM__)
#pragma diag_suppress = Pe940
#endif
__attribute__((naked)) void CSI_ExtractYFromYUYV(void *datBase, const void *dmaBase, size_t count);
void CSI_ExtractYFromYUYV(void *datBase, const void *dmaBase, size_t count)
{
    /* clang-format off */
    __asm volatile(
        "    push    {r1-r7, r12, lr}  \n"
        "loop0:                        \n"
        "    ldmia   r1!, {r3-r6}      \n"
        "    bfi     r7, r3, #0, #8    \n" /* Y0 */
        "    bfi     r12, r5, #0, #8   \n" /* Y4 */
        "    lsr     r3, r3, #16       \n"
        "    lsr     r5, r5, #16       \n"
        "    bfi     r7, r3, #8, #8    \n" /* Y1 */
        "    bfi     r12, r5, #8, #8   \n" /* Y5 */
        "    bfi     r7, r4, #16, #8   \n" /* Y2 */
        "    bfi     r12, r6, #16, #8  \n" /* Y6 */
        "    lsr     r4, r4, #16       \n"
        "    lsr     r6, r6, #16       \n"
        "    bfi     r7, r4, #24, #8   \n" /* Y3 */
        "    bfi     r12, r6, #24, #8  \n" /* Y7 */
        "    stmia   r0!, {r7, r12}    \n"
        "    subs    r2, #8            \n"
        "    bne     loop0             \n"
        "    pop     {r1-r7, r12, pc}  \n");
    /* clang-format on */
}

__attribute__((naked)) void CSI_ExtractYFromUYVY(void *datBase, const void *dmaBase, size_t count);
void CSI_ExtractYFromUYVY(void *datBase, const void *dmaBase, size_t count)
{
    /* clang-format off */
    __asm volatile(
        "    push    {r1-r7, r12, lr}  \n"
        "loop1:                        \n"
        "    ldmia   r1!, {r3-r6}      \n"
        "    lsr     r3, r3, #8        \n"
        "    lsr     r5, r5, #8        \n"
        "    bfi     r7, r3, #0, #8    \n" /* Y0 */
        "    bfi     r12, r5, #0, #8   \n" /* Y4 */
        "    lsr     r3, r3, #16       \n"
        "    lsr     r5, r5, #16       \n"
        "    bfi     r7, r3, #8, #8    \n" /* Y1 */
        "    bfi     r12, r5, #8, #8   \n" /* Y5 */
        "    lsr     r4, r4, #8        \n"
        "    lsr     r6, r6, #8        \n"
        "    bfi     r7, r4, #16, #8   \n" /* Y2 */
        "    bfi     r12, r6, #16, #8  \n" /* Y6 */
        "    lsr     r4, r4, #16       \n"
        "    lsr     r6, r6, #16       \n"
        "    bfi     r7, r4, #24, #8   \n" /* Y3 */
        "    bfi     r12, r6, #24, #8  \n" /* Y7 */
        "    stmia   r0!, {r7, r12}    \n"
        "    subs    r2, #8            \n"
        "    bne     loop1             \n"
        "    pop     {r1-r7, r12, pc}  \n");
    /* clang-format on */
}
#if defined(__ICCARM__)
#pragma diag_default = Pe940
#endif
#else
#error Toolchain not supported.
#endif

static void CSI_MemCopy(void *pDest, const void *pSrc, size_t cnt)
{
    (void)memcpy(pDest, pSrc, cnt);
}

/*!
 * brief Initialize the CSI to work in fragment mode.
 *
 * This function enables the CSI peripheral clock, and resets the CSI registers.
 *
 * param base CSI peripheral base address.
 */
void CSI_FragModeInit(CSI_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = CSI_GetInstance(base);
    CLOCK_EnableClock(s_csiClocks[instance]);
#endif

    CSI_Reset(base);
}

/*!
 * brief De-initialize the CSI.
 *
 * This function disables the CSI peripheral clock.
 *
 * param base CSI peripheral base address.
 */
void CSI_FragModeDeinit(CSI_Type *base)
{
    CSI_Deinit(base);
}

/*!
 * brief Create handle for CSI work in fragment mode.
 *
 * param base CSI peripheral base address.
 * param handle Pointer to the transactional handle.
 * param config Pointer to the configuration structure.
 * param callback Callback function for CSI transfer.
 * param userData Callback function parameter.
 *
 * retval kStatus_Success Initialize successfully.
 * retval kStatus_InvalidArgument Initialize failed because of invalid argument.
 */
status_t CSI_FragModeCreateHandle(CSI_Type *base,
                                  csi_frag_handle_t *handle,
                                  const csi_frag_config_t *config,
                                  csi_frag_transfer_callback_t callback,
                                  void *userData)
{
    assert(NULL != config);
    uint32_t reg;
    uint32_t instance;
    uint32_t imgWidth_Bytes;

    if (config->dataBus != kCSI_DataBus8Bit)
    {
        return kStatus_InvalidArgument;
    }

    imgWidth_Bytes = (uint32_t)config->width * CSI_FRAG_INPUT_BYTES_PER_PIXEL;

    /* The image buffer line width should be multiple of 8-bytes. */
    if ((imgWidth_Bytes & 0x07U) != 0U)
    {
        return kStatus_InvalidArgument;
    }

    /* Camera frame height must be dividable by DMA buffer line. */
    if (config->height % config->dmaBufferLine != 0U)
    {
        return kStatus_InvalidArgument;
    }

    (void)memset(handle, 0, sizeof(*handle));
    handle->callback            = callback;
    handle->userData            = userData;
    handle->height              = config->height;
    handle->width               = config->width;
    handle->maxLinePerFrag      = config->dmaBufferLine;
    handle->dmaBytePerLine      = config->width * CSI_FRAG_INPUT_BYTES_PER_PIXEL;
    handle->isDmaBufferCachable = config->isDmaBufferCachable;

    /* Get instance from peripheral base address. */
    instance = CSI_GetInstance(base);
    /* Save the handle in global variables to support the double weak mechanism. */
    s_csiHandle[instance] = handle;

    s_csiIsr = CSI_FragModeTransferHandleIRQ;

    (void)EnableIRQ(s_csiIRQ[instance]);

    /* Configure CSICR1. CSICR1 has been reset to the default value, so could write it directly. */
    reg = ((uint32_t)config->workMode) | config->polarityFlags | CSI_CR1_FCC_MASK;

    if (config->useExtVsync)
    {
        reg |= CSI_CR1_EXT_VSYNC_MASK;
    }

    CSI_REG_CR1(base) = reg;

    /* No stride. */
    CSI_REG_FBUF_PARA(base) = 0;

    /* Enable auto ECC. */
    CSI_REG_CR3(base) |= CSI_CR3_ECC_AUTO_EN_MASK;

    /*
     * For better performance.
     * The DMA burst size could be set to 16 * 8 byte, 8 * 8 byte, or 4 * 8 byte,
     * choose the best burst size based on bytes per line.
     */
    if (0U == (imgWidth_Bytes % (8U * 16U)))
    {
        CSI_REG_CR2(base) = CSI_CR2_DMA_BURST_TYPE_RFF(3U);
        CSI_REG_CR3(base) = (CSI_REG_CR3(base) & ~CSI_CR3_RxFF_LEVEL_MASK) | ((2U << CSI_CR3_RxFF_LEVEL_SHIFT));
    }
    else if (0U == (imgWidth_Bytes % (8U * 8U)))
    {
        CSI_REG_CR2(base) = CSI_CR2_DMA_BURST_TYPE_RFF(2U);
        CSI_REG_CR3(base) = (CSI_REG_CR3(base) & ~CSI_CR3_RxFF_LEVEL_MASK) | ((1U << CSI_CR3_RxFF_LEVEL_SHIFT));
    }
    else
    {
        CSI_REG_CR2(base) = CSI_CR2_DMA_BURST_TYPE_RFF(1U);
        CSI_REG_CR3(base) = (CSI_REG_CR3(base) & ~CSI_CR3_RxFF_LEVEL_MASK) | ((0U << CSI_CR3_RxFF_LEVEL_SHIFT));
    }

    CSI_REG_DMASA_FB1(base) = CSI_ADDR_CPU_2_IP(config->dmaBufferAddr0);
    CSI_REG_DMASA_FB2(base) = CSI_ADDR_CPU_2_IP(config->dmaBufferAddr1);

    if (handle->isDmaBufferCachable)
    {
        DCACHE_CleanInvalidateByRange(
            config->dmaBufferAddr0,
            (uint32_t)config->dmaBufferLine * (uint32_t)config->width * CSI_FRAG_INPUT_BYTES_PER_PIXEL);
        DCACHE_CleanInvalidateByRange(
            config->dmaBufferAddr1,
            (uint32_t)config->dmaBufferLine * (uint32_t)config->width * CSI_FRAG_INPUT_BYTES_PER_PIXEL);
    }

    return kStatus_Success;
}

/*!
 * brief Start to capture a image.
 *
 * param base CSI peripheral base address.
 * param handle Pointer to the transactional handle.
 * param config Pointer to the capture configuration.
 *
 * retval kStatus_Success Initialize successfully.
 * retval kStatus_InvalidArgument Initialize failed because of invalid argument.
 */
status_t CSI_FragModeTransferCaptureImage(CSI_Type *base,
                                          csi_frag_handle_t *handle,
                                          const csi_frag_capture_config_t *config)
{
    assert(NULL != config);

    uint16_t windowWidth;

    /*
     * If no special window setting, capture full frame.
     * If capture window, then capture 1 one each fragment.
     */
    if (config->window != NULL)
    {
        handle->windowULX   = config->window->windowULX;
        handle->windowULY   = config->window->windowULY;
        handle->windowLRX   = config->window->windowLRX;
        handle->windowLRY   = config->window->windowLRY;
        handle->linePerFrag = 1;
    }
    else
    {
        handle->windowULX   = 0;
        handle->windowULY   = 0;
        handle->windowLRX   = handle->width - 1U;
        handle->windowLRY   = handle->height - 1U;
        handle->linePerFrag = handle->maxLinePerFrag;
    }

    windowWidth = handle->windowLRX - handle->windowULX + 1U;

    if (config->outputGrayScale)
    {
        /* When output format is gray, the window width must be multiple value of 8. */
        if (windowWidth % 8U != 0U)
        {
            return kStatus_InvalidArgument;
        }

        handle->datBytePerLine = windowWidth;
        if (handle->inputFormat == kCSI_FragInputYUYV)
        {
            handle->copyFunc = CSI_ExtractYFromYUYV;
        }
        else
        {
            handle->copyFunc = CSI_ExtractYFromUYVY;
        }
    }
    else
    {
        handle->datBytePerLine = windowWidth * CSI_FRAG_INPUT_BYTES_PER_PIXEL;
        handle->copyFunc       = CSI_MemCopy;
    }

    handle->dmaCurLine      = 0;
    handle->outputBuffer    = (uint32_t)config->buffer;
    handle->datCurWriteAddr = (uint32_t)config->buffer;

    /* Image parameter. */
    CSI_REG_IMAG_PARA(base) =
        (((uint32_t)handle->width * CSI_FRAG_INPUT_BYTES_PER_PIXEL) << CSI_IMAG_PARA_IMAGE_WIDTH_SHIFT) |
        ((uint32_t)(handle->linePerFrag) << CSI_IMAG_PARA_IMAGE_HEIGHT_SHIFT);

    /*
     * Write to memory from first completed frame.
     * DMA base addr switch at dma transfer done.
     */
    CSI_REG_CR18(base) = (CSI_REG_CR18(base) & ~CSI_CR18_MASK_OPTION_MASK) | CSI_CR18_MASK_OPTION(0);

    CSI_EnableInterrupts(base, (uint32_t)kCSI_StartOfFrameInterruptEnable |
                                   (uint32_t)kCSI_RxBuffer1DmaDoneInterruptEnable |
                                   (uint32_t)kCSI_RxBuffer0DmaDoneInterruptEnable);

    return kStatus_Success;
}

/*!
 * brief Abort image capture.
 *
 * Abort image capture initialized by ref CSI_FragModeTransferCaptureImage.
 *
 * param base CSI peripheral base address.
 * param handle Pointer to the transactional handle.
 */
void CSI_FragModeTransferAbortCaptureImage(CSI_Type *base, csi_frag_handle_t *handle)
{
    CSI_Stop(base);
    CSI_DisableInterrupts(base, (uint32_t)kCSI_StartOfFrameInterruptEnable |
                                    (uint32_t)kCSI_RxBuffer1DmaDoneInterruptEnable |
                                    (uint32_t)kCSI_RxBuffer0DmaDoneInterruptEnable);
}

/*!
 * brief CSI IRQ handle function.
 *
 * This function handles the CSI IRQ request to work with CSI driver fragment mode
 * APIs.
 *
 * param base CSI peripheral base address.
 * param handle CSI handle pointer.
 */
void CSI_FragModeTransferHandleIRQ(CSI_Type *base, csi_frag_handle_t *handle)
{
    uint32_t csisr = CSI_REG_SR(base);
    uint32_t dmaBufAddr;
    uint16_t line;
    pvoid_to_u32_t memSrc;
    pvoid_to_u32_t memDest;

    /* Clear the error flags. */
    CSI_REG_SR(base) = csisr;

    /* Start of frame, clear the FIFO and start receiving. */
    if (0U != (csisr & (uint32_t)kCSI_StartOfFrameFlag))
    {
        /* Reflash the DMA and enable RX DMA request. */
        CSI_REG_CR3(base) |= (CSI_CR3_DMA_REFLASH_RFF_MASK | CSI_CR3_DMA_REQ_EN_RFF_MASK);
        CSI_Start(base);
        handle->dmaCurLine      = 0;
        handle->datCurWriteAddr = handle->outputBuffer;
    }
    else if ((csisr & (CSI_SR_DMA_TSF_DONE_FB2_MASK | CSI_SR_DMA_TSF_DONE_FB1_MASK)) != 0U)
    {
        if ((csisr & CSI_SR_DMA_TSF_DONE_FB1_MASK) == CSI_SR_DMA_TSF_DONE_FB1_MASK)
        {
            dmaBufAddr = CSI_REG_DMASA_FB1(base);
        }
        else
        {
            dmaBufAddr = CSI_REG_DMASA_FB2(base);
        }

        dmaBufAddr = CSI_ADDR_IP_2_CPU(dmaBufAddr);

        if (handle->isDmaBufferCachable)
        {
            DCACHE_InvalidateByRange(dmaBufAddr, (uint32_t)handle->dmaBytePerLine * (uint32_t)handle->linePerFrag);
        }

        /* Copy from DMA buffer to user data buffer. */
        dmaBufAddr += ((uint32_t)handle->windowULX * CSI_FRAG_INPUT_BYTES_PER_PIXEL);

        for (line = 0; line < handle->linePerFrag; line++)
        {
            if (handle->dmaCurLine + line > handle->windowLRY)
            {
                /* out of window range */
                break;
            }
            else if (handle->dmaCurLine + line >= handle->windowULY)
            {
                memDest.u32 = handle->datCurWriteAddr;
                memSrc.u32  = dmaBufAddr;

                handle->copyFunc(memDest.pvoid, memSrc.pvoid, handle->datBytePerLine);
                handle->datCurWriteAddr += handle->datBytePerLine;
                dmaBufAddr += handle->dmaBytePerLine;
            }
            else
            {
                ; /* For MISRA C-2012 Rule 15.7 */
            }
        }

        handle->dmaCurLine += handle->linePerFrag;

        if (handle->dmaCurLine >= handle->height)
        {
            CSI_Stop(base);
            CSI_DisableInterrupts(base, (uint32_t)kCSI_StartOfFrameInterruptEnable |
                                            (uint32_t)kCSI_RxBuffer1DmaDoneInterruptEnable |
                                            (uint32_t)kCSI_RxBuffer0DmaDoneInterruptEnable);

            /* Image captured. Stop the CSI. */
            if (NULL != handle->callback)
            {
                handle->callback(base, handle, kStatus_CSI_FrameDone, handle->userData);
            }
        }
    }
    else
    {
    }
}
#endif /* CSI_DRIVER_FRAG_MODE */

#if defined(CSI)
void CSI_DriverIRQHandler(void);
void CSI_DriverIRQHandler(void)
{
    s_csiIsr(CSI, s_csiHandle[0]);
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(CSI0)
void CSI0_DriverIRQHandler(void);
void CSI0_DriverIRQHandler(void)
{
    s_csiIsr(CSI, s_csiHandle[0]);
    SDK_ISR_EXIT_BARRIER;
}
#endif
