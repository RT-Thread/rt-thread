#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <queue.h>
#include "himax.h"


typedef struct {
	volatile uint32_t *rx_saddr; // 0x00
	volatile uint32_t rx_size; 	 // 0x04
	volatile uint32_t rx_cfg;    // 0x08
	volatile uint32_t rx_initcfg;// 0x0C
	volatile uint32_t *tx_saddr; // 0x10
	volatile uint32_t tx_size;   // 0x14
	volatile uint32_t tx_cfg;    // 0x18
	volatile uint32_t tx_initcfg;// 0x1C
	volatile uint32_t cfg_glob;  // 0x20
	volatile uint32_t cfg_ll;    // 0x24
	volatile uint32_t cfg_ur;    // 0x28
	volatile uint32_t cfg_size;  // 0x2C
	volatile uint32_t cfg_filter;// 0x30
	volatile uint32_t vsync_pol; // 0x34

} camera_struct_t;

typedef struct {
	uint16_t addr;
	uint8_t data;
}reg_cfg_t;


#endif
