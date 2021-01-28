# Raspberry PICO

## Build

```
scons -c
scons
```

**gcc version >= 6.x.x**

## Flash

```
./Libraries/generated/elf2uf2 rtthread-pico.elf rtthread-pico.uf2
```

- Copy the rtthread-pico.uf2 file to the "RPI-RP2" disk
- Then led blink.

## Run

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Jan 28 2021
 2006 - 2021 Copyright by rt-thread team
Hello, RT-Thread!
msh >
```

