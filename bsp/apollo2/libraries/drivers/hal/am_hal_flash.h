//*****************************************************************************
//
//  am_hal_flash.h
//! @file
//!
//! @brief Functions for performing Flash operations.
//!
//! @addtogroup flash2 Flash
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
#ifndef AM_HAL_FLASH_H
#define AM_HAL_FLASH_H

#include <stdint.h>
#include <stdbool.h>

//*****************************************************************************
//
// Flash Program keys.
//
//*****************************************************************************
#define AM_HAL_FLASH_PROGRAM_KEY            0x12344321
#define AM_HAL_FLASH_RECOVERY_KEY           0xA35C9B6D
#define AM_HAL_FLASH_INFO_KEY               0x12344321
#define AM_HAL_FLASH_OTP_KEY                (AM_HAL_FLASH_INFO_KEY)

//*****************************************************************************
//
// Some helpful flash values and macros.
//
//*****************************************************************************
#define AM_HAL_FLASH_ADDR                   0x00000000
#define AM_HAL_FLASH_PAGE_SIZE              ( 8 * 1024 )
#define AM_HAL_FLASH_INFO_SIZE              AM_HAL_FLASH_PAGE_SIZE
#define AM_HAL_FLASH_INSTANCE_SIZE          ( 512 * 1024 )
#define AM_HAL_FLASH_INSTANCE_PAGES         ( AM_HAL_FLASH_INSTANCE_SIZE / AM_HAL_FLASH_PAGE_SIZE )
#define AM_HAL_FLASH_TOTAL_SIZE             ( AM_HAL_FLASH_INSTANCE_SIZE * 2 )
#define AM_HAL_FLASH_LARGEST_VALID_ADDR     ( AM_HAL_FLASH_ADDR + AM_HAL_FLASH_TOTAL_SIZE - 1 )

//
// Convert an absolute flash address to a instance
//
#define AM_HAL_FLASH_ADDR2INST(addr)        ( ( addr >> 19 ) & 1 )

//
// Convert an absolute flash address to a page number relative to the instance
//
#define AM_HAL_FLASH_ADDR2PAGE(addr)        ( ( addr >> 13 ) & 0x3F )

//
// Convert an absolute flash address to an absolute page number
//
#define AM_HAL_FLASH_ADDR2ABSPAGE(addr)     ( addr >> 13 )

//*****************************************************************************
//
// Given an integer number of microseconds, convert to a value representing the
// number of am_hal_flash_delay() cycles that will provide that amount of delay.
// This macro is designed to take into account some of the call overhead.
//
// e.g. To provide a 2us delay:
//  am_hal_flash_delay( FLASH_CYCLES_US(2) );
//
// IMPORTANT - Apollo2 is spec'ed for only 48MHz operation, so this macro
// assumes that.
//
//*****************************************************************************
#define FLASH_CYCLES_US(n)      ((n * (AM_HAL_CLKGEN_FREQ_MAX_MHZ / 3)) - 4)

//
// Backward compatibility
//
#define am_hal_flash_program_otp        am_hal_flash_program_info
#define am_hal_flash_program_otp_sram   am_hal_flash_program_info_sram

//*****************************************************************************
//
// Structure of function pointers to helper functions for invoking various
// flash operations. The functions we are pointing to here are in the Apollo 2
// integrated BOOTROM.
//
//*****************************************************************************
typedef struct am_hal_flash_helper_struct
{
    //
    // The basics.
    //
    int      (*flash_mass_erase)(uint32_t, uint32_t);
    int      (*flash_page_erase)(uint32_t, uint32_t, uint32_t);
    int      (*flash_program_main)(uint32_t,  uint32_t *,
                                          uint32_t*, uint32_t);
    int      (*flash_program_info)(uint32_t,   uint32_t,
                                         uint32_t*,  uint32_t, uint32_t);

    //
    // Non-blocking variants, but be careful these are not interrupt safe so
    // mask interrupts while these very long operations proceed.
    //
    int      (*flash_mass_erase_nb)(uint32_t, uint32_t);
    int      (*flash_page_erase_nb)(uint32_t, uint32_t, uint32_t);
    bool     (*flash_nb_operation_complete)(void);

    //
    // Essentially these are recovery options.
    //
    int      (*flash_erase_info)(uint32_t, uint32_t);
    int      (*flash_erase_main_plus_info)(uint32_t, uint32_t);
    int      (*flash_erase_main_plus_info_both_instances)(uint32_t);
    void     (*flash_recovery)(uint32_t);

    //
    // Useful utilities.
    //
    uint32_t (*flash_util_read_word)(uint32_t*);
    void     (*flash_util_write_word)(uint32_t*, uint32_t);
    void     (*delay_cycles)(uint32_t);

    //
    // The following functions pointers will generally never be called from
    // user programs. They are here primarily to document these entry points
    // which are usable from a debugger or debugger script.
    //
    void     (*flash_program_main_sram)(void);
    void     (*flash_program_info_sram)(void);
    void     (*flash_erase_main_pages_sram)(void);
    void     (*flash_mass_erase_sram)(void);
    void     (*flash_erase_info_sram)(void);
    void     (*flash_erase_main_plus_info_sram)(void);
} g_am_hal_flash_t;
extern g_am_hal_flash_t g_am_hal_flash;


//*****************************************************************************
//
// Define some FLASH INFO SPACE values and macros.
//
//*****************************************************************************
#define AM_HAL_FLASH_INFO_ADDR              0x50020000
#define AM_HAL_FLASH_INFO_SECURITY_O        0x10
#define AM_HAL_FLASH_INFO_WRITPROT_O        0x20
#define AM_HAL_FLASH_INFO_COPYPROT_O        0x30

#define AM_HAL_FLASH_INFO_SECURITY_ADDR     (AM_HAL_FLASH_INFO_ADDR + AM_HAL_FLASH_INFO_SECURITY_O)
#define AM_HAL_FLASH_INFO_WRITPROT_ADDR     (AM_HAL_FLASH_INFO_ADDR + AM_HAL_FLASH_INFO_WRITPROT_O)
#define AM_HAL_FLASH_INFO_COPYPROT_ADDR     (AM_HAL_FLASH_INFO_ADDR + AM_HAL_FLASH_INFO_COPYPROT_O)

//
// Define the customer info signature data (at AM_HAL_FLASH_INFO_ADDR).
// These bits must exist in the customer info space in order for many of the
// security and protection functions to work.
//
#define AM_HAL_FLASH_INFO_SIGNATURE0        0x48EAAD88
#define AM_HAL_FLASH_INFO_SIGNATURE1        0xC9705737
#define AM_HAL_FLASH_INFO_SIGNATURE2        0x0A6B8458
#define AM_HAL_FLASH_INFO_SIGNATURE3        0xE41A9D74

//
// Define the customer security bits (at AM_HAL_FLASH_INFO_SECURITY_ADDR)
//
#define AM_HAL_FLASH_INFO_SECURITY_DEBUGGERPROT_S       0
#define AM_HAL_FLASH_INFO_SECURITY_SWOCTRL_S            1
#define AM_HAL_FLASH_INFO_SECURITY_SRAMWIPE_S           2
#define AM_HAL_FLASH_INFO_SECURITY_FLASHWIPE_S          3
#define AM_HAL_FLASH_INFO_SECURITY_ENINFOPRGM_S         4
#define AM_HAL_FLASH_INFO_SECURITY_ENINFOERASE_S        8
#define AM_HAL_FLASH_INFO_SECURITY_BOOTLOADERSPIN_S     9

#define AM_HAL_FLASH_INFO_SECURITY_DEBUGGERPROT_M       ((uint32_t)(0x1 << AM_HAL_FLASH_INFO_SECURITY_DEBUGGERPROT_S))
#define AM_HAL_FLASH_INFO_SECURITY_SWOCTRL_M            ((uint32_t)(0x1 << AM_HAL_FLASH_INFO_SECURITY_SWOCTRL_S))
#define AM_HAL_FLASH_INFO_SECURITY_SRAMWIPE_M           ((uint32_t)(0x1 << AM_HAL_FLASH_INFO_SECURITY_SRAMWIPE_S))
#define AM_HAL_FLASH_INFO_SECURITY_FLASHWIPE_M          ((uint32_t)(0x1 << AM_HAL_FLASH_INFO_SECURITY_FLASHWIPE_S))
#define AM_HAL_FLASH_INFO_SECURITY_ENINFOPRGM_M         ((uint32_t)(0xF << AM_HAL_FLASH_INFO_SECURITY_ENINFOPRGM_S))
#define AM_HAL_FLASH_INFO_SECURITY_ENINFOERASE_M        ((uint32_t)(0x1 << AM_HAL_FLASH_INFO_SECURITY_ENINFOERASE_S))
#define AM_HAL_FLASH_INFO_SECURITY_BOOTLOADERSPIN_M     ((uint32_t)(0x1 << AM_HAL_FLASH_INFO_SECURITY_BOOTLOADERSPIN_S))
#define AM_HAL_FLASH_INFO_SECURITY_DEEPSLEEP_M          ((uint32_t)(0x1 << AM_HAL_FLASH_INFO_SECURITY_BOOTLOADERSPIN_S))
#define AM_HAL_FLASH_INFO_SECURITY_DEEPSLEEP            ((uint32_t)(0x0 << AM_HAL_FLASH_INFO_SECURITY_BOOTLOADERSPIN_S))

//
// Protection chunk macros
// AM_HAL_FLASH_INFO_CHUNK2ADDR: Convert a chunk number to an address
// AM_HAL_FLASH_INFO_CHUNK2INST: Convert a chunk number to an instance number
// AM_HAL_FLASH_INFO_ADDR2CHUNK: Convert an address to a chunk number
//
#define AM_HAL_FLASH_INFO_CHUNKSIZE         (16*1024)

#define AM_HAL_FLASH_INFO_CHUNK2ADDR(n)     (AM_HAL_FLASH_ADDR + (n << 14))
#define AM_HAL_FLASH_INFO_CHUNK2INST(n)     ((n >> 5) & 1
#define AM_HAL_FLASH_INFO_ADDR2CHUNK(n)     ((n) >> 14)

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Function prototypes for the helper functions
//
//*****************************************************************************
extern int am_hal_flash_mass_erase(uint32_t ui32Value, uint32_t ui32FlashInst);
extern int am_hal_flash_page_erase(uint32_t ui32Value, uint32_t ui32FlashInst,
                                   uint32_t ui32PageNum);
extern int am_hal_flash_program_main(uint32_t value, uint32_t *pSrc,
                                     uint32_t *pDst, uint32_t  NumberOfWords);
extern int am_hal_flash_program_info(uint32_t ui32Value, uint32_t ui32InfoInst,
                                     uint32_t *pui32Src, uint32_t ui32Offset,
                                     uint32_t ui32NumWords);

//
// Recovery type functions for Customer INFO space.
//
extern int      am_hal_flash_erase_info(uint32_t ui32ProgramKey,
                                        uint32_t ui32Instance);
extern int      am_hal_flash_erase_main_plus_info(uint32_t ui32ProgramKey,
                                                  uint32_t ui32Instance);
extern int      am_hal_flash_erase_main_plus_info_both_instances(
                                                  uint32_t ui32ProgramKey);
extern void     am_hal_flash_recovery(uint32_t ui32RecoveryKey);

//
// BOOTROM resident reader, writer and delay utility functions.
//
extern uint32_t am_hal_flash_load_ui32(uint32_t ui32Address);
extern void     am_hal_flash_store_ui32(uint32_t ui32Address, uint32_t ui32Data);
extern void     am_hal_flash_delay(uint32_t ui32Iterations);
extern uint32_t am_hal_flash_delay_status_change(uint32_t ui32Iterations,
                                                 uint32_t ui32Address,
                                                 uint32_t ui32Mask,
                                                 uint32_t ui32Value);

//
// These functions update security/protection bits in the customer INFO blOCK.
//
extern bool     am_hal_flash_customer_info_signature_check(void);
extern bool     am_hal_flash_info_signature_set(void);
extern int32_t  am_hal_flash_info_erase_disable(void);
extern bool     am_hal_flash_info_erase_disable_check(void);
extern int32_t  am_hal_flash_info_program_disable(uint32_t ui32Mask);
extern uint32_t am_hal_flash_info_program_disable_get(void);
extern int32_t  am_hal_flash_wipe_flash_enable(void);
extern bool     am_hal_flash_wipe_flash_enable_check(void);
extern int32_t  am_hal_flash_wipe_sram_enable(void);
extern bool     am_hal_flash_wipe_sram_enable_check(void);
extern int32_t  am_hal_flash_swo_disable(void);
extern bool     am_hal_flash_swo_disable_check(void);
extern int32_t  am_hal_flash_debugger_disable(void);
extern bool     am_hal_flash_debugger_disable_check(void);

extern int32_t  am_hal_flash_copy_protect_set(uint32_t *pui32StartAddress,
                                              uint32_t *pui32StopAddress);
extern bool     am_hal_flash_copy_protect_check(uint32_t *pui32StartAddress,
                                                uint32_t *pui32StopAddress);
extern int32_t  am_hal_flash_write_protect_set(uint32_t *pui32StartAddress,
                                               uint32_t *pui32StopAddress);
extern bool     am_hal_flash_write_protect_check(uint32_t *pui32StartAddress,
                                                 uint32_t *pui32StopAddress);


#ifdef __cplusplus
}
#endif

#endif // AM_HAL_FLASH_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
