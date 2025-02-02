#!/usr/bin/perl
# SPDX-License-Identifier: GPL-2.0-or-later

#
# Helper for generating GPIO setup for STM32F0, F4, F7, H7, L0, L1, L4, L4+
# and F1 (for 'stmqspi' and 'cmspi' drivers).
#
# Each pin is configured by "PortAndBit:Conf:Speed"
#  'PortAndBit' specifies Port and bit number
#  'Conf' is one of 'AFx' (alternate), 'P' (output), 'IN' (input),
#    (each optionally by 'P' (push-pull) or 'O' (open-drain)),
#    (all optionally followed by 'UP' (pull-up), or 'DO' (pull-down))
#  'Speed' is one of 'L' (low), 'M' (medium), 'H' (high), 'V' (very high)
#
# Port configuration can be given on command line as a single string (pins separated by commas)
# or via CubeMX generated file. The latter must consist of the quadspi.c / octospi.c and the
# corresponding header. The precise spelling in these files doesn't seem to be consistent, though ...
#
# Pins have to be ordered this way:
#  - I2C: SDA, SCL
#  - SPI (1 line): NCS, CLK, IO1/MISO, IO0/MOSI
#  - DPI (2 lines): NCS, CLK, IO1/MISO, IO0/MOSI
#  - QPI (4 lines): NCS, CLK, IO3/NHOLD, IO2/NWP, IO1/MISO, IO0/MOSI
# For dual flash: BK_1 first, then BK_2. If single NCS for both, omit NCS in BK_2
# For octal flash: NCS, CLK, DQS, IO7 down to IO0

use strict;
use Getopt::Std;

my $GPIO_BASE = 0x58020000;
my $Conf = "PA06:AF06:V, PA07:AF10:V, PB00:AF04:V, PB01:AF04:V, PB02:AF09:V, PE11:AF11:V";
my $STM32F1 = 0;

# "Blue-Pill stm32f103cbt6 board w/ cmspi
#$STM32F1 = 1;
#$GPIO_BASE = 0x40010800;
#$Conf = "PB12:PP:M, PB13:PP:V, PB14:INUP:V, PB15:INUP:V";
#$Conf = "PB12:PP:M, PB13:PP:V, PB14:INUP:V, PB01:INUP:V";

#$STM32F1 = 1;
#$GPIO_BASE = 0x40010800;
#$Conf = "PB07:INUP:V, PB06:INUP:V";

# mini-stm32f030f4p6 board w/ cmspi
#$GPIO_BASE = 0x48000000;
#$Conf = "PB01:PP:V, PA05:PP:V, PA06:INUP:V, PA07:INUP:V";

# stm32f407vet6 board w/ cmspi
#$GPIO_BASE = 0x40020000;
#$Conf = "PB00:PP:M, PB03:PP:V, PB04:INUP:V, PB05:INUP:V";

# stm32f412g-disco quad
#$GPIO_BASE = 0x40020000;
#$Conf = "PB02:AF09:V, PF09:AF10:V, PF08:AF10:V, PF07:AF09:V, PF06:AF09:V, PG06:AF10:V";

# stm32f413h-disco
#$GPIO_BASE = 0x40020000;
#$Conf = "PB02:AF09:V, PD13:AF09:V, PE02:AF09:V, PF09:AF10:V, PF08:AF10:V, PG06:AF10:V";

# stm32f469i-disco quad
#$GPIO_BASE = 0x40020000;
#$Conf = "PB06:AF10:V, PF10:AF09:V, PF09:AF10:V, PF08:AF10:V, PF07:AF09:V, PF06:AF09:V";
# w/ cmspi
#$Conf = "PB06:PP:M, PF10:PP:V, PF06:INUP:V, PF07:INUP:V, PF09:INUP:V, PF08:INUP:V";

# stm32f723e-disco quad
#$GPIO_BASE = 0x40020000;
#$Conf = "PB06:AF10:V, PB02:AF09:V, PC10:AF09:V, PC09:AF09:V, PD13:AF09:V, PE02:AF09:V";

# stm32f746g-disco quad
#$GPIO_BASE = 0x40020000;
#Conf = "PB06:AF10:V, PB02:AF09:V, PD13:AF09:V, PE02:AF09:V, PD12:AF09:V, PD11:AF09:V";
# w/ cmspi
#$Conf = "PB06:PP:M, PB02:PP:V, PD13:INUP:V, PE02:INUP:V, PD12:INUP:V, PD11:INUP:V";

# stm32f769i-disco quad
#$GPIO_BASE = 0x40020000;
#$Conf = "PB06:AF10:V, PB02:AF09:V, PC10:AF09:V, PC09:AF09:V, PD13:AF09:V, PE02:AF09:V";
# w/ cmspi
#$Conf = "PB06:PP:M, PB02:PP:V, PD13:INUP:V, PE02:INUP:V, PC10:INUP:V, PC09:INUP:V, ";

# b-l475e-iot01a quad
#$GPIO_BASE = 0x48000000;
#$Conf = "PE15:AF10:V, PE14:AF10:V, PE13:AF10:V, PE12:AF10:V, PE11:AF10:V, PE10:AF10:V";

# stm32l476g-disco quad
#$GPIO_BASE = 0x48000000;
#$Conf = "PE15:AF10:V, PE14:AF10:V, PE13:AF10:V, PE12:AF10:V, PE11:AF10:V, PE10:AF10:V";

# stm32l496g-disco quad
#$GPIO_BASE = 0x48000000;
#$Conf = "PA07:AF10:V, PA06:AF10:V, PA03:AF10:V, PB11:AF10:V, PB01:AF10:V, PB00:AF10:V";

# stm32l4r9i-disco octal
#$GPIO_BASE = 0x48000000;
#$Conf = "PG15:AF05:V, PG12:AF05:V, PG10:AF05:V, PG09:AF05:V, PH10:AF05:V, PH09:AF05:V, "
#      . "PH08:AF05:V, PI11:AF05:V, PI10:AF05:V, PI09:AF05:V, PI06:AF05:V";

# stm32l4p5g-disco octal/octal
#$GPIO_BASE = 0x48000000;
#$Conf = "PA07:AF10:V, PA06:AF10:V, PC03:AF10:V, PD07:AF10:V, PD05:AF10:V, PD04:AF10:V, "
#      . "PE13:AF10:V, PE12:AF10:V, PE11:AF10:V, PE10:AF10:V, PG06:AF03:V";
#$Conf = "PF12:AF05:V, PF04:AF05:V, PF03:AF05:V, PF02:AF05:V, PF01:AF05:V, PF00:AF05:V, "
#      . "PG12:AF05:V, PG10:AF05:V, PG09:AF05:V, PG01:AF05:V, PG00:AF05:V";

# nucleo-f767zi dual quad
#$GPIO_BASE = 0x40020000;
#$Conf = "PB06:AF10:V, PB02:AF09:V, PC11:AF09:V, PD13:AF09:V, PE02:AF09:V, PD12:AF09:V, "
#      . "PD11:AF09:V, PE10:AF10:V, PE09:AF10:V, PE08:AF10:V, PE07:AF10:V";
# w/ cmspi
#$Conf = "PB10:PPUP:M, PB02:PPUP:V, PD13:INPUP:V, PE02:INPUP:V, PD12:INPUP:V, PD11:INPUP:V";
#$Conf = "PC11:PPUP:M, PB02:PPUP:V, PE10:INPUP:V, PE09:INPUP:V, PE08:INPUP:V, PE07:INPUP:V";

# nucleo-h743zi dual quad
#$GPIO_BASE = 0x58020000;
#$Conf = "PB10:AF09:V, PB02:AF09:V, PC11:AF09:V, PD13:AF09:V, PE02:AF09:V, PD12:AF09:V, "
#      . "PD11:AF09:V, PE10:AF10:V, PE09:AF10:V, PE08:AF10:V, PE07:AF10:V";
# w/ cmspi
#$Conf = "PB10:PPUP:M, PB02:PPUP:V, PD13:INPUP:V, PE02:INPUP:V, PD12:INPUP:V, PD11:INPUP:V";
#$Conf = "PC11:PPUP:M, PB02:PPUP:V, PE10:INPUP:V, PE09:INPUP:V, PE08:INPUP:V, PE07:INPUP:V";

# nucleo-h7a3zi dual quad
#$GPIO_BASE = 0x58020000;
#$Conf = "PB10:AF09:V, PB02:AF09:V, PD13:AF09:V, PE02:AF09:V, PD12:AF09:V, PD11:AF09:V, "
#      . "PC11:AF09:V, PE10:AF10:V, PD06:AF10:V, PE08:AF10:V, PE07:AF10:V";
# w/ cmspi
#$Conf = "PB10:PPUP:M, PB02:PPUP:V, PD13:INPUP:V, PE02:INPUP:V, PD12:INPUP:V, PD11:INPUP:V";
#$Conf = "PC11:PPUP:M, PB02:PPUP:V, PE10:INPUP:V, PD06:INPUP:V, PE08:INPUP:V, PE07:INPUP:V";

# nucleo-l4r5zi one dual quad single NCS
#$GPIO_BASE = 0x48000000;
#$Conf = "PA02:AF10:V, PE10:AF10:V, PD07:AF10:V, PD06:AF10:V, PD05:AF10:V, PD04:AF10:V, "
#      . "PE15:AF10:V, PE14:AF10:V, PE13:AF10:V, PE12:AF10:V";
# w/ cmspi
#$Conf = "PA02:PPUP:M,  PE10:PPUP:V, PD07:INPDO:V, PD06:INPDO:V, PD05:INPDO:V, PD04:INPDO:V";
#$Conf = "PA02:PPUP:M,  PE10:PPUP:V, PE15:INPDO:V, PE14:INPDO:V, PE13:INPDO:V, PE12:INPDO:V";

# nucleo-l552ze-q dual quad with single NCS
#$GPIO_BASE = 0x42020000;
#$Conf = "PA02:AF10:V, PE10:AF10:V, PD07:AF10:V, PD06:AF10:V, PD05:AF10:V, PD04:AF10:V, "
#      . "PE15:AF10:V, PE14:AF10:V, PE13:AF10:V, PE12:AF10:V";
# w/ cmspi
#$Conf = "PA02:PPUP:M,  PE10:PPUP:V, PD07:INPDO:V, PD06:INPDO:V, PD05:INPDO:V, PD04:INPDO:V";
#$Conf = "PA02:PPUP:M,  PE10:PPUP:V, PE15:INPDO:V, PE14:INPDO:V, PE13:INPDO:V, PE12:INPDO:V";

# nucleo-g071rb dual quad
#$GPIO_BASE = 0x50000000;
#$Conf = "PA00:PPUP:H, PA04:PPUP:V, PB03:INPUP:V, PA10:INPUP:V, PB11:INPUP:H, PB01:INPUP:H";
#$Conf = "PA01:PPUP:H, PA04:PPUP:V, PA08:INPUP:V, PB14:INPUP:V, PB04:INPUP:V, PB05:INPUP:V";

# nucleo-g474re dual quad with single NCS
#$GPIO_BASE = 0x48000000;
#$Conf = "PB11:AF10:H, PB10:AF10:V, PA06:AF10:V, PA07:AF10:V, PB00:AF10:V, PB01:AF10:V, "
#      . "PC04:AF10:V, PC03:AF10:V, PC02:AF10:V, PC01:AF10:V";
# w/ cmspi
#$Conf = "PB11:PPUP:H, PB10:PPUP:V, PA06:INPUP:V, PA07:INPUP:V, PB00:INPUP:V, PB01:INPUP:V";
#$Conf = "PB11:PPUP:H, PB10:PPUP:V, PC04:INPUP:V, PC03:INPUP:V, PC02:INPUP:V, PC01:INPUP:V";

# stm32h745i-disco dual quad with single NCS
#$GPIO_BASE = 0x58020000;
#$Conf = "PG06:AF10:H, PF10:AF09:V, PF06:AF09:V, PF07:AF09:V, PF09:AF10:V, PD11:AF09:V, "
#      . "PG14:AF09:H, PG09:AF09:V, PH03:AF09:V, PH02:AF09:V";

# stm32h747i-disco dual quad with single NCS
#GPIO_BASE = 0x58020000;
#$Conf = "PG06:AF10:H, PB02:AF09:V, PF06:AF09:V, PF07:AF09:V, PF09:AF10:V, PD11:AF09:V, "
#      . "PG14:AF09:H, PG09:AF09:V, PH03:AF09:V, PH02:AF09:V";

# stm32h7b3i-disco octal
#$GPIO_BASE = 0x58020000;
#$Conf = "PG06:AF10:V, PB02:AF09:V, PC05:AF10:V, PD07:AF10:V, PG09:AF09:V, PH03:AF09:V, PC01:AF10:V, "
#      . "PF06:AF10:V, PF07:AF10:V, PF09:AF10:V, PD11:AF09:V";

# stm32h735g-disco octal
#$GPIO_BASE = 0x58020000;
#$Conf = "PG06:AF10:V, PF10:AF09:V, PB02:AF10:V, PD07:AF10:V, PG09:AF09:V, PD05:AF10:V, PD04:AF10:V, "
#      . "PD13:AF09:V, PE02:AF09:V, PD12:AF09:V, PD11:AF09:V";

# stm32l562e-disco octal
#$GPIO_BASE = 0x42020000;
#$Conf = "PA02:AF10:V, PA03:AF10:V, PB02:AF10:V, PC00:AF03:V, PC03:AF10:V, PC02:AF10:V, PC01:AF10:V, "
#      . "PA06:AF10:V, PA07:AF10:V, PB00:AF10:V, PB01:AF10:V";

&getopts('b:c:f:t');
if ($Getopt::Std::opt_b eq '')
{
	if ($GPIO_BASE eq '')
	{
		die("usage: $0 [ -1 ] -b io_base [ -c port_configuration ] [ -f conf_file ]");
	}
}
else
{
	$GPIO_BASE = eval $Getopt::Std::opt_b;
}

if ($Getopt::Std::opt_c eq '')
{
	if (($Conf eq '') && ($Getopt::Std::opt_f eq ''))
	{
		die("usage: $0 [ -b io_base ] ( -c port_configuration | -f conf_file )");
	}
}#
else
{
	$Conf = $Getopt::Std::opt_c . ',';
}

$STM32F1 = $Getopt::Std::opt_t;

my $Sep = "\t";
my $Form = "${Sep}mmw 0x%08X 0x%08X 0x%08X\t;# ";

my $GPIO_OFFS;
my $GPIO_CRL;
my $GPIO_CRH;
my $GPIO_MODER;
my $GPIO_OTYPER;
my $GPIO_OSPEEDR;
my $GPIO_PUPDR;
my $GPIO_IDR;
my $GPIO_ODR;
my $GPIO_AFRL;
my $GPIO_AFRH;

if ($STM32F1)
{
	# offsets for F1 devices
	$GPIO_OFFS = 0x400;
	$GPIO_CRL = 0x00;
	$GPIO_CRH = 0x04;
	$GPIO_IDR = 0x08;
	$GPIO_ODR = 0x0C;
}
else
{
	# these offsets are identical on all F0, F4, F7, H7, L4, L4+ devices up to now
	$GPIO_OFFS = 0x400;
	$GPIO_MODER = 0x00;
	$GPIO_OTYPER = 0x04;
	$GPIO_OSPEEDR = 0x08;
	$GPIO_PUPDR = 0x0C;
	$GPIO_IDR = 0x10;
	$GPIO_ODR = 0x14;
	$GPIO_AFRL = 0x20;
	$GPIO_AFRH = 0x24;
}

my @Out = ( { }, { }, { }, { }, { }, { }, { }, { }, { }, { }, { } );
my @Port = ( );
my $Exor;
my %Conf;
my $Pins = "${Sep}#";

my $pins;
my $altn;
my %defs;

if ($Getopt::Std::opt_f ne '')
{
	open(CONF_FILE, '<', $Getopt::Std::opt_f) || die("can't open $Getopt::Std::opt_f");
	while (my $line = <CONF_FILE>)
	{
		if ($line =~ /^\s*#define\s+.?(QSPI|QUAD_?SPI|OCTOSPI[^_]*)\w+_(Port|Pin)\s/)
		{
			if ($line =~ /#define\s+(\w+)\s+(\w+)/)
			{
				$defs{$1} = $2;
			}
			else
			{
				die($line);
			}
		}
		elsif ($line =~ /^\s*(P[A-Z])([0-9]+)\s*-+>\s+.?(QSPI|QUAD_?SPI|OCTO_?SPI[^_]*)_(\w+)/)
		{
			$Conf{$4} = sprintf("%s%02d", $1, $2);
		}
		elsif ($line =~ /^\s*GPIO_InitStruct.Pin\s*=\s*([^;]+\w)/)
		{
			$pins = $1;
			while ($line !~ /;/)
			{
				$line = <CONF_FILE>;
				$line =~ /^\s*([^;]+\w)/;
				$pins .= $1;
			}
		}
		elsif ($line =~ /^\s*GPIO_InitStruct.Alternate\s*=\s*GPIO_AF([0-9]+)/)
		{
			$altn = $1;
		}
		elsif ($line =~ /^\s*HAL_GPIO_Init\s*\(\s*(\w+)\s*,/)
		{
			my $port = $1;
			if ($port =~ /GPIO([A-Z])/)
			{
				$port = $1;
			}
			elsif (exists($defs{$port}))
			{
				$defs{$port} =~ /GPIO([A-Z])/;
				$port = $1;
			}
			else
			{
				printf("\n");
				next;
			}
			my @pin = split(/\s*\|\s*/, $pins);
			foreach my $pin (@pin)
			{
				my $bit;
				if (exists($defs{$pin}))
				{
					$defs{$pin} =~ /GPIO_PIN_([0-9]+)/;
					$bit = $1;
				}
				else
				{
					$pin =~ /GPIO_PIN_([0-9]+)/;
					$bit = $1;
				}
				$Conf .= sprintf("P%s%02d:AF%02d:V, ", $port, $bit, $altn);
			}
			$pins = '';
			$altn = 0;
		}
	}
	close(CONF_FILE);
}
else
{
	my @names = ( );
	my @conf = split(/\s*,\s*/, $Conf);

	if (@conf == 2)
	{
		push(@names, 'SDA', 'SCL');
	} else {
		if (@conf == 3)
		{
			push(@names, 'NCS', 'CLK', 'IO0/DIO');
		}
		elsif (@conf == 4)
		{
			push(@names, 'NCS', 'CLK','IO1/MISO', 'IO0/MOSI');
		}
		elsif (@conf == 6)
		{
			push(@names, 'NCS', 'CLK', 'IO3/NHOLD', 'IO2/NWP', 'IO1/MISO', 'IO0/MOSI');
		}
		elsif (@conf == 10)
		{
			push(@names, 'NCS', 'CLK', 'BK_1_IO3/NHOLD', 'BK1_IO2/NWP', 'BK1_IO1/MISO', 'BK1_IO0/MOSI');
			push(@names, 'BK_2_IO3/NHOLD', 'BK2_IO2/NWP', 'BK2_IO1/MISO', 'BK2_IO0/MOSI');
		}
		elsif (@conf == 11)
		{
			push(@names, 'BK_1_NCS', 'CLK', 'BK_1_IO3/NHOLD', 'BK1_IO2/NWP', 'BK1_IO1/MISO', 'BK1_IO0/MOSI');
			push(@names, 'BK_2_NCS', 'BK_2_IO3/NHOLD', 'BK2_IO2/NWP', 'BK2_IO1/MISO', 'BK2_IO0/MOSI');
		}
		else
		{
			die("invalid config");
		}
	}

	for (my $index = 0; $index < @conf; $index++)
	{
		uc($conf[$index]) =~ /^P([A-K])([0-9]+):\s*([A-Z0-9]+):(L|M|H|V)$/;
		$Pins .= sprintf(" %s: P%s%02d,", $names[$index], $1, $2);
	}
	chop($Pins);
}

if (exists $Conf{'BK1_IO0'})
{
	# QuadSPI on F4, F7, H7
	my $line;
	for my $i ('NCS', 'BK1_NCS', 'CLK', 'BK1_IO3', 'BK1_IO2', 'BK1_IO1', 'BK1_IO0')
	{
		(exists $Conf{$i}) && ($Pins .= sprintf(" %s: %s,", $Conf{$i}, $i));
	}
}

if (exists $Conf{'BK2_IO0'})
{
	# QuadSPI on F4, F7, H7
	my $line;
	for my $i ('NCS', 'BK2_NCS', 'CLK', 'BK2_IO3', 'BK2_IO2', 'BK2_IO1', 'BK2_IO0')
	{
		(exists $Conf{$i}) && ($Pins .= sprintf(" %s: %s,", $Conf{$i}, $i));
	}
}

if (exists $Conf{'P1_IO0'})
{
	# OctoSPI on L4+, L5, H7
	my $line;
	for my $i ('P1_NCS', 'P1_CLK', 'P1_DQS', 'P1_IO7', 'P1_IO6', 'P1_IO5', 'P1_IO4',
			   'P1_IO3', 'P1_IO2', 'P1_IO1', 'P1_IO0')
	{
		(exists $Conf{$i}) && ($Pins .= sprintf(" %s: %s,", $Conf{$i}, $i));
	}
}

if (exists $Conf{'P2_IO0'})
{
	# OctoSPI on L4+, H7
	my $line;
	for my $i ('P2_NCS', 'P2_CLK', 'P2_DQS', 'P2_IO7', 'P2_IO6', 'P2_IO5', 'P2_IO4',
			   'P2_IO3', 'P2_IO2', 'P2_IO1', 'P2_IO0')
	{
		(exists $Conf{$i}) && ($Pins .= sprintf(" %s: %s,", $Conf{$i}, $i));
	}
}

my @Col = ( );
my @conf = split(/\s*,\s*/, $Conf);

if (@conf == 3)
{
	splice(@conf, 2, 0, 'NONE', 'NONE', 'NONE');
}
elsif (@conf == 4)
{
	splice(@conf, 2, 0, 'NONE', 'NONE');
}

foreach my $line (@conf)
{
	$line = uc($line);
	$line =~ /^P([A-K])([0-9]+):\s*([A-Z0-9]+):(L|M|H|V)$/;
	my $port = $1;
	my $pin = $2;
	my $conf = $3;
	my $speed = $4;

	my $MODER = 0x0;
	my $OTYPER = 0x0;
	my $OSPEEDR = 0x0;
	my $PUPDR = 0x0;
	my $AFR = 0x0;
	my $num = ord(${port}) - ord('A');
	my $out = $Out[$num];

	(exists $$out{'DEF'}) || ($$out{'DEF'} = 0);

	if ($conf eq '')
	{
		if ($line ne 'NONE')
		{
			printf(STDERR "invalid conf %s\n", $line);
		}
		next;
	}
	elsif ($conf =~ /^AF([0-9]+)(|P|O)(|UP|DO)$/)
	{
		if ($STM32F1)
		{
			printf(STDERR "no alternate %s for F1 family\n", $line);
			next;
		}
		if (($1 < 0) || ($1 > 15))
		{
			printf(STDERR "invalid alternate %s\n", $line);
			next;
		}
		$MODER = 0x2;
		$AFR = $1;
		if ($pin <= 7)
		{
			$$out{'AFRL_H'} |= ($AFR << (${pin} << 2));
			$$out{'AFRL_L'} |= (($AFR ^ 0xF) << (${pin} << 2));
		}
		else
		{
			$$out{'AFRH_H'} |= ($AFR << ((${pin} - 8) << 2));
			$$out{'AFRH_L'} |= (($AFR ^ 0xF) << ((${pin} - 8) << 2));
		}
		if ($2 ne '') {
			$OTYPER = ($1 eq 'O') ? 0x1 : 0x0;
			$$out{'OTYPER_H'} |= ($OTYPER << $pin);
			$$out{'OTYPER_L'} |= (($OTYPER ^ 0x1) << $pin);
		}
		$PUPDR = ($3 eq 'UP') ? 0x1 : (($3 eq 'DO') ? 0x2 : 0x0);
		$$out{'PUPDR_H'} |= ($PUPDR << (${pin} << 1));
		$$out{'PUPDR_L'} |= (($PUPDR ^0x3) << (${pin} << 1));
		$conf = sprintf("AF%02d%s%s", $AFR, $2, $3);
	}
	elsif ($conf =~ /^IN(|P|O)(|UP|DO)$/)
	{
		if ($STM32F1)
		{
			$MODER = ($1 eq '') ? 0x4 : 0x8;
			($2 eq 'UP') && ($$out{'PUPDR_H'} |= (1 << ${pin}));
			($2 eq 'DO') && ($$out{'PUPDR_L'} |= (1 << ${pin}));
		}
		else
		{
			$MODER = 0x0;
			if ($1 ne '')
			{
				$OTYPER = ($1 eq 'O') ? 0x1 : 0x0;
				$$out{'OTYPER_H'} |= ($OTYPER << $pin);
				$$out{'OTYPER_L'} |= (($OTYPER ^ 0x1) << $pin);
			}
			$PUPDR = ($2 eq 'UP') ? 0x1 : (($2 eq 'DO') ? 0x2 : 0x0);
			$$out{'PUPDR_H'} |= ($PUPDR << (${pin} << 1));
			$$out{'PUPDR_L'} |= (($PUPDR ^0x3) << (${pin} << 1));
		}
		($2 eq 'UP') && ($$out{'ODR_H'} |= (1 << ${pin}));
		($2 eq 'DO') && ($$out{'ODR_L'} |= (1 << ${pin}));
	}
	elsif ($conf =~ /^P(P|O)(|UP|DO)$/)
	{
		if ($STM32F1)
		{
			$MODER = ($1 eq 'O') ? 0x4 : 0x0;
			$MODER |= (($speed eq 'V') ? 0x03 : (($speed eq 'L') ? 0x2 : 0x1));
			if ($2 ne '')
			{
				printf(STDERR "WARNING: no output w/ pull-up/pull-down for F1 family %s\n", $line);
			}
		}
		else
		{
			$MODER = 0x1;
			$OTYPER = ($1 eq 'O') ? 0x1 : 0x0;
			$$out{'OTYPER_H'} |= ($OTYPER << $pin);
			$$out{'OTYPER_L'} |= (($OTYPER ^ 0x1) << $pin);
			$PUPDR = ($2 eq 'UP') ? 0x1 : (($2 eq 'DO') ? 0x2 : 0x0);
			$$out{'PUPDR_H'} |= ($PUPDR << ($pin << 1));
			$$out{'PUPDR_L'} |= (($PUPDR ^ 0x3) << ($pin << 1));
		}
		($2 eq 'UP') && ($$out{'ODR_H'} |= (1 << ${pin}));
		($2 eq 'DO') && ($$out{'ODR_L'} |= (1 << ${pin}));
	}
	else
	{
		printf(STDERR "invalid conf %s\n", $line);
		next;
	}

	if ($$out{'DEF'} & (1<< ${pin}))
	{
		printf(STDERR "redefinition: %s\n", $line);
	}

	if ($STM32F1)
	{
		if ($pin >= 8)
		{
			$$out{'CRH_H'} |= ($MODER << (($pin & 0x7) << 2));
			$$out{'CRH_L'} |= (($MODER ^ 0xF) << (($pin & 0x7) << 2));
		}
		else
		{
			$$out{'CRL_H'} |= ($MODER << (($pin & 0x7) << 2));
			$$out{'CRL_L'} |= (($MODER ^ 0xF) << (($pin & 0x7) << 2));
		}

		$Exor = sprintf("0x%08X %2d", ${GPIO_BASE} + (ord($port)  - ord('A')) * ${GPIO_OFFS} + ${GPIO_ODR}, $pin);
		my $exor = 0xB << (($pin & 0x7) << 2);
		(($MODER & 0x3) == 0x0) && ($Exor .= sprintf(" 0x%03X 0x%03X 0x%08X",
			((($pin >= 8) ? ${GPIO_CRH} : ${GPIO_CRL})-${GPIO_ODR}) & 0x3FF,
			((($pin >= 8) ? ${GPIO_CRH} : ${GPIO_CRL})-${GPIO_ODR}) & 0x3FF, $exor));
	}
	else
	{
		$$out{'DEF'} |= (1 << ${pin});
		$$out{'MODER_H'} |= ($MODER << (${pin} << 1));
		$$out{'MODER_L'} |= (($MODER ^ 0x3) << (${pin} << 1));

		$OSPEEDR = (($speed eq 'V') ? 0x3 : (($speed eq 'H') ? 0x2 : (($speed eq 'M') ? 0x1 : 0x0)));
		$$out{'OSPEEDR_H'} |= ($OSPEEDR << (${pin} << 1));
		$$out{'OSPEEDR_L'} |= (($OSPEEDR ^ 0x3) << (${pin} << 1));

		$Exor = sprintf("0x%08X %2d", ${GPIO_BASE} + (ord($port)  - ord('A')) * ${GPIO_OFFS} + ${GPIO_ODR}, $pin);
		my $exor = (0x1 << ($pin << 1));
		($MODER == 0x0) && ($Exor .= sprintf(" 0x%03X 0x%03X 0x%08X", (${GPIO_MODER}-${GPIO_ODR}) & 0x3FF,
			(${GPIO_MODER}-${GPIO_ODR}) & 0x3FF, $exor));
	}

	push(@{$Port[$num]}, sprintf("P%s%02d:%s:%s", $port, $pin, $conf, $speed));
	push(@Col, $Exor);
}

my $Col = sprintf("${Sep}0x%03X ", (${GPIO_IDR}-${GPIO_ODR}) & 0x3FF);
for (my $i = 0; $i < @Col; $i++)
{
	if (($i != 0) && (($i % 2) == 0))
	{
		(($i + 1) < @Col) && ($Col .= "\\\n${Sep}");
	}
	$Col .= sprintf("%s ", $Col[$i]);
}
printf("%s\n", $Col);

my @Col = ( );
my $Set;
for (my $i = 0; $i < @Out; $i++)
{
	my $out = $Out[$i];
	my $addr = ${GPIO_BASE} + $i * ${GPIO_OFFS};
	my $count = 0;

	if ($STM32F1)
	{
		if (($$out{'CRH_H'} | $$out{'CRH_L'} | $$out{'CRL_H'} | $$out{'CRL_L'} |
				$$out{'PUPDR_H'} | $$out{'PUPDR_L'}) != 0)
		{
			push(@Col, sort({ $b cmp $a } @{$Port[$i]}));

			$Set .= sprintf("\n%s# Port %s: %s\n", ${Sep}, chr($i + ord('A')),
				join(", ", sort({ $b cmp $a } @{$Port[$i]})));

			(($$out{'CRL_H'} | $$out{'CRL_L'}) != 0) &&
				($Set .= sprintf("${Form}CRL\n", $addr + ${GPIO_CRL}, $$out{'CRL_H'}, $$out{'CRL_L'}));

			(($$out{'CRH_H'} | $$out{'CRH_L'}) != 0) &&
				($Set .= sprintf("${Form}CRH\n", $addr + ${GPIO_CRH}, $$out{'CRH_H'}, $$out{'CRH_L'}));

			(($$out{'ODR_H'} | $$out{'ODR_L'}) != 0) &&
				($Set .= sprintf("${Form}ODR/PUPDR\n", $addr + ${GPIO_ODR}, $$out{'ODR_H'}, $$out{'ODR_L'}));
		}
	}
	else
	{
		if (($$out{'MODER_H'} | $$out{'MODER_L'} |
			$$out{'OTYPER_H'} | $$out{'OTYPER_L'} |
			$$out{'OSPEEDR_H'} | $$out{'OSPEEDR_L'} |
			$$out{'PUPDR_H'} | $$out{'PUPDR_L'} |
			$$out{'ODR_H'} | $$out{'ODR_L'} |
			$$out{'AFRL_H'} | $$out{'AFRL_L'} |
			$$out{'AFRH_H'} | $$out{'AFRH_L'}) != 0)
		{
			push(@Col, sort({ $b cmp $a } @{$Port[$i]}));

			$Set .= sprintf("%s# Port %s: %s\n", ${Sep}, chr($i + ord('A')),
				join(", ", sort({ $b cmp $a } @{$Port[$i]})));

			(($$out{'MODER_H'} | $$out{'MODER_L'}) != 0) &&
				($Set .= sprintf("${Form}MODER\n", $addr + ${GPIO_MODER}, $$out{'MODER_H'}, $$out{'MODER_L'}));

			(($$out{'OTYPER_H'} | $$out{'OTYPER_L'}) != 0) &&
				($Set .= sprintf("${Form}OTYPER\n", $addr + ${GPIO_OTYPER}, $$out{'OTYPER_H'}, $$out{'OTYPER_L'}));

			(($$out{'OSPEEDR_H'} | $$out{'OSPEEDR_L'}) != 0) &&
				($Set .= sprintf("${Form}OSPEEDR\n", $addr + ${GPIO_OSPEEDR}, $$out{'OSPEEDR_H'}, $$out{'OSPEEDR_L'}));

			(($$out{'PUPDR_H'} | $$out{'PUPDR_L'}) != 0) &&
				($Set .= sprintf("${Form}PUPDR\n", $addr + ${GPIO_PUPDR}, $$out{'PUPDR_H'}, $$out{'PUPDR_L'}));

			(($$out{'ODR_H'} | $$out{'ODR_L'}) != 0) &&
				($Set .= sprintf("${Form}ODR\n", $addr + ${GPIO_ODR}, $$out{'ODR_H'}, $$out{'ODR_L'}));

			(($$out{'AFRL_H'} | $$out{'AFRL_L'}) != 0) &&
				($Set .= sprintf("${Form}AFRL\n", $addr + ${GPIO_AFRL}, $$out{'AFRL_H'}, $$out{'AFRL_L'}));

			(($$out{'AFRH_H'} | $$out{'AFRH_L'}) != 0) &&
				($Set .= sprintf("${Form}AFRH\n", $addr + ${GPIO_AFRH}, $$out{'AFRH_H'}, $$out{'AFRH_L'}));
		}
	}
}

my $Col = '';
for (my $i = 0; $i < @Col; $i++)
{
	if (($i % 6) == 0)
	{
		chop($Col);
		(($i + 1) < @Col) && ($Col .= "\n${Sep}#");
	}
	$Col .= sprintf(" %s,", $Col[$i]);
}
chop($Col);
#printf("\n%s\n", $Pins);
printf("%s\n", $Col);
printf("%s\n", $Set);
