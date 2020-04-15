//*****************************************************************************
//
//  am_hal_sysctrl.c
//! @file
//!
//! @brief Functions for interfacing with the M4F system control registers
//!
//! @addtogroup sysctrl2 System Control (SYSCTRL)
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
//  Local macro constants
//
//*****************************************************************************
//
// Define ZX workaround values.
// These values are defined by the factory.
//
#define COREZXVALUE         0x07
#define MEMZXVALUE          0x07

//
// Define values for g_ui32CoreBuck, which indicates which timer carries
// the signal for the CORE Buck, and which also implies that the other timer
// carries the signal for the MEM buck.
//
#define COREBUCK_TIMERA     1       // Core buck signal comes in on timer A
#define COREBUCK_TIMERB     2       // Core buck signal comes in on timer B

//
// Define the bit values for static function g_buckZX_chk;
//
#define CHKBUCKZX_BUCKS     0x01    // The bucks are enabled
#define CHKBUCKZX_REV       0x02    // This chip rev needs the workaround
#define CHKBUCKZX_TIMER     0x04    // A valid timer has been allocated
#define CHKBUCKZX_DEVEN     0x08    // Devices are powered up and enabled

//*****************************************************************************
//
//  Prototypes
//
//*****************************************************************************
static void am_hal_sysctrl_buckA_ctimer_isr(void);
static void am_hal_sysctrl_buckB_ctimer_isr(void);

//*****************************************************************************
//
//  Globals
//
//*****************************************************************************
static volatile uint32_t g_ui32BuckTimer = 0;
static volatile uint32_t g_ui32BuckInputs = 0;
static volatile bool     g_bBuckRestoreComplete = false;
static volatile bool     g_bBuckTimed = false;
static          uint32_t g_ui32SaveCoreBuckZX, g_ui32SaveMemBuckZX;
static          uint32_t g_buckZX_chk = 0;
static volatile uint32_t g_ui32CoreBuck;

//
// Timer configuration for BUCK inputs.
//
static const am_hal_ctimer_config_t g_sBuckTimer =
{
    // Don't link timers.
    0,

    // Set up Timer0A.
    (AM_HAL_CTIMER_FN_ONCE      |
     AM_HAL_CTIMER_INT_ENABLE   |
     AM_HAL_CTIMER_BUCK),

    // Set up Timer0B.
    (AM_HAL_CTIMER_FN_ONCE      |
     AM_HAL_CTIMER_INT_ENABLE   |
     AM_HAL_CTIMER_BUCK),
};

//*****************************************************************************
//
// Determine if we need to do the zero cross workaround on this device.
// Three criteria are used.  All three must be true.
//  1. Are the bucks enabled?
//  2. Is the chip rev appropriate for the workaround?
//  3. Has a timer been allocated to do the workaround?
//  4. Are certain peripherals powered up?
//
// Saves the bitmask to the global g_buckZX_chk.
// Bitmask bits are defined as: CHKBUCKZX_BUCKS, CHKBUCKZX_REV, CHKBUCKZX_TIMER.
//
// Returns true if all criteria are met, false otherwise.
// g_buckZX_chk can be probed to determine which criteria passed or failed.
//
//*****************************************************************************
static bool
buckZX_chk(void)
{
    uint32_t ui32SupplySrc;

    //
    // Is this chip rev appropriate to do the workaround?
    //
    g_buckZX_chk = AM_BFM(MCUCTRL, CHIPREV, REVMAJ) == AM_REG_MCUCTRL_CHIPREV_REVMAJ_B ?
                   CHKBUCKZX_REV : 0x0;

    //
    // Has a timer been configured to handle the workaround?
    //
    g_buckZX_chk |= ( g_ui32BuckTimer - 1 ) <= BUCK_TIMER_MAX ?
                    CHKBUCKZX_TIMER : 0x0;

    //
    // Are either or both of the bucks actually enabled?
    //
    ui32SupplySrc = AM_REG(PWRCTRL, SUPPLYSRC);

    g_buckZX_chk |= (ui32SupplySrc &
                    (AM_REG_PWRCTRL_SUPPLYSRC_COREBUCKEN_M  |
                     AM_REG_PWRCTRL_SUPPLYSRC_MEMBUCKEN_M) ) ?
                     CHKBUCKZX_BUCKS : 0x0;

    //
    // Finally, if any peripheral is already powered up, we don't need to do the
    //  ZX workaround because in this case the bucks remain in active mode.
    //
    ui32SupplySrc = AM_REG(PWRCTRL, DEVICEEN);

    g_buckZX_chk |= ( ui32SupplySrc &
            (AM_REG_PWRCTRL_DEVICEEN_PDM_M          |
             AM_REG_PWRCTRL_DEVICEEN_UART1_M        |
             AM_REG_PWRCTRL_DEVICEEN_UART0_M        |
             AM_REG_PWRCTRL_DEVICEEN_IO_MASTER5_M   |
             AM_REG_PWRCTRL_DEVICEEN_IO_MASTER4_M   |
             AM_REG_PWRCTRL_DEVICEEN_IO_MASTER3_M   |
             AM_REG_PWRCTRL_DEVICEEN_IO_MASTER2_M   |
             AM_REG_PWRCTRL_DEVICEEN_IO_MASTER1_M   |
             AM_REG_PWRCTRL_DEVICEEN_IO_MASTER0_M   |
             AM_REG_PWRCTRL_DEVICEEN_IO_SLAVE_M) )      ?
                0x0 : CHKBUCKZX_DEVEN;

    //
    // If all 4 criteria were met, we're good to do the workaround.
    //
    return ( g_buckZX_chk ==
             (CHKBUCKZX_BUCKS | CHKBUCKZX_REV |
              CHKBUCKZX_TIMER | CHKBUCKZX_DEVEN) ) ? true : false;
}

//*****************************************************************************
//
// Set the buck zero cross settings to the values given.
//
// ui32Flags, one or more of the following:
//  SETBUCKZX_USE_PROVIDED_SETTINGS - Use the values provided in the parameters
//                                    to set the trim value(s).
//  SETBUCKZX_USE_SAVED_SETTINGS    - Use the values that were previously saved
//                                    to set the trim value(s).
//  SETBUCKZX_SAVE_CURR_SETTINGS    - Save the current trim values before
//                                    setting the new ones.
//  SETBUCKZX_RESTORE_CORE_ONLY     - Restore the Core trim and save the current
//                                    value of the core buck trim iff
//                                    SETBUCKZX_SAVE_CURR_SETTINGS is set.
//  SETBUCKZX_RESTORE_MEM_ONLY      - Restore the Mem trim and save the current
//                                    value of the mem buck trim iff
//                                    SETBUCKZX_SAVE_CURR_SETTINGS is set.
//  SETBUCKZX_RESTORE_BOTH          - Restore both buck trims and save the
//                                    current value of both iff
//                                    SETBUCKZX_SAVE_CURR_SETTINGS is set.
//
//*****************************************************************************
#define SETBUCKZX_USE_PROVIDED_SETTINGS 0x01
#define SETBUCKZX_USE_SAVED_SETTINGS    0x02
#define SETBUCKZX_SAVE_CURR_SETTINGS    0x04
#define SETBUCKZX_RESTORE_CORE_ONLY     0x10
#define SETBUCKZX_RESTORE_MEM_ONLY      0x20
#define SETBUCKZX_RESTORE_BOTH          ( SETBUCKZX_RESTORE_CORE_ONLY |     \
                                          SETBUCKZX_RESTORE_MEM_ONLY )
static void
setBuckZX(uint32_t ui32CoreBuckZX, uint32_t ui32MemBuckZX, uint32_t ui32Flags)
{
    uint32_t ui32SaveCore, ui32SaveMem, ui32NewCore, ui32NewMem;
    bool bDoRestore = false;

    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN_ASM

    //
    // Get the current zero cross trim values.
    //
    ui32SaveCore = AM_BFR(MCUCTRL, BUCK3, COREBUCKZXTRIM);
    ui32SaveMem  = AM_BFR(MCUCTRL, BUCK3, MEMBUCKZXTRIM);

    //
    // Determine which values will be restored.
    //
    if ( ui32Flags & SETBUCKZX_USE_SAVED_SETTINGS )
    {
        //
        // Use saved settings
        //
        ui32NewCore = g_ui32SaveCoreBuckZX;
        ui32NewMem  = g_ui32SaveMemBuckZX;
        bDoRestore = true;
    }
    else if ( ui32Flags & SETBUCKZX_USE_PROVIDED_SETTINGS )
    {
        //
        // Use settings provided in the call parameters
        //
        ui32NewCore = ui32CoreBuckZX;
        ui32NewMem  = ui32MemBuckZX;
        bDoRestore = true;
    }

    //
    // Restore the buck Core and Mem trim registers.
    //
    if ( bDoRestore )
    {
        if ( ui32Flags & SETBUCKZX_RESTORE_CORE_ONLY )
        {
            AM_BFW(MCUCTRL, BUCK3, COREBUCKZXTRIM, ui32NewCore);
        }

        if ( ui32Flags & SETBUCKZX_RESTORE_MEM_ONLY )
        {
            AM_BFW(MCUCTRL, BUCK3, MEMBUCKZXTRIM,  ui32NewMem);
        }
    }

    if ( ui32Flags & SETBUCKZX_SAVE_CURR_SETTINGS )
    {
        //
        // Save off the zero cross values as read on entry to the function.
        //
        if ( ui32Flags & SETBUCKZX_RESTORE_CORE_ONLY )
        {
            g_ui32SaveCoreBuckZX = ui32SaveCore;
        }

        if ( ui32Flags & SETBUCKZX_RESTORE_MEM_ONLY )
        {
            g_ui32SaveMemBuckZX  = ui32SaveMem;
        }
    }

    //
    // Done with critical section.
    //
    AM_CRITICAL_END_ASM
}

//*****************************************************************************
//
//! @brief Place the core into sleep or deepsleep.
//!
//! @param bSleepDeep - False for Normal or True Deep sleep.
//!
//! This function puts the MCU to sleep or deepsleep depending on bSleepDeep.
//!
//! Valid values for bSleepDeep are:
//!
//!     AM_HAL_SYSCTRL_SLEEP_NORMAL
//!     AM_HAL_SYSCTRL_SLEEP_DEEP
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_sleep(bool bSleepDeep)
{
    uint32_t ui32Critical;
//  uint32_t ui32DebugGpioSleep = g_ui32DebugGpioSleep - 1;
    bool bBuckZX_chk;
    volatile uint32_t ui32BuckTimer;

    //
    // Disable interrupts and save the previous interrupt state.
    //
    ui32Critical = am_hal_interrupt_master_disable();

    //
    // If the user selected DEEPSLEEP and the TPIU is off, attempt to enter
    // DEEP SLEEP.
    //
    if ((bSleepDeep == AM_HAL_SYSCTRL_SLEEP_DEEP) &&
        (AM_BFM(MCUCTRL, TPIUCTRL, ENABLE) == AM_REG_MCUCTRL_TPIUCTRL_ENABLE_DIS))
    {
        //
        // Prepare the core for deepsleep (write 1 to the DEEPSLEEP bit).
        //
        AM_BFW(SYSCTRL, SCR, SLEEPDEEP, 1);

        //
        // Check if special buck handling is needed
        //
        bBuckZX_chk = buckZX_chk();

        if ( bBuckZX_chk )
        {
            ui32BuckTimer = g_ui32BuckTimer - 1;

            //
            // Before going to sleep, clear the buck timers.
            // This will also handle the case where we're going back to
            // sleep before the buck sequence has even completed.
            //
            am_hal_ctimer_clear(ui32BuckTimer, AM_HAL_CTIMER_BOTH);

            //
            // Set CMPR0 of both timerA and timerB to the period value
            //
            #define     TIMER_PERIOD_BUCKS  1
            am_hal_ctimer_period_set(ui32BuckTimer,
                                     AM_HAL_CTIMER_BOTH,
                                     TIMER_PERIOD_BUCKS |
                                     (TIMER_PERIOD_BUCKS << 16),
                                     0);

            //
            // Disable bucks before going to sleep.
            //
            am_hal_pwrctrl_bucks_disable();
        }

        //
        // Execute the sleep instruction.
        //
        AM_ASM_WFI;

        //
        // Return from sleep
        //
        if ( bBuckZX_chk )
        {
            //
            // Adjust the core and mem trims
            //
            setBuckZX(COREZXVALUE, MEMZXVALUE,
                      SETBUCKZX_USE_PROVIDED_SETTINGS   |
                      SETBUCKZX_RESTORE_BOTH );

            //
            // Delay for 2us before enabling bucks.
            //
            am_hal_flash_delay( FLASH_CYCLES_US(2) );

            //
            // Turn on the bucks
            //
            am_hal_pwrctrl_bucks_enable();

            //
            // Get the actual timer number
            //
            ui32BuckTimer = g_ui32BuckTimer - 1;

            //
            // Initialize the complete flag
            //
            g_bBuckRestoreComplete = false;

            //
            // Initialize the input flags
            //
            g_ui32BuckInputs = 0;

            //
            // Delay for 5us to make sure we're receiving clean buck signals.
            //
            am_hal_flash_delay( FLASH_CYCLES_US(5) );

            //
            // Start timers (set the enable bit, clear the clear bit)
            //
            am_hal_ctimer_start(ui32BuckTimer, AM_HAL_CTIMER_BOTH);
        }
        else
        {
            //
            // Since we're not doing anything, we're done, so set the done flag.
            //
            g_bBuckRestoreComplete = true;
        }
    }
    else
    {
        //
        // Prepare the core for normal sleep (write 0 to the DEEPSLEEP bit).
        //
        AM_BFW(SYSCTRL, SCR, SLEEPDEEP, 0);

        //
        // Go to sleep.
        //
        AM_ASM_WFI;
    }

    //
    // Restore the interrupt state.
    //
    am_hal_interrupt_master_set(ui32Critical);
}

//*****************************************************************************
//
//! @brief Enable the floating point module.
//!
//! Call this function to enable the ARM hardware floating point module.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_fpu_enable(void)
{
    //
    // Enable access to the FPU in both privileged and user modes.
    // NOTE: Write 0s to all reserved fields in this register.
    //
    AM_REG(SYSCTRL, CPACR) = (AM_REG_SYSCTRL_CPACR_CP11(0x3) |
                             AM_REG_SYSCTRL_CPACR_CP10(0x3));
}

//*****************************************************************************
//
//! @brief Disable the floating point module.
//!
//! Call this function to disable the ARM hardware floating point module.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_fpu_disable(void)
{
    //
    // Disable access to the FPU in both privileged and user modes.
    // NOTE: Write 0s to all reserved fields in this register.
    //
    AM_REG(SYSCTRL, CPACR) = 0x00000000                     &
                          ~(AM_REG_SYSCTRL_CPACR_CP11(0x3) |
                            AM_REG_SYSCTRL_CPACR_CP10(0x3));
}

//*****************************************************************************
//
//! @brief Enable stacking of FPU registers on exception entry.
//!
//! @param bLazy - Set to "true" to enable "lazy stacking".
//!
//! This function allows the core to save floating-point information to the
//! stack on exception entry. Setting the bLazy option enables "lazy stacking"
//! for interrupt handlers.  Normally, mixing floating-point code and interrupt
//! driven routines causes increased interrupt latency, because the core must
//! save extra information to the stack upon exception entry. With the lazy
//! stacking option enabled, the core will skip the saving of floating-point
//! registers when possible, reducing average interrupt latency.
//!
//! @note This function should be called before the floating-point module is
//! used in interrupt-driven code. If it is not called, the core will not have
//! any way to save context information for floating-point variables on
//! exception entry.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_fpu_stacking_enable(bool bLazy)
{
    if ( bLazy )
    {
        //
        // Enable automatic saving of FPU registers on exception entry, using lazy
        // context saving.
        //
        AM_REG(SYSCTRL, FPCCR) |= (AM_REG_SYSCTRL_FPCCR_ASPEN(0x1) |
                                   AM_REG_SYSCTRL_FPCCR_LSPEN(0x1));
    }
    else
    {
        //
        // Enable automatic saving of FPU registers on exception entry.
        //
        AM_REG(SYSCTRL, FPCCR) |= AM_REG_SYSCTRL_FPCCR_ASPEN(0x1);
    }
}

//*****************************************************************************
//
//! @brief Disable FPU register stacking on exception entry.
//!
//! This function disables all stacking of floating point registers for
//! interrupt handlers.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_fpu_stacking_disable(void)
{
    //
    // Enable automatic saving of FPU registers on exception entry, using lazy
    // context saving.
    //
    AM_REG(SYSCTRL, FPCCR) &= ~(AM_REG_SYSCTRL_FPCCR_ASPEN(0x1) |
                                AM_REG_SYSCTRL_FPCCR_LSPEN(0x1));
}

//*****************************************************************************
//
//! @brief Issue a system wide reset using the AIRCR bit in the M4 system ctrl.
//!
//! This function issues a system wide reset (Apollo POR level reset).
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_sysctrl_aircr_reset(void)
{
    //
    // Set the system reset bit in the AIRCR register
    //
    AM_REG(SYSCTRL, AIRCR) = AM_REG_SYSCTRL_AIRCR_VECTKEY(0x5FA) |
                             AM_REG_SYSCTRL_AIRCR_SYSRESETREQ(1);
}

//*****************************************************************************
//
//! @brief Buck CTimer ISR initializer.
//!
//! @param ui32BuckTimerNumber - Timer number to be used for handling the buck.
//!                              Must be 0-3.
//!
//! If called with an invalid timer (that is, not 0 - 3, or greater than
//! BUCK_TIMER_MAX), then the workaround will not be enabled.
//!
//! Instead, the bucks will be initialized with a value that will avoid the
//! issues described in the Errata (ERR019).  However, this will cause a
//! less efficient energy usage condtion.
//!
//! @return 0.
//
//*****************************************************************************
uint32_t
am_hal_sysctrl_buck_ctimer_isr_init(uint32_t ui32BuckTimerNumber)
{
    uint32_t ui32RetVal = 0;

    //
    // Initialize the input flags
    //
    g_ui32BuckInputs = 0;

    //
    // Initialize operation complete flag
    //
    g_bBuckRestoreComplete = false;

    //
    // Initialize to assume there is no valid timer.
    //
    g_ui32BuckTimer = 0;

    if ( ui32BuckTimerNumber > BUCK_TIMER_MAX )
    {
        if ( ( ui32BuckTimerNumber & 0xFFFF0000 ) ==
             AM_HAL_SYSCTRL_BUCK_CTIMER_ZX_CONSTANT )
        {
            //
            // The caller is asking for the hard option, which changes the
            //  settings to the more noise-immune, if less efficient, settings.
            // While we're at it, go ahead and save off the current settings.
            //
            if ( (ui32BuckTimerNumber & 0x0000FFFF) == 0 )
            {
                setBuckZX(COREZXVALUE, MEMZXVALUE,
                          SETBUCKZX_USE_PROVIDED_SETTINGS   |
                          SETBUCKZX_SAVE_CURR_SETTINGS      |
                          SETBUCKZX_RESTORE_BOTH );
            }
            else
            {
                uint32_t ui32Core, ui32Mem;

                //
                // Use the setting provided in the parameter.
                //
                ui32Core = (((ui32BuckTimerNumber & 0x001F) >> 0) - 1) & 0xF;
                ui32Mem  = (((ui32BuckTimerNumber & 0x1F00) >> 8) - 1) & 0xF;

                setBuckZX(ui32Core, ui32Mem,
                          SETBUCKZX_USE_PROVIDED_SETTINGS   |
                          SETBUCKZX_SAVE_CURR_SETTINGS      |
                          SETBUCKZX_RESTORE_BOTH );
            }
        }
    }
    else
    {
        //
        // Save off the current trim settings (but don't change any settings).
        //
        setBuckZX(0, 0, SETBUCKZX_SAVE_CURR_SETTINGS | SETBUCKZX_RESTORE_BOTH);

        //
        // The timer number will be maintained as (n + 1).  Therefore, a value
        // of 0 saved in the global is an invalid timer.  1=timer0, 2=timer1...
        //
        g_ui32BuckTimer = ui32BuckTimerNumber + 1;

        //
        // Register the timer ISRs
        //
        am_hal_ctimer_int_register( AM_HAL_CTIMER_INT_TIMERA0C0 <<
                                    (ui32BuckTimerNumber * 2),
                                     am_hal_sysctrl_buckA_ctimer_isr );

        am_hal_ctimer_int_register( AM_HAL_CTIMER_INT_TIMERB0C0 <<
                                    (ui32BuckTimerNumber * 2),
                                     am_hal_sysctrl_buckB_ctimer_isr );

        //
        // Determine which timer input (A or B) is core buck and which is mem
        // buck based on the timer number.
        //  For CTIMER 0 & 1: Timer A is mem  buck, Timer B is core buck
        //  For CTIMER 2 & 3: Timer A is core buck, Timer B is mem  buck
        //
        if ( (ui32BuckTimerNumber == 0)  ||  (ui32BuckTimerNumber == 1) )
        {
            //
            // Indicate that TimerB is core buck.
            //
            g_ui32CoreBuck = COREBUCK_TIMERB;
        }
        else
        {
            //
            // Indicate that TimerA is core buck
            //
            g_ui32CoreBuck = COREBUCK_TIMERA;
        }

        //
        // Clear and configure the timers
        //
        am_hal_ctimer_clear(ui32BuckTimerNumber, AM_HAL_CTIMER_BOTH);

        am_hal_ctimer_config(ui32BuckTimerNumber,
                             (am_hal_ctimer_config_t*)&g_sBuckTimer);

        //
        // Enable the interrupts for timers A and B
        //
        am_hal_ctimer_int_enable( (AM_HAL_CTIMER_INT_TIMERA0C0 |
                                   AM_HAL_CTIMER_INT_TIMERB0C0 ) <<
                                   (ui32BuckTimerNumber * 2) );

        //
        // Enable the timer interrupt in the NVIC.
        //
        am_hal_interrupt_enable(AM_HAL_INTERRUPT_CTIMER);
    }

    return ui32RetVal;
}

//*****************************************************************************
//
// Get buck update complete status.
//
//*****************************************************************************
bool
am_hal_sysctrl_buck_update_complete(void)
{
    return g_bBuckRestoreComplete;
}

//*****************************************************************************
//
// Buck CTIMER ISR (for handling buck switching via TimerA).
//
// Note: This handler assumes that the interrupt is cleared in am_ctimer_isr().
//
//*****************************************************************************
static void
am_hal_sysctrl_buckA_ctimer_isr(void)
{
    //
    // Begin critical section.
    // Although a relatively long time, the following 2us delay is critically
    // timed for re-trimming the buck and thus cannot be extended.  Therefore,
    // we must keep it inside the critical section.
    //
    AM_CRITICAL_BEGIN_ASM

    //
    // Delay for 2us.
    //
    am_hal_flash_delay( FLASH_CYCLES_US(2) );

    //
    // Determine which buck (core or mem) needs to be updated.
    //
    if ( g_ui32CoreBuck == COREBUCK_TIMERA )
    {
        //
        // Timer A buck signal is the CORE buck.
        // Restore the core buck.
        //
        setBuckZX(0, 0, SETBUCKZX_RESTORE_CORE_ONLY |
                        SETBUCKZX_USE_SAVED_SETTINGS );
    }
    else
    {
        //
        // Timer A buck signal is the MEM buck.
        // Restore the mem buck.
        //
        setBuckZX(0, 0, SETBUCKZX_RESTORE_MEM_ONLY  |
                        SETBUCKZX_USE_SAVED_SETTINGS );
    }

    g_ui32BuckInputs |= 0x1;

    if ( g_ui32BuckInputs == 0x3 )
    {
        g_bBuckRestoreComplete = true;
        g_ui32BuckInputs = 0;
    }

    //
    // End critical section.
    //
    AM_CRITICAL_END_ASM
}

//*****************************************************************************
//
// Buck CTIMER ISR (for handling buck switching via TimerB).
//
// Note: This handler assumes that the interrupt is cleared in am_ctimer_isr().
//
//*****************************************************************************
static void
am_hal_sysctrl_buckB_ctimer_isr(void)
{
    //
    // Begin critical section.
    // Although a relatively long time, the following 2us delay is critically
    // timed for re-trimming the buck and thus cannot be extended.  Therefore,
    // we must keep it inside the critical section.
    //
    AM_CRITICAL_BEGIN_ASM

    //
    // Delay for 2us.
    //
    am_hal_flash_delay( FLASH_CYCLES_US(2) );

    //
    // Determine which buck (core or mem) needs to be updated.
    //
    if ( g_ui32CoreBuck == COREBUCK_TIMERB )
    {
        //
        // Timer B buck signal is the CORE buck.
        // Restore the core buck.
        //
        setBuckZX(0, 0, SETBUCKZX_RESTORE_CORE_ONLY |
                        SETBUCKZX_USE_SAVED_SETTINGS );
    }
    else
    {
        //
        // Timer B buck signal is the MEM buck.
        // Restore the mem buck.
        //
        setBuckZX(0, 0, SETBUCKZX_RESTORE_MEM_ONLY  |
                        SETBUCKZX_USE_SAVED_SETTINGS );
    }

    g_ui32BuckInputs |= 0x2;

    if ( g_ui32BuckInputs == 0x3 )
    {
        g_bBuckRestoreComplete = true;
        g_ui32BuckInputs = 0;
    }

    //
    // End critical section.
    //
    AM_CRITICAL_END_ASM
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
