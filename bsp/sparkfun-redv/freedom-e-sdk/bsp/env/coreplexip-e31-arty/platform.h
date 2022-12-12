// See LICENSE for license details.

#ifndef _SIFIVE_PLATFORM_H
#define _SIFIVE_PLATFORM_H

// Some things missing from the official encoding.h

#if __riscv_xlen == 32
#define MCAUSE_INT         0x80000000UL
#define MCAUSE_CAUSE       0x7FFFFFFFUL
#else
#define MCAUSE_INT         0x8000000000000000UL
#define MCAUSE_CAUSE       0x7FFFFFFFFFFFFFFFUL
#endif

#define IRQ_M_LOCAL        16
#define MIP_MLIP(x)        (1 << (IRQ_M_LOCAL + x))

#include "sifive/const.h"
#include "sifive/devices/clint.h"
#include "sifive/devices/gpio.h"
#include "sifive/devices/plic.h"
#include "sifive/devices/pwm.h"
#include "sifive/devices/spi.h"
#include "sifive/devices/uart.h"

/****************************************************************************
 * Platform definitions
 *****************************************************************************/

// Memory map
#define CLINT_CTRL_ADDR _AC(0x02000000,UL)
#define GPIO_CTRL_ADDR _AC(0x20002000,UL)
#define PLIC_CTRL_ADDR _AC(0x0C000000,UL)
#define PWM0_CTRL_ADDR _AC(0x20005000,UL)
#define RAM_MEM_ADDR _AC(0x80000000,UL)
#define RAM_MEM_SIZE _AC(0x10000,UL)
#define SPI0_CTRL_ADDR _AC(0x20004000,UL)
#define SPI0_MEM_ADDR _AC(0x40000000,UL)
#define SPI0_MEM_SIZE _AC(0x20000000,UL)
#define TESTBENCH_MEM_ADDR _AC(0x20000000,UL)
#define TESTBENCH_MEM_SIZE _AC(0x10000000,UL)
#define TRAPVEC_TABLE_CTRL_ADDR _AC(0x00001010,UL)
#define UART0_CTRL_ADDR _AC(0x20000000,UL)

// IOF masks

// Interrupt numbers
#define RESERVED_INT_BASE 0
#define UART0_INT_BASE 1
#define EXTERNAL_INT_BASE 2
#define SPI0_INT_BASE 6
#define GPIO_INT_BASE 7
#define PWM0_INT_BASE 23

// Helper functions
#define _REG64(p, i) (*(volatile uint64_t *)((p) + (i)))
#define _REG32(p, i) (*(volatile uint32_t *)((p) + (i)))
#define _REG16(p, i) (*(volatile uint16_t *)((p) + (i)))
// Bulk set bits in `reg` to either 0 or 1.
// E.g. SET_BITS(MY_REG, 0x00000007, 0) would generate MY_REG &= ~0x7
// E.g. SET_BITS(MY_REG, 0x00000007, 1) would generate MY_REG |= 0x7
#define SET_BITS(reg, mask, value) if ((value) == 0) { (reg) &= ~(mask); } else { (reg) |= (mask); }
#define CLINT_REG(offset) _REG32(CLINT_CTRL_ADDR, offset)
#define GPIO_REG(offset) _REG32(GPIO_CTRL_ADDR, offset)
#define PLIC_REG(offset) _REG32(PLIC_CTRL_ADDR, offset)
#define PWM0_REG(offset) _REG32(PWM0_CTRL_ADDR, offset)
#define SPI0_REG(offset) _REG32(SPI0_CTRL_ADDR, offset)
#define TRAPVEC_TABLE_REG(offset) _REG32(TRAPVEC_TABLE_CTRL_ADDR, offset)
#define UART0_REG(offset) _REG32(UART0_CTRL_ADDR, offset)
#define CLINT_REG64(offset) _REG64(CLINT_CTRL_ADDR, offset)
#define GPIO_REG64(offset) _REG64(GPIO_CTRL_ADDR, offset)
#define PLIC_REG64(offset) _REG64(PLIC_CTRL_ADDR, offset)
#define PWM0_REG64(offset) _REG64(PWM0_CTRL_ADDR, offset)
#define SPI0_REG64(offset) _REG64(SPI0_CTRL_ADDR, offset)
#define TRAPVEC_TABLE_REG64(offset) _REG64(TRAPVEC_TABLE_CTRL_ADDR, offset)
#define UART0_REG64(offset) _REG64(UART0_CTRL_ADDR, offset)

// Misc

#define NUM_GPIO 16

#define PLIC_NUM_INTERRUPTS 28
#define PLIC_NUM_PRIORITIES 7

#define HAS_BOARD_BUTTONS

#include "coreplexip-arty.h"

#endif /* _SIFIVE_PLATFORM_H */
