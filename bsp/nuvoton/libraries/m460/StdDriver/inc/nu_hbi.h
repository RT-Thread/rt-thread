/**************************************************************************//**
 * @file    nu_hbi.h
 * @version V1.00
 * @brief   M460 series HBI driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __NU_HBI_H__
#define __NU_HBI_H__

/*---------------------------------------------------------------------------------------------------------*/
/* Include related headers                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup HyperBus Interface Driver
  @{
*/


/** @addtogroup HBI_EXPORTED_CONSTANTS HBI Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/* HyperRAM memory mapping address*/
#define HYPER_RAM_MEM_MAP 0x0A000000
/*---------------------------------------------------------------------------------------------------------*/
/* HyperRAM Register Space constant definitions
Register Space Range:
   0x0000_0000 = Identification Register 0
   0x0000_0002 = Identification Register 1
   0x0000_1000 = Configuration Register 0
   0x0000_1002 = Configuration Register 1
*/
#define HYPERRAM_ID_REG0          0x00000000
#define HYPERRAM_ID_REG1          0x00000002
#define HYPERRAM_CONFIG_REG0      0x00001000
#define HYPERRAM_CONFIG_REG1      0x00001002
/*---------------------------------------------------------------------------------------------------------*/
/* HBI_CMD constant definitions
0001 = Reset HyperRAM
0010 = Read HyperRAM regsiter (16-Bit, Read Data[15:0]
0101 = Exit From Hybrid Sleep and deep power down
0111 = Write HyperRAM regsiter (16-Bit, Write Data[15:0]
1000 = Read 1 word (Read Data[15:0]) from HyperRAM
1001 = Read 2 word (Read Data[31:0]) from HyperRAM
1100 = Write 1 Byte (Write Data[7:0]) to HyperRAM
1101 = Write 2 Bytes (Write Data[15:0]) to HyperRAM
1110 = Write 3 Byte (Write Data[23:0]) to HyperRAM
1111 = Write 4 Byte (Write Data[31:0]) to HyperRAM
*/
/*---------------------------------------------------------------------------------------------------------*/
#define HBI_CMD_RESET_HRAM           0x1
#define HBI_CMD_READ_HRAM_REGISTER   0x2
#define HBI_CMD_EXIT_HS_PD           0x5
#define HBI_CMD_WRITE_HRAM_REGISTER  0x7
#define HBI_CMD_READ_HRAM_1_WORD     0x8
#define HBI_CMD_READ_HRAM_2_WORD     0x9
#define HBI_CMD_WRITE_HRAM_1_BYTE    0xC
#define HBI_CMD_WRITE_HRAM_2_BYTE    0xD
#define HBI_CMD_WRITE_HRAM_3_BYTE    0xE
#define HBI_CMD_WRITE_HRAM_4_BYTE    0xF
#define HBI_CMD_HRAM_IDLE            0x0
/*---------------------------------------------------------------------------------------------------------*/
/* HBI_CONFIG: Chip Select Setup Time to Next CK Rising Edge constant definitions
00 = 1.5 HCLK cycles.
01 = 2.5 HCLK cycles.
10 = 3.5 HCLK cycles.
11 = 4.5 HCLK cycles.
*/
/*---------------------------------------------------------------------------------------------------------*/
#define HBI_CONFIG_CSST_1_5_HCLK   (0x0 << HBI_CONFIG_CSST_Pos)
#define HBI_CONFIG_CSST_2_5_HCLK   (0x1 << HBI_CONFIG_CSST_Pos)
#define HBI_CONFIG_CSST_3_5_HCLK   (0x2 << HBI_CONFIG_CSST_Pos)
#define HBI_CONFIG_CSST_4_5_HCLK   (0x3 << HBI_CONFIG_CSST_Pos)
/*---------------------------------------------------------------------------------------------------------*/
/* HBI_CONFIG: Initial Access Time constant definitions
0000 = 5 HCLK cycles.
0001 = 6 HCLK cycles.
0010 = 7 HCLK cycles.
1110 = 3 HCLK cycles.
1111 = 4 HCLK cycles.
*/
/*---------------------------------------------------------------------------------------------------------*/
#define HBI_CONFIG_ACCT_5_CK   (0x0 << HBI_CONFIG_ACCT_Pos)
#define HBI_CONFIG_ACCT_6_CK   (0x1 << HBI_CONFIG_ACCT_Pos)
#define HBI_CONFIG_ACCT_7_CK   (0x2 << HBI_CONFIG_ACCT_Pos)
#define HBI_CONFIG_ACCT_3_CK   (0xE << HBI_CONFIG_ACCT_Pos)
#define HBI_CONFIG_ACCT_4_CK   (0xF << HBI_CONFIG_ACCT_Pos)
/*---------------------------------------------------------------------------------------------------------*/
/* HBI_CONFIG: Chip Select Hold Time After CK Falling Edge constant definitions
00 = 0.5 HCLK cycles.
01 = 1.5 HCLK cycles.
10 = 2.5 HCLK cycles.
11 = 3.5 HCLK cycles.
*/
/*---------------------------------------------------------------------------------------------------------*/
#define HBI_CONFIG_CSH_0_5_HCLK   (0x0 << HBI_CONFIG_CSH_Pos)
#define HBI_CONFIG_CSH_1_5_HCLK   (0x1 << HBI_CONFIG_CSH_Pos)
#define HBI_CONFIG_CSH_2_5_HCLK   (0x2 << HBI_CONFIG_CSH_Pos)
#define HBI_CONFIG_CSH_3_5_HCLK   (0x3 << HBI_CONFIG_CSH_Pos)
/*---------------------------------------------------------------------------------------------------------*/
/* HBI_CONFIG: Burst Group Size constant definitions
00 = 128 Bytes.
01 = 64 Bytes.
10 = 16 Bytes.
11 = 32 Bytes.
*/
/*---------------------------------------------------------------------------------------------------------*/
#define HBI_CONFIG_BGSIZE_128  (0x0 << HBI_CONFIG_BGSIZE_Pos)
#define HBI_CONFIG_BGSIZE_64   (0x1 << HBI_CONFIG_BGSIZE_Pos)
#define HBI_CONFIG_BGSIZE_16   (0x2 << HBI_CONFIG_BGSIZE_Pos)
#define HBI_CONFIG_BGSIZE_32   (0x3 << HBI_CONFIG_BGSIZE_Pos)
/*---------------------------------------------------------------------------------------------------------*/
/* HBI_CONFIG: Endian Condition on the Hyper Bus Data Pipe constant definitions
0 = Little-Endian.
1 = Big-Endian.
*/
/*---------------------------------------------------------------------------------------------------------*/
#define HBI_CONFIG_LITTLE_ENDIAN  (0x0 << HBI_CONFIG_ENDIAN_Pos)
#define HBI_CONFIG_BIG_ENDIAN     (0x1 << HBI_CONFIG_ENDIAN_Pos)
/*---------------------------------------------------------------------------------------------------------*/
/* HBI_CONFIG: Hyper Bus Clock Divider constant definitions
0 = Hyper Bus Clock rate is HCLK/2.
1 = Hyper Bus Clock rate is HCLK/4.
*/
/*---------------------------------------------------------------------------------------------------------*/
#define HBI_CONFIG_CKDIV_HCLK_DIV2    (0x0 << HBI_CONFIG_CKDIV_Pos)
#define HBI_CONFIG_CKDIV_HCLK_DIV4    (0x1 << HBI_CONFIG_CKDIV_Pos)
/*---------------------------------------------------------------------------------------------------------*/

#define HBI_TIMEOUT       SystemCoreClock   /*!< 1 second time-out \hideinitializer */
#define HBI_TIMEOUT_ERR   (-2L)             /*!< HBI operation abort due to timeout error \hideinitializer */
extern int32_t g_HBI_i32ErrCode;

/*---------------------------------------------------------------------------------------------------------*/
/*  Define Macros and functions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
/**
  * @brief      Set HBI Chip Select Setup Time to Next CK Rising Edge
  * @param[in]  u8Value   Chip Select Setup Time to Next CK Rising Edge.
  *                         - \ref HBI_CONFIG_CSST_1_5_HCLK   : 1.5 HCLK cycles
  *                         - \ref HBI_CONFIG_CSST_2_5_HCLK   : 2.5 HCLK cycles
  *                         - \ref HBI_CONFIG_CSST_3_5_HCLK   : 3.5 HCLK cycles
  *                         - \ref HBI_CONFIG_CSST_4_5_HCLK   : 4.5 HCLK cycles
  * @return     None
  * @details    This macro set HBI Chip Select Setup Time to Next CK Rising Edge
  * \hideinitializer
  */
#define HBI_CONFIG_SET_CSST(u8Value)    (HBI->CONFIG = (HBI->CONFIG & (~(HBI_CONFIG_CSST_Msk))) | u8Value)

/**
  * @brief      Set HBI Initial Access Time
  * @param[in]  u8Value   Initial Access Time.
  *                         - \ref HBI_CONFIG_ACCT_5_CK   : 5 CK cycles
  *                         - \ref HBI_CONFIG_ACCT_6_CK   : 6 CK cycles
  *                         - \ref HBI_CONFIG_ACCT_7_CK   : 7 CK cycles
  *                         - \ref HBI_CONFIG_ACCT_3_CK   : 3 CK cycles
    *                         - \ref HBI_CONFIG_ACCT_4_CK   : 4 CK cycles
  * @return     None
  * @details    This macro set HBI Initial Access Time
  * \hideinitializer
  */
#define HBI_CONFIG_SET_ACCT(u8Value)    (HBI->CONFIG = (HBI->CONFIG & (~(HBI_CONFIG_ACCT_Msk))) | u8Value)

/**
  * @brief      Set HBI Chip Select Hold Time After CK Falling Edge
  * @param[in]  u8Value   Chip Select Hold Time After CK Falling Edge.
  *                         - \ref HBI_CONFIG_CSH_0_5_HCLK   : 0.5 HCLK cycles
  *                         - \ref HBI_CONFIG_CSH_1_5_HCLK   : 1.5 HCLK cycles
  *                         - \ref HBI_CONFIG_CSH_2_5_HCLK   : 2.5 HCLK cycles
  *                         - \ref HBI_CONFIG_CSH_3_5_HCLK   : 3.5 HCLK cycles
  * @return     None
  * @details    This macro set HBI Chip Select Hold Time After CK Falling Edge
  * \hideinitializer
  */
#define HBI_CONFIG_SET_CSH(u8Value)    (HBI->CONFIG = (HBI->CONFIG & (~(HBI_CONFIG_CSH_Msk))) | u8Value)

/**
  * @brief      Set HBI Chip Select High between Transaction
  * @param[in]  u8Value       Set Chip Select High between Transaction as u8Value HCLK cycles
                                u8Value must be 1 ~ 16
  * @return     None
  * @details    This macro set HBI Chip Select High between Transaction.
  * \hideinitializer
  */
#define HBI_CONFIG_SET_CSHI(u8Value)    (HBI->CONFIG = (HBI->CONFIG & (~(HBI_CONFIG_CSHI_Msk))) | ((u8Value-1) << HBI_CONFIG_CSHI_Pos))

/**
  * @brief      Set HBI Burst Group Size
  * @param[in]  u8Value   Burst Group Size.
  *                         - \ref HBI_CONFIG_BGSIZE_128   : 128 Bytes
  *                         - \ref HBI_CONFIG_BGSIZE_64    : 64  Bytes
  *                         - \ref HBI_CONFIG_BGSIZE_16    : 16  Bytes
  *                         - \ref HBI_CONFIG_BGSIZE_32    : 32  Bytes
  * @return     None
  * @details    This macro set HBI Burst Group Size
  * \hideinitializer
  */
#define HBI_CONFIG_SET_BGSIZE(u8Value)    (HBI->CONFIG = (HBI->CONFIG & (~(HBI_CONFIG_BGSIZE_Msk))) | u8Value)

/**
  * @brief      Set HBI Endian Condition on the Hyper Bus Data Pipe
  * @param[in]  u8Value   Endian Condition on the Hyper Bus Data Pipe.
  *                         - \ref HBI_CONFIG_LITTLE_ENDIAN   : Little-Endian
  *                         - \ref HBI_CONFIG_BIG_ENDIAN      : Big-Endian
  * @return     None
  * @details    This macro set HBI Endian Condition on the Hyper Bus Data Pipe
  * \hideinitializer
  */
#define HBI_CONFIG_SET_ENDIAN(u8Value)    (HBI->CONFIG = (HBI->CONFIG & (~(HBI_CONFIG_ENDIAN_Msk))) | u8Value)

/**
  * @brief      Set HBI Hyper Bus Clock Divider
  * @param[in]  u8Value   Hyper Bus Clock Divider.
  *                         - \ref HBI_CONFIG_CKDIV_HCLK_DIV2   : HCLK/2
  *                         - \ref HBI_CONFIG_CKDIV_HCLK_DIV4   : HCLK/4
  * @return     None
  * @details    This macro set Hyper Bus Clock Divider
  * \hideinitializer
  */
#define HBI_CONFIG_SET_CKDIV(u8Value)    (HBI->CONFIG = (HBI->CONFIG & (~(HBI_CONFIG_CKDIV_Msk))) | u8Value)

/**
  * @brief      Set HBI Chip Select Maximum Low Time
  * @param[in]  u32CsMaxLT       Set HBI Chip Select Maximum Low Time as u32CsMaxLT HCLK cycles.
                                   u32CsMaxLT must be 1 ~ 2048
  * @return     None
  * @details    This macro set HBI Chip Select Maximum Low Time.
  * \hideinitializer
  */
#define HBI_CONFIG_SET_CSMAXLT(u32CsMaxLT)    (HBI->CONFIG = (HBI->CONFIG & (~(HBI_CONFIG_CSMAXLT_Msk))) | ((u32CsMaxLT-1) << HBI_CONFIG_CSMAXLT_Pos))

/**
  * @brief      Enable HyperBus Operation Done Interrupt
  * @param[in]  None
  * @return     None
  * @details    This macro enable HyperBus Operation Done Interrupt.
  * \hideinitializer
  */
#define HBI_ENABLE_INT    (HBI->INTEN |= HBI_INTEN_OPINTEN_Msk)

/**
  * @brief      Disable HyperBus Operation Done Interrupt
  * @param[in]  None
  * @return     None
  * @details    This macro disable HyperBus Operation Done Interrupt.
  * \hideinitializer
  */
#define HBI_DISABLE_INT    (HBI->INTEN &= ~HBI_INTEN_OPINTEN_Msk)

///////////////////
/**
  * @brief      Get HyperBus Operation Done Interrupt
  * @param[in]  None
  * @return     0 = HyperBus operation is busy.
  *             1 = HyperBus operation is done.
  * @details    This macro Get HyperBus Operation Done Interrupt.
  * \hideinitializer
  */
#define HBI_GET_INTSTS    ((HBI->INTSTS & HBI_INTSTS_OPDONE_Msk)? 1:0)

/*---------------------------------------------------------------------------------------------------------*/
/* Define Function Prototypes                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
void HBI_ResetHyperRAM(void);
void HBI_ExitHSAndDPD(void);
int32_t HBI_ReadHyperRAMReg(uint32_t u32Addr);
int32_t HBI_WriteHyperRAMReg(uint32_t u32Addr, uint32_t u32Value);
uint32_t HBI_Read1Word(uint32_t u32Addr);
uint32_t HBI_Read2Word(uint32_t u32Addr);
void HBI_Write1Byte(uint32_t u32Addr, uint8_t u8Data);
void HBI_Write2Byte(uint32_t u32Addr, uint16_t u16Data);
void HBI_Write3Byte(uint32_t u32Addr, uint32_t u32Data);
void HBI_Write4Byte(uint32_t u32Addr, uint32_t u32Data);

/*@}*/ /* end of group HBI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group HBI_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_HBI_H__ */
