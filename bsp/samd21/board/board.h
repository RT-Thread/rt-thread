/* This is a template file for board configuration created by MCUXpresso Project Generator. Enjoy! */

#ifndef _BOARD_H_
#define _BOARD_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#include <stdint.h>
#include "samd21.h"
#include "system_samd21.h"
#include "core_cm0plus.h"              /* Core Peripheral Access Layer */

/* The board name */
#define BOARD_NAME "###-not-specified-###"

#define CHIP_SRAM_END   (0x20000000 + 32*1024)

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief initialize debug console to enable printf for this demo/example
 */
void rt_board_init(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
