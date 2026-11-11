/*******************************************************************************
* Copyright (C) 2018, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \\file HC32L136.h
**
** Auto generate.
** Headerfile for HC32L136 series MCU
**
** History:
**
**   - 2018-09-14  0.1   Lux First version.
**
******************************************************************************/

#ifndef __HC32L136_H__
#define __HC32L136_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Configuration of the Cortex-M0P Processor and Core Peripherals
******************************************************************************/
#define __MPU_PRESENT           0 /* No MPU                                       */
#define __NVIC_PRIO_BITS        2 /* M0P uses 2 Bits for the Priority Levels      */
#define __Vendor_SysTickConfig  0 /* Set to 1 if different SysTick Config is used */

/******************************************************************************
* Interrupt Number Definition
******************************************************************************/
typedef enum IRQn
{
    NMI_IRQn            = -14, /*  2 Non Maskable                            */
    HardFault_IRQn      = -13, /*  3 Hard Fault                              */
    SVC_IRQn            = -5,  /* 11 SV Call                                 */
    PendSV_IRQn         = -2,  /* 14 Pend SV                                 */
    SysTick_IRQn        = -1,  /* 15 System Tick                             */
    
    PORTA_IRQn          = 0 ,
    PORTB_IRQn          = 1 ,
    PORTC_IRQn          = 2 ,
    PORTD_IRQn          = 3 ,
    DMAC_IRQn           = 4 ,
    TIM3_IRQn           = 5 ,
    UART0_IRQn          = 6 ,
    UART1_IRQn          = 7 ,
    LPUART0_IRQn        = 8 ,
    LPUART1_IRQn        = 9 ,
    SPI0_IRQn           = 10,
    SPI1_IRQn           = 11,
    I2C0_IRQn           = 12,
    I2C1_IRQn           = 13,
    TIM0_IRQn           = 14,
    TIM1_IRQn           = 15,
    TIM2_IRQn           = 16,
    LPTIM_IRQn          = 17,
    TIM4_IRQn           = 18,
    TIM5_IRQn           = 19,
    TIM6_IRQn           = 20,
    PCA_IRQn            = 21,
    WDT_IRQn            = 22,
    RTC_IRQn            = 23,
    ADC_IRQn            = 24,
    PCNT_IRQn           = 25,
    VC0_IRQn            = 26,
    VC1_IRQn            = 27,
    LVD_IRQn            = 28,
    LCD_IRQn            = 29,
    FLASH_RAM_IRQn      = 30,
    CLK_TRIM_IRQn       = 31,
    
    
} IRQn_Type;


#include <core_cm0plus.h>
#include <stdint.h>

#define SUCCESS         (0)
#define ERROR           (-1)

#ifndef NULL
#define NULL            (0)
#endif


/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

typedef struct
{
    __IO uint32_t EN                        : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CLKDIV                    : 2;
    __IO uint32_t SGLMUX                    : 5;
    __IO uint32_t REF                       : 2;
    __IO uint32_t BUF                       : 1;
    __IO uint32_t SAM                       : 2;
    __IO uint32_t INREFEN                   : 1;
    __IO uint32_t IE                        : 1;
} stc_adc_cr0_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 2;
    __IO uint32_t ALIGN                     : 1;
    __IO uint32_t THCH                      : 5;
    __IO uint32_t DMASQR                    : 1;
    __IO uint32_t DMAJQR                    : 1;
    __IO uint32_t MODE                      : 1;
    __IO uint32_t RACCEN                    : 1;
    __IO uint32_t LTCMP                     : 1;
    __IO uint32_t HTCMP                     : 1;
    __IO uint32_t REGCMP                    : 1;
    __IO uint32_t RACCCLR                   : 1;
} stc_adc_cr1_field_t;

typedef struct
{
    __IO uint32_t CH0MUX                    : 5;
    __IO uint32_t CH1MUX                    : 5;
    __IO uint32_t CH2MUX                    : 5;
    __IO uint32_t CH3MUX                    : 5;
    __IO uint32_t CH4MUX                    : 5;
    __IO uint32_t CH5MUX                    : 5;
} stc_adc_sqr0_field_t;

typedef struct
{
    __IO uint32_t CH6MUX                    : 5;
    __IO uint32_t CH7MUX                    : 5;
    __IO uint32_t CH8MUX                    : 5;
    __IO uint32_t CH9MUX                    : 5;
    __IO uint32_t CH10MUX                   : 5;
    __IO uint32_t CH11MUX                   : 5;
} stc_adc_sqr1_field_t;

typedef struct
{
    __IO uint32_t CH12MUX                   : 5;
    __IO uint32_t CH13MUX                   : 5;
    __IO uint32_t CH14MUX                   : 5;
    __IO uint32_t CH15MUX                   : 5;
    __IO uint32_t CNT                       : 4;
} stc_adc_sqr2_field_t;

typedef struct
{
    __IO uint32_t CH0MUX                    : 5;
    __IO uint32_t CH1MUX                    : 5;
    __IO uint32_t CH2MUX                    : 5;
    __IO uint32_t CH3MUX                    : 5;
    __IO uint32_t CNT                       : 2;
} stc_adc_jqr_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult0_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult1_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult2_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult3_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult4_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult5_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult6_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult7_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult8_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult9_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult10_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult11_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult12_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqr_result13_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult14_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_sqrresult15_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_jqrresult0_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_jqrresult1_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_jqrresult2_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_jqrresult3_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_result_field_t;

typedef struct
{
    __IO uint32_t RESULTACC                 :20;
} stc_adc_resultacc_field_t;

typedef struct
{
    __IO uint32_t HT                        :12;
} stc_adc_ht_field_t;

typedef struct
{
    __IO uint32_t LT                        :12;
} stc_adc_lt_field_t;

typedef struct
{
    __IO uint32_t SGLIF                     : 1;
    __IO uint32_t LTIF                      : 1;
    __IO uint32_t HTIF                      : 1;
    __IO uint32_t REGIF                     : 1;
    __IO uint32_t SQRIF                     : 1;
    __IO uint32_t JQRIF                     : 1;
} stc_adc_ifr_field_t;

typedef struct
{
    __IO uint32_t SGLIC                     : 1;
    __IO uint32_t LTIC                      : 1;
    __IO uint32_t HTIC                      : 1;
    __IO uint32_t REGIC                     : 1;
    __IO uint32_t SQRIC                     : 1;
    __IO uint32_t JQRIC                     : 1;
} stc_adc_icr_field_t;

typedef struct
{
    __IO uint32_t TIM0                      : 1;
    __IO uint32_t TIM1                      : 1;
    __IO uint32_t TIM2                      : 1;
    __IO uint32_t TIM3                      : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t UART0                     : 1;
    __IO uint32_t UART1                     : 1;
    __IO uint32_t LPUART0                   : 1;
    __IO uint32_t LPUART1                   : 1;
    __IO uint32_t VC0                       : 1;
    __IO uint32_t VC1                       : 1;
    __IO uint32_t RTC                       : 1;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t SPI0                      : 1;
    __IO uint32_t SPI1                      : 1;
    __IO uint32_t DMA                       : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PD07                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PA15                      : 1;
    __IO uint32_t PB15                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_adc_exttrigger0_field_t;

typedef struct
{
    __IO uint32_t TIM0                      : 1;
    __IO uint32_t TIM1                      : 1;
    __IO uint32_t TIM2                      : 1;
    __IO uint32_t TIM3                      : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t UART0                     : 1;
    __IO uint32_t UART1                     : 1;
    __IO uint32_t LPUART0                   : 1;
    __IO uint32_t LPUART1                   : 1;
    __IO uint32_t VC0                       : 1;
    __IO uint32_t VC1                       : 1;
    __IO uint32_t RTC                       : 1;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t SPI0                      : 1;
    __IO uint32_t SPI1                      : 1;
    __IO uint32_t DMA                       : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PD07                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PA15                      : 1;
    __IO uint32_t PB15                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_adc_exttrigger1_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
} stc_adc_sglstart_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
} stc_adc_sqrstart_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
} stc_adc_jqrstart_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    __IO uint32_t MODE                      : 1;
} stc_aes_cr_field_t;

typedef struct
{
    __IO uint32_t DATA0                     :32;
} stc_aes_data0_field_t;

typedef struct
{
    __IO uint32_t DATA0                     :32;
} stc_aes_data1_field_t;

typedef struct
{
    __IO uint32_t DATA0                     :32;
} stc_aes_data2_field_t;

typedef struct
{
    __IO uint32_t DATA0                     :32;
} stc_aes_data3_field_t;

typedef struct
{
    __IO uint32_t KEY0                      :32;
} stc_aes_key0_field_t;

typedef struct
{
    __IO uint32_t KEY0                      :32;
} stc_aes_key1_field_t;

typedef struct
{
    __IO uint32_t KEY0                      :32;
} stc_aes_key2_field_t;

typedef struct
{
    __IO uint32_t KEY0                      :32;
} stc_aes_key3_field_t;

typedef struct
{
    __IO uint32_t BGR_EN                    : 1;
    __IO uint32_t TS_EN                     : 1;
} stc_bgr_cr_field_t;

typedef struct
{
    __IO uint32_t TRIM_START                : 1;
    __IO uint32_t REFCLK_SEL                : 3;
    __IO uint32_t CALCLK_SEL                : 2;
    __IO uint32_t MON_EN                    : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t CALCLK_SEL2               : 1;
} stc_clk_trim_cr_field_t;

typedef struct
{
    __IO uint32_t RCNTVAL                   :32;
} stc_clk_trim_refcon_field_t;

typedef struct
{
    __IO uint32_t REFCNT                    :32;
} stc_clk_trim_refcnt_field_t;

typedef struct
{
    __IO uint32_t CALCNT                    :32;
} stc_clk_trim_calcnt_field_t;

typedef struct
{
    __IO uint32_t STOP                      : 1;
    __IO uint32_t CALCNT_OF                 : 1;
    __IO uint32_t XTL_FAULT                 : 1;
    __IO uint32_t XTH_FAULT                 : 1;
    __IO uint32_t PLL_FAULT                 : 1;
} stc_clk_trim_ifr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 2;
    __IO uint32_t XTL_FAULT_CLR             : 1;
    __IO uint32_t XTH_FAULT_CLR             : 1;
    __IO uint32_t PLL_FAULT_CLR             : 1;
} stc_clk_trim_iclr_field_t;

typedef struct
{
    __IO uint32_t CCNTVAL                   :32;
} stc_clk_trim_calcon_field_t;

typedef struct
{
    __IO uint32_t CR                        : 1;
    __IO uint32_t FLAG                      : 1;
} stc_crc_cr_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :32;
} stc_crc_result_field_t;

typedef struct
{
    __IO uint32_t DATA                      :32;
} stc_crc_data_field_t;

typedef struct
{
    __IO uint32_t TIM0                      : 1;
    __IO uint32_t TIM1                      : 1;
    __IO uint32_t TIM2                      : 1;
    __IO uint32_t LPTIM                     : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t WDT                       : 1;
    __IO uint32_t RTC                       : 1;
    uint32_t RESERVED10                     : 1;
    __IO uint32_t TIM3                      : 1;
} stc_debug_active_field_t;

typedef struct
{
    uint32_t RESERVED0                      :24;
    __IO uint32_t HALT                      : 4;
    __IO uint32_t PRIO                      : 1;
    uint32_t RESERVED29                     : 1;
    __IO uint32_t ST                        : 1;
    __IO uint32_t EN                        : 1;
} stc_dmac_conf_field_t;

typedef struct
{
    __IO uint32_t TC                        :16;
    __IO uint32_t BC                        : 4;
    uint32_t RESERVED20                     : 3;
    __IO uint32_t TRI_SEL                   : 6;
    __IO uint32_t ST                        : 1;
    __IO uint32_t PAS                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_dmac_confa0_field_t;

typedef struct
{
    __IO uint32_t MSK                       : 1;
    uint32_t RESERVED1                      :15;
    __IO uint32_t STAT                      : 3;
    __IO uint32_t FIS_IE                    : 1;
    __IO uint32_t ERR_IE                    : 1;
    __IO uint32_t RD                        : 1;
    __IO uint32_t RS                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t FD                        : 1;
    __IO uint32_t FS                        : 1;
    __IO uint32_t WIDTH                     : 2;
    __IO uint32_t MODE                      : 2;
} stc_dmac_confb0_field_t;

typedef struct
{
    __IO uint32_t SRCADR                    :32;
} stc_dmac_srcadr0_field_t;

typedef struct
{
    __IO uint32_t DSTADR                    :32;
} stc_dmac_dstadr0_field_t;

typedef struct
{
    __IO uint32_t TC                        :16;
    __IO uint32_t BC                        : 4;
    uint32_t RESERVED20                     : 3;
    __IO uint32_t TRI_SEL                   : 6;
    __IO uint32_t ST                        : 1;
    __IO uint32_t PAS                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_dmac_confa1_field_t;

typedef struct
{
    __IO uint32_t MSK                       : 1;
    uint32_t RESERVED1                      :15;
    __IO uint32_t STAT                      : 3;
    __IO uint32_t FIS_IE                    : 1;
    __IO uint32_t ERR_IE                    : 1;
    __IO uint32_t RD                        : 1;
    __IO uint32_t RS                        : 1;
    __IO uint32_t RC                        : 1;
    __IO uint32_t FD                        : 1;
    __IO uint32_t FS                        : 1;
    __IO uint32_t WIDTH                     : 2;
    __IO uint32_t MODE                      : 2;
} stc_dmac_confb1_field_t;

typedef struct
{
    __IO uint32_t SRCADR                    :32;
} stc_dmac_srcadr1_field_t;

typedef struct
{
    __IO uint32_t DSTADR                    :32;
} stc_dmac_dstadr1_field_t;

typedef struct
{
    __IO uint32_t TNVS                      : 9;
} stc_flash_tnvs_field_t;

typedef struct
{
    __IO uint32_t TPGS                      : 8;
} stc_flash_tpgs_field_t;

typedef struct
{
    __IO uint32_t TPROG                     : 9;
} stc_flash_tprog_field_t;

typedef struct
{
    __IO uint32_t TSERASE                   :18;
} stc_flash_tserase_field_t;

typedef struct
{
    __IO uint32_t TMERASE                   :21;
} stc_flash_tmerase_field_t;

typedef struct
{
    __IO uint32_t TPRCV                     :12;
} stc_flash_tprcv_field_t;

typedef struct
{
    __IO uint32_t TSRCV                     :12;
} stc_flash_tsrcv_field_t;

typedef struct
{
    __IO uint32_t TMRCV                     :13;
} stc_flash_tmrcv_field_t;

typedef struct
{
    __IO uint32_t OP                        : 2;
    __IO uint32_t WAIT                      : 2;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t IE                        : 2;
    uint32_t RESERVED7                      : 2;
    __IO uint32_t DPSTB_EN                  : 1;
} stc_flash_cr_field_t;

typedef struct
{
    __IO uint32_t IF0                       : 1;
    __IO uint32_t IF1                       : 1;
} stc_flash_ifr_field_t;

typedef struct
{
    __IO uint32_t ICLR0                     : 1;
    __IO uint32_t ICLR1                     : 1;
} stc_flash_iclr_field_t;

typedef struct
{
    __IO uint32_t BYSEQ                     :16;
} stc_flash_bypass_field_t;

typedef struct
{
    __IO uint32_t SLOCK                     :32;
} stc_flash_slock_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa00_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa04_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa05_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa06_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa07_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa08_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa09_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa10_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa11_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa12_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa13_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa14_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pa15_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb00_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb04_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb05_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb06_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb07_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb08_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb09_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb10_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb11_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb12_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb13_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb14_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pb15_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc00_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc04_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc05_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc06_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc07_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc08_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc09_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc10_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc11_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc12_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc13_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc14_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pc15_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pd00_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pd01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pd02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pd03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pd04_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pd05_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pd06_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_pd07_sel_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_padir_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_pain_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_paout_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_paads_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_pabset_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_pabclr_field_t;

typedef struct
{
    __IO uint32_t PABCLR                    :16;
    __IO uint32_t PABSET                    :16;
} stc_gpio_pabsetclr_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_padr_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_papu_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_papd_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_paod_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_pahie_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_palie_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_parie_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_pafie_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbdir_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbin_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbout_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbads_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbbset_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbbclr_field_t;

typedef struct
{
    __IO uint32_t PBBCLR                    :16;
    __IO uint32_t PBBSET                    :16;
} stc_gpio_pbbsetclr_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbdr_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbpu_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbpd_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbod_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbhie_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pblie_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbrie_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pbfie_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcdir_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcin_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcout_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcads_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcbset_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcbclr_field_t;

typedef struct
{
    __IO uint32_t PCBCLR                    :16;
    __IO uint32_t PCBSET                    :16;
} stc_gpio_pcbsetclr_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcdr_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcpu_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcpd_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcod_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pchie_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pclie_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcrie_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pcfie_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pddir_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdin_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdout_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdads_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdbset_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdbclr_field_t;

typedef struct
{
    __IO uint32_t PDBCLR                    : 8;
    uint32_t RESERVED8                      : 8;
    __IO uint32_t PDBSET                    : 8;
} stc_gpio_pdbsetclr_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pddr_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdpu_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdpd_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdod_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdhie_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdlie_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdrie_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pdfie_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_pa_stat_field_t;

typedef struct
{
    __IO uint32_t PA00                      : 1;
    __IO uint32_t PA01                      : 1;
    __IO uint32_t PA02                      : 1;
    __IO uint32_t PA03                      : 1;
    __IO uint32_t PA04                      : 1;
    __IO uint32_t PA05                      : 1;
    __IO uint32_t PA06                      : 1;
    __IO uint32_t PA07                      : 1;
    __IO uint32_t PA08                      : 1;
    __IO uint32_t PA09                      : 1;
    __IO uint32_t PA10                      : 1;
    __IO uint32_t PA11                      : 1;
    __IO uint32_t PA12                      : 1;
    __IO uint32_t PA13                      : 1;
    __IO uint32_t PA14                      : 1;
    __IO uint32_t PA15                      : 1;
} stc_gpio_pa_iclr_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pb_stat_field_t;

typedef struct
{
    __IO uint32_t PB00                      : 1;
    __IO uint32_t PB01                      : 1;
    __IO uint32_t PB02                      : 1;
    __IO uint32_t PB03                      : 1;
    __IO uint32_t PB04                      : 1;
    __IO uint32_t PB05                      : 1;
    __IO uint32_t PB06                      : 1;
    __IO uint32_t PB07                      : 1;
    __IO uint32_t PB08                      : 1;
    __IO uint32_t PB09                      : 1;
    __IO uint32_t PB10                      : 1;
    __IO uint32_t PB11                      : 1;
    __IO uint32_t PB12                      : 1;
    __IO uint32_t PB13                      : 1;
    __IO uint32_t PB14                      : 1;
    __IO uint32_t PB15                      : 1;
} stc_gpio_pb_iclr_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pc_stat_field_t;

typedef struct
{
    __IO uint32_t PC00                      : 1;
    __IO uint32_t PC01                      : 1;
    __IO uint32_t PC02                      : 1;
    __IO uint32_t PC03                      : 1;
    __IO uint32_t PC04                      : 1;
    __IO uint32_t PC05                      : 1;
    __IO uint32_t PC06                      : 1;
    __IO uint32_t PC07                      : 1;
    __IO uint32_t PC08                      : 1;
    __IO uint32_t PC09                      : 1;
    __IO uint32_t PC10                      : 1;
    __IO uint32_t PC11                      : 1;
    __IO uint32_t PC12                      : 1;
    __IO uint32_t PC13                      : 1;
    __IO uint32_t PC14                      : 1;
    __IO uint32_t PC15                      : 1;
} stc_gpio_pc_iclr_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pd_stat_field_t;

typedef struct
{
    __IO uint32_t PD00                      : 1;
    __IO uint32_t PD01                      : 1;
    __IO uint32_t PD02                      : 1;
    __IO uint32_t PD03                      : 1;
    __IO uint32_t PD04                      : 1;
    __IO uint32_t PD05                      : 1;
    __IO uint32_t PD06                      : 1;
    __IO uint32_t PD07                      : 1;
} stc_gpio_pd_iclr_field_t;

typedef struct
{
    __IO uint32_t IESEL                     : 1;
} stc_gpio_ctrl0_field_t;

typedef struct
{
    __IO uint32_t EXT_CLK_SEL               : 4;
    __IO uint32_t SSN0_SEL                  : 4;
    __IO uint32_t PCLK_SEL                  : 2;
    __IO uint32_t HCLK_SEL                  : 2;
    __IO uint32_t PCLK_EN                   : 1;
    __IO uint32_t HCLK_EN                   : 1;
    __IO uint32_t IR_POL                    : 1;
} stc_gpio_ctrl1_field_t;

typedef struct
{
    __IO uint32_t SSN1_SEL                  : 4;
    uint32_t RESERVED4                      :11;
    __IO uint32_t AHB_SEL                   : 1;
} stc_gpio_ctrl2_field_t;

typedef struct
{
    __IO uint32_t TIM0_G                    : 3;
    __IO uint32_t TIM1_G                    : 3;
    __IO uint32_t TIM2_G                    : 3;
    __IO uint32_t TIM3_G                    : 3;
    __IO uint32_t LPTIM_G                   : 3;
} stc_gpio_timgs_field_t;

typedef struct
{
    __IO uint32_t TIM0_E                    : 3;
    __IO uint32_t TIM1_E                    : 3;
    __IO uint32_t TIM2_E                    : 3;
    __IO uint32_t TIM3_E                    : 3;
    __IO uint32_t LPTIM_E                   : 3;
} stc_gpio_times_field_t;

typedef struct
{
    __IO uint32_t TIM0_CA                   : 3;
    __IO uint32_t TIM1_CA                   : 3;
    __IO uint32_t TIM2_CA                   : 3;
    __IO uint32_t TIM3_CA                   : 3;
    __IO uint32_t TIM3_CB                   : 3;
} stc_gpio_timcps_field_t;

typedef struct
{
    __IO uint32_t PCA_CH0                   : 3;
    __IO uint32_t PCA_ECI                   : 3;
} stc_gpio_pcas_field_t;

typedef struct
{
    __IO uint32_t DIVIDEND                  :32;
} stc_hdiv_dividend_field_t;

typedef struct
{
    __IO uint32_t DIVISOR                   :16;
} stc_hdiv_divisor_field_t;

typedef struct
{
    __IO uint32_t QUOTIENT                  :32;
} stc_hdiv_quotient_field_t;

typedef struct
{
    __IO uint32_t REMAINDER                 :32;
} stc_hdiv_remainder_field_t;

typedef struct
{
    __IO uint32_t SIGN                      : 1;
} stc_hdiv_sign_field_t;

typedef struct
{
    __IO uint32_t END                       : 1;
    __IO uint32_t ZERO                      : 1;
} stc_hdiv_stat_field_t;

typedef struct
{
    __IO uint32_t TME                       : 1;
} stc_i2c_tmrun_field_t;

typedef struct
{
    __IO uint32_t TM                        : 8;
} stc_i2c_tm_field_t;

typedef struct
{
    __IO uint32_t H1M                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t AA                        : 1;
    __IO uint32_t SI                        : 1;
    __IO uint32_t STO                       : 1;
    __IO uint32_t STA                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_i2c_cr_field_t;

typedef struct
{
    __IO uint32_t DAT                       : 8;
} stc_i2c_data_field_t;

typedef struct
{
    __IO uint32_t GC                        : 1;
    __IO uint32_t ADR                       : 7;
} stc_i2c_addr_field_t;

typedef struct
{
    __IO uint32_t STA                       : 8;
} stc_i2c_stat_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t LCDCLK                    : 2;
    __IO uint32_t CPCLK                     : 2;
    __IO uint32_t BIAS                      : 1;
    __IO uint32_t DUTY                      : 3;
    __IO uint32_t BSEL                      : 3;
    __IO uint32_t CONTRAST                  : 4;
} stc_lcd_cr0_field_t;

typedef struct
{
    __IO uint32_t BLINKCNT                  : 6;
    __IO uint32_t BLINKEN                   : 1;
    __IO uint32_t CLKSRC                    : 1;
    __IO uint32_t MODE                      : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t DMAEN                     : 1;
    __IO uint32_t INTF                      : 1;
} stc_lcd_cr1_field_t;

typedef struct
{
    uint32_t RESERVED0                      :10;
    __IO uint32_t INTF                      : 1;
} stc_lcd_intclr_field_t;

typedef struct
{
    __IO uint32_t S0                        : 1;
    __IO uint32_t S1                        : 1;
    __IO uint32_t S2                        : 1;
    __IO uint32_t S3                        : 1;
    __IO uint32_t S4                        : 1;
    __IO uint32_t S5                        : 1;
    __IO uint32_t S6                        : 1;
    __IO uint32_t S7                        : 1;
    __IO uint32_t S8                        : 1;
    __IO uint32_t S9                        : 1;
    __IO uint32_t S10                       : 1;
    __IO uint32_t S11                       : 1;
    __IO uint32_t S12                       : 1;
    __IO uint32_t S13                       : 1;
    __IO uint32_t S14                       : 1;
    __IO uint32_t S15                       : 1;
    __IO uint32_t S16                       : 1;
    __IO uint32_t S17                       : 1;
    __IO uint32_t S18                       : 1;
    __IO uint32_t S19                       : 1;
    __IO uint32_t S20                       : 1;
    __IO uint32_t S21                       : 1;
    __IO uint32_t S22                       : 1;
    __IO uint32_t S23                       : 1;
    __IO uint32_t S24                       : 1;
    __IO uint32_t S25                       : 1;
    __IO uint32_t S26                       : 1;
    __IO uint32_t S27                       : 1;
    __IO uint32_t S28                       : 1;
    __IO uint32_t S29                       : 1;
    __IO uint32_t S30                       : 1;
    __IO uint32_t S31                       : 1;
} stc_lcd_poen0_field_t;

typedef struct
{
    __IO uint32_t S32                       : 1;
    __IO uint32_t S33                       : 1;
    __IO uint32_t S34                       : 1;
    __IO uint32_t S35                       : 1;
    __IO uint32_t S36C7                     : 1;
    __IO uint32_t S37C6                     : 1;
    __IO uint32_t S38C5                     : 1;
    __IO uint32_t S39C4                     : 1;
    __IO uint32_t C0                        : 1;
    __IO uint32_t C1                        : 1;
    __IO uint32_t C2                        : 1;
    __IO uint32_t C3                        : 1;
    __IO uint32_t MUX                       : 1;
} stc_lcd_poen1_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram0_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram1_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram2_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram3_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram4_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram5_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram6_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
    __IO uint32_t D8                        : 1;
    __IO uint32_t D9                        : 1;
    __IO uint32_t D10                       : 1;
    __IO uint32_t D11                       : 1;
    __IO uint32_t D12                       : 1;
    __IO uint32_t D13                       : 1;
    __IO uint32_t D14                       : 1;
    __IO uint32_t D15                       : 1;
    __IO uint32_t D16                       : 1;
    __IO uint32_t D17                       : 1;
    __IO uint32_t D18                       : 1;
    __IO uint32_t D19                       : 1;
    __IO uint32_t D20                       : 1;
    __IO uint32_t D21                       : 1;
    __IO uint32_t D22                       : 1;
    __IO uint32_t D23                       : 1;
    __IO uint32_t D24                       : 1;
    __IO uint32_t D25                       : 1;
    __IO uint32_t D26                       : 1;
    __IO uint32_t D27                       : 1;
    __IO uint32_t D28                       : 1;
    __IO uint32_t D29                       : 1;
    __IO uint32_t D30                       : 1;
    __IO uint32_t D31                       : 1;
} stc_lcd_ram7_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
} stc_lcd_ram8_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
} stc_lcd_ram9_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
} stc_lcd_rama_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
} stc_lcd_ramb_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
} stc_lcd_ramc_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
} stc_lcd_ramd_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
} stc_lcd_rame_field_t;

typedef struct
{
    __IO uint32_t D0                        : 1;
    __IO uint32_t D1                        : 1;
    __IO uint32_t D2                        : 1;
    __IO uint32_t D3                        : 1;
    __IO uint32_t D4                        : 1;
    __IO uint32_t D5                        : 1;
    __IO uint32_t D6                        : 1;
    __IO uint32_t D7                        : 1;
} stc_lcd_ramf_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_lptimer_cnt_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_lptimer_arr_field_t;

typedef struct
{
    __IO uint32_t TR                        : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOG_EN                    : 1;
    __IO uint32_t TCK_SEL                   : 2;
    uint32_t RESERVED6                      : 1;
    __IO uint32_t WT_FLAG                   : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATE_P                    : 1;
    __IO uint32_t IE                        : 1;
} stc_lptimer_cr_field_t;

typedef struct
{
    __IO uint32_t TF                        : 1;
} stc_lptimer_ifr_field_t;

typedef struct
{
    __IO uint32_t TFC                       : 1;
} stc_lptimer_iclr_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    __IO uint32_t DATA8                     : 1;
} stc_lpuart_sbuf_field_t;

typedef struct
{
    __IO uint32_t RCIE                      : 1;
    __IO uint32_t TCIE                      : 1;
    __IO uint32_t B8CONT                    : 2;
    __IO uint32_t REN                       : 1;
    __IO uint32_t ADRDET                    : 1;
    __IO uint32_t SM                        : 2;
    __IO uint32_t TXEIE                     : 1;
    __IO uint32_t OVER                      : 2;
    __IO uint32_t SCLKSEL                   : 2;
    __IO uint32_t PEIE                      : 1;
    __IO uint32_t STOPBIT                   : 2;
    __IO uint32_t DMARXEN                   : 1;
    __IO uint32_t DMATXEN                   : 1;
    __IO uint32_t RTSEN                     : 1;
    __IO uint32_t CTSEN                     : 1;
    __IO uint32_t CTSIE                     : 1;
    __IO uint32_t FEIE                      : 1;
} stc_lpuart_scon_field_t;

typedef struct
{
    __IO uint32_t SADDR                     : 8;
} stc_lpuart_saddr_field_t;

typedef struct
{
    __IO uint32_t SADEN                     : 8;
} stc_lpuart_saden_field_t;

typedef struct
{
    __IO uint32_t RC                        : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t TXE                       : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t CTSIF                     : 1;
    __IO uint32_t CTS                       : 1;
} stc_lpuart_isr_field_t;

typedef struct
{
    __IO uint32_t RCCF                      : 1;
    __IO uint32_t TCCF                      : 1;
    __IO uint32_t FECF                      : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PECF                      : 1;
    __IO uint32_t CTSIFCF                   : 1;
} stc_lpuart_icr_field_t;

typedef struct
{
    __IO uint32_t SCNT                      :16;
} stc_lpuart_scnt_field_t;

typedef struct
{
    __IO uint32_t LVDEN                     : 1;
    __IO uint32_t ACT                       : 1;
    __IO uint32_t SOURCE_SEL                : 2;
    __IO uint32_t VTDS                      : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t DEBOUNCE_TIME             : 3;
    __IO uint32_t FTEN                      : 1;
    __IO uint32_t RTEN                      : 1;
    __IO uint32_t HTEN                      : 1;
    __IO uint32_t IE                        : 1;
} stc_lvd_cr_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
    __IO uint32_t FILTER                    : 1;
} stc_lvd_ifr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t AZEN                      : 1;
    __IO uint32_t MODE                      : 1;
    __IO uint32_t UBUFSEL                   : 1;
    __IO uint32_t RESSEL                    : 1;
    __IO uint32_t BIASSEL                   : 3;
    __IO uint32_t NEGSEL                    : 2;
    __IO uint32_t POSSEL                    : 2;
    __IO uint32_t PGAGAIN                   : 3;
    __IO uint32_t POEN                      : 1;
    __IO uint32_t RESINMUX                  : 2;
} stc_opa_cr0_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t AZEN                      : 1;
    __IO uint32_t MODE                      : 1;
    __IO uint32_t UBUFSEL                   : 1;
    __IO uint32_t RESSEL                    : 1;
    __IO uint32_t BIASSEL                   : 3;
    __IO uint32_t NEGSEL                    : 2;
    __IO uint32_t POSSEL                    : 2;
    __IO uint32_t PGAGAIN                   : 3;
    __IO uint32_t POEN                      : 1;
    __IO uint32_t RESINMUX                  : 2;
} stc_opa_cr1_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t AZEN                      : 1;
    __IO uint32_t MODE                      : 1;
    __IO uint32_t UBUFSEL                   : 1;
    __IO uint32_t RESSEL                    : 1;
    __IO uint32_t BIASSEL                   : 3;
    __IO uint32_t NEGSEL                    : 2;
    __IO uint32_t POSSEL                    : 2;
    __IO uint32_t PGAGAIN                   : 3;
    __IO uint32_t POEN                      : 1;
    __IO uint32_t RESINMUX                  : 2;
} stc_opa_cr2_field_t;

typedef struct
{
    __IO uint8_t ADCTR_EN                   : 1;
    __IO uint8_t TRIGGER                    : 1;
    __IO uint8_t AZ_PULSE                   : 1;
    __IO uint8_t CLK_SW_SET                 : 1;
    __IO uint8_t CLK_SEL                    : 4;
} stc_opa_cr_field_t;

typedef struct
{
    __IO uint32_t CCF0                      : 1;
    __IO uint32_t CCF1                      : 1;
    __IO uint32_t CCF2                      : 1;
    __IO uint32_t CCF3                      : 1;
    __IO uint32_t CCF4                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t CR                        : 1;
    __IO uint32_t CF                        : 1;
} stc_pca_ccon_field_t;

typedef struct
{
    __IO uint32_t CFIE                      : 1;
    __IO uint32_t CPS                       : 3;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t WDTE                      : 1;
    __IO uint32_t CIDL                      : 1;
} stc_pca_cmod_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_pca_cnt_field_t;

typedef struct
{
    __IO uint32_t CCF0                      : 1;
    __IO uint32_t CCF1                      : 1;
    __IO uint32_t CCF2                      : 1;
    __IO uint32_t CCF3                      : 1;
    __IO uint32_t CCF4                      : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t CF                        : 1;
} stc_pca_iclr_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
} stc_pca_ccapm0_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
} stc_pca_ccapm1_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
} stc_pca_ccapm2_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
} stc_pca_ccapm3_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
} stc_pca_ccapm4_field_t;

typedef struct
{
    __IO uint32_t CCAP0                     : 8;
} stc_pca_ccap0h_field_t;

typedef struct
{
    __IO uint32_t CCAP0                     : 8;
} stc_pca_ccap0l_field_t;

typedef struct
{
    __IO uint32_t CCAP1                     : 8;
} stc_pca_ccap1h_field_t;

typedef struct
{
    __IO uint32_t CCAP1                     : 8;
} stc_pca_ccap1l_field_t;

typedef struct
{
    __IO uint32_t CCAP2                     : 8;
} stc_pca_ccap2h_field_t;

typedef struct
{
    __IO uint32_t CCAP2                     : 8;
} stc_pca_ccap2l_field_t;

typedef struct
{
    __IO uint32_t CCAP3                     : 8;
} stc_pca_ccap3h_field_t;

typedef struct
{
    __IO uint32_t CCAP3                     : 8;
} stc_pca_ccap3l_field_t;

typedef struct
{
    __IO uint32_t CCAP4                     : 8;
} stc_pca_ccap4h_field_t;

typedef struct
{
    __IO uint32_t CCAP4                     : 8;
} stc_pca_ccap4l_field_t;

typedef struct
{
    __IO uint32_t CCAPO0                    : 1;
    __IO uint32_t CCAPO1                    : 1;
    __IO uint32_t CCAPO2                    : 1;
    __IO uint32_t CCAPO3                    : 1;
    __IO uint32_t CCAPO4                    : 1;
} stc_pca_ccapo_field_t;

typedef struct
{
    __IO uint32_t CCAP0                     :16;
} stc_pca_ccap0_field_t;

typedef struct
{
    __IO uint32_t CCAP1                     :16;
} stc_pca_ccap1_field_t;

typedef struct
{
    __IO uint32_t CCAP2                     :16;
} stc_pca_ccap2_field_t;

typedef struct
{
    __IO uint32_t CCAP3                     :16;
} stc_pca_ccap3_field_t;

typedef struct
{
    __IO uint32_t CCAP4                     :16;
} stc_pca_ccap4_field_t;

typedef struct
{
    __IO uint32_t CARR                      :16;
} stc_pca_carr_field_t;

typedef struct
{
    __IO uint32_t EPWM                      : 1;
} stc_pca_epwm_field_t;

typedef struct
{
    __IO uint8_t RUN                        : 1;
} stc_pcnt_run_field_t;

typedef struct
{
    __IO uint8_t MODE                       : 2;
    __IO uint8_t CLKSEL                     : 2;
    __IO uint8_t DIR                        : 1;
    __IO uint8_t S0P                        : 1;
    __IO uint8_t S1P                        : 1;
} stc_pcnt_cr_field_t;

typedef struct
{
    __IO uint32_t CLKDIV                    :13;
    __IO uint32_t DEBTOP                    : 3;
    __IO uint32_t EN                        : 1;
} stc_pcnt_flt_field_t;

typedef struct
{
    __IO uint32_t TH                        :12;
    uint32_t RESERVED12                     : 4;
    __IO uint32_t EN                        : 1;
} stc_pcnt_tocr_field_t;

typedef struct
{
    __IO uint8_t T2C                        : 1;
    __IO uint8_t B2T                        : 1;
    __IO uint8_t B2C                        : 1;
} stc_pcnt_cmd_field_t;

typedef struct
{
    __IO uint8_t DIR                        : 1;
} stc_pcnt_sr1_field_t;

typedef struct
{
    __IO uint16_t CNT                       :16;
} stc_pcnt_cnt_field_t;

typedef struct
{
    __IO uint16_t TOP                       :16;
} stc_pcnt_top_field_t;

typedef struct
{
    __IO uint16_t BUF                       :16;
} stc_pcnt_buf_field_t;

typedef struct
{
    __IO uint8_t UF                         : 1;
    __IO uint8_t OV                         : 1;
    __IO uint8_t TO                         : 1;
    __IO uint8_t DIR                        : 1;
    __IO uint8_t FE                         : 1;
    __IO uint8_t BB                         : 1;
    __IO uint8_t S0E                        : 1;
    __IO uint8_t S1E                        : 1;
} stc_pcnt_ifr_field_t;

typedef struct
{
    __IO uint8_t UF                         : 1;
    __IO uint8_t OV                         : 1;
    __IO uint8_t TO                         : 1;
    __IO uint8_t DIR                        : 1;
    __IO uint8_t FE                         : 1;
    __IO uint8_t BB                         : 1;
    __IO uint8_t S0E                        : 1;
    __IO uint8_t S1E                        : 1;
} stc_pcnt_icr_field_t;

typedef struct
{
    __IO uint8_t UF                         : 1;
    __IO uint8_t OV                         : 1;
    __IO uint8_t TO                         : 1;
    __IO uint8_t DIR                        : 1;
    __IO uint8_t FE                         : 1;
    __IO uint8_t BB                         : 1;
    __IO uint8_t S0E                        : 1;
    __IO uint8_t S1E                        : 1;
} stc_pcnt_ien_field_t;

typedef struct
{
    __IO uint8_t T2C                        : 1;
    __IO uint8_t B2T                        : 1;
    __IO uint8_t B2C                        : 1;
} stc_pcnt_sr2_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t IE                        : 1;
} stc_ram_cr_field_t;

typedef struct
{
    __IO uint32_t ERRADDR                   :13;
} stc_ram_erraddr_field_t;

typedef struct
{
    __IO uint32_t ERR                       : 1;
} stc_ram_ifr_field_t;

typedef struct
{
    __IO uint32_t ERRCLR                    : 1;
} stc_ram_iclr_field_t;

typedef struct
{
    __IO uint32_t POR5V                     : 1;
    __IO uint32_t POR15V                    : 1;
    __IO uint32_t LVD                       : 1;
    __IO uint32_t WDT                       : 1;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t LOCKUP                    : 1;
    __IO uint32_t SYSREQ                    : 1;
    __IO uint32_t RSTB                      : 1;
} stc_reset_flag_field_t;

typedef struct
{
    __IO uint32_t UART0                     : 1;
    __IO uint32_t UART1                     : 1;
    __IO uint32_t LPUART0                   : 1;
    __IO uint32_t LPUART1                   : 1;
    __IO uint32_t I2C0                      : 1;
    __IO uint32_t I2C1                      : 1;
    __IO uint32_t SPI0                      : 1;
    __IO uint32_t SPI1                      : 1;
    __IO uint32_t BASETIM                   : 1;
    __IO uint32_t LPTIM                     : 1;
    __IO uint32_t ADVTIM                    : 1;
    __IO uint32_t TIM3                      : 1;
    uint32_t RESERVED12                     : 1;
    __IO uint32_t OPA                       : 1;
    __IO uint32_t PCA                       : 1;
    uint32_t RESERVED15                     : 1;
    __IO uint32_t ADC                       : 1;
    __IO uint32_t VC                        : 1;
    __IO uint32_t RNG                       : 1;
    __IO uint32_t PCNT                      : 1;
    __IO uint32_t RTC                       : 1;
    __IO uint32_t TRIM                      : 1;
    __IO uint32_t LCD                       : 1;
    uint32_t RESERVED23                     : 1;
    __IO uint32_t TICK                      : 1;
    __IO uint32_t SWD                       : 1;
    __IO uint32_t CRC                       : 1;
    __IO uint32_t AES                       : 1;
    __IO uint32_t GPIO                      : 1;
    __IO uint32_t DMA                       : 1;
    __IO uint32_t DIV                       : 1;
} stc_reset_prei_field_t;

typedef struct
{
    __IO uint32_t RNGCIR_EN                 : 1;
    __IO uint32_t RNG_RUN                   : 1;
} stc_rng_cr_field_t;

typedef struct
{
    __IO uint32_t LOAD                      : 1;
    __IO uint32_t FDBK                      : 1;
    __IO uint32_t CNT                       : 3;
} stc_rng_mode_field_t;

typedef struct
{
    __IO uint32_t DATA0                     :32;
} stc_rng_data0_field_t;

typedef struct
{
    __IO uint32_t DATA1                     :32;
} stc_rng_data1_field_t;

typedef struct
{
    __IO uint32_t PRDS                      : 3;
    __IO uint32_t AMPM                      : 1;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t HZ1OE                     : 1;
    __IO uint32_t HZ1SEL                    : 1;
    __IO uint32_t START                     : 1;
    __IO uint32_t PRDX                      : 6;
    __IO uint32_t PRDSEL                    : 1;
} stc_rtc_cr0_field_t;

typedef struct
{
    __IO uint32_t WAIT                      : 1;
    __IO uint32_t WAITF                     : 1;
    uint32_t RESERVED2                      : 1;
    __IO uint32_t PRDF                      : 1;
    __IO uint32_t ALMF                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t ALMIE                     : 1;
    __IO uint32_t ALMEN                     : 1;
    __IO uint32_t CKSEL                     : 3;
} stc_rtc_cr1_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
} stc_rtc_sec_field_t;

typedef struct
{
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
} stc_rtc_min_field_t;

typedef struct
{
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
} stc_rtc_hour_field_t;

typedef struct
{
    __IO uint32_t WEEK                      : 3;
} stc_rtc_week_field_t;

typedef struct
{
    __IO uint32_t DAYL                      : 4;
    __IO uint32_t DAYH                      : 2;
} stc_rtc_day_field_t;

typedef struct
{
    __IO uint32_t MON                       : 5;
} stc_rtc_mon_field_t;

typedef struct
{
    __IO uint32_t YEARL                     : 4;
    __IO uint32_t YEARH                     : 4;
} stc_rtc_year_field_t;

typedef struct
{
    __IO uint32_t ALMMINL                   : 4;
    __IO uint32_t ALMMINH                   : 3;
} stc_rtc_almmin_field_t;

typedef struct
{
    __IO uint32_t ALMHOURL                  : 4;
    __IO uint32_t ALMHOURH                  : 2;
} stc_rtc_almhour_field_t;

typedef struct
{
    __IO uint32_t ALMWEEK                   : 7;
} stc_rtc_almweek_field_t;

typedef struct
{
    __IO uint32_t CR                        : 9;
    uint32_t RESERVED9                      : 6;
    __IO uint32_t EN                        : 1;
} stc_rtc_compen_field_t;

typedef struct
{
    __IO uint32_t SPR0                      : 1;
    __IO uint32_t SPR1                      : 1;
    __IO uint32_t CPHA                      : 1;
    __IO uint32_t CPOL                      : 1;
    __IO uint32_t MSTR                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t SPEN                      : 1;
    __IO uint32_t SPR2                      : 1;
} stc_spi_cr_field_t;

typedef struct
{
    __IO uint32_t SSN                       : 1;
} stc_spi_ssn_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t RXNE                      : 1;
    __IO uint32_t TXE                       : 1;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t MDF                       : 1;
    __IO uint32_t SSERR                     : 1;
    uint32_t RESERVED6                      : 1;
    __IO uint32_t SPIF                      : 1;
} stc_spi_stat_field_t;

typedef struct
{
    __IO uint32_t DAT                       : 8;
} stc_spi_data_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 2;
    __IO uint32_t INT_EN                    : 1;
    __IO uint32_t HDMA_RX                   : 1;
    __IO uint32_t HDMA_TX                   : 1;
    __IO uint32_t TXEIE                     : 1;
    __IO uint32_t RXNEIE                    : 1;
} stc_spi_cr2_field_t;

typedef struct
{
    __IO uint32_t INT_CLR                   : 1;
} stc_spi_iclr_field_t;

typedef struct
{
    __IO uint32_t RCH_EN                    : 1;
    __IO uint32_t XTH_EN                    : 1;
    __IO uint32_t RCL_EN                    : 1;
    __IO uint32_t XTL_EN                    : 1;
    __IO uint32_t PLL_EN                    : 1;
    __IO uint32_t CLK_SW5_SEL               : 3;
    __IO uint32_t HCLK_PRS                  : 3;
    __IO uint32_t PCLK_PRS                  : 2;
    uint32_t RESERVED13                     : 2;
    __IO uint32_t WAKEUP_BYRCH              : 1;
} stc_sysctrl_sysctrl0_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t EXTH_EN                   : 1;
    __IO uint32_t EXTL_EN                   : 1;
    __IO uint32_t XTL_ALWAYS_ON             : 1;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t RTC_LPW                   : 1;
    __IO uint32_t LOCKUP_EN                 : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t SWD_USE_IO                : 1;
    __IO uint32_t RTC_FREQ_ADJUST           : 3;
} stc_sysctrl_sysctrl1_field_t;

typedef struct
{
    __IO uint32_t SYSCTRL2                  :16;
} stc_sysctrl_sysctrl2_field_t;

typedef struct
{
    __IO uint32_t TRIM                      :11;
    __IO uint32_t STABLE                    : 1;
} stc_sysctrl_rch_cr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 2;
    __IO uint32_t XTH_FSEL                  : 2;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
} stc_sysctrl_xth_cr_field_t;

typedef struct
{
    __IO uint32_t TRIM                      :10;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
} stc_sysctrl_rcl_cr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 2;
    __IO uint32_t AMP_SEL                   : 2;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
} stc_sysctrl_xtl_cr_field_t;

typedef struct
{
    __IO uint32_t UART0                     : 1;
    __IO uint32_t UART1                     : 1;
    __IO uint32_t LPUART0                   : 1;
    __IO uint32_t LPUART1                   : 1;
    __IO uint32_t I2C0                      : 1;
    __IO uint32_t I2C1                      : 1;
    __IO uint32_t SPI0                      : 1;
    __IO uint32_t SPI1                      : 1;
    __IO uint32_t BASETIM                   : 1;
    __IO uint32_t LPTIM                     : 1;
    __IO uint32_t ADVTIM                    : 1;
    __IO uint32_t TIM3                      : 1;
    uint32_t RESERVED12                     : 1;
    __IO uint32_t OPA                       : 1;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t WDT                       : 1;
    __IO uint32_t ADC                       : 1;
    __IO uint32_t VC                        : 1;
    __IO uint32_t RNG                       : 1;
    __IO uint32_t PCNT                      : 1;
    __IO uint32_t RTC                       : 1;
    __IO uint32_t TRIM                      : 1;
    __IO uint32_t LCD                       : 1;
    uint32_t RESERVED23                     : 1;
    __IO uint32_t TICK                      : 1;
    __IO uint32_t SWD                       : 1;
    __IO uint32_t CRC                       : 1;
    __IO uint32_t AES                       : 1;
    __IO uint32_t GPIO                      : 1;
    __IO uint32_t DMA                       : 1;
    __IO uint32_t DIV                       : 1;
    __IO uint32_t FLASH                     : 1;
} stc_sysctrl_peri_clken_field_t;

typedef struct
{
    __IO uint32_t REFSEL                    : 2;
    __IO uint32_t FOSC                      : 3;
    __IO uint32_t DIVN                      : 4;
    __IO uint32_t IBSEL                     : 2;
    __IO uint32_t LFSEL                     : 2;
    __IO uint32_t FRSEL                     : 2;
    __IO uint32_t STARTUP                   : 3;
    __IO uint32_t STABLE                    : 1;
} stc_sysctrl_pll_cr_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_tim0_mode0_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim0_mode0_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_tim0_mode0_cnt32_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATEP                     : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
} stc_tim0_mode0_m0cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
} stc_tim0_mode0_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
} stc_tim0_mode0_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :12;
    __IO uint32_t MOE                       : 1;
} stc_tim0_mode0_dtr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim0_mode1_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CT                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t EDG1ST                    : 1;
    __IO uint32_t EDG2ND                    : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
} stc_tim0_mode1_m1cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
} stc_tim0_mode1_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
} stc_tim0_mode1_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t TS                        : 3;
    uint32_t RESERVED8                      : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
} stc_tim0_mode1_mscr_field_t;

typedef struct
{
    __IO uint32_t FLTA0                     : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FLTB0                     : 3;
    uint32_t RESERVED7                      :21;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim0_mode1_fltr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t CIEA                      : 1;
} stc_tim0_mode1_cr0_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
} stc_tim0_mode1_ccr0a_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_tim0_mode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim0_mode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
} stc_tim0_mode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
} stc_tim0_mode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
} stc_tim0_mode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    __IO uint32_t CCDS                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
} stc_tim0_mode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0_FLTA0               : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0_FLTB0               : 3;
    __IO uint32_t CCPB0                     : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim0_mode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    uint32_t RESERVED2                      : 2;
    __IO uint32_t CMB0E                     : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t ADTE                      : 1;
} stc_tim0_mode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
} stc_tim0_mode23_crch0_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VC0E                      : 1;
    __IO uint32_t VC1E                      : 1;
} stc_tim0_mode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
} stc_tim0_mode23_rcr_field_t;

typedef struct
{
    __IO uint32_t ARRDM                     :16;
} stc_tim0_mode23_arrdm_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
} stc_tim0_mode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
} stc_tim0_mode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_tim1_mode0_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim1_mode0_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_tim1_mode0_cnt32_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATEP                     : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
} stc_tim1_mode0_m0cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
} stc_tim1_mode0_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
} stc_tim1_mode0_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :12;
    __IO uint32_t MOE                       : 1;
} stc_tim1_mode0_dtr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim1_mode1_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CT                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t EDG1ST                    : 1;
    __IO uint32_t EDG2ND                    : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
} stc_tim1_mode1_m1cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
} stc_tim1_mode1_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
} stc_tim1_mode1_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t TS                        : 3;
    uint32_t RESERVED8                      : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
} stc_tim1_mode1_mscr_field_t;

typedef struct
{
    __IO uint32_t FLTA0                     : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FLTB0                     : 3;
    uint32_t RESERVED7                      :21;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim1_mode1_fltr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t CIEA                      : 1;
} stc_tim1_mode1_cr0_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
} stc_tim1_mode1_ccr0a_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_tim1_mode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim1_mode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
} stc_tim1_mode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
} stc_tim1_mode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
} stc_tim1_mode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    __IO uint32_t CCDS                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
} stc_tim1_mode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0_FLTA0               : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0_FLTB0               : 3;
    __IO uint32_t CCPB0                     : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim1_mode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    uint32_t RESERVED2                      : 2;
    __IO uint32_t CMB0E                     : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t ADTE                      : 1;
} stc_tim1_mode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
} stc_tim1_mode23_crch0_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VC0E                      : 1;
    __IO uint32_t VC1E                      : 1;
} stc_tim1_mode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
} stc_tim1_mode23_rcr_field_t;

typedef struct
{
    __IO uint32_t ARRDM                     :16;
} stc_tim1_mode23_arrdm_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
} stc_tim1_mode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
} stc_tim1_mode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_tim2_mode0_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim2_mode0_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_tim2_mode0_cnt32_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATEP                     : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
} stc_tim2_mode0_m0cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
} stc_tim2_mode0_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
} stc_tim2_mode0_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :12;
    __IO uint32_t MOE                       : 1;
} stc_tim2_mode0_dtr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim2_mode1_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CT                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t EDG1ST                    : 1;
    __IO uint32_t EDG2ND                    : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
} stc_tim2_mode1_m1cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
} stc_tim2_mode1_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
} stc_tim2_mode1_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t TS                        : 3;
    uint32_t RESERVED8                      : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
} stc_tim2_mode1_mscr_field_t;

typedef struct
{
    __IO uint32_t FLTA0                     : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FLTB0                     : 3;
    uint32_t RESERVED7                      :21;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim2_mode1_fltr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t CIEA                      : 1;
} stc_tim2_mode1_cr0_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
} stc_tim2_mode1_ccr0a_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_tim2_mode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim2_mode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
} stc_tim2_mode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
} stc_tim2_mode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    uint32_t RESERVED3                      : 2;
    __IO uint32_t CB0F                      : 1;
    uint32_t RESERVED6                      : 2;
    __IO uint32_t CA0E                      : 1;
    uint32_t RESERVED9                      : 2;
    __IO uint32_t CB0E                      : 1;
    uint32_t RESERVED12                     : 2;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
} stc_tim2_mode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    __IO uint32_t CCDS                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
} stc_tim2_mode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0_FLTA0               : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0_FLTB0               : 3;
    __IO uint32_t CCPB0                     : 1;
    uint32_t RESERVED8                      :16;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim2_mode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    uint32_t RESERVED2                      : 2;
    __IO uint32_t CMB0E                     : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t ADTE                      : 1;
} stc_tim2_mode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
} stc_tim2_mode23_crch0_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VC0E                      : 1;
    __IO uint32_t VC1E                      : 1;
} stc_tim2_mode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
} stc_tim2_mode23_rcr_field_t;

typedef struct
{
    __IO uint32_t ARRDM                     :16;
} stc_tim2_mode23_arrdm_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
} stc_tim2_mode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
} stc_tim2_mode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_tim3_mode0_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim3_mode0_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_tim3_mode0_cnt32_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOGEN                     : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATEP                     : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
} stc_tim3_mode0_m0cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
} stc_tim3_mode0_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
} stc_tim3_mode0_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      :12;
    __IO uint32_t MOE                       : 1;
} stc_tim3_mode0_dtr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim3_mode1_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CT                        : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t EDG1ST                    : 1;
    __IO uint32_t EDG2ND                    : 1;
    __IO uint32_t UIE                       : 1;
    uint32_t RESERVED11                     : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
} stc_tim3_mode1_m1cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
} stc_tim3_mode1_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
} stc_tim3_mode1_iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 5;
    __IO uint32_t TS                        : 3;
    uint32_t RESERVED8                      : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
} stc_tim3_mode1_mscr_field_t;

typedef struct
{
    __IO uint32_t FLTA0                     : 3;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t FLTB0                     : 3;
    uint32_t RESERVED7                      :21;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim3_mode1_fltr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 8;
    __IO uint32_t CIEA                      : 1;
} stc_tim3_mode1_cr0_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
} stc_tim3_mode1_ccr0a_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_tim3_mode23_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim3_mode23_cnt_field_t;

typedef struct
{
    __IO uint32_t CTEN                      : 1;
    __IO uint32_t COMP                      : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t PWM2S                     : 1;
    __IO uint32_t PRS                       : 3;
    __IO uint32_t BUFPEN                    : 1;
    __IO uint32_t CRG                       : 1;
    __IO uint32_t CFG                       : 1;
    __IO uint32_t UIE                       : 1;
    __IO uint32_t UDE                       : 1;
    __IO uint32_t MODE                      : 2;
    __IO uint32_t ONESHOT                   : 1;
    __IO uint32_t CSG                       : 1;
    __IO uint32_t OCCS                      : 1;
    __IO uint32_t URS                       : 1;
    __IO uint32_t TDE                       : 1;
    __IO uint32_t TIE                       : 1;
    __IO uint32_t BIE                       : 1;
    __IO uint32_t CIS                       : 2;
    __IO uint32_t OCCE                      : 1;
    __IO uint32_t TG                        : 1;
    __IO uint32_t UG                        : 1;
    __IO uint32_t BG                        : 1;
    __IO uint32_t DIR                       : 1;
} stc_tim3_mode23_m23cr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    __IO uint32_t CA1F                      : 1;
    __IO uint32_t CA2F                      : 1;
    __IO uint32_t CB0F                      : 1;
    __IO uint32_t CB1F                      : 1;
    __IO uint32_t CB2F                      : 1;
    __IO uint32_t CA0E                      : 1;
    __IO uint32_t CA1E                      : 1;
    __IO uint32_t CA2E                      : 1;
    __IO uint32_t CB0E                      : 1;
    __IO uint32_t CB1E                      : 1;
    __IO uint32_t CB2E                      : 1;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
} stc_tim3_mode23_ifr_field_t;

typedef struct
{
    __IO uint32_t UIF                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t CA0F                      : 1;
    __IO uint32_t CA1F                      : 1;
    __IO uint32_t CA2F                      : 1;
    __IO uint32_t CB0F                      : 1;
    __IO uint32_t CB1F                      : 1;
    __IO uint32_t CB2F                      : 1;
    __IO uint32_t CA0E                      : 1;
    __IO uint32_t CA1E                      : 1;
    __IO uint32_t CA2E                      : 1;
    __IO uint32_t CB0E                      : 1;
    __IO uint32_t CB1E                      : 1;
    __IO uint32_t CB2E                      : 1;
    __IO uint32_t BIF                       : 1;
    __IO uint32_t TIF                       : 1;
} stc_tim3_mode23_iclr_field_t;

typedef struct
{
    __IO uint32_t MMS                       : 3;
    __IO uint32_t CCDS                      : 1;
    __IO uint32_t MSM                       : 1;
    __IO uint32_t TS                        : 3;
    __IO uint32_t SMS                       : 3;
    __IO uint32_t IA0S                      : 1;
    __IO uint32_t IB0S                      : 1;
} stc_tim3_mode23_mscr_field_t;

typedef struct
{
    __IO uint32_t OCMA0_FLTA0               : 3;
    __IO uint32_t CCPA0                     : 1;
    __IO uint32_t OCMB0_FLTB0               : 3;
    __IO uint32_t CCPB0                     : 1;
    __IO uint32_t OCMA1_FLTA1               : 3;
    __IO uint32_t CCPA1                     : 1;
    __IO uint32_t OCMB1_FLTB1               : 3;
    __IO uint32_t CCPB1                     : 1;
    __IO uint32_t OCMA2_FLTA2               : 3;
    __IO uint32_t CCPA2                     : 1;
    __IO uint32_t OCMB2_FLTB2               : 3;
    __IO uint32_t CCPB2                     : 1;
    __IO uint32_t FLTBK                     : 3;
    __IO uint32_t BKP                       : 1;
    __IO uint32_t FLTET                     : 3;
    __IO uint32_t ETP                       : 1;
} stc_tim3_mode23_fltr_field_t;

typedef struct
{
    __IO uint32_t UEVE                      : 1;
    __IO uint32_t CMA0E                     : 1;
    __IO uint32_t CMA1E                     : 1;
    __IO uint32_t CMA2E                     : 1;
    __IO uint32_t CMB0E                     : 1;
    __IO uint32_t CMB1E                     : 1;
    __IO uint32_t CMB2E                     : 1;
    __IO uint32_t ADTE                      : 1;
} stc_tim3_mode23_adtr_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
} stc_tim3_mode23_crch0_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
} stc_tim3_mode23_crch1_field_t;

typedef struct
{
    __IO uint32_t CFA_CRA_BKSA              : 2;
    __IO uint32_t CFB_CRB_BKSB              : 2;
    __IO uint32_t CSA                       : 1;
    __IO uint32_t CSB                       : 1;
    __IO uint32_t BUFEA                     : 1;
    __IO uint32_t BUFEB                     : 1;
    __IO uint32_t CIEA                      : 1;
    __IO uint32_t CIEB                      : 1;
    __IO uint32_t CDEA                      : 1;
    __IO uint32_t CDEB                      : 1;
    __IO uint32_t CISB                      : 2;
    __IO uint32_t CCGA                      : 1;
    __IO uint32_t CCGB                      : 1;
} stc_tim3_mode23_crch2_field_t;

typedef struct
{
    __IO uint32_t DTR                       : 8;
    __IO uint32_t BKSEL                     : 1;
    __IO uint32_t DTEN                      : 1;
    __IO uint32_t BKE                       : 1;
    __IO uint32_t AOE                       : 1;
    __IO uint32_t MOE                       : 1;
    __IO uint32_t SAFEEN                    : 1;
    __IO uint32_t VC0E                      : 1;
    __IO uint32_t VC1E                      : 1;
} stc_tim3_mode23_dtr_field_t;

typedef struct
{
    __IO uint32_t RCR                       : 8;
} stc_tim3_mode23_rcr_field_t;

typedef struct
{
    __IO uint32_t ARRDM                     :16;
} stc_tim3_mode23_arrdm_field_t;

typedef struct
{
    __IO uint32_t CCR0A                     :16;
} stc_tim3_mode23_ccr0a_field_t;

typedef struct
{
    __IO uint32_t CCR0B                     :16;
} stc_tim3_mode23_ccr0b_field_t;

typedef struct
{
    __IO uint32_t CCR1A                     :16;
} stc_tim3_mode23_ccr1a_field_t;

typedef struct
{
    __IO uint32_t CCR1B                     :16;
} stc_tim3_mode23_ccr1b_field_t;

typedef struct
{
    __IO uint32_t CCR2A                     :16;
} stc_tim3_mode23_ccr2a_field_t;

typedef struct
{
    __IO uint32_t CCR2B                     :16;
} stc_tim3_mode23_ccr2b_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim4_cnter_field_t;

typedef struct
{
    __IO uint32_t PERA                      :16;
} stc_tim4_perar_field_t;

typedef struct
{
    __IO uint32_t PERB                      :16;
} stc_tim4_perbr_field_t;

typedef struct
{
    __IO uint32_t GCMA                      :16;
} stc_tim4_gcmar_field_t;

typedef struct
{
    __IO uint32_t GCMB                      :16;
} stc_tim4_gcmbr_field_t;

typedef struct
{
    __IO uint32_t GCMC                      :16;
} stc_tim4_gcmcr_field_t;

typedef struct
{
    __IO uint32_t GCMD                      :16;
} stc_tim4_gcmdr_field_t;

typedef struct
{
    __IO uint32_t SCMA                      :16;
} stc_tim4_scmar_field_t;

typedef struct
{
    __IO uint32_t SCMB                      :16;
} stc_tim4_scmbr_field_t;

typedef struct
{
    __IO uint32_t DTUA                      :16;
} stc_tim4_dtuar_field_t;

typedef struct
{
    __IO uint32_t DTDA                      :16;
} stc_tim4_dtdar_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    __IO uint32_t MODE                      : 3;
    __IO uint32_t CKDIV                     : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t DIR                       : 1;
    uint32_t RESERVED9                      : 7;
    __IO uint32_t ZMSKREV                   : 1;
    __IO uint32_t ZMSKPOS                   : 1;
    __IO uint32_t ZMSK                      : 2;
} stc_tim4_gconr_field_t;

typedef struct
{
    __IO uint32_t INTENA                    : 1;
    __IO uint32_t INTENB                    : 1;
    __IO uint32_t INTENC                    : 1;
    __IO uint32_t INTEND                    : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t INTENOVF                  : 1;
    __IO uint32_t INTENUDF                  : 1;
    __IO uint32_t INTENDE                   : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t INTENSAML                 : 1;
    __IO uint32_t INTENSAMH                 : 1;
    __IO uint32_t INTENSAU                  : 1;
    __IO uint32_t INTENSAD                  : 1;
    __IO uint32_t INTENSBU                  : 1;
    __IO uint32_t INTENSBD                  : 1;
} stc_tim4_iconr_field_t;

typedef struct
{
    __IO uint32_t CAPCA                     : 1;
    __IO uint32_t STACA                     : 1;
    __IO uint32_t STPCA                     : 1;
    __IO uint32_t STASTPSA                  : 1;
    __IO uint32_t CMPCA                     : 2;
    __IO uint32_t PERCA                     : 2;
    __IO uint32_t OUTENA                    : 1;
    __IO uint32_t DISSELA                   : 2;
    __IO uint32_t DISVALA                   : 2;
    uint32_t RESERVED13                     : 3;
    __IO uint32_t CAPCB                     : 1;
    __IO uint32_t STACB                     : 1;
    __IO uint32_t STPCB                     : 1;
    __IO uint32_t STASTPSB                  : 1;
    __IO uint32_t CMPCB                     : 2;
    __IO uint32_t PERCB                     : 2;
    __IO uint32_t OUTENB                    : 1;
    __IO uint32_t DISSELB                   : 2;
    __IO uint32_t DISVALB                   : 2;
} stc_tim4_pconr_field_t;

typedef struct
{
    __IO uint32_t BENA                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t BENB                      : 1;
    uint32_t RESERVED3                      : 5;
    __IO uint32_t BENP                      : 1;
} stc_tim4_bconr_field_t;

typedef struct
{
    __IO uint32_t DTCEN                     : 1;
    uint32_t RESERVED1                      : 7;
    __IO uint32_t SEPA                      : 1;
} stc_tim4_dconr_field_t;

typedef struct
{
    __IO uint32_t NOFIENGA                  : 1;
    __IO uint32_t NOFICKGA                  : 2;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t NOFIENGB                  : 1;
    __IO uint32_t NOFICKGB                  : 2;
    uint32_t RESERVED7                      : 9;
    __IO uint32_t NOFIENTA                  : 1;
    __IO uint32_t NOFICKTA                  : 2;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t NOFIENTB                  : 1;
    __IO uint32_t NOFICKTB                  : 2;
    uint32_t RESERVED23                     : 1;
    __IO uint32_t NOFIENTC                  : 1;
    __IO uint32_t NOFICKTC                  : 2;
    uint32_t RESERVED27                     : 1;
    __IO uint32_t NOFIENTD                  : 1;
    __IO uint32_t NOFICKTD                  : 2;
} stc_tim4_fconr_field_t;

typedef struct
{
    __IO uint32_t GEPERIA                   : 1;
    __IO uint32_t GEPERIB                   : 1;
    __IO uint32_t GEPERIC                   : 1;
    __IO uint32_t GEPERID                   : 1;
    uint32_t RESERVED4                      :12;
    __IO uint32_t PCNTE                     : 2;
    __IO uint32_t PCNTS                     : 3;
} stc_tim4_vperr_field_t;

typedef struct
{
    __IO uint32_t CMAF                      : 1;
    __IO uint32_t CMBF                      : 1;
    __IO uint32_t CMCF                      : 1;
    __IO uint32_t CMDF                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFF                      : 1;
    __IO uint32_t UDFF                      : 1;
    __IO uint32_t DTEF                      : 1;
    __IO uint32_t CMSAUF                    : 1;
    __IO uint32_t CMSADF                    : 1;
    __IO uint32_t CMSBUF                    : 1;
    __IO uint32_t CMSBDF                    : 1;
    uint32_t RESERVED13                     : 8;
    __IO uint32_t VPERNUM                   : 3;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t DIRF                      : 1;
} stc_tim4_stflr_field_t;

typedef struct
{
    __IO uint32_t HSTA0                     : 1;
    __IO uint32_t HSTA1                     : 1;
    __IO uint32_t HSTA2                     : 1;
    __IO uint32_t HSTA3                     : 1;
    __IO uint32_t HSTA4                     : 1;
    __IO uint32_t HSTA5                     : 1;
    __IO uint32_t HSTA6                     : 1;
    __IO uint32_t HSTA7                     : 1;
    __IO uint32_t HSTA8                     : 1;
    __IO uint32_t HSTA9                     : 1;
    __IO uint32_t HSTA10                    : 1;
    __IO uint32_t HSTA11                    : 1;
    __IO uint32_t HSTA12                    : 1;
    __IO uint32_t HSTA13                    : 1;
    __IO uint32_t HSTA14                    : 1;
    __IO uint32_t HSTA15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STARTS                    : 1;
} stc_tim4_hstar_field_t;

typedef struct
{
    __IO uint32_t HSTP0                     : 1;
    __IO uint32_t HSTP1                     : 1;
    __IO uint32_t HSTP2                     : 1;
    __IO uint32_t HSTP3                     : 1;
    __IO uint32_t HSTP4                     : 1;
    __IO uint32_t HSTP5                     : 1;
    __IO uint32_t HSTP6                     : 1;
    __IO uint32_t HSTP7                     : 1;
    __IO uint32_t HSTP8                     : 1;
    __IO uint32_t HSTP9                     : 1;
    __IO uint32_t HSTP10                    : 1;
    __IO uint32_t HSTP11                    : 1;
    __IO uint32_t HSTP12                    : 1;
    __IO uint32_t HSTP13                    : 1;
    __IO uint32_t HSTP14                    : 1;
    __IO uint32_t HSTP15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STOPS                     : 1;
} stc_tim4_hstpr_field_t;

typedef struct
{
    __IO uint32_t HCEL0                     : 1;
    __IO uint32_t HCEL1                     : 1;
    __IO uint32_t HCEL2                     : 1;
    __IO uint32_t HCEL3                     : 1;
    __IO uint32_t HCEL4                     : 1;
    __IO uint32_t HCEL5                     : 1;
    __IO uint32_t HCEL6                     : 1;
    __IO uint32_t HCEL7                     : 1;
    __IO uint32_t HCEL8                     : 1;
    __IO uint32_t HCEL9                     : 1;
    __IO uint32_t HCEL10                    : 1;
    __IO uint32_t HCEL11                    : 1;
    __IO uint32_t HCEL12                    : 1;
    __IO uint32_t HCEL13                    : 1;
    __IO uint32_t HCEL14                    : 1;
    __IO uint32_t HCEL15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STARTS                    : 1;
} stc_tim4_hcelr_field_t;

typedef struct
{
    __IO uint32_t HCPA0                     : 1;
    __IO uint32_t HCPA1                     : 1;
    __IO uint32_t HCPA2                     : 1;
    __IO uint32_t HCPA3                     : 1;
    __IO uint32_t HCPA4                     : 1;
    __IO uint32_t HCPA5                     : 1;
    __IO uint32_t HCPA6                     : 1;
    __IO uint32_t HCPA7                     : 1;
    __IO uint32_t HCPA8                     : 1;
    __IO uint32_t HCPA9                     : 1;
    __IO uint32_t HCPA10                    : 1;
    __IO uint32_t HCPA11                    : 1;
    __IO uint32_t HCPA12                    : 1;
    __IO uint32_t HCPA13                    : 1;
    __IO uint32_t HCPA14                    : 1;
    __IO uint32_t HCPA15                    : 1;
} stc_tim4_hcpar_field_t;

typedef struct
{
    __IO uint32_t HCPB0                     : 1;
    __IO uint32_t HCPB1                     : 1;
    __IO uint32_t HCPB2                     : 1;
    __IO uint32_t HCPB3                     : 1;
    __IO uint32_t HCPB4                     : 1;
    __IO uint32_t HCPB5                     : 1;
    __IO uint32_t HCPB6                     : 1;
    __IO uint32_t HCPB7                     : 1;
    __IO uint32_t HCPB8                     : 1;
    __IO uint32_t HCPB9                     : 1;
    __IO uint32_t HCPB10                    : 1;
    __IO uint32_t HCPB11                    : 1;
    __IO uint32_t HCPB12                    : 1;
    __IO uint32_t HCPB13                    : 1;
    __IO uint32_t HCPB14                    : 1;
    __IO uint32_t HCPB15                    : 1;
} stc_tim4_hcpbr_field_t;

typedef struct
{
    __IO uint32_t HCUP0                     : 1;
    __IO uint32_t HCUP1                     : 1;
    __IO uint32_t HCUP2                     : 1;
    __IO uint32_t HCUP3                     : 1;
    __IO uint32_t HCUP4                     : 1;
    __IO uint32_t HCUP5                     : 1;
    __IO uint32_t HCUP6                     : 1;
    __IO uint32_t HCUP7                     : 1;
    __IO uint32_t HCUP8                     : 1;
    __IO uint32_t HCUP9                     : 1;
    __IO uint32_t HCUP10                    : 1;
    __IO uint32_t HCUP11                    : 1;
    __IO uint32_t HCUP12                    : 1;
    __IO uint32_t HCUP13                    : 1;
    __IO uint32_t HCUP14                    : 1;
    __IO uint32_t HCUP15                    : 1;
    __IO uint32_t HCUP16                    : 1;
    __IO uint32_t HCUP17                    : 1;
    __IO uint32_t HCUP18                    : 1;
    __IO uint32_t HCUP19                    : 1;
} stc_tim4_hcupr_field_t;

typedef struct
{
    __IO uint32_t HCDO0                     : 1;
    __IO uint32_t HCDO1                     : 1;
    __IO uint32_t HCDO2                     : 1;
    __IO uint32_t HCDO3                     : 1;
    __IO uint32_t HCDO4                     : 1;
    __IO uint32_t HCDO5                     : 1;
    __IO uint32_t HCDO6                     : 1;
    __IO uint32_t HCDO7                     : 1;
    __IO uint32_t HCDO8                     : 1;
    __IO uint32_t HCDO9                     : 1;
    __IO uint32_t HCDO10                    : 1;
    __IO uint32_t HCDO11                    : 1;
    __IO uint32_t HCDO12                    : 1;
    __IO uint32_t HCDO13                    : 1;
    __IO uint32_t HCDO14                    : 1;
    __IO uint32_t HCDO15                    : 1;
    __IO uint32_t HCDO16                    : 1;
    __IO uint32_t HCDO17                    : 1;
    __IO uint32_t HCDO18                    : 1;
    __IO uint32_t HCDO19                    : 1;
} stc_tim4_hcdor_field_t;

typedef struct
{
    __IO uint32_t CMAF                      : 1;
    __IO uint32_t CMBF                      : 1;
    __IO uint32_t CMCF                      : 1;
    __IO uint32_t CMDF                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFF                      : 1;
    __IO uint32_t UDFF                      : 1;
    __IO uint32_t DTEF                      : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t SAMLF                     : 1;
    __IO uint32_t SAMHF                     : 1;
} stc_tim4_ifr_field_t;

typedef struct
{
    __IO uint32_t CMAC                      : 1;
    __IO uint32_t CMBC                      : 1;
    __IO uint32_t CMCC                      : 1;
    __IO uint32_t CMDC                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFC                      : 1;
    __IO uint32_t UDFC                      : 1;
    __IO uint32_t DTEC                      : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t SAMLC                     : 1;
    __IO uint32_t SAMHC                     : 1;
} stc_tim4_iclr_field_t;

typedef struct
{
    __IO uint32_t CMAE                      : 1;
    __IO uint32_t CMBE                      : 1;
    __IO uint32_t CMCE                      : 1;
    __IO uint32_t CMDE                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFE                      : 1;
    __IO uint32_t UDFE                      : 1;
    __IO uint32_t DITENA                    : 1;
    __IO uint32_t DITENB                    : 1;
    __IO uint32_t DITENS                    : 1;
    __IO uint32_t CMSAE                     : 1;
    __IO uint32_t CMSBE                     : 1;
    __IO uint32_t DMA_G_CMA                 : 1;
    __IO uint32_t DMA_G_CMB                 : 1;
    __IO uint32_t DMA_G_CMC                 : 1;
    __IO uint32_t DMA_G_CMD                 : 1;
    uint32_t RESERVED17                     : 2;
    __IO uint32_t DMA_G_OVF                 : 1;
    __IO uint32_t DMA_G_UDF                 : 1;
    __IO uint32_t DMA_S_CMA                 : 1;
    __IO uint32_t DMA_S_CMB                 : 1;
} stc_tim4_cr_field_t;

typedef struct
{
    __IO uint32_t FBRAKE                    : 1;
    __IO uint32_t FSAME                     : 1;
    __IO uint32_t BFILTS                    : 2;
    __IO uint32_t BFILTEN                   : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t SOFTBK                    : 1;
    __IO uint32_t SML0                      : 1;
    __IO uint32_t SML1                      : 1;
    __IO uint32_t SML2                      : 1;
    __IO uint32_t SMH0                      : 1;
    __IO uint32_t SMH1                      : 1;
    __IO uint32_t SMH2                      : 1;
} stc_tim4_aossr_field_t;

typedef struct
{
    __IO uint32_t FBRAKE                    : 1;
    __IO uint32_t FSAME                     : 1;
} stc_tim4_aoscl_field_t;

typedef struct
{
    __IO uint32_t EN0                       : 1;
    __IO uint32_t EN1                       : 1;
    __IO uint32_t EN2                       : 1;
    __IO uint32_t EN3                       : 1;
    __IO uint32_t EN4                       : 1;
    __IO uint32_t EN5                       : 1;
    __IO uint32_t EN6                       : 1;
    __IO uint32_t EN7                       : 1;
    __IO uint32_t EN8                       : 1;
    __IO uint32_t EN9                       : 1;
    __IO uint32_t EN10                      : 1;
    __IO uint32_t EN11                      : 1;
    __IO uint32_t EN12                      : 1;
    __IO uint32_t EN13                      : 1;
    __IO uint32_t EN14                      : 1;
    __IO uint32_t EN15                      : 1;
} stc_tim4_ptbks_field_t;

typedef struct
{
    __IO uint32_t TRIGAS                    : 4;
    __IO uint32_t TRIGBS                    : 4;
    __IO uint32_t TRIGCS                    : 4;
    __IO uint32_t TRIGDS                    : 4;
} stc_tim4_ttrig_field_t;

typedef struct
{
    __IO uint32_t IAOS0S                    : 4;
    __IO uint32_t IAOS1S                    : 4;
    __IO uint32_t IAOS2S                    : 4;
    __IO uint32_t IAOS3S                    : 4;
} stc_tim4_itrig_field_t;

typedef struct
{
    __IO uint32_t POL0                      : 1;
    __IO uint32_t POL1                      : 1;
    __IO uint32_t POL2                      : 1;
    __IO uint32_t POL3                      : 1;
    __IO uint32_t POL4                      : 1;
    __IO uint32_t POL5                      : 1;
    __IO uint32_t POL6                      : 1;
    __IO uint32_t POL7                      : 1;
    __IO uint32_t POL8                      : 1;
    __IO uint32_t POL9                      : 1;
    __IO uint32_t POL10                     : 1;
    __IO uint32_t POL11                     : 1;
    __IO uint32_t POL12                     : 1;
    __IO uint32_t POL13                     : 1;
    __IO uint32_t POL14                     : 1;
    __IO uint32_t POL15                     : 1;
} stc_tim4_ptbkp_field_t;

typedef struct
{
    __IO uint32_t SSTA0                     : 1;
    __IO uint32_t SSTA1                     : 1;
    __IO uint32_t SSTA2                     : 1;
} stc_tim4_sstar_field_t;

typedef struct
{
    __IO uint32_t SSTP0                     : 1;
    __IO uint32_t SSTP1                     : 1;
    __IO uint32_t SSTP2                     : 1;
} stc_tim4_sstpr_field_t;

typedef struct
{
    __IO uint32_t SCLR0                     : 1;
    __IO uint32_t SCLR1                     : 1;
    __IO uint32_t SCLR2                     : 1;
} stc_tim4_sclrr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim5_cnter_field_t;

typedef struct
{
    __IO uint32_t PERA                      :16;
} stc_tim5_perar_field_t;

typedef struct
{
    __IO uint32_t PERB                      :16;
} stc_tim5_perbr_field_t;

typedef struct
{
    __IO uint32_t GCMA                      :16;
} stc_tim5_gcmar_field_t;

typedef struct
{
    __IO uint32_t GCMB                      :16;
} stc_tim5_gcmbr_field_t;

typedef struct
{
    __IO uint32_t GCMC                      :16;
} stc_tim5_gcmcr_field_t;

typedef struct
{
    __IO uint32_t GCMD                      :16;
} stc_tim5_gcmdr_field_t;

typedef struct
{
    __IO uint32_t SCMA                      :16;
} stc_tim5_scmar_field_t;

typedef struct
{
    __IO uint32_t SCMB                      :16;
} stc_tim5_scmbr_field_t;

typedef struct
{
    __IO uint32_t DTUA                      :16;
} stc_tim5_dtuar_field_t;

typedef struct
{
    __IO uint32_t DTDA                      :16;
} stc_tim5_dtdar_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    __IO uint32_t MODE                      : 3;
    __IO uint32_t CKDIV                     : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t DIR                       : 1;
    uint32_t RESERVED9                      : 7;
    __IO uint32_t ZMSKREV                   : 1;
    __IO uint32_t ZMSKPOS                   : 1;
    __IO uint32_t ZMSK                      : 2;
} stc_tim5_gconr_field_t;

typedef struct
{
    __IO uint32_t INTENA                    : 1;
    __IO uint32_t INTENB                    : 1;
    __IO uint32_t INTENC                    : 1;
    __IO uint32_t INTEND                    : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t INTENOVF                  : 1;
    __IO uint32_t INTENUDF                  : 1;
    __IO uint32_t INTENDE                   : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t INTENSAML                 : 1;
    __IO uint32_t INTENSAMH                 : 1;
    __IO uint32_t INTENSAU                  : 1;
    __IO uint32_t INTENSAD                  : 1;
    __IO uint32_t INTENSBU                  : 1;
    __IO uint32_t INTENSBD                  : 1;
} stc_tim5_iconr_field_t;

typedef struct
{
    __IO uint32_t CAPCA                     : 1;
    __IO uint32_t STACA                     : 1;
    __IO uint32_t STPCA                     : 1;
    __IO uint32_t STASTPSA                  : 1;
    __IO uint32_t CMPCA                     : 2;
    __IO uint32_t PERCA                     : 2;
    __IO uint32_t OUTENA                    : 1;
    __IO uint32_t DISSELA                   : 2;
    __IO uint32_t DISVALA                   : 2;
    uint32_t RESERVED13                     : 3;
    __IO uint32_t CAPCB                     : 1;
    __IO uint32_t STACB                     : 1;
    __IO uint32_t STPCB                     : 1;
    __IO uint32_t STASTPSB                  : 1;
    __IO uint32_t CMPCB                     : 2;
    __IO uint32_t PERCB                     : 2;
    __IO uint32_t OUTENB                    : 1;
    __IO uint32_t DISSELB                   : 2;
    __IO uint32_t DISVALB                   : 2;
} stc_tim5_pconr_field_t;

typedef struct
{
    __IO uint32_t BENA                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t BENB                      : 1;
    uint32_t RESERVED3                      : 5;
    __IO uint32_t BENP                      : 1;
} stc_tim5_bconr_field_t;

typedef struct
{
    __IO uint32_t DTCEN                     : 1;
    uint32_t RESERVED1                      : 7;
    __IO uint32_t SEPA                      : 1;
} stc_tim5_dconr_field_t;

typedef struct
{
    __IO uint32_t NOFIENGA                  : 1;
    __IO uint32_t NOFICKGA                  : 2;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t NOFIENGB                  : 1;
    __IO uint32_t NOFICKGB                  : 2;
    uint32_t RESERVED7                      : 9;
    __IO uint32_t NOFIENTA                  : 1;
    __IO uint32_t NOFICKTA                  : 2;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t NOFIENTB                  : 1;
    __IO uint32_t NOFICKTB                  : 2;
    uint32_t RESERVED23                     : 1;
    __IO uint32_t NOFIENTC                  : 1;
    __IO uint32_t NOFICKTC                  : 2;
    uint32_t RESERVED27                     : 1;
    __IO uint32_t NOFIENTD                  : 1;
    __IO uint32_t NOFICKTD                  : 2;
} stc_tim5_fconr_field_t;

typedef struct
{
    __IO uint32_t GEPERIA                   : 1;
    __IO uint32_t GEPERIB                   : 1;
    __IO uint32_t GEPERIC                   : 1;
    __IO uint32_t GEPERID                   : 1;
    uint32_t RESERVED4                      :12;
    __IO uint32_t PCNTE                     : 2;
    __IO uint32_t PCNTS                     : 3;
} stc_tim5_vperr_field_t;

typedef struct
{
    __IO uint32_t CMAF                      : 1;
    __IO uint32_t CMBF                      : 1;
    __IO uint32_t CMCF                      : 1;
    __IO uint32_t CMDF                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFF                      : 1;
    __IO uint32_t UDFF                      : 1;
    __IO uint32_t DTEF                      : 1;
    __IO uint32_t CMSAUF                    : 1;
    __IO uint32_t CMSADF                    : 1;
    __IO uint32_t CMSBUF                    : 1;
    __IO uint32_t CMSBDF                    : 1;
    uint32_t RESERVED13                     : 8;
    __IO uint32_t VPERNUM                   : 3;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t DIRF                      : 1;
} stc_tim5_stflr_field_t;

typedef struct
{
    __IO uint32_t HSTA0                     : 1;
    __IO uint32_t HSTA1                     : 1;
    __IO uint32_t HSTA2                     : 1;
    __IO uint32_t HSTA3                     : 1;
    __IO uint32_t HSTA4                     : 1;
    __IO uint32_t HSTA5                     : 1;
    __IO uint32_t HSTA6                     : 1;
    __IO uint32_t HSTA7                     : 1;
    __IO uint32_t HSTA8                     : 1;
    __IO uint32_t HSTA9                     : 1;
    __IO uint32_t HSTA10                    : 1;
    __IO uint32_t HSTA11                    : 1;
    __IO uint32_t HSTA12                    : 1;
    __IO uint32_t HSTA13                    : 1;
    __IO uint32_t HSTA14                    : 1;
    __IO uint32_t HSTA15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STARTS                    : 1;
} stc_tim5_hstar_field_t;

typedef struct
{
    __IO uint32_t HSTP0                     : 1;
    __IO uint32_t HSTP1                     : 1;
    __IO uint32_t HSTP2                     : 1;
    __IO uint32_t HSTP3                     : 1;
    __IO uint32_t HSTP4                     : 1;
    __IO uint32_t HSTP5                     : 1;
    __IO uint32_t HSTP6                     : 1;
    __IO uint32_t HSTP7                     : 1;
    __IO uint32_t HSTP8                     : 1;
    __IO uint32_t HSTP9                     : 1;
    __IO uint32_t HSTP10                    : 1;
    __IO uint32_t HSTP11                    : 1;
    __IO uint32_t HSTP12                    : 1;
    __IO uint32_t HSTP13                    : 1;
    __IO uint32_t HSTP14                    : 1;
    __IO uint32_t HSTP15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STOPS                     : 1;
} stc_tim5_hstpr_field_t;

typedef struct
{
    __IO uint32_t HCEL0                     : 1;
    __IO uint32_t HCEL1                     : 1;
    __IO uint32_t HCEL2                     : 1;
    __IO uint32_t HCEL3                     : 1;
    __IO uint32_t HCEL4                     : 1;
    __IO uint32_t HCEL5                     : 1;
    __IO uint32_t HCEL6                     : 1;
    __IO uint32_t HCEL7                     : 1;
    __IO uint32_t HCEL8                     : 1;
    __IO uint32_t HCEL9                     : 1;
    __IO uint32_t HCEL10                    : 1;
    __IO uint32_t HCEL11                    : 1;
    __IO uint32_t HCEL12                    : 1;
    __IO uint32_t HCEL13                    : 1;
    __IO uint32_t HCEL14                    : 1;
    __IO uint32_t HCEL15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STARTS                    : 1;
} stc_tim5_hcelr_field_t;

typedef struct
{
    __IO uint32_t HCPA0                     : 1;
    __IO uint32_t HCPA1                     : 1;
    __IO uint32_t HCPA2                     : 1;
    __IO uint32_t HCPA3                     : 1;
    __IO uint32_t HCPA4                     : 1;
    __IO uint32_t HCPA5                     : 1;
    __IO uint32_t HCPA6                     : 1;
    __IO uint32_t HCPA7                     : 1;
    __IO uint32_t HCPA8                     : 1;
    __IO uint32_t HCPA9                     : 1;
    __IO uint32_t HCPA10                    : 1;
    __IO uint32_t HCPA11                    : 1;
    __IO uint32_t HCPA12                    : 1;
    __IO uint32_t HCPA13                    : 1;
    __IO uint32_t HCPA14                    : 1;
    __IO uint32_t HCPA15                    : 1;
} stc_tim5_hcpar_field_t;

typedef struct
{
    __IO uint32_t HCPB0                     : 1;
    __IO uint32_t HCPB1                     : 1;
    __IO uint32_t HCPB2                     : 1;
    __IO uint32_t HCPB3                     : 1;
    __IO uint32_t HCPB4                     : 1;
    __IO uint32_t HCPB5                     : 1;
    __IO uint32_t HCPB6                     : 1;
    __IO uint32_t HCPB7                     : 1;
    __IO uint32_t HCPB8                     : 1;
    __IO uint32_t HCPB9                     : 1;
    __IO uint32_t HCPB10                    : 1;
    __IO uint32_t HCPB11                    : 1;
    __IO uint32_t HCPB12                    : 1;
    __IO uint32_t HCPB13                    : 1;
    __IO uint32_t HCPB14                    : 1;
    __IO uint32_t HCPB15                    : 1;
} stc_tim5_hcpbr_field_t;

typedef struct
{
    __IO uint32_t HCUP0                     : 1;
    __IO uint32_t HCUP1                     : 1;
    __IO uint32_t HCUP2                     : 1;
    __IO uint32_t HCUP3                     : 1;
    __IO uint32_t HCUP4                     : 1;
    __IO uint32_t HCUP5                     : 1;
    __IO uint32_t HCUP6                     : 1;
    __IO uint32_t HCUP7                     : 1;
    __IO uint32_t HCUP8                     : 1;
    __IO uint32_t HCUP9                     : 1;
    __IO uint32_t HCUP10                    : 1;
    __IO uint32_t HCUP11                    : 1;
    __IO uint32_t HCUP12                    : 1;
    __IO uint32_t HCUP13                    : 1;
    __IO uint32_t HCUP14                    : 1;
    __IO uint32_t HCUP15                    : 1;
    __IO uint32_t HCUP16                    : 1;
    __IO uint32_t HCUP17                    : 1;
    __IO uint32_t HCUP18                    : 1;
    __IO uint32_t HCUP19                    : 1;
} stc_tim5_hcupr_field_t;

typedef struct
{
    __IO uint32_t HCDO0                     : 1;
    __IO uint32_t HCDO1                     : 1;
    __IO uint32_t HCDO2                     : 1;
    __IO uint32_t HCDO3                     : 1;
    __IO uint32_t HCDO4                     : 1;
    __IO uint32_t HCDO5                     : 1;
    __IO uint32_t HCDO6                     : 1;
    __IO uint32_t HCDO7                     : 1;
    __IO uint32_t HCDO8                     : 1;
    __IO uint32_t HCDO9                     : 1;
    __IO uint32_t HCDO10                    : 1;
    __IO uint32_t HCDO11                    : 1;
    __IO uint32_t HCDO12                    : 1;
    __IO uint32_t HCDO13                    : 1;
    __IO uint32_t HCDO14                    : 1;
    __IO uint32_t HCDO15                    : 1;
    __IO uint32_t HCDO16                    : 1;
    __IO uint32_t HCDO17                    : 1;
    __IO uint32_t HCDO18                    : 1;
    __IO uint32_t HCDO19                    : 1;
} stc_tim5_hcdor_field_t;

typedef struct
{
    __IO uint32_t CMAF                      : 1;
    __IO uint32_t CMBF                      : 1;
    __IO uint32_t CMCF                      : 1;
    __IO uint32_t CMDF                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFF                      : 1;
    __IO uint32_t UDFF                      : 1;
    __IO uint32_t DTEF                      : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t SAMLF                     : 1;
    __IO uint32_t SAMHF                     : 1;
} stc_tim5_ifr_field_t;

typedef struct
{
    __IO uint32_t CMAC                      : 1;
    __IO uint32_t CMBC                      : 1;
    __IO uint32_t CMCC                      : 1;
    __IO uint32_t CMDC                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFC                      : 1;
    __IO uint32_t UDFC                      : 1;
    __IO uint32_t DTEC                      : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t SAMLC                     : 1;
    __IO uint32_t SAMHC                     : 1;
} stc_tim5_iclr_field_t;

typedef struct
{
    __IO uint32_t CMAE                      : 1;
    __IO uint32_t CMBE                      : 1;
    __IO uint32_t CMCE                      : 1;
    __IO uint32_t CMDE                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFE                      : 1;
    __IO uint32_t UDFE                      : 1;
    __IO uint32_t DITENA                    : 1;
    __IO uint32_t DITENB                    : 1;
    __IO uint32_t DITENS                    : 1;
    __IO uint32_t CMSAE                     : 1;
    __IO uint32_t CMSBE                     : 1;
    __IO uint32_t DMA_G_CMA                 : 1;
    __IO uint32_t DMA_G_CMB                 : 1;
    __IO uint32_t DMA_G_CMC                 : 1;
    __IO uint32_t DMA_G_CMD                 : 1;
    uint32_t RESERVED17                     : 2;
    __IO uint32_t DMA_G_OVF                 : 1;
    __IO uint32_t DMA_G_UDF                 : 1;
    __IO uint32_t DMA_S_CMA                 : 1;
    __IO uint32_t DMA_S_CMB                 : 1;
} stc_tim5_cr_field_t;

typedef struct
{
    __IO uint32_t FBRAKE                    : 1;
    __IO uint32_t FSAME                     : 1;
    __IO uint32_t BFILTS                    : 2;
    __IO uint32_t BFILTEN                   : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t SOFTBK                    : 1;
    __IO uint32_t SML0                      : 1;
    __IO uint32_t SML1                      : 1;
    __IO uint32_t SML2                      : 1;
    __IO uint32_t SMH0                      : 1;
    __IO uint32_t SMH1                      : 1;
    __IO uint32_t SMH2                      : 1;
} stc_tim5_aossr_field_t;

typedef struct
{
    __IO uint32_t FBRAKE                    : 1;
    __IO uint32_t FSAME                     : 1;
} stc_tim5_aoscl_field_t;

typedef struct
{
    __IO uint32_t EN0                       : 1;
    __IO uint32_t EN1                       : 1;
    __IO uint32_t EN2                       : 1;
    __IO uint32_t EN3                       : 1;
    __IO uint32_t EN4                       : 1;
    __IO uint32_t EN5                       : 1;
    __IO uint32_t EN6                       : 1;
    __IO uint32_t EN7                       : 1;
    __IO uint32_t EN8                       : 1;
    __IO uint32_t EN9                       : 1;
    __IO uint32_t EN10                      : 1;
    __IO uint32_t EN11                      : 1;
    __IO uint32_t EN12                      : 1;
    __IO uint32_t EN13                      : 1;
    __IO uint32_t EN14                      : 1;
    __IO uint32_t EN15                      : 1;
} stc_tim5_ptbks_field_t;

typedef struct
{
    __IO uint32_t TRIGAS                    : 4;
    __IO uint32_t TRIGBS                    : 4;
    __IO uint32_t TRIGCS                    : 4;
    __IO uint32_t TRIGDS                    : 4;
} stc_tim5_ttrig_field_t;

typedef struct
{
    __IO uint32_t IAOS0S                    : 4;
    __IO uint32_t IAOS1S                    : 4;
    __IO uint32_t IAOS2S                    : 4;
    __IO uint32_t IAOS3S                    : 4;
} stc_tim5_itrig_field_t;

typedef struct
{
    __IO uint32_t POL0                      : 1;
    __IO uint32_t POL1                      : 1;
    __IO uint32_t POL2                      : 1;
    __IO uint32_t POL3                      : 1;
    __IO uint32_t POL4                      : 1;
    __IO uint32_t POL5                      : 1;
    __IO uint32_t POL6                      : 1;
    __IO uint32_t POL7                      : 1;
    __IO uint32_t POL8                      : 1;
    __IO uint32_t POL9                      : 1;
    __IO uint32_t POL10                     : 1;
    __IO uint32_t POL11                     : 1;
    __IO uint32_t POL12                     : 1;
    __IO uint32_t POL13                     : 1;
    __IO uint32_t POL14                     : 1;
    __IO uint32_t POL15                     : 1;
} stc_tim5_ptbkp_field_t;

typedef struct
{
    __IO uint32_t SSTA0                     : 1;
    __IO uint32_t SSTA1                     : 1;
    __IO uint32_t SSTA2                     : 1;
} stc_tim5_sstar_field_t;

typedef struct
{
    __IO uint32_t SSTP0                     : 1;
    __IO uint32_t SSTP1                     : 1;
    __IO uint32_t SSTP2                     : 1;
} stc_tim5_sstpr_field_t;

typedef struct
{
    __IO uint32_t SCLR0                     : 1;
    __IO uint32_t SCLR1                     : 1;
    __IO uint32_t SCLR2                     : 1;
} stc_tim5_sclrr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_tim6_cnter_field_t;

typedef struct
{
    __IO uint32_t PERA                      :16;
} stc_tim6_perar_field_t;

typedef struct
{
    __IO uint32_t PERB                      :16;
} stc_tim6_perbr_field_t;

typedef struct
{
    __IO uint32_t GCMA                      :16;
} stc_tim6_gcmar_field_t;

typedef struct
{
    __IO uint32_t GCMB                      :16;
} stc_tim6_gcmbr_field_t;

typedef struct
{
    __IO uint32_t GCMC                      :16;
} stc_tim6_gcmcr_field_t;

typedef struct
{
    __IO uint32_t GCMD                      :16;
} stc_tim6_gcmdr_field_t;

typedef struct
{
    __IO uint32_t SCMA                      :16;
} stc_tim6_scmar_field_t;

typedef struct
{
    __IO uint32_t SCMB                      :16;
} stc_tim6_scmbr_field_t;

typedef struct
{
    __IO uint32_t DTUA                      :16;
} stc_tim6_dtuar_field_t;

typedef struct
{
    __IO uint32_t DTDA                      :16;
} stc_tim6_dtdar_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    __IO uint32_t MODE                      : 3;
    __IO uint32_t CKDIV                     : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t DIR                       : 1;
    uint32_t RESERVED9                      : 7;
    __IO uint32_t ZMSKREV                   : 1;
    __IO uint32_t ZMSKPOS                   : 1;
    __IO uint32_t ZMSK                      : 2;
} stc_tim6_gconr_field_t;

typedef struct
{
    __IO uint32_t INTENA                    : 1;
    __IO uint32_t INTENB                    : 1;
    __IO uint32_t INTENC                    : 1;
    __IO uint32_t INTEND                    : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t INTENOVF                  : 1;
    __IO uint32_t INTENUDF                  : 1;
    __IO uint32_t INTENDE                   : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t INTENSAML                 : 1;
    __IO uint32_t INTENSAMH                 : 1;
    __IO uint32_t INTENSAU                  : 1;
    __IO uint32_t INTENSAD                  : 1;
    __IO uint32_t INTENSBU                  : 1;
    __IO uint32_t INTENSBD                  : 1;
} stc_tim6_iconr_field_t;

typedef struct
{
    __IO uint32_t CAPCA                     : 1;
    __IO uint32_t STACA                     : 1;
    __IO uint32_t STPCA                     : 1;
    __IO uint32_t STASTPSA                  : 1;
    __IO uint32_t CMPCA                     : 2;
    __IO uint32_t PERCA                     : 2;
    __IO uint32_t OUTENA                    : 1;
    __IO uint32_t DISSELA                   : 2;
    __IO uint32_t DISVALA                   : 2;
    uint32_t RESERVED13                     : 3;
    __IO uint32_t CAPCB                     : 1;
    __IO uint32_t STACB                     : 1;
    __IO uint32_t STPCB                     : 1;
    __IO uint32_t STASTPSB                  : 1;
    __IO uint32_t CMPCB                     : 2;
    __IO uint32_t PERCB                     : 2;
    __IO uint32_t OUTENB                    : 1;
    __IO uint32_t DISSELB                   : 2;
    __IO uint32_t DISVALB                   : 2;
} stc_tim6_pconr_field_t;

typedef struct
{
    __IO uint32_t BENA                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t BENB                      : 1;
    uint32_t RESERVED3                      : 5;
    __IO uint32_t BENP                      : 1;
} stc_tim6_bconr_field_t;

typedef struct
{
    __IO uint32_t DTCEN                     : 1;
    uint32_t RESERVED1                      : 7;
    __IO uint32_t SEPA                      : 1;
} stc_tim6_dconr_field_t;

typedef struct
{
    __IO uint32_t NOFIENGA                  : 1;
    __IO uint32_t NOFICKGA                  : 2;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t NOFIENGB                  : 1;
    __IO uint32_t NOFICKGB                  : 2;
    uint32_t RESERVED7                      : 9;
    __IO uint32_t NOFIENTA                  : 1;
    __IO uint32_t NOFICKTA                  : 2;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t NOFIENTB                  : 1;
    __IO uint32_t NOFICKTB                  : 2;
    uint32_t RESERVED23                     : 1;
    __IO uint32_t NOFIENTC                  : 1;
    __IO uint32_t NOFICKTC                  : 2;
    uint32_t RESERVED27                     : 1;
    __IO uint32_t NOFIENTD                  : 1;
    __IO uint32_t NOFICKTD                  : 2;
} stc_tim6_fconr_field_t;

typedef struct
{
    __IO uint32_t GEPERIA                   : 1;
    __IO uint32_t GEPERIB                   : 1;
    __IO uint32_t GEPERIC                   : 1;
    __IO uint32_t GEPERID                   : 1;
    uint32_t RESERVED4                      :12;
    __IO uint32_t PCNTE                     : 2;
    __IO uint32_t PCNTS                     : 3;
} stc_tim6_vperr_field_t;

typedef struct
{
    __IO uint32_t CMAF                      : 1;
    __IO uint32_t CMBF                      : 1;
    __IO uint32_t CMCF                      : 1;
    __IO uint32_t CMDF                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFF                      : 1;
    __IO uint32_t UDFF                      : 1;
    __IO uint32_t DTEF                      : 1;
    __IO uint32_t CMSAUF                    : 1;
    __IO uint32_t CMSADF                    : 1;
    __IO uint32_t CMSBUF                    : 1;
    __IO uint32_t CMSBDF                    : 1;
    uint32_t RESERVED13                     : 8;
    __IO uint32_t VPERNUM                   : 3;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t DIRF                      : 1;
} stc_tim6_stflr_field_t;

typedef struct
{
    __IO uint32_t HSTA0                     : 1;
    __IO uint32_t HSTA1                     : 1;
    __IO uint32_t HSTA2                     : 1;
    __IO uint32_t HSTA3                     : 1;
    __IO uint32_t HSTA4                     : 1;
    __IO uint32_t HSTA5                     : 1;
    __IO uint32_t HSTA6                     : 1;
    __IO uint32_t HSTA7                     : 1;
    __IO uint32_t HSTA8                     : 1;
    __IO uint32_t HSTA9                     : 1;
    __IO uint32_t HSTA10                    : 1;
    __IO uint32_t HSTA11                    : 1;
    __IO uint32_t HSTA12                    : 1;
    __IO uint32_t HSTA13                    : 1;
    __IO uint32_t HSTA14                    : 1;
    __IO uint32_t HSTA15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STARTS                    : 1;
} stc_tim6_hstar_field_t;

typedef struct
{
    __IO uint32_t HSTP0                     : 1;
    __IO uint32_t HSTP1                     : 1;
    __IO uint32_t HSTP2                     : 1;
    __IO uint32_t HSTP3                     : 1;
    __IO uint32_t HSTP4                     : 1;
    __IO uint32_t HSTP5                     : 1;
    __IO uint32_t HSTP6                     : 1;
    __IO uint32_t HSTP7                     : 1;
    __IO uint32_t HSTP8                     : 1;
    __IO uint32_t HSTP9                     : 1;
    __IO uint32_t HSTP10                    : 1;
    __IO uint32_t HSTP11                    : 1;
    __IO uint32_t HSTP12                    : 1;
    __IO uint32_t HSTP13                    : 1;
    __IO uint32_t HSTP14                    : 1;
    __IO uint32_t HSTP15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STOPS                     : 1;
} stc_tim6_hstpr_field_t;

typedef struct
{
    __IO uint32_t HCEL0                     : 1;
    __IO uint32_t HCEL1                     : 1;
    __IO uint32_t HCEL2                     : 1;
    __IO uint32_t HCEL3                     : 1;
    __IO uint32_t HCEL4                     : 1;
    __IO uint32_t HCEL5                     : 1;
    __IO uint32_t HCEL6                     : 1;
    __IO uint32_t HCEL7                     : 1;
    __IO uint32_t HCEL8                     : 1;
    __IO uint32_t HCEL9                     : 1;
    __IO uint32_t HCEL10                    : 1;
    __IO uint32_t HCEL11                    : 1;
    __IO uint32_t HCEL12                    : 1;
    __IO uint32_t HCEL13                    : 1;
    __IO uint32_t HCEL14                    : 1;
    __IO uint32_t HCEL15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STARTS                    : 1;
} stc_tim6_hcelr_field_t;

typedef struct
{
    __IO uint32_t HCPA0                     : 1;
    __IO uint32_t HCPA1                     : 1;
    __IO uint32_t HCPA2                     : 1;
    __IO uint32_t HCPA3                     : 1;
    __IO uint32_t HCPA4                     : 1;
    __IO uint32_t HCPA5                     : 1;
    __IO uint32_t HCPA6                     : 1;
    __IO uint32_t HCPA7                     : 1;
    __IO uint32_t HCPA8                     : 1;
    __IO uint32_t HCPA9                     : 1;
    __IO uint32_t HCPA10                    : 1;
    __IO uint32_t HCPA11                    : 1;
    __IO uint32_t HCPA12                    : 1;
    __IO uint32_t HCPA13                    : 1;
    __IO uint32_t HCPA14                    : 1;
    __IO uint32_t HCPA15                    : 1;
} stc_tim6_hcpar_field_t;

typedef struct
{
    __IO uint32_t HCPB0                     : 1;
    __IO uint32_t HCPB1                     : 1;
    __IO uint32_t HCPB2                     : 1;
    __IO uint32_t HCPB3                     : 1;
    __IO uint32_t HCPB4                     : 1;
    __IO uint32_t HCPB5                     : 1;
    __IO uint32_t HCPB6                     : 1;
    __IO uint32_t HCPB7                     : 1;
    __IO uint32_t HCPB8                     : 1;
    __IO uint32_t HCPB9                     : 1;
    __IO uint32_t HCPB10                    : 1;
    __IO uint32_t HCPB11                    : 1;
    __IO uint32_t HCPB12                    : 1;
    __IO uint32_t HCPB13                    : 1;
    __IO uint32_t HCPB14                    : 1;
    __IO uint32_t HCPB15                    : 1;
} stc_tim6_hcpbr_field_t;

typedef struct
{
    __IO uint32_t HCUP0                     : 1;
    __IO uint32_t HCUP1                     : 1;
    __IO uint32_t HCUP2                     : 1;
    __IO uint32_t HCUP3                     : 1;
    __IO uint32_t HCUP4                     : 1;
    __IO uint32_t HCUP5                     : 1;
    __IO uint32_t HCUP6                     : 1;
    __IO uint32_t HCUP7                     : 1;
    __IO uint32_t HCUP8                     : 1;
    __IO uint32_t HCUP9                     : 1;
    __IO uint32_t HCUP10                    : 1;
    __IO uint32_t HCUP11                    : 1;
    __IO uint32_t HCUP12                    : 1;
    __IO uint32_t HCUP13                    : 1;
    __IO uint32_t HCUP14                    : 1;
    __IO uint32_t HCUP15                    : 1;
    __IO uint32_t HCUP16                    : 1;
    __IO uint32_t HCUP17                    : 1;
    __IO uint32_t HCUP18                    : 1;
    __IO uint32_t HCUP19                    : 1;
} stc_tim6_hcupr_field_t;

typedef struct
{
    __IO uint32_t HCDO0                     : 1;
    __IO uint32_t HCDO1                     : 1;
    __IO uint32_t HCDO2                     : 1;
    __IO uint32_t HCDO3                     : 1;
    __IO uint32_t HCDO4                     : 1;
    __IO uint32_t HCDO5                     : 1;
    __IO uint32_t HCDO6                     : 1;
    __IO uint32_t HCDO7                     : 1;
    __IO uint32_t HCDO8                     : 1;
    __IO uint32_t HCDO9                     : 1;
    __IO uint32_t HCDO10                    : 1;
    __IO uint32_t HCDO11                    : 1;
    __IO uint32_t HCDO12                    : 1;
    __IO uint32_t HCDO13                    : 1;
    __IO uint32_t HCDO14                    : 1;
    __IO uint32_t HCDO15                    : 1;
    __IO uint32_t HCDO16                    : 1;
    __IO uint32_t HCDO17                    : 1;
    __IO uint32_t HCDO18                    : 1;
    __IO uint32_t HCDO19                    : 1;
} stc_tim6_hcdor_field_t;

typedef struct
{
    __IO uint32_t CMAF                      : 1;
    __IO uint32_t CMBF                      : 1;
    __IO uint32_t CMCF                      : 1;
    __IO uint32_t CMDF                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFF                      : 1;
    __IO uint32_t UDFF                      : 1;
    __IO uint32_t DTEF                      : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t SAMLF                     : 1;
    __IO uint32_t SAMHF                     : 1;
} stc_tim6_ifr_field_t;

typedef struct
{
    __IO uint32_t CMAC                      : 1;
    __IO uint32_t CMBC                      : 1;
    __IO uint32_t CMCC                      : 1;
    __IO uint32_t CMDC                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFC                      : 1;
    __IO uint32_t UDFC                      : 1;
    __IO uint32_t DTEC                      : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t SAMLC                     : 1;
    __IO uint32_t SAMHC                     : 1;
} stc_tim6_iclr_field_t;

typedef struct
{
    __IO uint32_t CMAE                      : 1;
    __IO uint32_t CMBE                      : 1;
    __IO uint32_t CMCE                      : 1;
    __IO uint32_t CMDE                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFE                      : 1;
    __IO uint32_t UDFE                      : 1;
    __IO uint32_t DITENA                    : 1;
    __IO uint32_t DITENB                    : 1;
    __IO uint32_t DITENS                    : 1;
    __IO uint32_t CMSAE                     : 1;
    __IO uint32_t CMSBE                     : 1;
    __IO uint32_t DMA_G_CMA                 : 1;
    __IO uint32_t DMA_G_CMB                 : 1;
    __IO uint32_t DMA_G_CMC                 : 1;
    __IO uint32_t DMA_G_CMD                 : 1;
    uint32_t RESERVED17                     : 2;
    __IO uint32_t DMA_G_OVF                 : 1;
    __IO uint32_t DMA_G_UDF                 : 1;
    __IO uint32_t DMA_S_CMA                 : 1;
    __IO uint32_t DMA_S_CMB                 : 1;
} stc_tim6_cr_field_t;

typedef struct
{
    __IO uint32_t FBRAKE                    : 1;
    __IO uint32_t FSAME                     : 1;
    __IO uint32_t BFILTS                    : 2;
    __IO uint32_t BFILTEN                   : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t SOFTBK                    : 1;
    __IO uint32_t SML0                      : 1;
    __IO uint32_t SML1                      : 1;
    __IO uint32_t SML2                      : 1;
    __IO uint32_t SMH0                      : 1;
    __IO uint32_t SMH1                      : 1;
    __IO uint32_t SMH2                      : 1;
} stc_tim6_aossr_field_t;

typedef struct
{
    __IO uint32_t FBRAKE                    : 1;
    __IO uint32_t FSAME                     : 1;
} stc_tim6_aoscl_field_t;

typedef struct
{
    __IO uint32_t EN0                       : 1;
    __IO uint32_t EN1                       : 1;
    __IO uint32_t EN2                       : 1;
    __IO uint32_t EN3                       : 1;
    __IO uint32_t EN4                       : 1;
    __IO uint32_t EN5                       : 1;
    __IO uint32_t EN6                       : 1;
    __IO uint32_t EN7                       : 1;
    __IO uint32_t EN8                       : 1;
    __IO uint32_t EN9                       : 1;
    __IO uint32_t EN10                      : 1;
    __IO uint32_t EN11                      : 1;
    __IO uint32_t EN12                      : 1;
    __IO uint32_t EN13                      : 1;
    __IO uint32_t EN14                      : 1;
    __IO uint32_t EN15                      : 1;
} stc_tim6_ptbks_field_t;

typedef struct
{
    __IO uint32_t TRIGAS                    : 4;
    __IO uint32_t TRIGBS                    : 4;
    __IO uint32_t TRIGCS                    : 4;
    __IO uint32_t TRIGDS                    : 4;
} stc_tim6_ttrig_field_t;

typedef struct
{
    __IO uint32_t IAOS0S                    : 4;
    __IO uint32_t IAOS1S                    : 4;
    __IO uint32_t IAOS2S                    : 4;
    __IO uint32_t IAOS3S                    : 4;
} stc_tim6_itrig_field_t;

typedef struct
{
    __IO uint32_t POL0                      : 1;
    __IO uint32_t POL1                      : 1;
    __IO uint32_t POL2                      : 1;
    __IO uint32_t POL3                      : 1;
    __IO uint32_t POL4                      : 1;
    __IO uint32_t POL5                      : 1;
    __IO uint32_t POL6                      : 1;
    __IO uint32_t POL7                      : 1;
    __IO uint32_t POL8                      : 1;
    __IO uint32_t POL9                      : 1;
    __IO uint32_t POL10                     : 1;
    __IO uint32_t POL11                     : 1;
    __IO uint32_t POL12                     : 1;
    __IO uint32_t POL13                     : 1;
    __IO uint32_t POL14                     : 1;
    __IO uint32_t POL15                     : 1;
} stc_tim6_ptbkp_field_t;

typedef struct
{
    __IO uint32_t SSTA0                     : 1;
    __IO uint32_t SSTA1                     : 1;
    __IO uint32_t SSTA2                     : 1;
} stc_tim6_sstar_field_t;

typedef struct
{
    __IO uint32_t SSTP0                     : 1;
    __IO uint32_t SSTP1                     : 1;
    __IO uint32_t SSTP2                     : 1;
} stc_tim6_sstpr_field_t;

typedef struct
{
    __IO uint32_t SCLR0                     : 1;
    __IO uint32_t SCLR1                     : 1;
    __IO uint32_t SCLR2                     : 1;
} stc_tim6_sclrr_field_t;

typedef struct
{
    __IO uint32_t DATA                      : 8;
    __IO uint32_t DATA8                     : 1;
} stc_uart_sbuf_field_t;

typedef struct
{
    __IO uint32_t RCIE                      : 1;
    __IO uint32_t TCIE                      : 1;
    __IO uint32_t B8CONT                    : 2;
    __IO uint32_t REN                       : 1;
    __IO uint32_t ADRDET                    : 1;
    __IO uint32_t SM                        : 2;
    __IO uint32_t TXEIE                     : 1;
    __IO uint32_t OVER                      : 1;
    uint32_t RESERVED10                     : 3;
    __IO uint32_t PEIE                      : 1;
    __IO uint32_t STOPBIT                   : 2;
    __IO uint32_t DMARXEN                   : 1;
    __IO uint32_t DMATXEN                   : 1;
    __IO uint32_t RTSEN                     : 1;
    __IO uint32_t CTSEN                     : 1;
    __IO uint32_t CTSIE                     : 1;
    __IO uint32_t FEIE                      : 1;
} stc_uart_scon_field_t;

typedef struct
{
    __IO uint32_t SADDR                     : 8;
} stc_uart_saddr_field_t;

typedef struct
{
    __IO uint32_t SADEN                     : 8;
} stc_uart_saden_field_t;

typedef struct
{
    __IO uint32_t RC                        : 1;
    __IO uint32_t TC                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t TXE                       : 1;
    __IO uint32_t PE                        : 1;
    __IO uint32_t CTSIF                     : 1;
    __IO uint32_t CTS                       : 1;
} stc_uart_isr_field_t;

typedef struct
{
    __IO uint32_t RCCF                      : 1;
    __IO uint32_t TCCF                      : 1;
    __IO uint32_t FECF                      : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t PECF                      : 1;
    __IO uint32_t CTSIFCF                   : 1;
} stc_uart_icr_field_t;

typedef struct
{
    __IO uint32_t SCNT                      :16;
} stc_uart_scnt_field_t;

typedef struct
{
    __IO uint32_t DIV                       : 6;
    __IO uint32_t DIV_EN                    : 1;
    __IO uint32_t REF2P5_SEL                : 1;
    __IO uint32_t VC0_BIAS_SEL              : 2;
    __IO uint32_t VC0_HYS_SEL               : 2;
    __IO uint32_t VC1_BIAS_SEL              : 2;
    __IO uint32_t VC1_HYS_SEL               : 2;
} stc_vc_cr_field_t;

typedef struct
{
    __IO uint32_t P_SEL                     : 4;
    __IO uint32_t N_SEL                     : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t DEBOUNCE_TIME             : 3;
    __IO uint32_t FALLING                   : 1;
    __IO uint32_t RISING                    : 1;
    __IO uint32_t LEVEL                     : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t EN                        : 1;
} stc_vc_vc0_cr_field_t;

typedef struct
{
    __IO uint32_t P_SEL                     : 4;
    __IO uint32_t N_SEL                     : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t DEBOUNCE_TIME             : 3;
    __IO uint32_t FALLING                   : 1;
    __IO uint32_t RISING                    : 1;
    __IO uint32_t LEVEL                     : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t EN                        : 1;
} stc_vc_vc1_cr_field_t;

typedef struct
{
    __IO uint32_t INV_TIMER                 : 1;
    __IO uint32_t TIM0RCLR                  : 1;
    __IO uint32_t TIM1RCLR                  : 1;
    __IO uint32_t TIM2RCLR                  : 1;
    __IO uint32_t TIM3RCLR                  : 1;
    __IO uint32_t TIMBK                     : 1;
    uint32_t RESERVED6                      : 3;
    __IO uint32_t INV_TIM4                  : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t INV_TIM5                  : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t INV_TIM6                  : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t BRAKE                     : 1;
} stc_vc_vc0_out_cfg_field_t;

typedef struct
{
    __IO uint32_t INV_TIMER                 : 1;
    __IO uint32_t TIM0RCLR                  : 1;
    __IO uint32_t TIM1RCLR                  : 1;
    __IO uint32_t TIM2RCLR                  : 1;
    __IO uint32_t TIM3RCLR                  : 1;
    __IO uint32_t TIMBK                     : 1;
    uint32_t RESERVED6                      : 3;
    __IO uint32_t INV_TIM4                  : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t INV_TIM5                  : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t INV_TIM6                  : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t BRAKE                     : 1;
} stc_vc_vc1_out_cfg_field_t;

typedef struct
{
    __IO uint32_t VC0_INTF                  : 1;
    __IO uint32_t VC1_INTF                  : 1;
    __IO uint32_t VC0_FILTER                : 1;
    __IO uint32_t VC1_FILTER                : 1;
} stc_vc_ifr_field_t;

typedef struct
{
    __IO uint32_t RST                       : 8;
} stc_wdt_rst_field_t;

typedef struct
{
    __IO uint32_t WOV                       : 4;
    __IO uint32_t WDTR                      : 1;
    __IO uint32_t WINT_EN                   : 1;
    uint32_t RESERVED6                      : 1;
    __IO uint32_t WDINT                     : 1;
    __IO uint32_t WCNTL                     : 8;
} stc_wdt_con_field_t;


typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CR0;
        stc_adc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_adc_cr1_field_t CR1_f;
    };
    uint8_t RESERVED2[52];
    union
    {
        __IO uint32_t SQR0;
        stc_adc_sqr0_field_t SQR0_f;
    };
    union
    {
        __IO uint32_t SQR1;
        stc_adc_sqr1_field_t SQR1_f;
    };
    union
    {
        __IO uint32_t SQR2;
        stc_adc_sqr2_field_t SQR2_f;
    };
    union
    {
        __IO uint32_t JQR;
        stc_adc_jqr_field_t JQR_f;
    };
    union
    {
        __IO uint32_t SQRRESULT0;
        stc_adc_sqrresult0_field_t SQRRESULT0_f;
    };
    union
    {
        __IO uint32_t SQRRESULT1;
        stc_adc_sqrresult1_field_t SQRRESULT1_f;
    };
    union
    {
        __IO uint32_t SQRRESULT2;
        stc_adc_sqrresult2_field_t SQRRESULT2_f;
    };
    union
    {
        __IO uint32_t SQRRESULT3;
        stc_adc_sqrresult3_field_t SQRRESULT3_f;
    };
    union
    {
        __IO uint32_t SQRRESULT4;
        stc_adc_sqrresult4_field_t SQRRESULT4_f;
    };
    union
    {
        __IO uint32_t SQRRESULT5;
        stc_adc_sqrresult5_field_t SQRRESULT5_f;
    };
    union
    {
        __IO uint32_t SQRRESULT6;
        stc_adc_sqrresult6_field_t SQRRESULT6_f;
    };
    union
    {
        __IO uint32_t SQRRESULT7;
        stc_adc_sqrresult7_field_t SQRRESULT7_f;
    };
    union
    {
        __IO uint32_t SQRRESULT8;
        stc_adc_sqrresult8_field_t SQRRESULT8_f;
    };
    union
    {
        __IO uint32_t SQRRESULT9;
        stc_adc_sqrresult9_field_t SQRRESULT9_f;
    };
    union
    {
        __IO uint32_t SQRRESULT10;
        stc_adc_sqrresult10_field_t SQRRESULT10_f;
    };
    union
    {
        __IO uint32_t SQRRESULT11;
        stc_adc_sqrresult11_field_t SQRRESULT11_f;
    };
    union
    {
        __IO uint32_t SQRRESULT12;
        stc_adc_sqrresult12_field_t SQRRESULT12_f;
    };
    union
    {
        __IO uint32_t SQR_RESULT13;
        stc_adc_sqr_result13_field_t SQR_RESULT13_f;
    };
    union
    {
        __IO uint32_t SQRRESULT14;
        stc_adc_sqrresult14_field_t SQRRESULT14_f;
    };
    union
    {
        __IO uint32_t SQRRESULT15;
        stc_adc_sqrresult15_field_t SQRRESULT15_f;
    };
    union
    {
        __IO uint32_t JQRRESULT0;
        stc_adc_jqrresult0_field_t JQRRESULT0_f;
    };
    union
    {
        __IO uint32_t JQRRESULT1;
        stc_adc_jqrresult1_field_t JQRRESULT1_f;
    };
    union
    {
        __IO uint32_t JQRRESULT2;
        stc_adc_jqrresult2_field_t JQRRESULT2_f;
    };
    union
    {
        __IO uint32_t JQRRESULT3;
        stc_adc_jqrresult3_field_t JQRRESULT3_f;
    };
    union
    {
        __IO uint32_t RESULT;
        stc_adc_result_field_t RESULT_f;
    };
    union
    {
        __IO uint32_t RESULTACC;
        stc_adc_resultacc_field_t RESULTACC_f;
    };
    union
    {
        __IO uint32_t HT;
        stc_adc_ht_field_t HT_f;
    };
    union
    {
        __IO uint32_t LT;
        stc_adc_lt_field_t LT_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_adc_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_adc_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t EXTTRIGGER0;
        stc_adc_exttrigger0_field_t EXTTRIGGER0_f;
    };
    union
    {
        __IO uint32_t EXTTRIGGER1;
        stc_adc_exttrigger1_field_t EXTTRIGGER1_f;
    };
    union
    {
        __IO uint32_t SGLSTART;
        stc_adc_sglstart_field_t SGLSTART_f;
    };
    union
    {
        __IO uint32_t SQRSTART;
        stc_adc_sqrstart_field_t SQRSTART_f;
    };
    union
    {
        __IO uint32_t JQRSTART;
        stc_adc_jqrstart_field_t JQRSTART_f;
    };
}M0P_ADC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_aes_cr_field_t CR_f;
    };
    uint8_t RESERVED1[12];
    union
    {
        __IO uint32_t DATA0;
        stc_aes_data0_field_t DATA0_f;
    };
    union
    {
        __IO uint32_t DATA1;
        stc_aes_data1_field_t DATA1_f;
    };
    union
    {
        __IO uint32_t DATA2;
        stc_aes_data2_field_t DATA2_f;
    };
    union
    {
        __IO uint32_t DATA3;
        stc_aes_data3_field_t DATA3_f;
    };
    union
    {
        __IO uint32_t KEY0;
        stc_aes_key0_field_t KEY0_f;
    };
    union
    {
        __IO uint32_t KEY1;
        stc_aes_key1_field_t KEY1_f;
    };
    union
    {
        __IO uint32_t KEY2;
        stc_aes_key2_field_t KEY2_f;
    };
    union
    {
        __IO uint32_t KEY3;
        stc_aes_key3_field_t KEY3_f;
    };
}M0P_AES_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_bgr_cr_field_t CR_f;
    };
}M0P_BGR_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_clk_trim_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t REFCON;
        stc_clk_trim_refcon_field_t REFCON_f;
    };
    union
    {
        __IO uint32_t REFCNT;
        stc_clk_trim_refcnt_field_t REFCNT_f;
    };
    union
    {
        __IO uint32_t CALCNT;
        stc_clk_trim_calcnt_field_t CALCNT_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_clk_trim_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_clk_trim_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CALCON;
        stc_clk_trim_calcon_field_t CALCON_f;
    };
}M0P_CLK_TRIM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_crc_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t RESULT;
        stc_crc_result_field_t RESULT_f;
    };
    uint8_t RESERVED2[120];
    union
    {
        __IO uint32_t DATA;
        stc_crc_data_field_t DATA_f;
    };
}M0P_CRC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t DEBUG_ACTIVE;
        stc_debug_active_field_t DEBUG_ACTIVE_f;
    };
}M0P_DEBUG_ACTIVE_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CONF;
        stc_dmac_conf_field_t CONF_f;
    };
    uint8_t RESERVED1[12];
    union
    {
        __IO uint32_t CONFA0;
        stc_dmac_confa0_field_t CONFA0_f;
    };
    union
    {
        __IO uint32_t CONFB0;
        stc_dmac_confb0_field_t CONFB0_f;
    };
    union
    {
        __IO uint32_t SRCADR0;
        stc_dmac_srcadr0_field_t SRCADR0_f;
    };
    union
    {
        __IO uint32_t DSTADR0;
        stc_dmac_dstadr0_field_t DSTADR0_f;
    };
    union
    {
        __IO uint32_t CONFA1;
        stc_dmac_confa1_field_t CONFA1_f;
    };
    union
    {
        __IO uint32_t CONFB1;
        stc_dmac_confb1_field_t CONFB1_f;
    };
    union
    {
        __IO uint32_t SRCADR1;
        stc_dmac_srcadr1_field_t SRCADR1_f;
    };
    union
    {
        __IO uint32_t DSTADR1;
        stc_dmac_dstadr1_field_t DSTADR1_f;
    };
}M0P_DMAC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t TNVS;
        stc_flash_tnvs_field_t TNVS_f;
    };
    union
    {
        __IO uint32_t TPGS;
        stc_flash_tpgs_field_t TPGS_f;
    };
    union
    {
        __IO uint32_t TPROG;
        stc_flash_tprog_field_t TPROG_f;
    };
    union
    {
        __IO uint32_t TSERASE;
        stc_flash_tserase_field_t TSERASE_f;
    };
    union
    {
        __IO uint32_t TMERASE;
        stc_flash_tmerase_field_t TMERASE_f;
    };
    union
    {
        __IO uint32_t TPRCV;
        stc_flash_tprcv_field_t TPRCV_f;
    };
    union
    {
        __IO uint32_t TSRCV;
        stc_flash_tsrcv_field_t TSRCV_f;
    };
    union
    {
        __IO uint32_t TMRCV;
        stc_flash_tmrcv_field_t TMRCV_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_flash_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_flash_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_flash_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t BYPASS;
        stc_flash_bypass_field_t BYPASS_f;
    };
    union
    {
        __IO uint32_t SLOCK;
        stc_flash_slock_field_t SLOCK_f;
    };
}M0P_FLASH_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t PA00_SEL;
        stc_gpio_pa00_sel_field_t PA00_SEL_f;
    };
    union
    {
        __IO uint32_t PA01_SEL;
        stc_gpio_pa01_sel_field_t PA01_SEL_f;
    };
    union
    {
        __IO uint32_t PA02_SEL;
        stc_gpio_pa02_sel_field_t PA02_SEL_f;
    };
    union
    {
        __IO uint32_t PA03_SEL;
        stc_gpio_pa03_sel_field_t PA03_SEL_f;
    };
    union
    {
        __IO uint32_t PA04_SEL;
        stc_gpio_pa04_sel_field_t PA04_SEL_f;
    };
    union
    {
        __IO uint32_t PA05_SEL;
        stc_gpio_pa05_sel_field_t PA05_SEL_f;
    };
    union
    {
        __IO uint32_t PA06_SEL;
        stc_gpio_pa06_sel_field_t PA06_SEL_f;
    };
    union
    {
        __IO uint32_t PA07_SEL;
        stc_gpio_pa07_sel_field_t PA07_SEL_f;
    };
    union
    {
        __IO uint32_t PA08_SEL;
        stc_gpio_pa08_sel_field_t PA08_SEL_f;
    };
    union
    {
        __IO uint32_t PA09_SEL;
        stc_gpio_pa09_sel_field_t PA09_SEL_f;
    };
    union
    {
        __IO uint32_t PA10_SEL;
        stc_gpio_pa10_sel_field_t PA10_SEL_f;
    };
    union
    {
        __IO uint32_t PA11_SEL;
        stc_gpio_pa11_sel_field_t PA11_SEL_f;
    };
    union
    {
        __IO uint32_t PA12_SEL;
        stc_gpio_pa12_sel_field_t PA12_SEL_f;
    };
    union
    {
        __IO uint32_t PA13_SEL;
        stc_gpio_pa13_sel_field_t PA13_SEL_f;
    };
    union
    {
        __IO uint32_t PA14_SEL;
        stc_gpio_pa14_sel_field_t PA14_SEL_f;
    };
    union
    {
        __IO uint32_t PA15_SEL;
        stc_gpio_pa15_sel_field_t PA15_SEL_f;
    };
    union
    {
        __IO uint32_t PB00_SEL;
        stc_gpio_pb00_sel_field_t PB00_SEL_f;
    };
    union
    {
        __IO uint32_t PB01_SEL;
        stc_gpio_pb01_sel_field_t PB01_SEL_f;
    };
    union
    {
        __IO uint32_t PB02_SEL;
        stc_gpio_pb02_sel_field_t PB02_SEL_f;
    };
    union
    {
        __IO uint32_t PB03_SEL;
        stc_gpio_pb03_sel_field_t PB03_SEL_f;
    };
    union
    {
        __IO uint32_t PB04_SEL;
        stc_gpio_pb04_sel_field_t PB04_SEL_f;
    };
    union
    {
        __IO uint32_t PB05_SEL;
        stc_gpio_pb05_sel_field_t PB05_SEL_f;
    };
    union
    {
        __IO uint32_t PB06_SEL;
        stc_gpio_pb06_sel_field_t PB06_SEL_f;
    };
    union
    {
        __IO uint32_t PB07_SEL;
        stc_gpio_pb07_sel_field_t PB07_SEL_f;
    };
    union
    {
        __IO uint32_t PB08_SEL;
        stc_gpio_pb08_sel_field_t PB08_SEL_f;
    };
    union
    {
        __IO uint32_t PB09_SEL;
        stc_gpio_pb09_sel_field_t PB09_SEL_f;
    };
    union
    {
        __IO uint32_t PB10_SEL;
        stc_gpio_pb10_sel_field_t PB10_SEL_f;
    };
    union
    {
        __IO uint32_t PB11_SEL;
        stc_gpio_pb11_sel_field_t PB11_SEL_f;
    };
    union
    {
        __IO uint32_t PB12_SEL;
        stc_gpio_pb12_sel_field_t PB12_SEL_f;
    };
    union
    {
        __IO uint32_t PB13_SEL;
        stc_gpio_pb13_sel_field_t PB13_SEL_f;
    };
    union
    {
        __IO uint32_t PB14_SEL;
        stc_gpio_pb14_sel_field_t PB14_SEL_f;
    };
    union
    {
        __IO uint32_t PB15_SEL;
        stc_gpio_pb15_sel_field_t PB15_SEL_f;
    };
    union
    {
        __IO uint32_t PC00_SEL;
        stc_gpio_pc00_sel_field_t PC00_SEL_f;
    };
    union
    {
        __IO uint32_t PC01_SEL;
        stc_gpio_pc01_sel_field_t PC01_SEL_f;
    };
    union
    {
        __IO uint32_t PC02_SEL;
        stc_gpio_pc02_sel_field_t PC02_SEL_f;
    };
    union
    {
        __IO uint32_t PC03_SEL;
        stc_gpio_pc03_sel_field_t PC03_SEL_f;
    };
    union
    {
        __IO uint32_t PC04_SEL;
        stc_gpio_pc04_sel_field_t PC04_SEL_f;
    };
    union
    {
        __IO uint32_t PC05_SEL;
        stc_gpio_pc05_sel_field_t PC05_SEL_f;
    };
    union
    {
        __IO uint32_t PC06_SEL;
        stc_gpio_pc06_sel_field_t PC06_SEL_f;
    };
    union
    {
        __IO uint32_t PC07_SEL;
        stc_gpio_pc07_sel_field_t PC07_SEL_f;
    };
    union
    {
        __IO uint32_t PC08_SEL;
        stc_gpio_pc08_sel_field_t PC08_SEL_f;
    };
    union
    {
        __IO uint32_t PC09_SEL;
        stc_gpio_pc09_sel_field_t PC09_SEL_f;
    };
    union
    {
        __IO uint32_t PC10_SEL;
        stc_gpio_pc10_sel_field_t PC10_SEL_f;
    };
    union
    {
        __IO uint32_t PC11_SEL;
        stc_gpio_pc11_sel_field_t PC11_SEL_f;
    };
    union
    {
        __IO uint32_t PC12_SEL;
        stc_gpio_pc12_sel_field_t PC12_SEL_f;
    };
    union
    {
        __IO uint32_t PC13_SEL;
        stc_gpio_pc13_sel_field_t PC13_SEL_f;
    };
    union
    {
        __IO uint32_t PC14_SEL;
        stc_gpio_pc14_sel_field_t PC14_SEL_f;
    };
    union
    {
        __IO uint32_t PC15_SEL;
        stc_gpio_pc15_sel_field_t PC15_SEL_f;
    };
    union
    {
        __IO uint32_t PD00_SEL;
        stc_gpio_pd00_sel_field_t PD00_SEL_f;
    };
    union
    {
        __IO uint32_t PD01_SEL;
        stc_gpio_pd01_sel_field_t PD01_SEL_f;
    };
    union
    {
        __IO uint32_t PD02_SEL;
        stc_gpio_pd02_sel_field_t PD02_SEL_f;
    };
    union
    {
        __IO uint32_t PD03_SEL;
        stc_gpio_pd03_sel_field_t PD03_SEL_f;
    };
    union
    {
        __IO uint32_t PD04_SEL;
        stc_gpio_pd04_sel_field_t PD04_SEL_f;
    };
    union
    {
        __IO uint32_t PD05_SEL;
        stc_gpio_pd05_sel_field_t PD05_SEL_f;
    };
    union
    {
        __IO uint32_t PD06_SEL;
        stc_gpio_pd06_sel_field_t PD06_SEL_f;
    };
    union
    {
        __IO uint32_t PD07_SEL;
        stc_gpio_pd07_sel_field_t PD07_SEL_f;
    };
    uint8_t RESERVED56[32];
    union
    {
        __IO uint32_t PADIR;
        stc_gpio_padir_field_t PADIR_f;
    };
    union
    {
        __IO uint32_t PAIN;
        stc_gpio_pain_field_t PAIN_f;
    };
    union
    {
        __IO uint32_t PAOUT;
        stc_gpio_paout_field_t PAOUT_f;
    };
    union
    {
        __IO uint32_t PAADS;
        stc_gpio_paads_field_t PAADS_f;
    };
    union
    {
        __IO uint32_t PABSET;
        stc_gpio_pabset_field_t PABSET_f;
    };
    union
    {
        __IO uint32_t PABCLR;
        stc_gpio_pabclr_field_t PABCLR_f;
    };
    union
    {
        __IO uint32_t PABSETCLR;
        stc_gpio_pabsetclr_field_t PABSETCLR_f;
    };
    union
    {
        __IO uint32_t PADR;
        stc_gpio_padr_field_t PADR_f;
    };
    union
    {
        __IO uint32_t PAPU;
        stc_gpio_papu_field_t PAPU_f;
    };
    union
    {
        __IO uint32_t PAPD;
        stc_gpio_papd_field_t PAPD_f;
    };
    uint8_t RESERVED66[4];
    union
    {
        __IO uint32_t PAOD;
        stc_gpio_paod_field_t PAOD_f;
    };
    union
    {
        __IO uint32_t PAHIE;
        stc_gpio_pahie_field_t PAHIE_f;
    };
    union
    {
        __IO uint32_t PALIE;
        stc_gpio_palie_field_t PALIE_f;
    };
    union
    {
        __IO uint32_t PARIE;
        stc_gpio_parie_field_t PARIE_f;
    };
    union
    {
        __IO uint32_t PAFIE;
        stc_gpio_pafie_field_t PAFIE_f;
    };
    union
    {
        __IO uint32_t PBDIR;
        stc_gpio_pbdir_field_t PBDIR_f;
    };
    union
    {
        __IO uint32_t PBIN;
        stc_gpio_pbin_field_t PBIN_f;
    };
    union
    {
        __IO uint32_t PBOUT;
        stc_gpio_pbout_field_t PBOUT_f;
    };
    union
    {
        __IO uint32_t PBADS;
        stc_gpio_pbads_field_t PBADS_f;
    };
    union
    {
        __IO uint32_t PBBSET;
        stc_gpio_pbbset_field_t PBBSET_f;
    };
    union
    {
        __IO uint32_t PBBCLR;
        stc_gpio_pbbclr_field_t PBBCLR_f;
    };
    union
    {
        __IO uint32_t PBBSETCLR;
        stc_gpio_pbbsetclr_field_t PBBSETCLR_f;
    };
    union
    {
        __IO uint32_t PBDR;
        stc_gpio_pbdr_field_t PBDR_f;
    };
    union
    {
        __IO uint32_t PBPU;
        stc_gpio_pbpu_field_t PBPU_f;
    };
    union
    {
        __IO uint32_t PBPD;
        stc_gpio_pbpd_field_t PBPD_f;
    };
    uint8_t RESERVED81[4];
    union
    {
        __IO uint32_t PBOD;
        stc_gpio_pbod_field_t PBOD_f;
    };
    union
    {
        __IO uint32_t PBHIE;
        stc_gpio_pbhie_field_t PBHIE_f;
    };
    union
    {
        __IO uint32_t PBLIE;
        stc_gpio_pblie_field_t PBLIE_f;
    };
    union
    {
        __IO uint32_t PBRIE;
        stc_gpio_pbrie_field_t PBRIE_f;
    };
    union
    {
        __IO uint32_t PBFIE;
        stc_gpio_pbfie_field_t PBFIE_f;
    };
    union
    {
        __IO uint32_t PCDIR;
        stc_gpio_pcdir_field_t PCDIR_f;
    };
    union
    {
        __IO uint32_t PCIN;
        stc_gpio_pcin_field_t PCIN_f;
    };
    union
    {
        __IO uint32_t PCOUT;
        stc_gpio_pcout_field_t PCOUT_f;
    };
    union
    {
        __IO uint32_t PCADS;
        stc_gpio_pcads_field_t PCADS_f;
    };
    union
    {
        __IO uint32_t PCBSET;
        stc_gpio_pcbset_field_t PCBSET_f;
    };
    union
    {
        __IO uint32_t PCBCLR;
        stc_gpio_pcbclr_field_t PCBCLR_f;
    };
    union
    {
        __IO uint32_t PCBSETCLR;
        stc_gpio_pcbsetclr_field_t PCBSETCLR_f;
    };
    union
    {
        __IO uint32_t PCDR;
        stc_gpio_pcdr_field_t PCDR_f;
    };
    union
    {
        __IO uint32_t PCPU;
        stc_gpio_pcpu_field_t PCPU_f;
    };
    union
    {
        __IO uint32_t PCPD;
        stc_gpio_pcpd_field_t PCPD_f;
    };
    uint8_t RESERVED96[4];
    union
    {
        __IO uint32_t PCOD;
        stc_gpio_pcod_field_t PCOD_f;
    };
    union
    {
        __IO uint32_t PCHIE;
        stc_gpio_pchie_field_t PCHIE_f;
    };
    union
    {
        __IO uint32_t PCLIE;
        stc_gpio_pclie_field_t PCLIE_f;
    };
    union
    {
        __IO uint32_t PCRIE;
        stc_gpio_pcrie_field_t PCRIE_f;
    };
    union
    {
        __IO uint32_t PCFIE;
        stc_gpio_pcfie_field_t PCFIE_f;
    };
    union
    {
        __IO uint32_t PDDIR;
        stc_gpio_pddir_field_t PDDIR_f;
    };
    union
    {
        __IO uint32_t PDIN;
        stc_gpio_pdin_field_t PDIN_f;
    };
    union
    {
        __IO uint32_t PDOUT;
        stc_gpio_pdout_field_t PDOUT_f;
    };
    union
    {
        __IO uint32_t PDADS;
        stc_gpio_pdads_field_t PDADS_f;
    };
    union
    {
        __IO uint32_t PDBSET;
        stc_gpio_pdbset_field_t PDBSET_f;
    };
    union
    {
        __IO uint32_t PDBCLR;
        stc_gpio_pdbclr_field_t PDBCLR_f;
    };
    union
    {
        __IO uint32_t PDBSETCLR;
        stc_gpio_pdbsetclr_field_t PDBSETCLR_f;
    };
    union
    {
        __IO uint32_t PDDR;
        stc_gpio_pddr_field_t PDDR_f;
    };
    union
    {
        __IO uint32_t PDPU;
        stc_gpio_pdpu_field_t PDPU_f;
    };
    union
    {
        __IO uint32_t PDPD;
        stc_gpio_pdpd_field_t PDPD_f;
    };
    uint8_t RESERVED111[4];
    union
    {
        __IO uint32_t PDOD;
        stc_gpio_pdod_field_t PDOD_f;
    };
    union
    {
        __IO uint32_t PDHIE;
        stc_gpio_pdhie_field_t PDHIE_f;
    };
    union
    {
        __IO uint32_t PDLIE;
        stc_gpio_pdlie_field_t PDLIE_f;
    };
    union
    {
        __IO uint32_t PDRIE;
        stc_gpio_pdrie_field_t PDRIE_f;
    };
    union
    {
        __IO uint32_t PDFIE;
        stc_gpio_pdfie_field_t PDFIE_f;
    };
    union
    {
        __IO uint32_t PA_STAT;
        stc_gpio_pa_stat_field_t PA_STAT_f;
    };
    uint8_t RESERVED117[12];
    union
    {
        __IO uint32_t PA_ICLR;
        stc_gpio_pa_iclr_field_t PA_ICLR_f;
    };
    uint8_t RESERVED118[44];
    union
    {
        __IO uint32_t PB_STAT;
        stc_gpio_pb_stat_field_t PB_STAT_f;
    };
    uint8_t RESERVED119[12];
    union
    {
        __IO uint32_t PB_ICLR;
        stc_gpio_pb_iclr_field_t PB_ICLR_f;
    };
    uint8_t RESERVED120[44];
    union
    {
        __IO uint32_t PC_STAT;
        stc_gpio_pc_stat_field_t PC_STAT_f;
    };
    uint8_t RESERVED121[12];
    union
    {
        __IO uint32_t PC_ICLR;
        stc_gpio_pc_iclr_field_t PC_ICLR_f;
    };
    uint8_t RESERVED122[44];
    union
    {
        __IO uint32_t PD_STAT;
        stc_gpio_pd_stat_field_t PD_STAT_f;
    };
    uint8_t RESERVED123[12];
    union
    {
        __IO uint32_t PD_ICLR;
        stc_gpio_pd_iclr_field_t PD_ICLR_f;
    };
    uint8_t RESERVED124[44];
    union
    {
        __IO uint32_t CTRL0;
        stc_gpio_ctrl0_field_t CTRL0_f;
    };
    union
    {
        __IO uint32_t CTRL1;
        stc_gpio_ctrl1_field_t CTRL1_f;
    };
    union
    {
        __IO uint32_t CTRL2;
        stc_gpio_ctrl2_field_t CTRL2_f;
    };
    union
    {
        __IO uint32_t TIMGS;
        stc_gpio_timgs_field_t TIMGS_f;
    };
    union
    {
        __IO uint32_t TIMES;
        stc_gpio_times_field_t TIMES_f;
    };
    union
    {
        __IO uint32_t TIMCPS;
        stc_gpio_timcps_field_t TIMCPS_f;
    };
    union
    {
        __IO uint32_t PCAS;
        stc_gpio_pcas_field_t PCAS_f;
    };
}M0P_GPIO_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t DIVIDEND;
        stc_hdiv_dividend_field_t DIVIDEND_f;
    };
    union
    {
        __IO uint32_t DIVISOR;
        stc_hdiv_divisor_field_t DIVISOR_f;
    };
    union
    {
        __IO uint32_t QUOTIENT;
        stc_hdiv_quotient_field_t QUOTIENT_f;
    };
    union
    {
        __IO uint32_t REMAINDER;
        stc_hdiv_remainder_field_t REMAINDER_f;
    };
    union
    {
        __IO uint32_t SIGN;
        stc_hdiv_sign_field_t SIGN_f;
    };
    union
    {
        __IO uint32_t STAT;
        stc_hdiv_stat_field_t STAT_f;
    };
}M0P_HDIV_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t TMRUN;
        stc_i2c_tmrun_field_t TMRUN_f;
    };
    union
    {
        __IO uint32_t TM;
        stc_i2c_tm_field_t TM_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_i2c_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t DATA;
        stc_i2c_data_field_t DATA_f;
    };
    union
    {
        __IO uint32_t ADDR;
        stc_i2c_addr_field_t ADDR_f;
    };
    union
    {
        __IO uint32_t STAT;
        stc_i2c_stat_field_t STAT_f;
    };
}M0P_I2C_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_lcd_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_lcd_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t INTCLR;
        stc_lcd_intclr_field_t INTCLR_f;
    };
    union
    {
        __IO uint32_t POEN0;
        stc_lcd_poen0_field_t POEN0_f;
    };
    union
    {
        __IO uint32_t POEN1;
        stc_lcd_poen1_field_t POEN1_f;
    };
    uint8_t RESERVED5[44];
    union
    {
        __IO uint32_t RAM0;
        stc_lcd_ram0_field_t RAM0_f;
    };
    union
    {
        __IO uint32_t RAM1;
        stc_lcd_ram1_field_t RAM1_f;
    };
    union
    {
        __IO uint32_t RAM2;
        stc_lcd_ram2_field_t RAM2_f;
    };
    union
    {
        __IO uint32_t RAM3;
        stc_lcd_ram3_field_t RAM3_f;
    };
    union
    {
        __IO uint32_t RAM4;
        stc_lcd_ram4_field_t RAM4_f;
    };
    union
    {
        __IO uint32_t RAM5;
        stc_lcd_ram5_field_t RAM5_f;
    };
    union
    {
        __IO uint32_t RAM6;
        stc_lcd_ram6_field_t RAM6_f;
    };
    union
    {
        __IO uint32_t RAM7;
        stc_lcd_ram7_field_t RAM7_f;
    };
    union
    {
        __IO uint32_t RAM8;
        stc_lcd_ram8_field_t RAM8_f;
    };
    union
    {
        __IO uint32_t RAM9;
        stc_lcd_ram9_field_t RAM9_f;
    };
    union
    {
        __IO uint32_t RAMA;
        stc_lcd_rama_field_t RAMA_f;
    };
    union
    {
        __IO uint32_t RAMB;
        stc_lcd_ramb_field_t RAMB_f;
    };
    union
    {
        __IO uint32_t RAMC;
        stc_lcd_ramc_field_t RAMC_f;
    };
    union
    {
        __IO uint32_t RAMD;
        stc_lcd_ramd_field_t RAMD_f;
    };
    union
    {
        __IO uint32_t RAME;
        stc_lcd_rame_field_t RAME_f;
    };
    union
    {
        __IO uint32_t RAMF;
        stc_lcd_ramf_field_t RAMF_f;
    };
}M0P_LCD_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CNT;
        stc_lptimer_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t ARR;
        stc_lptimer_arr_field_t ARR_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t CR;
        stc_lptimer_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_lptimer_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_lptimer_iclr_field_t ICLR_f;
    };
}M0P_LPTIMER_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SBUF;
        stc_lpuart_sbuf_field_t SBUF_f;
    };
    union
    {
        __IO uint32_t SCON;
        stc_lpuart_scon_field_t SCON_f;
    };
    union
    {
        __IO uint32_t SADDR;
        stc_lpuart_saddr_field_t SADDR_f;
    };
    union
    {
        __IO uint32_t SADEN;
        stc_lpuart_saden_field_t SADEN_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_lpuart_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_lpuart_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t SCNT;
        stc_lpuart_scnt_field_t SCNT_f;
    };
}M0P_LPUART_TypeDef;

typedef struct
{
    uint8_t RESERVED0[40];
    union
    {
        __IO uint32_t CR;
        stc_lvd_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_lvd_ifr_field_t IFR_f;
    };
}M0P_LVD_TypeDef;

typedef struct
{
    uint8_t RESERVED0[48];
    union
    {
        __IO uint32_t CR0;
        stc_opa_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_opa_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;
        stc_opa_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint8_t CR;
        stc_opa_cr_field_t CR_f;
    };
}M0P_OPA_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CCON;
        stc_pca_ccon_field_t CCON_f;
    };
    union
    {
        __IO uint32_t CMOD;
        stc_pca_cmod_field_t CMOD_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_pca_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_pca_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CCAPM0;
        stc_pca_ccapm0_field_t CCAPM0_f;
    };
    union
    {
        __IO uint32_t CCAPM1;
        stc_pca_ccapm1_field_t CCAPM1_f;
    };
    union
    {
        __IO uint32_t CCAPM2;
        stc_pca_ccapm2_field_t CCAPM2_f;
    };
    union
    {
        __IO uint32_t CCAPM3;
        stc_pca_ccapm3_field_t CCAPM3_f;
    };
    union
    {
        __IO uint32_t CCAPM4;
        stc_pca_ccapm4_field_t CCAPM4_f;
    };
    union
    {
        __IO uint32_t CCAP0H;
        stc_pca_ccap0h_field_t CCAP0H_f;
    };
    union
    {
        __IO uint32_t CCAP0L;
        stc_pca_ccap0l_field_t CCAP0L_f;
    };
    union
    {
        __IO uint32_t CCAP1H;
        stc_pca_ccap1h_field_t CCAP1H_f;
    };
    union
    {
        __IO uint32_t CCAP1L;
        stc_pca_ccap1l_field_t CCAP1L_f;
    };
    union
    {
        __IO uint32_t CCAP2H;
        stc_pca_ccap2h_field_t CCAP2H_f;
    };
    union
    {
        __IO uint32_t CCAP2L;
        stc_pca_ccap2l_field_t CCAP2L_f;
    };
    union
    {
        __IO uint32_t CCAP3H;
        stc_pca_ccap3h_field_t CCAP3H_f;
    };
    union
    {
        __IO uint32_t CCAP3L;
        stc_pca_ccap3l_field_t CCAP3L_f;
    };
    union
    {
        __IO uint32_t CCAP4H;
        stc_pca_ccap4h_field_t CCAP4H_f;
    };
    union
    {
        __IO uint32_t CCAP4L;
        stc_pca_ccap4l_field_t CCAP4L_f;
    };
    union
    {
        __IO uint32_t CCAPO;
        stc_pca_ccapo_field_t CCAPO_f;
    };
    union
    {
        __IO uint32_t CCAP0;
        stc_pca_ccap0_field_t CCAP0_f;
    };
    union
    {
        __IO uint32_t CCAP1;
        stc_pca_ccap1_field_t CCAP1_f;
    };
    union
    {
        __IO uint32_t CCAP2;
        stc_pca_ccap2_field_t CCAP2_f;
    };
    union
    {
        __IO uint32_t CCAP3;
        stc_pca_ccap3_field_t CCAP3_f;
    };
    union
    {
        __IO uint32_t CCAP4;
        stc_pca_ccap4_field_t CCAP4_f;
    };
    union
    {
        __IO uint32_t CARR;
        stc_pca_carr_field_t CARR_f;
    };
    union
    {
        __IO uint32_t EPWM;
        stc_pca_epwm_field_t EPWM_f;
    };
}M0P_PCA_TypeDef;

typedef struct
{
    union
    {
        __IO uint8_t RUN;
        stc_pcnt_run_field_t RUN_f;
    };
    uint8_t RESERVED1[3];
    union
    {
        __IO uint8_t CR;
        stc_pcnt_cr_field_t CR_f;
    };
    uint8_t RESERVED2[3];
    union
    {
        __IO uint32_t FLT;
        stc_pcnt_flt_field_t FLT_f;
    };
    union
    {
        __IO uint32_t TOCR;
        stc_pcnt_tocr_field_t TOCR_f;
    };
    union
    {
        __IO uint8_t CMD;
        stc_pcnt_cmd_field_t CMD_f;
    };
    uint8_t RESERVED5[3];
    union
    {
        __IO uint8_t SR1;
        stc_pcnt_sr1_field_t SR1_f;
    };
    uint8_t RESERVED6[3];
    union
    {
        __IO uint16_t CNT;
        stc_pcnt_cnt_field_t CNT_f;
    };
    uint8_t RESERVED7[2];
    union
    {
        __IO uint16_t TOP;
        stc_pcnt_top_field_t TOP_f;
    };
    uint8_t RESERVED8[2];
    union
    {
        __IO uint16_t BUF;
        stc_pcnt_buf_field_t BUF_f;
    };
    uint8_t RESERVED9[2];
    union
    {
        __IO uint8_t IFR;
        stc_pcnt_ifr_field_t IFR_f;
    };
    uint8_t RESERVED10[3];
    union
    {
        __IO uint8_t ICR;
        stc_pcnt_icr_field_t ICR_f;
    };
    uint8_t RESERVED11[3];
    union
    {
        __IO uint8_t IEN;
        stc_pcnt_ien_field_t IEN_f;
    };
    uint8_t RESERVED12[3];
    union
    {
        __IO uint8_t SR2;
        stc_pcnt_sr2_field_t SR2_f;
    };
}M0P_PCNT_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_ram_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t ERRADDR;
        stc_ram_erraddr_field_t ERRADDR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_ram_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_ram_iclr_field_t ICLR_f;
    };
}M0P_RAM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t RESET_FLAG;
        stc_reset_flag_field_t RESET_FLAG_f;
    };
    uint8_t RESERVED1[8];
    union
    {
        __IO uint32_t PREI_RESET;
        stc_reset_prei_field_t PREI_RESET_f;
    };
}M0P_RESET_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_rng_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t MODE;
        stc_rng_mode_field_t MODE_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t DATA0;
        stc_rng_data0_field_t DATA0_f;
    };
    union
    {
        __IO uint32_t DATA1;
        stc_rng_data1_field_t DATA1_f;
    };
}M0P_RNG_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_rtc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_rtc_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t SEC;
        stc_rtc_sec_field_t SEC_f;
    };
    union
    {
        __IO uint32_t MIN;
        stc_rtc_min_field_t MIN_f;
    };
    union
    {
        __IO uint32_t HOUR;
        stc_rtc_hour_field_t HOUR_f;
    };
    union
    {
        __IO uint32_t WEEK;
        stc_rtc_week_field_t WEEK_f;
    };
    union
    {
        __IO uint32_t DAY;
        stc_rtc_day_field_t DAY_f;
    };
    union
    {
        __IO uint32_t MON;
        stc_rtc_mon_field_t MON_f;
    };
    union
    {
        __IO uint32_t YEAR;
        stc_rtc_year_field_t YEAR_f;
    };
    union
    {
        __IO uint32_t ALMMIN;
        stc_rtc_almmin_field_t ALMMIN_f;
    };
    union
    {
        __IO uint32_t ALMHOUR;
        stc_rtc_almhour_field_t ALMHOUR_f;
    };
    union
    {
        __IO uint32_t ALMWEEK;
        stc_rtc_almweek_field_t ALMWEEK_f;
    };
    union
    {
        __IO uint32_t COMPEN;
        stc_rtc_compen_field_t COMPEN_f;
    };
}M0P_RTC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_spi_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t SSN;
        stc_spi_ssn_field_t SSN_f;
    };
    union
    {
        __IO uint32_t STAT;
        stc_spi_stat_field_t STAT_f;
    };
    union
    {
        __IO uint32_t DATA;
        stc_spi_data_field_t DATA_f;
    };
    union
    {
        __IO uint32_t CR2;
        stc_spi_cr2_field_t CR2_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_spi_iclr_field_t ICLR_f;
    };
}M0P_SPI_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SYSCTRL0;
        stc_sysctrl_sysctrl0_field_t SYSCTRL0_f;
    };
    union
    {
        __IO uint32_t SYSCTRL1;
        stc_sysctrl_sysctrl1_field_t SYSCTRL1_f;
    };
    union
    {
        __IO uint32_t SYSCTRL2;
        stc_sysctrl_sysctrl2_field_t SYSCTRL2_f;
    };
    union
    {
        __IO uint32_t RCH_CR;
        stc_sysctrl_rch_cr_field_t RCH_CR_f;
    };
    union
    {
        __IO uint32_t XTH_CR;
        stc_sysctrl_xth_cr_field_t XTH_CR_f;
    };
    union
    {
        __IO uint32_t RCL_CR;
        stc_sysctrl_rcl_cr_field_t RCL_CR_f;
    };
    union
    {
        __IO uint32_t XTL_CR;
        stc_sysctrl_xtl_cr_field_t XTL_CR_f;
    };
    uint8_t RESERVED7[4];
    union
    {
        __IO uint32_t PERI_CLKEN;
        stc_sysctrl_peri_clken_field_t PERI_CLKEN_f;
    };
    uint8_t RESERVED8[24];
    union
    {
        __IO uint32_t PLL_CR;
        stc_sysctrl_pll_cr_field_t PLL_CR_f;
    };
}M0P_SYSCTRL_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim0_mode0_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim0_mode0_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_tim0_mode0_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t M0CR;
        stc_tim0_mode0_m0cr_field_t M0CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim0_mode0_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim0_mode0_iclr_field_t ICLR_f;
    };
    uint8_t RESERVED6[24];
    union
    {
        __IO uint32_t DTR;
        stc_tim0_mode0_dtr_field_t DTR_f;
    };
}M0P_TIM0_MODE0_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CNT;
        stc_tim0_mode1_cnt_field_t CNT_f;
    };
    uint8_t RESERVED1[4];
    union
    {
        __IO uint32_t M1CR;
        stc_tim0_mode1_m1cr_field_t M1CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim0_mode1_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim0_mode1_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim0_mode1_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim0_mode1_fltr_field_t FLTR_f;
    };
    uint8_t RESERVED6[4];
    union
    {
        __IO uint32_t CR0;
        stc_tim0_mode1_cr0_field_t CR0_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t CCR0A;
        stc_tim0_mode1_ccr0a_field_t CCR0A_f;
    };
}M0P_TIM0_MODE1_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim0_mode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim0_mode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_tim0_mode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim0_mode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim0_mode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim0_mode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim0_mode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_tim0_mode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_tim0_mode23_crch0_field_t CRCH0_f;
    };
    uint8_t RESERVED9[8];
    union
    {
        __IO uint32_t DTR;
        stc_tim0_mode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_tim0_mode23_rcr_field_t RCR_f;
    };
    union
    {
        __IO uint32_t ARRDM;
        stc_tim0_mode23_arrdm_field_t ARRDM_f;
    };
    union
    {
        __IO uint32_t CCR0A;
        stc_tim0_mode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_tim0_mode23_ccr0b_field_t CCR0B_f;
    };
}M0P_TIM0_MODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim1_mode0_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim1_mode0_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_tim1_mode0_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t M0CR;
        stc_tim1_mode0_m0cr_field_t M0CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim1_mode0_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim1_mode0_iclr_field_t ICLR_f;
    };
    uint8_t RESERVED6[24];
    union
    {
        __IO uint32_t DTR;
        stc_tim1_mode0_dtr_field_t DTR_f;
    };
}M0P_TIM1_MODE0_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CNT;
        stc_tim1_mode1_cnt_field_t CNT_f;
    };
    uint8_t RESERVED1[4];
    union
    {
        __IO uint32_t M1CR;
        stc_tim1_mode1_m1cr_field_t M1CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim1_mode1_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim1_mode1_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim1_mode1_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim1_mode1_fltr_field_t FLTR_f;
    };
    uint8_t RESERVED6[4];
    union
    {
        __IO uint32_t CR0;
        stc_tim1_mode1_cr0_field_t CR0_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t CCR0A;
        stc_tim1_mode1_ccr0a_field_t CCR0A_f;
    };
}M0P_TIM1_MODE1_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim1_mode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim1_mode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_tim1_mode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim1_mode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim1_mode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim1_mode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim1_mode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_tim1_mode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_tim1_mode23_crch0_field_t CRCH0_f;
    };
    uint8_t RESERVED9[8];
    union
    {
        __IO uint32_t DTR;
        stc_tim1_mode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_tim1_mode23_rcr_field_t RCR_f;
    };
    union
    {
        __IO uint32_t ARRDM;
        stc_tim1_mode23_arrdm_field_t ARRDM_f;
    };
    union
    {
        __IO uint32_t CCR0A;
        stc_tim1_mode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_tim1_mode23_ccr0b_field_t CCR0B_f;
    };
}M0P_TIM1_MODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim2_mode0_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim2_mode0_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_tim2_mode0_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t M0CR;
        stc_tim2_mode0_m0cr_field_t M0CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim2_mode0_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim2_mode0_iclr_field_t ICLR_f;
    };
    uint8_t RESERVED6[24];
    union
    {
        __IO uint32_t DTR;
        stc_tim2_mode0_dtr_field_t DTR_f;
    };
}M0P_TIM2_MODE0_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CNT;
        stc_tim2_mode1_cnt_field_t CNT_f;
    };
    uint8_t RESERVED1[4];
    union
    {
        __IO uint32_t M1CR;
        stc_tim2_mode1_m1cr_field_t M1CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim2_mode1_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim2_mode1_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim2_mode1_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim2_mode1_fltr_field_t FLTR_f;
    };
    uint8_t RESERVED6[4];
    union
    {
        __IO uint32_t CR0;
        stc_tim2_mode1_cr0_field_t CR0_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t CCR0A;
        stc_tim2_mode1_ccr0a_field_t CCR0A_f;
    };
}M0P_TIM2_MODE1_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim2_mode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim2_mode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_tim2_mode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim2_mode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim2_mode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim2_mode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim2_mode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_tim2_mode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_tim2_mode23_crch0_field_t CRCH0_f;
    };
    uint8_t RESERVED9[8];
    union
    {
        __IO uint32_t DTR;
        stc_tim2_mode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_tim2_mode23_rcr_field_t RCR_f;
    };
    union
    {
        __IO uint32_t ARRDM;
        stc_tim2_mode23_arrdm_field_t ARRDM_f;
    };
    union
    {
        __IO uint32_t CCR0A;
        stc_tim2_mode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_tim2_mode23_ccr0b_field_t CCR0B_f;
    };
}M0P_TIM2_MODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim3_mode0_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim3_mode0_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_tim3_mode0_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t M0CR;
        stc_tim3_mode0_m0cr_field_t M0CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim3_mode0_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim3_mode0_iclr_field_t ICLR_f;
    };
    uint8_t RESERVED6[24];
    union
    {
        __IO uint32_t DTR;
        stc_tim3_mode0_dtr_field_t DTR_f;
    };
}M0P_TIM3_MODE0_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CNT;
        stc_tim3_mode1_cnt_field_t CNT_f;
    };
    uint8_t RESERVED1[4];
    union
    {
        __IO uint32_t M1CR;
        stc_tim3_mode1_m1cr_field_t M1CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim3_mode1_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim3_mode1_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim3_mode1_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim3_mode1_fltr_field_t FLTR_f;
    };
    uint8_t RESERVED6[4];
    union
    {
        __IO uint32_t CR0;
        stc_tim3_mode1_cr0_field_t CR0_f;
    };
    uint8_t RESERVED7[20];
    union
    {
        __IO uint32_t CCR0A;
        stc_tim3_mode1_ccr0a_field_t CCR0A_f;
    };
}M0P_TIM3_MODE1_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_tim3_mode23_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_tim3_mode23_cnt_field_t CNT_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t M23CR;
        stc_tim3_mode23_m23cr_field_t M23CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_tim3_mode23_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim3_mode23_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t MSCR;
        stc_tim3_mode23_mscr_field_t MSCR_f;
    };
    union
    {
        __IO uint32_t FLTR;
        stc_tim3_mode23_fltr_field_t FLTR_f;
    };
    union
    {
        __IO uint32_t ADTR;
        stc_tim3_mode23_adtr_field_t ADTR_f;
    };
    union
    {
        __IO uint32_t CRCH0;
        stc_tim3_mode23_crch0_field_t CRCH0_f;
    };
    union
    {
        __IO uint32_t CRCH1;
        stc_tim3_mode23_crch1_field_t CRCH1_f;
    };
    union
    {
        __IO uint32_t CRCH2;
        stc_tim3_mode23_crch2_field_t CRCH2_f;
    };
    union
    {
        __IO uint32_t DTR;
        stc_tim3_mode23_dtr_field_t DTR_f;
    };
    union
    {
        __IO uint32_t RCR;
        stc_tim3_mode23_rcr_field_t RCR_f;
    };
    union
    {
        __IO uint32_t ARRDM;
        stc_tim3_mode23_arrdm_field_t ARRDM_f;
    };
    union
    {
        __IO uint32_t CCR0A;
        stc_tim3_mode23_ccr0a_field_t CCR0A_f;
    };
    union
    {
        __IO uint32_t CCR0B;
        stc_tim3_mode23_ccr0b_field_t CCR0B_f;
    };
    union
    {
        __IO uint32_t CCR1A;
        stc_tim3_mode23_ccr1a_field_t CCR1A_f;
    };
    union
    {
        __IO uint32_t CCR1B;
        stc_tim3_mode23_ccr1b_field_t CCR1B_f;
    };
    union
    {
        __IO uint32_t CCR2A;
        stc_tim3_mode23_ccr2a_field_t CCR2A_f;
    };
    union
    {
        __IO uint32_t CCR2B;
        stc_tim3_mode23_ccr2b_field_t CCR2B_f;
    };
}M0P_TIM3_MODE23_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CNTER;
        stc_tim4_cnter_field_t CNTER_f;
    };
    union
    {
        __IO uint32_t PERAR;
        stc_tim4_perar_field_t PERAR_f;
    };
    union
    {
        __IO uint32_t PERBR;
        stc_tim4_perbr_field_t PERBR_f;
    };
    uint8_t RESERVED3[4];
    union
    {
        __IO uint32_t GCMAR;
        stc_tim4_gcmar_field_t GCMAR_f;
    };
    union
    {
        __IO uint32_t GCMBR;
        stc_tim4_gcmbr_field_t GCMBR_f;
    };
    union
    {
        __IO uint32_t GCMCR;
        stc_tim4_gcmcr_field_t GCMCR_f;
    };
    union
    {
        __IO uint32_t GCMDR;
        stc_tim4_gcmdr_field_t GCMDR_f;
    };
    uint8_t RESERVED7[8];
    union
    {
        __IO uint32_t SCMAR;
        stc_tim4_scmar_field_t SCMAR_f;
    };
    union
    {
        __IO uint32_t SCMBR;
        stc_tim4_scmbr_field_t SCMBR_f;
    };
    uint8_t RESERVED9[16];
    union
    {
        __IO uint32_t DTUAR;
        stc_tim4_dtuar_field_t DTUAR_f;
    };
    union
    {
        __IO uint32_t DTDAR;
        stc_tim4_dtdar_field_t DTDAR_f;
    };
    uint8_t RESERVED11[8];
    union
    {
        __IO uint32_t GCONR;
        stc_tim4_gconr_field_t GCONR_f;
    };
    union
    {
        __IO uint32_t ICONR;
        stc_tim4_iconr_field_t ICONR_f;
    };
    union
    {
        __IO uint32_t PCONR;
        stc_tim4_pconr_field_t PCONR_f;
    };
    union
    {
        __IO uint32_t BCONR;
        stc_tim4_bconr_field_t BCONR_f;
    };
    union
    {
        __IO uint32_t DCONR;
        stc_tim4_dconr_field_t DCONR_f;
    };
    uint8_t RESERVED16[4];
    union
    {
        __IO uint32_t FCONR;
        stc_tim4_fconr_field_t FCONR_f;
    };
    union
    {
        __IO uint32_t VPERR;
        stc_tim4_vperr_field_t VPERR_f;
    };
    union
    {
        __IO uint32_t STFLR;
        stc_tim4_stflr_field_t STFLR_f;
    };
    union
    {
        __IO uint32_t HSTAR;
        stc_tim4_hstar_field_t HSTAR_f;
    };
    union
    {
        __IO uint32_t HSTPR;
        stc_tim4_hstpr_field_t HSTPR_f;
    };
    union
    {
        __IO uint32_t HCELR;
        stc_tim4_hcelr_field_t HCELR_f;
    };
    union
    {
        __IO uint32_t HCPAR;
        stc_tim4_hcpar_field_t HCPAR_f;
    };
    union
    {
        __IO uint32_t HCPBR;
        stc_tim4_hcpbr_field_t HCPBR_f;
    };
    union
    {
        __IO uint32_t HCUPR;
        stc_tim4_hcupr_field_t HCUPR_f;
    };
    union
    {
        __IO uint32_t HCDOR;
        stc_tim4_hcdor_field_t HCDOR_f;
    };
    uint8_t RESERVED26[112];
    union
    {
        __IO uint32_t IFR;
        stc_tim4_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim4_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_tim4_cr_field_t CR_f;
    };
    uint8_t RESERVED29[4];
    union
    {
        __IO uint32_t AOSSR;
        stc_tim4_aossr_field_t AOSSR_f;
    };
    union
    {
        __IO uint32_t AOSCL;
        stc_tim4_aoscl_field_t AOSCL_f;
    };
    union
    {
        __IO uint32_t PTBKS;
        stc_tim4_ptbks_field_t PTBKS_f;
    };
    union
    {
        __IO uint32_t TTRIG;
        stc_tim4_ttrig_field_t TTRIG_f;
    };
    union
    {
        __IO uint32_t ITRIG;
        stc_tim4_itrig_field_t ITRIG_f;
    };
    union
    {
        __IO uint32_t PTBKP;
        stc_tim4_ptbkp_field_t PTBKP_f;
    };
    uint8_t RESERVED35[716];
    union
    {
        __IO uint32_t SSTAR;
        stc_tim4_sstar_field_t SSTAR_f;
    };
    union
    {
        __IO uint32_t SSTPR;
        stc_tim4_sstpr_field_t SSTPR_f;
    };
    union
    {
        __IO uint32_t SCLRR;
        stc_tim4_sclrr_field_t SCLRR_f;
    };
}M0P_TIM4_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CNTER;
        stc_tim5_cnter_field_t CNTER_f;
    };
    union
    {
        __IO uint32_t PERAR;
        stc_tim5_perar_field_t PERAR_f;
    };
    union
    {
        __IO uint32_t PERBR;
        stc_tim5_perbr_field_t PERBR_f;
    };
    uint8_t RESERVED3[4];
    union
    {
        __IO uint32_t GCMAR;
        stc_tim5_gcmar_field_t GCMAR_f;
    };
    union
    {
        __IO uint32_t GCMBR;
        stc_tim5_gcmbr_field_t GCMBR_f;
    };
    union
    {
        __IO uint32_t GCMCR;
        stc_tim5_gcmcr_field_t GCMCR_f;
    };
    union
    {
        __IO uint32_t GCMDR;
        stc_tim5_gcmdr_field_t GCMDR_f;
    };
    uint8_t RESERVED7[8];
    union
    {
        __IO uint32_t SCMAR;
        stc_tim5_scmar_field_t SCMAR_f;
    };
    union
    {
        __IO uint32_t SCMBR;
        stc_tim5_scmbr_field_t SCMBR_f;
    };
    uint8_t RESERVED9[16];
    union
    {
        __IO uint32_t DTUAR;
        stc_tim5_dtuar_field_t DTUAR_f;
    };
    union
    {
        __IO uint32_t DTDAR;
        stc_tim5_dtdar_field_t DTDAR_f;
    };
    uint8_t RESERVED11[8];
    union
    {
        __IO uint32_t GCONR;
        stc_tim5_gconr_field_t GCONR_f;
    };
    union
    {
        __IO uint32_t ICONR;
        stc_tim5_iconr_field_t ICONR_f;
    };
    union
    {
        __IO uint32_t PCONR;
        stc_tim5_pconr_field_t PCONR_f;
    };
    union
    {
        __IO uint32_t BCONR;
        stc_tim5_bconr_field_t BCONR_f;
    };
    union
    {
        __IO uint32_t DCONR;
        stc_tim5_dconr_field_t DCONR_f;
    };
    uint8_t RESERVED16[4];
    union
    {
        __IO uint32_t FCONR;
        stc_tim5_fconr_field_t FCONR_f;
    };
    union
    {
        __IO uint32_t VPERR;
        stc_tim5_vperr_field_t VPERR_f;
    };
    union
    {
        __IO uint32_t STFLR;
        stc_tim5_stflr_field_t STFLR_f;
    };
    union
    {
        __IO uint32_t HSTAR;
        stc_tim5_hstar_field_t HSTAR_f;
    };
    union
    {
        __IO uint32_t HSTPR;
        stc_tim5_hstpr_field_t HSTPR_f;
    };
    union
    {
        __IO uint32_t HCELR;
        stc_tim5_hcelr_field_t HCELR_f;
    };
    union
    {
        __IO uint32_t HCPAR;
        stc_tim5_hcpar_field_t HCPAR_f;
    };
    union
    {
        __IO uint32_t HCPBR;
        stc_tim5_hcpbr_field_t HCPBR_f;
    };
    union
    {
        __IO uint32_t HCUPR;
        stc_tim5_hcupr_field_t HCUPR_f;
    };
    union
    {
        __IO uint32_t HCDOR;
        stc_tim5_hcdor_field_t HCDOR_f;
    };
    uint8_t RESERVED26[112];
    union
    {
        __IO uint32_t IFR;
        stc_tim5_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim5_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_tim5_cr_field_t CR_f;
    };
    uint8_t RESERVED29[4];
    union
    {
        __IO uint32_t AOSSR;
        stc_tim5_aossr_field_t AOSSR_f;
    };
    union
    {
        __IO uint32_t AOSCL;
        stc_tim5_aoscl_field_t AOSCL_f;
    };
    union
    {
        __IO uint32_t PTBKS;
        stc_tim5_ptbks_field_t PTBKS_f;
    };
    union
    {
        __IO uint32_t TTRIG;
        stc_tim5_ttrig_field_t TTRIG_f;
    };
    union
    {
        __IO uint32_t ITRIG;
        stc_tim5_itrig_field_t ITRIG_f;
    };
    union
    {
        __IO uint32_t PTBKP;
        stc_tim5_ptbkp_field_t PTBKP_f;
    };
    uint8_t RESERVED35[716];
    union
    {
        __IO uint32_t SSTAR;
        stc_tim5_sstar_field_t SSTAR_f;
    };
    union
    {
        __IO uint32_t SSTPR;
        stc_tim5_sstpr_field_t SSTPR_f;
    };
    union
    {
        __IO uint32_t SCLRR;
        stc_tim5_sclrr_field_t SCLRR_f;
    };
}M0P_TIM5_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CNTER;
        stc_tim6_cnter_field_t CNTER_f;
    };
    union
    {
        __IO uint32_t PERAR;
        stc_tim6_perar_field_t PERAR_f;
    };
    union
    {
        __IO uint32_t PERBR;
        stc_tim6_perbr_field_t PERBR_f;
    };
    uint8_t RESERVED3[4];
    union
    {
        __IO uint32_t GCMAR;
        stc_tim6_gcmar_field_t GCMAR_f;
    };
    union
    {
        __IO uint32_t GCMBR;
        stc_tim6_gcmbr_field_t GCMBR_f;
    };
    union
    {
        __IO uint32_t GCMCR;
        stc_tim6_gcmcr_field_t GCMCR_f;
    };
    union
    {
        __IO uint32_t GCMDR;
        stc_tim6_gcmdr_field_t GCMDR_f;
    };
    uint8_t RESERVED7[8];
    union
    {
        __IO uint32_t SCMAR;
        stc_tim6_scmar_field_t SCMAR_f;
    };
    union
    {
        __IO uint32_t SCMBR;
        stc_tim6_scmbr_field_t SCMBR_f;
    };
    uint8_t RESERVED9[16];
    union
    {
        __IO uint32_t DTUAR;
        stc_tim6_dtuar_field_t DTUAR_f;
    };
    union
    {
        __IO uint32_t DTDAR;
        stc_tim6_dtdar_field_t DTDAR_f;
    };
    uint8_t RESERVED11[8];
    union
    {
        __IO uint32_t GCONR;
        stc_tim6_gconr_field_t GCONR_f;
    };
    union
    {
        __IO uint32_t ICONR;
        stc_tim6_iconr_field_t ICONR_f;
    };
    union
    {
        __IO uint32_t PCONR;
        stc_tim6_pconr_field_t PCONR_f;
    };
    union
    {
        __IO uint32_t BCONR;
        stc_tim6_bconr_field_t BCONR_f;
    };
    union
    {
        __IO uint32_t DCONR;
        stc_tim6_dconr_field_t DCONR_f;
    };
    uint8_t RESERVED16[4];
    union
    {
        __IO uint32_t FCONR;
        stc_tim6_fconr_field_t FCONR_f;
    };
    union
    {
        __IO uint32_t VPERR;
        stc_tim6_vperr_field_t VPERR_f;
    };
    union
    {
        __IO uint32_t STFLR;
        stc_tim6_stflr_field_t STFLR_f;
    };
    union
    {
        __IO uint32_t HSTAR;
        stc_tim6_hstar_field_t HSTAR_f;
    };
    union
    {
        __IO uint32_t HSTPR;
        stc_tim6_hstpr_field_t HSTPR_f;
    };
    union
    {
        __IO uint32_t HCELR;
        stc_tim6_hcelr_field_t HCELR_f;
    };
    union
    {
        __IO uint32_t HCPAR;
        stc_tim6_hcpar_field_t HCPAR_f;
    };
    union
    {
        __IO uint32_t HCPBR;
        stc_tim6_hcpbr_field_t HCPBR_f;
    };
    union
    {
        __IO uint32_t HCUPR;
        stc_tim6_hcupr_field_t HCUPR_f;
    };
    union
    {
        __IO uint32_t HCDOR;
        stc_tim6_hcdor_field_t HCDOR_f;
    };
    uint8_t RESERVED26[112];
    union
    {
        __IO uint32_t IFR;
        stc_tim6_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_tim6_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_tim6_cr_field_t CR_f;
    };
    uint8_t RESERVED29[4];
    union
    {
        __IO uint32_t AOSSR;
        stc_tim6_aossr_field_t AOSSR_f;
    };
    union
    {
        __IO uint32_t AOSCL;
        stc_tim6_aoscl_field_t AOSCL_f;
    };
    union
    {
        __IO uint32_t PTBKS;
        stc_tim6_ptbks_field_t PTBKS_f;
    };
    union
    {
        __IO uint32_t TTRIG;
        stc_tim6_ttrig_field_t TTRIG_f;
    };
    union
    {
        __IO uint32_t ITRIG;
        stc_tim6_itrig_field_t ITRIG_f;
    };
    union
    {
        __IO uint32_t PTBKP;
        stc_tim6_ptbkp_field_t PTBKP_f;
    };
    uint8_t RESERVED35[716];
    union
    {
        __IO uint32_t SSTAR;
        stc_tim6_sstar_field_t SSTAR_f;
    };
    union
    {
        __IO uint32_t SSTPR;
        stc_tim6_sstpr_field_t SSTPR_f;
    };
    union
    {
        __IO uint32_t SCLRR;
        stc_tim6_sclrr_field_t SCLRR_f;
    };
}M0P_TIM6_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SBUF;
        stc_uart_sbuf_field_t SBUF_f;
    };
    union
    {
        __IO uint32_t SCON;
        stc_uart_scon_field_t SCON_f;
    };
    union
    {
        __IO uint32_t SADDR;
        stc_uart_saddr_field_t SADDR_f;
    };
    union
    {
        __IO uint32_t SADEN;
        stc_uart_saden_field_t SADEN_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_uart_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_uart_icr_field_t ICR_f;
    };
    union
    {
        __IO uint32_t SCNT;
        stc_uart_scnt_field_t SCNT_f;
    };
}M0P_UART_TypeDef;

typedef struct
{
    uint8_t RESERVED0[16];
    union
    {
        __IO uint32_t CR;
        stc_vc_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t VC0_CR;
        stc_vc_vc0_cr_field_t VC0_CR_f;
    };
    union
    {
        __IO uint32_t VC1_CR;
        stc_vc_vc1_cr_field_t VC1_CR_f;
    };
    union
    {
        __IO uint32_t VC0_OUT_CFG;
        stc_vc_vc0_out_cfg_field_t VC0_OUT_CFG_f;
    };
    union
    {
        __IO uint32_t VC1_OUT_CFG;
        stc_vc_vc1_out_cfg_field_t VC1_OUT_CFG_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_vc_ifr_field_t IFR_f;
    };
}M0P_VC_TypeDef;

typedef struct
{
    uint8_t RESERVED0[128];
    union
    {
        __IO uint32_t RST;
        stc_wdt_rst_field_t RST_f;
    };
    union
    {
        __IO uint32_t CON;
        stc_wdt_con_field_t CON_f;
    };
}M0P_WDT_TypeDef;



#define M0P_PERIPH_BASE                        (0x40000000UL)
#define M0P_ADC_BASE                           (M0P_PERIPH_BASE + 0x00002400UL)
#define M0P_AES_BASE                           (M0P_PERIPH_BASE + 0x00021400UL)
#define M0P_BGR_BASE                           (M0P_PERIPH_BASE + 0x00002400UL)
#define M0P_CLK_TRIM_BASE                      (M0P_PERIPH_BASE + 0x00001800UL)
#define M0P_CRC_BASE                           (M0P_PERIPH_BASE + 0x00020900UL)
#define M0P_DEBUG_ACTIVE_BASE                  (M0P_PERIPH_BASE + 0x00002438UL)
#define M0P_DMAC_BASE                          (M0P_PERIPH_BASE + 0x00021000UL)
#define M0P_FLASH_BASE                         (M0P_PERIPH_BASE + 0x00020000UL)
#define M0P_GPIO_BASE                          (M0P_PERIPH_BASE + 0x00020C00UL)
#define M0P_HDIV_BASE                          (M0P_PERIPH_BASE + 0x00021800UL)
#define M0P_I2C0_BASE                          (M0P_PERIPH_BASE + 0x00000400UL)
#define M0P_I2C1_BASE                          (M0P_PERIPH_BASE + 0x00004400UL)
#define M0P_LCD_BASE                           (M0P_PERIPH_BASE + 0x00005C00UL)
#define M0P_LPTIMER_BASE                       (M0P_PERIPH_BASE + 0x00000F00UL)
#define M0P_LPUART0_BASE                       (M0P_PERIPH_BASE + 0x00000200UL)
#define M0P_LPUART1_BASE                       (M0P_PERIPH_BASE + 0x00004000UL)
#define M0P_LVD_BASE                           (M0P_PERIPH_BASE + 0x00002400UL)
#define M0P_OPA_BASE                           (M0P_PERIPH_BASE + 0x00002400UL)
#define M0P_PCA_BASE                           (M0P_PERIPH_BASE + 0x00001000UL)
#define M0P_PCNT_BASE                          (M0P_PERIPH_BASE + 0x00005400UL)
#define M0P_RAM_BASE                           (M0P_PERIPH_BASE + 0x00020400UL)
#define M0P_RESET_BASE                         (M0P_PERIPH_BASE + 0x0000201CUL)
#define M0P_RNG_BASE                           (M0P_PERIPH_BASE + 0x00004C00UL)
#define M0P_RTC_BASE                           (M0P_PERIPH_BASE + 0x00001400UL)
#define M0P_SPI0_BASE                          (M0P_PERIPH_BASE + 0x00000800UL)
#define M0P_SPI1_BASE                          (M0P_PERIPH_BASE + 0x00004800UL)
#define M0P_SYSCTRL_BASE                       (M0P_PERIPH_BASE + 0x00002000UL)
#define M0P_TIM0_MODE0_BASE                    (M0P_PERIPH_BASE + 0x00000C00UL)
#define M0P_TIM0_MODE1_BASE                    (M0P_PERIPH_BASE + 0x00000C00UL)
#define M0P_TIM0_MODE23_BASE                   (M0P_PERIPH_BASE + 0x00000C00UL)
#define M0P_TIM1_MODE0_BASE                    (M0P_PERIPH_BASE + 0x00000D00UL)
#define M0P_TIM1_MODE1_BASE                    (M0P_PERIPH_BASE + 0x00000D00UL)
#define M0P_TIM1_MODE23_BASE                   (M0P_PERIPH_BASE + 0x00000D00UL)
#define M0P_TIM2_MODE0_BASE                    (M0P_PERIPH_BASE + 0x00000E00UL)
#define M0P_TIM2_MODE1_BASE                    (M0P_PERIPH_BASE + 0x00000E00UL)
#define M0P_TIM2_MODE23_BASE                   (M0P_PERIPH_BASE + 0x00000E00UL)
#define M0P_TIM3_MODE0_BASE                    (M0P_PERIPH_BASE + 0x00005800UL)
#define M0P_TIM3_MODE1_BASE                    (M0P_PERIPH_BASE + 0x00005800UL)
#define M0P_TIM3_MODE23_BASE                   (M0P_PERIPH_BASE + 0x00005800UL)
#define M0P_TIM4_BASE                          (M0P_PERIPH_BASE + 0x00003000UL)
#define M0P_TIM5_BASE                          (M0P_PERIPH_BASE + 0x00003400UL)
#define M0P_TIM6_BASE                          (M0P_PERIPH_BASE + 0x00003800UL)
#define M0P_UART0_BASE                         (M0P_PERIPH_BASE + 0x00000000UL)
#define M0P_UART1_BASE                         (M0P_PERIPH_BASE + 0x00000100UL)
#define M0P_VC_BASE                            (M0P_PERIPH_BASE + 0x00002400UL)
#define M0P_WDT_BASE                           (M0P_PERIPH_BASE + 0x00000F00UL)


#define M0P_ADC                                ((M0P_ADC_TypeDef *)0x40002400UL)
#define M0P_AES                                ((M0P_AES_TypeDef *)0x40021400UL)
#define M0P_BGR                                ((M0P_BGR_TypeDef *)0x40002400UL)
#define M0P_CLK_TRIM                           ((M0P_CLK_TRIM_TypeDef *)0x40001800UL)
#define M0P_CRC                                ((M0P_CRC_TypeDef *)0x40020900UL)
#define M0P_DEBUG_ACTIVE                       ((M0P_DEBUG_ACTIVE_TypeDef *)0x40002438UL)
#define M0P_DMAC                               ((M0P_DMAC_TypeDef *)0x40021000UL)
#define M0P_FLASH                              ((M0P_FLASH_TypeDef *)0x40020000UL)
#define M0P_GPIO                               ((M0P_GPIO_TypeDef *)0x40020C00UL)
#define M0P_HDIV                               ((M0P_HDIV_TypeDef *)0x40021800UL)
#define M0P_I2C0                               ((M0P_I2C_TypeDef *)0x40000400UL)
#define M0P_I2C1                               ((M0P_I2C_TypeDef *)0x40004400UL)
#define M0P_LCD                                ((M0P_LCD_TypeDef *)0x40005C00UL)
#define M0P_LPTIMER                            ((M0P_LPTIMER_TypeDef *)0x40000F00UL)
#define M0P_LPUART0                            ((M0P_LPUART_TypeDef *)0x40000200UL)
#define M0P_LPUART1                            ((M0P_LPUART_TypeDef *)0x40004000UL)
#define M0P_LVD                                ((M0P_LVD_TypeDef *)0x40002400UL)
#define M0P_OPA                                ((M0P_OPA_TypeDef *)0x40002400UL)
#define M0P_PCA                                ((M0P_PCA_TypeDef *)0x40001000UL)
#define M0P_PCNT                               ((M0P_PCNT_TypeDef *)0x40005400UL)
#define M0P_RAM                                ((M0P_RAM_TypeDef *)0x40020400UL)
#define M0P_RESET                              ((M0P_RESET_TypeDef *)0x4000201CUL)
#define M0P_RNG                                ((M0P_RNG_TypeDef *)0x40004C00UL)
#define M0P_RTC                                ((M0P_RTC_TypeDef *)0x40001400UL)
#define M0P_SPI0                               ((M0P_SPI_TypeDef *)0x40000800UL)
#define M0P_SPI1                               ((M0P_SPI_TypeDef *)0x40004800UL)
#define M0P_SYSCTRL                            ((M0P_SYSCTRL_TypeDef *)0x40002000UL)
#define M0P_TIM0_MODE0                         ((M0P_TIM0_MODE0_TypeDef *)0x40000C00UL)
#define M0P_TIM0_MODE1                         ((M0P_TIM0_MODE1_TypeDef *)0x40000C00UL)
#define M0P_TIM0_MODE23                        ((M0P_TIM0_MODE23_TypeDef *)0x40000C00UL)
#define M0P_TIM1_MODE0                         ((M0P_TIM1_MODE0_TypeDef *)0x40000D00UL)
#define M0P_TIM1_MODE1                         ((M0P_TIM1_MODE1_TypeDef *)0x40000D00UL)
#define M0P_TIM1_MODE23                        ((M0P_TIM1_MODE23_TypeDef *)0x40000D00UL)
#define M0P_TIM2_MODE0                         ((M0P_TIM2_MODE0_TypeDef *)0x40000E00UL)
#define M0P_TIM2_MODE1                         ((M0P_TIM2_MODE1_TypeDef *)0x40000E00UL)
#define M0P_TIM2_MODE23                        ((M0P_TIM2_MODE23_TypeDef *)0x40000E00UL)
#define M0P_TIM3_MODE0                         ((M0P_TIM3_MODE0_TypeDef *)0x40005800UL)
#define M0P_TIM3_MODE1                         ((M0P_TIM3_MODE1_TypeDef *)0x40005800UL)
#define M0P_TIM3_MODE23                        ((M0P_TIM3_MODE23_TypeDef *)0x40005800UL)
#define M0P_TIM4                               ((M0P_TIM4_TypeDef *)0x40003000UL)
#define M0P_TIM5                               ((M0P_TIM5_TypeDef *)0x40003400UL)
#define M0P_TIM6                               ((M0P_TIM6_TypeDef *)0x40003800UL)
#define M0P_UART0                              ((M0P_UART_TypeDef *)0x40000000UL)
#define M0P_UART1                              ((M0P_UART_TypeDef *)0x40000100UL)
#define M0P_VC                                 ((M0P_VC_TypeDef *)0x40002400UL)
#define M0P_WDT                                ((M0P_WDT_TypeDef *)0x40000F00UL)


#ifdef __cplusplus
}
#endif

#endif /* __HC32L136_H__ */

