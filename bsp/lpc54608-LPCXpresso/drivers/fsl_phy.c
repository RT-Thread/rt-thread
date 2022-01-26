/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_phy.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Defines the timeout macro. */
#define PHY_TIMEOUT_COUNT 0xFFFFU

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the ENET instance from peripheral base address.
 *
 * @param base ENET peripheral base address.
 * @return ENET instance.
 */
extern uint32_t ENET_GetInstance(ENET_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to enet clocks for each instance. */
#if defined(FSL_FEATURE_SOC_ENET_COUNT) && (FSL_FEATURE_SOC_ENET_COUNT > 0)
extern clock_ip_name_t s_enetClock[FSL_FEATURE_SOC_ENET_COUNT];
#elif defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
extern clock_ip_name_t s_enetClock[FSL_FEATURE_SOC_LPC_ENET_COUNT];
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t PHY_Init(ENET_Type *base, uint32_t phyAddr, uint32_t srcClock_Hz)
{
    uint32_t reg;
    uint32_t idReg = 0;
    uint32_t delay = PHY_TIMEOUT_COUNT;
    uint32_t instance = ENET_GetInstance(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Set SMI first. */
    CLOCK_EnableClock(s_enetClock[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(FSL_FEATURE_SOC_ENET_COUNT) && (FSL_FEATURE_SOC_ENET_COUNT > 0)
    ENET_SetSMI(base, srcClock_Hz, false);
#elif defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
    ENET_SetSMI(base);
#endif
    /* Initialization after PHY stars to work. */
    while ((idReg != PHY_CONTROL_ID1) && (delay != 0))
    {
        PHY_Read(base, phyAddr, PHY_ID1_REG, &idReg);
        delay --;
    }

    if (!delay)
    {
        return kStatus_Fail;
    }
    delay = PHY_TIMEOUT_COUNT;

    /* Reset PHY and wait until completion. */
    PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, PHY_BCTL_RESET_MASK);
    do
    {
        PHY_Read(base, phyAddr, PHY_BASICCONTROL_REG, &reg);
    } while (delay-- && reg & PHY_BCTL_RESET_MASK);

    if (!delay)
    {
        return kStatus_Fail;
    }

    /* Set the ability. */
    PHY_Write(base, phyAddr, PHY_AUTONEG_ADVERTISE_REG, (PHY_ALL_CAPABLE_MASK | 0x1U));

    /* Start Auto negotiation and wait until auto negotiation completion */
    PHY_Write(base, phyAddr, PHY_BASICCONTROL_REG, (PHY_BCTL_AUTONEG_MASK | PHY_BCTL_RESTART_AUTONEG_MASK));
    delay = PHY_TIMEOUT_COUNT;
    do
    {
        PHY_Read(base, phyAddr, PHY_SEPCIAL_CONTROL_REG, &reg);
        delay --;
    } while (delay && ((reg & PHY_SPECIALCTL_AUTONEGDONE_MASK) == 0));

    if (!delay)
    {
        return kStatus_Fail;
    }

    return kStatus_Success;
}

status_t PHY_Write(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t data)
{
#if defined(FSL_FEATURE_SOC_ENET_COUNT) && (FSL_FEATURE_SOC_ENET_COUNT > 0)
    uint32_t counter;

    /* Clear the SMI interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI write command. */
    ENET_StartSMIWrite(base, phyAddr, phyReg, kENET_MiiWriteValidFrame, data);

    /* Wait for SMI complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter)
    {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

#elif defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
    ENET_StartSMIWrite(base, phyAddr, phyReg, data);
    while (ENET_IsSMIBusy(base))
        ;
#endif
    return kStatus_Success;
}

status_t PHY_Read(ENET_Type *base, uint32_t phyAddr, uint32_t phyReg, uint32_t *dataPtr)
{
#if defined(FSL_FEATURE_SOC_ENET_COUNT) && (FSL_FEATURE_SOC_ENET_COUNT > 0)
     assert(dataPtr);

    uint32_t counter;

    /* Clear the MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);

    /* Starts a SMI read command operation. */
    ENET_StartSMIRead(base, phyAddr, phyReg, kENET_MiiReadValidFrame);

    /* Wait for MII complete. */
    for (counter = PHY_TIMEOUT_COUNT; counter > 0; counter--)
    {
        if (ENET_GetInterruptStatus(base) & ENET_EIR_MII_MASK)
        {
            break;
        }
    }

    /* Check for timeout. */
    if (!counter)
    {
        return kStatus_PHY_SMIVisitTimeout;
    }

    /* Get data from MII register. */
    *dataPtr = ENET_ReadSMIData(base);

    /* Clear MII interrupt event. */
    ENET_ClearInterruptStatus(base, ENET_EIR_MII_MASK);
#elif defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
    ENET_StartSMIRead(base, phyAddr, phyReg);
    while (ENET_IsSMIBusy(base))
        ;
    *dataPtr = ENET_ReadSMIData(base);
#endif
     return kStatus_Success;
}

status_t PHY_GetLinkStatus(ENET_Type *base, uint32_t phyAddr, bool *status)
{
    uint32_t reg;
    status_t result = kStatus_Success;

    /* Read the basic status register. */
    result = PHY_Read(base, phyAddr, PHY_BASICSTATUS_REG, &reg);
    if (result == kStatus_Success)
    {
        if (reg & PHY_BSTATUS_LINKSTATUS_MASK)
        {
            /* link up. */
            *status = true;
        }
        else
        {
            *status = false;
        }
    }
    return result;
}

status_t PHY_GetLinkSpeedDuplex(ENET_Type *base, uint32_t phyAddr, phy_speed_t *speed, phy_duplex_t *duplex)
{
    assert(duplex);
    assert(speed);

    uint32_t reg;
    status_t result = kStatus_Success;

    /* Read the control two register. */
    result = PHY_Read(base, phyAddr, PHY_SEPCIAL_CONTROL_REG, &reg);
    if (result == kStatus_Success)
    {
        if (reg & PHY_SPECIALCTL_DUPLEX_MASK)
        {
            /* Full duplex. */
            *duplex = kPHY_FullDuplex;
        }
        else
        {
            /* Half duplex. */
            *duplex = kPHY_HalfDuplex;
        }

        if (reg & PHY_SPECIALCTL_100SPEED_MASK)
        {
            /* 100M speed. */
            *speed = kPHY_Speed100M;
        }
        else
        { /* 10M speed. */
            *speed = kPHY_Speed10M;
        }
    }
    return result;
}
