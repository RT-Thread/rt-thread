/****************************************************************************
 * @file     nutool_pincfg.c
 * @version  V1.21
 * @Date     2024/4/1-12:06:36
 * @brief    NuMicro generated code file
 *
 * Copyright (C) 2013-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include "rtconfig.h"
#include "NuMicro.h"

#if defined(BOARD_USING_NUTFT)
void expansion_nutft_pin_init(void)
{
#if defined(BOARD_USING_LCD_ILI9341)
    SET_SPI2_SS_PA11();
    SET_SPI2_CLK_PA10();
    SET_SPI2_MISO_PA9();
    SET_SPI2_MOSI_PA8();


    SET_GPIO_PB2();
    SET_GPIO_PB3();
    SET_GPIO_PB5();
#endif

#if defined(BOARD_USING_NUTFT_ADC_TOUCH)
    GPIO_SetMode(PB, BIT4 | BIT5 | BIT6 | BIT7, GPIO_MODE_INPUT);

    /* EADC Analog Pin: UNO_A0, UNO_A1, UNO_A2, UNO_A3 */
    SYS->GPB_MFP1 &= ~(SYS_GPB_MFP3_PB14MFP_Msk | SYS_GPB_MFP3_PB15MFP_Msk);
    SYS->GPB_MFP1 |= (SYS_GPB_MFP3_PB14MFP_EADC0_CH14 | SYS_GPB_MFP3_PB15MFP_EADC0_CH15);
    SYS->GPB_MFP2 &= ~(SYS_GPB_MFP2_PB9MFP_Msk | SYS_GPB_MFP2_PB8MFP_Msk);
    SYS->GPB_MFP2 |= (SYS_GPB_MFP2_PB9MFP_EADC0_CH9 | SYS_GPB_MFP2_PB8MFP_EADC0_CH8);

    /* Disable digital path on these EADC pins */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT8 | BIT9 | BIT14 | BIT15);
#endif

#if defined(BOARD_USING_QSPI_FLASH)
    SET_QSPI0_MOSI0_PA0();
    SET_QSPI0_MISO0_PA1();
    SET_QSPI0_CLK_PA2();
    SET_QSPI0_SS_PA3();
    SET_QSPI0_MOSI1_PA4();
    SET_QSPI0_MISO1_PA5();
#endif

#if defined(BOARD_USING_NUTFT_BUTTON)
    SYS->GPB_MFP0 &= ~(SYS_GPB_MFP0_PB0MFP_Msk | SYS_GPB_MFP0_PB1MFP_Msk);

    /* Disable digital path on these ADC pins */
    GPIO_ENABLE_DIGITAL_PATH(PB, BIT0 | BIT1);
#endif

}
#endif

void nutool_pincfg_init_sd0(void)
{
    SET_SD0_nCD_PD13();
    SET_SD0_DAT1_PE3();
    SET_SD0_DAT0_PE2();
    SET_SD0_CMD_PE7();
    SET_SD0_CLK_PE6();
    SET_SD0_DAT3_PE5();
    SET_SD0_DAT2_PE4();

    return;
}

void nutool_pincfg_deinit_sd0(void)
{
    SET_GPIO_PD13();
    SET_GPIO_PE3();
    SET_GPIO_PE2();
    SET_GPIO_PE7();
    SET_GPIO_PE6();
    SET_GPIO_PE5();
    SET_GPIO_PE4();
}

void nutool_pincfg_init_uart0(void)
{
    SET_UART0_RXD_PB12();
    SET_UART0_TXD_PB13();
}

void nutool_pincfg_deinit_uart0(void)
{
    SET_GPIO_PB12();
    SET_GPIO_PB13();
}

void nutool_pincfg_init_hsusb(void)
{
}

void nutool_pincfg_init(void)
{
    /* Vref connect to internal */
    SYS_SetVRef(SYS_VREFCTL_VREF_PIN);

#if defined(BSP_USING_UART0)
    nutool_pincfg_init_uart0();
#endif

#if defined(BSP_USING_SDH0)
    nutool_pincfg_init_sd0();
#endif

#if defined(BOARD_USING_NUTFT)
    expansion_nutft_pin_init();
#else
    /* Set PB15 multi-function pin for LLSI0 output */
    SET_LLSI0_OUT_PB15();

    /* Set PB9 multi-function pin for ELLSI0 output */
    //SET_ELLSI0_OUT_PB9();

    /* Configure EPWM1 channel 3 pin */
    SET_EPWM1_CH3_PC9();

    /* Configure BPWM0 channel 0 pin */
    SET_BPWM0_CH0_PA0();
#endif

    /* HSUSB_VBUS_EN (USB 2.0 VBUS power enable pin) multi-function pin - PB.10   */
    SET_HSUSB_VBUS_EN_PB10();

    /* HSUSB_VBUS_ST (USB 2.0 over-current detect pin) multi-function pin - PB.11 */
    SET_HSUSB_VBUS_ST_PB11();


    return;
}

void nutool_pincfg_deinit(void)
{
#if defined(BSP_USING_UART0)
    nutool_pincfg_deinit_uart0();
#endif

#if defined(BSP_USING_SDH0)
    nutool_pincfg_deinit_sd0();
#endif

    return;
}
