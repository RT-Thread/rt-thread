/***************************************************************************//**
* \file cy_prot.c
* \version 1.20
*
* \brief
* Provides an API implementation of the Protection Unit driver
*
********************************************************************************
* \copyright
* Copyright 2016-2018, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_prot.h"

#if defined(__cplusplus)
extern "C" {
#endif

static bool Prot_IsSmpuStructDisabled(uint32_t smpuStcIndex);
static bool Prot_IsPpuProgStructDisabled(uint32_t ppuStcIndex);
static cy_en_prot_status_t Prot_ConfigPpuAtt(volatile uint32_t * reg, uint16_t pcMask, 
                                       cy_en_prot_perm_t userPermission, cy_en_prot_perm_t privPermission, bool secure);

/* Define to enable all attributes for SMPU slave structure */
#define PROT_SMPU_STRUCT_ATT0_ENABLE_ALL_MASK      (PROT_SMPU_SMPU_STRUCT_ATT0_UR_Msk | \
                                                    PROT_SMPU_SMPU_STRUCT_ATT0_UW_Msk | \
                                                    PROT_SMPU_SMPU_STRUCT_ATT0_UX_Msk | \
                                                    PROT_SMPU_SMPU_STRUCT_ATT0_PR_Msk | \
                                                    PROT_SMPU_SMPU_STRUCT_ATT0_PW_Msk | \
                                                    PROT_SMPU_SMPU_STRUCT_ATT0_PX_Msk | \
                                                    PROT_SMPU_SMPU_STRUCT_ATT0_NS_Msk)

 /* Define to enable all attributes for programmable PPU slave structure */
#define PROT_PERI_PPU_PR_ATT0_ENABLE_ALL_MASK      (PERI_PPU_PR_ATT0_UR_Msk | \
                                                    PERI_PPU_PR_ATT0_UW_Msk | \
                                                    PERI_PPU_PR_ATT0_UX_Msk | \
                                                    PERI_PPU_PR_ATT0_PR_Msk | \
                                                    PERI_PPU_PR_ATT0_PW_Msk | \
                                                    PERI_PPU_PR_ATT0_PX_Msk | \
                                                    PERI_PPU_PR_ATT0_NS_Msk)

#define PROT_PERI_PPU_PROG_PC1_PC3_MASK            (0xffffffe0UL)  /* PC1 - PC3 bits mask */

/*******************************************************************************
* Function Name: Cy_Prot_ConfigBusMaster
****************************************************************************//**
*
* Configures the allowed protection contexts, security (secure/non-secure)
* and privilege level of the bus transaction created by the specified master.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param busMaster
* Indicates which master needs to be configured. Refer to the CPUSS_MS_ID_X
* defines in the device config header file.
* 
* \param privileged
* Boolean to define the privilege level of all subsequent bus transfers.
* True - privileged, False - not privileged.
* Note that this is an inherited value. If not inherited, then this bit will 
* be used.
*
* \param secure
* Security setting for the master. True - Secure, False - Not secure.
* 
* \param pcMask
* This is a 16 bit value of the allowed contexts, it is an OR'ed (|) field of the
* provided defines in cy_prot.h. For example: (CY_PROT_PCMASK1 | CY_PROT_PCMASK3 | CY_PROT_PCMASK4)
* \note The function accepts pcMask values from CY_PROT_PCMASK1 to CY_PROT_PCMASK15. 
* But each device has its own number of available protection contexts. 
* That number is defined by PERI_PC_NR in the config file.
*
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | The function completed successfully.
*   CY_PROT_FAILURE      | The resource is locked.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigBusMaster
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigBusMaster(en_prot_master_t busMaster, bool privileged, bool secure, uint32_t pcMask)
{
    cy_en_prot_status_t status = CY_PROT_SUCCESS;
    uint32_t regVal;
    volatile uint32_t *addrMsCtl; /* addrMsCtl is pointer to a register that is volatile by 
                                   * nature as can be changed outside of firmware control. 
                                   */

    CY_ASSERT_L1(CY_PROT_IS_BUS_MASTER_VALID(busMaster));
    CY_ASSERT_L2(CY_PROT_IS_PC_MASK_VALID(pcMask));
    
    /* Get the address of Master x protection context control register (MSx_CTL) */
    addrMsCtl = (uint32_t *)(CY_PROT_BASE + (uint32_t)((uint32_t)busMaster << CY_PROT_MSX_CTL_SHIFT));

    /* Get bitfields for MSx_CTL */
    regVal = _VAL2FLD(PROT_SMPU_MS0_CTL_NS, !secure)   /* Security setting */
            | _VAL2FLD(PROT_SMPU_MS0_CTL_P, privileged) /* Privileged setting */
            | _VAL2FLD(PROT_SMPU_MS0_CTL_PC_MASK_15_TO_1, pcMask); /* Protection context mask */
            
    /* Set the value of MSx_CTL */
    *addrMsCtl = regVal;

    /* Check if the MSx_CTL register is successfully updated with the new register value. 
     * The register will not be updated for the invalid master-protection context. 
     */ 
    status = (*addrMsCtl != regVal) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_SetActivePC
****************************************************************************//**
*
* Sets the current/active protection context of the specified bus master.
* 
* Allowed PC values are 1-15. If this value is not inherited from another bus 
* master, the value set through this function is used.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param busMaster
* The bus master to configure. Refer to the CPUSS_MS_ID_X defines in the device
* config header file.
* 
* \param pc
* Active protection context of the specified master \ref cy_en_prot_pc_t. 
* \note that only those protection contexts allowed by the pcMask (which was 
* configured in \ref Cy_Prot_ConfigBusMaster) will take effect. 
* \note The function accepts pcMask values from CY_PROT_PC1 to CY_PROT_PC15. 
* But each device has its own number of available protection contexts. 
* That number is defined by PERI_PC_NR in the config file.
*
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | The function completed successfully.
*   CY_PROT_FAILURE      | The resource is locked.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_SetActivePC
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_SetActivePC(en_prot_master_t busMaster, uint32_t pc)
{
    cy_en_prot_status_t status;
    
    CY_ASSERT_L1(CY_PROT_IS_BUS_MASTER_VALID(busMaster));
    CY_ASSERT_L2(CY_PROT_IS_PC_VALID(pc));
    
    PROT_MPU_MS_CTL(busMaster) = _VAL2FLD(PROT_MPU_MS_CTL_PC, pc) | _VAL2FLD(PROT_MPU_MS_CTL_PC_SAVED, pc);
    status = (_FLD2VAL(PROT_MPU_MS_CTL_PC, PROT_MPU_MS_CTL(busMaster)) != pc) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_GetActivePC
****************************************************************************//**
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* Returns the active protection context of a master. 
*
* \param busMaster
* The bus master, whose protection context is being read. Refer to the 
* CPUSS_MS_ID_X defines in the device config header file.
* 
* \return
* Active protection context of the master \ref cy_en_prot_pc_t.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_SetActivePC
*
*******************************************************************************/
uint32_t Cy_Prot_GetActivePC(en_prot_master_t busMaster)
{
    
    CY_ASSERT_L1(CY_PROT_IS_BUS_MASTER_VALID(busMaster));
    
    return ((uint32_t)_FLD2VAL(PROT_MPU_MS_CTL_PC, PROT_MPU_MS_CTL(busMaster)));
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigMpuStruct
****************************************************************************//**
*
* This function configures a memory protection unit (MPU) struct with its 
* protection attributes. 
*
* The protection structs act like the gatekeepers for a master's accesses to
* memory, allowing only the permitted transactions to go through.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param base
* The base address for the MPU struct being configured. 
* 
* \param config
* Initialization structure containing all the protection attributes.
* 
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | The MPU struct was configured.
*   CY_PROT_FAILURE      | Configuration failed due to a protection violation.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigMpuStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigMpuStruct(PROT_MPU_MPU_STRUCT_Type* base, const cy_stc_mpu_cfg_t* config)
{
    cy_en_prot_status_t status;
    uint32_t addrReg;
    uint32_t attReg;

    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_MPU_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_MPU_PERM_VALID(config->privPermission));
    CY_ASSERT_L3(CY_PROT_IS_REGION_SIZE_VALID(config->regionSize));

    addrReg = _VAL2FLD(PROT_MPU_MPU_STRUCT_ADDR_SUBREGION_DISABLE, config->subregions)
              | _VAL2FLD(PROT_MPU_MPU_STRUCT_ADDR_ADDR24, (uint32_t)((uint32_t)config->address >> CY_PROT_ADDR_SHIFT));
    attReg  = ((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK)
              | (((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
              | _VAL2FLD(PROT_MPU_MPU_STRUCT_ATT_NS, !(config->secure))
              | _VAL2FLD(PROT_MPU_MPU_STRUCT_ATT_REGION_SIZE, config->regionSize);
    PROT_MPU_MPU_STRUCT_ATT(base) = attReg;
    PROT_MPU_MPU_STRUCT_ADDR(base) = addrReg;
    status = ((PROT_MPU_MPU_STRUCT_ADDR(base) != addrReg) || (PROT_MPU_MPU_STRUCT_ATT(base) != attReg)) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnableMpuStruct
****************************************************************************//**
*
* Enables the MPU struct, which allows the MPU protection attributes to 
* take effect. 
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param base
* The base address of the MPU struct being configured. 
*
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | The MPU struct was enabled.
*   CY_PROT_FAILURE      | The MPU struct is disabled and possibly locked.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnableMpuStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnableMpuStruct(PROT_MPU_MPU_STRUCT_Type* base)
{
    cy_en_prot_status_t status;
    
    CY_ASSERT_L1(NULL != base);
    
    PROT_MPU_MPU_STRUCT_ATT(base) |= _VAL2FLD(PROT_MPU_MPU_STRUCT_ATT_ENABLED, CY_PROT_STRUCT_ENABLE);
    status = (_FLD2VAL(PROT_MPU_MPU_STRUCT_ATT_ENABLED, PROT_MPU_MPU_STRUCT_ATT(base)) != CY_PROT_STRUCT_ENABLE) ?
                CY_PROT_FAILURE : CY_PROT_SUCCESS;
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisableMpuStruct
****************************************************************************//**
*
* Disables the MPU struct, which prevents the MPU protection attributes
* from taking effect.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param base
* The base address of the MPU struct being configured. 
*
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | The MPU struct was disabled.
*   CY_PROT_FAILURE      | The MPU struct is enabled and possibly locked.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisableMpuStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisableMpuStruct(PROT_MPU_MPU_STRUCT_Type* base)
{
    cy_en_prot_status_t status;

    CY_ASSERT_L1(NULL != base);
    
    PROT_MPU_MPU_STRUCT_ATT(base) &= ~_VAL2FLD(PROT_MPU_MPU_STRUCT_ATT_ENABLED, CY_PROT_STRUCT_ENABLE);
    status = (_FLD2VAL(PROT_MPU_MPU_STRUCT_ATT_ENABLED, PROT_MPU_MPU_STRUCT_ATT(base)) == CY_PROT_STRUCT_ENABLE) ?
               CY_PROT_FAILURE : CY_PROT_SUCCESS;
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigSmpuMasterStruct
****************************************************************************//**
*
* Configures a Shared Memory Protection Unit (SMPU) master protection 
* struct with its protection attributes. 
*
* This function configures the master struct governing the corresponding slave
* struct pair. It is a mechanism to protect the slave SMPU struct. Since the
* memory location of the slave struct is known, the address, regionSize and
* subregions of the configuration struct are not applicable.
*
* Note that only the user/privileged write permissions are configurable. The 
* read and execute permissions are read-only and cannot be configured.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param base
* The register base address of the protection struct being configured.
* 
* \param config
* Initialization structure with all the protection attributes.
* 
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | SMPU master struct was successfully configured.
*   CY_PROT_FAILURE      | The resource is locked.
*   CY_PROT_BAD_PARAM    | An incorrect/invalid parameter was passed.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigSmpuMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigSmpuMasterStruct(PROT_SMPU_SMPU_STRUCT_Type* base, const cy_stc_smpu_cfg_t* config)
{
    cy_en_prot_status_t status;
    uint32_t attReg;
    
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L2(CY_PROT_IS_PC_MASK_VALID(config->pcMask));
    CY_ASSERT_L3(CY_PROT_IS_SMPU_MS_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_SMPU_MS_PERM_VALID(config->privPermission));
    
    if(((uint32_t)config->pcMask & CY_PROT_SMPU_PC_LIMIT_MASK) != 0UL) 
    {
        /* PC mask out of range - not supported in device */
        status = CY_PROT_BAD_PARAM;
    }
    else
    {
        /* ADDR1 is read only. Only configure ATT1 */
        attReg = ((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK)
                    | (uint32_t)(((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
                    | _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT1_NS, !(config->secure))
                    | _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT1_PC_MASK_15_TO_1, config->pcMask)
                    /* No region size - read only for master structs */
                    | _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT1_PC_MATCH, config->pcMatch);
        if ((attReg & CY_PROT_SMPU_ATT1_MASK) != attReg)
        {
            /* Invalid parameter was passed */
            status = CY_PROT_BAD_PARAM;
        }
        else
        {
            PROT_SMPU_SMPU_STRUCT_ATT1(base) = attReg;
            status = ((PROT_SMPU_SMPU_STRUCT_ATT1(base) & CY_PROT_SMPU_ATT1_MASK) != attReg) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
        }
    }
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigSmpuSlaveStruct
****************************************************************************//**
*
* Configures a Shared Memory Protection Unit (SMPU) slave protection 
* struct with its protection attributes. 
* 
* This function configures the slave struct of an SMPU pair, which can protect
* any memory region in a device from invalid bus master accesses.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param base
* The register base address of the protection structure being configured.
* 
* \param config
* Initialization structure with all the protection attributes.
* 
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | SMPU slave struct was successfully configured.
*   CY_PROT_FAILURE      | The resource is locked.
*   CY_PROT_BAD_PARAM    | An incorrect/invalid parameter was passed.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigSmpuSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigSmpuSlaveStruct(PROT_SMPU_SMPU_STRUCT_Type* base, const cy_stc_smpu_cfg_t* config)
{
    cy_en_prot_status_t status = CY_PROT_SUCCESS;
    uint32_t addrReg;
    uint32_t attReg;
    
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L2(CY_PROT_IS_PC_MASK_VALID(config->pcMask));
    CY_ASSERT_L3(CY_PROT_IS_SMPU_SL_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_SMPU_SL_PERM_VALID(config->privPermission));
    CY_ASSERT_L3(CY_PROT_IS_REGION_SIZE_VALID(config->regionSize));

    if(((uint32_t)config->pcMask & CY_PROT_SMPU_PC_LIMIT_MASK) != 0UL) 
    {
        /* PC mask out of range - not supported in device */
        status = CY_PROT_BAD_PARAM;
    }
    else
    {
        addrReg= _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ADDR0_SUBREGION_DISABLE, config->subregions)
                    | _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ADDR0_ADDR24, (uint32_t)((uint32_t)config->address >> CY_PROT_ADDR_SHIFT));
        attReg= ((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK)
                    | (uint32_t)(((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
                    | _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT0_NS, !(config->secure))
                    | _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT0_PC_MASK_15_TO_1, config->pcMask)
                    | _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT0_REGION_SIZE, config->regionSize)
                    | _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT0_PC_MATCH, config->pcMatch);
        PROT_SMPU_SMPU_STRUCT_ATT0(base) = attReg;
        PROT_SMPU_SMPU_STRUCT_ADDR0(base) = addrReg;
        status = ((PROT_SMPU_SMPU_STRUCT_ADDR0(base) != addrReg) || ((PROT_SMPU_SMPU_STRUCT_ATT0(base) & CY_PROT_SMPU_ATT0_MASK) != attReg))
            ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnableSmpuMasterStruct
****************************************************************************//**
*
* Enables the Master SMPU structure.
*
* This is an SMPU master struct enable function. The SMPU protection settings
* will take effect after successful completion of this function call.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | The Master PU struct was enabled.
*   CY_PROT_FAILURE      | The Master PU struct is disabled and possibly locked.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnableSmpuMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnableSmpuMasterStruct(PROT_SMPU_SMPU_STRUCT_Type* base)
{
    cy_en_prot_status_t status;
    
    CY_ASSERT_L1(NULL != base);
    
    PROT_SMPU_SMPU_STRUCT_ATT1(base) |= _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT1_ENABLED, CY_PROT_STRUCT_ENABLE);
    status = (_FLD2VAL(PROT_SMPU_SMPU_STRUCT_ATT1_ENABLED, PROT_SMPU_SMPU_STRUCT_ATT1(base)) != CY_PROT_STRUCT_ENABLE) ?
                CY_PROT_FAILURE : CY_PROT_SUCCESS;
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisableSmpuMasterStruct
****************************************************************************//**
*
* Disables the Master SMPU structure.
*
* This is an SMPU master struct disable function. The SMPU protection settings
* will seize to take effect after successful completion of this function call.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | The Master PU struct was disabled.
*   CY_PROT_FAILURE      | The Master PU struct is enabled and possibly locked.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisableSmpuMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisableSmpuMasterStruct(PROT_SMPU_SMPU_STRUCT_Type* base)
{
    cy_en_prot_status_t status;
    
    CY_ASSERT_L1(NULL != base);
    
    PROT_SMPU_SMPU_STRUCT_ATT1(base) &= ~_VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT1_ENABLED, CY_PROT_STRUCT_ENABLE);
    status = (_FLD2VAL(PROT_SMPU_SMPU_STRUCT_ATT1_ENABLED, PROT_SMPU_SMPU_STRUCT_ATT1(base)) == CY_PROT_STRUCT_ENABLE) ?
                CY_PROT_FAILURE : CY_PROT_SUCCESS;
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnableSmpuSlaveStruct
****************************************************************************//**
*
* Enables the Slave SMPU structure.
*
* This is an SMPU slave struct enable function. The SMPU protection settings
* will take effect after successful completion of this function call.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | The Slave PU struct was enabled.
*   CY_PROT_FAILURE      | The Slave PU struct is disabled and possibly locked.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnableSmpuSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnableSmpuSlaveStruct(PROT_SMPU_SMPU_STRUCT_Type* base)
{
    cy_en_prot_status_t status;
    
    CY_ASSERT_L1(NULL != base);
    
    PROT_SMPU_SMPU_STRUCT_ATT0(base) |= _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
    status = (_FLD2VAL(PROT_SMPU_SMPU_STRUCT_ATT0_ENABLED, PROT_SMPU_SMPU_STRUCT_ATT0(base)) != CY_PROT_STRUCT_ENABLE) ?
                CY_PROT_FAILURE : CY_PROT_SUCCESS;
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisableSmpuSlaveStruct
****************************************************************************//**
*
* Disables the Slave SMPU structure.
*
* This is an SMPU slave struct disable function. The SMPU protection settings
* will seize to take effect after successful completion of this function call.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*   CY_PROT_SUCCESS      | The Slave PU struct was disabled.
*   CY_PROT_FAILURE      | The Slave PU struct is enabled and possibly locked.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisableSmpuSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisableSmpuSlaveStruct(PROT_SMPU_SMPU_STRUCT_Type* base)
{
    cy_en_prot_status_t status;
    
    CY_ASSERT_L1(NULL != base);
    
    PROT_SMPU_SMPU_STRUCT_ATT0(base) &= ~_VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
    status = (_FLD2VAL(PROT_SMPU_SMPU_STRUCT_ATT0_ENABLED, PROT_SMPU_SMPU_STRUCT_ATT0(base)) == CY_PROT_STRUCT_ENABLE) ?
                CY_PROT_FAILURE : CY_PROT_SUCCESS;
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_GetSmpuStruct
****************************************************************************//**
*
* Functions returns a pointer of the requested unused SMPU structure. It 
* searches the SMPU structures until it finds one that both the slave and master
* sections are disabled. After an available structure is located, function 
* enables the slave structure and set the ATT0[7:0] bits to 0xFF, to make sure 
* that a subsequent call will not see this as an available (unused) SMPU. 
*
* It is up to the user to implement, if needed, a system in which a semaphore 
* will lock-out all but one CPU from calling this function at once.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param base
* The base address for the SMPU structure returned if an unused structure was 
* found. If an empty structure was not found, the returned pointer is NULL.
*
* \param reqMode
* This parameter (request mode) selects how the user wants to select a SMPU 
* structure.
*
*   reqMode                 | Description
* --------------------------| -----------------------------
* CY_PROT_REQMODE_HIGHPRIOR | Return the SMPU structure with the highest priority.
* CY_PROT_REQMODE_LOWPRIOR  | Return the SMPU structure with the lowest priority.
* CY_PROT_REQMODE_INDEX     | Return the SMPU structure with the specific index.
*
* \param smpuIndex
* This is the index of the requested SMPU structure. It is only used if the 
* request mode is reqMode = CY_PROT_REQMODE_INDEX.
*
* \return
* Status of the function call.
*
*   Status              | Description
* ----------------------| ---------------------------------------
* CY_PROT_SUCCESS       | The Slave PU struct was disabled.
* CY_PROT_FAILURE       | The Master or Slave SMPU struct is disabled and possibly locked.
* CY_PROT_UNAVAILABLE   | The requested structure in use or there were no unused structures.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_GetSmpuStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_GetSmpuStruct(PROT_SMPU_SMPU_STRUCT_Type** base, 
                                          cy_en_prot_req_mode_t reqMode, uint32_t smpuIndex)
{
    CY_ASSERT_L3(CY_PROT_IS_SMPU_REQ_MODE_VALID(reqMode));
    CY_ASSERT_L2(CY_PROT_IS_SMPU_IDX_VALID(smpuIndex));

    cy_en_prot_status_t status = CY_PROT_UNAVAILABLE;
    int32_t stcIdx = (int32_t)smpuIndex;

    *base = NULL;

    switch (reqMode)
    {
        /* The SMPU priority goes from PROT_SMPU_STRUCT_HIGHEST_PR 
        *  (highest priority) to 0 (lowest priority)
        */
        case CY_PROT_REQMODE_HIGHPRIOR:

            stcIdx = PROT_SMPU_STRUCT_WTH_HIGHEST_PR;
            do
            {
                if (Prot_IsSmpuStructDisabled((uint32_t)stcIdx))
                {
                    status = CY_PROT_SUCCESS;
                }
                else
                {
                    --stcIdx;
                }
            } while ((stcIdx >= 0) && (CY_PROT_SUCCESS != status));
            break;
        
        case CY_PROT_REQMODE_LOWPRIOR:
            stcIdx = 0;
            do
            {
                if (Prot_IsSmpuStructDisabled((uint32_t)stcIdx))
                {
                    status = CY_PROT_SUCCESS;
                }
                else
                {
                    ++stcIdx;
                }
            } while ((stcIdx <= PROT_SMPU_STRUCT_WTH_HIGHEST_PR) && (CY_PROT_SUCCESS != status));
            break;
        
        case CY_PROT_REQMODE_INDEX:
            if (Prot_IsSmpuStructDisabled((uint32_t)stcIdx))
            {
                status = CY_PROT_SUCCESS;
            }
            break;

        default:
            break;
    }

    /* Proceed if required structure is found */
    if (CY_PROT_SUCCESS == status)
    {
        /* Enable Slave SMPU struct */
        PROT_SMPU_SMPU_STRUCT_IDX_ATT0(stcIdx) |= _VAL2FLD(PROT_SMPU_SMPU_STRUCT_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
        
        status = 
        (_FLD2VAL(PROT_SMPU_SMPU_STRUCT_ATT0_ENABLED, PROT_SMPU_SMPU_STRUCT_IDX_ATT0(stcIdx)) != CY_PROT_STRUCT_ENABLE) ?
        CY_PROT_FAILURE : CY_PROT_SUCCESS;

        /* Enable all attributes only if Slave struct was enabled */
        if (CY_PROT_SUCCESS == status)
        {
            *base = (PROT_SMPU_SMPU_STRUCT_Type* ) PROT_SMPU_SMPU_STRUCT_IDX(stcIdx);
            PROT_SMPU_SMPU_STRUCT_IDX_ATT0(stcIdx) |= PROT_SMPU_STRUCT_ATT0_ENABLE_ALL_MASK;
        }
    }
    return status;
}


/*******************************************************************************
* Function Name: Prot_ConfigPpuAtt
********************************************************************************
*
* An internal function to hold the common code for 
* Cy_Prot_ConfigPpu[Prog/Fixed][Master/Slave]Att API functions
*
* \note This function is applicable for CPUSS ver_2 only.
*
* \param reg
* The register to update attributes in.
*
* \param pcMask
* The protection context mask. This is a 16-bit value of the allowed contexts. 
* It is an OR'ed (|) field of the * provided defines in cy_prot.h. 
* For example: (CY_PROT_PCMASK1 | CY_PROT_PCMASK3 | CY_PROT_PCMASK4).
* \note The function accepts pcMask values from CY_PROT_PCMASK1 to CY_PROT_PCMASK5. 
* But each device has its own number of available protection contexts. 
* That number is defined by PERI_PC_NR in the config file.
*
* \param userPermission
* The user permissions for the region.
*
* \param privPermission
* The privileged permissions for the region.
*
* \param secure 
* Non Secure = false, Secure = true
*
* \return
* The status of the function call.
*
*   Status              | Description
* ----------------------| ---------------------------------------
* CY_PROT_SUCCESS       | The attributes were set up.
* CY_PROT_FAILURE       | The attributes were not set up because the structure is possibly locked.
* CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
*******************************************************************************/
static cy_en_prot_status_t Prot_ConfigPpuAtt(volatile uint32_t * reg, uint16_t pcMask, 
                                       cy_en_prot_perm_t userPermission, cy_en_prot_perm_t privPermission, bool secure)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;

    if (!CY_PERI_V1)
    {
        uint32_t tmpMask = (uint32_t)pcMask << CY_PROT_PCMASK_CHECK;
        uint32_t attReg;
        uint32_t regIdx;
        uint32_t fldIdx;
        
        status = CY_PROT_SUCCESS;
        
        /* Populate the ATT values */
        for(regIdx = 0U; regIdx < CY_PROT_ATT_REGS_MAX; regIdx++)
        {
            if (0UL == tmpMask)
            {
                break;
            }
            
            /* Get the attributes register value */
            attReg = reg[regIdx];

            for(fldIdx = 0UL; fldIdx < CY_PROT_ATT_PC_MAX; fldIdx++)
            {
                if((tmpMask & CY_PROT_PCMASK_CHECK) == CY_PROT_STRUCT_ENABLE)
                {
                    /* Reset the bitfield for the PCx attributes */
                    attReg &= ~((_VAL2FLD(CY_PROT_ATT_PERI_USER_PERM, CY_PROT_PERM_RW) |
                                 _VAL2FLD(CY_PROT_ATT_PERI_PRIV_PERM, CY_PROT_PERM_RW) |
                                 _BOOL2FLD(PERI_MS_PPU_PR_V2_MS_ATT0_PC0_NS, true)) <<
                                (PERI_MS_PPU_PR_V2_MS_ATT0_PC1_UR_Pos * fldIdx)); 
                    
                    /* Set the bitfield for the PCx attributes */
                    attReg |= (_VAL2FLD(CY_PROT_ATT_PERI_USER_PERM, userPermission) |
                               _VAL2FLD(CY_PROT_ATT_PERI_PRIV_PERM, privPermission) |
                              _BOOL2FLD(PERI_MS_PPU_PR_V2_MS_ATT0_PC0_NS, !secure)) <<
                               (PERI_MS_PPU_PR_V2_MS_ATT0_PC1_UR_Pos * fldIdx);
                }
                tmpMask = tmpMask >> CY_PROT_PCMASK_CHECK;
            }
            
            /* Update the attributes register */
            reg[regIdx] = attReg;

            /* Check the result */
            if ((0UL == regIdx) && 
                ((reg[regIdx] & PROT_PERI_PPU_PROG_PC1_PC3_MASK) != (attReg & PROT_PERI_PPU_PROG_PC1_PC3_MASK)))
            {
                status = CY_PROT_FAILURE;
            }
            else if (reg[regIdx] != attReg)
            {
                status = CY_PROT_FAILURE;
            }
            else
            {
                /* CY_PROT_SUCCESS */
            }
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuProgMasterAtt
****************************************************************************//**
*
* Configures the protection-structure attributes of the 
* Programmable Peripheral Protection Unit (PPU PROG) master. 
*
* This function configures the master structure governing the corresponding slave
* structure pair. It is a mechanism to protect the slave PPU PROG structure.
* The memory location of the slave structure is known, so the address, regionSize, and
* sub-regions of the configuration structure are not applicable.
*
* \note This function is applicable for CPUSS ver_2 only.
*
* \param base
* The register base address of the protection structure is being configured.
*
* \param pcMask
* The protection context mask. This is a 16-bit value of the allowed contexts, 
* it is an OR'ed (|) field of the * provided defines in cy_prot.h. 
* For example: (CY_PROT_PCMASK1 | CY_PROT_PCMASK3 | CY_PROT_PCMASK4).
* \note The function accepts pcMask values from CY_PROT_PCMASK1 to CY_PROT_PCMASK15. 
* But each device has its own number of available protection contexts. 
* That number is defined by PERI_PC_NR in the config file.
*
* \param userPermission
* The user permission setting. The CY_PROT_PERM_R or CY_PROT_PERM_RW values 
* are valid for the master.
*
* \param privPermission
* The privileged permission setting. CY_PROT_PERM_R or CY_PROT_PERM_RW values 
* are valid for the master.
*
* \param secure
* The secure flag.
* 
* \return
* The status of the function call.
*
*   Status              | Description
* ----------------------| ---------------------------------------
* CY_PROT_SUCCESS       | The attributes were set up.
* CY_PROT_FAILURE       | The attributes were not set up because the structure is possibly locked.
* CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \note Only the user's/privileged Write permissions are configurable. The 
* Read permissions are read-only and cannot be configured.
*
* \note PC0 accesses are read-only and are always enabled. 
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuProgMasterAtt
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuProgMasterAtt(PERI_MS_PPU_PR_Type* base, uint16_t pcMask, 
                                       cy_en_prot_perm_t userPermission, cy_en_prot_perm_t privPermission, bool secure)
{   
    /* The parameter checks */
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_PROG_MS_PERM_VALID(userPermission));
    CY_ASSERT_L3(CY_PROT_IS_PROG_MS_PERM_VALID(privPermission));
    
    return (Prot_ConfigPpuAtt(PERI_MS_PPU_PR_MS_ATT(base), pcMask, userPermission, privPermission, secure));
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuProgSlaveAddr
****************************************************************************//**
*
* Configures the protection-structure address settings  of the 
* Programmable Peripheral Protection Unit (PPU PROG) slave. 
* 
* This function configures the slave structure of the PPU PROG pair, which can 
* protect any peripheral memory region in a device from an invalid bus-master 
* access.
*
* \note This function is applicable for CPUSS ver_2 only.
*
* \param base
* The register base address of the protection structure is being configured.
* 
* \param address
* The address.
* 
* \param regionSize
* The region size.
* 
* \return
* The status of the function call.
*
*   Status              | Description
* ----------------------| ---------------------------------------
* CY_PROT_SUCCESS       | The address settings were set up.
* CY_PROT_FAILURE       | The address settings were not set up because the structure is possibly locked.
* CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version. 
*
* \note PC0 accesses are Read-only and are always enabled. 
*
* \funcusage
* \ref Cy_Prot_ConfigPpuProgSlaveAtt
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuProgSlaveAddr(PERI_MS_PPU_PR_Type* base, uint32_t address, 
                                                                   cy_en_prot_size_t regionSize)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    /* The parameter checks */
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_PPU_V2_SIZE_VALID(regionSize));
    
    if (!CY_PERI_V1)
    {
        PERI_MS_PPU_PR_SL_ADDR(base) = address & PERI_MS_PPU_PR_V2_SL_ADDR_ADDR30_Msk;
        PERI_MS_PPU_PR_SL_SIZE(base) = _CLR_SET_FLD32U((PERI_MS_PPU_PR_SL_SIZE(base)), PERI_MS_PPU_PR_V2_SL_SIZE_REGION_SIZE, regionSize);
        
        status = ((PERI_MS_PPU_PR_SL_ADDR(base) != (address & PERI_MS_PPU_PR_V2_SL_ADDR_ADDR30_Msk)) ||
                  (_FLD2VAL(PERI_MS_PPU_PR_V2_SL_SIZE_REGION_SIZE, PERI_MS_PPU_PR_SL_SIZE(base)) != (uint32_t)regionSize)) ?
                   CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuProgSlaveAtt
****************************************************************************//**
*
* Configures the protection structure with its protection attributes of the 
* Programmable Peripheral Protection Unit (PPU PROG) slave. 
* 
* This function configures the slave structure of the PPU PROG pair, which can 
* protect any peripheral memory region in a device from invalid bus-master 
* access.
*
* \note This function is applicable for CPUSS ver_2 only.
*
* \param base
* The register base address of the protection structure is being configured.
*
* \param pcMask
* The protection context mask. This is a 16-bit value of the allowed contexts, 
* it is an OR'ed (|) field of the * provided defines in cy_prot.h. 
* For example: (CY_PROT_PCMASK1 | CY_PROT_PCMASK3 | CY_PROT_PCMASK4).
* \note The function accepts pcMask values from CY_PROT_PCMASK1 to CY_PROT_PCMASK15. 
* But each device has its own number of available protection contexts. 
* That number is defined by PERI_PC_NR in the config file.
*
* \param userPermission
* The user permission setting.
*
* \param privPermission
* The privileged permission setting.
*
* \param secure
* The secure flag.
* 
* \return
* The status of the function call.
*
*   Status              | Description
* ----------------------| ---------------------------------------
* CY_PROT_SUCCESS       | The attributes were set up.
* CY_PROT_FAILURE       | The attributes were not set up because the structure is possibly locked.
* CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \note PC0 accesses are read-only and are always enabled. 
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuProgSlaveAtt
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuProgSlaveAtt(PERI_MS_PPU_PR_Type* base, uint16_t pcMask, 
                                       cy_en_prot_perm_t userPermission, cy_en_prot_perm_t privPermission, bool secure)
{
    /* The parameter checks */
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_PROG_SL_PERM_VALID(userPermission));
    CY_ASSERT_L3(CY_PROT_IS_PROG_SL_PERM_VALID(privPermission));

    return (Prot_ConfigPpuAtt(PERI_MS_PPU_PR_SL_ATT(base), pcMask, userPermission, privPermission, secure));
}


/*******************************************************************************
* Function Name: Cy_Prot_EnablePpuProgSlaveRegion
****************************************************************************//**
*
* Enables the Slave PPU PROG structure.
*
* This is the PPU PROG slave-structure enable function. The PPU PROG protection 
* settings will take effect after a successful completion of this function call.
*
* \note This function is applicable for CPUSS ver_2 only.
*
* \param base
* The base address for the protection unit structure is being configured. 
*
* \return
* The status of the function call.
*
*   Status              | Description
* ----------------------| ---------------------------------------
* CY_PROT_SUCCESS       | The structure was enabled.
* CY_PROT_FAILURE       | The structure is disabled and possibly locked.
* CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version. 
*
* \funcusage
* \ref Cy_Prot_ConfigPpuProgSlaveAtt
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnablePpuProgSlaveRegion(PERI_MS_PPU_PR_Type* base)
{   
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (!CY_PERI_V1)
    {
        PERI_MS_PPU_PR_SL_SIZE(base) = 
        _CLR_SET_FLD32U((PERI_MS_PPU_PR_SL_SIZE(base)), PERI_MS_PPU_PR_V2_SL_SIZE_VALID, CY_PROT_STRUCT_ENABLE);
        
        status = (_FLD2VAL(PERI_MS_PPU_PR_V2_SL_SIZE_VALID, PERI_MS_PPU_PR_SL_SIZE(base)) != CY_PROT_STRUCT_ENABLE) ? 
        CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisablePpuProgSlaveRegion
****************************************************************************//**
*
* Disables the Slave PPU PROG structure.
*
* This is the PPU PROG slave-structure disable function. The PPU PROG protection 
* settings will seize to take effect after successful completion of this 
* function call.
*
* \note This function is applicable for CPUSS ver_2 only.
*
* \param base
* The base address for the protection unit structure is being configured. 
*
* \return
* The status of the function call.
*
*   Status              | Description
* ----------------------| ---------------------------------------
* CY_PROT_SUCCESS       | The slave PPU PROG structure was disabled.
* CY_PROT_FAILURE       | The structure is enabled and possibly locked.
* CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisablePpuProgSlaveRegion
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisablePpuProgSlaveRegion(PERI_MS_PPU_PR_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (!CY_PERI_V1)
    {
        PERI_MS_PPU_PR_SL_SIZE(base) = 
        _CLR_SET_FLD32U((PERI_MS_PPU_PR_SL_SIZE(base)), PERI_MS_PPU_PR_V2_SL_SIZE_VALID, CY_PROT_STRUCT_DISABLE);

        status = (_FLD2VAL(PERI_MS_PPU_PR_V2_SL_SIZE_VALID, PERI_MS_PPU_PR_SL_SIZE(base)) != CY_PROT_STRUCT_DISABLE) ? 
        CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuFixedMasterAtt
****************************************************************************//**
*
* Configures the protection structure with its protection attributes of the
* Fixed Peripheral Protection Unit (PPU FIXED) master. 
*
* This function configures the master structure governing the corresponding slave
* structure pair. It is a mechanism to protect the slave PPU FIXED structure.
* The memory location of the slave structure is known, so the address, region size
* and sub-regions of the configuration structure are not applicable.
*
* \note This function is applicable for CPUSS ver_2 only.
*
* \param base
* The register base address of the protection structure is being configured.
*
* \param pcMask
* The protection context mask. This is a 16-bit value of the allowed contexts, 
* it is an OR'ed (|) field of the * provided defines in cy_prot.h. 
* For example: (CY_PROT_PCMASK1 | CY_PROT_PCMASK3 | CY_PROT_PCMASK4).
* \note The function accepts pcMask values from CY_PROT_PCMASK1 to CY_PROT_PCMASK15. 
* But each device has its own number of available protection contexts. 
* That number is defined by PERI_PC_NR in the config file.
*
* \param userPermission
* The user permission setting. The CY_PROT_PERM_R or CY_PROT_PERM_RW values 
* are valid for the master.
*
* \param privPermission
* The privileged permission setting. The CY_PROT_PERM_R or CY_PROT_PERM_RW values 
* are valid for the master.
*
* \param secure
* The secure flag.
* 
* \return
* The status of the function call.
*
*   Status              | Description
* ----------------------| ---------------------------------------
* CY_PROT_SUCCESS       | The attributes were set up.
* CY_PROT_FAILURE       | The attributes were not setup and the structure is possibly locked.
* CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \note Only the user/privileged write permissions are configurable. The 
* read permissions are read-only and cannot be configured.
*
* \note PC0 accesses are read-only and are always enabled. 
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuFixedMasterAtt
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedMasterAtt(PERI_MS_PPU_FX_Type* base, uint16_t pcMask,
                                      cy_en_prot_perm_t userPermission, cy_en_prot_perm_t privPermission, bool secure)
{
    /* The parameter checks */
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_FIXED_MS_MS_PERM_VALID(userPermission));
    CY_ASSERT_L3(CY_PROT_IS_FIXED_MS_MS_PERM_VALID(privPermission));

    return (Prot_ConfigPpuAtt(PERI_MS_PPU_FX_MS_ATT(base), pcMask, userPermission, privPermission, secure));
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuFixedSlaveAtt
****************************************************************************//**
*
* Configures the protection structure with its protection attributes of
* the Fixed Peripheral Protection Unit (PPU FIXED) slave. 
* 
* This function configures the slave structure of the PPU FIXED pair, which can 
* protect any peripheral memory region in a device from invalid bus-master 
* access.
*
* \note This function is applicable for CPUSS ver_2 only.
*
* \param base
* The register base address of the protection structure is being configured.
*
* \param pcMask
* The protection context mask. This is a 16-bit value of the allowed contexts, 
* it is an OR'ed (|) field of the * provided defines in cy_prot.h. 
* For example: (CY_PROT_PCMASK1 | CY_PROT_PCMASK3 | CY_PROT_PCMASK4).
* \note The function accepts pcMask values from CY_PROT_PCMASK1 to CY_PROT_PCMASK15. 
* But each device has its own number of available protection contexts. 
* That number is defined by PERI_PC_NR in the config file.
*
* \param userPermission
* The user permission setting.
*
* \param privPermission
* The privileged permission setting.
*
* \param secure
* The secure flag.
* 
* \return
* The status of the function call.
*
*   Status              | Description
* ----------------------| ---------------------------------------
* CY_PROT_SUCCESS       | The attributes were set up.
* CY_PROT_FAILURE       | The attributes were not setup and the structure is possibly locked.
* CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \note PC0 accesses are read-only and are always enabled. 
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuFixedSlaveAtt
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedSlaveAtt(PERI_MS_PPU_FX_Type* base, uint16_t pcMask, 
                           cy_en_prot_perm_t userPermission, cy_en_prot_perm_t privPermission, bool secure)
{
    /* The parameter checks */
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_FIXED_MS_PERM_VALID(userPermission));
    CY_ASSERT_L3(CY_PROT_IS_FIXED_MS_PERM_VALID(privPermission));

    return (Prot_ConfigPpuAtt(PERI_MS_PPU_FX_SL_ATT(base), pcMask, userPermission, privPermission, secure));
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuProgMasterStruct
****************************************************************************//**
*
* Configures a Programmable Peripheral Protection Unit (PPU PROG) master 
* protection struct with its protection attributes. 
*
* This function configures the master struct governing the corresponding slave
* struct pair. It is a mechanism to protect the slave PPU PROG struct. Since
* the memory location of the slave struct is known, the address, regionSize and
* subregions of the configuration struct are not applicable.
*
* Note that only the user/privileged write permissions are configurable. The 
* read and execute permissions are read-only and cannot be configured.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The register base address of the protection struct being configured.
* 
* \param config
* Initialization structure with all the protection attributes.
* 
* \return
* Status of the function call.
*
*  Status                | Description
*  ------------          | -----------
*  CY_PROT_SUCCESS       | PPU PROG master struct was successfully configured.
*  CY_PROT_FAILURE       | The resource is locked.
*  CY_PROT_BAD_PARAM     | An incorrect/invalid parameter was passed.
*  CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuProgMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuProgMasterStruct(PERI_PPU_PR_Type* base, const cy_stc_ppu_prog_cfg_t* config)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    uint32_t attReg;
    
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_PROG_MS_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_PROG_MS_PERM_VALID(config->privPermission));
    
    if (CY_PERI_V1)
    {
        if(((uint32_t)config->pcMask & CY_PROT_PPU_PROG_PC_LIMIT_MASK) != 0UL) 
        {
            /* PC mask out of range - not supported in device */
            status = CY_PROT_BAD_PARAM;
        }
        else
        {
            /* ADDR1 is read only. Only configure ATT1 */
            attReg = ((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK)
                        | (uint32_t)(((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
                        | _VAL2FLD(PERI_PPU_PR_ATT1_NS, !(config->secure))
                        | _VAL2FLD(PERI_PPU_PR_ATT1_PC_MASK_15_TO_1, config->pcMask)
                        /* No region size - read only for master structs */
                        | _VAL2FLD(PERI_PPU_PR_ATT1_PC_MATCH, config->pcMatch);
            if ((attReg & CY_PROT_PPU_PROG_ATT1_MASK) != attReg)
            {
                /* Invalid parameter was passed */
                status = CY_PROT_BAD_PARAM;
            }
            else
            {
                PERI_PPU_PR_ATT1(base) = attReg;
                status = ((PERI_PPU_PR_ATT1(base) & CY_PROT_PPU_PROG_ATT1_MASK) != attReg) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
            }
        }
    }

    return status;
}

/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuProgSlaveStruct
****************************************************************************//**
*
* Configures a Programmable Peripheral Protection Unit (PPU PROG) slave
* protection struct with its protection attributes. 
* 
* This function configures the slave struct of a PPU PROG pair, which can 
* protect any peripheral memory region in a device from invalid bus master 
* accesses.
*
* Note that the user/privileged execute accesses are read-only and are always 
* enabled. 
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The register base address of the protection structure being configured.
* 
* \param config
* Initialization structure with all the protection attributes.
* 
* \return
* Status of the function call.
*
*   Status               | Description
*   ------------         | -----------
*  CY_PROT_SUCCESS       | PPU PROG slave struct was successfully configured.
*  CY_PROT_FAILURE       | The resource is locked.
*  CY_PROT_BAD_PARAM     | An incorrect/invalid parameter was passed.
*  CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuProgSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuProgSlaveStruct(PERI_PPU_PR_Type* base, const cy_stc_ppu_prog_cfg_t* config)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    uint32_t addrReg;
    uint32_t attReg;
    
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_PROG_SL_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_PROG_SL_PERM_VALID(config->privPermission));
    CY_ASSERT_L3(CY_PROT_IS_REGION_SIZE_VALID(config->regionSize));

    if (CY_PERI_V1)
    {
        if(((uint32_t)config->pcMask & CY_PROT_PPU_PROG_PC_LIMIT_MASK) != 0UL) 
        {
            /* PC mask out of range - not supported in device */
            status = CY_PROT_BAD_PARAM;
        }
        else
        {
            addrReg= _VAL2FLD(PERI_PPU_PR_ADDR0_SUBREGION_DISABLE, config->subregions)
                        | _VAL2FLD(PERI_PPU_PR_ADDR0_ADDR24, (uint32_t)((uint32_t)config->address >> CY_PROT_ADDR_SHIFT));
            attReg= ((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK)
                        | (uint32_t)(((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
                        | _VAL2FLD(PERI_PPU_PR_ATT0_NS, !(config->secure))
                        | _VAL2FLD(PERI_PPU_PR_ATT0_PC_MASK_15_TO_1, config->pcMask)
                        | _VAL2FLD(PERI_PPU_PR_ATT0_REGION_SIZE, config->regionSize)
                        | _VAL2FLD(PERI_PPU_PR_ATT0_PC_MATCH, config->pcMatch);
            if ((attReg & CY_PROT_PPU_PROG_ATT0_MASK) != attReg)
            {
                /* Invalid parameter was passed */
                status = CY_PROT_BAD_PARAM;
            }
            else
            {
                PERI_PPU_PR_ATT0(base) = attReg;
                PERI_PPU_PR_ADDR0(base) = addrReg;
                status = ((PERI_PPU_PR_ADDR0(base) != addrReg) || ((PERI_PPU_PR_ATT0(base) & CY_PROT_PPU_PROG_ATT0_MASK) != attReg))
                            ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
            }
        }
    }
    
    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnablePpuProgMasterStruct
****************************************************************************//**
*
* Enables the Master PPU PROG structure.
*
* This is a PPU PROG master struct enable function. The PPU PROG protection 
* settings will take effect after successful completion of this function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Master PU struct was enabled.
*   CY_PROT_FAILURE       | The Master PU struct is disabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnablePpuProgMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnablePpuProgMasterStruct(PERI_PPU_PR_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_PPU_PR_ATT1(base) |= _VAL2FLD(PERI_PPU_PR_ATT1_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_PPU_PR_ATT1_ENABLED, PERI_PPU_PR_ATT1(base)) != CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisablePpuProgMasterStruct
****************************************************************************//**
*
* Disables the Master PPU PROG structure.
*
* This is a PPU PROG master struct disable function. The PPU PROG protection 
* settings will seize to take effect after successful completion of this 
* function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Master PU struct was disabled.
*   CY_PROT_FAILURE       | The Master PU struct is enabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisablePpuProgMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisablePpuProgMasterStruct(PERI_PPU_PR_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_PPU_PR_ATT1(base) &= ~_VAL2FLD(PERI_PPU_PR_ATT1_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_PPU_PR_ATT1_ENABLED, PERI_PPU_PR_ATT1(base)) == CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnablePpuProgSlaveStruct
****************************************************************************//**
*
* Enables the Slave PPU PROG structure.
*
* This is a PPU PROG slave struct enable function. The PPU PROG protection 
* settings will take effect after successful completion of this function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Slave PU struct was enabled.
*   CY_PROT_FAILURE       | The Slave PU struct is disabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnablePpuProgSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnablePpuProgSlaveStruct(PERI_PPU_PR_Type* base)
{   
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_PPU_PR_ATT0(base) |= _VAL2FLD(PERI_PPU_PR_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_PPU_PR_ATT0_ENABLED, PERI_PPU_PR_ATT0(base)) != CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisablePpuProgSlaveStruct
****************************************************************************//**
*
* Disables the Slave PPU PROG structure.
*
* This is a PPU PROG slave struct disable function. The PPU PROG protection 
* settings will seize to take effect after successful completion of this 
* function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Slave PU struct was disabled.
*   CY_PROT_FAILURE       | The Slave PU struct is enabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisablePpuProgSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisablePpuProgSlaveStruct(PERI_PPU_PR_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_PPU_PR_ATT0(base) &= ~_VAL2FLD(PERI_PPU_PR_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_PPU_PR_ATT0_ENABLED, PERI_PPU_PR_ATT0(base)) == CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_GetPpuProgStruct
****************************************************************************//**
*
* Functions returns a pointer of the requested unused Programmable PPU 
* structure. Function searches the Programmable PPU structure until it finds 
* one that both the slave and master sections are disabled. After an available
* structure is located, function enables the slave structure and enables all 
* attributes, to make sure that a subsequent call will not see this
* as an available (unused) Programmable PPU. 
*
* It is up to the user to implement, if needed, a system in which a semaphore 
* will lock-out all but one CPU from calling this function at once.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the Programmable PPU structure returned if an unused 
* structure was found. If an empty structure was not found, the returned 
* pointer is NULL.
*
* \param reqMode
* This parameter (request mode) selects how the user wants to select a 
* Programmable PPU structure.
*
*   reqMode                 | Description
* --------------------------| -----------------------------
* CY_PROT_REQMODE_HIGHPRIOR | Return the Programmable PPU structure with the highest priority.
* CY_PROT_REQMODE_LOWPRIOR  | Return the Programmable PPU structure with the lowest priority.
* CY_PROT_REQMODE_INDEX     | Return the Programmable PPU structure with the specific index.
*
* \param ppuProgIndex
* This is the index of the requested Programmable PPU structure. It is only 
* used if the request mode is reqMode = CY_PROT_REQMODE_INDEX.
*
* \return
* Status of the function call.
*
*   Status              | Description
* ----------------------| ---------------------------------------
* CY_PROT_SUCCESS       | The Slave PU struct was disabled.
* CY_PROT_FAILURE       | The Master or Slave Programmable PPU struct is disabled and possibly locked.
* CY_PROT_UNAVAILABLE   | The requested structure in use or there were no unused structures.
* CY_PROT_INVALID_STATE | Function was called on unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_GetPpuProgStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_GetPpuProgStruct(PERI_PPU_PR_Type** base, cy_en_prot_req_mode_t reqMode, uint32_t ppuProgIndex)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    if (CY_PERI_V1)
    {
        CY_ASSERT_L3(CY_PROT_IS_PPU_PROG_REQ_MODE_VALID(reqMode));
        CY_ASSERT_L2(CY_PROT_IS_PPU_PROG_IDX_VALID(ppuProgIndex));

        status = CY_PROT_UNAVAILABLE;
        int32_t stcIdx = (int32_t) ppuProgIndex;

        *base = NULL;

        switch (reqMode)
        {
            /* Programmed structures priority goes from 0 (highest) to
            *  PROT_PPU_PROG_STRUCT_WTH_LOWEST_PR (lowest) 
            */
            case CY_PROT_REQMODE_LOWPRIOR:

                stcIdx = PROT_PPU_PROG_STRUCT_WTH_LOWEST_PR;
                do
                {
                    if (Prot_IsPpuProgStructDisabled((uint32_t)stcIdx))
                    {
                        status = CY_PROT_SUCCESS;
                    }
                    else
                    {
                        --stcIdx;
                    }
                } while ((stcIdx >= 0) && (CY_PROT_SUCCESS != status));
                break;

            /* Programmed structures priority goes from 0 (highest) to 
            *  PROT_PPU_PROG_STRUCT_WTH_LOWEST_PR (lowest)
            */
            case CY_PROT_REQMODE_HIGHPRIOR:
                stcIdx = 0;
                do
                {
                    if (Prot_IsPpuProgStructDisabled((uint32_t)stcIdx))
                    {
                        status = CY_PROT_SUCCESS;
                    }
                    else
                    {
                        ++stcIdx;
                    }
                } while ((stcIdx <= PROT_PPU_PROG_STRUCT_WTH_LOWEST_PR) && (CY_PROT_SUCCESS != status));
                break;
            
            case CY_PROT_REQMODE_INDEX:

                if (Prot_IsPpuProgStructDisabled((uint32_t)stcIdx))
                {
                    status = CY_PROT_SUCCESS;
                }
                break;
                
            default:
                break;
        }

        /* Enable Programmable PPU struct */
        if (CY_PROT_SUCCESS == status)
        {
            PROT_PERI_PPU_PR_STRUCT_IDX_ATT0(stcIdx) |= _VAL2FLD(PERI_PPU_PR_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
            
            status = 
            (_FLD2VAL(PERI_PPU_PR_ATT0_ENABLED, PROT_PERI_PPU_PR_STRUCT_IDX_ATT0(stcIdx)) != CY_PROT_STRUCT_ENABLE) ?
             CY_PROT_FAILURE : CY_PROT_SUCCESS;
            
            /* Enable all attributes only if Slave struct was enabled */
            if (CY_PROT_SUCCESS == status)
            {
                *base = (PERI_PPU_PR_Type*) PROT_PERI_PPU_PR_STRUCT_IDX(stcIdx);
                PROT_PERI_PPU_PR_STRUCT_IDX_ATT0(stcIdx) |= PROT_PERI_PPU_PR_ATT0_ENABLE_ALL_MASK;
            }
        }
    }

    return status;
}



/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuFixedGrMasterStruct
****************************************************************************//**
*
* Configures a Fixed Peripheral Group Protection Unit (PPU GR) master 
* protection struct with its protection attributes. 
*
* This function configures the master struct governing the corresponding slave
* struct pair. It is a mechanism to protect the slave PPU GR struct. Since
* the memory location of the slave struct is known, the address, regionSize and
* subregions of the configuration struct are not applicable.
*
* Note that only the user/privileged write permissions are configurable. The 
* read and execute permissions are read-only and cannot be configured.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The register base address of the protection struct being configured.
* 
* \param config
* Initialization structure with all the protection attributes.
* 
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | PPU GR master struct was successfully configured.
*   CY_PROT_FAILURE       | The resource is locked.
*   CY_PROT_BAD_PARAM     | An incorrect/invalid parameter was passed.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuFixedGrMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedGrMasterStruct(PERI_PPU_GR_Type* base, const cy_stc_ppu_gr_cfg_t* config)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    uint32_t attReg;
    
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_FIXED_MS_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_FIXED_MS_PERM_VALID(config->privPermission));
    
    if (CY_PERI_V1)
    {
        if(((uint32_t)config->pcMask & CY_PROT_PPU_FIXED_PC_LIMIT_MASK) != 0UL) 
        {
            /* PC mask out of range - not supported in device */
            status = CY_PROT_BAD_PARAM;
        }
        else
        {
            /* ADDR1 is read only. Only configure ATT1 */
            attReg = (((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK))
                        | (uint32_t)(((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
                        | _VAL2FLD(PERI_PPU_GR_ATT1_NS, !(config->secure))
                        | _VAL2FLD(PERI_PPU_GR_ATT1_PC_MASK_15_TO_1, config->pcMask)
                        /* No region size - read only for master structs */
                        | _VAL2FLD(PERI_PPU_GR_ATT1_PC_MATCH, config->pcMatch);
            if ((attReg & CY_PROT_PPU_GR_ATT1_MASK) != attReg)
            {
                /* Invalid parameter was passed */
                status = CY_PROT_BAD_PARAM;
            }
            else
            {
                PERI_PPU_GR_ATT1(base) = attReg;
                status = ((PERI_PPU_GR_ATT1(base) & CY_PROT_PPU_GR_ATT1_MASK) != attReg) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
            }
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuFixedGrSlaveStruct
****************************************************************************//**
*
* Configures a Fixed Peripheral Group Protection Unit (PPU GR) slave
* protection struct with its protection attributes. 
* 
* This function configures the slave struct of a PPU GR pair, which can 
* protect an entire peripheral MMIO group from invalid bus master accesses.
* Refer to the device Technical Reference manual for details on peripheral
* MMIO grouping and which peripherals belong to which groups.
*
* Each fixed PPU GR is devoted to a defined MMIO group. Hence the address, 
* regionSize and subregions of the configuration struct are not applicable.
*
* Note that the user/privileged execute accesses are read-only and are always 
* enabled. 
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The register base address of the protection structure being configured.
* 
* \param config
* Initialization structure with all the protection attributes.
* 
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | PPU GR slave struct was successfully configured.
*   CY_PROT_FAILURE       | The resource is locked.
*   CY_PROT_BAD_PARAM     | An incorrect/invalid parameter was passed.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuFixedGrSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedGrSlaveStruct(PERI_PPU_GR_Type* base, const cy_stc_ppu_gr_cfg_t* config)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    uint32_t attReg;
    
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_FIXED_SL_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_FIXED_SL_PERM_VALID(config->privPermission));
    
    if (CY_PERI_V1)
    {
        if(((uint32_t)config->pcMask & CY_PROT_PPU_FIXED_PC_LIMIT_MASK) != 0UL) 
        {
            /* PC mask out of range - not supported in device */
            status = CY_PROT_BAD_PARAM;
        }
        else
        {
            /* ADDR0 is read only. Only configure ATT0 */
            attReg = (uint32_t)(((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK))
                        | (uint32_t)(((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
                        | _VAL2FLD(PERI_PPU_GR_ATT0_NS, !(config->secure))
                        | _VAL2FLD(PERI_PPU_GR_ATT0_PC_MASK_15_TO_1, config->pcMask)
                        /* No region size - read only */
                        | _VAL2FLD(PERI_PPU_GR_ATT0_PC_MATCH, config->pcMatch);
            if ((attReg & CY_PROT_PPU_GR_ATT0_MASK) != attReg)
            {
                /* Invalid parameter was passed */
                status = CY_PROT_BAD_PARAM;
            }
            else
            {
                PERI_PPU_GR_ATT0(base) = attReg;
                status = ((PERI_PPU_GR_ATT0(base) & CY_PROT_PPU_GR_ATT0_MASK) != attReg) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
            }
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnablePpuFixedGrMasterStruct
****************************************************************************//**
*
* Enables the Master PPU GR structure.
*
* This is a PPU GR master struct enable function. The PPU GR protection 
* settings will take effect after successful completion of this function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Master PU struct was enabled.
*   CY_PROT_FAILURE       | The Master PU struct is disabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnablePpuFixedGrMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnablePpuFixedGrMasterStruct(PERI_PPU_GR_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_PPU_GR_ATT1(base) |= _VAL2FLD(PERI_PPU_GR_ATT1_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_PPU_GR_ATT1_ENABLED, PERI_PPU_GR_ATT1(base)) != CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisablePpuFixedGrMasterStruct
****************************************************************************//**
*
* Disables the Master PPU GR structure.
*
* This is a PPU GR master struct disable function. The PPU GR protection 
* settings will seize to take effect after successful completion of this 
* function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Master PU struct was disabled.
*   CY_PROT_FAILURE       | The Master PU struct is enabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisablePpuFixedGrMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisablePpuFixedGrMasterStruct(PERI_PPU_GR_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_PPU_GR_ATT1(base) &= ~_VAL2FLD(PERI_PPU_GR_ATT1_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_PPU_GR_ATT1_ENABLED, PERI_PPU_GR_ATT1(base)) == CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnablePpuFixedGrSlaveStruct
****************************************************************************//**
*
* Enables the Slave PPU GR structure.
*
* This is a PPU GR slave struct enable function. The PPU GR protection 
* settings will take effect after successful completion of this function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Slave PU struct was enabled.
*   CY_PROT_FAILURE       | The Slave PU struct is disabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnablePpuFixedGrSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnablePpuFixedGrSlaveStruct(PERI_PPU_GR_Type* base)
{   
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_PPU_GR_ATT0(base) |= _VAL2FLD(PERI_PPU_GR_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_PPU_GR_ATT0_ENABLED, PERI_PPU_GR_ATT0(base)) != CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisablePpuFixedGrSlaveStruct
****************************************************************************//**
*
* Disables the Slave PPU GR structure.
*
* This is a PPU GR slave struct disable function. The PPU GR protection 
* settings will seize to take effect after successful completion of this 
* function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Slave PU struct was disabled.
*   CY_PROT_FAILURE       | The Slave PU struct is enabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisablePpuFixedGrSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisablePpuFixedGrSlaveStruct(PERI_PPU_GR_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_PPU_GR_ATT0(base) &= ~_VAL2FLD(PERI_PPU_GR_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_PPU_GR_ATT0_ENABLED, PERI_PPU_GR_ATT0(base)) == CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuFixedSlMasterStruct
****************************************************************************//**
*
* Configures a Fixed Peripheral Slave Protection Unit (PPU SL) master 
* protection struct with its protection attributes. 
*
* This function configures the master struct governing the corresponding slave
* struct pair. It is a mechanism to protect the slave PPU SL struct. Since
* the memory location of the slave struct is known, the address, regionSize and
* subregions of the configuration struct are not applicable.
*
* Note that only the user/privileged write permissions are configurable. The 
* read and execute permissions are read-only and cannot be configured.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The register base address of the protection struct being configured.
* 
* \param config
* Initialization structure with all the protection attributes.
* 
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | PPU SL master struct was successfully configured.
*   CY_PROT_FAILURE       | The resource is locked.
*   CY_PROT_BAD_PARAM     | An incorrect/invalid parameter was passed.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuFixedSlMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedSlMasterStruct(PERI_GR_PPU_SL_Type* base, const cy_stc_ppu_sl_cfg_t* config)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    uint32_t attReg;
    
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_FIXED_MS_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_FIXED_MS_PERM_VALID(config->privPermission));
    
    if (CY_PERI_V1)
    {
        if(((uint32_t)config->pcMask & CY_PROT_PPU_FIXED_PC_LIMIT_MASK) != 0UL) 
        {
            /* PC mask out of range - not supported in device */
            status = CY_PROT_BAD_PARAM;
        }
        else
        {
            /* ADDR1 is read only. Only configure ATT1 */
            attReg = ((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK)
                        | (uint32_t)(((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
                        | _VAL2FLD(PERI_GR_PPU_SL_ATT1_NS, !(config->secure))
                        | _VAL2FLD(PERI_GR_PPU_SL_ATT1_PC_MASK_15_TO_1, config->pcMask)
                        /* No region size - read only for master structs */
                        | _VAL2FLD(PERI_GR_PPU_SL_ATT1_PC_MATCH, config->pcMatch);
            if ((attReg & CY_PROT_PPU_SL_ATT1_MASK) != attReg)
            {
                /* Invalid parameter was passed */
                status = CY_PROT_BAD_PARAM;
            }
            else
            {
                PERI_GR_PPU_SL_ATT1(base) = attReg;
                status = ((PERI_GR_PPU_SL_ATT1(base) & CY_PROT_PPU_SL_ATT1_MASK) != attReg) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
            }
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuFixedSlSlaveStruct
****************************************************************************//**
*
* Configures a Fixed Peripheral Slave Protection Unit (PPU SL) slave
* protection struct with its protection attributes. 
* 
* This function configures the slave struct of a PPU SL pair, which can 
* protect an entire peripheral slave instance from invalid bus master accesses.
* For example, TCPWM0, TCPWM1, SCB0 and SCB1 etc.
*
* Each fixed PPU SL is devoted to a defined peripheral slave. Hence the address, 
* regionSize and subregions of the configuration struct are not applicable.
*
* Note that the user/privileged execute accesses are read-only and are always 
* enabled. 
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The register base address of the protection structure being configured.
* 
* \param config
* Initialization structure with all the protection attributes.
* 
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | PPU SL slave struct was successfully configured.
*   CY_PROT_FAILURE       | The resource is locked.
*   CY_PROT_BAD_PARAM     | An incorrect/invalid parameter was passed.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuFixedSlSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedSlSlaveStruct(PERI_GR_PPU_SL_Type* base, const cy_stc_ppu_sl_cfg_t* config)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    uint32_t attReg;
    
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_FIXED_SL_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_FIXED_SL_PERM_VALID(config->privPermission));
    
    if (CY_PERI_V1)
    {
        if(((uint32_t)config->pcMask & CY_PROT_PPU_FIXED_PC_LIMIT_MASK) != 0UL) 
        {
            /* PC mask out of range - not supported in device */
            status = CY_PROT_BAD_PARAM;
        }
        else
        {
            /* ADDR0 is read only. Only configure ATT0 */
            attReg = ((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK)
                        | (uint32_t)(((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
                        | _VAL2FLD(PERI_GR_PPU_SL_ATT0_NS, !(config->secure))
                        | _VAL2FLD(PERI_GR_PPU_SL_ATT0_PC_MASK_15_TO_1, config->pcMask)
                        /* No region size - read only */
                        | _VAL2FLD(PERI_GR_PPU_SL_ATT0_PC_MATCH, config->pcMatch);
            if ((attReg & CY_PROT_PPU_SL_ATT0_MASK) != attReg)
            {
                /* Invalid parameter was passed */
                status = CY_PROT_BAD_PARAM;
            }
            else
            {
                PERI_GR_PPU_SL_ATT0(base) = attReg;
                status = ((PERI_GR_PPU_SL_ATT0(base) & CY_PROT_PPU_SL_ATT0_MASK) != attReg) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
            }
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnablePpuFixedSlMasterStruct
****************************************************************************//**
*
* Enables the Master PPU SL structure.
*
* This is a PPU SL master struct enable function. The PPU SL protection 
* settings will take effect after successful completion of this function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Master PU struct was enabled.
*   CY_PROT_FAILURE       | The Master PU struct is disabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnablePpuFixedSlMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnablePpuFixedSlMasterStruct(PERI_GR_PPU_SL_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_GR_PPU_SL_ATT1(base) |= _VAL2FLD(PERI_GR_PPU_SL_ATT1_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_GR_PPU_SL_ATT1_ENABLED, PERI_GR_PPU_SL_ATT1(base)) != CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisablePpuFixedSlMasterStruct
****************************************************************************//**
*
* Disables the Master PPU SL structure.
*
* This is a PPU SL master struct disable function. The PPU SL protection 
* settings will seize to take effect after successful completion of this 
* function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Master PU struct was disabled.
*   CY_PROT_FAILURE       | The Master PU struct is enabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisablePpuFixedSlMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisablePpuFixedSlMasterStruct(PERI_GR_PPU_SL_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_GR_PPU_SL_ATT1(base) &= ~_VAL2FLD(PERI_GR_PPU_SL_ATT1_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_GR_PPU_SL_ATT1_ENABLED, PERI_GR_PPU_SL_ATT1(base)) == CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnablePpuFixedSlSlaveStruct
****************************************************************************//**
*
* Enables the Slave PPU SL structure.
*
* This is a PPU SL slave struct enable function. The PPU SL protection 
* settings will take effect after successful completion of this function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Slave PU struct was enabled.
*   CY_PROT_FAILURE       | The Slave PU struct is disabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnablePpuFixedSlSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnablePpuFixedSlSlaveStruct(PERI_GR_PPU_SL_Type* base)
{   
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_GR_PPU_SL_ATT0(base) |= _VAL2FLD(PERI_GR_PPU_SL_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_GR_PPU_SL_ATT0_ENABLED, PERI_GR_PPU_SL_ATT0(base)) != CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisablePpuFixedSlSlaveStruct
****************************************************************************//**
*
* Disables the Slave PPU SL structure.
*
* This is a PPU SL slave struct disable function. The PPU SL protection 
* settings will seize to take effect after successful completion of this 
* function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Slave PU struct was enabled.
*   CY_PROT_FAILURE       | The Slave PU struct is disabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisablePpuFixedSlSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisablePpuFixedSlSlaveStruct(PERI_GR_PPU_SL_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    CY_ASSERT_L1(NULL != base);
    
    if (CY_PERI_V1)
    {
        PERI_GR_PPU_SL_ATT0(base) &= ~_VAL2FLD(PERI_GR_PPU_SL_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_GR_PPU_SL_ATT0_ENABLED, PERI_GR_PPU_SL_ATT0(base)) == CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuFixedRgMasterStruct
****************************************************************************//**
*
* Configures a Fixed Peripheral Region Protection Unit (PPU RG) master 
* protection struct with its protection attributes. 
*
* This function configures the master struct governing the corresponding slave
* struct pair. It is a mechanism to protect the slave PPU RG struct. Since
* the memory location of the slave struct is known, the address, regionSize and
* subregions of the configuration struct are not applicable.
*
* Note that only the user/privileged write permissions are configurable. The 
* read and execute permissions are read-only and cannot be configured.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The register base address of the protection struct being configured.
* 
* \param config
* Initialization structure with all the protection attributes.
* 
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | PPU RG master struct was successfully configured.
*   CY_PROT_FAILURE       | The resource is locked.
*   CY_PROT_BAD_PARAM     | An incorrect/invalid parameter was passed.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuFixedRgMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedRgMasterStruct(PERI_GR_PPU_RG_Type* base, const cy_stc_ppu_rg_cfg_t* config)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    uint32_t attReg;
    
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_FIXED_MS_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_FIXED_MS_PERM_VALID(config->privPermission));
    
    if (CY_PERI_V1)
    {
        if(((uint32_t)config->pcMask & CY_PROT_PPU_FIXED_PC_LIMIT_MASK) != 0UL) 
        {
            /* PC mask out of range - not supported in device */
            status = CY_PROT_BAD_PARAM;
        }
        else
        {
            /* ADDR1 is read only. Only configure ATT1 */
            attReg = ((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK)
                        | (uint32_t)(((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
                        | _VAL2FLD(PERI_GR_PPU_RG_ATT1_NS, !(config->secure))
                        | _VAL2FLD(PERI_GR_PPU_RG_ATT1_PC_MASK_15_TO_1, config->pcMask)
                        /* No region size - read only for master structs */
                        | _VAL2FLD(PERI_GR_PPU_RG_ATT1_PC_MATCH, config->pcMatch);
            if ((attReg & CY_PROT_PPU_RG_ATT1_MASK) != attReg)
            {
                /* Invalid parameter was passed */
                status = CY_PROT_BAD_PARAM;
            }
            else
            {
                PERI_GR_PPU_RG_ATT1(base) = attReg;
                status = ((PERI_GR_PPU_RG_ATT1(base) & CY_PROT_PPU_RG_ATT1_MASK) != attReg) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
            }
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_ConfigPpuFixedRgSlaveStruct
****************************************************************************//**
*
* Configures a Fixed Peripheral Region Protection Unit (PPU RG) slave
* protection struct with its protection attributes. 
* 
* This function configures the slave struct of a PPU RG pair, which can 
* protect specified regions of peripheral instances. For example, individual
* DW channel structs, SMPU structs, and IPC structs etc.
*
* Each fixed PPU RG is devoted to a defined peripheral region. Hence the address, 
* regionSize and subregions of the configuration struct are not applicable.
*
* Note that the user/privileged execute accesses are read-only and are always 
* enabled. 
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The register base address of the protection structure being configured.
* 
* \param config
* Initialization structure with all the protection attributes.
* 
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | PPU RG slave struct was successfully configured.
*   CY_PROT_FAILURE       | The resource is locked.
*   CY_PROT_BAD_PARAM     | An incorrect/invalid parameter was passed.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_ConfigPpuFixedRgSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedRgSlaveStruct(PERI_GR_PPU_RG_Type* base, const cy_stc_ppu_rg_cfg_t* config)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    uint32_t attReg;
    
    CY_ASSERT_L1(NULL != base);
    CY_ASSERT_L3(CY_PROT_IS_FIXED_SL_PERM_VALID(config->userPermission));
    CY_ASSERT_L3(CY_PROT_IS_FIXED_SL_PERM_VALID(config->privPermission));
    
    if (CY_PERI_V1)
    {
        if(((uint32_t)config->pcMask & CY_PROT_PPU_FIXED_PC_LIMIT_MASK) != 0UL) 
        {
            /* PC mask out of range - not supported in device */
            status = CY_PROT_BAD_PARAM;
        }
        else
        {
            /* ADDR0 is read only. Only configure ATT0 */
            attReg = ((uint32_t)config->userPermission & CY_PROT_ATT_PERMISSION_MASK)
                        | (uint32_t)(((uint32_t)config->privPermission & CY_PROT_ATT_PERMISSION_MASK) << CY_PROT_ATT_PRIV_PERMISSION_SHIFT)
                        | _VAL2FLD(PERI_GR_PPU_RG_ATT0_NS, !(config->secure))
                        | _VAL2FLD(PERI_GR_PPU_RG_ATT0_PC_MASK_15_TO_1, config->pcMask)
                        /* No region size - read only */
                        | _VAL2FLD(PERI_GR_PPU_RG_ATT0_PC_MATCH, config->pcMatch);
            if ((attReg & CY_PROT_PPU_RG_ATT0_MASK) != attReg)
            {
                /* Invalid parameter was passed */
                status = CY_PROT_BAD_PARAM;
            }
            else
            {
                PERI_GR_PPU_RG_ATT0(base) = attReg;
                status = ((PERI_GR_PPU_RG_ATT0(base) & CY_PROT_PPU_RG_ATT0_MASK) != attReg) ? CY_PROT_FAILURE : CY_PROT_SUCCESS;
            }
        }
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnablePpuFixedRgMasterStruct
****************************************************************************//**
*
* Enables the Master PPU RG structure.
*
* This is a PPU RG master struct enable function. The PPU RG protection 
* settings will take effect after successful completion of this function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Master PU struct was enabled.
*   CY_PROT_FAILURE       | The Master PU struct is disabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnablePpuFixedRgMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnablePpuFixedRgMasterStruct(PERI_GR_PPU_RG_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;

    if (CY_PERI_V1)
    {
        PERI_GR_PPU_RG_ATT1(base) |= _VAL2FLD(PERI_GR_PPU_RG_ATT1_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_GR_PPU_RG_ATT1_ENABLED, PERI_GR_PPU_RG_ATT1(base)) != CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisablePpuFixedRgMasterStruct
****************************************************************************//**
*
* Disables the Master PPU RG structure.
*
* This is a PPU RG master struct disable function. The PPU RG protection 
* settings will seize to take effect after successful completion of this 
* function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Master PU struct was disabled.
*   CY_PROT_FAILURE       | The Master PU struct is enabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisablePpuFixedRgMasterStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisablePpuFixedRgMasterStruct(PERI_GR_PPU_RG_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    if (CY_PERI_V1)
    {
        PERI_GR_PPU_RG_ATT1(base) &= ~_VAL2FLD(PERI_GR_PPU_RG_ATT1_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_GR_PPU_RG_ATT1_ENABLED, PERI_GR_PPU_RG_ATT1(base)) == CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_EnablePpuFixedRgSlaveStruct
****************************************************************************//**
*
* Enables the Slave PPU RG structure.
*
* This is a PPU RG slave struct enable function. The PPU RG protection 
* settings will take effect after successful completion of this function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Slave PU struct was enabled.
*   CY_PROT_FAILURE       | The Slave PU struct is disabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_EnablePpuFixedRgSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_EnablePpuFixedRgSlaveStruct(PERI_GR_PPU_RG_Type* base)
{   
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    if (CY_PERI_V1)
    {
        PERI_GR_PPU_RG_ATT0(base) |= _VAL2FLD(PERI_GR_PPU_RG_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_GR_PPU_RG_ATT0_ENABLED, PERI_GR_PPU_RG_ATT0(base)) != CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Cy_Prot_DisablePpuFixedRgSlaveStruct
****************************************************************************//**
*
* Disables the Slave PPU RG structure.
*
* This is a PPU RG slave struct disable function. The PPU RG protection 
* settings will seize to take effect after successful completion of this 
* function call.
*
* \note This function is applicable for CPUSS ver_1 only.
*
* \param base
* The base address for the protection unit structure being configured. 
*
* \return
* Status of the function call.
*
*   Status                | Description
*   ------------          | -----------
*   CY_PROT_SUCCESS       | The Slave PU struct was disabled.
*   CY_PROT_FAILURE       | The Slave PU struct is enabled and possibly locked.
*   CY_PROT_INVALID_STATE | The function was called on the device with an unsupported PERI HW version.
*
* \funcusage
* \snippet prot/1.20/snippet/main.c snippet_Cy_Prot_DisablePpuFixedRgSlaveStruct
*
*******************************************************************************/
cy_en_prot_status_t Cy_Prot_DisablePpuFixedRgSlaveStruct(PERI_GR_PPU_RG_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;
    
    if (CY_PERI_V1)
    {
        PERI_GR_PPU_RG_ATT0(base) &= ~_VAL2FLD(PERI_GR_PPU_RG_ATT0_ENABLED, CY_PROT_STRUCT_ENABLE);
        status = (_FLD2VAL(PERI_GR_PPU_RG_ATT0_ENABLED, PERI_GR_PPU_RG_ATT0(base)) == CY_PROT_STRUCT_ENABLE) ?
                    CY_PROT_FAILURE : CY_PROT_SUCCESS;
    }

    return status;
}


/*******************************************************************************
* Function Name: Prot_IsSmpuStructDisabled
****************************************************************************//**
*
* This function returns the SMPU disabled status.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param smpuStcIndex
* index of the SMPU structure.
*
* \return
* true if both Slave and Master structures are disabled.
* false if Master or/and Slave structure is/are enabled.
*
*******************************************************************************/
static bool Prot_IsSmpuStructDisabled(uint32_t smpuStcIndex)
{
    return ((!_FLD2BOOL(PROT_SMPU_SMPU_STRUCT_ATT0_ENABLED, PROT_SMPU_SMPU_STRUCT_IDX_ATT0(smpuStcIndex))) &&
            (!_FLD2BOOL(PROT_SMPU_SMPU_STRUCT_ATT1_ENABLED, PROT_SMPU_SMPU_STRUCT_IDX_ATT1(smpuStcIndex))));
}


/*******************************************************************************
* Function Name: Prot_IsPpoProgStructDisabled
****************************************************************************//**
*
* This function returns the Peripheral PPU disabled status.
*
* \note This function is applicable for both CPUSS ver_1 and ver_2.
*
* \param ppuStcIndex
* index of the Prot_IsPpoProgStructDisabled structure.
*
* \return
* true if both Slave and Master structures are disabled.
* false if Master or/and Slave structure is/are enabled.
*
*******************************************************************************/
static bool Prot_IsPpuProgStructDisabled(uint32_t ppuStcIndex)
{
    return ((!_FLD2BOOL(PERI_PPU_PR_ATT0_ENABLED, PROT_PERI_PPU_PR_STRUCT_IDX_ATT0(ppuStcIndex))) &&
            (!_FLD2BOOL(PERI_PPU_PR_ATT1_ENABLED, PROT_PERI_PPU_PR_STRUCT_IDX_ATT1(ppuStcIndex))));
}


#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
