Prerequisites:
The users of OpenOCD as well as computer programs interacting with OpenOCD are expecting that certain commands
do the same thing across all the targets.

Rules to follow when writing scripts:

1. The configuration script should be defined such as , for example, the following sequences are working:
	reset
	flash info <bank>
and
	reset
	flash erase_address <start> <len>
and
	reset init
	load

In most cases this can be accomplished by specifying the default startup mode as reset_init (target command
in the configuration file).

2. If the target is correctly configured, flash must be writable without any other helper commands. It is
assumed that all write-protect mechanisms should be disabled.

3. The configuration scripts should be defined such as the binary that was written to flash verifies
(turn off remapping, checksums, etc...)

flash write_image [file] <parameters>
verify_image [file] <parameters>

4. adapter speed sets the maximum speed (or alternatively RCLK). If invoked
multiple times only the last setting is used.

interface/xxx.cfg files are always executed *before* target/xxx.cfg
files, so any adapter speed in interface/xxx.cfg will be overridden by
target/xxx.cfg. adapter speed in interface/xxx.cfg would then, effectively,
set the default JTAG speed.

Note that a target/xxx.cfg file can invoke another target/yyy.cfg file,
so one can create target subtype configurations where e.g. only
amount of DRAM, oscillator speeds differ and having a single
config file for the default/common settings.
