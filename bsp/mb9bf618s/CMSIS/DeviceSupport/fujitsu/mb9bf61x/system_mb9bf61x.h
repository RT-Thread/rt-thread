/************************************************************************/
/*               (C) Fujitsu Semiconductor Europe GmbH (FSEU)           */
/*                                                                      */
/* The following software deliverable is intended for and must only be  */
/* used for reference and in an evaluation laboratory environment.      */
/* It is provided on an as-is basis without charge and is subject to    */
/* alterations.                                                         */
/* It is the user's obligation to fully test the software in its        */
/* environment and to ensure proper functionality, qualification and    */
/* compliance with component specifications.                            */
/*                                                                      */
/* In the event the software deliverable includes the use of open       */
/* source components, the provisions of the governing open source       */
/* license agreement shall apply with respect to such software          */
/* deliverable.                                                         */
/* FSEU does not warrant that the deliverables do not infringe any      */
/* third party intellectual property right (IPR). In the event that     */
/* the deliverables infringe a third party IPR it is the sole           */
/* responsibility of the customer to obtain necessary licenses to       */
/* continue the usage of the deliverable.                               */
/*                                                                      */
/* To the maximum extent permitted by applicable law FSEU disclaims all */
/* warranties, whether express or implied, in particular, but not       */
/* limited to, warranties of merchantability and fitness for a          */
/* particular purpose for which the deliverable is not designated.      */
/*                                                                      */
/* To the maximum extent permitted by applicable law, FSEU's liability  */
/* is restricted to intentional misconduct and gross negligence.        */
/* FSEU is not liable for consequential damages.                        */
/*                                                                      */
/* (V1.5)                                                               */
/************************************************************************/
/** \file system_mb9bf61x.h
 **
 ** Headerfile for FM3 system parameters
 **
 ** User clock definitions can be done for the following clock settings:
 ** - CLOCK_SETUP : Execute the clock settings form the settings below in
 **                 SystemInit()
 ** - __CLKMO : External clock frequency for main oscillion
 ** - __CLKSO : External clock frequency for sub oscillion
 ** - SCM_CTL : System Clock Mode Control Register
 ** - BSC_PSR : Base Clock Prescaler Register
 ** - APBC0_PSR : APB0 Prescaler Register
 ** - APBC1_PSR : APB1 Prescaler Register
 ** - APBC2_PSR : APB2 Prescaler Register
 ** - SWC_PSR : Software Watchdog Clock Prescaler Register
 ** - TTC_PSR : Trace Clock Prescaler Register
 ** - CSW_TMR : Clock Stabilization Wait Time Register
 ** - PSW_TMR : PLL Clock Stabilization Wait Time Setup Register
 ** - PLL_CTL1 : PLL Control Register 1
 ** - PLL_CTL2 : PLL Control Register 2
 **
 ** The register settings are check for correct values of reserved bits.
 ** Otherwise a preprocessor error is output and stops the build process.
 ** Furthermore the 'master clock' is retrieved from the register settings
 ** and the system clock (HCLK) is calculated from the Base Clock Prescaler
 ** Register (BSC_PSR). This value is used for the global CMSIS variable
 ** #SystemCoreClock. Also the absolute external, PLL and HCL freqeuncy is
 ** is checked. Note that not all possible wrong setting are checked! The
 ** user has to take care to fulfill the settings stated in the according
 ** device's data sheet!
 **
 ** User definition for Hardware Watchdog:
 ** - HWWD_DISABLE : Disables Hardware Watchdog in SystemInit()
 **
 ** User definition for CR Trimming:
 ** - CR_TRIM_SETUP : Enables CR trimming in SystemInit()
 **
 ** History:
 ** 2011-05-16 V1.0 MWi original version
 *****************************************************************************/

#ifndef _SYSTEM_MB9BF61X_H_
#define _SYSTEM_MB9BF61X_H_

#ifdef __cplusplus
extern "C" {
#endif 

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
   
#include <stdint.h>

/******************************************************************************/
/* Global pre-processor symbols/macros ('define')                             */
/******************************************************************************/
   
/******************************************************************************/
/*                                                                            */
/*                      START OF USER SETTINGS HERE                           */
/*                      ===========================                           */   
/*                                                                            */
/*                 All lines with '<<<' can be set by user.                   */
/*                                                                            */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief Clock Setup Enable
 **        <i>(USER SETTING)</i>
 **
 ** - 0 = No clock setup done by system_mb9xfxxx.c
 ** - 1 = Clock setup done by system_mb9xfxxx.c
 ******************************************************************************/ 
#define CLOCK_SETUP               1   // <<< Define clock setup here

/**
 ******************************************************************************
 ** \brief External Main Clock Frequency (in Hz, [value]UL)
 **        <i>(USER SETTING)</i>
 ******************************************************************************/    
#define __CLKMO        ( 4000000UL)   // <<< External   4MHz Crystal

/**
 ******************************************************************************
 ** \brief External Sub Clock Frequency (in Hz, [value]UL)
 **        <i>(USER SETTING)</i>
 ******************************************************************************/  
#define __CLKSO        (   32768UL)   // <<<  External  32KHz Crystal

/**
 ******************************************************************************
 ** \brief System Clock Mode Control Register value definition
 **        <i>(USER SETTING)</i>
 ** 
 ** SCM_CTL
 **
 ** Bit#7-5 : RCS[2:0]
 ** - 0 = Internal high-speed CR oscillation (default)
 ** - 1 = Main oscillation clock
 ** - 2 = PLL oscillation clock
 ** - 3 = (not allowed)
 ** - 4 = Internal low-speed CR oscillation
 ** - 5 = Sub clock oscillation
 ** - 6 = (not allowed)
 ** - 7 = (not allowed)
 **
 ** Bit#4 : PLLE
 ** - 0 = Disable PLL (default)
 ** - 1 = Enable PLL
 **
 ** Bit#3 : SOSCE
 ** - 0 = Disable sub oscillation (default)
 ** - 1 = Enable sub oscillation
 **
 ** Bit#2 : (reserved)
 **
 ** Bit#1 : MOSCE
 ** - 0 = Disable main oscillation (default)
 ** - 1 = Enable main oscillation  
 **
 ** Bit#0 : (reserved)  
 ******************************************************************************/ 
#define SCM_CTL_Val           0x00000052    // <<< Define SCM_CTL here

/**
 ******************************************************************************
 ** \brief Base Clock Prescaler Register value definition
 **        <i>(USER SETTING)</i>
 **
 ** BSC_PSR
 **
 ** Bit#7-3 : (reserved)
 **
 ** Bit#2-0 : BSR[2:0]
 ** - 0 = HCLK = Master Clock
 ** - 1 = HCLK = Master Clock / 2
 ** - 2 = HCLK = Master Clock / 3
 ** - 3 = HCLK = Master Clock / 4
 ** - 4 = HCLK = Master Clock / 6
 ** - 5 = HCLK = Master Clock / 8
 ** - 6 = HCLK = Master Clock / 16
 ** - 7 = (reserved)
 ******************************************************************************/    
#define BSC_PSR_Val           0x00000000    // <<< Define BSC_PSR here
 
/**
 ******************************************************************************
 ** \brief APB0 Prescaler Register value definition
 **        <i>(USER SETTING)</i>
 ** 
 ** APBC0_PSR
 **
 ** Bit#7-2 : (reserved)
 **
 ** Bit#1-0 : BSR[2:0] 
 ** - 0 = PCLK0 = HCLK
 ** - 1 = PCLK0 = HCLK / 2
 ** - 2 = PCLK0 = HCLK / 4
 ** - 3 = PCLK0 = HCLK / 8
 ******************************************************************************/    
#define APBC0_PSR_Val         0x00000001     // <<< Define APBC0_PSR here
   
/**
 ******************************************************************************
 ** \brief APB1 Prescaler Register value definition
 **        <i>(USER SETTING)</i>
 ** 
 ** APBC1_PSR
 **
 ** Bit#7 : APBC1EN
 ** - 0 = Disable PCLK1 output
 ** - 1 = Enables PCLK1 (default)
 **
 ** Bit#6-5 : (reserved)
 **
 ** Bit#4 : APBC1RST
 ** - 0 = APB1 bus reset, inactive (default)
 ** - 1 = APB1 bus reset, active  
 **
 ** Bit#3-2 : (reserved)
 **
 ** Bit#1-0 : APBC1[2:0]
 ** - 0 = PCLK1 = HCLK
 ** - 1 = PCLK1 = HCLK / 2
 ** - 2 = PCLK1 = HCLK / 4
 ** - 3 = PCLK1 = HCLK / 8
 ******************************************************************************/     
#define APBC1_PSR_Val         0x00000081    // <<< Define APBC1_PSR here
   
/**
 ******************************************************************************
 ** \brief APB2 Prescaler Register value definition
 **        <i>(USER SETTING)</i>
 ** 
 ** APBC2_PSR
 **
 ** Bit#7 : APBC2EN
 ** - 0 = Disable PCLK2 output
 ** - 1 = Enables PCLK2 (default)
 **
 ** Bit#6-5 : (reserved)
 ** 
 ** Bit#4 : APBC2RST
 ** - 0 = APB2 bus reset, inactive (default)
 ** - 1 = APB2 bus reset, active  
 **
 ** Bit#3-2 : (reserved)
 **
 ** Bit#1-0 : APBC2[1:0]
 ** - 0 = PCLK2 = HCLK
 ** - 1 = PCLK2 = HCLK / 2
 ** - 2 = PCLK2 = HCLK / 4
 ** - 3 = PCLK2 = HCLK / 8
 ******************************************************************************/    
#define APBC2_PSR_Val         0x00000081    // <<< Define APBC2_PSR here

/**
 ******************************************************************************
 ** \brief Software Watchdog Clock Prescaler Register value definition
 **        <i>(USER SETTING)</i>
 ** 
 ** SWC_PSR
 **
 ** Bit#7 : TESTB
 ** - 0 = (not allowed)
 ** - 1 = (always write "1" to this bit)
 **
 ** Bit#6-2 : (reserved)
 **
 ** Bit#1-0 : SWDS[2:0]
 ** - 0 = SWDGOGCLK = PCLK0
 ** - 1 = SWDGOGCLK = PCLK0 / 2
 ** - 2 = SWDGOGCLK = PCLK0 / 4
 ** - 3 = SWDGOGCLK = PCLK0 / 8
 ******************************************************************************/  
#define SWC_PSR_Val           0x00000003    // <<< Define SWC_PSR here

/**
 ******************************************************************************
 ** \brief Trace Clock Prescaler Register value definition
 **        <i>(USER SETTING)</i>
 ** 
 ** TTC_PSR
 **
 ** Bit#7-1 : (reserved)
 **
 ** Bit#0 : TTC
 ** - 0 = TPIUCLK = HCLK
 ** - 1 = TPIUCLK = HCLK / 2
 ******************************************************************************/  
#define TTC_PSR_Val           0x00000000    // <<< Define TTC_PSR here
 
/**
 ******************************************************************************
 ** \brief Clock Stabilization Wait Time Register value definition
 **        <i>(USER SETTING)</i>
 ** 
 ** CSW_TMR
 **
 ** Bit#7 : (reserved)
 **
 ** Bit#6-4 : SOWT[2:0]
 ** - 0 = ~10.3 ms (default)
 ** - 1 = ~20.5 ms
 ** - 2 = ~41 ms
 ** - 3 = ~82 ms
 ** - 4 = ~164 ms
 ** - 5 = ~327 ms
 ** - 6 = ~655 ms
 ** - 7 = ~1.31 s 
 **
 ** Bit#3-0 : MOWT[3:0]
 ** - 0 = ~500 ns (default)
 ** - 1 = ~8 us
 ** - 2 = ~16 us
 ** - 3 = ~32 us
 ** - 4 = ~64 us
 ** - 5 = ~128 us
 ** - 6 = ~256 us
 ** - 7 = ~512 us
 ** - 8 = ~1.0 ms
 ** - 9 = ~2.0 ms
 ** - 10 = ~4.0 ms
 ** - 11 = ~8.0 ms
 ** - 12 = ~33.0 ms
 ** - 13 = ~131 ms
 ** - 14 = ~524 ms
 ** - 15 = ~2.0 s
 ******************************************************************************/     
#define CSW_TMR_Val           0x0000005C    // <<< Define CSW_TMR here

/**
 ******************************************************************************
 ** \brief PLL Clock Stabilization Wait Time Setup Register value definition
 **        <i>(USER SETTING)</i>
 ** 
 ** PSW_TMR
 **
 ** Bit#7-5 : (reserved)
 **
 ** Bit#4 : PINC
 ** - 0 = Selects CLKMO (main oscillation) (default)
 ** - 1 = (setting diabled)
 **
 ** Bit#3 : (reserved)
 **
 ** Bit#2-0 : POWT[2:0]
 ** - 0 = ~128 us (default) 
 ** - 1 = ~256 us
 ** - 2 = ~512 us
 ** - 3 = ~1.02 ms
 ** - 4 = ~2.05 ms
 ** - 5 = ~4.10 ms
 ** - 6 = ~8.20 ms
 ** - 7 = ~16.40 ms
 ******************************************************************************/    
#define PSW_TMR_Val           0x00000000    // <<< Define PSW_TMR here

/**
 ******************************************************************************
 ** \brief PLL Control Register 1 value definition
 **        <i>(USER SETTING)</i>
 ** 
 ** PLL_CTL1
 **
 ** Bit#7-4 : PLLK[3:0]
 ** - 0 = Division(PLLK) = 1/1 (default)
 ** - 1 = Division(PLLK) = 1/2
 ** - 2 = Division(PLLK) = 1/3
 ** - . . .
 ** - 15 = Division(PLLK) = 1/16
 **
 ** Bit#3-0 : PLLM[3:0]
 ** - 0 = Division(PLLM) = 1/1 (default)
 ** - 1 = Division(PLLM) = 1/2
 ** - 2 = Division(PLLM) = 1/3
 ** - . . .
 ** - 15 = Division(PLLM) = 1/16
 ******************************************************************************/    
#define PLL_CTL1_Val          0x00000001    // <<< Define PLL_CTL1 here

/**
 ******************************************************************************
 ** \brief PLL Control Register 2 value definition
 **        <i>(USER SETTING)</i>
 ** 
 ** PLL_CTL2
 **
 ** Bit#7-6 : (reserved)
 **
 ** Bit#5-0 : PLLN[5:0]
 ** - 0 = Division(PLLN) = 1/1 (default)
 ** - 1 = Division(PLLN) = 1/2
 ** - 2 = Division(PLLN) = 1/3
 ** - . . .
 ** - 63 = Division(PLLN) = 1/64
 ******************************************************************************/    
#define PLL_CTL2_Val          0x00000023    // <<< Define PLL_CTL2 here
   
/**
 ******************************************************************************
 ** \brief Hardware Watchdog disable definition
 **        <i>(USER SETTING)</i>
 **
 ** - 0 = Hardware Watchdog enable
 ** - 1 = Hardware Watchdog disable
 ******************************************************************************/  
#define HWWD_DISABLE          1   // <<< Define HW Watach dog enable here

/**
 ******************************************************************************
 ** \brief Trimming CR
 **        <i>(USER SETTING)</i>
 **
 ** - 0 = CR is not trimmed at startup
 ** - 1 = CR is trimmed at startup
 ******************************************************************************/  
#define CR_TRIM_SETUP         1   // <<< Define CR trimming at startup enable here

   
/******************************************************************************/
/*                                                                            */
/*                         END OF USER SETTINGS HERE                          */
/*                         =========================                          */ 
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Device dependent System Clock absolute maximum ranges                      */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief Internal High-Speed CR Oscillator Frequency (in Hz, [value]UL)
 **        <i>(USER SETTING)</i>
 ******************************************************************************/    
#define __CLKHC        ( 4000000UL)         /* Internal   4MHz CR Oscillator  */
   
/**
 ******************************************************************************
 ** \brief Internal Low-Speed CR Oscillator Frequency (in Hz, [value]UL)
 **        <i>(USER SETTING)</i>
 ******************************************************************************/ 
#define __CLKLC        (  100000UL)         /* Internal 100KHz CR Oscillator  */  

/**
 ******************************************************************************
 ** \brief Any case minimum Main Clock frequency (in Hz, [value]UL)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __CLKMOMIN    (  4000000UL)
   
/**
 ******************************************************************************
 ** \brief Maximum Main Clock frequency using external clock
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __CLKMOMAX    ( 50000000UL)

/**
 ******************************************************************************
 ** \brief Any case minimum Sub Clock frequency
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __CLKSOMIN    (    32000UL)
   
/**
 ******************************************************************************
 ** \brief Maximum Sub Clock frequency using external clock
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __CLKSOMAX    (   100000UL)
   
/**
 ******************************************************************************
 ** \brief Absolute minimum PLL input frequency
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __PLLCLKINMIN (  4000000UL)
   
/**
 ******************************************************************************
 ** \brief Absolute maximum PLL input frequency
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __PLLCLKINMAX ( 16000000UL)

/**
 ******************************************************************************
 ** \brief Absolute minimum PLL oscillation frequency
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __PLLCLKMIN   (200000000UL)
   
/**
 ******************************************************************************
 ** \brief Absolute maximum PLL oscillation  frequency
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __PLLCLKMAX   (300000000UL)

/**
 ******************************************************************************
 ** \brief Absolute maximum System Clock frequency (HCLK)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __HCLKMAX     (144000000UL)

/**
 ******************************************************************************
 ** \brief Preprocessor macro for checking range (clock settings)
 ******************************************************************************/ 
#define CHECK_RANGE(val, min, max)                ((val < min) || (val > max))
   
/**
 ******************************************************************************
 ** \brief Preprocessor macro for checking bits with mask (clock settings)
 ******************************************************************************/ 
#define CHECK_RSVD(val, mask)                     (val & mask)


/******************************************************************************/
/* Check register settings                                                    */
/******************************************************************************/
#if (CHECK_RSVD((SCM_CTL_Val),    ~0x000000FA))
   #error "SCM_CTL: Invalid values of reserved bits!"
#endif

#if ((SCM_CTL_Val & 0xE0) == 0x40) && ((SCM_CTL_Val & 0x10) != 0x10)
   #error "SCM_CTL: CLKPLL is selected but PLL is not enabled!"
#endif

#if (CHECK_RSVD((CSW_TMR_Val),    ~0x0000007F))
   #error "CSW_TMR: Invalid values of reserved bits!"
#endif

#if ((SCM_CTL_Val & 0x10))       /* if PLL is used */
  #if (CHECK_RSVD((PSW_TMR_val),  ~0x00000007))
     #error "PSW_TMR: Invalid values of reserved bits!"
  #endif

  #if (CHECK_RSVD((PLL_CTL1_Val), ~0x000000FF))
     #error "PLL_CTL1: Invalid values of reserved bits!"
  #endif

  #if (CHECK_RSVD((PLL_CTL2_Val), ~0x0000003F))
    #error "PLL_CTL2: Invalid values of reserved bits!"
  #endif
#endif

#if (CHECK_RSVD((BSC_PSR_Val),    ~0x00000007))
  #error "BSC_PSR: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((APBC0_PSR_Val),  ~0x00000003))
  #error "APBC0_PSR: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((APBC1_PSR_Val),  ~0x00000083))
  #error "APBC1_PSR: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((APBC2_PSR_Val),  ~0x00000083))
  #error "APBC2_PSR: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((SWC_PSR_Val),    ~0x00000003))
  #error "SWC_PSR: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((TTC_PSR_Val),    ~0x00000001))
  #error "TTC_PSR: Invalid values of reserved bits!"
#endif

/******************************************************************************/
/* Define clocks with checking settings                                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief Calculate PLL K factor from settings
 ******************************************************************************/
#define __PLLK         (((PLL_CTL1_Val >> 4) & 0x0F) + 1)

/**
 ******************************************************************************
 ** \brief Calculate PLL N factor from settings
 ******************************************************************************/
#define __PLLN         (((PLL_CTL2_Val     ) & 0x3F) + 1)

/**
 ******************************************************************************
 ** \brief Calculate PLL M factor from settings
 ******************************************************************************/
#define __PLLM         (((PLL_CTL1_Val     ) & 0x0F) + 1)

/**
 ******************************************************************************
 ** \brief Calculate PLL output frequency from settings
 ******************************************************************************/
#define __PLLCLK       ((__CLKMO  * __PLLN) / __PLLK)

/******************************************************************************/
/* Determine core clock frequency according to settings                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief Define Master Clock from settings
 ******************************************************************************/
#if   (((SCM_CTL_Val >> 5) & 0x07) == 0)
  #define __MASTERCLK     (__CLKHC)
#elif (((SCM_CTL_Val >> 5) & 0x07) == 1)
  #define __MASTERCLK     (__CLKMO)
#elif (((SCM_CTL_Val >> 5) & 0x07) == 2)
  #define __MASTERCLK     (__PLLCLK)
#elif (((SCM_CTL_Val >> 5) & 0x07) == 4)
  #define __MASTERCLK     (__CLKLC)
#elif (((SCM_CTL_Val >> 5) & 0x07) == 5)
  #define __MASTERCLK     (__CLKSO)
#else
  #define __MASTERCLK     (0UL)
#endif

/**
 ******************************************************************************
 ** \brief Define System Clock Frequency (Core Clock) from settings
 ******************************************************************************/
#if   ((BSC_PSR_Val & 0x07) == 0)
  #define __HCLK         (__MASTERCLK / 1)
#elif ((BSC_PSR_Val & 0x07) == 1)
  #define __HCLK         (__MASTERCLK / 2)
#elif ((BSC_PSR_Val & 0x07) == 2)
  #define __HCLK         (__MASTERCLK / 3)
#elif ((BSC_PSR_Val & 0x07) == 3)
  #define __HCLK         (__MASTERCLK / 4)
#elif ((BSC_PSR_Val & 0x07) == 4)
  #define __HCLK         (__MASTERCLK / 6)
#elif ((BSC_PSR_Val & 0x07) == 5)
  #define __HCLK         (__MASTERCLK / 8)
#elif ((BSC_PSR_Val & 0x07) == 6)
  #define __HCLK         (__MASTERCLK /16)
#else
  #define __HCLK         (0UL)
#endif

/******************************************************************************/
/* HCLK range check                                                           */
/******************************************************************************/
#if (CHECK_RANGE(__CLKMO, __CLKMOMIN, __CLKMOMAX) != 0)
  #error "Main Oscillator Clock (CLKMO) out of range!"
#endif   

#if (CHECK_RANGE(__CLKSO, __CLKSOMIN, __CLKSOMAX) != 0)
  #error "Sub Oscillator Clock (CLKMO) out of range!"
#endif   

#if (CHECK_RANGE((__CLKMO / __PLLK), __PLLCLKINMIN, __PLLCLKINMAX) != 0)
  #error "PLL input frequency out of range!"
#endif  

#if (CHECK_RANGE(((__CLKMO * __PLLN * __PLLM) / __PLLK), __PLLCLKMIN, __PLLCLKMAX) != 0)
  #error "PLL oscillation frequency out of range!"
#endif  
   
#if (CHECK_RANGE(__HCLK, 0, __HCLKMAX) != 0)
  #error "System Clock (HCLK) out of range!"
#endif
   
/******************************************************************************/
/* Global function prototypes ('extern', definition in C source)              */
/******************************************************************************/

extern uint32_t SystemCoreClock;          // System Clock Frequency (Core Clock)
   
extern void SystemInit (void);            // Initialize the system

extern void SystemCoreClockUpdate (void); // Update SystemCoreClock variable

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_MB9BF61X_H */
