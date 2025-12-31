/**
  ******************************************************************************
  * @file               ft32f1xx_opa.c
  * @author             FMD xzhang
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the comparators (OPA1 OPA2 OPA3) peripheral
  *                     applicable
  * @version            V1.0.0
  * @data                   2025-03-31
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_opamp.h"
#include "ft32f4xx_rcc.h"


/**
  * @brief  Initializes the OPA peripheral according to the specified parameters
  *         in OPA_InitStruct
  * @note   If the selected opamp is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @note   To correctly run this function, the OPA_Cali() function must be called before.
  * @param  OPAMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg OPAMP_1:  OPAMP1 selected
  *            @arg OPAMP_2:  OPAMP2 selected
  *            @arg OPAMP_3:  OPAMP3 selected
  * @param  OPA_InitStruct: pointer to an OPA_InitTypeDef structure that contains
  *         the configuration information for the specified OPA peripheral.
  * @retval None
  */
void OPA_Init(OPA_InitTypeDef* OPA_InitStruct, uint32_t OPAMP_Selection)
{
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;

    /* Check the parameters */
    assert_param(IS_OPAX_PERIPH(OPAMP_Selection));
    assert_param(IS_OPA_VIP_SEL(OPA_InitStruct -> OPA_VPSEL));
    assert_param(IS_OPA_VIM_SEL(OPA_InitStruct -> OPA_VMSEL));
    assert_param(IS_OPA_VIPS_SEL(OPA_InitStruct -> OPA_VPSSEL));
    assert_param(IS_OPA_VIMS_SEL(OPA_InitStruct -> OPA_VMSSEL));
    assert_param(IS_OPAX_TIM8_EN(OPA_InitStruct -> T8_CM));
    assert_param(IS_OPAX_TIM1_EN(OPA_InitStruct -> T1_CM));
    assert_param(IS_OPAX_OPAHSM(OPA_InitStruct -> OPAHSM));
    assert_param(IS_OPAX_OPINTOEN(OPA_InitStruct -> OPINTOEN));
    assert_param(IS_OPAX_O2PADSEL(OPA_InitStruct -> O2PADSEL));
    assert_param(IS_OPA_PGAGAIN(OPA_InitStruct -> OPA_PGAGAIN));

    /*!< Configure : OPA_VPSEL OPA_VMSEL OPAHSM OPINTOEN O2PADSEL OPA_PGAGAIN*/
    tmpreg1 = (uint32_t)(OPA_InitStruct -> OPA_VPSEL | OPA_InitStruct -> OPA_VMSEL |   OPA_InitStruct -> OPAHSM | OPA_InitStruct -> OPINTOEN | OPA_InitStruct -> O2PADSEL | OPA_InitStruct -> OPA_PGAGAIN);

    /*!< Configure : OPA_VPSSEL OPA_VMSSEL T8_CM T1_CM*/
    tmpreg2 = (uint32_t)(OPA_InitStruct -> OPA_VPSSEL | OPA_InitStruct -> OPA_VMSSEL | OPA_InitStruct ->T8_CM | OPA_InitStruct -> T1_CM);

    if (OPAMP_Selection == OPAMP_1)           //config opamp1
    {
        /*!< Write to COMP_CSR register */
        COMP_OPAM_DAC ->OPAMP1_CSR  = tmpreg1;
        COMP_OPAM_DAC ->OPAMP1_TCMR = tmpreg2;
    }
    else if (OPAMP_Selection == OPAMP_2)      //config opamp2
    {
        /*!< Write to COMP_CSR register */
        COMP_OPAM_DAC ->OPAMP2_CSR  = tmpreg1;
        COMP_OPAM_DAC ->OPAMP2_TCMR  = tmpreg2;
    }
    else if (OPAMP_Selection == OPAMP_3)      //config opamp3
    {
        /*!< Write to COMP_CSR register */
        COMP_OPAM_DAC ->OPAMP3_CSR  = tmpreg1;
        COMP_OPAM_DAC ->OPAMP3_TCMR  = tmpreg2;
    }
}


/**
  * @brief  Deinitializes OPA peripheral registers to their default reset values.
  * @note   Deinitialization can't be performed if the OPA configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAx: the selected comparator.
  *         This parameter can be one of the following values:
  *            @arg OPAMP_1:  OPAMP1 selected
  *            @arg OPAMP_2:  OPAMP2 selected
  *            @arg OPAMP_3:  OPAMP3 selected
  * @retval None
  */
void OPA_DeInit(uint32_t OPAMP_Selection)
{
    /* Check the parameters */
    assert_param(IS_OPAX_PERIPH(OPAMP_Selection));

    if (OPAMP_Selection == OPAMP_1)
    {
        /*!< Set OPA_CSR register to reset value */
        COMP_OPAM_DAC ->OPAMP1_CSR  = ((uint32_t)0x00000000);
        COMP_OPAM_DAC ->OPAMP1_TCMR  = ((uint32_t)0x00000000);
    }
    else if (OPAMP_Selection == OPAMP_2)
    {
        COMP_OPAM_DAC ->OPAMP2_CSR  = ((uint32_t)0x00000000);
        COMP_OPAM_DAC ->OPAMP2_TCMR  = ((uint32_t)0x00000000);
    }
    else if (OPAMP_Selection == OPAMP_3)
    {
        COMP_OPAM_DAC ->OPAMP3_CSR  = ((uint32_t)0x00000000);
        COMP_OPAM_DAC ->OPAMP3_TCMR  = ((uint32_t)0x00000000);
    }

}


/**
  * @brief  Enable or disable the OPA peripheral.
  * @note   If the selected opamp is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  OPAMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg OPAMP_1:  OPAMP1 selected
  *            @arg OPAMP_2:  OPAMP2 selected
  *            @arg OPAMP_3:  OPAMP3 selected
  * @param  NewState: new state of the OPA peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When disabled, the opamp doesn't perform comparison and the
  *         output level is low.
  * @retval None
  */
void OPA_Cmd(uint32_t OPAMP_Selection, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_OPAX_PERIPH(OPAMP_Selection));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        if (OPAMP_Selection == OPAMP_1)
            /* Enable the selected OPA peripheral */
            COMP_OPAM_DAC ->OPAMP1_CSR |= OPAMP1_CSR_OPAEN;
        else if (OPAMP_Selection == OPAMP_2)
            /* Enable the selected OPA peripheral */
            COMP_OPAM_DAC ->OPAMP2_CSR |= OPAMP2_CSR_OPAEN;
        else if (OPAMP_Selection == OPAMP_3)
            /* Enable the selected OPA peripheral */
            COMP_OPAM_DAC ->OPAMP3_CSR |= OPAMP3_CSR_OPAEN;
    }
    else
    {
        if (OPAMP_Selection == OPAMP_1)
            /* Disable the selected OPA peripheral  */
            COMP_OPAM_DAC ->OPAMP1_CSR &= ~OPAMP1_CSR_OPAEN;
        else if (OPAMP_Selection == OPAMP_2)
            /* Disable the selected OPA peripheral  */
            COMP_OPAM_DAC ->OPAMP2_CSR &= ~OPAMP2_CSR_OPAEN;
        else if (OPAMP_Selection == OPAMP_3)
            /* Disable the selected OPA peripheral  */
            COMP_OPAM_DAC ->OPAMP3_CSR &= ~OPAMP3_CSR_OPAEN;
    }
}



/**
  * @brief  Calibration OPAMPx 's NMOS or PMOS.
  * @note  If you want to Calibration OPAMP ,recommend to use OPA_DeInit() firstly.
  * @note  Every TRIMOFFSETN/P change need delay 200 us
  * @note  Trim NMOS switch to PMOS need delay 500 us at least ,in this Function is 600us
  * @param  OPAMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg OPAMP_1:  OPAMP1 selected
  *            @arg OPAMP_2:  OPAMP2 selected
  *            @arg OPAMP_3:  OPAMP3 selected
  * @retval  NONE
  */
volatile uint32_t flag;
volatile uint32_t flag_n;
volatile uint32_t flag_p;
volatile uint32_t nmos_cnt = 0;
volatile uint32_t pmos_cnt = 0;

void OPAMP_Calibration(uint32_t OPAMP_Selection)
{
    uint32_t next_nmos_cnt;
    uint32_t next_pmos_cnt;
    uint32_t apbclock;
    /*This is TIM's ARR value is calculate automaticly according to sysclk by users set */
    uint32_t ARR_value;

    RCC_ClocksTypeDef RCC_ClocksStatus;

    RCC_GetClocksFreq(&RCC_ClocksStatus);

    apbclock = RCC_ClocksStatus.PCLK_Frequency ;

    if ((RCC->CFGR & 0x400) == 0x400) //if PPRE1[10] bit is 1
        ARR_value = (apbclock >> 2) / 625; //==(200*time freq)/1000000, tim freq=2 * apbclock;
    else
        ARR_value = (apbclock >> 3) / 625; //==(200*apbclock)/1000000;


    /*Open TIMER6 clk */
    RCC->APB1ENR |=  RCC_APB1ENR_TIM6EN;
    /*set 50us as calibration delay by TIMER6 */
    NVIC_EnableIRQ(TIM6_DAC_IRQn);
    TIM6 -> DIER   |=   TIM_DIER_UIE ;
    TIM6 -> ARR     =   ARR_value       ; //delay: 200us ;0xc80 =200000ns/T(freq clk)  Now apb1clk is 16MHZ
    TIM6 -> CR2    |=   TIM_CR2_MMS_1  ;
    TIM6 -> CR1    |=   TIM_CR1_CEN  ;
    /* ==========================select OPAMP1==========================*/
    if (OPAMP_Selection == OPAMP_1)
    {
        /*-------------------calibration NMOS------------------*/
        /*make sure enable opamp1*/
        COMP_OPAM_DAC -> OPAMP1_CSR |= OPAMP1_CSR_OPAEN   ;
        /*enable cal trim*/
        COMP_OPAM_DAC -> OPAMP1_CSR |= OPAMP1_CSR_USERTRIM ;
        /*cal sel NMOS*/
        COMP_OPAM_DAC -> OPAMP1_CSR |= OPAMP1_CSR_CALSEL_0 | OPAMP1_CSR_CALSEL_1;
        /*vpsel =101*/
        COMP_OPAM_DAC -> OPAMP1_CSR |= OPAMP1_CSR_VP_SEL_2 | OPAMP1_CSR_VP_SEL_0;

        /*if nmos_cnt = 31,jump out cal NMOS*/
        while (((COMP_OPAM_DAC -> OPAMP1_CSR) & OPAMP1_CSR_TRIMOFFSETN_Msk) != OPAMP1_CSR_TRIMOFFSETN_Msk)
        {
            /*wait calout value become 0 */
            while ((COMP_OPAM_DAC -> OPAMP1_CSR & OPAMP1_CSR_CALOUT) == 0x40000000)
            {
                if (nmos_cnt >= 0x1f)
                {
                    /*NMOS max value is 31 */
                    nmos_cnt = 0x1f;
                    break;
                }
                else
                {
                    /*wait 50us flag*/
                    while (flag_n == 1)
                    {
                        next_nmos_cnt = (nmos_cnt << 24) | 0xe0ffffff;
                        /*updata TRIMOFFSETN value in OPAMP1_CSR and keep other bit*/
                        COMP_OPAM_DAC -> OPAMP1_CSR = next_nmos_cnt & (0x1f000000 | (COMP_OPAM_DAC -> OPAMP1_CSR));
                        nmos_cnt ++;
                        flag_n = 0;
                    }
                }
            }
            break;
        }
        /*wait 600us*/
        for (int num = 0; num < 3; num++)
        {
            flag = 1;
            while (flag == 1); //wait 50us
        }
        /*-----------------calibration PMOS-----------------*/
        /*cal sel PMOS*/
        COMP_OPAM_DAC -> OPAMP1_CSR &= ~OPAMP1_CSR_CALSEL_1 ;
        /*if pmos_cnt = 31,jump out cal PMOS*/
        while (((COMP_OPAM_DAC -> OPAMP1_CSR) & OPAMP1_CSR_TRIMOFFSETP_Msk) != OPAMP1_CSR_TRIMOFFSETP_Msk)
        {
            while ((COMP_OPAM_DAC -> OPAMP1_CSR & OPAMP1_CSR_CALOUT) == 0x40000000)
            {
                if (pmos_cnt >= 0x20)
                {
                    pmos_cnt = 0x1f;
                    break;
                }
                else
                {
                    /*wait 50us flag*/
                    while (flag_p == 1)
                    {
                        next_pmos_cnt = (pmos_cnt << 19) | 0xff07ffff;
                        /*updata TRIMOFFSETN value in OPAMP1_CSR and keep other bit*/
                        COMP_OPAM_DAC -> OPAMP1_CSR = next_pmos_cnt & (0x00f80000 | (COMP_OPAM_DAC -> OPAMP1_CSR));
                        pmos_cnt ++;
                        flag_p = 0;
                    }
                }
            }
            break;
        }
        flag = 1;
        while (flag == 1); //50us
        COMP_OPAM_DAC -> OPAMP1_CSR &= ~OPAMP1_CSR_CALSEL_0
                                       &  ~OPAMP1_CSR_USERTRIM
                                       &  ~OPAMP1_CSR_VP_SEL_2 //vp_sel:000
                                       &  ~OPAMP1_CSR_VP_SEL_0;
    }//end opamp1


    /* =============================select OPAMP2==========================*/
    else if (OPAMP_Selection == OPAMP_2)
    {
        /*-------------------calibration NMOS------------------*/
        /*make sure enable OPAMP2*/
        COMP_OPAM_DAC -> OPAMP2_CSR |= OPAMP2_CSR_OPAEN   ;
        /*enable cal trim*/
        COMP_OPAM_DAC -> OPAMP2_CSR |= OPAMP2_CSR_USERTRIM ;
        /*cal sel NMOS*/
        COMP_OPAM_DAC -> OPAMP2_CSR |= OPAMP2_CSR_CALSEL_0 | OPAMP2_CSR_CALSEL_1;
        /*vpsel =101*/
        COMP_OPAM_DAC -> OPAMP2_CSR |= OPAMP2_CSR_VP_SEL_2 | OPAMP2_CSR_VP_SEL_0;
        /*if nmos_cnt = 31,jump out cal NMOS*/
        while (((COMP_OPAM_DAC -> OPAMP2_CSR) & OPAMP2_CSR_TRIMOFFSETN_Msk) != OPAMP2_CSR_TRIMOFFSETN_Msk)
        {
            /*wait calout value become 0 */
            while ((COMP_OPAM_DAC -> OPAMP2_CSR & OPAMP2_CSR_CALOUT) == 0x40000000)
            {
                if (nmos_cnt >= 0x1f)
                {
                    /*NMOS max value is 31 */
                    nmos_cnt = 0x1f;
                    break;
                }
                else
                {
                    /*wait 50us flag*/
                    while (flag_n == 1)
                    {
                        next_nmos_cnt = (nmos_cnt << 24) | 0xe0ffffff;
                        /*updata TRIMOFFSETN value in OPAMP2_CSR and keep other bit*/
                        COMP_OPAM_DAC -> OPAMP2_CSR = next_nmos_cnt & (0x1f000000 | (COMP_OPAM_DAC -> OPAMP2_CSR));
                        nmos_cnt ++;
                        flag_n = 0;
                    }
                }
            }
            break;
        }
        /*wait 600us*/
        for (int num = 0; num < 3; num++)
        {
            flag = 1;
            while (flag == 1);
        }
        /*-----------------calibration PMOS-----------------*/
        /*cal sel PMOS*/
        COMP_OPAM_DAC -> OPAMP2_CSR &= ~OPAMP2_CSR_CALSEL_1 ;
        /*if pmos_cnt = 31,jump out cal PMOS*/
        while (((COMP_OPAM_DAC -> OPAMP2_CSR) & OPAMP2_CSR_TRIMOFFSETP_Msk) != OPAMP2_CSR_TRIMOFFSETP_Msk)
        {
            while ((COMP_OPAM_DAC -> OPAMP2_CSR & OPAMP2_CSR_CALOUT) == 0x40000000)
            {
                if (pmos_cnt >= 0x20)
                {
                    pmos_cnt = 0x1f;
                    break;
                }
                else
                {
                    /*wait 50us flag*/
                    while (flag_p == 1)
                    {
                        next_pmos_cnt = (pmos_cnt << 19) | 0xff07ffff;
                        /*updata TRIMOFFSETN value in OPAMP2_CSR and keep other bit*/
                        COMP_OPAM_DAC -> OPAMP2_CSR = next_pmos_cnt & (0x00f80000 | (COMP_OPAM_DAC -> OPAMP2_CSR));
                        pmos_cnt ++;
                        flag_p = 0;
                    }
                }
            }
            break;
        }
        flag = 1;
        while (flag == 1); //50us
        COMP_OPAM_DAC -> OPAMP2_CSR &= ~OPAMP2_CSR_CALSEL_0
                                       &  ~OPAMP2_CSR_USERTRIM
                                       &  ~OPAMP2_CSR_VP_SEL_2 //vp_sel:000
                                       &  ~OPAMP2_CSR_VP_SEL_0;
    }//end OPAMP2

    /*================================= select OPAMP3===============================*/
    else if (OPAMP_Selection == OPAMP_3)
    {
        /*-------------------calibration NMOS------------------*/
        /*make sure enable OPAMP3*/
        COMP_OPAM_DAC -> OPAMP3_CSR |= OPAMP3_CSR_OPAEN   ;
        /*enable cal trim*/
        COMP_OPAM_DAC -> OPAMP3_CSR |= OPAMP3_CSR_USERTRIM ;
        /*cal sel NMOS*/
        COMP_OPAM_DAC -> OPAMP3_CSR |= OPAMP3_CSR_CALSEL_0 | OPAMP3_CSR_CALSEL_1;
        /*vpsel =101*/
        COMP_OPAM_DAC -> OPAMP3_CSR |= OPAMP3_CSR_VP_SEL_2 | OPAMP3_CSR_VP_SEL_0;

        /*if nmos_cnt = 31,jump out cal NMOS*/
        while (((COMP_OPAM_DAC -> OPAMP3_CSR) & OPAMP3_CSR_TRIMOFFSETN_Msk) != OPAMP3_CSR_TRIMOFFSETN_Msk)
        {
            /*wait calout value become 0 */
            while ((COMP_OPAM_DAC -> OPAMP3_CSR & OPAMP3_CSR_CALOUT) == 0x40000000)
            {
                if (nmos_cnt >= 0x1f)
                {
                    /*NMOS max value is 31 */
                    nmos_cnt = 0x1f;
                    break;
                }
                else
                {
                    /*wait 50us flag*/
                    while (flag_n == 1)
                    {
                        next_nmos_cnt = (nmos_cnt << 24) | 0xe0ffffff;
                        /*updata TRIMOFFSETN value in OPAMP3_CSR and keep other bit*/
                        COMP_OPAM_DAC -> OPAMP3_CSR = next_nmos_cnt & (0x1f000000 | (COMP_OPAM_DAC -> OPAMP3_CSR));
                        nmos_cnt ++;
                        flag_n = 0;
                    }
                }
            }
            break;
        }
        /*wait 600us*/
        for (int num = 0; num < 3; num++)
        {
            flag = 1;
            while (flag == 1); //wait 50us
        }
        /*-----------------calibration PMOS-----------------*/
        /*cal sel PMOS*/
        COMP_OPAM_DAC -> OPAMP3_CSR &= ~OPAMP3_CSR_CALSEL_1 ;
        /*if pmos_cnt = 31,jump out cal PMOS*/
        while (((COMP_OPAM_DAC -> OPAMP3_CSR) & OPAMP3_CSR_TRIMOFFSETP_Msk) != OPAMP3_CSR_TRIMOFFSETP_Msk)
        {
            while ((COMP_OPAM_DAC -> OPAMP3_CSR & OPAMP3_CSR_CALOUT) == 0x40000000)
            {
                if (pmos_cnt >= 0x20)
                {
                    pmos_cnt = 0x1f;
                    break;
                }
                else
                {
                    /*wait 50us flag*/
                    while (flag_p == 1)
                    {
                        next_pmos_cnt = (pmos_cnt << 19) | 0xff07ffff;
                        /*updata TRIMOFFSETN value in OPAMP3_CSR and keep other bit*/
                        COMP_OPAM_DAC -> OPAMP3_CSR = next_pmos_cnt & (0x00f80000 | (COMP_OPAM_DAC -> OPAMP3_CSR));
                        pmos_cnt ++;
                        flag_p = 0;
                    }
                }
            }
            break;
        }
        flag = 1;
        while (flag == 1); //50us
        COMP_OPAM_DAC -> OPAMP3_CSR &= ~OPAMP3_CSR_CALSEL_0
                                       &  ~OPAMP3_CSR_USERTRIM
                                       &  ~OPAMP3_CSR_VP_SEL_2 //vp_sel:000
                                       &  ~OPAMP3_CSR_VP_SEL_0;
    }//end OPAMP3

}

void TIM6_DAC_Handler(void)
{
    flag = 0;
    flag_n = 1;
    flag_p = 1;

    TIM6 -> SR   &=  ~TIM_SR_UIF;
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
