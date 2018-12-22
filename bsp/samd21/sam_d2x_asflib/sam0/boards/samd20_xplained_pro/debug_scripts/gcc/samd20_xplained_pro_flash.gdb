#*******************************************************
#
#  Connect to J-Link and debug application in flash.
#

# define 'reset' command
define reset

# Connect to the J-Link gdb server
target remote localhost:2331

# Reset the chip to get to a known state
monitor reset

# Select flash device
monitor flash device = ATSAMD20J18A
# Enable flash download and flash breakpoints
monitor flash download = 1

# Load the program
load

# Initializing PC and stack pointer
mon reg sp=(0x22008000)
mon reg pc=(0x00000000)
info reg

# end of 'reset' command
end
