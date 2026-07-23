/**
  ******************************************************************************
  * @file    lib_adc.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   ADC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __LIB_ADC_H
#define __LIB_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "target.h"

typedef struct
{
  uint32_t Mode;
  uint32_t ClockSource;
  uint32_t ClockFrq;
  uint32_t SkipSample;
  uint32_t AverageSample;
  uint32_t TriggerSource;
  uint32_t Channel;
  uint32_t ResDivEnable;
  uint32_t AverageEnable;
} ADC_InitType;

typedef struct
{
  uint32_t THDChannel;
  uint8_t UpperTHD; 
  uint8_t LowerTHD;
  uint32_t TriggerSel;  
  uint32_t THDSource;
} ADCTHD_InitType;

/* Exported constants --------------------------------------------------------*/
//Mode
#define ADC_MODE_DC             (0UL)
#define ADC_MODE_AC             (1UL)
#define ADC_MODE_TEMP           (2UL)
#define IS_ADC_MODE(__MODE__)  (((__MODE__) == ADC_MODE_DC) ||\
                                ((__MODE__) == ADC_MODE_AC) ||\
                                ((__MODE__) == ADC_MODE_TEMP))
//ClockSource
#define ADC_CLKSRC_RCH    (0)
#define ADC_CLKSRC_PLLL   ANA_ADCCTRL0_CLKSRCSEL
#define IS_ADC_CLKSRC(__CLKSRC__)  (((__CLKSRC__) == ADC_CLKSRC_RCH) ||\
                                    ((__CLKSRC__) == ADC_CLKSRC_PLLL))
//ClockFrq
#define ADC_CLKFRQ_HIGH  (0UL)
#define ADC_CLKFRQ_LOW   (1UL)
#define IS_ADC_CLKFRQ(__CLKFRQ__)  (((__CLKFRQ__) == ADC_CLKFRQ_HIGH) ||\
                                    ((__CLKFRQ__) == ADC_CLKFRQ_LOW))
//SkipSample
#define ADC_SKIP_0         (0x0UL << RTC_ADCMACTL_SKIP_SAMPLE_Pos)
#define ADC_SKIP_4         (0x4UL << RTC_ADCMACTL_SKIP_SAMPLE_Pos)
#define ADC_SKIP_8         (0x7UL << RTC_ADCMACTL_SKIP_SAMPLE_Pos)
#define ADC_SKIP_12        (0x12UL << RTC_ADCMACTL_SKIP_SAMPLE_Pos)
#define IS_ADC_SKIP(__SKIP__)  (((__SKIP__) == ADC_SKIP_0)  ||\
                                ((__SKIP__) == ADC_SKIP_4)  ||\
                                ((__SKIP__) == ADC_SKIP_8)  ||\
                                ((__SKIP__) == ADC_SKIP_12))
//AverageSample
#define ADC_AVERAGE_2     (0x0UL << RTC_ADCMACTL_AVERAGE_SAMPLE_Pos)
#define ADC_AVERAGE_4     (0x1UL << RTC_ADCMACTL_AVERAGE_SAMPLE_Pos)
#define ADC_AVERAGE_8     (0x2UL << RTC_ADCMACTL_AVERAGE_SAMPLE_Pos)
#define ADC_AVERAGE_16    (0x3UL << RTC_ADCMACTL_AVERAGE_SAMPLE_Pos)
#define ADC_AVERAGE_32    (0x4UL << RTC_ADCMACTL_AVERAGE_SAMPLE_Pos)
#define ADC_AVERAGE_64    (0x5UL << RTC_ADCMACTL_AVERAGE_SAMPLE_Pos)
#define IS_ADC_AVERAG(__AVERAG__)  (((__AVERAG__) == ADC_AVERAGE_2)   ||\
                                    ((__AVERAG__) == ADC_AVERAGE_4)   ||\
                                    ((__AVERAG__) == ADC_AVERAGE_8)   ||\
                                    ((__AVERAG__) == ADC_AVERAGE_16)  ||\
                                    ((__AVERAG__) == ADC_AVERAGE_32)  ||\
                                    ((__AVERAG__) == ADC_AVERAGE_64))
//TriggerSource
#define ADC_TRIGSOURCE_OFF      (0x0UL << ANA_ADCCTRL0_AEN_Pos)
#define ADC_TRIGSOURCE_ITVSITV  (0x1UL << ANA_ADCCTRL0_AEN_Pos)
#define ADC_TRIGSOURCE_WKUSEC   (0x2UL << ANA_ADCCTRL0_AEN_Pos)
#define ADC_TRIGSOURCE_ALARM    (0x3UL << ANA_ADCCTRL0_AEN_Pos)
#define ADC_TRIGSOURCE_TMR0     (0x4UL << ANA_ADCCTRL0_AEN_Pos)
#define ADC_TRIGSOURCE_TMR1     (0x5UL << ANA_ADCCTRL0_AEN_Pos)
#define ADC_TRIGSOURCE_TMR2     (0x6UL << ANA_ADCCTRL0_AEN_Pos)
#define ADC_TRIGSOURCE_TMR3     (0x7UL << ANA_ADCCTRL0_AEN_Pos)
#define IS_ADC_TRIGSOURCE(__TRIGSOURCE__)  (((__TRIGSOURCE__) == ADC_TRIGSOURCE_OFF)     ||\
                                            ((__TRIGSOURCE__) == ADC_TRIGSOURCE_ITVSITV) ||\
                                            ((__TRIGSOURCE__) == ADC_TRIGSOURCE_WKUSEC)  ||\
                                            ((__TRIGSOURCE__) == ADC_TRIGSOURCE_ALARM)   ||\
                                            ((__TRIGSOURCE__) == ADC_TRIGSOURCE_TMR0)    ||\
                                            ((__TRIGSOURCE__) == ADC_TRIGSOURCE_TMR1)    ||\
                                            ((__TRIGSOURCE__) == ADC_TRIGSOURCE_TMR2)    ||\
                                            ((__TRIGSOURCE__) == ADC_TRIGSOURCE_TMR3))
//Channel
#define ADC_CHANNEL_NONE      (0 << 0UL)
#define ADC_CHANNEL_GND0      (1 << 0UL)
#define ADC_CHANNEL_BAT1      (1 << 1UL)
#define ADC_CHANNEL_BATRTC    (1 << 2UL)
#define ADC_CHANNEL_CH3       (1 << 3UL)
#define ADC_CHANNEL_CH4       (1 << 4UL)
#define ADC_CHANNEL_CH5       (1 << 5UL)
#define ADC_CHANNEL_CH6       (1 << 6UL)
#define ADC_CHANNEL_CH7       (1 << 7UL)
#define ADC_CHANNEL_CH8       (1 << 8UL)
#define ADC_CHANNEL_CH9       (1 << 9UL)
#define ADC_CHANNEL_TEMP      (1 << 10UL)
#define ADC_CHANNEL_CH11      (1 << 11UL)
#define ADC_CHANNEL_DVCC      (1 << 12UL)
#define ADC_CHANNEL_GND13     (1 << 13UL)
#define ADC_CHANNEL_GND14     (1 << 14UL)
#define ADC_CHANNEL_GND15     (1 << 15UL)
#define ADC_CHANNEL_DC_Msk    (0xFBFFUL)
#define ADC_CHANNEL_DC_ALL     ADC_CHANNEL_DC_Msk
#define ADC_CHANNEL_AC_Msk    (0x0BF8UL)
#define ADC_CHANNEL_AC_ALL     ADC_CHANNEL_AC_Msk
#define IS_ADC_CHANNEL_GETDATA(__CHANNEL__)  (((__CHANNEL__) == ADC_CHANNEL_GND0)   ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_BAT1)   ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_BATRTC) ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_CH3)    ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_CH4)    ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_CH5)    ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_CH6)    ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_CH7)    ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_CH8)    ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_CH9)    ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_TEMP)   ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_CH11)   ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_DVCC)   ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_GND13)  ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_GND14)  ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_GND15))
#define IS_ADC_CHANNEL_AC(__CHANNEL__)  ((((__CHANNEL__) & ADC_CHANNEL_AC_Msk) != 0UL) &&\
                                         (((__CHANNEL__) & ~ADC_CHANNEL_AC_Msk) == 0UL))
#define IS_ADC_CHANNEL_DC(__CHANNEL__)  ((((__CHANNEL__) & ADC_CHANNEL_DC_Msk) != 0UL) &&\
                                         (((__CHANNEL__) & ~ADC_CHANNEL_DC_Msk) == 0UL))
#define IS_ADC_CHANNEL_TEMP(__CHANNEL__)  ((__CHANNEL__) == ADC_CHANNEL_TEMP)
#define IS_ADC_CHANNEL_EN_DC(__CHANNEL__)  (((((__CHANNEL__) & ADC_CHANNEL_DC_Msk) != 0UL) && (((__CHANNEL__) & ~ADC_CHANNEL_DC_Msk) == 0UL)) ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_NONE))
#define IS_ADC_CHANNEL_EN_AC(__CHANNEL__)  (((((__CHANNEL__) & ADC_CHANNEL_AC_Msk) != 0UL) && (((__CHANNEL__) & ~ADC_CHANNEL_AC_Msk) == 0UL)) ||\
                                              ((__CHANNEL__) == ADC_CHANNEL_NONE))

#define ADC_CHANNEL_Pos       (0UL)
#define ADC_CHANNEL_SHIFT     (ANA_ADCCTRL2_SCAN_CHx_Pos     - ADC_CHANNEL_Pos)
#define ADC_AVERAGECH_SHIFT   (RTC_ADCMACTL_AVERAGE_CHx_Pos  - ADC_CHANNEL_Pos)
#define ADC_RESDIVCH_SHIFT    (ANA_ADCCTRL1_RESDIV_CHx_Pos   - ADC_CHANNEL_Pos)

//THDChannel
#define ADC_THDCHANNEL0       (0UL)
#define ADC_THDCHANNEL1       (1UL)
#define ADC_THDCHANNEL2       (2UL)
#define ADC_THDCHANNEL3       (3UL)
#define IS_ADC_THDCHANNEL(THDCHANNEL)         (((THDCHANNEL) == ADC_THDCHANNEL0)  ||\
                                              ((THDCHANNEL) == ADC_THDCHANNEL1)  ||\
                                              ((THDCHANNEL) == ADC_THDCHANNEL2)  ||\
                                              ((THDCHANNEL) == ADC_THDCHANNEL3))

//TriggerSel
#define ADC_THDSEL_HIGH            (0UL)
#define ADC_THDSEL_RISING          (1UL)
#define ADC_THDSEL_FALLING         (2UL)
#define ADC_THDSEL_BOTH            (3UL)
#define IS_ADC_THDSEL(__THDSEL__)  (((__THDSEL__) == ADC_THDSEL_HIGH)      ||\
                                    ((__THDSEL__) == ADC_THDSEL_RISING)   ||\
                                    ((__THDSEL__) == ADC_THDSEL_FALLING)  ||\
                                    ((__THDSEL__) == ADC_THDSEL_BOTH))

//INTMask
#define ADC_INT_UPPER_TH3   ANA_INTEN_INTEN21
#define ADC_INT_LOWER_TH3   ANA_INTEN_INTEN20
#define ADC_INT_UPPER_TH2   ANA_INTEN_INTEN19
#define ADC_INT_LOWER_TH2   ANA_INTEN_INTEN18
#define ADC_INT_UPPER_TH1   ANA_INTEN_INTEN17
#define ADC_INT_LOWER_TH1   ANA_INTEN_INTEN16
#define ADC_INT_UPPER_TH0   ANA_INTEN_INTEN15
#define ADC_INT_LOWER_TH0   ANA_INTEN_INTEN14
#define ADC_INT_AUTODONE    ANA_INTEN_INTEN1
#define ADC_INT_MANUALDONE  ANA_INTEN_INTEN0
#define ADC_INT_Msk         (0x3FC003UL)
#define IS_ADC_INT(__INT__)  ((((__INT__) & ADC_INT_Msk) != 0UL) &&\
                              (((__INT__) & ~ADC_INT_Msk) == 0UL))

//INTSTS
#define ADC_INTSTS_UPPER_TH3   ANA_INTSTS_INTSTS21
#define ADC_INTSTS_LOWER_TH3   ANA_INTSTS_INTSTS20
#define ADC_INTSTS_UPPER_TH2   ANA_INTSTS_INTSTS19
#define ADC_INTSTS_LOWER_TH2   ANA_INTSTS_INTSTS18
#define ADC_INTSTS_UPPER_TH1   ANA_INTSTS_INTSTS17
#define ADC_INTSTS_LOWER_TH1   ANA_INTSTS_INTSTS16
#define ADC_INTSTS_UPPER_TH0   ANA_INTSTS_INTSTS15
#define ADC_INTSTS_LOWER_TH0   ANA_INTSTS_INTSTS14
#define ADC_INTSTS_AUTODONE    ANA_INTSTS_INTSTS1
#define ADC_INTSTS_MANUALDONE  ANA_INTSTS_INTSTS0
#define ADC_INTSTS_Msk            (0x3FC003UL)
#define IS_ADC_INTFLAGC(__INTFLAGC__)  ((((__INTFLAGC__) & ADC_INTSTS_Msk) != 0U) &&\
                                        (((__INTFLAGC__) & ~ADC_INTSTS_Msk) == 0U))
                                        
#define IS_ADC_INTFLAGR(__INTFLAGR__)  (((__INTFLAGR__) == ADC_INTSTS_UPPER_TH3)   ||\
                                        ((__INTFLAGR__) == ADC_INTSTS_LOWER_TH3)    ||\
                                        ((__INTFLAGR__) == ADC_INTSTS_UPPER_TH2)   ||\
                                        ((__INTFLAGR__) == ADC_INTSTS_LOWER_TH2)   ||\
                                        ((__INTFLAGR__) == ADC_INTSTS_UPPER_TH1)   ||\
                                        ((__INTFLAGR__) == ADC_INTSTS_LOWER_TH1)   ||\
                                        ((__INTFLAGR__) == ADC_INTSTS_UPPER_TH0)   ||\
                                        ((__INTFLAGR__) == ADC_INTSTS_LOWER_TH0)   ||\
                                        ((__INTFLAGR__) == ADC_INTSTS_AUTODONE)   ||\
                                        ((__INTFLAGR__) == ADC_INTSTS_MANUALDONE))

#define ADC_FLAG_CONV_ERR     (0x1U << ANA_ADCCTRL2_CONV_ERR_Pos)
#define ADC_FLAG_CAL_ERR      (0x1U << ANA_ADCCTRL2_CAL_ERR_Pos)
#define ADC_FLAG_CAL_DONE     (0x1U << ANA_ADCCTRL2_RTC_CAL_DONE_Pos)
#define ADC_FLAG_BUSY         (0x1U << ANA_ADCCTRL2_BUSY_Pos)
#define IS_ADC_ADCFLAG(__ADCFLAG__)  (((__ADCFLAG__) == ADC_FLAG_CONV_ERR)   ||\
                                      ((__ADCFLAG__) == ADC_FLAG_CAL_ERR)    ||\
                                      ((__ADCFLAG__) == ADC_FLAG_CAL_DONE)   ||\
                                      ((__ADCFLAG__) == ADC_FLAG_BUSY))

#define ADC_FLAG_RCMsk  (ADC_FLAG_CONV_ERR|ADC_FLAG_CAL_ERR)
#define IS_ADC_ADCFLAGC(__ADCFLAG__)  ((((__ADCFLAG__) & ADC_FLAG_RCMsk) != 0U) &&\
                                       (((__ADCFLAG__) & ~ADC_FLAG_RCMsk) == 0U))

//THDFlag
#define ADC_THDFLAG_UPPER3    (0x1U << ANA_ADCDATATHD_CH_UPPER_THD3_TRGED_Pos)
#define ADC_THDFLAG_LOWER3    (0x1U << ANA_ADCDATATHD_CH_LOWER_THD3_TRGED_Pos)
#define ADC_THDFLAG_UPPER2    (0x1U << ANA_ADCDATATHD_CH_UPPER_THD2_TRGED_Pos)
#define ADC_THDFLAG_LOWER2    (0x1U << ANA_ADCDATATHD_CH_LOWER_THD2_TRGED_Pos)
#define ADC_THDFLAG_UPPER1    (0x1U << ANA_ADCDATATHD_CH_UPPER_THD1_TRGED_Pos)
#define ADC_THDFLAG_LOWER1    (0x1U << ANA_ADCDATATHD_CH_LOWER_THD1_TRGED_Pos)
#define ADC_THDFLAG_UPPER0    (0x1U << ANA_ADCDATATHD_CH_UPPER_THD0_TRGED_Pos)
#define ADC_THDFLAG_LOWER0    (0x1U << ANA_ADCDATATHD_CH_LOWER_THD0_TRGED_Pos)
#define IS_ADC_THDFLAG(__THDFLAG__)  (((__THDFLAG__) == ADC_THDFLAG_UPPER3)   ||\
                                      ((__THDFLAG__) == ADC_THDFLAG_LOWER3)   ||\
                                      ((__THDFLAG__) == ADC_THDFLAG_UPPER2)   ||\
                                      ((__THDFLAG__) == ADC_THDFLAG_LOWER2)   ||\
                                      ((__THDFLAG__) == ADC_THDFLAG_UPPER1)   ||\
                                      ((__THDFLAG__) == ADC_THDFLAG_LOWER1)   ||\
                                      ((__THDFLAG__) == ADC_THDFLAG_UPPER0)   ||\
                                      ((__THDFLAG__) == ADC_THDFLAG_LOWER0))

#define IS_ADC_BATDIV(__BATDIV__)  (((__BATDIV__) == ADC_BAT_CAPDIV) ||\
                                    ((__BATDIV__) == ADC_BAT_RESDIV))

/* ADC_GetVoltage */
//Mode
#define ADC_3V_ADCCHx_NODIV    (0x000UL)    // Power supply: 3.3V;    Channel: External;    Divider modeL: None
#define ADC_3V_ADCCHx_RESDIV   (0x001UL)    // Power supply: 3.3V;    Channel: External;    Divider modeL: Resistive
#define ADC_3V_BAT1_RESDIV     (0x002UL)    // Power supply: 3.3V;    Channel: VDD;         Divider modeL: Resistive
#define ADC_3V_BATRTC_RESDIV   (0x003UL)    // Power supply: 3.3V;    Channel: BATRTC;      Divider modeL: Resistive
#define ADC_5V_ADCCHx_NODIV    (0x100UL)    // Power supply: 5V;      Channel: External;    Divider modeL: None
#define ADC_5V_ADCCHx_RESDIV   (0x101UL)    // Power supply: 5V;      Channel: External;    Divider modeL: Resistive
#define ADC_5V_BAT1_RESDIV     (0x102UL)    // Power supply: 5V;      Channel: VDD;         Divider modeL: Resistive
#define ADC_5V_BATRTC_RESDIV   (0x103UL)    // Power supply: 5V;      Channel: BATRTC;      Divider modeL: Resistive
#define ADC_TEMP               (0x1000UL)   // Temperature ;          Channel: ADC_CHANNEL_TEMP
#define IS_ADCVOL_MODE(__MODE__)      (((__MODE__) == ADC_3V_ADCCHx_NODIV)   ||\
                                       ((__MODE__) == ADC_3V_ADCCHx_RESDIV)  ||\
                                       ((__MODE__) == ADC_3V_BAT1_RESDIV)       ||\
                                       ((__MODE__) == ADC_3V_BATRTC_RESDIV)    ||\
                                       ((__MODE__) == ADC_5V_ADCCHx_NODIV)   ||\
                                       ((__MODE__) == ADC_5V_ADCCHx_RESDIV)  ||\
                                       ((__MODE__) == ADC_5V_BAT1_RESDIV)       ||\
                                       ((__MODE__) == ADC_5V_BATRTC_RESDIV)    ||\
                                       ((__MODE__) == ADC_TEMP))

/* Exported Functions ------------------------------------------------------- */
/* ADC Exported Functions Group1: 
                                  (De)Initialization -------------------------*/
void ADC_DeInit(void);
void ADC_StructInit(ADC_InitType* ADC_InitStruct);
void ADC_Init(ADC_InitType* ADC_InitStruct);
/* ADC Exported Functions Group2: 
                                  ADC Configuration --------------*/
void ADC_THDInit(ADCTHD_InitType* ADC_THDStruct);
void ADC_THDStructInit(ADCTHD_InitType* ADC_THDStruct);
void ADC_Calibration(void);
/* ADC Exported Functions Group3: 
                                  Get NVR Info, Calculate datas --------------*/
uint32_t ADC_CalculateValue(uint32_t Mode, int16_t adc_data, int16_t *value);
/* ADC Exported Functions Group4: 
                                  Interrupt (flag) ---------------------------*/
int16_t ADC_GetADCConversionValue(uint32_t Channel);
void ADC_INTConfig(uint32_t INTMask, uint32_t NewState);
uint8_t ADC_GetFlag(uint32_t FlagMask);
void ADC_ClearFlag(uint32_t FlagMask);
uint8_t ADC_GetINTStatus(uint32_t INTMask);
void ADC_ClearINTStatus(uint32_t INTMask);
uint8_t ADC_GetTHDFlag(uint32_t THDFlagMask);

/* ADC Exported Functions Group5: 
                                  MISC Configuration -------------------------*/
void ADC_Cmd(uint32_t NewState);
void ADC_LowerTHDCmd(uint32_t THDChannel,uint32_t NewState);
void ADC_UpperTHDCmd(uint32_t THDChannel,uint32_t NewState);
void ADC_StartManual(void);
void ADC_WaitForManual(void);

#ifdef __cplusplus
}
#endif
     
#endif  /* __LIB_ADC_H */

/*********************************** END OF FILE ******************************/
