/** @file sbi.h
 * 
 * @brief This file contains IF layer definitions.
 *  
 *  Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */
/********************************************************
Change log:
	10/11/05: Add Doxygen format comments
	01/05/06: Add kernel 2.6.x support	
	
********************************************************/

#ifndef	_SBI_H_
#define	_SBI_H_

/**Bit Definition*/
#define B_BIT_0		0x01
#define B_BIT_1		0x02
#define B_BIT_2		0x04
#define B_BIT_3		0x08
#define B_BIT_4		0x10
#define B_BIT_5		0x20
#define B_BIT_6		0x40
#define B_BIT_7		0x80
#define B_BIT_8		0x100
#define B_BIT_9		0X200
#define B_BIT_10	0x400

/** INT Status Bit Definition*/
#define HIS_RxUpLdRdy			B_BIT_0
#define HIS_TxDnLdRdy			B_BIT_1
#define HIS_CmdDnLdRdy			B_BIT_2
#define HIS_CardEvent			B_BIT_3
#define HIS_CmdUpLdRdy			B_BIT_4
#define HIS_WrFifoOvrflow		B_BIT_5
#define HIS_RdFifoUndrflow		B_BIT_6
#define HIS_WlanReady			B_BIT_7

#define	HIM_DISABLE			0xff
#define HIM_ENABLE			0x03

#define FIRMWARE_READY			0xfedc
#ifndef DEV_NAME_LEN
#define DEV_NAME_LEN			32
#endif
#define MAXKEYLEN			13

/* The number of times to try when polling for status bits */
#define MAX_POLL_TRIES			100

/* The number of times to try when waiting for downloaded firmware to 
     become active. (polling the scratch register). */

#define MAX_FIRMWARE_POLL_TRIES		100

#define FIRMWARE_TRANSFER_NBLOCK	2
#define SBI_EVENT_CAUSE_SHIFT		3

#define GSPI_BUS_DELAY_TIME_MODE	1
#define GSPI_BUS_DELAY_CLK_MODE		0

typedef enum _mv_sd_type
{
    MVSD_DAT = 0,
    MVSD_CMD = 1,
    MVSD_EVENT = 3
} mv_sd_type;

/** Function Prototype Declaration */
typedef wlan_private *(*wlan_notifier_fn_add) (void *dev_id);
typedef int (*wlan_notifier_fn_remove) (void *dev_id);

//typedef IRQ_RET_TYPE(*isr_notifier_fn_t) (s32 irq, void *dev_id,struct pt_regs * reg);
typedef IRQ_RET_TYPE(*isr_notifier_fn_t) (s32 irq, void *dev_id,void* reg);
typedef IRQ_RET_TYPE(*handler_fn_t) (s32 irq, void *dev_id, void *);

/* Probe and Check if the card is present*/
int sbi_probe_card(void *card);
int sbi_register_dev(wlan_private * priv);
int sbi_disable_host_int(wlan_private * priv);
int sbi_get_int_status(wlan_private * priv, u8 *);
int sbi_register(wlan_notifier_fn_add, wlan_notifier_fn_remove, void *);
void sbi_unregister(void);
int sbi_prog_firmware(wlan_private *);
//int sbi_verify_fw_download(wlan_private *);

int sbi_prog_helper(wlan_private *);
int sbi_prog_firmware_w_helper(wlan_private *);

int sbi_read_event_cause(wlan_private *);
//int sbi_host_to_card(wlan_private * priv, u8 type, u8 * payload, u16 nb);
int sbi_card_to_host(wlan_private * priv, u32 type, u32 * nb, u8 * payload,
                     u16 npayload);
int sbi_enable_host_int(wlan_private *);

int sbi_exit_deep_sleep(wlan_private *);
int sbi_reset_deepsleep_wakeup(wlan_private *);
#ifdef ENABLE_PM
int sbi_suspend(wlan_private *);
int sbi_resume(wlan_private *);
#endif

int sbi_get_cis_info(wlan_private * priv);

#endif /* _SBI_H */
