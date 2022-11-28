#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <usb/hal_hci.h>
#include <hal_cmd.h>
#include <hal_log.h>

static void show_ed_test_help(void)
{
    printf("Usage: hci_ed_test hci_num test_type\n");
    printf("hci_num  : 0/1\n");
    printf("test_type: test_not_operating\n");
    printf("           : test_j_state\n");
    printf("           : test_k_state\n");
    printf("           : test_se0_nak\n");
    printf("           : test_pack\n");
    printf("           : test_force_enable\n");
    printf("           : test_mask\n");
}

static int cmd_hal_hci_ed_test(int argc, const char **argv)
{
    int hci_num = 0;

    if (argc != 3)
    {
        show_ed_test_help();
        return 0;
    }
    hci_num = atoi(argv[1]);
    if (hci_num != 0 && hci_num != 1)
    {
        printf("err hci_num:%s\n", argv[1]);
        show_ed_test_help();
        return 0;
    }
    ehci_ed_test(hci_num, argv[2], strlen(argv[2]));
    return 0;

}
FINSH_FUNCTION_EXPORT_CMD(cmd_hal_hci_ed_test, __cmd_hci_ed_test, hci hal ed tests)

static void show_hci_dl_adjust(void)
{
    printf("Usage: hci_dl_adjust hci_num driver_level\n");
    printf("hci_num  : 0/1\n");
    printf("driver_level: [0-15]\n");
}

static int cmd_hci_dl_adjust(int argc, const char **argv)
{
    int hci_num = 0;
    int driver_level = 0;

    if (argc != 3)
    {
        show_hci_dl_adjust();
        return 0;
    }
    hci_num = atoi(argv[1]);
    driver_level = atoi(argv[2]);
    if (hci_num != 0 && hci_num != 1)
    {
        printf("hci_num err:%s\n", argv[1]);
        show_ed_test_help();
        return 0;
    }
    if (driver_level < 0 || driver_level > 15)
    {
        printf("driver_level err:%s\n", argv[2]);
        show_ed_test_help();
        return 0;
    }
    ehci_usb_driverlevel_adjust(hci_num, driver_level);
    return 0;

}
FINSH_FUNCTION_EXPORT_CMD(cmd_hci_dl_adjust, __cmd_hci_dl_adjust, hci driver level adjust)

