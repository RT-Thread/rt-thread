#ifndef __DRV_I2C_24LCXX_H__
#define __DRV_I2C_24LCXX_H__
#include <rtthread.h>

#define I2C_ADDR_1Byte	0
#define I2C_ADDR_2Byte	1

#define EE24LC02

#ifdef EE24LC02
	#define EE_ADDR_SIZE I2C_ADDR_1Byte	/* I2C_ADDR_1Byte | I2C_ADDR_2Byte */
	#define EE_MEM_SIZE	256
	#define EE_PageSize	8
#endif

#endif
