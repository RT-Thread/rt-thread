/*********************************************************************************************************//**
 * @file    ht32f5xxxx_midi.c
 * @version $Rev:: 6684         $
 * @date    $Date:: 2023-01-18 #$
 * @brief   This file provides all the MIDI firmware functions.
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f5xxxx_midi.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup MIDI MIDI
  * @brief MIDI driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup MIDI_Private_Define MIDI private definitions
  * @{
  */
/* MIDI TRIG ST Mask                                                                                        */
#define TRIG_ST_ENABLE               (u32)0x00000400
#define TRIG_ST_DISABLE              (u32)0xFFFFFBFF

/* MIDI TRIG VM Mask                                                                                        */
#define TRIG_VM_ENABLE               (u32)0x00000200
#define TRIG_VM_DISABLE              (u32)0xFFFFFDFF

/* MIDI TRIG FR Mask                                                                                        */
#define TRIG_FR_ENABLE               (u32)0x00000100
#define TRIG_FR_DISABLE              (u32)0xFFFFFEFF

/* MIDI CHAN CHx Mask                                                                                       */
#define MIDI_CHAN_CHx_MASK           (u32)0x0000001F

/* MIDI FREQ BL Mask                                                                                        */
#define MIDI_FREQ_BL_MASK            (u32)0x0000F000

/* MIDI FREQ FR Mask                                                                                        */
#define MIDI_FREQ_FR_MASK            (u32)0x00000FFF

/* MIDI VOL AR Mask                                                                                         */
#define MIDI_VOL_AR_MASK             (u32)0x80000000

/* MIDI VOL ENV Mask                                                                                        */
#define MIDI_VOL_ENV_MASK            (u32)0x60000000

/* MIDI VOL VL Mask                                                                                         */
#define MIDI_VOL_VL_MASK             (u32)0x03FF0000

/* MIDI VOL VR Mask                                                                                         */
#define MIDI_VOL_VR_MASK             (u32)0x000003FF

/* MIDI RENUM WBS Mask                                                                                      */
#define MIDI_RENUM_WBS_MASK          (u32)0x00030000

/* MIDI RENUM RE Mask                                                                                       */
#define MIDI_RENUM_RE_MASK           (u32)0x00007FFF

/* MIDI MCUCH0 CH0B Mask                                                                                    */
#define MIDI_MCUCH0_CH0B_MASK        (u32)0xFFFF0000

/* MIDI MCUCH0 CH0A Mask                                                                                    */
#define MIDI_MCUCH0_CH0A_MASK        (u32)0x0000FFFF

/* MIDI MCUCH1 CH1B Mask                                                                                    */
#define MIDI_MCUCH1_CH1B_MASK        (u32)0xFFFF0000

/* MIDI MCUCH1 CH1A Mask                                                                                    */
#define MIDI_MCUCH1_CH1A_MASK        (u32)0x0000FFFF

/* MIDI MCUCH2 CH2B Mask                                                                                    */
#define MIDI_MCUCH2_CH2B_MASK        (u32)0xFFFF0000

/* MIDI MCUCH2 CH2A Mask                                                                                    */
#define MIDI_MCUCH2_CH2A_MASK        (u32)0x0000FFFF

/* MIDI MCUCH3 CH3B Mask                                                                                    */
#define MIDI_MCUCH3_CH3B_MASK        (u32)0xFFFF0000

/* MIDI MCUCH3 CH3A Mask                                                                                    */
#define MIDI_MCUCH3_CH3A_MASK        (u32)0x0000FFFF

/* MIDI CTRL MCUCHEN3 Mask                                                                                  */
#define MCUCHEN3_ENABLE              (u32)0x00008000
#define MCUCHEN3_DISABLE             (u32)0xFFFF7FFF

/* MIDI CTRL MCUCHEN2 Mask                                                                                  */
#define MCUCHEN2_ENABLE              (u32)0x00004000
#define MCUCHEN2_DISABLE             (u32)0xFFFFBFFF

/* MIDI CTRL MCUCHEN1 Mask                                                                                  */
#define MCUCHEN1_ENABLE              (u32)0x00002000
#define MCUCHEN1_DISABLE             (u32)0xFFFFDFFF

/* MIDI CTRL MCUCHEN0 Mask                                                                                  */
#define MCUCHEN0_ENABLE              (u32)0x00001000
#define MCUCHEN0_DISABLE             (u32)0xFFFFEFFF

/* MIDI CTRL DACDS Mask                                                                                     */
#define MIDI_CTRL_DACDS_MASK         (u32)0x00000700

/* MIDI CTRL MUSICEN Mask                                                                                   */
#define MUSICEN_ENABLE               (u32)0x00000080
#define MUSICEN_DISABLE              (u32)0xFFFFFF7F

/* MIDI CTRL SPIRDEN Mask                                                                                   */
#define SPIRDEN_ENABLE               (u32)0x00000040
#define SPIRDEN_DISABLE              (u32)0xFFFFFFBF

/* MIDI CTRL SPIDISLOOP Mask                                                                                */
#define SPIDISLOOP_ENABLE            (u32)0x00000020
#define SPIDISLOOP_DISABLE           (u32)0xFFFFFFDF

/* MIDI CTRL CHS Mask                                                                                       */
#define MIDI_CTRL_CHS_MASK           (u32)0x00000007
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup MIDI_Exported_Functions MIDI exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the MIDI peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void MIDI_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.MIDI = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Initialize the MIDIx peripheral according to the specified parameters in the MIDI_InitStruct.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  MIDI_InitStruct: pointer to a MIDI_InitTypeDef structure that contains the configuration
  *   information for the specified MIDI peripheral.
  * @retval None
  ***********************************************************************************************************/
void MIDI_Init(HT_MIDI_TypeDef* MIDIx, MIDI_InitTypeDef* MIDI_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_CTRL_DACDS(MIDI_InitStruct->MIDI_CTRL_DACDS));
  Assert_Param(IS_MIDI_CTRL_MUSICEN(MIDI_InitStruct->MIDI_CTRL_MUSICEN));
  Assert_Param(IS_MIDI_CTRL_SPIDISLOOP(MIDI_InitStruct->MIDI_CTRL_SPIDISLOOP));
  Assert_Param(IS_MIDI_CTRL_CHS(MIDI_InitStruct->MIDI_CTRL_CHS));
  Assert_Param(IS_MIDI_FREQ_BL(MIDI_InitStruct->MIDI_FREQ_BL));
  Assert_Param(IS_MIDI_FREQ_FR(MIDI_InitStruct->MIDI_FREQ_FR));
  Assert_Param(IS_MIDI_VOL_AR(MIDI_InitStruct->MIDI_VOL_AR));
  Assert_Param(IS_MIDI_VOL_ENV(MIDI_InitStruct->MIDI_VOL_ENV));
  Assert_Param(IS_MIDI_VOL_VL(MIDI_InitStruct->MIDI_VOL_VL));
  Assert_Param(IS_MIDI_VOL_VR(MIDI_InitStruct->MIDI_VOL_VR));
  Assert_Param(IS_MIDI_STADDR(MIDI_InitStruct->MIDI_STADDR));
  Assert_Param(IS_MIDI_RENUM_WBS(MIDI_InitStruct->MIDI_RENUM_WBS));
  Assert_Param(IS_MIDI_RENUM_RE(MIDI_InitStruct->MIDI_RENUM_RE));
  Assert_Param(IS_MIDI_ENDADDR(MIDI_InitStruct->MIDI_ENDADDR));
  Assert_Param(IS_MIDI_CHAN_ST(MIDI_InitStruct->MIDI_CHAN_ST));
  Assert_Param(IS_MIDI_CHAN_VM(MIDI_InitStruct->MIDI_CHAN_VM));
  Assert_Param(IS_MIDI_CHAN_FR(MIDI_InitStruct->MIDI_CHAN_FR));
  Assert_Param(IS_MIDI_CHAN_CHx(MIDI_InitStruct->MIDI_CHAN_CHx));

  MIDIx->CTRL = ((MIDI_InitStruct->MIDI_CTRL_DACDS) << 8) |
                ((MIDI_InitStruct->MIDI_CTRL_MUSICEN) << 7) |
                ((MIDI_InitStruct->MIDI_CTRL_SPIDISLOOP) << 6) |
                (MIDI_InitStruct->MIDI_CTRL_CHS);

  MIDIx->FREQ = ((MIDI_InitStruct->MIDI_FREQ_BL) << 12) |
                (MIDI_InitStruct->MIDI_FREQ_FR);

  MIDIx->VOL = ((MIDI_InitStruct->MIDI_VOL_AR) << 31) |
               ((MIDI_InitStruct->MIDI_VOL_ENV) << 29) |
               ((MIDI_InitStruct->MIDI_VOL_VL) << 16) |
               (MIDI_InitStruct->MIDI_VOL_VR);

  MIDIx->ST_ADDR = MIDI_InitStruct->MIDI_STADDR;

  MIDIx->RE_NUM = ((MIDI_InitStruct->MIDI_RENUM_WBS) << 16) |
                  (MIDI_InitStruct->MIDI_RENUM_RE);

  MIDIx->END_ADDR = MIDI_InitStruct->MIDI_ENDADDR;

  MIDIx->CHAN = ((MIDI_InitStruct->MIDI_CHAN_ST) << 10) |
                ((MIDI_InitStruct->MIDI_CHAN_VM) << 9) |
                ((MIDI_InitStruct->MIDI_CHAN_FR) << 8) |
                (MIDI_InitStruct->MIDI_CHAN_CHx);
}

/*********************************************************************************************************//**
  * @brief  Fill each MIDI_InitStruct member with its default value.
  * @param  MIDI_InitStruct: pointer to an MIDI_InitTypeDef structure which will be initialized.
  * @retval None
  ***********************************************************************************************************/
void MIDI_StructInit(MIDI_InitTypeDef* MIDI_InitStruct)
{
  /* Initialize the MIDI_CTRL_DACDS member                                                                  */
  MIDI_InitStruct->MIDI_CTRL_DACDS = 0x0;

  /* Initialize the MIDI_CTRL_MUSICEN member                                                                */
  MIDI_InitStruct->MIDI_CTRL_MUSICEN = DISABLE;

  /* Initialize the MIDI_CTRL_SPIDISLOOP member                                                             */
  MIDI_InitStruct->MIDI_CTRL_SPIDISLOOP = DISABLE;

  /* Initialize the MIDI_CTRL_CHS member                                                                    */
  MIDI_InitStruct->MIDI_CTRL_CHS = CHS16;

  /* Initialize the MIDI_FREQ_BL member                                                                     */
  MIDI_InitStruct->MIDI_FREQ_BL = BL0;

  /* Initialize the MIDI_FREQ_FR member                                                                     */
  MIDI_InitStruct->MIDI_FREQ_FR = 0x0;

  /* Initialize the MIDI_VOL_AR member                                                                      */
  MIDI_InitStruct->MIDI_VOL_AR = ENV_RELEASE;

  /* Initialize the MIDI_VOL_ENV member                                                                     */
  MIDI_InitStruct->MIDI_VOL_ENV = ENV_NO;

  /* Initialize the MIDI_VOL_VL member                                                                      */
  MIDI_InitStruct->MIDI_VOL_VL = 0x3FF;

  /* Initialize the MIDI_VOL_VR member                                                                      */
  MIDI_InitStruct->MIDI_VOL_VR = 0x3FF;

  /* Initialize the MIDI_STADDR member                                                                      */
  MIDI_InitStruct->MIDI_STADDR = 0x0;

  /* Initialize the MIDI_RENUM_WBS member                                                                   */
  MIDI_InitStruct->MIDI_RENUM_WBS = WBS8;

  /* Initialize the MIDI_RENUM_RE member                                                                    */
  MIDI_InitStruct->MIDI_RENUM_RE = 0x0;

  /* Initialize the MIDI_ENDADDR member                                                                     */
  MIDI_InitStruct->MIDI_ENDADDR = 0x0;

  /* Initialize the MIDI_CHAN_ST member                                                                     */
  MIDI_InitStruct->MIDI_CHAN_ST = DISABLE;

  /* Initialize the MIDI_CHAN_VM member                                                                     */
  MIDI_InitStruct->MIDI_CHAN_VM = DISABLE;

  /* Initialize the MIDI_CHAN_FR member                                                                     */
  MIDI_InitStruct->MIDI_CHAN_FR = DISABLE;

  /* Initialize the MIDI_CHAN_CHx member                                                                    */
  MIDI_InitStruct->MIDI_CHAN_CHx = MIDI_CHx0;
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the specified MIDI interrupt.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  MIDI_Int: specify if the MIDI interrupt source to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg MIDIO_DMAEN             : MIDIO DMAEN
  *     @arg MIDII_DMAEN             : MIDII DMAEN
  *     @arg MIDI_INTEN              : MIDI INTEN
  * @param  NewState: new state of the MIDI interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_IntConfig(HT_MIDI_TypeDef* MIDIx, u32 MIDI_Int, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_INT(MIDI_Int));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->IER |= MIDI_Int;
  }
  else
  {
    MIDIx->IER &= (u32)~MIDI_Int;
  }
}

/*********************************************************************************************************//**
  * @brief  Check whether the specified MIDI flag has been set or not.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  MIDI_Flag: specify the flag that is to be check.
  *   This parameter can be one of the following values:
  *     @arg MIDI_INTF             : MIDI int flag
  * @retval The new state of MIDI_Flag (SET or RESET).
  ***********************************************************************************************************/
FlagStatus MIDI_GetFlagStatus(HT_MIDI_TypeDef* MIDIx, u32 MIDI_Flag)
{
  FlagStatus bitstatus = RESET;
  u32 statusreg = 0;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_FLAG(MIDI_Flag));

  statusreg = MIDIx->SR;

  if ((statusreg & MIDI_Flag) != (u32)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/*********************************************************************************************************//**
  * @brief  Clear the specified MIDI flag.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  MIDI_Flag: specify the flag that is to be cleared.
  *   This parameter can be one of the following values:
  *     @arg MIDI_INTF            : MIDI INTF
  * @retval None
  ***********************************************************************************************************/
void MIDI_ClearFlag(HT_MIDI_TypeDef* MIDIx, u32 MIDI_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_FLAG_CLEAR(MIDI_Flag));

  MIDIx->SR = MIDI_Flag;
}

/*********************************************************************************************************//**
  * @brief  Configure the Channel for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  MCUCHEN3: this parameter can be ENABLE or DISABLE.
  * @param  MCUCHEN2: this parameter can be ENABLE or DISABLE.
  * @param  MCUCHEN1: this parameter can be ENABLE or DISABLE.
  * @param  MCUCHEN0: this parameter can be ENABLE or DISABLE.
  * @param  DACDS: specify the clipping and distorting volume of the MIDI.
  * @param  MUSICEN: this parameter can be ENABLE or DISABLE.
  * @param  SPIRDEN: this parameter can be ENABLE or DISABLE.
  * @param  SPIDISLOOP: this parameter can be ENABLE or DISABLE.
  * @param  CHS: specify channel selection of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CTRL(HT_MIDI_TypeDef* MIDIx,
               MIDI_CTRL_MCUCHEN3_Enum MCUCHEN3, MIDI_CTRL_MCUCHEN2_Enum MCUCHEN2,
               MIDI_CTRL_MCUCHEN1_Enum MCUCHEN1, MIDI_CTRL_MCUCHEN0_Enum MCUCHEN0,
               u8 DACDS,
               MIDI_CTRL_MUSICEN_Enum MUSICEN,
               MIDI_CTRL_SPIRDEN_Enum SPIRDEN, MIDI_CTRL_SPIDISLOOP_Enum SPIDISLOOP,
               MIDI_CTRL_CHS_Enum CHS)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_CTRL_MCUCHEN3(MCUCHEN3));
  Assert_Param(IS_MIDI_CTRL_MCUCHEN2(MCUCHEN2));
  Assert_Param(IS_MIDI_CTRL_MCUCHEN1(MCUCHEN1));
  Assert_Param(IS_MIDI_CTRL_MCUCHEN0(MCUCHEN0));
  Assert_Param(IS_MIDI_CTRL_DACDS(DACDS));
  Assert_Param(IS_MIDI_CTRL_MUSICEN(MUSICEN));
  Assert_Param(IS_MIDI_CTRL_SPIRDEN(SPIRDEN));
  Assert_Param(IS_MIDI_CTRL_SPIDISLOOP(SPIDISLOOP));
  Assert_Param(IS_MIDI_CTRL_CHS(CHS));

  MIDIx->CTRL = (MCUCHEN3 << 15) | (MCUCHEN2 << 14) | (MCUCHEN1 << 13) | (MCUCHEN0 << 12) |
                (DACDS << 8) |
                (MUSICEN << 7) |
                (SPIRDEN << 6) | (SPIDISLOOP << 5) |
                 CHS;
}

/*********************************************************************************************************//**
  * @brief  Configure the FREQ for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  BL: specify octave of the MIDI.
  * @param  FR: specify pitch of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_FREQ(HT_MIDI_TypeDef* MIDIx, MIDI_FREQ_BL_Enum BL, u16 FR)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_FREQ_BL(BL));
  Assert_Param(IS_MIDI_FREQ_FR(FR));

  MIDIx->FREQ = (BL << 12) | FR;
}

/*********************************************************************************************************//**
  * @brief  Configure the VOL for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  A_R: specify attack or release of the MIDI.
  * @param  ENV: specify envelope of the MIDI.
  * @param  VL: specify left channel of the MIDI.
  * @param  VR: specify right channel of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_VOL(HT_MIDI_TypeDef* MIDIx, MIDI_VOL_AR_Enum A_R, MIDI_VOL_ENV_Enum ENV, u16 VL, u16 VR)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_VOL_AR(A_R));
  Assert_Param(IS_MIDI_VOL_ENV(ENV));
  Assert_Param(IS_MIDI_VOL_VL(VL));
  Assert_Param(IS_MIDI_VOL_VR(VR));

  MIDIx->VOL = (A_R << 31) | (ENV << 29) | (VL << 16) | VR;
}

/*********************************************************************************************************//**
  * @brief  Configure the Start Address for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  ST_ADDR: specify start address of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_STADDR(HT_MIDI_TypeDef* MIDIx, u32 ST_ADDR)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_STADDR(ST_ADDR));

  MIDIx->ST_ADDR = ST_ADDR;
}

/*********************************************************************************************************//**
  * @brief  Configure the RENUM for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  WBS: specify waveform of the MIDI.
  * @param  RE: specify repeated code of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_RENUM(HT_MIDI_TypeDef* MIDIx, MIDI_RENUM_WBS_Enum WBS, u16 RE)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_RENUM_WBS(WBS));
  Assert_Param(IS_MIDI_RENUM_RE(RE));

  MIDIx->RE_NUM = (WBS << 16) | RE;
}

/*********************************************************************************************************//**
  * @brief  Configure the End Address for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  END_ADDR: specify end address of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_ENDADDR(HT_MIDI_TypeDef* MIDIx, u32 END_ADDR)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_ENDADDR(END_ADDR));

  MIDIx->END_ADDR = END_ADDR;
}

/*********************************************************************************************************//**
  * @brief  Configure the Channel for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  TRIG_ST: this parameter can be ENABLE or DISABLE.
  * @param  TRIG_VM: this parameter can be ENABLE or DISABLE.
  * @param  TRIG_FR: this parameter can be ENABLE or DISABLE.
  * @param  CHx: specify selected channel of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CHAN(HT_MIDI_TypeDef* MIDIx,
               MIDI_CHAN_ST_Enum TRIG_ST, MIDI_CHAN_VM_Enum TRIG_VM, MIDI_CHAN_FR_Enum TRIG_FR,
               u8 CHx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_CHAN_ST(TRIG_ST));
  Assert_Param(IS_MIDI_CHAN_VM(TRIG_VM));
  Assert_Param(IS_MIDI_CHAN_FR(TRIG_FR));
  Assert_Param(IS_MIDI_CHAN_CHx(CHx));

  MIDIx->CHAN = (TRIG_ST << 10) | (TRIG_VM << 9) | (TRIG_FR << 8) | CHx;
}

/*********************************************************************************************************//**
  * @brief  Configure the MCU CH0 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH0B: specify DATA[31:16] of MCU CH0 of the MIDI.
  * @param  CH0A: specify DATA[15:0] of MCU CH0 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH0(HT_MIDI_TypeDef* MIDIx, u16 CH0B, u16 CH0A)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx11_BH(CH0B));
  Assert_Param(IS_MIDI_MCUCHx11_BL(CH0A));

  MIDIx->MCU_CH0 = (CH0B << 16) | CH0A;
}

/*********************************************************************************************************//**
  * @brief  Configure the MCU CH1 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH1B: specify DATA[31:16] of MCU CH1 of the MIDI.
  * @param  CH1A: specify DATA[15:0] of MCU CH1 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH1(HT_MIDI_TypeDef* MIDIx, u16 CH1B, u16 CH1A)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx12_CH(CH1B));
  Assert_Param(IS_MIDI_MCUCHx12_CL(CH1A));

  MIDIx->MCU_CH1 = (CH1B << 16) | CH1A;
}

/*********************************************************************************************************//**
  * @brief  Configure the MCU CH2 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH2B: specify DATA[31:16] of MCU CH2 of the MIDI.
  * @param  CH2A: specify DATA[15:0] of MCU CH2 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH2(HT_MIDI_TypeDef* MIDIx, u16 CH2B, u16 CH2A)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx13_DH(CH2B));
  Assert_Param(IS_MIDI_MCUCHx13_DL(CH2A));

  MIDIx->MCU_CH2 = (CH2B << 16) | CH2A;
}

/*********************************************************************************************************//**
  * @brief  Configure the MCU CH3 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH3B: specify DATA[31:16] of MCU CH3 of the MIDI.
  * @param  CH3A: specify DATA[15:0] of MCU CH3 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH3(HT_MIDI_TypeDef* MIDIx, u16 CH3B, u16 CH3A)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx14_EH(CH3B));
  Assert_Param(IS_MIDI_MCUCHx14_EL(CH3A));

  MIDIx->MCU_CH3 = (CH3B << 16) | CH3A;
}

/*********************************************************************************************************//**
  * @brief  Configure the FREQ BL for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  BL: specify octave of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_FREQ_BL(HT_MIDI_TypeDef* MIDIx, MIDI_FREQ_BL_Enum BL)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_FREQ_BL(BL));

  /* Clear BL[3:0] in FREQ                                                                                  */
  MIDIx->FREQ &= (u32)~MIDI_FREQ_BL_MASK;

  /* Set new BL[3:0] in FREQ                                                                                */
  MIDIx->FREQ |= (BL << 12);
}

/*********************************************************************************************************//**
  * @brief  Configure the FREQ FR for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  FR: specify pitch of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_FREQ_FR(HT_MIDI_TypeDef* MIDIx, u16 FR)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_FREQ_FR(FR));

  /* Clear FR[11:0] in FREQ                                                                                 */
  MIDIx->FREQ &= (u32)~MIDI_FREQ_FR_MASK;

  /* Set new FR[11:0] in FREQ                                                                               */
  MIDIx->FREQ |= FR;
}

/*********************************************************************************************************//**
  * @brief  Configure the VOL AR for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  A_R: specify attack or release of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_VOL_AR(HT_MIDI_TypeDef* MIDIx, MIDI_VOL_AR_Enum A_R)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_VOL_AR(A_R));

  /* Clear A_R in VOL                                                                                       */
  MIDIx->VOL &= (u32)~MIDI_VOL_AR_MASK;

  /* Set new A_R in VOL                                                                                     */
  MIDIx->VOL |= (A_R << 31);
}

/*********************************************************************************************************//**
  * @brief  Configure the VOL ENV for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  ENV: specify envelope of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_VOL_ENV(HT_MIDI_TypeDef* MIDIx, MIDI_VOL_ENV_Enum ENV)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_VOL_ENV(ENV));

  /* Clear ENV[1:0] in VOL                                                                                  */
  MIDIx->VOL &= (u32)~MIDI_VOL_ENV_MASK;

  /* Set new ENV[1:0] in VOL                                                                                */
  MIDIx->VOL |= (ENV << 29);
}

/*********************************************************************************************************//**
  * @brief  Configure the VOL VL for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  VL: specify left channel of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_VOL_VL(HT_MIDI_TypeDef* MIDIx, u16 VL)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_VOL_VL(VL));

  /* Clear VL[9:0] in VOL                                                                                   */
  MIDIx->VOL &= (u32)~MIDI_VOL_VL_MASK;

  /* Set new VL[9:0] in VOL                                                                                 */
  MIDIx->VOL |= (VL << 16);
}

/*********************************************************************************************************//**
  * @brief  Configure the VOL VR for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  VR: specify right channel of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_VOL_VR(HT_MIDI_TypeDef* MIDIx, u16 VR)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_VOL_VR(VR));

  /* Clear VR[9:0] in VOL                                                                                   */
  MIDIx->VOL &= (u32)~MIDI_VOL_VR_MASK;

  /* Set new VR[9:0] in VOL                                                                                 */
  MIDIx->VOL |= VR;
}

/*********************************************************************************************************//**
  * @brief  Configure the RENUM WBS for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  WBS: specify waveform of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_RENUM_WBS(HT_MIDI_TypeDef* MIDIx, MIDI_RENUM_WBS_Enum WBS)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_RENUM_WBS(WBS));

  /* Clear WBS[1:0] in RENUM                                                                                */
  MIDIx->RE_NUM &= (u32)~MIDI_RENUM_WBS_MASK;

  /* Set new WBS[1:0] in RENUM                                                                              */
  MIDIx->RE_NUM |= (WBS << 16);
}

/*********************************************************************************************************//**
  * @brief  Configure the RENUM RE for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  RE: specify repeated code of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_RENUM_RE(HT_MIDI_TypeDef* MIDIx, u16 RE)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_RENUM_RE(RE));

  /* Clear RE[14:0] in RENUM                                                                                */
  MIDIx->RE_NUM &= (u32)~MIDI_RENUM_RE_MASK;

  /* Set new RE[14:0] in RENUM                                                                              */
  MIDIx->RE_NUM |= RE;
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable ST ADDR for the specified MIDI peripheral.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  NewState: new state of the MIDIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CHAN_STCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->CHAN |= TRIG_ST_ENABLE;
  }
  else
  {
    MIDIx->CHAN &= (TRIG_ST_DISABLE);
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable VM for the specified MIDI peripheral.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  NewState: new state of the MIDIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CHAN_VMCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->CHAN |= TRIG_VM_ENABLE;
  }
  else
  {
    MIDIx->CHAN &= (TRIG_VM_DISABLE);
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable FR for the specified MIDI peripheral.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  NewState: new state of the MIDIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CHAN_FRCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->CHAN |= TRIG_FR_ENABLE;
  }
  else
  {
    MIDIx->CHAN &= (TRIG_FR_DISABLE);
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the Selected Channel for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CHx: specify selected channel of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CHAN_CHx(HT_MIDI_TypeDef* MIDIx, u8 CHx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_CHAN_CHx(CHx));

  /* Clear CHx[4:0] in CHAN                                                                                 */
  MIDIx->CHAN &= (u32)~MIDI_CHAN_CHx_MASK;

  /* Set new CHx[4:0] in CHAN                                                                               */
  MIDIx->CHAN |= CHx;
}

/*********************************************************************************************************//**
  * @brief  Configure the CH0B of MCU CH0 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH0B: specify DATA[31:16] of MCU CH0 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH0_CH0B(HT_MIDI_TypeDef* MIDIx, u16 CH0B)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx11_BH(CH0B));

  /* Clear CH0B[16:0] in MCUCH0                                                                             */
  MIDIx->MCU_CH0 &= (u32)~MIDI_MCUCH0_CH0B_MASK;

  /* Set new CH0B[16:0] in MCUCH0                                                                           */
  MIDIx->MCU_CH0 |= (CH0B << 16);
}

/*********************************************************************************************************//**
  * @brief  Configure the CH0A of MCU CH0 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH0A: specify DATA[15:0] of MCU CH0 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH0_CH0A(HT_MIDI_TypeDef* MIDIx, u16 CH0A)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx11_BL(CH0A));

  /* Clear CH0B[16:0] in MCUCH0                                                                             */
  MIDIx->MCU_CH0 &= (u32)~MIDI_MCUCH0_CH0A_MASK;

  /* Set new CH0B[16:0] in MCUCH0                                                                           */
  MIDIx->MCU_CH0 |= CH0A;
}

/*********************************************************************************************************//**
  * @brief  Configure the CH1B of MCU CH1 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH1B: specify DATA[31:16] of MCU CH1 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH1_CH1B(HT_MIDI_TypeDef* MIDIx, u16 CH1B)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx12_CH(CH1B));

  /* Clear CH0B[16:0] in MCUCH0                                                                             */
  MIDIx->MCU_CH1 &= (u32)~MIDI_MCUCH1_CH1B_MASK;

  /* Set new CH1B[16:0] in MCUCH1                                                                           */
  MIDIx->MCU_CH1 |= (CH1B << 16);
}

/*********************************************************************************************************//**
  * @brief  Configure the CH1A of MCU CH1 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH1A: specify DATA[15:0] of MCU CH1 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH1_CH1A(HT_MIDI_TypeDef* MIDIx, u16 CH1A)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx12_CL(CH1A));

  /* Clear CH1A[16:0] in MCUCH1                                                                             */
  MIDIx->MCU_CH1 &= (u32)~MIDI_MCUCH1_CH1A_MASK;

  /* Set new CH1A[16:0] in MCUCH1                                                                           */
  MIDIx->MCU_CH1 |= CH1A;
}

/*********************************************************************************************************//**
  * @brief  Configure the CH2B of MCU CH2 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH2B: specify DATA[31:16] of MCU CH2 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH2_CH2B(HT_MIDI_TypeDef* MIDIx, u16 CH2B)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx13_DH(CH2B));

  /* Clear CH2B[16:0] in MCUCH2                                                                             */
  MIDIx->MCU_CH2 &= (u32)~MIDI_MCUCH2_CH2B_MASK;

  /* Set new CH2B[16:0] in MCUCH2                                                                           */
  MIDIx->MCU_CH2 |= (CH2B << 16);
}

/*********************************************************************************************************//**
  * @brief  Configure the CH2A of MCU CH2 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH2A: specify DATA[15:0] of MCU CH2 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH2_CH2A(HT_MIDI_TypeDef* MIDIx, u16 CH2A)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx13_DL(CH2A));

  /* Clear CH2A[16:0] in MCUCH2                                                                             */
  MIDIx->MCU_CH2 &= (u32)~MIDI_MCUCH2_CH2A_MASK;

  /* Set new CH2A[16:0] in MCUCH2                                                                           */
  MIDIx->MCU_CH2 |= CH2A;
}

/*********************************************************************************************************//**
  * @brief  Configure the CH3B of MCU CH3 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH3B: specify DATA[31:16] of MCU CH3 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH3_CH3B(HT_MIDI_TypeDef* MIDIx, u16 CH3B)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx14_EH(CH3B));

  /* Clear CH3B[16:0] in MCUCH3                                                                             */
  MIDIx->MCU_CH3 &= (u32)~MIDI_MCUCH3_CH3B_MASK;

  /* Set new CH3B[16:0] in MCUCH3                                                                           */
  MIDIx->MCU_CH3 |= (CH3B << 16);
}

/*********************************************************************************************************//**
  * @brief  Configure the CH3A of MCU CH3 DATA for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CH3A: specify DATA[15:0] of MCU CH3 of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_MCUCH3_CH3A(HT_MIDI_TypeDef* MIDIx, u16 CH3A)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_MCUCHx14_EL(CH3A));

  /* Clear CH3A[16:0] in MCUCH3                                                                             */
  MIDIx->MCU_CH3 &= (u32)~MIDI_MCUCH3_CH3A_MASK;

  /* Set new CH3A[16:0] in MCUCH3                                                                           */
  MIDIx->MCU_CH3 |= CH3A;
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable MCU CHEN3 for the specified MIDI peripheral.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  NewState: new state of the MIDIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CTRL_MCUCHEN3(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->CTRL |= MCUCHEN3_ENABLE;
  }
  else
  {
    MIDIx->CTRL &= MCUCHEN3_DISABLE;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable MCU CHEN2 for the specified MIDI peripheral.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  NewState: new state of the MIDIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CTRL_MCUCHEN2(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->CTRL |= MCUCHEN2_ENABLE;
  }
  else
  {
    MIDIx->CTRL &= MCUCHEN2_DISABLE;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable MCU CHEN1 for the specified MIDI peripheral.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  NewState: new state of the MIDIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CTRL_MCUCHEN1(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->CTRL |= MCUCHEN1_ENABLE;
  }
  else
  {
    MIDIx->CTRL &= MCUCHEN1_DISABLE;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable MCU CHEN0 for the specified MIDI peripheral.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  NewState: new state of the MIDIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CTRL_MCUCHEN0(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->CTRL |= MCUCHEN0_ENABLE;
  }
  else
  {
    MIDIx->CTRL &= MCUCHEN0_DISABLE;
  }
}


/*********************************************************************************************************//**
  * @brief  Configure the DACDS for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  DACDS: specify the clipping and distorting volume of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CTRL_DACDS(HT_MIDI_TypeDef* MIDIx, u8 DACDS)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_CTRL_DACDS(DACDS));

  /* Clear DACDS[2:0] in CTRL                                                                               */
  MIDIx->CTRL &= (u32)~MIDI_CTRL_DACDS_MASK;

  /* Set new DACDS[2:0] in CTRL                                                                             */
  MIDIx->CTRL |= (DACDS << 8);
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable MUSIC Engine for the specified MIDI peripheral.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  NewState: new state of the MIDIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CTRL_MUSICENCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->CTRL |= MUSICEN_ENABLE;
  }
  else
  {
    MIDIx->CTRL &= MUSICEN_DISABLE;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable SPI RDEN for the specified MIDI peripheral.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  NewState: new state of the MIDIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CTRL_SPIRDENCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->CTRL |= SPIRDEN_ENABLE;
  }
  else
  {
    MIDIx->CTRL &= SPIRDEN_DISABLE;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable SPI DISLOOP for the specified MIDI peripheral.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  NewState: new state of the MIDIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CTRL_SPIDISLOOPCmd(HT_MIDI_TypeDef* MIDIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    MIDIx->CTRL |= SPIDISLOOP_ENABLE;
  }
  else
  {
    MIDIx->CTRL &= SPIDISLOOP_DISABLE;
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the Channel Selection for the selected MIDI.
  * @param  MIDIx: where MIDIx is the selected MIDI from the MIDI peripherals.
  * @param  CHS: specify channel selection of the MIDI.
  * @retval None
  ***********************************************************************************************************/
void MIDI_CTRL_CHS(HT_MIDI_TypeDef* MIDIx, u8 CHS)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_MIDI(MIDIx));
  Assert_Param(IS_MIDI_CTRL_CHS(CHS));

  /* Clear CHS[2:0] in CTRL                                                                                 */
  MIDIx->CTRL &= (u32)~MIDI_CTRL_CHS_MASK;

  /* Set new CHS[2:0] in CTRL                                                                               */
  MIDIx->CTRL |= CHS;
}

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */
