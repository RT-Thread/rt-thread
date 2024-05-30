/***************************************************************************//**
* \file system_cm0plus.c
* \version 1.0
*
* The device system-source file.
*
********************************************************************************
* \copyright
* Copyright 2021 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*******************************************************************************
* Function Name: SystemInit
****************************************************************************//**
*
* Initializes the system:
* - Unlocks and disables WDT.
* - Calls the Cy_SystemInit() function, if compiled from PSoC Creator.
* - Calls \ref SystemCoreClockUpdate().
*
*******************************************************************************/


#include <stdbool.h>
#include "cy_device.h"
#include "cy_device_headers.h"
#include "cy_syslib.h"
#include "cy_sysclk.h"
#include "cy_wdt.h"
#include "cmsis_compiler.h"

#define CY_SYS_CM7_PWR_CTL_KEY_OPEN  (0x05FAUL)
#define CY_SYS_CM7_PWR_CTL_KEY_CLOSE (0xFA05UL)

void Cy_DefaultUserHandler(void);
static void CopyVectorTable(void);
static void InitMemoryEccClearArea(uint32_t u32StartAddr, uint32_t u32EndAddr);
static void InitMemoryEcc(void);
static void EnableEcc(void);
static void PrepareSystemCallInfrastructure(void);

#define DEFAULT_HANDLER_NAME                            Cy_DefaultUserHandler

CY_NOINIT cy_israddress Cy_SystemIrqUserTable[CPUSS_SYSTEM_INT_NR] ;

CY_NOINIT cy_israddress * Cy_SysInt_SystemIrqUserTableRamPointer ;

extern uint32_t Cy_u32StartupStackStartAddress;
extern uint32_t Cy_u32StartupStackEndAddress;
extern void * __Vectors;
extern void * __Vectors_Size;
extern cy_israddress __ramVectors[];

/*******************************************************************************
* SystemCoreClockUpdate()
*******************************************************************************/

/** Default HFClk frequency in Hz */
#define CY_CLK_HFCLK0_FREQ_HZ_DEFAULT       (8000000UL)

/** Default PeriClk frequency in Hz */
#define CY_CLK_PERICLK_FREQ_HZ_DEFAULT      (8000000UL)

/** Default system core frequency in Hz */
#define CY_CLK_SYSTEM_FREQ_HZ_DEFAULT       (100000000UL)

/** Holds the CLK_SLOW(Cortex-M0+) or CLK_FAST0(Cortex-M7_0) or CLK_FAST(Cortex-M7_1) system core clock */
CY_NOINIT uint32_t SystemCoreClock ;

/** Holds the HFClk0 clock frequency. Updated by \ref SystemCoreClockUpdate(). */
CY_NOINIT uint32_t cy_Hfclk0FreqHz ;

/** Holds the PeriClk clock frequency. Updated by \ref SystemCoreClockUpdate(). */
CY_NOINIT uint32_t cy_PeriClkFreqHz ;

/** Holds the AHB frequency. Updated by \ref SystemCoreClockUpdate(). */
CY_NOINIT uint32_t cy_AhbFreqHz ;

/*******************************************************************************
* SystemCoreClockUpdate (void)
*******************************************************************************/

/* Do not use these definitions directly in your application */
#define CY_DELAY_MS_OVERFLOW_THRESHOLD  (0x8000u)
#define CY_DELAY_1K_THRESHOLD           (1000u)
#define CY_DELAY_1K_MINUS_1_THRESHOLD   (CY_DELAY_1K_THRESHOLD - 1u)
#define CY_DELAY_1M_THRESHOLD           (1000000u)
#define CY_DELAY_1M_MINUS_1_THRESHOLD   (CY_DELAY_1M_THRESHOLD - 1u)

CY_NOINIT uint32_t cy_delayFreqHz ;

CY_NOINIT uint32_t cy_delayFreqKhz ;

CY_NOINIT uint32_t cy_delayFreqMhz ;


/*****************************************************************************
* Global variable definitions (declared in header file with 'extern')
*****************************************************************************/
// CAUTION: Static or global initialized and non-const variables will not have their init value yet!


#define SRAM_BEGIN_ADDR                     (BASE_SRAM_CM0P)
#define SRAM_END_ADDR                       (CY_SRAM_BASE + CY_SRAM_SIZE)
#define STARTUP_STACK_OFFSEST               (0x100) /* 32 2-words are cleaned by startup */

#define ECC_INIT_WIDTH_BYTES                8
#define SROM_VECTOR_TABLE_BASE_ADDRESS      0x00000000
#define VECTOR_TABLE_OFFSET_IRQ0            0x40
#define VECTOR_TABLE_OFFSET_IRQ1            0x44

#if defined(__ARMCC_VERSION)
extern unsigned int Image$$ARM_LIB_STACK$$ZI$$Limit;            /* for (default) One Region model */
extern void __main(void);
#elif defined (__GNUC__)
extern unsigned int __StackTop;
#elif defined (__ICCARM__)
extern unsigned int CSTACK$$Limit;                      /* for (default) One Region model */
#endif

/******************************************************************************/

/** Define an abstract type for the chosen ECC initialization granularity */
typedef uint64_t  ecc_init_width_t;

/* Provide empty __WEAK implementation for the low-level initialization
   routine required by the RTOS-enabled applications.
   clib-support library provides FreeRTOS-specific implementation:
   https://github.com/Infineon/clib-support */
void cy_toolchain_init(void);
__WEAK void cy_toolchain_init(void)
{
}

#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
/* GCC: newlib crt0 _start executes software_init_hook.
   The cy_toolchain_init hook provided by clib-support library must execute
   after static data initialization and before static constructors. */
void software_init_hook();
void software_init_hook()
{
    cy_toolchain_init();
}
#elif defined(__ICCARM__)
/* Initialize data section */
void __iar_data_init3(void);

/* Call the constructors of all global objects */
void __iar_dynamic_initialization(void);

/* Define strong version to return zero for __iar_program_start
   to skip data sections initialization (__iar_data_init3). */
int __low_level_init(void);
int __low_level_init(void)
{
    return 0;
}
#else
/**/
#endif /* defined(__GNUC__) && !defined(__ARMCC_VERSION) */


void CyMain(void)
{
#if defined(__ICCARM__)
    /* Initialize data section */
    __iar_data_init3();

    /* Initialization hook for RTOS environment  */
    cy_toolchain_init();

    /* Call the constructors of all global objects */
    __iar_dynamic_initialization();
#endif

    __PROGRAM_START();
}


void SystemInit(void)
{
    /* startup Init */
    InitMemoryEcc();
    EnableEcc();
    CopyVectorTable();
    PrepareSystemCallInfrastructure();
    /* startup Init done */

    SystemIrqInit();

    Cy_WDT_Unlock();
    Cy_WDT_Disable();

    Cy_SystemInit();
    SystemCoreClockUpdate();

}


/*******************************************************************************
* Function Name: EnableEcc
****************************************************************************//**
*
* The function is called during device startup.
*
*******************************************************************************/
static void EnableEcc(void)
{
    /* Enable ECC checking in SRAM controllers again (had been switched off by assembly startup code) */
    CPUSS->RAM0_CTL0 &= ~(0x80000); /* set bit 19 to 0 */
#if (CPUSS_RAMC1_PRESENT == 1u)
    CPUSS->RAM1_CTL0 &= ~(0x80000); /* set bit 19 to 0 */
#endif
#if (CPUSS_RAMC2_PRESENT == 1u)
    CPUSS->RAM2_CTL0 &= ~(0x80000); /* set bit 19 to 0 */
#endif
}


/*******************************************************************************
* Function Name: InitMemoryEcc
****************************************************************************//**
*
* The function is called during device startup.
*
*******************************************************************************/
static void InitMemoryEcc(void)
{
    uint32_t *sp = (uint32_t*)&__INITIAL_SP;
    uint32_t u32StckLow = (uint32_t)sp - STARTUP_STACK_OFFSEST;
    uint32_t u32StackHigh = (uint32_t)sp;

    InitMemoryEccClearArea(SRAM_BEGIN_ADDR, u32StckLow);
    InitMemoryEccClearArea(u32StackHigh, SRAM_END_ADDR);
}


/**
 *****************************************************************************
 ** Clears an area by writing '0' using a pointer of type #ecc_init_width_t
 **
 ** \param u32StartAddr    Start address of area to be cleared,
 **                        must be aligned to #ECC_INIT_WIDTH_BYTES
 ** \param u32EndAddr      Last address within area to be cleared, (u32EndAddr+1)
 **                        must be aligned to #ECC_INIT_WIDTH_BYTES
 **
 ** \return none
 *****************************************************************************/
static void InitMemoryEccClearArea(uint32_t u32StartAddr, uint32_t u32EndAddr)
{
    volatile ecc_init_width_t * pRam = (volatile ecc_init_width_t *) u32StartAddr;
    ecc_init_width_t Zero = 0;

    for(; (uint32_t)pRam < u32EndAddr; pRam++)
    {
        // Note: Even if ecc_init_width_t is uint64_t, this will be compiled as two 32-bit accesses
        //       in case of CM0+, because there is no STRD instruction specified in ARMv6-M Thumb
        *pRam = Zero;
    }
}


/**
 *****************************************************************************
 ** Copies the vector table from ROM to RAM and updates the VTOR (CMx vector
 ** table base register) accordingly
 **
 ** \return none
 *****************************************************************************/
static void CopyVectorTable(void)
{
    const uint8_t    u8NrOfVectors = (uint8_t) ((uint32_t) &__Vectors_Size / 4);
    uint32_t * const pu32RamTable  = (uint32_t *) __ramVectors;
    uint32_t * const pu32RomTable  = (uint32_t *) (&__Vectors);


    for(uint8_t u8Index = 0; u8Index < u8NrOfVectors; u8Index++)
    {
        pu32RamTable[u8Index] = pu32RomTable[u8Index];
    }

    SCB->VTOR = (uint32_t) pu32RamTable;
}

/**
 *****************************************************************************
 ** Prepares necessary settings to get SROM system calls working
 **
 ** \return none
 *****************************************************************************/
static void PrepareSystemCallInfrastructure(void)
{
    const uint8_t u8Irq0Index = (uint8_t) (VECTOR_TABLE_OFFSET_IRQ0 / 4);
    const uint8_t u8Irq1Index = (uint8_t) (VECTOR_TABLE_OFFSET_IRQ1 / 4);
    uint32_t * const pu32RamTable   = (uint32_t *) __ramVectors;
    uint32_t * const pu32SromTable  = (uint32_t *) SROM_VECTOR_TABLE_BASE_ADDRESS;

    // Use IRQ0 and IRQ1 handlers from SROM vector table
    pu32RamTable[u8Irq0Index] = pu32SromTable[u8Irq0Index];
    pu32RamTable[u8Irq1Index] = pu32SromTable[u8Irq1Index];

    NVIC_SetPriority(NvicMux0_IRQn, 1);
    NVIC_SetPriority(NvicMux1_IRQn, 0);
    NVIC_EnableIRQ(NvicMux0_IRQn);
    NVIC_EnableIRQ(NvicMux1_IRQn);

    // Only item left is clearing of PRIMASK:
    // This should be done by the application at a later point in time (e.g. in main())
}

/*******************************************************************************
* Function Name: SystemIrqInit
****************************************************************************//**
*
* The function is called during device startup.
*
*******************************************************************************/
void SystemIrqInit(void)
{
    for (int i=0; i<(int)CPUSS_SYSTEM_INT_NR; i++)
    {
        Cy_SystemIrqUserTable[i] = DEFAULT_HANDLER_NAME;
    }

    Cy_SysInt_SystemIrqUserTableRamPointer = Cy_SystemIrqUserTable;
}

/*******************************************************************************
* Function Name: Cy_SystemInit
****************************************************************************//**
*
* The function is called during device startup.
*
*******************************************************************************/
__WEAK void Cy_SystemInit(void)
{
     /* Empty weak function. The actual implementation to be in the app
      * generated strong function.
     */
}

/*******************************************************************************
* Function Name: SystemCoreClockUpdate
****************************************************************************//**
*
* Gets core clock frequency and updates \ref SystemCoreClock.
*
* Updates global variables used by the \ref Cy_SysLib_Delay(), \ref
* Cy_SysLib_DelayUs(), and \ref Cy_SysLib_DelayCycles().
*
*******************************************************************************/
void SystemCoreClockUpdate (void)
{
    uint32_t pathFreqHz;
    uint32_t clkHfPath;

    /* Get frequency for the high-frequency clock*/
    clkHfPath = CY_SYSCLK_CLK_CORE_HF_PATH_NUM;

    pathFreqHz = Cy_SysClk_ClkHfGetFrequency(clkHfPath);

    SystemCoreClock = pathFreqHz;

    cy_Hfclk0FreqHz = SystemCoreClock;

    /* Get Peripheral clock Frequency*/
    clkHfPath = CY_SYSCLK_CLK_PERI_HF_PATH_NUM;

    pathFreqHz = Cy_SysClk_ClkHfGetFrequency(clkHfPath);

    cy_PeriClkFreqHz = pathFreqHz;

    /* Sets clock frequency for Delay API */
    cy_delayFreqHz = SystemCoreClock;
    cy_delayFreqMhz = (uint32_t)((cy_delayFreqHz + CY_DELAY_1M_MINUS_1_THRESHOLD) / CY_DELAY_1M_THRESHOLD);
    cy_delayFreqKhz = (cy_delayFreqHz + CY_DELAY_1K_MINUS_1_THRESHOLD) / CY_DELAY_1K_THRESHOLD;

    /* Get the frequency of AHB source, CLK HF0 is the source for AHB*/
    cy_AhbFreqHz = Cy_SysClk_ClkHfGetFrequency(0UL);
}


uint32_t Cy_SysGetCM7Status(uint8_t core)
{
    uint32_t regValue = 0u;

    CY_ASSERT(core < CORE_MAX);

    if(core == CORE_CM7_0)
    {
        /* Get current power mode */
        regValue = _FLD2VAL(CPUSS_CM7_0_PWR_CTL_PWR_MODE, CPUSS->CM7_0_PWR_CTL);
    }
    else if(core == CORE_CM7_1)
    {
        /* Get current power mode */
        regValue = _FLD2VAL(CPUSS_CM7_1_PWR_CTL_PWR_MODE, CPUSS->CM7_1_PWR_CTL);
    }
    else
    {
        /* */
    }

    return (regValue);
}


void Cy_SysEnableCM7(uint8_t core, uint32_t vectorTableOffset)
{
    uint32_t cmStatus;
    uint32_t interruptState;
    uint32_t regValue;

    CY_ASSERT(core < CORE_MAX);

    interruptState = Cy_SaveIRQ();

    cmStatus = Cy_SysGetCM7Status(core);
    if(cmStatus == CY_SYS_CM7_STATUS_ENABLED)
    {
        // Set core into reset first, so that new settings can get effective
        // This branch is e.g. entered if a debugger is connected that would power-up the CM7,
        // but let it run in ROM boot or pause its execution by keeping CPU_WAIT bit set.
        Cy_SysResetCM7(core);
    }

    // CLK_HF1, by default is disabled for use by CM7_0/1, hence enable
    SRSS->CLK_ROOT_SELECT[1] |= SRSS_CLK_ROOT_SELECT_ENABLE_Msk;

    if(core == CORE_CM7_0)
    {
        /* Adjust the vector address */
        CPUSS->CM7_0_VECTOR_TABLE_BASE = vectorTableOffset;

        /* Enable the Power Control Key */
        regValue = CPUSS->CM7_0_PWR_CTL & ~(CPUSS_CM7_0_PWR_CTL_VECTKEYSTAT_Msk | CPUSS_CM7_0_PWR_CTL_PWR_MODE_Msk);
        regValue |= _VAL2FLD(CPUSS_CM7_0_PWR_CTL_VECTKEYSTAT, CY_SYS_CM7_PWR_CTL_KEY_OPEN);
        regValue |= CY_SYS_CM7_STATUS_ENABLED;
        CPUSS->CM7_0_PWR_CTL = regValue;

        while((CPUSS->CM7_0_STATUS & CPUSS_CM7_0_STATUS_PWR_DONE_Msk) == 0UL)
        {
            /* Wait for the power mode to take effect */
        }

        CPUSS->CM7_0_CTL &= ~(0x1 << CPUSS_CM7_0_CTL_CPU_WAIT_Pos);
    }
    else if(core == CORE_CM7_1)
    {
        /* Adjust the vector address */
        CPUSS->CM7_1_VECTOR_TABLE_BASE = vectorTableOffset;

        /* Enable the Power Control Key */
        regValue = CPUSS->CM7_1_PWR_CTL & ~(CPUSS_CM7_1_PWR_CTL_VECTKEYSTAT_Msk | CPUSS_CM7_1_PWR_CTL_PWR_MODE_Msk);
        regValue |= _VAL2FLD(CPUSS_CM7_1_PWR_CTL_VECTKEYSTAT, CY_SYS_CM7_PWR_CTL_KEY_OPEN);
        regValue |= CY_SYS_CM7_STATUS_ENABLED;
        CPUSS->CM7_1_PWR_CTL = regValue;

        while((CPUSS->CM7_1_STATUS & CPUSS_CM7_1_STATUS_PWR_DONE_Msk) == 0UL)
        {
            /* Wait for the power mode to take effect */
        }

        CPUSS->CM7_1_CTL &= ~(0x1 << CPUSS_CM7_1_CTL_CPU_WAIT_Pos);
    }

    Cy_RestoreIRQ(interruptState);

}


void Cy_SysDisableCM7(uint8_t core)
{
    uint32_t regValue;

    CY_ASSERT(core < CORE_MAX);

    if(core == CORE_CM7_0)
    {
        regValue = CPUSS->CM7_0_PWR_CTL & ~(CPUSS_CM7_0_PWR_CTL_VECTKEYSTAT_Msk | CPUSS_CM7_0_PWR_CTL_PWR_MODE_Msk);
        regValue |= _VAL2FLD(CPUSS_CM7_0_PWR_CTL_VECTKEYSTAT, CY_SYS_CM7_PWR_CTL_KEY_OPEN);
        regValue |= CY_SYS_CM7_STATUS_DISABLED;
        CPUSS->CM7_0_PWR_CTL = regValue;

        while((CPUSS->CM7_0_STATUS & CPUSS_CM7_0_STATUS_PWR_DONE_Msk) == 0UL)
        {
            /* Wait for the power mode to take effect */
        }

    }
    else if(core == CORE_CM7_1)
    {
        regValue = CPUSS->CM7_1_PWR_CTL & ~(CPUSS_CM7_1_PWR_CTL_VECTKEYSTAT_Msk | CPUSS_CM7_1_PWR_CTL_PWR_MODE_Msk);
        regValue |= _VAL2FLD(CPUSS_CM7_1_PWR_CTL_VECTKEYSTAT, CY_SYS_CM7_PWR_CTL_KEY_OPEN);
        regValue |= CY_SYS_CM7_STATUS_DISABLED;
        CPUSS->CM7_1_PWR_CTL = regValue;

        while((CPUSS->CM7_1_STATUS & CPUSS_CM7_0_STATUS_PWR_DONE_Msk) == 0UL)
        {
            /* Wait for the power mode to take effect */
        }
    }
}


void Cy_SysRetainCM7(uint8_t core)
{
    uint32_t cmStatus;
    uint32_t  interruptState;
    uint32_t regValue;

    interruptState = Cy_SaveIRQ();

    cmStatus = Cy_SysGetCM7Status(core);
    if(cmStatus == CY_SYS_CM7_STATUS_ENABLED)
    {
        if(core == CORE_CM7_0)
        {
            regValue = CPUSS->CM7_0_PWR_CTL & ~(CPUSS_CM7_0_PWR_CTL_VECTKEYSTAT_Msk | CPUSS_CM7_0_PWR_CTL_PWR_MODE_Msk);
            regValue |= _VAL2FLD(CPUSS_CM7_0_PWR_CTL_VECTKEYSTAT, CY_SYS_CM7_PWR_CTL_KEY_OPEN);
            regValue |= CY_SYS_CM7_STATUS_RETAINED;
            CPUSS->CM7_0_PWR_CTL = regValue;
        }
        else if(core == CORE_CM7_1)
        {
            regValue = CPUSS->CM7_1_PWR_CTL & ~(CPUSS_CM7_1_PWR_CTL_VECTKEYSTAT_Msk | CPUSS_CM7_1_PWR_CTL_PWR_MODE_Msk);
            regValue |= _VAL2FLD(CPUSS_CM7_1_PWR_CTL_VECTKEYSTAT, CY_SYS_CM7_PWR_CTL_KEY_OPEN);
            regValue |= CY_SYS_CM7_STATUS_RETAINED;
            CPUSS->CM7_1_PWR_CTL = regValue;
        }
    }

    Cy_RestoreIRQ(interruptState);
}


void Cy_SysResetCM7(uint8_t core)
{
    uint32_t regValue;

    CY_ASSERT(core < CORE_MAX);

    if(core == CORE_CM7_0)
    {
        regValue = CPUSS->CM7_0_PWR_CTL & ~(CPUSS_CM7_0_PWR_CTL_VECTKEYSTAT_Msk | CPUSS_CM7_0_PWR_CTL_PWR_MODE_Msk);
        regValue |= _VAL2FLD(CPUSS_CM7_0_PWR_CTL_VECTKEYSTAT, CY_SYS_CM7_PWR_CTL_KEY_OPEN);
        regValue |= CY_SYS_CM7_STATUS_RESET;
        CPUSS->CM7_0_PWR_CTL = regValue;

        while((CPUSS->CM7_0_STATUS & CPUSS_CM7_0_STATUS_PWR_DONE_Msk) == 0UL)
        {
            /* Wait for the power mode to take effect */
        }
    }
    else if(core == CORE_CM7_1)
    {
        regValue = CPUSS->CM7_1_PWR_CTL & ~(CPUSS_CM7_1_PWR_CTL_VECTKEYSTAT_Msk | CPUSS_CM7_1_PWR_CTL_PWR_MODE_Msk);
        regValue |= _VAL2FLD(CPUSS_CM7_1_PWR_CTL_VECTKEYSTAT, CY_SYS_CM7_PWR_CTL_KEY_OPEN);
        regValue |= CY_SYS_CM7_STATUS_RESET;
        CPUSS->CM7_1_PWR_CTL = regValue;

        while((CPUSS->CM7_1_STATUS & CPUSS_CM7_1_STATUS_PWR_DONE_Msk) == 0UL)
        {
            /* Wait for the power mode to take effect */
        }
    }
}


/*******************************************************************************
* Function Name: Cy_DefaultUserHandler
****************************************************************************//**
*
* The Handler is called when the CPU attempts to call IRQ that has not been mapped to user functions.
*
*******************************************************************************/
void Cy_DefaultUserHandler(void)
{
    // This IRQ occurred because CPU attempted to call IRQ that has not been mapped to user function
    while(1);
}


/*******************************************************************************
* Function Name: CM0P_CpuIntr_HandlerInline
****************************************************************************//**
*
* The Inline handler for CPU interrupt.
* The system interrupt mapped to CPU interrupt will be fetched and executed
*
*******************************************************************************/
__STATIC_FORCEINLINE void CM0P_CpuIntr_HandlerInline(uint8_t intrNum)
{
    uint32_t system_int_idx;
    cy_israddress handler;

    if (_FLD2VAL(CPUSS_CM0_INT0_STATUS_SYSTEM_INT_VALID, CPUSS_CM0_INT_STATUS_BASE[intrNum]))
    {
        system_int_idx = _FLD2VAL(CPUSS_CM0_INT0_STATUS_SYSTEM_INT_IDX, CPUSS_CM0_INT_STATUS_BASE[intrNum]);
        handler = Cy_SystemIrqUserTable[system_int_idx];
        if(handler != NULL)
        handler(); // jump to system interrupt handler
    }
    else
    {
        // Triggered by software or because of software cleared a peripheral interrupt flag but did not clear the pending flag at NVIC
    }
    NVIC_ClearPendingIRQ((IRQn_Type)intrNum);
}


/*******************************************************************************
* Function Name: CpuIntr2_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt2 occurs.
*
*******************************************************************************/
void CM0P_CpuIntr2_Handler(void)
{
    CM0P_CpuIntr_HandlerInline(2);
}


/*******************************************************************************
* Function Name: CpuIntr3_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt3 occurs.
*
*******************************************************************************/
void CM0P_CpuIntr3_Handler(void)
{
    CM0P_CpuIntr_HandlerInline(3);
}


/*******************************************************************************
* Function Name: CpuIntr4_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt4 occurs.
*
*******************************************************************************/
void CM0P_CpuIntr4_Handler(void)
{
    CM0P_CpuIntr_HandlerInline(4);
}

/*******************************************************************************
* Function Name: CpuIntr5_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt5 occurs.
*
*******************************************************************************/
void CM0P_CpuIntr5_Handler(void)
{
    CM0P_CpuIntr_HandlerInline(5);
}


/*******************************************************************************
* Function Name: CpuIntr6_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt6 occurs.
*
*******************************************************************************/
void CM0P_CpuIntr6_Handler(void)
{
    CM0P_CpuIntr_HandlerInline(6);
}


/*******************************************************************************
* Function Name: CpuIntr7_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt7 occurs.
*
*******************************************************************************/
void CM0P_CpuIntr7_Handler(void)
{
    CM0P_CpuIntr_HandlerInline(7);
}


