##
# \file
#
# \brief Output a 2 color bitmap as an uint8_t array
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

from PIL import Image
import sys

im = Image.open(sys.argv[1]);
new_im = im.load()

width, height = im.size

for y in range(0, height) :
	for x in range(0, width) :
		if 0 < new_im[x, y]:
			new_im[x, y] = 1
		sys.stdout.write(str(new_im[x, y]))
	sys.stdout.write("\n")

sys.stdout.write("\n uint8_t image_header[] = {\n")
for y in range(0, height, 8) :
	for x in range(0, width) :
		first_byte = str(new_im[x, y + 7]) + str(new_im[x, y+6]) + str(new_im[x, y+5]) + str(new_im[x, y+4]) + str(new_im[x, y+3]) + str(new_im[x, y+2]) + str(new_im[x, y+1]) + str(new_im[x, y+0])
		print "0x%x," % int(first_byte, 2),

sys.stdout.write("};\n")
