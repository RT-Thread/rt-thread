# K1 Firmware

`esos.elf` is the SpacemiT K1 RCPU firmware used by the HDMI ADMA service.
It was obtained from `/lib/firmware/esos.elf` in the vendor Bianbu Linux
image and is embedded into `rtthread.bin` by `firmware.S`.

Validated SHA-256:

```text
d643349c9705b665b7af438cf8fcd46c1af2ef743f4249155b62ead3efbd8f9f  esos.elf
```

Confirm the vendor firmware redistribution terms before upstream submission.
