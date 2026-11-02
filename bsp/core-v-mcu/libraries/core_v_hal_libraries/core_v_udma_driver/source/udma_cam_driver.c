/*
 * Copyright 2021 QuickLogic
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
 */
#include "rtconfig.h"
#ifdef PKG_USING_FREERTOS_WRAPPER
#include "FreeRTOS.h"
#include <camera.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "semphr.h"
#include "core-v-mcu-config.h"
#include "hal_fc_event.h"
#include "hal_udma_ctrl_reg_defs.h"
#include "hal_udma_cam_reg_defs.h"
#include <udma_cam_driver.h>
#include <udma_i2cm_driver.h>
#include "himax.h"
#include "camera.h"

reg_cfg_t himaxRegInit[] = {
    {BLC_TGT, 0x08},            //  BLC target :8  at 8 bit mode
    {BLC2_TGT, 0x08},           //  BLI target :8  at 8 bit mode
    {0x3044, 0x0A},             //  Increase CDS time for settling
    {0x3045, 0x00},             //  Make symetric for cds_tg and rst_tg
    {0x3047, 0x0A},             //  Increase CDS time for settling
    {0x3050, 0xC0},             //  Make negative offset up to 4x
    {0x3051, 0x42},
    {0x3052, 0x50},
    {0x3053, 0x00},
    {0x3054, 0x03},             //  tuning sf sig clamping as lowest
    {0x3055, 0xF7},             //  tuning dsun
    {0x3056, 0xF8},             //  increase adc nonoverlap clk
    {0x3057, 0x29},             //  increase adc pwr for missing code
    {0x3058, 0x1F},             //  turn on dsun
    {0x3059, 0x1E},
    {0x3064, 0x00},
    {0x3065, 0x04},             //  pad pull 0

    {BLC_CFG, 0x43},            //  BLC_on, IIR

    {0x1001, 0x43},             //  BLC dithering en
    {0x1002, 0x43},             //  blc_darkpixel_thd
    {0x0350, 0x00},             //  Dgain Control
    {BLI_EN, 0x01},             //  BLI enable
    {0x1003, 0x00},             //  BLI Target [Def: 0x20]

    {DPC_CTRL, 0x01},           //  DPC option 0: DPC off   1 : mono   3 : bayer1   5 : bayer2
    {0x1009, 0xA0},             //  cluster hot pixel th
    {0x100A, 0x60},             //  cluster cold pixel th
    {SINGLE_THR_HOT, 0x90},     //  single hot pixel th
    {SINGLE_THR_COLD, 0x40},    //  single cold pixel th
    {0x1012, 0x00},             //  Sync. shift disable
    {0x2000, 0x07},
    {0x2003, 0x00},
    {0x2004, 0x1C},
    {0x2007, 0x00},
    {0x2008, 0x58},
    {0x200B, 0x00},
    {0x200C, 0x7A},
    {0x200F, 0x00},
    {0x2010, 0xB8},
    {0x2013, 0x00},
    {0x2014, 0x58},
    {0x2017, 0x00},
    {0x2018, 0x9B},

    {AE_CTRL,        0x01},      //Automatic Exposure Gain Control
    {AE_TARGET_MEAN, 0x3C},      //AE target mean [Def: 0x3C]
    {AE_MIN_MEAN,    0x0A},      //AE min target mean [Def: 0x0A]

    {INTEGRATION_H,  0x00},      //Integration H [Def: 0x01]
    {INTEGRATION_L,  0x60},      //Integration L [Def: 0x08]
    {ANALOG_GAIN,    0x00},      //Analog Global Gain
    {DAMPING_FACTOR, 0x20},      //Damping Factor [Def: 0x20]
    {DIGITAL_GAIN_H, 0x01},      //Digital Gain High [Def: 0x01]
    {DIGITAL_GAIN_L, 0x00},      //Digital Gain Low [Def: 0x00]

    {0x2103, 0x03},

    {0x2104, 0x05},
    {0x2105, 0x01},

    {0x2106, 0x54},

    {0x2108, 0x03},
    {0x2109, 0x04},

    {0x210B, 0xC0},
    {0x210E, 0x00}, //Flicker Control
    {0x210F, 0x00},
    {0x2110, 0x3C},
    {0x2111, 0x00},
    {0x2112, 0x32},

    {0x2150, 0x30},
    {0x0340, 0x02},
    {0x0341, 0x16},
    {0x0342, 0x01},
    {0x0343, 0x78},
    {0x3010, 0x01},
    {0x0383, 0x01},
    {0x0387, 0x01},
    {0x0390, 0x00},
    {0x3011, 0x70},
    {0x3059, 0x02},
    {0x3060, 0x01},
//    {0x3060, 0x25}, //Clock gating and clock divisors
    {0x3068, 0x20}, //PCLK0 polarity
    {IMG_ORIENTATION, 0x01}, // change the orientation
    {0x0104, 0x01},
    {0x0100, 0x01},
	//{0x0601, 0x11}	//Test pattern walking ones
	//{0x0601, 0x01}	//Test pattern colour bar
};

SemaphoreHandle_t  cam_semaphore_rx;
static uint8_t cam;
static void camISR() {

}
void cam_open (uint8_t cam_id)
{
	int i = 0;
	volatile UdmaCtrl_t*		pudma_ctrl = (UdmaCtrl_t*)UDMA_CH_ADDR_CTRL;

	/* Enable reset and enable uart clock */
	pudma_ctrl->reg_rst |= (UDMA_CTRL_CAM0_CLKEN << cam_id);
	pudma_ctrl->reg_rst &= ~(UDMA_CTRL_CAM0_CLKEN << cam_id);
	pudma_ctrl->reg_cg |= (UDMA_CTRL_CAM0_CLKEN << cam_id);

	//psdio_regs->clk_div_b.clk_div = 5;
	//psdio_regs->clk_div_b.valid = 1;
	hal_setpinmux(21, 0);
	hal_setpinmux(22, 0);
	hal_setpinmux(25, 0);
	for(i=0; i<8; i++ )
	{
		//set pin muxes to sdio functionality
		 hal_setpinmux(29+i, 0);
	}

	/* See if already initialized */
	if (cam_semaphore_rx != NULL ){
		return;
	}

	/* Set semaphore */
	SemaphoreHandle_t shSemaphoreHandle;		// FreeRTOS.h has a define for xSemaphoreHandle, so can't use that
	shSemaphoreHandle = xSemaphoreCreateBinary();
	configASSERT(shSemaphoreHandle);
	xSemaphoreGive(shSemaphoreHandle);
	cam_semaphore_rx = shSemaphoreHandle;


	/* Set handlers. */
	pi_fc_event_handler_set(SOC_EVENT_UDMA_CAM_RX(cam_id), camISR, cam_semaphore_rx);
	/* Enable SOC events propagation to FC. */
	hal_soc_eu_set_fc_mask(SOC_EVENT_UDMA_CAM_RX(cam_id));

	/* configure */
	cam = 0x48; // Himax address
	udma_cam_control(kCamReset, NULL);

	return;
}
uint16_t udma_cam_control(udma_cam_control_type_t control_type, void* pparam) {
	short retval = 0;
	uint16_t i;
	SemaphoreHandle_t shSemaphoreHandle;
	camera_struct_t *camera;
	//camera = (camera_struct_t *)0x1A102300;  // Peripheral 5?
	camera = (camera_struct_t *)(UDMA_CH_ADDR_CAM + 0 * UDMA_CH_SIZE);
	shSemaphoreHandle = cam_semaphore_rx;

	switch (control_type) {
	case kCamReset:
		_himaxRegWrite(SW_RESET, HIMAX_RESET);
		break;
	case kCamID:
		udma_i2cm_16read8(0, cam, MODEL_ID_H, 2, &retval, 0);
		retval = (retval >> 8) & 0xff | (retval <<8);
		break;
	case kCamInit:
	    for(i=0; i<(sizeof(himaxRegInit)/sizeof(reg_cfg_t)); i++){
	        _himaxRegWrite(himaxRegInit[i].addr, himaxRegInit[i].data);
	    }
	    camera->cfg_ll = 0<<16 | 0;
	    	camera->cfg_ur = 323<<16 | 243; // 320 x 240 ?
	    	camera->cfg_filter = (1 << 16) | (1 << 8) | 1;
	    	camera->cfg_size = 324;
	    	camera->vsync_pol = 1;
	    	camera->cfg_glob = (0 << 0) | //  framedrop disabled
	    			(000000 << 1) | // number of frames to drop
	    			(0 << 7) | // Frame slice disabled
	    			(004 << 8) | // Format binary 100 = ByPass little endian
	    			(0000 << 11);  // Shift value ignored in bypass

	    break;
	case kCamFrame:
		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
		camera->rx_saddr = pparam;
		camera->rx_size = (244*324);
		camera->rx_cfg = 0x12;  // start 16-bit transfers
    	camera->cfg_glob = camera->cfg_glob |
    			(1 << 31) ; // enable 1 == go

		configASSERT( xSemaphoreTake( shSemaphoreHandle, 1000000 ) == pdTRUE );
    	camera->cfg_glob = camera->cfg_glob &
    			(0x7fffffff) ; // enable 1 == go
		configASSERT( xSemaphoreGive( shSemaphoreHandle ) == pdTRUE );
	}
	return retval;
}

void _himaxRegWrite(unsigned int addr, unsigned char value){
	uint8_t naddr;
	uint16_t data;
	naddr = (addr>>8) & 0xff;
	data = (value << 8) | (addr & 0xff);
	udma_i2cm_write (0, cam, naddr, 2, &data, 0);
   //     i2c_16write8(cam,addr,value);
}
#endif
