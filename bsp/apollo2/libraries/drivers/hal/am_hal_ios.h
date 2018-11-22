//*****************************************************************************
//
//  am_hal_ios.h
//! @file
//!
//! @brief Functions for interfacing with the IO Slave module
//!
//! @addtogroup ios2 IO Slave (SPI/I2C)
//! @ingroup apollo2hal
//! @{
//
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
#ifndef AM_HAL_IOS_H
#define AM_HAL_IOS_H


//*****************************************************************************
//
//! @name Interface Configuration
//! @brief Macro definitions for configuring the physical interface of the IO
//! Slave
//!
//! These macros may be used with the am_hal_ios_config_t structure to set the
//! physical parameters of the SPI/I2C slave module.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_IOS_USE_SPI           AM_REG_IOSLAVE_CFG_IFCSEL_SPI
#define AM_HAL_IOS_SPIMODE_0         AM_REG_IOSLAVE_CFG_SPOL_SPI_MODES_0_3
#define AM_HAL_IOS_SPIMODE_1         AM_REG_IOSLAVE_CFG_SPOL_SPI_MODES_1_2
#define AM_HAL_IOS_SPIMODE_2         AM_REG_IOSLAVE_CFG_SPOL_SPI_MODES_1_2
#define AM_HAL_IOS_SPIMODE_3         AM_REG_IOSLAVE_CFG_SPOL_SPI_MODES_0_3

#define AM_HAL_IOS_USE_I2C           AM_REG_IOSLAVE_CFG_IFCSEL_I2C
#define AM_HAL_IOS_I2C_ADDRESS(n)    AM_REG_IOSLAVE_CFG_I2CADDR(n)

#define AM_HAL_IOS_LSB_FIRST         AM_REG_IOSLAVE_CFG_LSB(1)
//! @}

//*****************************************************************************
//
//! @name Register Access Interrupts
//! @brief Macro definitions for register access interrupts.
//!
//! These macros may be used with any of the
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_IOS_ACCESS_INT_00     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 31)
#define AM_HAL_IOS_ACCESS_INT_01     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 30)
#define AM_HAL_IOS_ACCESS_INT_02     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 29)
#define AM_HAL_IOS_ACCESS_INT_03     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 28)
#define AM_HAL_IOS_ACCESS_INT_04     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 27)
#define AM_HAL_IOS_ACCESS_INT_05     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 26)
#define AM_HAL_IOS_ACCESS_INT_06     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 25)
#define AM_HAL_IOS_ACCESS_INT_07     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 24)
#define AM_HAL_IOS_ACCESS_INT_08     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 23)
#define AM_HAL_IOS_ACCESS_INT_09     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 22)
#define AM_HAL_IOS_ACCESS_INT_0A     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 21)
#define AM_HAL_IOS_ACCESS_INT_0B     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 20)
#define AM_HAL_IOS_ACCESS_INT_0C     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 19)
#define AM_HAL_IOS_ACCESS_INT_0D     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 18)
#define AM_HAL_IOS_ACCESS_INT_0E     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 17)
#define AM_HAL_IOS_ACCESS_INT_0F     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 16)
#define AM_HAL_IOS_ACCESS_INT_13     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 15)
#define AM_HAL_IOS_ACCESS_INT_17     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 14)
#define AM_HAL_IOS_ACCESS_INT_1B     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 13)
#define AM_HAL_IOS_ACCESS_INT_1F     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 12)
#define AM_HAL_IOS_ACCESS_INT_23     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 11)
#define AM_HAL_IOS_ACCESS_INT_27     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 10)
#define AM_HAL_IOS_ACCESS_INT_2B     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 9)
#define AM_HAL_IOS_ACCESS_INT_2F     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 8)
#define AM_HAL_IOS_ACCESS_INT_33     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 7)
#define AM_HAL_IOS_ACCESS_INT_37     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 6)
#define AM_HAL_IOS_ACCESS_INT_3B     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 5)
#define AM_HAL_IOS_ACCESS_INT_3F     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 4)
#define AM_HAL_IOS_ACCESS_INT_43     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 3)
#define AM_HAL_IOS_ACCESS_INT_47     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 2)
#define AM_HAL_IOS_ACCESS_INT_4B     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 1)
#define AM_HAL_IOS_ACCESS_INT_4F     AM_REG_IOSLAVE_REGACCINTEN_REGACC((uint32_t)1 << 0)
#define AM_HAL_IOS_ACCESS_INT_ALL    0xFFFFFFFF
//! @}

//*****************************************************************************
//
//! @name I/O Slave Interrupts
//! @brief Macro definitions for I/O slave (IOS) interrupts.
//!
//! These macros may be used with any of the
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_IOS_INT_FSIZE            AM_REG_IOSLAVE_INTEN_FSIZE_M
#define AM_HAL_IOS_INT_FOVFL            AM_REG_IOSLAVE_INTEN_FOVFL_M
#define AM_HAL_IOS_INT_FUNDFL           AM_REG_IOSLAVE_INTEN_FUNDFL_M
#define AM_HAL_IOS_INT_FRDERR           AM_REG_IOSLAVE_INTEN_FRDERR_M
#define AM_HAL_IOS_INT_GENAD            AM_REG_IOSLAVE_INTEN_GENAD_M
#define AM_HAL_IOS_INT_IOINTW           AM_REG_IOSLAVE_INTEN_IOINTW_M
#define AM_HAL_IOS_INT_XCMPWR           AM_REG_IOSLAVE_INTEN_XCMPWR_M
#define AM_HAL_IOS_INT_XCMPWF           AM_REG_IOSLAVE_INTEN_XCMPWF_M
#define AM_HAL_IOS_INT_XCMPRR           AM_REG_IOSLAVE_INTEN_XCMPRR_M
#define AM_HAL_IOS_INT_XCMPRF           AM_REG_IOSLAVE_INTEN_XCMPRF_M
#define AM_HAL_IOS_INT_ALL              0xFFFFFFFF
//! @}

//*****************************************************************************
//
//! @name I/O Slave Interrupts triggers
//! @brief Macro definitions for I/O slave (IOS) interrupts.
//!
//! These macros may be used with am_hal_ios_int_set and am_hal_ios_int_clear
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_IOS_IOINTCTL_INT0    (0x01)
#define AM_HAL_IOS_IOINTCTL_INT1    (0x02)
#define AM_HAL_IOS_IOINTCTL_INT2    (0x04)
#define AM_HAL_IOS_IOINTCTL_INT3    (0x08)
#define AM_HAL_IOS_IOINTCTL_INT4    (0x10)
#define AM_HAL_IOS_IOINTCTL_INT5    (0x20)
//! @}

//*****************************************************************************
//
// External variable definitions
//
//*****************************************************************************

//*****************************************************************************
//
//! @brief LRAM pointer
//!
//! Pointer to the base of the IO Slave LRAM.
//
//*****************************************************************************
extern volatile uint8_t * const am_hal_ios_pui8LRAM;

//*****************************************************************************
//
//! @brief Configuration structure for the IO slave module.
//!
//! This structure may be used along with the am_hal_ios_config() function to
//! select key parameters of the IO Slave module. See the descriptions of each
//! parameter within this structure for more information on what they control.
//
//*****************************************************************************
typedef struct
{
    //
    //! Interface Selection
    //!
    //! This word selects the physical behavior of the IO Slave port. For SPI
    //! mode, this word should be the logical OR of one or more of the
    //! following:
    //!
    //!     AM_HAL_IOS_USE_SPI
    //!     AM_HAL_IOS_SPIMODE_0
    //!     AM_HAL_IOS_SPIMODE_1
    //!     AM_HAL_IOS_SPIMODE_2
    //!     AM_HAL_IOS_SPIMODE_3
    //!
    //! For I2C mode, use the logical OR of one or more of these values instead
    //! (where n is the 7 or 10-bit I2C address to use):
    //!
    //!     AM_HAL_IOS_USE_I2C
    //!     AM_HAL_IOS_I2C_ADDRESS(n)
    //!
    //! Also, in any mode, you may OR in this value to reverse the order of
    //! incoming data bits.
    //!
    //!     AM_HAL_IOS_LSB_FIRST
    //
    uint32_t ui32InterfaceSelect;

    //
    //! Read-Only section
    //!
    //! The IO Slave LRAM is split into three main sections. The first section
    //! is a "Direct Write" section, which may be accessed for reads or write
    //! either directly through the Apollo CPU, or over the SPI/I2C bus. The
    //! "Direct Write" section always begins at LRAM offset 0x0. At the end of
    //! the normal "Direct Write" space, there is a "Read Only" space, which is
    //! read/write accessible to the Apollo CPU, but read-only over the I2C/SPI
    //! Bus. This word selects the base address of this "Read Only" space.
    //!
    //! This value may be set to any multiple of 8 between 0x0 and 0x78,
    //! inclusive. For the configuration to be valid, \e ui32ROBase must also
    //! be less than or equal to \e ui32FIFOBase
    //!
    //! @note The address given here is in units of BYTES. Since the location
    //! of the "Read Only" space may only be set in 8-byte increments, this
    //! value must be a multiple of 8.
    //!
    //! For the avoidance of doubt this means 0x80 is 128 bytes. These functions
    //! will shift right by 8 internally.
    //
    uint32_t ui32ROBase;

    //
    //! FIFO section
    //!
    //! After the "Direct Access" and "Read Only" sections is a section of LRAM
    //! allocated to a FIFO. This section is accessible by the Apollo CPU
    //! through the FIFO control registers, and accessible on the SPI/I2C bus
    //! through the 0x7F address. This word selects the base address of the
    //! FIFO space. The FIFO will extend from the address specified here to the
    //! address specified in \e ui32RAMBase.
    //!
    //! This value may be set to any multiple of 8 between 0x0 and 0x78,
    //! inclusive. For the configuration to be valid, \e ui32FIFOBase must also
    //! be greater than or equal to \e ui32ROBase.
    //!
    //! @note The address given here is in units of BYTES. Since the location
    //! of the "FIFO" space may only be set in 8-byte increments, this value
    //! must be a multiple of 8.
    //!
    //! For the avoidance of doubt this means 0x80 is 128 bytes. These functions
    //! will shift right by 8 internally.
    //
    uint32_t ui32FIFOBase;

    //
    //! RAM section
    //!
    //! At the end of the IOS LRAM, the user may allocate a "RAM" space that
    //! can only be accessed by the Apollo CPU. This space will not interact
    //! with the SPI/I2C bus at all, and may be used as general-purpose memory.
    //! Unlike normal SRAM, this section of LRAM will retain its state through
    //! Deep Sleep, so it may be used as a data retention space for
    //! ultra-low-power applications.
    //!
    //! This value may be set to any multiple of 8 between 0x0 and 0x100,
    //! inclusive. For the configuration to be valid, \e ui32RAMBase must also
    //! be greater than or equal to \e ui32FIFOBase.
    //!
    //! @note The address given here is in units of BYTES. Since the location
    //! of the "FIFO" space may only be set in 8-byte increments, this value
    //! must be a multiple of 8.
    //!
    //! For the avoidance of doubt this means 0x80 is 128 bytes. These functions
    //! will shift right by 8 internally.
    //
    uint32_t ui32RAMBase;

    //
    //! FIFO threshold
    //!
    //! The IO Slave module will trigger an interrupt when the number of
    //! entries in the FIFO drops below this number of bytes.
    //
    uint32_t ui32FIFOThreshold;

    //
    // Pointer to an SRAM
    //
    uint8_t *pui8SRAMBuffer;
}
am_hal_ios_config_t;

#ifdef __cplusplus
extern "C"
{
#endif
//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void am_hal_ios_enable(uint32_t ui32Module);
extern void am_hal_ios_disable(uint32_t ui32Module);

// these interrupts drive the HOST side IOS interrupt pins
extern void am_hal_ios_host_int_set(uint32_t ui32Interrupt);
extern void am_hal_ios_host_int_clear(uint32_t ui32Interrupt);
extern uint32_t am_hal_ios_host_int_get(void);
extern uint32_t am_hal_ios_host_int_enable_get(void);

extern void am_hal_ios_lram_write(uint32_t ui32Offset, uint8_t ui8Value);
extern uint8_t am_hal_ios_lram_read(uint32_t ui32Offset);

// the following interrupts go back to the NVIC
extern void am_hal_ios_config(am_hal_ios_config_t *psConfig);
extern void am_hal_ios_access_int_enable(uint32_t ui32Interrupt);
extern uint32_t am_hal_ios_access_int_enable_get(void);
extern void am_hal_ios_access_int_disable(uint32_t ui32Interrupt);
extern void am_hal_ios_access_int_clear(uint32_t ui32Interrupt);
extern void am_hal_ios_access_int_set(uint32_t ui32Interrupt);
extern uint32_t am_hal_ios_access_int_status_get(bool bEnabledOnly);
extern void am_hal_ios_int_enable(uint32_t ui32Interrupt);
extern uint32_t am_hal_ios_int_enable_get(void);
extern void am_hal_ios_int_disable(uint32_t ui32Interrupt);
extern void am_hal_ios_int_clear(uint32_t ui32Interrupt);
extern void am_hal_ios_int_set(uint32_t ui32Interrupt);
extern uint32_t am_hal_ios_int_status_get(bool bEnabledOnly);

extern void am_hal_ios_fifo_buffer_init(uint8_t *pui8Buffer, uint32_t ui32NumBytes);
extern uint32_t am_hal_ios_fifo_space_left(void);
extern uint32_t am_hal_ios_fifo_space_used(void);
extern void am_hal_ios_fifo_service(uint32_t ui32Status);
// Returns the number of bytes actually written
extern uint32_t am_hal_ios_fifo_write(uint8_t *pui8Data, uint32_t ui32NumBytes);
extern void am_hal_ios_fifo_write_simple(uint8_t *pui8Data,
                                         uint32_t ui32NumBytes);
extern void am_hal_ios_fifo_ptr_set(uint32_t ui32Offset);
extern void am_hal_ios_update_fifoctr(void);

extern void am_hal_ios_read_poll_complete(void);
extern void am_hal_ios_pwrctrl_enable(void);
extern void am_hal_ios_pwrctrl_disable(void);


#ifdef __cplusplus
}
#endif

#endif // AM_HAL_IOS_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
