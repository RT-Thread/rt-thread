#ifndef SUNXI_DRV_UART_H
#define SUNXI_DRV_UART_H
#include <devfs.h>
typedef struct sunxi_driver_uart
{
    struct devfs_node  base;
    int32_t            dev_id;
    const void        *hal_drv;
} sunxi_driver_uart_t;

#endif  /*SUNXI_DRV_UART_H*/
