echo "\n\nFirmware recovery helpers"
echo "Use -c firmware_help to get help\n"

set known_boards {
    "asus-rt-n16		ASUS RT-N16"
    "asus-rt-n66u		ASUS RT-N66U"
    "linksys-wag200g		Linksys WAG200G"
    "linksys-wrt54gl		Linksys WRT54GL v1.1"
    "netgear-dg834v3		Netgear DG834G v3"
    "tp-link_tl-mr3020		TP-LINK TL-MR3020"
    "bt-homehubv1		BT HomeHub v1"
}

proc firmware_help { } {
    echo "
Your OpenOCD command should look like this:
openocd -f interface/<jtag adapter>.cfg -f tools/firmware-recovery.tcl -c \"<commands>*; shutdown\"

Where:
<jtag adapter> is one of the supported devices, e.g. ftdi/jtagkey2
<commands> are firmware-recovery commands separated by semicolon

Supported commands:
firmware_help			get this help
list_boards			list known boards and exit
board <name>			select board you work with
list_partitions			list partitions of the currently selected board
dump_part <name> <filename>	save partition's contents to a file
erase_part <name>		erase the given partition
flash_part <name> <filename>	erase, flash and verify the given partition
ram_boot <filename>		load binary file to RAM and run it
adapter speed <freq>		set JTAG clock frequency in kHz

For example, to clear nvram and reflash CFE on an RT-N16 using TUMPA, run:
openocd -f interface/ftdi/tumpa.cfg -f tools/firmware-recovery.tcl \\
	-c \"board asus-rt-n16; erase_part nvram; flash_part CFE cfe-n16.bin; shutdown\"
\n\n"
    shutdown
}

# set default, can be overridden later
adapter speed 1000

proc get_partition { name } {
    global partition_list
    dict get $partition_list $name
}

proc partition_desc { name } { lindex [get_partition $name] 0 }
proc partition_start { name } { lindex [get_partition $name] 1 }
proc partition_size { name } { lindex [get_partition $name] 2 }

proc list_boards { } {
    global known_boards
    echo "List of the supported boards:\n"
    echo "Board name\t\tDescription"
    echo "-----------------------------------"
    foreach i $known_boards {
	echo $i
    }
    echo "\n\n"
}

proc board { name } {
    script [find board/$name.cfg]
}

proc list_partitions { } {
    global partition_list
    set fstr "%-16s%-14s%-14s%s"
    echo "\nThe currently selected board is known to have these partitions:\n"
    echo [format $fstr Name Start Size Description]
    echo "-------------------------------------------------------"
    for {set i 0} {$i < [llength $partition_list]} {incr i 2} {
	set key [lindex $partition_list $i]
	echo [format $fstr $key [partition_start $key] [partition_size $key] [partition_desc $key]]
    }
    echo "\n\n"
}

# Magic to work with any targets, including semi-functional
proc prepare_target { } {
    init
    catch {halt}
    catch {reset init}
    catch {halt}
}

proc dump_part { name filename } {
    prepare_target
    dump_image $filename [partition_start $name] [partition_size $name]
}

proc erase_part { name } {
    prepare_target
    flash erase_address [partition_start $name] [partition_size $name]
}

proc flash_part { name filename } {
    prepare_target
    flash write_image erase $filename [partition_start $name] bin
    echo "Verifying:"
    verify_image $filename [partition_start $name]
}

proc ram_boot { filename } {
    global ram_boot_address
    prepare_target
    load_image $filename $ram_boot_address bin
    resume $ram_boot_address
}

echo ""
