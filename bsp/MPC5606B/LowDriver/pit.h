/*
 * pit.h
 *
 *  Created on: 2018Äê1ÔÂ2ÈÕ
 *      Author: Administrator
 */

#ifndef PIT_H_
#define PIT_H_

#include "lowdriver.h"


#define SystemTicks		64000000U
extern void pit_init(void);

extern void pit_start(uint8_t chNumber,uint8_t pri,uint16_t ticks_per_sec);

extern void PITDelay(uint32_t ticks);
#endif /* PIT_H_ */
