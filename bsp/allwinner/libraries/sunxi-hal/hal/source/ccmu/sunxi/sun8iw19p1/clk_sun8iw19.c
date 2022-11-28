/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 *the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.
 *
 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <typedef.h>

#include <stdio.h>
#include <string.h>

#include "../clk.h"
#include "../clk_periph.h"
#include "../clk_factors.h"
#include "clk_sun8iw19.h"

static int get_factors_pll_cpu(u32 rate, u32 parent_rate,
                               struct clk_factors_value *factor);

static int get_factors_pll_ddr(u32 rate, u32 parent_rate,
                               struct clk_factors_value *factor);

static int get_factors_pll_periph0(u32 rate, u32 parent_rate,
                                   struct clk_factors_value *factor);

static int get_factors_pll_periph1(u32 rate, u32 parent_rate,
                                   struct clk_factors_value *factor);

static int calc_rate_pll_cpu(u32 parent_rate,
                             struct clk_factors_value *factor);

static int calc_rate_pll_ddr(u32 parent_rate,
                             struct clk_factors_value *factor);

static int calc_rate_pll_periph0(u32 parent_rate,
                                 struct clk_factors_value *factor);

static int calc_rate_pll_periph1(u32 parent_rate,
                                 struct clk_factors_value *factor);

static int calc_rate_pll_audio(u32 parent_rate,
                               struct clk_factors_value *factor);

static int get_factors_pll_audio(u32 rate, u32 parent_rate,
                                 struct clk_factors_value *factor);

static int get_factors_pll_video(u32 rate, u32 parent_rate,
                                 struct clk_factors_value *factor);

static int calc_rate_pll_video(u32 parent_rate,
                               struct clk_factors_value *factor);

static int get_factors_pll_csi(u32 rate, u32 parent_rate,
                               struct clk_factors_value *factor);

static int calc_rate_pll_csi(u32 parent_rate,
                             struct clk_factors_value *factor);


struct sunxi_clk_factor_freq factor_pllcpu_tbl[] =
{
    PLLCPU(11,     2,     72000000U),
    PLLCPU(13,     2,     84000000U),
    PLLCPU(15,     2,     96000000U),
    PLLCPU(17,     2,     108000000U),
    PLLCPU(19,     2,     120000000U),
    PLLCPU(21,     2,     132000000U),
    PLLCPU(23,     2,     144000000U),
    PLLCPU(25,     2,     156000000U),
    PLLCPU(27,     2,     168000000U),
    PLLCPU(29,     2,     180000000U),
    PLLCPU(31,     2,     192000000U),
    PLLCPU(33,     2,     204000000U),
    PLLCPU(35,     2,     216000000U),
    PLLCPU(37,     2,     228000000U),
    PLLCPU(39,     2,     240000000U),
    PLLCPU(41,     2,     252000000U),
    PLLCPU(43,     2,     264000000U),
    PLLCPU(45,     2,     276000000U),
    PLLCPU(11,     0,     288000000U),
    PLLCPU(24,     1,     300000000U),
    PLLCPU(12,     0,     312000000U),
    PLLCPU(26,     1,     324000000U),
    PLLCPU(13,     0,     336000000U),
    PLLCPU(28,     1,     348000000U),
    PLLCPU(14,     0,     360000000U),
    PLLCPU(30,     1,     372000000U),
    PLLCPU(15,     0,     384000000U),
    PLLCPU(32,     1,     396000000U),
    PLLCPU(16,     0,     408000000U),
    PLLCPU(34,     1,     420000000U),
    PLLCPU(17,     0,     432000000U),
    PLLCPU(36,     1,     444000000U),
    PLLCPU(18,     0,     456000000U),
    PLLCPU(38,     1,     468000000U),
    PLLCPU(19,     0,     480000000U),
    PLLCPU(40,     1,     492000000U),
    PLLCPU(20,     0,     504000000U),
    PLLCPU(42,     1,     516000000U),
    PLLCPU(21,     0,     528000000U),
    PLLCPU(44,     1,     540000000U),
    PLLCPU(22,     0,     552000000U),
    PLLCPU(46,     1,     564000000U),
    PLLCPU(23,     0,     576000000U),
    PLLCPU(48,     1,     588000000U),
    PLLCPU(24,     0,     600000000U),
    PLLCPU(50,     1,     612000000U),
    PLLCPU(25,     0,     624000000U),
    PLLCPU(52,     1,     636000000U),
    PLLCPU(26,     0,     648000000U),
    PLLCPU(54,     1,     660000000U),
    PLLCPU(27,     0,     672000000U),
    PLLCPU(56,     1,     684000000U),
    PLLCPU(28,     0,     696000000U),
    PLLCPU(58,     1,     708000000U),
    PLLCPU(29,     0,     720000000U),
    PLLCPU(60,     1,     732000000U),
    PLLCPU(30,     0,     744000000U),
    PLLCPU(62,     1,     756000000U),
    PLLCPU(31,     0,     768000000U),
    PLLCPU(64,     1,     780000000U),
    PLLCPU(32,     0,     792000000U),
    PLLCPU(66,     1,     804000000U),
    PLLCPU(33,     0,     816000000U),
    PLLCPU(68,     1,     828000000U),
    PLLCPU(34,     0,     840000000U),
    PLLCPU(70,     1,     852000000U),
    PLLCPU(35,     0,     864000000U),
    PLLCPU(72,     1,     876000000U),
    PLLCPU(36,     0,     888000000U),
    PLLCPU(74,     1,     900000000U),
    PLLCPU(37,     0,     912000000U),
    PLLCPU(76,     1,     924000000U),
    PLLCPU(38,     0,     936000000U),
    PLLCPU(78,     1,     948000000U),
    PLLCPU(39,     0,     960000000U),
    PLLCPU(80,     1,     972000000U),
    PLLCPU(40,     0,     984000000U),
    PLLCPU(82,     1,     996000000U),
    PLLCPU(41,     0,     1008000000U),
    PLLCPU(84,     1,     1020000000U),
    PLLCPU(42,     0,     1032000000U),
    PLLCPU(86,     1,     1044000000U),
    PLLCPU(43,     0,     1056000000U),
    PLLCPU(88,     1,     1068000000U),
    PLLCPU(44,     0,     1080000000U),
    PLLCPU(90,     1,     1092000000U),
    PLLCPU(45,     0,     1104000000U),
    PLLCPU(92,     1,     1116000000U),
    PLLCPU(46,     0,     1128000000U),
    PLLCPU(94,     1,     1140000000U),
    PLLCPU(47,     0,     1152000000U),
    PLLCPU(96,     1,     1164000000U),
    PLLCPU(48,     0,     1176000000U),
    PLLCPU(98,     1,     1188000000U),
    PLLCPU(49,     0,     1200000000U),
};

/*n  m1   m0   freq */
/* PLLDDR(n, d1, d2, freq)  F_N8X8_D1V1X1_D2V0X1 */
struct sunxi_clk_factor_freq factor_pllddr_tbl[] =
{
    PLLDDR(23,     0,     1,     288000000U),
    PLLDDR(48,     1,     1,     294000000U),
    PLLDDR(24,     0,     1,     300000000U),
    PLLDDR(50,     1,     1,     306000000U),
    PLLDDR(25,     0,     1,     312000000U),
    PLLDDR(52,     1,     1,     318000000U),
    PLLDDR(26,     0,     1,     324000000U),
    PLLDDR(54,     1,     1,     330000000U),
    PLLDDR(27,     0,     1,     336000000U),
    PLLDDR(56,     1,     1,     342000000U),
    PLLDDR(28,     0,     1,     348000000U),
    PLLDDR(58,     1,     1,     354000000U),
    PLLDDR(29,     0,     1,     360000000U),
    PLLDDR(60,     1,     1,     366000000U),
    PLLDDR(30,     0,     1,     372000000U),
    PLLDDR(62,     1,     1,     378000000U),
    PLLDDR(15,     0,     0,     384000000U),
    PLLDDR(64,     1,     1,     390000000U),
    PLLDDR(32,     0,     1,     396000000U),
    PLLDDR(66,     1,     1,     402000000U),
    PLLDDR(16,     0,     0,     408000000U),
    PLLDDR(68,     1,     1,     414000000U),
    PLLDDR(34,     0,     1,     420000000U),
    PLLDDR(70,     1,     1,     426000000U),
    PLLDDR(17,     0,     0,     432000000U),
    PLLDDR(72,     1,     1,     438000000U),
    PLLDDR(36,     0,     1,     444000000U),
    PLLDDR(74,     1,     1,     450000000U),
    PLLDDR(18,     0,     0,     456000000U),
    PLLDDR(76,     1,     1,     462000000U),
    PLLDDR(38,     0,     1,     468000000U),
    PLLDDR(78,     1,     1,     474000000U),
    PLLDDR(19,     0,     0,     480000000U),
    PLLDDR(80,     1,     1,     486000000U),
    PLLDDR(40,     0,     1,     492000000U),
    PLLDDR(82,     1,     1,     498000000U),
    PLLDDR(20,     0,     0,     504000000U),
    PLLDDR(84,     1,     1,     510000000U),
    PLLDDR(42,     0,     1,     516000000U),
    PLLDDR(86,     1,     1,     522000000U),
    PLLDDR(21,     0,     0,     528000000U),
    PLLDDR(88,     1,     1,     534000000U),
    PLLDDR(44,     0,     1,     540000000U),
    PLLDDR(90,     1,     1,     546000000U),
    PLLDDR(22,     0,     0,     552000000U),
    PLLDDR(92,     1,     1,     558000000U),
    PLLDDR(46,     0,     1,     564000000U),
    PLLDDR(94,     1,     1,     570000000U),
    PLLDDR(23,     0,     0,     576000000U),
    PLLDDR(96,     1,     1,     582000000U),
    PLLDDR(48,     0,     1,     588000000U),
    PLLDDR(98,     1,     1,     594000000U),
    PLLDDR(24,     0,     0,     600000000U),
    PLLDDR(100,     1,     1,     606000000U),
    PLLDDR(50,     0,     1,     612000000U),
    PLLDDR(102,     1,     1,     618000000U),
    PLLDDR(25,     0,     0,     624000000U),
    PLLDDR(104,     1,     1,     630000000U),
    PLLDDR(52,     0,     1,     636000000U),
    PLLDDR(106,     1,     1,     642000000U),
    PLLDDR(26,     0,     0,     648000000U),
    PLLDDR(108,     1,     1,     654000000U),
    PLLDDR(54,     0,     1,     660000000U),
    PLLDDR(110,     1,     1,     666000000U),
    PLLDDR(27,     0,     0,     672000000U),
    PLLDDR(112,     1,     1,     678000000U),
    PLLDDR(56,     0,     1,     684000000U),
    PLLDDR(114,     1,     1,     690000000U),
    PLLDDR(28,     0,     0,     696000000U),
    PLLDDR(116,     1,     1,     702000000U),
    PLLDDR(58,     0,     1,     708000000U),
    PLLDDR(118,     1,     1,     714000000U),
    PLLDDR(29,     0,     0,     720000000U),
    PLLDDR(120,     1,     1,     726000000U),
    PLLDDR(60,     0,     1,     732000000U),
    PLLDDR(122,     1,     1,     738000000U),
    PLLDDR(30,     0,     0,     744000000U),
    PLLDDR(124,     1,     1,     750000000U),
    PLLDDR(62,     0,     1,     756000000U),
    PLLDDR(126,     1,     1,     762000000U),
    PLLDDR(31,     0,     0,     768000000U),
    PLLDDR(128,     1,     1,     774000000U),
    PLLDDR(64,     0,     1,     780000000U),
    PLLDDR(130,     1,     1,     786000000U),
    PLLDDR(32,     0,     0,     792000000U),
    PLLDDR(132,     1,     1,     798000000U),
    PLLDDR(66,     0,     1,     804000000U),
    PLLDDR(134,     1,     1,     810000000U),
    PLLDDR(33,     0,     0,     816000000U),
    PLLDDR(136,     1,     1,     822000000U),
    PLLDDR(68,     0,     1,     828000000U),
    PLLDDR(138,     1,     1,     834000000U),
    PLLDDR(34,     0,     0,     840000000U),
    PLLDDR(140,     1,     1,     846000000U),
    PLLDDR(70,     0,     1,     852000000U),
    PLLDDR(142,     1,     1,     858000000U),
    PLLDDR(35,     0,     0,     864000000U),
    PLLDDR(144,     1,     1,     870000000U),
    PLLDDR(72,     0,     1,     876000000U),
    PLLDDR(146,     1,     1,     882000000U),
    PLLDDR(36,     0,     0,     888000000U),
    PLLDDR(148,     1,     1,     894000000U),
    PLLDDR(74,     0,     1,     900000000U),
    PLLDDR(150,     1,     1,     906000000U),
    PLLDDR(37,     0,     0,     912000000U),
    PLLDDR(152,     1,     1,     918000000U),
    PLLDDR(76,     0,     1,     924000000U),
    PLLDDR(154,     1,     1,     930000000U),
    PLLDDR(38,     0,     0,     936000000U),
    PLLDDR(156,     1,     1,     942000000U),
    PLLDDR(78,     0,     1,     948000000U),
    PLLDDR(158,     1,     1,     954000000U),
    PLLDDR(39,     0,     0,     960000000U),
    PLLDDR(160,     1,     1,     966000000U),
    PLLDDR(80,     0,     1,     972000000U),
    PLLDDR(162,     1,     1,     978000000U),
    PLLDDR(40,     0,     0,     984000000U),
    PLLDDR(164,     1,     1,     990000000U),
    PLLDDR(82,     0,     1,     996000000U),
    PLLDDR(166,     1,     1,     1002000000U),
    PLLDDR(41,     0,     0,     1008000000U),
    PLLDDR(168,     1,     1,     1014000000U),
    PLLDDR(84,     0,     1,     1020000000U),
    PLLDDR(170,     1,     1,     1026000000U),
    PLLDDR(42,     0,     0,     1032000000U),
    PLLDDR(172,     1,     1,     1038000000U),
    PLLDDR(86,     0,     1,     1044000000U),
    PLLDDR(174,     1,     1,     1050000000U),
    PLLDDR(43,     0,     0,     1056000000U),
    PLLDDR(176,     1,     1,     1062000000U),
    PLLDDR(88,     0,     1,     1068000000U),
    PLLDDR(178,     1,     1,     1074000000U),
    PLLDDR(44,     0,     0,     1080000000U),
    PLLDDR(180,     1,     1,     1086000000U),
    PLLDDR(90,     0,     1,     1092000000U),
    PLLDDR(182,     1,     1,     1098000000U),
    PLLDDR(45,     0,     0,     1104000000U),
    PLLDDR(184,     1,     1,     1110000000U),
    PLLDDR(92,     0,     1,     1116000000U),
    PLLDDR(186,     1,     1,     1122000000U),
    PLLDDR(46,     0,     0,     1128000000U),
    PLLDDR(188,     1,     1,     1134000000U),
    PLLDDR(94,     0,     1,     1140000000U),
    PLLDDR(190,     1,     1,     1146000000U),
    PLLDDR(47,     0,     0,     1152000000U),
    PLLDDR(192,     1,     1,     1158000000U),
    PLLDDR(96,     0,     1,     1164000000U),
    PLLDDR(194,     1,     1,     1170000000U),
    PLLDDR(48,     0,     0,     1176000000U),
    PLLDDR(196,     1,     1,     1182000000U),
    PLLDDR(98,     0,     1,     1188000000U),
    PLLDDR(198,     1,     1,     1194000000U),
    PLLDDR(49,     0,     0,     1200000000U),
    PLLDDR(100,     1,     0,     1212000000U),
    PLLDDR(50,     0,     0,     1224000000U),
    PLLDDR(102,     1,     0,     1236000000U),
    PLLDDR(51,     0,     0,     1248000000U),
    PLLDDR(104,     1,     0,     1260000000U),
    PLLDDR(52,     0,     0,     1272000000U),
    PLLDDR(106,     1,     0,     1284000000U),
    PLLDDR(53,     0,     0,     1296000000U),
    PLLDDR(108,     1,     0,     1308000000U),
    PLLDDR(54,     0,     0,     1320000000U),
    PLLDDR(110,     1,     0,     1332000000U),
    PLLDDR(55,     0,     0,     1344000000U),
    PLLDDR(112,     1,     0,     1356000000U),
    PLLDDR(56,     0,     0,     1368000000U),
    PLLDDR(114,     1,     0,     1380000000U),
    PLLDDR(57,     0,     0,     1392000000U),
    PLLDDR(116,     1,     0,     1404000000U),
    PLLDDR(58,     0,     0,     1416000000U),
    PLLDDR(118,     1,     0,     1428000000U),
    PLLDDR(59,     0,     0,     1440000000U),
    PLLDDR(120,     1,     0,     1452000000U),
    PLLDDR(60,     0,     0,     1464000000U),
    PLLDDR(122,     1,     0,     1476000000U),
    PLLDDR(61,     0,     0,     1488000000U),
    PLLDDR(124,     1,     0,     1500000000U),
    PLLDDR(62,     0,     0,     1512000000U),
    PLLDDR(126,     1,     0,     1524000000U),
    PLLDDR(63,     0,     0,     1536000000U),
    PLLDDR(128,     1,     0,     1548000000U),
    PLLDDR(64,     0,     0,     1560000000U),
    PLLDDR(130,     1,     0,     1572000000U),
    PLLDDR(65,     0,     0,     1584000000U),
    PLLDDR(132,     1,     0,     1596000000U),
    PLLDDR(66,     0,     0,     1608000000U),
    PLLDDR(134,     1,     0,     1620000000U),
    PLLDDR(67,     0,     0,     1632000000U),
    PLLDDR(136,     1,     0,     1644000000U),
    PLLDDR(68,     0,     0,     1656000000U),
    PLLDDR(138,     1,     0,     1668000000U),
    PLLDDR(69,     0,     0,     1680000000U),
    PLLDDR(140,     1,     0,     1692000000U),
    PLLDDR(70,     0,     0,     1704000000U),
    PLLDDR(142,     1,     0,     1716000000U),
    PLLDDR(71,     0,     0,     1728000000U),
    PLLDDR(144,     1,     0,     1740000000U),
    PLLDDR(72,     0,     0,     1752000000U),
    PLLDDR(146,     1,     0,     1764000000U),
    PLLDDR(73,     0,     0,     1776000000U),
    PLLDDR(148,     1,     0,     1788000000U),
    PLLDDR(74,     0,     0,     1800000000U),
    PLLDDR(150,     1,     0,     1812000000U),
    PLLDDR(75,     0,     0,     1824000000U),
    PLLDDR(152,     1,     0,     1836000000U),
    PLLDDR(76,     0,     0,     1848000000U),
    PLLDDR(154,     1,     0,     1860000000U),
    PLLDDR(77,     0,     0,     1872000000U),
    PLLDDR(156,     1,     0,     1884000000U),
    PLLDDR(78,     0,     0,     1896000000U),
    PLLDDR(158,     1,     0,     1908000000U),
    PLLDDR(79,     0,     0,     1920000000U),
    PLLDDR(160,     1,     0,     1932000000U),
    PLLDDR(80,     0,     0,     1944000000U),
    PLLDDR(162,     1,     0,     1956000000U),
    PLLDDR(81,     0,     0,     1968000000U),
    PLLDDR(164,     1,     0,     1980000000U),
    PLLDDR(82,     0,     0,     1992000000U),
    PLLDDR(166,     1,     0,     2004000000U),
    PLLDDR(83,     0,     0,     2016000000U),
    PLLDDR(168,     1,     0,     2028000000U),
    PLLDDR(84,     0,     0,     2040000000U),
    PLLDDR(170,     1,     0,     2052000000U),
    PLLDDR(85,     0,     0,     2064000000U),
    PLLDDR(172,     1,     0,     2076000000U),
    PLLDDR(86,     0,     0,     2088000000U),
    PLLDDR(174,     1,     0,     2100000000U),
    PLLDDR(87,     0,     0,     2112000000U),
    PLLDDR(176,     1,     0,     2124000000U),
    PLLDDR(88,     0,     0,     2136000000U),
    PLLDDR(178,     1,     0,     2148000000U),
    PLLDDR(89,     0,     0,     2160000000U),
};

/* PLLPERIPH0(n, d1, d2, freq)  F_N8X8_D1V1X1_D2V0X1 */
struct sunxi_clk_factor_freq factor_pllperiph0_tbl[] =
{
    PLLPERIPH0(49,     1,     1,     300000000U),
    PLLPERIPH0(50,     1,     1,     306000000U),
    PLLPERIPH0(25,     0,     1,     312000000U),
    PLLPERIPH0(52,     1,     1,     318000000U),
    PLLPERIPH0(26,     0,     1,     324000000U),
    PLLPERIPH0(54,     1,     1,     330000000U),
    PLLPERIPH0(27,     0,     1,     336000000U),
    PLLPERIPH0(56,     1,     1,     342000000U),
    PLLPERIPH0(28,     0,     1,     348000000U),
    PLLPERIPH0(58,     1,     1,     354000000U),
    PLLPERIPH0(29,     0,     1,     360000000U),
    PLLPERIPH0(60,     1,     1,     366000000U),
    PLLPERIPH0(30,     0,     1,     372000000U),
    PLLPERIPH0(62,     1,     1,     378000000U),
    PLLPERIPH0(31,     0,     1,     384000000U),
    PLLPERIPH0(64,     1,     1,     390000000U),
    PLLPERIPH0(32,     0,     1,     396000000U),
    PLLPERIPH0(66,     1,     1,     402000000U),
    PLLPERIPH0(16,     0,     0,     408000000U),
    PLLPERIPH0(68,     1,     1,     414000000U),
    PLLPERIPH0(34,     0,     1,     420000000U),
    PLLPERIPH0(70,     1,     1,     426000000U),
    PLLPERIPH0(17,     0,     0,     432000000U),
    PLLPERIPH0(72,     1,     1,     438000000U),
    PLLPERIPH0(36,     0,     1,     444000000U),
    PLLPERIPH0(74,     1,     1,     450000000U),
    PLLPERIPH0(18,     0,     0,     456000000U),
    PLLPERIPH0(76,     1,     1,     462000000U),
    PLLPERIPH0(38,     0,     1,     468000000U),
    PLLPERIPH0(78,     1,     1,     474000000U),
    PLLPERIPH0(19,     0,     0,     480000000U),
    PLLPERIPH0(80,     1,     1,     486000000U),
    PLLPERIPH0(40,     0,     1,     492000000U),
    PLLPERIPH0(82,     1,     1,     498000000U),
    PLLPERIPH0(20,     0,     0,     504000000U),
    PLLPERIPH0(84,     1,     1,     510000000U),
    PLLPERIPH0(42,     0,     1,     516000000U),
    PLLPERIPH0(86,     1,     1,     522000000U),
    PLLPERIPH0(21,     0,     0,     528000000U),
    PLLPERIPH0(88,     1,     1,     534000000U),
    PLLPERIPH0(44,     0,     1,     540000000U),
    PLLPERIPH0(90,     1,     1,     546000000U),
    PLLPERIPH0(22,     0,     0,     552000000U),
    PLLPERIPH0(92,     1,     1,     558000000U),
    PLLPERIPH0(46,     0,     1,     564000000U),
    PLLPERIPH0(94,     1,     1,     570000000U),
    PLLPERIPH0(23,     0,     0,     576000000U),
    PLLPERIPH0(96,     1,     1,     582000000U),
    PLLPERIPH0(48,     0,     1,     588000000U),
    PLLPERIPH0(98,     1,     1,     594000000U),
    PLLPERIPH0(24,     0,     0,     600000000U),
    PLLPERIPH0(100,     1,     1,     606000000U),
    PLLPERIPH0(50,     0,     1,     612000000U),
    PLLPERIPH0(102,     1,     1,     618000000U),
    PLLPERIPH0(25,     0,     0,     624000000U),
    PLLPERIPH0(104,     1,     1,     630000000U),
    PLLPERIPH0(52,     0,     1,     636000000U),
};

/* PLLPERIPH1(n, d1, d2, freq)  F_N8X8_D1V1X1_D2V0X1 */
struct sunxi_clk_factor_freq factor_pllperiph1_tbl[] =
{
    PLLPERIPH1(49,     1,     1,     300000000U),
    PLLPERIPH1(50,     1,     1,     306000000U),
    PLLPERIPH1(25,     0,     1,     312000000U),
    PLLPERIPH1(52,     1,     1,     318000000U),
    PLLPERIPH1(26,     0,     1,     324000000U),
    PLLPERIPH1(54,     1,     1,     330000000U),
    PLLPERIPH1(27,     0,     1,     336000000U),
    PLLPERIPH1(56,     1,     1,     342000000U),
    PLLPERIPH1(28,     0,     1,     348000000U),
    PLLPERIPH1(58,     1,     1,     354000000U),
    PLLPERIPH1(29,     0,     1,     360000000U),
    PLLPERIPH1(60,     1,     1,     366000000U),
    PLLPERIPH1(30,     0,     1,     372000000U),
    PLLPERIPH1(62,     1,     1,     378000000U),
    PLLPERIPH1(31,     0,     1,     384000000U),
    PLLPERIPH1(64,     1,     1,     390000000U),
    PLLPERIPH1(32,     0,     1,     396000000U),
    PLLPERIPH1(66,     1,     1,     402000000U),
    PLLPERIPH1(16,     0,     0,     408000000U),
    PLLPERIPH1(68,     1,     1,     414000000U),
    PLLPERIPH1(34,     0,     1,     420000000U),
    PLLPERIPH1(70,     1,     1,     426000000U),
    PLLPERIPH1(17,     0,     0,     432000000U),
    PLLPERIPH1(72,     1,     1,     438000000U),
    PLLPERIPH1(36,     0,     1,     444000000U),
    PLLPERIPH1(74,     1,     1,     450000000U),
    PLLPERIPH1(18,     0,     0,     456000000U),
    PLLPERIPH1(76,     1,     1,     462000000U),
    PLLPERIPH1(38,     0,     1,     468000000U),
    PLLPERIPH1(78,     1,     1,     474000000U),
    PLLPERIPH1(19,     0,     0,     480000000U),
    PLLPERIPH1(80,     1,     1,     486000000U),
    PLLPERIPH1(40,     0,     1,     492000000U),
    PLLPERIPH1(82,     1,     1,     498000000U),
    PLLPERIPH1(20,     0,     0,     504000000U),
    PLLPERIPH1(84,     1,     1,     510000000U),
    PLLPERIPH1(42,     0,     1,     516000000U),
    PLLPERIPH1(86,     1,     1,     522000000U),
    PLLPERIPH1(21,     0,     0,     528000000U),
    PLLPERIPH1(88,     1,     1,     534000000U),
    PLLPERIPH1(44,     0,     1,     540000000U),
    PLLPERIPH1(90,     1,     1,     546000000U),
    PLLPERIPH1(22,     0,     0,     552000000U),
    PLLPERIPH1(92,     1,     1,     558000000U),
    PLLPERIPH1(46,     0,     1,     564000000U),
    PLLPERIPH1(94,     1,     1,     570000000U),
    PLLPERIPH1(23,     0,     0,     576000000U),
    PLLPERIPH1(96,     1,     1,     582000000U),
    PLLPERIPH1(48,     0,     1,     588000000U),
    PLLPERIPH1(98,     1,     1,     594000000U),
    PLLPERIPH1(24,     0,     0,     600000000U),
    PLLPERIPH1(100,     1,     1,     606000000U),
    PLLPERIPH1(50,     0,     1,     612000000U),
    PLLPERIPH1(102,     1,     1,     618000000U),
    PLLPERIPH1(25,     0,     0,     624000000U),
    PLLPERIPH1(104,     1,     1,     630000000U),
    PLLPERIPH1(52,     0,     1,     636000000U),
};

/* PLLVIDEO0(n, d1, freq)   F_N8X8_D1V1X1 */
struct sunxi_clk_factor_freq factor_pllvideo_tbl[] =
{
    PLLVIDEO0(23,     1,     72000000U),
    PLLVIDEO0(24,     1,     75000000U),
    PLLVIDEO0(12,     0,     78000000U),
    PLLVIDEO0(26,     1,     81000000U),
    PLLVIDEO0(13,     0,     84000000U),
    PLLVIDEO0(28,     1,     87000000U),
    PLLVIDEO0(14,     0,     90000000U),
    PLLVIDEO0(30,     1,     93000000U),
    PLLVIDEO0(15,     0,     96000000U),
    PLLVIDEO0(32,     1,     99000000U),
    PLLVIDEO0(16,     0,     102000000U),
    PLLVIDEO0(34,     1,     105000000U),
    PLLVIDEO0(17,     0,     108000000U),
    PLLVIDEO0(36,     1,     111000000U),
    PLLVIDEO0(18,     0,     114000000U),
    PLLVIDEO0(38,     1,     117000000U),
    PLLVIDEO0(19,     0,     120000000U),
    PLLVIDEO0(40,     1,     123000000U),
    PLLVIDEO0(20,     0,     126000000U),
    PLLVIDEO0(42,     1,     129000000U),
    PLLVIDEO0(21,     0,     132000000U),
    PLLVIDEO0(44,     1,     135000000U),
    PLLVIDEO0(22,     0,     138000000U),
    PLLVIDEO0(46,     1,     141000000U),
    PLLVIDEO0(23,     0,     144000000U),
    PLLVIDEO0(48,     1,     147000000U),
    PLLVIDEO0(24,     0,     150000000U),
    PLLVIDEO0(50,     1,     153000000U),
    PLLVIDEO0(25,     0,     156000000U),
    PLLVIDEO0(52,     1,     159000000U),
    PLLVIDEO0(26,     0,     162000000U),
    PLLVIDEO0(54,     1,     165000000U),
    PLLVIDEO0(27,     0,     168000000U),
    PLLVIDEO0(56,     1,     171000000U),
    PLLVIDEO0(28,     0,     174000000U),
    PLLVIDEO0(58,     1,     177000000U),
    PLLVIDEO0(29,     0,     180000000U),
    PLLVIDEO0(60,     1,     183000000U),
    PLLVIDEO0(30,     0,     186000000U),
    PLLVIDEO0(62,     1,     189000000U),
    PLLVIDEO0(31,     0,     192000000U),
    PLLVIDEO0(64,     1,     195000000U),
    PLLVIDEO0(32,     0,     198000000U),
    PLLVIDEO0(66,     1,     201000000U),
    PLLVIDEO0(33,     0,     204000000U),
    PLLVIDEO0(68,     1,     207000000U),
    PLLVIDEO0(34,     0,     210000000U),
    PLLVIDEO0(70,     1,     213000000U),
    PLLVIDEO0(35,     0,     216000000U),
    PLLVIDEO0(72,     1,     219000000U),
    PLLVIDEO0(36,     0,     222000000U),
    PLLVIDEO0(74,     1,     225000000U),
    PLLVIDEO0(37,     0,     228000000U),
    PLLVIDEO0(76,     1,     231000000U),
    PLLVIDEO0(38,     0,     234000000U),
    PLLVIDEO0(78,     1,     237000000U),
    PLLVIDEO0(39,     0,     240000000U),
    PLLVIDEO0(80,     1,     243000000U),
    PLLVIDEO0(40,     0,     246000000U),
    PLLVIDEO0(82,     1,     249000000U),
    PLLVIDEO0(41,     0,     252000000U),
    PLLVIDEO0(84,     1,     255000000U),
    PLLVIDEO0(42,     0,     258000000U),
    PLLVIDEO0(86,     1,     261000000U),
    PLLVIDEO0(43,     0,     264000000U),
    PLLVIDEO0(88,     1,     267000000U),
    PLLVIDEO0(44,     0,     270000000U),
    PLLVIDEO0(90,     1,     273000000U),
    PLLVIDEO0(45,     0,     276000000U),
    PLLVIDEO0(92,     1,     279000000U),
    PLLVIDEO0(46,     0,     282000000U),
    PLLVIDEO0(94,     1,     285000000U),
    PLLVIDEO0(47,     0,     288000000U),
    PLLVIDEO0(96,     1,     291000000U),
    PLLVIDEO0(48,     0,     294000000U),
    PLLVIDEO0(98,     1,     297000000U),
    PLLVIDEO0(49,     0,     300000000U),
    PLLVIDEO0(100,     1,     303000000U),
    PLLVIDEO0(50,     0,     306000000U),
    PLLVIDEO0(102,     1,     309000000U),
    PLLVIDEO0(51,     0,     312000000U),
    PLLVIDEO0(104,     1,     315000000U),
    PLLVIDEO0(52,     0,     318000000U),
    PLLVIDEO0(106,     1,     321000000U),
    PLLVIDEO0(53,     0,     324000000U),
    PLLVIDEO0(108,     1,     327000000U),
    PLLVIDEO0(54,     0,     330000000U),
    PLLVIDEO0(110,     1,     333000000U),
    PLLVIDEO0(55,     0,     336000000U),
    PLLVIDEO0(112,     1,     339000000U),
    PLLVIDEO0(56,     0,     342000000U),
    PLLVIDEO0(114,     1,     345000000U),
    PLLVIDEO0(57,     0,     348000000U),
    PLLVIDEO0(116,     1,     351000000U),
    PLLVIDEO0(58,     0,     354000000U),
    PLLVIDEO0(118,     1,     357000000U),
    PLLVIDEO0(59,     0,     360000000U),
    PLLVIDEO0(120,     1,     363000000U),
    PLLVIDEO0(60,     0,     366000000U),
    PLLVIDEO0(122,     1,     369000000U),
    PLLVIDEO0(61,     0,     372000000U),
    PLLVIDEO0(124,     1,     375000000U),
    PLLVIDEO0(62,     0,     378000000U),
    PLLVIDEO0(126,     1,     381000000U),
    PLLVIDEO0(63,     0,     384000000U),
    PLLVIDEO0(128,     1,     387000000U),
    PLLVIDEO0(64,     0,     390000000U),
    PLLVIDEO0(130,     1,     393000000U),
    PLLVIDEO0(65,     0,     396000000U),
    PLLVIDEO0(132,     1,     399000000U),
    PLLVIDEO0(66,     0,     402000000U),
    PLLVIDEO0(134,     1,     405000000U),
    PLLVIDEO0(67,     0,     408000000U),
    PLLVIDEO0(136,     1,     411000000U),
    PLLVIDEO0(68,     0,     414000000U),
    PLLVIDEO0(138,     1,     417000000U),
    PLLVIDEO0(69,     0,     420000000U),
    PLLVIDEO0(140,     1,     423000000U),
    PLLVIDEO0(70,     0,     426000000U),
    PLLVIDEO0(142,     1,     429000000U),
    PLLVIDEO0(71,     0,     432000000U),
    PLLVIDEO0(144,     1,     435000000U),
    PLLVIDEO0(72,     0,     438000000U),
    PLLVIDEO0(146,     1,     441000000U),
    PLLVIDEO0(73,     0,     444000000U),
    PLLVIDEO0(148,     1,     447000000U),
    PLLVIDEO0(74,     0,     450000000U),
    PLLVIDEO0(150,     1,     453000000U),
    PLLVIDEO0(75,     0,     456000000U),
    PLLVIDEO0(152,     1,     459000000U),
    PLLVIDEO0(76,     0,     462000000U),
    PLLVIDEO0(154,     1,     465000000U),
    PLLVIDEO0(77,     0,     468000000U),
    PLLVIDEO0(156,     1,     471000000U),
    PLLVIDEO0(78,     0,     474000000U),
    PLLVIDEO0(158,     1,     477000000U),
    PLLVIDEO0(79,     0,     480000000U),
    PLLVIDEO0(160,     1,     483000000U),
    PLLVIDEO0(80,     0,     486000000U),
    PLLVIDEO0(162,     1,     489000000U),
    PLLVIDEO0(81,     0,     492000000U),
    PLLVIDEO0(164,     1,     495000000U),
    PLLVIDEO0(82,     0,     498000000U),
    PLLVIDEO0(166,     1,     501000000U),
    PLLVIDEO0(83,     0,     504000000U),
    PLLVIDEO0(168,     1,     507000000U),
    PLLVIDEO0(84,     0,     510000000U),
    PLLVIDEO0(170,     1,     513000000U),
    PLLVIDEO0(85,     0,     516000000U),
    PLLVIDEO0(172,     1,     519000000U),
    PLLVIDEO0(86,     0,     522000000U),
    PLLVIDEO0(174,     1,     525000000U),
    PLLVIDEO0(87,     0,     528000000U),
    PLLVIDEO0(176,     1,     531000000U),
    PLLVIDEO0(88,     0,     534000000U),
    PLLVIDEO0(178,     1,     537000000U),
    PLLVIDEO0(89,     0,     540000000U),
    PLLVIDEO0(180,     1,     543000000U),
    PLLVIDEO0(90,     0,     546000000U),
    PLLVIDEO0(182,     1,     549000000U),
    PLLVIDEO0(91,     0,     552000000U),
    PLLVIDEO0(184,     1,     555000000U),
    PLLVIDEO0(92,     0,     558000000U),
    PLLVIDEO0(186,     1,     561000000U),
    PLLVIDEO0(93,     0,     564000000U),
    PLLVIDEO0(188,     1,     567000000U),
    PLLVIDEO0(94,     0,     570000000U),
    PLLVIDEO0(190,     1,     573000000U),
    PLLVIDEO0(95,     0,     576000000U),
    PLLVIDEO0(192,     1,     579000000U),
    PLLVIDEO0(96,     0,     582000000U),
    PLLVIDEO0(194,     1,     585000000U),
    PLLVIDEO0(97,     0,     588000000U),
    PLLVIDEO0(196,     1,     591000000U),
    PLLVIDEO0(98,     0,     594000000U),
    PLLVIDEO0(198,     1,     597000000U),
    PLLVIDEO0(99,     0,     600000000U),
    PLLVIDEO0(200,     1,     603000000U),
    PLLVIDEO0(100,     0,     606000000U),
    PLLVIDEO0(202,     1,     609000000U),
    PLLVIDEO0(101,     0,     612000000U),
    PLLVIDEO0(204,     1,     615000000U),
    PLLVIDEO0(102,     0,     618000000U),
    PLLVIDEO0(206,     1,     621000000U),
    PLLVIDEO0(103,     0,     624000000U),
    PLLVIDEO0(208,     1,     627000000U),
    PLLVIDEO0(104,     0,     630000000U),
};


#define FACTOR_SIZEOF(name) (sizeof(factor_pll##name##_tbl)/ \
                             sizeof(struct sunxi_clk_factor_freq))

#define FACTOR_SEARCH(name) (sunxi_clk_com_ftr_sr( \
                             &sunxi_clk_factor_config_pll_##name, factor, \
                             factor_pll##name##_tbl, index, \
                             FACTOR_SIZEOF(name)))

/**These clock belong to fixed clock in sun8iw18p1_clk.dtsi**/
SUNXI_CLK_FIXED_SRC(losc,  HAL_CLK_SRC_LOSC,  HAL_CLK_SRC_ROOT, HAL_CLK_ROOT, 32768U, 0);           /* defined as RTC_32K in spec*/
SUNXI_CLK_FIXED_SRC(iosc,  HAL_CLK_SRC_IOSC16M,  HAL_CLK_SRC_ROOT, HAL_CLK_ROOT, 16000000U, 0);     /* defined as RC61M in spec*/
SUNXI_CLK_FIXED_SRC(hosc,  HAL_CLK_SRC_HOSC24M,  HAL_CLK_SRC_ROOT, HAL_CLK_ROOT, 24000000U, 0);     /* defined as OSC24M in spec*/
SUNXI_CLK_FIXED_SRC(pll_periph0div25m,  HAL_CLK_PLL_PERI0DIV25M,  HAL_CLK_SRC_ROOT, HAL_CLK_ROOT, 25000000U, 0);     /* virtual clk for */
SUNXI_CLK_FIXED_SRC(osc48m, HAL_CLK_SRC_OSC48M, HAL_CLK_SRC_ROOT, HAL_CLK_ROOT, 48000000U, 0);
SUNXI_CLK_FIXED_SRC(hoscd2, HAL_CLK_SRC_HOSC24MD2, HAL_CLK_SRC_HOSC24M, HAL_CLK_FIXED_SRC, 12000000U, 24000000U);
SUNXI_CLK_FIXED_SRC(osc48md4, HAL_CLK_SRC_OSC48MD4, HAL_CLK_SRC_OSC48M, HAL_CLK_FIXED_SRC, 12000000U, 48000000U);


/**These clock belong to fixed factor clock in sun8iw18p1_clk.dtsi**/
SUNXI_CLK_FIXED_FACTOR(pll_periph0x2, HAL_CLK_PLL_PERI0X2, HAL_CLK_PLL_PERI0, HAL_CLK_FACTOR, 2, 1);
SUNXI_CLK_FIXED_FACTOR(pll_periph1x2, HAL_CLK_PLL_PERI1X2, HAL_CLK_PLL_PERI1, HAL_CLK_FACTOR, 2, 1);
SUNXI_CLK_FIXED_FACTOR(pll_audiox4, HAL_CLK_PLL_AUDIOX4, HAL_CLK_PLL_AUDIO, HAL_CLK_FACTOR, 4, 1);
SUNXI_CLK_FIXED_FACTOR(pll_audiox2, HAL_CLK_PLL_AUDIOX2, HAL_CLK_PLL_AUDIO, HAL_CLK_FACTOR, 2, 1);
SUNXI_CLK_FIXED_FACTOR(pll_videox4, HAL_CLK_PLL_VIDEOX4, HAL_CLK_PLL_VIDEO, HAL_CLK_FACTOR, 4, 1);
SUNXI_CLK_FIXED_FACTOR(pll_ddrdiv4, HAL_CLK_PLL_DDRDIV4, HAL_CLK_PLL_DDR0, HAL_CLK_FACTOR, 1, 4);

/*                       name,           ns  nw  ks  kw  ms  mw  ps  pw  d1s d1w d2s d2w {frac   out mode}   en-s    sdmss   sdmsw   sdmpat             sdmval  mux_in-s out_en-s*/
SUNXI_CLK_FACTORS_CONFIG(pll_cpu,        8,  8,  0,  0,  0,  0,  16, 2,  0,  0,  0,  0,    0,    0,  0,      31,     0,      0,      0,                 0,           23,  27);
SUNXI_CLK_FACTORS_CONFIG(pll_ddr,        8,  8,  0,  0,  0,  0,  0,  0,  1,  1,  0,  1,    0,    0,  0,      31,     24,     0,      CLK_PLL_DDRPAT,    0xd1303333,  23,  27);
SUNXI_CLK_FACTORS_CONFIG(pll_periph0,    8,  8,  0,  0,  0,  0,  0,  0,  1,  1,  0,  1,    0,    0,  0,      31,     0,      0,      0,                 0,           23,  27);
SUNXI_CLK_FACTORS_CONFIG(pll_periph1,    8,  8,  0,  0,  0,  0,  0,  0,  1,  1,  0,  1,    0,    0,  0,      31,     24,     0,      CLK_PLL_PERI1PAT0, 0xd1303333,  23,  27);
SUNXI_CLK_FACTORS_CONFIG(pll_video,      8,  8,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,    0,    0,  0,      31,     0,     0,      CLK_PLL_PERI1PAT0, 0xd1303333,  23,  27);
SUNXI_CLK_FACTORS_CONFIG(pll_audio,      8,  8,  0,  0,  0,  0,  16, 6,  1,  1,  0,  1,    0,    0,  0,      31,     24,     1,      CLK_PLL_AUDIOPAT0, 0xc00121ff,  23,  27);
SUNXI_CLK_FACTORS_CONFIG(pll_csi,        8,  8,  0,  0,  0,  0,  0,  0,  1,  1,  0,  1,    0,    0,  0,      31,     0,      0,      CLK_PLL_CSIPAT0,   0xc00121ff,  23,  27);

/* name        reg              lock_reg    lock_bit pll_lock_ctrl_reg lock_en_bit */
SUNXI_CLK_FACTORS_INIT(pll_cpu,      CLK_PLL_CPU,     CLK_PLL_CPU,     28,  CLK_PLL_CPU,     29);
SUNXI_CLK_FACTORS_INIT(pll_ddr,      CLK_PLL_DDR,     CLK_PLL_DDR,     28,  CLK_PLL_DDR,     29);
SUNXI_CLK_FACTORS_INIT(pll_periph0,  CLK_PLL_PERIPH0, CLK_PLL_PERIPH0, 28,  CLK_PLL_PERIPH0, 29);
SUNXI_CLK_FACTORS_INIT(pll_periph1,  CLK_PLL_PERIPH1, CLK_PLL_PERIPH1, 28,  CLK_PLL_PERIPH1, 29);
SUNXI_CLK_FACTORS_INIT(pll_video,    CLK_PLL_VIDEO0,  CLK_PLL_VIDEO0,  28,  CLK_PLL_VIDEO0,  29);
SUNXI_CLK_FACTORS_INIT(pll_audio,    CLK_PLL_AUDIO,   CLK_PLL_AUDIO,   28,  CLK_PLL_AUDIO,   29);
SUNXI_CLK_FACTORS_INIT(pll_csi,      CLK_PLL_CSI,     CLK_PLL_CSI,     28,  CLK_PLL_CSI,     29);

SUNXI_CLK_FACTOR(pll_cpu, HAL_CLK_PLL_CPUX_C0, HAL_CLK_SRC_HOSC24M, HAL_CLK_FIXED_SRC, 1200000000U, 24000000U);
SUNXI_CLK_FACTOR(pll_ddr, HAL_CLK_PLL_DDR0, HAL_CLK_SRC_HOSC24M, HAL_CLK_FIXED_SRC, 1056000000U, 24000000U);
SUNXI_CLK_FACTOR(pll_periph0, HAL_CLK_PLL_PERI0, HAL_CLK_SRC_HOSC24M, HAL_CLK_FIXED_SRC, 600000000U, 24000000U);
SUNXI_CLK_FACTOR(pll_periph1, HAL_CLK_PLL_PERI1, HAL_CLK_SRC_HOSC24M, HAL_CLK_FIXED_SRC, 600000000U, 24000000U);
SUNXI_CLK_FACTOR(pll_audio, HAL_CLK_PLL_AUDIO, HAL_CLK_SRC_HOSC24M, HAL_CLK_FIXED_SRC, 24576000U, 24000000U);
SUNXI_CLK_FACTOR(pll_video, HAL_CLK_PLL_VIDEO, HAL_CLK_SRC_HOSC24M, HAL_CLK_FIXED_SRC, 99000000U, 24000000U);
SUNXI_CLK_FACTOR(pll_csi, HAL_CLK_PLL_CSI, HAL_CLK_SRC_HOSC24M, HAL_CLK_FIXED_SRC, 432000000U, 24000000U);

hal_clk_id_t hosc_parents[] = {HAL_CLK_SRC_HOSC24M};
hal_clk_id_t losc_parents[] = {HAL_CLK_SRC_LOSC};
hal_clk_id_t cpu_parents[] = {HAL_CLK_SRC_HOSC24M, HAL_CLK_SRC_LOSC, HAL_CLK_SRC_IOSC16M, HAL_CLK_PLL_CPUX_C0, HAL_CLK_PLL_PERI0};
hal_clk_id_t axi_parents[] = {HAL_CLK_BUS_C0_CPU};
hal_clk_id_t psi_parents[] = {HAL_CLK_SRC_HOSC24M, HAL_CLK_SRC_LOSC, HAL_CLK_SRC_IOSC16M, HAL_CLK_PLL_PERI0};
hal_clk_id_t ahb1_parents[] = {HAL_CLK_BUS_PSI};
hal_clk_id_t ahb2_parents[] = {HAL_CLK_BUS_PSI};
hal_clk_id_t ahb3_parents[] = {HAL_CLK_SRC_HOSC24M, HAL_CLK_SRC_LOSC, HAL_CLK_BUS_PSI, HAL_CLK_PLL_PERI0};
hal_clk_id_t apb1_parents[] = {HAL_CLK_SRC_HOSC24M, HAL_CLK_SRC_LOSC, HAL_CLK_BUS_PSI, HAL_CLK_PLL_PERI0};
hal_clk_id_t apb2_parents[] = {HAL_CLK_SRC_HOSC24M, HAL_CLK_SRC_LOSC, HAL_CLK_BUS_PSI, HAL_CLK_PLL_PERI0};
hal_clk_id_t mbus_parents[] = {HAL_CLK_PLL_DDRDIV4};
hal_clk_id_t de_parents[] = {HAL_CLK_PLL_PERI1, HAL_CLK_PLL_PERI1X2, HAL_CLK_PLL_PERI0X2};
hal_clk_id_t ce_parents[] = {HAL_CLK_SRC_HOSC24M, HAL_CLK_PLL_PERI0X2};
hal_clk_id_t ve_parents[] = {HAL_CLK_PLL_PERI1, HAL_CLK_PLL_PERI1X2, HAL_CLK_PLL_PERI0, HAL_CLK_PLL_VIDEOX4};
hal_clk_id_t nna_parents[] = {HAL_CLK_PLL_PERI0, HAL_CLK_PLL_PERI0X2, HAL_CLK_PLL_PERI1, HAL_CLK_PLL_PERI1X2, HAL_CLK_PLL_VIDEOX4, HAL_CLK_PLL_CPUX_C0, HAL_CLK_PLL_CSI};
hal_clk_id_t sdram_parents[] = {HAL_CLK_PLL_DDR0};
hal_clk_id_t spi_parents[] = {HAL_CLK_SRC_HOSC24M, HAL_CLK_PLL_PERI0, HAL_CLK_PLL_PERI1, HAL_CLK_PLL_PERI0X2, HAL_CLK_PLL_PERI1X2};
hal_clk_id_t ephy_25m_parents[] = {HAL_CLK_PLL_PERI0DIV25M};
hal_clk_id_t nand_parents[] = {HAL_CLK_SRC_HOSC24M, HAL_CLK_PLL_PERI0, HAL_CLK_PLL_PERI1, HAL_CLK_PLL_PERI0X2, HAL_CLK_PLL_PERI1X2};
hal_clk_id_t smhc_parents[] = {HAL_CLK_SRC_HOSC24M, HAL_CLK_PLL_PERI0X2, HAL_CLK_PLL_PERI1X2};
hal_clk_id_t audio_parents[] = {HAL_CLK_PLL_AUDIO, HAL_CLK_PLL_AUDIOX2, HAL_CLK_PLL_AUDIOX4};
hal_clk_id_t usbohci_12m_parents[] = {HAL_CLK_SRC_OSC48MD4, HAL_CLK_SRC_HOSC24MD2, HAL_CLK_SRC_LOSC, HAL_CLK_SRC_IOSC16M};
hal_clk_id_t mipi_dphy0_parents[] = {HAL_CLK_PLL_VIDEO, HAL_CLK_PLL_VIDEOX4};
hal_clk_id_t mipi_host0_parents[] = {HAL_CLK_PLL_PERI0, HAL_CLK_PLL_PERI0X2, HAL_CLK_SRC_HOSC24M};
hal_clk_id_t csi_top_parents[] = {HAL_CLK_PLL_PERI1, HAL_CLK_PLL_PERI1X2, HAL_CLK_PLL_PERI0, HAL_CLK_PLL_PERI0X2, HAL_CLK_PLL_VIDEOX4, HAL_CLK_PLL_CSI};
hal_clk_id_t csi_master_parents[] = {HAL_CLK_SRC_HOSC24M, HAL_CLK_PLL_PERI1, HAL_CLK_PLL_PERI1X2, HAL_CLK_PLL_PERI0, HAL_CLK_PLL_PERI0X2, HAL_CLK_PLL_VIDEO, HAL_CLK_PLL_CSI};
hal_clk_id_t isp_parents[] = {HAL_CLK_PLL_PERI1, HAL_CLK_PLL_PERI1X2, HAL_CLK_PLL_PERI0, HAL_CLK_PLL_VIDEOX4, HAL_CLK_PLL_CSI};
hal_clk_id_t dspo_parents[] = {HAL_CLK_PLL_VIDEO, HAL_CLK_PLL_VIDEOX4, HAL_CLK_PLL_PERI0, HAL_CLK_PLL_PERI0X2, HAL_CLK_PLL_PERI1, HAL_CLK_PLL_PERI1X2, HAL_CLK_PLL_CSI};
hal_clk_id_t ahb1mod_parents[] = {HAL_CLK_BUS_AHB1};  /* some module use ahb1 as fixed-bus clk*/
hal_clk_id_t ahb3mod_parents[] = {HAL_CLK_BUS_AHB3};  /* some module use ahb3 as fixed-bus clk*/
hal_clk_id_t apb1mod_parents[] = {HAL_CLK_BUS_APB1};  /* some module use apb1 as fixed-bus clk*/
hal_clk_id_t apb2mod_parents[] = {HAL_CLK_BUS_APB2};  /* some module use apb2 as fixed-bus clk*/

struct sunxi_clk_comgate com_gates[] =
{
    {"codec",   0, 0x3, BUS_GATE_SHARE | RST_GATE_SHARE, 0},
    {"csi",     0, 0x1ff, BUS_GATE_SHARE | RST_GATE_SHARE | MBUS_GATE_SHARE, 0},
    {"mipi",    0, 0x3, BUS_GATE_SHARE | RST_GATE_SHARE | MBUS_GATE_SHARE, 0},
};

/*
SUNXI_CLK_PERIPH_CONFIG(name,           mux_reg,         mux_sft, mux_wid,      div_reg,            div_msft,  div_mwid,   div_nsft,   div_nwid,   gate_flag,  en_reg,          rst_reg,         bus_gate_reg,  drm_gate_reg,  en_sft,     rst_sft,    bus_gate_sft,   dram_gate_sft,  com_gate,         com_gate_off)
*/

SUNXI_CLK_PERIPH_CONFIG(cpu,            CLK_CPU_CFG,     24,      3,            0,                  0,         0,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(axi,            0,               0,       0,            CLK_CPU_CFG,        0,         2,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(cpuapb,         0,               0,       0,            CLK_CPU_CFG,        8,         2,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(psi,            CLK_PSI_CFG,     24,      2,            CLK_PSI_CFG,        0,         2,          8,          2,          0,          0,               CLK_PSI_GATE,    CLK_PSI_GATE,  0,             0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(ahb1,           0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(ahb2,           0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(ahb3,           CLK_AHB3_CFG,    24,      2,            CLK_AHB3_CFG,       0,         2,          8,          2,          0,          0,               0,               0,             0,             0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(apb1,           CLK_APB1_CFG,    24,      2,            CLK_APB1_CFG,       0,         2,          8,          2,          0,          0,               0,               0,             0,             0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(apb2,           CLK_APB2_CFG,    24,      2,            CLK_APB2_CFG,       0,         2,          8,          2,          0,          0,               0,               0,             0,             0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(mbus,           0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_MBUS_CFG,    0,             0,             0,          30,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(de,             CLK_DE_CFG,      24,      2,            CLK_DE_CFG,         0,         5,          0,          0,          0,          CLK_DE_CFG,      CLK_DE_GATE,     CLK_DE_GATE,   0,             31,         16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(g2d,            CLK_G2D_CFG,     24,      2,            CLK_G2D_CFG,        0,         5,          0,          0,          0,          CLK_G2D_CFG,     CLK_G2D_GATE,    CLK_G2D_GATE,  CLK_MBUS_GATE, 31,         16,         0,              10,             NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(ce,             CLK_CE_CFG,      24,      1,            CLK_CE_CFG,         0,         4,          8,          2,          0,          CLK_CE_CFG,      CLK_CE_GATE,     CLK_CE_GATE,   CLK_MBUS_GATE, 31,         16,         0,              2,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(ve,             CLK_VE_CFG,      24,      2,            CLK_VE_CFG,         0,         5,          0,          0,          0,          CLK_VE_CFG,      CLK_VE_GATE,     CLK_VE_GATE,   CLK_MBUS_GATE, 31,         16,         0,              1,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(eise,           CLK_EISE_CFG,    24,      2,            CLK_EISE_CFG,       0,         5,          0,          0,          0,          CLK_EISE_CFG,    CLK_EISE_GATE,   CLK_EISE_GATE, CLK_MBUS_GATE, 31,         16,         0,              23,             NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(nna,            CLK_NNA_CFG,     24,      3,            CLK_NNA_CFG,        0,         5,          0,          0,          0,          CLK_NNA_CFG,     CLK_NNA_GATE,    CLK_NNA_GATE,  0,             31,         16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(nna_rst,        0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_NNA_CFG,     0,             0,             0,          30,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(dma,            0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_DMA_GATE,    CLK_DMA_GATE,  CLK_MBUS_GATE, 0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(hstimer,        0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_HSTIMER_GATE, CLK_HSTIMER_GATE,     0,     0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(avs,            0,               0,       0,            0,                  0,         0,          0,          0,          0,          CLK_AVS_CFG,     0,               0,             0,             31,         0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(dbgsys,         0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_DBGSYS_GATE, CLK_DBGSYS_GATE,      0,      0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(pwm,            0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_PWM_GATE,    CLK_PWM_GATE,  0,             0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(iommu,          0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               0,               CLK_IOMMU_GATE, 0,            0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(sdram,          CLK_DRAM_CFG,    24,      2,            CLK_DRAM_CFG,       0,         2,          0,          0,          0,          0,               CLK_DRAM_GATE,   CLK_DRAM_GATE, 0,             0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(sdmmc0_mod,     CLK_SMHC0_CFG,   24,      2,            CLK_SMHC0_CFG,      0,         4,          8,          2,          0,          CLK_SMHC0_CFG,   0,               0,             0,             31,         0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(sdmmc0_rst,     0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_SMHC_GATE,   0,             0,             0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(sdmmc0_bus,     0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               0,              CLK_SMHC_GATE,  0,             0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(sdmmc1_mod,     CLK_SMHC1_CFG,   24,      2,            CLK_SMHC1_CFG,      0,         4,          8,          2,          0,          CLK_SMHC1_CFG,   0,               0,             0,             31,         0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(sdmmc1_rst,     0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_SMHC_GATE,   0,             0,             0,          17,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(sdmmc1_bus,     0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               0,              CLK_SMHC_GATE,  0,             0,          0,          1,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(sdmmc2_mod,     CLK_SMHC2_CFG,   24,      2,            CLK_SMHC2_CFG,      0,         4,          8,          2,          0,          CLK_SMHC2_CFG,   0,               0,             0,             31,         0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(sdmmc2_rst,     0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_SMHC_GATE,   0,             0,             0,          18,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(sdmmc2_bus,     0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               0,              CLK_SMHC_GATE,  0,             0,          0,          2,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(uart0,          0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_UART_GATE,  CLK_UART_GATE,  0,             0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(uart1,          0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_UART_GATE,  CLK_UART_GATE,  0,             0,          17,         1,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(uart2,          0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_UART_GATE,  CLK_UART_GATE,  0,             0,          18,         2,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(uart3,          0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_UART_GATE,  CLK_UART_GATE,  0,             0,          19,         3,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(twi0,           0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_TWI_GATE,   CLK_TWI_GATE,   0,             0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(twi1,           0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_TWI_GATE,   CLK_TWI_GATE,   0,             0,          17,         1,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(twi2,           0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_TWI_GATE,   CLK_TWI_GATE,   0,             0,          18,         2,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(twi3,           0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_TWI_GATE,   CLK_TWI_GATE,   0,             0,          19,         3,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(spi0,           CLK_SPI0_CFG,    24,      3,            CLK_SPI0_CFG,       0,         4,          8,          2,          0,          CLK_SPI0_CFG,    CLK_SPI_GATE,   CLK_SPI_GATE,   0,             31,         16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(spi1,           CLK_SPI1_CFG,    24,      3,            CLK_SPI1_CFG,       0,         4,          8,          2,          0,          CLK_SPI1_CFG,    CLK_SPI_GATE,   CLK_SPI_GATE,   0,             31,         17,         1,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(spi2,           CLK_SPI2_CFG,    24,      3,            CLK_SPI2_CFG,       0,         4,          8,          2,          0,          CLK_SPI2_CFG,    CLK_SPI_GATE,   CLK_SPI_GATE,   0,             31,         18,         2,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(ephy_25m,       0,               0,       0,            0,                  0,         0,          0,          0,          0,          CLK_EPHY25M_CFG, 0,              CLK_EPHY25M_CFG, 0,            31,         0,          30,             0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(gmac,           0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_GMAC_GATE,  CLK_GMAC_GATE,  0,             0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(gpadc,          0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_GPADC_GATE, CLK_GPADC_GATE, 0,             0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(ths,            0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_THS_GATE,   CLK_THS_GATE,   0,             0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(i2s0,           CLK_I2S0_CFG,    24,      2,            CLK_I2S0_CFG,       0,         0,          8,          2,          0,          CLK_I2S0_CFG,    CLK_I2S_GATE,   CLK_I2S_GATE,   0,             31,         16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(i2s1,           CLK_I2S1_CFG,    24,      2,            CLK_I2S1_CFG,       0,         0,          8,          2,          0,          CLK_I2S1_CFG,    CLK_I2S_GATE,   CLK_I2S_GATE,   0,             31,         17,         1,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(codec_1x,       CLK_CODEC_1X_CFG, 24,     2,            CLK_CODEC_1X_CFG,   0,         4,          0,          0,          0,          CLK_CODEC_1X_CFG, CLK_CODEC_GATE, CLK_CODEC_GATE, 0,            31,         16,         0,              0,              &com_gates[0],    0);
SUNXI_CLK_PERIPH_CONFIG(codec_4x,       CLK_CODEC_4X_CFG, 24,     2,            CLK_CODEC_4X_CFG,   0,         4,          0,          0,          0,          CLK_CODEC_4X_CFG, CLK_CODEC_GATE, CLK_CODEC_GATE, 0,            31,         16,         0,              0,              &com_gates[0],    1);
SUNXI_CLK_PERIPH_CONFIG(usbphy0,        0,               0,       0,            0,                  0,         0,          0,          0,          0,          CLK_USB0_CFG,    CLK_USB0_CFG,   0,              0,             29,         30,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(usbohci0,       0,               0,       0,            0,                  0,         0,          0,          0,          0,          CLK_USB0_CFG,    CLK_USB_GATE,   CLK_USB_GATE,   0,             31,         16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(usbohci0_12m,   CLK_USB0_CFG,    24,      2,            0,                  0,         0,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(usbehci0,       0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_USB_GATE,   CLK_USB_GATE,   0,             0,          20,         4,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(usbotg,         0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_USB_GATE,   CLK_USB_GATE,   0,             0,          24,         8,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(mipi_dphy0,     CLK_MIPI_DPHY0_CFG,  24,  2,            CLK_MIPI_DPHY0_CFG, 0,         4,          8,          2,          0,          CLK_MIPI_DPHY0_CFG, CLK_MIPI_GATE, CLK_MIPI_GATE, 0,            31,         16,         0,              0,              &com_gates[2],     0);
SUNXI_CLK_PERIPH_CONFIG(mipi_host0,     CLK_MIPI_HOST0_CFG,  24,  2,            CLK_MIPI_HOST0_CFG, 0,         4,          8,          2,          0,          CLK_MIPI_HOST0_CFG, CLK_MIPI_GATE, CLK_MIPI_GATE, 0,            31,         16,         0,              0,              &com_gates[2],     1);
SUNXI_CLK_PERIPH_CONFIG(display_top,    0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               CLK_DISPLAY_TOP_GATE, CLK_DISPLAY_TOP_GATE, 0, 0,          16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(tcon_lcd,       CLK_TCON_LCD_CFG, 24,     3,            0,                  0,         0,          0,          0,          0,          CLK_TCON_LCD_CFG, CLK_TCON_LCD_GATE, CLK_TCON_LCD_GATE, 0,      31,         16,         0,              0,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(csi_top,        CLK_CSI_TOP_CFG, 24,      3,            CLK_CSI_TOP_CFG,    0,         5,          0,          0,          0,          CLK_CSI_TOP_CFG, CLK_CSI_GATE,  CLK_CSI_GATE, CLK_MBUS_GATE, 31,        16,         0,              8,              &com_gates[1],     0);
SUNXI_CLK_PERIPH_CONFIG(csi_master0,    CLK_CSI_MASTER0_CFG, 24,  3,            CLK_CSI_MASTER0_CFG, 0,        5,          0,          0,          0,          CLK_CSI_MASTER0_CFG, CLK_CSI_GATE,  CLK_CSI_GATE, CLK_MBUS_GATE, 31,    16,         0,              8,              &com_gates[1],     1);
SUNXI_CLK_PERIPH_CONFIG(csi_master1,    CLK_CSI_MASTER1_CFG, 24,  3,            CLK_CSI_MASTER1_CFG, 0,        5,          0,          0,          0,          CLK_CSI_MASTER1_CFG, CLK_CSI_GATE,  CLK_CSI_GATE, CLK_MBUS_GATE, 31,    16,         0,              8,              &com_gates[1],     2);
SUNXI_CLK_PERIPH_CONFIG(isp,            CLK_ISP_CFG,     24,      3,            CLK_ISP_CFG,        0,         5,          0,          0,          0,          CLK_ISP_CFG,     0,               0,             CLK_MBUS_GATE, 31,         16,         0,              9,              NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(dspo,           CLK_DSPO_CFG,    24,      3,            CLK_DSPO_CFG,       0,         5,          8,          2,          0,          CLK_DSPO_CFG,    CLK_DSPO_GATE,   CLK_DSPO_GATE,  CLK_MBUS_GATE, 31,        16,         0,              27,             NULL,             0);
SUNXI_CLK_PERIPH_CONFIG(pio,            0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,              0,              NULL,             0);
//SUNXI_CLK_PERIPH_CONFIG(cpurcpus_pll,   0,               0,       0,            CLK_CPUS_CFG,           0,         5,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,             0,        NULL,             0);
//SUNXI_CLK_PERIPH_CONFIG(cpurcpus,       CLK_CPUS_CFG,        24,      2,        CLK_CPUS_CFG,           0,         0,          8,          2,          0,          0,               0,               0,             0,             0,          0,          0,             0,        NULL,             0);
//SUNXI_CLK_PERIPH_CONFIG(cpurahbs,       0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,             0,        NULL,             0);
//SUNXI_CLK_PERIPH_CONFIG(cpurapbs1,      0,               0,       0,            CLK_CPUS_APBS1_CFG,     0,         2,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,             0,        NULL,             0);
//SUNXI_CLK_PERIPH_CONFIG(cpurapbs2_pll,  0,               0,       0,            CLK_CPUS_APBS2_CFG,     0,         5,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,             0,        NULL,             0);
//SUNXI_CLK_PERIPH_CONFIG(cpurapbs2,      CLK_CPUS_APBS2_CFG,  24,      2,        CLK_CPUS_APBS2_CFG,     0,         0,          8,          2,          0,          0,               0,               0,             0,             0,          0,          0,             0,        NULL,             0);
//SUNXI_CLK_PERIPH_CONFIG(losc_out,       0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               0,               CLK_LOSC_OUT_GATE, 0,             0,          0,          0,             0,        NULL,             0);
//SUNXI_CLK_PERIPH_CONFIG(cpurpio,        0,               0,       0,            0,                  0,         0,          0,          0,          0,          0,               0,               0,             0,             0,          0,          0,             0,        NULL,             0);
//SUNXI_CLK_PERIPH_CONFIG(cpurcir,        CLK_CPUS_CIR_CFG,    24,      1,        CLK_CPUS_CIR_CFG,       0,         5,          8,          2,          0,          CLK_CPUS_CIR_CFG,    CLK_CPUS_CIR_GATE,   CLK_CPUS_CIR_GATE, 0,             31,         16,         0,             0,        NULL,             0);
//SUNXI_CLK_PERIPH_CONFIG(spwm,           CLK_CPUS_PWM_CFG,    24,      2,            0,                  0,         0,          0,          0,          0,          CLK_CPUS_PWM_GATE,   CLK_CPUS_PWM_GATE,   CLK_CPUS_PWM_GATE, 0,             31,        16,         0,             0,         NULL,             0);

SUNXI_CLK_PERIPH(cpu,       HAL_CLK_BUS_C0_CPU,     cpu_parents);
SUNXI_CLK_PERIPH(axi,       HAL_CLK_BUS_C0_AXI,     axi_parents);
//SUNXI_CLK_PERIPH(cpuapb,  HAL_CLK_BUS_CPUAPB,     cpuapb_parents);
SUNXI_CLK_PERIPH(psi,       HAL_CLK_BUS_PSI,        psi_parents);
SUNXI_CLK_PERIPH(ahb1,      HAL_CLK_BUS_AHB1,      ahb1_parents);
SUNXI_CLK_PERIPH(ahb2,      HAL_CLK_BUS_AHB2,      ahb2_parents);
SUNXI_CLK_PERIPH(ahb3,      HAL_CLK_BUS_AHB3,       ahb3_parents);
SUNXI_CLK_PERIPH(apb1,      HAL_CLK_BUS_APB1,       apb1_parents);
SUNXI_CLK_PERIPH(apb2,      HAL_CLK_BUS_APB2,       apb2_parents);
SUNXI_CLK_PERIPH(mbus,      HAL_CLK_BUS_MBUS,       mbus_parents);
SUNXI_CLK_PERIPH(de,        HAL_CLK_PERIPH_DE,      de_parents);
SUNXI_CLK_PERIPH(g2d,       HAL_CLK_PERIPH_G2D,     de_parents);
SUNXI_CLK_PERIPH(ce,        HAL_CLK_PERIPH_CE,      ce_parents);
SUNXI_CLK_PERIPH(ve,        HAL_CLK_PERIPH_VE,      ve_parents);
SUNXI_CLK_PERIPH(eise,      HAL_CLK_PERIPH_EISE,    ve_parents);
SUNXI_CLK_PERIPH(nna,       HAL_CLK_PERIPH_NNA,     nna_parents);
SUNXI_CLK_PERIPH(nna_rst,   HAL_CLK_PERIPH_NNA_RST,     nna_parents);
SUNXI_CLK_PERIPH(dma,       HAL_CLK_PERIPH_DMA,     ahb1mod_parents);
SUNXI_CLK_PERIPH(hstimer,   HAL_CLK_PERIPH_HSTIMER, ahb1mod_parents);
SUNXI_CLK_PERIPH(avs,       HAL_CLK_PERIPH_AVS,     hosc_parents);
SUNXI_CLK_PERIPH(dbgsys,    HAL_CLK_PERIPH_DBGSYS,  ahb1mod_parents);
SUNXI_CLK_PERIPH(pwm,       HAL_CLK_PERIPH_PWM,     apb1mod_parents);
SUNXI_CLK_PERIPH(iommu,     HAL_CLK_PERIPH_IOMMU,   ahb1mod_parents);
SUNXI_CLK_PERIPH(sdram,     HAL_CLK_PERIPH_DRAM,   sdram_parents);
SUNXI_CLK_PERIPH(sdmmc0_mod,        HAL_CLK_PERIPH_SDMMC0_MOD,  smhc_parents);
SUNXI_CLK_PERIPH(sdmmc0_rst,    HAL_CLK_PERIPH_SDMMC0_RST,  smhc_parents);
SUNXI_CLK_PERIPH(sdmmc0_bus,    HAL_CLK_PERIPH_SDMMC0_BUS,  smhc_parents);
SUNXI_CLK_PERIPH(sdmmc1_mod,        HAL_CLK_PERIPH_SDMMC1_MOD,  smhc_parents);
SUNXI_CLK_PERIPH(sdmmc1_rst,    HAL_CLK_PERIPH_SDMMC1_RST,  smhc_parents);
SUNXI_CLK_PERIPH(sdmmc1_bus,    HAL_CLK_PERIPH_SDMMC1_BUS,  smhc_parents);
SUNXI_CLK_PERIPH(sdmmc2_mod,        HAL_CLK_PERIPH_SDMMC2_MOD,  smhc_parents);
SUNXI_CLK_PERIPH(sdmmc2_rst,    HAL_CLK_PERIPH_SDMMC2_RST,  smhc_parents);
SUNXI_CLK_PERIPH(sdmmc2_bus,    HAL_CLK_PERIPH_SDMMC2_BUS,  smhc_parents);
SUNXI_CLK_PERIPH(uart0,     HAL_CLK_PERIPH_UART0,   apb2mod_parents);
SUNXI_CLK_PERIPH(uart1,     HAL_CLK_PERIPH_UART1,   apb2mod_parents);
SUNXI_CLK_PERIPH(uart2,     HAL_CLK_PERIPH_UART2,   apb2mod_parents);
SUNXI_CLK_PERIPH(uart3,     HAL_CLK_PERIPH_UART3,    apb2mod_parents);
SUNXI_CLK_PERIPH(twi0,      HAL_CLK_PERIPH_TWI0,    apb2mod_parents);
SUNXI_CLK_PERIPH(twi1,      HAL_CLK_PERIPH_TWI1,    apb2mod_parents);
SUNXI_CLK_PERIPH(twi2,      HAL_CLK_PERIPH_TWI2,    apb2mod_parents);
SUNXI_CLK_PERIPH(twi3,      HAL_CLK_PERIPH_TWI3,    apb2mod_parents);
SUNXI_CLK_PERIPH(spi0,      HAL_CLK_PERIPH_SPI0,    spi_parents);
SUNXI_CLK_PERIPH(spi1,      HAL_CLK_PERIPH_SPI1,    spi_parents);
SUNXI_CLK_PERIPH(spi2,      HAL_CLK_PERIPH_SPI2,    spi_parents);
SUNXI_CLK_PERIPH(ephy_25m,  HAL_CLK_PERIPH_EPHY,    ephy_25m_parents);
SUNXI_CLK_PERIPH(gmac,      HAL_CLK_PERIPH_GMAC,     ahb3mod_parents);
SUNXI_CLK_PERIPH(ths,       HAL_CLK_PERIPH_THS,     hosc_parents);
SUNXI_CLK_PERIPH(gpadc,     HAL_CLK_PERIPH_GPADC,   hosc_parents);
SUNXI_CLK_PERIPH(i2s0,      HAL_CLK_PERIPH_I2S0,    audio_parents);
SUNXI_CLK_PERIPH(i2s1,      HAL_CLK_PERIPH_I2S1,    audio_parents);
SUNXI_CLK_PERIPH(codec_1x,  HAL_CLK_PERIPH_AUDIOCODEC_1X, audio_parents);
SUNXI_CLK_PERIPH(codec_4x,  HAL_CLK_PERIPH_AUDIOCODEC_4X, audio_parents);
SUNXI_CLK_PERIPH(usbphy0,   HAL_CLK_PERIPH_USB0,    hosc_parents);
SUNXI_CLK_PERIPH(usbohci0,  HAL_CLK_PERIPH_USBOHCI0,   ahb3mod_parents);
SUNXI_CLK_PERIPH(usbohci0_12m,    HAL_CLK_PERIPH_USBOHCI0_12M,  usbohci_12m_parents);
SUNXI_CLK_PERIPH(usbehci0,  HAL_CLK_PERIPH_USBEHCI0, ahb3mod_parents);
SUNXI_CLK_PERIPH(usbotg,    HAL_CLK_PERIPH_USBOTG,   ahb3mod_parents);
SUNXI_CLK_PERIPH(pio,       HAL_CLK_PERIPH_PIO,      apb1mod_parents);
SUNXI_CLK_PERIPH(mipi_dphy0,       HAL_CLK_PERIPH_MIPI_DPHY0,      mipi_dphy0_parents);
SUNXI_CLK_PERIPH(mipi_host0,       HAL_CLK_PERIPH_MIPI_HOST0,      mipi_host0_parents);
SUNXI_CLK_PERIPH(display_top,       HAL_CLK_PERIPH_DISPLAY_TOP,      ahb3mod_parents);
SUNXI_CLK_PERIPH(tcon_lcd,       HAL_CLK_PERIPH_TCON_LCD0,      mipi_dphy0_parents);
SUNXI_CLK_PERIPH(csi_top,       HAL_CLK_PERIPH_CSI_TOP,      csi_top_parents);
SUNXI_CLK_PERIPH(csi_master0,       HAL_CLK_PERIPH_CSI_MASTER0,      csi_master_parents);
SUNXI_CLK_PERIPH(csi_master1,       HAL_CLK_PERIPH_CSI_MASTER1,      csi_master_parents);
SUNXI_CLK_PERIPH(isp,       HAL_CLK_PERIPH_ISP,      isp_parents);
SUNXI_CLK_PERIPH(dspo,       HAL_CLK_PERIPH_DSPO,      dspo_parents);


SUNXI_PERIPH_INIT(cpu, HAL_CLK_BUS_C0_CPU, HAL_CLK_PLL_CPUX_C0, 1200000000U);
SUNXI_PERIPH_INIT(axi, HAL_CLK_BUS_C0_AXI, HAL_CLK_BUS_C0_CPU, 400000000U);
SUNXI_PERIPH_INIT(apb1, HAL_CLK_BUS_APB1, HAL_CLK_PLL_PERI0, 100000000U);
SUNXI_PERIPH_INIT(apb2, HAL_CLK_BUS_APB2,  HAL_CLK_SRC_HOSC24M, 24000000U);
SUNXI_PERIPH_INIT(psi, HAL_CLK_BUS_PSI, HAL_CLK_PLL_PERI0, 200000000U);
SUNXI_PERIPH_INIT(ahb1, HAL_CLK_BUS_AHB1, HAL_CLK_BUS_PSI, 200000000U);
SUNXI_PERIPH_INIT(ahb2, HAL_CLK_BUS_AHB2, HAL_CLK_BUS_PSI, 200000000U);
SUNXI_PERIPH_INIT(ahb3, HAL_CLK_BUS_AHB3, HAL_CLK_PLL_PERI0, 200000000U);

static int get_factors_pll_cpu(u32 rate, u32 parent_rate,
                               struct clk_factors_value *factor)
{
    int index;
    u64 tmp_rate;

    if (!factor)
    {
        return -1;
    }
    tmp_rate = rate > SUNXI_CLK_FACTOR_CPU_MAX_FREQ ? SUNXI_CLK_FACTOR_CPU_MAX_FREQ : rate;
    do_div(tmp_rate, 1000000);
    index = tmp_rate;

    if (FACTOR_SEARCH(cpu))
    {
        return -1;
    }

    return 0;
}

static int get_factors_pll_ddr(u32 rate, u32 parent_rate,
                               struct clk_factors_value *factor)
{
    int index;
    u64 tmp_rate;

    if (!factor)
    {
        return -1;
    }

    tmp_rate = rate > SUNXI_CLK_FACTOR_DDR_MAX_FREQ ? SUNXI_CLK_FACTOR_DDR_MAX_FREQ : rate;
    do_div(tmp_rate, 1000000);
    index = tmp_rate;

    if (FACTOR_SEARCH(ddr))
    {
        return -1;
    }

    return 0;
}

static int get_factors_pll_periph0(u32 rate, u32 parent_rate,
                                   struct clk_factors_value *factor)
{
    int index;
    u64 tmp_rate;

    if (!factor)
    {
        return -1;
    }

    tmp_rate = rate > SUNXI_CLK_FACTOR_PERI0_MAX_FREQ ? SUNXI_CLK_FACTOR_PERI0_MAX_FREQ : rate;
    do_div(tmp_rate, 1000000);
    index = tmp_rate;

    if (FACTOR_SEARCH(periph0))
    {
        return -1;
    }

    return 0;
}

static int get_factors_pll_periph1(u32 rate, u32 parent_rate,
                                   struct clk_factors_value *factor)
{
    int index;
    u64 tmp_rate;

    if (!factor)
    {
        return -1;
    }

    tmp_rate = rate > SUNXI_CLK_FACTOR_PERI1_MAX_FREQ ? SUNXI_CLK_FACTOR_PERI1_MAX_FREQ : rate;
    do_div(tmp_rate, 1000000);
    index = tmp_rate;

    if (FACTOR_SEARCH(periph1))
    {
        return -1;
    }

    return 0;
}

static int get_factors_pll_video(u32 rate, u32 parent_rate,
                                 struct clk_factors_value *factor)
{
    int index;
    u64 tmp_rate;

    if (!factor)
    {
        return -1;
    }
    tmp_rate = rate > SUNXI_CLK_FACTOR_VIDEO_MAX_FREQ ? SUNXI_CLK_FACTOR_VIDEO_MAX_FREQ : rate;
    do_div(tmp_rate, 1000000);
    index = tmp_rate;

    if (FACTOR_SEARCH(video))
    {
        return -1;
    }

    return 0;
}

static int calc_rate_pll_video(u32 parent_rate,
                               struct clk_factors_value *factor)
{
    u64 tmp_rate = (parent_rate ? parent_rate : 24000000);
    tmp_rate = tmp_rate * (factor->factorn + 1);
    do_div(tmp_rate, 4 * (factor->factord1 + 1));
    return (u32)tmp_rate;
}

static int get_factors_pll_csi(u32 rate, u32 parent_rate,
                               struct clk_factors_value *factor)
{
    int index;
    u64 tmp_rate;

    if (!factor)
    {
        return -1;
    }

    tmp_rate = rate > SUNXI_CLK_FACTOR_DDR_MAX_FREQ ? SUNXI_CLK_FACTOR_DDR_MAX_FREQ : rate;
    do_div(tmp_rate, 1000000);
    index = tmp_rate;

    if (FACTOR_SEARCH(ddr))
    {
        return -1;
    }

    return 0;
}

static int calc_rate_pll_csi(u32 parent_rate,
                             struct clk_factors_value *factor)
{
    u64 tmp_rate = (parent_rate ? parent_rate : 24000000);
    tmp_rate = tmp_rate * (factor->factorn + 1);
    do_div(tmp_rate, (factor->factord1 + 1) * (factor->factord2 + 1));
    return (u32)tmp_rate;
}

/*    pll_cpux: 24*N/P (P=2^factorp)  */
static int calc_rate_pll_cpu(u32 parent_rate,
                             struct clk_factors_value *factor)
{
    u64 tmp_rate = (parent_rate ? parent_rate : 24000000);
    tmp_rate = tmp_rate * (factor->factorn + 1);
    do_div(tmp_rate, (1 << factor->factorp));
    return (u32)tmp_rate;
}

/*    pll_ddr: 24*N/D1/D2    */
static int calc_rate_pll_ddr(u32 parent_rate,
                             struct clk_factors_value *factor)
{
    u64 tmp_rate = (parent_rate ? parent_rate : 24000000);
    tmp_rate = tmp_rate * (factor->factorn + 1);
    do_div(tmp_rate, (factor->factord1 + 1) * (factor->factord2 + 1));
    return (u32)tmp_rate;
}

/*    pll_periph0/pll_periph1: 24*N/D1/D2/2    */
static int calc_rate_pll_periph0(u32 parent_rate,
                                 struct clk_factors_value *factor)
{
    u64 tmp_rate = (parent_rate ? parent_rate : 24000000);
    tmp_rate = tmp_rate * (factor->factorn + 1);
    do_div(tmp_rate, 2 * (factor->factord1 + 1) * (factor->factord2 + 1));
    return (u32)tmp_rate;
}

static int calc_rate_pll_periph1(u32 parent_rate,
                                 struct clk_factors_value *factor)
{
    u64 tmp_rate = (parent_rate ? parent_rate : 24000000);
    tmp_rate = tmp_rate * (factor->factorn + 1);
    do_div(tmp_rate, 2 * (factor->factord1 + 1) * (factor->factord2 + 1));
    return (u32)tmp_rate;
}

/*
 *    pll_audio: 24*N/D1/D2/P
 *
 *    NOTE: pll_audiox4 = 24*N/D1/2
 *          pll_audiox2 = 24*N/D1/4
 *
 *    pll_audiox4=2*pll_audiox2=4*pll_audio only when D2*P=8
 */
static int calc_rate_pll_audio(u32 parent_rate,
                               struct clk_factors_value *factor)
{
    u64 tmp_rate = (parent_rate ? parent_rate : 24000000);
    if ((factor->factorn == 21) &&
        (factor->factorp == 11) &&
        (factor->factord1 == 0) &&
        (factor->factord2 == 1))
    {
        return 22579200;
    }
    else if ((factor->factorn == 23) &&
             (factor->factorp == 11) &&
             (factor->factord1 == 0) &&
             (factor->factord2 == 1))
    {
        return 24576000;
    }
    else
    {
        tmp_rate = tmp_rate * (factor->factorn + 1);
        do_div(tmp_rate, ((factor->factorp + 1) *
                          (factor->factord1 + 1) *
                          (factor->factord2 + 1)));
        return (u32)tmp_rate;
    }
}

static int get_factors_pll_audio(u32 rate, u32 parent_rate,
                                 struct clk_factors_value *factor)
{
    if (rate == 22579200)
    {
        factor->factorn = 21;
        factor->factorp = 11;
        factor->factord1 = 0;
        factor->factord2 = 1;
        sunxi_clk_factor_config_pll_audio.sdmval = 0xC001288D;
    }
    else if (rate == 24576000)
    {
        factor->factorn = 23;
        factor->factorp = 11;
        factor->factord1 = 0;
        factor->factord2 = 1;
        sunxi_clk_factor_config_pll_audio.sdmval = 0xC00126E9;
    }
    else
    {
        return -1;
    }

    return 0;
}


/*************************************************************************
 * SUNXI Factor Pll Clock Initialize API definition
 * 初始化
 *************************************************************************/

hal_clk_status_t sunxi_factor_pll_cpu_init(void)
{
    u32 i = 0, current_rate = 0, parent_rate = 0;
    hal_clk_status_t ret = HAL_CLK_STATUS_OK;
    clk_factor_pt factor = NULL;
    clk_periph_pt periph = NULL;

    CCMU_TRACE();
    factor = (clk_factor_pt)clk_get_core(HAL_CLK_PLL_CPUX_C0);
    periph = (clk_periph_pt)clk_get_core(HAL_CLK_BUS_C0_AXI);
    if ((factor == NULL) || (periph == NULL))
    {
        return HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
    }
    ret = sunxi_clk_factors_recalc_rate(factor, &current_rate);
    if (ret != HAL_CLK_STATUS_OK)
    {
        return ret;
    }
    CCMU_DBG("clk %d current rate %d \n", factor->clk_core.clk, current_rate);
    if (factor->clk_core.clk_rate == current_rate)
    {
        return HAL_CLK_STATUS_OK;
    }
    //set AXI clock aprent to OSC23M before PLL_CPUX change rate
    ret = sunxi_clk_periph_set_parent(periph, 0);
    ret = sunxi_clk_factors_set_rate(factor, factor->clk_core.clk_rate);
    if (ret != HAL_CLK_STATUS_OK)
    {
        return ret;
    }
    ret = sunxi_clk_factors_recalc_rate(factor, &current_rate);
    if (ret != HAL_CLK_STATUS_OK)
    {
        return ret;
    }
    CCMU_DBG("clk %d recalc current rate %d \n", factor->clk_core.clk, current_rate);
    if (factor->clk_core.clk_rate != current_rate)
    {
        return HAL_CLK_STATUS_ERROR;
    }
    //set AXI clock aprent to PLL_CPUX after PLL_CPUX change rate
    ret = sunxi_clk_periph_set_parent(periph, 0x03);
    CCMU_DBG("clk init sucess! \n");
    return ret;
}


hal_clk_status_t sunxi_factor_pll_periph1_init(void)
{
    hal_clk_status_t ret = HAL_CLK_STATUS_OK;
    clk_factor_pt factor = NULL;

    CCMU_TRACE();
    factor = (clk_factor_pt)clk_get_core(HAL_CLK_PLL_PERI1);
    if (factor == NULL)
    {
        return HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
    }

    ret = sunxi_clk_fators_enable(factor);
    if (ret == HAL_CLK_STATUS_ENABLED)
    {
        factor->clk_core.clk_enbale = HAL_CLK_STATUS_ENABLED;
    }
    return HAL_CLK_STATUS_OK;
}

hal_clk_status_t sunxi_factor_pll_periph0_init(void)
{
    hal_clk_status_t ret = HAL_CLK_STATUS_OK;
    clk_factor_pt factor = NULL;

    CCMU_TRACE();
    factor = (clk_factor_pt)clk_get_core(HAL_CLK_PLL_PERI0);
    if (factor == NULL)
    {
        return HAL_CLK_STATUS_ERROT_CLK_UNDEFINED;
    }

    ret = sunxi_clk_fators_enable(factor);
    if (ret == HAL_CLK_STATUS_ENABLED)
    {
        factor->clk_core.clk_enbale = HAL_CLK_STATUS_ENABLED;
    }
    return HAL_CLK_STATUS_OK;
}

clk_core_pt sunxi_clk_fixed_src_arry[] =
{
    &sunxi_clk_fixed_src_losc,
    &sunxi_clk_fixed_src_iosc,
    &sunxi_clk_fixed_src_hosc,
    &sunxi_clk_fixed_src_osc48m,
    &sunxi_clk_fixed_src_hoscd2,
    &sunxi_clk_fixed_src_osc48md4,
    &sunxi_clk_fixed_src_pll_periph0div25m,
    NULL,
};

clk_factor_pt sunxi_clk_factor_arry[] =
{
    &sunxi_clk_factor_pll_cpu,
    &sunxi_clk_factor_pll_ddr,
    &sunxi_clk_factor_pll_periph0,
    &sunxi_clk_factor_pll_periph1,
    &sunxi_clk_factor_pll_audio,
    &sunxi_clk_factor_pll_video,
    &sunxi_clk_factor_pll_csi,
    NULL,
};

clk_fixed_factor_pt sunxi_clk_fixed_factor_arry[] =
{
    &sunxi_clk_fixed_factor_pll_periph0x2,
    &sunxi_clk_fixed_factor_pll_periph1x2,
    &sunxi_clk_fixed_factor_pll_audiox4,
    &sunxi_clk_fixed_factor_pll_videox4,
    &sunxi_clk_fixed_factor_pll_ddrdiv4,
    NULL,
};

clk_periph_pt sunxi_clk_periph_arry[] =
{
    &sunxi_clk_periph_cpu,
    &sunxi_clk_periph_axi,
    //  &sunxi_clk_periph_cpuapb,
    &sunxi_clk_periph_psi,
    &sunxi_clk_periph_ahb1,
    &sunxi_clk_periph_ahb2,
    &sunxi_clk_periph_ahb3,
    &sunxi_clk_periph_apb1,
    &sunxi_clk_periph_apb2,
    &sunxi_clk_periph_de,
    &sunxi_clk_periph_g2d,
    &sunxi_clk_periph_ce,
    &sunxi_clk_periph_ve,
    &sunxi_clk_periph_eise,
    &sunxi_clk_periph_nna,
    &sunxi_clk_periph_nna_rst,
    &sunxi_clk_periph_dma,
    &sunxi_clk_periph_hstimer,
    &sunxi_clk_periph_avs,
    &sunxi_clk_periph_dbgsys,
    &sunxi_clk_periph_pwm,
    &sunxi_clk_periph_sdram,
    &sunxi_clk_periph_sdmmc0_mod,
    &sunxi_clk_periph_sdmmc0_rst,
    &sunxi_clk_periph_sdmmc0_bus,
    &sunxi_clk_periph_sdmmc1_mod,
    &sunxi_clk_periph_sdmmc1_rst,
    &sunxi_clk_periph_sdmmc1_bus,
    &sunxi_clk_periph_sdmmc2_mod,
    &sunxi_clk_periph_sdmmc2_rst,
    &sunxi_clk_periph_sdmmc2_bus,
    &sunxi_clk_periph_uart0,
    &sunxi_clk_periph_uart1,
    &sunxi_clk_periph_uart2,
    &sunxi_clk_periph_uart3,
    &sunxi_clk_periph_twi0,
    &sunxi_clk_periph_twi1,
    &sunxi_clk_periph_twi2,
    &sunxi_clk_periph_twi3,
    &sunxi_clk_periph_spi0,
    &sunxi_clk_periph_spi1,
    &sunxi_clk_periph_spi2,
    &sunxi_clk_periph_ephy_25m,
    &sunxi_clk_periph_gmac,
    &sunxi_clk_periph_ths,
    &sunxi_clk_periph_gpadc,
    &sunxi_clk_periph_i2s0,
    &sunxi_clk_periph_i2s1,
    &sunxi_clk_periph_codec_1x,
    &sunxi_clk_periph_codec_4x,
    &sunxi_clk_periph_usbphy0,
    &sunxi_clk_periph_usbohci0,
    &sunxi_clk_periph_usbohci0_12m,
    &sunxi_clk_periph_usbehci0,
    &sunxi_clk_periph_usbotg,
    &sunxi_clk_periph_mipi_dphy0,
    &sunxi_clk_periph_mipi_host0,
    &sunxi_clk_periph_display_top,
    &sunxi_clk_periph_tcon_lcd,
    &sunxi_clk_periph_csi_top,
    &sunxi_clk_periph_csi_master0,
    &sunxi_clk_periph_csi_master1,
    &sunxi_clk_periph_isp,
    &sunxi_clk_periph_dspo,
    &sunxi_clk_periph_pio,
    NULL,
};

clk_base_pt sunxi_periph_clk_init_arry[] =
{
    &sunxi_periph_clk_init_cpu,
    &sunxi_periph_clk_init_axi,
    &sunxi_periph_clk_init_apb1,
    &sunxi_periph_clk_init_apb2,
    &sunxi_periph_clk_init_psi,
    &sunxi_periph_clk_init_ahb1,
    &sunxi_periph_clk_init_ahb2,
    &sunxi_periph_clk_init_ahb3,
    NULL,
};

hal_clk_status_t (*sunxi_clk_factor_init[])(void) =
{
    &sunxi_factor_pll_cpu_init,
    &sunxi_factor_pll_periph0_init,
    &sunxi_factor_pll_periph1_init,
    NULL,
};

