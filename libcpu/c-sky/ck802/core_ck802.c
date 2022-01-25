/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-01-01     Urey         first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <stdint.h>
#include <core_ck802.h>

/* flag in interrupt handling */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/*******************************************************************************
 *                Hardware Abstraction Layer
  Core Function Interface contains:
  - Core VIC Functions
  - Core CORET Functions
  - Core Register Access Functions
 ******************************************************************************/
/**
  \defgroup CSI_Core_FunctionInterface Functions and Instructions Reference
*/

/* ##########################   NVIC functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_NVICFunctions NVIC Functions
  \brief    Functions that manage interrupts and exceptions via the NVIC.
  @{
 */

/* Interrupt Priorities are WORD accessible only under CSKYv6M                   */
/* The following MACROS handle generation of the register offset and byte masks */
#define _BIT_SHIFT(IRQn)         (  ((((uint32_t)(int32_t)(IRQn))         )      &  0x03UL) * 8UL)
#define _IP_IDX(IRQn)            (   (((uint32_t)(int32_t)(IRQn))                >>    2UL)      )

static uint32_t s_nvic_prio_bits = __NVIC_PRIO_BITS;

/**
  \brief   initialize the NVIC interrupt controller
  \param [in]      prio_bits  the priority bits of NVIC interrupt controller.
 */
void drv_nvic_init(uint32_t prio_bits)
{
    if (s_nvic_prio_bits >= 8U)
    {
        return;
    }

    s_nvic_prio_bits = prio_bits;
}

/**
  \brief   Enable External Interrupt
  \details Enables a device-specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void drv_nvic_enable_irq(int32_t IRQn)
{
    NVIC->ISER[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
#ifdef CONFIG_SYSTEM_SECURE
    NVIC->ISSR[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
#endif
}

/**
  \brief   Disable External Interrupt
  \details Disables a device-specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void drv_nvic_disable_irq(int32_t IRQn)
{
    NVIC->ICER[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}

/**
  \brief   Enable External Secure Interrupt
  \details Enables a secure device-specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void drv_nvic_enable_sirq(int32_t IRQn)
{
    NVIC->ISSR[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}

/**
  \brief   Get Pending Interrupt
  \details Reads the pending register in the NVIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
 */
uint32_t drv_nvic_get_pending_irq(int32_t IRQn)
{
    return ((uint32_t)(((NVIC->ISPR[0U] & (1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
}

/**
  \brief   Set Pending Interrupt
  \details Sets the pending bit of an external interrupt.
  \param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
void drv_nvic_set_pending_irq(int32_t IRQn)
{
    NVIC->ISPR[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}

/**
  \brief   Clear Pending Interrupt
  \details Clears the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void drv_nvic_clear_pending_irq(int32_t IRQn)
{
    NVIC->ICPR[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}

/**
  \brief   Get Wake up Interrupt
  \details Reads the wake up register in the NVIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt is not set as wake up interrupt.
  \return             1  Interrupt is set as wake up interrupt.
 */
uint32_t drv_nvic_get_wakeup_irq(int32_t IRQn)
{
    return ((uint32_t)(((NVIC->IWER[0U] & (1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
}

/**
  \brief   Set Wake up Interrupt
  \details Sets the wake up bit of an external interrupt.
  \param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
void drv_nvic_set_wakeup_irq(int32_t IRQn)
{
    NVIC->IWER[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}

/**
  \brief   Clear Wake up Interrupt
  \details Clears the wake up bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
void drv_nvic_clear_wakeup_irq(int32_t IRQn)
{
    NVIC->IWDR[0U] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
}

/**
  \brief   Get Active Interrupt
  \details Reads the active register in the NVIC and returns the active bit for the device specific interrupt.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt status is not active.
  \return             1  Interrupt status is active.
  \note    IRQn must not be negative.
 */
uint32_t drv_nvic_get_active(int32_t IRQn)
{
    return ((uint32_t)(((NVIC->IABR[0] & (1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
}

/**
  \brief   Set Threshold register
  \details set the threshold register in the NVIC.
  \param [in]      VectThreshold  specific vecter threshold.
  \param [in]      PrioThreshold  specific priority threshold.
 */
void drv_nvic_set_threshold(uint32_t VectThreshold, uint32_t PrioThreshold)
{
    NVIC->IPTR = 0x80000000 | (((VectThreshold + 32) & 0xFF) << 8) | ((PrioThreshold & 0x3) << 6);
}

/**
  \brief   Set Interrupt Priority
  \details Sets the priority of an interrupt.
  \note    The priority cannot be set for every core interrupt.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
 */
void drv_nvic_set_prio(int32_t IRQn, uint32_t priority)
{
    NVIC->IPR[_IP_IDX(IRQn)]  = ((uint32_t)(NVIC->IPR[_IP_IDX(IRQn)]  & ~(0xFFUL << _BIT_SHIFT(IRQn))) |
                                 (((priority << (8U - s_nvic_prio_bits)) & (uint32_t)0xFFUL) << _BIT_SHIFT(IRQn)));
}

/**
  \brief   Get Interrupt Priority
  \details Reads the priority of an interrupt.
           The interrupt number can be positive to specify an external (device specific) interrupt,
           or negative to specify an internal (core) interrupt.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
uint32_t drv_nvic_get_prio(int32_t IRQn)
{
    return ((uint32_t)(((NVIC->IPR[ _IP_IDX(IRQn)] >> _BIT_SHIFT(IRQn)) & (uint32_t)0xFFUL) >> (8U - s_nvic_prio_bits)));
}


/*@} end of CSI_Core_NVICFunctions */

/* ##################################    SysTick function  ############################################ */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_SysTickFunctions SysTick Functions
  \brief    Functions that configure the System.
  @{
 */


/**
  \brief   CORE timer Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \param [in]  IRQn   core timer Interrupt number.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
uint32_t drv_coret_config(uint32_t ticks, int32_t IRQn)
{
    if ((ticks - 1UL) > CORET_LOAD_RELOAD_Msk)
    {
        return (1UL);                                                   /* Reload value impossible */
    }

    CORET->LOAD  = (uint32_t)(ticks - 1UL);                           /* set reload register */
    drv_nvic_set_prio(IRQn, (1UL << s_nvic_prio_bits) - 1UL);         /* set Priority for Systick Interrupt */
    CORET->VAL   = 0UL;                                               /* Load the CORET Counter Value */
    CORET->CTRL  = CORET_CTRL_CLKSOURCE_Msk |
                   CORET_CTRL_TICKINT_Msk |
                   CORET_CTRL_ENABLE_Msk;                           /* Enable CORET IRQ and CORET Timer */
    return (0UL);                                                     /* Function successful */
}

/**
  \brief   get CORE timer reload value
  \return          CORE timer counter value.
 */
uint32_t drv_coret_get_load(void)
{
    return CORET->LOAD;
}

/**
  \brief   get CORE timer counter value
  \return          CORE timer counter value.
 */
uint32_t drv_coret_get_value(void)
{
    return CORET->VAL;
}

/*@} end of CSI_Core_SysTickFunctions */

#if 0
/* ##################################### DCC function ########################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_core_DebugFunctions HAD Functions
  \brief    Functions that access the HAD debug interface.
  @{
 */

/**
  \brief   HAD Send Character
  \details Transmits a character via the HAD channel 0, and
           \li Just returns when no debugger is connected that has booked the output.
           \li Is blocking when a debugger is connected, but the previous character sent has not been transmitted.
  \param [in]     ch  Character to transmit.
  \returns            Character to transmit.
 */
uint32_t HAD_SendChar(uint32_t ch)
{
    DCC->DERJR = (uint8_t)ch;

    return (ch);
}


/**
  \brief   HAD Receive Character
  \details Inputs a character via the external variable \ref HAD_RxBuffer.
  \return             Received character.
  \return         -1  No character pending.
 */
int32_t HAD_ReceiveChar(void)
{
    int32_t ch = -1;                           /* no character available */

    if (_FLD2VAL(DCC_EHSR_JW, DCC->EHSR))
    {
        ch = DCC->DERJW;
    }

    return (ch);
}

/**
  \brief   HAD Check Character
  \details Checks whether a character is pending for reading in the variable \ref HAD_RxBuffer.
  \return          0  No character available.
  \return          1  Character available.
 */
int32_t HAD_CheckChar(void)
{
    return _FLD2VAL(DCC_EHSR_JW, DCC->EHSR);                              /* no character available */
}

#endif
