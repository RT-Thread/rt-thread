/**
  ******************************************************************************
  * @file               ft32f4xx_rcc.c
  * @author             Rwang
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Reset and clock control (RCC) peripheral:
  *                     + Internal/external clocks, PLL, CSS and MCO configuration
  *                     + System, AHB and APB busses clocks configuration
  *                 + Peripheral clocks configuration
  *                 + Interrupts and flags management
  * @version            V1.0.0
  * @data                   2025-03-28
    ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_rcc.h"


/* ---------------------- RCC registers mask -------------------------------- */
/* RCC Flag Mask */
#define FLAG_MASK                 ((uint8_t)0x1F)

/* CR register byte 2 (Bits[23:16]) base address */
#define CR_BYTE2_ADDRESS          ((uint32_t)0x40023802)

/* CFGR register byte 3 (Bits[31:24]) base address */
#define CFGR_BYTE3_ADDRESS        ((uint32_t)0x4002380F)

/* CIR register byte 1 (Bits[15:8]) base address */
#define CIR_BYTE1_ADDRESS         ((uint32_t)0x40023811)

/* CIR register byte 2 (Bits[23:16]) base address */
#define CIR_BYTE2_ADDRESS         ((uint32_t)0x40023812)

static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  * @note      HSI ON and used as system clock source
  * @note      HSI48, HSE and PLL OFF
  * @note      AHB, APB prescaler set to 1.
  * @note      CSS and MCO OFF
  * @note      All interrupts disabled
  * @note   However, this function doesn't modify the configuration of the
  * @note      Peripheral clocks LSI, LSE and RTC clocks
  * @param  None
  * @retval None
  */
void RCC_DeInit(void)
{
    /* Set HSION bit */
    RCC->CR |= (uint32_t)0x00000001;

    /* Reset SW[1:0], HPRE[3:0], PPRE1[2:0], PPRE2[2:0], MCOSEL[2:0], MCOPRE[2:0] bits */
    RCC->CFGR &= (uint32_t)0x80FFC00C;

    /* Reset HSEON, CSSON, PLLON and PLL2ON bits */
    RCC->CR &= (uint32_t)0xFAF6FFFF;

    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    /* Reset PLLR[2:0], PLLREN, PLLQ[3:0], PLLQEN, PLLP[2:0], PLLPEN, PLLSRC, PLLN[7:0], and PLLM[4:0] bits */
    RCC->PLLCFGR &= (uint32_t)0xE0008020;

    /* Reset PLL2R[2:0], PLL2REN, PLL2Q[3:0], PLL2QEN, PLL2SRC, PLL2N[7:0], and PLL2M[4:0] bits */
    RCC->PLL2CFGR &= (uint32_t)0xE00F8020;

    /* Reset QSPISEL[1:0], ADC123SEL[1:0], CANSEL[3:0], LPTIMSEL[1:0],
     * I2C3SEL[1:0], I2C2SEL[1:0], I2C1SEL[1:0], LPUARTSEL RNGDIV[1:0],
     * CLK48SEL, PWMSEL[1:0], EQEPSEL[1:0], ECAPSEL[1:0], and I2SSEL bits */
    RCC->CCIPR &= (uint32_t)0x00F00400;

    /* Reset HSI48ON bit */
    RCC->CR2 &= (uint32_t)0xFFFEFFFF;

    /* Reset RAMSEL */
    RCC->RAMCTL &= (uint32_t)0xFFFFFFC0;

    /* Disable all interrupts */
    RCC->CIR = 0x00000000;
}

/**
  * @brief  Configures the External High Speed oscillator (HSE).
  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
  *         software should wait on HSERDY flag to be set indicating that HSE clock
  *         is stable and can be used to clock the PLL and/or system clock.
  * @note   HSE state can not be changed if it is used directly or through the
  *         PLL as system clock. In this case, you have to select another source
  *         of the system clock then change the HSE state (ex. disable it).
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @param  RCC_HSE: specifies the new state of the HSE.
  *          This parameter can be one of the following values:
  *            @arg RCC_HSE_OFF: turn OFF the HSE oscillator, HSERDY flag goes low after
  *                              6 HSE oscillator clock cycles.
  *            @arg RCC_HSE_ON: turn ON the HSE oscillator, HSERDY flag gose high after
  *                              512 HSE oscillator clock cycles.
  *            @arg RCC_HSE_Bypass: HSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_HSEConfig(uint32_t RCC_HSE)
{
    /* Check the parameters */
    assert_param(IS_RCC_HSE(RCC_HSE));

    /* Reset HSEON and HSEBYP bits before configuring the HSE ------------------*/
    RCC->CR &= (uint32_t)(~RCC_HSE_Bypass);

    /* Set the new HSE configuration -------------------------------------------*/
    RCC->CR |= RCC_HSE;

}

/**
  * @brief  Waits for HSE start up.
  * @note   This function waits on HSERDY flag to be set and return SUCCESS if
  *         this flag is set, otherwise returns ERROR if the timeout is reached
  *         and this flag is not set. The timeout value is defined by the constant
  *         HSE_STARTUP_TIMEOUT in ft32f4xx.h file. You can tailor it depending
  *         on the HSE crystal used in your application.
  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: HSE oscillator is stable and ready to use
  *          - ERROR: HSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForHSEStartUp(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus HSEStatus = RESET;

    /* Wait till HSE is ready and if timeout is reached exit */
    do
    {
        HSEStatus = RCC_GetFlagStatus(RCC_FLAG_REG_CR, RCC_FLAG_HSERDY);
        StartUpCounter++;
    }
    while ((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));

    if (RCC_GetFlagStatus(RCC_FLAG_REG_CR, RCC_FLAG_HSERDY) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
  * @brief  Adjusts the Internal High Speed oscillator (HSI) calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  *         Refer to the Application Note AN4067 for more details on how to
  *         calibrate the HSI.
  * @param  HSICalibrationValue: specifies the HSI calibration trimming value.
  *          This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_HSI_CALIBRATION_VALUE(HSICalibrationValue));

    tmpreg = RCC->CR;

    /* Clear HSITRIM[4:0] bits */
    tmpreg &= ~RCC_CR_HSITRIM;

    /* Set the HSITRIM[4:0] bits according to HSICalibrationValue value */
    tmpreg |= ((uint32_t)HSICalibrationValue << 3);

    /* Store the new value */
    RCC->CR = tmpreg;
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator (HSI).
  * @note   After enabling the HSI, the application software should wait on
  *         HSIRDY flag to be set indicating that HSI clock is stable and can
  *         be used to clock the PLL and/or system clock.
  * @note   HSI can not be stopped if it is used directly or through the PLL
  *         as system clock. In this case, you have to select another source
  *         of the system clock then stop the HSI.
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the HSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSICmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR |= RCC_CR_HSION;
    }
    else
    {
        RCC->CR &= ~RCC_CR_HSION;
    }
}

/**
  * @brief  Waits for HSI start up.
  * @note   This function waits on HSIRDY flag to be set and return SUCCESS if
  *         this flag is set, otherwise returns ERROR if the timeout is reached
  *         and this flag is not set. The timeout value is defined by the constant
  *         HSI_STARTUP_TIMEOUT in ft32f4xx.h file. You can tailor it depending
  *         on the HSI crystal used in your application.
  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: HSU oscillator is stable and ready to use
  *          - ERROR: HSI oscillator not yet ready
  */
ErrorStatus RCC_WaitForHSIStartUp(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus HSIStatus = RESET;

    /* Wait till HSI is ready and if timeout is reached exit */
    do
    {
        HSIStatus = RCC_GetFlagStatus(RCC_FLAG_REG_CR, RCC_FLAG_HSIRDY);
        StartUpCounter++;
    }
    while ((StartUpCounter != HSI_STARTUP_TIMEOUT) && (HSIStatus == RESET));

    if (RCC_GetFlagStatus(RCC_FLAG_REG_CR, RCC_FLAG_HSIRDY) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
  * @brief  Adjusts the Internal High Speed oscillator for ADC (HSI48)
  *         calibration value.
  * @note   The calibration is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  *         Refer to the Application Note AN4067  for more details on how to
  *         calibrate the HSI48.
  * @param  HSI48CalibrationValue: specifies the HSI48 calibration trimming value.
  *          This parameter must be a number between 0 and 0x1FF.
  * @retval None
  */
void RCC_AdjustHSI48CalibrationValue(uint32_t HSI48CalibrationValue)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_HSI48_CALIBRATION_VALUE(HSI48CalibrationValue));

    tmpreg = RCC->CR2;

    /* Clear HSI48CAL[8:0] bits */
    tmpreg &= ~RCC_CR2_HSI48CAL;

    /* Set the HSICAL48[8:0] bits according to HSI48CalibrationValue value */
    tmpreg |= ((uint32_t)HSI48CalibrationValue << 23);

    /* Store the new value */
    RCC->CR2 = tmpreg;
}

/**
  * @brief  Enables or disables the Internal High Speed oscillator for ADC (HSI48).
  * @note   After enabling the HSI48, the application software should wait on
  *         HSI48RDY flag to be set indicating that HSI clock is stable and can
  *         be used to clock the ADC.
  * @note   The HSI48 is stopped by hardware when entering STOP and STANDBY modes.
  * @param  NewState: new state of the HSI48.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When the HSI48 is stopped, HSI48RDY flag goes low after 6 HSI14 oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_HSI48Cmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR2 |= RCC_CR2_HSI48ON;
    }
    else
    {
        RCC->CR2 &= ~RCC_CR2_HSI48ON;
    }
}

/**
  * @brief  Waits for HSI48 start up.
  * @note   This function waits on HSI48RDY flag to be set and return SUCCESS if
  *         this flag is set, otherwise returns ERROR if the timeout is reached
  *         and this flag is not set. The timeout value is defined by the constant
  *         HSI48_STARTUP_TIMEOUT in ft32f4xx.h file. You can tailor it depending
  *         on the HSI48 crystal used in your application.
  * @note   The HSI48 is stopped by hardware when entering STOP and STANDBY modes.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: HSI48 oscillator is stable and ready to use
  *          - ERROR: HSI48 oscillator not yet ready
  */
ErrorStatus RCC_WaitForHSI48StartUp(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus HSI48Status = RESET;

    /* Wait till HSI48 is ready and if timeout is reached exit */
    do
    {
        HSI48Status = RCC_GetFlagStatus(RCC_FLAG_REG_CR2, RCC_FLAG_HSI48RDY);
        StartUpCounter++;
    }
    while ((StartUpCounter != HSI48_STARTUP_TIMEOUT) && (HSI48Status == RESET));

    if (RCC_GetFlagStatus(RCC_FLAG_REG_CR2, RCC_FLAG_HSI48RDY) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}


/**
  * @brief  Configures the External Low Speed oscillator (LSE).
  * @note   As the LSE is in the Backup domain and write access is denied to this
  *         domain after reset, you have to enable write access using
  *         PWR_BackupAccessCmd(ENABLE) function before to configure the LSE
  *         (to be done once after reset).
  * @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_Bypass), the application
  *         software should wait on LSERDY flag to be set indicating that LSE clock
  *         is stable and can be used to clock the RTC.
  * @param  RCC_LSE: specifies the new state of the LSE.
  *          This parameter can be one of the following values:
  *            @arg RCC_LSE_OFF: turn OFF the LSE oscillator, LSERDY flag goes low after
  *                              6 LSE oscillator clock cycles.
  *            @arg RCC_LSE_ON: turn ON the LSE oscillator after 4096 clock cycle stable
  *            @arg RCC_LSE_BYP: LSE oscillator bypassed with external clock
  * @retval None
  */
void RCC_LSEConfig(uint32_t RCC_LSE)
{
    /* Check the parameters */
    assert_param(IS_RCC_LSE(RCC_LSE));

    /* Reset LSEON and LSEBYP bits before configuring the LSE ------------------*/
    /* Reset LSEON bit */
    RCC->BDCR &= ~(RCC_BDCR_LSEON);

    /* Reset LSEBYP bit */
    RCC->BDCR &= ~(RCC_BDCR_LSEBYP);

    /* Configure LSE */
    RCC->BDCR |= RCC_LSE | RCC_LSEDrive_MediumLow;
}

/**
  * @brief  Waits for LSE start up.
  * @note   This function waits on LSERDY flag to be set and return SUCCESS if
  *         this flag is set, otherwise returns ERROR if the timeout is reached
  *         and this flag is not set. The timeout value is defined by the constant
  *         LSE_STARTUP_TIMEOUT in ft32f4xx.h file. You can tailor it depending
  *         on the LSE crystal used in your application.
  * @note   The LSE is stopped by hardware when entering STOP and STANDBY modes.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: LSE oscillator is stable and ready to use
  *          - ERROR: LSE oscillator not yet ready
  */
ErrorStatus RCC_WaitForLSEStartUp(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus LSEStatus = RESET;

    /* Wait till LSE is ready and if timeout is reached exit */
    do
    {
        LSEStatus = RCC_GetFlagStatus(RCC_FLAG_REG_BDCR, RCC_FLAG_LSERDY);
        StartUpCounter++;
    }
    while ((StartUpCounter != LSE_STARTUP_TIMEOUT) && (LSEStatus == RESET));

    if (RCC_GetFlagStatus(RCC_FLAG_REG_BDCR, RCC_FLAG_LSERDY) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE) drive capability.
  * @param  RCC_LSEDrive: specifies the new state of the LSE drive capability.
  *          This parameter can be one of the following values:
  *            @arg RCC_LSEDrive_Low: LSE oscillator low drive capability.
  *            @arg RCC_LSEDrive_MediumLow: LSE oscillator medium low drive capability.
  *            @arg RCC_LSEDrive_MediumHigh: LSE oscillator medium high drive capability.
  *            @arg RCC_LSEDrive_High: LSE oscillator high drive capability.
  * @retval None
  */
void RCC_LSEDriveConfig(uint32_t RCC_LSEDrive)
{
    /* Check the parameters */
    assert_param(IS_RCC_LSE_DRIVE(RCC_LSEDrive));

    /* Clear LSEDRV[1:0] bits */
    RCC->BDCR &= ~(RCC_BDCR_LSEDRV);

    /* Set the LSE Drive */
    RCC->BDCR |= RCC_LSEDrive;
}

/**
  * @brief  Enables or disables the Internal Low Speed oscillator (LSI).
  * @note   After enabling the LSI, the application software should wait on
  *         LSIRDY flag to be set indicating that LSI clock is stable and can
  *         be used to clock the IWDG and/or the RTC.
  * @note   LSI can not be disabled if the IWDG is running.
  * @param  NewState: new state of the LSI.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
  *         clock cycles.
  * @retval None
  */
void RCC_LSICmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CSR |= RCC_CSR_LSION;
    }
    else
    {
        RCC->CSR &= ~RCC_CSR_LSION;
    }
}

/**
  * @brief  Waits for LSI start up.
  * @note   This function waits on LSIRDY flag to be set and return SUCCESS if
  *         this flag is set, otherwise returns ERROR if the timeout is reached
  *         and this flag is not set. The timeout value is defined by the constant
  *         LSI_STARTUP_TIMEOUT in ft32f4xx.h file. You can tailor it depending
  *         on the LSI crystal used in your application.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: LSI oscillator is stable and ready to use
  *          - ERROR: LSI oscillator not yet ready
  */
ErrorStatus RCC_WaitForLSIStartUp(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus LSIStatus = RESET;

    /* Wait till LSI is ready and if timeout is reached exit */
    do
    {
        LSIStatus = RCC_GetFlagStatus(RCC_FLAG_REG_CSR, RCC_FLAG_LSIRDY);
        StartUpCounter++;
    }
    while ((StartUpCounter != LSI_STARTUP_TIMEOUT) && (LSIStatus == RESET));

    if (RCC_GetFlagStatus(RCC_FLAG_REG_CSR, RCC_FLAG_LSIRDY) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
  * @brief  Configures the PLL clock source, multiplication and null factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PLLSource: specifies the PLL entry clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLLSource_HSI: HSI oscillator clock selected as PLL clock source
  *            @arg RCC_PLLSource_HSE: HSE oscillator clock selected as PLL clock source
  * @note   The minimum input clock frequency for PLL is 2 MHz
  * @param  RCC_PLLNul: specifies the PLL multiplication factor, which drive the PLLVCO clock
  *            This parameter must be a number between 0 and 0xFF.
  * @param  RCC_PLLMul: specifies the PLL Division factor, which drive the PLLVCO clock
  *            This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
void RCC_PLLVcoOutputConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLNul, uint32_t RCC_PLLMul)
{
    /* Check the parameters */
    assert_param(IS_RCC_PLLSRC(RCC_PLLSource));
    assert_param(IS_RCC_PLLN_VALUE(RCC_PLLNul));
    assert_param(IS_RCC_PLLM_VALUE(RCC_PLLMul));

    /* Clear PLLSRC[14], PLLN[7:0], and PLLM[4:0] bits */
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLM);

    /* Set the PLL Source PLLN and PLLM */
    RCC->PLLCFGR |= (uint32_t)(((uint32_t)RCC_PLLSource << 14) |
                               ((uint32_t)RCC_PLLNul << 6)   |
                               ((uint32_t)RCC_PLLMul));
}

/**
  * @brief  Configures the PLLR clock enable, division factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PLLRstatus: specifies the PLLR enable or disable.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLLR_OFF: PLLR clock disable
  *            @arg RCC_PLLR_ON:  PLLR clock enable
  * @param  RCC_PLLR: specifies the PLLR division factor
  *            This parameter must be a number between 0 and 0x07.
  * @retval None
  */
void RCC_PLLROutputConfig(uint32_t RCC_PLLRStatus, uint32_t RCC_PLLR)
{
    /* Check the parameters */
    assert_param(IS_RCC_PLLR(RCC_PLLRStatus));
    assert_param(IS_RCC_PLLR_VALUE(RCC_PLLR));

    /* Clear PLLR[2:0], PLLREN bits */
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLR | RCC_PLLCFGR_PLLREN);

    /* Set the PLLREN and PLLR[2:0] */
    RCC->PLLCFGR |= (uint32_t)(((uint32_t)RCC_PLLRStatus << 25) |
                               ((uint32_t)RCC_PLLR << 26));
}

/**
  * @brief  Configures the PLLQ clock enable, division factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PLLQstatus: specifies the PLLQ enable or disable.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLLQ_OFF: PLLQ clock disable
  *            @arg RCC_PLLQ_ON:  PLLQ clock enable
  * @param  RCC_PLLQ: specifies the PLLQ division factor
  *            This parameter must be a number between 0 and 0x0F.
  * @retval None
  */
void RCC_PLLQOutputConfig(uint32_t RCC_PLLQStatus, uint32_t RCC_PLLQ)
{
    /* Check the parameters */
    assert_param(IS_RCC_PLLQ(RCC_PLLQStatus));
    assert_param(IS_RCC_PLLQ_VALUE(RCC_PLLQ));

    /* Clear PLLQ[3:0], PLLQEN bits */
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLQEN);

    /* Set the PLLQEN and PLLQ[3:0] */
    RCC->PLLCFGR |= (uint32_t)(((uint32_t)RCC_PLLQStatus << 20) |
                               ((uint32_t)RCC_PLLQ << 21));
}

/**
  * @brief  Configures the PLLP clock enable, division factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PLLPstatus: specifies the PLLP enable or disable.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLLP_OFF: PLLP clock disable
  *            @arg RCC_PLLP_ON:  PLLP clock enable
  * @param  RCC_PLLP: specifies the PLLP division factor
  *            This parameter must be a number between 0 and 0x07.
  * @retval None
  */
void RCC_PLLPOutputConfig(uint32_t RCC_PLLPStatus, uint32_t RCC_PLLP)
{
    /* Check the parameters */
    assert_param(IS_RCC_PLLP(RCC_PLLPStatus));
    assert_param(IS_RCC_PLLP_VALUE(RCC_PLLP));

    /* Clear PLLP[2:0], PLLPEN bits */
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLPEN);

    /* Set the PLLPEN and PLLP[2:0] */
    RCC->PLLCFGR |= (uint32_t)(((uint32_t)RCC_PLLPStatus << 16) |
                               ((uint32_t)RCC_PLLP << 17));
}

/**
  * @brief  Configures the PLL2 clock source, multiplication and null factor.
  * @note   This function must be used only when the PLL is disabled.
  * @param  RCC_PLL2Source: specifies the PLL entry clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLL2Source_HSI: HSI oscillator clock selected as PLL2 clock source
  *            @arg RCC_PLL2Source_HSE: HSE oscillator clock selected as PLL2 clock source
  * @note   The minimum input clock frequency for PLL2 is 2 MHz
  * @param  RCC_PLL2Nul: specifies the PLL2 multiplication factor, which drive the PLL2VCO clock
  *            This parameter must be a number between 0 and 0xFF.
  * @param  RCC_PLL2Mul: specifies the PLL2 Division factor, which drive the PLL2VCO clock
  *            This parameter must be a number between 0 and 0x1F.
  * @retval None
  */
void RCC_PLL2VcoOutputConfig(uint32_t RCC_PLL2Source, uint32_t RCC_PLL2Nul, uint32_t RCC_PLL2Mul)
{
    /* Check the parameters */
    assert_param(IS_RCC_PLL2SRC(RCC_PLL2Source));
    assert_param(IS_RCC_PLL2N_VALUE(RCC_PLL2Nul));
    assert_param(IS_RCC_PLL2M_VALUE(RCC_PLL2Mul));

    /* Clear PLL2SRC[14], PLL2N[7:0], and PLL2M[4:0] bits */
    RCC->PLL2CFGR &= ~(RCC_PLL2CFGR_PLL2SRC | RCC_PLL2CFGR_PLL2N | RCC_PLL2CFGR_PLL2M);

    /* Set the PLL2 Source, PLL2N and PLL2M */
    RCC->PLL2CFGR |= (uint32_t)(((uint32_t)RCC_PLL2Source << 14) |
                                ((uint32_t)RCC_PLL2Nul << 6)   |
                                ((uint32_t)RCC_PLL2Mul));
}

/**
  * @brief  Configures the PLL2R clock enable, division factor.
  * @note   This function must be used only when the PLL2 is disabled.
  * @param  RCC_PLL2Rstatus: specifies the PLL2R enable or disable.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLL2R_OFF: PLL2R clock disable
  *            @arg RCC_PLL2R_ON:  PLL2R clock enable
  * @param  RCC_PLL2R: specifies the PLL2R division factor
  *            This parameter must be a number between 0 and 0x07.
  * @retval None
  */
void RCC_PLL2ROutputConfig(uint32_t RCC_PLL2RStatus, uint32_t RCC_PLL2R)
{
    /* Check the parameters */
    assert_param(IS_RCC_PLL2R(RCC_PLL2RStatus));
    assert_param(IS_RCC_PLL2R_VALUE(RCC_PLL2R));

    /* Clear PLL2R[2:0], PLL2REN bits */
    RCC->PLL2CFGR &= ~(RCC_PLL2CFGR_PLL2R | RCC_PLL2CFGR_PLL2REN);

    /* Set the PLL2REN and PLL2R[2:0] */
    RCC->PLL2CFGR |= (uint32_t)(((uint32_t)RCC_PLL2RStatus << 25) |
                                ((uint32_t)RCC_PLL2R << 26));
}

/**
  * @brief  Configures the PLL2Q clock enable, division factor.
  * @note   This function must be used only when the PLL2 is disabled.
  * @param  RCC_PLL2Qstatus: specifies the PLL2Q enable or disable.
  *          This parameter can be one of the following values:
  *            @arg RCC_PLL2Q_OFF: PLL2Q clock disable
  *            @arg RCC_PLL2Q_ON:  PLL2Q clock enable
  * @param  RCC_PLL2Q: specifies the PLL2Q division factor
  *            This parameter must be a number between 0 and 0x0F.
  * @retval None
  */
void RCC_PLL2QOutputConfig(uint32_t RCC_PLL2QStatus, uint32_t RCC_PLL2Q)
{
    /* Check the parameters */
    assert_param(IS_RCC_PLL2Q(RCC_PLL2QStatus));
    assert_param(IS_RCC_PLL2Q_VALUE(RCC_PLL2Q));

    /* Clear PLL2Q[3:0], PLL2QEN bits */
    RCC->PLL2CFGR &= ~(RCC_PLL2CFGR_PLL2Q | RCC_PLL2CFGR_PLL2QEN);

    /* Set the PLL2QEN and PLL2Q[3:0] */
    RCC->PLL2CFGR |= (uint32_t)(((uint32_t)RCC_PLL2QStatus << 20) |
                                ((uint32_t)RCC_PLL2Q << 21));
}


/**
  * @brief  Enables or disables the PLL.
  * @note   After enabling the PLL, the application software should wait on
  *         PLLRDY flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @note   The PLL can not be disabled if it is used as system clock source
  * @note   The PLL is disabled by hardware when entering STOP and STANDBY modes.
  * @param  RCC_PLLSelect: select enable pll or pll2.
  *          This parameter can be one of the following values:
  *            @arg RCC_SEL_PLL:  PLL clock enable
  *            @arg RCC_SEL_PLL2: PLL2 clock enable
  * @param  NewState: new state of the PLL.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_PLLCmd(uint32_t RCC_PLLSelect, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_SEL(RCC_PLLSelect));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (RCC_PLLSelect == RCC_SEL_PLL)
    {
        if (NewState != DISABLE)
        {
            RCC->CR |= RCC_CR_PLLON;
        }
        else
        {
            RCC->CR &= ~RCC_CR_PLLON;
        }
    }
    else if (RCC_PLLSelect == RCC_SEL_PLL2)
    {
        if (NewState != DISABLE)
        {
            RCC->CR |= RCC_CR_PLL2ON;
        }
        else
        {
            RCC->CR &= ~RCC_CR_PLL2ON;
        }
    }
}

/**
  * @brief  Waits for PLL start up.
  * @note   This function waits on PLLRDY flag to be set and return SUCCESS if
  *         this flag is set, otherwise returns ERROR if the timeout is reached
  *         and this flag is not set. The timeout value is defined by the constant
  *         PLL_STARTUP_TIMEOUT in ft32f4xx.h file. You can tailor it depending
  *         on the PLL crystal used in your application.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PLL oscillator is stable and ready to use
  *          - ERROR: PLL oscillator not yet ready
  */
ErrorStatus RCC_WaitForPLLStartUp(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus PLLStatus = RESET;

    /* Wait till PLL is ready and if timeout is reached exit */
    do
    {
        PLLStatus = RCC_GetFlagStatus(RCC_FLAG_REG_CR, RCC_FLAG_PLLRDY);
        StartUpCounter++;
    }
    while ((StartUpCounter != PLL_STARTUP_TIMEOUT) && (PLLStatus == RESET));

    if (RCC_GetFlagStatus(RCC_FLAG_REG_CR, RCC_FLAG_PLLRDY) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
  * @brief  Waits for PLL2 start up.
  * @note   This function waits on PLL2RDY flag to be set and return SUCCESS if
  *         this flag is set, otherwise returns ERROR if the timeout is reached
  *         and this flag is not set. The timeout value is defined by the constant
  *         PLL2_STARTUP_TIMEOUT in ft32f4xx.h file. You can tailor it depending
  *         on the PLL2 crystal used in your application.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PLL2 oscillator is stable and ready to use
  *          - ERROR: PLL2 oscillator not yet ready
  */
ErrorStatus RCC_WaitForPLL2StartUp(void)
{
    __IO uint32_t StartUpCounter = 0;
    ErrorStatus status = ERROR;
    FlagStatus PLL2Status = RESET;

    /* Wait till PLL2 is ready and if timeout is reached exit */
    do
    {
        PLL2Status = RCC_GetFlagStatus(RCC_FLAG_REG_CR, RCC_FLAG_PLL2RDY);
        StartUpCounter++;
    }
    while ((StartUpCounter != PLL2_STARTUP_TIMEOUT) && (PLL2Status == RESET));

    if (RCC_GetFlagStatus(RCC_FLAG_REG_CR, RCC_FLAG_PLL2RDY) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
  * @brief  Enables or disables the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to
  *         the Cortex-M0 NMI (Non-Maskable Interrupt) exception vector.
  * @param  NewState: new state of the Clock Security System.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->CR |= RCC_CR_CSSON;
    }
    else
    {
        RCC->CR &= ~RCC_CR_CSSON;
    }
}

/**
  * @brief  Selects the clock source to output on MCO pin (PA8) and the corresponding
  *         prescsaler.
  * @note   PA8 should be configured in alternate function mode(AF0).
  * @param  RCC_MCOSource: specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCOSource_NoClock: No clock selected.
  *            @arg RCC_MCOSource_SYSCLK: System clock selected.
  *            @arg RCC_MCOSource_PLL2R: PLL2R clock selected.
  *            @arg RCC_MCOSource_HSI16: HSI16 oscillator clock selected.
  *            @arg RCC_MCOSource_HSE: HSE oscillator clock selected.
  *            @arg RCC_MCOSource_PLLP: PLLP clock selected.
  *            @arg RCC_MCOSource_LSI: LSI oscillator clock selected.
  *            @arg RCC_MCOSource_LSE: LSE oscillator clock selected.
  *            @arg RCC_MCOSource_HSI48: HSI48 clock selected.
  * @param  RCC_MCOPrescaler: specifies the prescaler on MCO pin.
  *          This parameter can be one of the following values:
  *            @arg RCC_MCOPrescaler_1: MCO clock is divided by 1.
  *            @arg RCC_MCOPrescaler_2: MCO clock is divided by 2.
  *            @arg RCC_MCOPrescaler_4: MCO clock is divided by 4.
  *            @arg RCC_MCOPrescaler_8: MCO clock is divided by 8.
  *            @arg RCC_MCOPrescaler_16: MCO clock is divided by 16.
  *            @arg RCC_MCOPrescaler_32: MCO clock is divided by 32.
  *            @arg RCC_MCOPrescaler_64: MCO clock is divided by 64.
  *            @arg RCC_MCOPrescaler_128: MCO clock is divided by 128.
  * @retval None
  */
void RCC_MCOConfig(uint32_t RCC_MCOSource, uint32_t RCC_MCOPrescaler)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_MCO_SOURCE(RCC_MCOSource));
    assert_param(IS_RCC_MCO_PRESCALER(RCC_MCOPrescaler));

    /* Get CFGR value */
    tmpreg = RCC->CFGR;
    /* Clear MCOPRE[2:0] and MCOSEL[3:0] bits */
    tmpreg &= ~(RCC_CFGR_MCOPRE | RCC_CFGR_MCOSEL);
    /* Set the RCC_MCOSource and RCC_MCOPrescaler */
    tmpreg |= (RCC_MCOSource | RCC_MCOPrescaler);
    /* Store the new value */
    RCC->CFGR = tmpreg;
}
/**
  * @}
  */

/**
  * @brief  Configures the system clock (SYSCLK).
  * @note   The HSI is used (enabled by hardware) as system clock source after
  *         startup from Reset, wake-up from STOP and STANDBY mode, or in case
  *         of failure of the HSE used directly or indirectly as system clock
  *         (if the Clock Security System CSS is enabled).
  * @note   A switch from one clock source to another occurs only if the target
  *         clock source is ready (clock stable after startup delay or PLL locked).
  *         If a clock source which is not yet ready is selected, the switch will
  *         occur when the clock source will be ready.
  *         You can use RCC_GetSYSCLKSource() function to know which clock is
  *         currently used as system clock source.
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock source
  *          This parameter can be one of the following values:
  *            @arg RCC_SYSCLKSource_HSI16:  HSI16 selected as system clock source
  *            @arg RCC_SYSCLKSource_HSE:    HSE selected as system clock source
  *            @arg RCC_SYSCLKSource_PLLCLK: PLL selected as system clock source
  * @retval None
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));

    tmpreg = RCC->CFGR;

    /* Clear SW[1:0] bits */
    tmpreg &= ~RCC_CFGR_SW;

    /* Set SW[1:0] bits according to RCC_SYSCLKSource value */
    tmpreg |= RCC_SYSCLKSource;

    /* Store the new value */
    RCC->CFGR = tmpreg;
}

/**
  * @brief  Returns the clock source used as system clock.
  * @param  None
  * @retval The clock source used as system clock. The returned value can be one
  *         of the following values:
  *           - 0x00000000: HSI16 used as system clock
  *           - 0x00000004: HSE used as system clock
  *           - 0x00000008: PLL used as system clock
  */
uint32_t RCC_GetSYSCLKSource(void)
{
    return ((uint32_t)(RCC->CFGR & RCC_CFGR_SWS));
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @param  RCC_SYSCLK: defines the AHB clock divider. This clock is derived from
  *         the system clock (SYSCLK).
  *          This parameter can be one of the following values:
  *            @arg RCC_SYSCLK_DIV1:   AHB clock = SYSCLK
  *            @arg RCC_SYSCLK_DIV2:   AHB clock = SYSCLK/2
  *            @arg RCC_SYSCLK_DIV4:   AHB clock = SYSCLK/4
  *            @arg RCC_SYSCLK_DIV8:   AHB clock = SYSCLK/8
  *            @arg RCC_SYSCLK_DIV16:  AHB clock = SYSCLK/16
  *            @arg RCC_SYSCLK_DIV64:  AHB clock = SYSCLK/64
  *            @arg RCC_SYSCLK_DIV128: AHB clock = SYSCLK/128
  *            @arg RCC_SYSCLK_DIV256: AHB clock = SYSCLK/256
  *            @arg RCC_SYSCLK_DIV512: AHB clock = SYSCLK/512
  * @retval None
  */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_HCLK(RCC_SYSCLK));

    tmpreg = RCC->CFGR;

    /* Clear HPRE[3:0] bits */
    tmpreg &= ~RCC_CFGR_HPRE;

    /* Set HPRE[3:0] bits according to RCC_SYSCLK value */
    tmpreg |= RCC_SYSCLK;

    /* Store the new value */
    RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the APB clock (PCLK).
  * @param  RCC_HCLK1: defines the APB clock divider. This clock is derived from
  *         the AHB clock (HCLK).
  *          This parameter can be one of the following values:
  *            @arg RCC_HCLK_DIV1: APB clock = HCLK
  *            @arg RCC_HCLK_DIV2: APB clock = HCLK/2
  *            @arg RCC_HCLK_DIV4: APB clock = HCLK/4
  *            @arg RCC_HCLK_DIV8: APB clock = HCLK/8
  *            @arg RCC_HCLK_DIV16: APB clock = HCLK/16
  * @retval None
  */
void RCC_PCLK1Config(uint32_t RCC_HCLK1)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_PCLK(RCC_HCLK1));

    tmpreg = RCC->CFGR;

    /* Clear PPRE1[2:0] bits */
    tmpreg &= ~RCC_CFGR_PPRE1;

    /* Set PPRE1[2:0] bits according to RCC_HCLK value */
    tmpreg |= ((uint32_t)RCC_HCLK1 << 8);

    /* Store the new value */
    RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the APB clock (PCLK).
  * @param  RCC_HCLK2: defines the APB clock divider. This clock is derived from
  *         the AHB clock (HCLK).
  *          This parameter can be one of the following values:
  *            @arg RCC_HCLK_DIV1: APB clock = HCLK
  *            @arg RCC_HCLK_DIV2: APB clock = HCLK/2
  *            @arg RCC_HCLK_DIV4: APB clock = HCLK/4
  *            @arg RCC_HCLK_DIV8: APB clock = HCLK/8
  *            @arg RCC_HCLK_DIV16: APB clock = HCLK/16
  * @retval None
  */
void RCC_PCLK2Config(uint32_t RCC_HCLK2)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_RCC_PCLK(RCC_HCLK2));

    tmpreg = RCC->CFGR;

    /* Clear PPRE[2:0] bits */
    tmpreg &= ~RCC_CFGR_PPRE2;

    /* Set PPRE2[2:0] bits according to RCC_HCLK value */
    tmpreg |= ((uint32_t)RCC_HCLK2 << 11);

    /* Store the new value */
    RCC->CFGR = tmpreg;
}

/**
  * @brief  Configures the QSPI clock (QSPICLK).
  * @note   This function is obsolete.
  *         For proper QSPI clock selection, refer to QSPI_ClockModeConfig() in the QSPI driver
  * @param  RCC_QSPICLK: defines the QSPI clock source. This clock is derived
  *         from the HSI16, PLL1Q or SYSCLK.
  *          This parameter can be one of the following values:
  *             @arg RCC_QSPICLK_SYSCLK: QSPI clock = SYSCLK
  *             @arg RCC_QSPICLK_HSI16:  QSPI clock = HSI16
  *             @arg RCC_QSPICLK_PLL1Q:  QSPI clock = PLL1Q
  * @retval None
  */
void RCC_QSPICLKConfig(uint32_t RCC_QSPICLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_QSPICLK(RCC_QSPICLK));

    /* Clear QSPISEL[1:0] bitS */
    RCC->CCIPR &= ~RCC_CCIPR_QSPISEL;

    /* Set QSPISEL bits according to RCC_QSPICLK value */
    RCC->CCIPR |= RCC_QSPICLK;
}

/**
  * @brief  Configures the ADC clock (ADCCLK).
  * @note   This function is obsolete.
  *         For proper ADC clock selection, refer to ADC_ClockModeConfig() in the ADC driver
  * @param  RCC_ADCCLK: defines the ADC clock source. This clock is derived
  *         from the PLL1R or SYSCLK.
  *          This parameter can be one of the following values:
  *             @arg RCC_ADCCLK_NOCLK:  ADC no clock
  *             @arg RCC_ADCCLK_PLL1R:  ADC clock = PLL1R
  *             @arg RCC_ADCCLK_SYSCLK: ADC clock = SYSCLK
  * @retval None
  */
void RCC_ADCCLKConfig(uint32_t RCC_ADCCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_ADCCLK(RCC_ADCCLK));

    /* Clear ADC123SEL[1:0] bitS */
    RCC->CCIPR &= ~RCC_CCIPR_ADCSEL;

    /* Set ADCSEL bits according to RCC_ADCCLK value */
    RCC->CCIPR |= RCC_ADCCLK;
}

/**
  * @brief  Configures the CAN clock (CANCLK).
  * @note   This function is obsolete.
  *         For proper CAN clock selection, refer to CAN_ClockModeConfig() in the CAN driver
  * @param  RCC_CANCLK: defines the CAN clock source. This clock is derived
  *         from the HCLK or HCLK's prescaler.
  *          This parameter can be one of the following values:
  *             @arg RCC_CANCLK_HCLK:       CAN clock = HCLK
  *             @arg RCC_CANCLK_HCLK_DIV2:  CAN clock = HCLK/2
  *             @arg RCC_CANCLK_HCLK_DIV4:  CAN clock = HCLK/4
  *             @arg RCC_CANCLK_HCLK_DIV8:  CAN clock = HCLK/8
  *             @arg RCC_CANCLK_HCLK_DIV16: CAN clock = HCLK/16
  *             @arg RCC_CANCLK_HCLK_DIV32: CAN clock = HCLK/32
  * @retval None
  */
void RCC_CANCLKConfig(uint32_t RCC_CANCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_CANCLK(RCC_CANCLK));

    /* Clear CANSEL[3:0] bits */
    RCC->CCIPR &= ~RCC_CCIPR_CANSEL;

    /* Set CANSEL bits according to RCC_CANCLK value */
    RCC->CCIPR |= RCC_CANCLK;
}

/**
  * @brief  Configures the LPTIM clock (LPTIMCLK).
  * @note   This function is obsolete.
  *         For proper LPTIM clock selection, refer to LPTIM_ClockModeConfig() in the LPTIM driver
  * @param  RCC_LPTIMCLK: defines the LPTIM clock source. This clock is derived
  *         from the PCLK, LSI, HSI16 or LSE prescaler.
  *          This parameter can be one of the following values:
  *             @arg RCC_LPTIMCLK_PCLK:  LPTIM clock = PCLK
  *             @arg RCC_LPTIMCLK_LSI:   LPTIM clock = LSI
  *             @arg RCC_LPTIMCLK_HSI16: LPTIM clock = HSI16
  *             @arg RCC_LPTIMCLK_LSE:   LPTIM clock = LSE
  * @retval None
  */
void RCC_LPTIMCLKConfig(uint32_t RCC_LPTIMCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPTIMCLK(RCC_LPTIMCLK));

    /* Clear LPTIMSEL[1:0] bits */
    RCC->CCIPR &= ~RCC_CCIPR_LPTIMSEL;

    /* Set LPTIMSEL bits according to RCC_LPTIMCLK value */
    RCC->CCIPR |= RCC_LPTIMCLK;
}

/**
  * @brief  Configures the I2C3 clock (I2C3CLK).
  * @note   This function is obsolete.
  *         For proper I2C3 clock selection, refer to I2C3_ClockModeConfig() in the I2C3 driver
  * @param  RCC_I2C3CLK: defines the I2C3 clock source. This clock is derived
  *         from the PCLK, SYSCLK or HSI16.
  *          This parameter can be one of the following values:
  *             @arg RCC_I2C3CLK_PCLK:   I2C3 clock = PCLK
  *             @arg RCC_I2C3CLK_SYSCLK: I2C3 clock = SYSCLK
  *             @arg RCC_I2C3CLK_HSI16:  I2C3 clock = HSI16
  * @retval None
  */
void RCC_I2C3CLKConfig(uint32_t RCC_I2C3CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_I2C3CLK(RCC_I2C3CLK));

    /* Clear I2C3SEL[1:0] bits */
    RCC->CCIPR &= ~RCC_CCIPR_I2C3SEL;

    /* Set I2C3SEL bits according to RCC_I2C3CLK value */
    RCC->CCIPR |= RCC_I2C3CLK;
}

/**
  * @brief  Configures the I2C2 clock (I2C2CLK).
  * @note   This function is obsolete.
  *         For proper I2C2 clock selection, refer to I2C2_ClockModeConfig() in the I2C2 driver
  * @param  RCC_I2C2CLK: defines the I2C2 clock source. This clock is derived
  *         from the PCLK, SYSCLK or HSI16.
  *          This parameter can be one of the following values:
  *             @arg RCC_I2C2CLK_PCLK:   I2C2 clock = PCLK
  *             @arg RCC_I2C2CLK_SYSCLK: I2C2 clock = SYSCLK
  *             @arg RCC_I2C2CLK_HSI16:  I2C2 clock = HSI16
  * @retval None
  */
void RCC_I2C2CLKConfig(uint32_t RCC_I2C2CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_I2C2CLK(RCC_I2C2CLK));

    /* Clear I2C2SEL[1:0] bits */
    RCC->CCIPR &= ~RCC_CCIPR_I2C2SEL;

    /* Set I2C2SEL bits according to RCC_I2C2CLK value */
    RCC->CCIPR |= RCC_I2C2CLK;
}

/**
  * @brief  Configures the I2C1 clock (I2C1CLK).
  * @note   This function is obsolete.
  *         For proper I2C1 clock selection, refer to I2C1_ClockModeConfig() in the I2C1 driver
  * @param  RCC_I2C1CLK: defines the I2C1 clock source. This clock is derived
  *         from the PCLK, SYSCLK or HSI16.
  *          This parameter can be one of the following values:
  *             @arg RCC_I2C1CLK_PCLK:   I2C1 clock = PCLK
  *             @arg RCC_I2C1CLK_SYSCLK: I2C1 clock = SYSCLK
  *             @arg RCC_I2C1CLK_HSI16:  I2C1 clock = HSI16
  * @retval None
  */
void RCC_I2C1CLKConfig(uint32_t RCC_I2C1CLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_I2C1CLK(RCC_I2C1CLK));

    /* Clear I2C1SEL[1:0] bits */
    RCC->CCIPR &= ~RCC_CCIPR_I2C1SEL;

    /* Set I2C1SEL bits according to RCC_I2C1CLK value */
    RCC->CCIPR |= RCC_I2C1CLK;
}

/**
  * @brief  Configures the LPUART clock (LPUARTCLK).
  * @note   This function is obsolete.
  *         For proper LPUART clock selection, refer to LPUART_ClockModeConfig() in the LPUART driver
  * @param  RCC_LPUARTCLK: defines the LPUART clock source. This clock is derived
  *         from the PCLK or LSE.
  *          This parameter can be one of the following values:
  *             @arg RCC_LPUARTCLK_PCLK: LPUART clock = PCLK
  *             @arg RCC_LPUARTCLK_LSE:  LPUART clock = LSE
  * @retval None
  */
void RCC_LPUARTCLKConfig(uint32_t RCC_LPUARTCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_LPUARTCLK(RCC_LPUARTCLK));

    /* Clear LPUARTSEL[1:0] bits */
    RCC->CCIPR &= ~RCC_CCIPR_LPUARTSEL;

    /* Set LPUARTSEL bits according to RCC_LPUARTCLK value */
    RCC->CCIPR |= RCC_LPUARTCLK;
}

/**
  * @brief  Configures the RNG clock division(RNGCLKDIV).
  * @note   This function is obsolete.
  *         For proper RNG clock selection, refer to RNG_ClockModeConfig() in the RNG driver
  * @param  RCC_RNGCLKDIV: defines the RNG clock division. This clock is derived
  *         from the work clk's 1/2/4/8.
  *          This parameter can be one of the following values:
  *             @arg RCC_RNGCLK_DIV1: RNG clock = RNG work clock/1
  *             @arg RCC_RNGCLK_DIV2: RNG clock = RNG work clock/2
  *             @arg RCC_RNGCLK_DIV4: RNG clock = RNG work clock/4
  *             @arg RCC_RNGCLK_DIV8: RNG clock = RNG work clock/8
  * @retval None
  */
void RCC_RNGCLKDIVConfig(uint32_t RCC_RNGCLKDIV)
{
    /* Check the parameters */
    assert_param(IS_RCC_RNGCLK_DIV(RCC_RNGCLKDIV));

    /* Clear RNGDIV[1:0] bits */
    RCC->CCIPR &= ~RCC_CCIPR_RNGDIV;

    /* Set RNGDIV[1:0] bits according to RCC_RNGCLKDIV value */
    RCC->CCIPR |= RCC_RNGCLKDIV;
}

/**
  * @brief  Configures the 48M clock source(48MCLK).
  * @note   This function is obsolete.
  *         For proper 48M clock selection
  * @param  RCC_48MCLK: defines the 48M clock source. This clock is derived
  *         from the HSI48 or PLLQ .
  *          This parameter can be one of the following values:
  *             @arg RCC_48MCLK_HSI48: 48M clock = HSI48
  *             @arg RCC_48MCLK_PLLQ:  48M clock = PLLQ
  * @retval None
  */
void RCC_48MCLKConfig(uint32_t RCC_48MCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_48MCLK(RCC_48MCLK));

    /* Clear CLK48SEL bit */
    RCC->CCIPR &= ~RCC_CCIPR_CLK48SEL;

    /* Set CLK48SEL bits according to RCC_48MCLK value */
    RCC->CCIPR |= RCC_48MCLK;
}

/**
  * @brief  Configures the EPWM clock source(EPWMCLK).
  * @note   This function is obsolete.
  *         For proper EPWM clock selection
  * @param  RCC_EPWMCLK: defines the EPWM clock source. This clock is derived
  *         from the SYSCLK or SYSCLK/2/4 .
  *          This parameter can be one of the following values:
  *             @arg RCC_EPWMCLK_SYSCLK:       EPWM clock = SYSCLK
  *             @arg RCC_EPWMCLK_SYSCLK_DIV2:  EPWM clock = SYSCLK/2
  *             @arg RCC_EPWMCLK_SYSCLK_DIV4:  EPWM clock = SYSCLK/4
  * @retval None
  */
void RCC_EPWMCLKConfig(uint32_t RCC_EPWMCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_EPWMCLK(RCC_EPWMCLK));

    /* Clear PWMSEL[1:0] bit */
    RCC->CCIPR &= ~RCC_CCIPR_PWMSEL;

    /* Set PWMSEL bits according to RCC_EPWMCLK value */
    RCC->CCIPR |= RCC_EPWMCLK;
}

/**
  * @brief  Configures the EQEP clock source(EQEPCLK).
  * @note   This function is obsolete.
  *         For proper EQEP clock selection
  * @param  RCC_EQEPCLK: defines the EQEP clock source. This clock is derived
  *         from the SYSCLK or SYSCLK/2/4 .
  *          This parameter can be one of the following values:
  *             @arg RCC_EQEPCLK_SYSCLK:       EQEP clock = SYSCLK
  *             @arg RCC_EQEPCLK_SYSCLK_DIV2:  EQEP clock = SYSCLK/2
  *             @arg RCC_EQEPCLK_SYSCLK_DIV4:  EQEP clock = SYSCLK/4
  * @retval None
  */
void RCC_EQEPCLKConfig(uint32_t RCC_EQEPCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_EQEPCLK(RCC_EQEPCLK));

    /* Clear EQEPSEL[1:0] bit */
    RCC->CCIPR &= ~RCC_CCIPR_EQEPSEL;

    /* Set EQEPSEL bits according to RCC_EQEPCLK value */
    RCC->CCIPR |= RCC_EQEPCLK;
}

/**
  * @brief  Configures the ECAP clock source(ECAPCLK).
  * @note   This function is obsolete.
  *         For proper ECAP clock selection
  * @param  RCC_ECAPCLK: defines the ECAP clock source. This clock is derived
  *         from the SYSCLK or SYSCLK/2/4 .
  *          This parameter can be one of the following values:
  *             @arg RCC_ECAPCLK_SYSCLK:       ECAP clock = SYSCLK
  *             @arg RCC_ECAPCLK_SYSCLK_DIV2:  ECAP clock = SYSCLK/2
  *             @arg RCC_ECAPCLK_SYSCLK_DIV4:  ECAP clock = SYSCLK/4
  * @retval None
  */
void RCC_ECAPCLKConfig(uint32_t RCC_ECAPCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_ECAPCLK(RCC_ECAPCLK));

    /* Clear ECAPSEL[1:0] bit */
    RCC->CCIPR &= ~RCC_CCIPR_ECAPSEL;

    /* Set ECAPSEL bits according to RCC_ECAPCLK value */
    RCC->CCIPR |= RCC_ECAPCLK;
}

/**
  * @brief  Configures the I2S clock source(I2SCLK).
  * @note   This function is obsolete.
  *         For proper I2S clock selection
  * @param  RCC_I2SCLK: defines the I2S clock source. This clock is derived
  *         from the PLL2Q or external I2S_CKIN .
  *          This parameter can be one of the following values:
  *             @arg RCC_I2SCLK_PLL2Q:     I2S clock = PLL2Q
  *             @arg RCC_I2SCLK_I2S_CLKIN: I2S clock = EXTERNAL I2S_CKIN
  * @retval None
  */
void RCC_I2SCLKConfig(uint32_t RCC_I2SCLK)
{
    /* Check the parameters */
    assert_param(IS_RCC_I2SCLK(RCC_I2SCLK));

    /* Clear I2SSEL bit */
    RCC->CCIPR &= ~RCC_CCIPR_I2SSEL;

    /* Set I2SSEL bits according to RCC_I2SCLK value */
    RCC->CCIPR |= RCC_I2SCLK;
}



/**
  * @brief  Returns the frequencies of the System, AHB and APB busses clocks.
  * @note    The frequency returned by this function is not the real frequency
  *           in the chip. It is calculated based on the predefined constant and
  *           the source selected by RCC_SYSCLKConfig():
  *
  * @note     If SYSCLK source is HSI16, function returns constant HSI_VALUE(*)
  *
  * @note     If SYSCLK source is HSE, function returns constant HSE_VALUE(**)
  *
  * @note     If SYSCLK source is PLL, function returns constant HSE_VALUE(**)
  *             or HSI_VALUE(*) multiplied by the PLLN and PLLM factors.
  *
  * @note     (*) HSI_VALUE is a constant defined in ft32f0xx.h file (default value
  *               16 MHz) but the real value may vary depending on the variations
  *               in voltage and temperature, refer to RCC_AdjustHSICalibrationValue().
  *
  * @note     (**) HSE_VALUE is a constant defined in ft32f0xx.h file (default value
  *                24 MHz), user has to ensure that HSE_VALUE is same as the real
  *                frequency of the crystal used. Otherwise, this function may
  *                return wrong result.
  *
  * @note     (***) HSI48_VALUE is a constant defined in ft32f0xx.h file (default value
  *                 48 MHz) but the real value may vary depending on the variations
  *                 in voltage and temperature.
  *
  * @note   The result of this function could be not correct when using fractional
  *         value for HSE crystal.
  *
  * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
  *         the clocks frequencies.
  *
  * @note   This function can be used by the user application to compute the
  *         baudrate for the communication peripherals or configure other parameters.
  * @note   Each time SYSCLK, HCLK and/or PCLK clock changes, this function
  *         must be called to update the structure's field. Otherwise, any
  *         configuration based on this function will be incorrect.
  *
  * @retval None
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks)
{
    uint32_t tmp = 0, pllmul = 0, pllnul = 0, pllp = 0, pllr = 0, pllq = 0, pllsource = 0, pllvcoclk = 0, pllpclk = 0,
                                                                                                          pll2mul = 0, pll2nul = 0, pll2r = 0, pll2q = 0, pll2source = 0, pll2vcoclk = 0,
                                                                                                                                                                          hpresc = 0, presc1 = 0, presc2 = 0;

    /* Get SYSCLK source -------------------------------------------------------*/
    tmp = RCC->CFGR & RCC_CFGR_SWS;

    switch (tmp)
    {
    case 0x00:  /* HSI used as system clock */
        RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
        break;

    case 0x04:  /* HSE used as system clock */
        RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
        break;

    case 0x08:  /* PLL used as system clock */
        /* Get PLL clock source and pllm and plln factor ----------------------*/
        pllp      = (((RCC -> PLLCFGR) & RCC_PLLCFGR_PLLP) >> 17);
        pllsource = (((RCC -> PLLCFGR) & RCC_PLLCFGR_PLLSRC) >> 14);
        pllnul    = (((RCC -> PLLCFGR) & RCC_PLLCFGR_PLLN) >> 6);
        pllmul    = (RCC -> PLLCFGR) & RCC_PLLCFGR_PLLM;
        if (pllsource == 0x00)
        {
            /* HSI oscillator clock divided by pllmul and multiplicat by pllnul as pllvcoclk output */
            pllvcoclk = (HSI_VALUE * pllnul) / pllmul;
            if (pllp == 0)
            {
                pllpclk   = pllvcoclk / 2;
            }
            else
            {
                pllpclk   = pllvcoclk / (pllp + 1);
            }
        }
        else
        {
            /* HSE oscillator clock divided by pllmul and multiplicat by pllnul as pllvcoclk output */
            pllvcoclk = (HSE_VALUE * pllnul) / pllmul;
            if (pllp == 0)
            {
                pllpclk   = pllvcoclk / 2;
            }
            else
            {
                pllpclk   = pllvcoclk / (pllp + 1);
            }
        }

        RCC_Clocks->SYSCLK_Frequency  = pllpclk;
        break;

    default: /* HSI used as system clock */
        RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
        break;
    }

    /* Compute HCLK, PCLK and P2CLK clocks frequencies */
    /* Get HCLK prescaler */
    tmp = RCC->CFGR & RCC_CFGR_HPRE;
    tmp = tmp >> 4;
    hpresc = APBAHBPrescTable[tmp];
    /* HCLK clock frequency */
    RCC_Clocks->HCLK_Frequency = ((RCC_Clocks->SYSCLK_Frequency) >> hpresc);

    /* Get PCLK prescaler */
    tmp = RCC->CFGR & RCC_CFGR_PPRE1;
    tmp = tmp >> 8;
    presc1 = APBAHBPrescTable[tmp];
    /* PCLK clock frequency */
    RCC_Clocks->PCLK_Frequency = ((RCC_Clocks->HCLK_Frequency) >> presc1);
    /* Get PLLQ and PLLR clk */
    pllr      = (((RCC -> PLLCFGR) & RCC_PLLCFGR_PLLR) >> 26);
    pllq      = (((RCC -> PLLCFGR) & RCC_PLLCFGR_PLLQ) >> 21);
    pllsource = (((RCC -> PLLCFGR) & RCC_PLLCFGR_PLLSRC) >> 14);
    pllnul    = (((RCC -> PLLCFGR) & RCC_PLLCFGR_PLLN) >> 6);
    pllmul    = (RCC -> PLLCFGR) & RCC_PLLCFGR_PLLM;
    if (pllsource == 0x00)
    {
        /* HSI oscillator clock divided by pllmul and multiplicat by pllnul as pllvcoclk output */
        pllvcoclk  = (HSI_VALUE * pllnul) / pllmul;
        if (pllq == 0)
        {
            RCC_Clocks->PLLQ_Frequency = pllvcoclk / 2;
        }
        else
        {
            RCC_Clocks->PLLQ_Frequency = pllvcoclk / (pllq + 1);
        }
        if (pllr == 0)
        {
            RCC_Clocks->PLLR_Frequency = pllvcoclk / 2;
        }
        else
        {
            RCC_Clocks->PLLR_Frequency = pllvcoclk / (pllr + 1);
        }
    }
    else
    {
        /* HSE oscillator clock divided by pllmul and multiplicat by pllnul as pllvcoclk output */
        pllvcoclk  = (HSE_VALUE * pllnul) / pllmul;
        if (pllq == 0)
        {
            RCC_Clocks->PLLQ_Frequency = pllvcoclk / 2;
        }
        else
        {
            RCC_Clocks->PLLQ_Frequency = pllvcoclk / (pllq + 1);
        }
        if (pllr == 0)
        {
            RCC_Clocks->PLLR_Frequency = pllvcoclk / 2;
        }
        else
        {
            RCC_Clocks->PLLR_Frequency = pllvcoclk / (pllr + 1);
        }
    }

    /* Get P2CLK prescaler */
    tmp = RCC->CFGR & RCC_CFGR_PPRE2;
    tmp = tmp >> 11;
    presc2 = APBAHBPrescTable[tmp];
    /* PCLK clock frequency */
    RCC_Clocks->P2CLK_Frequency = ((RCC_Clocks->HCLK_Frequency) >> presc2);
    /* Get PLL2Q and PLL2R clk */
    pll2r      = (((RCC -> PLL2CFGR) & RCC_PLL2CFGR_PLL2R) >> 26);
    pll2q      = (((RCC -> PLL2CFGR) & RCC_PLL2CFGR_PLL2Q) >> 21);
    pll2source = (((RCC -> PLL2CFGR) & RCC_PLL2CFGR_PLL2SRC) >> 14);
    pll2nul    = (((RCC -> PLL2CFGR) & RCC_PLL2CFGR_PLL2N) >> 6);
    pll2mul    = (RCC -> PLL2CFGR) & RCC_PLL2CFGR_PLL2M;
    if (pll2source == 0x00)
    {
        /* HSI oscillator clock divided by pll2mul and multiplicat by pll2nul as pll2vcoclk output */
        pll2vcoclk  = (HSI_VALUE * pll2nul) / pll2mul;
        if (pll2q == 0)
        {
            RCC_Clocks->PLLQ_Frequency = pllvcoclk / 2;
        }
        else
        {
            RCC_Clocks->PLLQ_Frequency = pllvcoclk / (pll2q + 1);
        }
        if (pll2r == 0)
        {
            RCC_Clocks->PLLR_Frequency = pllvcoclk / 2;
        }
        else
        {
            RCC_Clocks->PLLR_Frequency = pllvcoclk / (pll2r + 1);
        }
    }
    else
    {
        /* HSE oscillator clock divided by pll2mul and multiplicat by pll2nul as pll2vcoclk output */
        pll2vcoclk  = (HSE_VALUE * pll2nul) / pll2mul;
        if (pll2q == 0)
        {
            RCC_Clocks->PLLQ_Frequency = pllvcoclk / 2;
        }
        else
        {
            RCC_Clocks->PLLQ_Frequency = pllvcoclk / (pll2q + 1);
        }
        if (pll2r == 0)
        {
            RCC_Clocks->PLLR_Frequency = pllvcoclk / 2;
        }
        else
        {
            RCC_Clocks->PLLR_Frequency = pllvcoclk / (pll2r + 1);
        }
    }

    /* QSPICLK clock frequency */
    if ((RCC->CCIPR & RCC_CCIPR_QSPISEL) == RESET)
    {
        RCC_Clocks->QSPICLK_Frequency = RCC_Clocks->SYSCLK_Frequency ;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_QSPISEL) == RCC_CCIPR_QSPISEL_HSI16)
    {
        RCC_Clocks->QSPICLK_Frequency =  HSI_VALUE;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_QSPISEL) == RCC_CCIPR_QSPISEL_PLLQ)
    {
        RCC_Clocks->QSPICLK_Frequency =  RCC_Clocks->PLLQ_Frequency;
    }

    /* ADCCLK clock frequency */
    if ((RCC->CCIPR & RCC_CCIPR_ADCSEL) == RESET)
    {
        RCC_Clocks->ADCCLK_Frequency = RESET ;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_ADCSEL) == RCC_CCIPR_ADCSEL_PLLR)
    {
        RCC_Clocks->ADCCLK_Frequency =  RCC_Clocks->PLLR_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_ADCSEL) == RCC_CCIPR_ADCSEL_SYS)
    {
        RCC_Clocks->ADCCLK_Frequency =  RCC_Clocks->SYSCLK_Frequency;
    }

    /* CANCLK clock frequency */
    if ((RCC->CCIPR & RCC_CCIPR_CANSEL) == RCC_CCIPR_CANSEL_HD2)
    {
        RCC_Clocks->CANCLK_Frequency = (RCC_Clocks->HCLK_Frequency >> 1);
    }
    else if ((RCC->CCIPR & RCC_CCIPR_CANSEL) == RCC_CCIPR_CANSEL_HD4)
    {
        RCC_Clocks->CANCLK_Frequency = (RCC_Clocks->HCLK_Frequency >> 2);
    }
    else if ((RCC->CCIPR & RCC_CCIPR_CANSEL) == RCC_CCIPR_CANSEL_HD8)
    {
        RCC_Clocks->CANCLK_Frequency = (RCC_Clocks->HCLK_Frequency >> 3);
    }
    else if ((RCC->CCIPR & RCC_CCIPR_CANSEL) == RCC_CCIPR_CANSEL_HD16)
    {
        RCC_Clocks->CANCLK_Frequency = (RCC_Clocks->HCLK_Frequency >> 4);
    }
    else if ((RCC->CCIPR & RCC_CCIPR_CANSEL) == RCC_CCIPR_CANSEL_HD32)
    {
        RCC_Clocks->CANCLK_Frequency = (RCC_Clocks->HCLK_Frequency >> 5);
    }
    else
    {
        RCC_Clocks->CANCLK_Frequency =  RCC_Clocks->HCLK_Frequency;
    }

    /* LPTIMCLK clock frequency */
    if ((RCC->CCIPR & RCC_CCIPR_LPTIMSEL) == RCC_CCIPR_LPTIMSEL_PCLK)
    {
        RCC_Clocks->LPTIMCLK_Frequency = RCC_Clocks->PCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_LPTIMSEL) == RCC_CCIPR_LPTIMSEL_LSI)
    {
        RCC_Clocks->LPTIMCLK_Frequency = LSI_VALUE;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_LPTIMSEL) == RCC_CCIPR_LPTIMSEL_HSI16)
    {
        RCC_Clocks->LPTIMCLK_Frequency = HSI_VALUE;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_LPTIMSEL) == RCC_CCIPR_LPTIMSEL_LSE)
    {
        RCC_Clocks->LPTIMCLK_Frequency = LSE_VALUE;
    }

    /* I2C3CLK clock frequency */
    if ((RCC->CCIPR & RCC_CCIPR_I2C3SEL) == RCC_CCIPR_I2C3SEL_PCLK)
    {
        RCC_Clocks->I2C3CLK_Frequency = RCC_Clocks->PCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_I2C3SEL) == RCC_CCIPR_I2C3SEL_SYS)
    {
        RCC_Clocks->I2C3CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_I2C3SEL) == RCC_CCIPR_I2C3SEL_HSI16)
    {
        RCC_Clocks->I2C3CLK_Frequency = HSI_VALUE;
    }

    /* I2C2CLK clock frequency */
    if ((RCC->CCIPR & RCC_CCIPR_I2C2SEL) == RCC_CCIPR_I2C2SEL_PCLK)
    {
        RCC_Clocks->I2C2CLK_Frequency = RCC_Clocks->PCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_I2C2SEL) == RCC_CCIPR_I2C2SEL_SYS)
    {
        RCC_Clocks->I2C2CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_I2C2SEL) == RCC_CCIPR_I2C2SEL_HSI16)
    {
        RCC_Clocks->I2C2CLK_Frequency = HSI_VALUE;
    }

    /* I2C1CLK clock frequency */
    if ((RCC->CCIPR & RCC_CCIPR_I2C1SEL) == RCC_CCIPR_I2C1SEL_PCLK)
    {
        RCC_Clocks->I2C1CLK_Frequency = RCC_Clocks->PCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_I2C1SEL) == RCC_CCIPR_I2C1SEL_SYS)
    {
        RCC_Clocks->I2C1CLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_I2C1SEL) == RCC_CCIPR_I2C1SEL_HSI16)
    {
        RCC_Clocks->I2C1CLK_Frequency = HSI_VALUE;
    }

    /* LPUARTCLK clock frequency */
    if ((RCC->CCIPR & RCC_CCIPR_LPUARTSEL) == RCC_CCIPR_LPUARTSEL_PCLK)
    {
        RCC_Clocks->LPUARTCLK_Frequency = RCC_Clocks->PCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_LPUARTSEL) == RCC_CCIPR_LPUARTSEL_LSE)
    {
        RCC_Clocks->LPUARTCLK_Frequency = LSE_VALUE;
    }

    /* PWMCLK clock frequency */
    if ((RCC->CCIPR & RCC_CCIPR_PWMSEL) == RCC_CCIPR_PWMSEL_SYS)
    {
        RCC_Clocks->PWMCLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_PWMSEL) == RCC_CCIPR_PWMSEL_SYSD2)
    {
        RCC_Clocks->PWMCLK_Frequency = (RCC_Clocks->SYSCLK_Frequency >> 1);
    }
    else if ((RCC->CCIPR & RCC_CCIPR_PWMSEL) == RCC_CCIPR_PWMSEL_SYSD4)
    {
        RCC_Clocks->PWMCLK_Frequency = (RCC_Clocks->SYSCLK_Frequency >> 2);
    }

    /* EQEPCLK clock frrequency */
    if ((RCC->CCIPR & RCC_CCIPR_EQEPSEL) == RCC_CCIPR_EQEPSEL_SYS)
    {
        RCC_Clocks->EQEPCLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_EQEPSEL) == RCC_CCIPR_EQEPSEL_SYSD2)
    {
        RCC_Clocks->EQEPCLK_Frequency = (RCC_Clocks->SYSCLK_Frequency >> 1);
    }
    else if ((RCC->CCIPR & RCC_CCIPR_EQEPSEL) == RCC_CCIPR_EQEPSEL_SYSD4)
    {
        RCC_Clocks->EQEPCLK_Frequency = (RCC_Clocks->SYSCLK_Frequency >> 2);
    }

    /* ECAPCLK clock frrequency */
    if ((RCC->CCIPR & RCC_CCIPR_ECAPSEL) == RCC_CCIPR_ECAPSEL_SYS)
    {
        RCC_Clocks->ECAPCLK_Frequency = RCC_Clocks->SYSCLK_Frequency;
    }
    else if ((RCC->CCIPR & RCC_CCIPR_ECAPSEL) == RCC_CCIPR_ECAPSEL_SYSD2)
    {
        RCC_Clocks->ECAPCLK_Frequency = (RCC_Clocks->SYSCLK_Frequency >> 1);
    }
    else if ((RCC->CCIPR & RCC_CCIPR_ECAPSEL) == RCC_CCIPR_ECAPSEL_SYSD4)
    {
        RCC_Clocks->ECAPCLK_Frequency = (RCC_Clocks->SYSCLK_Frequency >> 2);
    }

    /* I2SCLK clock frequency */
    if ((RCC->CCIPR & RCC_CCIPR_I2SSEL) == RESET)
    {
        RCC_Clocks->I2SCLK_Frequency = RCC_Clocks->PLL2Q_Frequency;
    }
    else
    {
        RCC_Clocks->I2SCLK_Frequency = ((uint32_t)0x00000000);//I2S_CKIN;
    }
}
/**
  * @}
  */

/**
  * @brief  Configures the LSCO clock (LSCOCLK).
  * @note   As the LSCO clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using PWR_BackupAccessCmd(ENABLE) function before to configure
  *         the LSCO clock source (to be done once after reset).
  * @param  RCC_LSCOCLKSource: specifies the LSCO clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_LSCOCLK_LSE: LSE selected as LSCO clock
  *            @arg RCC_LSCOCLK_LSI: LSI selected as LSCO clock
  * @retval None
  */
void RCC_LSCOCLKConfig(uint32_t RCC_LSCOCLKSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_LSCOCLK_SRC(RCC_LSCOCLKSource));

    /* Select the LSCO clock source */
    RCC->BDCR |= RCC_LSCOCLKSource;
}

/**
  * @brief  Enables or disables the LSCO clock.
  * @note   This function must be used only after the LSCO clock source was selected
  *         using the RCC_LSCOCLKConfig function.
  * @param  NewState: new state of the RTC clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_LSCOCLKCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->BDCR |=  RCC_LSCOCLK_ON;
    }
    else
    {
        RCC->BDCR &= ~RCC_LSCOCLK_ON;
    }
}

/**
  * @brief  Configures the RTC clock (RTCCLK).
  * @note   As the RTC clock configuration bits are in the Backup domain and write
  *         access is denied to this domain after reset, you have to enable write
  *         access using PWR_BackupAccessCmd(ENABLE) function before to configure
  *         the RTC clock source (to be done once after reset).
  * @note   Once the RTC clock is configured it can't be changed unless the RTC
  *         is reset using RCC_BackupResetCmd function, or by a Power On Reset (POR)
  * @param  RCC_RTCCLKSource: specifies the RTC clock source.
  *          This parameter can be one of the following values:
  *            @arg RCC_RTCCLKSource_LSE: LSE selected as RTC clock
  *            @arg RCC_RTCCLKSource_LSI: LSI selected as RTC clock
  *            @arg RCC_RTCCLKSource_HSE_Div32: HSE divided by 32 selected as RTC clock
  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
  *         work in STOP and STANDBY modes, and can be used as wakeup source.
  *         However, when the HSE clock is used as RTC clock source, the RTC
  *         cannot be used in STOP and STANDBY modes.
  * @note   The maximum input clock frequency for RTC is 2MHz (when using HSE as
  *         RTC clock source).
  * @retval None
  */
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource)
{
    /* Check the parameters */
    assert_param(IS_RCC_RTCCLK_SOURCE(RCC_RTCCLKSource));

    /* Select the RTC clock source */
    RCC->BDCR |= RCC_RTCCLKSource;
}

/**
  * @brief  Enables or disables the RTC clock.
  * @note   This function must be used only after the RTC clock source was selected
  *         using the RCC_RTCCLKConfig function.
  * @param  NewState: new state of the RTC clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCCLKCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->BDCR |=  RCC_BDCR_RTCEN;
    }
    else
    {
        RCC->BDCR &= ~RCC_BDCR_RTCEN;
    }
}

/**
  * @brief  Forces or releases the Backup domain reset.
  * @note   This function resets the RTC peripheral (including the backup registers)
  *         and the RTC clock source selection in RCC_BDCR register.
  * @param  NewState: new state of the Backup domain reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_BackupResetCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->BDCR |=  RCC_BDCR_BDRST;
    }
    else
    {
        RCC->BDCR &= ~RCC_BDCR_BDRST;
    }
}

/**
  * @brief  Enables or disables the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @param  RCC_AHB1Periph: specifies the AHB1 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_AHB1Periph_USBOTGHS: USBOTGHS clock
  *            @arg RCC_AHB1Periph_ETHMACPTP: ETHMACPTP clock
  *            @arg RCC_AHB1Periph_ETHMACRX: ETHMACRX clock
  *            @arg RCC_AHB1Periph_ETHMACTX: ETHMACTX clock
  *            @arg RCC_AHB1Periph_ETHMAC: ETHMAC clock
  *            @arg RCC_AHB1Periph_DMA2: DMA2 clock
  *            @arg RCC_AHB1Periph_DMA1: DMA1 clock
  *            @arg RCC_AHB1Periph_CCMDATARAM: CCMDATARAM clock
  *            @arg RCC_AHB1Periph_BKPSRAM: BKPSRAM clock
  *            @arg RCC_AHB1Periph_CRC: CRC clock
  *            @arg RCC_AHB1Periph_GPIOH: GPIOH clock
  *            @arg RCC_AHB1Periph_GPIOE: GPIOE clock
  *            @arg RCC_AHB1Periph_GPIOD: GPIOD clock
  *            @arg RCC_AHB1Periph_GPIOC: GPIOC clock
  *            @arg RCC_AHB1Periph_GPIOB: GPIOB clock
  *            @arg RCC_AHB1Periph_GPIOA: GPIOA clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB1_PERIPH(RCC_AHB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHB1ENR |=  RCC_AHB1Periph;
        volatile uint32_t tmpreg = RCC->AHB1ENR;
        (void)tmpreg;
    }
    else
    {
        RCC->AHB1ENR &= ~RCC_AHB1Periph;
    }
}

/**
  * @brief  Enables or disables the AHB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @param  RCC_AHB2Periph: specifies the AHB2 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_AHB2Periph_USBOTGFS: USBOTGFS clock
  *            @arg RCC_AHB2Periph_RNG: RNG clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHB2PeriphClockCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB2_PERIPH(RCC_AHB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHB2ENR |=  RCC_AHB2Periph;
        volatile uint32_t tmpreg = RCC->AHB2ENR;
        (void)tmpreg;
    }
    else
    {
        RCC->AHB2ENR &= ~RCC_AHB2Periph;
    }
}

/**
  * @brief  Enables or disables the AHB3 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @param  RCC_AHB3Periph: specifies the AHB3 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_AHB3Periph_QSPI: QSPI clock
  *            @arg RCC_AHB3Periph_FMC: FMC clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHB3PeriphClockCmd(uint32_t RCC_AHB3Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB3_PERIPH(RCC_AHB3Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHB3ENR |=  RCC_AHB3Periph;
        volatile uint32_t tmpreg = RCC->AHB3ENR;
        (void)tmpreg;
    }
    else
    {
        RCC->AHB3ENR &= ~RCC_AHB3Periph;
    }
}

/**
  * @brief  Enables or disables the High Speed APB (APB1) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @param  RCC_APB1Periph: specifies the APB1 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_APB1Periph_USART7: USART7 clock
  *             @arg RCC_APB1Periph_RAMP: RAMP clock
  *             @arg RCC_APB1Periph_DAC: DAC clock
  *             @arg RCC_APB1Periph_PWR: PWR clock
  *             @arg RCC_APB1Periph_CAN4: CAN4 clock
  *             @arg RCC_APB1Periph_CAN3: CAN3 clock
  *             @arg RCC_APB1Periph_CAN2: CAN2 clock
  *             @arg RCC_APB1Periph_CAN1: CAN1 clock
  *             @arg RCC_APB1Periph_I2C3: I2C3 clock
  *             @arg RCC_APB1Periph_I2C2: I2C2 clock
  *             @arg RCC_APB1Periph_I2C1: I2C1 clock
  *             @arg RCC_APB1Periph_UART5: UART5 clock
  *             @arg RCC_APB1Periph_UART4: UART4 clock
  *             @arg RCC_APB1Periph_UART3: UART3 clock
  *             @arg RCC_APB1Periph_UART2: UART2 clock
  *             @arg RCC_APB1Periph_LPUART: LPUART clock
  *             @arg RCC_APB1Periph_SPI3: SPI3 clock
  *             @arg RCC_APB1Periph_SPI2: SPI2 clock
  *             @arg RCC_APB1Periph_I2S3: I2S3 clock
  *             @arg RCC_APB1Periph_I2S2: I2S2 clock
  *             @arg RCC_APB1Periph_WWDG: WWDG clock
  *             @arg RCC_APB1Periph_AC97: AC97 clock
  *             @arg RCC_APB1Periph_CRS: CRS clock
  *             @arg RCC_APB1Periph_TIM14: TIM14 clock
  *             @arg RCC_APB1Periph_TIM13: TIM13 clock
  *             @arg RCC_APB1Periph_TIM12: TIM12 clock
  *             @arg RCC_APB1Periph_TIM7: TIM7 clock
  *             @arg RCC_APB1Periph_TIM6: TIM6 clock
  *             @arg RCC_APB1Periph_TIM5: TIM5 clock
  *             @arg RCC_APB1Periph_TIM4: TIM4 clock
  *             @arg RCC_APB1Periph_TIM3: TIM3 clock
  *             @arg RCC_APB1Periph_TIM2: TIM2 clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1_PERIPH(RCC_APB1Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB1ENR |=  RCC_APB1Periph;
        volatile uint32_t tmpreg = RCC->APB1ENR;
        (void)tmpreg;
    }
    else
    {
        RCC->APB1ENR &= ~RCC_APB1Periph;
    }
}

/**
  * @brief  Enables or disables the Low Speed APB (APB2) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before
  *         using it.
  * @param  RCC_APB2Periph: specifies the APB2 peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *           @arg RCC_APB2Periph_TBCLK: TBCLK clock
  *           @arg RCC_APB2Periph_EQEP: EQEP clock
  *           @arg RCC_APB2Periph_ECAP: ECAP clock
  *           @arg RCC_APB2Periph_EPWM4: EPWM4 clock
  *           @arg RCC_APB2Periph_EPWM3: EPWM3 clock
  *           @arg RCC_APB2Periph_EPWM2: EPWM2 clock
  *           @arg RCC_APB2Periph_EPWM1: EPWM1 clock
  *           @arg RCC_APB2Periph_TIM11: TIM11 clock
  *           @arg RCC_APB2Periph_TIM10: TIM10 clock
  *           @arg RCC_APB2Periph_TIM9: TIM9 clock
  *           @arg RCC_APB2Periph_LPTIM: LPTIM clock
  *           @arg RCC_APB2Periph_SYSCFG: SYSCFG clock
  *           @arg RCC_APB2Periph_SPI1: SPI1 clock
  *           @arg RCC_APB2Periph_SDIO: SDIO clock
  *           @arg RCC_APB2Periph_SPD: SPD clock
  *           @arg RCC_APB2Periph_ADC: ADC clock
  *           @arg RCC_APB2Periph_USART6: USART6 clock
  *           @arg RCC_APB2Periph_USART1: USART1 clock
  *           @arg RCC_APB2Periph_TIM8: TIM8 clock
  *           @arg RCC_APB2Periph_TIM1: TIM1 clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB2ENR |=  RCC_APB2Periph;
        volatile uint32_t tmpreg = RCC->APB2ENR;
        (void)tmpreg;
    }
    else
    {
        RCC->APB2ENR &= ~RCC_APB2Periph;
    }
}

/**
  * @brief  Enables or disables the AHB1 peripheral low-power clock.
  * @note   while enter sleep, want periph will work contiue, shoule enable
  *         this periph's lpen.
  * @param  RCC_AHB1PeriphLpen: specifies the AHB1 peripheral low-power to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_AHB1PeriphLpen_USBOTGHS: USBOTGHS low-power clock
  *            @arg RCC_AHB1PeriphLpen_ETHMACPTP: ETHMACPTP low-power clock
  *            @arg RCC_AHB1PeriphLpen_ETHMACRX: ETHMACRX low-power clock
  *            @arg RCC_AHB1PeriphLpen_ETHMACTX: ETHMACTX low-power clock
  *            @arg RCC_AHB1PeriphLpen_ETHMAC: ETHMAC low-power clock
  *            @arg RCC_AHB1PeriphLpen_DMA2: DMA2 low-power clock
  *            @arg RCC_AHB1PeriphLpen_DMA1: DMA1 low-power clock
  *            @arg RCC_AHB1PeriphLpen_CCMDATARAM: CCMDATARAM low-power clock
  *            @arg RCC_AHB1PeriphLpen_BKPSRAM: BKPSRAM low-power clock
  *            @arg RCC_AHB1PeriphLpen_CRC: CRC low-power clock
  *            @arg RCC_AHB1PeriphLpen_GPIOH: GPIOH low-power clock
  *            @arg RCC_AHB1PeriphLpen_GPIOE: GPIOE low-power clock
  *            @arg RCC_AHB1PeriphLpen_GPIOD: GPIOD low-power clock
  *            @arg RCC_AHB1PeriphLpen_GPIOC: GPIOC low-power clock
  *            @arg RCC_AHB1PeriphLpen_GPIOB: GPIOB low-power clock
  *            @arg RCC_AHB1PeriphLpen_GPIOA: GPIOA low-power clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHB1PeriphLpenCmd(uint32_t RCC_AHB1PeriphLpen, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB1LP_PERIPH(RCC_AHB1PeriphLpen));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHB1LPENR |=  RCC_AHB1PeriphLpen;
    }
    else
    {
        RCC->AHB1LPENR &= ~RCC_AHB1PeriphLpen;
    }
}

/**
  * @brief  Enables or disables the AHB2 peripheral low-power clock.
  * @note   while enter sleep, want periph will work contiue, shoule enable
  *         this periph's lpen.
  * @param  RCC_AHB2PeriphLpen: specifies the AHB2 peripheral low-power to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_AHB2PeriphLpen_USBOTGFS: USBOTGFS low-power clock
  *            @arg RCC_AHB2PeriphLpen_RNG: RNG low-power clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHB2PeriphLpenCmd(uint32_t RCC_AHB2PeriphLpen, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB2LP_PERIPH(RCC_AHB2PeriphLpen));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHB2LPENR |=  RCC_AHB2PeriphLpen;
    }
    else
    {
        RCC->AHB2LPENR &= ~RCC_AHB2PeriphLpen;
    }
}

/**
  * @brief  Enables or disables the AHB3 peripheral low-power clock.
  * @note   while enter sleep, want periph will work contiue, shoule enable
  *         this periph's lpen.
  * @param  RCC_AHB3PeriphLpen: specifies the AHB3 peripheral low-power to gates its clock.
  *          This parameter can be any combination of the following values:
  *            @arg RCC_AHB3PeriphLpen_QSPI: QSPI low-power clock
  *            @arg RCC_AHB3PeriphLpen_FMC: FMC low-power clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHB3PeriphLpenCmd(uint32_t RCC_AHB3PeriphLpen, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB2LP_PERIPH(RCC_AHB3PeriphLpen));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHB3LPENR |=  RCC_AHB3PeriphLpen;
    }
    else
    {
        RCC->AHB3LPENR &= ~RCC_AHB3PeriphLpen;
    }
}

/**
  * @brief  Enables or disables the High Speed APB (APB1) peripheral low-power clock.
  * @note   while enter sleep, want periph will work contiue, shoule enable
  *         this periph's lpen.
  * @param  RCC_APB1PeriphLpen: specifies the APB1 peripheral low-power to gates its clock.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_APB1PeriphLpen_UART7: UART7 low-power clock
  *             @arg RCC_APB1PeriphLpen_RAMP: RAMP low-power clock
  *             @arg RCC_APB1PeriphLpen_DAC: DAC low-power clock
  *             @arg RCC_APB1PeriphLpen_PWR: PWR low-power clock
  *             @arg RCC_APB1PeriphLpen_CAN4: CAN4 low-power clock
  *             @arg RCC_APB1PeriphLpen_CAN3: CAN3 low-power clock
  *             @arg RCC_APB1PeriphLpen_CAN2: CAN2 low-power clock
  *             @arg RCC_APB1PeriphLpen_CAN1: CAN1 low-power clock
  *             @arg RCC_APB1PeriphLpen_I2C3: I2C3 low-power clock
  *             @arg RCC_APB1PeriphLpen_I2C2: I2C2 low-power clock
  *             @arg RCC_APB1PeriphLpen_I2C1: I2C1 low-power clock
  *             @arg RCC_APB1PeriphLpen_UART5: UART5 low-power clock
  *             @arg RCC_APB1PeriphLpen_UART4: UART4 low-power clock
  *             @arg RCC_APB1PeriphLpen_UART3: UART3 low-power clock
  *             @arg RCC_APB1PeriphLpen_UART2: UART2 low-power clock
  *             @arg RCC_APB1PeriphLpen_LPUART: LPUART low-power clock
  *             @arg RCC_APB1PeriphLpen_SPI3: SPI3 low-power clock
  *             @arg RCC_APB1PeriphLpen_SPI2: SPI2 low-power clock
  *             @arg RCC_APB1PeriphLpen_I2S3: I2S3 low-power clock
  *             @arg RCC_APB1PeriphLpen_I2S2: I2S2 low-power clock
  *             @arg RCC_APB1PeriphLpen_WWDG: WWDG low-power clock
  *             @arg RCC_APB1PeriphLpen_AC97: AC97 low-power clock
  *             @arg RCC_APB1PeriphLpen_CRS: CRS low-power clock
  *             @arg RCC_APB1PeriphLpen_TIM14: TIM14 low-power clock
  *             @arg RCC_APB1PeriphLpen_TIM13: TIM13 low-power clock
  *             @arg RCC_APB1PeriphLpen_TIM12: TIM12 low-power clock
  *             @arg RCC_APB1PeriphLpen_TIM7: TIM7 low-power clock
  *             @arg RCC_APB1PeriphLpen_TIM6: TIM6 low-power clock
  *             @arg RCC_APB1PeriphLpen_TIM5: TIM5 low-power clock
  *             @arg RCC_APB1PeriphLpen_TIM4: TIM4 low-power clock
  *             @arg RCC_APB1PeriphLpen_TIM3: TIM3 low-power clock
  *             @arg RCC_APB1PeriphLpen_TIM2: TIM2 low-power clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphLpenCmd(uint32_t RCC_APB1PeriphLpen, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1LP_PERIPH(RCC_APB1PeriphLpen));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB1LPENR |=  RCC_APB1PeriphLpen;
    }
    else
    {
        RCC->APB1LPENR &= ~RCC_APB1PeriphLpen;
    }
}

/**
  * @brief  Enables or disables the Low Speed APB (APB2) peripheral low-power clock.
  * @note   while enter sleep, want periph will work contiue, shoule enable
  *         this periph's lpen.
  * @param  RCC_APB2PeriphLpen: specifies the APB2 peripheral low-power to gates its clock.
  *          This parameter can be any combination of the following values:
  *           @arg RCC_APB2PeriphLpen_TBCLK: TBCLK low-power clock
  *           @arg RCC_APB2PeriphLpen_EQEP: EQEP low-power clock
  *           @arg RCC_APB2PeriphLpen_ECAP: ECAP low-power clock
  *           @arg RCC_APB2PeriphLpen_EPWM4: EPWM4 low-power clock
  *           @arg RCC_APB2PeriphLpen_EPWM3: EPWM3 low-power clock
  *           @arg RCC_APB2PeriphLpen_EPWM2: EPWM2 low-power clock
  *           @arg RCC_APB2PeriphLpen_EPWM1: EPWM1 low-power clock
  *           @arg RCC_APB2PeriphLpen_TIM11: TIM11 low-power clock
  *           @arg RCC_APB2PeriphLpen_TIM10: TIM10 low-power clock
  *           @arg RCC_APB2PeriphLpen_TIM9: TIM9 low-power clock
  *           @arg RCC_APB2PeriphLpen_LPTIM: LPTIM low-power clock
  *           @arg RCC_APB2PeriphLpen_SYSCFG: SYSCFG low-power clock
  *           @arg RCC_APB2PeriphLpen_SPI1: SPI1 low-power clock
  *           @arg RCC_APB2PeriphLpen_SDIO: SDIO low-power clock
  *           @arg RCC_APB2PeriphLpen_SPD: SPD low-power clock
  *           @arg RCC_APB2PeriphLpen_ADC: ADC low-power clock
  *           @arg RCC_APB2PeriphLpen_USART6: USART6 low-power clock
  *           @arg RCC_APB2PeriphLpen_USART1: USART1 low-power clock
  *           @arg RCC_APB2PeriphLpen_TIM8: TIM8 low-power clock
  *           @arg RCC_APB2PeriphLpen_TIM1: TIM1 low-power clock
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphLpenCmd(uint32_t RCC_APB2PeriphLpen, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB2LP_PERIPH(RCC_APB2PeriphLpen));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB2LPENR |=  RCC_APB2PeriphLpen;
    }
    else
    {
        RCC->APB2LPENR &= ~RCC_APB2PeriphLpen;
    }
}

/**
  * @brief  Forces or releases AHB1 peripheral reset.
  * @param  RCC_AHB1PeriphRst: specifies the AHB1 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *           @arg RCC_AHB1PeriphRst_USBOTGHS: USBOTGHS reset
  *           @arg RCC_AHB1PeriphRst_ETHMAC: ETHMAC reset
  *           @arg RCC_AHB1PeriphRst_DMA2: DMA2 reset
  *           @arg RCC_AHB1PeriphRst_DMA1: DMA1 reset
  *           @arg RCC_AHB1PeriphRst_CRC: CRC reset
  *           @arg RCC_AHB1PeriphRst_GPIOH: GPIOH reset
  *           @arg RCC_AHB1PeriphRst_GPIOE: GPIOE reset
  *           @arg RCC_AHB1PeriphRst_GPIOD: GPIOD reset
  *           @arg RCC_AHB1PeriphRst_GPIOC: GPIOC reset
  *           @arg RCC_AHB1PeriphRst_GPIOB: GPIOB reset
  *           @arg RCC_AHB1PeriphRst_GPIOA: GPIOA reset
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHB1PeriphResetCmd(uint32_t RCC_AHB1PeriphRst, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB1RST_PERIPH(RCC_AHB1PeriphRst));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHB1RSTR |=  RCC_AHB1PeriphRst;
    }
    else
    {
        RCC->AHB1RSTR &= ~RCC_AHB1PeriphRst;
    }
}

/**
  * @brief  Forces or releases AHB2 peripheral reset.
  * @param  RCC_AHB2PeriphRst: specifies the AHB2 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *           @arg RCC_AHB2PeriphRst_USBOTGFS: USBOTGFS reset
  *           @arg RCC_AHB2PeriphRst_RNG: RNG reset
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHB2PeriphResetCmd(uint32_t RCC_AHB2PeriphRst, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB2RST_PERIPH(RCC_AHB2PeriphRst));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHB2RSTR |=  RCC_AHB2PeriphRst;
    }
    else
    {
        RCC->AHB2RSTR &= ~RCC_AHB2PeriphRst;
    }
}

/**
  * @brief  Forces or releases AHB3 peripheral reset.
  * @param  RCC_AHB3PeriphRst: specifies the AHB3 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *           @arg RCC_AHB3PeriphRst_QSPI: QSPI reset
  *           @arg RCC_AHB3PeriphRst_FMC: FMC reset
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHB3PeriphResetCmd(uint32_t RCC_AHB3PeriphRst, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_AHB3RST_PERIPH(RCC_AHB3PeriphRst));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->AHB3RSTR |=  RCC_AHB3PeriphRst;
    }
    else
    {
        RCC->AHB3RSTR &= ~RCC_AHB3PeriphRst;
    }
}

/**
  * @brief  Forces or releases High Speed APB (APB1) peripheral reset.
  * @param  RCC_APB1PeriphRst: specifies the APB1 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_APB1PeriphRst_UART7: UART7 reset
  *             @arg RCC_APB1PeriphRst_DAC: DAC reset
  *             @arg RCC_APB1PeriphRst_PWR: PWR reset
  *             @arg RCC_APB1PeriphRst_CAN4: CAN4 reset
  *             @arg RCC_APB1PeriphRst_CAN3: CAN3 reset
  *             @arg RCC_APB1PeriphRst_CAN2: CAN2 reset
  *             @arg RCC_APB1PeriphRst_CAN1: CAN1 reset
  *             @arg RCC_APB1PeriphRst_I2C3: I2C3 reset
  *             @arg RCC_APB1PeriphRst_I2C2: I2C2 reset
  *             @arg RCC_APB1PeriphRst_I2C1: I2C1 reset
  *             @arg RCC_APB1PeriphRst_UART5: UART5 reset
  *             @arg RCC_APB1PeriphRst_UART4: UART4 reset
  *             @arg RCC_APB1PeriphRst_UART3: UART3 reset
  *             @arg RCC_APB1PeriphRst_UART2: UART2 reset
  *             @arg RCC_APB1PeriphRst_LPUART: LPUART reset
  *             @arg RCC_APB1PeriphRst_SPI3: SPI3 reset
  *             @arg RCC_APB1PeriphRst_SPI2: SPI2 reset
  *             @arg RCC_APB1PeriphRst_I2S3: I2S3 reset
  *             @arg RCC_APB1PeriphRst_I2S2: I2S2 reset
  *             @arg RCC_APB1PeriphRst_WWDG: WWDG reset
  *             @arg RCC_APB1PeriphRst_AC97: AC97 reset
  *             @arg RCC_APB1PeriphRst_CRS: CRS reset
  *             @arg RCC_APB1PeriphRst_TIM14: TIM14 reset
  *             @arg RCC_APB1PeriphRst_TIM13: TIM13 reset
  *             @arg RCC_APB1PeriphRst_TIM12: TIM12 reset
  *             @arg RCC_APB1PeriphRst_TIM7: TIM7 reset
  *             @arg RCC_APB1PeriphRst_TIM6: TIM6 reset
  *             @arg RCC_APB1PeriphRst_TIM5: TIM5 reset
  *             @arg RCC_APB1PeriphRst_TIM4: TIM4 reset
  *             @arg RCC_APB1PeriphRst_TIM3: TIM3 reset
  *             @arg RCC_APB1PeriphRst_TIM2: TIM2 reset
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1PeriphRst, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB1RST_PERIPH(RCC_APB1PeriphRst));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB1RSTR |=  RCC_APB1PeriphRst;
    }
    else
    {
        RCC->APB1RSTR &= ~RCC_APB1PeriphRst;
    }
}

/**
  * @brief  Forces or releases High Speed APB (APB2) peripheral reset.
  * @param  RCC_APB2PeriphRst: specifies the APB2 peripheral to reset.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_APB2PeriphRst_EQEP: EQEP reset
  *             @arg RCC_APB2PeriphRst_ECAP: ECAP reset
  *             @arg RCC_APB2PeriphRst_EPWM4: EPWM4 reset
  *             @arg RCC_APB2PeriphRst_EPWM3: EPWM3 reset
  *             @arg RCC_APB2PeriphRst_EPWM2: EPWM2 reset
  *             @arg RCC_APB2PeriphRst_EPWM1: EPWM1 reset
  *             @arg RCC_APB2PeriphRst_TIM11: TIM11 reset
  *             @arg RCC_APB2PeriphRst_TIM10: TIM10 reset
  *             @arg RCC_APB2PeriphRst_TIM9: TIM9 reset
  *             @arg RCC_APB2PeriphRst_LPTIM: LPTIM reset
  *             @arg RCC_APB2PeriphRst_SYSCFG: SYSCFG reset
  *             @arg RCC_APB2PeriphRst_SPI1: SPI1 reset
  *             @arg RCC_APB2PeriphRst_SDIO: SDIO reset
  *             @arg RCC_APB2PeriphRst_SPD: SPD reset
  *             @arg RCC_APB2PeriphRst_ADC: ADC reset
  *             @arg RCC_APB2PeriphRst_USART6: USART6 reset
  *             @arg RCC_APB2PeriphRst_USART1: USART1 reset
  *             @arg RCC_APB2PeriphRst_TIM8: TIM8 reset
  *             @arg RCC_APB2PeriphRst_TIM1: TIM1 reset
  * @param  NewState: new state of the specified peripheral reset.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2PeriphRst, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_APB2RST_PERIPH(RCC_APB2PeriphRst));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        RCC->APB2RSTR |=  RCC_APB2PeriphRst;
    }
    else
    {
        RCC->APB2RSTR &= ~RCC_APB2PeriphRst;
    }
}
/**
  * @}
  */

/**
  * @brief  Checks whether the specified RCC flag is set or not.
  * @param  RCC_FLAG_REG: the flag in which register.
  *          This parameter can be one of the following values:
  *             @arg RCC_FLAG_REG_CR:  The flag in cr register
  *             @arg RCC_FLAG_REG_CR2: The flag in cr2 register
  *             @arg RCC_FLAG_REG_BDCR:The flag in bdcr register
  *             @arg RCC_FLAG_REG_CSR: The flag in csr register
  * @param  RCC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *             @arg RCC_FLAG_PLL2RDY: PLL2 clock ready
  *             @arg RCC_FLAG_PLLRDY:  PLL clock ready
  *             @arg RCC_FLAG_HSERDY:  HSE oscillator clock ready
  *             @arg RCC_FLAG_HSIRDY:  HSI oscillator clock ready
  *             @arg RCC_FLAG_HSI48RDY:HSI48 oscillator clock ready
  *             @arg RCC_FLAG_LSERDY:  LSE oscillator clock ready
  *             @arg RCC_FLAG_LPWRRST: Low Power reset
  *             @arg RCC_FLAG_WWDGRST: Window Watchdog reset
  *             @arg RCC_FLAG_IWDGRST: Independent Watchdog reset
  *             @arg RCC_FLAG_SFTRST:  Software reset
  *             @arg RCC_FLAG_PORRST:  POR/PDR reset
  *             @arg RCC_FLAG_PINRST:  Pin reset
  *             @arg RCC_FLAG_RMVF:    Remove all reset flag
  *             @arg RCC_FLAG_LSIRDY:  LSI oscillator clock ready
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG_REG, uint32_t RCC_FLAG)
{
    uint8_t  tmp = 0;
    uint32_t statusreg = 0;
    FlagStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_RCC_FLAG_REG(RCC_FLAG_REG));
    assert_param(IS_RCC_FLAG(RCC_FLAG));

    /* Get the RCC register index */
    tmp = RCC_FLAG_REG;

    if (tmp == 0)               /* The flag to check is in CR register */
    {
        statusreg = RCC->CR;
    }
    else if (tmp == 1)          /* The flag to check is in CR2 register */
    {
        statusreg = RCC->CR2;
    }
    else if (tmp == 2)          /* The flag to check is in BDCR register */
    {
        statusreg = RCC->BDCR;
    }
    else                        /* The flag to check is in CSR register */
    {
        statusreg = RCC->CSR;
    }

    if ((statusreg & RCC_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the flag status */
    return bitstatus;
}

/**
  * @brief  Clears the RCC reset flags.
  *         The reset flags are: RCC_FLAG_PINRSTF, RCC_FLAG_PORRSTF, RCC_FLAG_SFTRSTF,
  *         RCC_FLAG_IWDGRSTF, RCC_FLAG_WWDGRSTF, RCC_FLAG_LPWRRSTF.
  * @param  None
  * @retval None
  */
void RCC_ClrRstFlag(void)
{
    /* Set RMVF bit to clear the reset flags */
    RCC->CSR |= RCC_CSR_RMVF;
}

/**
  * @brief  Enables or disables the specified RCC interrupts.
  * @note   The CSS interrupt doesn't have an enable bit; once the CSS is enabled
  *         and if the HSE clock fails, the CSS interrupt occurs and an NMI is
  *         automatically generated. The NMI will be executed indefinitely, and
  *         since NMI has higher priority than any other IRQ (and main program)
  *         the application will be stacked in the NMI ISR unless the CSS interrupt
  *         pending bit is cleared.
  * @param  RCC_IT: specifies the RCC interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *              @arg RCC_ITEN_PLL2RDY: PLL2 ready interrupt enable
  *              @arg RCC_ITEN_PLLRDY: PLL ready interrupt enable
  *              @arg RCC_ITEN_HSERDY: HSE ready interrupt enable
  *              @arg RCC_ITEN_HSI48RDY: HSI48 ready interrupt enable
  *              @arg RCC_ITEN_HSIRDY: HSI ready interrupt enable
  *              @arg RCC_ITEN_LSERDY: LSE ready interrupt enable
  *              @arg RCC_ITEN_LSIRDY: LSI ready interrupt enable
  * @param  NewState: new state of the specified RCC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_ITConfig(uint32_t RCC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RCC_ITEN(RCC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* enable the selected interrupts */
        RCC->CIR |=  RCC_IT;
    }
    else
    {
        /* disable the selected interrupts */
        RCC->CIR &= ~RCC_IT;
    }
}

/**
  * @brief  Checks whether the specified RCC interrupt flag is set or not.
  * @param  RCC_IT_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *             @arg RCC_ITFLAG_CSS: CSS clock secure system interrupt flag
  *             @arg RCC_ITFLAG_PLL2RDY: PLL2 clock ready interrupt flag
  *             @arg RCC_ITFLAG_PLLRDY: PLL clock ready interrupt flag
  *             @arg RCC_ITFLAG_HSERDY: HSE oscillator clock ready interrupt flag
  *             @arg RCC_ITFLAG_HSI48RDY: HSI48 oscillator clock ready interrupt flag
  *             @arg RCC_ITFLAG_HSIRDY: HSI oscillator clock ready interrupt flag
  *             @arg RCC_ITFLAG_LSIRDY: LSI oscillator clock ready interrupt flag
  *             @arg RCC_ITFLAG_LSERDY: LSE oscillator clock ready interrupt flag
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
ITStatus RCC_GetITStatus(uint32_t RCC_IT_FLAG)
{
    uint32_t statusreg = 0;
    ITStatus bitstatus = RESET;

    /* Check the parameters */
    assert_param(IS_RCC_ITFLAG(RCC_IT_FLAG));

    /* Get the interrupts flag */
    statusreg = RCC->CIR;

    if ((statusreg & RCC_IT_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    /* Return the flag status */
    return bitstatus;
}

/**
  * @brief  Clears the RCC's interrupt pending bits.
  * @param  RCC_IT_CLR: specifies the interrupt pending bit to clear.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_ITCLR_CSS: Clear Clock Security System interrupt Pending
  *             @arg RCC_ITCLR_PLL2RDY: Clear PLL2 ready interrupt Pending
  *             @arg RCC_ITCLR_PLLRDY: Clear PLL ready interrupt Pending
  *             @arg RCC_ITCLR_HSERDY: Clear HSE ready interrupt Pending
  *             @arg RCC_ITCLR_HSI48RDY: Clear HSI48 ready interrupt Pending
  *             @arg RCC_ITCLR_HSIRDY: Clear HSI ready interrupt Pending
  *             @arg RCC_ITCLR_LSERDY: Clear LSE ready interrupt Pending
  *             @arg RCC_ITCLR_LSIRDY: Clear LSI ready interrupt Pending
  * @retval None
  */
void RCC_ClearITPendingBit(uint32_t RCC_IT_CLR)
{
    /* Check the parameters */
    assert_param(IS_RCC_ITCLR(RCC_IT_CLR));

    /* Clear the selected interrupt pending bits */
    RCC->CIR |= RCC_IT_CLR;
}

/**
  * @brief  Select the RAM Control by themself or AHB.
  * @param  RCC_RAM_CTL: specifies the RAM.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_DCACHE_CTL: Dcache Ram Control by Dcache or AHB
  *             @arg RCC_ICACHE_CTL: Icache Ram Control by Icache or AHB
  *             @arg RCC_ETHMAC_CTL: Ethmac Ram Control by Ethmac or AHB
  *             @arg RCC_CAN_CTL: Can Ram Control by Can or AHB
  *             @arg RCC_USBHS_CTL: Usbhs Ram Control by Usbhs or AHB
  *             @arg RCC_USBFS_CTL: Usbfs Ram Control by Usbfs or AHB
  * @param  RCC_RAM_CTL_SEL: specifies the RAM Control by Themself or AHB.
  *          This parameter can be any combination of the following values:
  *             @arg RCC_RAM_CTL_SELF: Ram Control by Themself
  *             @arg RCC_RAM_CTL_AHB: Ram Control by AHB
  * @retval None
  */
void RCC_RamCtrlSel(uint32_t RCC_RAM_CTL, uint32_t RCC_RAM_CTL_SEL)
{
    /* Check the parameters */
    assert_param(IS_RCC_RAMCTL(RCC_RAM_CTL));
    assert_param(IS_RCC_RAMCTL_SEL(RCC_RAM_CTL_SEL));

    if (RCC_RAM_CTL_SEL == RCC_RAM_CTL_SELF)
    {
        /* Select the Ram Control by Themself */
        RCC->RAMCTL &= ~RCC_RAM_CTL;
    }
    else if (RCC_RAM_CTL_SEL == RCC_RAM_CTL_AHB)
    {
        /* Select the Ram Control by AHB */
        RCC->RAMCTL |=  RCC_RAM_CTL;
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
