//*****************************************************************************
//
//  am_hal_ios.c
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

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

//*****************************************************************************
//
// SRAM Buffer structure
//
//*****************************************************************************
typedef struct
{
    uint8_t           *pui8Data;
    volatile uint32_t ui32WriteIndex;
    volatile uint32_t ui32ReadIndex;
    volatile uint32_t ui32Length;
    uint32_t          ui32FifoInc;
    uint32_t          ui32Capacity;
}
am_hal_ios_buffer_t;

am_hal_ios_buffer_t g_sSRAMBuffer;

//*****************************************************************************
//
// Forward declarations of static funcitons.
//
//*****************************************************************************
static void am_hal_ios_buffer_init(am_hal_ios_buffer_t *psBuffer,
                                   void *pvArray, uint32_t ui32Bytes);

static void fifo_write(uint8_t *pui8Data, uint32_t ui32NumBytes);

//*****************************************************************************
//
// Function-like macros.
//
//*****************************************************************************
#define am_hal_ios_buffer_empty(psBuffer)                                   \
    ((psBuffer)->ui32Length == 0)

#define am_hal_ios_buffer_full(psBuffer)                                    \
    ((psBuffer)->ui32Length == (psBuffer)->ui32Capacity)

#define am_hal_ios_buffer_data_left(psBuffer)                               \
    ((psBuffer)->ui32Length)

//*****************************************************************************
//
// Global Variables
//
//*****************************************************************************
volatile uint8_t * const am_hal_ios_pui8LRAM = (uint8_t *)REG_IOSLAVE_BASEADDR;
uint8_t *g_pui8FIFOBase = (uint8_t *) REG_IOSLAVE_BASEADDR;
uint8_t *g_pui8FIFOEnd = (uint8_t *) REG_IOSLAVE_BASEADDR;
uint8_t *g_pui8FIFOPtr = (uint8_t *) REG_IOSLAVE_BASEADDR;
uint8_t g_ui32HwFifoSize = 0;
uint32_t g_ui32FifoBaseOffset = 0;

//*****************************************************************************
//
// Checks to see if this processor is a Rev B2 device.
//
// This is needed to disable SHELBY-1654 workaround.
//
//*****************************************************************************
bool
isRevB2(void)
{
    //
    // Check to make sure the major rev is B and the minor rev is 2.
    //
    return ( (AM_REG(MCUCTRL, CHIPREV) & 0xFF) ==   \
        (AM_REG_MCUCTRL_CHIPREV_REVMAJ_B | (AM_REG_MCUCTRL_CHIPREV_REVMIN_REV0 + 2)) );
}

//*****************************************************************************
//
//! @brief Enable the IOS in the power control block.
//!
//! This function enables the IOS module in the power control block.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_pwrctrl_enable(void)
{
    am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_IOS);
}

//*****************************************************************************
//
//! @brief Disable the IOS in the power control block.
//!
//! This function disables the IOS module in the power control block.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_pwrctrl_disable(void)
{
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_IOS);
}

//*****************************************************************************
//
//! @brief Enables the IOS module
//!
//! This function enables the IOSLAVE module using the IFCEN bitfield in the
//! IOSLAVE_CFG register.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_enable(uint32_t ui32Module)
{
    AM_REGn(IOSLAVE, ui32Module, CFG) |= AM_REG_IOSLAVE_CFG_IFCEN(1);
}

//*****************************************************************************
//
//! @brief Disables the IOSLAVE module.
//!
//! This function disables the IOSLAVE module using the IFCEN bitfield in the
//! IOSLAVE_CFG register.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_disable(uint32_t ui32Module)
{
    AM_REGn(IOSLAVE, ui32Module, CFG) &= ~(AM_REG_IOSLAVE_CFG_IFCEN(1));
}

//*****************************************************************************
//
//! @brief Configure the IOS module.
//!
//! This function reads the an \e am_hal_ios_config_t structure and uses it to
//! set up the IO Slave module. Please see the information on the configuration
//! structure for more information on the parameters that may be set by this
//! function.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_config(am_hal_ios_config_t *psConfig)
{
    uint32_t ui32LRAMConfig;

    am_hal_pwrctrl_periph_enable(AM_HAL_PWRCTRL_IOS);

    //
    // Record the FIFO parameters for later use.
    //
    g_pui8FIFOBase = (uint8_t *)(REG_IOSLAVE_BASEADDR + psConfig->ui32FIFOBase);
    g_pui8FIFOEnd = (uint8_t *)(REG_IOSLAVE_BASEADDR + psConfig->ui32RAMBase);
    g_ui32HwFifoSize = g_pui8FIFOEnd - g_pui8FIFOBase;
    g_ui32FifoBaseOffset = psConfig->ui32FIFOBase;

    //
    // Caluclate the value for the IO Slave FIFO configuration register.
    //
    ui32LRAMConfig = AM_REG_IOSLAVE_FIFOCFG_ROBASE(psConfig->ui32ROBase >> 3);
    ui32LRAMConfig |= AM_REG_IOSLAVE_FIFOCFG_FIFOBASE(psConfig->ui32FIFOBase >> 3);
    ui32LRAMConfig |= AM_REG_IOSLAVE_FIFOCFG_FIFOMAX(psConfig->ui32RAMBase >> 3);

    //
    // Just in case, disable the IOS
    //
    am_hal_ios_disable(0);

    //
    // Write the configuration register with the user's selected interface
    // characteristics.
    //
    AM_REG(IOSLAVE, CFG) = psConfig->ui32InterfaceSelect;

    //
    // Write the FIFO configuration register to set the memory map for the LRAM.
    //
    AM_REG(IOSLAVE, FIFOCFG) = ui32LRAMConfig;

    //
    // Enable the IOS. The following configuration options can't be set while
    // the IOS is disabled.
    //
    am_hal_ios_enable(0);

    //
    // Initialize the FIFO pointer to the beginning of the FIFO section.
    //
    am_hal_ios_fifo_ptr_set(psConfig->ui32FIFOBase);

    //
    // Write the FIFO threshold register.
    //
    AM_REG(IOSLAVE, FIFOTHR) = psConfig->ui32FIFOThreshold;
}

//*****************************************************************************
//
//! @brief Set bits in the HOST side IOINTCTL register.
//!
//! This function may be used to set an interrupt bit to the host.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_host_int_set(uint32_t ui32Interrupt)
{
    //
    // Set a bit that will cause an interrupt to the host.
    //
    AM_REG(IOSLAVE, IOINTCTL) = AM_REG_IOSLAVE_IOINTCTL_IOINTSET(ui32Interrupt);
}

//*****************************************************************************
//
//! @brief Clear bits in the HOST side IOINTCTL register.
//!
//! This function may be used to clear an interrupt bit to the host.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_host_int_clear(uint32_t ui32Interrupt)
{
    //
    // Clear bits that will cause an interrupt to the host.
    //
    AM_REG(IOSLAVE, IOINTCTL) = AM_REG_IOSLAVE_IOINTCTL_IOINTCLR(ui32Interrupt);
}

//*****************************************************************************
//
//! @brief Get the bits in the HOST side IOINTCTL register.
//!
//! This function may be used to read the host side interrupt bits.
//!
//! @return None.
//
//*****************************************************************************
uint32_t
am_hal_ios_host_int_get(void)
{
    //
    // return the value of the bits that will cause an interrupt to the host.
    //
    return AM_BFR(IOSLAVE, IOINTCTL, IOINT);
}

//*****************************************************************************
//
//! @brief Get the enable bits in the HOST side IOINTCTL register.
//!
//! This function may be used to read the host side interrupt bits.
//!
//! @return None.
//
//*****************************************************************************
uint32_t
am_hal_ios_host_int_enable_get(void)
{
    //
    // return the value of the bits that will cause an interrupt to the host.
    //
    return AM_BFR(IOSLAVE, IOINTCTL, IOINTEN);
}

//*****************************************************************************
//
//! @brief Enable an IOS Access Interrupt.
//!
//! This function may be used to enable an interrupt to the NVIC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_access_int_enable(uint32_t ui32Interrupt)
{
    //
    // OR the desired interrupt into the enable register.
    //
    AM_REG(IOSLAVE, REGACCINTEN) |= ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Return all enabled IOS Access Interrupts.
//!
//! This function may be used to return all enabled IOS Access interrupts.
//!
//! @return the enabled interrrupts.
//
//*****************************************************************************
uint32_t
am_hal_ios_access_int_enable_get(void)
{
    //
    // Return the enabled interrupts.
    //
    return AM_REG(IOSLAVE, REGACCINTEN);
}

//*****************************************************************************
//
//! @brief Disable an IOS Access Interrupt.
//!
//! This function may be used to disable an interrupt to the NVIC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_access_int_disable(uint32_t ui32Interrupt)
{
    //
    // Clear the desired bit from the interrupt enable register.
    //
    AM_REG(IOSLAVE, REGACCINTEN) &= ~(ui32Interrupt);
}

//*****************************************************************************
//
//! @brief Clear an IOS Access Interrupt.
//!
//! This function may be used to clear an interrupt to the NVIC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_access_int_clear(uint32_t ui32Interrupt)
{
    //
    // Use the interrupt clear register to deactivate the chosen interrupt.
    //
    AM_REG(IOSLAVE, REGACCINTCLR) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Set an IOS Access Interrupt.
//!
//! This function may be used to set an interrupt to the NVIC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_access_int_set(uint32_t ui32Interrupt)
{
    //
    // Use the interrupt set register to activate the chosen interrupt.
    //
    AM_REG(IOSLAVE, REGACCINTSET) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Check the status of an IOS Access Interrupt.
//!
//! @param bEnabledOnly - return only the enabled interrupt status.
//!
//! This function may be used to return the enabled interrupt status.
//!
//! @return the enabled interrupt status.
//
//*****************************************************************************
uint32_t
am_hal_ios_access_int_status_get(bool bEnabledOnly)
{
    if ( bEnabledOnly )
    {
        uint32_t u32RetVal = AM_REG(IOSLAVE, REGACCINTSTAT);
        return u32RetVal & AM_REG(IOSLAVE, REGACCINTEN);

    }
    else
    {
        return AM_REG(IOSLAVE, REGACCINTSTAT);
    }
}

//*****************************************************************************
//
//! @brief Enable an IOS Interrupt.
//!
//! @param ui32Interrupt - desired interrupts.
//!
//! This function may be used to enable an interrupt to the NVIC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_int_enable(uint32_t ui32Interrupt)
{
    //
    // OR the desired interrupt into the enable register.
    //
    AM_REG(IOSLAVE, INTEN) |= ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Return all enabled IOS Interrupts.
//!
//! This function may be used to return all enabled IOS interrupts.
//!
//! @return the enabled interrrupts.
//
//*****************************************************************************
uint32_t
am_hal_ios_int_enable_get(void)
{
    //
    // Return the enabled interrupts.
    //
    return AM_REG(IOSLAVE, INTEN);
}

//*****************************************************************************
//
//! @brief Disable an IOS Interrupt.
//!
//! @param ui32Interrupt - desired interrupts.
//!
//! This function may be used to disable an interrupt to the NVIC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_int_disable(uint32_t ui32Interrupt)
{
    //
    // Clear the desired bit from the interrupt enable register.
    //
    AM_REG(IOSLAVE, INTEN) &= ~(ui32Interrupt);
}

//*****************************************************************************
//
//! @brief Clear an IOS Interrupt.
//!
//! @param ui32Interrupt - desired interrupts.
//!
//! This function may be used to clear an interrupt to the NVIC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_int_clear(uint32_t ui32Interrupt)
{
    //
    // Use the interrupt clear register to deactivate the chosen interrupt.
    //
    AM_REG(IOSLAVE, INTCLR) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Set an IOS Interrupt.
//!
//! @param ui32Interrupt - desired interrupts.
//!
//! This function may be used to set an interrupt to the NVIC.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_int_set(uint32_t ui32Interrupt)
{
    //
    // Use the interrupt clear register to deactivate the chosen interrupt.
    //
    AM_REG(IOSLAVE, INTSET) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Write to the LRAM.
//!
//! @param ui32Offset - offset into the LRAM to write.
//! @param ui8Value - value to be written.
//!
//! This function writes ui8Value to offset ui32Offset inside the LRAM.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_lram_write(uint32_t ui32Offset, uint8_t ui8Value)
{
    //
    // Write the LRAM.
    //
    am_hal_ios_pui8LRAM[ui32Offset] = ui8Value;
}

//*****************************************************************************
//
//! @brief Read from the LRAM.
//!
//! @param ui32Offset - offset into the LRAM to read.
//!
//! This function read from offset ui32Offset inside the LRAM.
//!
//! @return the value at ui32Offset.
//
//*****************************************************************************
uint8_t
am_hal_ios_lram_read(uint32_t ui32Offset)
{
    //
    // Read the LRAM.
    //
    return am_hal_ios_pui8LRAM[ui32Offset];
}

//*****************************************************************************
//
//! @brief Check the status of an IOS Interrupt.
//!
//! @param bEnabledOnly - return only the enabled interrupt status.
//!
//! This function may be used to return the enabled interrupt status.
//!
//! @return the enabled interrupt status.
//
//*****************************************************************************
uint32_t
am_hal_ios_int_status_get(bool bEnabledOnly)
{
    if ( bEnabledOnly )
    {
        uint32_t u32RetVal = AM_REG(IOSLAVE, INTSTAT);
        return u32RetVal & AM_REG(IOSLAVE, INTEN);

    }
    else
    {
        return AM_REG(IOSLAVE, INTSTAT);
    }
}

//*****************************************************************************
//
//! @brief Check the amount of space used in the FIFO
//!
//! This function returns the available data in the overall FIFO yet to be
//! read by the host. This takes into account the SRAM buffer and hardware FIFO
//!
//! @return Bytes used in the Overall FIFO.
//
//*****************************************************************************
uint32_t
am_hal_ios_fifo_space_used(void)
{
    uint32_t ui32Val;
    uint32_t ui32Primask;
    //
    // Start a critical section for thread safety.
    //
    ui32Primask = am_hal_interrupt_master_disable();
    ui32Val = g_sSRAMBuffer.ui32Length;
    ui32Val += AM_BFR(IOSLAVE, FIFOPTR, FIFOSIZ);
    //
    // End the critical section
    //
    am_hal_interrupt_master_set(ui32Primask);
    return ui32Val;
}



//*****************************************************************************
//
//! @brief Check the amount of space left in the FIFO
//!
//! This function returns the available space in the overall FIFO to accept
//! new data. This takes into account the SRAM buffer and hardware FIFO
//!
//! @return Bytes left in the Overall FIFO.
//
//*****************************************************************************
uint32_t
am_hal_ios_fifo_space_left(void)
{
    uint32_t ui32Val;
    uint32_t ui32Primask;
    //
    // Start a critical section for thread safety.
    //
    ui32Primask = am_hal_interrupt_master_disable();
    //
    // We waste one byte in HW FIFO
    //
    ui32Val = g_sSRAMBuffer.ui32Capacity + g_ui32HwFifoSize - 1;
    ui32Val -= g_sSRAMBuffer.ui32Length;
    ui32Val -= AM_BFR(IOSLAVE, FIFOPTR, FIFOSIZ);
    //
    // End the critical section
    //
    am_hal_interrupt_master_set(ui32Primask);
    return ui32Val;
}

//*****************************************************************************
//
//! @brief Check the amount of space left in the hardware FIFO
//!
//! This function reads the IOSLAVE FIFOPTR register and determines the amount
//! of space left in the IOS LRAM FIFO.
//!
//! @return Bytes left in the IOS FIFO.
//
//*****************************************************************************
static uint32_t
fifo_space_left(void)
{
    //
    // We waste one byte in HW FIFO
    //
    return ((uint32_t)g_ui32HwFifoSize- AM_BFR(IOSLAVE, FIFOPTR, FIFOSIZ) - 1);
}

//*****************************************************************************
//
// Helper function for managing IOS FIFO writes.
//
//*****************************************************************************
static void
fifo_write(uint8_t *pui8Data, uint32_t ui32NumBytes)
{
    uint8_t *pFifoPtr = g_pui8FIFOPtr;
    uint8_t *pFifoBase = g_pui8FIFOBase;
    uint8_t *pFifoEnd = g_pui8FIFOEnd;
    while ( ui32NumBytes )
    {
        //
        // Write the data to the FIFO
        //
        *pFifoPtr++ = *pui8Data++;
        ui32NumBytes--;

        //
        // Make sure to wrap the FIFO pointer if necessary.
        //
        if ( pFifoPtr == pFifoEnd )
        {
            pFifoPtr = pFifoBase;
        }
    }
    g_pui8FIFOPtr = pFifoPtr;
}

//
// Assembly code below assumes 8bit FIFOSIZ field aligned at a byte boundary
//
#if (((AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_M >> AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_S) != 0xFF) \
        || (AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_S & 0x3))
#error "FIFOSIZ not 8bit value aligned at byte offset"
#endif

//
// Byte offset of FIFOSIZ field in FIFOPTR register
//
#define BYTEOFFSET_FIFOSIZE             (AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_S >> 3)

//*****************************************************************************
//
// Helper function in assembly for implementing the ReSync
//
//*****************************************************************************
#if defined(__GNUC_STDC_INLINE__)
#if (AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_S != 8)
#error "AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_S not 8"
#endif
__attribute__((naked))
static void
internal_resync_fifoSize(uint32_t wrOffset, uint32_t maxFifoSize, uint32_t hwFifoPtrRegAddr)
{
    __asm
    (
        "   push    {r3,r4}\n\t"                  // Save r3, r4 - used by this function
        "__internal_resync_fifoSize_loop:\n\t"
        "   ldr     r4, [r2]\n\t"                 // Load FIFOPTR register in r4
        "   ubfx    r3, r4, #8, #8\n\t"           // Extract hwFifoSize to r3
        "   uxtb    r4, r4\n\t"                   // Extract rdOffset in r4
        "   subs    r4, r0, r4\n\t"               // fifoSize in r4 = wrOffset - rdOffset
        "   it      cc\n\t"                       // if (wrOffset < rdOffset)
        "   addcc   r4, r4, r1\n\t"               //     fifoSize = maxFifoSize - (rdOffset - wrOffset)
        "   cmp     r3, r4\n\t"                   // (hwFifoSize != fifoSize)
        "   beq     __internal_resync_fifosize_done\n\t"
        "   strb    r4, [r2, #1]\n\t"             // Overwrite FIFOSIZ value with fifoSize
        "   b       __internal_resync_fifoSize_loop\n\t" // Repeat the check
        "__internal_resync_fifosize_done:\n\t"
        "   pop     {r3,r4}\n\t"                  // Restore registers
        "   bx      lr\n\t"
    );
}

#elif defined(__ARMCC_VERSION)
__asm static void
internal_resync_fifoSize(uint32_t wrOffset, uint32_t maxFifoSize, uint32_t hwFifoPtrRegAddr)
{
    push    {r3, r4}                 // Save r3, r4 - used by this function
internal_resync_fifoSize_loop
    ldr     r4, [r2]                 // Load FIFOPTR register in r4
    ubfx    r3, r4, #AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_S, #8 // Extract hwFifoSize to r3
    uxtb    r4, r4                   // Extract rdOffset in r4
    subs    r4, r0, r4               // fifoSize in r4 = wrOffset - rdOffset
    it      cc                       // if (wrOffset < rdOffset),
    addcc   r4, r4, r1               //     fifoSize = maxFifoSize - (rdOffset - wrOffset)
    cmp     r3, r4                   // (hwFifoSize != fifoSize)
    beq     internal_resync_fifosize_done
    strb    r4, [r2, #1]             // Overwrite FIFOSIZ value with fifoSize
    b       internal_resync_fifoSize_loop // Repeat the check
internal_resync_fifosize_done
    pop     {r3, r4}                 // Restore registers
    bx      lr
}

#elif defined(__IAR_SYSTEMS_ICC__)
#if (AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_S != 8)
#error "AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_S not 8"
#endif
__stackless static void
internal_resync_fifoSize(uint32_t wrOffset, uint32_t maxFifoSize, uint32_t hwFifoPtrRegAddr)
{
    __asm volatile (
          "    push    {r3,r4}\n"                  // Save r3, r4 - used by this function
          "__internal_resync_fifoSize_loop:\n"
          "    ldr     r4, [r2]\n"                 // Load FIFOPTR register in r4
          "    ubfx    r3, r4, #8, #8\n"           // Extract hwFifoSize to r3
          "    uxtb    r4, r4\n"                   // Extract rdOffset in r4
          "    subs    r4, r0, r4\n"               // fifoSize in r4 = wrOffset - rdOffset
          "    it      cc\n"
          "    addcc   r4, r4, r1\n"               //     fifoSize = maxFifoSize - (rdOffset - wrOffset)
          "    cmp     r3, r4\n"                   // (fifoSize != hwFifoSize)
          "    beq     __internal_resync_fifosize_done\n"
          "    strb    r4, [r2, #1]\n"             // Overwrite FIFOSIZ value with fifoSize
          "    b       __internal_resync_fifoSize_loop\n" // Repeat the check
          "__internal_resync_fifosize_done:\n"
          "    pop     {r3,r4}\n"                  // Restore registers
          "    bx      lr\n"
          );
}

#else
static void
internal_resync_fifoSize(uint32_t wrOffset, uint32_t maxFifoSize, uint32_t hwFifoPtrRegAddr)
{
    uint32_t fifoSize;
    uint32_t hwFifoPtrReg;
    uint32_t rdOffset;
    uint32_t hwFifoSize;

    hwFifoPtrReg = AM_REGVAL(hwFifoPtrRegAddr);
    rdOffset = ((hwFifoPtrReg & AM_REG_IOSLAVE_FIFOPTR_FIFOPTR_M) >> AM_REG_IOSLAVE_FIFOPTR_FIFOPTR_S);
    hwFifoSize = (hwFifoPtrReg & AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_M) >> AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_S;
    // By wasting one byte in hardware FIFO, we're guaranteed that fifoSize does not need special handling for FULL FIFO case
    fifoSize = ((wrOffset >= rdOffset) ? (wrOffset - rdOffset) : (maxFifoSize - (rdOffset - wrOffset)));
    while ( fifoSize != hwFifoSize )
    {
        // Overwite correct FIFOSIZ
        // Need to do a Byte Write to make sure the FIFOPTR is not overwritten
        *((uint8_t *)(hwFifoPtrRegAddr + BYTEOFFSET_FIFOSIZE)) = fifoSize;
        // Read back the register and check for consistency
        hwFifoPtrReg = AM_REGVAL(hwFifoPtrRegAddr);
        rdOffset = ((hwFifoPtrReg & AM_REG_IOSLAVE_FIFOPTR_FIFOPTR_M) >> AM_REG_IOSLAVE_FIFOPTR_FIFOPTR_S);
        hwFifoSize = (hwFifoPtrReg & AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_M) >> AM_REG_IOSLAVE_FIFOPTR_FIFOSIZ_S;
        // By wasting one byte in hardware FIFO, we're guaranteed that fifoSize does not need special handling for FULL FIFO case
        fifoSize = ((wrOffset >= rdOffset) ? (wrOffset - rdOffset) : (hwFifoSize - (rdOffset - wrOffset)));
    }
}
#endif

//
// Address of the FIFOPTR register
//
#define AM_REG_IOS_FIFOPTR      (REG_IOSLAVE_BASEADDR + AM_REG_IOSLAVE_FIFOPTR_O)

// When the FIFO is being replenished by the SW, at the same time as host is
// reading from it, there is a possible race condition, where the hardware decrement
// of FIFOSIZ as a result of read gets overwritten by hardware increment due to
// write.
// This function re-sync's the FIFOSIZ to ensure such errors do not accumulate
void
resync_fifoSize(void)
{
    uint32_t ui32Primask;
    uint32_t wrOffset = (uint32_t)g_pui8FIFOPtr - (uint32_t)am_hal_ios_pui8LRAM;
    //
    // Start a critical section for thread safety.
    //
    ui32Primask = am_hal_interrupt_master_disable();
    internal_resync_fifoSize(wrOffset, g_ui32HwFifoSize, AM_REG_IOS_FIFOPTR);
    // Clear interrupts for IOS which could be spuriously triggered
    AM_REG(IOSLAVE, REGACCINTCLR) = (AM_HAL_IOS_INT_FSIZE | AM_HAL_IOS_INT_FOVFL | AM_HAL_IOS_INT_FUNDFL);
    //
    // End the critical section
    //
    am_hal_interrupt_master_set(ui32Primask);
    return;
}

//*****************************************************************************
//
//! @brief Transfer any available data from the IOS SRAM buffer to the FIFO.
//!
//! This function is meant to be called from an interrupt handler for the
//! ioslave module. It checks the IOS FIFO interrupt status for a threshold
//! event, and transfers data from an SRAM buffer into the IOS FIFO.
//!
//! @param ui32Status should be set to the ios interrupt status at the time of
//! ISR entry.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_fifo_service(uint32_t ui32Status)
{
    uint32_t thresh;
    uint32_t freeSpace, usedSpace, chunk1, chunk2, ui32WriteIndex;

    //
    // Check for FIFO size interrupts.
    //
    if ( ui32Status & AM_HAL_IOS_INT_FSIZE )
    {
        thresh = AM_BFR(IOSLAVE, FIFOTHR, FIFOTHR);

        //
        // While the FIFO is at or below threshold Add more data
        // If Fifo level is above threshold, we're guaranteed an FSIZ interrupt
        //
        while ( g_sSRAMBuffer.ui32Length &&
                ((usedSpace = AM_BFR(IOSLAVE, FIFOPTR, FIFOSIZ)) <= thresh) )
        {
            //
            // So, we do have some data in SRAM which needs to be moved to FIFO.
            // A chunk of data is a continguous set of bytes in SRAM that can be
            //  written to FIFO. Determine the chunks of data from SRAM that can
            //  be written. Up to two chunks possible
            //
            ui32WriteIndex = g_sSRAMBuffer.ui32WriteIndex;
            chunk1 = ((ui32WriteIndex > (uint32_t)g_sSRAMBuffer.ui32ReadIndex) ?   \
                        (ui32WriteIndex - (uint32_t)g_sSRAMBuffer.ui32ReadIndex) : \
                        (g_sSRAMBuffer.ui32Capacity - (uint32_t)g_sSRAMBuffer.ui32ReadIndex));
            chunk2 = g_sSRAMBuffer.ui32Length - chunk1;
            // We waste one byte in HW FIFO
            freeSpace = g_ui32HwFifoSize - usedSpace - 1;
            // Write data in chunks
            // Determine the chunks of data from SRAM that can be written
            if ( chunk1 > freeSpace )
            {
                fifo_write((uint8_t *)(g_sSRAMBuffer.pui8Data + g_sSRAMBuffer.ui32ReadIndex), freeSpace);
                //
                // Advance the read index, wrapping if needed.
                //
                g_sSRAMBuffer.ui32ReadIndex += freeSpace;
                // No need to check for wrap as we wrote less than chunk1
                //
                // Adjust the length value to reflect the change.
                //
                g_sSRAMBuffer.ui32Length -= freeSpace;
            }
            else
            {
                fifo_write((uint8_t *)(g_sSRAMBuffer.pui8Data + g_sSRAMBuffer.ui32ReadIndex), chunk1);

                //
                // Update the read index - wrapping as needed
                //
                g_sSRAMBuffer.ui32ReadIndex += chunk1;
                g_sSRAMBuffer.ui32ReadIndex %= g_sSRAMBuffer.ui32Capacity;
                //
                // Adjust the length value to reflect the change.
                //
                g_sSRAMBuffer.ui32Length -= chunk1;
                freeSpace -= chunk1;

                if ( freeSpace && chunk2 )
                {
                    if ( chunk2 > freeSpace )
                    {
                        fifo_write((uint8_t *)(g_sSRAMBuffer.pui8Data + g_sSRAMBuffer.ui32ReadIndex), freeSpace);

                        //
                        // Advance the read index, wrapping if needed.
                        //
                        g_sSRAMBuffer.ui32ReadIndex += freeSpace;

                        // No need to check for wrap in chunk2
                        //
                        // Adjust the length value to reflect the change.
                        //
                        g_sSRAMBuffer.ui32Length -= freeSpace;
                    }
                    else
                    {
                        fifo_write((uint8_t *)(g_sSRAMBuffer.pui8Data + g_sSRAMBuffer.ui32ReadIndex), chunk2);
                        //
                        // Advance the read index, wrapping if needed.
                        //
                        g_sSRAMBuffer.ui32ReadIndex += chunk2;

                        // No need to check for wrap in chunk2
                        //
                        // Adjust the length value to reflect the change.
                        //
                        g_sSRAMBuffer.ui32Length -= chunk2;
                    }
                }
            }
            if (!isRevB2())
            {
                resync_fifoSize();
            }

            //
            // Need to retake the FIFO space, after Threshold interrupt has been reenabled
            // Clear any spurious FSIZE interrupt that might have got raised
            //
            AM_BFW(IOSLAVE, INTCLR, FSIZE, 1);
        }
    }
}

//*****************************************************************************
//
//! @brief Writes the specified number of bytes to the IOS fifo.
//!
//! @param pui8Data is a pointer to the data to be written to the fifo.
//! @param ui32NumBytes is the number of bytes to send.
//!
//! This function will write data from the caller-provided array to the IOS
//! LRAM FIFO. If there is no space in the LRAM FIFO, the data will be copied
//! to a temporary SRAM buffer instead.
//!
//! The maximum message size for the IO Slave is 1023 bytes.
//!
//! @note In order for SRAM copy operations in the function to work correctly,
//! the \e am_hal_ios_buffer_service() function must be called in the ISR for
//! the ioslave module.
//!
//! @return Number of bytes written (could be less than ui32NumBytes, if not enough space)
//
//*****************************************************************************
uint32_t
am_hal_ios_fifo_write(uint8_t *pui8Data, uint32_t ui32NumBytes)
{
    uint32_t ui32FIFOSpace;
    uint32_t ui32SRAMSpace;
    uint32_t ui32SRAMLength;
    uint32_t ui32Primask;
    uint32_t totalBytes = ui32NumBytes;

    //
    // This operation will only work properly if an SRAM buffer has been
    // allocated. Make sure that am_hal_ios_fifo_buffer_init() has been called,
    // and the buffer pointer looks valid.
    //
    am_hal_debug_assert(g_sSRAMBuffer.pui8Data != 0);

    if ( ui32NumBytes == 0 )
    {
        return 0;
    }

    //
    // Start a critical section for thread safety.
    //
    ui32Primask = am_hal_interrupt_master_disable();

    ui32SRAMLength = g_sSRAMBuffer.ui32Length;
    //
    // End the critical section
    //
    am_hal_interrupt_master_set(ui32Primask);

    //
    // If the SRAM buffer is empty, we should just write directly to the FIFO.
    //
    if ( ui32SRAMLength == 0 )
    {
        ui32FIFOSpace = fifo_space_left();

        //
        // If the whole message fits, send it now.
        //
        if ( ui32NumBytes <= ui32FIFOSpace )
        {
            fifo_write(pui8Data, ui32NumBytes);
            ui32NumBytes = 0;
        }
        else
        {
            fifo_write(pui8Data, ui32FIFOSpace);
            ui32NumBytes -= ui32FIFOSpace;
            pui8Data += ui32FIFOSpace;
        };
        if (!isRevB2())
        {
            resync_fifoSize();
        }
    }

    //
    // If there's still data, write it to the SRAM buffer.
    //
    if ( ui32NumBytes )
    {
        uint32_t idx, writeIdx, capacity, fifoSize;
        ui32SRAMSpace = g_sSRAMBuffer.ui32Capacity - ui32SRAMLength;

        writeIdx = g_sSRAMBuffer.ui32WriteIndex;
        capacity = g_sSRAMBuffer.ui32Capacity;
        //
        // Make sure that the data will fit inside the SRAM buffer.
        //
        if ( ui32SRAMSpace > ui32NumBytes )
        {
            ui32SRAMSpace = ui32NumBytes;
        }

        //
        // If the data will fit, write it to the SRAM buffer.
        //
        for ( idx = 0; idx < ui32SRAMSpace; idx++ )
        {
            g_sSRAMBuffer.pui8Data[(idx + writeIdx) % capacity] = pui8Data[idx];
        }

        ui32NumBytes -= idx;
        //
        // Start a critical section for thread safety before updating length & wrIdx.
        //
        ui32Primask = am_hal_interrupt_master_disable();
        //
        // Advance the write index, making sure to wrap if necessary.
        //
        g_sSRAMBuffer.ui32WriteIndex = (idx + writeIdx) % capacity;

        //
        // Update the length value appropriately.
        //
        g_sSRAMBuffer.ui32Length += idx;
        //
        // End the critical section
        //
        am_hal_interrupt_master_set(ui32Primask);

        // It is possible that there is a race condition that the FIFO level has
        // gone below the threshold by the time we set the wrIdx above, and hence
        // we may never get the threshold interrupt to serve the SRAM data we
        // just wrote

        // If that is the case, explicitly generate the FSIZE interrupt from here
        fifoSize = AM_BFR(IOSLAVE, FIFOPTR, FIFOSIZ);
        if ( fifoSize <= AM_BFR(IOSLAVE, FIFOTHR, FIFOTHR) )
        {
            AM_BFW(IOSLAVE, INTSET, FSIZE, 1);
        }
    }

    // Number of bytes written
    g_sSRAMBuffer.ui32FifoInc += totalBytes - ui32NumBytes;
    return (totalBytes - ui32NumBytes);
}

//*****************************************************************************
//
//! @brief Writes the specified number of bytes to the IOS fifo simply.
//!
//! @param pui8Data is a pointer to the data to be written to the fifo.
//! @param ui32NumBytes is the number of bytes to send.
//!
//! This function will write data from the caller-provided array to the IOS
//! LRAM FIFO. This simple routine does not use SRAM buffering for large
//! messages. This function also updates the FIFOCTR.
//!
//! The maximum message size for the IO Slave is 128 bytes.
//!
//! @note Do note call the \e am_hal_ios_buffer_service() function in the ISR for
//! the ioslave module.
//!
//! @return
//
//*****************************************************************************
void
am_hal_ios_fifo_write_simple(uint8_t *pui8Data, uint32_t ui32NumBytes)
{
    uint32_t ui32FIFOSpace;

    //
    // Check the FIFO and the SRAM buffer to see where we have space.
    //
    ui32FIFOSpace = fifo_space_left();

    //
    // If the whole message fits, send it now.
    //
    if ( ui32NumBytes <= ui32FIFOSpace )
    {
        fifo_write(pui8Data, ui32NumBytes);
        // Write FIFOINC
        AM_BFW(IOSLAVE, FIFOINC, FIFOINC, ui32NumBytes);
    }
    else
    {
        //
        // The message didn't fit. Try using am_hal_ios_fifo_write() instead.
        //
        am_hal_debug_assert_msg(0, "The requested IOS transfer didn't fit in"
                                   "the LRAM FIFO. Try using am_hal_ios_fifo_write().");
    }
}

//*****************************************************************************
//
//! @brief Sets the IOS FIFO pointer to the specified LRAM offset.
//!
//! @param ui32Offset is LRAM offset to set the FIFO pointer to.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_fifo_ptr_set(uint32_t ui32Offset)
{
    uint32_t ui32Primask;

    //
    // Start a critical section for thread safety.
    //
    ui32Primask = am_hal_interrupt_master_disable();

    //
    // Set the FIFO Update bit.
    //
    AM_REG(IOSLAVE, FUPD) = 0x1;

    //
    // Change the FIFO offset.
    //
    AM_REG(IOSLAVE, FIFOPTR) = ui32Offset;

    //
    // Clear the FIFO update bit.
    //
    AM_REG(IOSLAVE, FUPD) = 0x0;

    //
    // Set the global FIFO-pointer tracking variable.
    //
    g_pui8FIFOPtr = (uint8_t *) (REG_IOSLAVE_BASEADDR + ui32Offset);

    //
    // End the critical section.
    //
    am_hal_interrupt_master_set(ui32Primask);
}

//*****************************************************************************
//
// Initialize an SRAM buffer for use with the IO Slave.
//
//*****************************************************************************
static void
am_hal_ios_buffer_init(am_hal_ios_buffer_t *psBuffer, void *pvArray,
                       uint32_t ui32Bytes)
{
    psBuffer->ui32WriteIndex = 0;
    psBuffer->ui32ReadIndex = 0;
    psBuffer->ui32Length = 0;
    psBuffer->ui32Capacity = ui32Bytes;
    psBuffer->ui32FifoInc = 0;
    psBuffer->pui8Data = (uint8_t *)pvArray;
}

//*****************************************************************************
//
//! @brief Poll for all host side read activity to complete.
//!
//! Poll for all host side read activity to complete. Use this before
//! calling am_hal_ios_fifo_write_simple().
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_read_poll_complete(void)
{
    while ( AM_REG(IOSLAVE, FUPD) & AM_REG_IOSLAVE_FUPD_IOREAD_M );
}

//*****************************************************************************
//
//! @brief Initializes an SRAM buffer for the IOS FIFO.
//!
//! @param pui8Buffer is the SRAM buffer that will be used for IOS fifo data.
//! @param ui32BufferSize is the size of the SRAM buffer.
//!
//! This function provides the IOS HAL functions with working memory for
//! managing outgoing IOS FIFO transactions. It needs to be called at least
//! once before am_hal_ios_fifo_write() may be used.
//!
//! The recommended buffer size for the IOS FIFO is 1024 bytes.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_fifo_buffer_init(uint8_t *pui8Buffer, uint32_t ui32NumBytes)
{
    //
    // Initialize the global SRAM buffer
    // Total size, which is SRAM Buffer plus the hardware FIFO needs to be
    // limited to 1023
    //
    if ( ui32NumBytes > (1023 - g_ui32HwFifoSize + 1) )
    {
        ui32NumBytes = (1023 - g_ui32HwFifoSize + 1);
    }

    am_hal_ios_buffer_init(&g_sSRAMBuffer, pui8Buffer, ui32NumBytes);

    //
    // Clear the FIFO State
    //
    AM_BFW(IOSLAVE, FIFOCTR, FIFOCTR, 0x0);
    AM_BFW(IOSLAVE, FIFOPTR, FIFOSIZ, 0x0);

    am_hal_ios_fifo_ptr_set(g_ui32FifoBaseOffset);
}

//*****************************************************************************
//
//! @brief Update the FIFOCTR to inform host of available data to read.
//!
//! This function allows the application to indicate to HAL when it is safe to
//! update the FIFOCTR. This function needs to be used in conjunction with
//! am_hal_ios_fifo_write(), which itself does not update the FIFOCTR
//!
//! CAUTION:
//! Application needs to implement some sort of
//! synchronization with the host to make sure host is not reading FIFOCTR while
//! it is being updated by the MCU, since the FIFOCTR read over
//! IO is not an atomic operation. Otherwise, some other logic could be implemented
//! by the host to detect and disregard transient values of FIFOCTR (e.g. multiple
//! reads till it gets a stable value).
//! For Pre-B2 parts, it is necessary to have this synchronization guarantee that
//! Host is not doing any READ operation - be it for FIFOCTR or FIFO itself when
//! this call is made, as otherwise the FIFOCTR value may get corrupted.
//!
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_ios_update_fifoctr(void)
{
    // Write FIFOINC
    AM_BFW(IOSLAVE, FIFOINC, FIFOINC, g_sSRAMBuffer.ui32FifoInc);
    g_sSRAMBuffer.ui32FifoInc = 0;
    return;
}

//*****************************************************************************
//
//  End the doxygen group
//! @}
//
//*****************************************************************************
