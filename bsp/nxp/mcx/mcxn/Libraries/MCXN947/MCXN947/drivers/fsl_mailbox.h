/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_MAILBOX_H_
#define FSL_MAILBOX_H_

#include "fsl_common.h"

/*!
 * @addtogroup mailbox
 * @{
 */

/*! @file */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mailbox"
#endif

/*! @name Driver version */
/*! @{ */
/*! @brief MAILBOX driver version 2.3.0. */
#define FSL_MAILBOX_DRIVER_VERSION (MAKE_VERSION(2, 3, 2))
/*! @} */

/*!
 * @brief CPU ID.
 */
#if (defined(LPC55S69_cm33_core0_SERIES) || defined(LPC55S69_cm33_core1_SERIES) || \
     defined(LPC55S66_cm33_core0_SERIES) || defined(LPC55S66_cm33_core1_SERIES))
typedef enum _mailbox_cpu_id
{
    kMAILBOX_CM33_Core1 = 0,
    kMAILBOX_CM33_Core0
} mailbox_cpu_id_t;
#elif ((defined(LPC54114_cm4_SERIES) || defined(LPC54114_cm0plus_SERIES)))
typedef enum _mailbox_cpu_id
{
    kMAILBOX_CM0Plus = 0,
    kMAILBOX_CM4
} mailbox_cpu_id_t;
#elif (defined(MCXN947_cm33_core0_SERIES) || defined(MCXN947_cm33_core1_SERIES) || \
       defined(MCXN946_cm33_core0_SERIES) || defined(MCXN946_cm33_core1_SERIES) || \
       defined(MCXN547_cm33_core0_SERIES) || defined(MCXN547_cm33_core1_SERIES) || \
       defined(MCXN546_cm33_core0_SERIES) || defined(MCXN546_cm33_core1_SERIES))
typedef enum _mailbox_cpu_id
{
    kMAILBOX_CM33_Core0 = 0,
    kMAILBOX_CM33_Core1
} mailbox_cpu_id_t;
#endif

#if (defined(CPU_NXH2004J640UK48))
typedef enum _mailbox_id
{
    kMAILBOX_CM0Plus_Core0 = 0,
    kMAILBOX_CM0Plus_Core1,
    kMAILBOX_CM0Plus_Sw_Irq0,
    kMAILBOX_CM0Plus_Sw_Irq1,
    kMAILBOX_CM0Plus_Sw_Irq2,
    kMAILBOX_CM0Plus_Sw_Irq3
} mailbox_id_t;
#endif
/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @name MAILBOX initialization
 * @{
 */

/*!
 * @brief Initializes the MAILBOX module.
 *
 * This function enables the MAILBOX clock only.
 *
 * @param base MAILBOX peripheral base address.
 */
static inline void MAILBOX_Init(MAILBOX_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(kCLOCK_Mailbox);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#if !(defined(FSL_FEATURE_MAILBOX_HAS_NO_RESET) && FSL_FEATURE_MAILBOX_HAS_NO_RESET)
    /* Reset the MAILBOX module */
    RESET_PeripheralReset(kMAILBOX_RST_SHIFT_RSTn);
#endif
}

/*!
 * @brief De-initializes the MAILBOX module.
 *
 * This function disables the MAILBOX clock only.
 *
 * @param base MAILBOX peripheral base address.
 */
static inline void MAILBOX_Deinit(MAILBOX_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(kCLOCK_Mailbox);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*! @} */

#if ((defined(LPC55S69_cm33_core0_SERIES) || defined(LPC55S69_cm33_core1_SERIES)) || \
     defined(LPC55S66_cm33_core0_SERIES) || defined(LPC55S66_cm33_core1_SERIES) || \
     defined(MCXN947_cm33_core0_SERIES) || defined(MCXN947_cm33_core1_SERIES) || \
     defined(MCXN946_cm33_core0_SERIES) || defined(MCXN946_cm33_core1_SERIES) || \
     defined(MCXN547_cm33_core0_SERIES) || defined(MCXN547_cm33_core1_SERIES) || \
     defined(MCXN546_cm33_core0_SERIES) || defined(MCXN546_cm33_core1_SERIES) || \
     defined(LPC54114_cm4_SERIES) || defined(LPC54114_cm0plus_SERIES))
/*!
 * @brief Set data value in the mailbox based on the CPU ID.
 *
 * @param base MAILBOX peripheral base address.
 * @param cpu_id CPU id, kMAILBOX_CM0Plus or kMAILBOX_CM4 for LPC5410x and LPC5411x devices,
 *               kMAILBOX_CM33_Core0 or kMAILBOX_CM33_Core1 for LPC55S69 devices.
 * @param mboxData Data to send in the mailbox.
 *
 * @note Sets a data value to send via the MAILBOX to the other core.
 */
static inline void MAILBOX_SetValue(MAILBOX_Type *base, mailbox_cpu_id_t cpu_id, uint32_t mboxData)
{
#if ((defined(LPC55S69_cm33_core0_SERIES) || defined(LPC55S69_cm33_core1_SERIES)) || \
     defined(LPC55S66_cm33_core0_SERIES) || defined(LPC55S66_cm33_core1_SERIES) || \
     defined(MCXN947_cm33_core0_SERIES) || defined(MCXN947_cm33_core1_SERIES) || \
     defined(MCXN946_cm33_core0_SERIES) || defined(MCXN946_cm33_core1_SERIES) || \
     defined(MCXN547_cm33_core0_SERIES) || defined(MCXN547_cm33_core1_SERIES) || \
     defined(MCXN546_cm33_core0_SERIES) || defined(MCXN546_cm33_core1_SERIES))
    assert((cpu_id == kMAILBOX_CM33_Core0) || (cpu_id == kMAILBOX_CM33_Core1));
#elif ((defined(LPC54114_cm4_SERIES) || defined(LPC54114_cm0plus_SERIES)))
    assert((cpu_id == kMAILBOX_CM0Plus) || (cpu_id == kMAILBOX_CM4));
#endif
    base->MBOXIRQ[cpu_id].IRQ = mboxData;
}

/*!
 * @brief Get data in the mailbox based on the CPU ID.
 *
 * @param base MAILBOX peripheral base address.
 * @param cpu_id CPU id, kMAILBOX_CM0Plus or kMAILBOX_CM4 for LPC5410x and LPC5411x devices,
 *               kMAILBOX_CM33_Core0 or kMAILBOX_CM33_Core1 for LPC55S69 devices.
 *
 * @return Current mailbox data.
 */
static inline uint32_t MAILBOX_GetValue(MAILBOX_Type *base, mailbox_cpu_id_t cpu_id)
{
#if ((defined(LPC55S69_cm33_core0_SERIES) || defined(LPC55S69_cm33_core1_SERIES)) || \
     defined(LPC55S66_cm33_core0_SERIES) || defined(LPC55S66_cm33_core1_SERIES) || \
     defined(MCXN947_cm33_core0_SERIES) || defined(MCXN947_cm33_core1_SERIES) || \
     defined(MCXN946_cm33_core0_SERIES) || defined(MCXN946_cm33_core1_SERIES) || \
     defined(MCXN547_cm33_core0_SERIES) || defined(MCXN547_cm33_core1_SERIES) || \
     defined(MCXN546_cm33_core0_SERIES) || defined(MCXN546_cm33_core1_SERIES))
    assert((cpu_id == kMAILBOX_CM33_Core0) || (cpu_id == kMAILBOX_CM33_Core1));
#elif ((defined(LPC54114_cm4_SERIES) || defined(LPC54114_cm0plus_SERIES)))
    assert((cpu_id == kMAILBOX_CM0Plus) || (cpu_id == kMAILBOX_CM4));
#endif
    return base->MBOXIRQ[cpu_id].IRQ;
}

/*!
 * @brief Set data bits in the mailbox based on the CPU ID.
 *
 * @param base MAILBOX peripheral base address.
 * @param cpu_id CPU id, kMAILBOX_CM0Plus or kMAILBOX_CM4 for LPC5410x and LPC5411x devices,
 *               kMAILBOX_CM33_Core0 or kMAILBOX_CM33_Core1 for LPC55S69 devices.
 * @param mboxSetBits Data bits to set in the mailbox.
 *
 * @note Sets data bits to send via the MAILBOX to the other core. A value of 0 will
 * do nothing. Only sets bits selected with a 1 in it's bit position.
 */
static inline void MAILBOX_SetValueBits(MAILBOX_Type *base, mailbox_cpu_id_t cpu_id, uint32_t mboxSetBits)
{
#if ((defined(LPC55S69_cm33_core0_SERIES) || defined(LPC55S69_cm33_core1_SERIES)) || \
     defined(LPC55S66_cm33_core0_SERIES) || defined(LPC55S66_cm33_core1_SERIES) || \
     defined(MCXN947_cm33_core0_SERIES) || defined(MCXN947_cm33_core1_SERIES) || \
     defined(MCXN946_cm33_core0_SERIES) || defined(MCXN946_cm33_core1_SERIES) || \
     defined(MCXN547_cm33_core0_SERIES) || defined(MCXN547_cm33_core1_SERIES) || \
     defined(MCXN546_cm33_core0_SERIES) || defined(MCXN546_cm33_core1_SERIES))
    assert((cpu_id == kMAILBOX_CM33_Core0) || (cpu_id == kMAILBOX_CM33_Core1));
#elif ((defined(LPC54114_cm4_SERIES) || defined(LPC54114_cm0plus_SERIES)))
    assert((cpu_id == kMAILBOX_CM0Plus) || (cpu_id == kMAILBOX_CM4));
#endif
    base->MBOXIRQ[cpu_id].IRQSET = mboxSetBits;
}

/*!
 * @brief Clear data bits in the mailbox based on the CPU ID.
 *
 * @param base MAILBOX peripheral base address.
 * @param cpu_id CPU id, kMAILBOX_CM0Plus or kMAILBOX_CM4 for LPC5410x and LPC5411x devices,
 *               kMAILBOX_CM33_Core0 or kMAILBOX_CM33_Core1 for LPC55S69 devices.
 * @param mboxClrBits Data bits to clear in the mailbox.
 *
 * @note Clear data bits to send via the MAILBOX to the other core. A value of 0 will
 * do nothing. Only clears bits selected with a 1 in it's bit position.
 */
static inline void MAILBOX_ClearValueBits(MAILBOX_Type *base, mailbox_cpu_id_t cpu_id, uint32_t mboxClrBits)
{
#if ((defined(LPC55S69_cm33_core0_SERIES) || defined(LPC55S69_cm33_core1_SERIES)) || \
     defined(LPC55S66_cm33_core0_SERIES) || defined(LPC55S66_cm33_core1_SERIES) || \
     defined(MCXN947_cm33_core0_SERIES) || defined(MCXN947_cm33_core1_SERIES) || \
     defined(MCXN946_cm33_core0_SERIES) || defined(MCXN946_cm33_core1_SERIES) || \
     defined(MCXN547_cm33_core0_SERIES) || defined(MCXN547_cm33_core1_SERIES) || \
     defined(MCXN546_cm33_core0_SERIES) || defined(MCXN546_cm33_core1_SERIES))
    assert((cpu_id == kMAILBOX_CM33_Core0) || (cpu_id == kMAILBOX_CM33_Core1));
#elif ((defined(LPC54114_cm4_SERIES) || defined(LPC54114_cm0plus_SERIES)))
    assert((cpu_id == kMAILBOX_CM0Plus) || (cpu_id == kMAILBOX_CM4));
#endif
    base->MBOXIRQ[cpu_id].IRQCLR = mboxClrBits;
}

#elif (defined(CPU_NXH2004J640UK48))

/*!
 * @brief Set data value in the mailbox based on the Mailbox ID.
 *
 * @param base MAILBOX peripheral base address.
 * @param id Mailbox Index for NXH2004 devices
 * @param mboxData Data to send in the mailbox.
 *
 */
static inline void MAILBOX_SetValue(MAILBOX_Type *base, mailbox_id_t id, uint32_t mboxData)
{
    assert((id >= kMAILBOX_CM0Plus_Core0) && (id <= kMAILBOX_CM0Plus_Sw_Irq3));
    base->MBOXIRQ[id].IRQ = mboxData;
}

/*!
 * @brief Get data in the mailbox based on the Mailbox ID.
 *
 * @param base MAILBOX peripheral base address.
 * @param id, Mailbox index for NXH2004 devies.
 *
 * @return Current mailbox data.
 */
static inline uint32_t MAILBOX_GetValue(MAILBOX_Type *base, mailbox_id_t id)
{
    assert((id >= kMAILBOX_CM0Plus_Core0) && (id <= kMAILBOX_CM0Plus_Sw_Irq3));
    return base->MBOXIRQ[id].IRQ;
}

/*!
 * @brief Set data bits in the mailbox based on the Mailbox Index.
 *
 * @param base MAILBOX peripheral base address.
 * @param id Mailbox Index for NXH2004 devices
 * @param mboxSetBits Data bits to set in the mailbox.
 *
 * @note Sets data bits to send via the MAILBOX. A value of 0 will
 * do nothing. Only sets bits selected with a 1 in it's bit position.
 */
static inline void MAILBOX_SetValueBits(MAILBOX_Type *base, mailbox_id_t id, uint32_t mboxSetBits)
{
    assert((id >= kMAILBOX_CM0Plus_Core0) && (id <= kMAILBOX_CM0Plus_Sw_Irq3));
    base->MBOXIRQ[id].IRQSET = mboxSetBits;
}

/*!
 * @brief Clear data bits in the mailbox based on the Mailbox ID.
 *
 * @param base MAILBOX peripheral base address.
 * @param id, Index to Mailbox for NXH2004 devices.
 * @param mboxClrBits Data bits to clear in the mailbox.
 *
 * @note Clear data bits to send via the MAILBOX. A value of 0 will do
 * nothing. Only clears bits selected with a 1 in it's bit position.
 */
static inline void MAILBOX_ClearValueBits(MAILBOX_Type *base, mailbox_id_t id, uint32_t mboxClrBits)
{
    assert((id >= kMAILBOX_CM0Plus_Core0) && (id <= kMAILBOX_CM0Plus_Sw_Irq3));
    base->MBOXIRQ[id].IRQCLR = mboxClrBits;
}

#endif /*CPU_NXH2004J640UK48*/

/*!
 * @brief Get MUTEX state and lock mutex
 *
 * @param base MAILBOX peripheral base address.
 *
 * @return See note
 *
 * @note Returns '1' if the mutex was taken or '0' if another resources has the
 * mutex locked. Once a mutex is taken, it can be returned with the MAILBOX_SetMutex()
 * function.
 */
static inline uint32_t MAILBOX_GetMutex(MAILBOX_Type *base)
{
    return (base->MUTEX & MAILBOX_MUTEX_EX_MASK);
}

/*!
 * @brief Set MUTEX state
 *
 * @param base MAILBOX peripheral base address.
 *
 * @note Sets mutex state to '1' and allows other resources to get the mutex.
 */
static inline void MAILBOX_SetMutex(MAILBOX_Type *base)
{
    base->MUTEX = MAILBOX_MUTEX_EX_MASK;
}

#if defined(__cplusplus)
}
#endif /*_cplusplus*/
/*! @} */

#endif /* FSL_MAILBOX_H_ */
