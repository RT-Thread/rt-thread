# Bring up LVGL demo on Nuvoton platforms

Current supported LVGL running environment on Nuvoton's boards shown in below table:

| **Board Name** | **Default demo** | **Need Expansion** | **Used Configuration filename** |
| -------------- | ------------------------------- | ---------------- | ----------- |
| numaker-iot-m487 | Widgets | Nu-TFT v1.3 | config_lvgl |
| numaker-pfm-m487 | Widgets | Advance v4 | config_lvgl |
| nk-980iot | Music | Nu-TFT v1.3 | config_lvgl |
| numaker-m2354 | Music | Nu-TFT v1.3 | config_lvgl |
| nk-n9h30 | Music | No | .config |
| numaker-m032ki | Widgets | Nu-TFT v1.3 | config_lvgl |
| numaker-m467hj | Widgets | NuMaker-TFT-LCD43 v1.0 | config_lvgl |
| numaker-iot-m467 | Widgets | Nu-TFT v1.3 | config_lvgl |
| numaker-hmi-ma35d1 | Widgets | No | .config |

## Download related packages

To execute below commands in env command-line window to download related packages for building.

```bash
# cd <path-to-rt-thread>bsp/nuvoton/<board-name>
# menuconfig --config config_lvgl
# pkgs --update
# scons
```

## Firmware programming

To program built rt-thread.bin into flash. You can refer steps in README.md in corresponding supported board folder or CN quick-start guide in rt-thread documents site.

```
<path-to-rt-thread>/bsp/nuvoton/<board-name>/README.md
```

   or

```
https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/quick-start/more
```
