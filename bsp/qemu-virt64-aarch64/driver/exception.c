#include <stdint.h>
#include <rtthread.h>

void process_exception(unsigned int num, unsigned long esr, unsigned long epc) {
	uint8_t ec;
	uint32_t iss;
	uint64_t fault_addr;
	rt_kprintf("\nexception %d\n", num);
	ec = (unsigned char)((esr>>26)&0x3f);
	iss = (unsigned int )(esr&0x00ffffff);
	rt_kprintf("esr.EC :0x%02x\n", ec);
	rt_kprintf("esr.IL :0x%02x\n", (unsigned char)((esr>>25)&0x01));
	rt_kprintf("esr.ISS:0x%08x\n", iss);
	rt_kprintf("epc    :0x%016llx\n", epc);
	switch (ec) {
		case 0x00:
			rt_kprintf("exceptions with an unknow reason\n");
			break;

		case 0x01:
			rt_kprintf("exceptions from an WFI or WFE instruction\n");
			break;

		case 0x03:
		case 0x05:
			rt_kprintf("exceptions from an MCR or MRC access\n");
			break;

		case 0x04:
			rt_kprintf("exceptions from an MCRR or MRRC access\n");
			break;

		case 0x06:
			rt_kprintf("exceptions from an LDC or STC access to CP14\n");
			break;

		case 0x07:
			rt_kprintf("exceptions from an"); 
			break;

		case 0x25:
			rt_kprintf("data abort\n");
			__asm__ volatile ("mrs %0, far_el1":"=r"(fault_addr));
			rt_kprintf("fault addr = 0x%016llx\n", fault_addr);
			if (iss & 0x40) {
				rt_kprintf("abort caused by write instruction\n");
			} else {
				rt_kprintf("abort caused by read instruction\n");
			}
			switch (iss & 0x3f) {
				case 0b000000:
					rt_kprintf("Address size fault, zeroth level of translation or translation table base register\n");
					break;

				case 0b000001:
					rt_kprintf("Address size fault, first level\n");
					break;

				case 0b000010:
					rt_kprintf("Address size fault, second level\n");
					break;

				case 0b000011:
					rt_kprintf("Address size fault, third level\n");
					break;

				case 0b000100:
					rt_kprintf("Translation fault, zeroth level\n");
					break;

				case 0b000101:
					rt_kprintf("Translation fault, first level\n");
					break;

				case 0b000110:
					rt_kprintf("Translation fault, second level\n");
					break;

				case 0b000111:
					rt_kprintf("Translation fault, third level\n");
					break;

				case 0b001001:
					rt_kprintf("Access flag fault, first level\n");
					break;

				case 0b001010:
					rt_kprintf("Access flag fault, second level\n");
					break;

				case 0b001011:
					rt_kprintf("Access flag fault, third level\n");
					break;

				case 0b001101:
					rt_kprintf("Permission fault, first level\n");
					break;

				case 0b001110:
					rt_kprintf("Permission fault, second level\n");
					break;

				case 0b001111:
					rt_kprintf("Permission fault, third level\n");
					break;

				case 0b010000:
                    {
                        uint32_t val;
                        __asm__ volatile ("mrs %0, sctlr_el1":"=r"(val));
                        rt_kprintf("%p\n", val);
                    }
					rt_kprintf("Synchronous external abort, not on translation table walk\n");
					break;

				case 0b011000:
					rt_kprintf("Synchronous parity or ECC error on memory access, not on translation table walk\n");
					break;

				case 0b010100:
					rt_kprintf("Synchronous external abort on translation table walk, zeroth level\n");
					break;

				case 0b010101:
					rt_kprintf("Synchronous external abort on translation table walk, first level\n");
					break;

				case 0b010110:
					rt_kprintf("Synchronous external abort on translation table walk, second level\n");
					break;

				case 0b010111:
					rt_kprintf("Synchronous external abort on translation table walk, third level\n");
					break;

				case 0b011100:
					rt_kprintf("Synchronous parity or ECC error on memory access on translation table walk, zeroth level\n");
					break;

				case 0b011101:
					rt_kprintf("Synchronous parity or ECC error on memory access on translation table walk, first level\n");
					break;

				case 0b011110:
					rt_kprintf("Synchronous parity or ECC error on memory access on translation table walk, second level\n");
					break;

				case 0b011111:
					rt_kprintf("Synchronous parity or ECC error on memory access on translation table walk, third level\n");
					break;

				case 0b100001:
					rt_kprintf("Alignment fault\n");
					break;

				case 0b110000:
					rt_kprintf("TLB conflict abort\n");
					break;

				case 0b110100:
					rt_kprintf("IMPLEMENTATION DEFINED fault (Lockdown fault)\n");
					break;

				case 0b110101:
					rt_kprintf("IMPLEMENTATION DEFINED fault (Unsupported Exclusive access fault)\n");
					break;

				case 0b111101:
					rt_kprintf("Section Domain Fault, used only for faults reported in the PAR_EL1\n");
					break;

				case 0b111110:
					rt_kprintf("Page Domain Fault, used only for faults reported in the PAR_EL1\n");
					break;

				default:
					rt_kprintf("unknow abort\n");
					break;
			}
			break;

		default:
			rt_kprintf("other error\n");
			break;
	}
}
