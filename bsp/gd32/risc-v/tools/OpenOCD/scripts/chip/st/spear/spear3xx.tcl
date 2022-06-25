# Generic init scripts for all ST SPEAr3xx family
# http://www.st.com/spear
#
# Date:      2010-09-23
# Author:    Antonio Borneo <borneo.antonio@gmail.com>


# Initialize internal clock
# Default:
# - Crystal =  24 MHz
# - PLL1    = 332 MHz
# - PLL2    = 332 MHz
# - CPU_CLK = 332 MHz
# - DDR_CLK = 332 MHz async
# - HCLK    = 166 MHz
# - PCLK    =  83 MHz
proc sp3xx_clock_default {} {
	mww 0xfca00000 0x00000002	;# set sysclk slow
	mww 0xfca00014 0x0ffffff8	;# set pll timeout to minimum (100us ?!?)

	# DDRCORE disable to change frequency
	set val [expr ([mrw 0xfca8002c] & ~0x20000000) | 0x40000000]
	mww 0xfca8002c $val
	mww 0xfca8002c $val ;# Yes, write twice!

	# programming PLL1
	mww 0xfca8000c 0xa600010c	;# M=166 P=1 N=12
	mww 0xfca80008 0x00001c0a	;# power down
	mww 0xfca80008 0x00001c0e	;# enable
	mww 0xfca80008 0x00001c06	;# strobe
	mww 0xfca80008 0x00001c0e
	while { [expr [mrw 0xfca80008] & 0x01] == 0x00 } { sleep 1 }

	# programming PLL2
	mww 0xfca80018 0xa600010c	;# M=166, P=1, N=12
	mww 0xfca80014 0x00001c0a	;# power down
	mww 0xfca80014 0x00001c0e	;# enable
	mww 0xfca80014 0x00001c06	;# strobe
	mww 0xfca80014 0x00001c0e
	while { [expr [mrw 0xfca80014] & 0x01] == 0x00 } { sleep 1 }

	mww 0xfca80028 0x00000082	;# enable plltimeen
	mww 0xfca80024 0x00000511	;# set hclkdiv="/2" & pclkdiv="/2"

	mww 0xfca00000 0x00000004	;# setting SYSCTL to NORMAL mode
	while { [expr [mrw 0xfca00000] & 0x20] != 0x20 } { sleep 1 }

	# Select source of DDR clock
	#mmw 0xfca80020 0x10000000 0x70000000 ;# PLL1
	mmw 0xfca80020 0x30000000 0x70000000 ;# PLL2

	# DDRCORE enable after change frequency
	mmw 0xfca8002c 0x20000000 0x00000000
}

proc sp3xx_common_init {} {
	mww 0xfca8002c 0xfffffff8	;# enable clock of all peripherals
	mww 0xfca80038 0x00000000	;# remove reset of all peripherals

	mww 0xfca80034 0x0000ffff	;# enable all RAS clocks
	mww 0xfca80040 0x00000000	;# remove all RAS resets

	mww 0xfca800e4 0x78000008	;# COMP1V8_REG
	mww 0xfca800ec 0x78000008	;# COMP3V3_REG

	mww 0xfc000000 0x10000f5f	;# init SMI and set HW mode
	mww 0xfc000000 0x00000f5f

	# Initialize Bus Interconnection Matrix
	# All ports Round-Robin and lowest priority
	mww 0xfca8007c 0x80000007
	mww 0xfca80080 0x80000007
	mww 0xfca80084 0x80000007
	mww 0xfca80088 0x80000007
	mww 0xfca8008c 0x80000007
	mww 0xfca80090 0x80000007
	mww 0xfca80094 0x80000007
	mww 0xfca80098 0x80000007
	mww 0xfca8009c 0x80000007
}


# Specific init scripts for ST SPEAr300
proc sp300_init {} {
	mww 0x99000000 0x00003fff	;# RAS function enable
}


# Specific init scripts for ST SPEAr310
proc sp310_init {} {
	mww 0xb4000008 0x00002ff4	;# RAS function enable

	mww 0xfca80050 0x00000001	;# Enable clk mem port 1

	mww 0xfca8013c 0x2f7bc210	;# plgpio_pad_drv
	mww 0xfca80140 0x017bdef6
}

proc sp310_emi_init {} {
	# set EMI pad strength
	mmw 0xfca80134 0x0e000000 0x00000000
	mmw 0xfca80138 0x0e739ce7 0x00000000
	mmw 0xfca8013c 0x00039ce7 0x00000000

	# set safe EMI timing as in BootROM
	#mww 0x4f000000 0x0000000f	;# tAP_0_reg
	#mww 0x4f000004 0x00000000	;# tSDP_0_reg
	#mww 0x4f000008 0x000000ff	;# tDPw_0_reg
	#mww 0x4f00000c 0x00000111	;# tDPr_0_reg
	#mww 0x4f000010 0x00000002	;# tDCS_0_reg

	# set fast EMI timing as in Linux
	mww 0x4f000000 0x00000010	;# tAP_0_reg
	mww 0x4f000004 0x00000005	;# tSDP_0_reg
	mww 0x4f000008 0x0000000a	;# tDPw_0_reg
	mww 0x4f00000c 0x0000000a	;# tDPr_0_reg
	mww 0x4f000010 0x00000005	;# tDCS_0_re

	# 32bit wide, 8/16/32bit access
	mww 0x4f000014 0x0000000e	;# control_0_reg
	mww 0x4f000094 0x0000003f	;# ack_reg
}


# Specific init scripts for ST SPEAr320
proc sp320_init {} {
	mww 0xb300000c 0xffffac04	;# RAS function enable
	mww 0xb3000010 0x00000001	;# RAS mode select
}
