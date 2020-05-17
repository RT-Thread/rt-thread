/**
 **************************************************************************
 * File Name    : at32f4xx_xmc.c
 * Description  : at32f4xx XMC source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_xmc.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup XMC
  * @brief XMC driver modules
  * @{
  */

#if defined (AT32F403xx) || defined (AT32F403Axx) || defined (AT32F407xx)

/** @defgroup XMC_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @defgroup XMC_Private_Defines
  * @{
  */

/* --------------------- XMC registers bit mask ---------------------------- */

/* XMC BCRx Mask */
#define BK1CTRLx_EN_Set                     ((uint32_t)0x00000001)
#define BK1CTRLx_EN_Reset                   ((uint32_t)0x000FFFFE)
#define BK1CTRLx_NOREN_Set                  ((uint32_t)0x00000040)

/* XMC PCRx Mask */
#define BKxCTRL_EN_Set                      ((uint32_t)0x00000004)
#define BKxCTRL_EN_Reset                    ((uint32_t)0x000FFFFB)
#define BKxCTRL_ECCEN_Set                   ((uint32_t)0x00000040)
#define BKxCTRL_ECCEN_Reset                 ((uint32_t)0x000FFFBF)
#define BKxCTRL_Device_NAND                 ((uint32_t)0x00000008)
/**
  * @}
  */

/** @defgroup XMC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup XMC_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup XMC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup XMC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the XMC NOR/SRAM Banks registers to their default
  *         reset values.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank1_NORSRAM1: XMC Bank1 NOR/SRAM1
  *     @arg XMC_Bank1_NORSRAM2: XMC Bank1 NOR/SRAM2
  *     @arg XMC_Bank1_NORSRAM3: XMC Bank1 NOR/SRAM3
  *     @arg XMC_Bank1_NORSRAM4: XMC Bank1 NOR/SRAM4
  * @retval None
  */
void XMC_NORSRAMReset(uint32_t XMC_Bank)
{
  /* Check the parameter */
  assert_param(IS_XMC_NORSRAM_REGION(XMC_Bank));

  /* XMC_Bank1_NORSRAM1 */
  if(XMC_Bank == XMC_Bank1_NORSRAM1)
  {
    XMC_Bank1->BK1CTRLR[XMC_Bank] = 0x000030DB;
  }
  /* XMC_Bank1_NORSRAM2,  XMC_Bank1_NORSRAM3 or XMC_Bank1_NORSRAM4 */
  else
  {
    XMC_Bank1->BK1CTRLR[XMC_Bank] = 0x000030D2;
  }

  XMC_Bank1->BK1CTRLR[XMC_Bank + 1] = 0x0FFFFFFF;
  XMC_Bank1E->BK1TMGWR[XMC_Bank] = 0x0FFFFFFF;
}

/**
  * @brief  Deinitializes the XMC NAND Banks registers to their default reset values.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank2_NAND: XMC Bank2 NAND
  *     @arg XMC_Bank3_NAND: XMC Bank3 NAND
  * @retval None
  */
void XMC_NANDReset(uint32_t XMC_Bank)
{
  /* Check the parameter */
  assert_param(IS_XMC_NAND_BANK(XMC_Bank));

  if(XMC_Bank == XMC_Bank2_NAND)
  {
    /* Set the XMC_Bank2 registers to their reset values */
    XMC_Bank2->BK2CTRL = 0x00000018;
    XMC_Bank2->BK2STS = 0x00000040;
    XMC_Bank2->BK2TMGMEM = 0xFCFCFCFC;
    XMC_Bank2->BK2TMGATT = 0xFCFCFCFC;
  }
  /* XMC_Bank3_NAND */
  else
  {
    /* Set the XMC_Bank3 registers to their reset values */
    XMC_Bank3->BK3CTRL = 0x00000018;
    XMC_Bank3->BK3STS = 0x00000040;
    XMC_Bank3->BK3TMGMEM = 0xFCFCFCFC;
    XMC_Bank3->BK3TMGATT = 0xFCFCFCFC;
  }
}

/**
  * @brief  Deinitializes the XMC PCCARD Bank registers to their default reset values.
  * @param  None
  * @retval None
  */
void XMC_PCCARDReset(void)
{
  /* Set the XMC_Bank4 registers to their reset values */
  XMC_Bank4->BK4CTRL = 0x00000018;
  XMC_Bank4->BK4STS = 0x00000000;
  XMC_Bank4->BK4TMGMEM = 0xFCFCFCFC;
  XMC_Bank4->BK4TMGATT = 0xFCFCFCFC;
  XMC_Bank4->BK4TMGIO = 0xFCFCFCFC;
}

/**
  * @brief  Initializes the XMC NOR/SRAM Banks according to the specified
  *         parameters in the XMC_NORSRAMInitStruct.
  * @param  XMC_NORSRAMInitStruct : pointer to a XMC_NORSRAMInitType
  *         structure that contains the configuration information for
  *        the XMC NOR/SRAM specified Banks.
  * @retval None
  */
void XMC_NORSRAMInit(XMC_NORSRAMInitType* XMC_NORSRAMInitStruct)
{
  /* Check the parameters */
  assert_param(IS_XMC_NORSRAM_REGION(XMC_NORSRAMInitStruct->XMC_Bank));
  assert_param(IS_XMC_MUX(XMC_NORSRAMInitStruct->XMC_DataAdrMux));
  assert_param(IS_XMC_DEVICE(XMC_NORSRAMInitStruct->XMC_Dev));
  assert_param(IS_XMC_BUS_TYPE(XMC_NORSRAMInitStruct->XMC_BusType));
  assert_param(IS_XMC_BURSTMODE(XMC_NORSRAMInitStruct->XMC_EnableBurstMode));
  assert_param(IS_XMC_ASYNWAIT(XMC_NORSRAMInitStruct->XMC_EnableAsynWait));
  assert_param(IS_XMC_WAIT_SIGNAL_LEVEL(XMC_NORSRAMInitStruct->XMC_WaitSignalLv));
  assert_param(IS_XMC_BURSTMODE_SPLIT(XMC_NORSRAMInitStruct->XMC_EnableBurstModeSplit));
  assert_param(IS_XMC_WAIT_SIGNAL_CONFIG(XMC_NORSRAMInitStruct->XMC_WaitSignalConfig));
  assert_param(IS_XMC_WRITE_OPERATION(XMC_NORSRAMInitStruct->XMC_EnableWrite));
  assert_param(IS_XMC_WAIT_SIGNAL(XMC_NORSRAMInitStruct->XMC_EnableWaitSignal));
  assert_param(IS_XMC_WRITE_TIMING(XMC_NORSRAMInitStruct->XMC_EnableWriteTiming));
  assert_param(IS_XMC_WRITE_BURST_SYN(XMC_NORSRAMInitStruct->XMC_WriteBurstSyn));
  assert_param(IS_XMC_ADDRESS_OP_TIME(XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_AdrOpTime));
  assert_param(IS_XMC_ADDRESS_HOLD_TIME(XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_AdrHoldTime));
  assert_param(IS_XMC_DATA_OP_TIME(XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_DataOpTime));
  assert_param(IS_XMC_INTERVAL_BETWEEN_OP_TIME(XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_IntervalBetweenOP));
  assert_param(IS_XMC_CLK_DIV(XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_CLKPsc));
  assert_param(IS_XMC_DATA_STABLE_TIME(XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_DataStableTime));
  assert_param(IS_XMC_MODE(XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_Mode));

  /* Bank1 NOR/SRAM control register configuration */
  XMC_Bank1->BK1CTRLR[XMC_NORSRAMInitStruct->XMC_Bank] =
    (uint32_t)XMC_NORSRAMInitStruct->XMC_DataAdrMux |
    XMC_NORSRAMInitStruct->XMC_Dev |
    XMC_NORSRAMInitStruct->XMC_BusType |
    XMC_NORSRAMInitStruct->XMC_EnableBurstMode |
    XMC_NORSRAMInitStruct->XMC_EnableAsynWait |
    XMC_NORSRAMInitStruct->XMC_WaitSignalLv |
    XMC_NORSRAMInitStruct->XMC_EnableBurstModeSplit |
    XMC_NORSRAMInitStruct->XMC_WaitSignalConfig |
    XMC_NORSRAMInitStruct->XMC_EnableWrite |
    XMC_NORSRAMInitStruct->XMC_EnableWaitSignal |
    XMC_NORSRAMInitStruct->XMC_EnableWriteTiming |
    XMC_NORSRAMInitStruct->XMC_WriteBurstSyn;

  if(XMC_NORSRAMInitStruct->XMC_Dev == XMC_Dev_NOR)
  {
    XMC_Bank1->BK1CTRLR[XMC_NORSRAMInitStruct->XMC_Bank] |= (uint32_t)BK1CTRLx_NOREN_Set;
  }

  /* Bank1 NOR/SRAM timing register configuration */
  XMC_Bank1->BK1CTRLR[XMC_NORSRAMInitStruct->XMC_Bank + 1] =
    (uint32_t)XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_AdrOpTime |
    (XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_AdrHoldTime << 4) |
    (XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_DataOpTime << 8) |
    (XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_IntervalBetweenOP << 16) |
    (XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_CLKPsc << 20) |
    (XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_DataStableTime << 24) |
    XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_Mode;


  /* Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
  if(XMC_NORSRAMInitStruct->XMC_EnableWriteTiming == XMC_WriteTiming_Enable)
  {
    assert_param(IS_XMC_ADDRESS_OP_TIME(XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_AdrOpTime));
    assert_param(IS_XMC_ADDRESS_HOLD_TIME(XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_AdrHoldTime));
    assert_param(IS_XMC_DATA_OP_TIME(XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_DataOpTime));
    assert_param(IS_XMC_CLK_DIV(XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_CLKPsc));
    assert_param(IS_XMC_DATA_STABLE_TIME(XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_DataStableTime));
    assert_param(IS_XMC_MODE(XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_Mode));
    XMC_Bank1E->BK1TMGWR[XMC_NORSRAMInitStruct->XMC_Bank] =
      (uint32_t)XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_AdrOpTime |
      (XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_AdrHoldTime << 4 ) |
      (XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_DataOpTime << 8) |
      (XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_CLKPsc << 20) |
      (XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_DataStableTime << 24) |
      XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_Mode;
  }
  else
  {
    XMC_Bank1E->BK1TMGWR[XMC_NORSRAMInitStruct->XMC_Bank] = 0x0FFFFFFF;
  }
}

/**
  * @brief  Initializes the XMC NAND Banks according to the specified
  *         parameters in the XMC_NANDInitStruct.
  * @param  XMC_NANDInitStruct : pointer to a XMC_NANDInitType
  *         structure that contains the configuration information for the XMC
  *         NAND specified Banks.
  * @retval None
  */
void XMC_NANDInit(XMC_NANDInitType* XMC_NANDInitStruct)
{
  uint32_t tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000;

  /* Check the parameters */
  assert_param( IS_XMC_NAND_BANK(XMC_NANDInitStruct->XMC_Bank));
  assert_param( IS_XMC_WAIT_OPERATION(XMC_NANDInitStruct->XMC_EnableWait));
  assert_param( IS_XMC_BUS_TYPE(XMC_NANDInitStruct->XMC_BusType));
  assert_param( IS_XMC_ECC_OPERATION(XMC_NANDInitStruct->XMC_EnableECC));
  assert_param( IS_XMC_ECCPAGE_SIZE(XMC_NANDInitStruct->XMC_ECCPageSize));
  assert_param( IS_XMC_DELAY_CR_TIME(XMC_NANDInitStruct->XMC_DelayTimeCR));
  assert_param( IS_XMC_DELAY_AR_TIME(XMC_NANDInitStruct->XMC_DelayTimeAR));
  assert_param(IS_XMC_SETUP_TIME(XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_SetupTime));
  assert_param(IS_XMC_OP_TIME(XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_OpTime));
  assert_param(IS_XMC_HOLD_TIME(XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_HoldTime));
  assert_param(IS_XMC_WRITE_SETUP_TIME(XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_WriteSetupTime));
  assert_param(IS_XMC_SETUP_TIME(XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_SetupTime));
  assert_param(IS_XMC_OP_TIME(XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_OpTime));
  assert_param(IS_XMC_HOLD_TIME(XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_HoldTime));
  assert_param(IS_XMC_WRITE_SETUP_TIME(XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_WriteSetupTime));

  /* Set the tmppcr value according to XMC_NANDInitStruct parameters */
  tmppcr = (uint32_t)XMC_NANDInitStruct->XMC_EnableWait |
           BKxCTRL_Device_NAND |
           XMC_NANDInitStruct->XMC_BusType |
           XMC_NANDInitStruct->XMC_EnableECC |
           XMC_NANDInitStruct->XMC_ECCPageSize |
           (XMC_NANDInitStruct->XMC_DelayTimeCR << 9 ) |
           (XMC_NANDInitStruct->XMC_DelayTimeAR << 13);

  /* Set tmppmem value according to XMC_CommonSpaceTimingStructure parameters */
  tmppmem = (uint32_t)XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_SetupTime |
            (XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_OpTime << 8) |
            (XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_HoldTime << 16) |
            (XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_WriteSetupTime << 24);

  /* Set tmppatt value according to XMC_AttributeSpaceTimingStructure parameters */
  tmppatt = (uint32_t)XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_SetupTime |
            (XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_OpTime << 8) |
            (XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_HoldTime << 16) |
            (XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_WriteSetupTime << 24);

  if(XMC_NANDInitStruct->XMC_Bank == XMC_Bank2_NAND)
  {
    /* XMC_Bank2_NAND registers configuration */
    XMC_Bank2->BK2CTRL = tmppcr;
    XMC_Bank2->BK2TMGMEM = tmppmem;
    XMC_Bank2->BK2TMGATT = tmppatt;
  }
  else
  {
    /* XMC_Bank3_NAND registers configuration */
    XMC_Bank3->BK3CTRL = tmppcr;
    XMC_Bank3->BK3TMGMEM = tmppmem;
    XMC_Bank3->BK3TMGATT = tmppatt;
  }
}

/**
  * @brief  Initializes the XMC PCCARD Bank according to the specified
  *         parameters in the XMC_PCCARDInitStruct.
  * @param  XMC_PCCARDInitStruct : pointer to a XMC_PCCARDInitType
  *         structure that contains the configuration information for the XMC
  *         PCCARD Bank.
  * @retval None
  */
void XMC_PCCARDInit(XMC_PCCARDInitType* XMC_PCCARDInitStruct)
{
  /* Check the parameters */
  assert_param(IS_XMC_WAIT_OPERATION(XMC_PCCARDInitStruct->XMC_EnableWait));
  assert_param(IS_XMC_DELAY_CR_TIME(XMC_PCCARDInitStruct->XMC_DelayTimeCR));
  assert_param(IS_XMC_DELAY_AR_TIME(XMC_PCCARDInitStruct->XMC_DelayTimeAR));

  assert_param(IS_XMC_SETUP_TIME(XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_SetupTime));
  assert_param(IS_XMC_OP_TIME(XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_OpTime));
  assert_param(IS_XMC_HOLD_TIME(XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_HoldTime));
  assert_param(IS_XMC_WRITE_SETUP_TIME(XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_WriteSetupTime));

  assert_param(IS_XMC_SETUP_TIME(XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_SetupTime));
  assert_param(IS_XMC_OP_TIME(XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_OpTime));
  assert_param(IS_XMC_HOLD_TIME(XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_HoldTime));
  assert_param(IS_XMC_WRITE_SETUP_TIME(XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_WriteSetupTime));
  assert_param(IS_XMC_SETUP_TIME(XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_SetupTime));
  assert_param(IS_XMC_OP_TIME(XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_OpTime));
  assert_param(IS_XMC_HOLD_TIME(XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_HoldTime));
  assert_param(IS_XMC_WRITE_SETUP_TIME(XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_WriteSetupTime));

  /* Set the PCR4 register value according to XMC_PCCARDInitStruct parameters */
  XMC_Bank4->BK4CTRL = (uint32_t)XMC_PCCARDInitStruct->XMC_EnableWait |
                       XMC_BusType_16b |
                       (XMC_PCCARDInitStruct->XMC_DelayTimeCR << 9) |
                       (XMC_PCCARDInitStruct->XMC_DelayTimeAR << 13);

  /* Set PMEM4 register value according to XMC_CommonSpaceTimingStructure parameters */
  XMC_Bank4->BK4TMGMEM = (uint32_t)XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_SetupTime |
                         (XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_OpTime << 8) |
                         (XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_HoldTime << 16) |
                         (XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_WriteSetupTime << 24);

  /* Set PATT4 register value according to XMC_AttributeSpaceTimingStructure parameters */
  XMC_Bank4->BK4TMGATT = (uint32_t)XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_SetupTime |
                         (XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_OpTime << 8) |
                         (XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_HoldTime << 16) |
                         (XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_WriteSetupTime << 24);

  /* Set PIO4 register value according to XMC_IOSpaceTimingStructure parameters */
  XMC_Bank4->BK4TMGIO = (uint32_t)XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_SetupTime |
                        (XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_OpTime << 8) |
                        (XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_HoldTime << 16) |
                        (XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_WriteSetupTime << 24);
}

/**
  * @brief  Fills each XMC_NORSRAMInitStruct member with its default value.
  * @param  XMC_NORSRAMInitStruct: pointer to a XMC_NORSRAMInitType
  *         structure which will be initialized.
  * @retval None
  */
void XMC_NORSRAMStructInit(XMC_NORSRAMInitType* XMC_NORSRAMInitStruct)
{
  /* Reset NOR/SRAM Init structure parameters values */
  XMC_NORSRAMInitStruct->XMC_Bank = XMC_Bank1_NORSRAM1;
  XMC_NORSRAMInitStruct->XMC_DataAdrMux = XMC_DataAdrMux_Enable;
  XMC_NORSRAMInitStruct->XMC_Dev = XMC_Dev_SRAM;
  XMC_NORSRAMInitStruct->XMC_BusType = XMC_BusType_8b;
  XMC_NORSRAMInitStruct->XMC_EnableBurstMode = XMC_BurstMode_Disable;
  XMC_NORSRAMInitStruct->XMC_EnableAsynWait = XMC_AsynWait_Disable;
  XMC_NORSRAMInitStruct->XMC_WaitSignalLv = XMC_WaitSignalLv_Low;
  XMC_NORSRAMInitStruct->XMC_EnableBurstModeSplit = XMC_BurstModeSplit_Disable;
  XMC_NORSRAMInitStruct->XMC_WaitSignalConfig = XMC_WaitSignalConfig_BeforeWaitState;
  XMC_NORSRAMInitStruct->XMC_EnableWrite = XMC_WriteOperation_Enable;
  XMC_NORSRAMInitStruct->XMC_EnableWaitSignal = XMC_WaitSignal_Enable;
  XMC_NORSRAMInitStruct->XMC_EnableWriteTiming = XMC_WriteTiming_Disable;
  XMC_NORSRAMInitStruct->XMC_WriteBurstSyn = XMC_WriteBurstSyn_Disable;
  XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_AdrOpTime = 0xF;
  XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_AdrHoldTime = 0xF;
  XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_DataOpTime = 0xFF;
  XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_IntervalBetweenOP = 0xF;
  XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_CLKPsc = 0xF;
  XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_DataStableTime = 0xF;
  XMC_NORSRAMInitStruct->XMC_RWTimingStruct->XMC_Mode = XMC_Mode_A;
  XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_AdrOpTime = 0xF;
  XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_AdrHoldTime = 0xF;
  XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_DataOpTime = 0xFF;
  XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_IntervalBetweenOP = 0xF;
  XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_CLKPsc = 0xF;
  XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_DataStableTime = 0xF;
  XMC_NORSRAMInitStruct->XMC_WTimingStruct->XMC_Mode = XMC_Mode_A;
}

/**
  * @brief  Fills each XMC_NANDInitStruct member with its default value.
  * @param  XMC_NANDInitStruct: pointer to a XMC_NANDInitType
  *         structure which will be initialized.
  * @retval None
  */
void XMC_NANDStructInit(XMC_NANDInitType* XMC_NANDInitStruct)
{
  /* Reset NAND Init structure parameters values */
  XMC_NANDInitStruct->XMC_Bank = XMC_Bank2_NAND;
  XMC_NANDInitStruct->XMC_EnableWait = XMC_WaitOperation_Disable;
  XMC_NANDInitStruct->XMC_BusType = XMC_BusType_8b;
  XMC_NANDInitStruct->XMC_EnableECC = XMC_ECCOperation_Disable;
  XMC_NANDInitStruct->XMC_ECCPageSize = XMC_ECCPageSize_256Bytes;
  XMC_NANDInitStruct->XMC_DelayTimeCR = 0x0;
  XMC_NANDInitStruct->XMC_DelayTimeAR = 0x0;
  XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_SetupTime = 0xFC;
  XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_OpTime = 0xFC;
  XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_HoldTime = 0xFC;
  XMC_NANDInitStruct->XMC_CommonSpaceTimingStruct->XMC_WriteSetupTime = 0xFC;
  XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_SetupTime = 0xFC;
  XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_OpTime = 0xFC;
  XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_HoldTime = 0xFC;
  XMC_NANDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_WriteSetupTime = 0xFC;
}

/**
  * @brief  Fills each XMC_PCCARDInitStruct member with its default value.
  * @param  XMC_PCCARDInitStruct: pointer to a XMC_PCCARDInitType
  *         structure which will be initialized.
  * @retval None
  */
void XMC_PCCARDStructInit(XMC_PCCARDInitType* XMC_PCCARDInitStruct)
{
  /* Reset PCCARD Init structure parameters values */
  XMC_PCCARDInitStruct->XMC_EnableWait = XMC_WaitOperation_Disable;
  XMC_PCCARDInitStruct->XMC_DelayTimeCR = 0x0;
  XMC_PCCARDInitStruct->XMC_DelayTimeAR = 0x0;
  XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_SetupTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_OpTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_HoldTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_CommonSpaceTimingStruct->XMC_WriteSetupTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_SetupTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_OpTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_HoldTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_AttributeSpaceTimingStruct->XMC_WriteSetupTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_SetupTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_OpTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_HoldTime = 0xFC;
  XMC_PCCARDInitStruct->XMC_IOSpaceTimingStruct->XMC_WriteSetupTime = 0xFC;
}

/**
  * @brief  Config the bus turnaround phase
  * @param  XMC_SubBank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_SubBank1_NORSRAM1: XMC SubBank1 NOR/SRAM1
  *     @arg XMC_SubBank1_NORSRAM2: XMC SubBank1 NOR/SRAM2
  *     @arg XMC_SubBank1_NORSRAM3: XMC SubBank1 NOR/SRAM3
  *     @arg XMC_SubBank1_NORSRAM4: XMC SubBank1 NOR/SRAM4
  * @param  W2W_Timing: Bus turnaround phase for consecutive write duration.from 0 to 255 HCLK, default:8 HCLK
  * @param  R2R_Timing: Bus turnaround phase for consecutive read duration.from 0 to 255 HCLK, default:8 HCLK
  * @retval None
  */
void XMC_ExtTimingConfig(uint32_t XMC_SubBank, uint8_t W2W_Timing, uint8_t R2R_Timing)
{
  assert_param(IS_XMC_Sub_NORSRAM_REGION(XMC_SubBank)); 
  
  XMC_Bank1H->BK1EXT[XMC_SubBank] &= 0;
  XMC_Bank1H->BK1EXT[XMC_SubBank] |= (W2W_Timing|(R2R_Timing<<8));  
}

/**
  * @brief  Enables or disables the specified NOR/SRAM Memory Bank.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank1_NORSRAM1: XMC Bank1 NOR/SRAM1
  *     @arg XMC_Bank1_NORSRAM2: XMC Bank1 NOR/SRAM2
  *     @arg XMC_Bank1_NORSRAM3: XMC Bank1 NOR/SRAM3
  *     @arg XMC_Bank1_NORSRAM4: XMC Bank1 NOR/SRAM4
  * @param  NewState: new state of the XMC_Bank. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void XMC_NORSRAMCmd(uint32_t XMC_Bank, FunctionalState NewState)
{
  assert_param(IS_XMC_NORSRAM_REGION(XMC_Bank));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected NOR/SRAM Bank by setting the PBKEN bit in the BCRx register */
    XMC_Bank1->BK1CTRLR[XMC_Bank] |= BK1CTRLx_EN_Set;
  }
  else
  {
    /* Disable the selected NOR/SRAM Bank by clearing the PBKEN bit in the BCRx register */
    XMC_Bank1->BK1CTRLR[XMC_Bank] &= BK1CTRLx_EN_Reset;
  }
}

/**
  * @brief  Enables or disables the specified NAND Memory Bank.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank2_NAND: XMC Bank2 NAND
  *     @arg XMC_Bank3_NAND: XMC Bank3 NAND
  * @param  NewState: new state of the XMC_Bank. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void XMC_NANDCmd(uint32_t XMC_Bank, FunctionalState NewState)
{
  assert_param(IS_XMC_NAND_BANK(XMC_Bank));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected NAND Bank by setting the PBKEN bit in the PCRx register */
    if(XMC_Bank == XMC_Bank2_NAND)
    {
      XMC_Bank2->BK2CTRL |= BKxCTRL_EN_Set;
    }
    else
    {
      XMC_Bank3->BK3CTRL |= BKxCTRL_EN_Set;
    }
  }
  else
  {
    /* Disable the selected NAND Bank by clearing the PBKEN bit in the PCRx register */
    if(XMC_Bank == XMC_Bank2_NAND)
    {
      XMC_Bank2->BK2CTRL &= BKxCTRL_EN_Reset;
    }
    else
    {
      XMC_Bank3->BK3CTRL &= BKxCTRL_EN_Reset;
    }
  }
}

/**
  * @brief  Enables or disables the PCCARD Memory Bank.
  * @param  NewState: new state of the PCCARD Memory Bank.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void XMC_PCCARDCmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the PCCARD Bank by setting the PBKEN bit in the PCR4 register */
    XMC_Bank4->BK4CTRL |= BKxCTRL_EN_Set;
  }
  else
  {
    /* Disable the PCCARD Bank by clearing the PBKEN bit in the PCR4 register */
    XMC_Bank4->BK4CTRL &= BKxCTRL_EN_Reset;
  }
}

/**
  * @brief  Enables or disables the XMC NAND ECC feature.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank2_NAND: XMC Bank2 NAND
  *     @arg XMC_Bank3_NAND: XMC Bank3 NAND
  * @param  NewState: new state of the XMC NAND ECC feature.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void XMC_NANDECCCmd(uint32_t XMC_Bank, FunctionalState NewState)
{
  assert_param(IS_XMC_NAND_BANK(XMC_Bank));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected NAND Bank ECC function by setting the ECCEN bit in the PCRx register */
    if(XMC_Bank == XMC_Bank2_NAND)
    {
      XMC_Bank2->BK2CTRL |= BKxCTRL_ECCEN_Set;
    }
    else
    {
      XMC_Bank3->BK3CTRL |= BKxCTRL_ECCEN_Set;
    }
  }
  else
  {
    /* Disable the selected NAND Bank ECC function by clearing the ECCEN bit in the PCRx register */
    if(XMC_Bank == XMC_Bank2_NAND)
    {
      XMC_Bank2->BK2CTRL &= BKxCTRL_ECCEN_Reset;
    }
    else
    {
      XMC_Bank3->BK3CTRL &= BKxCTRL_ECCEN_Reset;
    }
  }
}

/**
  * @brief  Returns the error correction code register value.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank2_NAND: XMC Bank2 NAND
  *     @arg XMC_Bank3_NAND: XMC Bank3 NAND
  * @retval The Error Correction Code (ECC) value.
  */
uint32_t XMC_GetECC(uint32_t XMC_Bank)
{
  uint32_t eccval = 0x00000000;

  if(XMC_Bank == XMC_Bank2_NAND)
  {
    /* Get the BK2ECC register value */
    eccval = XMC_Bank2->BK2ECC;
  }
  else
  {
    /* Get the BK3ECC register value */
    eccval = XMC_Bank3->BK3ECC;
  }

  /* Return the error correction code value */
  return(eccval);
}

/**
  * @brief  Enables or disables the specified XMC interrupts.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank2_NAND: XMC Bank2 NAND
  *     @arg XMC_Bank3_NAND: XMC Bank3 NAND
  *     @arg XMC_Bank4_PCCARD: XMC Bank4 PCCARD
  * @param  XMC_INT: specifies the XMC interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg XMC_INT_RisingEdge: Rising edge detection interrupt.
  *     @arg XMC_INT_Level: Level edge detection interrupt.
  *     @arg XMC_INT_FallingEdge: Falling edge detection interrupt.
  * @param  NewState: new state of the specified XMC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void XMC_INTConfig(uint32_t XMC_Bank, uint32_t XMC_INT, FunctionalState NewState)
{
  assert_param(IS_XMC_INT_BANK(XMC_Bank));
  assert_param(IS_XMC_INT(XMC_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected XMC_Bank2 interrupts */
    if(XMC_Bank == XMC_Bank2_NAND)
    {
      XMC_Bank2->BK2STS |= XMC_INT;
    }
    /* Enable the selected XMC_Bank3 interrupts */
    else if (XMC_Bank == XMC_Bank3_NAND)
    {
      XMC_Bank3->BK3STS |= XMC_INT;
    }
    /* Enable the selected XMC_Bank4 interrupts */
    else
    {
      XMC_Bank4->BK4STS |= XMC_INT;
    }
  }
  else
  {
    /* Disable the selected XMC_Bank2 interrupts */
    if(XMC_Bank == XMC_Bank2_NAND)
    {

      XMC_Bank2->BK2STS &= (uint32_t)~XMC_INT;
    }
    /* Disable the selected XMC_Bank3 interrupts */
    else if (XMC_Bank == XMC_Bank3_NAND)
    {
      XMC_Bank3->BK3STS &= (uint32_t)~XMC_INT;
    }
    /* Disable the selected XMC_Bank4 interrupts */
    else
    {
      XMC_Bank4->BK4STS &= (uint32_t)~XMC_INT;
    }
  }
}

/**
  * @brief  Checks whether the specified XMC flag is set or not.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank2_NAND: XMC Bank2 NAND
  *     @arg XMC_Bank3_NAND: XMC Bank3 NAND
  *     @arg XMC_Bank4_PCCARD: XMC Bank4 PCCARD
  * @param  XMC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg XMC_FLAG_RisingEdge: Rising egde detection Flag.
  *     @arg XMC_FLAG_Level: Level detection Flag.
  *     @arg XMC_FLAG_FallingEdge: Falling egde detection Flag.
  *     @arg XMC_FLAG_FEMPT: Fifo empty Flag.
  * @retval The new state of XMC_FLAG (SET or RESET).
  */
FlagStatus XMC_GetFlagStatus(uint32_t XMC_Bank, uint32_t XMC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpsr = 0x00000000;

  /* Check the parameters */
  assert_param(IS_XMC_GETFLAG_BANK(XMC_Bank));
  assert_param(IS_XMC_GET_FLAG(XMC_FLAG));

  if(XMC_Bank == XMC_Bank2_NAND)
  {
    tmpsr = XMC_Bank2->BK2STS;
  }
  else if(XMC_Bank == XMC_Bank3_NAND)
  {
    tmpsr = XMC_Bank3->BK3STS;
  }
  /* XMC_Bank4_PCCARD*/
  else
  {
    tmpsr = XMC_Bank4->BK4STS;
  }

  /* Get the flag status */
  if ((tmpsr & XMC_FLAG) != (uint16_t)RESET )
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return bitstatus;
}

/**
  * @brief  Clears the XMC's pending flags.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank2_NAND: XMC Bank2 NAND
  *     @arg XMC_Bank3_NAND: XMC Bank3 NAND
  *     @arg XMC_Bank4_PCCARD: XMC Bank4 PCCARD
  * @param  XMC_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg XMC_FLAG_RisingEdge: Rising egde detection Flag.
  *     @arg XMC_FLAG_Level: Level detection Flag.
  *     @arg XMC_FLAG_FallingEdge: Falling egde detection Flag.
  * @retval None
  */
void XMC_ClearFlag(uint32_t XMC_Bank, uint32_t XMC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_XMC_GETFLAG_BANK(XMC_Bank));
  assert_param(IS_XMC_CLEAR_FLAG(XMC_FLAG)) ;

  if(XMC_Bank == XMC_Bank2_NAND)
  {
    XMC_Bank2->BK2STS &= ~XMC_FLAG;
  }
  else if(XMC_Bank == XMC_Bank3_NAND)
  {
    XMC_Bank3->BK3STS &= ~XMC_FLAG;
  }
  /* XMC_Bank4_PCCARD*/
  else
  {
    XMC_Bank4->BK4STS &= ~XMC_FLAG;
  }
}

/**
  * @brief  Checks whether the specified XMC interrupt has occurred or not.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank2_NAND: XMC Bank2 NAND
  *     @arg XMC_Bank3_NAND: XMC Bank3 NAND
  *     @arg XMC_Bank4_PCCARD: XMC Bank4 PCCARD
  * @param  XMC_INT: specifies the XMC interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg XMC_INT_RisingEdge: Rising edge detection interrupt.
  *     @arg XMC_INT_Level: Level edge detection interrupt.
  *     @arg XMC_INT_FallingEdge: Falling edge detection interrupt.
  * @retval The new state of XMC_INT (SET or RESET).
  */
ITStatus XMC_GetINTStatus(uint32_t XMC_Bank, uint32_t XMC_INT)
{
  ITStatus bitstatus = RESET;
  uint32_t tmpsr = 0x0, itstatus = 0x0, itenable = 0x0;

  /* Check the parameters */
  assert_param(IS_XMC_INT_BANK(XMC_Bank));
  assert_param(IS_XMC_GET_INT(XMC_INT));

  if(XMC_Bank == XMC_Bank2_NAND)
  {
    tmpsr = XMC_Bank2->BK2STS;
  }
  else if(XMC_Bank == XMC_Bank3_NAND)
  {
    tmpsr = XMC_Bank3->BK3STS;
  }
  /* XMC_Bank4_PCCARD*/
  else
  {
    tmpsr = XMC_Bank4->BK4STS;
  }

  itstatus = tmpsr & XMC_INT;

  itenable = tmpsr & (XMC_INT >> 3);

  if ((itstatus != (uint32_t)RESET)  && (itenable != (uint32_t)RESET))
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
  * @brief  Clears the XMC's interrupt pending bits.
  * @param  XMC_Bank: specifies the XMC Bank to be used
  *   This parameter can be one of the following values:
  *     @arg XMC_Bank2_NAND: XMC Bank2 NAND
  *     @arg XMC_Bank3_NAND: XMC Bank3 NAND
  *     @arg XMC_Bank4_PCCARD: XMC Bank4 PCCARD
  * @param  XMC_INT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg XMC_INT_RisingEdge: Rising edge detection interrupt.
  *     @arg XMC_INT_Level: Level edge detection interrupt.
  *     @arg XMC_INT_FallingEdge: Falling edge detection interrupt.
  * @retval None
  */
void XMC_ClearINTPendingBit(uint32_t XMC_Bank, uint32_t XMC_INT)
{
  /* Check the parameters */
  assert_param(IS_XMC_INT_BANK(XMC_Bank));
  assert_param(IS_XMC_INT(XMC_INT));

  if(XMC_Bank == XMC_Bank2_NAND)
  {
    XMC_Bank2->BK2STS &= ~(XMC_INT >> 3);
  }
  else if(XMC_Bank == XMC_Bank3_NAND)
  {
    XMC_Bank3->BK3STS &= ~(XMC_INT >> 3);
  }
  /* XMC_Bank4_PCCARD*/
  else
  {
    XMC_Bank4->BK4STS &= ~(XMC_INT >> 3);
  }
}

/**
  * @}
  */

#endif /* AT32F403xx || AT32F403Axx || AT32F407xx */

/**
  * @}
  */

/**
  * @}
  */


