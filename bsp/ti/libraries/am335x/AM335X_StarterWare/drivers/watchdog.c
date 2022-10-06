/**
 *  \file   watchdog.c
 *
 *  \brief  WATCHDOG TIMER APIs.
 *
 *   This file contains the device abstraction layer APIs for Watchdog Timer.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "hw_types.h"
#include "watchdog.h"

/*******************************************************************************
*                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define WDT_DISABLE_SEQ1           (0x0000AAAAu)
#define WDT_DISABLE_SEQ2           (0x00005555u)
#define WDT_ENABLE_SEQ1            (0x0000BBBBu)
#define WDT_ENABLE_SEQ2            (0x00004444u)

/*******************************************************************************
*                        API FUNCTION DEFINITIONS
*******************************************************************************/

/**
 * \brief   Starts/Enables the watchdog timer. 
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  None.
 *
 **/
void WatchdogTimerEnable(unsigned int baseAdd)
{
    /* Write the first value of the watchdog timer enabling sequence */
    HWREG(baseAdd + WDT_WSPR) = WDT_ENABLE_SEQ1;

    /* Wait until write is successful to WDT_WSPR register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd, 
                                            WDT_WRITE_PENDING_WSPR));

    /* Write the second value of the watchdog timer enabling sequence */
    HWREG(baseAdd + WDT_WSPR) = WDT_ENABLE_SEQ2;

    /* Wait until write is successful to WDT_WSPR register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd, 
                                            WDT_WRITE_PENDING_WSPR));
}

/**
 * \brief   Stops/Disables the watchdog timer.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  None.
 *
 **/
void WatchdogTimerDisable(unsigned int baseAdd)
{
    /* Write the first value of the watchdog timer disabling sequence */
    HWREG(baseAdd + WDT_WSPR) = WDT_DISABLE_SEQ1;

    /* Wait until write is successful to WDT_WSPR register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd,
                                            WDT_WRITE_PENDING_WSPR));

    /* Write the second value of the watchdog timer disabling sequence */
    HWREG(baseAdd + WDT_WSPR) = WDT_DISABLE_SEQ2;

    /* Wait until write is successful to WDT_WSPR register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd,
                                            WDT_WRITE_PENDING_WSPR));
}

/**
 * \brief   Return the revision id of the SOC used.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  Returns the revision id  of the SOC used.
 *
 **/
unsigned int WatchdogTimerRevisionIDGet(unsigned int baseAdd)
{
    /* Return the revision id to the called function */
    return(HWREG(baseAdd + WDT_WIDR));
}

/**
 * \brief   Reset the watchdog timer module.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  None.
 *
 **/
void WatchdogTimerReset(unsigned int baseAdd)
{
    /* Reset the Watchdog timer module */
    HWREG(baseAdd + WDT_WDSC) |= WDT_WDSC_SOFTRESET;

    /* Wait until the reset is done */
    while(!(HWREG(baseAdd + WDT_WDST) & WDT_WDST_RESETDONE));
}

/**
 * \brief   This API will configure and enable the pre-scaler clock.
 *
 * \param   baseAdd      Base Address of the Watchdog Timer Module Register.
 * \param   ptv          Pre-scale clock Timer value.
 *
 * 'ptv' can take the following values \n
 *    WDT_PRESCALER_CLK_DIV_1   - WDT Functional clock divide by 1 \n
 *    WDT_PRESCALER_CLK_DIV_2   - WDT Functional clock divide by 2 \n
 *    WDT_PRESCALER_CLK_DIV_4   - WDT Functional clock divide by 4 \n
 *    WDT_PRESCALER_CLK_DIV_8   - WDT Functional clock divide by 8 \n
 *    WDT_PRESCALER_CLK_DIV_16  - WDT Functional clock divide by 16 \n
 *    WDT_PRESCALER_CLK_DIV_32  - WDT Functional clock divide by 32 \n
 *    WDT_PRESCALER_CLK_DIV_64  - WDT Functional clock divide by 64 \n
 *    WDT_PRESCALER_CLK_DIV_128 - WDT Functional clock divide by 128 \n
 *
 * \return  None.
 *
 **/
void WatchdogTimerPreScalerClkEnable(unsigned int baseAdd, unsigned int ptv)
{
    /* Clear the ptv field of WDT_WCLR register */
    HWREG(baseAdd + WDT_WCLR) &= ~WDT_WCLR_PTV;

    /* Wait until write is successful to WDT_WCLR register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd, 
                                              WDT_WRITE_PENDING_WCLR));

    /* 
    ** Set the ptv field of WDT_WCLR register with the ptv value and also 
    ** enable the pre-scaler clock 
    */                
    HWREG(baseAdd + WDT_WCLR) |= ((ptv & WDT_WCLR_PTV) | 
                                              WDT_WCLR_PRE);               

    /* Wait until write is successful to WDT_WCLR register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd,
                                              WDT_WRITE_PENDING_WCLR));
}

/**
 * \brief   This API will disable the pre-scaler clock.
 *
 * \param   baseAdd      Base Address of the Watchdog Timer Module Register.
 *
 * \return  None.
 *
 **/
void WatchdogTimerPreScalerClkDisable(unsigned int baseAdd)
{
    /* Disable Pre-scaler clock */
    HWREG(baseAdd + WDT_WCLR) &= ~WDT_WCLR_PRE;

    /* Wait until write is successful to WDT_WCLR register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd,
                                              WDT_WRITE_PENDING_WCLR));
}

/**
 * \brief   Set/Write the Counter register with the counter value.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   counter       Count value for the Watchdog Timer.
 *
 * \return  None.
 *
 **/
void WatchdogTimerCounterSet(unsigned int baseAdd, unsigned int countVal)
{
    /* Set the WDT_WCRR register with the countVal */
    HWREG(baseAdd + WDT_WCRR) = countVal;

    /* Wait until write is successful to WDT_WCRR register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd, 
                                            WDT_WRITE_PENDING_WCRR));
}

/**
 * \brief   Get/Read the counter value from the counter register.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the count value present in the Watchdog Timer 
 *            Counter register.
 *
 **/
unsigned int WatchdogTimerCounterGet(unsigned int baseAdd)
{
    /* Read the counter value from WDT_WCRR register */
    return(HWREG(baseAdd + WDT_WCRR));
}

/**
 * \brief   Set the reload count value in the Watchdog timer load register.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   reload        The reload count value of the Watchdog timer.
 *
 * \return  None.
 *
 * \note:   It is recommended to not use reload value as 0xFFFFFFFF. 
 *
 **/
void WatchdogTimerReloadSet(unsigned int baseAdd, unsigned int reloadVal)
{
    /* Load the WDT_WLDR register with the re-load value */
    HWREG(baseAdd + WDT_WLDR) = reloadVal;

    /* Wait until write is successful to the WDT_WLDR register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd, WDT_WRITE_PENDING_WLDR));
}

/**
 * \brief   Get the reload count value from the Watchdog timer load register.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the value present in Watchdog Timer Load Register.
 *
 **/
unsigned int WatchdogTimerReloadGet(unsigned int baseAdd)
{
    /* Return the contents of WDT_WLDR */
    return(HWREG(baseAdd + WDT_WLDR));
}

/**
 * \brief   Set/enable the trigger write access.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   trigVal       Value to be written to the WTGR register.
 *
 * \return  None.
 *
 * \note    This API should be called if the Watchdog timer WDT_WCRR 
 *          register has to be loaded with the WDT_WLDR register before 
 *          overflow occurs. If this API has to be called more than once in an
 *          application then ensure each time this API is called, pass a 
 *          different value to the parameter 'trigVal' to ensure proper working. 
 *
 **/
void WatchdogTimerTriggerSet(unsigned int baseAdd, unsigned int trigVal)
{
    /* Set the WDT_WTGR register with the trigVal*/
    HWREG(baseAdd + WDT_WTGR) = trigVal;

    /* Wait till write is successful to WDT_WTGR register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd, 
                                                  WDT_WRITE_PENDING_WTGR));
}

/**
 * \brief   Load the delay register of Watchdog timer with the delay value.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   delayVal      Delay value. 
 *
 * \return  None.
 *
 **/
void WatchdogTimerDelaySet(unsigned int baseAdd, unsigned int delayVal)
{
    /* Set the WDT_WDLY register with the delayVal */
    HWREG(baseAdd + WDT_WDLY) = delayVal;

    /* Wait until write is successful to the WDT_WDLY register */
    while(WatchdogTimerWritePostedStatusGet(baseAdd, 
          WDT_WRITE_PENDING_WDLY));
}

/**
 * \brief   Return the delay register value of Watchdog timer.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the delay register(WDT_WDLY) value of Watchdog 
 *          timer.
 *
 **/
unsigned int WatchdogTimerDelayGet(unsigned int baseAdd)
{
    /* Return the WDT_WDLY register value */
    return(HWREG(baseAdd + WDT_WDLY));
}

/**
 * \brief   Set IRQ status by software.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to trigger the events.
 *
 * 'intFlags' can take the following values \n
 *    WDT_INT_DELAY - Set the status for delay interrupt \n
 *    WDT_INT_OVERFLOW - Set the status for overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WatchdogTimerIntRawStatusSet(unsigned int baseAdd, unsigned int intFlags)
{
    /* Set the status in the WDT_WIRQSTATRAW register */
    HWREG(baseAdd + WDT_WIRQSTATRAW) = (intFlags & 
                                            (WDT_INT_OVERFLOW | 
                                             WDT_INT_DELAY));
}

/**
 * \brief   Return the Raw IRQ status.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the status of the WDT_WIRQSTATRAW register.
 *
 **/
unsigned int WatchdogTimerIntRawStatusGet(unsigned int baseAdd)
{
    /* Return the status of the WDT_WIRQSTATRAW register */
    return(HWREG(baseAdd + WDT_WIRQSTATRAW));
}

/**
 * \brief   Read the status of WDT_WIRQSTAT register.
 *
 * \param   baseAdd       Base Address of the DMTimer Module Register.
 *
 * \return  This API returns the status of WDT_WIRQSTAT register.
 *
 **/
unsigned int WatchdogTimerIntStatusGet(unsigned int baseAdd)
{
    /* Return the status of WDT_WIRQSTAT register */
    return(HWREG(baseAdd + WDT_WIRQSTAT));
}

/**
 * \brief   Clear IRQ status.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to clear the events.
 *
 * 'intFlags' can take the following values \n
 *    WDT_INT_DELAY - Clear the status for delay interrupt \n
 *    WDT_INT_OVERFLOW - Clear the status for overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WatchdogTimerIntStatusClear(unsigned int baseAdd, unsigned int intFlags)
{
    /* Clear the status in the WDT_WIRQSTAT register */
    HWREG(baseAdd + WDT_WIRQSTAT) = (intFlags & 
                                         (WDT_INT_OVERFLOW | 
                                          WDT_INT_DELAY));
}

/**
 * \brief   Enable Watchdog timer interrupts.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to enable interrupts.
 *
 * 'intFlags' can take the following values \n
 *    WDT_INT_ENABLE_DELAY - Enable the delay interrupt \n
 *    WDT_INT_ENABLE_OVRFLW - Enable the overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WatchdogTimerIntEnable(unsigned int baseAdd, unsigned int intFlags)
{
    /* Enable the watchdog timer interrupts */
    HWREG(baseAdd + WDT_WIRQENSET) = (intFlags & 
                                          (WDT_INT_ENABLE_OVRFLW | 
                                           WDT_INT_ENABLE_DELAY)); 
}

/**
 * \brief   Used to check whether interrupts of Watchdog timer are enabled 
 *          or disabled.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the status of WDT_WIRQENSET register.
 *
 **/
unsigned int WatchdogTimerIntEnableStatusGet(unsigned int baseAdd)
{
    /* Return the status of WDT_WIRQENSET register */
    return(HWREG(baseAdd + WDT_WIRQENSET));
}

/**
 * \brief   Disable Watchdog timer interrupts.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to enable interrupts.
 *
 * 'intFlags' can take the following values \n
 *    WDT_INT_DISABLE_DELAY - Disable the delay interrupt \n
 *    WDT_INT_DISABLE_OVRFLW - Disable the overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WatchdogTimerIntDisable(unsigned int baseAdd, unsigned int intFlags)
{
    /* Disable the Watchdog timer interrupts */
    HWREG(baseAdd + WDT_WIRQENCLR) = (intFlags & 
                                          (WDT_INT_DISABLE_DELAY | 
                                           WDT_INT_DISABLE_OVRFLW));
}

/**
 * \brief   Read the status of WDT_WWPS register.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   flags         Status of the particular field to be returned.
 *
 * 'flags' can take the following values \n
 *    WDT_WRITE_PENDING_WCLR - Write pending for register WDT_WCLR \n
 *    WDT_WRITE_PENDING_WCRR - Write pending for register WDT_WCRR \n
 *    WDT_WRITE_PENDING_WLDR - Write pending for register WDT_WLDR \n
 *    WDT_WRITE_PENDING_WTGR - Write pending for register WDT_WTGR \n
 *    WDT_WRITE_PENDING_WSPR - Write pending for register WDT_WSPR \n
 *    WDT_WRITE_PENDING_WDLY - Write pending for register WDT_WDLY \n
 *
 * \return  Returns the status of Write posted status(WDT_WWPS) register.
 *
 **/
unsigned int WatchdogTimerWritePostedStatusGet(unsigned int baseAdd, unsigned int flags)
{
    /* Return the status of WDT_WWPS register addressed by flags */
    return(HWREG(baseAdd + WDT_WWPS) & flags);
}

/************************* END OF WATCHDOG TIMER DAL **************************/
