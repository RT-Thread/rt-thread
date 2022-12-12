/*
File Name    : board_config.h
Author       : Yichip
Version      : V1.0
Date         : 2020/07/17
Description  : misc file.
*/

#include "misc.h"

/* following defines should be used for structure members */
#define __IM volatile const /*! Defines 'read only' structure member permissions */
#define __OM volatile       /*! Defines 'write only' structure member permissions */
#define __IOM volatile      /*! Defines 'read / write' structure member permissions */

/* Memory mapping of Cortex-M0 Hardware */
#define SCS_BASE (0xE000E000UL)         /*!< System Control Space Base Address */
#define NVIC_BASE (SCS_BASE + 0x0100UL) /*!< NVIC Base Address */
#define SCB_BASE (SCS_BASE + 0x0D00UL)  /*!< System Control Block Base Address */

typedef struct
{
    __IM uint32_t CPUID; /*!< Offset: 0x000 (R/ )  CPUID Base Register */
    __IOM uint32_t ICSR; /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
    uint32_t RESERVED0;
    __IOM uint32_t AIRCR; /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
    __IOM uint32_t SCR;   /*!< Offset: 0x010 (R/W)  System Control Register */
    __IOM uint32_t CCR;   /*!< Offset: 0x014 (R/W)  Configuration Control Register */
    uint32_t RESERVED1;
    __IOM uint32_t SHP[2U]; /*!< Offset: 0x01C (R/W)  System Handlers Priority Registers. [0] is RESERVED */
    __IOM uint32_t SHCSR;   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
} SCB_Type;

/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
    __IOM uint32_t ISER[1U]; /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
    uint32_t RESERVED0[31U];
    __IOM uint32_t ICER[1U]; /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
    uint32_t RSERVED1[31U];
    __IOM uint32_t ISPR[1U]; /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
    uint32_t RESERVED2[31U];
    __IOM uint32_t ICPR[1U]; /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
    uint32_t RESERVED3[31U];
    uint32_t RESERVED4[64U];
    __IOM uint32_t IP[8U]; /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
} NVIC_Type;

#define SCB ((SCB_Type *)SCB_BASE)    /*!< SCB configuration struct */
#define NVIC ((NVIC_Type *)NVIC_BASE) /*!< NVIC configuration struct */

/* The following MACROS handle generation of the register offset and byte masks */
#define _BIT_SHIFT(IRQn) (((((uint32_t)(int32_t)(IRQn))) & 0x03UL) * 8UL)
#define _SHP_IDX(IRQn) ((((((uint32_t)(int32_t)(IRQn)) & 0x0FUL) - 8UL) >> 2UL))
#define _IP_IDX(IRQn) ((((uint32_t)(int32_t)(IRQn)) >> 2UL))

/* ----------------Configuration of the Cortex-M0 Processor and Core Peripherals---------------- */
#define __CM0_REV 0x0000         /*!< Cortex-M0 Core Revision                                               */
#define __MPU_PRESENT 0          /*!< MPU present or not                                                    */
#define __NVIC_PRIO_BITS 2       /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig 0 /*!< Set to 1 if different SysTick Config is used                          */
/* End of group Configuration_of_CMSIS */

uint32_t NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    if ((int32_t)(IRQn) < 0)
    {
        SCB->SHP[_SHP_IDX(IRQn)] = ((uint32_t)(SCB->SHP[_SHP_IDX(IRQn)] & ~(0xFFUL << _BIT_SHIFT(IRQn))) |
                                    (((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL) << _BIT_SHIFT(IRQn)));
    }
    else
    {
        NVIC->IP[_IP_IDX(IRQn)] = ((uint32_t)(NVIC->IP[_IP_IDX(IRQn)] & ~(0xFFUL << _BIT_SHIFT(IRQn))) |
                                   (((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL) << _BIT_SHIFT(IRQn)));
    }
    return SUCCESS;
}

#define SBC_ICSR_PENDSV_IRQ 28
void trigger_PendSV(void)
{
    SCB->ICSR |= (1 << SBC_ICSR_PENDSV_IRQ);
}

void NVIC_EnableIRQ(IRQn_Type IRQnx)
{
    enable_intr((int)IRQnx);
}

void NVIC_DisableIRQ(IRQn_Type IRQnx)
{
    disable_intr((int)IRQnx);
}

void soft_reset(void)
{
    SYSCTRL_RST_EN |= 0x01;
    SYSCTRL_RESET = 0x55;
    while (1);
}
