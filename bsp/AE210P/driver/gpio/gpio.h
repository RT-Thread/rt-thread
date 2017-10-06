#ifndef __AG101_GPIOC_INC__
#define __AG101_GPIOC_INC__

//#include "hal.h"

// GPIO port name definition
typedef enum GPIOD_PORTS
{
    GPIO0       = 0x00000001,
    GPIO1       = 0x00000002,
    GPIO2       = 0x00000004,
    GPIO3       = 0x00000008,
    GPIO4       = 0x00000010,
    GPIO5       = 0x00000020,
    GPIO6       = 0x00000040,
    GPIO7       = 0x00000080,

    GPIO8       = 0x00000100,
    GPIO9       = 0x00000200,
    GPIO10      = 0x00000400,
    GPIO11      = 0x00000800,
    GPIO12      = 0x00001000,
    GPIO13      = 0x00002000,
    GPIO14      = 0x00004000,
    GPIO15      = 0x00008000,

    GPIO16      = 0x00010000,
    GPIO17      = 0x00020000,
    GPIO18      = 0x00040000,
    GPIO19      = 0x00080000,
    GPIO20      = 0x00100000,
    GPIO21      = 0x00200000,
    GPIO22      = 0x00400000,
    GPIO23      = 0x00800000,

    GPIO24      = 0x01000000,
    GPIO25      = 0x02000000,
    GPIO26      = 0x04000000,
    GPIO27      = 0x08000000,
    GPIO28      = 0x10000000,
    GPIO29      = 0x20000000,
    GPIO30      = 0x40000000,
    GPIO31      = 0x80000000,

} GPIOD_PORTS;

struct gpio_dev_t
{
//	hal_bh_t     hisr;
	unsigned int int_data;
};
#endif // __AG101_GPIOC_INC__
