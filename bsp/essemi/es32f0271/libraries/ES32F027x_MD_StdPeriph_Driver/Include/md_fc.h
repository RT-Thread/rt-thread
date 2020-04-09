/**
  ******************************************************************************
  * @file    md_FC.h
  * @brief   ES32F0271 FC HEAD File.
  *
  * @version V1.00.01
  * @date    11/20/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MD_FC_H__
#define __MD_FC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------*/
#include "es32f0271.h"
#include "reg_fc.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (FC)

/** @defgroup  FC  FC
  * @brief FC micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Public types ---------------------------------------------------------------*/
/** @defgroup MD_FC_Public_Types FC Public Types
  * @{
  */

/**
  * @brief MD FC Parameter Structure definition
  */
typedef struct
{
  uint32_t SAddr;      /*!< Specifies the FC sector address to be erased.
                This parameter should be aligned with 0x400*/

  uint32_t SAddrC;    /*!< Specifies the complement of FC sector address to be erased.
                This parameter should be the complement of FC page address*/

  uint16_t BCnt;      /*!< Specifies the control byte count.
                For program, this parameter should be aligned with 8 and smaller than 0x400
                For read, this parameter should be aligned with 4*/
                
  uint32_t *pU32Buf;    /*!< Specifies the uint32_t data buffer to program.
                This parameter should be the pointer to uint32_t*/
                
} md_fc_ControlTypeDef;

/**
  * @brief MD FC Update Protect Level Structure definition
  */
typedef struct
{
  uint32_t UpdateL;    /*!< Specifies the protect page bit mapping low byte (page 31~0) (0=protect, 1=unprotect).
                This parameter can be any value between 0~65535*/

  uint32_t UpdateH;    /*!< Specifies the protect page bit mapping high byte (page 63~32) (0=protect, 1=unprotect).
                This parameter can be any value between 0~65535*/

  uint32_t ClearL;    /*!< Specifies the reserve page bit mapping low byte (page 31~0) (0=reserve, 1=erase).
                This parameter can be any value between 0~65535*/
                
  uint32_t ClearH;    /*!< Specifies the reserve page bit mapping high byte (page 63~32) (0=reserve, 1=erase).
                This parameter can be any value between 0~65535*/
                
} md_fc_UpdProtTypeDef;

/**
  * @} MD_FC_Public_Types
  */

/* Public constants -----------------------------------------------------------*/
/** @defgroup MD_FC_Public_Constants FC Public Constants
  * @{
  */

#define MD_FC_PC_EF_MPAGESZ          (0x00000400UL)    /** @brief Select main page size */
#define MD_FC_PC_EF_IPAGESZ          (0x00000400UL)    /** @brief Select information page size */
#define MD_FC_PC_EF_MERASEID        (0xA5A5AA55UL)    /** @brief Select main erase ID */

#define  MD_FC_PC_CMD_PROG_EFLASH        (0xF0)        /** @brief Program EFlash  */
#define  MD_FC_PC_CMD_SECTOR_ERASE        (0xF1)        /** @brief Sector Erase  */
#define  MD_FC_PC_CMD_MACRO_ERASE        (0xF2)        /** @brief Macro Erase  */
#define  MD_FC_PC_CMD_UPDATE_LV1_PROTECT      (0xF3)        /** @brief Update Lv1 Protect  */
#define  MD_FC_PC_CMD_UPDATE_LV2_PROTECT      (0xF4)        /** @brief Update Lv2 Protect  */
#define  MD_FC_PC_CMD_OPTION_BYTE_ERASE      (0xF5)        /** @brief Option Byte Erase(Only for ISP)  */

#define  MD_FC_PC_SREMAP_MAIN          (0x00)        /** @brief Main Flash memory mapped at 0x0000 0000  */
#define  MD_FC_PC_SREMAP_SYSTEM          (0x01)        /** @brief System Flash memory mapped at 0x0000 0000  */
#define  MD_FC_PC_SREMAP_SRAM          (0x02)        /** @brief SRAM mapped at 0x0000 0000  */

/**
  * @} MD_FC_Public_Constants
  */

/* Public macro ---------------------------------------------------------------*/
/** @defgroup MD_FC_Public_Macros FC Public Macros
  * @{
  */

/** @defgroup MD_FC_PM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in FC register
  * @param  __INSTANCE__ FC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MD_FC_WRITEREG(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in FC register
  * @param  __INSTANCE__ FC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define MD_FC_READREG(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)

/**
  * @brief  Modify value in FC register
  * @param  __INSTANCE__ FC Instance
  * @param  __REG__ Register to be written
  * @param  __MASK__ Mask value to be written in the register
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define MD_FC_MODIFYREG(__INSTANCE__, __REG__, __MASK__, __VALUE__) MODIFY_REG(__INSTANCE__->__REG__, __MASK__, (__VALUE__))

/**
  * @brief  Set bit value in FC register
  * @param  __INSTANCE__ FC Instance
  * @param  __REG__ Register to be written
  * @param  __MASK__ Mask value to be set in the register
  * @retval None
  */
#define MD_FC_SET_BIT(__INSTANCE__, __REG__, __MASK__) SET_BIT(__INSTANCE__->__REG__, __MASK__)

/**
  * @brief  Clear bit value in FC register
  * @param  __INSTANCE__ FC Instance
  * @param  __REG__ Register to be written
  * @param  __MASK__ Mask value to be cleared in the register
  * @retval None
  */
#define MD_FC_CLEAR_BIT(__INSTANCE__, __REG__, __MASK__) CLEAR_BIT(__INSTANCE__->__REG__, __MASK__)

/**
  * @brief  Read bit value in FC register
  * @param  __INSTANCE__ FC Instance
  * @param  __REG__ Register to be read
  * @param  __MASK__ Mask value to be read in the register
  * @retval Register bit value
  */
#define MD_FC_READBIT(__INSTANCE__, __REG__, __MASK__) READ_BIT(__INSTANCE__->__REG__, __MASK__)

/**
  * @} MD_FC_PM_WRITE_READ
  */

/** @defgroup MD_FC_Macro_Drivers FC Public Macro Drivers
  * @{
  */

/**
  * @brief  Set FC CMD
  * @param  @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_fc_set_cmd(uint32_t U32)
{
  MD_FC_WRITEREG(FC, CMD, U32);
}

/**
  * @brief  Get FC CMD
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_cmd(void)
{
  return (MD_FC_READREG(FC, CMD));
}

/**
  * @brief  Set FC CMD Flash Command
  * @note  After procedure is finished, Flash command will be cleaned by itself
  * @param  @arg @ref MD_FC_PC_CMD_PROG_EFLASH(0xF0) : Program EFlash
  *         @arg @ref MD_FC_PC_CMD_SECTOR_ERASE(0xF1) : Sector Erase
  *         @arg @ref MD_FC_PC_CMD_MACRO_ERASE(0xF2) : Macro Erase
  *         @arg @ref MD_FC_PC_CMD_UPDATE_LV1_PROTECT(0xF3) : Update Lv1 Protect
  *         @arg @ref MD_FC_PC_CMD_UPDATE_LV2_PROTECT(0xF4) : Update Lv2 Protect
  *         @arg @ref MD_FC_PC_CMD_OPTION_BYTE_ERASE(0xF5) : Option Byte Erase(Only for ISP)
  *         @arg Else : Reserved 
  * @retval None
  */
__STATIC_INLINE void md_fc_set_fc_cmd(uint32_t Cmd)
{
  MD_FC_MODIFYREG(FC, CMD, FC_CMD_FC_CMD_MSK, (Cmd<<FC_CMD_FC_CMD_POSS));
}

/**
  * @brief  Get FC CMD Flash Command
  * @note  After procedure is finished, Flash command will be cleaned by itself
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_FC_PC_CMD_PROG_EFLASH(0xF0) : Program EFlash
  *         @arg @ref MD_FC_PC_CMD_SECTOR_ERASE(0xF1) : Sector Erase
  *         @arg @ref MD_FC_PC_CMD_MACRO_ERASE(0xF2) : Macro Erase
  *         @arg @ref MD_FC_PC_CMD_UPDATE_LV1_PROTECT(0xF3) : Update Lv1 Protect
  *         @arg @ref MD_FC_PC_CMD_UPDATE_LV2_PROTECT(0xF4) : Update Lv2 Protect
  *         @arg @ref MD_FC_PC_CMD_OPTION_BYTE_ERASE(0xF5) : Option Byte Erase(Only for ISP)
  *         @arg Else:Reserved 
  */
__STATIC_INLINE uint32_t md_fc_get_fc_cmd(void)
{
  return (MD_FC_READBIT(FC, CMD, FC_CMD_FC_CMD_MSK)>>FC_CMD_FC_CMD_POSS);
}

/**
  * @brief  Set FC PA
  * @param  @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_fc_set_pa(uint32_t U32)
{
  MD_FC_WRITEREG(FC, PA, U32);
}

/**
  * @brief  Get FC PA
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_pa(void)
{
  return (MD_FC_READREG(FC, PA));
}

/**
  * @brief  Set FC Program Counter
  * @note  Provide maximum 128 times continuous program
  * @note  Meanwhile user needs to fill out FC_PLD, FC_PHD and FC_CMD only
  * @param  @arg Max Value 0x7f
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_fc_set_pa_pcnt(uint32_t PCnt)
{
  MD_FC_MODIFYREG(FC, PA, FC_PA_PCNT_MSK, (((PCnt>>3)-1)<<FC_PA_PCNT_POSS));
}

/**
  * @brief  Get FC Program Counter
  * @note  Provide maximum 128 times continuous program
  * @note  Meanwhile user needs to fill out FC_PLD, FC_PHD and FC_CMD only
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x7f
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint8_t md_fc_get_pa_pcnt(void)
{
  return (MD_FC_READBIT(FC, PA, FC_PA_PCNT_MSK)>>FC_PA_PCNT_POSS);
}

/**
  * @brief  Enable FC Information Block
  * @note  User can program/erase Info. Block page 7 when Flash protect is disable
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_fc_enable_pa_ifren(void)
{
  MD_FC_SET_BIT(FC, PA, FC_PA_IFREN_MSK);
}

/**
  * @brief  Disable FC Information Block
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_fc_disble_pa_ifren(void)
{
  MD_FC_CLEAR_BIT(FC, PA, FC_PA_IFREN_MSK);
}

/**
  * @brief  Is FC Information Block Enabled
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg 0x1 : Enable
  *         @arg 0x0 : Disable
  */
__STATIC_INLINE uint8_t md_fc_is_enabled_pa_ifren(void)
{
  return (MD_FC_READBIT(FC, PA, FC_PA_IFREN_MSK)>>FC_PA_IFREN_POS);
}

/**
  * @brief  Set FC Program/Erase Address
  * @note  Program : PROG_ADDR[15:3] is double word address
  * @note  Sector Erase : PROG_ADDR[15:10] is page address, and PROG_ADDR[9:0] don・t care
  * @note  Macro Erase : PROG_ADDR[15:0] don・t care
  * @param  @arg Max Value 0xffc0
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_fc_set_pa_prog_addr(uint32_t PAddr)
{
  MD_FC_MODIFYREG(FC, PA, FC_PA_PROG_ADDR_MSK, (PAddr<<FC_PA_PROG_ADDR_POSS));
}

/**
  * @brief  Get FC Program/Erase Address
  * @note  Program : PROG_ADDR[15:3] is double word address
  * @note  Sector Erase : PROG_ADDR[15:10] is page address, and PROG_ADDR[9:0] don・t care
  * @note  Macro Erase : PROG_ADDR[15:0] don・t care
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffc0
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_pa_prog_addr(void)
{
  return (MD_FC_READBIT(FC, PA, FC_PA_PROG_ADDR_MSK)>>FC_PA_PROG_ADDR_POSS);
}

/**
  * @brief  Set FC Program Low Data
  * @note  Eflash supports 64 bits data program, this register provides Low 32 bits data
  * @param  @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_fc_set_pld(uint32_t U32)
{
  MD_FC_WRITEREG(FC, PLD, U32);
}

/**
  * @brief  Get FC Program Low Data
  * @note  Eflash supports 64 bits data program, this register provides Low 32 bits data
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_pld(void)
{
  return (MD_FC_READREG(FC, PLD));
}

/**
  * @brief  Set FC Program High Data
  * @note  Eflash supports 64 bits data program, this register provides high 32 bits data
  * @param  @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_fc_set_phd(uint32_t U32)
{
  MD_FC_WRITEREG(FC, PHD, U32);
}

/**
  * @brief  Get FC Program High Data
  * @note  Eflash supports 64 bits data program, this register provides high 32 bits data
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_phd(void)
{
  return (MD_FC_READREG(FC, PHD));
}

/**
  * @brief  Set FC CON
  * @param  @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_fc_set_con(uint32_t U32)
{
  MD_FC_WRITEREG(FC, CON, U32);
}

/**
  * @brief  Get FC CON
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_con(void)
{
  return (MD_FC_READREG(FC, CON));
}

/**
  * @brief  Enable FC Control Sleep
  * @note  When receive sleep or deep sleep from CPU, controller will mask Eflash control signal when this option is selected.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_fc_enable_con_sleep(void)
{
  MD_FC_SET_BIT(FC, CON, FC_CON_SLEEP_MSK);
}

/**
  * @brief  Disable FC Control Sleep
  * @note  When receive sleep or deep sleep from CPU, controller will mask Eflash control signal when this option is selected.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_fc_disable_con_sleep(void)
{
  MD_FC_CLEAR_BIT(FC, CON, FC_CON_SLEEP_MSK);
}

/**
  * @brief  Is FC Control Sleep Enabled
  * @note  When receive sleep or deep sleep from CPU, controller will mask Eflash control signal when this option is selected.
  * @param  None
  * @retval The retval can be one of the following values:
  *     0x0:Disable Flash sleep mask function
  *     0x1:Enable Flash sleep mask function
  */
__STATIC_INLINE uint8_t md_fc_is_enabled_con_sleep(void)
{
  return (MD_FC_READBIT(FC, CON, FC_CON_SLEEP_MSK)>>FC_CON_SLEEP_POS);
}

/**
  * @brief  Enable FC Control PreFetch
  * @note  This function allow user to pre-fetch 64 bits data from Eflash when the last 32bits data in data buffer has been read
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_fc_enable_con_pfen(void)
{
  MD_FC_SET_BIT(FC, CON, FC_CON_PFEN_MSK);
}

/**
  * @brief  Disable FC Control PreFetch
  * @note  This function allow user to pre-fetch 64 bits data from Eflash when the last 32bits data in data buffer has been read
  * @param  None
  * @retval None
  */
__STATIC_INLINE void md_fc_disable_con_pfen(void)
{
  MD_FC_CLEAR_BIT(FC, CON, FC_CON_PFEN_MSK);
}

/**
  * @brief  Is FC Control PreFetch Enabled
  * @note  This function allow user to pre-fetch 64 bits data from Eflash when the last 32bits data in data buffer has been read
  * @param  None
  * @retval The retval can be one of the following values:
  *     0x0:Disable pre-fetch function
  *     0x1:Enable pre-fetch function
  */
__STATIC_INLINE uint8_t md_fc_is_enabled_con_pfen(void)
{
  return (MD_FC_READBIT(FC, CON, FC_CON_PFEN_MSK)>>FC_CON_PFEN_POS);
}

/**
  * @brief  Set FC Control Wait Cycle
  * @note  Eflash supports 64 bits data program, this register provides high 32 bits data
  * @param  @arg Max Value 0x3
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_fc_set_con_wait(uint32_t Wait)
{
  MD_FC_MODIFYREG(FC, CON, FC_CON_WAIT_MSK, (Wait<<FC_CON_WAIT_POSS));
}

/**
  * @brief  Get FC Control Wait Cycle
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x3
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint8_t md_fc_get_con_wait(void)
{
  return (MD_FC_READBIT(FC, CON, FC_CON_WAIT_MSK)>>FC_CON_WAIT_POSS);
}

/**
  * @brief  Get FC STAT
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_sta(void)
{
  return (MD_FC_READREG(FC, STAT));
}

/**
  * @brief  Get FC Status Option Valid
  * @note  This bit is set when Option Byte Data is valid
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1 : Option Byte Data is valid
  *         @arg Min Value 0x0 : Option Byte Data is invalid
  */
__STATIC_INLINE uint8_t md_fc_get_stat_opvd(void)
{
  return (MD_FC_READBIT(FC, STAT, FC_STAT_OPVD_MSK)>>FC_STAT_OPVD_POS);
}

/**
  * @brief  Get FC Status Main Unprotect Level2 Status
  * @note  This bit is set when Flash main block is unprotect
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1 : Lv2 Protect Function is disabled
  *         @arg Min Value 0x0 : Lv2 Protect Function is enabled
  */
__STATIC_INLINE uint8_t md_fc_get_stat_munp2(void)
{
  return (MD_FC_READBIT(FC, STAT, FC_STAT_MUNP2_MSK)>>FC_STAT_MUNP2_POS);
}

/**
  * @brief  Get FC Status Main Unprotect Level1 Status
  * @note  This bit is set when Flash main block is unprotect
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0x1 : Lv1 Protect Function is disabled
  *         @arg Min Value 0x0 : Lv1 Protect Function is enabled
  */
__STATIC_INLINE uint8_t md_fc_get_stat_munp1(void)
{
  return (MD_FC_READBIT(FC, STAT, FC_STAT_MUNP1_MSK)>>FC_STAT_MUNP1_POS);
}

/**
  * @brief  Set FC Protect Update Low Data
  * @note  Update main block Lv2 Protect Page 0 ~ Page 31
  * @param  @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_fc_set_upl(uint32_t U32)
{
  MD_FC_WRITEREG(FC, UPL, U32);
}

/**
  * @brief  Get FC Protect Update Low Data
  * @note  Update main block Lv2 Protect Page 0 ~ Page 31
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_upl(void)
{
  return (MD_FC_READREG(FC, UPL));
}

/**
  * @brief  Set FC Protect Update High Data
  * @note  Update main block Lv2 Protect Page 63 ~ Page 32
  * @param  @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  * @retval None
  */
__STATIC_INLINE void md_fc_set_uph(uint32_t U32)
{
  MD_FC_WRITEREG(FC, UPH, U32);
}

/**
  * @brief  Get FC Protect Update High Data
  * @note  Update main block Lv2 Protect Page 63 ~ Page 32
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_uph(void)
{
  return (MD_FC_READREG(FC, UPH));
}

/**
  * @brief  Get FC OP_TRIM
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_op_trim(void)
{
  return (MD_FC_READREG(FC, OP_TRIM));
}

/**
  * @brief  Get FC OP_TRIM BangGap trim valid
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xff
  *         @arg Min Value 0x0
  *         @arg Value 0xa5 BG Trim is Valid
  */
__STATIC_INLINE uint32_t md_fc_get_op_trim_bgtrimvd(void)
{
  return (MD_FC_READBIT(FC, OP_TRIM, FC_OP_TRIM_BGTRIMVD_MSK)>>FC_OP_TRIM_BGTRIMVD_POSS);
}

/**
  * @brief  Get FC Trim BangGap trim value
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_op_trim_bgtrim(void)
{
  return (MD_FC_READBIT(FC, OP_TRIM, FC_OP_TRIM_BGTRIM_MSK)>>FC_OP_TRIM_BGTRIM_POSS);
}

/**
  * @brief  Get FC Trim HRC calibration value valid
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xff
  *         @arg Min Value 0x0
  *         @arg Value 0xa5 BG Trim is Valid
  */
__STATIC_INLINE uint32_t md_fc_get_op_trim_hrctrimvd(void)
{
  return (MD_FC_READBIT(FC, OP_TRIM, FC_OP_TRIM_HRCTRIMVD_MSK)>>FC_OP_TRIM_HRCTRIMVD_POSS);
}

/**
  * @brief  Get FC Trim HRC calibration value
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_op_trim_hrctrim(void)
{
  return (MD_FC_READBIT(FC, OP_TRIM, FC_OP_TRIM_HRCTRIM_MSK)>>FC_OP_TRIM_HRCTRIM_POSS);
}

/**
  * @brief  Get FC Lv2 Protect Low 32 bits
  * @note  Lv2 Protect Page 0 ~ Page 31.The Bit is set to 0 when the page is protected
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_op_prt2l(void)
{
  return (MD_FC_READREG(FC, OP_PRT2L));
}

/**
  * @brief  Get FC Lv2 Protect High 32 bits
  * @note  Lv2 Protect Page 63 ~ Page 32.The Bit is set to 0 when the page is protected
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_op_prt2h(void)
{
  return (MD_FC_READREG(FC, OP_PRT2H));
}

/**
  * @brief  Get FC Lv1 Protect Low 32 bits
  * @note  Lv1 Protect Page 0 ~ Page 31.The Bit is set to 0 when the page is protected
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_op_prt1l(void)
{
  return (MD_FC_READREG(FC, OP_PRT1L));
}

/**
  * @brief  Get FC Lv1 Protect High 32 bits
  * @note  Lv1 Protect Page 63 ~ Page 32.The Bit is set to 0 when the page is protected
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_op_prt1h(void)
{
  return (MD_FC_READREG(FC, OP_PRT1H));
}

/**
  * @brief  Get FC OP_REMAP
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xffffffff
  *         @arg Min Value 0x0
  */
__STATIC_INLINE uint32_t md_fc_get_op_remap(void)
{
  return (MD_FC_READREG(FC, OP_REMAP));
}

/**
  * @brief  Get FC Hardware Remap Option
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xff
  *         @arg Min Value 0x0
  *         @arg Value 0xa5 skip boot loader
  */
__STATIC_INLINE uint8_t md_fc_get_op_remap_hremap(void)
{
  return (MD_FC_READBIT(FC, OP_REMAP, FC_OP_REMAP_HREMAP_MSK)>>FC_OP_REMAP_HREMAP_POSS);
}

/**
  * @brief  Get FC Software Remap Option
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg @ref MD_FC_PC_SREMAP_MAIN(0x0) : Main Flash memory mapped at 0x0000 0000
  *         @arg @ref MD_FC_PC_SREMAP_SYSTEM(0x1) : System Flash memory mapped at 0x0000 0000
  *         @arg @ref MD_FC_PC_SREMAP_SRAM(0x2) : SRAM mapped at 0x0000 0000
  *         @arg Else : Reserved
  */
__STATIC_INLINE uint8_t md_fc_get_op_remap_sremap(void)
{
  return (MD_FC_READBIT(FC, OP_REMAP, FC_OP_REMAP_SREMAP_MSK)>>FC_OP_REMAP_SREMAP_POSS);
}

/**
  * @brief  Get FC Software Remap Base Address Settng Data
  * @note  If set 0x1, it means second 4k Byte, If set 0x2, it means third 4k Byte, and so on
  * @param  None
  * @retval The retval can be one of the following values:
  *         @arg Max Value 0xf
  *         @arg Min Value 0x0
  * @note  This value is invalid if the value in SREMAP field is 0x3  
  */
__STATIC_INLINE uint8_t md_fc_get_op_remap_sefbase(void)
{
  return (MD_FC_READBIT(FC, OP_REMAP, FC_OP_REMAP_SEFBASE_MSK)>>FC_OP_REMAP_SEFBASE_POSS);
}

/**
  * @} MD_FC_Macro_Drivers
  */

/**
  * @} MD_FC_Public_Macros
  */

/* Public functions -----------------------------------------------------------*/
/** @defgroup MD_FC_Public_Functions FC Public Functions
  * @{
  */
ErrorStatus  md_fc_merase(uint32_t MEraseID);
ErrorStatus  md_fc_serase(md_fc_ControlTypeDef *pSErasePara);
ErrorStatus  md_fc_program(md_fc_ControlTypeDef *pProgramPara);
ErrorStatus  md_fc_read(md_fc_ControlTypeDef *pReadPara);
ErrorStatus  md_fc_updprotl1(md_fc_UpdProtTypeDef *pUpdPL1Para);
ErrorStatus  md_fc_updprotl2(md_fc_UpdProtTypeDef *pUpdPL2Para);
ErrorStatus  md_fc_updremap(uint8_t UpdRemap);
/**
  * @}  MD_FC_Public_Functions
  */

#endif

/**
  * @}  FC
  */

/** 
  * @}  Micro_Driver
  */

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/

