/*******************************************************************
* *file       : ES8P508x.h
* *description: ES8P508x Device Head File
* *author     : Eastsoft MCU Software Team
* *version    : V0.01
* *data       : 7/11/2017
*
* *Copyright (C) 2017 Shanghai Eastsoft Microelectronics Co., Ltd.
*******************************************************************/
#ifndef __ES8P508x_H__
#define __ES8P508x_H__

#define __I volatile const /* defines 'read only' permissions */
#define __O volatile /* defines 'write only' permissions */
#define __IO volatile /* defines 'read / write' permissions */

#define __CM0_REV 0 /* Core Revision r0p0 */
#define __NVIC_PRIO_BITS 2 /* ES8P508x uses 2 Bits for the Priority Levels */
#define __Vendor_SysTickConfig 0 /* Set to 1 if different SysTick Config is used */

typedef enum IRQn
{
    /****** Cortex-M0 Processor Exceptions Numbers ******************************************************/
    RST_IRQn = -15,
    NonMaskableInt_IRQn = -14,
    HardFault_IRQn = -13,
    SVC_IRQn = -5,
    PendSV_IRQn = -2,
    SysTick_IRQn = -1,
    PINT0_IRQn = 0,
    PINT1_IRQn = 1,
    PINT2_IRQn = 2,
    PINT3_IRQn = 3,
    PINT4_IRQn = 4,
    PINT5_IRQn = 5,
    PINT6_IRQn = 6,
    PINT7_IRQn = 7,
    T16N0_IRQn = 8,
    T16N1_IRQn = 9,
    T16N2_IRQn = 10,
    T16N3_IRQn = 11,
    T32N0_IRQn = 12,
    Reserved0_IRQn = 13,
    IWDT_IRQn = 14,
    WWDT_IRQn = 15,
    CCM_IRQn = 16,
    PLK_IRQn = 17,
    LVD_IRQn = 18,
    KINT_IRQn = 19,
    RTC_IRQn = 20,
    ADC_IRQn = 21,
    Reserved1_IRQn = 22,
    AES_IRQn = 23,
    UART0_IRQn = 24,
    UART1_IRQn = 25,
    UART2_IRQn = 26,
    UART3_IRQn = 27,
    UART4_IRQn = 28,
    UART5_IRQn = 29,
    SPI0_IRQn = 30,
    I2C0_IRQn = 31,
} IRQn_Type;


#include "core_cm0.h"
#include <stdint.h>


/******************************************************************************/
/*                              设备特殊寄存器结构定䷿                       */
/******************************************************************************/

/*   允许匿名结构和匿名联县   */
#pragma anon_unions

typedef union
{
    struct
    {
        uint32_t PROT: 1;
        uint32_t RESERVED0: 31;
    };
    uint32_t Word;
} SCU_PROT_Typedef;

typedef union
{
    struct
    {
        uint32_t NMIEN: 1;
        uint32_t NMICS: 5;
        uint32_t RESERVED0: 26;
    };
    uint32_t Word;
} SCU_NMICON_Typedef;

typedef union
{
    struct
    {
        uint32_t PORF: 1;
        uint32_t PORRCF: 1;
        uint32_t PORRSTF: 1;
        uint32_t BORF: 1;
        uint32_t WWDTRSTF: 1;
        uint32_t IWDTRSTF: 1;
        uint32_t MRSTF: 1;
        uint32_t SOFT_RSTF: 1;
        uint32_t POR_LOST: 1;
        uint32_t CFG_RST: 1;
        uint32_t LOCKUP_RST: 1;
        uint32_t RESERVED0: 21;
    };
    uint32_t Word;
} SCU_PWRC_Typedef;

typedef union
{
    struct
    {
        uint32_t FLAG0: 1;
        uint32_t FLAG1: 1;
        uint32_t FLAG2: 1;
        uint32_t FLAG3: 1;
        uint32_t FLAG4: 1;
        uint32_t RESERVED0: 27;
    };
    uint32_t Word;
} SCU_FAULTFLAG_Typedef;

typedef union
{
    struct
    {
        uint32_t WAKEUPTIME: 12;
        uint32_t MOSC_EN: 1;
        uint32_t CLKFLT_EN: 1;
        uint32_t FLASHPW_PD: 1;
        uint32_t RESERVED0: 1;
        uint32_t LDOLP_VOSEL: 3;
        uint32_t LDOHP_SOFT: 1;
        uint32_t RESERVED1: 12;
    };
    uint32_t Word;
} SCU_WAKEUPTIME_Typedef;

typedef union
{
    struct
    {
        uint32_t PINST: 1;
        uint32_t RESERVED0: 31;
    };
    uint32_t Word;
} SCU_MRSTN_SOFT_Typedef;

typedef union
{
    struct
    {
        uint32_t T16N0HT: 1;
        uint32_t T16N1HT: 1;
        uint32_t T16N2HT: 1;
        uint32_t T16N3HT: 1;
        uint32_t RESERVED0: 4;
        uint32_t T32N0HT: 1;
        uint32_t RESERVED1: 7;
        uint32_t IWDTHT: 1;
        uint32_t WWDTHT: 1;
        uint32_t RESERVED2: 14;
    };
    uint32_t Word;
} SCU_DBGHALT_Typedef;

typedef union
{
    struct
    {
        uint32_t ACCT: 4;
        uint32_t HS: 1;
        uint32_t RESERVED0: 27;
    };
    uint32_t Word;
} SCU_FLASHWAIT_Typedef;

typedef union
{
    struct
    {
        uint32_t RESERVED0: 1;
        uint32_t BORV: 4;
        uint32_t BORFLT: 3;
        uint32_t RESERVED1: 24;
    };
    uint32_t Word;
} SCU_SOFTCFG_Typedef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t FLTEN: 1;
        uint32_t RESERVED0: 2;
        uint32_t VS: 4;
        uint32_t IF: 1;
        uint32_t IE: 1;
        uint32_t IFS: 3;
        uint32_t RESERVED1: 2;
        uint32_t LVDO: 1;
        uint32_t RESERVED2: 16;
    };
    uint32_t Word;
} SCU_LVDCON_Typedef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t RESERVED0: 3;
        uint32_t IE: 1;
        uint32_t IFS: 3;
        uint32_t IF: 1;
        uint32_t RESERVED1: 7;
        uint32_t FLAG: 1;
        uint32_t RESERVED2: 15;
    };
    uint32_t Word;
} SCU_CCM_Typedef;

typedef union
{
    struct
    {
        uint32_t IE: 1;
        uint32_t RESERVED0: 3;
        uint32_t LK_IFS: 3;
        uint32_t RESERVED1: 1;
        uint32_t IF: 1;
        uint32_t RESERVED2: 7;
        uint32_t LK_FLAG: 1;
        uint32_t RESERVED3: 15;
    };
    uint32_t Word;
} SCU_PLLLKCON_Typedef;

typedef union
{
    struct
    {
        uint32_t CLK_SEL: 2;
        uint32_t XTAL_LP: 1;
        uint32_t RESERVED0: 5;
        uint32_t PLL_MUX: 1;
        uint32_t RESERVED1: 3;
        uint32_t SYSCLK_DIV: 3;
        uint32_t RESERVED2: 1;
        uint32_t CLKFLT_BY: 8;
        uint32_t CLKOUT0_SEL: 2;
        uint32_t CLKOUT1_SEL: 2;
        uint32_t RESERVED3: 4;
    };
    uint32_t Word;
} SCU_SCLKEN0_Typedef;

typedef union
{
    struct
    {
        uint32_t XTAL_EN: 1;
        uint32_t HRC_EN: 1;
        uint32_t RESERVED0: 6;
        uint32_t PLL_REF_SEL: 3;
        uint32_t PLL_48M_SEL: 1;
        uint32_t PLL_EN: 1;
        uint32_t PLL_BYLOCK: 1;
        uint32_t RESERVED1: 2;
        uint32_t XTAL_RDY: 1;
        uint32_t HRC_RDY: 1;
        uint32_t PLL_RDY: 1;
        uint32_t RESERVED2: 13;
    };
    uint32_t Word;
} SCU_SCLKEN1_Typedef;

typedef union
{
    struct
    {
        uint32_t SCU_EN: 1;
        uint32_t GPIO_EN: 1;
        uint32_t IAP_EN: 1;
        uint32_t CRC_EN: 1;
        uint32_t ADC_EN: 1;
        uint32_t RTC_EN: 1;
        uint32_t RESERVED0: 1;
        uint32_t IWDT_EN: 1;
        uint32_t WWDT_EN: 1;
        uint32_t AES_EN: 1;
        uint32_t RESERVED1: 22;
    };
    uint32_t Word;
} SCU_PCLKEN0_Typedef;

typedef union
{
    struct
    {
        uint32_t T16N0_EN: 1;
        uint32_t T16N1_EN: 1;
        uint32_t T16N2_EN: 1;
        uint32_t T16N3_EN: 1;
        uint32_t RESERVED0: 4;
        uint32_t T32N0_EN: 1;
        uint32_t RESERVED1: 7;
        uint32_t UART0_EN: 1;
        uint32_t UART1_EN: 1;
        uint32_t UART2_EN: 1;
        uint32_t UART3_EN: 1;
        uint32_t UART4_EN: 1;
        uint32_t UART5_EN: 1;
        uint32_t RESERVED2: 2;
        uint32_t SPI0_EN: 1;
        uint32_t RESERVED3: 3;
        uint32_t I2C0_EN: 1;
        uint32_t RESERVED4: 3;
    };
    uint32_t Word;
} SCU_PCLKEN1_Typedef;

typedef union
{
    struct
    {
        uint32_t RESERVED0: 1;
        uint32_t GPIO_RST: 1;
        uint32_t IAP_RST: 1;
        uint32_t CRC_RST: 1;
        uint32_t ADC_RST: 1;
        uint32_t RTC_RST: 1;
        uint32_t RESERVED1: 1;
        uint32_t IWDT_RST: 1;
        uint32_t WWDT_RST: 1;
        uint32_t AES_RST: 1;
        uint32_t RESERVED2: 22;
    };
    uint32_t Word;
} SCU_PRSTEN0_Typedef;

typedef union
{
    struct
    {
        uint32_t T16N0_RST: 1;
        uint32_t T16N1_RST: 1;
        uint32_t T16N2_RST: 1;
        uint32_t T16N3_RST: 1;
        uint32_t RESERVED0: 4;
        uint32_t T32N0_RST: 1;
        uint32_t RESERVED1: 7;
        uint32_t UART0_RST: 1;
        uint32_t UART1_RST: 1;
        uint32_t UART2_RST: 1;
        uint32_t UART3_RST: 1;
        uint32_t UART4_RST: 1;
        uint32_t UART5_RST: 1;
        uint32_t RESERVED2: 2;
        uint32_t SPI0_RST: 1;
        uint32_t RESERVED3: 3;
        uint32_t I2C0_RST: 1;
        uint32_t RESERVED4: 3;
    };
    uint32_t Word;
} SCU_PRSTEN1_Typedef;

typedef union
{
    struct
    {
        uint32_t T16N0EN: 1;
        uint32_t T16N1EN: 1;
        uint32_t T16N2EN: 1;
        uint32_t T16N3EN: 1;
        uint32_t RESERVED0: 4;
        uint32_t T32N0EN: 1;
        uint32_t RESERVED1: 23;
    };
    uint32_t Word;
} SCU_TIMEREN_Typedef;

typedef union
{
    struct
    {
        uint32_t T16N0DIS: 1;
        uint32_t T16N1DIS: 1;
        uint32_t T16N2DIS: 1;
        uint32_t T16N3DIS: 1;
        uint32_t RESERVED0: 4;
        uint32_t T32N0DIS: 1;
        uint32_t RESERVED1: 23;
    };
    uint32_t Word;
} SCU_TIMERDIS_Typedef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t RESERVED0: 31;
    };
    uint32_t Word;
} SCU_TBLREMAPEN_Typedef;

typedef union
{
    struct
    {
        uint32_t TBLOFF: 32;
    };
    uint32_t Word;
} SCU_TBLOFF_Typedef;

typedef struct
{
    __IO SCU_PROT_Typedef PROT;
    __IO SCU_NMICON_Typedef NMICON;
    __IO SCU_PWRC_Typedef PWRC;
    __IO SCU_FAULTFLAG_Typedef FAULTFLAG;
    __IO SCU_WAKEUPTIME_Typedef WAKEUPTIME;
    __IO SCU_MRSTN_SOFT_Typedef MRSTN_SOFT;
    __IO SCU_DBGHALT_Typedef DBGHALT;
    uint32_t RESERVED0 ;
    __IO SCU_FLASHWAIT_Typedef FLASHWAIT;
    __IO SCU_SOFTCFG_Typedef SOFTCFG;
    __IO SCU_LVDCON_Typedef LVDCON;
    __IO SCU_CCM_Typedef CCM;
    __IO SCU_PLLLKCON_Typedef PLLLKCON;
    uint32_t RESERVED1[3] ;
    __IO SCU_SCLKEN0_Typedef SCLKEN0;
    __IO SCU_SCLKEN1_Typedef SCLKEN1;
    __IO SCU_PCLKEN0_Typedef PCLKEN0;
    __IO SCU_PCLKEN1_Typedef PCLKEN1;
    __IO SCU_PRSTEN0_Typedef PRSTEN0;
    __IO SCU_PRSTEN1_Typedef PRSTEN1;
    __O SCU_TIMEREN_Typedef TIMEREN;
    __IO SCU_TIMERDIS_Typedef TIMERDIS;
    __IO SCU_TBLREMAPEN_Typedef TBLREMAPEN;
    __IO SCU_TBLOFF_Typedef TBLOFF;
} SCU_TypeDef;

typedef union
{
    struct
    {
        uint32_t UL: 32;
    };
    uint32_t Word;
} CRC_UL_Typedef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t RST: 1;
        uint32_t HS: 1;
        uint32_t DS: 1;
        uint32_t REQ: 1;
        uint32_t ACK: 1;
        uint32_t RESERVED0: 2;
        uint32_t MOD: 2;
        uint32_t BYTE: 2;
        uint32_t REFIN: 1;
        uint32_t REFOUT: 1;
        uint32_t XOROUT: 1;
        uint32_t RESERVED1: 17;
    };
    uint32_t Word;
} CRC_CON_Typedef;

typedef union
{
    struct
    {
        uint32_t TRIG: 32;
    };
    uint32_t Word;
} CRC_TRIG_Typedef;

typedef union
{
    struct
    {
        uint32_t ADDR: 17;
        uint32_t RESERVED0: 3;
        uint32_t IFREN: 1;
        uint32_t RESERVED1: 11;
    };
    uint32_t Word;
} CRC_ADDR_Typedef;

typedef union
{
    struct
    {
        uint32_t CRC_SIZE: 15;
        uint32_t RESERVED0: 17;
    };
    uint32_t Word;
} CRC_SIZE_Typedef;

typedef union
{
    struct
    {
        uint32_t DI: 32;
    };
    uint32_t Word;
} CRC_DI_Typedef;

typedef union
{
    struct
    {
        uint32_t DO: 32;
    };
    uint32_t Word;
} CRC_DO_Typedef;

typedef union
{
    struct
    {
        uint32_t BUSY: 1;
        uint32_t RSTF: 1;
        uint32_t EMPTY_ERR: 1;
        uint32_t RESERVED0: 29;
    };
    uint32_t Word;
} CRC_STA_Typedef;

typedef union
{
    struct
    {
        uint32_t FADR: 15;
        uint32_t RESERVED0: 5;
        uint32_t IFREN: 1;
        uint32_t RESERVED1: 11;
    };
    uint32_t Word;
} CRC_FA_Typedef;

typedef struct
{
    __IO CRC_UL_Typedef UL;
    __IO CRC_CON_Typedef CON;
    __IO CRC_TRIG_Typedef TRIG;
    __IO CRC_ADDR_Typedef ADDR;
    __IO CRC_SIZE_Typedef SIZE;
    __IO CRC_DI_Typedef DI;
    __I CRC_DO_Typedef DO;
    __IO CRC_STA_Typedef STA;
    __I CRC_FA_Typedef FA;
} CRC_TypeDef;

typedef union
{
    struct
    {
        uint32_t PORT_0: 1;
        uint32_t PORT_1: 1;
        uint32_t PORT_2: 1;
        uint32_t PORT_3: 1;
        uint32_t PORT_4: 1;
        uint32_t PORT_5: 1;
        uint32_t PORT_6: 1;
        uint32_t PORT_7: 1;
        uint32_t PORT_8: 1;
        uint32_t PORT_9: 1;
        uint32_t PORT_10: 1;
        uint32_t PORT_11: 1;
        uint32_t PORT_12: 1;
        uint32_t PORT_13: 1;
        uint32_t PORT_14: 1;
        uint32_t PORT_15: 1;
        uint32_t PORT_16: 1;
        uint32_t PORT_17: 1;
        uint32_t PORT_18: 1;
        uint32_t PORT_19: 1;
        uint32_t PORT_20: 1;
        uint32_t PORT_21: 1;
        uint32_t PORT_22: 1;
        uint32_t PORT_23: 1;
        uint32_t PORT_24: 1;
        uint32_t PORT_25: 1;
        uint32_t PORT_26: 1;
        uint32_t PORT_27: 1;
        uint32_t PORT_28: 1;
        uint32_t PORT_29: 1;
        uint32_t PORT_30: 1;
        uint32_t PORT_31: 1;
    };
    uint32_t Word;
} GPIO_PAPORT_Typedef;

typedef union
{
    struct
    {
        uint32_t DATA_0: 1;
        uint32_t DATA_1: 1;
        uint32_t DATA_2: 1;
        uint32_t DATA_3: 1;
        uint32_t DATA_4: 1;
        uint32_t DATA_5: 1;
        uint32_t DATA_6: 1;
        uint32_t DATA_7: 1;
        uint32_t DATA_8: 1;
        uint32_t DATA_9: 1;
        uint32_t DATA_10: 1;
        uint32_t DATA_11: 1;
        uint32_t DATA_12: 1;
        uint32_t DATA_13: 1;
        uint32_t DATA_14: 1;
        uint32_t DATA_15: 1;
        uint32_t DATA_16: 1;
        uint32_t DATA_17: 1;
        uint32_t DATA_18: 1;
        uint32_t DATA_19: 1;
        uint32_t DATA_20: 1;
        uint32_t DATA_21: 1;
        uint32_t DATA_22: 1;
        uint32_t DATA_23: 1;
        uint32_t DATA_24: 1;
        uint32_t DATA_25: 1;
        uint32_t DATA_26: 1;
        uint32_t DATA_27: 1;
        uint32_t DATA_28: 1;
        uint32_t DATA_29: 1;
        uint32_t DATA_30: 1;
        uint32_t DATA_31: 1;
    };
    uint32_t Word;
} GPIO_PADATA_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PADATABSR_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PADATABCR_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PADATABRR_Typedef;

typedef union
{
    struct
    {
        uint32_t DIR_0: 1;
        uint32_t DIR_1: 1;
        uint32_t DIR_2: 1;
        uint32_t DIR_3: 1;
        uint32_t DIR_4: 1;
        uint32_t DIR_5: 1;
        uint32_t DIR_6: 1;
        uint32_t DIR_7: 1;
        uint32_t DIR_8: 1;
        uint32_t DIR_9: 1;
        uint32_t DIR_10: 1;
        uint32_t DIR_11: 1;
        uint32_t DIR_12: 1;
        uint32_t DIR_13: 1;
        uint32_t DIR_14: 1;
        uint32_t DIR_15: 1;
        uint32_t DIR_16: 1;
        uint32_t DIR_17: 1;
        uint32_t DIR_18: 1;
        uint32_t DIR_19: 1;
        uint32_t DIR_20: 1;
        uint32_t DIR_21: 1;
        uint32_t DIR_22: 1;
        uint32_t DIR_23: 1;
        uint32_t DIR_24: 1;
        uint32_t DIR_25: 1;
        uint32_t DIR_26: 1;
        uint32_t DIR_27: 1;
        uint32_t DIR_28: 1;
        uint32_t DIR_29: 1;
        uint32_t DIR_30: 1;
        uint32_t DIR_31: 1;
    };
    uint32_t Word;
} GPIO_PADIR_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PADIRBSR_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PADIRBCR_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PADIRBRR_Typedef;

typedef union
{
    struct
    {
        uint32_t PA0: 2;
        uint32_t RESERVED0: 2;
        uint32_t PA1: 2;
        uint32_t RESERVED1: 2;
        uint32_t PA2: 2;
        uint32_t RESERVED2: 2;
        uint32_t PA3: 2;
        uint32_t RESERVED3: 2;
        uint32_t PA4: 2;
        uint32_t RESERVED4: 2;
        uint32_t PA5: 2;
        uint32_t RESERVED5: 2;
        uint32_t PA6: 2;
        uint32_t RESERVED6: 2;
        uint32_t PA7: 2;
        uint32_t RESERVED7: 2;
    };
    uint32_t Word;
} GPIO_PAFUNC0_Typedef;

typedef union
{
    struct
    {
        uint32_t PA8: 2;
        uint32_t RESERVED0: 2;
        uint32_t PA9: 2;
        uint32_t RESERVED1: 2;
        uint32_t PA10: 2;
        uint32_t RESERVED2: 2;
        uint32_t PA11: 2;
        uint32_t RESERVED3: 2;
        uint32_t PA12: 2;
        uint32_t RESERVED4: 2;
        uint32_t PA13: 2;
        uint32_t RESERVED5: 2;
        uint32_t PA14: 2;
        uint32_t RESERVED6: 2;
        uint32_t PA15: 2;
        uint32_t RESERVED7: 2;
    };
    uint32_t Word;
} GPIO_PAFUNC1_Typedef;

typedef union
{
    struct
    {
        uint32_t PA16: 2;
        uint32_t RESERVED0: 2;
        uint32_t PA17: 2;
        uint32_t RESERVED1: 2;
        uint32_t PA18: 2;
        uint32_t RESERVED2: 2;
        uint32_t PA19: 2;
        uint32_t RESERVED3: 2;
        uint32_t PA20: 2;
        uint32_t RESERVED4: 2;
        uint32_t PA21: 2;
        uint32_t RESERVED5: 2;
        uint32_t PA22: 2;
        uint32_t RESERVED6: 2;
        uint32_t PA23: 2;
        uint32_t RESERVED7: 2;
    };
    uint32_t Word;
} GPIO_PAFUNC2_Typedef;

typedef union
{
    struct
    {
        uint32_t PA24: 2;
        uint32_t RESERVED0: 2;
        uint32_t PA25: 2;
        uint32_t RESERVED1: 2;
        uint32_t PA26: 2;
        uint32_t RESERVED2: 2;
        uint32_t PA27: 2;
        uint32_t RESERVED3: 2;
        uint32_t PA28: 2;
        uint32_t RESERVED4: 2;
        uint32_t PA29: 2;
        uint32_t RESERVED5: 2;
        uint32_t PA30: 2;
        uint32_t RESERVED6: 2;
        uint32_t PA31: 2;
        uint32_t RESERVED7: 2;
    };
    uint32_t Word;
} GPIO_PAFUNC3_Typedef;

typedef union
{
    struct
    {
        uint32_t INEB_0: 1;
        uint32_t INEB_1: 1;
        uint32_t INEB_2: 1;
        uint32_t INEB_3: 1;
        uint32_t INEB_4: 1;
        uint32_t INEB_5: 1;
        uint32_t INEB_6: 1;
        uint32_t INEB_7: 1;
        uint32_t INEB_8: 1;
        uint32_t INEB_9: 1;
        uint32_t INEB_10: 1;
        uint32_t INEB_11: 1;
        uint32_t INEB_12: 1;
        uint32_t INEB_13: 1;
        uint32_t INEB_14: 1;
        uint32_t INEB_15: 1;
        uint32_t INEB_16: 1;
        uint32_t INEB_17: 1;
        uint32_t INEB_18: 1;
        uint32_t INEB_19: 1;
        uint32_t INEB_20: 1;
        uint32_t INEB_21: 1;
        uint32_t INEB_22: 1;
        uint32_t INEB_23: 1;
        uint32_t INEB_24: 1;
        uint32_t INEB_25: 1;
        uint32_t INEB_26: 1;
        uint32_t INEB_27: 1;
        uint32_t INEB_28: 1;
        uint32_t INEB_29: 1;
        uint32_t INEB_30: 1;
        uint32_t INEB_31: 1;
    };
    uint32_t Word;
} GPIO_PAINEB_Typedef;

typedef union
{
    struct
    {
        uint32_t ODE_0: 1;
        uint32_t ODE_1: 1;
        uint32_t ODE_2: 1;
        uint32_t ODE_3: 1;
        uint32_t ODE_4: 1;
        uint32_t ODE_5: 1;
        uint32_t ODE_6: 1;
        uint32_t ODE_7: 1;
        uint32_t ODE_8: 1;
        uint32_t ODE_9: 1;
        uint32_t ODE_10: 1;
        uint32_t ODE_11: 1;
        uint32_t ODE_12: 1;
        uint32_t ODE_13: 1;
        uint32_t ODE_14: 1;
        uint32_t ODE_15: 1;
        uint32_t ODE_16: 1;
        uint32_t ODE_17: 1;
        uint32_t ODE_18: 1;
        uint32_t ODE_19: 1;
        uint32_t ODE_20: 1;
        uint32_t ODE_21: 1;
        uint32_t ODE_22: 1;
        uint32_t ODE_23: 1;
        uint32_t ODE_24: 1;
        uint32_t ODE_25: 1;
        uint32_t ODE_26: 1;
        uint32_t ODE_27: 1;
        uint32_t ODE_28: 1;
        uint32_t ODE_29: 1;
        uint32_t ODE_30: 1;
        uint32_t ODE_31: 1;
    };
    uint32_t Word;
} GPIO_PAODE_Typedef;

typedef union
{
    struct
    {
        uint32_t PUE_0: 1;
        uint32_t PUE_1: 1;
        uint32_t PUE_2: 1;
        uint32_t PUE_3: 1;
        uint32_t PUE_4: 1;
        uint32_t PUE_5: 1;
        uint32_t PUE_6: 1;
        uint32_t PUE_7: 1;
        uint32_t PUE_8: 1;
        uint32_t PUE_9: 1;
        uint32_t PUE_10: 1;
        uint32_t PUE_11: 1;
        uint32_t PUE_12: 1;
        uint32_t PUE_13: 1;
        uint32_t PUE_14: 1;
        uint32_t PUE_15: 1;
        uint32_t PUE_16: 1;
        uint32_t PUE_17: 1;
        uint32_t PUE_18: 1;
        uint32_t PUE_19: 1;
        uint32_t PUE_20: 1;
        uint32_t PUE_21: 1;
        uint32_t PUE_22: 1;
        uint32_t PUE_23: 1;
        uint32_t PUE_24: 1;
        uint32_t PUE_25: 1;
        uint32_t PUE_26: 1;
        uint32_t PUE_27: 1;
        uint32_t PUE_28: 1;
        uint32_t PUE_29: 1;
        uint32_t PUE_30: 1;
        uint32_t PUE_31: 1;
    };
    uint32_t Word;
} GPIO_PAPUE_Typedef;

typedef union
{
    struct
    {
        uint32_t PDE_0: 1;
        uint32_t PDE_1: 1;
        uint32_t PDE_2: 1;
        uint32_t PDE_3: 1;
        uint32_t PDE_4: 1;
        uint32_t PDE_5: 1;
        uint32_t PDE_6: 1;
        uint32_t PDE_7: 1;
        uint32_t PDE_8: 1;
        uint32_t PDE_9: 1;
        uint32_t PDE_10: 1;
        uint32_t PDE_11: 1;
        uint32_t PDE_12: 1;
        uint32_t PDE_13: 1;
        uint32_t PDE_14: 1;
        uint32_t PDE_15: 1;
        uint32_t PDE_16: 1;
        uint32_t PDE_17: 1;
        uint32_t PDE_18: 1;
        uint32_t PDE_19: 1;
        uint32_t PDE_20: 1;
        uint32_t PDE_21: 1;
        uint32_t PDE_22: 1;
        uint32_t PDE_23: 1;
        uint32_t PDE_24: 1;
        uint32_t PDE_25: 1;
        uint32_t PDE_26: 1;
        uint32_t PDE_27: 1;
        uint32_t PDE_28: 1;
        uint32_t PDE_29: 1;
        uint32_t PDE_30: 1;
        uint32_t PDE_31: 1;
    };
    uint32_t Word;
} GPIO_PAPDE_Typedef;

typedef union
{
    struct
    {
        uint32_t DS_0: 1;
        uint32_t DS_1: 1;
        uint32_t DS_2: 1;
        uint32_t DS_3: 1;
        uint32_t DS_4: 1;
        uint32_t DS_5: 1;
        uint32_t DS_6: 1;
        uint32_t DS_7: 1;
        uint32_t DS_8: 1;
        uint32_t DS_9: 1;
        uint32_t DS_10: 1;
        uint32_t DS_11: 1;
        uint32_t DS_12: 1;
        uint32_t DS_13: 1;
        uint32_t DS_14: 1;
        uint32_t DS_15: 1;
        uint32_t DS_16: 1;
        uint32_t DS_17: 1;
        uint32_t DS_18: 1;
        uint32_t DS_19: 1;
        uint32_t DS_20: 1;
        uint32_t DS_21: 1;
        uint32_t DS_22: 1;
        uint32_t DS_23: 1;
        uint32_t DS_24: 1;
        uint32_t DS_25: 1;
        uint32_t DS_26: 1;
        uint32_t DS_27: 1;
        uint32_t DS_28: 1;
        uint32_t DS_29: 1;
        uint32_t DS_30: 1;
        uint32_t DS_31: 1;
    };
    uint32_t Word;
} GPIO_PADS_Typedef;

typedef union
{
    struct
    {
        uint32_t PORT_0: 1;
        uint32_t PORT_1: 1;
        uint32_t PORT_2: 1;
        uint32_t PORT_3: 1;
        uint32_t PORT_4: 1;
        uint32_t PORT_5: 1;
        uint32_t PORT_6: 1;
        uint32_t PORT_7: 1;
        uint32_t PORT_8: 1;
        uint32_t PORT_9: 1;
        uint32_t PORT_10: 1;
        uint32_t PORT_11: 1;
        uint32_t PORT_12: 1;
        uint32_t PORT_13: 1;
        uint32_t RESERVED0: 18;
    };
    uint32_t Word;
} GPIO_PBPORT_Typedef;

typedef union
{
    struct
    {
        uint32_t DATA_0: 1;
        uint32_t DATA_1: 1;
        uint32_t DATA_2: 1;
        uint32_t DATA_3: 1;
        uint32_t DATA_4: 1;
        uint32_t DATA_5: 1;
        uint32_t DATA_6: 1;
        uint32_t DATA_7: 1;
        uint32_t DATA_8: 1;
        uint32_t DATA_9: 1;
        uint32_t DATA_10: 1;
        uint32_t DATA_11: 1;
        uint32_t DATA_12: 1;
        uint32_t DATA_13: 1;
        uint32_t RESERVED0: 18;
    };
    uint32_t Word;
} GPIO_PBDATA_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PBDATABSR_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PBDATABCR_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PBDATABRR_Typedef;

typedef union
{
    struct
    {
        uint32_t DIR_0: 1;
        uint32_t DIR_1: 1;
        uint32_t DIR_2: 1;
        uint32_t DIR_3: 1;
        uint32_t DIR_4: 1;
        uint32_t DIR_5: 1;
        uint32_t DIR_6: 1;
        uint32_t DIR_7: 1;
        uint32_t DIR_8: 1;
        uint32_t DIR_9: 1;
        uint32_t DIR_10: 1;
        uint32_t DIR_11: 1;
        uint32_t DIR_12: 1;
        uint32_t DIR_13: 1;
        uint32_t RESERVED0: 18;
    };
    uint32_t Word;
} GPIO_PBDIR_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PBDIRBSR_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PBDIRBCR_Typedef;

typedef union
{
    uint32_t Word;
} GPIO_PBDIRBRR_Typedef;

typedef union
{
    struct
    {
        uint32_t PB0: 2;
        uint32_t RESERVED0: 2;
        uint32_t PB1: 2;
        uint32_t RESERVED1: 2;
        uint32_t PB2: 2;
        uint32_t RESERVED2: 2;
        uint32_t PB3: 2;
        uint32_t RESERVED3: 2;
        uint32_t PB4: 2;
        uint32_t RESERVED4: 2;
        uint32_t PB5: 2;
        uint32_t RESERVED5: 2;
        uint32_t PB6: 2;
        uint32_t RESERVED6: 2;
        uint32_t PB7: 2;
        uint32_t RESERVED7: 2;
    };
    uint32_t Word;
} GPIO_PBFUNC0_Typedef;

typedef union
{
    struct
    {
        uint32_t PB8: 2;
        uint32_t RESERVED0: 2;
        uint32_t PB9: 2;
        uint32_t RESERVED1: 2;
        uint32_t PB10: 2;
        uint32_t RESERVED2: 2;
        uint32_t PB11: 2;
        uint32_t RESERVED3: 2;
        uint32_t PB12: 2;
        uint32_t RESERVED4: 2;
        uint32_t PB13: 2;
        uint32_t RESERVED5: 10;
    };
    uint32_t Word;
} GPIO_PBFUNC1_Typedef;

typedef union
{
    struct
    {
        uint32_t INEB_0: 1;
        uint32_t INEB_1: 1;
        uint32_t INEB_2: 1;
        uint32_t INEB_3: 1;
        uint32_t INEB_4: 1;
        uint32_t INEB_5: 1;
        uint32_t INEB_6: 1;
        uint32_t INEB_7: 1;
        uint32_t INEB_8: 1;
        uint32_t INEB_9: 1;
        uint32_t INEB_10: 1;
        uint32_t INEB_11: 1;
        uint32_t INEB_12: 1;
        uint32_t INEB_13: 1;
        uint32_t RESERVED0: 18;
    };
    uint32_t Word;
} GPIO_PBINEB_Typedef;

typedef union
{
    struct
    {
        uint32_t ODE_0: 1;
        uint32_t ODE_1: 1;
        uint32_t ODE_2: 1;
        uint32_t ODE_3: 1;
        uint32_t ODE_4: 1;
        uint32_t ODE_5: 1;
        uint32_t ODE_6: 1;
        uint32_t ODE_7: 1;
        uint32_t ODE_8: 1;
        uint32_t ODE_9: 1;
        uint32_t ODE_10: 1;
        uint32_t ODE_11: 1;
        uint32_t ODE_12: 1;
        uint32_t ODE_13: 1;
        uint32_t RESERVED0: 18;
    };
    uint32_t Word;
} GPIO_PBODE_Typedef;

typedef union
{
    struct
    {
        uint32_t PUEN_0: 1;
        uint32_t PUEN_1: 1;
        uint32_t PUEN_2: 1;
        uint32_t PUEN_3: 1;
        uint32_t PUEN_4: 1;
        uint32_t PUEN_5: 1;
        uint32_t PUEN_6: 1;
        uint32_t PUEN_7: 1;
        uint32_t PUEN_8: 1;
        uint32_t PUEN_9: 1;
        uint32_t PUEN_10: 1;
        uint32_t PUEN_11: 1;
        uint32_t PUEN_12: 1;
        uint32_t PUEN_13: 1;
        uint32_t RESERVED0: 18;
    };
    uint32_t Word;
} GPIO_PBPUE_Typedef;

typedef union
{
    struct
    {
        uint32_t PDEN_0: 1;
        uint32_t PDEN_1: 1;
        uint32_t PDEN_2: 1;
        uint32_t PDEN_3: 1;
        uint32_t PDEN_4: 1;
        uint32_t PDEN_5: 1;
        uint32_t PDEN_6: 1;
        uint32_t PDEN_7: 1;
        uint32_t PDEN_8: 1;
        uint32_t PDEN_9: 1;
        uint32_t PDEN_10: 1;
        uint32_t PDEN_11: 1;
        uint32_t PDEN_12: 1;
        uint32_t PDEN_13: 1;
        uint32_t RESERVED0: 18;
    };
    uint32_t Word;
} GPIO_PBPDE_Typedef;

typedef union
{
    struct
    {
        uint32_t DS_0: 1;
        uint32_t DS_1: 1;
        uint32_t DS_2: 1;
        uint32_t DS_3: 1;
        uint32_t DS_4: 1;
        uint32_t DS_5: 1;
        uint32_t DS_6: 1;
        uint32_t DS_7: 1;
        uint32_t DS_8: 1;
        uint32_t DS_9: 1;
        uint32_t DS_10: 1;
        uint32_t DS_11: 1;
        uint32_t DS_12: 1;
        uint32_t DS_13: 1;
        uint32_t RESERVED0: 18;
    };
    uint32_t Word;
} GPIO_PBDS_Typedef;

typedef union
{
    struct
    {
        uint32_t PINTIE: 8;
        uint32_t PMASK: 8;
        uint32_t RESERVED0: 16;
    };
    uint32_t Word;
} GPIO_PINTIE_Typedef;

typedef union
{
    struct
    {
        uint32_t PINTIF_0: 1;
        uint32_t PINTIF_1: 1;
        uint32_t PINTIF_2: 1;
        uint32_t PINTIF_3: 1;
        uint32_t PINTIF_4: 1;
        uint32_t PINTIF_5: 1;
        uint32_t PINTIF_6: 1;
        uint32_t PINTIF_7: 1;
        uint32_t RESERVED0: 24;
    };
    uint32_t Word;
} GPIO_PINTIF_Typedef;

typedef union
{
    struct
    {
        uint32_t PINT0SEL: 3;
        uint32_t RESERVED0: 1;
        uint32_t PINT1SEL: 3;
        uint32_t RESERVED1: 1;
        uint32_t PINT2SEL: 3;
        uint32_t RESERVED2: 1;
        uint32_t PINT3SEL: 3;
        uint32_t RESERVED3: 1;
        uint32_t PINT4SEL: 3;
        uint32_t RESERVED4: 1;
        uint32_t PINT5SEL: 3;
        uint32_t RESERVED5: 1;
        uint32_t PINT6SEL: 3;
        uint32_t RESERVED6: 1;
        uint32_t PINT7SEL: 3;
        uint32_t RESERVED7: 1;
    };
    uint32_t Word;
} GPIO_PINTSEL_Typedef;

typedef union
{
    struct
    {
        uint32_t PINT0CFG: 3;
        uint32_t RESERVED0: 1;
        uint32_t PINT1CFG: 3;
        uint32_t RESERVED1: 1;
        uint32_t PINT2CFG: 3;
        uint32_t RESERVED2: 1;
        uint32_t PINT3CFG: 3;
        uint32_t RESERVED3: 1;
        uint32_t PINT4CFG: 3;
        uint32_t RESERVED4: 1;
        uint32_t PINT5CFG: 3;
        uint32_t RESERVED5: 1;
        uint32_t PINT6CFG: 3;
        uint32_t RESERVED6: 1;
        uint32_t PINT7CFG: 3;
        uint32_t RESERVED7: 1;
    };
    uint32_t Word;
} GPIO_PINTCFG_Typedef;

typedef union
{
    struct
    {
        uint32_t KINTIE: 8;
        uint32_t KMASK: 8;
        uint32_t RESERVED0: 16;
    };
    uint32_t Word;
} GPIO_KINTIE_Typedef;

typedef union
{
    struct
    {
        uint32_t KINTIF_0: 1;
        uint32_t KINTIF_1: 1;
        uint32_t KINTIF_2: 1;
        uint32_t KINTIF_3: 1;
        uint32_t KINTIF_4: 1;
        uint32_t KINTIF_5: 1;
        uint32_t KINTIF_6: 1;
        uint32_t KINTIF_7: 1;
        uint32_t RESERVED0: 24;
    };
    uint32_t Word;
} GPIO_KINTIF_Typedef;

typedef union
{
    struct
    {
        uint32_t KINT0SEL: 3;
        uint32_t RESERVED0: 1;
        uint32_t KINT1SEL: 3;
        uint32_t RESERVED1: 1;
        uint32_t KINT2SEL: 3;
        uint32_t RESERVED2: 1;
        uint32_t KINT3SEL: 3;
        uint32_t RESERVED3: 1;
        uint32_t KINT4SEL: 3;
        uint32_t RESERVED4: 1;
        uint32_t KINT5SEL: 3;
        uint32_t RESERVED5: 1;
        uint32_t KINT6SEL: 3;
        uint32_t RESERVED6: 1;
        uint32_t KINT7SEL: 3;
        uint32_t RESERVED7: 1;
    };
    uint32_t Word;
} GPIO_KINTSEL_Typedef;

typedef union
{
    struct
    {
        uint32_t KINT0CFG: 3;
        uint32_t RESERVED0: 1;
        uint32_t KINT1CFG: 3;
        uint32_t RESERVED1: 1;
        uint32_t KINT2CFG: 3;
        uint32_t RESERVED2: 1;
        uint32_t KINT3CFG: 3;
        uint32_t RESERVED3: 1;
        uint32_t KINT4CFG: 3;
        uint32_t RESERVED4: 1;
        uint32_t KINT5CFG: 3;
        uint32_t RESERVED5: 1;
        uint32_t KINT6CFG: 3;
        uint32_t RESERVED6: 1;
        uint32_t KINT7CFG: 3;
        uint32_t RESERVED7: 1;
    };
    uint32_t Word;
} GPIO_KINTCFG_Typedef;

typedef union
{
    struct
    {
        uint32_t FLT_S_0: 1;
        uint32_t FLT_S_1: 1;
        uint32_t FLT_S_2: 1;
        uint32_t FLT_S_3: 1;
        uint32_t FLT_S_4: 1;
        uint32_t FLT_S_5: 1;
        uint32_t FLT_S_6: 1;
        uint32_t FLT_S_7: 1;
        uint32_t RESERVED0: 24;
    };
    uint32_t Word;
} GPIO_IOINTFLTS_Typedef;

typedef union
{
    struct
    {
        uint32_t FLT0_SEL: 4;
        uint32_t FLT1_SEL: 4;
        uint32_t FLT2_SEL: 4;
        uint32_t FLT3_SEL: 4;
        uint32_t RESERVED0: 16;
    };
    uint32_t Word;
} GPIO_TMRFLTSEL_Typedef;

typedef union
{
    struct
    {
        uint32_t TX0PS: 2;
        uint32_t RESERVED0: 2;
        uint32_t TX0PLV: 1;
        uint32_t TX0_S: 2;
        uint32_t RESERVED1: 1;
        uint32_t TX1PS: 2;
        uint32_t RESERVED2: 2;
        uint32_t TX1PLV: 1;
        uint32_t TX1_S: 2;
        uint32_t RESERVED3: 1;
        uint32_t TX2PS: 2;
        uint32_t RESERVED4: 2;
        uint32_t TX2PLV: 1;
        uint32_t TX2_S: 2;
        uint32_t RESERVED5: 1;
        uint32_t TX3PS: 2;
        uint32_t RESERVED6: 2;
        uint32_t TX3PLV: 1;
        uint32_t TX3_S: 2;
        uint32_t RESERVED7: 1;
    };
    uint32_t Word;
} GPIO_TXPWM_Typedef;

typedef union
{
    struct
    {
        uint32_t BUZEN: 1;
        uint32_t RESERVED0: 7;
        uint32_t BUZ_LOAD: 20;
        uint32_t RESERVED1: 4;
    };
    uint32_t Word;
} GPIO_BUZC_Typedef;

typedef struct
{
    __I GPIO_PAPORT_Typedef PAPORT;
    uint32_t RESERVED0[3] ;
    __IO GPIO_PADATA_Typedef PADATA;
    __O GPIO_PADATABSR_Typedef PADATABSR;
    __O GPIO_PADATABCR_Typedef PADATABCR;
    __O GPIO_PADATABRR_Typedef PADATABRR;
    __IO GPIO_PADIR_Typedef PADIR;
    __O GPIO_PADIRBSR_Typedef PADIRBSR;
    __O GPIO_PADIRBCR_Typedef PADIRBCR;
    __O GPIO_PADIRBRR_Typedef PADIRBRR;
    __IO GPIO_PAFUNC0_Typedef PAFUNC0;
    __IO GPIO_PAFUNC1_Typedef PAFUNC1;
    __IO GPIO_PAFUNC2_Typedef PAFUNC2;
    __IO GPIO_PAFUNC3_Typedef PAFUNC3;
    __IO GPIO_PAINEB_Typedef PAINEB;
    __IO GPIO_PAODE_Typedef PAODE;
    __IO GPIO_PAPUE_Typedef PAPUE;
    __IO GPIO_PAPDE_Typedef PAPDE;
    __IO GPIO_PADS_Typedef PADS;
    uint32_t RESERVED1[11] ;
    __I GPIO_PBPORT_Typedef PBPORT;
    uint32_t RESERVED2[3] ;
    __IO GPIO_PBDATA_Typedef PBDATA;
    __O GPIO_PBDATABSR_Typedef PBDATABSR;
    __O GPIO_PBDATABCR_Typedef PBDATABCR;
    __O GPIO_PBDATABRR_Typedef PBDATABRR;
    __IO GPIO_PBDIR_Typedef PBDIR;
    __O GPIO_PBDIRBSR_Typedef PBDIRBSR;
    __O GPIO_PBDIRBCR_Typedef PBDIRBCR;
    __O GPIO_PBDIRBRR_Typedef PBDIRBRR;
    __IO GPIO_PBFUNC0_Typedef PBFUNC0;
    __IO GPIO_PBFUNC1_Typedef PBFUNC1;
    uint32_t RESERVED3[2] ;
    __IO GPIO_PBINEB_Typedef PBINEB;
    __IO GPIO_PBODE_Typedef PBODE;
    __IO GPIO_PBPUE_Typedef PBPUE;
    __IO GPIO_PBPDE_Typedef PBPDE;
    __IO GPIO_PBDS_Typedef PBDS;
    uint32_t RESERVED4[139] ;
    __IO GPIO_PINTIE_Typedef PINTIE;
    __IO GPIO_PINTIF_Typedef PINTIF;
    __IO GPIO_PINTSEL_Typedef PINTSEL;
    __IO GPIO_PINTCFG_Typedef PINTCFG;
    __IO GPIO_KINTIE_Typedef KINTIE;
    __IO GPIO_KINTIF_Typedef KINTIF;
    __IO GPIO_KINTSEL_Typedef KINTSEL;
    __IO GPIO_KINTCFG_Typedef KINTCFG;
    uint32_t RESERVED5[4] ;
    __IO GPIO_IOINTFLTS_Typedef IOINTFLTS;
    uint32_t RESERVED6[3] ;
    __IO GPIO_TMRFLTSEL_Typedef TMRFLTSEL;
    uint32_t RESERVED7[15] ;
    __IO GPIO_TXPWM_Typedef TXPWM;
    uint32_t RESERVED8[3] ;
    __IO GPIO_BUZC_Typedef BUZC;
} GPIO_TypeDef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t RST: 1;
        uint32_t RESERVED0: 2;
        uint32_t FLASH_REQ: 1;
        uint32_t FLASH_ACK: 1;
        uint32_t RESERVED1: 1;
        uint32_t FLASH_FAIL: 1;
        uint32_t FEWE: 1;
        uint32_t SEWE: 1;
        uint32_t RESERVED2: 22;
    };
    uint32_t Word;
} IAP_CON_Typedef;

typedef union
{
    struct
    {
        uint32_t RESERVED0: 2;
        uint32_t IAPCA: 8;
        uint32_t IAPPA: 7;
        uint32_t RESERVED1: 3;
        uint32_t IFREN: 1;
        uint32_t RESERVED2: 11;
    };
    uint32_t Word;
} IAP_ADDR_Typedef;

typedef union
{
    struct
    {
        uint32_t DATA: 32;
    };
    uint32_t Word;
} IAP_DATA_Typedef;

typedef union
{
    struct
    {
        uint32_t TRIG: 32;
    };
    uint32_t Word;
} IAP_TRIG_Typedef;

typedef union
{
    struct
    {
        uint32_t UL: 32;
    };
    uint32_t Word;
} IAP_UL_Typedef;

typedef union
{
    struct
    {
        uint32_t BSY: 1;
        uint32_t PERASE_END: 1;
        uint32_t PROG_END: 1;
        uint32_t TIMEOUT_ERR: 1;
        uint32_t OP_ERR: 1;
        uint32_t MERASE_END: 1;
        uint32_t UERASE_END: 1;
        uint32_t RESERVED0: 25;
    };
    uint32_t Word;
} IAP_STA_Typedef;

typedef union
{
    struct
    {
        uint32_t IAP_WPROT: 32;
    };
    uint32_t Word;
} IAP_WPROT0_Typedef;

typedef union
{
    struct
    {
        uint32_t IAP_WPROT: 32;
    };
    uint32_t Word;
} IAP_WPROT1_Typedef;

typedef union
{
    struct
    {
        uint32_t IAP_WPROT: 1;
        uint32_t RESERVED0: 31;
    };
    uint32_t Word;
} IAP_WPROT2_Typedef;

typedef struct
{
    __IO IAP_CON_Typedef CON;
    __IO IAP_ADDR_Typedef ADDR;
    __IO IAP_DATA_Typedef DATA;
    __IO IAP_TRIG_Typedef TRIG;
    __IO IAP_UL_Typedef UL;
    __IO IAP_STA_Typedef STA;
    __IO IAP_WPROT0_Typedef WPROT0;
    __IO IAP_WPROT1_Typedef WPROT1;
    __IO IAP_WPROT2_Typedef WPROT2;
} IAP_TypeDef;

typedef union
{
    struct
    {
        uint32_t DR: 12;
        uint32_t RESERVED0: 20;
    };
    uint32_t Word;
} ADC_DR_Typedef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t TRIG: 1;
        uint32_t ACP_EN: 1;
        uint32_t RESERVED0: 1;
        uint32_t BIT_SEL: 2;
        uint32_t RESERVED1: 26;
    };
    uint32_t Word;
} ADC_CON0_Typedef;

typedef union
{
    struct
    {
        uint32_t CLKDIV: 3;
        uint32_t RESERVED0: 1;
        uint32_t CLKS: 2;
        uint32_t RESERVED1: 2;
        uint32_t VREFP: 2;
        uint32_t VREFN: 1;
        uint32_t VRBUF_EN: 1;
        uint32_t SMPS: 1;
        uint32_t SMPON: 1;
        uint32_t HSEN: 1;
        uint32_t RESERVED2: 1;
        uint32_t ST: 5;
        uint32_t RESERVED3: 3;
        uint32_t VCMBUF_EN: 1;
        uint32_t VCMBUF_HS: 1;
        uint32_t RESERVED4: 6;
    };
    uint32_t Word;
} ADC_CON1_Typedef;

typedef union
{
    struct
    {
        uint32_t CHS: 5;
        uint32_t RESERVED0: 3;
        uint32_t VDD5_FLAG_EN: 1;
        uint32_t RESERVED1: 23;
    };
    uint32_t Word;
} ADC_CHS_Typedef;

typedef union
{
    struct
    {
        uint32_t IE: 1;
        uint32_t ACPMINIE: 1;
        uint32_t ACPMAXIE: 1;
        uint32_t ACPOVIE: 1;
        uint32_t RESERVED0: 28;
    };
    uint32_t Word;
} ADC_IE_Typedef;

typedef union
{
    struct
    {
        uint32_t IF: 1;
        uint32_t ACPMINIF: 1;
        uint32_t ACPMAXIF: 1;
        uint32_t ACPOVIF: 1;
        uint32_t RESERVED0: 28;
    };
    uint32_t Word;
} ADC_IF_Typedef;

typedef union
{
    struct
    {
        uint32_t OVFL_TIME: 12;
        uint32_t RESERVED0: 4;
        uint32_t TIMES: 2;
        uint32_t RESERVED1: 2;
        uint32_t CLKS: 1;
        uint32_t RESERVED2: 11;
    };
    uint32_t Word;
} ADC_ACPC_Typedef;

typedef union
{
    struct
    {
        uint32_t CMP_MIN: 12;
        uint32_t RESERVED0: 4;
        uint32_t CMP_MAX: 12;
        uint32_t RESERVED1: 4;
    };
    uint32_t Word;
} ADC_ACPCMP_Typedef;

typedef union
{
    struct
    {
        uint32_t MEAN_DATA: 12;
        uint32_t RESERVED0: 20;
    };
    uint32_t Word;
} ADC_ACPMEAN_Typedef;

typedef union
{
    struct
    {
        uint32_t VREF_EN: 1;
        uint32_t RESERVED2: 1;
        uint32_t IREF_EN: 1;
        uint32_t RESERVED0: 1;
        uint32_t VDET_EN: 1;
        uint32_t VDET_SEL: 1;
        uint32_t RESERVED1: 26;
    };
    uint32_t Word;
} ADC_VREFCON_Typedef;

typedef struct
{
    __I ADC_DR_Typedef DR;
    __IO ADC_CON0_Typedef CON0;
    __IO ADC_CON1_Typedef CON1;
    __IO ADC_CHS_Typedef CHS;
    __IO ADC_IE_Typedef IE;
    __IO ADC_IF_Typedef IF;
    uint32_t RESERVED0[4] ;
    __IO ADC_ACPC_Typedef ACPC;
    uint32_t RESERVED1 ;
    __IO ADC_ACPCMP_Typedef ACPCMP;
    __I ADC_ACPMEAN_Typedef ACPMEAN;
    uint32_t RESERVED2[2] ;
    __IO ADC_VREFCON_Typedef VREFCON;
} ADC_TypeDef;

typedef union
{
    struct
    {
        uint32_t TMUP: 1;
        uint32_t TMWR: 1;
        uint32_t HSWI: 1;
        uint32_t RESERVED0: 1;
        uint32_t CLKS: 2;
        uint32_t XST: 1;
        uint32_t PON: 1;
        uint32_t RESERVED1: 24;
    };
    uint32_t Word;
} RTC_CON_Typedef;

typedef union
{
    struct
    {
        uint32_t CALF: 8;
        uint32_t DEV: 1;
        uint32_t COCR: 3;
        uint32_t CLKC: 1;
        uint32_t RESERVED0: 19;
    };
    uint32_t Word;
} RTC_CAL_Typedef;

typedef union
{
    struct
    {
        uint32_t WM: 7;
        uint32_t RESERVED0: 1;
        uint32_t WH: 6;
        uint32_t RESERVED1: 2;
        uint32_t WW: 7;
        uint32_t RESERVED2: 9;
    };
    uint32_t Word;
} RTC_WA_Typedef;

typedef union
{
    struct
    {
        uint32_t DM: 7;
        uint32_t RESERVED0: 1;
        uint32_t DH: 6;
        uint32_t RESERVED1: 18;
    };
    uint32_t Word;
} RTC_DA_Typedef;

typedef union
{
    struct
    {
        uint32_t SEC: 7;
        uint32_t RESERVED0: 1;
        uint32_t MIN: 7;
        uint32_t RESERVED1: 1;
        uint32_t HOUR: 6;
        uint32_t RESERVED2: 10;
    };
    uint32_t Word;
} RTC_HMS_Typedef;

typedef union
{
    struct
    {
        uint32_t WEEK: 7;
        uint32_t RESERVED0: 1;
        uint32_t DAY: 6;
        uint32_t RESERVED1: 2;
        uint32_t MON: 5;
        uint32_t RESERVED2: 3;
        uint32_t YEAR: 8;
    };
    uint32_t Word;
} RTC_YMDW_Typedef;

typedef union
{
    struct
    {
        uint32_t SCDIE: 1;
        uint32_t MINIE: 1;
        uint32_t HORIE: 1;
        uint32_t DAYIE: 1;
        uint32_t MONIE: 1;
        uint32_t RESERVED0: 3;
        uint32_t DALE: 1;
        uint32_t WALE: 1;
        uint32_t RESERVED1: 22;
    };
    uint32_t Word;
} RTC_IE_Typedef;

typedef union
{
    struct
    {
        uint32_t SCDIF: 1;
        uint32_t MINIF: 1;
        uint32_t HORIF: 1;
        uint32_t DAYIF: 1;
        uint32_t MONIF: 1;
        uint32_t RESERVED0: 3;
        uint32_t DAFG: 1;
        uint32_t WAFG: 1;
        uint32_t RESERVED1: 22;
    };
    uint32_t Word;
} RTC_IF_Typedef;

typedef union
{
    struct
    {
        uint32_t WP: 32;
    };
    uint32_t Word;
} RTC_WP_Typedef;

typedef struct
{
    __IO RTC_CON_Typedef CON;
    __IO RTC_CAL_Typedef CAL;
    __IO RTC_WA_Typedef WA;
    __IO RTC_DA_Typedef DA;
    __IO RTC_HMS_Typedef HMS;
    __IO RTC_YMDW_Typedef YMDW;
    __IO RTC_IE_Typedef IE;
    __IO RTC_IF_Typedef IF;
    __IO RTC_WP_Typedef WP;
} RTC_TypeDef;

typedef union
{
    struct
    {
        uint32_t LOAD: 32;
    };
    uint32_t Word;
} IWDT_LOAD_Typedef;

typedef union
{
    struct
    {
        uint32_t VALUE: 32;
    };
    uint32_t Word;
} IWDT_VALUE_Typedef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t IE: 1;
        uint32_t RSTEN: 1;
        uint32_t CLKS: 1;
        uint32_t RESERVED0: 28;
    };
    uint32_t Word;
} IWDT_CON_Typedef;

typedef union
{
    struct
    {
        uint32_t INTCLR: 32;
    };
    uint32_t Word;
} IWDT_INTCLR_Typedef;

typedef union
{
    struct
    {
        uint32_t WDTIF: 1;
        uint32_t RESERVED0: 31;
    };
    uint32_t Word;
} IWDT_RIS_Typedef;

typedef union
{
    struct
    {
        uint32_t LOCK: 1;
        uint32_t RESERVED0: 31;
    };
    uint32_t Word;
} IWDT_LOCK_Typedef;

typedef struct
{
    __O IWDT_LOAD_Typedef LOAD;
    __I IWDT_VALUE_Typedef VALUE;
    __IO IWDT_CON_Typedef CON;
    __O IWDT_INTCLR_Typedef INTCLR;
    __I IWDT_RIS_Typedef RIS;
    uint32_t RESERVED0[59] ;
    __IO IWDT_LOCK_Typedef LOCK;
} IWDT_TypeDef;

typedef union
{
    struct
    {
        uint32_t LOAD: 32;
    };
    uint32_t Word;
} WWDT_LOAD_Typedef;

typedef union
{
    struct
    {
        uint32_t VALUE: 32;
    };
    uint32_t Word;
} WWDT_VALUE_Typedef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t IE: 1;
        uint32_t RSTEN: 1;
        uint32_t CLKS: 1;
        uint32_t WWDTWIN: 2;
        uint32_t RESERVED0: 26;
    };
    uint32_t Word;
} WWDT_CON_Typedef;

typedef union
{
    struct
    {
        uint32_t INTCLR: 32;
    };
    uint32_t Word;
} WWDT_INTCLR_Typedef;

typedef union
{
    struct
    {
        uint32_t WWDTIF: 1;
        uint32_t RESERVED0: 31;
    };
    uint32_t Word;
} WWDT_RIS_Typedef;

typedef union
{
    struct
    {
        uint32_t LOCK: 1;
        uint32_t RESERVED0: 31;
    };
    uint32_t Word;
} WWDT_LOCK_Typedef;

typedef struct
{
    __O WWDT_LOAD_Typedef LOAD;
    __I WWDT_VALUE_Typedef VALUE;
    __IO WWDT_CON_Typedef CON;
    __O WWDT_INTCLR_Typedef INTCLR;
    __I WWDT_RIS_Typedef RIS;
    uint32_t RESERVED0[59] ;
    __IO WWDT_LOCK_Typedef LOCK;
} WWDT_TypeDef;

typedef union
{
    struct
    {
        uint32_t CNT: 16;
        uint32_t RESERVED0: 16;
    };
    uint32_t Word;
} T16N_CNT_Typedef;

typedef union
{
    struct
    {
        uint32_t PRECNT: 8;
        uint32_t RESERVED0: 24;
    };
    uint32_t Word;
} T16N_PRECNT_Typedef;

typedef union
{
    struct
    {
        uint32_t PREMAT: 8;
        uint32_t RESERVED0: 24;
    };
    uint32_t Word;
} T16N_PREMAT_Typedef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t CS: 2;
        uint32_t SYNC: 1;
        uint32_t EDGE: 2;
        uint32_t MOD: 2;
        uint32_t MAT0S: 2;
        uint32_t MAT1S: 2;
        uint32_t MAT2S: 2;
        uint32_t MAT3S: 2;
        uint32_t ASYWEN: 1;
        uint32_t RESERVED0: 15;
    };
    uint32_t Word;
} T16N_CON0_Typedef;

typedef union
{
    struct
    {
        uint32_t CAPPE: 1;
        uint32_t CAPNE: 1;
        uint32_t CAPIS0: 1;
        uint32_t CAPIS1: 1;
        uint32_t CAPT: 4;
        uint32_t CAPL0: 1;
        uint32_t CAPL1: 1;
        uint32_t RESERVED0: 22;
    };
    uint32_t Word;
} T16N_CON1_Typedef;

typedef union
{
    struct
    {
        uint32_t MOE0: 1;
        uint32_t MOE1: 1;
        uint32_t POL0: 1;
        uint32_t POL1: 1;
        uint32_t MOM0: 2;
        uint32_t MOM1: 2;
        uint32_t MOM2: 2;
        uint32_t MOM3: 2;
        uint32_t PBKEN: 1;
        uint32_t PBKPS: 1;
        uint32_t PBKF: 1;
        uint32_t RESERVED0: 1;
        uint32_t PBKS: 3;
        uint32_t RESERVED1: 1;
        uint32_t PBKL0: 1;
        uint32_t PBKL1: 1;
        uint32_t RESERVED2: 10;
    };
    uint32_t Word;
} T16N_CON2_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT0IE: 1;
        uint32_t MAT1IE: 1;
        uint32_t MAT2IE: 1;
        uint32_t MAT3IE: 1;
        uint32_t OVIE: 1;
        uint32_t CAP0IE: 1;
        uint32_t CAP1IE: 1;
        uint32_t PBKIE: 1;
        uint32_t RESERVED0: 24;
    };
    uint32_t Word;
} T16N_IE_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT0IF: 1;
        uint32_t MAT1IF: 1;
        uint32_t MAT2IF: 1;
        uint32_t MAT3IF: 1;
        uint32_t OVIF: 1;
        uint32_t CAP0IF: 1;
        uint32_t CAP1IF: 1;
        uint32_t PBKIF: 1;
        uint32_t RESERVED0: 24;
    };
    uint32_t Word;
} T16N_IF_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT0TAR: 1;
        uint32_t MAT1TAR: 1;
        uint32_t MAT2TAR: 1;
        uint32_t MAT3TAR: 1;
        uint32_t OVTAR: 1;
        uint32_t RESERVED0: 27;
    };
    uint32_t Word;
} T16N_TRG_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT0: 16;
        uint32_t RESERVED0: 16;
    };
    uint32_t Word;
} T16N_MAT0_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT1: 16;
        uint32_t RESERVED0: 16;
    };
    uint32_t Word;
} T16N_MAT1_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT2: 16;
        uint32_t RESERVED0: 16;
    };
    uint32_t Word;
} T16N_MAT2_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT3: 16;
        uint32_t RESERVED0: 16;
    };
    uint32_t Word;
} T16N_MAT3_Typedef;

typedef struct
{
    __IO T16N_CNT_Typedef CNT;
    uint32_t RESERVED0;
    __IO T16N_PRECNT_Typedef PRECNT;
    __IO T16N_PREMAT_Typedef PREMAT;
    __IO T16N_CON0_Typedef CON0;
    __IO T16N_CON1_Typedef CON1;
    __IO T16N_CON2_Typedef CON2;
    uint32_t RESERVED1;
    __IO T16N_IE_Typedef IE;
    __IO T16N_IF_Typedef IF;
    __IO T16N_TRG_Typedef TRG;
    uint32_t RESERVED2;
    __IO T16N_MAT0_Typedef MAT0;
    __IO T16N_MAT1_Typedef MAT1;
    __IO T16N_MAT2_Typedef MAT2;
    __IO T16N_MAT3_Typedef MAT3;
} T16N_TypeDef;

typedef union
{
    struct
    {
        uint32_t CNT: 32;
    };
    uint32_t Word;
} T32N_CNT_Typedef;

typedef union
{
    struct
    {
        uint32_t PRECNT: 8;
        uint32_t RESERVED0: 24;
    };
    uint32_t Word;
} T32N_PRECNT_Typedef;

typedef union
{
    struct
    {
        uint32_t PREMAT: 8;
        uint32_t RESERVED0: 24;
    };
    uint32_t Word;
} T32N_PREMAT_Typedef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t CS: 2;
        uint32_t SYNC: 1;
        uint32_t EDGE: 2;
        uint32_t MOD: 2;
        uint32_t MAT0S: 2;
        uint32_t MAT1S: 2;
        uint32_t MAT2S: 2;
        uint32_t MAT3S: 2;
        uint32_t ASYNC_WREN: 1;
        uint32_t RESERVED0: 15;
    };
    uint32_t Word;
} T32N_CON0_Typedef;

typedef union
{
    struct
    {
        uint32_t CAPPE: 1;
        uint32_t CAPNE: 1;
        uint32_t CAPIS0: 1;
        uint32_t CAPIS1: 1;
        uint32_t CAPT: 4;
        uint32_t CAPL0: 1;
        uint32_t CAPL1: 1;
        uint32_t RESERVED0: 22;
    };
    uint32_t Word;
} T32N_CON1_Typedef;

typedef union
{
    struct
    {
        uint32_t MOE0: 1;
        uint32_t MOE1: 1;
        uint32_t POL0: 1;
        uint32_t POL1: 1;
        uint32_t MOM0: 2;
        uint32_t MOM1: 2;
        uint32_t MOM2: 2;
        uint32_t MOM3: 2;
        uint32_t RESERVED0: 20;
    };
    uint32_t Word;
} T32N_CON2_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT0IE: 1;
        uint32_t MAT1IE: 1;
        uint32_t MAT2IE: 1;
        uint32_t MAT3IE: 1;
        uint32_t OVIE: 1;
        uint32_t CAP0IE: 1;
        uint32_t CAP1IE: 1;
        uint32_t RESERVED0: 25;
    };
    uint32_t Word;
} T32N_IE_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT0IF: 1;
        uint32_t MAT1IF: 1;
        uint32_t MAT2IF: 1;
        uint32_t MAT3IF: 1;
        uint32_t OVIF: 1;
        uint32_t CAP0IF: 1;
        uint32_t CAP1IF: 1;
        uint32_t RESERVED0: 25;
    };
    uint32_t Word;
} T32N_IF_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT0TAR: 1;
        uint32_t MAT1TAR: 1;
        uint32_t MAT2TAR: 1;
        uint32_t MAT3TAR: 1;
        uint32_t OVTAR: 1;
        uint32_t RESERVED0: 27;
    };
    uint32_t Word;
} T32N_TRG_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT0: 32;
    };
    uint32_t Word;
} T32N_MAT0_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT1: 32;
    };
    uint32_t Word;
} T32N_MAT1_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT2: 32;
    };
    uint32_t Word;
} T32N_MAT2_Typedef;

typedef union
{
    struct
    {
        uint32_t MAT3: 32;
    };
    uint32_t Word;
} T32N_MAT3_Typedef;

typedef struct
{
    __IO T32N_CNT_Typedef CNT;
    uint32_t RESERVED0;
    __IO T32N_PRECNT_Typedef PRECNT;
    __IO T32N_PREMAT_Typedef PREMAT;
    __IO T32N_CON0_Typedef CON0;
    __IO T32N_CON1_Typedef CON1;
    __IO T32N_CON2_Typedef CON2;
    uint32_t RESERVED1;
    __IO T32N_IE_Typedef IE;
    __IO T32N_IF_Typedef IF;
    __IO T32N_TRG_Typedef TRG;
    uint32_t RESERVED2;
    __IO T32N_MAT0_Typedef MAT0;
    __IO T32N_MAT1_Typedef MAT1;
    __IO T32N_MAT2_Typedef MAT2;
    __IO T32N_MAT3_Typedef MAT3;
} T32N_TypeDef;

typedef union
{
    struct
    {
        uint32_t TXEN: 1;
        uint32_t TRST: 1;
        uint32_t TXFS: 1;
        uint32_t RESERVED0: 1;
        uint32_t TXMOD: 3;
        uint32_t TXP: 1;
        uint32_t RXEN: 1;
        uint32_t RRST: 1;
        uint32_t RESERVED1: 2;
        uint32_t RXMOD: 3;
        uint32_t RXP: 1;
        uint32_t RESERVED2: 12;
        uint32_t BCS: 3;
        uint32_t RESERVED3: 1;
    };
    uint32_t Word;
} UART_CON_Typedef;

typedef union
{
    struct
    {
        uint32_t BRR: 11;
        uint32_t RESERVED0: 21;
    };
    uint32_t Word;
} UART_BRR_Typedef;

typedef union
{
    uint8_t Byte[4];
    uint16_t HalfWord[2];
    uint32_t Word;
} UART_TBW_Typedef;

typedef union
{
    uint8_t Byte[4];
    uint16_t HalfWord[2];
    uint32_t Word;
} UART_RBR_Typedef;

typedef union
{
    struct
    {
        uint32_t TB0: 9;
        uint32_t RESERVED0: 3;
        uint32_t TP0: 1;
        uint32_t TBEF0: 1;
        uint32_t RESERVED1: 2;
        uint32_t TB1: 9;
        uint32_t RESERVED2: 3;
        uint32_t TP1: 1;
        uint32_t TBEF1: 1;
        uint32_t RESERVED3: 2;
    };
    uint32_t Word;
} UART_TB01_Typedef;

typedef union
{
    struct
    {
        uint32_t TB2: 9;
        uint32_t RESERVED0: 3;
        uint32_t TP2: 1;
        uint32_t TBEF2: 1;
        uint32_t RESERVED1: 2;
        uint32_t TB3: 9;
        uint32_t RESERVED2: 3;
        uint32_t TP3: 1;
        uint32_t TBEF3: 1;
        uint32_t RESERVED3: 2;
    };
    uint32_t Word;
} UART_TB23_Typedef;

typedef union
{
    struct
    {
        uint32_t RB0: 9;
        uint32_t RESERVED0: 3;
        uint32_t RP0: 1;
        uint32_t RBFF0: 1;
        uint32_t FE0: 1;
        uint32_t PE0: 1;
        uint32_t RB1: 9;
        uint32_t RESERVED1: 3;
        uint32_t RP1: 1;
        uint32_t RBFF1: 1;
        uint32_t FE1: 1;
        uint32_t PE1: 1;
    };
    uint32_t Word;
} UART_RB01_Typedef;

typedef union
{
    struct
    {
        uint32_t RB2: 9;
        uint32_t RESERVED0: 3;
        uint32_t RP2: 1;
        uint32_t RBFF2: 1;
        uint32_t FE2: 1;
        uint32_t PE2: 1;
        uint32_t RB3: 9;
        uint32_t RESERVED1: 3;
        uint32_t RP3: 1;
        uint32_t RBFF3: 1;
        uint32_t FE3: 1;
        uint32_t PE3: 1;
    };
    uint32_t Word;
} UART_RB23_Typedef;

typedef union
{
    struct
    {
        uint32_t TBIE: 1;
        uint32_t RBIE: 1;
        uint32_t ROIE: 1;
        uint32_t FEIE: 1;
        uint32_t PEIE: 1;
        uint32_t TBEIE: 1;
        uint32_t RESERVED0: 2;
        uint32_t TBIM: 2;
        uint32_t RBIM: 2;
        uint32_t TIDIE: 1;
        uint32_t RIDIE: 1;
        uint32_t RESERVED1: 18;
    };
    uint32_t Word;
} UART_IE_Typedef;

typedef union
{
    struct
    {
        uint32_t TBIF: 1;
        uint32_t RBIF: 1;
        uint32_t ROIF: 1;
        uint32_t FEIF: 1;
        uint32_t PEIF: 1;
        uint32_t TBEIF: 1;
        uint32_t RESERVED0: 6;
        uint32_t TIDIF: 1;
        uint32_t RIDIF: 1;
        uint32_t RESERVED1: 18;
    };
    uint32_t Word;
} UART_IF_Typedef;

typedef struct
{
    __IO UART_CON_Typedef CON;
    __IO UART_BRR_Typedef BRR;
    __O UART_TBW_Typedef TBW;
    __I UART_RBR_Typedef RBR;
    __I UART_TB01_Typedef TB01;
    __I UART_TB23_Typedef TB23;
    __I UART_RB01_Typedef RB01;
    __I UART_RB23_Typedef RB23;
    __IO UART_IE_Typedef IE;
    __IO UART_IF_Typedef IF;
} UART_TypeDef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t RST: 1;
        uint32_t MS: 1;
        uint32_t REN: 1;
        uint32_t RESERVED0: 1;
        uint32_t DRE: 1;
        uint32_t DFS: 2;
        uint32_t RESERVED1: 8;
        uint32_t TME: 1;
        uint32_t TMS: 1;
        uint32_t TMP: 6;
        uint32_t DW: 3;
        uint32_t RESERVED2: 3;
        uint32_t TXCLR: 1;
        uint32_t RXCLR: 1;
    };
    uint32_t Word;
} SPI_CON_Typedef;

typedef union
{
    uint8_t Byte[4];
    uint16_t HalfWord[2];
    uint32_t Word;
} SPI_TBW_Typedef;

typedef union
{
    uint8_t Byte[4];
    uint16_t HalfWord[2];
    uint32_t Word;
} SPI_RBR_Typedef;

typedef union
{
    struct
    {
        uint32_t TBIE: 1;
        uint32_t RBIE: 1;
        uint32_t TEIE: 1;
        uint32_t ROIE: 1;
        uint32_t IDIE: 1;
        uint32_t NSSIE: 1;
        uint32_t TBWEIE: 1;
        uint32_t RESERVED0: 1;
        uint32_t TBIM: 2;
        uint32_t RBIM: 2;
        uint32_t RESERVED1: 20;
    };
    uint32_t Word;
} SPI_IE_Typedef;

typedef union
{
    struct
    {
        uint32_t TBIF: 1;
        uint32_t RBIF: 1;
        uint32_t TEIF: 1;
        uint32_t ROIF: 1;
        uint32_t IDIF: 1;
        uint32_t NSSIF: 1;
        uint32_t TBWEIF: 1;
        uint32_t RESERVED0: 25;
    };
    uint32_t Word;
} SPI_IF_Typedef;

typedef union
{
    struct
    {
        uint32_t TB0: 8;
        uint32_t TB1: 8;
        uint32_t TB2: 8;
        uint32_t TB3: 8;
    };
    uint32_t Word;
} SPI_TB_Typedef;

typedef union
{
    struct
    {
        uint32_t RB0: 8;
        uint32_t RB1: 8;
        uint32_t RB2: 8;
        uint32_t RB3: 8;
    };
    uint32_t Word;
} SPI_RB_Typedef;

typedef union
{
    struct
    {
        uint32_t RESERVED0: 7;
        uint32_t NSS: 1;
        uint32_t TBEF0: 1;
        uint32_t TBEF1: 1;
        uint32_t TBEF2: 1;
        uint32_t TBEF3: 1;
        uint32_t RBFF0: 1;
        uint32_t RBFF1: 1;
        uint32_t RBFF2: 1;
        uint32_t RBFF3: 1;
        uint32_t IDLE: 1;
        uint32_t RESERVED1: 15;
    };
    uint32_t Word;
} SPI_STA_Typedef;

typedef union
{
    struct
    {
        uint32_t CKS: 10;
        uint32_t RESERVED0: 22;
    };
    uint32_t Word;
} SPI_CKS_Typedef;

typedef struct
{
    __IO SPI_CON_Typedef CON;
    uint32_t RESERVED0 ;
    __O SPI_TBW_Typedef TBW;
    __I SPI_RBR_Typedef RBR;
    __IO SPI_IE_Typedef IE;
    __IO SPI_IF_Typedef IF;
    __I SPI_TB_Typedef TB;
    __I SPI_RB_Typedef RB;
    __I SPI_STA_Typedef STA;
    __IO SPI_CKS_Typedef CKS;
} SPI_TypeDef;

typedef union
{
    struct
    {
        uint32_t EN: 1;
        uint32_t RST: 1;
        uint32_t SCKOD: 1;
        uint32_t SDAOD: 1;
        uint32_t SCKSE: 1;
        uint32_t SDASE: 1;
        uint32_t RESERVED0: 1;
        uint32_t TJE: 1;
        uint32_t TJP: 8;
        uint32_t RW: 1;
        uint32_t SA: 7;
        uint32_t RESERVED1: 8;
    };
    uint32_t Word;
} I2C_CON_Typedef;

typedef union
{
    struct
    {
        uint32_t MS: 1;
        uint32_t RDM: 3;
        uint32_t CSE: 1;
        uint32_t ANAE: 1;
        uint32_t SRAE: 1;
        uint32_t SPAE: 1;
        uint32_t ADLY: 3;
        uint32_t ADE: 1;
        uint32_t TIS: 4;
        uint32_t SRT: 1;
        uint32_t SPT: 1;
        uint32_t RDT: 1;
        uint32_t BLD: 1;
        uint32_t RESERVED0: 4;
        uint32_t TAS: 1;
        uint32_t RESERVED1: 7;
    };
    uint32_t Word;
} I2C_MOD_Typedef;

typedef union
{
    struct
    {
        uint32_t SRIE: 1;
        uint32_t SPIE: 1;
        uint32_t TBIE: 1;
        uint32_t RBIE: 1;
        uint32_t TEIE: 1;
        uint32_t ROIE: 1;
        uint32_t NAIE: 1;
        uint32_t TBWEIE: 1;
        uint32_t TBIM: 2;
        uint32_t RBIM: 2;
        uint32_t TIDLEIE: 1;
        uint32_t RESERVED0: 19;
    };
    uint32_t Word;
} I2C_IE_Typedef;

typedef union
{
    struct
    {
        uint32_t SRIF: 1;
        uint32_t SPIF: 1;
        uint32_t TBIF: 1;
        uint32_t RBIF: 1;
        uint32_t TEIF: 1;
        uint32_t ROIF: 1;
        uint32_t NAIF: 1;
        uint32_t TBWEIF: 1;
        uint32_t RESERVED0: 4;
        uint32_t TIDLEIF: 1;
        uint32_t RESERVED1: 19;
    };
    uint32_t Word;
} I2C_IF_Typedef;

typedef union
{
    uint8_t Byte[4];
    uint16_t HalfWord[2];
    uint32_t Word;
} I2C_TBW_Typedef;

typedef union
{
    uint8_t Byte[4];
    uint16_t HalfWord[2];
    uint32_t Word;
} I2C_RBR_Typedef;

typedef union
{
    struct
    {
        uint32_t TB0: 8;
        uint32_t TB1: 8;
        uint32_t TB2: 8;
        uint32_t TB3: 8;
    };
    uint32_t Word;
} I2C_TB_Typedef;

typedef union
{
    struct
    {
        uint32_t RB0: 8;
        uint32_t RB1: 8;
        uint32_t RB2: 8;
        uint32_t RB3: 8;
    };
    uint32_t Word;
} I2C_RB_Typedef;

typedef union
{
    struct
    {
        uint32_t RESERVED0: 8;
        uint32_t TBEF0: 1;
        uint32_t TBEF1: 1;
        uint32_t TBEF2: 1;
        uint32_t TBEF3: 1;
        uint32_t RBFF0: 1;
        uint32_t RBFF1: 1;
        uint32_t RBFF2: 1;
        uint32_t RBFF3: 1;
        uint32_t ACK: 1;
        uint32_t IDLE: 1;
        uint32_t RESERVED1: 14;
    };
    uint32_t Word;
} I2C_STA_Typedef;

typedef struct
{
    __IO I2C_CON_Typedef CON;
    __IO I2C_MOD_Typedef MOD;
    __IO I2C_IE_Typedef IE;
    __IO I2C_IF_Typedef IF;
    __O I2C_TBW_Typedef TBW;
    __I I2C_RBR_Typedef RBR;
    __I I2C_TB_Typedef TB;
    __I I2C_RB_Typedef RB;
    __I I2C_STA_Typedef STA;
} I2C_TypeDef;

typedef union
{
    struct
    {
        uint32_t AES_DATA0: 32;
    };
    uint32_t Word;
} AES_DATA0_Typedef;

typedef union
{
    struct
    {
        uint32_t AES_DATA1: 32;
    };
    uint32_t Word;
} AES_DATA1_Typedef;

typedef union
{
    struct
    {
        uint32_t AES_DATA2: 32;
    };
    uint32_t Word;
} AES_DATA2_Typedef;

typedef union
{
    struct
    {
        uint32_t AES_DATA3: 32;
    };
    uint32_t Word;
} AES_DATA3_Typedef;

typedef union
{
    struct
    {
        uint32_t AES_KEY0: 32;
    };
    uint32_t Word;
} AES_KEY0_Typedef;

typedef union
{
    struct
    {
        uint32_t AES_KEY1: 32;
    };
    uint32_t Word;
} AES_KEY1_Typedef;

typedef union
{
    struct
    {
        uint32_t AES_KEY2: 32;
    };
    uint32_t Word;
} AES_KEY2_Typedef;

typedef union
{
    struct
    {
        uint32_t AES_KEY3: 32;
    };
    uint32_t Word;
} AES_KEY3_Typedef;

typedef union
{
    struct
    {
        uint32_t GO_DONE: 1;
        uint32_t ENCRYPT: 1;
        uint32_t RESERVED0: 4;
        uint32_t IE: 1;
        uint32_t IF: 1;
        uint32_t RESERVED1: 24;
    };
    uint32_t Word;
} AES_CON_Typedef;

typedef struct
{
    __IO AES_DATA0_Typedef DATA0;
    __IO AES_DATA1_Typedef DATA1;
    __IO AES_DATA2_Typedef DATA2;
    __IO AES_DATA3_Typedef DATA3;
    __IO AES_KEY0_Typedef KEY0;
    __IO AES_KEY1_Typedef KEY1;
    __IO AES_KEY2_Typedef KEY2;
    __IO AES_KEY3_Typedef KEY3;
    __IO AES_CON_Typedef CON;
} AES_TypeDef;

/******************************************************************************/
/* 物理地址映射 */
/******************************************************************************/

/* Base addresses */
#define FLASH_BASE (0x00000000UL)
#define SRAM_BASE (0x20000000UL)
#define APB_BASE (0x40000000UL)
#define RAM_BASE (0x60000000UL)

/* APB peripherals */
#define SCU_BASE (APB_BASE + 0x00000)
#define CRC_BASE (APB_BASE + 0x00C00)
#define GPIO_BASE (APB_BASE + 0x20000)
#define IAP_BASE (APB_BASE + 0x00800)
#define ADC_BASE (APB_BASE + 0x01000)
#define RTC_BASE (APB_BASE + 0x01400)
#define IWDT_BASE (APB_BASE + 0x01C00)
#define WWDT_BASE (APB_BASE + 0x01800)
#define T16N0_BASE (APB_BASE + 0x02000)
#define T16N1_BASE (APB_BASE + 0x02400)
#define T16N2_BASE (APB_BASE + 0x02800)
#define T16N3_BASE (APB_BASE + 0x02C00)
#define T32N0_BASE (APB_BASE + 0x04000)
#define UART0_BASE (APB_BASE + 0x06000)
#define UART1_BASE (APB_BASE + 0x06400)
#define UART2_BASE (APB_BASE + 0x06800)
#define UART3_BASE (APB_BASE + 0x06C00)
#define UART4_BASE (APB_BASE + 0x07000)
#define UART5_BASE (APB_BASE + 0x07400)
#define SPI0_BASE (APB_BASE + 0x08000)
#define I2C0_BASE (APB_BASE + 0x09000)
#define AES_BASE (APB_BASE + 0x0A000)

/******************************************************************************/
/* 外设定义 */
/******************************************************************************/
#define SCU ((SCU_TypeDef *) SCU_BASE )
#define CRC ((CRC_TypeDef *) CRC_BASE )
#define GPIO ((GPIO_TypeDef *) GPIO_BASE )
#define IAP ((IAP_TypeDef *) IAP_BASE )
#define ADC ((ADC_TypeDef *) ADC_BASE )
#define RTC ((RTC_TypeDef *) RTC_BASE )
#define IWDT ((IWDT_TypeDef *) IWDT_BASE )
#define WWDT ((WWDT_TypeDef *) WWDT_BASE )
#define T16N0 ((T16N_TypeDef *) T16N0_BASE )
#define T16N1 ((T16N_TypeDef *) T16N1_BASE )
#define T16N2 ((T16N_TypeDef *) T16N2_BASE )
#define T16N3 ((T16N_TypeDef *) T16N3_BASE )
#define T32N0 ((T32N_TypeDef *) T32N0_BASE )
#define UART0 ((UART_TypeDef *) UART0_BASE )
#define UART1 ((UART_TypeDef *) UART1_BASE )
#define UART2 ((UART_TypeDef *) UART2_BASE )
#define UART3 ((UART_TypeDef *) UART3_BASE )
#define UART4 ((UART_TypeDef *) UART4_BASE )
#define UART5 ((UART_TypeDef *) UART5_BASE )
#define SPI0 ((SPI_TypeDef *) SPI0_BASE )
#define I2C0 ((I2C_TypeDef *) I2C0_BASE )
#define AES ((AES_TypeDef *) AES_BASE )


#endif
