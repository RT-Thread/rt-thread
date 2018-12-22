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

#include "tempmon/tempmon.h"
#include "system_util.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////////////
// Code
//////////////////////////////////////////////////////////////////////////////////////////

void over_temp_callback(float theTemp)
{
    printf("\n* Temp alarm triggered! Temperature = %4.1f *\n", theTemp);
}

void print_current_temp(void)
{
    float temp = tempmon_get_temp();
    printf("Current temperature = %d degrees C\n\n", (int)temp);
}

//! @brief Test the tempmon driver.
//!
void tempmon_test(void)
{
    int status;
    
    printf("\n--- tempmon test ---\n\n");
    
    // Init the driver.
    status = tempmon_init();
    if (status)
    {
        printf("tempmon init failed: err=%d\n", status);
        return;
    }
    
    // Read the current temperature
    print_current_temp();
    
    do {
        // Print the prompt.
        printf("\n\
Choose an option:\n\
    p - Print current temperature\n\
    a - Set temperature alarm\n\
    d - Disable the alarm\n\
    x - Exit test\n\
\n\
> ");
    
        // Wait for the user to type a valid character.
        char c;
        while (true)
        {
            c = getchar();
            if (c == 'x' || c == 'p' || c == 'a' || c == 'd')
            {
                break;
            }
        }
        
        // Echo the typed char.
        printf("%c\n\n", c);
        
        switch (c)
        {
            case 'x':
                printf("Test exited.\n");
                return;

            case 'p':
                // Read the current temperature
                print_current_temp();
                break;
            
            case 'a':
            {
                printf("Enter the measurement period in milliseconds:\n");
                int period = read_int();
                
                printf("Enter alarm temperature in integer degrees C:\n");
                int alarmTemp = read_int();
                
                // Set the alarm.
                tempmon_set_alarm(period, alarmTemp, over_temp_callback);
                break;
            }
            
            case 'd':
                tempmon_disable_alarm();
                
                printf("Alarm disabled!\n");
                break;
        }
    } while (true);
}

//////////////////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////////////////
