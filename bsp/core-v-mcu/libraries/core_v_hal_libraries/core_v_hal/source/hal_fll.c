/*
 * Copyright (C) 2019 ETH Zurich and University of Bologna
 * Copyright (C) 2019 GreenWaves Technologies
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

/* FLL driver code for PULPissimo */
/* Author: Germain Haugou (germain.haugou@iis.ee.ethz.ch)
 *         Eric Flamand (eric.flamand@greenwaves-technologies.com)
 *         Robert Balas (balasr@iis.ee.ethz.ch)
 */

#include <pulp_io.h>
#include <stdint.h>
#include "system_metal.h"
#include "core-v-mcu-pulp-mem-map.h"
#include "hal_fll.h"

#define __MAX(a, b)                                                            \
	({                                                                     \
		typeof(a) _a = (a);                                            \
		typeof(b) _b = (b);                                            \
		_a > _b ? _a : _b;                                             \
	})

#define __FL1(x) (31 - __builtin_clz((x)))

int __rt_fll_freq[ARCHI_NB_FLL];
static char __rt_fll_is_on[ARCHI_NB_FLL];
int __rt_freq_domains[RT_FREQ_NB_DOMAIN];

void pulp_fll_init(void)
{
	for (int i = 0; i < ARCHI_NB_FLL; i++) {
		__rt_fll_freq[i] = 0;
		__rt_fll_is_on[i] = 0;
	}

	__rt_freq_domains[__RT_FREQ_DOMAIN_FC] = __fll_init(__RT_FLL_FC);
	__rt_freq_domains[__RT_FREQ_DOMAIN_PERIPH] =
		__fll_init(__RT_FLL_PERIPH);
}

static unsigned int __rt_fll_get_mult_div_from_freq(unsigned int freq,
						    unsigned int *mult,
						    unsigned int *div)
{
	unsigned int fref = ARCHI_REF_CLOCK;
	unsigned int Log2M = __FL1(freq) - __FL1(fref);
	unsigned int D = __MAX(1, (FLL_LOG2_MAXM - Log2M) >> 1);
	unsigned int M = (freq << D) / fref;
	unsigned int fres;

#if 0 /* PULP_CHIP == CHIP_QUENTIN */

	/* TODO on quentin, the fll never converges (e.g. a mult factor of 15000 is
	 * not working), check what is the maximum value we can use
	 */
	while (M >= 10000) {
		M >>= 1;
		D--;
	};

	if (D == 0) fres = fref*M;
	else fres = (fref*M + (1<<(D-1)))>>D;   /* Rounding */

#else
	fres = (fref * M + (1 << (D - 1))) >> D; /* Rounding */
#endif

	*mult = M;
	*div = D + 1;
	return fres;
}

static unsigned int __rt_fll_get_freq_from_mult_div(unsigned int mult,
						    unsigned int div)
{
	// FreqOut = Fref * Mult/2^(Div-1)	With Mult on 16 bits and Div on 4 bits
	unsigned int fref = ARCHI_REF_CLOCK;
	unsigned int fres = (fref * mult) >> (div - 1);
	return fres;
}

unsigned int __fll_init(int fll)
{
	//rt_trace(RT_TRACE_INIT, "Initializing FLL (fll: %d)\n", fll);

	fll_reg_conf1_t reg1 = {
		.raw = readw((uintptr_t)(PULP_FLL_ADDR + FLL_CONF1_OFFSET +
					  fll * PULP_FLL_AREA_SIZE))
	};

	/* Only lock the fll if it is not already done by the boot code */
	if (reg1.mode == 0) {
		/* Set Clock Ref lock assert count */
		fll_reg_conf2_t reg2 = {
			.raw = readw((uintptr_t)(PULP_FLL_ADDR +
						  FLL_CONF2_OFFSET +
						  fll * PULP_FLL_AREA_SIZE))
		};

		reg2.assert_cycles = 6;
		reg2.lock_tolerance = 0x50;
		writew(reg2.raw, (uintptr_t)(PULP_FLL_ADDR + FLL_CONF2_OFFSET +
					      fll * PULP_FLL_AREA_SIZE));
		/*
		* In order to lock the fll faster, we first setup an approximated
		* frequency while we are in open loop as it is set immediately.
		* Then starting from this frequency, we should reach the target one
		* in lock mode faster.
		* We are in open loop, prime the fll forcing dco input, approx 70 MHz
		*/
		//rt_trace(RT_TRACE_INIT, "Priming FLL in open loop (fll: %d)\n",
		//	 fll);
		fll_reg_integrator_t reg_int = {
			.raw = readw((uintptr_t)(PULP_FLL_ADDR +
						  FLL_INTEGRATOR_OFFSET +
						  fll * PULP_FLL_AREA_SIZE))
		};

/* TODO: quick hack to prevent 0 == 0 in next macro */
#ifndef PULP_CHIP
#define PULP_CHIP 1
#endif

#if PULP_CHIP == CHIP_QUENTIN || PULP_CHIP == CHIP_KERBIN
#error "Touching bad FLL code path"
		/* TODO: don't know how to choose the right, 332 is too agressive for
		 * quentin and the fll is never converging
		 */
		reg_int.state_int_part = 100;
#else
		reg_int.state_int_part = 332;
#endif

		writew(reg_int.raw,
		       (uintptr_t)(PULP_FLL_ADDR + FLL_INTEGRATOR_OFFSET +
				    fll * PULP_FLL_AREA_SIZE));

		/* Lock Fll */
		reg1.output_lock_enable = 1;
		reg1.mode = 1;
		writew(reg1.raw, (uintptr_t)(PULP_FLL_ADDR + FLL_CONF1_OFFSET +
					      fll * PULP_FLL_AREA_SIZE));
	}

	/* In case the FLL frequency was set while it was off, update it immediately */
	/* TODO */
	unsigned int freq = __rt_fll_freq[fll];
	if (freq) {
		__rt_fll_set_freq(fll, freq);
	} else {
		freq = __rt_fll_get_freq_from_mult_div(reg1.mult_factor,
						       reg1.clock_out_divider);
		__rt_fll_freq[fll] = freq;
	}

	__rt_fll_is_on[fll] = 1;

	//rt_trace(RT_TRACE_INIT, "FLL is locked (fll: %d, freq: %d)\n", fll,
	// freq);

	return freq;
}

unsigned int __rt_fll_set_freq(int fll, unsigned int frequency)
{
	/* Synchronize with bridge so that it does not try to access the chip
	 * while we are changing the frequency
	 */
	// if (fll == __RT_FLL_FC)
	// 	__rt_bridge_req_shutdown();

	unsigned int real_freq, mult, div;
	real_freq = __rt_fll_get_mult_div_from_freq(frequency, &mult, &div);

	__rt_fll_freq[fll] = real_freq;
	if (__rt_fll_is_on[fll]) {
		fll_reg_conf1_t reg1 = {
			.raw = readw((uintptr_t)(PULP_FLL_ADDR +
						  FLL_CONF1_OFFSET +
						  fll * PULP_FLL_AREA_SIZE))
		};

		reg1.mult_factor = mult;
		reg1.clock_out_divider = div;

		writew(reg1.raw, (uintptr_t)(PULP_FLL_ADDR + FLL_CONF1_OFFSET +
					      fll * PULP_FLL_AREA_SIZE));
	}

	return real_freq;
}
