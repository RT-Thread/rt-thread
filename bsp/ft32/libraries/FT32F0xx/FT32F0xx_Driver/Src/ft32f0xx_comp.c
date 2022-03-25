/**
  ******************************************************************************
  * @file               ft32f0xx_comp.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the comparators (COMP1 and COMP2) peripheral:
  *                      + Comparators configuration
  *                      + Window mode control
  * @version            V1.0.0
  * @data                   2021-07-01
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx_comp.h"

#define COMP_CSR_CLEAR_MASK              ((uint32_t)0x00003FFE)

/**
  * @brief  Deinitializes COMP peripheral registers to their default reset values.
  * @note   Deinitialization can't be performed if the COMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  None
  * @retval None
  */
void COMP_DeInit(void)
{
    COMP->CSR = ((uint32_t)0x00000000);    /*!< Set COMP_CSR register to reset value */

    #if defined(FT32F072xB)
        COMP->CSR2 = ((uint32_t)0x00000000);
    #endif
}

/**
  * @brief  Initializes the COMP peripheral according to the specified parameters
  *         in COMP_InitStruct
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @note   By default, PA1 is selected as COMP1 non inverting input.
  *
  * @param  COMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  *            @arg COMP_Selection_COMP3: COMP3 selected
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure that contains
  *         the configuration information for the specified COMP peripheral.
  * @retval None
  */
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef* COMP_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
    assert_param(IS_COMP_VIP_SEL(COMP_InitStruct->COMP_VipSel));
    assert_param(IS_COMP_VINSEL(COMP_InitStruct->COMP_VinSel));
    assert_param(IS_COMP_OUTPUT_SEL(COMP_InitStruct->COMP_OutputSel));
    assert_param(IS_COMP_POL(COMP_InitStruct->COMP_Pol));

    if (COMP_Selection != COMP_Selection_COMP3)
    {
        /*!< Get the COMP_CSR register value */
        tmpreg = COMP->CSR;

        /*!< Clear the bits */
        tmpreg &= (uint32_t) ~(COMP_CSR_CLEAR_MASK<<COMP_Selection);

        /*!< Configure COMP: COMP_VipSel, COMP_VinSel, COMP_OutputSel value and COMP_Pol */
        tmpreg |= (uint32_t)((COMP_InitStruct->COMP_VipSel | COMP_InitStruct->COMP_VinSel|
                           COMP_InitStruct->COMP_OutputSel | COMP_InitStruct->COMP_Pol));

        /*!< Write to COMP_CSR register */
        COMP->CSR = tmpreg;
    }
    else
    {
        #if defined(FT32F072xB)
            /*!< Get the COMP_CSR register value */
            tmpreg = COMP->CSR2;

            /*!< Clear the bits */
            tmpreg &= (uint32_t) ~(COMP_CSR_CLEAR_MASK);

            /*!< Configure COMP: COMP_VipSel, COMP_VinSel, COMP_OutputSel value and COMP_Pol */
            tmpreg |= (uint32_t)((COMP_InitStruct->COMP_VipSel | COMP_InitStruct->COMP_VinSel|
                                    COMP_InitStruct->COMP_OutputSel | COMP_InitStruct->COMP_Pol));

            /*!< Write to COMP_CSR2 register */
            COMP->CSR2 = tmpreg;
        #endif
    }
}

/**
  * @brief  Fills each COMP_InitStruct member with its default value.
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void COMP_StructInit(COMP_InitTypeDef* COMP_InitStruct)
{
    #if defined(FT32F072xB)
        COMP_InitStruct->COMP_VipSel = 0;
        COMP_InitStruct->COMP_VinSel = 0;
        COMP_InitStruct->COMP_OutputSel = 0;
        COMP_InitStruct->COMP_Pol = 0;
    #else
        COMP_InitStruct->COMP_VipSel = NCOMP_VIP_SEL_PAD_PA1;
        COMP_InitStruct->COMP_VinSel = NCOMP_VIN_SEL_PAD_PA0 | PCOMP_VIN_SEL_PAD_PA2;
        COMP_InitStruct->COMP_OutputSel = 0;
        COMP_InitStruct->COMP_Pol = 0;
    #endif
}

/**
  * @brief  Enable or disable the COMP peripheral.
  * @note   If the selected comparator is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  COMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  *            @arg COMP_Selection_COMP3: COMP3 selected
  * @param  NewState: new state of the COMP peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, the comparator compares the non inverting input with
  *         the inverting input and the comparison result is available on comparator output.
  * @note   When disabled, the comparator doesn't perform comparison and the
  *         output level is low.
  * @retval None
  */
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(COMP_Selection != COMP_Selection_COMP3)
    {
        if (NewState != DISABLE)
        {
            /* Enable the selected COMP peripheral */
            COMP->CSR |= (uint32_t) (1<<COMP_Selection);
        }
        else
        {
            /* Disable the selected COMP peripheral  */
            COMP->CSR &= (uint32_t)(~((uint32_t)1<<COMP_Selection));
        }
    }
    else
    {
        #if defined(FT32F072xB)
            if (NewState != DISABLE)
            {
                /* Enable the selected COMP peripheral */
                COMP->CSR2 |= (uint32_t) (1);
            }
            else
            {
                /* Disable the selected COMP peripheral  */
                COMP->CSR2 &= (uint32_t)(~((uint32_t)1));
            }
        #endif

    }
}

/**
  * @brief  Return the output level (high or low) of the selected comparator.
  * @note   The output level depends on the selected polarity.
  * @note   If the polarity is not inverted:
  *          - Comparator output is low when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is high when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @note   If the polarity is inverted:
  *          - Comparator output is high when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is low when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @param  COMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  *            @arg COMP_Selection_COMP3: COMP3 selected
  * @retval Returns the selected comparator output level: low or high.
  *
  */
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection)
{
    uint32_t compout = 0x0;

    /* Check the parameters */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

    if(COMP_Selection != COMP_Selection_COMP3)
    {
        /* Check if selected comparator output is high */
        if ((COMP->CSR & (COMP_CSR_COMP1OUT<<COMP_Selection)) != 0)
        {
            compout = COMP_OutputLevel_High;
        }
        else
        {
            compout = COMP_OutputLevel_Low;
        }
    }
    else
    {
        #if defined(FT32F072xB)
            /* Check if selected comparator output is high */
            if ( (COMP->CSR2 & COMP_CSR_COMP3OUT) != 0)
            {
                compout = COMP_OutputLevel_High;
            }
            else
            {
                compout = COMP_OutputLevel_Low;
            }
        #endif
    }

    /* Return the comparator output level */
    return (uint32_t)(compout);
}

/**
  * @}
  */
/**
  * @brief  Enables or disables the window mode.
  * @note   In window mode, COMP1 and COMP2 non inverting inputs are connected
  *         together and only COMP1 non inverting input (PA1) can be used.
  * @param  NewState: new state of the window mode.
  *          This parameter can be :
  *           @arg ENABLE: COMP1 and COMP2 non inverting inputs are connected together.
  *           @arg DISABLE: OMP1 and COMP2 non inverting inputs are disconnected.
  * @retval None
  */
void COMP_WindowCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the window mode */
    COMP->CSR |= (uint32_t) COMP_CSR_WNDWEN;
  }
  else
  {
    /* Disable the window mode */
    COMP->CSR &= (uint32_t)(~COMP_CSR_WNDWEN);
  }
}

/**
  * @}
  */
/**
  * @brief  Lock the selected comparator (COMP1/COMP2) configuration.
  * @note   Locking the configuration means that all control bits are read-only.
  *         To unlock the comparator configuration, perform a system reset.
  * @param  COMP_Selection: selects the comparator to be locked
  *          This parameter can be a value of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 configuration is locked.
  *            @arg COMP_Selection_COMP2: COMP2 configuration is locked.
  *            @arg COMP_Selection_COMP3: COMP3 configuration is locked.
  * @retval None
  */
void COMP_LockConfig(uint32_t COMP_Selection)
{
    /* Check the parameter */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

    if(COMP_Selection != COMP_Selection_COMP3)
    {
        /* Set the lock bit corresponding to selected comparator */
        COMP->CSR |= (uint32_t) (COMP_CSR_NCOMPLOCK<<COMP_Selection);
    }
    else
    {
        #if defined(FT32F072xB)
            /* Set the lock bit corresponding to selected comparator */
            COMP->CSR2 |= (uint32_t) (COMP_CSR_COMP3LOCK);
        #endif
    }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
