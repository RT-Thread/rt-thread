/***************************************************************************//**
* \file cy_gpio.c
* \version 1.70
*
* Provides an API implementation of the GPIO driver
*
********************************************************************************
* \copyright
* Copyright (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
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

#include "cy_device.h"

#if defined (CY_IP_MXS40SIOSS) || defined (CY_IP_MXS40IOSS) || defined (CY_IP_MXS22IOSS)

#include "cy_gpio.h"
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
#include "cy_pra.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif


/* Define for AMUX A splitters */
#define GPIO_AMUXA_SPLITTER_MASK     (uint32_t)(HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SL_Msk \
                                              | HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_SR_Msk \
                                              | HSIOM_AMUX_SPLIT_CTL_SWITCH_AA_S0_Msk)

/* Define for AMUX B splitters */
#define GPIO_AMUXB_SPLITTER_MASK     (uint32_t)(HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_Msk \
                                              | HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SR_Msk \
                                              | HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_S0_Msk)

/*******************************************************************************
* Function Name: Cy_GPIO_Pin_Init
****************************************************************************//**
*
* Initializes all pin configuration settings for the specified pin.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param config
* Pointer to the pin config structure base address
*
* \return
* Initialization status
*
* \note
* This function modifies port registers in read-modify-write operations. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \note
* When EXT_CLK is source to HF0 and this API is called from application then
* make sure that the drivemode argument is CY_GPIO_DM_HIGHZ.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Pin_Init
*
*******************************************************************************/
cy_en_gpio_status_t Cy_GPIO_Pin_Init(GPIO_PRT_Type *base, uint32_t pinNum, const cy_stc_gpio_pin_config_t *config)
{
    cy_en_gpio_status_t status = CY_GPIO_BAD_PARAM;

    if ((NULL != base) && (NULL != config))
    {
#if defined (CY_IP_MXS40IOSS)
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
        cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
        uint32_t maskCfgOut;
#endif /* CY_IP_MXS40IOSS */
        uint32_t tempReg, tempReg2;

        CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
        CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(config->outVal));
        CY_ASSERT_L2(CY_GPIO_IS_DM_VALID(config->driveMode));
        CY_ASSERT_L2(CY_GPIO_IS_HSIOM_VALID(config->hsiom));
        CY_ASSERT_L2(CY_GPIO_IS_INT_EDGE_VALID(config->intEdge));
        CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(config->intMask));
        CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(config->vtrip));

        CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(config->vregEn));
        CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(config->ibufMode));
        CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(config->vtripSel));
        CY_ASSERT_L2(CY_GPIO_IS_VREF_SEL_VALID(config->vrefSel));
        CY_ASSERT_L2(CY_GPIO_IS_VOH_SEL_VALID(config->vohSel));
        CY_ASSERT_L2(CY_GPIO_IS_DRIVE_SEL_VALID(config->driveSel));

#if defined (CY_IP_MXS22IOSS)
        CY_ASSERT_L2(CY_GPIO_IS_PULLUP_RES_VALID(config->pullUpRes));
#endif /* CY_IP_MXS22IOSS */

        /* Slew rate and Driver strength */
#if defined (CY_IP_MXS40IOSS)
        CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(config->slewRate));
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)

        pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);

        if (pinType == CY_PRA_PIN_SECURE)
        {
            return(status); /* Protected pins are not allowed to configure */
        }
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
        maskCfgOut = (CY_GPIO_CFG_OUT_SLOW_MASK << pinNum)
                     | (CY_GPIO_CFG_OUT_DRIVE_SEL_MASK << ((uint32_t)(pinNum << 1U) + CY_GPIO_CFG_OUT_DRIVE_OFFSET));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_OUT)) & ~(maskCfgOut);
        }
        else
        {
            tempReg = GPIO_PRT_CFG_OUT(base) & ~(maskCfgOut);
        }
#else
        tempReg = GPIO_PRT_CFG_OUT(base) & ~(maskCfgOut);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

        tempReg2 = tempReg | ((config->slewRate & CY_GPIO_CFG_OUT_SLOW_MASK) << pinNum)
                            | ((config->driveSel & CY_GPIO_CFG_OUT_DRIVE_SEL_MASK) << ((uint32_t)(pinNum << 1U) + CY_GPIO_CFG_OUT_DRIVE_OFFSET));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_OUT), tempReg2);
        }
        else /* non-secure pin */
        {
            GPIO_PRT_CFG_OUT(base) = tempReg2;
        }
#else
        GPIO_PRT_CFG_OUT(base) = tempReg2;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

#else
        CY_ASSERT_L2(CY_GPIO_IS_SLEW_RATE_VALID(config->slewRate));
#if ((IOSS_HSIOM_HSIOM_SEC_PORT_NR != 0) || (CPUSS_CM33_0_SECEXT_PRESENT != 0))
        CY_ASSERT_L2(CY_GPIO_IS_HSIOM_SEC_VALID(config->nonSec));
        Cy_GPIO_SetHSIOM_SecPin(base, pinNum, config->nonSec);
#endif /* IOSS_HSIOM_HSIOM_SEC_PORT_NR, CPUSS_CM33_0_SECEXT_PRESENT */
        Cy_GPIO_SetSlewRate(base, pinNum, config->slewRate);
        Cy_GPIO_SetDriveSel(base, pinNum, config->driveSel);
#endif /* CY_IP_MXS40IOSS */
        Cy_GPIO_SetHSIOM(base, pinNum, config->hsiom);
        Cy_GPIO_SetDrivemode(base, pinNum, config->driveMode);

        Cy_GPIO_SetInterruptEdge(base, pinNum, config->intEdge);
        Cy_GPIO_SetInterruptMask(base, pinNum, config->intMask);
        Cy_GPIO_SetVtrip(base, pinNum, config->vtrip);

        /* SIO specific configuration */
 #if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO)) & ~(CY_GPIO_SIO_PIN_MASK);
        }
        else
        {
            tempReg = GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_SIO_PIN_MASK);
        }
#else
        tempReg = GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_SIO_PIN_MASK);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

        tempReg2 = tempReg | (((config->vregEn & CY_GPIO_VREG_EN_MASK)
                                         | ((config->ibufMode & CY_GPIO_IBUF_MASK) << CY_GPIO_IBUF_SHIFT)
                                         | ((config->vtripSel & CY_GPIO_VTRIP_SEL_MASK) << CY_GPIO_VTRIP_SEL_SHIFT)
                                         | ((config->vrefSel & CY_GPIO_VREF_SEL_MASK)  << CY_GPIO_VREF_SEL_SHIFT)
                                         | ((config->vohSel & CY_GPIO_VOH_SEL_MASK) << CY_GPIO_VOH_SEL_SHIFT))
                                           << ((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO), tempReg2);
        }
        else /* non-secure pin */
        {
            GPIO_PRT_CFG_SIO(base) = tempReg2;
        }
#else
        GPIO_PRT_CFG_SIO(base) = tempReg2;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

#if defined (CY_IP_MXS22IOSS)
        Cy_GPIO_SetPullupResistance(base, pinNum, config->pullUpRes);
#endif /* CY_IP_MXS22IOSS */

        Cy_GPIO_Write(base, pinNum, config->outVal);

        status = CY_GPIO_SUCCESS;
    }

    return(status);
}


/*******************************************************************************
* Function Name: Cy_GPIO_Port_Init
****************************************************************************//**
*
* Initialize a complete port of pins from a single init structure.
*
* The configuration structure used in this function has a 1:1 mapping to the
* GPIO and HSIOM registers. Refer to the device Technical Reference Manual (TRM)
* for the register details on how to populate them.
*
* \param base
* Pointer to the pin's port register base address
*
* \param config
* Pointer to the pin config structure base address
*
* \return
* Initialization status
*
* \note
* If using the PSoC Creator IDE, there is no need to initialize the pins when
* using the GPIO component on the schematic. Ports are configured in
* Cy_SystemInit() before main() entry.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Port_Init
*
*******************************************************************************/
cy_en_gpio_status_t Cy_GPIO_Port_Init(GPIO_PRT_Type* base, const cy_stc_gpio_prt_config_t *config)
{
    cy_en_gpio_status_t status = CY_GPIO_BAD_PARAM;

    if ((NULL != base) && (NULL != config))
    {
        uint32_t portNum;
        HSIOM_PRT_V1_Type* baseHSIOM;
#if (defined (CY_IP_MXS40SIOSS) &&  ((IOSS_HSIOM_HSIOM_SEC_PORT_NR != 0) || (CPUSS_CM33_0_SECEXT_PRESENT != 0)))  || defined (CY_IP_MXS22IOSS)
        HSIOM_SECURE_PRT_Type *baseSecHSIOM;
#else
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
        bool secPort;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
#endif /* CY_IP_MXS40SIOSS, IOSS_HSIOM_HSIOM_SEC_PORT_NR, CPUSS_CM33_0_SECEXT_PRESENT, CY_IP_MXS22IOSS */
        portNum = ((uint32_t)(base) - CY_GPIO_BASE) / GPIO_PRT_SECTION_SIZE;
        baseHSIOM = (HSIOM_PRT_V1_Type*)(CY_HSIOM_BASE + (HSIOM_PRT_SECTION_SIZE * portNum));

        CY_ASSERT_L2(CY_GPIO_IS_PIN_BIT_VALID(config->out));
        CY_ASSERT_L2(CY_GPIO_IS_PIN_BIT_VALID(config->cfgIn));
        CY_ASSERT_L2(CY_GPIO_IS_INTR_CFG_VALID(config->intrCfg));
        CY_ASSERT_L2(CY_GPIO_IS_INTR_MASK_VALID(config->intrMask));
        CY_ASSERT_L2(CY_GPIO_IS_SEL_ACT_VALID(config->sel0Active));
        CY_ASSERT_L2(CY_GPIO_IS_SEL_ACT_VALID(config->sel1Active));

#if defined (CY_IP_MXS22IOSS)
        CY_ASSERT_L2(CY_GPIO_PRT_IS_PULLUP_RES_VALID(config->cfgRes));
#endif /* CY_IP_MXS22IOSS */

#if defined (CY_IP_MXS40SIOSS) || defined (CY_IP_MXS22IOSS)
#if (IOSS_HSIOM_HSIOM_SEC_PORT_NR != 0) || (CPUSS_CM33_0_SECEXT_PRESENT != 0)
        CY_ASSERT_L2(CY_GPIO_IS_PIN_BIT_VALID(config->nonSecMask));
        baseSecHSIOM = (HSIOM_SECURE_PRT_Type*)(CY_HSIOM_SECURE_BASE + (HSIOM_SECURE_PRT_SECTION_SIZE * portNum));

            HSIOM_SEC_PRT_NONSEC_MASK(baseSecHSIOM) = config->nonSecMask;
#endif /* IOSS_HSIOM_HSIOM_SEC_PORT_NR, CPUSS_CM33_0_SECEXT_PRESENT */
        GPIO_PRT_SLEW_EXT(base)                 = config->cfgSlew;
        GPIO_PRT_DRIVE_EXT0(base)               = config->cfgDriveSel0;
        GPIO_PRT_DRIVE_EXT1(base)               = config->cfgDriveSel1;
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
        secPort = CY_PRA_IS_PORT_SECURE(base);
        if (secPort)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG), config->cfg);
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_IN), config->cfgIn);
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_OUT), config->cfgOut);
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_CFG), config->intrCfg);
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_MASK), config->intrMask);
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO), config->cfgSIO);
            CY_PRA_REG32_SET(CY_PRA_GET_HSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT0), config->sel0Active);
            CY_PRA_REG32_SET(CY_PRA_GET_HSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT1), config->sel1Active);
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_OUT), config->out);
        }
        else
        {
            GPIO_PRT_CFG(base)             = config->cfg;
            GPIO_PRT_CFG_IN(base)          = config->cfgIn;
            GPIO_PRT_CFG_OUT(base)         = config->cfgOut;
            GPIO_PRT_INTR_CFG(base)        = config->intrCfg;
            GPIO_PRT_INTR_MASK(base)       = config->intrMask;
            GPIO_PRT_CFG_SIO(base)         = config->cfgSIO;
            /* For 1M device check for secure HSIOM */
#if defined(CY_DEVICE_PSOC6ABLE2)
            if (CY_PRA_IS_HSIOM_SECURE(base))
            {
                CY_PRA_REG32_SET(CY_PRA_GET_ADJHSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT0), config->sel0Active);
                CY_PRA_REG32_SET(CY_PRA_GET_ADJHSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT1), config->sel1Active);
            }
            else
            {
                HSIOM_PRT_PORT_SEL0(baseHSIOM) = config->sel0Active;
                HSIOM_PRT_PORT_SEL1(baseHSIOM) = config->sel1Active;
            }
#else
            HSIOM_PRT_PORT_SEL0(baseHSIOM) = config->sel0Active;
            HSIOM_PRT_PORT_SEL1(baseHSIOM) = config->sel1Active;
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
            GPIO_PRT_OUT(base)             = config->out;
        }
#else
        GPIO_PRT_CFG(base)             = config->cfg;
        GPIO_PRT_CFG_IN(base)          = config->cfgIn;
        GPIO_PRT_CFG_OUT(base)         = config->cfgOut;
        GPIO_PRT_INTR_CFG(base)        = config->intrCfg;
        GPIO_PRT_INTR_MASK(base)       = config->intrMask;
        GPIO_PRT_CFG_SIO(base)         = config->cfgSIO;
        HSIOM_PRT_PORT_SEL0(baseHSIOM) = config->sel0Active;
        HSIOM_PRT_PORT_SEL1(baseHSIOM) = config->sel1Active;
        GPIO_PRT_OUT(base)             = config->out;
#if defined (CY_IP_MXS22IOSS)
        GPIO_PRT_CFG_OUT3(base)    = config->cfgOut3;
        GPIO_PRT_CFG_RES(base)     = config->cfgRes;
#endif /* CY_IP_MXS22IOSS */
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

        status = CY_GPIO_SUCCESS;
    }

    return (status);
}


/*******************************************************************************
* Function Name: Cy_GPIO_Pin_FastInit
****************************************************************************//**
*
* Initialize the most common configuration settings for all pin types.
*
* These include, drive mode, initial output value, and HSIOM connection.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param driveMode
* Pin drive mode. Options are detailed in \ref group_gpio_driveModes macros
*
* \param outVal
* Logic state of the output buffer driven to the pin (1 or 0)
*
* \param hsiom
* HSIOM input selection
*
* \note
* This function modifies port registers in read-modify-write operations. It is
* not thread safe as the resource is shared among multiple pins on a port.
* You can use the Cy_SysLib_EnterCriticalSection() and
* Cy_SysLib_ExitCriticalSection() functions to ensure that
* Cy_GPIO_Pin_FastInit() function execution is not interrupted.
*
* \note
* When EXT_CLK is source to HF0 and this API is called from application then
* make sure that the drivemode argument is CY_GPIO_DM_HIGHZ.
*
* \note
* This doesn't set pull-up resistance value. By default. the pull-up resistance
* is disabled. To select it, use Cy_GPIO_SetPullupResistance.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Pin_FastInit
*
*******************************************************************************/
void Cy_GPIO_Pin_FastInit(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t driveMode,
                                        uint32_t outVal, en_hsiom_sel_t hsiom)
{
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_DM_VALID(driveMode));
    CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(outVal));
    CY_ASSERT_L2(CY_GPIO_IS_HSIOM_VALID(hsiom));

    uint32_t tempReg;
#if defined (CY_IP_MXS22IOSS)
    uint32_t tempRegCfg3;
#endif /* CY_IP_MXS22IOSS */

    Cy_GPIO_SetHSIOM(base, pinNum, hsiom);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);

    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
#if defined(CY_DEVICE_PSOC6ABLE2)
            tempReg = (CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_OUT)) & ~(CY_GPIO_OUT_MASK << pinNum));
#else
            tempReg = (GPIO_PRT_OUT(base) & ~(CY_GPIO_OUT_MASK << pinNum));
#endif
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_OUT), (tempReg | ((outVal & CY_GPIO_OUT_MASK) << pinNum)));

#if defined(CY_DEVICE_PSOC6ABLE2)
            tempReg = (CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG)) & ~(CY_GPIO_CFG_DM_MASK << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET)));
#else
            tempReg = (GPIO_PRT_CFG(base) & ~(CY_GPIO_CFG_DM_MASK << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET)));
#endif
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG), (tempReg | ((driveMode & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET))));
        }
        else /* non secure pin */
        {
            tempReg = (GPIO_PRT_OUT(base) & ~(CY_GPIO_OUT_MASK << pinNum));
            GPIO_PRT_OUT(base) = tempReg | ((outVal & CY_GPIO_OUT_MASK) << pinNum);

            tempReg = (GPIO_PRT_CFG(base) & ~(CY_GPIO_CFG_DM_MASK << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET)));
            GPIO_PRT_CFG(base) = tempReg | ((driveMode & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    tempReg = (GPIO_PRT_OUT(base) & ~(CY_GPIO_OUT_MASK << pinNum));
    GPIO_PRT_OUT(base) = tempReg | ((outVal & CY_GPIO_OUT_MASK) << pinNum);

    tempReg = (GPIO_PRT_CFG(base) & ~(CY_GPIO_CFG_DM_MASK << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET)));
#if defined (CY_IP_MXS22IOSS)
    tempRegCfg3 = (GPIO_PRT_CFG_OUT3(base) & ~(CY_GPIO_CFG_DM_MASK << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET)));

    if(CY_GPIO_DM_CFGOUT3_STRONG_PULLUP_HIGHZ == driveMode)
    {
        /* Enable CFG_OUT3 register and configure the extra drive mode. */
        GPIO_PRT_CFG(base) = tempReg | ((0U & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
        GPIO_PRT_CFG_OUT3(base) = tempRegCfg3 | (((driveMode >> CY_GPIO_EXT_DM_SHIFT) & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
    }
    else
    {
        /* If High-Z drive mode is selected, enable CFG_OUT3 register using CFG register and configure drive mode using CFG_OUT3 register. */
        /* For other drive modes, disable CFG_OUT3 register and use CFG register to configure drive modes. */
        GPIO_PRT_CFG(base) = tempReg | ((driveMode & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
        GPIO_PRT_CFG_OUT3(base) = tempRegCfg3 | ((0U & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
    }
#else
    GPIO_PRT_CFG(base) = tempReg | ((driveMode & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
#endif /* CY_IP_MXS22IOSS */
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}

#if (defined (CY_IP_MXS40SIOSS) &&  ((IOSS_HSIOM_HSIOM_SEC_PORT_NR != 0) || (CPUSS_CM33_0_SECEXT_PRESENT != 0))) || defined (CY_IP_MXS22IOSS)
/*******************************************************************************
* Function Name: Cy_GPIO_Pin_SecFastInit
****************************************************************************//**
*
* Initialize the most common configuration settings for all pin types.
*
* These include, drive mode, initial output value, and HSIOM connection. This
* function should be called from appropriate protection context where secure
* HSIOM port (HSIOM_SECURE_PRT_Type) is accessible.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param driveMode
* Pin drive mode. Options are detailed in \ref group_gpio_driveModes macros
*
* \param outVal
* Logic state of the output buffer driven to the pin (1 or 0)
*
* \param hsiom
* HSIOM input selection
*
* \note
* This function modifies port registers in read-modify-write operations. It is
* not thread safe as the resource is shared among multiple pins on a port.
* You can use the Cy_SysLib_EnterCriticalSection() and
* Cy_SysLib_ExitCriticalSection() functions to ensure that
* Cy_GPIO_Pin_SecFastInit() function execution is not interrupted.
*
* \note
* This API is only available for the CAT1B and CAT1D devices.
*
*******************************************************************************/
void Cy_GPIO_Pin_SecFastInit(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t driveMode,
                                        uint32_t outVal, en_hsiom_sel_t hsiom)
{
    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_DM_VALID(driveMode));
    CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(outVal));
    CY_ASSERT_L2(CY_GPIO_IS_HSIOM_VALID(hsiom));

    uint32_t tempReg;
    uint32_t tempRegCfg3;

    Cy_GPIO_SetHSIOM_SecPin(base, pinNum, 0UL); /* make the pin as secure */

    tempReg = (GPIO_PRT_CFG(base) & ~(CY_GPIO_CFG_DM_MASK << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET)));
#if defined (CY_IP_MXS22IOSS)
    tempRegCfg3 = (GPIO_PRT_CFG_OUT3(base) & ~(CY_GPIO_CFG_DM_MASK << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET)));

    if(driveMode == CY_GPIO_DM_CFGOUT3_STRONG_PULLUP_HIGHZ)
    {
        /* Enable CFG_OUT3 register and configure the extra drive mode. */
        GPIO_PRT_CFG(base) = tempReg | ((0U & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
        GPIO_PRT_CFG_OUT3(base) = tempRegCfg3 | (((driveMode >> CY_GPIO_EXT_DM_SHIFT) & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
    }
    else
    {
        /* If High-Z drive mode is selected, enable CFG_OUT3 register using CFG register and configure drive mode using CFG_OUT3 register. */
        /* For other drive modes, disable CFG_OUT3 register and use CFG register to configure drive modes. */
        GPIO_PRT_CFG(base) = tempReg | ((driveMode & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
        GPIO_PRT_CFG_OUT3(base) = tempRegCfg3 | ((0U & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
    }
#else
    GPIO_PRT_CFG(base) = tempReg | ((driveMode & CY_GPIO_CFG_DM_MASK) << (pinNum << CY_GPIO_DRIVE_MODE_OFFSET));
#endif /* CY_IP_MXS22IOSS */

    Cy_GPIO_SetHSIOM(base, pinNum, hsiom);

    tempReg = (GPIO_PRT_OUT(base) & ~(CY_GPIO_OUT_MASK << pinNum));
    GPIO_PRT_OUT(base) = tempReg | ((outVal & CY_GPIO_OUT_MASK) << pinNum);

}
#endif /* CY_IP_MXS40SIOSS, IOSS_HSIOM_HSIOM_SEC_PORT_NR, CPUSS_CM33_0_SECEXT_PRESENT, CY_IP_MXS22IOSS */

/*******************************************************************************
* Function Name: Cy_GPIO_Port_Deinit
****************************************************************************//**
*
* Reset a complete port of pins back to power on reset defaults.
*
* \param base
* Pointer to the pin's port register base address
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Port_Deinit
*
*******************************************************************************/
void Cy_GPIO_Port_Deinit(GPIO_PRT_Type* base)
{
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    bool secPort;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
    uint32_t portNum;
    HSIOM_PRT_V1_Type* baseHSIOM;
    portNum = ((uint32_t)(base) - CY_GPIO_BASE) / GPIO_PRT_SECTION_SIZE;
    baseHSIOM = (HSIOM_PRT_V1_Type*)(CY_HSIOM_BASE + (HSIOM_PRT_SECTION_SIZE * portNum));
#if defined (CY_IP_MXS40SIOSS) || defined (CY_IP_MXS22IOSS)
#if (IOSS_HSIOM_HSIOM_SEC_PORT_NR != 0) || (CPUSS_CM33_0_SECEXT_PRESENT != 0 )
    HSIOM_SECURE_PRT_Type *baseSecHSIOM;
    baseSecHSIOM = (HSIOM_SECURE_PRT_Type*)(CY_HSIOM_SECURE_BASE + (HSIOM_SECURE_PRT_SECTION_SIZE * portNum));
    HSIOM_SEC_PRT_NONSEC_MASK(baseSecHSIOM) = CY_HSIOM_NONSEC_DEINIT;
#endif /* IOSS_HSIOM_HSIOM_SEC_PORT_NR, CPUSS_CM33_0_SECEXT_PRESENT */
    GPIO_PRT_SLEW_EXT(base)                 = CY_GPIO_PRT_DEINIT;
    GPIO_PRT_DRIVE_EXT0(base)               = CY_GPIO_PRT_DEINIT;
    GPIO_PRT_DRIVE_EXT1(base)               = CY_GPIO_PRT_DEINIT;
#endif /* CY_IP_MXS40SIOSS */

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    secPort = CY_PRA_IS_PORT_SECURE(base);
    if (secPort)
    {
        CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_OUT), CY_GPIO_PRT_DEINIT);
        CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG), CY_GPIO_PRT_DEINIT);
        CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_IN), CY_GPIO_PRT_DEINIT);
        CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_OUT), CY_GPIO_PRT_DEINIT);
        CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_CFG), CY_GPIO_PRT_DEINIT);
        CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_MASK), CY_GPIO_PRT_DEINIT);
        CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO), CY_GPIO_PRT_DEINIT);
        CY_PRA_REG32_SET(CY_PRA_GET_HSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT0), CY_GPIO_PRT_DEINIT);
        CY_PRA_REG32_SET(CY_PRA_GET_HSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT1), CY_GPIO_PRT_DEINIT);

    }
    else
    {
        GPIO_PRT_OUT(base)             = CY_GPIO_PRT_DEINIT;
        GPIO_PRT_CFG(base)             = CY_GPIO_PRT_DEINIT;
        GPIO_PRT_CFG_IN(base)          = CY_GPIO_PRT_DEINIT;
        GPIO_PRT_CFG_OUT(base)         = CY_GPIO_PRT_DEINIT;
        GPIO_PRT_INTR_CFG(base)        = CY_GPIO_PRT_DEINIT;
        GPIO_PRT_INTR_MASK(base)       = CY_GPIO_PRT_DEINIT;
        GPIO_PRT_CFG_SIO(base)         = CY_GPIO_PRT_DEINIT;
        /* For 1M device check for secure HSIOM */
#if defined(CY_DEVICE_PSOC6ABLE2)
        if (CY_PRA_IS_HSIOM_SECURE(base))
        {
            CY_PRA_REG32_SET(CY_PRA_GET_ADJHSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT0), CY_GPIO_PRT_DEINIT);
            CY_PRA_REG32_SET(CY_PRA_GET_ADJHSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT1), CY_GPIO_PRT_DEINIT);
        }
        else
        {
            HSIOM_PRT_PORT_SEL0(baseHSIOM) = CY_GPIO_PRT_DEINIT;
            HSIOM_PRT_PORT_SEL1(baseHSIOM) = CY_GPIO_PRT_DEINIT;
        }
#else
        HSIOM_PRT_PORT_SEL0(baseHSIOM) = CY_GPIO_PRT_DEINIT;
        HSIOM_PRT_PORT_SEL1(baseHSIOM) = CY_GPIO_PRT_DEINIT;
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
    }
#else
    GPIO_PRT_OUT(base)             = CY_GPIO_PRT_DEINIT;
    GPIO_PRT_CFG(base)             = CY_GPIO_PRT_DEINIT;
    GPIO_PRT_CFG_IN(base)          = CY_GPIO_PRT_DEINIT;
    GPIO_PRT_CFG_OUT(base)         = CY_GPIO_PRT_DEINIT;
    GPIO_PRT_INTR_CFG(base)        = CY_GPIO_PRT_DEINIT;
    GPIO_PRT_INTR_MASK(base)       = CY_GPIO_PRT_DEINIT;
    GPIO_PRT_CFG_SIO(base)         = CY_GPIO_PRT_DEINIT;
    HSIOM_PRT_PORT_SEL0(baseHSIOM) = CY_GPIO_PRT_DEINIT;
    HSIOM_PRT_PORT_SEL1(baseHSIOM) = CY_GPIO_PRT_DEINIT;
#if defined (CY_IP_MXS22IOSS)
    GPIO_PRT_CFG_OUT3(base)         = CY_GPIO_PRT_DEINIT;
    GPIO_PRT_CFG_RES(base)          = CY_GPIO_PRT_DEINIT;
#endif /* CY_IP_MXS22IOSS */
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetAmuxSplit
****************************************************************************//**
*
* Configure a specific AMux bus splitter switch cell into a specific
* configuration.
*
* \param switchCtrl
* Selects specific AMux bus splitter cell between two segments.
* The cy_en_amux_split_t enumeration can be found in the GPIO header file
* for the device package.
*
* \param amuxConnect
* Selects configuration of the three switches within the splitter cell
*
* \param amuxBus
* Selects which AMux bus within the splitter is being configured
*
* \note
* This API is available for the CAT1A and CAT1D devices.
*
*******************************************************************************/
void Cy_GPIO_SetAmuxSplit(cy_en_amux_split_t switchCtrl, cy_en_gpio_amuxconnect_t amuxConnect,
                                                         cy_en_gpio_amuxselect_t amuxBus)
{
#if defined (CY_IP_MXS40IOSS) || defined (CY_IP_MXS22IOSS)
    CY_ASSERT_L2(CY_GPIO_IS_AMUX_SPLIT_VALID(switchCtrl));
    CY_ASSERT_L3(CY_GPIO_IS_AMUX_CONNECT_VALID(amuxConnect));
    CY_ASSERT_L3(CY_GPIO_IS_AMUX_SELECT_VALID(amuxBus));

    uint32_t tmpReg;

    if (amuxBus != CY_GPIO_AMUXBUSB)
    {
        tmpReg = HSIOM_AMUX_SPLIT_CTL(switchCtrl) & GPIO_AMUXB_SPLITTER_MASK;
        HSIOM_AMUX_SPLIT_CTL(switchCtrl) = tmpReg | ((uint32_t) amuxConnect & GPIO_AMUXA_SPLITTER_MASK);
    }
    else
    {
        tmpReg = HSIOM_AMUX_SPLIT_CTL(switchCtrl) & GPIO_AMUXA_SPLITTER_MASK;
        HSIOM_AMUX_SPLIT_CTL(switchCtrl) =
        tmpReg | (((uint32_t) amuxConnect << HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_Pos) & GPIO_AMUXB_SPLITTER_MASK);
    }
#else
    (void) switchCtrl;
    (void) amuxConnect;
    (void) amuxBus;

    CY_ASSERT_L2(1);
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetAmuxSplit
****************************************************************************//**
*
* Returns the configuration of a specific AMux bus splitter switch cell.
*
* \param switchCtrl
* Selects specific AMux bus splitter cell between two segments.
* The cy_en_amux_split_t enumeration can be found in the GPIO header file
* for the device package.
*
* \param amuxBus
* Selects which AMux bus within the splitter is being configured
*
* \return
* Returns configuration of the three switches in the selected splitter cell
*
* \note
* This API is available for the CAT1A and CAT1D devices.
*
*******************************************************************************/
cy_en_gpio_amuxconnect_t Cy_GPIO_GetAmuxSplit(cy_en_amux_split_t switchCtrl, cy_en_gpio_amuxselect_t amuxBus)
{
#if defined (CY_IP_MXS40IOSS) || defined (CY_IP_MXS22IOSS)
    CY_ASSERT_L2(CY_GPIO_IS_AMUX_SPLIT_VALID(switchCtrl));
    CY_ASSERT_L3(CY_GPIO_IS_AMUX_SELECT_VALID(amuxBus));

    uint32_t retVal;

    if (amuxBus != CY_GPIO_AMUXBUSB)
    {
        retVal = HSIOM_AMUX_SPLIT_CTL(switchCtrl) & GPIO_AMUXA_SPLITTER_MASK;
    }
    else
    {
        retVal = ((uint32_t) ((HSIOM_AMUX_SPLIT_CTL(switchCtrl) & GPIO_AMUXB_SPLITTER_MASK)
                                                     >> HSIOM_AMUX_SPLIT_CTL_SWITCH_BB_SL_Pos));
    }

    return ((cy_en_gpio_amuxconnect_t) retVal);
#else
    CY_ASSERT_L2(1);

    (void) switchCtrl;
    (void) amuxBus;

    return ((cy_en_gpio_amuxconnect_t) CY_GPIO_AMUX_GLR);
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetHSIOM
****************************************************************************//**
*
* Configures the HSIOM connection to the pin.
*
* Connects the specified High-Speed Input Output Multiplexer (HSIOM) selection
* to the pin.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* HSIOM input selection
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetHSIOM
*
*******************************************************************************/
void Cy_GPIO_SetHSIOM(GPIO_PRT_Type* base, uint32_t pinNum, en_hsiom_sel_t value)
{
    uint32_t portNum;
    uint32_t tempReg;
    uint32_t hsiomReg;
    HSIOM_PRT_V1_Type* portAddrHSIOM;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_HSIOM_VALID(value));

    portNum = ((uint32_t)(base) - CY_GPIO_BASE) / GPIO_PRT_SECTION_SIZE;
    portAddrHSIOM = (HSIOM_PRT_V1_Type*)(CY_HSIOM_BASE + (HSIOM_PRT_SECTION_SIZE * portNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#endif

    if(pinNum < CY_GPIO_PRT_HALF)
    {
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_HSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT0)) & ~(CY_GPIO_HSIOM_MASK << (pinNum << CY_GPIO_HSIOM_OFFSET));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        /* For 1M device check for secure HSIOM */
        if (CY_PRA_IS_HSIOM_SECURE(base))
        {
            tempReg = CY_PRA_REG32_GET(CY_PRA_GET_ADJHSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT0)) & ~(CY_GPIO_HSIOM_MASK << (pinNum << CY_GPIO_HSIOM_OFFSET));
        }
        else
        {
            tempReg = HSIOM_PRT_PORT_SEL0(portAddrHSIOM) & ~(CY_GPIO_HSIOM_MASK << (pinNum << CY_GPIO_HSIOM_OFFSET));
        }
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = HSIOM_PRT_PORT_SEL0(portAddrHSIOM) & ~(CY_GPIO_HSIOM_MASK << (pinNum << CY_GPIO_HSIOM_OFFSET));
#endif
    hsiomReg = tempReg | (((uint32_t)value & CY_GPIO_HSIOM_MASK) << (pinNum << CY_GPIO_HSIOM_OFFSET));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
        if (pinType != CY_PRA_PIN_SECURE)
        {
            if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
            {
                CY_PRA_REG32_SET(CY_PRA_GET_HSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT0), hsiomReg);
            }
            else
            {
                /* For 1M device check for secure HSIOM */
#if defined(CY_DEVICE_PSOC6ABLE2)
                    if (CY_PRA_IS_HSIOM_SECURE(base))
                    {
                        CY_PRA_REG32_SET(CY_PRA_GET_ADJHSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT0), hsiomReg);
                    }
                    else
                    {
                        HSIOM_PRT_PORT_SEL0(portAddrHSIOM) = hsiomReg;
                    }
#else
                    HSIOM_PRT_PORT_SEL0(portAddrHSIOM) = hsiomReg;
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
            }
        }
        else
        {
            /* Secure PIN can't be modified using register policy */
        }
#else
        HSIOM_PRT_PORT_SEL0(portAddrHSIOM) = hsiomReg;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
    }
    else
    {
        pinNum -= CY_GPIO_PRT_HALF;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            tempReg = CY_PRA_REG32_GET(CY_PRA_GET_HSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT1)) & ~(CY_GPIO_HSIOM_MASK << (pinNum << CY_GPIO_HSIOM_OFFSET));
        }
        else if (pinType == CY_PRA_PIN_SECURE_NONE)
        {
            /* For 1M device check for secure HSIOM */
            if (CY_PRA_IS_HSIOM_SECURE(base))
            {
                tempReg = CY_PRA_REG32_GET(CY_PRA_GET_ADJHSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT1)) & ~(CY_GPIO_HSIOM_MASK << (pinNum << CY_GPIO_HSIOM_OFFSET));
            }
            else
            {
                tempReg = HSIOM_PRT_PORT_SEL1(portAddrHSIOM) & ~(CY_GPIO_HSIOM_MASK << (pinNum << CY_GPIO_HSIOM_OFFSET));
            }

        }
        else
        {
            tempReg = 0UL;
        }
#else
        tempReg = HSIOM_PRT_PORT_SEL1(portAddrHSIOM) & ~(CY_GPIO_HSIOM_MASK << (pinNum << CY_GPIO_HSIOM_OFFSET));
#endif

        hsiomReg = tempReg | (((uint32_t)value & CY_GPIO_HSIOM_MASK) << (pinNum << CY_GPIO_HSIOM_OFFSET));
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)

        if (pinType != CY_PRA_PIN_SECURE)
        {
            if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
            {
                CY_PRA_REG32_SET(CY_PRA_GET_HSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT1), hsiomReg);
            }
            else
            {
                /* For 1M device check for secure HSIOM */
#if defined(CY_DEVICE_PSOC6ABLE2)
                    if (CY_PRA_IS_HSIOM_SECURE(base))
                    {
                        CY_PRA_REG32_SET(CY_PRA_GET_ADJHSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT1), hsiomReg);
                    }
                    else
                    {
                        HSIOM_PRT_PORT_SEL1(portAddrHSIOM) = hsiomReg;
                    }
#else
                    HSIOM_PRT_PORT_SEL1(portAddrHSIOM) = hsiomReg;
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
            }
        }
        else
        {
            /* Secure PIN can't be modified using register policy */
        }
#else
        HSIOM_PRT_PORT_SEL1(portAddrHSIOM) = hsiomReg;
#endif
    }
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetHSIOM
****************************************************************************//**
*
* Returns the current HSIOM multiplexer connection to the pin.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* HSIOM input selection
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetHSIOM
*
*******************************************************************************/
en_hsiom_sel_t Cy_GPIO_GetHSIOM(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t returnValue;
    uint32_t tempReg;
    uint32_t portNum;
    HSIOM_PRT_V1_Type* portAddrHSIOM;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

    portNum = ((uint32_t)(base) - CY_GPIO_BASE) / GPIO_PRT_SECTION_SIZE;
    portAddrHSIOM = (HSIOM_PRT_V1_Type*)(CY_HSIOM_BASE + (HSIOM_PRT_SECTION_SIZE * portNum));

    if(pinNum < CY_GPIO_PRT_HALF)
    {
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
        pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            tempReg = CY_PRA_REG32_GET(CY_PRA_GET_HSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT0));
        }
        else if (pinType == CY_PRA_PIN_SECURE_NONE)
        {
            /* For 1M device check for secure HSIOM */
            if (CY_PRA_IS_HSIOM_SECURE(base))
            {
                tempReg = CY_PRA_REG32_GET(CY_PRA_GET_ADJHSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT0));
            }
            else
            {
                tempReg = HSIOM_PRT_PORT_SEL0(portAddrHSIOM);
            }
        }
        else
        {
            /* secure pin */
            tempReg = 0UL;
        }
#else
        tempReg = HSIOM_PRT_PORT_SEL0(portAddrHSIOM);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

        returnValue = (tempReg >> (pinNum << CY_GPIO_HSIOM_OFFSET)) & CY_GPIO_HSIOM_MASK;
    }
    else
    {
        pinNum -= CY_GPIO_PRT_HALF;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
        pinType = CY_PRA_GET_PIN_PROT_TYPE(base, (pinNum + CY_GPIO_PRT_HALF));
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            tempReg = CY_PRA_REG32_GET(CY_PRA_GET_HSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT1));
        }
        else if (pinType == CY_PRA_PIN_SECURE_NONE)
        {
            /* For 1M device check for secure HSIOM */
            if (CY_PRA_IS_HSIOM_SECURE(base))
            {
                tempReg = CY_PRA_REG32_GET(CY_PRA_GET_ADJHSIOM_REG_INDEX(base, CY_PRA_SUB_INDEX_HSIOM_PORT1));
            }
            else
            {
                tempReg = HSIOM_PRT_PORT_SEL1(portAddrHSIOM);
            }
        }
        else
        {
            /* secure pin */
            tempReg = 0UL;
        }
#else
        tempReg = HSIOM_PRT_PORT_SEL1(portAddrHSIOM);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

        returnValue = (tempReg >> (pinNum << CY_GPIO_HSIOM_OFFSET)) & CY_GPIO_HSIOM_MASK;
    }

    return (en_hsiom_sel_t)returnValue;
}


/*******************************************************************************
* Function Name: Cy_GPIO_Read
****************************************************************************//**
*
* Reads the current logic level on the input buffer of the pin.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register.
* Bit position 8 is the routed pin through the port glitch filter.
*
* \return
* Logic level present on the pin
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Read
*
*******************************************************************************/
uint32_t Cy_GPIO_Read(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t tempReg;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    CY_ASSERT_L2(CY_GPIO_IS_FILTER_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_IN));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_IN(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_IN(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> (pinNum)) & CY_GPIO_IN_MASK;
}


/*******************************************************************************
* Function Name: Cy_GPIO_Write
****************************************************************************//**
*
* Write a logic 0 or logic 1 state to the output driver.
*
* This function should be used only for software driven pins. It does not have
* any effect on peripheral driven pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* Logic level to drive out on the pin
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Write
*
*******************************************************************************/
void Cy_GPIO_Write(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
    uint32_t outMask;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(value));

    outMask = CY_GPIO_OUT_MASK << pinNum;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)

    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);

    if (pinType != CY_PRA_PIN_SECURE)
    {
        if(0UL == value)
        {
            if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
            {
                CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_OUT_CLR), outMask);
            }
            else /* non-secure pin */
            {
                GPIO_PRT_OUT_CLR(base) = outMask;
            }
        }
        else
        {
            if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
            {
                CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_OUT_SET), outMask);
            }
            else
            {
                GPIO_PRT_OUT_SET(base) = outMask;
            }
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    /* Thread-safe: Directly access the pin registers instead of base->OUT */
    if(0UL == value)
    {
        GPIO_PRT_OUT_CLR(base) = outMask;
    }
    else
    {
        GPIO_PRT_OUT_SET(base) = outMask;
    }
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_ReadOut
****************************************************************************//**
*
* Reads the current logic level on the pin output driver.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* Logic level on the pin output driver
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_ReadOut
*
*******************************************************************************/
uint32_t Cy_GPIO_ReadOut(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t tempReg;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_OUT));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_OUT(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_OUT(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> pinNum) & CY_GPIO_OUT_MASK;
}


/*******************************************************************************
* Function Name: Cy_GPIO_Set
****************************************************************************//**
*
* Set a pin output to logic state high.
*
* This function should be used only for software driven pins. It does not have
* any effect on peripheral driven pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Set
*
*******************************************************************************/
void Cy_GPIO_Set(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t outMask;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

    outMask = CY_GPIO_OUT_MASK << pinNum;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);

    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_OUT_SET), outMask);
        }
        else
        {
            GPIO_PRT_OUT_SET(base) = outMask;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_OUT_SET(base) = outMask;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_Clr
****************************************************************************//**
*
* Set a pin output to logic state Low.
*
* This function should be used only for software driven pins. It does not have
* any effect on peripheral driven pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Clr
*
*******************************************************************************/
void Cy_GPIO_Clr(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t outMask;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

    outMask = CY_GPIO_OUT_MASK << pinNum;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);

    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_OUT_CLR), outMask);
        }
        else
        {
            GPIO_PRT_OUT_CLR(base) = outMask;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_OUT_CLR(base) = outMask;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_Inv
****************************************************************************//**
*
* Set a pin output logic state to the inverse of the current output
* logic state.
*
* This function should be used only for software driven pins. It does not have
* any effect on peripheral driven pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Inv
*
*******************************************************************************/
void Cy_GPIO_Inv(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t outMask;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

    outMask = CY_GPIO_OUT_MASK << pinNum;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);

    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_OUT_INV), outMask);
        }
        else
        {
            GPIO_PRT_OUT_INV(base) = outMask;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_OUT_INV(base) = outMask;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetDrivemode
****************************************************************************//**
*
* Configures the pin output buffer drive mode and input buffer enable.
*
* The output buffer drive mode and input buffer enable are combined into a single
* parameter. The drive mode controls the behavior of the pin in general.
* Enabling the input buffer allows the digital pin state to be read but also
* contributes to extra current consumption.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* Pin drive mode. Options are detailed in \ref group_gpio_driveModes macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetDrivemode
*
*******************************************************************************/
void Cy_GPIO_SetDrivemode(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
    uint32_t tempReg;
    uint32_t pinLoc;
    uint32_t prtCfg;
#if defined (CY_IP_MXS22IOSS)
    uint32_t prtCfg3;
    uint32_t tempRegCfg3;
#endif /* CY_IP_MXS22IOSS */
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_DM_VALID(value));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    pinLoc = pinNum << CY_GPIO_DRIVE_MODE_OFFSET;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = (CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG)) & ~(CY_GPIO_CFG_DM_MASK << pinLoc));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = (GPIO_PRT_CFG(base) & ~(CY_GPIO_CFG_DM_MASK << pinLoc));
    }
    else
    {
        /* secure pin */
        tempReg = 0;
    }
#else
    tempReg = (GPIO_PRT_CFG(base) & ~(CY_GPIO_CFG_DM_MASK << pinLoc));
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

#if defined (CY_IP_MXS22IOSS)
    tempRegCfg3 = (GPIO_PRT_CFG_OUT3(base) & ~(CY_GPIO_CFG_DM_MASK << pinLoc));
    if(CY_GPIO_DM_CFGOUT3_STRONG_PULLUP_HIGHZ == value)
    {
        prtCfg = tempReg | (0U << pinLoc);
        prtCfg3 = tempRegCfg3 | ((value >> CY_GPIO_EXT_DM_SHIFT) << pinLoc);
    }
    else
    {
        prtCfg = tempReg | ((value & CY_GPIO_CFG_DM_MASK) << pinLoc);
        prtCfg3 = tempRegCfg3 | (0U << pinLoc);
    }
#else
    prtCfg = tempReg | ((value & CY_GPIO_CFG_DM_MASK) << pinLoc);
#endif /* CY_IP_MXS22IOSS */

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG), prtCfg);
        }
        else
        {
            GPIO_PRT_CFG(base) = prtCfg;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_CFG(base) = prtCfg;
#if defined (CY_IP_MXS22IOSS)
    GPIO_PRT_CFG_OUT3(base) = prtCfg3;
#endif /* CY_IP_MXS22IOSS */
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetDrivemode
****************************************************************************//**
*
* Returns the pin output buffer drive mode and input buffer enable state.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* Pin drive mode. Options are detailed in \ref group_gpio_driveModes macros
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetDrivemode
*
*******************************************************************************/
uint32_t Cy_GPIO_GetDrivemode(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t tempReg, ret;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

#if defined (CY_IP_MXS22IOSS)
    /* Check drive mode value in CFG_OUT3 register if CFG_OUT3 is enabled */
    if((((tempReg >> (pinNum << CY_GPIO_DRIVE_MODE_OFFSET)) & CY_GPIO_CFG_DM_MASK) & CY_GPIO_CFG_DM_NO_INBUF_MASK) == 0U)
    {
        tempReg = GPIO_PRT_CFG_OUT3(base);
        ret = ((tempReg >> (pinNum << CY_GPIO_DRIVE_MODE_OFFSET)) & CY_GPIO_CFG_DM_MASK) << CY_GPIO_EXT_DM_SHIFT;
    }
#endif /* CY_IP_MXS22IOSS */

    ret = (tempReg >> (pinNum << CY_GPIO_DRIVE_MODE_OFFSET)) & CY_GPIO_CFG_DM_MASK;
    return ret;
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetVtrip
****************************************************************************//**
*
* Configures the GPIO pin input buffer voltage threshold mode.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* Pin voltage threshold mode. Options are detailed in \ref group_gpio_vtrip macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetVtrip
*
*******************************************************************************/
void Cy_GPIO_SetVtrip(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
    uint32_t tempReg;
    uint32_t cfgIn;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(value));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);

#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_IN)) & ~(CY_GPIO_CFG_IN_VTRIP_SEL_0_MASK << pinNum);
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_IN(base) & ~(CY_GPIO_CFG_IN_VTRIP_SEL_0_MASK << pinNum);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_IN(base) & ~(CY_GPIO_CFG_IN_VTRIP_SEL_0_MASK << pinNum);
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg = GPIO_PRT_CFG_IN(base) & ~(CY_GPIO_CFG_IN_VTRIP_SEL_0_MASK << pinNum);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    cfgIn = tempReg | ((value & CY_GPIO_CFG_IN_VTRIP_SEL_0_MASK) << pinNum);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_IN), cfgIn);
        }
        else
        {
            GPIO_PRT_CFG_IN(base) = cfgIn;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_CFG_IN(base) = cfgIn;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetVtrip
****************************************************************************//**
*
* Returns the pin input buffer voltage threshold mode.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* Pin voltage threshold mode. Options are detailed in \ref group_gpio_vtrip macros
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetVtrip
*
*******************************************************************************/
uint32_t Cy_GPIO_GetVtrip(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t tempReg;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_IN));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_IN(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_IN(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> pinNum) & CY_GPIO_CFG_IN_VTRIP_SEL_0_MASK;
}

#if (defined(CY_IP_MXS40IOSS) && (CY_IP_MXS40IOSS_VERSION == 3U)) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_GPIO_SetVtripAuto
****************************************************************************//**
*
* Configures the GPIO pin input buffer for automotive compatible or not.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* Pin voltage threshold mode. Options are detailed in
* \ref group_gpio_vtrip_auto macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_GPIO_SetVtripAuto(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
    uint32_t tempReg;
    uint32_t vtripSel;

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(value));

    tempReg = GPIO_PRT_CFG_IN_AUTOLVL(base) & ~(CY_GPIO_CFG_IN_VTRIP_SEL_1_MASK << pinNum);
    vtripSel = tempReg | ((value & CY_GPIO_CFG_IN_VTRIP_SEL_1_MASK) << pinNum);
    GPIO_PRT_CFG_IN_AUTOLVL(base) = vtripSel;
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetVtripAuto
****************************************************************************//**
*
* Returns the pin input buffer voltage whether it is automotive compatible or not.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* Pin voltage for automotive or not. Options are detailed in
* \ref group_gpio_vtrip_auto macros
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_GPIO_GetVtripAuto(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t tempReg;

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

    tempReg = GPIO_PRT_CFG_IN_AUTOLVL(base);

    return (tempReg >> pinNum) & CY_GPIO_CFG_IN_VTRIP_SEL_1_MASK;
}
#endif /* CY_IP_MXS40IOSS_VERSION */
/*******************************************************************************
* Function Name: Cy_GPIO_SetSlewRate
****************************************************************************//**
*
* Configures the pin output buffer slew rate.
* GPIO pins have fast and slow output slew rate options for the strong drivers
* configured using this API. By default the port works in fast slew mode.
* Slower slew rate results in reduced EMI and crosstalk and are recommended for
* low-frequency signals or signals without strict timing constraints.
*
* \note
* This function has no effect for the GPIO ports, where the slew rate
* configuration is not available. Refer to device datasheet for details.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* Pin slew rate. Options are detailed in \ref group_gpio_slewRate macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetSlewRate
*
*******************************************************************************/
void Cy_GPIO_SetSlewRate(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
    uint32_t tempReg;
#if defined (CY_IP_MXS40SIOSS) || defined (CY_IP_MXS22IOSS)
    uint32_t pinLoc;
#else
    uint32_t cfgOut;
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(value));

#if defined (CY_IP_MXS40SIOSS) || defined (CY_IP_MXS22IOSS)
    pinLoc = pinNum << CY_GPIO_CFG_SLEW_EXT_OFFSET;
    tempReg = (GPIO_PRT_SLEW_EXT(base) & ~(CY_GPIO_CFG_SLEW_EXT_MASK << pinLoc));
    GPIO_PRT_SLEW_EXT(base) = tempReg | ((value & CY_GPIO_CFG_SLEW_EXT_MASK) << pinLoc);
#else

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_OUT)) & ~(CY_GPIO_CFG_OUT_SLOW_MASK << pinNum);
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_OUT(base) & ~(CY_GPIO_CFG_OUT_SLOW_MASK << pinNum);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_OUT(base) & ~(CY_GPIO_CFG_OUT_SLOW_MASK << pinNum);
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg = GPIO_PRT_CFG_OUT(base) & ~(CY_GPIO_CFG_OUT_SLOW_MASK << pinNum);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
    cfgOut = tempReg | ((value & CY_GPIO_CFG_OUT_SLOW_MASK) << pinNum);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_OUT), cfgOut);
        }
        else
        {
            GPIO_PRT_CFG_OUT(base) = cfgOut;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_CFG_OUT(base) = cfgOut;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetSlewRate
****************************************************************************//**
*
* Returns the pin output buffer slew rate.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* Pin slew rate. Options are detailed in \ref group_gpio_slewRate macros
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetSlewRate
*
*******************************************************************************/
uint32_t Cy_GPIO_GetSlewRate(GPIO_PRT_Type* base, uint32_t pinNum)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */
#endif /* defined (CY_IP_MXS40IOSS) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

#if defined (CY_IP_MXS40IOSS)

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_OUT));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_OUT(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_OUT(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> pinNum) & CY_GPIO_CFG_OUT_SLOW_MASK;
#else
    return (GPIO_PRT_SLEW_EXT(base) >> (pinNum << CY_GPIO_CFG_SLEW_EXT_OFFSET)) & CY_GPIO_CFG_SLEW_EXT_MASK;
#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetDriveSel
****************************************************************************//**
*
* Configures the pin output buffer drive strength.
* The drive strength field determines the active portion of the output drivers
* used and can affect the slew rate of output signals. Drive strength options
* are full drive strength (default), one-half strength, one-quarter strength,
* and oneeighth strength. Drive strength must be set to full drive strength when
* the slow slew rate bit (SLOW) is set.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register.
*
* \param value
* Pin drive strength. Options are detailed in \ref group_gpio_driveStrength macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetDriveSel
*
*******************************************************************************/
void Cy_GPIO_SetDriveSel(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
    uint32_t tempReg;
#if defined (CY_IP_MXS40IOSS)
    uint32_t pinLoc;
    uint32_t cfgOut;
#endif /* CY_IP_MXS40IOSS */

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_DRIVE_SEL_VALID(value));

#if defined (CY_IP_MXS40IOSS)
    pinLoc = (uint32_t)(pinNum << 1u) + CY_GPIO_CFG_OUT_DRIVE_OFFSET;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_OUT)) & ~(CY_GPIO_CFG_OUT_DRIVE_SEL_MASK << pinLoc);
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_OUT(base) & ~(CY_GPIO_CFG_OUT_DRIVE_SEL_MASK << pinLoc);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_OUT(base) & ~(CY_GPIO_CFG_OUT_DRIVE_SEL_MASK << pinLoc);
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg = GPIO_PRT_CFG_OUT(base) & ~(CY_GPIO_CFG_OUT_DRIVE_SEL_MASK << pinLoc);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
    cfgOut = tempReg | ((value & CY_GPIO_CFG_OUT_DRIVE_SEL_MASK) << pinLoc);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_OUT), cfgOut);
        }
        else
        {
            GPIO_PRT_CFG_OUT(base) = cfgOut;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_CFG_OUT(base) = cfgOut;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
#else
    if(pinNum < CY_GPIO_PRT_HALF)
    {
        tempReg = GPIO_PRT_DRIVE_EXT0(base) & ~(CY_GPIO_CFG_DRIVE_SEL_EXT_MASK << (pinNum << CY_GPIO_CFG_DRIVE_SEL_EXT_OFFSET));
        GPIO_PRT_DRIVE_EXT0(base) = tempReg | ((value & CY_GPIO_CFG_DRIVE_SEL_EXT_MASK) << (pinNum << CY_GPIO_CFG_DRIVE_SEL_EXT_OFFSET));
    }
    else
    {
        pinNum -= CY_GPIO_PRT_HALF;
        tempReg = GPIO_PRT_DRIVE_EXT1(base) & ~(CY_GPIO_CFG_DRIVE_SEL_EXT_MASK << (pinNum << CY_GPIO_CFG_DRIVE_SEL_EXT_OFFSET));
        GPIO_PRT_DRIVE_EXT1(base) = tempReg | ((value & CY_GPIO_CFG_DRIVE_SEL_EXT_MASK) << (pinNum << CY_GPIO_CFG_DRIVE_SEL_EXT_OFFSET));
    }
#endif /* CY_IP_MXS40SIOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetDriveSel
****************************************************************************//**
*
* Returns the pin output buffer drive strength.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* Pin drive strength. Options are detailed in \ref group_gpio_driveStrength macros
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetDriveSel
*
*******************************************************************************/
uint32_t Cy_GPIO_GetDriveSel(GPIO_PRT_Type* base, uint32_t pinNum)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */
#endif /* defined (CY_IP_MXS40IOSS) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

#if defined (CY_IP_MXS40IOSS)
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_OUT));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_OUT(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_OUT(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return ((tempReg >> ((uint32_t)(pinNum << 1u) + CY_GPIO_CFG_OUT_DRIVE_OFFSET))
            & CY_GPIO_CFG_OUT_DRIVE_SEL_MASK);
#else
    uint32_t returnValue;
    if(pinNum < CY_GPIO_PRT_HALF)
    {
        returnValue = (GPIO_PRT_DRIVE_EXT0(base) >> (pinNum << CY_GPIO_CFG_DRIVE_SEL_EXT_OFFSET)) & CY_GPIO_CFG_DRIVE_SEL_EXT_MASK;
    }
    else
    {
        pinNum -= CY_GPIO_PRT_HALF;
        returnValue = (GPIO_PRT_DRIVE_EXT1(base) >> (pinNum << CY_GPIO_CFG_DRIVE_SEL_EXT_OFFSET)) & CY_GPIO_CFG_DRIVE_SEL_EXT_MASK;
    }
    return returnValue;
#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetVregEn
****************************************************************************//**
*
* Configures the SIO pin pair output buffer regulation mode.
*
* Note that this function has no effect on non-SIO pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* SIO pair output buffer regulator mode. Options are detailed in \ref group_gpio_sioVreg macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetVregEn
*
*******************************************************************************/
void Cy_GPIO_SetVregEn(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;
    uint32_t pinLoc;
    uint32_t cfgSio;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(value));

    pinLoc = (pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO)) & ~(CY_GPIO_VREG_EN_MASK << pinLoc);
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VREG_EN_MASK << pinLoc);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VREG_EN_MASK << pinLoc);
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg = GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VREG_EN_MASK << pinLoc);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
    cfgSio = tempReg | ((value & CY_GPIO_VREG_EN_MASK) << pinLoc);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO), cfgSio);
        }
        else
        {
            GPIO_PRT_CFG_SIO(base) = cfgSio;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_CFG_SIO(base) = cfgSio;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
#else
    CY_ASSERT_L2(1);
    (void) base;
    (void) pinNum;
    (void) value;

#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetVregEn
****************************************************************************//**
*
* Returns the SIO pin pair output buffer regulation mode.
*
* Note that this function has no effect on non-SIO pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* SIO pair output buffer regulator mode. Options are detailed in \ref group_gpio_sioVreg macros
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetVregEn
*
*******************************************************************************/
uint32_t Cy_GPIO_GetVregEn(GPIO_PRT_Type* base, uint32_t pinNum)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;
    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_SIO(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_SIO(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */


    return (tempReg >> ((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET)) & CY_GPIO_VREG_EN_MASK;
#else
    CY_ASSERT_L2(1);

    (void) base;
    (void) pinNum;

    return CYRET_INVALID_STATE;
#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetIbufMode
****************************************************************************//**
*
* Configures the SIO pin pair input buffer mode.
*
* Note that this function has no effect on non-SIO pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* SIO pair input buffer mode. Options are detailed in \ref group_gpio_sioIbuf macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetIbufMode
*
*******************************************************************************/
void Cy_GPIO_SetIbufMode(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;
    uint32_t pinLoc;
    uint32_t cfgSio;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(value));

    pinLoc = ((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_IBUF_SHIFT;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = (CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO)) &  ~(CY_GPIO_IBUF_MASK << pinLoc));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_IBUF_MASK << pinLoc));
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_IBUF_MASK << pinLoc));
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_IBUF_MASK << pinLoc));
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    cfgSio = tempReg | ((value & CY_GPIO_IBUF_MASK) << pinLoc);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO), cfgSio);
        }
        else
        {
            GPIO_PRT_CFG_SIO(base) = cfgSio;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_CFG_SIO(base) = cfgSio;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
#else
    CY_ASSERT_L2(1);
    (void) base;
    (void) pinNum;
    (void) value;

#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetIbufMode
****************************************************************************//**
*
* Returns the SIO pin pair input buffer mode.
*
* Note that this function has no effect on non-SIO pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* SIO pair input buffer mode. Options are detailed in \ref group_gpio_sioIbuf macros
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetIbufMode
*
*******************************************************************************/
uint32_t Cy_GPIO_GetIbufMode(GPIO_PRT_Type* base, uint32_t pinNum)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_SIO(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_SIO(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> (((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_IBUF_SHIFT)) & CY_GPIO_IBUF_MASK;
#else
    CY_ASSERT_L2(1);

    (void) base;
    (void) pinNum;

    return CYRET_INVALID_STATE;
#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetVtripSel
****************************************************************************//**
*
* Configures the SIO pin pair input buffer trip point.
*
* Note that this function has no effect on non-SIO pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* SIO pair input buffer trip point. Options are detailed in \ref group_gpio_sioVtrip macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetVtripSel
*
*******************************************************************************/
void Cy_GPIO_SetVtripSel(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;
    uint32_t pinLoc;
    uint32_t cfgSio;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(value));

    pinLoc = ((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_VTRIP_SEL_SHIFT;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = (CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO)) & ~(CY_GPIO_VTRIP_SEL_MASK << pinLoc));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VTRIP_SEL_MASK << pinLoc));
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VTRIP_SEL_MASK << pinLoc));
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VTRIP_SEL_MASK << pinLoc));
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    cfgSio = tempReg | ((value & CY_GPIO_VTRIP_SEL_MASK) << pinLoc);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO), cfgSio);
        }
        else
        {
            GPIO_PRT_CFG_SIO(base) = cfgSio;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_CFG_SIO(base) = cfgSio;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
#else
        (void) base;
        (void) pinNum;
        (void) value;

        CY_ASSERT_L2(1);
#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetVtripSel
****************************************************************************//**
*
* Returns the SIO pin pair input buffer trip point.
*
* Note that this function has no effect on non-SIO pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* SIO pair input buffer trip point. Options are detailed in \ref group_gpio_sioVtrip macros
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetVtripSel
*
*******************************************************************************/
uint32_t Cy_GPIO_GetVtripSel(GPIO_PRT_Type* base, uint32_t pinNum)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_SIO(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_SIO(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> (((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_VTRIP_SEL_SHIFT)) & CY_GPIO_VTRIP_SEL_MASK;
#else
    CY_ASSERT_L2(1);

    (void) base;
    (void) pinNum;

    return CYRET_INVALID_STATE;
#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetVrefSel
****************************************************************************//**
*
* Configures the SIO reference voltage for the input buffer trip point.
*
* Note that this function has no effect on non-SIO pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* SIO pair reference voltage. Options are detailed in \ref group_gpio_sioVref macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetVrefSel
*
*******************************************************************************/
void Cy_GPIO_SetVrefSel(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;
    uint32_t pinLoc;
    uint32_t cfgSio;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_VREF_SEL_VALID(value));

    pinLoc = ((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_VREF_SEL_SHIFT;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = (CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO)) & ~(CY_GPIO_VREF_SEL_MASK << pinLoc));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VREF_SEL_MASK << pinLoc));
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VREF_SEL_MASK << pinLoc));
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VREF_SEL_MASK << pinLoc));
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    cfgSio = tempReg | ((value & CY_GPIO_VREF_SEL_MASK) << pinLoc);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO), cfgSio);
        }
        else
        {
            GPIO_PRT_CFG_SIO(base) = cfgSio;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_CFG_SIO(base) = cfgSio;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
#else
    (void) base;
    (void) pinNum;
    (void) value;

    CY_ASSERT_L2(1);
#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetVrefSel
****************************************************************************//**
*
* Returns the SIO reference voltage for the input buffer trip point.
*
* Note that this function has no effect on non-SIO pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* SIO pair reference voltage. Options are detailed in \ref group_gpio_sioVref macros
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetVrefSel
*
*******************************************************************************/
uint32_t Cy_GPIO_GetVrefSel(GPIO_PRT_Type* base, uint32_t pinNum)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;
    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_SIO(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_SIO(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> (((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_VREF_SEL_SHIFT)) & CY_GPIO_VREF_SEL_MASK;
#else
    CY_ASSERT_L2(1);

    (void) base;
    (void) pinNum;

    return CYRET_INVALID_STATE;
#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetVohSel
****************************************************************************//**
*
* Configures the regulated output reference multiplier for the SIO pin pair.
*
* The regulated output reference controls both the output level of digital output
* pin and the input trip point of digital input pin in the SIO pair.
*
* Note that this function has no effect on non-SIO pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* SIO pair reference voltage. Options are detailed in \ref group_gpio_sioVoh macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetVohSel
*
*******************************************************************************/
void Cy_GPIO_SetVohSel(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;
    uint32_t pinLoc;
    uint32_t cfgSio;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_VOH_SEL_VALID(value));

    pinLoc = ((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_VOH_SEL_SHIFT;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = (CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO)) & ~(CY_GPIO_VOH_SEL_MASK << pinLoc));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VOH_SEL_MASK << pinLoc));
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VOH_SEL_MASK << pinLoc));
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg = (GPIO_PRT_CFG_SIO(base) & ~(CY_GPIO_VOH_SEL_MASK << pinLoc));
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
    cfgSio = tempReg | ((value & CY_GPIO_VOH_SEL_MASK) << pinLoc);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO), cfgSio);
        }
        else
        {
            GPIO_PRT_CFG_SIO(base) = cfgSio;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_CFG_SIO(base) = cfgSio;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
#else
    CY_ASSERT_L2(1);
    (void) base;
    (void) pinNum;
    (void) value;

#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetVohSel
****************************************************************************//**
*
* Returns the regulated output reference multiplier for the SIO pin pair.
*
* Note that this function has no effect on non-SIO pins.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* SIO pair reference voltage. Options are detailed in \ref group_gpio_sioVoh macros
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetVohSel
*
*******************************************************************************/
uint32_t Cy_GPIO_GetVohSel(GPIO_PRT_Type* base, uint32_t pinNum)
{
#if defined (CY_IP_MXS40IOSS)
    uint32_t tempReg;
    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_CFG_SIO));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_CFG_SIO(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_CFG_SIO(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> (((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_VOH_SEL_SHIFT)) & CY_GPIO_VOH_SEL_MASK;
#else
    CY_ASSERT_L2(1);
    (void) base;
    (void) pinNum;

    return CYRET_INVALID_STATE;
#endif /* CY_IP_MXS40IOSS */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetInterruptStatus
****************************************************************************//**
*
* Returns the current unmasked interrupt state of the pin.
*
* The core processor's NVIC is triggered by the masked interrupt bits. This
* function allows reading the unmasked interrupt state. Whether the bit
* positions actually trigger the interrupt are defined by the interrupt mask bits.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
* Bit position 8 is the routed pin through the port glitch filter.
*
* \return
* 0 = Pin interrupt condition not detected
* 1 = Pin interrupt condition detected
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_GetInterruptStatus
*
*******************************************************************************/
uint32_t Cy_GPIO_GetInterruptStatus(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t tempReg;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    CY_ASSERT_L2(CY_GPIO_IS_FILTER_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_INTR(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_INTR(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> pinNum) & CY_GPIO_INTR_STATUS_MASK;
}


/*******************************************************************************
* Function Name: Cy_GPIO_ClearInterrupt
****************************************************************************//**
*
* Clears the triggered pin interrupt.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
* Bit position 8 is the routed pin through the port glitch filter.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_ClearInterrupt
*
*******************************************************************************/
void Cy_GPIO_ClearInterrupt(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t prtIntr;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_FILTER_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        (void)CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        /* Any INTR MMIO registers AHB clearing must be preceded with an AHB read access */
        (void)GPIO_PRT_INTR(base);
    }
    else
    {
        /* secure pin */
    }
#else
    /* Any INTR MMIO registers AHB clearing must be preceded with an AHB read access */
    (void)GPIO_PRT_INTR(base);
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    /* Any INTR MMIO registers AHB clearing must be preceded with an AHB read access */
    (void)GPIO_PRT_INTR(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    prtIntr = CY_GPIO_INTR_STATUS_MASK << pinNum;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR), prtIntr);
        }
        else
        {
            GPIO_PRT_INTR(base) = prtIntr;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_INTR(base) = prtIntr;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    /* This read ensures that the initial write has been flushed out to the hardware */
    (void)GPIO_PRT_INTR(base);
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetInterruptMask
****************************************************************************//**
*
* Configures the pin interrupt to be forwarded to the CPU NVIC.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register.
* Bit position 8 is the routed pin through the port glitch filter.
*
* \param value
* 0 = Pin interrupt not forwarded to CPU interrupt controller
* 1 = Pin interrupt masked and forwarded to CPU interrupt controller
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetInterruptMask
*
*******************************************************************************/
void Cy_GPIO_SetInterruptMask(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
    uint32_t tempReg;
    uint32_t intrMask;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_FILTER_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_VALUE_VALID(value));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg= CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_MASK)) & ~(CY_GPIO_INTR_EN_MASK << pinNum);
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg= GPIO_PRT_INTR_MASK(base) & ~(CY_GPIO_INTR_EN_MASK << pinNum);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg= GPIO_PRT_INTR_MASK(base) & ~(CY_GPIO_INTR_EN_MASK << pinNum);
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg= GPIO_PRT_INTR_MASK(base) & ~(CY_GPIO_INTR_EN_MASK << pinNum);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    intrMask = tempReg | ((value & CY_GPIO_INTR_EN_MASK) << pinNum);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_MASK), intrMask);
        }
        else
        {
            GPIO_PRT_INTR_MASK(base) = intrMask;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_INTR_MASK(base) = intrMask;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetInterruptMask
****************************************************************************//**
*
* Returns the state of the pin interrupt mask.
*
* This mask is used to determine whether the pin is configured to be forwarded
* to the CPU NVIC.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register.
* Bit position 8 is the routed pin through the port glitch filter.
*
* \return
* 0 = Pin interrupt not forwarded to CPU interrupt controller
* 1 = Pin interrupt masked and forwarded to CPU interrupt controller
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetInterruptMask
*
*******************************************************************************/
uint32_t Cy_GPIO_GetInterruptMask(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t tempReg;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    CY_ASSERT_L2(CY_GPIO_IS_FILTER_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_MASK));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_INTR_MASK(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_INTR_MASK(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> pinNum) & CY_GPIO_INTR_EN_MASK;
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetInterruptStatusMasked
****************************************************************************//**
*
* Return the pin's current interrupt state after being masked.
*
* The core processor's NVIC is triggered by the masked interrupt bits. This
* function allows reading this masked interrupt state. Note that the bits that
* are not masked will not be forwarded to the NVIC.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register.
* Bit position 8 is the routed pin through the port glitch filter.
*
* \return
* 0 = Pin interrupt not detected or not forwarded to CPU interrupt controller
* 1 = Pin interrupt detected and forwarded to CPU interrupt controller
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_GetInterruptStatusMasked
*
*******************************************************************************/
uint32_t Cy_GPIO_GetInterruptStatusMasked(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t tempReg;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    CY_ASSERT_L2(CY_GPIO_IS_FILTER_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_MASKED));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_INTR_MASKED(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_INTR_MASKED(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> pinNum) & CY_GPIO_INTR_MASKED_MASK;
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetSwInterrupt
****************************************************************************//**
*
* Force a pin interrupt to trigger.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register.
* Bit position 8 is the routed pin through the port glitch filter.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetSwInterrupt
*
*******************************************************************************/
void Cy_GPIO_SetSwInterrupt(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t intrSet;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_FILTER_PIN_VALID(pinNum));

    intrSet = CY_GPIO_INTR_SET_MASK << pinNum;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);

    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_SET), intrSet);
        }
        else
        {
            GPIO_PRT_INTR_SET(base) = intrSet;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_INTR_SET(base) = intrSet;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetInterruptEdge
****************************************************************************//**
*
* Configures the type of edge that will trigger a pin interrupt.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register.
* Bit position 8 is the routed pin through the port glitch filter.
*
* \param value
* Pin interrupt mode. Options are detailed in \ref group_gpio_interruptTrigger macros
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetInterruptEdge
*
*******************************************************************************/
void Cy_GPIO_SetInterruptEdge(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
    uint32_t tempReg;
    uint32_t pinLoc;
    uint32_t intrCfg;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_FILTER_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_INT_EDGE_VALID(value));

    pinLoc = pinNum << CY_GPIO_INTR_CFG_OFFSET;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg= CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_CFG)) & ~(CY_GPIO_INTR_EDGE_MASK << pinLoc);
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_INTR_CFG(base) & ~(CY_GPIO_INTR_EDGE_MASK << pinLoc);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_INTR_CFG(base) & ~(CY_GPIO_INTR_EDGE_MASK << pinLoc);
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg = GPIO_PRT_INTR_CFG(base) & ~(CY_GPIO_INTR_EDGE_MASK << pinLoc);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    intrCfg = tempReg | ((value & CY_GPIO_INTR_EDGE_MASK) << pinLoc);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_CFG), intrCfg);
        }
        else
        {
            GPIO_PRT_INTR_CFG(base) = intrCfg;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_INTR_CFG(base) = intrCfg;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetInterruptEdge
****************************************************************************//**
*
* Returns the current pin interrupt edge type.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register.
* Bit position 8 is the routed pin through the port glitch filter.
*
* \return
* Pin interrupt mode. Options are detailed in \ref group_gpio_interruptTrigger macros
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetInterruptEdge
*
*******************************************************************************/
uint32_t Cy_GPIO_GetInterruptEdge(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t tempReg;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    CY_ASSERT_L2(CY_GPIO_IS_FILTER_PIN_VALID(pinNum));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, pinNum);
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_CFG));
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_INTR_CFG(base);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_INTR_CFG(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return (tempReg >> (pinNum << CY_GPIO_INTR_CFG_OFFSET)) & CY_GPIO_INTR_EDGE_MASK;
}


/*******************************************************************************
* Function Name: Cy_GPIO_SetFilter
****************************************************************************//**
*
* Configures which pin on the port connects to the port-specific glitch filter.
*
* Each port contains a single 50ns glitch filter. Any of the pins on the port
* can be routed to this filter such that the input signal is filtered before
* reaching the edge-detect interrupt circuitry. The state of the filtered pin
* can also be read by calling the Cy_GPIO_Read() function.
*
* \param base
* Pointer to the pin's port register base address
*
* \param value
* The number of the port pin to route to the port filter (0...7)
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \note
* The filtered pin does not have an associated HSIOM connection. Therefore
* it cannot be routed directly to other peripherals in hardware.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetFilter
*
*******************************************************************************/
void Cy_GPIO_SetFilter(GPIO_PRT_Type* base, uint32_t value)
{
    uint32_t tempReg;
    uint32_t intrCfg;

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    cy_en_pra_pin_prot_type_t pinType;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(value));

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    pinType = CY_PRA_GET_PIN_PROT_TYPE(base, value);
#if defined(CY_DEVICE_PSOC6ABLE2)
    if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
    {
        tempReg= CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_CFG)) & ~(CY_GPIO_INTR_FLT_EDGE_MASK << CY_GPIO_INTR_FILT_OFFSET);
    }
    else if (pinType == CY_PRA_PIN_SECURE_NONE)
    {
        tempReg = GPIO_PRT_INTR_CFG(base) & ~(CY_GPIO_INTR_FLT_EDGE_MASK << CY_GPIO_INTR_FILT_OFFSET);
    }
    else
    {
        /* secure pin */
        tempReg = 0UL;
    }
#else
    tempReg = GPIO_PRT_INTR_CFG(base) & ~(CY_GPIO_INTR_FLT_EDGE_MASK << CY_GPIO_INTR_FILT_OFFSET);
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#else
    tempReg = GPIO_PRT_INTR_CFG(base) & ~(CY_GPIO_INTR_FLT_EDGE_MASK << CY_GPIO_INTR_FILT_OFFSET);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */

    intrCfg = tempReg | ((value & CY_GPIO_INTR_FLT_EDGE_MASK) << CY_GPIO_INTR_FILT_OFFSET);

#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE)
    if (pinType != CY_PRA_PIN_SECURE)
    {
        if (pinType == CY_PRA_PIN_SECURE_UNCONSTRAINED)
        {
            CY_PRA_REG32_SET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_CFG), intrCfg);
        }
        else
        {
            GPIO_PRT_INTR_CFG(base) = intrCfg;
        }
    }
    else
    {
        /* Secure PIN can't be modified using register policy */
    }
#else
    GPIO_PRT_INTR_CFG(base) = intrCfg;
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) */
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetFilter
****************************************************************************//**
*
* Returns which pin is currently configured to connect to the port-specific
* glitch filter.
*
* Each port contains a single 50ns glitch filter. Any of the pins on the port
* can be routed to this filter such that the input signal is filtered before
* reaching the edge-detect interrupt circuitry. The state of the filtered pin
* can also be read by calling the Cy_GPIO_Read() function.
*
* \param base
* Pointer to the pin's port register base address
*
* \return
* The number of the port pin routed to the port filter (0...7)
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetFilter
*
*******************************************************************************/
uint32_t Cy_GPIO_GetFilter(GPIO_PRT_Type* base)
{
    uint32_t tempReg;
#if (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    if (CY_PRA_IS_PORT_SECURE(base))
    {
        tempReg = CY_PRA_REG32_GET(CY_PRA_GET_PORT_REG_INDEX(base, CY_PRA_SUB_INDEX_PORT_INTR_CFG));
    }
    else
    {
        tempReg = GPIO_PRT_INTR_CFG(base);
    }
#else
    tempReg = GPIO_PRT_INTR_CFG(base);
#endif /* (CY_CPU_CORTEX_M4) && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */

    return ((tempReg >> CY_GPIO_INTR_FILT_OFFSET) & CY_GPIO_INTR_FLT_EDGE_MASK);
}

#if defined (CY_IP_MXS22IOSS)
/*******************************************************************************
* Function Name: Cy_GPIO_SetPullupResistance
****************************************************************************//**
*
* Configures the GPIO pin Pull-up mode.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* Pull-up mode for a pin. Options are detailed in
* \ref group_gpio_PullUpMode macros
*
* \note
* This API configures pull-up resistors only when
* \ref CY_GPIO_DM_CFGOUT3_STRONG_PULLUP_HIGHZ is selected. For all other pin drive
* modes, it disables additional pull-up resistors.
*
* \note
* This API modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
*
* \note
* This API is available for the CAT1D devices.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetPullupResistance
*
*******************************************************************************/
void Cy_GPIO_SetPullupResistance(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
    uint32_t tempReg, pinLoc, prtCfg;

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_PULLUP_RES_VALID(value));

    if(Cy_GPIO_GetDrivemode(base, pinNum) != CY_GPIO_DM_CFGOUT3_STRONG_PULLUP_HIGHZ)
    {
        value = CY_GPIO_PULLUP_RES_DISABLE;
    }

    pinLoc = pinNum << CY_GPIO_CFG_RES_PULLUP_MODE_OFFSET;
    tempReg = (GPIO_PRT_CFG_RES(base) & ~(CY_GPIO_CFG_RES_PULLUP_MODE_MASK << pinLoc));
    prtCfg = tempReg | ((value & CY_GPIO_CFG_RES_PULLUP_MODE_MASK) << pinLoc);

    GPIO_PRT_CFG_RES(base) = prtCfg;
}

/*******************************************************************************
* Function Name: Cy_GPIO_GetPullupResistance
****************************************************************************//**
*
* Returns the Pull-up mode of GPIO Pin.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* Pull-up mode. Options are detailed in \ref group_gpio_PullUpMode macros
*
* \note
* This API is available for the CAT1D devices.
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_SetPullupResistance
*
*******************************************************************************/
uint32_t Cy_GPIO_GetPullupResistance(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t tempReg;

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

    tempReg = GPIO_PRT_CFG_RES(base);

    return ((tempReg >> (pinNum << CY_GPIO_CFG_RES_PULLUP_MODE_OFFSET)) & CY_GPIO_CFG_RES_PULLUP_MODE_MASK);
}
#endif /* CY_IP_MXS22IOSS */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS40IOSS, CY_IP_MXS22IOSS */
/* [] END OF FILE */
