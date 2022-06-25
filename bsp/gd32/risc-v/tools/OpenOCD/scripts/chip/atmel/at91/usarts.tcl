# the DBGU and USARTs are 'almost' indentical'
set DBGU_CR         [expr $AT91C_BASE_DBGU + 0x00000000]
set DBGU_MR         [expr $AT91C_BASE_DBGU + 0x00000004]
set DBGU_IER        [expr $AT91C_BASE_DBGU + 0x00000008]
set DBGU_IDR        [expr $AT91C_BASE_DBGU + 0x0000000C]
set DBGU_IMR        [expr $AT91C_BASE_DBGU + 0x00000010]
set DBGU_CSR        [expr $AT91C_BASE_DBGU + 0x00000014]
set DBGU_RHR        [expr $AT91C_BASE_DBGU + 0x00000018]
set DBGU_THR        [expr $AT91C_BASE_DBGU + 0x0000001C]
set DBGU_BRGR       [expr $AT91C_BASE_DBGU + 0x00000020]
# no RTOR
# no TTGR
# no FIDI
# no NER
set DBGU_CIDR       [expr $AT91C_BASE_DBGU + 0x00000040]
set DBGU_EXID       [expr $AT91C_BASE_DBGU + 0x00000044]
set DBGU_FNTR       [expr $AT91C_BASE_DBGU + 0x00000048]


set USx_CR           0x00000000
set USx_MR           0x00000004
set USx_IER          0x00000008
set USx_IDR          0x0000000C
set USx_IMR          0x00000010
set USx_CSR          0x00000014
set USx_RHR          0x00000018
set USx_THR          0x0000001C
set USx_BRGR         0x00000020
set USx_RTOR         0x00000024
set USx_TTGR         0x00000028
set USx_FIDI         0x00000040
set USx_NER          0x00000044
set USx_IF           0x0000004C

# Create all the uarts that exist..
# we blow up if there are >9


proc show_mmr_USx_MR_helper { NAME ADDR VAL } {
    # First - just print it

    set x [show_normalize_bitfield $VAL 3 0]
    if { $x == 0 } {
	echo "\tNormal operation"
    } else {
	echo [format "\tNon Normal operation mode: 0x%02x" $x]
    }

    set x [show_normalize_bitfield $VAL 11 9]
    set s "unknown"
    switch -exact $x {
	0 { set s "Even" }
	1 { set s "Odd" }
	2 { set s "Force=0" }
	3 { set s "Force=1" }
	* {
	    set $x [expr $x & 6]
	    switch -exact $x {
		4 { set s "None" }
		6 { set s "Multidrop Mode" }
	    }
	}
    }
    echo [format "\tParity: %s " $s]

    set x [expr 5 + [show_normalize_bitfield $VAL 7 6]]
    echo [format "\tDatabits: %d" $x]

    set x [show_normalize_bitfield $VAL 13 12]
    switch -exact $x {
	0 { echo "\tStop bits: 1" }
	1 { echo "\tStop bits: 1.5" }
	2 { echo "\tStop bits: 2" }
	3 { echo "\tStop bits: Illegal/Reserved" }
    }
}

# For every possbile usart...
foreach WHO { US0 US1 US2 US3 US4 US5 US6 US7 US8 US9 } {
    set n AT91C_BASE_[set WHO]
    set str ""

    # Only if it exists on the chip
    if [ info exists $n ] {
	# Hence: $n - is like AT91C_BASE_USx
	# For every sub-register
	foreach REG {CR MR IER IDR IMR CSR RHR THR BRGR RTOR TTGR FIDI NER IF}	{
	    # vn = variable name
	    set vn [set WHO]_[set REG]
	    # vn = USx_IER
	    # vv = variable value
	    set vv [expr $$n + [set USx_[set REG]]]
	    # And VV is the address in memory of that register


	    # make that VN a GLOBAL so others can find it
	    global $vn
	    set $vn $vv

	    # Create a command for this specific register.
	    proc show_$vn { } "show_mmr32_reg $vn"

	    # Add this command to the Device(as a whole) command
	    set str "$str\nshow_$vn"
	}
	# Now - create the DEVICE(as a whole) command
	set fn show_$WHO
	proc $fn { } $str
    }
}

# The Debug Uart is special..
set str ""


# For every sub-register
foreach REG {DBGU_CR DBGU_MR DBGU_IER DBGU_IDR DBGU_IMR
    DBGU_CSR DBGU_RHR DBGU_THR DBGU_BRGR DBGU_CIDR DBGU_EXID DBGU_FNTR} {

    # Create a command for this specific register.
    proc show_$REG { } "show_mmr32_reg $REG"

    # Add this command to the Device(as a whole) command
    set str "$str\nshow_$REG"
}

# Now - create the DEVICE(as a whole) command
proc show_DBGU { } $str

unset str

proc show_DBGU_MR_helper { NAME ADDR VAL } { show_mmr_USx_MR_helper $NAME $ADDR $VAL }
