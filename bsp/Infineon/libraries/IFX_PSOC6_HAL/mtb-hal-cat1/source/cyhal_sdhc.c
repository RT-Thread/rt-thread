/*******************************************************************************
* File Name: cyhal_sdhc.c
*
* Description:
* Provides a high level interface for interacting with the Infineon SDHC. This
* is a wrapper around the lower level PDL API.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
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

#include <string.h> /* For memcpy */
#include <stdlib.h>
#include <time.h>
#include "cy_pdl.h"
#include "cy_utils.h"
#include "cy_result.h"
#include "cyhal_sdhc.h"
#include "cyhal_sdio.h"
#include "cyhal_gpio.h"
#include "cyhal_clock.h"
#include "cyhal_hwmgr.h"
#include "cyhal_utils.h"
#include "cyhal_irq_impl.h"
#include "cyhal_system.h"
#include "cyhal_syspm.h"

/**
* \addtogroup group_hal_impl_sdhc SDHC (SD Host Controller)
* \ingroup group_hal_impl
* \{
*
* The SHDC HAL implemenation for CAT1 provides implementations for the following weak functions
* specified by the PDL to make their usage in SDHC HAL driver more flexible by providing user ability
* to use card detect, write protect, pwr en, and io select signals on custom pins instead of dedicated
* SDHC block pins
*   - Cy_SD_Host_IsCardConnected
*   - Cy_SD_Host_IsWpSet
*   - Cy_SD_Host_EnableCardVoltage
*   - Cy_SD_Host_DisableCardVoltage
*   - Cy_SD_Host_ChangeIoVoltage
* In order to disable these implementations, the define CYHAL_DISABLE_WEAK_FUNC_IMPL
* (DEFINES+=CYHAL_DISABLE_WEAK_FUNC_IMPL) must be set when building the application.
*
* By default, if the timeout_ms parameter given to \ref cyhal_sdhc_erase function is 0. The SDHC HAL driver
* will check to see if the connected card is emmc. If so, the timeout_ms parameter will be set to 100 milliseconds,
* otherwise it will be set to 1000 milliseconds.
* \} group_hal_impl_sdhc
*/


#if (CYHAL_DRIVER_AVAILABLE_SDHC)

#if defined(__cplusplus)
extern "C"
{
#endif

#define _CYHAL_SDXX_MHZ(x)                              (((uint32_t)(x)) * 1000UL * 1000UL)

#define _CYHAL_SDHC_IRQ_PRIORITY                        (3UL)
#define _CYHAL_SDHC_RW_RETRY_CYCLES                     (1000u)     /* Number of cycles for read/write operation complete */
#define _CYHAL_SDHC_RETRY_TIMES                         (1000UL)    /* The number loops to make the timeout in msec */
#define _CYHAL_SDHC_FUJE_TIMEOUT_MS                     (1000U)     /* The Fuje timeout for one block */
#define _CYHAL_SDHC_RW_TIMEOUT_US                       (500U)      /* The SDHC Read/Write timeout for one block */
#define _CYHAL_SDHC_TRANSFER_TIMEOUT                    (0xCUL)     /* The transfer timeout */
#define _CYHAL_SDHC_EMMC_TRIM_DELAY_MS                  (100U)      /* The EMMC TRIM timeout */
#define _CYHAL_SDIO_ENUMERATION_TIMEOUT_MS              (500U)
#define _CYHAL_SDHC_READ_TIMEOUT_MS                     (100U)      /* The Read timeout for one block. */
#define _CYHAL_SDHC_ALL_ERR_INTERRUPTS                  (CYHAL_SDHC_CMD_TOUT_ERR | CYHAL_SDHC_CMD_CRC_ERR |\
                                                         CYHAL_SDHC_CMD_END_BIT_ERR | CYHAL_SDHC_CMD_IDX_ERR |\
                                                         CYHAL_SDHC_DATA_TOUT_ERR | CYHAL_SDHC_DATA_CRC_ERR |\
                                                         CYHAL_SDHC_DATA_END_BIT_ERR | CYHAL_SDHC_CUR_LMT_ERR |\
                                                         CYHAL_SDHC_AUTO_CMD_ERR | CYHAL_SDHC_ADMA_ERR |\
                                                         CYHAL_SDHC_TUNNING_ERR | CYHAL_SDHC_RESP_ERR |\
                                                         CYHAL_SDHC_BOOT_ACK_ERR)
#define _CYHAL_SDHC_RCA_SHIFT                           (16U)
#define _CYHAL_SDHC_1_8_REG_STABLE_TIME_MS              (30U)       /* The 1.8 voltage regulator stable time. */
#define _CYHAL_SDHC_PWR_RAMP_UP_TIME_MS                 (36U)       /* Time needed for card VDD to achieve operating
                                                                    * supply range level after power on (power on time,
                                                                    * 1 ms + pwr ramp up, max 35 ms) */
#define _CYHAL_SDHC_TOUT_TMCLK_POW_MIN                  (13U)        /* Minimal power of 2 for data timeout counter value */
#define _CYHAL_SDHC_TOUT_TMCLK_POW_MAX                  (27U)        /* Maximal power of 2 for data timeout counter value */
#define _CYHAL_SDHC_EXPECTED_BASE_CLK_FREQ_HZ           (_CYHAL_SDXX_MHZ(100))
                                                                     /* By default SDHC block is expected to be clocked by 100 MHz */

#define _CYHAL_SDHC_EXTCSD_SIZE                         (512U)       /* EMMC EXT_CSD register size in bytes */
#define _CYHAL_SDHC_EMMC_CMD6_TIMEOUT_MULT              (10U)        /* The 10x multiplier of GENERIC_CMD6_TIME[248]. */
#define _CYHAL_SDHC_EXTCSD_GENERIC_CMD6_TIME            (248U)       /* Idx of GENERIC_CMD6_TIME byte in EXT_CSD register */
#define _CYHAL_SDHC_EMMC_MAX_SUP_FREQ_HZ                (_CYHAL_SDXX_MHZ(52))
                                                                    /* Maximal supported frequency for eMMC for current
                                                                     * implementation */

#define _CYHAL_SDIO_RW_TIMEOUT_US                       (5U)        /* The SDIO Read/Write timeout for one block */
#define _CYHAL_SDIO_CMD_CMPLT_DELAY_US                  (5U)        /* The Command complete delay */
#define _CYHAL_SDIO_HOST_CLK_400K                       (400UL * 1000UL)    /* 400 kHz clock frequency */
#define _CYHAL_SDIO_64B_BLOCK                           (64U)


#define _CYHAL_SDIO_SET_ALL_INTERRUPTS_MASK             (0x61FFUL)
#define _CYHAL_SDIO_ALL_INTERRUPTS_ENABLE_MASK          (0x61FFUL)
#define _CYHAL_SDIO_CLEAR_ALL_INTERRUPTS_MASK           (0x0UL)
#define _CYHAL_SDIO_CLEAR_ALL_INTERRUPTS_ENABLE_MASK    (0x0UL)
#define _CYHAL_SDIO_TRANSFER_TRIES                      (50U)

/* Clock frequency which is connected to SDHC divider */
#define _CYHAL_SDIO_CLK_HF_HZ                           (_CYHAL_SDXX_MHZ(100))

/* Macro-function to calculate pin mapping number */
#define _CYHAL_SDHC_ELEM_COUNT(pin_mapping)    (sizeof(pin_mapping)/sizeof(cyhal_resource_pin_mapping_t))

#if (defined(SDHC_CHIP_TOP_DATA8_PRESENT) && (SDHC_CHIP_TOP_DATA8_PRESENT))   || \
    (defined(SDHC0_CHIP_TOP_DATA8_PRESENT) && (SDHC0_CHIP_TOP_DATA8_PRESENT)) || \
    (defined(SDHC1_CHIP_TOP_DATA8_PRESENT) && (SDHC1_CHIP_TOP_DATA8_PRESENT))
    #define _CYHAL_SDHC_DATA8_PRESENT   1
#else
    #define _CYHAL_SDHC_DATA8_PRESENT   0
#endif
#if (defined(SDHC_CHIP_TOP_CARD_DETECT_PRESENT) && (SDHC_CHIP_TOP_CARD_DETECT_PRESENT))   || \
    (defined(SDHC0_CHIP_TOP_CARD_DETECT_PRESENT) && (SDHC0_CHIP_TOP_CARD_DETECT_PRESENT)) || \
    (defined(SDHC1_CHIP_TOP_CARD_DETECT_PRESENT) && (SDHC1_CHIP_TOP_CARD_DETECT_PRESENT))
    #define _CYHAL_SDHC_CARD_DETECT_PRESENT   1
#else
    #define _CYHAL_SDHC_CARD_DETECT_PRESENT   0
#endif
#if (defined(SDHC_CHIP_TOP_CARD_WRITE_PROT_PRESENT) && (SDHC_CHIP_TOP_CARD_WRITE_PROT_PRESENT))   || \
    (defined(SDHC0_CHIP_TOP_CARD_WRITE_PROT_PRESENT) && (SDHC0_CHIP_TOP_CARD_WRITE_PROT_PRESENT)) || \
    (defined(SDHC1_CHIP_TOP_CARD_WRITE_PROT_PRESENT) && (SDHC1_CHIP_TOP_CARD_WRITE_PROT_PRESENT))
    #define _CYHAL_SDHC_CARD_WRITE_PROT_PRESENT   1
#else
    #define _CYHAL_SDHC_CARD_WRITE_PROT_PRESENT   0
#endif
#if (defined(SDHC_CHIP_TOP_LED_CTRL_PRESENT) && (SDHC_CHIP_TOP_LED_CTRL_PRESENT))   || \
    (defined(SDHC0_CHIP_TOP_LED_CTRL_PRESENT) && (SDHC0_CHIP_TOP_LED_CTRL_PRESENT)) || \
    (defined(SDHC1_CHIP_TOP_LED_CTRL_PRESENT) && (SDHC1_CHIP_TOP_LED_CTRL_PRESENT))
    #define _CYHAL_SDHC_LED_CTRL_PRESENT   1
#else
    #define _CYHAL_SDHC_LED_CTRL_PRESENT   0
#endif
#if (defined(SDHC_CHIP_TOP_IO_VOLT_SEL_PRESENT) && (SDHC_CHIP_TOP_IO_VOLT_SEL_PRESENT))   || \
    (defined(SDHC0_CHIP_TOP_IO_VOLT_SEL_PRESENT) && (SDHC0_CHIP_TOP_IO_VOLT_SEL_PRESENT)) || \
    (defined(SDHC1_CHIP_TOP_IO_VOLT_SEL_PRESENT) && (SDHC1_CHIP_TOP_IO_VOLT_SEL_PRESENT))
    #define _CYHAL_SDHC_IO_VOLT_SEL_PRESENT   1
#else
    #define _CYHAL_SDHC_IO_VOLT_SEL_PRESENT   0
#endif
#if (defined(SDHC_CHIP_TOP_CARD_IF_PWR_EN_PRESENT) && (SDHC_CHIP_TOP_CARD_IF_PWR_EN_PRESENT))   || \
    (defined(SDHC0_CHIP_TOP_CARD_IF_PWR_EN_PRESENT) && (SDHC0_CHIP_TOP_CARD_IF_PWR_EN_PRESENT)) || \
    (defined(SDHC1_CHIP_TOP_CARD_IF_PWR_EN_PRESENT) && (SDHC1_CHIP_TOP_CARD_IF_PWR_EN_PRESENT))
    #define _CYHAL_SDHC_CARD_IF_PWR_EN_PRESENT   1
#else
    #define _CYHAL_SDHC_CARD_IF_PWR_EN_PRESENT   0
#endif
#if (defined(SDHC_CHIP_TOP_CARD_EMMC_RESET_PRESENT) && (SDHC_CHIP_TOP_CARD_EMMC_RESET_PRESENT))   || \
    (defined(SDHC0_CHIP_TOP_CARD_EMMC_RESET_PRESENT) && (SDHC0_CHIP_TOP_CARD_EMMC_RESET_PRESENT)) || \
    (defined(SDHC1_CHIP_TOP_CARD_EMMC_RESET_PRESENT) && (SDHC1_CHIP_TOP_CARD_EMMC_RESET_PRESENT))
    #define _CYHAL_SDHC_CARD_EMMC_RESET_PRESENT   1
#else
    #define _CYHAL_SDHC_CARD_EMMC_RESET_PRESENT   0
#endif

/* Mask which indicates interface change */
#define _CYHAL_SDIO_INTERFACE_CHANGE_MASK    ((uint32_t) ((uint32_t) CYHAL_SDIO_GOING_DOWN) | ((uint32_t) CYHAL_SDIO_COMING_UP))
const uint32_t MAX_FREQUENCY = 50000000;

/* List of available SDHC instances */
static SDHC_Type * const _CYHAL_SDHC_BASE_ADDRESSES[CY_IP_MXSDHC_INSTANCES] =
{
#ifdef SDHC0
    SDHC0,
#endif /* ifdef SDHC0 */

#ifdef SDHC1
    SDHC1,
#endif /* ifdef SDHC1 */
};

/* List of available SDHC interrupt sources */
static const _cyhal_system_irq_t _CYHAL_SDHC_IRQ_N[CY_IP_MXSDHC_INSTANCES] =
{
#ifdef SDHC0
    sdhc_0_interrupt_general_IRQn,
#endif /* ifdef SDHC0 */

#ifdef SDHC1
    sdhc_1_interrupt_general_IRQn,
#endif /* ifdef SDHC1 */
};

/* SDHC/SDIO I/O voltage select principle.
*  Internal version of cyhal_sdhc_io_volt_action_type_t and cyhal_sdio_io_volt_action_type_t */
typedef enum
{
    _CYHAL_SDXX_IO_VOLT_ACTION_NEGOTIATE         = 0U,
    _CYHAL_SDXX_IO_VOLT_ACTION_SWITCH_SEQ_ONLY   = 1U,
    _CYHAL_SDXX_IO_VOLT_ACTION_NONE              = 2U,
} _cyhal_sdxx_io_switch_action_t;

/** I/O voltage levels.
 * Internal version of cyhal_sdhc_io_voltage_t and cyhal_sdio_io_voltage_t */
typedef enum
{
    _CYHAL_SDXX_IO_VOLTAGE_3_3V                  = 0U,   //!< I/O voltage is 3.3V.
    _CYHAL_SDXX_IO_VOLTAGE_1_8V                  = 1U    //!< I/O voltage is 1.8V.
} cyhal_sdxx_io_voltage_t;

#if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
#include "cyabs_rtos.h"

typedef enum
{
    /* Semaphore is not initialized */
    _CYHAL_SDXX_SEMA_NOT_INITED,
    /* Semaphore is initialized, but will not be used */
    _CYHAL_SDXX_SEMA_NOT_USED,
    /* Semaphore is initialized and used (expected to be set in IRQ handler) */
    _CYHAL_SDXX_SEMA_USED,
    /* Set in irq handler */
    _CYHAL_SDXX_SEMA_SET
} _cyhal_sdxx_semaphore_status_t;

/* _cyhal_sdxx_t would be the better place for keeping these items, but since
 * cy_semaphore_t depends on cyabs_rtos.h that results in circular includes/
 * messy forward declarations. */
static cy_semaphore_t _cyhal_sdxx_semaphore_xfer_done[CY_IP_MXSDHC_INSTANCES];
static _cyhal_sdxx_semaphore_status_t _cyhal_sdxx_semaphore_status[CY_IP_MXSDHC_INSTANCES];

static inline bool _cyhal_sdxx_is_smfr_ready_for_set(_cyhal_sdxx_t *sdxx)
{
    CY_ASSERT(sdxx != NULL);
    return (_CYHAL_SDXX_SEMA_USED == _cyhal_sdxx_semaphore_status[sdxx->resource.block_num]);
}

static inline bool _cyhal_sdxx_is_smfr_ready_for_get(_cyhal_sdxx_t *sdxx)
{
    CY_ASSERT(sdxx != NULL);
    return (_CYHAL_SDXX_SEMA_USED == _cyhal_sdxx_semaphore_status[sdxx->resource.block_num]) ||
                (_CYHAL_SDXX_SEMA_SET == _cyhal_sdxx_semaphore_status[sdxx->resource.block_num]);
}

#endif /* CY_RTOS_AWARE or COMPONENT_RTOS_AWARE defined */

static cy_rslt_t _cyhal_sdxx_prepare_for_transfer(_cyhal_sdxx_t *sdxx)
{
    CY_ASSERT(sdxx != NULL);

    uint32_t activated_cmd_complete = 0;
    if (sdxx->irq_cause & (sdxx->is_sdio ? CYHAL_SDIO_CMD_COMPLETE : CYHAL_SDHC_CMD_COMPLETE))
    {
        /* Activate CY_SD_HOST_CMD_COMPLETE interrupt mask only if user enabled callback for that event */
        activated_cmd_complete = CY_SD_HOST_CMD_COMPLETE;
    }

    /* Enabling transfer complete interrupt as it takes part in in write / read processes */
    Cy_SD_Host_SetNormalInterruptMask(sdxx->base, Cy_SD_Host_GetNormalInterruptMask(sdxx->base) | activated_cmd_complete | CY_SD_HOST_XFER_COMPLETE);

    return CY_RSLT_SUCCESS;
}

typedef enum
{
    _CYHAL_SDHC_CARD_VDD                    = 0,
    _CYHAL_SDHC_CARD_IO_VOLTAGE             = 1,
    _CYHAL_SDHC_CARD_DETECT                 = 2,
    _CYHAL_SDHC_CARD_MECH_WRITE_PROTECT     = 3,
    _CYHAL_SDHC_NOT_WEAK_FUNC               = 4
} _cyhal_sdhc_weak_func_type;

static _cyhal_sdxx_t *_cyhal_sdxx_config_structs[CY_IP_MXSDHC_INSTANCES];

/* Structure to map SDHC events on SDHC interrupts */
static const uint32_t _cyhal_sdhc_event_map[] =
{
    (uint32_t)CYHAL_SDHC_ERR_INTERRUPT,   // Default error if nothing is recognized
    (uint32_t)CYHAL_SDHC_CMD_COMPLETE,    // CY_SD_HOST_CMD_COMPLETE
    (uint32_t)CYHAL_SDHC_XFER_COMPLETE,   // CY_SD_HOST_XFER_COMPLETE
    (uint32_t)CYHAL_SDHC_BGAP_EVENT,      // CY_SD_HOST_BGAP
    (uint32_t)CYHAL_SDHC_DMA_INTERRUPT,   // CY_SD_HOST_DMA_INTERRUPT
    (uint32_t)CYHAL_SDHC_BUF_WR_READY,    // CY_SD_HOST_BUF_WR_READY
    (uint32_t)CYHAL_SDHC_BUF_RD_READY,    // CY_SD_HOST_BUF_RD_READY
    (uint32_t)CYHAL_SDHC_CARD_INSERTION,  // CY_SD_HOST_CARD_INSERTION
    (uint32_t)CYHAL_SDHC_CARD_REMOVAL,    // CY_SD_HOST_CARD_REMOVAL
    /*  Placeholder of removed CYHAL_SDHC_CARD_INTERRUPT.
    *   It is needed for cyhal_sdhc_enable_event and _cyhal_utils_convert_flags
    *   functions correct work. */
    0,
    (uint32_t)CYHAL_SDHC_FX_EVENT,        // CY_SD_HOST_FX_EVENT
    (uint32_t)CYHAL_SDHC_CQE_EVENT,       // CY_SD_HOST_CQE_EVENT
    (uint32_t)CYHAL_SDHC_ERR_INTERRUPT,   // CY_SD_HOST_ERR_INTERRUPT
};


/* This callback is used when card detect pin is GPIO (not dedicated SDHC block signal) */
static void _cyhal_sdhc_gpio_card_detect_callback(void *callback_arg, cyhal_gpio_event_t event)
{
    CY_ASSERT(NULL != callback_arg);
    _cyhal_sdxx_t *sdxx = (_cyhal_sdxx_t *)callback_arg;

    if (sdxx->callback_data.callback != NULL)
    {
        cyhal_sdhc_event_callback_t callback = (cyhal_sdhc_event_callback_t) sdxx->callback_data.callback;

        /* Card is considered as inserted if card_detect pin in low state. */

        /* Card removal event */
        if ((event & CYHAL_GPIO_IRQ_RISE) && (sdxx->irq_cause & CYHAL_SDHC_CARD_REMOVAL))
        {
            /* Call registered callbacks here */
            (callback) (sdxx->callback_data.callback_arg, CYHAL_SDHC_CARD_REMOVAL);
        }
        /* Card insertion event */
        if ((event & CYHAL_GPIO_IRQ_FALL) && (sdxx->irq_cause & CYHAL_SDHC_CARD_INSERTION))
        {
            /* Call registered callbacks here */
            (callback) (sdxx->callback_data.callback_arg, CYHAL_SDHC_CARD_INSERTION);
        }
    }
}

#if !defined(CYHAL_DISABLE_WEAK_FUNC_IMPL)

/*  Function, that handles pins that stands behind SD Host PDL driver pin-related WEAK functions, such as:
*   - Cy_SD_Host_IsCardConnected
*   - Cy_SD_Host_IsWpSet
*   - Cy_SD_Host_EnableCardVoltage
*   - Cy_SD_Host_DisableCardVoltage
*   - Cy_SD_Host_ChangeIoVoltage
*   To make their usage in SDHC HAL driver more flexible by providing user ability to use card detect,
*   write protect, pwr en, and io select signals on pins they like instead of dedicated SDHC block pins */
static bool _cyhal_sdxx_handle_weak_func(const SDHC_Type *base, _cyhal_sdhc_weak_func_type weak_function, bool enable)
{
    uint8_t block_idx = (SDHC0 == base) ? 0 : 1;
    _cyhal_sdxx_t *sdxx = _cyhal_sdxx_config_structs[block_idx];
    CY_ASSERT(NULL != sdxx);

    cyhal_gpio_t pin_pwr_en;
    cyhal_gpio_t pin_io_volt_sel;
    cyhal_gpio_t pin_card_detect;
    cyhal_gpio_t pin_write_prot;

    CY_ASSERT((weak_function == _CYHAL_SDHC_CARD_VDD) || (weak_function == _CYHAL_SDHC_CARD_IO_VOLTAGE) ||
            (weak_function == _CYHAL_SDHC_CARD_DETECT) || (weak_function == _CYHAL_SDHC_CARD_MECH_WRITE_PROTECT));

    pin_io_volt_sel = sdxx->pin_io_vol_sel;

    if (sdxx->is_sdio)
    {
        pin_pwr_en = NC;
        pin_card_detect = NC;
        pin_write_prot = NC;
    }
    else
    {
        cyhal_sdhc_t *sdhc = (cyhal_sdhc_t *) sdxx->obj;
        pin_pwr_en = sdhc->pin_card_pwr_en;
        pin_card_detect = sdhc->pin_card_detect;
        pin_write_prot = sdhc->pin_card_mech_write_prot;
    }

    /* function index */
    uint8_t f_idx = (uint8_t)weak_function;

    /* Indexes according to _cyhal_sdhc_weak_func_type */
    #if _CYHAL_SDHC_IO_VOLT_SEL_PRESENT
    static const cyhal_resource_pin_mapping_t* pin_mappings[] = {
            cyhal_pin_map_sdhc_card_if_pwr_en, cyhal_pin_map_sdhc_io_volt_sel, cyhal_pin_map_sdhc_card_detect_n,
            cyhal_pin_map_sdhc_card_mech_write_prot
        };
    static const size_t pin_mapping_sizes[] = {
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_if_pwr_en), _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_io_volt_sel),
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_detect_n), _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_mech_write_prot)
        };
    #else  // _CYHAL_SDHC_IO_VOLT_SEL_PRESENT
    static const cyhal_resource_pin_mapping_t* pin_mappings[] = {
            cyhal_pin_map_sdhc_card_if_pwr_en, NULL, cyhal_pin_map_sdhc_card_detect_n,
            cyhal_pin_map_sdhc_card_mech_write_prot
        };
    static const size_t pin_mapping_sizes[] = {
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_if_pwr_en), 0,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_detect_n), _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_mech_write_prot)
        };
    #endif // _CYHAL_SDHC_IO_VOLT_SEL_PRESENT
    cyhal_gpio_t pins[] = { pin_pwr_en, pin_io_volt_sel, pin_card_detect, pin_write_prot };

    /*  Per sd_host PDL documentation (documentation for Cy_SD_Host_ChangeIoVoltage),
    *   SIGNALING_EN bit of the SDHC_CORE_HOST_CTRL2_R register must be set even if
    *   GPIO used for io voltage switching. */
    if (_CYHAL_SDHC_CARD_IO_VOLTAGE == weak_function)
    {
        SDHC_CORE_HOST_CTRL2_R(base) = _CLR_SET_FLD16U(SDHC_CORE_HOST_CTRL2_R(base),
                SDHC_CORE_HOST_CTRL2_R_SIGNALING_EN, enable);

        /* enable (true) stands for 1.8V while false for 3.3V */
        sdxx->low_voltage_io_set = enable;
    }

    /* BSP-3317. Need to enable PWR_CTRL_R for all pin types */
    if(weak_function == _CYHAL_SDHC_CARD_VDD)
    {
        SDHC_CORE_PWR_CTRL_R(base) =
                    _CLR_SET_FLD8U(SDHC_CORE_PWR_CTRL_R(base), SDHC_CORE_PWR_CTRL_R_SD_BUS_PWR_VDD1, enable);
        /* If GPIO pin */
        if (NULL == _cyhal_utils_get_resource(pins[f_idx], pin_mappings[f_idx], pin_mapping_sizes[f_idx], NULL, false))
        {
            cyhal_gpio_write(pins[f_idx], enable);
        }
        return true;
    }
    /* Pin is not provided by user */
    else if (NC == pins[f_idx])
    {
        /* Return true for card detect, false for write protect and false for other (dont care) */
        return (weak_function == _CYHAL_SDHC_CARD_DETECT) ? true : false;
    }
    /* Pin is GPIO */
    else if (NULL == _cyhal_utils_get_resource(pins[f_idx], pin_mappings[f_idx], pin_mapping_sizes[f_idx], NULL, false))
    {
        if (weak_function == _CYHAL_SDHC_CARD_DETECT)
        {
            /* Card is inserted if signal is low */
            return !cyhal_gpio_read(pins[f_idx]);
        }
        else if (weak_function == _CYHAL_SDHC_CARD_MECH_WRITE_PROTECT)
        {
            /* Card is mech. write protected if signal is high */
            return cyhal_gpio_read(pins[f_idx]);
        }
        /* _CYHAL_SDHC_CARD_IO_VOLTAGE */
        else
        {
            cyhal_gpio_write(pins[f_idx], enable);
            /* Don't care */
            return true;
        }
    }
    /* Pin is dedicated SDHC block signal */
    else
    {
        /* Actually copies of corresponding functions from cy_sd_host.c */
        /* _CYHAL_SDHC_CARD_VDD handled above */
        switch(weak_function)
        {
            case _CYHAL_SDHC_CARD_DETECT:
                while(true != _FLD2BOOL(SDHC_CORE_PSTATE_REG_CARD_STABLE, SDHC_CORE_PSTATE_REG(base)))
                {
                    /* Wait until the card is stable. */
                }
                return _FLD2BOOL(SDHC_CORE_PSTATE_REG_CARD_INSERTED, SDHC_CORE_PSTATE_REG(base));
            case _CYHAL_SDHC_CARD_MECH_WRITE_PROTECT:
                return _FLD2BOOL(SDHC_CORE_PSTATE_REG_WR_PROTECT_SW_LVL, SDHC_CORE_PSTATE_REG(base));
            case _CYHAL_SDHC_CARD_IO_VOLTAGE:
                /* io voltage already handled above */
                (void)0;
                break;
            default:
                CY_ASSERT(false);
                break;
        }
        /* dont care */
        return true;
    }
}

/* Overriden Cy_SD_Host_IsCardConnected (originally part of cy_sd_host.c)
*  This version can handle both - dedicated IP block sdhc_card_detect_n pin and
*  user-provided GPIO */
bool Cy_SD_Host_IsCardConnected(SDHC_Type const *base)
{
    return _cyhal_sdxx_handle_weak_func(base, _CYHAL_SDHC_CARD_DETECT, false);
}

/* Overriden Cy_SD_Host_IsWpSet function (originally part of cy_sd_host.c).
*  This version can handle both - dedicated IP block sdhc_card_mech_write_prot pin
*  and user-provided GPIO */
bool Cy_SD_Host_IsWpSet(SDHC_Type const *base)
{
    return _cyhal_sdxx_handle_weak_func(base, _CYHAL_SDHC_CARD_MECH_WRITE_PROTECT, false);
}

/* Overriden Cy_SD_Host_EnableCardVoltage and Cy_SD_Host_DisableCardVoltage
*  functions (originally part of in cy_sd_host.c).
*  This version can handle both - dedicated IP block sdhc_card_if_pwr_en pin and
*  user-provided GPIO */
void Cy_SD_Host_EnableCardVoltage(SDHC_Type *base)
{
    (void)_cyhal_sdxx_handle_weak_func(base, _CYHAL_SDHC_CARD_VDD, true);
}
void Cy_SD_Host_DisableCardVoltage(SDHC_Type *base)
{
    (void)_cyhal_sdxx_handle_weak_func(base, _CYHAL_SDHC_CARD_VDD, false);
}

/* Overriden Cy_SD_Host_ChangeIoVoltage function (originally part of cy_sd_host.c).
*  This version can handle both - dedicated IP block sdhc_io_volt_sel pin
*  and user-provided GPIO */
void Cy_SD_Host_ChangeIoVoltage(SDHC_Type *base, cy_en_sd_host_io_voltage_t ioVoltage)
{
    (void)_cyhal_sdxx_handle_weak_func(base, _CYHAL_SDHC_CARD_IO_VOLTAGE, (CY_SD_HOST_IO_VOLT_1_8V == ioVoltage));
}

#endif /* CYHAL_DISABLE_WEAK_FUNC_IMPL */

static uint8_t _cyhal_sdhc_get_block_from_irqn(_cyhal_system_irq_t irqn)
{
    switch (irqn)
    {
    #if (CY_IP_MXSDHC_INSTANCES > 0)
        case sdhc_0_interrupt_general_IRQn: return 0;
    #endif

    #if (CY_IP_MXSDHC_INSTANCES > 1)
        case sdhc_1_interrupt_general_IRQn: return 1;
    #endif

    #if (CY_IP_MXSDHC_INSTANCES > 2)
        #error "Unhandled SDHC count"
    #endif
    default:
        CY_ASSERT(false); /* Should never be called with a non-SDHC IRQn */
        return 0;
    }
}

static cy_rslt_t _cyhal_sdxx_setup_pin(_cyhal_sdxx_t *sdxx, cyhal_gpio_t pin, const cyhal_resource_pin_mapping_t *pinmap, uint8_t drive_mode,
    size_t count, cyhal_gpio_t *objRef, _cyhal_sdhc_weak_func_type weak_func_pin_type, bool reserve_pin)
{
    cy_rslt_t result;
    const cyhal_resource_pin_mapping_t *map = _cyhal_utils_get_resource(pin, pinmap, count, NULL, false);

    if (map == NULL)
    {
        result = CYHAL_SDHC_RSLT_ERR_PIN;
        if (_CYHAL_SDHC_NOT_WEAK_FUNC != weak_func_pin_type)
        {
            /* pin, provided by user is probably not dedicated SDHC signal, but GPIO */
            switch(weak_func_pin_type)
            {
                case _CYHAL_SDHC_CARD_DETECT:
                case _CYHAL_SDHC_CARD_MECH_WRITE_PROTECT:
                    result = reserve_pin
                        ? cyhal_gpio_init(pin, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, true)
                        : CY_RSLT_SUCCESS;
                    break;
                case _CYHAL_SDHC_CARD_VDD:
                case _CYHAL_SDHC_CARD_IO_VOLTAGE:
                    result = reserve_pin
                        ? cyhal_gpio_init(pin, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false)
                        : CY_RSLT_SUCCESS;
                    break;
                default:
                    CY_ASSERT(false); /* Should never get here. */
            }
        }
        if ((_CYHAL_SDHC_CARD_DETECT == weak_func_pin_type) && (CY_RSLT_SUCCESS == result))
        {
            // Ensure the two structures are the same. Divide by 0 build error if they differ.
            CY_ASSERT(1 / (sizeof(struct cyhal_sdhc_t_gpio_cb) == sizeof(cyhal_gpio_callback_data_t)));

            cyhal_sdhc_t* sdhc = ((cyhal_sdhc_t*) sdxx->obj);
            cyhal_gpio_callback_data_t* cb_data = (cyhal_gpio_callback_data_t*)&(sdhc->card_detect_cb);
            cb_data->callback = _cyhal_sdhc_gpio_card_detect_callback;
            cb_data->callback_arg = sdxx;
            cyhal_gpio_register_callback(pin, cb_data);
            cyhal_gpio_enable_event(pin, CYHAL_GPIO_IRQ_BOTH, CYHAL_ISR_PRIORITY_DEFAULT, true);
            sdhc->cd_gpio_cb_enabled = true;
        }
    }
    else
    {
        result = reserve_pin
            ? _cyhal_utils_reserve_and_connect(map, drive_mode)
            : CY_RSLT_SUCCESS;
    }

    if (result == CY_RSLT_SUCCESS)
    {
        *objRef = pin;
    }

    return result;
}

bool _cyhal_sdhc_is_busy(const _cyhal_sdxx_t *sdxx) {
    bool busy_status = true;
    /* Check DAT Line Active */
    uint32_t pState = Cy_SD_Host_GetPresentState(sdxx->base);
    if ((CY_SD_HOST_DAT_LINE_ACTIVE != (pState & CY_SD_HOST_DAT_LINE_ACTIVE)) &&
        (CY_SD_HOST_CMD_CMD_INHIBIT_DAT != (pState & CY_SD_HOST_CMD_CMD_INHIBIT_DAT)))
    {
        busy_status = false;
    }
    return busy_status || (_CYHAL_SDXX_NOT_RUNNING != sdxx->data_transfer_status);
}


bool _cyhal_sdio_is_busy(const _cyhal_sdxx_t *sdxx) {
    return (_CYHAL_SDXX_NOT_RUNNING != sdxx->data_transfer_status);
}

/*******************************************************************************
*       Deep Sleep Callback Service Routine
*******************************************************************************/
static bool _cyhal_sdio_syspm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void *callback_arg)
{
    bool allow = true;
    _cyhal_sdxx_t *sdxx = (_cyhal_sdxx_t *)callback_arg;
    CY_ASSERT(sdxx != NULL);

    cyhal_sdio_t *sdio = (cyhal_sdio_t *) sdxx->obj;

    cy_stc_syspm_callback_params_t pdl_params =
    {
        .base = sdxx->base,
        .context = &(sdxx->context)
    };

    /* Check if hardware is ready to go sleep using lower level callback. */
    if (state == CYHAL_SYSPM_CB_CPU_DEEPSLEEP)
    {
        allow = (Cy_SD_Host_DeepSleepCallback(&pdl_params, _cyhal_utils_convert_haltopdl_pm_mode(mode)) == CY_SYSPM_SUCCESS);
    }

    if (allow)
    {
        switch (mode)
        {
            case CYHAL_SYSPM_CHECK_READY:
            {
                allow = !_cyhal_sdio_is_busy(sdxx);
                if (allow)
                {
                    /* Call the event only if we are ready to go to sleep */
                    cyhal_sdio_event_callback_t callback = (cyhal_sdio_event_callback_t) sdxx->callback_data.callback;
                    if ((callback != NULL) && (0U != (sdio->events & (uint32_t) CYHAL_SDIO_GOING_DOWN)))
                    {
                        (callback)(sdxx->callback_data.callback_arg, CYHAL_SDIO_GOING_DOWN);
                    }
                    /* Set transition flag to prevent any further transaction */
                    sdxx->pm_transition_pending = true;
                }
                break;
            }

            case CYHAL_SYSPM_BEFORE_TRANSITION:
            case CYHAL_SYSPM_AFTER_DS_WFI_TRANSITION:
            {
                /* Nothing to do */
                break;
            }

            case CYHAL_SYSPM_AFTER_TRANSITION:
            case CYHAL_SYSPM_CHECK_FAIL:
            {
                /* Execute this only if check ready case was executed */
                if (sdxx->pm_transition_pending)
                {
                    /* Execute callback to indicate that interface is coming up */
                    cyhal_sdio_event_callback_t callback = (cyhal_sdio_event_callback_t) sdxx->callback_data.callback;
                    if ((callback != NULL) && (0U != (sdio->events & (uint32_t) CYHAL_SDIO_COMING_UP)))
                    {
                        (callback)(sdxx->callback_data.callback_arg, CYHAL_SDIO_COMING_UP);
                    }

                    sdxx->pm_transition_pending = false;
                }
                break;
            }

            default:
                CY_ASSERT(false);
                break;
        }
    }
    return allow;
}

static bool _cyhal_sdhc_syspm_callback(cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode, void *callback_arg)
{
    bool allow = true;
    _cyhal_sdxx_t *sdxx = (_cyhal_sdxx_t *)callback_arg;
    CY_ASSERT(sdxx != NULL);

    cy_stc_syspm_callback_params_t pdl_params =
    {
        .base = sdxx->base,
        .context = &(sdxx->context)
    };

    /* Check if hardware is ready to go sleep using lower level callback. */
    if (state == CYHAL_SYSPM_CB_CPU_DEEPSLEEP)
    {
        allow = (Cy_SD_Host_DeepSleepCallback(&pdl_params, _cyhal_utils_convert_haltopdl_pm_mode(mode)) == CY_SYSPM_SUCCESS);
    }

    if (allow)
    {
        switch (mode)
        {
            case CYHAL_SYSPM_CHECK_READY:
            {
                allow = !_cyhal_sdhc_is_busy(sdxx);
                if (allow)
                {
                    /* Set transition flag to prevent any further transaction */
                    sdxx->pm_transition_pending = true;
                }
                break;
            }

            case CYHAL_SYSPM_BEFORE_TRANSITION:
            {
                /* Nothing to do */
                break;
            }

            case CYHAL_SYSPM_AFTER_TRANSITION:
            case CYHAL_SYSPM_CHECK_FAIL:
            {
                /* Execute this only if check ready case was executed */
                sdxx->pm_transition_pending = false;
                break;
            }

            default:
                CY_ASSERT(false);
                break;
        }
    }
    return allow;
}

static cy_en_sd_host_bus_width_t _cyhal_sdhc_buswidth_hal_to_pdl(uint8_t sd_data_bits)
{
    switch (sd_data_bits)
    {
        case 1:
            return CY_SD_HOST_BUS_WIDTH_1_BIT;
        case 4:
            return CY_SD_HOST_BUS_WIDTH_4_BIT;
        case 8:
            return CY_SD_HOST_BUS_WIDTH_8_BIT;
        default:
            CY_ASSERT(false);
            return CY_SD_HOST_BUS_WIDTH_1_BIT;
    }
}

static uint8_t _cyhal_sdhc_buswidth_pdl_to_hal(cy_en_sd_host_bus_width_t sd_data_bits)
{
    switch (sd_data_bits)
    {
        case CY_SD_HOST_BUS_WIDTH_1_BIT:
            return 1;
        case CY_SD_HOST_BUS_WIDTH_4_BIT:
            return 4;
        case CY_SD_HOST_BUS_WIDTH_8_BIT:
            return 8;
        default:
            CY_ASSERT(false);
            return 1;
    }
}

/***********************************************************************************************************************
*
* Finds SDHC internal divider value according to source clock frequency and desired frequency.
*
* hz_src                - Source clock frequency, that needs to be divided
* desired_hz            - Desired clock frequency
* tolerance             - (Not used)
* only_below_desired    - (Not used)
* div                   - Calculated divider value will be placed by this pointer
*
***********************************************************************************************************************/
static cy_rslt_t _cyhal_sdxx_find_best_div(uint32_t hz_src, uint32_t desired_hz,
            const cyhal_clock_tolerance_t *tolerance, bool only_below_desired, uint32_t *div)
{
    CY_UNUSED_PARAMETER(tolerance);
    CY_UNUSED_PARAMETER(only_below_desired);

    /* Rounding up for correcting the error in integer division
    * to ensure the actual frequency is less than or equal to
    * the requested frequency.
    * Ensure computed divider is no more than 10-bit.
    */

    if (hz_src > desired_hz)
    {
        uint32_t freq = (desired_hz << 1);
        uint32_t calculated_divider = ((hz_src + freq - 1) / freq) & 0x3FF;
        /* Real divider is 2 x calculated_divider */
        *div = calculated_divider << 1;
    }
    else
    {
        *div = 1;
    }

    return CY_RSLT_SUCCESS;
}

/***********************************************************************************************************************
*
* Determines SD bus speed mode according to provided clock frequency and updates SDHC HW registers with corresponding
*   speed mode setting and, optionally, negotiates new speed mode with the card
*
* sdxx                  - Pointer to SDHC/SDIO common structure
* freq                  - Clock frequency, according to which speed mode will be determined
* lv_signaling          - Support 1.8V
* negotiate             - Whether new frequency value needs to be negotiated with the card
*
***********************************************************************************************************************/
static cy_rslt_t _cyhal_sdxx_update_hw_clock_config(_cyhal_sdxx_t *sdxx, uint32_t freq, bool lv_signaling, bool negotiate)
{
    cy_en_sd_host_bus_speed_mode_t  busSpeed;
    cy_rslt_t                       result;

    if (!sdxx->is_sdio && sdxx->emmc)
    {
        /* legacy MMC speed is 0-26 MHz */
        if (freq <= _CYHAL_SDXX_MHZ(26))
        {
            busSpeed = CY_SD_HOST_BUS_SPEED_EMMC_LEGACY;
        }
        /* High Speed SDR is 0-52 MHz */
        else
        {
            busSpeed = CY_SD_HOST_BUS_SPEED_EMMC_HIGHSPEED_SDR;
        }
    }
    else
    {
        if (freq <= _CYHAL_SDXX_MHZ(25))
        {
            busSpeed = (lv_signaling)
                ? CY_SD_HOST_BUS_SPEED_SDR12_5
                : CY_SD_HOST_BUS_SPEED_DEFAULT;
        }
        else if (freq <= _CYHAL_SDXX_MHZ(50))
        {
            busSpeed = (lv_signaling)
                ? CY_SD_HOST_BUS_SPEED_SDR25
                : CY_SD_HOST_BUS_SPEED_HIGHSPEED;
        }
        else
        {
            busSpeed = (lv_signaling)
                ? CY_SD_HOST_BUS_SPEED_SDR50
                : CY_SD_HOST_BUS_SPEED_HIGHSPEED;
        }
    }

    /*  Currently can only negotiate with SD Card. SDIO negotiation proccess is tracked in BSP-2643. */
    if (negotiate && !sdxx->is_sdio)
    {
        result = (cy_rslt_t)Cy_SD_Host_SetBusSpeedMode(sdxx->base, busSpeed, &(sdxx->context));
    }
    else
    {
        result = (cy_rslt_t)Cy_SD_Host_SetHostSpeedMode(sdxx->base, busSpeed);
    }
    return result;
}

/***********************************************************************************************************************
*
* Changes the Host controller SD clock.
*
* sdxx                  - Pointer to SHDC/SDIO common structure
* frequency             - The frequency in Hz (pointer). This variable will be updated with actual frequency achieved
*   upon function return.
* lv_signaling          - Support 1.8V
* negotiate             - Whether new frequency value needs to be negotiated with the card
*
***********************************************************************************************************************/
static cy_rslt_t _cyhal_sdxx_sdcardchangeclock(_cyhal_sdxx_t *sdxx, uint32_t *frequency, bool lv_signaling, bool negotiate)
{
    CY_ASSERT(NULL != sdxx);
    CY_ASSERT(NULL != frequency);
    CY_ASSERT(NULL != sdxx->base);

    cyhal_clock_t most_suitable_hf_source;
    uint32_t most_suitable_div = 0;
    uint32_t actual_freq = 0;
    uint32_t hf_freq = 0;
    cy_rslt_t ret = CY_RSLT_SUCCESS;

    if (sdxx->clock_owned)
    {
        /*  Find most suitable HF clock source and divider for it to achieve closest frequency to desired.
        *   No clock settings are being changed here. */
        ret = _cyhal_utils_find_hf_source_n_divider(&(sdxx->clock), *frequency, NULL, _cyhal_sdxx_find_best_div,
                                &most_suitable_hf_source, &most_suitable_div);
    }
    else
    {
        ret = _cyhal_sdxx_find_best_div(cyhal_clock_get_frequency(&(sdxx->clock)), *frequency, NULL, false, &most_suitable_div);
    }

    if (CY_RSLT_SUCCESS == ret)
    {
        /* If clock is owned, we just found most suitable hf source for it. if not - we need to work with the one provided */
        hf_freq = cyhal_clock_get_frequency(sdxx->clock_owned ? &most_suitable_hf_source : &(sdxx->clock));
        actual_freq = hf_freq / most_suitable_div;

        ret = _cyhal_sdxx_update_hw_clock_config(sdxx, actual_freq, lv_signaling, negotiate);
    }

    if (sdxx->clock_owned)
    {
        if (CY_RSLT_SUCCESS == ret)
        {
            /* Switch to most suitable HF clock source */
            ret = cyhal_clock_set_source(&(sdxx->clock), &most_suitable_hf_source);
        }

        if (CY_RSLT_SUCCESS == ret)
        {
            /* SDHC internal divider will be configured instead. */
            ret = cyhal_clock_set_divider(&(sdxx->clock), 1);
        }
    }

    if (!sdxx->is_sdio)
    {
        ((cyhal_sdhc_t *) sdxx->obj)->block_source_freq_hz = hf_freq;
    }

    if (CY_RSLT_SUCCESS == ret)
    {
        Cy_SD_Host_DisableSdClk(sdxx->base);
        ret = (cy_rslt_t)Cy_SD_Host_SetSdClkDiv(sdxx->base, most_suitable_div >> 1);
        Cy_SD_Host_EnableSdClk(sdxx->base);
    }

    if (CY_RSLT_SUCCESS == ret)
    {
        *frequency = actual_freq;
    }

    return ret;
}

/*******************************************************************************
*
* Waits for the command complete event.
*
* sdxx                     - Pointer to SHDC/SDIO common structure
* time_used_ms             - Pointer to uint32_t value for the total time taken for the function.
*
*******************************************************************************/
static cy_en_sd_host_status_t _cyhal_sdxx_pollcmdcomplete(_cyhal_sdxx_t *sdxx, uint32_t *time_used_ms)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_TIMEOUT;
    uint32_t retry  = _CYHAL_SDHC_RETRY_TIMES * _CYHAL_SDIO_CMD_CMPLT_DELAY_US;

    while (retry > 0UL)
    {
        /* Command complete */
        if (CY_SD_HOST_CMD_COMPLETE == (CY_SD_HOST_CMD_COMPLETE & Cy_SD_Host_GetNormalInterruptStatus(sdxx->base)))
        {
            sdxx->data_transfer_status &= ~_CYHAL_SDXX_WAIT_CMD_COMPLETE;

            /* Clear interrupt flag */
            Cy_SD_Host_ClearNormalInterruptStatus(sdxx->base, CY_SD_HOST_CMD_COMPLETE);

            ret = CY_SD_HOST_SUCCESS;
            break;
        }

        cyhal_system_delay_us(1);
        retry--;
    }
    if (time_used_ms != NULL)
    {
        *time_used_ms = (((_CYHAL_SDHC_RETRY_TIMES * _CYHAL_SDIO_CMD_CMPLT_DELAY_US) - retry) / 1000);
    }

    return ret;
}


/*******************************************************************************
*
* Waits for the transfer complete event.
*
* sdxx                  - Pointer to SHDC/SDIO common structure
* delay                 - The delay timeout for one block transfer.
*
* return If the sdxx pointer is NULL, returns error.
*
*******************************************************************************/
static cy_en_sd_host_status_t _cyhal_sdxx_polltransfercomplete(_cyhal_sdxx_t *sdxx, const uint16_t delay)
{
    cy_en_sd_host_status_t ret = CY_SD_HOST_ERROR_TIMEOUT;
    uint32_t               retry = _CYHAL_SDHC_RW_RETRY_CYCLES;
    uint32_t               status = 0UL;

    while ((CY_SD_HOST_ERROR_TIMEOUT == ret) && (retry-- > 0U))
    {
        /* We check for either the interrupt register or the byte set in the _cyhal_sdxx_irq_handler
         * to avoid a deadlock in the case where if an API that is polling is called from an ISR
         * and its priority is higher than the priority of the _cyhal_sdxx_irq_handler thus not allowing
         * the signalling byte to be set.
         */
        status = Cy_SD_Host_GetNormalInterruptStatus(sdxx->base);
        if (CY_SD_HOST_XFER_COMPLETE == (CY_SD_HOST_XFER_COMPLETE & status) ||
            (sdxx->is_sdio ? !_cyhal_sdio_is_busy(sdxx) : !_cyhal_sdhc_is_busy(sdxx)))
        {
            /* Transfer complete */
            ret = CY_SD_HOST_SUCCESS;
            break;
        }
        cyhal_system_delay_us(delay);
    }

    return ret;
}

// Indicates that a sync transfer is in process
static void _cyhal_sdxx_setup_smphr(_cyhal_sdxx_t *sdxx)
{
#if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
    uint8_t block_num = sdxx->resource.block_num;
    bool in_isr = (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0;
    if (!in_isr)
    {
        cy_rslt_t ret = CY_RSLT_SUCCESS;
        if (_CYHAL_SDXX_SEMA_NOT_INITED == _cyhal_sdxx_semaphore_status[block_num])
        {
            /* Semaphore is used to make transfer complete event wait process be more RTOS-friendly.
            *  It cannot be initialized in ISR context (some of mbed layers are initializing sdio in ISR conext),
            *  so we have to do it in scope of transfer functions. */
            /* Assert that we are not in an ISR */
            CY_ASSERT((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) == 0);
            ret = cy_rtos_init_semaphore(&(_cyhal_sdxx_semaphore_xfer_done[block_num]), 1, 0);
        }
        else if (_CYHAL_SDXX_SEMA_SET == _cyhal_sdxx_semaphore_status[block_num])
        {
            /*  Situation, when semaphore was set, but _cyhal_sdxx_waitfor_transfer_complete function was not
            *   used for the transfer to get the semaphore (async transfer). Clearing the semaphore in order
            *   to prepare it for another transfer.  */
            ret = cy_rtos_get_semaphore(&(_cyhal_sdxx_semaphore_xfer_done[block_num]), 500, in_isr);
        }
        if (CY_RSLT_SUCCESS == ret)
        {
            _cyhal_sdxx_semaphore_status[block_num] = _CYHAL_SDXX_SEMA_USED;
        }
    }
    else if (_CYHAL_SDXX_SEMA_NOT_INITED != _cyhal_sdxx_semaphore_status[block_num])
    {
        _cyhal_sdxx_semaphore_status[block_num] = _CYHAL_SDXX_SEMA_NOT_USED;
    }
#else
    // We don't need to do anything special if we're not in an RTOS context
    CY_UNUSED_PARAMETER(sdxx);
#endif
}

static cy_rslt_t _cyhal_sdxx_waitfor_transfer_complete(_cyhal_sdxx_t *sdxx)
{
    /* When using an RTOS if a sdxx api (read or write) is called from and ISR in
     * in certain RTOSes cy_rtos_get_semaphore returns immediately without blocking. So we can
     * either busy wait around the semaphore being set in the ISR or use the normal polling method
     * we use in the non-RTOS case. For simplicity and to avoid the calling ISR from depending on
     * the SDXX ISR priority we use the normal polling method.
     */
    cy_rslt_t ret = CY_RSLT_SUCCESS;
    #if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
    bool in_isr = (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0;
    if ((!in_isr) && _cyhal_sdxx_is_smfr_ready_for_get(sdxx))
    {
        ret = cy_rtos_get_semaphore(&(_cyhal_sdxx_semaphore_xfer_done[sdxx->resource.block_num]), 500, in_isr);
        if (CY_RSLT_SUCCESS == ret)
        {
            _cyhal_sdxx_semaphore_status[sdxx->resource.block_num] = _CYHAL_SDXX_SEMA_NOT_USED;
        }
    }
    else
    {
    #endif
        ret = (cy_rslt_t)_cyhal_sdxx_polltransfercomplete(sdxx, _CYHAL_SDHC_RW_TIMEOUT_US);
    #if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
    }
    #endif

    return ret;
}

static void _cyhal_sdhc_irq_handler(void)
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint8_t block = _cyhal_sdhc_get_block_from_irqn(irqn);
    SDHC_Type *blockAddr = _CYHAL_SDHC_BASE_ADDRESSES[block];
    _cyhal_sdxx_t *sdxx = (_cyhal_sdxx_t*) _cyhal_sdxx_config_structs[block];

    uint32_t interruptStatus = Cy_SD_Host_GetNormalInterruptStatus(blockAddr);
    uint32_t userInterruptStatus = interruptStatus & sdxx->irq_cause;
    cyhal_sdhc_event_t user_events = (0 != userInterruptStatus) ? (cyhal_sdhc_event_t)_cyhal_utils_convert_flags(
        _cyhal_sdhc_event_map, sizeof(_cyhal_sdhc_event_map) / sizeof(uint32_t), userInterruptStatus) :
        (cyhal_sdhc_event_t)0;

    /*  Some parts of SDHost PDL and SDHC HAL drivers are sending SD commands and polling interrupt status
    *   until CY_SD_HOST_CMD_COMPLETE occurs. Thats why we can't clear CY_SD_HOST_CMD_COMPLETE interrupt status
    *   and code below prevents _cyhal_sdhc_irq_handler from being continuosly called because of uncleared
    *   CY_SD_HOST_CMD_COMPLETE event. */

    if (interruptStatus & Cy_SD_Host_GetNormalInterruptMask(blockAddr) & CY_SD_HOST_CMD_COMPLETE)
    {
        /* Disabling command complete interrupt mask */
        Cy_SD_Host_SetNormalInterruptMask(sdxx->base,
                Cy_SD_Host_GetNormalInterruptMask(sdxx->base) & (uint32_t) ~CY_SD_HOST_CMD_COMPLETE);
        sdxx->data_transfer_status &= ~_CYHAL_SDXX_WAIT_CMD_COMPLETE;
    }

    /*  During SDHost PDL driver operation, CY_SD_HOST_XFER_COMPLETE status can occur and driver
    *   is polling Cy_SD_Host_GetNormalInterruptStatus while waiting for it. Because of this
    *   it is critical to have CY_SD_HOST_XFER_COMPLETE event mask disabled and only enabled during
    *   transfers. Write / Read SDHC/SDIO HAL functions are taking care of enabling CY_SD_HOST_XFER_COMPLETE
    *   mask before transfer while code below disables it. */

    /* CY_SD_HOST_XFER_COMPLETE occured and appropriate bit in interrupt mask is enabled */
    if (interruptStatus & Cy_SD_Host_GetNormalInterruptMask(blockAddr) & CY_SD_HOST_XFER_COMPLETE)
    {
        /* Clearing transfer complete status */
        Cy_SD_Host_ClearNormalInterruptStatus(blockAddr, CY_SD_HOST_XFER_COMPLETE);

        sdxx->data_transfer_status &= ~_CYHAL_SDXX_WAIT_XFER_COMPLETE;

        #if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
        if (_cyhal_sdxx_is_smfr_ready_for_set(sdxx))
        {
            cy_rtos_set_semaphore(&(_cyhal_sdxx_semaphore_xfer_done[sdxx->resource.block_num]), true);
            _cyhal_sdxx_semaphore_status[sdxx->resource.block_num] = _CYHAL_SDXX_SEMA_SET;
        }
        #endif /* CY_RTOS_AWARE or COMPONENT_RTOS_AWARE defined */

        /* Disabling transfer complete interrupt mask */
        Cy_SD_Host_SetNormalInterruptMask(sdxx->base,
                Cy_SD_Host_GetNormalInterruptMask(sdxx->base) & (uint32_t) ~CY_SD_HOST_XFER_COMPLETE);
    }

    if ((sdxx->callback_data.callback != NULL) && (0 != user_events))
    {
        cyhal_sdhc_event_callback_t callback = (cyhal_sdhc_event_callback_t) sdxx->callback_data.callback;

        /* Call registered callbacks here */
        (callback) (sdxx->callback_data.callback_arg, user_events);
    }

    /*  Cannot clear cmd complete interrupt, as it is being polling-waited by many SD Host functions.
    *   It is expected to be cleared by mentioned polling functions. */
    userInterruptStatus &= (uint32_t) ~CY_SD_HOST_CMD_COMPLETE;

    /* Clear only handled events */
    Cy_SD_Host_ClearNormalInterruptStatus(blockAddr, userInterruptStatus);
}

static void _cyhal_sdio_irq_handler(void)
{
    _cyhal_system_irq_t irqn = _cyhal_irq_get_active();
    uint8_t block = _cyhal_sdhc_get_block_from_irqn(irqn);
    SDHC_Type *blockAddr = _CYHAL_SDHC_BASE_ADDRESSES[block];
    _cyhal_sdxx_t *sdxx = (_cyhal_sdxx_t*) _cyhal_sdxx_config_structs[block];

    uint32_t interruptStatus = Cy_SD_Host_GetNormalInterruptStatus(blockAddr);
    uint32_t userInterruptStatus = interruptStatus & sdxx->irq_cause;
    uint32_t normalInterruptMask = Cy_SD_Host_GetNormalInterruptMask(blockAddr);

    /*  Some parts of SDHost PDL and SDIO HAL drivers are sending SD commands and polling interrupt status
    *   until CY_SD_HOST_CMD_COMPLETE occurs. Thats why we can't clear CY_SD_HOST_CMD_COMPLETE interrupt status
    *   and code below prevents _cyhal_sdhc_irq_handler from being continuosly called because of uncleared
    *   CY_SD_HOST_CMD_COMPLETE event. */

    if (interruptStatus & normalInterruptMask & CY_SD_HOST_CMD_COMPLETE)
    {
        /* Disabling command complete interrupt mask */
        Cy_SD_Host_SetNormalInterruptMask(sdxx->base,
                Cy_SD_Host_GetNormalInterruptMask(sdxx->base) & (uint32_t) ~CY_SD_HOST_CMD_COMPLETE);
        sdxx->data_transfer_status &= ~_CYHAL_SDXX_WAIT_CMD_COMPLETE;
    }

    /*  During SDHost PDL driver operation, CY_SD_HOST_XFER_COMPLETE status can occur and driver
    *   is polling Cy_SD_Host_GetNormalInterruptStatus while waiting for it. Because of this
    *   it is critical to have CY_SD_HOST_XFER_COMPLETE event mask disabled and only enabled during
    *   transfers. Write / Read SDHC/SDIO HAL functions are taking care of enabling CY_SD_HOST_XFER_COMPLETE
    *   mask before transfer while code below disables it. */

    /*  CY_SD_HOST_XFER_COMPLETE occured and appropriate bit in interrupt mask is enabled */
    if (interruptStatus & normalInterruptMask & CY_SD_HOST_XFER_COMPLETE)
    {
        sdxx->data_transfer_status &= ~_CYHAL_SDXX_WAIT_XFER_COMPLETE ;
        Cy_SD_Host_ClearNormalInterruptStatus(blockAddr, CY_SD_HOST_XFER_COMPLETE);
        #if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
        if (_cyhal_sdxx_is_smfr_ready_for_set(sdxx))
        {
            cy_rtos_set_semaphore(&(_cyhal_sdxx_semaphore_xfer_done[block]), true);
            _cyhal_sdxx_semaphore_status[block] = _CYHAL_SDXX_SEMA_SET;
        }
        #endif /* CY_RTOS_AWARE or COMPONENT_RTOS_AWARE defined */

        /* Disabling transfer complete interrupt mask */
        Cy_SD_Host_SetNormalInterruptMask(sdxx->base,
                Cy_SD_Host_GetNormalInterruptMask(sdxx->base) & (uint32_t) ~CY_SD_HOST_XFER_COMPLETE);

        /* Transfer is no more active. If card interrupt was not yet enabled after it was disabled in
        *   interrupt handler, enable it.
        */
        uint32_t interrupt_enable_status = Cy_SD_Host_GetNormalInterruptEnable(sdxx->base);
        if ((interrupt_enable_status & CY_SD_HOST_CARD_INTERRUPT) == 0)
        {
            Cy_SD_Host_SetNormalInterruptEnable(sdxx->base, (interrupt_enable_status | CY_SD_HOST_CARD_INTERRUPT));
        }
    }

    if (sdxx->callback_data.callback != NULL && (userInterruptStatus & normalInterruptMask) > 0)
    {
        cyhal_sdio_event_callback_t callback = (cyhal_sdio_event_callback_t) sdxx->callback_data.callback;
        /* Call registered callbacks here */
        /* We may have masked off CMD_COMPLETE above on a previous interrupt, mask here with normalInterruptMask to echo this */
        (callback)(sdxx->callback_data.callback_arg, (cyhal_sdio_event_t) (userInterruptStatus & normalInterruptMask));
    }

    /*  Cannot clear cmd complete interrupt, as it is being polling-waited by many SD Host functions.
    *   It is expected to be cleared by mentioned polling functions. */
    userInterruptStatus &= (uint32_t) ~CY_SD_HOST_CMD_COMPLETE;

    /* Clear only handled events */
    Cy_SD_Host_ClearNormalInterruptStatus(blockAddr, userInterruptStatus);

    /* To clear Card Interrupt need to disable Card Interrupt Enable bit.
    *  The Card Interrupt is enabled after the current transfer is complete
    */
    if (0U != (interruptStatus & CY_SD_HOST_CARD_INTERRUPT))
    {
        uint32_t interruptMask = Cy_SD_Host_GetNormalInterruptEnable(blockAddr);
        interruptMask &= (uint32_t) ~CY_SD_HOST_CARD_INTERRUPT;
        /* Disable Card Interrupt */
        Cy_SD_Host_SetNormalInterruptEnable(blockAddr, interruptMask);
    }
}

/* Software reset of SDHC block data and command circuits */
static void _cyhal_sdxx_reset(_cyhal_sdxx_t *sdxx)
{
    CY_ASSERT(NULL != sdxx);
    CY_ASSERT(NULL != sdxx->base);

    /* Usually it is enough ~ 15 us for reset to complete on 100 MHz HF clock for any supported compiler / optimization.
    *  Making max time much greater to cover different frequencies and unusual cases. Timeout and SW_RST_R check
    *  will be removed after DRIVERS-5769 is resolved. */
    uint32_t timeout_us = 1000;

    sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
    Cy_SD_Host_SoftwareReset(sdxx->base, CY_SD_HOST_RESET_DATALINE);
    Cy_SD_Host_SoftwareReset(sdxx->base, CY_SD_HOST_RESET_CMD_LINE);

    /* This wait loop will be removed after DRIVERS-5769 resolved. */
    while ((sdxx->base->CORE.SW_RST_R != 0) && (timeout_us-- != 0))
    {
        cyhal_system_delay_us(1);
    }

    /* Reset was not cleared by SDHC IP Block. Something wrong. Are clocks enabled? */
    CY_ASSERT(timeout_us != 0);
}

static cy_rslt_t _cyhal_sdhc_init_common_hw(cyhal_sdhc_t *obj, const cyhal_sdhc_configurator_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);

    cy_rslt_t result = CY_RSLT_SUCCESS;

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    sdxx->obj = obj;
    sdxx->is_sdio = false;

    /* Configuration is provided by device configurator */
    sdxx->dc_configured = (cfg->resource != NULL);
    sdxx->dma_type = cfg->host_config->dmaType;

    if (sdxx->dc_configured && (cfg->host_config->dmaType != CY_SD_HOST_DMA_ADMA2))
    {
        /* SDHC HAL does not support non-CY_SD_HOST_DMA_ADMA2 DMA configurations */
        return CYHAL_SDHC_RSLT_ERR_UNSUPPORTED;
    }

    sdxx->base = NULL;
    sdxx->resource.type = CYHAL_RSC_INVALID;

    sdxx->pin_clk = CYHAL_NC_PIN_VALUE;
    sdxx->pin_cmd = CYHAL_NC_PIN_VALUE;
    obj->pin_data[0] = CYHAL_NC_PIN_VALUE;
    obj->pin_data[1] = CYHAL_NC_PIN_VALUE;
    obj->pin_data[2] = CYHAL_NC_PIN_VALUE;
    obj->pin_data[3] = CYHAL_NC_PIN_VALUE;
    obj->pin_data[4] = CYHAL_NC_PIN_VALUE;
    obj->pin_data[5] = CYHAL_NC_PIN_VALUE;
    obj->pin_data[6] = CYHAL_NC_PIN_VALUE;
    obj->pin_data[7] = CYHAL_NC_PIN_VALUE;
    obj->pin_card_detect = CYHAL_NC_PIN_VALUE;
    sdxx->pin_io_vol_sel = CYHAL_NC_PIN_VALUE;
    obj->pin_card_pwr_en = CYHAL_NC_PIN_VALUE;
    obj->pin_card_mech_write_prot = CYHAL_NC_PIN_VALUE;
    obj->pin_led_ctrl = CYHAL_NC_PIN_VALUE;
    obj->pin_emmc_reset = CYHAL_NC_PIN_VALUE;

    obj->cd_gpio_cb_enabled = false;
    sdxx->clock_owned = false;
    sdxx->low_voltage_io_set = false;

    cyhal_gpio_t data[8];
    memcpy(data, cfg->gpios.data, sizeof(data));

    cyhal_gpio_t cmd = cfg->gpios.cmd;
    cyhal_gpio_t clk = cfg->gpios.clk;
    cyhal_gpio_t card_detect = cfg->gpios.card_detect;
    cyhal_gpio_t io_volt_sel = cfg->gpios.io_volt_sel;
    cyhal_gpio_t card_pwr_en = cfg->gpios.card_pwr_en;
    cyhal_gpio_t card_mech_write_prot = cfg->gpios.card_mech_write_prot;
    cyhal_gpio_t led_ctrl = cfg->gpios.led_ctrl;
    cyhal_gpio_t emmc_reset = cfg->gpios.emmc_reset;

    obj->data_timeout_tout = _CYHAL_SDHC_TRANSFER_TIMEOUT;
    obj->data_timeout_card_clocks_user = 0;
    obj->data_timeout_auto_reconfig = false;

    /* Reserve SDHC */
    const cyhal_resource_pin_mapping_t *map = _CYHAL_UTILS_GET_RESOURCE(cmd, cyhal_pin_map_sdhc_card_cmd);

    if (NULL == map || NC == data[0])
    {
        // return now, nothing has been allocated so no need to proceed on
        return CYHAL_SDHC_RSLT_ERR_PIN;
    }

    cyhal_resource_inst_t rsc = { CYHAL_RSC_SDHC, map->block_num, map->channel_num };

    /* Reserve and configure GPIO pins */
    if (result == CY_RSLT_SUCCESS)
    {
        result = _cyhal_sdxx_setup_pin(
            sdxx, cmd, cyhal_pin_map_sdhc_card_cmd, CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_CMD,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_cmd),
            &(sdxx->pin_cmd), _CYHAL_SDHC_NOT_WEAK_FUNC, !sdxx->dc_configured);
    }

    if (result == CY_RSLT_SUCCESS)
    {
        result = _cyhal_sdxx_setup_pin(
            sdxx, clk, cyhal_pin_map_sdhc_clk_card, CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CLK_CARD,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_clk_card),
            &(sdxx->pin_clk), _CYHAL_SDHC_NOT_WEAK_FUNC, !sdxx->dc_configured);
    }

    for (uint8_t i = 0; (i < 4) && (CY_RSLT_SUCCESS == result); i++)
    {
        if (NC != data[i])
        {
            result = _cyhal_sdxx_setup_pin(sdxx, data[i], cyhal_pin_map_sdhc_card_dat_3to0,
                    CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_3TO0,
                    _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_dat_3to0), &(obj->pin_data[i]),
                    _CYHAL_SDHC_NOT_WEAK_FUNC, !sdxx->dc_configured);
        }
    }

#if _CYHAL_SDHC_DATA8_PRESENT
    for (uint8_t i = 4; (i < 8) && (CY_RSLT_SUCCESS == result); i++)
    {
        if (NC != data[i])
        {
            result = _cyhal_sdxx_setup_pin(sdxx, data[i], cyhal_pin_map_sdhc_card_dat_7to4,
                    CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_7TO4,
                    _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_dat_7to4), &(obj->pin_data[i]),
                    _CYHAL_SDHC_NOT_WEAK_FUNC, !sdxx->dc_configured);
        }
    }
#else
    if ((NC != data[4] || NC != data[5] || NC != data[6] || NC != data[7]) && (CY_RSLT_SUCCESS == result))
    {
        result = CYHAL_SDHC_RSLT_ERR_PIN;
    }
#endif

    if ((NC != card_detect) && (CY_RSLT_SUCCESS == result))
    {
#if _CYHAL_SDHC_CARD_DETECT_PRESENT
        result = _cyhal_sdxx_setup_pin(sdxx, card_detect, cyhal_pin_map_sdhc_card_detect_n,
                CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DETECT_N,
                _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_detect_n), &(obj->pin_card_detect),
                _CYHAL_SDHC_CARD_DETECT, !sdxx->dc_configured);
#else
        result = CYHAL_SDHC_RSLT_ERR_PIN;
#endif
    }

    if ((NC != io_volt_sel) && (CY_RSLT_SUCCESS == result))
    {
#if _CYHAL_SDHC_IO_VOLT_SEL_PRESENT
        result = _cyhal_sdxx_setup_pin(sdxx, io_volt_sel, cyhal_pin_map_sdhc_io_volt_sel,
            CYHAL_PIN_MAP_DRIVE_MODE_SDHC_IO_VOLT_SEL,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_io_volt_sel), &(sdxx->pin_io_vol_sel),
            _CYHAL_SDHC_CARD_IO_VOLTAGE, !sdxx->dc_configured);
#else
        result = _cyhal_sdxx_setup_pin(sdxx, io_volt_sel, NULL,
            CY_GPIO_DM_STRONG_IN_OFF,
            0, &(sdxx->pin_io_vol_sel),
            _CYHAL_SDHC_CARD_IO_VOLTAGE, !sdxx->dc_configured);
#endif
    }

    if ((NC != card_pwr_en) && (CY_RSLT_SUCCESS == result))
    {
#if _CYHAL_SDHC_CARD_IF_PWR_EN_PRESENT
        result = _cyhal_sdxx_setup_pin(sdxx, card_pwr_en, cyhal_pin_map_sdhc_card_if_pwr_en,
            CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_IF_PWR_EN,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_if_pwr_en), &(obj->pin_card_pwr_en), _CYHAL_SDHC_CARD_VDD,
            !sdxx->dc_configured);
#else
        result = CYHAL_SDHC_RSLT_ERR_PIN;
#endif
    }

    if ((NC != card_mech_write_prot) && (CY_RSLT_SUCCESS == result))
    {
#if _CYHAL_SDHC_CARD_WRITE_PROT_PRESENT
        result = _cyhal_sdxx_setup_pin(sdxx, card_mech_write_prot, cyhal_pin_map_sdhc_card_mech_write_prot,
            CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_MECH_WRITE_PROT,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_mech_write_prot), &(obj->pin_card_mech_write_prot),
            _CYHAL_SDHC_CARD_MECH_WRITE_PROTECT, !sdxx->dc_configured);
#else
        result = CYHAL_SDHC_RSLT_ERR_PIN;
#endif
    }

    if ((NC != led_ctrl) && (CY_RSLT_SUCCESS == result))
    {
#if _CYHAL_SDHC_LED_CTRL_PRESENT
        result = _cyhal_sdxx_setup_pin(sdxx, led_ctrl, cyhal_pin_map_sdhc_led_ctrl,
            CYHAL_PIN_MAP_DRIVE_MODE_SDHC_LED_CTRL,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_led_ctrl), &(obj->pin_led_ctrl), _CYHAL_SDHC_NOT_WEAK_FUNC, !sdxx->dc_configured);
#else
        result = CYHAL_SDHC_RSLT_ERR_PIN;
#endif
    }

    if ((NC != emmc_reset) && (CY_RSLT_SUCCESS == result))
    {
#if _CYHAL_SDHC_CARD_EMMC_RESET_PRESENT
        result = _cyhal_sdxx_setup_pin(sdxx, emmc_reset, cyhal_pin_map_sdhc_card_emmc_reset_n,
            CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_EMMC_RESET_N,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_emmc_reset_n), &(obj->pin_emmc_reset),
            _CYHAL_SDHC_NOT_WEAK_FUNC, !sdxx->dc_configured);
#else
        result = CYHAL_SDHC_RSLT_ERR_PIN;
#endif
    }

    if (CY_RSLT_SUCCESS == result)
    {
        /* Clock was not provided, so allocate one */
        if (cfg->clock == NULL)
        {
            result = _cyhal_utils_allocate_clock(&(sdxx->clock), &rsc, CYHAL_CLOCK_BLOCK_PERIPHERAL_8BIT, true);

            if (CY_RSLT_SUCCESS == result)
            {
                sdxx->clock_owned = true;
                result = _cyhal_utils_set_clock_frequency2(&(sdxx->clock), MAX_FREQUENCY, &CYHAL_CLOCK_TOLERANCE_5_P);
            }

            if (CY_RSLT_SUCCESS == result && !cyhal_clock_is_enabled(&(sdxx->clock)))
            {
                result = cyhal_clock_set_enabled(&(sdxx->clock), true, true);
            }
        }
        else
        {
            if (cfg->clock->block == CYHAL_CLOCK_BLOCK_HF)
            {
                sdxx->clock = *cfg->clock;
                obj->bus_frequency_hz = cyhal_clock_get_frequency(&(sdxx->clock));
            }
            if ((cfg->clock->block != CYHAL_CLOCK_BLOCK_HF) || (obj->bus_frequency_hz == 0))
            {
                result = CYHAL_SDHC_RSLT_ERR_CLOCK;
            }
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        if (sdxx->dc_configured)
        {
            sdxx->resource = *(cfg->resource);
        }
        else
        {
            result = cyhal_hwmgr_reserve(&rsc);
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        sdxx->resource = rsc;
        sdxx->base = _CYHAL_SDHC_BASE_ADDRESSES[sdxx->resource.block_num];
        sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
        #if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
        _cyhal_sdxx_semaphore_status[sdxx->resource.block_num] = _CYHAL_SDXX_SEMA_NOT_INITED;
        #endif /* defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE) */

        /* Enable the SDHC block */
        Cy_SD_Host_Enable(sdxx->base);

        sdxx->emmc = cfg->host_config->emmc;
        sdxx->context.cardType = CY_SD_HOST_NOT_EMMC;

        sdxx->irq_cause = 0UL;
        sdxx->callback_data.callback = NULL;
        sdxx->callback_data.callback_arg = NULL;
        _cyhal_sdxx_config_structs[sdxx->resource.block_num] = sdxx;

        _cyhal_system_irq_t irqn = _CYHAL_SDHC_IRQ_N[sdxx->resource.block_num];
        _cyhal_irq_register(irqn, CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_sdhc_irq_handler);
        _cyhal_irq_enable(irqn);

        result = (cy_rslt_t)Cy_SD_Host_Init(sdxx->base, cfg->host_config, &(sdxx->context));
    }

    if(result == CY_RSLT_SUCCESS)
    {
        sdxx->pm_transition_pending = false;
        sdxx->pm_callback_data.callback = &_cyhal_sdhc_syspm_callback;
        sdxx->pm_callback_data.states =
                (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE);
        sdxx->pm_callback_data.next = NULL;
        sdxx->pm_callback_data.args = sdxx;
        /* The CYHAL_SYSPM_BEFORE_TRANSITION mode cannot be ignored because the PM handler
            * calls the PDL deep-sleep callback that disables the block in this mode before transitioning.
            */
        sdxx->pm_callback_data.ignore_modes = (cyhal_syspm_callback_mode_t)0;

        _cyhal_syspm_register_peripheral_callback(&(sdxx->pm_callback_data));
    }

    if (result != CY_RSLT_SUCCESS)
    {
        cyhal_sdhc_free(obj);
    }

    return result;
}

cy_rslt_t cyhal_sdhc_init_hw(cyhal_sdhc_t *obj,
                        const cyhal_sdhc_config_t *config,
                        cyhal_gpio_t cmd,
                        cyhal_gpio_t clk,
                        cyhal_gpio_t data0,
                        cyhal_gpio_t data1,
                        cyhal_gpio_t data2,
                        cyhal_gpio_t data3,
                        cyhal_gpio_t data4,
                        cyhal_gpio_t data5,
                        cyhal_gpio_t data6,
                        cyhal_gpio_t data7,
                        cyhal_gpio_t card_detect,
                        cyhal_gpio_t io_volt_sel,
                        cyhal_gpio_t card_pwr_en,
                        cyhal_gpio_t card_mech_write_prot,
                        cyhal_gpio_t led_ctrl,
                        cyhal_gpio_t emmc_reset,
                        cyhal_clock_t *block_clk)
{
    CY_ASSERT(NULL != obj);

    cy_stc_sd_host_init_config_t sd_host_config = {
        .emmc = config->isEmmc,
        .dmaType = CY_SD_HOST_DMA_ADMA2,
        .enableLedControl = config->enableLedControl
    };

    const cyhal_sdhc_configurator_t cfg = {
        /* Resource will be reserved and assigned in HAL flow */
        .resource = NULL,
        .host_config = &sd_host_config,
        .card_config = NULL,
        .clock = block_clk,
        .gpios = {
            .cmd = cmd, .clk = clk, .data[0] = data0, .data[1] = data1, .data[2] = data2, .data[3] = data3,
            .data[4] = data4, .data[5] = data5, .data[6] = data6, .data[7] = data7, .card_detect = card_detect,
            .io_volt_sel = io_volt_sel, .card_pwr_en = card_pwr_en, .card_mech_write_prot = card_mech_write_prot,
            .led_ctrl = led_ctrl, .emmc_reset = emmc_reset
        }
    };

    obj->low_voltage_io_desired = config->lowVoltageSignaling;
    obj->bus_width = config->busWidth;

    return _cyhal_sdhc_init_common_hw(obj, &cfg);
}

static cy_rslt_t _cyhal_sdhc_init_card_common(cyhal_sdhc_t *obj, cy_stc_sd_host_sd_card_config_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->sdxx.base);

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    /* Initialize the card */
    cy_rslt_t result = (cy_rslt_t)Cy_SD_Host_InitCard(sdxx->base, cfg, &(sdxx->context));

    if (CY_RSLT_SUCCESS == result)
    {
        /* If clock is owned by driver, update SD Card frequency to be 25 Mhz. Otherwise, configure interface clock
        *   for passthrough (to be same as SDHC block source clock) */
        result = cyhal_sdhc_set_frequency(obj,
                        sdxx->clock_owned ? _CYHAL_SDXX_MHZ(25) : cyhal_clock_get_frequency(&(sdxx->clock)), true);
    }

    if ((CY_RSLT_SUCCESS == result) && (sdxx->emmc))
    {
        uint8_t ext_csd[_CYHAL_SDHC_EXTCSD_SIZE] = { 0UL };
        if (CY_RSLT_SUCCESS == (cy_rslt_t)Cy_SD_Host_GetExtCsd(sdxx->base, (uint32_t *)ext_csd, &(sdxx->context)))
        {
            /* Get GENERIC_CMD6_TIME [248] of the EXTCSD register */
            obj->emmc_generic_cmd6_time_ms =
                   (uint16_t) (_CYHAL_SDHC_EMMC_CMD6_TIMEOUT_MULT * ext_csd[_CYHAL_SDHC_EXTCSD_GENERIC_CMD6_TIME]);
        }
    }
    return result;
}

cy_rslt_t cyhal_sdhc_init_card(cyhal_sdhc_t *obj)
{
    cy_en_sd_host_card_type_t card_type;
    cy_en_sd_host_card_capacity_t card_capacity;
    uint32_t rca = 0;

    cy_stc_sd_host_sd_card_config_t sd_card_config = {
        .lowVoltageSignaling = obj->low_voltage_io_desired,
        .busWidth = _cyhal_sdhc_buswidth_hal_to_pdl(obj->bus_width),
        .cardType = &card_type,
        .rca = &rca,
        .cardCapacity = &card_capacity
    };

    return _cyhal_sdhc_init_card_common(obj, &sd_card_config);
}

cy_rslt_t cyhal_sdhc_init(cyhal_sdhc_t *obj,
                          const cyhal_sdhc_config_t *config,
                          cyhal_gpio_t cmd,
                          cyhal_gpio_t clk,
                          cyhal_gpio_t data0,
                          cyhal_gpio_t data1,
                          cyhal_gpio_t data2,
                          cyhal_gpio_t data3,
                          cyhal_gpio_t data4,
                          cyhal_gpio_t data5,
                          cyhal_gpio_t data6,
                          cyhal_gpio_t data7,
                          cyhal_gpio_t card_detect,
                          cyhal_gpio_t io_volt_sel,
                          cyhal_gpio_t card_pwr_en,
                          cyhal_gpio_t card_mech_write_prot,
                          cyhal_gpio_t led_ctrl,
                          cyhal_gpio_t emmc_reset,
                          cyhal_clock_t *block_clk)
{
    cy_rslt_t result = cyhal_sdhc_init_hw(obj, config, cmd, clk, data0, data1, data2, data3, data4, data5, data6,
            data7, card_detect, io_volt_sel, card_pwr_en, card_mech_write_prot, led_ctrl, emmc_reset, block_clk);

    /* Initialize card */
    if (result == CY_RSLT_SUCCESS)
    {
        result = cyhal_sdhc_init_card(obj);
    }

    return result;
}

cy_rslt_t cyhal_sdhc_init_cfg(cyhal_sdhc_t *obj, const cyhal_sdhc_configurator_t *cfg)
{
    obj->low_voltage_io_desired = cfg->card_config->lowVoltageSignaling;
    obj->bus_width = _cyhal_sdhc_buswidth_pdl_to_hal(cfg->card_config->busWidth);

    return _cyhal_sdhc_init_common_hw(obj, cfg);
}

void cyhal_sdhc_free(cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    if (NULL != sdxx->base)
    {
        _cyhal_system_irq_t irqn = _CYHAL_SDHC_IRQ_N[sdxx->resource.block_num];
        _cyhal_irq_free(irqn);
        #if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
        if (_CYHAL_SDXX_SEMA_NOT_INITED != _cyhal_sdxx_semaphore_status[sdxx->resource.block_num])
        {
            cy_rtos_deinit_semaphore(&(_cyhal_sdxx_semaphore_xfer_done[sdxx->resource.block_num]));
            _cyhal_sdxx_semaphore_status[sdxx->resource.block_num] = _CYHAL_SDXX_SEMA_NOT_INITED;
        }
        #endif /* CY_RTOS_AWARE or COMPONENT_RTOS_AWARE defined */

        Cy_SD_Host_DeInit(sdxx->base);
        _cyhal_sdxx_config_structs[sdxx->resource.block_num] = NULL;
        sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;

        if (!sdxx->dc_configured)
        {
            cyhal_hwmgr_free(&(sdxx->resource));
        }
        sdxx->base = NULL;

        _cyhal_syspm_unregister_peripheral_callback(&(sdxx->pm_callback_data));
    }

    if (sdxx->resource.type != CYHAL_RSC_INVALID)
    {
        sdxx->resource.type = CYHAL_RSC_INVALID;
    }

    if (sdxx->clock_owned)
    {
        cyhal_clock_free(&(sdxx->clock));
        sdxx->clock_owned = false;
    }

    if (!sdxx->dc_configured)
    {
        /* Free pins */
        _cyhal_utils_release_if_used(&(sdxx->pin_cmd));
        _cyhal_utils_release_if_used(&(sdxx->pin_clk));
        #if _CYHAL_SDHC_DATA8_PRESENT
            const uint8_t max_idx = 8;
        #else
            const uint8_t max_idx = 4;
        #endif
        for (uint8_t i = 0; i < max_idx; i++)
        {
            _cyhal_utils_release_if_used(&(obj->pin_data[i]));
        }
    }

    #if _CYHAL_SDHC_CARD_DETECT_PRESENT
    if ((obj->cd_gpio_cb_enabled) && (CYHAL_NC_PIN_VALUE != obj->pin_card_detect))
    {
        cyhal_gpio_enable_event(obj->pin_card_detect, CYHAL_GPIO_IRQ_BOTH, CYHAL_ISR_PRIORITY_DEFAULT, false);
        cyhal_gpio_register_callback(obj->pin_card_detect, NULL);
        obj->cd_gpio_cb_enabled = false;
    }
    if (!sdxx->dc_configured)
    {
        _cyhal_utils_release_if_used(&(obj->pin_card_detect));
    }
    #endif

    if (!sdxx->dc_configured)
    {
    /* io_vol_sel may have been used with GPIO pin */
        _cyhal_utils_release_if_used(&(sdxx->pin_io_vol_sel));

    #if _CYHAL_SDHC_CARD_IF_PWR_EN_PRESENT
        _cyhal_utils_release_if_used(&(obj->pin_card_pwr_en));
    #endif

    #if _CYHAL_SDHC_CARD_WRITE_PROT_PRESENT
        _cyhal_utils_release_if_used(&(obj->pin_card_mech_write_prot));
    #endif

    #if _CYHAL_SDHC_LED_CTRL_PRESENT
        _cyhal_utils_release_if_used(&(obj->pin_led_ctrl));
    #endif

    #if _CYHAL_SDHC_CARD_EMMC_RESET_PRESENT
        _cyhal_utils_release_if_used(&(obj->pin_emmc_reset));
    #endif
    }
}

cy_rslt_t cyhal_sdhc_read(cyhal_sdhc_t *obj, uint32_t address, uint8_t *data, size_t *length)
{
    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    CY_ASSERT(_CYHAL_SDXX_NOT_RUNNING == sdxx->data_transfer_status);
    _cyhal_sdxx_setup_smphr(sdxx);
    cy_rslt_t ret = cyhal_sdhc_read_async(obj, address, data, length);
    /* Waiting for async operation to end */
    if (CY_RSLT_SUCCESS == ret)
    {
        ret = _cyhal_sdxx_waitfor_transfer_complete(sdxx);
    }
    if(CY_RSLT_SUCCESS != ret)
    {
        sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
    }
    return ret;
}

cy_rslt_t cyhal_sdhc_write(cyhal_sdhc_t *obj, uint32_t address, const uint8_t *data, size_t *length)
{
    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    CY_ASSERT(_CYHAL_SDXX_NOT_RUNNING == sdxx->data_transfer_status);
    _cyhal_sdxx_setup_smphr(sdxx);
    cy_rslt_t ret = cyhal_sdhc_write_async(obj, address, data, length);
    /* Waiting for async operation to end */
    if (CY_RSLT_SUCCESS == ret)
    {
        ret = _cyhal_sdxx_waitfor_transfer_complete(sdxx);
    }
    if(CY_RSLT_SUCCESS != ret)
    {
        sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
    }
    return ret;
}

cy_rslt_t cyhal_sdhc_erase(cyhal_sdhc_t *obj, uint32_t start_addr, size_t length, uint32_t timeout_ms)
{
    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    if (timeout_ms == 0)
    {
        timeout_ms = sdxx->emmc ? _CYHAL_SDHC_EMMC_TRIM_DELAY_MS : _CYHAL_SDHC_RETRY_TIMES;
    }
    if (sdxx->pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }
    if (0 == length)
    {
        return CYHAL_SDHC_RSLT_ERR_WRONG_PARAM;
    }

    cy_rslt_t ret = CY_RSLT_SUCCESS;
    cy_en_sd_host_erase_type_t eraseType = CY_SD_HOST_ERASE_ERASE;
    uint32_t cardStatus;

    if (sdxx->emmc)
    {
         eraseType = CY_SD_HOST_ERASE_TRIM;
    }

    /* First clear out the transfer and command complete statuses */
    Cy_SD_Host_ClearNormalInterruptStatus(sdxx->base, (CY_SD_HOST_XFER_COMPLETE | CY_SD_HOST_CMD_COMPLETE));

    if (sdxx->irq_cause & CYHAL_SDHC_CMD_COMPLETE)
    {
        /*  Enabling command complete interrupt mask if corresponding event was enabled by user
        *   _cyhal_sdhc_irq_handler will disable CY_SD_HOST_CMD_COMPLETE mask once interrupt
        *   is generated. */
        Cy_SD_Host_SetNormalInterruptMask(sdxx->base, Cy_SD_Host_GetNormalInterruptMask(sdxx->base) |
                CY_SD_HOST_CMD_COMPLETE);
    }

    ret = (cy_rslt_t)Cy_SD_Host_Erase(sdxx->base, start_addr, (start_addr + length - 1), eraseType, &(sdxx->context));

    if (CY_RSLT_SUCCESS == ret)
    {
        uint32_t time_used_ms;
        ret = (cy_rslt_t)_cyhal_sdxx_pollcmdcomplete(sdxx, &time_used_ms);
        timeout_ms = timeout_ms - time_used_ms;
    }
    if (CY_RSLT_SUCCESS == ret)
    {
        if (false == sdxx->emmc)
        {
            /* polling result */
            ret = CYHAL_SDHC_RSLT_ERR_ERASE_CMPLT_TIMEOUT;
            while(timeout_ms > 0)
            {
                cardStatus = Cy_SD_Host_GetCardStatus(sdxx->base, &(sdxx->context));
                if (((CY_SD_HOST_CARD_TRAN << CY_SD_HOST_CMD13_CURRENT_STATE) |
                    (1UL << CY_SD_HOST_CMD13_READY_FOR_DATA)) == cardStatus)
                {
                    ret = CY_RSLT_SUCCESS;
                    break;
                }
                cyhal_system_delay_us(_CYHAL_SDHC_FUJE_TIMEOUT_MS); /* The Fuje timeout for one block. */
                timeout_ms--;
            }
        }
        else
        {
            cyhal_system_delay_ms(timeout_ms);
        }
    }

    return ret;
}

cy_rslt_t cyhal_sdhc_read_async(cyhal_sdhc_t *obj, uint32_t address, uint8_t *data, size_t *length)
{
    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    if (sdxx->pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }

    cy_rslt_t ret;
    cy_stc_sd_host_write_read_config_t dataConfig;

    /* The pointer to data. */
    dataConfig.data = (uint32_t*)data;
    /* The address to write/read data on the card or eMMC. */
    dataConfig.address = address;
    /* The number of blocks to write/read. */
    dataConfig.numberOfBlocks = (uint32_t)*length;
    dataConfig.autoCommand = (1UL == (uint32_t)*length)
        ? CY_SD_HOST_AUTO_CMD_NONE
        : CY_SD_HOST_AUTO_CMD_AUTO;
    /* The timeout value for the transfer. */
    dataConfig.dataTimeout = obj->data_timeout_tout;
    /* For EMMC cards enable reliable write. */
    dataConfig.enReliableWrite = false;
    dataConfig.enableDma = true;

    /* First clear out the transfer and command complete statuses */
    Cy_SD_Host_ClearNormalInterruptStatus(sdxx->base, (CY_SD_HOST_XFER_COMPLETE | CY_SD_HOST_CMD_COMPLETE));

    ret = _cyhal_sdxx_prepare_for_transfer(sdxx);

    if (CY_RSLT_SUCCESS == ret)
    {
        // The PDL takes care of the cmd complete stage in sdhc mode so we can jump straight
        // to waiting for the xfer complete
        sdxx->data_transfer_status = _CYHAL_SDXX_WAIT_XFER_COMPLETE;
        ret = (cy_rslt_t)Cy_SD_Host_Read(sdxx->base, &dataConfig, &(sdxx->context));
        /* Read operation failed */
        if (CY_RSLT_SUCCESS != ret)
        {
            sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
        }
    }

    return ret;
}

cy_rslt_t cyhal_sdhc_write_async(cyhal_sdhc_t *obj, uint32_t address, const uint8_t *data, size_t *length)
{
    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    if (sdxx->pm_transition_pending)
    {
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;
    }

    cy_rslt_t ret;
    cy_stc_sd_host_write_read_config_t dataConfig;

    /* The pointer to data. */
    dataConfig.data = (uint32_t*)data;
    /* The address to write/read data on the card or eMMC. */
    dataConfig.address = address;
    /* The number of blocks to write/read. */
    dataConfig.numberOfBlocks = (uint32_t)*length;
    dataConfig.autoCommand = (1UL == (uint32_t)*length)
        ? CY_SD_HOST_AUTO_CMD_NONE
        : CY_SD_HOST_AUTO_CMD_AUTO;
    /* The timeout value for the transfer. */
    dataConfig.dataTimeout = obj->data_timeout_tout;
    /* For EMMC cards enable reliable write. */
    dataConfig.enReliableWrite = false;
    dataConfig.enableDma = true;

    /* First clear out the transfer and command complete statuses */
    Cy_SD_Host_ClearNormalInterruptStatus(sdxx->base, (CY_SD_HOST_XFER_COMPLETE | CY_SD_HOST_CMD_COMPLETE));

    ret = _cyhal_sdxx_prepare_for_transfer(sdxx);

    if (CY_RSLT_SUCCESS == ret)
    {
        // The PDL takes care of the cmd complete stage in sdhc mode so we can jump straight
        // to waiting for the xfer complete
        sdxx->data_transfer_status = _CYHAL_SDXX_WAIT_XFER_COMPLETE;
        ret = (cy_rslt_t)Cy_SD_Host_Write(sdxx->base, &dataConfig, &(sdxx->context));
        /* Write operation failed */
        if (CY_RSLT_SUCCESS != ret)
        {
            sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
        }
    }

    return ret;
}

bool cyhal_sdhc_is_busy(const cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);
    return _cyhal_sdhc_is_busy(&(obj->sdxx));
}

cy_rslt_t cyhal_sdhc_abort_async(cyhal_sdhc_t *obj)
{
    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    cy_rslt_t ret = (cy_rslt_t)Cy_SD_Host_AbortTransfer(sdxx->base, &(sdxx->context));
    if (CY_RSLT_SUCCESS == ret)
    {
        sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
    }
    return ret;
}

void cyhal_sdhc_register_callback(cyhal_sdhc_t *obj, cyhal_sdhc_event_callback_t callback, void *callback_arg)
{
    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    sdxx->callback_data.callback = (cy_israddress) callback;
    sdxx->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
}

void cyhal_sdhc_enable_event(cyhal_sdhc_t *obj, cyhal_sdhc_event_t event, uint8_t intr_priority, bool enable)
{
    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    uint32_t interruptMask = Cy_SD_Host_GetNormalInterruptMask(sdxx->base);

    _cyhal_system_irq_t irqn = _CYHAL_SDHC_IRQ_N[sdxx->resource.block_num];
    _cyhal_irq_set_priority(irqn, intr_priority);
    uint32_t map_count = sizeof(_cyhal_sdhc_event_map) / sizeof(uint32_t);

    /* Specific interrupt */
    if ((uint32_t) event < (uint32_t) CYHAL_SDHC_ALL_INTERRUPTS)
    {
        for (uint8_t i = 1; i < map_count; i++)
        {
            if ((_cyhal_sdhc_event_map[i] & (uint32_t) event) != 0)
            {
                if (enable)
                    interruptMask |= ((uint32_t)1 << (i - 1));
                else
                    interruptMask &= ~((uint32_t)1 << (i - 1));
            }
        }
    }
    /* All interrupts */
    else
    {
        interruptMask = (enable) ? CYHAL_SDHC_ALL_INTERRUPTS : 0;
    }

    sdxx->irq_cause = interruptMask;
    /*  CY_SD_HOST_CMD_COMPLETE and CY_SD_HOST_XFER_COMPLETE cannot be always enabled because of SD Host driver limitations.
    *   SDHC HAL transfer APIs are taking care of enabling these statuses. CY_SD_HOST_CMD_COMPLETE is only
    *   enabled if user callback is enabled while CY_SD_HOST_XFER_COMPLETE is enabled by transfer API regardless it was enabled
    *   by user or not. */
    interruptMask &= ((uint32_t) ~CY_SD_HOST_CMD_COMPLETE) & ((uint32_t) ~CY_SD_HOST_XFER_COMPLETE);
    Cy_SD_Host_SetNormalInterruptMask(sdxx->base, interruptMask);
}

bool cyhal_sdhc_is_card_inserted(const cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->sdxx.base);
    return Cy_SD_Host_IsCardConnected(obj->sdxx.base);
}

bool cyhal_sdhc_is_card_mech_write_protected(const cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->sdxx.base);
    return Cy_SD_Host_IsWpSet(obj->sdxx.base);
}

cy_rslt_t cyhal_sdhc_get_block_count(cyhal_sdhc_t *obj, uint32_t * block_count)
{
    CY_ASSERT(NULL != obj);

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    cy_rslt_t result = CYHAL_SDHC_RSLT_ERR_BLOCK_COUNT_GET_FAILURE;

    if (CY_SD_HOST_SUCCESS == Cy_SD_Host_GetBlockCount(sdxx->base, block_count, &(sdxx->context)))
    {
        result = CY_RSLT_SUCCESS;
    }

    return result;
}

cy_rslt_t cyhal_sdhc_set_frequency(cyhal_sdhc_t *obj, uint32_t hz, bool negotiate)
{
    CY_ASSERT(NULL != obj);
    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    cy_rslt_t result = CYHAL_SDHC_RSLT_ERR_SET_FREQ;
    if (NULL != sdxx->base)
    {
        if ((sdxx->emmc) && (_CYHAL_SDHC_EMMC_MAX_SUP_FREQ_HZ < hz))
        {
            /* Maximal supported frequency for eMMC for current implementation is exceeded */
            return CYHAL_SDHC_RSLT_ERR_UNSUPPORTED;
        }

        /*  Assigning for desired freq as for now and this variable
         *  will be updated with achieved freq. */
        uint32_t actual_freq = hz;
        result = _cyhal_sdxx_sdcardchangeclock(sdxx, &actual_freq, sdxx->low_voltage_io_set, negotiate);
        if (CY_RSLT_SUCCESS == result)
        {
            obj->bus_frequency_hz = actual_freq;
            if (obj->data_timeout_auto_reconfig && (0 != obj->data_timeout_card_clocks_user))
            {
                /* User have data timeout configured, we need to reconfigure it according to new card clock */
                result = cyhal_sdhc_set_data_read_timeout(obj, obj->data_timeout_card_clocks_user, true);
            }
        }
    }
    return result;
}

uint32_t cyhal_sdhc_get_frequency(cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);
    return obj->bus_frequency_hz;
}

cy_rslt_t cyhal_sdhc_set_data_read_timeout(cyhal_sdhc_t *obj, uint32_t timeout, bool auto_reconfigure)
{
    CY_ASSERT(NULL != obj);

    uint32_t current_card_clock = cyhal_sdhc_get_frequency(obj);

    /* TMCLK works on 1 MHz in current block implementation if corresponding HF clock is 100 MHz.
    *  This is defined in registers (TOUT_CLK_FREQ[5:0] = 1 and TOUT_CLK_UNIT[7] = 1).  */
    float tout_clk_period_us = _CYHAL_SDHC_EXPECTED_BASE_CLK_FREQ_HZ / (float)obj->block_source_freq_hz;

    uint32_t user_needs_us = (((uint64_t)timeout * 1000000) + current_card_clock - 1) / current_card_clock;

    /* Timeout range from 0x0 to 0xE is valid for CAT1 which corresponds to
    * TMCLK x 2^13 for 0, TMCLK x 2^14 for 1, ..., TMCLK x 2^27 for 0xE. 0xF is reserved. */
    const uint8_t tout_clk_power_base = _CYHAL_SDHC_TOUT_TMCLK_POW_MIN;
    for (uint8_t tmclk_power = tout_clk_power_base; tmclk_power <= _CYHAL_SDHC_TOUT_TMCLK_POW_MAX; tmclk_power++)
    {
        if (tout_clk_period_us * ((uint32_t)1 << tmclk_power) >= user_needs_us)
        {
            obj->data_timeout_tout = tmclk_power - tout_clk_power_base;
            obj->data_timeout_card_clocks_user = timeout;
            obj->data_timeout_auto_reconfig = auto_reconfigure;
            return CY_RSLT_SUCCESS;
        }
    }
    return CYHAL_SDHC_RSLT_ERR_TOUT_CFG;
}

cy_rslt_t cyhal_sdhc_config_data_transfer(cyhal_sdhc_t *obj, cyhal_sdhc_data_config_t *data_config)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != data_config);

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    CY_ASSERT(NULL != sdxx->base);

    if (NULL == data_config->data_ptr)
    {
        return CYHAL_SDHC_RSLT_ERR_WRONG_PARAM;
    }

    cy_stc_sd_host_data_config_t dataConfig = {
        .blockSize = data_config->block_size,
        .numberOfBlock = data_config->number_of_blocks,
        .enableDma = true,
        .autoCommand = (cy_en_sd_host_auto_cmd_t)data_config->auto_command,
        .read = data_config->is_read,
        /* .data is skipped to configure adma2 descriptor for it later */
        .dataTimeout = obj->data_timeout_tout,
        .enableIntAtBlockGap = false,
        .enReliableWrite = false
    };

    uint32_t length = data_config->block_size * data_config->number_of_blocks;

    sdxx->adma_descriptor_tbl[0] = (1UL << CY_SD_HOST_ADMA_ATTR_VALID_POS) | /* Attr Valid */
                            (1UL << CY_SD_HOST_ADMA_ATTR_END_POS) |   /* Attr End */
                            (0UL << CY_SD_HOST_ADMA_ATTR_INT_POS) |   /* Attr Int */
                            (CY_SD_HOST_ADMA_TRAN << CY_SD_HOST_ADMA_ACT_POS) |
                            (length << CY_SD_HOST_ADMA_LEN_POS);     /* Len */

    sdxx->adma_descriptor_tbl[1] = (uint32_t)data_config->data_ptr;

    /* The address of the ADMA descriptor table. */
    dataConfig.data = (uint32_t*)&sdxx->adma_descriptor_tbl[0];

    return (cy_rslt_t) Cy_SD_Host_InitDataTransfer(sdxx->base, &dataConfig);
}

cy_rslt_t cyhal_sdhc_send_cmd(cyhal_sdhc_t *obj, cyhal_sdhc_cmd_config_t *cmd_config)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cmd_config);

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    CY_ASSERT(NULL != sdxx->base);

    cy_rslt_t result = CY_RSLT_SUCCESS;
    bool cmd_data_present = (NULL != cmd_config->data_config);

    cy_stc_sd_host_cmd_config_t cmd = {
        .commandIndex = cmd_config->command_index,
        .commandArgument = cmd_config->command_argument,
        .enableCrcCheck = cmd_config->enable_crc_check,
        .enableAutoResponseErrorCheck = false,
        .respType = (cy_en_sd_host_response_type_t)cmd_config->response_type,
        .enableIdxCheck = cmd_config->enable_idx_check,
        .dataPresent = cmd_data_present,
        .cmdType = (cy_en_sd_host_cmd_type_t)cmd_config->command_type
    };

    /* First clear out the transfer and command complete statuses */
    Cy_SD_Host_ClearNormalInterruptStatus(sdxx->base, (CY_SD_HOST_XFER_COMPLETE | CY_SD_HOST_CMD_COMPLETE));

    if (cmd_data_present)
    {
        result = _cyhal_sdxx_prepare_for_transfer(sdxx);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        if (cmd_data_present)
        {
            /* Data will be transfered in scope of this command, so setting _CYHAL_SDXX_WAIT_BOTH (cmd and data)
            *  and setting up xfer complete semaphore */
            sdxx->data_transfer_status = _CYHAL_SDXX_WAIT_BOTH;
            _cyhal_sdxx_setup_smphr(sdxx);
        }
        else
        {
            /* No data is transfered in this command, just waiting for cmd to complete */
            sdxx->data_transfer_status = _CYHAL_SDXX_WAIT_CMD_COMPLETE;
        }
        result = (cy_rslt_t)Cy_SD_Host_SendCommand(sdxx->base, &cmd);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = (cy_rslt_t)_cyhal_sdxx_pollcmdcomplete(sdxx, NULL);
    }

    if (CY_RSLT_SUCCESS != result)
    {
        /* Transfer failed */
        sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
    }

    return result;
}

cy_rslt_t cyhal_sdhc_get_response(cyhal_sdhc_t *obj, uint32_t *response, bool large_response)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->sdxx.base);
    CY_ASSERT(NULL != response);
    return (cy_rslt_t)Cy_SD_Host_GetResponse(obj->sdxx.base, response, large_response);
}

cy_rslt_t cyhal_sdhc_wait_transfer_complete(cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->sdxx.base);
    return _cyhal_sdxx_waitfor_transfer_complete(&(obj->sdxx));
}

static cy_rslt_t _cyhal_sdxx_io_volt_switch_seq(SDHC_Type *base)
{
    CY_ASSERT(NULL != base);

    uint32_t p_state;
    cy_rslt_t result = CY_RSLT_SUCCESS;

    /* Disable providing the SD Clock. */
    Cy_SD_Host_DisableSdClk(base);

    p_state = Cy_SD_Host_GetPresentState(base) & SDHC_CORE_PSTATE_REG_DAT_3_0_Msk;

    /* Check DAT[3:0]. */
    if (0UL == p_state)
    {
        /* Switch the bus to 1.8 V (Set the IO_VOLT_SEL pin to low)*/
        Cy_SD_Host_ChangeIoVoltage(base, CY_SD_HOST_IO_VOLT_1_8V);

        /* Wait 10 ms to 1.8 voltage regulator to be stable. */
        cyhal_system_delay_ms(_CYHAL_SDHC_1_8_REG_STABLE_TIME_MS);

        /* Check the 1.8V signaling enable. */
        if (true == _FLD2BOOL(SDHC_CORE_HOST_CTRL2_R_SIGNALING_EN,
                            SDHC_CORE_HOST_CTRL2_R(base)))
        {
            /* Enable providing the SD Clock. */
            Cy_SD_Host_EnableSdClk(base);

            /* Wait for the stable CLK */
            cyhal_system_delay_ms(CY_SD_HOST_CLK_RAMP_UP_TIME_MS);

            p_state = Cy_SD_Host_GetPresentState(base) & SDHC_CORE_PSTATE_REG_DAT_3_0_Msk;

            /* Check DAT[3:0]. */
            if (SDHC_CORE_PSTATE_REG_DAT_3_0_Msk != p_state)
            {
                result = (cy_rslt_t)CY_SD_HOST_ERROR;
            }
        }
        else
        {
            result = (cy_rslt_t)CY_SD_HOST_ERROR;
        }
    }
    else
    {
        result = (cy_rslt_t)CY_SD_HOST_ERROR;
    }

    return result;
}

/* Ncc - is time, needed to wait after certain commands before issuing next cmd.
*  Ncc is 8 clock cycles which for 400 kHz is 20 us */
static inline void _cyhal_sdhc_wait_ncc_time_at_400khz(void)
{
    cyhal_system_delay_us(20);
}

static cy_rslt_t _cyhal_sdhc_io_volt_negotiate(cyhal_sdhc_t *obj, cyhal_sdhc_io_voltage_t io_voltage)
{
    /* GO_IDLE (CMD0) command is issued in scope of Cy_SD_Host_SelBusVoltage, which resets
    *  SD bus to 1 bit bus width and 400 khz on the SD card side. Preparing host side for that. */

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    /* 1 bit data bus width */
    cy_rslt_t result = cyhal_sdhc_set_bus_width(obj, 1, true);

    if (CY_RSLT_SUCCESS == result)
    {
        /* 400 khz sd bus clock */
        result = cyhal_sdhc_set_frequency(obj, 400000, false);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        bool voltage_1v8 = (io_voltage == CYHAL_SDHC_IO_VOLTAGE_1_8V);
        result = (cy_rslt_t)Cy_SD_Host_SelBusVoltage(sdxx->base, voltage_1v8, &(sdxx->context));
        /* Card is expected to be in "ready" state now */
    }

    if (CY_RSLT_SUCCESS == result)
    {
        /* GetCid (CMD2) will switch card from "ready" state to "ident" */
        uint32_t cid_reg[4];  /* The Device Identification register. */
        result = (cy_rslt_t)Cy_SD_Host_GetCid(sdxx->base, cid_reg);
        _cyhal_sdhc_wait_ncc_time_at_400khz();
    }

    if (CY_RSLT_SUCCESS == result)
    {
        /* Cy_SD_Host_GetRca (CMD3) will switch card from "ident" state to "stand-by" state */
        sdxx->context.RCA = Cy_SD_Host_GetRca(sdxx->base);
        _cyhal_sdhc_wait_ncc_time_at_400khz();

        /* CMD7 will switch card from "stand-by" state to "transfer" state */
        cyhal_sdhc_cmd_config_t cmd = {
            .command_index = 7,
            .command_argument = sdxx->context.RCA << _CYHAL_SDHC_RCA_SHIFT,
            .enable_crc_check = false,
            .response_type = CYHAL_SDHC_RESPONSE_LEN_48B,
            .enable_idx_check = false,
            .command_type = CYHAL_SDHC_CMD_NORMAL,
            .data_config = NULL
        };

        result = cyhal_sdhc_send_cmd(obj, &cmd);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        _cyhal_sdhc_wait_ncc_time_at_400khz();
        result = _cyhal_sdxx_waitfor_transfer_complete(sdxx);
    }

    return result;
}

typedef struct
{
    en_hsiom_sel_t      clk;
    en_hsiom_sel_t      cmd;
    #if _CYHAL_SDHC_DATA8_PRESENT
    en_hsiom_sel_t      data[8];
    #else
    en_hsiom_sel_t      data[4];
    #endif
} _cyhal_sdhc_saved_lines_hsiom_t;

/* power cycle config single pin */
static void _cyhal_sdhc_pc_config_single_pin(cyhal_gpio_t *gpio_ptr, en_hsiom_sel_t *hsiom_ptr, bool set_line_low)
{
    GPIO_PRT_Type* port;
    uint8_t pin;

    cyhal_gpio_t gpio = *gpio_ptr;
    if (NC != gpio)
    {
        port = CYHAL_GET_PORTADDR(gpio);
        pin = (uint8_t)CYHAL_GET_PIN(gpio);
        if(set_line_low)
        {
            /* Switching HSIOM to GPIO and set pin to low state */
            *hsiom_ptr = Cy_GPIO_GetHSIOM(port, pin);
            Cy_GPIO_Clr(port, pin);
            Cy_GPIO_SetHSIOM(port, pin, HSIOM_SEL_GPIO);
        }
        else
        {
            /* Restore pin's HSIOM configuration for SDHC block signals */
            Cy_GPIO_SetHSIOM(port, pin, *hsiom_ptr);
        }
    }
}

/* Per SD Spec, during card power down, DAT, CMD and CLK lines should be disconnected or driven to logical 0
*  by the host to avoid operating current being drawn through the signal lines.
*  Lines are set low if set_lines_low true, pins configuration resored if set_lines_low false */
static void _cyhal_sdhc_power_cycle_config_lines(cyhal_sdhc_t *obj, _cyhal_sdhc_saved_lines_hsiom_t *pins_cfg,
    bool set_lines_low)
{
    _cyhal_sdhc_pc_config_single_pin(&(obj->sdxx.pin_clk), &pins_cfg->clk, set_lines_low);
    _cyhal_sdhc_pc_config_single_pin(&(obj->sdxx.pin_cmd), &pins_cfg->cmd, set_lines_low);
    for(size_t i = 0; i < sizeof(pins_cfg->data)/sizeof(pins_cfg->data[0]); ++i)
    {
        _cyhal_sdhc_pc_config_single_pin(&(obj->pin_data[i]), &(pins_cfg->data[i]), set_lines_low);
    }
}

static cy_rslt_t _cyhal_sdhc_card_power_cycle(cyhal_sdhc_t *obj)
{
    /* To perform reliable SD card hard reset, Card VDD should drop to below 0.5V for at least 1 ms */
    if (NC == obj->pin_card_pwr_en)
    {
        /* card_pwr_en needs to be provided in order to control card VDD */
        return CYHAL_SDHC_RSLT_ERR_PIN;
    }

    _cyhal_sdhc_saved_lines_hsiom_t pins_cfg;

    /* Drive signal lines logic 0 to avoid card being powered through signal lines */
    _cyhal_sdhc_power_cycle_config_lines(obj, &pins_cfg, true);
    /* Power down the card */
    cyhal_sdhc_enable_card_power(obj, false);
    /* Waiting for 1 ms per spec */
    cyhal_system_delay_us(1000);
    /* Restore signals configuration */
    _cyhal_sdhc_power_cycle_config_lines(obj, &pins_cfg, false);
    /* Power up the card */
    cyhal_sdhc_enable_card_power(obj, true);
    cyhal_system_delay_ms(_CYHAL_SDHC_PWR_RAMP_UP_TIME_MS);

    return CY_RSLT_SUCCESS;
}

static cy_rslt_t _cyhal_sdxx_set_io_voltage(_cyhal_sdxx_t *sdxx, cyhal_sdxx_io_voltage_t io_voltage,
                                           _cyhal_sdxx_io_switch_action_t io_switch_type)
{
    CY_ASSERT(NULL != sdxx);
    CY_ASSERT(NULL != sdxx->base);

    if ((!sdxx->is_sdio && CY_SD_HOST_SD != sdxx->context.cardType) &&
            (_CYHAL_SDXX_IO_VOLT_ACTION_NONE != io_switch_type))
    {
        /* For SDHC, Negotiation or Voltage switch is not supported when eMMC used */
        return CYHAL_SDHC_RSLT_ERR_UNSUPPORTED;
    }
    if (sdxx->is_sdio && (_CYHAL_SDXX_IO_VOLT_ACTION_NEGOTIATE == io_switch_type))
    {
        /* For SDIO, Negotiation is not supported */
        return CYHAL_SDIO_RSLT_ERR_UNSUPPORTED;
    }

    cy_rslt_t result = CY_RSLT_SUCCESS;

    switch (io_switch_type)
    {
        /* Not supported by current SDIO HAL implementation */
        case _CYHAL_SDXX_IO_VOLT_ACTION_NEGOTIATE:
        {
            cyhal_sdhc_t *sdhc_obj = (cyhal_sdhc_t *) sdxx->obj;

            /*  Bus width and card frequency settings are initialized to default during negotiation.
            *   Saving the parameters to restore them after I/O switch is done. */
            uint8_t sd_bus_width_before_switch = cyhal_sdhc_get_bus_width(sdhc_obj);
            uint32_t sd_freq_before_switch = cyhal_sdhc_get_frequency(sdhc_obj);

            /*  Once the card enters 1.8V signaling mode, it cannot be switched back to 3.3V signaling without power cycle. */
            if ((sdxx->low_voltage_io_set) && (_CYHAL_SDXX_IO_VOLTAGE_3_3V == io_voltage))
            {
                result = _cyhal_sdhc_card_power_cycle(sdhc_obj);
                if (CY_RSLT_SUCCESS == result)
                {
                    sdhc_obj->low_voltage_io_desired = false;
                    result = cyhal_sdhc_init_card(sdhc_obj);
                }
            }
            else
            {
                result = _cyhal_sdhc_io_volt_negotiate(sdhc_obj, (cyhal_sdhc_io_voltage_t)io_voltage);
            }

            /* Return back bus width and frequency regardless of volt select change status */
            (void)cyhal_sdhc_set_bus_width(sdhc_obj, sd_bus_width_before_switch, true);
            (void)cyhal_sdhc_set_frequency(sdhc_obj, sd_freq_before_switch, true);
            break;
        }

        case _CYHAL_SDXX_IO_VOLT_ACTION_SWITCH_SEQ_ONLY:
            if (_CYHAL_SDXX_IO_VOLTAGE_1_8V == io_voltage)
            {
                result = _cyhal_sdxx_io_volt_switch_seq(sdxx->base);
                if (CY_RSLT_SUCCESS != result)
                {
                    result = sdxx->is_sdio ? CYHAL_SDHC_RSLT_ERR_IO_VOLT_SWITCH_SEQ : CYHAL_SDIO_RSLT_ERR_IO_VOLT_SWITCH_SEQ;
                }
                break;
            }
            Cy_SD_Host_ChangeIoVoltage(sdxx->base, (cy_en_sd_host_io_voltage_t)io_voltage);
            break;

        case _CYHAL_SDXX_IO_VOLT_ACTION_NONE:
            Cy_SD_Host_ChangeIoVoltage(sdxx->base, (cy_en_sd_host_io_voltage_t)io_voltage);
            break;

        default:
            /* Illegal io_switch_type value provided */
            CY_ASSERT(false);
    }

    return result;
}

cy_rslt_t cyhal_sdhc_set_io_voltage(cyhal_sdhc_t *obj, cyhal_sdhc_io_voltage_t io_voltage, cyhal_sdhc_io_volt_action_type_t io_switch_type)
{
    CY_ASSERT(NULL != obj);

    if (NC == obj->sdxx.pin_io_vol_sel)
    {
        /* Need to have io_volt_sel pin configured in order to switch io voltage */
        return CYHAL_SDHC_RSLT_ERR_PIN;
    }

    return _cyhal_sdxx_set_io_voltage(&(obj->sdxx), (cyhal_sdxx_io_voltage_t)io_voltage,
            (_cyhal_sdxx_io_switch_action_t)io_switch_type);
}

cyhal_sdhc_io_voltage_t cyhal_sdhc_get_io_voltage(cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);
    return obj->sdxx.low_voltage_io_set ? CYHAL_SDHC_IO_VOLTAGE_1_8V : CYHAL_SDHC_IO_VOLTAGE_3_3V;
}

static inline bool _cyhal_sdhc_is_buswidth_correct(uint8_t sd_data_bits)
{
    return ((1 == sd_data_bits) || (4 == sd_data_bits) || (8 == sd_data_bits));
}

cy_rslt_t cyhal_sdhc_set_bus_width(cyhal_sdhc_t *obj, uint8_t bus_width, bool configure_card)
{
    CY_ASSERT(NULL != obj);

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    CY_ASSERT(NULL != sdxx->base);

    if (!_cyhal_sdhc_is_buswidth_correct(bus_width))
    {
        return CYHAL_SDHC_RSLT_ERR_WRONG_PARAM;
    }

    cy_rslt_t result;

    if (configure_card)
    {
        result = (cy_rslt_t)Cy_SD_Host_SetBusWidth(sdxx->base, _cyhal_sdhc_buswidth_hal_to_pdl(bus_width), &(sdxx->context));
        if ((CY_RSLT_SUCCESS == result) && (sdxx->emmc))
        {
            /* GENERIC_CMD6_TIME is maximum timeout for a SWITCH command (CMD6), that is called for eMMC in scope of
            *   Cy_SD_Host_SetBusWidth */
            cyhal_system_delay_ms(obj->emmc_generic_cmd6_time_ms);
        }
    }
    else
    {
        result = (cy_rslt_t)Cy_SD_Host_SetHostBusWidth(sdxx->base, _cyhal_sdhc_buswidth_hal_to_pdl(bus_width));
    }

    if (CY_RSLT_SUCCESS == result)
    {
        obj->bus_width = bus_width;
    }

    return result;
}

uint8_t cyhal_sdhc_get_bus_width(cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);
    return obj->bus_width;
}

void cyhal_sdhc_clear_errors(cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->sdxx.base);
    Cy_SD_Host_ClearErrorInterruptStatus(obj->sdxx.base, _CYHAL_SDHC_ALL_ERR_INTERRUPTS);
}

cyhal_sdhc_error_type_t cyhal_sdhc_get_last_command_errors(cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != obj->sdxx.base);
    return (cyhal_sdhc_error_type_t)Cy_SD_Host_GetErrorInterruptStatus(obj->sdxx.base);
}

void cyhal_sdhc_software_reset(cyhal_sdhc_t *obj)
{
    CY_ASSERT(NULL != obj);
    _cyhal_sdxx_reset(&(obj->sdxx));
}

cy_rslt_t cyhal_sdhc_enable_card_power(cyhal_sdhc_t *obj, bool enable)
{
    CY_ASSERT(NULL != obj);

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    CY_ASSERT(NULL != sdxx->base);

    if (NC == obj->pin_card_pwr_en)
    {
        /* Need to have card_pwr_en pin configured in order to switch card power state */
        return CYHAL_SDHC_RSLT_ERR_PIN;
    }

    if (enable)
    {
        Cy_SD_Host_EnableCardVoltage(sdxx->base);
    }
    else
    {
        Cy_SD_Host_DisableCardVoltage(sdxx->base);
    }
    return CY_RSLT_SUCCESS;
}

static cy_rslt_t _cyhal_sdio_init_common(cyhal_sdio_t *obj, const cyhal_sdio_configurator_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);
    CY_ASSERT(NULL != cfg->host_config);
    CY_ASSERT(NULL != cfg->card_config);

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);
    sdxx->obj = obj;
    sdxx->is_sdio = true;

    /* Configuration is provided by device configurator */
    sdxx->dc_configured = (cfg->resource != NULL);

    if ((sdxx->dc_configured) &&
            (cfg->host_config->emmc || cfg->host_config->dmaType != CY_SD_HOST_DMA_ADMA2 ||
             cfg->card_config->busWidth != CY_SD_HOST_BUS_WIDTH_4_BIT))
    {
        /*  emmc setting should be false for SDIO.
            Next settings are only supported by SDIO HAL:
                - DMA type : ADMA2
                - Data bus width : 4 bit
        */
        return CYHAL_SDIO_RSLT_ERR_UNSUPPORTED;
    }

    sdxx->resource.type = CYHAL_RSC_INVALID;
    sdxx->base = NULL;
    sdxx->pin_cmd = CYHAL_NC_PIN_VALUE;
    sdxx->pin_clk = CYHAL_NC_PIN_VALUE;
    obj->pin_data0 = CYHAL_NC_PIN_VALUE;
    obj->pin_data1 = CYHAL_NC_PIN_VALUE;
    obj->pin_data2 = CYHAL_NC_PIN_VALUE;
    obj->pin_data3 = CYHAL_NC_PIN_VALUE;
    sdxx->pin_io_vol_sel = CYHAL_NC_PIN_VALUE;

    sdxx->low_voltage_io_set = false;
    sdxx->clock_owned = false;

    cyhal_gpio_t cmd = cfg->gpios.cmd;
    cyhal_gpio_t clk = cfg->gpios.clk;
    cyhal_gpio_t data[4];
    memcpy(data, cfg->gpios.data, sizeof(cfg->gpios.data));

    cy_rslt_t result = _cyhal_sdxx_setup_pin(sdxx, cmd, cyhal_pin_map_sdhc_card_cmd,
        CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_CMD,
        _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_cmd), &(sdxx->pin_cmd), _CYHAL_SDHC_NOT_WEAK_FUNC,
        !sdxx->dc_configured);

    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_sdxx_setup_pin(sdxx, clk, cyhal_pin_map_sdhc_clk_card,
            CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CLK_CARD,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_clk_card), &(sdxx->pin_clk), _CYHAL_SDHC_NOT_WEAK_FUNC,
            !sdxx->dc_configured);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_sdxx_setup_pin(sdxx, data[0], cyhal_pin_map_sdhc_card_dat_3to0,
            CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_3TO0,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_dat_3to0), &(obj->pin_data0), _CYHAL_SDHC_NOT_WEAK_FUNC,
            !sdxx->dc_configured);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_sdxx_setup_pin(sdxx, data[1], cyhal_pin_map_sdhc_card_dat_3to0,
            CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_3TO0,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_dat_3to0), &(obj->pin_data1), _CYHAL_SDHC_NOT_WEAK_FUNC,
            !sdxx->dc_configured);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_sdxx_setup_pin(sdxx, data[2], cyhal_pin_map_sdhc_card_dat_3to0,
            CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_3TO0,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_dat_3to0), &(obj->pin_data2), _CYHAL_SDHC_NOT_WEAK_FUNC,
            !sdxx->dc_configured);
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_sdxx_setup_pin(sdxx, data[3], cyhal_pin_map_sdhc_card_dat_3to0,
            CYHAL_PIN_MAP_DRIVE_MODE_SDHC_CARD_DAT_3TO0,
            _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_card_dat_3to0), &(obj->pin_data3), _CYHAL_SDHC_NOT_WEAK_FUNC,
            !sdxx->dc_configured);
    }

    if (result == CY_RSLT_SUCCESS)
    {
        const cyhal_resource_pin_mapping_t *cmd_map = _CYHAL_UTILS_GET_RESOURCE(cmd, cyhal_pin_map_sdhc_card_cmd);
        cyhal_resource_inst_t sdhc = { CYHAL_RSC_SDHC, cmd_map->block_num, cmd_map->channel_num };

        if (cfg->clock == NULL)
        {
            result = _cyhal_utils_allocate_clock(&(sdxx->clock), &sdhc, CYHAL_CLOCK_BLOCK_PERIPHERAL_16BIT, true);
            if (CY_RSLT_SUCCESS == result)
            {
                sdxx->clock_owned = true;
                result = _cyhal_utils_set_clock_frequency2(&(sdxx->clock), MAX_FREQUENCY, &CYHAL_CLOCK_TOLERANCE_5_P);
            }
            if (CY_RSLT_SUCCESS == result && !cyhal_clock_is_enabled(&(sdxx->clock)))
            {
                result = cyhal_clock_set_enabled(&(sdxx->clock), true, true);
            }
        }
        else
        {
            if (cfg->clock->block == CYHAL_CLOCK_BLOCK_HF)
            {
                sdxx->clock = *cfg->clock;
                obj->frequencyhal_hz = cyhal_clock_get_frequency(&(sdxx->clock));
            }

            if ((cfg->clock->block != CYHAL_CLOCK_BLOCK_HF) || (obj->frequencyhal_hz == 0))
            {
                result = CYHAL_SDIO_RSLT_ERR_CLOCK;
            }
        }

        if (CY_RSLT_SUCCESS == result)
        {
            if (sdxx->dc_configured)
            {
                sdxx->resource = *(cfg->resource);
            }
            else
            {
                sdxx->resource = sdhc;
                result = cyhal_hwmgr_reserve(&sdhc);
            }
        }
    }

        if (result == CY_RSLT_SUCCESS)
        {
            sdxx->base = _CYHAL_SDHC_BASE_ADDRESSES[sdxx->resource.block_num];
            sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;

            /* Enable the SDHC block */
            Cy_SD_Host_Enable(sdxx->base);

        /* Configure SD Host to operate */
        result = (cy_rslt_t)Cy_SD_Host_Init(sdxx->base, cfg->host_config, &sdxx->context);

        /* Register SDIO Deep Sleep Callback */
        if (CY_RSLT_SUCCESS == result)
        {
            sdxx->context.cardType = CY_SD_HOST_SDIO;
            sdxx->pm_transition_pending = false;
            sdxx->pm_callback_data.callback = &_cyhal_sdio_syspm_callback;
            sdxx->pm_callback_data.states = (cyhal_syspm_callback_state_t)(CYHAL_SYSPM_CB_CPU_DEEPSLEEP | CYHAL_SYSPM_CB_SYSTEM_HIBERNATE);
            sdxx->pm_callback_data.next = NULL;
            sdxx->pm_callback_data.args = sdxx;
            /* The CYHAL_SYSPM_BEFORE_TRANSITION mode cannot be ignored because the PM handler
                * calls the PDL deep-sleep callback that disables the block in this mode before transitioning.
                */
            sdxx->pm_callback_data.ignore_modes = (cyhal_syspm_callback_mode_t)0;

            _cyhal_syspm_register_peripheral_callback(&(sdxx->pm_callback_data));
        }

        if (result == CY_RSLT_SUCCESS)
        {
            /* Don't enable any error interrupts for now */
            Cy_SD_Host_SetErrorInterruptMask(sdxx->base, 0UL);

            /* Clear all interrupts */
            Cy_SD_Host_ClearErrorInterruptStatus(sdxx->base, _CYHAL_SDIO_SET_ALL_INTERRUPTS_MASK);
            Cy_SD_Host_ClearNormalInterruptStatus(sdxx->base, _CYHAL_SDIO_SET_ALL_INTERRUPTS_MASK);

            sdxx->irq_cause = 0UL;
            obj->events    = 0UL;

            sdxx->callback_data.callback = NULL;
            sdxx->callback_data.callback_arg = NULL;
            _cyhal_sdxx_config_structs[sdxx->resource.block_num] = sdxx;

            #if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
            _cyhal_sdxx_semaphore_status[sdxx->resource.block_num] = _CYHAL_SDXX_SEMA_NOT_INITED;
            #endif /* defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE) */

            _cyhal_system_irq_t irqn = _CYHAL_SDHC_IRQ_N[sdxx->resource.block_num];
            _cyhal_irq_register(irqn, CYHAL_ISR_PRIORITY_DEFAULT, _cyhal_sdio_irq_handler);
            _cyhal_irq_enable(irqn);

            result = (cy_rslt_t)Cy_SD_Host_SetHostBusWidth(sdxx->base, CY_SD_HOST_BUS_WIDTH_4_BIT);
        }

        /* Change the host SD clock to 400 kHz */
        if (result == CY_RSLT_SUCCESS)
        {
            uint32_t freq = _CYHAL_SDIO_HOST_CLK_400K;
            result = _cyhal_sdxx_sdcardchangeclock(sdxx, &freq, sdxx->low_voltage_io_set, false);
            if (result == CY_RSLT_SUCCESS)
            {
                obj->frequencyhal_hz = freq;
                obj->block_size = _CYHAL_SDIO_64B_BLOCK;
            }
        }
    }

    if (result != CY_RSLT_SUCCESS)
    {
        cyhal_sdio_free(obj);
    }

    return result;
}

cy_rslt_t cyhal_sdio_init(cyhal_sdio_t *obj, cyhal_gpio_t cmd, cyhal_gpio_t clk, cyhal_gpio_t data0, cyhal_gpio_t data1,
        cyhal_gpio_t data2, cyhal_gpio_t data3)
{
    cy_en_sd_host_card_capacity_t card_capacity = CY_SD_HOST_SDSC;
    cy_en_sd_host_card_type_t card_type = CY_SD_HOST_NOT_EMMC;
    uint32_t rca = 0u;
    const cy_stc_sd_host_init_config_t host_config =
    {
        .emmc = false,
        .dmaType = CY_SD_HOST_DMA_ADMA2,
        .enableLedControl = false,
    };
    cy_stc_sd_host_sd_card_config_t card_config =
    {
        .lowVoltageSignaling = false,
        .busWidth = CY_SD_HOST_BUS_WIDTH_4_BIT,
        .cardType = &card_type,
        .rca = &rca,
        .cardCapacity = &card_capacity,
    };
    const cyhal_sdio_configurator_t cfg = {
        .resource = NULL,
        .host_config = &host_config,
        .card_config = &card_config,
        .clock = NULL,
        .gpios = {clk, cmd, { data0, data1, data2, data3 } }
    };
    return _cyhal_sdio_init_common(obj, &cfg);
}

void cyhal_sdio_free(cyhal_sdio_t *obj)
{
    CY_ASSERT(NULL != obj);

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    if (NULL != sdxx->base)
    {
        _cyhal_system_irq_t irqn = _CYHAL_SDHC_IRQ_N[sdxx->resource.block_num];
        _cyhal_irq_free(irqn);

        #if defined(CY_RTOS_AWARE) || defined(COMPONENT_RTOS_AWARE)
        if (_CYHAL_SDXX_SEMA_NOT_INITED != _cyhal_sdxx_semaphore_status[sdxx->resource.block_num])
        {
            cy_rtos_deinit_semaphore(&(_cyhal_sdxx_semaphore_xfer_done[sdxx->resource.block_num]));
            _cyhal_sdxx_semaphore_status[sdxx->resource.block_num] = _CYHAL_SDXX_SEMA_NOT_INITED;
        }
        #endif /* CY_RTOS_AWARE or COMPONENT_RTOS_AWARE defined */

        Cy_SD_Host_DeInit(sdxx->base);
        sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;

        if (!sdxx->dc_configured)
        {
            cyhal_hwmgr_free(&(sdxx->resource));
        }
        sdxx->base = NULL;

        _cyhal_sdxx_config_structs[sdxx->resource.block_num] = NULL;
        _cyhal_syspm_unregister_peripheral_callback(&(sdxx->pm_callback_data));
    }

    if (sdxx->resource.type != CYHAL_RSC_INVALID)
    {
        sdxx->resource.type = CYHAL_RSC_INVALID;
    }

    if (sdxx->clock_owned)
    {
        cyhal_clock_free(&(sdxx->clock));
        sdxx->clock_owned = false;
    }

    if (!sdxx->dc_configured)
    {
        /* Free pins */
        _cyhal_utils_release_if_used(&(sdxx->pin_clk));
        _cyhal_utils_release_if_used(&(sdxx->pin_cmd));
        _cyhal_utils_release_if_used(&obj->pin_data0);
        _cyhal_utils_release_if_used(&obj->pin_data1);
        _cyhal_utils_release_if_used(&obj->pin_data2);
        _cyhal_utils_release_if_used(&obj->pin_data3);
    }
}

cy_rslt_t cyhal_sdio_configure(cyhal_sdio_t *obj, const cyhal_sdio_cfg_t *config)
{
    cy_rslt_t result = CYHAL_SDIO_RSLT_ERR_CONFIG;

    if ((NULL == obj) || (config == NULL))
    {
        return CYHAL_SDIO_RSLT_ERR_BAD_PARAM;
    }

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    if (config->frequencyhal_hz != 0U)
    {
        uint32_t freq = config->frequencyhal_hz;
        result = _cyhal_sdxx_sdcardchangeclock(sdxx, &freq, sdxx->low_voltage_io_set, false);
        if (CY_RSLT_SUCCESS == result)
        {
            obj->frequencyhal_hz = freq;
        }
    }

    if (config->block_size != 0U)
    {
        /* No need to change anything in HW, because it will be overwritten
        *  in cyhal_sdio_bulk_transfer()/cyhal_sdio_transfer_async() functions.
        *  The HW block size will taken based on obj->block_size, which is
        *  updated here.
        */
        obj->block_size = config->block_size;
    }

    return result;
}

cy_rslt_t cyhal_sdio_send_cmd(cyhal_sdio_t *obj, cyhal_sdio_transfer_type_t direction, \
                              cyhal_sdio_command_t command, uint32_t argument, uint32_t* response)
{
    CY_UNUSED_PARAMETER(direction);
    if (NULL == obj)
    {
        return CYHAL_SDIO_RSLT_ERR_BAD_PARAM;
    }

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    if (sdxx->pm_transition_pending)
    {
        return CYHAL_SDIO_RSLT_ERR_PM_PENDING;
    }

    cy_rslt_t                   ret;
    cy_stc_sd_host_cmd_config_t cmd;
    uint32_t                    retry = _CYHAL_SDIO_TRANSFER_TRIES;

    /* Clear out the response */
    if ( response != NULL )
    {
        *response = 0UL;
    }

    do
    {
        /* First clear out the command complete and transfer complete statuses */
        Cy_SD_Host_ClearNormalInterruptStatus(sdxx->base, CY_SD_HOST_CMD_COMPLETE);

        /* Check if an error occurred on any previous transactions */
        if ( Cy_SD_Host_GetNormalInterruptStatus(sdxx->base) & CY_SD_HOST_ERR_INTERRUPT )
        {
            /* Reset the block if there was an error. Note a full reset usually
             * requires more time, but this short version is working quite well and
             * successfully clears out the error state.
             */
            Cy_SD_Host_ClearErrorInterruptStatus(sdxx->base, _CYHAL_SDIO_SET_ALL_INTERRUPTS_MASK);
            _cyhal_sdxx_reset(sdxx);
        }

        cmd.commandIndex                 = (uint32_t)command;
        cmd.commandArgument              = argument;
        cmd.enableCrcCheck               = true;
        cmd.enableAutoResponseErrorCheck = false;
        cmd.respType                     = CY_SD_HOST_RESPONSE_LEN_48;
        cmd.enableIdxCheck               = true;
        cmd.dataPresent                  = false;
        cmd.cmdType                      = CY_SD_HOST_CMD_NORMAL;

        if (sdxx->irq_cause & CYHAL_SDIO_CMD_COMPLETE)
        {
            /*  Enabling command complete interrupt mask if corresponding event was enabled by user
            *   _cyhal_sdio_irq_handler will disable CY_SD_HOST_CMD_COMPLETE mask once interrupt
            *   is generated. */
            Cy_SD_Host_SetNormalInterruptMask(sdxx->base, Cy_SD_Host_GetNormalInterruptMask(sdxx->base) |
                    CY_SD_HOST_CMD_COMPLETE);
        }

        ret = (cy_rslt_t)Cy_SD_Host_SendCommand(sdxx->base, &cmd);

        if (CY_RSLT_SUCCESS == ret)
        {
            ret = (cy_rslt_t)_cyhal_sdxx_pollcmdcomplete(sdxx, NULL);
        }
    } while ((CY_RSLT_SUCCESS != ret) && (retry-- > 0UL));

    if (CY_RSLT_SUCCESS == ret)
    {
        ret = (cy_rslt_t)Cy_SD_Host_GetResponse(sdxx->base, response, false);
    }

    return ret;
}

cy_rslt_t cyhal_sdio_bulk_transfer(cyhal_sdio_t *obj, cyhal_sdio_transfer_type_t direction,
                                   uint32_t argument, const uint32_t* data,
                                   uint16_t length, uint32_t* response)
{
    cy_rslt_t ret = CY_RSLT_SUCCESS;
    uint32_t retry = _CYHAL_SDIO_TRANSFER_TRIES;

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    _cyhal_sdxx_setup_smphr(sdxx);

    do
    {
        ret = cyhal_sdio_transfer_async(obj, direction, argument, data, length);

        if (CY_RSLT_SUCCESS == ret)
        {
            ret = _cyhal_sdxx_waitfor_transfer_complete(sdxx);
        }

        if (CY_RSLT_SUCCESS != ret)
        {
            /*  SDIO Error Handling
            *   SDIO write timeout is expected when doing first write to register
            *   after KSO bit disable (as it goes to AOS core).
            *   This is the only time known that a write timeout occurs.
            *   Issue the reset to recover from error. */
            _cyhal_sdxx_reset(sdxx);
        }

    } while ((CY_RSLT_SUCCESS != ret) && (--retry > 0UL));

    if(CY_RSLT_SUCCESS != ret)
    {
        sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
    }

    if ((response != NULL) && (CY_RSLT_SUCCESS == ret))
    {
        *response = 0UL;
        ret = (cy_rslt_t)Cy_SD_Host_GetResponse(sdxx->base, response, false);
    }

    return ret;
}

/*******************************************************************************
*
*   The asynchronous transfer is implemented on the CY_SD_HOST_XFER_COMPLETE
*   interrupt. The function sets up data and enables the CY_SD_HOST_XFER_COMPLETE
*   interrupt mask, which causes interrupt to occur and handled by _cyhal_sdio_irq_handler
*   which take care of disabling CY_SD_HOST_XFER_COMPLETE mask. This function
*   can also activate CY_SD_HOST_CMD_COMPLETE interrupt mask if it was enabled
*   by user via cyhal_sdio_enable_event function.
*
*******************************************************************************/
cy_rslt_t cyhal_sdio_transfer_async(cyhal_sdio_t *obj, cyhal_sdio_transfer_type_t direction,
                                    uint32_t argument, const uint32_t* data, uint16_t length)
{
    if (NULL == obj)
    {
        return CYHAL_SDIO_RSLT_ERR_BAD_PARAM;
    }

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    if (sdxx->pm_transition_pending)
    {
        return CYHAL_SDIO_RSLT_ERR_PM_PENDING;
    }

    cy_rslt_t                    ret;
    uint32_t                     retry = _CYHAL_SDIO_TRANSFER_TRIES;
    cy_stc_sd_host_cmd_config_t  cmd;
    cy_stc_sd_host_data_config_t dat;

    /* Initialize data constants*/
    dat.autoCommand         = CY_SD_HOST_AUTO_CMD_NONE;
    dat.dataTimeout         = 0x0dUL;
    dat.enableIntAtBlockGap = false;
    dat.enReliableWrite     = false;
    dat.enableDma           = true;

    do
    {
        /* Add SDIO Error Handling
        * SDIO write timeout is expected when doing first write to register
        * after KSO bit disable (as it goes to AOS core).
        * This timeout, however, triggers an error state in the hardware.
        * So, check for the error and then recover from it
        * as needed via reset issuance. This is the only time known that
        * a write timeout occurs.
        */

        /* First clear out the command complete and transfer complete statuses */
        Cy_SD_Host_ClearNormalInterruptStatus(sdxx->base, (CY_SD_HOST_XFER_COMPLETE | CY_SD_HOST_CMD_COMPLETE));

        /* Check if an error occurred on any previous transactions or reset after the first unsuccessful transfer try */
        if ((Cy_SD_Host_GetNormalInterruptStatus(sdxx->base) & CY_SD_HOST_ERR_INTERRUPT) ||
            (retry < _CYHAL_SDIO_TRANSFER_TRIES))
        {
            /* Reset the block if there was an error. Note a full reset usually
             * requires more time, but this short version is working quite well and
             * successfully clears out the error state.
             */
            Cy_SD_Host_ClearErrorInterruptStatus(sdxx->base, _CYHAL_SDIO_SET_ALL_INTERRUPTS_MASK);
            _cyhal_sdxx_reset(sdxx);
        }

        /* Prepare the data transfer register */
        cmd.commandIndex                 = (uint32_t) CYHAL_SDIO_CMD_IO_RW_EXTENDED;
        cmd.commandArgument              = argument;
        cmd.enableCrcCheck               = true;
        cmd.enableAutoResponseErrorCheck = false;
        cmd.respType                     = CY_SD_HOST_RESPONSE_LEN_48;
        cmd.enableIdxCheck               = true;
        cmd.dataPresent                  = true;
        cmd.cmdType                      = CY_SD_HOST_CMD_NORMAL;

        dat.read = ( direction == CYHAL_SDIO_XFER_TYPE_WRITE ) ? false : true;

        /* Block mode */
        if (length >= obj->block_size)
        {
            dat.blockSize     = obj->block_size;
            dat.numberOfBlock = ( length + obj->block_size - 1 ) / obj->block_size;
        }
        /* Byte mode */
        else
        {
            dat.blockSize     = length;
            dat.numberOfBlock = 1UL;
        }

        length = dat.blockSize * dat.numberOfBlock;

        sdxx->adma_descriptor_tbl[0] = (1UL << CY_SD_HOST_ADMA_ATTR_VALID_POS) | /* Attr Valid */
                                       (1UL << CY_SD_HOST_ADMA_ATTR_END_POS) |   /* Attr End */
                                       (0UL << CY_SD_HOST_ADMA_ATTR_INT_POS) |   /* Attr Int */
                                       (CY_SD_HOST_ADMA_TRAN << CY_SD_HOST_ADMA_ACT_POS) |
                                       ((uint32_t)length << CY_SD_HOST_ADMA_LEN_POS);     /* Len */

        sdxx->adma_descriptor_tbl[1] = (uint32_t)data;

        /* The address of the ADMA descriptor table. */
        dat.data = (uint32_t*)&(sdxx->adma_descriptor_tbl[0]);

        ret = _cyhal_sdxx_prepare_for_transfer(sdxx);

        if (CY_RSLT_SUCCESS == ret)
        {
            ret = (cy_rslt_t)Cy_SD_Host_InitDataTransfer(sdxx->base, &dat);
        }

        if (CY_RSLT_SUCCESS == ret)
        {
            /* Indicate that async transfer in progress */
            sdxx->data_transfer_status = _CYHAL_SDXX_WAIT_BOTH;
            ret = (cy_rslt_t)Cy_SD_Host_SendCommand(sdxx->base, &cmd);
        }

        if (CY_RSLT_SUCCESS == ret)
        {
            ret = (cy_rslt_t)_cyhal_sdxx_pollcmdcomplete(sdxx, NULL);
        }

    } while ((CY_RSLT_SUCCESS != ret) && (--retry > 0UL));

    if (CY_RSLT_SUCCESS != ret)
    {
        /* Transfer failed */
        sdxx->data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
    }

    return ret;
}

bool cyhal_sdio_is_busy(const cyhal_sdio_t *obj)
{
    CY_ASSERT(NULL != obj);
    return _cyhal_sdio_is_busy(&(obj->sdxx));
}

cy_rslt_t cyhal_sdio_abort_async(cyhal_sdio_t *obj)
{
    cy_rslt_t ret = CY_RSLT_SUCCESS;

    /* To abort transition reset dat and cmd lines (software reset) */
    _cyhal_sdxx_reset(&(obj->sdxx));
    obj->sdxx.data_transfer_status = _CYHAL_SDXX_NOT_RUNNING;
    return ret;
}

void cyhal_sdio_register_callback(cyhal_sdio_t *obj, cyhal_sdio_event_callback_t callback, void *callback_arg)
{
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->sdxx.callback_data.callback = (cy_israddress) callback;
    obj->sdxx.callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
}

void cyhal_sdio_enable_event(cyhal_sdio_t *obj, cyhal_sdio_event_t event, uint8_t intr_priority, bool enable)
{
    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    /* Configure interrupt-based event(s) */
    if (0U != ((uint32_t) event & (uint32_t) CYHAL_SDIO_ALL_INTERRUPTS))
    {
        uint32_t cur_interrupt_mask = Cy_SD_Host_GetNormalInterruptMask(sdxx->base);
        uint32_t new_interrupt_mask = cur_interrupt_mask;

        _cyhal_system_irq_t irqn = _CYHAL_SDHC_IRQ_N[sdxx->resource.block_num];
        _cyhal_irq_set_priority(irqn, intr_priority);

        if (enable)
        {
            sdxx->irq_cause |= event;

            /*  CY_SD_HOST_CMD_COMPLETE and CY_SD_HOST_XFER_COMPLETE cannot be always enabled because of SD Host driver limitations.
            *   SDHC HAL transfer APIs are taking care of enabling these statuses. CY_SD_HOST_CMD_COMPLETE is only
            *   enabled if corresponding user callback is enabled while CY_SD_HOST_XFER_COMPLETE is enabled by transfer API
            *   regardless it was enabled by user or not. */
            event &= ((uint32_t) ~CY_SD_HOST_CMD_COMPLETE) & ((uint32_t) ~CY_SD_HOST_XFER_COMPLETE);

            new_interrupt_mask |= event;
            Cy_SD_Host_ClearNormalInterruptStatus(sdxx->base, new_interrupt_mask & ~cur_interrupt_mask);
        }
        else
        {
            new_interrupt_mask &= ~(event);
            sdxx->irq_cause &= ~event;
        }

        Cy_SD_Host_SetNormalInterruptMask(sdxx->base, new_interrupt_mask);
    }

    /* Configure non-interrupt based event(s) */
    if (0U != ((uint32_t) event & _CYHAL_SDIO_INTERFACE_CHANGE_MASK))
    {
        if (enable)
        {
            obj->events |= (uint32_t) event;
        }
        else
        {
            obj->events &= (uint32_t) ~((uint32_t) event);
        }
    }
}

cy_rslt_t cyhal_sdio_set_io_voltage(cyhal_sdio_t *obj, cyhal_gpio_t io_volt_sel, cyhal_sdio_io_voltage_t io_voltage,
                                    cyhal_sdio_io_volt_action_type_t io_switch_type)
{
    CY_ASSERT(NULL != obj);
    cy_rslt_t result = CY_RSLT_SUCCESS;

    _cyhal_sdxx_t *sdxx = &(obj->sdxx);

    if (NC != io_volt_sel)
    {
        /* Configure provided pin it was not yet configured */
        if (NC == sdxx->pin_io_vol_sel)
        {
            #if _CYHAL_SDHC_IO_VOLT_SEL_PRESENT
            result = _cyhal_sdxx_setup_pin(sdxx, io_volt_sel, cyhal_pin_map_sdhc_io_volt_sel,
                CYHAL_PIN_MAP_DRIVE_MODE_SDHC_IO_VOLT_SEL,
                _CYHAL_SDHC_ELEM_COUNT(cyhal_pin_map_sdhc_io_volt_sel), &(sdxx->pin_io_vol_sel),
                _CYHAL_SDHC_CARD_IO_VOLTAGE, true);
            #else
            result = _cyhal_sdxx_setup_pin(sdxx, io_volt_sel, NULL,
                CY_GPIO_DM_STRONG_IN_OFF,
                0, &(sdxx->pin_io_vol_sel),
                _CYHAL_SDHC_CARD_IO_VOLTAGE, true);
            #endif //_CYHAL_SDHC_IO_VOLT_SEL_PRESENT
        }
        /* io volt sel pin is already configured and user provided other pin */
        else if (io_volt_sel != sdxx->pin_io_vol_sel)
        {
            result = CYHAL_SDIO_RSLT_ERR_IO_VOLT_SEL_PIN_CONFIGURED;
        }
    }

    if (CY_RSLT_SUCCESS == result)
    {
        result = _cyhal_sdxx_set_io_voltage(sdxx, (cyhal_sdxx_io_voltage_t)io_voltage,
            (_cyhal_sdxx_io_switch_action_t)io_switch_type);
    }

    return result;
}

cy_rslt_t cyhal_sdio_init_cfg(cyhal_sdio_t *obj, const cyhal_sdio_configurator_t *cfg)
{
    CY_ASSERT(NULL != obj);
    CY_ASSERT(NULL != cfg);
    return _cyhal_sdio_init_common(obj, cfg);
}

#if defined(__cplusplus)
}
#endif

#endif /* CYHAL_DRIVER_AVAILABLE_SDHC */
