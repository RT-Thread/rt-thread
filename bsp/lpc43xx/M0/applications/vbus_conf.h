#ifndef __VBUS_CONF_H__
#define __VBUS_CONF_H__

/* Number of blocks in VBus. The total size of VBus is
 * RT_VMM_RB_BLK_NR * 64byte * 2. */
#define RT_VMM_RB_BLK_NR     20

/* We don't use the IRQ number to trigger IRQ in this BSP. */
#define RT_VBUS_GUEST_VIRQ    0
#define RT_VBUS_HOST_VIRQ     0

#endif /* end of include guard: __VBUS_CONF_H__ */

