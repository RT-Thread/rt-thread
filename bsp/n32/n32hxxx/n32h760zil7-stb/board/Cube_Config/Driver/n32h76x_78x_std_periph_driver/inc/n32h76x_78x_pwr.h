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
 * @file n32h76x_78x_pwr.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H76X_78X_PWR_H__
#define __N32H76X_78X_PWR_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "n32h76x_78x.h"


/** PWR sleep status enmu definition **/
typedef enum
{
    PWR_SLEEP_NOW = 0x0,
    PWR_SLEEP_ON_EXIT = 0x1,
} PWR_SLEEPONEXIT_STATUS; 

/**  PWR registers bit mask  **/
/** PWR system status enmu definition **/
typedef enum
{
    PWR_SYSTEM_RUN = 0x0,
    PWR_SYSTEM_STOP0 = 0x1,
    PWR_SYSTEM_STOP2 = 0x2,
} SYSTEM_OPTC_STATUS; 
/** PWR system memory enmu definition **/
typedef enum
{
    SYSTEM_MEMORY_AXISRAM    = 0x0,
    SYSTEM_MEMORY_AHBSRAM1   = 0x1,
    SYSTEM_MEMORY_AHBSRAM2   = 0x2,
    SYSTEM_MEMORY_AHBSRAM3   = 0x3,
    SYSTEM_MEMORY_AHBSRAM4   = 0x4,
    SYSTEM_MEMORY_AHBSRAM5S1 = 0x5,
    SYSTEM_MEMORY_AHBSRAM5S2 = 0x6,
} SYSTEM_MEMORY_TYPE;
/** PWR VDDD POR/PDR mode enmu definition **/
typedef enum
{
    SYSTEM_RUN_MODE         = 0x0,
    SYSTEM_LOW_POWER_MODE   = 0x1,
} SYSTEM_POWER_TYPE;

/** register bit mask **/
#define PWR_REG_BIT_MASK                ((uint32_t)0x00000000U)

/** POR BOR DCDC VSEL Control Register **/
#define PVD_ContrlBaseAddress           (AFEC_BASE + 0x2CU)
#define AVD_ContrlBaseAddress           (AFEC_BASE + 0x00U)
#define DCDC_ContrlBaseAddress          (AFEC_BASE + 0x30U)
/** POR BOR DCDC VSEL bit mask **/
#define BOR_VSEL_BIT_MASK               ((uint32_t)0x03E00000U)
#define POR_VSEL_BIT_MASK               ((uint32_t)0x001F0000U)

#define DCDC_VSEL_MASK                  ((uint32_t)0x00001F00U)
#define DCDC_VSEL_POR_MASK              ((uint32_t)0x001F0000U)
#define DCDC_VSEL_BOR_MASK              ((uint32_t)0x03E00000U)


/** CM7/CM4 low power config **/
#define PWR_PDSLPS_MASK         (~(PWR_CTRL_LPS | PWR_CTRL_PDS))
#define PWR_PDS_SET             (PWR_CTRL_PDS)
#define PWR_REGULATOR_NORMAL    (PWR_REG_BIT_MASK)
#define PWR_REGULATOR_LOWPOWER  (PWR_CTRL_LPS)

/** PWR_ENABLE **/ 
#define PWR_STBRET_ENABLE        (PWR_M7CTRL2_BSRSTBRET) 
#define PWR_VBATRET_ENABLE       (PWR_M7CTRL2_BSRVBRET) 

/** PVD level config **/
#define PWR_PVD_LEVEL_MASK                          ((uint32_t)0x001E0000U)
#define PWR_PVD_LEVEL_2V28                          ((uint32_t)0x000A0000U)
#define PWR_PVD_LEVEL_2V38                          ((uint32_t)0x000C0000U)
#define PWR_PVD_LEVEL_2V48                          ((uint32_t)0x000E0000U)
#define PWR_PVD_LEVEL_2V58                          ((uint32_t)0x00100000U)
#define PWR_PVD_LEVEL_2V68                          ((uint32_t)0x00120000U)
#define PWR_PVD_LEVEL_2V78                          ((uint32_t)0x00140000U)
#define PWR_PVD_LEVEL_2V88                          ((uint32_t)0x00160000U)
#define PWR_PVD_LEVEL_3V28                          ((uint32_t)0x00180000U)
#define PWR_PVD_LEVEL_3V38                          ((uint32_t)0x001A0000U)
#define PWR_PVD_LEVEL_3V48                          ((uint32_t)0x001C0000U)
#define PWR_PVD_LEVEL_3V58                          ((uint32_t)0x001E0000U)
/** AVD level config **/
#define PWR_AVD_LEVEL_MASK                          ((uint32_t)0x0000F000U)
#define PWR_AVD_LEVEL_2V28                          ((uint32_t)0x00005000U)
#define PWR_AVD_LEVEL_2V38                          ((uint32_t)0x00006000U)
#define PWR_AVD_LEVEL_2V48                          ((uint32_t)0x00007000U)
#define PWR_AVD_LEVEL_2V58                          ((uint32_t)0x00008000U)
#define PWR_AVD_LEVEL_2V68                          ((uint32_t)0x00009000U)
#define PWR_AVD_LEVEL_2V78                          ((uint32_t)0x0000A000U)
#define PWR_AVD_LEVEL_2V88                          ((uint32_t)0x0000B000U)
#define PWR_AVD_LEVEL_3V28                          ((uint32_t)0x0000C000U)
#define PWR_AVD_LEVEL_3V38                          ((uint32_t)0x0000D000U)
#define PWR_AVD_LEVEL_3V48                          ((uint32_t)0x0000E000U)
#define PWR_AVD_LEVEL_3V58                          ((uint32_t)0x0000F000U)

/**VDDD POR PDR level config **/
#define PWR_VDDD_POR_Level_MASK                     ((uint32_t)0x00000003U)
#define PWR_VDDD_POR_Level_0V70                     ((uint32_t)0x00000000U)
#define PWR_VDDD_POR_Level_0V75                     ((uint32_t)0x00000002U)
#define PWR_VDDD_POR_Level_0V80                     ((uint32_t)0x00000003U)
/**VDDD POR PDR bit offset **/
#define PWR_VDDD_POR_LEVEL_OFFSET                   ((uint32_t)0x0000000CU)
#define PWR_VDDD_LPPOR_LEVEL_OFFSET                 ((uint32_t)0x00000016U)

/** DCDC POR PDR level config **/
#define PWR_DCDC_POR_Level_MASK                     ((uint32_t)0x0000001FU)
#define PWR_DCDC_POR_Level_0V80                     ((uint32_t)0x00000005U)
#define PWR_DCDC_POR_Level_0V85                     ((uint32_t)0x00000006U)
#define PWR_DCDC_POR_Level_0V90                     ((uint32_t)0x00000007U)
/**DCDC POR PDR bit offset **/
#define PWR_DCDC_POR_LEVEL_OFFSET                   ((uint32_t)0x00000010U)
#define PWR_DCDC_LPPOR_LEVEL_OFFSET                 ((uint32_t)0x00000011U)

/** Main LDO Output Voltage config **/
#define PWR_MLDO_VOLTAGE_OUTPUT_LEVEL_MASK          ((uint32_t)0x00000003U)
#define PWR_MLDO_VOLTAGE_OUTPUT_LEVEL_0V80          ((uint32_t)0x00000000U)
#define PWR_MLDO_VOLTAGE_OUTPUT_LEVEL_0V85          ((uint32_t)0x00000001U)
#define PWR_MLDO_VOLTAGE_OUTPUT_LEVEL_0V90          ((uint32_t)0x00000002U)
/**Main LDO Output Voltage bit offset **/
#define PWR_MLDO_VOLT_OUTPUT_LEVEL_OFFSET           ((uint32_t)0x00000008U)
#define PWR_MLDO_LP_VOLT_OUTPUT_LEVEL_OFFSET        ((uint32_t)0x0000000AU)

/** DCDC Output Voltage config **/
#define PWR_DCDC_VOLTAGE_OUTPUT_LEVEL_MASK          ((uint32_t)0x0000000FU)
#define PWR_DCDC_VOLTAGE_OUTPUT_LEVEL_0V80          ((uint32_t)0x00000005U)
#define PWR_DCDC_VOLTAGE_OUTPUT_LEVEL_0V85          ((uint32_t)0x00000006U)
#define PWR_DCDC_VOLTAGE_OUTPUT_LEVEL_0V90          ((uint32_t)0x00000007U)
/**DCDC Output Voltage bit offset **/
#define PWR_DCDC_VOLT_OUTPUT_LEVEL_OFFSET           ((uint32_t)0x00000008U)
#define PWR_DCDC_LP_VOLT_OUTPUT_LEVEL_OFFSET        ((uint32_t)0x00000018U)

/** BKPLDO Output Voltage config **/
#define PWR_BKPLDO_VOLTAGE_OUTPUT_LEVEL_MASK        ((uint32_t)0x00000001U)
#define PWR_BKPLDO_VOLTAGE_OUTPUT_LEVEL_0V80        ((uint32_t)0x00000001U)
#define PWR_BKPLDO_VOLTAGE_OUTPUT_LEVEL_0V90        ((uint32_t)0x00000000U)
/**BKPLDO Output Voltage  bit offset **/
#define PWR_BKPLDO_VOLT_OUTPUT_LEVEL_OFFSET         ((uint32_t)0x0000000FU)
#define PWR_BKPLDO_LP_VOLT_OUTPUT_LEVEL_OFFSET      ((uint32_t)0x00000010U)

/**MR Output Voltage Enable bit **/
#define PWR_MR_LPVSELEN                             (PWR_SYSCTRL4_MR_LPVSELEN)

/** Sleep_mode_entry **/
#define PWR_SLEEPENTRY_WFI                          ((uint8_t)0x01U)
#define PWR_SLEEPENTRY_WFE                          ((uint8_t)0x02U)

/** STOP_mode_entry **/                 
#define PWR_STOPENTRY_WFI                           ((uint8_t)0x01U)
#define PWR_STOPENTRY_WFE                           ((uint8_t)0x02U)

/** STANDBY_mode_entry **/
#define PWR_STANDBYEntry_WFI                        ((uint8_t)0x01U)
#define PWR_STANDBYEntry_WFE                        ((uint8_t)0x02U)


/** Stop2 enable **/
#define PWR_STOP2EN                                 (PWR_M7CTRL2_STOP2EN)
#define PWR_PDSEN                                   (PWR_M7CTRL1_PDS)

/** wakeup pin enable **/
#define WAKEUP_PIN0EN                               (PWR_M7CTRLSTS_WKUP0EN)
#define WAKEUP_PIN1EN                               (PWR_M7CTRLSTS_WKUP1EN)
#define WAKEUP_PIN2EN                               (PWR_M7CTRLSTS_WKUP2EN)
#define WAKEUP_PIN3EN                               (PWR_M7CTRLSTS_WKUP3EN)
#define WAKEUP_PIN4EN                               (PWR_M7CTRLSTS_WKUP4EN)
#define WAKEUP_PIN5EN                               (PWR_M7CTRLSTS_WKUP5EN)

#define WAKEUP_RTCEN                                (PWR_M7CTRL2_RTC_ALMWUPEN)
#define WAKEUP_NRSTEN                               (PWR_M7CTRL2_NRST_WUPEN)

/** wakeup pin polarity config **/
#define WAKEUP_PIN0POL                              (PWR_M7CTRLSTS_WKUP0POL)
#define WAKEUP_PIN1POL                              (PWR_M7CTRLSTS_WKUP1POL)
#define WAKEUP_PIN2POL                              (PWR_M7CTRLSTS_WKUP2POL)
#define WAKEUP_PIN3POL                              (PWR_M7CTRLSTS_WKUP3POL)
#define WAKEUP_PIN4POL                              (PWR_M7CTRLSTS_WKUP4POL)
#define WAKEUP_PIN5POL                              (PWR_M7CTRLSTS_WKUP5POL)

/** PWR_Flag **/
#define PWR_FLAG_WKUP0                              (PWR_M7CTRLSTS_WKUP0F)
#define PWR_FLAG_WKUP1                              (PWR_M7CTRLSTS_WKUP1F)
#define PWR_FLAG_WKUP2                              (PWR_M7CTRLSTS_WKUP2F)
#define PWR_FLAG_WKUP3                              (PWR_M7CTRLSTS_WKUP3F)
#define PWR_FLAG_WKUP4                              (PWR_M7CTRLSTS_WKUP4F)
#define PWR_FLAG_WKUP5                              (PWR_M7CTRLSTS_WKUP5F)
#define PWR_FLAG_WKUPP                              (PWR_M7CTRLSTS_WKUP6F)
#define PWR_FLAG_STANDBY                            (PWR_M7CTRLSTS_SBF)
#define PWR_FLAG_VBAT                               (PWR_M7CTRLSTS_VBATF)

/** PWR_Flag clear **/
#define PWR_CLR_WKUPx                               (PWR_M7CTRL1_CWKUPF)
#define PWR_CLR_STANDBY                             (PWR_M7CTRL1_CSBF)
#define PWR_CLR_VBAT                                (PWR_M7CTRL1_CVBATF)


/** PWR_system control 1 **/
#define PWR_PVDEN                                    (PWR_SYSCTRL1_PVDEN)
#define PWR_AVDEN                                    (PWR_SYSCTRL1_AVDEN)
#define PWR_DBKPEN                                   (PWR_SYSCTRL1_DBKP)
#define PWR_BKPLDOEN                                 (PWR_SYSCTRL1_BKPLDOEN)

/** NRST_Digital Filtering   **/
#define PWR_NRST_DGF_CNT_MASK                        (PWR_SYSCTRL1_NRST_DGFCNT)
#define PWR_NRST_DGF_BP                              (PWR_SYSCTRL1_NRST_DGFBP)

#define PWR_NRST_DGF_CNT_BIT_OFFSET                  (16U)
/** PWR_SystemFlag **/
#define PWR_SYSFLAG_PVDO                             (PWR_SYSCTRLSTS_PVDO)
#define PWR_SYSFLAG_AVDO                             (PWR_SYSCTRLSTS_AVDO)
#define PWR_SYSFLAG_OTPRDY                           (PWR_SYSCTRLSTS_OTP_PWRRDY)
#define PWR_FLAG_DCDCBP                              (PWR_SYSCTRLSTS_DCDC_BPF)

/** PWR_system control 2 **/
#define PWR_MROFF_IN_STANDBY                         (PWR_SYSCTRL2_MR_STBOFFEN)

/** Module PWR Enable **/
#define GRAPHIC_GPU_PWRCTRL                         (PWR_IPMEMCTRL_GPU_PWREN)
#define GRAPHIC_LCDC_PWRCTRL                        (PWR_IPMEMCTRL_LCDC_PWREN)
#define GRAPHIC_JPEG_PWRCTRL                        (PWR_IPMEMCTRL_JPEG_PWREN)
#define GRAPHIC_DSI_PWRCTRL                         (PWR_IPMEMCTRL_DSI_PWREN)
#define GRAPHIC_DVP_PWRCTRL                         (PWR_IPMEMCTRL_DVP_PWREN)
#define HSC2_ETH2_PWRCTRL                           (PWR_IPMEMCTRL_ETH2_PWREN)
#define HSC2_USB2_PWRCTRL                           (PWR_IPMEMCTRL_USB2_PWREN)
#define HSC2_SDMMC2_PWRCTRL                         (PWR_IPMEMCTRL_SDMMC2_PWREN)
#define HSC1_ETH1_PWRCTRL                           (PWR_IPMEMCTRL_ETH1_PWREN)
#define HSC1_USB1_PWRCTRL                           (PWR_IPMEMCTRL_USB1_PWREN)
#define HSC1_SDMMC1_PWRCTRL                         (PWR_IPMEMCTRL_SDMMC1_PWREN)
#define FMAC_PWRCTRL                                (PWR_IPMEMCTRL_FMAC_PWREN)
#define ESC_PWRCTRL                                 (PWR_IPMEMCTRL_ESC_PWREN)

/** PWR Ready flag **/
#define FMAC_PWRRDY_FLAG                            (PWR_IPMEMCTRLSTS_FMAC_PWRRDY)
#define ESC_PWRRDY_FLAG                             (PWR_IPMEMCTRLSTS_ESC_PWRRDY)

/** MDMA PWR control **/
#define MDMA_POWER_ENABLE                           (PWR_MDMACTRL_MDMA_PWREN)
#define MDMA_FUNCTION_ENABLE                        (PWR_MDMACTRL_MDMA_FUCEN)
#define MDMA_ISOLATION_ENABLE                       (PWR_MDMACTRL_MDMA_ISNEN)
#define MDMA_POWER_RDY                              (PWR_MDMACTRL_MDMA_PRDY)
#define MDMA_PSWACK1                                (PWR_MDMACTRL_MDMA_PSWACK1)

/** ESC PWR control **/
#define ESC_POWER_ENABLE                            (PWR_ESCCTRL_ESC_PWREN)
#define ESC_FUNCTION_ENABLE                         (PWR_ESCCTRL_ESC_FUCEN)
#define ESC_ISOLATION_ENABLE                        (PWR_ESCCTRL_ESC_ISNEN)
#define ESC_POWER_RDY                               (PWR_ESCCTRL_ESC_PRDY)
#define ESC_PSWACK1                                 (PWR_ESCCTRL_ESC_PSWACK1)

/** SHRTIM PWR control **/
#define SHRTIM1_POWER_ENABLE                        (PWR_SHRTIMCTRL_SHR1_PWREN)
#define SHRTIM1_FUNCTION_ENABLE                     (PWR_SHRTIMCTRL_SHR1_FUCEN)
#define SHRTIM1_ISOLATION_ENABLE                    (PWR_SHRTIMCTRL_SHR1_ISNEN)
#define SHRTIM1_POWER_RDY                           (PWR_SHRTIMCTRL_SHR1_PRDY)
#define SHRTIM1_PSWACK1                             (PWR_SHRTIMCTRL_SHR1_PSWACK1)

#define SHRTIM2_POWER_ENABLE                        (PWR_SHRTIMCTRL_SHR2_PWREN)
#define SHRTIM2_FUNCTION_ENABLE                     (PWR_SHRTIMCTRL_SHR2_FUCEN)
#define SHRTIM2_ISOLATION_ENABLE                    (PWR_SHRTIMCTRL_SHR2_ISNEN)
#define SHRTIM2_POWER_RDY                           (PWR_SHRTIMCTRL_SHR2_PRDY)
#define SHRTIM2_PSWACK1                             (PWR_SHRTIMCTRL_SHR2_PSWACK1)

#define SHRTIMA_POWER_ENABLE                        (PWR_SHRTIMCTRL_SHRA_PWREN)
#define SHRTIMA_FUNCTION_ENABLE                     (PWR_SHRTIMCTRL_SHRA_FUCEN)
#define SHRTIMA_ISOLATION_ENABLE                    (PWR_SHRTIMCTRL_SHRA_ISNEN)
#define SHRTIMA_POWER_RDY                           (PWR_SHRTIMCTRL_SHRA_PRDY)
#define SHRTIMA_PSWACK1                             (PWR_SHRTIMCTRL_SHRA_PSWACK1)

/** OPTC_POWER  control **/
#define OPTC_POWER_ENTER_MODE_MASK                  (0x000000003U)
#define OPTC_POWER_ENTER_RUN_MODE                   (0x000000000U)
#define OPTC_POWER_ENTER_DEEPSTANDBY_MODE           (0x000000001U)
#define OPTC_POWER_ENTER_STANDBY_MODE               (0x000000002U)



/** SYSTEM MEMORY Low Power mode in Stop2 mode **/
#define SYSTEM_MEMORY_STATUS_MASK                   (0x000000003U)
#define SYSTEM_MEMORY_STATUS_PD                     (0x000000000U)
#define SYSTEM_MEMORY_STATUS_RETENTION_1            (0x000000001U)
#define SYSTEM_MEMORY_STATUS_RETENTION_2            (0x000000002U)

#define SYSTEM_MEMORY_AXISRAM_BITOFFSET             (0x00000000DU)

/** ALL SYSTEM MEMORY Low Power mode in Stop0 mode **/
#define ALL_SYSTEM_MEMORY_STATUS_MASK               (PWR_SYSMEMLPCTRL_MEM_PGSTP0EN | PWR_SYSMEMLPCTRL_MEM_RETSTP0EN)
#define ALL_SYSTEM_MEMORY_STATUS_CHIP_DISABLE       (0x000000000U)
#define ALL_SYSTEM_MEMORY_STATUS_PRECHARGE          (PWR_SYSMEMLPCTRL_MEM_RETSTP0EN)
#define ALL_SYSTEM_MEMORY_STATUS_RETENTION_1        (PWR_SYSMEMLPCTRL_MEM_PGSTP0EN | PWR_SYSMEMLPCTRL_MEM_RETSTP0EN)



typedef enum{
    GRAPHIC_Domain = 0,
    HSC1_Domain    = 1,
    HSC2_Domain    = 2
}DOMAIN_Type;

typedef enum{
    Power_SHRTIM1   = 0,
    Power_SHRTIM2   = 1,
}SHRTIM_PowerType;

/** PWR wakeup PIN polarity enmu definition **/
typedef enum
{
    POL_HIGH = 0x0,
    POL_LOW = 0x1,
} WAKEUP_PIN_POL;



/** PWR_Exported_Functions **/ 

void PWR_DeInit_Sys(void);
void PWR_DeInit_CM7(void);
void PWR_DeInit_CM4(void);

void PWR_BackupAccessEnable(FunctionalState Cmd);
void PWR_AvdEnable(FunctionalState Cmd);
void PWR_PvdEnable(FunctionalState Cmd);
void PWR_BorEnable(FunctionalState Cmd);
void PWR_PVDLevelConfig(uint32_t level);
void PWR_AVDLevelConfig(uint32_t level);
void PWR_EnableMRInStandby(FunctionalState Cmd);
void PWR_EnableBKPLDO(FunctionalState Cmd);

void PWR_ConfigDigitalFilterOnNRST(uint32_t cycle_cnt, FunctionalState Cmd);

void PWR_EnableLPMRVoltageOutput(FunctionalState Cmd);
void PWR_VDDDPORLevelConfig(SYSTEM_POWER_TYPE mode, uint32_t level);
void PWR_DCDCPORLevelConfig(SYSTEM_POWER_TYPE mode, uint32_t level);

void PWR_MLDOOutputVoltageConfig(SYSTEM_POWER_TYPE mode, uint32_t level);
void PWR_DCDCOutputVoltageConfig(SYSTEM_POWER_TYPE mode, uint32_t level);
void PWR_BKPLDOOutputVoltageConfig(SYSTEM_POWER_TYPE mode, uint32_t level);

void PWR_MDMA_DomainEnable(FunctionalState Cmd);
void PWR_SHRTIM_DomainEnable(SHRTIM_PowerType shrtimx, FunctionalState Cmd);
void PWR_MoudlePowerEnable(uint32_t module, FunctionalState Cmd);

void PWR_EnableBKPSRAMRetainInStandbyMode(FunctionalState Cmd);
void PWR_EnableBKPSRAMRetainInVbatMode(FunctionalState Cmd);
void PWR_WakeUpPinEnable(uint32_t pin, FunctionalState Cmd);
void PWR_WakeUpPinPolarity(uint32_t pin, WAKEUP_PIN_POL polarity);
void PWR_WakeUpRTCEnable(FunctionalState Cmd);
void PWR_WakeUpNRSTEnable(FunctionalState Cmd);

FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
FlagStatus PWR_GetSystemFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);

void PWR_EnterSLEEPMode(uint8_t SLEEPONEXIT, uint8_t PWR_SLEEPEntry);
void PWR_EnterSTOP0Mode(uint8_t PWR_STOPEntry);
void PWR_EnterSTOP2Mode(uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);

void PWR_EnableOPTC_LPMode(SYSTEM_OPTC_STATUS ChipStatus, uint32_t OPTC_Mode, FunctionalState Cmd);
void PWR_EnableTCMPiece(uint32_t PieceIndex, FunctionalState Cmd);
void PWR_TCMModeSelInSTOP2(uint32_t PieceIndex, uint32_t Mode);

void PWR_SystemMemoryModeSelInSTOP2(SYSTEM_MEMORY_TYPE SysMemoryType, uint32_t Mode);
void PWR_SystemMemoryModeSelInSTOP0(uint32_t Mode);
void PWR_EnableSystemMemory(SYSTEM_MEMORY_TYPE SysMemoryType, FunctionalState Cmd);
     
#ifdef __cplusplus
}
#endif

#endif //__N32H76X_78X_PWR_H__

