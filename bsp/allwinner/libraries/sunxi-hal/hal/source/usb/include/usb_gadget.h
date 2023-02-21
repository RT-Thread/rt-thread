#ifndef __USB_GADGET_H__
#define __USB_GADGET_H__

#ifdef __cplusplus
extern "C" {
#endif

enum {
    USB_GADGET_MANUFACTURER_IDX     = 0,
    USB_GADGET_PRODUCT_IDX,
    USB_GADGET_SERIAL_IDX,
    USB_GADGET_LANGUAGE_IDX,
    USB_GADGET_CONFIG_IDX,
    USB_GADGET_INTERFACE_IDX,
    USB_GADGET_MAX_IDX,
};

int usb_gadget_function_enable(const char *name);
int usb_gadget_function_disable(void);
int usb_gadget_function_read(int ep_idx, char *buf, int size);
int usb_gadget_function_write(int ep_idx, char *buf, int size);
int usb_gadget_function_string_set(char *name, char *str, unsigned int idx);

#ifdef __cplusplus
}
#endif

#endif /* __USB_GADGET_H__ */
