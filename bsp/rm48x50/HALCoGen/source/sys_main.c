/** @file sys_main.c 
*   @brief Application main file
*   @date 23.May.2013
*   @version 03.05.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* USER CODE BEGIN (0) */
/* we will use our own main and get rid off everything from HALCoGen here */
#if 0
#include <stdint.h>
/* USER CODE END */

/* Include Files */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */

/* Include HET header file - types, definitions and function declarations for system driver */
#include "het.h"
#include "esm.h"
#include "sci.h"
#include "rti.h"

/* Task1 */
void vTaskDelay(int t)
{
    for (; t; t--)
    {
        int i;
        for(i = 100000;i ; i--)
        {
        }
    }
}
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
uint8_t sci_buf;
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */

    /* Set high end timer GIO port hetPort pin direction to all output */
    gioSetDirection(hetPORT1, 0xFFFFFFFF);
    sciInit();
    rtiInit();
    rtiStartCounter(rtiCOUNTER_BLOCK1);
    rtiEnableNotification(rtiNOTIFICATION_COMPARE3);
    _enable_IRQ();
    sciReceive(scilinREG, 1, &sci_buf);

    for(;;)
    {
        gioSetBit(hetPORT1, 17, gioGetBit(hetPORT1, 17) ^ 1);
        /* Taggle HET[1] with timer tick */
        /*sciSendByte(scilinREG, 'b');*/
        vTaskDelay(100);
        /*sciSendByte(scilinREG, 'a');*/
    }
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
#endif
/* USER CODE END */
