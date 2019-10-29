/***************************************************************************//**
* \file  cy_sysint.c
* \version 1.20
*
* \brief
* Provides an API implementation of the SysInt driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2018, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_sysint.h"


/*******************************************************************************
* Function Name: Cy_SysInt_Init
****************************************************************************//**
*
* \brief Initializes the referenced interrupt by setting the priority and the
* interrupt vector.
*
* Use the CMSIS core function NVIC_EnableIRQ(config.intrSrc) to enable the interrupt.
*
* \param config
* Interrupt configuration structure
*
* \param userIsr
* Address of the ISR
*
* \return 
* Initialization status  
*
* \note The interrupt vector will be relocated only if the vector table was
* moved to __ramVectors in SRAM. Otherwise it is ignored.
*
* \funcusage
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_Init
*
*******************************************************************************/
cy_en_sysint_status_t Cy_SysInt_Init(const cy_stc_sysint_t* config, cy_israddress userIsr)
{
    cy_en_sysint_status_t status = CY_SYSINT_SUCCESS;

    if(NULL != config)
    {
        CY_ASSERT_L3(CY_SYSINT_IS_PRIORITY_VALID(config->intrPriority));

        #if (CY_CPU_CORTEX_M0P)
            if (config->intrSrc > SysTick_IRQn)
            {
                Cy_SysInt_SetInterruptSource(config->intrSrc, config->cm0pSrc);
            }
            else
            {
                status = CY_SYSINT_BAD_PARAM;
            }
        #endif
        
        NVIC_SetPriority(config->intrSrc, config->intrPriority);
        
        /* Set the new vector only if it was moved to __ramVectors */
        if (SCB->VTOR == (uint32_t)&__ramVectors)
        {
            (void)Cy_SysInt_SetVector(config->intrSrc, userIsr);
        }
    }
    else
    {
        status = CY_SYSINT_BAD_PARAM;
    }
    
    return(status);
}


#if (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysInt_SetInterruptSource
****************************************************************************//**
*
* \brief Configures the interrupt selection for the specified NVIC channel.
*
* To disconnect the interrupt source from the NVIC channel
* use the \ref Cy_SysInt_DisconnectInterruptSource.
*
* \param IRQn
* NVIC channel number connected to the CPU core.
*
* \param devIntrSrc
* Device interrupt to be routed to the NVIC channel.
*
* \note This function is available for CM0+ core only.
*
* \funcusage
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_SetInterruptSource
*
*******************************************************************************/
void Cy_SysInt_SetInterruptSource(IRQn_Type IRQn, cy_en_intr_t devIntrSrc)
{    
    if (CY_CPUSS_V1)
    {
        uint32_t regPos = ((uint32_t)IRQn >> CY_SYSINT_CM0P_MUX_SHIFT);
        if(0UL == (regPos & (uint32_t)~CY_SYSINT_MUX_REG_MSK))
        {
            uint32_t bitfield_Pos = (uint32_t)((uint32_t)IRQn - (uint32_t)(regPos << CY_SYSINT_CM0P_MUX_SHIFT)) << CY_SYSINT_CM0P_MUX_SCALE;
            uint32_t bitfield_Msk = (uint32_t)(CY_SYSINT_CM0P_MUX_MASK << bitfield_Pos);
            
            CY_REG32_CLR_SET(CPUSS_CM0_INT_CTL[regPos], bitfield, devIntrSrc);
        }
    }
    else /* CPUSS_V2 */
    {
        CY_ASSERT_L1(CY_CPUSS_DISCONNECTED_IRQN != devIntrSrc); /* Disconnection feature doesn't work for CPUSS_V2 */

        CPUSS_CM0_SYSTEM_INT_CTL[devIntrSrc] = _VAL2FLD(CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_IDX, IRQn)
                                                      | CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk;
    }
}


/*******************************************************************************
* Function Name: Cy_SysInt_DisconnectInterruptSource
****************************************************************************//**
*
* \brief Disconnect the interrupt source from the specified NVIC channel.
*
* \param IRQn
* NVIC channel number connected to the CPU core.
* This parameter is ignored for devices using CPUSS_ver2.
*
* \param devIntrSrc
* Device interrupt routed to the NVIC channel.
* This parameter is ignored for devices using CPUSS_ver1.
*
* \note This function is available for CM0+ core only.
*
* \funcusage
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_DisconnectInterruptSource
*
*******************************************************************************/
void Cy_SysInt_DisconnectInterruptSource(IRQn_Type IRQn, cy_en_intr_t devIntrSrc)
{
    if (CY_CPUSS_V1)
    {
        Cy_SysInt_SetInterruptSource(IRQn, CY_CPUSS_DISCONNECTED_IRQN);
    }
    else /* CPUSS_V2 */
    {
        CPUSS_CM0_SYSTEM_INT_CTL[devIntrSrc] &= (uint32_t)~ CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_VALID_Msk;
    }
}


/*******************************************************************************
* Function Name: Cy_SysInt_GetInterruptSource
****************************************************************************//**
*
* \brief Gets the interrupt source of the NVIC channel.
*
* \param IRQn
* NVIC channel number connected to the CPU core
*
* \return 
* Device interrupt connected to the NVIC channel. A returned value of 
* "disconnected_IRQn" indicates that the interrupt source is disconnected.  
*
* \note This function is available for CM0+ core only.
*
* \note This function supports only devices using CPUSS_ver1. For all
* other devices, use the Cy_SysInt_GetNvicConnection() function.
*
* \funcusage
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_SetInterruptSource
*
*******************************************************************************/
cy_en_intr_t Cy_SysInt_GetInterruptSource(IRQn_Type IRQn)
{
    uint32_t tempReg = CY_CPUSS_NOT_CONNECTED_IRQN;

    if (CY_CPUSS_V1)
    {
        uint32_t regPos  = ((uint32_t)IRQn >> CY_SYSINT_CM0P_MUX_SHIFT);
        if(0UL == (regPos & (uint32_t)~CY_SYSINT_MUX_REG_MSK))
        {
            uint32_t bitfield_Pos  = ((uint32_t)IRQn - (regPos <<  CY_SYSINT_CM0P_MUX_SHIFT)) <<  CY_SYSINT_CM0P_MUX_SCALE;
            uint32_t bitfield_Msk = (uint32_t)(CY_SYSINT_CM0P_MUX_MASK << bitfield_Pos);
        
            tempReg = _FLD2VAL(bitfield, CPUSS_CM0_INT_CTL[regPos]);
        }
    }

    return ((cy_en_intr_t)tempReg);
}

    
/*******************************************************************************
* Function Name: Cy_SysInt_GetNvicConnection
****************************************************************************//**
*
* \brief Gets the NVIC channel to which the interrupt source is connected.
*
* \param devIntrSrc
* Device interrupt that is potentially connected to the NVIC channel.
*
* \return
* NVIC channel number connected to the CPU core. A returned value of
* "unconnected_IRQn" indicates that the interrupt source is disabled.
*
* \note This function is available for CM0+ core only.
*
* \note This function supports only devices using CPUSS_ver2 or higher.
*
* \funcusage
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_SetInterruptSource
*
*******************************************************************************/
IRQn_Type Cy_SysInt_GetNvicConnection(cy_en_intr_t devIntrSrc)
{
    uint32_t tempReg = CY_CPUSS_NOT_CONNECTED_IRQN;

    if ((!CY_CPUSS_V1) && (CY_SYSINT_ENABLE == _FLD2VAL(CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_VALID, CPUSS_CM0_SYSTEM_INT_CTL[devIntrSrc])))
    {
        tempReg = _FLD2VAL(CPUSS_V2_CM0_SYSTEM_INT_CTL_CPU_INT_IDX, CPUSS_CM0_SYSTEM_INT_CTL[devIntrSrc]);
    }
    return ((IRQn_Type)tempReg);
}


/*******************************************************************************
* Function Name: Cy_SysInt_GetInterruptActive
****************************************************************************//**
*
* \brief Gets the highest priority active interrupt for the selected NVIC channel.
*
* The priority of the interrupt in a given channel is determined by the index
* value of the interrupt in the cy_en_intr_t enum. The lower the index, the 
* higher the priority. E.g. Consider a case where an interrupt source with value
* 29 and an interrupt source with value 46 both source the same NVIC channel. If
* both are active (triggered) at the same time, calling Cy_SysInt_GetInterruptActive()
* will return 29 as the active interrupt.
*
* \param IRQn
* NVIC channel number connected to the CPU core
*
* \return
* Device interrupt connected to the NVIC channel. A returned value of 
* "disconnected_IRQn" indicates that there are no active (pending) interrupts 
* on this NVIC channel.  
*
* \note This function is available for CM0+ core only.
*
* \note This function supports only devices using CPUSS_ver2 or higher.
*
* \funcusage
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_GetInterruptActive
*
*******************************************************************************/
cy_en_intr_t Cy_SysInt_GetInterruptActive(IRQn_Type IRQn)
{
    uint32_t tempReg = CY_CPUSS_NOT_CONNECTED_IRQN;
    uint32_t locIdx = (uint32_t)IRQn & CY_SYSINT_INT_STATUS_MSK;

    if ((!CY_CPUSS_V1) && (CY_SYSINT_ENABLE == _FLD2VAL(CPUSS_V2_CM0_INT0_STATUS_SYSTEM_INT_VALID, CPUSS_CM0_INT_STATUS[locIdx])))
    {
        tempReg = _FLD2VAL(CPUSS_V2_CM0_INT0_STATUS_SYSTEM_INT_IDX, CPUSS_CM0_INT_STATUS[locIdx]);
    }
    return (cy_en_intr_t)tempReg;
}

#endif


/*******************************************************************************
* Function Name: Cy_SysInt_SetVector
****************************************************************************//**
*
* \brief Changes the ISR vector for the interrupt.
*
* This function relies on the assumption that the vector table is
* relocated to __ramVectors[RAM_VECTORS_SIZE] in SRAM. Otherwise it will
* return the address of the default ISR location in the flash vector table.
*
* \param IRQn
* Interrupt source
*
* \param userIsr
* Address of the ISR to set in the interrupt vector table
*
* \return
* Previous address of the ISR in the interrupt vector table
*
* \note For CM0+, this function sets the interrupt vector for the interrupt
* channel on the NVIC.
*
* \funcusage
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_SetVector
*
*******************************************************************************/
cy_israddress Cy_SysInt_SetVector(IRQn_Type IRQn, cy_israddress userIsr)
{
    cy_israddress prevIsr;
    
    /* Set the new vector only if it was moved to __ramVectors */
    if (SCB->VTOR == (uint32_t)&__ramVectors)
    {
        CY_ASSERT_L1(CY_SYSINT_IS_VECTOR_VALID(userIsr));

        prevIsr = __ramVectors[CY_INT_IRQ_BASE + IRQn];
        __ramVectors[CY_INT_IRQ_BASE + IRQn] = userIsr;
    }
    else
    {
        prevIsr = __Vectors[CY_INT_IRQ_BASE + IRQn];
    }

    return prevIsr;
}


/*******************************************************************************
* Function Name: Cy_SysInt_GetVector
****************************************************************************//**
*
* \brief Gets the address of the current ISR vector for the interrupt.
*
* This function relies on the assumption that the vector table is
* relocated to __ramVectors[RAM_VECTORS_SIZE] in SRAM. Otherwise it will
* return the address of the default ISR location in the flash vector table.
*
* \param IRQn
* Interrupt source
*
* \return
* Address of the ISR in the interrupt vector table
*
* \note For CM0+, this function returns the interrupt vector for the interrupt 
* channel on the NVIC.
*
* \funcusage
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_SetVector
*
*******************************************************************************/
cy_israddress Cy_SysInt_GetVector(IRQn_Type IRQn)
{
    cy_israddress currIsr;
    
    /* Return the SRAM ISR address only if it was moved to __ramVectors */
    if (SCB->VTOR == (uint32_t)&__ramVectors)
    {
        currIsr = __ramVectors[CY_INT_IRQ_BASE + IRQn];
    }
    else
    {
        currIsr = __Vectors[CY_INT_IRQ_BASE + IRQn];
    }
    
    return currIsr;
}


/* [] END OF FILE */
