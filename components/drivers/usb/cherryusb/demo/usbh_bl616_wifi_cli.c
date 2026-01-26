#include "usbh_core.h"
#include "usbh_cdc_acm.h"
#include "shell.h"

static USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t cdc_buffer[8 * 1024];

int wifi_scan(int argc, char **argv)
{
    struct usbh_cdc_acm *cdc_acm_class = usbh_find_class_instance("/dev/ttyACM0");
    uint32_t len;
    int ret;

    if (cdc_acm_class == NULL) {
        printf("cdc acm class not found\r\n");
        return -1;
    }

    len = snprintf((char *)cdc_buffer, sizeof(cdc_buffer), "ap_scan\r\n");
    ret = usbh_cdc_acm_bulk_out_transfer(cdc_acm_class, cdc_buffer, len, 3000);
    if (ret < 0) {
        printf("wifi scan failed1, ret:%d\r\n", ret);
        return -1;
    }

    ret = usbh_cdc_acm_bulk_in_transfer(cdc_acm_class, cdc_buffer, sizeof(cdc_buffer), 3000);
    if (ret < 0) {
        printf("wifi scan failed2, ret:%d\r\n", ret);
        return -1;
    }
    cdc_buffer[ret] = '\0';
    printf("%s\r\n", cdc_buffer);
    return 0;
}
CSH_CMD_EXPORT(wifi_scan, wifi_scan);

int wifi_scan_result(int argc, char **argv)
{
    struct usbh_cdc_acm *cdc_acm_class = usbh_find_class_instance("/dev/ttyACM0");
    uint32_t len;
    int ret;

    if (cdc_acm_class == NULL) {
        printf("cdc acm class not found\r\n");
        return -1;
    }

    len = snprintf((char *)cdc_buffer, sizeof(cdc_buffer), "ap_scan_result {\"offset\":0, \"count\":0}\r\n");
    ret = usbh_cdc_acm_bulk_out_transfer(cdc_acm_class, cdc_buffer, len, 3000);
    if (ret < 0) {
        printf("wifi scan failed1, ret:%d\r\n", ret);
        return -1;
    }

    ret = usbh_cdc_acm_bulk_in_transfer(cdc_acm_class, cdc_buffer, sizeof(cdc_buffer), 3000);
    if (ret < 0) {
        printf("wifi scan failed2, ret:%d\r\n", ret);
        return -1;
    }
    cdc_buffer[ret] = '\0';
    printf("%s\r\n", cdc_buffer);
    return 0;
}
CSH_CMD_EXPORT(wifi_scan_result, wifi_scan_result);

int wifi_connect(int argc, char **argv)
{
    struct usbh_cdc_acm *cdc_acm_class = usbh_find_class_instance("/dev/ttyACM0");
    uint32_t len;
    int ret;

    if (cdc_acm_class == NULL) {
        printf("cdc acm class not found\r\n");
        return -1;
    }

    if (argc < 3) {
        printf("please input correct command: wifi_connect ssid password\r\n");
        return -1;
    }

    len = snprintf((char *)cdc_buffer, sizeof(cdc_buffer), "ap_connect {\"ssid\":\"%s\", \"password\":\"%s\"}\r\n", argv[1], argv[2]);
    ret = usbh_cdc_acm_bulk_out_transfer(cdc_acm_class, cdc_buffer, len, 3000);
    if (ret < 0) {
        printf("wifi connect failed1, ret:%d\r\n", ret);
        return -1;
    }
    ret = usbh_cdc_acm_bulk_in_transfer(cdc_acm_class, cdc_buffer, sizeof(cdc_buffer), 3000);
    if (ret < 0) {
        printf("wifi connect failed2, ret:%d\r\n", ret);
        return -1;
    }
    cdc_buffer[ret] = '\0';
    printf("%s\r\n", cdc_buffer);
    return 0;
}
CSH_CMD_EXPORT(wifi_connect, wifi_connect);

int wifi_disconnect(int argc, char **argv)
{
    struct usbh_cdc_acm *cdc_acm_class = usbh_find_class_instance("/dev/ttyACM0");
    uint32_t len;
    int ret;

    if (cdc_acm_class == NULL) {
        printf("cdc acm class not found\r\n");
        return -1;
    }

    len = snprintf((char *)cdc_buffer, sizeof(cdc_buffer), "ap_disconnect\r\n");
    ret = usbh_cdc_acm_bulk_out_transfer(cdc_acm_class, cdc_buffer, len, 3000);
    if (ret < 0) {
        printf("wifi disconnect failed1, ret:%d\r\n", ret);
        return -1;
    }
    ret = usbh_cdc_acm_bulk_in_transfer(cdc_acm_class, cdc_buffer, sizeof(cdc_buffer), 3000);
    if (ret < 0) {
        printf("wifi disconnect failed2, ret:%d\r\n", ret);
        return -1;
    }
    cdc_buffer[ret] = '\0';
    printf("%s\r\n", cdc_buffer);
    return 0;
}
CSH_CMD_EXPORT(wifi_disconnect, wifi_disconnect);

int wifi_status(int argc, char **argv)
{
    struct usbh_cdc_acm *cdc_acm_class = usbh_find_class_instance("/dev/ttyACM0");
    uint32_t len;
    int ret;

    if (cdc_acm_class == NULL) {
        printf("cdc acm class not found\r\n");
        return -1;
    }

    len = snprintf((char *)cdc_buffer, sizeof(cdc_buffer), "ap_status\r\n");
    ret = usbh_cdc_acm_bulk_out_transfer(cdc_acm_class, cdc_buffer, len, 3000);
    if (ret < 0) {
        printf("wifi status failed1, ret:%d\r\n", ret);
        return -1;
    }

    ret = usbh_cdc_acm_bulk_in_transfer(cdc_acm_class, cdc_buffer, sizeof(cdc_buffer), 3000);
    if (ret < 0) {
        printf("wifi status failed2, ret:%d\r\n", ret);
        return -1;
    }
    cdc_buffer[ret] = '\0';
    printf("%s\r\n", cdc_buffer);
    return 0;
}
CSH_CMD_EXPORT(wifi_status, wifi_status);

int wifi_version(int argc, char **argv)
{
    struct usbh_cdc_acm *cdc_acm_class = usbh_find_class_instance("/dev/ttyACM0");
    uint32_t len;
    int ret;

    if (cdc_acm_class == NULL) {
        printf("cdc acm class not found\r\n");
        return -1;
    }

    len = snprintf((char *)cdc_buffer, sizeof(cdc_buffer), "sys_version\r\n");
    ret = usbh_cdc_acm_bulk_out_transfer(cdc_acm_class, cdc_buffer, len, 3000);
    if (ret < 0) {
        printf("wifi status failed1, ret:%d\r\n", ret);
        return -1;
    }

    ret = usbh_cdc_acm_bulk_in_transfer(cdc_acm_class, cdc_buffer, sizeof(cdc_buffer), 3000);
    if (ret < 0) {
        printf("wifi status failed2, ret:%d\r\n", ret);
        return -1;
    }
    cdc_buffer[ret] = '\0';
    printf("%s\r\n", cdc_buffer);
    return 0;
}
CSH_CMD_EXPORT(wifi_version, wifi_version);