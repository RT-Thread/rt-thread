#include "rtthread.h"

#if IDLE_THREAD_STACK_SIZE < 2048
#error "IDLE_THREAD_STACK_SIZE must be greater than 2048"
#endif

#ifdef RT_CHERRYUSB_HOST
#include "usbh_core.h"

int usbh_init(int argc, char **argv)
{
    uint8_t busid;
    uint32_t reg_base;

    if (argc < 3) {
        USB_LOG_ERR("please input correct command: usbh_init <busid> <reg_base>\r\n");
        return -1;
    }

    busid = atoi(argv[1]);
    reg_base = strtoll(argv[2], NULL, 16);
    usbh_initialize(busid, reg_base);

    return 0;
}

int usbh_deinit(int argc, char **argv)
{
    uint8_t busid;

    if (argc < 2) {
        USB_LOG_ERR("please input correct command: usbh_deinit <busid>\r\n");
        return -1;
    }

    busid = atoi(argv[1]);
    usbh_deinitialize(busid);

    return 0;
}

MSH_CMD_EXPORT(usbh_init, init usb host);
MSH_CMD_EXPORT(usbh_deinit, deinit usb host);
MSH_CMD_EXPORT(lsusb, ls usb devices);
#endif
