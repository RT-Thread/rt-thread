# fdt示例 #

在`examples`文件夹中存放`bcm2711-rpi-4-b.dtb`和`vexpress-v2p-ca9.dtb`可供测试，如果系统可以从bootloader或其他方式获取到bsp本身的dtb，也可以通过修改示例程序进行测试

## fdt_dump
```bash
fdt_dump vexpress-v2p-ca9.dtb
```

####  示例结果 ####
```bash
/dts-v1/;

/ {
        model = "V2P-CA9";
        arm,hbi = <0x191>;
        arm,vexpress,site = <0xf>;
        compatible = "arm,vexpress,v2p-ca9", "arm,vexpress";
        interrupt-parent = <0x1>;
        #address-cells = <0x1>;
        #size-cells = <0x1>;

        chosen {
        };

        aliases {
                serial0 = "/smb@4000000/motherboard/iofpga@7,00000000/uart@9000";
                serial1 = "/smb@4000000/motherboard/iofpga@7,00000000/uart@a000";
                serial2 = "/smb@4000000/motherboard/iofpga@7,00000000/uart@b000";
                serial3 = "/smb@4000000/motherboard/iofpga@7,00000000/uart@c000";
                i2c0 = "/smb@4000000/motherboard/iofpga@7,00000000/i2c@16000";
                i2c1 = "/smb@4000000/motherboard/iofpga@7,00000000/i2c@2000";
        };

...... 省略

        hsb@e0000000 {
                compatible = "simple-bus";
                #address-cells = <0x1>;
                #size-cells = <0x1>;
                ranges = <0x0 0xe0000000 0x20000000>;
                #interrupt-cells = <0x1>;
                interrupt-map-mask = <0x0 0x3>;
                interrupt-map = <0x0 0x0 0x1 0x0 0x24 0x4 0x0 0x1 0x1 0x0 0x25 0x4 0x0 0x2 0x1 0x0 0x26 0x4 0x0 0x3 0x1 0x0 0x27 0x4>;
        };
};
```

## fdt_test
```bash
fdt_test
```

####  示例结果 ####
```bash
name = uart@9000
reg = <0x9000,0x1000>;
compatible = "arm,pl011","arm,primecell";

name = cpus
path = /cpus/cpu@0/
path = /cpus/cpu@1/
path = /cpus/cpu@2/
path = /cpus/cpu@3/

name = user1, lable = v2m:green:user1
name = user2, lable = v2m:green:user2
name = user3, lable = v2m:green:user3
name = user4, lable = v2m:green:user4
name = user5, lable = v2m:green:user5
name = user6, lable = v2m:green:user6
name = user7, lable = v2m:green:user7
name = user8, lable = v2m:green:user8

/memreserve/    0x0000000000000000 0x0000000000001000;

phandle = <0x9>
name = bt_pins
path = /soc/gpio@7e200000/bt_pins/
brcm,pins = [2d 00]
```