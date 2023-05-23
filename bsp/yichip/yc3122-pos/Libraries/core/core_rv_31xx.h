/*
 * Copyright (c) 2006-2021, YICHIP Development Team
 * @file     yc_rom_api.h
 * @brief    source file for setting rom_api
 *
 * Change Logs:
 * Date           Author      Version        Notes
 * 2021-06-23     wushengyan  V1.0.0         the first version
 */
#ifndef __RV_31XX_H__
#define __RV_31XX_H__

#ifdef __USE_YC_RISC_V__

#include "type.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* IO definitions (access restrictions to peripheral registers) */
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */
/*end IO definitions*/


#define __STATIC_INLINE                        static __inline
/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
  - Core NVIC PLIC
  - Core SysTick Register
 ******************************************************************************/

/********************  RISC-V REG START  **************************************/
typedef struct
{
    __IO  uint32_t RV_PAUSE_EN                  : 1;
    __IO  uint32_t RV_PAUSE_START               : 1;
    __IO  uint32_t RV_DCLK_EN                   : 1;
    __IO  uint32_t RV_QSORTCLK_EN               : 1;
    __IO  uint32_t RV_BINCLK_EN                 : 1;
    __IO  uint32_t DBG_STEP_EN                  : 1;
    __IO  uint32_t FPU_STEP_DIS                 : 1;
    __IO  uint32_t LONGP_STEP_EN                : 1;
    __IO  uint32_t RV_CORECLK_EN                : 8;
    __I   uint32_t RV_CTRL_RSVD                 : 16;
    __IO  uint32_t RV_WKUP_SRC_EN               : 32;
    __IO  uint32_t RV_PC_RTVEC                  : 32;
    __IO  uint32_t RV_STACK_ADDR                : 32;
} RVCtrl_TypeDef;

typedef struct
{
    __IO  uint32_t ICE_CTRL                     : 16;
    __IO  uint32_t ICE_CMD                      : 4;
    __I   uint32_t ICE_CTRL_RSVD                : 12;
    __IO  uint32_t ICE_BREAK0                   : 25;
    __I   uint32_t ICE_BREAK0_RSVD              : 7;
    __IO  uint32_t ICE_BREAK1                   : 25;
    __I   uint32_t ICE_BREAK1_RSVD              : 7;
    __IO  uint32_t ICE_REG_WDATA                : 32;
    __I   uint32_t ICE_REG_RDATA                : 32;
    __IO  uint32_t TRACE_ADDR                   : 25;
    __I   uint32_t TRACE_ADDR_RSVD              : 7;
    __I   uint32_t TRACE_FIFO_RDATA             : 25;
    __I   uint32_t TRACE_FIFO_RDATA_RSVD        : 7;
    __I   uint32_t EXE_ADDR                     : 32;
    __I   uint32_t ICE_STATUS                   : 8;
    __I   uint32_t ICE_STATUS_RSVD              : 24;                           //RV_CTRL
} RVIce_TypeDef;

typedef struct
{
    __IO  uint32_t BIN_CTRL_BLOCK_ENABLE        : 1;
    __IO  uint32_t BIN_CTRL_GRID_MODE           : 1;
    __IO  uint32_t BIN_CTRL_CUT_ENABLE          : 1;
    __IO  uint32_t BIN_CTRL_SCALER_ENABLE       : 1;
    __IO  uint32_t BIN_CTRL_INV_BIT_ENABLE      : 1;
    __I   uint32_t BIN_CTRL_RSVD                : 3;
    __IO  uint32_t RANGE                        : 8;
    __IO  uint32_t SUB_HEIGHT                   : 8;
    __IO  uint32_t SUB_WIDTH                    : 8;

    __IO  uint32_t RAW_BIN_BASEADDR             : 24;
    __I   uint32_t RAW_BIN_BASEADDR_RSVD        : 8;
    __IO  uint32_t RGB_BASEADDR                 : 24;
    __I   uint32_t RGB_BASEADDR_RSVD            : 8;
    __IO  uint32_t AVG_BASEADDR                 : 24;
    __I   uint32_t AVG_BASEADDR_RSVD            : 8;
    __IO  uint32_t SCA_BIN_BASEADDR             : 24;
    __I   uint32_t SCA_BIN_BASEADDR_RSVD        : 8;

    __I   uint32_t BIN_STATUS                   : 32;
    __I   uint32_t RAW_DOUT_ADDR_LOCK           : 24;
    __I   uint32_t RAW_DOUT_ADDR_LOCK_RSVD      : 8;
    __I   uint32_t SCA_DOUT_ADDR_LOCK           : 24;
    __I   uint32_t SCA_DOUT_ADDR_LOCK_RSVD      : 8;
    __IO  uint32_t QSORT_CTRL                   : 32;
    __IO  uint32_t QSORT_BASEADDR               : 24;
    __I   uint32_t QSORT_BASEADDR_RSVD          : 8;
    __I   uint32_t QSORT_DONE                   : 1;
    __I   uint32_t QSORT_DONE_RSVD              : 31;

    __IO  uint32_t ONE_RGB_BASEADDR             : 24;
    __I   uint32_t ONE_RGB_BASEADDR_RSVD        : 8;
    __IO  uint32_t FAST_BIN_BASEADDR            : 24;
    __I   uint32_t FAST_BIN_BASEADDR_RSVD       : 8;
    __IO  uint32_t CANNY_BIN_BASEADDR           : 24;
    __I   uint32_t CANNY_BIN_BASEADDR_RSVD      : 8;
    __IO  uint32_t ONE_BIN_CTRL                 : 13;
    __I   uint32_t ONE_BIN_CTRL_RSVD            : 19;
    __IO  uint32_t FAST_BIN_CTRL                : 24;
    __I   uint32_t FAST_BIN_CTRL_RSVD           : 8;
    __IO  uint32_t CANNY_BIN_CTRL               : 23;
    __I   uint32_t CANNY_BIN_CTRL_RSVD          : 9;
    __IO  uint32_t CANNY_BIN_CTRL1              : 12;
    __I   uint32_t CANNY_BIN_CTRL1_RSVD         : 20;
    __IO  uint32_t ONE_BIN_STATUS               : 21;
    __I   uint32_t ONE_BIN_STATUS_RSVD          : 11;
    __IO  uint32_t FAST_BIN_BASEADDR_USED       : 24;
    __I   uint32_t FAST_BIN_BASEADDR_USED_RSVD  : 8;
    __IO  uint32_t CANNY_BIN_BASEADDR_USED      : 24;
    __I   uint32_t CANNY_BIN_BASEADDR_USED_RSVD : 8;
} RVBin_TypeDef;

typedef struct
{
    __IO  uint32_t JTAG_SW_SEL                  :1;
    __I   uint32_t JTAG_SW_SEL_RSVD             :3;
    __IO  uint32_t DAP_REG_BASE_ADDR            :4;
    __I   uint32_t DAP_CTRL_RSVD                :24;
    __IO  uint32_t RV_TM_EN                     :1;
    __IO  uint32_t RV_TM_EN_RSVD                :31;
    __IO  uint32_t RV_TM_CNT                    :32;
    __IO  uint32_t M0_TO_RV_IE                  :1;
    __I   uint32_t M0_TO_RV_IE_RSVD             :7;
    __IO  uint32_t M0_TO_RV_IRQ                 :1;
    __I   uint32_t M0_TO_RV_IRQ_RSVD            :7;
    __IO  uint32_t RV_TO_M0_IRQ_TRIG            :1;
    __I   uint32_t RV_TO_M0_IRQ_TRIG_RSVD       :15;
    __IO  uint32_t IRQ_SW_EN                    :1;
    __IO  uint32_t IRQ_SW_PEND                  :1;
    __I   uint32_t IRQ_SW_RSVD                  :6;
    __IO  uint32_t IRQ_SW_CODE                  :8;
    __I   uint32_t RV_SW_IRQ_RSVD               :16;
}RVIrq_TypeDef;

#define MPU_REGION_NUM    4
typedef struct
{
    __IO uint8_t Protect_region[MPU_REGION_NUM];

} RVMPUREGION_TypeDef;

typedef struct
{
    __IO uint32_t BaseAndLimit[MPU_REGION_NUM];

} RVMPUBASE_TypeDef;

#define BASE_LIMIT_REGION_NUM    4
typedef struct
{
    __IO uint32_t MPU_ENABLE_CODE                   : 4;
    __IO RVMPUREGION_TypeDef ICB_PROTECT;
    __IO RVMPUREGION_TypeDef DTCM_PROTECT;
    __IO RVMPUREGION_TypeDef ITCM_PROTECT;
    __IO uint32_t  USER_START                       : 24;
    __IO uint32_t  MPU_STS_CLR;
    __I  uint32_t  FAULT_STATUS;
    __I  uint32_t  FAULT_ADDR_ICB;
    __I  uint32_t  FAULT_ADDR_DTCM;
    __I  uint32_t  FAULT_ADDR_ITCM;
    __IO RVMPUBASE_TypeDef  ICB_BASE;
    __IO RVMPUBASE_TypeDef  DTCM_BASE;
    __IO RVMPUBASE_TypeDef  ITCM_BASE;
    __IO RVMPUBASE_TypeDef  ICB_LIMIT;
    __IO RVMPUBASE_TypeDef  DTCM_LIMIT;
    __IO RVMPUBASE_TypeDef  ITCM_LIMIT;
} RVMPU_TypeDef;

typedef struct
{
    __IO  uint32_t WDT_EN                       : 1;
    __IO  uint32_t WDT_EN_LOCK                  : 1;
    __IO  uint32_t WDT_ACT                      : 1;
    __I   uint32_t WDT_CTRL_RSVD1               : 5;
    __IO  uint32_t WDT_DIV                      : 4;
    __I   uint32_t WDT_CTRL_RSVD2               : 20;
    __IO  uint32_t WDT_KEY                      : 16;
    __I   uint32_t WDT_KEY_RSVD                 : 16;
    __IO  uint32_t WDT_RELOAD_VALUE             : 32;
    __I   uint32_t WDT_CNT                      : 32;
    __IO  uint32_t WDT_IRQ_EN                   : 1;
    __I   uint32_t WDT_IRQ_EN_RSVD              : 31;
    __IO  uint32_t WDT_IRQ                      : 1;
    __I   uint32_t WDT_IRQ_RSVD                 : 31;
} RVWdt_TypeDef;

#define YC3122_RV_BASE                          (0x000E0000UL)   /* RV Base Address */

#define RV_CTRL_BASEADDR                        (YC3122_RV_BASE + 0x00000) //0xe0000
#define RV_ICE_BASEADDR                         (YC3122_RV_BASE + 0x00004) //0xe0004
#define RV_BIN_BASEADDR                         (YC3122_RV_BASE + 0x00034) //0xe0034
#define RV_IRQ_BASEADDR                         (YC3122_RV_BASE + 0x000D0) //0xe00d0
#define RV_SYSTICK_BASEADDR                     (YC3122_RV_BASE + 0x000D0) //0xe00d4
#define RV_MPU_BASEADDR                         (YC3122_RV_BASE + 0x00100) //0xe0100
#define RV_IRQ_PRIO_BASEADDR                    (YC3122_RV_BASE + 0x01000) //0xe1000
#define RV_IRQ_PEND_BASEADDR                    (YC3122_RV_BASE + 0x02000) //0xe2000
#define RV_IRQ_ENAB_BASEADDR                    (YC3122_RV_BASE + 0x03000) //0xe3000
#define RV_IRQ_THRD_BASEADDR                    (YC3122_RV_BASE + 0x04000) //0xe4000
#define RV_IRQ_CLAM_BASEADDR                    (YC3122_RV_BASE + 0x04004) //0xe4004
#define RV_WDT_BASEADDR                         (0xfb700) //0xfb700

#define RV_CTRL1                             	((RVCtrl_TypeDef *)RV_CTRL_BASEADDR)
#define RV_ICE                                  ((RVIce_TypeDef *)RV_ICE_BASEADDR)
#define RV_BIN                                  ((RVBin_TypeDef *)RV_BIN_BASEADDR)
#define RISC_IRQ                                ((RVIrq_TypeDef *)RV_IRQ_BASEADDR)

/*risc-v mpu map start*/
#define RV_MPU_ICB_PROTECT_BASE                 (RV_MPU_BASEADDR + 0x0004)
#define RV_MPU_DTCM_PROTECT_BASE                (RV_MPU_ICB_PROTECT_BASE + 0x0004)
#define RV_MPU_ITCM_PROTECT_BASE                (RV_MPU_DTCM_PROTECT_BASE + 0x0004)

#define RV_MPU_ICB_BASE_BASE                    (RV_MPU_BASEADDR + 0x0040)
#define RV_MPU_DTCM_BASE_BASE                   (RV_MPU_ICB_BASE_BASE + 0x0010)
#define RV_MPU_ITCM_BASE_BASE                   (RV_MPU_DTCM_BASE_BASE + 0x0010)

#define RV_MPU_ICB_LIMIT_BASE                   (RV_MPU_BASEADDR + 0x0080)
#define RV_MPU_DTCM_LIMIT_BASE                  (RV_MPU_ICB_LIMIT_BASE + 0x0010)
#define RV_MPU_ITCM_LIMIT_BASE                  (RV_MPU_DTCM_LIMIT_BASE + 0x0010)

/*risc-v mpu reg start*/
#define RVMPU                                   ((RVMPU_TypeDef *)RV_MPU_BASEADDR)
#define ICB_PROTECTION                          ((RVMPUREGION_TypeDef *)RV_MPU_ICB_PROTECT_BASE)
#define DTCM_PROTECTION                         ((RVMPUREGION_TypeDef *)RV_MPU_DTCM_PROTECT_BASE)
#define ITCM_PROTECTION                         ((RVMPUREGION_TypeDef *)RV_MPU_ITCM_PROTECT_BASE)

#define ICB_BASE                                ((RVMPUBASE_TypeDef *)RV_MPU_ICB_BASE_BASE)
#define DTCM_BASE                               ((RVMPUBASE_TypeDef *)RV_MPU_DTCM_BASE_BASE)
#define ITCM_BASE                               ((RVMPUBASE_TypeDef *)RV_MPU_ITCM_BASE_BASE)

#define ICB_LIMIT                               ((RVMPUBASE_TypeDef *)RV_MPU_ICB_LIMIT_BASE)
#define DTCM_LIMIT                              ((RVMPUBASE_TypeDef *)RV_MPU_DTCM_LIMIT_BASE)
#define ITCM_LIMIT                              ((RVMPUBASE_TypeDef *)RV_MPU_ITCM_LIMIT_BASE)


#define RV_WDT                                  ((RVWdt_TypeDef *)RV_WDT_BASEADDR)

#define RV_IRQ_PRIO(x)				            *(volatile uint8_t*)(RV_IRQ_PRIO_BASEADDR + ((uint8_t)((uint8_t)(x)/2)))
#define RV_IRQ_PEND(x)				            *(volatile uint8_t*)(RV_IRQ_PEND_BASEADDR + ((uint8_t)((uint8_t)(x)/8)))
#define RV_IRQ_ENAB(x)				            *(volatile uint8_t*)(RV_IRQ_ENAB_BASEADDR + ((uint8_t)((uint8_t)(x)/8)))
#define RV_IRQ_THOD					            *(volatile int*)(RV_IRQ_THRD_BASEADDR)
#define RV_IRQ_CLAM					            *(volatile int*)(RV_IRQ_CLAM_BASEADDR)
/********************  RISC-V REG END    **************************************/


/**
  \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  uint32_t TM_EN;                   /*!< Offset: 0x000 (R/W)  SysTick Enable */
  uint32_t TM_CNT;                  /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
} SysTick_Type;



#define SysTick             ((SysTick_Type   *)     RV_SYSTICK_BASEADDR  )   /*!< SysTick configuration struct */
/******************************************************************************/


/**
 * @method	RV EnableIRQ
 * @brief	  Enable IRQ
 * @param	IRQn   : USB_IRQn...
 * @retval NULL
 */
__STATIC_INLINE void RV_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    RV_IRQ_ENAB(IRQn) |= (uint32_t)(1UL << (uint8_t)((uint8_t)(IRQn)%8));
  }
}

/**
 * @method	RV DisableIRQ
 * @brief	  Disable IRQ
 * @param	IRQn   : USB_IRQn...
 * @retval NULL
 */
__STATIC_INLINE void RV_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    RV_IRQ_ENAB(IRQn) &= ~(uint32_t)(1UL << (uint8_t)((uint8_t)(IRQn)%8));
  }
}

/**
 * @method	RV SetPriority
 * @brief	  SetPriority IRQ
 * @param	IRQn      : USB_IRQn...
 * @param	priority  : 0~15
 * @retval NULL
 */
__STATIC_INLINE void RV_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0 && priority > 0 && priority < 16)
  {
    RV_IRQ_PRIO(IRQn) |= (priority << (uint8_t)((uint8_t)(IRQn)%2)*4);
  }
}

/**
 * @method	RV Get Pending Interrupt
 * @brief	  Reads The PLIC pending register returns the pending bit
 * @param	IRQn      : USB_IRQn...
 * @retval 0:  Interrupt status is not pending.
 *         1:  Interrupt status is pending
 */
__STATIC_INLINE uint32_t RV_GetPendingIRQ(IRQn_Type IRQn)
{

}

/**
 * @method	RV Get Interrupt Priority
 * @brief	  Reads the priority of a device specific interrupt
 * @param	IRQn      : USB_IRQn...
 * @retval  Interrupt Priority.
 */
__STATIC_INLINE uint32_t RV_GetPriority(IRQn_Type IRQn)
{

}

/**
 * @method NVIC_Configuration
 * @brief  NVIC initialization function for risc-v.
 * @param  IRQn: Interrupt vector numbers could be 0~31.
 * @param  priority: Interrupt priority numbers could be 1~15.
 * @param  newstate: enable or disable
 * @retval None
 */
__STATIC_INLINE void NVIC_Configuration(IRQn_Type IRQn, uint32_t priority,FunctionalState newstate)
{
    if(newstate == ENABLE )
    {
    	RV_EnableIRQ(IRQn);
    	RV_SetPriority(IRQn, priority);
    }
    else
    {
    	RV_DisableIRQ(IRQn);
    	RV_SetPriority(IRQn, priority);
    }
}

/**
 * @method SysTick_Config
 * @brief  Initializes the System Timer and its interrupt (priority default 1)
 * @param  ticks: Number of ticks between two interrupts. (0~0xffffffff)
 * @retval 0: FuncTion succeeded.
 *         1: Function failed.
 */
__STATIC_INLINE uint32_t SysTick_Config(uint32_t ticks)
{
  SysTick->TM_CNT = ticks;
  RV_EnableIRQ(34);    /*set systick priority*/
  RV_SetPriority(34,15);
  SysTick->TM_EN  = 1;

  return (0UL);
}

/**
 * @method __enable_irq
 * @brief  Enable IRQ Interrupts
 * @retval NONE.
 */
__STATIC_INLINE void __enable_irq(void)
{
	__asm("csrs mstatus,0x00000008");
}

/**
 * @method __disable_irq
 * @brief  Disable IRQ Interrupts
 * @retval NONE.
 */
__STATIC_INLINE void __disable_irq(void)
{
	__asm("csrc mstatus,0x00000008");
}

/*make M0 and RV IRQ equ*/
#define NVIC_EnableIRQ      RV_EnableIRQ
#define NVIC_DisableIRQ     RV_DisableIRQ
#define NVIC_SetPriority    RV_SetPriority
#define NVIC_GetPendingIRQ  RV_GetPendingIRQ
/*end*/


#ifdef __cplusplus
}
#endif

#endif
#endif
