#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <usb/sunxi_hal_udc.h>
#include <hal_cmd.h>
#include <hal_log.h>

#include "usb_msg.h"

static int cmd_gadget_test(int argc, const char **argv)
{
        hal_log_info("usb msg desc init\n");
    usb_msg_desc_init();
        hal_log_info("hal udc init\n");
    hal_udc_init();
    hal_udc_register_callback(usb_msg_callback);
    return 0;

}
FINSH_FUNCTION_EXPORT_CMD(cmd_gadget_test, hal_udc, udc hal APIs tests)

