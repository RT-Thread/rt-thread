/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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


#ifndef __FSL_QSPI_DRIVER_H__
#define __FSL_QSPI_DRIVER_H__

#include <stdbool.h>
#include "fsl_qspi_hal.h"
#include "fsl_edma_driver.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_QuadSPIO_COUNT

/*!
 * @addtogroup qspi_driver
 * @{ 
 */

/*! @file */
extern QuadSPI_Type * const g_qspiBase[QuadSPI_INSTANCE_COUNT];
extern const IRQn_Type g_qspiIrqId[QuadSPI_INSTANCE_COUNT];

/*! @brief QSPI runtime state structure. */
typedef struct QspiState
{
    uint32_t *txAddr;
    uint32_t *rxAddr;
    uint32_t txSize;
    uint32_t rxSize;
    uint32_t txFinishedBytes;
    uint32_t rxFinishedBytes;
    uint8_t txWatermark;
    uint8_t rxWatermark;
    bool isTxBusy;
    bool isRxBusy;
    bool txUseDma;
    bool rxUseDma;
    edma_chn_state_t txEdmaChn;
    edma_chn_state_t rxEdmaChn;
    edma_software_tcd_t txEdmaTCD[2];
    edma_software_tcd_t rxEdmaTCD[2];
    dma_request_source_t txSource;
    dma_request_source_t rxSource;
    uint32_t err;
} qspi_state_t;

/*! @brief Status structure of QSPI.*/
typedef enum _qspi_status
{
    kStatus_QSPI_Success = 0U,
    kStatus_QSPI_Fail = 1U,
    kStatus_QSPI_DeviceBusy = 2U
} qspi_status_t;

/*! @brief Serial Flash command ID for the QSPI engine. */
typedef enum _qspi_flash_command
{
    kQspiFlashCommandStop = 0x0U,
    kQspiFlashCommandCmd = 0x400U,
    kQspiFlashCommandAddr = 0x800U,
    kQspiFlashCommandDummy = 0xC00U,
    kQspiFlashCommandMode = 0x1000U,
    kQspiFlashCommandMode2 = 0x1400U,
    kQspiFlashCommandMode4 = 0x1800U,
    kQspiFlashCommandRead = 0x1C00U,
    kQspiFlashCommandWrite = 0x2000U,
    kQspiFlashCommandJmpOnCS = 0x2400U,
    kQspiFlashCommandAddrDDR = 0x2800U,
    kQspiFlashCommandModeDDR = 0x2C00U,
    kQspiFlashCommandMode2DDR = 0x3000U,
    kQspiFlashCommandMode4DDR = 0x3400U,
    kQspiFlashCommandReadDDR = 0x3800U,
    kQspiFlashCommandWriteDDR = 0x3C00U,
    kQspiFlashCommandDataLearn = 0x4000U,
    kQspiFlashCommandCmdDDR = 0x4400U,
    kQspiFlashCommandCaddr = 0x4800U,
    kQspiFlashCommandCaddrDDR = 0x4C00U
} qspi_flash_command_t;

/*! @brief QSPI command pad type */
typedef enum _qspi_pad_type
{
    kQspiPad1 = 0x0,
    kQspiPad2 = 0x100U,
    kQspiPad4 = 0x200U,
    kQspiPad8 = 0x300U
} qspi_pad_type_t;

/*! @brief QSPI command Mode type */
typedef enum _qspi_command_mode
{
    kQspiCommandModeDefault = 0U,
    kQspiCommandMode2 = 1U,
    kQspiCommandMode4 = 2U
} qspi_command_mode_t;

/*! @brief QSPI flash command structure*/
typedef struct QspiLUTCommand
{
    uint32_t addr; /*!< Address used in the serial flash command.*/
    uint8_t cmd; /*!< Serial flash command number.*/
    uint8_t param; /*!< Parameter used in the serial flash command. */
    uint8_t LUTIndex; /*!< Location of the command in the look up table. */
    uint8_t dummy_cycle;/*!< Dummy cycle number of the instruction. */
    uint8_t dummy_index; /*!< Dummy instruction index. */
    qspi_pad_type_t padType; /*!< 1 pad,  4 pad or 8 pad*/
    qspi_flash_command_t commandType; /*!< command type */
} qspi_lut_command_t;

/*! @brief QSPI configuration structure*/
typedef struct QspiConfig
{
    clock_qspi_src_t clockSrc; /*!< Clock source of QSPI module */
    uint32_t sclk; /*!< Serial flash clock frequency, which should be smaller than the QSPI source clock. */
    uint8_t txWatermark; /*!< QSPI transmit watermark value */
    uint8_t rxWatermark; /*!< QSPI receive watermark value. */
    uint32_t AHBbufferSize[FSL_FEATURE_QSPI_AHB_BUFFER_COUNT]; /*!< AHB buffer size. */
    uint8_t AHBbufferMaster[FSL_FEATURE_QSPI_AHB_BUFFER_COUNT]; /*!< AHB buffer master.  */
    bool AHBbuffer3AllMaster; /*!< Is AHB buffer3 for all master.*/
    dma_request_source_t txSource; /*!< DMA request source for QSPI transmit.*/
    dma_request_source_t rxSource; /*!< DMA request source for QSPI receive. */
} qspi_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/******************************************************************************
 * API
 *****************************************************************************/

/*! @brief Initializes the QSPI module and internal state.
 *
 * This function initializes the internal state in QSPI PD and calls the HAL API to
 * initialize the QSPI module.
 * @param instance QSPI module instance.
 * @param state State structure used by QSPI PD. Users MUST allocate the space for
 * QSPI and the memory should NOT be freed until the QSPI is deinitialized.
 */
qspi_status_t QSPI_DRV_Init(uint32_t instance, qspi_state_t *state);

/*! @brief Deinitializes the QSPI module.
 *
 * Clears the QSPI state and  QSPI module registers.
 * @param instance QSPI module instance.
 */
qspi_status_t QSPI_DRV_Deinit(uint32_t instance);

/*! @brief Configures the QSPI features. 
 *
 * The configuration of QSPI includes configuration of the QSPI module and the configuration
 * of the serial flash connected to the QSPI. This function configures the parameters for
 * QSPI only, not the serial flash.
 * @param instance QSPI module instance.
 * @param config Config structure for QSPI module.
 */
qspi_status_t QSPI_DRV_ConfigQspi(uint32_t instance, qspi_config_t * config);

/*! @brief Configures the QSPI clock source. 
 *
 * @param instance QSPI module instance.
 * @param clkSrc QSPI clock source.
 */
static inline void QSPI_DRV_ConfigClockSrc(uint32_t instance, uint32_t clkSrc)
{
    QSPI_HAL_SetClockSrc(g_qspiBase[instance],clkSrc);
}

/*! @brief Gets  default settings for QSPI.
 *
 * QSPI works with default settings.
 * This function provides the default parameters for the QSPI configuration.
 * @param config QSPI configuration structure.
 */
void QSPI_DRV_GetDefaultQspiConfig(qspi_config_t * config);

/*! @brief Configures the serial flash parameter.
 *
 * This function configures the serial flash relevant parameters, such as the size, command, and so on.
 * @param instance QSPI module instance.
 * @param flashConfig Flash configuration parameters.
 */
static inline void QSPI_DRV_ConfigFlash(uint32_t instance, qspi_flash_config_t *flashConfig)
{
    QSPI_HAL_ConfigFlash(g_qspiBase[instance], flashConfig);
}

/*! @brief Sets the IP command address.
 *
 * @param instance QSPI module instance.
 * @param addr IP command address.
 */
static inline void QSPI_DRV_SetIPCommandAddr(uint32_t instance, uint32_t addr)
{
    QSPI_HAL_SetIPCommandAddr(g_qspiBase[instance], addr);
}

/*! @brief Sets the IP command size.
 *
 * @param instance QSPI module instance.
 * @param size IP command size.
 */
static inline void QSPI_DRV_SetIPCommandSize(uint32_t instance, uint32_t size)
{
    QSPI_HAL_SetIPCommandSize(g_qspiBase[instance], size);
}

/*! @brief Writes data to the QSPI transmit buffer.
 *
 * This function writes a continuous data to the QSPI transmit FIFO. This function is a block function and  can return only when
 * finished. This function uses polling methods.
 * @param instance QSPI module instance.
 * @param addr Start address of source data.
 * @param size Data length in bytes to be transferred.
 */
static inline void QSPI_DRV_WriteDataBlocking(uint32_t instance, uint32_t * addr, uint32_t size)
{
    QSPI_HAL_WriteDataBlocking(g_qspiBase[instance], addr, size);
}

/*! @brief Writes data to the QSPI transmit buffer using interrupts.
 *
 * This function writes data to the QSPI transmit FIFO. This function is non-blocking.
 * @param instance QSPI module instance.
 * @param addr Start address of source data.
 * @param size Data length in bytes to be transferred.
 */
qspi_status_t QSPI_DRV_WriteDataInt(uint32_t instance, uint32_t *addr, uint32_t size);

/*! @brief Writes data to the QSPI transmit buffer using the DMA method.
 *
 * This function writes data to the QSPI transmit FIFO. This function is non-blocking.
 * @param instance QSPI module instance.
 * @param addr Start address of source data.
 * @param size Data length in bytes to be transferred.
 */
qspi_status_t QSPI_DRV_WriteDataEdma(uint32_t instance, uint32_t *addr, uint32_t size);

/*! @brief Reads data from the QSPI receive buffer.
 *
 * This function reads continuous data from the QSPI receive buffer/FIFO. This function is a blocking function and can return only when
 * finished. This function uses polling methods.
 * @param instance QSPI module instance.
 * @param addr Destination address to put data.
 * @param size Data length in bytes to be read.
 */
static inline void QSPI_DRV_ReadDataBlocking(uint32_t instance, uint32_t *addr, uint32_t size)
{
    QSPI_HAL_ReadDataBlocking(g_qspiBase[instance], addr, size);
}

/*! @brief Reads data from the QSPI receive buffer using interrupts.
 *
 * To find out the transfer state, call QSPI_DRV_GetRxState function. If the return value is kStatus_QSPI_Success,
 * the read is finished.
 * @param instance QSPI module instance.
 * @param addr Destination address to put data.
 * @param size Data length in bytes to be read.
 */
void QSPI_DRV_ReadDataInt(uint32_t instance, uint32_t *addr, uint32_t size);

/*! @brief Reads data from the QSPI receive buffer using the DMA method.
 *
 * To find out the transfer state, call QSPI_DRV_GetRxState function. If the return value is kStatus_QSPI_Success,
 * the read is finished.
 * @param instance QSPI module instance.
 * @param addr Destination address to put data.
 * @param size Data length in bytes to be read.
 */
void QSPI_DRV_ReadDataEdma(uint32_t instance, uint32_t * addr, uint32_t size);

/*! @brief Gets the state value of QSPI.
 *
 * This function returns the status flag in the QSPI_SR register according to the input status bit and gets
 * single or multiple status value.
 * @param instance QSPI module instance.
 * @param status Element of qspi_state_bit_t, it can be one or multiple.
 * @return State bit value.
 */
static inline  uint32_t QSPI_DRV_GetQspiStatus(uint32_t instance, uint32_t status)
{
    return QSPI_HAL_GetState(g_qspiBase[instance], status);
}

/*! @brief Clears the QSPI state flags.
 *
 * @param instance QSPI module instance.
 * @param flag Which kind of QSPI flags to be cleared.
 */
static inline void QSPI_DRV_ClearFlag(uint32_t instance, uint32_t flag)
{
    QSPI_HAL_ClearStateFlag(g_qspiBase[instance], flag);
}

/*! @brief Clears the QSPI FIFO logic.
 *
 * @param instance QSPI module instance.
 * @param flag Which kind of QSPI FIFO to be cleared.
 */
 static inline void QSPI_DRV_ClearFifo(uint32_t instance, qspi_fifo_t fifo)
{
    QSPI_HAL_ClearFifo(g_qspiBase[instance], fifo);
}

/*! @brief Software reset for the QSPI logic.
 *
 * @param instance QSPI module instance.
 */
 static inline void QSPI_DRV_SoftwareReset(uint32_t instance)
{
    QSPI_HAL_SoftwareReset(g_qspiBase[instance]);
}

/*! @brief Gets the status of the transmit transfer.
 *
 * @param instance QSPI module instance.
 * @return If kStatus_QSPI_Success is returned, the transfer is finished.
 */
qspi_status_t QSPI_DRV_GetTxStatus(uint32_t instance);

/*! @brief Gets the status of the receive transfer.
 *
 * @param instance QSPI module instance.
 * @return If kStatus_QSPI_Success is returned, transfer is finished.
 */
qspi_status_t QSPI_DRV_GetRxStatus(uint32_t instance);

/*! @brief Updates the LUT table.
*
* @param instance QSPI module instance.
* @param index Which LUT index needs to be located. It should be an integer divided by 4.
* @param cmd Command sequence array.
*/
void QSPI_DRV_UpdateLUT(uint32_t instance, uint32_t index, uint32_t *cmd);

/*! @brief Executes the IP serial flash command.
*
* @param instance QSPI module instance.
* @param index Which LUT index needs to be located. It should be an integer divided by 4.
*/
void QSPI_DRV_ExecuteFlashCommand(uint32_t instance, uint32_t index);

/*! @brief Executes the buffer serial flash command.
*
* @param instance QSPI module instance.
* @param index Which LUT index needs to be located. It should be an integer divided by 4.
*/
void QSPI_DRV_ExecuteBufferCommand(uint32_t instance, uint32_t index);

/*! @brief Transfers the interrupt handler.
*
* This handler transfers data and also clears an error flag.
* @param instance QSPI module instance.
*/
void QSPI_DRV_TxIrqHandler(uint32_t instance);

/*! @brief Receives the interrupt handler.
*
* This handler receives data and also clears an error flag.
* @param instance QSPI module instance.
*/
void QSPI_DRV_RxIrqHandler(uint32_t instance);


#if defined(__cplusplus)
}
#endif

/*!
 *@}
 */
#endif
#endif /* __FSL_QSPI_DRIVER_H__ */

