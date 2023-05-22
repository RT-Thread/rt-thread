/***************************************************************************//**
* \file cy_pra.c
* \version 2.40
*
* \brief The source code file for the PRA driver. The API is not intended to
* be used directly by the user application.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation
* (an Infineon company) or an affiliate of Cypress Semiconductor Corporation.
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

#if defined (CY_IP_MXS40SRSS)

#include "cy_pra.h"
#include "cy_pra_cfg.h"
#include "cy_sysint.h"
#include "cy_ipc_drv.h"
#include "cy_device.h"
#include "cy_syspm.h"
#include "cy_ble_clk.h"
#include "cy_gpio.h"

#if defined (CY_DEVICE_SECURE) || defined (CY_DOXYGEN)

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 17.2', 4, \
'Checked manually. All the recursive cycles are handled properly.');

#define CY_PRA_REG_POLICY_WRITE_ALL   (0x00000000UL)
#define CY_PRA_REG_POLICY_WRITE_NONE  (0xFFFFFFFFUL)
#define CY_PRA_MS_NR                  (16U)

#define CY_PRA_GPIO_V2_PRT_REG_NR       (21U)   /* No of registers in GPIO PRT_V2 */
#define CY_PRA_HSIOM_PRT_REG_NR         (2U)    /* No of registers in GPIO PRT_V1 */

#define CY_PRA_CLK_EXT_PIN_INDEX        (0UL)
#define CY_PRA_CLK_ECO_INPIN_INDEX      (1UL)
#define CY_PRA_CLK_ECO_OUTPIN_INDEX     (2UL)
#define CY_PRA_CLK_WCO_INPIN_INDEX      (3UL)
#define CY_PRA_CLK_WCO_OUTPIN_INDEX     (4UL)

#define CY_PRA_SKIP_SYS_CFG             (0xFFUL)


/* The table to get a register address based on its index */
cy_stc_pra_reg_policy_t regIndexToAddr[CY_PRA_REG_INDEX_COUNT];

#if (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
/* SRAM power mode configurations */
cy_pra_sram_pwr_mode_config_t sramPwrModeConfig[CY_PRA_SRAM_MAX_NR];
#endif

#if (CY_CPU_CORTEX_M4)
    static IPC_STRUCT_Type *ipcPraBase = NULL;

    /* External clock secure pin list */
    cy_stc_pra_extclk_pin_t secExtclkPinList[CY_PRA_EXTCLK_PIN_NR];
#if defined(CY_DEVICE_PSOC6ABLE2)
    cy_stc_pra_extclk_hsiom_t secExtClkAdjHsiomList[CY_PRA_EXTCLK_PIN_NR];
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#endif /* (CY_CPU_CORTEX_M0P) */


/*******************************************************************************
*        Internal Function Prototypes
*******************************************************************************/
#if (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
    static void Cy_PRA_Handler(void);
    static void Cy_PRA_ProcessCmd(cy_stc_pra_msg_t *message);
    static void Cy_PRA_PmHibernate(uint32_t funcProc);
    static void Cy_PRA_PmCm4DpFlagSet(void);
    static cy_en_pra_status_t Cy_PRA_ClkDSBeforeTransition(void);
    static cy_en_pra_status_t Cy_PRA_ClkDSAfterTransition(void);
    static bool Cy_PRA_RegAccessRangeValid(uint16_t index);
    static cy_en_pra_status_t Cy_PRA_ClocksReset(void);
    static cy_en_pra_status_t Cy_PRA_BackupReset(bool iloHibernateON);
    static void Cy_PRA_InitGpioPort(cy_stc_pra_reg_policy_t *regPolicy, uint16_t index, GPIO_PRT_Type *port, uint32_t pinNum);
    static void Cy_PRA_InitHsiomPort(cy_stc_pra_reg_policy_t *regPolicy, uint16_t index, GPIO_PRT_Type *port, uint32_t pinNum);
#if defined(CY_DEVICE_PSOC6ABLE2)
    static void Cy_PRA_InitAdjHsiomPort(cy_stc_pra_reg_policy_t *regPolicy, uint16_t index, GPIO_PRT_Type *base);
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
    static cy_en_pra_status_t Cy_PRA_ValidateSramPowerMode(cy_en_syspm_sram_index_t sramNum, uint32_t sramMacroNum, cy_en_syspm_sram_pwr_mode_t sramPwrMode);
    static cy_en_pra_status_t Cy_PRA_ValidateEntireSramPowerMode(cy_en_syspm_sram_index_t sramNum, cy_en_syspm_sram_pwr_mode_t sramPwrMode);
#endif /* (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN) */


/*******************************************************************************
* Function Name: Cy_PRA_Init
****************************************************************************//**
*
* Initializes the PRA driver:
* - Initializes the register access array with the register addresses (Cortex-M0+)
* - Sets up the IPC communication between CPU cores
* - Checks that the driver versions match on the Cortex-M0+ and Cortex-M4 sides.
*
* Call the function before accessing any protected registers.
* It is called during a device startup from \ref SystemInit().
*
*******************************************************************************/
void Cy_PRA_Init(void)
{

#if (CY_CPU_CORTEX_M0P)
    for (uint32_t i = 0UL; i < CY_PRA_REG_INDEX_COUNT; i++)
    {
        regIndexToAddr[i].writeMask = CY_PRA_REG_POLICY_WRITE_ALL;
    }
    regIndexToAddr[CY_PRA_INDX_SRSS_PWR_LVD_CTL].addr          = &SRSS_PWR_LVD_CTL;
    regIndexToAddr[CY_PRA_INDX_SRSS_SRSS_INTR].addr            = &SRSS_SRSS_INTR;
    regIndexToAddr[CY_PRA_INDX_SRSS_SRSS_INTR_SET].addr        = &SRSS_SRSS_INTR_SET;
    regIndexToAddr[CY_PRA_INDX_SRSS_SRSS_INTR_MASK].addr       = &SRSS_SRSS_INTR_MASK;
    regIndexToAddr[CY_PRA_INDX_SRSS_SRSS_INTR_CFG].addr        = &SRSS_SRSS_INTR_CFG;
    regIndexToAddr[CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_1].addr    = &SRSS_CLK_ROOT_SELECT[1U];
    regIndexToAddr[CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_2].addr    = &SRSS_CLK_ROOT_SELECT[2U];
    regIndexToAddr[CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_3].addr    = &SRSS_CLK_ROOT_SELECT[3U];
    regIndexToAddr[CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_4].addr    = &SRSS_CLK_ROOT_SELECT[4U];
    regIndexToAddr[CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_5].addr    = (CY_SRSS_NUM_HFROOT > 4U) ? &SRSS_CLK_ROOT_SELECT[5U] : NULL;
    regIndexToAddr[CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_6].addr    = (CY_SRSS_NUM_HFROOT > 5U) ? &SRSS_CLK_ROOT_SELECT[6U] : NULL;
    regIndexToAddr[CY_PRA_INDX_FLASHC_FLASH_CMD].addr          = &FLASHC_FLASH_CMD;
    regIndexToAddr[CY_PRA_INDX_SRSS_PWR_HIBERNATE].addr        = &SRSS_PWR_HIBERNATE;
    regIndexToAddr[CY_PRA_INDX_SRSS_PWR_HIBERNATE].writeMask   = (uint32_t) ~ (SRSS_PWR_HIBERNATE_TOKEN_Msk |
                                                                               SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Msk |
                                                                               SRSS_PWR_HIBERNATE_MASK_HIBPIN_Msk |
                                                                               SRSS_PWR_HIBERNATE_MASK_HIBALARM_Msk |
                                                                               SRSS_PWR_HIBERNATE_MASK_HIBWDT_Msk);
    regIndexToAddr[CY_PRA_INDX_SRSS_CLK_MFO_CONFIG].addr       = &SRSS_CLK_MFO_CONFIG;
    regIndexToAddr[CY_PRA_INDX_SRSS_CLK_MF_SELECT].addr        = &SRSS_CLK_MF_SELECT;
    regIndexToAddr[CY_PRA_INDX_FLASHC_FM_CTL_BOOKMARK].addr     = &FLASHC_FM_CTL_BOOKMARK;
    regIndexToAddr[CY_PRA_INDX_FLASHC_FM_CTL_BOOKMARK].writeMask= CY_PRA_REG_POLICY_WRITE_NONE;

    /* There are up to 16 bus masters */
    for (uint32_t i = 0UL; i < CY_PRA_MS_NR; i++)
    {
        #if defined(CY_DEVICE_PSOC6ABLE2)
            regIndexToAddr[CY_PRA_INDX_PROT_MPU_MS_CTL + i].addr = &PROT_MPU_MS_CTL(i);
        #else
            regIndexToAddr[CY_PRA_INDX_PROT_MPU_MS_CTL + i].addr = (volatile uint32_t *) 0UL;
        #endif /* (CY_DEVICE_PSOC6ABLE2) */

        regIndexToAddr[CY_PRA_INDX_PROT_MPU_MS_CTL + i].writeMask= CY_PRA_REG_POLICY_WRITE_NONE;
    }

    /* Initialize SRAM power modes */
    for (uint32_t i = 0UL; i < CY_PRA_SRAM_MAX_NR; i++)
    {
        sramPwrModeConfig[i].macroConfigCount = 0UL;
    }

    /* Configures the IPC interrupt handler. */
    Cy_IPC_Drv_SetInterruptMask(Cy_IPC_Drv_GetIntrBaseAddr(CY_IPC_INTR_PRA), CY_PRA_IPC_NONE_INTR, CY_PRA_IPC_CHAN_INTR);
    cy_stc_sysint_t intr = {
        .intrSrc = (IRQn_Type)CY_SYSINT_CM0P_MUX4,
        .cm0pSrc = (cy_en_intr_t)(int32_t) CY_IPC_INTR_NUM_TO_VECT((int32_t) CY_IPC_INTR_PRA),
        .intrPriority = 0UL
    };

    if (CY_SYSINT_SUCCESS != Cy_SysInt_Init(&intr, &Cy_PRA_Handler))
    {
        CY_HALT();
    }

    NVIC_EnableIRQ(intr.intrSrc);
#else
    /* Need to get this address in RAM, because there are use cases
    *  where this address is used but flash is not accessible
    */
    ipcPraBase = Cy_IPC_Drv_GetIpcBaseAddress(CY_IPC_CHAN_PRA);

    /* Check the version of the driver on the Cortex-M0+ side to match with this one */
    if (CY_PRA_STATUS_SUCCESS != Cy_PRA_SendCmd(CY_PRA_MSG_TYPE_VERSION_CHECK,
                                    (uint16_t) 0U,
                                    (uint32_t) CY_PRA_DRV_VERSION_MAJOR,
                                    (uint32_t) CY_PRA_DRV_VERSION_MINOR))
    {
        /* The PRA driver may not function as expected if different versions
        *  of the driver are on the Cortex-M0+ and Cortex-M4 sides, so halt device.
        */
        CY_HALT();
    }

    /* Fill the external clock ports */
    if (CY_PRA_STATUS_SUCCESS != Cy_PRA_SendCmd(CY_PRA_MSG_TYPE_EXTCLK_PIN_LIST,
                                    (uint16_t) 0U,
                                    (uint32_t) secExtclkPinList,
                                    (uint32_t) CY_PRA_EXTCLK_PIN_NR))
    {
        /* Initialize the List */
        for (uint32_t index = 0UL; index<CY_PRA_EXTCLK_PIN_NR; index++)
        {
            secExtclkPinList[index].port = NULL;
        }
    }

#if defined(CY_DEVICE_PSOC6ABLE2)
    /* Fill the external clock HSIOM ports */
    if (CY_PRA_STATUS_SUCCESS != Cy_PRA_SendCmd(CY_PRA_MSG_TYPE_EXTCLK_ADJHSIOM_LIST,
                                    (uint16_t) 0U,
                                    (uint32_t) secExtClkAdjHsiomList,
                                    (uint32_t) CY_PRA_EXTCLK_PIN_NR))
    {
        /* Initialize the List */
        for (uint32_t index = 0UL; index<CY_PRA_EXTCLK_PIN_NR; index++)
        {
            secExtClkAdjHsiomList[index].port = NULL;
        }
    }
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */

#endif /* (CY_CPU_CORTEX_M0P) */
}


#if (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_PRA_UpdateExtClockRegIndex
****************************************************************************//**
*
* Update Index-to-Addr Array with External clock addresses
*
*******************************************************************************/
void Cy_PRA_UpdateExtClockRegIndex(void)
{
    if (NULL != extClkPolicyPtr)
    {
        if (extClkPolicyPtr->extClkEnable)
        {
            Cy_PRA_InitGpioPort(regIndexToAddr, CY_PRA_INDX_GPIO_EXTCLK_PRT, extClkPolicyPtr->extClkPort, extClkPolicyPtr->extClkPinNum);
            Cy_PRA_InitHsiomPort(regIndexToAddr, CY_PRA_INDEX_HSIOM_EXTCLK_PRT, extClkPolicyPtr->extClkPort, extClkPolicyPtr->extClkPinNum);
            #if defined(CY_DEVICE_PSOC6ABLE2)
                Cy_PRA_InitAdjHsiomPort(regIndexToAddr, CY_PRA_INDEX_HSIOM_EXTCLK_ADJ_PRT, extClkPolicyPtr->extClkPort);
            #endif /* defined(CY_DEVICE_PSOC6ABLE2) */
        }

        if (extClkPolicyPtr->ecoEnable)
        {
            Cy_PRA_InitGpioPort(regIndexToAddr, CY_PRA_INDX_GPIO_ECO_IN_PRT, extClkPolicyPtr->ecoInPort, extClkPolicyPtr->ecoInPinNum);
            Cy_PRA_InitGpioPort(regIndexToAddr, CY_PRA_INDX_GPIO_ECO_OUT_PRT, extClkPolicyPtr->ecoOutPort, extClkPolicyPtr->ecoOutPinNum);
            Cy_PRA_InitHsiomPort(regIndexToAddr, CY_PRA_INDEX_HSIOM_ECO_IN_PRT, extClkPolicyPtr->ecoInPort, extClkPolicyPtr->ecoInPinNum);
            Cy_PRA_InitHsiomPort(regIndexToAddr, CY_PRA_INDEX_HSIOM_ECO_OUT_PRT, extClkPolicyPtr->ecoOutPort, extClkPolicyPtr->ecoOutPinNum);
            #if defined(CY_DEVICE_PSOC6ABLE2)
                Cy_PRA_InitAdjHsiomPort(regIndexToAddr, CY_PRA_INDEX_HSIOM_ECO_IN_ADJ_PRT, extClkPolicyPtr->ecoInPort);
                Cy_PRA_InitAdjHsiomPort(regIndexToAddr, CY_PRA_INDEX_HSIOM_ECO_OUT_ADJ_PRT, extClkPolicyPtr->ecoOutPort);
            #endif /* defined(CY_DEVICE_PSOC6ABLE2) */
        }

        if (extClkPolicyPtr->wcoEnable)
        {
            Cy_PRA_InitGpioPort(regIndexToAddr, CY_PRA_INDX_GPIO_WCO_IN_PRT, extClkPolicyPtr->wcoInPort, extClkPolicyPtr->wcoInPinNum);
            Cy_PRA_InitGpioPort(regIndexToAddr, CY_PRA_INDX_GPIO_WCO_OUT_PRT, extClkPolicyPtr->wcoOutPort, extClkPolicyPtr->wcoOutPinNum);
            Cy_PRA_InitHsiomPort(regIndexToAddr, CY_PRA_INDEX_HSIOM_WCO_IN_PRT, extClkPolicyPtr->wcoInPort, extClkPolicyPtr->wcoInPinNum);
            Cy_PRA_InitHsiomPort(regIndexToAddr, CY_PRA_INDEX_HSIOM_WCO_OUT_PRT, extClkPolicyPtr->wcoOutPort, extClkPolicyPtr->wcoOutPinNum);
            #if defined(CY_DEVICE_PSOC6ABLE2)
                Cy_PRA_InitAdjHsiomPort(regIndexToAddr, CY_PRA_INDEX_HSIOM_WCO_IN_ADJ_PRT, extClkPolicyPtr->wcoInPort);
                Cy_PRA_InitAdjHsiomPort(regIndexToAddr, CY_PRA_INDEX_HSIOM_WCO_OUT_ADJ_PRT, extClkPolicyPtr->wcoOutPort);
            #endif /* defined(CY_DEVICE_PSOC6ABLE2) */
        }
    }
}

/*******************************************************************************
* Function Name: Cy_PRA_InitGpioPort
****************************************************************************//**
*
* Initializes all port register address and write mask
*
*******************************************************************************/
static void Cy_PRA_InitGpioPort(cy_stc_pra_reg_policy_t *regPolicy, uint16_t index, GPIO_PRT_Type *port, uint32_t pinNum)
{
    uint32_t pinLoc;
    volatile uint32_t *portAddr;

    if ((NULL != regPolicy) && (NULL != port) && CY_GPIO_IS_PIN_VALID(pinNum))
    {
        portAddr = (volatile uint32_t *)((void *)(port));
        for (uint32_t i = 0UL; i < CY_PRA_GPIO_V2_PRT_REG_NR; i++)
        {
            regPolicy[index + i].addr = (portAddr + i);
        }

        regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, OUT), 4U)].writeMask = (CY_GPIO_OUT_MASK << pinNum); /* OUT */
        regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, OUT_CLR), 4U)].writeMask = (CY_GPIO_OUT_MASK << pinNum); /* OUT_CLR */
        regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, OUT_SET), 4U)].writeMask = (CY_GPIO_OUT_MASK << pinNum); /* OUT_SET */
        regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, OUT_INV), 4U)].writeMask = (CY_GPIO_OUT_MASK << pinNum); /* OUT_INV */
        regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, IN), 4U)].writeMask = (CY_GPIO_IN_MASK << pinNum); /* IN */
        regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, INTR), 4U)].writeMask = (CY_GPIO_INTR_STATUS_MASK << pinNum); /* INTR */
        regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, INTR_MASK), 4U)].writeMask = (CY_GPIO_INTR_EN_MASK << pinNum); /* INTR_MASK */
        regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, INTR_MASKED), 4U)].writeMask = (CY_GPIO_INTR_MASKED_MASK << pinNum); /* INTR_MASKED */
        regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, INTR_SET), 4U)].writeMask = (CY_GPIO_INTR_SET_MASK << pinNum); /* INTR_SET */

        pinLoc = pinNum << CY_GPIO_INTR_CFG_OFFSET;
        regPolicy[index + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtIntrCfgOffset), 4U)].writeMask = (CY_GPIO_INTR_EDGE_MASK << pinLoc); /* INTR_CFG */

        pinLoc = pinNum << CY_GPIO_DRIVE_MODE_OFFSET;
        regPolicy[index + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgOffset), 4U)].writeMask = (CY_GPIO_CFG_DM_MASK << pinLoc); /* CFG */

        regPolicy[index + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgInOffset), 4U)].writeMask = (CY_GPIO_CFG_IN_VTRIP_SEL_MASK << pinNum); /* CFG_IN */

        pinLoc = (uint32_t)(pinNum << 1u) + CY_GPIO_CFG_OUT_DRIVE_OFFSET;
        regPolicy[index + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgOutOffset), 4U)].writeMask = (CY_GPIO_CFG_OUT_DRIVE_SEL_MASK << pinLoc) |
                                                                                                            (CY_GPIO_CFG_OUT_SLOW_MASK << pinNum); /* CFG_OUT */

        pinLoc = (pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET;
        regPolicy[index + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgSioOffset), 4U)].writeMask = (CY_GPIO_VREG_EN_MASK << pinLoc);
        pinLoc = ((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_IBUF_SHIFT;
        regPolicy[index + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgSioOffset), 4U)].writeMask |= (CY_GPIO_IBUF_MASK << pinLoc);
        pinLoc = ((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_VTRIP_SEL_SHIFT;
        regPolicy[index + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgSioOffset), 4U)].writeMask |= (CY_GPIO_VTRIP_SEL_MASK << pinLoc);
        pinLoc = ((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_VREF_SEL_SHIFT;
        regPolicy[index + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgSioOffset), 4U)].writeMask |= (CY_GPIO_VREF_SEL_MASK << pinLoc);
        pinLoc = ((pinNum & CY_GPIO_SIO_ODD_PIN_MASK) << CY_GPIO_CFG_SIO_OFFSET) + CY_GPIO_VOH_SEL_SHIFT;
        regPolicy[index + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgSioOffset), 4U)].writeMask |= (CY_GPIO_VOH_SEL_MASK << pinLoc);
    }
    else if (NULL != regPolicy)
    {
        /* regIndexToAddr Indexes are filled with NULL addresses. So don't allow to write in these indexes */
        for (uint32_t i = 0UL; i < CY_PRA_GPIO_V2_PRT_REG_NR; i++)
        {
            regPolicy[index + i].addr = NULL;
            regPolicy[index + i].writeMask = CY_PRA_REG_POLICY_WRITE_NONE;
        }
    }
    else
    {
        /* Invalid parameters */
    }
}

/*******************************************************************************
* Function Name: Cy_PRA_InitHsiomPort
****************************************************************************//**
*
* Initializes all HSIOM port register address and write mask
*
*******************************************************************************/
static void Cy_PRA_InitHsiomPort(cy_stc_pra_reg_policy_t *regPolicy, uint16_t index, GPIO_PRT_Type *port, uint32_t pinNum)
{
    uint32_t portNum;
    volatile uint32_t *portAddrHSIOM;

    if ((NULL != regPolicy) && (NULL != port) && CY_GPIO_IS_PIN_VALID(pinNum))
    {
        /* calculate hsiom port */
        portNum = ((uint32_t)(port) - CY_GPIO_BASE) / GPIO_PRT_SECTION_SIZE;
        portAddrHSIOM = (volatile uint32_t *)(CY_HSIOM_BASE + (HSIOM_PRT_SECTION_SIZE * portNum));

        for (uint32_t i = 0UL; i < CY_PRA_HSIOM_PRT_REG_NR; i++)
        {
            regPolicy[index + i].addr = (portAddrHSIOM + i);
        }

        if (pinNum < CY_GPIO_PRT_HALF)
        {
            regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(HSIOM_PRT_V1_Type, PORT_SEL0), 4U)].writeMask = (CY_GPIO_HSIOM_MASK << (pinNum << CY_GPIO_HSIOM_OFFSET));
        }
        else
        {
            pinNum -= CY_GPIO_PRT_HALF;
            regPolicy[index + CY_SYSLIB_DIV_ROUND(offsetof(HSIOM_PRT_V1_Type, PORT_SEL1), 4U)].writeMask = (CY_GPIO_HSIOM_MASK << (pinNum << CY_GPIO_HSIOM_OFFSET));
        }
    }
    else if (NULL != regPolicy)
    {
        /* regIndexToAddr Indexes are filled with NULL addresses. So don't allow to write in these indexes */
        for (uint32_t i = 0UL; i < CY_PRA_HSIOM_PRT_REG_NR; i++)
        {
            regPolicy[index + i].addr = NULL;
            regPolicy[index + i].writeMask = CY_PRA_REG_POLICY_WRITE_NONE;
        }
    }
    else
    {
        /* Invalid parameters */
    }
}

#if defined(CY_DEVICE_PSOC6ABLE2)
/*******************************************************************************
* Function Name: Cy_PRA_InitAdjHsiomPort
****************************************************************************//**
*
* Initializes all adjacent HSIOM port register address and write mask
*
*******************************************************************************/
static void Cy_PRA_InitAdjHsiomPort(cy_stc_pra_reg_policy_t *regPolicy, uint16_t index, GPIO_PRT_Type *base)
{
    uint32_t portNum;
    volatile uint32_t *portAddrHSIOM;
    GPIO_PRT_Type *port;

    if ((NULL != regPolicy) && (NULL != base))
    {
        /* calculate next port address */
        port = base + 1UL;

        /* calculate hsiom port */
        portNum = ((uint32_t)(port) - CY_GPIO_BASE) / GPIO_PRT_SECTION_SIZE;
        portAddrHSIOM = (volatile uint32_t *)(CY_HSIOM_BASE + (HSIOM_PRT_SECTION_SIZE * portNum));

        for (uint32_t i = 0UL; i < CY_PRA_HSIOM_PRT_REG_NR; i++)
        {
            regPolicy[index + i].addr = (portAddrHSIOM + i);
            regPolicy[index + i].writeMask = CY_PRA_REG_POLICY_WRITE_ALL;
        }
    }
    else if (NULL != regPolicy)
    {
        /* regIndexToAddr Indexes are filled with NULL addresses. So don't allow to write in these indexes */
        for (uint32_t i = 0UL; i < CY_PRA_HSIOM_PRT_REG_NR; i++)
        {
            regPolicy[index + i].addr = NULL;
            regPolicy[index + i].writeMask = CY_PRA_REG_POLICY_WRITE_NONE;
        }
    }
    else
    {
        /* Invalid parameters */
    }
}
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */

/*******************************************************************************
* Function Name: Cy_PRA_Handler
****************************************************************************//**
*
* The IPC interrupt handler on Cortex-M0+ core is called after there is a
* request from the Cortex-M4 core.
*
*******************************************************************************/
static void Cy_PRA_Handler(void)
{
    cy_stc_pra_msg_t msgLocal;
    cy_stc_pra_msg_t* msgRemote;

    /* Processes an internal command copy and updates the original value */
    msgRemote = (cy_stc_pra_msg_t *)Cy_IPC_Drv_ReadDataValue(Cy_IPC_Drv_GetIpcBaseAddress(CY_IPC_CHAN_PRA));

    msgLocal = *msgRemote;
    Cy_PRA_ProcessCmd(&msgLocal);
    *msgRemote = msgLocal;

    /* Clears the interrupt logic to detect a next interrupt */
    Cy_IPC_Drv_ClearInterrupt(Cy_IPC_Drv_GetIntrBaseAddr(CY_IPC_INTR_PRA), CY_PRA_IPC_NONE_INTR, CY_PRA_IPC_CHAN_INTR);

    (void) Cy_IPC_Drv_LockRelease(Cy_IPC_Drv_GetIpcBaseAddress(CY_IPC_CHAN_PRA), CY_PRA_IPC_NONE_INTR);
}


/*******************************************************************************
* Function Name: Cy_PRA_ProcessCmd
****************************************************************************//**
*
* Processes and executes the command on Cortex-M0+ which was received from
* the Cortex-M4 application.
*
* \param message cy_stc_pra_msg_t
*
*******************************************************************************/
static void Cy_PRA_ProcessCmd(cy_stc_pra_msg_t *message)
{
    static bool structInit = false;
    static cy_stc_pra_system_config_t structCpy = {0UL};

    CY_ASSERT_L1(NULL != message);


    switch (message->praCommand)
    {
        case CY_PRA_MSG_TYPE_REG32_CLR_SET:
            /* Reports an error if any of the following conditions is false:
            *  - A new value (message->praData2) has zeros in the write-protected fields
            *  - The register index is within the valid range.
            */
            if ((0U == (message->praData2 & regIndexToAddr[message->praIndex].writeMask)) &&
                (CY_PRA_REG_POLICY_WRITE_NONE != regIndexToAddr[message->praIndex].writeMask) &&
                (Cy_PRA_RegAccessRangeValid(message->praIndex)))
            {
                uint32_t tmp;

                tmp =  CY_GET_REG32(regIndexToAddr[message->praIndex].addr);

                tmp &= (message->praData1 | regIndexToAddr[message->praIndex].writeMask);
                tmp |= message->praData2;
                CY_SET_REG32(regIndexToAddr[message->praIndex].addr, tmp);
                message->praStatus = CY_PRA_STATUS_SUCCESS;
            }
            else
            {
                message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
            }
            break;

        case CY_PRA_MSG_TYPE_REG32_SET:
            /* Reports an error if any of the following conditions is false:
            *  - A new value (message->praData1) has zeros or same value in the write-protected fields
            *  - The register index is within the valid range.
            */
            if ((CY_PRA_REG_POLICY_WRITE_NONE != regIndexToAddr[message->praIndex].writeMask) &&
                (Cy_PRA_RegAccessRangeValid(message->praIndex)))
            {
                uint32_t tmp;

                tmp =  CY_GET_REG32(regIndexToAddr[message->praIndex].addr);

                if ((0U == (message->praData1 & regIndexToAddr[message->praIndex].writeMask)) ||
                    ((tmp & regIndexToAddr[message->praIndex].writeMask) ==
                    (message->praData1 & regIndexToAddr[message->praIndex].writeMask)))
                {
                    /* Clears the bits allowed to write */
                    tmp &= regIndexToAddr[message->praIndex].writeMask;

                    /* Sets the allowed bits based on the new value.
                    *  The write-protected fields have zeros in the new value, so no additional checks needed
                    */
                    tmp |= message->praData1;
                    CY_SET_REG32(regIndexToAddr[message->praIndex].addr, tmp);
                    message->praStatus = CY_PRA_STATUS_SUCCESS;
                }
                else
                {
                    message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
                }
            }
            else
            {
                message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
            }
            break;

        case CY_PRA_MSG_TYPE_REG32_GET:
            if (Cy_PRA_RegAccessRangeValid(message->praIndex))
            {
                message->praData1 = CY_GET_REG32(regIndexToAddr[message->praIndex].addr);
                message->praStatus = CY_PRA_STATUS_SUCCESS;
            }
            else
            {
                message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
            }
            break;

        case CY_PRA_MSG_TYPE_CM0_WAKEUP:
            message->praStatus = CY_PRA_STATUS_SUCCESS;
            break;

        case CY_PRA_MSG_TYPE_VERSION_CHECK:
            /* The PRA driver may not function as expected if different versions
            *  of the driver are on the Cortex-M0+ and Cortex-M4 sides.
            */
            if (((uint32_t) CY_PRA_DRV_VERSION_MAJOR == (message->praData1)) &&
                ((uint32_t) CY_PRA_DRV_VERSION_MINOR == (message->praData2)))
            {
                message->praStatus = CY_PRA_STATUS_SUCCESS;
            }
            else
            {
                message->praStatus = CY_PRA_STATUS_ERROR_PRA_VERSION;
            }
            break;

        case CY_PRA_MSG_TYPE_EXTCLK_PIN_LIST:

            if ((NULL != (cy_stc_pra_extclk_pin_t *) (message->praData1)) && ((uint32_t) (message->praData2) <= CY_PRA_EXTCLK_PIN_NR))
            {
                cy_stc_pra_extclk_pin_t *pinList =  (cy_stc_pra_extclk_pin_t *) message->praData1;
                message->praStatus = CY_PRA_STATUS_SUCCESS;

                /* when there is no policy input then initialize the pinList */
                if (NULL == extClkPolicyPtr)
                {
                    pinList[CY_PRA_CLK_EXT_PIN_INDEX].port = NULL;
                    pinList[CY_PRA_CLK_ECO_INPIN_INDEX].port = NULL;
                    pinList[CY_PRA_CLK_ECO_OUTPIN_INDEX].port = NULL;
                    pinList[CY_PRA_CLK_WCO_INPIN_INDEX].port = NULL;
                    pinList[CY_PRA_CLK_WCO_OUTPIN_INDEX].port = NULL;
                }
                else
                {

                    if (extClkPolicyPtr->extClkEnable)
                    {
                        pinList[CY_PRA_CLK_EXT_PIN_INDEX].port = extClkPolicyPtr->extClkPort;
                        pinList[CY_PRA_CLK_EXT_PIN_INDEX].pinNum = extClkPolicyPtr->extClkPinNum;
                        pinList[CY_PRA_CLK_EXT_PIN_INDEX].index = CY_PRA_INDX_GPIO_EXTCLK_PRT;
                        pinList[CY_PRA_CLK_EXT_PIN_INDEX].hsiomIndex = CY_PRA_INDEX_HSIOM_EXTCLK_PRT;
                    }
                    else
                    {
                        pinList[CY_PRA_CLK_EXT_PIN_INDEX].port = NULL;
                    }

                    if (extClkPolicyPtr->ecoEnable)
                    {
                        pinList[CY_PRA_CLK_ECO_INPIN_INDEX].port = extClkPolicyPtr->ecoInPort;
                        pinList[CY_PRA_CLK_ECO_INPIN_INDEX].pinNum = extClkPolicyPtr->ecoInPinNum;
                        pinList[CY_PRA_CLK_ECO_INPIN_INDEX].index = CY_PRA_INDX_GPIO_ECO_IN_PRT;
                        pinList[CY_PRA_CLK_ECO_INPIN_INDEX].hsiomIndex = CY_PRA_INDEX_HSIOM_ECO_IN_PRT;

                        pinList[CY_PRA_CLK_ECO_OUTPIN_INDEX].port = extClkPolicyPtr->ecoOutPort;
                        pinList[CY_PRA_CLK_ECO_OUTPIN_INDEX].pinNum = extClkPolicyPtr->ecoOutPinNum;
                        pinList[CY_PRA_CLK_ECO_OUTPIN_INDEX].index = CY_PRA_INDX_GPIO_ECO_OUT_PRT;
                        pinList[CY_PRA_CLK_ECO_OUTPIN_INDEX].hsiomIndex = CY_PRA_INDEX_HSIOM_ECO_OUT_PRT;
                    }
                    else
                    {
                        pinList[CY_PRA_CLK_ECO_INPIN_INDEX].port = NULL;
                        pinList[CY_PRA_CLK_ECO_OUTPIN_INDEX].port = NULL;
                    }

                    if (extClkPolicyPtr->wcoEnable)
                    {
                        pinList[CY_PRA_CLK_WCO_INPIN_INDEX].port = extClkPolicyPtr->wcoInPort;
                        pinList[CY_PRA_CLK_WCO_INPIN_INDEX].pinNum = extClkPolicyPtr->wcoInPinNum;
                        pinList[CY_PRA_CLK_WCO_INPIN_INDEX].index = CY_PRA_INDX_GPIO_WCO_IN_PRT;
                        pinList[CY_PRA_CLK_WCO_INPIN_INDEX].hsiomIndex = CY_PRA_INDEX_HSIOM_WCO_IN_PRT;

                        pinList[CY_PRA_CLK_WCO_OUTPIN_INDEX].port = extClkPolicyPtr->wcoOutPort;
                        pinList[CY_PRA_CLK_WCO_OUTPIN_INDEX].pinNum = extClkPolicyPtr->wcoOutPinNum;
                        pinList[CY_PRA_CLK_WCO_OUTPIN_INDEX].index = CY_PRA_INDX_GPIO_WCO_OUT_PRT;
                        pinList[CY_PRA_CLK_WCO_OUTPIN_INDEX].hsiomIndex = CY_PRA_INDEX_HSIOM_WCO_OUT_PRT;
                    }
                    else
                    {
                        pinList[CY_PRA_CLK_WCO_INPIN_INDEX].port = NULL;
                        pinList[CY_PRA_CLK_WCO_OUTPIN_INDEX].port = NULL;
                    }
                } /* NULL == extClkPolicyPtr */
            }
            else
            {
                message->praStatus = CY_PRA_STATUS_INVALID_PARAM;
            }

            break;
#if defined(CY_DEVICE_PSOC6ABLE2)
        case CY_PRA_MSG_TYPE_EXTCLK_ADJHSIOM_LIST:
            if ((NULL != (cy_stc_pra_extclk_hsiom_t *) (message->praData1)) && ((uint32_t) (message->praData2) <= CY_PRA_EXTCLK_PIN_NR))
            {
                cy_stc_pra_extclk_hsiom_t *hsiomList =  (cy_stc_pra_extclk_hsiom_t *) message->praData1;

                /* when there is no policy input then initialize the hsiomList */
                if (NULL == extClkPolicyPtr)
                {
                    hsiomList[CY_PRA_CLK_EXT_PIN_INDEX].port = NULL;
                    hsiomList[CY_PRA_CLK_ECO_INPIN_INDEX].port = NULL;
                    hsiomList[CY_PRA_CLK_ECO_OUTPIN_INDEX].port = NULL;
                    hsiomList[CY_PRA_CLK_WCO_INPIN_INDEX].port = NULL;
                    hsiomList[CY_PRA_CLK_WCO_OUTPIN_INDEX].port = NULL;
                }
                else
                {

                    if (extClkPolicyPtr->extClkEnable)
                    {
                        hsiomList[CY_PRA_CLK_EXT_PIN_INDEX].port = extClkPolicyPtr->extClkPort + 1; /* Fill adjacent GPIO port */
                        hsiomList[CY_PRA_CLK_EXT_PIN_INDEX].hsiomIndex = CY_PRA_INDEX_HSIOM_EXTCLK_ADJ_PRT;
                    }
                    else
                    {
                        hsiomList[CY_PRA_CLK_EXT_PIN_INDEX].port = NULL;
                    }

                    if (extClkPolicyPtr->ecoEnable)
                    {
                        hsiomList[CY_PRA_CLK_ECO_INPIN_INDEX].port = extClkPolicyPtr->ecoInPort + 1; /* Fill adjacent GPIO port */
                        hsiomList[CY_PRA_CLK_ECO_INPIN_INDEX].hsiomIndex = CY_PRA_INDEX_HSIOM_ECO_IN_ADJ_PRT;
                        hsiomList[CY_PRA_CLK_ECO_OUTPIN_INDEX].port = extClkPolicyPtr->ecoOutPort + 1; /* Fill adjacent GPIO port */
                        hsiomList[CY_PRA_CLK_ECO_OUTPIN_INDEX].hsiomIndex = CY_PRA_INDEX_HSIOM_ECO_OUT_ADJ_PRT;
                    }
                    else
                    {
                        hsiomList[CY_PRA_CLK_ECO_INPIN_INDEX].port = NULL;
                        hsiomList[CY_PRA_CLK_ECO_OUTPIN_INDEX].port = NULL;
                    }

                    if (extClkPolicyPtr->wcoEnable)
                    {
                        hsiomList[CY_PRA_CLK_WCO_INPIN_INDEX].port = extClkPolicyPtr->wcoInPort + 1; /* Fill adjacent GPIO port */
                        hsiomList[CY_PRA_CLK_WCO_INPIN_INDEX].hsiomIndex = CY_PRA_INDEX_HSIOM_WCO_IN_ADJ_PRT;
                        hsiomList[CY_PRA_CLK_WCO_OUTPIN_INDEX].port = extClkPolicyPtr->wcoOutPort + 1; /* Fill adjacent GPIO port */
                        hsiomList[CY_PRA_CLK_WCO_OUTPIN_INDEX].hsiomIndex = CY_PRA_INDEX_HSIOM_WCO_OUT_ADJ_PRT;
                    }
                    else
                    {
                        hsiomList[CY_PRA_CLK_WCO_INPIN_INDEX].port = NULL;
                        hsiomList[CY_PRA_CLK_WCO_OUTPIN_INDEX].port = NULL;
                    }
                } /* NULL == extClkPolicyPtr */

                message->praStatus = CY_PRA_STATUS_SUCCESS;
            }
            break;
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
        case CY_PRA_MSG_TYPE_SYS_CFG_FUNC:
            CY_ASSERT_L1((cy_stc_pra_system_config_t *)(message->praData1) != NULL);

            if( NULL != (cy_stc_pra_system_config_t *)(message->praData1))
            {
                bool structInitBak = structInit;
                message->praStatus = CY_PRA_STATUS_SUCCESS;

                structCpy = *((cy_stc_pra_system_config_t *)(message->praData1));

                /* Resets clocks configuration to the default state during system reset - DRIVERS-495 */
                if (0u != Cy_SysLib_GetResetReason())
                {
                    message->praStatus = Cy_PRA_ClocksReset();
                }
                /* Resets clocks configuration and backup domain to default
                 * state during hardware reset (POR, XRES, BOD)
                 */
                else if (!structInit)
                {
                    /* Resets the Backup domain on POR, XRES, BOD only if Backup domain is supplied by VDDD */
                    if ((structCpy.vBackupVDDDEnable) && (structCpy.iloEnable))
                    {
                        message->praStatus = Cy_PRA_BackupReset(structCpy.iloHibernateON);
                    }
                    message->praStatus = Cy_PRA_ClocksReset();
                }
                else
                {
                    /* Skip clock clocks configuration resetting */
                }

                if (CY_PRA_STATUS_SUCCESS == message->praStatus)
                {
                    structInit = false; /* This makes sure not to allow any CY_PRA_MSG_TYPE_FUNC_POLICY \
                                            operation during system configurations */
                    message->praStatus = Cy_PRA_SystemConfig(&structCpy);

                    structInit = structInitBak;

                    if(CY_PRA_STATUS_SUCCESS == message->praStatus)
                    {
                        structInit = true;
                    }
                }
                else
                {
                    /* Error PRA status */
                }
            }
            else
            {
                message->praStatus = CY_PRA_STATUS_INVALID_PARAM;
            }
            break;

        case CY_PRA_MSG_TYPE_SECURE_ONLY:
            switch (message->praIndex)
            {
                case CY_PRA_PM_FUNC_HIBERNATE:
                    Cy_PRA_PmHibernate(message->praData1);
                    message->praStatus = CY_PRA_STATUS_SUCCESS;
                    break;

                case CY_PRA_PM_FUNC_CM4_DP_FLAG_SET:
                    Cy_PRA_PmCm4DpFlagSet();
                    message->praStatus = CY_PRA_STATUS_SUCCESS;
                    break;

                case CY_PRA_CLK_FUNC_DS_BEFORE_TRANSITION:
                    message->praStatus = Cy_PRA_ClkDSBeforeTransition();
                    break;

                case CY_PRA_CLK_FUNC_DS_AFTER_TRANSITION:
                    message->praStatus = Cy_PRA_ClkDSAfterTransition();
                    break;

                case CY_PRA_PM_FUNC_BUCK_ENABLE_VOLTAGE2:
                    Cy_SysPm_BuckEnableVoltage2();
                    message->praStatus = CY_PRA_STATUS_SUCCESS;
                    break;

                case CY_PRA_PM_FUNC_BUCK_DISABLE_VOLTAGE2:
                    Cy_SysPm_BuckDisableVoltage2();
                    message->praStatus = CY_PRA_STATUS_SUCCESS;
                    break;

                case CY_PRA_PM_FUNC_BUCK_VOLTAGE2_HW_CTRL:
                    Cy_SysPm_BuckSetVoltage2HwControl((bool) message->praData1);
                    message->praStatus = CY_PRA_STATUS_SUCCESS;
                    break;

                case CY_PRA_PM_FUNC_BUCK_SET_VOLTAGE2:
                    if (CY_SYSPM_IS_BUCK_VOLTAGE2_VALID(((cy_stc_pra_voltage2_t *) message->praData1)->praVoltage))
                    {
                        Cy_SysPm_BuckSetVoltage2(((cy_stc_pra_voltage2_t *) message->praData1)->praVoltage,
                                                 ((cy_stc_pra_voltage2_t *) message->praData1)->praWaitToSettle);
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                    }
                    else
                    {
                        message->praStatus = CY_PRA_STATUS_INVALID_PARAM;
                    }
                    break;

                case CY_PRA_PM_FUNC_SRAM_MACRO_PWR_MODE:
                {
                    cy_en_syspm_sram_index_t sramNum;
                    uint32_t sramMacroNum;
                    cy_en_syspm_sram_pwr_mode_t sramPwrMode;

                    sramNum = ((cy_stc_pra_sram_power_mode_config_t *) message->praData1)->sramNum;
                    sramMacroNum = ((cy_stc_pra_sram_power_mode_config_t *) message->praData1)->sramMacroNum;
                    sramPwrMode = ((cy_stc_pra_sram_power_mode_config_t *) message->praData1)->sramPwrMode;

                    message->praStatus = Cy_PRA_ValidateSramPowerMode(sramNum, sramMacroNum, sramPwrMode);

                    if (message->praStatus == CY_PRA_STATUS_SUCCESS)
                    {
                        if (CY_SYSPM_SUCCESS != Cy_SysPm_SetSRAMMacroPwrMode(sramNum, sramMacroNum, sramPwrMode))
                        {
                            message->praStatus = CY_PRA_STATUS_INVALID_PARAM;
                        }
                    }
                    else
                    {
                        /* Not allowed to modify sram power mode */
                    }
                }
                    break;

                case CY_PRA_PM_FUNC_SRAM_PWR_MODE:
                {
                    cy_en_syspm_sram_index_t sramNum;
                    cy_en_syspm_sram_pwr_mode_t sramPwrMode;

                    sramNum = ((cy_stc_pra_sram_power_mode_config_t *) message->praData1)->sramNum;
                    sramPwrMode = ((cy_stc_pra_sram_power_mode_config_t *) message->praData1)->sramPwrMode;

                    message->praStatus = Cy_PRA_ValidateEntireSramPowerMode(sramNum, sramPwrMode);

                    if (message->praStatus == CY_PRA_STATUS_SUCCESS)
                    {
                        if (CY_SYSPM_SUCCESS != Cy_SysPm_SetSRAMPwrMode(sramNum, sramPwrMode))
                        {
                            message->praStatus = CY_PRA_STATUS_INVALID_PARAM;
                        }
                    }
                    else
                    {
                        /* Not allowed to modify sram power mode */
                    }
                }
                    break;

            #ifdef CY_IP_MXBLESS
                case CY_PRA_CLK_FUNC_PILO_INITIAL_TRIM:
                    Cy_SysClk_PiloInitialTrim();
                    message->praStatus = CY_PRA_STATUS_SUCCESS;
                    break;

                case CY_PRA_CLK_FUNC_UPDATE_PILO_TRIM_STEP:
                    Cy_SysClk_PiloUpdateTrimStep();
                    message->praStatus = CY_PRA_STATUS_SUCCESS;
                    break;
            #endif /* CY_IP_MXBLESS */

                case CY_PRA_CLK_FUNC_START_MEASUREMENT:
                {
                    cy_en_meas_clks_t clockVal1, clockVal2;
                    uint32_t countVal1;
                    clockVal1 = ((cy_stc_pra_start_clk_measurement_t *) message->praData1)->clock1;
                    clockVal2 = ((cy_stc_pra_start_clk_measurement_t *) message->praData1)->clock2;
                    countVal1 = ((cy_stc_pra_start_clk_measurement_t *) message->praData1)->count1;
                    message->praStatus = (cy_en_pra_status_t)Cy_SysClk_StartClkMeasurementCounters(clockVal1, countVal1, clockVal2);
                }
                    break;

                case CY_PRA_CLK_FUNC_ILO_TRIM:
                    message->praStatus = (cy_en_pra_status_t)Cy_SysClk_IloTrim(message->praData1);
                    break;

                case CY_PRA_CLK_FUNC_SET_PILO_TRIM:
                    Cy_SysClk_PiloSetTrim(message->praData1);
                    message->praStatus = CY_PRA_STATUS_SUCCESS;
                    break;

            #if defined(CY_IP_MXBLESS)
                case CY_PRA_BLE_CLK_FUNC_ECO_CONFIGURE:
                    structCpy.altHFcLoad = ((cy_stc_pra_ble_eco_config_t *) message->praData1)->cLoad;
                    structCpy.altHFxtalStartUpTime = ((cy_stc_pra_ble_eco_config_t *) message->praData1)->xtalStartUpTime;
                    structCpy.altHFclkFreq = (uint32_t)((cy_stc_pra_ble_eco_config_t *) message->praData1)->freq;
                    structCpy.altHFsysClkDiv = (uint32_t)((cy_stc_pra_ble_eco_config_t *) message->praData1)->sysClkDiv;
                    structCpy.altHFvoltageReg = (uint32_t)((cy_stc_pra_ble_eco_config_t *) message->praData1)->voltageReg;
                    structCpy.clkAltHfEnable = true;

                    message->praStatus = (cy_en_pra_status_t)Cy_BLE_EcoConfigure(
                                                                (cy_en_ble_eco_freq_t)structCpy.altHFclkFreq,
                                                                (cy_en_ble_eco_sys_clk_div_t)structCpy.altHFsysClkDiv,
                                                                structCpy.altHFcLoad,
                                                                structCpy.altHFxtalStartUpTime,
                                                                (cy_en_ble_eco_voltage_reg_t)structCpy.altHFvoltageReg);
                    break;

                case CY_PRA_BLE_CLK_FUNC_ECO_RESET:
                    Cy_BLE_EcoReset();
                    message->praStatus = CY_PRA_STATUS_SUCCESS;
                    break;
            #endif /* CY_IP_MXBLESS */

                default:
                    message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
                    break;
            }
            break;

        case CY_PRA_MSG_TYPE_FUNC_POLICY:
            if(structInit)
            {
                switch (message->praIndex)
                {
                    case CY_PRA_PM_FUNC_LDO_SET_VOLTAGE:
                    {
                        bool powerEnableTmp, ldoEnableTmp, ulpEnableTmp;
                        powerEnableTmp = structCpy.powerEnable; /* old value backup */
                        ldoEnableTmp = structCpy.ldoEnable; /* old value backup */
                        ulpEnableTmp = structCpy.ulpEnable; /* old value backup */
                        structCpy.powerEnable = true;
                        structCpy.ldoEnable = true;
                        structCpy.ldoVoltage = (cy_en_syspm_ldo_voltage_t)message->praData1;
                        if (structCpy.ldoVoltage == CY_SYSPM_LDO_VOLTAGE_0_9V)
                        {
                            structCpy.ulpEnable = true;
                        }
                        else
                        {
                            structCpy.ulpEnable = false;
                        }
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.powerEnable = powerEnableTmp;
                                structCpy.ldoEnable = ldoEnableTmp;
                                structCpy.ulpEnable = ulpEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_PM_FUNC_BUCK_ENABLE:
                    {
                        bool powerEnableTmp, ldoEnableTmp, ulpEnableTmp;
                        powerEnableTmp = structCpy.powerEnable; /* Old value backup */
                        ldoEnableTmp = structCpy.ldoEnable; /* Old value backup */
                        ulpEnableTmp = structCpy.ulpEnable; /* Old value backup */
                        structCpy.powerEnable = true;
                        structCpy.ldoEnable = false;
                        structCpy.buckVoltage = (cy_en_syspm_buck_voltage1_t)message->praData1;
                        if (structCpy.buckVoltage == CY_SYSPM_BUCK_OUT1_VOLTAGE_0_9V)
                        {
                            structCpy.ulpEnable = true;
                        }
                        else
                        {
                            structCpy.ulpEnable = false;
                        }
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.powerEnable = powerEnableTmp;
                                structCpy.ldoEnable = ldoEnableTmp;
                                structCpy.ulpEnable = ulpEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_PM_FUNC_SET_MIN_CURRENT:
                    {
                        bool powerEnableTmp, pwrCurrentModeMinTmp;
                        /* Backups old values */
                        powerEnableTmp = structCpy.powerEnable;
                        pwrCurrentModeMinTmp = structCpy.pwrCurrentModeMin;
                        structCpy.powerEnable = true;
                        structCpy.pwrCurrentModeMin = true;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.powerEnable = powerEnableTmp;
                                structCpy.pwrCurrentModeMin = pwrCurrentModeMinTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_PM_FUNC_SET_NORMAL_CURRENT:
                    {
                        bool powerEnableTmp, pwrCurrentModeMinTmp;
                        /* Backups old values */
                        powerEnableTmp = structCpy.powerEnable;
                        pwrCurrentModeMinTmp = structCpy.pwrCurrentModeMin;
                        structCpy.powerEnable = true;
                        structCpy.pwrCurrentModeMin = false;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.powerEnable = powerEnableTmp;
                                structCpy.pwrCurrentModeMin = pwrCurrentModeMinTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_ECO_DISABLE:
                    {
                        bool ecoEnableTmp;
                        /* Backups old values */
                        ecoEnableTmp = structCpy.ecoEnable;
                        structCpy.ecoEnable = false;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.ecoEnable = ecoEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_FLL_DISABLE:
                    {
                        bool fllEnableTmp;
                        uint32_t fllOutFreqHzTmp;
                        /* Backups old values */
                        fllOutFreqHzTmp = structCpy.fllOutFreqHz;
                        fllEnableTmp = structCpy.fllEnable;
                        structCpy.fllEnable = false;
                        structCpy.fllOutFreqHz = CY_PRA_DEFAULT_ZERO;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.fllEnable = fllEnableTmp;
                                structCpy.fllOutFreqHz = fllOutFreqHzTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PLL_DISABLE:
                    {
                        bool pllEnable;
                        if (((message->praData1) > CY_PRA_CLKPATH_0) && ((message->praData1) <= CY_SRSS_NUM_PLL)) /* 0 is invalid pll number */
                        {
                            /* Backups old values */
                            ((message->praData1) == CY_PRA_CLKPLL_1) ? (pllEnable = structCpy.pll0Enable) : (pllEnable = structCpy.pll1Enable);

                            ((message->praData1) == CY_PRA_CLKPLL_1) ? (structCpy.pll0Enable = false) : (structCpy.pll1Enable = false);
                            if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                            {
                                message->praStatus = Cy_PRA_SystemConfig(&structCpy);

                                if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                                {
                                    /* On failure, previous values are restored */
                                    ((message->praData1) == CY_PRA_CLKPLL_1) ? (structCpy.pll0Enable = pllEnable) : (structCpy.pll1Enable = pllEnable);
                                }
                            }
                            else
                            {
                                message->praStatus = CY_PRA_STATUS_SUCCESS;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_INVALID_PARAM_PLL_NUM;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_ILO_ENABLE:
                    {
                        bool iloEnableTmp;
                        /* Backups old values */
                        iloEnableTmp = structCpy.iloEnable;
                        structCpy.iloEnable = true;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                structCpy.iloEnable = iloEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_ILO_DISABLE:
                    {
                        bool iloEnableTmp;
                        /* Backups old values */
                        iloEnableTmp = structCpy.iloEnable;
                        structCpy.iloEnable = false;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.iloEnable = iloEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_ILO_HIBERNATE_ON:
                    {
                        bool iloHibernateOnTmp;
                        /* Backups old values */
                        iloHibernateOnTmp = structCpy.iloHibernateON;
                        structCpy.iloHibernateON = (CY_PRA_DATA_DISABLE != message->praData1);
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.iloHibernateON = iloHibernateOnTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PILO_ENABLE:
                    {
                        bool piloEnableTmp;
                        /* Backups old values */
                        piloEnableTmp = structCpy.piloEnable;
                        structCpy.piloEnable = true;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.piloEnable = piloEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PILO_DISABLE:
                    {
                        bool piloEnableTmp;
                        /* Backups old values */
                        piloEnableTmp = structCpy.piloEnable;
                        structCpy.piloEnable = false;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.piloEnable = piloEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_WCO_ENABLE:
                    {
                        bool wcoEnableTmp;
                        /* Backups old values */
                        wcoEnableTmp = structCpy.wcoEnable;
                        structCpy.wcoEnable = true;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.wcoEnable = wcoEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_WCO_DISABLE:
                    {
                        bool wcoEnableTmp;
                        /* Backups old values */
                        wcoEnableTmp = structCpy.wcoEnable;
                        structCpy.wcoEnable = false;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.wcoEnable = wcoEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_WCO_BYPASS:
                    {
                        bool bypassEnableTmp;
                        /* Backups old values */
                        bypassEnableTmp = structCpy.bypassEnable;
                        structCpy.bypassEnable = ((cy_en_wco_bypass_modes_t) message->praData1 == CY_SYSCLK_WCO_BYPASSED) ? true : false;
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            /* The bypass value will be written to the register only when WCO is enabled */
                            if (structCpy.wcoEnable)
                            {
                                message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                                if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                                {
                                    /* On failure, previous values are restored */
                                    structCpy.bypassEnable = bypassEnableTmp;
                                }
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_HF_ENABLE:
                    {
                        bool clkHFEnable;
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                        /* Backups old values */
                        switch (message->praData1)
                        {
                            case CY_PRA_CLKHF_0:
                            clkHFEnable = structCpy.clkHF0Enable;
                            structCpy.clkHF0Enable = true;
                            break;

                            case CY_PRA_CLKHF_1:
                            clkHFEnable = structCpy.clkHF1Enable;
                            structCpy.clkHF1Enable = true;
                            break;

                            case CY_PRA_CLKHF_2:
                            clkHFEnable = structCpy.clkHF2Enable;
                            structCpy.clkHF2Enable = true;
                            break;

                            case CY_PRA_CLKHF_3:
                            clkHFEnable = structCpy.clkHF3Enable;
                            structCpy.clkHF3Enable = true;
                            break;

                            case CY_PRA_CLKHF_4:
                            clkHFEnable = structCpy.clkHF4Enable;
                            structCpy.clkHF4Enable = true;
                            break;

                            case CY_PRA_CLKHF_5:
                            clkHFEnable = structCpy.clkHF5Enable;
                            structCpy.clkHF5Enable = true;
                            break;

                            default:
                            clkHFEnable = false;
                            message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
                            break;

                        }
                        if ((message->praStatus == CY_PRA_STATUS_SUCCESS) && (CY_PRA_SKIP_SYS_CFG != message->praData2))
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                switch (message->praData1)
                                {
                                    case CY_PRA_CLKHF_0:
                                    structCpy.clkHF0Enable = clkHFEnable;
                                    break;

                                    case CY_PRA_CLKHF_1:
                                    structCpy.clkHF1Enable = clkHFEnable;
                                    break;

                                    case CY_PRA_CLKHF_2:
                                    structCpy.clkHF2Enable = clkHFEnable;
                                    break;

                                    case CY_PRA_CLKHF_3:
                                    structCpy.clkHF3Enable = clkHFEnable;
                                    break;

                                    case CY_PRA_CLKHF_4:
                                    structCpy.clkHF4Enable = clkHFEnable;
                                    break;

                                    case CY_PRA_CLKHF_5:
                                    structCpy.clkHF5Enable = clkHFEnable;
                                    break;

                                    default:
                                    /* Unknown Clock HF source */
                                    break;
                                }
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_HF_DISABLE:
                    {
                        bool clkHFEnable;
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                        /* Backups old values */
                        switch (message->praData1)
                        {
                            case CY_PRA_CLKHF_0:
                            clkHFEnable = structCpy.clkHF0Enable;
                            structCpy.clkHF0Enable = false;
                            break;

                            case CY_PRA_CLKHF_1:
                            clkHFEnable = structCpy.clkHF1Enable;
                            structCpy.clkHF1Enable = false;
                            break;

                            case CY_PRA_CLKHF_2:
                            clkHFEnable = structCpy.clkHF2Enable;
                            structCpy.clkHF2Enable = false;
                            break;

                            case CY_PRA_CLKHF_3:
                            clkHFEnable = structCpy.clkHF3Enable;
                            structCpy.clkHF3Enable = false;
                            break;

                            case CY_PRA_CLKHF_4:
                            clkHFEnable = structCpy.clkHF4Enable;
                            structCpy.clkHF4Enable = false;
                            break;

                            case CY_PRA_CLKHF_5:
                            clkHFEnable = structCpy.clkHF5Enable;
                            structCpy.clkHF5Enable = false;
                            break;

                            default:
                            clkHFEnable = false;
                            message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
                            break;

                        }
                        if ((message->praStatus == CY_PRA_STATUS_SUCCESS) && (CY_PRA_SKIP_SYS_CFG != message->praData2))
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                switch (message->praData1)
                                {
                                    case CY_PRA_CLKHF_0:
                                    structCpy.clkHF0Enable = clkHFEnable;
                                    break;

                                    case CY_PRA_CLKHF_1:
                                    structCpy.clkHF1Enable = clkHFEnable;
                                    break;

                                    case CY_PRA_CLKHF_2:
                                    structCpy.clkHF2Enable = clkHFEnable;
                                    break;

                                    case CY_PRA_CLKHF_3:
                                    structCpy.clkHF3Enable = clkHFEnable;
                                    break;

                                    case CY_PRA_CLKHF_4:
                                    structCpy.clkHF4Enable = clkHFEnable;
                                    break;

                                    case CY_PRA_CLKHF_5:
                                    structCpy.clkHF5Enable = clkHFEnable;
                                    break;

                                    default:
                                    /* Unknown Clock HF source */
                                    break;
                                }
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_HF_SET_SOURCE:
                    {
                        cy_en_clkhf_in_sources_t hfSource;
                        uint32_t hfOutFreqMHz;
                        bool hfEnabled;
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                        /* Backups old values */
                        switch (((cy_stc_pra_clkhfsetsource_t *) message->praData1)->clkHf)
                        {
                            case CY_PRA_CLKHF_0:
                            hfSource = structCpy.hf0Source;
                            structCpy.hf0Source = ((cy_stc_pra_clkhfsetsource_t *) message->praData1)->source;
                            hfOutFreqMHz = structCpy.hf0OutFreqMHz;
                            hfEnabled = structCpy.clkHF0Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf0OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf0Source)/(1UL << (uint32_t)structCpy.hf0Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            case CY_PRA_CLKHF_1:
                            hfSource = structCpy.hf1Source;
                            structCpy.hf1Source = ((cy_stc_pra_clkhfsetsource_t *) message->praData1)->source;
                            hfOutFreqMHz = structCpy.hf1OutFreqMHz;
                            hfEnabled = structCpy.clkHF1Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf1OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf1Source)/(1UL << (uint32_t)structCpy.hf1Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            case CY_PRA_CLKHF_2:
                            hfSource = structCpy.hf2Source;
                            structCpy.hf2Source = ((cy_stc_pra_clkhfsetsource_t *) message->praData1)->source;
                            hfOutFreqMHz = structCpy.hf2OutFreqMHz;
                            hfEnabled = structCpy.clkHF2Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf2OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf2Source)/(1UL << (uint32_t)structCpy.hf2Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            case CY_PRA_CLKHF_3:
                            hfSource = structCpy.hf3Source;
                            structCpy.hf3Source = ((cy_stc_pra_clkhfsetsource_t *) message->praData1)->source;
                            hfOutFreqMHz = structCpy.hf3OutFreqMHz;
                            hfEnabled = structCpy.clkHF3Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf3OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf3Source)/(1UL << (uint32_t)structCpy.hf3Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            case CY_PRA_CLKHF_4:
                            hfSource = structCpy.hf4Source;
                            structCpy.hf4Source = ((cy_stc_pra_clkhfsetsource_t *) message->praData1)->source;
                            hfOutFreqMHz = structCpy.hf4OutFreqMHz;
                            hfEnabled = structCpy.clkHF4Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf4OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf4Source)/(1UL << (uint32_t)structCpy.hf4Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            case CY_PRA_CLKHF_5:
                            hfSource = structCpy.hf5Source;
                            structCpy.hf5Source = ((cy_stc_pra_clkhfsetsource_t *) message->praData1)->source;
                            hfOutFreqMHz = structCpy.hf5OutFreqMHz;
                            hfEnabled = structCpy.clkHF5Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf5OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf5Source)/(1UL << (uint32_t)structCpy.hf5Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            default:
                            hfEnabled = false;
                            message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
                            break;
                        }
                        /* The HF source value is updated in the register only when
                         * that particular HF is enabled. Otherwise, it is stored in
                         * the system config structure
                         */
                        if ((message->praStatus == CY_PRA_STATUS_SUCCESS) && (hfEnabled) && (CY_PRA_SKIP_SYS_CFG != message->praData2))
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                switch (((cy_stc_pra_clkhfsetsource_t *) message->praData1)->clkHf)
                                {
                                    case CY_PRA_CLKHF_0:
                                    structCpy.hf0Source = hfSource;
                                    structCpy.hf0OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    case CY_PRA_CLKHF_1:
                                    structCpy.hf1Source = hfSource;
                                    structCpy.hf1OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    case CY_PRA_CLKHF_2:
                                    structCpy.hf2Source = hfSource;
                                    structCpy.hf2OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    case CY_PRA_CLKHF_3:
                                    structCpy.hf3Source = hfSource;
                                    structCpy.hf3OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    case CY_PRA_CLKHF_4:
                                    structCpy.hf4Source = hfSource;
                                    structCpy.hf4OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    case CY_PRA_CLKHF_5:
                                    structCpy.hf5Source = hfSource;
                                    structCpy.hf5OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    default:
                                    /* Unknown Clock HF source */
                                    break;
                                }
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_HF_SET_DIVIDER:
                    {
                        cy_en_clkhf_dividers_t hfDivider;
                        uint32_t hfOutFreqMHz;
                        bool hfEnabled;
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                        /* Backups old values */
                        switch (((cy_stc_pra_clkhfsetdivider_t *) message->praData1)->clkHf)
                        {
                            case CY_PRA_CLKHF_0:
                            hfDivider = structCpy.hf0Divider;
                            structCpy.hf0Divider = ((cy_stc_pra_clkhfsetdivider_t *) message->praData1)->divider;
                            hfOutFreqMHz = structCpy.hf0OutFreqMHz;
                            hfEnabled = structCpy.clkHF0Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf0OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf0Source)/(1UL << (uint32_t)structCpy.hf0Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            case CY_PRA_CLKHF_1:
                            hfDivider = structCpy.hf1Divider;
                            structCpy.hf1Divider = ((cy_stc_pra_clkhfsetdivider_t *) message->praData1)->divider;
                            hfOutFreqMHz = structCpy.hf1OutFreqMHz;
                            hfEnabled = structCpy.clkHF1Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf1OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf1Source)/(1UL << (uint32_t)structCpy.hf1Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            case CY_PRA_CLKHF_2:
                            hfDivider = structCpy.hf2Divider;
                            structCpy.hf2Divider = ((cy_stc_pra_clkhfsetdivider_t *) message->praData1)->divider;
                            hfOutFreqMHz = structCpy.hf2OutFreqMHz;
                            hfEnabled = structCpy.clkHF2Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf2OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf2Source)/(1UL << (uint32_t)structCpy.hf2Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            case CY_PRA_CLKHF_3:
                            hfDivider = structCpy.hf3Divider;
                            structCpy.hf3Divider = ((cy_stc_pra_clkhfsetdivider_t *) message->praData1)->divider;
                            hfOutFreqMHz = structCpy.hf3OutFreqMHz;
                            hfEnabled = structCpy.clkHF3Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf3OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf3Source)/(1UL << (uint32_t)structCpy.hf3Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            case CY_PRA_CLKHF_4:
                            hfDivider = structCpy.hf4Divider;
                            structCpy.hf4Divider = ((cy_stc_pra_clkhfsetdivider_t *) message->praData1)->divider;
                            hfOutFreqMHz = structCpy.hf4OutFreqMHz;
                            hfEnabled = structCpy.clkHF4Enable;
                            /* The HF output frequency is not present in the PDL API argument. Update the system config structure with the current HF output frequency value */
                            structCpy.hf4OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf4Source)/(1UL << (uint32_t)structCpy.hf4Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            case CY_PRA_CLKHF_5:
                            hfDivider = structCpy.hf5Divider;
                            structCpy.hf5Divider = ((cy_stc_pra_clkhfsetdivider_t *) message->praData1)->divider;
                            hfOutFreqMHz = structCpy.hf5OutFreqMHz;
                            hfEnabled = structCpy.clkHF5Enable;
                            /* The HF output frequency is not present in PDL API argument. So updated the system config structure with current HF output frequency value */
                            structCpy.hf5OutFreqMHz = (Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf5Source)/(1UL << (uint32_t)structCpy.hf5Divider))/CY_PRA_FREQUENCY_HZ_CONVERSION;
                            break;

                            default:
                            hfEnabled = false;
                            message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
                            break;
                        }
                        /* The HF divider value is updated in the register only when
                         * that particular HF is enabled. Otherwise, it is stored in
                         * the system config structure
                         */
                        if ((message->praStatus == CY_PRA_STATUS_SUCCESS) && (hfEnabled) && (CY_PRA_SKIP_SYS_CFG != message->praData2))
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                switch (((cy_stc_pra_clkhfsetdivider_t *) message->praData1)->clkHf)
                                {
                                    case CY_PRA_CLKHF_0:
                                    structCpy.hf0Divider = hfDivider;
                                    structCpy.hf0OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    case CY_PRA_CLKHF_1:
                                    structCpy.hf1Divider = hfDivider;
                                    structCpy.hf1OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    case CY_PRA_CLKHF_2:
                                    structCpy.hf2Divider = hfDivider;
                                    structCpy.hf2OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    case CY_PRA_CLKHF_3:
                                    structCpy.hf3Divider = hfDivider;
                                    structCpy.hf3OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    case CY_PRA_CLKHF_4:
                                    structCpy.hf4Divider = hfDivider;
                                    structCpy.hf4OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    case CY_PRA_CLKHF_5:
                                    structCpy.hf5Divider = hfDivider;
                                    structCpy.hf5OutFreqMHz = hfOutFreqMHz;
                                    break;

                                    default:
                                    /* Invalid Clock HF Source */
                                    break;
                                }
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_FAST_SET_DIVIDER:
                    {
                        uint8_t clkFastDivTmp;
                        bool clkFastEnableTmp;
                        /* Backups old values */
                        clkFastEnableTmp = structCpy.clkFastEnable;
                        clkFastDivTmp = structCpy.clkFastDiv;
                        structCpy.clkFastEnable = true;
                        structCpy.clkFastDiv =  (uint8_t)(message->praData1);
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                structCpy.clkFastDiv = clkFastDivTmp;
                                structCpy.clkFastEnable = clkFastEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PERI_SET_DIVIDER:
                    {
                        uint8_t clkPeriDivTmp;
                        bool clkPeriEnableTmp;
                        /* Backups old values */
                        clkPeriDivTmp = structCpy.clkPeriDiv;
                        clkPeriEnableTmp = structCpy.clkPeriEnable;
                        structCpy.clkPeriEnable = true;
                        structCpy.clkPeriDiv =  (uint8_t)(message->praData1);
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                structCpy.clkPeriDiv = clkPeriDivTmp;
                                structCpy.clkPeriEnable = clkPeriEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_LF_SET_SOURCE:
                    {
                        cy_en_clklf_in_sources_t clkLfSourceTmp;
                        bool clkLFEnableTmp;
                        /* Backups old values */
                        clkLFEnableTmp = structCpy.clkLFEnable;
                        clkLfSourceTmp = structCpy.clkLfSource;
                        structCpy.clkLFEnable = true;
                        structCpy.clkLfSource = (cy_en_clklf_in_sources_t)message->praData1;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.clkLfSource = clkLfSourceTmp;
                                structCpy.clkLFEnable = clkLFEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_TIMER_SET_SOURCE:
                    {
                        cy_en_clktimer_in_sources_t clkTimerSourceTmp;
                        /* Backups old values */
                        clkTimerSourceTmp = structCpy.clkTimerSource;
                        structCpy.clkTimerSource = (cy_en_clktimer_in_sources_t)message->praData1;
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                        if ((structCpy.clkTimerEnable) && (CY_PRA_SKIP_SYS_CFG != message->praData2))
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.clkTimerSource = clkTimerSourceTmp;
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_TIMER_SET_DIVIDER:
                    {
                        uint8_t clkTimerDividerTmp;
                        /* Backups old values */
                        clkTimerDividerTmp = structCpy.clkTimerDivider;
                        structCpy.clkTimerDivider = (uint8_t)(message->praData1);
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                        /* The timer divider value is updated in the register only
                         * when CLK_TIMER is enabled. Otherwise, it is only
                         * stored in the system config structure
                         */
                        if ((structCpy.clkTimerEnable) && (CY_PRA_SKIP_SYS_CFG != message->praData2))
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.clkTimerDivider = clkTimerDividerTmp;
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_TIMER_ENABLE:
                    {
                        bool clkTimerEnableTmp;
                        /* Backups old values */
                        clkTimerEnableTmp = structCpy.clkTimerEnable;
                        structCpy.clkTimerEnable = true;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                structCpy.clkTimerEnable = clkTimerEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_TIMER_DISABLE:
                    {
                        bool clkTimerEnableTmp;
                        /* Backups old values */
                        clkTimerEnableTmp = structCpy.clkTimerEnable;
                        structCpy.clkTimerEnable = false;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                structCpy.clkTimerEnable = clkTimerEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PUMP_SET_SOURCE:
                    {
                        cy_en_clkpump_in_sources_t pumpSourceTmp;
                        /* Backups old values */
                        pumpSourceTmp = structCpy.pumpSource;
                        structCpy.pumpSource = (cy_en_clkpump_in_sources_t)message->praData1;
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                        /* The PUMP source value is updated in the register only
                         * when PUMP is enabled. Otherwise, it is only
                         * stored in the system config structure
                         */
                        if ((structCpy.clkPumpEnable) && (CY_PRA_SKIP_SYS_CFG != message->praData2))
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                structCpy.pumpSource = pumpSourceTmp;
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PUMP_SET_DIVIDER:
                    {
                        cy_en_clkpump_divide_t pumpDividerTmp;
                        /* Backups old values */
                        pumpDividerTmp = structCpy.pumpDivider;
                        structCpy.pumpDivider = (cy_en_clkpump_divide_t)message->praData1;
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                        /* The PUMP divider value is updated in the register only
                         * when PUMP is enabled. Otherwise, it is only
                         * stored in the system config structure
                         */
                        if ((structCpy.clkPumpEnable) && (CY_PRA_SKIP_SYS_CFG != message->praData2))
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                structCpy.pumpDivider = pumpDividerTmp;
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PUMP_ENABLE:
                    {
                        bool clkPumpEnableTmp;
                        /* Backups old values */
                        clkPumpEnableTmp = structCpy.clkPumpEnable;
                        structCpy.clkPumpEnable = true;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                structCpy.clkPumpEnable = clkPumpEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PUMP_DISABLE:
                    {
                        bool clkPumpEnableTmp;
                        /* Backups old values */
                        clkPumpEnableTmp = structCpy.clkPumpEnable;
                        structCpy.clkPumpEnable = false;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored */
                                structCpy.clkPumpEnable = clkPumpEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_BAK_SET_SOURCE:
                    {
                        cy_en_clkbak_in_sources_t clkBakSourceTmp;
                        bool clkBakEnableTmp;
                        /* Backups old values */
                        clkBakEnableTmp = structCpy.clkBakEnable;
                        clkBakSourceTmp = structCpy.clkBakSource;
                        structCpy.clkBakEnable = true;
                        structCpy.clkBakSource = (cy_en_clkbak_in_sources_t)message->praData1;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                structCpy.clkBakSource = clkBakSourceTmp;
                                structCpy.clkBakEnable = clkBakEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_ECO_CONFIGURE:
                    {
                        /* ECO configuration is not allowed if ECO is already enabled.
                         * The correct sequence is ECO_DISABLE -> ECO_CONFIGURE -> ECO_ENABLE
                         */
                        if (structCpy.ecoEnable)
                        {
                            message->praStatus = CY_PRA_STATUS_ERROR_PROCESSING_ECO_ENABLED;
                        }
                        else
                        {
                            /* Stored the ECO config values into the system config structure.
                             * These values are applied to the register after a call from ECO_ENABLE.
                             */
                            structCpy.ecoFreqHz = ((cy_stc_pra_clk_eco_configure_t *) message->praData1)->praClkEcofreq;
                            structCpy.ecoLoad = ((cy_stc_pra_clk_eco_configure_t *) message->praData1)->praCsum;
                            structCpy.ecoEsr = ((cy_stc_pra_clk_eco_configure_t *) message->praData1)->praEsr;
                            structCpy.ecoDriveLevel = ((cy_stc_pra_clk_eco_configure_t *) message->praData1)->praDriveLevel;
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_ECO_ENABLE:
                    {
                        bool ecoEnableTmp;
                        /* Backups old values */
                        ecoEnableTmp = structCpy.ecoEnable;
                        structCpy.ecoEnable = true;
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous values are restored  */
                                structCpy.ecoEnable = ecoEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PATH_SET_SOURCE:
                    {
                        bool pathEnable = false;
                        cy_en_clkpath_in_sources_t pathSrc = CY_SYSCLK_CLKPATH_IN_IMO;
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                        /* Backups old values */
                        switch (((cy_stc_pra_clkpathsetsource_t *) message->praData1)->clk_path)
                        {
                            case CY_PRA_CLKPATH_0:
                            pathEnable = structCpy.path0Enable;
                            pathSrc = structCpy.path0Src;
                            structCpy.path0Enable = true;
                            structCpy.path0Src = ((cy_stc_pra_clkpathsetsource_t *) message->praData1)->source;
                            break;

                            case CY_PRA_CLKPATH_1:
                            pathEnable = structCpy.path1Enable;
                            pathSrc = structCpy.path1Src;
                            structCpy.path1Enable = true;
                            structCpy.path1Src = ((cy_stc_pra_clkpathsetsource_t *) message->praData1)->source;
                            break;

                            case CY_PRA_CLKPATH_2:
                            pathEnable = structCpy.path2Enable;
                            pathSrc = structCpy.path2Src;
                            structCpy.path2Enable = true;
                            structCpy.path2Src = ((cy_stc_pra_clkpathsetsource_t *) message->praData1)->source;
                            break;

                            case CY_PRA_CLKPATH_3:
                            pathEnable = structCpy.path3Enable;
                            pathSrc = structCpy.path3Src;
                            structCpy.path3Enable = true;
                            structCpy.path3Src = ((cy_stc_pra_clkpathsetsource_t *) message->praData1)->source;
                            break;

                            case CY_PRA_CLKPATH_4:
                            pathEnable = structCpy.path4Enable;
                            pathSrc = structCpy.path4Src;
                            structCpy.path4Enable = true;
                            structCpy.path4Src = ((cy_stc_pra_clkpathsetsource_t *) message->praData1)->source;
                            break;

                            case CY_PRA_CLKPATH_5:
                            pathEnable = structCpy.path5Enable;
                            pathSrc = structCpy.path5Src;
                            structCpy.path5Enable = true;
                            structCpy.path5Src = ((cy_stc_pra_clkpathsetsource_t *) message->praData1)->source;
                            break;

                            default:
                            message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
                            break;
                        }
                        if ((message->praStatus == CY_PRA_STATUS_SUCCESS) && (CY_PRA_SKIP_SYS_CFG != message->praData2))
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous path values are restored  */
                                switch (((cy_stc_pra_clkpathsetsource_t *) message->praData1)->clk_path)
                                {
                                    case CY_PRA_CLKPATH_0:
                                    structCpy.path0Enable = pathEnable;
                                    structCpy.path0Src = pathSrc;
                                    break;

                                    case CY_PRA_CLKPATH_1:
                                    structCpy.path1Enable = pathEnable;
                                    structCpy.path1Src = pathSrc;
                                    break;

                                    case CY_PRA_CLKPATH_2:
                                    structCpy.path2Enable = pathEnable;
                                    structCpy.path2Src = pathSrc;
                                    break;

                                    case CY_PRA_CLKPATH_3:
                                    structCpy.path3Enable = pathEnable;
                                    structCpy.path3Src = pathSrc;
                                    break;

                                    case CY_PRA_CLKPATH_4:
                                    structCpy.path4Enable = pathEnable;
                                    structCpy.path4Src = pathSrc;
                                    break;

                                    case CY_PRA_CLKPATH_5:
                                    structCpy.path5Enable = pathEnable;
                                    structCpy.path5Src = pathSrc;
                                    break;

                                    default:
                                    message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
                                    break;
                                }
                            }
                            else
                            {
                                switch (((cy_stc_pra_clkpathsetsource_t *) message->praData1)->clk_path)
                                {
                                    case CY_PRA_CLKPATH_0:
                                    {
                                        if (structCpy.fllEnable)
                                        {
                                            /* Update FLL output frequency */
                                            structCpy.fllOutFreqHz = Cy_PRA_CalculateFLLOutFreq(&structCpy);
                                        }
                                        if (structCpy.hf0Source == CY_SYSCLK_CLKHF_IN_CLKPATH0)
                                        {
                                            /* Update HF0 output frequency */
                                            structCpy.hf0OutFreqMHz = CY_SYSLIB_DIV_ROUND(Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf0Source), ((1UL << (uint32_t)structCpy.hf0Divider) * CY_PRA_FREQUENCY_HZ_CONVERSION));
                                        }
                                    }
                                    break;

                                    case CY_PRA_CLKPATH_1:
                                    {
                                        if (structCpy.pll0Enable)
                                        {
                                            /* Update PLL0 output frequency */
                                            structCpy.pll0OutFreqHz = Cy_PRA_CalculatePLLOutFreq(CY_PRA_CLKPLL_1, &structCpy);
                                        }
                                        if (structCpy.hf0Source == CY_SYSCLK_CLKHF_IN_CLKPATH1)
                                        {
                                            /* Update HF0 output frequency */
                                            structCpy.hf0OutFreqMHz = CY_SYSLIB_DIV_ROUND(Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf0Source), ((1UL << (uint32_t)structCpy.hf0Divider) * CY_PRA_FREQUENCY_HZ_CONVERSION));
                                        }
                                    }
                                    break;

                                    case CY_PRA_CLKPATH_2:
                                    {
                                        if (structCpy.pll1Enable)
                                        {
                                            /* Update PLL1 output frequency */
                                            structCpy.pll1OutFreqHz = Cy_PRA_CalculatePLLOutFreq(CY_PRA_CLKPLL_2, &structCpy);
                                        }
                                        if (structCpy.hf0Source == CY_SYSCLK_CLKHF_IN_CLKPATH2)
                                        {
                                            /* Update HF0 output frequency */
                                            structCpy.hf0OutFreqMHz = CY_SYSLIB_DIV_ROUND(Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf0Source), ((1UL << (uint32_t)structCpy.hf0Divider) * CY_PRA_FREQUENCY_HZ_CONVERSION));
                                        }
                                    }
                                    break;

                                    case CY_PRA_CLKPATH_3:
                                    {
                                        if (structCpy.hf0Source == CY_SYSCLK_CLKHF_IN_CLKPATH3)
                                        {
                                            /* Update HF0 output frequency */
                                            structCpy.hf0OutFreqMHz = CY_SYSLIB_DIV_ROUND(Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf0Source), ((1UL << (uint32_t)structCpy.hf0Divider) * CY_PRA_FREQUENCY_HZ_CONVERSION));
                                        }
                                    }
                                    break;

                                    case CY_PRA_CLKPATH_4:
                                    {
                                        if (structCpy.hf0Source == CY_SYSCLK_CLKHF_IN_CLKPATH4)
                                        {
                                            /* Update HF0 output frequency */
                                            structCpy.hf0OutFreqMHz = CY_SYSLIB_DIV_ROUND(Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf0Source), ((1UL << (uint32_t)structCpy.hf0Divider) * CY_PRA_FREQUENCY_HZ_CONVERSION));
                                        }
                                    }
                                    break;

                                    case CY_PRA_CLKPATH_5:
                                    {
                                        if (structCpy.hf0Source == CY_SYSCLK_CLKHF_IN_CLKPATH5)
                                        {
                                            /* Update HF0 output frequency */
                                            structCpy.hf0OutFreqMHz = CY_SYSLIB_DIV_ROUND(Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf0Source), ((1UL << (uint32_t)structCpy.hf0Divider) * CY_PRA_FREQUENCY_HZ_CONVERSION));
                                        }
                                    }
                                    break;

                                    default:
                                    /* Unknown clock path */
                                    break;
                                }
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_FLL_MANCONFIG:
                    {
                        /* FLL manual configuration values are not written to the
                         * register but stored in the system config structure.
                         * These values are applied to the register
                         * after a call from CY_PRA_CLK_FUNC_FLL_ENABLE */
                        structCpy.fllMult = ((cy_stc_fll_manual_config_t *) message->praData1)->fllMult;
                        structCpy.fllRefDiv = ((cy_stc_fll_manual_config_t *) message->praData1)->refDiv;
                        structCpy.fllCcoRange = ((cy_stc_fll_manual_config_t *) message->praData1)->ccoRange;
                        structCpy.enableOutputDiv = ((cy_stc_fll_manual_config_t *) message->praData1)->enableOutputDiv;
                        structCpy.lockTolerance = ((cy_stc_fll_manual_config_t *) message->praData1)->lockTolerance;
                        structCpy.igain = ((cy_stc_fll_manual_config_t *) message->praData1)->igain;
                        structCpy.pgain = ((cy_stc_fll_manual_config_t *) message->praData1)->pgain;
                        structCpy.settlingCount = ((cy_stc_fll_manual_config_t *) message->praData1)->settlingCount;
                        structCpy.outputMode = ((cy_stc_fll_manual_config_t *) message->praData1)->outputMode;
                        structCpy.ccoFreq = ((cy_stc_fll_manual_config_t *) message->praData1)->cco_Freq;
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                    }
                    break;

                    case CY_PRA_CLK_FUNC_FLL_ENABLE:
                    {
                        /* FLL Enable is not allowed if it is already enabled */
                        if (structCpy.fllEnable == true) /* FLL is already enabled */
                        {
                            message->praStatus = CY_PRA_STATUS_ERROR_PROCESSING_FLL0_ENABLED;
                        }
                        else
                        {
                            structCpy.fllEnable = true;
                            /* FLL Enable API does not contain the FLL output value
                             * as the argument. So, calculate and update the FLL output value */
                            structCpy.fllOutFreqHz = Cy_PRA_CalculateFLLOutFreq(&structCpy);
                            if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                            {
                                message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                                if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                                {
                                    structCpy.fllOutFreqHz = CY_PRA_DEFAULT_ZERO;
                                    structCpy.fllEnable = false;
                                }
                                else
                                {
                                    /* Check if FLL is source to HF0 */
                                    if (structCpy.hf0Source == CY_SYSCLK_CLKHF_IN_CLKPATH0)
                                    {
                                        /* Update HF0 output frequency */
                                        structCpy.hf0OutFreqMHz = CY_SYSLIB_DIV_ROUND(Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf0Source), ((1UL << (uint32_t)structCpy.hf0Divider) * CY_PRA_FREQUENCY_HZ_CONVERSION));
                                    }
                                }
                            } /* (CY_PRA_SKIP_SYS_CFG != message->praData2) */
                            else
                            {
                                message->praStatus = CY_PRA_STATUS_SUCCESS;
                            }
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PLL_MANCONFIG:
                    {
                        /* Checks for the valid PLL number */
                        if((((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->clkPath == CY_PRA_CLKPATH_0) ||
                           (((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->clkPath > CY_SRSS_NUM_PLL))
                        {
                            message->praStatus = CY_PRA_STATUS_INVALID_PARAM_PLL_NUM;
                        }
                        else
                        {
                            /* PLL manual configuration values are not written to
                             * the register but stored in the system config structure.
                             * These values are applied to the register
                             * after a call from CY_PRA_CLK_FUNC_PLL_ENABLE. */
                            if(((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->clkPath == CY_PRA_CLKPATH_1)
                            {
                                structCpy.pll0FeedbackDiv = ((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->praConfig->feedbackDiv;
                                structCpy.pll0ReferenceDiv = ((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->praConfig->referenceDiv;
                                structCpy.pll0OutputDiv = ((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->praConfig->outputDiv;
                                structCpy.pll0LfMode = ((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->praConfig->lfMode;
                                structCpy.pll0OutputMode = ((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->praConfig->outputMode;
                            }
                            else
                            {
                                structCpy.pll1FeedbackDiv = ((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->praConfig->feedbackDiv;
                                structCpy.pll1ReferenceDiv = ((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->praConfig->referenceDiv;
                                structCpy.pll1OutputDiv = ((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->praConfig->outputDiv;
                                structCpy.pll1LfMode = ((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->praConfig->lfMode;
                                structCpy.pll1OutputMode = ((cy_stc_pra_clk_pll_manconfigure_t *) message->praData1)->praConfig->outputMode;
                            }
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_PLL_ENABLE:
                    {
                        if ((((message->praData1) == CY_PRA_CLKPLL_1) && (structCpy.pll0Enable == true))
                            || (((message->praData1) == CY_PRA_CLKPLL_2) && (structCpy.pll1Enable == true))
                            || (message->praData1 > CY_SRSS_NUM_PLL) || (message->praData1 == 0UL))
                        {
                            message->praStatus = CY_PRA_STATUS_ERROR_PROCESSING_PLL_ENABLED;
                        }
                        else
                        {
                            /* PLL Enable API does not contain the PLL output value
                             * as the argument. So, calculate and update the PLL output value */
                            if ((message->praData1) == CY_PRA_CLKPLL_1)
                            {
                                structCpy.pll0OutFreqHz = Cy_PRA_CalculatePLLOutFreq(CY_PRA_CLKPLL_1, &structCpy);
                                structCpy.pll0Enable = true;
                            }
                            else
                            {
                                structCpy.pll1OutFreqHz = Cy_PRA_CalculatePLLOutFreq(CY_PRA_CLKPLL_2, &structCpy);
                                structCpy.pll1Enable = true;
                            }
                            if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                            {
                                message->praStatus = Cy_PRA_SystemConfig(&structCpy);

                                if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                                {
                                    if ((message->praData1) == CY_PRA_CLKPLL_1)
                                    {
                                        structCpy.pll0OutFreqHz = CY_PRA_DEFAULT_ZERO;
                                        structCpy.pll0Enable = false;
                                    }
                                    else
                                    {
                                        structCpy.pll1OutFreqHz = CY_PRA_DEFAULT_ZERO;
                                        structCpy.pll1Enable = false;
                                    }
                                }
                                else /* PLL is enabled successfully */
                                {
                                    /* Check if PLL0 or PLL1 is source to HF0 */
                                    if ((structCpy.hf0Source == CY_SYSCLK_CLKHF_IN_CLKPATH1) || (structCpy.hf0Source == CY_SYSCLK_CLKHF_IN_CLKPATH2))
                                    {
                                        /* Update HF0 output frequency */
                                        structCpy.hf0OutFreqMHz = CY_SYSLIB_DIV_ROUND(Cy_SysClk_ClkPathGetFrequency((uint32_t) structCpy.hf0Source), ((1UL << (uint32_t)structCpy.hf0Divider) * CY_PRA_FREQUENCY_HZ_CONVERSION));
                                    }
                                }
                            } /* (CY_PRA_SKIP_SYS_CFG != message->praData2) */
                            else
                            {
                                message->praStatus = CY_PRA_STATUS_SUCCESS;
                            }

                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_SLOW_SET_DIVIDER:
                    {
                        uint8_t clkSlowDivTmp;
                        bool clkSlowEnableTmp;
                        /* Backups old values */
                        clkSlowEnableTmp = structCpy.clkSlowEnable;
                        clkSlowDivTmp = structCpy.clkSlowDiv;
                        structCpy.clkSlowEnable = true;
                        structCpy.clkSlowDiv = (uint8_t)(message->praData1);
                        if (CY_PRA_SKIP_SYS_CFG != message->praData2)
                        {
                            message->praStatus = Cy_PRA_SystemConfig(&structCpy);
                            if (message->praStatus != CY_PRA_STATUS_SUCCESS)
                            {
                                /* On failure, previous path values are restored */
                                structCpy.clkSlowDiv = clkSlowDivTmp;
                                structCpy.clkSlowEnable = clkSlowEnableTmp;
                            }
                        }
                        else
                        {
                            message->praStatus = CY_PRA_STATUS_SUCCESS;
                        }
                    }
                    break;

                    case CY_PRA_CLK_FUNC_EXT_CLK_SET_FREQUENCY:
                    {
                        structCpy.extClkEnable = true;
                        structCpy.extClkFreqHz = (uint32_t)(message->praData1);
                        message->praStatus = CY_PRA_STATUS_SUCCESS;
                    }
                    break;

                    default:
                        message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
                        break;
                }
            }
            else
            {
                message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
            }
            break;

        default:
            message->praStatus = CY_PRA_STATUS_ACCESS_DENIED;
           break;
    }

}
#endif /* (CY_CPU_CORTEX_M0P) */



/*******************************************************************************
* Function Name: Cy_PRA_SendCmd
****************************************************************************//**
*
* Takes the parameters, passes them to the secure Cortex-M0+ via IPC, waits for
* Cortex-M0+ to finish and reports the status.
*
* \param cmd The command to execute on the secure side. The macros for this
* parameter are defined in the cy_pra.h file with the CY_PRA_MSG_TYPE_ prefix.
* \param regIndex The index of the function or register depending on the command
* parameter. The macros for this parameter are defined in the cy_pra.h file with
* the CY_PRA_INDX_ prefix.
* \param clearMask Data sent to secure the core.
* \param setMask Additional data send to secure the core.
*
* \return The command execution status. For the register read command, the read
* value is returned.
*
*******************************************************************************/
#if defined(CY_DEVICE_PSOC6ABLE2)

    CY_SECTION_RAMFUNC_BEGIN
    #if !defined (__ICCARM__)
        CY_NOINLINE
    #endif
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
    cy_en_pra_status_t Cy_PRA_SendCmd(uint16_t cmd, uint16_t regIndex, uint32_t clearMask, uint32_t setMask)
    {
        cy_en_pra_status_t status;
    #if (CY_CPU_CORTEX_M0P)
        /* update structCpy variable */
        CY_ALIGN(4UL)cy_stc_pra_msg_t msgLocal;

        msgLocal.praCommand = cmd;
        msgLocal.praStatus  = CY_PRA_STATUS_REQUEST_SENT;
        msgLocal.praIndex   = regIndex;
        msgLocal.praData1   = clearMask;

        if (cmd == CY_PRA_MSG_TYPE_FUNC_POLICY)
        {
            msgLocal.praData2   = CY_PRA_SKIP_SYS_CFG;
            Cy_PRA_ProcessCmd(&msgLocal);
            status = CY_PRA_STATUS_SUCCESS;
            (void)setMask;
        }
        else if ((cmd == CY_PRA_MSG_TYPE_SYS_CFG_FUNC) && (regIndex == CY_PRA_FUNC_INIT_CYCFG_DEVICE))
        {
            msgLocal.praData2   = setMask;
            Cy_PRA_ProcessCmd(&msgLocal);
            status = (cy_en_pra_status_t) msgLocal.praStatus;
        }
        else
        {
            status = CY_PRA_STATUS_ACCESS_DENIED;
            (void)cmd;
            (void)regIndex;
            (void)clearMask;
            (void)setMask;
        }
    #else
        CY_ASSERT_L1(NULL != ipcPraBase);


        CY_ALIGN(4UL) cy_stc_pra_msg_t ipcMsg;
        uint32_t interruptState;

        ipcMsg.praCommand = cmd;
        ipcMsg.praStatus  = CY_PRA_STATUS_REQUEST_SENT;
        ipcMsg.praIndex   = regIndex;
        ipcMsg.praData1   = clearMask;
        ipcMsg.praData2   = setMask;

        interruptState = Cy_SysLib_EnterCriticalSection();

        while (0U == _FLD2VAL(IPC_STRUCT_ACQUIRE_SUCCESS, REG_IPC_STRUCT_ACQUIRE(ipcPraBase)))
        {
            /* Waits until the PRA IPC structure is acquired */
        }

        /* Sends the message */
        REG_IPC_STRUCT_DATA(ipcPraBase) = (uint32_t) &ipcMsg;

        /* Generates an acquire notification event by the PRA IPC interrupt structure */
        REG_IPC_STRUCT_NOTIFY(ipcPraBase) = _VAL2FLD(IPC_STRUCT_NOTIFY_INTR_NOTIFY, CY_PRA_IPC_NOTIFY_INTR);

        while (0U != _FLD2VAL(IPC_STRUCT_ACQUIRE_SUCCESS, REG_IPC_STRUCT_LOCK_STATUS(ipcPraBase)))
        {
            /* Waits until the PRA IPC structure is released */
        }

        Cy_SysLib_ExitCriticalSection(interruptState);

        /* Cortex-M0+ has an updated ipcMsg variable */

        status = (cy_en_pra_status_t) ipcMsg.praStatus;

        if (CY_PRA_STATUS_ACCESS_DENIED == status)
        {
            CY_HALT();
        }

        if (CY_PRA_MSG_TYPE_SYS_CFG_FUNC == ipcMsg.praCommand)
        {
        #if defined(CY_IP_MXBLESS)
            /* Update cy_BleEcoClockFreqHz for the proper Cy_SysLib_Delay functionality */
            if(((cy_stc_pra_system_config_t *) clearMask)->altHFclkFreq == CY_BLE_BLESS_ECO_FREQ_32MHZ)
            {
                cy_BleEcoClockFreqHz = CY_PRA_ALTHF_FREQ_32MHZ / (1UL << ((cy_stc_pra_system_config_t *) clearMask)->altHFsysClkDiv);
            }
            else
            {
                cy_BleEcoClockFreqHz = CY_PRA_ALTHF_FREQ_16MHZ / (1UL << ((cy_stc_pra_system_config_t *) clearMask)->altHFsysClkDiv);
            }

            if(((cy_stc_pra_system_config_t *) clearMask)->clkAltHfEnable == false)
            {
                cy_BleEcoClockFreqHz = 0UL;
            }
        #endif /* defined(CY_IP_MXBLESS) */

            cySysClkExtFreq = ((cy_stc_pra_system_config_t *) clearMask)->extClkFreqHz;

            SystemCoreClockUpdate();
        }

        if (CY_PRA_MSG_TYPE_REG32_GET == ipcMsg.praCommand)
        {
            status = (cy_en_pra_status_t)ipcMsg.praData1;
        }

    #endif /* (CY_CPU_CORTEX_M0P) */

        return status;
    }
#if defined(CY_DEVICE_PSOC6ABLE2)
    CY_SECTION_RAMFUNC_END
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */

#if (CY_CPU_CORTEX_M4) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_PRA_GetPinProtType
****************************************************************************//**
*
* Find the matching PORT and PIN number from External clock secure PIN list and
* returns protection status of the PIN.
*
*******************************************************************************/
    cy_en_pra_pin_prot_type_t Cy_PRA_GetPinProtType(GPIO_PRT_Type *base, uint32_t pinNum)
    {
        uint32_t index;
        cy_en_pra_pin_prot_type_t pinType = CY_PRA_PIN_SECURE_NONE;

        if ((NULL != base) && (CY_GPIO_IS_PIN_VALID(pinNum)))
        {
            for (index=0; index<CY_PRA_EXTCLK_PIN_NR; index++)
            {
                if (secExtclkPinList[index].port == base)
                {
                    pinType = CY_PRA_PIN_SECURE_UNCONSTRAINED;

                    if (secExtclkPinList[index].pinNum == pinNum)
                    {
                        pinType = CY_PRA_PIN_SECURE;
                        break;
                    }
                }
            }
        }

        return pinType;
    }

/*******************************************************************************
* Function Name: Cy_PRA_IsPortSecure
****************************************************************************//**
*
* Find the matching PORT from External clock secure PIN list and returns
* protection status of the PORT.
*
*******************************************************************************/
    bool Cy_PRA_IsPortSecure(GPIO_PRT_Type *base)
    {
        uint32_t index;
        bool retPort = false;
        if (NULL != base)
        {
            for (index=0; index<CY_PRA_EXTCLK_PIN_NR; index++)
            {
                if (secExtclkPinList[index].port == base)
                {
                    retPort = true;
                    break;
                }
            }
        }

        return retPort;
    }

#if defined(CY_DEVICE_PSOC6ABLE2)
/*******************************************************************************
* Function Name: Cy_PRA_IsHsiomSecure
****************************************************************************//**
*
* Find the matching PORT from External clock adjacent HSIOM list and returns
* protection status of the PORT.
*
*******************************************************************************/
    bool Cy_PRA_IsHsiomSecure(GPIO_PRT_Type *base)
    {
        uint32_t index;
        bool retPort = false;
        if (NULL != base)
        {
            for (index=0; index<CY_PRA_EXTCLK_PIN_NR; index++)
            {
                if (secExtClkAdjHsiomList[index].port == base)
                {
                    retPort = true;
                    break;
                }
            }
        }

        return retPort;
    }

#endif /* defined(CY_DEVICE_PSOC6ABLE2) */

/*******************************************************************************
* Function Name: Cy_PRA_GetPortRegIndex
****************************************************************************//**
*
* Find the matching PORT and PIN number from External clock secure PIN list and
* returns port address index
*
*******************************************************************************/
    uint16_t Cy_PRA_GetPortRegIndex(GPIO_PRT_Type *base, uint16_t subIndex)
    {
        uint32_t index;
        uint16_t portIndex;
        uint16_t retIndex = CY_PRA_REG_INDEX_COUNT; /* assigned with invalid index */

        if (NULL != base)
        {
            for (index=0; index<CY_PRA_EXTCLK_PIN_NR; index++)
            {
                if (secExtclkPinList[index].port == base)
                {
                    portIndex = secExtclkPinList[index].index;

                    switch (subIndex)
                    {
                        case CY_PRA_SUB_INDEX_PORT_OUT:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, OUT), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_OUT_CLR:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, OUT_CLR), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_OUT_SET:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, OUT_SET), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_OUT_INV:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, OUT_INV), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_IN:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, IN), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_INTR:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, INTR), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_INTR_MASK:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, INTR_MASK), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_INTR_MASKED:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, INTR_MASKED), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_INTR_SET:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND(offsetof(GPIO_PRT_Type, INTR_SET), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_INTR_CFG:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtIntrCfgOffset), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_CFG:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgOffset), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_CFG_IN:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgInOffset), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_CFG_OUT:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgOutOffset), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_PORT_CFG_SIO:
                        retIndex = portIndex + CY_SYSLIB_DIV_ROUND((uint16_t)(cy_device->gpioPrtCfgSioOffset), 4U);
                        break;
                        default:
                        retIndex = CY_PRA_REG_INDEX_COUNT;
                        break;
                    }

                    break;
                }
            }
        }
        return retIndex;
    }

/*******************************************************************************
* Function Name: Cy_PRA_GetHsiomRegIndex
****************************************************************************//**
*
* Find the matching PORT address from External clock secure PIN list and
* returns HSIOM port address index
*
*******************************************************************************/
    uint16_t Cy_PRA_GetHsiomRegIndex(GPIO_PRT_Type *base, uint16_t subIndex)
    {
        uint32_t index;
        uint16_t hsiomIndex;
        uint16_t retIndex = CY_PRA_REG_INDEX_COUNT; /* assigned with invalid index */

        if (NULL != base)
        {
            for (index=0; index<CY_PRA_EXTCLK_PIN_NR; index++)
            {
                if (secExtclkPinList[index].port == base)
                {
                    hsiomIndex = secExtclkPinList[index].hsiomIndex;

                    switch (subIndex)
                    {
                        case CY_PRA_SUB_INDEX_HSIOM_PORT0:
                        retIndex = hsiomIndex + CY_SYSLIB_DIV_ROUND(offsetof(HSIOM_PRT_V1_Type, PORT_SEL0), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_HSIOM_PORT1:
                        retIndex = hsiomIndex + CY_SYSLIB_DIV_ROUND(offsetof(HSIOM_PRT_V1_Type, PORT_SEL1), 4U);
                        break;
                        default:
                        retIndex = CY_PRA_REG_INDEX_COUNT;
                        break;
                    }
                    break;
                }
            }
        }
        return retIndex;
    }

#if defined(CY_DEVICE_PSOC6ABLE2)
/*******************************************************************************
* Function Name: Cy_PRA_GetAdjHsiomRegIndex
****************************************************************************//**
*
* Find the matching PORT address from External clock adjacent hsiom list and
* returns HSIOM port address index
*
*******************************************************************************/
    uint16_t Cy_PRA_GetAdjHsiomRegIndex(GPIO_PRT_Type *base, uint16_t subIndex)
    {
        uint32_t index;
        uint16_t hsiomIndex;
        uint16_t retIndex = CY_PRA_REG_INDEX_COUNT; /* assigned with invalid index */

        if (NULL != base)
        {
            for (index=0; index<CY_PRA_EXTCLK_PIN_NR; index++)
            {
                if (secExtClkAdjHsiomList[index].port == base)
                {
                    hsiomIndex = secExtClkAdjHsiomList[index].hsiomIndex;

                    switch (subIndex)
                    {
                        case CY_PRA_SUB_INDEX_HSIOM_PORT0:
                        retIndex = hsiomIndex + CY_SYSLIB_DIV_ROUND(offsetof(HSIOM_PRT_V1_Type, PORT_SEL0), 4U);
                        break;
                        case CY_PRA_SUB_INDEX_HSIOM_PORT1:
                        retIndex = hsiomIndex + CY_SYSLIB_DIV_ROUND(offsetof(HSIOM_PRT_V1_Type, PORT_SEL1), 4U);
                        break;
                        default:
                        retIndex = CY_PRA_REG_INDEX_COUNT;
                        break;
                    }
                    break;
                }
            }
        }
        return retIndex;
    }
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */

#endif /* (CY_CPU_CORTEX_M4) */


#if (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)

/* The mask to unlock Hibernate power mode */
#define HIBERNATE_UNLOCK_VAL                 ((uint32_t) 0x3Au << SRSS_PWR_HIBERNATE_UNLOCK_Pos)

/* The mask to set Hibernate power mode */
#define SET_HIBERNATE_MODE                   ((HIBERNATE_UNLOCK_VAL |\
                                               SRSS_PWR_HIBERNATE_FREEZE_Msk |\
                                               SRSS_PWR_HIBERNATE_HIBERNATE_Msk))

/* The mask to retain Hibernate power mode status */
#define HIBERNATE_RETAIN_STATUS_MASK         ((SRSS_PWR_HIBERNATE_TOKEN_Msk |\
                                               SRSS_PWR_HIBERNATE_MASK_HIBALARM_Msk |\
                                               SRSS_PWR_HIBERNATE_MASK_HIBWDT_Msk |\
                                               SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Msk |\
                                               SRSS_PWR_HIBERNATE_MASK_HIBPIN_Msk))

/** The mask for Hibernate wakeup sources */
#define HIBERNATE_WAKEUP_MASK               ((SRSS_PWR_HIBERNATE_MASK_HIBALARM_Msk |\
                                              SRSS_PWR_HIBERNATE_MASK_HIBWDT_Msk |\
                                              SRSS_PWR_HIBERNATE_POLARITY_HIBPIN_Msk |\
                                              SRSS_PWR_HIBERNATE_MASK_HIBPIN_Msk))

/** The define to update the token to indicate the transition into Hibernate */
#define HIBERNATE_TOKEN                    ((uint32_t) 0x1BU << SRSS_PWR_HIBERNATE_TOKEN_Pos)


/*******************************************************************************
* Function Name: Cy_PRA_PmHibernate
****************************************************************************//**
*
* Updates the SRSS_PWR_HIBERNATE register for the Cy_SysPm_SystemEnterHibernate and
* Cy_SysPm_IoUnfreeze functions.
*
*******************************************************************************/
static void Cy_PRA_PmHibernate(uint32_t funcProc)
{

    if(0UL == funcProc)
    {
        /* Saves the token to be retained through a wakeup sequence.
         * This could be used by Cy_SysLib_GetResetReason() to differentiate
         * Wakeup from a general reset event.
         * Saves the wakeup source(s) configuration.
         */
        SRSS_PWR_HIBERNATE = (SRSS_PWR_HIBERNATE & HIBERNATE_WAKEUP_MASK) | HIBERNATE_TOKEN;

        /* Disables the overriding the next pin-freeze command by the peripherals */
        SRSS_PWR_HIBERNATE |= SET_HIBERNATE_MODE;

        /* The second write causes freezing of I/O cells to save the I/O-cell state */
        SRSS_PWR_HIBERNATE |= SET_HIBERNATE_MODE;

        /* The third write cause system to enter Hibernate */
        SRSS_PWR_HIBERNATE |= SET_HIBERNATE_MODE;
    }
    else
    {
        /* Saves the last reset reason and wakeup polarity. Then, unfreeze I/O:
         * writes PWR_HIBERNATE.FREEZE=0, .UNLOCK=0x3A, .HIBERANTE=0
         */
        SRSS_PWR_HIBERNATE = (SRSS_PWR_HIBERNATE & HIBERNATE_RETAIN_STATUS_MASK) | HIBERNATE_UNLOCK_VAL;

        /* Locks Hibernate mode:
        * write PWR_HIBERNATE.HIBERNATE=0, UNLOCK=0x00, HIBERANTE=0
        */
        SRSS_PWR_HIBERNATE &= HIBERNATE_RETAIN_STATUS_MASK;
    }
}


/*******************************************************************************
* Function Name: Cy_PRA_PmCm4DpFlagSet
****************************************************************************//**
*
* Sets Deep Sleep Flag for the CM4 core.
*
*******************************************************************************/
static void Cy_PRA_PmCm4DpFlagSet(void)
{
    uint32_t ddftStructData;

    /* Acquires the IPC to prevent the changing of the shared resources at the same time */
    while (0U == _FLD2VAL(IPC_STRUCT_ACQUIRE_SUCCESS, REG_IPC_STRUCT_ACQUIRE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT))))
    {
        /* Waits until the IPC structure is released by another CPU */
    }

    ddftStructData = REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT));

    /* Updates the CM4 core Deep Sleep mask */
    ddftStructData |= (0x01UL << 28u);

    /* Updates the pointer to the latest saved structure */
    REG_IPC_STRUCT_DATA(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = ddftStructData;

    /* Releases the IPC */
    REG_IPC_STRUCT_RELEASE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT)) = 0U;

    /* Reads the release value to make sure it is set */
    (void) REG_IPC_STRUCT_RELEASE(CY_IPC_STRUCT_PTR(CY_IPC_CHAN_DDFT));
}

/* The timeout count for function Cy_PRA_ClkDeepSleepCallback() is sufficiently large for ~1 second */
#define CY_PRA_TIMEOUT (1000000UL)
/* These variables act as locks to prevent collisions between clock measurement and entry into
   Deep Sleep mode. See Cy_SysClk_DeepSleep(). */
static uint16_t changedSourcePaths = CY_PRA_DEFAULT_ZERO;
static uint16_t pllAutoModes = CY_PRA_DEFAULT_ZERO;


/*******************************************************************************
* Function Name: Cy_PRA_ClkDSBeforeTransition
****************************************************************************//**
*
* SysClock before deep sleep transition.
*
*******************************************************************************/
static cy_en_pra_status_t Cy_PRA_ClkDSBeforeTransition(void)
{
    uint32_t fllPll; /* 0 = FLL, all other values = a PLL */

    /* Initializes the storage of changed paths */
    changedSourcePaths = CY_PRA_DEFAULT_ZERO;
    pllAutoModes = CY_PRA_DEFAULT_ZERO;

    /* For FLL and each PLL */
    for (fllPll = 0UL; fllPll <= CY_SRSS_NUM_PLL; fllPll++)
    {
        /* If FLL or PLL is enabled */
        if ((0UL == fllPll) ? Cy_SysClk_FllIsEnabled() : Cy_SysClk_PllIsEnabled(fllPll))
        {
            /* And the FLL/PLL has ECO as a source */
            if (Cy_SysClk_ClkPathGetSource(fllPll) == CY_SYSCLK_CLKPATH_IN_ECO)
            {
                /* Bypasses the FLL/PLL */
                if (0UL == fllPll)
                {
                    CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
                }
                else
                {
                    if (((uint32_t)CY_SYSCLK_FLLPLL_OUTPUT_AUTO  == _FLD2VAL(SRSS_CLK_PLL_CONFIG_BYPASS_SEL, SRSS_CLK_PLL_CONFIG[fllPll - 1UL])) ||
                        ((uint32_t)CY_SYSCLK_FLLPLL_OUTPUT_AUTO1 == _FLD2VAL(SRSS_CLK_PLL_CONFIG_BYPASS_SEL, SRSS_CLK_PLL_CONFIG[fllPll - 1UL])))
                    {
                        pllAutoModes |= (uint16_t)(1UL << fllPll);
                    }

                    CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[fllPll - 1UL], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
                }

                /* Changes this path source to IMO */
                (void)Cy_SysClk_ClkPathSetSource(fllPll, CY_SYSCLK_CLKPATH_IN_IMO);

                /* Stores a record that this path source was changed from ECO */
                changedSourcePaths |= (uint16_t)(1UL << fllPll);
            }
            else if (0UL == fllPll)
            {
                CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_INPUT);
            }
            else
            {
                /* Does nothing */
            }
        }
    }

    return CY_PRA_STATUS_SUCCESS;
}

/*******************************************************************************
* Function Name: Cy_PRA_ClkDSAfterTransition
****************************************************************************//**
*
* SysClock after Deep Sleep transition.
*
*******************************************************************************/
static cy_en_pra_status_t Cy_PRA_ClkDSAfterTransition(void)
{
    /* Bit-mapped paths with enabled FLL/PLL sourced by ECO */
    uint32_t timeout = CY_PRA_TIMEOUT;
    cy_en_pra_status_t retVal = CY_PRA_STATUS_ERROR_SYSPM_TIMEOUT;

    /* After return from Deep Sleep, for each FLL/PLL, if needed, restore the source to ECO.
     * And block until the FLL/PLL has regained its frequency lock.
     */
    if (0U != changedSourcePaths)
    {
        /* If any FLL/PLL was sourced by the ECO, the timeout waits for the ECO to become fully stabilized again */
        while ((CY_SYSCLK_ECOSTAT_STABLE != Cy_SysClk_EcoGetStatus()) && (0UL != timeout))
        {
            timeout--;
        }

        if (0UL != timeout)
        {
            uint32_t fllPll; /* 0 = FLL, all other values = PLL */

            for (fllPll = 0UL; fllPll <= CY_SRSS_NUM_PLL; fllPll++)
            {
                /* If there is a correspondent record about a changed clock source */
                if (0U != (changedSourcePaths & (uint16_t)(1UL << fllPll)))
                {
                    /* Changes this path source back to ECO */
                    (void)Cy_SysClk_ClkPathSetSource(fllPll, CY_SYSCLK_CLKPATH_IN_ECO);

                    /* The timeout waits for FLL/PLL to regain a lock.
                     * Split FLL and PLL lock polling loops into two separate threads to minimize one polling loop duration.
                     */
                    if (0UL == fllPll)
                    {
                        while ((!Cy_SysClk_FllLocked()) && (0UL != timeout))
                        {
                            timeout--;
                        }
                    }
                    else
                    {
                        while ((!Cy_SysClk_PllLocked(fllPll)) && (0UL != timeout))
                        {
                            timeout--;
                        }
                    }

                    if (0UL != timeout)
                    {
                        /* Undoes the bypass for FLL/PLL */
                        if (0UL == fllPll)
                        {
                            CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT);
                        }
                        else
                        {
                            if (0U != (pllAutoModes & (uint16_t)(1UL << fllPll)))
                            {
                                CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[fllPll - 1UL], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_AUTO);
                            }
                            else
                            {
                                CY_REG32_CLR_SET(SRSS_CLK_PLL_CONFIG[fllPll - 1UL], SRSS_CLK_PLL_CONFIG_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT);
                            }
                        }

                        retVal = CY_PRA_STATUS_SUCCESS;
                    }
                }
            }
        }
    }
    else if (Cy_SysClk_FllIsEnabled())
    {
        /* The timeout waits for FLL to regain a lock */
        while ((!Cy_SysClk_FllLocked()) && (0UL != timeout))
        {
            timeout--;
        }

        if (0UL != timeout)
        {
            /* Undoes the bypass for FLL */
            CY_REG32_CLR_SET(SRSS_CLK_FLL_CONFIG3, SRSS_CLK_FLL_CONFIG3_BYPASS_SEL, CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT);
            retVal = CY_PRA_STATUS_SUCCESS;
        }
    }
    else
    {
        retVal = CY_PRA_STATUS_SUCCESS;
    }

    return (retVal);
}

/*******************************************************************************
* Function Name: Cy_PRA_RegAccessRangeValid
****************************************************************************//**
*
* Checks if the access is within the valid range and the access address is non-zero.
*
* \param index The index of the accessed register.
*
* \return Returns true for the valid access.
*
*******************************************************************************/
static bool Cy_PRA_RegAccessRangeValid(uint16_t index)
{
    bool accessValid = true;

    /* Checks if access is within the array range */
    if (index >= CY_PRA_REG_INDEX_COUNT)
    {
        accessValid = false;
    }
    else
    {
        /* Some registers do not exist for some families */
        if (regIndexToAddr[index].addr == (const volatile uint32_t *) 0U)
        {
            accessValid = false;
        }
    }

    return accessValid;
}


/*******************************************************************************
* Function Name: Cy_PRA_ClocksReset
****************************************************************************//**
*
* Initializes system clocks and dividers to the default state after reset.
*
*******************************************************************************/
static cy_en_pra_status_t Cy_PRA_ClocksReset(void)
{
    cy_en_pra_status_t returnStatus = CY_PRA_STATUS_SUCCESS;
    cy_en_sysclk_status_t sysClkStatus = CY_SYSCLK_SUCCESS;

    /* Sets the worst case memory wait states (! ultra low power, 150 MHz) */
    Cy_SysLib_SetWaitStates(false, CY_PRA_150MHZ_FREQUENCY);

    /* Resets the core clock path to default and disable all the FLLs/PLLs after Reset or Software reset */
    sysClkStatus = Cy_SysClk_ClkHfSetDivider(CY_PRA_CLKHF_0, CY_SYSCLK_CLKHF_NO_DIVIDE);
    if (CY_SYSCLK_SUCCESS != sysClkStatus)
    {
        returnStatus = CY_PRA_STATUS_ERROR_PROCESSING_CLKHF0;
    }

    /* Sets the default divider for FAST, PERI and SLOW clocks */
    Cy_SysClk_ClkFastSetDivider(CY_PRA_DIVIDER_0);
    Cy_SysClk_ClkPeriSetDivider(CY_PRA_DIVIDER_1);
    Cy_SysClk_ClkSlowSetDivider(CY_PRA_DIVIDER_0);

    SystemCoreClockUpdate();

    /* Disables All PLLs */
    if (CY_SRSS_NUM_PLL >= CY_PRA_CLKPLL_1)
    {
        sysClkStatus = Cy_SysClk_PllDisable(CY_PRA_CLKPLL_1);
    }

    if (CY_SYSCLK_SUCCESS != sysClkStatus)
    {
        returnStatus = CY_PRA_STATUS_ERROR_PROCESSING_PLL0;
    }

    if (CY_SRSS_NUM_PLL >= CY_PRA_CLKPLL_2)
    {
        sysClkStatus = Cy_SysClk_PllDisable(CY_PRA_CLKPLL_2);
    }

    if (CY_SYSCLK_SUCCESS != sysClkStatus)
    {
        returnStatus = CY_PRA_STATUS_ERROR_PROCESSING_PLL1;
    }

    /* Sets the CLK_PATH1 source to IMO */
    sysClkStatus = Cy_SysClk_ClkPathSetSource((uint32_t) CY_SYSCLK_CLKHF_IN_CLKPATH1, CY_SYSCLK_CLKPATH_IN_IMO);
    if (CY_SYSCLK_SUCCESS != sysClkStatus)
    {
        returnStatus = CY_PRA_STATUS_ERROR_PROCESSING_PATHMUX1;
    }

    /* Set the HF0 source to IMO if it is sourced from WCO */
    if (CY_SYSCLK_CLKHF_IN_CLKPATH0 == Cy_SysClk_ClkHfGetSource(CY_PRA_CLKHF_0))
    {
            if (CY_SYSCLK_CLKPATH_IN_WCO == Cy_SysClk_ClkPathGetSource((uint32_t) CY_SYSCLK_CLKHF_IN_CLKPATH0))
            {
                sysClkStatus = Cy_SysClk_ClkHfSetSource(CY_PRA_CLKHF_0, CY_SYSCLK_CLKHF_IN_CLKPATH1);
                if (CY_SYSCLK_SUCCESS != sysClkStatus)
                {
                    returnStatus = CY_PRA_STATUS_ERROR_PROCESSING_CLKHF0;
                }
                SystemCoreClockUpdate();
            }
    }

    sysClkStatus = Cy_SysClk_FllDisable();
    if (CY_SYSCLK_SUCCESS != sysClkStatus)
    {
        returnStatus = CY_PRA_STATUS_ERROR_PROCESSING_FLL0;
    }

    /* Sets the CLK_PATH0 source to IMO */
    sysClkStatus = Cy_SysClk_ClkPathSetSource((uint32_t) CY_SYSCLK_CLKHF_IN_CLKPATH0, CY_SYSCLK_CLKPATH_IN_IMO);
    if (CY_SYSCLK_SUCCESS != sysClkStatus)
    {
        returnStatus = CY_PRA_STATUS_ERROR_PROCESSING_PATHMUX0;
    }

    /* Sets the HF0 source to IMO via CLK_PATH0 */
    sysClkStatus = Cy_SysClk_ClkHfSetSource(CY_PRA_CLKHF_0, CY_SYSCLK_CLKHF_IN_CLKPATH0);
    if (CY_SYSCLK_SUCCESS != sysClkStatus)
    {
        returnStatus = CY_PRA_STATUS_ERROR_PROCESSING_CLKHF0;
    }

    #ifdef CY_IP_MXBLESS
        Cy_BLE_EcoReset();
    #endif

    return returnStatus;
}


/*******************************************************************************
* Function Name: Cy_PRA_BackupReset
****************************************************************************//**
*
* Resets the Backup domain and system clocks after System reset.
*
*******************************************************************************/
static cy_en_pra_status_t Cy_PRA_BackupReset(bool iloHibernateON)
{
    cy_en_pra_status_t returnStatus = CY_PRA_STATUS_SUCCESS;

    if (CY_SYSLIB_SUCCESS != Cy_SysLib_ResetBackupDomain())
    {
        returnStatus = CY_PRA_STATUS_ERROR_PROCESSING_PWR;
    }
    else
    {
        if (Cy_SysClk_IloIsEnabled())
        {
            if (CY_SYSCLK_SUCCESS != Cy_SysClk_IloDisable())
            {
                returnStatus = CY_PRA_STATUS_ERROR_PROCESSING_PWR;
            }
        }

        if (CY_PRA_STATUS_SUCCESS == returnStatus)
        {
            Cy_SysClk_IloEnable();
            Cy_SysClk_IloHibernateOn(iloHibernateON);
        }
    }

    return returnStatus;
}

/*******************************************************************************
* Function Name: Cy_PRA_ValidateSramPowerMode
****************************************************************************//**
*
* Validate SRAM power mode for a particular macro.
*
*******************************************************************************/
static cy_en_pra_status_t Cy_PRA_ValidateSramPowerMode(cy_en_syspm_sram_index_t sramNum, uint32_t sramMacroNum, cy_en_syspm_sram_pwr_mode_t sramPwrMode)
{
    uint32_t macroConfigIndex;
    cy_en_pra_status_t praStatus = CY_PRA_STATUS_SUCCESS;

    if (((uint8_t)sramNum < CY_PRA_SRAM_MAX_NR) && ((uint8_t)sramMacroNum < CY_PRA_SRAM_MACRO_MAX_NR))
    {
        /* find the sram macro */
        for (macroConfigIndex=0UL; macroConfigIndex<sramPwrModeConfig[sramNum].macroConfigCount; macroConfigIndex++)
        {
            if (0UL != (sramPwrModeConfig[sramNum].macroConfigs[macroConfigIndex].sramMacros & (1UL<<sramMacroNum)))
            {
                switch(sramPwrMode)
                {
                    case CY_SYSPM_SRAM_PWR_MODE_OFF:
                    if (0U == _FLD2VAL(CY_PRA_PM_SRAM_PWR_MODE_OFF, sramPwrModeConfig[sramNum].macroConfigs[macroConfigIndex].sramPwrMode))
                    {
                        praStatus = CY_PRA_STATUS_INVALID_PARAM;
                    }
                    break;
                    case CY_SYSPM_SRAM_PWR_MODE_RET:
                    if (0U == _FLD2VAL(CY_PRA_PM_SRAM_PWR_MODE_RETAIN, sramPwrModeConfig[sramNum].macroConfigs[macroConfigIndex].sramPwrMode))
                    {
                        praStatus = CY_PRA_STATUS_INVALID_PARAM;
                    }
                    break;
                    case CY_SYSPM_SRAM_PWR_MODE_ON:
                    if (0U == _FLD2VAL(CY_PRA_PM_SRAM_PWR_MODE_ON, sramPwrModeConfig[sramNum].macroConfigs[macroConfigIndex].sramPwrMode))
                    {
                        praStatus = CY_PRA_STATUS_INVALID_PARAM;
                    }
                    break;
                    default:
                    /* invalid power mode */
                    break;
                }
                break; /* found the macro number */
            }
        }

        /* if configuration is not present in policy, then all power modes are allowed */
    }
    else
    {
        praStatus = CY_PRA_STATUS_INVALID_PARAM;
    }

    return praStatus;
}

/*******************************************************************************
* Function Name: Cy_PRA_ValidateEntireSramPowerMode
****************************************************************************//**
*
* Validate SRAM power mode for all macros.
*
*******************************************************************************/
static cy_en_pra_status_t Cy_PRA_ValidateEntireSramPowerMode(cy_en_syspm_sram_index_t sramNum, cy_en_syspm_sram_pwr_mode_t sramPwrMode)
{
    uint32_t macroConfigIndex;
    cy_en_pra_status_t praStatus = CY_PRA_STATUS_SUCCESS;

    if ((uint8_t)sramNum < CY_PRA_SRAM_MAX_NR)
    {
        /* find the sram macro */
        for (macroConfigIndex=0UL; macroConfigIndex<sramPwrModeConfig[sramNum].macroConfigCount; macroConfigIndex++)
        {
            switch(sramPwrMode)
            {
                case CY_SYSPM_SRAM_PWR_MODE_OFF:
                if (0U == _FLD2VAL(CY_PRA_PM_SRAM_PWR_MODE_OFF, sramPwrModeConfig[sramNum].macroConfigs[macroConfigIndex].sramPwrMode))
                {
                    praStatus = CY_PRA_STATUS_INVALID_PARAM;
                }
                break;
                case CY_SYSPM_SRAM_PWR_MODE_RET:
                if (0U == _FLD2VAL(CY_PRA_PM_SRAM_PWR_MODE_RETAIN, sramPwrModeConfig[sramNum].macroConfigs[macroConfigIndex].sramPwrMode))
                {
                    praStatus = CY_PRA_STATUS_INVALID_PARAM;
                }
                break;
                case CY_SYSPM_SRAM_PWR_MODE_ON:
                if (0U == _FLD2VAL(CY_PRA_PM_SRAM_PWR_MODE_ON, sramPwrModeConfig[sramNum].macroConfigs[macroConfigIndex].sramPwrMode))
                {
                    praStatus = CY_PRA_STATUS_INVALID_PARAM;
                }
                break;
                default:
                /* invalid power mode */
                break;
            }
            if (praStatus == CY_PRA_STATUS_INVALID_PARAM)
            {
                break;
            }
        }

        /* if configuration is not present in policy, then all power modes are allowed */
    }
    else
    {
        praStatus = CY_PRA_STATUS_INVALID_PARAM;
    }

    return praStatus;
}

#endif /* (CY_CPU_CORTEX_M0P) */

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 17.2');

#endif /* (CY_DEVICE_SECURE) */

#endif /* CY_IP_M4CPUSS */

/* [] END OF FILE */
