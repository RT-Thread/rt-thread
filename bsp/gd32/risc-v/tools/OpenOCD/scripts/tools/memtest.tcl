# Algorithms by Michael Barr, released into public domain
# Ported to OpenOCD by Shane Volpe, additional fixes by Paul Fertser

set CPU_MAX_ADDRESS 0xFFFFFFFF
source [find bitsbytes.tcl]
source [find memory.tcl]

proc runAllMemTests { baseAddress nBytes } {
    memTestDataBus $baseAddress
    memTestAddressBus $baseAddress $nBytes
    memTestDevice $baseAddress $nBytes
}

#***********************************************************************************
# *
# * Function:    memTestDataBus()
# *
# * Description: Test the data bus wiring in a memory region by
# *              performing a walking 1's test at a fixed address
# *              within that region.  The address (and hence the
# *              memory region) is selected by the caller.
# *		 Ported from:
# *		 http://www.netrino.com/Embedded-Systems/How-To/Memory-Test-Suite-C
# * Notes:
# *
# * Returns:     Empty string if the test succeeds.
# *              A non-zero result is the first pattern that failed.
# *
#***********************************************************************************
proc memTestDataBus { address } {
    echo "Running memTestDataBus"

    for {set i 0} {$i < 32} {incr i} {
	# Shift bit
	set pattern [expr {1 << $i}]

	# Write pattern to memory
	memwrite32 $address $pattern

	# Read pattern from memory
	set data [memread32 $address]

	if {$data != $pattern} {
	    echo "FAILED DATABUS: Address: $address, Pattern: $pattern, Returned: $data"
	    return $pattern
	}
    }
}

#***********************************************************************************
# *
# * Function:    memTestAddressBus()
# *
# * Description: Perform a walking 1's test on the relevant bits
# *              of the address and check for aliasing.  This test
# *              will find single-bit address failures such as stuck
# *              -high, stuck-low, and shorted pins.  The base address
# *              and size of the region are selected by the caller.
# *		 Ported from:
# *		 http://www.netrino.com/Embedded-Systems/How-To/Memory-Test-Suite-C
# *
# * Notes:       For best results, the selected base address should
# *              have enough LSB 0's to guarantee single address bit
# *              changes.  For example, to test a 64-Kbyte region,
# *              select a base address on a 64-Kbyte boundary.  Also,
# *              select the region size as a power-of-two--if at all
# *              possible.
# *
# * Returns:     Empty string if the test succeeds.
# *              A non-zero result is the first address at which an
# *              aliasing problem was uncovered.  By examining the
# *              contents of memory, it may be possible to gather
# *              additional information about the problem.
# *
#***********************************************************************************
proc memTestAddressBus { baseAddress nBytes } {
    set addressMask [expr $nBytes - 1]
    set pattern 0xAAAAAAAA
    set antipattern 0x55555555

    echo "Running memTestAddressBus"

    echo "addressMask: [convertToHex $addressMask]"

    echo "memTestAddressBus: Writing the default pattern at each of the power-of-two offsets..."
    for {set offset 32} {[expr $offset & $addressMask] != 0} {set offset [expr $offset << 1] } {
	set addr [expr $baseAddress + $offset]
	memwrite32 $addr $pattern
    }

    echo "memTestAddressBus: Checking for address bits stuck high..."
    memwrite32 $baseAddress $antipattern

    for {set offset 32} {[expr $offset & $addressMask] != 0} {set offset [expr $offset << 1]} {
	set addr [expr $baseAddress + $offset]
	set data [memread32 $addr]

	if {$data != $pattern} {
	    echo "FAILED DATA_ADDR_BUS_SHIGH: Address: [convertToHex $addr], Pattern: [convertToHex $pattern], Returned: [convertToHex $data]"
	    return $pattern
	}
    }

    echo "memTestAddressBus: Checking for address bits stuck low or shorted..."
    memwrite32 $baseAddress $pattern
    for {set testOffset 32} {[expr $testOffset & $addressMask] != 0} {set testOffset [expr $testOffset << 1] } {
	set addr [expr $baseAddress + $testOffset]
	memwrite32 $addr $antipattern

	set data [memread32 $baseAddress]
	if {$data != $pattern} {
	    echo "FAILED DATA_ADDR_BUS_SLOW: Address: [convertToHex $addr], Pattern: [convertToHex $pattern], Returned: [convertToHex $data]"
	    return $pattern
	}

	for {set offset 32} {[expr $offset & $addressMask] != 0} {set offset [expr $offset << 1]} {
	    set addr [expr $baseAddress + $offset]
	    set data [memread32 $baseAddress]

            if {(($data != $pattern) && ($offset != $testOffset))} {
		echo "FAILED DATA_ADDR_BUS_SLOW2: Address: [convertToHex $addr], Pattern: [convertToHex $pattern], Returned: [convertToHex $data], offset: [convertToHex $offset], testOffset [convertToHex $testOffset]"
		return $pattern
	    }
        }
	set addr [expr $baseAddress + $testOffset]
	memwrite32 $addr $pattern
    }
}

#***********************************************************************************
# *
# * Function:    memTestDevice()
# *
# * Description: Test the integrity of a physical memory device by
# *              performing an increment/decrement test over the
# *              entire region.  In the process every storage bit
# *              in the device is tested as zero and as one.  The
# *              base address and the size of the region are
# *              selected by the caller.
# *		 Ported from:
# *		 http://www.netrino.com/Embedded-Systems/How-To/Memory-Test-Suite-C
# * Notes:
# *
# * Returns:     Empty string if the test succeeds.
# *              A non-zero result is the first address at which an
# *              incorrect value was read back.  By examining the
# *              contents of memory, it may be possible to gather
# *              additional information about the problem.
# *
#***********************************************************************************
proc memTestDevice { baseAddress nBytes } {
    echo "Running memTestDevice"

    echo "memTestDevice: Filling memory with a known pattern..."
    for {set pattern 1; set offset 0} {$offset < $nBytes} {incr pattern; incr offset 32} {
	memwrite32 [expr $baseAddress + $offset] $pattern
    }

    echo "memTestDevice: Checking each location and inverting it for the second pass..."
    for {set pattern 1; set offset 0} {$offset < $nBytes} {incr pattern; incr offset 32} {
	set addr [expr $baseAddress + $offset]
	set data [memread32 $addr]

	if {$data != $pattern} {
	    echo "FAILED memTestDevice_pattern: Address: [convertToHex $addr], Pattern: [convertToHex $pattern], Returned: [convertToHex $data], offset: [convertToHex $offset]"
	    return $pattern
	}

	set antiPattern [expr ~$pattern]
	memwrite32 [expr $baseAddress + $offset] $antiPattern
    }

    echo "memTestDevice: Checking each location for the inverted pattern and zeroing it..."
    for {set pattern 1; set offset 0} {$offset < $nBytes} {incr pattern; incr offset 32} {
	set antiPattern [expr ~$pattern & ((1<<32) - 1)]
	set addr [expr $baseAddress + $offset]
	set data [memread32 $addr]
	set dataHex [convertToHex $data]
	set antiPatternHex [convertToHex $antiPattern]
	if {[expr $dataHex != $antiPatternHex]} {
	    echo "FAILED memTestDevice_antipattern: Address: [convertToHex $addr], antiPattern: $antiPatternHex, Returned: $dataHex, offset: $offset"
	    return $pattern
	}
    }
}

proc convertToHex { value } {
    format 0x%08x $value
}
