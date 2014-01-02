######################################################################## 
# $Id:: makefile 814 2008-06-19 19:57:32Z pdurgesh                     $
# 
# Project: Standard compile makefile
# 
# Description: 
#  Makefile
# 
######################################################################## 
# Software that is described herein is for illustrative purposes only  
# which provides customers with programming information regarding the  
# products. This software is supplied "AS IS" without any warranties.  
# NXP Semiconductors assumes no responsibility or liability for the 
# use of the software, conveys no license or title under any patent, 
# copyright, or mask work right to the product. NXP Semiconductors 
# reserves the right to make changes in the software without 
# notification. NXP Semiconductors also make no representation or 
# warranty that such application will be suitable for the specified 
# use without further testing or modification. 
########################################################################

########################################################################
#
# Get the project root
#
########################################################################
PROJ_ROOT			= $(CURDIR)/../..

########################################################################
#
# Pick up the configuration file in make section
#
########################################################################
include ../../makesection/makeconfig 

########################################################################
#
# Pick up the default build rules 
#
########################################################################

include $(PROJ_ROOT)/makesection/makerule/LPC/make.LPC.$(TOOL)

########################################################################
#
# Pick up the assembler and C source files in the directory  
#
########################################################################
include $(PROJ_ROOT)/makesection/makerule/common/make.rules.ftypes
AFLAGS +=-I../include 
CFLAGS +=-I../include 


########################################################################
#
# Build the library
#
########################################################################

$(TARGET_FWLIB_LIB) : .vias $(OBJS) $(FWLIB_LIB_DIR)
	$(ECHO) "creating" $(FWLIB) "Firmware support package library" 
	$(AR) $@ $(OBJS)

$(FWLIB_LIB_DIR):
	$(MKDIR) $(FWLIB_LIB_DIR)	

# delete all targets this Makefile can make
lib_clean:
	-@$(RM) $(TARGET_FWLIB_LIB)

# delete all targets this Makefile can make and all built libraries
# linked in
lib_realclean: 
	-@$(RM) $(FWLIB_LIB_DIR)/*.a
	-@$(RMDIR) $(FWLIB_LIB_DIR)
	
clean: lib_clean
realclean: lib_realclean 

########################################################################
#
# Compile the code base 
#
########################################################################

include $(PROJ_ROOT)/makesection/makerule/common/make.rules.build

.PHONY: all lib_clean lib_realclean



