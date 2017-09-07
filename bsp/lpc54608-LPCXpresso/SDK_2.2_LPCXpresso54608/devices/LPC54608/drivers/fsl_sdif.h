/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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
#ifndef _FSL_SDIF_H_
#define _FSL_SDIF_H_

#include "fsl_common.h"

/*!
 * @addtogroup sdif
 * @{
 */

/******************************************************************************
 * Definitions.
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Driver version 2.0.1. */
#define FSL_SDIF_DRIVER_VERSION (MAKE_VERSION(2U, 0U, 1U))
/*@}*/

#define SDIF_DriverIRQHandler SDIO_DriverIRQHandler /*!< convert the name here, due to RM use SDIO */

#define SDIF_SUPPORT_SD_VERSION (0x20)  /*!< define the controller support sd/sdio card version 2.0 */
#define SDIF_SUPPORT_MMC_VERSION (0x44) /*!< define the controller support mmc card version 4.4 */

#define SDIF_TIMEOUT_VALUE (65535U)    /*!< define the timeout counter */
#define SDIF_POLL_DEMAND_VALUE (0xFFU) /*!< this value can be any value */

#define SDIF_DMA_DESCRIPTOR_BUFFER1_SIZE(x) (x & 0x1FFFU)          /*!< DMA descriptor buffer1 size */
#define SDIF_DMA_DESCRIPTOR_BUFFER2_SIZE(x) ((x & 0x1FFFU) << 13U) /*!<DMA descriptor buffer2 size */
#define SDIF_RX_WATERMARK (15U)                                    /*!<RX water mark value */
#define SDIF_TX_WATERMARK (16U)                                    /*!<TX water mark value */

/*! @brief  SDIOCLKCTRL setting
* below clock delay setting should meet you board layout
* user can change it when you meet timing mismatch issue
* such as: response error/CRC error and so on
*/
#define SDIF_INDENTIFICATION_MODE_SAMPLE_DELAY (0X17U)
#define SDIF_INDENTIFICATION_MODE_DRV_DELAY (0X17U)
#define SDIF_HIGHSPEED_25MHZ_SAMPLE_DELAY (0x10U)
#define SDIF_HIGHSPEED_25MHZ_DRV_DELAY (0x10U)
#define SDIF_HIGHSPEED_50MHZ_SAMPLE_DELAY (0x1FU)
#define SDIF_HIGHSPEED_50MHZ_DRV_DELAY (0x1FU)

/*! @brief SDIF status */
enum _sdif_status
{
    kStatus_SDIF_DescriptorBufferLenError = MAKE_STATUS(kStatusGroup_SDIF, 0U), /*!< Set DMA descriptor failed */
    kStatue_SDIF_InvalidArgument = MAKE_STATUS(kStatusGroup_SDIF, 1U),          /*!< invalid argument status */
    kStatus_SDIF_SyncCmdTimeout = MAKE_STATUS(kStatusGroup_SDIF, 2U), /*!< sync command to CIU timeout status */
    kStatus_SDIF_SendCmdFail = MAKE_STATUS(kStatusGroup_SDIF, 3U),    /* send command to card fail */
    kStatus_SDIF_SendCmdErrorBufferFull =
        MAKE_STATUS(kStatusGroup_SDIF, 4U), /* send command to card fail, due to command buffer full
                                     user need to resend this command */
    kStatus_SDIF_DMATransferFailWithFBE =
        MAKE_STATUS(kStatusGroup_SDIF, 5U), /* DMA transfer data fail with fatal bus error ,
                                     to do with this error :issue a hard reset/controller reset*/
    kStatus_SDIF_DMATransferDescriptorUnavaliable = MAKE_STATUS(kStatusGroup_SDIF, 6U), /* DMA descriptor unavalible */
    kStatus_SDIF_DataTransferFail = MAKE_STATUS(kStatusGroup_SDIF, 6U),                 /* transfer data fail */
    kStatus_SDIF_ResponseError = MAKE_STATUS(kStatusGroup_SDIF, 7U),
};

/*! @brief Host controller capabilities flag mask */
enum _sdif_capability_flag
{
    kSDIF_SupportHighSpeedFlag = 0x1U,     /*!< Support high-speed */
    kSDIF_SupportDmaFlag = 0x2U,           /*!< Support DMA */
    kSDIF_SupportSuspendResumeFlag = 0x4U, /*!< Support suspend/resume */
    kSDIF_SupportV330Flag = 0x8U,          /*!< Support voltage 3.3V */
    kSDIF_Support4BitFlag = 0x10U,         /*!< Support 4 bit mode */
    kSDIF_Support8BitFlag = 0x20U,         /*!< Support 8 bit mode */
};

/*! @brief define the reset type */
enum _sdif_reset_type
{
    kSDIF_ResetController =
        SDIF_CTRL_CONTROLLER_RESET_MASK,                /*!< reset controller,will reset: BIU/CIU interface
                                                          CIU and state machine,ABORT_READ_DATA,SEND_IRQ_RESPONSE
                                                          and READ_WAIT bits of control register,START_CMD bit of the
                                                          command register*/
    kSDIF_ResetFIFO = SDIF_CTRL_FIFO_RESET_MASK,        /*!< reset data FIFO*/
    kSDIF_ResetDMAInterface = SDIF_CTRL_DMA_RESET_MASK, /*!< reset DMA interface */

    kSDIF_ResetAll = kSDIF_ResetController | kSDIF_ResetFIFO | /*!< reset all*/
                     kSDIF_ResetDMAInterface,
};

/*! @brief define the card bus width type */
typedef enum _sdif_bus_width
{
    kSDIF_Bus1BitWidth = 0U,                          /*!< 1bit bus width, 1bit mode and 4bit mode
                                                      share one register bit */
    kSDIF_Bus4BitWidth = SDIF_CTYPE_CARD_WIDTH0_MASK, /*!< 4bit mode mask */
    kSDIF_Bus8BitWidth = SDIF_CTYPE_CARD_WIDTH1_MASK, /*!< support 8 bit mode */
} sdif_bus_width_t;

/*! @brief define the command flags */
enum _sdif_command_flags
{
    kSDIF_CmdResponseExpect = SDIF_CMD_RESPONSE_EXPECT_MASK,      /*!< command request response*/
    kSDIF_CmdResponseLengthLong = SDIF_CMD_RESPONSE_LENGTH_MASK,  /*!< command response length long */
    kSDIF_CmdCheckResponseCRC = SDIF_CMD_CHECK_RESPONSE_CRC_MASK, /*!< request check command response CRC*/
    kSDIF_DataExpect = SDIF_CMD_DATA_EXPECTED_MASK,               /*!< request data transfer,ethier read/write*/
    kSDIF_DataWriteToCard = SDIF_CMD_READ_WRITE_MASK,             /*!< data transfer direction */
    kSDIF_DataStreamTransfer = SDIF_CMD_TRANSFER_MODE_MASK,    /*!< data transfer mode :stream/block transfer command */
    kSDIF_DataTransferAutoStop = SDIF_CMD_SEND_AUTO_STOP_MASK, /*!< data transfer with auto stop at the end of */
    kSDIF_WaitPreTransferComplete =
        SDIF_CMD_WAIT_PRVDATA_COMPLETE_MASK, /*!< wait pre transfer complete before sending this cmd  */
    kSDIF_TransferStopAbort =
        SDIF_CMD_STOP_ABORT_CMD_MASK, /*!< when host issue stop or abort cmd to stop data transfer
                                       ,this bit should set so that cmd/data state-machines of CIU can return
                                       to idle correctly*/
    kSDIF_SendInitialization =
        SDIF_CMD_SEND_INITIALIZATION_MASK, /*!< send initaliztion  80 clocks for SD card after power on  */
    kSDIF_CmdUpdateClockRegisterOnly =
        SDIF_CMD_UPDATE_CLOCK_REGISTERS_ONLY_MASK,                /*!< send cmd update the CIU clock register only */
    kSDIF_CmdtoReadCEATADevice = SDIF_CMD_READ_CEATA_DEVICE_MASK, /*!< host is perform read access to CE-ATA device */
    kSDIF_CmdExpectCCS = SDIF_CMD_CCS_EXPECTED_MASK,         /*!< command expect command completion signal signal */
    kSDIF_BootModeEnable = SDIF_CMD_ENABLE_BOOT_MASK,        /*!< this bit should only be set for mandatory boot mode */
    kSDIF_BootModeExpectAck = SDIF_CMD_EXPECT_BOOT_ACK_MASK, /*!< boot mode expect ack */
    kSDIF_BootModeDisable = SDIF_CMD_DISABLE_BOOT_MASK,      /*!< when software set this bit along with START_CMD, CIU
                                                                terminates the boot operation*/
    kSDIF_BootModeAlternate = SDIF_CMD_BOOT_MODE_MASK,       /*!< select boot mode ,alternate or mandatory*/
    kSDIF_CmdVoltageSwitch = SDIF_CMD_VOLT_SWITCH_MASK,      /*!< this bit set for CMD11 only */
    kSDIF_CmdDataUseHoldReg = SDIF_CMD_USE_HOLD_REG_MASK,    /*!< cmd and data send to card through the HOLD register*/
};

/*! @brief The command type */
enum _sdif_command_type
{
    kCARD_CommandTypeNormal = 0U,  /*!< Normal command */
    kCARD_CommandTypeSuspend = 1U, /*!< Suspend command */
    kCARD_CommandTypeResume = 2U,  /*!< Resume command */
    kCARD_CommandTypeAbort = 3U,   /*!< Abort command */
};

/*!
 * @brief The command response type.
 *
 * Define the command response type from card to host controller.
 */
enum _sdif_response_type
{
    kCARD_ResponseTypeNone = 0U, /*!< Response type: none */
    kCARD_ResponseTypeR1 = 1U,   /*!< Response type: R1 */
    kCARD_ResponseTypeR1b = 2U,  /*!< Response type: R1b */
    kCARD_ResponseTypeR2 = 3U,   /*!< Response type: R2 */
    kCARD_ResponseTypeR3 = 4U,   /*!< Response type: R3 */
    kCARD_ResponseTypeR4 = 5U,   /*!< Response type: R4 */
    kCARD_ResponseTypeR5 = 6U,   /*!< Response type: R5 */
    kCARD_ResponseTypeR5b = 7U,  /*!< Response type: R5b */
    kCARD_ResponseTypeR6 = 8U,   /*!< Response type: R6 */
    kCARD_ResponseTypeR7 = 9U,   /*!< Response type: R7 */
};

/*! @brief define the interrupt mask flags */
enum _sdif_interrupt_mask
{
    kSDIF_CardDetect = SDIF_INTMASK_CDET_MASK,                 /*!< mask for card detect */
    kSDIF_ResponseError = SDIF_INTMASK_RE_MASK,                /*!< command response error */
    kSDIF_CommandDone = SDIF_INTMASK_CDONE_MASK,               /*!< command transfer over*/
    kSDIF_DataTransferOver = SDIF_INTMASK_DTO_MASK,            /*!< data transfer over flag*/
    kSDIF_WriteFIFORequest = SDIF_INTMASK_TXDR_MASK,           /*!< write FIFO request */
    kSDIF_ReadFIFORequest = SDIF_INTMASK_RXDR_MASK,            /*!< read FIFO request */
    kSDIF_ResponseCRCError = SDIF_INTMASK_RCRC_MASK,           /*!< reponse CRC error */
    kSDIF_DataCRCError = SDIF_INTMASK_DCRC_MASK,               /*!< data CRC error */
    kSDIF_ResponseTimeout = SDIF_INTMASK_RTO_MASK,             /*!< response timeout */
    kSDIF_DataReadTimeout = SDIF_INTMASK_DRTO_MASK,            /*!< read data timeout */
    kSDIF_DataStarvationByHostTimeout = SDIF_INTMASK_HTO_MASK, /*!< data starvation by host time out */
    kSDIF_FIFOError = SDIF_INTMASK_FRUN_MASK,                  /*!< indicate the FIFO underrun or overrun error */
    kSDIF_HardwareLockError = SDIF_INTMASK_HLE_MASK,           /*!< hardware lock write error */
    kSDIF_DataStartBitError = SDIF_INTMASK_SBE_MASK,           /*!< start bit error */
    kSDIF_AutoCmdDone = SDIF_INTMASK_ACD_MASK,                 /*!< indicate the auto command done */
    kSDIF_DataEndBitError = SDIF_INTMASK_EBE_MASK,             /*!< end bit error */
    kSDIF_SDIOInterrupt = SDIF_INTMASK_SDIO_INT_MASK_MASK,     /*!< interrupt from the SDIO card */

    kSDIF_CommandTransferStatus = kSDIF_ResponseError | kSDIF_CommandDone | kSDIF_ResponseCRCError |
                                  kSDIF_ResponseTimeout |
                                  kSDIF_HardwareLockError, /*!< command transfer status collection*/
    kSDIF_DataTransferStatus = kSDIF_DataTransferOver | kSDIF_WriteFIFORequest | kSDIF_ReadFIFORequest |
                               kSDIF_DataCRCError | kSDIF_DataReadTimeout | kSDIF_DataStarvationByHostTimeout |
                               kSDIF_FIFOError | kSDIF_DataStartBitError | kSDIF_DataEndBitError |
                               kSDIF_AutoCmdDone, /*!< data transfer status collection */
    kSDIF_DataTransferError =
        kSDIF_DataCRCError | kSDIF_FIFOError | kSDIF_DataStartBitError | kSDIF_DataEndBitError | kSDIF_DataReadTimeout,
    kSDIF_AllInterruptStatus = 0x1FFFFU, /*!< all interrupt mask */

};

/*! @brief define the internal DMA status flags */
enum _sdif_dma_status
{
    kSDIF_DMATransFinishOneDescriptor = SDIF_IDSTS_TI_MASK, /*!< DMA transfer finished for one DMA descriptor */
    kSDIF_DMARecvFinishOneDescriptor = SDIF_IDSTS_RI_MASK,  /*!< DMA revieve finished for one DMA descriptor */
    kSDIF_DMAFatalBusError = SDIF_IDSTS_FBE_MASK,           /*!< DMA fatal bus error */
    kSDIF_DMADescriptorUnavailable = SDIF_IDSTS_DU_MASK,    /*!< DMA descriptor unavailable */
    kSDIF_DMACardErrorSummary = SDIF_IDSTS_CES_MASK,        /*!< card error summary */
    kSDIF_NormalInterruptSummary = SDIF_IDSTS_NIS_MASK,     /*!< normal interrupt summary */
    kSDIF_AbnormalInterruptSummary = SDIF_IDSTS_AIS_MASK,   /*!< abnormal interrupt summary*/

    kSDIF_DMAAllStatus = kSDIF_DMATransFinishOneDescriptor | kSDIF_DMARecvFinishOneDescriptor | kSDIF_DMAFatalBusError |
                         kSDIF_DMADescriptorUnavailable | kSDIF_DMACardErrorSummary | kSDIF_NormalInterruptSummary |
                         kSDIF_AbnormalInterruptSummary,

};

/*! @brief define the internal DMA descriptor flag */
enum _sdif_dma_descriptor_flag
{
    kSDIF_DisableCompleteInterrupt = 0x2U,     /*!< disable the complete interrupt flag for the ends
                                                in the buffer pointed to by this descriptor*/
    kSDIF_DMADescriptorDataBufferEnd = 0x4U,   /*!< indicate this descriptor contain the last data buffer of data */
    kSDIF_DMADescriptorDataBufferStart = 0x8U, /*!< indicate this descriptor contain the first data buffer
                                                 of data,if first buffer size is 0,next descriptor contain
                                                 the begaining of the data*/
    kSDIF_DMASecondAddrChained = 0x10U,        /*!< indicate that the second addr in the descriptor is the
                                               next descriptor addr not the data buffer */
    kSDIF_DMADescriptorEnd = 0x20U,            /*!< indicate that the descriptor list reached its final descriptor*/
    kSDIF_DMADescriptorOwnByDMA = 0x80000000U, /*!< indicate the descriptor is own by SD/MMC DMA */
};

/*! @brief define the internal DMA mode */
typedef enum _sdif_dma_mode
{
    kSDIF_ChainDMAMode = 0x01U, /* one descriptor with one buffer,but one descriptor point to another */
    kSDIF_DualDMAMode = 0x02U,  /* dual mode is one descriptor with two buffer */
} sdif_dma_mode_t;

/*! @brief define the card work freq mode */
enum _sdif_card_freq
{
    kSDIF_Freq50MHZ = 50000000U, /*!< 50MHZ mode*/
    kSDIF_Freq400KHZ = 400000U,  /*!< identificatioin mode*/
};

/*! @brief define the clock pharse shift */
enum _sdif_clock_pharse_shift
{
    kSDIF_ClcokPharseShift0,   /*!< clock pharse shift 0*/
    kSDIF_ClcokPharseShift90,  /*!< clock pharse shift 90*/
    kSDIF_ClcokPharseShift180, /*!< clock pharse shift 180*/
    kSDIF_ClcokPharseShift270, /*!< clock pharse shift 270*/
};

/*! @brief define the internal DMA descriptor */
typedef struct _sdif_dma_descriptor
{
    uint32_t dmaDesAttribute;           /*!< internal DMA attribute control and status */
    uint32_t dmaDataBufferSize;         /*!< internal DMA transfer buffer size control */
    const uint32_t *dmaDataBufferAddr0; /*!< internal DMA buffer 0 addr ,the buffer size must be 32bit aligned */
    const uint32_t *dmaDataBufferAddr1; /*!< internal DMA buffer 1 addr ,the buffer size must be 32bit aligned */

} sdif_dma_descriptor_t;

/*! @brief Defines the internal DMA config structure. */
typedef struct _sdif_dma_config
{
    bool enableFixBurstLen; /*!< fix burst len enable/disable flag,When set, the AHB will
                             use only SINGLE, INCR4, INCR8 or INCR16 during start of
                             normal burst transfers. When reset, the AHB will use SINGLE
                             and INCR burst transfer operations */

    sdif_dma_mode_t mode; /*!< define the DMA mode */

    uint8_t dmaDesSkipLen; /*!< define the descriptor skip length ,the length between two descriptor
                               this field is special for dual DMA mode */

    uint32_t *dmaDesBufferStartAddr; /*!< internal DMA descriptor start address*/
    uint32_t dmaDesBufferLen;        /*!< internal DMA buffer descriptor buffer len ,user need to pay attention to the
                                        dma descriptor buffer length if it is bigger enough for your transfer */

} sdif_dma_config_t;

/*!
 * @brief Card data descriptor
 */
typedef struct _sdif_data
{
    bool streamTransfer;      /*!< indicate this is a stream data transfer command */
    bool enableAutoCommand12; /*!< indicate if auto stop will send when data transfer over */
    bool enableIgnoreError;   /*!< indicate if enable ignore error when transfer data */

    size_t blockSize;       /*!< Block size, take care when config this parameter */
    uint32_t blockCount;    /*!< Block count */
    uint32_t *rxData;       /*!< data buffer to recieve */
    const uint32_t *txData; /*!< data buffer to transfer */
} sdif_data_t;

/*!
 * @brief Card command descriptor
 *
 * Define card command-related attribute.
 */
typedef struct _sdif_command
{
    uint32_t index;              /*!< Command index */
    uint32_t argument;           /*!< Command argument */
    uint32_t response[4U];       /*!< Response for this command */
    uint32_t type;               /*!< define the command type */
    uint32_t responseType;       /*!< Command response type */
    uint32_t flags;              /*!< Cmd flags */
    uint32_t responseErrorFlags; /*!< response error flags, need to check the flags when
                                    recieve the cmd response */
} sdif_command_t;

/*! @brief Transfer state */
typedef struct _sdif_transfer
{
    sdif_data_t *data;       /*!< Data to transfer */
    sdif_command_t *command; /*!< Command to send */
} sdif_transfer_t;

/*! @brief Data structure to initialize the sdif */
typedef struct _sdif_config
{
    uint8_t responseTimeout;        /*!< command reponse timeout value */
    uint32_t cardDetDebounce_Clock; /*!< define the debounce clock count which will used in
                                        card detect logic,typical value is 5-25ms */
    uint32_t endianMode;            /*!< define endian mode ,this field is not used in this
                                    module actually, keep for compatible with middleware*/
    uint32_t dataTimeout;           /*!< data timeout value  */
} sdif_config_t;

/*!
 * @brief SDIF capability information.
 * Defines a structure to get the capability information of SDIF.
 */
typedef struct _sdif_capability
{
    uint32_t sdVersion;      /*!< support SD card/sdio version */
    uint32_t mmcVersion;     /*!< support emmc card version */
    uint32_t maxBlockLength; /*!< Maximum block length united as byte */
    uint32_t maxBlockCount;  /*!< Maximum byte count can be transfered */
    uint32_t flags;          /*!< Capability flags to indicate the support information */
} sdif_capability_t;

/*! @brief sdif callback functions. */
typedef struct _sdif_transfer_callback
{
    void (*SDIOInterrupt)(void);     /*!< SDIO card interrupt occurs */
    void (*DMADesUnavailable)(void); /*!< DMA descriptor unavailable */
    void (*CommandReload)(void);     /*!< command buffer full,need re-load */
    void (*TransferComplete)(SDIF_Type *base,
                             void *handle,
                             status_t status,
                             void *userData); /*!< Transfer complete callback */
} sdif_transfer_callback_t;

/*!
 * @brief sdif handle
 *
 * Defines the structure to save the sdif state information and callback function. The detail interrupt status when
 * send command or transfer data can be obtained from interruptFlags field by using mask defined in
 * sdif_interrupt_flag_t;
 * @note All the fields except interruptFlags and transferredWords must be allocated by the user.
 */
typedef struct _sdif_handle
{
    /* Transfer parameter */
    sdif_data_t *volatile data;       /*!< Data to transfer */
    sdif_command_t *volatile command; /*!< Command to send */

    /* Transfer status */
    volatile uint32_t interruptFlags;    /*!< Interrupt flags of last transaction */
    volatile uint32_t dmaInterruptFlags; /*!< DMA interrupt flags of last transaction*/
    volatile uint32_t transferredWords;  /*!< Words transferred by polling way */

    /* Callback functions */
    sdif_transfer_callback_t callback; /*!< Callback function */
    void *userData;                    /*!< Parameter for transfer complete callback */
} sdif_handle_t;

/*! @brief sdif transfer function. */
typedef status_t (*sdif_transfer_function_t)(SDIF_Type *base, sdif_transfer_t *content);

/*! @brief sdif host descriptor */
typedef struct _sdif_host
{
    SDIF_Type *base;                   /*!< sdif peripheral base address */
    uint32_t sourceClock_Hz;           /*!< sdif source clock frequency united in Hz */
    sdif_config_t config;              /*!< sdif configuration */
    sdif_transfer_function_t transfer; /*!< sdif transfer function */
    sdif_capability_t capability;      /*!< sdif capability information */
} sdif_host_t;

/*************************************************************************************************
 * API
 ************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief SDIF module initialization function.
 *
 * Configures the SDIF according to the user configuration.
 * @param base SDIF peripheral base address.
 * @param config SDIF configuration information.
 */
void SDIF_Init(SDIF_Type *base, sdif_config_t *config);

/*!
 * @brief SDIF module deinit function.
 * user should call this function follow with IP reset
 * @param base SDIF peripheral base address.
 */
void SDIF_Deinit(SDIF_Type *base);

/*!
 * @brief SDIF send initialize 80 clocks for SD card after initilize
 * @param base SDIF peripheral base address.
 * @param timeout value
 */
bool SDIF_SendCardActive(SDIF_Type *base, uint32_t timeout);

/*!
 * @brief SDIF module detect card insert status function.
 * @param base SDIF peripheral base address.
 * @param data3 indicate use data3 as card insert detect pin
 * will return the data3 PIN status in this condition
 */
static inline uint32_t SDIF_DetectCardInsert(SDIF_Type *base, bool data3)
{
    if (data3)
    {
        return base->STATUS & SDIF_STATUS_DATA_3_STATUS_MASK;
    }
    else
    {
        return base->CDETECT & SDIF_CDETECT_CARD_DETECT_MASK;
    }
}

/*!
 * @brief SDIF module enable/disable card clock.
 * @param base SDIF peripheral base address.
 * @param enable/disable flag
 */
static inline void SDIF_EnableCardClock(SDIF_Type *base, bool enable)
{
    if (enable)
    {
        base->CLKENA |= SDIF_CLKENA_CCLK_ENABLE_MASK;
    }
    else
    {
        base->CLKENA &= ~SDIF_CLKENA_CCLK_ENABLE_MASK;
    }
}

/*!
 * @brief SDIF module enable/disable module disable the card clock
 * to enter low power mode when card is idle,for SDIF cards, if
 * interrupts must be detected, clock should not be stopped
 * @param base SDIF peripheral base address.
 * @param enable/disable flag
 */
static inline void SDIF_EnableLowPowerMode(SDIF_Type *base, bool enable)
{
    if (enable)
    {
        base->CLKENA |= SDIF_CLKENA_CCLK_LOW_POWER_MASK;
    }
    else
    {
        base->CLKENA &= ~SDIF_CLKENA_CCLK_LOW_POWER_MASK;
    }
}

/*!
 * @brief Sets the card bus clock frequency.
 *
 * @param base SDIF peripheral base address.
 * @param srcClock_Hz SDIF source clock frequency united in Hz.
 * @param target_HZ card bus clock frequency united in Hz.
 * @return The nearest frequency of busClock_Hz configured to SD bus.
 */
uint32_t SDIF_SetCardClock(SDIF_Type *base, uint32_t srcClock_Hz, uint32_t target_HZ);

/*!
 * @brief reset the different block of the interface.
 * @param base SDIF peripheral base address.
 * @param mask indicate which block to reset.
 * @param timeout value,set to wait the bit self clear
 * @return reset result.
 */
bool SDIF_Reset(SDIF_Type *base, uint32_t mask, uint32_t timeout);

/*!
 * @brief enable/disable the card power.
 * once turn power on, software should wait for regulator/switch
 * ramp-up time before trying to initialize card.
 * @param base SDIF peripheral base address.
 * @param enable/disable flag.
 */
static inline void SDIF_EnableCardPower(SDIF_Type *base, bool enable)
{
    if (enable)
    {
        base->PWREN |= SDIF_PWREN_POWER_ENABLE_MASK;
    }
    else
    {
        base->PWREN &= ~SDIF_PWREN_POWER_ENABLE_MASK;
    }
}

/*!
 * @brief get the card write protect status
 * @param base SDIF peripheral base address.
 */
static inline uint32_t SDIF_GetCardWriteProtect(SDIF_Type *base)
{
    return base->WRTPRT & SDIF_WRTPRT_WRITE_PROTECT_MASK;
}

/*!
 * @brief set card data bus width
 * @param base SDIF peripheral base address.
 * @param data bus width type
 */
static inline void SDIF_SetCardBusWidth(SDIF_Type *base, sdif_bus_width_t type)
{
    base->CTYPE = type;
}

/*!
 * @brief toggle state on hardware reset PIN
 * This is used which card has a reset PIN typically.
 * @param base SDIF peripheral base address.
 */
static inline void SDIF_AssertHardwareReset(SDIF_Type *base)
{
    base->RST_N &= ~SDIF_RST_N_CARD_RESET_MASK;
}

/*!
 * @brief send command to the card
 * @param base SDIF peripheral base address.
 * @param command configuration collection
 * @param timeout value
 * @return command excute status
 */
status_t SDIF_SendCommand(SDIF_Type *base, sdif_command_t *cmd, uint32_t timeout);

/*!
 * @brief SDIF enable/disable global interrupt
 * @param base SDIF peripheral base address.
 * @param enable/disable flag
 */
static inline void SDIF_EnableGlobalInterrupt(SDIF_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= SDIF_CTRL_INT_ENABLE_MASK;
    }
    else
    {
        base->CTRL &= ~SDIF_CTRL_INT_ENABLE_MASK;
    }
}

/*!
 * @brief SDIF enable interrupt
 * @param base SDIF peripheral base address.
 * @param interrupt mask
 */
static inline void SDIF_EnableInterrupt(SDIF_Type *base, uint32_t mask)
{
    base->INTMASK |= mask;
}

/*!
 * @brief SDIF disable interrupt
 * @param base SDIF peripheral base address.
 * @param interrupt mask
 */
static inline void SDIF_DisableInterrupt(SDIF_Type *base, uint32_t mask)
{
    base->INTMASK &= ~mask;
}

/*!
 * @brief SDIF get interrupt status
 * @param base SDIF peripheral base address.
 */
static inline uint32_t SDIF_GetInterruptStatus(SDIF_Type *base)
{
    return base->MINTSTS;
}

/*!
 * @brief SDIF clear interrupt status
 * @param base SDIF peripheral base address.
 * @param status mask to clear
 */
static inline void SDIF_ClearInterruptStatus(SDIF_Type *base, uint32_t mask)
{
    base->RINTSTS &= mask;
}

/*!
 * @brief Creates the SDIF handle.
 * register call back function for interrupt and enable the interrupt
 * @param base SDIF peripheral base address.
 * @param handle SDIF handle pointer.
 * @param callback Structure pointer to contain all callback functions.
 * @param userData Callback function parameter.
 */
void SDIF_TransferCreateHandle(SDIF_Type *base,
                               sdif_handle_t *handle,
                               sdif_transfer_callback_t *callback,
                               void *userData);

/*!
 * @brief SDIF enable DMA interrupt
 * @param base SDIF peripheral base address.
 * @param interrupt mask to set
 */
static inline void SDIF_EnableDmaInterrupt(SDIF_Type *base, uint32_t mask)
{
    base->IDINTEN |= mask;
}

/*!
 * @brief SDIF disable DMA interrupt
 * @param base SDIF peripheral base address.
 * @param interrupt mask to clear
 */
static inline void SDIF_DisableDmaInterrupt(SDIF_Type *base, uint32_t mask)
{
    base->IDINTEN &= ~mask;
}

/*!
 * @brief SDIF get internal DMA status
 * @param base SDIF peripheral base address.
 * @return the internal DMA status register
 */
static inline uint32_t SDIF_GetInternalDMAStatus(SDIF_Type *base)
{
    return base->IDSTS;
}

/*!
 * @brief SDIF clear internal DMA status
 * @param base SDIF peripheral base address.
 * @param status mask to clear
 */
static inline void SDIF_ClearInternalDMAStatus(SDIF_Type *base, uint32_t mask)
{
    base->IDSTS &= mask;
}

/*!
 * @brief SDIF internal DMA config function
 * @param base SDIF peripheral base address.
 * @param internal DMA configuration collection
 * @param data buffer pointer
 * @param data buffer size
 */
status_t SDIF_InternalDMAConfig(SDIF_Type *base, sdif_dma_config_t *config, const uint32_t *data, uint32_t dataSize);

/*!
 * @brief SDIF send read wait to SDIF card function
 * @param base SDIF peripheral base address.
 */
static inline void SDIF_SendReadWait(SDIF_Type *base)
{
    base->CTRL |= SDIF_CTRL_READ_WAIT_MASK;
}

/*!
 * @brief SDIF abort the read data when SDIF card is in suspend state
 * Once assert this bit,data state machine will be reset which is waiting for the
 * next blocking data,used in SDIO card suspend sequence,should call after suspend
 * cmd send
 * @param base SDIF peripheral base address.
 * @param timeout value to wait this bit self clear which indicate the data machine
 * reset to idle
 */
bool SDIF_AbortReadData(SDIF_Type *base, uint32_t timeout);

/*!
 * @brief SDIF enable/disable CE-ATA card interrupt
 * this bit should set together with the card register
 * @param base SDIF peripheral base address.
 * @param enable/disable flag
 */
static inline void SDIF_EnableCEATAInterrupt(SDIF_Type *base, bool enable)
{
    if (enable)
    {
        base->CTRL |= SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_MASK;
    }
    else
    {
        base->CTRL &= ~SDIF_CTRL_CEATA_DEVICE_INTERRUPT_STATUS_MASK;
    }
}

/*!
 * @brief SDIF transfer function data/cmd in a non-blocking way
 * this API should be use in interrupt mode, when use this API user
 * must call SDIF_TransferCreateHandle first, all status check through
 * interrupt
 * @param base SDIF peripheral base address.
 * @param sdif handle
 * @param DMA config structure
 *  This parameter can be config as:
 *      1. NULL
            In this condition, polling transfer mode is selected
        2. avaliable DMA config
            In this condition, DMA transfer mode is selected
 * @param sdif transfer configuration collection
 */
status_t SDIF_TransferNonBlocking(SDIF_Type *base,
                                  sdif_handle_t *handle,
                                  sdif_dma_config_t *dmaConfig,
                                  sdif_transfer_t *transfer);

/*!
 * @brief SDIF transfer function data/cmd in a blocking way
 * @param base SDIF peripheral base address.
 * @param DMA config structure
 *       1. NULL
 *           In this condition, polling transfer mode is selected
 *       2. avaliable DMA config
 *           In this condition, DMA transfer mode is selected
 * @param sdif transfer configuration collection
 */
status_t SDIF_TransferBlocking(SDIF_Type *base, sdif_dma_config_t *dmaConfig, sdif_transfer_t *transfer);

/*!
 * @brief SDIF release the DMA descriptor to DMA engine
 * this function should be called when DMA descriptor unavailable status occurs
 * @param base SDIF peripheral base address.
 * @param sdif DMA config pointer
 */
status_t SDIF_ReleaseDMADescriptor(SDIF_Type *base, sdif_dma_config_t *dmaConfig);

/*!
 * @brief SDIF return the controller capability
 * @param base SDIF peripheral base address.
 * @param sdif capability pointer
 */
void SDIF_GetCapability(SDIF_Type *base, sdif_capability_t *capability);

/*!
 * @brief SDIF return the controller status
 * @param base SDIF peripheral base address.
 */
static inline uint32_t SDIF_GetControllerStatus(SDIF_Type *base)
{
    return base->STATUS;
}

/*!
 * @brief SDIF send command  complete signal disable to CE-ATA card
 * @param base SDIF peripheral base address.
 * @param send auto stop flag
 */
static inline void SDIF_SendCCSD(SDIF_Type *base, bool withAutoStop)
{
    if (withAutoStop)
    {
        base->CTRL |= SDIF_CTRL_SEND_CCSD_MASK | SDIF_CTRL_SEND_AUTO_STOP_CCSD_MASK;
    }
    else
    {
        base->CTRL |= SDIF_CTRL_SEND_CCSD_MASK;
    }
}

/*!
 * @brief SDIF config the clock delay
 * This function is used to config the cclk_in delay to
 * sample and drvive the data ,should meet the min setup
 * time and hold time, and user need to config this paramter
 * according to your board setting
 * @param target freq work mode
 * @param clock divider which is used to decide if use pharse shift for delay
 */
void SDIF_ConfigClockDelay(uint32_t target_HZ, uint32_t divider);

/* @} */

#if defined(__cplusplus)
}
#endif
/*! @} */

#endif /* _FSL_sdif_H_*/
