# MEMORY
#
# All Memory regions have two components.
#    (1) A count of regions, in the form N_NAME
#    (2) An array within info about each region.
#
# The ARRAY
#
#       <NAME>(  RegionNumber ,  ATTRIBUTE )
#
# Where <NAME> is one of:
#
#     N_FLASH  & FLASH   (internal memory)
#     N_RAM    & RAM     (internal memory)
#     N_MMREGS & MMREGS  (for memory mapped registers)
#     N_XMEM   & XMEM    (off chip memory, ie: flash on cs0, sdram on cs2)
# or  N_UNKNOWN & UNKNOWN for things that do not exist.
#
# We have 1 unknown region.
set N_UNKNOWN 1
# All MEMORY regions must have these attributes
#     CS          - chip select (if internal, use -1)
set UNKNOWN(0,CHIPSELECT) -1
#     BASE        - base address in memory
set UNKNOWN(0,BASE)       0
#     LEN         - length in bytes
set UNKNOWN(0,LEN)        $CPU_MAX_ADDRESS
#     HUMAN       - human name of the region
set UNKNOWN(0,HUMAN) "unknown"
#     TYPE        - one of:
#                       flash, ram, mmr, unknown
#                    For harvard arch:
#                       iflash, dflash, iram, dram
set UNKNOWN(0,TYPE)       "unknown"
#     RWX         - access ablity
#                       unix style chmod bits
#                           0 - no access
#                           1 - execute
#                           2 - write
#                           4 - read
#                       hence: 7 - readwrite execute
set RWX_NO_ACCESS     0
set RWX_X_ONLY        $BIT0
set RWX_W_ONLY        $BIT1
set RWX_R_ONLY        $BIT2
set RWX_RW            [expr $RWX_R_ONLY + $RWX_W_ONLY]
set RWX_R_X           [expr $RWX_R_ONLY + $RWX_X_ONLY]
set RWX_RWX           [expr $RWX_R_ONLY + $RWX_W_ONLY + $RWX_X_ONLY]
set UNKNOWN(0,RWX)     $RWX_NO_ACCESS

#     WIDTH       - access width
#                      8,16,32 [0 means ANY]
set ACCESS_WIDTH_NONE 0
set ACCESS_WIDTH_8    $BIT0
set ACCESS_WIDTH_16   $BIT1
set ACCESS_WIDTH_32   $BIT2
set ACCESS_WIDTH_ANY  [expr $ACCESS_WIDTH_8 + $ACCESS_WIDTH_16 + $ACCESS_WIDTH_32]
set UNKNOWN(0,ACCESS_WIDTH) $ACCESS_WIDTH_NONE

proc iswithin { ADDRESS BASE LEN } {
    return [expr ((($ADDRESS - $BASE) >= 0) && (($BASE + $LEN - $ADDRESS) > 0))]
}

proc address_info { ADDRESS } {

    foreach WHERE { FLASH RAM MMREGS XMEM UNKNOWN } {
	if { info exists $WHERE } {
	    set lmt [set N_[set WHERE]]
	    for { set region 0 } { $region < $lmt } { incr region } {
		if { iswithin $ADDRESS $WHERE($region,BASE) $WHERE($region,LEN) } {
		    return  "$WHERE $region";
		}
	    }
	}
    }

    # Return the 'unknown'
    return "UNKNOWN 0"
}

proc memread32 {ADDR} {
    set foo(0) 0
    if ![ catch { mem2array foo 32 $ADDR 1  } msg ] {
	return $foo(0)
    } else {
	error "memread32: $msg"
    }
}

proc memread16 {ADDR} {
    set foo(0) 0
    if ![ catch { mem2array foo 16 $ADDR 1  } msg ] {
	return $foo(0)
    } else {
	error "memread16: $msg"
    }
}

proc memread8 {ADDR} {
    set foo(0) 0
    if ![ catch { mem2array foo 8 $ADDR 1  } msg ] {
	return $foo(0)
    } else {
	error "memread8: $msg"
    }
}

proc memwrite32 {ADDR DATA} {
    set foo(0) $DATA
    if ![ catch { array2mem foo 32 $ADDR 1  } msg ] {
	return $foo(0)
    } else {
	error "memwrite32: $msg"
    }
}

proc memwrite16 {ADDR DATA} {
    set foo(0) $DATA
    if ![ catch { array2mem foo 16 $ADDR 1  } msg ] {
	return $foo(0)
    } else {
	error "memwrite16: $msg"
    }
}

proc memwrite8 {ADDR DATA} {
    set foo(0) $DATA
    if ![ catch { array2mem foo 8 $ADDR 1  } msg ] {
	return $foo(0)
    } else {
	error "memwrite8: $msg"
    }
}

proc memread32_phys {ADDR} {
    set foo(0) 0
    if ![ catch { mem2array foo 32 $ADDR 1 phys } msg ] {
	return $foo(0)
    } else {
	error "memread32: $msg"
    }
}

proc memread16_phys {ADDR} {
    set foo(0) 0
    if ![ catch { mem2array foo 16 $ADDR 1 phys } msg ] {
	return $foo(0)
    } else {
	error "memread16: $msg"
    }
}

proc memread8_phys {ADDR} {
    set foo(0) 0
    if ![ catch { mem2array foo 8 $ADDR 1 phys } msg ] {
	return $foo(0)
    } else {
	error "memread8: $msg"
    }
}

proc memwrite32_phys {ADDR DATA} {
    set foo(0) $DATA
    if ![ catch { array2mem foo 32 $ADDR 1 phys } msg ] {
	return $foo(0)
    } else {
	error "memwrite32: $msg"
    }
}

proc memwrite16_phys {ADDR DATA} {
    set foo(0) $DATA
    if ![ catch { array2mem foo 16 $ADDR 1 phys } msg ] {
	return $foo(0)
    } else {
	error "memwrite16: $msg"
    }
}

proc memwrite8_phys {ADDR DATA} {
    set foo(0) $DATA
    if ![ catch { array2mem foo 8 $ADDR 1 phys } msg ] {
	return $foo(0)
    } else {
	error "memwrite8: $msg"
    }
}
