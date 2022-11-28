#include <stdio.h>
#include <platform_usb.h>
#include <hal_log.h>
#include <hal_cmd.h>
#include <usb/hal_hci.h>


static int cmd_test_hci(int argc, const char **argv)
{
    hal_usb_core_init();

    for (int hci_num = 0; hci_num < USB_MAX_CONTROLLER_COUNT; hci_num++)
    {
        /*usb0 need hcd neet to choose */
        hal_usb_hcd_init(hci_num);
    }

    return 0;
}

FINSH_FUNCTION_EXPORT_CMD(cmd_test_hci, hal_hci, hci hal APIs tests)

static int cmd_test_hci_rm(int argc, const char **argv)
{
    for (int hci_num = 0; hci_num < USB_MAX_CONTROLLER_COUNT; hci_num++)
    {
        hal_usb_hcd_deinit(hci_num);
    }
    hal_usb_core_exit();

    return 0;
}

FINSH_FUNCTION_EXPORT_CMD(cmd_test_hci_rm, hal_hci_rm, hci hal APIs tests)
