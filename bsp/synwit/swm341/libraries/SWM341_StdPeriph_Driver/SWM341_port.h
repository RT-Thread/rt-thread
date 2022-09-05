#ifndef __SWM341_PORT_H__
#define __SWM341_PORT_H__

void PORT_Init(PORT_TypeDef * PORTx, uint32_t n, uint32_t func, uint32_t digit_in_en);  //端口引脚功能选择，其可取值如下：



#define PORTA_PIN0_GPIO         0
#define PORTA_PIN0_I2C0_SDA     1
#define PORTA_PIN0_UART1_TX     2
#define PORTA_PIN0_HALL0_IN0    3
#define PORTA_PIN0_LCD_B7       4
#define PORTA_PIN0_ACMP2_INP    15

#define PORTA_PIN1_GPIO         0
#define PORTA_PIN1_I2C0_SCL     1
#define PORTA_PIN1_UART2_RTS    2
#define PORTA_PIN1_HALL0_IN1    3
#define PORTA_PIN1_LCD_B3       4
#define PORTA_PIN1_ACMP1_INP    15

#define PORTA_PIN2_GPIO         0
#define PORTA_PIN2_UART1_RX     1
#define PORTA_PIN2_PWM_BRK0     2
#define PORTA_PIN2_HALL0_IN2    3
#define PORTA_PIN2_LCD_B4       4
#define PORTA_PIN2_ACMP0_INP    15

#define PORTA_PIN3_GPIO         0
#define PORTA_PIN3_I2C0_SDA     1
#define PORTA_PIN3_LCD_B6       2
#define PORTA_PIN3_XTAL_IN      15

#define PORTA_PIN4_GPIO         0
#define PORTA_PIN4_I2C0_SCL     1
#define PORTA_PIN4_LCD_B5       2
#define PORTA_PIN4_XTAL_OUT     15

#define PORTA_PIN5_GPIO         0
#define PORTA_PIN5_PWM_BRK1     1
#define PORTA_PIN5_PWM_CLK1     2
#define PORTA_PIN5_SDR_LDQM     3

#define PORTA_PIN6_GPIO         0
#define PORTA_PIN6_I2C1_SDA     1
#define PORTA_PIN6_PWM_BRK0     2
#define PORTA_PIN6_PWM_CLK0     3

#define PORTA_PIN7_GPIO         0
#define PORTA_PIN7_I2C1_SCL     1
#define PORTA_PIN7_TIMR3_IN     2
#define PORTA_PIN7_TIMR3_OUT    3

#define PORTA_PIN8_GPIO         0

#define PORTA_PIN9_GPIO         0
#define PORTA_PIN9_CAN0_RX      1
#define PORTA_PIN9_LCD_B5       2
#define PORTA_PIN9_OPA1_INN     15

#define PORTA_PIN10_GPIO        0
#define PORTA_PIN10_UART0_CTS   1
#define PORTA_PIN10_PWM_CLK1    2
#define PORTA_PIN10_BTIMR3_OUT  3
#define PORTA_PIN10_CAN0_TX     4
#define PORTA_PIN10_LCD_B6      5
#define PORTA_PIN10_ADC0_CH11   15
#define PORTA_PIN10_OPA1_OUT    15

#define PORTA_PIN11_GPIO        0
#define PORTA_PIN11_UART0_RTS   1
#define PORTA_PIN11_PWM_CLK0    2
#define PORTA_PIN11_BTIMR2_OUT  3
#define PORTA_PIN11_LCD_B7      4
#define PORTA_PIN11_ADC1_TRIG1  5
#define PORTA_PIN11_OPA1_INP    15

#define PORTA_PIN12_GPIO        0
#define PORTA_PIN12_UART0_RX    1
#define PORTA_PIN12_HALL3_IN0   2
#define PORTA_PIN12_BTIMR1_OUT  3
#define PORTA_PIN12_LCD_G0      4
#define PORTA_PIN12_ADC0_TRIG1  5
#define PORTA_PIN12_ADC0_CH10   15

#define PORTA_PIN13_GPIO        0
#define PORTA_PIN13_UART0_TX    1
#define PORTA_PIN13_HALL3_IN1   2
#define PORTA_PIN13_BTIMR0_OUT  3
#define PORTA_PIN13_LCD_G1      4
#define PORTA_PIN13_ADC0_CH9    15
#define PORTA_PIN13_OPA3_INN    15

#define PORTA_PIN14_GPIO        0
#define PORTA_PIN14_HALL3_IN2   1
#define PORTA_PIN14_LCD_G2      2
#define PORTA_PIN14_ADC0_CH8    15
#define PORTA_PIN14_OPA3_INP    15

#define PORTA_PIN15_GPIO        0
#define PORTA_PIN15_HALL3_IN0   1
#define PORTA_PIN15_LCD_G3      2
#define PORTA_PIN15_ADC0_CH7    15
#define PORTA_PIN15_OPA3_OUT    15

#define PORTB_PIN0_GPIO         0
#define PORTB_PIN0_UART1_TX     1
#define PORTB_PIN0_PWM3BN       2
#define PORTB_PIN0_DMA_TRIG1    3
#define PORTB_PIN0_TIMR1_IN     4
#define PORTB_PIN0_TIMR1_OUT    5
#define PORTB_PIN0_SD_D6        6

#define PORTB_PIN1_GPIO         0
#define PORTB_PIN1_PWM3B        1
#define PORTB_PIN1_TIMR0_IN     2
#define PORTB_PIN1_TIMR0_OUT    3
#define PORTB_PIN1_LCD_B0       4
#define PORTB_PIN1_SD_D7        5

#define PORTB_PIN2_GPIO         0
#define PORTB_PIN2_SPI1_SCLK    1
#define PORTB_PIN2_UART3_RTS    2
#define PORTB_PIN2_PWM2B        3
#define PORTB_PIN2_BTIMR3_OUT   4
#define PORTB_PIN2_CAN1_TX      5
#define PORTB_PIN2_LCD_CS       6
#define PORTB_PIN2_LCD_VSYNC    6

#define PORTB_PIN3_GPIO         0
#define PORTB_PIN3_SPI1_MISO    1
#define PORTB_PIN3_UART3_TX     2
#define PORTB_PIN3_PWM2A        3
#define PORTB_PIN3_HALL0_IN0    4
#define PORTB_PIN3_BTIMR2_OUT   5
#define PORTB_PIN3_CAN1_RX      6
#define PORTB_PIN3_LCD_WR       7
#define PORTB_PIN3_LCD_HSYNC    7

#define PORTB_PIN4_GPIO         0
#define PORTB_PIN4_SPI1_MOSI    1
#define PORTB_PIN4_UART3_RX     2
#define PORTB_PIN4_HALL0_IN1    3
#define PORTB_PIN4_BTIMR1_OUT   4
#define PORTB_PIN4_CAN0_TX      5
#define PORTB_PIN4_LCD_RS       6
#define PORTB_PIN4_LCD_DEN      6
#define PORTB_PIN4_ACMP2_INN    15

#define PORTB_PIN5_GPIO         0
#define PORTB_PIN5_SPI1_SSEL    1
#define PORTB_PIN5_UART3_CTS    2
#define PORTB_PIN5_HALL0_IN2    3
#define PORTB_PIN5_BTIMR0_OUT   4
#define PORTB_PIN5_CAN0_RX      5
#define PORTB_PIN5_LCD_RD       6
#define PORTB_PIN5_LCD_DCLK     6
#define PORTB_PIN5_ACMP1_INN    15

#define PORTB_PIN6_GPIO         0
#define PORTB_PIN6_SDR_LDQM     1

#define PORTB_PIN7_GPIO         0
#define PORTB_PIN7_SDR_WE       1

#define PORTB_PIN8_GPIO         0
#define PORTB_PIN8_SPI0_SCLK    1
#define PORTB_PIN8_TIMR3_IN     2
#define PORTB_PIN8_TIMR3_OUT    3
#define PORTB_PIN8_SDR_CAS      4

#define PORTB_PIN9_GPIO         0
#define PORTB_PIN9_SPI0_MISO    1
#define PORTB_PIN9_TIMR2_IN     2
#define PORTB_PIN9_TIMR2_OUT    3
#define PORTB_PIN9_SDR_RAS      4

#define PORTB_PIN10_GPIO        0
#define PORTB_PIN10_SPI0_MOSI   1
#define PORTB_PIN10_TIMR1_IN    2
#define PORTB_PIN10_TIMR1_OUT   3
#define PORTB_PIN10_SDR_CS      4

#define PORTB_PIN11_GPIO        0
#define PORTB_PIN11_JTAG_TDO    1
#define PORTB_PIN11_UART2_TX    2
#define PORTB_PIN11_PWM_BRK2    3
#define PORTB_PIN11_TIMR0_IN    4
#define PORTB_PIN11_TIMR0_OUT   5
#define PORTB_PIN11_LCD_B1      6

#define PORTB_PIN12_GPIO        0
#define PORTB_PIN12_SWDCK       1
#define PORTB_PIN12_JTAG_TCK    1
#define PORTB_PIN12_UART0_RX    2
#define PORTB_PIN12_PWM4BN      3
#define PORTB_PIN12_TIMR3_IN    4
#define PORTB_PIN12_TIMR3_OUT   5
#define PORTB_PIN12_ACMP0_INN   15

#define PORTB_PIN13_GPIO        0
#define PORTB_PIN13_JTAG_TDI    1
#define PORTB_PIN13_I2C1_SDA    2
#define PORTB_PIN13_UART2_RX    3
#define PORTB_PIN13_PWM4B       4
#define PORTB_PIN13_TIMR2_IN    5
#define PORTB_PIN13_TIMR2_OUT   6
#define PORTB_PIN13_LCD_B2      7

#define PORTB_PIN14_GPIO        0
#define PORTB_PIN14_SWDIO       1
#define PORTB_PIN14_JTAG_TMS    1
#define PORTB_PIN14_SPI0_SSEL   2
#define PORTB_PIN14_UART0_TX    3
#define PORTB_PIN14_PWM4AN      4
#define PORTB_PIN14_TIMR1_IN    5
#define PORTB_PIN14_TIMR1_OUT   6

#define PORTB_PIN15_GPIO        0
#define PORTB_PIN15_JTAG_TRST   1
#define PORTB_PIN15_I2C1_SCL    2
#define PORTB_PIN15_UART2_CTS   3
#define PORTB_PIN15_PWM4A       4
#define PORTB_PIN15_TIMR0_IN    5
#define PORTB_PIN15_TIMR0_OUT   6
#define PORTB_PIN15_LCD_B3      7

#define PORTC_PIN0_GPIO         0
#define PORTC_PIN0_UART2_TX     1
#define PORTC_PIN0_HALL3_IN1    2
#define PORTC_PIN0_TIMR1_IN     3
#define PORTC_PIN0_TIMR1_OUT    4
#define PORTC_PIN0_LCD_G4       5
#define PORTC_PIN0_ADC0_CH6     15

#define PORTC_PIN1_GPIO         0
#define PORTC_PIN1_I2C0_SDA     1
#define PORTC_PIN1_UART2_RX     2
#define PORTC_PIN1_HALL3_IN2    3
#define PORTC_PIN1_TIMR0_IN     4
#define PORTC_PIN1_TIMR0_OUT    5
#define PORTC_PIN1_LCD_G5       6
#define PORTC_PIN1_ADC0_CH5     15
#define PORTC_PIN1_OPA2_INN     15

#define PORTC_PIN2_GPIO         0
#define PORTC_PIN2_I2C0_SCL     1
#define PORTC_PIN2_UART3_RX     2
#define PORTC_PIN2_PWM3A        3
#define PORTC_PIN2_TIMR2_IN     4
#define PORTC_PIN2_TIMR2_OUT    5
#define PORTC_PIN2_LCD_G6       6
#define PORTC_PIN2_ADC0_CH4     15
#define PORTC_PIN2_OPA2_INP     15

#define PORTC_PIN3_GPIO         0
#define PORTC_PIN3_UART3_TX     1
#define PORTC_PIN3_PWM3AN       2
#define PORTC_PIN3_BTIMR11_OUT  3
#define PORTC_PIN3_TIMR3_IN     4
#define PORTC_PIN3_TIMR3_OUT    5
#define PORTC_PIN3_LCD_G7       6
#define PORTC_PIN3_ADC0_CH3     15
#define PORTC_PIN3_OPA2_OUT     15

#define PORTC_PIN4_GPIO         0
#define PORTC_PIN4_I2C1_SDA     1
#define PORTC_PIN4_SPI1_SSEL    2
#define PORTC_PIN4_BTIMR10_OUT  3
#define PORTC_PIN4_TIMR4_IN     4
#define PORTC_PIN4_TIMR4_OUT    5
#define PORTC_PIN4_LCD_R0       6
#define PORTC_PIN4_ADC0_CH2     15

#define PORTC_PIN5_GPIO         0
#define PORTC_PIN5_I2C1_SCL     1
#define PORTC_PIN5_SPI1_MISO    2
#define PORTC_PIN5_BTIMR9_OUT   3
#define PORTC_PIN5_LCD_R1       4
#define PORTC_PIN5_ADC0_CH1     15
#define PORTC_PIN5_OPA0_INN     15

#define PORTC_PIN6_GPIO         0
#define PORTC_PIN6_SPI1_MOSI    1
#define PORTC_PIN6_BTIMR8_OUT   2
#define PORTC_PIN6_ADC0_CH0     15

#define PORTC_PIN7_GPIO         0
#define PORTC_PIN7_SPI1_SCLK    1

#define PORTC_PIN8_GPIO         0
#define PORTC_PIN8_LCD_R2       1
#define PORTC_PIN8_OPA0_INP     15

#define PORTC_PIN9_GPIO         0
#define PORTC_PIN9_BTIMR7_OUT   1
#define PORTC_PIN9_TIMR2_IN     2
#define PORTC_PIN9_TIMR2_OUT    3
#define PORTC_PIN9_LCD_R3       4
#define PORTC_PIN9_ADC1_CH6     15
#define PORTC_PIN9_OPA0_OUT     15

#define PORTC_PIN10_GPIO        0
#define PORTC_PIN10_BTIMR6_OUT  1
#define PORTC_PIN10_TIMR1_IN    2
#define PORTC_PIN10_TIMR1_OUT   3
#define PORTC_PIN10_LCD_R4      4
#define PORTC_PIN10_ADC1_CH5    15

#define PORTC_PIN11_GPIO        0
#define PORTC_PIN11_BTIMR5_OUT  1
#define PORTC_PIN11_TIMR0_IN    2
#define PORTC_PIN11_TIMR0_OUT   3
#define PORTC_PIN11_LCD_R5      4
#define PORTC_PIN11_ADC1_CH4    15

#define PORTC_PIN12_GPIO        0
#define PORTC_PIN12_UART0_RX    1
#define PORTC_PIN12_BTIMR4_OUT  2
#define PORTC_PIN12_LCD_R6      3
#define PORTC_PIN12_ADC1_CH3    15

#define PORTC_PIN13_GPIO        0
#define PORTC_PIN13_I2C0_SDA    1
#define PORTC_PIN13_UART0_TX    2
#define PORTC_PIN13_BTIMR3_OUT  3
#define PORTC_PIN13_TIMR4_IN    4
#define PORTC_PIN13_TIMR4_OUT   5
#define PORTC_PIN13_LCD_R7      6
#define PORTC_PIN13_ADC1_CH2    15

#define PORTC_PIN14_GPIO        0
#define PORTC_PIN14_SDR_D14     1

#define PORTC_PIN15_GPIO        0
#define PORTC_PIN15_SDR_D15     1

#define PORTD_PIN0_GPIO         0
#define PORTD_PIN0_I2C0_SCL     1
#define PORTD_PIN0_TIMR3_IN     2
#define PORTD_PIN0_TIMR3_OUT    3
#define PORTD_PIN0_LCD_R4       4
#define PORTD_PIN0_ADC1_CH1     15

#define PORTD_PIN1_GPIO         0
#define PORTD_PIN1_LCD_R5       1
#define PORTD_PIN1_ADC1_CH0     15

#define PORTD_PIN2_GPIO         0
#define PORTD_PIN2_QEI_Z        1
#define PORTD_PIN2_HALL3_IN0    2
#define PORTD_PIN2_DAC_OUT      15

#define PORTD_PIN3_GPIO         0
#define PORTD_PIN3_QEI_B        1
#define PORTD_PIN3_FSPI_DATA2   2
#define PORTD_PIN3_UART1_TX     3
#define PORTD_PIN3_HALL3_IN1    4
#define PORTD_PIN3_CAN1_TX      5
#define PORTD_PIN3_ADC1_TRIG1   6

#define PORTD_PIN4_GPIO         0
#define PORTD_PIN4_QEI_A        1
#define PORTD_PIN4_FSPI_DATA3   2
#define PORTD_PIN4_UART1_RX     3
#define PORTD_PIN4_HALL3_IN2    4
#define PORTD_PIN4_BTIMR11_OUT  5
#define PORTD_PIN4_CAN1_RX      6
#define PORTD_PIN4_ADC0_TRIG1   7

#define PORTD_PIN5_GPIO         0
#define PORTD_PIN5_FSPI_SCLK    1
#define PORTD_PIN5_UART3_TX     2
#define PORTD_PIN5_PWM_CLK1     3
#define PORTD_PIN5_BTIMR10_OUT  4
#define PORTD_PIN5_CAN0_TX      5

#define PORTD_PIN6_GPIO         0
#define PORTD_PIN6_FSPI_SSEL    1
#define PORTD_PIN6_UART3_RX     2
#define PORTD_PIN6_PWM_CLK0     3
#define PORTD_PIN6_BTIMR9_OUT   4
#define PORTD_PIN6_CAN0_RX      5
#define PORTD_PIN6_WAKEUP       15

#define PORTD_PIN7_GPIO         0
#define PORTD_PIN7_QEI_DIR      1
#define PORTD_PIN7_I2C1_SDA     2
#define PORTD_PIN7_FSPI_MISO    3
#define PORTD_PIN7_BTIMR8_OUT   4

#define PORTD_PIN8_GPIO         0
#define PORTD_PIN8_I2C1_SCL     1
#define PORTD_PIN8_FSPI_MOSI    2
#define PORTD_PIN8_PWM1BN       3
#define PORTD_PIN8_TIMR4_IN     4
#define PORTD_PIN8_TIMR4_OUT    5

#define PORTD_PIN9_GPIO         0
#define PORTD_PIN9_PWM1B        1
#define PORTD_PIN9_TIMR3_IN     2
#define PORTD_PIN9_TIMR3_OUT    3

#define PORTD_PIN10_GPIO        0
#define PORTD_PIN10_PWM_CLK1    1
#define PORTD_PIN10_SDR_UDQM    2

#define PORTD_PIN11_GPIO        0
#define PORTD_PIN11_PWM_CLK0    1

#define PORTD_PIN12_GPIO        0

#define PORTD_PIN13_GPIO        0

#define PORTD_PIN14_GPIO        0

#define PORTD_PIN15_GPIO        0
#define PORTD_PIN15_WAKEUP      15

#define PORTE_PIN0_GPIO         0
#define PORTE_PIN0_SDR_D7       1

#define PORTE_PIN1_GPIO         0
#define PORTE_PIN1_SDR_D6       1

#define PORTE_PIN2_GPIO         0
#define PORTE_PIN2_SDR_D5       1

#define PORTE_PIN3_GPIO         0
#define PORTE_PIN3_SDR_D4       1

#define PORTE_PIN4_GPIO         0
#define PORTE_PIN4_SDR_D3       1

#define PORTE_PIN5_GPIO         0
#define PORTE_PIN5_SDR_D2       1

#define PORTE_PIN6_GPIO         0
#define PORTE_PIN6_SDR_D1       1

#define PORTE_PIN7_GPIO         0
#define PORTE_PIN7_SDR_D0       1

#define PORTE_PIN8_GPIO         0
#define PORTE_PIN8_SDR_D8       1

#define PORTE_PIN9_GPIO         0
#define PORTE_PIN9_SDR_D9       1

#define PORTE_PIN10_GPIO        0
#define PORTE_PIN10_SDR_D10     1

#define PORTE_PIN11_GPIO        0
#define PORTE_PIN11_SDR_D11     1

#define PORTE_PIN12_GPIO        0
#define PORTE_PIN12_SDR_D12     1

#define PORTE_PIN13_GPIO        0
#define PORTE_PIN13_SDR_D13     1

#define PORTE_PIN14_GPIO        0
#define PORTE_PIN14_SDR_BA1     1

#define PORTE_PIN15_GPIO        0
#define PORTE_PIN15_SDR_BA0     1

#define PORTM_PIN0_GPIO         0
#define PORTM_PIN0_UART0_RX     1
#define PORTM_PIN0_PWM_BRK1     2
#define PORTM_PIN0_CAN1_TX      3

#define PORTM_PIN1_GPIO         0
#define PORTM_PIN1_UART0_TX     1
#define PORTM_PIN1_PWM0A        2
#define PORTM_PIN1_TIMR2_IN     3
#define PORTM_PIN1_TIMR2_OUT    4
#define PORTM_PIN1_CAN1_RX      5

#define PORTM_PIN2_GPIO         0
#define PORTM_PIN2_SPI0_SCLK    1
#define PORTM_PIN2_UART1_RX     2
#define PORTM_PIN2_PWM0B        3
#define PORTM_PIN2_BTIMR3_OUT   4
#define PORTM_PIN2_TIMR1_IN     5
#define PORTM_PIN2_TIMR1_OUT    6
#define PORTM_PIN2_SD_CLK       7

#define PORTM_PIN3_GPIO         0
#define PORTM_PIN3_SPI0_SSEL    1
#define PORTM_PIN3_UART1_TX     2
#define PORTM_PIN3_PWM1A        3
#define PORTM_PIN3_BTIMR2_OUT   4
#define PORTM_PIN3_TIMR0_IN     5
#define PORTM_PIN3_TIMR0_OUT    6
#define PORTM_PIN3_SD_DET       7

#define PORTM_PIN4_GPIO         0
#define PORTM_PIN4_SPI0_MISO    1
#define PORTM_PIN4_UART3_TX     2
#define PORTM_PIN4_PWM0AN       3
#define PORTM_PIN4_BTIMR1_OUT   4
#define PORTM_PIN4_TIMR2_IN     5
#define PORTM_PIN4_TIMR2_OUT    6
#define PORTM_PIN4_LCD_CS       7
#define PORTM_PIN4_LCD_VSYNC    7
#define PORTM_PIN4_SD_CMD       8

#define PORTM_PIN5_GPIO         0
#define PORTM_PIN5_I2C1_SDA     1
#define PORTM_PIN5_SPI0_MOSI    2
#define PORTM_PIN5_UART3_RX     3
#define PORTM_PIN5_PWM0BN       4
#define PORTM_PIN5_BTIMR0_OUT   5
#define PORTM_PIN5_TIMR1_IN     6
#define PORTM_PIN5_TIMR1_OUT    7
#define PORTM_PIN5_SD_D0        8

#define PORTM_PIN6_GPIO         0
#define PORTM_PIN6_I2C1_SCL     1
#define PORTM_PIN6_UART2_RX     2
#define PORTM_PIN6_PWM1AN       3
#define PORTM_PIN6_TIMR0_IN     4
#define PORTM_PIN6_TIMR0_OUT    5
#define PORTM_PIN6_SD_D1        6

#define PORTM_PIN7_GPIO         0
#define PORTM_PIN7_UART2_TX     1

#define PORTM_PIN8_GPIO         0
#define PORTM_PIN8_PWM2BN       1
#define PORTM_PIN8_CAN0_TX      2
#define PORTM_PIN8_LCD_WR       3
#define PORTM_PIN8_LCD_HSYNC    3

#define PORTM_PIN9_GPIO         0
#define PORTM_PIN9_PWM2AN       1
#define PORTM_PIN9_CAN0_RX      2

#define PORTM_PIN10_GPIO        0
#define PORTM_PIN10_PWM3A       1

#define PORTM_PIN11_GPIO        0
#define PORTM_PIN11_PWM2B       1
#define PORTM_PIN11_LCD_RS      2
#define PORTM_PIN11_LCD_DEN     2

#define PORTM_PIN12_GPIO        0
#define PORTM_PIN12_PWM2A       1
#define PORTM_PIN12_SDR_UDQM    2

#define PORTM_PIN13_GPIO        0
#define PORTM_PIN13_PWM_BRK0    1
#define PORTM_PIN13_SDR_CLK     2

#define PORTM_PIN14_GPIO        0
#define PORTM_PIN14_TIMR3_IN    1
#define PORTM_PIN14_TIMR3_OUT   2
#define PORTM_PIN14_SDR_CKE     3

#define PORTM_PIN15_GPIO        0
#define PORTM_PIN15_TIMR2_IN    1
#define PORTM_PIN15_TIMR2_OUT   2
#define PORTM_PIN15_SDR_A12     3

#define PORTN_PIN0_GPIO         0
#define PORTN_PIN0_SPI1_SCLK    1
#define PORTN_PIN0_PWM3AN       2
#define PORTN_PIN0_BTIMR7_OUT   3
#define PORTN_PIN0_TIMR1_IN     4
#define PORTN_PIN0_TIMR1_OUT    5
#define PORTN_PIN0_LCD_RD       6
#define PORTN_PIN0_LCD_DCLK     6
#define PORTN_PIN0_SD_D2        7

#define PORTN_PIN1_GPIO         0
#define PORTN_PIN1_SPI1_SSEL    1
#define PORTN_PIN1_PWM2BN       2
#define PORTN_PIN1_BTIMR6_OUT   3
#define PORTN_PIN1_TIMR0_IN     4
#define PORTN_PIN1_TIMR0_OUT    5
#define PORTN_PIN1_SD_D3        6

#define PORTN_PIN2_GPIO         0
#define PORTN_PIN2_SDR_A11      1

#define PORTN_PIN3_GPIO         0
#define PORTN_PIN3_UART1_CTS    1
#define PORTN_PIN3_SDR_A9       2

#define PORTN_PIN4_GPIO         0
#define PORTN_PIN4_I2C0_SDA     1
#define PORTN_PIN4_SPI1_MISO    2
#define PORTN_PIN4_UART1_RTS    3
#define PORTN_PIN4_PWM2AN       4
#define PORTN_PIN4_BTIMR5_OUT   5
#define PORTN_PIN4_TIMR3_IN     6
#define PORTN_PIN4_TIMR3_OUT    7
#define PORTN_PIN4_CAN0_TX      8
#define PORTN_PIN4_SD_D4        9
#define PORTN_PIN4_ADC1_TRIG0   10

#define PORTN_PIN5_GPIO         0
#define PORTN_PIN5_I2C0_SCL     1
#define PORTN_PIN5_SPI1_MOSI    2
#define PORTN_PIN5_UART1_RX     3
#define PORTN_PIN5_PWM3A        4
#define PORTN_PIN5_DMA_TRIG0    5
#define PORTN_PIN5_BTIMR4_OUT   6
#define PORTN_PIN5_TIMR2_IN     7
#define PORTN_PIN5_TIMR2_OUT    8
#define PORTN_PIN5_CAN0_RX      9
#define PORTN_PIN5_LCD_R3       10
#define PORTN_PIN5_SD_D5        11
#define PORTN_PIN5_ADC0_TRIG0   12

#define PORTN_PIN6_GPIO         0
#define PORTN_PIN6_SDR_A8       1

#define PORTN_PIN7_GPIO         0
#define PORTN_PIN7_SDR_A7       1

#define PORTN_PIN8_GPIO         0
#define PORTN_PIN8_SDR_A6       1

#define PORTN_PIN9_GPIO         0
#define PORTN_PIN9_SDR_A5       1

#define PORTN_PIN10_GPIO        0
#define PORTN_PIN10_SDR_A4      1

#define PORTN_PIN11_GPIO        0
#define PORTN_PIN11_SDR_A3      1

#define PORTN_PIN12_GPIO        0
#define PORTN_PIN12_SDR_A2      1

#define PORTN_PIN13_GPIO        0
#define PORTN_PIN13_SDR_A1      1

#define PORTN_PIN14_GPIO        0
#define PORTN_PIN14_SDR_A0      1

#define PORTN_PIN15_GPIO        0
#define PORTN_PIN15_SDR_A10     1


#endif //__SWM341_PORT_H__
