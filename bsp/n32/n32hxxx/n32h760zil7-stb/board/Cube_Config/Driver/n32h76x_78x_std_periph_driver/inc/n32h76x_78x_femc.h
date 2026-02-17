/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_femc.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H76X_78X_FEMC_H__
#define __N32H76X_78X_FEMC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"


/** Timing parameters **/
typedef struct
{
    uint32_t    Trc;      /* Defines the RC in memory clock cycles. This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */

    uint32_t    Twc;      /* Defines the WC in memory clock cycles. This parameter can be a value between Min_Data = 0 and Max_Data = 0x0F */

    uint32_t    Tcere;    /* Defines the CEOE or REA in memory clock cycles. This parameter can be a value between Min_Data = 0 and Max_Data = 7 */

    uint32_t    Twp;      /* Defines the WP in memory clock cycles. This parameter can be a value between Min_Data = 0 and Max_Data = 7 */

    uint32_t    Tpcclr;   /* Defines the PC OR CLR in memory clock cycles. This parameter can be a value between Min_Data = 0 and Max_Data = 7 */

    uint32_t    Ttrar;    /* Defines the TR or AR in memory clock cycles. This parameter can be a value between Min_Data = 0 and Max_Data = 7 */
    
    uint32_t    Twerr;    /* Defines the WE or RR in memory clock cycles. This parameter can be a value between Min_Data = 0 and Max_Data = 7 */

} FEMC_TimingInitType;

/** FEMC Chip Init structure definition **/
typedef struct
{
    uint32_t    ReadSyncMode;    /* Defines the read sync enable. This parameter can be a value of @ref FEMC_Memory_Read_Mode */

    uint32_t    WriteSyncMode;   /* Defines the write sync enable. This parameter can be a value of @ref FEMC_Memory_Write_Mode */

    uint32_t    ReadBurstLen;    /* Defines the number of read data access. This parameter can be a value of @ref FEMC_Memory_Read_Burst_Length. */

    uint32_t    WriteBurstLen;   /* Defines the number of write data access. This parameter can be a value of @ref FEMC_Memory_Write_Burst_Length. */

    uint32_t    MemWidth;        /* Defines the memory width. This parameter can be a value of @ref FEMC_Memory_Width. */

    uint32_t    BAA;             /* Defines the BAA signal enable. This parameter can be a value of @ref FEMC_BAA_Port_Selection. */

    uint32_t    ADV;             /* Defines the ADVS signal enable. This parameter can be a value of @ref FEMC_ADV_Port_Selection. */

    uint32_t    BLSS;            /* Defines the BLS signal selection. This parameter can be a value of @ref FEMC_BLS_Synchronization_Selection. */

    uint32_t    BurstAlign;      /* Defines whether memory bursts are split on memory burst boundaries, when you configure the FEMC to perform synchronous transfers
                                    This parameter can be a value of @ref FEMC_Burst_align_Selection. */

} FEMC_ChipInitType;

/** FEMC Init structure definition **/
typedef struct
{
    FEMC_ChipInitType       ChipCfg;
    FEMC_TimingInitType     TimingCfg;
    
}FEMC_InitType;

/** FEMC ECC Configuration Structure definition **/
typedef struct
{
    uint32_t    BLKNum;         /* Defines the number of 512 byte blocks in a nand flash page. */

    uint32_t    Mode;           /* Defines the mode of the ECC block. This parameter can be a value of @ref FEMC_ECC_Mode */

    uint32_t    ReadMode;       /* Defines when ECC values are read from memory. This parameter can be a value of @ref FEMC_ECC_Read_Time */

    uint32_t    JUMP;           /* Defines whether the memory supports column change address commands or not. This parameter can be a value of @ref FEMC_ECC_Jump_Mode */

    uint32_t    A8OUTMSK;       /* Defines if A8 is output with the address. This parameter can be a value of @ref FEMC_ECC_A8_Output */

    uint32_t    ReadINT;        /* Defines the ECC pass interrupt state when the ECC data is read from memory. This parameter can be a value of @ref FEMC_ECC_Pass_Interrupt */

    uint32_t    ABTINT;         /* Defines the ECC error interrupt state when an error occurs. This parameter can be a value of @ref FEMC_ECC_Abort_Interrupt */

    uint32_t    EXTBLKEN;       /* Defines whether enables a small block for extra information after the last 512 bytes block in the page or not.
                                           This parameter can be a value of @ref FEMC_ECC_Extra_Block_State */

    uint32_t    EXTBLKSize;     /* Defines the size of the extra block in memory after the last 512-byte block. This parameter can be a value of @ref FEMC_ECC_Extra_Block_Size */
                                                                                                                                                             
    uint32_t    CMD0;           /* Defines the commands that the ECC block uses to detect the start of an ECC operation for nand flash memory interface*/

    uint32_t    CMD1;           /* Defines the commands that the ECC block uses to access different parts of a NAND page for nand flash memory interface*/	

}FEMC_ECCInitType;

/** Last Ecc Operation Status **/
typedef enum
{
    COMPLETE        = 0U,
    UNALIGNADDR     = 1U,
    DATASTOP        = 2U,
    DATASTOP_NOREAD = 3U,
} ECC_Last_Stats;


#define SRAM_NOR_CHIP_1                     (0x00)     /* SRAM Nor Flash Chip 0 */
#define SRAM_NOR_CHIP_2                     (0x01)     /* SRAM Nor Flash Chip 1 */
#define SRAM_NOR_CHIP_3                     (0x02)     /* SRAM Nor Flash Chip 2 */
#define SRAM_NOR_CHIP_4                     (0x03)     /* SRAM Nor Flash Chip 3 */

#define NAND_CHIP_1                         (0x04)     /* NAND Chip 1 */
#define NAND_CHIP_2                         (0x05)     /* NAND Chip 2 */


/** FEMC Memory Read Mode **/
#define FEMC_MEM_READ_ASYNC                 ((uint32_t)0x00000000)
#define FEMC_MEM_READ_SYNC                  (FEMC_OMCFG_RDSYN)
/** FEMC Memory Write Mode **/
#define FEMC_MEM_WRITE_ASYNC                ((uint32_t)0x00000000)
#define FEMC_MEM_WRITE_SYNC                 (FEMC_OMCFG_WRSYN)

/** FEMC Memory Read Burst Length **/
#define FEMC_MEM_READ_BURST_1               ((uint32_t)0x00000000)                  /* 1 beat */
#define FEMC_MEM_READ_BURST_4               (FEMC_OMCFG_RDBL_0)                     /* 4 beats */
#define FEMC_MEM_READ_BURST_8               (FEMC_OMCFG_RDBL_1)                     /* 8 beats */
#define FEMC_MEM_READ_BURST_16              (FEMC_OMCFG_RDBL_1 | FEMC_OMCFG_RDBL_0) /* 16 beats */
#define FEMC_MEM_READ_BURST_32              (FEMC_OMCFG_RDBL_2)                     /* 32 beats */
#define FEMC_MEM_READ_BURST_CONTINUOUS      (FEMC_OMCFG_RDBL_2 | FEMC_OMCFG_RDBL_0) /* continuous */

/** FEMC Memory Write Burst Length **/
#define FEMC_MEM_WRITE_BURST_1              (0UL)                                   /* 1 beat */
#define FEMC_MEM_WRITE_BURST_4              (FEMC_OMCFG_WRBL_0)                     /* 4 beats */
#define FEMC_MEM_WRITE_BURST_8              (FEMC_OMCFG_WRBL_1)                     /* 8 beats */
#define FEMC_MEM_WRITE_BURST_16             (FEMC_OMCFG_WRBL_1 | FEMC_OMCFG_WRBL_0) /* 16 beats */
#define FEMC_MEM_WRITE_BURST_32             (FEMC_OMCFG_WRBL_2)                     /* 32 beats */
#define FEMC_MEM_WRITE_BURST_CONTINUOUS     (FEMC_OMCFG_WRBL_2 | FEMC_OMCFG_WRBL_0) /* continuous */

/** FEMC Memory Width **/
#define FEMC_MEMORY_WIDTH_8BIT              ((uint32_t)0x00000000)
#define FEMC_MEMORY_WIDTH_16BIT             (FEMC_OMCFG_MDBW_0)
#define FEMC_MEMORY_WIDTH_32BIT             (FEMC_OMCFG_MDBW_1)

/** FEMC BAA Port Selection **/
#define FEMC_BAA_PORT_DISABLE               ((uint32_t)0x00000000)
#define FEMC_BAA_PORT_ENABLE                (FEMC_OMCFG_BAA)

/** FEMC ADV Port Selection **/
#define FEMC_ADV_PORT_DISABLE               ((uint32_t)0x00000000)
#define FEMC_ADV_PORT_ENABLE                (FEMC_OMCFG_ADV)

/** FEMC_BLS_Synchronization_Selection **/
#define FEMC_BLS_SYNC_CS                    ((uint32_t)0x00000000)
#define FEMC_BLS_SYNC_WE                    (FEMC_OMCFG_BLSS)

/** FEMC_Burst_align_Selection **/
#define FEMC_BURST_NO_SPLIT                 ((uint32_t)0x00000000)
#define FEMC_BURST_SPLIT_ON_32              (FEMC_OMCFG_BSTAGN_0)
#define FEMC_BURST_SPLIT_ON_64              (FEMC_OMCFG_BSTAGN_1)
#define FEMC_BURST_SPLIT_ON_128             (FEMC_OMCFG_BSTAGN_1 | FEMC_OMCFG_BSTAGN_0)
#define FEMC_BURST_SPLIT_ON_256             (FEMC_OMCFG_BSTAGN_2)
 
/** FEMC Command **/
#define FEMC_CMD_UPDATEREGS_AND_AXI         ((uint32_t)0x00000000)
#define FEMC_CMD_MDREGCONFIG                (FEMC_CTRL_CMDTYPE_0)
#define FEMC_CMD_UPDATEREGS                 (FEMC_CTRL_CMDTYPE_1)
#define FEMC_CMD_MDREGCONFIG_AND_UPDATEREGS (FEMC_CTRL_CMDTYPE_1 | FEMC_CTRL_CMDTYPE_0)

/** FEMC CRE Polarity **/
#define FEMC_CRE_POLARITY_LOW               ((uint32_t)0x00000000)  /* CRE is LOW */
#define FEMC_CRE_POLARITY_HIGH              (FEMC_CTRL_CREPOL)      /* CRE is HIGH when ModeReg write occurs */

/** FEMC Flag definition **/
#define FEMC_SRAM_FLAG                      (FEMC_STS_RINT0F)
#define FEMC_NAND_FLAG                      (FEMC_STS_RINT1F)
#define FEMC_ECC_FLAG                       (FEMC_STS_RECCINTF)
#define FEMC_SRAM_EN_FLAG                   (FEMC_STS_INT0ENF)
#define FEMC_NAND_EN_FLAG                   (FEMC_STS_INT1ENF)
#define FEMC_ECC_EN_FLAG                    (FEMC_STS_ECCINTENF)

/** FEMC Flag clear */
#define FEMC_SRAM_FLAG_CLEAR                (FEMC_CCFG_INT0CLR)
#define FEMC_NAND_FLAG_CLEAR                (FEMC_CCFG_INT1CLR)

/** FEMC interrupts definition **/
#define FEMC_IT_SRAM_EN                     (FEMC_CFG_INT0EN)
#define FEMC_IT_NAND_EN                     (FEMC_CFG_INT1EN)
#define FEMC_IT_ECC_EN                      (FEMC_CFG_ECCINTEN)

/** FEMC interrupts clear */
#define FEMC_IT_SRAM_FLAG_CLEAR             (FEMC_CCFG_INT0CLR)
#define FEMC_IT_NAND_FLAG_CLEAR             (FEMC_CCFG_INT1CLR)

/** FEMC interrupts disable **/
#define FEMC_IT_SRAM_DIS                    (FEMC_CCFG_INT0DIS)
#define FEMC_IT_NAND_DIS                    (FEMC_CCFG_INT1DIS)
#define FEMC_IT_ECC_DIS                     (FEMC_CCFG_ECCINTDIS)

/** FEMC interrupts status **/
#define FEMC_IT_SRAM_FLAG                   (FEMC_STS_INT0F)
#define FEMC_IT_NAND_FLAG                   (FEMC_STS_INT1F)
#define FEMC_IT_ECC_FLAG                    (FEMC_STS_ECCINTF)

/** FEMC SRAM interface type **/
#define FEMC_SRAM_MULT                      (FEMC_STS1_M0TYPE_0 | FEMC_STS1_M0TYPE_1)
#define FEMC_SRAM_NON_MULT                  (FEMC_STS1_M0TYPE_0)

/** FEMC ECC Page block number **/
#define FEMC_ECC_NO_512_BYTES               ((uint32_t)0x00000000)
#define FEMC_ECC_ONE_512_BYTES              (FEMC_ECCCFG_BLKNUM_0)
#define FEMC_ECC_TWO_512_BYTES              (FEMC_ECCCFG_BLKNUM_1)
#define FEMC_ECC_FOUR_512_BYTES             (FEMC_ECCCFG_BLKNUM_1 | FEMC_ECCCFG_BLKNUM_0)

/** FEMC ECC Mode **/
#define FEMC_ECC_BYPASSED                   ((uint32_t)0x00000000)
#define FEMC_ECC_FOR_APB                    (FEMC_ECCCFG_MOD_0)
#define FEMC_ECC_AUTO_WR                    (FEMC_ECCCFG_MOD_1)

/** FEMC ECC Read Mode **/
#define FEMC_ECC_READ_BLOCK_END             ((uint32_t)0x00000000)
#define FEMC_ECC_READ_PAGE_END              (FEMC_ECCCFG_RMOD)

/** FEMC ECC Jump Mode **/
#define FEMC_ECC_NO_JUMP                    ((uint32_t)0x00000000)
#define FEMC_ECC_COLUMN_JUMP                (FEMC_ECCCFG_JUMP_0)
#define FEMC_ECC_FULL_JUMP                  (FEMC_ECCCFG_JUMP_1)

/** FEMC ECC A8 Output **/
#define FEMC_A8_OUTPUT_DISABLE              (FEMC_ECCCFG_A8OUTMSK)
#define FEMC_A8_OUTPUT_ENABLE               ((uint32_t)0x00000000)

/** FEMC ECC Pass Interrupt **/
#define FEMC_ECC_PASS_INTERRUPT_DISABLE     ((uint32_t)0x00000000)
#define FEMC_ECC_PASS_INTERRUPT_ENABLE      (FEMC_ECCCFG_RDCINT)

/** FEMC ECC Abort Interrupt **/
#define FEMC_ECC_ABORT_INTERRUPT_DISABLE    ((uint32_t)0x00000000)
#define FEMC_ECC_ABORT_INTERRUPT_ENABLE     (FEMC_ECCCFG_ABTINT)

/** FEMC ECC Extra Block Size **/
#define FEMC_ECC_EXTRA_BLOCK_4_BYTES        ((uint32_t)0x00000000)
#define FEMC_ECC_EXTRA_BLOCK_8_BYTES        (FEMC_ECCCFG_EBLKSIZ_0)
#define FEMC_ECC_EXTRA_BLOCK_16_BYTES       (FEMC_ECCCFG_EBLKSIZ_1)
#define FEMC_ECC_EXTRA_BLOCK_32_BYTES       (FEMC_ECCCFG_EBLKSIZ_1 | FEMC_ECCCFG_EBLKSIZ_0)

/** FEMC ECC Extra Block State **/
#define FEMC_ECC_EXTRA_BLOCK_DISABLE        ((uint32_t)0x00000000)
#define FEMC_ECC_EXTRA_BLOCK_ENABLE         (FEMC_ECCCFG_EBLKEN)

/** FEMC ECC Page block Index **/
#define FEMC_ECC_PAGE_BLOCK_INDEX0          ((uint32_t)0x00000000)
#define FEMC_ECC_PAGE_BLOCK_INDEX1          ((uint32_t)0x00000001)
#define FEMC_ECC_PAGE_BLOCK_INDEX2          ((uint32_t)0x00000002)
#define FEMC_ECC_PAGE_BLOCK_INDEX3          ((uint32_t)0x00000003)
#define FEMC_ECC_PAGE_BLOCK_EXTRA           ((uint32_t)0x00000004)

/** FEMC Flag Index **/
#define FEMC_ECC_FLAG_VALUE_VALID       (FEMC_ECCSTS_VLDF_0)
#define FEMC_ECC_FLAG_FAIL              (FEMC_ECCSTS_FAILF_0)
#define FEMC_ECC_FLAG_CAN_CORRECT       (FEMC_ECCSTS_CORCTF_0)
#define FEMC_ECC_FLAG_READ              (FEMC_ECCSTS_RDF_0)

/** FEMC ECC Page Block Interrupt Index **/
#define FEMC_ECC_INT_FLAG_PAGE_BLOCK0       (FEMC_ECCSTS_INTF_0)
#define FEMC_ECC_INT_FLAG_PAGE_BLOCK1       (FEMC_ECCSTS_INTF_1)
#define FEMC_ECC_INT_FLAG_PAGE_BLOCK2       (FEMC_ECCSTS_INTF_2)
#define FEMC_ECC_INT_FLAG_PAGE_BLOCK3       (FEMC_ECCSTS_INTF_3)
#define FEMC_ECC_INT_FLAG_PAGE_EXTRA        (FEMC_ECCSTS_INTF_4)
#define FEMC_ECC_INT_FLAG_ABORT             (FEMC_ECCSTS_INTF_5)

/** FEMC ECC Block Flag Index **/
#define FEMC_ECC_BLOCK_FLAG_CAN_CORRECT     ((uint32_t)0x0000001)
#define FEMC_ECC_BLOCK_FLAG_FAIL            ((uint32_t)0x0000002)
#define FEMC_ECC_BLOCK_FLAG_READ            ((uint32_t)0x0000004)
#define FEMC_ECC_BLOCK_FLAG_VALUE_VALID     ((uint32_t)0x0000008)
#define FEMC_ECC_BLOCK_FLAG_INTERRUPT       ((uint32_t)0x0000010)

/** FEMC Last status **/
#define FEMC_ECC_LAST_STATUS_COMPLETE           ((uint32_t)0x0000000)
#define FEMC_ECC_LAST_STATUS_UNALIGNADDR        (FEMC_ECCSTS_LASTS_0)
#define FEMC_ECC_LAST_STATUS_DATASTOP           (FEMC_ECCSTS_LASTS_1)
#define FEMC_ECC_LAST_STATUS_DATASTOP_NOREAD    (FEMC_ECCSTS_LASTS_0 | FEMC_ECCSTS_LASTS_1)

/** FEMC_Exported_Functions **/
void FEMC_Init(FEMC_InitType *FEMC_InitStruct);
void FEMC_InitStruct(FEMC_InitType* FEMC_InitStruct);
void FEMC_SetCommand(uint32_t Chip, uint32_t Cmd, uint32_t CrePolarity, uint32_t Address);
ErrorStatus FEMC_CheckChipStatus(uint32_t Chip, FEMC_ChipInitType *ChipCfg);
ErrorStatus FEMC_CheckTimingStatus(uint32_t Chip, FEMC_TimingInitType *TimingCfg);
void FEMC_SetRefreshPeriod(uint32_t PeriodVal);
uint32_t FEMC_GetRefreshPeriod(void);
void FEMC_SetAddressmatch(uint32_t Chip, uint32_t Address_Match_Value);
void FEMC_SRAMMuxModeEnable(FunctionalState NewState);
void FEMC_SRAMAGTMEnable(FunctionalState NewState);
void FEMC_SRAMSYNCEnable(FunctionalState NewState);
void FEMC_NANDCSLEnable(FunctionalState NewState);
void FEMC_NANDAGTMEnable(FunctionalState NewState);
void FEMC_NANDSYNCEnable(FunctionalState NewState);
void FEMC_RemapEnable(FunctionalState NewState);
void FEMC_AsyncADVConfig(FunctionalState NewState);
uint32_t FEMC_GetSRAMType(void);

void FEMC_ClrFlag(uint32_t FEMC_FLAG);
FlagStatus FEMC_GetFlag(uint32_t FEMC_FLAG);
void FEMC_ITConfig(uint32_t FEMC_IT, FunctionalState NewState);
void FEMC_ClrITFlag(uint32_t FEMC_FLAG);
ITStatus FEMC_GetITFlag(uint32_t FEMC_IT_FLAG);

void FEMC_ECC_Init(const FEMC_ECCInitType *ECCInitType);
void FEMC_SetECCAddr(uint32_t address0, uint32_t address1);
FlagStatus FEMC_GetECCFlag(uint32_t FEMC_ECC_Flag_Index, uint32_t ECC_Block_Index);
FlagStatus FEMC_GetECCITFlag(uint32_t ECC_Block_Index);
void FEMC_ECCClrFlag(uint32_t ECC_Block_Index);
FlagStatus FEMC_GetECCBusyFlag(void);
ECC_Last_Stats FEMC_GetECCLastSTS(void);
FlagStatus FEMC_GetECCRWFlag(void);
FlagStatus FEMC_GetECCBlockSTS(uint32_t ECC_Block_Index, uint32_t FEMC_Block_Flag_Index);
void FEMC_ClrECCBlockSTS(uint32_t ECC_Block_Index, uint32_t FEMC_Block_Flag_Index);
uint32_t FEMC_GetECCvalue(uint32_t ECC_Block_Index);

#ifdef __cplusplus
}
#endif

#endif /*__N32H76X_78X_FEMC_H__ */

