/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
/*================================================================================================
*   @file    system.c
*   @version 5.0.0
*
*   @brief   AUTOSAR Platform - SYSTEM
*   @details SYSTEM
*            This file contains sample code only. It is not part of the production code deliverables.
*   @addtogroup PLATFORM
*   @{
*
==================================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Platform_Types.h"
#include "Mcal.h"
#include "system.h"
#include "core_specific.h"

#ifdef S32K344
    #include "S32K344_SCB.h"
    #include "S32K344_MPU.h"
    #include "S32K344_MSCM.h"
#endif
#ifdef S32K342
    #include "S32K342_SCB.h"
    #include "S32K342_MPU.h"
    #include "S32K342_MSCM.h"
#endif
#ifdef S32K341
    #include "S32K341_SCB.h"
    #include "S32K341_MPU.h"
    #include "S32K341_MSCM.h"
#endif
#ifdef S32K324
    #include "S32K324_SCB.h"
    #include "S32K324_MPU.h"
    #include "S32K324_MSCM.h"
#endif
#ifdef S32K314
    #include "S32K314_SCB.h"
    #include "S32K314_MPU.h"
    #include "S32K314_MSCM.h"
#endif
#ifdef S32K312
    #include "S32K312_SCB.h"
    #include "S32K312_MPU.h"
    #include "S32K312_MSCM.h"
#endif
#ifdef S32K322
    #include "S32K322_SCB.h"
    #include "S32K322_MPU.h"
    #include "S32K322_MSCM.h"
#endif
#if defined(S32K396) || defined(S32K394) || defined(S32K364) || defined(S32K366)
    #include "S32K39_SCB.h"
    #include "S32K39_MPU.h"
    #include "S32K39_MSCM.h"
#endif
#if defined(S32K374) || defined(S32K376)
    #include "S32K37_SCB.h"
    #include "S32K37_MPU.h"
    #include "S32K37_MSCM.h"
#endif
#if defined(S32K358) || defined(S32K328) || defined(S32K338) || defined(S32K348)
    #include "S32K358_SCB.h"
    #include "S32K358_MPU.h"
    #include "S32K358_MSCM.h"
#endif
#ifdef S32K388
    #include "S32K388_SCB.h"
    #include "S32K388_MPU.h"
    #include "S32K388_MSCM.h"
#endif
#if defined(S32K311) || defined(S32K310)
    #include "S32K311_SCB.h"
    #include "S32K311_MPU.h"
    #include "S32K311_MSCM.h"
#endif
#if defined(S32M276) || defined(S32M274)
    #include "S32M27x_SCB.h"
    #include "S32M27x_MPU.h"
    #include "S32M27x_MSCM.h"
#endif

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

extern  uint32 __INT_ITCM_START[];
extern  uint32 __ROM_CODE_START[];
extern  uint32 __ROM_DATA_START[];
extern  uint32 __INT_DTCM_START[];
extern  uint32 __INT_SRAM_START[];
extern  uint32 __RAM_NO_CACHEABLE_START[];
extern  uint32 __RAM_SHAREABLE_START[];
extern  uint32 __RAM_CACHEABLE_SIZE[];
extern  uint32 __RAM_NO_CACHEABLE_SIZE[];
extern  uint32 __RAM_SHAREABLE_SIZE[];
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define CM7_0  (0UL)
#define CM7_1  (1UL)
#define CM7_2  (2UL)
#define CM7_3  (3UL)

#define MSCM_ITCM_DECOUPLE_MODE         (0x7UL)
#define MSCM_ITCM_LOCKSTEP_MODE         (0x8UL)
#define MSCM_DTCM_DECOUPLE_MODE         (0x8UL)
#define MSCM_DTCM_LOCKSTEP_MODE         (0x9UL)
#define MPU_TCM_32KB_SIZE               (0xFUL)
#define MPU_TCM_64KB_SIZE               (0x10UL)
#define MPU_TCM_128KB_SIZE              (0x11UL)
#define SVC_GoToSupervisor()                        ASM_KEYWORD("svc 0x0")
#define SVC_GoToUser()                              ASM_KEYWORD("svc 0x1")

#define S32_SCB_CPACR_CPx_MASK(CpNum)               (0x3U << S32_SCB_CPACR_CPx_SHIFT(CpNum))
#define S32_SCB_CPACR_CPx_SHIFT(CpNum)              (2U*((uint32)CpNum))
#define S32_SCB_CPACR_CPx(CpNum, x)                 (((uint32)(((uint32)(x))<<S32_SCB_CPACR_CPx_SHIFT((CpNum))))&S32_SCB_CPACR_CPx_MASK((CpNum)))

/* MPU setting */
#define CPU_MPU_MEMORY_COUNT (16U)

/* Check symbol and linker information in linker file of each derivative 
 * Region 15: Only S32K388
*/
/*
  Region  Description       Start                       End                                      Size[KB]  Type              Inner Cache Policy    Outer Cache Policy    Shareable    Executable    Privileged Access    Unprivileged Access
--------  -------------     ----------                  ----------                             ----------  ----------------  --------------------  --------------------  -----------  ------------  -------------------  ---------------------
       0  Whole memory map  0x00000000                  0xFFFFFFFF                                4194304  Strongly Ordered  None                  None                  Yes          No            No Access            No Access
       1  ITCM              0x00000000                  0x0000FFFF                                     64  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           No Access
       2  Program Flash 1   0x40000000                  PFLASH SIZE                           PFLASH SIZE  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read-Only            Read-Only
       3  Data Flash        0x10000000                  0x1003FFFF                                    256  Normal            Write-Back/Allocate   Write-Back/Allocate   No           No            Read-Only            Read-Only
       4  UTEST             0x1B000000                  0x1B001FFF                                   8192  Normal            Write-Back/Allocate   Write-Back/Allocate   No           No            Read-Only            Read-Only
       5  DTCM              0x20000000                  0x2001FFFF                                    128  Normal            None                  None                  No           Yes           Read/Write           Read/Write
       6  SRAM CACHE        __RAM_CACHEABLE_START      __RAM_CACHEABLE_END           __RAM_CACHEABLE_SIZE  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       7  SRAM N-CACHE      __RAM_NO_CACHEABLE_START      __RAM_NO_CACHEABLE_END  __RAM_NO_CACHEABLE_SIZE  Normal            None                  None                  Yes          No            Read/Write           Read/Write
       8  SRAM SHARED       __RAM_SHAREABLE_START      __RAM_SHAREABLE_END           __RAM_SHAREABLE_SIZE  Normal            None                  None                  Yes          No            Read/Write           Read/Write
       9  AIPS_0/1/2        0x40000000                 0x405FFFFF                                    6144  Strongly ordered  None                  None                  Yes          No            Read/Write           Read/Write
      10  AIPS_3            0x40600000                 0x407FFFFF                                    2048  Strongly ordered  None                  None                  Yes          No            Read/Write           Read/Write
      11  QSPI Rx           0x67000000                 0x670003FF                                       1  Strongly ordered  None                  None                  Yes          No            Read/Write           Read/Write
      12  QSPI AHB          0x68000000                 0x6FFFFFFF                                  131072  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
      13  PPB               0xE0000000                 0xE00FFFFF                                    1024  Strongly Ordered  None                  None                  Yes          No            Read/Write           Read/Write
      14  Program Flash 2   0x00800000                 PFLASH SIZE                            PFLASH SIZE  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read-Only            Read-Only
      15  ACE               0x44000000                 0x440003FF                                       1  Strongly-ordered  None                  None                  Yes          No            Read/Write           Read/Write
*/
volatile   uint32 rbar[CPU_MPU_MEMORY_COUNT] = {0x0UL};
volatile   uint32 rasr[CPU_MPU_MEMORY_COUNT] = {0x0UL};

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================-
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
#define PLATFORM_START_SEC_VAR_CLEARED_32
#include "Platform_MemMap.h"

/* Allocate a global variable which will be overwritten by the debugger if attached(in CMM), to catch the core after reset. */
uint32 RESET_CATCH_CORE;

#define PLATFORM_STOP_SEC_VAR_CLEARED_32
#include "Platform_MemMap.h"
/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"

/*================================================================================================*/
/*
 * @brief Initializes the caches on the platform based on build options. This requires the MPU areas to be configured and enabled before calling this routine.
 * @param: None
 *
 * @return: None
 */
static INLINE void sys_m7_cache_init(void);
/*
 * @brief Disables any previously configured and initialized cache, please make sure MPU is enabled before calling these apis
 * @param: None
 *
 * @return: None
 */
static INLINE void sys_m7_cache_disable(void);
/*
 * @brief Performs a cache clean operation over the configured caches.
 * @param: None
 *
 * @return: None
 */
static INLINE void sys_m7_cache_clean(void);


#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
LOCAL_INLINE void Direct_GoToUser(void);
#endif
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
LOCAL_INLINE void Direct_GoToUser(void)
{
    ASM_KEYWORD("push {r0}");
    ASM_KEYWORD("ldr r0, =0x1");
    ASM_KEYWORD("msr CONTROL, r0");
    ASM_KEYWORD("pop {r0}");
}
#endif
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
    extern uint32 startup_getControlRegisterValue(void);
    extern uint32 startup_getAipsRegisterValue(void);
    extern void Suspend_Interrupts(void);
    extern void Resume_Interrupts(void);
#endif /*MCAL_ENABLE_USER_MODE_SUPPORT*/



/*================================================================================================*/
/**
* @brief    startup_go_to_user_mode
* @details  Function called from startup.s to switch to user mode if MCAL_ENABLE_USER_MODE_SUPPORT
*           is defined
*/
/*================================================================================================*/
void startup_go_to_user_mode(void);
void startup_go_to_user_mode(void)
{
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
    ASM_KEYWORD("svc 0x1");
#endif
}

/*================================================================================================*/
/**
* @brief   Default IRQ handler
* @details Infinite Loop
*/
/*================================================================================================*/
void default_interrupt_routine(void)
{
    while(TRUE){};
}

/*================================================================================================*/
/**
* @brief Sys_GoToSupervisor
* @details function used to enter to supervisor mode.
*           check if it's needed to switch to supervisor mode and make the switch.
*           Return 1 if switch was done
*/
/*================================================================================================*/

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
uint32 Sys_GoToSupervisor(void)
{
    uint32 u32ControlRegValue;
    uint32 u32AipsRegValue;
    uint32 u32SwitchToSupervisor;

    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();

    /* if core is already in supervisor mode for Thread mode, or running form Handler mode, there is no need to make the switch */
    if((0U == (u32ControlRegValue & 1u)) || (0u < (u32AipsRegValue & 0xFFu)))
    {
        u32SwitchToSupervisor = 0U;
    }
    else
    {
        u32SwitchToSupervisor = 1U;
        SVC_GoToSupervisor();
    }

    return u32SwitchToSupervisor;
}

/*================================================================================================*/
/**
* @brief Sys_GoToUser_Return
* @details function used to switch back to user mode for Thread mode, return a uint32 value passed as parameter
*/
/*================================================================================================*/
uint32 Sys_GoToUser_Return(uint32 u32SwitchToSupervisor, uint32 u32returnValue)
{
    if (1UL == u32SwitchToSupervisor)
    {
        Direct_GoToUser();
    }

    return u32returnValue;
}

uint32 Sys_GoToUser(void)
{
    Direct_GoToUser();
    return 0UL;
}
/*================================================================================================*/
/**
* @brief Sys_SuspendInterrupts
* @details Suspend Interrupts
*/
/*================================================================================================*/
void Sys_SuspendInterrupts(void)
{
    uint32 u32ControlRegValue;
    uint32 u32AipsRegValue;

    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();

    if((0U == (u32ControlRegValue & 1u)) || (0u < (u32AipsRegValue & 0xFFu)))
    {
        Suspend_Interrupts();
    }
    else
    {
        ASM_KEYWORD(" svc 0x3");
    }
}
/*================================================================================================*/
/**
* @brief Sys_ResumeInterrupts
* @details Resume Interrupts
*/
/*================================================================================================*/
void Sys_ResumeInterrupts(void)
{
    uint32 u32ControlRegValue;
    uint32 u32AipsRegValue;

    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();

    if((0U == (u32ControlRegValue & 1u)) || (0u < (u32AipsRegValue & 0xFFu)))
    {
        Resume_Interrupts();
    }
    else
    {
        ASM_KEYWORD(" svc 0x2");
    }
}
#endif
/*================================================================================================*/
/**
* @brief Sys_GetCoreID
* @details Function used to get the ID of the currently executing thread
*/
/*================================================================================================*/
#if !defined(USING_OS_AUTOSAROS)
uint8 Sys_GetCoreID(void)
{
    return (IP_MSCM->CPXNUM & MSCM_CPXNUM_CPN_MASK);
}
#endif

/*================================================================================================*/
/*
 * system initialization : system clock, interrupt router ...
 */


void SystemInit(void)
{
    uint32 i;
    uint32 coreMask = 0UL;
    uint8 coreId = OsIf_GetCoreID();
#ifdef MPU_ENABLE
    uint8 index = 0U;
    uint8 regionNum = 0U;
    uint32 u32ItcmMode = ((IP_MSCM->CPXCFG2 & MSCM_CPXCFG2_ITCMSZ_MASK) >> MSCM_CPXCFG2_ITCMSZ_SHIFT);
    uint32 u32DtcmMode = ((IP_MSCM->CPXCFG2 & MSCM_CPXCFG2_DTCMSZ_MASK) >> MSCM_CPXCFG2_DTCMSZ_SHIFT);
#endif /* MPU_ENABLE */
    switch(coreId)
    {
        case CM7_0:
            coreMask = (1UL << MSCM_IRSPRC_M7_0_SHIFT);
            break;
        case CM7_1:
#if defined (S32K324) || defined (S32K358) || defined(S32K328) || defined(S32K338) || defined(S32K348)
            coreMask = (1UL << MSCM_IRSPRC_M7_1_SHIFT);
#endif
            break;
        case CM7_2:
#if defined(S32K396) || defined(S32K394) || defined(S32K376) || defined(S32K374) || defined(S32K364) || defined(S32K366)
            coreMask = (1UL << MSCM_IRSPRC_M7_2_SHIFT);
#endif
            break;
        case CM7_3:
#ifdef S32K388
            coreMask = (1UL << MSCM_IRSPRC_M7_3_SHIFT);
            break;
#endif
        default:
            coreMask = 0UL;
            break;
    }

    /* Configure MSCM to enable/disable interrupts routing to Core processor */
    for (i = 0; i < MSCM_IRSPRC_COUNT; i++)
    {
        IP_MSCM->IRSPRC[i] |= coreMask;
    }
/**************************************************************************/
                      /* MPU ENABLE*/
/**************************************************************************/
#ifdef MPU_ENABLE
/**************************************************************************/
                      /* DEFAULT MEMORY ENABLE*/
/**************************************************************************/
    /* Init MPU table for memory layout*/
    /* Cover all memory on device as background set all memory as strong-order and no access*/
    rbar[0]=0x00000000UL;
    rasr[0]=0x1004003FUL;
    /* Note: For code portability to other Arm processors or systems, Arm recommends that TCM regions are always defined as Normal, Non-shared memory in the MPU. */
    /* This is consistent with the default ARMv7E-M memory map attributes that apply when the MPU is either disabled or not implemented.*/

    /* ITCM for cortex M7 if no set it as zero */
    rbar[1]=(uint32)__INT_ITCM_START;
    /* Size: depends on current mode (Lockstep/Decoupled Mode), Type: Normal, Inner Cache Policy: None, Outer Cache Policy: None, Shareable: No, Privileged Access:RW, Unprivileged Access:RW */
    if (MSCM_ITCM_LOCKSTEP_MODE == u32ItcmMode)
    {
        rasr[1] = ((uint32)0x03080001UL)|(((uint32)MPU_TCM_64KB_SIZE - 1) << 1);
    }
    else
    {
        /* Decoupled Mode */
        rasr[1] = ((uint32)0x03080001UL)|(((uint32)MPU_TCM_32KB_SIZE - 1) << 1);
    }

    rbar[2]=(uint32)__ROM_CODE_START;
#if defined(S32K311) || defined(S32K341) || defined(S32M276) || defined(S32K310) || defined(S32M274)
    rasr[2]=0x070B0027UL; /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back. write and read allocate, Shareable: No, Privileged Access: Read-Only, Unprivileged Access: Read-Only */
#elif defined(S32K342) || defined(S32K312) || defined(S32K322)
    rasr[2]=0x070B0029UL; /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back. write and read allocate, Shareable: No, Privileged Access: Read-Only, Unprivileged Access: Read-Only */
#else
    rasr[2]=0x070B002BUL; /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back. write and read allocate, Shareable: No, Privileged Access: Read-Only, Unprivileged Access: Read-Only */
#endif

    /*Data flash which would extract from linker symbol*/
    rbar[3]=(uint32)__ROM_DATA_START;
    rasr[3]=0x160B0023UL; /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back. write and read allocate, Shareable: Yes, Privileged Access: Read-Only, Unprivileged Access: Read-Only */

    /*UTEST*/
    rbar[4]=0x1B000000UL;
    /* Size: 8KB, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back. write and read allocate, Shareable: Yes, Privileged Access: Read-Only, Unprivileged Access: Read-Only */
    rasr[4]=0x160B0019UL;

    /*DTCM for cortex m7 if no set it as zero*/
    rbar[5]=(uint32)__INT_DTCM_START;
    /* Size: depends on current mode (Lockstep/Decoupled Mode), Type: Normal, Inner Cache Policy: None, Outer Cache Policy: None, Shareable: No, Privileged Access:RW, Unprivileged Access:RW */
    if (MSCM_DTCM_LOCKSTEP_MODE == u32DtcmMode)
    {
        rasr[5] = ((uint32)0x03080001UL)|(((uint32)MPU_TCM_128KB_SIZE - 1) << 1);
    }
    else
    {
        /* Decoupled Mode */
        rasr[5] = ((uint32)0x03080001UL)|(((uint32)MPU_TCM_64KB_SIZE - 1) << 1);
    }

    /*Ram unified section*/
#if defined(S32K396) || defined(S32K394) || defined(S32K344) || defined(S32K324) || defined(S32K314) || defined(S32K374)|| defined(S32K376) || defined(S32K364) || defined(S32K366)
    rbar[6]=(uint32)__INT_SRAM_START;
    /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back, write and read allocate, Shareable: No, Privileged Access:RW, Unprivileged Access:RW */
    #if (defined(S32K396) || defined(S32K394) || defined(S32K376) || defined(S32K374)|| defined(S32K366) || defined(S32K364)) && defined(MULTIPLE_IMAGE)
    rasr[6]=((uint32)0x030B0001UL)|(((uint32)__RAM_CACHEABLE_SIZE - 1) << 1);
    #else
    /* Disable subregion 7 & 8*/
    rasr[6]=((uint32)0x030B0001UL)|(((uint32)__RAM_CACHEABLE_SIZE - 1) << 1)|(1<<15)|(1<<14);
    #endif
#else
    rbar[6]=(uint32)__INT_SRAM_START;
    /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back, write and read allocate, Shareable: No, Privileged Access:RW, Unprivileged Access:RW */
    rasr[6]=((uint32)0x030B0001UL)|(((uint32)__RAM_CACHEABLE_SIZE - 1) << 1);
#endif

    /* Limitation : TCM is not cacheable memory, the purpose is to expand the RAM size for low RAM derivatives. Used for cases like ccov testing,... */
#ifdef EXTEND_LOWRAM_DERIVATIVES
    #if defined(S32K310) || defined(S32K311) || defined(S32M274) || defined(S32M276)
    rbar[6]=(uint32)__INT_DTCM_START;
    /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back, write and read allocate, Shareable: No, Privileged Access:RW, Unprivileged Access:RW */
    rasr[6]=((uint32)0x030B0001UL)|(((uint32)__RAM_CACHEABLE_SIZE - 1) << 1);
    #endif
#endif

    /*Ram non-cache section plus int result which is using for test report*/
    rbar[7]=(uint32)__RAM_NO_CACHEABLE_START;
    /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: None, Outer Cache Policy: None, Shareable: Yes, Privileged Access:RW, Unprivileged Access:RW */
    rasr[7]= ((uint32)0x130C0001UL)|(((uint32)__RAM_NO_CACHEABLE_SIZE - 1) << 1);

#ifdef EXTEND_LOWRAM_DERIVATIVES
    #if defined(S32K310) || defined(S32K311) || defined(S32M274) || defined(S32M276)
    /*Ram non-cache section plus int result which is using for test report*/
    rbar[7]=(uint32)__INT_SRAM_START;
    /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: None, Outer Cache Policy: None, Shareable: Yes, Privileged Access:RW, Unprivileged Access:RW */
    rasr[7]= ((uint32)0x130C0001UL)|(((uint32)__RAM_NO_CACHEABLE_SIZE - 1) << 1);
    #endif
#endif

    /*Ram shareable section*/
    rbar[8]=(uint32)__RAM_SHAREABLE_START;
    /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: None, Outer Cache Policy: None, Shareable: Yes, Privileged Access:RW, Unprivileged Access:RW */
    rasr[8]=((uint32)0x130C0001UL)|(((uint32)__RAM_SHAREABLE_SIZE - 1) << 1);
    /* Additional configuration for peripheral device*/

    /*AIPS_0, AIPS_1, AIPS_2*/
    rbar[9]=0x40000000UL;
    /* Size: 6MB, Type: Strongly-ordered, Inner Cache Policy: None, Outer Cache Policy: None, Shareable: Yes, Privileged Access:RW, Unprivileged Access:RW */
    /* Disable subregion 7 & 8*/
    rasr[9]=((uint32)0x1304002DUL)|(1<<15)|(1<<14);

    /*AIPS_3*/
    rbar[10]=0x40600000UL;
#if defined(S32K396) || defined(S32K394) || defined(S32K374) || defined(S32K376) || defined(S32K364) || defined(S32K366)
    /* Size: 2MB, Type: Strongly-ordered, Inner Cache Policy: None, Outer Cache Policy: None, Shareable: Yes, Privileged Access:RW, Unprivileged Access:RW */
    rasr[10]=0x13040029UL;
#else
    rasr[10]=0x0UL;
#endif /* S32K39x */

    /*QSPI Rx*/
    rbar[11]=0x67000000UL;
    /* Size: 128MB, Type: Strongly-ordered, Inner Cache Policy: None, Outer Cache Policy: None, Shareable: Yes, Privileged Access:RW, Unprivileged Access:RW */
    rasr[11]=0x13040013UL;

    /*QSPI AHB*/
    rbar[12]=0x68000000UL;
    /* Size: 128MB, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back, write and read allocate, Shareable: No, Privileged Access:RW, Unprivileged Access:RW */
    rasr[12]=0x030B0035UL;

    /*Private Peripheral Bus*/
    rbar[13]=0xE0000000UL;
    /* Size: Normal, Type: Strongly-ordered, Inner Cache Policy: None, Outer Cache Policy: None, Shareable: Yes, Privileged Access:RW, Unprivileged Access:RW */
    rasr[13]=0x13040027UL;

    /* Program flash */
    /* Note: Do not merge with MPU region 2 because of alignment with the size */
    rbar[14]=(uint32)((uint32)__ROM_CODE_START + 0x400000UL);
#if defined(S32K396) || defined(S32K376) || defined(S32K366)
    rasr[14]=0x070B0029UL; /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back. write and read allocate, Shareable: No, Privileged Access: Read-Only, Unprivileged Access: Read-Only */
#elif defined(S32K358) || defined(S32K388) || defined(S32K328) || defined(S32K338) || defined(S32K348)
    rasr[14]=0x070B002BUL; /* Size: import information from linker symbol, Type: Normal, Inner Cache Policy: Inner write-back, write and read allocate, Outer Cache Policy: Outer write-back. write and read allocate, Shareable: No, Privileged Access: Read-Only, Unprivileged Access: Read-Only */
#else
    rasr[14]=0UL;
#endif
    /*ACE region*/
    rbar[15]=0x44000000UL;
#if defined(S32K388)
    /* Size: 1KB, Type: Strongly-ordered, Inner Cache Policy: None, Outer Cache Policy: None, Shareable: Yes, Privileged Access:RW, Unprivileged Access:RW */
    rasr[15]=0x13040013UL;
#else
    rasr[15]=0UL;
#endif
    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();

    /*Checking if cache is enable before*/
    if (((((uint32)1U << (uint32)17U) & S32_SCB->CCR) != (uint32)0) || ((((uint32)1U << (uint32)16U) & S32_SCB->CCR) != (uint32)0))
    {
 /*synchronize cache before update mpu */
        sys_m7_cache_clean();
        sys_m7_cache_disable();
    }
    /* Set default memory regions */
    for (index = 0U; index < CPU_MPU_MEMORY_COUNT; index++)
    {
        if ((rasr[index]&(uint32)0x1) == (uint32)0x1)
        {
            S32_MPU->RNR  = regionNum;
            S32_MPU->RBAR = rbar[index];
            S32_MPU->RASR = rasr[index];
            regionNum++;
        }
    }

    /* Enable MPU, enables the MPU during the HardFault handler */
    S32_MPU->CTRL |= (S32_MPU_CTRL_ENABLE_MASK | S32_MPU_CTRL_HFNMIENA_MASK);

    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();

#endif /* MPU_ENABLE */
/**************************************************************************/
            /* ENABLE CACHE */
/**************************************************************************/
#if defined(D_CACHE_ENABLE) || defined(I_CACHE_ENABLE)
    sys_m7_cache_init();
#endif /*defined(D_CACHE_ENABLE) || defined(I_CACHE_ENABLE)*/
}


/* Cache apis which are using for cache initilization, please make sure MPU is enable before calling these apis. Due to limitation of speculative access on cortex m7, MPU need to be initialized before enable cache. So if user specify -DDISABLE_MPUSTARTUP, cache will be disable in startup as well. If user want to enable cache again please call cache api after RM_init() or MPU_init() */

static INLINE void sys_m7_cache_init(void)
{
#ifdef D_CACHE_ENABLE
    uint32 ccsidr = 0U;
    uint32 sets = 0U;
    uint32 ways = 0U;


    /*init Data caches*/
    S32_SCB->CSSELR = 0U;                       /* select Level 1 data cache */
    MCAL_DATA_SYNC_BARRIER();
    ccsidr = S32_SCB->CCSIDR;
    sets = (uint32)(CCSIDR_SETS(ccsidr));
    do {
      ways = (uint32)(CCSIDR_WAYS(ccsidr));
      do {
        S32_SCB->DCISW = (((sets << SCB_DCISW_SET_SHIFT) & SCB_DCISW_SET_MASK) |
                      ((ways << SCB_DCISW_WAY_SHIFT) & SCB_DCISW_WAY_MASK)  );
        MCAL_DATA_SYNC_BARRIER();
      } while (ways-- != 0U);
    } while(sets-- != 0U);
    MCAL_DATA_SYNC_BARRIER();
    S32_SCB->CCR |=  (uint32)SCB_CCR_DC_MASK;  /* enable D-Cache */
    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();;
#endif /*D_CACHE_ENABLE*/

#ifdef I_CACHE_ENABLE
    /*init Code caches*/
    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();;
    S32_SCB->ICIALLU = 0UL;                     /* invalidate I-Cache */
    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();;
    S32_SCB->CCR |=  (uint32)SCB_CCR_IC_MASK;  /* enable I-Cache */
    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();;
#endif /*I_CACHE_ENABLE*/

}


static INLINE void sys_m7_cache_disable(void)
{
    sys_m7_cache_clean();
    S32_SCB->CCR &= ~((uint32)1U << 17U);
    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();;
    S32_SCB->CCR &= ~((uint32)1U << 16U);
    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();;
}


static INLINE void sys_m7_cache_clean(void)
{
#ifdef D_CACHE_ENABLE
    uint32 ccsidr = 0U;
    uint32 sets = 0U;
    uint32 ways = 0U;

    S32_SCB->CSSELR = 0U;                       /* select Level 1 data cache */
    MCAL_DATA_SYNC_BARRIER();
    ccsidr = S32_SCB->CCSIDR;
    sets = (uint32)(CCSIDR_SETS(ccsidr));
    do {
      ways = (uint32)(CCSIDR_WAYS(ccsidr));
      do {
        S32_SCB->DCCISW = (((sets << 5) & (uint32)0x3FE0U) |
                      ((ways << 30) & (uint32)0xC0000000U)  );
        MCAL_DATA_SYNC_BARRIER();
      } while (ways-- != 0U);
    } while(sets-- != 0U);

    S32_SCB->CSSELR = (uint32)((S32_SCB->CSSELR) | 1U);
#endif /*D_CACHE_ENABLE*/

#ifdef I_CACHE_ENABLE
    S32_SCB->ICIALLU = 0UL;
#endif /*I_CACHE_ENABLE*/
    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();;
}
/**************************************************************************/
                      /* FPU ENABLE*/
/**************************************************************************/
void Enable_FPU(void)
{
#ifdef ENABLE_FPU
    /* Enable CP10 and CP11 coprocessors */
    S32_SCB->CPACR |= (S32_SCB_CPACR_CPx(10U, 3U) | S32_SCB_CPACR_CPx(11U, 3U)); 

    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();;
#endif /* ENABLE_FPU */
}

#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

#ifdef __cplusplus
}
#endif
