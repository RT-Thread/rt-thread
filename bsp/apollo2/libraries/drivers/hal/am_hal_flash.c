//*****************************************************************************
//
//  am_hal_flash.c
//! @file
//!
//! @brief Functions for performing Flash operations.
//!
//! @addtogroup flash2 Flash
//! @ingroup apollo2hal
//!
//! IMPORTANT: Interrupts are active during execution of all HAL flash
//! functions. If an interrupt occurs during execution of a flash function
//! that programs or erases flash or INFO space, errors will occur if the
//! interrupt service routine (ISR) is located in on-chip flash.
//! If interrupts are expected during execution of a flash function that
//! programs or erases either flash or INFO space:
//! - Interrupts must be disabled via a critical section handler prior to
//!   calling the flash function.
//! - Alternatively, applicable ISRs must be located in non-flash address space
//!   (i.e. SRAM, off-chip ROM, etc.).
//!
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

//
// Look-up table
//
g_am_hal_flash_t g_am_hal_flash =
{
    //
    // The basics.
    //
    // flash_mass_erase()
    ((int  (*) (uint32_t, uint32_t)) 0x0800004d),
    // flash_page_erase()
    ((int  (*) (uint32_t, uint32_t, uint32_t))  0x08000051),
    // flash_program_main()
    ((int  (*) (uint32_t, uint32_t *, uint32_t *, uint32_t))  0x08000055),
    // flash_program_info()
    ((int  (*) (uint32_t, uint32_t, uint32_t *, uint32_t, uint32_t)) 0x08000059),

    //
    // Non-blocking variants, but be careful these are not interrupt safe so
    // mask interrupts while these very long operations proceed.
    //
    // flash_mass_erase_nb()
    ((int      (*)(uint32_t, uint32_t)) 0x0800006d),
    // flash_page_erase_nb()
    ((int      (*)(uint32_t, uint32_t, uint32_t)) 0x08000071),
    // flash_nb_operation_complete()
    ((bool     (*)(void)) 0x0800007d),

    //
    // Essentially these are recovery options.
    //
    // flash_erase_info()
    ((int      (*)(uint32_t, uint32_t)) 0x08000081),
    // flash_erase_main_plus_info()
    ((int      (*)(uint32_t, uint32_t)) 0x08000089),
    // flash_erase_main_plus_info_both_instances()
    ((int      (*)(uint32_t)) 0x08000091),
    // flash_recovery()
    ((void     (*)(uint32_t)) 0x08000099),

    //
    // Useful utilities.
    //
    // flash_util_read_word()
    ((uint32_t (*)(uint32_t*)) 0x08000075),
    // flash_util_write_word()
    ((void     (*)(uint32_t*, uint32_t)) 0x08000079),
    // delay_cycles()
    ((void     (*)(uint32_t)) 0x0800009d),

    //
    // The following functions pointers must never be called from user
    // programs. They are here primarily to document these entry points
    // which are usable from a debugger or debugger script.
    //
    // flash_program_main_sram()
    ((void (*) (void))  0x0800005d),
    // flash_program_info_sram()
    ((void (*) (void))  0x08000061),
    // flash_erase_main_pages_sram()
    ((void (*) (void))  0x08000065),
    // flash_mass_erase_sram()
    ((void (*) (void))  0x08000069),
    // flash_erase_info_sram()
    ((void     (*)(void)) 0x08000085),
    // flash_erase_main_plus_info_sram()
    ((void     (*)(void)) 0x0800008d)
};

//*****************************************************************************
//
//! @brief This function performs a mass erase on a flash instance.
//!
//! @param ui32Value - The flash program key.
//! @param ui32FlashInst - The flash instance to erase.
//!
//! This function will erase the desired instance of flash.
//!
//! @note For Apollo2, each flash instance contains a maximum of 512KB.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return 0 for success, non-zero for failure.
//
//*****************************************************************************
int
am_hal_flash_mass_erase(uint32_t ui32Value, uint32_t ui32FlashInst)
{
    return g_am_hal_flash.flash_mass_erase(ui32Value, ui32FlashInst);
}

//*****************************************************************************
//
//! @brief This function performs a page erase on a flash instance.
//!
//! @param ui32Value - The flash program key.
//! @param ui32FlashInst - The flash instance to reference the page number with.
//! @param ui32PageNum - The flash page relative to the specified instance.
//!
//! This function will erase the desired flash page in the desired instance of
//! flash.
//!
//! @note For Apollo2, each flash page is 8KB (or AM_HAL_FLASH_PAGE_SIZE).
//! Each flash instance contains a maximum of 64 pages (or
//! AM_HAL_FLASH_INSTANCE_PAGES).
//!
//! @note When given an absolute flash address, a couple of helpful macros can
//! be utilized when calling this function.
//! For example:
//!     am_hal_flash_page_erase(AM_HAL_FLASH_PROGRAM_KEY,
//!                             AM_HAL_FLASH_ADDR2INST(ui32Addr),
//!                             AM_HAL_FLASH_ADDR2PAGE(ui32Addr) );
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return 0 for success, non-zero for failure.
//
//*****************************************************************************
int
am_hal_flash_page_erase(uint32_t ui32Value, uint32_t ui32FlashInst,
                        uint32_t ui32PageNum)
{
    return g_am_hal_flash.flash_page_erase(ui32Value,
                                           ui32FlashInst,
                                           ui32PageNum);
}

//*****************************************************************************
//
//! @brief This programs up to N words of the Main array on one flash instance.
//!
//! @param ui32Value - The programming key, AM_HAL_FLASH_PROGRAM_KEY.
//! @param pui32Src - Pointer to word aligned array of data to program into
//! the flash instance.
//! @param pui32Dst - Pointer to the word aligned flash location where
//! programming of the flash instance is to begin.
//! @param ui32NumWords - The number of words to be programmed.
//!
//! This function will program multiple words in main flash.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return 0 for success, non-zero for failure.
//
//*****************************************************************************
int
am_hal_flash_program_main(uint32_t ui32Value, uint32_t *pui32Src,
                          uint32_t *pui32Dst, uint32_t ui32NumWords)
{
    return g_am_hal_flash.flash_program_main(ui32Value, pui32Src,
                                             pui32Dst, ui32NumWords);
}

//*****************************************************************************
//
//! @brief This function programs multiple words in the customer INFO space.
//!
//! @param ui32Value - The customer INFO space key.
//! @param ui32InfoInst - The INFO space instance, 0 or 1.
//! @param *pui32Src - Pointer to word aligned array of data to program into
//! the customer INFO space.
//! @param ui32Offset - Word offset into customer INFO space (offset of 0 is
//! the first word, 1 is second word, etc.).
//! @param ui32NumWords - The number of words to be programmed, must not
//! exceed AM_HAL_FLASH_INFO_SIZE/4.
//!
//! This function will program multiple words in the customer INFO space.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return 0 for success, non-zero for failure.
//
//*****************************************************************************
int
am_hal_flash_program_info(uint32_t ui32Value, uint32_t ui32InfoInst,
                          uint32_t *pui32Src, uint32_t ui32Offset,
                          uint32_t ui32NumWords)
{
    return g_am_hal_flash.flash_program_info(ui32Value, 0, pui32Src,
                                             ui32Offset, ui32NumWords);
}

//*****************************************************************************
//
//! @brief This function erases an instance of the customer INFO space.
//!
//! @param ui32ProgramKey - The customer INFO space programming key
//! (AM_HAL_FLASH_PROGRAM_KEY).
//! @param ui32Inst - The flash instance, either 0 or 1.
//!
//! This function will erase the the customer INFO space of the specified
//! instance.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return 0 for success, non-zero for failure.
//
//*****************************************************************************
int
am_hal_flash_erase_info(uint32_t ui32ProgramKey,
                        uint32_t ui32Inst)
{
    return g_am_hal_flash.flash_erase_info(ui32ProgramKey, ui32Inst);
}

//*****************************************************************************
//
//! @brief This function erases the main instance + the customer INFO space.
//!
//! @param ui32ProgramKey - The customer INFO space key.
//! @param ui32Inst      - The flash instance, either 0 or 1.
//!
//! This function will erase the main flash + the customer INFO space of the
//! specified instance.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return 0 for success, non-zero for failure.
//
//*****************************************************************************
int
am_hal_flash_erase_main_plus_info(uint32_t ui32ProgramKey,
                                  uint32_t ui32Inst)
{
    return g_am_hal_flash.flash_erase_main_plus_info(ui32ProgramKey,
                                                     ui32Inst);
}

//*****************************************************************************
//
//! @brief This function erases the main flash + the customer INFO space.
//!
//! @param ui32ProgramKey - The customer INFO space key.
//!
//! This function will erase both instances the main flash + the
//! customer INFO space.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return 0 for success, non-zero for failure.
//
//*****************************************************************************
int
am_hal_flash_erase_main_plus_info_both_instances(uint32_t ui32ProgramKey)
{
    return g_am_hal_flash.flash_erase_main_plus_info_both_instances(
                                                               ui32ProgramKey);
}

//*****************************************************************************
//
//! @brief This function erases both main flash instances + both customer INFO
//! space instances.
//!
//! @param ui32RecoveryKey - The recovery key.
//!
//! This function erases both main instances and both customer INFOinstances
//! even if the customer INFO space is programmed to not be erasable. This
//! function completely erases the flash main and info instances and wipes the
//! SRAM. Upon completion of the erasure operations, it does a POI (power on
//! initialization) reset.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return Never Returns!!!
//
//*****************************************************************************
void
am_hal_flash_recovery(uint32_t ui32RecoveryKey)
{
    g_am_hal_flash.flash_recovery(ui32RecoveryKey);
}

//*****************************************************************************
//
//! @brief Return ui32 value obtained from anywhere in D Code or System Bus
//!
//! @param ui32Address - return the value corresponding to this location.
//!
//! Use this function to read a value from various peripheral locations
//! that must be read from code running external to flash.
//!
//! @return the value found
//
//*****************************************************************************
uint32_t
am_hal_flash_load_ui32(uint32_t ui32Address)
{
    return g_am_hal_flash.flash_util_read_word((uint32_t*)ui32Address);
}

//*****************************************************************************
//
//! @brief Use the bootrom to write to a location in SRAM or the system bus.
//!
//! @param ui32Address - Store the data value corresponding to this location.
//! @param ui32Data    - 32-bit Data to be stored.
//!
//! Use this function to store a value to various peripheral or SRAM locations
//! that can not be touched from code running in SRAM or FLASH.  There is no
//! known need for this function in Apollo2 at this time.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_flash_store_ui32(uint32_t ui32Address, uint32_t ui32Data)
{
    g_am_hal_flash.flash_util_write_word((uint32_t*)ui32Address,
                                                ui32Data);
}

//*****************************************************************************
//
//! @brief Use the bootrom to implement a spin loop.
//!
//! @param ui32Iterations - Number of iterations to delay.
//!
//! Use this function to implement a CPU busy waiting spin loop without cache
//! or delay uncertainties.
//!
//! Note that the ROM-based function executes at 3 cycles per iteration plus
//! the regular function call, entry, and exit overhead.
//! The call and return overhead, including the call to this function, is
//! somewhere in the neighborhood of 14 cycles, or 4.7 iterations.
//!
//! Example:
//! - MCU operating at 48MHz -> 20.83 ns / cycle
//! - Therefore each iteration (once inside the bootrom function) will consume
//!   62.5ns.
//! - The total overhead (assuming 14 cycles) is 292ns.
//! - For ui32Iterations=28: Total delay time = 0.292 + (0.0625 * 28) = 2.04us.
//!
//! The FLASH_CYCLES_US(n) macro can be used with am_hal_flash_delay() to
//! get an approximate microsecond delay.
//! e.g. For a 2us delay, use:
//!      am_hal_flash_delay( FLASH_CYCLES_US(2) );
//!
//! @note Interrupts are active during execution of this function.  Therefore,
//! any interrupt taken will affect the delay timing.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_flash_delay(uint32_t ui32Iterations)
{
    g_am_hal_flash.delay_cycles(ui32Iterations);
}

//*****************************************************************************
//
//! @brief Delays for a desired amount of cycles while also waiting for a
//! status change.
//!
//! @param ui32usMaxDelay - Maximum number of ~1uS delay loops.
//! @param ui32Address    - Address of the register for the status change.
//! @param ui32Mask       - Mask for the status change.
//! @param ui32Value      - Target value for the status change.
//!
//! This function will delay for approximately the given number of microseconds
//! while checking for a status change, exiting when either the given time has
//! expired or the status change is detected.
//!
//! @returns 0 = timeout.
//!          1 = status change detected.
//
//*****************************************************************************
uint32_t
am_hal_flash_delay_status_change(uint32_t ui32usMaxDelay, uint32_t ui32Address,
                                 uint32_t ui32Mask, uint32_t ui32Value)
{
    while ( ui32usMaxDelay-- )
    {
        //
        // Check the status
        //
        if ( ( AM_REGVAL(ui32Address) & ui32Mask ) == ui32Value )
        {
            return 1;
        }

        //
        // Call the BOOTROM cycle function to delay for about 1 microsecond.
        //
        am_hal_flash_delay( FLASH_CYCLES_US(1) );
    }

    return 0;
} // am_hal_flash_delay_status_change()

//*****************************************************************************
//
//! @brief Static Helper Function to check customer info valid bits erasure.
//!
//! Use this function to test the state of the 128 valid bits at the beginning
//! of customer info space. If these are all erased then return true.
//!
//! @return true if the customer info bits are currently erased.
//
//*****************************************************************************
static bool
customer_info_signature_erased(void)
{
    uint32_t *pui32Signature = (uint32_t *) AM_HAL_FLASH_INFO_ADDR;

    return ( (pui32Signature[3] == 0xFFFFFFFF)  &&
             (pui32Signature[2] == 0xFFFFFFFF)  &&
             (pui32Signature[1] == 0xFFFFFFFF)  &&
             (pui32Signature[0] == 0xFFFFFFFF) ) ? true : false;
}

//*****************************************************************************
//
//! @brief Static Helper Function to set customer info valid bits
//!
//! Use this function to set the state of the 128 valid bits at the beginning
//! of customer info space. If these bits are not set correctly then the
//! customer protection bits in the INFO space will not be honored by the
//! hardware.
//!
//! @return Zero for success. Non-Zero for errors.
//
//*****************************************************************************
static int
customer_info_signature_set(void)
{
    uint32_t ui32Valid[4];
    int iRC;

    //
    // If they are already set then we are done.
    //
    if ( am_hal_flash_customer_info_signature_check() )
    {
        return 0;
    }

    //
    // If they are not erased at this point we have an error.
    //
    if ( !customer_info_signature_erased() )
    {
        return (2 << 16);
    }

    //
    // OK they need to be set so do it.
    //
    ui32Valid[3] = AM_HAL_FLASH_INFO_SIGNATURE3;
    ui32Valid[2] = AM_HAL_FLASH_INFO_SIGNATURE2;
    ui32Valid[1] = AM_HAL_FLASH_INFO_SIGNATURE1;
    ui32Valid[0] = AM_HAL_FLASH_INFO_SIGNATURE0;

    iRC = g_am_hal_flash.flash_program_info(AM_HAL_FLASH_PROGRAM_KEY,
                                            0,         // instance
                                            ui32Valid, // source data
                                            0,         // offset
                                            4);        // number of words
    return iRC | ((iRC) ? (1 << 16) : 0);
}

//*****************************************************************************
//
//! @brief Check that the customer info bits are valid.
//!
//! Use this function to test the state of the 128 valid bits at the beginning
//! of customer info space. If these are not set correctly then the customer
//! protection bits in the INFO space will not be honored by the hardware.
//!
//! @return true if valid.
//
//*****************************************************************************
bool
am_hal_flash_customer_info_signature_check(void)
{
    uint32_t *pui32Signature = (uint32_t *)AM_HAL_FLASH_INFO_ADDR;

    return ( (pui32Signature[3] == AM_HAL_FLASH_INFO_SIGNATURE3)    &&
             (pui32Signature[2] == AM_HAL_FLASH_INFO_SIGNATURE2)    &&
             (pui32Signature[1] == AM_HAL_FLASH_INFO_SIGNATURE1)    &&
             (pui32Signature[0] == AM_HAL_FLASH_INFO_SIGNATURE0) );
}

//*****************************************************************************
//
//! @brief INFO signature set.
//!
//! Use this function to set the state of the 128 valid bits at the beginning
//! of customer info space, if needed.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return Zero for success. Non-Zero for errors.
//
//*****************************************************************************
bool
am_hal_flash_info_signature_set(void)
{
    //
    // Check and set signature.
    //
    return customer_info_signature_set() ? false : true;
}

//*****************************************************************************
//
//! @brief Disable FLASH INFO space.
//!
//! Use this function to set the state of the 128 valid bits at the beginning
//! of customer info space, if needed. Then disable FLASH erasure.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return Zero for success. Non-Zero for errors.
//
//*****************************************************************************
int32_t
am_hal_flash_info_erase_disable(void)
{
    int iRC;
    uint32_t ui32SecurityValue;

    //
    // Security protection only works if the signature data is correct.
    //
    iRC = customer_info_signature_set();
    if ( iRC )
    {
        return iRC;
    }

    //
    // Clear bit in INFO space to disable erasure.
    //
    ui32SecurityValue = AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR)  &
                        ~AM_HAL_FLASH_INFO_SECURITY_ENINFOERASE_M;

    //
    // Now write the word to the flash INFO space.
    //
    return g_am_hal_flash.flash_program_info(
            AM_HAL_FLASH_PROGRAM_KEY,
            0,                                  // instance
            &ui32SecurityValue,                 // source data
            AM_HAL_FLASH_INFO_SECURITY_O / 4,   // word offset
            1 );                                // number of words
}

//*****************************************************************************
//
//! @brief Check for Disabled FLASH INFO space.
//!
//! Use this function to determine whether FLASH INFO erasure is disabled.
//!
//! @return true if FLASH INFO erase is disabled, otherwise false.
//
//*****************************************************************************
bool
am_hal_flash_info_erase_disable_check(void)
{
    //
    // If they are erased at this point then SRAM wipe can't be enabled.
    //
    if ( customer_info_signature_erased() )
    {
        return false;
    }

    //
    // If they are not valid at this point then SRAM wipe can't be enabled.
    //
    if ( !am_hal_flash_customer_info_signature_check() )
    {
        return false;
    }

    //
    // Looking good so far, now check the SRAM WIPE bit.
    //
    return AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR)   &
                     AM_HAL_FLASH_INFO_SECURITY_ENINFOERASE_M  ? false : true;
}

//*****************************************************************************
//
//! @brief Mask off 1 to 4 quadrants of FLASH INFO space for programming.
//!
//! Use this function to set the state of the 128 valid bits at the beginning
//! of customer info space, if needed. Then and the mask bits with the INFO
//! space programming disable bits.
//!
//! @param ui32Mask - A mask of the 4 quadrants of info space where
//!                   bit0 = First quadrant (first 2KB).
//!                   bit1 = Second quadrant (second 2KB).
//!                   bit2 = Third quadrant (third 2KB).
//!                   bit3 = Fourth quadrant (fourth 2KB).
//!
//! @note This function disables only, any quadrant already disabled is not
//! reenabled.  That is, any ui32Mask bits specified as 0 are essentially nops.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return Zero for success. Non-Zero for errors.
//
//*****************************************************************************
int32_t
am_hal_flash_info_program_disable(uint32_t ui32Mask)
{
    int iRC;
    uint32_t ui32SecurityValue;

    //
    // Security protection only works if the signature data is correct.
    //
    iRC = customer_info_signature_set();
    if ( iRC )
    {
        return iRC;
    }

    //
    // Make sure we have a valid mask and get the mask into the correct position.
    //
    ui32Mask <<= AM_HAL_FLASH_INFO_SECURITY_ENINFOPRGM_S;
    ui32Mask &= AM_HAL_FLASH_INFO_SECURITY_ENINFOPRGM_M;

    //
    // The security bit set to 1 enables programming, 0 disables programming.
    //
    ui32SecurityValue = AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR) & ~ui32Mask;

    //
    // Now write the word to the flash INFO space.
    //
    return g_am_hal_flash.flash_program_info(
            AM_HAL_FLASH_PROGRAM_KEY,
            0,                                  // instance
            &ui32SecurityValue,                 // source data
            AM_HAL_FLASH_INFO_SECURITY_O / 4,   // word offset
            1 );                                // number of words
}

//*****************************************************************************
//
//! @brief Return a mask specifying which quadrants of customer INFO space have
//! been disabled for programming.
//!
//! Use this function to determine whether programming of customer INFO space
//! has been disabled.
//!
//! @return A 4-bit mask of the disabled quadrants.
//! 0xFFFFFFFF indicates an error.
//! 0x0  indicates all customer INFO space programming is enabled.
//! 0xF  indicates all customer INFO space programming is disabled.
//! bit0 indicates the first customer INFO space is disabled for programming.
//! bit1 indicates the second customer INFO space is disabled for programming.
//! bit2 indicates the third customer INFO space is disabled for programming.
//! bit3 indicates the fourth customer INFO space is disabled for programming.
//
//*****************************************************************************
uint32_t
am_hal_flash_info_program_disable_get(void)
{
    //
    // If they are erased at this point then SRAM wipe can't be enabled.
    //
    if ( customer_info_signature_erased() )
    {
        return 0xFFFFFFFF;
    }

    //
    // If not valid at this point, then INFO programming can't be enabled.
    //
    if ( !am_hal_flash_customer_info_signature_check() )
    {
        return 0xFFFFFFFF;
    }

    //
    // Looking good so far, now return a mask of the disabled bits.
    //
    return  ((AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR) &
                AM_HAL_FLASH_INFO_SECURITY_ENINFOPRGM_M) ^
                AM_HAL_FLASH_INFO_SECURITY_ENINFOPRGM_M) >>
                AM_HAL_FLASH_INFO_SECURITY_ENINFOPRGM_S;
}

//*****************************************************************************
//
//! @brief Enable FLASH debugger protection (FLASH gets wiped if a debugger is
//! connected).
//!
//! Use this function to set the state of the 128 valid bits at the beginning
//! of customer info space, if needed. Then set the FLASH wipe bit to zero.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return Zero for success. Non-Zero for errors.
//
//*****************************************************************************
int32_t
am_hal_flash_wipe_flash_enable(void)
{
    int iRC;
    uint32_t ui32SecurityValue;

    //
    // Security protection only works if the signature data is correct.
    //
    iRC = customer_info_signature_set();
    if ( iRC )
    {
        return iRC;
    }

    //
    // Clear the FLASH Wipe bit.
    //
    ui32SecurityValue = AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR) &
                        ~AM_HAL_FLASH_INFO_SECURITY_FLASHWIPE_M;

    //
    // Now write the word to the flash INFO space.
    //
    return g_am_hal_flash.flash_program_info(
            AM_HAL_FLASH_PROGRAM_KEY,
            0,                                  // instance
            &ui32SecurityValue,                 // source data
            AM_HAL_FLASH_INFO_SECURITY_O / 4,   // word offset
            1 );                                // number of words
}

//*****************************************************************************
//
//! @brief check for FLASH wipe protection enabled.
//!
//! Use this function to determine if FLASH wipe protection is enabled.
//!
//! @return true if FLASH wipe protection is enabled, otherwise false.
//
//*****************************************************************************
bool
am_hal_flash_wipe_flash_enable_check(void)
{
    //
    // If they are erased at this point then flash wipe can't be enabled.
    //
    if ( customer_info_signature_erased() )
    {
        return false;
    }

    //
    // If they are not valid at this point then flash wipe can't be enabled.
    //
    if ( !am_hal_flash_customer_info_signature_check() )
    {
        return false;
    }

    //
    // Looking good so far, now check the Flash WIPE bit.
    //
    return AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR) &
            AM_HAL_FLASH_INFO_SECURITY_FLASHWIPE_M ? false : true;
}

//*****************************************************************************
//
//! @brief Enable SRAM protection so SRAM gets wiped if a debgger is connected.
//!
//! Use this function to set the state of the 128 valid bits at the beginning
//! of customer info space, if needed. Then set the SRAM wipe bit to zero.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return Zero for success. Non-Zero for errors.
//
//*****************************************************************************
int32_t
am_hal_flash_wipe_sram_enable(void)
{
    int iRC;
    uint32_t ui32SecurityValue;

    //
    // Security protection only works if the signature data is correct.
    //
    iRC = customer_info_signature_set();
    if ( iRC )
    {
        return iRC;
    }

    //
    // Clear the SRAM Wipe bit.
    //
    ui32SecurityValue = AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR) &
                        ~AM_HAL_FLASH_INFO_SECURITY_SRAMWIPE_M;

    //
    // Now write the word to the flash INFO space.
    //
    return g_am_hal_flash.flash_program_info(
            AM_HAL_FLASH_PROGRAM_KEY,
            0,                                  // instance
            &ui32SecurityValue,                 // source data
            AM_HAL_FLASH_INFO_SECURITY_O / 4,   // word offset
            1 );                                // number of words
}

//*****************************************************************************
//
//! @brief check for SRAM protection enabled.
//!
//! Use this function to determine if SRAM protection is enabled.
//!
//! @return true if SRAM wipe protection is enabled, otherwise false.
//
//*****************************************************************************
bool
am_hal_flash_wipe_sram_enable_check(void)
{
    //
    // If they are erased at this point then SRAM wipe can't be enabled.
    //
    if ( customer_info_signature_erased() )
    {
        return false;
    }

    //
    // If they are not vale at this point then SRAM wipe can't be enabled.
    //
    if ( !am_hal_flash_customer_info_signature_check() )
    {
        return false;
    }

    //
    // Looking good so far, now check the SRAM WIPE bit.
    //
    return AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR) &
            AM_HAL_FLASH_INFO_SECURITY_SRAMWIPE_M ? false : true;
}

//*****************************************************************************
//
//! @brief Disable Output from ITM/SWO.
//!
//! Use this function to set the state of the 128 valid bits at the beginning
//! of customer info space, if needed. Set the SWO disable bit to zero.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return Zero for success. Non-Zero for errors.
//
//*****************************************************************************
int32_t
am_hal_flash_swo_disable(void)
{
    int iRC;
    uint32_t ui32SecurityValue;

    //
    // Security protection only works if the signature data is correct.
    //
    iRC = customer_info_signature_set();
    if ( iRC )
    {
        return iRC;
    }

    //
    // Clear the SWO bit.
    //
    ui32SecurityValue = AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR) &
                        ~AM_HAL_FLASH_INFO_SECURITY_SWOCTRL_M;

    //
    // Now write the word to the flash INFO space.
    //
    return g_am_hal_flash.flash_program_info(
            AM_HAL_FLASH_PROGRAM_KEY,
            0,                                  // instance
            &ui32SecurityValue,                 // source data
            AM_HAL_FLASH_INFO_SECURITY_O / 4,   // word offset
            1 );                                // number of words
}

//*****************************************************************************
//
//! @brief check for SWO disabled.
//!
//! Use this function to determine if the SWO is disabled.
//!
//! @return true if the ITM/SWO is disabled, otherwise false.
//
//*****************************************************************************
bool
am_hal_flash_swo_disable_check(void)
{
    //
    // If they are erased at this point then SRAM wipe can't be enabled.
    //
    if ( customer_info_signature_erased() )
    {
        return false;
    }

    //
    // If they are not vale at this point then SRAM wipe can't be enabled.
    //
    if ( !am_hal_flash_customer_info_signature_check() )
    {
        return false;
    }

    //
    // Looking good so far, now check the SWO bit.
    //
    return AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR) &
            AM_HAL_FLASH_INFO_SECURITY_SWOCTRL_M ? false : true;
}

//*****************************************************************************
//
//! @brief Disable Connections from a debugger on the SWD interface.
//!
//! Use this function to set the state of the 128 valid bits at the beginning
//! of customer info space, if needed. Set the debugger disable bit to zero.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return Zero for success. Non-Zero for errors.
//
//*****************************************************************************
int32_t
am_hal_flash_debugger_disable(void)
{
    int iRC;
    uint32_t ui32SecurityValue;

    //
    // Security protection only works if the signature data is correct.
    //
    iRC = customer_info_signature_set();
    if ( iRC )
    {
        return iRC;
    }

    //
    // Clear the DEBUGGER bit.
    //
    ui32SecurityValue = AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR) &
                        ~AM_HAL_FLASH_INFO_SECURITY_DEBUGGERPROT_M;

    //
    // Now write the word to the flash INFO space.
    //
    return g_am_hal_flash.flash_program_info(
            AM_HAL_FLASH_PROGRAM_KEY,
            0,                                  // instance
            &ui32SecurityValue,                 // source data
            AM_HAL_FLASH_INFO_SECURITY_O / 4,   // word offset
            1 );                                // number of words
}

//*****************************************************************************
//
//! @brief check for debugger disabled.
//!
//! Use this function to determine if the debugger is disabled.
//!
//! @return true if the debugger is disabled, otherwise false.
//
//*****************************************************************************
bool
am_hal_flash_debugger_disable_check(void)
{
    //
    // If they are erased at this point then SRAM wipe can't be enabled.
    //
    if ( customer_info_signature_erased() )
    {
        return false;
    }

    //
    // If they are not vale at this point then SRAM wipe can't be enabled.
    //
    if ( !am_hal_flash_customer_info_signature_check() )
    {
        return false;
    }

    //
    // Looking good so far, now check the debugger disable bit.
    //
    return AM_REGVAL(AM_HAL_FLASH_INFO_SECURITY_ADDR) &
            AM_HAL_FLASH_INFO_SECURITY_DEBUGGERPROT_M ? false : true;
}

//*****************************************************************************
//
//! @brief This static helper function generates a 64-bit protection mask.
//!
//! @param pui32StartAddress - Starting address in flash to begin protection.
//! @param pui32StopAddress  - Ending address in flash to stop protection.
//!
//! This function computes a chunk map for the protection range.
//!
//! @return Inverse of the actual chunk mask.  That is, chunks to be protected
//! are represented as 0 in the returned mask, while chunks to be left alone
//! are represented as 1.  This value can therefore be directly ANDed with the
//! existing bits in INFO space.
//! Note that -1 is returned if input parameters are invalid - this return
//! value would indicate that no chunks are to be protected.
//!
//
//*****************************************************************************
static uint64_t
generate_chunk_mask(uint32_t *pui32StartAddress, uint32_t *pui32StopAddress)
{
    uint32_t ui32ChunkStart, ui32ChunkStop;
    uint32_t ui32Width;
    uint64_t ui64Mask;

    //
    // Validate the address input parameters
    //
    if ( (pui32StartAddress > pui32StopAddress)  ||
         (pui32StopAddress > (uint32_t*)AM_HAL_FLASH_LARGEST_VALID_ADDR) )
    {
        //
        // Argument error, return value to leave all chunks unprotected.
        //
        return 0xFFFFFFFFFFFFFFFF;
    }

    //
    // Extract chunk related information
    //
    ui32ChunkStart = AM_HAL_FLASH_INFO_ADDR2CHUNK((uint32_t)pui32StartAddress);
    ui32ChunkStop  = AM_HAL_FLASH_INFO_ADDR2CHUNK((uint32_t)pui32StopAddress);
    ui32Width = ui32ChunkStop - ui32ChunkStart + 1;

    if ( ui32Width == 64 )
    {
        ui64Mask = (uint64_t)0xFFFFFFFFFFFFFFFFLLU;
    }
    else
    {
        ui64Mask = ( ((uint64_t)0x0000000000000001) << ui32Width) - 1;
        ui64Mask <<= ui32ChunkStart;
    }

    //
    // OK now return the chunk mask (inverted).
    //
    return ~ui64Mask;
}

//*****************************************************************************
//
//! @brief This function sets copy protection for a range of flash chunks.
//!
//! @param pui32StartAddress - Starting address in flash to begin protection.
//! @param pui32StopAddress - Ending address in flash to stop protection.
//!
//! This function will set copy protection bits for a range of flash chunks
//!
//! @note Each flash chunk contains 16KBytes and corresponds to one bit in
//! the protection register. Set the bit to zero to enable protection.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return
//!     0 for success.
//!     0x400000 if the protection bits were already programmed (mask the return
//!              value with 0x3FFFFF to ignore this case and treat as success).
//!     Otherwise, non-zero for failure.
//
//*****************************************************************************
int32_t
am_hal_flash_copy_protect_set(uint32_t *pui32StartAddress,
                              uint32_t *pui32StopAddress)
{
    int iRC;
    bool bModified = false;
    uint64_t ui64Mask;
    uint32_t ui32Work;
    uint32_t ui32Protection[2];
    uint32_t *pui32Protection = (uint32_t *)AM_HAL_FLASH_INFO_COPYPROT_ADDR;

    //
    // Extract chunk mask from parameters.
    // Also checks parameter validity (returns -1 if bad parameters).
    //
    ui64Mask = generate_chunk_mask(pui32StartAddress, pui32StopAddress);
    if ( ~ui64Mask == 0x0 )
    {
        return 0x100000;
    }

    //
    // Go get the current settings for copy protection.
    //
    ui32Protection[0] = pui32Protection[0];
    ui32Protection[1] = pui32Protection[1];

    //
    // AND mask off the necessary protection bits in the lower word.
    //
    ui32Work = (uint32_t)ui64Mask;
    if ( ( ~ui32Work )  &&  ( ui32Work != ui32Protection[0] ) )
    {
        bModified = true;
        ui32Protection[0] &= ui32Work;
        iRC = g_am_hal_flash.flash_program_info(
                AM_HAL_FLASH_PROGRAM_KEY,
                0,                                      // instance
                &ui32Protection[0],                     // source data
                (AM_HAL_FLASH_INFO_COPYPROT_O / 4) + 0, // word offset
                1 );                                    // number of words

        if ( iRC )
        {
            return iRC | 0x10000;
        }
    }

    //
    // AND mask off the necessary protection bits in the upper word.
    //
    ui32Work = (uint32_t)(ui64Mask >> 32);
    if ( ( ~ui32Work )  &&  ( ui32Work != ui32Protection[1] ) )
    {
        bModified = true;
        ui32Protection[1] &= ui32Work;
        iRC = g_am_hal_flash.flash_program_info(
                AM_HAL_FLASH_PROGRAM_KEY,
                0,                                      // instance
                &ui32Protection[1],                     // source data
                (AM_HAL_FLASH_INFO_COPYPROT_O / 4) + 1, // word offset
                1 );                                    // number of words

        if ( iRC )
        {
            return iRC | 0x20000;
        }
    }

    if ( bModified )
    {
        return 0;
    }
    else
    {
        return 0x400000;
    }
}

//*****************************************************************************
//
//! @brief This function checks copy protection for a range of flash chunks.
//!
//! @param pui32StartAddress - Starting address in flash.
//! @param pui32StopAddress - Ending address in flash.
//!
//! This function will check copy protection bits for a range of flash chunks
//! it expects all chunks in the range to be protected.
//!
//! @note Each flash chunk contains 16KBytes and corresponds to one bit in
//! the protection register. Set the bit to zero to enable protection.
//!
//! @return false for at least one chunk in the covered range is not protected,
//!         and true if all chunks in the covered range are protected.
//!
//
//*****************************************************************************
bool
am_hal_flash_copy_protect_check(uint32_t *pui32StartAddress,
                                uint32_t *pui32StopAddress)
{
    uint64_t ui64Mask;
    uint32_t ui32Work;
    uint32_t *pui32Protection = (uint32_t *)AM_HAL_FLASH_INFO_COPYPROT_ADDR;

    //
    // Extract chunk mask from parameters.
    // Also checks parameter validity (returns -1 if bad parameters).
    //
    ui64Mask = generate_chunk_mask(pui32StartAddress, pui32StopAddress);
    if ( ~ui64Mask == 0x0 )
    {
        return false;
    }

    //
    // Now check the lower word of protection bits.
    //
    ui32Work = (uint32_t)ui64Mask;
    if ( ~ui32Work  &  pui32Protection[0] )
    {
        return false;
    }

    //
    // Now check the lower word of protection bits.
    //
    ui32Work = (uint32_t)(ui64Mask >> 32);
    if ( ~ui32Work & pui32Protection[1] )
    {
        return false;
    }

    //
    // If we get here, there are no unprotected chunks within specified range.
    //
    return true;
}

//*****************************************************************************
//
//! @brief This function sets write protection for a range of flash chunks.
//!
//! @param pui32StartAddress - Starting address in flash to begin protection.
//! @param pui32StopAddress - Ending address in flash to stop protection.
//!
//! This function will set write protection bits for a range of flash chunks
//!
//! @note Each flash chunk contains 16KBytes and corresponds to one bit in
//! the protection register. Set the bit to zero to enable protection.
//!
//! @note Interrupts are active during execution of this function. Any interrupt
//! taken could cause execution errors. Please see the IMPORTANT note under
//! Detailed Description above for more details.
//!
//! @return
//!     0 for success.
//!     0x400000 if the protection bits were already programmed (mask the return
//!              value with 0x3FFFFF to ignore this case and treat as success).
//!     Otherwise, non-zero for failure.
//
//*****************************************************************************
int32_t
am_hal_flash_write_protect_set(uint32_t *pui32StartAddress,
                               uint32_t *pui32StopAddress)
{
    int iRC;
    bool bModified = false;
    uint64_t ui64Mask;
    uint32_t ui32Work;
    uint32_t ui32Protection[2];
    uint32_t *pui32Protection = (uint32_t *)AM_HAL_FLASH_INFO_WRITPROT_ADDR;

    //
    // Extract chunk mask from parameters.
    // Also checks parameter validity (returns -1 if bad parameters).
    //
    ui64Mask = generate_chunk_mask(pui32StartAddress, pui32StopAddress);
    if ( ~ui64Mask == 0x0 )
    {
        return 0x100000;
    }

    //
    // Go get the current settings for copy protection.
    //
    ui32Protection[0] = pui32Protection[0];
    ui32Protection[1] = pui32Protection[1];

    //
    // AND mask off the necessary protection bits in the lower word.
    //
    ui32Work = (uint32_t)ui64Mask;
    if ( ( ~ui32Work )  &&  ( ui32Work != ui32Protection[0] ) )
    {
        bModified = true;
        ui32Protection[0] &= ui32Work;
        iRC = g_am_hal_flash.flash_program_info(
                AM_HAL_FLASH_PROGRAM_KEY,
                0,                                      // instance
                &ui32Protection[0],                     // source data
                (AM_HAL_FLASH_INFO_WRITPROT_O / 4) + 0, // word offset
                1 );                                    // number of words

        if ( iRC )
        {
            return iRC | 0x10000;
        }
    }

    //
    // AND mask off the necessary protection bits in the upper word.
    //
    ui32Work = (uint32_t)(ui64Mask >> 32);
    if ( ( ~ui32Work )  &&  ( ui32Work != ui32Protection[1] ) )
    {
        bModified = true;
        ui32Protection[1] &= ui32Work;
        iRC = g_am_hal_flash.flash_program_info(
                AM_HAL_FLASH_PROGRAM_KEY,
                0,                                      // instance
                &ui32Protection[1],                     // source data
                (AM_HAL_FLASH_INFO_WRITPROT_O / 4) + 1, // word offset
                1 );                                    // number of words

        if ( iRC )
        {
            return iRC | 0x20000;
        }
    }

    if ( bModified )
    {
        return 0;
    }
    else
    {
        return 0x400000;
    }
}

//*****************************************************************************
//
//! @brief This function checks write protection for a range of flash chunks.
//!
//! @param pui32StartAddress - Starting address in flash.
//! @param pui32StopAddress - Ending address in flash.
//!
//! This function will check write protection bits for a range of flash chunks
//! it expects all chunks in the range to be protected.
//!
//! @note Each flash chunk contains 16KBytes and corresponds to one bit in
//! the protection register. Set the bit to zero to enable protection.
//!
//! @return false for at least one chunk in the covered range is not protected,
//!         and true if all chunks in the covered range are protected.
//!
//
//*****************************************************************************
bool
am_hal_flash_write_protect_check(uint32_t *pui32StartAddress,
                                 uint32_t *pui32StopAddress)
{
    uint64_t ui64Mask;
    uint32_t ui32Work;
    uint32_t *pui32Protection = (uint32_t *)AM_HAL_FLASH_INFO_WRITPROT_ADDR;

    //
    // Extract chunk mask from parameters.
    // Also checks parameter validity (returns -1 if bad parameters).
    //
    ui64Mask = generate_chunk_mask(pui32StartAddress, pui32StopAddress);
    if ( ~ui64Mask == 0x0 )
    {
        return false;
    }

    //
    // Now check the lower word of protection bits.
    //
    ui32Work = (uint32_t)ui64Mask;
    if ( ~ui32Work & pui32Protection[0] )
    {
        return false;
    }

    //
    // Now check the lower word of protection bits.
    //
    ui32Work = (uint32_t)(ui64Mask >> 32);
    if ( ~ui32Work & pui32Protection[1] )
    {
        return false;
    }

    //
    // If we get here, there are no unprotected chunks within specified range.
    //
    return true;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
