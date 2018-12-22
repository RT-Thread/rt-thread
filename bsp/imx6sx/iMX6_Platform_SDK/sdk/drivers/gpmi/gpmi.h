/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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
#if !defined(__gpmi_h_)
#define __gpmi_h_

#include "sdk.h"
#include "bch_ecc.h"

/*!
 * @file gpmi.h
 * @brief The header file that contains the general definitions for NAND
 *
 * @ingroup diag_nand
 */

//! @addtogroup diag_nand
//! @{

#pragma pack(1)
//! @brief NAND timings for setting up the GPMI timing.
//!
//! This structure holds the timings for the NAND.  This data is used by
//! gpmi_set_timings() to setup the GPMI hardware registers.
typedef struct GpmiNandTimings
{
    //! @brief The data setup time (tDS), in nanoseconds.
    uint8_t tDS;

    //! @brief The data hold time (tDH), in nanoseconds.
    uint8_t tDH;

    //! @brief The address setup time (tSU), in nanoseconds.
    //!
    //! This value amalgamates the NAND parameters tCLS, tCS, and tALS.
    uint8_t tSU;

    //! @brief From the NAND datasheet.
    uint8_t tREA;

    //! @brief From the NAND datasheet.
    //!
    //! This is the amount of time that the last contents of the data lines will persist
    //! after the controller drives the -RE signal true.
    //!
    //! EDO Mode: This time is from the NAND spec, and the persistence of data
    //! is determined by (tRLOH + tDH).
    //!
    //! Non-EDO Mode: This time is ignored, because the persistence of data
    //! is determined by tRHOH.
    uint8_t tRLOH;

    //! @brief From the NAND datasheet.
    //!
    //! This is the amount of time that the last contents of the data lines will persist after the
    //! controller drives the -RE signal false.
    //!
    //! EDO Mode: This time is ignored, because the persistence of data is determined by
    //! (tRLOH + tDH).
    //!
    //! Non-EDO Mode: This time is totally due to capacitive effects of the hardware. For reliable
    //! behavior it should be set to zero, unless there is specific knowledge of the trace
    //! capacitance and the persistence of the data values.
    uint8_t tRHOH;
} GpmiNandTimings_t;
#pragma pack()

// Forward declaration.
typedef struct _apbh_dma_t apbh_dma_t;

//! @brief DMA wait options.
//!
//! These mask values are combined together to form the wait mask that is passed to gpmi_run_dma().
//! The wait mask indicates which IRQs must fire before the DMA is considered done executing.
enum _nand_gpmi_dma_wait_mask {
    kNandGpmiDmaWaitMask_Nothing = 0,   //!< Do not wait.
    kNandGpmiDmaWaitMask_GpmiDma = 1,   //!< Wait for the APBH DMA completion IRQ.
    kNandGpmiDmaWaitMask_Ecc = 2,       //!< Wait for the BCH completion IRQ.
};

//! @brief APBH DMA channel for GPMI chip select 0.
#define NAND0_APBH_CH (0)

//! @brief Number of NAND chip selects supported by this chip.
//!
//! This is also implicitly the number of DMA channels in the APBH.
#define GPMI_CHIP_SELECT_COUNT (4)

//! @name Error codes
//@{
#if !defined(SUCCESS)
#define SUCCESS (0)
#endif

#define ERROR_DDI_NAND_GPMI_NOT_PRESENT (1)
#define ERROR_DDI_NAND_GPMI_DMA_TIMEOUT (2)
#define ERROR_DDI_NAND_GPMI_DMA_BUSY (3)
#define ERROR_DDI_NAND_GPMI_UNCORRECTABLE_ECC (4)
#define ERROR_DDI_NAND_HAL_WRITE_FAILED (5)
//@}

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

//! @name Init and shutdown
//@{

////////////////////////////////////////////////////////////////////////////////
//! @brief Enable and initialize the GPMI driver.
//!
//! This function configures the GPMI block using the HW registers based upon
//! the desired chip and the number of bits. You must call this API for each
//! chip select that will be used in the application configuration.
//!
//! @param[in] minDelay Minimum signal propagation delay in nanoseconds. Pass 0 to use the
//!     default of 5 ns.
//! @param[in] maxDelay Maximum signal propagation delay in nanoseconds. Pass 0 to use the
//!     default of 9 ns.
//!
//! @return SUCCESS
//! @return ERROR_DDI_NAND_GPMI_NOT_PRESENT
////////////////////////////////////////////////////////////////////////////////
int gpmi_init(uint32_t minDelay, uint32_t maxDelay);

////////////////////////////////////////////////////////////////////////////////
//! @brief Resets the GPMI block.
//!
//! A soft reset can take multiple clocks to complete, so do NOT gate the
//! clock when setting soft reset. The reset process will gate the clock
//! automatically. Poll until this has happened before subsequently
//! clearing soft reset and clock gate.
////////////////////////////////////////////////////////////////////////////////
void gpmi_soft_reset(void);

////////////////////////////////////////////////////////////////////////////////
//! @brief Disable the GPMI driver.
//!
//! This function gates the clock to the GPMI peripheral.
////////////////////////////////////////////////////////////////////////////////
void gpmi_disable(void);

//@}

//! @name Write enable
//@{

////////////////////////////////////////////////////////////////////////////////
//! @brief Enable writes via the Write Protect line of the NAND.
//!
//! Enable or disable writes via the /WP pin of the NAND.  This WP line is
//! shared amongst all the NANDs.
//!
//! @param[in] doEnable Enable writes (1) or Disable writes (0) (/WP pin)
////////////////////////////////////////////////////////////////////////////////
void gpmi_enable_writes(bool doEnable);

//@}

//! @name DMA Utilities
//@{

////////////////////////////////////////////////////////////////////////////////
//! @brief Synchronously execute a DMA descriptor chain.
//!
//! Starts a NAND DMA command associated with the chip select
//! in the @a chipSelect parameter. Once the DMA is running, this function waits
//! for the interrupt handler(s) to signal completion.
//!
//! @param[in] theDma Pointer to dma command structure. Must be the virtual address,
//!     as it is converted to a physical address before the DMA is started.
//! @param[in] chipSelect Which NAND chip select should be started.
//! @param[in] waitMask A bitmask used to indicate criteria for terminating the DMA.
//!     See #_nand_gpmi_dma_wait_mask for more info.
//! @param[in] timeout Number of microseconds to wait before timing out. If
//!     zero is passed for the timeout, then this function will wait forever.
//!
//! @retval SUCCESS The DMA is started.
//! @retval ERROR_DDI_NAND_GPMI_DMA_BUSY Another DMA is already running.
//! @retval ERROR_DDI_NAND_GPMI_DMA_TIMEOUT DMA never completed or is still
//!     running. This value is returned explicitly from this function when
//!     the DMA semphore times out, and most DMA chains also return this
//!     error (see below for how) when the GPMI device busy timeout expires.
//!
//! @note Uses the BAR field of the last DMA command to signal                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
//!             result of the DMA chain.
////////////////////////////////////////////////////////////////////////////////
int gpmi_run_dma(apbh_dma_t * theDma, unsigned chipSelect, uint16_t waitMask, uint32_t timeout);

////////////////////////////////////////////////////////////////////////////////
//! @brief Returns a Boolean indicating if a DMA is currently running.
//!
//! @param u32NANDDeviceNum Specifies which DMA channel to inspect.
//! @retval true A DMA is currently running.
//! @retval false The DMA channel is free.
////////////////////////////////////////////////////////////////////////////////
bool gpmi_is_dma_active(uint32_t u32NANDDeviceNum);

//@}

//! @name Timing Control Functions
//@{

////////////////////////////////////////////////////////////////////////////////
//! @brief Fill the given timing structure with the safe timings.
//!
//! This function is used to get the timings characteristics that work with
//! every device we've ever known. These timings should be used during initialization
//! and device discovery. Once the device type is known,  timings specific to
//! that device should be set.  Remember to actually set the safe timings once
//! you get them by calling ddi_gpmi_set_timings().
//!
//! @param[out] timings The timings structure that will be set to the safe
//!     timings upon return.
////////////////////////////////////////////////////////////////////////////////
void gpmi_get_safe_timings(GpmiNandTimings_t * timings);

////////////////////////////////////////////////////////////////////////////////
//! @brief Set the flash timing for optimal NAND performance.
//!
//! Set the optimal NAND timings based upon the passed in NAND timings and the
//! current GPMI clock.
//!
//! @param[in] newTimings Pointer to timing table for the NAND.
//!
//! @warning This function assumes all NAND I/O is halted.
////////////////////////////////////////////////////////////////////////////////
void gpmi_set_timings(const GpmiNandTimings_t * newTimings);

////////////////////////////////////////////////////////////////////////////////
//! @brief Set the timeout value for wait for ready.
//!
//! The timeout value set here is used for the GPMI wait for ready mode. It
//! will have the most effect upon DMA operations.
//!
//! @param[in] busyTimeout Timeout value in microseconds.
////////////////////////////////////////////////////////////////////////////////
void gpmi_set_busy_timeout(uint32_t busyTimeout);

////////////////////////////////////////////////////////////////////////////////
//! @brief Returns the current GPMI timings values.
//!
//! @return A pointer to the current timing values used by the GPMI block.
//!     This will be the last set of timings passed to gpmi_set_timings().
////////////////////////////////////////////////////////////////////////////////
const GpmiNandTimings_t * gpmi_get_current_timings();

//@}

//! @name Common NAND operations
//!
//! These functions are used to perform the common set of NAND read and write operations. They
//! will build an appropriate DMA chain and execute it synchronously.
//@{

////////////////////////////////////////////////////////////////////////////////
//! @brief Configure the driver for a particular NAND type.
////////////////////////////////////////////////////////////////////////////////
int gpmi_nand_configure(unsigned rowBytes, unsigned columnBytes, unsigned pagesPerBlock, const BchEccLayout_t * ecc);

////////////////////////////////////////////////////////////////////////////////
//! @brief Reset the NAND.
////////////////////////////////////////////////////////////////////////////////
int gpmi_nand_reset(unsigned chipSelect);

////////////////////////////////////////////////////////////////////////////////
//! @brief Read a NAND's ID.
////////////////////////////////////////////////////////////////////////////////
int gpmi_nand_read_id(unsigned chipSelect, uint8_t * resultID);

////////////////////////////////////////////////////////////////////////////////
//! @brief Erase a block on a NAND.
////////////////////////////////////////////////////////////////////////////////
int gpmi_nand_erase_block(unsigned chipSelect, uint32_t blockNumber);

////////////////////////////////////////////////////////////////////////////////
//! @brief Read raw bytes from a NAND page.
////////////////////////////////////////////////////////////////////////////////
int gpmi_nand_read_raw(unsigned chipSelect, uint32_t pageNumber, uint8_t * buffer, uint32_t offset, uint32_t count);

////////////////////////////////////////////////////////////////////////////////
//! @brief Write a NAND page without using ECC.
////////////////////////////////////////////////////////////////////////////////
int gpmi_nand_write_raw(unsigned chipSelect, uint32_t pageNumber, const uint8_t * buffer, uint32_t offset, uint32_t count);

////////////////////////////////////////////////////////////////////////////////
//! @brief Read a NAND page using ECC.
//! @bug Not yet functional.
////////////////////////////////////////////////////////////////////////////////
int gpmi_nand_read_page(unsigned chipSelect, uint32_t pageNumber, uint8_t * buffer, uint8_t * auxBuffer);

////////////////////////////////////////////////////////////////////////////////
//! @brief Read the metadata from a NAND page.
//! @bug Not yet functional.
////////////////////////////////////////////////////////////////////////////////
int gpmi_nand_read_metadata(unsigned chipSelect, uint32_t pageNumber, uint8_t * buffer);

////////////////////////////////////////////////////////////////////////////////
//! @brief Write a NAND page.
//! @bug Not yet functional.
////////////////////////////////////////////////////////////////////////////////
int gpmi_nand_write_page(unsigned chipSelect, uint32_t pageNumber, const uint8_t * buffer, const uint8_t * auxBuffer);

//@}

//! @name Application APIs
//!
//! These functions must be implemented by the application. They are intended to isolate the
//! GPMI driver from board and application specific design choices.
//@{

//! @brief Configure GPMI pins.
void gpmi_iomux_config(void);

//! @brief External function to enable and configure the GPMI clock.
void gpmi_nand_clk_setup(void);

//! @brief Convert a virtual address to a physical address.
static inline void * nand_virtual_to_physical(const void * virtualAddress) { return (void *)virtualAddress; }

//@}

#ifdef __cplusplus
}
#endif

//! @}
#endif //__gpmi_h_
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
