/*******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file interrupts_hc32f480.h
 **
 ** A detailed description is available at
 ** @link InterruptGroup Interrupt description @endlink
 **
 **   - 2017-05-15  1.0  Zhangxl First version for Device Driver Library of
 **     interrupt.
 **
 ******************************************************************************/
#ifndef __INTERRUPTS_HC32F480_H___
#define __INTERRUPTS_HC32F480_H___

/*******************************************************************************
 * Include files
 ******************************************************************************/
//#include "base_types.h"
#include "hc32f480.h"
#include "ddl.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup InterruptGroup Interrupt
 **
 ******************************************************************************/
//@{

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
typedef enum
{
    /* External Interrupt */
    PORT_EIRQ0  =  1,
    PORT_EIRQ1  =  2,
    PORT_EIRQ2  =  3,
    PORT_EIRQ3  =  4,
    PORT_EIRQ4  =  5,
    PORT_EIRQ5  =  6,
    PORT_EIRQ6  =  7,
    PORT_EIRQ7  =  8,
    PORT_EIRQ8  =  9,
    PORT_EIRQ9  = 10,
    PORT_EIRQ10 = 11,
    PORT_EIRQ11 = 12,
    PORT_EIRQ12 = 13,
    PORT_EIRQ13 = 14,
    PORT_EIRQ14 = 15,
    PORT_EIRQ15 = 16,

    /* DMAC */
    DMA_TC0 = 33,
    DMA_TC1 = 34,
    DMA_TC2 = 35,
    DMA_TC3 = 36,
    DMA_TC4 = 37,
    DMA_TC5 = 38,
    DMA_TC6 = 39,
    DMA_TC7 = 40,
    DMA_BTC0 = 41,
    DMA_BTC1 = 42,
    DMA_BTC2 = 43,
    DMA_BTC3 = 44,
    DMA_BTC4 = 45,
    DMA_BTC5 = 46,
    DMA_BTC6 = 47,
    DMA_BTC7 = 48,
    DMA_ERR  = 49,

    /* FMC */
    FMC_PEERR  = 50,
    FMC_RDCOL  = 51,
    FMC_OPTEND = 52,

    /* VDU */
    VDU_VDU1 = 56,
    VDU_VDU2 = 57,

    /* SOSC */
    SOSC_STOP = 58,

    /* MOSC */
    MOSC_STOP = 59,

    /* WKTM */
    WKTM_PRD = 60,

    /* TIMER0_0 */
    TMR0_U0_GCMA = 64,
    TMR0_U0_GCMB = 65,

    /* TIMER0_1 */
    TMR0_U1_GCMA = 66,
    TMR0_U1_GCMB = 67,

    /* TIMER2_0 */
    TMR2_U0_GCMA = 68,
    TMR2_U0_GCMB = 69,

    /* TIMER2_1 */
    TMR2_U1_GCMA = 70,
    TMR2_U1_GCMB = 71,

    /* TIMER2_2 */
    TMR2_U2_GCMA = 72,
    TMR2_U2_GCMB = 73,

    /* TIMER2_3 */
    TMR2_U3_GCMA = 74,
    TMR2_U3_GCMB = 75,

    /*  SWDT*/
    SWDT_NMIUNDF = 76,

    /* RTC */
    RTC_TP  = 77,
    RTC_ALM = 78,
    RTC_PRD = 79,
    RTC_IT  = 80,

    /* DPRAMC */
    DPRAMC_INT = 85,
    DPRAMC_EI  = 86,

    /* DCU */
    DCU0 = 89,
    DCU1 = 90,
    DCU2 = 91,
    DCU3 = 92,

    /* TIMER6_0 */
    TMR6_U0_GCMA = 108,
    TMR6_U0_GCMB = 109,
    TMR6_U0_GCMC = 110,
    TMR6_U0_GCMD = 111,
    TMR6_U0_GCME = 112,
    TMR6_U0_GCMF = 113,
    TMR6_U0_GOVF = 114,
    TMR6_U0_GUDF = 115,
    TMR6_U0_GDTE = 116,
    TMR6_U0_GSMH = 117,
    TMR6_U0_GSML = 118,
    TMR6_U0_SCMA = 119,
    TMR6_U0_SCMB = 120,

    /* TIMER6_1 */
    TMR6_U1_GCMA = 121,
    TMR6_U1_GCMB = 122,
    TMR6_U1_GCMC = 123,
    TMR6_U1_GCMD = 124,
    TMR6_U1_GCME = 125,
    TMR6_U1_GCMF = 126,
    TMR6_U1_GOVF = 127,
    TMR6_U1_GUDF = 128,
    TMR6_U1_GDTE = 129,
    TMR6_U1_GSMH = 130,
    TMR6_U1_GSML = 131,
    TMR6_U1_SCMA = 132,
    TMR6_U1_SCMB = 133,

    /* TIMER6_2 */
    TMR6_U2_GCMA = 134,
    TMR6_U2_GCMB = 135,
    TMR6_U2_GCMC = 136,
    TMR6_U2_GCMD = 137,
    TMR6_U2_GCME = 138,
    TMR6_U2_GCMF = 139,
    TMR6_U2_GOVF = 140,
    TMR6_U2_GUDF = 141,
    TMR6_U2_GDTE = 142,
    TMR6_U2_GSMH = 143,
    TMR6_U2_GSML = 144,
    TMR6_U2_SCMA = 145,
    TMR6_U2_SCMB = 146,

    /* TIMER6_3 */
    TMR6_U3_GCMA = 147,
    TMR6_U3_GCMB = 148,
    TMR6_U3_GCMC = 149,
    TMR6_U3_GCMD = 150,
    TMR6_U3_GCME = 151,
    TMR6_U3_GCMF = 152,
    TMR6_U3_GOVF = 153,
    TMR6_U3_GUDF = 154,
    TMR6_U3_GDTE = 155,
    TMR6_U3_GSMH = 156,
    TMR6_U3_GSML = 157,
    TMR6_U3_SCMA = 158,
    TMR6_U3_SCMB = 159,

    /* TIMER6_4 */
    TMR6_U4_GCMA = 160,
    TMR6_U4_GCMB = 161,
    TMR6_U4_GCMC = 162,
    TMR6_U4_GCMD = 163,
    TMR6_U4_GCME = 164,
    TMR6_U4_GCMF = 165,
    TMR6_U4_GOVF = 166,
    TMR6_U4_GUDF = 167,
    TMR6_U4_GDTE = 168,
    TMR6_U4_GSMH = 169,
    TMR6_U4_GSML = 170,
    TMR6_U4_SCMA = 171,
    TMR6_U4_SCMB = 172,

    /* TIMER6_5 */
    TMR6_U5_GCMA = 173,
    TMR6_U5_GCMB = 174,
    TMR6_U5_GCMC = 175,
    TMR6_U5_GCMD = 176,
    TMR6_U5_GCME = 177,
    TMR6_U5_GCMF = 178,
    TMR6_U5_GOVF = 179,
    TMR6_U5_GUDF = 180,
    TMR6_U5_GDTE = 181,
    TMR6_U5_GSMH = 182,
    TMR6_U5_GSML = 183,
    TMR6_U5_SCMA = 184,
    TMR6_U5_SCMB = 185,

    /* TIMER6_6 */
    TMR6_U6_GCMA = 186,
    TMR6_U6_GCMB = 187,
    TMR6_U6_GCMC = 188,
    TMR6_U6_GCMD = 189,
    TMR6_U6_GCME = 190,
    TMR6_U6_GCMF = 191,
    TMR6_U6_GOVF = 192,
    TMR6_U6_GUDF = 193,
    TMR6_U6_GDTE = 194,
    TMR6_U6_GSMH = 195,
    TMR6_U6_GSML = 196,
    TMR6_U6_SCMA = 197,
    TMR6_U6_SCMB = 198,

    /* TIMER6_7 */
    TMR6_U7_GCMA = 199,
    TMR6_U7_GCMB = 200,
    TMR6_U7_GCMC = 201,
    TMR6_U7_GCMD = 202,
    TMR6_U7_GCME = 203,
    TMR6_U7_GCMF = 204,
    TMR6_U7_GOVF = 205,
    TMR6_U7_GUDF = 206,
    TMR6_U7_GDTE = 207,
    TMR6_U7_GSMH = 208,
    TMR6_U7_GSML = 209,
    TMR6_U7_SCMA = 210,
    TMR6_U7_SCMB = 211,

    /* TIMER6_8 */
    TMR6_U8_GCMA = 212,
    TMR6_U8_GCMB = 213,
    TMR6_U8_GCMC = 214,
    TMR6_U8_GCMD = 215,
    TMR6_U8_GCME = 216,
    TMR6_U8_GCMF = 217,
    TMR6_U8_GOVF = 218,
    TMR6_U8_GUDF = 219,
    TMR6_U8_GDTE = 220,
    TMR6_U8_GSMH = 221,
    TMR6_U8_GSML = 222,
    TMR6_U8_SCMA = 223,
    TMR6_U8_SCMB = 224,

    /* TIMER6_9 */
    TMR6_U9_GCMA = 225,
    TMR6_U9_GCMB = 226,
    TMR6_U9_GCMC = 227,
    TMR6_U9_GCMD = 228,
    TMR6_U9_GCME = 229,
    TMR6_U9_GCMF = 230,
    TMR6_U9_GOVF = 231,
    TMR6_U9_GUDF = 232,
    TMR6_U9_GDTE = 233,
    TMR6_U9_GSMH = 234,
    TMR6_U9_GSML = 235,
    TMR6_U9_SCMA = 236,
    TMR6_U9_SCMB = 237,

    /* DFMC */
    DFMC_PERR   = 292,
    DFMC_RDCOL  = 293,
    DFMC_OPTEND = 294,

    /* CAN0 */
    CAN0_INT = 306,

    /* CAN1 */
    CAN1_INT = 311,

    /* USART0 */
    USART0_EI  = 315,
    USART0_RI  = 316,
    USART0_TI  = 317,
    USART0_TCI = 318,
    USART0_WUPI =319,

    /* USART1 */
    USART1_EI  = 320,
    USART1_RI  = 321,
    USART1_TI  = 322,
    USART1_TCI = 323,

    /* USART2 */
    USART2_EI  = 324,
    USART2_RI  = 325,
    USART2_TI  = 326,
    USART2_TCI = 327,

    /* USART3 */
    USART3_EI  = 328,
    USART3_RI  = 329,
    USART3_TI  = 330,
    USART3_TCI = 331,

    /* USART4 */
    USART4_EI  = 332,
    USART4_RI  = 333,
    USART4_TI  = 334,
    USART4_TCI = 335,

    /* USART5 */
    USART5_EI  = 336,
    USART5_RI  = 337,
    USART5_TI  = 338,
    USART5_TCI = 339,

    /* USART6 */
    USART6_EI  = 340,
    USART6_RI  = 341,
    USART6_TI  = 342,
    USART6_TCI = 343,

    /* MSC0 */
    MSC0_1 = 344,
    MSC0_2 = 345,
    MSC0_3 = 346,

    /* MSC1 */
    MSC1_1 = 347,
    MSC1_2 = 348,
    MSC1_3 = 349,

    /* MSC2 */
    MSC2_1 = 350,
    MSC2_2 = 351,
    MSC2_3 = 352,

    /* SPI */
    SPI0_SRRI   = 353,
    SPI0_SRTI   = 354,
    SPI0_SPII   = 355,
    SPI0_SPEI   = 356,
    SPI0_SPTEND = 357,

    /* INTSFTTRG */
    STRG = 358,

    /* Event port */
    IOPORT_TRG1 = 359,
    IOPORT_TRG2 = 360,
    IOPORT_TRG3 = 361,
    IOPORT_TRG4 = 362,

    /* TIMER4_0 */
    TMR4_U0_CMUH  = 363,
    TMR4_U0_CMUL  = 364,
    TMR4_U0_CMVH  = 365,
    TMR4_U0_CMVL  = 366,
    TMR4_U0_CMWH  = 367,
    TMR4_U0_CMWL  = 368,
    TMR4_U0_OVF   = 369,
    TMR4_U0_UDF   = 370,
    TMR4_U0_RLOU  = 371,
    TMR4_U0_RLOV  = 372,
    TMR4_U0_RLOW  = 373,
    TMR4_U0_EMI   = 374,
    TMR4_U0_ACMUH = 375,
    TMR4_U0_ACMUL = 376,
    TMR4_U0_ACMVH = 377,
    TMR4_U0_ACMVL = 378,
    TMR4_U0_ACMWH = 379,
    TMR4_U0_ACMWL = 380,

    /* TIMER4_1 */
    TMR4_U1_CMUH  = 381,
    TMR4_U1_CMUL  = 382,
    TMR4_U1_CMVH  = 383,
    TMR4_U1_CMVL  = 384,
    TMR4_U1_CMWH  = 385,
    TMR4_U1_CMWL  = 386,
    TMR4_U1_GOVF  = 387,
    TMR4_U1_UDF   = 388,
    TMR4_U1_LOU   = 389,
    TMR4_U1_RLOV  = 390,
    TMR4_U1_RLOW  = 391,
    TMR4_U1_EMI   = 392,
    TMR4_U1_ACMUH = 393,
    TMR4_U1_ACMUL = 394,
    TMR4_U1_ACMVH = 395,
    TMR4_U1_ACMVL = 396,
    TMR4_U1_ACMWH = 397,
    TMR4_U1_ACMWL = 398,

    /* USBHS */
    USBHS_GLB_INT = 399,
    HS_SOF_TRG    = 400,

    /* USBFS */
    USBFS_GLB_INT = 403,
    FS_SOF_TRG    = 404,

    /* ETHER */
    ETH_GLB_INT   = 407,
    ETH_WKP_INT   = 408,
    ETH_PPS_OUT_0 = 409,
    ETH_PPS_OUT_1 = 410,

    /* EMB */
    EMB_GR0 = 411,
    EMB_GR1 = 412,
    EMB_GR2 = 413,
    EMB_GR3 = 414,
    EMB_GR4 = 415,
    EMB_GR5 = 416,

    /* TRNG */
    TRNG_END = 420,

    /* ACMP */
    ACMP0 = 421,
    ACMP1 = 422,
    ACMP2 = 423,
    ACMP3 = 424,

    /* IIC0 */
    IIC0_RXI = 425,
    IIC0_TXI = 426,
    IIC0_TEI = 427,
    IIC0_EE1 = 428,
    IIC0_WUI = 429,

    /* FCM */
    FCMFERRI = 430,
    FCMMENDI = 431,
    FCMCOVFI = 432,

    /* WDT */
    WDT_NMIUNDF = 433,

    /* ADC120 */
    ADC120_EOCA_INT = 450,
    ADC120_EOCB_INT = 451,
    ADC120_AWD_INT  = 452,

    /* ADC121 */
    ADC121_EOCA_INT = 456,
    ADC121_EOCB_INT = 457,
    ADC121_AWD_INT  = 458,

    /* ADC122 */
    ADC122_EOCA_INT = 462,
    ADC122_EOCB_INT = 463,
    ADC122_AWD_INT  = 464,

    /* NFC */
    NFC_INT = 480,

}en_int_src_t;


typedef struct
{
    en_int_src_t enIntSrc;
    IRQn_Type enIRQn;
    func_ptr_t pfnCallback;
}stc_irq_regi_conf_t;


/*! Default Priority for IRQ, Possible values are 0 (high priority) to 15 (low priority) */
#define     DDL_IRQ_LEVEL_DEFAULT   15u

/*! External Int Ch.0~15 Priority */
#define     DDL_IRQ_LEVEL_EXTI00    15u
#define     DDL_IRQ_LEVEL_EXTI01    15u
#define     DDL_IRQ_LEVEL_EXTI02    15u
#define     DDL_IRQ_LEVEL_EXTI03    15u
#define     DDL_IRQ_LEVEL_EXTI04    15u
#define     DDL_IRQ_LEVEL_EXTI05    15u
#define     DDL_IRQ_LEVEL_EXTI06    15u
#define     DDL_IRQ_LEVEL_EXTI07    15u
#define     DDL_IRQ_LEVEL_EXTI08    15u
#define     DDL_IRQ_LEVEL_EXTI09    15u
#define     DDL_IRQ_LEVEL_EXTI10    15u
#define     DDL_IRQ_LEVEL_EXTI11    15u
#define     DDL_IRQ_LEVEL_EXTI12    15u
#define     DDL_IRQ_LEVEL_EXTI13    15u
#define     DDL_IRQ_LEVEL_EXTI14    15u
#define     DDL_IRQ_LEVEL_EXTI15    15u

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern en_result_t enIrqRegistration(stc_irq_regi_conf_t stcIrqRegiConf);

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
__WEAKDEF void Nmi_IrqHandler(void);
__WEAKDEF void MemManage_IrqHandler(void);
__WEAKDEF void BusFault_IrqHandler(void);
__WEAKDEF void UsageFault_IrqHandler(void);
__WEAKDEF void DebugMon_IrqHandler(void);


//@} // InterruptGroup

#ifdef __cplusplus
}
#endif

#endif /* __INTERRUPTS_HC32F480_H___ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
