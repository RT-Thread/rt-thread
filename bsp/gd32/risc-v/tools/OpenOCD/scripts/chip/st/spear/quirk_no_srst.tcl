# Quirks to bypass missing SRST on JTAG connector
# EVALSPEAr310 Rev. 2.0
# http://www.st.com/spear
#
# Date:      2010-08-17
# Author:    Antonio Borneo <borneo.antonio@gmail.com>

# For boards that have JTAG SRST not connected.
# We use "arm9 vector_catch reset" to catch button reset event.


$_TARGETNAME configure -event reset-assert sp_reset_assert
$_TARGETNAME configure -event reset-deassert-post sp_reset_deassert_post

# keeps the name of the SPEAr target
global sp_target_name
set sp_target_name $_TARGETNAME

# Keeps the argument of "reset" command (run, init, halt).
global sp_reset_mode
set sp_reset_mode ""

# Helper procedure. Returns 0 is target is halted.
proc sp_is_halted {} {
	global sp_target_name

	return [expr [string compare [$sp_target_name curstate] "halted" ] == 0]
}

# wait for reset button to be pressed, causing CPU to get halted
proc sp_reset_deassert_post {} {
	global sp_reset_mode

	set bar(0) |
	set bar(1) /
	set bar(2) -
	set bar(3) \\

	poll on
	echo "====> Press reset button on the board <===="
	for {set i 0} { [sp_is_halted] == 0 } { set i [expr $i + 1]} {
		echo -n "$bar([expr $i & 3])\r"
		sleep 200
	}

	# Remove catch reset event
	arm9 vector_catch none

	# CPU is halted, but we typed "reset run" ...
	if { [string compare $sp_reset_mode "run"] == 0 } {
		resume
	}
}

# Override reset-assert, since no SRST available
# Catch reset event
proc sp_reset_assert {} {
	arm9 vector_catch reset
}

# Override default init_reset{mode} to catch parameter "mode"
proc init_reset {mode} {
	global sp_reset_mode

	set sp_reset_mode $mode

	# We need to detect CPU get halted, so exit from halt
	if { [sp_is_halted] } {
		echo "Resuming CPU to detect reset"
		resume
	}

	# Execute default init_reset{mode}
	jtag arp_init-reset
}
