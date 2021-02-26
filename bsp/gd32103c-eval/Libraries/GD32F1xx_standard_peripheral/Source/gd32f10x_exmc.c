/**
  ******************************************************************************
  * @brief   EXMC functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_exmc.h"
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup EXMC
  * @brief EXMC driver modules
  * @{
  */

/** @defgroup EXMC_Private_Defines
  * @{
  */

/* EXMC Bank1 SCTLRx_BAKEN and SCTLRx_NORAEN Mask */
#define SCTLR_BAKEN_SET                              ((uint32_t)0x00000001)
#define SCTLR_BAKEN_RESET                            ((uint32_t)0x000FFFFE)

/* EXMC Bank1 SCTLRx_NOREN Mask */
#define SCTLR_NOREN_SET                              ((uint32_t)0x00000040)


/* EXMC Bank2/3/4 CTLRx_BAKEN Mask */
#define CTLR_BAKEN_SET                               ((uint32_t)0x00000004)
#define CTLR_BAKEN_RESET                             ((uint32_t)0x000FFFFB)

/* EXMC Bank2/3/4 CTLRx_ECCEN Mask */
#define CTLR_ECCEN_SET                               ((uint32_t)0x00000040)
#define CTLR_ECCEN_RESET                             ((uint32_t)0x000FFFBF)

/* EXMC Bank2/3/4 CTLRx_MTYPE Mask */
#define CTLR_EMTYP_NAND                              ((uint32_t)0x00000008)

/* EXMC Bank1 Register Reset mask*/
#define BANK1_SCTLR1_RESET                           ((uint32_t)0x000030DB)
#define BANK1_SCTLR_RESET                            ((uint32_t)0x000030D2)
#define BANK1_STR_RESET                              ((uint32_t)0x0FFFFFFF)
#define BANK1_SWTR_RESET                             ((uint32_t)0x0FFFFFFF)

/* EXMC Bank2/3 Register Reset mask*/
#define BANK2_3_CTLR_RESET                           ((uint32_t)0x00000018)
#define BANK2_3_SIR_RESET                            ((uint32_t)0x00000040)
#define BANK2_3_COMTR_RESET                          ((uint32_t)0xFCFCFCFC)
#define BANK2_3_ATTR_RESET                           ((uint32_t)0xFCFCFCFC)

/* EXMC Bank4 Register Reset mask*/
#define BANK4_CTLR_RESET                             ((uint32_t)0x00000018)
#define BANK4_SIR_RESET                              ((uint32_t)0x00000000)
#define BANK4_COMTR_RESET                            ((uint32_t)0xFCFCFCFC)
#define BANK4_ATTR_RESET                             ((uint32_t)0xFCFCFCFC)
#define BANK4_IOTR_RESET                             ((uint32_t)0xFCFCFCFC)

/* EXMC register bit offset */
#define STR_AHT_OFFSET                               ((uint32_t)0x00000004)
#define STR_DST_OFFSET                               ((uint32_t)0x00000008)
#define STR_BUSLAT_OFFSET                            ((uint32_t)0x00000010)
#define STR_CDIV_OFFSET                              ((uint32_t)0x00000014)
#define STR_DLAT_OFFSET                              ((uint32_t)0x00000018)

#define SWTR_AHT_OFFSET                              ((uint32_t)0x00000004)
#define SWTR_DST_OFFSET                              ((uint32_t)0x00000008)
#define SWTR_CDIV_OFFSET                             ((uint32_t)0x00000014)
#define SWTR_DLAT_OFFSET                             ((uint32_t)0x00000018)

#define CTLR_CTR_OFFSET                              ((uint32_t)0x00000009)
#define CTLR_ATR_OFFSET                              ((uint32_t)0x0000000D)

#define COMTR_COMWT_OFFSET                           ((uint32_t)0x00000008)
#define COMTR_COMHT_OFFSET                           ((uint32_t)0x00000010)
#define COMTR_COMHIZT_OFFSET                         ((uint32_t)0x00000018)

#define ATTR_ATTWT_OFFSET                            ((uint32_t)0x00000008)
#define ATTR_ATTHT_OFFSET                            ((uint32_t)0x00000010)
#define ATTR_ATTHIZT_OFFSET                          ((uint32_t)0x00000018)

#define IOTR_IOTWT_OFFSET                            ((uint32_t)0x00000008)
#define IOTR_IOHT_OFFSET                             ((uint32_t)0x00000010)
#define IOTR_IOHIZT_OFFSET                           ((uint32_t)0x00000018)

#define SIR_INTEN_OFFSET                             ((uint32_t)0x00000003)

/**
  * @}
  */

/** @defgroup EXMC_Private_Functions
  * @{
  */

/**
  * @brief  Reset the Bank1 NOR/SRAM registers.
  * @param  EXMC_NORSRAMBank: specifies the Region of Bank1.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK1_NORSRAM1: the Region1 of Bank1
  *     @arg EXMC_BANK1_NORSRAM2: the Region2 of Bank1
  *     @arg EXMC_BANK1_NORSRAM3: the Region3 of Bank1
  *     @arg EXMC_BANK1_NORSRAM4: the Region4 of Bank1
  * @retval None
  */
void EXMC_NORSRAM_DeInit(uint32_t EXMC_NORSRAMBank)
{
    switch (EXMC_NORSRAMBank) {
    case EXMC_BANK1_NORSRAM1: {
        /* the Region1 of Bank1 */
        EXMC_BANK1->SCTLR1 = BANK1_SCTLR1_RESET;
        EXMC_BANK1->STR1 = BANK1_STR_RESET;
        EXMC_BANK1_WT->SWTR1 = BANK1_SWTR_RESET;
        break;
    }
    case EXMC_BANK1_NORSRAM2: {
        /* the Region2 of Bank1 */
        EXMC_BANK1->SCTLR2 = BANK1_SCTLR_RESET;
        EXMC_BANK1->STR2 = BANK1_STR_RESET;
        EXMC_BANK1_WT->SWTR2 = BANK1_SWTR_RESET;
        break;
    }
    case EXMC_BANK1_NORSRAM3: {
        /* the Region3 of Bank1 */
        EXMC_BANK1->SCTLR3 = BANK1_SCTLR_RESET;
        EXMC_BANK1->STR3 = BANK1_STR_RESET;
        EXMC_BANK1_WT->SWTR3 = BANK1_SWTR_RESET;
        break;
    }
    case EXMC_BANK1_NORSRAM4: {
        /* the Region4 of Bank1 */
        EXMC_BANK1->SCTLR4 = BANK1_SCTLR_RESET;
        EXMC_BANK1->STR4 = BANK1_STR_RESET;
        EXMC_BANK1_WT->SWTR4 = BANK1_SWTR_RESET;
        break;
    }
    default:
        break;
    }
}

/**
  * @brief  Reset the Bank2 or Bank3 NAND registers.
  * @param  EXMC_NANDBank: specifies the Bank2 or Bank3 to be used.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK2_NAND: Bank2
  *     @arg EXMC_BANK3_NAND: Bank3
  * @retval None
  */
void EXMC_NAND_DeInit(uint32_t EXMC_NANDBank)
{
    if (EXMC_NANDBank == EXMC_BANK2_NAND) {
        /* Reset the Bank2 NAND registers */
        EXMC_BANK2->CTLR2 = BANK2_3_CTLR_RESET;
        EXMC_BANK2->SIR2 = BANK2_3_SIR_RESET;
        EXMC_BANK2->COMTR2 = BANK2_3_COMTR_RESET;
        EXMC_BANK2->ATTR2 = BANK2_3_ATTR_RESET;
    }
    /* EXMC_Bank3_NAND */
    else {
        /* Reset the Bank3 NAND registers */
        EXMC_BANK3->CTLR3 = BANK2_3_CTLR_RESET;
        EXMC_BANK3->SIR3 = BANK2_3_SIR_RESET;
        EXMC_BANK3->COMTR3 = BANK2_3_COMTR_RESET;
        EXMC_BANK3->ATTR3 = BANK2_3_ATTR_RESET;
    }
}

/**
  * @brief  Reset the Bank4 PCCARD registers.
  * @param  None
  * @retval None
  */
void EXMC_PCCARD_DeInit(void)
{
    /* Reset EXMC Bank4 PCCARD registers */
    EXMC_BANK4->CTLR4 = BANK4_CTLR_RESET;
    EXMC_BANK4->SIR4 = BANK4_SIR_RESET;
    EXMC_BANK4->COMTR4 = BANK4_COMTR_RESET;
    EXMC_BANK4->ATTR4 = BANK4_ATTR_RESET;
    EXMC_BANK4->IOTR4 = BANK4_IOTR_RESET;
}

/**
  * @brief  Initializes the EXMC Bank1 NOR/SRAM parameters.
  * @param  EXMC_NORSRAMInitParaStruct : the struct EXMC_NORSRAMInitPara pointer
  * @retval None
  */
void EXMC_NORSRAM_Init(EXMC_NORSRAMInitPara *EXMC_NORSRAMInitParaStruct)
{
    uint32_t temp_SCTLR = 0x00000000, temp_STR = 0x00000000, temp_SWTR = 0x00000000;

    temp_SCTLR = (uint32_t)EXMC_NORSRAMInitParaStruct->EXMC_AddressDataMux |
                 EXMC_NORSRAMInitParaStruct->EXMC_MemoryType |
                 EXMC_NORSRAMInitParaStruct->EXMC_DatabusWidth |
                 EXMC_NORSRAMInitParaStruct->EXMC_BurstMode |
                 EXMC_NORSRAMInitParaStruct->EXMC_NWAITPolarity |
                 EXMC_NORSRAMInitParaStruct->EXMC_WrapBurstMode |
                 EXMC_NORSRAMInitParaStruct->EXMC_NWAITConfig |
                 EXMC_NORSRAMInitParaStruct->EXMC_MemoryWrite |
                 EXMC_NORSRAMInitParaStruct->EXMC_NWAITSignal |
                 EXMC_NORSRAMInitParaStruct->EXMC_ExtendedMode |
                 EXMC_NORSRAMInitParaStruct->EXMC_AsynWait |
                 EXMC_NORSRAMInitParaStruct->EXMC_WriteMode;

    temp_STR = (uint32_t)EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_AsynAddressSetupTime |
               (EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_AsynAddressHoldTime << STR_AHT_OFFSET) |
               (EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_AsynDataSetupTime << STR_DST_OFFSET) |
               (EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_BusLatency << STR_BUSLAT_OFFSET) |
               (EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_SynCLKDivision << STR_CDIV_OFFSET) |
               (EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_SynDataLatency << STR_DLAT_OFFSET) |
               EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_AsynAccessMode;

    if (EXMC_NORSRAMInitParaStruct->EXMC_MemoryType == EXMC_MEMORY_TYPE_NOR) {
        temp_SCTLR |= (uint32_t)SCTLR_NOREN_SET;
    }

    if (EXMC_NORSRAMInitParaStruct->EXMC_ExtendedMode == EXMC_EXTENDED_MODE_ENABLE) {
        temp_SWTR = (uint32_t)EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_AsynAddressSetupTime |
                    (EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_AsynAddressHoldTime << SWTR_AHT_OFFSET) |
                    (EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_AsynDataSetupTime << SWTR_DST_OFFSET) |
                    (EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_SynCLKDivision << SWTR_CDIV_OFFSET) |
                    (EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_SynDataLatency << SWTR_DLAT_OFFSET) |
                    EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_AsynAccessMode;
    } else {
        temp_SWTR = BANK1_SWTR_RESET;
    }

    switch (EXMC_NORSRAMInitParaStruct->EXMC_NORSRAMBank) {
    case EXMC_BANK1_NORSRAM1: {
        /* Bank1 NOR/SRAM Region1 registers configuration */
        EXMC_BANK1->SCTLR1 = temp_SCTLR;
        EXMC_BANK1->STR1 = temp_STR;
        EXMC_BANK1_WT->SWTR1 = temp_SWTR;
        break;
    }
    case EXMC_BANK1_NORSRAM2: {
        /* Bank1 NOR/SRAM Region2 registers configuration */
        EXMC_BANK1->SCTLR2 = temp_SCTLR;
        EXMC_BANK1->STR2 = temp_STR;
        EXMC_BANK1_WT->SWTR2 = temp_SWTR;
        break;
    }
    case EXMC_BANK1_NORSRAM3: {
        /* Bank1 NOR/SRAM Region3 registers configuration */
        EXMC_BANK1->SCTLR3 = temp_SCTLR;
        EXMC_BANK1->STR3 = temp_STR;
        EXMC_BANK1_WT->SWTR3 = temp_SWTR;
        break;
    }
    case EXMC_BANK1_NORSRAM4: {
        /* Bank1 NOR/SRAM Region4 registers configuration */
        EXMC_BANK1->SCTLR4 = temp_SCTLR;
        EXMC_BANK1->STR4 = temp_STR;
        EXMC_BANK1_WT->SWTR4 = temp_SWTR;
        break;
    }
    default:
        break;
    }
}

/**
  * @brief  Initialize the EXMC Bank2 or Bank3 NAND parameters.
  * @param  EXMC_NANDInitParaStruct : the struct EXMC_NANDInitPara pointer
  * @retval None
  */

void EXMC_NAND_Init(EXMC_NANDInitPara *EXMC_NANDInitParaStruct)
{
    uint32_t temp_CTLR = 0x00000000, temp_COMTR = 0x00000000, temp_ATTR = 0x00000000;

    temp_CTLR = (uint32_t)EXMC_NANDInitParaStruct->EXMC_WaitFeature |
                CTLR_EMTYP_NAND |
                EXMC_NANDInitParaStruct->EXMC_DatabusWidth |
                EXMC_NANDInitParaStruct->EXMC_ECCLogic |
                EXMC_NANDInitParaStruct->EXMC_ECCSize |
                (EXMC_NANDInitParaStruct->EXMC_CTRLatency << CTLR_CTR_OFFSET) |
                (EXMC_NANDInitParaStruct->EXMC_ATRLatency << CTLR_ATR_OFFSET);

    temp_COMTR = (uint32_t)EXMC_NANDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_SetupTime |
                 (EXMC_NANDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_WaitTime << COMTR_COMWT_OFFSET) |
                 (EXMC_NANDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_HoldTime << COMTR_COMHT_OFFSET) |
                 (EXMC_NANDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_DatabusHiZTime << COMTR_COMHIZT_OFFSET);

    temp_ATTR = (uint32_t)EXMC_NANDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_SetupTime |
                (EXMC_NANDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_WaitTime << ATTR_ATTWT_OFFSET) |
                (EXMC_NANDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_HoldTime << ATTR_ATTHT_OFFSET) |
                (EXMC_NANDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_DatabusHiZTime << ATTR_ATTHIZT_OFFSET);

    if (EXMC_NANDInitParaStruct->EXMC_NANDBank == EXMC_BANK2_NAND) {
        /* Configure the EXMC_Bank2 NAND registers using the value of parameters */
        EXMC_BANK2->CTLR2 = temp_CTLR;
        EXMC_BANK2->COMTR2 = temp_COMTR;
        EXMC_BANK2->ATTR2 = temp_ATTR;
    } else {
        /* EXMC_Bank3_NAND registers configuration */
        EXMC_BANK3->CTLR3 = temp_CTLR;
        EXMC_BANK3->COMTR3 = temp_COMTR;
        EXMC_BANK3->ATTR3 = temp_ATTR;
    }
}

/**
  * @brief  Initialize the EXMC Bank4 PCCARD parameters.
  * @param  EXMC_PCCARDInitParaStruct : the struct EXMC_PCCARDInitPara pointer.
  * @retval None
  */
void EXMC_PCCARD_Init(EXMC_PCCARDInitPara *EXMC_PCCARDInitParaStruct)
{
    /* Configure the EXMC_Bank4_PCCARD CTLR4 register using the value of parameters */
    EXMC_BANK4->CTLR4 = (uint32_t)EXMC_PCCARDInitParaStruct->EXMC_WaitFeature |
                        EXMC_DATABUS_WIDTH_16B |
                        (EXMC_PCCARDInitParaStruct->EXMC_CTRLatency << CTLR_CTR_OFFSET) |
                        (EXMC_PCCARDInitParaStruct->EXMC_ATRLatency << CTLR_ATR_OFFSET);

    /* Configure the EXMC_Bank4_PCCARD COMTR4 register using the value of parameters */
    EXMC_BANK4->COMTR4 = (uint32_t)EXMC_PCCARDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_SetupTime |
                         (EXMC_PCCARDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_WaitTime << COMTR_COMWT_OFFSET) |
                         (EXMC_PCCARDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_HoldTime << COMTR_COMHT_OFFSET) |
                         (EXMC_PCCARDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_DatabusHiZTime << COMTR_COMHIZT_OFFSET);

    /* Configure the EXMC_Bank4_PCCARD ATTR4 register using the value of parameters */
    EXMC_BANK4->ATTR4 = (uint32_t)EXMC_PCCARDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_SetupTime |
                        (EXMC_PCCARDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_WaitTime << ATTR_ATTWT_OFFSET) |
                        (EXMC_PCCARDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_HoldTime << ATTR_ATTHT_OFFSET) |
                        (EXMC_PCCARDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_DatabusHiZTime << ATTR_ATTHIZT_OFFSET);

    /* Configure the EXMC_Bank4_PCCARD IOTR4 register using the value of parameters */
    EXMC_BANK4->IOTR4 = (uint32_t)EXMC_PCCARDInitParaStruct->EXMC_IOSpaceTimingParaStruct->EXMC_SetupTime |
                        (EXMC_PCCARDInitParaStruct->EXMC_IOSpaceTimingParaStruct->EXMC_WaitTime << IOTR_IOTWT_OFFSET) |
                        (EXMC_PCCARDInitParaStruct->EXMC_IOSpaceTimingParaStruct->EXMC_HoldTime << IOTR_IOHT_OFFSET) |
                        (EXMC_PCCARDInitParaStruct->EXMC_IOSpaceTimingParaStruct->EXMC_DatabusHiZTime << IOTR_IOHIZT_OFFSET);
}

/**
  * @brief  Initialize the struct EXMC_NORSRAMInitPara
  * @param  EXMC_NORSRAMInitParaStruct: the struct EXMC_NORSRAMInitPara pointer
  * @retval None
  */
void EXMC_NORSRAMStruct_Init(EXMC_NORSRAMInitPara *EXMC_NORSRAMInitParaStruct)
{
    EXMC_NORSRAMInitParaStruct->EXMC_NORSRAMBank = EXMC_BANK1_NORSRAM1;
    EXMC_NORSRAMInitParaStruct->EXMC_AddressDataMux = EXMC_ADDRESS_DATA_MUX_ENABLE;
    EXMC_NORSRAMInitParaStruct->EXMC_MemoryType = EXMC_MEMORY_TYPE_SRAM;
    EXMC_NORSRAMInitParaStruct->EXMC_DatabusWidth = EXMC_DATABUS_WIDTH_8B;
    EXMC_NORSRAMInitParaStruct->EXMC_BurstMode = EXMC_BURST_MODE_DISABLE;
    EXMC_NORSRAMInitParaStruct->EXMC_NWAITPolarity = EXMC_NWAIT_POLARITY_LOW;
    EXMC_NORSRAMInitParaStruct->EXMC_WrapBurstMode = EXMC_WRAP_BURST_MODE_DISABLE;
    EXMC_NORSRAMInitParaStruct->EXMC_NWAITConfig = EXMC_NWAIT_CONFIG_BEFORE;
    EXMC_NORSRAMInitParaStruct->EXMC_MemoryWrite = EXMC_MEMORY_WRITE_ENABLE;
    EXMC_NORSRAMInitParaStruct->EXMC_NWAITSignal = EXMC_NWAIT_SIGNAL_ENABLE;
    EXMC_NORSRAMInitParaStruct->EXMC_ExtendedMode = EXMC_EXTENDED_MODE_DISABLE;
    EXMC_NORSRAMInitParaStruct->EXMC_AsynWait = EXMC_ASYN_WAIT_DISABLE;
    EXMC_NORSRAMInitParaStruct->EXMC_WriteMode = EXMC_ASYN_WRITE;
    EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_AsynAddressSetupTime = 0xF;
    EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_AsynAddressHoldTime = 0xF;
    EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_AsynDataSetupTime = 0xFF;
    EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_BusLatency = 0xF;
    EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_SynCLKDivision = 0xF;
    EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_SynDataLatency = 0xF;
    EXMC_NORSRAMInitParaStruct->EXMC_ReadWriteTimingParaStruct->EXMC_AsynAccessMode = EXMC_ACCESS_MODE_A;
    EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_AsynAddressSetupTime = 0xF;
    EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_AsynAddressHoldTime = 0xF;
    EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_AsynDataSetupTime = 0xFF;
    EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_BusLatency = 0xF;
    EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_SynCLKDivision = 0xF;
    EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_SynDataLatency = 0xF;
    EXMC_NORSRAMInitParaStruct->EXMC_WriteTimingParaStruct->EXMC_AsynAccessMode = EXMC_ACCESS_MODE_A;
}

/**
  * @brief  Initialize the struct EXMC_NANDInitPara
  * @param  EXMC_NANDInitParaStruct: the struct EXMC_NANDInitPara pointer.
  * @retval None
  */
void EXMC_NANDStruct_Init(EXMC_NANDInitPara *EXMC_NANDInitParaStruct)
{
    EXMC_NANDInitParaStruct->EXMC_NANDBank = EXMC_BANK2_NAND;
    EXMC_NANDInitParaStruct->EXMC_WaitFeature = EXMC_WAIT_FEATURE_DISABLE;
    EXMC_NANDInitParaStruct->EXMC_DatabusWidth = EXMC_DATABUS_WIDTH_8B;
    EXMC_NANDInitParaStruct->EXMC_ECCLogic = EXMC_ECC_LOGIC_DISABLE;
    EXMC_NANDInitParaStruct->EXMC_ECCSize = EXMC_ECC_SIZE_256BYTES;
    EXMC_NANDInitParaStruct->EXMC_CTRLatency = 0x0;
    EXMC_NANDInitParaStruct->EXMC_ATRLatency = 0x0;
    EXMC_NANDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_SetupTime = 0xFC;
    EXMC_NANDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_WaitTime = 0xFC;
    EXMC_NANDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_HoldTime = 0xFC;
    EXMC_NANDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_DatabusHiZTime = 0xFC;
    EXMC_NANDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_SetupTime = 0xFC;
    EXMC_NANDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_WaitTime = 0xFC;
    EXMC_NANDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_HoldTime = 0xFC;
    EXMC_NANDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_DatabusHiZTime = 0xFC;
}

/**
  * @brief  Initialize the struct EXMC_PCCARDInitParaStruct
  * @param  EXMC_PCCARDInitPara: the struct EXMC_PCCARDInitParaStruct pointer.
  * @retval None
  */
void EXMC_PCCARDStruct_Init(EXMC_PCCARDInitPara *EXMC_PCCARDInitParaStruct)
{
    EXMC_PCCARDInitParaStruct->EXMC_WaitFeature = EXMC_WAIT_FEATURE_DISABLE;
    EXMC_PCCARDInitParaStruct->EXMC_CTRLatency = 0x0;
    EXMC_PCCARDInitParaStruct->EXMC_ATRLatency = 0x0;
    EXMC_PCCARDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_SetupTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_WaitTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_HoldTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_CommonSpaceTimingParaStruct->EXMC_DatabusHiZTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_SetupTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_WaitTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_HoldTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_AttributeSpaceTimingParaStruct->EXMC_DatabusHiZTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_IOSpaceTimingParaStruct->EXMC_SetupTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_IOSpaceTimingParaStruct->EXMC_WaitTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_IOSpaceTimingParaStruct->EXMC_HoldTime = 0xFC;
    EXMC_PCCARDInitParaStruct->EXMC_IOSpaceTimingParaStruct->EXMC_DatabusHiZTime = 0xFC;
}

/**
  * @brief  Enable or disable the specified Region of Bank1.
  * @param  EXMC_NORSRAMBank: specifies the Region of Bank1.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK1_NORSRAM1: the Region1 of Bank1
  *     @arg EXMC_BANK1_NORSRAM2: the Region2 of Bank1
  *     @arg EXMC_BANK1_NORSRAM3: the Region3 of Bank1
  *     @arg EXMC_BANK1_NORSRAM4: the Region4 of Bank1
  * @param  NewValue: new value of the specified Region of Bank1.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EXMC_NORSRAM_Enable(uint32_t EXMC_NORSRAMBank, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the selected NOR/SRAM Bank by setting the PBKEN bit in the BCRx register */
        switch (EXMC_NORSRAMBank) {
        case EXMC_BANK1_NORSRAM1:
            EXMC_BANK1->SCTLR1 |= SCTLR_BAKEN_SET;
            break;
        case EXMC_BANK1_NORSRAM2:
            EXMC_BANK1->SCTLR2 |= SCTLR_BAKEN_SET;
            break;
        case EXMC_BANK1_NORSRAM3:
            EXMC_BANK1->SCTLR3 |= SCTLR_BAKEN_SET;
            break;
        case EXMC_BANK1_NORSRAM4:
            EXMC_BANK1->SCTLR4 |= SCTLR_BAKEN_SET;
            break;
        default:
            break;
        }
    } else {
        /* Disable the selected NOR/SRAM Bank by clearing the PBKEN bit in the BCRx register */
        switch (EXMC_NORSRAMBank) {
        case EXMC_BANK1_NORSRAM1:
            EXMC_BANK1->SCTLR1 &= SCTLR_BAKEN_RESET;
            break;
        case EXMC_BANK1_NORSRAM2:
            EXMC_BANK1->SCTLR2 &= SCTLR_BAKEN_RESET;
            break;
        case EXMC_BANK1_NORSRAM3:
            EXMC_BANK1->SCTLR3 &= SCTLR_BAKEN_RESET;
            break;
        case EXMC_BANK1_NORSRAM4:
            EXMC_BANK1->SCTLR4 &= SCTLR_BAKEN_RESET;
            break;
        default:
            break;
        }
    }
}

/**
  * @brief  Enable or disable the specified NAND Bank2 or Bank3.
  * @param  EXMC_NANDBank: specifies the NAND Bank.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK2_NAND: the NAND Bank2
  *     @arg EXMC_BANK3_NAND: the NAND Bank3
  * @param  NewValue: new value of the specified Bank.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EXMC_NAND_Enable(uint32_t EXMC_NANDBank, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the selected NAND Bank by setting the PBKEN bit in the PCRx register */
        if (EXMC_NANDBank == EXMC_BANK2_NAND) {
            EXMC_BANK2->CTLR2 |= CTLR_BAKEN_SET;
        } else {
            EXMC_BANK3->CTLR3 |= CTLR_BAKEN_SET;
        }
    } else {
        /* Disable the selected NAND Bank by clearing the PBKEN bit in the PCRx register */
        if (EXMC_NANDBank == EXMC_BANK2_NAND) {
            EXMC_BANK2->CTLR2 &= CTLR_BAKEN_RESET;
        } else {
            EXMC_BANK3->CTLR3 &= CTLR_BAKEN_RESET;
        }
    }
}

/**
  * @brief  Enable or disable the Bank4 of PCCARD.
  * @param  NewValue: new value of the PCCARD Bank.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EXMC_PCCARD_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the PCCARD Bank */
        EXMC_BANK4->CTLR4 |= CTLR_BAKEN_SET;
    } else {
        /* Disable the PCCARD Bank */
        EXMC_BANK4->CTLR4 &= CTLR_BAKEN_RESET;
    }
}

/**
  * @brief  Enable or disable the EXMC_CTLR1_ECCEN control bit.
  * @param  EXMC_NANDBank: specifies the NAND Bank.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK2_NAND: the NAND Bank2
  *     @arg EXMC_BANK3_NAND: the NAND Bank3
  * @param  NewValue: new value of the EXMC Bank2 or Bank3 ECC calculation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EXMC_NANDECC_Enable(uint32_t EXMC_NANDBank, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the selected NAND Bank ECC function by setting the ECCEN bit in the PCRx register */
        if (EXMC_NANDBank == EXMC_BANK2_NAND) {
            EXMC_BANK2->CTLR2 |= CTLR_ECCEN_SET;
        } else {
            EXMC_BANK3->CTLR3 |= CTLR_ECCEN_SET;
        }
    } else {
        /* Disable the selected NAND Bank ECC function by clearing the ECCEN bit in the PCRx register */
        if (EXMC_NANDBank == EXMC_BANK2_NAND) {
            EXMC_BANK2->CTLR2 &= CTLR_ECCEN_RESET;
        } else {
            EXMC_BANK3->CTLR3 &= CTLR_ECCEN_RESET;
        }
    }
}

/**
  * @brief  Get the EXMC_ECCR value.
  * @param  EXMC_NANDBank: specifies the NAND Bank.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK2_NAND: the NAND Bank2
  *     @arg EXMC_BANK3_NAND: the NAND Bank3
  * @retval The Error Correction Code (ECC) value.
  */
uint32_t EXMC_GetECC(uint32_t EXMC_NANDBank)
{
    if (EXMC_NANDBank == EXMC_BANK2_NAND) {
        return (EXMC_BANK2->ECCR2);
    } else {
        return (EXMC_BANK3->ECCR3);
    }
}

/**
  * @brief  Enable or disable the specified EXMC Bank2/3/4 interrupts.
  * @param  EXMC_PCNANDBank: specifies the NAND Bank or PCCARD Bank.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK2_NAND: the NAND Bank2
  *     @arg EXMC_BANK3_NAND: the NAND Bank3
  *     @arg EXMC_BANK4_PCCARD: the PCCARD Bank4
  * @param  EXMC_INT: the EXMC interrupt sources.
  *   This parameter can be any combination of the following values:
  *     @arg EXMC_INT_RISE: Rising edge detection interrupt
  *     @arg EXMC_INT_LEVEL: Level edge detection interrupt
  *     @arg EXMC_INT_FALL: Falling edge detection interrupt
  * @param  NewValue: new value of the specified EXMC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void EXMC_INTConfig(uint32_t EXMC_PCNANDBank, uint32_t EXMC_INT, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the specified EXMC_Bank2 interrupts */
        if (EXMC_PCNANDBank == EXMC_BANK2_NAND) {
            EXMC_BANK2->SIR2 |= EXMC_INT;
        }
        /* Enable the specified EXMC_Bank3 interrupts */
        else if (EXMC_PCNANDBank == EXMC_BANK3_NAND) {
            EXMC_BANK3->SIR3 |= EXMC_INT;
        }
        /* Enable the specified EXMC_Bank4 interrupts */
        else {
            EXMC_BANK4->SIR4 |= EXMC_INT;
        }
    } else {
        /* Disable the specified EXMC_Bank2 interrupts */
        if (EXMC_PCNANDBank == EXMC_BANK2_NAND) {
            EXMC_BANK2->SIR2 &= ~((uint32_t)EXMC_INT);
        }
        /* Disable the specified EXMC_Bank3 interrupts */
        else if (EXMC_PCNANDBank == EXMC_BANK3_NAND) {
            EXMC_BANK3->SIR3 &= ~((uint32_t)EXMC_INT);
        }
        /* Disable the specified EXMC_Bank4 interrupts */
        else {
            EXMC_BANK4->SIR4 &= ~((uint32_t)EXMC_INT);
        }
    }
}

/**
  * @brief  Get the bit flag of EXMC_SIRx register.
  * @param  EXMC_PCNANDBank: specifies the NAND Bank or PCCARD Bank.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK2_NAND: the NAND Bank2
  *     @arg EXMC_BANK3_NAND: the NAND Bank3
  *     @arg EXMC_BANK4_PCCARD: the PCCARD Bank4
  * @param  EXMC_FLAG: the flag of EXMC_SIRx register.
  *   This parameter can be one of the following values:
  *     @arg EXMC_FLAG_RISE: Rising egde detection Flag
  *     @arg EXMC_FLAG_LEVEL: Level detection Flag
  *     @arg EXMC_FLAG_FALL: Falling egde detection Flag
  *     @arg EXMC_FLAG_FIFOE: FIFO empty Flag
  * @retval The new value of EXMC_FLAG (SET or RESET).
  */
TypeState EXMC_GetBitState(uint32_t EXMC_PCNANDBank, uint32_t EXMC_FLAG)
{
    uint32_t temp_SIR = 0x00000000;
    /* the NAND Bank2 */
    if (EXMC_PCNANDBank == EXMC_BANK2_NAND) {
        temp_SIR = EXMC_BANK2->SIR2;
    }
    /* the NAND Bank3 */
    else if (EXMC_PCNANDBank == EXMC_BANK3_NAND) {
        temp_SIR = EXMC_BANK3->SIR3;
    }
    /* the PCCARD Bank4 */
    else {
        temp_SIR = EXMC_BANK4->SIR4;
    }

    if ((temp_SIR & EXMC_FLAG) != (uint16_t)RESET) {
        /* EXMC_FLAG is set */
        return SET;
    } else {
        /* EXMC_FLAG is reset */
        return RESET;
    }
}

/**
  * @brief  Clear the bit flag of EXMC_SIRx register.
  * @param  EXMC_PCNANDBank: specifies the NAND Bank or PCCARD Bank.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK2_NAND: the NAND Bank2
  *     @arg EXMC_BANK3_NAND: the NAND Bank3
  *     @arg EXMC_BANK4_PCCARD: the PCCARD Bank4
  * @param  EXMC_FLAG: the flag of EXMC_SIRx register.
  *   This parameter can be any combination of the following values:
  *     @arg EXMC_FLAG_RISE: Rising egde detection Flag
  *     @arg EXMC_FLAG_LEVEL: Level detection Flag
  *     @arg EXMC_FLAG_FALL: Falling egde detection Flag
  * @retval None
  */
void EXMC_ClearBitState(uint32_t EXMC_PCNANDBank, uint32_t EXMC_FLAG)
{
    if (EXMC_PCNANDBank == EXMC_BANK2_NAND) {
        EXMC_BANK2->SIR2 &= ~EXMC_FLAG;
    } else if (EXMC_PCNANDBank == EXMC_BANK3_NAND) {
        EXMC_BANK3->SIR3 &= ~EXMC_FLAG;
    }
    /* EXMC_Bank4_PCCARD*/
    else {
        EXMC_BANK4->SIR4 &= ~EXMC_FLAG;
    }
}

/**
  * @brief  Get the interrupt bit flag.
  * @param  EXMC_PCNANDBank: specifies the NAND Bank or PCCARD Bank.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK2_NAND: the NAND Bank2
  *     @arg EXMC_BANK3_NAND: the NAND Bank3
  *     @arg EXMC_BANK4_PCCARD: the PCCARD Bank4
  * @param  EXMC_INT: the interrupt bit flag.
  *   This parameter can be one of the following values:
  *     @arg EXMC_INT_RISE: Rising edge detection interrupt
  *     @arg EXMC_INT_LEVEL: Level edge detection interrupt
  *     @arg EXMC_INT_FALL: Falling edge detection interrupt
  * @retval The new value of EXMC_INT (SET or RESET).
  */
TypeState EXMC_GetIntBitState(uint32_t EXMC_PCNANDBank, uint32_t EXMC_INT)
{
    uint32_t temp_SIR = 0x00000000, temp_INTState = 0x00000000, temp_INTEnable = 0x00000000;

    if (EXMC_PCNANDBank == EXMC_BANK2_NAND) {
        temp_SIR = EXMC_BANK2->SIR2;
    } else if (EXMC_PCNANDBank == EXMC_BANK3_NAND) {
        temp_SIR = EXMC_BANK3->SIR3;
    }
    /* EXMC_Bank4_PCCARD*/
    else {
        temp_SIR = EXMC_BANK4->SIR4;
    }

    temp_INTState = temp_SIR & EXMC_INT;

    temp_INTEnable = temp_SIR & (EXMC_INT >> SIR_INTEN_OFFSET);

    if ((temp_INTState != (uint32_t)RESET)  && (temp_INTEnable != (uint32_t)RESET)) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Clear the interrupt bit flag.
  * @param  EXMC_PCNANDBank: specifies the NAND Bank or PCCARD Bank.
  *   This parameter can be one of the following values:
  *     @arg EXMC_BANK2_NAND: the NAND Bank2
  *     @arg EXMC_BANK3_NAND: the NAND Bank3
  *     @arg EXMC_BANK4_PCCARD: the PCCARD Bank4
  * @param  EXMC_INT: the interrupt bit flag.
  *   This parameter can be any combination of the following values:
  *     @arg EXMC_FLAG_RISE: Rising edge detection interrupt
  *     @arg EXMC_FLAG_LEVEL: Level edge detection interrupt
  *     @arg EXMC_FLAG_FALL: Falling edge detection interrupt
  * @retval None
  */
void EXMC_ClearIntBitState(uint32_t EXMC_PCNANDBank, uint32_t EXMC_INT)
{
    if (EXMC_PCNANDBank == EXMC_BANK2_NAND) {
        EXMC_BANK2->SIR2 &= ~(EXMC_INT >> SIR_INTEN_OFFSET);
    } else if (EXMC_PCNANDBank == EXMC_BANK3_NAND) {
        EXMC_BANK3->SIR3 &= ~(EXMC_INT >> SIR_INTEN_OFFSET);
    }
    /* EXMC_Bank4_PCCARD*/
    else {
        EXMC_BANK4->SIR4 &= ~(EXMC_INT >> SIR_INTEN_OFFSET);
    }
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
