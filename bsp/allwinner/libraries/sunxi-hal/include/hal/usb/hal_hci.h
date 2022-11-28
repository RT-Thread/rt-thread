#ifndef SUNXI_HAL_HCI_H
#define SUNXI_HAL_HCI_H
#ifdef __cplusplus
extern "C" {
#endif

int hal_usb_core_init(void);

int hal_usb_core_exit(void);

void hal_usb_hci_init(void);

int hal_usb_hcd_init(int hci_num);

int hal_usb_hcd_deinit(int hci_num);

unsigned int ehci_ed_test(int hci_num, const char *buf, unsigned int count);
unsigned int ehci_usb_driverlevel_adjust(int hci_num, int driverlevel);
#ifdef __cplusplus
}
#endif

#endif
