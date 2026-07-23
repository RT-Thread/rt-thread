/*
File Name    : yc3121.h
Author       : Yichip
Version      : V1.0
Date         : 2018/03/27
Description  : Register and hardware information.
*/

#ifndef __YC3121_H__
#define __YC3121_H__

#include "type.h"
#include "system.h"
#include <string.h>
#include "rom_api.h"

#define NO_BT           0
#define EXIST_BT        1
#define NO_XTAL         2

#define VERSIONS		EXIST_BT

#define M0_FPGA     1
#define POS_FPGA    2
#define POS_CHIP    3

#define HARDWAER	POS_CHIP

#if (HARDWAER == M0_FPGA)
    #define CPU_MHZ        (24*1000000)
#elif (HARDWAER == POS_CHIP)
    #define CRYSTAL_CLK (192*1000000)
    #define CPU_MHZ     ((CRYSTAL_CLK)/((SYSCTRL_HCLK_CON&0x0f)+2))
#endif

#define noinline __attribute__((noinline))

#define IPC_HOLD_BT				   *(volatile byte*)0xC4FEF
#define IPC_RX_START_ADDR		 	(volatile byte*)0xc4ff0
#define IPC_RX_END_ADDR				(volatile byte*)0xc4ff2
#define IPC_RX_READ_PTR				(volatile byte*)0xc4ff4
#define IPC_RX_WRITE_PTR			(volatile byte*)0xc4ff6
#define IPC_TX_START_ADDR			(volatile byte*)0xc4ff8
#define IPC_TX_END_ADDR				(volatile byte*)0xc4ffa
#define IPC_TX_READ_PTR				(volatile byte*)0xc4ffc
#define IPC_TX_WRITE_PTR			(volatile byte*)0xc4ffe

#define BT_REV             *(volatile byte*)0xc8000
#define BT_STEP            *(volatile byte*)0xc8001
#define BT_PC              *(volatile word*)0xc800e
#define BT_RESET           *(volatile byte*)0xc8010
#define BT_UCODE_HI        *(volatile byte*)0xc8022
#define BT_UCODE_CTRL      *(volatile byte*)0xc8023
#define BT_UCODE_LO        *(volatile byte*)0xc8024
#define BT_UCODE_DATA      *(volatile byte*)0xc8025
#define BT_RHALFSLOT_LOW   *(volatile byte*)0xc8040
#define BT_CONTRU          *(volatile byte*)0xc812c
#define BT_CONTWU          *(volatile byte*)0xc812e
#define BT_CONFIG          *(volatile byte*)0xc8043
#define BT_CLKPLL_EN       *(volatile byte*)0xc8905
#define BT_CHGPUMP_EN      *(volatile byte*)0xc8973
#define WAKEUP_BT          *(volatile byte*)0xF853C

#define BT_INIT_FLAG       7
#define WAKEUP_BT_FLAG     2

//register base address

#define WDT_BASEADDR        0xf0000
#define SCI7816_BASEADDR    0xf0400

#define TIMER_BASEADDR      0xf0c00
#define SM4_BASEADDR        0xf5200
#define RSA_BASEADDR        0xf5800
#define USB_BASEADDR        0xf6000
#define DES_BASEADDR        0xf8000
#define CRC_BASEADDR        0xf8200
#define AES_BASEADDR        0xf8300
#define LPM_BASEADDR        0xf8400
#define SYSCTRL_BASEADDR    0xf8500
#define SECURE_BASEADDR     0xf8540
#define CLKGEN_BASEADDR     0xf8560
#define MPU_BASEADDR        0xf8580
#define SHA_BASEADDR        0xf8600
#define GPIO_BASEADDR       0xf8700
#define DMA_BASEADDR        0xf8800
#define QSPI_BASEADDR       DMA_BASEADDR
#define ISO7811_BASEADDR    0xf8f00

#define WD_CONFIG         *(volatile int*)(WDT_BASEADDR + 0x00)
#define WD_STATUS         *(volatile int*)(WDT_BASEADDR + 0x04)
#define WD_KICK           *(volatile int*)(WDT_BASEADDR + 0x08)
#define WD_CLEAR          *(volatile int*)(WDT_BASEADDR + 0x0c)

#define SCI7816_MODE      *(volatile int*)(SCI7816_BASEADDR + 0x00)
#define SCI7816_CTRL      *(volatile int*)(SCI7816_BASEADDR + 0x08)
#define SCI7816_STAT      *(volatile int*)(SCI7816_BASEADDR + 0x0c)
#define SCI7816_INT       *(volatile int*)(SCI7816_BASEADDR + 0x10)
#define SCI7816_DATA      *(volatile int*)(SCI7816_BASEADDR + 0x20)
#define SCI7816_ETU       *(volatile int*)(SCI7816_BASEADDR + 0x28)
#define SCI7816_BGT       *(volatile int*)(SCI7816_BASEADDR + 0x2c)
#define SCI7816_CWT       *(volatile int*)(SCI7816_BASEADDR + 0x30)
#define SCI7816_EDC       *(volatile int*)(SCI7816_BASEADDR + 0x34)

#define PWM_TOTAL				9

#define TIM_PCNT(x)     *(volatile int*)(TIMER_BASEADDR + x*8)
#define TIM_NCNT(x)     *(volatile int*)(TIMER_BASEADDR + 4 + x*8)
#define TIM_CTRL        *(volatile int*)(TIMER_BASEADDR + PWM_TOTAL*8)
#define TIM_CTRL1       *(volatile int*)(TIMER_BASEADDR + PWM_TOTAL*8 + 4)
#define TIM_CNT(x)      *(volatile int*)(TIMER_BASEADDR + PWM_TOTAL*8 + (PWM_TOTAL*4 + 31)/32*4 + x*4)

#define SHA_DATA(x)     *(volatile int*)(SHA_BASEADDR + 0x00 + x*4)
#define SHA_BDATA(x)    *(volatile uint8_t*)(SHA_BASEADDR + 0x00 + x)
#define SHA_RESULT(x)   *(volatile int*)(SHA_BASEADDR + 0x80 + x*4)
#define SHA_CTRL        *(volatile int*)(SHA_BASEADDR + 0xc0)

#define SYSCTRL_PRIV_CTRL    *(volatile int*)(SYSCTRL_BASEADDR + 0x0)
#define SYSCTRL_STATUS       *(volatile int*)(SYSCTRL_BASEADDR + 0x4)
#define OTP_ADDR             *(volatile short*)(SYSCTRL_BASEADDR + 0x8)
#define OTP_CTRL             *(volatile short*)(SYSCTRL_BASEADDR + 0xa)
#define OTP_RDATA            *(volatile byte*)(SYSCTRL_BASEADDR + 0xc)
#define OTP_STATUS           *(volatile int*)(SYSCTRL_BASEADDR + 0xc)

#define SYSCTRL_LPM_RDATA    *(volatile int*)(SYSCTRL_BASEADDR + 0x10)
#define SYSCTRL_LPM_SCB      *(volatile int*)(SYSCTRL_BASEADDR + 0x14)
#define SYSCTRL_HWCTRL(x)    *(volatile uint8_t*)(SYSCTRL_BASEADDR + 0x18 + x)
#define SYSCTRL_RNG_CTRL     *(volatile int*)(SYSCTRL_BASEADDR + 0x28)
#define SYSCTRL_RNG_DATAB(x) *(volatile uint8_t*)(SYSCTRL_BASEADDR + 0x2c+x)

#define SYSCTRL_RNG_DATA(x)  *(volatile int*)(SYSCTRL_BASEADDR + 0x2c+x*4)

#define SYSCTRL_ROM_SWITCH   *(volatile uint8_t*)(SYSCTRL_BASEADDR + 0x3c)
#define SYSCTRL_LPM_STATUS   *(volatile byte *)(SYSCTRL_BASEADDR + 0x3d)
#define SYSCTRL_OTPN_ADDR    *(volatile uint8_t*)(SYSCTRL_BASEADDR + 0x3e)
#define SYSCTRL_OTPU_ADDR    *(volatile uint8_t*)(SYSCTRL_BASEADDR + 0x3f)

#define SECURE_CTRL          *(volatile int*)(SECURE_BASEADDR + 0x0)
#define SECURE_STATUS        *(volatile int*)(SECURE_BASEADDR + 0x4)
#define SECURE_MEDCON        *(volatile int*)(SECURE_BASEADDR + 0x8)
#define SECURE_RAMKEY        *(volatile int*)(SECURE_BASEADDR + 0xc)

#define SYSCTRL_HCLK_CON     *(volatile int*)(CLKGEN_BASEADDR + 0x00)
#define SYSCTRL_RSACLK       *(volatile int*)(CLKGEN_BASEADDR + 0x08)
#define SYSCTRL_CLK_CLS      *(volatile int*)(CLKGEN_BASEADDR + 0x0c)
#define SYSCTRL_RST_EN       *(volatile int*)(CLKGEN_BASEADDR + 0x14)
#define SYSCTRL_RST_TYPE     *(volatile int*)(CLKGEN_BASEADDR + 0x18)
#define SYSCTRL_RESET        *(volatile int*)(CLKGEN_BASEADDR + 0x1c)

#define MPUCTRL_ID           *(volatile int*)(MPU_BASEADDR + 0x00)
#define MPUCTRL_CTRL         *(volatile int*)(MPU_BASEADDR + 0x04)
#define MPUCTRL_FSR          *(volatile int*)(MPU_BASEADDR + 0x0c)
#define MPUCTRL_FAR          *(volatile int*)(MPU_BASEADDR + 0x10)

#define MPUCTRL_PROTECTION      *(volatile int*)(MPU_BASEADDR + 0x14)
#define MPUCTRL_USER_START      *(volatile int*)(MPU_BASEADDR + 0x18)
#define MPUCTRL_REGION_BASE(x)	*(volatile int*)(MPU_BASEADDR + 0x40 + x*4)
#define MPUCTRL_REGION_LIMIT(x)	*(volatile int*)(MPU_BASEADDR + 0x60 + x*4)

#define LPM_CTRL         (volatile int*)(LPM_BASEADDR + 0x00)
#define LPM_SENSOR       (volatile int*)(LPM_BASEADDR + 0x04)
#define LPM_WKUP_TIMER   (volatile int*)(LPM_BASEADDR + 0x08)
#define LPM_SECMAX       (volatile int*)(LPM_BASEADDR+0x0c)
#define LPM_GPIO_WKUP    (volatile int*)(LPM_BASEADDR + 0x10)
#define LPM_GPIO_WKHI    (volatile int*)(LPM_BASEADDR + 0x14)
#define LPM_SLEEP        (volatile int*)(LPM_BASEADDR + 0x20)
#define LPM_CLR_INTR     (volatile int*)(LPM_BASEADDR + 0x24)
#define LPM_STATUS       (volatile int*)(LPM_BASEADDR + 0x78)
#define LPM_RTC_CNT      (volatile int*)(LPM_BASEADDR + 0x7c)
#define LPM_KEY(x)       (volatile int*)(LPM_BASEADDR + 0x80 + x*4)

#define GPIO_GROUP_NUM			3
#define GPIO_PIN_NUM			  16

#define GPIO_CONFIG(x)         *((volatile uint8_t*)(GPIO_BASEADDR + x))
#define GPIO_INTR_EN(groupx)   *((volatile uint16_t*)(GPIO_BASEADDR+GPIO_GROUP_NUM*GPIO_PIN_NUM) + groupx)
#define GPIO_TRIG_MODE(groupx) *((volatile uint16_t*)(GPIO_BASEADDR+(GPIO_GROUP_NUM*GPIO_PIN_NUM) +GPIO_GROUP_NUM*2) +groupx)
#define GPIO_IN(groupx)        *((volatile uint16_t*)(GPIO_BASEADDR+(GPIO_GROUP_NUM*GPIO_PIN_NUM) +GPIO_GROUP_NUM*4)+groupx)

#define DMA_SRC_ADDR(x)    *(volatile int*)(DMA_BASEADDR + 0x00 + x*0x100)
#define DMA_DEST_ADDR(x)   *(volatile int*)(DMA_BASEADDR + 0x04 + x*0x100)
#define DMA_LEN(x)         *(volatile int*)(DMA_BASEADDR + 0x08 + x*0x100)
#define DMA_CONFIG(x)      *(volatile uint8_t*)(DMA_BASEADDR + 0x0c + x*0x100)
#define DMA_START(x)       *(volatile uint8_t*)(DMA_BASEADDR + 0x0f + x*0x100)
#define DMA_STATUS(x)      *(volatile int*)(DMA_BASEADDR + 0x10 + x*0x100)
#define DMA_RPTR(x)        *(volatile int*)(DMA_BASEADDR + 0x14 + x*0x100)
#define DMA_WPTR(x)        *(volatile int*)(DMA_BASEADDR + 0x18 + x*0x100)

#define QSPI_CTRL         *(volatile int*)(QSPI_BASEADDR + 0x1c)
#define QAES_ADDRKEY      *(volatile int*)(QSPI_BASEADDR + 0x20)
#define QAES_CTRL         *(volatile int*)(QSPI_BASEADDR + 0x24)
#define QAES_RAND(x)      *(volatile int*)(QSPI_BASEADDR + 0x28 + x*4)
#define QAES_KEY(x)       *(volatile int*)(QSPI_BASEADDR + 0x30 + x*4)
#define QAES_DATA(x)      *(volatile int*)(QSPI_BASEADDR + 0x40 + x*4)
#define QAES_KEYB(x)      *(volatile byte*)(QSPI_BASEADDR + 0x30 + x)
#define SPID0_CTRL        *(volatile int*)0xf891c
#define SPID1_CTRL        *(volatile int*)0xf8a1c
#define UART0_CTRL        *(volatile int*)0xf8b1c
#define UART0_INTR        *(volatile int*)0xf8b20
#define UART0_RDATA       *(volatile byte*)0xf8b24
#define UART0_STATUS      *(volatile int*)0xf8b28
#define UART1_CTRL        *(volatile int*)0xf8c1c
#define UART1_INTR        *(volatile int*)0xf8c20
#define UART1_RDATA       *(volatile byte*)0xf8c24
#define UART1_STATUS      *(volatile int*)0xf8c28
#define IICD_DELAY        *(volatile int*)0xf8d1c
#define IICD_CTRL         *(volatile int*)0xf8d20

#define USB_CONFIG        *(volatile byte*)USB_BASEADDR
#define USB_INT_MASK(x)   *(volatile byte*)(USB_BASEADDR + 1 + x)
#define USB_ADDR          *(volatile byte*)(USB_BASEADDR + 4)
#define USB_TRG           *(volatile byte*)(USB_BASEADDR + 0x10)
#define USB_STALL         *(volatile byte*)(USB_BASEADDR + 0x11)
#define USB_CLEAR         *(volatile byte*)(USB_BASEADDR + 0x12)
#define USB_EP(x)         *(volatile byte*)(USB_BASEADDR + 0x18 + x)
#define USB_EP_LEN(x)     *(volatile byte*)(USB_BASEADDR + 0x20 + x)
#define USB_STATUS        *(volatile byte*)(USB_BASEADDR + 0x26)
#define USB_FIFO_EMPTY    *(volatile byte*)(USB_BASEADDR + 0x27)
#define USB_FIFO_FULL     *(volatile byte*)(USB_BASEADDR + 0x28)


#define AES_CNTRL_REG     *((volatile uint32_t *)(AES_BASEADDR))
#define AES_DATA_REG0      ((volatile uint32_t *)(AES_BASEADDR+0x10))
#define AES_DATA_REG1      ((volatile uint32_t *)(AES_BASEADDR+0x14))
#define AES_DATA_REG2      ((volatile uint32_t *)(AES_BASEADDR+0x18))
#define AES_DATA_REG3      ((volatile uint32_t *)(AES_BASEADDR+0x1C))
#define AES_KEY_REG0       ((volatile uint32_t *)(AES_BASEADDR+0x20))
#define AES_KEY_REG1       ((volatile uint32_t *)(AES_BASEADDR+0x24))
#define AES_KEY_REG2       ((volatile uint32_t *)(AES_BASEADDR+0x28))
#define AES_KEY_REG3       ((volatile uint32_t *)(AES_BASEADDR+0x2C))
#define AES_KEY_REG4       ((volatile uint32_t *)(AES_BASEADDR+0x30))
#define AES_KEY_REG5       ((volatile uint32_t *)(AES_BASEADDR+0x34))
#define AES_KEY_REG6       ((volatile uint32_t *)(AES_BASEADDR+0x38))
#define AES_KEY_REG7       ((volatile uint32_t *)(AES_BASEADDR+0x3C))
#define AES_RAND_REG0      ((volatile uint32_t *)(AES_BASEADDR+0x40))
#define AES_RAND_REG1      ((volatile uint32_t *)(AES_BASEADDR+0x44))
#define AES_FKEY_REG0      ((volatile uint32_t *)(AES_BASEADDR+0x50))

#define AES_DATAB(x)      *(volatile byte*)(AES_BASEADDR + 0x10 + (x))
#define AES_KEYB(x)       *(volatile byte*)(AES_BASEADDR + 0x20 + (x))

#define	DESCNTRL_REG      *((volatile uint32_t *)(DES_BASEADDR+0x00))
#define	DESRAND_REG        ((volatile uint32_t *)(DES_BASEADDR+0x0c))
#define	DESFAKE_KEY        ((volatile uint32_t *)(DES_BASEADDR+0x10))
#define	DESIV_REG          ((volatile uint32_t *)(DES_BASEADDR+0x18))
#define	DESDATA_REG        ((volatile uint32_t *)(DES_BASEADDR+0x20))
#define	DESKEY1_REG        ((volatile uint32_t *)(DES_BASEADDR+0x28))
#define	DESKEY2_REG        ((volatile uint32_t *)(DES_BASEADDR+0x30))
#define	DESKEY3_REG        ((volatile uint32_t *)(DES_BASEADDR+0x38))
#define	DES_KEYB(x)       *(volatile byte *)(DES_BASEADDR+0x28 + x)
#define	DES_DATAB(x)      *(volatile byte *)(DES_BASEADDR+0x20 + x)

#define SM4_REG0         (*(volatile uint32_t *)(SM4_BASEADDR + 0x0))
#define SM4_REG1         (*(volatile uint32_t *)(SM4_BASEADDR + 0x4))
#define SM4_IER          (*(volatile uint32_t *)(SM4_BASEADDR + 0x8))
#define SM4_MR           (*(volatile uint32_t *)(SM4_BASEADDR + 0xc))
#define SM4_KEY0         ((volatile uint32_t *)(SM4_BASEADDR + 0x10))
#define SM4_KEY1         ((volatile uint32_t *)(SM4_BASEADDR + 0x14))
#define SM4_KEY2         ((volatile uint32_t *)(SM4_BASEADDR + 0x18))
#define SM4_KEY3         ((volatile uint32_t *)(SM4_BASEADDR + 0x1c))
#define SM4_IV0          ((volatile uint32_t *)(SM4_BASEADDR + 0x20))
#define SM4_IV1          ((volatile uint32_t *)(SM4_BASEADDR + 0x24))
#define SM4_IV2          ((volatile uint32_t *)(SM4_BASEADDR + 0x28))
#define SM4_IV3          ((volatile uint32_t *)(SM4_BASEADDR + 0x2c))
#define SM4_DATA0        ((volatile uint32_t *)(SM4_BASEADDR + 0x30))
#define SM4_DATA1        ((volatile uint32_t *)(SM4_BASEADDR + 0x34))
#define SM4_DATA2        ((volatile uint32_t *)(SM4_BASEADDR + 0x38))
#define SM4_DATA3        ((volatile uint32_t *)(SM4_BASEADDR + 0x3c))


#define RECR             (*((volatile uint32_t *)(RSA_BASEADDR+0x00)))
#define RESR             (*((volatile uint32_t *)(RSA_BASEADDR+0x04)))
#define REFR             (*((volatile uint32_t *)(RSA_BASEADDR+0x08)))
#define RESCR            (*((volatile uint32_t *)(RSA_BASEADDR+0x0c)))
#define REDQR            (*((volatile uint32_t *)(RSA_BASEADDR+0x10)))
#define REINT            (*((volatile uint32_t *)(RSA_BASEADDR+0x14)))
#define RECFR            (*((volatile uint32_t *)(RSA_BASEADDR+0x18)))
#define REBKR            ((volatile uint32_t *)(RSA_BASEADDR+0x1c))
#define REDRR            (*((volatile uint32_t *)(RSA_BASEADDR+0x24)))
#define REDAR            ((volatile uint32_t *)(RSA_BASEADDR+0x100))
#define REDAR1           ((volatile uint32_t *)(RSA_BASEADDR+0x120))
#define REDAR2           ((volatile uint32_t *)(RSA_BASEADDR+0x140))
#define REDAR3           ((volatile uint32_t *)(RSA_BASEADDR+0x160))
#define REDXR            ((volatile uint32_t *)(RSA_BASEADDR+0x200))
#define REDXR1           ((volatile uint32_t *)(RSA_BASEADDR+0x220))
#define REDXR2           ((volatile uint32_t *)(RSA_BASEADDR+0x240))
#define REDXR3           ((volatile uint32_t *)(RSA_BASEADDR+0x260))
#define REDYR            ((volatile uint32_t *)(RSA_BASEADDR+0x280))
#define REDYR1           ((volatile uint32_t *)(RSA_BASEADDR+0x2a0))
#define REDYR2           ((volatile uint32_t *)(RSA_BASEADDR+0x2c0))
#define REDYR3           ((volatile uint32_t *)(RSA_BASEADDR+0x2e0))
#define REDBR            ((volatile uint32_t *)(RSA_BASEADDR+0x300))
#define REDBR1           ((volatile uint32_t *)(RSA_BASEADDR+0x320))
#define REDBR2           ((volatile uint32_t *)(RSA_BASEADDR+0x340))
#define REDBR3           ((volatile uint32_t *)(RSA_BASEADDR+0x360))
#define REDBRH           ((volatile uint32_t *)(RSA_BASEADDR+0x380))
#define REDCR            ((volatile uint32_t *)(RSA_BASEADDR+0x500))
#define REDCR1           ((volatile uint32_t *)(RSA_BASEADDR+0x520))
#define REDCR2           ((volatile uint32_t *)(RSA_BASEADDR+0x540))
#define REDCR3           ((volatile uint32_t *)(RSA_BASEADDR+0x560))
#define REDCRH           ((volatile uint32_t *)(RSA_BASEADDR+0x580))
#define REDUR            ((volatile uint32_t *)(RSA_BASEADDR+0x600))
#define REDVR            ((volatile uint32_t *)(RSA_BASEADDR+0x680))
#define REDVR2           ((volatile uint32_t *)(RSA_BASEADDR+0x6c0))
#define REDPR            ((volatile uint32_t *)(RSA_BASEADDR+0x700))
#define REDPR1           ((volatile uint32_t *)(RSA_BASEADDR+0x720))
#define REDPR2           ((volatile uint32_t *)(RSA_BASEADDR+0x740))
#define REDPR3           ((volatile uint32_t *)(RSA_BASEADDR+0x760))
#define REDPRH           ((volatile uint32_t *)(RSA_BASEADDR+0x780))

#define ISO7811_BASE_ADDR_T1   *((volatile uint32_t *)(ISO7811_BASEADDR+0x00))
#define ISO7811_BASE_ADDR_T2   *((volatile uint32_t *)(ISO7811_BASEADDR+0x04))
#define ISO7811_BASE_ADDR_T3   *((volatile uint32_t *)(ISO7811_BASEADDR+0x08))
#define ISO7811_CTRL           *((volatile uint32_t *)(ISO7811_BASEADDR+0x0C))

#define ISO7811_T1_PEAK_VALUE_CFG   *((volatile uint32_t *)(ISO7811_BASEADDR+0x10))
#define ISO7811_T1_PEAK_WIDTH_CFG   *((volatile uint32_t *)(ISO7811_BASEADDR+0x14))
#define ISO7811_T1_PULSE_WIDTH_CFG  *((volatile uint32_t *)(ISO7811_BASEADDR+0x18))
#define ISO7811_T1_AGC_CFG          *((volatile uint32_t *)(ISO7811_BASEADDR+0x1c))

#define ISO7811_T2_PEAK_VALUE_CFG   *((volatile uint32_t *)(ISO7811_BASEADDR+0x20))
#define ISO7811_T2_PEAK_WIDTH_CFG   *((volatile uint32_t *)(ISO7811_BASEADDR+0x24))
#define ISO7811_T2_PULSE_WIDTH_CFG  *((volatile uint32_t *)(ISO7811_BASEADDR+0x28))
#define ISO7811_T2_AGC_CFG          *((volatile uint32_t *)(ISO7811_BASEADDR+0x2c))

#define ISO7811_T3_PEAK_VALUE_CFG   *((volatile uint32_t *)(ISO7811_BASEADDR+0x30))
#define ISO7811_T3_PEAK_WIDTH_CFG   *((volatile uint32_t *)(ISO7811_BASEADDR+0x34))
#define ISO7811_T3_PULSE_WIDTH_CFG  *((volatile uint32_t *)(ISO7811_BASEADDR+0x38))
#define ISO7811_T3_AGC_CFG          *((volatile uint32_t *)(ISO7811_BASEADDR+0x3c))

#define ISO7811_STATUS              *((volatile uint32_t *)(ISO7811_BASEADDR+0x40))
#define ISO7811_CHAR_NUM            *((volatile uint32_t *)(ISO7811_BASEADDR+0x44))
#define ISO7811_INTERFER_CHAR_NUM   *((volatile uint32_t *)(ISO7811_BASEADDR+0x48))
#define ISO7811_DC_EST              *((volatile uint32_t *)(ISO7811_BASEADDR+0x4c))
#define ISO7811_INTF_PEAK           *((volatile uint32_t *)(ISO7811_BASEADDR+0x50))
#define ISO7811_AGC_PEAK_VAL        *((volatile uint32_t *)(ISO7811_BASEADDR +0x54))

#define SYST_CSR           *(volatile int*)0xE000E010
#define SYST_RVR           *(volatile int*)0xE000E014
#define SYST_CVR           *(volatile int*)0xE000E018

#define TRACE_FIFO         *(volatile int*)0xe0002020
#define NVIC_ISER          *(volatile int*)0xe000e100
#define NVIC_ICER          *(volatile int*)0xe000e180
#define NVIC_ISPR          *(volatile int*)0xe000e200
#define NVIC_ICPR          *(volatile int*)0xe000e280

#define CRC_RESULT_REG     *(volatile uint32_t *)(CRC_BASEADDR+0X04)
#define CRC_MASK_REG       *(volatile uint32_t *)(CRC_BASEADDR+0X08)
#define CRC_DATAB_REG      *(volatile byte *)(CRC_BASEADDR+0X80)
#define CRC_DATAS_REG      *(volatile short int *)(CRC_BASEADDR+0X80)
#define CRC_DATA_REG       *(volatile int *)(CRC_BASEADDR+0X80)

#define ADC_CTRL0 *(volatile uint8_t*)0xC8970
#define ADC_CTRL1	*(volatile uint8_t*)0xC8971
#define ADC_CTRL2	*(volatile uint8_t*)0xC8972
#define ADC_CTRL3 *(volatile uint8_t*)0xC8973
#define ADC_ENBLE *(volatile uint8_t*)0xC8906
#define ADC_RDATA *(volatile uint16_t*)0xf850e

/* SysTick registers */
/* SysTick control & status */
#define SYSTICK_CSR     ((volatile unsigned int *)0xE000E010)
/* SysTick Reload value */
#define SYSTICK_RVR     ((volatile unsigned int *)0xE000E014)
/* SysTick Current value */
#define SYSTICK_CVR     ((volatile unsigned int *)0xE000E018)
/* SysTick CSR register bits */
#define SYSTICK_CSR_COUNTFLAG     16
#define SYSTICK_CSR_CLKSOURCE     2
#define SYSTICK_CSR_TICKINT       1
#define SYSTICK_CSR_ENABLE        0

//================ bit definitions ====================
#define OTBIT_DIN                       1<<0
#define OTBIT_DLE                       1<<1
#define OTBIT_CEB                       1<<2
#define OTBIT_RSTB                      1<<3
#define OTBIT_CLE                       1<<4
#define OTBIT_PGMEN                     1<<5
#define OTBIT_PGMVFY                    1<<6
#define OTBIT_READEN                    1<<7
#define OTBIT_VPPEN                     1<<8
#define OTBIT_WEB                       1<<9

#define AES_CNTRL_REG_START             0x1

#define AES_CNTRL_KEY_SEL_128           0X00
#define AES_CNTRL_KEY_SEL_192           0X08
#define AES_CNTRL_KEY_SEL_256           0X10

#define AES_CNTRL_ENC                   0X00
#define AES_CNTRL_DEC                   0X02

#define AES_CNTRL_ENABLE_RAND           0X20

#define DMACH_QSPI                    0
#define DMACH_SPID0                   1
#define DMACH_SPID1                   2
#define DMACH_UART0                   3
#define DMACH_UART1                   4
#define DMACH_IICD                    5
#define DMACH_MEMCP                   6

#define DMA_START_BIT                 7
#define DMA_CLR_INTR_BIT              6
#define DMA_RESET_BIT                 5

//==DES==
#define DESCNTRL_REG_START            0x1
#define DESCNTRL_REG_ENCRYPT          0x2
#define DESCNTRL_REG_KEY_SEL          0xc
#define DESCNTRL_REG_DES_MODE         0x10
#define DESCNTRL_REG_OP_MODE          0x60
#define DESCNTRL_REG_RAND_EN          0x80

#define DESCNTRL_REG_ENCRYPT_ENC      0X00
#define DESCNTRL_REG_ENCRYPT_DEC      0X02

#define DESCNTRL_REG_KEY_SEL_DES1     0x00
#define DESCNTRL_REG_KEY_SEL_DES2     0x04
#define DESCNTRL_REG_KEY_SEL_DES3     0x08

#define DESCNTRL_REG_KEY_SEL_TDES2    0x00
#define DESCNTRL_REG_KEY_SEL_TDES3    0x04

#define DESCNTRL_REG_DES_MODE_DES     0X00
#define DESCNTRL_REG_DES_MODE_TDES    0X10

#define DESCNTRL_REG_OP_MODE_ECB      0x00
#define DESCNTRL_REG_OP_MODE_CBC      0x20
//==DES==END==

//==RSA==
//sfr bit
// RECR register
#define RECR_start                    0x01
#define RECR_idle_run                 0x02
#define RECR_bus_crypt_en             0x04
// RESR register
#define RESR_error_flag               0x01
#define RESR_opdata_error             0x02
//REINT register
#define REINT_rsa_int                 0x01
//==RSA==END==

#define CLKCLS_INT      1
#define CLKCLS_SHA      2
#define CLKCLS_CRC      3
#define CLKCLS_TIM      4
#define CLKCLS_WDT      5
#define CLKCLS_USB      6
#define CLKCLS_SPI      7
#define CLKCLS_DES      8
#define CLKCLS_RSA      9
#define CLKCLS_AES      10
#define CLKCLS_GPIO     11
#define CLKCLS_7816     12
#define CLKCLS_BT       13
#define CLKCLS_SM4      14
#define CLKCLS_UART     15
#define CLKCLS_7811     16
#define CLKCLS_ADC7811  17
#define CLKCLS_CP       18

#define INTR_USB     0
#define INTR_IIC     1
#define INTR_QSPI    2
#define INTR_SPI0    3
#define INTR_SPI1    4
#define INTR_UART0   5
#define INTR_UART1   6
#define INTR_MEMCP   7
#define INTR_RSA     8
#define INTR_SCI0    9
#define INTR_SCI1    10
#define INTR_BT      11
#define INTR_GPIO    12
#define INTR_TMR0    13
#define INTR_TMR1    14
#define INTR_TMR2    15
#define INTR_TMR3    16
#define INTR_TMR4    17
#define INTR_TMR5    18
#define INTR_TMR6    19
#define INTR_TMR7    20
#define INTR_TMR8    21
#define INTR_SM4     22
#define INTR_SEC     23
#define INTR_ISO7811 24
#define INTR_TRNG    25
#define INTR_WDT     26

#define SCICFG_TMODE      0
#define SCICFG_BIT_ORDER  1
#define SCICFG_PAD_TYPE   2
#define SCICFG_ETU_SEL    3
#define SCICFG_RETRY      5
#define SCICFG_RETRY_EN   8
#define SCICFG_IO_EN      9
#define SCICFG_BGTEN      10
#define SCICFG_CWTEN      11
#define SCICFG_MCLK_SEL   12
#define SCICFG_MASTER     15
#define SCICFG_EDCEN      16

#define KCFG_COL      3
#define KCFG_MDDBC    8
#define KCFG_MUDBC    12
#define KCFG_UDBC     16
#define KCFG_CYLE     20

#define SM4_CNTRL_ECB 0X00
#define SM4_CNTRL_CBC 0X02
#define SM4_CNTRL_ENC 0X01
#define SM4_CNTRL_DEC 0X00

/* =============== qspi flash command =================== */
#define W25X_WRITE_ENABLE       0x06
#define W25X_WRITE_DISABLE      0x04
#define W25X_READ_STATUS1       0x05
#define W25X_READ_STATUS2       0x35
#define W25X_WRITE_STATUS       0x01
#define W25X_READ_DATA          0x03
#define W25X_FASTREAD_DATA      0x0B
#define W25X_FASTREAD_DUAL1     0x3B
#define W25X_FASTREAD_DUAL2     0xBB

#define W25X_FASTREAD_QUAD1     0x6B
#define W25X_FASTREAD_QUAD2     0xEB
#define W25X_FASTREAD_QUAD3     0xE7

#define W25X_PAGE_PROGRAM       0x02
#define W25X_SECTOR_ERASE       0x20
#define W25X_BLOCK_ERASE32K     0x52
#define W25X_BLOCK_ERASE64K     0xD8
#define W25X_CHIP_ERASE         0xC7
#define W25X_POWER_DOWN         0xB9
#define W25X_RELEASE_POWERDOWN  0xAB
#define W25X_DEVICEID           0xAB
#define W25X_MANUFACT_DEVICEID  0x90
#define W25X_JEDEC_DEVICEID     0x9F

#define QSPICFG_XIPEN       1 << 12
#define QSPICFG_DECEN       1 << 13
#define QSPICFG_DUAL_MODE   1 << 0
#define QSPICFG_QUAD_MODE   2 << 0
#define QSPICFG_MBYTE       1 << 2
#define QSPICFG_MBYTE_CONT  1 << 3
#define QSPICFG_RETRY       3 << 24

#define QCSFT_DUMMY         8
#define QCSFT_CMD           16

#define QSPICFG_MODE_3B     QSPICFG_DUAL_MODE | W25X_FASTREAD_DUAL1 << QCSFT_CMD | 8 << QCSFT_DUMMY
#define QSPICFG_MODE_6B     QSPICFG_QUAD_MODE | W25X_FASTREAD_QUAD1 << QCSFT_CMD | 8 << QCSFT_DUMMY
#define QSPICFG_MODE_BB     QSPICFG_DUAL_MODE | QSPICFG_MBYTE | 0x60 | W25X_FASTREAD_DUAL2 << QCSFT_CMD
#define QSPICFG_MODE_EB     QSPICFG_QUAD_MODE | QSPICFG_MBYTE | 0x60 | W25X_FASTREAD_QUAD2 << QCSFT_CMD | 4 << QCSFT_DUMMY
#define QSPICFG_MODE_E7     QSPICFG_QUAD_MODE | QSPICFG_MBYTE | 0x60 | W25X_FASTREAD_QUAD3 << QCSFT_CMD | 2 << QCSFT_DUMMY

#define LPMCFG_BUCK_EN      1 << 25
#define LPMCFG_TIMER_EN     1 << 28
#define LPMCFG_KRST_EN      1 << 29
#define LPMCFG_SENSOR_DUR   1 << 30

#define LPMSEN_SENSOR_DLY         5
#define LPMSEN_SENSOR_LOCK        7
#define LPMSEN_SHIELD_IO_EN       8
#define LPMSEN_SHIELD_IO_TYPE     12
#define LPMSEN_SHIELD_IO_PU       16
#define LPMSEN_SHIELD_INTERVAL    24
#define LPMSEN_SHIELD_ENABLE      27
#define LPMSEN_SHIELD_PU_DLY      28
#define LPMSEN_SHIELD_A_DLY       30
#define LPMCFG_SENSOR_LOCK        31

//gpio ctrl bit define
#define  GPCFG_INPUT              0
#define  GPCFG_QSPI_NCS           2
#define  GPCFG_QSPI_SCK           3
#define  GPCFG_QSPI_IO0           4
#define  GPCFG_QSPI_IO1           5
#define  GPCFG_QSPI_IO2           6
#define  GPCFG_QSPI_IO3           7
#define  GPCFG_UART0_TXD          8
#define  GPCFG_UART0_RXD          9
#define  GPCFG_UART0_RTS          10
#define  GPCFG_UART0_CTS          11
#define  GPCFG_UART1_TXD          12
#define  GPCFG_UART1_RXD          13
#define  GPCFG_UART1_RTS          14
#define  GPCFG_UART1_CTS          15
#define  GPCFG_PWM_OUT0           16
#define  GPCFG_PWM_OUT1           17
#define  GPCFG_PWM_OUT2           18
#define  GPCFG_PWM_OUT3           19
#define  GPCFG_PWM_OUT4           20
#define  GPCFG_PWM_OUT5           21
#define  GPCFG_PWM_OUT6           22
#define  GPCFG_PWM_OUT7           23
#define  GPCFG_SPID0_NCS          24
#define  GPCFG_SPID0_SCK          25
#define  GPCFG_SPID0_MOSI         26
#define  GPCFG_SPID0_SDIO         27
#define  GPCFG_SPID0_MISO         28
#define  GPCFG_SPID0_NCSIN        29
#define  GPCFG_SPID0_SCKIN        30
#define  GPCFG_PWM_OUT8           31

#define  GPCFG_SPID1_NCS          48
#define  GPCFG_SPID1_SCK          49
#define  GPCFG_SPID1_MOSI         50
#define  GPCFG_SPID1_SDIO         51
#define  GPCFG_SPID1_MISO         52
#define  GPCFG_SPID1_NCSIN        53
#define  GPCFG_SPID1_SCKIN        54
#define  GPCFG_NFC_CLK_OUT        55
#define  GPCFG_SCI7816_IO         56

#define  GPCFG_ICE                57
#define  GPCFG_IIC_SCL            58
#define  GPCFG_IIC_SDA            59
#define  GPCFG_JTAG_SWCLK         60
#define  GPCFG_JTAG_SWDAT         61
#define  GPCFG_OUTPUT_LOW         62
#define  GPCFG_OUTPUT_HIGH        63
#define  GPCFG_PU                 64
#define  GPCFG_PD                 128
#define  GPCFG_ANALOG             192

#define TIM_CTRL_ENABLE         ((uint32_t)0)
#define TIM_CTRL_START_LEVEL    ((uint32_t)1)
#define TIM_CTRL_MODE           ((uint32_t)2)
#define TIM_CTRL_AUTO_RELOAD    ((uint32_t)3)

/* =============== macros =================== */
#define PREFETCH_LINE(addr)	*(volatile int*)addr = 0
#define GETWORD(p)    ((uint16_t)((*(volatile uint8_t *)((uint32_t)p)) |((((uint16_t)(*(volatile uint8_t *)((uint32_t)(p+1))))<<8) & 0xff00)))
static inline void enable_clock(int id)
{
    SYSCTRL_CLK_CLS &= ~(1 << id);
}
static inline void disable_clock(int id)
{
    SYSCTRL_CLK_CLS |= 1 << id;
}
static inline void enable_intr(int intid)
{
    NVIC_ISER |= 1 << intid;
}
static inline void disable_intr(int intid)
{
    NVIC_ICER = 1 << intid;
}

extern void delay(int);//delay(x)=delay(x*110+450ns)
extern void invalidate_icache(int addr, int len);

//#define SCY_FALSE  seesim1()

/*********************************************/
#define SYSCTRL_PCLK_CON		*(volatile int*)0xf7208
#define SYSCTRL_POWERMODE		*(volatile int*)0xf7218

//#define debug
#endif	/* __YC3121_H__ */
