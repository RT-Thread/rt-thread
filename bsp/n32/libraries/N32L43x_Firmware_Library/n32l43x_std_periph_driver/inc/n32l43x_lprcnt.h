#ifndef __N32L43X_LPRCNT_H__
#define __N32L43X_LPRCNT_H__
#include "n32l43x.h"
#ifdef __cplusplus
extern "C" {
#endif

/* LPRCNT CH_TH mask */
#define DACREF_default         ((uint32_t)0xFFC0FFFF)           //比较器内部参考电压设置

/* LPRCNT Chanal define */
typedef enum
{
    CHANNEL_0 = 0,
    CHANNEL_1 = 1,
    CHANNEL_2 = 2,
} CHANNELX;

#define CHANNEL_ERROR   0xff
/* LPRCNT VibrationPowerSelect mask */
#define POWERSELECT1V5        0     //1.5V
#define POWERSELECT1V65       1     //1.65V
#define POWERSELECT1V8        2     //1.8V
#define POWERSELECT2V0        3     //2.0V


/* LPRCNT the alarm sensor scan frequence  mask */
#define FRETIME4        0
#define FRETIME8        1
#define FRETIME16       2
#define FRETIME32       3
/* LPRCNT MSI division factor mask */
#define LPRCNT_PRESCALER_DIV1               0x00000000U
#define LPRCNT_PRESCALER_DIV2               0x00010000U
#define LPRCNT_PRESCALER_DIV4               0x00020000U
#define LPRCNT_PRESCALER_DIV8               0x00030000U

#define LPRCNT_ALMFRE_DIV4                  0x00000000U
#define LPRCNT_ALMFRE_DIV8                  0x04000000U
#define LPRCNT_ALMFRE_DIV16                 0x08000000U
#define LPRCNT_ALMFRE_DIV32                 0x0c000000U
/* LPRCNT interrupt mask */
#define CALIBRATION_INT                 LPRCNT_CTRL_CALIE
#define REPORT_INT                      LPRCNT_CTRL_RPTIE
#define ALARM_INT                       LPRCNT_CTRL_ALMIE
/* LPRCNT interrupt flag mask */
#define CALIBRATION_INT_FLAG                 LPRCNT_INTSTS_CALIF
#define REPORT_INT_FLAG                      LPRCNT_INTSTS_RPTIF
#define ALARM_INT_FLAG                       LPRCNT_INTSTS_ALMIF
//CMD register
#define START                                 1
#define STOP                                  2
#define CLEAR                                 4
#define CMD_REG_CLR                           0x03
//work mode
#define LPRCNT_MODE                           1
#define CAL_MODE                              0


//Time register
#define CLEAR_TIME_VALE          0xFF00C0C0
//TH register
#define CLEAR_TH_VALE            0xFFFF0000

/**
 * @brief  LPRCNT COMP definition
 */
//COMP bits Clear mask
//#define CMP_HYSEL_CLEAR      ((uint32_t)0xFFD8F300)
//#define CMP_INMSEL_CLEAR     ((uint32_t)0xFFD88F00)
//#define CMP_FILTH_CLEAR      ((uint32_t)0xFD68FF00)
 //Filter threshold control
#define CMP_FILTH_MODE0                       ((uint32_t)0x00000000)
#define CMP_FILTH_MODE1                       ((uint32_t)0x00800000)
#define CMP_FILTH_MODE2                       ((uint32_t)0x01000000)

/**
 * @brief  define LPRCNT some funtion
 */

//#define  STARTSTS(void)   ((bool)(LPRCNT->CMD & 0x01) //read start status
#define  LPRCNTModeEnable(mode) do{LPRCNT->CMD &= (~CMD_REG_CLR); LPRCNT->CMD |= (uint32_t)mode;}while (0)//set LPRCNT module CMD .
#define  SetLPRCNTWorkMode(mode) do{LPRCNT->CTRL &= (~LPRCNT_CTRL_RCNTM); LPRCNT->CTRL |= (uint32_t)(mode << 24);}while (0)//calibration mode or  LPRCNT mode
/**
 * @brief  define Auto detection
 */
#define AUTODETPERIOD4 0  //count overflow 4*pulse period
#define AUTODETPERIOD8 1  //count overflow 8*pulse period
/**************************************************************************************************************************************/
/*                           function structure variable                                                                              */
/**************************************************************************************************************************************/
typedef enum
{
    HYST_NO   = (0x0L << 10),
    HYST_LOW  = (0x1L << 10),
    HYST_MID  = (0x2L << 10),
    HYST_HIGH = (0x3L << 10),
} LPRCNT_COMP_CTRL_HYST;

typedef enum {
  //comp1 inm sel
  INMSEL_NC          = ((uint32_t)0x00000000),
  INMSEL_DAC1        = ((uint32_t)0x00001000),
  INMSEL_PA0         = ((uint32_t)0x00002000),
  INMSEL_PA5         = ((uint32_t)0x00003000),
  INMSEL_PB5         = ((uint32_t)0x00004000),
  INMSEL_PD4         = ((uint32_t)0x00005000),
  INMSEL_VREF_VC1    = ((uint32_t)0x00006000),
  INMSEL_VREF_VC2    = ((uint32_t)0x00007000),
}LPRCNT_COMP_CTRL_INMSEL;
/**
 * @brief  LPRCNT Init structure definition
 */
typedef struct
{
      uint8_t vibrationtime;
      uint8_t dischargetime;
      uint8_t chargetime;
} LPRCNT_InitTime;
typedef struct
{
      uint8_t dacreference;
      uint8_t undampedTh;
      uint8_t dampedTh;
} LPRCNT_InitThreshold;
typedef struct
{
      uint16_t low_speed;
      uint8_t hight_speed;
      uint8_t swtich_time;
} LPRCNT_Initfrequence;
typedef struct
{
      uint8_t Channel[3];
      uint8_t ChargeVol;
      uint8_t WorkMode;
      LPRCNT_InitTime ChTime[3];
      LPRCNT_InitThreshold ChTH[3];
      LPRCNT_Initfrequence NormalFreq;
      uint8_t AlarmFreq;
      uint32_t PrescaleDiv;
      uint16_t Circle;
      FunctionalState AutoDetEn;
      bool AutoWaitPer;
      FunctionalState IntEn;
      uint32_t Int;

} LPRCNT_InitType;

/**
 * @brief  COMP Init structure definition
 */

typedef struct
{
    bool LowPoweMode;          //low power mode
    LPRCNT_COMP_CTRL_HYST Hyst;  //COMP hysteresis
    LPRCNT_COMP_CTRL_INMSEL InmSel; //COMP input minus selection
    uint16_t ClkPsc;
} LPRCNT_COMP_InitType;


/**************************************************************************************************************************************/
/*                           specail  registers                                                                                       */
/**************************************************************************************************************************************/
//LPRCNT module setup time
#define DacSetupTime(time)      do{LPRCNT->CAL2 &= (~LPRCNT_CAL2_DACSET); LPRCNT->CAL2 |= (uint32_t)(time);}while (0)//time < 64 ,6bit
#define CompSetupTime(time)     do{LPRCNT->CAL2 &= (~LPRCNT_CAL2_CMPSET); LPRCNT->CAL2 |= (uint32_t)(time << 8);}while (0)//time < 64 ,6bit

#define DacSetupTimeConfig()   DacSetupTime(20)
#define CompSetupTimeConfig()  CompSetupTime(31)

#define RcntAdjustCircleNum(time)  do{LPRCNT->CAL2 &= (~LPRCNT_CAL2_RCNTADJ); LPRCNT->CAL2 |= (uint32_t)(time << 20);}while (0)//time < 16 ,4bit
#define ChargeAndDischargeGap(time) do{LPRCNT->CAL2 &= (~LPRCNT_CAL2_GAP); LPRCNT->CAL2 |= (uint32_t)(time << 16);}while (0)//time < 16 ,4bit
//Analog filter
#define POPH 0
#define NEPH 1
#define ANGFILT_TH   (__IO unsigned*)(0x40001800 + 0x1c)
#define ANGFILT_CTRL (__IO unsigned*)(0x40001800 + 0x28)
#define CLERR_ANGTH  0xffffff87 //bit3~6
#define CLERR_ANGPHA 0xffffefff //bit12
#define SetAnalogFilterTh(vale) do{(*ANGFILT_TH) &= CLERR_ANGTH;(*ANGFILT_TH) |= (uint32_t)(vale <<3);}while (0) //vale only equal to 0,1,3,8,12
#define CompAnalogFilterPhase(dir) do{(*ANGFILT_CTRL) &= CLERR_ANGPHA;(*ANGFILT_CTRL) |= (uint32_t)(dir << 12);}while (0)//Analog filtering  phase selection
//auto control set funtion
#define PwrAutoChargeEnable(cmd) do{LPRCNT->CAL3 & = (~LPRCNT_CAL3_PWR_DUR_EN);(LPRCNT->CAL3)|= (uint32_t)(cmd <<7);}while (0)//0 :enable 1:disable

/**************************************************************************************************************************************/
/*                           function declaration                                                                                     */
/**************************************************************************************************************************************/
void ClearITPendingBit(uint32_t intflag);
void COMP_1_2_IRQHandler(void);
void LPRCNT_IE(uint32_t MODE_IE ,FunctionalState NewState);
void CfgChannelTime(uint8_t Ch,uint8_t VibrationTime ,uint8_t DischargeTime,uint8_t  ChargeTime);
void CfgChannelDacRefVol(uint8_t Ch,uint8_t DacRef);
void CfgChannelThr(uint8_t Ch, uint8_t UndampedTh, uint8_t DampedTh);
void SetMsiClkPrescale(uint32_t Div);
void SetAutoReportCircle(uint16_t Circle);
void SetScanAverageValue(uint8_t N);
void SetVibrationPower(uint8_t Value);
void SetNormalSensorScanfrequence(uint16_t low_speed,uint8_t hight_speed,uint8_t swtich_time);
void SetAlarmSensorScanfrequence(uint8_t Period);
void SetAutoDetect(FunctionalState NewState );
void SetAutoDetectEnale(FunctionalState NewState );
void SetAutoDetectPeriod(bool per);
uint8_t GetSampleMode(void);
uint8_t GetChannelSensorWavesNum(uint8_t Ch);
uint8_t GetChannelSensorState(uint8_t Ch);
uint16_t GetRotationCircle(void);
uint16_t GetSetRcnt(void);
void ClrRcntCircle(void);
void SetPwrAutoCharge(bool En);
bool ReadStartState(void);
void LPRCNTInit(LPRCNT_InitType* LPRCNT_InitStruct);
void DAC_CMP_ALWSONCmd(FunctionalState NewState);

void LPRCNT_CompInit(LPRCNT_COMP_InitType* COMP_InitStruct);
void CompDigitalFilterCfg(bool cmd, uint32_t filterTh);
void CompAnalogFilterEn(bool cmd);
void LPRCNTAnalogFilterConfig(void);
//Interruprt mask
void LPRCNT_ClrIntBit(uint32_t intflag);

INTStatus LPRCNT_GetIntSts(uint32_t Int);
void LPRCNT_IntEn(uint32_t Mode ,FunctionalState NewState);
void CompDigitalFilterPhase(bool dir);

//for prinft some set values
uint16_t GetNormalSensorLowSpeed(void);
uint8_t GetNormalSensorHightSpeed(void);
uint8_t GetNormalSensorSwtichTime(void);
uint8_t GetDacRefVol(uint8_t Ch);
uint8_t GetUndampedTh(uint8_t Ch);
uint8_t GetDampedTh(uint8_t Ch);
uint8_t GetVibrationTime(uint8_t Ch);
uint8_t GetDischargeTime(uint8_t Ch);
uint8_t GetChargeTime(uint8_t Ch);
#endif /* __LPRCNT_H__ */
/**
 * @}
 */
