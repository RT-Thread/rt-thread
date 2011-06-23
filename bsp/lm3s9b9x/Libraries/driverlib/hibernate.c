//*****************************************************************************
//
// hibernate.c - Driver for the Hibernation module
//
// Copyright (c) 2007-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 6459 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup hibernate_api
//! @{
//
//*****************************************************************************

#include "inc/hw_hibernate.h"
#include "inc/hw_ints.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/hibernate.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
// The delay in microseconds for writing to the Hibernation module registers.
//
//*****************************************************************************
#define DELAY_USECS             95

//*****************************************************************************
//
// The number of processor cycles to execute one pass of the delay loop.
//
//*****************************************************************************
#define LOOP_CYCLES             3

//*****************************************************************************
//
// The calculated number of delay loops to achieve the write delay.
//
//*****************************************************************************
static unsigned long g_ulWriteDelay;

//*****************************************************************************
//
//! \internal
//!
//! Polls until the write complete (WRC) bit in the hibernate control register
//! is set.
//!
//! \param None.
//!
//! On non-Fury-class devices, the hibernate module provides an indication when
//! any write is completed.  This is used to pace writes to the module.  This
//! function merely polls this bit and returns as soon as it is set.  At this
//! point, it is safe to perform another write to the module.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateWriteComplete(void)
{
    //
    // Spin until the write complete bit is set.
    //
    while(!(HWREG(HIB_CTL) & HIB_CTL_WRC))
    {
    }
}

//*****************************************************************************
//
//! Enables the Hibernation module for operation.
//!
//! \param ulHibClk is the rate of the clock supplied to the Hibernation
//! module.
//!
//! Enables the Hibernation module for operation.  This function should be
//! called before any of the Hibernation module features are used.
//!
//! The peripheral clock will be the same as the processor clock.  This will be
//! the value returned by SysCtlClockGet(), or it can be explicitly hard-coded
//! if it is constant and known (to save the code/execution overhead of a call
//! to SysCtlClockGet()).
//!
//! This function replaces the original HibernateEnable() API and performs the
//! same actions.  A macro is provided in <tt>hibernate.h</tt> to map the
//! original API to this API.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateEnableExpClk(unsigned long ulHibClk)
{
    //
    // Turn on the clock enable bit.
    //
    HWREG(HIB_CTL) |= HIB_CTL_CLK32EN;

    //
    // For Fury-class devices, compute the number of delay loops that must be
    // used to achieve the desired delay for writes to the hibernation
    // registers.  This value will be used in calls to SysCtlDelay().
    //
    if(CLASS_IS_FURY)
    {
        g_ulWriteDelay = (((ulHibClk / 1000) * DELAY_USECS) /
                          (1000L * LOOP_CYCLES));
        g_ulWriteDelay++;
    }
}

//*****************************************************************************
//
//! Disables the Hibernation module for operation.
//!
//! Disables the Hibernation module for operation.  After this function is
//! called, none of the Hibernation module features are available.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateDisable(void)
{
    //
    // Turn off the clock enable bit.
    //
    HWREG(HIB_CTL) &= ~HIB_CTL_CLK32EN;
}

//*****************************************************************************
//
//! Selects the clock input for the Hibernation module.
//!
//! \param ulClockInput specifies the clock input.
//!
//! Configures the clock input for the Hibernation module.  The configuration
//! option chosen depends entirely on hardware design.  The clock input for the
//! module will either be a 32.768 kHz oscillator or a 4.194304 MHz crystal.
//! The \e ulClockFlags parameter must be one of the following:
//!
//! - \b HIBERNATE_CLOCK_SEL_RAW - use the raw signal from a 32.768 kHz
//!   oscillator.
//! - \b HIBERNATE_CLOCK_SEL_DIV128 - use the crystal input, divided by 128.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateClockSelect(unsigned long ulClockInput)
{
    //
    // Check the arguments.
    //
    ASSERT((ulClockInput == HIBERNATE_CLOCK_SEL_RAW) ||
           (ulClockInput == HIBERNATE_CLOCK_SEL_DIV128));

    //
    // Set the clock selection bit according to the parameter.
    //
    HWREG(HIB_CTL) = ulClockInput | (HWREG(HIB_CTL) & ~HIB_CTL_CLKSEL);
}

//*****************************************************************************
//
//! Enables the RTC feature of the Hibernation module.
//!
//! Enables the RTC in the Hibernation module.  The RTC can be used to wake the
//! processor from hibernation at a certain time, or to generate interrupts at
//! certain times.  This function must be called before using any of the RTC
//! features of the Hibernation module.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCEnable(void)
{
    //
    // Turn on the RTC enable bit.
    //
    HWREG(HIB_CTL) |= HIB_CTL_RTCEN;
}

//*****************************************************************************
//
//! Disables the RTC feature of the Hibernation module.
//!
//! Disables the RTC in the Hibernation module.  After calling this function
//! the RTC features of the Hibernation module will not be available.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCDisable(void)
{
    //
    // Turn off the RTC enable bit.
    //
    HWREG(HIB_CTL) &= ~HIB_CTL_RTCEN;
}

//*****************************************************************************
//
//! Configures the wake conditions for the Hibernation module.
//!
//! \param ulWakeFlags specifies which conditions should be used for waking.
//!
//! Enables the conditions under which the Hibernation module will wake.  The
//! \e ulWakeFlags parameter is the logical OR of any combination of the
//! following:
//!
//! - \b HIBERNATE_WAKE_PIN - wake when the external wake pin is asserted.
//! - \b HIBERNATE_WAKE_RTC - wake when one of the RTC matches occurs.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateWakeSet(unsigned long ulWakeFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(!(ulWakeFlags & ~(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC)));

    //
    // Set the specified wake flags in the control register.
    //
    HWREG(HIB_CTL) = (ulWakeFlags |
                      (HWREG(HIB_CTL) &
                       ~(HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC)));
}

//*****************************************************************************
//
//! Gets the currently configured wake conditions for the Hibernation module.
//!
//! Returns the flags representing the wake configuration for the Hibernation
//! module.  The return value will be a combination of the following flags:
//!
//! - \b HIBERNATE_WAKE_PIN - wake when the external wake pin is asserted.
//! - \b HIBERNATE_WAKE_RTC - wake when one of the RTC matches occurs.
//!
//! \return Returns flags indicating the configured wake conditions.
//
//*****************************************************************************
unsigned long
HibernateWakeGet(void)
{
    //
    // Read the wake bits from the control register and return
    // those bits to the caller.
    //
    return(HWREG(HIB_CTL) & (HIBERNATE_WAKE_PIN | HIBERNATE_WAKE_RTC));
}

//*****************************************************************************
//
//! Configures the low battery detection.
//!
//! \param ulLowBatFlags specifies behavior of low battery detection.
//!
//! Enables the low battery detection and whether hibernation is allowed if a
//! low battery is detected.  If low battery detection is enabled, then a low
//! battery condition will be indicated in the raw interrupt status register,
//! and can also trigger an interrupt.  Optionally, hibernation can be aborted
//! if a low battery is detected.
//!
//! The \e ulLowBatFlags parameter is one of the following values:
//!
//! - \b HIBERNATE_LOW_BAT_DETECT - detect a low battery condition.
//! - \b HIBERNATE_LOW_BAT_ABORT - detect a low battery condition, and abort
//!   hibernation if low battery is detected.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateLowBatSet(unsigned long ulLowBatFlags)
{
    //
    // Check the arguments.
    //
    ASSERT((ulLowBatFlags == HIBERNATE_LOW_BAT_DETECT) ||
           (ulLowBatFlags == HIBERNATE_LOW_BAT_ABORT));

    //
    // Set the low battery detect and abort bits in the control register,
    // according to the parameter.
    //
    HWREG(HIB_CTL) = (ulLowBatFlags |
                      (HWREG(HIB_CTL) & ~HIBERNATE_LOW_BAT_ABORT));
}

//*****************************************************************************
//
//! Gets the currently configured low battery detection behavior.
//!
//! Returns a value representing the currently configured low battery detection
//! behavior.  The return value will be one of the following:
//!
//! - \b HIBERNATE_LOW_BAT_DETECT - detect a low battery condition.
//! - \b HIBERNATE_LOW_BAT_ABORT - detect a low battery condition, and abort
//! hibernation if low battery is detected.
//!
//! \return Returns a value indicating the configured low battery detection.
//
//*****************************************************************************
unsigned long
HibernateLowBatGet(void)
{
    //
    // Read the low bat bits from the control register and return those bits to
    // the caller.
    //
    return(HWREG(HIB_CTL) & HIBERNATE_LOW_BAT_ABORT);
}

//*****************************************************************************
//
//! Sets the value of the real time clock (RTC) counter.
//!
//! \param ulRTCValue is the new value for the RTC.
//!
//! Sets the value of the RTC.  The RTC will count seconds if the hardware is
//! configured correctly.  The RTC must be enabled by calling
//! HibernateRTCEnable() before calling this function.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCSet(unsigned long ulRTCValue)
{
    //
    // Write the new RTC value to the RTC load register.
    //
    HWREG(HIB_RTCLD) = ulRTCValue;

    //
    // Add a delay here to enforce the required delay between write accesses to
    // certain Hibernation module registers.
    //
    if(CLASS_IS_FURY)
    {
        //
        // Delay a fixed time on Fury-class devices
        //
        SysCtlDelay(g_ulWriteDelay);
    }
    else
    {
        //
        // Wait for write complete to be signaled on later devices.
        //
        HibernateWriteComplete();
    }
}

//*****************************************************************************
//
//! Gets the value of the real time clock (RTC) counter.
//!
//! Gets the value of the RTC and returns it to the caller.
//!
//! \return Returns the value of the RTC.
//
//*****************************************************************************
unsigned long
HibernateRTCGet(void)
{
    //
    // Return the value of the RTC counter register to the caller.
    //
    return(HWREG(HIB_RTCC));
}

//*****************************************************************************
//
//! Sets the value of the RTC match 0 register.
//!
//! \param ulMatch is the value for the match register.
//!
//! Sets the match 0 register for the RTC.  The Hibernation module can be
//! configured to wake from hibernation, and/or generate an interrupt when the
//! value of the RTC counter is the same as the match register.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCMatch0Set(unsigned long ulMatch)
{
    //
    // Write the new match value to the match register.
    //
    HWREG(HIB_RTCM0) = ulMatch;

    //
    // Add a delay here to enforce the required delay between write accesses to
    // certain Hibernation module registers.
    //
    if(CLASS_IS_FURY)
    {
        //
        // Delay a fixed time on Fury-class devices
        //
        SysCtlDelay(g_ulWriteDelay);
    }
    else
    {
        //
        // Wait for write complete to be signaled on later devices.
        //
        HibernateWriteComplete();
    }
}

//*****************************************************************************
//
//! Gets the value of the RTC match 0 register.
//!
//! Gets the value of the match 0 register for the RTC.
//!
//! \return Returns the value of the match register.
//
//*****************************************************************************
unsigned long
HibernateRTCMatch0Get(void)
{
    //
    // Return the value of the match register to the caller.
    //
    return(HWREG(HIB_RTCM0));
}

//*****************************************************************************
//
//! Sets the value of the RTC match 1 register.
//!
//! \param ulMatch is the value for the match register.
//!
//! Sets the match 1 register for the RTC.  The Hibernation module can be
//! configured to wake from hibernation, and/or generate an interrupt when the
//! value of the RTC counter is the same as the match register.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCMatch1Set(unsigned long ulMatch)
{
    //
    // Write the new match value to the match register.
    //
    HWREG(HIB_RTCM1) = ulMatch;

    //
    // Add a delay here to enforce the required delay between write accesses to
    // certain Hibernation module registers.
    //
    if(CLASS_IS_FURY)
    {
        //
        // Delay a fixed time on Fury-class devices
        //
        SysCtlDelay(g_ulWriteDelay);
    }
    else
    {
        //
        // Wait for write complete to be signaled on later devices.
        //
        HibernateWriteComplete();
    }
}

//*****************************************************************************
//
//! Gets the value of the RTC match 1 register.
//!
//! Gets the value of the match 1 register for the RTC.
//!
//! \return Returns the value of the match register.
//
//*****************************************************************************
unsigned long
HibernateRTCMatch1Get(void)
{
    //
    // Return the value of the match register to the caller.
    //
    return(HWREG(HIB_RTCM1));
}

//*****************************************************************************
//
//! Sets the value of the RTC predivider trim register.
//!
//! \param ulTrim is the new value for the pre-divider trim register.
//!
//! Sets the value of the pre-divider trim register.  The input time source is
//! divided by the pre-divider to achieve a one-second clock rate.  Once every
//! 64 seconds, the value of the pre-divider trim register is applied to the
//! predivider to allow fine-tuning of the RTC rate, in order to make
//! corrections to the rate.  The software application can make adjustments to
//! the predivider trim register to account for variations in the accuracy of
//! the input time source.  The nominal value is 0x7FFF, and it can be adjusted
//! up or down in order to fine-tune the RTC rate.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRTCTrimSet(unsigned long ulTrim)
{
    //
    // Check the arguments.
    //
    ASSERT(ulTrim < 0x10000);

    //
    // Write the new trim value to the trim register.
    //
    HWREG(HIB_RTCT) = ulTrim;

    //
    // Add a delay here to enforce the required delay between write accesses to
    // certain Hibernation module registers.
    //
    if(CLASS_IS_FURY)
    {
        //
        // Delay a fixed time on Fury-class devices
        //
        SysCtlDelay(g_ulWriteDelay);
    }
    else
    {
        //
        // Wait for write complete to be signaled on later devices.
        //
        HibernateWriteComplete();
    }
}

//*****************************************************************************
//
//! Gets the value of the RTC predivider trim register.
//!
//! Gets the value of the pre-divider trim register.  This function can be used
//! to get the current value of the trim register prior to making an adjustment
//! by using the HibernateRTCTrimSet() function.
//!
//! \return None.
//
//*****************************************************************************
unsigned long
HibernateRTCTrimGet(void)
{
    //
    // Return the value of the trim register to the caller.
    //
    return(HWREG(HIB_RTCT));
}

//*****************************************************************************
//
//! Stores data in the non-volatile memory of the Hibernation module.
//!
//! \param pulData points to the data that the caller wants to store in the
//! memory of the Hibernation module.
//! \param ulCount is the count of 32-bit words to store.
//!
//! Stores a set of data in the Hibernation module non-volatile memory.  This
//! memory will be preserved when the power to the processor is turned off, and
//! can be used to store application state information which will be available
//! when the processor wakes.  Up to 64 32-bit words can be stored in the
//! non-volatile memory.  The data can be restored by calling the
//! HibernateDataGet() function.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateDataSet(unsigned long *pulData, unsigned long ulCount)
{
    unsigned int uIdx;

    //
    // Check the arguments.
    //
    ASSERT(ulCount <= 64);
    ASSERT(pulData != 0);

    //
    // Loop through all the words to be stored, storing one at a time.
    //
    for(uIdx = 0; uIdx < ulCount; uIdx++)
    {
        //
        // Write a word to the non-volatile storage area.
        //
        HWREG(HIB_DATA + (uIdx * 4)) = pulData[uIdx];

        //
        // Add a delay between writes to the data area.
        //
        if(CLASS_IS_FURY)
        {
            //
            // Delay a fixed time on Fury-class devices
            //
            SysCtlDelay(g_ulWriteDelay);
        }
        else
        {
            //
            // Wait for write complete to be signaled on later devices.
            //
            HibernateWriteComplete();
        }
    }
}

//*****************************************************************************
//
//! Reads a set of data from the non-volatile memory of the Hibernation module.
//!
//! \param pulData points to a location where the data that is read from the
//! Hibernation module will be stored.
//! \param ulCount is the count of 32-bit words to read.
//!
//! Retrieves a set of data from the Hibernation module non-volatile memory
//! that was previously stored with the HibernateDataSet() function.  The
//! caller must ensure that \e pulData points to a large enough memory block to
//! hold all the data that is read from the non-volatile memory.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateDataGet(unsigned long *pulData, unsigned long ulCount)
{
    unsigned int uIdx;

    //
    // Check the arguments.
    //
    ASSERT(ulCount <= 64);
    ASSERT(pulData != 0);

    //
    // Loop through all the words to be restored, reading one at a time.
    //
    for(uIdx = 0; uIdx < ulCount; uIdx++)
    {
        //
        // Read a word from the non-volatile storage area.  No delay is
        // required between reads.
        //
        pulData[uIdx] = HWREG(HIB_DATA + (uIdx * 4));
    }
}

//*****************************************************************************
//
//! Requests hibernation mode.
//!
//! This function requests the Hibernation module to disable the external
//! regulator, thus removing power from the processor and all peripherals.  The
//! Hibernation module will remain powered from the battery or auxiliary power
//! supply.
//!
//! The Hibernation module will re-enable the external regulator when one of
//! the configured wake conditions occurs (such as RTC match or external
//! \b WAKE pin).  When the power is restored the processor will go through a
//! normal power-on reset.  The processor can retrieve saved state information
//! with the HibernateDataGet() function.  Prior to calling the function to
//! request hibernation mode, the conditions for waking must have already been
//! set by using the HibernateWakeSet() function.
//!
//! Note that this function may return because some time may elapse before the
//! power is actually removed, or it may not be removed at all.  For this
//! reason, the processor will continue to execute instructions for some time
//! and the caller should be prepared for this function to return.  There are
//! various reasons why the power may not be removed.  For example, if the
//! HibernateLowBatSet() function was used to configure an abort if low
//! battery is detected, then the power will not be removed if the battery
//! voltage is too low.  There may be other reasons, related to the external
//! circuit design, that a request for hibernation may not actually occur.
//!
//! For all these reasons, the caller must be prepared for this function to
//! return.  The simplest way to handle it is to just enter an infinite loop
//! and wait for the power to be removed.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateRequest(void)
{
    //
    // Set the bit in the control register to cut main power to the processor.
    //
    HWREG(HIB_CTL) |= HIB_CTL_HIBREQ;
}

//*****************************************************************************
//
//! Enables interrupts for the Hibernation module.
//!
//! \param ulIntFlags is the bit mask of the interrupts to be enabled.
//!
//! Enables the specified interrupt sources from the Hibernation module.
//!
//! The \e ulIntFlags parameter must be the logical OR of any combination of
//! the following:
//!
//! - \b HIBERNATE_INT_PIN_WAKE - wake from pin interrupt
//! - \b HIBERNATE_INT_LOW_BAT - low battery interrupt
//! - \b HIBERNATE_INT_RTC_MATCH_0 - RTC match 0 interrupt
//! - \b HIBERNATE_INT_RTC_MATCH_1 - RTC match 1 interrupt
//!
//! \return None.
//
//*****************************************************************************
void
HibernateIntEnable(unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(!(ulIntFlags & ~(HIBERNATE_INT_PIN_WAKE | HIBERNATE_INT_LOW_BAT |
                            HIBERNATE_INT_RTC_MATCH_0 |
                            HIBERNATE_INT_RTC_MATCH_1)));

    //
    // Set the specified interrupt mask bits.
    //
    HWREG(HIB_IM) |= ulIntFlags;
}

//*****************************************************************************
//
//! Disables interrupts for the Hibernation module.
//!
//! \param ulIntFlags is the bit mask of the interrupts to be disabled.
//!
//! Disables the specified interrupt sources from the Hibernation module.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to the HibernateIntEnable() function.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateIntDisable(unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(!(ulIntFlags & ~(HIBERNATE_INT_PIN_WAKE | HIBERNATE_INT_LOW_BAT |
                            HIBERNATE_INT_RTC_MATCH_0 |
                            HIBERNATE_INT_RTC_MATCH_1)));

    //
    // Clear the specified interrupt mask bits.
    //
    HWREG(HIB_IM) &= ~ulIntFlags;
}

//*****************************************************************************
//
//! Registers an interrupt handler for the Hibernation module interrupt.
//!
//! \param pfnHandler points to the function to be called when a hibernation
//! interrupt occurs.
//!
//! Registers the interrupt handler in the system interrupt controller.  The
//! interrupt is enabled at the global level, but individual interrupt sources
//! must still be enabled with a call to HibernateIntEnable().
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateIntRegister(void (*pfnHandler)(void))
{
    //
    // Register the interrupt handler.
    //
    IntRegister(INT_HIBERNATE, pfnHandler);

    //
    // Enable the hibernate module interrupt.
    //
    IntEnable(INT_HIBERNATE);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the Hibernation module interrupt.
//!
//! Unregisters the interrupt handler in the system interrupt controller.  The
//! interrupt is disabled at the global level, and the interrupt handler will
//! no longer be called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
HibernateIntUnregister(void)
{
    //
    // Disable the hibernate interrupt.
    //
    IntDisable(INT_HIBERNATE);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(INT_HIBERNATE);
}

//*****************************************************************************
//
//! Gets the current interrupt status of the Hibernation module.
//!
//! \param bMasked is false to retrieve the raw interrupt status, and true to
//! retrieve the masked interrupt status.
//!
//! Returns the interrupt status of the Hibernation module.  The caller can use
//! this to determine the cause of a hibernation interrupt.  Either the masked
//! or raw interrupt status can be returned.
//!
//! \return Returns the interrupt status as a bit field with the values as
//! described in the HibernateIntEnable() function.
//
//*****************************************************************************
unsigned long
HibernateIntStatus(tBoolean bMasked)
{
    //
    // Read and return the Hibernation module raw or masked interrupt status.
    //
    if(bMasked == true)
    {
        return(HWREG(HIB_MIS) & 0xf);
    }
    else
    {
        return(HWREG(HIB_RIS) & 0xf);
    }
}

//*****************************************************************************
//
//! Clears pending interrupts from the Hibernation module.
//!
//! \param ulIntFlags is the bit mask of the interrupts to be cleared.
//!
//! Clears the specified interrupt sources.  This must be done from within the
//! interrupt handler or else the handler will be called again upon exit.
//!
//! The \e ulIntFlags parameter has the same definition as the \e ulIntFlags
//! parameter to the HibernateIntEnable() function.
//!
//! \note Since there is a write buffer in the Cortex-M3 processor, it may take
//! several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (since NVIC still sees the interrupt source
//! asserted).
//!
//! \return None.
//
//*****************************************************************************
void
HibernateIntClear(unsigned long ulIntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(!(ulIntFlags & ~(HIBERNATE_INT_PIN_WAKE | HIBERNATE_INT_LOW_BAT |
                            HIBERNATE_INT_RTC_MATCH_0 |
                            HIBERNATE_INT_RTC_MATCH_1)));

    //
    // Write the specified interrupt bits into the interrupt clear register.
    //
    HWREG(HIB_IC) |= ulIntFlags;
}

//*****************************************************************************
//
//! Checks to see if the Hibernation module is already powered up.
//!
//! This function queries the control register to determine if the module is
//! already active.  This function can be called at a power-on reset to help
//! determine if the reset is due to a wake from hibernation or a cold start.
//! If the Hibernation module is already active, then it does not need to be
//! re-enabled and its status can be queried immediately.
//!
//! The software application should also use the HibernateIntStatus() function
//! to read the raw interrupt status to determine the cause of the wake.  The
//! HibernateDataGet() function can be used to restore state.  These
//! combinations of functions can be used by the software to determine if the
//! processor is waking from hibernation and the appropriate action to take as
//! a result.
//!
//! \return Returns \b true if the module is already active, and \b false if
//! not.
//
//*****************************************************************************
unsigned int
HibernateIsActive(void)
{
    //
    // Read the control register, and return true if the module is enabled.
    //
    return(HWREG(HIB_CTL) & HIB_CTL_CLK32EN ? 1 : 0);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
