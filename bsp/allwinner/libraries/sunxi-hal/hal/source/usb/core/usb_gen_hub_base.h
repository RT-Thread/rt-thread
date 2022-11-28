#ifndef _USB_GEN_HUB_BASE_H_
#define _USB_GEN_HUB_BASE_H_

#include <usb_host_hub.h>

/* use a short timeout for hub/port status fetches */
#define USB_STS_TIMEOUT     300//1000
#define USB_STS_RETRIES     5

static int blinkenlights;
//extern int blinkenlights;
static hal_spinlock_t hub_event_lock;
//extern uint32_t hub_event_lock;
static struct usb_list_head hub_event_list;
//extern  struct list_head hub_event_list;

#define USB_HUB_THREAD_EXIT_FLAG_FALSE  0x00
#define USB_HUB_THREAD_EXIT_FLAG_TRUE   0x01

//用来控制hub thread的
struct hub_thread_context
{
    //USB_OS_KERNEL_EVENT    *hub_thread_complete;    //hub thread的 create,exit的complete
   // USB_OS_KERNEL_EVENT   *hub_thread_event;        //只是用来控制thread的sleep/wakeup
    hal_sem_t   hub_thread_complete;    //hub thread的 create,exit的complete
    hal_sem_t   hub_thread_event;        //只是用来控制thread的sleep/wakeup
    volatile    u32 hub_thread_exit_flag ;                  //hub thread 退出flag
    //如USB_HUB_THREAD_EXIT_FLAG_TRUE
};

static struct hub_thread_context hub_thread_cont;
//extern struct hub_thread_context hub_thread_cont;

int32_t hub_port_status(struct usb_hub *hub, int32_t port1, u16 *status, u16 *change);
int32_t usb_suspend_device(struct usb_host_virt_dev *virt_dev);

int32_t usb_resume_device(struct usb_host_virt_dev *virt_dev);


void hub_quiesce(struct usb_hub *hub);

int32_t hub_suspend(struct usb_interface *intf);
int hub_resume(struct usb_interface *intf);
int remote_wakeup(struct usb_host_virt_dev *udev);

int hub_hub_status(struct usb_hub *hub, u16 *status, u16 *change);


int hub_thread_sleep(struct hub_thread_context *thread_cont);
void hub_thread_wakeup(struct hub_thread_context *thread_cont);


#endif
