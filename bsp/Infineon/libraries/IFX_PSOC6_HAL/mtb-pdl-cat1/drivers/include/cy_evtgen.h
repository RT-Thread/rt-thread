/***************************************************************************//**
* \file cy_evtgen.h
* \version 1.0
*
* Provides the API declarations of the Event generator driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2022 Cypress Semiconductor Corporation
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

/**
* \addtogroup group_evtgen
* \{
* This driver provides API functions to configure and use the Event Generator.
*
* The functions and other declarations used in this driver are in cy_evtgen.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
********************************************************************************
* \section group_evtgen_glossary Glossary
********************************************************************************
* * Structure or Comparator Structure - is the main instance of the Event
*   Generator that set of two comparators.
* * Comparator - it is a sub-module of Structures for saving value to compare.
*
********************************************************************************
* \section group_evtgen_solution EVTGEN Solution
********************************************************************************
* The Event Generator (EVTGEN) implements event generation - in Active mode,
* for interrupts and triggers and in Deep Sleep mode only for interrupts. The
* Active functionality interrupt is connected to the CPU interrupt controller.
* Active mode triggered events can be used to trigger a specific device functionality
* mode (for example, execution of an interrupt handler, a SAR ADC conversion,
* and so on) in Active power mode. The Deep Sleep functionality interrupts can
* be used to wake up the CPU from the Deep Sleep power mode. The event generator
* includes a single counter and a maximum of 16 comparator structures for each
* Active and Deep Sleep mode. EVTGEN reduces CPU involvement and thus overall
* power consumption and jitters.
* \image html evtgen_architecture.png
*
* EVTGEN consists of two blocks: Active and Deep Sleep mode blocks.
* There are 16 comparator structures and one 32-bit counter for each of the
* modes which increment with each cycle CLK_REF. Each comparator structure has
* an Active and a Deep Sleep comparator. A comparator compares a programmed
* comparator value with the current counter value. When the counter value
* "passes" (equal) a comparator value, a comparator output is activated.
* \image html evtgen_clock_structure.png
* The Event Generator implements synchronization between the Active counter
* and Deep Sleep counter through ratio control. The ratio value shows the number
* of clk_ref_div periods in one clk_lf periods. Event Generator uses Ratio value
* to synchronize active counter and Deep Sleep counter with hardware
* automatically.
*
********************************************************************************
* \section group_evtgen_configuration Configuration Considerations
********************************************************************************
* The EVTGEN driver configuration can be divided into a number of sequential
* steps:
* * \ref group_scb_evtgen_config
* * \ref group_scb_evtgen_clock
* * \ref group_scb_evtgen_intr
* * \ref group_scb_evtgen_enable
* * \ref group_scb_evtgen_comp_struct_config
*
* \note
* The EVTGEN driver is built on top of the EVTGEN hardware block. The EVTGEN0
* instance is used as an example for all code snippets. Modify the code to match
* your design.
*
********************************************************************************
* \subsection group_scb_evtgen_config Configure EVTGEN
********************************************************************************
* To set up the EVTGEN driver, provide the configuration parameters in the
* \ref cy_stc_evtgen_config_t structure. To initialize the driver, call the
* \ref Cy_EvtGen_Init function providing a pointer to the populated
* \ref cy_stc_evtgen_config_t structure.
*
* \snippet evtgen/snippet/main.c EVTGEN_CFG
*
********************************************************************************
* \subsection group_scb_evtgen_clock Enable Clock Path
********************************************************************************
* A clock source must be connected to the EVTGEN block to control time. Enable
* High Frequency clock. Use the \ref group_sysclk driver API to do.
*
* \snippet evtgen/snippet/main.c EVTGEN_CFG_ASSIGN_CLOCK
*
********************************************************************************
* \subsection group_scb_evtgen_comp_struct_config Configure Comparator Structure
********************************************************************************
* To set up the Comparator Structure of the EVTGEN driver, provide the
* configuration parameters in the \ref cy_stc_evtgen_struct_config_t structure.
* To initialize the Comparator Structure, call the \ref Cy_EvtGen_InitStruct
* function providing a pointer to the populated
* \ref cy_stc_evtgen_struct_config_t structure.
*
* \snippet evtgen/snippet/main.c EVTGEN_CFG_COMP_STRUCT
*
********************************************************************************
* \subsection group_scb_evtgen_intr Configure Interrupt
********************************************************************************
* The interrupt is the main operation of EVTGEN. Use it to configure an
* interrupt and create the interrupt handle for the selected EVTGEN instance.
* Also, enable this interrupt in the NVIC.
*
* \snippet evtgen/snippet/main.c EVTGEN_INTR_A
* \snippet evtgen/snippet/main.c EVTGEN_INTR_B
*
********************************************************************************
* \subsection group_scb_evtgen_enable Enable EVTGEN
********************************************************************************
* Finally, enable the EVTGEN operation by calling \ref Cy_EvtGen_Enable.
*
* \snippet evtgen/snippet/main.c EVTGEN_ENABLE
*
* \section group_evtgen_changelog Changelog
*
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
*
* \defgroup group_evtgen_macros Macro
* \defgroup group_evtgen_functions Functions
* \defgroup group_evtgen_data_structures Data structures
* \defgroup group_evtgen_enums Enumerated types
*/

#if !defined(CY_EVTGEN_H)
#define CY_EVTGEN_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "cy_syslib.h"
#include "cy_utils.h"
#include "cy_device_headers.h"

#ifdef CY_IP_MXEVTGEN

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
* Macro definitions
***************************************/
/**
* \addtogroup group_evtgen_macros
* \{
*/

/** Driver major version */
#define CY_EVTGEN_DRV_VERSION_MAJOR       1

/** Driver minor version */
#define CY_EVTGEN_DRV_VERSION_MINOR       0

/** EVTGEN driver identifier */
#define CY_EVTGEN_ID                      (CY_PDL_DRV_ID(0x4AU))

/** EVTGEN driver struct number mask */
#define CY_EVTGEN_STRUCTNUM_MASK          0xFU

/** \cond */
/******************************************************************************
 * Local definitions
*******************************************************************************/
/* Macros for conditions used by CY_ASSERT calls */
#define CY_EVTGEN_IS_STRUCTNUM_VALID(structNum) ((structNum) < EVTGEN_COMP_STRUCT_NR)
#define CY_EVTGEN_IS_MASK_VALID(mask) (0UL == ((mask) & ((uint32_t) ~EVTGEN_INTR_COMP0_Msk)))
#define CY_EVTGEN_IS_BASE_VALID(base) ((base) != NULL)
#define CY_EVTGEN_IS_DIVIDER_VALID_RANGE(divider) ((divider < 255UL) && (divider > 0UL))
/** \endcond */

/** \} group_evtgen_macros */

/**
* \addtogroup group_evtgen_enums
* \{
*/

/**
* Specifies return values meaning
*/

/** This enum has the return values of the Event generator driver */
typedef enum
{
    CY_EVTGEN_SUCCESS    = 0UL,
    CY_EVTGEN_BAD_PARAM,
} cy_en_evtgen_status_t;

/**
* Returns the state of the Active Counter in the function Cy_EvtGen_GetCounterStatus.
*/
typedef enum
{
    CY_EVTGEN_COUNTER_STATUS_INVALID = 0UL,
    CY_EVTGEN_COUNTER_STATUS_VALID   = 1UL,
} cy_en_evtgen_counter_status_t;

/**
* Ratio Value Dynamic Mode.
* Ratio calculation is based on a weighted average operation.
* This enum has the setting weight for calculation.
*
* \note Small weights coefficients respond more quickly to changes in the number of
* clk_ref_div cycles per clk_lf cycle than larger weights coefficients. Use the small
* dynamic ratio values in the cause low-precision of the low-frequency clock or in
* difficult operating conditions (eg high temperature).
*/
typedef enum
{
    CY_EVTGEN_RATIO_DYNAMIC_MODE0    = 0UL,    /**< new RATIO value = (RATIO + measurement + 1) / 2. */
    CY_EVTGEN_RATIO_DYNAMIC_MODE1    = 1UL,    /**< new RATIO value = (3*RATIO + measurement + 2) / 4. */
    CY_EVTGEN_RATIO_DYNAMIC_MODE2    = 2UL,    /**< new RATIO value = (7*RATIO + measurement + 4) / 8. */
    CY_EVTGEN_RATIO_DYNAMIC_MODE3    = 3UL,    /**< new RATIO value = (15*RATIO + measurement + 8) / 16. */
    CY_EVTGEN_RATIO_DYNAMIC_MODE4    = 4UL,    /**< new RATIO value = (31*RATIO + measurement + 16) / 32. */
    CY_EVTGEN_RATIO_DYNAMIC_MODE5    = 5UL,    /**< new RATIO value = (63*RATIO + measurement + 32) / 64. */
    CY_EVTGEN_RATIO_DYNAMIC_MODE6    = 6UL,    /**< new RATIO value = (127*RATIO + measurement + 64) / 128. */
    CY_EVTGEN_RATIO_DYNAMIC_MODE7    = 7UL,    /**< new RATIO value = (255*RATIO + measurement + 128) / 256. */
} cy_en_evtgen_ratio_dynamic_mode_t;

/**
* Set Ratio Control Mode
*/
typedef enum
{
    CY_EVTGEN_RATIO_CONTROL_SW    = 0UL,    /**< The ratio value is static and calculated during the initialization of the
                                            Event Generator. */
    CY_EVTGEN_RATIO_CONTROL_HW    = 1UL,    /**< Autocalibration continuously measures the number of clk_ref_div cycles
                                             per clk_lf cycle and combines this new measurement with the current
                                             RATIO value to calculate the new RATIO value. */
} cy_en_evtgen_ratio_control_t;

/**
* Set Trigger Mode
*/
typedef enum
{
    CY_EVTGEN_LEVEL_SENSITIVE    = 0UL,
    CY_EVTGEN_EDGE_SENSITIVE,
} cy_en_evtgen_struct_trigger_t;

/**
* Set Work Mode of Comparator Structure
*/
typedef enum
{
    CY_EVTGEN_ACTIVE_FUNCTIONALITY    = 0UL,
    CY_EVTGEN_DEEPSLEEP_FUNCTIONALITY,
} cy_en_evtgen_struct_functionality_t;

/** \} group_evtgen_enums */

/***************************************
* Data Structure definitions
***************************************/

/**
* \addtogroup group_evtgen_data_structures
* \{
*/

/**
* Configuration structure to set up the entire EVTGEN to be used with \ref Cy_EvtGen_Init.
*/
typedef struct
{
    uint32_t frequencyRef;                                      /**< Set clock source frequency in Active power mode. */
    uint32_t frequencyLf;                                       /**< Set clock source frequency in DeepSleep power mode. */
    uint32_t frequencyTick;                                     /**< Set the EVTGEN customized period.  */
    cy_en_evtgen_ratio_control_t ratioControlMode;              /**< Set the ratio control mode. */
    cy_en_evtgen_ratio_dynamic_mode_t ratioValueDynamicMode;    /**< Set the specific dynamic mode. Use only during
                                                                     CY_EVTGEN_RATIO_CONTROL_HW */
}cy_stc_evtgen_config_t;

typedef void (* cy_evtgen_handler)(void);   /**< Type of ISR callbacks */

/**
* Configuration structure to set up the comparator structure of the EVTGEN to be used with
* \ref Cy_EvtGen_InitStruct.
*/
typedef struct
{
    cy_en_evtgen_struct_functionality_t functionalitySelection;    /**< Functionality comparator structure */
    cy_en_evtgen_struct_trigger_t triggerOutEdge;                  /**< Condition for start trigger/interrupt */
    uint32_t valueActiveComparator;                                /**< Value is used for making period of interrupts/triggers */
    uint32_t valueDeepSleepComparator;                             /**< Value is used for making period of deepsleep_interrupts */
}cy_stc_evtgen_struct_config_t;

/** \} group_evtgen_data_structures */


/***************************************
* Function Prototypes
***************************************/

/**
* \addtogroup group_evtgen_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_EvtGen_Enable
****************************************************************************//**
*
* Enable the Event Generator.
*
* \param base
* Pointer to structure describing registers
*
* \note
* Check the ratio status \ref Cy_EvtGen_GetRatioStatus after enabling the
* Event Generator during hardware control ratio. Set a valid value takes to 625
* microseconds.
*
*******************************************************************************/
__STATIC_INLINE void Cy_EvtGen_Enable(EVTGEN_Type *base)
{
    base->CTL |= EVTGEN_CTL_ENABLED_Msk;
}

/*******************************************************************************
* Function Name: Cy_EvtGen_Disable
****************************************************************************//**
*
* Disable event generator
*
* \param base
* Pointer to structure describing registers
*
*******************************************************************************/
__STATIC_INLINE void Cy_EvtGen_Disable(EVTGEN_Type *base)
{
    base->CTL = 0UL;
}


/*******************************************************************************
* Function Name: Cy_EvtGen_SetStructInterrupt
****************************************************************************//**
*
* Set interrupt factor of corresponding structure
*
* \param base
* Pointer to structure describing registers
*
* \param structNumber
* Number of structure. The interrupt factor of that is to be set.
* Valid range from 0 to 15.
*
*******************************************************************************/
__STATIC_INLINE void Cy_EvtGen_SetStructInterrupt(EVTGEN_Type *base, uint8_t structNumber)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNumber));
    base->INTR_SET = _VAL2FLD(EVTGEN_INTR_SET_COMP0, 1UL << (structNumber & CY_EVTGEN_STRUCTNUM_MASK));
}


/*******************************************************************************
* Function Name: Cy_EvtGen_ClearInterrupt
****************************************************************************//**
*
* Clear the interrupt factor
*
* \param base
* Pointer to structure describing registers
*
* \param mask
* Each bit of this parameter corresponds to each structure factor to be clear
*
*******************************************************************************/
__STATIC_INLINE void Cy_EvtGen_ClearInterrupt(EVTGEN_Type *base, uint32_t mask)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_MASK_VALID(mask));
    CY_SET_REG32(&base->INTR, mask);
    /* Readback for the value to take effect */
    (void) base->INTR;
}


/*******************************************************************************
* Function Name: Cy_EvtGen_ClearStructInterrupt
****************************************************************************//**
*
* Clear interrupt factor of corresponding structure
*
* \param base
* Pointer to structure describing registers
*
* \param structNumber
* Number of structure. The factor of that is to be clear.
* Valid range from 0 to 15.
*
*******************************************************************************/
__STATIC_INLINE void Cy_EvtGen_ClearStructInterrupt(EVTGEN_Type *base, uint8_t structNumber)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNumber));
    base->INTR = EVTGEN_INTR_COMP0_Msk & (1UL << structNumber);
    /* Readback for the value to take effect */
    (void) base->INTR;
}


/*******************************************************************************
* Function Name: Cy_EvtGen_SetStructInterruptMask
****************************************************************************//**
*
* Set interrupt mask bit of a corresponding structure
*
* \param base
* Pointer to structure describing registers
*
* \param structNumber
* Number of structure. The mask bit of that is to be set.
* Valid range from 0 to 15.
*
*******************************************************************************/
__STATIC_INLINE void Cy_EvtGen_SetStructInterruptMask(EVTGEN_Type *base, uint8_t structNumber)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNumber));
    base->INTR_MASK |= EVTGEN_INTR_MASK_COMP0_Msk & (1UL << structNumber);
}


/*******************************************************************************
* Function Name: Cy_EvtGen_GetStructInterrupt
****************************************************************************//**
*
*  Get interrupt bit of corresponding structure
*
* \param base
* Pointer to structure describing registers
*
* \param structNumber
* Number of structure. The interrupt factor of the structure is to be returned.
* Valid range from 0 to 15.
*
* \return
* The interrupt bit
*
*******************************************************************************/
__STATIC_INLINE bool Cy_EvtGen_GetStructInterrupt(EVTGEN_Type *base, uint8_t structNumber)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNumber));
    return _FLD2BOOL(EVTGEN_INTR_COMP0, (base->INTR & (1UL << structNumber)));
}


/*******************************************************************************
* Function Name: Cy_EvtGen_GetStructInterruptMasked
****************************************************************************//**
*
* Get interrupt masked bit of corresponding structure
*
* \param base
* Pointer to structure describing registers
*
* \param structNumber
* Number of structure. The masked bit of the structure is to be returned.
* Valid range from 0 to 15.
*
* \return
* The interrupt masked bit
*
*******************************************************************************/
__STATIC_INLINE bool Cy_EvtGen_GetStructInterruptMasked(EVTGEN_Type *base, uint8_t structNumber)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNumber));
    return _FLD2BOOL(EVTGEN_INTR_MASKED_COMP0, (base->INTR_MASKED & (1UL << structNumber)));
}


/*******************************************************************************
* Function Name: Cy_EvtGen_SetStructInterruptDeepSleep
****************************************************************************//**
*
* Set deep sleep interrupt factor of corresponding structure
*
* \param base
* Pointer to structure describing registers
*
* \param structNumber
* Number of structure. The interrupt factor of that is to be set.
* Valid range from 0 to 15.
*
*******************************************************************************/
__STATIC_INLINE void Cy_EvtGen_SetStructInterruptDeepSleep(EVTGEN_Type *base, uint8_t structNumber)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNumber));
    base->INTR_DPSLP_SET = _VAL2FLD(EVTGEN_INTR_DPSLP_SET_COMP1, 1UL << structNumber);
}


/*******************************************************************************
* Function Name: Cy_EvtGen_ClearInterruptDeepSleep
****************************************************************************//**
*
* Clear the deep sleep interrupt factor
*
* \param base
* Pointer to structure describing registers
*
* \param mask
* Each bit of this parameter corresponds to each structure factor to be clear.
*
*******************************************************************************/
__STATIC_INLINE void Cy_EvtGen_ClearInterruptDeepSleep(EVTGEN_Type *base, uint32_t mask)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_MASK_VALID(mask));
    base->INTR_DPSLP = _VAL2FLD(EVTGEN_INTR_DPSLP_COMP1, mask);
    /* Readback for the value to take effect */
    (void) base->INTR_DPSLP;
}


/*******************************************************************************
* Function Name: Cy_EvtGen_ClearStructInterruptDeepSleep
****************************************************************************//**
*
* Clear deep sleep interrupt factor of corresponding structure
*
* \param base
* Pointer to structure describing registers
*
* \param structNumber
* Number of structure. The factor of that is to be clear.
* Valid range from 0 to 15.
*
*******************************************************************************/
__STATIC_INLINE void Cy_EvtGen_ClearStructInterruptDeepSleep(EVTGEN_Type *base, uint8_t structNumber)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNumber));
    base->INTR_DPSLP = _VAL2FLD(EVTGEN_INTR_DPSLP_COMP1, (1UL << structNumber));
    /* Readback for the value to take effect */
    (void) base->INTR_DPSLP;
}


/*******************************************************************************
* Function Name: Cy_EvtGen_SetStructInterruptDeepSleepMask
****************************************************************************//**
*
* Set deep sleep interrupt mask bit of a corresponding structure
*
* \param base
* Pointer to structure describing registers
*
* \param structNumber
* Number of structure. The deep sleep mask bit of that is to be set.
* Valid range from 0 to 15.
*
*******************************************************************************/
__STATIC_INLINE void Cy_EvtGen_SetStructInterruptDeepSleepMask(EVTGEN_Type *base, uint8_t structNumber)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNumber));
    base->INTR_DPSLP_MASK |= EVTGEN_INTR_DPSLP_MASK_COMP1_Msk & (1UL << structNumber);
}


/*******************************************************************************
* Function Name: Cy_EvtGen_GetStructInterruptDeepSleep
****************************************************************************//**
*
* Get deep sleep interrupt bit of corresponding structure.
*
* \param base
* Pointer to structure describing registers.
*
* \param structNumber
* Number of structure. The deep sleep interrupt factor of the structure is to be returned.
* Valid range from 0 to 15.
*
* \return
* Returns the interrupt bit.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_EvtGen_GetStructInterruptDeepSleep(EVTGEN_Type *base, uint8_t structNumber)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNumber));
    return _FLD2BOOL(EVTGEN_INTR_DPSLP_COMP1, (base->INTR_DPSLP & (1UL << structNumber)));
}


/*******************************************************************************
* Function Name: Cy_EvtGen_GetStructInterruptDeepSleepMasked
****************************************************************************//**
*
* Get deep sleep interrupt masked bit of corresponding structure.
*
* \param base
* Pointer to structure describing registers.
*
* \param structNumber
* Number of structure. The deep sleep masked bit of the structure is to be returned.
* Valid range from 0 to 15.
*
* \return
* Returns the interrupt masked bit.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_EvtGen_GetStructInterruptDeepSleepMasked(EVTGEN_Type *base, uint8_t structNumber)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNumber));
    return _FLD2BOOL(EVTGEN_INTR_DPSLP_MASKED_COMP1, (base->INTR_DPSLP_MASKED & (1UL << structNumber)));
}


/*******************************************************************************
* Function Name: Cy_EvtGen_GetComp0Status
****************************************************************************//**
*
* Get comparator 0 status.
*
* \param base
* Pointer to structure describing registers.
*
* \return
* Returns comparator 0 Status.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_EvtGen_GetComp0Status(EVTGEN_Type *base)
{
    return (uint32_t) _FLD2VAL(EVTGEN_COMP0_STATUS_COMP0_OUT, base->COMP0_STATUS);
}


/*******************************************************************************
* Function Name: Cy_EvtGen_GetComp1Status
****************************************************************************//**
*
* Get comparator 1 status.
*
* \param base
* Pointer to structure describing registers.
*
* \return
* Returns comparator 1 Status.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_EvtGen_GetComp1Status(EVTGEN_Type *base)
{
    return (uint32_t) _FLD2VAL(EVTGEN_COMP1_STATUS_COMP1_OUT, base->COMP1_STATUS);
}


/*******************************************************************************
* Function Name: Cy_EvtGen_GetCounterStatus
****************************************************************************//**
*
* Get active counter status.
*
* \param base
* Pointer to structure describing registers.
*
* \return
* Returns counter status.
*
* \note
* If this status is CY_EVTGEN_COUNTER_STATUS_VALID, the counter completed initialization
* and is ready to be read.
*
*******************************************************************************/
__STATIC_INLINE cy_en_evtgen_counter_status_t Cy_EvtGen_GetCounterStatus(EVTGEN_Type *base)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_evtgen_counter_status_t enum.');
    return (cy_en_evtgen_counter_status_t)(_FLD2VAL(EVTGEN_COUNTER_STATUS_VALID, base->COUNTER_STATUS));
}



/*******************************************************************************
* Function Name: Cy_EvtGen_GetCounterValue
****************************************************************************//**
*
* Get counter value.
*
* \param base
* Pointer to structure describing registers.
*
* \return
* Returns counter value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_EvtGen_GetCounterValue(EVTGEN_Type *base)
{
    return (_FLD2VAL(EVTGEN_COUNTER_INT32, base->COUNTER));
}

/*******************************************************************************
* Function Name: Cy_EvtGen_GetRatioStatus
****************************************************************************//**
*
* Get status ratio value.
*
* \param base
* Pointer to structure describing registers.
*
* \return
* Returns true if ratio value is valid.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_EvtGen_GetRatioStatus(EVTGEN_Type *base)
{
    return (((_FLD2VAL(EVTGEN_RATIO_CTL_VALID, base->RATIO_CTL)) != 0UL) ? true : false);
}

/*******************************************************************************
* Function Name: Cy_EvtGen_GetCompActiveEnabledStatus
****************************************************************************//**
*
* Get status active struct comparator enable.
*
* \param base
* Pointer to structure describing registers.
*
* \param structNum
* Structure number for status active comparator enable. Valid range from 0 to 15.
*
* \return
* Returns true if status active struct comparator enabled.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_EvtGen_GetCompActiveEnabledStatus(EVTGEN_Type *base, uint8_t structNum)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNum));
    return (((_FLD2VAL(EVTGEN_COMP_STRUCT_COMP_CTL_COMP0_EN, base->COMP_STRUCT[structNum].COMP_CTL)) != 0UL) ? true : false);
}

/*******************************************************************************
* Function Name: Cy_EvtGen_GetCompDeepSleepEnabledStatus
****************************************************************************//**
*
* Get status Deep Sleep struct comparator enable.
*
* \param base
* Pointer to structure describing registers.
*
* \param structNum
* Structure number for status Deep Sleep comparator enable. Valid range from 0 to 15.
*
* \return
* Returns true if status Deep Sleep struct comparator enabled.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_EvtGen_GetCompDeepSleepEnabledStatus(EVTGEN_Type *base, uint8_t structNum)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNum));
    return (((_FLD2VAL(EVTGEN_COMP_STRUCT_COMP_CTL_COMP1_EN, base->COMP_STRUCT[structNum].COMP_CTL)) != 0UL) ? true : false);
}

/*******************************************************************************
* Function Name: Cy_EvtGen_IsCompStructEnabled
****************************************************************************//**
*
* Get status struct comparator enable.
*
* \param base
* Pointer to structure describing registers.
*
* \param structNum
* Structure number for status comparator enable. Valid range from 0 to 15.
*
* \return
* Returns true if status struct comparator enabled.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_EvtGen_IsCompStructEnabled(EVTGEN_Type *base, uint8_t structNum)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNum));
    return (((_FLD2VAL(EVTGEN_COMP_STRUCT_COMP_CTL_ENABLED, base->COMP_STRUCT[structNum].COMP_CTL)) != 0UL) ? true : false);
}

cy_en_evtgen_status_t Cy_EvtGen_Init(EVTGEN_Type *base, const cy_stc_evtgen_config_t* config);
void Cy_EvtGen_DeInit(EVTGEN_Type *base);
cy_en_evtgen_status_t Cy_EvtGen_InitStruct(EVTGEN_Type *base,
                                                        uint8_t structNum,
                                                        const cy_stc_evtgen_struct_config_t* configStruct);
void Cy_EvtGen_DeinitStruct(EVTGEN_Type *base, uint8_t structNum);
void Cy_EvtGen_UpdateActiveCompValue(EVTGEN_Type *base, uint8_t structNum, uint32_t newCompareValue);
void Cy_EvtGen_UpdateDeepSleepCompValue(EVTGEN_Type *base, uint8_t structNum, uint32_t newCompareValue);

/** \} group_evtgen_functions */

#if defined(__cplusplus)
}
#endif

#endif /* #if !defined(CY_EVTGEN_H) */

#endif /* if not defined CY_IP_MXEVTGEN */

/** \} group_ctb */

/* [] END OF FILE */
