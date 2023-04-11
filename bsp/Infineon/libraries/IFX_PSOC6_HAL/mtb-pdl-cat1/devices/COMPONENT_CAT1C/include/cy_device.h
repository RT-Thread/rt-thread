/***************************************************************************//**
* \file cy_device.h
* \version 2.0
*
* This file specifies the structure for core and peripheral block HW base
* addresses, versions, and parameters.
*
********************************************************************************/
#ifndef CY_DEVICE_H_
#define CY_DEVICE_H_

#include <stdint.h>
#include <stddef.h>
#include "cy_utils.h"
#include "cy_device_headers.h"
#include "startup_cat1c.h"
#include "ip/cyip_cpuss.h"

CY_MISRA_FP_BLOCK_START('MISRA C-2012 Rule 8.6', 1, \
'Checked manually. The definition is a part of linker script.');

/* Device descriptor type */
typedef struct
{
    /* Base HW addresses */
    uint32_t hsiomBase;
    uint32_t gpioBase;

    /* IP block versions: [7:4] major, [3:0] minor */
    uint8_t  dwVersion;

    /* Parameters */
    uint8_t  cpussDw0ChNr;
    uint8_t  cpussDw1ChNr;
    uint8_t  epMonitorNr;

    /* Peripheral register offsets */

   /* DW registers */
    uint16_t dwChOffset;
    uint16_t dwChSize;
    uint8_t  dwChCtlPrioPos;
    uint8_t  dwChCtlPreemptablePos;
    uint8_t  dwStatusChIdxPos;
    uint32_t dwStatusChIdxMsk;

    uint8_t  tcpwmCC1Present;
    uint8_t  tcpwmAMCPresent;
    uint8_t  tcpwmSMCPrecent;

} cy_stc_device_t;

void Cy_PDL_Init(const cy_stc_device_t * device);

/* Pointer to device configuration structure */
#define CY_DEVICE_CFG                   (&cy_deviceIpBlockCfg)

/*******************************************************************************
*                   Global Variables
*******************************************************************************/

extern const cy_stc_device_t   cy_deviceIpBlockCfg;
extern const cy_stc_device_t* cy_device;

/*******************************************************************************
*                   Global Extern Functions
*******************************************************************************/

#if defined(__ARMCC_VERSION)
#define interrupt_type __attribute__((interrupt))
#elif defined (__GNUC__)
#define interrupt_type __attribute__((interrupt))
#elif defined (__ICCARM__)
#define interrupt_type __irq
#else
    #error "An unsupported toolchain"
#endif  /* (__ARMCC_VERSION) */

/*******************************************************************************
*               Macro Definitions
*******************************************************************************/
/*******************************************************************************
*               Register Access Helper Macros
*******************************************************************************/
#define CY_DEVICE_CAT1C            /* Device Category */
#define CY_CRYPTO_V1                        (0U) /* CAT1C devices have only mxcrypto_v2 IP */

/*******************************************************************************
*                System Level
*******************************************************************************/
#define ENABLE_CM7_INSTRUCTION_CACHE
//#define ENABLE_CM7_DATA_CACHE

/*******************************************************************************
*                CRYPTO
*******************************************************************************/

/* The CRYPTO internal-memory buffer-size in 32-bit words. */
#define CY_CRYPTO_MEM_BUFF_SIZE_U32         (2048U)

/*******************************************************************************
*                SYSLIB
*******************************************************************************/
#if defined(CORE_NAME_CM7_0) || defined(CORE_NAME_CM7_1)
#define CY_SYSLIB_DELAY_CALIBRATION_FACTOR    2U
#else
#define CY_SYSLIB_DELAY_CALIBRATION_FACTOR    1U
#endif

/*******************************************************************************
*                SRSS
*******************************************************************************/

#define CY_SRSS_NUM_CLKPATH                 SRSS_NUM_CLKPATH
#define CY_SRSS_NUM_PLL                     SRSS_NUM_TOTAL_PLL
#define CY_SRSS_NUM_PLL200M                 SRSS_NUM_PLL
#define CY_SRSS_NUM_PLL400M                 SRSS_NUM_PLL400M
#define CY_SRSS_NUM_HFROOT                  SRSS_NUM_HFROOT
#define CY_SRSS_ECO_PRESENT                 SRSS_ECO_PRESENT
#define CY_SRSS_FLL_PRESENT                 1
#define CY_SRSS_PLL_PRESENT                 SRSS_NUM_PLL
#define CY_SRSS_PLL400M_PRESENT             1
#define CY_SRSS_ALTHF_PRESENT               SRSS_ALTHF_PRESENT

#define CY_SRSS_ILO_COUNT                   2

/** HF PATH # used for PERI PCLK */
#define CY_SYSCLK_CLK_PERI_HF_PATH_NUM     2U

/** HF PATH # used for MEM CLK */
#define CY_SYSCLK_CLK_MEM_HF_PATH_NUM     0U


/** HF PATH # used for Core */
#ifdef CORE_NAME_CM0P_0
#define CY_SYSCLK_CLK_CORE_HF_PATH_NUM     0U
#else
#define CY_SYSCLK_CLK_CORE_HF_PATH_NUM     1U
#endif

/** HF PATH # used for CLOCK FAST */
#define CY_SYSCLK_CLK_FAST_HF_NUM          1U

/* HF PATH # Max Allowed Frequencies */
#define CY_SYSCLK_HF_MAX_FREQ(hfNum)       (350000000U)

/** FLL Max Frequency */
#define  CY_SYSCLK_FLL_MAX_OUTPUT_FREQ     (100000000UL)

/* Technology Independant Register set */
#define SRSS_CLK_DSI_SELECT                 (((SRSS_Type *) SRSS)->CLK_DSI_SELECT)
#define SRSS_CLK_OUTPUT_FAST                (((SRSS_Type *) SRSS)->CLK_OUTPUT_FAST)
#define SRSS_CLK_OUTPUT_SLOW                (((SRSS_Type *) SRSS)->CLK_OUTPUT_SLOW)
#define SRSS_CLK_CAL_CNT1                   (((SRSS_Type *) SRSS)->CLK_CAL_CNT1)
#define SRSS_CLK_CAL_CNT2                   (((SRSS_Type *) SRSS)->CLK_CAL_CNT2)
#define SRSS_SRSS_INTR                      (((SRSS_Type *) SRSS)->SRSS_INTR)
#define SRSS_SRSS_INTR_SET                  (((SRSS_Type *) SRSS)->SRSS_INTR_SET)
#define SRSS_SRSS_INTR_MASK                 (((SRSS_Type *) SRSS)->SRSS_INTR_MASK)
#define SRSS_SRSS_INTR_MASKED               (((SRSS_Type *) SRSS)->SRSS_INTR_MASKED)
#define SRSS_PWR_CTL                        (((SRSS_Type *) SRSS)->PWR_CTL)
#define SRSS_PWR_CTL2                       (((SRSS_Type *) SRSS)->PWR_CTL2)
#define SRSS_PWR_HIBERNATE                  (((SRSS_Type *) SRSS)->PWR_HIBERNATE)
#define SRSS_PWR_BUCK_CTL                   (((SRSS_Type *) SRSS)->PWR_BUCK_CTL)
#define SRSS_PWR_BUCK_CTL2                  (((SRSS_Type *) SRSS)->PWR_BUCK_CTL2)
#define SRSS_PWR_SSV_CTL                    (((SRSS_Type *) SRSS)->PWR_SSV_CTL)
#define SRSS_PWR_SSV_STATUS                 (((SRSS_Type *) SRSS)->PWR_SSV_STATUS)
#define SRSS_PWR_LVD_CTL                    (((SRSS_Type *) SRSS)->PWR_LVD_CTL)
#define SRSS_PWR_LVD_CTL2                   (((SRSS_Type *) SRSS)->PWR_LVD_CTL2)
#define SRSS_PWR_REGHC_CTL                  (((SRSS_Type *) SRSS)->PWR_REGHC_CTL)
#define SRSS_PWR_REGHC_STATUS               (((SRSS_Type *) SRSS)->PWR_REGHC_STATUS)
#define SRSS_PWR_REGHC_CTL2                 (((SRSS_Type *) SRSS)->PWR_REGHC_CTL2)
#define SRSS_PWR_REGHC_CTL4                 (((SRSS_Type *) SRSS)->PWR_REGHC_CTL4)
#define SRSS_PWR_HIB_DATA                   (((SRSS_Type *) SRSS)->PWR_HIB_DATA)
#define SRSS_PWR_PMIC_CTL                   (((SRSS_Type *) SRSS)->PWR_PMIC_CTL)
#define SRSS_PWR_PMIC_STATUS                (((SRSS_Type *) SRSS)->PWR_PMIC_STATUS)
#define SRSS_PWR_PMIC_CTL2                  (((SRSS_Type *) SRSS)->PWR_PMIC_CTL2)
#define SRSS_PWR_PMIC_CTL4                  (((SRSS_Type *) SRSS)->PWR_PMIC_CTL4)
#define SRSS_CLK_PATH_SELECT                (((SRSS_Type *) SRSS)->CLK_PATH_SELECT)
#define SRSS_CLK_ROOT_SELECT                (((SRSS_Type *) SRSS)->CLK_ROOT_SELECT)
#define SRSS_CLK_DIRECT_SELECT              (((SRSS_Type *) SRSS)->CLK_DIRECT_SELECT)
#define SRSS_CLK_ECO_STATUS                 (((SRSS_Type *) SRSS)->CLK_ECO_STATUS)
#define SRSS_CLK_ILO_CONFIG                 (((SRSS_Type *) SRSS)->CLK_ILO0_CONFIG) /* BWC */
#define SRSS_CLK_ILO0_CONFIG                (((SRSS_Type *) SRSS)->CLK_ILO0_CONFIG)
#define SRSS_CLK_ILO1_CONFIG                (((SRSS_Type *) SRSS)->CLK_ILO1_CONFIG)

#define SRSS_CLK_ILO_CONFIG_ENABLE_Msk      SRSS_CLK_ILO0_CONFIG_ENABLE_Msk /* BWC */

#define SRSS_CLK_TRIM_ILO_CTL               (((SRSS_Type *) SRSS)->CLK_TRIM_ILO_CTL)
#define SRSS_CLK_PILO_CONFIG                (((SRSS_Type *) SRSS)->CLK_PILO_CONFIG)
#define SRSS_CLK_ECO_CONFIG                 (((SRSS_Type *) SRSS)->CLK_ECO_CONFIG)
#define SRSS_CLK_ECO_CONFIG2                 (((SRSS_Type *) SRSS)->CLK_ECO_CONFIG2)
#define SRSS_CLK_MFO_CONFIG                 (((SRSS_Type *) SRSS)->CLK_MFO_CONFIG)
#define SRSS_CLK_IHO_CONFIG                 (((SRSS_Type *) SRSS)->CLK_IHO_CONFIG)
#define SRSS_CLK_ALTHF_CTL                  (((SRSS_Type *) SRSS)->CLK_ALTHF_CTL)

#define SRSS_CLK_ILO0_CONFIG                 (((SRSS_Type *) SRSS)->CLK_ILO0_CONFIG)
#define SRSS_CLK_ILO1_CONFIG                 (((SRSS_Type *) SRSS)->CLK_ILO1_CONFIG)

#define SRSS_CSV_HF                         (((SRSS_Type *) SRSS)->CSV_HF)
#define SRSS_CLK_SELECT                     (((SRSS_Type *) SRSS)->CLK_SELECT)
#define SRSS_CLK_TIMER_CTL                  (((SRSS_Type *) SRSS)->CLK_TIMER_CTL)
#define SRSS_CLK_IMO_CONFIG                 (((SRSS_Type *) SRSS)->CLK_IMO_CONFIG)
#define SRSS_CLK_ECO_PRESCALE               (((SRSS_Type *) SRSS)->CLK_ECO_PRESCALE)
#define SRSS_CLK_MF_SELECT                  (((SRSS_Type *) SRSS)->CLK_MF_SELECT)
#define SRSS_CSV_REF_SEL                    (((SRSS_Type *) SRSS)->CSV_REF_SEL)
#define SRSS_CSV_REF                        (((SRSS_Type *) SRSS)->CSV_REF)
#define SRSS_CSV_LF                         (((SRSS_Type *) SRSS)->CSV_LF)
#define SRSS_CSV_ILO                        (((SRSS_Type *) SRSS)->CSV_ILO)
#define SRSS_RES_CAUSE                      (((SRSS_Type *) SRSS)->RES_CAUSE)
#define SRSS_RES_CAUSE2                     (((SRSS_Type *) SRSS)->RES_CAUSE2)
#define SRSS_RES_CAUSE_EXTEND               (((SRSS_Type *) SRSS)->RES_CAUSE_EXTEND)
#define SRSS_CLK_LP_PLL                     (((SRSS_Type *) SRSS)->CLK_LP_PLL)
#define SRSS_CLK_IHO                        (((SRSS_Type *) SRSS)->CLK_IHO)
#define SRSS_TST_XRES_SECURE                (((SRSS_Type *) SRSS)->TST_XRES_SECURE)
#define SRSS_RES_PXRES_CTL                  (((SRSS_Type *) SRSS)->RES_PXRES_CTL)

#define SRSS_CLK_FLL_CONFIG                 (((SRSS_Type *) SRSS)->CLK_FLL_CONFIG)
#define SRSS_CLK_FLL_CONFIG2                (((SRSS_Type *) SRSS)->CLK_FLL_CONFIG2)
#define SRSS_CLK_FLL_CONFIG3                (((SRSS_Type *) SRSS)->CLK_FLL_CONFIG3)
#define SRSS_CLK_FLL_CONFIG4                (((SRSS_Type *) SRSS)->CLK_FLL_CONFIG4)
#define SRSS_CLK_FLL_STATUS                 (((SRSS_Type *) SRSS)->CLK_FLL_STATUS)

#define SRSS_PWR_LVD_STATUS                 (((SRSS_Type *) SRSS)->PWR_LVD_STATUS)
#define SRSS_PWR_LVD_STATUS2                 (((SRSS_Type *) SRSS)->PWR_LVD_STATUS2)

#define SRSS_SRSS_INTR_CFG                  (((SRSS_Type *) SRSS)->SRSS_AINTR_CFG)

#define SRSS_PWR_HIB_WAKE_CTL               (((SRSS_Type *) SRSS)->PWR_HIB_WAKE_CTL)
#define SRSS_PWR_HIB_WAKE_CTL2              (((SRSS_Type *) SRSS)->PWR_HIB_WAKE_CTL2)
#define SRSS_PWR_HIB_WAKE_CAUSE             (((SRSS_Type *) SRSS)->PWR_HIB_WAKE_CAUSE)
#define SRSS_RES_SOFT_CTL                   (((SRSS_Type *) SRSS)->RES_SOFT_CTL)

#define SRSS_CLK_PLL_CONFIG                 (((SRSS_Type *) SRSS)->CLK_PLL_CONFIG)
#define SRSS_CLK_PLL_STATUS                 (((SRSS_Type *) SRSS)->CLK_PLL_STATUS)

#define SRSS_FLL_PATH_NUM         (0UL)
#define SRSS_PLL_400M_0_PATH_NUM  (1UL)
#define SRSS_PLL_400M_1_PATH_NUM  (2UL)
#define SRSS_PLL_200M_0_PATH_NUM  (3UL)
#define SRSS_PLL_200M_1_PATH_NUM  (4UL)

#define SRSS_PLL400M_FRAC_BIT_COUNT (24ULL)

#if (CY_IP_MXS40SRSS_VERSION >= 3)
#define SRSS_CLK_PLL_400M_CONFIG(pllNum)                 (((SRSS_Type *) SRSS)->CLK_PLL400M[pllNum].CONFIG)
#define SRSS_CLK_PLL_400M_CONFIG2(pllNum)                 (((SRSS_Type *) SRSS)->CLK_PLL400M[pllNum].CONFIG2)
#define SRSS_CLK_PLL_400M_CONFIG3(pllNum)                 (((SRSS_Type *) SRSS)->CLK_PLL400M[pllNum].CONFIG3)
#define SRSS_CLK_PLL_400M_STATUS(pllNum)                 (((SRSS_Type *) SRSS)->CLK_PLL400M[pllNum].STATUS)
#endif


#define SRSS_WDT_CTL                        (((WDT_Type*) &SRSS->WDT_STRUCT)->CTL)
#define SRSS_WDT_LOWER_LIMIT                (((WDT_Type*) &SRSS->WDT_STRUCT)->LOWER_LIMIT)
#define SRSS_WDT_UPPER_LIMIT                (((WDT_Type*) &SRSS->WDT_STRUCT)->UPPER_LIMIT)
#define SRSS_WDT_WARN_LIMIT                 (((WDT_Type*) &SRSS->WDT_STRUCT)->WARN_LIMIT)
#define SRSS_WDT_CONFIG                     (((WDT_Type*) &SRSS->WDT_STRUCT)->CONFIG)
#define SRSS_WDT_CNT                        (((WDT_Type*) &SRSS->WDT_STRUCT)->CNT)
#define SRSS_WDT_LOCK                       (((WDT_Type*) &SRSS->WDT_STRUCT)->LOCK)
#define SRSS_WDT_SERVICE                    (((WDT_Type*) &SRSS->WDT_STRUCT)->SERVICE)
#define SRSS_WDT_INTR                       (((WDT_Type*) &SRSS->WDT_STRUCT)->INTR)
#define SRSS_WDT_INTR_SET                   (((WDT_Type*) &SRSS->WDT_STRUCT)->INTR_SET)
#define SRSS_WDT_INTR_MASK                  (((WDT_Type*) &SRSS->WDT_STRUCT)->INTR_MASK)
#define SRSS_WDT_INTR_MASKED                (((WDT_Type*) &SRSS->WDT_STRUCT)->INTR_MASKED)



#define SRSS_TST_DDFT_FAST_CTL_REG          (*(volatile uint32_t *) 0x40261104U)
#define SRSS_TST_DDFT_SLOW_CTL_REG          (*(volatile uint32_t *) 0x40261108U)

#define SRSS_TST_DDFT_SLOW_CTL_MASK         (0x00001F1EU)
#define SRSS_TST_DDFT_FAST_CTL_MASK         (62U)


/*******************************************************************************
*                BACKUP
*******************************************************************************/

#define BACKUP_PMIC_CTL                     (((BACKUP_Type *) BACKUP)->PMIC_CTL)
#define BACKUP_CTL                          (((BACKUP_Type *) BACKUP)->CTL)
#define BACKUP_RTC_TIME                     (((BACKUP_Type *) BACKUP)->RTC_TIME)
#define BACKUP_RTC_DATE                     (((BACKUP_Type *) BACKUP)->RTC_DATE)
#define BACKUP_RTC_RW                       (((BACKUP_Type *) BACKUP)->RTC_RW)
#define BACKUP_CAL_CTL                      (((BACKUP_Type *) BACKUP)->CAL_CTL)
#define BACKUP_ALM1_TIME                    (((BACKUP_Type *) BACKUP)->ALM1_TIME)
#define BACKUP_ALM1_DATE                    (((BACKUP_Type *) BACKUP)->ALM1_DATE)
#define BACKUP_ALM2_TIME                    (((BACKUP_Type *) BACKUP)->ALM2_TIME)
#define BACKUP_ALM2_DATE                    (((BACKUP_Type *) BACKUP)->ALM2_DATE)
#define BACKUP_STATUS                       (((BACKUP_Type *) BACKUP)->STATUS)
#define BACKUP_INTR                         (((BACKUP_Type *) BACKUP)->INTR)
#define BACKUP_INTR_SET                     (((BACKUP_Type *) BACKUP)->INTR_SET)
#define BACKUP_INTR_MASK                    (((BACKUP_Type *) BACKUP)->INTR_MASK)
#define BACKUP_INTR_MASKED                  (((BACKUP_Type *) BACKUP)->INTR_MASKED)
#define BACKUP_RESET                        (((BACKUP_Type *) BACKUP)->RESET)
#define BACKUP_BREG                         (((BACKUP_Type *) BACKUP)->BREG)


#define CY_SRSS_BACKUP_NUM_BREG             SRSS_BACKUP_NUM_BREG


/*******************************************************************************
*                CANFD
*******************************************************************************/

#define CANFD_CTL(base)                           (((CANFD_Type *)(base))->CTL)
#define CANFD_STATUS(base)                        (((CANFD_Type *)(base))->STATUS)
#define CANFD_NBTP(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.NBTP)
#define CANFD_IR(base, chan)                      (((CANFD_Type *)(base))->CH[chan].M_TTCAN.IR)
#define CANFD_IE(base, chan)                      (((CANFD_Type *)(base))->CH[chan].M_TTCAN.IE)
#define CANFD_ILS(base, chan)                     (((CANFD_Type *)(base))->CH[chan].M_TTCAN.ILS)
#define CANFD_ILE(base, chan)                     (((CANFD_Type *)(base))->CH[chan].M_TTCAN.ILE)
#define CANFD_CCCR(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.CCCR)
#define CANFD_SIDFC(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.SIDFC)
#define CANFD_XIDFC(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.XIDFC)
#define CANFD_XIDAM(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.XIDAM)
#define CANFD_RXESC(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXESC)
#define CANFD_RXF0C(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF0C)
#define CANFD_RXF1C(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF1C)
#define CANFD_RXFTOP_CTL(base, chan)              (((CANFD_Type *)(base))->CH[chan].RXFTOP_CTL)
#define CANFD_RXBC(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXBC)
#define CANFD_TXESC(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXESC)
#define CANFD_TXEFC(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXEFC)
#define CANFD_TXBC(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBC)
#define CANFD_DBTP(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.DBTP)
#define CANFD_TDCR(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TDCR)
#define CANFD_GFC(base, chan)                     (((CANFD_Type *)(base))->CH[chan].M_TTCAN.GFC)
#define CANFD_TXBRP(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBRP)
#define CANFD_TXBAR(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBAR)
#define CANFD_TXBCR(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBCR)
#define CANFD_TXBTO(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBTO)
#define CANFD_TXBCF(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBCF)
#define CANFD_TXBTIE(base, chan)                  (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBTIE)
#define CANFD_TXBCIE(base, chan)                  (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TXBCIE)
#define CANFD_NDAT1(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.NDAT1)
#define CANFD_NDAT2(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.NDAT2)
#define CANFD_RXF0S(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF0S)
#define CANFD_RXFTOP0_DATA(base, chan)            (((CANFD_Type *)(base))->CH[chan].RXFTOP0_DATA)
#define CANFD_RXFTOP1_DATA(base, chan)            (((CANFD_Type *)(base))->CH[chan].RXFTOP1_DATA)
#define CANFD_RXF0A(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF0A)
#define CANFD_RXF1S(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF1S)
#define CANFD_RXF1A(base, chan)                   (((CANFD_Type *)(base))->CH[chan].M_TTCAN.RXF1A)
#define CANFD_PSR(base, chan)                     (((CANFD_Type *)(base))->CH[chan].M_TTCAN.PSR)
#define CANFD_TEST(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.TEST)
#define CANFD_CREL(base, chan)                    (((CANFD_Type *)(base))->CH[chan].M_TTCAN.CREL)

#define CY_CANFD_CHANNELS_NUM                     (0x1UL)


/*******************************************************************************
*                FLASHC
*******************************************************************************/
#if ((CPUSS_FLASHC_PRESENT == 1) && (CPUSS_FLASHC_ECT == 1))
#define CY_IP_MXFLASHC_VERSION_ECT
#endif

#define FLASHC_FLASH_CTL             (((FLASHC_Type *)(FLASHC))->FLASH_CTL)
#define FLASHC_FLASH_PWR_CTL         (((FLASHC_Type *)(FLASHC))->FLASH_PWR_CTL)
#define FLASHC_FLASH_CMD             (((FLASHC_Type *)(FLASHC))->FLASH_CMD)
#define FLASHC_ECC_CTL               (((FLASHC_Type *)(FLASHC))->ECC_CTL)
#define FLASHC_FM_SRAM_ECC_CTL0      (((FLASHC_Type *)(FLASHC))->FM_SRAM_ECC_CTL0)
#define FLASHC_FM_SRAM_ECC_CTL1      (((FLASHC_Type *)(FLASHC))->FM_SRAM_ECC_CTL1)
#define FLASHC_FM_SRAM_ECC_CTL2      (((FLASHC_Type *)(FLASHC))->FM_SRAM_ECC_CTL2)
#define FLASHC_FM_SRAM_ECC_CTL3      (((FLASHC_Type *)(FLASHC))->FM_SRAM_ECC_CTL3)
#define FLASHC_CM0_CA_CTL0           (((FLASHC_Type *)(FLASHC))->CM0_CA_CTL0)
#define FLASHC_CM0_CA_CTL1           (((FLASHC_Type *)(FLASHC))->CM0_CA_CTL1)
#define FLASHC_CM0_CA_CTL2           (((FLASHC_Type *)(FLASHC))->CM0_CA_CTL2)
#define FLASHC_CM0_CA_STATUS0        (((FLASHC_Type *)(FLASHC))->CM0_CA_STATUS0)
#define FLASHC_CM0_CA_STATUS1        (((FLASHC_Type *)(FLASHC))->CM0_CA_STATUS1)
#define FLASHC_CM0_CA_STATUS2        (((FLASHC_Type *)(FLASHC))->CM0_CA_STATUS2)
#define FLASHC_CM0_STATUS            (((FLASHC_Type *)(FLASHC))->CM0_STATUS)
#define FLASHC_CM7_0_STATUS          (((FLASHC_Type *)(FLASHC))->CM7_0_STATUS)
#define FLASHC_CM7_1_STATUS          (((FLASHC_Type *)(FLASHC))->CM7_1_STATUS)
#define FLASHC_CRYPTO_BUFF_CTL       (((FLASHC_Type *)(FLASHC))->CRYPTO_BUFF_CTL)
#define FLASHC_DW0_BUFF_CTL          (((FLASHC_Type *)(FLASHC))->DW0_BUFF_CTL)
#define FLASHC_DW1_BUFF_CTL          (((FLASHC_Type *)(FLASHC))->DW1_BUFF_CTL)
#define FLASHC_DMAC_BUFF_CTL         (((FLASHC_Type *)(FLASHC))->DMAC_BUFF_CTL)
#define FLASHC_SLOW0_MS_BUFF_CTL     (((FLASHC_Type *)(FLASHC))->SLOW0_MS_BUFF_CTL)
#define FLASHC_SLOW1_MS_BUFF_CTL     (((FLASHC_Type *)(FLASHC))->SLOW1_MS_BUFF_CTL)

/* FLASH Memory  */
#define FLASHC_FM_CTL_ECT_WORK_FLASH_SAFETY (((FLASHC_FM_CTL_ECT_Type *)(FLASHC_FM_CTL_ECT))->WORK_FLASH_SAFETY)
#define FLASHC_FM_CTL_ECT_MAIN_FLASH_SAFETY (((FLASHC_FM_CTL_ECT_Type *)(FLASHC_FM_CTL_ECT))->MAIN_FLASH_SAFETY)
#define FLASHC_FM_CTL_ECT_FLASH_STATUS (((FLASHC_FM_CTL_ECT_Type *)(FLASHC_FM_CTL_ECT))->STATUS)

/*******************************************************************************
*                SFLASH
*******************************************************************************/

#define SFLASH_DIE_YEAR                     (((SFLASH_V1_Type *) SFLASH)->DIE_YEAR)
#define SFLASH_DIE_MINOR                    (((SFLASH_V1_Type *) SFLASH)->DIE_MINOR)
#define SFLASH_DIE_SORT                     (((SFLASH_V1_Type *) SFLASH)->DIE_SORT)
#define SFLASH_DIE_Y                        (((SFLASH_V1_Type *) SFLASH)->DIE_Y)
#define SFLASH_DIE_X                        (((SFLASH_V1_Type *) SFLASH)->DIE_X)
#define SFLASH_DIE_WAFER                    (((SFLASH_V1_Type *) SFLASH)->DIE_WAFER)
#define SFLASH_DIE_LOT(val)                 (((SFLASH_V1_Type *) SFLASH)->DIE_LOT[(val)])
#define SFLASH_FAMILY_ID                    (((SFLASH_V1_Type *) SFLASH)->FAMILY_ID)
#define SFLASH_SI_REVISION_ID               (((SFLASH_V1_Type *) SFLASH)->SI_REVISION_ID)
#define SFLASH_PWR_TRIM_WAKE_CTL            (((SFLASH_V1_Type *) SFLASH)->PWR_TRIM_WAKE_CTL)
#define SFLASH_LDO_0P9V_TRIM                (((SFLASH_V1_Type *) SFLASH)->LDO_0P9V_TRIM)
#define SFLASH_LDO_1P1V_TRIM                (((SFLASH_V1_Type *) SFLASH)->LDO_1P1V_TRIM)
#define SFLASH_BLE_DEVICE_ADDRESS           (((SFLASH_V1_Type *) SFLASH)->BLE_DEVICE_ADDRESS)
#define SFLASH_SILICON_ID                   (((SFLASH_V1_Type *) SFLASH)->SILICON_ID)
#define SFLASH_SINGLE_CORE                  (*(volatile uint8_t *) (SFLASH_BASE + 0xBU))


#define SFLASH_CPUSS_TRIM_ROM_CTL_LP        (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_ROM_CTL_LP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_LP        (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_RAM_CTL_LP)
#define SFLASH_CPUSS_TRIM_ROM_CTL_ULP       (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_ROM_CTL_ULP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_ULP       (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_RAM_CTL_ULP)
#define SFLASH_CPUSS_TRIM_ROM_CTL_HALF_LP   (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_ROM_CTL_HALF_LP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_HALF_LP   (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_RAM_CTL_HALF_LP)
#define SFLASH_CPUSS_TRIM_ROM_CTL_HALF_ULP  (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_ROM_CTL_HALF_ULP)
#define SFLASH_CPUSS_TRIM_RAM_CTL_HALF_ULP  (((SFLASH_V1_Type *) SFLASH)->CPUSS_TRIM_RAM_CTL_HALF_ULP)


#define SFLASH_CSD0_ADC_VREF0_TRIM          (((SFLASH_V1_Type *) SFLASH)->CSDV2_CSD0_ADC_VREF0)
#define SFLASH_CSD0_ADC_VREF1_TRIM          (((SFLASH_V1_Type *) SFLASH)->CSDV2_CSD0_ADC_VREF1)
#define SFLASH_CSD0_ADC_VREF2_TRIM          (((SFLASH_V1_Type *) SFLASH)->CSDV2_CSD0_ADC_VREF2)


/*******************************************************************************
*                CPUSS
*******************************************************************************/

/* ARM core registers */
#define SYSTICK_CTRL                        (((SysTick_Type *)SysTick)->CTRL)
#define SYSTICK_LOAD                        (((SysTick_Type *)SysTick)->LOAD)
#define SYSTICK_VAL                         (((SysTick_Type *)SysTick)->VAL)
#define SCB_SCR                             (((SCB_Type *)SCB)->SCR)

#define CPUSS_SYSTICK_CTL                (((CPUSS_Type*) CPUSS_BASE)->SYSTICK_CTL)

#define UDB_UDBIF_BANK_CTL                  (((UDB_V1_Type *) cy_device->udbBase)->UDBIF.BANK_CTL)
#define UDB_BCTL_MDCLK_EN                   (((UDB_V1_Type *) cy_device->udbBase)->BCTL.MDCLK_EN)
#define UDB_BCTL_MBCLK_EN                   (((UDB_V1_Type *) cy_device->udbBase)->BCTL.MBCLK_EN)
#define UDB_BCTL_BOTSEL_L                   (((UDB_V1_Type *) cy_device->udbBase)->BCTL.BOTSEL_L)
#define UDB_BCTL_BOTSEL_U                   (((UDB_V1_Type *) cy_device->udbBase)->BCTL.BOTSEL_U)
#define UDB_BCTL_QCLK_EN_0                  (((UDB_V1_Type *) cy_device->udbBase)->BCTL.QCLK_EN[0U])
#define UDB_BCTL_QCLK_EN_1                  (((UDB_V1_Type *) cy_device->udbBase)->BCTL.QCLK_EN[1U])
#define UDB_BCTL_QCLK_EN_2                  (((UDB_V1_Type *) cy_device->udbBase)->BCTL.QCLK_EN[2U])

#define CPUSS_FAST_0_CLOCK_CTL              (((CPUSS_Type*) CPUSS_BASE)->FAST_0_CLOCK_CTL)
#define CPUSS_FAST_1_CLOCK_CTL              (((CPUSS_Type*) CPUSS_BASE)->FAST_1_CLOCK_CTL)
#define CPUSS_SLOW_CLOCK_CTL                (((CPUSS_Type*) CPUSS_BASE)->SLOW_CLOCK_CTL)
#define CPUSS_MEM_CLOCK_CTL                (((CPUSS_Type*) CPUSS_BASE)->MEM_CLOCK_CTL)
#define CPUSS_PERI_CLOCK_CTL                (((CPUSS_Type*) CPUSS_BASE)->PERI_CLOCK_CTL)

#define CPUSS_CM0_NMI_CTL(nmi)               (((volatile uint32_t *) (CPUSS->CM0_NMI_CTL))[(nmi)])
#define CPUSS_CM7_0_NMI_CTL(nmi)             (((volatile uint32_t *) (CPUSS->CM7_0_NMI_CTL))[(nmi)])
#define CPUSS_CM7_1_NMI_CTL(nmi)             (((volatile uint32_t *) (CPUSS->CM7_1_NMI_CTL))[(nmi)])


#define CY_CPUSS_NOT_CONNECTED_IRQN          ((uint32_t)disconnected_IRQn)
#define CY_CPUSS_DISCONNECTED_IRQN           ((cy_en_intr_t)CY_CPUSS_NOT_CONNECTED_IRQN)

#define CPUSS_CM0_INT_STATUS_BASE            ((volatile const uint32_t *) &(((CPUSS_Type *)(CPUSS))->CM0_INT0_STATUS))
#define CY_IS_CM0_CORE   ((_FLD2VAL(CPUSS_IDENTITY_MS, CPUSS_IDENTITY) == ((uint32_t)(CPUSS_MS_ID_CM0))) ? true : false)
#define CY_IS_CM7_CORE_0 ((_FLD2VAL(CPUSS_IDENTITY_MS, CPUSS_IDENTITY) == ((uint32_t)(CPUSS_MS_ID_CM7_0))) ? true : false)
#define CY_IS_CM7_CORE_1 ((_FLD2VAL(CPUSS_IDENTITY_MS, CPUSS_IDENTITY) == ((uint32_t)(CPUSS_MS_ID_CM7_1))) ? true : false)

#define CPUSS_IDENTITY                       ((((CPUSS_Type *)(CPUSS_BASE))->IDENTITY))
#define CPUSS_CM7_0_STATUS                   ((((CPUSS_Type *)(CPUSS_BASE))->CM7_0_STATUS))
#define CPUSS_FAST_0_CLOCK_CTL               (((CPUSS_Type*) CPUSS_BASE)->FAST_0_CLOCK_CTL)
#define CPUSS_CM7_0_CTL                      (((CPUSS_Type*) CPUSS_BASE)->CM7_0_CTL)
#define CPUSS_CM7_0_INT_STATUS               (((CPUSS_Type*) CPUSS_BASE)->CM7_0_INT_STATUS)
#define CPUSS_CM7_0_VECTOR_TABLE_BASE        (((CPUSS_Type*) CPUSS_BASE)->CM7_0_VECTOR_TABLE_BASE)
#define CPUSS_CM7_0_NMI_CTL(nmi)             (((volatile uint32_t *) (CPUSS->CM7_0_NMI_CTL))[(nmi)])
#define CPUSS_CM7_1_STATUS                   ((((CPUSS_Type *)(CPUSS_BASE))->CM7_1_STATUS))
#define CPUSS_FAST_1_CLOCK_CTL               (((CPUSS_Type*) CPUSS_BASE)->FAST_1_CLOCK_CTL)
#define CPUSS_CM7_1_CTL                      (((CPUSS_Type*) CPUSS_BASE)->CM7_1_CTL)
#define CPUSS_CM7_1_INT_STATUS               ((((CPUSS_Type *)(CPUSS_BASE))->CM7_1_INT_STATUS))
#define CPUSS_CM7_1_VECTOR_TABLE_BASE        (((CPUSS_Type*) CPUSS_BASE)->CM7_1_VECTOR_TABLE_BASE)
#define CPUSS_CM7_1_NMI_CTL(nmi)             (((volatile uint32_t *) (CPUSS->CM7_1_NMI_CTL))[(nmi)])
#define CPUSS_CM0_CTL                        (((CPUSS_Type*) CPUSS_BASE)->CM0_CTL)
#define CPUSS_CM0_STATUS                     (((CPUSS_Type*) CPUSS_BASE)->CM0_STATUS)
#define CPUSS_SLOW_CLOCK_CTL                 (((CPUSS_Type*) CPUSS_BASE)->SLOW_CLOCK_CTL)
#define CPUSS_PERI_CLOCK_CTL                 (((CPUSS_Type*) CPUSS_BASE)->PERI_CLOCK_CTL)
#define CPUSS_MEM_CLOCK_CTL                  (((CPUSS_Type*) CPUSS_BASE)->MEM_CLOCK_CTL)
#define CPUSS_CM0_INT0_STATUS                ((((CPUSS_Type *)(CPUSS_BASE))->CM0_INT0_STATUS))
#define CPUSS_CM0_INT1_STATUS                ((((CPUSS_Type *)(CPUSS_BASE))->CM0_INT1_STATUS))
#define CPUSS_CM0_INT2_STATUS                ((((CPUSS_Type *)(CPUSS_BASE))->CM0_INT2_STATUS))
#define CPUSS_CM0_INT3_STATUS                ((((CPUSS_Type *)(CPUSS_BASE))->CM0_INT3_STATUS))
#define CPUSS_CM0_INT4_STATUS                ((((CPUSS_Type *)(CPUSS_BASE))->CM0_INT4_STATUS))
#define CPUSS_CM0_INT5_STATUS                ((((CPUSS_Type *)(CPUSS_BASE))->CM0_INT5_STATUS))
#define CPUSS_CM0_INT6_STATUS                ((((CPUSS_Type *)(CPUSS_BASE))->CM0_INT6_STATUS))
#define CPUSS_CM0_INT7_STATUS                ((((CPUSS_Type *)(CPUSS_BASE))->CM0_INT7_STATUS))
#define CPUSS_CM0_NMI_CTL(nmi)               (((volatile uint32_t *) (CPUSS->CM0_NMI_CTL))[(nmi)])
#define CPUSS_CM0_VECTOR_TABLE_BASE          ((((CPUSS_Type *)(CPUSS_BASE))->CM0_VECTOR_TABLE_BASE))
#define CPUSS_CM7_0_PWR_CTL                  ((((CPUSS_Type *)(CPUSS_BASE))->CM7_0_PWR_CTL))
#define CPUSS_CM7_1_PWR_DELAY_CTL            ((((CPUSS_Type *)(CPUSS_BASE))->CM7_1_PWR_DELAY_CTL))
#define CPUSS_RAM0_CTL0                      ((((CPUSS_Type *)(CPUSS_BASE))->RAM0_CTL0))
#define CPUSS_RAM0_STATUS                    ((((CPUSS_Type *)(CPUSS_BASE))->RAM0_STATUS))
#define CPUSS_RAM0_PWR_MACRO_CTL(macroIdx)   ((((CPUSS_Type *)(CPUSS_BASE))->RAM0_PWR_MACRO_CTL[(macroIdx)]))
#define CPUSS_RAM1_CTL0                      ((((CPUSS_Type *)(CPUSS_BASE))->RAM1_STATUS))
#define CPUSS_RAM1_STATUS                    ((((CPUSS_Type *)(CPUSS_BASE))->RAM0_CTL0))
#define CPUSS_RAM1_PWR_CTL                   ((((CPUSS_Type *)(CPUSS_BASE))->RAM1_PWR_CTL))
#define CPUSS_RAM2_CTL0                      ((((CPUSS_Type *)(CPUSS_BASE))->RAM2_CTL0))
#define CPUSS_RAM2_STATUS                    ((((CPUSS_Type *)(CPUSS_BASE))->RAM2_STATUS))
#define CPUSS_RAM2_PWR_CTL                   ((((CPUSS_Type *)(CPUSS_BASE))->RAM2_PWR_CTL))
#define CPUSS_RAM_PWR_DELAY_CTL              ((((CPUSS_Type *)(CPUSS_BASE))->RAM_PWR_DELAY_CTL))
#define CPUSS_ROM_CTL                        ((((CPUSS_Type *)(CPUSS_BASE))->ROM_CTL))
#define CPUSS_ECC_CTL                        ((((CPUSS_Type *)(CPUSS_BASE))->ECC_CTL))
#define CPUSS_PRODUCT_ID                     ((((CPUSS_Type*) CPUSS_BASE)->PRODUCT_ID))
#define CPUSS_CM0_SYSTEM_INT_CTL             (((CPUSS_Type *)(CPUSS_BASE))->CM0_SYSTEM_INT_CTL)
#define CPUSS_CM7_0_SYSTEM_INT_CTL           (((CPUSS_Type *)(CPUSS_BASE))->CM7_0_SYSTEM_INT_CTL)
#define CPUSS_CM7_1_SYSTEM_INT_CTL           (((CPUSS_Type *)(CPUSS_BASE))->CM7_1_SYSTEM_INT_CTL)

#define CPUSS_SRAM_COUNT                    (1u + CPUSS_RAMC1_PRESENT + CPUSS_RAMC2_PRESENT)


/*******************************************************************************
*                LPCOMP
*******************************************************************************/

#define LPCOMP_CMP0_CTRL(base)              (((LPCOMP_V1_Type *)(base))->CMP0_CTRL)
#define LPCOMP_CMP1_CTRL(base)              (((LPCOMP_V1_Type *)(base))->CMP1_CTRL)
#define LPCOMP_CMP0_SW_CLEAR(base)          (((LPCOMP_V1_Type *)(base))->CMP0_SW_CLEAR)
#define LPCOMP_CMP1_SW_CLEAR(base)          (((LPCOMP_V1_Type *)(base))->CMP1_SW_CLEAR)
#define LPCOMP_CMP0_SW(base)                (((LPCOMP_V1_Type *)(base))->CMP0_SW)
#define LPCOMP_CMP1_SW(base)                (((LPCOMP_V1_Type *)(base))->CMP1_SW)
#define LPCOMP_STATUS(base)                 (((LPCOMP_V1_Type *)(base))->STATUS)
#define LPCOMP_CONFIG(base)                 (((LPCOMP_V1_Type *)(base))->CONFIG)
#define LPCOMP_INTR(base)                   (((LPCOMP_V1_Type *)(base))->INTR)
#define LPCOMP_INTR_SET(base)               (((LPCOMP_V1_Type *)(base))->INTR_SET)
#define LPCOMP_INTR_MASK(base)              (((LPCOMP_V1_Type *)(base))->INTR_MASK)
#define LPCOMP_INTR_MASKED(base)            (((LPCOMP_V1_Type *)(base))->INTR_MASKED)


/*******************************************************************************
*                MCWDT
*******************************************************************************/
#define MCWDT_CTR_CTL(base, counter)            (((MCWDT_Type *)(base))->CTR[counter].CTL)
#define MCWDT_CTR_LOWER_LIMIT(base, counter)    (((MCWDT_Type *)(base))->CTR[counter].LOWER_LIMIT)
#define MCWDT_CTR_UPPER_LIMIT(base, counter)    (((MCWDT_Type *)(base))->CTR[counter].UPPER_LIMIT)
#define MCWDT_CTR_WARN_LIMIT(base, counter)     (((MCWDT_Type *)(base))->CTR[counter].WARN_LIMIT)
#define MCWDT_CTR_CONFIG(base, counter)         (((MCWDT_Type *)(base))->CTR[counter].CONFIG)
#define MCWDT_CTR_CNT(base, counter)            (((MCWDT_Type *)(base))->CTR[counter].CNT)

#define MCWDT_CPU_SELECT(base)                  (((MCWDT_Type *)(base))->CPU_SELECT)
#define MCWDT_CTR2_CTL(base)                    (((MCWDT_Type *)(base))->CTR2_CTL)
#define MCWDT_CTR2_CONFIG(base)                 (((MCWDT_Type *)(base))->CTR2_CONFIG)
#define MCWDT_CTR2_CNT(base)                    (((MCWDT_Type *)(base))->CTR2_CNT)
#define MCWDT_LOCK(base)                        (((MCWDT_Type *)(base))->LOCK)
#define MCWDT_SERVICE(base)                     (((MCWDT_Type *)(base))->SERVICE)
#define MCWDT_INTR(base)                        (((MCWDT_Type *)(base))->INTR)
#define MCWDT_INTR_SET(base)                    (((MCWDT_Type *)(base))->INTR_SET)
#define MCWDT_INTR_MASK(base)                   (((MCWDT_Type *)(base))->INTR_MASK)
#define MCWDT_INTR_MASKED(base)                 (((MCWDT_Type *)(base))->INTR_MASKED)


/*******************************************************************************
*                TCPWM
*******************************************************************************/

#define TCPWM_CTRL_SET(base)                (((TCPWM_Type *)(base))->CTRL_SET)
#define TCPWM_CTRL_CLR(base)                (((TCPWM_Type *)(base))->CTRL_CLR)
#define TCPWM_CMD_START(base)               (((TCPWM_Type *)(base))->CMD_START)
#define TCPWM_CMD_RELOAD(base)              (((TCPWM_Type *)(base))->CMD_RELOAD)
#define TCPWM_CMD_STOP(base)                (((TCPWM_Type *)(base))->CMD_STOP)
#define TCPWM_CMD_CAPTURE(base)             (((TCPWM_Type *)(base))->CMD_CAPTURE)

#define TCPWM_CNT_CTRL(base, cntNum)         (((TCPWM_Type *)(base))->CNT[cntNum].CTRL)
#define TCPWM_CNT_CC(base, cntNum)           (((TCPWM_Type *)(base))->CNT[cntNum].CC)
#define TCPWM_CNT_CC_BUFF(base, cntNum)      (((TCPWM_Type *)(base))->CNT[cntNum].CC_BUFF)
#define TCPWM_CNT_COUNTER(base, cntNum)      (((TCPWM_Type *)(base))->CNT[cntNum].COUNTER)
#define TCPWM_CNT_PERIOD(base, cntNum)       (((TCPWM_Type *)(base))->CNT[cntNum].PERIOD)
#define TCPWM_CNT_PERIOD_BUFF(base, cntNum)  (((TCPWM_Type *)(base))->CNT[cntNum].PERIOD_BUFF)
#define TCPWM_CNT_STATUS(base, cntNum)       (((TCPWM_Type *)(base))->CNT[cntNum].STATUS)
#define TCPWM_CNT_INTR(base, cntNum)         (((TCPWM_Type *)(base))->CNT[cntNum].INTR)
#define TCPWM_CNT_INTR_SET(base, cntNum)     (((TCPWM_Type *)(base))->CNT[cntNum].INTR_SET)
#define TCPWM_CNT_INTR_MASK(base, cntNum)    (((TCPWM_Type *)(base))->CNT[cntNum].INTR_MASK)
#define TCPWM_CNT_INTR_MASKED(base, cntNum)  (((TCPWM_Type *)(base))->CNT[cntNum].INTR_MASKED)
#define TCPWM_CNT_TR_CTRL0(base, cntNum)     (((TCPWM_Type *)(base))->CNT[cntNum].TR_CTRL0)
#define TCPWM_CNT_TR_CTRL1(base, cntNum)     (((TCPWM_Type *)(base))->CNT[cntNum].TR_CTRL1)
#define TCPWM_CNT_TR_CTRL2(base, cntNum)     (((TCPWM_Type *)(base))->CNT[cntNum].TR_CTRL2)

#if (CY_IP_MXTCPWM_INSTANCES == 1UL)
#define TCPWM_GRP_CC1_PRESENT_STATUS(base) (TCPWM_GRP_NR0_CNT_GRP_CC1_PRESENT | (TCPWM_GRP_NR1_CNT_GRP_CC1_PRESENT << 1) | (TCPWM_GRP_NR2_CNT_GRP_CC1_PRESENT << 2))
#define TCPWM_GRP_AMC_PRESENT_STATUS(base) (TCPWM_GRP_NR0_CNT_GRP_AMC_PRESENT | (TCPWM_GRP_NR1_CNT_GRP_AMC_PRESENT << 1) | (TCPWM_GRP_NR2_CNT_GRP_CC1_PRESENT << 2))
#define TCPWM_GRP_SMC_PRESENT_STATUS(base) (TCPWM_GRP_NR0_CNT_GRP_SMC_PRESENT | (TCPWM_GRP_NR1_CNT_GRP_SMC_PRESENT << 1) | (TCPWM_GRP_NR2_CNT_GRP_CC1_PRESENT << 2))
#endif

#if (CY_IP_MXTCPWM_INSTANCES == 2UL)
#define TCPWM_GRP_CC1_PRESENT_STATUS(base) (((base) == (TCPWM_Type *) TCPWM0_BASE) ? (TCPWM0_GRP_NR0_CNT_GRP_CC1_PRESENT | (TCPWM0_GRP_NR1_CNT_GRP_CC1_PRESENT << 1) | (TCPWM0_GRP_NR2_CNT_GRP_CC1_PRESENT << 2)) : (TCPWM1_GRP_NR0_CNT_GRP_CC1_PRESENT | (TCPWM1_GRP_NR1_CNT_GRP_CC1_PRESENT << 1) | (TCPWM1_GRP_NR2_CNT_GRP_CC1_PRESENT << 2)))
#define TCPWM_GRP_AMC_PRESENT_STATUS(base) (((base) == (TCPWM_Type *) TCPWM0_BASE) ? (TCPWM0_GRP_NR0_CNT_GRP_AMC_PRESENT | (TCPWM0_GRP_NR1_CNT_GRP_AMC_PRESENT << 1) | (TCPWM0_GRP_NR2_CNT_GRP_CC1_PRESENT << 2)) : (TCPWM1_GRP_NR0_CNT_GRP_AMC_PRESENT | (TCPWM1_GRP_NR1_CNT_GRP_AMC_PRESENT << 1) | (TCPWM1_GRP_NR2_CNT_GRP_CC1_PRESENT << 2)))
#define TCPWM_GRP_SMC_PRESENT_STATUS(base) (((base) == (TCPWM_Type *) TCPWM0_BASE) ? (TCPWM0_GRP_NR0_CNT_GRP_SMC_PRESENT | (TCPWM0_GRP_NR1_CNT_GRP_SMC_PRESENT << 1) | (TCPWM0_GRP_NR2_CNT_GRP_CC1_PRESENT << 2)) : (TCPWM1_GRP_NR0_CNT_GRP_SMC_PRESENT | (TCPWM1_GRP_NR1_CNT_GRP_SMC_PRESENT << 1) | (TCPWM1_GRP_NR2_CNT_GRP_CC1_PRESENT << 2)))
#endif

#define TCPWM_GRP_CC1(base, grp) ((bool)(((TCPWM_GRP_CC1_PRESENT_STATUS(base)) >> (grp)) & 0x01U))
#define TCPWM_GRP_AMC(base, grp) ((bool)(((TCPWM_GRP_AMC_PRESENT_STATUS(base)) >> (grp)) & 0x01U))
#define TCPWM_GRP_SMC(base, grp) ((bool)(((TCPWM_GRP_SMC_PRESENT_STATUS(base)) >> (grp)) & 0x01U))

#define TCPWM_GRP_CNT_GET_GRP(cntNum)        ((cntNum )/ 256U)

#define TCPWM_GRP_CNT_CTRL(base, grp, cntNum)           (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CTRL)
#define TCPWM_GRP_CNT_STATUS(base, grp, cntNum)         (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].STATUS)
#define TCPWM_GRP_CNT_COUNTER(base, grp, cntNum)        (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].COUNTER)
#define TCPWM_GRP_CNT_CC0(base, grp, cntNum)            (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC0)
#define TCPWM_GRP_CNT_CC0_BUFF(base, grp, cntNum)       (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC0_BUFF)
#define TCPWM_GRP_CNT_CC1(base, grp, cntNum)            (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC1)
#define TCPWM_GRP_CNT_CC1_BUFF(base, grp, cntNum)       (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].CC1_BUFF)
#define TCPWM_GRP_CNT_PERIOD(base, grp, cntNum)         (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].PERIOD)
#define TCPWM_GRP_CNT_PERIOD_BUFF(base, grp, cntNum)    (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].PERIOD_BUFF)
#define TCPWM_GRP_CNT_LINE_SEL(base, grp, cntNum)       (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].LINE_SEL)
#define TCPWM_GRP_CNT_LINE_SEL_BUFF(base, grp, cntNum)  (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].LINE_SEL_BUFF)
#define TCPWM_GRP_CNT_DT(base, grp, cntNum)             (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].DT)
#define TCPWM_GRP_CNT_TR_CMD(base, grp, cntNum)         (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_CMD)
#define TCPWM_GRP_CNT_TR_IN_SEL0(base, grp, cntNum)     (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_IN_SEL0)
#define TCPWM_GRP_CNT_TR_IN_SEL1(base, grp, cntNum)     (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_IN_SEL1)
#define TCPWM_GRP_CNT_TR_IN_EDGE_SEL(base, grp, cntNum) (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_IN_EDGE_SEL)
#define TCPWM_GRP_CNT_TR_PWM_CTRL(base, grp, cntNum)    (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_PWM_CTRL)
#define TCPWM_GRP_CNT_TR_OUT_SEL(base, grp, cntNum)     (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].TR_OUT_SEL)
#define TCPWM_GRP_CNT_INTR(base, grp, cntNum)           (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR)
#define TCPWM_GRP_CNT_INTR_SET(base, grp, cntNum)       (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR_SET)
#define TCPWM_GRP_CNT_INTR_MASK(base, grp, cntNum)      (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR_MASK)
#define TCPWM_GRP_CNT_INTR_MASKED(base, grp, cntNum)    (((TCPWM_Type *)(base))->GRP[grp].CNT[((cntNum) % 256U)].INTR_MASKED)

#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC0_Pos TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC0_Pos
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC0_Msk TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC0_Msk
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC1_Pos TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC1_Pos
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_CC1_Msk TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_CC1_Msk
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_PERIOD_Pos TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_PERIOD_Pos
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_PERIOD_Msk TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_PERIOD_Msk
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_LINE_SEL_Pos TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_LINE_SEL_Pos
#define TCPWM_GRP_CNT_V2_CTRL_AUTO_RELOAD_LINE_SEL_Msk TCPWM_GRP_CNT_CTRL_AUTO_RELOAD_LINE_SEL_Msk
#define TCPWM_GRP_CNT_V2_CTRL_CC0_MATCH_UP_EN_Pos TCPWM_GRP_CNT_CTRL_CC0_MATCH_UP_EN_Pos
#define TCPWM_GRP_CNT_V2_CTRL_CC0_MATCH_UP_EN_Msk TCPWM_GRP_CNT_CTRL_CC0_MATCH_UP_EN_Msk
#define TCPWM_GRP_CNT_V2_CTRL_CC0_MATCH_DOWN_EN_Pos TCPWM_GRP_CNT_CTRL_CC0_MATCH_DOWN_EN_Pos
#define TCPWM_GRP_CNT_V2_CTRL_CC0_MATCH_DOWN_EN_Msk TCPWM_GRP_CNT_CTRL_CC0_MATCH_DOWN_EN_Msk
#define TCPWM_GRP_CNT_V2_CTRL_CC1_MATCH_UP_EN_Pos TCPWM_GRP_CNT_CTRL_CC1_MATCH_UP_EN_Pos
#define TCPWM_GRP_CNT_V2_CTRL_CC1_MATCH_UP_EN_Msk TCPWM_GRP_CNT_CTRL_CC1_MATCH_UP_EN_Msk
#define TCPWM_GRP_CNT_V2_CTRL_CC1_MATCH_DOWN_EN_Pos TCPWM_GRP_CNT_CTRL_CC1_MATCH_DOWN_EN_Pos
#define TCPWM_GRP_CNT_V2_CTRL_CC1_MATCH_DOWN_EN_Msk TCPWM_GRP_CNT_CTRL_CC1_MATCH_DOWN_EN_Msk
#define TCPWM_GRP_CNT_V2_CTRL_PWM_IMM_KILL_Pos  TCPWM_GRP_CNT_CTRL_PWM_IMM_KILL_Pos
#define TCPWM_GRP_CNT_V2_CTRL_PWM_IMM_KILL_Msk  TCPWM_GRP_CNT_CTRL_PWM_IMM_KILL_Msk
#define TCPWM_GRP_CNT_V2_CTRL_PWM_STOP_ON_KILL_Pos TCPWM_GRP_CNT_CTRL_PWM_STOP_ON_KILL_Pos
#define TCPWM_GRP_CNT_V2_CTRL_PWM_STOP_ON_KILL_Msk TCPWM_GRP_CNT_CTRL_PWM_STOP_ON_KILL_Msk
#define TCPWM_GRP_CNT_V2_CTRL_PWM_SYNC_KILL_Pos TCPWM_GRP_CNT_CTRL_PWM_SYNC_KILL_Pos
#define TCPWM_GRP_CNT_V2_CTRL_PWM_SYNC_KILL_Msk TCPWM_GRP_CNT_CTRL_PWM_SYNC_KILL_Msk
#define TCPWM_GRP_CNT_V2_CTRL_PWM_DISABLE_MODE_Pos TCPWM_GRP_CNT_CTRL_PWM_DISABLE_MODE_Pos
#define TCPWM_GRP_CNT_V2_CTRL_PWM_DISABLE_MODE_Msk TCPWM_GRP_CNT_CTRL_PWM_DISABLE_MODE_Msk
#define TCPWM_GRP_CNT_V2_CTRL_UP_DOWN_MODE_Pos  TCPWM_GRP_CNT_CTRL_UP_DOWN_MODE_Pos
#define TCPWM_GRP_CNT_V2_CTRL_UP_DOWN_MODE_Msk  TCPWM_GRP_CNT_CTRL_UP_DOWN_MODE_Msk
#define TCPWM_GRP_CNT_V2_CTRL_ONE_SHOT_Pos      TCPWM_GRP_CNT_CTRL_ONE_SHOT_Pos
#define TCPWM_GRP_CNT_V2_CTRL_ONE_SHOT_Msk      TCPWM_GRP_CNT_CTRL_ONE_SHOT_Msk
#define TCPWM_GRP_CNT_V2_CTRL_QUAD_ENCODING_MODE_Pos TCPWM_GRP_CNT_CTRL_QUAD_ENCODING_MODE_Pos
#define TCPWM_GRP_CNT_V2_CTRL_QUAD_ENCODING_MODE_Msk TCPWM_GRP_CNT_CTRL_QUAD_ENCODING_MODE_Msk
#define TCPWM_GRP_CNT_V2_CTRL_MODE_Pos          TCPWM_GRP_CNT_CTRL_MODE_Pos
#define TCPWM_GRP_CNT_V2_CTRL_MODE_Msk          TCPWM_GRP_CNT_CTRL_MODE_Msk
#define TCPWM_GRP_CNT_V2_CTRL_DBG_FREEZE_EN_Pos TCPWM_GRP_CNT_CTRL_DBG_FREEZE_EN_Pos
#define TCPWM_GRP_CNT_V2_CTRL_DBG_FREEZE_EN_Msk TCPWM_GRP_CNT_CTRL_DBG_FREEZE_EN_Msk
#define TCPWM_GRP_CNT_V2_CTRL_ENABLED_Pos       TCPWM_GRP_CNT_CTRL_ENABLED_Pos
#define TCPWM_GRP_CNT_V2_CTRL_ENABLED_Msk       TCPWM_GRP_CNT_CTRL_ENABLED_Msk
/* TCPWM_GRP_CNT.STATUS */
#define TCPWM_GRP_CNT_V2_STATUS_DOWN_Pos        TCPWM_GRP_CNT_STATUS_DOWN_Pos
#define TCPWM_GRP_CNT_V2_STATUS_DOWN_Msk        TCPWM_GRP_CNT_STATUS_DOWN_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_CAPTURE0_Pos TCPWM_GRP_CNT_STATUS_TR_CAPTURE0_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_CAPTURE0_Msk TCPWM_GRP_CNT_STATUS_TR_CAPTURE0_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_COUNT_Pos    TCPWM_GRP_CNT_STATUS_TR_COUNT_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_COUNT_Msk    TCPWM_GRP_CNT_STATUS_TR_COUNT_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_RELOAD_Pos   TCPWM_GRP_CNT_STATUS_TR_RELOAD_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_RELOAD_Msk   TCPWM_GRP_CNT_STATUS_TR_RELOAD_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_STOP_Pos     TCPWM_GRP_CNT_STATUS_TR_STOP_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_STOP_Msk     TCPWM_GRP_CNT_STATUS_TR_STOP_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_START_Pos    TCPWM_GRP_CNT_STATUS_TR_START_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_START_Msk    TCPWM_GRP_CNT_STATUS_TR_START_Msk
#define TCPWM_GRP_CNT_V2_STATUS_TR_CAPTURE1_Pos TCPWM_GRP_CNT_STATUS_TR_CAPTURE1_Pos
#define TCPWM_GRP_CNT_V2_STATUS_TR_CAPTURE1_Msk TCPWM_GRP_CNT_STATUS_TR_CAPTURE1_Msk
#define TCPWM_GRP_CNT_V2_STATUS_LINE_OUT_Pos    TCPWM_GRP_CNT_STATUS_LINE_OUT_Pos
#define TCPWM_GRP_CNT_V2_STATUS_LINE_OUT_Msk    TCPWM_GRP_CNT_STATUS_LINE_OUT_Msk
#define TCPWM_GRP_CNT_V2_STATUS_LINE_COMPL_OUT_Pos TCPWM_GRP_CNT_STATUS_LINE_COMPL_OUT_Pos
#define TCPWM_GRP_CNT_V2_STATUS_LINE_COMPL_OUT_Msk TCPWM_GRP_CNT_STATUS_LINE_COMPL_OUT_Msk
#define TCPWM_GRP_CNT_V2_STATUS_RUNNING_Pos     TCPWM_GRP_CNT_STATUS_RUNNING_Pos
#define TCPWM_GRP_CNT_V2_STATUS_RUNNING_Msk     TCPWM_GRP_CNT_STATUS_RUNNING_Msk
#define TCPWM_GRP_CNT_V2_STATUS_DT_CNT_L_Pos    TCPWM_GRP_CNT_STATUS_DT_CNT_L_Pos
#define TCPWM_GRP_CNT_V2_STATUS_DT_CNT_L_Msk    TCPWM_GRP_CNT_STATUS_DT_CNT_L_Msk
#define TCPWM_GRP_CNT_V2_STATUS_DT_CNT_H_Pos    TCPWM_GRP_CNT_STATUS_DT_CNT_H_Pos
#define TCPWM_GRP_CNT_V2_STATUS_DT_CNT_H_Msk    TCPWM_GRP_CNT_STATUS_DT_CNT_H_Msk
/* TCPWM_GRP_CNT.COUNTER */
#define TCPWM_GRP_CNT_V2_COUNTER_COUNTER_Pos    TCPWM_GRP_CNT_COUNTER_COUNTER_Pos
#define TCPWM_GRP_CNT_V2_COUNTER_COUNTER_Msk    TCPWM_GRP_CNT_COUNTER_COUNTER_Msk
/* TCPWM_GRP_CNT.CC0 */
#define TCPWM_GRP_CNT_V2_CC0_CC_Pos             TCPWM_GRP_CNT_CC0_CC_Pos
#define TCPWM_GRP_CNT_V2_CC0_CC_Msk             TCPWM_GRP_CNT_CC0_CC_Msk
/* TCPWM_GRP_CNT.CC0_BUFF */
#define TCPWM_GRP_CNT_V2_CC0_BUFF_CC_Pos        TCPWM_GRP_CNT_CC0_BUFF_CC_Pos
#define TCPWM_GRP_CNT_V2_CC0_BUFF_CC_Msk        TCPWM_GRP_CNT_CC0_BUFF_CC_Msk
/* TCPWM_GRP_CNT.CC1 */
#define TCPWM_GRP_CNT_V2_CC1_CC_Pos             TCPWM_GRP_CNT_CC1_CC_Pos
#define TCPWM_GRP_CNT_V2_CC1_CC_Msk             TCPWM_GRP_CNT_CC1_CC_Msk
/* TCPWM_GRP_CNT.CC1_BUFF */
#define TCPWM_GRP_CNT_V2_CC1_BUFF_CC_Pos        TCPWM_GRP_CNT_CC1_BUFF_CC_Pos
#define TCPWM_GRP_CNT_V2_CC1_BUFF_CC_Msk        TCPWM_GRP_CNT_CC1_BUFF_CC_Msk
/* TCPWM_GRP_CNT.PERIOD */
#define TCPWM_GRP_CNT_V2_PERIOD_PERIOD_Pos      TCPWM_GRP_CNT_PERIOD_PERIOD_Pos
#define TCPWM_GRP_CNT_V2_PERIOD_PERIOD_Msk      TCPWM_GRP_CNT_PERIOD_PERIOD_Msk
/* TCPWM_GRP_CNT.PERIOD_BUFF */
#define TCPWM_GRP_CNT_V2_PERIOD_BUFF_PERIOD_Pos TCPWM_GRP_CNT_PERIOD_BUFF_PERIOD_Pos
#define TCPWM_GRP_CNT_V2_PERIOD_BUFF_PERIOD_Msk TCPWM_GRP_CNT_PERIOD_BUFF_PERIOD_Msk
/* TCPWM_GRP_CNT.LINE_SEL */
#define TCPWM_GRP_CNT_V2_LINE_SEL_OUT_SEL_Pos   TCPWM_GRP_CNT_LINE_SEL_OUT_SEL_Pos
#define TCPWM_GRP_CNT_V2_LINE_SEL_OUT_SEL_Msk   TCPWM_GRP_CNT_LINE_SEL_OUT_SEL_Msk
#define TCPWM_GRP_CNT_V2_LINE_SEL_COMPL_OUT_SEL_Pos TCPWM_GRP_CNT_LINE_SEL_COMPL_OUT_SEL_Pos
#define TCPWM_GRP_CNT_V2_LINE_SEL_COMPL_OUT_SEL_Msk TCPWM_GRP_CNT_LINE_SEL_COMPL_OUT_SEL_Msk
/* TCPWM_GRP_CNT.LINE_SEL_BUFF */
#define TCPWM_GRP_CNT_V2_LINE_SEL_BUFF_OUT_SEL_Pos TCPWM_GRP_CNT_LINE_SEL_BUFF_OUT_SEL_Pos
#define TCPWM_GRP_CNT_V2_LINE_SEL_BUFF_OUT_SEL_Msk TCPWM_GRP_CNT_LINE_SEL_BUFF_OUT_SEL_Msk
#define TCPWM_GRP_CNT_V2_LINE_SEL_BUFF_COMPL_OUT_SEL_Pos TCPWM_GRP_CNT_LINE_SEL_BUFF_COMPL_OUT_SEL_Pos
#define TCPWM_GRP_CNT_V2_LINE_SEL_BUFF_COMPL_OUT_SEL_Msk TCPWM_GRP_CNT_LINE_SEL_BUFF_COMPL_OUT_SEL_Msk
/* TCPWM_GRP_CNT.DT */
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_L_Pos   TCPWM_GRP_CNT_DT_DT_LINE_OUT_L_Pos
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_L_Msk   TCPWM_GRP_CNT_DT_DT_LINE_OUT_L_Msk
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_H_Pos   TCPWM_GRP_CNT_DT_DT_LINE_OUT_H_Pos
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_OUT_H_Msk   TCPWM_GRP_CNT_DT_DT_LINE_OUT_H_Msk
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_COMPL_OUT_Pos TCPWM_GRP_CNT_DT_DT_LINE_COMPL_OUT_Pos
#define TCPWM_GRP_CNT_V2_DT_DT_LINE_COMPL_OUT_Msk TCPWM_GRP_CNT_DT_DT_LINE_COMPL_OUT_Msk
/* TCPWM_GRP_CNT.TR_CMD */
#define TCPWM_GRP_CNT_V2_TR_CMD_CAPTURE0_Pos    TCPWM_GRP_CNT_TR_CMD_CAPTURE0_Pos
#define TCPWM_GRP_CNT_V2_TR_CMD_CAPTURE0_Msk    TCPWM_GRP_CNT_TR_CMD_CAPTURE0_Msk
#define TCPWM_GRP_CNT_V2_TR_CMD_RELOAD_Pos      TCPWM_GRP_CNT_TR_CMD_RELOAD_Pos
#define TCPWM_GRP_CNT_V2_TR_CMD_RELOAD_Msk      TCPWM_GRP_CNT_TR_CMD_RELOAD_Msk
#define TCPWM_GRP_CNT_V2_TR_CMD_STOP_Pos        TCPWM_GRP_CNT_TR_CMD_STOP_Pos
#define TCPWM_GRP_CNT_V2_TR_CMD_STOP_Msk        TCPWM_GRP_CNT_TR_CMD_STOP_Msk
#define TCPWM_GRP_CNT_V2_TR_CMD_START_Pos       TCPWM_GRP_CNT_TR_CMD_START_Pos
#define TCPWM_GRP_CNT_V2_TR_CMD_START_Msk       TCPWM_GRP_CNT_TR_CMD_START_Msk
#define TCPWM_GRP_CNT_V2_TR_CMD_CAPTURE1_Pos    TCPWM_GRP_CNT_TR_CMD_CAPTURE1_Pos
#define TCPWM_GRP_CNT_V2_TR_CMD_CAPTURE1_Msk    TCPWM_GRP_CNT_TR_CMD_CAPTURE1_Msk
/* TCPWM_GRP_CNT.TR_IN_SEL0 */
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL0_CAPTURE0_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_CAPTURE0_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL0_CAPTURE0_SEL_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL0_COUNT_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_COUNT_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL0_COUNT_SEL_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL0_RELOAD_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_RELOAD_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL0_RELOAD_SEL_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL0_STOP_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL0_STOP_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL0_STOP_SEL_Msk
/* TCPWM_GRP_CNT.TR_IN_SEL1 */
#define TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL1_START_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL1_START_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL1_START_SEL_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_SEL1_CAPTURE1_SEL_Pos TCPWM_GRP_CNT_TR_IN_SEL1_CAPTURE1_SEL_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_SEL1_CAPTURE1_SEL_Msk TCPWM_GRP_CNT_TR_IN_SEL1_CAPTURE1_SEL_Msk
/* TCPWM_GRP_CNT.TR_IN_EDGE_SEL */
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE0_EDGE_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_COUNT_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_COUNT_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_COUNT_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_COUNT_EDGE_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_RELOAD_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_RELOAD_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_RELOAD_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_RELOAD_EDGE_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_STOP_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_STOP_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_STOP_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_STOP_EDGE_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_START_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_START_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_START_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_START_EDGE_Msk
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Pos TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Pos
#define TCPWM_GRP_CNT_V2_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Msk TCPWM_GRP_CNT_TR_IN_EDGE_SEL_CAPTURE1_EDGE_Msk
/* TCPWM_GRP_CNT.TR_PWM_CTRL */
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE_Pos TCPWM_GRP_CNT_TR_PWM_CTRL_CC0_MATCH_MODE_Pos
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC0_MATCH_MODE_Msk TCPWM_GRP_CNT_TR_PWM_CTRL_CC0_MATCH_MODE_Msk
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE_Pos TCPWM_GRP_CNT_TR_PWM_CTRL_OVERFLOW_MODE_Pos
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_OVERFLOW_MODE_Msk TCPWM_GRP_CNT_TR_PWM_CTRL_OVERFLOW_MODE_Msk
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE_Pos TCPWM_GRP_CNT_TR_PWM_CTRL_UNDERFLOW_MODE_Pos
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_UNDERFLOW_MODE_Msk TCPWM_GRP_CNT_TR_PWM_CTRL_UNDERFLOW_MODE_Msk
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC1_MATCH_MODE_Pos TCPWM_GRP_CNT_TR_PWM_CTRL_CC1_MATCH_MODE_Pos
#define TCPWM_GRP_CNT_V2_TR_PWM_CTRL_CC1_MATCH_MODE_Msk TCPWM_GRP_CNT_TR_PWM_CTRL_CC1_MATCH_MODE_Msk
/* TCPWM_GRP_CNT.TR_OUT_SEL */
#define TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0_Pos    TCPWM_GRP_CNT_TR_OUT_SEL_OUT0_Pos
#define TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT0_Msk    TCPWM_GRP_CNT_TR_OUT_SEL_OUT0_Msk
#define TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1_Pos    TCPWM_GRP_CNT_TR_OUT_SEL_OUT1_Pos
#define TCPWM_GRP_CNT_V2_TR_OUT_SEL_OUT1_Msk    TCPWM_GRP_CNT_TR_OUT_SEL_OUT1_Msk
/* TCPWM_GRP_CNT.INTR */
#define TCPWM_GRP_CNT_V2_INTR_TC_Pos            TCPWM_GRP_CNT_INTR_TC_Pos
#define TCPWM_GRP_CNT_V2_INTR_TC_Msk            TCPWM_GRP_CNT_INTR_TC_Msk
#define TCPWM_GRP_CNT_V2_INTR_CC0_MATCH_Pos     TCPWM_GRP_CNT_INTR_CC0_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_CC0_MATCH_Msk     TCPWM_GRP_CNT_INTR_CC0_MATCH_Msk
#define TCPWM_GRP_CNT_V2_INTR_CC1_MATCH_Pos     TCPWM_GRP_CNT_INTR_CC1_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_CC1_MATCH_Msk     TCPWM_GRP_CNT_INTR_CC1_MATCH_Msk
/* TCPWM_GRP_CNT.INTR_SET */
#define TCPWM_GRP_CNT_V2_INTR_SET_TC_Pos        TCPWM_GRP_CNT_INTR_SET_TC_Pos
#define TCPWM_GRP_CNT_V2_INTR_SET_TC_Msk        TCPWM_GRP_CNT_INTR_SET_TC_Msk
#define TCPWM_GRP_CNT_V2_INTR_SET_CC0_MATCH_Pos TCPWM_GRP_CNT_INTR_SET_CC0_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_SET_CC0_MATCH_Msk TCPWM_GRP_CNT_INTR_SET_CC0_MATCH_Msk
#define TCPWM_GRP_CNT_V2_INTR_SET_CC1_MATCH_Pos TCPWM_GRP_CNT_INTR_SET_CC1_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_SET_CC1_MATCH_Msk TCPWM_GRP_CNT_INTR_SET_CC1_MATCH_Msk
/* TCPWM_GRP_CNT.INTR_MASK */
#define TCPWM_GRP_CNT_V2_INTR_MASK_TC_Pos       TCPWM_GRP_CNT_INTR_MASK_TC_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASK_TC_Msk       TCPWM_GRP_CNT_INTR_MASK_TC_Msk
#define TCPWM_GRP_CNT_V2_INTR_MASK_CC0_MATCH_Pos TCPWM_GRP_CNT_INTR_MASK_CC0_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASK_CC0_MATCH_Msk TCPWM_GRP_CNT_INTR_MASK_CC0_MATCH_Msk
#define TCPWM_GRP_CNT_V2_INTR_MASK_CC1_MATCH_Pos TCPWM_GRP_CNT_INTR_MASK_CC1_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASK_CC1_MATCH_Msk TCPWM_GRP_CNT_INTR_MASK_CC1_MATCH_Msk
/* TCPWM_GRP_CNT.INTR_MASKED */
#define TCPWM_GRP_CNT_V2_INTR_MASKED_TC_Pos     TCPWM_GRP_CNT_INTR_MASKED_TC_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASKED_TC_Msk     TCPWM_GRP_CNT_INTR_MASKED_TC_Msk
#define TCPWM_GRP_CNT_V2_INTR_MASKED_CC0_MATCH_Pos TCPWM_GRP_CNT_INTR_MASKED_CC0_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASKED_CC0_MATCH_Msk TCPWM_GRP_CNT_INTR_MASKED_CC0_MATCH_Msk
#define TCPWM_GRP_CNT_V2_INTR_MASKED_CC1_MATCH_Pos TCPWM_GRP_CNT_INTR_MASKED_CC1_MATCH_Pos
#define TCPWM_GRP_CNT_V2_INTR_MASKED_CC1_MATCH_Msk TCPWM_GRP_CNT_INTR_MASKED_CC1_MATCH_Msk

/* For backward compatibility, we set TCPWM_CNT_STATUS_RUNNING_Pos with TCPWM_GRP_CNT_V2_STATUS_RUNNING
we need to define this for version 2 only. */
#define TCPWM_CNT_STATUS_RUNNING_Pos 31UL


/*******************************************************************************
*                SAR
*******************************************************************************/

#define CY_SAR_INSTANCES                    (2UL)
#define CY_SAR0_BASE                        ((SAR_Type*)(cy_device->sar0Base))
#define CY_SAR_INSTANCE(base)               ((CY_SAR0_BASE == (base)) ? 0UL : 1UL)

#define SAR_SAMPLE_CTRL(base)               (((SAR_V1_Type *)(base))->SAMPLE_CTRL)
#define SAR_SAMPLE_TIME01(base)             (((SAR_V1_Type *)(base))->SAMPLE_TIME01)
#define SAR_SAMPLE_TIME23(base)             (((SAR_V1_Type *)(base))->SAMPLE_TIME23)

#define SAR_RANGE_THRES(base)               (((SAR_V1_Type *)(base))->RANGE_THRES)
#define SAR_RANGE_COND(base)                (((SAR_V1_Type *)(base))->RANGE_COND)
#define SAR_RANGE_INTR(base)                (((SAR_V1_Type *)(base))->RANGE_INTR)
#define SAR_RANGE_INTR_SET(base)            (((SAR_V1_Type *)(base))->RANGE_INTR_SET)

#define SAR_RANGE_INTR_MASK(base)           (((SAR_V1_Type *)(base))->RANGE_INTR_MASK)
#define SAR_RANGE_INTR_MASKED(base)         (((SAR_V1_Type *)(base))->RANGE_INTR_MASKED)

#define SAR_CHAN_EN(base)                   (((SAR_V1_Type *)(base))->CHAN_EN)
#define SAR_CHAN_CONFIG(base, chan)         (((SAR_V1_Type *)(base))->CHAN_CONFIG[(chan)])
#define SAR_CHAN_RESULT(base, chan )        (((SAR_V1_Type *)(base))->CHAN_RESULT[(chan)])
#define SAR_CHAN_RESULT_UPDATED(base)       (((SAR_V1_Type *)(base))->CHAN_RESULT_UPDATED)

#define SAR_INTR(base)                      (((SAR_V1_Type *)(base))->INTR)
#define SAR_INTR_MASK(base)                 (((SAR_V1_Type *)(base))->INTR_MASK)
#define SAR_INTR_MASKED(base)               (((SAR_V1_Type *)(base))->INTR_MASKED)
#define SAR_INTR_SET(base)                  (((SAR_V1_Type *)(base))->INTR_SET)
#define SAR_INTR_CAUSE(base)                (((SAR_V1_Type *)(base))->INTR_CAUSE)

#define SAR_MUX_SWITCH_CLEAR0(base)         (((SAR_V1_Type *)(base))->MUX_SWITCH_CLEAR0)
#define SAR_MUX_SWITCH0(base)               (((SAR_V1_Type *)(base))->MUX_SWITCH0)
#define SAR_MUX_SWITCH_SQ_CTRL(base)        (((SAR_V1_Type *)(base))->MUX_SWITCH_SQ_CTRL)
#define SAR_MUX_SWITCH_DS_CTRL(base)        (((SAR_V1_Type *)(base))->MUX_SWITCH_DS_CTRL)

#define SAR_ANA_TRIM0(base)                 (((SAR_V1_Type *)(base))->ANA_TRIM0)
#define SAR_CTRL(base)                      (((SAR_V1_Type *)(base))->CTRL)
#define SAR_STATUS(base)                    (((SAR_V1_Type *)(base))->STATUS)
#define SAR_START_CTRL(base)                (((SAR_V1_Type *)(base))->START_CTRL)

#define SAR_SATURATE_INTR(base)             (((SAR_V1_Type *)(base))->SATURATE_INTR)
#define SAR_SATURATE_INTR_MASK(base)        (((SAR_V1_Type *)(base))->SATURATE_INTR_MASK)
#define SAR_SATURATE_INTR_MASKED(base)      (((SAR_V1_Type *)(base))->SATURATE_INTR_MASKED)
#define SAR_SATURATE_INTR_SET(base)         (((SAR_V1_Type *)(base))->SATURATE_INTR_SET)

#define SAR_INJ_CHAN_CONFIG(base)           (((SAR_V1_Type *)(base))->INJ_CHAN_CONFIG)
#define SAR_INJ_RESULT(base)                (((SAR_V1_Type *)(base))->INJ_RESULT)

/*******************************************************************************
*                FAULT
*******************************************************************************/

#define FAULT_CTL(base)                         (((FAULT_STRUCT_Type *)(base))->CTL)
#define FAULT_STATUS(base)                      (((FAULT_STRUCT_Type *)(base))->STATUS)
#define FAULT_DATA(base)                        (((FAULT_STRUCT_Type *)(base))->DATA)
#define FAULT_PENDING0(base)                    (((FAULT_STRUCT_Type *)(base))->PENDING0)
#define FAULT_PENDING1(base)                    (((FAULT_STRUCT_Type *)(base))->PENDING1)
#define FAULT_PENDING2(base)                    (((FAULT_STRUCT_Type *)(base))->PENDING2)
#define FAULT_MASK0(base)                       (((FAULT_STRUCT_Type *)(base))->MASK0)
#define FAULT_MASK1(base)                       (((FAULT_STRUCT_Type *)(base))->MASK1)
#define FAULT_MASK2(base)                       (((FAULT_STRUCT_Type *)(base))->MASK2)
#define FAULT_INTR(base)                        (((FAULT_STRUCT_Type *)(base))->INTR)
#define FAULT_INTR_SET(base)                    (((FAULT_STRUCT_Type *)(base))->INTR_SET)
#define FAULT_INTR_MASK(base)                   (((FAULT_STRUCT_Type *)(base))->INTR_MASK)
#define FAULT_INTR_MASKED(base)                 (((FAULT_STRUCT_Type *)(base))->INTR_MASKED)

/*******************************************************************************
*                SDHC
*******************************************************************************/

#define SDHC_WRAP_CTL(base)                     (((SDHC_Type *)(base))->WRAP.CTL)
#define SDHC_CORE_SDMASA_R(base)                (((SDHC_Type *)(base))->CORE.SDMASA_R)
#define SDHC_CORE_BLOCKSIZE_R(base)             (((SDHC_Type *)(base))->CORE.BLOCKSIZE_R)
#define SDHC_CORE_BLOCKCOUNT_R(base)            (((SDHC_Type *)(base))->CORE.BLOCKCOUNT_R)
#define SDHC_CORE_ARGUMENT_R(base)              (((SDHC_Type *)(base))->CORE.ARGUMENT_R)
#define SDHC_CORE_XFER_MODE_R(base)             (((SDHC_Type *)(base))->CORE.XFER_MODE_R)
#define SDHC_CORE_CMD_R(base)                   (((SDHC_Type *)(base))->CORE.CMD_R)
#define SDHC_CORE_RESP01_R(base)                (((SDHC_Type *)(base))->CORE.RESP01_R)
#define SDHC_CORE_RESP23_R(base)                (((SDHC_Type *)(base))->CORE.RESP23_R)
#define SDHC_CORE_RESP45_R(base)                (((SDHC_Type *)(base))->CORE.RESP45_R)
#define SDHC_CORE_RESP67_R(base)                (((SDHC_Type *)(base))->CORE.RESP67_R)
#define SDHC_CORE_BUF_DATA_R(base)              (((SDHC_Type *)(base))->CORE.BUF_DATA_R)
#define SDHC_CORE_PSTATE_REG(base)              (((SDHC_Type *)(base))->CORE.PSTATE_REG)
#define SDHC_CORE_HOST_CTRL1_R(base)            (((SDHC_Type *)(base))->CORE.HOST_CTRL1_R)
#define SDHC_CORE_PWR_CTRL_R(base)              (((SDHC_Type *)(base))->CORE.PWR_CTRL_R)
#define SDHC_CORE_BGAP_CTRL_R(base)             (((SDHC_Type *)(base))->CORE.BGAP_CTRL_R)
#define SDHC_CORE_WUP_CTRL_R(base)              (((SDHC_Type *)(base))->CORE.WUP_CTRL_R)
#define SDHC_CORE_CLK_CTRL_R(base)              (((SDHC_Type *)(base))->CORE.CLK_CTRL_R)
#define SDHC_CORE_TOUT_CTRL_R(base)             (((SDHC_Type *)(base))->CORE.TOUT_CTRL_R)
#define SDHC_CORE_SW_RST_R(base)                (((SDHC_Type *)(base))->CORE.SW_RST_R)
#define SDHC_CORE_NORMAL_INT_STAT_R(base)       (((SDHC_Type *)(base))->CORE.NORMAL_INT_STAT_R)
#define SDHC_CORE_ERROR_INT_STAT_R(base)        (((SDHC_Type *)(base))->CORE.ERROR_INT_STAT_R)
#define SDHC_CORE_NORMAL_INT_STAT_EN_R(base)    (((SDHC_Type *)(base))->CORE.NORMAL_INT_STAT_EN_R)
#define SDHC_CORE_ERROR_INT_STAT_EN_R(base)     (((SDHC_Type *)(base))->CORE.ERROR_INT_STAT_EN_R)
#define SDHC_CORE_NORMAL_INT_SIGNAL_EN_R(base)  (((SDHC_Type *)(base))->CORE.NORMAL_INT_SIGNAL_EN_R)
#define SDHC_CORE_ERROR_INT_SIGNAL_EN_R(base)   (((SDHC_Type *)(base))->CORE.ERROR_INT_SIGNAL_EN_R)
#define SDHC_CORE_AUTO_CMD_STAT_R(base)         (((SDHC_Type *)(base))->CORE.AUTO_CMD_STAT_R)
#define SDHC_CORE_HOST_CTRL2_R(base)            (((SDHC_Type *)(base))->CORE.HOST_CTRL2_R)
#define SDHC_CORE_CAPABILITIES1_R(base)         (((SDHC_Type *)(base))->CORE.CAPABILITIES1_R)
#define SDHC_CORE_CAPABILITIES2_R(base)         (((SDHC_Type *)(base))->CORE.CAPABILITIES2_R)
#define SDHC_CORE_CURR_CAPABILITIES1_R(base)    (((SDHC_Type *)(base))->CORE.CURR_CAPABILITIES1_R)
#define SDHC_CORE_CURR_CAPABILITIES2_R(base)    (((SDHC_Type *)(base))->CORE.CURR_CAPABILITIES2_R)
#define SDHC_CORE_ADMA_ERR_STAT_R(base)         (((SDHC_Type *)(base))->CORE.ADMA_ERR_STAT_R)
#define SDHC_CORE_ADMA_SA_LOW_R(base)           (((SDHC_Type *)(base))->CORE.ADMA_SA_LOW_R)
#define SDHC_CORE_ADMA_ID_LOW_R(base)           (((SDHC_Type *)(base))->CORE.ADMA_ID_LOW_R)
#define SDHC_CORE_EMMC_CTRL_R(base)             (((SDHC_Type *)(base))->CORE.EMMC_CTRL_R)
#define SDHC_CORE_GP_OUT_R(base)                (((SDHC_Type *)(base))->CORE.GP_OUT_R)

/*******************************************************************************
*                SMARTIO
*******************************************************************************/

#define SMARTIO_PRT_CTL(base)               (((SMARTIO_PRT_Type *)(base))->CTL)
#define SMARTIO_PRT_SYNC_CTL(base)          (((SMARTIO_PRT_Type *)(base))->SYNC_CTL)
#define SMARTIO_PRT_LUT_SEL(base, idx)      (((SMARTIO_PRT_Type *)(base))->LUT_SEL[idx])
#define SMARTIO_PRT_LUT_CTL(base, idx)      (((SMARTIO_PRT_Type *)(base))->LUT_CTL[idx])
#define SMARTIO_PRT_DU_SEL(base)            (((SMARTIO_PRT_Type *)(base))->DU_SEL)
#define SMARTIO_PRT_DU_CTL(base)            (((SMARTIO_PRT_Type *)(base))->DU_CTL)
#define SMARTIO_PRT_DATA(base)              (((SMARTIO_PRT_Type *)(base))->DATA)


/*******************************************************************************
*                SMIF
*******************************************************************************/

#define SMIF_DEVICE_CTL(base)               (((SMIF_DEVICE_Type *)(base))->CTL)
#define SMIF_DEVICE_ADDR(base)              (((SMIF_DEVICE_Type *)(base))->ADDR)
#define SMIF_DEVICE_ADDR_CTL(base)          (((SMIF_DEVICE_Type *)(base))->ADDR_CTL)
#define SMIF_DEVICE_MASK(base)              (((SMIF_DEVICE_Type *)(base))->MASK)
#define SMIF_DEVICE_RD_CMD_CTL(base)        (((SMIF_DEVICE_Type *)(base))->RD_CMD_CTL)
#define SMIF_DEVICE_RD_ADDR_CTL(base)       (((SMIF_DEVICE_Type *)(base))->RD_ADDR_CTL)
#define SMIF_DEVICE_RD_MODE_CTL(base)       (((SMIF_DEVICE_Type *)(base))->RD_MODE_CTL)
#define SMIF_DEVICE_RD_DUMMY_CTL(base)      (((SMIF_DEVICE_Type *)(base))->RD_DUMMY_CTL)
#define SMIF_DEVICE_RD_DATA_CTL(base)       (((SMIF_DEVICE_Type *)(base))->RD_DATA_CTL)
#define SMIF_DEVICE_WR_CMD_CTL(base)        (((SMIF_DEVICE_Type *)(base))->WR_CMD_CTL)
#define SMIF_DEVICE_WR_ADDR_CTL(base)       (((SMIF_DEVICE_Type *)(base))->WR_ADDR_CTL)
#define SMIF_DEVICE_WR_MODE_CTL(base)       (((SMIF_DEVICE_Type *)(base))->WR_MODE_CTL)
#define SMIF_DEVICE_WR_DUMMY_CTL(base)      (((SMIF_DEVICE_Type *)(base))->WR_DUMMY_CTL)
#define SMIF_DEVICE_WR_DATA_CTL(base)       (((SMIF_DEVICE_Type *)(base))->WR_DATA_CTL)

#define SMIF_DEVICE_IDX(base, deviceIndex)                 (((SMIF_Type *)(base))->DEVICE[deviceIndex])

#define SMIF_DEVICE_IDX_CTL(base, deviceIndex)             (SMIF_DEVICE_IDX(base, deviceIndex).CTL)
#define SMIF_DEVICE_IDX_ADDR(base, deviceIndex)            (SMIF_DEVICE_IDX(base, deviceIndex).ADDR)
#define SMIF_DEVICE_IDX_ADDR_CTL(base, deviceIndex)        (SMIF_DEVICE_IDX(base, deviceIndex).ADDR_CTL)
#define SMIF_DEVICE_IDX_MASK(base, deviceIndex)            (SMIF_DEVICE_IDX(base, deviceIndex).MASK)
#define SMIF_DEVICE_IDX_RD_CMD_CTL(base, deviceIndex)      (SMIF_DEVICE_IDX(base, deviceIndex).RD_CMD_CTL)
#define SMIF_DEVICE_IDX_RD_ADDR_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).RD_ADDR_CTL)
#define SMIF_DEVICE_IDX_RD_MODE_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).RD_MODE_CTL)
#define SMIF_DEVICE_IDX_RD_DUMMY_CTL(base, deviceIndex)    (SMIF_DEVICE_IDX(base, deviceIndex).RD_DUMMY_CTL)
#define SMIF_DEVICE_IDX_RD_DATA_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).RD_DATA_CTL)
#define SMIF_DEVICE_IDX_WR_CMD_CTL(base, deviceIndex)      (SMIF_DEVICE_IDX(base, deviceIndex).WR_CMD_CTL)
#define SMIF_DEVICE_IDX_WR_ADDR_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).WR_ADDR_CTL)
#define SMIF_DEVICE_IDX_WR_MODE_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).WR_MODE_CTL)
#define SMIF_DEVICE_IDX_WR_DUMMY_CTL(base, deviceIndex)    (SMIF_DEVICE_IDX(base, deviceIndex).WR_DUMMY_CTL)
#define SMIF_DEVICE_IDX_WR_DATA_CTL(base, deviceIndex)     (SMIF_DEVICE_IDX(base, deviceIndex).WR_DATA_CTL)

#define SMIF_CTL(base)                      (((SMIF_Type *)(base))->CTL)
#define SMIF_STATUS(base)                   (((SMIF_Type *)(base))->STATUS)
#define SMIF_TX_DATA_FIFO_CTL(base)         (((SMIF_Type *)(base))->TX_DATA_FIFO_CTL)
#define SMIF_RX_DATA_MMIO_FIFO_CTL(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_CTL)
#define SMIF_TX_DATA_FIFO_WR1(base)         (((SMIF_Type *)(base))->TX_DATA_FIFO_WR1)
#define SMIF_TX_DATA_FIFO_WR2(base)         (((SMIF_Type *)(base))->TX_DATA_FIFO_WR2)
#define SMIF_TX_DATA_FIFO_WR4(base)         (((SMIF_Type *)(base))->TX_DATA_FIFO_WR4)
#define SMIF_TX_DATA_FIFO_WR1ODD(base)      (((SMIF_Type *)(base))->TX_DATA_FIFO_WR1ODD)
#define SMIF_RX_DATA_FIFO_STATUS(base)        (((SMIF_Type *)(base))->RX_DATA_FIFO_STATUS)
#define SMIF_RX_DATA_MMIO_FIFO_STATUS(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_STATUS)
#define SMIF_RX_DATA_MMIO_FIFO_RD1(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_RD1)
#define SMIF_RX_DATA_MMIO_FIFO_RD2(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_RD2)
#define SMIF_RX_DATA_MMIO_FIFO_RD4(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_RD4)
#define SMIF_RX_DATA_MMIO_FIFO_RD1_SILENT(base)    (((SMIF_Type *)(base))->RX_DATA_MMIO_FIFO_RD1_SILENT)
#define SMIF_TX_CMD_FIFO_WR(base)           (((SMIF_Type *)(base))->TX_CMD_FIFO_WR)
#define SMIF_TX_CMD_FIFO_STATUS(base)       (((SMIF_Type *)(base))->TX_CMD_FIFO_STATUS)
#define SMIF_TX_DATA_FIFO_STATUS(base)      (((SMIF_Type *)(base))->TX_DATA_FIFO_STATUS)
#define SMIF_INTR(base)                     (((SMIF_Type *)(base))->INTR)
#define SMIF_INTR_SET(base)                 (((SMIF_Type *)(base))->INTR_SET)
#define SMIF_INTR_MASK(base)                (((SMIF_Type *)(base))->INTR_MASK)
#define SMIF_INTR_MASKED(base)              (((SMIF_Type *)(base))->INTR_MASKED)
#define SMIF_CRYPTO_INPUT0(base)            (((SMIF_Type *)(base))->CRYPTO_INPUT0)
#define SMIF_CRYPTO_INPUT1(base)            (((SMIF_Type *)(base))->CRYPTO_INPUT1)
#define SMIF_CRYPTO_INPUT2(base)            (((SMIF_Type *)(base))->CRYPTO_INPUT2)
#define SMIF_CRYPTO_INPUT3(base)            (((SMIF_Type *)(base))->CRYPTO_INPUT3)
#define SMIF_CRYPTO_KEY0(base)              (((SMIF_Type *)(base))->CRYPTO_KEY0)
#define SMIF_CRYPTO_KEY1(base)              (((SMIF_Type *)(base))->CRYPTO_KEY1)
#define SMIF_CRYPTO_KEY2(base)              (((SMIF_Type *)(base))->CRYPTO_KEY2)
#define SMIF_CRYPTO_KEY3(base)              (((SMIF_Type *)(base))->CRYPTO_KEY3)
#define SMIF_CRYPTO_OUTPUT0(base)           (((SMIF_Type *)(base))->CRYPTO_OUTPUT0)
#define SMIF_CRYPTO_OUTPUT1(base)           (((SMIF_Type *)(base))->CRYPTO_OUTPUT1)
#define SMIF_CRYPTO_OUTPUT2(base)           (((SMIF_Type *)(base))->CRYPTO_OUTPUT2)
#define SMIF_CRYPTO_OUTPUT3(base)           (((SMIF_Type *)(base))->CRYPTO_OUTPUT3)
#define SMIF_CRYPTO_CMD(base)               (((SMIF_Type *)(base))->CRYPTO_CMD)
#define SMIF_SLOW_CA_CTL(base)              (((SMIF_Type *)(base))->SLOW_CA_CTL)
#define SMIF_FAST_CA_CTL(base)              (((SMIF_Type *)(base))->FAST_CA_CTL)
#define SMIF_SLOW_CA_CMD(base)              (((SMIF_Type *)(base))->SLOW_CA_CMD)
#define SMIF_FAST_CA_CMD(base)              (((SMIF_Type *)(base))->FAST_CA_CMD)


/*******************************************************************************
*                DW
*******************************************************************************/

#define CY_DW                               (0UL)
#define CY_DW_CRC                           (1UL)
#define CY_DW0_BASE                         DW0
#define CY_DW1_BASE                         DW1
#define CY_DW0_CH_NR                        CPUSS_DW0_CH_NR
#define CY_DW1_CH_NR                        CPUSS_DW1_CH_NR

#define CY_DW_CH_CTL_PRIO_Pos               ((uint32_t)(DW_CH_STRUCT_CH_CTL_PRIO_Pos))
#define CY_DW_CH_CTL_PRIO_Msk               ((uint32_t)(0x3UL << CY_DW_CH_CTL_PRIO_Pos))
#define CY_DW_CH_CTL_PREEMPTABLE_Pos        ((uint32_t)(DW_CH_STRUCT_CH_CTL_PREEMPTABLE_Pos))
#define CY_DW_CH_CTL_PREEMPTABLE_Msk        ((uint32_t)(0x1UL << CY_DW_CH_CTL_PREEMPTABLE_Pos))
#define CY_DW_STATUS_CH_IDX_Pos             ((uint32_t)(DW_STATUS_CH_IDX_Pos))
#define CY_DW_STATUS_CH_IDX_Msk             (DW_STATUS_CH_IDX_Msk)

#define DW_CTL(base)                        (((DW_Type*)(base))->CTL)
#define DW_STATUS(base)                     (((DW_Type const*)(base))->STATUS)
#define DW_DESCR_SRC(base)                  (((DW_Type*)(base))->ACT_DESCR_SRC)
#define DW_DESCR_DST(base)                  (((DW_Type*)(base))->ACT_DESCR_DST)

#define DW_CRC_CTL(base)                    (((DW_Type*)(base))->CRC_CTL)
#define DW_CRC_DATA_CTL(base)               (((DW_Type*)(base))->CRC_DATA_CTL)
#define DW_CRC_REM_CTL(base)                (((DW_Type*)(base))->CRC_REM_CTL)
#define DW_CRC_POL_CTL(base)                (((DW_Type*)(base))->CRC_POL_CTL)
#define DW_CRC_LFSR_CTL(base)               (((DW_Type*)(base))->CRC_LFSR_CTL)

#define DW_CH_OFFSET                        (uint32_t)(offsetof(DW_Type, CH_STRUCT))
#define DW_CH_SIZE                            (uint32_t)(sizeof(DW_CH_STRUCT_Type))

#define DW_CH(base, chan)                    ((DW_CH_STRUCT_Type*)((uint32_t)(base) + DW_CH_OFFSET + (chan * DW_CH_SIZE)))
#define DW_CH_CTL(base, chan)               (DW_CH((base), (chan))->CH_CTL)
#define DW_CH_STATUS(base, chan)            (DW_CH((base), (chan))->CH_STATUS)
#define DW_CH_IDX(base, chan)               (DW_CH((base), (chan))->CH_IDX)
#define DW_CH_CURR_PTR(base, chan)          (DW_CH((base), (chan))->CH_CURR_PTR)

#define DW_CH_INTR(base, chan)              (DW_CH((base), (chan))->INTR)
#define DW_CH_INTR_SET(base, chan)          (DW_CH((base), (chan))->INTR_SET)
#define DW_CH_INTR_MASK(base, chan)         (DW_CH((base), (chan))->INTR_MASK)
#define DW_CH_INTR_MASKED(base, chan)       (DW_CH((base), (chan))->INTR_MASKED)

#define DW_V2_CRC_CTL_DATA_REVERSE_Msk DW_CRC_CTL_DATA_REVERSE_Msk
#define DW_V2_CRC_CTL_REM_REVERSE_Msk DW_CRC_CTL_REM_REVERSE_Msk
#define DW_V2_CRC_DATA_CTL_DATA_XOR_Msk DW_CRC_DATA_CTL_DATA_XOR_Msk
#define DW_V2_CRC_REM_CTL_REM_XOR_Msk DW_CRC_REM_CTL_REM_XOR_Msk
#define DW_V2_CRC_POL_CTL_POLYNOMIAL_Msk DW_CRC_POL_CTL_POLYNOMIAL_Msk
#define DW_V2_CRC_LFSR_CTL_LFSR32_Msk DW_CRC_LFSR_CTL_LFSR32_Msk
#define DW_V2_CRC_CTL_DATA_REVERSE_Pos DW_CRC_CTL_DATA_REVERSE_Pos
#define DW_V2_CRC_CTL_REM_REVERSE_Pos DW_CRC_CTL_REM_REVERSE_Pos
#define DW_V2_CRC_DATA_CTL_DATA_XOR_Pos DW_CRC_DATA_CTL_DATA_XOR_Pos
#define DW_V2_CRC_REM_CTL_REM_XOR_Pos DW_CRC_REM_CTL_REM_XOR_Pos
#define DW_V2_CRC_POL_CTL_POLYNOMIAL_Pos DW_CRC_POL_CTL_POLYNOMIAL_Pos
#define DW_V2_CRC_LFSR_CTL_LFSR32_Pos DW_CRC_LFSR_CTL_LFSR32_Pos


/*******************************************************************************
*                DMAC
*******************************************************************************/

#define CY_DMAC_CH_NR                       CPUSS_DMAC_CH_NR
#define DMAC_CTL(base)                      (((DMAC_Type*)(base))->CTL)
#define DMAC_ACTIVE(base)                   (((DMAC_Type const*)(base))->ACTIVE)
#define DMAC_CH(base, chan)                 (&(((DMAC_Type*)(base))->CH[(chan)]))
#define DMAC_CH_CTL(base, chan)             (DMAC_CH(base, chan)->CTL)
#define DMAC_CH_IDX(base, chan)             (DMAC_CH(base, chan)->IDX)
#define DMAC_CH_CURR(base, chan)            (DMAC_CH(base, chan)->CURR)
#define DMAC_CH_DESCR_SRC(base, chan)       (DMAC_CH(base, chan)->DESCR_SRC)
#define DMAC_CH_DESCR_DST(base, chan)       (DMAC_CH(base, chan)->DESCR_DST)
#define DMAC_CH_INTR(base, chan)            (DMAC_CH(base, chan)->INTR)
#define DMAC_CH_INTR_SET(base, chan)        (DMAC_CH(base, chan)->INTR_SET)
#define DMAC_CH_INTR_MASK(base, chan)       (DMAC_CH(base, chan)->INTR_MASK)
#define DMAC_CH_INTR_MASKED(base, chan)     (DMAC_CH(base, chan)->INTR_MASKED)

#define DMAC_CH_V2_INTR_COMPLETION_Msk DMAC_CH_INTR_COMPLETION_Msk
#define DMAC_CH_V2_INTR_COMPLETION_Pos DMAC_CH_INTR_COMPLETION_Pos
#define DMAC_CH_V2_INTR_SRC_BUS_ERROR_Msk DMAC_CH_INTR_SRC_BUS_ERROR_Msk
#define DMAC_CH_V2_INTR_SRC_BUS_ERROR_Pos DMAC_CH_INTR_SRC_BUS_ERROR_Pos
#define DMAC_CH_V2_INTR_DST_BUS_ERROR_Msk DMAC_CH_INTR_DST_BUS_ERROR_Msk
#define DMAC_CH_V2_INTR_DST_BUS_ERROR_Pos DMAC_CH_INTR_DST_BUS_ERROR_Pos
#define DMAC_CH_V2_INTR_SRC_MISAL_Msk DMAC_CH_INTR_SRC_MISAL_Msk
#define DMAC_CH_V2_INTR_SRC_MISAL_Pos DMAC_CH_INTR_SRC_MISAL_Pos
#define DMAC_CH_V2_INTR_DST_MISAL_Msk DMAC_CH_INTR_DST_MISAL_Msk
#define DMAC_CH_V2_INTR_DST_MISAL_Pos DMAC_CH_INTR_DST_MISAL_Pos
#define DMAC_CH_V2_INTR_CURR_PTR_NULL_Msk DMAC_CH_INTR_CURR_PTR_NULL_Msk
#define DMAC_CH_V2_INTR_CURR_PTR_NULL_Pos DMAC_CH_INTR_CURR_PTR_NULL_Pos
#define DMAC_CH_V2_INTR_ACTIVE_CH_DISABLED_Msk DMAC_CH_INTR_ACTIVE_CH_DISABLED_Msk
#define DMAC_CH_V2_INTR_ACTIVE_CH_DISABLED_Pos DMAC_CH_INTR_ACTIVE_CH_DISABLED_Pos
#define DMAC_CH_V2_INTR_DESCR_BUS_ERROR_Msk DMAC_CH_INTR_DESCR_BUS_ERROR_Msk
#define DMAC_CH_V2_INTR_DESCR_BUS_ERROR_Pos DMAC_CH_INTR_DESCR_BUS_ERROR_Pos
#define DMAC_V2_CTL_ENABLED_Msk DMAC_CTL_ENABLED_Msk
#define DMAC_V2_CTL_ENABLED_Pos DMAC_CTL_ENABLED_Pos
#define DMAC_V2_ACTIVE_ACTIVE_Msk DMAC_ACTIVE_ACTIVE_Msk
#define DMAC_V2_ACTIVE_ACTIVE_Pos DMAC_ACTIVE_ACTIVE_Pos
#define DMAC_CH_V2_DESCR_CTL_INTR_TYPE_Msk DMAC_CH_DESCR_CTL_INTR_TYPE_Msk
#define DMAC_CH_V2_DESCR_CTL_INTR_TYPE_Pos DMAC_CH_DESCR_CTL_INTR_TYPE_Pos
#define DMAC_CH_V2_DESCR_CTL_TR_IN_TYPE_Msk DMAC_CH_DESCR_CTL_TR_IN_TYPE_Msk
#define DMAC_CH_V2_DESCR_CTL_TR_IN_TYPE_Pos DMAC_CH_DESCR_CTL_TR_IN_TYPE_Pos
#define DMAC_CH_V2_DESCR_CTL_TR_OUT_TYPE_Msk DMAC_CH_DESCR_CTL_TR_OUT_TYPE_Msk
#define DMAC_CH_V2_DESCR_CTL_TR_OUT_TYPE_Pos DMAC_CH_DESCR_CTL_TR_OUT_TYPE_Pos
#define DMAC_CH_V2_DESCR_CTL_DATA_SIZE_Msk DMAC_CH_DESCR_CTL_DATA_SIZE_Msk
#define DMAC_CH_V2_DESCR_CTL_DATA_SIZE_Pos DMAC_CH_DESCR_CTL_DATA_SIZE_Pos
#define DMAC_CH_V2_DESCR_CTL_SRC_TRANSFER_SIZE_Msk DMAC_CH_DESCR_CTL_SRC_TRANSFER_SIZE_Msk
#define DMAC_CH_V2_DESCR_CTL_SRC_TRANSFER_SIZE_Pos DMAC_CH_DESCR_CTL_SRC_TRANSFER_SIZE_Pos
#define DMAC_CH_V2_DESCR_CTL_DST_TRANSFER_SIZE_Msk DMAC_CH_DESCR_CTL_DST_TRANSFER_SIZE_Msk
#define DMAC_CH_V2_DESCR_CTL_DST_TRANSFER_SIZE_Pos DMAC_CH_DESCR_CTL_DST_TRANSFER_SIZE_Pos
#define DMAC_CH_V2_DESCR_CTL_WAIT_FOR_DEACT_Msk DMAC_CH_DESCR_CTL_WAIT_FOR_DEACT_Msk
#define DMAC_CH_V2_DESCR_CTL_WAIT_FOR_DEACT_Pos DMAC_CH_DESCR_CTL_WAIT_FOR_DEACT_Pos
#define DMAC_CH_V2_DESCR_CTL_DESCR_TYPE_Msk DMAC_CH_DESCR_CTL_DESCR_TYPE_Msk
#define DMAC_CH_V2_DESCR_CTL_DESCR_TYPE_Pos DMAC_CH_DESCR_CTL_DESCR_TYPE_Pos
#define DMAC_CH_V2_DESCR_CTL_CH_DISABLE_Msk DMAC_CH_DESCR_CTL_CH_DISABLE_Msk
#define DMAC_CH_V2_DESCR_CTL_CH_DISABLE_Pos DMAC_CH_DESCR_CTL_CH_DISABLE_Pos
#define DMAC_CH_V2_DESCR_X_INCR_SRC_X_Msk DMAC_CH_DESCR_X_INCR_SRC_X_Msk
#define DMAC_CH_V2_DESCR_X_INCR_SRC_X_Pos DMAC_CH_DESCR_X_INCR_SRC_X_Pos
#define DMAC_CH_V2_DESCR_X_INCR_DST_X_Msk DMAC_CH_DESCR_X_INCR_DST_X_Msk
#define DMAC_CH_V2_DESCR_X_INCR_DST_X_Pos DMAC_CH_DESCR_X_INCR_DST_X_Pos
#define DMAC_CH_V2_DESCR_Y_SIZE_Y_COUNT_Msk DMAC_CH_DESCR_Y_SIZE_Y_COUNT_Msk
#define DMAC_CH_V2_DESCR_Y_SIZE_Y_COUNT_Pos DMAC_CH_DESCR_Y_SIZE_Y_COUNT_Pos
#define DMAC_CH_V2_DESCR_Y_INCR_SRC_Y_Msk DMAC_CH_DESCR_Y_INCR_SRC_Y_Msk
#define DMAC_CH_V2_DESCR_Y_INCR_SRC_Y_Pos DMAC_CH_DESCR_Y_INCR_SRC_Y_Pos
#define DMAC_CH_V2_DESCR_Y_INCR_DST_Y_Msk DMAC_CH_DESCR_Y_INCR_DST_Y_Msk
#define DMAC_CH_V2_DESCR_Y_INCR_DST_Y_Pos DMAC_CH_DESCR_Y_INCR_DST_Y_Pos
#define DMAC_CH_V2_CTL_ENABLED_Msk DMAC_CH_CTL_ENABLED_Msk
#define DMAC_CH_V2_CTL_ENABLED_Pos DMAC_CH_CTL_ENABLED_Pos
#define DMAC_CH_V2_CTL_PRIO_Msk DMAC_CH_CTL_PRIO_Msk
#define DMAC_CH_V2_CTL_PRIO_Pos DMAC_CH_CTL_PRIO_Pos
#define DMAC_CH_V2_IDX_X_Msk DMAC_CH_IDX_X_Msk
#define DMAC_CH_V2_IDX_X_Pos DMAC_CH_IDX_X_Pos
#define DMAC_CH_V2_IDX_Y_Msk DMAC_CH_IDX_Y_Msk
#define DMAC_CH_V2_IDX_Y_Pos DMAC_CH_IDX_Y_Pos
#define DMAC_CH_V2_DESCR_CTL_DATA_PREFETCH_Msk DMAC_CH_DESCR_CTL_DATA_PREFETCH_Msk
#define DMAC_CH_V2_DESCR_CTL_DATA_PREFETCH_Pos DMAC_CH_DESCR_CTL_DATA_PREFETCH_Pos
#define DMAC_CH_V2_CTL_B_Msk DMAC_CH_CTL_B_Msk
#define DMAC_CH_V2_CTL_B_Pos DMAC_CH_CTL_B_Pos
#define DMAC_CH_V2_DESCR_X_SIZE_X_COUNT_Msk DMAC_CH_DESCR_X_SIZE_X_COUNT_Msk
#define DMAC_CH_V2_DESCR_X_SIZE_X_COUNT_Pos DMAC_CH_DESCR_X_SIZE_X_COUNT_Pos


/*******************************************************************************
*                PERI
*******************************************************************************/
/*******************************************************************************
*                PERI PCLK
*******************************************************************************/

#define PERI_INSTANCE_COUNT                    (1U)

#ifndef PERI0_PCLK_GROUP_NR
#define PERI0_PCLK_GROUP_NR     PERI_PCLK_GROUP_NR
#endif

#ifndef PERI1_PCLK_GROUP_NR
#define PERI1_PCLK_GROUP_NR     (0U)
#endif


#ifndef PERI_PCLK0_BASE
#define PERI_PCLK0_BASE     PERI_PCLK_BASE
#endif

#ifndef PERI_PCLK1_BASE
#define PERI_PCLK1_BASE     0U
#endif

#if (PERI_INSTANCE_COUNT == 1U)
#define PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_8_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_8_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_8_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_8_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_8_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_8_VECT 0U


#define PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_VECT 0U


#define PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_5_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_5_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_5_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_5_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_5_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_5_VECT 0U

#define PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT PERI_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT
#define PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_24_5_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_24_5_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_24_5_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_24_5_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_24_5_VECT 0U
#define PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_24_5_VECT 0U

#define PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_8_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_8_VECT 0U


#define PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_VECT 0U


#define PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_5_VECT 0U


#define PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_24_5_VECT 0U
#define PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_24_5_VECT 0U

#endif

#define PERI_PCLK_PERI_NUM_Msk                 (0x000000FFU)
#define PERI_PCLK_GR_NUM_Msk                   (0x0000FF00U)
#define PERI_PCLK_GR_NUM_Pos                   (8U)
#define PERI_PCLK_PERIPHERAL_GROUP_NUM         (1UL << PERI_PCLK_GR_NUM_Pos)
#define PERI_PCLK_INST_NUM_Msk                 (0x00FF0000U)
#define PERI_PCLK_INST_NUM_Pos                 (16U)

#define PERI_PCLK_GR_NUM(instNum)              (((instNum) == 0U)? PERI0_PCLK_GROUP_NR : PERI1_PCLK_GROUP_NR)

#define PERI_PCLK1_OFFSET                      (PERI_PCLK1_BASE - PERI_PCLK0_BASE)
#define PERI_PCLK_REG_BASE(instNum)            ((PERI_PCLK_Type*)(PERI_PCLK0_BASE + ((instNum) * PERI_PCLK1_OFFSET)))

#define PERI_DIV_8_CTL(instNum, grNum, divNum)                   ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->DIV_8_CTL[divNum]
#define PERI_DIV_16_CTL(instNum, grNum, divNum)                  ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->DIV_16_CTL[divNum]
#define PERI_DIV_16_5_CTL(instNum, grNum, divNum)                ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->DIV_16_5_CTL[divNum]
#define PERI_DIV_24_5_CTL(instNum, grNum, divNum)                ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->DIV_24_5_CTL[divNum]
#define PERI_CLOCK_CTL(instNum, grNum, periNum)                  ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->CLOCK_CTL[periNum]
#define PERI_DIV_CMD(instNum, grNum)                             ((PERI_PCLK_GR_Type*) &PERI_PCLK_REG_BASE(instNum)->GR[grNum])->DIV_CMD

#define PERI_DIV_8_NR(instNum, grNum)           (((instNum) == 0U) ? \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT) |      \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT) << 8U)         |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_8_VECT) << 16U)        |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_8_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_8_VECT)) |        \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_8_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_8_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_8_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))) \
                                                  : \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_8_VECT) |      \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_8_VECT) << 8U)          |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_8_VECT) << 16U)         |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_8_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_8_VECT)) |         \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_8_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_8_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_8_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))))

#define PERI_DIV_16_NR(instNum, grNum)           (((instNum) == 0U) ? \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT) |      \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT) << 8U)         |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_VECT) << 16U)        |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_VECT)) |         \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))) \
                                                  : \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_VECT) |       \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_VECT) << 8U)          |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_VECT) << 16U)         |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_VECT)) |         \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))))

#define PERI_DIV_16_5_NR(instNum, grNum)         (((instNum) == 0U) ? \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT) |          \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_5_VECT) << 16U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_5_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_5_VECT)) |         \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_5_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_5_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_5_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))) \
                                                  : \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_16_5_VECT) |       \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_16_5_VECT) << 8U)          |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_16_5_VECT) << 16U)         |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_16_5_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_16_5_VECT)) |         \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_16_5_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_16_5_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_16_5_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))))

#define PERI_DIV_24_5_NR(instNum, grNum)         (((instNum) == 0U) ? \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT) |      \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT) << 8U)         |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_24_5_VECT) << 16U)        |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_24_5_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI0_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_24_5_VECT)) |         \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_24_5_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_24_5_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI0_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_24_5_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))) \
                                                  : \
                                                  (((grNum) <= 3U) ? \
                                                  ((uint32_t)(((((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR0_GR_DIV_24_5_VECT) |       \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR1_GR_DIV_24_5_VECT) << 8U)          |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR2_GR_DIV_24_5_VECT) << 16U)         |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR3_GR_DIV_24_5_VECT) << 24U)) >> ((grNum) * 8UL)) & 0xFFUL)) \
                                                  : \
                                                  ((uint32_t)(((((PERI1_PERI_PCLK_PCLK_GROUP_NR4_GR_DIV_24_5_VECT)) |         \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR5_GR_DIV_24_5_VECT) << 8U)    |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR6_GR_DIV_24_5_VECT) << 16U)   |    \
                                                  (((uint32_t)PERI1_PERI_PCLK_PCLK_GROUP_NR7_GR_DIV_24_5_VECT) << 24U)) >> (((uint32_t)(grNum) - 4UL) * 8UL)) & 0xFFUL))))

/* PERI_PCLK_GR.DIV_CMD */
#define CY_PERI_DIV_CMD_DIV_SEL_Pos             PERI_PCLK_GR_DIV_CMD_DIV_SEL_Pos
#define CY_PERI_DIV_CMD_DIV_SEL_Msk             PERI_PCLK_GR_DIV_CMD_DIV_SEL_Msk
#define CY_PERI_DIV_CMD_TYPE_SEL_Pos            PERI_PCLK_GR_DIV_CMD_TYPE_SEL_Pos
#define CY_PERI_DIV_CMD_TYPE_SEL_Msk            PERI_PCLK_GR_DIV_CMD_TYPE_SEL_Msk
#define CY_PERI_DIV_CMD_PA_DIV_SEL_Pos          PERI_PCLK_GR_DIV_CMD_PA_DIV_SEL_Pos
#define CY_PERI_DIV_CMD_PA_DIV_SEL_Msk          PERI_PCLK_GR_DIV_CMD_PA_DIV_SEL_Msk
#define CY_PERI_DIV_CMD_PA_TYPE_SEL_Pos         PERI_PCLK_GR_DIV_CMD_PA_TYPE_SEL_Pos
#define CY_PERI_DIV_CMD_PA_TYPE_SEL_Msk         PERI_PCLK_GR_DIV_CMD_PA_TYPE_SEL_Msk
#define CY_PERI_DIV_CMD_DISABLE_Pos             PERI_PCLK_GR_DIV_CMD_DISABLE_Pos
#define CY_PERI_DIV_CMD_DISABLE_Msk             PERI_PCLK_GR_DIV_CMD_DISABLE_Msk
#define CY_PERI_DIV_CMD_ENABLE_Pos              PERI_PCLK_GR_DIV_CMD_ENABLE_Pos
#define CY_PERI_DIV_CMD_ENABLE_Msk              PERI_PCLK_GR_DIV_CMD_ENABLE_Msk


#define PERI_DIV_CMD_DIV_SEL_Pos                PERI_PCLK_GR_DIV_CMD_DIV_SEL_Pos
#define PERI_DIV_CMD_DIV_SEL_Msk                PERI_PCLK_GR_DIV_CMD_DIV_SEL_Msk
#define PERI_DIV_CMD_TYPE_SEL_Pos               PERI_PCLK_GR_DIV_CMD_TYPE_SEL_Pos
#define PERI_DIV_CMD_TYPE_SEL_Msk               PERI_PCLK_GR_DIV_CMD_TYPE_SEL_Msk
#define PERI_DIV_CMD_PA_DIV_SEL_Pos             PERI_PCLK_GR_DIV_CMD_PA_DIV_SEL_Pos
#define PERI_DIV_CMD_PA_DIV_SEL_Msk             PERI_PCLK_GR_DIV_CMD_PA_DIV_SEL_Msk
#define PERI_DIV_CMD_PA_TYPE_SEL_Pos            PERI_PCLK_GR_DIV_CMD_PA_TYPE_SEL_Pos
#define PERI_DIV_CMD_PA_TYPE_SEL_Msk            PERI_PCLK_GR_DIV_CMD_PA_TYPE_SEL_Msk
#define PERI_DIV_CMD_DISABLE_Pos                PERI_PCLK_GR_DIV_CMD_DISABLE_Pos
#define PERI_DIV_CMD_DISABLE_Msk                PERI_PCLK_GR_DIV_CMD_DISABLE_Msk
#define PERI_DIV_CMD_ENABLE_Pos                 PERI_PCLK_GR_DIV_CMD_ENABLE_Pos
#define PERI_DIV_CMD_ENABLE_Msk                 PERI_PCLK_GR_DIV_CMD_ENABLE_Msk

/* PERI_PCLK_GR.CLOCK_CTL */
#define CY_PERI_CLOCK_CTL_DIV_SEL_Pos           PERI_PCLK_GR_CLOCK_CTL_DIV_SEL_Pos
#define CY_PERI_CLOCK_CTL_DIV_SEL_Msk           PERI_PCLK_GR_CLOCK_CTL_DIV_SEL_Msk
#define CY_PERI_CLOCK_CTL_TYPE_SEL_Pos          PERI_PCLK_GR_CLOCK_CTL_TYPE_SEL_Pos
#define CY_PERI_CLOCK_CTL_TYPE_SEL_Msk          PERI_PCLK_GR_CLOCK_CTL_TYPE_SEL_Msk
/* PERI.DIV_8_CTL */
#define PERI_DIV_8_CTL_EN_Pos                   PERI_PCLK_GR_DIV_8_CTL_EN_Pos
#define PERI_DIV_8_CTL_EN_Msk                   PERI_PCLK_GR_DIV_8_CTL_EN_Msk
#define PERI_DIV_8_CTL_INT8_DIV_Pos             PERI_PCLK_GR_DIV_8_CTL_INT8_DIV_Pos
#define PERI_DIV_8_CTL_INT8_DIV_Msk             PERI_PCLK_GR_DIV_8_CTL_INT8_DIV_Msk
/* PERI.DIV_16_CTL */
#define PERI_DIV_16_CTL_EN_Pos                  PERI_PCLK_GR_DIV_16_CTL_EN_Pos
#define PERI_DIV_16_CTL_EN_Msk                  PERI_PCLK_GR_DIV_16_CTL_EN_Msk
#define PERI_DIV_16_CTL_INT16_DIV_Pos           PERI_PCLK_GR_DIV_16_CTL_INT16_DIV_Pos
#define PERI_DIV_16_CTL_INT16_DIV_Msk           PERI_PCLK_GR_DIV_16_CTL_INT16_DIV_Msk
/* PERI.DIV_16_5_CTL */
#define PERI_DIV_16_5_CTL_EN_Pos                PERI_PCLK_GR_DIV_16_5_CTL_EN_Pos
#define PERI_DIV_16_5_CTL_EN_Msk                PERI_PCLK_GR_DIV_16_5_CTL_EN_Msk
#define PERI_DIV_16_5_CTL_FRAC5_DIV_Pos         PERI_PCLK_GR_DIV_16_5_CTL_FRAC5_DIV_Pos
#define PERI_DIV_16_5_CTL_FRAC5_DIV_Msk         PERI_PCLK_GR_DIV_16_5_CTL_FRAC5_DIV_Msk
#define PERI_DIV_16_5_CTL_INT16_DIV_Pos         PERI_PCLK_GR_DIV_16_5_CTL_INT16_DIV_Pos
#define PERI_DIV_16_5_CTL_INT16_DIV_Msk         PERI_PCLK_GR_DIV_16_5_CTL_INT16_DIV_Msk
/* PERI.DIV_24_5_CTL */
#define PERI_DIV_24_5_CTL_EN_Pos                PERI_PCLK_GR_DIV_24_5_CTL_EN_Pos
#define PERI_DIV_24_5_CTL_EN_Msk                PERI_PCLK_GR_DIV_24_5_CTL_EN_Msk
#define PERI_DIV_24_5_CTL_FRAC5_DIV_Pos         PERI_PCLK_GR_DIV_24_5_CTL_FRAC5_DIV_Pos
#define PERI_DIV_24_5_CTL_FRAC5_DIV_Msk         PERI_PCLK_GR_DIV_24_5_CTL_FRAC5_DIV_Msk
#define PERI_DIV_24_5_CTL_INT24_DIV_Pos         PERI_PCLK_GR_DIV_24_5_CTL_INT24_DIV_Pos
#define PERI_DIV_24_5_CTL_INT24_DIV_Msk         PERI_PCLK_GR_DIV_24_5_CTL_INT24_DIV_Msk

/*******************************************************************************
*                PERI-GROUP
*******************************************************************************/
#define CY_PERI_GROUP_NR                        10

#ifndef PERI0_BASE
#define PERI0_BASE PERI_BASE
#endif

#ifndef PERI1_BASE
#define PERI1_BASE 0U
#endif


#define PERI_GR_OFFSET                      (PERI1_BASE - PERI0_BASE)
#define PERI_GR_REG_BASE(instNum)           ((PERI_Type*)(PERI0_BASE + ((instNum) * PERI_GR_OFFSET)))

#define PERI_GR_INST_NUM_Msk                 (0x0000FF00U)
#define PERI_GR_INST_NUM_Pos                 (8U)


#define PERI_GR_CLOCK_CTL(instNum, grNum)   ((PERI_GR_Type*) &PERI_GR_REG_BASE(instNum)->GR[grNum])->CLOCK_CTL
#define PERI_GR_SL_CTL(instNum, grNum)      ((PERI_GR_Type*) &PERI_GR_REG_BASE(instNum)->GR[grNum])->SL_CTL
#define PERI_GR_SL_CTL2(instNum, grNum)     ((PERI_GR_Type*) &PERI_GR_REG_BASE(instNum)->GR[grNum])->SL_CTL2
#define PERI_GR_SL_CTL3(instNum, grNum)     ((PERI_GR_Type*) &PERI_GR_REG_BASE(instNum)->GR[grNum])->SL_CTL3


/* CLK_HF* to PERI PCLK Group Mapping */
#define PERI0_PCLK_GR_NUM_0_CLK_HF_NUM              (0U)
#define PERI0_PCLK_GR_NUM_1_CLK_HF_NUM              (2U)

/*******************************************************************************
*                PERI-TR
*******************************************************************************/
#define PERI_TR_CMD                         (((PERI_Type*) (PERI_BASE))->TR_CMD)
#define PERI_TR_GR_TR_CTL(group, trCtl)     (*(volatile uint32_t*) ((uint32_t)PERI_BASE+ (uint32_t)offsetof(PERI_Type,TR_GR) + \
                                            ((group) * (uint32_t)sizeof(PERI_TR_GR_Type)) + \
                                            ((trCtl) * (uint32_t)sizeof(uint32_t))))

#if defined (CY_IP_MXPERI)
#define PERI_TR_GR_TR_OUT_CTL_TR_SEL_Msk PERI_TR_GR_TR_CTL_TR_SEL_Msk
#define PERI_TR_GR_TR_OUT_CTL_TR_SEL_Pos PERI_TR_GR_TR_CTL_TR_SEL_Pos
#define CY_PERI_TR_CTL_SEL_Msk PERI_TR_GR_TR_CTL_TR_SEL_Msk
#define CY_PERI_TR_CTL_SEL_Pos PERI_TR_GR_TR_CTL_TR_SEL_Pos
#define PERI_V2_TR_CMD_OUT_SEL_Msk PERI_TR_CMD_OUT_SEL_Msk
#define PERI_V2_TR_CMD_OUT_SEL_Pos PERI_TR_CMD_OUT_SEL_Pos
#define PERI_V2_TR_CMD_GROUP_SEL_Msk PERI_TR_CMD_GROUP_SEL_Msk
#define PERI_V2_TR_CMD_GROUP_SEL_Pos PERI_TR_CMD_GROUP_SEL_Pos
#define CY_PERI_TR_CMD_GROUP_SEL_Msk PERI_TR_CMD_GROUP_SEL_Msk
#define CY_PERI_TR_CMD_GROUP_SEL_Pos PERI_TR_CMD_GROUP_SEL_Pos
#define CY_PERI_TR_CTL_SEL PERI_TR_GR_TR_CTL_TR_SEL
#define PERI_TR_GR_TR_OUT_CTL_TR_INV_Msk PERI_TR_GR_TR_CTL_TR_INV_Msk
#define PERI_TR_GR_TR_OUT_CTL_TR_INV_Pos PERI_TR_GR_TR_CTL_TR_INV_Pos
#define PERI_TR_GR_TR_OUT_CTL_TR_EDGE_Msk PERI_TR_GR_TR_CTL_TR_EDGE_Msk
#define PERI_TR_GR_TR_OUT_CTL_TR_EDGE_Pos PERI_TR_GR_TR_CTL_TR_EDGE_Pos
#define PERI_V2_TR_CMD_TR_EDGE_Msk PERI_TR_CMD_TR_EDGE_Msk
#define PERI_V2_TR_CMD_TR_EDGE_Pos PERI_TR_CMD_TR_EDGE_Pos
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_INV_Msk PERI_TR_1TO1_GR_TR_CTL_TR_INV_Msk
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_INV_Pos PERI_TR_1TO1_GR_TR_CTL_TR_INV_Pos
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_EDGE_Msk PERI_TR_1TO1_GR_TR_CTL_TR_EDGE_Msk
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_EDGE_Pos PERI_TR_1TO1_GR_TR_CTL_TR_EDGE_Pos
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_SEL_Msk PERI_TR_1TO1_GR_TR_CTL_TR_SEL_Msk
#define PERI_TR_1TO1_GR_V2_TR_CTL_TR_SEL_Pos PERI_TR_1TO1_GR_TR_CTL_TR_SEL_Pos
#define PERI_TR_GR_V2_TR_CTL_DBG_FREEZE_EN_Msk PERI_TR_GR_TR_CTL_DBG_FREEZE_EN_Msk
#define PERI_TR_GR_V2_TR_CTL_DBG_FREEZE_EN_Pos PERI_TR_GR_TR_CTL_DBG_FREEZE_EN_Pos
#define CY_PERI_V1 0U
#define PERI_TR_CMD_COUNT_Pos 0UL
#define PERI_TR_CMD_COUNT_Msk 0UL
#endif /* CY_IP_MXPERI */

#define PERI_MS_PPU_PR_SL_ADDR(base)        (((PERI_MS_PPU_PR_Type *) (base))->SL_ADDR)
#define PERI_MS_PPU_PR_SL_SIZE(base)        (((PERI_MS_PPU_PR_Type *) (base))->SL_SIZE)
#define PERI_MS_PPU_PR_MS_ATT(base)         ((volatile uint32_t *) &(((PERI_MS_PPU_PR_Type *)(base))->MS_ATT0))
#define PERI_MS_PPU_PR_SL_ATT(base)         ((volatile uint32_t *) &(((PERI_MS_PPU_PR_Type *)(base))->SL_ATT0))
#define PERI_MS_PPU_FX_MS_ATT(base)         ((volatile uint32_t *) &(((PERI_MS_PPU_FX_Type *)(base))->MS_ATT0))
#define PERI_MS_PPU_FX_SL_ATT(base)         ((volatile uint32_t *) &(((PERI_MS_PPU_FX_Type *)(base))->SL_ATT0))


/*******************************************************************************
*                PROT
*******************************************************************************/
#define CY_PROT_BASE                        ((uint32_t)PROT_BASE)
#define CY_PROT_PC_MAX                      (8UL)
#define CY_PROT_BUS_MASTER_MASK             (0xFE7FUL)
#define PROT_MPU_MS_CTL(mpu)                (((PROT_Type*)CY_PROT_BASE)->CYMPU[(mpu)].MS_CTL)
#define PROT_MPU_MPU_STRUCT_ADDR(base)      (((PROT_MPU_MPU_STRUCT_Type *) (base))->ADDR)
#define PROT_MPU_MPU_STRUCT_ATT(base)       (((PROT_MPU_MPU_STRUCT_Type *) (base))->ATT)
#define PROT_SMPU_SMPU_STRUCT_ADDR0(base)   (((PROT_SMPU_SMPU_STRUCT_Type *) (base))->ADDR0)
#define PROT_SMPU_SMPU_STRUCT_ADDR1(base)   (((PROT_SMPU_SMPU_STRUCT_Type *) (base))->ADDR1)
#define PROT_SMPU_SMPU_STRUCT_ATT0(base)    (((PROT_SMPU_SMPU_STRUCT_Type *) (base))->ATT0)
#define PROT_SMPU_SMPU_STRUCT_ATT1(base)    (((PROT_SMPU_SMPU_STRUCT_Type *) (base))->ATT1)
#define PROT_SMPU_SMPU_STRUCT_IDX_ATT0(stcIdx)    (((PROT_SMPU_Type *) CY_PROT_BASE)->SMPU_STRUCT[(stcIdx)].ATT0)
#define PROT_SMPU_SMPU_STRUCT_IDX_ATT1(stcIdx)    (((PROT_SMPU_Type *) CY_PROT_BASE)->SMPU_STRUCT[(stcIdx)].ATT1)
#define PROT_SMPU_SMPU_STRUCT_IDX(stcIdx)         (((PROT_SMPU_SMPU_STRUCT_Type *) &((PROT_SMPU_Type *) CY_PROT_BASE)->SMPU_STRUCT[(stcIdx)]))


/*******************************************************************************
*                IOSS
*******************************************************************************/

#define CY_GPIO_BASE                       ((uint32_t)GPIO_BASE)

#define GPIO_INTR_CAUSE0                   ((GPIO)->INTR_CAUSE0)
#define GPIO_INTR_CAUSE1                   ((GPIO)->INTR_CAUSE1)
#define GPIO_INTR_CAUSE2                   ((GPIO)->INTR_CAUSE2)
#define GPIO_INTR_CAUSE3                   ((GPIO)->INTR_CAUSE3)

#define GPIO_PRT_OUT(base)                 (((GPIO_PRT_Type*)(base))->OUT)
#define GPIO_PRT_OUT_CLR(base)             (((GPIO_PRT_Type*)(base))->OUT_CLR)
#define GPIO_PRT_OUT_SET(base)             (((GPIO_PRT_Type*)(base))->OUT_SET)
#define GPIO_PRT_OUT_INV(base)             (((GPIO_PRT_Type*)(base))->OUT_INV)
#define GPIO_PRT_IN(base)                  (((GPIO_PRT_Type*)(base))->IN)
#define GPIO_PRT_INTR(base)                (((GPIO_PRT_Type*)(base))->INTR)
#define GPIO_PRT_INTR_MASK(base)           (((GPIO_PRT_Type*)(base))->INTR_MASK)
#define GPIO_PRT_INTR_MASKED(base)         (((GPIO_PRT_Type*)(base))->INTR_MASKED)
#define GPIO_PRT_INTR_SET(base)            (((GPIO_PRT_Type*)(base))->INTR_SET)
#define GPIO_PRT_INTR_CFG(base)            (((GPIO_PRT_Type*)(base))->INTR_CFG)
#define GPIO_PRT_CFG(base)                 (((GPIO_PRT_Type*)(base))->CFG)
#define GPIO_PRT_CFG_IN(base)              (((GPIO_PRT_Type*)(base))->CFG_IN)
#define GPIO_PRT_CFG_OUT(base)             (((GPIO_PRT_Type*)(base))->CFG_OUT)
#define GPIO_PRT_CFG_SIO(base)             (((GPIO_PRT_Type*)(base))->CFG_SIO)
#define GPIO_PRT_CFG_IN_AUTOLVL(base)      (((GPIO_PRT_Type*)(base))->CFG_IN_AUTOLVL)

#define CY_HSIOM_BASE                      ((uint32_t)HSIOM_BASE)

#define HSIOM_PRT_PORT_SEL0(base)          (((HSIOM_PRT_Type *)(base))->PORT_SEL0)
#define HSIOM_PRT_PORT_SEL1(base)          (((HSIOM_PRT_Type *)(base))->PORT_SEL1)

#define HSIOM_AMUX_SPLIT_CTL(switchCtrl)    (((HSIOM_Type *)HSIOM_BASE)->AMUX_SPLIT_CTL[switchCtrl])

#define ioss_interrupts_gpio_0_IRQn         ioss_interrupts_gpio_dpslp_0_IRQn
#define ioss_interrupts_gpio_1_IRQn         ioss_interrupts_gpio_dpslp_1_IRQn
#define ioss_interrupts_gpio_2_IRQn         ioss_interrupts_gpio_dpslp_2_IRQn
#define ioss_interrupts_gpio_3_IRQn         ioss_interrupts_gpio_dpslp_3_IRQn
#define ioss_interrupts_gpio_4_IRQn         ioss_interrupts_gpio_dpslp_4_IRQn
#define ioss_interrupts_gpio_5_IRQn         ioss_interrupts_gpio_dpslp_5_IRQn
#define ioss_interrupts_gpio_6_IRQn         ioss_interrupts_gpio_dpslp_6_IRQn
#define ioss_interrupts_gpio_7_IRQn         ioss_interrupts_gpio_dpslp_7_IRQn
#define ioss_interrupts_gpio_8_IRQn         ioss_interrupts_gpio_dpslp_8_IRQn
#define ioss_interrupts_gpio_9_IRQn         ioss_interrupts_gpio_dpslp_9_IRQn
#define ioss_interrupts_gpio_10_IRQn        ioss_interrupts_gpio_dpslp_10_IRQn
#define ioss_interrupts_gpio_11_IRQn        ioss_interrupts_gpio_dpslp_11_IRQn
#define ioss_interrupts_gpio_12_IRQn        ioss_interrupts_gpio_dpslp_12_IRQn
#define ioss_interrupts_gpio_13_IRQn        ioss_interrupts_gpio_dpslp_13_IRQn
#define ioss_interrupts_gpio_14_IRQn        ioss_interrupts_gpio_dpslp_14_IRQn
#define ioss_interrupts_gpio_15_IRQn        ioss_interrupts_gpio_dpslp_15_IRQn
#define ioss_interrupts_gpio_16_IRQn        ioss_interrupts_gpio_dpslp_16_IRQn
#define ioss_interrupts_gpio_17_IRQn        ioss_interrupts_gpio_dpslp_17_IRQn
#define ioss_interrupts_gpio_18_IRQn        ioss_interrupts_gpio_dpslp_18_IRQn
#define ioss_interrupts_gpio_19_IRQn        ioss_interrupts_gpio_dpslp_19_IRQn
#define ioss_interrupts_gpio_20_IRQn        ioss_interrupts_gpio_dpslp_20_IRQn
#define ioss_interrupts_gpio_21_IRQn        ioss_interrupts_gpio_dpslp_21_IRQn
#define ioss_interrupts_gpio_22_IRQn        ioss_interrupts_gpio_dpslp_22_IRQn
#define ioss_interrupts_gpio_23_IRQn        ioss_interrupts_gpio_dpslp_23_IRQn
#define ioss_interrupts_gpio_28_IRQn        ioss_interrupts_gpio_dpslp_28_IRQn
#define ioss_interrupts_gpio_29_IRQn        ioss_interrupts_gpio_dpslp_29_IRQn
#define ioss_interrupts_gpio_30_IRQn        ioss_interrupts_gpio_dpslp_30_IRQn
#define ioss_interrupts_gpio_31_IRQn        ioss_interrupts_gpio_dpslp_31_IRQn
#define ioss_interrupts_gpio_32_IRQn        ioss_interrupts_gpio_dpslp_32_IRQn
#define ioss_interrupts_gpio_24_IRQn        ioss_interrupts_gpio_act_24_IRQn
#define ioss_interrupts_gpio_25_IRQn        ioss_interrupts_gpio_act_25_IRQn
#define ioss_interrupts_gpio_26_IRQn        ioss_interrupts_gpio_act_26_IRQn
#define ioss_interrupts_gpio_27_IRQn        ioss_interrupts_gpio_act_27_IRQn
#define ioss_interrupts_gpio_33_IRQn        ioss_interrupts_gpio_act_33_IRQn
#define ioss_interrupts_gpio_34_IRQn        ioss_interrupts_gpio_act_34_IRQn

/*******************************************************************************
*                I2S
*******************************************************************************/
#if (defined(AUDIOSS_I2S) || defined(AUDIOSS0_I2S_I2S))
#define AUDIOSS_I2S_PRESENT
#endif

#define REG_I2S_CTL(base)                   (((I2S_Type*)(base))->CTL)
#define REG_I2S_CMD(base)                   (((I2S_Type*)(base))->CMD)
#define REG_I2S_CLOCK_CTL(base)             (((I2S_Type*)(base))->CLOCK_CTL)
#define REG_I2S_TR_CTL(base)                (((I2S_Type*)(base))->TR_CTL)
#define REG_I2S_TX_CTL(base)                (((I2S_Type*)(base))->TX_CTL)
#define REG_I2S_TX_FIFO_CTL(base)           (((I2S_Type*)(base))->TX_FIFO_CTL)
#define REG_I2S_TX_FIFO_STATUS(base)        (((I2S_Type*)(base))->TX_FIFO_STATUS)
#define REG_I2S_TX_FIFO_WR(base)            (((I2S_Type*)(base))->TX_FIFO_WR)
#define REG_I2S_TX_WATCHDOG(base)           (((I2S_Type*)(base))->TX_WATCHDOG)
#define REG_I2S_RX_CTL(base)                (((I2S_Type*)(base))->RX_CTL)
#define REG_I2S_RX_FIFO_CTL(base)           (((I2S_Type*)(base))->RX_FIFO_CTL)
#define REG_I2S_RX_FIFO_STATUS(base)        (((I2S_Type*)(base))->RX_FIFO_STATUS)
#define REG_I2S_RX_FIFO_RD(base)            (((I2S_Type*)(base))->RX_FIFO_RD)
#define REG_I2S_RX_FIFO_RD_SILENT(base)     (((I2S_Type*)(base))->RX_FIFO_RD_SILENT)
#define REG_I2S_RX_WATCHDOG(base)           (((I2S_Type*)(base))->RX_WATCHDOG)
#define REG_I2S_INTR(base)                  (((I2S_Type*)(base))->INTR)
#define REG_I2S_INTR_SET(base)              (((I2S_Type*)(base))->INTR_SET)
#define REG_I2S_INTR_MASK(base)             (((I2S_Type*)(base))->INTR_MASK)
#define REG_I2S_INTR_MASKED(base)           (((I2S_Type*)(base))->INTR_MASKED)



/*******************************************************************************
*                LCD
*******************************************************************************/

#define LCD_OCTET_NUM                       (8U) /* LCD_NUMPORTS - number of octets supporting up to 4 COMs */
#define LCD_OCTET_NUM_8                     (8U) /* LCD_NUMPORTS8 - number of octets supporting up to 8 COMs */
#define LCD_OCTET_NUM_16                    (0U) /* LCD_NUMPORTS16 - number of octets supporting up to 16 COMs */
#define LCD_COM_NUM                         (8U) /* LCD_CHIP_TOP_COM_NR - maximum number of commons */

#define LCD_ID(base)                        (((LCD_V1_Type*)(base))->ID)
#define LCD_CONTROL(base)                   (((LCD_V1_Type*)(base))->CONTROL)
#define LCD_DIVIDER(base)                   (((LCD_V1_Type*)(base))->DIVIDER)
#define LCD_DATA0(base)                     (((LCD_V1_Type*)(base))->DATA0)
#define LCD_DATA1(base)                     (((LCD_V1_Type*)(base))->DATA1)
#define LCD_DATA2(base)                     (((LCD_V1_Type*)(base))->DATA2)
#define LCD_DATA3(base)                     (((LCD_V1_Type*)(base))->DATA3)


/*******************************************************************************
*                IPC
*******************************************************************************/

#define CY_IPC_V1                              (0x20u > cy_device->ipcVersion) /* true if the IPC version is 1.x */

#define REG_IPC_STRUCT_ACQUIRE(base)           (((IPC_STRUCT_Type*)(base))->ACQUIRE)
#define REG_IPC_STRUCT_RELEASE(base)           (((IPC_STRUCT_Type*)(base))->RELEASE)
#define REG_IPC_STRUCT_NOTIFY(base)            (((IPC_STRUCT_Type*)(base))->NOTIFY)
#define REG_IPC_STRUCT_DATA(base)              (((IPC_STRUCT_Type*)(base))->DATA0)
#define REG_IPC_STRUCT_DATA1(base)             (((IPC_STRUCT_Type*)(base))->DATA1)
#define REG_IPC_STRUCT_LOCK_STATUS(base)       (*(volatile uint32_t*)((uint32_t)(base) + (uint32_t)offsetof(IPC_STRUCT_Type, LOCK_STATUS)))

#define REG_IPC_INTR_STRUCT_INTR(base)         (((IPC_INTR_STRUCT_Type*)(base))->INTR)
#define REG_IPC_INTR_STRUCT_INTR_SET(base)     (((IPC_INTR_STRUCT_Type*)(base))->INTR_SET)
#define REG_IPC_INTR_STRUCT_INTR_MASK(base)    (((IPC_INTR_STRUCT_Type*)(base))->INTR_MASK)
#define REG_IPC_INTR_STRUCT_INTR_MASKED(base)  (((IPC_INTR_STRUCT_Type*)(base))->INTR_MASKED)

#define CY_IPC_STRUCT_PTR(ipcIndex)            ((IPC_STRUCT_Type*)(IPC_BASE + (uint32_t)(sizeof(IPC_STRUCT_Type) * (ipcIndex))))
#define CY_IPC_INTR_STRUCT_PTR(ipcIntrIndex)   &(((IPC_Type *)IPC_BASE)->INTR_STRUCT[ipcIntrIndex])

#define CY_IPC_STRUCT_PTR_FOR_IP(ipcIndex, base)            ((IPC_STRUCT_Type*)((uint32_t)(base) + (sizeof(IPC_STRUCT_Type) * (ipcIndex))))
#define CY_IPC_INTR_STRUCT_PTR_FOR_IP(ipcIntrIndex, base)   &(((IPC_Type *)base)->INTR_STRUCT[ipcIntrIndex])

#define CY_IPC_CHANNELS                        (uint32_t)CPUSS_IPC_IPC_NR
#define CY_IPC_INTERRUPTS                      (uint32_t)CPUSS_IPC_IPC_IRQ_NR

/* IPC channel definitions  */
#define CY_IPC_CHAN_SYSCALL_CM0             (0UL)  /* System calls for the CM0 processor */
#define CY_IPC_CHAN_SYSCALL_CM7_0           (1UL)  /* System calls for the CM7_0 processor */
#if (CPUSS_CM7_1_PRESENT == 1)
#define CY_IPC_CHAN_SYSCALL_CM7_1           (2UL)  /* System calls for the CM7_1 processor */
#define CY_IPC_CHAN_SYSCALL_DAP             (3UL) /* System calls for the DAP */
#define CY_IPC_CHAN_SEMA                    (4UL) /* IPC data channel for the Semaphores */
#else
#define CY_IPC_CHAN_SYSCALL_CM7_1           (CY_IPC_CHANNELS)  /* This macro should not be used. This is defined only for compilation purpose */
#define CY_IPC_CHAN_SYSCALL_DAP             (2UL) /* System calls for the DAP */
#define CY_IPC_CHAN_SEMA                    (3UL) /* IPC data channel for the Semaphores */
#endif
#define CY_IPC_CHAN_USER                    (CY_IPC_CHAN_SEMA + 1UL)

/* IPC Notify interrupts definitions */
#define CY_IPC_INTR_SYSCALL1                (0UL)
#define CY_IPC_INTR_USER                    (CY_IPC_INTR_SYSCALL1 + 1UL)


/*******************************************************************************
*                CTB
*******************************************************************************/

#define CTBM_CTB_CTRL(base)                 (((CTBM_V1_Type *) (base))->CTB_CTRL)
#define CTBM_CTB_SW_DS_CTRL(base)           (((CTBM_V1_Type *) (base))->CTB_SW_DS_CTRL)
#define CTBM_CTB_SW_SQ_CTRL(base)           (((CTBM_V1_Type *) (base))->CTB_SW_SQ_CTRL)
#define CTBM_CTD_SW(base)                   (((CTBM_V1_Type *) (base))->CTD_SW)
#define CTBM_CTD_SW_CLEAR(base)             (((CTBM_V1_Type *) (base))->CTD_SW_CLEAR)
#define CTBM_COMP_STAT(base)                (((CTBM_V1_Type *) (base))->COMP_STAT)
#define CTBM_OA0_SW_CLEAR(base)             (((CTBM_V1_Type *) (base))->OA0_SW_CLEAR)
#define CTBM_OA1_SW_CLEAR(base)             (((CTBM_V1_Type *) (base))->OA1_SW_CLEAR)
#define CTBM_OA0_SW(base)                   (((CTBM_V1_Type *) (base))->OA0_SW)
#define CTBM_OA1_SW(base)                   (((CTBM_V1_Type *) (base))->OA1_SW)
#define CTBM_OA_RES0_CTRL(base)             (((CTBM_V1_Type *) (base))->OA_RES0_CTRL)
#define CTBM_OA_RES1_CTRL(base)             (((CTBM_V1_Type *) (base))->OA_RES1_CTRL)
#define CTBM_OA0_COMP_TRIM(base)            (((CTBM_V1_Type *) (base))->OA0_COMP_TRIM)
#define CTBM_OA1_COMP_TRIM(base)            (((CTBM_V1_Type *) (base))->OA1_COMP_TRIM)
#define CTBM_OA0_OFFSET_TRIM(base)          (((CTBM_V1_Type *) (base))->OA0_OFFSET_TRIM)
#define CTBM_OA1_OFFSET_TRIM(base)          (((CTBM_V1_Type *) (base))->OA1_OFFSET_TRIM)
#define CTBM_OA0_SLOPE_OFFSET_TRIM(base)    (((CTBM_V1_Type *) (base))->OA0_SLOPE_OFFSET_TRIM)
#define CTBM_OA1_SLOPE_OFFSET_TRIM(base)    (((CTBM_V1_Type *) (base))->OA1_SLOPE_OFFSET_TRIM)
#define CTBM_INTR(base)                     (((CTBM_V1_Type *) (base))->INTR)
#define CTBM_INTR_SET(base)                 (((CTBM_V1_Type *) (base))->INTR_SET)
#define CTBM_INTR_MASK(base)                (((CTBM_V1_Type *) (base))->INTR_MASK)
#define CTBM_INTR_MASKED(base)              (((CTBM_V1_Type *) (base))->INTR_MASKED)


/*******************************************************************************
*                CTDAC
*******************************************************************************/

#define CTDAC_CTDAC_CTRL(base)              (((CTDAC_V1_Type *) (base))->CTDAC_CTRL)
#define CTDAC_CTDAC_SW(base)                (((CTDAC_V1_Type *) (base))->CTDAC_SW)
#define CTDAC_CTDAC_SW_CLEAR(base)          (((CTDAC_V1_Type *) (base))->CTDAC_SW_CLEAR)
#define CTDAC_CTDAC_VAL(base)               (((CTDAC_V1_Type *) (base))->CTDAC_VAL)
#define CTDAC_CTDAC_VAL_NXT(base)           (((CTDAC_V1_Type *) (base))->CTDAC_VAL_NXT)
#define CTDAC_INTR(base)                    (((CTDAC_V1_Type *) (base))->INTR)
#define CTDAC_INTR_SET(base)                (((CTDAC_V1_Type *) (base))->INTR_SET)
#define CTDAC_INTR_MASK(base)               (((CTDAC_V1_Type *) (base))->INTR_MASK)
#define CTDAC_INTR_MASKED(base)             (((CTDAC_V1_Type *) (base))->INTR_MASKED)


/*******************************************************************************
*                SYSANALOG
*******************************************************************************/

#define CY_PASS_V1                          (0x20U > cy_device->passVersion)
#define CY_PASS_ADDR                        ((PASS_Type*)cy_device->passBase)
#define CY_PASS_V2_ADDR                     ((PASS_V2_Type*)cy_device->passBase)
#define CY_PASS_BASE(sarBase)               ((NULL != (sarBase)) ? ((PASS_V2_Type*) cy_device->passBase) : NULL) /* temporary solution for single pass instance */

#define PASS_AREF_AREF_CTRL                 (((PASS_V1_Type*) CY_PASS_ADDR)->AREF.AREF_CTRL)
#define PASS_INTR_CAUSE(passBase)           (((PASS_V1_Type*) (passBase))->INTR_CAUSE)
#define PASS_CTBM_CLOCK_SEL(passBase)       (((PASS_V2_Type*) (passBase))->CTBM_CLOCK_SEL)
#define PASS_DPSLP_CLOCK_SEL(passBase)      (((PASS_V2_Type*) (passBase))->DPSLP_CLOCK_SEL)
#define PASS_LPOSC_CTRL(passBase)           (((PASS_V2_Type*) (passBase))->LPOSC.CTRL)
#define PASS_LPOSC_CONFIG(passBase)         (((PASS_V2_Type*) (passBase))->LPOSC.CONFIG)
#define PASS_TIMER_CTRL(passBase)           (((PASS_V2_Type*) (passBase))->TIMER.CTRL)
#define PASS_TIMER_CONFIG(passBase)         (((PASS_V2_Type*) (passBase))->TIMER.CONFIG)
#define PASS_TIMER_PERIOD(passBase)         (((PASS_V2_Type*) (passBase))->TIMER.PERIOD)

#define PASS_SAR_SIMULT_CTRL(passBase)      (((PASS_V2_Type*) (passBase))->SAR_SIMULT_CTRL)
#define PASS_SAR_TR_SCAN_CNT(passBase)      (((PASS_V2_Type*) (passBase))->SAR_TR_SCAN_CNT)
#define PASS_SAR_OVR_CTRL(passBase)         (((PASS_V2_Type*) (passBase))->SAR_OVR_CTRL)
#define PASS_SAR_SIMULT_FW_START_CTRL(passBase) (((PASS_V2_Type*) (passBase))->SAR_SIMULT_FW_START_CTRL)
#define PASS_ANA_PWR_CFG(passBase)          (((PASS_V2_Type*) (passBase))->ANA_PWR_CFG)
#define PASS_SAR_TR_OUT_CTRL(passBase)      (((PASS_V2_Type*) (passBase))->SAR_TR_OUT_CTRL)

#define PASS_SAR_DPSLP_CTRL(sarBase)        (((PASS_V2_Type*) cy_device->passBase)->SAR_DPSLP_CTRL[CY_SAR_INSTANCE(sarBase)])
#define PASS_SAR_CLOCK_SEL(sarBase)         (((PASS_V2_Type*) cy_device->passBase)->SAR_CLOCK_SEL[CY_SAR_INSTANCE(sarBase)])

#define PASS_FIFO_BASE(sarBase)             ((PASS_FIFO_V2_Type*)&(((PASS_V2_Type*)cy_device->passBase)->FIFO[CY_SAR_INSTANCE(sarBase)]))
#define PASS_FIFO_CTRL(sarBase)             (PASS_FIFO_BASE(sarBase)->CTRL)
#define PASS_FIFO_CONFIG(sarBase)           (PASS_FIFO_BASE(sarBase)->CONFIG)
#define PASS_FIFO_LEVEL(sarBase)            (PASS_FIFO_BASE(sarBase)->LEVEL)
#define PASS_FIFO_USED(sarBase)             (PASS_FIFO_BASE(sarBase)->USED)
#define PASS_FIFO_RD_DATA(sarBase)          (PASS_FIFO_BASE(sarBase)->RD_DATA)
#define PASS_FIFO_INTR(sarBase)             (PASS_FIFO_BASE(sarBase)->INTR)
#define PASS_FIFO_INTR_SET(sarBase)         (PASS_FIFO_BASE(sarBase)->INTR_SET)
#define PASS_FIFO_INTR_MASK(sarBase)        (PASS_FIFO_BASE(sarBase)->INTR_MASK)
#define PASS_FIFO_INTR_MASKED(sarBase)      (PASS_FIFO_BASE(sarBase)->INTR_MASKED)

/*******************************************************************************
*                SCB
*******************************************************************************/

#define SCB_CTRL(base)                      (((CySCB_Type*) (base))->CTRL)
#define SCB_SPI_CTRL(base)                  (((CySCB_Type*) (base))->SPI_CTRL)
#define SCB_SPI_STATUS(base)                (((CySCB_Type*) (base))->SPI_STATUS)
#define SCB_SPI_TX_CTRL(base)               (((CySCB_Type*) (base))->SPI_TX_CTRL)
#define SCB_SPI_RX_CTRL(base)               (((CySCB_Type*) (base))->SPI_RX_CTRL)
#define SCB_UART_CTRL(base)                 (((CySCB_Type*) (base))->UART_CTRL)
#define SCB_UART_TX_CTRL(base)              (((CySCB_Type*) (base))->UART_TX_CTRL)
#define SCB_UART_RX_CTRL(base)              (((CySCB_Type*) (base))->UART_RX_CTRL)
#define SCB_UART_FLOW_CTRL(base)            (((CySCB_Type*) (base))->UART_FLOW_CTRL)
#define SCB_I2C_CTRL(base)                  (((CySCB_Type*) (base))->I2C_CTRL)
#define SCB_I2C_STATUS(base)                (((CySCB_Type*) (base))->I2C_STATUS)
#define SCB_I2C_M_CMD(base)                 (((CySCB_Type*) (base))->I2C_M_CMD)
#define SCB_I2C_S_CMD(base)                 (((CySCB_Type*) (base))->I2C_S_CMD)
#define SCB_I2C_CFG(base)                   (((CySCB_Type*) (base))->I2C_CFG)
#define SCB_TX_CTRL(base)                   (((CySCB_Type*) (base))->TX_CTRL)
#define SCB_TX_FIFO_CTRL(base)              (((CySCB_Type*) (base))->TX_FIFO_CTRL)
#define SCB_TX_FIFO_STATUS(base)            (((CySCB_Type*) (base))->TX_FIFO_STATUS)
#define SCB_TX_FIFO_WR(base)                (((CySCB_Type*) (base))->TX_FIFO_WR)
#define SCB_RX_CTRL(base)                   (((CySCB_Type*) (base))->RX_CTRL)
#define SCB_RX_FIFO_CTRL(base)              (((CySCB_Type*) (base))->RX_FIFO_CTRL)
#define SCB_RX_FIFO_STATUS(base)            (((CySCB_Type*) (base))->RX_FIFO_STATUS)
#define SCB_RX_MATCH(base)                  (((CySCB_Type*) (base))->RX_MATCH)
#define SCB_RX_FIFO_RD(base)                (((CySCB_Type*) (base))->RX_FIFO_RD)
#define SCB_INTR_CAUSE(base)                (((CySCB_Type*) (base))->INTR_CAUSE)
#define SCB_INTR_I2C_EC(base)               (((CySCB_Type*) (base))->INTR_I2C_EC)
#define SCB_INTR_I2C_EC_MASK(base)          (((CySCB_Type*) (base))->INTR_I2C_EC_MASK)
#define SCB_INTR_I2C_EC_MASKED(base)        (((CySCB_Type*) (base))->INTR_I2C_EC_MASKED)
#define SCB_INTR_SPI_EC(base)               (((CySCB_Type*) (base))->INTR_SPI_EC)
#define SCB_INTR_SPI_EC_MASK(base)          (((CySCB_Type*) (base))->INTR_SPI_EC_MASK)
#define SCB_INTR_SPI_EC_MASKED(base)        (((CySCB_Type*) (base))->INTR_SPI_EC_MASKED)
#define SCB_INTR_M(base)                    (((CySCB_Type*) (base))->INTR_M)
#define SCB_INTR_M_SET(base)                (((CySCB_Type*) (base))->INTR_M_SET)
#define SCB_INTR_M_MASK(base)               (((CySCB_Type*) (base))->INTR_M_MASK)
#define SCB_INTR_M_MASKED(base)             (((CySCB_Type*) (base))->INTR_M_MASKED)
#define SCB_INTR_S(base)                    (((CySCB_Type*) (base))->INTR_S)
#define SCB_INTR_S_SET(base)                (((CySCB_Type*) (base))->INTR_S_SET)
#define SCB_INTR_S_MASK(base)               (((CySCB_Type*) (base))->INTR_S_MASK)
#define SCB_INTR_S_MASKED(base)             (((CySCB_Type*) (base))->INTR_S_MASKED)
#define SCB_INTR_TX(base)                   (((CySCB_Type*) (base))->INTR_TX)
#define SCB_INTR_TX_SET(base)               (((CySCB_Type*) (base))->INTR_TX_SET)
#define SCB_INTR_TX_MASK(base)              (((CySCB_Type*) (base))->INTR_TX_MASK)
#define SCB_INTR_TX_MASKED(base)            (((CySCB_Type*) (base))->INTR_TX_MASKED)
#define SCB_INTR_RX(base)                   (((CySCB_Type*) (base))->INTR_RX)
#define SCB_INTR_RX_SET(base)               (((CySCB_Type*) (base))->INTR_RX_SET)
#define SCB_INTR_RX_MASK(base)              (((CySCB_Type*) (base))->INTR_RX_MASK)
#define SCB_INTR_RX_MASKED(base)            (((CySCB_Type*) (base))->INTR_RX_MASKED)


/*******************************************************************************
*                PROFILE
*******************************************************************************/

#define CY_EP_MONITOR_COUNT                 ((uint32_t)(cy_device->epMonitorNr))
#define CY_EP_CNT_NR                        (8UL)
#define PROFILE_CTL                         (((PROFILE_V1_Type*) PROFILE_BASE)->CTL)
#define PROFILE_STATUS                      (((PROFILE_V1_Type*) PROFILE_BASE)->STATUS)
#define PROFILE_CMD                         (((PROFILE_V1_Type*) PROFILE_BASE)->CMD)
#define PROFILE_INTR                        (((PROFILE_V1_Type*) PROFILE_BASE)->INTR)
#define PROFILE_INTR_MASK                   (((PROFILE_V1_Type*) PROFILE_BASE)->INTR_MASK)
#define PROFILE_INTR_MASKED                 (((PROFILE_V1_Type*) PROFILE_BASE)->INTR_MASKED)
#define PROFILE_CNT_STRUCT                  (((PROFILE_V1_Type*) PROFILE_BASE)->CNT_STRUCT)

/******************************************************************************
*                MXETH
*******************************************************************************/
#define ETH_CTL(base)                       (((ETH_Type*)(base))->CTL)
#define ETH_TX_Q_PTR(base)                  (((ETH_Type*)(base))->TRANSMIT_Q_PTR)
#define ETH_TX_Q1_PTR(base)                 (((ETH_Type*)(base))->TRANSMIT_Q1_PTR)
#define ETH_TX_Q2_PTR(base)                 (((ETH_Type*)(base))->TRANSMIT_Q2_PTR)
#define ETH_RX_Q_PTR(base)                  (((ETH_Type*)(base))->RECEIVE_Q_PTR)
#define ETH_RX_Q1_PTR(base)                 (((ETH_Type*)(base))->RECEIVE_Q1_PTR)
#define ETH_RX_Q2_PTR(base)                 (((ETH_Type*)(base))->RECEIVE_Q2_PTR)

/*******************************************************************************
*                BLE
*******************************************************************************/

#define BLE_RCB_INTR                        (((BLE_V1_Type *) BLE_BASE)->RCB.INTR)
#define BLE_RCB_TX_FIFO_WR                  (((BLE_V1_Type *) BLE_BASE)->RCB.TX_FIFO_WR)
#define BLE_RCB_RX_FIFO_RD                  (((BLE_V1_Type *) BLE_BASE)->RCB.RX_FIFO_RD)
#define BLE_RCB_CTRL                        (((BLE_V1_Type *) BLE_BASE)->RCB.CTRL)
#define BLE_RCB_RCBLL_CTRL                  (((BLE_V1_Type *) BLE_BASE)->RCB.RCBLL.CTRL)
#define BLE_BLESS_XTAL_CLK_DIV_CONFIG       (((BLE_V1_Type *) BLE_BASE)->BLESS.XTAL_CLK_DIV_CONFIG)
#define BLE_BLESS_MT_CFG                    (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_CFG)
#define BLE_BLESS_MT_STATUS                 (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_STATUS)
#define BLE_BLESS_MT_DELAY_CFG              (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_DELAY_CFG)
#define BLE_BLESS_MT_DELAY_CFG2             (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_DELAY_CFG2)
#define BLE_BLESS_MT_DELAY_CFG3             (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_DELAY_CFG3)
#define BLE_BLESS_MT_VIO_CTRL               (((BLE_V1_Type *) BLE_BASE)->BLESS.MT_VIO_CTRL)
#define BLE_BLESS_LL_CLK_EN                 (((BLE_V1_Type *) BLE_BASE)->BLESS.LL_CLK_EN)
#define BLE_BLESS_MISC_EN_CTRL              (((BLE_V1_Type *) BLE_BASE)->BLESS.MISC_EN_CTRL)
#define BLE_BLESS_INTR_STAT                 (((BLE_V1_Type *) BLE_BASE)->BLESS.INTR_STAT)
#define BLE_BLELL_EVENT_INTR                (((BLE_V1_Type *) BLE_BASE)->BLELL.EVENT_INTR)
#define BLE_BLELL_CONN_INTR                 (((BLE_V1_Type *) BLE_BASE)->BLELL.CONN_INTR)
#define BLE_BLELL_CONN_EXT_INTR             (((BLE_V1_Type *) BLE_BASE)->BLELL.CONN_EXT_INTR)
#define BLE_BLELL_SCAN_INTR                 (((BLE_V1_Type *) BLE_BASE)->BLELL.SCAN_INTR)
#define BLE_BLELL_ADV_INTR                  (((BLE_V1_Type *) BLE_BASE)->BLELL.ADV_INTR)


/*******************************************************************************
*                USBFS Device
*******************************************************************************/

#define USBFS_DEV_CR0(base)             (((USBFS_V1_Type *)(base))->USBDEV.CR0)
#define USBFS_DEV_CR1(base)             (((USBFS_V1_Type *)(base))->USBDEV.CR1)
#define USBFS_DEV_USBIO_CR0(base)       (((USBFS_V1_Type *)(base))->USBDEV.USBIO_CR0)
#define USBFS_DEV_USBIO_CR2(base)       (((USBFS_V1_Type *)(base))->USBDEV.USBIO_CR2)
#define USBFS_DEV_USBIO_CR1(base)       (((USBFS_V1_Type *)(base))->USBDEV.USBIO_CR1)
#define USBFS_DEV_USB_CLK_EN(base)      (((USBFS_V1_Type *)(base))->USBDEV.USB_CLK_EN)
#define USBFS_DEV_BUS_RST_CNT(base)     (((USBFS_V1_Type *)(base))->USBDEV.BUS_RST_CNT)
#define USBFS_DEV_OSCLK_DR0(base)       (((USBFS_V1_Type *)(base))->USBDEV.EP_TYPE)
#define USBFS_DEV_OSCLK_DR1(base)       (((USBFS_V1_Type *)(base))->USBDEV.OSCLK_DR0)
#define USBFS_DEV_SOF0(base)            (((USBFS_V1_Type *)(base))->USBDEV.SOF0)
#define USBFS_DEV_SOF1(base)            (((USBFS_V1_Type *)(base))->USBDEV.SOF1)
#define USBFS_DEV_SOF16(base)           (((USBFS_V1_Type *)(base))->USBDEV.OSCLK_DR1)
#define USBFS_DEV_OSCLK_DR16(base)      (((USBFS_V1_Type *)(base))->USBDEV.SOF16)
#define USBFS_DEV_ARB_CFG(base)         (((USBFS_V1_Type *)(base))->USBDEV.ARB_CFG)
#define USBFS_DEV_DYN_RECONFIG(base)    (((USBFS_V1_Type *)(base))->USBDEV.DYN_RECONFIG)
#define USBFS_DEV_BUF_SIZE(base)        (((USBFS_V1_Type *)(base))->USBDEV.BUF_SIZE)
#define USBFS_DEV_EP_ACTIVE(base)       (((USBFS_V1_Type *)(base))->USBDEV.EP_ACTIVE)
#define USBFS_DEV_EP_TYPE(base)         (((USBFS_V1_Type *)(base))->USBDEV.EP_TYPE)
#define USBFS_DEV_CWA16(base)           (((USBFS_V1_Type *)(base))->USBDEV.CWA16)
#define USBFS_DEV_CWA(base)             (((USBFS_V1_Type *)(base))->USBDEV.CWA)
#define USBFS_DEV_CWA_MSB(base)         (((USBFS_V1_Type *)(base))->USBDEV.CWA_MSB)
#define USBFS_DEV_DMA_THRES16(base)     (((USBFS_V1_Type *)(base))->USBDEV.DMA_THRES16)
#define USBFS_DEV_DMA_THRES(base)       (((USBFS_V1_Type *)(base))->USBDEV.DMA_THRES)
#define USBFS_DEV_DMA_THRES_MSB(base)   (((USBFS_V1_Type *)(base))->USBDEV.DMA_THRES_MSB)

#define USBFS_DEV_SIE_EP_INT_EN(base)   (((USBFS_V1_Type *)(base))->USBDEV.SIE_EP_INT_EN)
#define USBFS_DEV_SIE_EP_INT_SR(base)   (((USBFS_V1_Type *)(base))->USBDEV.SIE_EP_INT_SR)
#define USBFS_DEV_ARB_INT_EN(base)      (((USBFS_V1_Type *)(base))->USBDEV.ARB_INT_EN)
#define USBFS_DEV_ARB_INT_SR(base)      (((USBFS_V1_Type *)(base))->USBDEV.ARB_INT_SR)

#define USBFS_DEV_EP0_CR(base)          (((USBFS_V1_Type *)(base))->USBDEV.EP0_CR)
#define USBFS_DEV_EP0_CNT(base)         (((USBFS_V1_Type *)(base))->USBDEV.EP0_CNT)
#define USBFS_DEV_EP0_DR(base, idx)     (((USBFS_V1_Type *)(base))->USBDEV.EP0_DR[idx])

#define USBFS_DEV_MEM_DATA(base, idx)   (((USBFS_V1_Type *)(base))->USBDEV.MEM[idx])

#define USBFS_DEV_SIE_REGS_BASE        (0x30U)
#define USBFS_DEV_SIE_REGS_SIZE        (0x40U)
#define USBFS_DEV_SIE_EP_CNT0_OFFSET   (0x00U)
#define USBFS_DEV_SIE_EP_CNT1_OFFSET   (0x04U)
#define USBFS_DEV_SIE_EP_CR0_OFFSET    (0x08U)
#define USBFS_DEV_SIE_REGS(base, endpoint) ((uint32_t)(base) + USBFS_DEV_SIE_REGS_BASE + ((endpoint) * USBFS_DEV_SIE_REGS_SIZE))

#define USBFS_DEV_SIE_EP_CNT0(base, endpoint)  (*(volatile uint32_t *) (USBFS_DEV_SIE_REGS(base, endpoint) + \
                                                                        USBFS_DEV_SIE_EP_CNT0_OFFSET))
#define USBFS_DEV_SIE_EP_CNT1(base, endpoint)  (*(volatile uint32_t *) (USBFS_DEV_SIE_REGS(base, endpoint) + \
                                                                        USBFS_DEV_SIE_EP_CNT1_OFFSET))
#define USBFS_DEV_SIE_EP_CR0(base, endpoint)   (*(volatile uint32_t *) (USBFS_DEV_SIE_REGS(base, endpoint) + \
                                                                        USBFS_DEV_SIE_EP_CR0_OFFSET))

#define USBFS_DEV_ARB_REGS_BASE         (0x200U)
#define USBFS_DEV_ARB_REGS_SIZE         (0x40U)
#define USBFS_DEV_ARB_EP_CFG_OFFSET     (0x00U)
#define USBFS_DEV_ARB_EP_INT_EN_OFFSET  (0x04U)
#define USBFS_DEV_ARB_EP_SR_OFFSET      (0x08U)
#define USBFS_DEV_ARB_RW_WA_OFFSET      (0x10U)
#define USBFS_DEV_ARB_RW_WA_MSB_OFFSET  (0x14U)
#define USBFS_DEV_ARB_RW_RA_OFFSET      (0x18U)
#define USBFS_DEV_ARB_RW_RA_MSB_OFFSET  (0x1CU)
#define USBFS_DEV_ARB_RW_DR_OFFSET      (0x20U)
#define USBFS_DEV_ARB_REGS(base, endpoint) ((uint32_t)(base) + USBFS_DEV_ARB_REGS_BASE + ((endpoint) * USBFS_DEV_ARB_REGS_SIZE))

#define USBFS_DEV_ARB_EP_CFG(base, endpoint)       (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_EP_CFG_OFFSET))
#define USBFS_DEV_ARB_EP_INT_EN(base, endpoint)    (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_EP_INT_EN_OFFSET))
#define USBFS_DEV_ARB_EP_SR(base, endpoint)        (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_EP_SR_OFFSET))
#define USBFS_DEV_ARB_RW_WA(base, endpoint)        (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_WA_OFFSET))
#define USBFS_DEV_ARB_RW_WA_MSB(base, endpoint)    (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_WA_MSB_OFFSET))
#define USBFS_DEV_ARB_RW_RA(base, endpoint)        (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_RA_OFFSET))
#define USBFS_DEV_ARB_RW_RA_MSB(base, endpoint)    (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_RA_MSB_OFFSET))
#define USBFS_DEV_ARB_RW_DR(base, endpoint)        (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_DR_OFFSET))

#define USBFS_DEV_ARB_REGS16_BASE       (0x1210U)
#define USBFS_DEV_ARB_REGS16_SIZE       (0x40U)
#define USBFS_DEV_ARB_RW_WA16_OFFSET    (0x00U)
#define USBFS_DEV_ARB_RW_RA16_OFFSET    (0x08U)
#define USBFS_DEV_ARB_RW_DR16_OFFSET    (0x10U)
#define USBFS_DEV_ARB_REGS_16(base, endpoint) ((uint32_t)(base) + USBFS_DEV_ARB_REGS16_BASE + ((endpoint) * USBFS_DEV_ARB_REGS16_SIZE))

#define USBFS_DEV_ARB_RW_WA16(base, endpoint)      (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS_16(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_WA16_OFFSET))
#define USBFS_DEV_ARB_RW_RA16(base, endpoint)      (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS_16(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_RA16_OFFSET))
#define USBFS_DEV_ARB_RW_DR16(base, endpoint)      (*(volatile uint32_t *) (USBFS_DEV_ARB_REGS_16(base, endpoint) + \
                                                                            USBFS_DEV_ARB_RW_DR16_OFFSET))

#define USBFS_DEV_LPM_POWER_CTL(base)       (((USBFS_V1_Type *)(base))->USBLPM.POWER_CTL)
#define USBFS_DEV_LPM_USBIO_CTL(base)       (((USBFS_V1_Type *)(base))->USBLPM.USBIO_CTL)
#define USBFS_DEV_LPM_FLOW_CTL(base)        (((USBFS_V1_Type *)(base))->USBLPM.FLOW_CTL)
#define USBFS_DEV_LPM_LPM_CTL(base)         (((USBFS_V1_Type *)(base))->USBLPM.LPM_CTL)
#define USBFS_DEV_LPM_LPM_STAT(base)        (((USBFS_V1_Type const *)(base))->USBLPM.LPM_STAT)
#define USBFS_DEV_LPM_INTR_SIE(base)        (((USBFS_V1_Type *)(base))->USBLPM.INTR_SIE)
#define USBFS_DEV_LPM_INTR_SIE_SET(base)    (((USBFS_V1_Type *)(base))->USBLPM.INTR_SIE_SET)
#define USBFS_DEV_LPM_INTR_SIE_MASK(base)   (((USBFS_V1_Type *)(base))->USBLPM.INTR_SIE_MASK)
#define USBFS_DEV_LPM_INTR_SIE_MASKED(base) (((USBFS_V1_Type *)(base))->USBLPM.INTR_SIE_MASKED)
#define USBFS_DEV_LPM_INTR_LVL_SEL(base)    (((USBFS_V1_Type *)(base))->USBLPM.INTR_LVL_SEL)
#define USBFS_DEV_LPM_INTR_CAUSE_HI(base)   (((USBFS_V1_Type const *)(base))->USBLPM.INTR_CAUSE_HI)
#define USBFS_DEV_LPM_INTR_CAUSE_MED(base)  (((USBFS_V1_Type const *)(base))->USBLPM.INTR_CAUSE_MED)
#define USBFS_DEV_LPM_INTR_CAUSE_LO(base)   (((USBFS_V1_Type const *)(base))->USBLPM.INTR_CAUSE_LO)
#define USBFS_DEV_LPM_DFT_CTL(base)         (((USBFS_V1_Type *)(base))->USBLPM.DFT_CTL)

#define USBFS_HOST_CTL0(base)               (((USBFS_V1_Type *)(base))->USBHOST.HOST_CTL0)
#define USBFS_HOST_CTL1(base)               (((USBFS_V1_Type *)(base))->USBHOST.HOST_CTL1)
#define USBFS_HOST_CTL2(base)               (((USBFS_V1_Type *)(base))->USBHOST.HOST_CTL2)
#define USBFS_HOST_ERR(base)                (((USBFS_V1_Type *)(base))->USBHOST.HOST_ERR)
#define USBFS_HOST_STATUS(base)             (((USBFS_V1_Type *)(base))->USBHOST.HOST_STATUS)
#define USBFS_HOST_FCOMP(base)              (((USBFS_V1_Type *)(base))->USBHOST.HOST_FCOMP)
#define USBFS_HOST_RTIMER(base)             (((USBFS_V1_Type *)(base))->USBHOST.HOST_RTIMER)
#define USBFS_HOST_ADDR(base)               (((USBFS_V1_Type *)(base))->USBHOST.HOST_ADDR)
#define USBFS_HOST_EOF(base)                (((USBFS_V1_Type *)(base))->USBHOST.HOST_EOF)
#define USBFS_HOST_FRAME(base)              (((USBFS_V1_Type *)(base))->USBHOST.HOST_FRAME)
#define USBFS_HOST_TOKEN(base)              (((USBFS_V1_Type *)(base))->USBHOST.HOST_TOKEN)
#define USBFS_HOST_EP1_CTL(base)            (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP1_CTL)
#define USBFS_HOST_EP1_STATUS(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP1_STATUS)
#define USBFS_HOST_EP1_RW1_DR(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP1_RW1_DR)
#define USBFS_HOST_EP1_RW2_DR(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP1_RW2_DR)
#define USBFS_HOST_EP2_CTL(base)            (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP2_CTL)
#define USBFS_HOST_EP2_STATUS(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP2_STATUS)
#define USBFS_HOST_EP2_RW1_DR(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP2_RW1_DR)
#define USBFS_HOST_EP2_RW2_DR(base)         (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP2_RW2_DR)
#define USBFS_HOST_LVL1_SEL(base)           (((USBFS_V1_Type *)(base))->USBHOST.HOST_LVL1_SEL)
#define USBFS_HOST_LVL2_SEL(base)           (((USBFS_V1_Type *)(base))->USBHOST.HOST_LVL2_SEL)
#define USBFS_INTR_USBHOST_CAUSE_HI(base)   (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_CAUSE_HI)
#define USBFS_INTR_USBHOST_CAUSE_MED(base)  (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_CAUSE_MED)
#define USBFS_INTR_USBHOST_CAUSE_LO(base)   (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_CAUSE_LO)
#define USBFS_INTR_HOST_EP_CAUSE_HI(base)   (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_CAUSE_HI)
#define USBFS_INTR_HOST_EP_CAUSE_MED(base)  (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_CAUSE_MED)
#define USBFS_INTR_HOST_EP_CAUSE_LO(base)   (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_CAUSE_LO)
#define USBFS_INTR_USBHOST(base)            (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST)
#define USBFS_INTR_USBHOST_SET(base)        (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_SET)
#define USBFS_INTR_USBHOST_MASK(base)       (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_MASK)
#define USBFS_INTR_USBHOST_MASKED(base)     (((USBFS_V1_Type *)(base))->USBHOST.INTR_USBHOST_MASKED)
#define USBFS_INTR_HOST_EP(base)            (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP)
#define USBFS_INTR_HOST_EP_SET(base)        (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_SET)
#define USBFS_INTR_HOST_EP_MASK(base)       (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_MASK)
#define USBFS_INTR_HOST_EP_MASKED(base)     (((USBFS_V1_Type *)(base))->USBHOST.INTR_HOST_EP_MASKED)
#define USBFS_HOST_DMA_ENBL(base)           (((USBFS_V1_Type *)(base))->USBHOST.HOST_DMA_ENBL)
#define USBFS_HOST_EP1_BLK(base)            (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP1_BLK)
#define USBFS_HOST_EP2_BLK(base)            (((USBFS_V1_Type *)(base))->USBHOST.HOST_EP2_BLK)


/*******************************************************************************
*                LIN
*******************************************************************************/
#if defined (CY_IP_MXLIN)
#define LIN0_CH1                                ((LIN_CH_Type*) &LIN0->CH[1])
#define LIN0_CH2                                ((LIN_CH_Type*) &LIN0->CH[2])
#define LIN0_CH3                                ((LIN_CH_Type*) &LIN0->CH[3])
#define LIN0_CH4                                ((LIN_CH_Type*) &LIN0->CH[4])
#define LIN0_CH5                                ((LIN_CH_Type*) &LIN0->CH[5])
#define LIN0_CH6                                ((LIN_CH_Type*) &LIN0->CH[6])
#define LIN0_CH7                                ((LIN_CH_Type*) &LIN0->CH[7])
#define LIN0_CH8                                ((LIN_CH_Type*) &LIN0->CH[8])
#define LIN0_CH9                                ((LIN_CH_Type*) &LIN0->CH[9])
#define LIN0_CH10                               ((LIN_CH_Type*) &LIN0->CH[10])
#define LIN0_CH11                               ((LIN_CH_Type*) &LIN0->CH[11])
#define LIN0_CH12                               ((LIN_CH_Type*) &LIN0->CH[12])
#define LIN0_CH13                               ((LIN_CH_Type*) &LIN0->CH[13])
#define LIN0_CH14                               ((LIN_CH_Type*) &LIN0->CH[14])
#define LIN0_CH15                               ((LIN_CH_Type*) &LIN0->CH[15])
#define LIN0_CH16                               ((LIN_CH_Type*) &LIN0->CH[16])
#define LIN0_CH17                               ((LIN_CH_Type*) &LIN0->CH[17])
#define LIN0_CH18                               ((LIN_CH_Type*) &LIN0->CH[18])
#define LIN0_CH19                               ((LIN_CH_Type*) &LIN0->CH[19])
#define LIN0_CH20                               ((LIN_CH_Type*) &LIN0->CH[20])
#define LIN0_CH21                               ((LIN_CH_Type*) &LIN0->CH[21])
#define LIN0_CH22                               ((LIN_CH_Type*) &LIN0->CH[22])
#define LIN0_CH23                               ((LIN_CH_Type*) &LIN0->CH[23])
#define LIN0_CH24                               ((LIN_CH_Type*) &LIN0->CH[24])
#define LIN0_CH25                               ((LIN_CH_Type*) &LIN0->CH[25])
#define LIN0_CH26                               ((LIN_CH_Type*) &LIN0->CH[26])
#define LIN0_CH27                               ((LIN_CH_Type*) &LIN0->CH[27])
#define LIN0_CH28                               ((LIN_CH_Type*) &LIN0->CH[28])
#define LIN0_CH29                               ((LIN_CH_Type*) &LIN0->CH[29])
#define LIN0_CH30                               ((LIN_CH_Type*) &LIN0->CH[30])
#define LIN0_CH31                               ((LIN_CH_Type*) &LIN0->CH[31])

#define LIN_CH_CTL0(base)                       (((LIN_CH_Type *)(base))->CTL0)
#define LIN_CH_CTL1(base)                       (((LIN_CH_Type *)(base))->CTL1)
#define LIN_CH_STATUS(base)                     (((LIN_CH_Type *)(base))->STATUS)
#define LIN_CH_CMD(base)                        (((LIN_CH_Type *)(base))->CMD)
#define LIN_CH_TX_RX_STATUS(base)               (((LIN_CH_Type *)(base))->TX_RX_STATUS)
#define LIN_CH_PID_CHECKSUM(base)               (((LIN_CH_Type *)(base))->PID_CHECKSUM)
#define LIN_CH_DATA0(base)                      (((LIN_CH_Type *)(base))->DATA0)
#define LIN_CH_DATA1(base)                      (((LIN_CH_Type *)(base))->DATA1)
#define LIN_CH_INTR(base)                       (((LIN_CH_Type *)(base))->INTR)
#define LIN_CH_INTR_SET(base)                   (((LIN_CH_Type *)(base))->INTR_SET)
#define LIN_CH_INTR_MASK(base)                  (((LIN_CH_Type *)(base))->INTR_MASK)
#define LIN_CH_INTR_MASKED(base)                (((LIN_CH_Type *)(base))->INTR_MASKED)

#define LIN_ERROR_CTL(base)                     (((LIN_Type *)(base))->ERROR_CTL)
#define LIN_TEST_CTL(base)                      (((LIN_Type *)(base))->TEST_CTL)
#endif /* CY_IP_MXLIN */

/*******************************************************************************
*                SAR ADC
*******************************************************************************/
/** Channel TR_CTL register access macro. */
#define SAR2_CH_TR_CTL(base, channel) (((PASS_SAR_Type *)base)->CH[channel].TR_CTL)

/** Channel SAMPLE_CTL register access macro. */
#define SAR2_CH_SAMPLE_CTL(base, channel) (((PASS_SAR_Type *)base)->CH[channel].SAMPLE_CTL)

/** Channel POST_CTL register access macro. */
#define SAR2_CH_POST_CTL(base, channel) (((PASS_SAR_Type *)base)->CH[channel].POST_CTL)

/** Channel RANGE_CTL register access macro. */
#define SAR2_CH_RANGE_CTL(base, channel) (((PASS_SAR_Type *)base)->CH[channel].RANGE_CTL)

/** Channel INTR register access macro. */
#define SAR2_CH_INTR(base, channel) (((PASS_SAR_Type *)base)->CH[channel].INTR)

/** Channel INTR_SET register access macro. */
#define SAR2_CH_INTR_SET(base, channel) (((PASS_SAR_Type *)base)->CH[channel].INTR_SET)

/** Channel INTR_MASK register access macro. */
#define SAR2_CH_INTR_MASK(base, channel) (((PASS_SAR_Type *)base)->CH[channel].INTR_MASK)

/** Channel INTR_MASKED register access macro. */
#define SAR2_CH_INTR_MASKED(base, channel) (((PASS_SAR_Type *)base)->CH[channel].INTR_MASKED)

/** Channel WORK register access macro. */
#define SAR2_CH_WORK(base, channel) (((PASS_SAR_Type *)base)->CH[channel].WORK)

/** Channel WORK register access macro. */
#define SAR2_CH_RESULT(base, channel) (((PASS_SAR_Type *)base)->CH[channel].WORK)

/** Channel GRP_STAT register access macro. */
#define SAR2_CH_GRP_STAT(base, channel) (((PASS_SAR_Type *)base)->CH[channel].GRP_STAT)

/** Channel ENABLE register access macro. */
#define SAR2_CH_ENABLE(base, channel) (((PASS_SAR_Type *)base)->CH[channel].ENABLE)

/** Channel TR_CMD register access macro. */
#define SAR2_CH_TR_CMD(base, channel) (((PASS_SAR_Type *)base)->CH[channel].TR_CMD)

#endif /* CY_DEVICE_H_ */

/* [] END OF FILE */
