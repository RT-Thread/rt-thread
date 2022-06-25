#----------------------------------------
# Purpose - Create some $BIT variables
#           Create $K and $M variables
#          and some bit field extraction variables.
# Creat helper variables ...
#    BIT0.. BIT31

for { set x 0  } { $x < 32 } { set x [expr $x + 1]} {
    set vn [format "BIT%d" $x]
    global $vn
    set $vn   [expr (1 << $x)]
}

# Create K bytes values
#    __1K ... to __2048K
for { set x 1  } { $x < 2048 } { set x [expr $x * 2]} {
    set vn [format "__%dK" $x]
    global $vn
    set $vn   [expr (1024 * $x)]
}

# Create M bytes values
#    __1M ... to __2048K
for { set x 1  } { $x < 2048 } { set x [expr $x * 2]} {
    set vn [format "__%dM" $x]
    global $vn
    set $vn [expr (1024 * 1024 * $x)]
}

proc create_mask { MSB LSB } {
    return [expr (((1 << ($MSB - $LSB + 1))-1) << $LSB)]
}

# Cut Bits $MSB to $LSB out of this value.
# Example: % format "0x%08x" [extract_bitfield 0x12345678 27 16]
# Result:  0x02340000

proc extract_bitfield { VALUE MSB LSB } {
    return [expr [create_mask $MSB $LSB] & $VALUE]
}


# Cut bits $MSB to $LSB out of this value
# and shift (normalize) them down to bit 0.
#
# Example: % format "0x%08x" [normalize_bitfield 0x12345678 27 16]
# Result:  0x00000234
#
proc normalize_bitfield { VALUE MSB LSB } {
    return [expr [extract_bitfield $VALUE $MSB $LSB ] >> $LSB]
}

proc show_normalize_bitfield { VALUE MSB LSB } {
    set m [create_mask $MSB $LSB]
    set mr [expr $VALUE & $m]
    set sr [expr $mr >> $LSB]
    echo [format "((0x%08x & 0x%08x) -> 0x%08x) >> %2d => (0x%x) %5d " $VALUE $m $mr $LSB $sr $sr]
   return $sr
}
