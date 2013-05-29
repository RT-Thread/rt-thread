/** @file sys_selftest.h
*   @brief System Memory Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Efuse Self Test Functions
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __sys_selftest_H__
#define __sys_selftest_H__

#include "reg_pbist.h"
#include "reg_stc.h"
#include "reg_efc.h"
#include "sys_core.h"
#include "system.h"
#include "sys_vim.h"
#include "adc.h"
#include "can.h"
#include "mibspi.h"
#include "het.h"
#include "htu.h"
#include "esm.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

#define flash1bitError	(*(volatile uint32 *)(0xF00803F0U))
#define flash2bitError	(*(volatile uint32 *)(0xF00803F8U))

#define tcramA1bitError	(*(volatile uint32 *)(0x08400000U))
#define tcramA2bitError (*(volatile uint32 *)(0x08400010U))

#define tcramB1bitError	(*(volatile uint32 *)(0x08400008U))
#define tcramB2bitError (*(volatile uint32 *)(0x08400018U))

#define tcramA1bit		(*(volatile uint32 *)(0x08000000U))
#define tcramA2bit		(*(volatile uint32 *)(0x08000010U))

#define tcramB1bit		(*(volatile uint32 *)(0x08000008U))
#define tcramB2bit		(*(volatile uint32 *)(0x08000018U))

#define flashBadECC		(*(volatile uint32 *)(0x20040000U))

#define CCMSR 			(*(volatile uint32 *)(0xFFFFF600U))
#define CCMKEYR			(*(volatile uint32 *)(0xFFFFF604U))


#define DMA_PARCR		(*(volatile uint32 *)(0xFFFFF1A8U))
#define DMA_PARADDR		(*(volatile uint32 *)(0xFFFFF1ACU))

#define DMARAMLOC		(*(volatile uint32 *)(0xFFF80000U))
#define DMARAMPARLOC	(*(volatile uint32 *)(0xFFF80A00U))


#ifndef __PBIST_H__
#define __PBIST_H__

/** @enum pbistPort
*   @brief Alias names for pbist Port number
*
*   This enumeration is used to provide alias names for the pbist Port number
*     - PBIST_PORT0
*     - PBIST_PORT1
*/
enum pbistPort
{
    PBIST_PORT0 = 0U, /**< Alias for PBIST Port 0 */
    PBIST_PORT1 = 1U  /**< Alias for PBIST Port 1 */
};
/** @enum pbistAlgo
*   @brief Alias names for pbist Algorithm
*
*   This enumeration is used to provide alias names for the pbist Algorithm
*     - PBIST_TripleReadSlow 
*     - PBIST_TripleReadFast 
*     - PBIST_March13N_DP    
*     - PBIST_March13N_SP    
*     - PBIST_DOWN1a_DP      
*     - PBIST_DOWN1a_SP      
*     - PBIST_MapColumn_DP   
*     - PBIST_MapColumn_SP   
*     - PBIST_Precharge_DP   
*     - PBIST_Precharge_SP   
*     - PBIST_DTXN2a_DP      
*     - PBIST_DTXN2a_SP      
*     - PBIST_PMOSOpen_DP    
*     - PBIST_PMOSOpen_SP    
*     - PBIST_PPMOSOpenSlice1_DP
*     - PBIST_PPMOSOpenSlice1_SP
*     - PBIST_PPMOSOpenSlice2_DP
*     - PBIST_PPMOSOpenSlice2_SP

*/
enum pbistAlgo
{
    PBIST_TripleReadSlow     = 0x00000001U,
    PBIST_TripleReadFast     = 0x00000002U,
    PBIST_March13N_DP        = 0x00000004U,
	PBIST_March13N_SP        = 0x00000008U,
    PBIST_DOWN1a_DP          = 0x00000010U,
	PBIST_DOWN1a_SP          = 0x00000020U,
    PBIST_MapColumn_DP       = 0x00000040U,
	PBIST_MapColumn_SP       = 0x00000080U,
    PBIST_Precharge_DP       = 0x00000100U,
	PBIST_Precharge_SP       = 0x00000200U,
    PBIST_DTXN2a_DP          = 0x00000400U,
	PBIST_DTXN2a_SP          = 0x00000800U,
	PBIST_PMOSOpen_DP        = 0x00001000U,
    PBIST_PMOSOpen_SP        = 0x00002000U,
	PBIST_PPMOSOpenSlice1_DP = 0x00004000U,
    PBIST_PPMOSOpenSlice1_SP = 0x00008000U,
	PBIST_PPMOSOpenSlice2_DP = 0x00010000U,
    PBIST_PPMOSOpenSlice2_SP = 0x00020000U
};
/* PBIST configuration registers */
typedef struct pbist_config_reg
{
    uint32 CONFIG_RAMT;
    uint32 CONFIG_DLR;
    uint32 CONFIG_PACT;
    uint32 CONFIG_PBISTID;
    uint32 CONFIG_OVER;
    uint32 CONFIG_FSRDL1;
    uint32 CONFIG_ROM;
    uint32 CONFIG_ALGO;
    uint32 CONFIG_RINFOL;
    uint32 CONFIG_RINFOU;
} pbist_config_reg_t;

/* PBIST congiruration registers initial value */
#define PBIST_RAMT_CONFIGVALUE 0U
#define PBIST_DLR_CONFIGVALUE 0U
#define PBIST_PACT_CONFIGVALUE 0U
#define PBIST_PBISTID_CONFIGVALUE 0U
#define PBIST_OVER_CONFIGVALUE 0U
#define PBIST_FSRDL1_CONFIGVALUE 0U
#define PBIST_ROM_CONFIGVALUE 0U
#define PBIST_ALGO_CONFIGVALUE 0U
#define PBIST_RINFOL_CONFIGVALUE 0U
#define PBIST_RINFOU_CONFIGVALUE 0U


/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void memoryPort0TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data)
*   @brief Memory Port 0 test fail notification
*   @param[in] groupSelect Failing Ram group select:
*   @param[in] dataSelect Failing Ram data select:
*   @param[in] address Failing Ram offset:
*   @param[in] data Failing data at address:
*
*   @note This function has to be provide by the user.
*/
void memoryPort0TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data);

/** @fn void memoryPort1TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data)
*   @brief Memory Port 1 test fail notification
*   @param[in] groupSelect Failing Ram group select:
*   @param[in] dataSelect Failing Ram data select:
*   @param[in] address Failing Ram offset:
*   @param[in] data Failing data at address:
*
*   @note This function has to be provide by the user.
*/
void memoryPort1TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data);

void pbistGetConfigValue(pbist_config_reg_t *config_reg, config_value_type_t type);
#endif

#ifndef __STC_H__
#define __STC_H__

/* STC General Definitions */

/* STC Test Intervals supported in the Device */
#define STC_INTERVAL 24U
#define STC_MAX_TIMEOUT 0xFFFFFFFFU



/* Configuration registers */
typedef struct stc_config_reg
{
	uint32 CONFIG_STCGCR0;
    uint32 CONFIG_STCGCR1;
    uint32 CONFIG_STCTPR;
    uint32 CONFIG_STCSCSCR;
} stc_config_reg_t;

/* Configuration registers initial value */
#define STC_STCGCR0_CONFIGVALUE	0xFFFF0000U
#define STC_STCGCR1_CONFIGVALUE	0x5U
#define STC_STCTPR_CONFIGVALUE	0xFFFFFFFFU
#define STC_STCSCSCR_CONFIGVALUE 0x5U

void stcGetConfigValue(stc_config_reg_t *config_reg, config_value_type_t type);

#endif

#ifndef __EFC_H__
#define __EFC_H__

#define INPUT_ENABLE         0x0000000FU
#define INPUT_DISABLE        0x00000000U

#define SYS_WS_READ_STATES   0x00000000U


#define SYS_REPAIR_EN_0      0x00000000U
#define SYS_REPAIR_EN_3      0x00000100U
#define SYS_REPAIR_EN_5      0x00000200U

#define SYS_DEID_AUTOLOAD_EN 0x00000400U

#define EFC_FDI_EN            0x00000800U
#define EFC_FDI_DIS           0x00000000U

#define SYS_ECC_OVERRIDE_EN   0x00001000U
#define SYS_ECC_OVERRIDE_DIS  0x00000000U

#define SYS_ECC_SELF_TEST_EN  0x00002000U
#define SYS_ECC_SELF_TEST_DIS 0x00000000U

#define OUTPUT_ENABLE         0x0003C000U
#define OUTPUT_DISABLE        0x00000000U

/*********** OUTPUT **************/

#define EFC_AUTOLOAD_ERROR_EN    0x00040000U
#define EFC_INSTRUCTION_ERROR_EN 0x00080000U
#define EFC_INSTRUCTION_INFO_EN  0x00100000U
#define EFC_SELF_TEST_ERROR_EN   0x00200000U


#define EFC_AUTOLOAD_ERROR_DIS    0x00000000U
#define EFC_INSTRUCTION_ERROR_DIS 0x00000000U
#define EFC_INSTRUCTION_INFO_DIS  0x00000000U
#define EFC_SELF_TEST_ERROR_DIS   0x00000000U

#define DISABLE_READ_ROW0         0x00800000U

/********************************************************************/

#define SYS_REPAIR_0         0x00000010U
#define SYS_REPAIR_3         0x00000010U
#define SYS_REPAIR_5         0x00000020U

#define SYS_DEID_AUTOLOAD    0x00000040U
#define SYS_FCLRZ            0x00000080U
#define EFC_READY            0x00000100U
#define SYS_ECC_OVERRIDE     0x00000200U
#define EFC_AUTOLOAD_ERROR   0x00000400U
#define EFC_INSTRUCTION_ERROR 0x00000800U
#define EFC_INSTRUCTION_INFO  0x00001000U
#define SYS_ECC_SELF_TEST    0x00002000U
#define EFC_SELF_TEST_ERROR  0x00004000U
#define EFC_SELF_TEST_DONE   0x00008000U

/**************   0x3C error status register ******************************************************/

#define TIME_OUT 0x01
#define AUTOLOAD_NO_FUSEROM_DATA      0x02U 
#define AUTOLOAD_SIGN_FAIL            0x03U
#define AUTOLOAD_PROG_INTERRUPT       0x04U
#define AUTOLOAD_TWO_BIT_ERR          0x05U
#define PROGRAME_WR_P_SET             0x06U
#define PROGRAME_MNY_DATA_ITERTN      0x07U
#define PROGRAME_MNY_CNTR_ITERTN      0x08U
#define UN_PROGRAME_BIT_SET           0x09U
#define REDUNDANT_REPAIR_ROW          0x0AU
#define PROGRAME_MNY_CRA_ITERTN       0x0BU
#define PROGRAME_SAME_DATA            0x0CU
#define PROGRAME_CMP_SKIP			  0x0DU
#define PROGRAME_ABORT                0x0EU
#define PROGRAME_INCORRECT_KEY		  0x0FU
#define FUSEROM_LASTROW_STUCK		  0x10U
#define AUTOLOAD_SINGLE_BIT_ERR		  0x15U
#define DUMPWORD_TWO_BIT_ERR	      0x16U
#define DUMPWORD_ONE_BIT_ERR          0x17U
#define SELF_TEST_ERROR               0x18U

#define INSTRUCTION_DONE              0x20U

/**************   Efuse Instruction set ******************************************************/

#define TEST_UNPROGRAME_ROM  0x01000000U
#define PROGRAME_CRA         0x02000000U 
#define DUMP_WORD            0x04000000U
#define LOAD_FUSE_SCAN_CHAIN 0x05000000U
#define PROGRAME_DATA        0x07000000U
#define RUN_AUTOLOAD_8       0x08000000U
#define RUN_AUTOLOAD_A       0x0A000000U

/* Configuration registers */
typedef struct efc_config_reg
{
	uint32 CONFIG_BOUNDARY;
	uint32 CONFIG_PINS;
	uint32 CONFIG_SELFTESTCYCLES;
	uint32 CONFIG_SELFTESTSIGN;
}efc_config_reg_t;

/* Configuration registers initial value */
#define EFC_BOUNDARY_CONFIGVALUE	0x0000200FU
#define EFC_PINS_CONFIGVALUE		0x000082E0U
#define EFC_SELFTESTCYCLES_CONFIGVALUE	0x00000258U
#define EFC_SELFTESTSIGN_CONFIGVALUE	0x5362F97FU

void efcGetConfigValue(efc_config_reg_t *config_reg, config_value_type_t type);
#endif

/* safety Init Interface Functions */
void ccmSelfCheck(void);
void ccmFail(uint32 x);

void stcSelfCheck(void);
void stcSelfCheckFail(void);
void cpuSelfTest(uint32 no_of_intervals, uint32 max_timeout, boolean restart_test);
void cpuSelfTestFail(void);

void memoryInit(uint32 ram);

void pbistSelfCheck(void);
void pbistRun(uint32 raminfoL, uint32 algomask);
void pbistStop(void);
void pbistSelfCheckFail(void);
boolean pbistIsTestCompleted(void);
boolean pbistIsTestPassed(void);
boolean pbistPortTestStatus(uint32 port);

void efcCheck(void);
void efcSelfTest(void);
boolean efcStuckZeroTest(void);
boolean checkefcSelfTest(void);
void efcClass1Error(void);
void efcClass2Error(void);

void fmcBus2Check(void);
void fmcECCcheck(void);
void fmcClass1Error(void);
void fmcClass2Error(void);

void checkB0RAMECC(void);
void checkB1RAMECC(void);
void tcramClass1Error(void);
void tcramClass2Error(void);

void checkFlashECC(void);
void flashClass1Error(void);
void flashClass2Error(void);

void vimParityCheck(void);
void dmaParityCheck(void);
void adc1ParityCheck(void);
void adc2ParityCheck(void);
void het1ParityCheck(void);
void htu1ParityCheck(void);
void het2ParityCheck(void);
void htu2ParityCheck(void);
void can1ParityCheck(void);
void can2ParityCheck(void);
void can3ParityCheck(void);
void mibspi1ParityCheck(void);
void mibspi3ParityCheck(void);
void mibspi5ParityCheck(void);

/* USER CODE BEGIN (2) */
/* USER CODE END */

/* Configuration registers */
typedef struct ccmr4_config_reg
{
	uint32 CONFIG_CCMKEYR;
}ccmr4_config_reg_t;

/* Configuration registers initial value */
#define CCMR4_CCMKEYR_CONFIGVALUE	0U

void ccmr4GetConfigValue(ccmr4_config_reg_t *config_reg, config_value_type_t type);
#endif
