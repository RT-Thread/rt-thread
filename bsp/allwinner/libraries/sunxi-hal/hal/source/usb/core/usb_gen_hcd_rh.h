#ifndef _USB_GEN_HCD_RH_H_
#define _USB_GEN_HCD_RH_H_




void rh_timer_func(void *timer_para_hcd);
int rh_urb_enqueue(struct hc_gen_dev *hcd, struct urb *urb);
int rh_urb_dequeue(struct hc_gen_dev *hcd, struct urb *urb);


#endif
