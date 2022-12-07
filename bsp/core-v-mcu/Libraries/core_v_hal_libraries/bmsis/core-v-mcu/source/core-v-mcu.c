/*
 * Copyright 2020 ETH Zurich
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 * Author: Robert Balas (balasr@iis.ee.ethz.ch)
 */

#include <stdint.h>
#include <assert.h>

//#include <FreeRTOS.h>
//#include "FreeRTOSConfig.h"

#include <core_pulp_cluster.h>
#include <core-v-mcu-config.h>

//#include "pmsis/implem/drivers/fc_event/fc_event.h"
#include "hal_fc_event.h"
/* TODO: weird include */
#include "core-v-mcu-properties.h"
#include "hal_irq.h"
#include "hal_soc_eu.h"
#include "hal_apb_soc_ctrl_reg_defs.h"

#include "udma_uart_driver.h"
#include "udma_i2cm_driver.h"
#include "udma_qspi_driver.h"

//#include "../../app/N25Q_16Mb-1Gb_Device_Driver/N25Q.h"
#include "hal_apb_i2cs.h"

#include <rthw.h>
#include <rtthread.h>
//#include "portmacro.h"

#include "hal_udma_ctrl_reg_defs.h"
#include "hal_udma_uart_reg_defs.h"

#include "rtconfig.h"
#define FOR_SIMULATION_TESTING 0


char a[] = "a";
char b[] = "b";

#if (FOR_SIMULATION_TESTING == 1)

typedef struct
{
	volatile uint32_t *rx_saddr;  // 0x00
	volatile uint32_t rx_size;    // 0x04
	volatile uint32_t rx_cfg;     // 0x08
	volatile uint32_t rx_initcfg; // 0x0C
	volatile uint32_t *tx_saddr;  // 0x10
	volatile uint32_t tx_size;    // 0x14
	volatile uint32_t tx_cfg;     // 0x18
	volatile uint32_t tx_initcfg; // 0x1C
	volatile uint32_t cfg_glob;   // 0x20
	volatile uint32_t cfg_ll;     // 0x24
	volatile uint32_t cfg_ur;     // 0x28
	volatile uint32_t cfg_size;   // 0x2C
	volatile uint32_t cfg_filter; // 0x30
	volatile uint32_t vsync_pol;  // 0x34

} camera_struct_t;

void forSimulationTesting(void);
#endif

//FLASH_DEVICE_OBJECT gFlashDeviceObject[N_QSPIM];
uint8_t gQSPIFlashPresentFlg[N_QSPIM] = {0};
uint8_t gMicronFlashDetectedFlg[N_QSPIM] = {0};

/* test some assumptions we make about compiler settings */
static_assert(sizeof(uintptr_t) == 4,
	      "uintptr_t is not 4 bytes. Make sure you are using -mabi=ilp32*");

/* Allocate heap to special section. Note that we have no references in the
 * whole program to this variable (since its just here to allocate space in the
 * section for our heap), so when using LTO it will be removed. We force it to
 * stay with the "used" attribute
 */
__attribute__((section(".heap"), used)) uint8_t ucHeap[configTOTAL_HEAP_SIZE];

/* Inform linker script about .heap section size. Note: GNU ld seems to
 * internally represent integers with the bfd_vma type, that is a type that can
 * contain memory addresses (typdefd to some int type depending on the
 * architecture). uint32_t seems to me the most fitting candidate for rv32.
 */
uint32_t __heap_size = configTOTAL_HEAP_SIZE;

volatile uint32_t system_core_clock = 5000000u;


/* interrupt handling */
void timer_irq_handler(uint32_t mcause);
void undefined_handler(uint32_t mcause);
extern void fc_soc_event_handler1(uint32_t mcause);
void (*isr_table[32])(uint32_t);
void flash_readid(const struct cli_cmd_entry *pEntry);
/**
 * Board init code. Always call this before anything else.
 */

uint8_t setFLLFrequencyInIntegerMode(uint8_t aFLLNum, uint8_t aRefFreqInMHz, uint16_t aMultiplier, uint8_t aDivideRatio_R_Prescale, uint8_t aPS0_L1, uint8_t aPS0_L2)
{
	uint8_t lSts = 0;
	volatile uint32_t *lPLLStartAddress = (uint32_t *)NULL;
	uint32_t lCounter = 0;
	uint32_t lCfgVal = 0;

	uint8_t lPS0_L1 = aPS0_L1 & 0x03;
	uint8_t lPS0_L2 = aPS0_L2 & 0xFF;

	if (aFLLNum == 0)
		lPLLStartAddress = (uint32_t *)FLL1_START_ADDR;
	else if (aFLLNum == 1)
		lPLLStartAddress = (uint32_t *)FLL2_START_ADDR;
	else if (aFLLNum == 2)
		lPLLStartAddress = (uint32_t *)FLL3_START_ADDR;
	else
		lPLLStartAddress = (uint32_t *)NULL;

	if (lPLLStartAddress != NULL)
	{
		if ((aRefFreqInMHz >= 5) && (aRefFreqInMHz <= 500))
		{
			if ((aMultiplier > 0) && (aMultiplier < 2048))
			{
				if (aDivideRatio_R_Prescale < 16)
				{
					*lPLLStartAddress |= (1 << 19);	     // Bypass on;
					*lPLLStartAddress |= (1 << 2);	     // Reset high
					*lPLLStartAddress &= ~(1 << 2);	     // Reset low;
					*lPLLStartAddress &= ~(1 << 18);     // PS0_EN is set to low
					*lPLLStartAddress |= (lPS0_L1 << 0); // PS0_L1 0 which gives L01 = 1
					*lPLLStartAddress |= (lPS0_L2 << 4); // PS0_L2_INT 0 and PS0_L2_FRAC 0 which gives L02 = 1
					*lPLLStartAddress |= (0 << 12);	     // PS0_L2_INT 0 and PS0_L2_FRAC 0 which gives L02 = 1

					// FLL1 Config 1 register not configuring PS1
					*(lPLLStartAddress + 1) = 0;

					// FLL1 Config 2 register
					lCfgVal = 0;
					lCfgVal |= (aMultiplier << 4);		    // MULT_INT	0x28 = 40 (40*10 = 400MHz) Multiplier cannot hold 0
					lCfgVal |= (1 << 27);			    // INTEGER_MODE is enabled
					lCfgVal |= (aDivideRatio_R_Prescale << 28); // PRESCALE value (Divide Ratio R = 1)

					*(lPLLStartAddress + 2) = lCfgVal;

					// FLL1 Config 3 register not configuring SSC
					*(lPLLStartAddress + 3) = 0;

					// FLL1 Config 4 register
					*(lPLLStartAddress + 4) = 0x64;

					// FLL1 Config 5 register
					*(lPLLStartAddress + 5) = 0x269;

					*lPLLStartAddress |= (1 << 2);	// Reset high
					*lPLLStartAddress |= (1 << 18); // PS0_EN;
					// lCounter = 0;
					while ((*(lPLLStartAddress + 4) & 0x80000000) == 0) // Wait for lock detect to go high
					{
						lCounter++;
						if (lCounter >= 0x00010000)
						{
							lSts = 5; // Unable to achieve lock
							lCounter = 0;
							break;
						}
					}
					if (lSts == 0)
						*(lPLLStartAddress) &= ~(1 << 19); // Bypass off;
				}
				else
				{
					lSts = 1; // aDivideRatio_R_Prescale
				}
			}
			else
			{
				lSts = 2; // Invalid aMultiplier
			}
		}
		else
		{
			lSts = 3; // Invalid reference freq
		}
	}
	else
	{
		lSts = 4; // Invalid PLL number
	}
	return lSts;
}

int handler_count[32];
uint32_t gSpecialHandlingIRQCnt = 0;
uint8_t gQSPIIdNum = 0;

void system_init(void)
{
	uint32_t lFlashID = 0;
	SocCtrl_t *soc = APB_SOC_CTRL_ADDR;
	soc->soft_reset = 1;
	uint32_t val = 0;
	uint8_t i = 0;
	timer_irq_disable();

	uint32_t *lFFL1StartAddress = (uint32_t *)FLL1_START_ADDR;
	uint32_t *lFFL2StartAddress = (uint32_t *)FLL2_START_ADDR;
	uint32_t *lFFL3StartAddress = (uint32_t *)FLL3_START_ADDR;

	setFLLFrequencyInIntegerMode(0, 10, 40, 1, 0, 1); // 400

	setFLLFrequencyInIntegerMode(1, 10, 40, 1, 0, 2); // 200

	setFLLFrequencyInIntegerMode(2, 10, 40, 1, 0, 4); // 100

	/* Hook up isr table. This table is temporary until we figure out how to  do proper vectored interrupts. */
	for (int i = 0; i < 32; i++)
	{
		isr_table[i] = undefined_handler;
		handler_count[i] = 0;
	}
	isr_table[0x7] = timer_irq_handler;
	isr_table[0xb] = (void (*)(uint32_t))fc_soc_event_handler1; // 11 for cv32

	/* mtvec is set in crt0.S */

	/* deactivate all soc events as they are enabled by default */
	pulp_soc_eu_event_init();

	/* Setup soc events handler. */
	// pi_fc_event_handler_init(FC_SOC_EVENT);
	pi_fc_event_handler_init(11);

	/* TODO: I$ enable*/
	/* enable core level interrupt (mie) */
	//irq_clint_enable();

	val = csr_read(CSR_MIE);

	/* TODO: enable uart */
	for (uint8_t id = 0; id != N_UART; id++)
	{
		udma_uart_open(id, 115200);
	}
	#if 0  
	for (uint8_t id = 0; id != N_I2CM; id++)
	{
		udma_i2cm_open(id, 400000); // 200000
	} 
	for (i = 0; i < N_QSPIM; i++)
	{
		setQspimPinMux(i);
		udma_qspim_open(i, 2500000);
		udma_qspim_control((uint8_t)i, (udma_qspim_control_type_t)kQSPImReset, (void *)0);

		lFlashID = udma_flash_readid(i, 0);
		if ((lFlashID == 0xFFFFFFFF) || (lFlashID == 0))
		{
			gQSPIFlashPresentFlg[i] = 0;
		}
		else
		{
			gQSPIFlashPresentFlg[i] = 1;
			if ((lFlashID & 0xFF) == 0x20)
			{
				gMicronFlashDetectedFlg[i] = 1;
				gQSPIIdNum = 0;
			}
			else
				gMicronFlashDetectedFlg[i] = 0;
		}
		restoreQspimPinMux(i);
	}
	#endif

#if (FOR_SIMULATION_TESTING == 1)
	forSimulationTesting();
#endif

	// hal_set_apb_i2cs_slave_on_off(1);
	// if (hal_get_apb_i2cs_slave_address() != MY_I2C_SLAVE_ADDRESS)
	// 	hal_set_apb_i2cs_slave_address(MY_I2C_SLAVE_ADDRESS);
}

void system_core_clock_update(void)
{
	system_core_clock = pi_fll_get_frequency(FLL_SOC, 0);
}

void system_core_clock_get(void)
{
	system_core_clock_update();
	return;
}

uint16_t Writeraw(uint8_t uart_id, uint16_t write_len, uint8_t* write_buffer) {
	UdmaUart_t*				puart = (UdmaUart_t*)(UDMA_CH_ADDR_UART + uart_id * UDMA_CH_SIZE);

	while (puart->status_b.tx_busy) {  // ToDo: Why is this necessary?  Thought the semaphore should have protected
	}

	puart->tx_saddr = (uint32_t)write_buffer;
	puart->tx_size = write_len;
	puart->tx_cfg_b.en = 1; //enable the transfer

	return 0;
}

void timer_irq_handler(uint32_t mcause)
{
#warning requires critical section if interrupt nesting is used.
	//Writeraw(0, 1 ,(uint8_t*)a);
	rt_interrupt_enter();
	rt_tick_increase();
	rt_interrupt_leave();
}

void vSystemIrqHandler(uint32_t mcause)
{
	//Writeraw(0, 1,(uint8_t*)b);
	isr_table[mcause & 0x1f](mcause & 0x1f);
}

void undefined_handler(uint32_t mcause)
{
	uint32_t RegReadVal = 0;
#ifdef __PULP_USE_LIBC
	abort();
#else
	//	taskDISABLE_INTERRUPTS();
	//	for(;;);
	if ((mcause == 18) || (mcause == 19) || (mcause == 31))
	{
		gSpecialHandlingIRQCnt++;
		if (gSpecialHandlingIRQCnt >= 20)
		{
			RegReadVal = csr_read(CSR_MIE);
			if ((RegReadVal & BIT(mcause)) != 0) // Check if the event interrupt mask is open.
			{
				// close the event interrupt mask.
				csr_read_clear(CSR_MIE, BIT(mcause));
			}
		}
	}
	else
	{
		handler_count[mcause]++;
		//csr_read_clear(CSR_MIE, BIT(mcause));
	}
#endif
}

void vPortSetupTimerInterrupt(void)
{

	extern int timer_irq_init(uint32_t ticks);
	timer_irq_init(ARCHI_FPGA_FREQUENCY / RT_TICK_PER_SECOND);
}

#if (FOR_SIMULATION_TESTING == 1)
uint8_t gCamDataBuf[1024];

void udma_cam_open(uint8_t cam_id)
{
	int i = 0;
	volatile UdmaCtrl_t *pudma_ctrl = (UdmaCtrl_t *)UDMA_CH_ADDR_CTRL;

	/* Enable reset and enable uart clock */
	pudma_ctrl->reg_rst |= (UDMA_CTRL_CAM0_CLKEN << cam_id);
	pudma_ctrl->reg_rst &= ~(UDMA_CTRL_CAM0_CLKEN << cam_id);
	pudma_ctrl->reg_cg |= (UDMA_CTRL_CAM0_CLKEN << cam_id);

	// psdio_regs->clk_div_b.clk_div = 5;
	// psdio_regs->clk_div_b.valid = 1;
	hal_setpinmux(21, 0); // cam0_vsync
	hal_setpinmux(22, 0); // cam0_hsync
	hal_setpinmux(25, 0); // cam0_clk
	for (i = 0; i < 8; i++)
	{
		// set pin muxes to cam functionality
		hal_setpinmux(29 + i, 0);
	}
	return;
}

void cam_interface_init(uint16_t x, uint16_t y, uint8_t aBitMode)
{
	camera_struct_t *camera;

	uint16_t lXCoordOfUpperRightCorner = 0; // X coordinate of upper right corner of slice
	uint16_t lYCoordOfUpperRightCorner = 0; // Y coordinate of upper right corner of slice

	lXCoordOfUpperRightCorner = x + 3;
	lYCoordOfUpperRightCorner = y + 3;
	// camera = (camera_struct_t *)0x1A102300;  // Peripheral 5?
	camera = (camera_struct_t *)(UDMA_CH_ADDR_CAM + 0 * UDMA_CH_SIZE);
	camera->cfg_ll = 0 << 16 | 0;
	camera->cfg_ur = ((lYCoordOfUpperRightCorner << 16) | lXCoordOfUpperRightCorner);
	// camera->cfg_ur = 323<<16 | 243; // 320 x 240 ?
	camera->cfg_filter = (1 << 16) | (1 << 8) | 1;
	// camera->cfg_size = 324;
	camera->cfg_size = y + 4;
	camera->vsync_pol = 1;
	if (aBitMode == 1)
	{
		camera->cfg_glob |= (1 << 17);
	}
	else if (aBitMode == 4)
	{
		camera->cfg_glob |= (1 << 16);
	}
	else if (aBitMode == 8)
	{
		camera->cfg_glob |= (0 << 0);
	}
	camera->cfg_glob |= (0 << 0) |	    //  framedrop disabled
			    (000000 << 1) | // number of frames to drop
			    (0 << 7) |	    // Frame slice disabled
			    (004 << 8) |    // Format binary 100 = ByPass little endian
			    (0000 << 11);   // Shift value ignored in bypass
}

uint8_t cam_grab_frame(int x, int y, uint8_t *pparam)
{
	uint32_t lCounter = 0;
	uint8_t lStatus = 0;
	uint16_t lX = x + 4;
	uint16_t lY = y + 4;

	camera_struct_t *camera;
	// camera = (camera_struct_t *)0x1A102300;  // Peripheral 5?
	camera = (camera_struct_t *)(UDMA_CH_ADDR_CAM + 0 * UDMA_CH_SIZE);

	camera->rx_saddr = pparam;
	camera->rx_size = (lX * lY);
	camera->rx_cfg = 0x12;				  // start 16-bit transfers
	camera->cfg_glob |= camera->cfg_glob | (1 << 31); // enable 1 == go

	lCounter = 0;
	while (camera->rx_size != 0)
	{
		lCounter++;
		if (lCounter >= 0x00100000)
		{
			lStatus = 3; // Time out
			break;
		}
	}
	// configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
	camera->cfg_glob = camera->cfg_glob & (0x7fffffff); // enable 1 == go
	// configASSERT( xSemaphoreGive( shSemaphoreHandle ) == pdTRUE );
	return lStatus;
}

void forSimulationTesting(void)
{
	udma_cam_open(0);
	cam_interface_init(240, 320, 8);
	cam_grab_frame(240, 320, gCamDataBuf);
}
#endif
