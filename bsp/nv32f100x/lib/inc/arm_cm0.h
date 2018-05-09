/******************************************************************************
*
* @brief provide generic high-level routines for ARM Cortex M0/M0+ processors. 
*
*******************************************************************************/

#ifndef _CPU_ARM_CM0_H
#define _CPU_ARM_CM0_H

/*ARM Cortex M0 implementation for interrupt priority shift*/
#define ARM_INTERRUPT_LEVEL_BITS          2


/***********************************************************************/
  /*!< Macro to enable all interrupts. */
#ifndef KEIL
#define EnableInterrupts asm(" CPSIE i");
#else
#define EnableInterrupts  __enable_irq()
#endif

  /*!< Macro to disable all interrupts. */
#ifndef KEIL
#define DisableInterrupts asm(" CPSID i");
#else
#define DisableInterrupts __disable_irq()
#endif

#define disable_irq(irq)             NVIC_DisableIRQ(irq)
#define enable_irq(irq)              NVIC_EnableIRQ(irq)
#define set_irq_priority(irq, prio)  NVIC_SetPriority(irq, prio)
/***********************************************************************/


/*
 * Misc. Defines
 */
#ifdef	FALSE
#undef	FALSE
#endif
#define FALSE	(0)

#ifdef	TRUE
#undef	TRUE
#endif
#define	TRUE	(1)

#ifdef	NULL
#undef	NULL
#endif
#define NULL	(0)

#ifdef  ON
#undef  ON
#endif
#define ON      (1)

#ifdef  OFF
#undef  OFF
#endif
#define OFF     (0)

#undef  ENABLE
#define ENABLE  (1)

#undef  DISABLE
#define DISABLE  (0)


/***********************************************************************/
/*
 * The basic data types
 */
typedef unsigned char		uint8;  /*  8 bits */
typedef unsigned short int	uint16; /* 16 bits */
typedef unsigned long int	uint32; /* 32 bits */

typedef char			int8;   /*  8 bits */
typedef short int	        int16;  /* 16 bits */
typedef int		        int32;  /* 32 bits */

typedef volatile int8		vint8;  /*  8 bits */
typedef volatile int16		vint16; /* 16 bits */
typedef volatile int32		vint32; /* 32 bits */

typedef volatile uint8		vuint8;  /*  8 bits */
typedef volatile uint16		vuint16; /* 16 bits */
typedef volatile uint32		vuint32; /* 32 bits */

// function prototype for main function
int main(void);
/***********************************************************************/
// function prototypes for arm_cm0.c
void stop (void);
void wait (void);
void write_vtor (int);

/***********************************************************************/
#endif	/* _CPU_ARM_CM4_H */

