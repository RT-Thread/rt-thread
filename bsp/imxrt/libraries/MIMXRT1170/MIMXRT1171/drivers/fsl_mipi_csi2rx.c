/*
 * Copyright 2017, 2019-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_mipi_csi2rx.h"

/*
 * The MIPI CSI2 peripheral can not work independently, some other control and
 * status registers must be used together. There are two integration methods
 * with these registers.
 *
 * 1. The registers are collected in one dedicated module: CSR.
 * 2. The registers are scattered in multiple modules.
 *
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mipi_csi2rx"
#endif

#if (defined(FSL_FEATURE_CSI2RX_CSR_OFFSET) && FSL_FEATURE_CSI2RX_CSR_OFFSET)
#define CSI2RX_GET_CSR(csi_base) (MIPI_CSI_CSR_Type *)((uint32_t)(csi_base) - (uint32_t)FSL_FEATURE_CSI2RX_CSR_OFFSET)
#define MIPI_CSI2RX_HAS_CSR      1
#else
#define MIPI_CSI2RX_HAS_CSR 0
#include "fsl_soc_mipi_csi2rx.h"
#endif

#if MIPI_CSI2RX_HAS_CSR

/* Macro Map */
#ifndef MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_CTL_CLK_OFF_MASK
#define MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_CTL_CLK_OFF_MASK \
    MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_CONTROLLER_CLOCK_RESET_CONTROL(2U)
#define MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_SW_RESET_MASK \
    MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_CONTROLLER_CLOCK_RESET_CONTROL(1U)
#endif

#ifndef MIPI_CSI_CSR_PHY_CTRL_CONTI_CLK_MODE_MASK
#define MIPI_CSI_CSR_PHY_CTRL_CONTI_CLK_MODE_MASK MIPI_CSI_CSR_PHY_CTRL_CONT_CLK_MODE_MASK
#endif

#ifndef MIPI_CSI_CSR_PHY_CTRL_PRG_RXHS_SETTLE
#define MIPI_CSI_CSR_PHY_CTRL_PRG_RXHS_SETTLE(x) MIPI_CSI_CSR_PHY_CTRL_S_PRG_RXHS_SETTLE(x)
#endif

#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Returns an instance number given a base address.
 *
 * If an invalid base address is passed, debug builds will assert. Release builds will just return
 * instance number 0.
 *
 * @param base The CSI2RX peripheral base address.
 * @return CSI2RX instance number starting from 0.
 */
uint32_t CSI2RX_GetInstance(MIPI_CSI2RX_Type *base);

#if MIPI_CSI2RX_HAS_CSR

/*!
 * @brief Perform CSI2RX resource reset in system level.
 *
 * @param base The CSI2RX peripheral base address.
 * @param reset Pass in true to set to reset state, false to release reset.
 */
static void MIPI_CSI2RX_SoftwareReset(MIPI_CSI2RX_Type *base, bool reset);

/*!
 * @brief Initialize the CSI2RX interface.
 *
 * @param base The CSI2RX peripheral base address.
 * @param tHsSettle_EscClk t-HS_SETTLE in esc clock period.
 */
static void MIPI_CSI2RX_InitInterface(MIPI_CSI2RX_Type *base, uint8_t tHsSettle_EscClk);

/*!
 * @brief Deinitialize the CSI2RX interface.
 *
 * @param base The CSI2RX peripheral base address.
 */
static void MIPI_CSI2RX_DeinitInterface(MIPI_CSI2RX_Type *base);

#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Array to map MIPI CSI2RX instance number to base address. */
static const uint32_t s_csi2rxBaseAddrs[] = MIPI_CSI2RX_BASE_ADDRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to MPI CSI2RX clocks for each instance. */
static const clock_ip_name_t s_csi2rxClocks[] = MIPI_CSI2RX_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

#if MIPI_CSI2RX_HAS_CSR
static void MIPI_CSI2RX_SoftwareReset(MIPI_CSI2RX_Type *base, bool reset)
{
    MIPI_CSI_CSR_Type *csr = CSI2RX_GET_CSR(base);

    if (reset)
    {
        csr->CONTROLLER_CLOCK_RESET_CONTROL = MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_CTL_CLK_OFF_MASK;
    }
    else
    {
        csr->CONTROLLER_CLOCK_RESET_CONTROL = MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_CTL_CLK_OFF_MASK;
        csr->CONTROLLER_CLOCK_RESET_CONTROL = MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_SW_RESET_MASK |
                                              MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_CTL_CLK_OFF_MASK;
    }
}

static void MIPI_CSI2RX_InitInterface(MIPI_CSI2RX_Type *base, uint8_t tHsSettle_EscClk)
{
    MIPI_CSI_CSR_Type *csr = CSI2RX_GET_CSR(base);

    /* Pixel link control */
    csr->PLM_CTRL = 0;

    /* Configure the PHY. */
    csr->PHY_CTRL = MIPI_CSI_CSR_PHY_CTRL_RX_ENABLE_MASK |  /* Enable RX. */
                    MIPI_CSI_CSR_PHY_CTRL_AUTO_PD_EN_MASK | /* Auto power down unused lanes. */
                    MIPI_CSI_CSR_PHY_CTRL_PD_MASK | MIPI_CSI_CSR_PHY_CTRL_DDRCLK_EN_MASK | /* Enable the DDR clock. */
                    MIPI_CSI_CSR_PHY_CTRL_CONTI_CLK_MODE_MASK |                            /* Continue clock. */
                    MIPI_CSI_CSR_PHY_CTRL_RTERM_SEL_MASK | /*  LPRX voltage level enable HS termination */
                    MIPI_CSI_CSR_PHY_CTRL_PRG_RXHS_SETTLE(tHsSettle_EscClk - 1UL); /* T(HS-SETTLE) */

    /* Don't support interlace currently. */
    csr->VC_INTERLACED = 0U;

    /* Don't mask any data type */
#if defined(MIPI_CSI_CSR_DATA_TYPE_DISABLE_BF_DATA_TYPE_DISABLE_MASK)
    csr->DATA_TYPE_DISABLE_BF = 0U;
#else
    csr->DATA_TYPE_DIS       = 0U;
#endif

    /* VC fence. */
#if defined(MIPI_CSI_CSR_STREAM_FENCING_CONTROL_STREAM_FENCING_CONTROL_MASK)
    csr->STREAM_FENCING_CONTROL = 0U;
#else
    csr->STREAM_FENCING_CTRL = 0U;
#endif

#if defined(MIPI_CSI_CSR_PLM_CTRL_PL_CLOCK_RUNNING_MASK)
    /* Wait for PL clock active. */
    while (0UL != (csr->PLM_CTRL & MIPI_CSI_CSR_PLM_CTRL_PL_CLOCK_RUNNING_MASK))
    {
    }
#endif

    /* Enable pixel link master. */
    csr->PLM_CTRL |= (MIPI_CSI_CSR_PLM_CTRL_ENABLE_MASK | MIPI_CSI_CSR_PLM_CTRL_VALID_OVERRIDE_MASK);

    /* Power up PHY. */
    csr->PHY_CTRL &= ~MIPI_CSI_CSR_PHY_CTRL_PD_MASK;

    /* Start clock. */
    csr->CONTROLLER_CLOCK_RESET_CONTROL = MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_SW_RESET_MASK;
}

static void MIPI_CSI2RX_DeinitInterface(MIPI_CSI2RX_Type *base)
{
    MIPI_CSI_CSR_Type *csr = CSI2RX_GET_CSR(base);

    /* Disable the PHY. */
    csr->PHY_CTRL = 0;

    /* Disable the pixel link master. */
    csr->PLM_CTRL = 0;

    /* Stop the clock and assert reset. */
    csr->CONTROLLER_CLOCK_RESET_CONTROL = MIPI_CSI_CSR_CONTROLLER_CLOCK_RESET_CONTROL_CTL_CLK_OFF_MASK;
}
#endif

uint32_t CSI2RX_GetInstance(MIPI_CSI2RX_Type *base)
{
    uint32_t i;

    for (i = 0U; i < ARRAY_SIZE(s_csi2rxBaseAddrs); i++)
    {
        if (MSDK_REG_SECURE_ADDR((uint32_t)base) == MSDK_REG_SECURE_ADDR(s_csi2rxBaseAddrs[i]))
        {
            return i;
        }
    }

    assert(false);

    return 0;
}

/*!
 * brief Enables and configures the CSI2RX peripheral module.
 *
 * param base CSI2RX peripheral address.
 * param config CSI2RX module configuration structure.
 */
void CSI2RX_Init(MIPI_CSI2RX_Type *base, const csi2rx_config_t *config)
{
    assert(NULL != config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* un-gate clock */
    (void)CLOCK_EnableClock(s_csi2rxClocks[CSI2RX_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    MIPI_CSI2RX_SoftwareReset(base, false);

    CSI2RX_REG_CFG_NUM_LANES(base) = config->laneNum - 1UL;
    CSI2RX_REG_CFG_DISABLE_DATA_LANES(base) =
        MIPI_CSI2RX_CSI2RX_CFG_NUM_LANES_csi2rx_cfg_num_lanes_MASK & ~((1UL << (uint32_t)config->laneNum) - 1UL);

    /* Don't disable data types. */
    CSI2RX_REG_CFG_DISABLE_PAYLOAD_0(base) = 0;
    CSI2RX_REG_CFG_DISABLE_PAYLOAD_1(base) = 0;

    /* Disable all interrupts. */
    CSI2RX_REG_IRQ_MASK(base) = MIPI_CSI2RX_CSI2RX_IRQ_MASK_csi2rx_irq_mask_MASK;

    MIPI_CSI2RX_InitInterface(base, config->tHsSettle_EscClk);
}

/*!
 * brief Disables the CSI2RX peripheral module.
 *
 * param base CSI2RX peripheral address.
 */
void CSI2RX_Deinit(MIPI_CSI2RX_Type *base)
{
    MIPI_CSI2RX_DeinitInterface(base);

    MIPI_CSI2RX_SoftwareReset(base, true);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* gate clock */
    (void)CLOCK_DisableClock(s_csi2rxClocks[CSI2RX_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
