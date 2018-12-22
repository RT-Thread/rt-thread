/*!
    \file  gd32f4xx_trng.h
    \brief definitions for the TRNG
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef GD32F4XX_TRNG_H
#define GD32F4XX_TRNG_H

#include "gd32f4xx.h"

/* EXTI definitions */
#define TRNG                        TRNG_BASE

/* registers definitions */
#define TRNG_CTL                    REG32(TRNG + 0x00U)        /*!< interrupt enable register */
#define TRNG_STAT                   REG32(TRNG + 0x04U)        /*!< event enable register */
#define TRNG_DATA                   REG32(TRNG + 0x08U)        /*!< rising edge trigger enable register */

/* bits definitions */
/* TRNG_CTL */
#define TRNG_CTL_TRNGEN             BIT(2)                     /*!< TRNG enable bit */
#define TRNG_CTL_IE                 BIT(3)                     /*!< interrupt enable bit */

/* TRNG_STAT */
#define TRNG_STAT_DRDY              BIT(0)                     /*!< random data ready status bit */
#define TRNG_STAT_CECS              BIT(1)                     /*!< clock error current status */
#define TRNG_STAT_SECS              BIT(2)                     /*!< seed error current status */
#define TRNG_STAT_CEIF              BIT(5)                     /*!< clock error interrupt flag */
#define TRNG_STAT_SEIF              BIT(6)                     /*!< seed error interrupt flag */

/* TRNG_DATA */
#define TRNG_DATA_TRNDATA           BITS(0,31)                 /*!< 32-Bit Random data */

/* constants definitions */
/* trng status flag */
typedef enum
{ 
    TRNG_FLAG_DRDY = TRNG_STAT_DRDY,                           /*!< random Data ready status */
    TRNG_FLAG_CECS = TRNG_STAT_CECS,                           /*!< clock error current status */
    TRNG_FLAG_SECS = TRNG_STAT_SECS                            /*!< seed error current status */
}trng_flag_enum;

/* trng inerrupt flag */
typedef enum
{
    TRNG_INT_FLAG_CEIF = TRNG_STAT_CEIF,                       /*!< clock error interrupt flag */
    TRNG_INT_FLAG_SEIF = TRNG_STAT_SEIF                        /*!< seed error interrupt flag */
}trng_int_flag_enum;

/* function declarations */
/* deinitialize the TRNG */
void trng_deinit(void);
/* enable the TRNG interface */
void trng_enable(void);
/* disable the TRNG interface */
void trng_disable(void);
/* get the true random data */
uint32_t trng_get_true_random_data(void);
/* get the trng status flags */
FlagStatus trng_flag_get(trng_flag_enum flag);
/* clear the trng status flags */
void trng_flag_clear(trng_flag_enum flag);
/* the trng interrupt enable */
void trng_interrupt_enable(void);
/* the trng interrupt disable */
void trng_interrupt_disable(void);
/* get the trng interrupt flags */
FlagStatus trng_interrupt_flag_get(trng_int_flag_enum int_flag);
/* clear the trng interrupt flags */
void trng_interrupt_flag_clear(trng_int_flag_enum int_flag);

#endif /* GD32F4XX_TRNG_H */
