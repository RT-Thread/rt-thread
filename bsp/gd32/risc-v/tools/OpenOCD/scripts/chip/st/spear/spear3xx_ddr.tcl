# Init scripts to configure DDR controller of SPEAr3xx
# http://www.st.com/spear
# Original values taken from XLoader source code
#
# Date:      2010-09-23
# Author:    Antonio Borneo <borneo.antonio@gmail.com>


proc sp3xx_ddr_init {ddr_type {ddr_chips 1}} {
	if { $ddr_chips != 1 && $ddr_chips != 2 } {
		error "Only 1 or 2 DDR chips permitted. Wrong value "$ddr_chips
	}

	if { $ddr_type == "mt47h64m16_3_333_cl5_async" } {
		ddr_spr3xx_mt47h64m16_3_333_cl5_async $ddr_chips
		set ddr_size 0x08000000
	## add here new DDR chip definition. Prototype:
	#} elseif { $ddr_type == "?????" } {
	#	????? $ddr_chips
	#	set ddr_size 0x?????
	} else {
		error "sp3xx_ddr_init: unrecognized DDR type "$ddr_type
	}

	# MPMC START
	mww 0xfc60001c 0x01000100

	if { $ddr_chips == 2 } {
		echo [format \
			"Double chip DDR memory. Total memory size 0x%08x byte" \
			[expr 2 * $ddr_size]]
	} else {
		echo [format \
			"Single chip DDR memory. Memory size 0x%08x byte" \
			$ddr_size]
	}
}


# from Xloader file ddr/spr300_mt47h64m16_3_333_cl5_async.S
proc ddr_spr3xx_mt47h64m16_3_333_cl5_async {ddr_chips} {
	# DDR_PAD_REG
	mww 0xfca800f0 0x00003aa5

	# Use "1:2 sync" only when DDR clock source is PLL1 and
	# HCLK is half of PLL1
	mww 0xfc600000 0x00000001	;# MEMCTL_AHB_SET_00 # This is async
	mww 0xfc600004 0x00000000	;# MEMCTL_AHB_SET_01
#	mww 0xfc600000 0x02020201	;# MEMCTL_AHB_SET_00 # This is 1:2 sync
#	mww 0xfc600004 0x02020202	;# MEMCTL_AHB_SET_01

	mww 0xfc600008 0x01000000	;# MEMCTL_RFSH_SET_00
	mww 0xfc60000c 0x00000101	;# MEMCTL_DLL_SET_00
	mww 0xfc600010 0x00000101	;# MEMCTL_GP_00
	mww 0xfc600014 0x01000000	;# MEMCTL_GP_01
	mww 0xfc600018 0x00010001	;# MEMCTL_GP_02
	mww 0xfc60001c 0x00000100	;# MEMCTL_GP_03
	mww 0xfc600020 0x00010001	;# MEMCTL_GP_04
	if { $ddr_chips == 2 } {
		mww 0xfc600024 0x01020203	;# MEMCTL_GP_05
		mww 0xfc600028 0x01000102	;# MEMCTL_GP_06
		mww 0xfc60002c 0x02000202	;# MEMCTL_AHB_SET_02
	} else {
		mww 0xfc600024 0x00000201	;# MEMCTL_GP_05
		mww 0xfc600028 0x02000001	;# MEMCTL_GP_06
		mww 0xfc60002c 0x02000201	;# MEMCTL_AHB_SET_02
	}
	mww 0xfc600030 0x04040105	;# MEMCTL_AHB_SET_03
	mww 0xfc600034 0x03030302	;# MEMCTL_AHB_SET_04
	mww 0xfc600038 0x02040101	;# MEMCTL_AHB_SET_05
	mww 0xfc60003c 0x00000002	;# MEMCTL_AHB_SET_06
	mww 0xfc600044 0x03000405	;# MEMCTL_DQS_SET_0
	mww 0xfc600048 0x03040002	;# MEMCTL_TIME_SET_01
	mww 0xfc60004c 0x04000305	;# MEMCTL_TIME_SET_02
	mww 0xfc600050 0x0505053f	;# MEMCTL_AHB_RELPR_00
	mww 0xfc600054 0x05050505	;# MEMCTL_AHB_RELPR_01
	mww 0xfc600058 0x04040405	;# MEMCTL_AHB_RELPR_02
	mww 0xfc60005c 0x04040404	;# MEMCTL_AHB_RELPR_03
	mww 0xfc600060 0x03030304	;# MEMCTL_AHB_RELPR_04
	mww 0xfc600064 0x03030303	;# MEMCTL_AHB_RELPR_05
	mww 0xfc600068 0x02020203	;# MEMCTL_AHB_RELPR_06
	mww 0xfc60006c 0x02020202	;# MEMCTL_AHB_RELPR_07
	mww 0xfc600070 0x01010102	;# MEMCTL_AHB_RELPR_08
	mww 0xfc600074 0x01010101	;# MEMCTL_AHB_RELPR_09
	mww 0xfc600078 0x00000001	;# MEMCTL_AHB_RELPR_10
	mww 0xfc600088 0x0a0c0a00	;# MEMCTL_DQS_SET_1
	mww 0xfc60008c 0x0000023f	;# MEMCTL_GP_07
	mww 0xfc600090 0x00050a00	;# MEMCTL_GP_08
	mww 0xfc600094 0x11000000	;# MEMCTL_GP_09
	mww 0xfc600098 0x00001302	;# MEMCTL_GP_10
	mww 0xfc60009c 0x00001c1c	;# MEMCTL_DLL_SET_01
	mww 0xfc6000a0 0x7c000000	;# MEMCTL_DQS_OUT_SHIFT
	mww 0xfc6000a4 0x005c0000	;# MEMCTL_WR_DQS_SHIFT
	mww 0xfc6000a8 0x2b050e00	;# MEMCTL_TIME_SET_03
	mww 0xfc6000ac 0x00640064	;# MEMCTL_AHB_PRRLX_00
	mww 0xfc6000b0 0x00640064	;# MEMCTL_AHB_PRRLX_01
	mww 0xfc6000b4 0x00000064	;# MEMCTL_AHB_PRRLX_02
	mww 0xfc6000b8 0x00000000	;# MEMCTL_OUTRANGE_LGTH
	mww 0xfc6000bc 0x00200020	;# MEMCTL_AHB_RW_SET_00
	mww 0xfc6000c0 0x00200020	;# MEMCTL_AHB_RW_SET_01
	mww 0xfc6000c4 0x00200020	;# MEMCTL_AHB_RW_SET_02
	mww 0xfc6000c8 0x00200020	;# MEMCTL_AHB_RW_SET_03
	mww 0xfc6000cc 0x00200020	;# MEMCTL_AHB_RW_SET_04
	mww 0xfc6000d8 0x00000a24	;# MEMCTL_TREF
	mww 0xfc6000dc 0x00000000	;# MEMCTL_EMRS3_DATA
	mww 0xfc6000e0 0x5b1c00c8	;# MEMCTL_TIME_SET_04
	mww 0xfc6000e4 0x00c8002e	;# MEMCTL_TIME_SET_05
	mww 0xfc6000e8 0x00000000	;# MEMCTL_VERSION
	mww 0xfc6000ec 0x0001046b	;# MEMCTL_TINIT
	mww 0xfc6000f0 0x00000000	;# MEMCTL_OUTRANGE_ADDR_01
	mww 0xfc6000f4 0x00000000	;# MEMCTL_OUTRANGE_ADDR_02
	mww 0xfc600104 0x001c0000	;# MEMCTL_DLL_DQS_DELAY_BYPASS_0
	mww 0xfc600108 0x0019001c	;# MEMCTL_DLL_SET_02
	mww 0xfc60010c 0x00100000	;# MEMCTL_DLL_SET_03
	mww 0xfc600110 0x001e007a	;# MEMCTL_DQS_SET_2
	mww 0xfc600188 0x00000000	;# MEMCTL_USER_DEF_REG_0
	mww 0xfc60018c 0x00000000	;# MEMCTL_USER_DEF_REG_1
	mww 0xfc600190 0x01010001	;# MEMCTL_GP_11
	mww 0xfc600194 0x01000000	;# MEMCTL_GP_12
	mww 0xfc600198 0x00000001	;# MEMCTL_GP_13
	mww 0xfc60019c 0x00400000	;# MEMCTL_GP_14
	mww 0xfc6001a0 0x00000000	;# MEMCTL_EMRS2_DATA_X
	mww 0xfc6001a4 0x00000000	;# MEMCTL_LWPWR_CNT
	mww 0xfc6001a8 0x00000000	;# MEMCTL_LWPWR_REG
	mww 0xfc6001ac 0x00860000	;# MEMCTL_GP_15
	mww 0xfc6001b0 0x00000002	;# MEMCTL_TPDEX
}
