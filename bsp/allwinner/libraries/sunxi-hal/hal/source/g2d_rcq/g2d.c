/*
 * g2d_rcq/g2d_driver/g2d.c
 *
 * Copyright (c) 2007-2019 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <hal_mem.h>
#include <hal_cache.h>
#include <stdlib.h>
#include <string.h>
#include <interrupt.h>
#include <init.h>
#include <hal_clk.h>
#include <hal_reset.h>
#include <hal_timer.h>
// #include <melis/standby/standby.h>

#include "g2d_driver_i.h"
#include "g2d_top.h"
#include "g2d_mixer.h"
#include "g2d_rotate.h"

#define SUNXI_GIC_START 32

#if defined(CONFIG_ARCH_SUN8IW19)
#define SUNXI_IRQ_G2D				(SUNXI_GIC_START + 21)
#define SUNXI_G2D_START				0x01480000
#define SUNXI_G2D_RESET_ID			0
#define SUNXI_G2D_CLK_ID			HAL_CLK_PERIPH_G2D
#define SUNXI_G2D_CLK_BUS_ID			(hal_clk_id_t)(-1)
#define SUNXI_G2D_CLK_MBUS_ID			(hal_clk_id_t)(-1)
#define SUNXI_G2D_CLK_PARENT			HAL_CLK_PLL_PERI1

#elif defined(CONFIG_SOC_SUN20IW1)
#define SUNXI_IRQ_G2D				105
#define SUNXI_G2D_START				0x05410000
#define RESET_IOMMU
#define G2D_IOMMU_MASTER_ID			3
#define IOMMU_RESET_REG                         0x02010010
#define IOMMU_BGR_REG                           0x020017bc
#endif

#ifndef SUNXI_G2D_CLK_ID
#define SUNXI_G2D_CLK_ID			CLK_G2D
#endif
#ifndef SUNXI_G2D_RESET_ID
#define SUNXI_G2D_RESET_ID			RST_BUS_G2D
#endif
#ifndef SUNXI_G2D_CLK_BUS_ID
#define SUNXI_G2D_CLK_BUS_ID			CLK_BUS_G2D
#endif
#ifndef SUNXI_G2D_CLK_MBUS_ID
#define SUNXI_G2D_CLK_MBUS_ID			CLK_MBUS_G2D
#endif
#ifndef SUNXI_G2D_CLK_PARENT
#define SUNXI_G2D_CLK_PARENT			CLK_PLL_PERIPH0_2X
#endif

enum g2d_scan_order scan_order;
hal_sem_t global_lock;
u32 g_time_info;
u32 g_func_runtime;
__g2d_drv_t g2d_ext_hd;
__g2d_info_t para;

__u32 dbg_info;

void *g2d_malloc(__u32 bytes_num, __u32 *phy_addr)
{

	char* vir_addr;

	if (bytes_num != 0) {
		vir_addr = hal_malloc_align(bytes_num, CACHELINE_LEN);
		if(vir_addr!=NULL){
			*phy_addr = __va_to_pa((unsigned long)vir_addr);
			memset((void *)vir_addr, 0, bytes_num);
			hal_dcache_clean((unsigned long)vir_addr, bytes_num);
			return vir_addr;
		}
		G2D_ERR_MSG("hal_malloc fail!\n");
		return NULL;
	}
	G2D_ERR_MSG("size is zero\n");

	return NULL;
}

void g2d_free(void *virt_addr, void *phy_addr, unsigned int size)
{

	if (virt_addr == NULL)
		return;
	hal_free_align(virt_addr);
}

int g2d_mutex_lock(hal_sem_t sem)
{
    return hal_sem_wait(sem);
}

int g2d_mutex_unlock(hal_sem_t sem)
{
    return hal_sem_post(sem);
}

__s32 g2d_byte_cal(__u32 format, __u32 *ycnt, __u32 *ucnt, __u32 *vcnt)
{
	*ycnt = 0;
	*ucnt = 0;
	*vcnt = 0;
	if (format <= G2D_FORMAT_BGRX8888)
		*ycnt = 4;

	else if (format <= G2D_FORMAT_BGR888)
		*ycnt = 3;

	else if (format <= G2D_FORMAT_BGRA5551)
		*ycnt = 2;

	else if (format <= G2D_FORMAT_BGRA1010102)
		*ycnt = 4;

	else if (format <= 0x23) {
		*ycnt = 2;
	}

	else if (format <= 0x25) {
		*ycnt = 1;
		*ucnt = 2;
	}

	else if (format == 0x26) {
		*ycnt = 1;
		*ucnt = 1;
		*vcnt = 1;
	}

	else if (format <= 0x29) {
		*ycnt = 1;
		*ucnt = 2;
	}

	else if (format == 0x2a) {
		*ycnt = 1;
		*ucnt = 1;
		*vcnt = 1;
	}

	else if (format <= 0x2d) {
		*ycnt = 1;
		*ucnt = 2;
	}

	else if (format == 0x2e) {
		*ycnt = 1;
		*ucnt = 1;
		*vcnt = 1;
	}

	else if (format == 0x30)
		*ycnt = 1;

	else if (format <= 0x36) {
		*ycnt = 2;
		*ucnt = 4;
	}

	else if (format <= 0x39)
		*ycnt = 6;
	return 0;
}


/**
 */
__u32 cal_align(__u32 width, __u32 align)
{
	switch (align) {
	case 0:
		return width;
	case 4:
		return (width + 3) >> 2 << 2;
	case 8:
		return (width + 7) >> 3 << 3;
	case 16:
		return (width + 15) >> 4 << 4;
	case 32:
		return (width + 31) >> 5 << 5;
	case 64:
		return (width + 63) >> 6 << 6;
	case 128:
		return (width + 127) >> 7 << 7;
	default:
		return (width + 31) >> 5 << 5;
	}
}


__s32 g2d_image_check(g2d_image_enh *p_image)
{
	__s32 ret = -EINVAL;

	if (!p_image) {
		G2D_ERR_MSG("NUll pointer!\n");
		goto OUT;
	}

	if (((p_image->clip_rect.x < 0) &&
	     ((-p_image->clip_rect.x) > p_image->clip_rect.w)) ||
	    ((p_image->clip_rect.y < 0) &&
	     ((-p_image->clip_rect.y) > p_image->clip_rect.h)) ||
	    ((p_image->clip_rect.x > 0) &&
	     (p_image->clip_rect.x > p_image->width - 1)) ||
	    ((p_image->clip_rect.y > 0) &&
	     (p_image->clip_rect.y > p_image->height - 1))) {
		G2D_ERR_MSG("Invalid imager parameter setting\n");
		goto OUT;
	}

	if (((p_image->clip_rect.x < 0) &&
				((-p_image->clip_rect.x) <
				 p_image->clip_rect.w))) {
		p_image->clip_rect.w =
			p_image->clip_rect.w +
			p_image->clip_rect.x;
		p_image->clip_rect.x = 0;
	} else if ((p_image->clip_rect.x +
				p_image->clip_rect.w)
			> p_image->width) {
		p_image->clip_rect.w =
			p_image->width -
			p_image->clip_rect.x;
	}
	if (((p_image->clip_rect.y < 0) &&
				((-p_image->clip_rect.y) <
				 p_image->clip_rect.h))) {
		p_image->clip_rect.h =
			p_image->clip_rect.h +
			p_image->clip_rect.y;
		p_image->clip_rect.y = 0;
	} else if ((p_image->clip_rect.y +
				p_image->clip_rect.h)
			> p_image->height) {
		p_image->clip_rect.h =
			p_image->height -
			p_image->clip_rect.y;
	}

	p_image->bpremul = 0;
	p_image->bbuff = 1;
	p_image->gamut = G2D_BT709;
	ret = 0;
OUT:
	return ret;

}

int g2d_blit_h(g2d_blt_h *para)
{
	int ret = -1;

	ret = g2d_rotate_set_para(&para->src_image_h,
			    &para->dst_image_h,
			    para->flag_h);

	return ret;
}

#ifdef RESET_IOMMU
/**
 * g2d could cause iommu stop, when iommu stop, g2d could not work, we should reset iommu.
 */
static void reset_iommu(void)
{
	int tmp;
	int ret;
	uint32_t regval;
	*(volatile uint32_t *)(IOMMU_BGR_REG) = 0x1;
	regval = (*(volatile uint32_t *)(IOMMU_RESET_REG));

	*(volatile uint32_t *)(IOMMU_RESET_REG) = regval & (~(1 << G2D_IOMMU_MASTER_ID));
	regval = (*(volatile uint32_t *)(IOMMU_RESET_REG));
	if (!(regval & ((1 << G2D_IOMMU_MASTER_ID)))) {
		*(volatile uint32_t *)(IOMMU_RESET_REG) = regval | ((1 << G2D_IOMMU_MASTER_ID));
	}
	regval = (*(volatile uint32_t *)(IOMMU_RESET_REG));

	*(volatile uint32_t *)(IOMMU_BGR_REG) = 0;
	return;
}
#else
static void reset_iommu(void)
{
}
#endif

int g2d_wait_cmd_finish(unsigned int timeout)
{
	int ret;
	ret = hal_sem_timedwait(g2d_ext_hd.queue_sem,timeout* 10);
	if (ret < 0) {
		reset_iommu();
		g2d_bsp_reset();
		G2D_ERR_MSG("G2D irq pending flag timeout\n");
		g2d_ext_hd.finish_flag = 1;
		//wake_up(&g2d_ext_hd.queue);
		return -1;
	}
	g2d_ext_hd.finish_flag = 0;

	return 0;
}

irqreturn_t g2d_handle_irq(int irq, void *dev_id)
{
#if G2D_MIXER_RCQ_USED == 1
	if (g2d_top_rcq_task_irq_query()) {
		// g2d_top_mixer_reset();
		g2d_ext_hd.finish_flag = 1;
		hal_sem_post(g2d_ext_hd.queue_sem);
		return IRQ_HANDLED;
	}
#else
	if (g2d_mixer_irq_query()) {
		// g2d_top_mixer_reset();
		g2d_ext_hd.finish_flag = 1;
		hal_sem_post(g2d_ext_hd.queue_sem);
		return IRQ_HANDLED;
	}
#endif
	if (g2d_rot_irq_query()) {
		// g2d_top_rot_reset();
		g2d_ext_hd.finish_flag = 1;
		hal_sem_post(g2d_ext_hd.queue_sem);
		return IRQ_HANDLED;
	}

	return IRQ_HANDLED;
}

int g2d_clk_init(__g2d_info_t *info)
{
	int i;
	int ret;
	hal_reset_id_t rst_id;
	hal_reset_type_t reset_type = HAL_SUNXI_RESET;
	hal_clk_type_t clk_type = HAL_SUNXI_CCU;
	hal_clk_id_t clk_id[G2D_CLK_NUM] = {
			SUNXI_G2D_CLK_ID,/*note SUNXI_G2D_CLK_ID must be here, please see g2d_clock_enable*/
			SUNXI_G2D_CLK_BUS_ID,
			SUNXI_G2D_CLK_MBUS_ID,
	};
	info->clk_rate = 300000000; /*300Mhz*/
	info->reset = hal_reset_control_get(reset_type, SUNXI_G2D_RESET_ID);
	hal_reset_control_deassert(info->reset);
	info->clk_parent= hal_clock_get(clk_type,SUNXI_G2D_CLK_PARENT);
	for(i = 0; i < G2D_CLK_NUM; i++) {
		if (clk_id[i] != (hal_clk_id_t)-1) {
			info->clk[i] = hal_clock_get(clk_type, clk_id[i]);
		}
	}
	ret = hal_clk_set_parent(info->clk[0], info->clk_parent);
	if (ret)
		G2D_ERR_MSG("set clk:%d's parent:%d fail!\n", info->clk, info->clk_parent);
	return ret;
}

int g2d_clk_exit(__g2d_info_t *info)
{
	int i = 0;
	for(i = 0; i < G2D_CLK_NUM; i++) {
		hal_clock_put(info->clk[i]);
	}

	hal_reset_control_put(info->reset);

	return 0;
}

int g2d_clock_enable(__g2d_info_t *info)
{
	int ret = -1;
	int i = 0;
	ret = hal_reset_control_deassert(info->reset);
	if (ret) {
		G2D_ERR_MSG("deassert rst fail:%d\n", ret);
		goto OUT;
	}

	ret = hal_clock_enable(info->clk_parent);
	if (ret) {
		G2D_ERR_MSG("Enable clk parent fail:%d\n", ret);
		goto OUT;
	}

	ret = hal_clk_set_rate(info->clk[0], info->clk_rate);
	if (ret) {
		G2D_ERR_MSG("Set clk rate fail:%d:%u!\n", info->clk[0], (unsigned int)info->clk_rate);
		goto OUT;
	}

	for(i = 0; i < G2D_CLK_NUM; i++) {
		ret = hal_clock_enable(info->clk[i]);
		if (ret) {
			G2D_ERR_MSG("Enable clk %d fail:%d\n", i, ret);
			goto OUT;
		}
	}

OUT:
	return ret;
}

static int g2d_clock_disable(__g2d_info_t *info)
{
	int ret = -1;
	int i;
	for(i = 0; i < G2D_CLK_NUM; i++) {
		ret = hal_clock_disable(info->clk[i]);
		if (ret) {
			G2D_ERR_MSG("Disable clk %d fail:%d\n", i, ret);
			goto OUT;
		}
	}

	ret = hal_reset_control_assert(info->reset);
	if (ret) {
		G2D_ERR_MSG("assert rst fail:%d\n", ret);
		goto OUT;
	}
OUT:
	return  ret;
}
__s32 drv_g2d_init(__g2d_info_t *info)
{
	int ret;
	memset(&g2d_ext_hd, 0, sizeof(__g2d_drv_t));

	g2d_ext_hd.queue_sem = hal_sem_create(0);
	if (g2d_ext_hd.queue_sem == NULL)
	{
		G2D_ERR_MSG("create g2d_ext_hd.queue_sem failed\n");
		return -1;
	}


	g2d_top_set_base((__u32)info->io);
	g2d_rot_set_base((__u32)info->io);
	g2d_mixer_idr_init();
	return 0;
}

#ifdef CONFIG_STANDBY
/**
 * @desc      This function suspend the g2d
 * @param     null
 */
int g2d_suspend(void)
{
	g2d_mutex_lock(para.mutex);
	if (para.opened) {
		g2d_clock_disable(&para);
		g2d_bsp_close();
	}
	g2d_mutex_unlock(para.mutex);

	return 0;
}

/**
 * @desc     This function resume the g2d
 * @param    null
 */
int g2d_resume(void)
{
	g2d_mutex_lock(para.mutex);
	if (para.opened) {
		g2d_clock_enable(&para);
		g2d_bsp_open();
	}
	g2d_mutex_unlock(para.mutex);

	return 0;
}
static void g2d_register_pm_dev_notify(void)
{
	register_pm_dev_notify(g2d_suspend, g2d_resume, NULL);
}
#else
static void g2d_register_pm_dev_notify(void)
{
}
#endif

int g2d_probe(void)
{
	int ret = 0;
	__g2d_info_t *info = NULL;

	info = &para;
	memset(info, 0, sizeof(__g2d_info_t));
	info->io = SUNXI_G2D_START;

	if (request_irq(SUNXI_IRQ_G2D, g2d_handle_irq, 0, "g2d", NULL))
        {
		G2D_ERR_MSG("g2d request irq error\n");
		return -1;
        }
	enable_irq(SUNXI_IRQ_G2D);

	g2d_clk_init(info);
	drv_g2d_init(info);
	info->mutex = hal_sem_create(1);
	global_lock = hal_sem_create(1);
	if ((info->mutex == NULL) || (global_lock == NULL)) {
		G2D_ERR_MSG("sysfs_create_file fail!\n");
		ret = -1;
	}

	g2d_register_pm_dev_notify();

	G2D_INFO_MSG("g2d probe finished\n");
	return ret;
}

static int g2d_remove(void)
{
	__g2d_info_t *info = &para;

	g2d_clk_exit(info);
	g2d_mixer_idr_remove();
	INFO("Driver unloaded succesfully.\n");
	return 0;
}

void g2d_ioctl_mutex_lock(void)
{

	g2d_mutex_lock(para.mutex);

}


void g2d_ioctl_mutex_unlock(void)
{
	g2d_mutex_unlock(para.mutex);
}

int sunxi_g2d_open(void)
{
	g2d_mutex_lock(para.mutex);
	g2d_clock_enable(&para);
	para.user_cnt++;
	if (para.user_cnt == 1) {
		para.opened = true;
		g2d_bsp_open();
	}
	g2d_mutex_unlock(para.mutex);
	return 0;

}

int sunxi_g2d_close(void)
{
	g2d_mutex_lock(para.mutex);
	para.user_cnt--;
	if (para.user_cnt == 0) {
		para.opened = false;
		g2d_bsp_close();
	}
	g2d_clock_disable(&para);
	g2d_mutex_unlock(para.mutex);

	g2d_mutex_lock(global_lock);
	scan_order = G2D_SM_TDLR;
	g2d_mutex_unlock(global_lock);

	return 0;

}
int sunxi_g2d_control(int cmd, void *arg)
{
	int ret = -1;

	g2d_ioctl_mutex_lock();

	g2d_ext_hd.finish_flag = 0;
	switch (cmd) {
	case G2D_CMD_MIXER_TASK:
		{

		unsigned long *karg;
		karg = arg;
		ret  = mixer_task_process(&para, (struct mixer_para *)karg[0], karg[1]);
		break;
		}
	case G2D_CMD_CREATE_TASK:
		{

		unsigned long *karg;
		karg = arg;
		ret = create_mixer_task(&para, (struct mixer_para *)karg[0], karg[1]);
			break;
		}
	case G2D_CMD_TASK_APPLY:
		{


		unsigned long *karg;
		karg = arg;


		struct g2d_mixer_task *p_task = NULL;
		p_task = g2d_mixer_get_inst((int)karg[0]);
		ret = p_task->apply(p_task, (struct mixer_para *)karg[1]);



			break;
		}
	case G2D_CMD_TASK_DESTROY:
		{

			struct g2d_mixer_task *p_task = NULL;
			p_task = g2d_mixer_get_inst((int)(unsigned long)arg);
			ret = p_task->destory(p_task);
			break;
		}
	case G2D_CMD_TASK_GET_PARA:
		{

			unsigned long *karg;
			karg = arg;
			struct g2d_mixer_task *p_task = NULL;

			p_task = g2d_mixer_get_inst((int)karg[0]);
			if(!p_task) {
				ret = -EFAULT;
				goto err_noput;
			}

			karg[1] = (unsigned long)(p_task->p_para);
			ret = 0;
			break;
		}
	case G2D_CMD_BITBLT_H:
		{
		g2d_blt_h blit_para;


		memcpy(&blit_para, arg, sizeof(g2d_blt_h));
		if (blit_para.flag_h & 0xff00) {
			ret = g2d_blit_h(&blit_para);
		}

		else {
			struct mixer_para mixer_blit_para;
			memset(&mixer_blit_para, 0, sizeof(struct mixer_para));
			memcpy(&mixer_blit_para.dst_image_h,
			       &blit_para.dst_image_h, sizeof(g2d_image_enh));
			memcpy(&mixer_blit_para.src_image_h,
			       &blit_para.src_image_h, sizeof(g2d_image_enh));
			mixer_blit_para.flag_h = blit_para.flag_h;
			mixer_blit_para.op_flag = OP_BITBLT;
			ret = mixer_task_process(&para, &mixer_blit_para, 1);

		}


		break;
		}

	case G2D_CMD_LBC_ROT:
		{
			g2d_lbc_rot lbc_para;
			memcpy(&lbc_para, (g2d_lbc_rot *)arg, sizeof(g2d_lbc_rot));
			ret = g2d_lbc_rot_set_para(&lbc_para);
			break;
		}

	case G2D_CMD_BLD_H:{

			g2d_bld bld_para;
			struct mixer_para mixer_bld_para;



			memcpy(&bld_para,  (g2d_bld *) arg, sizeof(g2d_bld));
			memset(&mixer_bld_para, 0, sizeof(struct mixer_para));
			memcpy(&mixer_bld_para.dst_image_h,
			       &bld_para.dst_image, sizeof(g2d_image_enh));
			memcpy(&mixer_bld_para.src_image_h,
			       &bld_para.src_image[0], sizeof(g2d_image_enh));
			/* ptn use as src  */
			memcpy(&mixer_bld_para.ptn_image_h,
			       &bld_para.src_image[1], sizeof(g2d_image_enh));
			memcpy(&mixer_bld_para.ck_para, &bld_para.ck_para,
			       sizeof(g2d_ck));
			mixer_bld_para.bld_cmd = bld_para.bld_cmd;
			mixer_bld_para.op_flag = OP_BLEND;

			ret  = mixer_task_process(&para, &mixer_bld_para, 1);

			break;
		}
	case G2D_CMD_FILLRECT_H:{

		g2d_fillrect_h fill_para;
		struct mixer_para mixer_fill_para;


		memcpy(&fill_para, (g2d_fillrect_h *) arg,  sizeof(g2d_fillrect_h));
		memset(&mixer_fill_para, 0, sizeof(struct mixer_para));
		memcpy(&mixer_fill_para.dst_image_h,
		       &fill_para.dst_image_h, sizeof(g2d_image_enh));
		mixer_fill_para.op_flag = OP_FILLRECT;

		ret  = mixer_task_process(&para, &mixer_fill_para, 1);

		break;
	}
	case G2D_CMD_MASK_H:{

			g2d_maskblt mask_para;
			struct mixer_para mixer_mask_para;

			memcpy(&mask_para, (g2d_maskblt *) arg, sizeof(g2d_maskblt));
			memset(&mixer_mask_para, 0, sizeof(struct mixer_para));
			memcpy(&mixer_mask_para.ptn_image_h,
			       &mask_para.ptn_image_h, sizeof(g2d_image_enh));
			memcpy(&mixer_mask_para.mask_image_h,
			       &mask_para.mask_image_h, sizeof(g2d_image_enh));
			memcpy(&mixer_mask_para.dst_image_h,
			       &mask_para.dst_image_h, sizeof(g2d_image_enh));
			memcpy(&mixer_mask_para.src_image_h,
			       &mask_para.src_image_h, sizeof(g2d_image_enh));
			mixer_mask_para.back_flag = mask_para.back_flag;
			mixer_mask_para.fore_flag = mask_para.fore_flag;
			mixer_mask_para.op_flag = OP_MASK;

			ret  = mixer_task_process(&para, &mixer_mask_para, 1);

			break;
		}
	case G2D_CMD_INVERTED_ORDER:
		{
			if ((enum g2d_scan_order)arg > G2D_SM_DTRL) {
				G2D_ERR_MSG("scan mode is err.\n");
				ret = -EINVAL;
				goto err_noput;
			}

			g2d_mutex_lock(global_lock);
			scan_order = (enum g2d_scan_order)arg;
			g2d_mutex_unlock(global_lock);
			ret = 0;
			break;
		}

	default:
		goto err_noput;
		break;
	}

err_noput:
	g2d_ioctl_mutex_unlock();

	return ret;
}

