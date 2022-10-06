/**
 * \file     clock.h
 *
 * \brief    This file contains the function prototypes for PRCM API's.
 *
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

 
#ifndef      __PRCM_H__
#define      __PRCM_H__

#include "hw_control_AM335x.h"
#include "hw_types.h"
#include "hw_cm_per.h"
#include "hw_cm_wkup.h"
#include "hw_cm_rtc.h"
#include "hw_cm_mpu.h"
#include "hw_cm_dpll.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { 
    FAIL     = 0,
    SUCCESS = 1
}result;


/********************** MACROS ***************************/

/* Configs */
/*    Maximun number of OPP's supported by the device    */
#define     CLK_MAX_OPP_SUPPORTED                (0x4)
#define     CLK_OPP_SR_TURBO                     (0x0)
#define     CLK_OPP_120                          (0x1)
#define     CLK_OPP_100                          (0x2)
#define     CLK_OPP_50                           (0x3)

/*    Maximum number of clocks under a clock domain    */
#define     CLK_CLOCKDOMAIN_MAX_CLOCKS           (0x50)

/*    active logic is '1'     */
#define     CLK_ACTIVE_HIGH_LOGIC                (0x0)

/*    active logic is '0'        */
#define     CLK_ACTIVE_LOW_LOGIC                 (0x1)

/*    Different clock speeds    */
#define     CLK_EXT_CRYSTAL_SPEED                (24*1000*1000)
#define     CLK_CLOCK_SPEED_32768_HZ             (32768)
#define     CLK_CLOCK_SPEED_192_MHZ              (192*1000*1000)
#define     CLK_CLOCK_SPEED_960_MHZ              (960*1000*1000)
#define     CLK_CLOCK_SPEED_600_MHZ              (600*1000*1000)
#define     CLK_CLOCK_SPEED_550_MHZ              (550*1000*1000)
#define     CLK_CLOCK_SPEED_250_MHZ              (250*1000*1000)
#define     CLK_CLOCK_SPEED_200_MHZ              (200*1000*1000)
#define     CLK_CLOCK_SPEED_100_MHZ              (100*1000*1000)

/*    Maximum inputs for the Mux    */
#define     CLK_MUX_MAX_INPUT_CLOCKS             (0x6)

/*    Maximum number of interface clocks required for a module    */
#define     CLK_MAX_INTERFACE_CLOCK              (0x3)

/*    Maximum number of functional clocks required for a module    */
#define     CLK_MAX_FUNCTIONAL_CLOCK             (0x5)

/*    Maximum number of optional clocks required for a module    */
#define     CLK_MAX_OPT_CLOCK                    (0x2)

/*    Maximum number of interface clock enable required for a module    */
#define     CLK_MAX_INTERFACE_LOCK_ENABLE        (0x2)

/*    Minimum sigma delta divider for a PLL    */
#define     CLK_MIN_ADPLL_SIGMA_DELTA_DIVIDER    (0x2)

/*    List of Modules    */
#define     CLK_MPU_CLK                          (0x0)
#define     CLK_EMIF                             (0x1)
#define     CLK_TIMER2                           (0x2)
#define     CLK_I2C1                             (0x3)
#define     CLK_GPIO3                            (0x4)
#define     CLK_SPI0                             (0x5)
#define     CLK_UART0                            (0x6)
#define     CLK_MAILBOX0                         (0x7)
#define     CLK_RTC                              (0x8)
#define     CLK_L4LS                             (0x9)
#define     CLK_WDT1                             (0xA)
#define     CLK_ADC_TSC                          (0xB)
#define     CLK_LCDC                             (0xC)
#define     CLK_WKUP_M3                          (0xD)
#define     CLK_L4WKUP                           (0xE)
#define     CLK_MCASP1                           (0xF)
#define     CLK_OCMCRAM                          (0x10)
#define     CLK_L3                               (0x11)
#define     CLK_GPMC                             (0x12)
#define     CLK_USB0                             (0x13)
#define     CLK_L4FW                             (0x14)
#define     CLK_CPGMAC0                          (0x15)
#define     CLK_I2C0                             (0x16)
#define     CLK_GPIO0                            (0x17)
#define     CLK_GPIO1                            (0x18)
#define     CLK_TIMER1                           (0x19)
#define     CLK_TIMER3                           (0x1A)
#define     CLK_TIMER4                           (0x1B)
#define     CLK_TIMER7                           (0x1C)
#define     CLK_EPWMSS0                          (0x1D)
#define     CLK_TPCC                             (0x1E)
#define     CLK_TPTC0                            (0x1F)
#define     CLK_TPTC1                            (0x20)
#define     CLK_TPTC2                            (0x21)
#define     CLK_TIMER6                           (0x22)

/*    List of Clock Domains    */
#define     CLK_L4LS_CLK_DOMAIN                  (0x0)
#define     CLK_RTC_CLK_DOMAIN                   (0x1)
#define     CLK_WKUP_CLK_DOMAIN                  (0x2)
#define     CLK_PER_L3_CLK_DOMAIN                (0x3)
#define     CLK_L4WKUP_AON_CLK_DOMAIN            (0x4)
#define     CLK_MPU_CLK_DOMAIN                   (0x5)
#define     CLK_LCDC_CLK_DOMAIN                  (0x6)
#define     CLK_L4_FW_CLK_DOMAIN                 (0x7)
#define     CLK_L3S_CLK_DOMAIN                   (0x8)
#define     CLK_CPSW_125MHZ_CLK_DOMAIN           (0x9)
#define     CLK_L4HS_CLK_DOMAIN                  (0xA)
#define     CLK_24MHZ_CLK_DOMAIN                 (0xB)

/*    Clock domain sleep transition    */
#define     CM_CLKSTCTRL_CLKTRCTRL_SW_SLEEP      (0x1u)
#define     CM_CLKSTCTRL_CLKTRCTRL_SW_WKUP       (0x2u)
#define     CM_CLKSTCTRL_CLKTRCTRL_SHIFT         (0x00000000u)

/*    PLL low power mode config    */
#define     CM_DPLL_LPMODE_EN_ENABLED            (0x1u)
#define     CM_DPLL_LPMODE_EN_SHIFT              (0x0000000Au)

/*    Module     */
#define     MODULE_INVALID                       (0xFFFFFFFFu)
#define     MODULE_NOT_IDLE                      (0xFFFFFFFEu)
#define     MODULE_NOT_DISABLED                  (0xFFFFFFFDu)
#define     MODULE_FUNCTIONAL                    (0x0u)
#define     MODULE_IN_TRANS                      (0x1u)
#define     MODULE_IDLE                          (0x2u)
#define     MODULE_DISABLED                      (0x3u)

#define     MODULE_AND_CLOCK_DISABLED            (0x0u)
#define     MODULE_AND_CLOCK_NOT_DISABLED        (0x1u)

/*    Clock    */
#define     CLK_INVALID_GCLK                     (0xFFFFFFFFu)
#define     CLK_INVALID_DIVIDER                  (0xFFFFFFFFu)
#define     CLK_CLOCK_GATED                      (0x0u)
#define     CLK_CLOCK_UNGATED                    (0x1u)

/*    ADPLL    */
#define     ADPLL_UNLOCKED                       (0x0u)
#define     ADPLL_LOCKED                         (0x1u)
#define     ADPLL_INVALID                        (0xFFFFFFFFu)

#define     CLK_NAME_MAX_SIZE                    (30)

#define     CLK_DOMAIN_CLOCK_GATED               (0x0)
                                                
#define     CLK_LP_MODE_NORMAL                   (0x0)
#define     CLK_LP_MODE_BYPASS                   (0x1)


/********************** Structure definitions   ***************************/

typedef struct clkDivider ClockDivider;
typedef struct clkDomain ClockDomain;
typedef struct genericClock Clock;

/**
 * \brief Clock divider definition
 *
 * Clock divider for different OPP's
 */
struct clkDivider{

        /**
         * \brief Divider config register
         * This reigster configures the divider, auto clock gating ctrl and status
         */
        unsigned int *dividerConfigReg;

        /**
         * \brief Clock divider mask
         */
        unsigned int clkDividerMask;

        /**
         * \brief Divider array ptr
         * Pointer to clock divider array for different OPP
         */
        unsigned int clkDividerValue[CLK_MAX_OPP_SUPPORTED];

        /**
         * \brief divider updated status mask
         */
        unsigned int clkDivUpdatedStatusMask;

        /**
         * \brief divider updated status shift
         */
        unsigned int clkDivUpdatedStatusShift;

        /**
         * \brief CLKOUT auto gating Control mask
         */
        unsigned int clkoutAutoGateCtrlMask;

        /**
         * \brief CLKOUT auto gating Control
         */
        unsigned int clkoutAutoGateCtrl;

        /**
         * \brief CLKOUT gate status mask
         */
        unsigned int clkoutGateStatusMask;

        /**
         * \brief CLKOUT gate status shift
         */
        unsigned int clkoutGateStatusShift;

        /**
         * \brief divider auto power down validity
         */
        unsigned int isPdCtrlValid;

        /**
         * \brief divider auto Power down Control mask
         */
        unsigned int clkAutoPDCtrlMask;

        /**
         * \brief divider auto Power down Control
         */
        unsigned int clkAutoPDCtrl;

};


/**
 * \brief PLL structure definition. This will be included as a member of clock
 *        structure. If a node in clock tree is PLL then that clock will have valid PLL.
 *        This is used to configure the PLL to generate required frequency.
 */
typedef struct {

        /**
         * \brief indicated whether the PLL is configured already
        */
        tBoolean isPLLConfigured;

        /**
         * \brief Auto idle register
         * Register to be written to configure the automatic control of the 
         * DPLL activity
         */
        unsigned int *autoIdleCtrlReg;

        /**
         * \brief Auto idle config value
         * Value to be written to configure the automatic control of the 
         * DPLL activity
         */
        unsigned int autoIdleCtrlVal;

        /**
         * \brief Idle status register
         * This reigster indicates the master clock idle status
         */
        unsigned int *idleStatusReg;

        /**
         * \brief DPLL Clock activity status mask
         */
        unsigned int adpllClkStatusMask;

        /**
         * \brief DPLL Clock activity status mask shift
         */
        unsigned int adpllClkStatusShift;

        /**
         * \brief DPLL Clock MN bypass status mask
         */
        unsigned int adpllClkMNBypassStatusMask;

        /**
         * \brief DPLL Clock MN bypass status mask shift
         */
        unsigned int adpllClkMNBypassStatusShift;

        /**
         * \brief DPLL config register
         * This reigster configures the multiplier, divider and bypass clock source
         */
        unsigned int *adpllConfigReg;

        /**
         * \brief DPLL Bypass clock source mask
         */
        unsigned int adpllBypassClkMask;

        /**
         * \brief DPLL Bypass clock source
         */
        unsigned int adpllBypassClkSource;

        /**
         * \brief Sigma delta divider mask
         */
        unsigned int adpllSigmaDeltaDividerMask;

        /**
         * \brief Sigma delta divider
         * Sigma-Delta divider select (2 -255). This factor must be set by s/w
         * to ensure optimum jitter performance.
         */
        unsigned int adpllSigmaDeltaDivider[CLK_MAX_OPP_SUPPORTED];

        /**
         * \brief DPLL Multiplier mask
         */
        unsigned int adpllMultiplierMask;

        /**
         * \brief DPLL Multiplier
         */
        unsigned int adpllMultiplier[CLK_MAX_OPP_SUPPORTED];

        /**
         * \brief DPLL divider mask
         */
        unsigned int adpllDividerMask;

        /**
         * \brief DPLL divider
         */
        unsigned int adpllDivider[CLK_MAX_OPP_SUPPORTED];

        /**
         * \brief DPLL mode register
         * This reigster configures low power mode setting and relock ramp setting
         */
        unsigned int *adpllModeReg;

        /**
         * \brief DPLL low power mode control Mask
         */
        unsigned int adpllLowPowerMask;

        /**
         * \brief DPLL low power mode control setting
         */
        unsigned int adpllLowPowerNormalVal;

        /**
         * \brief DPLL low power mode bypass control setting
         */
        unsigned int adpllLowPowerBypassVal;

        /**
         * \brief DPLL relock ramp control Mask
         */
        unsigned int adpllRelockRampMask;

        /**
         * \brief DPLL relock ramp control setting
         */
        unsigned int adpllRelockRampVal;

}ADPLL;


/**
 * \brief clock definition
 *
 * These are set of parameters defining clock of a module
 */
struct genericClock{

        /**
         * \brief Clock Name
         */
        signed char clkName[CLK_NAME_MAX_SIZE];

        /**
         * \brief is leaf clock
         * Is this clock the last node in the clock tree
         */
        unsigned int isLeafClock;

        /**
         * \brief Parent clock
         * Parent node of this node in the clock tree
         */
        Clock *parentClock;

        /**
         * \brief Clock domain
         * clock domain to which the clock belongs
         */
        ClockDomain *clkDomainPtr;

        /**
         * \brief clock speed
         * clock speed in Hz. Always specifies the input clock
         */
        unsigned int clockSpeedHz;

        /**
         * \brief PLL pointer
         * Pointer to PLL instance if the clock is a PLL
         */
        ADPLL *adpllPtr;

        /**
         * \brief OPP's supported
         * Number of OPP's supported
         */
        unsigned int OPPSupported;

        /**
         * \brief Divider
         * Pointer to clock divider 
         */
        ClockDivider *clkDivider;

        /**
         * \brief Mux input select register
         */
        unsigned int *muxInputSelReg;

        /**
         * \brief Mux input select mask
         */
        unsigned int muxInputSelMask;

        /**
         * \brief Mux input selector
         */
        unsigned int muxInputSelVal;

        /**
         * \brief active child count
         * Indiactes the number of dependent active nodes
         */
        unsigned int activeChildCount;

        /*    to be extracted from Clock domain ctrl reg (gclk (F/I) belongs to a clock domain)    */

        /**
         * \brief Module clock gate status register
         * Register to read to get the clock gate  status
         */
        unsigned int *clkGateStatusReg;

        /**
         * \brief Module clock (gate) status mask
         * Mask to be applied to extract the status bit of the clock gate
         */
        unsigned int clockGateStatusMask;

        /**
         * \brief Module clock (gate) status shift
         * No of bits to be shifted to get the status of the clock gate
         */
        unsigned int clockGateStatusShift;

};


/**
 * \brief Clock dmoain
 *
 * Clock domain combines multiple clocks and controls the sleep transition
 */
struct clkDomain{

        /**
         * \brief indicated whether the clock domain is initialized already
        */
        tBoolean isCDInitialized;

        /**
         * \brief Number of active clocks under the clock domain
         */
        unsigned int activeClockCount;

        /**
         * \brief Clock state transition control
         * Register to be written to configure mode of clock transition
         */
        unsigned int *clkStateTransCtrlReg;

        /**
         * \brief Clock state transition value
         * Value to be written to configure mode of clock transition
         */
        unsigned int clkStateTransValue;

        /**
         * \brief Clock gate status mask
         * Mask for getting the gate status of all the clocks in the clock domain
         */
        unsigned int clkGateStatusMask;

        /**
         * \brief List of clocks in the clock domain
         */
        Clock *clkList[CLK_CLOCKDOMAIN_MAX_CLOCKS];

};


/**
 * \brief Mux selection struct, to be used by clock during definition
 */
typedef struct {
        /**
         * \brief Parent clock
         * Parent node of this node in the clock tree
         */
        Clock *parentClock[CLK_MUX_MAX_INPUT_CLOCKS];
}MuxParentClockSel;


/**
 * \brief Module clock
 * This struct defines the interface clock and functional clock.
 */
typedef struct {

        /*    module specific    */

        /**
         * \brief clock control register
         * Register to be written to control the clock
         */
        unsigned int *clockCtrlReg;

        /**
         * \brief Enable Value
         * Value to be written to enable the clock
         */
        unsigned int enableValue;

        /**
         * \brief Disable Value
         * Value to be written to disable the clock
         */
        unsigned int disableValue;

        /**
         * \brief Module status register
         * Register to read to get the clock status
         */
        unsigned int *moduleStatusReg;

        /**
         * \brief Module idle status mask
         * Mask to be applied to extract the status bit of the clock
         */
        unsigned int idleStatusMask;

        /**
         * \brief Module idle status shift
         * No of bits to be shifted to get the status of the clock
         */
        unsigned int idleStatusShift;

        /**
         * \brief Module standby status mask
         * Mask to be applied to extract the standby status bit of the clock
         */
        unsigned int stbyStatusMask;

        /**
         * \brief Module standby status shift
         * No of bits to be shifted to get the standby status of the clock
         */
        unsigned int stbyStatusShift;

        /*    Optional functional clock - not considered here    */

        /**
         * \brief Interface clock
         */
        Clock    *iClk[CLK_MAX_INTERFACE_CLOCK];

        /**
         * \brief Functional clock
         */
        Clock    *fClk[CLK_MAX_FUNCTIONAL_CLOCK];

        /**
         * \brief Optional Clock
         */
        Clock    *optClk[CLK_MAX_OPT_CLOCK];

        /**
         * \brief clock enable
         */
        Clock    *clkEnable[CLK_MAX_INTERFACE_LOCK_ENABLE];

}ModuleClock;

/**
 * \brief Associates a flag with modules to include or exclude for PM Mode
 */
typedef struct mapModule
{
    unsigned int module;
    unsigned int select;
} tMapModule;

/*****************************************************************************
**                   FUNCTION DECLARATIONS                                   
*****************************************************************************/

/*    Clock management API's    */

void deviceClockEnable(unsigned int enableList[], unsigned noOfElements);

// disable all modules & their clocks
result deviceClockDisable(unsigned int moduleDisableList[], unsigned noOfElements);

void enableModule(unsigned int moduleId);

void disableModule(unsigned int moduleId);

void enableModuleClock(unsigned int moduleId);

unsigned int disableModuleClock(unsigned int moduleId, tBoolean isBlockingCall);

unsigned int getModuleState(unsigned int moduleId);

int getGclockGateState(Clock *clkPtr);

void initClockDomain(ClockDomain *clkDomainptr);

result disableClockDomain(ClockDomain *clkDomainptr);


/*    PLL config API's    */
void configADPLL(ADPLL *adpllPtr, unsigned int OPPSupported);

unsigned int getADPLLIdleStatus(ADPLL *adpllPtr);

unsigned int getDividerClkGateStatus(Clock *clkPtr);

result clkdomainGateStatus(unsigned int clkDomainId);

result deviceClockGateStatus(unsigned int clockDomainStatusList[], unsigned noOfElements);

void setLPBypassMode(ADPLL *adpllPtr, unsigned int isNormalByp);

void enableADPLLLowPowerMode(ADPLL *adpllPtr);

void enableSelModuleClock(tMapModule enableList[], unsigned noOfElements);

result disableSelModuleClock(tMapModule moduleDisableList[],
                             unsigned int noOfElements);

#ifdef __cplusplus
}
#endif

#endif
