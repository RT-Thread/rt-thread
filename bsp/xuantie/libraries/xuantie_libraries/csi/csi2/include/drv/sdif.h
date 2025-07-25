 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv/sdif.h
 * @brief    Header File for SDIF Driver
 * @version  V1.0
 * @date     28. June 2020
 * @model    sdif
 ******************************************************************************/
#ifndef _DRV_SDIF_H_
#define _DRV_SDIF_H_

#include <stdbool.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *sdif_handle_t;

/*! @brief Construct a status code value from a group and code number. */
#define MAKE_STATUS(group, code) ((((group)*100) + (code)))

/*! @brief Status group numbers. */
enum _status_groups {
    kStatusGroup_Generic = 0,                 /*!< Group number for generic status codes. */
    kStatusGroup_SDMMC = 18,                  /*!< Group number for SDMMC status code */
    kStatusGroup_SDIF = 59,                   /*!< Group number for SDIF status codes.*/
    kStatusGroup_ApplicationRangeStart = 101, /*!< Starting number for application groups. */
};

/*! @brief Generic status return codes. */
enum _generic_status {
    kStatus_Success = MAKE_STATUS(kStatusGroup_Generic, 0),
    kStatus_Fail = MAKE_STATUS(kStatusGroup_Generic, 1),
    kStatus_ReadOnly = MAKE_STATUS(kStatusGroup_Generic, 2),
    kStatus_OutOfRange = MAKE_STATUS(kStatusGroup_Generic, 3),
    kStatus_InvalidArgument = MAKE_STATUS(kStatusGroup_Generic, 4),
    kStatus_Timeout = MAKE_STATUS(kStatusGroup_Generic, 5),
    kStatus_NoTransferInProgress = MAKE_STATUS(kStatusGroup_Generic, 6),
};

/*! @brief SDIF status */
enum _sdif_status {
    kStatus_SDIF_DescriptorBufferLenError = MAKE_STATUS(kStatusGroup_SDIF, 0U), /*!< Set DMA descriptor failed */
    kStatus_SDIF_InvalidArgument = MAKE_STATUS(kStatusGroup_SDIF, 1U),          /*!< invalid argument status */
    kStatus_SDIF_SyncCmdTimeout = MAKE_STATUS(kStatusGroup_SDIF, 2U), /*!< sync command to CIU timeout status */
    kStatus_SDIF_SendCmdFail = MAKE_STATUS(kStatusGroup_SDIF, 3U),    /*!< send command to card fail */
    kStatus_SDIF_SendCmdErrorBufferFull =
        MAKE_STATUS(kStatusGroup_SDIF, 4U), /*!< send command to card fail, due to command buffer full
                                     user need to resend this command */
    kStatus_SDIF_DMATransferFailWithFBE =
        MAKE_STATUS(kStatusGroup_SDIF, 5U), /*!< DMA transfer data fail with fatal bus error ,
                                     to do with this error :issue a hard reset/controller reset*/
    kStatus_SDIF_DMATransferDescriptorUnavailable =
        MAKE_STATUS(kStatusGroup_SDIF, 6U),                             /*!< DMA descriptor unavailable */
    kStatus_SDIF_DataTransferFail = MAKE_STATUS(kStatusGroup_SDIF, 6U), /*!< transfer data fail */
    kStatus_SDIF_ResponseError = MAKE_STATUS(kStatusGroup_SDIF, 7U),    /*!< response error */
    kStatus_SDIF_DMAAddrNotAlign = MAKE_STATUS(kStatusGroup_SDIF, 8U),  /*!< DMA address not align */
};

/*! @brief Type used for all status and error return values. */
typedef int32_t status_t;

/*! @brief Computes the number of elements in an array. */
#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

/*! Macro to change a value to a given size aligned value */
#define SDK_SIZEALIGN(var, alignbytes) \
    ((unsigned int)((var) + ((alignbytes)-1)) & (unsigned int)(~(unsigned int)((alignbytes)-1)))

///< #define assert(__e) ((void)0)
/*! @name Min/max macros */
#if !defined(MIN)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#if !defined(MAX)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#define SDK_ALIGN(var, alignbytes) var

static inline unsigned long cpu_to_dma(unsigned long addr)
{
    return addr;
}

static inline unsigned long *ptr_cpu_to_dma(unsigned long *addr)
{
    return (unsigned long *)cpu_to_dma((unsigned long)addr);
}

typedef enum {
    SDIF_ERROR_CMD_CRC_FAIL  = (1),      ///< Command response received (but CRC check failed)
    SDIF_ERROR_DATA_CRC_FAIL,                                 ///< Data block sent/received (CRC check failed)
    SDIF_ERROR_CMD_RSP_TIMEOUT,                               ///< Command response timeout
    SDIF_ERROR_DATA_TIMEOUT,                                  ///< Data timeout
    SDIF_ERROR_TX_UNDERRUN,                                   ///< Transmit FIFO underrun
    SDIF_ERROR_RX_OVERRUN,                                    ///< Receive FIFO overrun
    SDIF_ERROR_ADDR_MISALIGNED,                               ///< Misaligned address
    SDIF_ERROR_BLOCK_LEN_ERR,                                 ///< Transferred block length is not allowed for the card or the number of transferred bytes does not match the block length
    SDIF_ERROR_ERASE_SEQ_ERR,                                 ///< An error in the sequence of erase command occurs
    SDIF_ERROR_BAD_ERASE_PARAM,                               ///< An invalid selection for erase groups
    SDIF_ERROR_WRITE_PROT_VIOLATION,                          ///< Attempt to program a write protect block
    SDIF_ERROR_LOCK_UNLOCK_FAILED,                            ///< Sequence or password error has been detected in unlock command or if there was an attempt to access a locked card
    SDIF_ERROR_COM_CRC_FAILED,                                ///< CRC check of the previous command failed
    SDIF_ERROR_ILLEGAL_CMD,                                   ///< Command is not legal for the card state
    SDIF_ERROR_CARD_ECC_FAILED,                               ///< Card internal ECC was applied but failed to correct the data
    SDIF_ERROR_CC_ERR,                                        ///< Internal card controller error
    SDIF_ERROR_GENERAL_UNKNOWN_ERR,                           ///< General or unknown error
    SDIF_ERROR_STREAM_READ_UNDERRUN,                          ///< The card could not sustain data reading in stream rmode
    SDIF_ERROR_STREAM_WRITE_OVERRUN,                          ///< The card could not sustain data programming in stream mode
    SDIF_ERROR_CID_CSD_OVERWRITE,                             ///< CID/CSD overwrite error
    SDIF_ERROR_WP_ERASE_SKIP,                                 ///< Only partial address space was erased
    SDIF_ERROR_CARD_ECC_DISABLED,                             ///< Command has been executed without using internal ECC
    SDIF_ERROR_ERASE_RESET,                                   ///< Erase sequence was cleared before executing because an out
    SDIF_ERROR_AKE_SEQ_ERR,                                   ///< Error in sequence of authentication
    SDIF_ERROR_INVALID_VOLTRANGE,                             ///< Error in case of invalid voltage range
    SDIF_ERROR_ADDR_OUT_OF_RANGE,                             ///< Error when addressed block is out of range
    SDIF_ERROR_REQUEST_NOT_APPLICABLE,                        ///< Error when command request is not applicable
    SDIF_ERROR_UNSUPPORTED_FEATURE,                           ///< Error when feature is not insupported
} sdif_error_e;

/*  Host controller capabilities flag mask */
typedef enum {
    SDIF_SUPPORT_HIGH_SPEED     = 0x1U,         ///< Support high-speed
    SDIF_SUPPORT_DMA_SPEED      = 0x2U,         ///< Support DMA
    SDIF_SUPPORT_USPEND_RESUME  = 0x4U,         ///< Support suspend/resume
    SDIF_SUPPORT_V330           = 0x8U,         ///< Support voltage 3.3V
    SDIF_SUPPORT_4BIT           = 0x10U,        ///< Support 4 bit mode
    SDIF_SUPPORT_8BIT           = 0x20U,        ///< Support 8 bit mode
} sdif_capability_flag_e;

/* \brief define the internal DMA mode */
typedef enum {
    SDIF_CHAIN_DMA_MODE = 0x01U, ///< one descriptor with one buffer,but one descriptor point to another
    SDIF_DUAL_DMA_MODE  = 0x02U,  ///< dual mode is one descriptor with two buffer
} sdif_dma_mode_e;

/* The command type */
typedef enum {
    SDIF_CARD_COMMAND_NORMAL    = 0U, ///< Normal command
    SDIF_CARD_COMMAND_SUSPEND   = 1U, ///< Suspend command
    SDIF_CARD_COMMAND_RESUME    = 2U, ///< Resume command
    SDIF_CARD_COMMAND_ABORT     = 3U, ///< Abort command
} sdif_card_command_type_e;

/* The command response type */
typedef enum {
    SDIF_CARD_RESPONSE_NONE = 0U, ///< Response type: none
    SDIF_CARD_RESPONSE_R1   = 1U, ///< Response type: R1
    SDIF_CARD_RESPONSE_R1b  = 2U, ///< Response type: R1b
    SDIF_CARD_RESPONSE_R2   = 3U, ///< Response type: R2
    SDIF_CARD_RESPONSE_R3   = 4U, ///< Response type: R3
    SDIF_CARD_RESPONSE_R4   = 5U, ///< Response type: R4
    SDIF_CARD_RESPONSE_R5   = 6U, ///< Response type: R5
    SDIF_CARD_RESPONSE_R5b  = 7U, ///< Response type: R5b
    SDIF_CARD_RESPONSE_R6   = 8U, ///< Response type: R6
    SDIF_CARD_RESPONSE_R7   = 9U, ///< Response type: R7
} sdif_card_response_type_e;

/* \brief define the card bus width type */
typedef enum {
    SDIF_BUS_1BIT_WIDTH = 0U,  ///< 1bit bus width, 1bit mode and 4bit mode share one register bit
    SDIF_BUS_4BIT_WIDTH = 1U,  ///< 4bit mode mask
    SDIF_BUS_8BIT_WIDTH = 2U,  ///< support 8 bit mode
} sdif_bus_width_e;

/* \brief Defines the internal DMA configure structure. */
typedef struct {
    bool            enable_fix_burst_len;           ///< fix burst len enable/disable flag,When set, the AHB will
    ///<  use only SINGLE, INCR4, INCR8 or INCR16 during start of
    ///<  normal burst transfers. When reset, the AHB will use SINGLE
    ///<  and INCR burst transfer operations

    sdif_dma_mode_e mode;                           ///< define the DMA mode */


    uint32_t        *dma_des_buffer_start_addr;     ///< internal DMA descriptor start address
    uint32_t        dma_des_buffer_len;             ///<  internal DMA buffer descriptor buffer len ,user need to pay attention to the
    ///<  dma descriptor buffer length if it is bigger enough for your transfer
    uint8_t         dma_dws_skip_len;               ///< define the descriptor skip length ,the length between two descriptor
    ///<  this field is special for dual DMA mode
} sdif_dma_config_t;

/* \brief sdif callback functions. */
typedef struct {
    void (*card_inserted)(uint32_t idx, void *user_data);      ///< card insert call back
    void (*card_removed)(uint32_t idx, void *user_data);       ///< card remove call back
    void (*sdif_interrupt)(uint32_t idx, void *user_data);     ///< SDIF card interrupt occurs
    void (*dma_des_unavailable)(uint32_t idx, void *user_data);///< DMA descriptor unavailable
    void (*command_reload)(uint32_t idx, void *user_data);     ///< command buffer full,need re-load
    void (*transfer_complete)(uint32_t idx,
                              void *state,
                              int32_t status,
                              void *user_data); ///<Transfer complete callback
} sdif_callback_t;

/* Card data descriptor */
typedef struct {
    bool            stream_transfer;           ///< indicate this is a stream data transfer command
    bool            enable_auto_command12;     ///< indicate if auto stop will send when data transfer over
    bool            enable_ignore_error;       ///< indicate if enable ignore error when transfer data

    uint32_t        block_size;                ///< Block size, take care when configure this parameter
    uint32_t        block_count;               ///< Block count
    uint32_t        *rx_date_buffer;           ///< data buffer to receive
    const uint32_t  *tx_data_buffer;           ///< data buffer to transfer
} sdif_data_t;

/* Card command descriptor */
typedef struct {
    uint32_t index;                     ///< Command index
    uint32_t argument;                  ///< Command argument
    uint32_t response[4U];              ///< Response for this command
    uint32_t type;                      ///< define the command type
    uint32_t response_type;             ///< Command response type
    uint32_t flags;                     ///< Cmd flags
    uint32_t resopnse_error_flags;      ///< response error flags, need to check the flags when receive the cmd response
} sdif_command_t;
/* Transfer state */
typedef struct {
    sdif_data_t *data;          ///< Data to transfer
    sdif_command_t *command;    ///< Command to send
} sdif_transfer_t;

/* Data structure to initialize the sdif */
typedef struct {
    uint8_t  response_timeout;        ///< command response timeout value
    uint32_t card_det_debounce_clock; ///< define the debounce clock count which will used in
    ///  card detect logic,typical value is 5-25ms
    uint32_t endian_mode;             ///< define endian mode ,this field is not used in this
    ///  module actually, keep for compatible with middleware
    uint32_t data_timeout;            ///< data timeout value
} sdif_config_t;

/*
 * \brief SDIF capability information.
 * Defines a structure to get the capability information of SDIF.
 */
typedef struct {
    uint32_t sd_version;       ///< support SD card/SDIF version
    uint32_t mmc_version;      ///< support emmc card version
    uint32_t max_block_length; ///< Maximum block length united as byte
    uint32_t max_block_count;  ///< Maximum byte count can be transfered
    uint32_t flags;            ///< Capability flags to indicate the support information
} sdif_capability_t;

/**
  \brief  Initializes the SDIF according to the specified
  \param[in]   idx SDIF index
  \param[in]   callback Callback Structure pointer to contain all callback functions.
  \param[in]   user_data User_data Callback function parameter.
  \return sdif Handle if success
*/
sdif_handle_t csi_sdif_initialize(uint32_t idx, sdif_callback_t *callback, void *user_data);

/**
  \brief       De-initialize SD Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  SDIF handle to operate.
*/
void csi_sdif_uninitialize(uint32_t idx, sdif_handle_t handle);

/**
  \brief  Initializes the SDIF config
  \param[in]   idx SDIF index
  \param[in]   config  SDIF config descriptor \ref sdif_config_t
*/
void csi_sdif_config(sdif_handle_t handle, sdif_config_t *config);

/**
  \brief       Get driver capabilities.
  \param[in]   handle  SDIF handle to operate.
  \param[out]  capability SDIF capability information \ref sdif_capabilities_t
 */
void csi_sdif_get_capabilities(sdif_handle_t handle, sdif_capability_t *capability);


/**
  \brief   send command to the card
  \param[in]  handle  SDIF handle to operate.
  \param[in]  cmd command configuration collection
  \param[in]  retries total number of tries
  \return  Error code
 */
int32_t csi_sdif_send_command(sdif_handle_t handle, sdif_command_t *cmd, uint32_t retries);

/**
  \brief  SDIF transfer function data/cmd in a non-blocking way
      this API should be use in interrupt mode, when use this API user
      must call csi_sdif_create_state first, all status check through
      interrupt
  \param[in] handle  SDIF handle to operate.
  \param[in] dma_config DMA config structure \ref sdif_dma_config_t
        This parameter can be config as:
        1. NULL
            In this condition, polling transfer mode is selected
        2. avaliable DMA config
            In this condition, DMA transfer mode is selected
  \param[in] transfer  SDIF transfer configuration collection. \ref sdif_transfer_t
  \return Error code
  */
int32_t csi_sdif_transfer(sdif_handle_t handle, sdif_dma_config_t *dma_config, sdif_transfer_t *transfer);

/**
 \brief    Poll-wait for the response to the last command to be ready.  This
   function should be called even after sending commands that have no
   response (such as CMD0) to make sure that the hardware is ready to
   receive the next command.
 \param[in]  handle  SDIF handle to operate.
 \param[in]  cmd : The command that was sent.  See 32-bit command definitions above.
*/
void csi_sdif_transfer_abort(sdif_handle_t handle);

/**
 \brief Called after change in Bus width has been selected (via ACMD6).  Most
    controllers will need to perform some special operations to work
    correctly in the new bus mode.
 \param[in]  handle  SDIF handle to operate.
 \param[in]  bus_width Wide bus mode \ref sdif_bus_width_e.
*/
void csi_sdif_bus_width(sdif_handle_t handle, sdif_bus_width_e bus_width);

/**
 \brief Set SDIF clocking
 \param[in]  Handle  SDIF handle to operate.
 \param[in]  Target_hz card bus clock frequency united in Hz.
 \return  Error code
*/
uint32_t csi_sdif_set_clock(sdif_handle_t handle, uint32_t target_hz);

/**
  \brief  Get sdif handle
  \param[in]   Idx sdif index
  \return      SDIF handle
*/
sdif_handle_t csi_sdif_get_handle(uint32_t idx);

/**
  \brief  Get sdif index
  \param[out]   Handle  SDIF handle to operate.
  \return       SDIF index
*/
uint32_t csi_sdif_get_idx(sdif_handle_t handle);

/**
  \brief       SDIF return the controller status
  \param[in]   handle  SDIF handle to operate.
 */
uint32_t csi_sdif_get_controller_status(sdif_handle_t handle);

/**
 \brief SDIF send initialize 80 clocks for SD card after initial
 \param[in]  handle  SDIF handle to operate.
 \param[in]  timeout  millisecond
 */
bool csi_sdif_send_card_active(sdif_handle_t handle, uint32_t timeout);

/**
 \brief SDIF module enable/disable card clock.
 \param[in]  handle  SDIF handle to operate.
 \param[in]  enable  enable:true, disable:false
 */
void csi_sdif_enable_card_clock(sdif_handle_t handle, bool enable);

/**
 \brief SDIF enable interrupt
 \param[in]  handle  SDIF handle to operate.
 \param[in]  mask interrupt mask
 */
void csi_sdif_enable_interrupt(sdif_handle_t handle, uint32_t mask);

/**
 \brief SDIF disable interrupt
 \param[in]  handle  SDIF handle to operate.
 \param[in]  mask interrupt mask
 */
void csi_sdif_disable_interrupt(sdif_handle_t handle, uint32_t mask);

/**
 \brief SDIF enable card detect interrupt
 \param[in]  handle  SDIF handle to operate.
 */
void csi_sdif_enable_card_detect_interrupt(sdif_handle_t handle);

/**
 \brief SDIF enable sdio interrupt
 \param[in]  handle  SDIF handle to operate.
 */
void csi_sdif_enable_sdio_interrupt(sdif_handle_t handle);

/**
 \brief SDIF disable sdio interrupt
 \param[in]  handle  SDIF handle to operate.
 */
void csi_sdif_disable_sdio_interrupt(sdif_handle_t handle);

/**
 \brief SDIF module detect card insert status function.
 \param[in]  handle  SDIF handle to operate.
 \param[in]  data3 indicate use data3 as card insert detect pin
 \return 1 card is inserted
 *       0 card is removed
 */
uint32_t csi_sdif_detect_card_insert(sdif_handle_t handle, bool data3);

/**
 \brief enable/disable the card power.
 * once turn power on, software should wait for regulator/switch
 * ramp-up time before trying to initialize card.
 \param[in]  handle  SDIF handle to operate.
 \param[in]  enable  enable:true, disable:false
 */
void csi_sdif_enable_card_power(sdif_handle_t handle, bool enable);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_SDIF_H_  */

