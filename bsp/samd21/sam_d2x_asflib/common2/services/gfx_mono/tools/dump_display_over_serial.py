##
# \file
#
# \brief Convert display data on a serial line to a graphical representation
#
# Copyright (C) 2011-2014 Atmel Corporation. All rights reserved.
#
# \page License
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# 3. The name of Atmel may not be used to endorse or promote products derived
# from this software without specific prior written permission.
#
# 4. This software may only be redistributed and used in connection with an
# Atmel microcontroller product.
#
# THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
import sys
import serial
import os.path
import argparse

def scan_for_ports():
	available_ports = []

	for index in range(64):
		try:
			serial_port = serial.Serial(index)
			available_ports.append((index, serial_port.portstr))
			serial_port.close()
		except serial.SerialException:
			pass
		except IndexError as Error:
			pass

	for port_number, port_name in available_ports:
		print "%02d - %s" % (port_number, port_name)

	return available_ports

def dump_display_data(serial_port, baud_rate, output_file_name):
	try:
		output_file = open(output_file_name, 'w')
		port        = serial.Serial(port = serial_port,
				baudrate = baud_rate, timeout = 1)
		port.close()
		port.open()
	except ValueError as e:
		print "error: invalid serial port parameters. %s" % (str(e))
		output_file.close()
		return -1
	except serial.SerialException as e:
		print "error: could not open serial port. %s" % (str(e))
		output_file.close()
		return -1
	except IOError as e:
		print "error: could not open output file. %s" % (str(e))
		return -1

	print "Display on %s: %u,8,N,1" % (port.name, port.baudrate)
	port.write("D")
	line = port.readline()
	display_data = ""
	while(line[:2] != "};") :
		display_data = display_data + line[:-1]
		line = port.readline()
	display_data = display_data + line
	port.close()

	print "Writing data to file %s" % (output_file_name)
	output_file.write(display_data)

	output_file.close()

def main():
	parser = argparse.ArgumentParser(description="This script will try to "
			"open the given serial port, send a string to "
			"instruct the target device to dump the contents of "
			"the display to a serial link in XPM format. The "
			"received file is then written to 'display.xpm', "
			"unless a file is specified by the -o option.")
	parser.add_argument("-p", "--port", dest="serial_port",
			help="which serial port to open")
	parser.add_argument("-b", "--baud", dest="baudrate", type=int,
			help="baud rate to use for serial communication",
			default=19200)
	parser.add_argument("-o", "--output", dest="output_file",
			help="write XPM image to FILE. Default is display.xpm.",
			metavar="FILE", default="display.xpm")
	parser.add_argument("-s", "--scan", action="store_true",
			dest="scan_ports",
			help="scan for available serial ports and exit",
			default=False)

	arguments = parser.parse_args()

	if arguments.scan_ports:
		scan_for_ports()
		sys.exit()

	if arguments.serial_port is None:
		parser.print_usage()
		sys.exit()

	if os.path.exists(arguments.output_file):
		print "Warning: output file '%s' already exists" % (arguments.output_file)
		print "Do you want to write over file '%s'?" % (arguments.output_file)
		answer = raw_input("[yes/NO] ")
		if answer not in ("yes", "Yes", "YES"):
			sys.exit()

	dump_display_data(arguments.serial_port, arguments.baudrate, arguments.output_file)

if __name__ == "__main__":
	main()
