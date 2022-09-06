#ifndef __SWM320_PORT_H__
#define __SWM320_PORT_H__

void PORT_Init(uint32_t PORTx, uint32_t n, uint32_t func, uint32_t digit_in_en);    //端口引脚功能选择，其可取值如下：

#define PORTA   0
#define PORTB   1
#define PORTC   2
#define PORTM   3
#define PORTN   4
#define PORTP   5

#define PORTA_PIN0_GPIO         0
#define PORTA_PIN0_FUNMUX       1
#define PORTA_PIN0_SWCLK        2

#define PORTA_PIN1_GPIO         0
#define PORTA_PIN1_FUNMUX       1
#define PORTA_PIN1_SWDIO        2

#define PORTA_PIN2_GPIO         0
#define PORTA_PIN2_FUNMUX       1

#define PORTA_PIN3_GPIO         0
#define PORTA_PIN3_FUNMUX       1

#define PORTA_PIN4_GPIO         0
#define PORTA_PIN4_FUNMUX       1

#define PORTA_PIN5_GPIO         0
#define PORTA_PIN5_FUNMUX       1

#define PORTA_PIN6_GPIO         0
#define PORTA_PIN6_FUNMUX       1

#define PORTA_PIN7_GPIO         0
#define PORTA_PIN7_FUNMUX       1

#define PORTA_PIN8_GPIO         0
#define PORTA_PIN8_FUNMUX       1

#define PORTA_PIN9_GPIO         0
#define PORTA_PIN9_FUNMUX       1
#define PORTA_PIN9_ADC0_IN7     3

#define PORTA_PIN10_GPIO        0
#define PORTA_PIN10_FUNMUX      1
#define PORTA_PIN10_ADC0_IN6    3

#define PORTA_PIN11_GPIO        0
#define PORTA_PIN11_FUNMUX      1
#define PORTA_PIN11_ADC0_IN5    3

#define PORTA_PIN12_GPIO        0
#define PORTA_PIN12_ADC0_IN4    3


#define PORTB_PIN0_GPIO         0
#define PORTB_PIN0_FUNMUX       1
#define PORTB_PIN0_SD_DETECT    2

#define PORTB_PIN1_GPIO         0
#define PORTB_PIN1_FUNMUX       1
#define PORTB_PIN1_SD_CLK       2

#define PORTB_PIN2_GPIO         0
#define PORTB_PIN2_FUNMUX       1
#define PORTB_PIN2_SD_CMD       2

#define PORTB_PIN3_GPIO         0
#define PORTB_PIN3_FUNMUX       1
#define PORTB_PIN3_SD_D0        2

#define PORTB_PIN4_GPIO         0
#define PORTB_PIN4_FUNMUX       1
#define PORTB_PIN4_SD_D1        2

#define PORTB_PIN5_GPIO         0
#define PORTB_PIN5_FUNMUX       1
#define PORTB_PIN5_SD_D2        2

#define PORTB_PIN6_GPIO         0
#define PORTB_PIN6_FUNMUX       1
#define PORTB_PIN6_SD_D3        2

#define PORTB_PIN7_GPIO         0
#define PORTB_PIN7_FUNMUX       1
#define PORTB_PIN7_SD_D4        2

#define PORTB_PIN8_GPIO         0
#define PORTB_PIN8_FUNMUX       1
#define PORTB_PIN8_SD_D5        2

#define PORTB_PIN9_GPIO         0
#define PORTB_PIN9_FUNMUX       1
#define PORTB_PIN9_SD_D6        2

#define PORTB_PIN10_GPIO        0
#define PORTB_PIN10_FUNMUX      1
#define PORTB_PIN10_SD_D7       2

#define PORTB_PIN11_GPIO        0
#define PORTB_PIN11_FUNMUX      1

#define PORTB_PIN12_GPIO        0


#define PORTC_PIN0_GPIO         0
#define PORTC_PIN0_FUNMUX       1

#define PORTC_PIN1_GPIO         0
#define PORTC_PIN1_FUNMUX       1

#define PORTC_PIN2_GPIO         0
#define PORTC_PIN2_FUNMUX       1

#define PORTC_PIN3_GPIO         0
#define PORTC_PIN3_FUNMUX       1

#define PORTC_PIN4_GPIO         0
#define PORTC_PIN4_FUNMUX       1
#define PORTC_PIN4_ADC1_IN3     3

#define PORTC_PIN5_GPIO         0
#define PORTC_PIN5_FUNMUX       1
#define PORTC_PIN5_ADC1_IN2     3

#define PORTC_PIN6_GPIO         0
#define PORTC_PIN6_FUNMUX       1
#define PORTC_PIN6_ADC1_IN1     3

#define PORTC_PIN7_GPIO         0
#define PORTC_PIN7_FUNMUX       1
#define PORTC_PIN7_ADC1_IN0     3


#define PORTM_PIN0_GPIO         0
#define PORTM_PIN0_FUNMUX       1
#define PORTM_PIN0_NORFL_D15    2

#define PORTM_PIN1_GPIO         0
#define PORTM_PIN1_FUNMUX       1
#define PORTM_PIN1_NORFL_D14    2

#define PORTM_PIN2_GPIO         0
#define PORTM_PIN2_FUNMUX       1
#define PORTM_PIN2_NORFL_D13    2

#define PORTM_PIN3_GPIO         0
#define PORTM_PIN3_FUNMUX       1
#define PORTM_PIN3_NORFL_D12    2

#define PORTM_PIN4_GPIO         0
#define PORTM_PIN4_FUNMUX       1
#define PORTM_PIN4_NORFL_D11    2

#define PORTM_PIN5_GPIO         0
#define PORTM_PIN5_FUNMUX       1
#define PORTM_PIN5_NORFL_D10    2

#define PORTM_PIN6_GPIO         0
#define PORTM_PIN6_FUNMUX       1
#define PORTM_PIN6_NORFL_D9     2

#define PORTM_PIN7_GPIO         0
#define PORTM_PIN7_FUNMUX       1
#define PORTM_PIN7_NORFL_D8     2

#define PORTM_PIN8_GPIO         0
#define PORTM_PIN8_FUNMUX       1
#define PORTM_PIN8_NORFL_D7     2

#define PORTM_PIN9_GPIO         0
#define PORTM_PIN9_FUNMUX       1
#define PORTM_PIN9_NORFL_D6     2

#define PORTM_PIN10_GPIO        0
#define PORTM_PIN10_FUNMUX      1
#define PORTM_PIN10_NORFL_D5    2

#define PORTM_PIN11_GPIO        0
#define PORTM_PIN11_FUNMUX      1
#define PORTM_PIN11_NORFL_D4    2

#define PORTM_PIN12_GPIO        0
#define PORTM_PIN12_FUNMUX      1
#define PORTM_PIN12_NORFL_D3    2

#define PORTM_PIN13_GPIO        0
#define PORTM_PIN13_FUNMUX      1
#define PORTM_PIN13_NORFL_D2    2

#define PORTM_PIN14_GPIO        0
#define PORTM_PIN14_FUNMUX      1
#define PORTM_PIN14_NORFL_D1    2

#define PORTM_PIN15_GPIO        0
#define PORTM_PIN15_FUNMUX      1
#define PORTM_PIN15_NORFL_D0    2

#define PORTM_PIN16_GPIO        0
#define PORTM_PIN16_FUNMUX      1
#define PORTM_PIN16_NORFL_OEN   2

#define PORTM_PIN17_GPIO        0
#define PORTM_PIN17_FUNMUX      1
#define PORTM_PIN17_NORFL_WEN   2

#define PORTM_PIN18_GPIO        0
#define PORTM_PIN18_FUNMUX      1
#define PORTM_PIN18_NORFL_CSN   2

#define PORTM_PIN19_GPIO        0
#define PORTM_PIN19_FUNMUX      1
#define PORTM_PIN19_SDRAM_CSN   2

#define PORTM_PIN20_GPIO        0
#define PORTM_PIN20_FUNMUX      1
#define PORTM_PIN20_SRAM_CSN    2

#define PORTM_PIN21_GPIO        0
#define PORTM_PIN21_FUNMUX      1
#define PORTM_PIN21_SDRAM_CKE   2


#define PORTN_PIN0_GPIO         0
#define PORTN_PIN0_FUNMUX       1
#define PORTN_PIN0_LCD_D0       2
#define PORTN_PIN0_ADC1_IN4     3

#define PORTN_PIN1_GPIO         0
#define PORTN_PIN1_FUNMUX       1
#define PORTN_PIN1_LCD_D1       2
#define PORTN_PIN1_ADC1_IN5     3

#define PORTN_PIN2_GPIO         0
#define PORTN_PIN2_FUNMUX       1
#define PORTN_PIN2_LCD_D2       2
#define PORTN_PIN2_ADC1_IN6     3

#define PORTN_PIN3_GPIO         0
#define PORTN_PIN3_FUNMUX       1
#define PORTN_PIN3_LCD_D3       2

#define PORTN_PIN4_GPIO         0
#define PORTN_PIN4_FUNMUX       1
#define PORTN_PIN4_LCD_D4       2

#define PORTN_PIN5_GPIO         0
#define PORTN_PIN5_FUNMUX       1
#define PORTN_PIN5_LCD_D5       2

#define PORTN_PIN6_GPIO         0
#define PORTN_PIN6_FUNMUX       1
#define PORTN_PIN6_LCD_D6       2

#define PORTN_PIN7_GPIO         0
#define PORTN_PIN7_FUNMUX       1
#define PORTN_PIN7_LCD_D7       2

#define PORTN_PIN8_GPIO         0
#define PORTN_PIN8_FUNMUX       1
#define PORTN_PIN8_LCD_D8       2

#define PORTN_PIN9_GPIO         0
#define PORTN_PIN9_FUNMUX       1
#define PORTN_PIN9_LCD_D9       2

#define PORTN_PIN10_GPIO        0
#define PORTN_PIN10_FUNMUX      1
#define PORTN_PIN10_LCD_D10     2

#define PORTN_PIN11_GPIO        0
#define PORTN_PIN11_FUNMUX      1
#define PORTN_PIN11_LCD_D11     2

#define PORTN_PIN12_GPIO        0
#define PORTN_PIN12_FUNMUX      1
#define PORTN_PIN12_LCD_D12     2

#define PORTN_PIN13_GPIO        0
#define PORTN_PIN13_FUNMUX      1
#define PORTN_PIN13_LCD_D13     2

#define PORTN_PIN14_GPIO        0
#define PORTN_PIN14_FUNMUX      1
#define PORTN_PIN14_LCD_D14     2

#define PORTN_PIN15_GPIO        0
#define PORTN_PIN15_FUNMUX      1
#define PORTN_PIN15_LCD_D15     2

#define PORTN_PIN16_GPIO        0
#define PORTN_PIN16_FUNMUX      1
#define PORTN_PIN16_LCD_RD      2
#define PORTN_PIN16_LCD_DOTCK   2

#define PORTN_PIN17_GPIO        0
#define PORTN_PIN17_FUNMUX      1
#define PORTN_PIN17_LCD_CS      2
#define PORTN_PIN17_LCD_VSYNC   2

#define PORTN_PIN18_GPIO        0
#define PORTN_PIN18_LCD_RS      2
#define PORTN_PIN18_LCD_DATEN   2   //Data Enable

#define PORTN_PIN19_GPIO        0
#define PORTN_PIN19_LCD_WR      2
#define PORTN_PIN19_LCD_HSYNC   2


#define PORTP_PIN0_GPIO         0
#define PORTP_PIN0_FUNMUX       1
#define PORTP_PIN0_NORFL_A0     2

#define PORTP_PIN1_GPIO         0
#define PORTP_PIN1_FUNMUX       1
#define PORTP_PIN1_NORFL_A1     2

#define PORTP_PIN2_GPIO         0
#define PORTP_PIN2_FUNMUX       1
#define PORTP_PIN2_NORFL_A2     2
#define PORTP_PIN2_SD_D7        3

#define PORTP_PIN3_GPIO         0
#define PORTP_PIN3_FUNMUX       1
#define PORTP_PIN3_NORFL_A3     2
#define PORTP_PIN3_SD_D6        3

#define PORTP_PIN4_GPIO         0
#define PORTP_PIN4_FUNMUX       1
#define PORTP_PIN4_NORFL_A4     2
#define PORTP_PIN4_SD_D5        3

#define PORTP_PIN5_GPIO         0
#define PORTP_PIN5_FUNMUX       1
#define PORTP_PIN5_NORFL_A5     2
#define PORTP_PIN5_SD_D4        3

#define PORTP_PIN6_GPIO         0
#define PORTP_PIN6_FUNMUX       1
#define PORTP_PIN6_NORFL_A6     2
#define PORTP_PIN6_SD_D3        3

#define PORTP_PIN7_GPIO         0
#define PORTP_PIN7_FUNMUX       1
#define PORTP_PIN7_NORFL_A7     2
#define PORTP_PIN7_SD_D2        3

#define PORTP_PIN8_GPIO         0
#define PORTP_PIN8_FUNMUX       1
#define PORTP_PIN8_NORFL_A8     2
#define PORTP_PIN8_SD_D1        3

#define PORTP_PIN9_GPIO         0
#define PORTP_PIN9_FUNMUX       1
#define PORTP_PIN9_NORFL_A9     2
#define PORTP_PIN9_SD_D0        3

#define PORTP_PIN10_GPIO        0
#define PORTP_PIN10_FUNMUX      1
#define PORTP_PIN10_NORFL_A10   2
#define PORTP_PIN10_SD_CMD      3

#define PORTP_PIN11_GPIO        0
#define PORTP_PIN11_FUNMUX      1
#define PORTP_PIN11_NORFL_A11   2
#define PORTP_PIN11_SD_CLK      3

#define PORTP_PIN12_GPIO        0
#define PORTP_PIN12_FUNMUX      1
#define PORTP_PIN12_NORFL_A12   2
#define PORTP_PIN12_SD_DETECT   3

#define PORTP_PIN13_GPIO        0
#define PORTP_PIN13_FUNMUX      1
#define PORTP_PIN13_NORFL_A13   2
#define PORTP_PIN13_SDRAM_CLK   2

#define PORTP_PIN14_GPIO        0
#define PORTP_PIN14_FUNMUX      1
#define PORTP_PIN14_NORFL_A14   2
#define PORTP_PIN14_SDRAM_CAS   2

#define PORTP_PIN15_GPIO        0
#define PORTP_PIN15_FUNMUX      1
#define PORTP_PIN15_NORFL_A15   2
#define PORTP_PIN15_SDRAM_RAS   2

#define PORTP_PIN16_GPIO        0
#define PORTP_PIN16_FUNMUX      1
#define PORTP_PIN16_NORFL_A16   2
#define PORTP_PIN16_SDRAM_LDQ   2

#define PORTP_PIN17_GPIO        0
#define PORTP_PIN17_FUNMUX      1
#define PORTP_PIN17_NORFL_A17   2
#define PORTP_PIN17_SDRAM_UDQ   2

#define PORTP_PIN18_GPIO        0
#define PORTP_PIN18_FUNMUX      1
#define PORTP_PIN18_NORFL_A18   2

#define PORTP_PIN19_GPIO        0
#define PORTP_PIN19_FUNMUX      1
#define PORTP_PIN19_NORFL_A19   2

#define PORTP_PIN20_GPIO        0
#define PORTP_PIN20_FUNMUX      1
#define PORTP_PIN20_NORFL_A20   2
#define PORTP_PIN20_SDRAM_BA0   2

#define PORTP_PIN21_GPIO        0
#define PORTP_PIN21_FUNMUX      1
#define PORTP_PIN21_NORFL_A21   2
#define PORTP_PIN21_SDRAM_BA1   2

#define PORTP_PIN22_GPIO        0
#define PORTP_PIN22_FUNMUX      1
#define PORTP_PIN22_NORFL_A22   2

#define PORTP_PIN23_GPIO        0
#define PORTP_PIN23_FUNMUX      1
#define PORTP_PIN23_NORFL_A23   2



/* 下面宏定义的取值全部在正确值的基础上“加100”，以区分上面宏定义的值，从而方便库函数的编写*/
/* 下面这些值是偶数编号引脚的功能取值，如PIN0、PIN2、... */
#define FUNMUX0_UART0_RXD       100
#define FUNMUX0_UART1_RXD       101
#define FUNMUX0_UART2_RXD       102
#define FUNMUX0_UART3_RXD       103
#define FUNMUX0_I2C0_SCL        105
#define FUNMUX0_I2C1_SCL        106
#define FUNMUX0_PWM0A_OUT       107
#define FUNMUX0_PWM2A_OUT       108
#define FUNMUX0_PWM4A_OUT       109
#define FUNMUX0_PWM0B_OUT       110
#define FUNMUX0_PWM2B_OUT       111
#define FUNMUX0_PWM4B_OUT       112
#define FUNMUX0_PWM_BREAK       113
#define FUNMUX0_TIMR0_IN        114
#define FUNMUX0_TIMR2_IN        115
#define FUNMUX0_CAN_RX          116
#define FUNMUX0_SPI0_SSEL       117
#define FUNMUX0_SPI0_MOSI       118
#define FUNMUX0_SPI1_SSEL       119
#define FUNMUX0_SPI1_MOSI       120
#define FUNMUX0_UART0_CTS       121
#define FUNMUX0_UART1_CTS       122
#define FUNMUX0_UART2_CTS       123
#define FUNMUX0_UART3_CTS       124

/* 下面这些值是奇数编号引脚的功能取值，如PIN1、PIN3、... */
#define FUNMUX1_UART0_TXD       100
#define FUNMUX1_UART1_TXD       101
#define FUNMUX1_UART2_TXD       102
#define FUNMUX1_UART3_TXD       103
#define FUNMUX1_I2C0_SDA        105
#define FUNMUX1_I2C1_SDA        106
#define FUNMUX1_PWM1A_OUT       107
#define FUNMUX1_PWM3A_OUT       108
#define FUNMUX1_PWM5A_OUT       109
#define FUNMUX1_PWM1B_OUT       110
#define FUNMUX1_PWM3B_OUT       111
#define FUNMUX1_PWM5B_OUT       112
#define FUNMUX1_PULSE_IN        113
#define FUNMUX1_TIMR1_IN        114
#define FUNMUX1_TIMR3_IN        115
#define FUNMUX1_CAN_TX          116
#define FUNMUX1_SPI0_SCLK       117
#define FUNMUX1_SPI0_MISO       118
#define FUNMUX1_SPI1_SCLK       119
#define FUNMUX1_SPI1_MISO       120
#define FUNMUX1_UART0_RTS       121
#define FUNMUX1_UART1_RTS       122
#define FUNMUX1_UART2_RTS       123
#define FUNMUX1_UART3_RTS       124


#endif //__SWM320_PORT_H__
