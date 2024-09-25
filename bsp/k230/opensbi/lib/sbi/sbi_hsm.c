/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Atish Patra <atish.patra@wdc.com>
 */

#include <sbi/riscv_asm.h>
#include <sbi/riscv_barrier.h>
#include <sbi/riscv_encoding.h>
#include <sbi/riscv_atomic.h>
#include <sbi/sbi_bitops.h>
#include <sbi/sbi_console.h>
#include <sbi/sbi_domain.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_hartmask.h>
#include <sbi/sbi_hsm.h>
#include <sbi/sbi_init.h>
#include <sbi/sbi_ipi.h>
#include <sbi/sbi_scratch.h>
#include <sbi/sbi_system.h>
#include <sbi/sbi_timer.h>
#include <sbi/sbi_console.h>

static const struct sbi_hsm_device *hsm_dev = NULL;
static unsigned long hart_data_offset;

/** Per hart specific data to manage state transition **/
struct sbi_hsm_data {
	atomic_t state;
	unsigned long suspend_type;
	unsigned long saved_mie;
	unsigned long saved_mip;
};

static inline int __sbi_hsm_hart_get_state(u32 hartid)
{
	struct sbi_hsm_data *hdata;
	struct sbi_scratch *scratch;

	scratch = sbi_hartid_to_scratch(hartid);
	if (!scratch)
		return SBI_EINVAL;

	hdata = sbi_scratch_offset_ptr(scratch, hart_data_offset);
	return atomic_read(&hdata->state);
}

int sbi_hsm_hart_get_state(const struct sbi_domain *dom, u32 hartid)
{
	if (!sbi_domain_is_assigned_hart(dom, hartid))
		return SBI_EINVAL;

	return __sbi_hsm_hart_get_state(hartid);
}

/**
 * Get ulong HART mask for given HART base ID
 * @param dom the domain to be used for output HART mask
 * @param hbase the HART base ID
 * @param out_hmask the output ulong HART mask
 * @return 0 on success and SBI_Exxx (< 0) on failure
 * Note: the output HART mask will be set to zero on failure as well.
 */
int sbi_hsm_hart_interruptible_mask(const struct sbi_domain *dom,
				    ulong hbase, ulong *out_hmask)
{
	int hstate;
	ulong i, hmask, dmask;
	ulong hend = sbi_scratch_last_hartid() + 1;

	*out_hmask = 0;
	if (hend <= hbase)
		return SBI_EINVAL;
	if (BITS_PER_LONG < (hend - hbase))
		hend = hbase + BITS_PER_LONG;

	dmask = sbi_domain_get_assigned_hartmask(dom, hbase);
	for (i = hbase; i < hend; i++) {
		hmask = 1UL << (i - hbase);
		if (dmask & hmask) {
			hstate = __sbi_hsm_hart_get_state(i);
			if (hstate == SBI_HSM_STATE_STARTED ||
			    hstate == SBI_HSM_STATE_SUSPENDED)
				*out_hmask |= hmask;
		}
	}

	return 0;
}

void sbi_hsm_prepare_next_jump(struct sbi_scratch *scratch, u32 hartid)
{
	u32 oldstate;
	struct sbi_hsm_data *hdata = sbi_scratch_offset_ptr(scratch,
							    hart_data_offset);

	oldstate = atomic_cmpxchg(&hdata->state, SBI_HSM_STATE_START_PENDING,
				  SBI_HSM_STATE_STARTED);
	if (oldstate != SBI_HSM_STATE_START_PENDING)
		sbi_hart_hang();
}

static void sbi_hsm_hart_wait(struct sbi_scratch *scratch, u32 hartid)
{
	unsigned long saved_mie;
	struct sbi_hsm_data *hdata = sbi_scratch_offset_ptr(scratch,
							    hart_data_offset);
	/* Save MIE CSR */
	saved_mie = csr_read(CSR_MIE);

	/* Set MSIE bit to receive IPI */
	csr_set(CSR_MIE, MIP_MSIP);

	/* Wait for hart_add call*/
	while (atomic_read(&hdata->state) != SBI_HSM_STATE_START_PENDING) {
		wfi();
	};

	/* Restore MIE CSR */
	csr_write(CSR_MIE, saved_mie);

	/*
	 * No need to clear IPI here because the sbi_ipi_init() will
	 * clear it for current HART via sbi_platform_ipi_init().
	 */
}

const struct sbi_hsm_device *sbi_hsm_get_device(void)
{
	return hsm_dev;
}

void sbi_hsm_set_device(const struct sbi_hsm_device *dev)
{
	if (!dev || hsm_dev)
		return;

	hsm_dev = dev;
}

static bool hsm_device_has_hart_hotplug(void)
{
	if (hsm_dev && hsm_dev->hart_start && hsm_dev->hart_stop)
		return true;
	return false;
}

static bool hsm_device_has_hart_secondary_boot(void)
{
	if (hsm_dev && hsm_dev->hart_start && !hsm_dev->hart_stop)
		return true;
	return false;
}

static int hsm_device_hart_start(u32 hartid, ulong saddr)
{
	if (hsm_dev && hsm_dev->hart_start)
		return hsm_dev->hart_start(hartid, saddr);
	return SBI_ENOTSUPP;
}

static int hsm_device_hart_stop(void)
{
	if (hsm_dev && hsm_dev->hart_stop)
		return hsm_dev->hart_stop();
	return SBI_ENOTSUPP;
}

static int hsm_device_hart_suspend(u32 suspend_type, ulong raddr)
{
	if (hsm_dev && hsm_dev->hart_suspend)
		return hsm_dev->hart_suspend(suspend_type, raddr);
	return SBI_ENOTSUPP;
}

int sbi_hsm_init(struct sbi_scratch *scratch, u32 hartid, bool cold_boot)
{
	u32 i;
	struct sbi_scratch *rscratch;
	struct sbi_hsm_data *hdata;

	if (cold_boot) {
		hart_data_offset = sbi_scratch_alloc_offset(sizeof(*hdata),
							    "HART_DATA");
		if (!hart_data_offset)
			return SBI_ENOMEM;

		/* Initialize hart state data for every hart */
		for (i = 0; i <= sbi_scratch_last_hartid(); i++) {
			rscratch = sbi_hartid_to_scratch(i);
			if (!rscratch)
				continue;

			hdata = sbi_scratch_offset_ptr(rscratch,
						       hart_data_offset);
			ATOMIC_INIT(&hdata->state,
				    (i == hartid) ?
				    SBI_HSM_STATE_START_PENDING :
				    SBI_HSM_STATE_STOPPED);
		}
	} else {
		sbi_hsm_hart_wait(scratch, hartid);
	}

	return 0;
}

void __noreturn sbi_hsm_exit(struct sbi_scratch *scratch)
{
	u32 hstate;
	struct sbi_hsm_data *hdata = sbi_scratch_offset_ptr(scratch,
							    hart_data_offset);
	void (*jump_warmboot)(void) = (void (*)(void))scratch->warmboot_addr;

	hstate = atomic_cmpxchg(&hdata->state, SBI_HSM_STATE_STOP_PENDING,
				SBI_HSM_STATE_STOPPED);
	if (hstate != SBI_HSM_STATE_STOP_PENDING)
		goto fail_exit;

	if (hsm_device_has_hart_hotplug()) {
		hsm_device_hart_stop();
		/* It should never reach here */
		goto fail_exit;
	}

	/**
	 * As platform is lacking support for hotplug, directly jump to warmboot
	 * and wait for interrupts in warmboot. We do it preemptively in order
	 * preserve the hart states and reuse the code path for hotplug.
	 */
	jump_warmboot();

fail_exit:
	/* It should never reach here */
	sbi_printf("ERR: Failed stop hart [%u]\n", current_hartid());
	sbi_hart_hang();
}

int sbi_hsm_hart_start(struct sbi_scratch *scratch,
		       const struct sbi_domain *dom,
		       u32 hartid, ulong saddr, ulong smode, ulong priv)
{
	unsigned long init_count;
	unsigned int hstate;
	struct sbi_scratch *rscratch;
	struct sbi_hsm_data *hdata;

	/* For now, we only allow start mode to be S-mode or U-mode. */
	if (smode != PRV_S && smode != PRV_U)
		return SBI_EINVAL;
	if (dom && !sbi_domain_is_assigned_hart(dom, hartid))
		return SBI_EINVAL;
	if (dom && !sbi_domain_check_addr(dom, saddr, smode,
					  SBI_DOMAIN_EXECUTE))
		return SBI_EINVALID_ADDR;

	rscratch = sbi_hartid_to_scratch(hartid);
	if (!rscratch)
		return SBI_EINVAL;
	hdata = sbi_scratch_offset_ptr(rscratch, hart_data_offset);
	hstate = atomic_cmpxchg(&hdata->state, SBI_HSM_STATE_STOPPED,
				SBI_HSM_STATE_START_PENDING);
	if (hstate == SBI_HSM_STATE_STARTED)
		return SBI_EALREADY;

	/**
	 * if a hart is already transition to start or stop, another start call
	 * is considered as invalid request.
	 */
	if (hstate != SBI_HSM_STATE_STOPPED)
		return SBI_EINVAL;

	init_count = sbi_init_count(hartid);
	rscratch->next_arg1 = priv;
	rscratch->next_addr = saddr;
	rscratch->next_mode = smode;

	if (hsm_device_has_hart_hotplug() ||
	   (hsm_device_has_hart_secondary_boot() && !init_count)) {
		return hsm_device_hart_start(hartid, scratch->warmboot_addr);
	} else {
		sbi_ipi_raw_send(hartid);
	}

	return 0;
}

int sbi_hsm_hart_stop(struct sbi_scratch *scratch, bool exitnow)
{
	int oldstate;
	const struct sbi_domain *dom = sbi_domain_thishart_ptr();
	struct sbi_hsm_data *hdata = sbi_scratch_offset_ptr(scratch,
							    hart_data_offset);

	if (!dom)
		return SBI_EFAIL;

	oldstate = atomic_cmpxchg(&hdata->state, SBI_HSM_STATE_STARTED,
				  SBI_HSM_STATE_STOP_PENDING);
	if (oldstate != SBI_HSM_STATE_STARTED) {
		sbi_printf("%s: ERR: The hart is in invalid state [%u]\n",
			   __func__, oldstate);
		return SBI_EFAIL;
	}

	if (exitnow)
		sbi_exit(scratch);

	return 0;
}

static int __sbi_hsm_suspend_ret_default(struct sbi_scratch *scratch)
{
	/* Wait for interrupt */
	wfi();

	return 0;
}

static void __sbi_hsm_suspend_non_ret_save(struct sbi_scratch *scratch)
{
	struct sbi_hsm_data *hdata = sbi_scratch_offset_ptr(scratch,
							    hart_data_offset);

	/*
	 * We will be resuming in warm-boot path so the MIE and MIP CSRs
	 * will be back to initial state. It is possible that HART has
	 * configured timer event before going to suspend state so we
	 * should save MIE and MIP CSRs and restore it after resuming.
	 *
	 * Further, the M-mode bits in MIP CSR are read-only and set by
	 * external devices (such as interrupt controller) whereas all
	 * VS-mode bits in MIP are read-only alias of bits in HVIP CSR.
	 *
	 * This means we should only save/restore S-mode bits of MIP CSR
	 * such as MIP.SSIP and MIP.STIP.
	 */

	hdata->saved_mie = csr_read(CSR_MIE);
	hdata->saved_mip = csr_read(CSR_MIP) & (MIP_SSIP | MIP_STIP);
}

static void __sbi_hsm_suspend_non_ret_restore(struct sbi_scratch *scratch)
{
	struct sbi_hsm_data *hdata = sbi_scratch_offset_ptr(scratch,
							    hart_data_offset);

	csr_write(CSR_MIE, hdata->saved_mie);
	csr_write(CSR_MIP, (hdata->saved_mip & (MIP_SSIP | MIP_STIP)));
}

static int __sbi_hsm_suspend_non_ret_default(struct sbi_scratch *scratch,
					     ulong raddr)
{
	void (*jump_warmboot)(void) = (void (*)(void))scratch->warmboot_addr;

	/*
	 * Save some of the M-mode CSRs which should be restored after
	 * resuming from suspend state
	 */
	__sbi_hsm_suspend_non_ret_save(scratch);

	/* Wait for interrupt */
	wfi();

	/*
	 * Directly jump to warm reboot to simulate resume from a
	 * non-retentive suspend.
	 */
	jump_warmboot();

	return 0;
}

void sbi_hsm_hart_resume_start(struct sbi_scratch *scratch)
{
	int oldstate;
	struct sbi_hsm_data *hdata = sbi_scratch_offset_ptr(scratch,
							    hart_data_offset);

	/* If current HART was SUSPENDED then set RESUME_PENDING state */
	oldstate = atomic_cmpxchg(&hdata->state, SBI_HSM_STATE_SUSPENDED,
			SBI_HSM_STATE_RESUME_PENDING);
	if (oldstate != SBI_HSM_STATE_SUSPENDED) {
		sbi_printf("%s: ERR: The hart is in invalid state [%u]\n",
			   __func__, oldstate);
		sbi_hart_hang();
	}
}

void sbi_hsm_hart_resume_finish(struct sbi_scratch *scratch)
{
	u32 oldstate;
	struct sbi_hsm_data *hdata = sbi_scratch_offset_ptr(scratch,
							    hart_data_offset);

	/* If current HART was RESUME_PENDING then set STARTED state */
	oldstate = atomic_cmpxchg(&hdata->state, SBI_HSM_STATE_RESUME_PENDING,
				  SBI_HSM_STATE_STARTED);
	if (oldstate != SBI_HSM_STATE_RESUME_PENDING) {
		sbi_printf("%s: ERR: The hart is in invalid state [%u]\n",
			   __func__, oldstate);
		sbi_hart_hang();
	}

	/*
	 * Restore some of the M-mode CSRs which we are re-configured by
	 * the warm-boot sequence.
	 */
	__sbi_hsm_suspend_non_ret_restore(scratch);
}

int sbi_hsm_hart_suspend(struct sbi_scratch *scratch, u32 suspend_type,
			 ulong raddr, ulong rmode, ulong priv)
{
	int oldstate, ret;
	const struct sbi_domain *dom = sbi_domain_thishart_ptr();
	struct sbi_hsm_data *hdata = sbi_scratch_offset_ptr(scratch,
							    hart_data_offset);

	/* For now, we only allow suspend from S-mode or U-mode. */

	/* Sanity check on domain assigned to current HART */
	if (!dom)
		return SBI_EINVAL;

	/* Sanity check on suspend type */
	if (SBI_HSM_SUSPEND_RET_DEFAULT < suspend_type &&
	    suspend_type < SBI_HSM_SUSPEND_RET_PLATFORM)
		return SBI_EINVAL;
	if (SBI_HSM_SUSPEND_NON_RET_DEFAULT < suspend_type &&
	    suspend_type < SBI_HSM_SUSPEND_NON_RET_PLATFORM)
		return SBI_EINVAL;

	/* Additional sanity check for non-retentive suspend */
	if (suspend_type & SBI_HSM_SUSP_NON_RET_BIT) {
		if (rmode != PRV_S && rmode != PRV_U)
			return SBI_EINVAL;
		if (dom && !sbi_domain_check_addr(dom, raddr, rmode,
						  SBI_DOMAIN_EXECUTE))
			return SBI_EINVALID_ADDR;
	}

	/* Save the resume address and resume mode */
	scratch->next_arg1 = priv;
	scratch->next_addr = raddr;
	scratch->next_mode = rmode;

	/* Directly move from STARTED to SUSPENDED state */
	oldstate = atomic_cmpxchg(&hdata->state, SBI_HSM_STATE_STARTED,
				  SBI_HSM_STATE_SUSPENDED);
	if (oldstate != SBI_HSM_STATE_STARTED) {
		sbi_printf("%s: ERR: The hart is in invalid state [%u]\n",
			   __func__, oldstate);
		ret = SBI_EDENIED;
		goto fail_restore_state;
	}

	/* Save the suspend type */
	hdata->suspend_type = suspend_type;

	/* Try platform specific suspend */
	ret = hsm_device_hart_suspend(suspend_type, scratch->warmboot_addr);
	if (ret == SBI_ENOTSUPP) {
		/* Try generic implementation of default suspend types */
		if (suspend_type == SBI_HSM_SUSPEND_RET_DEFAULT) {
			ret = __sbi_hsm_suspend_ret_default(scratch);
		} else if (suspend_type == SBI_HSM_SUSPEND_NON_RET_DEFAULT) {
			ret = __sbi_hsm_suspend_non_ret_default(scratch,
						scratch->warmboot_addr);
		}
	}

fail_restore_state:
	/*
	 * We might have successfully resumed from retentive suspend
	 * or suspend failed. In both cases, we restore state of hart.
	 */
	oldstate = atomic_cmpxchg(&hdata->state, SBI_HSM_STATE_SUSPENDED,
				  SBI_HSM_STATE_STARTED);
	if (oldstate != SBI_HSM_STATE_SUSPENDED) {
		sbi_printf("%s: ERR: The hart is in invalid state [%u]\n",
			   __func__, oldstate);
		sbi_hart_hang();
	}

	return ret;
}
