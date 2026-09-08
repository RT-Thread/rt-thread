# FRDM-MCXC162 BSP

## Overview

This BSP targets the production FRDM-MCXC162 board fitted with an
`MCXC162VFT` Cortex-M23 MCU. The core runs from the 72 MHz FRO with no FPU,
TrustZone, or MPU enabled.

The linker uses only the 64 KiB Program Flash at `0x00000000` and 12 KiB SRAM
at `0x20000000`. The non-contiguous Data Flash at `0x0001C000` is not part of
the program image.

## Supported interfaces

| RT-Thread device | Peripheral | Board pins | Default |
| --- | --- | --- | --- |
| `pin` | GPIO0-GPIO3 | `GET_PINS(port, pin)` | Enabled |
| `uart0` | LPUART0 | P0_2 RX, P0_3 TX | Enabled, console |
| `uart1` | LPUART1 | P2_12 RX, P2_13 TX | Disabled |
| `uart2` | LPUART2 | P3_13 RX, P3_12 TX | Disabled |
| `i2c0` | LPI2C0 | P3_27 SCL, P3_28 SDA | Disabled |
| `spi0` | LPSPI0 | P3_10 SCK, P3_8 SDO, P3_9 SDI, P3_11 software CS | Disabled |
| `rtc` | RTC0 | Internal | Disabled |
| `wdt` | WWDT0 | Internal | Disabled |
| `timer0`, `timer1` | CTIMER0, CTIMER1 | Internal | Disabled |
| `pwm0` channel 0/1 | FLEXPWM0 SM0 A/B | P3_0, P3_1 | Disabled |

The two PWM channels share one period. Changing the period while the other
channel is enabled returns `-RT_EINVAL`.

UART3, LPADC0, DMA, Data Flash, TRDC, low-power modes, and tickless operation
are outside this BSP version.

## Build

Install or update the NXP MCX CMSIS and series packages first:

```console
pkgs --update
```

Set `RTT_EXEC_PATH` to the compiler binary directory, then build:

```console
set RTT_CC=gcc
set RTT_EXEC_PATH=C:\path\to\arm-none-eabi\bin
scons -j8
```

The primary GCC baseline is Arm GNU Toolchain 14.2 from MCUXpresso IDE 25.06.
GCC 10.3.1 is retained as a compatibility build. Keil MDK 5.43a with
`MCXC162_DFP 26.06.00` and IAR EWARM 9.70.4 are the SDK 26.06 reference
versions.

The final generated projects are verified with Keil MDK 5.42 and Arm Compiler
6.23, and with IAR EWARM 9.60.3.422. The SDK reference Keil 5.43a and IAR
9.70.4 versions have not been repeated locally.

Project files can be regenerated with:

```console
set RTT_CC=keil
scons --target=mdk5
set RTT_CC=iar
scons --target=iar
```

Build the generated `project.uvprojx` with `uVision.com` and `project.ewp` with
`IarBuild.exe`; the `template.*` files are generator inputs, not build targets.

```console
uVision.com -b project.uvprojx -j0
IarBuild.exe project.ewp -build Debug
```

## Default behavior

The default configuration provides a 1 kHz system tick and a 115200-8-N-1
`uart0` console with MSH. The active-low red LED on P2_3 toggles every 500 ms.
No periodic application log is emitted.

Run `button_irq_test`, then press both SW2 and SW3 during its 10-second window.
It must report non-zero falling-edge interrupt counts for both buttons. The wait
also provides a simple observable check of the 1 kHz RT-Thread tick.
Run `reboot` and confirm that the banner and MSH prompt return after a software
reset; use the RESET button for the matching hardware-reset check.

The validation commands below are compiled only when their corresponding
optional BSP driver is enabled. They add no code to the default PIN + UART0
image.

Build the two CI validation configurations with:

```console
scons --attach=peripheral.communication
scons -j8
scons --attach=default
scons --attach=peripheral.timing_control
scons -j8
scons --attach=default
```

## Peripheral validation commands

Use `uart0` for the MSH console while testing the other UARTs.

| Test | Wiring | Command | Pass criterion |
| --- | --- | --- | --- |
| UART1 | Jumper Arduino D1/P2_13 TX to D0/P2_12 RX | `uart_loop uart1` | `PASS` after an 8-byte 115200-8-N-1 loopback |
| UART2 | Jumper mikroBUS TX/P3_12 to RX/P3_13 | `uart_loop uart2` | `PASS` after an 8-byte 115200-8-N-1 loopback |
| P3T1755 | None; the sensor is already connected to P3_27 SCL and P3_28 SDA | `p3t1755` | Address `0x48` acknowledges and one temperature is printed |
| SPI0 | Jumper Arduino D11/P3_8 SDO to D12/P3_9 SDI; probe D13/P3_10 SCK and D10/P3_11 CS | `spi_loop` | `PASS`; the analyzer also shows mode 0, 1 MHz SCK, and active-low CS |
| CTIMER0 | None | `ctimer0_test` | The RT-Thread clock-time backend reports one 100 ms one-shot completion |
| CTIMER1 | None | `ctimer_test timer1 oneshot`, then `ctimer_test timer1 periodic` | One interrupt, then 4-6 interrupts in 550 ms |

`timer0` is opened exclusively by the RT-Thread clock-time subsystem and must
not be opened or controlled as a regular timer device. Use `timer1` for direct
one-shot and periodic device tests.

P3_11 is driven as the RT-Thread software chip select. LPSPI uses an unrouted
internal PCS, so P3_11 remains asserted across compound SPI messages. This BSP
supports active-low software chip select only.

`p3t1755` sends the temperature-register pointer and the two-byte read as one
two-message transaction. The bus therefore emits a repeated START, as required
by ERR053261.

The v1 I2C adapter requires each `rt_i2c_transfer()` call to begin with START
and end with STOP. A first-message `RT_I2C_NO_START` or final-message
`RT_I2C_NO_STOP` request is rejected. `RT_I2C_NO_START` is accepted only when
joining consecutive writes to the same addressed slave.

WWDT tests must be run separately after each reset. `wwdt refresh` starts a
3-second watchdog and refreshes it once per second without periodic output; let
it run for at least 10 seconds and press RESET to end the test. `wwdt timeout`
does not refresh the watchdog: the MCU must reset in about 3 seconds, and the
next boot must report `last reset was caused by WWDT0`.

RTC set/get and PWM control reuse the standard MSH commands:

```console
date 2026 9 3 12 0 0
date
rtc_alarm_test

pwm probe pwm0
pwm set 0 1000000 250000
pwm enable 0
pwm set 1 1000000 500000
pwm enable 1
pwm get 0
pwm get 1
pwm disable 0
pwm disable 1
```

`rtc_alarm_test` requires `RT_USING_ALARM` and must report `PASS` after about
3 seconds. For PWM, probe Arduino D5/P3_0 (channel 0) and D6/P3_1 (channel 1)
against GND; expect 1 kHz at 25% and 50% duty respectively. While channel 0 is
enabled, `pwm set 1 2000000 1000000` must return `-RT_EINVAL` and must not
change the shared 1 ms period.

## Hardware validation

The following checks have been completed on a production FRDM-MCXC162 Rev 1:

- banner, MSH, red LED, SW2 P3_14 and SW3 P3_29 interrupts, reset behavior,
  1 kHz tick, and a 10-minute run;
- UART1/UART2 loopback;
- the onboard P3T1755 at address `0x48` and temperature reads on `i2c0`;
- SPI0 SDO-to-SDI loopback, including SCK and CS;
- RTC time/alarm, WWDT refresh and timeout reset, CTIMER one-shot/periodic,
  and PWM frequency, duty, start/stop, and shared-period rejection;
- download, startup, tick, console, and GPIO with both Keil and IAR.

For MCXC162 erratum ERR053261, do not issue consecutive LPI2C read commands
without a STOP/START or repeated START between them.

Board programming and the MCUXpresso IDE debug configuration are performed by
the board owner.

## References

- [FRDM-MCXC162 board](https://www.nxp.com/design/design-center/development-boards-and-designs/FRDM-MCXC162)
- [MCXC162 data sheet](https://www.nxp.com/docs/en/data-sheet/MCXCP048M072F20.pdf)
- [MCXC162 errata](https://www.nxp.com/docs/en/errata/MCXC162VFT_0P18R.pdf)
- [NXP MCXC162 device files](https://github.com/nxp-mcuxpresso/mcux-devices-mcx/tree/main/MCXC/MCXC162)
- [MCUX SDK 26.06 release notes](https://docs.mcuxpresso.nxp.com/mcuxsdk/26.06.00/html/boards/MCX/frdmmcxc162/releaseNotes/rnindex.html)
