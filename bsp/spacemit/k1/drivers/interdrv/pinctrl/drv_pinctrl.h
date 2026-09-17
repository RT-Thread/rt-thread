/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-10-15     IronsideZhang     first version
 */

#ifndef __DRV_PINCTRL_H__
#define __DRV_PINCTRL_H__

#include <rtthread.h>

/*
 * ==========================================================================
 * This section is adapted from the Linux kernel device tree binding header:
 * dt-bindings/pinctrl/k1-x-pinctrl.h
 * ==========================================================================
 */

/* pin offset */
#define PINID(x)	((x) + 1)

#define GPIO_00  PINID(0)
#define GPIO_01  PINID(1)
#define GPIO_02  PINID(2)
#define GPIO_03  PINID(3)
#define GPIO_04  PINID(4)
#define GPIO_05  PINID(5)
#define GPIO_06  PINID(6)
#define GPIO_07  PINID(7)
#define GPIO_08  PINID(8)
#define GPIO_09  PINID(9)
#define GPIO_10  PINID(10)
#define GPIO_11  PINID(11)
#define GPIO_12  PINID(12)
#define GPIO_13  PINID(13)
#define GPIO_14  PINID(14)
#define GPIO_15  PINID(15)
#define GPIO_16  PINID(16)
#define GPIO_17  PINID(17)
#define GPIO_18  PINID(18)
#define GPIO_19  PINID(19)
#define GPIO_20  PINID(20)
#define GPIO_21  PINID(21)
#define GPIO_22  PINID(22)
#define GPIO_23  PINID(23)
#define GPIO_24  PINID(24)
#define GPIO_25  PINID(25)
#define GPIO_26  PINID(26)
#define GPIO_27  PINID(27)
#define GPIO_28  PINID(28)
#define GPIO_29  PINID(29)
#define GPIO_30  PINID(30)
#define GPIO_31  PINID(31)

#define GPIO_32  PINID(32)
#define GPIO_33  PINID(33)
#define GPIO_34  PINID(34)
#define GPIO_35  PINID(35)
#define GPIO_36  PINID(36)
#define GPIO_37  PINID(37)
#define GPIO_38  PINID(38)
#define GPIO_39  PINID(39)
#define GPIO_40  PINID(40)
#define GPIO_41  PINID(41)
#define GPIO_42  PINID(42)
#define GPIO_43  PINID(43)
#define GPIO_44  PINID(44)
#define GPIO_45  PINID(45)
#define GPIO_46  PINID(46)
#define GPIO_47  PINID(47)
#define GPIO_48  PINID(48)
#define GPIO_49  PINID(49)
#define GPIO_50  PINID(50)
#define GPIO_51  PINID(51)
#define GPIO_52  PINID(52)
#define GPIO_53  PINID(53)
#define GPIO_54  PINID(54)
#define GPIO_55  PINID(55)
#define GPIO_56  PINID(56)
#define GPIO_57  PINID(57)
#define GPIO_58  PINID(58)
#define GPIO_59  PINID(59)
#define GPIO_60  PINID(60)
#define GPIO_61  PINID(61)
#define GPIO_62  PINID(62)
#define GPIO_63  PINID(63)

#define GPIO_64  PINID(64)
#define GPIO_65  PINID(65)
#define GPIO_66  PINID(66)
#define GPIO_67  PINID(67)
#define GPIO_68  PINID(68)
#define GPIO_69  PINID(69)
#define PRI_TDI  PINID(70)
#define PRI_TMS  PINID(71)
#define PRI_TCK  PINID(72)
#define PRI_TDO  PINID(73)
#define GPIO_74  PINID(74)
#define GPIO_75  PINID(75)
#define GPIO_76  PINID(76)
#define GPIO_77  PINID(77)
#define GPIO_78  PINID(78)
#define GPIO_79  PINID(79)
#define GPIO_80  PINID(80)
#define GPIO_81  PINID(81)
#define GPIO_82  PINID(82)
#define GPIO_83  PINID(83)
#define GPIO_84  PINID(84)
#define GPIO_85  PINID(85)

#define QSPI_DAT0   PINID(89)
#define QSPI_DAT1   PINID(90)
#define QSPI_DAT2   PINID(91)
#define QSPI_DAT3   PINID(92)
#define QSPI_CSI    PINID(93)
#define QSPI_CLK    PINID(94)

#define MMC1_DAT3   PINID(109)
#define MMC1_DAT2   PINID(110)
#define MMC1_DAT1   PINID(111)
#define MMC1_DAT0   PINID(112)
#define MMC1_CMD    PINID(113)
#define MMC1_CLK    PINID(114)
#define GPIO_110    PINID(115)
#define PWR_SCL     PINID(116)
#define PWR_SDA     PINID(117)
#define VCXO_EN     PINID(118)
#define DVL0        PINID(119)
#define DVL1        PINID(120)
#define PMIC_INT_N  PINID(121)
#define GPIO_86     PINID(122)
#define GPIO_87     PINID(123)
#define GPIO_88     PINID(124)
#define GPIO_89     PINID(125)
#define GPIO_90     PINID(126)
#define GPIO_91     PINID(127)
#define GPIO_92     PINID(128)

#define GPIO_111    PINID(130)
#define GPIO_112    PINID(131)
#define GPIO_113    PINID(132)
#define GPIO_114    PINID(133)
#define GPIO_115    PINID(134)
#define GPIO_116    PINID(135)
#define GPIO_117    PINID(136)
#define GPIO_118    PINID(137)
#define GPIO_119    PINID(138)
#define GPIO_120    PINID(139)
#define GPIO_121    PINID(140)
#define GPIO_122    PINID(141)
#define GPIO_123    PINID(142)
#define GPIO_124    PINID(143)
#define GPIO_125    PINID(144)
#define GPIO_126    PINID(145)
#define GPIO_127    PINID(146)

#define EMMC_D0     PINID(147)
#define EMMC_D1     PINID(148)
#define EMMC_D2     PINID(149)
#define EMMC_D3     PINID(150)
#define EMMC_D4     PINID(151)
#define EMMC_D5     PINID(152)
#define EMMC_D6     PINID(153)
#define EMMC_D7     PINID(154)
#define EMMC_DS     PINID(155)
#define EMMC_CLK    PINID(156)
#define EMMC_CMD    PINID(157)

/* pin mux */
#define MUX_MODE0       0
#define MUX_MODE1       1
#define MUX_MODE2       2
#define MUX_MODE3       3
#define MUX_MODE4       4
#define MUX_MODE5       5
#define MUX_MODE6       6
#define MUX_MODE7       7

/* strong pull resistor */
#define SPU_EN          (1 << 3)

/* edge detect */
#define EDGE_NONE       (1 << 6)
#define EDGE_RISE       (1 << 4)
#define EDGE_FALL       (1 << 5)
#define EDGE_BOTH       (3 << 4)

/* slew rate output control */
#define SLE_EN          (1 << 7)

/* schmitter trigger input threshhold */
#define ST00            (0 << 8)
#define ST01            (1 << 8)
#define ST02            (2 << 8)
#define ST03            (3 << 8)

/* driver strength*/
#define PAD_1V8_DS0     (0 << 11)
#define PAD_1V8_DS1     (1 << 11)
#define PAD_1V8_DS2     (2 << 11)
#define PAD_1V8_DS3     (3 << 11)

/*
 * notice: !!!
 * ds2 ---> bit10, ds1 ----> bit12, ds0 ----> bit11
*/
#define PAD_3V_DS0      (0 << 10)     /* bit[12:10] 000 */
#define PAD_3V_DS1      (2 << 10)     /* bit[12:10] 010 */
#define PAD_3V_DS2      (4 << 10)     /* bit[12:10] 100 */
#define PAD_3V_DS3      (6 << 10)     /* bit[12:10] 110 */
#define PAD_3V_DS4      (1 << 10)     /* bit[12:10] 001 */
#define PAD_3V_DS5      (3 << 10)     /* bit[12:10] 011 */
#define PAD_3V_DS6      (5 << 10)     /* bit[12:10] 101 */
#define PAD_3V_DS7      (7 << 10)     /* bit[12:10] 111 */

/* pull up/down */
#define PULL_DIS        (0 << 13)     /* bit[15:13] 000 */
#define PULL_UP         (6 << 13)     /* bit[15:13] 110 */
#define PULL_DOWN       (5 << 13)     /* bit[15:13] 101 */

#define K1X_PADCONF(pinid, conf, mux)	((pinid) * 4) (conf) (mux)

/*
 * ==========================================================================
 * RT-Thread Driver API Declarations
 * ==========================================================================
 */

void k1_pinctrl_init(void);
void k1_pinctrl_set_function(rt_uint32_t pin_id, rt_uint32_t func_mode);
void k1_pinctrl_set_pull(rt_uint32_t pin_id, rt_uint32_t pull_state);

#endif /* __DRV_PINCTRL_H__ */