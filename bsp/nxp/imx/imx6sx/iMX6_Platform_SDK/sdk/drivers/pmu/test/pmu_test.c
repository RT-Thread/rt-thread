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

#include <string.h>
#include <stdio.h>
#include "pmu/pmu_driver.h"
#include "sdk.h"
#include "system_util.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Macro to check and handle PMU errors.
#define CHECK_GET_(e) do { \
        int __status__ = (e); \
        if (__status__ != kPMUSuccess)  \
        {   \
            printf("Error getting property (err=%d)\n", __status__);    \
        }   \
    } while (false);

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

void print_rails(void);
void print_reg_info(pmu_regulators_t reg);
bool choose_regulator(pmu_regulators_t * reg);
void pmu_test(void);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Table of names for each of the regulators.
const char * kRegulatorNames[] = {
        "REG_1P1",
        "REG_2P5",
        "REG_3P0",
        "REG_ARM",
        "REG_PU",
        "REG_SOC"
    };

//! @brief Table of strings for boolean values.
const char * kYesNoNames[] = { "no", "yes" };

//! @brief Table of names for each of the ramp rate values.
const char * kRampRateNames[] = {
        "fast",         // kPMURate_Fast
        "medium",       // kPMURate_Medium
        "slow",         // kPMURate_Slow
        "very slow",    // kPMURate_VerySlow
    };

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Determines if the regulator is an analog regulator.
static inline bool is_ana_reg(pmu_regulators_t reg)
{
    return (reg == kPMURegulator_1p1 || reg == kPMURegulator_2p5 || reg == kPMURegulator_3p0);
}

//! @brief Determines if the regulator is an digital (core) regulator.
static inline bool is_dig_reg(pmu_regulators_t reg)
{
    return (reg == kPMURegulator_ArmCore || reg == kPMURegulator_Graphics || reg == kPMURegulator_SoC);
}

//! @brief Print out all of the rail voltages.
void print_rails(void)
{
    pmu_regulators_t reg;
    
    for (reg = kPMURegulator_1p1; reg <= kPMURegulator_SoC; ++reg)
    {
        uint32_t mV;
        CHECK_GET_( pmu_get_property(reg, kPMUProperty_OutputMillivolts, &mV) );
        
        printf("%s = %lu mV\n", kRegulatorNames[reg], mV);
    }
}

void print_reg_info(pmu_regulators_t reg)
{
    uint32_t mV;
    uint32_t flag;
    
    printf("%s state:\n", kRegulatorNames[reg]);
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_OutputMillivolts, &mV) );
    printf("  output = %lu mV\n", mV);
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_MinOutputMillivolts, &mV) );
    printf("  min output = %lu mV\n", mV);
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_MaxOutputMillivolts, &mV) );
    printf("  max output = %lu mV\n", mV);
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_BrownoutMillivolts, &mV) );
    printf("  brownout level = %lu mV\n", mV);
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_MinBrownoutMillivolts, &mV) );
    printf("  min brownout level = %lu mV\n", mV);
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_MaxBrownoutMillivolts, &mV) );
    printf("  max brownout level = %lu mV\n", mV);
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_IsEnabled, &flag) );
    printf("  enabled = %s\n", kYesNoNames[flag]);
    
    if (is_dig_reg(reg))
    {
        CHECK_GET_( pmu_get_property(reg, kPMUProperty_IsBypassed, &flag) );
        printf("  bypassed = %s\n", kYesNoNames[flag]);
    
        uint32_t i;
        CHECK_GET_( pmu_get_property(reg, kPMUProperty_RampRate, &i) );
        printf("  ramp rate = %s\n", kRampRateNames[i]);
    }
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_BrownoutDetectIsEnabled, &flag) );
    printf("  brownout enabled = %s\n", kYesNoNames[flag]);
    
    if (is_ana_reg(reg))
    {
        CHECK_GET_( pmu_get_property(reg, kPMUProperty_CurrentLimitIsEnabled, &flag) );
        printf("  ilimit bypassed = %s\n", kYesNoNames[flag]);

        if (reg != kPMURegulator_3p0)
        {
            CHECK_GET_( pmu_get_property(reg, kPMUProperty_PulldownIsEnabled, &flag) );
            printf("  pulldown enabled = %s\n", kYesNoNames[flag]);
        }
    }
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_IsOK, &flag) );
    printf("  regulator ok = %s\n", kYesNoNames[flag]);
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_IsInBrownout, &flag) );
    printf("  in brownout = %s\n", kYesNoNames[flag]);
    
    pmu_bo_handler_t handler;
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_BrownoutHandler, &handler) );
    printf("  brownout handler = 0x%08x\n", handler);
    
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_SafetyOverrideIsEnabled, &flag) );
    printf("  safety override enable = %s\n", kYesNoNames[flag]);
}

bool choose_regulator(pmu_regulators_t * reg)
{
    printf("\n\
Choose a regulator:\n\
    1 - REG_1P1\n\
    2 - REG_2P5\n\
    3 - REG_3P0\n\
    4 - REG_ARM\n\
    5 - REG_PU\n\
    6 - REG_SOC\n\
    x - Return to main menu\n\
\n\
> ");
    
    // Wait for the user to type a valid character.
    char c;
    while (true)
    {
        c = getchar();
        if (c == 'x' || (c >= '1' && c <= '6'))
        {
            break;
        }
    }
    
    // Echo the typed char.
    printf("%c\n\n", c);
    
    if (c == 'x')
    {
        return false;
    }
    
    *reg = (pmu_regulators_t)(c - '1');
    return true;
}

void set_regulator_voltage(void)
{
    pmu_regulators_t reg;
    if (!choose_regulator(&reg))
    {
        return;
    }
    
    uint32_t mV;
    CHECK_GET_( pmu_get_property(reg, kPMUProperty_OutputMillivolts, &mV) );
    
    printf("Current output: %ld mV\n\n", mV);
    printf("Enter new voltage in millivolts (0 to abort):\n");
    mV = read_int();
    
    if (mV == 0)
    {
        return;
    }
    
    int err = pmu_set_property(reg, kPMUProperty_OutputMillivolts, &mV);
    if (err != kPMUSuccess)
    {
        printf("Error %d setting voltage for %s!\n", err, kRegulatorNames[reg]);
    }
}

void pmu_test(void)
{
    printf("\n--- PMU test ---\n\n");
    
    // Init the PMU driver.
    pmu_init();
    
    do {
        // Print the prompt.
        printf("\n\
Choose an option:\n\
    p - Print regulator voltages\n\
    i - Print detailed info for one regulator\n\
    v - Set voltage for a regulator\n\
    x - Exit test\n\
\n\
> ");
    
        // Wait for the user to type a valid character.
        char c;
        while (true)
        {
            c = getchar();
            if (c == 'x' || c == 'p' || c == 'i' || c == 'v')
            {
                break;
            }
        }
        
        // Echo the typed char.
        printf("%c\n\n", c);
        
        pmu_regulators_t reg;
        switch (c)
        {
            case 'x':
                printf("Test exited.\n");
                return;
            
            case 'i':
                if (choose_regulator(&reg))
                {
                    printf("\n");
                    print_reg_info(reg);
                    printf("\n");
                }
                break;
            
            case 'v':
                set_regulator_voltage();
                break;

            case 'p':
                // Read the current voltages.
                printf("\n");
                print_rails();
                printf("\n");
                break;
        }
    } while (true);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
