/**
  * @file       board.c
  * @author     Haven-X
  * @brief      Board setup for NS800RTxxx examples.
  *
  * @note       Board Configurations
  *             Initializes the rest of the modules.
  *
  * <h2><center>&copy; Copyright (c) 2025 Novosense Limited.
  * All rights reserved.</center></h2>
  */
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Functions
 ******************************************************************************/

/**
 * @brief  Board Initialization.
 * @note   Call this function in your application if you wish to do all module
 *         initialization.
 *         If you wish to not use some of the initializations, instead of the
 *         Board_init use the individual Module_inits.
 */
void Board_init (void)
{
    PinMux_init();
    SerialCOM_init();
    LED_init();
    Switch_init();
}

/**
 * @brief  PinMux Initialization.
 * @note   Call this function in your application if you want all
 *         PinMux initialization to be done.
 */
void PinMux_init (void)
{
    /* Configure GPIO pins for SCI_COM. */
    GPIO_setPinConfig(GPIO_12_SCIA_TX);
    GPIO_setPinConfig(GPIO_13_SCIA_RX);

    /* Configure GPIO pins for LED1 and LED2. */
    GPIO_setPinConfig(GPIO_68_GPIO68);
    GPIO_setPinConfig(GPIO_69_GPIO69);

    /* Configure GPIO pins for KEY. */
    GPIO_setPinConfig(GPIO_41_GPIO41);
}

/**
 * @brief  Board Serial Communication Interface Initialization.
 * @note   Call this function in the application to initialize the SCI serial port
 *         on the board for outputting debugging information.
 */
void SerialCOM_init(void)
{
    /* uart1 rx control */
    GPIO_setAnalogMode(BOARD_SERIALCOM_RX_PIN, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(BOARD_SERIALCOM_RX_PIN, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(BOARD_SERIALCOM_RX_PIN, GPIO_QUAL_SYNC);
    GPIO_setQualificationPeriod(BOARD_SERIALCOM_RX_PIN, GPIO_SMP_SYSCLK_DIV_1);
    GPIO_setDirectionMode(BOARD_SERIALCOM_RX_PIN, GPIO_DIR_MODE_IN);
    /* uart1 tx control */
    GPIO_setAnalogMode(BOARD_SERIALCOM_TX_PIN, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(BOARD_SERIALCOM_TX_PIN, GPIO_PIN_TYPE_STD);
    GPIO_setDriveLevel(BOARD_SERIALCOM_TX_PIN, GPIO_DRV_LOW);
    GPIO_setPin(BOARD_SERIALCOM_TX_PIN);
    GPIO_setDirectionMode(BOARD_SERIALCOM_TX_PIN, GPIO_DIR_MODE_OUT);
    /* Reset uart before configure it */
    UART_resetModule(BOARD_SERIALCOM);
    /* Set baudrate */
    UART_setBaud(BOARD_SERIALCOM, BOARD_SERIALCOM_BAUDRATE);
    /* Set the number of stop bits */
    UART_setStopBitCount(BOARD_SERIALCOM, UART_ONE_STOP_BIT);
    /* Set MSB bit reverses the order of the bits */
    UART_setMSB(BOARD_SERIALCOM, false);
    /* Config tx fifo */
    UART_enableTxFifo(BOARD_SERIALCOM);
    UART_resetTxFifo(BOARD_SERIALCOM);
    UART_setTxFifoWatermark(BOARD_SERIALCOM, UART_FIFO_TX6);

    /* Enable transmitter */
    UART_enableTxModule(BOARD_SERIALCOM);
    /* Enable receiver */
    UART_enableRxModule(BOARD_SERIALCOM);
}

/**
 * @brief  Board LED Initialization.
 * @note   Call this function in the application to initialize the LED
 *         on the board.
 */
void LED_init (void)
{
    /* led1 initialization */
    GPIO_setAnalogMode(BOARD_LED1_PIN, GPIO_ANALOG_DISABLED);
    GPIO_setDriveLevel(BOARD_LED1_PIN, GPIO_DRV_MAX);
    GPIO_clearPin(BOARD_LED1_PIN);
    GPIO_setDirectionMode(BOARD_LED1_PIN, GPIO_DIR_MODE_OUT);
    /* led2 initialization */
    GPIO_setAnalogMode(BOARD_LED2_PIN, GPIO_ANALOG_DISABLED);
    GPIO_setDriveLevel(BOARD_LED2_PIN, GPIO_DRV_MAX);
    GPIO_clearPin(BOARD_LED2_PIN);
    GPIO_setDirectionMode(BOARD_LED2_PIN, GPIO_DIR_MODE_OUT);
}

/**
 * @brief  Board Switch Initialization.
 * @note   Call this function in the application to initialize the Switch
 *         on the board.
 */
void Switch_init (void)
{
    /* KEY initialization */
    GPIO_setAnalogMode(BOARD_KEY_PIN, GPIO_ANALOG_DISABLED);
    GPIO_setPadConfig(BOARD_KEY_PIN, GPIO_PIN_TYPE_OD);
    GPIO_setQualificationPeriod(BOARD_KEY_PIN, GPIO_SMP_SYSCLK_DIV_510);
    GPIO_setQualificationMode(BOARD_KEY_PIN, GPIO_QUAL_6SAMPLE);
    GPIO_setDirectionMode(BOARD_KEY_PIN, GPIO_DIR_MODE_IN);
}

/**
 * @brief  Function to initialize the device.
 * @note   Mainly initialize the system clock and enable all peripheral clocks.
 */
void Device_init(void)
{
    System_setClock();
#if (DUAL_CORE_ENABLE == 0)
    Device_enableAllPeripheralsInCpu1();
#endif
    Device_enableAllPeripherals();
}

/**
 * @brief  Set up clock source selection, PLL control, and clock dividers.
 */
void System_setClock (void)
{
    /* If CPU1 has been configured, do not repeat the configuration for CPU2. */
    if((MCM->CPUID.WORDVAL & 0x01) == 0x01)
    {
#ifdef SYSCLK_USE_PLL
#ifdef SYSCLK_SOURCE_USE_HXTL
        RCC_configHxtl(HXTL_CONFIG, RCC_HXTL_NORMAL, RCC_FUN_ON);
#endif
        RCC_configPll(PLL_CONFIG, PLL_EXT_CONFIG, RCC_FUN_ON);

        RCC_setClock(RCC_SYSCLKSOURCE_PLL);
#else  /* !SYSCLK_USE_PLL */
#ifdef SYSCLK_SOURCE_USE_HXTL
        RCC_configHxtl(HXTL_CONFIG, RCC_HXTL_NORMAL, RCC_FUN_ON);
        RCC_setClock(RCC_SYSCLKSOURCE_HXTL);
#endif /* SYSCLK_SOURCE_USE_HXTL */

#ifdef SYSCLK_SOURCE_USE_MIRC1
        RCC_setClock(RCC_SYSCLKSOURCE_MIRC1);
#endif /* SYSCLK_SOURCE_USE_MIRC1 */

#ifdef SYSCLK_SOURCE_USE_MIRC2
        RCC_setClock(RCC_SYSCLKSOURCE_MIRC2);
#endif /* SYSCLK_SOURCE_USE_MIRC2 */
#endif /* SYSCLK_USE_PLL */
        RCC_configClockDiv(SYSCLOCK_CFGR_DIV_CONFIG, SYSCLOCK_CFGR2_DIV_CONFIG);
    }
}

#if (DUAL_CORE_ENABLE == 0)
/**
 * @brief  Enable CPU1 for  peripherals.
 */
void Device_enableAllPeripheralsInCpu1 (void)
{
    SYSCON->UNLOCK.WORDVAL = 0x55aa6699;

    WRITE_REG(SYSCON->AHBCPUSEL1.WORDVAL, 0x0);
    WRITE_REG(SYSCON->AHBCPUSEL2.WORDVAL, 0x0);
    WRITE_REG(SYSCON->APBCPUSEL1.WORDVAL, 0x0);
    WRITE_REG(SYSCON->APBCPUSEL2.WORDVAL, 0x0);
    WRITE_REG(SYSCON->APBCPUSEL3.WORDVAL, 0x0);
    WRITE_REG(SYSCON->APBCPUSEL5.WORDVAL, 0x0);
    WRITE_REG(SYSCON->APBCPUSEL6.WORDVAL, 0x0);
    WRITE_REG(SYSCON->APBCPUSEL8.WORDVAL, 0x0);

    SET_BIT(SYSCON->AHBCPUSELEN1.WORDVAL, 0x00000330);
    SET_BIT(SYSCON->AHBCPUSELEN2.WORDVAL, 0x00007303);
    SET_BIT(SYSCON->APBCPUSELEN1.WORDVAL, 0xFF7FFFFF);
    SET_BIT(SYSCON->APBCPUSELEN2.WORDVAL, 0x07FF800F);
    SET_BIT(SYSCON->APBCPUSELEN3.WORDVAL, 0x00000300);
    SET_BIT(SYSCON->APBCPUSELEN5.WORDVAL, 0x01070F0F);
    SET_BIT(SYSCON->APBCPUSELEN6.WORDVAL, 0x03003F03);
    SET_BIT(SYSCON->APBCPUSELEN8.WORDVAL, 0x03FF0010);

    SYSCON->UNLOCK.WORDVAL = 0x55aa6698;
}
#endif

/**
 * @brief  Enable clocks for all peripherals.
 */
void Device_enableAllPeripherals (void)
{
    RCC_unlockRccRegister();

    RCC_enableAhb1PeripheralClock(RCC_HCLKEN1_UPPEN_M | RCC_HCLKEN1_EMIFEN_M | RCC_HCLKEN1_SEMAEN_M |
                                  RCC_HCLKEN1_MUEN_M | RCC_HCLKEN1_GPIOHEN_M | RCC_HCLKEN1_GPIOGEN_M |
                                  RCC_HCLKEN1_GPIOFEN_M | RCC_HCLKEN1_GPIOEEN_M | RCC_HCLKEN1_GPIODEN_M |
                                  RCC_HCLKEN1_GPIOCEN_M | RCC_HCLKEN1_GPIOBEN_M | RCC_HCLKEN1_GPIOAEN_M |
                                  RCC_HCLKEN1_EMATHEN_M | RCC_HCLKEN1_QSPIEN_M | RCC_HCLKEN1_CPUXMMATHEN_M |
                                  RCC_HCLKEN1_EDMA2EN_M | RCC_HCLKEN1_EDMA1EN_M | RCC_HCLKEN1_DMAMUX2EN_M |
                                  RCC_HCLKEN1_DMAMUX1EN_M | RCC_HCLKEN1_SMPUEN_M | RCC_HCLKEN1_FMUEN_M);

    RCC_enableAhb2PeripheralClock(RCC_HCLKEN2_CANFD2EN_M | RCC_HCLKEN2_CANFD1EN_M | RCC_HCLKEN2_CAN1EN_M |
                                  RCC_HCLKEN2_LIN2EN_M | RCC_HCLKEN2_LIN1EN_M | RCC_HCLKEN2_BGCRC2EN_M |
                                  RCC_HCLKEN2_BGCRC1EN_M | RCC_HCLKEN2_CRC2EN_M | RCC_HCLKEN2_CRC1EN_M |
                                  RCC_HCLKEN2_AESHASHEN_M | RCC_HCLKEN2_TRNGEN_M);

    RCC_enableApb1PeripheralClock(RCC_PCLKEN1_EPWM18EN_M | RCC_PCLKEN1_EPWM17EN_M | RCC_PCLKEN1_EQEP6EN_M |
                                  RCC_PCLKEN1_EQEP5EN_M | RCC_PCLKEN1_EQEP4EN_M | RCC_PCLKEN1_EQEP3EN_M |
                                  RCC_PCLKEN1_EQEP2EN_M | RCC_PCLKEN1_EQEP1EN_M | RCC_PCLKEN1_ECAP7EN_M |
                                  RCC_PCLKEN1_ECAP6EN_M | RCC_PCLKEN1_ECAP5EN_M | RCC_PCLKEN1_ECAP4EN_M |
                                  RCC_PCLKEN1_ECAP3EN_M | RCC_PCLKEN1_ECAP2EN_M | RCC_PCLKEN1_ECAP1EN_M |
                                  RCC_PCLKEN1_EPWM16EN_M | RCC_PCLKEN1_EPWM15EN_M | RCC_PCLKEN1_EPWM14EN_M |
                                  RCC_PCLKEN1_EPWM13EN_M | RCC_PCLKEN1_EPWM12EN_M | RCC_PCLKEN1_EPWM11EN_M |
                                  RCC_PCLKEN1_EPWM10EN_M | RCC_PCLKEN1_EPWM9EN_M | RCC_PCLKEN1_EPWM8EN_M |
                                  RCC_PCLKEN1_EPWM7EN_M | RCC_PCLKEN1_EPWM6EN_M | RCC_PCLKEN1_EPWM5EN_M |
                                  RCC_PCLKEN1_EPWM4EN_M | RCC_PCLKEN1_EPWM3EN_M | RCC_PCLKEN1_EPWM2EN_M |
                                  RCC_PCLKEN1_EPWM1EN_M);

    RCC_enableApb2PeripheralClock(RCC_PCLKEN2_CMPSS11EN_M | RCC_PCLKEN2_CMPSS10EN_M | RCC_PCLKEN2_CMPSS9EN_M |
                                  RCC_PCLKEN2_SDFM1EN_M | RCC_PCLKEN2_CMPSS8EN_M | RCC_PCLKEN2_CMPSS7EN_M |
                                  RCC_PCLKEN2_CMPSS6EN_M | RCC_PCLKEN2_CMPSS5EN_M | RCC_PCLKEN2_CMPSS4EN_M |
                                  RCC_PCLKEN2_CMPSS3EN_M | RCC_PCLKEN2_CMPSS2EN_M | RCC_PCLKEN2_CMPSS1EN_M |
                                  RCC_PCLKEN2_XBAREN_M | RCC_PCLKEN2_ADCDEN_M | RCC_PCLKEN2_ADCCEN_M |
                                  RCC_PCLKEN2_ADCBEN_M | RCC_PCLKEN2_ADCAEN_M | RCC_PCLKEN2_SDFM4EN_M |
                                  RCC_PCLKEN2_SDFM3EN_M | RCC_PCLKEN2_SDFM2EN_M);

    RCC_enableApb3PeripheralClock(RCC_PCLKEN3_ANALOGSS_M | RCC_PCLKEN3_DAC3EN_M | RCC_PCLKEN3_DAC1EN_M);

    RCC_enableApb5PeripheralClock(RCC_PCLKEN5_DCC1EN_M | RCC_PCLKEN5_CPUXWWDGEN_M | RCC_PCLKEN5_EPGEN_M |
                                  RCC_PCLKEN5_PMBUSEN_M | RCC_PCLKEN5_I2C2EN_M | RCC_PCLKEN5_I2C1EN_M |
                                  RCC_PCLKEN5_SPI4EN_M | RCC_PCLKEN5_SPI3EN_M | RCC_PCLKEN5_SPI2EN_M |
                                  RCC_PCLKEN5_SPI1EN_M | RCC_PCLKEN5_UART4EN_M | RCC_PCLKEN5_UART3EN_M |
                                  RCC_PCLKEN5_UART2EN_M | RCC_PCLKEN5_UART1EN_M);

    RCC_enableApb6PeripheralClock(RCC_PCLKEN6_DCC3EN_M | RCC_PCLKEN6_DCC2EN_M | RCC_PCLKEN6_BTIM2EN_M |
                                  RCC_PCLKEN6_BTIM1EN_M | RCC_PCLKEN6_CPUXSTIM3EN_M | RCC_PCLKEN6_CPUXSTIM2EN_M |
                                  RCC_PCLKEN6_CPUXSTIM1EN_M | RCC_PCLKEN6_CLB6EN_M | RCC_PCLKEN6_CLB5EN_M |
                                  RCC_PCLKEN6_CLB4EN_M | RCC_PCLKEN6_CLB3EN_M | RCC_PCLKEN6_CLB2EN_M |
                                  RCC_PCLKEN6_CLB1EN_M | RCC_PCLKEN6_TIM2EN_M | RCC_PCLKEN6_TIM1EN_M);

    RCC_enableApb8PeripheralClock(RCC_PCLKEN8_ADCAGG2EN_M | RCC_PCLKEN8_ADCAGG1EN_M | RCC_PCLKEN8_ADCCHK8EN_M |
                                  RCC_PCLKEN8_ADCCHK7EN_M | RCC_PCLKEN8_ADCCHK6EN_M | RCC_PCLKEN8_ADCCHK5EN_M |
                                  RCC_PCLKEN8_ADCCHK4EN_M | RCC_PCLKEN8_ADCCHK3EN_M | RCC_PCLKEN8_ADCCHK2EN_M |
                                  RCC_PCLKEN8_ADCCHK1EN_M | RCC_PCLKEN8_AWKEN_M | RCC_PCLKEN8_LPTIMEN_M |
                                  RCC_PCLKEN8_IWDG2EN_M | RCC_PCLKEN8_CPUXIWDG1EN_M | RCC_PCLKEN8_PWREN_M);

    RCC_lockRccRegister();
}

/**
 * @brief  Unlock all peripheral registers.
 */
void Device_unlockPeriphReg (void)
{
    /* Enables register writing function about FMU/ECAP/EPWM/XBAR/CMPSS/SDFM/DAC/ANASS/ADC/PGA/GPIO */
    SYSCON->SYSEALLOW1.WORDVAL = 0x7FFFFFFF;
    SYSCON->SYSEALLOW2.WORDVAL = 0x7FFFFFFF;
    SYSCON->SYSEALLOW3.WORDVAL = 0x00003FFF;
}

/**
 * @brief  Disable clocks for all peripherals.
 */
void Device_disableAllPeripherals (void)
{
    RCC_unlockRccRegister();

    RCC_disableAhb1PeripheralClock(RCC_HCLKEN1_UPPEN_M | RCC_HCLKEN1_EMIFEN_M | RCC_HCLKEN1_SEMAEN_M |
                                   RCC_HCLKEN1_MUEN_M | RCC_HCLKEN1_GPIOHEN_M | RCC_HCLKEN1_GPIOGEN_M |
                                   RCC_HCLKEN1_GPIOFEN_M | RCC_HCLKEN1_GPIOEEN_M | RCC_HCLKEN1_GPIODEN_M |
                                   RCC_HCLKEN1_GPIOCEN_M | RCC_HCLKEN1_GPIOBEN_M | RCC_HCLKEN1_GPIOAEN_M |
                                   RCC_HCLKEN1_EMATHEN_M | RCC_HCLKEN1_QSPIEN_M  | RCC_HCLKEN1_CPUXMMATHEN_M |
                                   RCC_HCLKEN1_EDMA2EN_M | RCC_HCLKEN1_EDMA1EN_M | RCC_HCLKEN1_DMAMUX2EN_M |
                                   RCC_HCLKEN1_DMAMUX1EN_M | RCC_HCLKEN1_SMPUEN_M | RCC_HCLKEN1_FMUEN_M);

    RCC_disableAhb2PeripheralClock(RCC_HCLKEN2_CANFD2EN_M | RCC_HCLKEN2_CANFD1EN_M | RCC_HCLKEN2_CAN1EN_M |
                                   RCC_HCLKEN2_LIN2EN_M | RCC_HCLKEN2_LIN1EN_M | RCC_HCLKEN2_BGCRC2EN_M |
                                   RCC_HCLKEN2_BGCRC1EN_M | RCC_HCLKEN2_CRC2EN_M | RCC_HCLKEN2_CRC1EN_M |
                                   RCC_HCLKEN2_AESHASHEN_M |RCC_HCLKEN2_TRNGEN_M);

    RCC_disableApb1PeripheralClock(RCC_PCLKEN1_EPWM18EN_M | RCC_PCLKEN1_EPWM17EN_M | RCC_PCLKEN1_EQEP6EN_M |
                                   RCC_PCLKEN1_EQEP5EN_M | RCC_PCLKEN1_EQEP4EN_M | RCC_PCLKEN1_EQEP3EN_M |
                                   RCC_PCLKEN1_EQEP2EN_M | RCC_PCLKEN1_EQEP1EN_M | RCC_PCLKEN1_ECAP7EN_M |
                                   RCC_PCLKEN1_ECAP6EN_M | RCC_PCLKEN1_ECAP5EN_M | RCC_PCLKEN1_ECAP4EN_M |
                                   RCC_PCLKEN1_ECAP3EN_M | RCC_PCLKEN1_ECAP2EN_M | RCC_PCLKEN1_ECAP1EN_M |
                                   RCC_PCLKEN1_EPWM16EN_M | RCC_PCLKEN1_EPWM15EN_M | RCC_PCLKEN1_EPWM14EN_M |
                                   RCC_PCLKEN1_EPWM13EN_M | RCC_PCLKEN1_EPWM12EN_M | RCC_PCLKEN1_EPWM11EN_M |
                                   RCC_PCLKEN1_EPWM10EN_M | RCC_PCLKEN1_EPWM9EN_M | RCC_PCLKEN1_EPWM8EN_M |
                                   RCC_PCLKEN1_EPWM7EN_M | RCC_PCLKEN1_EPWM6EN_M | RCC_PCLKEN1_EPWM5EN_M |
                                   RCC_PCLKEN1_EPWM4EN_M | RCC_PCLKEN1_EPWM3EN_M | RCC_PCLKEN1_EPWM2EN_M |
                                   RCC_PCLKEN1_EPWM1EN_M);

    RCC_disableApb2PeripheralClock(RCC_PCLKEN2_CMPSS11EN_M | RCC_PCLKEN2_CMPSS10EN_M | RCC_PCLKEN2_CMPSS9EN_M |
                                   RCC_PCLKEN2_SDFM1EN_M | RCC_PCLKEN2_CMPSS8EN_M | RCC_PCLKEN2_CMPSS7EN_M |
                                   RCC_PCLKEN2_CMPSS6EN_M | RCC_PCLKEN2_CMPSS5EN_M | RCC_PCLKEN2_CMPSS4EN_M |
                                   RCC_PCLKEN2_CMPSS3EN_M | RCC_PCLKEN2_CMPSS2EN_M | RCC_PCLKEN2_CMPSS1EN_M |
                                   RCC_PCLKEN2_XBAREN_M | RCC_PCLKEN2_ADCDEN_M | RCC_PCLKEN2_ADCCEN_M |
                                   RCC_PCLKEN2_ADCBEN_M | RCC_PCLKEN2_ADCAEN_M | RCC_PCLKEN2_SDFM4EN_M |
                                   RCC_PCLKEN2_SDFM3EN_M | RCC_PCLKEN2_SDFM2EN_M);

    RCC_disableApb3PeripheralClock(RCC_PCLKEN3_ANALOGSS_M | RCC_PCLKEN3_DAC3EN_M | RCC_PCLKEN3_DAC1EN_M);

    RCC_disableApb5PeripheralClock(RCC_PCLKEN5_DCC1EN_M | RCC_PCLKEN5_CPUXWWDGEN_M | RCC_PCLKEN5_EPGEN_M |
                                   RCC_PCLKEN5_PMBUSEN_M | RCC_PCLKEN5_I2C2EN_M | RCC_PCLKEN5_I2C1EN_M |
                                   RCC_PCLKEN5_SPI4EN_M | RCC_PCLKEN5_SPI3EN_M | RCC_PCLKEN5_SPI2EN_M |
                                   RCC_PCLKEN5_SPI1EN_M | RCC_PCLKEN5_UART4EN_M |RCC_PCLKEN5_UART3EN_M |
                                   RCC_PCLKEN5_UART2EN_M | RCC_PCLKEN5_UART1EN_M);

    RCC_disableApb6PeripheralClock(RCC_PCLKEN6_DCC3EN_M | RCC_PCLKEN6_DCC2EN_M | RCC_PCLKEN6_BTIM2EN_M |
                                   RCC_PCLKEN6_BTIM1EN_M | RCC_PCLKEN6_CPUXSTIM3EN_M | RCC_PCLKEN6_CPUXSTIM2EN_M |
                                   RCC_PCLKEN6_CPUXSTIM1EN_M | RCC_PCLKEN6_CLB6EN_M | RCC_PCLKEN6_CLB5EN_M |
                                   RCC_PCLKEN6_CLB4EN_M | RCC_PCLKEN6_CLB3EN_M | RCC_PCLKEN6_CLB2EN_M |
                                   RCC_PCLKEN6_CLB1EN_M | RCC_PCLKEN6_TIM2EN_M | RCC_PCLKEN6_TIM1EN_M);

    RCC_disableApb8PeripheralClock(RCC_PCLKEN8_ADCAGG2EN_M | RCC_PCLKEN8_ADCAGG1EN_M | RCC_PCLKEN8_ADCCHK8EN_M |
                                   RCC_PCLKEN8_ADCCHK7EN_M | RCC_PCLKEN8_ADCCHK6EN_M | RCC_PCLKEN8_ADCCHK5EN_M |
                                   RCC_PCLKEN8_ADCCHK4EN_M | RCC_PCLKEN8_ADCCHK3EN_M | RCC_PCLKEN8_ADCCHK2EN_M |
                                   RCC_PCLKEN8_ADCCHK1EN_M | RCC_PCLKEN8_AWKEN_M | RCC_PCLKEN8_LPTIMEN_M |
                                   RCC_PCLKEN8_IWDG2EN_M | RCC_PCLKEN8_CPUXIWDG1EN_M | RCC_PCLKEN8_PWREN_M);
    RCC_lockRccRegister();
}

/**
 * @brief  Lock all peripheral registers.
 */
void Device_lockPeriphReg (void)
{
    /* Enables register writing function about FMU/ECAP/EPWM/XBAR/CMPSS/SDFM/DAC/ANASS/ADC/PGA/GPIO */
    SYSCON->SYSEALLOW1.WORDVAL = 0x00000000;
    SYSCON->SYSEALLOW2.WORDVAL = 0x00000000;
    SYSCON->SYSEALLOW3.WORDVAL = 0x00000000;
}

