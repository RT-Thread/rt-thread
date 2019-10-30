/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <rtthread.h>
#include <drivers/pm.h>
#include <drivers/pin.h>
#include <drv_wakeup.h>
#include "board.h"
#include "project.h"
#include "PowerConfiguration.h"

extern int wakeup_app(void);

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    wakeup_app();

    for(;;)
    {
        Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

/* [] END OF FILE */
