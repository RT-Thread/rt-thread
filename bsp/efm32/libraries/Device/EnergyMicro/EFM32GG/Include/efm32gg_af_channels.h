/**************************************************************************//**
 * @file
 * @brief efm32gg_af_annels.h Register and Bit Field definitions
 * @author Energy Micro AS
 * @version 3.0.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
/**************************************************************************//**
 * @defgroup EFM32GG_AF_Channels
 * @{
 *****************************************************************************/

/** AF channels connect the different on-chip peripherals with the af-mux */
#define AFCHAN_MAX           163
#define AFCHANLOC_MAX        7
/** Analog AF channels */
#define AFACHAN_MAX          53

/** Peripheral Alternate Function (AF) channels */
#define AF_CMU_CLK0          0
#define AF_CMU_CLK1          1
#define AF_LESENSE_CH0       2
#define AF_LESENSE_CH1       3
#define AF_LESENSE_CH2       4
#define AF_LESENSE_CH3       5
#define AF_LESENSE_CH4       6
#define AF_LESENSE_CH5       7
#define AF_LESENSE_CH6       8
#define AF_LESENSE_CH7       9
#define AF_LESENSE_CH8       10
#define AF_LESENSE_CH9       11
#define AF_LESENSE_CH10      12
#define AF_LESENSE_CH11      13
#define AF_LESENSE_CH12      14
#define AF_LESENSE_CH13      15
#define AF_LESENSE_CH14      16
#define AF_LESENSE_CH15      17
#define AF_LESENSE_ALTEX0    18
#define AF_LESENSE_ALTEX1    19
#define AF_LESENSE_ALTEX2    20
#define AF_LESENSE_ALTEX3    21
#define AF_LESENSE_ALTEX4    22
#define AF_LESENSE_ALTEX5    23
#define AF_LESENSE_ALTEX6    24
#define AF_LESENSE_ALTEX7    25
#define AF_EBI_AD00          26
#define AF_EBI_AD01          27
#define AF_EBI_AD02          28
#define AF_EBI_AD03          29
#define AF_EBI_AD04          30
#define AF_EBI_AD05          31
#define AF_EBI_AD06          32
#define AF_EBI_AD07          33
#define AF_EBI_AD08          34
#define AF_EBI_AD09          35
#define AF_EBI_AD10          36
#define AF_EBI_AD11          37
#define AF_EBI_AD12          38
#define AF_EBI_AD13          39
#define AF_EBI_AD14          40
#define AF_EBI_AD15          41
#define AF_EBI_CS0           42
#define AF_EBI_CS1           43
#define AF_EBI_CS2           44
#define AF_EBI_CS3           45
#define AF_EBI_ARDY          46
#define AF_EBI_ALE           47
#define AF_EBI_WEn           48
#define AF_EBI_REn           49
#define AF_EBI_NANDWEn       50
#define AF_EBI_NANDREn       51
#define AF_EBI_BL0           52
#define AF_EBI_BL1           53
#define AF_EBI_A00           54
#define AF_EBI_A01           55
#define AF_EBI_A02           56
#define AF_EBI_A03           57
#define AF_EBI_A04           58
#define AF_EBI_A05           59
#define AF_EBI_A06           60
#define AF_EBI_A07           61
#define AF_EBI_A08           62
#define AF_EBI_A09           63
#define AF_EBI_A10           64
#define AF_EBI_A11           65
#define AF_EBI_A12           66
#define AF_EBI_A13           67
#define AF_EBI_A14           68
#define AF_EBI_A15           69
#define AF_EBI_A16           70
#define AF_EBI_A17           71
#define AF_EBI_A18           72
#define AF_EBI_A19           73
#define AF_EBI_A20           74
#define AF_EBI_A21           75
#define AF_EBI_A22           76
#define AF_EBI_A23           77
#define AF_EBI_A24           78
#define AF_EBI_A25           79
#define AF_EBI_A26           80
#define AF_EBI_A27           81
#define AF_EBI_CSTFT         82
#define AF_EBI_DCLK          83
#define AF_EBI_DTEN          84
#define AF_EBI_VSNC          85
#define AF_EBI_HSNC          86
#define AF_PRS_CH0           87
#define AF_PRS_CH1           88
#define AF_PRS_CH2           89
#define AF_PRS_CH3           90
#define AF_TIMER0_CC0        91
#define AF_TIMER0_CC1        92
#define AF_TIMER0_CC2        93
#define AF_TIMER0_CDTI0      94
#define AF_TIMER0_CDTI1      95
#define AF_TIMER0_CDTI2      96
#define AF_TIMER1_CC0        97
#define AF_TIMER1_CC1        98
#define AF_TIMER1_CC2        99
#define AF_TIMER1_CDTI0      100
#define AF_TIMER1_CDTI1      101
#define AF_TIMER1_CDTI2      102
#define AF_TIMER2_CC0        103
#define AF_TIMER2_CC1        104
#define AF_TIMER2_CC2        105
#define AF_TIMER2_CDTI0      106
#define AF_TIMER2_CDTI1      107
#define AF_TIMER2_CDTI2      108
#define AF_TIMER3_CC0        109
#define AF_TIMER3_CC1        110
#define AF_TIMER3_CC2        111
#define AF_TIMER3_CDTI0      112
#define AF_TIMER3_CDTI1      113
#define AF_TIMER3_CDTI2      114
#define AF_USART0_TX         115
#define AF_USART0_RX         116
#define AF_USART0_CLK        117
#define AF_USART0_CS         118
#define AF_USART1_TX         119
#define AF_USART1_RX         120
#define AF_USART1_CLK        121
#define AF_USART1_CS         122
#define AF_USART2_TX         123
#define AF_USART2_RX         124
#define AF_USART2_CLK        125
#define AF_USART2_CS         126
#define AF_UART0_TX          127
#define AF_UART0_RX          128
#define AF_UART0_CLK         129
#define AF_UART0_CS          130
#define AF_UART1_TX          131
#define AF_UART1_RX          132
#define AF_UART1_CLK         133
#define AF_UART1_CS          134
#define AF_LEUART0_TX        135
#define AF_LEUART0_RX        136
#define AF_LEUART1_TX        137
#define AF_LEUART1_RX        138
#define AF_LETIMER0_OUT0     139
#define AF_LETIMER0_OUT1     140
#define AF_PCNT0_S0IN        141
#define AF_PCNT0_S1IN        142
#define AF_PCNT1_S0IN        143
#define AF_PCNT1_S1IN        144
#define AF_PCNT2_S0IN        145
#define AF_PCNT2_S1IN        146
#define AF_I2C0_SDA          147
#define AF_I2C0_SCL          148
#define AF_I2C1_SDA          149
#define AF_I2C1_SCL          150
#define AF_ACMP0_OUT         151
#define AF_ACMP1_OUT         152
#define AF_USB_VBUSEN        153
#define AF_USB_DMPU          154
#define AF_DBG_SWO           155
#define AF_DBG_SWDIO         156
#define AF_DBG_SWCLK         157
#define AF_ETM_TCLK          158
#define AF_ETM_TD0           159
#define AF_ETM_TD1           160
#define AF_ETM_TD2           161
#define AF_ETM_TD3           162

/** Analog Alternate Function (AF) channels */
#define AFA_MSC_TM0          0
#define AFA_MSC_TM1          1
#define AFA_MSC_TM2          2
#define AFA_ADC0_CH0         3
#define AFA_ADC0_CH1         4
#define AFA_ADC0_CH2         5
#define AFA_ADC0_CH3         6
#define AFA_ADC0_CH4         7
#define AFA_ADC0_CH5         8
#define AFA_ADC0_CH6         9
#define AFA_ADC0_CH7         10
#define AFA_ADC0_VCM         11
#define AFA_DAC0_OUT0        12
#define AFA_DAC0_OUT1        13
#define AFA_DAC0_P0          14
#define AFA_DAC0_N0          15
#define AFA_DAC0_OUT0ALT     16
#define AFA_DAC0_P1          17
#define AFA_DAC0_N1          18
#define AFA_DAC0_OUT1ALT     19
#define AFA_DAC0_P2          20
#define AFA_DAC0_N2          21
#define AFA_DAC0_OUT2        22
#define AFA_DAC0_OUT2ALT     23
#define AFA_ACMP0_CH0        24
#define AFA_ACMP0_CH1        25
#define AFA_ACMP0_CH2        26
#define AFA_ACMP0_CH3        27
#define AFA_ACMP0_CH4        28
#define AFA_ACMP0_CH5        29
#define AFA_ACMP0_CH6        30
#define AFA_ACMP0_CH7        31
#define AFA_ACMP1_CH0        32
#define AFA_ACMP1_CH1        33
#define AFA_ACMP1_CH2        34
#define AFA_ACMP1_CH3        35
#define AFA_ACMP1_CH4        36
#define AFA_ACMP1_CH5        37
#define AFA_ACMP1_CH6        38
#define AFA_ACMP1_CH7        39
#define AFA_USB_DM           40
#define AFA_USB_DP           41
#define AFA_USB_ID           42
#define AFA_BU_VIN           43
#define AFA_BU_VOUT          44
#define AFA_BU_STAT          45
#define AFA_LCD_BCAP_P       46
#define AFA_LCD_BCAP_N       47
#define AFA_LCD_BEXT         48
#define AFA_HFXTAL_P         49
#define AFA_HFXTAL_N         50
#define AFA_LFXTAL_P         51
#define AFA_LFXTAL_N         52

/** Digital Alternate Function (AF) */
#define AF_TIMER_CC0(i)       ((i) == 0 ? AF_TIMER0_CC0 : (i) == 1 ? AF_TIMER1_CC0 : (i) == 2 ? AF_TIMER2_CC0 : (i) == 3 ? AF_TIMER3_CC0 :  -1)
#define AF_UART_CLK(i)        ((i) == 0 ? AF_UART0_CLK : (i) == 1 ? AF_UART1_CLK :  -1)
#define AF_I2C_SDA(i)         ((i) == 0 ? AF_I2C0_SDA : (i) == 1 ? AF_I2C1_SDA :  -1)
#define AF_TIMER_CC1(i)       ((i) == 0 ? AF_TIMER0_CC1 : (i) == 1 ? AF_TIMER1_CC1 : (i) == 2 ? AF_TIMER2_CC1 : (i) == 3 ? AF_TIMER3_CC1 :  -1)
#define AF_USART_CS(i)        ((i) == 0 ? AF_USART0_CS : (i) == 1 ? AF_USART1_CS : (i) == 2 ? AF_USART2_CS :  -1)
#define AF_I2C_SCL(i)         ((i) == 0 ? AF_I2C0_SCL : (i) == 1 ? AF_I2C1_SCL :  -1)
#define AF_TIMER_CC2(i)       ((i) == 0 ? AF_TIMER0_CC2 : (i) == 1 ? AF_TIMER1_CC2 : (i) == 2 ? AF_TIMER2_CC2 : (i) == 3 ? AF_TIMER3_CC2 :  -1)
#define AF_TIMER_CDTI1(i)     ((i) == 0 ? AF_TIMER0_CDTI1 : (i) == 1 ? AF_TIMER1_CDTI1 : (i) == 2 ? AF_TIMER2_CDTI1 : (i) == 3 ? AF_TIMER3_CDTI1 :  -1)
#define AF_TIMER_CDTI0(i)     ((i) == 0 ? AF_TIMER0_CDTI0 : (i) == 1 ? AF_TIMER1_CDTI0 : (i) == 2 ? AF_TIMER2_CDTI0 : (i) == 3 ? AF_TIMER3_CDTI0 :  -1)
#define AF_USART_CLK(i)       ((i) == 0 ? AF_USART0_CLK : (i) == 1 ? AF_USART1_CLK : (i) == 2 ? AF_USART2_CLK :  -1)
#define AF_UART_RX(i)         ((i) == 0 ? AF_UART0_RX : (i) == 1 ? AF_UART1_RX :  -1)
#define AF_UART_TX(i)         ((i) == 0 ? AF_UART0_TX : (i) == 1 ? AF_UART1_TX :  -1)
#define AF_LETIMER_OUT1(i)    ((i) == 0 ? AF_LETIMER0_OUT1 :  -1)
#define AF_LEUART_RX(i)       ((i) == 0 ? AF_LEUART0_RX : (i) == 1 ? AF_LEUART1_RX :  -1)
#define AF_PCNT_S1IN(i)       ((i) == 0 ? AF_PCNT0_S1IN : (i) == 1 ? AF_PCNT1_S1IN : (i) == 2 ? AF_PCNT2_S1IN :  -1)
#define AF_TIMER_CDTI2(i)     ((i) == 0 ? AF_TIMER0_CDTI2 : (i) == 1 ? AF_TIMER1_CDTI2 : (i) == 2 ? AF_TIMER2_CDTI2 : (i) == 3 ? AF_TIMER3_CDTI2 :  -1)
#define AF_LEUART_TX(i)       ((i) == 0 ? AF_LEUART0_TX : (i) == 1 ? AF_LEUART1_TX :  -1)
#define AF_USART_TX(i)        ((i) == 0 ? AF_USART0_TX : (i) == 1 ? AF_USART1_TX : (i) == 2 ? AF_USART2_TX :  -1)
#define AF_LETIMER_OUT0(i)    ((i) == 0 ? AF_LETIMER0_OUT0 :  -1)
#define AF_ACMP_OUT(i)        ((i) == 0 ? AF_ACMP0_OUT : (i) == 1 ? AF_ACMP1_OUT :  -1)
#define AF_USART_RX(i)        ((i) == 0 ? AF_USART0_RX : (i) == 1 ? AF_USART1_RX : (i) == 2 ? AF_USART2_RX :  -1)
#define AF_UART_CS(i)         ((i) == 0 ? AF_UART0_CS : (i) == 1 ? AF_UART1_CS :  -1)
#define AF_PCNT_S0IN(i)       ((i) == 0 ? AF_PCNT0_S0IN : (i) == 1 ? AF_PCNT1_S0IN : (i) == 2 ? AF_PCNT2_S0IN :  -1)
#define AFA_DAC_OUT1ALT(i)    ((i) == 0 ? AFA_DAC0_OUT1ALT :  -1)
#define AFA_ADC_CH7(i)        ((i) == 0 ? AFA_ADC0_CH7 :  -1)
#define AFA_DAC_N2(i)         ((i) == 0 ? AFA_DAC0_N2 :  -1)
#define AFA_DAC_N0(i)         ((i) == 0 ? AFA_DAC0_N0 :  -1)
#define AFA_ADC_VCM(i)        ((i) == 0 ? AFA_ADC0_VCM :  -1)
#define AFA_DAC_OUT2ALT(i)    ((i) == 0 ? AFA_DAC0_OUT2ALT :  -1)
#define AFA_DAC_N1(i)         ((i) == 0 ? AFA_DAC0_N1 :  -1)
#define AFA_ACMP_CH1(i)       ((i) == 0 ? AFA_ACMP0_CH1 : (i) == 1 ? AFA_ACMP1_CH1 :  -1)
#define AFA_ADC_CH0(i)        ((i) == 0 ? AFA_ADC0_CH0 :  -1)
#define AFA_ACMP_CH0(i)       ((i) == 0 ? AFA_ACMP0_CH0 : (i) == 1 ? AFA_ACMP1_CH0 :  -1)
#define AFA_ADC_CH1(i)        ((i) == 0 ? AFA_ADC0_CH1 :  -1)
#define AFA_ACMP_CH3(i)       ((i) == 0 ? AFA_ACMP0_CH3 : (i) == 1 ? AFA_ACMP1_CH3 :  -1)
#define AFA_ADC_CH2(i)        ((i) == 0 ? AFA_ADC0_CH2 :  -1)
#define AFA_ACMP_CH2(i)       ((i) == 0 ? AFA_ACMP0_CH2 : (i) == 1 ? AFA_ACMP1_CH2 :  -1)
#define AFA_ADC_CH3(i)        ((i) == 0 ? AFA_ADC0_CH3 :  -1)
#define AFA_ADC_CH4(i)        ((i) == 0 ? AFA_ADC0_CH4 :  -1)
#define AFA_ADC_CH5(i)        ((i) == 0 ? AFA_ADC0_CH5 :  -1)
#define AFA_DAC_OUT0ALT(i)    ((i) == 0 ? AFA_DAC0_OUT0ALT :  -1)
#define AFA_ADC_CH6(i)        ((i) == 0 ? AFA_ADC0_CH6 :  -1)
#define AFA_DAC_OUT2(i)       ((i) == 0 ? AFA_DAC0_OUT2 :  -1)
#define AFA_ACMP_CH5(i)       ((i) == 0 ? AFA_ACMP0_CH5 : (i) == 1 ? AFA_ACMP1_CH5 :  -1)
#define AFA_ACMP_CH4(i)       ((i) == 0 ? AFA_ACMP0_CH4 : (i) == 1 ? AFA_ACMP1_CH4 :  -1)
#define AFA_ACMP_CH7(i)       ((i) == 0 ? AFA_ACMP0_CH7 : (i) == 1 ? AFA_ACMP1_CH7 :  -1)
#define AFA_ACMP_CH6(i)       ((i) == 0 ? AFA_ACMP0_CH6 : (i) == 1 ? AFA_ACMP1_CH6 :  -1)
#define AFA_DAC_OUT1(i)       ((i) == 0 ? AFA_DAC0_OUT1 :  -1)
#define AFA_DAC_OUT0(i)       ((i) == 0 ? AFA_DAC0_OUT0 :  -1)
#define AFA_DAC_P1(i)         ((i) == 0 ? AFA_DAC0_P1 :  -1)
#define AFA_DAC_P0(i)         ((i) == 0 ? AFA_DAC0_P0 :  -1)
#define AFA_DAC_P2(i)         ((i) == 0 ? AFA_DAC0_P2 :  -1)

/** @} End of group EFM32GG_AF_Channels  */


