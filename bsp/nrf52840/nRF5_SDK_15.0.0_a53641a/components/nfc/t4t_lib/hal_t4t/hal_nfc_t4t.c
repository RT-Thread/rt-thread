/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#include "sdk_config.h"
#if NFC_T4T_HAL_ENABLED

#include "hal_nfc_t4t.h"
#include <stdint.h>
#include <stdbool.h>
#include "nfc_t4t_lib.h"
#include "nfc_fixes.h"
#include "nrf.h"
#include "app_util_platform.h"
#include "nordic_common.h"
#include "nrf_drv_clock.h"

#define NRF_LOG_MODULE_NAME hal_nfc
#if HAL_NFC_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       HAL_NFC_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  HAL_NFC_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR HAL_NFC_CONFIG_DEBUG_COLOR
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();
#else // HAL_NFC_CONFIG_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#include "nrf_log.h"
#endif // HAL_NFC_CONFIG_LOG_ENABLED


#if HAL_NFC_CONFIG_DEBUG_PIN_ENABLED
    #include "nrf_gpio.h"

    #define HAL_NFC_DEBUG_PIN_CONFIG(pin_num) nrf_gpio_cfg_output(pin_num)
    #define HAL_NFC_DEBUG_PIN_CLEAR(pin_num)  nrf_gpio_pin_clear(pin_num)
    #define HAL_NFC_DEBUG_PIN_SET(pin_num)    nrf_gpio_pin_set(pin_num)

    #define HAL_NFC_DEBUG_PINS_INITIALIZE()                             \
        do{                                                             \
            HAL_NFC_DEBUG_PIN_CONFIG(HAL_NFC_HCLOCK_OFF_DEBUG_PIN);     \
            HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_HCLOCK_OFF_DEBUG_PIN);      \
            HAL_NFC_DEBUG_PIN_CONFIG(HAL_NFC_HCLOCK_ON_DEBUG_PIN);      \
            HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_HCLOCK_ON_DEBUG_PIN);       \
            HAL_NFC_DEBUG_PIN_CONFIG(HAL_NFC_NFC_EVENT_DEBUG_PIN);      \
            HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_NFC_EVENT_DEBUG_PIN);       \
            HAL_NFC_DEBUG_PIN_CONFIG(HAL_NFC_DETECT_EVENT_DEBUG_PIN);   \
            HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_DETECT_EVENT_DEBUG_PIN);    \
            HAL_NFC_DEBUG_PIN_CONFIG(HAL_NFC_TIMER4_EVENT_DEBUG_PIN);   \
            HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_TIMER4_EVENT_DEBUG_PIN);    \
        } while(0)
#else
    #define HAL_NFC_DEBUG_PIN_CLEAR(pin_num)
    #define HAL_NFC_DEBUG_PIN_SET(pin_num)
    #define HAL_NFC_DEBUG_PINS_INITIALIZE()
#endif // HAL_NFC_DEBUG_PIN_ENABLE


/* NFC library version history:
 * #define NFC_LIB_VERSION          0x00 first experimental version intended for nRF52840 IC rev. Engineering A (PCA10056, part of nRF52840 Preview Development Kit)
 */

#define NFC_LIB_VERSION             0x00u              /**< Internal: current NFC lib. version  */

#define CASCADE_TAG_BYTE            0x88u              /**< Constant defined by ISO/EIC 14443-3 */
#define NFCID1_3RD_LAST_BYTE2_SHIFT 16u                /**< Shift value for NFC ID byte 2 */
#define NFCID1_3RD_LAST_BYTE1_SHIFT 8u                 /**< Shift value for NFC ID byte 1 */
#define NFCID1_3RD_LAST_BYTE0_SHIFT 0u                 /**< Shift value for NFC ID byte 0 */
#define NFCID1_2ND_LAST_BYTE2_SHIFT 16u                /**< Shift value for NFC ID byte 2 */
#define NFCID1_2ND_LAST_BYTE1_SHIFT 8u                 /**< Shift value for NFC ID byte 1 */
#define NFCID1_2ND_LAST_BYTE0_SHIFT 0u                 /**< Shift value for NFC ID byte 0 */
#define NFCID1_LAST_BYTE3_SHIFT     24u                /**< Shift value for NFC ID byte 3 */
#define NFCID1_LAST_BYTE2_SHIFT     16u                /**< Shift value for NFC ID byte 2 */
#define NFCID1_LAST_BYTE1_SHIFT     8u                 /**< Shift value for NFC ID byte 1 */
#define NFCID1_LAST_BYTE0_SHIFT     0u                 /**< Shift value for NFC ID byte 0 */
#define NFCID1_SINGLE_SIZE          4u                 /**< Length of single size NFCID1 */
#define NFCID1_DOUBLE_SIZE          7u                 /**< Length of double size NFCID1 */
#define NFCID1_TRIPLE_SIZE          10u                /**< Length of triple size NFCID1 */
#define NFCID1_DEFAULT_LENGHT       NFCID1_DOUBLE_SIZE /**< Length of NFCID1 if user does not provide one */
#define NFCID1_MAX_LENGHT           NFCID1_TRIPLE_SIZE /**< Maximum length of NFCID1 */
#define NFC_RX_BUFFER_SIZE          256u               /**< NFC Rx data buffer size */
#define NFC_SLP_REQ_CMD             0x50u              /**< NFC SLP_REQ command identifier */
#define NFC_CRC_SIZE                2u                 /**< CRC size in bytes */
#define NFC_T4T_SELRES_PROTOCOL     1u                 /**< Type 4A Tag PROTOCOL bit setup (b7:b6) for SEL_RES Response frame */
#define NFC_T4T_SELRES_PROTOCOL_MSK 0x03u              /**< PROTOCOL bits mask for SEL_RES Response frame */

#ifdef  BOARD_PCA10056
    #define NFC_T4T_FWI_MAX         8u                 /**< Maximum FWI parameter value for 52840*/
#else
    #define NFC_T4T_FWI_MAX         4u                 /**< Maximum FWI parameter value */
#endif // BOARD_PCA10056

#define NFC_T4T_FWI_52840S_MAX      4u                 /**< Maximum FWI parameter value for first sample of 52840 */
#define NFCT_FRAMEDELAYMAX_52840S   (0xFFFFUL)         /**< Bit mask of FRAMEDELAYMAX field for first sample of 52840 */
#define NFC_T4T_FWI_DEFAULT         4u                 /**< Default FWI parameter value */
#define NRF_T4T_FWI_LISTEN_MAX      8u                 /**< Maxiumum FWI parameter value in Listen Mode */
#define NFC_T4T_RATS_CMD            0xE0u              /**< RATS Command Byte */
#define NFC_T4T_RATS_DID_MASK       0x0Fu              /**< Mask of DID field inside RATS Parameter Byte. */
#define NFC_T4T_RATS_DID_RFU        0x0Fu              /**< Invalid value of DID - RFU. */
#define NFC_T4T_S_DESELECT          0xC2u              /**< S(DESELECT) Block identifier */
#define NFC_T4T_S_WTX               0xF2u              /**< S(WTX)Block identifier */
#define NFC_T4T_S_BLOCK_MSK         0xF7u              /**< S-Block Mask */
#define NFC_T4T_I_BLOCK             0x02u              /**< I-Block identifier */
#define NFC_T4T_BLOCK_MSK           0xE6u              /**< I/R- block mask (NAD not supported, expect this bit equal 0) */
#define NFC_T4T_ISO_DEP_MSK         0x02u              /**< ISO-DEP block mask */
#define NFC_T4T_R_BLOCK             0xA2u              /**< R- Block identifier (static bits) */
#define NFC_T4T_WTX_NO_DID_SIZE     0x02               /**< WTX data buffer size without DID field. */
#define NFC_T4T_WTX_DID_SIZE        0x03               /**< WTX data buffer size with DID field. */
#define NFC_T4T_WTXM_MAX_VALUE      0x3B               /**< WTXM max value, according to 'NFC Forum Digital Protocol Technical Specification 2.0, 16.2.2 */
#define NFC_T4T_DID_BIT             0x08               /**< Indicates if DID present in ISO-DEP block. */
#define NFC_T4T_DID_MASK            0x0F               /**< DID field mask */
#define NFCT_INTEN_MSK              0x1C5CFFu          /**< Mask for all NFCT interrupts */


#ifdef HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
    #define NRF_NFCT_ERRORSTATUS_ALL (NFCT_ERRORSTATUS_FRAMEDELAYTIMEOUT_Msk)   /**< Mask for clearing all error flags in NFCT_ERRORSTATUS register */
#else
    #define NRF_NFCT_ERRORSTATUS_ALL (NFCT_ERRORSTATUS_NFCFIELDTOOWEAK_Msk   | \
                                      NFCT_ERRORSTATUS_NFCFIELDTOOSTRONG_Msk | \
                                      NFCT_ERRORSTATUS_FRAMEDELAYTIMEOUT_Msk)   /**< Mask for clearing all error flags in NFCT_ERRORSTATUS register */
#endif // HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND

#define NRF_NFCT_FRAMESTATUS_RX_MSK (NFCT_FRAMESTATUS_RX_OVERRUN_Msk      | \
                                     NFCT_FRAMESTATUS_RX_PARITYSTATUS_Msk | \
                                     NFCT_FRAMESTATUS_RX_CRCERROR_Msk)          /**< Mask for clearing all flags in NFCT_FRAMESTATUS_RX register */
#define NFC_FIELD_ON_MASK            NFCT_FIELDPRESENT_LOCKDETECT_Msk           /**< Mask for checking FIELDPRESENT register for state: FIELD ON. */
#define NFC_FIELD_OFF_MASK           NFCT_FIELDPRESENT_FIELDPRESENT_Msk         /**< Mask for checking FIELDPRESENT register for state: FIELD OFF. */

#define NFC_T4T_FWI_TO_FWT(FWI)      (256u * 16u * (1 << (FWI)))                /**< Macro for calculating FWT (in number of NFC carrier periods) from FWI parameter. */
#define NFC_T4T_WTXM_MAX(FWI)        ( 1 << (NRF_T4T_FWI_LISTEN_MAX - (FWI)))   /**< Macro for calculating WTXM based on 'NFC Forum Digital Protocol Specification Version 1.1, Requirement 15.2.2.9', and FRAMEDELAYMAX maximum register setting */

/* Begin: Bugfix for FTPAN-xx (AUTOCOLRESCONFIG) */
#define NRF_NFCT_AUTOCOLRESCONFIG     (*(uint32_t volatile *)(0x4000559C))
#define NRF_NFCT_AUTOCOLRESCONFIG_Pos 0
/* End: Bugfix for FTPAN-xx */

#define NRF_NFCT_DEFAULTSTATESLEEP     (*(uint32_t volatile *)(0x40005420))     /**< The default state of NFCT. */
#define NRF_NFCT_DEFAULTSTATESLEEP_MSK 0x1UL                                    /**< Mask for checking the default state of NFCT. */

#ifdef HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
    #define NRF_NFCT_ACTIVATE_CONDS_THR    2                                        /**< Number of required conditions to activate NFCT. */
    #define NRF_NFCT_ACTIVATE_DELAY        1000                                     /**< Minimal delay in us between NFC field detection and activation of NFCT. */
#endif // HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND

typedef enum
{
    NFC_FIELD_STATE_NONE,   /**< Initial value indicating no NFCT Field events. */
    NFC_FIELD_STATE_OFF,    /**< NFCT FIELDLOST Event has been set. */
    NFC_FIELD_STATE_ON,     /**< NFCT FIELDDETECTED Event has been set. */
    NFC_FIELD_STATE_UNKNOWN /**< Both NFCT Field Events have been set - ambiguous state. */
}nfct_field_sense_state_t;

/* Static function declarations */
static inline void nrf_nfct_event_clear(volatile uint32_t * p_event);
static inline void nrf_nfct_clock_event_handler(nrf_drv_clock_evt_type_t event);
static inline void nrf_nfct_field_event_handler(volatile nfct_field_sense_state_t field_state);
static void hal_nfc_nfcid1_default_bytes(void);
static void hal_nfc_nfcid1_registers_setup(void);

/* Static data */
static hal_nfc_callback_t           m_nfc_lib_callback = (hal_nfc_callback_t) NULL;                     /**< Callback to nfc_lib layer */
static void *                       m_nfc_lib_context;                                                  /**< Callback execution context */
static volatile uint8_t             m_nfc_rx_buffer[NFC_RX_BUFFER_SIZE]   = {0};                        /**< Buffer for NFC Rx data */
static volatile bool                m_slp_req_received                    = false;                      /**< Flag indicating that SLP_REQ Command was received */
static volatile bool                m_field_on                            = false;                      /**< Flag indicating that NFC Tag field is present */
static nrf_drv_clock_handler_item_t m_clock_handler_item;                                               /**< Clock event handler item structure */
static volatile uint8_t             m_fwi;                                                              /**< FWI parameter */
static volatile uint8_t             m_wtxm;                                                             /**< WTXM maximum value */
static volatile uint8_t             m_wtx_data[3];                                                      /**< Tx buffer for an S(WTX) block */
static volatile bool                m_deselect                            = false;                      /**< Flag indicating reception of DESELECT command */
static volatile bool                m_swtx_sent                           = false;                      /**< Flag indicating that SWTX command has been sended. */
static volatile bool                m_pending_msg                         = false;                      /**< Flag signaling pending message during SWTX command execution. */
static volatile const uint8_t *     m_pending_msg_ptr                     = NULL;                       /**< Pointer to pending message buffer. */
static volatile size_t              m_pending_data_length                 = 0;                          /**< Length of pending message data. */
static volatile bool                m_t4t_tx_waiting                      = false;                      /**< Indicates if HAL is waiting for upper layer response to received command */
static volatile uint8_t             m_t4t_selres                          = NFC_T4T_SELRES_PROTOCOL;    /**< Protocol bits setup in SEL_RES frame - can be modified using the library API */
static volatile uint8_t             m_did                                 = 0;                          /**< DID field value. */
static uint8_t                      m_nfcid1_length                       = 0;                          /**< Length of NFCID1 provided by user or 0 if not initialized yet */
static uint8_t                      m_nfcid1_data[NFCID1_MAX_LENGHT]      = {0};                        /**< Content of NFCID1 */
static volatile uint8_t             m_t4t_active                          = false;                      /**< Indicates if NFC Tag is in 4A state (on reception of correct RATS command). */

#ifdef HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
static volatile bool                m_nfc_fieldevents_filter_active       = false;     /**< Flag indicating that field events are ignored. */
static volatile uint32_t            m_nfc_activate_conditions             = 0;         /**< Number of activation conditions that are met. */
#endif // HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND

#ifndef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
static volatile uint32_t            m_nfc_fieldpresent_mask               = NFC_FIELD_OFF_MASK;   /**< Mask used for NFC Field polling in NFCT_FIELDPRESENT register */
#endif // HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND

#ifdef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND

static inline void hal_nfc_re_setup(void);
static void hal_nfc_field_check(void);

#define NRF_NFCT_POWER (*(uint32_t volatile *)(0x40005FFC))

#define NFC_HAL_FIELDPRESENT_MASK      (NFCT_FIELDPRESENT_LOCKDETECT_Msk | \
                                       NFCT_FIELDPRESENT_FIELDPRESENT_Msk)

#define NFC_HAL_FIELDPRESENT_IS_LOST   ((NFCT_FIELDPRESENT_FIELDPRESENT_NoField <<  \
                                       NFCT_FIELDPRESENT_FIELDPRESENT_Pos) |        \
                                       (NFCT_FIELDPRESENT_LOCKDETECT_NotLocked <<   \
                                       NFCT_FIELDPRESENT_LOCKDETECT_Pos))

#endif // HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND

#ifdef HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
static void hal_nfc_activate_check(void)
{
    static bool is_field_validation_pending = false;

    if (is_field_validation_pending)
    {
        is_field_validation_pending     = false;
        m_nfc_fieldevents_filter_active = false;

        // Check the field status with FIELDPRESENT and take action if field is lost.
        nrf_nfct_field_event_handler(NFC_FIELD_STATE_UNKNOWN);
        return;
    }

    m_nfc_activate_conditions++;
    if (m_nfc_activate_conditions == NRF_NFCT_ACTIVATE_CONDS_THR)
    {
        m_nfc_activate_conditions = 0;

        NRF_NFCT->TASKS_ACTIVATE    = 1;
        is_field_validation_pending = true;

        // Start the timer second time to validate if tag has locked to the field
        NRF_TIMER4->TASKS_CLEAR = 1;
        NRF_TIMER4->TASKS_START = 1;
    }
}
#endif // HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND

#if defined(HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND) || defined(HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND)

static void field_timer_with_callback_config(void)
{
    NRF_TIMER4->MODE      = TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos;
    NRF_TIMER4->BITMODE   = TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos;
    NRF_TIMER4->PRESCALER = 4 << TIMER_PRESCALER_PRESCALER_Pos;
#ifdef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
    NRF_TIMER4->CC[0]     = HAL_NFC_FIELD_TIMER_PERIOD << TIMER_CC_CC_Pos;
#else
    NRF_TIMER4->CC[0]     = NRF_NFCT_ACTIVATE_DELAY << TIMER_CC_CC_Pos;
#endif
    NRF_TIMER4->SHORTS    = TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;
    NRF_TIMER4->INTENSET  = TIMER_INTENSET_COMPARE0_Set << TIMER_INTENSET_COMPARE0_Pos;

    NVIC_ClearPendingIRQ(TIMER4_IRQn);
    NVIC_SetPriority(TIMER4_IRQn, NFCT_CONFIG_IRQ_PRIORITY);
    NVIC_EnableIRQ(TIMER4_IRQn);
}

void TIMER4_IRQHandler(void)
{
    HAL_NFC_DEBUG_PIN_SET(HAL_NFC_TIMER4_EVENT_DEBUG_PIN);
#ifdef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
    hal_nfc_field_check();
#else
    NRF_TIMER4->TASKS_SHUTDOWN = 1;
    hal_nfc_activate_check();
#endif
    NRF_TIMER4->EVENTS_COMPARE[0] = 0;
    HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_TIMER4_EVENT_DEBUG_PIN);
}

#endif // defined(HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND) || defined(HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND)

/**
 * @brief Common part of setup used for NFCT initialization and reinitialization.
 */
#ifdef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
static void hal_nfc_common_hw_setup()
#else
static inline void hal_nfc_common_hw_setup()
#endif // HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
{
#ifdef HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
    if (type_52840_sample_check())
    {
        /* Begin: Bugfix for FTPAN-98 */
        *(volatile uint32_t *) 0x4000568C = 0x00038148;
        /* End: Bugfix for FTPAN-98 */
        /* Begin: Bugfix for FTPAN-144 */
        *(volatile uint32_t *) 0x4000561c = 0x01;
        *(volatile uint32_t *) 0x4000562c = 0x3F;
        *(volatile uint32_t *) 0x4000563c = 0x0;
        /* End: Bugfix for FTPAN-144 */
    }
#endif // HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND

/* Begin: Bugfix for FTPAN-17 */
/* fixed by avoiding usage of FIELDLOST event */
#ifdef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
    NRF_NFCT->INTENSET = (NFCT_INTENSET_FIELDDETECTED_Enabled << NFCT_INTENSET_FIELDDETECTED_Pos);
#else
    NRF_NFCT->INTENSET = (NFCT_INTENSET_FIELDDETECTED_Enabled << NFCT_INTENSET_FIELDDETECTED_Pos) |
                         (NFCT_INTENSET_FIELDLOST_Enabled     << NFCT_INTENSET_FIELDLOST_Pos);
#endif // HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
/* End:   Bugfix for FTPAN-17 */

    NRF_NFCT->INTENSET = (NFCT_INTENSET_TXFRAMESTART_Enabled << NFCT_INTENSET_TXFRAMESTART_Pos);

    NRF_NFCT->INTENSET = (NFCT_INTENSET_ERROR_Enabled    << NFCT_INTENSET_ERROR_Pos) |
                         (NFCT_INTENSET_SELECTED_Enabled << NFCT_INTENSET_SELECTED_Pos);

    hal_nfc_nfcid1_registers_setup();

    /* Set FRAMEDELAYMAX to default setting */
    uint8_t fwi             = NFC_T4T_FWI_DEFAULT;

    ret_code_t err_code     = hal_nfc_parameter_set( HAL_NFC_PARAM_FWI, &fwi, sizeof(fwi));
    ASSERT(err_code == NRF_SUCCESS);

    /* Set PROTOCOL bits for Type 4A Tag */
    NRF_NFCT->SELRES =
        (m_t4t_selres << NFCT_SELRES_PROTOCOL_Pos) & NFCT_SELRES_PROTOCOL_Msk;

    m_swtx_sent           = false;
    m_pending_msg         = false;
    m_pending_msg_ptr     = NULL;
    m_pending_data_length = 0;
}

/** @brief Setup NRF_NFCT->NFCID1 and NRF_NFCT->SENSRES registers based on m_nfcid1_data and m_nfcid1_length variables.
 */
static void hal_nfc_nfcid1_registers_setup(void)
{
    uint32_t sens_res_size;         // Value that will be written to NRF_NFCT->SENSRES
    uint8_t* p_nfcid_remaining_data;  // Points to the first byte of m_nfcid1_data remaining to write to NRF_NFCT->NFCID1 registers

    p_nfcid_remaining_data = m_nfcid1_data;

    if (m_nfcid1_length == NFCID1_SINGLE_SIZE)
    {
        sens_res_size = NFCT_SENSRES_NFCIDSIZE_NFCID1Single;
    }
    else
    {
        if (m_nfcid1_length == NFCID1_DOUBLE_SIZE)
        {
            sens_res_size = NFCT_SENSRES_NFCIDSIZE_NFCID1Double;
        }
        else // then m_nfcid1_length == NFCID1_TRIPLE_SIZE
        {
            /* MSB of NFCID1_3RD_LAST register is not used - always 0 */
            NRF_NFCT->NFCID1_3RD_LAST =
                ((uint32_t) p_nfcid_remaining_data[0] << NFCID1_3RD_LAST_BYTE2_SHIFT) |
                ((uint32_t) p_nfcid_remaining_data[1] << NFCID1_3RD_LAST_BYTE1_SHIFT) |
                ((uint32_t) p_nfcid_remaining_data[2] << NFCID1_3RD_LAST_BYTE0_SHIFT);
            p_nfcid_remaining_data += 3;
            sens_res_size = NFCT_SENSRES_NFCIDSIZE_NFCID1Triple;
        }
        /* MSB of NFCID1_2ND_LAST register is not used - always 0 */
        NRF_NFCT->NFCID1_2ND_LAST =
            ((uint32_t) p_nfcid_remaining_data[0] << NFCID1_2ND_LAST_BYTE2_SHIFT) |
            ((uint32_t) p_nfcid_remaining_data[1] << NFCID1_2ND_LAST_BYTE1_SHIFT) |
            ((uint32_t) p_nfcid_remaining_data[2] << NFCID1_2ND_LAST_BYTE0_SHIFT);
        p_nfcid_remaining_data += 3;
    }

    NRF_NFCT->NFCID1_LAST =
        ((uint32_t) p_nfcid_remaining_data[0] << NFCID1_LAST_BYTE3_SHIFT) |
        ((uint32_t) p_nfcid_remaining_data[1] << NFCID1_LAST_BYTE2_SHIFT) |
        ((uint32_t) p_nfcid_remaining_data[2] << NFCID1_LAST_BYTE1_SHIFT) |
        ((uint32_t) p_nfcid_remaining_data[3] << NFCID1_LAST_BYTE0_SHIFT);

    /* Begin: Bugfix for FTPAN-25 (IC-9929) */
    /* Workaround for wrong SENSRES values require using SDD00001, but here SDD00100 is used
       because it's required to operate with Windows Phone */
    NRF_NFCT->SENSRES =
            (sens_res_size << NFCT_SENSRES_NFCIDSIZE_Pos) |
            (NFCT_SENSRES_BITFRAMESDD_SDD00100   << NFCT_SENSRES_BITFRAMESDD_Pos);
    /* End:   Bugfix for FTPAN-25 (IC-9929)*/

    m_t4t_active          = false;
    m_swtx_sent           = false;
    m_pending_msg         = false;
    m_pending_msg_ptr     = NULL;
    m_pending_data_length = 0;
}


ret_code_t hal_nfc_setup(hal_nfc_callback_t callback, void * p_context)
{
    m_nfc_lib_callback = callback;
    m_nfc_lib_context  = p_context;

    if (m_nfcid1_length == 0)
    {
        m_nfcid1_length = NFCID1_DEFAULT_LENGHT;
        hal_nfc_nfcid1_default_bytes();
    }

    hal_nfc_common_hw_setup();

    /* Initialize SDK Clock module for handling high precission clock requests */
    m_clock_handler_item.event_handler = nrf_nfct_clock_event_handler;
    m_clock_handler_item.p_next        = NULL;

    ret_code_t err_code = nrf_drv_clock_init();

#if defined(HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND) || defined(HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND)
    #if defined(HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND)
    if (!type_52840_sample_check())
    #endif // defined(HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND)
    {
        field_timer_with_callback_config();
    }
#endif // defined(HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND) || defined(HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND)

    NRF_LOG_INFO("Init");
    HAL_NFC_DEBUG_PINS_INITIALIZE();

    if ((err_code == NRF_SUCCESS) || (err_code == NRF_ERROR_MODULE_ALREADY_INITIALIZED))
    {
        return NRF_SUCCESS;
    }
    else
    {
        return NRF_ERROR_INTERNAL;
    }
}


/**@brief Function for clearing an event flag in NRF_NFCT registers.
 *
 * @param[in]  p_event  Pointer to event register.
 *
 */
static inline void nrf_nfct_event_clear(volatile uint32_t * p_event)
{
    *p_event = 0;

    /* Perform read to ensure clearing is effective */
    volatile uint32_t dummy = *p_event;
    (void)dummy;
}


/**@brief Function for handling events from Clock Module.
 *
 * @param[in]  event  Clock event.
 *
 */
static inline void nrf_nfct_clock_event_handler(nrf_drv_clock_evt_type_t event)
{
    switch (event)
    {
        case NRF_DRV_CLOCK_EVT_HFCLK_STARTED:
            /* Activate NFCT only when HFXO is running */
            HAL_NFC_DEBUG_PIN_SET(HAL_NFC_HCLOCK_ON_DEBUG_PIN); // DEBUG!

#ifdef HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
            if (type_52840_final_check())
            {
                hal_nfc_activate_check();
            }
            else
#endif // HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
            {
                NRF_NFCT->TASKS_ACTIVATE = 1;
            }

            HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_HCLOCK_ON_DEBUG_PIN); // DEBUG!
            break;

        default:
            /* No implementation required */
            break;
    }
}


#ifdef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
static inline void nrf_nfct_field_lost_hfclk_handle(void)
{
    /* Begin: Bugfix for FTPAN-116 (IC-12886) */
    // reset the NFC for release HFCLK
    __DMB();
    NRF_NFCT_POWER = 0;
    __DMB();
    NRF_NFCT_POWER = 1;
    /* END:   Bugfix for FTPAN-116 (IC-12886) */

}
#endif // HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND

#ifndef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
/**@brief Function for evaluating and handling NFC field events.
 *
 * @param[in]  field_state  Current field state.
 *
 */
static inline void nrf_nfct_field_event_handler(volatile nfct_field_sense_state_t field_state)
{
#ifdef HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
    bool is_first_sample = type_52840_sample_check();

    if((!is_first_sample) && (m_nfc_fieldevents_filter_active))
    {
        return;
    }
#endif // HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND

    if (field_state == NFC_FIELD_STATE_UNKNOWN)
    {
        /* Probe NFC field */
        uint32_t field_present = NRF_NFCT->FIELDPRESENT;

        if (field_present & m_nfc_fieldpresent_mask)
        {
            field_state = NFC_FIELD_STATE_ON;
        }
        else
        {
            field_state = NFC_FIELD_STATE_OFF;
        }
    }

    /* Field event service */
    switch (field_state)
    {
        case NFC_FIELD_STATE_ON:
            if (!m_field_on)
            {
                HAL_NFC_DEBUG_PIN_SET(HAL_NFC_HCLOCK_ON_DEBUG_PIN); // DEBUG!
                nrf_drv_clock_hfclk_request(&m_clock_handler_item);

#ifdef HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
                /* Begin: Bugfix for FTPAN-190 */
                if (!is_first_sample)
                {
                    m_nfc_activate_conditions       = 0;
                    m_nfc_fieldevents_filter_active = true;

                    NRF_TIMER4->TASKS_CLEAR = 1;
                    NRF_TIMER4->TASKS_START = 1;
                }
                /* END: Bugfix for FTPAN-190 */
#endif // HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND

                HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_HCLOCK_ON_DEBUG_PIN); // DEBUG!
            }
            m_field_on = true;
            break;

        case NFC_FIELD_STATE_OFF:
            HAL_NFC_DEBUG_PIN_SET(HAL_NFC_HCLOCK_OFF_DEBUG_PIN); // DEBUG!

#ifdef HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
            /* Begin: Bugfix for FTPAN-116 (IC-12886) */
            if (is_first_sample)
            {
                *(volatile uint32_t *)0x40005010 = 1;
            }
            /* END: Bugfix for FTPAN-116 (IC-12886) */
#endif // HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND

            NRF_NFCT->TASKS_SENSE = 1;
            nrf_drv_clock_hfclk_release();
            m_field_on = false;

            NRF_NFCT->INTENCLR =
                (NFCT_INTENCLR_RXFRAMEEND_Clear << NFCT_INTENCLR_RXFRAMEEND_Pos) |
                (NFCT_INTENCLR_RXERROR_Clear    << NFCT_INTENCLR_RXERROR_Pos);

            /* Change mask to FIELD_OFF state - trigger FIELD_ON even if HW has not locked to the field */
            m_nfc_fieldpresent_mask = NFC_FIELD_OFF_MASK;

            if ((m_nfc_lib_callback != NULL) )
            {
                m_nfc_lib_callback(m_nfc_lib_context, HAL_NFC_EVENT_FIELD_OFF, 0, 0);
            }

            /* Re-enable Auto Collision Resolution */
            NRF_NFCT_AUTOCOLRESCONFIG = NRF_NFCT_AUTOCOLRESCONFIG &
                                        ~(1u << NRF_NFCT_AUTOCOLRESCONFIG_Pos);
            m_t4t_active = false;

            /* Go back to default frame delay mode, bugfix for tag locking. */
            NRF_NFCT->FRAMEDELAYMODE = NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_WindowGrid <<
                                       NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_Pos;

            HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_HCLOCK_OFF_DEBUG_PIN); // DEBUG!
            break;

        default:
            /* No implementation required */
            break;
    }
}
#endif // HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND

__STATIC_INLINE void hal_nfc_wtx_data_set(bool did_present)
{
    uint32_t wtx_data_size;

    m_wtx_data[0] = NFC_T4T_S_WTX;
    if (did_present)
    {
        m_wtx_data[0] |= NFC_T4T_DID_BIT;
        m_wtx_data[1]  = m_did;
        m_wtx_data[2]  = m_wtxm;
        wtx_data_size  = NFC_T4T_WTX_DID_SIZE;
    }
    else
    {
        m_wtx_data[1] = m_wtxm;
        wtx_data_size = NFC_T4T_WTX_NO_DID_SIZE;
    }

    NRF_NFCT->PACKETPTR      = (uint32_t) m_wtx_data;
    NRF_NFCT->TXD.AMOUNT     = (wtx_data_size << NFCT_TXD_AMOUNT_TXDATABYTES_Pos) &
                               NFCT_TXD_AMOUNT_TXDATABYTES_Msk;
    NRF_NFCT->FRAMEDELAYMODE = NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_ExactVal <<
                               NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_Pos;
    NRF_NFCT->TASKS_STARTTX  = 1;
    m_t4t_tx_waiting         = true;
}


/** @brief Writes default values to m_nfcid1_data based on NRF_FICR->NFC registers.
 */
static void hal_nfc_nfcid1_default_bytes(void)
{
    uint32_t nfc_tag_header0 = NRF_FICR->NFC.TAGHEADER0;
    uint32_t nfc_tag_header1 = NRF_FICR->NFC.TAGHEADER1;
    uint32_t nfc_tag_header2 = NRF_FICR->NFC.TAGHEADER2;

    m_nfcid1_data[0] = (uint8_t) LSB_32(nfc_tag_header0 >> 0);
    m_nfcid1_data[1] = (uint8_t) LSB_32(nfc_tag_header0 >> 8);
    m_nfcid1_data[2] = (uint8_t) LSB_32(nfc_tag_header0 >> 16);
    m_nfcid1_data[3] = (uint8_t) LSB_32(nfc_tag_header1 >> 0);
    m_nfcid1_data[4] = (uint8_t) LSB_32(nfc_tag_header1 >> 8);
    m_nfcid1_data[5] = (uint8_t) LSB_32(nfc_tag_header1 >> 16);
    m_nfcid1_data[6] = (uint8_t) LSB_32(nfc_tag_header1 >> 24);
    m_nfcid1_data[7] = (uint8_t) LSB_32(nfc_tag_header2 >> 0);
    m_nfcid1_data[8] = (uint8_t) LSB_32(nfc_tag_header2 >> 8);
    m_nfcid1_data[9] = (uint8_t) LSB_32(nfc_tag_header2 >> 16);
}


/** @brief Resets NFCT peripheral to its default state before automatic collision resolution
 *         procedure.
 */
static inline void nrf_nfct_default_state_reset(void)
{
    if (NRF_NFCT_DEFAULTSTATESLEEP & NRF_NFCT_DEFAULTSTATESLEEP_MSK) // Default state is SLEEP_A
    {
        NRF_NFCT->TASKS_GOSLEEP = 1;
    }
    else // Default state is IDLE
    {
        NRF_NFCT->TASKS_GOIDLE = 1;
    }

    /* Disable RX here (will be enabled at SELECTED) */
    NRF_NFCT->INTENCLR = NFCT_INTENCLR_RXFRAMEEND_Clear <<
                         NFCT_INTENCLR_RXFRAMEEND_Pos;
}


ret_code_t hal_nfc_parameter_set(hal_nfc_param_id_t id, void * p_data, size_t data_length)
{
    /* Parameter validation is done in upper-layer */

    if (id == HAL_NFC_PARAM_FWI)
    {
        /* Update Frame Wait Time setting; possible settings are limited by NFCT hardware */
        m_fwi = *((uint8_t *)p_data);

        if (data_length != sizeof(uint8_t))
        {
            return NRF_ERROR_DATA_SIZE;
        }
        /* Frame Wait Time settings for first sample of 52840 */
        if (type_52840_sample_check())
        {
            if (m_fwi > NFC_T4T_FWI_52840S_MAX)
            {
                return NRF_ERROR_INVALID_PARAM;
            }
            /* Set FRAMEDELAYTIME */
            if (m_fwi == NFC_T4T_FWI_52840S_MAX)
            {
                NRF_NFCT->FRAMEDELAYMAX = NFCT_FRAMEDELAYMAX_52840S;
            }
            else
            {
                NRF_NFCT->FRAMEDELAYMAX = NFC_T4T_FWI_TO_FWT(m_fwi);
            }
        }
        else
        {
            if (m_fwi > NFC_T4T_FWI_MAX)
            {
                return NRF_ERROR_INVALID_PARAM;
            }

            /* Set FRAMEDELAYTIME */
            if (m_fwi == NFC_T4T_FWI_MAX)
            {
                NRF_NFCT->FRAMEDELAYMAX = NFCT_FRAMEDELAYMAX_FRAMEDELAYMAX_Msk;
            }
            else
            {
                NRF_NFCT->FRAMEDELAYMAX = NFC_T4T_FWI_TO_FWT(m_fwi);
            }
        }

        if (NFC_T4T_WTXM_MAX(m_fwi) > NFC_T4T_WTXM_MAX_VALUE)
        {
            m_wtxm = NFC_T4T_WTXM_MAX_VALUE;
        }
        else
        {
            m_wtxm = NFC_T4T_WTXM_MAX(m_fwi);
        }
    }
    else if (id == HAL_NFC_PARAM_SELRES)
    {
        /* Update SEL_RES 'Protocol' bits setting */
        uint8_t sel_res = *((uint8_t *)p_data);

        if (data_length != sizeof(uint8_t))
        {
            return NRF_ERROR_DATA_SIZE;
        }
        if (sel_res > NFC_T4T_SELRES_PROTOCOL_MSK)
        {
            return NRF_ERROR_INVALID_PARAM;
        }

        m_t4t_selres     = sel_res;
        NRF_NFCT->SELRES =
            (m_t4t_selres << NFCT_SELRES_PROTOCOL_Pos) & NFCT_SELRES_PROTOCOL_Msk;
    }
    else if (id == HAL_NFC_PARAM_DID)
    {
        if (data_length > sizeof(uint8_t))
        {
            return NRF_ERROR_DATA_SIZE;
        }

        m_did = (data_length == sizeof(m_did)) ? *((uint8_t *)p_data) : 0;
    }
    else if (id == HAL_NFC_PARAM_NFCID1)
    {
        if (data_length == 1)
        {
            uint8_t id_length = *((uint8_t *) p_data);
            if (id_length == NFCID1_SINGLE_SIZE || id_length == NFCID1_DOUBLE_SIZE ||
                id_length == NFCID1_TRIPLE_SIZE)
            {
                m_nfcid1_length = id_length;
                hal_nfc_nfcid1_default_bytes();
            }
            else
            {
                return NRF_ERROR_INVALID_LENGTH;
            }
        }
        else if (data_length == NFCID1_SINGLE_SIZE || data_length == NFCID1_DOUBLE_SIZE ||
            data_length == NFCID1_TRIPLE_SIZE)
        {
            m_nfcid1_length = (uint8_t) data_length;
            memcpy(m_nfcid1_data, p_data, data_length);
        }
        else
        {
            return NRF_ERROR_INVALID_LENGTH;
        }
        hal_nfc_nfcid1_registers_setup();
    }
    else
    {
        /* No implementation needed */
    }

    return NRF_SUCCESS;
}

/* This function is used by nfc_lib for unit testing only */
ret_code_t hal_nfc_parameter_get(hal_nfc_param_id_t id, void * p_data, size_t * p_max_data_length)
{
    if (*p_max_data_length < 1)
    {
        *p_max_data_length = 1;
        return NRF_ERROR_DATA_SIZE;
    }

    if (id == HAL_NFC_PARAM_FWI)
    {
        *((uint8_t *) p_data) = m_fwi;
        *p_max_data_length    = sizeof(m_fwi);
    }
    else if (id == HAL_NFC_PARAM_SELRES)
    {
        /* Get SEL_RES 'Protocol' bits setting */
        *((uint8_t *) p_data) = m_t4t_selres;
        *p_max_data_length    = sizeof(m_t4t_selres);
    }
    else if (id == HAL_NFC_PARAM_DID)
    {
        *((uint8_t *) p_data) = m_did;
        *p_max_data_length    = sizeof(m_did);
    }
    else if (id == HAL_NFC_PARAM_NFCID1)
    {
        if (m_nfcid1_length == 0)
        {
            m_nfcid1_length = NFCID1_DEFAULT_LENGHT;
            hal_nfc_nfcid1_default_bytes();
        }

        if (*p_max_data_length < (size_t) m_nfcid1_length)
        {
            return NRF_ERROR_DATA_SIZE;
        }

        *p_max_data_length = (size_t) m_nfcid1_length;
        memcpy(p_data, m_nfcid1_data, m_nfcid1_length);
    }
    else
    {
        /* No implementation needed */
    }

    return NRF_SUCCESS;
}


ret_code_t hal_nfc_start(void)
{
    NRF_NFCT->ERRORSTATUS = NRF_NFCT_ERRORSTATUS_ALL;
    NRF_NFCT->TASKS_SENSE = 1;

    NVIC_ClearPendingIRQ(NFCT_IRQn);
    NVIC_SetPriority(NFCT_IRQn, NFCT_CONFIG_IRQ_PRIORITY);
    NVIC_EnableIRQ(NFCT_IRQn);

    NRF_LOG_INFO("Start");
    return NRF_SUCCESS;
}


ret_code_t hal_nfc_send(const uint8_t * p_data, size_t data_length)
{
    if (data_length == 0)
    {
        return NRF_ERROR_DATA_SIZE;
    }

    if(m_swtx_sent)
    {
        m_pending_msg_ptr     = p_data;
        m_pending_data_length = data_length;
        m_pending_msg         = true;

        NRF_LOG_DEBUG("Pending message.");
        return NRF_SUCCESS;
    }

    m_t4t_tx_waiting   = false;

    /* Ignore previous TX END events, SW takes care only for data frames which tranmission is triggered in this function */
    nrf_nfct_event_clear(&NRF_NFCT->EVENTS_TXFRAMEEND);

    NRF_NFCT->INTENSET       = (NFCT_INTENSET_TXFRAMEEND_Enabled << NFCT_INTENSET_TXFRAMEEND_Pos); //Moved to the end in T4T to avoid delaying TASKS_STARTX
    NRF_NFCT->PACKETPTR      = (uint32_t) p_data;
    NRF_NFCT->TXD.AMOUNT     = (data_length << NFCT_TXD_AMOUNT_TXDATABYTES_Pos) &
                                NFCT_TXD_AMOUNT_TXDATABYTES_Msk;
    NRF_NFCT->FRAMEDELAYMODE = NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_WindowGrid <<
                               NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_Pos;
    NRF_NFCT->TASKS_STARTTX  = 1;

    NRF_LOG_INFO("Send");
    return NRF_SUCCESS;
}


ret_code_t hal_nfc_stop(void)
{
    NRF_NFCT->TASKS_DISABLE = 1;

    NRF_LOG_INFO("Stop");
    return NRF_SUCCESS;
}


ret_code_t hal_nfc_done(void)
{
    m_nfc_lib_callback = (hal_nfc_callback_t) NULL;

    return NRF_SUCCESS;
}


void NFCT_IRQHandler(void)
{
    nfct_field_sense_state_t current_field = NFC_FIELD_STATE_NONE;

    HAL_NFC_DEBUG_PIN_SET(HAL_NFC_NFC_EVENT_DEBUG_PIN); // DEBUG!

    if (NRF_NFCT->EVENTS_FIELDDETECTED && (NRF_NFCT->INTEN & NFCT_INTEN_FIELDDETECTED_Msk))
    {
        nrf_nfct_event_clear(&NRF_NFCT->EVENTS_FIELDDETECTED);
        HAL_NFC_DEBUG_PIN_SET(HAL_NFC_DETECT_EVENT_DEBUG_PIN); // DEBUG!
        current_field = NFC_FIELD_STATE_ON;
        HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_DETECT_EVENT_DEBUG_PIN); // DEBUG!

        NRF_LOG_DEBUG("Field detected");
    }

#ifndef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
    if (NRF_NFCT->EVENTS_FIELDLOST && (NRF_NFCT->INTEN & NFCT_INTEN_FIELDLOST_Msk))
    {
        nrf_nfct_event_clear(&NRF_NFCT->EVENTS_FIELDLOST);
        current_field =
           (current_field == NFC_FIELD_STATE_NONE) ? NFC_FIELD_STATE_OFF : NFC_FIELD_STATE_UNKNOWN;

        NRF_LOG_DEBUG("Field lost");
    }
#endif // HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND

    /* Perform actions if any FIELD event is active */
    if (current_field != NFC_FIELD_STATE_NONE)
    {
        nrf_nfct_field_event_handler(current_field);
    }

    if (NRF_NFCT->EVENTS_RXFRAMEEND && (NRF_NFCT->INTEN & NFCT_INTEN_RXFRAMEEND_Msk))
    {
        /* Take into account only number of whole bytes */
        uint32_t rx_status    = 0;
        uint32_t rx_data_size = ((NRF_NFCT->RXD.AMOUNT & NFCT_RXD_AMOUNT_RXDATABYTES_Msk) >>
                                 NFCT_RXD_AMOUNT_RXDATABYTES_Pos) - NFC_CRC_SIZE;
        nrf_nfct_event_clear(&NRF_NFCT->EVENTS_RXFRAMEEND);

        if (NRF_NFCT->EVENTS_RXERROR && (NRF_NFCT->INTEN & NFCT_INTEN_RXERROR_Msk))
        {
            rx_status = (NRF_NFCT->FRAMESTATUS.RX & NRF_NFCT_FRAMESTATUS_RX_MSK);
            nrf_nfct_event_clear(&NRF_NFCT->EVENTS_RXERROR);

            NRF_LOG_DEBUG("Rx error (0x%x)", (unsigned int) rx_status);

            /* Clear rx frame status */
            NRF_NFCT->FRAMESTATUS.RX = NRF_NFCT_FRAMESTATUS_RX_MSK;
        }

        /* Ignore all NFC-A data frames with Transmission Error */
        if (rx_status)
        {
            /* Go back to idle state if currently in the ACTIVE_A state */
            if (!m_t4t_active)
            {
                nrf_nfct_default_state_reset();
            }
            /* Stay in the CARD_EMULATOR_4A state */
            else
            {
                /* Command with Transmission Error, so wait for next frame reception */
                NRF_NFCT->TASKS_ENABLERXDATA = 1;
            }
        }
        else
        {
            /* Look for NFC-A Commands */
            if (!m_t4t_active)
            {
                // 'NFC Forum Digital Protocol Technical Specification 2.0, 14.6.1.13' */
                if ((m_nfc_rx_buffer[0] == NFC_T4T_RATS_CMD) &&
                    ((m_nfc_rx_buffer[1] & NFC_T4T_RATS_DID_MASK) != NFC_T4T_RATS_DID_RFU))
                {
                    /* Disable Auto Collision Resolution */
                    NRF_NFCT_AUTOCOLRESCONFIG = NRF_NFCT_AUTOCOLRESCONFIG |
                                                (1u << NRF_NFCT_AUTOCOLRESCONFIG_Pos);
                    m_t4t_active = true;
                    NRF_LOG_DEBUG("RX: T4T Activate");
                }
                /* Indicate that SLP_REQ was received - this will cause FRAMEDELAYTIMEOUT error */
                else if (m_nfc_rx_buffer[0] == NFC_SLP_REQ_CMD)
                {
                    // disable RX here (will enable at SELECTED)
                    m_slp_req_received = true;
                    NRF_NFCT->INTENCLR = NFCT_INTENCLR_RXFRAMEEND_Clear << NFCT_INTENCLR_RXFRAMEEND_Pos;
                }
                else
                {
                    nrf_nfct_default_state_reset();
                }
            }
            /* Look for Tag 4 Type Commands */
            else
            {
                bool    did_present;
                uint8_t did;

                did_present = (m_nfc_rx_buffer[0] & NFC_T4T_DID_BIT) != 0;
                did         = m_did;

                // React only to the ISO-DEP blocks that are directed to our tag.
                if ((!did_present) && (did > 0)) // 'NFC Forum Digital Protocol Technical Specification 2.0, 16.1.2.12' */
                {
                    /* Not our ISO-DEP block, so wait for next frame reception */
                    NRF_NFCT->TASKS_ENABLERXDATA = 1;
                }
                else if ((!did_present) || (did == (m_nfc_rx_buffer[1] & NFC_T4T_DID_MASK)))
                {
                    if ((m_nfc_rx_buffer[0] & NFC_T4T_S_BLOCK_MSK) == NFC_T4T_S_DESELECT)
                    {
                        m_deselect = true;
                        NRF_LOG_DEBUG("RX: T4T Deselect");
                    }
                    else if (m_swtx_sent && ((m_nfc_rx_buffer[0] & NFC_T4T_S_BLOCK_MSK) == NFC_T4T_S_WTX))
                    {
                        m_swtx_sent = false;

                        NRF_LOG_DEBUG("RX: S(WTX) response");

                        if (m_pending_msg)
                        {
                            m_pending_msg = false;

                            nrf_nfct_event_clear(&NRF_NFCT->EVENTS_TXFRAMEEND);

                            NRF_NFCT->INTENSET       = (NFCT_INTENSET_TXFRAMEEND_Enabled <<
                                                        NFCT_INTENSET_TXFRAMEEND_Pos);
                            NRF_NFCT->PACKETPTR      = (uint32_t) m_pending_msg_ptr;
                            NRF_NFCT->TXD.AMOUNT     = (m_pending_data_length <<
                                                        NFCT_TXD_AMOUNT_TXDATABYTES_Pos) &
                                                        NFCT_TXD_AMOUNT_TXDATABYTES_Msk;
                            NRF_NFCT->FRAMEDELAYMODE = NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_WindowGrid <<
                                                       NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_Pos;
                            NRF_NFCT->TASKS_STARTTX  = 1;

                            m_t4t_tx_waiting   = false;
                            NRF_LOG_DEBUG("Sending pending message!");
                        }
                        else
                        {
                            hal_nfc_wtx_data_set(did_present);
                        }
                    }
                    else if ((m_nfc_rx_buffer[0] & NFC_T4T_BLOCK_MSK) == NFC_T4T_I_BLOCK)
                    {
                        /* Set up default transmission of S(WTX) block. Tx will be executed only if FDT timer
                        * expires (FrameDelayMode-ExactVal) before hal_nfc_send is called */
                        hal_nfc_wtx_data_set(did_present);

                        NRF_NFCT->INTENSET = (NFCT_INTENSET_TXFRAMEEND_Enabled <<
                                            NFCT_INTENSET_TXFRAMEEND_Pos);
                    }
                    else
                    {
                        /* Not a valid ISO-DEP block, so wait for next frame reception */
                        NRF_NFCT->TASKS_ENABLERXDATA = 1;
                    }
                }
                else
                {
                    /* Not our ISO-DEP block, so wait for next frame reception */
                    NRF_NFCT->TASKS_ENABLERXDATA = 1;
                }
            }

            if (m_nfc_lib_callback != NULL)
            {
                /* This callback should trigger transmission of READ Response */
                m_nfc_lib_callback(m_nfc_lib_context,
                                   HAL_NFC_EVENT_DATA_RECEIVED,
                                   (void *)m_nfc_rx_buffer,
                                   rx_data_size);
            }
            /* Clear TXFRAMESTART EVENT so it can be checked in hal_nfc_send */
            nrf_nfct_event_clear(&NRF_NFCT->EVENTS_TXFRAMESTART);
        }
        NRF_LOG_DEBUG("Rx fend");
    }

    if (NRF_NFCT->EVENTS_TXFRAMEEND && (NRF_NFCT->INTEN & NFCT_INTEN_TXFRAMEEND_Msk))
    {
        nrf_nfct_event_clear(&NRF_NFCT->EVENTS_TXFRAMEEND);

        /* Disable TX END event to ignore frame transmission other than READ response */
        NRF_NFCT->INTENCLR = (NFCT_INTENCLR_TXFRAMEEND_Clear << NFCT_INTENCLR_TXFRAMEEND_Pos);

        if (m_deselect)
        {
            /* Re-enable Auto Collision Resolution */
            NRF_NFCT_AUTOCOLRESCONFIG = NRF_NFCT_AUTOCOLRESCONFIG &
                                        ~(1u << NRF_NFCT_AUTOCOLRESCONFIG_Pos);
            NRF_NFCT->TASKS_GOSLEEP   = 1;
            /* Disable RX here (will be enabled at SELECTED) */
            NRF_NFCT->INTENCLR        = NFCT_INTENCLR_RXFRAMEEND_Clear <<
                                        NFCT_INTENCLR_RXFRAMEEND_Pos;
            m_deselect   = false;
            m_t4t_active = false;
        }
        else
        {
            /* Set up for reception */
            NRF_NFCT->PACKETPTR          = (uint32_t) m_nfc_rx_buffer;
            NRF_NFCT->MAXLEN             = NFC_RX_BUFFER_SIZE;
            NRF_NFCT->TASKS_ENABLERXDATA = 1;
            NRF_NFCT->INTENSET           =
                        (NFCT_INTENSET_RXFRAMEEND_Enabled << NFCT_INTENSET_RXFRAMEEND_Pos) |
                        (NFCT_INTENSET_RXERROR_Enabled    << NFCT_INTENSET_RXERROR_Pos);
        }

        if (m_nfc_lib_callback != NULL)
        {
            m_nfc_lib_callback(m_nfc_lib_context, HAL_NFC_EVENT_DATA_TRANSMITTED, 0, 0);
        }

        NRF_LOG_DEBUG("Tx fend");
    }

    if (NRF_NFCT->EVENTS_SELECTED && (NRF_NFCT->INTEN & NFCT_INTEN_SELECTED_Msk))
    {
        nrf_nfct_event_clear(&NRF_NFCT->EVENTS_SELECTED);

        /* Clear also RX END and RXERROR events because SW does not take care of commands which were received before selecting the tag */
        nrf_nfct_event_clear(&NRF_NFCT->EVENTS_RXFRAMEEND);
        nrf_nfct_event_clear(&NRF_NFCT->EVENTS_RXERROR);

        /* Set up registers for EasyDMA and start receiving packets */
        NRF_NFCT->PACKETPTR          = (uint32_t) m_nfc_rx_buffer;
        NRF_NFCT->MAXLEN             = NFC_RX_BUFFER_SIZE;
        NRF_NFCT->TASKS_ENABLERXDATA = 1;

        NRF_NFCT->INTENSET = (NFCT_INTENSET_RXFRAMEEND_Enabled << NFCT_INTENSET_RXFRAMEEND_Pos) |
                             (NFCT_INTENSET_RXERROR_Enabled    << NFCT_INTENSET_RXERROR_Pos);

        /* At this point any previous error status can be ignored */
        NRF_NFCT->FRAMESTATUS.RX = NRF_NFCT_FRAMESTATUS_RX_MSK;
        NRF_NFCT->ERRORSTATUS    = NRF_NFCT_ERRORSTATUS_ALL;

#ifndef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND
        /* Change mask to FIELD_ON state - trigger FIELD_ON only if HW has locked to the field */
        m_nfc_fieldpresent_mask = NFC_FIELD_ON_MASK;
#endif // HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND

        if (m_nfc_lib_callback != NULL)
        {
            m_nfc_lib_callback(m_nfc_lib_context, HAL_NFC_EVENT_FIELD_ON, 0, 0);
        }

        m_t4t_active          = false;
        m_swtx_sent           = false;
        m_pending_msg         = false;
        m_pending_msg_ptr     = NULL;
        m_pending_data_length = 0;

        NRF_LOG_DEBUG("Selected");
    }

    if (NRF_NFCT->EVENTS_ERROR && (NRF_NFCT->INTEN & NFCT_INTEN_ERROR_Msk))
    {
        uint32_t err_status = NRF_NFCT->ERRORSTATUS;
        nrf_nfct_event_clear(&NRF_NFCT->EVENTS_ERROR);

        /* Clear FRAMEDELAYTIMEOUT error (expected HW behaviour) when SLP_REQ command was received */
        if ((err_status & NFCT_ERRORSTATUS_FRAMEDELAYTIMEOUT_Msk) && m_slp_req_received)
        {
            NRF_NFCT->ERRORSTATUS = NFCT_ERRORSTATUS_FRAMEDELAYTIMEOUT_Msk;
            m_slp_req_received    = false;

            NRF_LOG_DEBUG("RX: SLP_REQ");
        }
        /* Report any other error */
        err_status &= ~NFCT_ERRORSTATUS_FRAMEDELAYTIMEOUT_Msk;

        if (err_status)
        {
            NRF_LOG_DEBUG("Error (0x%x)", (unsigned int) err_status);
        }

        /* Clear error status */
        NRF_NFCT->ERRORSTATUS = NRF_NFCT_ERRORSTATUS_ALL;
    }

    if (NRF_NFCT->EVENTS_TXFRAMESTART && (NRF_NFCT->INTEN & NFCT_INTEN_TXFRAMESTART_Msk))
    {
        nrf_nfct_event_clear(&NRF_NFCT->EVENTS_TXFRAMESTART);

        if (m_t4t_tx_waiting)
        {
            m_t4t_tx_waiting = false;
            m_swtx_sent      = true;

            NRF_LOG_DEBUG("Response timeout, sending WTX!");
        }
    }

    HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_NFC_EVENT_DEBUG_PIN); // DEBUG!
}


#ifdef HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND

#ifdef  HAL_NFC_NRF52840_ENGINEERING_ABC_WORKAROUND
    #error Wrong workaround combination
#endif

static uint32_t field_state_cnt = 0;
/**
 * @brief Function for evaluating and handling NFC fieldlost event.
 */
static void hal_nfc_field_check(void)
{
    uint32_t nfc_fieldpresen_masked;

    nfc_fieldpresen_masked = NRF_NFCT->FIELDPRESENT & NFC_HAL_FIELDPRESENT_MASK;

    if (nfc_fieldpresen_masked == NFC_HAL_FIELDPRESENT_IS_LOST)
    {
        ++field_state_cnt;
        if (field_state_cnt > 7)
        {
            HAL_NFC_DEBUG_PIN_SET(HAL_NFC_HCLOCK_OFF_DEBUG_PIN); // DEBUG!

            NRF_TIMER4->TASKS_SHUTDOWN = 1;

            nrf_drv_clock_hfclk_release();

            nrf_nfct_field_lost_hfclk_handle();

            if ((m_nfc_lib_callback != NULL) )
            {
                m_nfc_lib_callback(m_nfc_lib_context, HAL_NFC_EVENT_FIELD_OFF, 0, 0);
            }
            m_field_on = false;

            /* Begin:   Bugfix for FTPAN-116 (IC-12886) */
            // resume the NFCT to initialized state
            hal_nfc_re_setup();
            /* End:   Bugfix for FTPAN-116 (IC-12886) */

            HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_HCLOCK_OFF_DEBUG_PIN); // DEBUG!
        }

        return;
    }

    field_state_cnt = 0;
}


/**
 * @brief Function for enablinge hight precision clock and start eveluating fieldlost event.
 */
static inline void nrf_nfct_field_event_handler(volatile nfct_field_sense_state_t field_state)
{
    if (!m_field_on)
    {
        HAL_NFC_DEBUG_PIN_SET(HAL_NFC_HCLOCK_ON_DEBUG_PIN); // DEBUG!
        nrf_drv_clock_hfclk_request(&m_clock_handler_item);

        NRF_TIMER4->TASKS_CLEAR = 1;
        NRF_TIMER4->TASKS_START = 1;
        field_state_cnt         = 0;

        HAL_NFC_DEBUG_PIN_CLEAR(HAL_NFC_HCLOCK_ON_DEBUG_PIN); // DEBUG!
    }
    m_field_on = true;
}


/**
 * @brief Function for resume the NFCT to initialized state after software's reset.
 */
static inline void hal_nfc_re_setup(void)
{
    hal_nfc_common_hw_setup();

    NRF_LOG_INFO("Reinitialize");
}
#endif // HAL_NFC_ENGINEERING_BC_FTPAN_WORKAROUND

#endif // NFC_T4T_HAL_ENABLED
