/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

/* Access to peripherals and board defines. */
#include "bsp_api.h"
#include "r_rmac_phy.h"

/***********************************************************************************************************************
 * Macro definitions
 ***********************************************************************************************************************/
#ifndef RMAC_PHY_ERROR_RETURN
 #define RMAC_PHY_ERROR_RETURN(a, err)    FSP_ERROR_RETURN((a), (err))
#endif

#define RMAC_REG_SIZE                          (R_RMAC1_BASE - R_RMAC0_BASE)
#define ETHA_REG_SIZE                          (R_ETHA1_BASE - R_ETHA0_BASE)

/** "RPHY" in ASCII.  Used to determine if the control block is open. */
#define RMAC_PHY_OPEN                          (('R' << 24U) | ('P' << 16U) | ('H' << 8U) | ('Y' << 0U))

/* Standard PHY Registers */
#define RMAC_PHY_REG_CONTROL                   (0)
#define RMAC_PHY_REG_STATUS                    (1)
#define RMAC_PHY_REG_IDENTIFIER1               (2)
#define RMAC_PHY_REG_IDENTIFIER2               (3)
#define RMAC_PHY_REG_AN_ADVERTISEMENT          (4)
#define RMAC_PHY_REG_AN_LINK_PARTNER           (5)
#define RMAC_PHY_REG_AN_EXPANSION              (6)
#define RMAC_PHY_REG_GIGABIT_CONTROL           (9)
#define RMAC_PHY_REG_GIGABIT_STATUS            (10)

/* Basic Mode Control Register Bit Definitions */
#define RMAC_PHY_CONTROL_RESET                 (1 << 15)
#define RMAC_PHY_CONTROL_LOOPBACK              (1 << 14)
#define RMAC_PHY_CONTROL_100_MBPS              (1 << 13)
#define RMAC_PHY_CONTROL_AN_ENABLE             (1 << 12)
#define RMAC_PHY_CONTROL_POWER_DOWN            (1 << 11)
#define RMAC_PHY_CONTROL_ISOLATE               (1 << 10)
#define RMAC_PHY_CONTROL_AN_RESTART            (1 << 9)
#define RMAC_PHY_CONTROL_FULL_DUPLEX           (1 << 8)
#define RMAC_PHY_CONTROL_COLLISION             (1 << 7)

/* Basic Mode Status Register Bit Definitions */
#define RMAC_PHY_STATUS_100_T4                 (1 << 15)
#define RMAC_PHY_STATUS_100F                   (1 << 14)
#define RMAC_PHY_STATUS_100H                   (1 << 13)
#define RMAC_PHY_STATUS_10F                    (1 << 12)
#define RMAC_PHY_STATUS_10H                    (1 << 11)
#define RMAC_PHY_STATUS_AN_COMPLETE            (1 << 5)
#define RMAC_PHY_STATUS_RM_FAULT               (1 << 4)
#define RMAC_PHY_STATUS_AN_ABILITY             (1 << 3)
#define RMAC_PHY_STATUS_LINK_UP                (1 << 2)
#define RMAC_PHY_STATUS_JABBER                 (1 << 1)
#define RMAC_PHY_STATUS_EX_CAPABILITY          (1 << 0)

/* Auto Negotiation Advertisement Bit Definitions */
#define RMAC_PHY_AN_ADVERTISEMENT_NEXT_PAGE    (1 << 15)
#define RMAC_PHY_AN_ADVERTISEMENT_RM_FAULT     (1 << 13)
#define RMAC_PHY_AN_ADVERTISEMENT_ASM_DIR      (1 << 11)
#define RMAC_PHY_AN_ADVERTISEMENT_PAUSE        (1 << 10)
#define RMAC_PHY_AN_ADVERTISEMENT_100_T4       (1 << 9)
#define RMAC_PHY_AN_ADVERTISEMENT_100F         (1 << 8)
#define RMAC_PHY_AN_ADVERTISEMENT_100H         (1 << 7)
#define RMAC_PHY_AN_ADVERTISEMENT_10F          (1 << 6)
#define RMAC_PHY_AN_ADVERTISEMENT_10H          (1 << 5)
#define RMAC_PHY_AN_ADVERTISEMENT_SELECTOR     (1 << 0)

/* Auto Negotiate Link Partner Ability Bit Definitions */
#define RMAC_PHY_AN_LINK_PARTNER_NEXT_PAGE     (1 << 15)
#define RMAC_PHY_AN_LINK_PARTNER_ACK           (1 << 14)
#define RMAC_PHY_AN_LINK_PARTNER_RM_FAULT      (1 << 13)
#define RMAC_PHY_AN_LINK_PARTNER_ASM_DIR       (1 << 11)
#define RMAC_PHY_AN_LINK_PARTNER_PAUSE         (1 << 10)
#define RMAC_PHY_AN_LINK_PARTNER_100_T4        (1 << 9)
#define RMAC_PHY_AN_LINK_PARTNER_100F          (1 << 8)
#define RMAC_PHY_AN_LINK_PARTNER_100H          (1 << 7)
#define RMAC_PHY_AN_LINK_PARTNER_10F           (1 << 6)
#define RMAC_PHY_AN_LINK_PARTNER_10H           (1 << 5)
#define RMAC_PHY_AN_LINK_PARTNER_SELECTOR      (1 << 0)

/* Gigabit Control Bit Definitions */
#define RMAC_PHY_GIGABIT_CONTROL_1000F         (1 << 9)
#define RMAC_PHY_GIGABIT_CONTROL_1000H         (1 << 8)

/* Gigabit Status Bit Definitions. LP stands for Link Partner. */
#define RMAC_PHY_GIGABIT_STATUS_LP_1000H       (1 << 10)
#define RMAC_PHY_GIGABIT_STATUS_LP_1000F       (1 << 11)

#define RMAC_PHY_ADDRESS_SIZE                  (0x1fU)
#define RMAC_PHY_REGISTER_DATA_SIZE            (0xffffU)

/* MDIO frame OP code */
#define RMAC_PHY_MDIO_OPCODE_WRITE             (0x1)
#define RMAC_PHY_MDIO_OPCODE_READ              (0x2)

/* eMDIO frame OP code */
#define RMAC_PHY_EMDIO_OPCODE_ADDRESS          (0x0)
#define RMAC_PHY_EMDIO_OPCODE_WRITE            (0x1)
#define RMAC_PHY_EMDIO_OPCODE_READ             (0x3)
#define RMAC_PHY_EMDIO_OPCODE_POST_READ        (0x2)

/* Operation mode of ETHA*/
#define RMAC_PHY_ETHA_CONFIG_MODE              (0b10)
#define RMAC_PHY_ETHA_OPERATION_MODE           (0b11)
#define RMAC_PHY_ETHA_DISABLE_MODE             (0b01)

/***********************************************************************************************************************
 * Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global function
 ***********************************************************************************************************************/
#if (ETHER_PHY_CFG_TARGET_KSZ8091RNB_ENABLE)
extern void rmac_phy_target_ksz8091rnb_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
extern bool rmac_phy_target_ksz8091rnb_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                                       uint32_t                   line_speed_duplex);

#endif
#if (ETHER_PHY_CFG_TARGET_KSZ8041_ENABLE)
extern void rmac_phy_target_ksz8041_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
extern bool rmac_phy_target_ksz8041_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                                    uint32_t                   line_speed_duplex);

#endif
#if (ETHER_PHY_CFG_TARGET_DP83620_ENABLE)
extern void rmac_phy_target_dp83620_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
extern bool rmac_phy_target_dp83620_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                                    uint32_t                   line_speed_duplex);

#endif
#if (ETHER_PHY_CFG_TARGET_ICS1894_ENABLE)
extern void rmac_phy_target_ics1894_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
extern bool rmac_phy_target_ics1894_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                                    uint32_t                   line_speed_duplex);

#endif

#if (ETHER_PHY_CFG_TARGET_GPY111_ENABLE)
extern void rmac_phy_target_gpy111_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
extern bool rmac_phy_target_gpy111_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                                   uint32_t                   line_speed_duplex);

#endif

/***********************************************************************************************************************
 * Private global variables and functions
 ***********************************************************************************************************************/
static void rmac_phy_targets_initialize(rmac_phy_instance_ctrl_t * p_instance_ctrl);
static bool rmac_phy_targets_is_support_link_partner_ability(rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                             uint32_t                   line_speed_duplex);
static uint32_t r_rmac_phy_calculate_mpic(rmac_phy_instance_ctrl_t * p_instance_ctrl, uint32_t line_speed_duplex);
static uint8_t  r_rmac_phy_get_operation_mode(rmac_phy_instance_ctrl_t * p_instance_ctrl);
static void     r_rmac_phy_set_operation_mode(uint8_t channel, uint8_t mode);
static void     r_rmac_phy_set_mii_type_configuration(rmac_phy_instance_ctrl_t * p_instance_ctrl, uint8_t port);

/** RMAC_PHY HAL API mapping for Ethernet PHY Controller interface */
/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const ether_phy_api_t g_ether_phy_on_rmac_phy =
{
    .open                  = R_RMAC_PHY_Open,
    .close                 = R_RMAC_PHY_Close,
    .startAutoNegotiate    = R_RMAC_PHY_StartAutoNegotiate,
    .linkPartnerAbilityGet = R_RMAC_PHY_LinkPartnerAbilityGet,
    .linkStatusGet         = R_RMAC_PHY_LinkStatusGet,
    .chipInit              = R_RMAC_PHY_ChipInit,
    .read                  = R_RMAC_PHY_Read,
    .write                 = R_RMAC_PHY_Write
};

/*******************************************************************************************************************//**
 * @addtogroup RMAC_PHY
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/********************************************************************************************************************//**
 * @brief Resets Ethernet PHY device. Implements @ref ether_phy_api_t::open.
 *
 * @retval  FSP_SUCCESS                             Channel opened successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to RMAC_PHY control block is NULL.
 * @retval  FSP_ERR_ALREADY_OPEN                    Control block has already been opened or channel is being used by another
 *                                                  instance. Call close() then open() to reconfigure.
 * @retval  FSP_ERR_INVALID_CHANNEL                 Invalid channel number is given.
 * @retval  FSP_ERR_INVALID_POINTER                 Pointer to p_cfg is NULL.
 * @retval  FSP_ERR_INVALID_MODE                    Function is called when not in CONFIG mode.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_PHY_Open (ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rmac_phy_instance_ctrl_t * p_instance_ctrl = (rmac_phy_instance_ctrl_t *) p_ctrl;
    rmac_phy_extended_cfg_t  * p_extend;
    uint32_t       link_speed = ETHER_PHY_LINK_SPEED_10F;
    R_RMAC0_Type * p_reg_rmac;

#if (RMAC_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    RMAC_PHY_ERROR_RETURN(NULL != p_cfg, FSP_ERR_INVALID_POINTER);
    RMAC_PHY_ERROR_RETURN((RMAC_PHY_OPEN != p_instance_ctrl->open), FSP_ERR_ALREADY_OPEN);
    RMAC_PHY_ERROR_RETURN((BSP_FEATURE_ETHER_NUM_CHANNELS > p_cfg->channel), FSP_ERR_INVALID_CHANNEL);
    p_extend = (rmac_phy_extended_cfg_t *) p_cfg->p_extend;
    RMAC_PHY_ERROR_RETURN(NULL != p_extend, FSP_ERR_INVALID_POINTER);
    RMAC_PHY_ERROR_RETURN(NULL != p_extend->p_phy_lsi_cfg_list[p_extend->default_phy_lsi_cfg_index],
                          FSP_ERR_INVALID_ARGUMENT);
#else
    p_extend = (rmac_phy_extended_cfg_t *) p_cfg->p_extend;
#endif

    /* Initialize configuration of ethernet phy module. */
    p_instance_ctrl->p_ether_phy_cfg = p_cfg;

    /* ETHA IP should be CONFIG mode */
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_ETHA_CONFIG_MODE == r_rmac_phy_get_operation_mode(p_instance_ctrl),
                          FSP_ERR_INVALID_MODE);

    /* Set the RMAC register address of this channel. */
    p_instance_ctrl->p_reg_rmac      = (R_RMAC0_Type *) (R_RMAC0_BASE + (RMAC_REG_SIZE * p_cfg->channel));
    p_instance_ctrl->local_advertise = 0;

    /* Copy default PHY LSI settings. */
    p_instance_ctrl->phy_lsi_cfg_index = p_extend->default_phy_lsi_cfg_index;

    /* Configure maximum link speed for each interface. */
    if ((ETHER_PHY_MII_TYPE_MII == p_instance_ctrl->p_ether_phy_cfg->mii_type) ||
        (ETHER_PHY_MII_TYPE_RMII == p_instance_ctrl->p_ether_phy_cfg->mii_type))
    {
        link_speed = ETHER_PHY_LINK_SPEED_100F;
    }
    else if ((ETHER_PHY_MII_TYPE_GMII == p_instance_ctrl->p_ether_phy_cfg->mii_type) ||
             (ETHER_PHY_MII_TYPE_RGMII == p_instance_ctrl->p_ether_phy_cfg->mii_type))
    {
        link_speed = ETHER_PHY_LINK_SPEED_1000F;
    }
    else
    {
        ;
    }

    /* Configure PHY interface for each available channels. */
    for (uint32_t i = 0; i < BSP_FEATURE_ETHER_NUM_CHANNELS; i++)
    {
        if (NULL != p_extend->p_phy_lsi_cfg_list[i])
        {
            p_reg_rmac       = (R_RMAC0_Type *) (R_RMAC0_BASE + (RMAC_REG_SIZE * i));
            p_reg_rmac->MPIC = r_rmac_phy_calculate_mpic(p_instance_ctrl, link_speed);
        }
    }

    p_instance_ctrl->open = RMAC_PHY_OPEN;

    return err;
}                                      /* End of function R_RMAC_PHY_Open() */

/********************************************************************************************************************//**
 * @brief Close Ethernet PHY device. Implements @ref ether_phy_api_t::close.
 *
 * @retval  FSP_SUCCESS                                 Channel successfully closed.
 * @retval  FSP_ERR_ASSERTION                           Pointer to RMAC_PHY control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 * @retval  FSP_ERR_INVALID_MODE                        Function is called when not in DISABLE mode.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_PHY_Close (ether_phy_ctrl_t * const p_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    rmac_phy_instance_ctrl_t * p_instance_ctrl = (rmac_phy_instance_ctrl_t *) p_ctrl;

#if (RMAC_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* ETHA IP should be DISABLE mode */
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_ETHA_DISABLE_MODE == r_rmac_phy_get_operation_mode(p_instance_ctrl),
                          FSP_ERR_INVALID_MODE);

    /** Clear configure block parameters. */
    p_instance_ctrl->p_ether_phy_cfg = NULL;
    p_instance_ctrl->local_advertise = 0;
    p_instance_ctrl->p_reg_rmac      = NULL;

    p_instance_ctrl->interface_status = RMAC_PHY_INTERFACE_STATUS_UNINITIALIZED;
    p_instance_ctrl->open             = 0;

    return err;
}                                      /* End of function R_RMAC_PHY_Close() */

/********************************************************************************************************************//**
 * @brief Starts auto-negotiate. Implements @ref ether_phy_api_t::startAutoNegotiate.
 *
 * @retval  FSP_SUCCESS                                 RMAC_PHY successfully starts auto-negotiate.
 * @retval  FSP_ERR_ASSERTION                           Pointer to RMAC_PHY control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 * @retval  FSP_ERR_NOT_INITIALIZED                     The control block has not been initialized
 * @retval  FSP_ERR_INVALID_MODE                        Function is called when not in OPERATION mode.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_PHY_StartAutoNegotiate (ether_phy_ctrl_t * const p_ctrl)
{
    rmac_phy_instance_ctrl_t * p_instance_ctrl = (rmac_phy_instance_ctrl_t *) p_ctrl;
    uint32_t reg = 0;

#if (RMAC_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_INTERFACE_STATUS_INITIALIZED == p_instance_ctrl->interface_status,
                          FSP_ERR_NOT_INITIALIZED);
#endif

    /* ETHA IP should be OPERATION mode */
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_ETHA_OPERATION_MODE == r_rmac_phy_get_operation_mode(p_instance_ctrl),
                          FSP_ERR_INVALID_MODE);

    /* Set local ability */
    /* When pause frame is not used */
    if (ETHER_PHY_FLOW_CONTROL_DISABLE == p_instance_ctrl->p_ether_phy_cfg->flow_control)
    {
        p_instance_ctrl->local_advertise = ((((RMAC_PHY_AN_ADVERTISEMENT_100F |
                                               RMAC_PHY_AN_ADVERTISEMENT_100H) |
                                              RMAC_PHY_AN_ADVERTISEMENT_10F) |
                                             RMAC_PHY_AN_ADVERTISEMENT_10H) |
                                            RMAC_PHY_AN_ADVERTISEMENT_SELECTOR);
    }
    /* When pause frame is used */
    else
    {
        p_instance_ctrl->local_advertise = ((((((RMAC_PHY_AN_ADVERTISEMENT_ASM_DIR |
                                                 RMAC_PHY_AN_ADVERTISEMENT_PAUSE) |
                                                RMAC_PHY_AN_ADVERTISEMENT_100F) |
                                               RMAC_PHY_AN_ADVERTISEMENT_100H) |
                                              RMAC_PHY_AN_ADVERTISEMENT_10F) |
                                             RMAC_PHY_AN_ADVERTISEMENT_10H) |
                                            RMAC_PHY_AN_ADVERTISEMENT_SELECTOR);
    }

    /* Configure what the PHY and the Ethernet controller on this board supports */
    R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_AN_ADVERTISEMENT, p_instance_ctrl->local_advertise);

    /* Advertise Gigabit Ethernet capacity when using RGMII or GMII. */
    if ((ETHER_PHY_MII_TYPE_RGMII == p_instance_ctrl->p_ether_phy_cfg->mii_type) ||
        (ETHER_PHY_MII_TYPE_GMII == p_instance_ctrl->p_ether_phy_cfg->mii_type))
    {
        R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_GIGABIT_CONTROL,
                         (RMAC_PHY_GIGABIT_CONTROL_1000F | RMAC_PHY_GIGABIT_CONTROL_1000H));
    }

    /* Start auto-negotiation. */
    R_RMAC_PHY_Write(p_instance_ctrl,
                     RMAC_PHY_REG_CONTROL,
                     (RMAC_PHY_CONTROL_AN_ENABLE |
                      RMAC_PHY_CONTROL_AN_RESTART));

    R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_AN_ADVERTISEMENT, &reg);

    return FSP_SUCCESS;
}                                      /* End of function R_RMAC_PHY_StartAutoNegotiate() */

/********************************************************************************************************************//**
 * @brief Reports the other side's physical capability. Implements @ref ether_phy_api_t::linkPartnerAbilityGet.
 *
 * @retval  FSP_SUCCESS                                 RMAC_PHY successfully get link partner ability.
 * @retval  FSP_ERR_ASSERTION                           Pointer to RMAC_PHY control block is NULL.
 * @retval  FSP_ERR_INVALID_POINTER                     Pointer to arguments are NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK                PHY-LSI is not link up.
 * @retval  FSP_ERR_ETHER_PHY_NOT_READY                 The auto-negotiation isn't completed
 * @retval  FSP_ERR_NOT_INITIALIZED                     The control block has not been initialized
 * @retval  FSP_ERR_INVALID_MODE                        Function is called when not in OPERATION mode.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_PHY_LinkPartnerAbilityGet (ether_phy_ctrl_t * const p_ctrl,
                                            uint32_t * const         p_line_speed_duplex,
                                            uint32_t * const         p_local_pause,
                                            uint32_t * const         p_partner_pause)
{
    fsp_err_t err = FSP_SUCCESS;
    rmac_phy_instance_ctrl_t * p_instance_ctrl = (rmac_phy_instance_ctrl_t *) p_ctrl;
    uint32_t       reg               = 0;
    uint32_t       line_speed_duplex = ETHER_PHY_LINK_SPEED_NO_LINK;
    uint32_t       mpic;
    R_RMAC0_Type * p_reg_rmac;

#if (RMAC_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    RMAC_PHY_ERROR_RETURN(NULL != p_line_speed_duplex, FSP_ERR_INVALID_POINTER);
    RMAC_PHY_ERROR_RETURN(NULL != p_local_pause, FSP_ERR_INVALID_POINTER);
    RMAC_PHY_ERROR_RETURN(NULL != p_partner_pause, FSP_ERR_INVALID_POINTER);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_INTERFACE_STATUS_INITIALIZED == p_instance_ctrl->interface_status,
                          FSP_ERR_NOT_INITIALIZED);
#endif

    /* ETHA IP should be OPERATION mode */
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_ETHA_OPERATION_MODE == r_rmac_phy_get_operation_mode(p_instance_ctrl),
                          FSP_ERR_INVALID_MODE);

    /* Because reading the first time shows the previous state, the Link status bit is read twice. */
    R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_STATUS, &reg);
    R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_STATUS, &reg);

    /* When the link isn't up, return error */
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_STATUS_LINK_UP == (reg & RMAC_PHY_STATUS_LINK_UP), FSP_ERR_ETHER_PHY_ERROR_LINK);

    /* Establish local pause capability */
    if (RMAC_PHY_AN_ADVERTISEMENT_PAUSE == (p_instance_ctrl->local_advertise & RMAC_PHY_AN_ADVERTISEMENT_PAUSE))
    {
        (*p_local_pause) |= (1 << 1);
    }

    if (RMAC_PHY_AN_ADVERTISEMENT_ASM_DIR == (p_instance_ctrl->local_advertise & RMAC_PHY_AN_ADVERTISEMENT_ASM_DIR))
    {
        (*p_local_pause) |= 1;
    }

    /* When the auto-negotiation isn't completed, return error */
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_STATUS_AN_COMPLETE == (reg & RMAC_PHY_STATUS_AN_COMPLETE),
                          FSP_ERR_ETHER_PHY_NOT_READY);

    /* Get the link partner response */
    R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_AN_LINK_PARTNER, &reg);

    /* Establish partner pause capability */
    if (RMAC_PHY_AN_LINK_PARTNER_PAUSE == (reg & RMAC_PHY_AN_LINK_PARTNER_PAUSE))
    {
        (*p_partner_pause) = (1 << 1);
    }

    if (RMAC_PHY_AN_LINK_PARTNER_ASM_DIR == (reg & RMAC_PHY_AN_LINK_PARTNER_ASM_DIR))
    {
        (*p_partner_pause) |= 1;
    }

    /* Establish the line speed and the duplex */
    if ((RMAC_PHY_AN_LINK_PARTNER_10H == (reg & RMAC_PHY_AN_LINK_PARTNER_10H)) &&
        rmac_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_10H))
    {
        line_speed_duplex = ETHER_PHY_LINK_SPEED_10H;
    }

    if ((RMAC_PHY_AN_LINK_PARTNER_10F == (reg & RMAC_PHY_AN_LINK_PARTNER_10F)) &&
        rmac_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_10F))
    {
        line_speed_duplex = ETHER_PHY_LINK_SPEED_10F;
    }

    if ((RMAC_PHY_AN_LINK_PARTNER_100H == (reg & RMAC_PHY_AN_LINK_PARTNER_100H)) &&
        rmac_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_100H))
    {
        line_speed_duplex = ETHER_PHY_LINK_SPEED_100H;
    }

    if ((RMAC_PHY_AN_LINK_PARTNER_100F == (reg & RMAC_PHY_AN_LINK_PARTNER_100F)) &&
        rmac_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_100F))
    {
        line_speed_duplex = ETHER_PHY_LINK_SPEED_100F;
    }

    /* When MII type is RGMII, check also Gigabit Ethernet ability. */
    if ((ETHER_PHY_MII_TYPE_RGMII == p_instance_ctrl->p_ether_phy_cfg->mii_type) ||
        (ETHER_PHY_MII_TYPE_GMII == p_instance_ctrl->p_ether_phy_cfg->mii_type))
    {
        R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_GIGABIT_STATUS, &reg);

        if ((RMAC_PHY_GIGABIT_STATUS_LP_1000H == (reg & RMAC_PHY_GIGABIT_STATUS_LP_1000H)) &&
            rmac_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_1000H))
        {
            line_speed_duplex = ETHER_PHY_LINK_SPEED_1000H;
        }

        if ((RMAC_PHY_GIGABIT_STATUS_LP_1000F == (reg & RMAC_PHY_GIGABIT_STATUS_LP_1000F)) &&
            rmac_phy_targets_is_support_link_partner_ability(p_instance_ctrl, ETHER_PHY_LINK_SPEED_1000F))
        {
            line_speed_duplex = ETHER_PHY_LINK_SPEED_1000F;
        }
    }

    if (ETHER_PHY_LINK_SPEED_NO_LINK == line_speed_duplex)
    {
        err = FSP_ERR_ETHER_PHY_ERROR_LINK;
    }
    else
    {
        (*p_line_speed_duplex) = line_speed_duplex;
    }

    mpic       = r_rmac_phy_calculate_mpic(p_instance_ctrl, line_speed_duplex);
    p_reg_rmac = (R_RMAC0_Type *) (R_RMAC0_BASE + (RMAC_REG_SIZE * p_instance_ctrl->phy_lsi_cfg_index));
    if (mpic != p_reg_rmac->MPIC)
    {
        /* Set ETHA to CONFIG mode */
        r_rmac_phy_set_operation_mode(p_instance_ctrl->phy_lsi_cfg_index, RMAC_PHY_ETHA_DISABLE_MODE);
        r_rmac_phy_set_operation_mode(p_instance_ctrl->phy_lsi_cfg_index, RMAC_PHY_ETHA_CONFIG_MODE);

        p_reg_rmac->MPIC = mpic;

        /* Set ETHA to OPERATION mode */
        r_rmac_phy_set_operation_mode(p_instance_ctrl->phy_lsi_cfg_index, RMAC_PHY_ETHA_DISABLE_MODE);
        r_rmac_phy_set_operation_mode(p_instance_ctrl->phy_lsi_cfg_index, RMAC_PHY_ETHA_OPERATION_MODE);
    }

    return err;
}                                      /* End of function R_RMAC_PHY_LinkPartnerAbilityGet() */

/********************************************************************************************************************//**
 * @brief Returns the status of the physical link. Implements @ref ether_phy_api_t::linkStatusGet.
 *
 * @retval  FSP_SUCCESS                                 RMAC_PHY successfully get link partner ability.
 * @retval  FSP_ERR_ASSERTION                           Pointer to RMAC_PHY control block is NULL.
 * @retval  FSP_ERR_NOT_OPEN                            The control block has not been opened
 * @retval  FSP_ERR_ETHER_PHY_ERROR_LINK                PHY-LSI is not link up.
 * @retval  FSP_ERR_NOT_INITIALIZED                     The control block has not been initialized
 * @retval  FSP_ERR_INVALID_MODE                        Function is called when not in OPERATION mode.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_PHY_LinkStatusGet (ether_phy_ctrl_t * const p_ctrl)
{
    rmac_phy_instance_ctrl_t * p_instance_ctrl = (rmac_phy_instance_ctrl_t *) p_ctrl;
    uint32_t  reg = 0;
    fsp_err_t err = FSP_SUCCESS;

#if (RMAC_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_INTERFACE_STATUS_INITIALIZED == p_instance_ctrl->interface_status,
                          FSP_ERR_NOT_INITIALIZED);
#endif

    /* ETHA IP should be OPERATION mode */
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_ETHA_OPERATION_MODE == r_rmac_phy_get_operation_mode(p_instance_ctrl),
                          FSP_ERR_INVALID_MODE);

    /* Because reading the first time shows the previous state, the Link status bit is read twice. */
    R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_STATUS, &reg);
    R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_STATUS, &reg);

    /* When the link isn't up, return error */
    if (RMAC_PHY_STATUS_LINK_UP != (reg & RMAC_PHY_STATUS_LINK_UP))
    {
        /* Link is down */
        err = FSP_ERR_ETHER_PHY_ERROR_LINK;
    }
    else
    {
        /* Link is up */
        err = FSP_SUCCESS;
    }

    return err;
}                                      /* End of function R_RMAC_PHY_LinkStatusGet() */

/********************************************************************************************************************//**
 * @brief Initialize Ethernet PHY device. Implements @ref ether_phy_api_t::chipInit.
 *
 * @retval  FSP_SUCCESS                             PHY device initialized successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to RMAC_PHY control block or configuration structure is NULL.
 * @retval  FSP_ERR_NOT_OPEN                        The control block has not been opened.
 * @retval  FSP_ERR_TIMEOUT                         PHY-LSI Reset wait timeout.
 * @retval  FSP_ERR_INVALID_MODE                    Function is called when not in OPERATION mode.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_PHY_ChipInit (ether_phy_ctrl_t * const p_ctrl, ether_phy_cfg_t const * const p_cfg)
{
    fsp_err_t err = FSP_SUCCESS;
    rmac_phy_instance_ctrl_t * p_instance_ctrl = (rmac_phy_instance_ctrl_t *) p_ctrl;
    uint32_t reg   = 0;
    uint32_t count = 0;

#if (RMAC_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    RMAC_PHY_ERROR_RETURN(NULL != p_cfg, FSP_ERR_INVALID_POINTER);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
#endif

    /* ETHA IP should be OPERATION mode */
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_ETHA_OPERATION_MODE == r_rmac_phy_get_operation_mode(p_instance_ctrl),
                          FSP_ERR_INVALID_MODE);

    /* Set MII type configuration for this PHY LSI port. */
    r_rmac_phy_set_mii_type_configuration(p_instance_ctrl, p_instance_ctrl->phy_lsi_cfg_index);

    p_instance_ctrl->interface_status = RMAC_PHY_INTERFACE_STATUS_INITIALIZED;

    /* Reset PHY */
    R_RMAC_PHY_Write(p_instance_ctrl, RMAC_PHY_REG_CONTROL, RMAC_PHY_CONTROL_RESET);

    /* Reset completion waiting */
    do
    {
        R_RMAC_PHY_Read(p_instance_ctrl, RMAC_PHY_REG_CONTROL, &reg);
        count++;
    } while ((reg & RMAC_PHY_CONTROL_RESET) && (count < p_cfg->phy_reset_wait_time));

    if (count < p_cfg->phy_reset_wait_time)
    {
        rmac_phy_targets_initialize(p_instance_ctrl);
    }
    else
    {
        err = FSP_ERR_TIMEOUT;
    }

    return err;
}                                      /* End of function R_RMAC_PHY_ChipInit() */

/********************************************************************************************************************//**
 * @brief Read data from register of PHY-LSI . Implements @ref ether_phy_api_t::read.
 *
 * @retval  FSP_SUCCESS                                 RMAC_PHY successfully read data.
 * @retval  FSP_ERR_ASSERTION                           Pointer to RMAC_PHY control block is NULL.
 * @retval  FSP_ERR_INVALID_POINTER                     Pointer to read buffer is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Address is not a valid size
 * @retval  FSP_ERR_NOT_INITIALIZED                     The control block has not been initialized
 * @retval  FSP_ERR_INVALID_MODE                        Function is called when not in OPERATION mode.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_PHY_Read (ether_phy_ctrl_t * const p_ctrl, uint32_t reg_addr, uint32_t * const p_data)
{
    rmac_phy_instance_ctrl_t * p_instance_ctrl = (rmac_phy_instance_ctrl_t *) p_ctrl;
    uint32_t mpsm = 0;
    rmac_phy_extended_cfg_t * p_extend;

#if (RMAC_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    RMAC_PHY_ERROR_RETURN(NULL != p_data, FSP_ERR_INVALID_POINTER);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_ADDRESS_SIZE >= reg_addr, FSP_ERR_INVALID_ARGUMENT);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_INTERFACE_STATUS_INITIALIZED == p_instance_ctrl->interface_status,
                          FSP_ERR_NOT_INITIALIZED);
#endif
    p_extend = (rmac_phy_extended_cfg_t *) p_instance_ctrl->p_ether_phy_cfg->p_extend;

    /*  Create configuration value to read phy register. */
    mpsm |= R_RMAC0_MPSM_POP_Msk & (RMAC_PHY_MDIO_OPCODE_READ << R_RMAC0_MPSM_POP_Pos);
    mpsm |= R_RMAC0_MPSM_PDA_Msk &
            ((uint32_t) p_extend->p_phy_lsi_cfg_list[p_instance_ctrl->phy_lsi_cfg_index]->address <<
             R_RMAC0_MPSM_PDA_Pos);
    mpsm |= R_RMAC0_MPSM_PRA_Msk & (reg_addr << R_RMAC0_MPSM_PRA_Pos);

    /* Set configuration value. */
    p_instance_ctrl->p_reg_rmac->MPSM = mpsm;

    /* Start read access to the phy register and wait for completion. */
    p_instance_ctrl->p_reg_rmac->MPSM_b.PSME = 1;
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg_rmac->MPSM_b.PSME, 0);

    /* Copy register value. */
    *p_data = p_instance_ctrl->p_reg_rmac->MPSM_b.PRD;

    return FSP_SUCCESS;
}                                      /* End of function R_RMAC_PHY_Read() */

/********************************************************************************************************************//**
 * @brief Write data to register of PHY-LSI . Implements @ref ether_phy_api_t::write.
 *
 * @retval  FSP_SUCCESS                                 RMAC_PHY successfully write data.
 * @retval  FSP_ERR_ASSERTION                           Pointer to RMAC_PHY control block is NULL.
 * @retval  FSP_ERR_INVALID_ARGUMENT                    Address or data is not a valid size
 * @retval  FSP_ERR_NOT_INITIALIZED                     The control block has not been initialized
 * @retval  FSP_ERR_INVALID_MODE                        Function is called when not in OPERATION mode.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_PHY_Write (ether_phy_ctrl_t * const p_ctrl, uint32_t reg_addr, uint32_t data)
{
    rmac_phy_instance_ctrl_t * p_instance_ctrl = (rmac_phy_instance_ctrl_t *) p_ctrl;
    uint32_t mpsm = 0;
    rmac_phy_extended_cfg_t * p_extend;

#if (RMAC_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_ADDRESS_SIZE >= reg_addr, FSP_ERR_INVALID_ARGUMENT);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_REGISTER_DATA_SIZE >= data, FSP_ERR_INVALID_ARGUMENT);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_INTERFACE_STATUS_INITIALIZED == p_instance_ctrl->interface_status,
                          FSP_ERR_NOT_INITIALIZED);
#endif
    p_extend = (rmac_phy_extended_cfg_t *) p_instance_ctrl->p_ether_phy_cfg->p_extend;

    /* ETHA IP should be OPERATION mode */
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_ETHA_OPERATION_MODE == r_rmac_phy_get_operation_mode(p_instance_ctrl),
                          FSP_ERR_INVALID_MODE);

    /*  Create configuration value to write phy register. */
    mpsm |= R_RMAC0_MPSM_POP_Msk & (RMAC_PHY_MDIO_OPCODE_WRITE << R_RMAC0_MPSM_POP_Pos);
    mpsm |= R_RMAC0_MPSM_PDA_Msk &
            ((uint32_t) p_extend->p_phy_lsi_cfg_list[p_instance_ctrl->phy_lsi_cfg_index]->address <<
             R_RMAC0_MPSM_PDA_Pos);
    mpsm |= R_RMAC0_MPSM_PRA_Msk & (reg_addr << R_RMAC0_MPSM_PRA_Pos);
    mpsm |= R_RMAC0_MPSM_PRD_Msk & (data << R_RMAC0_MPSM_PRD_Pos);

    /* Set configuration value. */
    p_instance_ctrl->p_reg_rmac->MPSM = mpsm;

    /* Start write access to the phy register and wait for completion. */
    p_instance_ctrl->p_reg_rmac->MPSM_b.PSME = 1;
    FSP_HARDWARE_REGISTER_WAIT(p_instance_ctrl->p_reg_rmac->MPSM_b.PSME, 0);

    return FSP_SUCCESS;
}                                      /* End of function R_RMAC_PHY_Write() */

/********************************************************************************************************************//**
 * @brief Update the target PHY LSI of this driver.
 *
 * @retval  FSP_SUCCESS                             PHY device initialized successfully.
 * @retval  FSP_ERR_ASSERTION                       Pointer to RMAC_PHY control block or configuration structure is NULL.
 * @retval  FSP_ERR_NOT_OPEN                        The control block has not been opened.
 * @retval  FSP_ERR_INVALID_ARGUMENT                Invalid PHY LSI is selected.
 ***********************************************************************************************************************/
fsp_err_t R_RMAC_PHY_ChipSelect (ether_phy_ctrl_t * const p_ctrl, uint8_t port)
{
    rmac_phy_instance_ctrl_t * p_instance_ctrl = (rmac_phy_instance_ctrl_t *) p_ctrl;
    rmac_phy_extended_cfg_t  * p_extend;
#if (RMAC_PHY_CFG_PARAM_CHECKING_ENABLE)
    FSP_ASSERT(NULL != p_instance_ctrl);
    RMAC_PHY_ERROR_RETURN(RMAC_PHY_OPEN == p_instance_ctrl->open, FSP_ERR_NOT_OPEN);
    RMAC_PHY_ERROR_RETURN(BSP_FEATURE_ETHER_NUM_CHANNELS > port, FSP_ERR_INVALID_ARGUMENT);
#endif
    p_extend = (rmac_phy_extended_cfg_t *) p_instance_ctrl->p_ether_phy_cfg->p_extend;
    FSP_ERROR_RETURN(NULL != p_extend->p_phy_lsi_cfg_list[port], FSP_ERR_INVALID_ARGUMENT);

    /* Update the target PHY lSI. */
    p_instance_ctrl->phy_lsi_cfg_index = port;

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup RMAC_PHY)
 **********************************************************************************************************************/

/**
 * Private functions
 */

/***********************************************************************************************************************
 * Function Name: rmac_phy_targets_initialize
 * Description  : PHY-LSI specific initialization processing
 * Arguments    : p_instance_ctrl -
 *                    Ethernet control block
 * Return Value : none
 ***********************************************************************************************************************/
static void rmac_phy_targets_initialize (rmac_phy_instance_ctrl_t * p_instance_ctrl)
{
    rmac_phy_extended_cfg_t * p_extend = (rmac_phy_extended_cfg_t *) p_instance_ctrl->p_ether_phy_cfg->p_extend;

    switch (p_extend->p_phy_lsi_cfg_list[p_instance_ctrl->phy_lsi_cfg_index]->type)
    {
        /* Use KSZ8091RNB */
#if (ETHER_PHY_CFG_TARGET_KSZ8091RNB_ENABLE)
        case ETHER_PHY_LSI_TYPE_KSZ8091RNB:
        {
            rmac_phy_target_ksz8091rnb_initialize(p_instance_ctrl);
            break;
        }
#endif

        /* Use KSZ8041 */
#if (ETHER_PHY_CFG_TARGET_KSZ8041_ENABLE)
        case ETHER_PHY_LSI_TYPE_KSZ8041:
        {
            rmac_phy_target_ksz8041_initialize(p_instance_ctrl);
            break;
        }
#endif

        /* Use DP83620 */
#if (ETHER_PHY_CFG_TARGET_DP83620_ENABLE)
        case ETHER_PHY_LSI_TYPE_DP83620:
        {
            rmac_phy_target_dp83620_initialize(p_instance_ctrl);
            break;
        }
#endif

        /* Use ICS1894 */
#if (ETHER_PHY_CFG_TARGET_ICS1894_ENABLE)
        case ETHER_PHY_LSI_TYPE_ICS1894:
        {
            rmac_phy_target_ics1894_initialize(p_instance_ctrl);
            break;
        }
#endif

        /* Use GPY111 */
#if (ETHER_PHY_CFG_TARGET_GPY111_ENABLE)
        case ETHER_PHY_LSI_TYPE_GPY111:
        {
            rmac_phy_target_gpy111_initialize(p_instance_ctrl);
            break;
        }
#endif

        /* User custom */
#if (ETHER_PHY_CFG_USE_CUSTOM_PHY_LSI_ENABLE)
        case ETHER_PHY_LSI_TYPE_CUSTOM:
        {
            if (NULL != p_instance_ctrl->p_ether_phy_cfg->p_extend)
            {
                rmac_phy_extended_cfg_t const * p_callback = p_instance_ctrl->p_ether_phy_cfg->p_extend;
                if (NULL != p_callback->p_target_init)
                {
                    p_callback->p_target_init(p_instance_ctrl);
                }
            }

            break;
        }
#endif

        /* If module is configured for default LSI */
        default:
        {
            break;
        }
    }
}                                      /* End of function rmac_phy_targets_initialize() */

/***********************************************************************************************************************
 * Function Name: rmac_phy_targets_is_support_link_partner_ability
 * Description  : Check if the PHY-LSI connected Ethernet controller supports link ability
 * Arguments    : p_instance_ctrl -
 *                    Ethernet control block
 *                line_speed_duplex -
 *                    Line speed duplex of link partner PHY-LSI
 * Return Value : bool
 ***********************************************************************************************************************/
static bool rmac_phy_targets_is_support_link_partner_ability (rmac_phy_instance_ctrl_t * p_instance_ctrl,
                                                              uint32_t                   line_speed_duplex)
{
    rmac_phy_extended_cfg_t * p_extend = (rmac_phy_extended_cfg_t *) p_instance_ctrl->p_ether_phy_cfg->p_extend;
    bool result = false;
    switch (p_extend->p_phy_lsi_cfg_list[p_instance_ctrl->phy_lsi_cfg_index]->type)
    {
        /* Use KSZ8091RNB */
#if (ETHER_PHY_CFG_TARGET_KSZ8091RNB_ENABLE)
        case ETHER_PHY_LSI_TYPE_KSZ8091RNB:
        {
            result = rmac_phy_target_ksz8091rnb_is_support_link_partner_ability(p_instance_ctrl, line_speed_duplex);
            break;
        }
#endif

        /* Use KSZ8041 */
#if (ETHER_PHY_CFG_TARGET_KSZ8041_ENABLE)
        case ETHER_PHY_LSI_TYPE_KSZ8041:
        {
            result = rmac_phy_target_ksz8041_is_support_link_partner_ability(p_instance_ctrl, line_speed_duplex);
            break;
        }
#endif

        /* Use DP83620 */
#if (ETHER_PHY_CFG_TARGET_DP83620_ENABLE)
        case ETHER_PHY_LSI_TYPE_DP83620:
        {
            result = rmac_phy_target_dp83620_is_support_link_partner_ability(p_instance_ctrl, line_speed_duplex);
            break;
        }
#endif

        /* Use ICS1894 */
#if (ETHER_PHY_CFG_TARGET_ICS1894_ENABLE)
        case ETHER_PHY_LSI_TYPE_ICS1894:
        {
            result = rmac_phy_target_ics1894_is_support_link_partner_ability(p_instance_ctrl, line_speed_duplex);
            break;
        }
#endif

        /* Use ICS1894 */
#if (ETHER_PHY_CFG_TARGET_GPY111_ENABLE)
        case ETHER_PHY_LSI_TYPE_GPY111:
        {
            result = rmac_phy_target_gpy111_is_support_link_partner_ability(p_instance_ctrl, line_speed_duplex);
            break;
        }
#endif

        /* User custom */
#if (ETHER_PHY_CFG_USE_CUSTOM_PHY_LSI_ENABLE)
        case ETHER_PHY_LSI_TYPE_CUSTOM:
        {
            if (NULL != p_instance_ctrl->p_ether_phy_cfg->p_extend)
            {
                rmac_phy_extended_cfg_t const * p_callback = p_instance_ctrl->p_ether_phy_cfg->p_extend;
                if (NULL != p_callback->p_target_link_partner_ability_get)
                {
                    result = p_callback->p_target_link_partner_ability_get(p_instance_ctrl, line_speed_duplex);
                }
            }

            break;
        }
#endif

        /* If module is configured for default LSI, always return true */
        default:
        {
            result = true;
            break;
        }
    }

    return result;
}                                      /* End of function rmac_phy_targets_is_support_link_partner_ability() */

/***********************************************************************************************************************
 * Function Name: r_rmac_phy_calculate_mpic
 * Description  : Calculate MPIC register value.
 * Arguments    : p_instance_ctrl -
 *                    Ethernet control block
 *                line_speed_duplex -
 *                    Line speed duplex of link partner PHY-LSI
 * Return Value : uint32_t
 ***********************************************************************************************************************/
static uint32_t r_rmac_phy_calculate_mpic (rmac_phy_instance_ctrl_t * p_instance_ctrl, uint32_t line_speed_duplex)
{
    rmac_phy_extended_cfg_t * p_extend = (rmac_phy_extended_cfg_t *) p_instance_ctrl->p_ether_phy_cfg->p_extend;
    uint32_t mpic;
    uint32_t mpic_psmcs;
    uint32_t mpic_pis;
    uint32_t mpic_lsc;
    uint32_t eswclk_frequency;

    /*Get frequency of ESWCLK. */
    eswclk_frequency = R_BSP_SourceClockHzGet((fsp_priv_source_clock_t) (R_SYSTEM->ESWCKCR_b.CKSEL)) /
                       R_FSP_ClockDividerGet(R_SYSTEM->ESWCKDIVCR_b.CKDIV);

    /* Calculate cycle of MDC clock. */
    mpic_psmcs = ((eswclk_frequency / p_extend->mdc_clock_rate) / 2) - 1;

    /* Configure interface. */
    if ((ETHER_PHY_MII_TYPE_MII == p_instance_ctrl->p_ether_phy_cfg->mii_type) ||
        (ETHER_PHY_MII_TYPE_RMII == p_instance_ctrl->p_ether_phy_cfg->mii_type))
    {
        /* MII, 100Mbps */
        mpic_pis = 0;
    }
    else
    {
        /* GMII, 1000Mbps */
        mpic_pis = 2;
    }

    /* Configure link speed. */
    switch (line_speed_duplex)
    {
        case ETHER_PHY_LINK_SPEED_10H:
        case ETHER_PHY_LINK_SPEED_10F:
        {
            mpic_lsc = 0;
            break;
        }

        case ETHER_PHY_LINK_SPEED_100H:
        case ETHER_PHY_LINK_SPEED_100F:
        {
            mpic_lsc = 1;
            break;
        }

        case ETHER_PHY_LINK_SPEED_1000H:
        case ETHER_PHY_LINK_SPEED_1000F:
        {
            mpic_lsc = 2;
            break;
        }

        default:
        {
            mpic_lsc = 0;
            break;
        }
    }

    mpic = (R_RMAC0_MPIC_PSMCS_Msk & (mpic_psmcs << R_RMAC0_MPIC_PSMCS_Pos)) |
           (R_RMAC0_MPIC_PIS_Msk & (mpic_pis << R_RMAC0_MPIC_PIS_Pos)) |
           (R_RMAC0_MPIC_LSC_Msk & (mpic_lsc << R_RMAC0_MPIC_LSC_Pos)) |
           (R_RMAC0_MPIC_PSMCT_Msk & ((uint32_t) p_extend->mdio_capture_time << R_RMAC0_MPIC_PSMCT_Pos)) |
           (R_RMAC0_MPIC_PSMHT_Msk & ((uint32_t) p_extend->mdio_hold_time << R_RMAC0_MPIC_PSMHT_Pos));

    return mpic;
}

/***********************************************************************************************************************
 * Function Name: r_rmac_phy_get_operation_mode
 * Description  : Get operation mode of ETHA.
 * Arguments    : p_instance_ctrl -
 *                    Ethernet control block
 * Return Value : uint8_t
 ***********************************************************************************************************************/
static uint8_t r_rmac_phy_get_operation_mode (rmac_phy_instance_ctrl_t * p_instance_ctrl)
{
    R_ETHA0_Type * p_etha_reg =
        (R_ETHA0_Type *) (R_ETHA0_BASE + (ETHA_REG_SIZE * p_instance_ctrl->p_ether_phy_cfg->channel));

    /* Return operation mode of ETHA IP. */
    return p_etha_reg->EAMS_b.OPS;
}

/***********************************************************************************************************************
 * Change operation mode of ETHA.
 *
 * @param[in] mode New operation mode
 ***********************************************************************************************************************/
static void r_rmac_phy_set_operation_mode (uint8_t channel, uint8_t mode)
{
    R_ETHA0_Type * p_etha_reg =
        (R_ETHA0_Type *) (R_ETHA0_BASE + (ETHA_REG_SIZE * channel));

    /* Mode transition */
    p_etha_reg->EAMC_b.OPC = R_ETHA0_EAMC_OPC_Msk & mode;
    FSP_HARDWARE_REGISTER_WAIT(p_etha_reg->EAMS_b.OPS, mode);
}

/***********************************************************************************************************************
 * Function Name: r_rmac_phy_set_mii_type_configuration
 * Description  : Set MII type configuration for the port.
 * Arguments    : p_instance_ctrl -
 *                    Ethernet control block
 * Return Value : uint32_t
 ***********************************************************************************************************************/
static void r_rmac_phy_set_mii_type_configuration (rmac_phy_instance_ctrl_t * p_instance_ctrl, uint8_t port)
{
    volatile uint32_t * p_miicr_register;

    /* Configure pins for MII or RMII. Set PHYMODE0 if MII is selected. */
    R_PMISC->PFENET =
        (uint8_t) ((ETHER_PHY_MII_TYPE_MII ==
                    p_instance_ctrl->p_ether_phy_cfg->mii_type) << (R_PMISC_PFENET_PHYMODE0_Pos + port));

    /* Get pointer to a MIICRn register. */
    p_miicr_register = &(R_ESWM->MIICR0) + port;

    /* Configure ESWM as MII, RMII, or RGMII. */
    switch (p_instance_ctrl->p_ether_phy_cfg->mii_type)
    {
        case ETHER_PHY_MII_TYPE_RMII:
        {
            *p_miicr_register = 2;
            break;
        }

        case ETHER_PHY_MII_TYPE_RGMII:
        {
            *p_miicr_register = (R_ESWM_MIICR0_TXCIDE_Msk | 1);

            /* Enable TXC generation.  */
            R_ESWM->MIIRR = R_ESWM->MIIRR | (1 << (R_ESWM_MIIRR_RGRST_Pos + port));
            break;
        }

        default:
        {
            /* MII or GMII. */
            *p_miicr_register = 0;
            break;
        }
    }
}
