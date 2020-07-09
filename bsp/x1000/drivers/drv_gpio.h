/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */

#ifndef _BOARD_GPIO_H_
#define _BOARD_GPIO_H_

#include <stdint.h>

//#define GPIO_PA(n)  (0*32 + n)
//#define GPIO_PB(n)  (1*32 + n)
//#define GPIO_PC(n)  (2*32 + n)
//#define GPIO_PD(n)  (3*32 + n)
//#define GPIO_PE(n)  (4*32 + n)
//#define GPIO_PF(n)  (5*32 + n)
//#define GPIO_PG(n)  (6*32 + n)

#define GPIO_PIN(n) (0x01 << n)

/*************************************************************************
 * GPIO (General-Purpose I/O Ports)
 *************************************************************************/
#define GPIO_PORT_OFF       0x100
#define GPIO_SHADOW_OFF     0x700

#define PXPIN       0x00   /* PIN Level Register */
#define PXINT       0x10   /* Port Interrupt Register */
#define PXINTS      0x14   /* Port Interrupt Set Register */
#define PXINTC      0x18   /* Port Interrupt Clear Register */
#define PXMSK       0x20   /* Port Interrupt Mask Reg */
#define PXMSKS      0x24   /* Port Interrupt Mask Set Reg */
#define PXMSKC      0x28   /* Port Interrupt Mask Clear Reg */
#define PXPAT1      0x30   /* Port Pattern 1 Set Reg. */
#define PXPAT1S     0x34   /* Port Pattern 1 Set Reg. */
#define PXPAT1C     0x38   /* Port Pattern 1 Clear Reg. */
#define PXPAT0      0x40   /* Port Pattern 0 Register */
#define PXPAT0S     0x44   /* Port Pattern 0 Set Register */
#define PXPAT0C     0x48   /* Port Pattern 0 Clear Register */
#define PXFLG       0x50   /* Port Flag Register */
#define PXFLGC      0x58   /* Port Flag clear Register */
#define PXOENS      0x64   /* Port Output Disable Set Register */
#define PXOENC      0x68   /* Port Output Disable Clear Register */
#define PXPEN       0x70   /* Port Pull Disable Register */
#define PXPENS      0x74   /* Port Pull Disable Set Register */
#define PXPENC      0x78   /* Port Pull Disable Clear Register */
#define PXDSS       0x84   /* Port Drive Strength set Register */
#define PXDSC       0x88   /* Port Drive Strength clear Register */
#define PZGID2LD    0xF0   /* GPIOZ Group ID to load */


#define GPIO_PXPIN(n)       (GPIO_BASE + (PXPIN     + (n) * GPIO_PORT_OFF)) /* PIN Level Register */
#define GPIO_PXINT(n)       (GPIO_BASE + (PXINT     + (n) * GPIO_PORT_OFF)) /* Port Interrupt Register */
#define GPIO_PXINTS(n)      (GPIO_BASE + (PXINTS    + (n) * GPIO_PORT_OFF)) /* Port Interrupt Set Register */
#define GPIO_PXINTC(n)      (GPIO_BASE + (PXINTC    + (n) * GPIO_PORT_OFF)) /* Port Interrupt Clear Register */
#define GPIO_PXMSK(n)       (GPIO_BASE + (PXMSK     + (n) * GPIO_PORT_OFF)) /* Port Interrupt Mask Register */
#define GPIO_PXMSKS(n)      (GPIO_BASE + (PXMSKS    + (n) * GPIO_PORT_OFF)) /* Port Interrupt Mask Set Reg */
#define GPIO_PXMSKC(n)      (GPIO_BASE + (PXMSKC    + (n) * GPIO_PORT_OFF)) /* Port Interrupt Mask Clear Reg */
#define GPIO_PXPAT1(n)      (GPIO_BASE + (PXPAT1    + (n) * GPIO_PORT_OFF)) /* Port Pattern 1 Register */
#define GPIO_PXPAT1S(n)     (GPIO_BASE + (PXPAT1S   + (n) * GPIO_PORT_OFF)) /* Port Pattern 1 Set Reg. */
#define GPIO_PXPAT1C(n)     (GPIO_BASE + (PXPAT1C   + (n) * GPIO_PORT_OFF)) /* Port Pattern 1 Clear Reg. */
#define GPIO_PXPAT0(n)      (GPIO_BASE + (PXPAT0    + (n) * GPIO_PORT_OFF)) /* Port Pattern 0 Register */
#define GPIO_PXPAT0S(n)     (GPIO_BASE + (PXPAT0S   + (n) * GPIO_PORT_OFF)) /* Port Pattern 0 Set Register */
#define GPIO_PXPAT0C(n)     (GPIO_BASE + (PXPAT0C   + (n) * GPIO_PORT_OFF)) /* Port Pattern 0 Clear Register */
#define GPIO_PXFLG(n)       (GPIO_BASE + (PXFLG     + (n) * GPIO_PORT_OFF)) /* Port Flag Register */
#define GPIO_PXFLGC(n)      (GPIO_BASE + (PXFLGC    + (n) * GPIO_PORT_OFF)) /* Port Flag clear Register */
#define GPIO_PXOENS(n)      (GPIO_BASE + (PXOENS    + (n) * GPIO_PORT_OFF))   /* Port Output Disable Set Register */
#define GPIO_PXOENC(n)      (GPIO_BASE + (PXOENC    + (n) * GPIO_PORT_OFF))   /* Port Output Disable Clear Register */
#define GPIO_PXPEN(n)       (GPIO_BASE + (PXPEN     + (n) * GPIO_PORT_OFF))   /* Port Pull Disable Register */
#define GPIO_PXPENS(n)      (GPIO_BASE + (PXPENS    + (n) * GPIO_PORT_OFF))   /* Port Pull Disable Set Register */
#define GPIO_PXPENC(n)      (GPIO_BASE + (PXPENC    + (n) * GPIO_PORT_OFF))   /* Port Pull Disable Clear Register */
#define GPIO_PXDSS(n)       (GPIO_BASE + (PXDSS     + (n) * GPIO_PORT_OFF))   /* Port Drive Strength set Register */
#define GPIO_PXDSC(n)       (GPIO_BASE + (PXDSC     + (n) * GPIO_PORT_OFF))   /* Port Drive Strength clear Register */
#define GPIO_PZGID2LD(n)    (GPIO_BASE + (PZGID2LD  + (n) * GPIO_PORT_OFF))   /* GPIOZ Group ID to load */


struct jzgpio_state {
    uint32_t pxint;
    uint32_t pxmsk;
    uint32_t pxpat1;
    uint32_t pxpat0;
    uint32_t pxpen;
    uint32_t pxignore;
};

enum gpio_function
{
    GPIO_FUNC_0     = 0x00,  //0000, GPIO as function 0 / device 0
    GPIO_FUNC_1     = 0x01,  //0001, GPIO as function 1 / device 1
    GPIO_FUNC_2     = 0x02,  //0010, GPIO as function 2 / device 2
    GPIO_FUNC_3     = 0x03,  //0011, GPIO as function 3 / device 3
    GPIO_OUTPUT0    = 0x04,  //0100, GPIO output low  level
    GPIO_OUTPUT1    = 0x05,  //0101, GPIO output high level
    GPIO_INPUT      = 0x06,  //0110, GPIO as input
    GPIO_INT_LO     = 0x08,  //1000, Low  Level trigger interrupt
    GPIO_INT_HI     = 0x09,  //1001, High Level trigger interrupt
    GPIO_INT_FE     = 0x0a,  //1010, Fall Edge trigger interrupt
    GPIO_INT_RE     = 0x0b,  //1011, Rise Edge trigger interrupt
    GPIO_PULL       = 0x10,  //0001 0000, GPIO enable pull
    GPIO_INPUT_PULL = 0x16,  //0001 0110, GPIO as input and enable pull
};

enum gpio_irq_type
{
    IRQ_TYPE_NONE           = 0x00000000,
    IRQ_TYPE_EDGE_RISING    = 0x00000001,
    IRQ_TYPE_EDGE_FALLING   = 0x00000002,
    IRQ_TYPE_EDGE_BOTH      = (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING),
    IRQ_TYPE_LEVEL_HIGH     = 0x00000004,
    IRQ_TYPE_LEVEL_LOW      = 0x00000008,
    IRQ_TYPE_LEVEL_MASK     = (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH),
    IRQ_TYPE_SENSE_MASK     = 0x0000000f,
    IRQ_TYPE_DEFAULT        = IRQ_TYPE_SENSE_MASK,

    IRQ_TYPE_PROBE          = 0x00000010,

    IRQ_LEVEL               = (1 <<  8),
};

enum gpio_port {
    GPIO_PORT_A = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    /* this must be last */
    GPIO_NR_PORTS,
	GPIO_PORT_Z = 7,
};

//#define IS_GPIO_ALL_PORT(PORT) (   ((PORT) == GPIO_PORT_A) || \
//                                    ((PORT) == GPIO_PORT_B) || \
//                                    ((PORT) == GPIO_PORT_C) || \
//                                    ((PORT) == GPIO_PORT_D) )
#define IS_GPIO_ALL_PORT(PORT) (   (PORT) < GPIO_NR_PORTS )

enum gpio_pin {
    GPIO_Pin_0     = ((uint32_t)0x00000001),  /* Pin 0  selected */
    GPIO_Pin_1     = ((uint32_t)0x00000002),  /* Pin 1  selected */
    GPIO_Pin_2     = ((uint32_t)0x00000004),  /* Pin 2  selected */
    GPIO_Pin_3     = ((uint32_t)0x00000008),  /* Pin 3  selected */
    GPIO_Pin_4     = ((uint32_t)0x00000010),  /* Pin 4  selected */
    GPIO_Pin_5     = ((uint32_t)0x00000020),  /* Pin 5  selected */
    GPIO_Pin_6     = ((uint32_t)0x00000040),  /* Pin 6  selected */
    GPIO_Pin_7     = ((uint32_t)0x00000080),  /* Pin 7  selected */
    GPIO_Pin_8     = ((uint32_t)0x00000100),  /* Pin 8  selected */
    GPIO_Pin_9     = ((uint32_t)0x00000200),  /* Pin 9  selected */
    GPIO_Pin_10    = ((uint32_t)0x00000400),  /* Pin 10 selected */
    GPIO_Pin_11    = ((uint32_t)0x00000800),  /* Pin 11 selected */
    GPIO_Pin_12    = ((uint32_t)0x00001000),  /* Pin 12 selected */
    GPIO_Pin_13    = ((uint32_t)0x00002000),  /* Pin 13 selected */
    GPIO_Pin_14    = ((uint32_t)0x00004000),  /* Pin 14 selected */
    GPIO_Pin_15    = ((uint32_t)0x00008000),  /* Pin 15 selected */
    GPIO_Pin_16    = ((uint32_t)0x00010000),  /* Pin 16 selected */
    GPIO_Pin_17    = ((uint32_t)0x00020000),  /* Pin 17 selected */
    GPIO_Pin_18    = ((uint32_t)0x00040000),  /* Pin 18 selected */
    GPIO_Pin_19    = ((uint32_t)0x00080000),  /* Pin 19 selected */
    GPIO_Pin_20    = ((uint32_t)0x00100000),  /* Pin 20 selected */
    GPIO_Pin_21    = ((uint32_t)0x00200000),  /* Pin 21 selected */
    GPIO_Pin_22    = ((uint32_t)0x00400000),  /* Pin 22 selected */
    GPIO_Pin_23    = ((uint32_t)0x00800000),  /* Pin 23 selected */
    GPIO_Pin_24    = ((uint32_t)0x01000000),  /* Pin 24 selected */
    GPIO_Pin_25    = ((uint32_t)0x02000000),  /* Pin 25 selected */
    GPIO_Pin_26    = ((uint32_t)0x04000000),  /* Pin 26 selected */
    GPIO_Pin_27    = ((uint32_t)0x08000000),  /* Pin 27 selected */
    GPIO_Pin_28    = ((uint32_t)0x10000000),  /* Pin 28 selected */
    GPIO_Pin_29    = ((uint32_t)0x20000000),  /* Pin 29 selected */
    GPIO_Pin_30    = ((uint32_t)0x40000000),  /* Pin 30 selected */
    GPIO_Pin_31    = ((uint32_t)0x80000000),  /* Pin 31 selected */

    GPIO_Pin_All   = ((uint32_t)0xFFFFFFFF),  /* All pins selected */
};

struct jz_gpio_irq_def
{
    void    *irq_arg[32];
    void   (*irq_cb[32])   (void *param);
};

void    gpio_set_func               (enum gpio_port port, uint32_t pins, enum gpio_function func);

void    gpio_set_value              (enum gpio_port port, enum gpio_pin pin,int value);
int     gpio_get_value              (enum gpio_port port, enum gpio_pin pin);
int     gpio_get_flag               (enum gpio_port port, enum gpio_pin pin);
void    gpio_clear_flag             (enum gpio_port port, enum gpio_pin pin);
void    gpio_direction_input        (enum gpio_port port, enum gpio_pin pin);
void    gpio_direction_output       (enum gpio_port port, enum gpio_pin pin,int value);
void    gpio_enable_pull            (enum gpio_port port, enum gpio_pin pin);
void    gpio_disable_pull           (enum gpio_port port, enum gpio_pin pin);
void    gpio_as_irq_high_level      (enum gpio_port port, enum gpio_pin pin);
void    gpio_as_irq_rise_edge       (enum gpio_port port, enum gpio_pin pin);
void    gpio_as_irq_fall_edge       (enum gpio_port port, enum gpio_pin pin);
void    gpio_ack_irq                (enum gpio_port port, enum gpio_pin pin);
void    gpio_set_irq_callback(enum gpio_port port, enum gpio_pin pin, void (*irq_cb)(void *),void *irq_arg);
void    gpio_mask_irq(enum gpio_port port,  enum gpio_pin pin);
void    gpio_unmask_irq(enum gpio_port port,  enum gpio_pin pin);

#endif /* _BOARD_GPIO_H_ */
