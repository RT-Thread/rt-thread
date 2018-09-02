//###########################################################################
//
// FILE:   F2837xD_Adc.c
//
// TITLE:  F2837xD Adc Support Functions.
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

//
// Included Files
//
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

//
// AdcSetMode - Set the resolution and signalmode for a given ADC. This will
//              ensure that the correct trim is loaded.
//
// NOTE!!! There is no EALLOW/EDIS in this function! You need to make sure you
// perform the EALLOW before calling this function or else the ADC registers
// will not be configured.
//
void AdcSetMode(Uint16 adc, Uint16 resolution, Uint16 signalmode)
{
    Uint16 adcOffsetTrimOTPIndex; //index into OTP table of ADC offset trims
    Uint16 adcOffsetTrim;         //temporary ADC offset trim

    //
    //re-populate INL trim
    //
    CalAdcINL(adc);

    if(0xFFFF != *((Uint16*)GetAdcOffsetTrimOTP))
    {
        //
        //offset trim function is programmed into OTP, so call it
        //

        //
        //calculate the index into OTP table of offset trims and call
        //function to return the correct offset trim
        //
#ifndef _DUAL_HEADERS
        if(ADC_RESOLUTION_12BIT == resolution)
#else
        if(ADC_BITRESOLUTION_12BIT == resolution)
#endif
        {
            adcOffsetTrimOTPIndex = 4*adc + 1*signalmode;
        }
        else
        {
            adcOffsetTrimOTPIndex = 4*adc + 1*signalmode + 2;
        }

        adcOffsetTrim = (*GetAdcOffsetTrimOTP)(adcOffsetTrimOTPIndex);
    }
    else
    {
        //
        //offset trim function is not populated, so set offset trim to 0
        //
        adcOffsetTrim = 0;
    }

    //
    // Apply the resolution and signalmode to the specified ADC.
    // Also apply the offset trim and, if needed, linearity trim correction.
    //
    switch(adc)
    {
        case ADC_ADCA:
        {
            AdcaRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            AdcaRegs.ADCOFFTRIM.all = adcOffsetTrim;
#ifndef _DUAL_HEADERS
            if(ADC_RESOLUTION_12BIT == resolution)
#else
            if(ADC_BITRESOLUTION_12BIT == resolution)
#endif
            {
                AdcaRegs.ADCCTL2.bit.RESOLUTION = 0;

                //
                //12-bit linearity trim workaround
                //
                AdcaRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdcaRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdcaRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdcaRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
            else
            {
                AdcaRegs.ADCCTL2.bit.RESOLUTION = 1;
            }
            break;
        }
        case ADC_ADCB:
        {
            AdcbRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            AdcbRegs.ADCOFFTRIM.all = adcOffsetTrim;
#ifndef _DUAL_HEADERS
            if(ADC_RESOLUTION_12BIT == resolution)
#else
            if(ADC_BITRESOLUTION_12BIT == resolution)
#endif
            {
                AdcbRegs.ADCCTL2.bit.RESOLUTION = 0;

                //
                //12-bit linearity trim workaround
                //
                AdcbRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdcbRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdcbRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdcbRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
            else
            {
                AdcbRegs.ADCCTL2.bit.RESOLUTION = 1;
            }
            break;
        }
        case ADC_ADCC:
        {
            AdccRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            AdccRegs.ADCOFFTRIM.all = adcOffsetTrim;
#ifndef _DUAL_HEADERS
            if(ADC_RESOLUTION_12BIT == resolution)
#else
            if(ADC_BITRESOLUTION_12BIT == resolution)
#endif
            {
                AdccRegs.ADCCTL2.bit.RESOLUTION = 0;
                //
                //12-bit linearity trim workaround
                //
                AdccRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdccRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdccRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdccRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
            else
            {
                AdccRegs.ADCCTL2.bit.RESOLUTION = 1;
            }
            break;
        }
        case ADC_ADCD:
        {
            AdcdRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            AdcdRegs.ADCOFFTRIM.all = adcOffsetTrim;
#ifndef _DUAL_HEADERS
            if(ADC_RESOLUTION_12BIT == resolution)
#else
            if(ADC_BITRESOLUTION_12BIT == resolution)
#endif
            {
                AdcdRegs.ADCCTL2.bit.RESOLUTION = 0;

                //
                //12-bit linearity trim workaround
                //
                AdcdRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdcdRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdcdRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdcdRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
            else
            {
                AdcdRegs.ADCCTL2.bit.RESOLUTION = 1;
            }
            break;
        }
    }
}

//
// CalAdcINL - Loads INL trim values from OTP into the trim registers of the
//             specified ADC. Use only as part of AdcSetMode function, since
//             linearity trim correction is needed for some modes.
//
void CalAdcINL(Uint16 adc)
{
    switch(adc)
    {
        case ADC_ADCA:
            if(0xFFFF != *((Uint16*)CalAdcaINL))
            {
                //
                //trim function is programmed into OTP, so call it
                //
                (*CalAdcaINL)();
            }
            else
            {
                //
                //do nothing, no INL trim function populated
                //
            }
            break;
        case ADC_ADCB:
            if(0xFFFF != *((Uint16*)CalAdcbINL))
            {
                //
                //trim function is programmed into OTP, so call it
                //
                (*CalAdcbINL)();
            }
            else
            {
                //
                //do nothing, no INL trim function populated
                //
            }
            break;
        case ADC_ADCC:
            if(0xFFFF != *((Uint16*)CalAdccINL))
            {
                //
                //trim function is programmed into OTP, so call it
                //
                (*CalAdccINL)();
            }
            else
            {
                //
                //do nothing, no INL trim function populated
                //
            }
            break;
        case ADC_ADCD:
            if(0xFFFF != *((Uint16*)CalAdcdINL))
            {
                //
                //trim function is programmed into OTP, so call it
                //
                (*CalAdcdINL)();
            }
            else
            {
                //
                //do nothing, no INL trim function populated
                //
            }
            break;
    }
}

//
// End of file
//
