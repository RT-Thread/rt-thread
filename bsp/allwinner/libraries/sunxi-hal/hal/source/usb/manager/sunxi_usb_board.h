#ifndef __SUNXI_USB_BOARD_H__
#define __SUNXI_USB_BOARD_H__

#define  SET_USB0               "usbc0"
#define  KEY_USB_ENABLE         "usb_used"
#define  KEY_USB_PORT_TYPE          "usb_port_type"
#define  KEY_USB_DET_TYPE           "usb_detect_type"
#define  KEY_USB_DET_MODE           "usb_detect_mode"
#define  KEY_USB_DETVBUS_GPIO           "usb_det_vbus_gpio"
#define  KEY_USB_ID_GPIO            "usb_id_gpio"

#define  KEY_USB_DRVVBUS_GPIO           "usb_drv_vbus_gpio"
#define  KEY_USB_REGULATOR_IO           "usb_regulator_io"
#define  KEY_USB_REGULATOR_IO_VOL       "usb_regulator_vol"
#define  KEY_USB_REGULATOR_ID_VBUS      "usb_regulator_id_vbus"
#define  KEY_USB_REGULATOR_ID_VBUS_VOL      "usb_regulator_id_vbus_vol"
#define  KEY_USB_WAKEUP_SUSPEND             "usb_wakeup_suspend"

/* USB config info */
enum usb_gpio_group_type
{
    GPIO_GROUP_TYPE_PIO = 0,
    GPIO_GROUP_TYPE_POWER,
};

/* 0: device only; 1: host only; 2: otg */
enum usb_port_type
{
    USB_PORT_TYPE_DEVICE = 0,
    USB_PORT_TYPE_HOST,
    USB_PORT_TYPE_OTG,
};

/* 0: dp/dm detect, 1: vbus/id detect */
enum usb_detect_type
{
    USB_DETECT_TYPE_DP_DM = 0,
    USB_DETECT_TYPE_VBUS_ID,
};

/* 0: thread scan mode; 1: gpio interrupt mode */
enum usb_detect_mode
{
    USB_DETECT_MODE_THREAD = 0,
    USB_DETECT_MODE_INTR,
};

enum usb_det_vbus_type
{
    USB_DET_VBUS_TYPE_NULL = 0,
    USB_DET_VBUS_TYPE_GPIO,
    USB_DET_VBUS_TYPE_AXP,
};

enum usb_id_type
{
    USB_ID_TYPE_NULL = 0,
    USB_ID_TYPE_GPIO,
    USB_ID_TYPE_AXP,
};
/*
 * struct gpio_config - gpio config info
 * @gpio:      gpio global index, must be unique
 * @mul_sel:   multi sel val: 0 - input, 1 - output.
 * @pull:      pull val: 0 - pull up/down disable, 1 - pull up
 * @drv_level: driver level val: 0 - level 0, 1 - level 1
 * @data:      data val: 0 - low, 1 - high, only valid when mul_sel is input/output
 */
struct gpio_config
{
    unsigned int data;
    unsigned int gpio;
    unsigned int mul_sel;
    unsigned int pull;
    unsigned int drv_level;
};

/* pio info */
typedef struct usb_gpio
{
    unsigned int valid; /* pio valid, 1 - valid, 0 - invalid */
    struct gpio_config gpio_set;
} usb_gpio_t;

typedef struct usb_port_info
{
    unsigned int enable;                /* port valid */

    //  unsigned int port_no;               /* usb port number */
    enum usb_port_type port_type;       /* usb port type */
    enum usb_detect_type detect_type;   /* usb detect type */
    enum usb_detect_mode detect_mode;   /* usb detect mode */
    enum usb_det_vbus_type det_vbus_type;
    enum usb_id_type id_type;
    const char *det_vbus_name;
    const char *id_name;
    usb_gpio_t id;              /* usb id pin info */
    usb_gpio_t det_vbus;            /* usb vbus pin info */
    usb_gpio_t drv_vbus;            /* usb drv_vbus pin info */
    usb_gpio_t restrict_gpio_set;       /* usb drv_vbus pin info */
    unsigned int usb_restrict_flag;     /* usb port number(?) */
    unsigned int voltage;               /* usb port number(?) */
    unsigned int capacity;              /* usb port number(?) */

    int id_irq_num;             /* id gpio irq num */
} usb_port_info_t;

typedef struct usb_cfg
{
    unsigned int usb_global_enable;
    unsigned int usbc_num;

    struct usb_port_info port;
} usb_cfg_t;

#endif /* __SUNXI_USB_BOARD_H__ */
