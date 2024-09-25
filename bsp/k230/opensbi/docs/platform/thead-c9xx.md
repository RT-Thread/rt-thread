T-HEAD C9xx Series Processors
=============================

The **C9xx** series processors are high-performance RISC-V architecture
multi-core processors with AI vector acceleration engine.

For more details, refer [T-HEAD.CN](https://www.t-head.cn/)

To build the platform-specific library and firmware images, provide the
*PLATFORM=generic* parameter to the top level `make` command.

Platform Options
----------------

The *T-HEAD C9xx* does not have any platform-specific compile options
because it use generic platform.

```
CROSS_COMPILE=riscv64-linux-gnu- PLATFORM=generic FW_PIC=y /usr/bin/make
```

The *T-HEAD C9xx* DTB provided to OpenSBI generic firmwares will usually have
"riscv,clint0", "riscv,plic0", "thead,reset-sample" compatible strings.

DTS Example1: (Single core, eg: Allwinner D1 - c906)
----------------------------------------------------

```
	cpus {
		#address-cells = <1>;
		#size-cells = <0>;
		timebase-frequency = <3000000>;
		cpu@0 {
			device_type = "cpu";
			reg = <0>;
			status = "okay";
			compatible = "riscv";
			riscv,isa = "rv64imafdcv";
			mmu-type = "riscv,sv39";
			cpu0_intc: interrupt-controller {
				#interrupt-cells = <1>;
				compatible = "riscv,cpu-intc";
				interrupt-controller;
			};
		};
	};

	soc {
		#address-cells = <2>;
		#size-cells = <2>;
		compatible = "simple-bus";
		ranges;

		reset: reset-sample {
			compatible = "thead,reset-sample";
			plic-delegate = <0x0 0x101ffffc>;
		};

		clint0: clint@14000000 {
			compatible = "riscv,clint0";
			interrupts-extended = <
				&cpu0_intc  3 &cpu0_intc  7
				>;
			reg = <0x0 0x14000000 0x0 0x04000000>;
			clint,has-no-64bit-mmio;
		};

		intc: interrupt-controller@10000000 {
			#interrupt-cells = <1>;
			compatible = "riscv,plic0";
			interrupt-controller;
			interrupts-extended = <
				&cpu0_intc  0xffffffff &cpu0_intc  9
				>;
			reg = <0x0 0x10000000 0x0 0x04000000>;
			reg-names = "control";
			riscv,max-priority = <7>;
			riscv,ndev = <200>;
		};
	}
```

DTS Example2: (Multi cores with soc reset-regs)
-----------------------------------------------

```
	cpus {
		#address-cells = <1>;
		#size-cells = <0>;
		timebase-frequency = <3000000>;
		cpu@0 {
			device_type = "cpu";
			reg = <0>;
			status = "okay";
			compatible = "riscv";
			riscv,isa = "rv64imafdc";
			mmu-type = "riscv,sv39";
			cpu0_intc: interrupt-controller {
				#interrupt-cells = <1>;
				compatible = "riscv,cpu-intc";
				interrupt-controller;
			};
		};
		cpu@1 {
			device_type = "cpu";
			reg = <1>;
			status = "fail";
			compatible = "riscv";
			riscv,isa = "rv64imafdc";
			mmu-type = "riscv,sv39";
			cpu1_intc: interrupt-controller {
				#interrupt-cells = <1>;
				compatible = "riscv,cpu-intc";
				interrupt-controller;
			};
		};
		cpu@2 {
			device_type = "cpu";
			reg = <2>;
			status = "fail";
			compatible = "riscv";
			riscv,isa = "rv64imafdc";
			mmu-type = "riscv,sv39";
			cpu2_intc: interrupt-controller {
				#interrupt-cells = <1>;
				compatible = "riscv,cpu-intc";
				interrupt-controller;
			};
		};
		cpu@3 {
			device_type = "cpu";
			reg = <3>;
			status = "fail";
			compatible = "riscv";
			riscv,isa = "rv64imafdc";
			mmu-type = "riscv,sv39";
			cpu3_intc: interrupt-controller {
				#interrupt-cells = <1>;
				compatible = "riscv,cpu-intc";
				interrupt-controller;
			};
		};
	};

	soc {
		#address-cells = <2>;
		#size-cells = <2>;
		compatible = "simple-bus";
		ranges;

		reset: reset-sample {
			compatible = "thead,reset-sample";
			plic-delegate = <0xff 0xd81ffffc>;
			entry-reg = <0xff 0xff019050>;
			entry-cnt = <4>;
			control-reg = <0xff 0xff015004>;
			control-val = <0x1c>;
			csr-copy = <0x7f3 0x7c0 0x7c1 0x7c2 0x7c3 0x7c5 0x7cc>;
		};

		clint0: clint@ffdc000000 {
			compatible = "riscv,clint0";
			interrupts-extended = <
				&cpu0_intc  3 &cpu0_intc  7
				&cpu1_intc  3 &cpu1_intc  7
				&cpu2_intc  3 &cpu2_intc  7
				&cpu3_intc  3 &cpu3_intc  7
				&cpu4_intc  3 &cpu4_intc  7
				>;
			reg = <0xff 0xdc000000 0x0 0x04000000>;
			clint,has-no-64bit-mmio;
		};

		intc: interrupt-controller@ffd8000000 {
			#interrupt-cells = <1>;
			compatible = "riscv,plic0";
			interrupt-controller;
			interrupts-extended = <
				&cpu0_intc  0xffffffff &cpu0_intc  9
				&cpu1_intc  0xffffffff &cpu1_intc  9
				&cpu2_intc  0xffffffff &cpu2_intc  9
				&cpu3_intc  0xffffffff &cpu3_intc  9
				>;
			reg = <0xff 0xd8000000 0x0 0x04000000>;
			reg-names = "control";
			riscv,max-priority = <7>;
			riscv,ndev = <80>;
		};
	}
```

DTS Example2: (Multi cores with old reset csrs)
-----------------------------------------------
```
	reset: reset-sample {
		compatible = "thead,reset-sample";
		plic-delegate = <0xff 0xd81ffffc>;
		using-csr-reset;
		csr-copy = <0x7c0 0x7c1 0x7c2 0x7c3 0x7c5 0x7cc
			    0x3b0 0x3b1 0x3b2 0x3b3
			    0x3b4 0x3b5 0x3b6 0x3b7
			    0x3a0>;
	};
```
