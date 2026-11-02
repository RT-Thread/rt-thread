/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @ingroup RENESAS_NETWORKING_INTERFACES
 * @defgroup ETHER_PHY_API Ethernet PHY Interface
 * @brief Interface for Ethernet PHY functions.
 *
 * @section ETHER_PHY_API_Summary Summary
 * The Ethernet PHY module (r_ether_phy) provides an API for standard Ethernet PHY communications applications that use
 * the ETHERC peripheral.
 *
 * The Ethernet PHY interface supports the following features:
 * - Auto negotiation support
 * - Flow control support
 * - Link status check support
 *
 *
 * @{
 **********************************************************************************************************************/

#ifndef R_ETHER_PHY_API_H
#define R_ETHER_PHY_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Register definitions, common services and error codes. */
#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

#ifndef BSP_OVERRIDE_ETHER_PHY_LSI_TYPE_T

/** Phy LSI */
typedef enum e_ether_phy_lsi_type
{
    ETHER_PHY_LSI_TYPE_DEFAULT    = 0,     ///< Select default configuration. This type dose not change Phy LSI default setting by strapping option.
    ETHER_PHY_LSI_TYPE_KSZ8091RNB = 1,     ///< Select configuration for KSZ8091RNB.
    ETHER_PHY_LSI_TYPE_KSZ8041    = 2,     ///< Select configuration for KSZ8041.
    ETHER_PHY_LSI_TYPE_DP83620    = 3,     ///< Select configuration for DP83620.
    ETHER_PHY_LSI_TYPE_ICS1894    = 4,     ///< Select configuration for ICS1894.
    ETHER_PHY_LSI_TYPE_GPY111     = 5,     ///< Select configuration for GPY111.
    ETHER_PHY_LSI_TYPE_CUSTOM     = 0xFFU, ///< Select configuration for User custom.
} ether_phy_lsi_type_t;
#endif

/** Flow control functionality  */
typedef enum e_ether_phy_flow_control
{
    ETHER_PHY_FLOW_CONTROL_DISABLE = 0, ///< Disable flow control functionality
    ETHER_PHY_FLOW_CONTROL_ENABLE  = 1, ///< Enable flow control functionality with pause frames
} ether_phy_flow_control_t;

/** Link speed  */
typedef enum e_ether_phy_link_speed
{
    ETHER_PHY_LINK_SPEED_NO_LINK = 0,  ///< Link is not established
    ETHER_PHY_LINK_SPEED_10H     = 1,  ///< Link status is 10Mbit/s and half duplex
    ETHER_PHY_LINK_SPEED_10F     = 2,  ///< Link status is 10Mbit/s and full duplex
    ETHER_PHY_LINK_SPEED_100H    = 3,  ///< Link status is 100Mbit/s and half duplex
    ETHER_PHY_LINK_SPEED_100F    = 4,  ///< Link status is 100Mbit/s and full duplex
    ETHER_PHY_LINK_SPEED_1000H   = 5,  ///< Link status is 1000Mbit/s and half duplex
    ETHER_PHY_LINK_SPEED_1000F   = 6   ///< Link status is 1000Mbit/s and full duplex
} ether_phy_link_speed_t;

/** Media-independent interface */
typedef enum e_ether_phy_mii_type
{
    ETHER_PHY_MII_TYPE_MII   = 0,      ///< MII
    ETHER_PHY_MII_TYPE_RMII  = 1,      ///< RMII
    ETHER_PHY_MII_TYPE_GMII  = 2,      ///< GMII
    ETHER_PHY_MII_TYPE_RGMII = 3       ///< RGMII
} ether_phy_mii_type_t;

/** Control block.  Allocate an instance specific control block to pass into the API calls.
 */
typedef void ether_phy_ctrl_t;

/** Configuration parameters. */
typedef struct st_ether_phy_cfg
{
    uint8_t channel;                               ///< Channel
    uint8_t phy_lsi_address;                       ///< DEPRECATED Address of PHY-LSI

    uint32_t             phy_reset_wait_time;      ///< Wait time for PHY-LSI reboot
    int32_t              mii_bit_access_wait_time; ///< Wait time for MII/RMII access
    ether_phy_lsi_type_t phy_lsi_type;             ///< DEPRECATED Phy LSI type

    ether_phy_flow_control_t flow_control;         ///< Flow control functionally enable or disable
    ether_phy_mii_type_t     mii_type;             ///< Interface type is MII or RMII

    /** Placeholder for user data.  Passed to the user callback in ether_phy_callback_args_t. */
    void       * p_context;
    void const * p_extend;                         ///< Placeholder for user extension.
} ether_phy_cfg_t;

/** PHY LSI configuration. */
typedef struct st_ether_phy_lsi_cfg
{
    uint8_t              address;      ///< Address of PHY-LSI
    ether_phy_lsi_type_t type;         ///< Phy LSI type
} ether_phy_lsi_cfg_t;

/** Functions implemented at the HAL layer will follow this API. */
typedef struct st_ether_phy_api
{
    /** Open driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* open)(ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg);

    /** Close driver.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* close)(ether_phy_ctrl_t * const p_ctrl);

    /** Initialize PHY-LSI.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  p_cfg        Pointer to pin configuration structure.
     */
    fsp_err_t (* chipInit)(ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg);

    /** Read register value of PHY-LSI.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  reg_addr     Register address.
     * @param[out] p_data       Pointer to the location to store read data.
     */
    fsp_err_t (* read)(ether_phy_ctrl_t * const p_ctrl, uint32_t reg_addr, uint32_t * const p_data);

    /** Write data to register of PHY-LSI.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     * @param[in]  reg_addr     Register address.
     * @param[in]  data         Data written to register.
     */
    fsp_err_t (* write)(ether_phy_ctrl_t * const p_ctrl, uint32_t reg_addr, uint32_t data);

    /** Start auto negotiation.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* startAutoNegotiate)(ether_phy_ctrl_t * const p_ctrl);

    /** Get the partner ability.
     *
     * @param[in]  p_ctrl                     Pointer to control structure.
     * @param[out] p_line_speed_duplex        Pointer to the location of both the line speed and the duplex.
     * @param[out] p_local_pause              Pointer to the location to store the local pause bits.
     * @param[out] p_partner_pause            Pointer to the location to store the partner pause bits.
     */
    fsp_err_t (* linkPartnerAbilityGet)(ether_phy_ctrl_t * const p_ctrl, uint32_t * const p_line_speed_duplex,
                                        uint32_t * const p_local_pause, uint32_t * const p_partner_pause);

    /** Get Link status from PHY-LSI interface.
     *
     * @param[in]  p_ctrl       Pointer to control structure.
     */
    fsp_err_t (* linkStatusGet)(ether_phy_ctrl_t * const p_ctrl);
} ether_phy_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_ether_phy_instance
{
    ether_phy_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    ether_phy_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    ether_phy_api_t const * p_api;     ///< Pointer to the API structure for this instance
} ether_phy_instance_t;

/*******************************************************************************************************************//**
 * @} (end defgroup ETHER_PHY_API)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 /* R_ETHER_PHY_API_H */
