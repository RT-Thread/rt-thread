//###########################################################################
//
// FILE:   sysctl.c
//
// TITLE:  Stellaris style wrapper driver for F2837x system control.
//
//###########################################################################
// $TI Release: F2837xD Support Library v3.05.00.00 $
// $Release Date: Tue Jun 26 03:15:23 CDT 2018 $
// $Copyright:
// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//*****************************************************************************
//
//! \addtogroup sysctl_api
//! @{
//
//*****************************************************************************

#include "F28x_Project.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
//! \internal
//! Checks a peripheral identifier.
//!
//! \param ui32Peripheral is the peripheral identifier.
//!
//! This function determines if a peripheral identifier is valid.
//!
//! \return Returns \b true if the peripheral identifier is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static bool
_SysCtlPeripheralValid(uint32_t ui32Peripheral)
{
    return((ui32Peripheral == SYSCTL_PERIPH_CLA1) ||
           (ui32Peripheral == SYSCTL_PERIPH_DMA) ||
           (ui32Peripheral == SYSCTL_PERIPH_TIMER0) ||
           (ui32Peripheral == SYSCTL_PERIPH_TIMER1) ||
           (ui32Peripheral == SYSCTL_PERIPH_TIMER2) ||
           (ui32Peripheral == SYSCTL_PERIPH_HRPWM) ||
           (ui32Peripheral == SYSCTL_PERIPH_TBCLKSYNC) ||
           (ui32Peripheral == SYSCTL_PERIPH_GTBCLKSYNC) ||
           (ui32Peripheral == SYSCTL_PERIPH_EMIF1) ||
           (ui32Peripheral == SYSCTL_PERIPH_EMIF2) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM1) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM2) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM3) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM4) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM5) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM6) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM7) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM8) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM9) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM10) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM11) ||
           (ui32Peripheral == SYSCTL_PERIPH_EPWM12) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP1) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP2) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP3) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP4) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP5) ||
           (ui32Peripheral == SYSCTL_PERIPH_ECAP6) ||
           (ui32Peripheral == SYSCTL_PERIPH_EQEP1) ||
           (ui32Peripheral == SYSCTL_PERIPH_EQEP2) ||
           (ui32Peripheral == SYSCTL_PERIPH_EQEP3) ||
           (ui32Peripheral == SYSCTL_PERIPH_SD1) ||
           (ui32Peripheral == SYSCTL_PERIPH_SD2) ||
           (ui32Peripheral == SYSCTL_PERIPH_SCI1) ||
           (ui32Peripheral == SYSCTL_PERIPH_SCI2) ||
           (ui32Peripheral == SYSCTL_PERIPH_SCI3) ||
           (ui32Peripheral == SYSCTL_PERIPH_SCI4) ||
           (ui32Peripheral == SYSCTL_PERIPH_SPI1) ||
           (ui32Peripheral == SYSCTL_PERIPH_SPI2) ||
           (ui32Peripheral == SYSCTL_PERIPH_SPI3) ||
           (ui32Peripheral == SYSCTL_PERIPH_I2C1) ||
           (ui32Peripheral == SYSCTL_PERIPH_I2C2) ||
           (ui32Peripheral == SYSCTL_PERIPH_CAN1) ||
           (ui32Peripheral == SYSCTL_PERIPH_CAN2) ||
           (ui32Peripheral == SYSCTL_PERIPH_MCBSP1) ||
           (ui32Peripheral == SYSCTL_PERIPH_MCBSP2) ||
           (ui32Peripheral == SYSCTL_PERIPH_UPP1) ||
           (ui32Peripheral == SYSCTL_PERIPH_ADC1) ||
           (ui32Peripheral == SYSCTL_PERIPH_ADC2) ||
           (ui32Peripheral == SYSCTL_PERIPH_ADC3) ||
           (ui32Peripheral == SYSCTL_PERIPH_ADC4) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS1) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS2) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS3) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS4) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS5) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS6) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS7) ||
           (ui32Peripheral == SYSCTL_PERIPH_CMPSS8) ||
           (ui32Peripheral == SYSCTL_PERIPH_BUFFDAC1) ||
           (ui32Peripheral == SYSCTL_PERIPH_BUFFDAC2) ||
           (ui32Peripheral == SYSCTL_PERIPH_BUFFDAC3));
}
#endif



//*****************************************************************************
//
//! Determines if a peripheral is present.
//!
//! \param ui32Peripheral is the peripheral in question.
//!
//! This function determines if a particular peripheral is present in the
//! device.  Each member of the family has a different peripheral
//! set; this function determines which peripherals are present on this device.
//!
//! \return Returns \b true if the specified peripheral is present and \b false
//! if it is not.
//
//*****************************************************************************
bool
SysCtlPeripheralPresent(uint32_t ui32Peripheral)
{

    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));


    regIndex = ui32Peripheral & SYSCTL_PERIPH_REG_M;
    bitIndex = (ui32Peripheral & SYSCTL_PERIPH_BIT_M) >> SYSCTL_PERIPH_BIT_S;

    if(HWREG(&(DevCfgRegs.DC0.all) + (2 * regIndex)) & (1 << bitIndex)){
        return true;
    }else{
        return false;
    }


}

//*****************************************************************************
//
//! Determines if a peripheral is ready.
//!
//! \param ui32Peripheral is the peripheral in question.
//!
//! This function determines if a particular peripheral is ready to be
//! accessed.  The peripheral may be in a non-ready state if it is not enabled,
//! is being held in reset, or is in the process of becoming ready after being
//! enabled or taken out of reset.
//!
//! \note The ability to check for a peripheral being ready varies based on the
//! part in use.  Please consult the data sheet for the part you are
//! using to determine if this feature is available.
//!
//! \return Returns \b true if the specified peripheral is ready and \b false
//! if it is not.
//
//*****************************************************************************
bool
SysCtlPeripheralReady(uint32_t ui32Peripheral)
{

    uint16_t regIndex;
    uint16_t bitIndex;

    //
    // Check the arguments.
    //
    ASSERT(_SysCtlPeripheralValid(ui32Peripheral));


    regIndex = ui32Peripheral & SYSCTL_PERIPH_REG_M;
    bitIndex = (ui32Peripheral & SYSCTL_PERIPH_BIT_M) >> SYSCTL_PERIPH_BIT_S;

    // Is the peripheral there?
    if(HWREG((uint32_t)&(DevCfgRegs.DC0.all) + (2 * regIndex)) & ((uint32_t)1 << bitIndex)){
        // Is the peripheral enabled?
        if(HWREG((uint32_t)&(CpuSysRegs.PCLKCR0.all) + (2 * regIndex)) & ((uint32_t)1 << bitIndex)){
            // Is the peripheral in reset?
            if((HWREG((uint32_t)&(DevCfgRegs.SOFTPRES0.all) + (2 * regIndex)) & ((uint32_t)1 << bitIndex)) == 0){
                // No?  Ok cool
                return true;
            }
        }
    }else{
        return false;
    }

    return false;
}
//*****************************************************************************
//
//! Resets a peripheral
//!
//! \param ui32Peripheral is the peripheral to reset.
//!
//! The f2837x devices do not have a means of resetting peripherals via
//! via software.  This is a dummy function that does nothing.
//!
//!
//! \return None.
//
//*****************************************************************************
void SysCtlPeripheralReset(uint32_t ui32Peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    regIndex = ui32Peripheral & SYSCTL_PERIPH_REG_M;
    bitIndex = (ui32Peripheral & SYSCTL_PERIPH_BIT_M) >> SYSCTL_PERIPH_BIT_S;

    EALLOW;

    HWREG((uint32_t)&(DevCfgRegs.SOFTPRES0.all) + (2 * regIndex)) |= ((uint32_t)1 << bitIndex);
    asm(" nop");
    asm(" nop");
    asm(" nop");
    asm(" nop");
    HWREG((uint32_t)&(DevCfgRegs.SOFTPRES0.all) + (2 * regIndex)) &= ~((uint32_t)1 << bitIndex);
    EDIS;
}

//*****************************************************************************
//
//! Enables a peripheral.
//!
//! \param ui32Peripheral is the peripheral to enable.
//!
//! Peripherals are enabled with this function.  At power-up, all peripherals
//! are disabled; they must be enabled in order to operate or respond to
//! register reads/writes.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_UART_A, \b SYSCTL_PERIPH_UART_B, \b SYSCTL_PERIPH_UART_C,
//! \b SYSCTL_PERIPH_UART_D, \b SYSCTL_PERIPH_SPI_A, \b SYSCTL_PERIPH_SPI_B,
//! \b SYSCTL_PERIPH_SPI_C, \b SYSCTL_PERIPH_MCBSP_A, \b SYSCTL_PERIPH_MCBSP_B,
//! \b SYSCTL_PERIPH_DMA, \b SYSCTL_PERIPH_USB_A
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralEnable(uint32_t ui32Peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;
    volatile uint32_t test1, test2, test3, test4;

    regIndex = (ui32Peripheral & SYSCTL_PERIPH_REG_M);
    bitIndex = (ui32Peripheral & SYSCTL_PERIPH_BIT_M) >> SYSCTL_PERIPH_BIT_S;

    EALLOW;
    HWREG((uint32_t)&(CpuSysRegs.PCLKCR0.all) + (2 * regIndex)) |= ((uint32_t)1 << bitIndex);

    EDIS;
}

//*****************************************************************************
//
//! Disables a peripheral.
//!
//! \param ui32Peripheral is the peripheral to disable.
//!
//! Peripherals are disabled with this function.  Once disabled, they will not
//! operate or respond to register reads/writes.
//!
//! The \e ui32Peripheral parameter must be only one of the following values:
//! \b SYSCTL_PERIPH_UART_A, \b SYSCTL_PERIPH_UART_B, \b SYSCTL_PERIPH_UART_C,
//! \b SYSCTL_PERIPH_UART_D, \b SYSCTL_PERIPH_SPI_A, \b SYSCTL_PERIPH_SPI_B,
//! \b SYSCTL_PERIPH_SPI_C, \b SYSCTL_PERIPH_MCBSP_A, \b SYSCTL_PERIPH_MCBSP_B,
//! \b SYSCTL_PERIPH_DMA, \b SYSCTL_PERIPH_USB_A
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlPeripheralDisable(uint32_t ui32Peripheral)
{
    uint16_t regIndex;
    uint16_t bitIndex;

    regIndex = ui32Peripheral & SYSCTL_PERIPH_REG_M;
    bitIndex = (ui32Peripheral & SYSCTL_PERIPH_BIT_M) >> SYSCTL_PERIPH_BIT_S;

    EALLOW;

    HWREG((uint32_t)&(CpuSysRegs.PCLKCR0.all) + (2 * regIndex)) &= ~((uint32_t)1 << bitIndex);

    EDIS;
}

//*****************************************************************************
//
//! Resets the device.
//!
//! This function performs a software reset of the entire device.  The
//! processor and all peripherals are reset and all device registers are
//! returned to their default values (with the exception of the reset cause
//! register, which maintains its current value but has the software reset
//! bit set as well).
//!
//! \return This function does not return.
//
//*****************************************************************************
void
SysCtlReset(void)
{
    //
    // Write an incorrect check value to the watchdog control register
    // This will cause a device reset
    //
    EALLOW;
    // Enable the watchdog
    HWREG(&(WdRegs.WDCR.all)) = 0x0028;
    // Write a bad check value
    HWREG(&(WdRegs.WDCR.all)) = 0xFFFF;
    EDIS;

    //
    // The device should have reset, so this should never be reached.  Just in
    // case, loop forever.
    //
    while(1)
    {
    }
}


//*****************************************************************************
//
//! Provides a small delay.
//!
//! \param ulCount is the number of delay loop iterations to perform.
//!
//! This function provides a means of generating a constant length delay.  It
//! is written in assembly to keep the delay consistent across tool chains,
//! avoiding the need to tune the delay based on the tool chain in use.
//!
//! The loop takes 5 cycles/loop + 9.
//!
//! \return None.
//
//*****************************************************************************
#ifdef __TI_COMPILER_VERSION__
    #if __TI_COMPILER_VERSION__ >= 15009000
    __asm(" .def _SysCtlDelay\n"
          " .sect \".TI.ramfunc\"\n"
          " .global  _SysCtlDelay\n"
          "_SysCtlDelay:\n"
          " SUB    ACC,#1\n"
          " BF     _SysCtlDelay,GEQ\n"
          " LRETR\n");    
    #else
    __asm(" .def _SysCtlDelay\n"
          " .sect \"ramfuncs\"\n"
          " .global  _SysCtlDelay\n"
          "_SysCtlDelay:\n"
          " SUB    ACC,#1\n"
          " BF     _SysCtlDelay,GEQ\n"
          " LRETR\n");        
    #endif
#endif

//*****************************************************************************
//
//! Gets the processor clock rate.
//!
//! This function determines the clock rate of the processor clock.
//!
//! \note Because of the many different clocking options available, this
//!  function cannot determine the clock speed of the processor.  This function
//!  should be modified to return the actual clock speed of the processor in
//!  your specific application.
//!
//! \return The processor clock rate.
//
//*****************************************************************************
uint32_t
SysCtlClockGet(uint32_t u32ClockIn)
{

    if((ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL == 0) ||
            (ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL == 2)){
        //10MHz Internal Clock
        u32ClockIn = 10000000;
    }

    //If the pll is enabled calculate its effect on the clock
//    if((HWREG(SYSCTL_SYSPLLCTL) &
//        (SYSCTL_SYSPLLCTL_SPLLEN | SYSCTL_SYSPLLCTL_SPLLCLKEN)) == 3)
    if(ClkCfgRegs.SYSPLLCTL1.bit.PLLEN && ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN)
    {
        //Calculate integer multiplier and fixed divide by 2
//        ulClockIn = ulClockIn *
//                    (HWREG(SYSCTL_SYSPLLMULT) & SYSCTL_SYSPLLMULT_SPLLIMULT_M);
        u32ClockIn = u32ClockIn * ClkCfgRegs.SYSPLLMULT.bit.IMULT;


        //Calculate fractional multiplier
//        switch((HWREG(SYSCTL_SYSPLLMULT) & SYSCTL_SYSPLLMULT_SPLLFMULT_M) >>
//                SYSCTL_SYSPLLMULT_SPLLFMULT_S)
        switch(ClkCfgRegs.SYSPLLMULT.bit.FMULT)
        {
        default:
        case 0:
            break;

        case 1:
            u32ClockIn += u32ClockIn / 4;
            break;

        case 2:
            u32ClockIn += u32ClockIn / 2;
            break;

        case 3:
            u32ClockIn += (u32ClockIn * 3) / 4;
            break;
        }
    }

    if(ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV != 0){
        u32ClockIn /= (2 * ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV);
    }

    return u32ClockIn;

}

//*****************************************************************************
//
//! Gets the low speed peripheral clock rate.
//!
//! This function determines the clock rate of the low speed peripherals.
//!
//! \note Because of the many different clocking options available, this
//!  function cannot determine the clock speed of the processor.  This function
//!  should be modified to return the actual clock speed of the processor in
//!  your specific application.
//!
//! \return The low speed peripheral clock rate.
//
//*****************************************************************************
uint32_t
SysCtlLowSpeedClockGet(uint32_t u32ClockIn)
{

    // Get the main system clock
    u32ClockIn = SysCtlClockGet(u32ClockIn);

    // Apply the divider to the main clock
    if(ClkCfgRegs.LOSPCP.bit.LSPCLKDIV != 0){
        u32ClockIn /= (2 * ClkCfgRegs.LOSPCP.bit.LSPCLKDIV);
    }

    return u32ClockIn;

}

//*****************************************************************************
//
//! Sets the clocking of the device.
//!
//! \param ui32Config is the required configuration of the device clocking.
//!
//! This function configures the clocking of the device.  The oscillator to be 
//! used, SYSPLL fractional and integer multiplier, and the system clock
//! divider are all configured with this function.
//!
//! The \e ui32Config parameter is the logical OR of four values:
//! Clock divider, Integer multiplier, Fractional multiplier, and oscillator
//! source. 
//!
//! The system clock divider is chosen with using the following macro:
//! \b SYSCTL_SYSDIV(x) - "x" is an integer of value 1 or any even value
//!                       up to 126
//!
//! The System PLL fractional multiplier is chosen with one of the following 
//! values:
//! \b SYSCTL_FMULT_0, \b SYSCTL_FMULT_1_4, \b SYSCTL_FMULT_1_2,
//! \b SYSCTL_FMULT_3_4
//!
//! The System PLL integer multiplier is chosen with using the following macro:
//! \b SYSCTL_IMULT(x) - "x" is an integer from 0 to 127
//!
//! The oscillator source is chosen with one of the following values:
//! \b SYSCTL_OSCSRC_OSC2, \b SYSCTL_OSCSRC_XTAL, \b SYSCTL_OSCSRC_OSC1
//!
//! \note The external oscillator must be enabled in order to use an external 
//! clock source.  Note that attempts to disable the oscillator used to clock 
//! the device is prevented by the hardware.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlClockSet(uint32_t ui32Config)
{
    uint32_t clock_source = (ui32Config & SYSCTL_OSCSRC_M) >> SYSCTL_OSCSRC_S;
    uint32_t imult = (ui32Config & SYSCTL_IMULT_M);
    uint32_t fmult = (ui32Config & SYSCTL_FMULT_M) >> SYSCTL_FMULT_S;
    uint32_t divsel = (ui32Config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S;
    
    if((clock_source == ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL)    &&
      (imult         == ClkCfgRegs.SYSPLLMULT.bit.IMULT)           &&
      (fmult         == ClkCfgRegs.SYSPLLMULT.bit.FMULT)           &&
      (divsel        == ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV))
    {
        //everything is set as required, so just return
        return;
    }    
 
    if(clock_source != ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL)
    {
        //Configure Oscillator
        EALLOW;
        switch (clock_source)
        {
            case ((uint32_t)SYSCTL_OSCSRC_OSC2 >> SYSCTL_OSCSRC_S):
                ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF=0;     // Turn on INTOSC2
                ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0; // Clk Src = INTOSC2
				ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=1;        // Turn off XTALOSC
                break;

            case ((uint32_t)SYSCTL_OSCSRC_XTAL >> SYSCTL_OSCSRC_S):
                ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=0;        // Turn on XTALOSC
                ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 1; // Clk Src = XTAL
                break;

            case ((uint32_t)SYSCTL_OSCSRC_OSC1 >> SYSCTL_OSCSRC_S):
                ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 2; // Clk Src = INTOSC1
				ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=1;        // Turn off XTALOSC
                break;
        }
        EDIS; 
    }
    
    EALLOW;
    // first modify the PLL multipliers
    if(imult != ClkCfgRegs.SYSPLLMULT.bit.IMULT || 
       fmult != ClkCfgRegs.SYSPLLMULT.bit.FMULT)
    {
        // Bypass PLL and set dividers to /1
        ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0;

        // Program PLL multipliers
        uint32_t temp_syspllmult = ClkCfgRegs.SYSPLLMULT.all;
        ClkCfgRegs.SYSPLLMULT.all = ((temp_syspllmult & ~(0x37FU)) | 
                                     ((fmult << 8U) | imult));
               
        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1;            // Enable SYSPLL

        // Wait for the SYSPLL lock
        while(ClkCfgRegs.SYSPLLSTS.bit.LOCKS != 1)
        {
            // Uncomment to service the watchdog
            //WdRegs.WDKEY.bit.WDKEY = 0x0055;
            //WdRegs.WDKEY.bit.WDKEY = 0x00AA;
        }

        // Write a multiplier again to ensure proper PLL initialization
        // This will force the PLL to lock a second time
        ClkCfgRegs.SYSPLLMULT.bit.IMULT = imult;        // Setting integer multiplier

        // Wait for the SYSPLL re-lock
        while(ClkCfgRegs.SYSPLLSTS.bit.LOCKS != 1)
        {
            // Uncomment to service the watchdog
            //WdRegs.WDKEY.bit.WDKEY = 0x0055;
            //WdRegs.WDKEY.bit.WDKEY = 0x00AA;
        }        
    }
    
    // Set divider to produce slower output frequency to limit current increase
    if(divsel != (126/2))
    {
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel + 1;
    }
    else
    {
        ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel;
    } 

    // Enable PLLSYSCLK is fed from system PLL clock
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;

    // Small 100 cycle delay
    asm(" RPT #100 || NOP");

    // Set the divider to user value
    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = divsel;    

    EDIS;
}

//*****************************************************************************
//
//! Sets the clocking of the device.
//!
//! \param ui32Config is the required configuration of the device clocking.
//!
//! This function configures the clocking of the device.  The input crystal
//! frequency, oscillator to be used, use of the PLL, and the system clock
//! divider are all configured with this function.
//!
//! The \e ui32Config parameter is the logical OR of several different values,
//! many of which are grouped into sets where only one can be chosen.
//!
//! The system clock divider is chosen with one of the following values:
//! \b SYSCTL_SYSDIV_1, \b SYSCTL_SYSDIV_2, \b SYSCTL_SYSDIV_3, ...
//! \b SYSCTL_SYSDIV_64.
//!
//! The use of the PLL is chosen with either \b SYSCTL_USE_PLL or
//! \b SYSCTL_USE_OSC.
//!
//! The external crystal frequency is chosen with one of the following values:
//! \b SYSCTL_XTAL_4MHZ, \b SYSCTL_XTAL_4_09MHZ, \b SYSCTL_XTAL_4_91MHZ,
//! \b SYSCTL_XTAL_5MHZ, \b SYSCTL_XTAL_5_12MHZ, \b SYSCTL_XTAL_6MHZ,
//! \b SYSCTL_XTAL_6_14MHZ, \b SYSCTL_XTAL_7_37MHZ, \b SYSCTL_XTAL_8MHZ,
//! \b SYSCTL_XTAL_8_19MHZ, \b SYSCTL_XTAL_10MHZ, \b SYSCTL_XTAL_12MHZ,
//! \b SYSCTL_XTAL_12_2MHZ, \b SYSCTL_XTAL_13_5MHZ, \b SYSCTL_XTAL_14_3MHZ,
//! \b SYSCTL_XTAL_16MHZ, \b SYSCTL_XTAL_16_3MHZ, \b SYSCTL_XTAL_18MHZ,
//! \b SYSCTL_XTAL_20MHZ, \b SYSCTL_XTAL_24MHZ, or \b SYSCTL_XTAL_25MHz.
//! Values below \b SYSCTL_XTAL_5MHZ are not valid when the PLL is in
//! operation.
//!
//! The oscillator source is chosen with one of the following values:
//! \b SYSCTL_OSC_MAIN, \b SYSCTL_OSC_INT, \b SYSCTL_OSC_INT4,
//! \b SYSCTL_OSC_INT30, or \b SYSCTL_OSC_EXT32.  \b SYSCTL_OSC_EXT32 is only
//! available on devices with the hibernate module, and then only when the
//! hibernate module has been enabled.
//!
//! The internal and main oscillators are disabled with the
//! \b SYSCTL_INT_OSC_DIS and \b SYSCTL_MAIN_OSC_DIS flags, respectively.
//! The external oscillator must be enabled in order to use an external clock
//! source.  Note that attempts to disable the oscillator used to clock the
//! device is prevented by the hardware.
//!
//! To clock the system from an external source (such as an external crystal
//! oscillator), use \b SYSCTL_USE_OSC \b | \b SYSCTL_OSC_MAIN.  To clock the
//! system from the main oscillator, use \b SYSCTL_USE_OSC \b |
//! \b SYSCTL_OSC_MAIN.  To clock the system from the PLL, use
//! \b SYSCTL_USE_PLL \b | \b SYSCTL_OSC_MAIN, and select the appropriate
//! crystal with one of the \b SYSCTL_XTAL_xxx values.
//!
//! \note If selecting the PLL as the system clock source (that is, via
//! \b SYSCTL_USE_PLL), this function polls the PLL lock interrupt to
//! determine when the PLL has locked.  If an interrupt handler for the
//! system control interrupt is in place, and it responds to and clears the
//! PLL lock interrupt, this function delays until its timeout has occurred
//! instead of completing as soon as PLL lock is achieved.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlAuxClockSet(uint32_t ui32Config)
{
    uint16_t ui16TempDivsel;

    //Bypass PLL
    //Ensure the PLL is out of our clock tree
    EALLOW;
    ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 0;
    EDIS;

    __asm( " RPT #255 || NOP");

    //Configure Oscillator
    EALLOW;
    switch (ui32Config & SYSCTL_OSCSRC_M)
    {
        default:
        case SYSCTL_OSCSRC_OSC2:
            ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF=0;     // Turn on INTOSC2
            ClkCfgRegs.CLKSRCCTL2.bit.AUXOSCCLKSRCSEL = 0; // Clk Src = INTOSC2
			ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=1;        // Turn off XTALOSC
            break;

        case SYSCTL_OSCSRC_XTAL:
            ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=0;        // Turn on XTALOSC
            ClkCfgRegs.CLKSRCCTL2.bit.AUXOSCCLKSRCSEL = 1; // Clk Src = XTAL
            break;

        case SYSCTL_OSCSRC_OSC1:
            ClkCfgRegs.CLKSRCCTL2.bit.AUXOSCCLKSRCSEL = 2; // Clk Src = INTOSC1
			ClkCfgRegs.CLKSRCCTL1.bit.XTALOFF=1;        // Turn off XTALOSC
            break;

    }
    EDIS;

    __asm( " RPT #255 || NOP");

    //Configure PLL if enabled
    if(ui32Config & SYSCTL_PLL_ENABLE)
    {
        EALLOW;
        //modify dividers to maximum to reduce the inrush current
        //set the integer fractional multipliers in one single write
        ClkCfgRegs.AUXPLLMULT.all = ((ui32Config & SYSCTL_IMULT_M) >> SYSCTL_IMULT_S) |
        		                    (((ui32Config & SYSCTL_FMULT_M) >> SYSCTL_FMULT_S) << 8);
        EDIS;

        __asm( " RPT #255 || NOP");

        //Wait for the SYSPLL lock
        while(ClkCfgRegs.AUXPLLSTS.bit.LOCKS != 1)
        {
            // Uncomment to service the watchdog
            // ServiceDog();
        }
    }

    //Configure Dividers
    //increase the freq. of operation in steps to avoid any VDD fluctuations
    ui16TempDivsel = 3;
    while(ClkCfgRegs.AUXCLKDIVSEL.bit.AUXPLLDIV != ((ui32Config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S))
    {
        EALLOW;
        ClkCfgRegs.AUXCLKDIVSEL.bit.AUXPLLDIV = ui16TempDivsel;
        EDIS;
        ui16TempDivsel -= 1;
        if(ClkCfgRegs.AUXCLKDIVSEL.bit.AUXPLLDIV != ((ui32Config & SYSCTL_SYSDIV_M) >> SYSCTL_SYSDIV_S))
        {
            SysCtlDelay(15);
        }
    }

    //Enable PLLSYSCLK is fed from system PLL clock
    EALLOW;
    ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 1;
    EDIS;
}

//*****************************************************************************
//
//! Powers up the USB PLL.
//!
//! This function will enable the USB controller's PLL.
//!
//! \note Because every application is different, the user will likely have to
//! modify this function to ensure the PLL multiplier is set correctly to
//! achieve the 60 MHz required by the USB controller.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlUSBPLLEnable(void)
{
//    // Turn on INTOSC2
//    ClkCfgRegs.CLKSRCCTL1.bit.INTOSC2OFF=0;
//    //Select INTOSC2 as USB PLL Clk In
//    ClkCfgRegs.CLKSRCCTL2.bit.AUXOSCCLKSRCSEL = 0;
//    // Set Aux PLL divider
//    ClkCfgRegs.AUXCLKDIVSEL.bit.AUXPLLDIV = 1;
//    // Set Aux PLL multiplier
//    ClkCfgRegs.AUXPLLMULT.bit.IMULT = 12;
//    // Set Aux PLL fractional multiplier to 0.0
//  ClkCfgRegs.AUXPLLMULT.bit.FMULT = 0;
//    //Enable AUXPLL
//  ClkCfgRegs.AUXPLLCTL1.bit.PLLEN = 1;
//
//    //Wait for the AUXPLL lock
//  while(ClkCfgRegs.AUXPLLSTS.bit.LOCKS != 1)
//  {
//      // Uncomment to service the watchdog
//      // ServiceDog();
//  }
//    // AUXPLLCLK is fed from the AUXPLL
//  ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 1;

}

//*****************************************************************************
//
//! Powers down the USB PLL.
//!
//! This function will disable the USB controller's PLL.  The USB registers
//! are still accessible, but the physical layer will no longer function.
//!
//! \return None.
//
//*****************************************************************************
void
SysCtlUSBPLLDisable(void)
{
    //Disable the PLL
//    ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 0;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


