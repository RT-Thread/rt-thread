/*
 * Enhanced Host Controller Interface (EHCI) driver for USB.
 *
 * Maintainer: Alan Stern <stern@rowland.harvard.edu>
 *
 * Copyright (c) 2000-2004 by David Brownell
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdint.h>
#include <stdio.h>
#include <hal_osal.h>
//#include <aw_types.h>
#include <aw_list.h>
#include <interrupt.h>
#include <usb_gen_hub.h>
#include <sunxi_hal_common.h>

#include "ehci.h"

/*-------------------------------------------------------------------------*/

/*
 * EHCI hc_driver implementation ... experimental, incomplete.
 * Based on the final 1.0 register interface specification.
 *
 * USB 2.0 shows up in upcoming www.pcmcia.org technology.
 * First was PCMCIA, like ISA; then CardBus, which is PCI.
 * Next comes "CardBay", using USB 2.0 signals.
 *
 * Contains additional contributions by Brad Hards, Rory Bolt, and others.
 * Special thanks to Intel and VIA for providing host controllers to
 * test this driver on, and Cypress (including In-System Design) for
 * providing early devices for those host controllers to talk to!
 */

#define DRIVER_AUTHOR "David Brownell"
#define DRIVER_DESC "USB 2.0 'Enhanced' Host Controller (EHCI) Driver"

static const char   hcd_name [] = "ehci_hcd";
uint32_t le32_to_cpu(uint32_t x);


#undef EHCI_URB_TRACE

/* magic numbers that can affect system performance */
#define EHCI_TUNE_CERR      3   /* 0-3 qtd retries; 0 == don't stop */
#define EHCI_TUNE_RL_HS     4   /* nak throttle; see 4.9 */
#define EHCI_TUNE_RL_TT     0
#define EHCI_TUNE_MULT_HS   1   /* 1-3 transactions/uframe; 4.10.3 */
#define EHCI_TUNE_MULT_TT   1
/*
 * Some drivers think it's safe to schedule isochronous transfers more than
 * 256 ms into the future (partly as a result of an old bug in the scheduling
 * code).  In an attempt to avoid trouble, we will use a minimum scheduling
 * length of 512 frames instead of 256.
 */
#define EHCI_TUNE_FLS       1   /* (medium) 512-frame schedule */

/* Initial IRQ latency:  faster than hw default */
static int log2_irq_thresh = 0;     // 0 to 6
//module_param (log2_irq_thresh, int, S_IRUGO);
//MODULE_PARM_DESC (log2_irq_thresh, "log2 IRQ latency, 1-64 microframes");

/* initial park setting:  slower than hw default */
static unsigned park = 0;
//module_param (park, uint, S_IRUGO);
//MODULE_PARM_DESC (park, "park setting; 1-3 back-to-back async packets");

/* for flakey hardware, ignore overcurrent indicators */
//static bool ignore_oc;
//module_param (ignore_oc, bool, S_IRUGO);
//MODULE_PARM_DESC (ignore_oc, "ignore bogus hardware overcurrent indications");

//#define   INTR_MASK (STS_IAA | STS_FATAL | STS_PCD | STS_ERR | STS_INT)

/*-------------------------------------------------------------------------*/

#include "ehci.h"
//#include "pci-quirks.h"

static void compute_tt_budget(u8 budget_table[EHCI_BANDWIDTH_SIZE],
        struct ehci_tt *tt);

/*
 * The MosChip MCS9990 controller updates its microframe counter
 * a little before the frame counter, and occasionally we will read
 * the invalid intermediate value.  Avoid problems by checking the
 * microframe number (the low-order 3 bits); if they are 0 then
 * re-read the register to get the correct value.
 */
static unsigned ehci_moschip_read_frame_index(struct ehci_hcd *ehci)
{
    unsigned uf;

    uf = ehci_readl(ehci, &ehci->regs->frame_index);
    if (unlikely((uf & 7) == 0))
        uf = ehci_readl(ehci, &ehci->regs->frame_index);
    return uf;
}

static inline unsigned ehci_read_frame_index(struct ehci_hcd *ehci)
{
    if (ehci->frame_index_bug)
        return ehci_moschip_read_frame_index(ehci);
    return ehci_readl(ehci, &ehci->regs->frame_index);
}

//#include "ehci-dbg.c"

/*-------------------------------------------------------------------------*/

/*
 * ehci_handshake - spin reading hc until handshake completes or fails
 * @ptr: address of hc register to be read
 * @mask: bits to look at in result of read
 * @done: value of those bits when handshake succeeds
 * @usec: timeout in microseconds
 *
 * Returns negative errno, or zero on success
 *
 * Success happens when the "mask" bits have the specified value (hardware
 * handshake done).  There are two failure modes:  "usec" have passed (major
 * hardware flakeout), or the register reads as all-ones (hardware removed).
 *
 * That last failure should_only happen in cases like physical cardbus eject
 * before driver shutdown. But it also seems to be caused by bugs in cardbus
 * bridge shutdown:  shutting down the bridge before the devices using it.
 */
int ehci_handshake(struct ehci_hcd *ehci, u32 *ptr,
           u32 mask, u32 done, int usec)
{
    u32 result;

    do {
        result = ehci_readl(ehci, ptr);
        if (result == ~(u32)0)      /* card removed */
            return -ENODEV;
        result &= mask;
        if (result == done)
            return 0;
        udelay (1);
        usec--;
    } while (usec > 0);
    return -ETIMEDOUT;
}

/* check TDI/ARC silicon is in host mode */
static int tdi_in_host_mode (struct ehci_hcd *ehci)
{
    u32     tmp;

    tmp = ehci_readl(ehci, &ehci->regs->usbmode);
    return (tmp & 3) == USBMODE_CM_HC;
}

/*
 * Force HC to halt state from unknown (EHCI spec section 2.3).
 * Must be called with interrupts enabled and the lock not held.
 */
int ehci_halt (struct ehci_hcd *ehci)
{
    u32 temp;
    uint32_t cpusr;

    hal_spin_lock(&ehci->lock);

    /* disable any irqs left enabled by previous code */
    ehci_writel(ehci, 0, &ehci->regs->intr_enable);

    //if (ehci_is_TDI(ehci) && !tdi_in_host_mode(ehci)) {
    //  hal_spin_unlock_irqrestore(cpusr);
    //  return 0;
    //}

    /*
     * This routine gets called during probe before ehci->command
     * has been initialized, so we can't rely on its value.
     */
    ehci->command &= ~CMD_RUN;
    temp = ehci_readl(ehci, &ehci->regs->command);
    temp &= ~(CMD_RUN | CMD_IAAD);
    ehci_writel(ehci, temp, &ehci->regs->command);

    hal_spin_unlock(&ehci->lock);
    //synchronize_irq(ehci_to_hcd(ehci)->irq);

    return ehci_handshake(ehci, &ehci->regs->status,
              STS_HALT, STS_HALT, 16 * 125);
}

/* put TDI/ARC silicon into EHCI mode */
static void tdi_reset (struct ehci_hcd *ehci)
{
    u32     tmp;

    tmp = ehci_readl(ehci, &ehci->regs->usbmode);
    tmp |= USBMODE_CM_HC;
    /* The default byte access to MMR space is LE after
     * controller reset. Set the required endian mode
     * for transfer buffers to match the host microprocessor
     */
    if (ehci_big_endian_mmio(ehci))
        tmp |= USBMODE_BE;
    ehci_writel(ehci, tmp, &ehci->regs->usbmode);
}

/*
 * Reset a non-running (STS_HALT == 1) controller.
 * Must be called with interrupts enabled and the lock not held.
 */
int ehci_reset(struct ehci_hcd *ehci)
{
    int retval;
    u32 command = ehci_readl(ehci, &ehci->regs->command);

    command |= CMD_RESET;
    //dbg_cmd (ehci, "reset", command);
    ehci_writel(ehci, command, &ehci->regs->command);
    ehci->rh_state = EHCI_RH_HALTED;
    //ehci->next_statechange = jiffies;
    retval = ehci_handshake(ehci, &ehci->regs->command,
                CMD_RESET, 0, 250 * 1000);

    if (ehci->has_hostpc) {
        ehci_writel(ehci, USBMODE_EX_HC | USBMODE_EX_VBPS,
                &ehci->regs->usbmode_ex);
        ehci_writel(ehci, TXFIFO_DEFAULT, &ehci->regs->txfill_tuning);
    }
    if (retval)
        return retval;

    //if (ehci_is_TDI(ehci))
    //  tdi_reset (ehci);

    ehci->port_c_suspend = ehci->suspended_ports =
            ehci->resuming_ports = 0;
    return retval;
}

/*
 * Idle the controller (turn off the schedules).
 * Must be called with interrupts enabled and the lock not held.
 */
static void ehci_quiesce (struct ehci_hcd *ehci)
{
    u32 temp;
    uint32_t cpusr;

    if (ehci->rh_state != EHCI_RH_RUNNING)
        return;

    /* wait for any schedule enables/disables to take effect */
    temp = (ehci->command << 10) & (STS_ASS | STS_PSS);
    ehci_handshake(ehci, &ehci->regs->status, STS_ASS | STS_PSS, temp,
            16 * 125);

    /* then disable anything that's still active */
    hal_spin_lock(&ehci->lock);
    ehci->command &= ~(CMD_ASE | CMD_PSE);
    ehci_writel(ehci, ehci->command, &ehci->regs->command);
    hal_spin_unlock(&ehci->lock);

    /* hardware can take 16 microframes to turn off ... */
    ehci_handshake(ehci, &ehci->regs->status, STS_ASS | STS_PSS, 0,
            16 * 125);
}

/*-------------------------------------------------------------------------*/

static void end_iaa_cycle(struct ehci_hcd *ehci);
static void end_unlink_async(struct ehci_hcd *ehci);
static void unlink_empty_async(struct ehci_hcd *ehci);
void ehci_work(struct ehci_hcd *ehci);
static void start_unlink_intr(struct ehci_hcd *ehci, struct ehci_qh *qh);
static void end_unlink_intr(struct ehci_hcd *ehci, struct ehci_qh *qh);
static int ehci_port_power(struct ehci_hcd *ehci, int portnum, bool enable);

#define EHCI_QH_COMPLETIONS_DEBUG 0
#if EHCI_QH_COMPLETIONS_DEBUG
#define EHCI_DEBUG_PRINTF(format, args...) \
    printf("[%s:%d] " format "\n", __func__, __LINE__, ##args)
#else
#define EHCI_DEBUG_PRINTF(...)
#endif

#include "ehci-timer.c"
#include "ehci-hub.c"
#include "ehci-mem.c"
#include "ehci-q.c"
#include "ehci-sched.c"
//#include "ehci-sysfs.c"

/*-------------------------------------------------------------------------*/

/* On some systems, leaving remote wakeup enabled prevents system shutdown.
 * The firmware seems to think that powering off is a wakeup event!
 * This routine turns off remote wakeup and everything else, on all ports.
 */
static void ehci_turn_off_all_ports(struct ehci_hcd *ehci)
{
    int port = HCS_N_PORTS(ehci->hcs_params);

    while (port--) {
        hal_spin_unlock(&ehci->lock);
        ehci_port_power(ehci, port, false);
        hal_spin_lock(&ehci->lock);
        ehci_writel(ehci, PORT_RWC_BITS,
                &ehci->regs->port_status[port]);
    }
}

/*
 * Halt HC, turn off all ports, and let the BIOS use the companion controllers.
 * Must be called with interrupts enabled and the lock not held.
 */
static void ehci_silence_controller(struct ehci_hcd *ehci)
{
    ehci_halt(ehci);

    hal_spin_lock(&ehci->lock);
    ehci->rh_state = EHCI_RH_HALTED;
    ehci_turn_off_all_ports(ehci);

    /* make BIOS/etc use companion controller during reboot */
    ehci_writel(ehci, 0, &ehci->regs->configured_flag);

    /* unblock posted writes */
    ehci_readl(ehci, &ehci->regs->configured_flag);
    hal_spin_unlock(&ehci->lock);
}

/* ehci_shutdown kick in for silicon on any bus (not just pci, etc).
 * This forcibly disables dma and IRQs, helping kexec and other cases
 * where the next system software may expect clean state.
 */
static void ehci_shutdown(struct hc_gen_dev *hcd)
{
    struct ehci_hcd *ehci = hcd_to_ehci(hcd);

    /**
     * Protect the system from crashing at system shutdown in cases where
     * usb host is not added yet from OTG controller driver.
     * As ehci_setup() not done yet, so stop accessing registers or
     * variables initialized in ehci_setup()
     */
    if (!ehci->sbrn)
        return;

    hal_spin_lock(&ehci->lock);
    ehci->shutdown = true;
    ehci->rh_state = EHCI_RH_STOPPING;
    ehci->enabled_hrtimer_events = 0;
    hal_spin_unlock(&ehci->lock);

    ehci_silence_controller(ehci);

    osal_timer_stop(ehci->hrtimer);
}

/*-------------------------------------------------------------------------*/

/*
 * ehci_work is called from some interrupts, timers, and so on.
 * it calls driver completion functions, after dropping ehci->lock.
 */
void ehci_work (struct ehci_hcd *ehci)
{
    /* another CPU may drop ehci->lock during a schedule scan while
     * it reports urb completions.  this flag guards against bogus
     * attempts at re-entrant schedule scanning.
     */
    EHCI_DEBUG_PRINTF("ehci->scanning = %d, ehci->async_count = %u, ehci->intr_count = %u, ehci->isoc_count = %u",
                    ehci->scanning, ehci->async_count, ehci->intr_count, ehci->isoc_count);

    if (ehci->scanning) {
        ehci->need_rescan = true;
        return;
    }
    ehci->scanning = true;

 rescan:
    ehci->need_rescan = false;
    if (ehci->async_count)
        scan_async(ehci);
    if (ehci->intr_count > 0)
        scan_intr(ehci);
    if (ehci->isoc_count > 0)
        scan_isoc(ehci);
    if (ehci->need_rescan)
        goto rescan;
    ehci->scanning = false;

    /* the IO watchdog guards against hardware or driver bugs that
     * misplace IRQs, and should let us run completely without IRQs.
     * such lossage has been observed on both VT6202 and VT8235.
     */
    turn_on_io_watchdog(ehci);
}

/*
 * Called when the ehci_hcd module is removed.
 */
void ehci_stop (struct hc_gen_dev *hcd)
{
    struct ehci_hcd     *ehci = hcd_to_ehci (hcd);

    ehci_dbg ("ehci stop\n");

    /* no more interrupts ... */

    //spin_lock_irq(&ehci->lock);
    hal_spin_lock (&ehci->lock);
    ehci->enabled_hrtimer_events = 0;
    hal_spin_unlock (&ehci->lock);
    //spin_unlock_irq(&ehci->lock);

    ehci_quiesce(ehci);
    ehci_silence_controller(ehci);
    ehci_reset (ehci);

    osal_timer_stop(ehci->hrtimer);
    //hrtimer_cancel(&ehci->hrtimer);
    //remove_sysfs_files(ehci);
    //remove_debug_files (ehci);

    /* root hub is shut down separately (first, when possible) */
    hal_spin_lock (&ehci->lock);
    end_free_itds(ehci);
    hal_spin_unlock (&ehci->lock);
    ehci_mem_cleanup (ehci);

    //if (ehci->amd_pll_fix == 1)
    //  usb_amd_dev_put();

    //dbg_status (ehci, "ehci_stop completed",
    //      ehci_readl(ehci, &ehci->regs->status));
}

/* one-time init, only for memory state */
//static int ehci_init(struct usb_hcd *hcd)
int ehci_init(struct hc_gen_dev *hcd)
{
    struct ehci_hcd     *ehci = hcd_to_ehci(hcd);
    u32         temp;
    int         retval;
    u32         hcc_params;
    struct ehci_qh_hw   *hw;

    //spin_lock_init(&ehci->lock);

    /*
     * keep io watchdog by default, those good HCDs could turn off it later
     */
    //ehci->need_io_watchdog = 1;

    //hrtimer_init(&ehci->hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
    //ehci->hrtimer.function = ehci_hrtimer_func;
    //ehci->next_hrtimer_event = EHCI_HRTIMER_NO_EVENT;
    ehci->hrtimer = osal_timer_create("hcd_hrtimer", ehci_hrtimer_func, (void*)ehci,
                    1, OSAL_TIMER_FLAG_ONE_SHOT);

    if (ehci->hrtimer == NULL)
    {
        hal_log_err("PANIC : create timer fail");
    }
    ehci->next_hrtimer_event = EHCI_HRTIMER_NO_EVENT;

    hcc_params = ehci_readl(ehci, &ehci->caps->hcc_params);

    /*
     * by default set standard 80% (== 100 usec/uframe) max periodic
     * bandwidth as required by USB 2.0
     */
    ehci->uframe_periodic_max = 100;

    /*
     * hw default: 1K periodic list heads, one per frame.
     * periodic_size can shrink by USBCMD update if hcc_params allows.
     */
    ehci->periodic_size = DEFAULT_I_TDPS;
    INIT_LIST_HEAD(&ehci->async_unlink);
    INIT_LIST_HEAD(&ehci->async_idle);
    INIT_LIST_HEAD(&ehci->intr_unlink_wait);
    INIT_LIST_HEAD(&ehci->intr_unlink);
    INIT_LIST_HEAD(&ehci->intr_qh_list);
    INIT_LIST_HEAD(&ehci->cached_itd_list);
    INIT_LIST_HEAD(&ehci->cached_sitd_list);
    INIT_LIST_HEAD(&ehci->tt_list);
    INIT_LIST_HEAD(&ehci->wait_free_list);

    if (HCC_PGM_FRAMELISTLEN(hcc_params)) {
        /* periodic schedule size can be smaller than default */
        switch (EHCI_TUNE_FLS) {
        case 0: ehci->periodic_size = 1024; break;
        case 1: ehci->periodic_size = 512; break;
        case 2: ehci->periodic_size = 256; break;
        default:    ;   //BUG();
        }
    }
    if ((retval = ehci_mem_init(ehci)) < 0)
        return retval;

    /* controllers may cache some of the periodic schedule ... */
    if (HCC_ISOC_CACHE(hcc_params))     // full frame cache
        ehci->i_thresh = 0;
    else                    // N microframes cached
        ehci->i_thresh = 2 + HCC_ISOC_THRES(hcc_params);

    /*
     * dedicate a qh for the async ring head, since we couldn't unlink
     * a 'real' qh without stopping the async schedule [4.8].  use it
     * as the 'reclamation list head' too.
     * its dummy is used in hw_alt_next of many tds, to prevent the qh
     * from automatically advancing to the next td after short reads.
     */
    ehci->async->qh_next.qh = NULL;
    hw = ehci->async->hw;
    hw->hw_next = QH_NEXT(ehci, ehci->async->qh_dma);
    //hw->hw_info1 = cpu_to_hc32(ehci, QH_HEAD);
    //hw->hw_token = cpu_to_hc32(ehci, QTD_STS_HALT);
    hw->hw_info1 = QH_HEAD;
    hw->hw_token = QTD_STS_HALT;
    hw->hw_qtd_next = EHCI_LIST_END(ehci);
    ehci->async->qh_state = QH_STATE_LINKED;
    //hw->hw_alt_next = QTD_NEXT(ehci, ehci->async->dummy->qtd_dma);

    /* clear interrupt enables, set irq latency */
    if (log2_irq_thresh < 0 || log2_irq_thresh > 6)
        log2_irq_thresh = 0;
    temp = 1 << (16 + log2_irq_thresh);
    if (HCC_PER_PORT_CHANGE_EVENT(hcc_params)) {
        ehci->has_ppcd = 1;
        ehci_dbg("enable per-port change event\n");
        temp |= CMD_PPCEE;
    }
    if (HCC_CANPARK(hcc_params)) {
        /* HW default park == 3, on hardware that supports it (like
         * NVidia and ALI silicon), maximizes throughput on the async
         * schedule by avoiding QH fetches between transfers.
         *
         * With fast usb storage devices and NForce2, "park" seems to
         * make problems:  throughput reduction (!), data errors...
         */
        if (park) {
            park = min(park, (unsigned) 3);
            temp |= CMD_PARK;
            temp |= park << 8;
        }
        ehci_dbg("park %d\n", park);
    }
    if (HCC_PGM_FRAMELISTLEN(hcc_params)) {
        /* periodic schedule size can be smaller than default */
        temp &= ~(3 << 2);
        temp |= (EHCI_TUNE_FLS << 2);
    }
    ehci->command = temp;
    /* Accept arbitrarily long scatter-gather lists */
    //if (!(hcd->driver->flags & HCD_LOCAL_MEM))
    //  hcd->self.sg_tablesize = ~0;

    /* Prepare for unlinking active QHs */
    ehci->old_current = ~0;
    return 0;
}

/* start HC running; it's halted, ehci_init() has been run (once) */
int ehci_run (struct hc_gen_dev *hcd)
{
    struct ehci_hcd     *ehci = hcd_to_ehci (hcd);
    u32         temp;
    u32         hcc_params;

    hcd->uses_new_polling = 1;

    /* EHCI spec section 4.1 */

    ehci_writel(ehci, ehci->periodic_dma, &ehci->regs->frame_list);
    ehci_writel(ehci, (u32)ehci->async->qh_dma, &ehci->regs->async_next);

    /*
     * hcc_params controls whether ehci->regs->segment must (!!!)
     * be used; it constrains QH/ITD/SITD and QTD locations.
     * pci_pool consistent memory always uses segment zero.
     * streaming mappings for I/O buffers, like pci_map_single(),
     * can return segments above 4GB, if the device allows.
     *
     * NOTE:  the dma mask is visible through dev->dma_mask, so
     * drivers can pass this info along ... like NETIF_F_HIGHDMA,
     * Scsi_Host.highmem_io, and so forth.  It's readonly to all
     * host side drivers though.
     */
    hcc_params = ehci_readl(ehci, &ehci->caps->hcc_params);
    if (HCC_64BIT_ADDR(hcc_params)) {
//#ifdef CONFIG_ARM64
//      ehci_writel(ehci, ehci->periodic_dma >> 32,
//          &ehci->regs->segment);
//      /*
//      * this is deeply broken on almost all architectures
//      * but arm64 can use it so enable it
//      */
//      if (!dma_set_mask(hcd->self.controller, DMA_BIT_MASK(64)))
//          ehci_info(ehci, "enabled 64bit DMA\n");
//#else
        ehci_writel(ehci, 0, &ehci->regs->segment);
//endif
    }


    // Philips, Intel, and maybe others need CMD_RUN before the
    // root hub will detect new devices (why?); NEC doesn't
    ehci->command &= ~(CMD_LRESET|CMD_IAAD|CMD_PSE|CMD_ASE|CMD_RESET);
    ehci->command |= CMD_RUN;
    ehci_writel(ehci, ehci->command, &ehci->regs->command);
    //dbg_cmd (ehci, "init", ehci->command);

    /*
     * Start, enabling full USB 2.0 functionality ... usb 1.1 devices
     * are explicitly handed to companion controller(s), so no TT is
     * involved with the root hub.  (Except where one is integrated,
     * and there's no companion controller unless maybe for USB OTG.)
     *
     * Turning on the CF flag will transfer ownership of all ports
     * from the companions to the EHCI controller.  If any of the
     * companions are in the middle of a port reset at the time, it
     * could cause trouble.  Write-locking ehci_cf_port_reset_rwsem
     * guarantees that no resets are in progress.  After we set CF,
     * a short delay lets the hardware catch up; new resets shouldn't
     * be started before the port switching actions could complete.
     */
    //down_write(&ehci_cf_port_reset_rwsem);
    ehci->rh_state = EHCI_RH_RUNNING;
    ehci_writel(ehci, FLAG_CF, &ehci->regs->configured_flag);
    ehci_readl(ehci, &ehci->regs->command); /* unblock posted writes */
    hal_log_info("--ehci_run: cmd = 0x%x\n", ehci_readl(ehci, &ehci->regs->command));
    hal_msleep(5);
    //up_write(&ehci_cf_port_reset_rwsem);
    //ehci->last_periodic_enable = ktime_get_real();

    temp = HC_VERSION(ehci, ehci_readl(ehci, &ehci->caps->hc_capbase));
    //ehci_info ("USB %x.%x started, EHCI %x.%02x%s\n",
    //  ((ehci->sbrn & 0xf0)>>4), (ehci->sbrn & 0x0f),
    //  temp >> 8, temp & 0xff,
    //  ignore_oc ? ", overcurrent ignored" : "");
    hal_log_info("--ehci_run: hc_capbase = 0x%x\n", temp);
    ehci_info ("USB %x.%x started, EHCI %x.%02x%s\n",
        ((ehci->sbrn & 0xf0)>>4), (ehci->sbrn & 0x0f),
        temp >> 8, temp & 0xff);

    ehci_writel(ehci, INTR_MASK,
            &ehci->regs->intr_enable); /* Turn On Interrupts */

    /* GRR this is run-once init(), being done every time the HC starts.
     * So long as they're part of class devices, we can't do it init()
     * since the class device isn't created that early.
     */
    return 0;
}

int ehci_setup(struct hc_gen_dev *hcd)
{
    struct ehci_hcd *ehci = hcd_to_ehci(hcd);
    int retval;

    ehci->regs = (void *)ehci->caps +
        HC_LENGTH(ehci, ehci_readl(ehci, &ehci->caps->hc_capbase));
    //dbg_hcs_params(ehci, "reset");
    //dbg_hcc_params(ehci, "reset");

    /* cache this readonly data; minimize chip reads */
    ehci->hcs_params = ehci_readl(ehci, &ehci->caps->hcs_params);

    ehci->sbrn = 0x0020;//HCD_USB2;

    /* data structure init */
    retval = ehci_init(hcd);
    if (retval)
        return retval;

    retval = ehci_halt(ehci);
    if (retval) {
        ehci_mem_cleanup(ehci);
        return retval;
    }

    ehci_reset(ehci);

    return 0;
}
//EXPORT_SYMBOL_GPL(ehci_setup);

/*-------------------------------------------------------------------------*/

//irqreturn_t ehci_irq (struct hc_gen_dev *hcd)
irqreturn_t ehci_irq_handler (int dummy, void *dev)
{
    struct hc_gen_dev   *hcd = (struct hc_gen_dev *)dev;
    struct ehci_hcd     *ehci = hcd_to_ehci (hcd);
    u32         status, masked_status, pcd_status = 0, cmd;
    int         bh;
    unsigned long       flags;

    EHCI_DEBUG_PRINTF("");

    /*
     * For threadirqs option we use spin_lock_irqsave() variant to prevent
     * deadlock with ehci hrtimer callback, because hrtimer callbacks run
     * in interrupt context even when threadirqs is specified. We can go
     * back to spin_lock() variant when hrtimer callbacks become threaded.
     */
    flags = hal_spin_lock_irqsave(&ehci->lock);
    status = ehci_readl(ehci, &ehci->regs->status);

    /* e.g. cardbus physical eject */
    if (status == ~(u32) 0) {
        printf("device removed\n");
        goto dead;
    }

    /*
     * We don't use STS_FLR, but some controllers don't like it to
     * remain on, so mask it out along with the other status bits.
     */
    masked_status = status & (INTR_MASK | STS_FLR);

    /* Shared IRQ? */
    if (!masked_status || unlikely(ehci->rh_state == EHCI_RH_HALTED)) {
        hal_spin_unlock_irqrestore(&ehci->lock, flags);
        return IRQ_NONE;
    }

    /* clear (just) interrupts */
    ehci_writel(ehci, masked_status, &ehci->regs->status);
    cmd = ehci_readl(ehci, &ehci->regs->command);
    bh = 0;

    /* normal [4.15.1.2] or error [4.15.1.1] completion */
    if (likely ((status & (STS_INT|STS_ERR)) != 0)) {
        if (likely ((status & STS_ERR) == 0))
            COUNT (ehci->stats.normal);
        else {
            COUNT (ehci->stats.error);
        }
        bh = 1;
    }

    /* complete the unlinking of some qh [4.15.2.3] */
    if (status & STS_IAA) {

        /* Turn off the IAA watchdog */
        ehci->enabled_hrtimer_events &= ~BIT(EHCI_HRTIMER_IAA_WATCHDOG);

        /*
         * Mild optimization: Allow another IAAD to reset the
         * hrtimer, if one occurs before the next expiration.
         * In theory we could always cancel the hrtimer, but
         * tests show that about half the time it will be reset
         * for some other event anyway.
         */
        if (ehci->next_hrtimer_event == EHCI_HRTIMER_IAA_WATCHDOG)
            ++ehci->next_hrtimer_event;

        /* guard against (alleged) silicon errata */
        if (cmd & CMD_IAAD)
            hal_log_info("IAA with IAAD still set?\n");
        if (ehci->iaa_in_progress) {
            COUNT(ehci->stats.iaa);
        }

        hal_log_info("\033[41m WARN : STS_IAA!!!! \033[0m");
        // end_iaa_cycle(ehci);//for test
    }

    /* remote wakeup [4.3.1] */
    if (status & STS_PCD) {
        unsigned    i = HCS_N_PORTS (ehci->hcs_params);
        u32     ppcd = ~0;
{
        int pstatus0 = 0;

        pstatus0 = ehci_readl(ehci, &ehci->regs->port_status[0]);

        if ((pstatus0 & PORT_CONNECT) && (pstatus0 & PORT_CSC))
            printf("\nehci_irq: highspeed device connect \n\n");
        else if (!(pstatus0 & PORT_CONNECT) && (pstatus0 & PORT_CSC))
            printf("\nehci_irq: highspeed device disconnect \n\n");
}

        /* kick root hub later */
        pcd_status = status;

        /* resume root hub? */
        //if (ehci->rh_state == EHCI_RH_SUSPENDED)
        //  usb_hcd_resume_root_hub(hcd);

        /* get per-port change detect bits */
        if (ehci->has_ppcd)
            ppcd = status >> 16;

        while (i--) {
            int pstatus;

            /* leverage per-port change bits feature */
            if (!(ppcd & (1 << i)))
                continue;
            pstatus = ehci_readl(ehci,
                     &ehci->regs->port_status[i]);

            if (pstatus & PORT_OWNER)
                continue;
            if (!(usb_test_bit(i, (volatile uint32_t *)&ehci->suspended_ports) &&
                    ((pstatus & PORT_RESUME) ||
                        !(pstatus & PORT_SUSPEND)) &&
                    (pstatus & PORT_PE) &&
                    ehci->reset_done[i] == 0))
                continue;

            /* start USB_RESUME_TIMEOUT msec resume signaling from
             * this port, and make hub_wq collect
             * PORT_STAT_C_SUSPEND to stop that signaling.
             */
            //ehci->reset_done[i] = jiffies +
            //  msecs_to_jiffies(USB_RESUME_TIMEOUT);
            //set_bit(i, &ehci->resuming_ports);
            printf("port %d remote wakeup\n", i + 1);
            usb_hcd_start_port_resume(&hcd->self, i);
            //mod_timer(&hcd->rh_timer, ehci->reset_done[i]);
        }
    }

    /* PCI errors [4.15.2.4] */
    if (unlikely ((status & STS_FATAL) != 0)) {
        hal_log_err("fatal error\n");
        //dbg_cmd(ehci, "fatal", cmd);
        //dbg_status(ehci, "fatal", status);
dead:
        //usb_hc_died(hcd);

        /* Don't let the controller do anything more */
        ehci->shutdown = true;
        ehci->rh_state = EHCI_RH_STOPPING;
        ehci->command &= ~(CMD_RUN | CMD_ASE | CMD_PSE);
        ehci_writel(ehci, ehci->command, &ehci->regs->command);
        ehci_writel(ehci, 0, &ehci->regs->intr_enable);
        ehci_handle_controller_death(ehci);

        /* Handle completions when the controller stops */
        bh = 0;
    }

    if (bh)
        ehci_work (ehci);
    hal_spin_unlock_irqrestore(&ehci->lock, flags);
    if (pcd_status)
        usb_hcd_poll_rh_status(hcd);
    return IRQ_HANDLED;
}

/*-------------------------------------------------------------------------*/

/*
 * non-error returns are a promise to giveback() the urb later
 * we drop ownership so next owner (or urb unlink) can get it
 *
 * urb + dev is in hcd.self.controller.urb_list
 * we're queueing TDs onto software and hardware lists
 *
 * hcd-specific init for hcpriv hasn't been done yet
 *
 * NOTE:  control, bulk, and interrupt share the same code to append TDs
 * to a (possibly active) QH, and the same QH scanning code.
 */

// 从usb_submit_urb传下来的调用
// 实现了EHCI这一层上HCD(host controller driver)与硬件的读写接口
// 该函数被执行代表driver有数据要与usb交换（收或者发），driver的请求用urb传下来
// EHCI与CPU的数据交换方式是通过在内存中建立一块共享的内存区域，通过DMA的方式实现的
// 数据在usb设备和HC间传输不需要CPU的干预，但是需要CPU告诉HC共享区域的地址和长度信息（还有usb设备的信息）等
// 那么CPU就会把共享内存区域的地址、长度等信息构造成HC能识别的表（iTD,QH,qTD等描述符），再把这些表交给HC
// HC就会按这张表所记录的信息在指定的内存地址处进行数据的传输，传输完成后，以中断的方式通知CPU一次传输的完成

int ehci_urb_enqueue (
    struct hc_gen_dev *hcd,
    struct urb  *urb,
    unsigned    mem_flags
) {
    struct ehci_hcd     *ehci = hcd_to_ehci (hcd);
    struct list_head    qtd_list;

    INIT_LIST_HEAD (&qtd_list);//用于管理EHCI中的qtd数据结构

    switch (usb_pipetype (urb->pipe)) {
    case PIPE_CONTROL:
        /* qh_completions() code doesn't handle all the fault cases
         * in multi-TD control transfers.  Even 1KB is rare anyway.
         */
        if (urb->transfer_buffer_length > (16 * 1024))
            return -EMSGSIZE;
        /* FALLTHROUGH */
    /* case PIPE_BULK: */
    default:
        if (!qh_urb_transaction (ehci, urb, &qtd_list, mem_flags))
            return -ENOMEM;
        return submit_async(ehci, urb, &qtd_list, mem_flags);

    case PIPE_INTERRUPT:
        if (!qh_urb_transaction (ehci, urb, &qtd_list, mem_flags))
            return -ENOMEM;
        return intr_submit(ehci, urb, &qtd_list, mem_flags);

    case PIPE_ISOCHRONOUS:
        if (urb->dev->speed == USB_SPEED_HIGH)
            return itd_submit (ehci, urb, mem_flags);
        else
            return sitd_submit (ehci, urb, mem_flags);
    }
}

/* remove from hardware lists
 * completions normally happen asynchronously
 */
int ehci_urb_dequeue(struct hc_gen_dev *hcd, struct urb *urb)
{
    struct ehci_hcd     *ehci = hcd_to_ehci (hcd);
    struct ehci_qh      *qh;
    unsigned long       flags;
    int         rc;

    flags = hal_spin_lock_irqsave (&ehci->lock);
    rc = usb_hcd_check_unlink_urb(hcd, urb);
    if (rc)
        goto done;

    if (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) {
        /*
         * We don't expedite dequeue for isochronous URBs.
         * Just wait until they complete normally or their
         * time slot expires.
         */
    } else {
        qh = (struct ehci_qh *) urb->hcpriv;
        qh->unlink_reason |= QH_UNLINK_REQUESTED;
        switch (qh->qh_state) {
        case QH_STATE_LINKED:
            if (usb_pipetype(urb->pipe) == PIPE_INTERRUPT)
                start_unlink_intr(ehci, qh);
            else
                start_unlink_async(ehci, qh);
            break;
        case QH_STATE_COMPLETING:
            qh->dequeue_during_giveback = 1;
            break;
        case QH_STATE_UNLINK:
        case QH_STATE_UNLINK_WAIT:
            /* already started */
            break;
        case QH_STATE_IDLE:
            /* QH might be waiting for a Clear-TT-Buffer */
            qh_completions(ehci, qh);
            break;
        }
    }
done:
    hal_spin_unlock_irqrestore(&ehci->lock, flags);
    return rc;
    // return 0;
}

/*-------------------------------------------------------------------------*/

// bulk qh holds the data toggle

//ehci_endpoint_disable (struct usb_hcd *hcd, struct usb_host_endpoint *ep)
void ehci_endpoint_disable (struct hc_gen_dev *hcd, struct usb_host_virt_endpoint *ep)
{
    struct ehci_hcd     *ehci = hcd_to_ehci (hcd);
    unsigned long       flags;
    struct ehci_qh      *qh;

    /* ASSERT:  any requests/urbs are being unlinked */
    /* ASSERT:  nobody can be submitting urbs for this any more */

rescan:
    flags = hal_spin_lock_irqsave (&ehci->lock);
    qh = ep->hcpriv;
    if (!qh)
        goto done;

    /* endpoints can be iso streams.  for now, we don't
     * accelerate iso completions ... so spin a while.
     */
    if (qh->hw == NULL) {
        struct ehci_iso_stream  *stream = ep->hcpriv;

        if (!list_empty(&stream->td_list))
            goto idle_timeout;

        /* BUG_ON(!list_empty(&stream->free_list)); */
        reserve_release_iso_bandwidth(ehci, stream, -1);
        hal_free(stream);
        goto done;
    }

    qh->unlink_reason |= QH_UNLINK_REQUESTED;
    switch (qh->qh_state) {
    case QH_STATE_LINKED:
        if (list_empty(&qh->qtd_list))
            qh->unlink_reason |= QH_UNLINK_QUEUE_EMPTY;
        //else
        //  WARN_ON(1);
        if (usb_endpoint_type(&ep->desc) != USB_ENDPOINT_XFER_INT)
            start_unlink_async(ehci, qh);
        else
            start_unlink_intr(ehci, qh);
        /* FALL THROUGH */
    case QH_STATE_COMPLETING:   /* already in unlinking */
    case QH_STATE_UNLINK:       /* wait for hw to finish? */
    case QH_STATE_UNLINK_WAIT:
idle_timeout:
        hal_spin_unlock_irqrestore(&ehci->lock, flags);
        //schedule_timeout_uninterruptible(1);
        goto rescan;
    case QH_STATE_IDLE:     /* fully unlinked */
        //if (qh->clearing_tt)
        //  goto idle_timeout;
        if (list_empty (&qh->qtd_list)) {
            if (qh->ps.bw_uperiod)
                reserve_release_intr_bandwidth(ehci, qh, -1);
            qh_destroy(ehci, qh);
            break;
        }
        break;
        /* else FALL THROUGH */
    default:
        /* caller was supposed to have unlinked any requests;
         * that's not our job.  just leak this memory.
         */
        ehci_err ("qh %p (#%02x) state %d%s\n",
            qh, ep->desc.bEndpointAddress, qh->qh_state,
            list_empty (&qh->qtd_list) ? "" : "(has tds)");
        break;
    }
 done:
    ep->hcpriv = NULL;
    hal_spin_unlock_irqrestore (&ehci->lock, flags);
}

static void
ehci_endpoint_reset(struct hc_gen_dev *hcd, struct usb_host_virt_endpoint *ep)
{
    struct ehci_hcd     *ehci = hcd_to_ehci(hcd);
    struct ehci_qh      *qh;
    int         eptype = usb_endpoint_type(&ep->desc);
    int         epnum = usb_endpoint_num(&ep->desc);
    int         is_out = usb_endpoint_dir_out(&ep->desc);
    unsigned long       flags;

    if (eptype != USB_ENDPOINT_XFER_BULK && eptype != USB_ENDPOINT_XFER_INT)
        return;

    flags = hal_spin_lock_irqsave(&ehci->lock);
    qh = ep->hcpriv;

    /* For Bulk and Interrupt endpoints we maintain the toggle state
     * in the hardware; the toggle bits in udev aren't used at all.
     * When an endpoint is reset by usb_clear_halt() we must reset
     * the toggle bit in the QH.
     */
    if (qh) {
        if (!list_empty(&qh->qtd_list)) {
            ehci_warn("clear_halt for a busy endpoint\n");
        } else {
            /* The toggle value in the QH can't be updated
             * while the QH is active.  Unlink it now;
             * re-linking will call qh_refresh().
             */
            usb_settoggle(qh->ps.udev, epnum, is_out, 0);
            qh->unlink_reason |= QH_UNLINK_REQUESTED;
            if (eptype == USB_ENDPOINT_XFER_BULK)
                start_unlink_async(ehci, qh);
            else
                start_unlink_intr(ehci, qh);
        }
    }
    hal_spin_unlock_irqrestore(&ehci->lock, flags);
}

int ehci_get_frame (struct hc_gen_dev *hcd)
{
    /*struct ehci_hcd       *ehci = hcd_to_ehci (hcd);
    return (ehci_read_frame_index(ehci) >> 3) % ehci->periodic_size;
    */
    ehci_warn("PANIC : hcd_ops_get_frame() not support now");
    return 0;
}

/*-------------------------------------------------------------------------*/

/* Device addition and removal */

static void ehci_remove_device(struct hc_gen_dev *hcd, struct usb_host_virt_dev *udev)
{
    struct ehci_hcd     *ehci = hcd_to_ehci(hcd);

    //hal_spin_lock(&ehci->lock);
    //drop_tt(udev);
    //hal_spin_unlock(&ehci->lock);
}

/*-------------------------------------------------------------------------*/

#ifdef  CONFIG_PM

/* suspend/resume, section 4.3 */

/* These routines handle the generic parts of controller suspend/resume */

int ehci_suspend(struct usb_hcd *hcd, bool do_wakeup)
{
    struct ehci_hcd     *ehci = hcd_to_ehci(hcd);

    if (time_before(jiffies, ehci->next_statechange))
        msleep(10);

    /*
     * Root hub was already suspended.  Disable IRQ emission and
     * mark HW unaccessible.  The PM and USB cores make sure that
     * the root hub is either suspended or stopped.
     */
    ehci_prepare_ports_for_controller_suspend(ehci, do_wakeup);

    spin_lock_irq(&ehci->lock);
    ehci_writel(ehci, 0, &ehci->regs->intr_enable);
    (void) ehci_readl(ehci, &ehci->regs->intr_enable);

    clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
    spin_unlock_irq(&ehci->lock);

    synchronize_irq(hcd->irq);

    /* Check for race with a wakeup request */
    if (do_wakeup && HCD_WAKEUP_PENDING(hcd)) {
        ehci_resume(hcd, false);
        return -EBUSY;
    }

    return 0;
}
EXPORT_SYMBOL_GPL(ehci_suspend);

/* Returns 0 if power was preserved, 1 if power was lost */
int ehci_resume(struct usb_hcd *hcd, bool force_reset)
{
    struct ehci_hcd     *ehci = hcd_to_ehci(hcd);

    if (time_before(jiffies, ehci->next_statechange))
        msleep(100);

    /* Mark hardware accessible again as we are back to full power by now */
    set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

    if (ehci->shutdown)
        return 0;       /* Controller is dead */

    /*
     * If CF is still set and reset isn't forced
     * then we maintained suspend power.
     * Just undo the effect of ehci_suspend().
     */
    if (ehci_readl(ehci, &ehci->regs->configured_flag) == FLAG_CF &&
            !force_reset) {
        int mask = INTR_MASK;

        ehci_prepare_ports_for_controller_resume(ehci);

        spin_lock_irq(&ehci->lock);
        if (ehci->shutdown)
            goto skip;

        if (!hcd->self.root_hub->do_remote_wakeup)
            mask &= ~STS_PCD;
        ehci_writel(ehci, mask, &ehci->regs->intr_enable);
        ehci_readl(ehci, &ehci->regs->intr_enable);
 skip:
        spin_unlock_irq(&ehci->lock);
        return 0;
    }

    /*
     * Else reset, to cope with power loss or resume from hibernation
     * having let the firmware kick in during reboot.
     */
    usb_root_hub_lost_power(hcd->self.root_hub);
    (void) ehci_halt(ehci);
    (void) ehci_reset(ehci);

    spin_lock_irq(&ehci->lock);
    if (ehci->shutdown)
        goto skip;

    ehci_writel(ehci, ehci->command, &ehci->regs->command);
    ehci_writel(ehci, FLAG_CF, &ehci->regs->configured_flag);
    ehci_readl(ehci, &ehci->regs->command); /* unblock posted writes */

    ehci->rh_state = EHCI_RH_SUSPENDED;
    spin_unlock_irq(&ehci->lock);

    return 1;
}
EXPORT_SYMBOL_GPL(ehci_resume);

#endif

/*-------------------------------------------------------------------------*/
//void ehci_init_driver(struct hc_driver *drv,
//      const struct ehci_driver_overrides *over)
//{
//  /* Copy the generic table to drv and then apply the overrides */
//  *drv = ehci_hc_driver;
//
//  if (over) {
//      drv->hcd_priv_size += over->extra_priv_size;
//      if (over->reset)
//          drv->reset = over->reset;
//      if (over->port_power)
//          drv->port_power = over->port_power;
//  }
//}
//EXPORT_SYMBOL_GPL(ehci_init_driver);
//
///*-------------------------------------------------------------------------*/
//
//MODULE_DESCRIPTION(DRIVER_DESC);
//MODULE_AUTHOR (DRIVER_AUTHOR);
//MODULE_LICENSE ("GPL");

//static int ehci_hcd_init(void)
//{
//  int retval = 0;
//
//  if (usb_disabled())
//      return -ENODEV;
//
//  printk(KERN_INFO "%s: " DRIVER_DESC "\n", hcd_name);
//  set_bit(USB_EHCI_LOADED, &usb_hcds_loaded);
//  if (test_bit(USB_UHCI_LOADED, &usb_hcds_loaded) ||
//          test_bit(USB_OHCI_LOADED, &usb_hcds_loaded))
//      printk(KERN_WARNING "Warning! ehci_hcd should always be loaded"
//              " before uhci_hcd and ohci_hcd, not after\n");
//
//  pr_debug("%s: block sizes: qh %Zd qtd %Zd itd %Zd sitd %Zd\n",
//       hcd_name,
//       sizeof(struct ehci_qh), sizeof(struct ehci_qtd),
//       sizeof(struct ehci_itd), sizeof(struct ehci_sitd));
//
//#ifdef CONFIG_DYNAMIC_DEBUG
//  ehci_debug_root = debugfs_create_dir("ehci", usb_debug_root);
//  if (!ehci_debug_root) {
//      retval = -ENOENT;
//      goto err_debug;
//  }
//#endif
//
//#ifdef PLATFORM_DRIVER
//  retval = platform_driver_register(&PLATFORM_DRIVER);
//  if (retval < 0)
//      goto clean0;
//#endif
//
//#ifdef PS3_SYSTEM_BUS_DRIVER
//  retval = ps3_ehci_driver_register(&PS3_SYSTEM_BUS_DRIVER);
//  if (retval < 0)
//      goto clean2;
//#endif
//
//#ifdef OF_PLATFORM_DRIVER
//  retval = platform_driver_register(&OF_PLATFORM_DRIVER);
//  if (retval < 0)
//      goto clean3;
//#endif
//
//#ifdef XILINX_OF_PLATFORM_DRIVER
//  retval = platform_driver_register(&XILINX_OF_PLATFORM_DRIVER);
//  if (retval < 0)
//      goto clean4;
//#endif
//  return retval;
//
//#ifdef XILINX_OF_PLATFORM_DRIVER
//  /* platform_driver_unregister(&XILINX_OF_PLATFORM_DRIVER); */
//clean4:
//#endif
//#ifdef OF_PLATFORM_DRIVER
//  platform_driver_unregister(&OF_PLATFORM_DRIVER);
//clean3:
//#endif
//#ifdef PS3_SYSTEM_BUS_DRIVER
//  ps3_ehci_driver_unregister(&PS3_SYSTEM_BUS_DRIVER);
//clean2:
//#endif
//#ifdef PLATFORM_DRIVER
//  platform_driver_unregister(&PLATFORM_DRIVER);
//clean0:
//#endif
//#ifdef CONFIG_DYNAMIC_DEBUG
//  debugfs_remove(ehci_debug_root);
//  ehci_debug_root = NULL;
//err_debug:
//#endif
//  clear_bit(USB_EHCI_LOADED, &usb_hcds_loaded);
//  return retval;
//}
//module_init(ehci_hcd_init);

//static void ehci_hcd_cleanup(void)
//{
//#ifdef XILINX_OF_PLATFORM_DRIVER
//  platform_driver_unregister(&XILINX_OF_PLATFORM_DRIVER);
//#endif
//#ifdef OF_PLATFORM_DRIVER
//  platform_driver_unregister(&OF_PLATFORM_DRIVER);
//#endif
//#ifdef PLATFORM_DRIVER
//  platform_driver_unregister(&PLATFORM_DRIVER);
//#endif
//#ifdef PS3_SYSTEM_BUS_DRIVER
//  ps3_ehci_driver_unregister(&PS3_SYSTEM_BUS_DRIVER);
//#endif
//#ifdef CONFIG_DYNAMIC_DEBUG
//  debugfs_remove(ehci_debug_root);
//#endif
//  clear_bit(USB_EHCI_LOADED, &usb_hcds_loaded);
//}
//module_exit(ehci_hcd_cleanup);
