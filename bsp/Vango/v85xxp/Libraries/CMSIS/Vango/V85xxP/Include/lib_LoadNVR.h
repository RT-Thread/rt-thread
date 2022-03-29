/**
  ******************************************************************************
  * @file    lib_LoadNVR.h 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
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
  int16_t RTCTempK0; //K0
  int16_t RTCTempK1; //K1
  int16_t RTCTempK2; //K2
  int16_t RTCTempK3; //K3
  int16_t RTCTempK4; //K4
  int16_t RTCACTI;      //Center temperature
  uint32_t RTCACKTemp;  //section X temperature
  int32_t RTCTempDelta; //Temperature delta
  uint32_t RTCACF200;   //RTC_ACF200
} NVR_RTCINFO;

/* RTC(temp) information */
typedef struct
{
  int16_t RTCTempP0; //P0
  int16_t RTCTempP1; //P1
  int32_t RTCTempP2; //P2
} NVR_TempParams;

/* ADC Voltage Parameters */
typedef struct
{
  float aParameter;
  float bParameter;
  float OffsetParameter;
} NVR_ADCVOLPARA;
//Mode
#define NVR_3V_EXTERNAL_NODIV    (0x000UL)    // Power supply: 3.3V;    Channel: External;    Divider modeL: None
#define NVR_3V_EXTERNAL_RESDIV   (0x001UL)    // Power supply: 3.3V;    Channel: External;    Divider modeL: Resistive
#define NVR_3V_BAT1_RESDIV       (0x002UL)    // Power supply: 3.3V;    Channel: VDD;         Divider modeL: Resistive
#define NVR_3V_BATRTC_RESDIV     (0x003UL)    // Power supply: 3.3V;    Channel: BATRTC;      Divider modeL: Resistive
#define NVR_5V_EXTERNAL_NODIV    (0x100UL)    // Power supply: 5V;      Channel: External;    Divider modeL: None
#define NVR_5V_EXTERNAL_RESDIV   (0x101UL)    // Power supply: 5V;      Channel: External;    Divider modeL: Resistive
#define NVR_5V_BAT1_RESDIV       (0x102UL)    // Power supply: 5V;      Channel: VDD;         Divider modeL: Resistive
#define NVR_5V_BATRTC_RESDIV     (0x103UL)    // Power supply: 5V;      Channel: BATRTC;      Divider modeL: Resistive
#define IS_NVR_ADCVOL_MODE(__MODE__)  (((__MODE__) == NVR_3V_EXTERNAL_NODIV)   ||\
                                       ((__MODE__) == NVR_3V_EXTERNAL_RESDIV)  ||\
                                       ((__MODE__) == NVR_3V_BAT1_RESDIV)       ||\
                                       ((__MODE__) == NVR_3V_BATRTC_RESDIV)    ||\
                                       ((__MODE__) == NVR_5V_EXTERNAL_NODIV)   ||\
                                       ((__MODE__) == NVR_5V_EXTERNAL_RESDIV)  ||\
                                       ((__MODE__) == NVR_5V_BAT1_RESDIV)       ||\
                                       ((__MODE__) == NVR_5V_BATRTC_RESDIV))

//VOLMode
#define NVR_MEARES_3V      0
#define NVR_MEARES_5V      1
#define IS_MEARES(__VOLMODE__)     (((__VOLMODE__) == NVR_MEARES_3V)   ||\
                                    ((__VOLMODE__) == NVR_MEARES_5V))
/********** NVR Address **********/
//ADC Voltage Parameters
#define NVR_3VPARA_BASEADDR1          (__IO uint32_t *)(0x80C48)
#define NVR_3VPARA_BASEADDR2          (__IO uint32_t *)(0x80C6C)
#define NVR_5VPARA_BASEADDR1          (__IO uint32_t *)(0x80C00)
#define NVR_5VPARA_BASEADDR2          (__IO uint32_t *)(0x80C24)
//RTC DATA
//P4
#define NVR_RTC1_P4                   (__IO uint32_t *)(0x80800)
#define NVR_RTC1_P4_CHKSUM            (__IO uint32_t *)(0x80804)
#define NVR_RTC2_P4                   (__IO uint32_t *)(0x80808)
#define NVR_RTC2_P4_CHKSUM            (__IO uint32_t *)(0x8080C)
//ACK1~ACK5
#define NVR_RTC1_ACK0                 (__IO uint32_t *)(0x80810)
#define NVR_RTC1_ACK1                 (__IO uint32_t *)(0x80814)
#define NVR_RTC1_ACK2                 (__IO uint32_t *)(0x80818)
#define NVR_RTC1_ACK3                 (__IO uint32_t *)(0x8081C)
#define NVR_RTC1_ACK4                 (__IO uint32_t *)(0x80820)
#define NVR_RTC1_ACK_CHKSUM           (__IO uint32_t *)(0x80824)
#define NVR_RTC2_ACK0                 (__IO uint32_t *)(0x80828)
#define NVR_RTC2_ACK1                 (__IO uint32_t *)(0x8082C)
#define NVR_RTC2_ACK2                 (__IO uint32_t *)(0x80830)
#define NVR_RTC2_ACK3                 (__IO uint32_t *)(0x80834)
#define NVR_RTC2_ACK4                 (__IO uint32_t *)(0x80838)
#define NVR_RTC2_ACK_CHKSUM           (__IO uint32_t *)(0x8083C)
//ACTI
#define NVR_RTC1_ACTI                 (__IO uint32_t *)(0x80840)
#define NVR_RTC1_ACTI_CHKSUM          (__IO uint32_t *)(0x80844)
#define NVR_RTC2_ACTI                 (__IO uint32_t *)(0x80848)
#define NVR_RTC2_ACTI_CHKSUM          (__IO uint32_t *)(0x8084C)
//ACKTEMP
#define NVR_RTC1_ACKTEMP              (__IO uint32_t *)(0x80850)
#define NVR_RTC1_ACKTEMP_CHKSUM       (__IO uint32_t *)(0x80854)
#define NVR_RTC2_ACKTEMP              (__IO uint32_t *)(0x80858)
#define NVR_RTC2_ACKTEMP_CHKSUM       (__IO uint32_t *)(0x8085C)
//Analog trim data
#define NVR_ANA_TRIMDATA1             (__IO uint32_t *)(0x80DC0)
#define NVR_ANA_OPREG1                (__IO uint32_t *)(0x80DC4)
#define NVR_ANA_KEYREG1               (__IO uint32_t *)(0x80DC8)
#define NVR_ANA_CHECKSUM1             (__IO uint32_t *)(0x80DCC)
#define NVR_ANA_TRIMDATA2             (__IO uint32_t *)(0x80DD0)
#define NVR_ANA_OPREG2                (__IO uint32_t *)(0x80DD4)
#define NVR_ANA_KEYREG2               (__IO uint32_t *)(0x80DD8)
#define NVR_ANA_CHECKSUM2             (__IO uint32_t *)(0x80DDC)
#define NVR_ANA1_REG10                (__IO uint32_t *)(0x80DE0)
#define NVR_ANA1_REG10_CHKSUM         (__IO uint32_t *)(0x80DE4)
#define NVR_ANA2_REG10                (__IO uint32_t *)(0x80DE8)
#define NVR_ANA2_REG10_CHKSUM         (__IO uint32_t *)(0x80DEC)
//ADC_CHx
#define NVR_5VADCCHx_NODIV1           (__IO uint32_t *)(0x80C90)
#define NVR_5VADCCHx_RESDIV1          (__IO uint32_t *)(0x80C94)
#define NVR_5VADCCHx_NODIV2           (__IO uint32_t *)(0x80CA4)
#define NVR_5VADCCHx_RESDIV2          (__IO uint32_t *)(0x80CA8)
#define NVR_3VADCCHx_NODIV1           (__IO uint32_t *)(0x80CB8)
#define NVR_3VADCCHx_RESDIV1          (__IO uint32_t *)(0x80CBC)
#define NVR_3VADCCHx_NODIV2           (__IO uint32_t *)(0x80CCC)
#define NVR_3VADCCHx_RESDIV2          (__IO uint32_t *)(0x80CD0)
//BAT Measure Result 
#define NVR_5VBAT1                    (__IO uint32_t *)(0x80C98)
#define NVR_5VBATRTC1                 (__IO uint32_t *)(0x80C9C)
#define NVR_5VBATCHKSUM1              (__IO uint32_t *)(0x80CA0)
#define NVR_5VBAT2                    (__IO uint32_t *)(0x80CAC)
#define NVR_5VBATRTC2                 (__IO uint32_t *)(0x80CB0)
#define NVR_5VBATCHKSUM2              (__IO uint32_t *)(0x80CB4)
#define NVR_3VBAT1                    (__IO uint32_t *)(0x80CC0)
#define NVR_3VBATRTC1                 (__IO uint32_t *)(0x80CC4)
#define NVR_3VBATCHKSUM1              (__IO uint32_t *)(0x80CC8)
#define NVR_3VBAT2                    (__IO uint32_t *)(0x80CD4)
#define NVR_3VBATRTC2                 (__IO uint32_t *)(0x80CD8)
#define NVR_3VBATCHKSUM2              (__IO uint32_t *)(0x80CDC)
//RTC AutoCal Px pramameters
#define NVR_RTC1_P1_P0                (__IO uint32_t *)(0x80D10)
#define NVR_RTC1_P2                   (__IO uint32_t *)(0x80D14)
#define NVR_RTC1_P5_P4                (__IO uint32_t *)(0x80D18)
#define NVR_RTC1_P7_P6                (__IO uint32_t *)(0x80D1C)
#define NVR_RTC1_PCHECHSUM            (__IO uint32_t *)(0x80D20)
#define NVR_RTC2_P1_P0                (__IO uint32_t *)(0x80D24)
#define NVR_RTC2_P2                   (__IO uint32_t *)(0x80D28)
#define NVR_RTC2_P5_P4                (__IO uint32_t *)(0x80D2C)
#define NVR_RTC2_P7_P6                (__IO uint32_t *)(0x80D30)
#define NVR_RTC2_PCHECHSUM            (__IO uint32_t *)(0x80D34)
//Power Measure Result
#define NVR_AVCC_MEA1                 (__IO uint32_t *)(0x80D38)
#define NVR_DVCC_MEA1                 (__IO uint32_t *)(0x80D3C)
#define NVR_BGP_MEA1                  (__IO uint32_t *)(0x80D40)
#define NVR_RCL_MEA1                  (__IO uint32_t *)(0x80D44)
#define NVR_RCH_MEA1                  (__IO uint32_t *)(0x80D48)
#define NVR_PWR_CHECKSUM1             (__IO uint32_t *)(0x80D4C)
#define NVR_AVCC_MEA2                 (__IO uint32_t *)(0x80D50)
#define NVR_DVCC_MEA2                 (__IO uint32_t *)(0x80D54)
#define NVR_BGP_MEA2                  (__IO uint32_t *)(0x80D58)
#define NVR_RCL_MEA2                  (__IO uint32_t *)(0x80D5C)
#define NVR_RCH_MEA2                  (__IO uint32_t *)(0x80D60)
#define NVR_PWR_CHECKSUM2             (__IO uint32_t *)(0x80D64)
//Chip ID
#define NVR_CHIP1_ID0                 (__IO uint32_t *)(0x80D68)
#define NVR_CHIP1_ID1                 (__IO uint32_t *)(0x80D6C)
#define NVR_CHIP1_CHECKSUM            (__IO uint32_t *)(0x80D70)
#define NVR_CHIP2_ID0                 (__IO uint32_t *)(0x80D74)
#define NVR_CHIP2_ID1                 (__IO uint32_t *)(0x80D78)
#define NVR_CHIP2_CHECKSUM            (__IO uint32_t *)(0x80D7C)
//Temperature information
#define NVR_REALTEMP1                 (__IO uint32_t *)(0x80D80)
#define NVR_MEATEMP1                  (__IO uint32_t *)(0x80D84)
#define NVR_TEMP_CHECKSUM1            (__IO uint32_t *)(0x80D88)
#define NVR_REALTEMP2                 (__IO uint32_t *)(0x80D9C)
#define NVR_MEATEMP2                  (__IO uint32_t *)(0x80D90)
#define NVR_TEMP_CHECKSUM2            (__IO uint32_t *)(0x80D94)

uint32_t NVR_LoadANADataManual(void);
uint32_t NVR_GetInfo_LoadRTCData(NVR_RTCINFO *RTCTempData, uint32_t DivCLKSource);
uint32_t NVR_GetVoltageParameters(uint32_t Mode, NVR_ADCVOLPARA *Parameter);
uint32_t NVR_GetTempParameters(NVR_TempParams *TempParams);
uint32_t NVR_GetMISCGain(NVR_MISCGain *MEAResult);
uint32_t NVR_GetChipID(NVR_CHIPID *ChipID);

#ifdef __cplusplus
}
#endif

#endif /* __LIB_LOADNVR_H */

/*********************************** END OF FILE ******************************/
