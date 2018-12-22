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

/*!
 * @file keypad_port.c
 * @brief Keypad port driver source file.
 *
 * @ingroup diag_keypad
 */

#include "keypad/keypad_port.h"
#include "registers/regskpp.h"
#include "iomux_config.h"
#include "utility/spinlock.h"
#include "timer/timer.h"
#include "core/interrupt.h"
#include "irq_numbers.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Bit mask with all column bits set.
#define ALL_COLUMNS 0xff

//! @brief Global state for the keypad driver.
typedef struct kpp_state {
    uint8_t activeColumns;
    uint8_t activeRows;
    spinlock_t irqLock;
} kpp_state_t;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Global state for the keypad driver.
static kpp_state_t s_kpp;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Clear status flags and synchronizer chains.
static inline void kpp_clear_status(void)
{
    HW_KPP_KPSR_WR(BM_KPP_KPSR_KPKD | BM_KPP_KPSR_KPKR | BM_KPP_KPSR_KDSC | BM_KPP_KPSR_KRSS);
}

/*!
 * @brief Keypad port function to scan the keypad matrix and return the read key(s).
 *
 * The scan sequence is described into the reference manual into "Key press
 * interrupt scanning sequence".
 * To debounce, this sequence is at least executed 3 times, and if the result
 * of the 3 scans is the same, it exits.
 * Likely if a key was detected active 3 times, it's because it is pressed.
 * This is an implementation of the "Keypad matrix Scanning" section presented
 * in the reference manual.
 *
 * @param keypad_state Variable that returns the keypad read state.
 */
void kpp_scan_matrix(uint16_t *keypad_state)
{
    uint16_t port_state_1[8];
    uint16_t port_state_2[8];
    uint16_t port_state_3[8];
    uint16_t *port_state;
    uint8_t tested_col, loop;
    uint16_t col_mask, i;

    memset(port_state_1, 0x0000, sizeof(port_state_1));
    memset(port_state_2, 0x0000, sizeof(port_state_2));
    memset(port_state_3, 0x0000, sizeof(port_state_3));

    loop = 1;
    while (loop != 0)
    {
        if (loop == 1)
        {
            port_state = port_state_1;
        }
        else if (loop == 2)
        {
            port_state = port_state_2;
        }
        else if (loop == 3)
        {
            port_state = port_state_3;
            loop = 0;
        }
        loop++;

        // Execute the scan sequence on the whole keypad.
        // it clears consecutively each active column and
        // sample the row state each time.
        for (tested_col=0 ; tested_col < 8 ; tested_col++)
        {
            col_mask = s_kpp.activeColumns & (1 << tested_col);
            if (col_mask)
            {
                HW_KPP_KPDR_WR(~col_mask << 8);
				hal_delay_us(1);
                port_state[tested_col] = ~HW_KPP_KPDR_RD();
            }
            else
            {
                port_state[tested_col] = 0x0;
            }
        }

        // For key pressed detection:
        // exit from here when 3 consecutive scans of the full
        // keypad matrix give the same result.
        // The read of the KPP_KPDR is inverted, so that the software
        // looks for a value different from 0
        //  => at least one key is pressed.
        for (i=0 ; i < 8 ; i++)
        {
            if ((port_state_1[i] & port_state_2[i] &
               port_state_3[i] & 0xFF) != 0x00)
            {
                loop = 0;
            }
        }
    }

    // copy the result into the global keypad state variable 
    memcpy(keypad_state, port_state_1, sizeof(port_state_1));
}

void kpp_get_keypad_state(uint16_t *rd_keys, bool returnImmediately)
{
    // Clear status flags and synchronizer chains 
    kpp_clear_status();

    // Either the application waits for a pressed key event
    // or it runs immediately the scanning sequence.
    if (!returnImmediately)
    {
        HW_KPP_KPSR_SET(BM_KPP_KPSR_KDIE);
        
        spinlock_lock(&s_kpp.irqLock, kSpinlockWaitForever);
    }

    // Start the scanning routine 
    // Set a high level on each columns 
    HW_KPP_KPDR_WR(BF_KPP_KPDR_KCD(ALL_COLUMNS));

    // For quick discharging of keypad capacitance 
    // configure the column in totem pole 
    HW_KPP_KPCR.B.KCO = 0;

    // re-configure the column to open-drain 
    HW_KPP_KPCR.B.KCO = ALL_COLUMNS;

    // Scan sequence function 
     kpp_scan_matrix(rd_keys);

    // Set a low level on each columns 
    HW_KPP_KPDR_WR(0);
}

void kpp_wait_for_release_state(void)
{
    // Clear status flags and synchronizer chains 
    kpp_clear_status();

    // There's nothing to return. This event only occurs
    // when all key are released.
    HW_KPP_KPSR_SET(BM_KPP_KPSR_KRIE);
    
    spinlock_lock(&s_kpp.irqLock, kSpinlockWaitForever);
}

/*!
 * Keypad port interrupt routine.
 */
void kpp_interrupt_routine(void)
{
    HW_KPP_KPSR_CLR(BM_KPP_KPSR_KDIE | BM_KPP_KPSR_KRIE);

    spinlock_unlock(&s_kpp.irqLock);
}

/*!
 * @brief Setup keypad interrupt.
 *
 * Enables or disables the related HW module interrupt, and attached the related sub-routine
 * into the vector table.
 *
 * @param state Flag indicating whether to enable (true) or disable (false) the interrupt.
 */
void kpp_setup_interrupt(bool state)
{
    if (state)
    {    
        // clear status flags and synchronizer chains 
        kpp_clear_status();
        
        // register the IRQ sub-routine 
        register_interrupt_routine(IMX_INT_KPP, &kpp_interrupt_routine);
        
        // enable the IRQ 
        enable_interrupt(IMX_INT_KPP, CPU_0, 0);
    }
    else
    {
        // disable the IRQ 
        disable_interrupt(IMX_INT_KPP, CPU_0);
        
        // clear status flags and synchronizer chains 
        kpp_clear_status();
    }
}

void kpp_open(uint8_t kpp_col, uint8_t kpp_row)
{
    // Initialize global variables to store the board's keypad usage 
    s_kpp.activeColumns = kpp_col;
    s_kpp.activeRows = kpp_row;
    
    // Init the spinlock used for interrupt synchronization and lock it.
    spinlock_init(&s_kpp.irqLock);
    spinlock_lock(&s_kpp.irqLock, kSpinlockNoWait);

    // there's no clock to enable for the keypad port 

    // configure the IOMUX 
    kpp_iomux_config();

    // configure the columns in open-drain & set the active rows 
    HW_KPP_KPCR_WR(BF_KPP_KPCR_KCO(ALL_COLUMNS)
                | BF_KPP_KPCR_KRE(s_kpp.activeRows));

    // Set a low level on each columns. Must do this before configuring outputs.
    HW_KPP_KPDR_WR(0);

    // configure columns as outputs and rows as inputs 
    HW_KPP_KDDR_WR(BF_KPP_KDDR_KCDD(s_kpp.activeColumns) | BF_KPP_KDDR_KRDD(0));

    // clear status flags and synchronizer chains 
    kpp_clear_status();

    // set up the interrupt 
    kpp_setup_interrupt(true);
}

void kpp_close(void)
{
    // disable the interrupts 
    HW_KPP_KPSR_CLR(BM_KPP_KPSR_KDIE | BM_KPP_KPSR_KRIE);
    
    kpp_setup_interrupt(false);
    
    // Disable all rows.
    HW_KPP_KPCR_WR(0);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
