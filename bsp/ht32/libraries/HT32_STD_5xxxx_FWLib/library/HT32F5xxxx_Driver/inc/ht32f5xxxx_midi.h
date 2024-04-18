/*********************************************************************************************************//**
 * @file    ht32f5xxxx_midi.h
 * @version $Rev:: 6684         $
 * @date    $Date:: 2023-01-18 #$
 * @brief   The header file of the MIDI library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_MIDI_H
#define __HT32F5XXXX_MIDI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"


/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup MIDI
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup MIDI_Exported_Types MIDI exported types
  * @{
  */

/**
 * @brief  Enumeration of MIDI CTRL MCUCHEN3.
 */
typedef enum
{
  MCUCHEN3_OFF = DISABLE,
  MCUCHEN3_ON = ENABLE,
} MIDI_CTRL_MCUCHEN3_Enum;
/**
 * @brief  Enumeration of MIDI CTRL MCUCHEN2.
 */
typedef enum
{
  MCUCHEN2_OFF = DISABLE,
  MCUCHEN2_ON = ENABLE,
} MIDI_CTRL_MCUCHEN2_Enum;
/**
 * @brief  Enumeration of MIDI CTRL MCUCHEN1.
 */
typedef enum
{
  MCUCHEN1_OFF = DISABLE,
  MCUCHEN1_ON = ENABLE,
} MIDI_CTRL_MCUCHEN1_Enum;
/**
 * @brief  Enumeration of MIDI CTRL MCUCHEN0.
 */
typedef enum
{
  MCUCHEN0_OFF = DISABLE,
  MCUCHEN0_ON = ENABLE,
} MIDI_CTRL_MCUCHEN0_Enum;
/**
 * @brief  Enumeration of MIDI CTRL MUSIC.
 */
typedef enum
{
  MUSICEN_OFF = DISABLE,
  MUSICEN_ON = ENABLE,
} MIDI_CTRL_MUSICEN_Enum;
/**
 * @brief  Enumeration of MIDI SPI RDEN.
 */
typedef enum
{
  SPIRDEN_OFF = DISABLE,
  SPIRDEN_ON = ENABLE,
} MIDI_CTRL_SPIRDEN_Enum;
/**
 * @brief  Enumeration of MIDI SPI DISLOOP.
 */
typedef enum
{
  SPIDISLOOP_OFF = DISABLE,
  SPIDISLOOP_ON = ENABLE,
} MIDI_CTRL_SPIDISLOOP_Enum;
/**
 * @brief  Enumeration of MIDI CTRL CHS.
 */
typedef enum
{
  CHS16 = 0,  /*!< Select 16-Channel                                                                        */
  CHS20,      /*!< Select 20-Channel                                                                        */
  CHS24,      /*!< Select 24-Channel                                                                        */
  CHS28,      /*!< Select 28-Channel                                                                        */
  CHS32,      /*!< Select 32-Channel                                                                        */
} MIDI_CTRL_CHS_Enum;

/**
 * @brief  Enumeration of MIDI Note.
 */
typedef enum
{
  BL0   = 0,
  BL1,
  BL2,
  BL3,
  BL4,
  BL5,
  BL6,
  BL7,
  BL8,
  BL9,
  BL10,
  BL11,
} MIDI_FREQ_BL_Enum;

/**
 * @brief  Enumeration of MIDI VOL AR.
 */
typedef enum
{
  ENV_RELEASE = RESET,
  ENV_ATTACK = SET,
} MIDI_VOL_AR_Enum;
/**
 * @brief  Enumeration of MIDI VOL ENV.
 */
typedef enum
{
  ENV_TYPE0 = 0,
  ENV_TYPE1,
  ENV_TYPE2,
  ENV_NO,
} MIDI_VOL_ENV_Enum;

/**
 * @brief  Enumeration of MIDI RE_NUM WBS.
 */
typedef enum
{
  WBS8   = 0,  /*!< WBS 8-bit                                                                               */
  WBS12,       /*!< WBS 12-bit                                                                              */
  WBS16,       /*!< WBS 16-bit                                                                              */
} MIDI_RENUM_WBS_Enum;

/**
 * @brief  Enumeration of MIDI CHAN ST.
 */
typedef enum
{
  ST_OFF = DISABLE,
  ST_ON = ENABLE,
} MIDI_CHAN_ST_Enum;
/**
 * @brief  Enumeration of MIDI CHAN VM.
 */
typedef enum
{
  VM_OFF = DISABLE,
  VM_ON = ENABLE,
} MIDI_CHAN_VM_Enum;
/**
 * @brief  Enumeration of MIDI CHAN FR.
 */
typedef enum
{
  FR_OFF = DISABLE,
  FR_ON = ENABLE,
} MIDI_CHAN_FR_Enum;
/**
 * @brief  Enumeration of MIDI CHAN CHx.
 */
typedef enum
{
  MIDI_CHx0  = 0,
  MIDI_CHx1,
  MIDI_CHx2,
  MIDI_CHx3,
  MIDI_CHx4,
  MIDI_CHx5,
  MIDI_CHx6,
  MIDI_CHx7,
  MIDI_CHx8,
  MIDI_CHx9,
  MIDI_CHx10,
  MIDI_CHx11,
  MIDI_CHx12,
  MIDI_CHx13,
  MIDI_CHx14,
  MIDI_CHx15,
  MIDI_CHx16,
  MIDI_CHx17,
  MIDI_CHx18,
  MIDI_CHx19,
  MIDI_CHx20,
  MIDI_CHx21,
  MIDI_CHx22,
  MIDI_CHx23,
  MIDI_CHx24,
  MIDI_CHx25,
  MIDI_CHx26,
  MIDI_CHx27,
  MIDI_CHx28,
  MIDI_CHx29,
  MIDI_CHx30,
  MIDI_CHx31,
} MIDI_CHAN_CHx_Enum;

typedef struct
{
  u8 MIDI_CTRL_DACDS;
  ControlStatus MIDI_CTRL_MUSICEN;
  ControlStatus MIDI_CTRL_SPIDISLOOP;
  u8 MIDI_CTRL_CHS;
  MIDI_FREQ_BL_Enum MIDI_FREQ_BL;
  u16 MIDI_FREQ_FR;
  MIDI_VOL_AR_Enum MIDI_VOL_AR;
  MIDI_VOL_ENV_Enum MIDI_VOL_ENV;
  u16 MIDI_VOL_VL;
  u16 MIDI_VOL_VR;
  u32 MIDI_STADDR;
  MIDI_RENUM_WBS_Enum MIDI_RENUM_WBS;
  u16 MIDI_RENUM_RE;
  u32 MIDI_ENDADDR;
  ControlStatus MIDI_CHAN_ST;
  ControlStatus MIDI_CHAN_VM;
  ControlStatus MIDI_CHAN_FR;
  u8 MIDI_CHAN_CHx;
} MIDI_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup MIDI_Exported_Constants MIDI exported constants
  * @{
  */
/* Definitions of MIDI_FLAG                                                                                 */
#define MIDI_FLAG_INTF        0x0001

/* Definitions of MIDI_INT                                                                                  */
#define MIDI_INT_INTEN        0x0001
#define MIDI_INT_MIDII_DMAEN  0x0002
#define MIDI_INT_MIDIO_DMAEN  0x0004

/* Definitions of MIDI_VOL                                                                                  */
#define VOL_MAX  0
#define VOL_MID  0x1FF
#define VOL_380  0x380
#define VOL_MIN  0x3FF
#define VOL_MUTE VOL_MIN

//#define IS_MIDI(x) ((MIDI == HT_MIDI))
#define IS_MIDI(x) ((x == HT_MIDI))

#define IS_MIDI_INT(x)        (((x & 0xFFFFFFF8) == 0x0) && (x != 0))
#define IS_MIDI_FLAG(x)       (x == MIDI_FLAG_INTF)
#define IS_MIDI_FLAG_CLEAR(x) (((x & 0xFFFFFFFE) == 0) && (x != 0))

#define IS_MIDI_CTRL_MCUCHEN3(x)    ((x == MCUCHEN3_OFF) || (x == MCUCHEN3_ON))
#define IS_MIDI_CTRL_MCUCHEN2(x)    ((x == MCUCHEN2_OFF) || (x == MCUCHEN2_ON))
#define IS_MIDI_CTRL_MCUCHEN1(x)    ((x == MCUCHEN1_OFF) || (x == MCUCHEN1_ON))
#define IS_MIDI_CTRL_MCUCHEN0(x)    ((x == MCUCHEN0_OFF) || (x == MCUCHEN0_ON))
#define IS_MIDI_CTRL_DACDS(x)       (x < 8)
#define IS_MIDI_CTRL_MUSICEN(x)     ((x == MUSICEN_OFF) || (x == MUSICEN_ON))
#define IS_MIDI_CTRL_SPIRDEN(x)     ((x == SPIRDEN_OFF) || (x == SPIRDEN_ON))
#define IS_MIDI_CTRL_SPIDISLOOP(x)  ((x == SPIDISLOOP_OFF) || (x == SPIDISLOOP_ON))
#define IS_MIDI_CTRL_CHS(x)         (x < 8)

#define IS_MIDI_FREQ_BL(x)    (x < 12)
#define IS_MIDI_FREQ_FR(x)    (x < 0xFFF)

#define IS_MIDI_VOL_AR(x)     (ENV_ATTACK || ENV_RELEASE)
#define IS_MIDI_VOL_ENV(x)    (ENV_TYPE0 || ENV_TYPE1 || ENV_TYPE2 || ENV_NO)
#define IS_MIDI_VOL_VL(x)     (x < 0x3FF)
#define IS_MIDI_VOL_VR(x)     (x < 0x3FF)

#define IS_MIDI_STADDR(x)     (x < 0x7FFFF)

#define IS_MIDI_RENUM_WBS(x)  ((x == WBS8) || (x == WBS12) || (x == WBS16))
#define IS_MIDI_RENUM_RE(x)   (x < 0x7FFF)

#define IS_MIDI_ENDADDR(x)    (x < 0xFFFFFF)

#define IS_MIDI_CHAN_ST(x)    ((x == ST_OFF) || (x == ST_ON))
#define IS_MIDI_CHAN_VM(x)    ((x == VM_OFF) || (x == VM_ON))
#define IS_MIDI_CHAN_FR(x)    ((x == FR_OFF) || (x == FR_ON))
#define IS_MIDI_CHAN_CHx(x)   (x < 32)

#define IS_MIDI_MCUCHx11_BH(x)    (x < 0xFFFF)
#define IS_MIDI_MCUCHx11_BL(x)    (x < 0xFFFF)

#define IS_MIDI_MCUCHx12_CH(x)    (x < 0xFFFF)
#define IS_MIDI_MCUCHx12_CL(x)    (x < 0xFFFF)

#define IS_MIDI_MCUCHx13_DH(x)    (x < 0xFFFF)
#define IS_MIDI_MCUCHx13_DL(x)    (x < 0xFFFF)

#define IS_MIDI_MCUCHx14_EH(x)    (x < 0xFFFF)
#define IS_MIDI_MCUCHx14_EL(x)    (x < 0xFFFF)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup MIDI_Exported_Functions MIDI exported functions
  * @{
  */
void MIDI_DeInit(void);
void MIDI_Init(HT_MIDI_TypeDef* MIDIx, MIDI_InitTypeDef* MIDI_InitStruct);
void MIDI_StructInit(MIDI_InitTypeDef* MIDI_InitStruct);
void MIDI_IntConfig(HT_MIDI_TypeDef* MIDIx, u32 MIDI_Int, ControlStatus NewState);
FlagStatus MIDI_GetFlagStatus(HT_MIDI_TypeDef* MIDIx, u32 MIDI_Flag);
void MIDI_ClearFlag(HT_MIDI_TypeDef* MIDIx, u32 MIDI_Flag);

void MIDI_CTRL(HT_MIDI_TypeDef* MIDIx,
               MIDI_CTRL_MCUCHEN3_Enum MCUCHEN3, MIDI_CTRL_MCUCHEN2_Enum MCUCHEN2,
               MIDI_CTRL_MCUCHEN1_Enum MCUCHEN1, MIDI_CTRL_MCUCHEN0_Enum MCUCHEN0,
               u8 DACDS,
               MIDI_CTRL_MUSICEN_Enum MUSICEN,
               MIDI_CTRL_SPIRDEN_Enum SPIRDEN, MIDI_CTRL_SPIDISLOOP_Enum SPIDISLOOP,
               MIDI_CTRL_CHS_Enum CHS);
void MIDI_FREQ(HT_MIDI_TypeDef* MIDIx, MIDI_FREQ_BL_Enum BL, u16 FR);
void MIDI_VOL(HT_MIDI_TypeDef* MIDIx, MIDI_VOL_AR_Enum A_R, MIDI_VOL_ENV_Enum ENV, u16 VL, u16 VR);
void MIDI_STADDR(HT_MIDI_TypeDef* MIDIx, u32 ST_ADDR);
void MIDI_RENUM(HT_MIDI_TypeDef* MIDIx, MIDI_RENUM_WBS_Enum WBS, u16 RE);
void MIDI_ENDADDR(HT_MIDI_TypeDef* MIDIx, u32 END_ADDR);
void MIDI_CHAN(HT_MIDI_TypeDef* MIDIx, MIDI_CHAN_ST_Enum ST, MIDI_CHAN_VM_Enum VM, MIDI_CHAN_FR_Enum FR, u8 CHx);

void MIDI_MCUCH0(HT_MIDI_TypeDef* MIDIx, u16 CH0B, u16 CH0A);
void MIDI_MCUCH1(HT_MIDI_TypeDef* MIDIx, u16 CH1B, u16 CH1A);
void MIDI_MCUCH2(HT_MIDI_TypeDef* MIDIx, u16 CH2B, u16 CH2A);
void MIDI_MCUCH3(HT_MIDI_TypeDef* MIDIx, u16 CH3B, u16 CH3A);

void MIDI_FREQ_BL(HT_MIDI_TypeDef* MIDIx, MIDI_FREQ_BL_Enum BL);
void MIDI_FREQ_FR(HT_MIDI_TypeDef* MIDIx, u16 FR);
void MIDI_VOL_AR(HT_MIDI_TypeDef* MIDIx, MIDI_VOL_AR_Enum A_R);
void MIDI_VOL_ENV(HT_MIDI_TypeDef* MIDIx, MIDI_VOL_ENV_Enum ENV);
void MIDI_VOL_VL(HT_MIDI_TypeDef* MIDIx, u16 VL);
void MIDI_VOL_VR(HT_MIDI_TypeDef* MIDIx, u16 VR);
void MIDI_RENUM_WBS(HT_MIDI_TypeDef* MIDIx, MIDI_RENUM_WBS_Enum WBS);
void MIDI_RENUM_RE(HT_MIDI_TypeDef* MIDIx, u16 RE);
void MIDI_CHAN_STCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState);
void MIDI_CHAN_VMCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState);
void MIDI_CHAN_FRCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState);
void MIDI_CHAN_CHx(HT_MIDI_TypeDef* MIDIx, u8 CHx);
void MIDI_MCUCH0_CH0B(HT_MIDI_TypeDef* MIDIx, u16 CH0B);
void MIDI_MCUCH0_CH0A(HT_MIDI_TypeDef* MIDIx, u16 CH0A);
void MIDI_MCUCH1_CH1B(HT_MIDI_TypeDef* MIDIx, u16 CH1B);
void MIDI_MCUCH1_CH1A(HT_MIDI_TypeDef* MIDIx, u16 CH1A);
void MIDI_MCUCH2_CH2B(HT_MIDI_TypeDef* MIDIx, u16 CH2B);
void MIDI_MCUCH2_CH2A(HT_MIDI_TypeDef* MIDIx, u16 CH2A);
void MIDI_MCUCH3_CH3B(HT_MIDI_TypeDef* MIDIx, u16 CH3B);
void MIDI_MCUCH3_CH3A(HT_MIDI_TypeDef* MIDIx, u16 CH3A);
void MIDI_CTRL_MCUCHEN3(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState);
void MIDI_CTRL_MCUCHEN2(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState);
void MIDI_CTRL_MCUCHEN1(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState);
void MIDI_CTRL_MCUCHEN0(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState);
void MIDI_CTRL_DACDS(HT_MIDI_TypeDef* MIDIx, u8 DACDS);
void MIDI_CTRL_MUSICENCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState);
void MIDI_CTRL_SPIRDENCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState);
void MIDI_CTRL_SPIDISLOOPCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState);
void MIDI_CTRL_CHS(HT_MIDI_TypeDef* MIDIx, u8 CHS);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
