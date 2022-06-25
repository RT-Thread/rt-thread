#  Copyright (C) 2015, 2020 Synopsys, Inc.
#  Anton Kolesov <anton.kolesov@synopsys.com>
#  Didin Evgeniy <didin@synopsys.com>
#
# SPDX-License-Identifier: GPL-2.0-or-later

source [find cpu/arc/v2.tcl]

proc arc_em_examine_target { {target ""} } {
	# Will set current target
	arc_v2_examine_target $target
}

proc arc_em_init_regs { } {
	arc_v2_init_regs

	[target current] configure \
		-event examine-end "arc_em_examine_target [target current]"
}

# Scripts in "target" folder should call this function instead of direct
# invocation of arc_common_reset.
proc arc_em_reset { {target ""} } {
	arc_v2_reset $target

	# Set DEBUG.ED bit to enable clock in actionpoint module.
	# This is specific to ARC EM.
	set debug [arc jtag get-aux-reg 5]
	if { !($debug & (1 << 20)) } {
		arc jtag set-aux-reg 5 [expr $debug | (1 << 20)]
	}
}
