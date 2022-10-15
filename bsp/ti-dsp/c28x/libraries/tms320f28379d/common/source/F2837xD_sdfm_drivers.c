//###########################################################################
//
// FILE:   F2837xD_sdfm_drivers.c
//
// TITLE:  SDFM Driver functions
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
#include "F28x_Project.h"
#include "F2837xD_struct.h"
#include "F2837xD_sdfm_drivers.h"

//
// Sdfm_configureInputCtrl - This function configures SDFM Input control unit.
//                           sdfmNumber   - This parameter should be used to
//                                          select SDFM1 (or) SDFM2
//                           filterNumber - This parameter is used to select
//                                          which filter (FILTER1,FILTER2,
//                                          FILTER3,FILTER4) needs to be
//                                          configured.
//                           mode         - This parameter is used to select
//                                          one of the modes mentioned above
//
//  Input control unit can be configured in four different modes:
//      MODE_0 : Modulator clock rate = Modulator data rate
//      MODE_1 : Modulator clock rate = (Modulator data rate / 2)
//      MODE_2 : Manchester encoded data (Modulator clock is encoded into data)
//      MODE_3 : Modulator clock rate = (2 x Modulator data rate)
//
void Sdfm_configureInputCtrl(Uint16 sdfmNumber, Uint16 filterNumber,
                             Uint16 mode)
{
    EALLOW;

    switch (filterNumber)
    {
        case FILTER1:
            (*SDFM[sdfmNumber]).SDCTLPARM1.bit.MOD = mode;
            break;

        case FILTER2:
            (*SDFM[sdfmNumber]).SDCTLPARM2.bit.MOD = mode;
            break;

        case FILTER3:
            (*SDFM[sdfmNumber]).SDCTLPARM3.bit.MOD = mode;
            break;

        case FILTER4:
            (*SDFM[sdfmNumber]).SDCTLPARM4.bit.MOD = mode;
            break;
    }

    EDIS;
}

//
// Sdfm_configureComparator - This function configures SDFM Comparator unit.
//                            Comparator unit can be configured to monitor
//                            input conditions with a fast settling time.
//                            This module can be programmed to detect over and
//                            under value conditions.
//
//                            sdfmNumber   - This parameter should be used to
//                                           select SDFM1 (or) SDFM2
//                            filterNumber - This parameter is used to select
//                                           which filter (FILTER1,FILTER2,
//                                           FILTER3,FILTER3)
//                            filterType   - This parameter is used to select
//                                           one of the filter type mentioned
//                                           above (SINC1,SINC2,SINC3,SINCFAST)
//                            OSR          - This parameter is used to
//                                           configure oversampling ratio for
//                                           comparator
//                            HLT          - This parameter is used to
//                                           configure to detect over value
//                                           condition
//                            LLT          - This parameter is used to
//                                           configure to detect under value
//                                           condition
//
void Sdfm_configureComparator(Uint16 sdfmNumber, Uint16 filterNumber,
                              Uint16 filterType, Uint16 OSR, Uint16 HLT,
                              Uint16 LLT)
{
    EALLOW;

    switch (filterNumber)
    {
        case FILTER1:        //Filter 1

            //
            //Configure filter type : Sincfast / Sinc1 / Sinc2 / Sinc3
            //
            (*SDFM[sdfmNumber]).SDCPARM1.bit.CS1_CS0  = filterType;

            //
            //Configure OSR value
            //
            if(OSR<=COMPARATOR_MAX_OSR)
            {
                (*SDFM[sdfmNumber]).SDCPARM1.bit.COSR = OSR;
            }
            else
            {
                (*SDFM[sdfmNumber]).SDCPARM1.bit.COSR = COMPARATOR_MAX_OSR;
            }

            (*SDFM[sdfmNumber]).SDCMPH1.bit.HLT = HLT;
            (*SDFM[sdfmNumber]).SDCMPL1.bit.LLT = LLT;
            break;

        case FILTER2:        //Filter 2
            //
            //Configure filter type : Sincfast / Sinc1 / Sinc2 / Sinc3
            //
            (*SDFM[sdfmNumber]).SDCPARM2.bit.CS1_CS0  = filterType;

            //
            //Configure OSR value
            //
            if(OSR<=COMPARATOR_MAX_OSR)
            {
                (*SDFM[sdfmNumber]).SDCPARM2.bit.COSR = OSR;
            }
            else
            {
                (*SDFM[sdfmNumber]).SDCPARM2.bit.COSR = COMPARATOR_MAX_OSR;
            }

            (*SDFM[sdfmNumber]).SDCMPH2.bit.HLT = HLT;
            (*SDFM[sdfmNumber]).SDCMPL2.bit.LLT = LLT;
            break;

        case FILTER3:        //Filter 3
            //
            //Configure filter type : Sincfast / Sinc1 / Sinc2 / Sinc3
            //
            (*SDFM[sdfmNumber]).SDCPARM3.bit.CS1_CS0  = filterType;

            //
            //Configure OSR value
            //
            if(OSR<=COMPARATOR_MAX_OSR)
            {
                (*SDFM[sdfmNumber]).SDCPARM3.bit.COSR = OSR;
            }
            else
            {
                (*SDFM[sdfmNumber]).SDCPARM3.bit.COSR = COMPARATOR_MAX_OSR;
            }

            (*SDFM[sdfmNumber]).SDCMPH3.bit.HLT = HLT;
            (*SDFM[sdfmNumber]).SDCMPL3.bit.LLT = LLT;
            break;

        case FILTER4:        //Filter 4
            //
            //Configure filter type : Sincfast / Sinc1 / Sinc2 / Sinc3
            //
            (*SDFM[sdfmNumber]).SDCPARM4.bit.CS1_CS0  = filterType;

            //
            //Configure Comparator OSR value
            //
            if(OSR<=COMPARATOR_MAX_OSR)
            {
                (*SDFM[sdfmNumber]).SDCPARM4.bit.COSR = OSR;
            }
            else
            {
                (*SDFM[sdfmNumber]).SDCPARM4.bit.COSR = COMPARATOR_MAX_OSR;
            }

            (*SDFM[sdfmNumber]).SDCMPH4.bit.HLT = HLT;
            (*SDFM[sdfmNumber]).SDCMPL4.bit.LLT = LLT;
            break;
    }

    EDIS;
}


//
// SDFM_configureData_filter - This function configures SDFM Data filter unit
//
//                             SDFM Data filter unit can be configured in any
//                             of four different Sinc filter types:
//                             sdfmNumber    - This parameter should be used to
//                                             select SDFM1 (or) SDFM2
//                             filterNumber  - This parameter is used to select
//                                             which filter(FILTER1,FILTER2,
//                                             FILTER3,FILTER3) needs to be
//                                             configured
//                             Filter_switch - This parameter is used to
//                                             enable/disable a filter
//                             filterType    - This parameter is used to select
//                                             one of the filter type mentioned
//                                             above (SINC1 / SINC2 / SINC3 /
//                                             SINCFAST)
//                             OSR           - This parameter is used to
//                                             configure oversampling ratio
//                                             for Data filter (Upto OSR_256)
//                             DR_switch     - This parameter selects whether
//                                             data is represented in 16 (or)
//                                             32 bits
//                             shift_bits    - When user chooses 16 bit
//                                             representation, this variable
//                                             allows to right shift by
//                                             specific number of bits
//
void Sdfm_configureData_filter(Uint16 sdfmNumber, Uint16 filterNumber,
                               Uint16 Filter_switch, Uint16 filterType,
                               Uint16 OSR, Uint16 DR_switch, Uint16 shift_bits)
{
    EALLOW;

    switch(filterNumber)
    {

        case FILTER1:        //Filter 1
            (*SDFM[sdfmNumber]).SDDFPARM1.bit.FEN  = Filter_switch;
            (*SDFM[sdfmNumber]).SDDFPARM1.bit.SST  = filterType;

            //
            //Configure Sinc filter OSR value
            //
            if(OSR<=DATA_FILTER_MAX_OSR)
            {
                (*SDFM[sdfmNumber]).SDDFPARM1.bit.DOSR  = OSR;
            }
            else
            {
                (*SDFM[sdfmNumber]).SDDFPARM1.bit.DOSR  = DATA_FILTER_MAX_OSR;
            }

            //
            //Configure Data filter data representation
            //DR_switch - Data Representation (0/1 = 16/32b 2's complement)
            //
            (*SDFM[sdfmNumber]).SDDPARM1.bit.DR = DR_switch;
            if(DR_switch == 0)
            {
                (*SDFM[sdfmNumber]).SDDPARM1.bit.SH = shift_bits;
            }

            break;

        case FILTER2:        //Filter 2
            (*SDFM[sdfmNumber]).SDDFPARM2.bit.FEN  = Filter_switch;
            (*SDFM[sdfmNumber]).SDDFPARM2.bit.SST  = filterType;

            //
            //Configure Sinc filter OSR value
            //
            if(OSR<=DATA_FILTER_MAX_OSR)
            {
                (*SDFM[sdfmNumber]).SDDFPARM2.bit.DOSR  = OSR;
            }
            else
            {
                (*SDFM[sdfmNumber]).SDDFPARM2.bit.DOSR  = DATA_FILTER_MAX_OSR;
            }

            //
            //Configure Data filter data representation
            // DR_switch - Data Representation (0/1 = 16/32b 2's complement)
            //
            (*SDFM[sdfmNumber]).SDDPARM2.bit.DR    = DR_switch;
            if(DR_switch == 0)
            {
                (*SDFM[sdfmNumber]).SDDPARM2.bit.SH    = shift_bits;
            }

            break;

        case FILTER3:        //Filter 3
            (*SDFM[sdfmNumber]).SDDFPARM3.bit.FEN  = Filter_switch;
            (*SDFM[sdfmNumber]).SDDFPARM3.bit.SST  = filterType;

            //
            //Configure Sinc filter OSR value
            //
            if(OSR<=DATA_FILTER_MAX_OSR)
            {
                (*SDFM[sdfmNumber]).SDDFPARM3.bit.DOSR  = OSR;
            }
            else
            {
                (*SDFM[sdfmNumber]).SDDFPARM3.bit.DOSR  = DATA_FILTER_MAX_OSR;
            }

            //
            //Configure Data filter data representation
            // DR_switch - Data Representation (0/1 = 16/32b 2's complement)
            //
            (*SDFM[sdfmNumber]).SDDPARM3.bit.DR    = DR_switch;
            if(DR_switch == 0)
            {
                (*SDFM[sdfmNumber]).SDDPARM3.bit.SH    = shift_bits;
            }

            break;

        case FILTER4:        //Filter 4
            (*SDFM[sdfmNumber]).SDDFPARM4.bit.FEN = Filter_switch;
            (*SDFM[sdfmNumber]).SDDFPARM4.bit.SST  = filterType;

            //
            //Configure Sinc filter OSR value
            //
            if(OSR<=DATA_FILTER_MAX_OSR)
            {
                (*SDFM[sdfmNumber]).SDDFPARM4.bit.DOSR  = OSR;
            }
            else
            {
                (*SDFM[sdfmNumber]).SDDFPARM4.bit.DOSR  = DATA_FILTER_MAX_OSR;
            }

            //
            //Configure Data filter data representation
            // DR_switch - Data Representation (0/1 = 16/32b 2's complement)
            //
            (*SDFM[sdfmNumber]).SDDPARM4.bit.DR    = DR_switch;
            if(DR_switch == 0)
            {
                (*SDFM[sdfmNumber]).SDDPARM4.bit.SH    = shift_bits;
            }

            break;
    }

    EDIS;
}

//
// Sdfm_configureInterrupt - This function configures SDFM Interrupt unit.
//                           SDFM Interrupt unit can be configured to
//                           enable/disable different sources of SDFM
//                           interrupts which should trigger CPU interrupt.
//
//                           sdfmNumber   - This parameter should be used to
//                                          select SDFM1 (or) SDFM2
//                           filterNumber - This parameter is used to select
//                                          which filter(FILTER1,FILTER2,
//                                          FILTER3,FILTER3) needs to be
//                                          configured
//                           IEH_Switch   - This parameter allows over value
//                                          condition to trigger CPU interrupt
//                           IEL_Switch   - This parameter allows under value
//                                          condition to trigger CPU interrupt
//                           MFIE_Switch  - This parameter allows modulator
//                                          failure to trigger CPU interrupt
//                           AE_Switch    - This parameter allows new filter
//                                          data acknowledge interrupt signal
//                                          to trigger CPU interrupt
//
void Sdfm_configureInterrupt(Uint16 sdfmNumber, Uint16 filterNumber,
                             Uint16 IEH_Switch, Uint16 IEL_Switch,
                             Uint16 MFIE_Switch, Uint16 AE_Switch)
{
    EALLOW;

    switch(filterNumber)
    {
        case FILTER1:        //Filter 1
            (*SDFM[sdfmNumber]).SDCPARM1.bit.IEH  =  IEH_Switch;
            (*SDFM[sdfmNumber]).SDCPARM1.bit.IEL  =  IEL_Switch;
            (*SDFM[sdfmNumber]).SDCPARM1.bit.MFIE =  MFIE_Switch;
            (*SDFM[sdfmNumber]).SDDFPARM1.bit.AE  =  AE_Switch;
            break;

        case FILTER2:        //Filter 2
            (*SDFM[sdfmNumber]).SDCPARM2.bit.IEH  =  IEH_Switch;
            (*SDFM[sdfmNumber]).SDCPARM2.bit.IEL  =  IEL_Switch;
            (*SDFM[sdfmNumber]).SDCPARM2.bit.MFIE =  MFIE_Switch;
            (*SDFM[sdfmNumber]).SDDFPARM2.bit.AE  =  AE_Switch;
            break;

        case FILTER3:        //Filter 3
            (*SDFM[sdfmNumber]).SDCPARM3.bit.IEH  =  IEH_Switch;
            (*SDFM[sdfmNumber]).SDCPARM3.bit.IEL  =  IEL_Switch;
            (*SDFM[sdfmNumber]).SDCPARM3.bit.MFIE =  MFIE_Switch;
            (*SDFM[sdfmNumber]).SDDFPARM3.bit.AE  =  AE_Switch;
            break;

        case FILTER4:        //Filter 4
            (*SDFM[sdfmNumber]).SDCPARM4.bit.IEH  =  IEH_Switch;
            (*SDFM[sdfmNumber]).SDCPARM4.bit.IEL  =  IEL_Switch;
            (*SDFM[sdfmNumber]).SDCPARM4.bit.MFIE =  MFIE_Switch;
            (*SDFM[sdfmNumber]).SDDFPARM4.bit.AE  =  AE_Switch;
            break;
    }

    EDIS;
}


//
// SDFM_configExternalreset - This function configures SDFM module to
//                            enable/disable external filter reset from PWM
//
//                            sdfmNumber               - This parameter should
//                                                       be used to select
//                                                       SDFM1 (or) SDFM2
//                            filter1_Config_ext_reset - This parameter is used
//                                                       to enable/disable
//                                                       external PWM reset for
//                                                       filter1
//                            filter2_Config_ext_reset - This parameter is used
//                                                       to enable/disable
//                                                       external PWM reset for
//                                                       filter2
//                            filter3_Config_ext_reset - This parameter is used
//                                                       to enable / disable
//                                                       external PWM reset for
//                                                       filter3
//                            filter4_Config_ext_reset - This parameter is used
//                                                       to enable / disable
//                                                       external PWM reset for
//                                                       filter4
//
void Sdfm_configureExternalreset(Uint16 sdfmNumber,
                                 Uint16 filter1_Config_ext_reset,
                                 Uint16 filter2_Config_ext_reset,
                                 Uint16 filter3_Config_ext_reset,
                                 Uint16 filter4_Config_ext_reset)
{
    EALLOW;
    (*SDFM[sdfmNumber]).SDDFPARM1.bit.SDSYNCEN = filter1_Config_ext_reset;
    (*SDFM[sdfmNumber]).SDDFPARM2.bit.SDSYNCEN = filter2_Config_ext_reset;
    (*SDFM[sdfmNumber]).SDDFPARM3.bit.SDSYNCEN = filter3_Config_ext_reset;
    (*SDFM[sdfmNumber]).SDDFPARM4.bit.SDSYNCEN = filter4_Config_ext_reset;
    EDIS;
}

//
// SDFM_enableMFE - This function enables Master filter bit of SDFM module
//
//                  sdfmNumber - This parameter should be used to select
//                               SDFM1 (or) SDFM2
//
void Sdfm_enableMFE(Uint16 sdfmNumber)
{
    EALLOW;
    (*SDFM[sdfmNumber]).SDMFILEN.bit.MFE = 1;  //Master Filter bit is enabled
    EDIS;
}

//
// SDFM_disableMFE - This function disable Master filter bit of SDFM module
//
//                   sdfmNumber - This parameter should be used to select
//                                SDFM1 (or) SDFM2
//
void SDFM_disableMFE(Uint16 sdfmNumber)
{
    EALLOW;
    (*SDFM[sdfmNumber]).SDMFILEN.bit.MFE = 0;  //Master Filter bit is disabled
    EDIS;
}

//
// SDFM_enableMIE - This function enable Master Interrupt bit of SDFM module
//
//                  sdfmNumber - This parameter should be used to select
//                               SDFM1 (or) SDFM2
//
void Sdfm_enableMIE(Uint16 sdfmNumber)
{
    EALLOW;
    //
    //Enable MIE (Master Interrupt Enable) bit
    //
    (*SDFM[sdfmNumber]).SDCTL.bit.MIE = 1;
    EDIS;
}

//
// Sdfm_disableMIE - This function disable Master Interrupt bit of SDFM module
//
//                   sdfmNumber - This parameter should be used to select
//                                SDFM1 (or) SDFM2
//
void Sdfm_disableMIE(Uint16 sdfmNumber)
{

    EALLOW;
    //
    //Disable MIE (Master Interrupt Enable) bit
    //
    (*SDFM[sdfmNumber]).SDCTL.bit.MIE = 0;
    EDIS;
}

//
// Sdfm_readFlagRegister - This function helps user read SDFM flag
//                         register (SDIFLG)
//
Uint32 Sdfm_readFlagRegister(Uint16 sdfmNumber)
{
    return ((*SDFM[sdfmNumber]).SDIFLG.all);
}

//
// Sdfm_clearFlagRegister - This function helps is used to clear
//                          SDIFLG register
//
void Sdfm_clearFlagRegister(Uint16 sdfmNumber,Uint32 sdfmReadFlagRegister)
{
    (*SDFM[sdfmNumber]).SDIFLGCLR.all = sdfmReadFlagRegister;
}

//
// End of file
//
