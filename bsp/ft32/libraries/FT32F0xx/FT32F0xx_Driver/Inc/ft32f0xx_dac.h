/**
  ******************************************************************************
  * @file               ft32f0xx_dac.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the DAC firmware
  *                     library.
  * @version            V1.0.0
  * @data                   2021-07-01
  ******************************************************************************
  */
#ifndef __FT32F0XX_DAC_H
#define __FT32F0XX_DAC_H


#include "ft32f0xx.h"



/**
    *   @Parama DAC_CTRL
    */

#define DAC_DATA_RESET          ((uint32_t)(0x0000007f))

#define DAC_CTRL_READ               (uint8_t)(0x20)
#define DAC_DATA1_READ          (uint8_t)(0x24)
#define DAC_DATA2_READ          (uint8_t)(0x28)


#define IS_DAC_DATA(DATA) ((DATA) <= 0x7F)


/**
    *   @Parama DAC1_DATA
    */
void DAC_Ref_Config(uint32_t    DAC_RefSel);
void Bsp_DAC_Config(void);
uint8_t DAC_Read_Reg(uint8_t DAC_Register);
void DAC_Cmd(FunctionalState NewState);
void DAC_SetChannel1Data(uint32_t DAC_Align, uint8_t Data);
void DAC_SetChannel2Data(uint32_t DAC_Align, uint8_t Data);

#endif
