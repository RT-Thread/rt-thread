/** @file sys_startup.c
*   @brief Startup Source File
*   @date 29.May.2013
*   @version 03.05.02
*
*   This file contains:
*   - Include Files
*   - Type Definitions
*   - External Functions
*   - VIM RAM Setup
*   - Startup Routine
*   .
*   which are relevant for the Startup.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

/* Include Files */

#include "sys_common.h"
#include "system.h"
#include "sys_vim.h"
#include "sys_core.h"
#include "sys_selftest.h"
#include "esm.h"
#include "mibspi.h"

/* Type Definitions */

typedef void (*handler_fptr)(const uint8 * in, uint8 * out);

/* External Functions */

/*SAFETYMCUSW 94 S MR:11.1 <REVIEWED> "Startup code(handler pointers)" */
/*SAFETYMCUSW 296 S MR:8.6 <REVIEWED> "Startup code(library functions at block scope)" */
/*SAFETYMCUSW 298 S MR:  <REVIEWED> "Startup code(handler pointers)" */
/*SAFETYMCUSW 299 S MR:  <REVIEWED> "Startup code(typedef for handler pointers in library )" */
/*SAFETYMCUSW 326 S MR:8.2 <REVIEWED> "Startup code(Declaration for main in library)" */
/*SAFETYMCUSW 60 D MR:8.8 <REVIEWED> "Startup code(Declaration for main in library;Only doing an extern for the same)" */
/*SAFETYMCUSW 94 S MR:11.1 <REVIEWED> "Startup code(handler pointers)" */
/*SAFETYMCUSW 354 S MR:1.4 <REVIEWED> " Startup code(Extern declaration present in the library)" */

/*SAFETYMCUSW 218 S MR:20.2 <REVIEWED> "Functions from library" */

#ifdef __TI_COMPILER_VERSION__
#pragma WEAK(__TI_Handler_Table_Base)
#pragma WEAK(__TI_Handler_Table_Limit)
#pragma WEAK(__TI_CINIT_Base)
#pragma WEAK(__TI_CINIT_Limit)

extern uint32   __TI_Handler_Table_Base;
extern uint32   __TI_Handler_Table_Limit;
extern uint32   __TI_CINIT_Base;
extern uint32   __TI_CINIT_Limit;
extern uint32   __TI_PINIT_Base;
extern uint32   __TI_PINIT_Limit;
extern uint32 * __binit__;
#endif

extern void main(void);

/* USER CODE BEGIN (3) */
/* USER CODE END */

/* Startup Routine */

/** @fn void memoryInit(uint32 ram)
*   @brief Memory Initialization Driver
*
*   This function is called to perform Memory initialization of selected RAM's.
*/
void memoryInit(uint32 ram)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

	/* Enable Memory Hardware Initialization */
	systemREG1->MINITGCR = 0xAU;

    /* Enable Memory Hardware Initialization for selected RAM's */
	systemREG1->MSINENA  = ram;

	/* Wait until Memory Hardware Initialization complete */
	while((systemREG1->MSTCGSTAT & 0x00000100U) != 0x00000100U)
	{
	}/* Wait */

	/* Disable Memory Hardware Initialization */
	systemREG1->MINITGCR = 0x5U;

/* USER CODE BEGIN (12) */
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */

void _c_int00(void)
{
    /* Work Around for Errata DEVICE#140: ( Only on Rev A silicon)
     *
     * Errata Description:
     *            The Core Compare Module(CCM-R4) may cause nERROR to be asserted after a cold power-on
     * Workaround:
     *            Clear ESM Group2 Channel 2 error in ESMSR2 and Compare error in CCMSR register */
    if (DEVICE_ID_REV == 0x802AAD05U)
    {
        _esmCcmErrorsClear_();
    }

/* USER CODE BEGIN (8) */
/* USER CODE END */
/* USER CODE BEGIN (11) */
/* USER CODE END */

    /* Reset handler: the following instructions read from the system exception status register
     * to identify the cause of the CPU reset. */
    /* check for power-on reset condition */
    if ((SYS_EXCEPTION & POWERON_RESET) != 0U)
    {
/* USER CODE BEGIN (12) */
/* USER CODE END */

        /* clear all reset status flags */
        SYS_EXCEPTION = 0xFFFFU;

/* USER CODE BEGIN (13) */
/* USER CODE END */

    _errata_CORTEXR4_66_();

/* USER CODE BEGIN (14) */
/* USER CODE END */

    _errata_CORTEXR4_57_();

/* USER CODE BEGIN (15) */
/* USER CODE END */

        /* continue with normal start-up sequence */
    }
    else if ((SYS_EXCEPTION & OSC_FAILURE_RESET) != 0U)
    {
        /* Reset caused due to oscillator failure.
        Add user code here to handle oscillator failure */

/* USER CODE BEGIN (16) */
/* USER CODE END */
    }
    else if ((SYS_EXCEPTION & WATCHDOG_RESET) !=0U)
    {
        /* Reset caused due
         *  1) windowed watchdog violation - Add user code here to handle watchdog violation.
         *  2) ICEPICK Reset - After loading code via CCS / System Reset through CCS
         */
        /* Check the WatchDog Status register */
        if(WATCHDOG_STATUS != 0U)
        {
            /* Add user code here to handle watchdog violation. */
/* USER CODE BEGIN (17) */
/* USER CODE END */

            /* Clear the Watchdog reset flag in Exception Status register */
            SYS_EXCEPTION = WATCHDOG_RESET;

/* USER CODE BEGIN (18) */
/* USER CODE END */
        }
        else
        {
            /* Clear the ICEPICK reset flag in Exception Status register */
            SYS_EXCEPTION = ICEPICK_RESET;
/* USER CODE BEGIN (19) */
/* USER CODE END */
        }
    }
    else if ((SYS_EXCEPTION & CPU_RESET) !=0U)
    {
        /* Reset caused due to CPU reset.
        CPU reset can be caused by CPU self-test completion, or
        by toggling the "CPU RESET" bit of the CPU Reset Control Register. */

/* USER CODE BEGIN (20) */
/* USER CODE END */

        /* clear all reset status flags */
        SYS_EXCEPTION = CPU_RESET;

/* USER CODE BEGIN (21) */
/* USER CODE END */

    }
    else if ((SYS_EXCEPTION & SW_RESET) != 0U)
    {
        /* Reset caused due to software reset.
        Add user code to handle software reset. */

/* USER CODE BEGIN (22) */
/* USER CODE END */
    }
    else
    {
        /* Reset caused by nRST being driven low externally.
        Add user code to handle external reset. */

/* USER CODE BEGIN (23) */
/* USER CODE END */
    }

/* USER CODE BEGIN (26) */
/* USER CODE END */
    /* Initialize System - Clock, Flash settings with Efuse self check */
    systemInit();
/* USER CODE BEGIN (29) */
/* USER CODE END */
/* USER CODE BEGIN (31) */
/* USER CODE END */
/* USER CODE BEGIN (33) */
/* USER CODE END */

/* USER CODE BEGIN (36) */
/* USER CODE END */
/* USER CODE BEGIN (37) */
/* USER CODE END */
    /* Initialize CPU RAM.
     * This function uses the system module's hardware for auto-initialization of memories and their
     * associated protection schemes. The CPU RAM is initialized by setting bit 0 of the MSIENA register.
     * Hence the value 0x1 passed to the function.
     * This function will initialize the entire CPU RAM and the corresponding ECC locations.
     */
    memoryInit(0x1U);

/* USER CODE BEGIN (38) */
/* USER CODE END */
    _coreEnableRamEcc_();
/* USER CODE BEGIN (39) */
/* USER CODE END */
/* USER CODE BEGIN (40) */
/* USER CODE END */
    tcram1REG->RAMCTRL &= ~(0x00000100U);                /* disable writes to ECC RAM */
    tcram2REG->RAMCTRL &= ~(0x00000100U);
    tcram1REG->RAMCTRL &= ~(0x00000100U);                /* disable writes to ECC RAM */
    tcram2REG->RAMCTRL &= ~(0x00000100U);

/* USER CODE BEGIN (41) */
/* USER CODE END */


/* USER CODE BEGIN (43) */
/* USER CODE END */

/* USER CODE BEGIN (44) */
/* USER CODE END */

/* USER CODE BEGIN (48) */
/* USER CODE END */
/* USER CODE BEGIN (56) */
/* USER CODE END */
    /* Release the MibSPI1 modules from local reset.
     * This will cause the MibSPI1 RAMs to get initialized along with the parity memory.
     */
     mibspiREG1->GCR0 = 0x1U;

    /* Release the MibSPI3 modules from local reset.
     * This will cause the MibSPI3 RAMs to get initialized along with the parity memory.
     */
    mibspiREG3->GCR0 = 0x1U;

    /* Release the MibSPI5 modules from local reset.
     * This will cause the MibSPI5 RAMs to get initialized along with the parity memory.
     */
    mibspiREG5->GCR0 = 0x1U;

/* USER CODE BEGIN (57) */
/* USER CODE END */

    /* Initialize all on-chip SRAMs except for MibSPIx RAMs
     * The MibSPIx modules have their own auto-initialization mechanism which is triggered
     * as soon as the modules are brought out of local reset.
     */
    /* The system module auto-init will hang on the MibSPI RAM if the module is still in local reset.
     */
    /* NOTE : Please Refer DEVICE DATASHEET for the list of Supported Memories and their channel numbers.
              Memory Initialization is perfomed only on the user selected memories in HALCoGen's GUI SAFETY INIT tab.
     */
    memoryInit(  (1U << 1U)
                 | (1U << 2U)
                 | (1U << 5U)
                 | (1U << 6U)
                 | (1U << 10U)
                 | (1U << 8U)
                 | (1U << 14U)
                 | (1U << 3U)
                 | (1U << 4U)
                 | (1U << 15U)
                 | (1U << 16U)
                 | (0U << 13U) );
/* USER CODE BEGIN (58) */
/* USER CODE END */
/* USER CODE BEGIN (59) */
/* USER CODE END */
/* USER CODE BEGIN (60) */
/* USER CODE END */
/* USER CODE BEGIN (61) */
/* USER CODE END */
/* USER CODE BEGIN (62) */
/* USER CODE END */
/* USER CODE BEGIN (63) */
/* USER CODE END */
/* USER CODE BEGIN (64) */
/* USER CODE END */
/* USER CODE BEGIN (65) */
/* USER CODE END */
/* USER CODE BEGIN (66) */
/* USER CODE END */
/* USER CODE BEGIN (67) */
/* USER CODE END */
/* USER CODE BEGIN (68) */
/* USER CODE END */
/* USER CODE BEGIN (69) */
/* USER CODE END */

    while ((mibspiREG1->FLG & 0x01000000U) == 0x01000000U)
    {
    }/* Wait */
    /* wait for MibSPI1 RAM to complete initialization */
    while ((mibspiREG3->FLG & 0x01000000U) == 0x01000000U)
    {
    }/* Wait */
    /* wait for MibSPI3 RAM to complete initialization */
    while ((mibspiREG5->FLG & 0x01000000U) == 0x01000000U)
    {
    }/* Wait */
    /* wait for MibSPI5 RAM to complete initialization */

/* USER CODE BEGIN (70) */
/* USER CODE END */
/* USER CODE BEGIN (71) */
/* USER CODE END */
/* USER CODE BEGIN (72) */
/* USER CODE END */

/* USER CODE BEGIN (73) */
/* USER CODE END */
/* USER CODE BEGIN (74) */
/* USER CODE END */

    /* Initialize VIM table */
    vimInit();

/* USER CODE BEGIN (75) */
/* USER CODE END */

#ifdef __GNUC__
    data_init();
#elif defined(__TI_COMPILER_VERSION__)
    /* initialize copy table */
    if ((uint32 *)&__binit__ != (uint32 *)0xFFFFFFFFU)
    {
        extern void copy_in(void * binit);
        copy_in((void *)&__binit__);
    }

    /* initialize the C global variables */
    if (&__TI_Handler_Table_Base < &__TI_Handler_Table_Limit)
    {
        uint8 **tablePtr   = (uint8 **)&__TI_CINIT_Base;
        uint8 **tableLimit = (uint8 **)&__TI_CINIT_Limit;

        while (tablePtr < tableLimit)
        {
            uint8 * loadAdr = *tablePtr++;
            uint8 * runAdr  = *tablePtr++;
            uint8  idx     = *loadAdr++;
            handler_fptr   handler = (handler_fptr)(&__TI_Handler_Table_Base)[idx];

            (*handler)((const uint8 *)loadAdr, runAdr);
        }
    }

    /* initialize constructors */
    if (__TI_PINIT_Base < __TI_PINIT_Limit)
    {
        void (**p0)(void) = (void *)__TI_PINIT_Base;

        while ((uint32)p0 < __TI_PINIT_Limit)
        {
            void (*p)(void) = *p0++;
            p();
        }
    }
#endif
/* USER CODE BEGIN (76) */
/* USER CODE END */
    /* call the application */
    main();

/* USER CODE BEGIN (77) */
/* USER CODE END */

/* USER CODE BEGIN (78) */
/* USER CODE END */
}

/* USER CODE BEGIN (79) */
/* USER CODE END */
