/**
  ******************************************************************************
  * @file    lib_LoadNVR.h 
  * @author  Application Team
  * @version V4.7.0
  * @date    2019-12-12
  * @brief   Load information from NVR.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __LIB_LOADNVR_H
#define __LIB_LOADNVR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "target.h"

/* BAT measure result */
typedef struct
{
  float  BATRESResult;  // BAT Resistor division Measure Result 
  float  BATCAPResult;  // BATRTC Cap division Measure Result 
} NVR_BATMEARES;

/* Power Measure Result */
typedef struct
{
  uint32_t  AVCCMEAResult;  // LDO33 Measure Result
  uint32_t  DVCCMEAResult;  // LDO15 Measure Result
  uint32_t  BGPMEAResult;    // BGP Measure Result
  uint32_t  RCLMEAResult;    // RCL Measure Result
  uint32_t  RCHMEAResult;    // RCH Measure Result
} NVR_MISCGain;

/* Chip ID */
typedef struct
{
  uint32_t  ChipID0;        // ID word 0
  uint32_t  ChipID1;        // ID word 1
} NVR_CHIPID;

/* Temperature information */
typedef struct
{
  float  TempOffset; 
} NVR_TEMPINFO;

/* LCD information */
typedef struct
{
  uint32_t  MEALCDLDO;     // Measure LCD LDO pre trim value
  uint32_t  MEALCDVol;     // VLCD setting
} NVR_LCDINFO;

/* RTC(temp) information */
typedef struct
{
  int16_t RTCTempP0; //P0
  int16_t RTCTempP1; //P1
  int32_t RTCTempP2; //P2
  int16_t RTCTempP4; //P4
  int16_t RTCTempP5; //P5
  int16_t RTCTempP6; //P6
  int16_t RTCTempP7; //P7 
  int16_t RTCTempK1; //K1
  int16_t RTCTempK2; //K2
  int16_t RTCTempK3; //K3
  int16_t RTCTempK4; //K4
  int16_t RTCTempK5; //K5
  int16_t RTCACTI;      //Center temperature
  uint32_t RTCACKTemp;  //section X temperature
  int16_t RTCTempDelta; //Temperature delta
  uint32_t RTCACF200;   //RTC_ACF200
  uint32_t APBClock;    //APB clock
} NVR_RTCINFO;

/* ADC Voltage Parameters */
typedef struct
{
  float aParameter;
  float bParameter;
} NVR_ADCVOLPARA;
//Mode
#define NVR_3V_EXTERNAL_NODIV    (0x000UL)    // Power supply: 3.3V;    Channel: External;    Divider modeL: None
#define NVR_3V_EXTERNAL_RESDIV   (0x001UL)    // Power supply: 3.3V;    Channel: External;    Divider modeL: Resistive
#define NVR_3V_EXTERNAL_CAPDIV   (0x002UL)    // Power supply: 3.3V;    Channel: External;    Divider modeL: Capacitive
#define NVR_3V_VDD_RESDIV        (0x003UL)    // Power supply: 3.3V;    Channel: VDD;         Divider modeL: Resistive
#define NVR_3V_VDD_CAPDIV        (0x004UL)    // Power supply: 3.3V;    Channel: VDD;         Divider modeL: Capacitive
#define NVR_3V_BATRTC_RESDIV     (0x005UL)    // Power supply: 3.3V;    Channel: BATRTC;      Divider modeL: Resistive
#define NVR_3V_BATRTC_CAPDIV     (0x006UL)    // Power supply: 3.3V;    Channel: BATRTC;      Divider modeL: Capacitive
#define NVR_5V_EXTERNAL_NODIV    (0x100UL)    // Power supply: 5V;      Channel: External;    Divider modeL: None
#define NVR_5V_EXTERNAL_RESDIV   (0x101UL)    // Power supply: 5V;      Channel: External;    Divider modeL: Resistive
#define NVR_5V_EXTERNAL_CAPDIV   (0x102UL)    // Power supply: 5V;      Channel: External;    Divider modeL: Capacitive
#define NVR_5V_VDD_RESDIV        (0x103UL)    // Power supply: 5V;      Channel: VDD;         Divider modeL: Resistive
#define NVR_5V_VDD_CAPDIV        (0x104UL)    // Power supply: 5V;      Channel: VDD;         Divider modeL: Capacitive
#define NVR_5V_BATRTC_RESDIV     (0x105UL)    // Power supply: 5V;      Channel: BATRTC;      Divider modeL: Resistive
#define NVR_5V_BATRTC_CAPDIV     (0x106UL)    // Power supply: 5V;      Channel: BATRTC;      Divider modeL: Capacitive
#define IS_NVR_ADCVOL_MODE(__MODE__)  (((__MODE__) == NVR_3V_EXTERNAL_NODIV)   ||\
                                       ((__MODE__) == NVR_3V_EXTERNAL_RESDIV)  ||\
                                       ((__MODE__) == NVR_3V_EXTERNAL_CAPDIV)  ||\
                                       ((__MODE__) == NVR_3V_VDD_RESDIV)       ||\
                                       ((__MODE__) == NVR_3V_VDD_CAPDIV)       ||\
                                       ((__MODE__) == NVR_3V_BATRTC_RESDIV)    ||\
                                       ((__MODE__) == NVR_3V_BATRTC_CAPDIV)    ||\
                                       ((__MODE__) == NVR_5V_EXTERNAL_NODIV)   ||\
                                       ((__MODE__) == NVR_5V_EXTERNAL_RESDIV)  ||\
                                       ((__MODE__) == NVR_5V_EXTERNAL_CAPDIV)  ||\
                                       ((__MODE__) == NVR_5V_VDD_RESDIV)       ||\
                                       ((__MODE__) == NVR_5V_VDD_CAPDIV)       ||\
                                       ((__MODE__) == NVR_5V_BATRTC_RESDIV)    ||\
                                       ((__MODE__) == NVR_5V_BATRTC_CAPDIV))

/********** NVR Address **********/
//ADC Voltage Parameters
#define NVR_3VPARA_BASEADDR1          (__IO uint32_t *)(0x40400)
#define NVR_3VPARA_BASEADDR2          (__IO uint32_t *)(0x40440)
#define NVR_5VPARA_BASEADDR1          (__IO uint32_t *)(0x40480)
#define NVR_5VPARA_BASEADDR2          (__IO uint32_t *)(0x404C0)
//RTC DATA
//P4
#define NVR_RTC1_P4                   (__IO uint32_t *)(0x40800)
#define NVR_RTC1_P4_CHKSUM            (__IO uint32_t *)(0x40804)
#define NVR_RTC2_P4                   (__IO uint32_t *)(0x40808)
#define NVR_RTC2_P4_CHKSUM            (__IO uint32_t *)(0x4080C)
//ACK1~ACK5
#define NVR_RTC1_ACK1                 (__IO uint32_t *)(0x40810)
#define NVR_RTC1_ACK2                 (__IO uint32_t *)(0x40814)
#define NVR_RTC1_ACK3                 (__IO uint32_t *)(0x40818)
#define NVR_RTC1_ACK4                 (__IO uint32_t *)(0x4081C)
#define NVR_RTC1_ACK5                 (__IO uint32_t *)(0x40820)
#define NVR_RTC1_ACK_CHKSUM           (__IO uint32_t *)(0x40824)
#define NVR_RTC2_ACK1                 (__IO uint32_t *)(0x40828)
#define NVR_RTC2_ACK2                 (__IO uint32_t *)(0x4082C)
#define NVR_RTC2_ACK3                 (__IO uint32_t *)(0x40830)
#define NVR_RTC2_ACK4                 (__IO uint32_t *)(0x40834)
#define NVR_RTC2_ACK5                 (__IO uint32_t *)(0x40838)
#define NVR_RTC2_ACK_CHKSUM           (__IO uint32_t *)(0x4083C)
//ACTI
#define NVR_RTC1_ACTI                 (__IO uint32_t *)(0x40840)
#define NVR_RTC1_ACTI_CHKSUM          (__IO uint32_t *)(0x40844)
#define NVR_RTC2_ACTI                 (__IO uint32_t *)(0x40848)
#define NVR_RTC2_ACTI_CHKSUM          (__IO uint32_t *)(0x4084C)
//ACKTEMP
#define NVR_RTC1_ACKTEMP              (__IO uint32_t *)(0x40850)
#define NVR_RTC1_ACKTEMP_CHKSUM       (__IO uint32_t *)(0x40854)
#define NVR_RTC2_ACKTEMP              (__IO uint32_t *)(0x40858)
#define NVR_RTC2_ACKTEMP_CHKSUM       (__IO uint32_t *)(0x4085C)
//Analog trim data
#define NVR_ANA_TRIMDATA1             (__IO uint32_t *)(0x40DC0)
#define NVR_ANA_OPREG1                (__IO uint32_t *)(0x40DC4)
#define NVR_ANA_KEYREG1               (__IO uint32_t *)(0x40DC8)
#define NVR_ANA_CHECKSUM1             (__IO uint32_t *)(0x40DCC)
#define NVR_ANA_TRIMDATA2             (__IO uint32_t *)(0x40DD0)
#define NVR_ANA_OPREG2                (__IO uint32_t *)(0x40DD4)
#define NVR_ANA_KEYREG2               (__IO uint32_t *)(0x40DD8)
#define NVR_ANA_CHECKSUM2             (__IO uint32_t *)(0x40DDC)
//BAT Measure Result 
#define NVR_BAT_R1                    (__IO uint32_t *)(0x40CE0)
#define NVR_BAT_C1                    (__IO uint32_t *)(0x40CE4)
#define NVR_BATMEA_CHECHSUM1          (__IO uint32_t *)(0x40CE8)
#define NVR_BAT_R2                    (__IO uint32_t *)(0x40CF0)
#define NVR_BAT_C2                    (__IO uint32_t *)(0x40CF4)
#define NVR_BATMEA_CHECHSUM2          (__IO uint32_t *)(0x40CF8)
//RTC AutoCal Px pramameters
#define NVR_RTC1_P1_P0                (__IO uint32_t *)(0x40D00)
#define NVR_RTC1_P2                   (__IO uint32_t *)(0x40D04)
#define NVR_RTC1_P5_P4                (__IO uint32_t *)(0x40D08)
#define NVR_RTC1_P7_P6                (__IO uint32_t *)(0x40D0C)
#define NVR_RTC1_PCHECHSUM            (__IO uint32_t *)(0x40D10)
#define NVR_RTC2_P1_P0                (__IO uint32_t *)(0x40D14)
#define NVR_RTC2_P2                   (__IO uint32_t *)(0x40D18)
#define NVR_RTC2_P5_P4                (__IO uint32_t *)(0x40D1C)
#define NVR_RTC2_P7_P6                (__IO uint32_t *)(0x40D20)
#define NVR_RTC2_PCHECHSUM            (__IO uint32_t *)(0x40D24)
//Power Measure Result
#define NVR_DVCC_MEA1                 (__IO uint32_t *)(0x40D28)
#define NVR_AVCC_MEA1                 (__IO uint32_t *)(0x40D2C)
#define NVR_BGP_MEA1                  (__IO uint32_t *)(0x40D30)
#define NVR_RCL_MEA1                  (__IO uint32_t *)(0x40D34)
#define NVR_RCH_MEA1                  (__IO uint32_t *)(0x40D38)
#define NVR_PWR_CHECKSUM1             (__IO uint32_t *)(0x40D3C)
#define NVR_DVCC_MEA2                 (__IO uint32_t *)(0x40D40)
#define NVR_AVCC_MEA2                 (__IO uint32_t *)(0x40D44)
#define NVR_BGP_MEA2                  (__IO uint32_t *)(0x40D48)
#define NVR_RCL_MEA2                  (__IO uint32_t *)(0x40D4C)
#define NVR_RCH_MEA2                  (__IO uint32_t *)(0x40D50)
#define NVR_PWR_CHECKSUM2             (__IO uint32_t *)(0x40D54)
//Chip ID
#define NVR_CHIP1_ID0                 (__IO uint32_t *)(0x40D58)
#define NVR_CHIP1_ID1                 (__IO uint32_t *)(0x40D5C)
#define NVR_CHIP1_CHECKSUM            (__IO uint32_t *)(0x40D60)
#define NVR_CHIP2_ID0                 (__IO uint32_t *)(0x40D64)
#define NVR_CHIP2_ID1                 (__IO uint32_t *)(0x40D68)
#define NVR_CHIP2_CHECKSUM            (__IO uint32_t *)(0x40D6C)
//Temperature information
#define NVR_REALTEMP1                 (__IO uint32_t *)(0x40D70)
#define NVR_MEATEMP1                  (__IO uint32_t *)(0x40D74)
#define NVR_TEMP_CHECKSUM1            (__IO uint32_t *)(0x40D78)
#define NVR_REALTEMP2                 (__IO uint32_t *)(0x40D7C)
#define NVR_MEATEMP2                  (__IO uint32_t *)(0x40D80)
#define NVR_TEMP_CHECKSUM2            (__IO uint32_t *)(0x40D84)
//LCD Information
#define NVR_LCD_LDO1                  (__IO uint32_t *)(0x40D90)
#define NVR_LCD_VOL1                  (__IO uint32_t *)(0x40D94)
#define NVR_LCD_CHECKSUM1             (__IO uint32_t *)(0x40D98)
#define NVR_LCD_LDO2                  (__IO uint32_t *)(0x40D9C)
#define NVR_LCD_VOL2                  (__IO uint32_t *)(0x40DA0)
#define NVR_LCD_CHECKSUM2             (__IO uint32_t *)(0x40DA4)


uint32_t NVR_LoadANADataManual(void);
uint32_t NVR_GetADCVoltageParameter(uint32_t Mode, NVR_ADCVOLPARA *Parameter);
uint32_t NVR_GetBATOffset(NVR_BATMEARES *MEAResult);
uint32_t NVR_GetInfo_LoadRTCData(NVR_RTCINFO *RTCTempData);
uint32_t NVR_GetMISCGain(NVR_MISCGain *MEAResult);
uint32_t NVR_GetChipID(NVR_CHIPID *ChipID);
uint32_t NVR_GetLCDInfo(NVR_LCDINFO *LCDInfo);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_LOADNVR_H */

/*********************************** END OF FILE ******************************/
