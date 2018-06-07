/*
 * File      : nuc97x_mfp.h
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */

#ifndef DRIVERS_NUC97X_MFP_H_
#define DRIVERS_NUC97X_MFP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void mfp_set_port_a(uint32_t pin, uint32_t func);
void mfp_set_port_b(uint32_t pin, uint32_t func);
void mfp_set_port_c(uint32_t pin, uint32_t func);
void mfp_set_port_d(uint32_t pin, uint32_t func);
void mfp_set_port_e(uint32_t pin, uint32_t func);
void mfp_set_port_f(uint32_t pin, uint32_t func);
void mfp_set_port_g(uint32_t pin, uint32_t func);
void mfp_set_port_h(uint32_t pin, uint32_t func);
void mfp_set_port_i(uint32_t pin, uint32_t func);


#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_NUC97X_MFP_H_ */
