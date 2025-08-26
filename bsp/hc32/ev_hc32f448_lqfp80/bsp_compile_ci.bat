scons --attach=devices.adc
scons -j4
scons --attach=default

scons --attach=devices.crypto
scons -j4
scons --attach=default

scons --attach=devices.dac
scons -j4
scons --attach=default

scons --attach=devices.flash
scons -j4
scons --attach=default

scons --attach=devices.gpio
scons -j4
scons --attach=default

scons --attach=devices.hwtimer
scons -j4
scons --attach=default

scons --attach=devices.i2c
scons -j4
scons --attach=default

scons --attach=devices.input_capture
scons -j4
scons --attach=default

scons --attach=devices.mcan
scons -j4
scons --attach=default

scons --attach=devices.pm
scons -j4
scons --attach=default

scons --attach=devices.pulse_encoder_tmr6
scons -j4
scons --attach=default

scons --attach=devices.pulse_encoder_tmra
scons -j4
scons --attach=default

scons --attach=devices.pwm_tmr4
scons -j4
scons --attach=default

scons --attach=devices.pwm_tmr6
scons -j4
scons --attach=default

scons --attach=devices.pwm_tmra
scons -j4
scons --attach=default

scons --attach=devices.qspi
scons -j4
scons --attach=default

scons --attach=devices.rtc
scons -j4
scons --attach=default

scons --attach=devices.soft_i2c
scons -j4
scons --attach=default

scons --attach=devices.spi
scons -j4
scons --attach=default

scons --attach=devices.uart_v1
scons -j4
scons --attach=default

scons --attach=devices.uart_v2
scons -j4
scons --attach=default

scons --attach=devices.watchdog_swdt
scons -j4
scons --attach=default

scons --attach=devices.watchdog_wdt
scons -j4
scons --attach=default


scons --attach=peripheral.spi_flash
scons -j4
scons --attach=default
