/*******************************************************************************
* Copyright (C) 2013 Spansion LLC. All Rights Reserved. 
*
* This software is owned and published by: 
* Spansion LLC, 915 DeGuigne Dr. Sunnyvale, CA  94088-3453 ("Spansion").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND 
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with Spansion 
* components. This software is licensed by Spansion to be adapted only 
* for use in systems utilizing Spansion components. Spansion shall not be 
* responsible for misuse or illegal use of this software for devices not 
* supported herein.  Spansion is providing this software "AS IS" and will 
* not be responsible for issues arising from incorrect user implementation 
* of the software.  
*
* SPANSION MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS), 
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING, 
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED 
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED 
* WARRANTY OF NONINFRINGEMENT.  
* SPANSION SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT, 
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT 
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, 
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR 
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA, 
* SAVINGS OR PROFITS, 
* EVEN IF SPANSION HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED 
* FROM, THE SOFTWARE.  
*
* This software may be replicated in part or whole for the licensed use, 
* with the restriction that this Disclaimer and Copyright notice must be 
* included with each copy of this software, whether used in part or whole, 
* at all times.  
*/

/******************************************************************************/
/** \file system_mb9bf56xr.h
 **
 ** Headerfile for FM4 system parameters
 **
 ** History: 
 ** 2013-01-21  0.1  MWi  AI: Unification to be done
 ** 2013-02-06  0.2  MWi  CMSIS coding restored; unifying still to be done
 ** 2013-06-28  0.3  EH   Added Trace Buffer enable definition
 ** 2013-08-15  0.4  EH   Changed APB1 Prescaler value
 ******************************************************************************/

#ifndef _SYSTEM_MB9ABXXX_H_
#define _SYSTEM_MB9ABXXX_H_

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
 ** \brief External Main Clock Frequency (in Hz, [value]ul)
 **        <i>(USER SETTING)</i>
 ******************************************************************************/    
#define __CLKMO        ( 4000000ul)   // <<< External   4MHz Crystal

/**
 ******************************************************************************
 ** \brief External Sub Clock Frequency (in Hz, [value]ul)
 **        <i>(USER SETTING)</i>
 ******************************************************************************/  
#define __CLKSO        (   32768ul)   // <<<  External  32KHz Crystal

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
#define SCM_CTL_Val           0x00000052ul    // <<< Define SCM_CTL here

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
#define BSC_PSR_Val           0x00000000ul    // <<< Define BSC_PSR here
 
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
#define APBC0_PSR_Val         0x00000001UL     // <<< Define APBC0_PSR here
   
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
#define APBC1_PSR_Val         0x00000080ul    // <<< Define APBC1_PSR here
   
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
#define APBC2_PSR_Val         0x00000081ul    // <<< Define APBC2_PSR here

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
#define SWC_PSR_Val           0x00000003ul    // <<< Define SWC_PSR here

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
#define TTC_PSR_Val           0x00000000ul    // <<< Define TTC_PSR here
 
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
#define CSW_TMR_Val           0x0000005Cul    // <<< Define CSW_TMR here

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
#define PSW_TMR_Val           0x00000000ul    // <<< Define PSW_TMR here

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
#define PLL_CTL1_Val          0x00000001ul    // <<< Define PLL_CTL1 here

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
#define PLL_CTL2_Val          0x00000027ul    // <<< Define PLL_CTL2 here
   
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

/**
 ******************************************************************************
 ** brief Trace Buffer enable definition
 **        <i>(USER SETTING)</i>
 **
 ** - 0 = Trace Buffer disable
 ** - 1 = Trace Buffer enable
 ******************************************************************************/  
#define TRACE_BUFFER_ENABLE   1   // <<< Define Trace Buffer enable here

   
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
 ** \brief Internal High-Speed CR Oscillator Frequency (in Hz, [value]ul)
 **        <i>(USER SETTING)</i>
 ******************************************************************************/    
#define __CLKHC        ( 4000000ul)         /* Internal   4MHz CR Oscillator  */
   
/**
 ******************************************************************************
 ** \brief Internal Low-Speed CR Oscillator Frequency (in Hz, [value]ul)
 **        <i>(USER SETTING)</i>
 ******************************************************************************/ 
#define __CLKLC        (  100000ul)         /* Internal 100KHz CR Oscillator  */  

/**
 ******************************************************************************
 ** \brief Any case minimum Main Clock frequency (in Hz, [value]ul)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __CLKMOMIN    (  4000000ul)
   
/**
 ******************************************************************************
 ** \brief Maximum Main Clock frequency using external clock (in Hz, [value]ul)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __CLKMOMAX    ( 48000000ul)

/**
 ******************************************************************************
 ** \brief Any case minimum Sub Clock frequency (in Hz, [value]ul)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __CLKSOMIN    (    32000ul)
   
/**
 ******************************************************************************
 ** \brief Maximum Sub Clock frequency using external clock (in Hz, [value]ul)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __CLKSOMAX    (   100000ul)
   
/**
 ******************************************************************************
 ** \brief Absolute minimum PLL input frequency (in Hz, [value]ul)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __PLLCLKINMIN (  4000000ul)
   
/**
 ******************************************************************************
 ** \brief Absolute maximum PLL input frequency (in Hz, [value]ul)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __PLLCLKINMAX ( 16000000ul)

/**
 ******************************************************************************
 ** \brief Absolute minimum PLL oscillation frequency (in Hz, [value]ul)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __PLLCLKMIN   (200000000ul)
   
/**
 ******************************************************************************
 ** \brief Absolute maximum PLL oscillation  frequency (in Hz, [value]ul)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __PLLCLKMAX   (320000000ul)

/**
 ******************************************************************************
 ** \brief Absolute maximum System Clock frequency (HCLK) (in Hz, [value]ul)
 **        <i>(DEVICE DEPENDENT SETTING)</i>
 ******************************************************************************/ 
#define __HCLKMAX     (160000000ul)

/**
 ******************************************************************************
 ** \brief Preprocessor macro for checking range (clock settings).
 **
 ** \return 0    Within range
 ** \return 1    Out of range
 ******************************************************************************/ 
#define CHECK_RANGE(val, min, max)          (((val) < (min)) || ((val) > (max)))
   
/**
 ******************************************************************************
 ** \brief Preprocessor macro for checking bits with mask (clock settings).
 **        Prevents from setting reserved bits by mistake.
 **
 ** \return 0    All bits within mask
 ** \return 1    One or more bits out of mask
 ******************************************************************************/ 
#define CHECK_RSVD(val, mask)                ((val) & (mask))


/******************************************************************************/
/* Check register settings                                                    */
/******************************************************************************/
#if (CHECK_RSVD((SCM_CTL_Val),    ~0x000000FAul))
   #error "SCM_CTL: Invalid values of reserved bits!"
#endif

#if ((SCM_CTL_Val & 0xE0ul) == 0x40ul) && ((SCM_CTL_Val & 0x10ul) != 0x10ul)
   #error "SCM_CTL: CLKPLL is selected but PLL is not enabled!"
#endif

#if (CHECK_RSVD((CSW_TMR_Val),    ~0x0000007Ful))
   #error "CSW_TMR: Invalid values of reserved bits!"
#endif

#if ((SCM_CTL_Val & 0x10ul))       /* if PLL is used */
  #if (CHECK_RSVD((PSW_TMR_Val),  ~0x00000017ul))
     #error "PSW_TMR: Invalid values of reserved bits!"
  #endif

  #if (CHECK_RSVD((PLL_CTL1_Val), ~0x000000FFul))
     #error "PLL_CTL1: Invalid values of reserved bits!"
  #endif

  #if (CHECK_RSVD((PLL_CTL2_Val), ~0x0000003Ful))
    #error "PLL_CTL2: Invalid values of reserved bits!"
  #endif
#endif

#if (CHECK_RSVD((BSC_PSR_Val),    ~0x00000007ul))
  #error "BSC_PSR: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((APBC0_PSR_Val),  ~0x00000003ul))
  #error "APBC0_PSR: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((APBC1_PSR_Val),  ~0x00000093ul))
  #error "APBC1_PSR: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((APBC2_PSR_Val),  ~0x00000093ul))
  #error "APBC2_PSR: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((SWC_PSR_Val),    ~0x00000003ul))
  #error "SWC_PSR: Invalid values of reserved bits!"
#endif

#if (CHECK_RSVD((TTC_PSR_Val),    ~0x00000003ul))
  #error "TTC_PSR: Invalid values of reserved bits!"
#endif

/******************************************************************************/
/* Define clocks with checking settings                                       */
/******************************************************************************/

/**
 ******************************************************************************
 ** \brief Calculate PLL K factor from settings
 ******************************************************************************/
#define __PLLK         (((PLL_CTL1_Val >> 4ul) & 0x0Ful) + 1ul)

/**
 ******************************************************************************
 ** \brief Calculate PLL N factor from settings
 ******************************************************************************/
#define __PLLN         (((PLL_CTL2_Val     ) & 0x3Ful) + 1ul)

/**
 ******************************************************************************
 ** \brief Calculate PLL M factor from settings
 ******************************************************************************/
#define __PLLM         (((PLL_CTL1_Val     ) & 0x0Ful) + 1ul)

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
#if   (((SCM_CTL_Val >> 5ul) & 0x07UL) == 0ul)
  #define __MASTERCLK     (__CLKHC)
#elif (((SCM_CTL_Val >> 5ul) & 0x07UL) == 1ul)
  #define __MASTERCLK     (__CLKMO)
#elif (((SCM_CTL_Val >> 5ul) & 0x07UL) == 2ul)
  #define __MASTERCLK     (__PLLCLK)
#elif (((SCM_CTL_Val >> 5ul) & 0x07UL) == 4ul)
  #define __MASTERCLK     (__CLKLC)
#elif (((SCM_CTL_Val >> 5ul) & 0x07UL) == 5ul)
  #define __MASTERCLK     (__CLKSO)
#else
  #define __MASTERCLK     (0UL)
#endif

/**
 ******************************************************************************
 ** \brief Define System Clock Frequency (Core Clock) from settings
 ******************************************************************************/
#if   ((BSC_PSR_Val & 0x07UL) == 0ul)
  #define __HCLK         (__MASTERCLK / 1ul)
#elif ((BSC_PSR_Val & 0x07UL) == 1ul)
  #define __HCLK         (__MASTERCLK / 2ul)
#elif ((BSC_PSR_Val & 0x07UL) == 2ul)
  #define __HCLK         (__MASTERCLK / 3ul)
#elif ((BSC_PSR_Val & 0x07UL) == 3ul)
  #define __HCLK         (__MASTERCLK / 4ul)
#elif ((BSC_PSR_Val & 0x07UL) == 4ul)
  #define __HCLK         (__MASTERCLK / 6ul)
#elif ((BSC_PSR_Val & 0x07UL) == 5ul)
  #define __HCLK         (__MASTERCLK / 8ul)
#elif ((BSC_PSR_Val & 0x07UL) == 6ul)
  #define __HCLK         (__MASTERCLK /16ul)
#else
  #define __HCLK         (0ul)
#endif

/******************************************************************************/
/* HCLK range check                                                           */
/******************************************************************************/
#if (CHECK_RANGE(__CLKMO, __CLKMOMIN, __CLKMOMAX))
  #error "Main Oscillator Clock (CLKMO) out of range!"
#endif   

#if (CHECK_RANGE(__CLKSO, __CLKSOMIN, __CLKSOMAX))
  #error "Sub Oscillator Clock (CLKMO) out of range!"
#endif   

#if (CHECK_RANGE((__CLKMO / __PLLK), __PLLCLKINMIN, __PLLCLKINMAX))
  #error "PLL input frequency out of range!"
#endif  

#if (CHECK_RANGE(((__CLKMO * __PLLN * __PLLM) / __PLLK), __PLLCLKMIN, __PLLCLKMAX))
  #error "PLL oscillation frequency out of range!"
#endif  
   
#if (CHECK_RANGE(__HCLK, 0UL, __HCLKMAX))
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

#endif /* _SYSTEM_MB9ABXXX_H_ */
