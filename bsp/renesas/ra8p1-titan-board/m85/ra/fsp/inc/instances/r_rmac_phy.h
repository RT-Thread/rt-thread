/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup RMAC_PHY
 * @{
 **********************************************************************************************************************/

#ifndef R_RMAC_PHY_H
#define R_RMAC_PHY_H

#include "bsp_api.h"

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_rmac_phy_cfg.h"
#include "r_ether_phy_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Initialization state for read/write */
typedef enum e_rmac_phy_interface_status
{
    RMAC_PHY_INTERFACE_STATUS_UNINITIALIZED = 0, ///< ETHER PHY interface is uninitialized
    RMAC_PHY_INTERFACE_STATUS_INITIALIZED   = 1  ///< ETHER PHY interface is initialized
} rmac_phy_interface_status_t;

typedef enum e_rmac_phy_frame_format
{
    RMAC_PHY_FRAME_FORMAT_MDIO  = 0,   ///< Normal management frame format defined in clause 22.
    RMAC_PHY_FRAME_FORMAT_EMDIO = 1    ///< Extension management frame format defined in clause 45.
} rmac_phy_frame_format_t;

/** RMAC PHY control block. DO NOT INITIALIZE.  Initialization occurs when @ref ether_phy_api_t::open is called. */
typedef struct st_rmac_phy_instance_ctrl
{
    uint32_t                    open;             ///< Used to determine if the channel is configured
    ether_phy_cfg_t const     * p_ether_phy_cfg;  ///< Pointer to initial configurations.
    R_RMAC0_Type              * p_reg_rmac;       ///< Pointer to RMAC peripheral registers.
    uint32_t                    local_advertise;  ///< Capabilities bitmap for local advertising.
    rmac_phy_interface_status_t interface_status; ///< Initialized status of ETHER PHY interface.
    uint8_t phy_lsi_cfg_index;                    ///< Index of the PHY LSI that is currently the target of operation
} rmac_phy_instance_ctrl_t;

/** RMAC PHY extended configuration. */
typedef struct st_rmac_phy_extended_cfg
{
    void (* p_target_init)(rmac_phy_instance_ctrl_t * p_instance_ctrl);                                                 ///< Pointer to callback that is called to initialize the target.
    bool (* p_target_link_partner_ability_get)(rmac_phy_instance_ctrl_t * p_instance_ctrl, uint32_t line_speed_duplex); ///< Pointer to callback that is called to get the link partner ability.
    rmac_phy_frame_format_t     frame_format;                                                                           ///< Whether the management frame format is MDIO or eMDIO
    uint32_t                    mdc_clock_rate;                                                                         ///< MDC frequency division
    uint8_t                     mdio_hold_time;                                                                         ///< MDIO hold time adjustment
    uint8_t                     mdio_capture_time;                                                                      ///< MDIO capture time adjustment
    ether_phy_lsi_cfg_t const * p_phy_lsi_cfg_list[BSP_FEATURE_ETHER_NUM_CHANNELS];                                     ///< Pointer list of PHY LSI configurations.
    uint8_t                     default_phy_lsi_cfg_index;                                                              ///< Index of the default PHY LSI condiguration.
} rmac_phy_extended_cfg_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const ether_phy_api_t g_ether_phy_on_rmac_phy;

/** @endcond */

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

/**********************************************************************************************************************
 * Public Function Prototypes
 **********************************************************************************************************************/
fsp_err_t R_RMAC_PHY_Open(ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg);

fsp_err_t R_RMAC_PHY_Close(ether_phy_ctrl_t * const p_ctrl);

fsp_err_t R_RMAC_PHY_ChipInit(ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg);

fsp_err_t R_RMAC_PHY_Read(ether_phy_ctrl_t * const p_ctrl, uint32_t reg_addr, uint32_t * const p_data);

fsp_err_t R_RMAC_PHY_Write(ether_phy_ctrl_t * const p_ctrl, uint32_t reg_addr, uint32_t data);

fsp_err_t R_RMAC_PHY_StartAutoNegotiate(ether_phy_ctrl_t * const p_ctrl);

fsp_err_t R_RMAC_PHY_LinkPartnerAbilityGet(ether_phy_ctrl_t * const p_ctrl,
                                           uint32_t * const         p_line_speed_duplex,
                                           uint32_t * const         p_local_pause,
                                           uint32_t * const         p_partner_pause);

fsp_err_t R_RMAC_PHY_LinkStatusGet(ether_phy_ctrl_t * const p_ctrl);

fsp_err_t R_RMAC_PHY_ChipSelect(ether_phy_ctrl_t * const p_ctrl, uint8_t port);

/*******************************************************************************************************************//**
 * @} (end addtogroup RMAC_PHY)
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif                                 // R_RMAC_PHY_H
