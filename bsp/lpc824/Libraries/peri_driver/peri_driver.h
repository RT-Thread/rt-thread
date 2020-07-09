#ifndef _PERI_DRIVER_H_
#define _PERI_DRIVER_H_

#include "chip.h"
#include "rom/romapi_8xx.h"
#include "acmp/acmp_8xx.h"

#if defined(CHIP_LPC82X)
	#include "adc/adc_8xx.h"
#endif

#include "crc/crc_8xx.h"

#if defined(CHIP_LPC82X)
	#include "dma/dma_8xx.h"
#endif

#include "gpio/gpio_8xx.h"
#include "i2c/i2c_8xx.h"
#include "iap/iap.h"
#include "crc/crc_8xx.h"

#if defined(CHIP_LPC82X)
	#include "inmux/inmux_8xx.h"
#endif

#include "mrt/mrt_8xx.h"
#include "mrt/stopwatch.h"
#include "pinint/pinint_8xx.h"
#include "pmu/pmu_8xx.h"

#include "sctimer/sct_8xx.h"
#include "sctimer/sct_pwm_8xx.h"
#include "spi/spi_8xx.h"
#include "uart/uart_8xx.h"
#include "wkt/wkt_8xx.h"
#include "wwdt/wwdt_8xx.h"
#include "iap/iap.h"
#endif
