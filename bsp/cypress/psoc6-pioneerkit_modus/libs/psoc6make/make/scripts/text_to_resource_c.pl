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
    print "Usage ./text_to_resource__c.pl  <MEM|FILESYS> <variable name> <text file>";
    exit;
}

# Print start of output
my $location = shift @ARGV;
my $variable_name = shift @ARGV;
my $original_variable_name = $variable_name;
my $file = shift @ARGV;

#open the file
open INFILE, "<:raw", $file or die "cant open " . $file;
@file_cont_array = <INFILE>;
close INFILE;
$file_cont = join('',@file_cont_array);


print "#include \"cy_abs_resource.h\"\n";
print "\n";

my $pos = 0;

if ( ( $file =~ m/\.html$/sgi ) ||
     ( $file =~ m/\.txt$/sgi ) )
{
  while ( $file_cont =~ s/^(.*?)\r?\n?\<WICED\:section\s+suffix=\"(\S+)\"\s*\/\>\r?\n?(.*)$/$3/sgi )
  {
    my $substr = $1;
    my $variable_suffix = $2;
    my $nextpos = $-[3];

    print "\n";
    if ( $location ne "MEM" )
    {
        $name = $file;
        $name=~s/^.+\/(.*?)/$1/;
        print "const cy_resource_handle_t ${variable_name} = { CY_RESOURCE_IN_FILESYSTEM, " . (length( $substr )) . ", { .fs = { $pos, \"$name\" }}};\n";
        print "\n";
    }
    else
    {
        print "const uint8_t ${variable_name}_data[" . (length( $substr )+1) . "] = ";
        my $section_length = length( $substr );
        while ( $substr =~ s/^(.*?\n)(.*)$/$2/sgi )
        {
            print "\"" . escape_string( $1 ) . "\" \\\n";
        }
        print "\"" . escape_string( $substr ) . "\";\n";

        print "const cy_resource_handle_t ${variable_name} = { CY_RESOURCE_IN_MEMORY, $section_length, { .mem_data = ${variable_name}_data}};";
        print "\n";
    }

    $variable_name = $original_variable_name . $variable_suffix;
    $pos += $nextpos;
  }
}

if ( $location ne "MEM" )
{
    print "\n";
    $name = $file;
    $name=~s/^.+\/(.*?)/$1/;
    print "const cy_resource_handle_t ${variable_name} = { CY_RESOURCE_IN_FILESYSTEM, " . (length( $file_cont )) . ", { .fs = { $pos, \"$name\" }}};\n";
    print "\n";
}
else
{
    print "const uint8_t ${variable_name}_data[" . (length( $file_cont ) + 1) . "] = ";
    my $section_length = length( $file_cont );
    while ( $file_cont =~ s/^(.*?\n)(.*)$/$2/sgi )
    {
        print "\"" . escape_string( $1 ) . "\" \\\n";
    }
    print "\"" . escape_string( $file_cont ) . "\";\n";
    print "const cy_resource_handle_t ${variable_name} = { CY_RESOURCE_IN_MEMORY, $section_length, { .mem_data = ${variable_name}_data }};";
    print "\n";
}

sub escape_string( $escstring )
{
  my $escstring = shift;
  # Escape characters for C string
  $escstring =~ s/\\/\\\\/sgi; # backslash
  $escstring =~ s/\a/\\a/sgi;  # bell
  $escstring =~ s/\x8/\\b/sgi; # backspace
  $escstring =~ s/\f/\\f/sgi;  # formfeed
  $escstring =~ s/\n/\\n/sgi;  # linefeed
  $escstring =~ s/\r/\\r/sgi;  # carriage return
  $escstring =~ s/\t/\\t/sgi;  # tab
  $escstring =~ s/\xB/\\v/sgi; # vertical tab
  $escstring =~ s/\'/\\'/sgi;  # single quote
  $escstring =~ s/\"/\\"/sgi;  # double quote
  return $escstring;
}
