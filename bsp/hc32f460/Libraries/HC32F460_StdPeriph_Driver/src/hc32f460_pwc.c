/******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_pwc.c
 **
 ** A detailed description is available at
 ** @link PwcGroup PWC description @endlink
 **
 **   - 2018-10-28  CDT  First version for Device Driver Library of PWC.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_pwc.h"
#include "hc32f460_utility.h"

#if (DDL_PWC_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup PwcGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define ENABLE_FCG0_REG_WRITE()             (M4_MSTP->FCG0PC = 0xa5a50001u)
#define DISABLE_FCG0_REG_WRITE()            (M4_MSTP->FCG0PC = 0xa5a50000u)

#define ENABLE_PWR_REG0_WRITE()             (M4_SYSREG->PWR_FPRC |= 0xa503u)
#define DISABLE_PWR_REG0_WRITE()            (M4_SYSREG->PWR_FPRC = (0xa500u | (M4_SYSREG->PWR_FPRC & (uint16_t)(~3u))))

#define ENABLE_PWR_REG_WRITE()              (M4_SYSREG->PWR_FPRC |= 0xa502u)
#define DISABLE_PWR_REG_WRITE()             (M4_SYSREG->PWR_FPRC = (0xa500u | (M4_SYSREG->PWR_FPRC & (uint16_t)(~2u))))

#define ENABLE_PVD_REG_WRITE()              (M4_SYSREG->PWR_FPRC |= 0xa508u)
#define DISABLE_PVD_REG_WRITE()             (M4_SYSREG->PWR_FPRC = (0xa500u | (M4_SYSREG->PWR_FPRC & (uint16_t)(~8u))))

/*! Parameter validity check for wake up event. */
#define IS_PWC_WKUP_EVENT(evt)              ((0x00u) != ((evt) & (0xFF)))

/*! Parameter validity check for wake up event. */
#define IS_PWC_WKUP2_EVENT(evt)             ((0x00u) != ((evt) & (0xB7)))

#define IS_PWC_WKUP_EDGE_EVENT(evt)         ((0x00u) != ((evt) & (0x7F)))

/*! Parameter validity check for wake up flag. */
#define IS_PWC_WKUP0_FLAG(flag)             ((0x00u) != ((flag) & (0x7F)))

/*! Parameter validity check for wake up flag. */
#define IS_PWC_WKUP1_FLAG(flag)             ((0x07u) != ((flag) & (0xB8)))

/*! Parameter validity check for power down mode. */
#define IS_PWC_PWR_DOWN_MODE(md)                                               \
(   ((md) == PowerDownMd1)              ||                                     \
    ((md) == PowerDownMd2)              ||                                     \
    ((md) == PowerDownMd3)              ||                                     \
    ((md) == PowerDownMd4))

/*! Parameter validity check for power down wake_up time control. */
#define IS_PWC_PWR_DOWN_WKUP_TIM(x)                                            \
(   ((x) == Vcap01)                     ||                                     \
    ((x) == Vcap0047))

/*! Parameter validity check for IO retain state while power down. */
#define IS_PWC_PWR_DWON_IO_STATE(x)                                            \
(   ((x) == IoPwrDownRetain)            ||                                     \
    ((x) == IoPwrRstRetain)             ||                                     \
    ((x) == IoHighImp))

/*! Parameter validity check for driver ability while enter stop mode. */
#define IS_PWC_STP_DRIVER_ABILITY(x)                                           \
(   ((x) == StopHighspeed)              ||                                     \
    ((x) == StopUlowspeed))

/*! Parameter validity check for driver ability. */
#define IS_PWC_DRIVER_ABILITY(x)                                               \
(   ((x) == Ulowspeed)                  ||                                     \
    ((x) == HighSpeed))

/*! Parameter validity check for dynamic voltage. */
#define IS_PWC_DYNAMIC_VOLTAGE(val)                                            \
(   ((val) == RunUHighspeed)            ||                                     \
    ((val) == RunUlowspeed)             ||                                     \
    ((val) == RunHighspeed))

/*! Parameter validity check for wake_up edge. */
#define IS_PWC_EDGE_SEL(edg)                                                   \
(   ((edg) == EdgeFalling)              ||                                     \
    ((edg) == EdgeRising))

/*! Parameter validity check for peripheral in fcg0. */
#define IS_PWC_FCG0_PERIPH(per)                                                \
(   (((per) & (0x700C3AEEu)) == (0x00u))  &&                                   \
    ((0x00u) != (per)))

/*! Parameter validity check for peripheral in fcg1. */
#define IS_PWC_FCG1_PERIPH(per)                                                \
(   (((per) & (0xF0F00286u)) == (0x00u))  &&                                     \
    ((0x00u) != (per)))

/*! Parameter validity check for peripheral in fcg2. */
#define IS_PWC_FCG2_PERIPH(per)                                                \
(   (((per) & (0xFFF87800u)) == (0x00u))  &&                                   \
    ((0x00u) != (per)))

/*! Parameter validity check for peripheral in fcg3. */
#define IS_PWC_FCG3_PERIPH(per)                                                \
(   (((per) & (0xFFFFEEECu)) == (0x00u))  &&                                   \
    ((0x00u) != (per)))

/*! Parameter validity check for clock value while stop mode mode. */
#define IS_PWC_STOP_MODE_CLK(clk)                                              \
(   ((clk) == ClkFix)                   ||                                     \
    ((clk) == ClkMrc))

/*! Parameter validity check for flash mode while stop mode mode. */
#define IS_PWC_STOP_MODE_FLASH(x)                                              \
(   ((x) == Wait)                       ||                                     \
    ((x) == NotWait))

/*! Parameter validity check for wake_up timer over flag. */
#define IS_PWC_WKTMOVER_FLAG(flag)                                             \
(   ((flag) == UnEqual)                 ||                                     \
    ((flag) == Equal))

/*! Parameter validity check for ram operate mode. */
#define IS_PWC_RAM_OP_MD(x)                                                    \
(   ((x) == HighSpeedMd)                ||                                     \
    ((x) == UlowSpeedMd))

/*! Parameter validity check for wake_up timer clock. */
#define IS_PWC_WKTM_CLK(clk)                                                   \
(   ((clk) == Wk64hz)                   ||                                     \
    ((clk) == WkXtal32)                 ||                                     \
    ((clk) == WkLrc))


/*! Parameter validity check for handle of pvd. */
#define IS_PWC_PVD_MD(x)                                                       \
(   ((x) == PvdInt)                     ||                                     \
    ((x) == PvdReset))


/*! Parameter validity check for pvd1 level. */
#define IS_PWC_PVD_FILTER_CLK(clk)                                             \
(   ((clk) == PvdLrc025)                ||                                     \
    ((clk) == PvdLrc05)                 ||                                     \
    ((clk) == PvdLrc1)                  ||                                     \
    ((clk) == PvdLrc2))

/*! Parameter validity check for pvd2 level. */
#define IS_PWC_PVD2_LEVEL(lvl)                                                 \
(   ((lvl) == Pvd2Level0)               ||                                     \
    ((lvl) == Pvd2Level1)               ||                                     \
    ((lvl) == Pvd2Level2)               ||                                     \
    ((lvl) == Pvd2Level3)               ||                                     \
    ((lvl) == Pvd2Level4)               ||                                     \
    ((lvl) == Pvd2Level5)               ||                                     \
    ((lvl) == Pvd2Level6)               ||                                     \
    ((lvl) == Pvd2Level7))

/*! Parameter validity check for pvd1 level. */
#define IS_PWC_PVD1_LEVEL(lvl)                                                 \
(   ((lvl) == Pvd1Level0)               ||                                     \
    ((lvl) == Pvd1Level1)               ||                                     \
    ((lvl) == Pvd1Level2)               ||                                     \
    ((lvl) == Pvd1Level3)               ||                                     \
    ((lvl) == Pvd1Level4)               ||                                     \
    ((lvl) == Pvd1Level5)               ||                                     \
    ((lvl) == Pvd1Level6)               ||                                     \
    ((lvl) == Pvd1Level7))

/*! Parameter validity check for pvd interrupt. */
#define IS_PWC_PVD_INT_SEL(x)                                                  \
(   ((x) == NonMskInt)                  ||                                     \
    ((x) == MskInt))

/*! Parameter validity check for valid wakeup source from stop mode. */
#define IS_VALID_WKUP_SRC(x)                                                    \
(   ((x) == INT_USART1_WUPI)                    ||                              \
    ((x) == INT_TMR01_GCMA)                     ||                              \
    ((x) == INT_RTC_ALM)                        ||                              \
    ((x) == INT_RTC_PRD)                        ||                              \
    ((x) == INT_WKTM_PRD)                       ||                              \
    ((x) == INT_ACMP1)                          ||                              \
    ((x) == INT_PVD_PVD1)                       ||                              \
    ((x) == INT_PVD_PVD2)                       ||                              \
    ((x) == INT_SWDT_REFUDF)                    ||                              \
    ((x) == INT_PORT_EIRQ0)                     ||                              \
    ((x) == INT_PORT_EIRQ1)                     ||                              \
    ((x) == INT_PORT_EIRQ2)                     ||                              \
    ((x) == INT_PORT_EIRQ3)                     ||                              \
    ((x) == INT_PORT_EIRQ4)                     ||                              \
    ((x) == INT_PORT_EIRQ5)                     ||                              \
    ((x) == INT_PORT_EIRQ6)                     ||                              \
    ((x) == INT_PORT_EIRQ7)                     ||                              \
    ((x) == INT_PORT_EIRQ8)                     ||                              \
    ((x) == INT_PORT_EIRQ9)                     ||                              \
    ((x) == INT_PORT_EIRQ10)                    ||                              \
    ((x) == INT_PORT_EIRQ11)                    ||                              \
    ((x) == INT_PORT_EIRQ12)                    ||                              \
    ((x) == INT_PORT_EIRQ13)                    ||                              \
    ((x) == INT_PORT_EIRQ14)                    ||                              \
    ((x) == INT_PORT_EIRQ15))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
uint32_t    NVIC_ISER_BAK[5];
uint8_t     u8HrcState = 0u;
uint8_t     u8MrcState = 0u;
uint8_t     u8WkupIntCnt = 0u;
uint8_t     u8StopFlag = 0u;
uint8_t     u8SysClkSrc = 1u;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief  The power mode configuration.
 **
 ** \param  [in] pstcPwrMdCfg           The power mode configuration.
 ** \arg    enPwrDownMd                 The power down mode.
 ** \arg    enRLdo                      Enable or disable RLDO.
 ** \arg    enRetSram                   Enable or disable RetSram.
 ** \arg    enIoRetain                  The IO state while power down.
 ** \arg    enPwrDWkupTm                The wake_up timer while power down.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_PowerModeCfg(const stc_pwc_pwr_mode_cfg_t* pstcPwrMdCfg)
{
    DDL_ASSERT(IS_PWC_PWR_DOWN_MODE(pstcPwrMdCfg->enPwrDownMd ));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcPwrMdCfg->enRLdo));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcPwrMdCfg->enRetSram));
    DDL_ASSERT(IS_PWC_PWR_DWON_IO_STATE(pstcPwrMdCfg->enIoRetain));
    DDL_ASSERT(IS_PWC_PWR_DOWN_WKUP_TIM(pstcPwrMdCfg->enPwrDWkupTm));

    ENABLE_PWR_REG_WRITE();

    M4_SYSREG->PWR_PWRC0 = (pstcPwrMdCfg->enPwrDownMd                                       |
                           (uint8_t)(((Enable == pstcPwrMdCfg->enRLdo) ? 0u : 1u) << 2u)    |
                           (uint8_t)(((Enable == pstcPwrMdCfg->enRetSram) ? 0u : 1u) << 3u) |
                           (pstcPwrMdCfg->enIoRetain << 4u));

    M4_SYSREG->PWR_PWRC3 = (pstcPwrMdCfg->enPwrDWkupTm | (0x03));

    DISABLE_PWR_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enter power down mode.
 **
 ** \param  None
 **
 ** \retval None
 **
 ** \note   This function should be put ram
 **
 ******************************************************************************/
__RAM_FUNC void PWC_EnterPowerDownMd(void)
{
    ENABLE_PVD_REG_WRITE();

    /* Reset PVD1IRS & PVD2IRS */
    M4_SYSREG->PWR_PVDCR1 &= 0xddu;

    DISABLE_PVD_REG_WRITE();

    ENABLE_PWR_REG_WRITE();

    M4_SYSREG->PWR_STPMCR_f.STOP = 1u;

    __disable_irq();
    M4_SYSREG->PWR_PWRC0_f.PWDN = 1u;
    for(uint8_t i = 0u; i < 10u; i++)
    {
        __NOP();
    }
    __enable_irq();

    DISABLE_PWR_REG_WRITE();

    __WFI();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the power down wake up event.
 **
 ** \param  [in] u32Wkup0Event          The wake_up event in PDWKEN0.
 ** \arg    PWC_PDWKEN0_WKUP00          Wake_up 0_0 event
 ** \arg    PWC_PDWKEN0_WKUP01          Wake_up 0_1 event
 ** \arg    PWC_PDWKEN0_WKUP02          Wake_up 0_2 event
 ** \arg    PWC_PDWKEN0_WKUP03          Wake_up 0_3 event
 ** \arg    PWC_PDWKEN0_WKUP10          Wake_up 1_0 event
 ** \arg    PWC_PDWKEN0_WKUP11          Wake_up 1_1 event
 ** \arg    PWC_PDWKEN0_WKUP12          Wake_up 1_2 event
 ** \arg    PWC_PDWKEN0_WKUP13          Wake_up 1_3 event
 **
 ** \param  [in] enNewState             The new state of the wake_up event.
 ** \arg    Enable                      Enable wake_up event.
 ** \arg    Disable                     Disable wake_up event.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_PdWakeup0Cmd(uint32_t u32Wkup0Event, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_WKUP_EVENT(u32Wkup0Event));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PWR_REG_WRITE();

    if(Enable == enNewState)
    {
        M4_SYSREG->PWR_PDWKE0 |= (uint8_t)u32Wkup0Event;
    }
    else
    {
        M4_SYSREG->PWR_PDWKE0 &= (uint8_t)(~u32Wkup0Event);
    }

    DISABLE_PWR_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the power down wake up event.
 **
 ** \param  [in] u32Wkup1Event          The wake_up event in PDWKEN0.
 ** \arg    PWC_PDWKEN1_WKUP20          Wake_up 2_0 event
 ** \arg    PWC_PDWKEN1_WKUP21          Wake_up 2_1 event
 ** \arg    PWC_PDWKEN1_WKUP22          Wake_up 2_2 event
 ** \arg    PWC_PDWKEN1_WKUP23          Wake_up 2_3 event
 ** \arg    PWC_PDWKEN1_WKUP30          Wake_up 3_0 event
 ** \arg    PWC_PDWKEN1_WKUP31          Wake_up 3_1 event
 ** \arg    PWC_PDWKEN1_WKUP32          Wake_up 3_2 event
 ** \arg    PWC_PDWKEN1_WKUP33          Wake_up 3_3 event
 **
 ** \param  [in] enNewState             The new state of the wake_up event.
 ** \arg    Enable                      Enable wake_up event.
 ** \arg    Disable                     Disable wake_up event.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_PdWakeup1Cmd(uint32_t u32Wkup1Event, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_WKUP_EVENT(u32Wkup1Event));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PWR_REG_WRITE();

    if(Enable == enNewState)
    {
        M4_SYSREG->PWR_PDWKE1 |= (uint8_t)u32Wkup1Event;
    }
    else
    {
        M4_SYSREG->PWR_PDWKE1 &= (uint8_t)(~u32Wkup1Event);
    }

    DISABLE_PWR_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the power down wake up event.
 **
 ** \param  [in] u32Wkup2Event           The wake_up event in PDWKEN0.
 ** \arg    PWC_PDWKEN2_PVD1            Wake_up PVD1 event
 ** \arg    PWC_PDWKEN2_PVD2            Wake_up PVD2 event
 ** \arg    PWC_PDWKEN2_NMI             Wake_up NMI event
 ** \arg    PWC_PDWKEN2_RTCPRD          Wake_up RTCPRD event
 ** \arg    PWC_PDWKEN2_RTCAL           Wake_up RTCAL event
 ** \arg    PWC_PDWKEN2_WKTM            Wake_up WKTM event
 **
 ** \param  [in] enNewState             The new state of the wake_up event.
 ** \arg    Enable                      Enable wake_up event.
 ** \arg    Disable                     Disable wake_up event.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_PdWakeup2Cmd(uint32_t u32Wkup2Event, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_WKUP2_EVENT(u32Wkup2Event));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PWR_REG_WRITE();

    if(Enable == enNewState)
    {
        M4_SYSREG->PWR_PDWKE2 |= (uint8_t)u32Wkup2Event;
    }
    else
    {
        M4_SYSREG->PWR_PDWKE2 &= (uint8_t)(~u32Wkup2Event);
    }

    DISABLE_PWR_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Configure the power down wake up event edge.
 **
 ** \param  [in] u8WkupEvent            The wake_up event in PDWKEN0.
 ** \arg    PWC_PDWKUP_EDGE_WKP0          Wake_up WKP0 event
 ** \arg    PWC_PDWKUP_EDGE_WKP1          Wake_up WKP1 event
 ** \arg    PWC_PDWKUP_EDGE_WKP2          Wake_up WKP2 event
 ** \arg    PWC_PDWKUP_EDGE_WKP3          Wake_up WKP3 event
 ** \arg    PWC_PDWKUP_EDGE_PVD1          Wake_up PVD1 event
 ** \arg    PWC_PDWKUP_EDGE_PVD2          Wake_up PVD2 event
 ** \arg    PWC_PDWKUP_EDGE_NMI           Wake_up NMI event
 **
 ** \param  [in] enEdge                 The wake_up event edge select.
 ** \arg    EdgeRising                   Wake_up event edge rising.
 ** \arg    EdgeFalling                  Wake_up event edge falling.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_PdWakeupEvtEdgeCfg(uint8_t u8WkupEvent, en_pwc_edge_sel_t enEdge)
{
    DDL_ASSERT(IS_PWC_WKUP_EDGE_EVENT(u8WkupEvent));
    DDL_ASSERT(IS_PWC_EDGE_SEL(enEdge));

    ENABLE_PWR_REG_WRITE();

    if(EdgeRising == enEdge)
    {
        M4_SYSREG->PWR_PDWKES |= (uint8_t)u8WkupEvent;
    }
    else
    {
        M4_SYSREG->PWR_PDWKES &= (uint8_t)(~u8WkupEvent);
    }

    DISABLE_PWR_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Get wake_up event in PDWKF0 flag.
 **
 ** \param  [in] u8WkupFlag             The wake_up event in PDWKF0.
 ** \arg    PWC_PTWK0_WKUPFLAG          Ptwk0 wake_up flag
 ** \arg    PWC_PTWK1_WKUPFLAG          Ptwk1 wake_up flag
 ** \arg    PWC_PTWK2_WKUPFLAG          Ptwk2 wake_up flag
 ** \arg    PWC_PTWK3_WKUPFLAG          Ptwk3 wake_up flag
 ** \arg    PWC_PVD1_WKUPFLAG           Pvd1 wake_up flag
 ** \arg    PWC_PVD2_WKUPFLAG           Pvd2 wake_up flag
 ** \arg    PWC_NMI_WKUPFLAG            Nmi wake_up flag
 **
 ** \retval en_flag_status_t
 **
 ** \note   None
 **
 ******************************************************************************/
en_flag_status_t PWC_GetWakeup0Flag(uint8_t u8WkupFlag)
{
    uint8_t u8flag;
    DDL_ASSERT(IS_PWC_WKUP0_FLAG(u8WkupFlag));

    u8flag = (M4_SYSREG->PWR_PDWKF0 & u8WkupFlag);

    return ((0u == u8flag) ? Reset : Set);
}

/**
 *******************************************************************************
 ** \brief  Get wake_up event in PDWKF1 flag.
 **
 ** \param  [in] u8WkupFlag             The wake_up event in PDWKF1.
 ** \arg    PWC_RTCPRD_WKUPFALG         Rtcprd wake_up flag
 ** \arg    PWC_RTCAL_WKUPFLAG          Rtcal wake_up flag
 ** \arg    PWC_WKTM_WKUPFLAG           Wktm wake_up flag
 **
 ** \retval en_flag_status_t
 **
 ** \note   None
 **
 ******************************************************************************/
en_flag_status_t PWC_GetWakeup1Flag(uint8_t u8WkupFlag)
{
    uint8_t u8flag;
    DDL_ASSERT(IS_PWC_WKUP1_FLAG(u8WkupFlag));

    u8flag = (M4_SYSREG->PWR_PDWKF1 & u8WkupFlag);

    return ((0u == u8flag) ? Reset : Set);
}

/**
 *******************************************************************************
 ** \brief  clear wake_up event in PDWKF0 flag.
 **
 ** \param  [in] u8WkupFlag             The wake_up event in PDWKF0.
 ** \arg    PWC_PTWK0_WKUPFLAG          Ptwk0 wake_up flag
 ** \arg    PWC_PTWK1_WKUPFLAG          Ptwk1 wake_up flag
 ** \arg    PWC_PTWK2_WKUPFLAG          Ptwk2 wake_up flag
 ** \arg    PWC_PTWK3_WKUPFLAG          Ptwk3 wake_up flag
 ** \arg    PWC_PVD1_WKUPFLAG           Pvd1 wake_up flag
 ** \arg    PWC_PVD2_WKUPFLAG           Pvd2 wake_up flag
 ** \arg    PWC_NMI_WKUPFLAG            Nmi wake_up flag
 **
 ** \retval en_flag_status_t
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_ClearWakeup0Flag(uint8_t u8WkupFlag)
{
    DDL_ASSERT(IS_PWC_WKUP0_FLAG(u8WkupFlag));

    ENABLE_PWR_REG_WRITE();

    M4_SYSREG->PWR_PDWKF0 &= (uint8_t)(~u8WkupFlag);

    DISABLE_PWR_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  clear wake_up event in PDWKF1 flag.
 **
 ** \param  [in] u8WkupFlag             The wake_up event in PDWKF1.
 ** \arg    PWC_RTCPRD_WKUPFALG         Rtcprd wake_up flag
 ** \arg    PWC_RTCAL_WKUPFLAG          Rtcal wake_up flag
 ** \arg    PWC_WKTM_WKUPFLAG           Wktm wake_up flag
 **
 ** \retval en_flag_status_t
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_ClearWakeup1Flag(uint8_t u8WkupFlag)
{
    DDL_ASSERT(IS_PWC_WKUP1_FLAG(u8WkupFlag));

    ENABLE_PWR_REG_WRITE();

    M4_SYSREG->PWR_PDWKF1 &= (uint8_t)(~u8WkupFlag);

    DISABLE_PWR_REG_WRITE();
}
/**
 *******************************************************************************
 ** \brief  Enable or disable power monitor .
 **
 ** \param  [in] enNewState             The power monitor state.
 ** \arg    Enable                      Enable power monitor.
 ** \arg    Disable                     Disable power monitor.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_PwrMonitorCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PWR_REG_WRITE();

    M4_SYSREG->PWR_PWCMR_f.ADBUFE = ((Enable == enNewState) ? 1u : 0u);

    DISABLE_PWR_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the FCG0 peripheral clock.
 **
 ** \note   After reset,the peripheral clock is disabled and the application
 **         software has to enable this clock before using it.
 **
 ** \param  [in] u32Fcg0Periph          The peripheral in FCG0.
 ** \arg    PWC_FCG0_PERIPH_SRAMH       RAMHS clock
 ** \arg    PWC_FCG0_PERIPH_SRAM12      RAM0 clock
 ** \arg    PWC_FCG0_PERIPH_SRAM3       ECCRAM clock
 ** \arg    PWC_FCG0_PERIPH_SRAMRET     RetRAM clock
 ** \arg    PWC_FCG0_PERIPH_DMA1        DMA1 clock
 ** \arg    PWC_FCG0_PERIPH_DMA2        DMA2 clock
 ** \arg    PWC_FCG0_PERIPH_FCM         FCM clock
 ** \arg    PWC_FCG0_PERIPH_AOS         PTDIS clock
 ** \arg    PWC_FCG0_PERIPH_AES         AES clock
 ** \arg    PWC_FCG0_PERIPH_HASH        HASH clock
 ** \arg    PWC_FCG0_PERIPH_TRNG        TRNG clock
 ** \arg    PWC_FCG0_PERIPH_CRC         CRC clock
 ** \arg    PWC_FCG0_PERIPH_DCU1        DCU1 clock
 ** \arg    PWC_FCG0_PERIPH_DCU2        DCU2 clock
 ** \arg    PWC_FCG0_PERIPH_DCU3        DCU3 clock
 ** \arg    PWC_FCG0_PERIPH_DCU4        DCU4 clock
 ** \arg    PWC_FCG0_PERIPH_KEY         KEY clock

 ** \param  [in] enNewState             The new state of the clock output.
 ** \arg    Enable                      Enable clock output.
 ** \arg    Disable                     Disable clock output.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_Fcg0PeriphClockCmd(uint32_t u32Fcg0Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG0_PERIPH(u32Fcg0Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_FCG0_REG_WRITE();

    if(Enable == enNewState)
    {
        M4_MSTP->FCG0 &= ~u32Fcg0Periph;
    }
    else
    {
        M4_MSTP->FCG0 |= u32Fcg0Periph;
    }

    DISABLE_FCG0_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the FCG1 peripheral clock.
 **
 ** \note   After reset,the peripheral clock is disabled and the application
 **         software has to enable this clock before using it.
 **
 ** \param  [in] u32Fcg1Periph          The peripheral in FCG1.
 ** \arg    PWC_FCG1_PERIPH_CAN         CAN clock
 ** \arg    PWC_FCG1_PERIPH_QSPI        QSPI clock
 ** \arg    PWC_FCG1_PERIPH_I2C1        I2C1 clock
 ** \arg    PWC_FCG1_PERIPH_I2C2        I2C2 clock
 ** \arg    PWC_FCG1_PERIPH_I2C3        I2C3 clock
 ** \arg    PWC_FCG1_PERIPH_USBFS       USBFS clock
 ** \arg    PWC_FCG1_PERIPH_SDIOC1      SDIOC1 clock
 ** \arg    PWC_FCG1_PERIPH_SDIOC2      SDIOC2 clock
 ** \arg    PWC_FCG1_PERIPH_I2S1        I2S1 clock
 ** \arg    PWC_FCG1_PERIPH_I2S2        I2S2 clock
 ** \arg    PWC_FCG1_PERIPH_I2S3        I2S3 clock
 ** \arg    PWC_FCG1_PERIPH_I2S4        I2S4 clock
 ** \arg    PWC_FCG1_PERIPH_SPI1        SPI1 clock
 ** \arg    PWC_FCG1_PERIPH_SPI2        SPI2 clock
 ** \arg    PWC_FCG1_PERIPH_SPI3        SPI3 clock
 ** \arg    PWC_FCG1_PERIPH_SPI4        SPI4 clock
 ** \arg    PWC_FCG1_PERIPH_USART1      USART1 clock
 ** \arg    PWC_FCG1_PERIPH_USART2      USART2 clock
 ** \arg    PWC_FCG1_PERIPH_USART3      USART3 clock
 ** \arg    PWC_FCG1_PERIPH_USART4      USART4 clock
 **
 ** \param  [in] enNewState             The new state of the clock output.
 ** \arg    Enable                      Enable clock output.
 ** \arg    Disable                     Disable clock output.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_Fcg1PeriphClockCmd(uint32_t u32Fcg1Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG1_PERIPH(u32Fcg1Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        M4_MSTP->FCG1 &= ~u32Fcg1Periph;
    }
    else
    {
        M4_MSTP->FCG1 |= u32Fcg1Periph;
    }
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the FCG2 peripheral clock.
 **
 ** \note   After reset,the peripheral clock is disabled and the application
 **         software has to enable this clock before using it.
 **
 ** \param  [in] u32Fcg2Periph          The peripheral in FCG2.
 ** \arg    PWC_FCG2_PERIPH_TIM01       TIM01 clock
 ** \arg    PWC_FCG2_PERIPH_TIM02       TIM02 clock
 ** \arg    PWC_FCG2_PERIPH_TIMA1       TIMA1 clock
 ** \arg    PWC_FCG2_PERIPH_TIMA2       TIMA2 clock
 ** \arg    PWC_FCG2_PERIPH_TIMA3       TIMA3 clock
 ** \arg    PWC_FCG2_PERIPH_TIMA4       TIMA4 clock
 ** \arg    PWC_FCG2_PERIPH_TIMA5       TIMA5 clock
 ** \arg    PWC_FCG2_PERIPH_TIMA6       TIMA6 clock
 ** \arg    PWC_FCG2_PERIPH_TIM41       TIM41 clock
 ** \arg    PWC_FCG2_PERIPH_TIM42       TIM42 clock
 ** \arg    PWC_FCG2_PERIPH_TIM43       TIM43 clock
 ** \arg    PWC_FCG2_PERIPH_EMB         EMB clock
 ** \arg    PWC_FCG2_PERIPH_TIM61       TIM61 clock
 ** \arg    PWC_FCG2_PERIPH_TIM62       TIM62 clock
 ** \arg    PWC_FCG2_PERIPH_TIM63       TIM63 clock

 **
 ** \param  [in] enNewState             The new state of the clock output.
 ** \arg    Enable                      Enable clock output.
 ** \arg    Disable                     Disable clock output.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_Fcg2PeriphClockCmd(uint32_t u32Fcg2Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG2_PERIPH(u32Fcg2Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        M4_MSTP->FCG2 &= ~u32Fcg2Periph;
    }
    else
    {
        M4_MSTP->FCG2 |= u32Fcg2Periph;
    }
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the FCG3 peripheral clock.
 **
 ** \note   After reset,the peripheral clock is disabled and the application
 **         software has to enable this clock before using it.
 **
 ** \param  [in] u32Fcg3Periph          The peripheral in FCG3.
 ** \arg    PWC_FCG3_PERIPH_ADC1        ADC1 clock
 ** \arg    PWC_FCG3_PERIPH_ADC2        ADC2 clock
 ** \arg    PWC_FCG3_PERIPH_CMP         CMP clock
 ** \arg    PWC_FCG3_PERIPH_OTS         OTS clock
 **
 ** \param  [in] enNewState             The new state of the clock output.
 ** \arg    Enable                      Enable clock output.
 ** \arg    Disable                     Disable clock output.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_Fcg3PeriphClockCmd(uint32_t u32Fcg3Periph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_PWC_FCG3_PERIPH(u32Fcg3Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        M4_MSTP->FCG3 &= ~u32Fcg3Periph;
    }
    else
    {
        M4_MSTP->FCG3 |= u32Fcg3Periph;
    }
}

/**
 *******************************************************************************
 ** \brief  The stop mode configuration.
 **
 ** \param  [in] pstcStpMdCfg           Pointer to stop mode configuration structure.
 ** \arg    Enable                      Enable stop mode.
 ** \arg    Disable                     Disable stop mode.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
en_result_t PWC_StopModeCfg(const stc_pwc_stop_mode_cfg_t*  pstcStpMdCfg)
{
    en_result_t enRet = Ok;

    DDL_ASSERT(IS_PWC_STOP_MODE_FLASH(pstcStpMdCfg->enStopFlash));
    DDL_ASSERT(IS_PWC_STOP_MODE_CLK(pstcStpMdCfg->enStopClk));

    ENABLE_PWR_REG0_WRITE();

    M4_SYSREG->PWR_STPMCR = (pstcStpMdCfg->enStopFlash          |
                            (pstcStpMdCfg->enStopClk << 1u)     |
                            (1u << 14u));

    /* if should close HRC & PLL while stop mode, please disable before modifying the register */
    if(Disable == pstcStpMdCfg->enPll)
    {
        /* PLL is system clock */
        if(5u == M4_SYSREG->CMU_CKSWR_f.CKSW)
        {
            enRet = ErrorInvalidParameter;
        }
        else
        {
            /* Disable PLL */
            M4_SYSREG->CMU_PLLCR_f.MPLLOFF = 1u;
        }
    }

    /* Hrc power should be enable. */
    M4_SYSREG->PWR_PWRC1_f.VHRCSD = 0u;
    M4_SYSREG->PWR_PWRC1_f.VPLLSD = ((Enable == pstcStpMdCfg->enPll) ? 0u : 1u);
    M4_SYSREG->PWR_PWRC1_f.STPDAS = pstcStpMdCfg->enStpDrvAbi;

    DISABLE_PWR_REG0_WRITE();

    return enRet;
}

/**
 *******************************************************************************
 ** \brief  Enable or disable the power down wake up event.
 **
 ** \param  [in] u32Wkup0Event          The wake_up event in PDWKEN0.
 ** \arg    PWC_STOPWKUPEN_EIRQ0        EIRQ0 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ1        EIRQ1 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ2        EIRQ2 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ3        EIRQ3 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ4        EIRQ4 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ5        EIRQ5 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ6        EIRQ6 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ7        EIRQ7 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ8        EIRQ8 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ9        EIRQ9 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ10       EIRQ10 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ11       EIRQ11 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ12       EIRQ12 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ13       EIRQ13 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ14       EIRQ14 wake_up event
 ** \arg    PWC_STOPWKUPEN_EIRQ15       EIRQ15 wake_up event
 ** \arg    PWC_STOPWKUPEN_SWDT         SWDT wake_up event
 ** \arg    PWC_STOPWKUPEN_VDU1         VDU1 wake_up event
 ** \arg    PWC_STOPWKUPEN_VDU2         VDU2 wake_up event
 ** \arg    PWC_STOPWKUPEN_CMPI0        CMPI0 wake_up event
 ** \arg    PWC_STOPWKUPEN_WKTM         WKTM wake_up event
 ** \arg    PWC_STOPWKUPEN_RTCAL        RTCAL wake_up event
 ** \arg    PWC_STOPWKUPEN_RTCPRD       RTCPRD wake_up event
 ** \arg    PWC_STOPWKUPEN_TMR0         TMR0 wake_up event
 ** \arg    PWC_STOPWKUPEN_USARTRXD     USARTRXD wake_up event
 **
 ** \param  [in] enNewState             The new state of the wake_up event.
 ** \arg    Enable                      Enable wake_up event.
 ** \arg    Disable                     Disable wake_up event.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_StopWkupCmd(uint32_t u32Wkup0Event, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(Enable == enNewState)
    {
        M4_INTC->WUPEN |= u32Wkup0Event;
    }
    else
    {
        M4_INTC->WUPEN &= ~u32Wkup0Event;
    }
}

/**
 *******************************************************************************
 ** \brief  Enter sleep mode.
 **
 ** \param  None
 **
 ** \retval None
 **
 ******************************************************************************/
void PWC_EnterSleepMd(void)
{
    ENABLE_PWR_REG_WRITE();

    M4_SYSREG->PWR_STPMCR_f.STOP = 0u;
    M4_SYSREG->PWR_PWRC0_f.PWDN = 0u;

    DISABLE_PWR_REG_WRITE();

    __WFI();
}
/**
 *******************************************************************************
 ** \brief  Ram area power down commond.
 **
 ** \param  [in] u32RamCtlBit           The ram area contol.
 ** \arg    PWC_RAMPWRDOWN_SRAM1        Ram0(0x20000000-0x2000FFFF) power down control.
 ** \arg    PWC_RAMPWRDOWN_SRAM2        Ram1(0x20010000-0x2001FFFF) power down control.
 ** \arg    PWC_RAMPWRDOWN_SRAM3        Ram2(0x20020000-0x20026FFF) power down control.
 ** \arg    PWC_RAMPWRDOWN_SRAMH        Ram3(0x1FFF8000-0x1FFFFFFF) power down control.
 ** \arg    PWC_RAMPWRDOWN_USBFS        Usbfs power down control.
 ** \arg    PWC_RAMPWRDOWN_SDIOC0       Sdioc0 power down control.
 ** \arg    PWC_RAMPWRDOWN_SDIOC1       Sdioc1 power down control.
 ** \arg    PWC_RAMPWRDOWN_CAN          Can power down control.
 ** \arg    PWC_RAMPWRDOWN_CACHE        Cache power down control.
 ** \arg    PWC_RAMPWRDOWN_FULL         Full.
 **
 ** \param  [in] enNewState             The new state of the Ram area.
 ** \arg    Enable                      Ten ram area run.
 ** \arg    Disable                     The ram area power down.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_RamPwrdownCmd(uint32_t u32RamCtlBit, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PWR_REG_WRITE();

    if(Enable == enNewState)
    {
        M4_SYSREG->PWR_RAMPC0 &= ~u32RamCtlBit;
    }
    else
    {
        M4_SYSREG->PWR_RAMPC0 |= u32RamCtlBit;
    }

    DISABLE_PWR_REG_WRITE();
}

void PWC_RamOpMdConfig(en_pwc_ram_op_md_t enRamOpMd)
{
    DDL_ASSERT(IS_PWC_RAM_OP_MD(enRamOpMd));

    ENABLE_PWR_REG_WRITE();

    M4_SYSREG->PWR_RAMOPM = enRamOpMd;

    DISABLE_PWR_REG_WRITE();
}
/**
 *******************************************************************************
 ** \brief  Enable or disable XTAL/RTC/WKTM bias current.
 **
 ** \param  [in] enNewState             The XTAL/RTC/WKTM bias current state.
 ** \arg    Enable                      Enable XTAL/RTC/WKTM bias current.
 ** \arg    Disable                     Disable XTAL/RTC/WKTM bias current.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_Xtal32CsCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PWR_REG0_WRITE();

    M4_SYSREG->PWR_XTAL32CS_f.CSDIS = ((Enable == enNewState) ? 0u : 1u);

    DISABLE_PWR_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  wake_up timer control.
 **
 ** \param  [in] pstcWktmCtl            The wake_up timer configuration.
 ** \arg    enWktmEn                    Enable or disable wake_up timer.
 ** \arg    enWkclk                     The wake_up timer clock.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_WktmControl(const stc_pwc_wktm_ctl_t* pstcWktmCtl)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcWktmCtl->enWktmEn));
    DDL_ASSERT(IS_PWC_WKTM_CLK(pstcWktmCtl->enWkclk));
    DDL_ASSERT(IS_PWC_WKTMOVER_FLAG(pstcWktmCtl->enWkOverFlag));

    ENABLE_PWR_REG_WRITE();

    M4_WKTM->CR = ((pstcWktmCtl->u16WktmCmp & PWC_WKTMCMP_MSK)        |
                  (pstcWktmCtl->enWkOverFlag << 12)                   |
                  (pstcWktmCtl->enWkclk << 13)                        |
                  (pstcWktmCtl->enWktmEn << 15));

    DISABLE_PWR_REG_WRITE();
}
/**
 *******************************************************************************
 ** \brief  The pvd configuration.
 **
 ** \param  [in] pstcPvdCfg             The pvd configuration.
 ** \arg    enPtwk0Edge                 Ptwk0 edge
 ** \arg    enPtwk1Edge                 Ptwk1 edge
 ** \arg    enPtwk2Edge                 Ptwk2 edge
 ** \arg    enPtwk3Edge                 Ptwk3 edge
 ** \arg    enPvd1Edge                  Pvd1 edge
 ** \arg    enPvd1Edge                  Pvd2 edge
 ** \arg    enNmiEdge                   Nmi edge
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_PvdCfg(const stc_pwc_pvd_cfg_t* pstcPvdCfg)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcPvdCfg->stcPvd1Ctl.enPvdIREn));
    DDL_ASSERT(IS_PWC_PVD_MD(pstcPvdCfg->stcPvd1Ctl.enPvdMode));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcPvdCfg->stcPvd1Ctl.enPvdCmpOutEn));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcPvdCfg->stcPvd2Ctl.enPvdIREn));
    DDL_ASSERT(IS_PWC_PVD_MD(pstcPvdCfg->stcPvd2Ctl.enPvdMode));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcPvdCfg->stcPvd2Ctl.enPvdCmpOutEn));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcPvdCfg->enPvd1FilterEn));
    DDL_ASSERT(IS_PWC_PVD_FILTER_CLK(pstcPvdCfg->enPvd1Filtclk));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcPvdCfg->enPvd2FilterEn));
    DDL_ASSERT(IS_PWC_PVD_FILTER_CLK(pstcPvdCfg->enPvd2Filtclk));
    DDL_ASSERT(IS_PWC_PVD1_LEVEL(pstcPvdCfg->enPvd1Level));
    DDL_ASSERT(IS_PWC_PVD2_LEVEL(pstcPvdCfg->enPvd2Level));
    DDL_ASSERT(IS_PWC_PVD_INT_SEL(pstcPvdCfg->enPvd1Int));
    DDL_ASSERT(IS_PWC_PVD_INT_SEL(pstcPvdCfg->enPvd2Int));

    ENABLE_PVD_REG_WRITE();

    /* Config Pvd control. */
    M4_SYSREG->PWR_PVDCR1 = (pstcPvdCfg->stcPvd1Ctl.enPvdIREn           |
                            (pstcPvdCfg->stcPvd1Ctl.enPvdMode << 1)     |
                            (pstcPvdCfg->stcPvd1Ctl.enPvdCmpOutEn << 2) |
                            (pstcPvdCfg->stcPvd2Ctl.enPvdIREn<< 4)      |
                            (pstcPvdCfg->stcPvd2Ctl.enPvdMode << 5)     |
                            (pstcPvdCfg->stcPvd2Ctl.enPvdCmpOutEn << 6));
    /* Set pvd filter sampling. */
    M4_SYSREG->PWR_PVDFCR = (~(pstcPvdCfg->enPvd1FilterEn)              |
                            (pstcPvdCfg->enPvd1Filtclk << 1)            |
                            ((~pstcPvdCfg->enPvd2FilterEn) << 4)        |
                            (pstcPvdCfg->enPvd2Filtclk << 5));
    /* Set pvd level. */
    M4_SYSREG->PWR_PVDLCR = (pstcPvdCfg->enPvd1Level                    |
                            (pstcPvdCfg->enPvd2Level << 4));
    /* Set pvd interrupt(non_maskable or maskable). */
    M4_SYSREG->PWR_PVDICR = (pstcPvdCfg->enPvd1Int                      |
                            (pstcPvdCfg->enPvd2Int << 4));

    DISABLE_PVD_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable pvd1.
 **
 ** \param  [in] enNewState             The pvd1 state.
 ** \arg    Enable                      Enable pvd1.
 ** \arg    Disable                     Disable pvd1.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_Pvd1Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PVD_REG_WRITE();

    M4_SYSREG->PWR_PVDCR0_f.PVD1EN = ((Enable == enNewState) ? 1u : 0u);

    DISABLE_PVD_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable pvd2.
 **
 ** \param  [in] enNewState             The pvd2 state.
 ** \arg    Enable                      Enable pvd2.
 ** \arg    Disable                     Disable pvd2.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_Pvd2Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PVD_REG_WRITE();

    M4_SYSREG->PWR_PVDCR0_f.PVD2EN = ((Enable == enNewState) ? 1u : 0u);

    DISABLE_PVD_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable external vcc.
 **
 ** \param  [in] enNewState             The external vcc state.
 ** \arg    Enable                      Enable external vcc.
 ** \arg    Disable                     Disable external vcc.
 **
 ** \retval None
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_ExVccCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PVD_REG_WRITE();

    M4_SYSREG->PWR_PVDCR0_f.EXVCCINEN = ((Enable == enNewState) ? 1u : 0u);

    DISABLE_PVD_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Get pvd detection status.
 **
 ** \param  [in] enPvd              The unit of pvd detection.
 ** \arg    PvdU1                   The unit1 of pvd detection.
 ** \arg    PvdU2                   The unit2 of pvd detection.
 **
 ** \retval en_flag_status_t
 **
 ** \note   None
 **
 ******************************************************************************/
en_flag_status_t PWC_GetPvdStatus(en_pwc_pvd_t enPvd)
{
    uint8_t u8flag = 0u;

    switch(enPvd)
    {
        case PvdU1:
            u8flag = M4_SYSREG->PWR_PVDDSR_f.PVD1MON;
            break;
        case PvdU2:
            u8flag = M4_SYSREG->PWR_PVDDSR_f.PVD2MON;
            break;
        default:
            break;
    }

    return ((1u == u8flag) ? Set : Reset);
}

/**
 *******************************************************************************
 ** \brief  Get pvd detection flag.
 **
 ** \param  [in] enPvd                  The unit of pvd detection.
 ** \arg    PvdU1                       The unit1 of pvd detection.
 ** \arg    PvdU2                       The unit2 of pvd detection.
 **
 ** \retval en_flag_status_t
 **
 ** \note   None
 **
 ******************************************************************************/
en_flag_status_t PWC_GetPvdFlag(en_pwc_pvd_t enPvd)
{
    uint8_t u8flag = 0u;

    switch(enPvd)
    {
        case PvdU1:
            u8flag = M4_SYSREG->PWR_PVDDSR_f.PVD1DETFLG;
            break;
        case PvdU2:
            u8flag = M4_SYSREG->PWR_PVDDSR_f.PVD2DETFLG;
            break;
        default:
            break;
    }

    return ((1u == u8flag) ? Set : Reset);
}

/**
 *******************************************************************************
 ** \brief  Clear pvd detection flag.
 **
 ** \param  [in] enPvd                  The unit of pvd detection.
 ** \arg    PvdU1                       The unit1 of pvd detection.
 ** \arg    PvdU2                       The unit2 of pvd detection.
 **
 ** \note   None
 **
 ******************************************************************************/
void PWC_ClearPvdFlag(en_pwc_pvd_t enPvd)
{
    ENABLE_PVD_REG_WRITE();
    switch(enPvd)
    {
        case PvdU1:
            M4_SYSREG->PWR_PVDDSR_f.PVD1MON = 0u;
            break;
        case PvdU2:
            M4_SYSREG->PWR_PVDDSR_f.PVD2MON = 0u;
            break;
        default:
            break;
    }
    DISABLE_PVD_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable HRC power.
 **
 ** \param  [in] enNewState             The HRC power state.
 ** \arg    Enable                      Enable HRC power.
 ** \arg    Disable                     Disable HRC power.
 **
 ** \retval None
 **
 ******************************************************************************/
void PWC_HrcPwrCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PWR_REG_WRITE();

     M4_SYSREG->PWR_PWRC1_f.VHRCSD = ((Enable == enNewState) ? 0u : 1u);

    DISABLE_PWR_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Enable or disable PLL power.
 **
 ** \param  [in] enNewState             The PLL power state.
 ** \arg    Enable                      Enable PLL power.
 ** \arg    Disable                     Disable PLL power.
 **
 ** \retval None
 **
 ******************************************************************************/
void PWC_PllPwrCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    ENABLE_PWR_REG_WRITE();

     M4_SYSREG->PWR_PWRC1_f.VPLLSD = ((Enable == enNewState) ? 0u : 1u);

    DISABLE_PWR_REG_WRITE();
}

/**
 *******************************************************************************
 ** \brief NVIC backup and disable before entry from stop mode
 **
 ** param  None
 **
 ** retval None
 **
 *****************************************************************************/
void PWC_enNvicBackup(void)
{
    uint8_t u8Cnt;
    stc_intc_sel_field_t *stcIntSel;
    uint32_t u32WakeupSrc = INT_MAX;

    /* Backup NVIC set enable register for IRQ0~143*/
    for (u8Cnt = 0u; u8Cnt < sizeof(NVIC_ISER_BAK)/sizeof(uint32_t); u8Cnt++)
    {
        NVIC_ISER_BAK[u8Cnt] = NVIC->ISER[u8Cnt];
    }

    /* Disable share vector */
    for (u8Cnt = 128u; u8Cnt < 144u; u8Cnt++)
    {
        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
    }

    for (u8Cnt = 0u; u8Cnt < 128u; u8Cnt++)
    {
        stcIntSel = (stc_intc_sel_field_t *)((uint32_t)(&M4_INTC->SEL0) + (4ul * u8Cnt));
        /* Disable NVIC if it is the wakeup-able source from stop mode */
        u32WakeupSrc = stcIntSel->INTSEL;
        if (IS_VALID_WKUP_SRC(u32WakeupSrc))
        {
            switch (stcIntSel->INTSEL)
            {
                case INT_USART1_WUPI:
                    if (Reset == bM4_INTC_WUPEN_RXWUEN)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_TMR01_GCMA:
                    if (Reset == bM4_INTC_WUPEN_TMR0WUEN)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_RTC_ALM:
                    if (Reset == bM4_INTC_WUPEN_RTCALMWUEN)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_RTC_PRD:
                    if (Reset == bM4_INTC_WUPEN_RTCPRDWUEN)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_WKTM_PRD:
                    if (Reset == bM4_INTC_WUPEN_WKTMWUEN)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_ACMP1:
                    if (Reset == bM4_INTC_WUPEN_CMPI0WUEN)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PVD_PVD1:
                    if (Reset == bM4_INTC_WUPEN_PVD1WUEN)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PVD_PVD2:
                    if (Reset == bM4_INTC_WUPEN_PVD2WUEN)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_SWDT_REFUDF:
                    if (Reset == bM4_INTC_WUPEN_SWDTWUEN)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ0:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN0)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ1:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN1)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ2:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN2)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ3:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN3)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ4:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN4)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ5:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN5)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ6:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN6)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ7:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN7)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ8:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN8)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ9:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN9)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ10:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN10)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ11:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN11)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ12:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN12)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ13:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN13)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ14:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN14)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                case INT_PORT_EIRQ15:
                    if (Reset == bM4_INTC_WUPEN_EIRQWUEN15)
                    {
                        NVIC_DisableIRQ((IRQn_Type)u8Cnt);
                    }
                    break;
                default:
                    break;
            }
        }
        /* Disable NVIC for all none-wakeup source */
        else if (INT_MAX != stcIntSel->INTSEL)
        {
            NVIC_DisableIRQ((IRQn_Type)u8Cnt);
        }
        else
        {
            ;
        }
    }
}

/**
 *******************************************************************************
 ** \brief NVIC recover after wakeup from stop mode
 **
 ** param  None
 **
 ** retval None
 **
 *****************************************************************************/
void PWC_enNvicRecover(void)
{
    uint8_t u8Cnt;

    for (u8Cnt = 0u; u8Cnt < sizeof(NVIC_ISER_BAK)/sizeof(uint32_t); u8Cnt++)
    {
        NVIC->ISER[u8Cnt] = NVIC_ISER_BAK[u8Cnt];
    }
}

/**
 *******************************************************************************
 ** \brief  Select system clock source.
 **
 ** \param  [in] u8SysSrc         The system clock source.
 **
 ** \retval None
 **
 ** \note   Must close all of the fcg register before switch system clock source.
 **         This function only be called in func. PWC_enClockBackup and
 **         PWC_enClockRecover.
 **         If need to switch system clock please call CLK_SetSysClkSource.
 **
 ******************************************************************************/
static void PWC_SetSysClk(uint8_t u8SysSrc)
{
    __IO uint32_t fcg0 = M4_MSTP->FCG0;
    __IO uint32_t fcg1 = M4_MSTP->FCG1;
    __IO uint32_t fcg2 = M4_MSTP->FCG2;
    __IO uint32_t fcg3 = M4_MSTP->FCG3;

    /* Only current system clock source or target system clock source is MPLL
    need to close fcg0~fcg3 and open fcg0~fcg3 during switch system clock source.
    We need to backup fcg0~fcg3 before close them. */
    if((5u == M4_SYSREG->CMU_CKSWR_f.CKSW) || (5u == u8SysSrc))
    {
        /* Close fcg0~fcg3. */
        M4_MSTP->FCG0 = 0xFFFFFAEEul;
        M4_MSTP->FCG1 = 0xFFFFFFFFul;
        M4_MSTP->FCG2 = 0xFFFFFFFFul;
        M4_MSTP->FCG3 = 0xFFFFFFFFul;

        Ddl_Delay1us(1ul);
    }

    /* Switch to target system clock source. */
    ENABLE_PWR_REG0_WRITE();

    M4_SYSREG->CMU_CKSWR_f.CKSW = u8SysSrc;

    DISABLE_PWR_REG0_WRITE();

    /* update system clock frequency. */
    SystemCoreClockUpdate();

    Ddl_Delay1us(1ul);

    /* Open fcg0~fcg3. */
    M4_MSTP->FCG0 = fcg0;
    M4_MSTP->FCG1 = fcg1;
    M4_MSTP->FCG2 = fcg2;
    M4_MSTP->FCG3 = fcg3;

    Ddl_Delay1us(1ul);
}
/**
 *******************************************************************************
 ** \brief  Backup HRC/MRC state and system clock , enable HRC/MRC ,set MRC as
 **         system clock before enter stop mode.
 **
 ** \param  None
 **
 ** \retval None
 **
 ******************************************************************************/
static void PWC_enClockBackup(void)
{
    __IO uint32_t timeout = 0ul;
    en_flag_status_t status = Reset;

    /* HRC state backup. */
    u8HrcState = (uint8_t)bM4_SYSREG_CMU_HRCCR_HRCSTP;
    /* System clock backup*/
    u8SysClkSrc = M4_SYSREG->CMU_CKSWR_f.CKSW;

    ENABLE_PWR_REG0_WRITE();

    /* Enable HRC  before enter stop mode. */
    if(0u != u8HrcState)
    {
        bM4_SYSREG_CMU_HRCCR_HRCSTP = 0u;
        do
        {
            status = (en_flag_status_t)M4_SYSREG->CMU_OSCSTBSR_f.HRCSTBF;
            timeout++;
        }while((timeout < 0x1000ul) && (status != Set));
    }
    else
    {
        /* code */
    }
    /* When system clock source is HRC and MPLL, set MRC as system clock. . */
    if((0u == u8SysClkSrc) || (5u == u8SysClkSrc))
    {
        /* MRC state backup. */
        u8MrcState = (uint8_t)bM4_SYSREG_CMU_MRCCR_MRCSTP;
        if(0u != u8MrcState)
        {
            bM4_SYSREG_CMU_MRCCR_MRCSTP = 0u;
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
        PWC_SetSysClk(1u);
    }
    else
    {
        /* code */
    }

    DISABLE_PWR_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Recover HRC/MRC state and system clock after wakeup stop mode.
 **
 ** \param  None
 **
 ** \retval None
 **
 ******************************************************************************/
static void PWC_enClockRecover(void)
{
    ENABLE_PWR_REG0_WRITE();

    if((0u == u8SysClkSrc) || (5u == u8SysClkSrc))
    {
        /* Recover MRC state & system clock source. */
        M4_SYSREG->CMU_MRCCR_f.MRCSTP = u8MrcState;
        PWC_SetSysClk(u8SysClkSrc);
    }
    /* Recover HRC state after wakeup stop mode. */
    M4_SYSREG->CMU_HRCCR_f.HRCSTP = u8HrcState;

    DISABLE_PWR_REG0_WRITE();
}

/**
 *******************************************************************************
 ** \brief  Clock backup before enter stop mode and mark it.
 **
 ** \param  None
 **
 ** \retval None
 **
 ** \note   This function should be called before func. PWC_EnterStopMd.
 ******************************************************************************/
void PWC_ClkBackup(void)
{
    /* Disable all interrupt to ensure the following operation continued. */
    __disable_irq();

    /* HRC/MRC backup and switch system clock as MRC before entry from stop mode. */
    PWC_enClockBackup();

    /* Mark the system clock has been switch as MRC, and will enter the stop mode. */
    u8StopFlag = 1u;

    /* Enable all interrupt. */
    __enable_irq();
}

/**
 *******************************************************************************
 ** \brief  Clock recover after wakeup stop mode.
 **
 ** \param  None
 **
 ** \retval None
 **
 ** \note   This function should be called after func. PWC_EnterStopMd.
 ******************************************************************************/
void PWC_ClkRecover(void)
{
    /* Disable all interrupt to ensure the following operation continued. */
    __disable_irq();

    /* Mark the system clock will be switch as MRC, and has waked_up from stop mode. */
    u8StopFlag = 0u;

    /* Recover HRC/MRC state and system clock after wakeup stop mode. */
    PWC_enClockRecover();

    /* Enable all interrupt. */
    __enable_irq();
}

/**
 *******************************************************************************
 ** \brief  Clock backup before exit wakup interrupt.
 **
 ** \param  None
 **
 ** \retval None
 **
 ** \note   This function should be called before exit wakup interrput.
 ******************************************************************************/
void PWC_IrqClkBackup(void)
{
    if((1ul == u8StopFlag) && (1ul == u8WkupIntCnt))
    {
         /* HRC/MRC backup and switch system clock as MRC. */
        PWC_enClockBackup();
    }
    u8WkupIntCnt--;
}

/**
 *******************************************************************************
 ** \brief  Clock recover after enter wakeup interrupt.
 **
 ** \param  None
 **
 ** \retval None
 **
** \note   This function should be called after enter wakup interrput.
 ******************************************************************************/
void PWC_IrqClkRecover(void)
{
    /* The varibale to display how many waked_up interrupt has been occured
       simultaneously and to decided whether backup clock before exit wake_up
       interrupt. */
    u8WkupIntCnt++;

    if(1ul == u8StopFlag)
    {
        /* Recover HRC/MRC state and system clock. */
        PWC_enClockRecover();
    }
}

/**
 *******************************************************************************
 ** \brief  Enter stop mode.
 **
 ** \param  None
 **
 ** \retval None
 **
 ******************************************************************************/
void PWC_EnterStopMd(void)
{
    /* NVIC backup and disable before entry from stop mode.*/
    PWC_enNvicBackup();
    /* Clock backup and switch system clock as MRC before entry from stop mode. */
    PWC_ClkBackup();

    ENABLE_PWR_REG0_WRITE();

    M4_SYSREG->PWR_STPMCR_f.STOP = 1u;
    M4_SYSREG->PWR_PWRC0_f.PWDN = 0u;

    DISABLE_PWR_REG0_WRITE();

    __WFI();

    /* Recover HRC/MRC state and system clock after wakeup from stop mode. */
    PWC_ClkRecover();
    /* NVIC recover after wakeup from stop mode. */
    PWC_enNvicRecover();
}

/**
 *******************************************************************************
 ** \brief  Switch MCU from low_speed (HCLK < 8MHz) to high-speed (HCLK > 8MHz) mode.
 **
 ** \param  None
 **
 ** \retval Ok:     Mode switch sucessfully.
 **
 ** \note   Called after clock is ready.
 ******************************************************************************/
en_result_t PWC_HS2LS(void)
{
    uint32_t u32To = 10000ul;

    if(0ul == M4_EFM->FAPRT)
    {
        M4_EFM->FAPRT = 0x0123ul;
        M4_EFM->FAPRT = 0x3210ul;
        M4_EFM->FRMC_f.LVM = 1u;
        M4_EFM->FAPRT = 0x0123ul;
        M4_EFM->FAPRT = 0x0123ul;
    }
    else
    {
        M4_EFM->FRMC_f.LVM = 1u;
    }

    ENABLE_PWR_REG_WRITE();
    M4_SYSREG->PWR_RAMOPM = 0x9062u;
    while((0x9062 != M4_SYSREG->PWR_RAMOPM) || (1u != M4_EFM->FRMC_f.LVM))
    {
        if (0ul == u32To--)
        {
            return Error;
        }
    }
    M4_SYSREG->PWR_PWRC2 = 0xE1U;
    M4_SYSREG->PWR_MDSWCR = 0x10U;
    DISABLE_PWR_REG_WRITE();

    Ddl_Delay1ms(1ul);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Switch MCU from high-speed (HCLK > 8MHz) to low_speed (HCLK < 8MHz) mode.
 **
 ** \param  None
 **
 ** \retval Ok:     Mode switch sucessfully.
 **         Error:  Mode switch failure.
 **
 ** \note   Called before clock is ready.
 ******************************************************************************/
en_result_t PWC_LS2HS(void)
{
    uint32_t u32To = 10000ul;

    ENABLE_PWR_REG_WRITE();
    M4_SYSREG->PWR_PWRC2 = 0xFFU;
    M4_SYSREG->PWR_MDSWCR = 0x10U;

    Ddl_Delay1ms(1ul);

    if(0ul == M4_EFM->FAPRT)
    {
        M4_EFM->FAPRT = 0x0123ul;
        M4_EFM->FAPRT = 0x3210ul;
        M4_EFM->FRMC_f.LVM = 0u;
        M4_EFM->FAPRT = 0x0123ul;
        M4_EFM->FAPRT = 0x0123ul;
    }
    else
    {
        M4_EFM->FRMC_f.LVM = 0u;
    }

    M4_SYSREG->PWR_RAMOPM = 0x8043u;
    while((0x8043 != M4_SYSREG->PWR_RAMOPM) || (0u != M4_EFM->FRMC_f.LVM))
    {
        if (0ul == u32To--)
        {
            return Error;
        }
    }

    DISABLE_PWR_REG_WRITE();

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Switch MCU from high-speed (HCLK > 8MHz) to high-performance mode.
 **
 ** \param  None
 **
 ** \retval Ok:     Mode switch sucessfully.
 **         Error:  Mode switch failure.
 **
 ** \note   Called before clock is ready.
 ******************************************************************************/
en_result_t PWC_HS2HP(void)
{
    ENABLE_PWR_REG_WRITE();
    M4_SYSREG->PWR_PWRC2 = 0xCFU;
    M4_SYSREG->PWR_MDSWCR = 0x10U;
    DISABLE_PWR_REG_WRITE();
    Ddl_Delay1ms(1ul);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Switch MCU from high-performance to high-speed (HCLK > 8MHz) mode.
 **
 ** \param  None
 **
 ** \retval Ok:     Mode switch sucessfully.
 **         Error:  Mode switch failure.
 **
 ** \note   Called after clock is ready.
 ******************************************************************************/
en_result_t PWC_HP2HS(void)
{
    ENABLE_PWR_REG_WRITE();
    M4_SYSREG->PWR_PWRC2 = 0xFFU;
    M4_SYSREG->PWR_MDSWCR = 0x10U;
    DISABLE_PWR_REG_WRITE();
    Ddl_Delay1ms(1ul);

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Switch MCU from low-speed (HCLK <= 8MHz) to high-performance mode.
 **
 ** \param  None
 **
 ** \retval Ok:     Mode switch sucessfully.
 **         Error:  Mode switch failure.
 **
 ** \note   Called before clock is ready.
 ******************************************************************************/
en_result_t PWC_LS2HP(void)
{
    uint32_t u32To = 10000ul;

    ENABLE_PWR_REG_WRITE();
    M4_SYSREG->PWR_PWRC2 = 0xCFU;
    M4_SYSREG->PWR_MDSWCR = 0x10U;

    Ddl_Delay1ms(1);

    if(0ul == M4_EFM->FAPRT)
    {
        M4_EFM->FAPRT = 0x0123ul;
        M4_EFM->FAPRT = 0x3210ul;
        M4_EFM->FRMC_f.LVM = 0u;
        M4_EFM->FAPRT = 0x0123ul;
        M4_EFM->FAPRT = 0x0123ul;
    }
    else
    {
        M4_EFM->FRMC_f.LVM = 0u;
    }

    M4_SYSREG->PWR_RAMOPM = 0x8043u;
    while((0x8043 != M4_SYSREG->PWR_RAMOPM) || (0u != M4_EFM->FRMC_f.LVM))
    {
        if (0ul == u32To--)
        {
            return Error;
        }
    }

    DISABLE_PWR_REG_WRITE();

    return Ok;
}

/**
 *******************************************************************************
 ** \brief  Switch MCU from high-performance to low-speed (HCLK <= 8MHz) mode.
 **
 ** \param  None
 **
 ** \retval Ok:     Mode switch sucessfully.
 **         Error:  Mode switch failure.
 **
 ** \note   Called after clock is ready.
 ******************************************************************************/
en_result_t PWC_HP2LS(void)
{
    uint32_t u32To = 10000ul;

    if(0ul == M4_EFM->FAPRT)
    {
        M4_EFM->FAPRT = 0x0123ul;
        M4_EFM->FAPRT = 0x3210ul;
        M4_EFM->FRMC_f.LVM = 1u;
        M4_EFM->FAPRT = 0x0123ul;
        M4_EFM->FAPRT = 0x0123ul;
    }
    else
    {
        M4_EFM->FRMC_f.LVM = 1u;
    }

    ENABLE_PWR_REG_WRITE();
    M4_SYSREG->PWR_RAMOPM = 0x9062u;
    u32To = 10000ul;
    while((0x9062 != M4_SYSREG->PWR_RAMOPM) || (1u != M4_EFM->FRMC_f.LVM))
    {
        if (0ul == u32To--)
        {
            return Error;
        }
    }

    M4_SYSREG->PWR_PWRC2 = 0xD1U;
    M4_SYSREG->PWR_MDSWCR = 0x10U;

    DISABLE_PWR_REG_WRITE();

    Ddl_Delay1ms(1);

    return Ok;
}

#endif /* DDL_PWC_ENABLE */

//@} // PwcGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
