/**
  ******************************************************************************
  * @file    lib_pmu.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   PMU library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_PMU_H
#define __LIB_PMU_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

/**
  * Deep-sleep low-power configuration
*/
typedef struct
{
  uint32_t COMP1Power;           /* Comparator 1 power control */
  uint32_t COMP2Power;           /* Comparator 2 power control */
  uint32_t TADCPower;            /* Tiny ADC power control */
  uint32_t BGPPower;             /* BGP power control */
  uint32_t AVCCPower;            /* AVCC power control */
//  uint32_t LCDPower;             /* LCD controller power control */
  uint32_t VDCINDetector;        /* VDCIN detector control */
  uint32_t VDDDetector;          /* VDD detector control */
  uint32_t AHBPeriphralDisable;  /* AHB Periphral clock disable selection */
  uint32_t APBPeriphralDisable;  /* APB Periphral clock disable selection */
} PMU_LowPWRTypeDef; 

/**************  Bits definition for ANA_REG8 register       ******************/
#define ANA_REG8_VDDPVDSEL_0         (0x0UL << ANA_REG8_VDDPVDSEL_Pos)   
#define ANA_REG8_VDDPVDSEL_1         (0x1UL << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_2         (0x2UL << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_3         (0x3UL << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_4         (0x4UL << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_5         (0x5UL << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_6         (0x6UL << ANA_REG8_VDDPVDSEL_Pos)
#define ANA_REG8_VDDPVDSEL_7         (0x7UL << ANA_REG8_VDDPVDSEL_Pos)

/****************************** PMU Instances *********************************/
#define IS_PMU_ALL_INSTANCE(INSTANCE) ((INSTANCE) == PMU)

/****************************** PMU_RETRAM Instances **************************/
#define IS_PMU_RETRAM_ALL_INSTANCE(INSTANCE) ((INSTANCE) == PMU_RETRAM)

/* COMP1Power */
#define PMU_COMP1PWR_ON         (ANA_REG3_CMP1PDN)
#define PMU_COMP1PWR_OFF        (0UL)
#define IS_PMU_COMP1PWR(__COMP1PWR__)  (((__COMP1PWR__) == PMU_COMP1PWR_ON) ||\
                                        ((__COMP1PWR__) == PMU_COMP1PWR_OFF))
/* COMP2Power */
#define PMU_COMP2PWR_ON         (ANA_REG3_CMP2PDN)
#define PMU_COMP2PWR_OFF        (0UL)
#define IS_PMU_COMP2PWR(__COMP2PWR__)  (((__COMP2PWR__) == PMU_COMP2PWR_ON) ||\
                                        ((__COMP2PWR__) == PMU_COMP2PWR_OFF))
/* TADCPower */
#define PMU_TADCPWR_ON          (ANA_REGF_ADTPDN)
#define PMU_TADCPWR_OFF         (0UL)
#define IS_PMU_TADCPWR(__TADCPWR__)  (((__TADCPWR__) == PMU_TADCPWR_ON) ||\
                                      ((__TADCPWR__) == PMU_TADCPWR_OFF))
/* BGPPower */
#define PMU_BGPPWR_ON           (0UL)
#define PMU_BGPPWR_OFF          (ANA_REG3_BGPPD)
#define IS_PMU_BGPPWR(__BGPPWR__)  (((__BGPPWR__) == PMU_BGPPWR_ON) ||\
                                    ((__BGPPWR__) == PMU_BGPPWR_OFF))
/* AVCCPower */
#define PMU_AVCCPWR_ON         (0UL)
#define PMU_AVCCPWR_OFF        (ANA_REG8_AVCCLDOPD)
#define IS_PMU_AVCCPWR(__AVCCPWR__)  (((__AVCCPWR__) == PMU_AVCCPWR_ON) ||\
                                        ((__AVCCPWR__) == PMU_AVCCPWR_OFF))

/* VDCINDetector */
#define PMU_VDCINDET_ENABLE     (0UL)
#define PMU_VDCINDET_DISABLE    (ANA_REGA_VDCINDETPD)
#define IS_PMU_VDCINDET(__VDCINDET__)  (((__VDCINDET__) == PMU_VDCINDET_ENABLE) ||\
                                        ((__VDCINDET__) == PMU_VDCINDET_DISABLE)) 

/* VDDDetector */
#define PMU_VDDDET_ENABLE       (0UL)
#define PMU_VDDDET_DISABLE      (ANA_REG9_VDDDETPD)
#define IS_PMU_VDDDET(__VDDDET__)  (((__VDDDET__) == PMU_VDDDET_ENABLE) ||\
                                    ((__VDDDET__) == PMU_VDDDET_DISABLE))

#define PMU_APB_ALL       (MISC2_PCLKEN_DMA      \
                          |MISC2_PCLKEN_I2C      \
                          |MISC2_PCLKEN_SPI1     \
                          |MISC2_PCLKEN_UART0    \
                          |MISC2_PCLKEN_UART1    \
                          |MISC2_PCLKEN_UART2    \
                          |MISC2_PCLKEN_UART3    \
                          |MISC2_PCLKEN_UART4    \
                          |MISC2_PCLKEN_UART5    \
                          |MISC2_PCLKEN_ISO78160 \
                          |MISC2_PCLKEN_ISO78161 \
                          |MISC2_PCLKEN_TIMER    \
                          |MISC2_PCLKEN_MISC1    \
                          |MISC2_PCLKEN_MISC2    \
                          |MISC2_PCLKEN_U32K0    \
                          |MISC2_PCLKEN_U32K1    \
                          |MISC2_PCLKEN_SPI2     \
                          |MISC2_PCLKEN_SPI3)
#define PMU_APB_DMA        MISC2_PCLKEN_DMA       
#define PMU_APB_I2C        MISC2_PCLKEN_I2C       
#define PMU_APB_SPI1       MISC2_PCLKEN_SPI1      
#define PMU_APB_UART0      MISC2_PCLKEN_UART0     
#define PMU_APB_UART1      MISC2_PCLKEN_UART1     
#define PMU_APB_UART2      MISC2_PCLKEN_UART2     
#define PMU_APB_UART3      MISC2_PCLKEN_UART3     
#define PMU_APB_UART4      MISC2_PCLKEN_UART4     
#define PMU_APB_UART5      MISC2_PCLKEN_UART5     
#define PMU_APB_ISO78160   MISC2_PCLKEN_ISO78160     
#define PMU_APB_ISO78161   MISC2_PCLKEN_ISO78161     
#define PMU_APB_TIMER      MISC2_PCLKEN_TIMER     
#define PMU_APB_MISC1      MISC2_PCLKEN_MISC1                         
#define PMU_APB_U32K0      MISC2_PCLKEN_U32K0     
#define PMU_APB_U32K1      MISC2_PCLKEN_U32K1 
#define PMU_APB_SPI2       MISC2_PCLKEN_SPI2
#define PMU_APB_SPI3       MISC2_PCLKEN_SPI3

#define PMU_AHB_ALL       (MISC2_HCLKEN_DMA     \
                          |MISC2_HCLKEN_GPIO    \
                          |MISC2_HCLKEN_CRYPT)
//                          |MISC2_HCLKEN_LCD     
#define PMU_AHB_DMA        MISC2_HCLKEN_DMA
#define PMU_AHB_GPIO       MISC2_HCLKEN_GPIO
//#define PMU_AHB_LCD        MISC2_HCLKEN_LCD
#define PMU_AHB_CRYPT      MISC2_HCLKEN_CRYPT   
   
//PMU interrupt
#define PMU_INT_IOAEN   PMU_CONTROL_INT_IOA_EN
#define PMU_INT_32K     PMU_CONTROL_INT_32K_EN
#define PMU_INT_6M      PMU_CONTROL_INT_6M_EN
#define PMU_INT_Msk     (PMU_INT_IOAEN  \
                         |PMU_INT_32K \
                         |PMU_INT_6M)
#define IS_PMU_INT(__INT__)  ((((__INT__)&PMU_INT_Msk) != 0UL) &&\
                              (((__INT__)&(~PMU_INT_Msk)) == 0UL))

//INTStatus
#define PMU_INTSTS_32K      PMU_STS_INT_32K
#define PMU_INTSTS_6M       PMU_STS_INT_6M
#define PMU_INTSTS_Msk      (PMU_INTSTS_32K    \
                            |PMU_INTSTS_6M)
#define IS_PMU_INTFLAGR(__INTFLAG__)  (((__INTFLAG__) == PMU_INTSTS_32K)    ||\
                                       ((__INTFLAG__) == PMU_INTSTS_6M))

#define IS_PMU_INTFLAGC(__INTFLAG__)  ((((__INTFLAG__)&PMU_INTSTS_Msk) != 0UL) &&\
                                       (((__INTFLAG__)&(~PMU_INTSTS_Msk)) == 0UL))

/***** Reset Source Status  *****/
#define PMU_RSTSRC_EXTRST        PMU_STS_EXTRST
#define PMU_RSTSRC_PORST         PMU_STS_PORST
#define PMU_RSTSRC_DPORST        PMU_STS_DPORST
#define PMU_RSTSRC_WDTRST        PMU_STS_WDTRST
#define PMU_RSTSRC_SFTRST        PMU_STS_SFTRST
#define PMU_RSTSRC_MODERST       PMU_STS_MODERST
#define PMU_RSTSRC_Msk          (PMU_RSTSRC_EXTRST |\
                                 PMU_RSTSRC_PORST  |\
                                 PMU_RSTSRC_DPORST |\
                                 PMU_RSTSRC_WDTRST |\
                                 PMU_RSTSRC_SFTRST |\
                                 PMU_RSTSRC_MODERST)
#define PMU_RSTSRC_ALL           PMU_RSTSRC_Msk 
#define PMU_RESETSRC(__RSTSRC__)  (((__RSTSRC__) == PMU_RSTSRC_EXTRST) ||\
                                   ((__RSTSRC__) == PMU_RSTSRC_PORST)  ||\
                                   ((__RSTSRC__) == PMU_RSTSRC_DPORST) ||\
                                   ((__RSTSRC__) == PMU_RSTSRC_WDTRST) ||\
                                   ((__RSTSRC__) == PMU_RSTSRC_SFTRST) ||\
                                   ((__RSTSRC__) == PMU_RSTSRC_MODERST))
#define PMU_RESETSRC_CLR(__RSTSRC__)  ((((__RSTSRC__) & PMU_RSTSRC_Msk) != 0UL) &&\
                                       (((__RSTSRC__) & (~PMU_RSTSRC_Msk)) == 0UL))

/***** DeepSleep wakeup Source Status  *****/
#define PMU_DSLEEPWKUSRC_MODE  PMU_STS_WKUMODE
#define PMU_DSLEEPWKUSRC_XTAL  PMU_STS_WKUXTAL
#define PMU_DSLEEPWKUSRC_U32K  PMU_STS_WKUU32K
#define PMU_DSLEEPWKUSRC_ANA   PMU_STS_WKUANA
#define PMU_DSLEEPWKUSRC_RTC   PMU_STS_WKURTC
#define PMU_DSLEEPWKUSRC_IOA   PMU_STS_WKUIOA
#define PMU_DSLEEPWKUSRC_Msk  (PMU_DSLEEPWKUSRC_MODE |\
                               PMU_DSLEEPWKUSRC_XTAL |\
                               PMU_DSLEEPWKUSRC_U32K |\
                               PMU_DSLEEPWKUSRC_ANA  |\
                               PMU_DSLEEPWKUSRC_RTC  |\
                               PMU_DSLEEPWKUSRC_IOA)
#define IS_PMU_DSLEEPWKUSRC(__SRC__)  (((__SRC__) == PMU_DSLEEPWKUSRC_MODE) ||\
                                       ((__SRC__) == PMU_DSLEEPWKUSRC_XTAL) ||\
                                       ((__SRC__) == PMU_DSLEEPWKUSRC_U32K) ||\
                                       ((__SRC__) == PMU_DSLEEPWKUSRC_ANA)  ||\
                                       ((__SRC__) == PMU_DSLEEPWKUSRC_RTC)  ||\
                                       ((__SRC__) == PMU_DSLEEPWKUSRC_IOA))


//Status
#define PMU_STS_32K     PMU_STS_EXIST_32K
#define PMU_STS_6M      PMU_STS_EXIST_6M
#define IS_PMU_FLAG(__FLAG__)  (((__FLAG__) == PMU_STS_32K) || ((__FLAG__) == PMU_STS_6M))

//Wakeup_Event
#define IOA_DISABLE     (0UL)
#define IOA_RISING      (1UL)
#define IOA_FALLING     (2UL)
#define IOA_HIGH        (3UL)
#define IOA_LOW         (4UL)
#define IOA_EDGEBOTH    (5UL)
#define IS_PMU_WAKEUP(__WAKEUP__)  (((__WAKEUP__) == IOA_DISABLE)     ||\
                                    ((__WAKEUP__) == IOA_RISING)  ||\
                                    ((__WAKEUP__) == IOA_FALLING) ||\
                                    ((__WAKEUP__) == IOA_HIGH)    ||\
                                    ((__WAKEUP__) == IOA_LOW)     ||\
                                    ((__WAKEUP__) == IOA_EDGEBOTH)) 

/***** Wakeup_Event (PMU_SleepWKUSRCConfig_RTC) *****/
#define PMU_RTCEVT_ALARM      RTC_INTSTS_INTSTS10
#define PMU_RTCEVT_WKUCNT     RTC_INTSTS_INTSTS6
#define PMU_RTCEVT_MIDNIGHT   RTC_INTSTS_INTSTS5
#define PMU_RTCEVT_WKUHOUR    RTC_INTSTS_INTSTS4
#define PMU_RTCEVT_WKUMIN     RTC_INTSTS_INTSTS3
#define PMU_RTCEVT_WKUSEC     RTC_INTSTS_INTSTS2
#define PMU_RTCEVT_TIMEILLE   RTC_INTSTS_INTSTS1
#define PMU_RTCEVT_ITVSITV    RTC_INTSTS_INTSTS0
#define PMU_RTCEVT_Msk         (PMU_RTCEVT_WKUCNT   \
                               |PMU_RTCEVT_MIDNIGHT \
                               |PMU_RTCEVT_WKUHOUR  \
                               |PMU_RTCEVT_WKUMIN   \
                               |PMU_RTCEVT_WKUSEC   \
                               |PMU_RTCEVT_TIMEILLE \
                               |PMU_RTCEVT_ITVSITV  \
                               |PMU_RTCEVT_ALARM)
#define IS_PMU_RTCEVT(__RTCEVT__)  ((((__RTCEVT__)&PMU_RTCEVT_Msk) != 0UL) &&\
                                    (((__RTCEVT__)&(~PMU_RTCEVT_Msk)) == 0UL))                              


/***** BATRTCDisc (PMU_BATDischargeConfig) *****/
#define PMU_BAT1     ANA_REG6_BAT1DISC
#define PMU_BATRTC   ANA_REG6_BATRTCDISC
#define IS_PMU_BATRTCDISC(__BATRTCDISC__)  (((__BATRTCDISC__) == PMU_BAT1) || ((__BATRTCDISC__) == PMU_BATRTC))

/***** PowerThreshold (PMU_PowerAlarmTHConfig) *****/
#define PMU_VDDALARM_4_5V      ANA_REG8_VDDPVDSEL_0
#define PMU_VDDALARM_4_2V      ANA_REG8_VDDPVDSEL_1
#define PMU_VDDALARM_3_9V      ANA_REG8_VDDPVDSEL_2
#define PMU_VDDALARM_3_6V      ANA_REG8_VDDPVDSEL_3
#define PMU_VDDALARM_3_2V      ANA_REG8_VDDPVDSEL_4
#define PMU_VDDALARM_2_9V      ANA_REG8_VDDPVDSEL_5
#define PMU_VDDALARM_2_6V      ANA_REG8_VDDPVDSEL_6
#define PMU_VDDALARM_2_3V      ANA_REG8_VDDPVDSEL_7

#define IS_PMU_VDDALARM_THR(__VDDALARM__)  (((__VDDALARM__) == PMU_VDDALARM_4_5V) ||\
                                            ((__VDDALARM__) == PMU_VDDALARM_4_2V) ||\
                                            ((__VDDALARM__) == PMU_VDDALARM_3_9V) ||\
                                            ((__VDDALARM__) == PMU_VDDALARM_3_6V) ||\
                                            ((__VDDALARM__) == PMU_VDDALARM_3_2V) ||\
                                            ((__VDDALARM__) == PMU_VDDALARM_2_9V) ||\
                                            ((__VDDALARM__) == PMU_VDDALARM_2_6V) ||\
                                            ((__VDDALARM__) == PMU_VDDALARM_2_3V))

/***** RTCLDOSel (PMU_RTCLDOConfig) *****/
#define PMU_RTCLDO_1_5         (0UL)
#define PMU_RTCLDO_1_2          ANA_REGA_RTCVSEL

/***** StatusMask (PMU_GetPowerStatus) *****/
#define PMU_PWRSTS_AVCCLV         ANA_COMPOUT_AVCCLV
#define PMU_PWRSTS_VDCINDROP      ANA_CMPOUT_VDCINDROP
#define PMU_PWRSTS_VDDALARM       ANA_CMPOUT_VDDALARM

/***** PMU_PDNDSleepConfig *****/
//VDCIN_PDNS
#define PMU_VDCINPDNS_0  (0UL)
#define PMU_VDCINPDNS_1  (ANA_CTRL_PDNS)
#define IS_PMU_VDCINPDNS(__VDCINPDNS__)  (((__VDCINPDNS__) == PMU_VDCINPDNS_0) ||\
                                          ((__VDCINPDNS__) == PMU_VDCINPDNS_1))
//VDD_PDNS
#define PMU_VDDPDNS_0  (0UL)
#define PMU_VDDPDNS_1  (ANA_CTRL_PDNS2)
#define IS_PMU_VDDPDNS(__VDDPDNS__)  (((__VDDPDNS__) == PMU_VDDPDNS_0) ||\
                                        ((__VDDPDNS__) == PMU_VDDPDNS_1))

#define PMU_VDDALARM_CHKFRE_NOCHECK    (0x0UL << ANA_CMPCTL_VDDALARM_CHK_FRQ_SEL_Pos)
#define PMU_VDDALARM_CHKFRE_30US       (0x1UL << ANA_CMPCTL_VDDALARM_CHK_FRQ_SEL_Pos)
#define IS_PMU_VDDALARM_CHKFRE(__CHKFRE__)  (((__CHKFRE__) == PMU_VDDALARM_CHKFRE_NOCHECK) ||\
                                          ((__CHKFRE__) == PMU_VDDALARM_CHKFRE_30US))

#define IS_PMU_PWR_DEBSEL(__DEBSEL__)  ((__DEBSEL__) < 256UL)

/* Exported Functions ------------------------------------------------------- */

uint32_t PMU_EnterDSleepMode(void);
void PMU_EnterIdleMode(void);
uint32_t PMU_EnterSleepMode(void);

void PMU_INTConfig(uint32_t INTMask, uint32_t NewState);
uint8_t PMU_GetINTStatus(uint32_t INTMask);
void PMU_ClearINTStatus(uint32_t INTMask);

uint8_t PMU_GetCrystalStatus(uint32_t Mask);
uint16_t PMU_GetIOAAllINTStatus(void);
uint8_t PMU_GetIOAINTStatus(uint16_t INTMask);
void PMU_ClearIOAINTStatus(uint16_t INTMask);

void PMU_WakeUpPinConfig(uint32_t IOAx, uint32_t Wakeup_Event);

uint8_t PMU_EnterDSleep_LowPower(PMU_LowPWRTypeDef *InitStruct);
uint8_t PMU_EnterSleep_LowPower(PMU_LowPWRTypeDef *InitStruct);
#ifndef __GNUC__
void PMU_EnterIdle_LowPower(void);
#endif
void PMU_SleepWKUSRCConfig_IOA(uint16_t IOAx, uint32_t Wakeup_Event, uint32_t Priority);
void PMU_SleepWKUSRCConfig_RTC(uint32_t Wakeup_Event, uint32_t Priority);
void PMU_DeepSleepWKUSRCConfig_IOA(uint16_t IOAx, uint32_t Wakeup_Event);
void PMU_DeepSleepWKUSRCConfig_RTC(uint32_t Wakeup_Event);
void PMU_PDNDSleepConfig(uint32_t VDCIN_PDNS, uint32_t VDD_PDNS);

/***** BGP functions *****/
void PMU_BGPCmd(uint32_t NewState);

/***** VDD functions *****/
void PMU_VDDAlarmConfig(uint32_t CheckTHR, uint32_t CheckFrequency);
uint8_t PMU_GetVDDAlarmStatus(void);

/***** AVCC functions *****/
void PMU_AVCCCmd(uint32_t NewState);
void PMU_AVCCOutputCmd(uint32_t NewState);
void PMU_AVCCLVDetectorCmd(uint32_t NewState);
uint8_t PMU_GetAVCCLVStatus(void);

/***** VDCIN functions *****/
void PMU_VDCINDetectorCmd(uint32_t NewState);
uint8_t PMU_GetVDCINDropStatus(void);

void PMU_PWRDEBSel(uint32_t DEBSel);

/***** BAT functions *****/
void PMU_BATDischargeConfig(uint32_t BATDisc, uint32_t NewState);

/***** Other functions *****/
uint8_t PMU_GetModeStatus(void);
uint8_t PMU_GetPowerStatus(uint32_t StatusMask);

uint8_t PMU_GetResetSource(uint32_t Mask);
void PMU_ClearResetSource(uint32_t Mask);
uint32_t PMU_GetAllResetSource(void);

uint8_t PMU_GetDSleepWKUSource(uint32_t Mask);
uint32_t PMU_GetAllDSleepWKUSource(void);
 
#ifdef __cplusplus
}
#endif
     
#endif /* __LIB_PMU_H */

/*********************************** END OF FILE ******************************/
