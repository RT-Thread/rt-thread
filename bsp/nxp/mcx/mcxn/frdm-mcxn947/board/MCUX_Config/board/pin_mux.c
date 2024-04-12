#include "rtconfig.h"

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"


void BOARD_InitBootPins(void)
{
    CLOCK_EnableClock(kCLOCK_Port0);
    CLOCK_EnableClock(kCLOCK_Port1);
    CLOCK_EnableClock(kCLOCK_Port2);
    CLOCK_EnableClock(kCLOCK_Port3);
    CLOCK_EnableClock(kCLOCK_Port4);

    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);
    CLOCK_EnableClock(kCLOCK_Gpio2);
    CLOCK_EnableClock(kCLOCK_Gpio3);
    CLOCK_EnableClock(kCLOCK_Gpio4);



    /* UART */
    PORT1->PCR[8]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_IBE(1);     /* FC4_P0 */
    PORT1->PCR[9]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_IBE(1);     /* FC4_P1 */

    /* Mikro Bus UART */
//	  PORT1->PCR[16]  = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_IBE(1);     /* FC5_P0 */
//	  PORT1->PCR[17]  = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_IBE(1);     /* FC5_P1 */

    PORT1->PCR[16]  = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC5_UART */
    PORT1->PCR[17]  = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC5_UART */

    /* DAC */
    // PORT4->PCR[2] = PORT_PCR_MUX(0) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(0); /* DAC0 */
    // PORT4->PCR[3] = PORT_PCR_MUX(0) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(0); /* DAC1 */

    /* MCX_RST UART */
    PORT4->PCR[2]  = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC2_UART */
    PORT4->PCR[3]  = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC2_UART */


    PORT0->PCR[6]   = PORT_PCR_MUX(12) | PORT_PCR_PS(1) | PORT_PCR_PE(1) | PORT_PCR_IBE(1) | PORT_PCR_SRE(0) | PORT_PCR_ODE(0);     /* CLKOUT */

#ifdef BSP_USING_I2C1
    PORT0->PCR[24]   = PORT_PCR_MUX(2) | PORT_PCR_PS(1) | PORT_PCR_PE(1) | PORT_PCR_IBE(1) | PORT_PCR_SRE(0) | PORT_PCR_ODE(0);     /* FC1 I2C_SDA */
    PORT0->PCR[25]   = PORT_PCR_MUX(2) | PORT_PCR_PS(1) | PORT_PCR_PE(1) | PORT_PCR_IBE(1) | PORT_PCR_SRE(0) | PORT_PCR_ODE(0);     /* FC1 I2C_SCL */
#endif

    PORT0->PCR[16]   = PORT_PCR_MUX(2) | PORT_PCR_PS(1) | PORT_PCR_PE(1) | PORT_PCR_IBE(1) | PORT_PCR_SRE(0) | PORT_PCR_ODE(0);     /* FC0 I2C_SDA */
    PORT0->PCR[17]   = PORT_PCR_MUX(2) | PORT_PCR_PS(1) | PORT_PCR_PE(1) | PORT_PCR_IBE(1) | PORT_PCR_SRE(0) | PORT_PCR_ODE(0);     /* FC0 I2C_SCL */


#ifdef BSP_USING_SPI1
    /* Arduino D11(P0_24), D12(P0_26), D13(P0_25) as SPI function, for RW007 MOSI, MISO, CLK  */
    PORT0->PCR[24]   = PORT_PCR_MUX(2) | PORT_PCR_PS(1) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* P0_24: FC1_0 */
    PORT0->PCR[26]   = PORT_PCR_MUX(2) | PORT_PCR_PS(1) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* P0_26: FC1_2 */
    PORT0->PCR[25]   = PORT_PCR_MUX(2) | PORT_PCR_PS(1) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* P0_25: FC1_1 */

    /* Arduino D8(P0_28), D9(P0_10), D10(P0_27) as GPIO function, for RW007 RST, INT, CS */
    /* drv_pin.c works well, follow lines just notice that pins we used as GPIO function */
    // PORT0->PCR[28]   = PORT_PCR_MUX(0) | PORT_PCR_PS(1) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* P0_28: P0_28 */
    // PORT0->PCR[10]   = PORT_PCR_MUX(0) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* P0_10: P0_27 */
    PORT0->PCR[27]   = PORT_PCR_MUX(0) | PORT_PCR_PS(1) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* P0_27: P0_27 */
#endif

    /* PMOD */
    PORT1->PCR[0]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC3_0 SDO/D[0], FC3_SPI_MOSI */
    PORT1->PCR[1]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC3_1 SCK, FC3_SPI_CLK */
    PORT1->PCR[2]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC3_2 SDI/D[1], FC3_SPI_MISO */
    PORT1->PCR[3]   = PORT_PCR_MUX(0) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* CS */
//    PORT1->PCR[3]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC3_3 CS0 */
//    PORT1->PCR[4]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC3_4 D[3] */
//    PORT1->PCR[5]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC3_5 D[2] */

    /* SPI */
    PORT3->PCR[8]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC7_P0, MOSI */
    PORT3->PCR[9]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC7_P2, MISO */
    PORT3->PCR[7]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC7_P1, CLK */
    PORT3->PCR[0]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC7_P1, CS */

    PORT1->PCR[8]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC4_UART */
    PORT1->PCR[9]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC4_UART */


    PORT1->PCR[10]   = PORT_PCR_MUX(11) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* CAN0_TX */
    PORT1->PCR[11]   = PORT_PCR_MUX(11) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* CAN0_RX */


    PORT1->PCR[12]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC3_0 SDO/D[0] */
    PORT1->PCR[13]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC3_1 SCK */
    PORT1->PCR[14]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC3_2 SDI/D[1] */
    PORT1->PCR[15]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC3_3 CS0 */
//    PORT1->PCR[16]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC3_4 D[3] */
//    PORT1->PCR[17]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC3_5 D[2] */

//    PORT1->PCR[8]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC5_4 D[3] */
//    PORT1->PCR[9]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC5_5 D[2] */
    PORT1->PCR[4]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC5_0 SDO/D[0] */
    PORT1->PCR[5]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC5_1 SCK */
    PORT1->PCR[6]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC5_2 SDI/D[1] */
    PORT1->PCR[7]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* FC5_3 CS0 */

    PORT2->PCR[2]   = PORT_PCR_MUX(3) | PORT_PCR_PE(0) | PORT_PCR_PS(0) | PORT_PCR_IBE(1);   /* SDHC0_D1 */
    PORT2->PCR[3]   = PORT_PCR_MUX(3) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_IBE(1);   /* SDHC0_D0 */
    PORT2->PCR[4]   = PORT_PCR_MUX(3) | PORT_PCR_PE(0) | PORT_PCR_PS(0) | PORT_PCR_IBE(1);   /* SDHC0_CLK */
    PORT2->PCR[5]   = PORT_PCR_MUX(3) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_IBE(1);   /* SDHC0_CMD */
    PORT2->PCR[6]   = PORT_PCR_MUX(3) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_IBE(1);   /* SDHC0_D3 */
    PORT2->PCR[7]   = PORT_PCR_MUX(3) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_IBE(1);   /* SDHC0_D2 */

    /* mikroBUS SPI6 */
    PORT3->PCR[20]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC6_P0 SDO/D[0], FC6_SPI_MOSI */
    PORT3->PCR[21]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC6_P1 SCK, FC6_SPI_CLK */
    PORT3->PCR[22]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC6_P2 SDI/D[1], FC3_SPI_MISO */
    PORT3->PCR[23]   = PORT_PCR_MUX(0) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* CS */


//    PORT1->PCR[20]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC4_0 */
//    PORT1->PCR[21]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC4_1 */
//    PORT1->PCR[22]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC4_2 */
//    PORT1->PCR[23]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC4_3 */
//    PORT1->PCR[0]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);      /* FC4_4 */
//    PORT1->PCR[1]   = PORT_PCR_MUX(3) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);      /* FC4_5 */

//    PORT4->PCR[0]   = PORT_PCR_MUX(0) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ANA_0, ADC0_A0 */
//    PORT4->PCR[1]   = PORT_PCR_MUX(0) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ANA_1, ADC0_B0 */

    PORT4->PCR[0]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC2_P0 I2C_SDA */
    PORT4->PCR[1]   = PORT_PCR_MUX(2) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* FC2_P1 I2C_SCL */

    /* FLEXIO */
    PORT0->PCR[ 9] = PORT_PCR_MUX(6) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; /* FLEXIO WR */
    PORT0->PCR[ 8] = PORT_PCR_MUX(6) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; /* FLEXIO RD */
    PORT0->PCR[12] = PORT_PCR_MUX(0) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; /* FLEXIO CS */
    PORT0->PCR[ 7] = PORT_PCR_MUX(0) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; /* FLEXIO RS */

    PORT2->PCR[ 8]   = PORT_PCR_MUX(FLEXIO_DATA0_MUX)  | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D0 */
    PORT2->PCR[ 9]   = PORT_PCR_MUX(FLEXIO_DATA1_MUX)  | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D1 */
    PORT2->PCR[10]   = PORT_PCR_MUX(FLEXIO_DATA2_MUX)  | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D2 */
    PORT2->PCR[11]   = PORT_PCR_MUX(FLEXIO_DATA3_MUX)  | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D3 */
    PORT4->PCR[12]   = PORT_PCR_MUX(FLEXIO_DATA4_MUX)  | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D4 */
    PORT4->PCR[13]   = PORT_PCR_MUX(FLEXIO_DATA5_MUX)  | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D5 */
    PORT4->PCR[14]   = PORT_PCR_MUX(FLEXIO_DATA6_MUX)  | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D6 */
    PORT4->PCR[15]   = PORT_PCR_MUX(FLEXIO_DATA7_MUX)  | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D7 */
    PORT4->PCR[16] = PORT_PCR_MUX(FLEXIO_DATA8_MUX)  | PORT_PCR_PE_MASK | PORT_PCR_PS(0);         /* FXIO0_D8  */


//    PORT4->PCR[15]   = PORT_PCR_MUX(11) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* CAN1 */
//    PORT4->PCR[16]   = PORT_PCR_MUX(11) | PORT_PCR_PS(0) | PORT_PCR_PE(1) | PORT_PCR_IBE(1);     /* CAN */


    PORT4->PCR[17] = PORT_PCR_MUX(FLEXIO_DATA9_MUX)  | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D9  */
    PORT4->PCR[18] = PORT_PCR_MUX(FLEXIO_DATA10_MUX) | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D10 */
    PORT4->PCR[19] = PORT_PCR_MUX(FLEXIO_DATA11_MUX) | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D11 */
    PORT4->PCR[20] = PORT_PCR_MUX(FLEXIO_DATA12_MUX) | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D12 */
    PORT4->PCR[21] = PORT_PCR_MUX(FLEXIO_DATA13_MUX) | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D13 */
    PORT4->PCR[22] = PORT_PCR_MUX(FLEXIO_DATA14_MUX) | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D14 */
    PORT4->PCR[23] = PORT_PCR_MUX(FLEXIO_DATA15_MUX) | PORT_PCR_PE_MASK | PORT_PCR_PS(0);       /* FXIO0_D15 */


    /* ENET */
    PORT1->PCR[13]   = PORT_PCR_MUX(9) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ENET0_RXDV */
    PORT1->PCR[14]   = PORT_PCR_MUX(9) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ENET0_RXD0 */
    PORT1->PCR[15]   = PORT_PCR_MUX(9) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ENET0_RXD1 */
    PORT1->PCR[20]   = PORT_PCR_MUX(9) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ENET0_MDC */
    PORT1->PCR[21]   = PORT_PCR_MUX(9) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ENET0_MDIO */
    PORT1->PCR[4]    = PORT_PCR_MUX(9) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ENET0_TX_CLK */
    PORT1->PCR[5]    = PORT_PCR_MUX(9) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ENET0_TXEN */
    PORT1->PCR[6]    = PORT_PCR_MUX(9) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ENET0_TXD0 */
    PORT1->PCR[7]    = PORT_PCR_MUX(9) | PORT_PCR_PS(0) | PORT_PCR_PE(0) | PORT_PCR_IBE(1);     /* ENET0_TXD1 */

}



/* Configure port mux of FlexIO data pins */
void FLEXIO_8080_Config_Data_Pin(void)
{

}


/* Configure FLEXIO_WR pin as FlexIO function */
void FLEXIO_8080_Config_WR_FlexIO(void)
{
   // FLEXIO_WR_PORT->PCR[FLEXIO_WR_PIN] = PORT_PCR_MUX(FLEXIO_WR_PIN_MUX) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
}

/* Configure FLEXIO_WR pin as GPIO function and outputting high level */
void FLEXIO_8080_Config_WR_GPIO(void)
{

}

/* Configure FLEXIO_RD pin as FlexIO function */
void FLEXIO_8080_Config_RD_FlexIO(void)
{
  //  FLEXIO_RD_PORT->PCR[FLEXIO_RD_PIN] = PORT_PCR_MUX(FLEXIO_RD_PIN_MUX) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
}

/* Configure FLEXIO_RD pin as GPIO function and outputting high level */
void FLEXIO_8080_Config_RD_GPIO(void)
{
//    FLEXIO_RD_GPIO->PSOR |= 1U << FLEXIO_RD_PIN;
//    FLEXIO_RD_GPIO->PDDR |= 1U << FLEXIO_RD_PIN;
//    FLEXIO_RD_PORT->PCR[FLEXIO_RD_PIN] = PORT_PCR_MUX(0U) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
}

/* Configure FLEXIO_CS pin as GPIO function and outputting high level */
void FLEXIO_8080_Config_CS_GPIO(void)
{
    FLEXIO_CS_GPIO->PSOR |= 1U << FLEXIO_CS_PIN;
    FLEXIO_CS_GPIO->PDDR |= 1U << FLEXIO_CS_PIN;
//    FLEXIO_CS_PORT->PCR[FLEXIO_CS_PIN] = PORT_PCR_MUX(0U) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
}

/* Set FLEXIO_CS pin's level */
void FLEXIO_8080_Set_CS_Pin(bool level)
{
    if(level)
    {
        FLEXIO_CS_GPIO->PSOR |= 1U << FLEXIO_CS_PIN;
    }
    else
    {
        FLEXIO_CS_GPIO->PCOR |= 1U << FLEXIO_CS_PIN;
    }
}

/* Configure RS pin as GPIO function and outputting high level */
void FLEXIO_8080_Config_RS_GPIO(void)
{
    FLEXIO_RS_GPIO->PSOR |= 1U << FLEXIO_RS_PIN;
    FLEXIO_RS_GPIO->PDDR |= 1U << FLEXIO_RS_PIN;
//    FLEXIO_RS_PORT->PCR[FLEXIO_RS_PIN] = PORT_PCR_MUX(0U) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
}

/* Set RS pin's level */
void FLEXIO_8080_Set_RS_Pin(bool level)
{
    if(level)
    {
        FLEXIO_RS_GPIO->PSOR |= 1U << FLEXIO_RS_PIN;
    }
    else
    {
        FLEXIO_RS_GPIO->PCOR |= 1U << FLEXIO_RS_PIN;
    }
}

/* Configure ReSet pin as GPIO function and outputting high level */
void FLEXIO_8080_Config_ReSet_GPIO(void)
{
    FLEXIO_ReSet_GPIO->PSOR |= 1U << FLEXIO_ReSet_PIN;
    FLEXIO_ReSet_GPIO->PDDR |= 1U << FLEXIO_ReSet_PIN;
    FLEXIO_ReSet_PORT->PCR[FLEXIO_ReSet_PIN] = PORT_PCR_MUX(0U) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
}

/* Set ReSet pin's level */
void FLEXIO_8080_Set_ReSet_Pin(bool level)
{
    if(level)
    {
        FLEXIO_ReSet_GPIO->PSOR |= 1U << FLEXIO_ReSet_PIN;
    }
    else
    {
        FLEXIO_ReSet_GPIO->PCOR |= 1U << FLEXIO_ReSet_PIN;
    }
}
