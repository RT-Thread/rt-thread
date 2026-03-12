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
 * @file n32h76x_78x_mmu.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "n32h76x_78x_mmu.h"

/**
*\*\name    MMU_ConfigReset.
*\*\fun     This function Config MMU reset .
*\*\param   Cmd:
*\*\           - ENABLE :        Enable the Interrupt
*\*\           - DISABLE :       Disable the Interrupt
*\*\return  none
**/
void MMU_ConfigReset(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        MMU->CTRL |=  MMU_RESET;
    }
    else
    {
        MMU->CTRL &=  (~MMU_RESET);
    }
}

/**
*\*\name    MMU_ConfigInt.
*\*\fun     This function Config MMU Interrupt .
*\*\param   Cmd:
*\*\           - ENABLE :        Enable the Interrupt
*\*\           - DISABLE :       Disable the Interrupt
*\*\return  none
**/
void MMU_ConfigInt(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        MMU->CTRL |=  MMU_INT_EN;
    }
    else
    {
        MMU->CTRL &=  (~MMU_INT_EN);
    }
}

/**
*\*\name    MMU_GetFlagStatus.
*\*\fun     Checks whether the specified MMU flag is set or not.
*\*\param   MMU_FLAG: (The input   parameters must be the following values):
*\*\           - MMU_XSPI_LOCK_FLAG
*\*\           - MMU_ITCM_RERR_FLAG
*\*\           - MMU_ITCM_WERR_FLAG
*\*\           - MMU_BKSRAM_RERR_FLAG
*\*\           - MMU_BKSRAM_WERR_FLAG
*\*\           - MMU_AHBSRAM5_RERR_FLAG
*\*\           - MMU_AHBSRAM5_WERR_FLAG
*\*\           - MMU_AHBSRAM4_RERR_FLAG
*\*\           - MMU_AHBSRAM4_WERR_FLAG
*\*\           - MMU_AHBSRAM3_RERR_FLAG
*\*\           - MMU_AHBSRAM3_WERR_FLAG
*\*\           - MMU_AHBSRAM2_RERR_FLAG
*\*\           - MMU_AHBSRAM2_WERR_FLAG
*\*\           - MMU_AHBSRAM1_RERR_FLAG
*\*\           - MMU_AHBSRAM1_WERR_FLAG
*\*\           - MMU_AXISRAM3_RERR_FLAG
*\*\           - MMU_AXISRAM3_WERR_FLAG
*\*\           - MMU_AXISRAM2_RERR_FLAG
*\*\           - MMU_AXISRAM2_WERR_FLAG
*\*\           - MMU_AXISRAM1_RERR_FLAG
*\*\           - MMU_AXISRAM1_WERR_FLAG
*\*\           - MMU_OB_LOCK_FLAG
*\*\           - MMU_FLASH_LOCK_FLAG
*\*\           - MMU_XSPI_RERR_FLAG
*\*\return  bitstatus
*\*\           - SET
*\*\           - RESET
**/
FlagStatus MMU_GetFlagStatus(uint32_t MMU_FLAG)
{
    FlagStatus bitstatus;

    if ((MMU->STS & MMU_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}


/**
*\*\name    MMU_ClrFlag.
*\*\fun     Clears the MMU's pending flags.
*\*\param   MMU_FLAG: (The input   parameters must be the following values):
*\*\           - MMU_ITCM_RERR_FLAG
*\*\           - MMU_ITCM_WERR_FLAG
*\*\           - MMU_BKSRAM_RERR_FLAG
*\*\           - MMU_BKSRAM_WERR_FLAG
*\*\           - MMU_AHBSRAM5_RERR_FLAG
*\*\           - MMU_AHBSRAM5_WERR_FLAG
*\*\           - MMU_AHBSRAM4_RERR_FLAG
*\*\           - MMU_AHBSRAM4_WERR_FLAG
*\*\           - MMU_AHBSRAM3_RERR_FLAG
*\*\           - MMU_AHBSRAM3_WERR_FLAG
*\*\           - MMU_AHBSRAM2_RERR_FLAG
*\*\           - MMU_AHBSRAM2_WERR_FLAG
*\*\           - MMU_AHBSRAM1_RERR_FLAG
*\*\           - MMU_AHBSRAM1_WERR_FLAG
*\*\           - MMU_AXISRAM3_RERR_FLAG
*\*\           - MMU_AXISRAM3_WERR_FLAG
*\*\           - MMU_AXISRAM2_RERR_FLAG
*\*\           - MMU_AXISRAM2_WERR_FLAG
*\*\           - MMU_AXISRAM1_RERR_FLAG
*\*\           - MMU_AXISRAM1_WERR_FLAG
*\*\           - MMU_XSPI_RERR_FLAG
*\*\return  none
**/
void MMU_ClrFlag(uint32_t MMU_FLAG)
{
    MMU->STS &= (~MMU_FLAG);
}


/**
*\*\name    MMU_EnableRTAD.
*\*\fun     This function Enable RTADx.
*\*\param   RTADx :
*\*\           - MMU_RTAD1
*\*\           - MMU_RTAD2
*\*\           - MMU_RTAD3
*\*\           - MMU_RTAD4
*\*\param   Cmd :
*\*\           - ENABLE          Enable the RTADx
*\*\           - DISABLE         Disable the RTADx
*\*\return  none
**/
void MMU_EnableRTAD(uint32_t RTADx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        *(uint32_t *)(MMU_BASE + (MMU_RTAD_ADDRESS_OFFSET + ((RTADx - 1UL) * 4UL))) |= MMU_RTAD_ENABLE;
    }
    else
    {
        *(uint32_t *)(MMU_BASE + (MMU_RTAD_ADDRESS_OFFSET + ((RTADx - 1UL) * 4UL))) &= (~MMU_RTAD_ENABLE);
    }
}

/**
*\*\name    MMU_GetRTADRegionKey.
*\*\fun     RTAD Partial Area KEY Configuration.
*\*\param   region_key :
*\*\           - MMU_RTAD_REGION1_PART0_KEY                      MMU Region1 Part0 Key Register Offset Address
*\*\           - MMU_RTAD_REGION1_PART1_KEY                      MMU Region1 Part1 Key Register Offset Address
*\*\           - MMU_RTAD_REGION1_PART2_KEY                      MMU Region1 Part2 Key Register Offset Address
*\*\           - MMU_RTAD_REGION1_PART3_KEY                      MMU Region1 Part3 Key Register Offset Address
*\*\           - MMU_RTAD_REGION2_PART0_KEY                      MMU Region2 Part0 Key Register Offset Address
*\*\           - MMU_RTAD_REGION2_PART1_KEY                      MMU Region2 Part1 Key Register Offset Address
*\*\           - MMU_RTAD_REGION2_PART2_KEY                      MMU Region2 Part2 Key Register Offset Address
*\*\           - MMU_RTAD_REGION2_PART3_KEY                      MMU Region2 Part3 Key Register Offset Address
*\*\           - MMU_RTAD_REGION3_PART0_KEY                      MMU Region3 Part0 Key Register Offset Address
*\*\           - MMU_RTAD_REGION3_PART1_KEY                      MMU Region3 Part1 Key Register Offset Address
*\*\           - MMU_RTAD_REGION3_PART2_KEY                      MMU Region3 Part2 Key Register Offset Address
*\*\           - MMU_RTAD_REGION3_PART3_KEY                      MMU Region3 Part3 Key Register Offset Address
*\*\           - MMU_RTAD_REGION4_PART0_KEY                      MMU Region4 Part0 Key Register Offset Address
*\*\           - MMU_RTAD_REGION4_PART1_KEY                      MMU Region4 Part1 Key Register Offset Address
*\*\           - MMU_RTAD_REGION4_PART2_KEY                      MMU Region4 Part2 Key Register Offset Address
*\*\           - MMU_RTAD_REGION4_PART3_KEY                      MMU Region4 Part3 Key Register Offset Address
*\*\param   key :  The Key to Config
*\*\return  none
**/
uint32_t MMU_GetRTADRegionKey(uint32_t region)
{
    uint32_t key_temp;
    key_temp = *(uint32_t *)(MMU_BASE + region);
    return key_temp;
}

/**
*\*\name    MMU_ConfigRTADCFGLock.
*\*\fun     This function Config RTADx Config Key Lock / Unlock.
*\*\param   RTADx :
*\*\           - MMU_RTAD1
*\*\           - MMU_RTAD2
*\*\           - MMU_RTAD3
*\*\           - MMU_RTAD4
*\*\param   Cmd :
*\*\           - ENABLE          Enable the RTADx
*\*\           - DISABLE         Disable the RTADx
*\*\return  none
**/
void MMU_ConfigRTADCFGLock(uint32_t RTADx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        *(uint32_t *)(MMU_BASE + (MMU_RTAD_ADDRESS_OFFSET + ((RTADx - 1UL) * 4UL))) |= MMU_RTAD_CFG_LOCK;
    }
    else
    {
        *(uint32_t *)(MMU_BASE + (MMU_RTAD_ADDRESS_OFFSET + ((RTADx - 1UL) * 4UL))) &= (~MMU_RTAD_CFG_LOCK);
    }
}

/**
*\*\name    MMU_ConfigRTADKeyLock.
*\*\fun     This function Config RTADx Key Lock / Unlock.
*\*\param   RTADx :
*\*\           - MMU_RTAD1
*\*\           - MMU_RTAD2
*\*\           - MMU_RTAD3
*\*\           - MMU_RTAD4
*\*\param   Cmd :
*\*\           - ENABLE          Enable the RTADx
*\*\           - DISABLE         Disable the RTADx
*\*\return  none
**/
void MMU_ConfigRTADKeyLock(uint32_t RTADx, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        *(uint32_t *)(MMU_BASE + MMU_RTAD_ADDRESS_OFFSET + ((RTADx - 1UL) * 4UL)) |= MMU_RTAD_KEY_LOCK;
    }
    else
    {
        *(uint32_t *)(MMU_BASE + MMU_RTAD_ADDRESS_OFFSET + ((RTADx - 1UL) * 4UL)) &= (~MMU_RTAD_KEY_LOCK);
    }
}

/**
*\*\name    MMU_ConfigRTADMode.
*\*\fun     This function Config RTADx Work Mode.
*\*\param   RTADx :
*\*\           - MMU_RTAD1
*\*\           - MMU_RTAD2
*\*\           - MMU_RTAD3
*\*\           - MMU_RTAD4
*\*\param   mode :
*\*\           - MMU_RTAD_MODE_DEC_INST          RTAD Work as Decryption Instruction
*\*\           - MMU_RTAD_MODE_DEC_DATA          RTAD Work as Decryption Data / Literal
*\*\           - MMU_RTAD_MODE_DEC_ALL           RTAD Work as Decryption Instruction and Data / Literal
*\*\return  none
**/
void MMU_ConfigRTADMode(uint32_t RTADx, uint32_t mode)
{
    /* Clear the Mode Field */
    *(uint32_t *)(MMU_BASE + MMU_RTAD_ADDRESS_OFFSET + ((RTADx - 1UL) * 4UL)) &= (~MMU_RTAD_MODE_MASK);

    /* Config the Mode */
    *(uint32_t *)(MMU_BASE + MMU_RTAD_ADDRESS_OFFSET + ((RTADx - 1UL) * 4UL)) |= (mode);
}

/**
*\*\name    MMU_ConfigRTADProperty.
*\*\fun     This function Config RTADx Property.
*\*\param   RTADx :
*\*\           - MMU_RTAD1
*\*\           - MMU_RTAD2
*\*\           - MMU_RTAD3
*\*\           - MMU_RTAD4
*\*\param   property :
*\*\           - MMU_RTAD_PROPERTY_INST          Instruction Can Fetch this Region
*\*\           - MMU_RTAD_PROPERTY_DATA          Data Can Fetch this Region
*\*\           - MMU_RTAD_PROPERTY_ALL           Instruction and Data Can Fetch this Region
*\*\return  none
**/
void MMU_ConfigRTADProperty(uint32_t RTADx, uint32_t property)
{
    /* Clear the Mode Field */
    *(uint32_t *)(MMU_BASE + MMU_RTAD_ADDRESS_OFFSET + ((RTADx - 1UL) * 4UL)) &= (~MMU_RTAD_PROPERTY_MASK);

    /* Config the Mode */
    *(uint32_t *)(MMU_BASE + MMU_RTAD_ADDRESS_OFFSET + ((RTADx - 1UL) * 4UL)) |= (property);
}

/**
*\*\name    MMU_ConfigRTADRegionAddress.
*\*\fun     This function Config the Region Address.
*\*\param   region :
*\*\           - MMU_RTAD_REGION1
*\*\           - MMU_RTAD_REGION2
*\*\           - MMU_RTAD_REGION3
*\*\           - MMU_RTAD_REGION4
*\*\param   begin_addr :  0x0000~0x1FFF, The Region begin Address,Granularity size 4KB
*\*\param   end_addr :  0x0000~0x1FFF, The Region end Address,Granularity size 4KB
*\*\return  none
**/
void MMU_ConfigRTADRegionAddress(uint32_t region, uint32_t begin_addr, uint32_t end_addr)
{
    *(uint32_t *)(MMU_BASE + MMU_RTR_ADDRESS_OFFSET + ((region - 1UL) * 4UL)) = (begin_addr | (end_addr << MMU_RTR_ENDADDR_OFFSET));
}

/**
*\*\name    MMU_GetRTADCRC.
*\*\fun     This function Return RTADx CRC Value.
*\*\param   none
*\*\return  uint32_t : The RTAD CRC
**/
uint32_t MMU_GetRTADCRC(void)
{
    return ((uint32_t) MMU->RTCRC);
}

/**
*\*\name    MMU_EnableModuleMemory.
*\*\fun     This function Config the Module Memory Enable / Disable.
*\*\param   RTADx :
*\*\           - MMU_MEMORY_ETH1                 Enable ETH1 Memory
*\*\           - MMU_MEMORY_ETH2                 Enable ETH2 Memory
*\*\           - MMU_MEMORY_USB1                 Enable USB1 Memory
*\*\           - MMU_MEMORY_USB2                 Enable USB2 Memory
*\*\           - MMU_MEMORY_SDMMC1               Enable SDMMC1 Memory
*\*\           - MMU_MEMORY_SDMMC2               Enable SDMMC2 Memory
*\*\           - MMU_MEMORY_DVP1                 Enable DVP1 Memory
*\*\           - MMU_MEMORY_DVP2                 Enable DVP2 Memory
*\*\           - MMU_MEMORY_DMA1                 Enable DMA1 Memory
*\*\           - MMU_MEMORY_DMA2                 Enable DMA2 Memory
*\*\           - MMU_MEMORY_DMA3                 Enable DMA3 Memory
*\*\           - MMU_MEMORY_MDMA                 Enable MDMA Memory
*\*\           - MMU_MEMORY_JPEG                 Enable JPEG Memory
*\*\           - MMU_MEMORY_LCDC                 Enable LCDC Memory
*\*\           - MMU_MEMORY_GPU                  Enable GPU Memory
*\*\           - MMU_MEMORY_SDPU                 Enable SDPU Memory
*\*\param   Cmd :
*\*\            ENABLE          Enable the Memory
*\*\            DISABLE         Disable the Memory
*\*\return  none
**/
void MMU_EnableModuleMemory(uint32_t module, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        *(uint32_t *)(MMU_BASE + MMU_MEMORY_ADDRESS_OFFSET + ((module - 1UL) * 4UL)) |= MMU_MEMORY_EN;
    }
    else
    {
        *(uint32_t *)(MMU_BASE + MMU_MEMORY_ADDRESS_OFFSET + ((module - 1UL) * 4UL)) &= (~MMU_MEMORY_EN);
    }
}

/**
*\*\name    MMU_GetModuleUserID.
*\*\fun     This function Get Module User ID
*\*\param   RTADx :
*\*\           - MMU_MEMORY_ETH1                 Enable ETH1 Memory
*\*\           - MMU_MEMORY_ETH2                 Enable ETH2 Memory
*\*\           - MMU_MEMORY_USB1                 Enable USB1 Memory
*\*\           - MMU_MEMORY_USB2                 Enable USB2 Memory
*\*\           - MMU_MEMORY_SDMMC1               Enable SDMMC1 Memory
*\*\           - MMU_MEMORY_SDMMC2               Enable SDMMC2 Memory
*\*\           - MMU_MEMORY_DVP1                 Enable DVP1 Memory
*\*\           - MMU_MEMORY_DVP2                 Enable DVP2 Memory
*\*\           - MMU_MEMORY_DMA1                 Enable DMA1 Memory
*\*\           - MMU_MEMORY_DMA2                 Enable DMA2 Memory
*\*\           - MMU_MEMORY_DMA3                 Enable DMA3 Memory
*\*\           - MMU_MEMORY_MDMA                 Enable MDMA Memory
*\*\           - MMU_MEMORY_JPEG                 Enable JPEG Memory
*\*\           - MMU_MEMORY_LCDC                 Enable LCDC Memory
*\*\           - MMU_MEMORY_GPU                  Enable GPU Memory
*\*\           - MMU_MEMORY_SDPU                 Enable SDPU Memory
*\*\return  UID: The corresponding bit set to 1 indicates that it is enabled by the corresponding user.
*\*\           - [0]:other_id(SDRAM,external SRAM,etc), [1]: nonsec_tcm/sram, [2]: sec_tcm/sram, [3]:non_sec_flash,
*\*\           - [4] pfoer_flash, [5]: sec_flash, [6]: bootrom_api, [7]:sec_bootrom
**/
uint8_t MMU_GetModuleUserID(uint32_t module)
{
    uint32_t UID_temp;
    UID_temp = *(uint32_t *)(MMU_BASE + MMU_MEMORY_ADDRESS_OFFSET + ((module - 1UL) * 4UL));
    return ((uint8_t) (UID_temp >> MMU_MEMORY_UID_OFFSET));
}

/**
*\*\name    MMU_GetModuleMasterID.
*\*\fun     This function Get the Module Master ID.
*\*\param   RTADx :
*\*\           - MMU_MEMORY_ETH1                 Enable ETH1 Memory
*\*\           - MMU_MEMORY_ETH2                 Enable ETH2 Memory
*\*\           - MMU_MEMORY_USB1                 Enable USB1 Memory
*\*\           - MMU_MEMORY_USB2                 Enable USB2 Memory
*\*\           - MMU_MEMORY_SDMMC1               Enable SDMMC1 Memory
*\*\           - MMU_MEMORY_SDMMC2               Enable SDMMC2 Memory
*\*\           - MMU_MEMORY_DVP1                 Enable DVP1 Memory
*\*\           - MMU_MEMORY_DVP2                 Enable DVP2 Memory
*\*\           - MMU_MEMORY_DMA1                 Enable DMA1 Memory
*\*\           - MMU_MEMORY_DMA2                 Enable DMA2 Memory
*\*\           - MMU_MEMORY_DMA3                 Enable DMA3 Memory
*\*\           - MMU_MEMORY_MDMA                 Enable MDMA Memory
*\*\           - MMU_MEMORY_JPEG                 Enable JPEG Memory
*\*\           - MMU_MEMORY_LCDC                 Enable LCDC Memory
*\*\           - MMU_MEMORY_GPU                  Enable GPU Memory
*\*\           - MMU_MEMORY_SDPU                 Enable SDPU Memory
*\*\return  MID: The corresponding bit set to 1 indicates that it is enabled by the corresponding master.
*\*\           - [0]: CM7,[1]: CM4,[2]: DEBUG
**/
uint8_t MMU_GetModuleMasterID(uint32_t module)
{
    uint32_t MID_temp;
    MID_temp = *(uint32_t *)(MMU_BASE + MMU_MEMORY_ADDRESS_OFFSET + ((module - 1UL) * 4UL));
    return ((uint8_t) (MID_temp >> MMU_MEMORY_MID_OFFSET));
}

/**
*\*\name    MMU_GetReadErrorAddress.
*\*\fun     This function Get the Read Error Address.
*\*\param   readerroraddr :   The Read Error Register Offset Address
*\*\	      - MMU_XRAD_ADDR_OFFSET       XSPI read error address
*\*\	      - MMU_X1RAD_ADDR_OFFSET      AXI SRAM1 read error address
*\*\	      - MMU_X2RAD_ADDR_OFFSET      AXI SRAM2 read error address
*\*\	      - MMU_X3RAD_ADDR_OFFSET      AXI SRAM3 read error address
*\*\	      - MMU_H1RAD_ADDR_OFFSET      AHB SRAM1 read error address
*\*\	      - MMU_H2RAD_ADDR_OFFSET      AHB SRAM2 read error address
*\*\	      - MMU_H3RAD_ADDR_OFFSET      AHB SRAM3 read error address
*\*\	      - MMU_H4RAD_ADDR_OFFSET      AHB SRAM4 read error address
*\*\	      - MMU_H5RAD_ADDR_OFFSET      AHB SRAM5 read error address
*\*\	      - MMU_BKRAD_ADDR_OFFSET      Backup SRAM read error address
*\*\	      - MMU_ITRAD_ADDR_OFFSET      ITCM SRAM read error address
*\*\return  uint32_t error address
**/
uint32_t MMU_GetReadErrorAddress(uint32_t readerroraddr)
{
    return ((uint32_t) (*(uint32_t *)(MMU_BASE + readerroraddr)));
}

/**
*\*\name    MMU_GetWriteErrorAddress.
*\*\fun     This function Get the Write Error Address.
*\*\param   writeerroraddr :     The Write Error Register Offset Address
*\*\	      - MMU_X1WAD_ADDR_OFFSET      AXI SRAM1 read error address
*\*\	      - MMU_X2WAD_ADDR_OFFSET      AXI SRAM2 read error address
*\*\	      - MMU_X3WAD_ADDR_OFFSET      AXI SRAM3 read error address
*\*\	      - MMU_H1WAD_ADDR_OFFSET      AHB SRAM1 read error address
*\*\	      - MMU_H2WAD_ADDR_OFFSET      AHB SRAM2 read error address
*\*\	      - MMU_H3WAD_ADDR_OFFSET      AHB SRAM3 read error address
*\*\	      - MMU_H4WAD_ADDR_OFFSET      AHB SRAM4 read error address
*\*\	      - MMU_H5WAD_ADDR_OFFSET      AHB SRAM5 read error address
*\*\	      - MMU_BKWAD_ADDR_OFFSET      Backup SRAM read error address
*\*\	      - MMU_ITWAD_ADDR_OFFSET      ITCM SRAM read error address
*\*\return  uint32_t  error address
**/
uint32_t MMU_GetWriteErrorAddress(uint32_t writeerroraddr)
{
    return ((uint32_t) (*(uint32_t *)(MMU_BASE + writeerroraddr)));
}

/**
*\*\name    MMU_GetWriteErrorMasterID.
*\*\fun     This function Get Write Error Master ID.
*\*\param   writeerrordebug:    The Write Error ID Register Offset Address
*\*\	      - MMU_X1WD_ADDR_OFFSET      AXI SRAM1 read error debug
*\*\	      - MMU_X2WD_ADDR_OFFSET      AXI SRAM2 read error debug
*\*\	      - MMU_X3WD_ADDR_OFFSET      AXI SRAM3 read error debug
*\*\	      - MMU_H1WD_ADDR_OFFSET      AHB SRAM1 read error debug
*\*\	      - MMU_H2WD_ADDR_OFFSET      AHB SRAM2 read error debug
*\*\	      - MMU_H3WD_ADDR_OFFSET      AHB SRAM3 read error debug
*\*\	      - MMU_H4WD_ADDR_OFFSET      AHB SRAM4 read error debug
*\*\	      - MMU_H5WD_ADDR_OFFSET      AHB SRAM5 read error debug
*\*\	      - MMU_BKWD_ADDR_OFFSET      Backup SRAM read error debug
*\*\	      - MMU_ITWD_ADDR_OFFSET      ITCM SRAM read error debug
*\*\return  MID: The corresponding bit set to 1 indicates that it is enabled by the corresponding master.
*\*\          - [0]: DEBUG,[1]: other non-cpu master(ETH/USB/etc),[2]: CM7,[3]: CM4
**/
uint32_t MMU_GetWriteErrorMasterID(uint32_t writeerrordebug)
{
    uint32_t MID_temp;
    MID_temp = *(uint32_t *)(MMU_BASE + writeerrordebug);
    return ((uint8_t) (MID_temp >> MMU_WERRDEBUG_MID_OFFSET));
}

/**
*\*\name    MMU_GetWriteErrorUserID.
*\*\fun     This function Get Write Error User ID.
*\*\param   writeerrordebug :   The Write Error ID Register Offset Address
*\*\	      - MMU_X1WD_ADDR_OFFSET      AXI SRAM1 read error debug
*\*\	      - MMU_X2WD_ADDR_OFFSET      AXI SRAM2 read error debug
*\*\	      - MMU_X3WD_ADDR_OFFSET      AXI SRAM3 read error debug
*\*\	      - MMU_H1WD_ADDR_OFFSET      AHB SRAM1 read error debug
*\*\	      - MMU_H2WD_ADDR_OFFSET      AHB SRAM2 read error debug
*\*\	      - MMU_H3WD_ADDR_OFFSET      AHB SRAM3 read error debug
*\*\	      - MMU_H4WD_ADDR_OFFSET      AHB SRAM4 read error debug
*\*\	      - MMU_H5WD_ADDR_OFFSET      AHB SRAM5 read error debug
*\*\	      - MMU_BKWD_ADDR_OFFSET      Backup SRAM read error debug
*\*\	      - MMU_ITWD_ADDR_OFFSET      ITCM SRAM read error debug
*\*\return  UID: The corresponding bit set to 1 indicates that it is enabled by the corresponding user.
*\*\           - [0]:other_id(SDRAM,external SRAM,etc), [1]: nonsec_tcm/sram, [2]: sec_tcm/sram, [3]:non_sec_flash,
*\*\           - [4] pfoer_flash, [5]: sec_flash, [6]: bootrom_api, [7]:sec_bootrom
**/
uint32_t MMU_GetWriteErrorUserID(uint32_t writeerrordebug)
{
    uint32_t UID_temp;
    UID_temp = *(uint32_t *)(MMU_BASE + writeerrordebug);
    return ((uint8_t) UID_temp);
}

/**
*\*\name    MMU_GetReadErrorMasterID.
*\*\fun     This function Get Read Error Master ID.
*\*\param   readerrordebug :   The Read Error ID Register Offset Address
*\*\	      - MMU_XRD_ADDR_OFFSET       XSPI read error debug
*\*\	      - MMU_X1RD_ADDR_OFFSET      AXI SRAM1 read error debug
*\*\	      - MMU_X2RD_ADDR_OFFSET      AXI SRAM2 read error debug
*\*\	      - MMU_X3RD_ADDR_OFFSET      AXI SRAM3 read error debug
*\*\	      - MMU_H1RD_ADDR_OFFSET      AHB SRAM1 read error debug
*\*\	      - MMU_H2RD_ADDR_OFFSET      AHB SRAM2 read error debug
*\*\	      - MMU_H3RD_ADDR_OFFSET      AHB SRAM3 read error debug
*\*\	      - MMU_H4RD_ADDR_OFFSET      AHB SRAM4 read error debug
*\*\	      - MMU_H5RD_ADDR_OFFSET      AHB SRAM5 read error debug
*\*\	      - MMU_BKRD_ADDR_OFFSET      Backup SRAM read error debug
*\*\	      - MMU_ITRD_ADDR_OFFSET      ITCM SRAM read error debug
*\*\return  MID: The corresponding bit set to 1 indicates that it is enabled by the corresponding master.
*\*\          - [0]: DEBUG,[1]: other non-cpu master(ETH/USB/etc),[2]: CM7,[3]: CM4
**/
uint32_t MMU_GetReadErrorMasterID(uint32_t readerrordebug)
{
    uint32_t MID_temp;
    MID_temp = *(uint32_t *)(MMU_BASE + readerrordebug);
    return ((uint8_t) (MID_temp >> MMU_WERRDEBUG_MID_OFFSET));
}

/**
*\*\name    MMU_GetReadErrorUserID.
*\*\fun     This function Get Read Error User ID.
*\*\param   readerrordebug :   The Read Error ID Register Offset Address
*\*\	      - MMU_XRD_ADDR_OFFSET       XSPI read error debug
*\*\	      - MMU_X1RD_ADDR_OFFSET      AXI SRAM1 read error debug
*\*\	      - MMU_X2RD_ADDR_OFFSET      AXI SRAM2 read error debug
*\*\	      - MMU_X3RD_ADDR_OFFSET      AXI SRAM3 read error debug
*\*\	      - MMU_H1RD_ADDR_OFFSET      AHB SRAM1 read error debug
*\*\	      - MMU_H2RD_ADDR_OFFSET      AHB SRAM2 read error debug
*\*\	      - MMU_H3RD_ADDR_OFFSET      AHB SRAM3 read error debug
*\*\	      - MMU_H4RD_ADDR_OFFSET      AHB SRAM4 read error debug
*\*\	      - MMU_H5RD_ADDR_OFFSET      AHB SRAM5 read error debug
*\*\	      - MMU_BKRD_ADDR_OFFSET      Backup SRAM read error debug
*\*\	      - MMU_ITRD_ADDR_OFFSET      ITCM SRAM read error debug
*\*\return  UID: The corresponding bit set to 1 indicates that it is enabled by the corresponding user.
*\*\           - [0]:other_id(SDRAM,external SRAM,etc), [1]: nonsec_tcm/sram, [2]: sec_tcm/sram, [3]:non_sec_flash,
*\*\           - [4] pfoer_flash, [5]: sec_flash, [6]: bootrom_api, [7]:sec_bootrom
**/
uint32_t MMU_GetReadErrorUserID(uint32_t readerrordebug)
{
    uint32_t UID_temp;
    UID_temp = *(uint32_t *)(MMU_BASE + readerrordebug);
    return ((uint8_t) UID_temp);
}


