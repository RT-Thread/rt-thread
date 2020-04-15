//*****************************************************************************
//
//  am_hal_iom.h
//! @file
//!
//! @brief Functions for accessing and configuring the IO Master module
//!
//! @addtogroup iom2 IO Master (SPI/I2C)
//! @ingroup apollo2hal
//! @{

//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#ifndef AM_HAL_IOM_H
#define AM_HAL_IOM_H

//*****************************************************************************
//
// Macro definitions
//
//*****************************************************************************

//*****************************************************************************
//
//! @name IOM Clock Frequencies
//! @brief Macro definitions for common SPI and I2C clock frequencies.
//!
//! These macros may be used with the ui32ClockFrequency member of the
//! am_hal_iom_config_t structure to set the clock frequency of the serial
//! interfaces.
//!
//! This list of frequencies is not exhaustive by any means. If your desired
//! frequency is not in this list, simply set ui32ClockFrequency to the
//! desired frequency (in Hz) when calling am_hal_iom_config().
//
//*****************************************************************************
#define AM_HAL_IOM_24MHZ    24000000
#define AM_HAL_IOM_16MHZ    16000000
#define AM_HAL_IOM_12MHZ    12000000
#define AM_HAL_IOM_8MHZ      8000000
#define AM_HAL_IOM_6MHZ      6000000
#define AM_HAL_IOM_4MHZ      4000000
#define AM_HAL_IOM_3MHZ      3000000
#define AM_HAL_IOM_2MHZ      2000000
#define AM_HAL_IOM_1_5MHZ    1500000
#define AM_HAL_IOM_1MHZ      1000000
#define AM_HAL_IOM_800KHZ     800000
#define AM_HAL_IOM_750KHZ     750000
#define AM_HAL_IOM_500KHZ     500000
#define AM_HAL_IOM_400KHZ     400000
#define AM_HAL_IOM_375KHZ     375000
#define AM_HAL_IOM_250KHZ     250000
#define AM_HAL_IOM_200KHZ     200000
#define AM_HAL_IOM_125KHZ     125000
#define AM_HAL_IOM_100KHZ     100000
#define AM_HAL_IOM_50KHZ       50000
#define AM_HAL_IOM_10KHZ       10000

// Hardware FIFO Size
#define AM_HAL_IOM_MAX_FIFO_SIZE    128

//*****************************************************************************
//
//! @name IOM Physical Protocols
//! @brief Macro Definitions for general IOM configuration.
//!
//! These macros may be used with the am_hal_iom_config_t structure to set the
//! operating parameters of each serial IO master module. Choose SPIMODE to
//! select the SPI interface, or I2CMODE to select the I2C interface.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_IOM_SPIMODE                  AM_REG_IOMSTR_CFG_IFCSEL(1)
#define AM_HAL_IOM_I2CMODE                  AM_REG_IOMSTR_CFG_IFCSEL(0)
//! @}

//*****************************************************************************
//
//! @name IOM Operations
//! @brief Macro definitions used for ui32Operation parameters.
//!
//! These macros may be used to specify which action an IOM command will
//! execute. The 'OFFSET' operations will cause the IOM hardware to transmit the
//! provided 1-byte 'offset' before executing the rest of the command.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_IOM_WRITE                    0x00000000
#define AM_HAL_IOM_READ                     0x80000000
//! @}

//*****************************************************************************
//
//! @name Command Options
//! @brief Macro definitions used for ui32Options parameters.
//!
//! These macros are all related to SPI or I2C command words. They can be used
//! to set specific options on a per-transaction basis.
//!
//! - CS_LOW - Do not raise the CS signal at the end of this SPI command.
//! - NO_STOP - Do not release the I2C bus with a STOP bit after this command.
//! - LSB_FIRST - Reverse the payload bits of this command.
//! - 10BIT_ADDRESS - (I2C only) use a 10-bit I2C address protocol.
//! - RAW - Don't use an offset byte.
//! - OFFSET() - Send this 1-byte offset as the first byte of the transaction.
//!   This can be used to access "registers" in external I2C devices, or add a
//!   1-byte write to the beginning of a SPI write or read command. See
//!   "normal mode" operation in the I2C/SPI Master section of the datasheet
//!   for more information on this parameter.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_IOM_CS_LOW                   0x10000000
#define AM_HAL_IOM_NO_STOP                  0x10000000
#define AM_HAL_IOM_LSB_FIRST                0x08000000
#define AM_HAL_IOM_10BIT_ADDRESS            0x04000000
#define AM_HAL_IOM_RAW                      0x40000000
#define AM_HAL_IOM_OFFSET(n)                (((n) << 8) & 0x0000FF00)
//! @}

//*****************************************************************************
//
//! @name IOM Interrupts
//! @brief Macro definitions for IOM interrupt status bits.
//!
//! These macros correspond to the bits in the IOM interrupt status register.
//! They may be used with any of the \e am_hal_iom_int_x() functions.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_IOM_INT_ARB                  AM_REG_IOMSTR_INTEN_ARB_M
#define AM_HAL_IOM_INT_STOP                 AM_REG_IOMSTR_INTEN_STOP_M
#define AM_HAL_IOM_INT_START                AM_REG_IOMSTR_INTEN_START_M
#define AM_HAL_IOM_INT_ICMD                 AM_REG_IOMSTR_INTEN_ICMD_M
#define AM_HAL_IOM_INT_IACC                 AM_REG_IOMSTR_INTEN_IACC_M
#define AM_HAL_IOM_INT_WTLEN                AM_REG_IOMSTR_INTEN_WTLEN_M
#define AM_HAL_IOM_INT_NAK                  AM_REG_IOMSTR_INTEN_NAK_M
#define AM_HAL_IOM_INT_FOVFL                AM_REG_IOMSTR_INTEN_FOVFL_M
#define AM_HAL_IOM_INT_FUNDFL               AM_REG_IOMSTR_INTEN_FUNDFL_M
#define AM_HAL_IOM_INT_THR                  AM_REG_IOMSTR_INTEN_THR_M
#define AM_HAL_IOM_INT_CMDCMP               AM_REG_IOMSTR_INTEN_CMDCMP_M

#define AM_HAL_IOM_INT_ALL          (   \
            AM_HAL_IOM_INT_ARB      |   \
            AM_HAL_IOM_INT_STOP     |   \
            AM_HAL_IOM_INT_START    |   \
            AM_HAL_IOM_INT_ICMD     |   \
            AM_HAL_IOM_INT_IACC     |   \
            AM_HAL_IOM_INT_WTLEN    |   \
            AM_HAL_IOM_INT_NAK      |   \
            AM_HAL_IOM_INT_FOVFL    |   \
            AM_HAL_IOM_INT_FUNDFL   |   \
            AM_HAL_IOM_INT_THR      |   \
            AM_HAL_IOM_INT_CMDCMP)

#define AM_HAL_IOM_INT_SWERR        (   \
            AM_HAL_IOM_INT_ICMD     |   \
            AM_HAL_IOM_INT_FOVFL    |   \
            AM_HAL_IOM_INT_FUNDFL   |   \
            AM_HAL_IOM_INT_IACC)

#define AM_HAL_IOM_INT_I2CARBERR    (   \
            AM_HAL_IOM_INT_ARB      |   \
            AM_HAL_IOM_INT_START    |   \
            AM_HAL_IOM_INT_STOP)
//! @}

//*****************************************************************************
//
//! @name Software IOM modules
//! @brief Macro definitions for using the software I2C interface.
//!
//! Use this macro as the module number for standard IOM functions to emulate
//! them using the bit-banged i2c interface.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_IOM_I2CBB_MODULE             AM_REG_IOMSTR_NUM_MODULES
//! @}

//*****************************************************************************
//
//! @name IOM Return Codes
//! @brief Enum definitions for defining return values for IOM APIs
//!
//! This enum defines possible values for non-void IOM APIs
//!
//! @{
//
//*****************************************************************************
typedef enum
{
    AM_HAL_IOM_SUCCESS = 0,
    AM_HAL_IOM_ERR_TIMEOUT,
    AM_HAL_IOM_ERR_INVALID_MODULE,
    AM_HAL_IOM_ERR_INVALID_PARAM,
    AM_HAL_IOM_ERR_INVALID_CFG,
    AM_HAL_IOM_ERR_INVALID_OPER,
    AM_HAL_IOM_ERR_I2C_NAK,
    AM_HAL_IOM_ERR_I2C_ARB,
    AM_HAL_IOM_ERR_RESOURCE_ERR,
} am_hal_iom_status_e ;

//! @}

//*****************************************************************************
//
//! @brief Union type for a word-aligned, byte-addressable array.
//!
//! This is a convenience macro that may be used to define byte-addressable
//! arrays with 32-bit alignment. This allows the programmer to define SPI or
//! I2C transactions as a series of 8-bit values, but also write them to the
//! IOM FIFO efficiently as a series of 32-bit values.
//!
//! Example usage:
//!
//! @code
//!     //
//!     // Declare a buffer array with at least 3-bytes worth of space.
//!     //
//!     am_hal_iom_buffer(3) sBuffer;
//!
//!     //
//!     // Populate the buffer with a 3-byte command.
//!     //
//!     sBuffer.bytes[0] = 's';
//!     sBuffer.bytes[1] = 'p';
//!     sBuffer.bytes[2] = 'i';
//!
//!     //
//!     // Send the buffer over the spi interface.
//!     //
//!     am_hal_iom_spi_write(psDevice, sBuffer.words, 3, 0);
//!
//! @endcode
//
//*****************************************************************************
#define am_hal_iom_buffer(A)                                                  \
    union                                                                     \
    {                                                                         \
        uint32_t words[(A + 3) >> 2];                                         \
        uint8_t bytes[A];                                                     \
    }

//*****************************************************************************
//
//! @brief Configuration structure for the IO master module.
//
//*****************************************************************************
typedef struct
{
    //
    //! @brief Selects the physical protocol for the IO master module. Choose
    //! either AM_HAL_IOM_SPIMODE or AM_HAL_IOM_I2CMODE.
    //
    uint32_t ui32InterfaceMode;

    //
    //! @brief Selects the output clock frequency for SPI or I2C mode. Choose
    //! one of the AM_HAL_IOM_nMHZ or AM_HAL_IOM_nKHZ macros.
    //
    uint32_t ui32ClockFrequency;

    //
    //! Select the SPI clock phase (unused in I2C mode).
    //
    bool bSPHA;

    //
    //! Select the SPI clock polarity (unused in I2C mode).
    //
    bool bSPOL;
    
    //
    //! @brief Select the FIFO write threshold.
    //!
    //! The IOM controller will generate a processor interrupt when the number
    //! of entries in the FIFO goes *below* this number.
    //
    uint8_t ui8WriteThreshold;

    //
    //! @brief Select the FIFO read threshold.
    //!
    //! The IOM controller will generate a processor interrupt when the number
    //! of entries in the FIFO grows *larger* than this number.
    //
    uint8_t ui8ReadThreshold;
    
}
am_hal_iom_config_t;

//*****************************************************************************
//
//! Configuration structure for an individual SPI device.
//
//*****************************************************************************
typedef struct
{
    //
    //! IOM module to use for communicating with this device.
    //
    uint32_t ui32Module;

    //
    //! Chip select signal that should be used for this device.
    //
    uint32_t ui32ChipSelect;

    //
    //! Additional options that will ALWAYS be ORed into the command word.
    //
    uint32_t ui32Options;
}
am_hal_iom_spi_device_t;

//*****************************************************************************
//
//! Configuration structure for an individual I2C device.
//
//*****************************************************************************
typedef struct
{
    //
    //! IOM module to use for communicating with this device.
    //
    uint32_t ui32Module;

    //
    //! I2C address associated with this device.
    //
    uint32_t ui32BusAddress;

    //
    //! Additional options that will ALWAYS be ORed into the command word.
    //
    uint32_t ui32Options;
}
am_hal_iom_i2c_device_t;

//*****************************************************************************
//
// Typedef for non-blocking function callbacks.
//
//*****************************************************************************
typedef void (*am_hal_iom_callback_t)(void);

//*****************************************************************************
//
// Typedef for a function that waits until the IOM queue is empty.
//
//*****************************************************************************
typedef void (*am_hal_iom_queue_flush_t)(uint32_t);

extern am_hal_iom_queue_flush_t am_hal_iom_queue_flush;


//*****************************************************************************
//
// Operations
//
//*****************************************************************************
#define AM_HAL_IOM_QUEUE_SPI_WRITE                 0
#define AM_HAL_IOM_QUEUE_SPI_READ                  1
#define AM_HAL_IOM_QUEUE_I2C_WRITE                 2
#define AM_HAL_IOM_QUEUE_I2C_READ                  3

//*****************************************************************************
//
// Structure to hold IOM operations.
//
//*****************************************************************************
typedef struct
{
    uint32_t ui32Operation;
    uint32_t ui32Module;
    uint32_t ui32ChipSelect;
    uint32_t *pui32Data;
    uint32_t ui32NumBytes;
    uint32_t ui32Options;
    am_hal_iom_callback_t pfnCallback;
}
am_hal_iom_queue_entry_t;

//*****************************************************************************
//
// Structure to hold IOM configuration during module power-down.
//
//*****************************************************************************
typedef struct
{
    uint32_t FIFOTHR;
    uint32_t CLKCFG;
    uint32_t CFG;
    uint32_t INTEN;
    uint32_t bValid;
}
am_hal_iom_pwrsave_t;

//*****************************************************************************
//
// Global variables
//
//*****************************************************************************
extern am_hal_iom_pwrsave_t am_hal_iom_pwrsave[AM_REG_IOMSTR_NUM_MODULES];

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void     am_hal_iom_pwrctrl_enable(uint32_t ui32Module);
extern void     am_hal_iom_pwrctrl_disable(uint32_t ui32Module);
extern void     am_hal_iom_power_on_restore(uint32_t ui32Module);
extern void     am_hal_iom_power_off_save(uint32_t ui32Module);
extern void     am_hal_iom_config(uint32_t ui32Module,
                                  const am_hal_iom_config_t *psConfig);
extern uint32_t am_hal_iom_frequency_get(uint32_t ui32Module);
extern void     am_hal_iom_enable(uint32_t ui32Module);
extern void     am_hal_iom_disable(uint32_t ui32Module);
extern am_hal_iom_status_e am_hal_iom_spi_write(uint32_t ui32Module, uint32_t ui32ChipSelect,
                                     uint32_t *pui32Data, uint32_t ui32NumBytes,
                                     uint32_t ui32Options);
extern am_hal_iom_status_e am_hal_iom_spi_read(uint32_t ui32Module, uint32_t ui32ChipSelect,
                                    uint32_t *pui32Data, uint32_t ui32NumBytes,
                                    uint32_t ui32Options);
extern am_hal_iom_status_e am_hal_iom_spi_fullduplex(uint32_t ui32Module, uint32_t ui32ChipSelect,
                                                     uint32_t *pui32TxData, uint32_t *pui32RxData, 
                                                     uint32_t ui32NumBytes, uint32_t ui32Options);

extern am_hal_iom_status_e am_hal_iom_spi_write_nq(uint32_t ui32Module, uint32_t ui32ChipSelect,
                                        uint32_t *pui32Data, uint32_t ui32NumBytes,
                                        uint32_t ui32Options);
extern am_hal_iom_status_e am_hal_iom_spi_read_nq(uint32_t ui32Module, uint32_t ui32ChipSelect,
                                       uint32_t *pui32Data, uint32_t ui32NumBytes,
                                       uint32_t ui32Options);
extern am_hal_iom_status_e am_hal_iom_spi_fullduplex_nq(uint32_t ui32Module, uint32_t ui32ChipSelect,
                                                        uint32_t *pui32TxData, uint32_t *pui32RxData, 
                                                        uint32_t ui32NumBytes, uint32_t ui32Options);
extern am_hal_iom_status_e am_hal_iom_spi_write_nb(uint32_t ui32Module, uint32_t ui32ChipSelect,
                                        uint32_t *pui32Data, uint32_t ui32NumBytes,
                                        uint32_t ui32Options,
                                        am_hal_iom_callback_t pfnCallback);
extern am_hal_iom_status_e am_hal_iom_spi_read_nb(uint32_t ui32Module, uint32_t ui32ChipSelect,
                                       uint32_t *pui32Data, uint32_t ui32NumBytes,
                                       uint32_t ui32Options,
                                       am_hal_iom_callback_t pfnCallback);
extern void     am_hal_iom_spi_cmd_run(uint32_t ui32Operation,
                                       uint32_t ui32Module,
                                       uint32_t ui32ChipSelect,
                                       uint32_t ui32NumBytes,
                                       uint32_t ui32Options);
extern am_hal_iom_status_e am_hal_iom_i2c_write(uint32_t ui32Module,
                                     uint32_t ui32BusAddress,
                                     uint32_t *pui32Data,
                                     uint32_t ui32NumBytes,
                                     uint32_t ui32Options);
extern am_hal_iom_status_e am_hal_iom_i2c_read(uint32_t ui32Module,
                                    uint32_t ui32BusAddress,
                                    uint32_t *pui32Data,
                                    uint32_t ui32NumBytes,
                                    uint32_t ui32Options);
extern am_hal_iom_status_e am_hal_iom_i2c_write_nq(uint32_t ui32Module,
                                        uint32_t ui32BusAddress,
                                        uint32_t *pui32Data,
                                        uint32_t ui32NumBytes,
                                        uint32_t ui32Options);
extern am_hal_iom_status_e am_hal_iom_i2c_read_nq(uint32_t ui32Module,
                                       uint32_t ui32BusAddress,
                                       uint32_t *pui32Data,
                                       uint32_t ui32NumBytes,
                                       uint32_t ui32Options);
extern am_hal_iom_status_e am_hal_iom_i2c_write_nb(uint32_t ui32Module,
                                        uint32_t ui32BusAddress,
                                        uint32_t *pui32Data,
                                        uint32_t ui32NumBytes,
                                        uint32_t ui32Options,
                                        am_hal_iom_callback_t pfnCallback);
extern am_hal_iom_status_e am_hal_iom_i2c_read_nb(uint32_t ui32Module,
                                       uint32_t ui32BusAddress,
                                       uint32_t *pui32Data,
                                       uint32_t ui32NumBytes,
                                       uint32_t ui32Options,
                                       am_hal_iom_callback_t pfnCallback);
extern am_hal_iom_status_e am_hal_iom_i2c_cmd_run(uint32_t ui32Operation,
                                       uint32_t ui32Module,
                                       uint32_t ui32BusAddress,
                                       uint32_t ui32NumBytes,
                                       uint32_t ui32Options);
extern void     am_hal_iom_command_repeat_set(uint32_t ui32Module,
                                              uint32_t ui32CmdCount);
extern uint32_t am_hal_iom_status_get(uint32_t ui32Module);
extern am_hal_iom_status_e am_hal_iom_error_status_get(uint32_t ui32Module);
extern uint32_t am_hal_iom_fifo_write(uint32_t ui32Module, uint32_t *pui32Data,
                                      uint32_t ui32NumBytes);
extern uint32_t am_hal_iom_fifo_read(uint32_t ui32Module, uint32_t *pui32Data,
                                     uint32_t ui32NumBytes);
extern uint8_t  am_hal_iom_fifo_empty_slots(uint32_t ui32Module);
extern uint8_t  am_hal_iom_fifo_full_slots(uint32_t ui32Module);
extern void     am_hal_iom_poll_complete(uint32_t ui32Module);
extern void     am_hal_iom_int_service(uint32_t ui32Module, uint32_t ui32Status);
extern void     am_hal_iom_int_enable(uint32_t ui32Module, uint32_t ui32Interrupt);
extern uint32_t am_hal_iom_int_enable_get(uint32_t ui32Module);
extern void     am_hal_iom_int_disable(uint32_t ui32Module, uint32_t ui32Interrupt);
extern void     am_hal_iom_int_clear(uint32_t ui32Module, uint32_t ui32Interrupt);
extern void     am_hal_iom_int_set(uint32_t ui32Module, uint32_t ui32Interrupt);
extern uint32_t am_hal_iom_int_status_get(uint32_t ui32Module, bool bEnabledOnly);
extern void     am_hal_iom_queue_init(uint32_t ui32ModuleNum,
                                      am_hal_iom_queue_entry_t *psQueueMemory,
                                      uint32_t ui32QueueMemSize);
extern uint32_t am_hal_iom_queue_length_get(uint32_t ui32Module);
extern void     am_hal_iom_sleeping_queue_flush(uint32_t ui32Module);
extern am_hal_iom_status_e am_hal_iom_queue_spi_write(uint32_t ui32Module, uint32_t ui32ChipSelect,
                                           uint32_t *pui32Data, uint32_t ui32NumBytes,
                                           uint32_t ui32Options,
                                           am_hal_iom_callback_t pfnCallback);
extern am_hal_iom_status_e am_hal_iom_queue_spi_read(uint32_t ui32Module, uint32_t ui32ChipSelect,
                                          uint32_t *pui32Data, uint32_t ui32NumBytes,
                                          uint32_t ui32Options,
                                          am_hal_iom_callback_t pfnCallback);
extern am_hal_iom_status_e am_hal_iom_queue_i2c_write(uint32_t ui32Module, uint32_t ui32BusAddress,
                                           uint32_t *pui32Data, uint32_t ui32NumBytes,
                                           uint32_t ui32Options,
                                           am_hal_iom_callback_t pfnCallback);
extern am_hal_iom_status_e am_hal_iom_queue_i2c_read(uint32_t ui32Module, uint32_t ui32BusAddress,
                                          uint32_t *pui32Data, uint32_t ui32NumBytes,
                                          uint32_t ui32Options,
                                          am_hal_iom_callback_t pfnCallback);
extern void     am_hal_iom_queue_start_next_msg(uint32_t ui32Module);
extern void     am_hal_iom_queue_service(uint32_t ui32Module, uint32_t ui32Status);

//*****************************************************************************
//
// Helper functions.
//
//*****************************************************************************
#define AM_IOMASTER_ISR_QUEUE(x)                            \
void am_iomaster##x##_isr(void)                             \
{                                                           \
    uint32_t ui32IntStatus;                                 \
    ui32IntStatus = am_hal_iom_int_status_get(x, false);    \
    am_hal_iom_int_clear(x, ui32IntStatus);                 \
    am_hal_iom_queue_service(x, ui32IntStatus);             \
}

#define AM_IOMASTER_ISR_NB(x)                               \
void am_iomaster##x##_isr(void)                             \
{                                                           \
    uint32_t ui32IntStatus;                                 \
    ui32IntStatus = am_hal_iom_int_status_get(x, false);    \
    am_hal_iom_int_clear(x, ui32IntStatus);                 \
    am_hal_iom_int_service(x, ui32IntStatus);               \
}

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_IOM_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
