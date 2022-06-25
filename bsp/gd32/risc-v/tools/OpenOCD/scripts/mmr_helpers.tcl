
proc proc_exists { NAME } {
    set n [info commands $NAME]
    set l [string length $n]
    return [expr $l != 0]
}

# Give: REGISTER name - must be a global variable.
proc show_mmr32_reg { NAME } {

    global $NAME
    # we want $($NAME)
    set a [set [set NAME]]

    if ![catch { set v [memread32 $a] } msg ] {
	echo [format "%15s: (0x%08x): 0x%08x" $NAME $a $v]

	# Was a helper defined?
	set fn show_${NAME}_helper
	if [ proc_exists $fn ] {
	    # Then call it
	    $fn $NAME $a $v
	}
	return $v;
    } else {
	error [format "%s (%s)" $msg $NAME ]
    }
}


# Give: NAMES - an array of names accessible
#               in the callers symbol-scope.
#       VAL - the bits to display.

proc show_mmr32_bits { NAMES VAL } {

    upvar $NAMES MYNAMES

    set w 5
    foreach {IDX N} $MYNAMES {
	set l [string length $N]
	if { $l > $w } { set w $l }
    }

    for { set x 24 } { $x >= 0 } { incr x -8 } {
	echo -n "  "
	for { set y 7 } { $y >= 0 } { incr y -1 } {
	    set s $MYNAMES([expr $x + $y])
	    echo -n [format "%2d: %-*s | " [expr $x + $y] $w $s ]
	}
	echo ""

	echo -n "  "
	for { set y 7 } { $y >= 0 } { incr y -1 } {
	    echo -n [format "    %d%*s | " [expr !!($VAL & (1 << ($x + $y)))] [expr $w -1] ""]
	}
	echo ""
    }
}


proc show_mmr_bitfield { MSB LSB VAL FIELDNAME FIELDVALUES } {
    set width [expr (($MSB - $LSB + 1) + 7) / 4]
    set nval [show_normalize_bitfield $VAL $MSB $LSB ]
    set name0 [lindex $FIELDVALUES 0 ]
    if [ string compare $name0 _NUMBER_ ] {
	set sval [lindex $FIELDVALUES $nval]
    } else {
	set sval ""
    }
    echo [format "%-15s: %d (0x%0*x) %s" $FIELDNAME $nval $width $nval $sval ]
}
