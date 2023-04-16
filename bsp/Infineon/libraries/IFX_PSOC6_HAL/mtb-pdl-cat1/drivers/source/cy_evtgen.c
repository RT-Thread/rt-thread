/***************************************************************************//**
* \file cy_evtgen.c
* \version 1.0
*
* \brief
* Provides API implementation of the Event generator Driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2022 Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "cy_evtgen.h"

#ifdef CY_IP_MXEVTGEN

#define RATIO_FRAC_SHIFT   100UL       /* This value is required to shift the fractional comma by two characters.
                                         It needs for the selection fractional part ratio. */

/*******************************************************************************
* Function Name: Cy_EvtGen_RatioCalculate
****************************************************************************//**
*
* Internal function for calculate two part of the RATIO register.
*
* \param frequencyTick
* High frequency of the Event Generator.
*
* \param frequencyLf
* Low frequency of the Event Generator.
*
* \param ratioInt
* The pointer to a variable where the integer part is stored.
*
* \param ratioFrac
* The pointer to a variable where the fractional part is stored.
*
*******************************************************************************/
static void Cy_EvtGen_RatioCalculate(uint32_t frequencyTick, uint32_t frequencyLf, uint16_t* ratioInt, uint8_t* ratioFrac)
{
    uint32_t tempInt = 0;
    float tempFrac = (float)frequencyTick / (float)frequencyLf;

    tempInt = (uint32_t)tempFrac;
    tempFrac = tempFrac - (float)tempInt;
    tempFrac = (tempFrac * (float)RATIO_FRAC_SHIFT);

    *ratioFrac = (uint8_t)tempFrac;
    *ratioInt = (uint16_t)tempInt;
}

/*******************************************************************************
* Function Name: Cy_EvtGen_Init
****************************************************************************//**
*
* Initialize the event generator
*
* \param base
* Pointer to structure describing registers
*
* \param config
* Pointer to the event generator config structure base address
*
* \return
* Event generator initialization status
*
*******************************************************************************/
cy_en_evtgen_status_t Cy_EvtGen_Init(EVTGEN_Type *base, const cy_stc_evtgen_config_t* config)
{
    cy_en_evtgen_status_t ret = CY_EVTGEN_BAD_PARAM;

    /* Checking input parameter valid */
    if ((NULL != base) && (NULL != config))
    {
        if ((config->frequencyRef != 0UL) && (config->frequencyTick != 0UL))
        {
            uint32_t refDiv;

            /* Setting divider value of clk_ref */
            refDiv = config->frequencyRef / config->frequencyTick;

            CY_ASSERT_L1(CY_EVTGEN_IS_DIVIDER_VALID_RANGE(refDiv));

            if(((config->frequencyRef % config->frequencyTick) == 0UL) && ((refDiv <= 256UL) && (refDiv  > 0UL)))
            {
                CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to uint8_t.');
                base->REF_CLOCK_CTL = _VAL2FLD(EVTGEN_REF_CLOCK_CTL_INT_DIV, (uint8_t)(refDiv - 1UL));

                /* Setting ratio operation */
                if(config->ratioControlMode == CY_EVTGEN_RATIO_CONTROL_SW)
                {
                    /* SW control: setting value for ratio value should be ratio between tick_ref_div and clk_lf. */
                    uint8_t ratioFrac;
                    uint16_t ratioInt;
                    Cy_EvtGen_RatioCalculate(config->frequencyTick, config->frequencyLf, &ratioInt, &ratioFrac);

                    base->RATIO = (_VAL2FLD(EVTGEN_RATIO_FRAC8, ratioFrac)) | (_VAL2FLD(EVTGEN_RATIO_INT16, ratioInt));

                    /* SW control: valid bit should be set manually. */
                    base->RATIO_CTL &= ~EVTGEN_RATIO_CTL_DYNAMIC_Msk;
                    base->RATIO_CTL |= EVTGEN_RATIO_CTL_VALID_Msk;
                }
                else
                {
                    /* HW control: */
                    base->RATIO_CTL |= EVTGEN_RATIO_CTL_DYNAMIC_Msk |
                                    (_VAL2FLD(EVTGEN_RATIO_CTL_DYNAMIC_MODE, config->ratioValueDynamicMode));
                }
                ret = CY_EVTGEN_SUCCESS;
            }
        }
    }
    return (ret);
}

/*******************************************************************************
* Function Name: Cy_EvtGen_DeInit
****************************************************************************//**
*
* Deinitialize event generator
*
* \param base
* Pointer to structure describing registers
*
*******************************************************************************/
void Cy_EvtGen_DeInit(EVTGEN_Type *base)
{
    CY_ASSERT_L1(base);

    /* Returns block registers into the default state */
    base->CTL = 0UL;
    base->REF_CLOCK_CTL = 0UL;
    base->RATIO = 0UL;
    base->RATIO_CTL = 0UL;
    base->INTR_MASK = 0UL;
    base->INTR_DPSLP_MASK = 0UL;
}

/*******************************************************************************
* Function Name: Cy_EvtGen_InitStruct
****************************************************************************//**
*
* Initialize a comparator structure
*
* \param base
* Pointer to structure describing registers
*
* \param structNum
* Number of structure to be initialized. Valid range from 0 to 16.
*
* \param configStruct
* Pointer to the event generator structure config structure base address
*
* \return
* Event generator initialization status
*
*******************************************************************************/
cy_en_evtgen_status_t Cy_EvtGen_InitStruct(EVTGEN_Type *base,
                                                        uint8_t structNum,
                                                        const cy_stc_evtgen_struct_config_t* configStruct)
{
    cy_en_evtgen_status_t ret = CY_EVTGEN_BAD_PARAM;

    /* Checking input parameter valid */
    if ((NULL != base) && (NULL != configStruct) && (EVTGEN_COMP_STRUCT_NR > structNum))
    {
        uint64_t tempCounterValue = 0UL;
        uint32_t tempCompStructCompCTL = 0UL;

        tempCompStructCompCTL = base->COMP_STRUCT[structNum].COMP_CTL;

        if (CY_EVTGEN_DEEPSLEEP_FUNCTIONALITY == configStruct->functionalitySelection)
        {
            tempCompStructCompCTL |= EVTGEN_COMP_STRUCT_COMP_CTL_COMP1_EN_Msk;
        }

        tempCompStructCompCTL |= EVTGEN_COMP_STRUCT_COMP_CTL_COMP0_EN_Msk |
                                 (_VAL2FLD(EVTGEN_COMP_STRUCT_COMP_CTL_TR_OUT_EDGE, configStruct->triggerOutEdge)) |
                                 EVTGEN_COMP_STRUCT_COMP_CTL_ENABLED_Msk;

        CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to uint64_t.');
        tempCounterValue = (uint64_t) (_FLD2VAL(EVTGEN_COUNTER_INT32, base->COUNTER));

        /* Setting active comparator value */
        base->COMP_STRUCT[structNum].COMP0 = (uint32_t) (tempCounterValue + (uint64_t) configStruct->valueActiveComparator);

        /* Setting deep sleep comparator value */
        if (CY_EVTGEN_DEEPSLEEP_FUNCTIONALITY == configStruct->functionalitySelection)
        {
            base->COMP_STRUCT[structNum].COMP1 = (uint32_t)(tempCounterValue + (uint64_t)configStruct->valueDeepSleepComparator);
        }

        /* Setting comparator struct control parameter */
        base->COMP_STRUCT[structNum].COMP_CTL = tempCompStructCompCTL;

        Cy_EvtGen_SetStructInterruptMask(base, structNum);
        if (CY_EVTGEN_DEEPSLEEP_FUNCTIONALITY == configStruct->functionalitySelection)
        {
            Cy_EvtGen_SetStructInterruptDeepSleepMask(base, structNum);
        }

        ret = CY_EVTGEN_SUCCESS;
    }
    return (ret);
}

/*******************************************************************************
* Function Name: Cy_EvtGen_DeinitStruct
****************************************************************************//**
*
* Deinitialize event generator struct
*
* \param base
* Pointer to structure describing registers
*
* \param structNum
* Number of structure to be de-initialized. Valid range from 0 to 16.
*
*******************************************************************************/
void Cy_EvtGen_DeinitStruct(EVTGEN_Type *base, uint8_t structNum)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_BASE_VALID(base));
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNum));

    base->COMP_STRUCT[structNum].COMP_CTL = 0UL;
    base->COMP_STRUCT[structNum].COMP0 = 0UL;
    base->COMP_STRUCT[structNum].COMP1 = 0UL;
}

/*******************************************************************************
* Function Name: Cy_EvtGen_UpdateActiveCompValue
****************************************************************************//**
*
* Update active comparator value corresponding comparator structure.
*
* \param base
* Pointer to structure describing registers
*
* \param structNum
* Number of structure to be update value. Valid range from 0 to 15.
*
* \param newCompareValue
* Value for update active comparator value.
*
*******************************************************************************/
void Cy_EvtGen_UpdateActiveCompValue(EVTGEN_Type *base, uint8_t structNum, uint32_t newCompareValue)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNum));

    /* Note: In cases where the current value of the comparator is close to MAX_INT
    then the update may lead to overflow. Using 64 bit handles this case. Cast to
    32 bit is safe brings the value to what it will be after the counter overflows. */
    uint64_t tempCompValue = (uint64_t) EVTGEN0->COMP_STRUCT[structNum].COMP0;
    tempCompValue += newCompareValue;

    base->COMP_STRUCT[structNum].COMP_CTL &= ~EVTGEN_COMP_STRUCT_COMP_CTL_COMP0_EN_Msk;
    base->COMP_STRUCT[structNum].COMP0 = (uint32_t) tempCompValue;
    base->COMP_STRUCT[structNum].COMP_CTL |= EVTGEN_COMP_STRUCT_COMP_CTL_COMP0_EN_Msk;
}

/*******************************************************************************
* Function Name: Cy_EvtGen_UpdateDeepSleepCompValue
****************************************************************************//**
*
* Update Deep Sleep comparator value corresponding comparator structure.
*
* \param base
* Pointer to structure describing registers
*
* \param structNum
* Number of structure to be update value. Valid range from 0 to 15.
*
* \param newCompareValue
* Value for update Deep Sleep comparator value.
*
*******************************************************************************/
void Cy_EvtGen_UpdateDeepSleepCompValue(EVTGEN_Type *base, uint8_t structNum, uint32_t newCompareValue)
{
    CY_ASSERT_L1(CY_EVTGEN_IS_STRUCTNUM_VALID(structNum));

    /* Note: In cases where the current value of the comparator is close to MAX_INT
    then the update may lead to overflow. Using 64 bit handles this case. Cast to
    32 bit is safe brings the value to what it will be after the counter overflows. */
    uint64_t tempCompValue = (uint64_t) EVTGEN0->COMP_STRUCT[structNum].COMP1;
    tempCompValue += newCompareValue;

    base->COMP_STRUCT[structNum].COMP_CTL &= ~EVTGEN_COMP_STRUCT_COMP_CTL_COMP1_EN_Msk;
    base->COMP_STRUCT[structNum].COMP1 = (uint32_t) tempCompValue;
    base->COMP_STRUCT[structNum].COMP_CTL |= EVTGEN_COMP_STRUCT_COMP_CTL_COMP1_EN_Msk;
}

#endif /* CY_IP_MXEVTGEN */

/* [] END OF FILE */
