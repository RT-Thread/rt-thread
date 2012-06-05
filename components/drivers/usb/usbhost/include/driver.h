#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <rtthread.h>

enum uclass_type
{
	rt_usb_Class_MassStor = 0,
	rt_usb_Class_Hid,
	rt_usb_Class_Hub,	
};

struct uclass_driver
{
	rt_list_t list;
	int class_code;
	int subclass_code;
	
	rt_err_t (*run)(void* arg);
	rt_err_t (*stop)(void* arg);

	void* user_data;
};
typedef struct uclass_driver* ucd_t;

struct uprotocal
{
	rt_list_t list;
	int pro_id;
	
	rt_err_t (*init)(void* arg);
	rt_err_t (*callback)(void* arg);	
};
typedef struct uprotocal* uprotocal_t;

rt_err_t rt_usb_class_driver_init(void);
rt_err_t rt_usb_class_driver_register(ucd_t drv);
rt_err_t rt_usb_class_driver_unregister(ucd_t drv);
rt_err_t rt_usb_class_driver_run(ucd_t drv, void* args);
rt_err_t rt_usb_class_driver_stop(ucd_t drv, void* args);
ucd_t rt_usb_class_driver_find(int class_code, int subclass_code);

#endif
