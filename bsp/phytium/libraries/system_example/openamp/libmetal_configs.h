#ifndef LIBMETAL_CONFIGS_H
#define LIBMETAL_CONFIGS_H

#if defined __cplusplus
extern "C" {
#endif

#include <metal/sys.h>
#include <metal/device.h>
#include <metal/irq.h>

#define KICK_BUS_NAME         "generic"
#define KICK_SGI_NUM_9            9
// #define KICK_SGI_NUM_10           10

/* device name for slave 00 */
#define SLAVE_00_KICK_DEV_NAME "slave_00_kick"
#define SLAVE_00_SGI            KICK_SGI_NUM_9
// #define SLAVE_01_KICK_DEV_NAME "slave_01_kick"
// #define SLAVE_01_SGI            KICK_SGI_NUM_10

#if defined __cplusplus
}
#endif

#endif /* LIBMETAL_CONFIGS_H */
