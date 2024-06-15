# Use Env to Generate VSCode Project

## Preparation

Assume that you have install the Env environment, if not, please read these document first:

- [User Manual of Env](env.md)

## Generate VSCode Project

Go to a specific RT-Thread bsp folder, e.g. `bsp/stm32/stm32f411-st-nucleo`, and open the Env terminal under this directory.

Type `menuconfig` command to configure the BSP, and use `pkgs --update` to download and update software packages if select pacakges and didn't set automatically downloading using `menuconfig -s`.

Then, use `scons --target=vsc` command to generate the VSCode project, and use `code .` command to open the VSCode. Noted that you must execute `code .` under Env terminal to open the VSCode, please don't directly open VSCode because environment variables need to be set automatically for VSCode under Env terminal.

In the VSCode terminal, you can use `scons -j12` to compile the project or edit the project source code.
