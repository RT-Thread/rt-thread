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
 * @file gpmi.c
 * @brief The driver source for the GPMI controller.
 *
 * @ingroup diag_nand
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <assert.h>
#include "sdk.h"
#include "gpmi/gpmi.h"
#include "gpmi_internal.h"
#include "registers/regsapbh.h"
#include "registers/regsgpmi.h"
#include "registers/regsbch.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! Controls whether GPMI timing values should be printed to TSS when they are set.
//! Set to 1 to print timings.
#define GPMI_PRINT_TIMINGS 0

#define MAX_DATA_SETUP_CYCLES (BM_GPMI_TIMING0_DATA_SETUP >> BP_GPMI_TIMING0_DATA_SETUP)

#define MAX_DATA_SAMPLE_DELAY_CYCLES            (uint32_t)(BM_GPMI_CTRL1_RDN_DELAY >> BP_GPMI_CTRL1_RDN_DELAY)
#define GPMI_DELAY_SHIFT                        (3)         // Right shift value to get the fractional GPMI time for data delay
#define GPMI_MAX_DLL_PERIOD_NS                  (32)        // Max GPMI clock Period that the GPMI DLL works for
#define GPMI_DLL_HALF_THRESHOLD_PERIOD_NS       (16)        // Threshold for GPMI clock Period that above thise requires a divide by two for the DLL 
#define GPMI_WAIT_CYCLES_AFTER_DLL_ENABLE       (64)        // Number of GPMI clock cycles to wait for use of GPMI after DLL enable 

#define GPMI_DATA_SETUP_NS                      (0)         // Time in nanoSeconds required for GPMI data read internal setup

#define GPMI_MAX_HARDWARE_DELAY_NS              (uint32_t)(16)        // Time in nanoSeconds required for GPMI data read internal setup

// Max data delay possible for the GPMI.  Use the min 
// of the time (16 nS) or what will fit in the register
// If the GPMI clock period is greater than 
// GPMI_MAX_DLL_PERIOD_NS then can't use the delay.
#define GPMI_GET_MAX_DELAY_NS(x)                ((x < GPMI_MAX_DLL_PERIOD_NS) ? \
                                                (std::min( GPMI_MAX_HARDWARE_DELAY_NS, ((MAX_DATA_SAMPLE_DELAY_CYCLES * x) / u32GpmiDelayFraction))) : \
                                                0)

//! Frequency in kHz for GPMI_CLK. PMI will do its best to give us
//! this frequency when the PLL is enabled.
// #define GPMI_CLK_PLL_ON_FREQUENCY_kHZ (96000)
// 
// //! Frequency to use for GPMI_CLK when the PLL is disabled.
// #define GPMI_CLK_PLL_OFF_FREQUENCY_kHZ (24000)

//! @brief Busy Timeout time in microsec. (10msec)
//!
//! Should only need 100msec (Program/Erase), and reads shouldn't be anywhere near this long..
#define NAND_BUSY_TIMEOUT          (100000)

#define DDI_NAND_HAL_GPMI_SOFT_RESET_LATENCY  (2)

//! @brief Default values for the signal propagation delay.
enum _default_prop_delays
{
    kDefaultMinPropagationDelay = 5,    //!< 5 ns
    kDefaultMaxPropagationDelay = 9     //!< 9 ns
};

//! Timing characteristics that work with every device we've ever known.
#define NAND_SAFESTARTUP_TIMINGS  { 80, 60, 25, 0, 0, 0 }

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

void gpmi_init_apbh();
void gpmi_init_dma_channel(int u32ChipNumber);

uint32_t gpmi_init_data_sample_delay(uint32_t u32GpmiPeriod_ns);
void gpmi_set_and_enable_data_sample_delay(uint32_t u32DelayCycles, uint32_t u32GpmiPeriod_ns);

uint32_t gpmi_get_clock_period_ns(void);

void gpmi_set_timing_internal(const GpmiNandTimings_t * theTimings, 
                                    uint32_t u32GpmiPeriod_ns, 
                                    uint32_t u32PropDelayMin_ns, 
                                    uint32_t u32PropDelayMax_ns);

uint32_t gpmi_find_cycles_ceiling(uint64_t u32NandTime_ns, uint32_t u32GpmiPeriod_ns, uint32_t u32MinVal);
uint32_t gpmi_find_cycles_rounded(uint64_t u32NandTime_ns, uint32_t u32GpmiPeriod_ns);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief The current GPMI driver state information.
GpmiState_t g_gpmi;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

#if GPMI_PRINT_TIMINGS

static void _print_dynamic_timing_summary(
    uint32_t u32GpmiPeriod_ns,
    uint32_t u32GpmiDelayFraction,
    uint32_t i32tEYE,
    uint32_t i32DelayTime_ns,
    uint32_t u32GpmiMaxDelay_ns,
    uint32_t u32DataSetupCycles,
    uint32_t u32DataSetup_ns)
{
    printf("  GpmiPeriod = %d ns@n", u32GpmiPeriod_ns);
    printf("  GpmiDelayFraction = %d@n", u32GpmiDelayFraction);
    printf("  tEYE = %d ns@n", i32tEYE);
    printf("  DelayTime = %d ns@n", i32DelayTime_ns);
    printf("  GpmiMaxDelay = %d ns@n", u32GpmiMaxDelay_ns);
    printf("  DataSetupCycles = %d cycles@n", u32DataSetupCycles);
    printf("  DataSetup = %d ns@n", u32DataSetup_ns);

    return;    
}
#endif  //GPMI_PRINT_TIMINGS

void gpmi_init_apbh()
{
    // APBH - disable reset, enable clock
    // bring APBH out of reset
    HW_APBH_CTRL0_CLR(BM_APBH_CTRL0_SFTRST);
    // Poll until the SFTRST is truly deasserted.
    while (HW_APBH_CTRL0.B.SFTRST);

    HW_APBH_CTRL0_CLR(BM_APBH_CTRL0_CLKGATE);
    // Poll until the CLKGATE is truly deasserted.
    while (HW_APBH_CTRL0.B.CLKGATE);
}

void gpmi_init_dma_channel(int u32ChipNumber)
{
    reg32_t r32ChipDmaNumber = NAND0_APBH_CH + u32ChipNumber;
    reg32_t chipDmaMask = 1 << r32ChipDmaNumber;

    // Reset dma channel
    HW_APBH_CHANNEL_CTRL_SET(BF_APBH_CHANNEL_CTRL_RESET_CHANNEL(chipDmaMask));

    // Wait for the reset to complete
    while (HW_APBH_CHANNEL_CTRL.B.RESET_CHANNEL & chipDmaMask);

    // Clear IRQ
    HW_APBH_CTRL1_CLR(chipDmaMask);
}

int gpmi_init(uint32_t minDelay, uint32_t maxDelay)
{
    // Set and enable GPMI_CLK before doing anything else.
    gpmi_nand_clk_setup();
	
    // Can't use NAND if GPMI block is not present
    if (!(HW_GPMI_STAT_RD() & BM_GPMI_STAT_PRESENT))
    {
        return ERROR_DDI_NAND_GPMI_NOT_PRESENT;
    }
    
    // Init globals.
    gpmi_get_safe_timings(&g_gpmi.currentTimings);
    
    // Apply default values for propagation delay.
    if (minDelay == 0)
    {
        minDelay = kDefaultMinPropagationDelay;
    }

    if (maxDelay == 0)
    {
        maxDelay = kDefaultMaxPropagationDelay;
    }

    g_gpmi.propDelayMin_ns = minDelay;
    g_gpmi.propDelayMax_ns = maxDelay;
    
    // Configure GPMI pins.
    gpmi_iomux_config();

    // Init APBH DMA controller.
    gpmi_init_apbh();
    gpmi_init_dma_channel(0);

    // Soft-reset GPMI
    gpmi_soft_reset();

    // Init ECC engine.
    bch_init();
	
    // Init interrupts. This must be done after APBH, GPMI, and BCH are all ready to roll.
    gpmi_init_interrupts(0);
	
    // Put GPMI in NAND mode, disable DEVICE reset, and make certain polarity is active high, 
    // sample on GPMI clock. We also enable ganged R/B# and DECOUPLE_CS, which allows us to
    // only have to use a single DMA channel.
    HW_GPMI_CTRL1_WR(
        BF_GPMI_CTRL1_DECOUPLE_CS(1) |
        BF_GPMI_CTRL1_GANGED_RDYBUSY(1) |
        BF_GPMI_CTRL1_BCH_MODE(1) |
        BF_GPMI_CTRL1_BURST_EN(1) |
        BF_GPMI_CTRL1_DEV_RESET(BV_GPMI_CTRL1_DEV_RESET__DISABLED) |
        BF_GPMI_CTRL1_ATA_IRQRDY_POLARITY(BV_GPMI_CTRL1_ATA_IRQRDY_POLARITY__ACTIVEHIGH) |
        BF_GPMI_CTRL1_GPMI_MODE(BV_GPMI_CTRL1_GPMI_MODE__NAND));
    
    // Use the failsafe timings and default 24MHz clock
    gpmi_set_timing_internal(&g_gpmi.currentTimings, 0, g_gpmi.propDelayMin_ns, g_gpmi.propDelayMax_ns);
                    
    // Set the timeout for the wait for ready mode.
    gpmi_set_busy_timeout(NAND_BUSY_TIMEOUT);
    
    return SUCCESS;
}
		
////////////////////////////////////////////////////////////////////////////////
//! @brief GPMI Init Data Sample Delay.
//!
//! This function determines the fraction of GPMI period for the data sample 
//! delay period per delay count.  The data sample delay period per cycle is a 
//! fraction of the GPMI clock.  The fraction amount is a function of chip type 
//! and GPMI clock speed.  
//!
//! @param[in]  u32GpmiPeriod_ns GPMI Clock Period in nsec.
//!
//! @return Fraction (ie amount to divide by) of the GPMI period for a delay period
////////////////////////////////////////////////////////////////////////////////
uint32_t gpmi_init_data_sample_delay(uint32_t u32GpmiPeriod_ns)
{
    uint32_t retVal = GPMI_DELAY_SHIFT;
    
    BW_GPMI_CTRL1_DLL_ENABLE(0);                        // Init to a known value
    BW_GPMI_CTRL1_RDN_DELAY(0);                         // Init to a known value
                    
    if (u32GpmiPeriod_ns > GPMI_DLL_HALF_THRESHOLD_PERIOD_NS )
    {
        // the GPMI clock period is high enough that the DLL
        // requires a divide by two
        BW_GPMI_CTRL1_HALF_PERIOD(1);

        // Account for the half period, add 1 to shift (or / by 2)
        retVal++;
    }
	
    return (1 << retVal);
}
    
////////////////////////////////////////////////////////////////////////////////
//! @brief GPMI Set And Start Data Sample Delay.
//!
//! This function sets the NAND Timing register which controls the delay 
//! in the data read sampling.  It then set the delay hardware to be active
//! (if needed by hardware)
//!
//! @param[in]  u32DelayCycles Delay count to put to register
//!
//! @return None
////////////////////////////////////////////////////////////////////////////////
void gpmi_set_and_enable_data_sample_delay(uint32_t u32DelayCycles, uint32_t u32GpmiPeriod_ns)
{
    // DLL_ENABLE must be set to zero when setting RDN_DELAY or HALF_PERIOD!!!
    BW_GPMI_CTRL1_DLL_ENABLE(0);
                    
    if ((u32DelayCycles == 0) || (u32GpmiPeriod_ns > GPMI_MAX_DLL_PERIOD_NS) )
    {
        // If no delay is desired, or if GPMI clock period is out of supported 
        // range, then don't enable the delay
    
        //BW_GPMI_CTRL1_DLL_ENABLE(0);    // This is already done several lines up
        BW_GPMI_CTRL1_RDN_DELAY(0);
        BW_GPMI_CTRL1_HALF_PERIOD(0);
    }
    else
    {
        // Set the delay and needed registers to run.  GPMI_CTRL1_HALF_PERIOD is 
        // assumed to have already been set properly
    
        uint32_t waitTimeNeeded;
                    
        BW_GPMI_CTRL1_RDN_DELAY(u32DelayCycles);
        BW_GPMI_CTRL1_DLL_ENABLE(1);
    
        // After the GPMI DLL has been enable it is reqiured to wait for 
        // GPMI_WAIT_CYCLES_AFTER_DLL_ENABLE number of GPMI clock cycles before 
        // using the GPMI interface.
    
        // calculate out the wait time and convert from nanoSeconds to microSeconds
        waitTimeNeeded = (u32GpmiPeriod_ns * GPMI_WAIT_CYCLES_AFTER_DLL_ENABLE) / 1000;
    
        // wait until the required time for DLL hardware startup has passed.
        hal_delay_us(waitTimeNeeded);
    
    }
}
    
         
////////////////////////////////////////////////////////////////////////////////
//! @brief Find NAND Timing.
//!
//! This function determines the NAND Timing parameter which is given in
//! units of GPMI cycles.  The GPMI period is used to determine how many
//! cycles fit into the NAND parameter.
//!
//! @param[in] u32NandTime_ns The quantity in nsec to be converted to units of GPMI cycles.
//! @param[in] u32GpmiPeriod_ns GPMI Clock Period in nsec.
//! @param[in] u32MinValue Minimum value to be returned, if the computed value is less than
//!     this value.
//!
//! @return Number of GPMI cycles required for this time.
////////////////////////////////////////////////////////////////////////////////
uint32_t gpmi_find_cycles_ceiling(uint64_t u32NandTime_ns, uint32_t u32GpmiPeriod_ns, uint32_t u32MinVal)
{
    uint32_t retVal = ((u32NandTime_ns + (u32GpmiPeriod_ns - 1)) / u32GpmiPeriod_ns);
    return std::max(retVal, u32MinVal);
}

////////////////////////////////////////////////////////////////////////////////
//! @brief Find a NAND timing value that is rounded as appropriate.
//!
//! This function determines the NAND Timing parameter which is given in
//! units of GPMI cycles.  The GPMI period is used to determine how many
//! cycles fit into the NAND parameter, rounding up or down as appropriate.
//!
//! @param[in]  u32NandTime_ns      The quantity in nsec to be converted to units of
//!                                 GPMI cycles.
//! @param[in]  u32GpmiPeriod_ns    GPMI Clock Period in nsec.
//!
//! @return Number of GPMI cycles required for this time.
////////////////////////////////////////////////////////////////////////////////
uint32_t gpmi_find_cycles_rounded(uint64_t u32NandTime_ns, uint32_t u32GpmiPeriod_ns)
{
    return (u32NandTime_ns + (u32GpmiPeriod_ns>>1)) / u32GpmiPeriod_ns;
}

uint32_t gpmi_get_clock_period_ns(void)
{
    uint32_t freq_MHz = get_peri_clock(RAWNAND_CLK);
    return 1000000000 / freq_MHz;
}

////////////////////////////////////////////////////////////////////////////////
//! @brief Compute and setup the NAND clocks.
//!
//! This function sets the GPMI NAND timing based upon the desired NAND timings that
//! are passed in. If the GPMI clock period is non-zero it is used in the
//! calculation of the new register values. If zero is passed instead, the
//! current GPMI_CLK frequency is obtained and used to calculate the period
//! in nanoseconds.
//!
//! @param[in] theTimings  Pointer to a nand-timing Structure with Address Setup, Data Setup and Hold, etc.
//!                             This structure must be one of those that contains an eState element,
//!                             so this function can tell how to crack it and process it.
//! @param[in]  u32GpmiPeriod_ns GPMI Clock Period in nsec. May be zero, in
//!                             which case the actual current GPMI_CLK period is used.
//! @param[in] u32PropDelayMin_ns Minimum propagation delay in nanoseconds.
//! @param[in] u32PropDelayMax_ns Maximum propagation delay in nanoseconds.
////////////////////////////////////////////////////////////////////////////////
void gpmi_set_timing_internal(const GpmiNandTimings_t * theTimings, 
                                    uint32_t u32GpmiPeriod_ns, 
                                    uint32_t u32PropDelayMin_ns, 
                                    uint32_t u32PropDelayMax_ns)
{
    uint32_t u32GpmiDelayFraction;
    int32_t u32GpmiMaxDelay_ns;
    uint32_t u32AddressSetupCycles;
    uint32_t u32DataSetupCycles;
    uint32_t u32DataHoldCycles;
    uint32_t u32DataSampleDelayCycles;
    uint32_t u32DataSetup_ns;
    int32_t  i32tEYE;
    int32_t  i32DelayTime_ns;
#if GPMI_PRINT_TIMINGS
    char bPrintInterimTimings = false;
#endif
	
    assert(theTimings);
	
    // If u32GpmiPeriod is passed in as 0, we get the current GPMI_CLK frequency
    // and compute the period in ns.
    if (u32GpmiPeriod_ns == 0)
    {
        u32GpmiPeriod_ns = gpmi_get_clock_period_ns();
    }
	
    u32GpmiDelayFraction = gpmi_init_data_sample_delay(u32GpmiPeriod_ns);
                    
    u32GpmiMaxDelay_ns = GPMI_GET_MAX_DELAY_NS(u32GpmiPeriod_ns);
    
	
#if GPMI_PRINT_TIMINGS
    printf("NAND GPMI timings:@n");
#endif
    
    /* *******************************************************************
        Process the given AddressSetup, DataSetup, and DataHold
        parameters
    ******************************************************************* */
                    
    // The chip hardware quantizes the setup and hold parameters to intervals of
    // the GPMI clock period.
    // Quantize the setup and hold parameters to the next-highest GPMI clock period to
    // make sure we use at least the requested times.
    //
    // For DataSetup and DataHold, the chip interprets a value of zero as the largest
    // amount of delay supported.  This is not what's intended by a zero
    // in the input parameter, so we modify the zero input parameter to
    // the smallest supported value.
    
    u32AddressSetupCycles = gpmi_find_cycles_ceiling(theTimings->tSU, u32GpmiPeriod_ns, 0);
    u32DataSetupCycles    = gpmi_find_cycles_ceiling(theTimings->tDS, u32GpmiPeriod_ns, 1);
    u32DataHoldCycles     = gpmi_find_cycles_ceiling(theTimings->tDH, u32GpmiPeriod_ns, 1);
                    
	
//     switch (theTimings->eState)
//     {
//         case e_NAND_Timing_State_STATIC_DSAMPLE_TIME:
//         {
//             // Get delay time and include required chip read setup time
//             i32DelayTime_ns = theTimings->u8DSAMPLE_TIME + GPMI_DATA_SETUP_NS;
//     
//             // Extend the Data Setup time as needed to reduce delay time below 
//             // the max supported by hardware.  Also keep DataSetup in allowable range
//             while ((i32DelayTime_ns > u32GpmiMaxDelay_ns) && (u32DataSetupCycles  < MAX_DATA_SETUP_CYCLES))
//             {
//                 u32DataSetupCycles++;
//                 i32DelayTime_ns -= u32GpmiPeriod_ns;
//                 if (i32DelayTime_ns < 0)
//                 {
//                     i32DelayTime_ns = 0;
//                 }
//             }
//                     
//             u32DataSampleDelayCycles = std::min( gpmi_find_cycles_ceiling( (u32GpmiDelayFraction * i32DelayTime_ns), u32GpmiPeriod_ns, 0), MAX_DATA_SAMPLE_DELAY_CYCLES);
// 	
// #if GPMI_PRINT_TIMINGS
//             printf("(--static--)@n");
// #endif
//             break;
//         } // case e_NAND_Timing_State_STATIC_DSAMPLE_TIME:
//     
//         case e_NAND_Timing_State_DYNAMIC_DSAMPLE_TIME:
//         {
	
    
            // Compute the times associated with the quantized number of GPMI cycles.
            u32DataSetup_ns = u32GpmiPeriod_ns * u32DataSetupCycles;
                    
            // This accounts for chip specific GPMI read setup time on the data sample 
            // circuit.  See 378x datasheet "14.3.4. High-Speed NAND Timing"
            u32PropDelayMax_ns += GPMI_DATA_SETUP_NS;
                    
         /* *******************************************************************
                Compute tEYE, the width of the data eye when reading from the NAND.
            ******************************************************************* */
    
            // Note that we use the quantized versions of setup and hold, because the chip
            // uses these quantized values, and these timings create the eye.
            //
            // end of the eye = u32PropDelayMin_ns + theTimings->tRHOH + u32DataSetup_ns
            // start of the eye = u32PropDelayMax_ns + theTimings->tREA
            i32tEYE = ( (int)u32PropDelayMin_ns + (int)theTimings->tRHOH + (int)u32DataSetup_ns ) - ( (int)u32PropDelayMax_ns + (int)theTimings->tREA );
                    
                         
            // The eye has to be open.  Constrain tEYE to be greater than zero
            // and the number of DataSetup cycles to fit in the timing register.
            while ( (i32tEYE <= 0) && (u32DataSetupCycles  < MAX_DATA_SETUP_CYCLES) )
            {
                // The eye is not open.  An increase in data-setup time 
                // causes a coresponding increase to size of the eye.
                u32DataSetupCycles++;                               // Give an additional DataSetup cycle
                u32DataSetup_ns += u32GpmiPeriod_ns;                // Keep DataSetup time in step with cycles
                i32tEYE += u32GpmiPeriod_ns;                        // And adjust the tEYE accordingly
    
            } // while ( i32tEYE
	
   
         /* *******************************************************************
                Compute the ideal point at which to sample the data
                at the center of tEYE.
            ******************************************************************* */
    
            // Find the delay to get the center in time-units.
            // Delay for center of the eye = ((end of the eye + start of the eye) / 2) - DataSetup
            // This simplifies to the following:
            i32DelayTime_ns = ( (int)u32PropDelayMax_ns + (int)theTimings->tREA + (int)u32PropDelayMin_ns + (int)theTimings->tRHOH - (int)u32DataSetup_ns ) >> 1;
    
            // The chip can't accomodate a negative parameter for the sample point.
            if ( i32DelayTime_ns < 0 ) i32DelayTime_ns = 0;
    
            //  Make sure the required DelayTime does not exceed the max allowed value.
            //  Also make sure the quantized DelayTime (at u32DataSampleDelayCycles) is 
            //  within the eye.  
            //
            //  Increasing DataSetup decreases the length of DelayTime 
            //  required to get to into the eye.  Increasing DataSetup also moves the rear 
            //  of the eye back, enlarges the eye (helpful in the case where quantized 
            //  DelayTime does not fall inside the initial eye).
            //          
            //          ____                   __________________________________________
            //  RDN         \_________________/
            //
            //                                               <----- tEYE ---->
            //                                             /--------------------\                    x
            //  Read Data --------------------------------<                      >-------
            //                                             \--------------------/
            //              ^                 ^                      ^   tEYE/2     ^
            //              |                 |                      |              |
            //              |<---DataSetup--->|<-----DelayTime------>|              |
            //              |                 |                      |              |
            //              |                 |                                     |
            //              |                 |<------quantized DelayTime---------->|
            //              |                 |                                     |
            //                                      
    
            #if GPMI_PRINT_TIMINGS
            printf("(--dynamic--)(--Start--)@n");
            _print_dynamic_timing_summary(
                u32GpmiPeriod_ns,
                u32GpmiDelayFraction,
                i32tEYE,
                i32DelayTime_ns,
                u32GpmiMaxDelay_ns,
                u32DataSetupCycles,
                u32DataSetup_ns);
            #endif
            
            // Extend the Data Setup time as needed to reduce delay time below 
            // the max allowable value.  Also keep DataSetup in allowable range
            while ((i32DelayTime_ns > u32GpmiMaxDelay_ns) && (u32DataSetupCycles  < MAX_DATA_SETUP_CYCLES))
            {
                #if GPMI_PRINT_TIMINGS
                if ( !bPrintInterimTimings )
                {
                    // Print an explanation once now...
                    printf("(DelayTime > GPMI max %d) and DataSetupCycles < max %d. Adjusting DelayTime.@n",u32GpmiMaxDelay_ns,MAX_DATA_SETUP_CYCLES );
                    // ...and print an interim list of timings afterward.
                    bPrintInterimTimings = true;
                }
                #endif
                u32DataSetupCycles++;                               // Give an additional DataSetup cycle
                u32DataSetup_ns += u32GpmiPeriod_ns;                // Keep DataSetup time in step with cycles
                i32tEYE += u32GpmiPeriod_ns;                        // And adjust the tEYE accordingly
                i32DelayTime_ns -= (u32GpmiPeriod_ns >> 1);         // decrease DelayTime by one half DataSetup cycle worth, to keep in the middle of the eye
                if (i32DelayTime_ns < 0)
                {
                    i32DelayTime_ns = 0;                            // Do not allow DelayTime less than zero
                }
            }

            // The DelayTime parameter is expressed in the chip in units of fractions of GPMI clocks.
            // Convert DelayTime to an integer quantity of fractional GPMI cycles..
            u32DataSampleDelayCycles = std::min( gpmi_find_cycles_ceiling( (u32GpmiDelayFraction * i32DelayTime_ns), u32GpmiPeriod_ns, 0), MAX_DATA_SAMPLE_DELAY_CYCLES);

            #if GPMI_PRINT_TIMINGS
            if ( bPrintInterimTimings )
            {
                _print_dynamic_timing_summary(
                    u32GpmiPeriod_ns,
                    u32GpmiDelayFraction,
                    i32tEYE,
                    i32DelayTime_ns,
                    u32GpmiMaxDelay_ns,
                    u32DataSetupCycles,
                    u32DataSetup_ns);
                bPrintInterimTimings = false;
            }
	
            #endif
            #define DSAMPLE_IS_NOT_WITHIN_THE_DATA_EYE  ( i32tEYE>>1 < std::abs( (int32_t)((u32DataSampleDelayCycles * u32GpmiPeriod_ns) / u32GpmiDelayFraction) - i32DelayTime_ns ))
                    
            // While the quantized DelayTime is out of the eye reduce the DelayTime or extend 
            // the DataSetup to get in the eye.  Do not allow the number of DataSetup cycles to 
            // exceed the max supported by hardware.
            while ( DSAMPLE_IS_NOT_WITHIN_THE_DATA_EYE
                    && (u32DataSetupCycles  < MAX_DATA_SETUP_CYCLES) )
            {
                #if GPMI_PRINT_TIMINGS
                if ( !bPrintInterimTimings )
                {
                    // Print an explanation once now.
                    printf("Data sample point not within data eye.  Adjusting.@n" );
                    bPrintInterimTimings = true;
                }
                #endif
                if ( (int32_t)((u32DataSampleDelayCycles * u32GpmiPeriod_ns) / u32GpmiDelayFraction) > i32DelayTime_ns )
                {
                    // If quantized DelayTime is greater than max reach of the eye decrease quantized 
                    // DelayTime to get it into the eye or before the eye
	
                    if (u32DataSampleDelayCycles != 0)
                    {
                        u32DataSampleDelayCycles--;
                    }
                }
                else
                {
                    // If quantized DelayTime is less than min reach of the eye, shift up the sample 
                    // point by increasing DataSetup.  This will also open the eye (helping get 
                    // quantized DelayTime in the eye)
                    u32DataSetupCycles++;                           // Give an additional DataSetup cycle
                    u32DataSetup_ns += u32GpmiPeriod_ns;            // Keep DataSetup time in step with cycles
                    i32tEYE         += u32GpmiPeriod_ns;            // And adjust the tEYE accordingly
                    i32DelayTime_ns -= (u32GpmiPeriod_ns >> 1);     // decrease DelayTime by one half DataSetup cycle worth, to keep in the middle of the eye
                    i32DelayTime_ns -= u32GpmiPeriod_ns;            // ...and one less period for DelayTime.
    
                    if ( i32DelayTime_ns < 0 ) i32DelayTime_ns = 0; // keep DelayTime from going negative
                    
                    // Convert time to GPMI cycles and make sure the number of 
                    // cycles fit in the coresponding hardware register...
                    u32DataSampleDelayCycles = std::min( gpmi_find_cycles_ceiling( (u32GpmiDelayFraction * i32DelayTime_ns), u32GpmiPeriod_ns, 0), MAX_DATA_SAMPLE_DELAY_CYCLES);
                }
	
            }   // while ( DSAMPLE_IS_NOT_WITHIN_THE_DATA_EYE )
    
#if GPMI_PRINT_TIMINGS
            printf("(--Final--)@n");
            _print_dynamic_timing_summary(
                u32GpmiPeriod_ns,
                u32GpmiDelayFraction,
                i32tEYE,
                i32DelayTime_ns,
                u32GpmiMaxDelay_ns,
                u32DataSetupCycles,
                u32DataSetup_ns);
//            hal_delay_us(GPMI_PRINT_DELAY);
#endif
                    
//             break;
//         } //case e_NAND_Timing_State_DYNAMIC_DSAMPLE_TIME:
// 	
//         default:
// #if GPMI_PRINT_TIMINGS
//             printf("(--unchanged--)@n");
// #endif
//             return;
//     }
    
#if GPMI_PRINT_TIMINGS
    printf("GPMI (tDS, tDH, tAS, DelayT) = (%d, %d, %d, %d) ns@n",
                    u32GpmiPeriod_ns * u32DataSetupCycles,
                    u32GpmiPeriod_ns * u32DataHoldCycles,
                    u32GpmiPeriod_ns * u32AddressSetupCycles,
                    ((u32GpmiPeriod_ns * u32DataSampleDelayCycles) / u32GpmiDelayFraction) );
//    hal_delay_us(GPMI_PRINT_DELAY);
	
    printf("(DataSetup, DataHold, AddressSetup, DelayTime) = (%d, %d, %d, %d) Count@n",
                    u32DataSetupCycles,
                    u32DataHoldCycles,
                    u32AddressSetupCycles,
                    u32DataSampleDelayCycles );
    
//    hal_delay_us(GPMI_PRINT_DELAY);
#endif
                    
    // Set the values in the registers.
    HW_GPMI_TIMING0_WR( BF_GPMI_TIMING0_ADDRESS_SETUP(u32AddressSetupCycles)
                        | BF_GPMI_TIMING0_DATA_SETUP(u32DataSetupCycles)
                        | BF_GPMI_TIMING0_DATA_HOLD(u32DataHoldCycles));
                         
    gpmi_set_and_enable_data_sample_delay(u32DataSampleDelayCycles, u32GpmiPeriod_ns);
    
    return;
}
                    
void gpmi_set_busy_timeout(uint32_t busyTimeout)
{
    // Get current GPMI_CLK period in nanoseconds.
//     uint32_t u32GpmiPeriod_ns = gpmi_get_clock_period_ns();
//     
//     // Convert from microseconds to nanoseconds.
//     uint64_t busyTimeout_ns = busyTimeout * 1000;
//     
//     // Divide the number of GPMI_CLK cycles for the timeout by 4096 as the
//     // timeout register expects.
//     uint32_t busyTimeout_gpmiclk = gpmi_find_cycles_ceiling(busyTimeout_ns, u32GpmiPeriod_ns, 0) / 4096;
//     
//     // The busy timeout field is only 16 bits, so make sure the desired timeout will fit.
//     if ((busyTimeout_gpmiclk & 0xffff0000) != 0)
//     {
//         // Set the timeout to the maximum value.
//         busyTimeout_gpmiclk = 0xffff;
//     }
    
    HW_GPMI_TIMING1_WR(BF_GPMI_TIMING1_DEVICE_BUSY_TIMEOUT(0xffff)); //busyTimeout_gpmiclk));
}
    
void gpmi_disable()
{
    // Gate clocks to GPMI.
    BW_GPMI_CTRL0_CLKGATE(1);
    
    // Disable BCH as well.
    bch_disable();
}
    
void gpmi_enable_writes(bool bClearOrSet)
{
    if (bClearOrSet)
    {
        HW_GPMI_CTRL1_SET(BM_GPMI_CTRL1_DEV_RESET);
    }
    else
    {
        HW_GPMI_CTRL1_CLR(BM_GPMI_CTRL1_DEV_RESET);
    }
}
    
void gpmi_soft_reset(void)
{
    // Reset the GPMI_CTRL0 block.
    // Prepare for soft-reset by making sure that SFTRST is not currently
    // asserted.  Also clear CLKGATE so we can wait for its assertion below.
    HW_GPMI_CTRL0_CLR(BM_GPMI_CTRL0_SFTRST);

    // Wait at least a microsecond for SFTRST to deassert.
    hal_delay_us(DDI_NAND_HAL_GPMI_SOFT_RESET_LATENCY);
    while (HW_GPMI_CTRL0.B.SFTRST);

    // Also clear CLKGATE so we can wait for its assertion below.
    HW_GPMI_CTRL0_CLR(BM_GPMI_CTRL0_CLKGATE);

    // Now soft-reset the hardware.
    HW_GPMI_CTRL0_SET(BM_GPMI_CTRL0_SFTRST);

    // Poll until clock is in the gated state before subsequently
    // clearing soft reset and clock gate.
    while (!HW_GPMI_CTRL0.B.CLKGATE);

    // bring GPMI_CTRL0 out of reset
    HW_GPMI_CTRL0_CLR(BM_GPMI_CTRL0_SFTRST);

    // Wait at least a microsecond for SFTRST to deassert. In actuality, we
    // need to wait 3 GPMI clocks, but this is much easier to implement.
    hal_delay_us(DDI_NAND_HAL_GPMI_SOFT_RESET_LATENCY);
    while (HW_GPMI_CTRL0.B.SFTRST);

    HW_GPMI_CTRL0_CLR(BM_GPMI_CTRL0_CLKGATE);

    // Poll until clock is in the NON-gated state before returning.
    while (HW_GPMI_CTRL0.B.CLKGATE);
}

void gpmi_set_timings(const GpmiNandTimings_t * newTimings)
{
    // Handle a NULL newTimings (means clock-change only, so use old newTimings)
    if (newTimings != NULL)
    {
        // We have a new set of timings at the newTimings parameter.
        // Copy the new timing-table into the static table.
        g_gpmi.currentTimings = *newTimings;
    }

    // Pass 0 for period to use 24MHz default.
    gpmi_set_timing_internal(&g_gpmi.currentTimings, 0, g_gpmi.propDelayMin_ns, g_gpmi.propDelayMax_ns);
}

void gpmi_get_safe_timings(GpmiNandTimings_t * timings)
{
    const GpmiNandTimings_t safeTimings = NAND_SAFESTARTUP_TIMINGS;
    *timings = safeTimings;
}

const GpmiNandTimings_t * gpmi_get_current_timings()
{
    return &g_gpmi.currentTimings;
}

int gpmi_wait_for_dma(uint32_t u32usec, uint32_t chipSelect)
{
    reg32_t     r32ChipDmaNumber = NAND0_APBH_CH; // + chipSelect;
    bool        bTimedOut = FALSE;
    int  rtStatus = SUCCESS;

#if 1 //def RTOS_THREADX
    // Wait for the IRQ to unlock the spinlock.
    int lockResult = spinlock_lock(&g_gpmi.dmaInfo.irqSpinlock, u32usec);

    // Note that, in the RTOS_THREADX case, SEMA.PHORE register can easily be nonzero if the CPU is running fast.
    // (The DMA engine can trigger the ISR at the end of the DMA, before decrementing
    // the SEMA.PHORE count, thus creating a race condition that lets us find a
    // nonzero SEMA.PHORE value here.)
    //
    // Since SEMA.PHORE can still be nonzero, we cannot use it as
    // evidence of timeout.  We have to rely on the RTOS timeout indicator.
    bTimedOut = (lockResult != 0); //( TX_SUCCESS != retCode_tx_semaphore );

#else   // RTOS_THREADX not defined
    // Poll for DMA completion.
    {
        uint64_t u64StartTime;

        // Microsecond read - always read at start of transaction so that if
        // ThreadX times out, that time is included in the overall timeout time.
        u64StartTime = g_gpmi.dmaInfo.uStartDMATime;

        // End of DMA chain will decrement the hardware semaphore.  Poll the hardware semaphore for
        // DMA completion.
        do {
            i32Sema = HW_APBH_CHn_SEMA_RD(r32ChipDmaNumber) & BM_APBH_CHn_SEMA_PHORE;
        } while ((i32Sema != 0) && ( (hw_profile_GetMicroseconds() - u64StartTime) < u32usec));
    }

    // Re-read the hardware semaphore in case a higher-priority thread caused the timeout between semaphore
    // and timeout test.
    i32Sema = HW_APBH_CHn_SEMA_RD(r32ChipDmaNumber) & BM_APBH_CHn_SEMA_PHORE;

    bTimedOut = (0 != i32Sema);
    
#endif  // ifdef RTOS_THREADX

    //
    // If timeout: return error,
    //       else: return BAR field from last DMA command
    //

    if ( bTimedOut )
    {
        // The DMA has not completed within the alotted time.
        //
        // Clean up.

        //! @todo Since we don't know exactly what caused the timeout, it 
        //! could be beneficial to also reset the GPMI block here.
        //! Note, however, that soft-resetting the GPMI block changes
        //! its register settings.  Thus, it would also be necessary to
        //! re-initialize the GPMI settings completely.  Otherwise the
        //! GPMI may not work.

        // abort dma by resetting channel
//         BW_APBH_CHANNEL_CTRL_RESET_CHANNEL(1 << r32ChipDmaNumber);
//         
//         // Wait for the reset to complete
//         while ( HW_APBH_CHANNEL_CTRL.B.RESET_CHANNEL & (0x1 << r32ChipDmaNumber) )
//         {
//             ;
//         }
// 
//         //
//         // Okay, this is important.
//         // When we read from the NAND using GPMI with ECC,
//         // there will be an ECC interrupt upon completion of the ECC correction.
//         // Thereafter, these actions must happen in sequence:
//         //     1.  ECC status must be read.
//         //     2.  ECC ISR must be reenabled.
//         //     3.  ECC-completion must be cleared, which frees the ECC
//         //         block to process the next data.
//         // The status must be read before the ECC-completion is cleared, or
//         // the next ECC cycle will overwrite the status.  In the case of a
//         // successful DMA and ECC, the code that reads the ECC status
//         // also performs steps 2 and 3.
//         // 
//         // Q:  What happens if the DMA times-out for some reason?
//         // A:  Somebody may have to clean-up by using steps 2 and 3.
//         //     That somebody is us.
//         //
// 
//         // If there was an ECC-completion expected...
//         if (kNandGpmiDmaWaitMask_Ecc & g_gpmi.dmaInfo.u16DmaWaitMask)
//         {
//             // ...then we have to clear the ECC-completion and the ECC circuit.
// 
//             // It is not necessary to reset the BCH block after an "uncorrectable" error.
//             // In fact, due to a 378x chip bug it is not possible to reset the
//             // BCH block after it has been used to transfer data.
// 
//             // Clear the ECC-completion.
//             gpmi_clear_ecc_isr_enable( );
//         }

        rtStatus = ERROR_DDI_NAND_GPMI_DMA_TIMEOUT;
    }
    else
    {
        // The DMA descriptor chain was set up with the alternate meaning
        // of the BAR register.  Rather than containing an
        // address at this point, it contains a return-code that indicates whether
        // the "success" or "failure" part of the chain executed last.
        // So, here we get that return code.
        rtStatus = (int)BF_RDn(APBH_CHn_BAR, r32ChipDmaNumber, ADDRESS);
    }

    return rtStatus;
}

int gpmi_run_dma(apbh_dma_t * theDma, unsigned chipSelect, uint16_t waitMask, uint32_t timeout)
{
    uint32_t    physicalCommandAddress;
    reg32_t     r32ChipDmaNumber        = (NAND0_APBH_CH); //+chipSelect);
    reg32_t     r32ChannelMask          = (0x1 << r32ChipDmaNumber);
    bool        bDmaIsRunning;
    int  rtStatus = SUCCESS;

    // Save off the chip that we're watching in the DMA completion structure.
    g_gpmi.dmaInfo.u16CurrentChip = chipSelect;
    
    // We're using DMA channel 0 for all DMAs.
    g_gpmi.dmaInfo.dmaChannel = 0;

    // Set the criteria for finishing this DMA.
    g_gpmi.dmaInfo.u16DmaWaitMask      = waitMask;

    // Clear the status word used to check the criteria for finishing this DMA.
    g_gpmi.dmaInfo.u16DmaWaitStatus    = kNandGpmiDmaWaitMask_Nothing;

    // Alert me if a DMA chain is currently running!!
    // Note that this checks the SEMA.PHORE register field for the DMA.
    bDmaIsRunning = gpmi_is_dma_active(chipSelect);

    if (bDmaIsRunning)
    {
        rtStatus = ERROR_DDI_NAND_GPMI_DMA_BUSY;

        goto _standardExit;
    }

    // At this point, there should be no DMA running.
    // Sanity-test to make sure the DMA channel IRQ is deasserted.
    // (Note that the optimizing compiler will probably combine the
    // body of this section with the previous section.)
    if ( 0 != (HW_APBH_CTRL1_RD() & (r32ChannelMask << BP_APBH_CTRL1_CH0_CMDCMPLT_IRQ)) )
    {
        rtStatus = ERROR_DDI_NAND_GPMI_DMA_BUSY;

        goto _standardExit;
    }

    // Get the physical address of the DMA chain.
    physicalCommandAddress = (uint32_t)nand_virtual_to_physical(theDma);

    // Flush the data cache. We don't need to invalidate since the hardware is only reading
    // the DMA chain, not writing to it. If the caller set the length to 0, then they don't
    // want us to flush the cache, probably because they just flushed the entire cache already.
//     if (dmaCommandLength > 0)
//     {
//         hw_core_clean_DCache_MVA_BySize((uint32_t)pDmaCmd, dmaCommandLength);
//     }
    
    // Initialize DMA by setting up NextCMD field
    HW_APBH_CHn_NXTCMDAR_WR(r32ChipDmaNumber, (reg32_t)physicalCommandAddress);

    // Start DMA by incrementing the semaphore.
    BW_APBH_CHn_SEMA_INCREMENT_SEMA(r32ChipDmaNumber, 1);

    // Record the time that I started the transaction
    // Used in the NAND_HAL_Dma_Status function below and the ddi_gpmi_wait_for_dma
    // function above to determine timeouts.
    g_gpmi.dmaInfo.uStartDMATime = time_get_microseconds();

    rtStatus = gpmi_wait_for_dma(timeout, chipSelect);

_standardExit:

    return rtStatus;
}

bool gpmi_is_dma_active(uint32_t chipSelect)
{
    uint32_t    u32Sema;
    reg32_t     r32ChipDmaNumber    = (NAND0_APBH_CH); //+chipSelect);
    uint32_t    u32Run;

    u32Sema = HW_APBH_CHn_SEMA_RD(r32ChipDmaNumber) & BM_APBH_CHn_SEMA_PHORE;

    u32Run = BF_RD(GPMI_CTRL0, RUN);

    // A nonzero value for either of these means a DMA is running.
    return ( u32Sema | u32Run );
}

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
