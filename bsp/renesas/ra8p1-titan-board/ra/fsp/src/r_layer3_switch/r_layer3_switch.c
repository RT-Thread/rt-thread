/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/
#include "r_layer3_switch.h"
#include "r_rmac_phy.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/

/** "ESWM" in ASCII.  Used to determine if the control block is open. */
#define LAYER3_SWITCH_OPEN                                   (('E' << 24U) | ('S' << 16U) | ('W' << 8U) | ('M' << 0U))

#define LAYER3_SWITCH_ETHA_REG_SIZE                          (R_ETHA1_BASE - R_ETHA0_BASE)
#define LAYER3_SWITCH_RMAC_REG_SIZE                          (R_RMAC1_BASE - R_RMAC0_BASE)
#define LAYER3_SWITCH_REGISTER_SIZE                          (32)
#define LAYER3_SWITCH_QUEUE_ADDRESS_UPPER_MASK               (0xFF00000000)
#define LAYER3_SWITCH_QUEUE_ADDRESS_UPPER_POSITION           (32)
#define LAYER3_SWITCH_QUEUE_ADDRESS_LOWER_MASK               (0xFFFFFFFF)

#define LAYER3_SWITCH_FWPBFC_REGISTER_OFFSET                 (0x10)
#define LAYER3_SWITCH_FWPBFCSDC0_REGISTER_OFFSET             (0x10)
#define LAYER3_SWITCH_INTERRUPT_REGISTER_OFFSET              (0x10)
#define LAYER3_SWITCH_FWPC_REGISTER_OFFSET                   (0x10)
#define LAYER3_SWITCH_PORT_CONFIG_REGISTER_OFFSET            (0x10)
#define LAYER3_SWITCH_TS_DESCRIPTOR_QUEUE_REGISTOR_OFFSET    (0x08)
#define LAYER3_SWITCH_TS_DESCRIPTOR_TIMER_REGISTOR_OFFSET    (0x04)

/* VLAN tag bit position. */
#define LAYER3_SWITCH_VLAN_TAG_DEI_POSITION                  (12UL)
#define LAYER3_SWITCH_VLAN_TAG_PCP_POSITION                  (13UL)

/* Definitions for forwarding feature. */
#define LAYER3_SWITCH_MAC_ENTRY_MAX_NUM                      (0x7FFU)
#define LAYER3_SWITCH_VLAN_ENTRY_MAX_NUM                     (0xFFFU)
#define LAYER3_SWITCH_L3_ENTRY_MAX_NUM                       (0xFFU)
#define LAYER3_SWITCH_L3_UPDATE_REMAPPING_MAX_NUM            (0x1FU)
#define LAYER3_SWITCH_CLOCK_100MHZ                           (100U)

/* MFWD Register bitmask and position. */
#define R_MFWD_FWIP6OC_IP6IPOM1_Pos                          (16UL)
#define R_MFWD_FWIP6OC_IP6IPOM1_Msk                          (0x10000UL)
#define R_MFWD_FWIP6OC_IP6IPO1_Pos                           (20UL)
#define R_MFWD_FWIP6OC_IP6IPO1_Msk                           (0xf00000UL)
#define R_MFWD_FWRFVC0_RFSV0_Pos                             (0UL)
#define R_MFWD_FWRFVC0_RFSV0_Msk                             (0xffUL)
#define R_MFWD_FWRFVC0_RFSV1_Pos                             (8UL)
#define R_MFWD_FWRFVC0_RFSV1_Msk                             (0xff00UL)

/* Bitmask for the CPU port (GWCA). */
#define LAYER3_SWITCH_PORT_CPU_BITMASK                       (1 << BSP_FEATURE_ESWM_GWCA_PORT)
#define LAYER3_SWITCH_EATASIGSC_MASK                         (R_ETHA0_EATASIGSC_TASIGS0_Msk | \
                                                              R_ETHA0_EATASIGSC_TASIGS1_Msk | \
                                                              R_ETHA0_EATASIGSC_TASIGS2_Msk | \
                                                              R_ETHA0_EATASIGSC_TASIGS3_Msk | \
                                                              R_ETHA0_EATASIGSC_TASIGS4_Msk | \
                                                              R_ETHA0_EATASIGSC_TASIGS5_Msk | \
                                                              R_ETHA0_EATASIGSC_TASIGS6_Msk | \
                                                              R_ETHA0_EATASIGSC_TASIGS7_Msk)

/* Bitmask for unique number of timestamp. */
#define LAYER3_SWITCH_TS_UNIQUE_NUMBER_BITMASK               (0xFF)

/* For CBS feature. */
#define LAYER3_SWITCH_CBS_REQUEST_DELAY                      (50)
#define LAYER3_SWITCH_CBS_INTERFERENCE_SIZE_OFFSET           (20)
#define LAYER3_SWITCH_CBS_BITS_PER_BYTE                      (8)
#define LAYER3_SWITCH_LINK_SPEED_100M                        (100000000)
#define LAYER3_SWITCH_LINK_SPEED_1G                          (1000000000)
#define LAYER3_SWITCH_MAXIMUM_FRAME_SIZE                     (1514U)

/* FRER feature. */
#define LAYER3_SWITCH_FWSEQNGC_REGISTER_OFFSET               (0x08)
#define LAYER3_SWITCH_FRER_CHECK_PERIOD_BITMASK              (0xFFFFUL)
#define LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK                 (0x7FUL)
#define LAYER3_SWITCH_FRER_SEQ_GENERATOR_NUM_BITMASK         (0x1FUL)
#define LAYER3_SWITCH_FRER_SYSTEM_CLOCK_BITMASK              (0x3FFUL)
#define LAYER3_SWITCH_SEQ_REG_MAX_NUM                        (32)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/
#if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * layer3_switch_prv_ns_callback)(ether_switch_callback_args_t * p_args);
#elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile layer3_switch_prv_ns_callback)(ether_switch_callback_args_t * p_args);
#endif

/* Operation mode of ETHA and GWCA. */
typedef enum e_layer3_switch_agent_mode
{
    LAYER3_SWITCH_AGENT_MODE_RESET     = (0),
    LAYER3_SWITCH_AGENT_MODE_DISABLE   = (1),
    LAYER3_SWITCH_AGENT_MODE_CONFIG    = (2),
    LAYER3_SWITCH_AGENT_MODE_OPERATION = (3),
} layer3_switch_agent_mode_t;

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
void layer3_switch_gwdi_isr(void);
void layer3_switch_eaei_isr(void);

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void r_layer3_switch_module_start(void);
static void r_layer3_switch_update_gwca_operation_mode(
    layer3_switch_instance_ctrl_t * p_instance_ctrl,
    layer3_switch_agent_mode_t      mode);
static void r_layer3_switch_update_etha_operation_mode(uint8_t                    port,
                                                       layer3_switch_agent_mode_t mode);
static void r_layer3_switch_reset_coma(void);
static void r_layer3_switch_close_etha_ports(layer3_switch_instance_ctrl_t * p_instance_ctrl);
static void r_layer3_switch_initialize_linkfix_table(
    layer3_switch_instance_ctrl_t * p_instance_ctrl);
static layer3_switch_descriptor_t * r_layer3_switch_get_descriptor(layer3_switch_instance_ctrl_t * p_instance_ctrl,
                                                                   uint32_t                        queue_index,
                                                                   uint32_t                        descriptor_index);
static layer3_switch_descriptor_t * r_layer3_switch_get_current_descriptor(
    layer3_switch_instance_ctrl_t * p_instance_ctrl,
    uint32_t                        queue_index);
static bool r_layer3_switch_is_descriptor_queue_active(
    layer3_switch_instance_ctrl_t * p_instance_ctrl,
    uint32_t                        queue_index);
static void r_layer3_switch_configure_mac_address(uint8_t * p_mac_address, uint8_t port);
static void r_layer3_switch_configure_port(
    layer3_switch_instance_ctrl_t * const  p_instance_ctrl,
    uint8_t                                port,
    layer3_switch_port_cfg_t const * const p_port_cfg);

/* Forwarding features. */
static void r_layer3_switch_configure_forwarding_port(layer3_switch_forwarding_port_cfg_t const * const port_cfg,
                                                      uint8_t                                           port);
static void      r_layer3_switch_reset_table(layer3_switch_instance_ctrl_t * p_instance_ctrl);
static fsp_err_t r_layer3_switch_learn_mac_entry(layer3_switch_frame_filter_t const * const    p_target_frame,
                                                 layer3_switch_table_entry_cfg_t const * const p_entry_cfg);
static fsp_err_t r_layer3_switch_search_mac_entry(layer3_switch_frame_filter_t const * const p_target_frame,
                                                  layer3_switch_table_entry_cfg_t * const    p_entry_cfg);
static fsp_err_t r_layer3_switch_read_mac_entry(uint16_t offset, layer3_switch_table_entry_t * p_entry);
static fsp_err_t r_layer3_switch_learn_vlan_entry(layer3_switch_frame_filter_t const * const    p_target_frame,
                                                  layer3_switch_table_entry_cfg_t const * const p_entry_cfg);
static fsp_err_t r_layer3_switch_search_vlan_entry(layer3_switch_frame_filter_t const * const p_target_frame,
                                                   layer3_switch_table_entry_cfg_t * const    p_entry_cfg);
static fsp_err_t r_layer3_switch_read_vlan_entry(uint16_t offset, layer3_switch_table_entry_t * p_entry);
static fsp_err_t r_layer3_switch_learn_l3_entry(layer3_switch_instance_ctrl_t               * p_instance_ctrl,
                                                layer3_switch_frame_filter_t const * const    p_target_frame,
                                                layer3_switch_table_entry_cfg_t const * const p_entry_cfg);
static fsp_err_t r_layer3_switch_search_l3_entry(layer3_switch_frame_filter_t const    * p_target_frame,
                                                 layer3_switch_table_entry_cfg_t * const p_entry_cfg);
static fsp_err_t r_layer3_switch_learn_l3_update(layer3_switch_instance_ctrl_t          * p_instance_ctrl,
                                                 layer3_switch_l3_update_config_t * const p_config);
static fsp_err_t r_layer3_switch_search_l3_update(uint8_t routing_number, layer3_switch_l3_update_config_t * p_config);

/* MAC/VLAN forwarding. */
static fsp_err_t r_layer3_switch_enable_mac_table_aging(uint32_t aging_time);
static fsp_err_t r_layer3_switch_extract_vlan_id(layer3_switch_frame_filter_t const * const p_target_frame,
                                                 uint16_t                                 * p_vlan_id);
static void r_layer3_switch_initialize_vlan_port(layer3_switch_instance_ctrl_t                   * p_instance_ctrl,
                                                 layer3_switch_forwarding_port_cfg_t const * const p_port_cfg,
                                                 uint8_t                                           port);

/* L3 forwarding. */
static fsp_err_t r_layer3_switch_configure_stream_filter(layer3_switch_l3_stream_filter_cfg_t const * p_filter_cfg);
static uint16_t  r_layer3_switch_calculate_l3_hash(layer3_switch_frame_filter_t const * p_frame);
static uint8_t   r_layer3_switch_calculate_l3_format_code(layer3_switch_frame_filter_t const * p_frame);
static fsp_err_t r_layer3_switch_calculate_l3_stream_id(layer3_switch_frame_filter_t const * p_frame,
                                                        layer3_switch_stream_id_t          * p_stream_id);
static uint32_t r_layer3_switch_convert_vlan_tag_to_int(layer3_switch_frame_vlan_tag_t const * p_vlan_s_tag,
                                                        layer3_switch_frame_vlan_tag_t const * p_vlan_c_tag);
static fsp_err_t r_layer3_switch_remapping_l3_update(layer3_switch_instance_ctrl_t    * p_instance_ctrl,
                                                     uint32_t                           routing_number,
                                                     layer3_switch_l3_update_config_t * p_update_cfg);
static uint32_t r_layer3_switch_convert_array_to_int(uint8_t * array, uint8_t length);

/* TSN feature. */
static void r_layer3_switch_configure_cbs(layer3_switch_instance_ctrl_t const * const p_instance_ctrl,
                                          uint8_t                                     port,
                                          layer3_switch_cbs_cfg_t const * const       p_cbs_cfg);
static uint32_t r_layer3_switch_calculate_max_interference_size(uint8_t               queue_number,
                                                                uint8_t const * const p_max_burst_num_list);

/* FRER feature. */
static fsp_err_t r_layer3_switch_frer_init(layer3_switch_instance_ctrl_t  * p_instance_ctrl,
                                           layer3_switch_frer_cfg_t const * p_frer_cfg);
static void      r_layer3_switch_frer_table_reset(void);
static void      r_layer3_switch_configure_sequence_number_generation(layer3_switch_instance_ctrl_t * p_instance_ctrl);
static fsp_err_t r_layer3_switch_learn_frer_entry(layer3_switch_instance_ctrl_t    * p_instance_ctrl,
                                                  layer3_switch_frer_entry_t * const p_frer_entry,
                                                  layer3_switch_frer_entry_t * const p_sequence_recovery,
                                                  uint32_t                           sequence_recovery_id);
static fsp_err_t r_layer3_switch_learn_frer_individual_recovery(layer3_switch_instance_ctrl_t        * p_instance_ctrl,
                                                                layer3_switch_frer_entry_cfg_t * const p_frer_entry_cfg);

static void r_layer3_switch_call_callback_for_ports(layer3_switch_instance_ctrl_t * p_instance_ctrl,
                                                    ether_switch_callback_args_t  * p_callback_args,
                                                    uint32_t                        ports);
static void r_layer3_switch_call_callback(void (* p_callback)(
                                              ether_switch_callback_args_t *),
                                          ether_switch_callback_args_t       * p_callback_args,
                                          ether_switch_callback_args_t * const p_callback_memory);

/* Timestamp feature. */
static fsp_err_t r_layer3_switch_create_tx_timestamp_queue(ether_switch_ctrl_t * const                        p_ctrl,
                                                           const layer3_switch_descriptor_queue_cfg_t * const p_queue_cfg,
                                                           uint32_t * const                                   p_ts_descriptor_queue_index);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/** ETHER SWITCH API mapping for layer3 switch module. */
const ether_switch_api_t g_ether_switch_on_layer3_switch =
{
    .open  = R_LAYER3_SWITCH_Open,
    .close = R_LAYER3_SWITCH_Close,
};

/*******************************************************************************************************************//**
 * @addtogroup LAYER3_SWITCH
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * Initializes the switch module and applies configurations. Implements @ref ether_switch_api_t::open.
 *
 * @retval  FSP_SUCCESS                             Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to control block, config structure or extended config structure is NULL.
 * @retval  FSP_ERR_ALREADY_OPEN                    Control block has already been opened or channel is being used by another
 *                                                  instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_ETHER_ERROR_PHY_COMMUNICATION   Initialization of PHY-LSI failed.
 * @retval  FSP_ERR_INVALID_ARGUMENT                Invalid configuration value.
 ************************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_Open (ether_switch_ctrl_t * const p_ctrl, ether_switch_cfg_t const * const p_cfg)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    layer3_switch_extended_cfg_t  * p_extend;
    ether_phy_instance_t const    * p_ether_phy;
    volatile uint32_t             * p_mfwd_fwpbfc_reg;
    volatile uint32_t             * p_etha_eatdqdcn_reg;
    R_ETHA0_Type * p_reg_etha;
    R_RMAC0_Type * p_reg_rmac;

    fsp_err_t phy_err = FSP_SUCCESS;

#if (LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE)

    /** Check parameters. */
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_cfg);

    p_extend = (layer3_switch_extended_cfg_t *) p_cfg->p_extend;
    FSP_ASSERT(p_cfg->p_extend);
    FSP_ERROR_RETURN((0 <= p_cfg->irq), FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN((LAYER3_SWITCH_CFG_AVAILABLE_QUEUE_NUM <= BSP_FEATURE_ESWM_MAX_QUEUE_NUM),
                     FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(LAYER3_SWITCH_L3_ENTRY_MAX_NUM > p_extend->l3_filter_list_length, FSP_ERR_INVALID_ARGUMENT);
#else
    p_extend = (layer3_switch_extended_cfg_t *) p_cfg->p_extend;
#endif

    FSP_ERROR_RETURN((LAYER3_SWITCH_OPEN != p_instance_ctrl->open), FSP_ERR_ALREADY_OPEN);

    /* Initialize parameters. */
    p_instance_ctrl->p_cfg             = p_cfg;
    p_instance_ctrl->p_callback        = p_cfg->p_callback;
    p_instance_ctrl->p_gwca_reg        = R_GWCA0;
    p_instance_ctrl->table_status      = LAYER3_SWITCH_TABLE_STATUS_UNINITIALIZED;
    p_instance_ctrl->l3_entry_count    = 0;
    p_instance_ctrl->l3_routing_number = 0;

    for (uint8_t i = 0; i < BSP_FEATURE_ESWM_TS_DESCRIPTOR_QUEUE_MAX_NUM; i++)
    {
        p_instance_ctrl->ts_descriptor_queue_status_list[i] = LAYER3_SWITCH_TS_DESCRIPTOR_QUEUE_STATUS_UNUSED;
    }

    /* Clear module stops. */
    r_layer3_switch_module_start();

    /* Reset COMA IP. */
    r_layer3_switch_reset_coma();

    /* When a r_gptp instance is set, initialize it. */
    if (NULL != p_extend->p_gptp_instance)
    {
        p_extend->p_gptp_instance->p_api->open(p_extend->p_gptp_instance->p_ctrl, p_extend->p_gptp_instance->p_cfg);
    }

    /* Configure destination ports of forwarding feature. */
    for (uint32_t i = 0; i < BSP_FEATURE_ETHER_NUM_CHANNELS; i++)
    {
        p_mfwd_fwpbfc_reg =
            (uint32_t *) ((uintptr_t) &(R_MFWD->FWPBFC0) + (i * LAYER3_SWITCH_FWPBFC_REGISTER_OFFSET));
        *p_mfwd_fwpbfc_reg |= (R_MFWD_FWPBFC0_PBDV_Msk & p_extend->fowarding_target_port_masks[i]);
    }

    /* Enable extended descriptor for each agents. */
    R_MFWD->FWPC10_b.DDE = 0x1;
    R_MFWD->FWPC11_b.DDE = 0x1;
    R_MFWD->FWPC12_b.DDE = 0x1;

    /* Set GWCA to CONFIG mode. */
    r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_DISABLE);
    r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_CONFIG);

    /* Reset AXI RAM. */
    p_instance_ctrl->p_gwca_reg->GWARIRM_b.ARIOG = 1;
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_gwca_reg->GWARIRM_b.ARR, 1);

    /* Initialize LINKFIX table. */
    r_layer3_switch_initialize_linkfix_table(p_instance_ctrl);

    /* Set GWCA to OPERATION mode. */
    r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_DISABLE);
    r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_OPERATION);

    /* ETHA ports initialization. */
    for (uint8_t channel = 0; (channel < BSP_FEATURE_ETHER_NUM_CHANNELS) && (FSP_SUCCESS == phy_err); channel++)
    {
        if (NULL != p_extend->p_ether_phy_instances[channel])
        {
            /* Set ETHA to CONFIG mode. */
            r_layer3_switch_update_etha_operation_mode(channel, LAYER3_SWITCH_AGENT_MODE_DISABLE);
            r_layer3_switch_update_etha_operation_mode(channel, LAYER3_SWITCH_AGENT_MODE_CONFIG);

            /* Configure the port specific feature. */
            if (NULL != p_extend->p_port_cfg_list[channel])
            {
                r_layer3_switch_configure_port(p_instance_ctrl, channel, p_extend->p_port_cfg_list[channel]);
            }

            /* Configure queue depth for each transmission IPV queue. */
            p_reg_etha          = (R_ETHA0_Type *) (R_ETHA0_BASE + (LAYER3_SWITCH_ETHA_REG_SIZE * channel));
            p_etha_eatdqdcn_reg = &p_reg_etha->EATDQDC0;
            for (uint8_t j = 0; j < BSP_FEATURE_ESWM_ETHA_IPV_QUEUE_NUM; j++)
            {
                *p_etha_eatdqdcn_reg = p_extend->ipv_queue_depth_list[channel][j] & R_ETHA0_EATDQDC0_DQD_Msk;
                p_etha_eatdqdcn_reg += 1;
            }

            /* Enable Magic packet detection. */
            p_reg_rmac =
                (R_RMAC0_Type *) (R_RMAC0_BASE + (channel * LAYER3_SWITCH_RMAC_REG_SIZE));
            p_reg_rmac->MRGC_b.MPDE = 1;

            if (NULL != p_extend->p_gptp_instance)
            {
                p_reg_rmac->MTRC_b.DTN = (uint8_t) (p_extend->gptp_timer_numbers[channel] & 0x1);
            }
        }
    }

    /* Open all ETHER_PHY instances. */
    for (uint8_t channel = 0;
         (channel < BSP_FEATURE_ETHER_NUM_CHANNELS) && ((FSP_SUCCESS == phy_err) | (FSP_ERR_ALREADY_OPEN == phy_err));
         channel++)
    {
        p_ether_phy = p_extend->p_ether_phy_instances[channel];
        if (NULL != p_ether_phy)
        {
            p_ether_phy->p_api->open(p_ether_phy->p_ctrl, p_ether_phy->p_cfg);
        }
    }

    /* Start operation on ETHA ports. */
    for (uint8_t channel = 0; (channel < BSP_FEATURE_ETHER_NUM_CHANNELS) && (FSP_SUCCESS == phy_err); channel++)
    {
        p_ether_phy = p_extend->p_ether_phy_instances[channel];
        if (NULL != p_ether_phy)
        {
            /* Set ETHA to OPERATION mode. */
            r_layer3_switch_update_etha_operation_mode(channel, LAYER3_SWITCH_AGENT_MODE_DISABLE);
            r_layer3_switch_update_etha_operation_mode(channel, LAYER3_SWITCH_AGENT_MODE_OPERATION);

            /* Initialize each PHY LSI. */
            R_RMAC_PHY_ChipSelect(p_ether_phy->p_ctrl, channel);
            phy_err = p_ether_phy->p_api->chipInit(p_ether_phy->p_ctrl, p_ether_phy->p_cfg);
            if (phy_err != FSP_SUCCESS)
            {
                break;
            }

            phy_err = p_ether_phy->p_api->startAutoNegotiate(p_ether_phy->p_ctrl);
        }
    }

    /* If failed to open a PHY instance, revert all configurations and return error. */
    if (FSP_SUCCESS != phy_err)
    {
        /* Close ETHA IP and other PHY instances. */
        r_layer3_switch_close_etha_ports(p_instance_ctrl);

        /* Disable GWCA. */
        r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_DISABLE);

        /* Reset destination ports of forwarding feature. */
        for (uint32_t i = 0; i < BSP_FEATURE_ETHER_NUM_CHANNELS; i++)
        {
            p_mfwd_fwpbfc_reg =
                (uint32_t *) ((uintptr_t) &(R_MFWD->FWPBFC0) + (i * LAYER3_SWITCH_FWPBFC_REGISTER_OFFSET));
            *p_mfwd_fwpbfc_reg = 0;
        }

        /* Disable extended descriptor for each agents. */
        R_MFWD->FWPC10_b.DDE = 0;
        R_MFWD->FWPC11_b.DDE = 0;
        R_MFWD->FWPC12_b.DDE = 0;

        FSP_RETURN(FSP_ERR_ETHER_ERROR_PHY_COMMUNICATION);
    }

    /* Enable GWCA Data Interrupt IRQ. It occurs when a descriptor completes RX/TX or receive frame for a full queue. */
    R_BSP_IrqCfgEnable(p_instance_ctrl->p_cfg->irq, p_instance_ctrl->p_cfg->ipl, p_instance_ctrl);
    if (p_extend->etha_error_irq_port_0 >= 0)
    {
        R_BSP_IrqCfgEnable(p_extend->etha_error_irq_port_0, p_extend->etha_error_ipl_port_0, p_instance_ctrl);
    }

    if (p_extend->etha_error_irq_port_1 >= 0)
    {
        R_BSP_IrqCfgEnable(p_extend->etha_error_irq_port_1, p_extend->etha_error_ipl_port_1, p_instance_ctrl);
    }

    p_instance_ctrl->open = LAYER3_SWITCH_OPEN;

    return FSP_SUCCESS;
}                                      /* End of function R_LAYER3_SWITCH_Open() */

/********************************************************************************************************************//**
 * @brief Disables interrupts and stop module. Implements @ref ether_switch_api_t::close.
 *
 * @retval  FSP_SUCCESS                                 Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION                           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            Control block is not open.
 ***********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_Close (ether_switch_ctrl_t * const p_ctrl)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    layer3_switch_extended_cfg_t  * p_extend;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    p_extend = (layer3_switch_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Disable GWCA Data Interrupt IRQ. */
    R_BSP_IrqDisable(p_instance_ctrl->p_cfg->irq);
    R_FSP_IsrContextSet(p_instance_ctrl->p_cfg->irq, NULL);

    if (p_extend->etha_error_irq_port_0 >= 0)
    {
        R_BSP_IrqDisable(p_extend->etha_error_irq_port_0);
        R_FSP_IsrContextSet(p_extend->etha_error_irq_port_0, NULL);
    }

    if (p_extend->etha_error_irq_port_1 >= 0)
    {
        R_BSP_IrqDisable(p_extend->etha_error_irq_port_1);
        R_FSP_IsrContextSet(p_extend->etha_error_irq_port_1, NULL);
    }

    /* Close ETHA ports and PHY instances. */
    r_layer3_switch_close_etha_ports(p_instance_ctrl);

    /* When a r_gptp instance is set, close it. */
    if (NULL != p_extend->p_gptp_instance)
    {
        p_extend->p_gptp_instance->p_api->close(p_extend->p_gptp_instance->p_ctrl);
    }

    /* Set GWCA to DISABLE mode. */
    r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_DISABLE);

    /* Waiting for all pointers to be released. */
    FSP_HARDWARE_REGISTER_WAIT(R_COMA->CABPPCM_b.RPC, R_COMA->CABPPCM_b.TPC)

    /* Not set ESWM module stop feature because it shared with EtherCAT.*/

    /* Reset instance ctrl members. */
    p_instance_ctrl->p_cfg = NULL;
    memset(p_instance_ctrl->p_queues_status, 0, sizeof(p_instance_ctrl->p_queues_status));
    p_instance_ctrl->table_status = LAYER3_SWITCH_TABLE_STATUS_UNINITIALIZED;

    /* Mark the driver as closed. */
    p_instance_ctrl->open = 0U;

    return FSP_SUCCESS;
}                                      /* End of function R_LAYER3_SWITCH_Close() */

/********************************************************************************************************************//**
 * @brief Create a new descriptor queue and set it to LINKFIX table.
 * This function must be called before calling @ref R_LAYER3_SWITCH_SetDescriptor and @ref R_LAYER3_SWITCH_GetDescriptor.
 *
 * @retval  FSP_SUCCESS                                 Descriptor created successfully.
 * @retval  FSP_ERR_ASSERTION                           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            Control block is not open.
 * @retval  FSP_ERR_INVALID_POINTER                     Pointer to a argument is NULL.
 * @retval  FSP_ERR_OUT_OF_MEMORY                       Descriptor queue list is depleted.
 * @retval  FSP_ERR_OVERFLOW                            TS descriptor queue is used.
 ***********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_CreateDescriptorQueue (ether_switch_ctrl_t * const                        p_ctrl,
                                                 uint32_t * const                                   p_queue_index,
                                                 const layer3_switch_descriptor_queue_cfg_t * const p_queue_cfg)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    uint32_t  queue_index;
    fsp_err_t err = FSP_SUCCESS;

    volatile uint32_t * p_gwca_gwdcc_reg;
    volatile uint32_t * p_gwca_gwdie_reg;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_queue_index, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(NULL != p_queue_cfg, FSP_ERR_INVALID_POINTER);
    if (LAYER3_SWITCH_DISCRIPTOR_FORMTAT_TX_TIMESTAMP == p_queue_cfg->descriptor_format)
    {
        FSP_ERROR_RETURN(NULL != p_queue_cfg->p_ts_descriptor_array, FSP_ERR_INVALID_POINTER);
    }
    else
    {
        FSP_ERROR_RETURN(NULL != p_queue_cfg->p_descriptor_array, FSP_ERR_INVALID_POINTER);
    }
#endif

    if (LAYER3_SWITCH_DISCRIPTOR_FORMTAT_TX_TIMESTAMP == p_queue_cfg->descriptor_format)
    {
        err = r_layer3_switch_create_tx_timestamp_queue(p_instance_ctrl, p_queue_cfg, p_queue_index);
    }
    else
    {
        queue_index = p_instance_ctrl->allocated_descriptor_queue_index;
        FSP_ERROR_RETURN(LAYER3_SWITCH_CFG_AVAILABLE_QUEUE_NUM > queue_index, FSP_ERR_OUT_OF_MEMORY);

        /* Set all descriptors of new queue as disable. */
        for (uint32_t i = 0; i < p_queue_cfg->array_length; i++)
        {
            p_queue_cfg->p_descriptor_array[i].basic.dt = LAYER3_SWITCH_DESCRIPTOR_TYPE_LEMPTY;
        }

        /* Set the new queue to LINKFIX table. */
        p_instance_ctrl->p_descriptor_queue_list[queue_index].ptr_h =
            (LAYER3_SWITCH_QUEUE_ADDRESS_UPPER_MASK & (uint64_t) (uintptr_t) p_queue_cfg->p_descriptor_array) >>
            LAYER3_SWITCH_QUEUE_ADDRESS_UPPER_POSITION;
        p_instance_ctrl->p_descriptor_queue_list[queue_index].ptr_l =
            LAYER3_SWITCH_QUEUE_ADDRESS_LOWER_MASK & (uintptr_t) p_queue_cfg->p_descriptor_array;
        p_instance_ctrl->p_descriptor_queue_list[queue_index].dt = LAYER3_SWITCH_DESCRIPTOR_TYPE_LINKFIX;

        /* Configure the new queue.*/
        p_gwca_gwdcc_reg  = &(p_instance_ctrl->p_gwca_reg->GWDCC0) + queue_index;
        *p_gwca_gwdcc_reg =
            (uint32_t) ((p_queue_cfg->write_back_mode << R_GWCA0_GWDCC0_SM_Pos) |
                        (p_queue_cfg->descriptor_format << R_GWCA0_GWDCC0_EDE_Pos) |
                        (p_queue_cfg->rx_timestamp_storage << R_GWCA0_GWDCC0_ETS_Pos) |
                        (p_queue_cfg->type << R_GWCA0_GWDCC0_DQT_Pos));

        /* Enable GWCA Data Interrupt of this queue. */
        /* Get register address. Use GWDIE0 for queue 0-31, GWDIE1 for queue 32-63. */
        p_gwca_gwdie_reg = (uint32_t *) ((uintptr_t) &(p_instance_ctrl->p_gwca_reg->GWDIE0) +
                                         ((queue_index / LAYER3_SWITCH_REGISTER_SIZE) *
                                          LAYER3_SWITCH_INTERRUPT_REGISTER_OFFSET));

        /* Set bit field of this queue. */
        *p_gwca_gwdie_reg = (*p_gwca_gwdie_reg) | (1 << (queue_index % LAYER3_SWITCH_REGISTER_SIZE));

        /* Enable also Descriptor Full Error Interrupt. */
        p_gwca_gwdie_reg = (uint32_t *) ((uintptr_t) &(p_instance_ctrl->p_gwca_reg->GWEIE20) +
                                         ((queue_index / LAYER3_SWITCH_REGISTER_SIZE) *
                                          LAYER3_SWITCH_INTERRUPT_REGISTER_OFFSET));
        *p_gwca_gwdie_reg = (*p_gwca_gwdie_reg) | (1 << (queue_index % LAYER3_SWITCH_REGISTER_SIZE));

        /* Initialize software queue status. */
        p_instance_ctrl->p_queues_status[queue_index].created     = true;
        p_instance_ctrl->p_queues_status[queue_index].head        = 0;
        p_instance_ctrl->p_queues_status[queue_index].tail        = 0;
        p_instance_ctrl->p_queues_status[queue_index].p_queue_cfg = p_queue_cfg;

        /* Store queue index. */
        *p_queue_index = queue_index;
        p_instance_ctrl->allocated_descriptor_queue_index += 1;
    }

    return err;
}                                      /* End of function R_LAYER3_SWITCH_CreateDescriptorQueue() */

/********************************************************************************************************************//**
 * @brief Set descriptor data to a target descriptor.
 *
 * @retval  FSP_SUCCESS                                 Descriptor set successfully.
 * @retval  FSP_ERR_ASSERTION                           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            Control block is not open.
 * @retval  FSP_ERR_INVALID_POINTER                     Pointer to a argument is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Queue index is invalid.
 * @retval  FSP_ERR_NOT_INITIALIZED                     This descriptor queue is not created.
 * @retval  FSP_ERR_IN_USE                              Target descriptor is now running.
 * @retval  FSP_ERR_OVERFLOW                            Descriptor queue is full.
 ***********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_SetDescriptor (ether_switch_ctrl_t * const              p_ctrl,
                                         uint32_t                                 queue_index,
                                         layer3_switch_descriptor_t const * const p_descriptor)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    layer3_switch_descriptor_t    * p_target_descriptor;
    layer3_switch_descriptor_type_t active_descriptor_type;
    fsp_err_t err = FSP_SUCCESS;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_descriptor, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(LAYER3_SWITCH_CFG_AVAILABLE_QUEUE_NUM > queue_index, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_instance_ctrl->p_queues_status[queue_index].created, FSP_ERR_NOT_INITIALIZED);
#endif

    /* The last descriptor of the queue cannot be rewritten. */
    FSP_ERROR_RETURN(p_instance_ctrl->p_queues_status[queue_index].tail <
                     p_instance_ctrl->p_queues_status[queue_index].p_queue_cfg->array_length - 1,
                     FSP_ERR_OVERFLOW);

    /* Get pointer to the target descriptor. */
    p_target_descriptor =
        r_layer3_switch_get_descriptor(p_instance_ctrl, queue_index,
                                       p_instance_ctrl->p_queues_status[queue_index].tail);

    /* Check the descriptor queue is in TX queue or RX queue. */
    if (LAYER3_SWITCH_QUEUE_TYPE_TX == p_instance_ctrl->p_queues_status[queue_index].p_queue_cfg->type)
    {
        /* In TX queue, FSINGLE descriptor is active. */
        active_descriptor_type = LAYER3_SWITCH_DESCRIPTOR_TYPE_FSINGLE;
    }
    else                               /* When RX descriptor queue. */
    {
        /* In RX queue, FEMPTY descriptor is active. */
        active_descriptor_type = LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY;
    }

    /* Check if the target descriptor is active. Set is only permitted to a stopped descriptor. */
    if ((active_descriptor_type == p_target_descriptor->basic.dt) &&
        (LAYER3_SWITCH_DESCRIPTOR_TYPE_LEMPTY != p_descriptor->basic.dt))
    {
        err = FSP_ERR_IN_USE;
    }
    else
    {
        /* Copy all fields in the descriptor. */
        memcpy(p_target_descriptor, p_descriptor, sizeof(layer3_switch_descriptor_t));
        p_instance_ctrl->p_queues_status[queue_index].tail += 1;

        /* RX queue become available. */
        if (LAYER3_SWITCH_QUEUE_TYPE_RX == p_instance_ctrl->p_queues_status[queue_index].p_queue_cfg->type)
        {
            p_instance_ctrl->p_queues_status[queue_index].rx_available = true;
        }
    }

    return err;
}                                      /* End of function R_LAYER3_SWITCH_SetDescriptor() */

/********************************************************************************************************************//**
 * @brief Get descriptor data from a target descriptor.
 *
 * @retval  FSP_SUCCESS                                 Descriptor got successfully.
 * @retval  FSP_ERR_ASSERTION                           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            Control block is not open.
 * @retval  FSP_ERR_INVALID_POINTER                     Pointer to a argument is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Queue index is invalid.
 * @retval  FSP_ERR_NOT_INITIALIZED                     This descriptor queue is not created or target descriptor is not set.
 * @retval  FSP_ERR_IN_USE                              Target descriptor is now running.
 ***********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_GetDescriptor (ether_switch_ctrl_t * const        p_ctrl,
                                         uint32_t                           queue_index,
                                         layer3_switch_descriptor_t * const p_descriptor)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    layer3_switch_descriptor_t    * p_target_descriptor;
    layer3_switch_descriptor_type_t active_descriptor_type;
    fsp_err_t err = FSP_SUCCESS;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(NULL != p_descriptor, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(LAYER3_SWITCH_CFG_AVAILABLE_QUEUE_NUM > queue_index, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_instance_ctrl->p_queues_status[queue_index].created, FSP_ERR_NOT_INITIALIZED);
#endif

    /* Get pointer to the target descriptor. */
    p_target_descriptor =
        r_layer3_switch_get_descriptor(p_instance_ctrl, queue_index,
                                       p_instance_ctrl->p_queues_status[queue_index].head);

    /* Check the descriptor queue is in TX queue or RX queue. */
    if (LAYER3_SWITCH_QUEUE_TYPE_TX == p_instance_ctrl->p_queues_status[queue_index].p_queue_cfg->type)
    {
        /* In TX queue, FSINGLE descriptor is active. */
        active_descriptor_type = LAYER3_SWITCH_DESCRIPTOR_TYPE_FSINGLE;
    }
    else                               /* When RX descriptor queue. */
    {
        /* In RX queue, FEMPTY descriptor is active. */
        active_descriptor_type = LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY;
    }

    /* Check if the target descriptor is active. Get is only permitted to a stopped descriptor. */
    if (active_descriptor_type == p_target_descriptor->basic.dt)
    {
        err = FSP_ERR_IN_USE;
    }
    else if (LAYER3_SWITCH_DESCRIPTOR_TYPE_LEMPTY == p_target_descriptor->basic.dt)
    {
        err = FSP_ERR_NOT_INITIALIZED;
    }
    else
    {
        /* Copy the all descriptor fields to a argument.*/
        memcpy(p_descriptor, p_target_descriptor, sizeof(layer3_switch_descriptor_t));

        p_instance_ctrl->p_queues_status[queue_index].head += 1;
    }

    return err;
}                                      /* End of function R_LAYER3_SWITCH_GetDescriptor() */

/********************************************************************************************************************//**
 * @brief Reload and enable a descriptor queue.
 * In a TX descriptor queue, the queue start transmission. In a RX descriptor queue, the queue start reception.
 *
 * @retval  FSP_SUCCESS                                 Descriptor queue started successfully.
 * @retval  FSP_ERR_ASSERTION                           Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            Control block is not open.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Queue index is invalid.
 * @retval  FSP_ERR_NOT_INITIALIZED                     Target descriptor queue is not created.
 * @retval  FSP_ERR_IN_USE                              Target descriptor queue is already running.
 * @retval  FSP_ERR_INVALID_DATA                       Target TX queue have no data.
 ***********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_StartDescriptorQueue (ether_switch_ctrl_t * const p_ctrl, uint32_t queue_index)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;

    volatile uint32_t          * p_gwca_gwdcc_reg;
    volatile uint32_t          * p_gwca_gwtrc_reg;
    volatile uint32_t          * p_mfwd_fwpbfcsdc0_reg;
    layer3_switch_descriptor_t * p_descriptor;
    fsp_err_t err = FSP_SUCCESS;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(NULL != p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(LAYER3_SWITCH_CFG_AVAILABLE_QUEUE_NUM > queue_index, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_instance_ctrl->p_queues_status[queue_index].created, FSP_ERR_NOT_INITIALIZED);
#endif

    /* The target descriptor queue should be stopped. */
    if (LAYER3_SWITCH_QUEUE_TYPE_RX == p_instance_ctrl->p_queues_status[queue_index].p_queue_cfg->type)
    {
        /* RX queue should have been set a new buffer. */
        FSP_ERROR_RETURN(p_instance_ctrl->p_queues_status[queue_index].rx_available, FSP_ERR_IN_USE);
        p_instance_ctrl->p_queues_status[queue_index].rx_available = false;
    }
    else
    {
        /* TX queue should have completed previous transmission. */
        FSP_ERROR_RETURN(!r_layer3_switch_is_descriptor_queue_active(p_instance_ctrl, queue_index), FSP_ERR_IN_USE);

        /* Reset descriptor index of this queue. */
        p_instance_ctrl->p_queues_status[queue_index].head = 0;
        p_instance_ctrl->p_queues_status[queue_index].tail = 0;

        /* When the head of the queue has no data, do not start transmission. */
        p_descriptor = r_layer3_switch_get_descriptor(p_instance_ctrl, queue_index, 0);
        FSP_ERROR_RETURN(LAYER3_SWITCH_DESCRIPTOR_TYPE_LEMPTY != p_descriptor->basic.dt, FSP_ERR_INVALID_DATA);
    }

    /* Reload the queue. */
    p_gwca_gwdcc_reg   = &(p_instance_ctrl->p_gwca_reg->GWDCC0) + queue_index;
    *p_gwca_gwdcc_reg |= R_GWCA0_GWDCC0_BALR_Msk;
    FSP_HARDWARE_REGISTER_WAIT((*p_gwca_gwdcc_reg & R_GWCA0_GWDCC0_BALR_Msk), 0);

    /* Check if target descriptor queue type is TX or RX. */
    if (LAYER3_SWITCH_QUEUE_TYPE_TX == p_instance_ctrl->p_queues_status[queue_index].p_queue_cfg->type)
    {
        /* Get a pointer to GWTRCi register. Use GWTRC0 register for queue 0-31, GWTRC1 register for queue 32-63. */
        p_gwca_gwtrc_reg = &(p_instance_ctrl->p_gwca_reg->GWTRC0) + (queue_index / LAYER3_SWITCH_REGISTER_SIZE);

        /* Request to start transmission. */
        *p_gwca_gwtrc_reg = (*p_gwca_gwtrc_reg) | (1 << (queue_index % LAYER3_SWITCH_REGISTER_SIZE));
    }
    else
    {
        /* When RX queue. */
        for (uint32_t i = 0; i < BSP_FEATURE_ETHER_NUM_CHANNELS; i++)
        {
            /* Get register address that depend on port number. */
            if (1 & (p_instance_ctrl->p_queues_status[queue_index].p_queue_cfg->ports >> i))
            {
                p_mfwd_fwpbfcsdc0_reg = (uint32_t *) ((uintptr_t) &(R_MFWD->FWPBFCSDC00) +
                                                      (LAYER3_SWITCH_FWPBFCSDC0_REGISTER_OFFSET * i));

                /* Configure reception frame forwarding to the queue. */
                *p_mfwd_fwpbfcsdc0_reg = R_MFWD_FWPBFCSDC00_PBCSD_Msk & queue_index;
            }
        }
    }

    /* Reset descriptor index of this queue. */
    p_instance_ctrl->p_queues_status[queue_index].head = 0;
    p_instance_ctrl->p_queues_status[queue_index].tail = 0;

    return err;
}                                      /* End of function R_LAYER3_SWITCH_StartDescriptorQueue() */

/*******************************************************************************************************************//**
 * Updates the user callback with the option to provide memory for the callback argument structure.
 *
 * @retval  FSP_SUCCESS                  Callback updated successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_NO_CALLBACK_MEMORY   p_callback is non-secure and p_callback_memory is either secure or NULL.
 **********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_CallbackSet (ether_switch_ctrl_t * const          p_ctrl,
                                       void (                             * p_callback)(ether_switch_callback_args_t *),
                                       void * const                         p_context,
                                       ether_switch_callback_args_t * const p_callback_memory)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ASSERT(p_callback);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

#if BSP_TZ_SECURE_BUILD && BSP_FEATURE_ETHER_SUPPORTS_TZ_SECURE

    /* Get security state of p_callback. */
    bool callback_is_secure =
        (NULL == cmse_check_address_range((void *) p_callback, sizeof(void *), CMSE_AU_NONSECURE));

 #if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE

    /* In secure projects, p_callback_memory must be provided in non-secure space if p_callback is non-secure. */
    ether_switch_callback_args_t * const p_callback_memory_checked = cmse_check_pointed_object(p_callback_memory,
                                                                                               CMSE_AU_NONSECURE);
    FSP_ERROR_RETURN(callback_is_secure || (NULL != p_callback_memory_checked), FSP_ERR_NO_CALLBACK_MEMORY);
 #endif
#endif

    /* Store callback and context. */
#if BSP_TZ_SECURE_BUILD && BSP_FEATURE_ETHER_SUPPORTS_TZ_SECURE
    p_instance_ctrl->p_callback = callback_is_secure ? p_callback :
                                  (void (*)(ether_switch_callback_args_t *))cmse_nsfptr_create(p_callback);
#else
    p_instance_ctrl->p_callback = p_callback;
#endif
    p_instance_ctrl->p_context         = p_context;
    p_instance_ctrl->p_callback_memory = p_callback_memory;

    return FSP_SUCCESS;
}                                      /* End of function R_LAYER3_SWITCH_CallbackSet() */

/*******************************************************************************************************************//**
 * Configure Ethernet port features, including callback function for each port.
 *
 * @retval  FSP_SUCCESS                  Port configured successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER      Pointer to a argument is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT     Port number is invalid.
 **********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_ConfigurePort (ether_switch_ctrl_t * const p_ctrl,
                                         uint8_t                     port,
                                         layer3_switch_port_cfg_t  * p_port_cfg)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(port < BSP_FEATURE_ETHER_NUM_CHANNELS, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(p_port_cfg, FSP_ERR_INVALID_POINTER);
#endif

    /* Set ETHA to CONFIG mode. */
    r_layer3_switch_update_etha_operation_mode(port, LAYER3_SWITCH_AGENT_MODE_DISABLE);
    r_layer3_switch_update_etha_operation_mode(port, LAYER3_SWITCH_AGENT_MODE_CONFIG);

    r_layer3_switch_configure_port(p_instance_ctrl, port, p_port_cfg);

    /* Set ETHA to OPERATION mode. */
    r_layer3_switch_update_etha_operation_mode(port, LAYER3_SWITCH_AGENT_MODE_DISABLE);
    r_layer3_switch_update_etha_operation_mode(port, LAYER3_SWITCH_AGENT_MODE_OPERATION);

    return FSP_SUCCESS;
}                                      /* End of function R_LAYER3_SWITCH_ConfigurePort() */

/*******************************************************************************************************************//**
 * Add or update an entry of the forwarding table.
 *
 * @retval  FSP_SUCCESS                  Successfully add/updated an entry into the table.
 * @retval  FSP_ERR_ASSERTION            Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER      Pointer to a argument is NULL.
 * @retval  FSP_ERR_OVERFLOW             The number of unsecure entries exceeded the configured value.
 * @retval  FSP_ERR_WRITE_FAILED         A hardware error occurred while learning the entry.
 * @retval  FSP_ERR_INVALID_ARGUMENT     Target frame or entry type is invalid.
 * @retval  FSP_ERR_INVALID_MODE         VLAN feature is disabled and a VLAN entry is passed.
 **********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_AddTableEntry (ether_switch_ctrl_t * const                   p_ctrl,
                                         layer3_switch_frame_filter_t const * const    p_target_frame,
                                         layer3_switch_table_entry_cfg_t const * const p_entry_cfg)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_target_frame, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(p_entry_cfg, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(LAYER3_SWITCH_TABLE_STATUS_INITIALIZED == p_instance_ctrl->table_status, FSP_ERR_NOT_INITIALIZED);
    FSP_ERROR_RETURN(LAYER3_SWITCH_TABLE_ENTRY_TYPE_EMPTY != p_target_frame->entry_type, FSP_ERR_INVALID_ARGUMENT);
#endif

    switch (p_target_frame->entry_type)
    {
        case LAYER3_SWITCH_TABLE_ENTRY_TYPE_MAC:
        {
            err = r_layer3_switch_learn_mac_entry(p_target_frame, p_entry_cfg);
            break;
        }

        case LAYER3_SWITCH_TABLE_ENTRY_TYPE_VLAN:
        {
            err = r_layer3_switch_learn_vlan_entry(p_target_frame, p_entry_cfg);
            break;
        }

        case LAYER3_SWITCH_TABLE_ENTRY_TYPE_LAYER3:
        {
            err = r_layer3_switch_learn_l3_entry(p_instance_ctrl, p_target_frame, p_entry_cfg);
            break;
        }

        default:
        {
            break;
        }
    }

    return err;
}                                      /* End of function R_LAYER3_SWITCH_AddTableEntry() */

/*******************************************************************************************************************//**
 * Search an entry from the forwarding table.
 *
 * @retval  FSP_SUCCESS                  The entry is found successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER      Pointer to a argument is NULL.
 * @retval  FSP_ERR_NOT_FOUND            The entry is not found in the table.
 * @retval  FSP_ERR_INVALID_ARGUMENT     Target frame or entry type is invalid.
 * @retval  FSP_ERR_INVALID_MODE         VLAN feature is disabled and a VLAN entry is passed.
 **********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_SearchTableEntry (ether_switch_ctrl_t * const                p_ctrl,
                                            layer3_switch_frame_filter_t const * const p_target_frame,
                                            layer3_switch_table_entry_cfg_t * const    p_entry_cfg)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_target_frame, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(p_entry_cfg, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(LAYER3_SWITCH_TABLE_STATUS_INITIALIZED == p_instance_ctrl->table_status, FSP_ERR_NOT_INITIALIZED);
    FSP_ERROR_RETURN(LAYER3_SWITCH_TABLE_ENTRY_TYPE_EMPTY != p_target_frame->entry_type, FSP_ERR_INVALID_ARGUMENT);
#else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
#endif

    switch (p_target_frame->entry_type)
    {
        case LAYER3_SWITCH_TABLE_ENTRY_TYPE_MAC:
        {
            err = r_layer3_switch_search_mac_entry(p_target_frame, p_entry_cfg);
            break;
        }

        case LAYER3_SWITCH_TABLE_ENTRY_TYPE_VLAN:
        {
            err = r_layer3_switch_search_vlan_entry(p_target_frame, p_entry_cfg);
            break;
        }

        case LAYER3_SWITCH_TABLE_ENTRY_TYPE_LAYER3:
        {
            err = r_layer3_switch_search_l3_entry(p_target_frame, p_entry_cfg);
            break;
        }

        default:
        {
            break;
        }
    }

    return err;
}                                      /* End of function R_LAYER3_SWITCH_SearchTableEntry() */

/*******************************************************************************************************************//**
 * Configure and initialize an forwarding table.
 *
 * @retval  FSP_SUCCESS                  Table configured successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER      Pointer to a argument is NULL.
 * @retval  FSP_ERR_WRITE_FAILED         Failed to add entries.
 **********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_ConfigureTable (ether_switch_ctrl_t * const             p_ctrl,
                                          layer3_switch_table_cfg_t const * const p_table_cfg)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    fsp_err_t err = FSP_SUCCESS;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_table_cfg, FSP_ERR_INVALID_POINTER);
#endif

    /* Set VLAN mode. */
    R_MFWD->FWGC_b.SVM = p_table_cfg->vlan_mode;

    /* Reset table. */
    r_layer3_switch_reset_table(p_instance_ctrl);
    p_instance_ctrl->table_status = LAYER3_SWITCH_TABLE_STATUS_INITIALIZED;

    /* Set maximum number of unsecure entries. */
    R_MFWD->FWMACHEC = (uint32_t) (R_MFWD_FWMACHEC_MACHMC_Msk & (7) << R_MFWD_FWMACHEC_MACHMC_Pos) |
                       (uint32_t) (R_MFWD_FWMACHEC_MACHMUE_Msk &
                                   (p_table_cfg->unsecure_entry_maximum_num) <<
                                   R_MFWD_FWMACHEC_MACHMUE_Pos);
    R_MFWD->FWVLANTEC = (p_table_cfg->unsecure_entry_maximum_num << R_MFWD_FWVLANTEC_VLANTMUE_Pos) &
                        (R_MFWD_FWVLANTEC_VLANTMUE_Msk);
    R_MFWD->FWLTHHEC = (p_table_cfg->unsecure_entry_maximum_num << R_MFWD_FWLTHHEC_LTHHMUE_Pos) &
                       (R_MFWD_FWLTHHEC_LTHHMUE_Msk);

    /* Initialize FRER parameters. */
    err = r_layer3_switch_frer_init(p_instance_ctrl, &p_table_cfg->frer_cfg);
    FSP_ASSERT(FSP_SUCCESS == err);

    /* Configure each port. */
    for (uint8_t i = 0; i < BSP_FEATURE_ETHER_NUM_CHANNELS + 1; i++)
    {
        r_layer3_switch_configure_forwarding_port(&p_table_cfg->port_cfg_list[i], i);

        /* Configure VLAN ingress/egress mode. */
        r_layer3_switch_initialize_vlan_port(p_instance_ctrl, &p_table_cfg->port_cfg_list[i], i);
    }

    /* Configure MAC table aging. */
    if (p_table_cfg->mac_entry_aging_enable)
    {
        r_layer3_switch_enable_mac_table_aging((uint16_t) p_table_cfg->mac_entry_aging_time_sec);
    }

    /* Configure Layer3 table stream filter. */
    r_layer3_switch_configure_stream_filter(&p_table_cfg->l3_stream_filter_cfg);

    /* When an table is passed, learn all entries. */
    if (NULL != p_table_cfg->p_table)
    {
        /* Learn MAC entries. */
        for (uint32_t i = 0; (i < p_table_cfg->p_table->mac_list_length) & (FSP_SUCCESS == err); i++)
        {
            err = R_LAYER3_SWITCH_AddTableEntry(p_instance_ctrl,
                                                &p_table_cfg->p_table->p_mac_entry_list[i].target_frame,
                                                &p_table_cfg->p_table->p_mac_entry_list[i].entry_cfg);
        }

        /* Learn VLAN entries. */
        for (uint32_t i = 0; (i < p_table_cfg->p_table->vlan_list_length) & (FSP_SUCCESS == err); i++)
        {
            err = R_LAYER3_SWITCH_AddTableEntry(p_instance_ctrl,
                                                &p_table_cfg->p_table->p_vlan_entry_list[i].target_frame,
                                                &p_table_cfg->p_table->p_vlan_entry_list[i].entry_cfg);
        }

        /* Learn Layer3 entries. */
        for (uint32_t i = 0; (i < p_table_cfg->p_table->l3_list_length) & (FSP_SUCCESS == err); i++)
        {
            err = R_LAYER3_SWITCH_AddTableEntry(p_instance_ctrl,
                                                &p_table_cfg->p_table->p_vlan_entry_list[i].target_frame,
                                                &p_table_cfg->p_table->p_l3_entry_list[i].entry_cfg);
        }
    }

    if (FSP_SUCCESS != err)
    {
        /* When an error occurs, remove entries and return the error. */
        r_layer3_switch_reset_table(p_instance_ctrl);
        err = FSP_ERR_WRITE_FAILED;
    }

    return err;
}                                      /* End of function R_LAYER3_SWITCH_ConfigureTable() */

/*******************************************************************************************************************//**
 * Get a pointer to the forwarding table.
 *
 * @retval  FSP_SUCCESS                  Table got successfully.
 * @retval  FSP_ERR_ASSERTION            Pointer to control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER      Pointer to a argument is NULL.
 * @retval  FSP_ERR_INVALID_MODE         VLAN feature is disabled and a VLAN entry list is passed.
 **********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_GetTable (ether_switch_ctrl_t * const p_ctrl, layer3_switch_table_t * const p_table)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    layer3_switch_extended_cfg_t  * p_extend;
    fsp_err_t err = FSP_SUCCESS;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(p_table, FSP_ERR_INVALID_POINTER);
    FSP_ERROR_RETURN(LAYER3_SWITCH_TABLE_STATUS_INITIALIZED == p_instance_ctrl->table_status, FSP_ERR_NOT_INITIALIZED);
#endif

    /* Initialize lengths. */
    p_table->mac_list_length  = 0;
    p_table->vlan_list_length = 0;
    p_table->l3_list_length   = 0;

    /* Read all MAC entries. */
    if (NULL != p_table->p_mac_entry_list)
    {
        for (uint16_t i = 0;
             (i < LAYER3_SWITCH_MAC_ENTRY_MAX_NUM) && ((FSP_SUCCESS == err) || (FSP_ERR_NOT_FOUND == err));
             i++)
        {
            err = r_layer3_switch_read_mac_entry(i, &p_table->p_mac_entry_list[p_table->mac_list_length]);
            if (FSP_SUCCESS == err)
            {
                p_table->mac_list_length += 1;
            }
        }
    }

    /* Read all VLAN entries. */
    if ((NULL != p_table->p_vlan_entry_list) && ((FSP_SUCCESS == err) || (FSP_ERR_NOT_FOUND == err)))
    {
        for (uint16_t i = 1;
             (i < LAYER3_SWITCH_VLAN_ENTRY_MAX_NUM) && ((FSP_SUCCESS == err) || (FSP_ERR_NOT_FOUND == err));
             i++)
        {
            err = r_layer3_switch_read_vlan_entry(i, &p_table->p_vlan_entry_list[p_table->vlan_list_length]);
            if (FSP_SUCCESS == err)
            {
                p_table->vlan_list_length += 1;
            }
        }
    }

    /* Read all L3 entries. */
    if ((NULL != p_table->p_l3_entry_list) && ((FSP_SUCCESS == err) || (FSP_ERR_NOT_FOUND == err)))
    {
        p_extend = (layer3_switch_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
        for (uint16_t i = 0;
             (i < p_extend->l3_filter_list_length) && ((FSP_SUCCESS == err) || (FSP_ERR_NOT_FOUND == err));
             i++)
        {
            err =
                r_layer3_switch_search_l3_entry(&p_extend->l3_filter_list[i].frame,
                                                &p_table->p_l3_entry_list[p_table->l3_list_length].entry_cfg);
            if (FSP_SUCCESS == err)
            {
                p_table->p_l3_entry_list[p_table->l3_list_length].target_frame = p_extend->l3_filter_list[i].frame;
                p_table->l3_list_length += 1;
            }
        }
    }

    if (FSP_ERR_NOT_FOUND == err)
    {
        /* When entries are not found, it is acceptable. */
        err = FSP_SUCCESS;
    }

    return err;
}                                      /* End of function R_LAYER3_SWITCH_GetTable() */

/*******************************************************************************************************************//**
 * Configure Time Aware Shaper feature.
 *
 * @retval  FSP_SUCCESS                  TAS configure successfully.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INVALID_POINTER      Pointer to a argument is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT     Port number is invalid.
 * @retval  FSP_ERR_UNSUPPORTED          TAS feature is not enabled in the configuration.
 **********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_ConfigureTAS (ether_switch_ctrl_t * const p_ctrl,
                                        uint8_t                     port,
                                        layer3_switch_tas_cfg_t   * p_tas_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

#if LAYER3_SWITCH_CFG_TAS_ENABLE
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    uint8_t             tas_entry_addr;
    uint8_t             learn_count = 0;
    R_ETHA0_Type      * p_etha_reg;
    volatile uint32_t * p_eatasenc_reg;
    uint32_t            initial_gate_state_bitmask = 0;

 #if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(port < BSP_FEATURE_ETHER_NUM_CHANNELS, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(NULL != p_tas_cfg, FSP_ERR_INVALID_POINTER);
 #else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
 #endif

    p_etha_reg = (R_ETHA0_Type *) (R_ETHA0_BASE + (LAYER3_SWITCH_ETHA_REG_SIZE * port));

    /* Enable TAS gate error interrupt. */
    p_etha_reg->EAEIE1 |= (R_ETHA0_EAEIE1_TASGEE0_Msk | R_ETHA0_EAEIE1_TASGEE1_Msk |
                           R_ETHA0_EAEIE1_TASGEE2_Msk | R_ETHA0_EAEIE1_TASGEE3_Msk | R_ETHA0_EAEIE1_TASGEE4_Msk |
                           R_ETHA0_EAEIE1_TASGEE5_Msk | R_ETHA0_EAEIE1_TASGEE6_Msk | R_ETHA0_EAEIE1_TASGEE7_Msk);

    /* Initialize TAS RAM. */
    p_etha_reg->EATASRIRM_b.TASRIOG = 1U;
    FSP_HARDWARE_REGISTER_WAIT(p_etha_reg->EATASRIRM_b.TASRR, 1);

    /* Wait until TAS Configuration becomes available. */
    FSP_HARDWARE_REGISTER_WAIT(p_etha_reg->EATASC_b.TASCI, 0);

    /* Set entry count and the initial state of each gate. */
    tas_entry_addr = p_etha_reg->EATASC_b.TASCA;
    for (uint8_t i = 0; i < BSP_FEATURE_ESWM_ETHA_IPV_QUEUE_NUM; i++)
    {
        p_eatasenc_reg  = &p_etha_reg->EATASENC0 + i;
        *p_eatasenc_reg = ((p_tas_cfg->gate_cfg_list[i].tas_entry_num - 1) & R_ETHA0_EATASCTENC_TASCTAEN_Msk);

        initial_gate_state_bitmask |= (uint8_t) (p_tas_cfg->gate_cfg_list[i].initial_gate_state << i);
    }

    p_etha_reg->EATASIGSC = initial_gate_state_bitmask & LAYER3_SWITCH_EATASIGSC_MASK;

    /* Set cycle start time and span. */
    p_etha_reg->EATASCSTC0_b.TASACSTP0 = (p_tas_cfg->cycle_time_start_low);
    p_etha_reg->EATASCSTC1_b.TASACSTP1 = (p_tas_cfg->cycle_time_start_high);
    p_etha_reg->EATASCTC_b.TASACT      = (p_tas_cfg->cycle_time);

    /* Learning TAS gate entries. */
    for (uint8_t i = 0; i < BSP_FEATURE_ESWM_ETHA_IPV_QUEUE_NUM; i++)
    {
        for (uint8_t learn_port_cnt = 0;
             learn_port_cnt < p_tas_cfg->gate_cfg_list[i].tas_entry_num;
             learn_port_cnt++)
        {
            layer3_switch_tas_entry_t * p_learn_entry =
                (p_tas_cfg->gate_cfg_list[i].p_tas_entry_list + learn_port_cnt);

            p_etha_reg->EATASGL0_b.TASGAL = (tas_entry_addr + learn_count);
            p_etha_reg->EATASGL1          =
                ((p_learn_entry->time << R_ETHA0_EATASGL1_TASGTL_Pos) & R_ETHA0_EATASGL1_TASGTL_Msk) |
                ((uint32_t) (p_learn_entry->state << R_ETHA0_EATASGL1_TASGSL_Pos) &
                 R_ETHA0_EATASGL1_TASGSL_Msk);
            FSP_HARDWARE_REGISTER_WAIT(p_etha_reg->EATASGLR_b.GL, 0);

            learn_count++;
        }
    }

    /* Set gPTP timer number. */
    p_etha_reg->EATASC_b.TASTS = (uint32_t) (p_tas_cfg->gptp_timer_number & 0x01);

    /* When the TAS operation is already enabled, apply the configuration. */
    if (p_etha_reg->EATASC_b.TASE == 1)
    {
        p_etha_reg->EATASC |= R_ETHA0_EATASC_TASE_Msk | R_ETHA0_EATASC_TASCC_Msk;
    }

#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(port);
    FSP_PARAMETER_NOT_USED(p_tas_cfg);
    err = FSP_ERR_UNSUPPORTED;
#endif

    return err;
}                                      /* End of function R_LAYER3_SWITCH_ConfigureTAS() */

/*******************************************************************************************************************//**
 * Enable Time Aware Shaper feature.
 *
 * @retval  FSP_SUCCESS                  TAS enabled successfully.
 * @retval  FSP_ERR_NOT_OPEN             The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT     Port number is invalid.
 * @retval  FSP_ERR_UNSUPPORTED          TAS feature is not enabled in the configuration.
 **********************************************************************************************************************/
fsp_err_t R_LAYER3_SWITCH_EnableTAS (ether_switch_ctrl_t * const p_ctrl, uint8_t port)
{
    fsp_err_t err = FSP_SUCCESS;
#if LAYER3_SWITCH_CFG_TAS_ENABLE
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
 #if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ASSERT(p_instance_ctrl);
    FSP_ERROR_RETURN(LAYER3_SWITCH_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    FSP_ERROR_RETURN(port < BSP_FEATURE_ETHER_NUM_CHANNELS, FSP_ERR_INVALID_ARGUMENT);
    FSP_ERROR_RETURN(LAYER3_SWITCH_CFG_TAS_ENABLE, FSP_ERR_UNSUPPORTED);
 #else
    FSP_PARAMETER_NOT_USED(p_instance_ctrl);
 #endif
    R_ETHA0_Type * p_etha_reg = (R_ETHA0_Type *) (R_ETHA0_BASE + (LAYER3_SWITCH_ETHA_REG_SIZE * port));

    /* Enable TAS feature if it is disabled. */
    p_etha_reg->EATASC |= R_ETHA0_EATASC_TASE_Msk;
#else
    FSP_PARAMETER_NOT_USED(p_ctrl);
    FSP_PARAMETER_NOT_USED(port);
    err = FSP_ERR_UNSUPPORTED;
#endif

    return err;
}                                      /* End of function R_LAYER3_SWITCH_EnableTAS() */

/*******************************************************************************************************************//**
 * @} (end addtogroup LAYER3_SWITCH)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Clear module stop and turn on the domain power of the ESWM IP.
 ***********************************************************************************************************************/
static void r_layer3_switch_module_start (void)
{
    /* Disable protect of the power domain control. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);

    /* Turn on the domain power. */
    if ((0 == R_SYSTEM->PDCTRESWM_b.PDCSF) && (1 == R_SYSTEM->PDCTRESWM_b.PDPGSF))
    {
        R_SYSTEM->PDCTRESWM_b.PDDE = 0;
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->PDCTRESWM_b.PDCSF, 0);
        FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->PDCTRESWM_b.PDPGSF, 0);
    }

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);

    /* Clear Ether-PHY clock Module Stop. */
    R_MSTP->MSTPCRC_b.MSTPC28 = 0;

    /* Clear Layer 3 Ethernet Switch Module Module Stop. */
    R_MSTP->MSTPCRC_b.MSTPC30 = 0;

    /* Waiting for module start. */
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
}                                      /* End of function r_layer3_switch_module_start() */

/***********************************************************************************************************************
 * Reset COMA IP.
 ***********************************************************************************************************************/
static void r_layer3_switch_reset_coma (void)
{
    /* Reset ESWM IP. */
    R_COMA->RRC_b.RR = 1;
    R_COMA->RRC_b.RR = 0;
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    /* Enable switch clock. */
    R_COMA->RCEC_b.RCE = 1;
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    /* Reset COMA buffer pool. */
    R_COMA->CABPIRM_b.BPIOG = 1;
    FSP_HARDWARE_REGISTER_WAIT(R_COMA->CABPIRM_b.BPR, 1);

    /* Waiting for COMA reset. */
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);

    /* Enable all agent clock. */
    R_COMA->RCEC = R_COMA_RCEC_RCE_Msk | R_COMA_RCEC_ACE_Msk;
}                                      /* End of function r_layer3_switch_reset_coma() */

/***********************************************************************************************************************
 * Close ETHA ports with PHY instance.
 *
 * @param[in] p_instance_ctrl Pointer to a instance ctrl
 ***********************************************************************************************************************/
static void r_layer3_switch_close_etha_ports (layer3_switch_instance_ctrl_t * p_instance_ctrl)
{
    layer3_switch_extended_cfg_t * p_extend = (layer3_switch_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    ether_phy_instance_t const   * p_ether_phy;

    /* Disable ETHA ports. */
    for (uint8_t i = 0; i < BSP_FEATURE_ETHER_NUM_CHANNELS; i++)
    {
        p_ether_phy = p_extend->p_ether_phy_instances[i];
        if (NULL != p_ether_phy)
        {
            /* Set ETHA to DISABLE mode. */
            r_layer3_switch_update_etha_operation_mode(i, LAYER3_SWITCH_AGENT_MODE_DISABLE);

            /* Close a ETHER_PHY instance. */
            p_ether_phy->p_api->close(p_ether_phy->p_ctrl);
        }
    }
}                                      /* End of function r_layer3_switch_close_etha_ports() */

/***********************************************************************************************************************
 * Initialize LINKFIX table as queue disabled.
 *
 * @param[in] p_instance_ctrl Pointer to a instance control
 ***********************************************************************************************************************/
static void r_layer3_switch_initialize_linkfix_table (layer3_switch_instance_ctrl_t * p_instance_ctrl)
{
    layer3_switch_basic_descriptor_t * p_linkfix_descriptor;

    /* Initialize descriptor queue index. */
    p_instance_ctrl->allocated_descriptor_queue_index = 0;

    /* Initialize all LINKFIX descriptors in the LINKFIX table. */
    for (uint32_t i = 0; i < LAYER3_SWITCH_CFG_AVAILABLE_QUEUE_NUM; i++)
    {
        p_linkfix_descriptor = &p_instance_ctrl->p_descriptor_queue_list[i];

        /* Initialize descriptor by 0. */
        memset(p_linkfix_descriptor, 0, sizeof(layer3_switch_basic_descriptor_t));

        /* Set descriptor type as LEMPTY that mean disable queue. */
        p_linkfix_descriptor->dt = LAYER3_SWITCH_DESCRIPTOR_TYPE_LEMPTY;
    }

    /* Set link fix table address. */
    p_instance_ctrl->p_gwca_reg->GWDCBAC0 =
        (LAYER3_SWITCH_QUEUE_ADDRESS_UPPER_MASK & (uint64_t) (uintptr_t) p_instance_ctrl->p_descriptor_queue_list) >>
        LAYER3_SWITCH_QUEUE_ADDRESS_UPPER_POSITION;
    p_instance_ctrl->p_gwca_reg->GWDCBAC1 = R_GWCA0_GWDCBAC1_DCBADP_Msk &
                                            (uintptr_t) p_instance_ctrl->p_descriptor_queue_list;
}                                      /* End of function r_layer3_switch_initialize_linkfix_table() */

/***********************************************************************************************************************
 * Return a descriptor at descriptor_index in the queue.
 *
 *  @param[in] p_instance_ctrl Pointer to a instance control
 *  @param[in] queue_index Index of the queue
 *  @param[in] descriptor_index Index of the descriptor
 ***********************************************************************************************************************/
static layer3_switch_descriptor_t * r_layer3_switch_get_descriptor (layer3_switch_instance_ctrl_t * p_instance_ctrl,
                                                                    uint32_t                        queue_index,
                                                                    uint32_t                        descriptor_index)
{
    layer3_switch_basic_descriptor_t * p_linkfix_descriptor;
    layer3_switch_descriptor_t       * p_queue_head_descriptor;

    p_linkfix_descriptor    = &p_instance_ctrl->p_descriptor_queue_list[queue_index];
    p_queue_head_descriptor = (layer3_switch_descriptor_t *) p_linkfix_descriptor->ptr_l;

    return &p_queue_head_descriptor[descriptor_index];
}                                      /* End of function r_layer3_switch_get_descriptor() */

/***********************************************************************************************************************
 * Return a descriptor that now processed by hardware in the queue.
 *
 * @param[in] p_instance_ctrl Pointer to a instance control
 * @param[in] queue_index Index of the queue
 ***********************************************************************************************************************/
static layer3_switch_descriptor_t * r_layer3_switch_get_current_descriptor (
    layer3_switch_instance_ctrl_t * p_instance_ctrl,
    uint32_t                        queue_index)
{
    /* Set dummy value to clear AXI searching address. */
    p_instance_ctrl->p_gwca_reg->GWAARSS_b.AARA = R_GWCA0_GWAARSS_AARA_Msk & (queue_index + 1);
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_gwca_reg->GWAARSR0_b.AARS, 0);

    /* Get descriptor address that hardware use now. */
    p_instance_ctrl->p_gwca_reg->GWAARSS_b.AARA = R_GWCA0_GWAARSS_AARA_Msk & queue_index;
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_gwca_reg->GWAARSR0_b.AARS, 0);

    return (layer3_switch_descriptor_t *) p_instance_ctrl->p_gwca_reg->GWAARSR1;
}                                      /* End of function r_layer3_switch_get_current_descriptor() */

/***********************************************************************************************************************
 * Check if the descriptor queue is active. If active, return true.
 *
 * @param[in] p_instance_ctrl Pointer to a instance control
 * @param[in] queue_index Index of the queue
 ***********************************************************************************************************************/
static bool r_layer3_switch_is_descriptor_queue_active (layer3_switch_instance_ctrl_t * p_instance_ctrl,
                                                        uint32_t                        queue_index)
{
    volatile layer3_switch_descriptor_t * p_current_descriptor;
    bool active = false;

    /* Check the target descriptor queue type is TX or RX.*/
    if (LAYER3_SWITCH_QUEUE_TYPE_TX == p_instance_ctrl->p_queues_status[queue_index].p_queue_cfg->type)
    {
        /* In TX queue, the GWTRCi register indicates whether the queue is active. Use GWTRC0 for queue 0-31, GWTRC1 for queue 32-63. */
        if (*(&(p_instance_ctrl->p_gwca_reg->GWTRC0) + (queue_index / LAYER3_SWITCH_REGISTER_SIZE)) &
            (1 << (queue_index % LAYER3_SWITCH_REGISTER_SIZE)))
        {
            active = true;
        }
    }
    else                               /* When RX descriptor queue. */
    {
        p_current_descriptor = r_layer3_switch_get_current_descriptor(p_instance_ctrl, queue_index);

        if (NULL == p_current_descriptor)
        {
            /* When the pointer is NULL, this queue is not started. */
            active = false;
        }
        else if (&p_instance_ctrl->p_descriptor_queue_list[queue_index] == (void *) p_current_descriptor)
        {
            active = false;
        }
        else
        {
            /* When the current descriptor is LINKFIX, checking the next descriptor. */
            while (LAYER3_SWITCH_DESCRIPTOR_TYPE_LINKFIX == p_current_descriptor->basic.dt)
            {
                p_current_descriptor = (layer3_switch_descriptor_t *) p_current_descriptor->basic.ptr_l;
            }

            if ((LAYER3_SWITCH_DESCRIPTOR_TYPE_LEMPTY == p_current_descriptor->basic.dt) ||
                (LAYER3_SWITCH_DESCRIPTOR_TYPE_FSINGLE == p_current_descriptor->basic.dt))
            {
                /* When the current descriptor is LEMPTY or FSINGLE, this queue has reached its end. */
                active = false;
            }
            else
            {
                active = true;
            }
        }
    }

    return active;
}                                      /* End of function r_layer3_switch_is_descriptor_queue_active() */

/***********************************************************************************************************************
 * Change operation mode of GWCA.
 *
 * @param[in] p_instance_ctrl Pointer to a instance control
 * @param[in] mode New operation mode
 ***********************************************************************************************************************/
static void r_layer3_switch_update_gwca_operation_mode (layer3_switch_instance_ctrl_t * p_instance_ctrl,
                                                        layer3_switch_agent_mode_t      mode)
{
    if (NULL != p_instance_ctrl)
    {
        /* Mode transition. */
        p_instance_ctrl->p_gwca_reg->GWMC_b.OPC = R_GWCA0_GWMC_OPC_Msk & mode;
        FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_gwca_reg->GWMS_b.OPS, mode);
    }
}                                      /* End of function r_layer3_switch_update_gwca_operation_mode() */

/***********************************************************************************************************************
 * Change operation mode of ETHA.
 *
 * @param[in] mode New operation mode
 ***********************************************************************************************************************/
static void r_layer3_switch_update_etha_operation_mode (uint8_t port, layer3_switch_agent_mode_t mode)
{
    R_ETHA0_Type * p_etha_reg = (R_ETHA0_Type *) (R_ETHA0_BASE + (LAYER3_SWITCH_ETHA_REG_SIZE * port));

    /* Mode transition. */
    p_etha_reg->EAMC_b.OPC = R_ETHA0_EAMC_OPC_Msk & mode;
    FSP_HARDWARE_REGISTER_WAIT(p_etha_reg->EAMS_b.OPS, mode);
}                                      /* End of function r_layer3_switch_update_etha_operation_mode() */

/*******************************************************************************************************************
 * Configure MAC address of a ETHA port.
 *
 * @param[in]     p_mac_address      Pointer to a MAC address
 * @param[in]     port      The target port
 **********************************************************************************************************************/
static void r_layer3_switch_configure_mac_address (uint8_t * p_mac_address, uint8_t port)
{
    R_RMAC0_Type * p_reg_rmac = (R_RMAC0_Type *) (R_RMAC0_BASE + port * LAYER3_SWITCH_RMAC_REG_SIZE);
    uint32_t       mac_h;
    uint32_t       mac_l;

    if (NULL != p_mac_address)
    {
        mac_h =
            ((((uint32_t) p_mac_address[0] << 8)) | (uint32_t) p_mac_address[1]);

        mac_l = (((uint32_t) p_mac_address[2] << 24) | ((uint32_t) p_mac_address[3] << 16) |
                 ((uint32_t) p_mac_address[4] << 8) | (uint32_t) p_mac_address[5]);

        p_reg_rmac->MRMAC0 = mac_h;
        p_reg_rmac->MRMAC1 = mac_l;
    }
}                                      /* End of function r_layer3_switch_configure_mac_address() */

/*******************************************************************************************************************
 * Configure the port specific features.
 **********************************************************************************************************************/
static void r_layer3_switch_configure_port (layer3_switch_instance_ctrl_t * const  p_instance_ctrl,
                                            uint8_t                                port,
                                            layer3_switch_port_cfg_t const * const p_port_cfg)
{
    volatile uint32_t * p_mfwd_fwpbfc_reg;

    /* Copy callback settings to the control member. */
    p_instance_ctrl->p_port_cfg_list[port].p_callback        = p_port_cfg->p_callback;
    p_instance_ctrl->p_port_cfg_list[port].p_context         = p_port_cfg->p_context;
    p_instance_ctrl->p_port_cfg_list[port].p_callback_memory = p_port_cfg->p_callback_memory;

    /* Configure MAC address. */
    r_layer3_switch_configure_mac_address(p_port_cfg->p_mac_address, port);

    p_mfwd_fwpbfc_reg =
        (uint32_t *) ((uintptr_t) &(R_MFWD->FWPBFC0) + (port * LAYER3_SWITCH_FWPBFC_REGISTER_OFFSET));
    if (p_port_cfg->forwarding_to_cpu_enable)
    {
        *p_mfwd_fwpbfc_reg |= (R_MFWD_FWPBFC0_PBDV_Msk & (uint32_t) (LAYER3_SWITCH_PORT_CPU_BITMASK));
    }
    else
    {
        /* Disable forwarding to CPU. But forwarding from the LAN port to the LAN port is still enabled. */
        *p_mfwd_fwpbfc_reg &= (R_MFWD_FWPBFC0_PBDV_Msk & (uint32_t) (~LAYER3_SWITCH_PORT_CPU_BITMASK));
    }

    if (NULL != p_port_cfg->p_cbs_cfg)
    {
        r_layer3_switch_configure_cbs(p_instance_ctrl, port, p_port_cfg->p_cbs_cfg);
    }
}                                      /* End of function r_layer3_switch_configure_port() */

/*******************************************************************************************************************
 * Set forwarding configuration of the target port. This configuration includes enable forwarding and reject unknown frame.
 *
 * @param[in] p_port_cfg Pointer to a port dependent configuration
 * @param[in] port       The target port
 **********************************************************************************************************************/
static void r_layer3_switch_configure_forwarding_port (layer3_switch_forwarding_port_cfg_t const * const p_port_cfg,
                                                       uint8_t                                           port)
{
    uint32_t * p_mfwd_fwpc0_reg =
        (uint32_t *) ((uintptr_t) (&R_MFWD->FWPC00) + (port * LAYER3_SWITCH_PORT_CONFIG_REGISTER_OFFSET));
    uint32_t fwpc0_value = *p_mfwd_fwpc0_reg;

    /* Set VLAN configuration. */
    if (p_port_cfg->vlan_table_enable)
    {
        fwpc0_value |= R_MFWD_FWPC00_VLANSA_Msk;
    }

    if (p_port_cfg->vlan_reject_unknown)
    {
        fwpc0_value |= (R_MFWD_FWPC00_VLANRU_Msk | R_MFWD_FWPC00_VLANRUS_Msk);
    }

    /* Set MAC configuration. */
    if (p_port_cfg->mac_table_enable)
    {
        fwpc0_value |= (R_MFWD_FWPC00_MACDSA_Msk | R_MFWD_FWPC00_MACSSA_Msk);
    }

    if (p_port_cfg->mac_reject_unknown)
    {
        fwpc0_value |=
            (R_MFWD_FWPC00_MACRUDA_Pos | R_MFWD_FWPC00_MACRUDSA_Pos | R_MFWD_FWPC00_MACRUSA_Pos |
             R_MFWD_FWPC00_MACRUSSA_Pos);
    }

    if (p_port_cfg->mac_hardware_learning_enable)
    {
        fwpc0_value |= (R_MFWD_FWPC00_MACHLA_Msk | R_MFWD_FWPC00_MACHMA_Msk);
    }

    /* Set layer3 configuration. */
    if (p_port_cfg->layer3_table_enable)
    {
        fwpc0_value |= R_MFWD_FWPC00_LTHTA_Msk;
    }

    if (p_port_cfg->layer3_ipv4_filter_enable)
    {
        fwpc0_value |= R_MFWD_FWPC00_IP4UE_Msk | R_MFWD_FWPC00_IP4TE_Msk | R_MFWD_FWPC00_IP4OE_Msk;
    }

    if (p_port_cfg->layer3_ipv6_filter_enable)
    {
        fwpc0_value |= R_MFWD_FWPC00_IP6UE_Msk | R_MFWD_FWPC00_IP6TE_Msk | R_MFWD_FWPC00_IP6OE_Msk;
    }

    if (p_port_cfg->layer3_l2_filter_enable)
    {
        fwpc0_value |= R_MFWD_FWPC00_L2SE_Msk;
    }

    if (p_port_cfg->layer3_reject_unknown)
    {
        fwpc0_value |= (R_MFWD_FWPC00_VLANRU_Msk | R_MFWD_FWPC00_VLANRUS_Msk);
    }

    /* Write to port configuration register. */
    *p_mfwd_fwpc0_reg = fwpc0_value;
}                                      /* End of function r_layer3_switch_configure_forwarding_port() */

/*******************************************************************************************************************
 * Reset each forwarding table.
 **********************************************************************************************************************/
static void r_layer3_switch_reset_table (layer3_switch_instance_ctrl_t * p_instance_ctrl)
{
    /* Reset MAC table. */
    R_MFWD->FWMACTIM_b.MACTIOG = 1;
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWMACTIM_b.MACTR, 1);

    /* Reset VLAN table. */
    R_MFWD->FWVLANTIM_b.VLANTIOG = 1;
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWVLANTIM_b.VLANTR, 1);

    /* Reset layer3 table. */
    R_MFWD->FWLTHTIM_b.LTHTIOG = 1;
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWLTHTIM_b.LTHTR, 1);

    /* Reset layer3 Update feature. */
    R_MFWD->FWL23UTIM_b.L23UTIOG = 1;
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWL23UTIM_b.L23UTR, 1);

    /* Initialize entry counts. */
    p_instance_ctrl->l3_entry_count      = 0;
    p_instance_ctrl->l3_routing_number   = 0;
    p_instance_ctrl->l3_remapping_number = 0;
}                                      /* End of function r_layer3_switch_reset_table() */

/*******************************************************************************************************************
 * Learning an entry of MAC table.
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_learn_mac_entry (layer3_switch_frame_filter_t const * const    p_target_frame,
                                                  layer3_switch_table_entry_cfg_t const * const p_entry_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    uint32_t mac_address_high;
    uint32_t mac_address_low;
    uint32_t fwmactl3_value = 0;

    /* Destination or source MAC address should be set. */
    FSP_ERROR_RETURN((NULL != p_target_frame->p_destination_mac_address) ||
                     (NULL != p_target_frame->p_source_mac_address),
                     FSP_ERR_INVALID_ARGUMENT);

    if (NULL != p_target_frame->p_destination_mac_address)
    {
        /* Enable forwarding when destination MAC of a incoming frame is matched. */
        fwmactl3_value  |= R_MFWD_FWMACTL3_MACDSLVL_Msk & (p_entry_cfg->source_ports << R_MFWD_FWMACTL3_MACDSLVL_Pos);
        mac_address_high = r_layer3_switch_convert_array_to_int(&p_target_frame->p_destination_mac_address[0], 2);
        mac_address_low  = r_layer3_switch_convert_array_to_int(&p_target_frame->p_destination_mac_address[2], 4);
    }
    else
    {
        /* Enable forwarding when source MAC address of a incoming frame is matched. */
        fwmactl3_value  |= R_MFWD_FWMACTL3_MACSSLVL_Msk & (p_entry_cfg->source_ports << R_MFWD_FWMACTL3_MACSSLVL_Pos);
        mac_address_high = r_layer3_switch_convert_array_to_int(&p_target_frame->p_source_mac_address[0], 2);
        mac_address_low  = r_layer3_switch_convert_array_to_int(&p_target_frame->p_source_mac_address[2], 4);
    }

    if (p_entry_cfg->entry_enable)
    {
        /* Set security and dynamic entry feature. */
        R_MFWD->FWMACTL0 = (uint32_t) (p_entry_cfg->mac.dinamic_entry << R_MFWD_FWMACTL0_MACDEL_Pos) |
                           (uint32_t) (p_entry_cfg->security_enable << R_MFWD_FWMACTL0_MACSLL_Pos);

        /* Set MAC address. */
        R_MFWD->FWMACTL1 = mac_address_high;
        R_MFWD->FWMACTL2 = mac_address_low;

        /* Set enabled source port. */
        R_MFWD->FWMACTL3 = fwmactl3_value;

        /* Set destination queue index when forward to CPU. */
        R_MFWD->FWMACTL40 = R_MFWD_FWMACTL40_MACCSDL_Msk & p_entry_cfg->destination_queue_index;

        /* Set destination ports and internal priority. */
        R_MFWD->FWMACTL5 = (p_entry_cfg->internal_priority_update_enable << R_MFWD_FWMACTL5_MACIPUL_Pos) |
                           (R_MFWD_FWMACTL5_MACIPVL_Msk & p_entry_cfg->internal_priority_update_value <<
                            R_MFWD_FWMACTL5_MACIPVL_Pos) |
                           (R_MFWD_FWMACTL5_MACDVL_Msk & p_entry_cfg->destination_ports);
    }
    else
    {
        /* If entry is disabled, delete the target entry. */
        /* Set to delete mode. */
        R_MFWD->FWMACTL0 = R_MFWD_FWMACTL0_MACED_Msk;

        /* Set MAC address. */
        R_MFWD->FWMACTL1 = R_MFWD_FWMACTL1_MACMALP0_Msk & mac_address_high;
        R_MFWD->FWMACTL2 = mac_address_low;

        /* Write to FWMACTL5 register. It is need to start deleting process. */
        R_MFWD->FWMACTL5 = 0;
    }

    /* Wait to complete learning. */
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWMACTLR_b.MACTL, 0);

    /* Check learning result. */
    if (0 != (R_MFWD->FWMACTLR & R_MFWD_FWMACTLR_MACLSF_Msk))
    {
        /* Unsecure entry overflow. */
        err = FSP_ERR_OVERFLOW;
    }
    else if (0 != (R_MFWD->FWMACTLR & (R_MFWD_FWMACTLR_MACLF_Msk | R_MFWD_FWMACTLR_MACLEF_Msk)))
    {
        err = FSP_ERR_WRITE_FAILED;
    }
    else
    {
        /* Do nothing. */
    }

    return err;
}                                      /* End of function r_layer3_switch_learn_mac_entry() */

/*******************************************************************************************************************
 * Search an entry of MAC table.
 *
 * @param[in] p_port_cfg Pointer to a target frame
 * @param[in] port       Pointer to an entry
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_search_mac_entry (layer3_switch_frame_filter_t const * const p_target_frame,
                                                   layer3_switch_table_entry_cfg_t * const    p_entry_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  mac_address_high;
    uint32_t  mac_address_low;

    /* Destination or source MAC address should be set. */
    FSP_ERROR_RETURN((NULL != p_target_frame->p_destination_mac_address) ||
                     (NULL != p_target_frame->p_source_mac_address),
                     FSP_ERR_INVALID_POINTER);

    if (NULL != p_target_frame->p_destination_mac_address)
    {
        /* Use destination MAC address to search. */
        mac_address_high = r_layer3_switch_convert_array_to_int(&p_target_frame->p_destination_mac_address[0], 2);
        mac_address_low  = r_layer3_switch_convert_array_to_int(&p_target_frame->p_destination_mac_address[2], 4);
    }
    else
    {
        /* If destination is not passed, use source MAC address to search. */
        mac_address_high = r_layer3_switch_convert_array_to_int(&p_target_frame->p_source_mac_address[0], 2);
        mac_address_low  = r_layer3_switch_convert_array_to_int(&p_target_frame->p_source_mac_address[2], 4);
    }

    /* Set MAC address and start searching. */
    R_MFWD->FWMACTS0 = mac_address_high;
    R_MFWD->FWMACTS1 = mac_address_low;

    /* Wait to complete searching. */
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWMACTSR0_b.MACTS, 0);

    if (0 == R_MFWD->FWMACTSR0_b.MACSNF)
    {
        /* If an entry is found successfully, copy the entry fields. */
        p_entry_cfg->security_enable                 = R_MFWD->FWMACTSR0_b.MACSLS;
        p_entry_cfg->mac.dinamic_entry               = R_MFWD->FWMACTSR0_b.MACDES;
        p_entry_cfg->source_ports                    = R_MFWD->FWMACTSR1_b.MACDSLVS | R_MFWD->FWMACTSR1_b.MACSSLVS;
        p_entry_cfg->destination_queue_index         = R_MFWD->FWMACTSR20_b.MACCSDS;
        p_entry_cfg->destination_ports               = R_MFWD->FWMACTSR3_b.MACDVS;
        p_entry_cfg->internal_priority_update_enable = R_MFWD->FWMACTSR3_b.MACIPUS;
        p_entry_cfg->internal_priority_update_value  = R_MFWD->FWMACTSR3_b.MACIPVS;
    }
    else
    {
        /* Any entry is not found. */
        err = FSP_ERR_NOT_FOUND;
    }

    return err;
}                                      /* End of function r_layer3_switch_search_mac_entry() */

/*******************************************************************************************************************
 * Read an entry of MAC table.
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_read_mac_entry (uint16_t offset, layer3_switch_table_entry_t * p_entry)
{
    fsp_err_t err = FSP_SUCCESS;
    uint8_t * p_mac_address;

    R_MFWD->FWMACTR = LAYER3_SWITCH_MAC_ENTRY_MAX_NUM & offset;
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWMACTRR0_b.MACTR, 0);

    if (R_MFWD->FWMACTRR0_b.MACEVR)
    {
        p_entry->entry_cfg.security_enable   = R_MFWD->FWMACTRR1_b.MACSLR;
        p_entry->entry_cfg.mac.dinamic_entry = R_MFWD->FWMACTRR1_b.MACDER;
        p_entry->entry_cfg.source_ports      = R_MFWD->FWMACTRR4_b.MACDSLVR |
                                               R_MFWD->FWMACTRR4_b.MACSSLVR;
        p_entry->entry_cfg.destination_queue_index         = R_MFWD->FWMACTRR50_b.MACCSDR;
        p_entry->entry_cfg.destination_ports               = R_MFWD->FWMACTRR6_b.MACDVR;
        p_entry->entry_cfg.internal_priority_update_enable = R_MFWD->FWMACTRR6_b.MACIPUR;
        p_entry->entry_cfg.internal_priority_update_value  = R_MFWD->FWMACTRR6_b.MACIPVR;

        if (R_MFWD->FWMACTRR4_b.MACDSLVR)
        {
            /* When destination MAC address matching is enabled. */
            p_mac_address = p_entry->target_frame.p_destination_mac_address;
        }
        else if (R_MFWD->FWMACTRR4_b.MACSSLVR)
        {
            /* When source MAC address matching is enabled. */
            p_mac_address = p_entry->target_frame.p_source_mac_address;
        }
        else
        {
            p_mac_address = NULL;
        }

        if (NULL != p_mac_address)
        {
            p_mac_address[0] = (uint8_t) (R_MFWD->FWMACTRR2_b.MACMARP0 >> 8);
            p_mac_address[1] = (uint8_t) (R_MFWD->FWMACTRR2_b.MACMARP0);
            p_mac_address[2] = (uint8_t) (R_MFWD->FWMACTRR3_b.MACMARP1 >> 24);
            p_mac_address[3] = (uint8_t) (R_MFWD->FWMACTRR3_b.MACMARP1 >> 16);
            p_mac_address[4] = (uint8_t) (R_MFWD->FWMACTRR3_b.MACMARP1 >> 8);
            p_mac_address[5] = (uint8_t) (R_MFWD->FWMACTRR3_b.MACMARP1);
        }
        else
        {
            /* An array for MAC address should be given by the argument. */
            err = FSP_ERR_INVALID_ARGUMENT;
        }
    }
    else
    {
        err = FSP_ERR_NOT_FOUND;
    }

    return err;
}                                      /* End of function r_layer3_switch_read_mac_entry() */

/*******************************************************************************************************************
 * Learning an entry of VLAN table.
 *
 * @param[in] p_entry Pointer to an entry
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_learn_vlan_entry (layer3_switch_frame_filter_t const * const    p_target_frame,
                                                   layer3_switch_table_entry_cfg_t const * const p_entry_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    uint16_t  vlan_id;

    /* Extract VLAN ID. */
    err = r_layer3_switch_extract_vlan_id(p_target_frame, &vlan_id);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    if (p_entry_cfg->entry_enable)
    {
        /*  Set entry is secure or not. */
        R_MFWD->FWVLANTL0 = (uint32_t) (p_entry_cfg->security_enable << R_MFWD_FWVLANTL0_VLANSLL_Pos);

        /*  Set VLAN ID. */
        R_MFWD->FWVLANTL1 = vlan_id;

        /* Set forwarding ports. */
        R_MFWD->FWVLANTL2  = p_entry_cfg->source_ports;
        R_MFWD->FWVLANTL30 = p_entry_cfg->destination_queue_index;
        R_MFWD->FWVLANTL4  = (p_entry_cfg->destination_ports);
    }
    else
    {
        /* Set to delete mode. */
        R_MFWD->FWVLANTL0 = R_MFWD_FWVLANTL0_VLANED_Msk;
        R_MFWD->FWVLANTL1 = vlan_id;

        /* Write to following register to start learning process. */
        R_MFWD->FWVLANTL4 = 0x0;
    }

    /* Wait to complete learning */
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWVLANTLR_b.VLANTL, 0);

    if (0 != (R_MFWD->FWVLANTLR & R_MFWD_FWVLANTLR_VLANLSF_Msk))
    {
        /* Unsecure entry overflow. */
        err = FSP_ERR_OVERFLOW;
    }
    else if (0 != (R_MFWD->FWVLANTLR & (R_MFWD_FWVLANTLR_VLANLF_Msk | R_MFWD_FWVLANTLR_VLANLEF_Msk)))
    {
        err = FSP_ERR_WRITE_FAILED;
    }
    else
    {
        err = FSP_SUCCESS;

        /* Do nothing. */
    }

    return err;
}                                      /* End of function r_layer3_switch_learn_vlan_entry() */

/*******************************************************************************************************************
 * Search an entry of VLAN table.
 *
 * @param[in] p_port_cfg Pointer to a target frame
 * @param[in] port       Pointer to an entry
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_search_vlan_entry (layer3_switch_frame_filter_t const * const p_target_frame,
                                                    layer3_switch_table_entry_cfg_t * const    p_entry_cfg)
{
    uint16_t  vlan_id;
    fsp_err_t err;

    /* Extract VLAN ID from the target frame. */
    err = r_layer3_switch_extract_vlan_id(p_target_frame, &vlan_id);
    FSP_ERROR_RETURN(FSP_SUCCESS == err, err);

    /* Start searching. */
    R_MFWD->FWVLANTS = vlan_id;

    /* Wait to complete searching. */
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWVLANTSR0_b.VLANTS, 0);

    if (0 == R_MFWD->FWVLANTSR0_b.VLANSNF)
    {
        /* An entry with the VLAN ID is found. Copy entry fields. */
        p_entry_cfg->security_enable         = R_MFWD->FWVLANTSR0_b.VLANSLS;
        p_entry_cfg->source_ports            = R_MFWD->FWVLANTSR1_b.VLANSLVS;
        p_entry_cfg->destination_queue_index = R_MFWD->FWVLANTSR20_b.VLANCSDS;
        p_entry_cfg->destination_ports       = R_MFWD->FWVLANTSR3_b.VLANDVS;
    }
    else
    {
        /* Any entry is not found. */
        err = FSP_ERR_NOT_FOUND;
    }

    return err;
}                                      /* End of function r_layer3_switch_search_vlan_entry() */

/*******************************************************************************************************************
 * Read an entry of VLAN table.
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_read_vlan_entry (uint16_t offset, layer3_switch_table_entry_t * p_entry)
{
    fsp_err_t err;
    FSP_ERROR_RETURN(LAYER3_SWITCH_VLAN_MODE_NO_VLAN != R_MFWD->FWGC_b.SVM, FSP_ERR_INVALID_MODE);

    /* Set offset as VLAN ID. */
    p_entry->target_frame.vlan_c_tag.id = LAYER3_SWITCH_VLAN_ENTRY_MAX_NUM & offset;

    /* Search an entry with this VLAN ID. */
    err = r_layer3_switch_search_vlan_entry(&p_entry->target_frame, &p_entry->entry_cfg);

    return err;
}                                      /* End of function r_layer3_switch_read_vlan_entry() */

/*******************************************************************************************************************
 * Learn an entry of layer3 forwarding table.
 *
 * @param[in] p_entry Pointer to an entry
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_learn_l3_entry (layer3_switch_instance_ctrl_t               * p_instance_ctrl,
                                                 layer3_switch_frame_filter_t const * const    p_target_frame,
                                                 layer3_switch_table_entry_cfg_t const * const p_entry_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    layer3_switch_extended_cfg_t * p_extend  = (layer3_switch_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;
    layer3_switch_stream_id_t      stream_id = {0};
    uint32_t frer_number = 0;
    uint32_t routing_number;

    FSP_ERROR_RETURN(p_extend->l3_filter_list_length > p_instance_ctrl->l3_entry_count, FSP_ERR_OVERFLOW);

    /* Calculate new stream ID. */
    r_layer3_switch_calculate_l3_stream_id(p_target_frame, &stream_id);

    /* Set stream ID. */
    R_MFWD->FWLTHTL1 = stream_id.words[0];
    R_MFWD->FWLTHTL2 = stream_id.words[1];
    R_MFWD->FWLTHTL3 = stream_id.words[2];
    R_MFWD->FWLTHTL4 = stream_id.words[3];

    /* Calculate FRER number. */
    if (NULL != p_entry_cfg->p_frer_entry_cfg)
    {
        /* If sequence recovery is passed and has not been learned, two FRER entries will be learned. */
        if ((NULL != p_entry_cfg->p_frer_entry_cfg->p_sequence_recovery) &&
            (false ==
             p_instance_ctrl->frer_sequence_recovery_status[p_entry_cfg->p_frer_entry_cfg->sequence_recovery_id &
                                                            LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK].learned))
        {
            frer_number = (p_instance_ctrl->valid_frer_entry_num + 1) & LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK;
        }
        else
        {
            /* In other case, one FRER entry will be learned. */
            frer_number = p_instance_ctrl->valid_frer_entry_num & LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK;
        }
    }

    if (p_entry_cfg->entry_enable)
    {
        /* Set stream ID and security level. */
        R_MFWD->FWLTHTL0 =
            (uint32_t) ((R_MFWD_FWLTHTL0_LTHSLP0_Msk &
                         (uint32_t) (stream_id.frame_format_code << R_MFWD_FWLTHTL0_LTHSLP0_Pos)) |
                        (uint32_t) (p_entry_cfg->security_enable << R_MFWD_FWLTHTL0_LTHSLL_Pos));

        /* Configure FRER feature. */
        R_MFWD->FWLTHTL6 = ((R_MFWD_FWLTHTL6_LTHFRERVL_Msk &
                             (uint32_t) ((NULL != p_entry_cfg->p_frer_entry_cfg) << R_MFWD_FWLTHTL6_LTHFRERVL_Pos)) |
                            (R_MFWD_FWLTHTL6_LTHFRERNL_Msk &
                             (frer_number << R_MFWD_FWLTHTL6_LTHFRERNL_Pos)));

        /* Configure routing number and source ports. */
        R_MFWD->FWLTHTL7 =
            (uint32_t) ((uint32_t) ((NULL != p_entry_cfg->layer3.p_update_configs) << R_MFWD_FWLTHTL7_LTHRVL_Pos) |
                        (R_MFWD_FWLTHTL7_LTHRNL_Msk &
                         (uint32_t) (p_instance_ctrl->l3_routing_number <<
                                     R_MFWD_FWLTHTL7_LTHRNL_Pos)) |
                        (R_MFWD_FWLTHTL7_LTHSLVL_Msk &
                         (p_entry_cfg->source_ports << R_MFWD_FWLTHTL7_LTHSLVL_Pos)));

        /* Configure queue index that frame forwarding to. */
        R_MFWD->FWLTHTL80 =
            (uint32_t) (R_MFWD_FWLTHTL80_LTHCSDL_Msk &
                        (p_entry_cfg->destination_queue_index << R_MFWD_FWLTHTL80_LTHCSDL_Pos));

        /* Configure destination ports, mirroring and internal priority. After writing this register, hardware start learning. */
        R_MFWD->FWLTHTL9 =
            (p_entry_cfg->destination_ports << R_MFWD_FWLTHTL9_LTHDVL_Pos);
    }
    else
    {
        /* Set to delete mode. */
        R_MFWD->FWLTHTL0 =
            (uint32_t) ((R_MFWD_FWLTHTL0_LTHSLP0_Msk &
                         (uint32_t) (stream_id.frame_format_code << R_MFWD_FWLTHTL0_LTHSLP0_Pos)) |
                        (1 << R_MFWD_FWLTHTL0_LTHED_Pos));

        /* Start removing entry. */
        R_MFWD->FWLTHTL9 = 0;
    }

    /* Wait reset. */
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWLTHTLR_b.LTHTL, 0);

    /* Check learning result. */
    if (0 == (R_MFWD->FWLTHTLR & (R_MFWD_FWLTHTLR_LTHLF_Msk | R_MFWD_FWLTHTLR_LTHLSF_Msk | R_MFWD_FWLTHTLR_LTHLEF_Msk)))
    {
        err = FSP_SUCCESS;
    }
    else
    {
        err = FSP_ERR_WRITE_FAILED;
    }

    if (err == FSP_SUCCESS)
    {
        /*  Configure L3 update feature. */
        if (NULL != p_entry_cfg->layer3.p_update_configs)
        {
            if (0 < p_entry_cfg->layer3.number_of_configs)
            {
                err =
                    r_layer3_switch_learn_l3_update(p_instance_ctrl, &p_entry_cfg->layer3.p_update_configs[0]);
                routing_number = p_instance_ctrl->l3_routing_number - 1;
            }

            /* When two or more config are passed, set it using remapping feature. */
            for (uint32_t i = 1; (i < p_entry_cfg->layer3.number_of_configs) && (FSP_SUCCESS == err); i++)
            {
                err = r_layer3_switch_remapping_l3_update(p_instance_ctrl,
                                                          routing_number,
                                                          &p_entry_cfg->layer3.p_update_configs[i]);
            }
        }

        /* When the FRER individual recovery is passed, learn the FRER entry. */
        if ((FSP_SUCCESS == err) && (NULL != p_entry_cfg->p_frer_entry_cfg))
        {
            err = r_layer3_switch_learn_frer_individual_recovery(p_instance_ctrl, p_entry_cfg->p_frer_entry_cfg);
        }

        if ((FSP_SUCCESS == err) && p_entry_cfg->entry_enable)
        {
            /* Save routing number. */
            if (0 != stream_id.frame_format_code)
            {
                /* This stream ID is generated by stream filter. Save frame with routing number.*/
                p_extend->l3_filter_list[p_instance_ctrl->l3_entry_count].frame = *p_target_frame;
            }

            /* Count the valid Layer 3 entry. */
            p_instance_ctrl->l3_entry_count += 1;
        }
    }

    return err;
}                                      /* End of function r_layer3_switch_learn_l3_entry() */

/*******************************************************************************************************************
 * Search an entry of layer3 forwarding table.
 *
 * @param[in] p_port_cfg Pointer to a target frame
 * @param[in] port       Pointer to an entry
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_search_l3_entry (layer3_switch_frame_filter_t const * const p_target_frame,
                                                  layer3_switch_table_entry_cfg_t * const    p_entry_cfg)
{
    fsp_err_t                 err = FSP_SUCCESS;
    layer3_switch_stream_id_t stream_id;
    uint8_t routing_number;
    bool    l3_update_enable;

    r_layer3_switch_calculate_l3_stream_id(p_target_frame, &stream_id);

    /* Set stream ID of a entry. */
    R_MFWD->FWLTHTS0_b.LTHSSP0 = R_MFWD_FWLTHTS0_LTHSSP0_Msk & stream_id.frame_format_code;
    R_MFWD->FWLTHTS1_b.LTHSSP1 = stream_id.words[0];
    R_MFWD->FWLTHTS2_b.LTHSSP2 = stream_id.words[1];
    R_MFWD->FWLTHTS3_b.LTHSSP3 = stream_id.words[2];
    R_MFWD->FWLTHTS4_b.LTHSSP4 = stream_id.words[3];

    /* Wait completing search. */
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWLTHTSR0_b.LTHTS, 0);

    if (0 == R_MFWD->FWLTHTSR0_b.LTHSNF)
    {
        /* Copy entry values. */
        routing_number                 = R_MFWD->FWLTHTSR3_b.LTHRNS;
        p_entry_cfg->source_ports      = R_MFWD->FWLTHTSR3_b.LTHSLVS;
        p_entry_cfg->destination_ports = R_MFWD->FWLTHTSR5_b.LTHDVS;

        /* Copy enable/disable setting bits. */
        p_entry_cfg->security_enable = R_MFWD->FWLTHTSR0_b.LTHSLS;
        l3_update_enable             = R_MFWD->FWLTHTSR3_b.LTHRVS;
    }
    else
    {
        /* Any entry for the stream ID is not found. */
        err = FSP_ERR_NOT_FOUND;
    }

    if (err == FSP_SUCCESS)
    {
        /* Search and get update config. */
        if (l3_update_enable && (NULL != p_entry_cfg->layer3.p_update_configs))
        {
            err = r_layer3_switch_search_l3_update(routing_number, &p_entry_cfg->layer3.p_update_configs[0]);
        }
    }

    return err;
}                                      /* End of function r_layer3_switch_search_l3_entry() */

/*******************************************************************************************************************
 * Learn an entry of layer3 update table.
 *
 * @param[in] routing_number Index of a target layer3 entry.
 * @param[in] p_config Pointer to an configuration of update entry.
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_learn_l3_update (layer3_switch_instance_ctrl_t          * p_instance_ctrl,
                                                  layer3_switch_l3_update_config_t * const p_config)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Set the target routing number. */
    R_MFWD->FWL23URL0 =
        (R_MFWD_FWL23URL0_L23URNL_Msk &
         ((uint32_t) (p_instance_ctrl->l3_routing_number << R_MFWD_FWL23URL0_L23URNL_Pos))) |
        (R_MFWD_FWL23URL0_L23URPVL_Msk &
         (p_config->enable_destination_ports << R_MFWD_FWL23URL0_L23URPVL_Pos));

    R_MFWD->FWL23URL1 =
        (R_MFWD_FWL23URL1_L23UMDALP0_Msk &
         (r_layer3_switch_convert_array_to_int(&p_config->p_mac_destination_address[0],
                                               2) << R_MFWD_FWL23URL1_L23UMDALP0_Pos)) |
        (p_config->update_field_bitmask << R_MFWD_FWL23URL1_L23UTTLUL_Pos) |
        (R_MFWD_FWL23URL1_L23URTUL_Msk & ((uint32_t) (p_config->r_tag_update_mode << R_MFWD_FWL23URL1_L23URTUL_Pos)));

    R_MFWD->FWL23URL2 =
        (R_MFWD_FWL23URL2_L23UMDALP1_Msk &
         (r_layer3_switch_convert_array_to_int(&p_config->p_mac_destination_address[2],
                                               4) << R_MFWD_FWL23URL2_L23UMDALP1_Pos));

    R_MFWD->FWL23URL3 =
        (R_MFWD_FWL23URL3_L23UCVIDL_Msk & ((uint32_t) (p_config->vlan_c_tag.id << R_MFWD_FWL23URL3_L23UCVIDL_Pos))) |
        (R_MFWD_FWL23URL3_L23UCPCPL_Msk & ((uint32_t) (p_config->vlan_c_tag.pcp << R_MFWD_FWL23URL3_L23UCPCPL_Pos))) |
        (R_MFWD_FWL23URL3_L23UCDEIL_Msk & ((uint32_t) (p_config->vlan_c_tag.dei << R_MFWD_FWL23URL3_L23UCDEIL_Pos))) |
        (R_MFWD_FWL23URL3_L23USVIDL_Msk & ((uint32_t) (p_config->vlan_s_tag.id << R_MFWD_FWL23URL3_L23USVIDL_Pos))) |
        (R_MFWD_FWL23URL3_L23USPCPL_Msk & ((uint32_t) (p_config->vlan_s_tag.pcp << R_MFWD_FWL23URL3_L23USPCPL_Pos))) |
        (R_MFWD_FWL23URL3_L23USDEIL_Msk & ((uint32_t) (p_config->vlan_s_tag.dei << R_MFWD_FWL23URL3_L23USDEIL_Pos)));

    /* Wait reset. */
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWL23URLR_b.L23URL, 0);

    if (0 != R_MFWD->FWL23URLR_b.L23ULF)
    {
        /* Layer3 update learning fail. */
        err = FSP_ERR_WRITE_FAILED;
    }
    else
    {
        if (true == p_config->sequence_number_generation_enable)
        {
            /* Enable sequence_number_generation for this L23U entry. */
            if (LAYER3_SWITCH_SEQ_REG_MAX_NUM >
                (p_instance_ctrl->used_frer_sequence_generator_num & LAYER3_SWITCH_FRER_SEQ_GENERATOR_NUM_BITMASK))
            {
                r_layer3_switch_configure_sequence_number_generation(p_instance_ctrl);

                p_instance_ctrl->used_frer_sequence_generator_num =
                    (p_instance_ctrl->used_frer_sequence_generator_num + 1) &
                    LAYER3_SWITCH_FRER_SEQ_GENERATOR_NUM_BITMASK;
            }
        }

        p_instance_ctrl->l3_routing_number += 1;
    }

    return err;
}                                      /* End of function r_layer3_switch_learn_l3_update() */

/*******************************************************************************************************************
 * Search an entry of layer3 update table.
 *
 * @param[in] routing_number Index of a target layer3 entry.
 * @param[out] p_config Pointer to an configuration of update entry.
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_search_l3_update (uint8_t routing_number, layer3_switch_l3_update_config_t * p_config)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Search for entries that match the routing number. */
    R_MFWD->FWL23URR_b.L23RNR = routing_number;

    /* Wait reset. */
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWL23URRR0_b.L23URR, 0);

    if (0 == R_MFWD->FWL23URRR0_b.L23UREF)
    {
        /* Layer3 update entry searching success. Copy fields.*/
        p_config->enable_destination_ports = R_MFWD->FWL23URRR0_b.L23URPVR;
        p_config->update_field_bitmask     =
            ((R_MFWD_FWL23URRR1_L23UTTLUR_Msk | R_MFWD_FWL23URRR1_L23UMDAUR_Msk | R_MFWD_FWL23URRR1_L23UMSAUR_Msk |
              R_MFWD_FWL23URRR1_L23UCVIDUR_Msk | R_MFWD_FWL23URRR1_L23UCPCPUR_Msk | R_MFWD_FWL23URRR1_L23UCDEIUR_Msk |
              R_MFWD_FWL23URRR1_L23USVIDUR_Msk | R_MFWD_FWL23URRR1_L23USPCPUR_Msk | R_MFWD_FWL23URRR1_L23USDEIUR_Msk) &
             R_MFWD->FWL23URRR1) >> R_MFWD_FWL23URRR1_L23UTTLUR_Pos;
        p_config->r_tag_update_mode = (layer3_switch_forwarding_r_tag_t) R_MFWD->FWL23URRR1_b.L23URTUR;
        p_config->vlan_c_tag.id     = R_MFWD->FWL23URRR3_b.L23UCVIDR;
        p_config->vlan_c_tag.pcp    = R_MFWD->FWL23URRR3_b.L23UCPCPR;
        p_config->vlan_c_tag.dei    = R_MFWD->FWL23URRR3_b.L23UCDEIR;
        p_config->vlan_s_tag.id     = R_MFWD->FWL23URRR3_b.L23USVIDR;
        p_config->vlan_s_tag.pcp    = R_MFWD->FWL23URRR3_b.L23USPCPR;
        p_config->vlan_s_tag.dei    = R_MFWD->FWL23URRR3_b.L23USDEIR;
        if (NULL != p_config->p_mac_destination_address)
        {
            /* Copy MAC address. */
            p_config->p_mac_destination_address[0] = (uint8_t) (R_MFWD->FWL23URRR1_b.L23UMDARP0 >> 8);
            p_config->p_mac_destination_address[1] = (uint8_t) R_MFWD->FWL23URRR1_b.L23UMDARP0;
            p_config->p_mac_destination_address[2] = (uint8_t) (R_MFWD->FWL23URRR2_b.L23UMDARP1 >> 24);
            p_config->p_mac_destination_address[3] = (uint8_t) (R_MFWD->FWL23URRR2_b.L23UMDARP1 >> 16);
            p_config->p_mac_destination_address[4] = (uint8_t) (R_MFWD->FWL23URRR2_b.L23UMDARP1 >> 8);
            p_config->p_mac_destination_address[5] = (uint8_t) R_MFWD->FWL23URRR2_b.L23UMDARP1;
        }
    }
    else
    {
        /* Layer3 update entry is not found. */
        err = FSP_ERR_NOT_FOUND;
    }

    return err;
}                                      /* End of function r_layer3_switch_search_l3_update() */

/*******************************************************************************************************************
 * Enable and configure MAC aging feature.
 *
 * @param[in] aging_time Aging cycle time
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_enable_mac_table_aging (uint32_t aging_time)
{
    /* Configure aging clock prescaler. */
    R_MFWD->FWMACAGUSPC = R_MFWD_FWMACAGUSPC_MACAGUSP_Msk & LAYER3_SWITCH_CLOCK_100MHZ;

    /* Enable aging and set aging time. */
    R_MFWD->FWMACAGC = R_MFWD_FWMACAGC_MACAGE_Msk | (R_MFWD_FWMACAGC_MACAGT_Msk & aging_time);

    return FSP_SUCCESS;
}                                      /* End of function r_layer3_switch_enable_mac_table_aging() */

/*******************************************************************************************************************
 * Extract VLAN ID from a target frame based on hardware VLAN mode.
 *
 * @param[in] p_target_frame Pointer to a target frame
 * @param[out] p_vlan_id Extracted VLAN ID
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_extract_vlan_id (layer3_switch_frame_filter_t const * const p_target_frame,
                                                  uint16_t                                 * p_vlan_id)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Check VLAN mode of this switch. */
    if (R_MFWD->FWGC_b.SVM == LAYER3_SWITCH_VLAN_MODE_NO_VLAN)
    {
        /* When No VLAN mode, can't use VLAN feature. */
        err = FSP_ERR_INVALID_MODE;
    }
    else if ((R_MFWD->FWGC_b.SVM == LAYER3_SWITCH_VLAN_MODE_SC_TAG) && (0 < p_target_frame->vlan_s_tag.id))
    {
        /* When the switch is SC-TAG mode and passed S-TAG is valid, use S-TAG. */
        *p_vlan_id = p_target_frame->vlan_s_tag.id;
    }
    else if (0 < p_target_frame->vlan_c_tag.id)
    {
        /* If passed C-TAG is valid, use C-TAG. */
        *p_vlan_id = p_target_frame->vlan_c_tag.id;
    }
    else
    {
        /* If S-TAG and C-TAG is invalid, return error. */
        err = FSP_ERR_INVALID_ARGUMENT;
    }

    return err;
}                                      /* End of function r_layer3_switch_extract_vlan_id() */

/*******************************************************************************************************************
 * Configure VLAN ingress and egress mode of the target port.
 *
 * @param[in] p_instance_ctrl Pointer to a instance control
 * @param[in] p_port_cfg Pointer to a port dependent configuration
 * @param[in] port       The target port
 **********************************************************************************************************************/
static void r_layer3_switch_initialize_vlan_port (layer3_switch_instance_ctrl_t                   * p_instance_ctrl,
                                                  layer3_switch_forwarding_port_cfg_t const * const p_port_cfg,
                                                  uint8_t                                           port)
{
    R_ETHA0_Type * p_reg_etha;
    uint32_t       vcc_reg_value;
    uint32_t       vtc_reg_value;

    /* Set ingress/egress mode. */
    vcc_reg_value = (uint32_t) ((p_port_cfg->vlan_ingress_mode << R_ETHA0_EAVCC_VIM_Pos) |
                                (p_port_cfg->vlan_egress_mode << R_ETHA0_EAVCC_VEM_Pos));

    /* Set VLAN ID, PCP, DEI of the port. */
    vtc_reg_value = (uint32_t) ((p_port_cfg->vlan_c_tag.id << R_ETHA0_EAVTC_CTV_Pos) |
                                (p_port_cfg->vlan_c_tag.pcp << R_ETHA0_EAVTC_CTP_Pos) |
                                (p_port_cfg->vlan_c_tag.dei << R_ETHA0_EAVTC_CTD_Pos) |
                                (p_port_cfg->vlan_s_tag.id << R_ETHA0_EAVTC_STV_Pos) |
                                (p_port_cfg->vlan_s_tag.pcp << R_ETHA0_EAVTC_STP_Pos) |
                                (p_port_cfg->vlan_s_tag.dei << R_ETHA0_EAVTC_STD_Pos));

    if (port < BSP_FEATURE_ETHER_NUM_CHANNELS)
    {
        /* When port is external(ETHA).  */
        /* Set ETHA to CONFIG mode. */
        r_layer3_switch_update_etha_operation_mode(port, LAYER3_SWITCH_AGENT_MODE_DISABLE);
        r_layer3_switch_update_etha_operation_mode(port, LAYER3_SWITCH_AGENT_MODE_CONFIG);

        /* Write register to configuration value. */
        p_reg_etha        = (R_ETHA0_Type *) (R_ETHA0_BASE + (LAYER3_SWITCH_ETHA_REG_SIZE * port));
        p_reg_etha->EAVCC = vcc_reg_value;
        p_reg_etha->EAVTC = vtc_reg_value;

        /* Set ETHA to OPERATION mode. */
        r_layer3_switch_update_etha_operation_mode(port, LAYER3_SWITCH_AGENT_MODE_DISABLE);
        r_layer3_switch_update_etha_operation_mode(port, LAYER3_SWITCH_AGENT_MODE_OPERATION);
    }
    else
    {
        /* When port is the CPU (GWCA). */
        /* Set GWCA to CONFIG mode. */
        r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_DISABLE);
        r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_CONFIG);

        /* Write register to configuration value. */
        p_instance_ctrl->p_gwca_reg->GWVCC = vcc_reg_value;
        p_instance_ctrl->p_gwca_reg->GWVTC = vtc_reg_value;

        /* Set GWCA to OPERATION mode. */
        r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_DISABLE);
        r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_OPERATION);
    }
}                                      /* End of function r_layer3_switch_initialize_vlan_port() */

/*******************************************************************************************************************
 * Configure IPv4/IPv6/L2 stream filter to which frame fields used to stream ID creation.
 *
 * @param[in] p_filter_cfg Pointer to a stream filter configuration
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_configure_stream_filter (layer3_switch_l3_stream_filter_cfg_t const * p_filter_cfg)
{
    FSP_ERROR_RETURN(NULL != p_filter_cfg, FSP_ERR_INVALID_POINTER);
    uint32_t filter_reg_value = 0;

    /* Configure IPv4 filter. */
    /* Set fields included to hash calculation. */
    filter_reg_value = p_filter_cfg->filter_field_bitmask;

    /* Set fields included to stream ID creation. */
    filter_reg_value |=
        ((R_MFWD_FWIP4SC_IP4ISVS_Msk | R_MFWD_FWIP4SC_IP4ISPS_Msk | R_MFWD_FWIP4SC_IP4ISDS_Msk |
          R_MFWD_FWIP4SC_IP4ICVS_Msk | R_MFWD_FWIP4SC_IP4ICPS_Msk | R_MFWD_FWIP4SC_IP4ICDS_Msk |
          R_MFWD_FWIP4SC_IP4IISS_Msk |
          R_MFWD_FWIP4SC_IP4IIDS_Msk) &
         (uint32_t) (p_filter_cfg->filter_field_bitmask << (R_MFWD_FWIP4SC_IP4ISVS_Pos - 2))) |
        ((uint32_t) ((p_filter_cfg->filter_field_bitmask &
                      LAYER3_SWITCH_L3_FILTER_BITMASK_IP_DESTINATION_PORT) != 0) << R_MFWD_FWIP4SC_IP4IDPTS_Pos);

    R_MFWD->FWIP4SC = filter_reg_value;

    /* Configure IPv6 filter. */
    /* Set fields included to hash calculation. */
    filter_reg_value = p_filter_cfg->filter_field_bitmask;

    /* Set fields included to stream ID creation. */
    filter_reg_value |=
        ((R_MFWD_FWIP6SC_IP6ISVS_Msk | R_MFWD_FWIP6SC_IP6ISPS_Msk | R_MFWD_FWIP6SC_IP6ISDS_Msk |
          R_MFWD_FWIP6SC_IP6ICVS_Msk | R_MFWD_FWIP6SC_IP6ICPS_Msk | R_MFWD_FWIP6SC_IP6ICDS_Msk |
          R_MFWD_FWIP6SC_IP6II0S_Msk |
          R_MFWD_FWIP6SC_IP6II1S_Msk) &
         (uint32_t) (p_filter_cfg->filter_field_bitmask << (R_MFWD_FWIP6SC_IP6ISVS_Pos - 2))) |
        ((uint32_t) ((p_filter_cfg->filter_field_bitmask &
                      LAYER3_SWITCH_L3_FILTER_BITMASK_IP_DESTINATION_PORT) != 0) << R_MFWD_FWIP6SC_IP6IDPTS_Pos);

    R_MFWD->FWIP6SC = filter_reg_value;

    /* Configure L2 filter. */
    /* Set fields included to stream ID creation. */
    filter_reg_value =
        ((R_MFWD_FWL2SC_L2ISVS_Msk | R_MFWD_FWL2SC_L2ISPS_Msk | R_MFWD_FWL2SC_L2ISDS_Msk | R_MFWD_FWL2SC_L2ICVS_Msk |
          R_MFWD_FWL2SC_L2ICPS_Msk | R_MFWD_FWL2SC_L2ICDS_Msk | R_MFWD_FWL2SC_L2IMDS_Msk | R_MFWD_FWL2SC_L2IMSS_Msk) &
         p_filter_cfg->filter_field_bitmask);
    R_MFWD->FWL2SC = filter_reg_value;

    /* Set IPv6 address offset. */
    R_MFWD->FWIP6OC =
        (uint32_t) ((R_MFWD_FWIP6OC_IP6IPO1_Msk &
                     (uint32_t) (p_filter_cfg->ipv6_address1.offset << R_MFWD_FWIP6OC_IP6IPO1_Pos)) |
                    (R_MFWD_FWIP6OC_IP6IPOM1_Msk &
                     (uint32_t) (p_filter_cfg->ipv6_address1.direction << R_MFWD_FWIP6OC_IP6IPOM1_Pos)) |
                    (R_MFWD_FWIP6OC_IP6IPO_Msk &
                     (uint32_t) (p_filter_cfg->ipv6_address0.offset << R_MFWD_FWIP6OC_IP6IPO_Pos)) |
                    (R_MFWD_FWIP6OC_IP6IPOM_Msk &
                     (uint32_t) (p_filter_cfg->ipv6_address0.direction << R_MFWD_FWIP6OC_IP6IPOM_Pos)));

    /* Set IPv4/IPv6 hash equation. */
    R_MFWD->FWSFHEC = (uint32_t) ((1 << R_MFWD_FWSFHEC_IP4HE_Pos) | (1 << R_MFWD_FWSFHEC_IP6HE_Pos));

    return FSP_SUCCESS;
}                                      /* End of function r_layer3_switch_configure_stream_filter() */

/*******************************************************************************************************************
 * Calculate a layer3 hash value of the target frame.
 *
 * @param[in] p_frame Pointer to the target frame.
 **********************************************************************************************************************/
uint16_t r_layer3_switch_calculate_l3_hash (layer3_switch_frame_filter_t const * p_frame)
{
    uint16_t hash_value;

    /* If target is not IP packet, hash value is 0. */
    if (LAYER3_SWITCH_IP_VERSION_NONE == p_frame->ip_version)
    {
        hash_value = 0;
    }
    else
    {
        /* Set destination MAC address. */
        if (NULL != p_frame->p_destination_mac_address)
        {
            R_MFWD->FWSHCR0           = r_layer3_switch_convert_array_to_int(&p_frame->p_destination_mac_address[0], 4);
            R_MFWD->FWSHCR1_b.SHCMDP1 = (uint16_t) r_layer3_switch_convert_array_to_int(
                &p_frame->p_destination_mac_address[4],
                2);
        }
        else
        {
            R_MFWD->FWSHCR0           = 0;
            R_MFWD->FWSHCR1_b.SHCMDP1 = 0;
        }

        if (NULL != p_frame->p_source_mac_address)
        {
            /* Source address should be input as 2 byte higher part and 4 byte lower part. */
            R_MFWD->FWSHCR1_b.SHCMSP0 = (uint16_t) r_layer3_switch_convert_array_to_int(
                &p_frame->p_source_mac_address[0],
                2);
            R_MFWD->FWSHCR2 = r_layer3_switch_convert_array_to_int(&p_frame->p_source_mac_address[2], 4);
        }
        else
        {
            R_MFWD->FWSHCR1_b.SHCMSP0 = 0;
            R_MFWD->FWSHCR2           = 0;
        }

        /* Set VLANs. */
        R_MFWD->FWSHCR3 = r_layer3_switch_convert_vlan_tag_to_int(&p_frame->vlan_s_tag, &p_frame->vlan_c_tag);

        /* Set IP addresses. */
        if (LAYER3_SWITCH_IP_VERSION_IPV4 == p_frame->ip_version)
        {
            /* Set IP protocol. */
            R_MFWD->FWSHCR4 = p_frame->protocol;

            /* IPv4 source. */
            R_MFWD->FWSHCR5 = 0;
            R_MFWD->FWSHCR6 = 0;
            R_MFWD->FWSHCR7 = 0;
            R_MFWD->FWSHCR8 = r_layer3_switch_convert_array_to_int(p_frame->p_source_ip_address, 4);

            /* IPv4 destination. */
            R_MFWD->FWSHCR9  = 0;
            R_MFWD->FWSHCR10 = 0;
            R_MFWD->FWSHCR11 = 0;
            R_MFWD->FWSHCR12 = r_layer3_switch_convert_array_to_int(p_frame->p_destination_ip_address, 4);
        }
        else
        {
            /* Set IP protocol and IPv6 bit. */
            R_MFWD->FWSHCR4 = (1 << R_MFWD_FWSHCR4_SHCFF_Pos) | p_frame->protocol;

            /* IPv6 source. */
            if (NULL != p_frame->p_source_ip_address)
            {
                R_MFWD->FWSHCR5 = r_layer3_switch_convert_array_to_int(&p_frame->p_source_ip_address[0], 4);
                R_MFWD->FWSHCR6 = r_layer3_switch_convert_array_to_int(&p_frame->p_source_ip_address[4], 4);
                R_MFWD->FWSHCR7 = r_layer3_switch_convert_array_to_int(&p_frame->p_source_ip_address[8], 4);
                R_MFWD->FWSHCR8 = r_layer3_switch_convert_array_to_int(&p_frame->p_source_ip_address[12], 4);
            }
            else
            {
                R_MFWD->FWSHCR5 = 0;
                R_MFWD->FWSHCR6 = 0;
                R_MFWD->FWSHCR7 = 0;
                R_MFWD->FWSHCR8 = 0;
            }

            /* IPv6 destination. */
            if (NULL != p_frame->p_destination_ip_address)
            {
                R_MFWD->FWSHCR9  = r_layer3_switch_convert_array_to_int(&p_frame->p_destination_ip_address[0], 4);
                R_MFWD->FWSHCR10 = r_layer3_switch_convert_array_to_int(&p_frame->p_destination_ip_address[4], 4);
                R_MFWD->FWSHCR11 = r_layer3_switch_convert_array_to_int(&p_frame->p_destination_ip_address[8], 4);
                R_MFWD->FWSHCR12 = r_layer3_switch_convert_array_to_int(&p_frame->p_destination_ip_address[12], 4);
            }
            else
            {
                R_MFWD->FWSHCR9  = 0;
                R_MFWD->FWSHCR10 = 0;
                R_MFWD->FWSHCR11 = 0;
                R_MFWD->FWSHCR12 = 0;
            }
        }

        /* Set layer4 destination/source ports. That used for TCP and UDP. */
        R_MFWD->FWSHCR13 =
            (R_MFWD_FWSHCR13_SHCDP_Msk &
             (uint32_t) (p_frame->layer4_destination_port << R_MFWD_FWSHCR13_SHCDP_Pos)) |
            (R_MFWD_FWSHCR13_SHCSP_Msk &
             (uint32_t) (p_frame->layer4_source_port << R_MFWD_FWSHCR13_SHCSP_Pos));

        /* After writing FWSHCR13 register, IP start calculation. */
        /* Wait for completing calculation. */
        FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWSHCRR_b.SHC, 0);

        /* Read hash value. */
        hash_value = R_MFWD->FWSHCRR_b.SHCR;
    }

    return hash_value;
}                                      /* End of function r_layer3_switch_calculate_l3_hash() */

/*******************************************************************************************************************
 * Calculate a layer3 format code of the target frame.
 *
 * @param[in] p_frame Pointer to the target frame.
 **********************************************************************************************************************/
uint8_t r_layer3_switch_calculate_l3_format_code (layer3_switch_frame_filter_t const * p_frame)
{
    uint8_t ip_version_offset  = 0;
    uint8_t ip_protocol_offset = 0;

    /* Get the offset value of format code based on the IP version. */
    switch (p_frame->ip_version)
    {
        case LAYER3_SWITCH_IP_VERSION_IPV4:
        {
            ip_version_offset = 1;
            break;
        }

        case LAYER3_SWITCH_IP_VERSION_IPV6:
        {
            ip_version_offset = 4;
            break;
        }

        case LAYER3_SWITCH_IP_VERSION_NONE:
        {
            /* When not IP packet. */
            ip_version_offset = 7;
            break;
        }

        default:
        {
            /* Not reach here. */
            break;
        }
    }

    if (LAYER3_SWITCH_IP_VERSION_NONE != p_frame->ip_version)
    {
        switch (p_frame->protocol)
        {
            case LAYER3_SWITCH_IP_PROTOCOL_UDP:
            {
                ip_protocol_offset = 1;
                break;
            }

            case LAYER3_SWITCH_IP_PROTOCOL_TCP:
            {
                ip_protocol_offset = 2;
                break;
            }

            default:
            {
                ip_protocol_offset = 0;
                break;
            }
        }
    }

    /* Return frame format code. */
    return ip_version_offset + ip_protocol_offset;
}                                      /* End of function r_layer3_switch_calculate_l3_format_code() */

/*******************************************************************************************************************
 * Calculate a layer3 stream ID of the target frame.
 *
 * @param[in] p_frame Pointer to the target frame.
 * @param[out] p_stream_id Pointer to the stream ID.
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_calculate_l3_stream_id (layer3_switch_frame_filter_t const * p_frame,
                                                         layer3_switch_stream_id_t          * p_stream_id)
{
    uint32_t ip_address0 = 0;
    uint32_t ip_address1 = 0;
    uint32_t ipv6_offset;

    switch (p_frame->ip_version)
    {
        case LAYER3_SWITCH_IP_VERSION_IPV4:
        {
            ip_address0 = r_layer3_switch_convert_array_to_int(p_frame->p_source_ip_address, 4);
            ip_address1 = r_layer3_switch_convert_array_to_int(p_frame->p_destination_ip_address, 4);

            break;
        }

        case LAYER3_SWITCH_IP_VERSION_IPV6:
        {
            /* Extract 4 bytes from the IPv6 address according to the offset configuration. */
            ipv6_offset = R_MFWD->FWIP6OC_b.IP6IPO0;
            if ((0 == R_MFWD->FWIP6OC_b.IP6IPOM0) && (NULL != p_frame->p_source_ip_address))
            {
                /* Use source IP address. */
                ip_address0 = r_layer3_switch_convert_array_to_int(&p_frame->p_source_ip_address[ipv6_offset], 4);
            }
            else if ((1 == R_MFWD->FWIP6OC_b.IP6IPOM0) && (NULL != p_frame->p_destination_ip_address))
            {
                /* Use destination IP address. */
                ip_address0 = r_layer3_switch_convert_array_to_int(&p_frame->p_destination_ip_address[ipv6_offset], 4);
            }
            else
            {
                ip_address0 = 0;
            }

            /* Extract additional 4 bytes according to another offset configuration. */
            ipv6_offset = R_MFWD->FWIP6OC_b.IP6IPO1;
            if ((0 == R_MFWD->FWIP6OC_b.IP6IPOM1) && (NULL != p_frame->p_source_ip_address))
            {
                ip_address1 = r_layer3_switch_convert_array_to_int(&p_frame->p_source_ip_address[ipv6_offset], 4);
            }
            else if ((1 == R_MFWD->FWIP6OC_b.IP6IPOM1) && (NULL != p_frame->p_destination_ip_address))
            {
                ip_address1 = r_layer3_switch_convert_array_to_int(&p_frame->p_destination_ip_address[ipv6_offset], 4);
            }
            else
            {
                ip_address1 = 0;
            }

            break;
        }

        default:
        {
            break;
        }
    }

    /* Common for stream filters. */
    p_stream_id->frame_format_code =
        r_layer3_switch_calculate_l3_format_code(p_frame);
    p_stream_id->words[0] = r_layer3_switch_convert_vlan_tag_to_int(&p_frame->vlan_s_tag, &p_frame->vlan_c_tag);

    if (LAYER3_SWITCH_IP_VERSION_NONE == p_frame->ip_version)
    {
        /* When Layer2 stream filter. */

        /* Set destination MAC address. */
        if (NULL != p_frame->p_destination_mac_address)
        {
            p_stream_id->words[1] = r_layer3_switch_convert_array_to_int(&p_frame->p_destination_mac_address[0], 4);
            p_stream_id->words[2] =
                r_layer3_switch_convert_array_to_int(&p_frame->p_destination_mac_address[4], 2) << 16;
        }

        /* Source address should be input as 2 byte higher part and 4 byte lower part. */
        if (NULL != p_frame->p_source_mac_address)
        {
            p_stream_id->words[2] |= r_layer3_switch_convert_array_to_int(&p_frame->p_source_mac_address[0], 2);
            p_stream_id->words[3]  = r_layer3_switch_convert_array_to_int(&p_frame->p_source_mac_address[2], 4);
        }
    }
    else
    {
        /* When IPv4/IPv6 stream filter. */
        p_stream_id->words[1] = (uint32_t) ((p_frame->layer4_destination_port << 16) |
                                            r_layer3_switch_calculate_l3_hash(p_frame));
        p_stream_id->words[2] = ip_address0;
        p_stream_id->words[3] = ip_address1;
    }

    return FSP_SUCCESS;
}                                      /* End of function r_layer3_switch_calculate_l3_stream_id() */

/*******************************************************************************************************************
 * Configure remapping feature for L3 update.
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_remapping_l3_update (layer3_switch_instance_ctrl_t    * p_instance_ctrl,
                                                      uint32_t                           routing_number,
                                                      layer3_switch_l3_update_config_t * p_update_cfg)
{
    uint8_t             dest_port            = (uint8_t) (31 - __CLZ(p_update_cfg->enable_destination_ports));
    volatile uint32_t * p_mfwd_fwl23urmc_reg = &R_MFWD->FWL23URMC0 + p_instance_ctrl->l3_remapping_number;
    fsp_err_t           err;

    FSP_ERROR_RETURN(LAYER3_SWITCH_L3_UPDATE_REMAPPING_MAX_NUM >= p_instance_ctrl->l3_remapping_number,
                     FSP_ERR_WRITE_FAILED);

    /* Learn new l3 update rule. */
    err = r_layer3_switch_learn_l3_update(p_instance_ctrl, p_update_cfg);

    if (FSP_SUCCESS == err)
    {
        /* Set remapping feature. */
        *p_mfwd_fwl23urmc_reg = (routing_number << R_MFWD_FWL23URMC0_RMRN_Pos) |
                                (uint32_t) (dest_port << R_MFWD_FWL23URMC0_RMDPN_Pos) |
                                (uint32_t) ((p_instance_ctrl->l3_routing_number - 1) << R_MFWD_FWL23URMC0_RMNRN_Pos) |
                                R_MFWD_FWL23URMC0_RME_Msk;

        /* Increment indexes. */
        p_instance_ctrl->l3_routing_number   += 1;
        p_instance_ctrl->l3_remapping_number += 1;
    }

    return err;
}                                      /* End of function r_layer3_switch_remapping_l3_update() */

/*******************************************************************************************************************
 * Convert VLAN SC-TAG to uint32_t.
 *
 * @param[in] p_vlan_s_tag Pointer to a VLAN S-TAG.
 * @param[in] p_vlan_c_tag Pointer to a VLAN C-TAG.
 **********************************************************************************************************************/
static uint32_t r_layer3_switch_convert_vlan_tag_to_int (layer3_switch_frame_vlan_tag_t const * p_vlan_s_tag,
                                                         layer3_switch_frame_vlan_tag_t const * p_vlan_c_tag)
{
    return (uint32_t) (
        (((p_vlan_s_tag->pcp << LAYER3_SWITCH_VLAN_TAG_PCP_POSITION) |
          (p_vlan_s_tag->dei << LAYER3_SWITCH_VLAN_TAG_DEI_POSITION) | p_vlan_s_tag->id) << 16) |
        ((p_vlan_c_tag->pcp << LAYER3_SWITCH_VLAN_TAG_PCP_POSITION) |
         (p_vlan_c_tag->dei << LAYER3_SWITCH_VLAN_TAG_DEI_POSITION) | p_vlan_c_tag->id));
}                                      /* End of function r_layer3_switch_convert_vlan_tag_to_int() */

/*******************************************************************************************************************
 * Convert a uint8_t array to int32_t.
 *
 * @param[in] array Pointer to a array.
 **********************************************************************************************************************/
static uint32_t r_layer3_switch_convert_array_to_int (uint8_t * array, uint8_t length)
{
    uint32_t result = 0;
    if (NULL != array)
    {
        for (int i = 0; i < length; i++)
        {
            result |= (uint32_t) (array[i] << (8 * (length - 1 - i)));
        }
    }

    return result;
}                                      /* End of function r_layer3_switch_convert_array_to_int() */

/*******************************************************************************************************************
 * Configure CBS feature for a port.
 **********************************************************************************************************************/
static void r_layer3_switch_configure_cbs (layer3_switch_instance_ctrl_t const * p_instance_ctrl,
                                           uint8_t                               port,
                                           layer3_switch_cbs_cfg_t const       * p_cbs_cfg)
{
    R_ETHA0_Type * p_etha_reg =
        (R_ETHA0_Type *) (R_ETHA0_BASE + (LAYER3_SWITCH_ETHA_REG_SIZE * port));

    /* CBS registers for the target queue. */
    volatile uint32_t * p_eacaivc_reg;
    volatile uint32_t * p_eacaulc_reg;

    double   bandwidth_fraction;
    double   civ_raw_value;
    uint32_t civ_int_value;
    uint32_t max_interference_size;
    uint8_t  enable_cbs_bitmask = 0;
    uint32_t eswclk_frequency;
    uint32_t link_speed = 0;
    ether_phy_instance_t const * p_phy_instance =
        ((layer3_switch_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend)->p_ether_phy_instances[port];

    /*Get frequency of ESWCLK. */
    eswclk_frequency = R_BSP_SourceClockHzGet((fsp_priv_source_clock_t) (R_SYSTEM->ESWCKCR_b.CKSEL)) /
                       R_FSP_ClockDividerGet(R_SYSTEM->ESWCKDIVCR_b.CKDIV);

    /* Get link speed. */
    switch (p_phy_instance->p_cfg->mii_type)
    {
        /* 100 Mbps. */
        case ETHER_PHY_MII_TYPE_MII:
        case ETHER_PHY_MII_TYPE_RMII:
        {
            link_speed = LAYER3_SWITCH_LINK_SPEED_100M;
            break;
        }

        /* 1000 Mbps. */
        case ETHER_PHY_MII_TYPE_GMII:
        case ETHER_PHY_MII_TYPE_RGMII:
        {
            link_speed = LAYER3_SWITCH_LINK_SPEED_1G;
            break;
        }

        default:
        {
            break;
        }
    }

    for (uint8_t i = 0; i < BSP_FEATURE_ESWM_ETHA_IPV_QUEUE_NUM; i++)
    {
        if (0 != p_cbs_cfg->band_width_list[i])
        {
            p_eacaivc_reg = (volatile uint32_t *) ((uint8_t *) &p_etha_reg->EACAIVC0 + (4 * i));
            p_eacaulc_reg = (volatile uint32_t *) ((uint8_t *) &p_etha_reg->EACAULC0 + (4 * i));

            /* Calculate CIV (Credit Increment Value). */
            bandwidth_fraction = p_cbs_cfg->band_width_list[i] / 100.0;
            civ_raw_value      = (link_speed / LAYER3_SWITCH_CBS_BITS_PER_BYTE) * bandwidth_fraction / eswclk_frequency;
            civ_int_value      =
                (uint32_t) (((uint8_t) civ_raw_value << 16) | (uint16_t) (civ_raw_value * (UINT16_MAX + 1)));

            /* Set CIV value to the register.  */
            *p_eacaivc_reg = civ_int_value;

            /* Calculate credit upper limit. */
            max_interference_size = r_layer3_switch_calculate_max_interference_size(i, p_cbs_cfg->max_burst_num_list);
            *p_eacaulc_reg        = 0 *
                                    max_interference_size *
                                    (eswclk_frequency / (link_speed + LAYER3_SWITCH_CBS_REQUEST_DELAY)) * civ_int_value;
            enable_cbs_bitmask |= (1 << i);
        }
    }

    /* Enable and apply CBS configuration. */
    p_etha_reg->EACAEC = enable_cbs_bitmask;
    p_etha_reg->EACC   = enable_cbs_bitmask;
}                                      /* End of function r_layer3_switch_configure_cbs() */

/*******************************************************************************************************************
 * Calculate max interference size which used to configure CBS.
 **********************************************************************************************************************/
static uint32_t r_layer3_switch_calculate_max_interference_size (uint8_t         queue_number,
                                                                 uint8_t const * p_max_burst_num_list)
{
    uint32_t queue_interference_size = (LAYER3_SWITCH_MAXIMUM_FRAME_SIZE + LAYER3_SWITCH_CBS_INTERFERENCE_SIZE_OFFSET) *
                                       LAYER3_SWITCH_CBS_BITS_PER_BYTE;
    uint32_t queue_interference_size_low  = 0;
    uint32_t queue_interference_size_high = 0;

    /* Get the interference size of the queues with lower priority than the target queue. */
    if (queue_number > 0)
    {
        queue_interference_size_low = (LAYER3_SWITCH_MAXIMUM_FRAME_SIZE + LAYER3_SWITCH_CBS_INTERFERENCE_SIZE_OFFSET) *
                                      LAYER3_SWITCH_CBS_BITS_PER_BYTE;
    }

    /* Get the interference size of the queues with higher priority than the target queue. */
    for (uint8_t i = queue_number + 1; i < BSP_FEATURE_ESWM_ETHA_IPV_QUEUE_NUM; i++)
    {
        if (0 != p_max_burst_num_list[i])
        {
            queue_interference_size_high +=
                (LAYER3_SWITCH_MAXIMUM_FRAME_SIZE * 2 + LAYER3_SWITCH_CBS_INTERFERENCE_SIZE_OFFSET * 2) *
                LAYER3_SWITCH_CBS_BITS_PER_BYTE;
        }
        else
        {
            queue_interference_size_high +=
                ((p_max_burst_num_list[i] + 1) * LAYER3_SWITCH_MAXIMUM_FRAME_SIZE +
                 LAYER3_SWITCH_CBS_INTERFERENCE_SIZE_OFFSET * 2) * LAYER3_SWITCH_CBS_BITS_PER_BYTE;
        }
    }

    return queue_interference_size_low + queue_interference_size + queue_interference_size_high;
}                                      /* End of function r_layer3_switch_calculate_max_interference_size() */

/***********************************************************************************************************************
 * Create queue of transmission timestamp.
 ***********************************************************************************************************************/
static fsp_err_t r_layer3_switch_create_tx_timestamp_queue (ether_switch_ctrl_t * const                        p_ctrl,
                                                            const layer3_switch_descriptor_queue_cfg_t * const p_queue_cfg,
                                                            uint32_t * const                                   p_ts_descriptor_queue_index)
{
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) p_ctrl;
    layer3_switch_extended_cfg_t  * p_extend;
    layer3_switch_ts_reception_process_descriptor_t * p_ts_descriptor;

    volatile uint32_t * p_gwtsdcc_reg;  /* Timestamp Descriptor Chain Configuration */
    volatile uint32_t * p_gwtdcac0_reg; /* Timestamp Descriptor Chain Address Configuration 0 */
    volatile uint32_t * p_gwtdcac1_reg; /* Timestamp Descriptor Chain Address Configuration 1 */

    uint8_t port = (uint8_t) (1 & (p_queue_cfg->ports >> 1));

    p_extend = (layer3_switch_extended_cfg_t *) p_instance_ctrl->p_cfg->p_extend;

    /* Search TS descriptor queue can use. */
    uint32_t ts_descriptor_queue_index = 0;
    for (ts_descriptor_queue_index = 0;
         ts_descriptor_queue_index < BSP_FEATURE_ESWM_TS_DESCRIPTOR_QUEUE_MAX_NUM;
         ts_descriptor_queue_index++)
    {
        if (port == ts_descriptor_queue_index)
        {
            if (LAYER3_SWITCH_TS_DESCRIPTOR_QUEUE_STATUS_UNUSED ==
                p_instance_ctrl->ts_descriptor_queue_status_list[ts_descriptor_queue_index])
            {
                break;
            }
        }
    }

    FSP_ERROR_RETURN(BSP_FEATURE_ESWM_TS_DESCRIPTOR_QUEUE_MAX_NUM > ts_descriptor_queue_index, FSP_ERR_OVERFLOW);

    p_ts_descriptor = p_queue_cfg->p_ts_descriptor_array;

    /* Initialize TS descriptor in queue. */
    for (uint8_t i = 0; i < (p_queue_cfg->array_length - 1); i++)
    {
        p_ts_descriptor[i].ts_reception_descriptor_basic.dt  = LAYER3_SWITCH_DESCRIPTOR_TYPE_FEMPTY_ND;
        p_ts_descriptor[i].ts_reception_descriptor_basic.die = 1;
    }

    p_ts_descriptor[(p_queue_cfg->array_length -
                     1)].ts_reception_descriptor_basic.dt = LAYER3_SWITCH_DESCRIPTOR_TYPE_LINKFIX;
    p_ts_descriptor[(p_queue_cfg->array_length -
                     1)].ts_reception_descriptor_basic.ptr_l = (uintptr_t) p_ts_descriptor;

    /* Set GWCA to CONFIG mode. */
    r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_DISABLE);
    r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_CONFIG);

    p_gwtdcac0_reg = (volatile uint32_t *) ((uint8_t *) &p_instance_ctrl->p_gwca_reg->GWTDCAC00 +
                                            (LAYER3_SWITCH_TS_DESCRIPTOR_QUEUE_REGISTOR_OFFSET *
                                             ts_descriptor_queue_index));

    p_gwtdcac1_reg = (volatile uint32_t *) ((uint8_t *) &p_instance_ctrl->p_gwca_reg->GWTDCAC10 +
                                            (LAYER3_SWITCH_TS_DESCRIPTOR_QUEUE_REGISTOR_OFFSET *
                                             ts_descriptor_queue_index));

    *p_gwtdcac1_reg = (uintptr_t) p_ts_descriptor;
    *p_gwtdcac0_reg = 0;

    p_gwtsdcc_reg = (volatile uint32_t *) ((uint8_t *) &p_instance_ctrl->p_gwca_reg->GWTSDCC0 +
                                           (LAYER3_SWITCH_TS_DESCRIPTOR_TIMER_REGISTOR_OFFSET *
                                            p_extend->gptp_timer_numbers[port]));

    *p_gwtsdcc_reg = ((1U << R_GWCA0_GWTSDCC0_TE_Pos) |
                      (ts_descriptor_queue_index << R_GWCA0_GWTSDCC0_DCS_Pos));

    /* Set GWCA to OPERATION mode. */
    r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_DISABLE);
    r_layer3_switch_update_gwca_operation_mode(p_instance_ctrl, LAYER3_SWITCH_AGENT_MODE_OPERATION);

    /* Output TS Descriptor queue index and change state used. */
    *p_ts_descriptor_queue_index = ts_descriptor_queue_index;
    p_instance_ctrl->ts_descriptor_queue_status_list[ts_descriptor_queue_index] =
        LAYER3_SWITCH_TS_DESCRIPTOR_QUEUE_STATUS_USED;

    return FSP_SUCCESS;
}                                      /* End of function r_layer3_switch_create_tx_timestamp_queue() */

/*******************************************************************************************************************
 * FRER initialization.
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_frer_init (layer3_switch_instance_ctrl_t  * p_instance_ctrl,
                                            layer3_switch_frer_cfg_t const * p_frer_cfg)
{
    volatile uint32_t * p_fwseqngc_reg;

#if LAYER3_SWITCH_CFG_PARAM_CHECKING_ENABLE
    FSP_ERROR_RETURN(p_frer_cfg, FSP_ERR_INVALID_POINTER);
#endif

    r_layer3_switch_frer_table_reset();

    /* Set FRER timeout us prescaler 1 MHz to derive the timeout 1 kHz clock. */
    R_MFWD->FWFTOPC_b.USP = p_frer_cfg->sys_clock & LAYER3_SWITCH_FRER_SYSTEM_CLOCK_BITMASK;
    R_MFWD->FWFTOC_b.TOCE = p_frer_cfg->timeout_enable & 0x1U;
    R_MFWD->FWFTOC_b.TOT  = p_frer_cfg->check_period & LAYER3_SWITCH_FRER_CHECK_PERIOD_BITMASK;

    /* Sequence number generation reset n (n = 0 to 31). */
    R_MFWD->FWSEQNRC_b.SEQNR |= R_MFWD_FWSEQNRC_SEQNR_Msk;

    /* FWSEQNGCi(i = 0~31) 0 write. */
    for (uint32_t i = 0; i < LAYER3_SWITCH_SEQ_REG_MAX_NUM; i++)
    {
        p_fwseqngc_reg =
            (uint32_t *) ((uintptr_t) (&R_MFWD->FWSEQNGC0) + (i * LAYER3_SWITCH_FWSEQNGC_REGISTER_OFFSET));
        *p_fwseqngc_reg = 0;
    }

    /*SEQNR 0 write. */
    R_MFWD->FWSEQNRC_b.SEQNR &= ~R_MFWD_FWSEQNRC_SEQNR_Msk;

    /* Reset current register index. */
    p_instance_ctrl->valid_frer_entry_num = 0;

    R_MFWD->FWSEQNRC |= R_MFWD_FWSEQNRC_SEQNR_Msk;
    for (uint32_t i = 0; i < LAYER3_SWITCH_SEQ_REG_MAX_NUM; i++)
    {
        p_fwseqngc_reg =
            (uint32_t *) ((uintptr_t) (&R_MFWD->FWSEQNGC0) + (i * LAYER3_SWITCH_FWSEQNGC_REGISTER_OFFSET));
        *p_fwseqngc_reg = 0;
    }

    R_MFWD->FWSEQNRC &= ~R_MFWD_FWSEQNRC_SEQNR_Msk;

    p_instance_ctrl->used_frer_sequence_generator_num = 0;

    return FSP_SUCCESS;
}                                      /* End of function r_layer3_switch_frer_init() */

/*******************************************************************************************************************
 * Reset FRER table.
 **********************************************************************************************************************/
static void r_layer3_switch_frer_table_reset (void)
{
    R_MFWD->FWFTIM_b.FTIOG = R_MFWD_FWFTIM_FTIOG_Msk;    /* FRER Table Initialization Ongoing */
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWFTIM_b.FTR, 1); /* FRER Table Ready */
}                                                        /* End of function r_layer3_switch_frer_table_reset() */

/*******************************************************************************************************************
 * Configure sequence number generate.
 **********************************************************************************************************************/
static void r_layer3_switch_configure_sequence_number_generation (layer3_switch_instance_ctrl_t * p_instance_ctrl)
{
    volatile uint32_t * p_fwseqngc_reg;
    uint32_t            fwseqngc_reg_value;

    /* Get FWSEQNGCi register address. */
    p_fwseqngc_reg =
        (uint32_t *) ((uintptr_t) (&R_MFWD->FWSEQNGC0) +
                      ((p_instance_ctrl->used_frer_sequence_generator_num &
                        LAYER3_SWITCH_FRER_SEQ_GENERATOR_NUM_BITMASK) *
                       LAYER3_SWITCH_FWSEQNGC_REGISTER_OFFSET));
    fwseqngc_reg_value = *p_fwseqngc_reg;

    /* Sequence generation enable. Routing number set. Sequence number generate valid. */
    fwseqngc_reg_value |= (p_instance_ctrl->l3_routing_number & R_MFWD_FWSEQNGC0_SEQNGRN_Msk) |
                          (1U << R_MFWD_FWSEQNGC0_SEQNGE_Pos);
    *p_fwseqngc_reg = fwseqngc_reg_value;
}                                      /* End of function r_layer3_switch_configure_sequence_number_generation() */

/*******************************************************************************************************************
 * Learn an entry of FRER table.
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_learn_frer_entry (layer3_switch_instance_ctrl_t    * p_instance_ctrl,
                                                   layer3_switch_frer_entry_t * const p_frer_entry,
                                                   layer3_switch_frer_entry_t * const p_sequence_recovery,
                                                   uint32_t                           sequence_recovery_id)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t  sequence_recovery_addr = 0;

    if (NULL != p_sequence_recovery)
    {
        sequence_recovery_addr =
            p_instance_ctrl->frer_sequence_recovery_status[sequence_recovery_id &
                                                           LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK].frer_entry_index &
            LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK;
    }

    /* Set entry address and sequence recovery pointer. */
    R_MFWD->FWFTL0 = (R_MFWD_FWFTL0_FSRPL_Msk & (sequence_recovery_addr << R_MFWD_FWFTL0_FSRPL_Pos)) |
                     (R_MFWD_FWFTL0_FEAL_Msk & (p_instance_ctrl->valid_frer_entry_num << R_MFWD_FWFTL0_FEAL_Pos));

    /* Set sequence recovery settings. */
    R_MFWD->FWFTL1 =
        (R_MFWD_FWFTL1_FSHLL_Msk & (p_frer_entry->sequence_history_len << R_MFWD_FWFTL1_FSHLL_Pos)) |
        (R_MFWD_FWFTL1_FTNSL_Msk & (p_frer_entry->take_no_sequence << R_MFWD_FWFTL1_FTNSL_Pos)) |
        (R_MFWD_FWFTL1_FSRPVL_Msk &
         (uint32_t) ((NULL != p_sequence_recovery) << R_MFWD_FWFTL1_FSRPVL_Pos)) |
        (R_MFWD_FWFTL1_FSRRTL_Msk & (p_frer_entry->set_recovery_remaining_tick << R_MFWD_FWFTL1_FSRRTL_Pos));

    /* Wait for learning complete. */
    FSP_HARDWARE_REGISTER_WAIT(R_MFWD->FWFTLR_b.FTL, 0);

    /* Check learning error. */
    if (1 == R_MFWD->FWFTLR_b.FLF)
    {
        err = FSP_ERR_WRITE_FAILED;
    }
    else
    {
        /* Store the entry information to sequence recovery table. */
        if (NULL == p_sequence_recovery)
        {
            p_instance_ctrl->frer_sequence_recovery_status[sequence_recovery_id &
                                                           LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK].learned =
                true;
            p_instance_ctrl->frer_sequence_recovery_status[sequence_recovery_id &
                                                           LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK].frer_entry_index =
                p_instance_ctrl->valid_frer_entry_num & LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK;
        }

        /* Update the current index of the FRER table. */
        p_instance_ctrl->valid_frer_entry_num = (p_instance_ctrl->valid_frer_entry_num + 1) &
                                                LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK;
    }

    return err;
}                                      /* End of function r_layer3_switch_learn_frer_entry() */

/*******************************************************************************************************************
 * Learn a individual recovery entry of FRER entry.
 **********************************************************************************************************************/
static fsp_err_t r_layer3_switch_learn_frer_individual_recovery (layer3_switch_instance_ctrl_t        * p_instance_ctrl,
                                                                 layer3_switch_frer_entry_cfg_t * const p_frer_entry_cfg)
{
    fsp_err_t err = FSP_SUCCESS;

    /* When the target sequence recovery has not been learned, first learn the sequence recovery entry. */
    if ((NULL != p_frer_entry_cfg->p_sequence_recovery) &&
        (false ==
         p_instance_ctrl->frer_sequence_recovery_status[p_frer_entry_cfg->sequence_recovery_id &
                                                        LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK].learned))
    {
        r_layer3_switch_learn_frer_entry(p_instance_ctrl,
                                         p_frer_entry_cfg->p_sequence_recovery,
                                         NULL,
                                         p_frer_entry_cfg->sequence_recovery_id &
                                         LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK);
    }

    /* Add the FRER individual recovery entry. */
    err = r_layer3_switch_learn_frer_entry(p_instance_ctrl,
                                           &p_frer_entry_cfg->individual_recovery,
                                           p_frer_entry_cfg->p_sequence_recovery,
                                           p_frer_entry_cfg->sequence_recovery_id &
                                           LAYER3_SWITCH_FRER_ENTRY_NUM_BITMASK);

    return err;
}                                      /* End of function r_layer3_switch_learn_frer_individual_recovery() */

/*******************************************************************************************************************
 * Calls user callback for each ports.
 *
 * @param[in]     p_instance_ctrl      Pointer to a instance control.
 * @param[in]     p_callback_args      Pointer to callback args.
 * @param[in]     ports      Ports that should call user callback.
 **********************************************************************************************************************/
static void r_layer3_switch_call_callback_for_ports (layer3_switch_instance_ctrl_t * p_instance_ctrl,
                                                     ether_switch_callback_args_t  * p_callback_args,
                                                     uint32_t                        ports)
{
    /* Call port-specific callback for each port. */
    for (uint8_t i = 0; i < BSP_FEATURE_ETHER_NUM_CHANNELS; i++)
    {
        /* Check if event occurred on this port. */
        if (0 != (ports & (1 << i)))
        {
            if (NULL != p_instance_ctrl->p_port_cfg_list[i].p_callback)
            {
                p_callback_args->p_context = p_instance_ctrl->p_port_cfg_list[i].p_context;
                r_layer3_switch_call_callback(p_instance_ctrl->p_port_cfg_list[i].p_callback,
                                              p_callback_args,
                                              p_instance_ctrl->p_port_cfg_list[i].p_callback_memory);
            }
        }
    }
}                                      /* End of function r_layer3_switch_call_callback_for_ports() */

/*******************************************************************************************************************//**
 * Calls user callback.
 *
 * @param[in]     p_callback           Function pointer to target callback
 * @param[in]     p_callback_args      Pointer to callback args
 * @param[in]     p_callback_memory    Pointer to memory allocated for callback arguments
 **********************************************************************************************************************/
static void r_layer3_switch_call_callback (void (* p_callback)(
                                               ether_switch_callback_args_t *),
                                           ether_switch_callback_args_t       * p_callback_args,
                                           ether_switch_callback_args_t * const p_callback_memory)
{
    ether_switch_callback_args_t args;

    /* Store callback arguments in memory provided by user if available.  This allows callback arguments to be
     * stored in non-secure memory so they can be accessed by a non-secure callback function. */
    ether_switch_callback_args_t * p_args = p_callback_memory;

    if (NULL == p_args)
    {
        /* Store on stack. */
        p_args = &args;
    }
    else
    {
        /* Save current arguments on the stack in case this is a nested interrupt. */
        args = *p_args;
    }

    memcpy(p_args, p_callback_args, sizeof(ether_switch_callback_args_t));

#if BSP_TZ_SECURE_BUILD && BSP_FEATURE_ETHER_SUPPORTS_TZ_SECURE

    /* p_callback can point to a secure function or a non-secure function. */
    if (!cmse_is_nsfptr(p_callback))
    {
        /* If p_callback is secure, then the project does not need to change security state. */
        p_callback(p_args);
    }
    else
    {
        /* If p_callback is Non-secure, then the project must change to Non-secure state in order to call the callback. */
        layer3_switch_prv_ns_callback p_ns_callback = (layer3_switch_prv_ns_callback) (p_callback);
        p_ns_callback(p_args);
    }

#else

    /* If the project is not TrustZone Secure, then it will never need to change security state in order to call the callback. */
    p_callback(p_args);
#endif

    if (NULL != p_callback_memory)
    {
        /* Restore callback memory in case this is a nested interrupt. */
        *p_callback_memory = args;
    }
}                                      /* End of function r_layer3_switch_call_callback() */

/***********************************************************************************************************************
 * Function Name: layer3_switch_gwdi_isr
 * Description  : Interrupt handler for GWCA data interrupts that includes RX/TX complete and buffer full error events.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
void layer3_switch_gwdi_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    ether_switch_callback_args_t    callback_arg    = {};
    bool port_callback_exists = false;

    uint32_t            gwdi_status;
    uint32_t            gwei2_status;
    volatile uint32_t * p_gwca_gwdi_reg;
    volatile uint32_t * p_gwca_gwei2_reg;

    /* Check if port-specific callbacks are set. */
    for (uint8_t i = 0; i < BSP_FEATURE_ETHER_NUM_CHANNELS; i++)
    {
        if (NULL != p_instance_ctrl->p_port_cfg_list[i].p_callback)
        {
            port_callback_exists = true;
            break;
        }
    }

    /* Get queue ISR happened. */
    for (uint32_t i = 0; i < (LAYER3_SWITCH_CFG_AVAILABLE_QUEUE_NUM / LAYER3_SWITCH_REGISTER_SIZE) + 1; i++)
    {
        /* Get status register address. */
        p_gwca_gwdi_reg =
            (uint32_t *) ((uintptr_t) &(p_instance_ctrl->p_gwca_reg->GWDIS0) +
                          (i * LAYER3_SWITCH_INTERRUPT_REGISTER_OFFSET));
        p_gwca_gwei2_reg =
            (uint32_t *) ((uintptr_t) &(p_instance_ctrl->p_gwca_reg->GWEIS20) +
                          (i * LAYER3_SWITCH_INTERRUPT_REGISTER_OFFSET));

        /* Copy status bits. GWDI occur when a descriptor complete RX/TX. GWEI2 occur when receive frame for full RX queue. */
        gwdi_status  = *p_gwca_gwdi_reg;
        gwei2_status = *p_gwca_gwei2_reg;

        /* Clear status bits. */
        *p_gwca_gwdi_reg  = gwdi_status;
        *p_gwca_gwei2_reg = gwei2_status;

        /* If a callback is provided, then call it with callback argument. */
        if ((NULL != p_instance_ctrl->p_callback) || port_callback_exists)
        {
            callback_arg.channel = p_instance_ctrl->p_cfg->channel;

            for (uint32_t j = 0; j < (LAYER3_SWITCH_CFG_AVAILABLE_QUEUE_NUM % LAYER3_SWITCH_REGISTER_SIZE); j++)
            {
                /* Check RX/TX complete event. */
                if (gwdi_status & (1 << j))
                {
                    /* Store index of queue. */
                    callback_arg.queue_index = j + (i * LAYER3_SWITCH_REGISTER_SIZE);
                    callback_arg.ports       =
                        p_instance_ctrl->p_queues_status[callback_arg.queue_index].p_queue_cfg->ports;

                    /* Store that the event is RX or TX. */
                    if (LAYER3_SWITCH_QUEUE_TYPE_RX ==
                        p_instance_ctrl->p_queues_status[callback_arg.queue_index].p_queue_cfg->type)
                    {
                        /* Check if queue is active. */
                        if (r_layer3_switch_is_descriptor_queue_active(p_instance_ctrl, callback_arg.queue_index))
                        {
                            callback_arg.event = ETHER_SWITCH_EVENT_RX_COMPLETE;
                        }
                        else
                        {
                            callback_arg.event = ETHER_SWITCH_EVENT_RX_QUEUE_FULL;

                            /* Clear the status bit. */
                            *p_gwca_gwdi_reg = (1 << j);
                        }
                    }
                    else
                    {
                        callback_arg.event = ETHER_SWITCH_EVENT_TX_COMPLETE;
                    }

                    r_layer3_switch_call_callback_for_ports(p_instance_ctrl, &callback_arg, callback_arg.ports);

                    /* Do not callback other event for the same queue. */
                    continue;
                }

                /* Check RX descriptor queue full error event. */
                if (gwei2_status & (1 << j))
                {
                    /* Store index of queue. */
                    callback_arg.queue_index = j + (i * LAYER3_SWITCH_REGISTER_SIZE);
                    callback_arg.ports       =
                        p_instance_ctrl->p_queues_status[callback_arg.queue_index].p_queue_cfg->ports;
                    callback_arg.event = ETHER_SWITCH_EVENT_RX_MESSAGE_LOST;

                    r_layer3_switch_call_callback_for_ports(p_instance_ctrl, &callback_arg, callback_arg.ports);
                }
            }
        }
    }

    /* Clear pending interrupt flag to make sure it doesn't fire again after exiting. */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE
}                                      /* End of function layer3_switch_gwdi_isr() */

/***********************************************************************************************************************
 * Interrupt handler for ETHA error interrupts that includes TAS error events.
 ***********************************************************************************************************************/
void layer3_switch_eaei_isr (void)
{
    /* Save context if RTOS is used. */
    FSP_CONTEXT_SAVE

    IRQn_Type irq = R_FSP_CurrentIrqGet();
    layer3_switch_instance_ctrl_t * p_instance_ctrl = (layer3_switch_instance_ctrl_t *) R_FSP_IsrContextGet(irq);
    ether_switch_callback_args_t    callback_arg    = {0};

    R_ETHA0_Type * p_etha_reg;
    uint32_t       eaei_status;

    callback_arg.channel   = p_instance_ctrl->p_cfg->channel;
    callback_arg.p_context = p_instance_ctrl->p_context;

    for (uint32_t i = 0; i < BSP_FEATURE_ETHER_NUM_CHANNELS; i++)
    {
        /* Get status register address. */
        p_etha_reg  = (R_ETHA0_Type *) (R_ETHA0_BASE + (LAYER3_SWITCH_ETHA_REG_SIZE * i));
        eaei_status = p_etha_reg->EAEIS1;

        /* Clear status register. */
        p_etha_reg->EAEIS1 = eaei_status;

        /* Check TAS gate error events. */
        if (eaei_status & (R_ETHA0_EAEIS1_TASGES0_Msk | R_ETHA0_EAEIS1_TASGES1_Msk |
                           R_ETHA0_EAEIS1_TASGES2_Msk | R_ETHA0_EAEIS1_TASGES3_Msk | R_ETHA0_EAEIS1_TASGES4_Msk |
                           R_ETHA0_EAEIS1_TASGES5_Msk | R_ETHA0_EAEIS1_TASGES6_Msk | R_ETHA0_EAEIS1_TASGES7_Msk))
        {
            /* Call callback function for the port. */
            callback_arg.ports |= (1 << i);
            callback_arg.event  = ETHER_SWITCH_EVENT_TAS_ERROR;
        }
    }

    /* Call callback of the switch. */
    if (0 != callback_arg.ports)
    {
        r_layer3_switch_call_callback(p_instance_ctrl->p_callback, &callback_arg, p_instance_ctrl->p_callback_memory);
    }

    /* Clear pending interrupt flag to make sure it doesn't fire again after exiting. */
    R_BSP_IrqStatusClear(R_FSP_CurrentIrqGet());

    /* Restore context if RTOS is used. */
    FSP_CONTEXT_RESTORE
}                                      /*  End of function layer3_switch_eaei_isr() */
