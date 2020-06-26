#!/usr/bin/perl

#
# Copyright 2019, Cypress Semiconductor Corporation or a subsidiary of
# Cypress Semiconductor Corporation. All Rights Reserved.
#
# This software, including source code, documentation and related
# materials ("Software"), is owned by Cypress Semiconductor Corporation
# or one of its subsidiaries ("Cypress") and is protected by and subject to
# worldwide patent protection (United States and foreign),
# United States copyright laws and international treaty provisions.
# Therefore, you may use this Software only as provided in the license
# agreement accompanying the software package from which you
# obtained this Software ("EULA").
# If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
# non-transferable license to copy, modify, and compile the Software
# source code solely for use in connection with Cypress's
# integrated circuit products. Any reproduction, modification, translation,
# compilation, or representation of this Software except as specified
# above is prohibited without the express written permission of Cypress.
#
# Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
# reserves the right to make changes to the Software without notice. Cypress
# does not assume any liability arising out of the application or use of the
# Software or any product or circuit described in the Software. Cypress does
# not authorize its products for use in any products where a malfunction or
# failure of the Cypress product may reasonably be expected to result in
# significant property damage, injury or death ("High Risk Product"). By
# including Cypress's product in a High Risk Product, the manufacturer
# of such system or application assumes all risk of such use and in doing
# so agrees to indemnify Cypress against all liability.
#

if (! $ARGV[0] )
{
    print "Usage ./resources_header.pl  <C file 1> <C file 2> ...";
    exit;
}

print "/* Auto-generated header file. Do not edit */\n";
print "\n";
print "#pragma once\n";
print "\n";
print "#include <stdint.h>\n";
print "#include \"cy_abs_resource.h\"\n";
print "\n";
print "#ifdef __cplusplus\n";
print "extern \"C\" {\n";
print "#endif\n";
print "\n";


my $mem_resources = "";
my $filesystem_resources = "";

foreach $file (@ARGV)
{
    #open the file
    open INFILE, $file or die "cant open " . $file;

    @file_cont_array = <INFILE>;
    close INFILE;
    $file_cont = join('',@file_cont_array);

    while ( $file_cont =~ m/(const cy_resource_handle_t \S+)/sgi )
    {
        $resources .= "extern $1;\n";
    }
    while ( $file_cont =~ m/(const uint8_t \S+\[\d+\])/sgi )
    {
        $resources .= "extern $1;\n";
    }
}

print "\n";
print "$resources";
print "\n";
print "/* @} */\n";
print "#ifdef __cplusplus\n";
print "} /*extern \"C\" */\n";
print "#endif\n";
