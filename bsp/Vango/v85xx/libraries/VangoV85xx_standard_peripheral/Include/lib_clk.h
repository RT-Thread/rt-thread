/**
  ******************************************************************************
  * @file    lib_clk.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   Clock library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_CLK_H
#define __LIB_CLK_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"
   
/* PLLL Configure */
typedef struct
{
  uint32_t Source;
  uint32_t State;
  uint32_t Frequency;
} PLLL_ConfTypeDef;

/* PLLH Configure */
typedef struct
{
  uint32_t Source;
  uint32_t State;
  uint32_t Frequency;
} PLLH_ConfTypeDef;

/* RCH Configure */
typedef struct
{
  uint32_t State;
} RCH_ConfTypeDef;

/* XTALH Configure */
typedef struct
{
  uint32_t State;
} XTALH_ConfTypeDef;

/* RTCCLK Configure */
typedef struct
{
  uint32_t Source;
  uint32_t Divider;
} RTCCLK_ConfTypeDef;

/* HCLK Configure */
typedef struct
{
  uint32_t Divider;   /* 1 ~ 256 */
} HCLK_ConfTypeDef;

/* PCLK Configure */
typedef struct
{
  uint32_t Divider;   /* 1 ~ 256 */
} PCLK_ConfTypeDef;

/* Clock Configure */
typedef struct 
{
  uint32_t            ClockType;       /* The clock to be configured */ 
  
  uint32_t            AHBSource;
  
  PLLL_ConfTypeDef    PLLL;
  
  PLLH_ConfTypeDef    PLLH;
  
  XTALH_ConfTypeDef   XTALH;
  
  RTCCLK_ConfTypeDef  RTCCLK;
  
  HCLK_ConfTypeDef    HCLK;  
  
  PCLK_ConfTypeDef    PCLK;         
  
} CLK_InitTypeDef;

/*****  ClockType *****/
#define CLK_TYPE_Msk      (0xFFUL)
#define CLK_TYPE_ALL       CLK_TYPE_Msk
#define CLK_TYPE_AHBSRC   (0x01UL)   /* AHB Clock source to configure */
#define CLK_TYPE_PLLL     (0x02UL)   /* PLLL to configure */
#define CLK_TYPE_PLLH     (0x04UL)   /* PLLH to configure */
#define CLK_TYPE_XTALH    (0x08UL)   /* XTALH to configure */
#define CLK_TYPE_RTCCLK   (0x20UL)   /* RTCCLK to configure */
#define CLK_TYPE_HCLK     (0x40UL)   /* AHB Clock to configure */
#define CLK_TYPE_PCLK     (0x80UL)   /* APB Clock to configure */

/*****  AHBSource *****/
#define CLK_AHBSEL_6_5MRC     MISC2_CLKSEL_CLKSEL_RCOH
#define CLK_AHBSEL_6_5MXTAL   MISC2_CLKSEL_CLKSEL_XOH
#define CLK_AHBSEL_HSPLL      MISC2_CLKSEL_CLKSEL_PLLH
#define CLK_AHBSEL_RTCCLK     MISC2_CLKSEL_CLKSEL_RTCCLK
#define CLK_AHBSEL_LSPLL      MISC2_CLKSEL_CLKSEL_PLLL

/*****  PLLL_ConfTypeDef PLLL *****/
/* PLLL.Source */
#define CLK_PLLLSRC_RCL       PMU_CONTROL_PLLL_SEL
#define CLK_PLLLSRC_XTALL    (0)
/* PLLL.State */
#define CLK_PLLL_ON           ANA_REG3_PLLLPDN 
#define CLK_PLLL_OFF         (0) 
/* PLLL.Frequency */
#define CLK_PLLL_26_2144MHz   ANA_REG9_PLLLSEL_26M
#define CLK_PLLL_13_1072MHz   ANA_REG9_PLLLSEL_13M
#define CLK_PLLL_6_5536MHz    ANA_REG9_PLLLSEL_6_5M
#define CLK_PLLL_3_2768MHz    ANA_REG9_PLLLSEL_3_2M
#define CLK_PLLL_1_6384MHz    ANA_REG9_PLLLSEL_1_6M
#define CLK_PLLL_0_8192MHz    ANA_REG9_PLLLSEL_800K
#define CLK_PLLL_0_4096MHz    ANA_REG9_PLLLSEL_400K
#define CLK_PLLL_0_2048MHz    ANA_REG9_PLLLSEL_200K

/*****  PLLH_ConfTypeDef PLLH *****/
/* PLLH.Source */
#define CLK_PLLHSRC_RCH      (0)
#define CLK_PLLHSRC_XTALH     PMU_CONTROL_PLLH_SEL
/* PLLH.State */
#define CLK_PLLH_ON           ANA_REG3_PLLHPDN 
#define CLK_PLLH_OFF         (0) 
/* PLLH.Frequency */
#define CLK_PLLH_13_1072MHz       ANA_REG9_PLLHSEL_X2
#define CLK_PLLH_16_384MHz        ANA_REG9_PLLHSEL_X2_5
#define CLK_PLLH_19_6608MHz       ANA_REG9_PLLHSEL_X3
#define CLK_PLLH_22_9376MHz       ANA_REG9_PLLHSEL_X3_5
#define CLK_PLLH_26_2144MHz       ANA_REG9_PLLHSEL_X4
#define CLK_PLLH_29_4912MHz       ANA_REG9_PLLHSEL_X4_5
#define CLK_PLLH_32_768MHz        ANA_REG9_PLLHSEL_X5
#define CLK_PLLH_36_0448MHz       ANA_REG9_PLLHSEL_X5_5
#define CLK_PLLH_39_3216MHz       ANA_REG9_PLLHSEL_X6
#define CLK_PLLH_42_5984MHz       ANA_REG9_PLLHSEL_X6_5
#define CLK_PLLH_45_8752MHz       ANA_REG9_PLLHSEL_X7
#define CLK_PLLH_49_152MHz        ANA_REG9_PLLHSEL_X7_5

/* XTALH_ConfTypeDef XTALH */
/* XTALH.State */
#define CLK_XTALH_ON         ANA_REG3_XOHPDN
#define CLK_XTALH_OFF       (0)

/* RTCCLK Configure */
/* RTCCLK.Source */
#define CLK_RTCCLKSRC_XTALL     (0)
#define CLK_RTCCLKSRC_RCL       (PMU_CONTROL_RTCLK_SEL)
/* RTCCLK.Divider */
#define CLK_RTCCLKDIV_1         (RTC_PSCA_PSCA_0)
#define CLK_RTCCLKDIV_4         (RTC_PSCA_PSCA_1)

//AHB Periphral
#define CLK_AHBPERIPHRAL_DMA        MISC2_HCLKEN_DMA
#define CLK_AHBPERIPHRAL_GPIO       MISC2_HCLKEN_GPIO
#define CLK_AHBPERIPHRAL_LCD        MISC2_HCLKEN_LCD
#define CLK_AHBPERIPHRAL_CRYPT      MISC2_HCLKEN_CRYPT    
#define CLK_AHBPERIPHRAL_ALL       (MISC2_HCLKEN_DMA \
                                   |MISC2_HCLKEN_GPIO \
                                   |MISC2_HCLKEN_LCD \
                                   |MISC2_HCLKEN_CRYPT)

//APB Periphral  
#define CLK_APBPERIPHRAL_DMA        MISC2_PCLKEN_DMA       
#define CLK_APBPERIPHRAL_I2C        MISC2_PCLKEN_I2C       
#define CLK_APBPERIPHRAL_SPI1       MISC2_PCLKEN_SPI1      
#define CLK_APBPERIPHRAL_UART0      MISC2_PCLKEN_UART0     
#define CLK_APBPERIPHRAL_UART1      MISC2_PCLKEN_UART1     
#define CLK_APBPERIPHRAL_UART2      MISC2_PCLKEN_UART2     
#define CLK_APBPERIPHRAL_UART3      MISC2_PCLKEN_UART3     
#define CLK_APBPERIPHRAL_UART4      MISC2_PCLKEN_UART4     
#define CLK_APBPERIPHRAL_UART5      MISC2_PCLKEN_UART5     
#define CLK_APBPERIPHRAL_ISO78160   MISC2_PCLKEN_ISO78160     
#define CLK_APBPERIPHRAL_ISO78161   MISC2_PCLKEN_ISO78161     
#define CLK_APBPERIPHRAL_TIMER      MISC2_PCLKEN_TIMER     
#define CLK_APBPERIPHRAL_MISC       MISC2_PCLKEN_MISC      
#define CLK_APBPERIPHRAL_MISC2      MISC2_PCLKEN_MISC2 
#define CLK_APBPERIPHRAL_PMU        MISC2_PCLKEN_PMU       
#define CLK_APBPERIPHRAL_RTC        MISC2_PCLKEN_RTC       
#define CLK_APBPERIPHRAL_ANA        MISC2_PCLKEN_ANA       
#define CLK_APBPERIPHRAL_U32K0      MISC2_PCLKEN_U32K0     
#define CLK_APBPERIPHRAL_U32K1      MISC2_PCLKEN_U32K1 
#define CLK_APBPERIPHRAL_SPI2       MISC2_PCLKEN_SPI2 
#define CLK_APBPERIPHRAL_ALL       (MISC2_PCLKEN_DMA \
                                   |MISC2_PCLKEN_I2C \
                                   |MISC2_PCLKEN_SPI1 \
                                   |MISC2_PCLKEN_UART0 \
                                   |MISC2_PCLKEN_UART1 \
                                   |MISC2_PCLKEN_UART2 \
                                   |MISC2_PCLKEN_UART3 \
                                   |MISC2_PCLKEN_UART4 \
                                   |MISC2_PCLKEN_UART5 \
                                   |MISC2_PCLKEN_ISO78160 \
                                   |MISC2_PCLKEN_ISO78161 \
                                   |MISC2_PCLKEN_TIMER \
                                   |MISC2_PCLKEN_MISC \
                                   |MISC2_PCLKEN_MISC2 \
                                   |MISC2_PCLKEN_PMU \
                                   |MISC2_PCLKEN_RTC \
                                   |MISC2_PCLKEN_ANA \
                                   |MISC2_PCLKEN_U32K0 \
                                   |MISC2_PCLKEN_U32K1 \
                                   |MISC2_PCLKEN_SPI2)

/***** PLLStatus (CLK_GetPLLLockStatus) *****/
#define CLK_STATUS_LOCKL      ANA_COMPOUT_LOCKL
#define CLK_STATUS_LOCKH      ANA_COMPOUT_LOCKH


/* Private macros ------------------------------------------------------------*/
#define IS_CLK_TYPE(__TYPE__)   ((((__TYPE__) & CLK_TYPE_Msk) != 0UL) &&\
                                 (((__TYPE__) & ~CLK_TYPE_Msk) == 0UL))

#define IS_CLK_AHBSRC(__AHBSRC__)  (((__AHBSRC__) == CLK_AHBSEL_6_5MRC)   ||\
                                    ((__AHBSRC__) == CLK_AHBSEL_6_5MXTAL) ||\
                                    ((__AHBSRC__) == CLK_AHBSEL_HSPLL)    ||\
                                    ((__AHBSRC__) == CLK_AHBSEL_RTCCLK)   ||\
                                    ((__AHBSRC__) == CLK_AHBSEL_LSPLL))

#define IS_CLK_PLLLSRC(__PLLLSRC__)  (((__PLLLSRC__) == CLK_PLLLSRC_RCL) ||\
                                      ((__PLLLSRC__) == CLK_PLLLSRC_XTALL))

#define IS_CLK_PLLLSTA(__PLLLSTA__)  (((__PLLLSTA__) == CLK_PLLL_ON) ||\
                                      ((__PLLLSTA__) == CLK_PLLL_OFF))

#define IS_CLK_PLLLFRQ(__PLLLFRQ__)  (((__PLLLFRQ__) == CLK_PLLL_26_2144MHz) ||\
                                      ((__PLLLFRQ__) == CLK_PLLL_13_1072MHz) ||\
                                      ((__PLLLFRQ__) == CLK_PLLL_6_5536MHz)  ||\
                                      ((__PLLLFRQ__) == CLK_PLLL_3_2768MHz)  ||\
                                      ((__PLLLFRQ__) == CLK_PLLL_1_6384MHz)  ||\
                                      ((__PLLLFRQ__) == CLK_PLLL_0_8192MHz)  ||\
                                      ((__PLLLFRQ__) == CLK_PLLL_0_4096MHz)  ||\
                                      ((__PLLLFRQ__) == CLK_PLLL_0_2048MHz))

#define IS_CLK_PLLHSRC(__PLLHSRC__)  (((__PLLHSRC__) == CLK_PLLHSRC_RCH) ||\
                                      ((__PLLHSRC__) == CLK_PLLHSRC_XTALH))

#define IS_CLK_PLLHSTA(__PLLHSTA__)  (((__PLLHSTA__) == CLK_PLLH_ON) ||\
                                      ((__PLLHSTA__) == CLK_PLLH_OFF))

#define IS_CLK_PLLHFRQ(__PLLHSRC__)  (((__PLLHSRC__) == CLK_PLLH_13_1072MHz) ||\
                                      ((__PLLHSRC__) == CLK_PLLH_16_384MHz)  ||\
                                      ((__PLLHSRC__) == CLK_PLLH_19_6608MHz) ||\
                                      ((__PLLHSRC__) == CLK_PLLH_22_9376MHz) ||\
                                      ((__PLLHSRC__) == CLK_PLLH_26_2144MHz) ||\
                                      ((__PLLHSRC__) == CLK_PLLH_29_4912MHz) ||\
                                      ((__PLLHSRC__) == CLK_PLLH_32_768MHz)  ||\
                                      ((__PLLHSRC__) == CLK_PLLH_36_0448MHz) ||\
                                      ((__PLLHSRC__) == CLK_PLLH_39_3216MHz) ||\
                                      ((__PLLHSRC__) == CLK_PLLH_42_5984MHz) ||\
                                      ((__PLLHSRC__) == CLK_PLLH_45_8752MHz) ||\
                                      ((__PLLHSRC__) == CLK_PLLH_49_152MHz))

#define IS_CLK_XTALHSTA(__XTALHSTA__)  (((__XTALHSTA__) == CLK_XTALH_ON) ||\
                                        ((__XTALHSTA__) == CLK_XTALH_OFF))

#define IS_CLK_RTCSRC(__RTCSRC__)  (((__RTCSRC__) == CLK_RTCCLKSRC_XTALL) ||\
                                    ((__RTCSRC__) == CLK_RTCCLKSRC_RCL))

#define IS_CLK_RTCDIV(__RTCDIV__)  (((__RTCDIV__) == CLK_RTCCLKDIV_1) ||\
                                    ((__RTCDIV__) == CLK_RTCCLKDIV_4))

#define IS_CLK_HCLKDIV(__HCLKDIV__)  (((__HCLKDIV__) > 0UL) &&\
                                      ((__HCLKDIV__) < 257UL))

#define IS_CLK_PCLKDIV(__PCLKDIV__)  (((__PCLKDIV__) > 0UL) &&\
                                      ((__PCLKDIV__) < 257UL))

#define IS_CLK_AHBPERIPHRAL(__AHBPERIPHRAL__)  ((((__AHBPERIPHRAL__) & CLK_AHBPERIPHRAL_ALL) != 0UL) &&\
                                                (((__AHBPERIPHRAL__) & ~CLK_AHBPERIPHRAL_ALL) == 0UL))

#define IS_CLK_APBPERIPHRAL(__APBPERIPHRAL__)  ((((__APBPERIPHRAL__) & CLK_APBPERIPHRAL_ALL) != 0UL) &&\
                                                (((__APBPERIPHRAL__) & ~CLK_APBPERIPHRAL_ALL) == 0UL))

#define IS_CLK_PLLLOCK(__PLLLOCK__)  (((__PLLLOCK__) == ANA_COMPOUT_LOCKL) ||\
                                      ((__PLLLOCK__) == ANA_COMPOUT_LOCKH))
/* Exported Functions ------------------------------------------------------- */
/* CLK Exported Functions Group1: 
                                  Initialization and functions ---------------*/
void CLK_ClockConfig(CLK_InitTypeDef *CLK_ClkInitStruct);

/* CLK Exported Functions Group2: 
                                  Peripheral Control -------------------------*/
void CLK_AHBPeriphralCmd(uint32_t Periphral, uint32_t NewState);
void CLK_APBPeriphralCmd(uint32_t Periphral, uint32_t NewState);
/* CLK Exported Functions Group3: 
                                  Get clock/configuration information --------*/
uint32_t CLK_GetHCLKFreq(void);
uint32_t CLK_GetPCLKFreq(void);
void CLK_GetClockConfig(CLK_InitTypeDef *CLK_ClkInitStruct);
uint8_t CLK_GetXTALHStatus(void);
uint8_t CLK_GetXTALLStatus(void);
uint8_t CLK_GetPLLLockStatus(uint32_t PLLStatus);

#ifdef __cplusplus
}
#endif
     
#endif /* __LIB_CLK_H */

/*********************************** END OF FILE ******************************/
