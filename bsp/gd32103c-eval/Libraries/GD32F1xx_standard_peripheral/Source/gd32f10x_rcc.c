/**
  ******************************************************************************
  * @brief   RCC functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup RCC
  * @brief RCC driver modules
  * @{
  */

/** @defgroup RCC_Private_Defines
  * @{
  */


/* RCC GCCR_HSIEN mask */
#define  GCCR_HSIEN_SET                                 ((uint32_t)0x00000001)

/* RCC GCFGR_Reset mask */
#define  GCFGR_RESET_CL                                 ((uint32_t)0xE0FF0000)
#define  GCFGR_RESET                                    ((uint32_t)0xE8FF0000)

/* RCC GCCR_HSEEN_CKMEN_PLLEN masks */
#define  GCCR_HSEEN_CKMEN_PLLEN_RESET                   ((uint32_t)0xFEF6FFFF)

/* RCC GCCR_HSEBPS mask */
#define  GCCR_HSEBPS_RESET                              ((uint32_t)0xFFFBFFFF)

/* RCC GCFGR_PLLSEL_PLLPREDV_PLLMF masks */
#define  GCFGR_PLLSEL_PLLPREDV_PLLMF_USBPS_RESET        ((uint32_t)0xF700FFFF)
#define  GCFGR_PLLSEL_PLLPREDV_PLLMF_OTGFSPS_RESET_CL   ((uint32_t)0xDF00FFFF)

/* RCC GCCR_PLL2EN_PLL3EN masks */
#define  GCCR_PLL2EN_PLL3EN_RESET                       ((uint32_t)0xEBFFFFFF)

/* RCC GCFGR2 reset */
#define  GCFGR2_RESET                                   ((uint32_t)0x00000000)

/* RCC GCIR_INT ans FLAG masks */
#define  GCIR_INT_FLAG_RESET                            ((uint32_t)0x009F0000)
#define  GCIR_INT_FLAG_RESET_CL                         ((uint32_t)0x00FF0000)

#define  GCCR_HSEEN_HSEBPS_RESET                        ((uint32_t)0xFFFAFFFF)

/* RCC GCCR_HSIADJ masks */
#define  GCCR_HSIADJ_OFFSET                             ((uint32_t)0x00000003)


#define  RCC_GCFGR_PLLMF_3_0                            ((uint32_t)0x003C0000) /*!< PLLMF[3:0] Bits */

/* RCC HSI clock divided by 2 masks */
#define  HSI_CLOCK_DIVIDED_2                            ((uint32_t)0x00000001)

/* RCC HSE clock divided by 2 masks */
#define  HSE_CLOCK_DIVIDED_2                            ((uint32_t)0x00000001)


static __I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
static __I uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};


/* GCIR register byte 1 (Bits[15:8]) base address */
#define GCIR_BYTE1_ADDRESS                              ((uint32_t)0x40021009)

/* GCIR register byte 2 (Bits[23:16]) base address */
#define  GCIR_BYTE2_ADDRESS                             ((uint32_t)0x4002100A)

/* RCC Flag Mask */
#define FLAG_MASK                                       ((uint8_t)0x1F)

/**
  * @}
  */

/** @defgroup RCC_Private_Functions
  * @{
  */

/**
  * @brief  Reset the RCC clock configuration.
  * @param  None
  * @retval None
  */
void RCC_DeInit(void)
{
    /* Set RCC GCCR_HSIEN mask */
    RCC->GCCR |= GCCR_HSIEN_SET;

    /* Reset SCS[1:0], AHBPS[3:0], APB1PS[2:0],APB2PS[2:0], ADCPS[2:0],CKOTUSEL[2:0] bits */
#ifdef GD32F10X_CL
    RCC->GCFGR &= GCFGR_RESET_CL;
#else
    RCC->GCFGR &= GCFGR_RESET;
#endif /* GD32F10X_CL */

    /* Reset HSEEN, CKMEN and PLLEN bits */
    RCC->GCCR &= GCCR_HSEEN_CKMEN_PLLEN_RESET;

    /* Reset HSEBPS bit */
    RCC->GCCR &= GCCR_HSEBPS_RESET;

    /* Reset PLLSEL, PLLPREDV and PLLMF[4:0] USBPS/OTGFSPS bits */
#ifdef GD32F10X_CL
    RCC->GCFGR &= GCFGR_PLLSEL_PLLPREDV_PLLMF_OTGFSPS_RESET_CL;
#else
    RCC->GCFGR &= GCFGR_PLLSEL_PLLPREDV_PLLMF_USBPS_RESET;
#endif /* GD32F10X_CL */

#ifdef GD32F10X_CL
    /* Reset PLL2EN and PLL3EN bits */
    RCC->GCCR &= GCCR_PLL2EN_PLL3EN_RESET;

    /* Reset GCFGR2 register */
    RCC->GCFGR2 = GCFGR2_RESET ;

    /* Disable all interrupts and clear flag bits */
    RCC->GCIR = GCIR_INT_FLAG_RESET_CL;
#else
    /* Disable all interrupts and clear flag bits */
    RCC->GCIR = GCIR_INT_FLAG_RESET;
#endif /* GD32F10X_CL */
}

/**
  * @brief  Configure the External High Speed oscillator (HSE).
  * @param  RCC_HSE: specify the new state of HSE.
  *   This parameter can be one of the following values:
  *   @arg RCC_HSE_OFF: turn off the HSE
  *   @arg RCC_HSE_ON: turn on the HSE
  *   @arg RCC_HSE_BYPASS: HSE bypassed with external clock
  * @retval None
  */
void RCC_HSEConfig(uint32_t RCC_HSE)
{
    /* Reset HSEEN and HSEBPS bits */
    RCC->GCCR &= GCCR_HSEEN_HSEBPS_RESET;
    /* Set the new state of HSE */
    RCC->GCCR |= RCC_HSE;

}

/**
  * @brief  Wait for HSE start-up.
  * @param  None
  * @retval The HSE start-up result(SUCCESS or ERROR)
  */
TypeState RCC_WaitForHSEStartUp(void)
{
    __IO uint32_t HSE_StartOk_Counter = 0;
    TypeState HSEState = RESET;

    /* Wait until HSE is ready and if timeout to exit */
    while ((HSE_StartOk_Counter != HSE_STARTUP_TIMEOUT) && (HSEState == RESET)) {
        HSEState = RCC_GetBitState(RCC_FLAG_HSESTB);
        HSE_StartOk_Counter++;
    }

    if (RCC_GetBitState(RCC_FLAG_HSESTB) != RESET) {
        return SUCCESS;
    } else {
        return ERROR;
    }
}

/**
  * @brief  Adjust the Internal High Speed oscillator (HSI) calibration value.
  * @param  HSICalibrationValue: the HSI calibration value.
  *   This parameter must be between 0 and 0x1F.
  * @retval None
  */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
    uint32_t temp_adjust = 0;

    temp_adjust = RCC->GCCR;

    /* Clear HSIADJ[4:0] bits */
    temp_adjust &= ~RCC_GCCR_HSIADJ;

    /* Set HSIADJ[4:0] bits according to HSICalibrationValue value */
    temp_adjust |= (uint32_t)HSICalibrationValue << GCCR_HSIADJ_OFFSET ;

    /* Store the calibration value */
    RCC->GCCR = temp_adjust;
}

/**
  * @brief  Enable or disable the Internal High Speed oscillator (HSI).
  * @param  NewValue: new value of the HSI.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSI_Enable(TypeState NewValue)
{

    if (NewValue != DISABLE) {
        RCC->GCCR |= RCC_GCCR_HSIEN;
    } else {
        RCC->GCCR &= ~RCC_GCCR_HSIEN;
    }
}

/**
  * @brief  Configure the PLL clock source and multiplication factor.
  * @param  RCC_PLLSelect: specify the PLL clock source.
  *   For @b GD32_Connectivity_line_devices, this parameter can be one of the following values:
  *       @arg RCC_PLLSOURCE_HSI_DIV2: HSI divided by 2 selected as PLL clock source
  *       @arg RCC_PLLSOURCE_PREDIV1: PREDIV1 clock selected as PLL clock source
  *   For @b other GD32_devices, this parameter can be one of the following values:
  *       @arg RCC_PLLSOURCE_HSI_DIV2: HSI divided by 2 selected as PLL clock source
  *       @arg RCC_PLLSOURCE_HSE_DIV1: HSE selected as PLL clock source
  *       @arg RCC_PLLSOURCE_HSE_DIV2: HSE divided by 2 selected as PLL clock source
  * @param  RCC_PLLMF: specify the PLL multiplication factor.
  *   For @b GD32_Connectivity_line_devices, this parameter can be RCC_PLLMUL_x where x:{[2,32], 6_5}
  *   For @b other_GD32_devices, this parameter can be RCC_PLLMUL_x where x:[2,32]
  * @retval None
  */
void RCC_PLLConfig(uint32_t RCC_PLLSelect, uint32_t RCC_PLLMF)
{
    uint32_t temp = 0;

    temp = RCC->GCFGR;
    /* Clear PLLSEL [16] and PLLMF[4:0] bits */
    temp &= ~(RCC_GCFGR_PLLMF | RCC_GCFGR_PLLSEL);
    /* Set the PLLSEL and PLLMF */
    temp |= RCC_PLLSelect | RCC_PLLMF;

    RCC->GCFGR = temp;
}

/**
  * @brief  Enable or disable the PLL.
  * @param  NewValue: new value of the PLL.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PLL_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        RCC->GCCR |= RCC_GCCR_PLLEN;
    } else {
        RCC->GCCR &= ~RCC_GCCR_PLLEN;
    }
}


#ifdef GD32F10X_CL
/**
  * @brief  Configure the PREDV1 division factor.
  * @param  RCC_PREDV1_Source: specifies the PREDV1 clock source.
  *   This parameter can be one of the following values:
  *   @arg RCC_PREDIV1_SOURCE_HSE: HSE selected as PREDIV1 clock
  *   @arg RCC_PREDIV1_SOURCE_PLL2: PLL2 selected as PREDIV1 clock
  * @param  RCC_PREDV1_DIV: specify the PREDV1 division factor.
  *   This parameter can be RCC_PREDIV1_DIVx where x:[1,16]
  * @retval None
  */
void RCC_PREDV1Config(uint32_t RCC_PREDV1_Source, uint32_t RCC_PREDV1_Div)
{
    uint32_t temp = 0;

    temp = RCC->GCFGR2;
    /* Clear PREDV1[3:0] and PREDV1SEL bits */
    temp &= ~(RCC_GCFGR2_PREDV1 | RCC_GCFGR2_PREDV1SEL);
    /* Set the PREDV1 division factor and PREDV1SEL */
    temp |= (RCC_PREDV1_Div | RCC_PREDV1_Source);

    RCC->GCFGR2 = temp;
}

/**
  * @brief  Configure the PREDV2 division factor.
  * @param  RCC_PREDV2_Div: specify the PREDV2 clock division factor.
  *   This parameter can be RCC_PREDIV2_DIVx where x:[1,16]
  * @retval None
  */
void RCC_PREDV2Config(uint32_t RCC_PREDV2_Div)
{
    uint32_t temp = 0;

    temp = RCC->GCFGR2;
    /* Clear PREDV2[3:0] bits */
    temp &= ~RCC_GCFGR2_PREDV2;
    /* Set the PREDV2 division factor */
    temp |= RCC_PREDV2_Div;

    RCC->GCFGR2 = temp;
}

/**
  * @brief  Configure the PLL2 multiplication factor.
  * @param  RCC_PLL2MF: specify the PLL2 multiplication factor.
  *   This parameter can be RCC_PLL2MUL_x where x:{[8,14], 16, 20}
  * @retval None
  */
void RCC_PLL2Config(uint32_t RCC_PLL2MF)
{
    uint32_t temp = 0;

    temp = RCC->GCFGR2;
    /* Clear PLL2MF[3:0] bits */
    temp &= ~RCC_GCFGR2_PLL2MF;
    /* Set the PLL2 configuration bits */
    temp |= RCC_PLL2MF;

    RCC->GCFGR2 = temp;
}


/**
  * @brief  Enable or disable the PLL2.
  * @param  NewValue: new value of the PLL2.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PLL2_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        RCC->GCCR |= RCC_GCCR_PLL2EN;
    } else {
        RCC->GCCR &= ~RCC_GCCR_PLL2EN;
    }
}


/**
  * @brief  Configure the PLL3 multiplication factor.
  * @param  RCC_PLL3MF: specify the PLL3 multiplication factor.
  *   This parameter can be RCC_PLL3MUL_x where x:{[8,14], 16, 20}
  * @retval None
  */
void RCC_PLL3Config(uint32_t RCC_PLL3MF)
{
    uint32_t temp = 0;

    temp = RCC->GCFGR2;
    /* Clear PLL2MF[3:0] bits */
    temp &= ~RCC_GCFGR2_PLL3MF;
    /* Set the PLL3 configuration bits */
    temp |= RCC_PLL3MF;

    RCC->GCFGR2 = temp;
}


/**
  * @brief  Enable or disable the PLL3.
  * @param  NewValue: new value of the PLL3.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PLL3_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        RCC->GCCR |= RCC_GCCR_PLL3EN;
    } else {
        RCC->GCCR &= ~RCC_GCCR_PLL3EN;
    }
}
#endif /* GD32F10X_CL */

/**
  * @brief  Configure the system clock (CK_SYS)
  * @param  RCC_SYSCLKSource: specify the system clock source
  *   This parameter can be one of the following values:
  *   @arg RCC_SYSCLKSOURCE_HSI:    selecte HSI as CK_SYS source
  *   @arg RCC_SYSCLKSOURCE_HSE:    selecte HSE as CK_SYS source
  *   @arg RCC_SYSCLKSOURCE_PLLCLK: selecte PLL as CK_SYS source
  * @retval None
  */
void RCC_CK_SYSConfig(uint32_t RCC_SYSCLKSource)
{
    uint32_t temp = 0;

    temp = RCC->GCFGR;

    /* Clear SCS[1:0] bits */
    temp &= ~RCC_GCFGR_SCS;

    /* Set SCS[1:0] bits according to RCC_SYSCLKSource value */
    temp |= RCC_SYSCLKSource;

    /* Store the new value */
    RCC->GCFGR = temp;
}

/**
  * @brief  Get the system clock source.
  * @param  None
  * @retval Get the system clock source. The returned value can be one
  *   of the following values:
  *   @arg 0x00: HSI used as CK_SYS source
  *   @arg 0x04: HSE used as CK_SYS source
  *   @arg 0x08: PLL used as CK_SYS source
  */
uint8_t RCC_GetCK_SYSSource(void)
{
    return ((uint8_t)(RCC->GCFGR & RCC_GCFGR_SCSS));
}
/**
  * @brief  Configure the AHB clock.
  * @param  RCC_CK_SYSDiv: specify the AHB clock divider. This clock is derived from
  *   the system clock (CK_SYS).
  *   This parameter can be one of the following values:
  *   @arg RCC_SYSCLK_DIV1:   AHB clock = CK_SYS
  *   @arg RCC_SYSCLK_DIV2:   AHB clock = CK_SYS/2
  *   @arg RCC_SYSCLK_DIV4:   AHB clock = CK_SYS/4
  *   @arg RCC_SYSCLK_DIV8:   AHB clock = CK_SYS/8
  *   @arg RCC_SYSCLK_DIV16:  AHB clock = CK_SYS/16
  *   @arg RCC_SYSCLK_DIV64:  AHB clock = CK_SYS/64
  *   @arg RCC_SYSCLK_DIV128: AHB clock = CK_SYS/128
  *   @arg RCC_SYSCLK_DIV256: AHB clock = CK_SYS/256
  *   @arg RCC_SYSCLK_DIV512: AHB clock = CK_SYS/512
  * @retval None
  */
void RCC_AHBConfig(uint32_t RCC_CK_SYSDiv)
{
    uint32_t temp = 0;

    temp = RCC->GCFGR;

    /* Clear AHBPS[3:0] bits */
    temp &= ~RCC_GCFGR_AHBPS;

    /* Set AHBPS[3:0] bits according to RCC_CK_SYSDiv value */
    temp |= RCC_CK_SYSDiv;

    /* Store the new value */
    RCC->GCFGR = temp;
}

/**
  * @brief  Configure the APB1 clock.
  * @param  RCC_APB1: specify the APB1 clock divider. This clock is derived from
  *         the AHB clock.
  *   This parameter can be one of the following values:
  *   @arg RCC_APB1AHB_DIV1: APB1 clock = AHB
  *   @arg RCC_APB1AHB_DIV2: APB1 clock = AHB/2
  *   @arg RCC_APB1AHB_DIV4: APB1 clock = AHB/4
  *   @arg RCC_APB1AHB_DIV8: APB1 clock = AHB/8
  *   @arg RCC_APB1AHB_DIV16: APB1 clock = AHB/16
  * @retval None
  */
void RCC_APB1Config(uint32_t RCC_APB1)
{
    uint32_t temp = 0;

    temp = RCC->GCFGR;

    /* Clear APB1PS[2:0] bits */
    temp &= ~RCC_GCFGR_APB1PS;

    /* Set APB1PS[2:0] bits according to RCC_APB1 value */
    temp |= RCC_APB1;

    /* Store the new value */
    RCC->GCFGR = temp;
}

/**
  * @brief  Configure the APB2 clock.
  * @param  RCC_APB2: specify the APB2 clock divider. This clock is derived from
  *         the AHB clock.
  *   This parameter can be one of the following values:
  *   @arg RCC_APB2AHB_DIV1: APB2 clock = AHB
  *   @arg RCC_APB2AHB_DIV2: APB2 clock = AHB/2
  *   @arg RCC_APB2AHB_DIV4: APB2 clock = AHB/4
  *   @arg RCC_APB2AHB_DIV8: APB2 clock = AHB/8
  *   @arg RCC_APB2AHB_DIV16: APB2 clock = AHB/16
  * @retval None
  */
void RCC_APB2Config(uint32_t RCC_APB2)
{
    uint32_t temp = 0;

    temp = RCC->GCFGR;

    /* Clear APB2PS[2:0] bits */
    temp &= ~RCC_GCFGR_APB2PS;

    /* Set APB2PS[2:0] bits according to RCC_APB2 value */
    temp |= RCC_APB2;

    /* Store the new value */
    RCC->GCFGR = temp;
}

#ifdef GD32F10X_CL
/**
  * @brief  Configure the USB_OTG clock (USB_OTG CLK).
  * @param  RCC_OTGFSCLK: specify the USB_OTG clock source. This clock is derived
  *         from the PLL.
  *   This parameter can be one of the following values:
  *   @arg RCC_OTGCLK_PLL_DIV1_5: USB_OTG clock = PLL/1.5
  *   @arg RCC_OTGCLK_PLL_DIV1:   USB_OTG clock = PLL
  *   @arg RCC_OTGCLK_PLL_DIV2:   USB_OTG clock = PLL/2
  *   @arg RCC_OTGCLK_PLL_DIV2_5: USB-OTG clock = PLL/2.5
  * @retval None
  */
void RCC_OTGFSCLKConfig(uint32_t RCC_OTGFSCLK)
{

    /* Clear OTGFSPS bit */
    RCC->GCFGR &= ~RCC_GCFGR_OTGFSPS;
    /* Set OTGFSPS bits according to RCC_OTGFSCLK value */
    RCC->GCFGR |= RCC_OTGFSCLK;

}

#else
/**
  * @brief  Configure the USB clock (USBCLK).
  * @param  RCC_USBCLK: specify the USB clock source. This clock is derived
  *         from the PLL.
  *   This parameter can be one of the following values:
  *   @arg RCC_USBCLK_PLL_DIV1_5: USB clock = PLL/1.5
  *   @arg RCC_USBCLK_PLL_DIV1:   USB clock = PLL
  *   @arg RCC_USBCLK_PLL_DIV2:   USB clock = PLL/2
  *   @arg RCC_USBCLK_PLL_DIV2_5: USB clock = PLL/2.5
  * @retval None
  */
void RCC_USBCLKConfig(uint32_t RCC_USBCLK)
{

    /* Clear USBPS bit */
    RCC->GCFGR &= ~RCC_GCFGR_USBPS;
    /* Set USBPS bits according to RCC_USBCLK value */
    RCC->GCFGR |= RCC_USBCLK;

}
#endif /* GD32F10X_CL */

/**
  * @brief  Configure the ADC clock (ADCCLK).
  * @param  RCC_ADCCLK: specify the ADC clock source. This clock is derived from APB2 clock.
  *   This parameter can be one of the following values:
  *   @arg RCC_ADCCLK_APB2_DIV2: ADC clock = APB2/2
  *   @arg RCC_ADCCLK_APB2_DIV4: ADC clock = APB2/4
  *   @arg RCC_ADCCLK_APB2_DIV6: ADC clock = APB2/6
  *   @arg RCC_ADCCLK_APB2_DIV8: ADC clock = APB2/8
  *   @arg RCC_ADCCLK_APB2_DIV12: ADC clock = APB2/12
  *   @arg RCC_ADCCLK_APB2_DIV16: ADC clock = APB2/16
  * @retval None
  */
void RCC_ADCCLKConfig(uint32_t RCC_ADCCLK)
{

    /* Clear ADCPS bit */
    RCC->GCFGR &= ~RCC_GCFGR_ADCPS;
    /* Set ADCPS bits according to RCC_APB2 value */
    RCC->GCFGR |= RCC_ADCCLK;
}

#ifdef GD32F10X_CL
/**
  * @brief  Configure the I2S2 clock source(I2S2CLK).
  * @param  RCC_I2S2CLK: specify the I2S2 clock source.
  *   This parameter can be one of the following values:
  *   @arg RCC_I2S2CLK_SYSCLK: system clock selected as I2S2 clock entry
  *   @arg RCC_I2S2CLK_PLL3: PLL3 clock selected as I2S2 clock entry
  * @note If the RCC_I2S2CLK_PLL3 selected, the I2S2 clock is (PLL3 x 2).
  * @retval None
  */
void RCC_I2S2CLKConfig(uint32_t RCC_I2S2CLK)
{
    /* Clear I2S2SEL bit */
    RCC->GCFGR2 &= ~RCC_GCFGR2_I2S2SEL;
    /* Set I2S2CLK bits according to RCC_I2S2CLK value */
    RCC->GCFGR2 |= RCC_I2S2CLK;

}

/**
  * @brief  Configure the I2S3 clock source(I2S3CLK).
  * @param  RCC_I2S3CLK: specify the I2S3 clock source.
  *   This parameter can be one of the following values:
  *   @arg RCC_I2S3CLK_SYSCLK: system clock selected as I2S3 clock entry
  *   @arg RCC_I2S3CLK_PLL3: PLL3 clock selected as I2S3 clock entry
  * @note If the RCC_I2S3CLK_PLL3 selected, the I2S3 clock is (PLL3 x 2).
  * @retval None
  */
void RCC_I2S3CLKConfig(uint32_t RCC_I2S3CLK)
{
    /* Clear I2S3SEL bit */
    RCC->GCFGR2 &= ~RCC_GCFGR2_I2S3SEL;
    /* Set I2S3CLK bits according to RCC_I2S3CLK value */
    RCC->GCFGR2 |= RCC_I2S3CLK;
}
#endif /* GD32F10X_CL */

/**
  * @brief  Configure the External Low Speed oscillator (LSE).
  * @param  RCC_LSE: specify the new state of the LSE.
  *  This parameter can be one of the following values:
  *  @arg RCC_LSE_OFF: turn off the LSE
  *  @arg RCC_LSE_EN: turn on the LSE
  *  @arg RCC_LSE_BYPASS: LSE bypassed with external clock
  * @retval None
  */
void RCC_LSEConfig(uint32_t RCC_LSE)
{

    /* Reset LSEEN and LSEBPS bits before configuring the LSE */
    RCC->BDCR &= ~(RCC_BDCR_LSEEN);
    RCC->BDCR &= ~(RCC_BDCR_LSEBPS);

    /* Configure LSE */
    RCC->BDCR |= RCC_LSE;
}


/**
  * @brief  Enable or disable the Internal Low Speed oscillator (LSI).
  * @param  NewValue: new value of the LSI.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_LSI_Enable(TypeState NewValue)
{

    if (NewValue != DISABLE) {
        RCC->GCSR |= RCC_GCSR_LSIEN;
    } else {
        RCC->GCSR &= ~RCC_GCSR_LSIEN;
    }
}

/**
  * @brief  Configure the RTC clock (RTCCLK).
  * @param  RCC_RTCCLKSource: specify the RTC clock source.
  *   This parameter can be one of the following values:
  *   @arg RCC_RTCCLKSOURCE_LSE: selecte LSE as RTC clock
  *   @arg RCC_RTCCLKSOURCE_LSI: selecte LSI as RTC clock
  *   @arg RCC_RTCCLKSOURCE_HSE_DIV128: selecte HSE divided by 128 as RTC clock
  * @note   if using HSE as RTC source, the maximum clock frequency for RTC is 2 MHz.
  * @retval None
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
    /* Clear RTCSEL bit */
    RCC->BDCR &= ~RCC_BDCR_RTCSEL;
    /* Select the RTC clock source */
    RCC->BDCR |= RCC_RTCCLKSource;
}

/**
  * @brief  Enable or disable the RTC clock.
  * @param  NewValue: new state of the RTC clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCCLK_Enable(TypeState NewValue)
{

    if (NewValue != DISABLE) {
        RCC->BDCR |= RCC_BDCR_RTCEN;
    } else {
        RCC->BDCR &= ~RCC_BDCR_RTCEN;
    }
}

/**
  * @brief  Get the frequencies of the CK_SYS, AHB, APB1, APB2, ADC clocks.
  * @retval None
  */
void RCC_GetClocksFreq(RCC_ClocksPara *RCC_Clocks)
{
    uint32_t temp = 0, pllmf = 0, pllmf4 = 0, pllselect = 0, presc = 0;

#ifdef  GD32F10X_CL
    uint32_t prediv1select = 0, prediv1factor = 0, prediv2factor = 0, pll2mf = 0;
#endif /* GD32F10X_CL */


    /* Get CK_SYS source */
    temp = RCC->GCFGR & RCC_GCFGR_SCSS;

    switch (temp) {
    case 0x00:  /* HSI used as CK_SYS */
        RCC_Clocks->CK_SYS_Frequency = HSI_VALUE;
        break;
    case 0x04:  /* HSE used as CK_SYS */
        RCC_Clocks->CK_SYS_Frequency = HSE_VALUE;
        break;
    case 0x08:  /* PLL used as CK_SYS */
#ifdef  GD32F10X_CL
        /* Get PLL clock source and multiplication factor */
        /* Get PLLMF[3:0] */
        pllmf = RCC->GCFGR & RCC_GCFGR_PLLMF_3_0;
        /* Get PLLMF[4] */
        pllmf4 = RCC->GCFGR & RCC_GCFGR_PLLMF_4;

        pllmf4 = ((pllmf4 >> 29) * 16);

        pllmf = (pllmf >> 18) + pllmf4;
        if (pllmf == 0x0D) {
            /* PLL multiplication factor = PLL input clock * 6.5*/
            /* Beacause of the float number 6.5, pllmf * 2 to remove the float number  */
            pllmf = 13 * 2 / 2;

        } else if (pllmf >= 0x0F) {
            pllmf += 1;
            /* Here is consistent with the above that pllmf * 2 to remove the float number*/
            pllmf = pllmf * 2;
        } else {
            pllmf += 2;
            /* Here is consistent with the above that pllmf * 2 to remove the float number*/
            pllmf = pllmf * 2;
        }

        pllselect = RCC->GCFGR & RCC_GCFGR_PLLSEL;
        if (pllselect == 0x00) {
            /* HSI clock divided by 2 selected as PLL clock source */
            /* Here is consistent with the above that pllmf / 2 */
            RCC_Clocks->CK_SYS_Frequency = (HSI_VALUE >> HSI_CLOCK_DIVIDED_2) * pllmf / 2;
        } else {
            /* PREDIV1 selected as PLL clock entry */

            /* Get PREDIV1 clock source and division factor */
            prediv1select = RCC->GCFGR2 & RCC_GCFGR2_PREDV1SEL;
            prediv1factor = (RCC->GCFGR2 & RCC_GCFGR2_PREDV1) + 1;

            if (prediv1select == 0) {
                /* HSE clock selected as PREDIV1 clock entry */
                /* Here is consistent with the above that pllmf / 2 */
                RCC_Clocks->CK_SYS_Frequency = (HSE_VALUE / prediv1factor) * pllmf / 2;
            } else {
                /* PLL2 clock selected as PREDIV1 clock entry */
                /* Get PREDIV2 division factor and PLL2 multiplication factor */
                prediv2factor = ((RCC->GCFGR2 & RCC_GCFGR2_PREDV2) >> 4) + 1;
                pll2mf = ((RCC->GCFGR2 & RCC_GCFGR2_PLL2MF) >> 8);
                if (pll2mf != 15) {
                    pll2mf += 2;
                } else {
                    pll2mf += 5;
                }
                /* Here is consistent with the above that pllmf / 2 */
                RCC_Clocks->CK_SYS_Frequency = (((HSE_VALUE / prediv2factor) * pll2mf) / prediv1factor) * pllmf / 2;
            }
        }
#else
        /* Get PLL clock source and multiplication factor */
        /* Get PLLMF[3:0] */
        pllmf = RCC->GCFGR & RCC_GCFGR_PLLMF_3_0;
        /* Get PLLMF[4] */
        pllmf4 = RCC->GCFGR & RCC_GCFGR_PLLMF_4;

        pllmf4 = ((pllmf4 >> 27) * 16);
        pllmf = (pllmf >> 18) + pllmf4;
        if (pllmf >= 0x0F)
            pllmf += 1;
        else
            pllmf += 2;

        pllselect = RCC->GCFGR & RCC_GCFGR_PLLSEL;
        if (pllselect == 0x00) {
            /* HSI clock divided by 2 selected as PLL clock source */
            RCC_Clocks->CK_SYS_Frequency = (HSI_VALUE >> HSI_CLOCK_DIVIDED_2) * pllmf;
        } else {
            if ((RCC->GCFGR & RCC_GCFGR_PLLPREDV) != (uint32_t)RESET) {
                /* HSE clock divided by 2 */
                RCC_Clocks->CK_SYS_Frequency = (HSE_VALUE >> HSE_CLOCK_DIVIDED_2) * pllmf;
            } else {
                RCC_Clocks->CK_SYS_Frequency = HSE_VALUE * pllmf;
            }
        }
#endif/* GD32F10X_CL */
        break;
    default: /* HSI used as system clock */
        RCC_Clocks->CK_SYS_Frequency = HSI_VALUE;
        break;
    }

    /* Get AHB prescaler */
    temp = RCC->GCFGR & RCC_GCFGR_AHBPS;
    temp = temp >> 4;
    presc = AHBPrescTable[temp];
    /* Get AHB clock frequency */
    RCC_Clocks->AHB_Frequency = RCC_Clocks->CK_SYS_Frequency >> presc;

    /* Get APB1 prescaler */
    temp = RCC->GCFGR & RCC_GCFGR_APB1PS;
    temp = temp >> 8;
    presc = APBPrescTable[temp];
    /* Get APB1 clock frequency */
    RCC_Clocks->APB1_Frequency = RCC_Clocks->AHB_Frequency >> presc;

    /* Get APB2 prescaler */
    temp = RCC->GCFGR & RCC_GCFGR_APB2PS;
    temp = temp >> 11;
    presc = APBPrescTable[temp];
    /* Get APB2 clock frequency */
    RCC_Clocks->APB2_Frequency = RCC_Clocks->AHB_Frequency >> presc;

    /* Get ADCCLK clock frequency */
    temp = ((RCC->GCFGR & RCC_GCFGR_ADCPS_2) >> 26);
    temp += ((RCC->GCFGR & (RCC_GCFGR_ADCPS_0 | RCC_GCFGR_ADCPS_1)) >> 14);
    switch (temp) {
    case 0x00: /* ADC Clock is derived from APB2/2 */
        RCC_Clocks->ADCCLK_Frequency = (RCC_Clocks->APB2_Frequency / 2);
        break;
    case 0x01: /* ADC Clock is derived from APB2/4 */
        RCC_Clocks->ADCCLK_Frequency = (RCC_Clocks->APB2_Frequency / 4);
        break;
    case 0x02: /* ADC Clock is derived from APB2/6 */
        RCC_Clocks->ADCCLK_Frequency = (RCC_Clocks->APB2_Frequency / 6);
        break;
    case 0x03: /* ADC Clock is derived from APB2/8 */
        RCC_Clocks->ADCCLK_Frequency = (RCC_Clocks->APB2_Frequency / 8);
        break;
    case 0x04: /* ADC Clock is derived from APB2/2 */
        RCC_Clocks->ADCCLK_Frequency = (RCC_Clocks->APB2_Frequency / 2);
        break;
    case 0x05: /* ADC Clock is derived from APB2/12 */
        RCC_Clocks->ADCCLK_Frequency = (RCC_Clocks->APB2_Frequency / 12);
        break;
    case 0x06: /* ADC Clock is derived from APB2/8 */
        RCC_Clocks->ADCCLK_Frequency = (RCC_Clocks->APB2_Frequency / 8);
        break;
    case 0x07: /* ADC Clock is derived from APB2/16 */
        RCC_Clocks->ADCCLK_Frequency = (RCC_Clocks->APB2_Frequency / 16);
        break;
    default:
        break;
    }
}

/**
  * @brief  Enable or disable the AHB peripheral clock.
  * @param  RCC_AHBPeriph: specify the AHB peripheral clock.
  *   For @b GD32_Connectivity_line_devices,
  *   this parameter can be any combination of the following values:
  *   @arg RCC_AHBPERIPH_DMA1
  *   @arg RCC_AHBPERIPH_DMA2
  *   @arg RCC_AHBPERIPH_SRAM
  *   @arg RCC_AHBPERIPH_FMC
  *   @arg RCC_AHBPERIPH_CRC
  *   @arg RCC_AHBPERIPH_EXMC
  *   @arg RCC_AHBPERIPH_OTG_FS
  *   @arg RCC_AHBPERIPH_ETH_MAC
  *   @arg RCC_AHBPERIPH_ETH_MAC_RX
  *   @arg RCC_AHBPERIPH_ETH_MAC_TX
  *
  *   For @b other_GD32_devices, this parameter can be any combination of the
  *   following values:
  *   @arg RCC_AHBPERIPH_DMA1
  *   @arg RCC_AHBPERIPH_DMA2
  *   @arg RCC_AHBPERIPH_SRAM
  *   @arg RCC_AHBPERIPH_FMC
  *   @arg RCC_AHBPERIPH_CRC
  *   @arg RCC_AHBPERIPH_EXMC
  *   @arg RCC_AHBPERIPH_SDIO
  * @param  NewValue: new state of the peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClock_Enable(uint32_t RCC_AHBPeriph, TypeState NewValue)
{

    if (NewValue != DISABLE) {
        RCC->AHBCCR |= RCC_AHBPeriph;
    } else {
        RCC->AHBCCR &= ~RCC_AHBPeriph;
    }
}

/**
  * @brief  Enable or disable the APB2 peripheral clock.
  * @param  RCC_APB2Periph: specify the APB2 peripheral clock.
  *   This parameter can be any combination of the following values:
  *   @arg RCC_APB2PERIPH_AF
  *   @arg RCC_APB2PERIPH_GPIOA
  *   @arg RCC_APB2PERIPH_GPIOB
  *   @arg RCC_APB2PERIPH_GPIOC
  *   @arg RCC_APB2PERIPH_GPIOD
  *   @arg RCC_APB2PERIPH_GPIOE
  *   @arg RCC_APB2PERIPH_GPIOF
  *   @arg RCC_APB2PERIPH_GPIOG
  *   @arg RCC_APB2PERIPH_ADC1
  *   @arg RCC_APB2PERIPH_ADC2
  *   @arg RCC_APB2PERIPH_TIMER1
  *   @arg RCC_APB2PERIPH_SPI1
  *   @arg RCC_APB2PERIPH_TIMER8
  *   @arg RCC_APB2PERIPH_USART1
  *   @arg RCC_APB2PERIPH_ADC3
  *   @arg RCC_APB2PERIPH_TIMER9
  *   @arg RCC_APB2PERIPH_TIMER10
  *   @arg RCC_APB2PERIPH_TIMER11
  * @param  NewValue: new state of the peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphClock_Enable(uint32_t RCC_APB2Periph, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        RCC->APB2CCR |= RCC_APB2Periph;
    } else {
        RCC->APB2CCR &= ~RCC_APB2Periph;
    }
}

/**
  * @brief  Enable or disable the APB1 peripheral clock.
  * @param  RCC_APB1Periph: specify the APB1 peripheral clock.
  *   This parameter can be any combination of the following values:
  *   @arg RCC_APB1PERIPH_TIMER2
  *   @arg RCC_APB1PERIPH_TIMER3
  *   @arg RCC_APB1PERIPH_TIMER4
  *   @arg RCC_APB1PERIPH_TIMER5
  *   @arg RCC_APB1PERIPH_TIMER6
  *   @arg RCC_APB1PERIPH_TIMER7
  *   @arg RCC_APB1PERIPH_TIMER12
  *   @arg RCC_APB1PERIPH_TIMER13
  *   @arg RCC_APB1PERIPH_TIMER14
  *   @arg RCC_APB1PERIPH_WWDG
  *   @arg RCC_APB1PERIPH_SPI2
  *   @arg RCC_APB1PERIPH_SPI3,
  *   @arg RCC_APB1PERIPH_USART2
  *   @arg RCC_APB1PERIPH_USART3
  *   @arg RCC_APB1PERIPH_UART4
  *   @arg RCC_APB1PERIPH_UART5
  *   @arg RCC_APB1PERIPH_I2C1
  *   @arg RCC_APB1PERIPH_I2C2
  *   @arg RCC_APB1PERIPH_USB
  *   @arg RCC_APB1PERIPH_CAN1
  *   @arg RCC_APB1PERIPH_CAN2
  *   @arg RCC_APB1PERIPH_BKP
  *   @arg RCC_APB1PERIPH_PWR
  *   @arg RCC_APB1PERIPH_DAC
  * @param  NewState: new state of the specified peripheral clock.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClock_Enable(uint32_t RCC_APB1Periph, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        RCC->APB1CCR |= RCC_APB1Periph;
    } else {
        RCC->APB1CCR &= ~RCC_APB1Periph;
    }
}

#ifdef GD32F10X_CL
/**
  * @brief  Force or release AHB peripheral reset.
  * @param  RCC_AHBPeriphRST: specify the AHB peripheral to reset.
  *   This parameter can be any combination of the following values:
  *   @arg RCC_AHBPeriph_OTGFSRST
  *   @arg RCC_AHBPeriph_ETHMACRST
  * @param  NewState: new state of the specified peripheral reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphReset_Enable(uint32_t RCC_AHBPeriphRST, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        RCC->AHBRCR |= RCC_AHBPeriphRST;
    } else {
        RCC->AHBRCR &= ~RCC_AHBPeriphRST;
    }
}
#endif /* GD32F10X_CL */

/**
  * @brief  Force or release APB2 peripheral reset.
  * @param  RCC_APB2PeriphRST: specify the APB2 peripheral to reset.
  *   This parameter can be any combination of the following values:
  *   @arg RCC_APB2PERIPH_AFRST
  *   @arg RCC_APB2PERIPH_GPIOARST
  *   @arg RCC_APB2PERIPH_GPIOBRST
  *   @arg RCC_APB2PERIPH_GPIOCRST
  *   @arg RCC_APB2PERIPH_GPIODRST
  *   @arg RCC_APB2PERIPH_GPIOERST
  *   @arg RCC_APB2PERIPH_GPIOFRST
  *   @arg RCC_APB2PERIPH_GPIOGRST
  *   @arg RCC_APB2PERIPH_ADC1RST
  *   @arg RCC_APB2PERIPH_ADC2RST
  *   @arg RCC_APB2PERIPH_TIMER1RST
  *   @arg RCC_APB2PERIPH_SPI1RST
  *   @arg RCC_APB2PERIPH_TIMER8RST
  *   @arg RCC_APB2PERIPH_USART1RST
  *   @arg RCC_APB2PERIPH_ADC3RST
  *   @arg RCC_APB2PERIPH_TIMER9RST
  *   @arg RCC_APB2PERIPH_TIMER10RST
  *   @arg RCC_APB2PERIPH_TIMER11RST
  * @param  NewValue: new state of the peripheral reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphReset_Enable(uint32_t RCC_APB2PeriphRST, TypeState NewValue)
{

    if (NewValue != DISABLE) {
        RCC->APB2RCR |= RCC_APB2PeriphRST;
    } else {
        RCC->APB2RCR &= ~RCC_APB2PeriphRST;
    }
}


/**
  * @brief  Force or release APB1 peripheral reset.
  * @param  RCC_APB1PeriphRST: specify the APB1 peripheral to reset.
  *   This parameter can be any combination of the following values:
  *   @arg RCC_APB1PERIPH_TIMER2RST
  *   @arg RCC_APB1PERIPH_TIMER3RST
  *   @arg RCC_APB1PERIPH_TIMER4RST
  *   @arg RCC_APB1PERIPH_TIMER5RST
  *   @arg RCC_APB1PERIPH_TIMER6RST
  *   @arg RCC_APB1PERIPH_TIMER7RST
  *   @arg RCC_APB1PERIPH_TIMER12RST
  *   @arg RCC_APB1PERIPH_TIMER13RST
  *   @arg RCC_APB1PERIPH_TIMER14RST
  *   @arg RCC_APB1PERIPH_WWDGRST
  *   @arg RCC_APB1PERIPH_SPI2RST
  *   @arg RCC_APB1PERIPH_SPI3RST
  *   @arg RCC_APB1PERIPH_USART2RST
  *   @arg RCC_APB1PERIPH_USART3RST
  *   @arg RCC_APB1PERIPH_UART4RST
  *   @arg RCC_APB1PERIPH_UART5RST
  *   @arg RCC_APB1PERIPH_I2C1RST
  *   @arg RCC_APB1PERIPH_I2C2RST
  *   @arg RCC_APB1PERIPH_USBRST
  *   @arg RCC_APB1PERIPH_CAN1RST
  *   @arg RCC_APB1PERIPH_CAN2RST
  *   @arg RCC_APB1PERIPH_BKPRST
  *   @arg RCC_APB1PERIPH_PWRRST
  *   @arg RCC_APB1PERIPH_DACRST
  * @param  NewValue: new state of the peripheral clock (ENABLE or DISABLE).
  * @retval None
  */
void RCC_APB1PeriphReset_Enable(uint32_t RCC_APB1PeriphRST, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        RCC->APB1RCR |= RCC_APB1PeriphRST;
    } else {
        RCC->APB1RCR &= ~RCC_APB1PeriphRST;
    }
}

/**
  * @brief  Force or release the Backup domain reset.
  * @param  NewValue: new state of the Backup domain reset (ENABLE or DISABLE).
  * @retval None
  */
void RCC_BackupReset_Enable(TypeState NewValue)
{

    if (NewValue != DISABLE) {
        RCC->BDCR |= RCC_BDCR_BKPRST;
    } else {
        RCC->BDCR &= ~RCC_BDCR_BKPRST;
    }
}

/**
  * @brief  Enable or disable the Clock Security System.
  * @param  NewValue: new value of the Clock Security System.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_HSEClockMonitor_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        RCC->GCCR |= RCC_GCCR_CKMEN;
    } else {
        RCC->GCCR &= ~RCC_GCCR_CKMEN;
    }
}

/**
  * @brief  Select the clock source to output on CKOUTSRC and the corresponding prescaler.
  * @param  RCC_CKOUTSRC: specify the clock source to output.
  *   For @b GD32_Connectivity_line_devices, this parameter can be one of the
  *   following values:
  *   @arg RCC_CKOUTSRC_NOCLOCK: No clock selected
  *   @arg RCC_CKOUTSRC_SYSCLK: System clock selected
  *   @arg RCC_CKOUTSRC_HSI: HSI oscillator clock selected
  *   @arg RCC_CKOUTSRC_HSE: HSE oscillator clock selected
  *   @arg RCC_CKOUTSRC_PLL2CLK: PLL2 clock selected
  *   @arg RCC_CKOUTSRC_PLLCLK_DIV2: PLL clock divided by 2 selected
  *   @arg RCC_CKOUTSRC_PLL3CLK: PLL3 clock selected
  *   @arg RCC_CKOUTSRC_PLL3CLK_DIV2: PLL3 clock divided by 2 selected
  *   @arg RCC_CKOUTSRC_EXT1: External 3-25 MHz oscillator clock selected
  *   For  @b other_GD32_devices, this parameter can be one of the following values:
  *   @arg RCC_CKOUTSRC_NOCLOCK: No clock selected
  *   @arg RCC_CKOUTSRC_SYSCLK: System clock selected
  *   @arg RCC_CKOUTSRC_HSI: HSI oscillator clock selected
  *   @arg RCC_CKOUTSRC_HSE: HSE oscillator clock selected
  *   @arg RCC_CKOUTSRC_PLLCLK_DIV2: PLL clock divided by 2 selected
  * @retval None
  */

void RCC_CKOUTSRCConfig(uint32_t RCC_CKOUTSRC)
{
    uint32_t temp = 0;

    temp = RCC->GCFGR;
    /* Clear CKOUTSRC[2:0] bits */
    temp &= ~(RCC_GCFGR_CKOUTSEL);
    /* Set the RCC_CKOUTSRC */
    temp |= RCC_CKOUTSRC;
    /* Store the new value */
    RCC->GCFGR = temp;
}


/**
  * @brief  Enable or disable RCC interrupts.
  * @param  RCC_INT: specify the RCC interrupt sources.
  *   For @b GD32_Connectivity_line_devices, this parameter can be any combination
  *   of the following values
  *   @arg RCC_INT_LSISTB: LSI ready interrupt
  *   @arg RCC_INT_LSESTB LSE ready interrupt
  *   @arg RCC_INT_HSISTB: HSI ready interrupt
  *   @arg RCC_INT_HSESTB: HSE ready interrupt
  *   @arg RCC_INT_PLLSTB: PLL ready interrupt
  *   @arg RCC_INT_PLL2STB: PLL2 ready interrupt
  *   @arg RCC_INT_PLL3STB: PLL3 ready interrupt
  *
  *   For @b other_GD32_devices, this parameter can be any combination of the
  *   following values
  *   @arg RCC_INT_LSISTB: LSI ready interrupt
  *   @arg RCC_INT_LSESTB: LSE ready interrupt
  *   @arg RCC_INT_HSISTB: HSI ready interrupt
  *   @arg RCC_INT_HSESTB: HSE ready interrupt
  *   @arg RCC_INT_PLLSTB: PLL ready interrupt
  * @param  NewValue: new state of the RCC interrupts (ENABLE or DISABLE).
  * @retval None
  */
void RCC_INTConfig(uint8_t RCC_INT, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Perform Byte access to RCC_GCIR[14:8] bits to enable the selected interrupts */
        *(__IO uint8_t *) GCIR_BYTE1_ADDRESS |= RCC_INT;
    } else {
        /* Perform Byte access to RCC_GCIR bits to disable the selected interrupts */
        *(__IO uint8_t *) GCIR_BYTE1_ADDRESS &= (uint8_t)~RCC_INT;
    }
}


/**
  * @brief  Check whether the specified RCC flag is set or not.
  * @param  RCC_FLAG: specify the flag to check.
  *   For @b GD32_Connectivity_line_devices, this parameter can be one of the
  *   following values:
  *   @arg RCC_FLAG_HSISTB: HSI clock ready
  *   @arg RCC_FLAG_HSESTB: HSE clock ready
  *   @arg RCC_FLAG_PLLSTB: PLL clock ready
  *   @arg RCC_FLAG_PLL2STB: PLL2 clock ready
  *   @arg RCC_FLAG_PLL3STB: PLL3 clock ready
  *   @arg RCC_FLAG_LSESTB: LSE clock ready
  *   @arg RCC_FLAG_LSISTB: LSI clock ready
  *   @arg RCC_FLAG_EPRST: Pin reset
  *   @arg RCC_FLAG_POPDRST: POR/PDR reset
  *   @arg RCC_FLAG_SWRRST: Software reset
  *   @arg RCC_FLAG_IWDGRST: Independent Watchdog reset
  *   @arg RCC_FLAG_WWDGRST: Window Watchdog reset
  *   @arg RCC_FLAG_LPRRST: Low Power reset
  *   For @b other_GD32_devices, this parameter can be one of the following values:
  *   @arg RCC_FLAG_HSISTB: HSI oscillator clock ready
  *   @arg RCC_FLAG_HSESTB: HSE oscillator clock ready
  *   @arg RCC_FLAG_PLLSTB: PLL clock ready
  *   @arg RCC_FLAG_LSESTB: LSE oscillator clock ready
  *   @arg RCC_FLAG_LSISTB: LSI oscillator clock ready
  *   @arg RCC_FLAG_EPRST: Pin reset
  *   @arg RCC_FLAG_POPDRST: POR/PDR reset
  *   @arg RCC_FLAG_SWRRST: Software reset
  *   @arg RCC_FLAG_IWDGRST: Independent Watchdog reset
  *   @arg RCC_FLAG_WWDGRST: Window Watchdog reset
  *   @arg RCC_FLAG_LPRRST: Low Power reset
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
TypeState RCC_GetBitState(uint8_t RCC_FLAG)
{
    uint32_t temp = 0;
    uint32_t statusreg = 0;

    /* Get the RCC register index */
    temp = RCC_FLAG >> 5;

    /* The flag to check is in GCCR register */
    if (temp == 1) {
        statusreg = RCC->GCCR;
    }

    /* The flag to check is in BDCR register */
    else if (temp == 2) {
        statusreg = RCC->BDCR;
    }

    /* The flag to check is in GCSR register */
    else {
        statusreg = RCC->GCSR;
    }

    /* Get the flag position */
    temp = RCC_FLAG & FLAG_MASK;
    if ((statusreg & ((uint32_t)(1 << temp))) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }

}

/**
  * @brief  Clear the RCC all reset flags.
  * @param  None
  * @retval None
  */
void RCC_ClearBitState(void)
{
    /* Set RSTFC bit to clear all reset flags */
    RCC->GCSR |= RCC_GCSR_RSTFC;
}


/**
  * @brief  Check whether the RCC interrupt has occurred or not.
  * @param  RCC_INT: specify the RCC interrupt source to check.
  *   For @b GD32_Connectivity_line_devices, this parameter can be one of the
  *   following values:
  *   @arg RCC_INT_LSISTB: the flag of LSI ready interrupt
  *   @arg RCC_INT_LSESTB: the flag of LSE ready interrupt
  *   @arg RCC_INT_HSISTB: the flag of HSI ready interrupt
  *   @arg RCC_INT_HSESTB: the flag of HSE ready interrupt
  *   @arg RCC_INT_PLLSTB: the flag of PLL ready interrupt
  *   @arg RCC_INT_PLL2STB: the flag of PLL2 ready interrupt
  *   @arg RCC_INT_PLL3STB: the flag of PLL3 ready interrupt
  *   @arg RCC_INT_CKM: the flag of Clock Security System interrupt
  *   For @b other_GD32_devices, this parameter can be one of the following values:
  *   @arg RCC_INT_LSISTB: the flag of LSI ready interrupt
  *   @arg RCC_INT_LSESTB: the flag of LSE ready interrupt
  *   @arg RCC_INT_HSISTB: the flag of HSI ready interrupt
  *   @arg RCC_INT_HSESTB: the flag of HSE ready interrupt
  *   @arg RCC_INT_PLLSTB: the flag of PLL ready interrupt
  *   @arg RCC_INT_CKM: the flag of Clock Security System interrupt
  * @retval The new state of RCC_INT (SET or RESET).
  */
TypeState RCC_GetIntBitState(uint8_t RCC_INT)
{
    /* Check the status of the RCC interrupt */
    if ((RCC->GCIR & RCC_INT) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}
/**
  * @brief  Clear the RCC interrupt bits.
  * @param  RCC_INT: specify the interrupt bit to clear.
  *   For @b GD32_Connectivity_line_devices, this parameter can be any combination
  *   of the following values:
  *   @arg RCC_INT_LSISTB: LSI ready interrupt
  *   @arg RCC_INT_LSESTB LSE ready interrupt
  *   @arg RCC_INT_HSISTB: HSI ready interrupt
  *   @arg RCC_INT_HSESTB: HSE ready interrupt
  *   @arg RCC_INT_PLLSTB: PLL ready interrupt
  *   @arg RCC_INT_PLL2STB: PLL2 ready interrupt
  *   @arg RCC_INT_PLL3STB: PLL3 ready interrupt
  *   @arg RCC_INT_CKM: Clock Security System interrupt
  *   For @b other_GD32_devices, this parameter can be any combination of the
  *   following values
  *   @arg RCC_INT_LSISTB: LSI ready interrupt
  *   @arg RCC_INT_LSESTB: LSE ready interrupt
  *   @arg RCC_INT_HSISTB: HSI ready interrupt
  *   @arg RCC_INT_HSESTB: HSE ready interrupt
  *   @arg RCC_INT_PLLSTB: PLL ready interrupt
  *   @arg RCC_INT_CKM: Clock Security System interrupt
  * @retval None
  */

void RCC_ClearIntBitState(uint8_t RCC_INT)
{


    /* Perform RCC_GCIR[23:16] bits to clear the selected interrupt bits */
    *(__IO uint8_t *) GCIR_BYTE2_ADDRESS = RCC_INT;
}

/**
  * @brief  Configure the kernel voltage in Deep-sleep mode.
  * @note   Only unlock the power,this configuration is effective.
  * @param  RCC_KERNEL_VOL: specify the kernel voltage.
  *   This parameter can be one of the following values:
  *   @arg RCC_KERNEL_VOL1_2: The kernel voltage in Deep-sleep mode is 1.2V
  *   @arg RCC_KERNEL_VOL1_1: The kernel voltage in Deep-sleep mode is 1.1V
  *   @arg RCC_KERNEL_VOL1_0: The kernel voltage in Deep-sleep mode is 1.0V
  *   @arg RCC_KERNEL_VOL0_9: The kernel voltage in Deep-sleep mode is 0.9V
  * @retval None
  */
void RCC_KERNELVOLConfig(uint32_t RCC_KERNEL_VOL)
{
    /* Clear DEEPSLEEP_VC bit */
    RCC->RCC_DEEPSLEEP_VC &= ~RCC_DEEPSLEEP_VC_CLEAR;
    /* Set DEEPSLEEP_VC bits according to RCC_KERNEL_VOL value */
    RCC->RCC_DEEPSLEEP_VC |= RCC_KERNEL_VOL;
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



