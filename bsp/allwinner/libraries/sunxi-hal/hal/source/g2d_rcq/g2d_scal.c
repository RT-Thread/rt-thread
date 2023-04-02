/*
 * g2d_scal.c
 *
 * Copyright (c) 2007-2019 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
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
#include <stdlib.h>
#include <string.h>
#include "g2d_scal.h"

static __s32 linearcoefftab32[32] = {
	0x00004000, 0x00023e00, 0x00043c00, 0x00063a00, 0x00083800,
	0x000a3600, 0x000c3400, 0x000e3200, 0x00103000, 0x00122e00,
	0x00142c00, 0x00162a00, 0x00182800, 0x001a2600, 0x001c2400,
	0x001e2200, 0x00202000, 0x00221e00, 0x00241c00, 0x00261a00,
	0x00281800, 0x002a1600, 0x002c1400, 0x002e1200, 0x00301000,
	0x00320e00, 0x00340c00, 0x00360a00, 0x00380800, 0x003a0600,
	0x003c0400, 0x003e0200, };

static __s32 lan2coefftab32_full[512] = {
	0x00004000, 0x000140ff, 0x00033ffe, 0x00043ffd, 0x00063efc, 0xff083dfc,
	0x000a3bfb, 0xff0d39fb, 0xff0f37fb, 0xff1136fa, 0xfe1433fb,
	0xfe1631fb, 0xfd192ffb, 0xfd1c2cfb, 0xfd1f29fb, 0xfc2127fc,
	0xfc2424fc, 0xfc2721fc, 0xfb291ffd, 0xfb2c1cfd, 0xfb2f19fd,
	0xfb3116fe, 0xfb3314fe, 0xfa3611ff, 0xfb370fff, 0xfb390dff,
	0xfb3b0a00, 0xfc3d08ff, 0xfc3e0600, 0xfd3f0400, 0xfe3f0300,
	0xff400100,
	/* counter = 1 */
	0x00004000, 0x000140ff, 0x00033ffe, 0x00043ffd, 0x00063efc,
	0xff083dfc, 0x000a3bfb, 0xff0d39fb, 0xff0f37fb, 0xff1136fa,
	0xfe1433fb, 0xfe1631fb, 0xfd192ffb, 0xfd1c2cfb, 0xfd1f29fb,
	0xfc2127fc, 0xfc2424fc, 0xfc2721fc, 0xfb291ffd, 0xfb2c1cfd,
	0xfb2f19fd, 0xfb3116fe, 0xfb3314fe, 0xfa3611ff, 0xfb370fff,
	0xfb390dff, 0xfb3b0a00, 0xfc3d08ff, 0xfc3e0600, 0xfd3f0400,
	0xfe3f0300, 0xff400100,
	/* counter = 2 */
	0xff053804, 0xff063803, 0xff083801, 0xff093701, 0xff0a3700,
	0xff0c3500, 0xff0e34ff, 0xff1033fe, 0xff1232fd, 0xfe1431fd,
	0xfe162ffd, 0xfe182dfd, 0xfd1b2cfc, 0xfd1d2afc, 0xfd1f28fc,
	0xfd2126fc, 0xfd2323fd, 0xfc2621fd, 0xfc281ffd, 0xfc2a1dfd,
	0xfc2c1bfd, 0xfd2d18fe, 0xfd2f16fe, 0xfd3114fe, 0xfd3212ff,
	0xfe3310ff, 0xff340eff, 0x00350cff, 0x00360a00, 0x01360900,
	0x02370700, 0x03370600,
	/* counter = 3 */
	0xff083207, 0xff093206, 0xff0a3205, 0xff0c3203, 0xff0d3103,
	0xff0e3102, 0xfe113001, 0xfe132f00, 0xfe142e00, 0xfe162dff,
	0xfe182bff, 0xfe192aff, 0xfe1b29fe, 0xfe1d27fe, 0xfe1f25fe,
	0xfd2124fe, 0xfe2222fe, 0xfe2421fd, 0xfe251ffe, 0xfe271dfe,
	0xfe291bfe, 0xff2a19fe, 0xff2b18fe, 0xff2d16fe, 0x002e14fe,
	0x002f12ff, 0x013010ff, 0x02300fff, 0x03310dff, 0x04310cff,
	0x05310a00, 0x06310900,
	/* counter = 4 */
	0xff0a2e09, 0xff0b2e08, 0xff0c2e07, 0xff0e2d06, 0xff0f2d05,
	0xff102d04, 0xff122c03, 0xfe142c02, 0xfe152b02, 0xfe172a01,
	0xfe182901, 0xfe1a2800, 0xfe1b2700, 0xfe1d2500, 0xff1e24ff,
	0xfe2023ff, 0xff2121ff, 0xff2320fe, 0xff241eff, 0x00251dfe,
	0x00261bff, 0x00281afe, 0x012818ff, 0x012a16ff, 0x022a15ff,
	0x032b13ff, 0x032c12ff, 0x052c10ff, 0x052d0fff, 0x062d0d00,
	0x072d0c00, 0x082d0b00,
	/* counter = 5 */
	0xff0c2a0b, 0xff0d2a0a, 0xff0e2a09, 0xff0f2a08, 0xff102a07,
	0xff112a06, 0xff132905, 0xff142904, 0xff162803, 0xff172703,
	0xff182702, 0xff1a2601, 0xff1b2501, 0xff1c2401, 0xff1e2300,
	0xff1f2200, 0x00202000, 0x00211f00, 0x01221d00, 0x01231c00,
	0x01251bff, 0x02251aff, 0x032618ff, 0x032717ff, 0x042815ff,
	0x052814ff, 0x052913ff, 0x06291100, 0x072a10ff, 0x082a0e00,
	0x092a0d00, 0x0a2a0c00,
	/* counter = 6 */
	0xff0d280c, 0xff0e280b, 0xff0f280a, 0xff102809, 0xff112808,
	0xff122708, 0xff142706, 0xff152705, 0xff162605, 0xff172604,
	0xff192503, 0xff1a2403, 0x001b2302, 0x001c2202, 0x001d2201,
	0x001e2101, 0x011f1f01, 0x01211e00, 0x01221d00, 0x02221c00,
	0x02231b00, 0x03241900, 0x04241800, 0x04251700, 0x052616ff,
	0x06261400, 0x072713ff, 0x08271100, 0x08271100, 0x09271000,
	0x0a280e00, 0x0b280d00,
	/* counter = 7 */
	0xff0e260d, 0xff0f260c, 0xff10260b, 0xff11260a, 0xff122609,
	0xff132608, 0xff142508, 0xff152507, 0x00152506, 0x00172405,
	0x00182305, 0x00192304, 0x001b2203, 0x001c2103, 0x011d2002,
	0x011d2002, 0x011f1f01, 0x021f1e01, 0x02201d01, 0x03211c00,
	0x03221b00, 0x04221a00, 0x04231801, 0x05241700, 0x06241600,
	0x07241500, 0x08251300, 0x09251200, 0x09261100, 0x0a261000,
	0x0b260f00, 0x0c260e00,
	/* counter = 8 */
	0xff0e250e, 0xff0f250d, 0xff10250c, 0xff11250b, 0x0011250a,
	0x00132409, 0x00142408, 0x00152407, 0x00162307, 0x00172306,
	0x00182206, 0x00192205, 0x011a2104, 0x011b2004, 0x011c2003,
	0x021c1f03, 0x021e1e02, 0x031e1d02, 0x03201c01, 0x04201b01,
	0x04211a01, 0x05221900, 0x05221801, 0x06231700, 0x07231600,
	0x07241500, 0x08241400, 0x09241300, 0x0a241200, 0x0b241100,
	0x0c241000, 0x0d240f00,
	/* counter = 9 */
	0x000e240e, 0x000f240d, 0x0010240c, 0x0011240b, 0x0013230a,
	0x0013230a, 0x00142309, 0x00152308, 0x00162208, 0x00172207,
	0x01182106, 0x01192105, 0x011a2005, 0x021b1f04, 0x021b1f04,
	0x021d1e03, 0x031d1d03, 0x031e1d02, 0x041e1c02, 0x041f1b02,
	0x05201a01, 0x05211901, 0x06211801, 0x07221700, 0x07221601,
	0x08231500, 0x09231400, 0x0a231300, 0x0a231300, 0x0b231200,
	0x0c231100, 0x0d231000,
	/* counter = 10 */
	0x000f220f, 0x0010220e, 0x0011220d, 0x0012220c, 0x0013220b,
	0x0013220b, 0x0015210a, 0x0015210a, 0x01162108, 0x01172008,
	0x01182007, 0x02191f06, 0x02191f06, 0x021a1e06, 0x031a1e05,
	0x031c1d04, 0x041c1c04, 0x041d1c03, 0x051d1b03, 0x051e1a03,
	0x061f1902, 0x061f1902, 0x07201801, 0x08201701, 0x08211601,
	0x09211501, 0x0a211500, 0x0b211400, 0x0b221300, 0x0c221200,
	0x0d221100, 0x0e221000,
	/* counter = 11 */
	0x0010210f, 0x0011210e, 0x0011210e, 0x0012210d, 0x0013210c,
	0x0014200c, 0x0114200b, 0x0115200a, 0x01161f0a, 0x01171f09,
	0x02171f08, 0x02181e08, 0x03181e07, 0x031a1d06, 0x031a1d06,
	0x041b1c05, 0x041c1c04, 0x051c1b04, 0x051d1a04, 0x061d1a03,
	0x071d1903, 0x071e1803, 0x081e1802, 0x081f1702, 0x091f1602,
	0x0a201501, 0x0b1f1501, 0x0b201401, 0x0c211300, 0x0d211200,
	0x0e201200, 0x0e211100,
	/* counter = 12 */
	0x00102010, 0x0011200f, 0x0012200e, 0x0013200d, 0x0013200d,
	0x01141f0c, 0x01151f0b, 0x01151f0b, 0x01161f0a, 0x02171e09,
	0x02171e09, 0x03181d08, 0x03191d07, 0x03191d07, 0x041a1c06,
	0x041b1c05, 0x051b1b05, 0x051c1b04, 0x061c1a04, 0x071d1903,
	0x071d1903, 0x081d1803, 0x081e1703, 0x091e1702, 0x0a1f1601,
	0x0a1f1502, 0x0b1f1501, 0x0c1f1401, 0x0d201300, 0x0d201300,
	0x0e201200, 0x0f201100,
	/* counter = 13 */
	0x00102010, 0x0011200f, 0x00121f0f, 0x00131f0e, 0x00141f0d,
	0x01141f0c, 0x01141f0c, 0x01151e0c, 0x02161e0a, 0x02171e09,
	0x03171d09, 0x03181d08, 0x03181d08, 0x04191c07, 0x041a1c06,
	0x051a1b06, 0x051b1b05, 0x061b1a05, 0x061c1a04, 0x071c1904,
	0x081c1903, 0x081d1803, 0x091d1703, 0x091e1702, 0x0a1e1602,
	0x0b1e1502, 0x0c1e1501, 0x0c1f1401, 0x0d1f1400, 0x0e1f1300,
	0x0e1f1201, 0x0f1f1200,
	/* counter = 14 */
	0x00111e11, 0x00121e10, 0x00131e0f, 0x00131e0f, 0x01131e0e,
	0x01141d0e, 0x02151d0c, 0x02151d0c, 0x02161d0b, 0x03161c0b,
	0x03171c0a, 0x04171c09, 0x04181b09, 0x05181b08, 0x05191b07,
	0x06191a07, 0x061a1a06, 0x071a1906, 0x071b1905, 0x081b1805,
	0x091b1804, 0x091c1704, 0x0a1c1703, 0x0a1c1604, 0x0b1d1602,
	0x0c1d1502, 0x0c1d1502, 0x0d1d1402, 0x0e1d1401, 0x0e1e1301,
	0x0f1e1300, 0x101e1200,
	/* counter = 15 */
	0x00111e11, 0x00121e10, 0x00131d10, 0x01131d0f, 0x01141d0e,
	0x01141d0e, 0x02151c0d, 0x02151c0d, 0x03161c0b, 0x03161c0b,
	0x04171b0a, 0x04171b0a, 0x05171b09, 0x05181a09, 0x06181a08,
	0x06191a07, 0x07191907, 0x071a1906, 0x081a1806, 0x081a1806,
	0x091a1805, 0x0a1b1704, 0x0a1b1704, 0x0b1c1603, 0x0b1c1603,
	0x0c1c1503, 0x0d1c1502, 0x0d1d1402, 0x0e1d1401, 0x0f1d1301,
	0x0f1d1301, 0x101e1200,
	/* counter = 16 */
};

static int scal_rcq_setup(struct scaler_submodule *p_scal, u8 *base,
			  struct g2d_rcq_mem_info *p_rcq_info)
{
	u8 *reg_base = base + G2D_VSU;
	int ret = -1;

	if (!p_scal) {
		G2D_ERR_MSG("Null pointer!\n");
		goto OUT;
	}

	p_scal->reg_info->size = sizeof(struct g2d_mixer_video_scaler_reg);
	p_scal->reg_info->vir_addr = (u8 *)g2d_top_reg_memory_alloc(
	    p_scal->reg_info->size, (void *)&(p_scal->reg_info->phy_addr),
	    p_rcq_info);

	if (!p_scal->reg_info->vir_addr) {
		G2D_ERR_MSG("Malloc scaler reg rcq memory fail!\n");
		goto OUT;
	}

	p_scal->reg_blks->vir_addr = p_scal->reg_info->vir_addr;
	p_scal->reg_blks->phy_addr = p_scal->reg_info->phy_addr;
	p_scal->reg_blks->size = p_scal->reg_info->size;
	p_scal->reg_blks->reg_addr = reg_base;
	ret = 0;

OUT:
	return ret;
}

static __u32 scal_get_reg_block_num(struct scaler_submodule *p_scal)
{
	if (p_scal)
		return p_scal->reg_blk_num;
	return 0;
}

static __s32 scal_get_reg_block(struct scaler_submodule *p_scal,
			    struct g2d_reg_block **blks)
{
	__s32 i = 0, ret = -1;
	if (p_scal) {
		for (i = 0; i < p_scal->reg_blk_num; ++i)
			blks[i] = p_scal->reg_blks + i;
		ret = 0;
	}

	return ret;
}

static struct g2d_mixer_video_scaler_reg *scal_get_reg(struct scaler_submodule *p_scal)
{

#if G2D_MIXER_RCQ_USED == 1
	return (struct g2d_mixer_video_scaler_reg *)(p_scal->reg_blks
						     ->vir_addr);
#else
	return (struct g2d_mixer_video_scaler_reg *)(p_scal->reg_blks
						     ->reg_addr);
#endif

	return NULL;
}

static void scal_set_block_dirty(struct scaler_submodule *p_scal, __u32 blk_id, __u32 dirty)
{
#if G2D_MIXER_RCQ_USED == 1
	if (p_scal && p_scal->reg_blks->rcq_hd)
		p_scal->reg_blks->rcq_hd->dirty.bits.dirty = dirty;
	else
		G2D_ERR_MSG("Null pointer!\n");
#else

	if (p_scal)
		p_scal->reg_blks->dirty = dirty;
	else
		G2D_ERR_MSG("Null pointer!\n");
#endif
}

/**
 * function       : g2d_vsu_calc_fir_coef(unsigned int step)
 * description    : set fir coefficients
 * parameters     :
 *                  step		<horizontal scale ratio of vsu>
 * return         :
 *                  offset (in word) of coefficient table
 */
static __u32 g2d_vsu_calc_fir_coef(__u32 step)
{
	__u32 pt_coef;
	__u32 scale_ratio, int_part, float_part, fir_coef_ofst;

	scale_ratio = step >> (VSU_PHASE_FRAC_BITWIDTH - 3);
	int_part = scale_ratio >> 3;
	float_part = scale_ratio & 0x7;
	fir_coef_ofst = (int_part == 0) ? VSU_ZOOM0_SIZE :
	    (int_part == 1) ? VSU_ZOOM0_SIZE + float_part :
	    (int_part ==
	     2) ? VSU_ZOOM0_SIZE + VSU_ZOOM1_SIZE +
	    (float_part >> 1) : (int_part ==
				  3) ? VSU_ZOOM0_SIZE + VSU_ZOOM1_SIZE +
	    VSU_ZOOM2_SIZE : (int_part ==
			       4) ? VSU_ZOOM0_SIZE + VSU_ZOOM1_SIZE +
	    VSU_ZOOM2_SIZE + VSU_ZOOM3_SIZE : VSU_ZOOM0_SIZE +
	    VSU_ZOOM1_SIZE + VSU_ZOOM2_SIZE + VSU_ZOOM3_SIZE + VSU_ZOOM4_SIZE;
	pt_coef = fir_coef_ofst * VSU_PHASE_NUM;
	return pt_coef;
}

__s32 g2d_vsu_para_set(struct scaler_submodule *p_scal, __u32 fmt, __u32 in_w,
		       __u32 in_h, __u32 out_w, __u32 out_h, __u8 alpha)
{
	__u64 temp;
	__u32 yhstep, yvstep;
	__u32 incw, inch;
	__u32 yhcoef_offset, yvcoef_offset, chcoef_offset;
	__u32 format;
	__s32 ret = -1;

	struct g2d_mixer_video_scaler_reg *p_reg = NULL;
	p_reg = p_scal->get_reg(p_scal);
	if (!p_reg)
		goto OUT;

	p_reg->vs_ctrl.bits.coef_access_sel = 1;
	p_reg->vs_ctrl.bits.en = 1;
	if (fmt > G2D_FORMAT_IYUV422_Y1U0Y0V0)
		p_reg->vs_ctrl.bits.filter_type = 1;
	else
		p_reg->vs_ctrl.bits.filter_type = 0;

	p_reg->out_size.bits.out_width = out_w - 1;
	p_reg->out_size.bits.out_height = out_h - 1;
	p_reg->glb_alpha.bits.glb_alpha = alpha;

	p_reg->y_ch_size.bits.y_width = in_w - 1;
	p_reg->y_ch_size.bits.y_height = in_h - 1;

	temp = in_w << VSU_PHASE_FRAC_BITWIDTH;
	if (out_w)
		// do_div(temp, out_w); /////////// temp是被除数
		temp = temp/out_w;
	else
		temp = 0;

	yhstep = temp;
	p_reg->y_hor_step.dwval = yhstep << 1;
	temp = in_h << VSU_PHASE_FRAC_BITWIDTH;
	if (out_h)
//		do_div(temp, out_h);
		temp = temp/out_h;
	else
		temp = 0;
	yvstep = temp;
	p_reg->y_ver_step.dwval = yvstep << 1;

	yhcoef_offset = g2d_vsu_calc_fir_coef(yhstep);
	memcpy(&p_reg->vs_y_ch_hor_filter_coef[0],
	       &lan2coefftab32_full[yhcoef_offset], VSU_PHASE_NUM * sizeof(unsigned int));

	yvcoef_offset = g2d_vsu_calc_fir_coef(yvstep);
	switch (fmt) {
	case G2D_FORMAT_Y8:
		format = VSU_FORMAT_RGB;
		incw = (in_w + 1) >> 1;
		inch = in_h;
		p_reg->c_ch_size.bits.y_width = 0;
		p_reg->c_ch_size.bits.y_height = 0;
		p_reg->c_hor_step.dwval = 0;
		p_reg->c_ver_step.dwval = 0;
		memcpy(&p_reg->vs_y_ch_ver_filter_coef[0],
		       &linearcoefftab32[0],
		       VSU_PHASE_NUM * sizeof(unsigned int));
		p_reg->y_hor_phase.dwval = 0;
		p_reg->y_ver_phase.dwval = 0x0;
		p_reg->y_ver_phase.bits.integer =
		    ((in_h / out_h) < 3) ? 0 : (in_h / out_h - 3);
		p_reg->c_hor_phase.dwval = 0;
		p_reg->c_ver_phase.dwval = 0;
		break;
	case G2D_FORMAT_IYUV422_V0Y1U0Y0:
	case G2D_FORMAT_IYUV422_Y1V0Y0U0:
	case G2D_FORMAT_IYUV422_U0Y1V0Y0:
	case G2D_FORMAT_IYUV422_Y1U0Y0V0:{
			incw = (in_w + 1) >> 1;
			inch = in_h;
			format = VSU_FORMAT_YUV422;
			p_reg->c_ch_size.bits.y_width = incw - 1;
			p_reg->c_ch_size.bits.y_height = inch - 1;

			    /* chstep = yhstep>>1 cvstep = yvstep */
			p_reg->c_hor_step.dwval = yhstep;
			p_reg->c_ver_step.dwval = yvstep << 1;
			chcoef_offset = g2d_vsu_calc_fir_coef(yhstep >> 1);
			memcpy(&p_reg->vs_c_ch_hor_filter_coef[0],
			       &lan2coefftab32_full[chcoef_offset],
			       VSU_PHASE_NUM * sizeof(unsigned int));
			memcpy(&p_reg->vs_y_ch_ver_filter_coef[0],
			       &linearcoefftab32[0],
			       VSU_PHASE_NUM * sizeof(unsigned int));
			break;
		}
	case G2D_FORMAT_YUV422UVC_V1U1V0U0:
	case G2D_FORMAT_YUV422UVC_U1V1U0V0:
	case G2D_FORMAT_YUV422_PLANAR:{
			incw = (in_w + 1) >> 1;
			inch = in_h;
			format = VSU_FORMAT_YUV422;
			p_reg->c_ch_size.bits.y_width = incw - 1;
			p_reg->c_ch_size.bits.y_height = inch - 1;

			    /* chstep = yhstep>>1 cvstep = yvstep>>1 */
			p_reg->c_hor_step.dwval = yhstep;
			p_reg->c_ver_step.dwval = yvstep << 1;
			chcoef_offset = g2d_vsu_calc_fir_coef(yhstep >> 1);

			memcpy(&p_reg->vs_c_ch_hor_filter_coef[0],
			       &lan2coefftab32_full[chcoef_offset],
			       VSU_PHASE_NUM * sizeof(unsigned int));

			memcpy(&p_reg->vs_y_ch_ver_filter_coef[0],
			       &lan2coefftab32_full[yvcoef_offset],
			       VSU_PHASE_NUM * sizeof(unsigned int));
			break;
		}
	case G2D_FORMAT_YUV420_PLANAR:
	case G2D_FORMAT_YUV420UVC_V1U1V0U0:
	case G2D_FORMAT_YUV420UVC_U1V1U0V0:{
			incw = (in_w + 1) >> 1;
			inch = (in_h + 1) >> 1;
			format = VSU_FORMAT_YUV420;
			p_reg->c_ch_size.bits.y_width = incw - 1;
			p_reg->c_ch_size.bits.y_height = inch - 1;

			    /* chstep = yhstep>>1 cvstep = yvstep>>1 */
			p_reg->c_hor_step.dwval = yhstep;
			p_reg->c_ver_step.dwval = yvstep;

			chcoef_offset = g2d_vsu_calc_fir_coef(yhstep >> 1);

			memcpy(&p_reg->vs_c_ch_hor_filter_coef[0],
			       &lan2coefftab32_full[chcoef_offset],
			       VSU_PHASE_NUM * sizeof(unsigned int));
			memcpy(&p_reg->vs_y_ch_ver_filter_coef[0],
			       &lan2coefftab32_full[yvcoef_offset],
			       VSU_PHASE_NUM * sizeof(unsigned int));
			break;
		}
	case G2D_FORMAT_YUV411_PLANAR:
	case G2D_FORMAT_YUV411UVC_V1U1V0U0:
	case G2D_FORMAT_YUV411UVC_U1V1U0V0:{
			incw = (in_w + 3) >> 2;
			inch = in_h;
			format = VSU_FORMAT_YUV411;
			p_reg->c_ch_size.bits.y_width = incw - 1;
			p_reg->c_ch_size.bits.y_height = inch - 1;

			    /* chstep = yhstep>>2 cvstep = yvstep */
			p_reg->c_hor_step.dwval = yhstep >> 1;
			p_reg->c_ver_step.dwval = yvstep << 1;

			chcoef_offset = g2d_vsu_calc_fir_coef(yhstep >> 2);
			memcpy(&p_reg->vs_c_ch_hor_filter_coef[0],
			       &lan2coefftab32_full[chcoef_offset],
			       VSU_PHASE_NUM * sizeof(unsigned int));

			memcpy(&p_reg->vs_y_ch_ver_filter_coef[0],
			       &lan2coefftab32_full[yvcoef_offset],
			       VSU_PHASE_NUM * sizeof(unsigned int));

			break;
		}
	default:
		format = VSU_FORMAT_RGB;
		incw = in_w;
		inch = in_h;
		p_reg->c_ch_size.bits.y_width = incw - 1;
		p_reg->c_ch_size.bits.y_height = inch - 1;

		p_reg->c_hor_step.dwval = yhstep << 1;
		p_reg->c_ver_step.dwval = yvstep << 1;
		    /* chstep = yhstep cvstep = yvstep */
		chcoef_offset = g2d_vsu_calc_fir_coef(yhstep);

		memcpy(&p_reg->vs_c_ch_hor_filter_coef[0],
		       &lan2coefftab32_full[chcoef_offset],
		       VSU_PHASE_NUM * sizeof(unsigned int));

		memcpy(&p_reg->vs_y_ch_ver_filter_coef[0],
		       &linearcoefftab32[0],
		       VSU_PHASE_NUM * sizeof(unsigned int));

		break;
	}
	if (format == VSU_FORMAT_YUV420) {
		/**
		 * yhphase = 0;
		 * yvphase = 0;
		 * chphase = 0xFFFE0000;
		 * cvphase = 0xFFFE0000;
		 */
		p_reg->y_hor_phase.dwval = 0;
		p_reg->y_ver_phase.dwval = 0;
		p_reg->c_hor_phase.dwval = 0xFFFc0000;
		p_reg->c_ver_phase.dwval = 0xFFFc0000;
	} else if (fmt != G2D_FORMAT_Y8) {
		p_reg->y_hor_phase.dwval = 0;
		p_reg->y_ver_phase.dwval = 0;
		p_reg->c_hor_phase.dwval = 0;
		p_reg->c_ver_phase.dwval = 0;
	}

	ret = 0;
	p_scal->set_block_dirty(p_scal, 0, 1);
OUT:
	return ret;
}

static __u32 scal_get_rcq_mem_size(struct scaler_submodule *p_scal)
{
	return G2D_RCQ_BYTE_ALIGN(sizeof(struct g2d_mixer_video_scaler_reg));
}

static __s32 scal_destory(struct scaler_submodule *p_scal)
{
	__s32 ret = -1;

	if (p_scal) {
		free(p_scal->reg_blks);
		p_scal->reg_blks = NULL;

		free(p_scal->reg_info);
		p_scal->reg_info = NULL;
		free(p_scal);
		ret = 0;
	}

	return ret;
}

struct scaler_submodule *g2d_scaler_submodule_setup(struct g2d_mixer_frame *p_frame)
{
	struct scaler_submodule *p_scal = NULL;

	p_scal = hal_malloc(sizeof(struct scaler_submodule));

	if (!p_scal) {
		G2D_ERR_MSG("malloc wb submodule fail!\n");
		return NULL;
	}
	memset(p_scal, 0, sizeof(struct scaler_submodule));
	p_scal->rcq_setup = scal_rcq_setup;
	p_scal->reg_blk_num = 1;
	p_scal->get_reg_block_num = scal_get_reg_block_num;
	p_scal->get_reg_block = scal_get_reg_block;
	p_scal->get_reg = scal_get_reg;
	p_scal->set_block_dirty = scal_set_block_dirty;
	p_scal->get_rcq_mem_size = scal_get_rcq_mem_size;
	p_scal->destory = scal_destory;

	p_scal->reg_blks =
	    hal_malloc(sizeof(struct g2d_reg_block) * p_scal->reg_blk_num);
	p_scal->reg_info =
	    hal_malloc(sizeof(struct g2d_reg_mem_info));

	if (!p_scal->reg_blks || !p_scal->reg_info) {
		G2D_ERR_MSG("malloc wb reg info fail!\n");
		goto FREE_WB;
	}
	memset(p_scal->reg_blks, 0, sizeof(struct g2d_reg_block) * p_scal->reg_blk_num);
	memset(p_scal->reg_info, 0, sizeof(struct g2d_reg_mem_info));

	return p_scal;
FREE_WB:
	free(p_scal->reg_blks);
	free(p_scal->reg_info);
	free(p_scal);

	return NULL;
}
