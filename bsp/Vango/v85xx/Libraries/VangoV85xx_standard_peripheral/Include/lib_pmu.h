/**
  ******************************************************************************
  * @file    lib_pmu.h 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
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
  uint32_t LCDPower;             /* LCD controller power control */
  uint32_t VDCINDetector;        /* VDCIN detector control */
  uint32_t VDDDetector;          /* VDD detector control */
  uint32_t AHBPeriphralDisable;  /* AHB Periphral clock disable selection */
  uint32_t APBPeriphralDisable;  /* APB Periphral clock disable selection */
} PMU_LowPWRTypeDef; 


/* COMP1Power */
#define PMU_COMP1PWR_ON         (ANA_REG3_CMP1PDN)
#define PMU_COMP1PWR_OFF        (0)
#define IS_PMU_COMP1PWR(__COMP1PWR__)  (((__COMP1PWR__) == PMU_COMP1PWR_ON) ||\
                                        ((__COMP1PWR__) == PMU_COMP1PWR_OFF))
/* COMP2Power */
#define PMU_COMP2PWR_ON         (ANA_REG3_CMP2PDN)
#define PMU_COMP2PWR_OFF        (0)
#define IS_PMU_COMP2PWR(__COMP2PWR__)  (((__COMP2PWR__) == PMU_COMP2PWR_ON) ||\
                                        ((__COMP2PWR__) == PMU_COMP2PWR_OFF))
/* TADCPower */
#define PMU_TADCPWR_ON          (ANA_REGF_PDNADT)
#define PMU_TADCPWR_OFF         (0)
#define IS_PMU_TADCPWR(__TADCPWR__)  (((__TADCPWR__) == PMU_TADCPWR_ON) ||\
                                      ((__TADCPWR__) == PMU_TADCPWR_OFF))
/* BGPPower */
#define PMU_BGPPWR_ON           (0)
#define PMU_BGPPWR_OFF          (ANA_REG3_BGPPD)
#define IS_PMU_BGPPWR(__BGPPWR__)  (((__BGPPWR__) == PMU_BGPPWR_ON) ||\
                                    ((__BGPPWR__) == PMU_BGPPWR_OFF))
/* AVCCPower */
#define PMU_AVCCPWR_ON         (0)
#define PMU_AVCCPWR_OFF        (ANA_REG8_PD_AVCCLDO)
#define IS_PMU_AVCCPWR(__AVCCPWR__)  (((__AVCCPWR__) == PMU_AVCCPWR_ON) ||\
                                        ((__AVCCPWR__) == PMU_AVCCPWR_OFF))
/* LCDPower */
#define PMU_LCDPWER_ON          (LCD_CTRL_EN)
#define PMU_LCDPWER_OFF         (0)
#define IS_PMU_LCDPWER(__LCDPWER__)  (((__LCDPWER__) == PMU_LCDPWER_ON) ||\
                                      ((__LCDPWER__) == PMU_LCDPWER_OFF))
/* VDCINDetector */
#define PMU_VDCINDET_ENABLE     (0)
#define PMU_VDCINDET_DISABLE    (ANA_REGA_PD_VDCINDET)
#define IS_PMU_VDCINDET(__VDCINDET__)  (((__VDCINDET__) == PMU_VDCINDET_ENABLE) ||\
                                        ((__VDCINDET__) == PMU_VDCINDET_DISABLE)) 

/* VDDDetector */
#define PMU_VDDDET_ENABLE       (0)
#define PMU_VDDDET_DISABLE      (ANA_REG9_PDDET)
#define IS_PMU_VDDDET(__VDDDET__)  (((__VDDDET__) == PMU_VDDDET_ENABLE) ||\
                                    ((__VDDDET__) == PMU_VDDDET_DISABLE))

/* APBPeriphralDisable */
#define PMU_APB_ALL       (MISC2_PCLKEN_DMA     \
                          |MISC2_PCLKEN_I2C     \
                          |MISC2_PCLKEN_SPI1    \
                          |MISC2_PCLKEN_UART0   \
                          |MISC2_PCLKEN_UART1   \
                          |MISC2_PCLKEN_UART2   \
                          |MISC2_PCLKEN_UART3   \
                          |MISC2_PCLKEN_UART4   \
                          |MISC2_PCLKEN_UART5   \
                          |MISC2_PCLKEN_ISO78160\
                          |MISC2_PCLKEN_ISO78161\
                          |MISC2_PCLKEN_TIMER   \
                          |MISC2_PCLKEN_MISC    \
                          |MISC2_PCLKEN_U32K0   \
                          |MISC2_PCLKEN_U32K1   \
                          |MISC2_PCLKEN_SPI2)   
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
#define PMU_APB_MISC       MISC2_PCLKEN_MISC                         
#define PMU_APB_U32K0      MISC2_PCLKEN_U32K0     
#define PMU_APB_U32K1      MISC2_PCLKEN_U32K1 
#define PMU_APB_SPI2       MISC2_PCLKEN_SPI2
/* AHBPeriphralDisable */
#define PMU_AHB_ALL       (MISC2_HCLKEN_DMA     \
                          |MISC2_HCLKEN_GPIO    \
                          |MISC2_HCLKEN_LCD     \
                          |MISC2_HCLKEN_CRYPT)
#define PMU_AHB_DMA        MISC2_HCLKEN_DMA
#define PMU_AHB_GPIO       MISC2_HCLKEN_GPIO
#define PMU_AHB_LCD        MISC2_HCLKEN_LCD
#define PMU_AHB_CRYPT      MISC2_HCLKEN_CRYPT   
   
//PMU interrupt
#define PMU_INT_IOAEN   PMU_CONTROL_INT_IOA_EN
#define PMU_INT_32K     PMU_CONTROL_INT_32K_EN
#define PMU_INT_6M      PMU_CONTROL_INT_6M_EN
#define PMU_INT_Msk     (PMU_INT_IOAEN  \
                         |PMU_INT_32K \
                         |PMU_INT_6M)
#define IS_PMU_INT(__INT__)  ((((__INT__)&PMU_INT_Msk) != 0U) &&\
                              (((__INT__)&(~PMU_INT_Msk)) == 0U))
   
//INTStatus
#define PMU_INTSTS_32K      PMU_STS_INT_32K
#define PMU_INTSTS_6M       PMU_STS_INT_6M
#define PMU_INTSTS_EXTRST   PMU_STS_EXTRST
#define PMU_INTSTS_PORST    PMU_STS_PORST
#define PMU_INTSTS_DPORST   PMU_STS_DPORST
#define PMU_INTSTS_Msk      (PMU_INTSTS_32K    \
                            |PMU_INTSTS_6M     \
                            |PMU_INTSTS_EXTRST \
                            |PMU_INTSTS_PORST  \
                            |PMU_INTSTS_DPORST)
#define IS_PMU_INTFLAGR(__INTFLAG__)  (((__INTFLAG__) == PMU_INTSTS_32K)   ||\
                                      ((__INTFLAG__) == PMU_INTSTS_6M)     ||\
                                      ((__INTFLAG__) == PMU_INTSTS_EXTRST) ||\
                                      ((__INTFLAG__) == PMU_INTSTS_PORST)  ||\
                                      ((__INTFLAG__) == PMU_INTSTS_DPORST))                        

#define IS_PMU_INTFLAGC(__INTFLAG__)  ((((__INTFLAG__)&PMU_INTSTS_Msk) != 0U) &&\
                                       (((__INTFLAG__)&(~PMU_INTSTS_Msk)) == 0U))
  


//Status
#define PMU_STS_32K     PMU_STS_EXIST_32K
#define PMU_STS_6M      PMU_STS_EXIST_6M
#define IS_PMU_FLAG(__FLAG__)  (((__FLAG__) == PMU_STS_32K) || ((__FLAG__) == PMU_STS_6M))

//Wakeup_Event
#define IOA_DISABLE     (0)
#define IOA_RISING      (1)
#define IOA_FALLING     (2)
#define IOA_HIGH        (3)
#define IOA_LOW         (4)
#define IOA_EDGEBOTH    (5)
#define IS_PMU_WAKEUP(__WAKEUP__)  (((__WAKEUP__) == IOA_DISABLE)     ||\
                                    ((__WAKEUP__) == IOA_RISING)  ||\
                                    ((__WAKEUP__) == IOA_FALLING) ||\
                                    ((__WAKEUP__) == IOA_HIGH)    ||\
                                    ((__WAKEUP__) == IOA_LOW)     ||\
                                    ((__WAKEUP__) == IOA_EDGEBOTH)) 

/***** Wakeup_Event (PMU_SleepWKUSRC_Config_RTC) *****/
#define PMU_RTCEVT_ACDONE     RTC_INTSTS_INTSTS7
#define PMU_RTCEVT_WKUCNT     RTC_INTSTS_INTSTS6
#define PMU_RTCEVT_MIDNIGHT   RTC_INTSTS_INTSTS5
#define PMU_RTCEVT_WKUHOUR    RTC_INTSTS_INTSTS4
#define PMU_RTCEVT_WKUMIN     RTC_INTSTS_INTSTS3
#define PMU_RTCEVT_WKUSEC     RTC_INTSTS_INTSTS2
#define PMU_RTCEVT_TIMEILLE   RTC_INTSTS_INTSTS1
#define PMU_RTCEVT_Msk         (PMU_RTCEVT_ACDONE   \
                               |PMU_RTCEVT_WKUCNT   \
                               |PMU_RTCEVT_MIDNIGHT \
                               |PMU_RTCEVT_WKUHOUR  \
                               |PMU_RTCEVT_WKUMIN   \
                               |PMU_RTCEVT_WKUSEC   \
                               |PMU_RTCEVT_TIMEILLE)
#define IS_PMU_RTCEVT(__RTCEVT__)  ((((__RTCEVT__)&PMU_RTCEVT_Msk) != 0U) &&\
                                    (((__RTCEVT__)&(~PMU_RTCEVT_Msk)) == 0U))                              


/***** BATDisc (PMU_BATDischargeConfig) *****/
#define PMU_BATRTC_DISC   ANA_REG6_BATRTCDISC
#define IS_PMU_BATRTCDISC(__BATRTCDISC__)  ((__BATRTCDISC__) == PMU_BATRTC_DISC)

/***** PowerThreshold (PMU_PowerAlarmTHConfig) *****/
#define PMU_PWTH_4_5      ANA_REG8_VDDPVDSEL_0
#define PMU_PWTH_4_2      ANA_REG8_VDDPVDSEL_1
#define PMU_PWTH_3_9      ANA_REG8_VDDPVDSEL_2
#define PMU_PWTH_3_6      ANA_REG8_VDDPVDSEL_3
#define PMU_PWTH_3_2      ANA_REG8_VDDPVDSEL_4
#define PMU_PWTH_2_9      ANA_REG8_VDDPVDSEL_5
#define PMU_PWTH_2_6      ANA_REG8_VDDPVDSEL_6
#define PMU_PWTH_2_3      ANA_REG8_VDDPVDSEL_7

#define IS_PMU_PWTH(__PWTH__)  (((__PWTH__) == PMU_PWTH_4_5) ||\
                                ((__PWTH__) == PMU_PWTH_4_2) ||\
                                ((__PWTH__) == PMU_PWTH_3_9) ||\
                                ((__PWTH__) == PMU_PWTH_3_6) ||\
                                ((__PWTH__) == PMU_PWTH_3_2) ||\
                                ((__PWTH__) == PMU_PWTH_2_9) ||\
                                ((__PWTH__) == PMU_PWTH_2_6) ||\
                                ((__PWTH__) == PMU_PWTH_2_3))

/***** RTCLDOSel (PMU_RTCLDOConfig) *****/
#define PMU_RTCLDO_1_5         (0)
#define PMU_RTCLDO_1_2          ANA_REGA_RTCVSEL

/***** StatusMask (PMU_GetPowerStatus) *****/
#define PMU_PWRSTS_AVCCLV         ANA_COMPOUT_AVCCLV
#define PMU_PWRSTS_VDCINDROP       ANA_COMPOUT_VDCINDROP
#define PMU_PWRSTS_VDDALARM       ANA_COMPOUT_VDDALARM

/***** Debounce (PMU_PWRDropDEBConfig) *****/
#define PMU_PWRDROP_DEB_0       ANA_CTRL_PWRDROPDEB_0
#define PMU_PWRDROP_DEB_1       ANA_CTRL_PWRDROPDEB_1
#define PMU_PWRDROP_DEB_2       ANA_CTRL_PWRDROPDEB_2
#define PMU_PWRDROP_DEB_3       ANA_CTRL_PWRDROPDEB_3
#define IS_PMU_PWRDROP_DEB(__DEB__)  (((__DEB__) == PMU_PWRDROP_DEB_0) ||\
                                      ((__DEB__) == PMU_PWRDROP_DEB_1) ||\
                                      ((__DEB__) == PMU_PWRDROP_DEB_2) ||\
                                      ((__DEB__) == PMU_PWRDROP_DEB_3))

/***** RSTSource (PMU_GetRSTSource) *****/
#define PMU_RSTSRC_EXTRST   PMU_STS_EXTRST
#define PMU_RSTSRC_PORST    PMU_STS_PORST
#define PMU_RSTSRC_DPORST   PMU_STS_DPORST
//#define PMU_RSTSRC_WDTRST   PMU_WDTSTS_WDTSTS
#define IS_PMU_RSTSRC(__RSTSRC__)  (((__RSTSRC__) == PMU_RSTSRC_EXTRST) ||\
                                    ((__RSTSRC__) == PMU_RSTSRC_PORST)  ||\
                                    ((__RSTSRC__) == PMU_RSTSRC_DPORST) )

/***** PMU_PDNDSleepConfig *****/
//VDCIN_PDNS
#define PMU_VDCINPDNS_0  (0)
#define PMU_VDCINPDNS_1  (ANA_CTRL_PDNS)
#define IS_PMU_VDCINPDNS(__VDCINPDNS__)  (((__VDCINPDNS__) == PMU_VDCINPDNS_0) ||\
                                          ((__VDCINPDNS__) == PMU_VDCINPDNS_1))
//VDD_PDNS
#define PMU_VDDPDNS_0  (0)
#define PMU_VDDPDNS_1  (ANA_CTRL_PDNS2)
#define IS_PMU_VDDPDNS(__VDDPDNS__)  (((__VDDPDNS__) == PMU_VDDPDNS_0) ||\
                                        ((__VDDPDNS__) == PMU_VDDPDNS_1))

/* Exported Functions ------------------------------------------------------- */

uint32_t PMU_EnterDSleepMode(void);
void PMU_EnterIdleMode(void);
uint32_t PMU_EnterSleepMode(void);

void PMU_INTConfig(uint32_t INTMask, uint32_t NewState);
uint8_t PMU_GetINTStatus(uint32_t INTMask);
void PMU_ClearINTStatus(uint32_t INTMask);

uint8_t PMU_GetStatus(uint32_t Mask);
uint16_t PMU_GetIOAAllINTStatus(void);
uint16_t PMU_GetIOAINTStatus(uint16_t INTMask);
void PMU_ClearIOAINTStatus(uint16_t INTMask);

void PMU_WakeUpPinConfig(uint32_t IOAx, uint32_t Wakeup_Event);

uint8_t PMU_EnterDSleep_LowPower(PMU_LowPWRTypeDef *InitStruct);
uint8_t PMU_EnterSleep_LowPower(PMU_LowPWRTypeDef *InitStruct);
#ifndef __GNUC__
void PMU_EnterIdle_LowPower(void);
#endif
void PMU_SleepWKUSRC_Config_IOA(uint16_t IOAx, uint32_t Wakeup_Event, uint32_t Priority);
void PMU_SleepWKUSRC_Config_RTC(uint32_t Wakeup_Event, uint32_t Priority);
void PMU_DeepSleepWKUSRC_Config_IOA(uint16_t IOAx, uint32_t Wakeup_Event);
void PMU_DeepSleepWKUSRC_Config_RTC(uint32_t Wakeup_Event);
void PMU_PDNDSleepConfig(uint32_t VDCIN_PDNS, uint32_t VDD_PDNS);

/***** BGP functions *****/
void PMU_BGP_Cmd(uint32_t NewState);

/***** VDD functions *****/
void PMU_VDDAlarmTHConfig(uint32_t PowerThreshold);
uint8_t PMU_GetVDDALARMStatus(void);
void PMU_VDDDetectorCmd(uint32_t NewState);

/***** AVCC functions *****/
void PMU_AVCC_Cmd(uint32_t NewState);
void PMU_AVCCOutput_Cmd(uint32_t NewState);
void PMU_AVCCLVDetector_Cmd(uint32_t NewState);
uint8_t PMU_GetAVCCLVStatus(void);

/***** VDCIN functions *****/
void PMU_VDCINDetector_Cmd(uint32_t NewState);
uint8_t PMU_GetVDCINDropStatus(void);

/***** BAT functions *****/
void PMU_BATDischargeConfig(uint32_t BATDisc, uint32_t NewState);

/***** Other functions *****/
uint8_t PMU_GetModeStatus(void);
uint8_t PMU_GetPowerStatus(uint32_t StatusMask);
void PMU_PWRDropDEBConfig(uint32_t Debounce);
uint8_t PMU_GetRSTSource(uint32_t RSTSource);
 
#ifdef __cplusplus
}
#endif
     
#endif /* __LIB_PMU_H */

/*********************************** END OF FILE ******************************/
