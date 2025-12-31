/**
  ******************************************************************************
  * @file               ft32f4xx_comp.c
  * @author             FMD xzhang
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the comparators (COMP1 COMP2 COMP3 COMP4 COMP5 COMP6) peripheral:
  *                      + Comparators configuration
  *                      + Window mode control
  *                      + RAMP mode control
  *                      + QUALIFICATION mode control
  * @version            V1.0.0
  * @date                   2025-03-20
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_comp.h"

/**
  * @brief  Initializes the COMP peripheral according to the specified parameters
  *         in COMP_InitStruct
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  *
  * @param  COMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  *            @arg COMP_Selection_COMP3: COMP3 selected
  *            @arg COMP_Selection_COMP4: COMP4 selected
  *            @arg COMP_Selection_COMP5: COMP5 selected
  *            @arg COMP_Selection_COMP6: COMP6 selected
  * @param  COMP_InitStruct: pointer to an COMP_InitTypeDef structure that contains
  *         the configuration information for the specified COMP peripheral.
  * @retval None
  */
void COMP_Init(uint32_t COMP_Selection, COMP_InitTypeDef *COMP_InitStruct)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
    assert_param(IS_COMP_BLANKING(COMP_InitStruct ->COMP_Blanking_Sel));
    assert_param(IS_COMP_HYSTERESIS(COMP_InitStruct ->COMP_Hysteresis_Sel));
    assert_param(IS_COMP_POL(COMP_InitStruct ->COMP_Pol));

    /*!< Configure COMP: COMP_VipSel, COMP_VinSel,COMP_Blanking_Sel ,COMP_Hysteresis_Sel , COMP_Pol */
    tmpreg = (uint32_t)((COMP_InitStruct ->COMP_VipSel | COMP_InitStruct ->COMP_VinSel | COMP_InitStruct -> COMP_Blanking_Sel | COMP_InitStruct ->COMP_Hysteresis_Sel | COMP_InitStruct ->COMP_Pol));

    if (COMP_Selection == COMP_Selection_COMP1)
    {
        /* Check the parameters */
        assert_param(IS_COMP1_VIP_SEL(COMP_InitStruct ->COMP_VipSel));
        assert_param(IS_COMP1_VIN_SEL(COMP_InitStruct ->COMP_VinSel));
        /*!< Write to COMP_CSR register */
        COMP_OPAM_DAC -> COMP1_CSR = tmpreg;
    }
    else if (COMP_Selection == COMP_Selection_COMP2)
    {
        /* Check the parameters */
        assert_param(IS_COMP2_VIP_SEL(COMP_InitStruct ->COMP_VipSel));
        assert_param(IS_COMP2_VIN_SEL(COMP_InitStruct ->COMP_VinSel));
        /*!< Write to COMP_CSR register */
        COMP_OPAM_DAC -> COMP2_CSR = tmpreg;
    }
    else if (COMP_Selection == COMP_Selection_COMP3)
    {
        /* Check the parameters */
        assert_param(IS_COMP3_VIP_SEL(COMP_InitStruct ->COMP_VipSel));
        assert_param(IS_COMP3_VIN_SEL(COMP_InitStruct ->COMP_VinSel));
        /*!< Write to COMP_CSR register */
        COMP_OPAM_DAC -> COMP3_CSR = tmpreg;
    }
    else if (COMP_Selection == COMP_Selection_COMP4)
    {
        /* Check the parameters */
        assert_param(IS_COMP4_VIP_SEL(COMP_InitStruct ->COMP_VipSel));
        assert_param(IS_COMP4_VIN_SEL(COMP_InitStruct ->COMP_VinSel));
        /*!< Write to COMP_CSR register */
        COMP_OPAM_DAC -> COMP4_CSR = tmpreg;
    }
    else if (COMP_Selection == COMP_Selection_COMP5)
    {
        /* Check the parameters */
        assert_param(IS_COMP5_VIP_SEL(COMP_InitStruct ->COMP_VipSel));
        assert_param(IS_COMP5_VIN_SEL(COMP_InitStruct ->COMP_VinSel));
        /*!< Write to COMP_CSR register */
        COMP_OPAM_DAC -> COMP5_CSR = tmpreg;
    }
    else if (COMP_Selection == COMP_Selection_COMP6)
    {
        /* Check the parameters */
        assert_param(IS_COMP6_VIP_SEL(COMP_InitStruct ->COMP_VipSel));
        assert_param(IS_COMP6_VIN_SEL(COMP_InitStruct ->COMP_VinSel));
        /*!< Write to COMP_CSR register */
        COMP_OPAM_DAC -> COMP6_CSR = tmpreg;
    }
}

/**
  * @brief  Deinitializes COMP peripheral registers to their default reset values.
  * @note   Deinitialization can't be performed if the COMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  None
  * @retval None
  */
void COMP_DeInit(uint32_t COMP_Selection)
{
    /* Check the parameters */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

    if (COMP_Selection == COMP_Selection_COMP1)
    {
        COMP_OPAM_DAC -> COMP1_CSR = ((uint32_t)0x00000000);    /*!< Set COMP_CSR register to reset value */
        COMP_OPAM_DAC -> COMP1_RAMPMAXREF_SHADOW = ((uint32_t)0x00000000);  /*!< Set COMP1_RAMPMAXREF_SHADOW register to reset value */
        COMP_OPAM_DAC -> COMP1_RAMPDECVAL_SHADOW = ((uint32_t)0x00000000);  /*!< Set COMP1_RAMPDECVAL_SHADOW register to reset value */
    }
    else if (COMP_Selection == COMP_Selection_COMP2)
    {
        COMP_OPAM_DAC -> COMP2_CSR = ((uint32_t)0x00000000);    /*!< Set COMP_CSR register to reset value */
        COMP_OPAM_DAC -> COMP2_RAMPMAXREF_SHADOW = ((uint32_t)0x00000000);  /*!< Set COMP2_RAMPMAXREF_SHADOW register to reset value */
        COMP_OPAM_DAC -> COMP2_RAMPDECVAL_SHADOW = ((uint32_t)0x00000000);  /*!< Set COMP2_RAMPDECVAL_SHADOW register to reset value */
    }
    else if (COMP_Selection == COMP_Selection_COMP3)
    {
        COMP_OPAM_DAC -> COMP3_CSR = ((uint32_t)0x00000000);    /*!< Set COMP_CSR register to reset value */
    }
    else if (COMP_Selection == COMP_Selection_COMP4)
    {
        COMP_OPAM_DAC -> COMP4_CSR = ((uint32_t)0x00000000);    /*!< Set COMP_CSR register to reset value */
    }
    else if (COMP_Selection == COMP_Selection_COMP5)
    {
        COMP_OPAM_DAC -> COMP5_CSR = ((uint32_t)0x00000000);    /*!< Set COMP_CSR register to reset value */
    }
    else if (COMP_Selection == COMP_Selection_COMP6)
    {
        COMP_OPAM_DAC -> COMP6_CSR = ((uint32_t)0x00000000);    /*!< Set COMP_CSR register to reset value */
    }

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
  *            @arg COMP_Selection_COMP4: COMP4 selected
  *            @arg COMP_Selection_COMP5: COMP5 selected
  *            @arg COMP_Selection_COMP6: COMP6 selected
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

    if (NewState != DISABLE)
    {
        if (COMP_Selection == COMP_Selection_COMP1)
        {
            COMP_OPAM_DAC -> COMP1_CSR |= COMP_EN;      //enable comp1
        }
        else if (COMP_Selection == COMP_Selection_COMP2)
        {
            COMP_OPAM_DAC -> COMP2_CSR |= COMP_EN;      //enable comp2
        }
        else if (COMP_Selection == COMP_Selection_COMP3)
        {
            COMP_OPAM_DAC -> COMP3_CSR |= COMP_EN;      //enable comp3
        }
        else if (COMP_Selection == COMP_Selection_COMP4)
        {
            COMP_OPAM_DAC -> COMP4_CSR |= COMP_EN;      //enable comp4
        }
        else if (COMP_Selection == COMP_Selection_COMP5)
        {
            COMP_OPAM_DAC -> COMP5_CSR |= COMP_EN;      //enable comp5
        }
        else if (COMP_Selection == COMP_Selection_COMP6)
        {
            COMP_OPAM_DAC -> COMP6_CSR |= COMP_EN;      //enable comp6
        }
    }
    else
    {
        if (COMP_Selection == COMP_Selection_COMP1)
        {
            COMP_OPAM_DAC -> COMP1_CSR &= ~COMP_EN;     //disable comp1
        }
        else if (COMP_Selection == COMP_Selection_COMP2)
        {
            COMP_OPAM_DAC -> COMP2_CSR &= ~COMP_EN;     //disable comp2
        }
        else if (COMP_Selection == COMP_Selection_COMP3)
        {
            COMP_OPAM_DAC -> COMP3_CSR &= ~COMP_EN;     //disable comp3
        }
        else if (COMP_Selection == COMP_Selection_COMP4)
        {
            COMP_OPAM_DAC -> COMP4_CSR &= ~COMP_EN;     //disable comp4
        }
        else if (COMP_Selection == COMP_Selection_COMP5)
        {
            COMP_OPAM_DAC -> COMP5_CSR &= ~COMP_EN;     //disable comp5
        }
        else if (COMP_Selection == COMP_Selection_COMP6)
        {
            COMP_OPAM_DAC -> COMP6_CSR &= ~COMP_EN;     //disable comp6
        }
    }
}
/**
  * @}
  */
/**
  * @brief  Enables or disables the window mode.
  * @note   In window mode, COMP3 COMP4 are connected together,COMP5 COMP6 are connected together
  *         if select COMP3 's window mode as output ,COMP4 will not enable COMPx_OUTSEL;
  *         if select COMP4 's window mode as output ,COMP3 will not enable COMPx_OUTSEL;
  *         if select COMP5 's window mode as output ,COMP6 will not enable COMPx_OUTSEL;
  *         if select COMP6 's window mode as output ,COMP5 will not enable COMPx_OUTSEL;
  * @param  NewState: new state of the window mode.
  *          This parameter can be :
  *           @arg ENABLE: COMP3 and COMP4 or COMP5 and COMP6 are connected together.
  *           @arg DISABLE: COMP3 and COMP4 or COMP5 and COMP6 are disconnected.
  * @param  COMP_WIN_Selection: the selected comparator of Window mode.
  *          This parameter can be one of the following values:
  *           COMP_WIN_Selection_COMP3 : Connect INP of COMP3 to INP of COMP4
  *           COMP_WIN_Selection_COMP4 : Connect INP of COMP4 to INP of COMP3
  *           COMP_WIN_Selection_COMP5 : Connect INP of COMP5 to INP of COMP6
  *           COMP_WIN_Selection_COMP6 : Connect INP of COMP6 to INP of COMP5
  * @retval None
  */
void COMP_WindowCmd(FunctionalState NewState, uint32_t COMP_WIN_Selection)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_COMP_WIN_PERIPH(COMP_WIN_Selection));

    if (NewState != DISABLE)
    {
        if (COMP_WIN_Selection == COMP_WIN_Selection_COMP3)    //comp3 inp to comp4 inp
        {
            /* Enable the window mode of COMP3*/
            COMP_OPAM_DAC -> COMP3_CSR |= WINMODE | OUTSEL; //enable Comp3_outsel
            COMP_OPAM_DAC -> COMP4_CSR &= ~WINMODE & ~OUTSEL; //disable Comp4_outsel
        }
        else if (COMP_WIN_Selection == COMP_WIN_Selection_COMP4) //comp4 inp to comp3 inp
        {
            /* Enable the window mode of COMP4*/
            COMP_OPAM_DAC -> COMP4_CSR |= WINMODE | OUTSEL ; //enable Comp4_outsel;
            COMP_OPAM_DAC -> COMP3_CSR &= ~WINMODE & ~OUTSEL ; //disable Comp3_outsel;
        }
        else if (COMP_WIN_Selection == COMP_WIN_Selection_COMP5)//comp5 inp to comp6 inp
        {
            /* Enable the window mode of COMP5*/
            COMP_OPAM_DAC -> COMP5_CSR |= WINMODE | OUTSEL ; //enable Comp5_outsel;
            COMP_OPAM_DAC -> COMP6_CSR &= ~WINMODE & ~OUTSEL ; //disable Comp6_outsel;
        }
        else if (COMP_WIN_Selection == COMP_WIN_Selection_COMP6) //comp6 inp to comp5 inp
        {
            /* Enable the window mode of COMP6*/
            COMP_OPAM_DAC -> COMP6_CSR |= WINMODE | OUTSEL; //enable Comp6_outsel;
            COMP_OPAM_DAC -> COMP5_CSR &= ~WINMODE & ~OUTSEL ; //disable Comp5_outsel;
        }
    }
    else
    {
        if (COMP_WIN_Selection == COMP_WIN_Selection_COMP3 || COMP_WIN_Selection == COMP_WIN_Selection_COMP4)
        {
            /* Disable the window mode of comp3 comp4 */
            COMP_OPAM_DAC -> COMP3_CSR &= ~WINMODE & ~OUTSEL;
            COMP_OPAM_DAC -> COMP4_CSR &= ~WINMODE & ~OUTSEL;
        }
        else if (COMP_WIN_Selection == COMP_WIN_Selection_COMP5 || COMP_WIN_Selection == COMP_WIN_Selection_COMP6)
        {
            /* Disable the window mode of comp5 comp6 */
            COMP_OPAM_DAC -> COMP5_CSR &= ~WINMODE & ~OUTSEL;
            COMP_OPAM_DAC -> COMP6_CSR &= ~WINMODE & ~OUTSEL;
        }
    }
}

/**
  * @brief  Select epwm from HRTIME as trigger of RAMP mode in comp1 and comp 2.
  * @note   If want to use RAMP function need to enable DAC_Input_sel.DAC_INPUT_SEL_RAMP firstly.
  * @param   COMP_1_2_Selection: select COMP1 or COMP2.
  *          This parameter can be :
  *           @arg COMP_1_2_Selection_COMP1:select COMP1 .
  *           @arg COMP_1_2_Selection_COMP2:select COMP2.
  * @param   COMP_RAMP_SEL: Select EPWM as trigger of RAMP source  .
  *          This parameter can be one of the following values:
  *           COMPx_RAMPSRC_PWM1 : select EPWM1 as RAMP function trigger source
  *           COMPx_RAMPSRC_PWM2 : select EPWM2 as RAMP function trigger source
  *           COMPx_RAMPSRC_PWM3 : select EPWM3 as RAMP function trigger source
  *           COMPx_RAMPSRC_PWM4 : select EPWM4 as RAMP function trigger source
  * @retval None
  */
void COMPx_RAMP_EPWM_SEL(uint32_t COMP_1_2_Selection, uint32_t COMP_RAMP_SEL)
{
    assert_param(IS_COMP_1_2_PERIPH(COMP_1_2_Selection));
    assert_param(IS_COMP_RAMPSRC(COMP_RAMP_SEL));

    if (COMP_1_2_Selection == COMP_1_2_Selection_COMP1) //select COMP1 's RAMP mode
    {
        if (COMP_RAMP_SEL == COMPx_RAMPSRC_PWM1)     //select epwm1 as trigger
        {
            COMP_OPAM_DAC -> COMP1_CSR |= COMPx_RAMPSRC_PWM1;
        }
        else if (COMP_RAMP_SEL == COMPx_RAMPSRC_PWM2) //select epwm2 as trigger
        {
            COMP_OPAM_DAC -> COMP1_CSR |= COMPx_RAMPSRC_PWM2;
        }
        else if (COMP_RAMP_SEL == COMPx_RAMPSRC_PWM3) //select epwm3 as trigger
        {
            COMP_OPAM_DAC -> COMP1_CSR |= COMPx_RAMPSRC_PWM3;
        }
        else if (COMP_RAMP_SEL == COMPx_RAMPSRC_PWM4) //select epwm4 as trigger
        {
            COMP_OPAM_DAC -> COMP1_CSR |= COMPx_RAMPSRC_PWM4;
        }
    }
    else if (COMP_1_2_Selection == COMP_1_2_Selection_COMP2) //select COMP2 's RAMP mode
    {
        if (COMP_RAMP_SEL == COMPx_RAMPSRC_PWM1)     //select epwm1 as trigger
        {
            COMP_OPAM_DAC -> COMP2_CSR |= COMPx_RAMPSRC_PWM1;
        }
        else if (COMP_RAMP_SEL == COMPx_RAMPSRC_PWM2) //select epwm2 as trigger
        {
            COMP_OPAM_DAC -> COMP2_CSR |= COMPx_RAMPSRC_PWM2;
        }
        else if (COMP_RAMP_SEL == COMPx_RAMPSRC_PWM3) //select epwm3 as trigger
        {
            COMP_OPAM_DAC -> COMP2_CSR |= COMPx_RAMPSRC_PWM3;
        }
        else if (COMP_RAMP_SEL == COMPx_RAMPSRC_PWM4) //select epwm4 as trigger
        {
            COMP_OPAM_DAC -> COMP2_CSR |= COMPx_RAMPSRC_PWM4;
        }
    }
}

/**
  * @brief  Select RAMPLDIS bit to forbid COMP RAMP reset in comp1 and comp 2.
  * @note   If want to use RAMP function need to enable DAC_Input_sel.DAC_INPUT_SEL_RAMP firstly.
  * @param   COMP_1_2_Selection: select COMP1 or COMP2.
  *          This parameter can be :
  *           @arg COMP_1_2_Selection_COMP1:select COMP1 .
  *           @arg COMP_1_2_Selection_COMP2:select COMP2.
  * @param  NewState: new state of the COMP peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void COMPx_RAMP_RMPRLDIS(FunctionalState NewState, uint32_t COMP_1_2_Selection)
{
    assert_param(IS_COMP_1_2_PERIPH(COMP_1_2_Selection));

    if (COMP_1_2_Selection == COMP_1_2_Selection_COMP1) //select COMP1
    {
        if (NewState != DISABLE)
            COMP_OPAM_DAC -> COMP1_CSR |= RAMPLDIS;
        else
            COMP_OPAM_DAC -> COMP1_CSR &= ~RAMPLDIS;
    }
    else if (COMP_1_2_Selection == COMP_1_2_Selection_COMP2) //select COMP2
    {
        if (NewState != DISABLE)
            COMP_OPAM_DAC -> COMP2_CSR |= RAMPLDIS;
        else
            COMP_OPAM_DAC -> COMP2_CSR &= ~RAMPLDIS;
    }
}

/**
  * @brief  Load RAMPDECVAL_SHADOW and RAMPMAXREF_SHADOW of COMP1 and COMP2.
  * @param  COMPx_RAMPDECVAL_SHADOW is 16 bit ,x=comp1 or comp2
  * @param  COMPx_RAMPMAXREF_SHADOW is 16 bit ,x=comp1 or comp2
  * @param  COMP_1_2_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg COMP_1_2_Selection_COMP1: COMP1 be selected
  *            @arg COMP_1_2_Selection_COMP2: COMP2 be selected
  * @retval
  */
void COMP_RAMPVAL_SHADOW_LOAD(uint32_t COMP_1_2_Selection, uint16_t COMPx_RAMPDECVAL_SHADOW, uint16_t COMPx_RAMPMAXREF_SHADOW)
{
    /* Check the parameters */
    assert_param(IS_COMP_1_2_PERIPH(COMP_1_2_Selection));

    if (COMP_1_2_Selection == COMP_1_2_Selection_COMP1)                   //select comp1
    {
        /* load ramp max value*/
        COMP_OPAM_DAC -> COMP1_RAMPMAXREF_SHADOW = COMPx_RAMPMAXREF_SHADOW;
        /* load ramp dec value */
        COMP_OPAM_DAC -> COMP1_RAMPDECVAL_SHADOW = COMPx_RAMPDECVAL_SHADOW;
    }
    else if (COMP_1_2_Selection == COMP_1_2_Selection_COMP2)              //select comp2
    {
        /* load ramp max value*/
        COMP_OPAM_DAC -> COMP2_RAMPMAXREF_SHADOW = COMPx_RAMPMAXREF_SHADOW;
        /* load ramp dec value */
        COMP_OPAM_DAC -> COMP2_RAMPDECVAL_SHADOW = COMPx_RAMPDECVAL_SHADOW;
    }

}


/**
  * @brief  Select qualification number and enable qualification mode in comp1 and comp2.
  * @note
  * @param   NewState: new state of the qualification mode.
  *          This parameter can be :
  *           @arg ENABLE: COMP1 or COMP2 enable qualification mode.
  *           @arg DISABLE: COMP1 or COMP2 disable qualification mode.
  * @param   COMP_1_2_Selection: select COMP1 or COMP2.
  *          This parameter can be :
  *           @arg COMP_1_2_Selection_COMP1:select COMP1.
  *           @arg COMP_1_2_Selection_COMP2:select COMP2.
  * @param   COMP_qualsel: Select qualification clk number.
  *          This parameter can be one of the following values:
  *           COMPx_QUALSEL_NONE :None select qualification clk number
  *           COMPx_QUALSEL_1C : select 1 clk as qualification clk number
  *           COMPx_QUALSEL_2C : select 2 clk as qualification clk number
  *           COMPx_QUALSEL_3C : select 3 clk as qualification clk number
  *           COMPx_QUALSEL_4C : select 4 clk as qualification clk number
  *           COMPx_QUALSEL_5C : select 5 clk as qualification clk number
  *           COMPx_QUALSEL_6C : select 6 clk as qualification clk number
  *           COMPx_QUALSEL_7C : select 7 clk as qualification clk number
  *           COMPx_QUALSEL_8C : select 8 clk as qualification clk number
  *           COMPx_QUALSEL_9C : select 9 clk as qualification clk number
  *           COMPx_QUALSEL_10C: select 10 clk as qualification clk number
  *           COMPx_QUALSEL_11C: select 11 clk as qualification clk number
  *           COMPx_QUALSEL_12C: select 12 clk as qualification clk number
  *           COMPx_QUALSEL_13C: select 13 clk as qualification clk number
  *           COMPx_QUALSEL_14C: select 14 clk as qualification clk number
  *           COMPx_QUALSEL_15C: select 15 clk as qualification clk number
  *           COMPx_QUALSEL_16C: select 16 clk as qualification clk number
  *           COMPx_QUALSEL_17C: select 17 clk as qualification clk number
  *           COMPx_QUALSEL_18C: select 18 clk as qualification clk number
  *           COMPx_QUALSEL_18C: select 19 clk as qualification clk number
  *           COMPx_QUALSEL_20C: select 20 clk as qualification clk number
  *           COMPx_QUALSEL_21C: select 21 clk as qualification clk number
  *           COMPx_QUALSEL_22C: select 22 clk as qualification clk number
  *           COMPx_QUALSEL_23C: select 23 clk as qualification clk number
  *           COMPx_QUALSEL_24C: select 24 clk as qualification clk number
  *           COMPx_QUALSEL_25C: select 25 clk as qualification clk number
  *           COMPx_QUALSEL_26C: select 26 clk as qualification clk number
  *           COMPx_QUALSEL_27C: select 27 clk as qualification clk number
  *           COMPx_QUALSEL_28C: select 28 clk as qualification clk number
  *           COMPx_QUALSEL_29C: select 29 clk as qualification clk number
  *           COMPx_QUALSEL_30C: select 30 clk as qualification clk number
  *           COMPx_QUALSEL_31C: select 31 clk as qualification clk number
  * @retval None
  */
void COMPx_QUALIFICATION(FunctionalState NewState, uint32_t COMP_1_2_Selection, uint32_t COMP_qualsel)
{
    assert_param(IS_COMP_1_2_PERIPH(COMP_1_2_Selection));
    assert_param(IS_COMP_QUALSER_PERIPH(COMP_qualsel));

    if (NewState != DISABLE)
    {
        if (COMP_1_2_Selection == COMP_1_2_Selection_COMP1)   //select COMP1
        {
            /* enable qualification mode in Comp1 */
            COMP_OPAM_DAC -> COMP1_CSR |= QUALEN ;
            /* select qualification number and enable sync bit*/
            COMP_OPAM_DAC -> COMP1_CSR |= COMP_qualsel | SYNCSEL;
        }
        else if (COMP_1_2_Selection == COMP_1_2_Selection_COMP2) //select COMP2
        {
            /* enable qualification mode in Comp1 */
            COMP_OPAM_DAC -> COMP2_CSR |= QUALEN ;
            /* select qualification number and enable sync bit */
            COMP_OPAM_DAC -> COMP2_CSR |= COMP_qualsel | SYNCSEL;
        }
    }
    else
    {
        if (COMP_1_2_Selection == COMP_1_2_Selection_COMP1)   //select COMP1
        {
            COMP_OPAM_DAC -> COMP1_CSR &= ~COMP_qualsel & ~SYNCSEL & ~QUALEN;
        }
        else if (COMP_1_2_Selection == COMP_1_2_Selection_COMP2) //select COMP2
        {
            COMP_OPAM_DAC -> COMP2_CSR &= ~COMP_qualsel & ~SYNCSEL & ~QUALEN;
        }
    }
}

/**
  * @brief  enable or disable feedback 100K resistor.
  * @param   NewState: new state of the RAMP mode.
  *          This parameter can be :
  *           @arg ENABLE: COMP1 or COMP2 enable feedback resistor .
  *           @arg DISABLE: COMP1 or COMP2 disable feedback resistor .
  * @param   COMP_1_2_Selection: select COMP1 or COMP2.
  *          This parameter can be :
  *           @arg COMP_1_2_Selection_COMP1:select COMP1.
  *           @arg COMP_1_2_Selection_COMP2:select COMP2.
  * @retval None
  */
void COMPx_Resistor(FunctionalState NewState, uint32_t COMP_1_2_Selection)
{
    assert_param(IS_COMP_1_2_PERIPH(COMP_1_2_Selection));

    if (NewState != DISABLE)
    {
        if (COMP_1_2_Selection == COMP_1_2_Selection_COMP1)
        {
            COMP_OPAM_DAC ->  COMP1_CSR |= RSWITCH;   //enable resistor of comp1
        }
        else if (COMP_1_2_Selection == COMP_1_2_Selection_COMP2)
        {
            COMP_OPAM_DAC ->  COMP2_CSR |= RSWITCH;   //enable resistor of comp1
        }
    }
    else
    {
        if (COMP_1_2_Selection == COMP_1_2_Selection_COMP1)
        {
            COMP_OPAM_DAC ->  COMP1_CSR &= ~RSWITCH;    //disable resistor of comp1
        }
        else if (COMP_1_2_Selection == COMP_1_2_Selection_COMP2)
        {
            COMP_OPAM_DAC ->  COMP2_CSR &= ~RSWITCH;    //disable resistor of comp1
        }
    }
}


/**
  * @brief  Lock the selected comparator (COMP1/COMP2/COMP3/COMP4/COMP5/COMP6) configuration.
  * @note   Locking the configuration means that all control bits are read-only.
  *         To unlock the comparator configuration, perform a system reset.
  * @param  COMP_Selection: selects the comparator to be locked
  *          This parameter can be a value of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 configuration is locked.
  *            @arg COMP_Selection_COMP2: COMP2 configuration is locked.
  *            @arg COMP_Selection_COMP3: COMP3 configuration is locked.
  *            @arg COMP_Selection_COMP4: COMP4 configuration is locked.
  *            @arg COMP_Selection_COMP5: COMP5 configuration is locked.
  *            @arg COMP_Selection_COMP6: COMP6 configuration is locked.
  * @retval None
  */
void COMP_LockConfig(uint32_t COMP_Selection)
{
    /* Check the parameter */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

    if (COMP_Selection == COMP_Selection_COMP1)
        COMP_OPAM_DAC ->  COMP1_CSR |= COMP_LOCK;     //lock COMP1_CSR's bit

    else if (COMP_Selection == COMP_Selection_COMP2)
        COMP_OPAM_DAC ->  COMP2_CSR |= COMP_LOCK;     //lock COMP2_CSR's bit

    else if (COMP_Selection == COMP_Selection_COMP3)
        COMP_OPAM_DAC ->  COMP3_CSR |= COMP_LOCK;     //lock COMP3_CSR's bit

    else if (COMP_Selection == COMP_Selection_COMP4)
        COMP_OPAM_DAC ->  COMP4_CSR |= COMP_LOCK;     //lock COMP4_CSR's bit

    else if (COMP_Selection == COMP_Selection_COMP5)
        COMP_OPAM_DAC ->  COMP5_CSR |= COMP_LOCK;     //lock COMP5_CSR's bit

    else if (COMP_Selection == COMP_Selection_COMP6)
        COMP_OPAM_DAC ->  COMP6_CSR |= COMP_LOCK;     //lock COMP6_CSR's bit
}


/**
  * @brief  Return the output level (high or low) of the selected comparator ,which is behind the comp analog out and ahead of qualification .
  * @note   The output level NOT depends on the selected polarity.
  * @note   The polarity is not influence output value:
  *          - Comparator output is low when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is high when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @param  COMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg COMP_Selection_COMP1: COMP1 selected
  *            @arg COMP_Selection_COMP2: COMP2 selected
  *            @arg COMP_Selection_COMP3: COMP3 selected
  *            @arg COMP_Selection_COMP4: COMP4 selected
  *            @arg COMP_Selection_COMP5: COMP5 selected
  *            @arg COMP_Selection_COMP6: COMP6 selected
  * @retval Returns the selected comparator output level: low or high.
  *
  */
uint32_t COMP_GetOutputLevel(uint32_t COMP_Selection)
{
    uint32_t compout = 0x0;

    /* Check the parameters */
    assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

    if (COMP_Selection == COMP_Selection_COMP1)
    {
        /* Check if selected comparator output is high */
        if (((COMP_OPAM_DAC -> COMP1_CSR) & COMPx_CSR_VALUE_Msk)  == (uint32_t)VALUE)
        {
            compout = (uint32_t) COMP_OutputLevel_High >> 30;
        }
        else
        {
            compout = (uint32_t) COMP_OutputLevel_Low >> 30;
        }
    }
    else if (COMP_Selection == COMP_Selection_COMP2)
    {
        /* Check if selected comparator output is high */
        if (((COMP_OPAM_DAC -> COMP2_CSR) & COMPx_CSR_VALUE_Msk) == (uint32_t)VALUE)
        {
            compout = (uint32_t) COMP_OutputLevel_High  >> 30;
        }
        else
        {
            compout = (uint32_t) COMP_OutputLevel_Low  >> 30;
        }
    }
    else if (COMP_Selection == COMP_Selection_COMP3)
    {
        /* Check if selected comparator output is high */
        if (((COMP_OPAM_DAC -> COMP3_CSR) & (uint32_t)VALUE) == (uint32_t)VALUE)
        {
            compout = (uint32_t) COMP_OutputLevel_High >> 30;
        }
        else
        {
            compout = (uint32_t) COMP_OutputLevel_Low >> 30;
        }
    }
    else if (COMP_Selection == COMP_Selection_COMP4)
    {
        /* Check if selected comparator output is high */
        if (((COMP_OPAM_DAC -> COMP4_CSR) & (uint32_t)VALUE) == (uint32_t)VALUE)
        {
            compout = (uint32_t) COMP_OutputLevel_High >> 30;
        }
        else
        {
            compout = (uint32_t) COMP_OutputLevel_Low >> 30;
        }
    }
    else if (COMP_Selection == COMP_Selection_COMP5)
    {
        /* Check if selected comparator output is high */
        if (((COMP_OPAM_DAC -> COMP5_CSR) & (uint32_t)VALUE) == (uint32_t)VALUE)
        {
            compout = (uint32_t) COMP_OutputLevel_High >> 30;
        }
        else
        {
            compout = (uint32_t) COMP_OutputLevel_Low >> 30;
        }
    }
    else if (COMP_Selection == COMP_Selection_COMP6)
    {
        /* Check if selected comparator output is high */
        if (((COMP_OPAM_DAC -> COMP6_CSR) & (uint32_t)VALUE) == (uint32_t)VALUE)
        {
            compout = (uint32_t) COMP_OutputLevel_High >> 30;
        }
        else
        {
            compout = (uint32_t) COMP_OutputLevel_Low >> 30;
        }
    }
    /* Return the comparator output level */
    return (uint32_t)(compout);
}


/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
