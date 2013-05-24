/** @file notification.c 
*   @brief User Notification Definition File
*   @date 23.May.2013
*   @version 03.05.01
*
*   This file  defines  empty  notification  routines to avoid
*   linker errors, Driver expects user to define the notification. 
*   The user needs to either remove this file and use their custom 
*   notification function or place their code sequence in this file 
*   between the provided USER CODE BEGIN and USER CODE END.
*
*/

/* Include Files */

#include "esm.h"
#include "sys_selftest.h"
#include "gio.h"
#include "sci.h"
#include "rti.h"
#include "sys_dma.h"
/* USER CODE BEGIN (0) */
#include <stdint.h>
/* USER CODE END */

void esmGroup1Notification(uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (1) */
/* USER CODE END */
}

/* USER CODE BEGIN (2) */
/* USER CODE END */

void esmGroup2Notification(uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (3) */
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */

void memoryPort0TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (5) */
/* USER CODE END */
}

/* USER CODE BEGIN (6) */
/* USER CODE END */

void memoryPort1TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (7) */
/* USER CODE END */
}

/* USER CODE BEGIN (8) */
/* USER CODE END */
void rtiNotification(uint32 notification)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (9) */
sciSendByte(scilinREG, 'I');
/* USER CODE END */
}

/* USER CODE BEGIN (10) */
/* USER CODE END */
void gioNotification(gioPORT_t *port, sint32 bit)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (19) */
/* USER CODE END */
}

/* USER CODE BEGIN (20) */
/* USER CODE END */

void sciNotification(sciBASE_t *sci, uint32 flags)     
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (29) */
	if (sci == scilinREG && flags == SCI_RX_INT)
	{
	}
/* USER CODE END */
}

/* USER CODE BEGIN (30) */
/* USER CODE END */



/* USER CODE BEGIN (43) */
/* USER CODE END */


/* USER CODE BEGIN (47) */
/* USER CODE END */


/* USER CODE BEGIN (50) */
/* USER CODE END */


/* USER CODE BEGIN (53) */
/* USER CODE END */

void dmaGroupANotification(dmaInterrupt_t inttype, sint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (54) */
/* USER CODE END */
}
/* USER CODE BEGIN (55) */
/* USER CODE END */

/* USER CODE BEGIN (56) */
/* USER CODE END */
