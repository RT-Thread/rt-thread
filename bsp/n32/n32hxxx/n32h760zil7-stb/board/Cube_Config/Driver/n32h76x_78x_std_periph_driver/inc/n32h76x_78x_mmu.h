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
 * @file n32h76x_78x_mmu.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H76X_78X_MMU_H__
#define __N32H76X_78X_MMU_H__

#include "n32h76x_78x.h"

#ifdef __cplusplus
extern "C" {
#endif
 
/** MMU Flash Key **/
#define MMU_FLASH_KEY0  ((uint32_t) 0x89ABCDEFU)
#define MMU_FLASH_KEY1  ((uint32_t) 0x01234567U)

/** MMU Control **/
#define MMU_RESET   (MMU_CTRL_RSTE)
#define MMU_INT_EN  (MMU_CTRL_INTE)

/** MMU status register **/
#define MMU_XSPI_LOCK_FLAG       (MMU_STS_XSPIL)
#define MMU_ITCM_RERR_FLAG       (MMU_STS_ITRDE)
#define MMU_ITCM_WERR_FLAG       (MMU_STS_ITWRE)
#define MMU_BKSRAM_RERR_FLAG     (MMU_STS_BKRDE)
#define MMU_BKSRAM_WERR_FLAG     (MMU_STS_BKWRE)
#define MMU_AHBSRAM5_RERR_FLAG   (MMU_STS_H5RDE)
#define MMU_AHBSRAM5_WERR_FLAG   (MMU_STS_H5WRE)
#define MMU_AHBSRAM4_RERR_FLAG   (MMU_STS_H4RDE)
#define MMU_AHBSRAM4_WERR_FLAG   (MMU_STS_H4WRE)
#define MMU_AHBSRAM3_RERR_FLAG   (MMU_STS_H3RDE)
#define MMU_AHBSRAM3_WERR_FLAG   (MMU_STS_H3WRE)
#define MMU_AHBSRAM2_RERR_FLAG   (MMU_STS_H2RDE)
#define MMU_AHBSRAM2_WERR_FLAG   (MMU_STS_H2WRE)
#define MMU_AHBSRAM1_RERR_FLAG   (MMU_STS_H1RDE)
#define MMU_AHBSRAM1_WERR_FLAG   (MMU_STS_H1WRE)
#define MMU_AXISRAM3_RERR_FLAG   (MMU_STS_X3RDE)
#define MMU_AXISRAM3_WERR_FLAG   (MMU_STS_X3WRE)
#define MMU_AXISRAM2_RERR_FLAG   (MMU_STS_X2RDE)
#define MMU_AXISRAM2_WERR_FLAG   (MMU_STS_X2WRE)
#define MMU_AXISRAM1_RERR_FLAG   (MMU_STS_X1RDE)
#define MMU_AXISRAM1_WERR_FLAG   (MMU_STS_X1WRE)
#define MMU_OB_LOCK_FLAG         (MMU_STS_OBL)
#define MMU_FLASH_LOCK_FLAG      (MMU_STS_FLASHL)
#define MMU_XSPI_RERR_FLAG       (MMU_STS_XSPIRDE)

/** MMU RTAD **/
#define MMU_RTAD_ADDRESS_OFFSET     ((uint32_t)0x00000034U)
#define MMU_RTAD1                   ((uint32_t)0x00000001U)
#define MMU_RTAD2                   ((uint32_t)0x00000002U)
#define MMU_RTAD3                   ((uint32_t)0x00000003U)
#define MMU_RTAD4                   ((uint32_t)0x00000004U)

#define MMU_RTR_ADDRESS_OFFSET      ((uint32_t)0x00000084U)
#define MMU_RTR_ENDADDR_OFFSET      ((uint32_t)0x00000010U)
#define MMU_RTAD_REGION1            ((uint32_t)0x00000001U)
#define MMU_RTAD_REGION2            ((uint32_t)0x00000002U)
#define MMU_RTAD_REGION3            ((uint32_t)0x00000003U)
#define MMU_RTAD_REGION4            ((uint32_t)0x00000004U)

#define MMU_RTAD_ENABLE             (MMU_RTADC_REN)
#define MMU_RTAD_CFG_LOCK           (MMU_RTADC_RCFGL)
#define MMU_RTAD_KEY_LOCK           (MMU_RTADC_RKEYL)

#define MMU_RTAD_MODE_DEC_INST      ((uint32_t) 0x00000000U)
#define MMU_RTAD_MODE_DEC_DATA      (MMU_RTADC_RMOD_0)
#define MMU_RTAD_MODE_DEC_ALL       (MMU_RTADC_RMOD_1)
#define MMU_RTAD_MODE_MASK          (MMU_RTADC_RMOD)

#define MMU_RTAD_PROPERTY_INST      ((uint32_t) 0x00000000U)
#define MMU_RTAD_PROPERTY_DATA      (MMU_RTADC_RPROPERTY_0)
#define MMU_RTAD_PROPERTY_ALL       (MMU_RTADC_RPROPERTY_1)
#define MMU_RTAD_PROPERTY_MASK      (MMU_RTADC_RPROPERTY)

#define MMU_RTAD_REGION1_PART0_KEY  ((uint32_t) 0x00000044U)
#define MMU_RTAD_REGION1_PART1_KEY  ((uint32_t) 0x00000048U)
#define MMU_RTAD_REGION1_PART2_KEY  ((uint32_t) 0x0000004CU)
#define MMU_RTAD_REGION1_PART3_KEY  ((uint32_t) 0x00000050U)

#define MMU_RTAD_REGION2_PART0_KEY  ((uint32_t) 0x00000054U)
#define MMU_RTAD_REGION2_PART1_KEY  ((uint32_t) 0x00000058U)
#define MMU_RTAD_REGION2_PART2_KEY  ((uint32_t) 0x0000005CU)
#define MMU_RTAD_REGION2_PART3_KEY  ((uint32_t) 0x00000060U)

#define MMU_RTAD_REGION3_PART0_KEY  ((uint32_t) 0x00000064U)
#define MMU_RTAD_REGION3_PART1_KEY  ((uint32_t) 0x00000068U)
#define MMU_RTAD_REGION3_PART2_KEY  ((uint32_t) 0x0000006CU)
#define MMU_RTAD_REGION3_PART3_KEY  ((uint32_t) 0x00000070U)

#define MMU_RTAD_REGION4_PART0_KEY  ((uint32_t) 0x00000074U)
#define MMU_RTAD_REGION4_PART1_KEY  ((uint32_t) 0x00000078U)
#define MMU_RTAD_REGION4_PART2_KEY  ((uint32_t) 0x0000007CU)
#define MMU_RTAD_REGION4_PART3_KEY  ((uint32_t) 0x00000080U)


/** MMU Module Memory **/
#define MMU_MEMORY_ADDRESS_OFFSET   ((uint32_t)0x0000012CU)
#define MMU_MEMORY_EN               (MMU_ETH1ME_EN)
#define MMU_MEMORY_ETH1             ((uint32_t) 0x00000001U)
#define MMU_MEMORY_ETH2             ((uint32_t) 0x00000002U)
#define MMU_MEMORY_USB1             ((uint32_t) 0x00000003U)
#define MMU_MEMORY_USB2             ((uint32_t) 0x00000004U)
#define MMU_MEMORY_SDMMC1           ((uint32_t) 0x00000005U)
#define MMU_MEMORY_SDMMC2           ((uint32_t) 0x00000006U)
#define MMU_MEMORY_DVP1             ((uint32_t) 0x00000007U)
#define MMU_MEMORY_DVP2             ((uint32_t) 0x00000008U)
#define MMU_MEMORY_DMA1             ((uint32_t) 0x00000009U)
#define MMU_MEMORY_DMA2             ((uint32_t) 0x0000000AU)
#define MMU_MEMORY_DMA3             ((uint32_t) 0x0000000BU)
#define MMU_MEMORY_MDMA             ((uint32_t) 0x0000000CU)
#define MMU_MEMORY_JPEG             ((uint32_t) 0x0000000DU)
#define MMU_MEMORY_LCDC             ((uint32_t) 0x0000000EU)
#define MMU_MEMORY_GPU              ((uint32_t) 0x0000000FU)
#define MMU_MEMORY_SDPU             ((uint32_t) 0x00000010U)
#define MMU_MEMORY_UID_OFFSET       (REG_BIT8_OFFSET)
#define MMU_MEMORY_MID_OFFSET       (REG_BIT16_OFFSET)

/** MMU Read Error Address Register **/
#define MMU_XRAD_ADDR_OFFSET              ((uint32_t) 0x00000178U)
#define MMU_X1RAD_ADDR_OFFSET             ((uint32_t) 0x00000188U)
#define MMU_X2RAD_ADDR_OFFSET             ((uint32_t) 0x00000198U)
#define MMU_X3RAD_ADDR_OFFSET             ((uint32_t) 0x000001A8U)

#define MMU_H1RAD_ADDR_OFFSET             ((uint32_t) 0x0000021CU)
#define MMU_H2RAD_ADDR_OFFSET             ((uint32_t) 0x0000022CU)
#define MMU_H3RAD_ADDR_OFFSET             ((uint32_t) 0x0000023CU)
#define MMU_H4RAD_ADDR_OFFSET             ((uint32_t) 0x0000024CU)
#define MMU_H5RAD_ADDR_OFFSET             ((uint32_t) 0x0000025CU)

#define MMU_BKRAD_ADDR_OFFSET             ((uint32_t) 0x0000026CU)
#define MMU_ITRAD_ADDR_OFFSET             ((uint32_t) 0x0000027CU)

/** MMU Write Error Address Register **/
#define MMU_X1WAD_ADDR_OFFSET             ((uint32_t) 0x00000184U)
#define MMU_X2WAD_ADDR_OFFSET             ((uint32_t) 0x00000194U)
#define MMU_X3WAD_ADDR_OFFSET             ((uint32_t) 0x000001A4U)

#define MMU_H1WAD_ADDR_OFFSET             ((uint32_t) 0x00000218U)
#define MMU_H2WAD_ADDR_OFFSET             ((uint32_t) 0x00000228U)
#define MMU_H3WAD_ADDR_OFFSET             ((uint32_t) 0x00000238U)
#define MMU_H4WAD_ADDR_OFFSET             ((uint32_t) 0x00000248U)
#define MMU_H5WAD_ADDR_OFFSET             ((uint32_t) 0x00000258U)

#define MMU_BKWAD_ADDR_OFFSET             ((uint32_t) 0x00000268U)
#define MMU_ITWAD_ADDR_OFFSET             ((uint32_t) 0x00000278U)

/** MMU Read Error Debug Register **/
#define MMU_XRD_ADDR_OFFSET              ((uint32_t) 0x00000170U)
#define MMU_X1RD_ADDR_OFFSET             ((uint32_t) 0x00000180U)
#define MMU_X2RD_ADDR_OFFSET             ((uint32_t) 0x00000190U)
#define MMU_X3RD_ADDR_OFFSET             ((uint32_t) 0x000001A0U)

#define MMU_H1RD_ADDR_OFFSET             ((uint32_t) 0x00000214U)
#define MMU_H2RD_ADDR_OFFSET             ((uint32_t) 0x00000224U)
#define MMU_H3RD_ADDR_OFFSET             ((uint32_t) 0x00000234U)
#define MMU_H4RD_ADDR_OFFSET             ((uint32_t) 0x00000244U)
#define MMU_H5RD_ADDR_OFFSET             ((uint32_t) 0x00000254U)

#define MMU_BKRD_ADDR_OFFSET             ((uint32_t) 0x00000264U)
#define MMU_ITRD_ADDR_OFFSET             ((uint32_t) 0x00000274U)
#define MMU_RERRDEBUG_MID_OFFSET         (REG_BIT8_OFFSET)

/** MMU Write Error Debug Register **/
#define MMU_X1WD_ADDR_OFFSET             ((uint32_t) 0x0000017CU)
#define MMU_X2WD_ADDR_OFFSET             ((uint32_t) 0x0000018CU)
#define MMU_X3WD_ADDR_OFFSET             ((uint32_t) 0x0000019CU)

#define MMU_H1WD_ADDR_OFFSET             ((uint32_t) 0x00000210U)
#define MMU_H2WD_ADDR_OFFSET             ((uint32_t) 0x00000220U)
#define MMU_H3WD_ADDR_OFFSET             ((uint32_t) 0x00000230U)
#define MMU_H4WD_ADDR_OFFSET             ((uint32_t) 0x00000240U)
#define MMU_H5WD_ADDR_OFFSET             ((uint32_t) 0x00000250U)

#define MMU_BKWD_ADDR_OFFSET             ((uint32_t) 0x00000260U)
#define MMU_ITWD_ADDR_OFFSET             ((uint32_t) 0x00000270U)
#define MMU_WERRDEBUG_MID_OFFSET         (REG_BIT8_OFFSET)

/** MMU Function **/
void MMU_ConfigReset(FunctionalState Cmd);
void MMU_ConfigInt(FunctionalState Cmd);
FlagStatus MMU_GetFlagStatus(uint32_t MMU_FLAG);
void MMU_ClrFlag(uint32_t MMU_FLAG);
void MMU_EnableRTAD(uint32_t RTADx, FunctionalState Cmd);
uint32_t MMU_GetRTADRegionKey(uint32_t region);
void MMU_ConfigRTADCFGLock(uint32_t RTADx, FunctionalState Cmd);
void MMU_ConfigRTADKeyLock(uint32_t RTADx, FunctionalState Cmd);
void MMU_ConfigRTADMode(uint32_t RTADx, uint32_t mode);
void MMU_ConfigRTADProperty(uint32_t RTADx, uint32_t property);
void MMU_ConfigRTADRegionAddress(uint32_t region, uint32_t begin_addr, uint32_t end_addr);
uint32_t MMU_GetRTADCRC(void);
void MMU_EnableModuleMemory(uint32_t module, FunctionalState Cmd);
uint8_t MMU_GetModuleUserID(uint32_t module);
uint8_t MMU_GetModuleMasterID(uint32_t module);
uint32_t MMU_GetReadErrorAddress(uint32_t readerroraddr);
uint32_t MMU_GetWriteErrorAddress(uint32_t writeerroraddr);
uint32_t MMU_GetWriteErrorMasterID(uint32_t writeerrordebug);
uint32_t MMU_GetWriteErrorUserID(uint32_t writeerrordebug);
uint32_t MMU_GetReadErrorMasterID(uint32_t readerrordebug);
uint32_t MMU_GetReadErrorUserID(uint32_t readerrordebug);


#ifdef __cplusplus
}
#endif

#endif /* __N32H76X_78X_MMU_H__ */
