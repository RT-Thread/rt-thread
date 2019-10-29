Cypress Semiconductor
Board: CY8CKIT-062-BLE PSoC 6 BLE Pioneer Kit
Chip: CY8C6347BZI-BLD53
Tool: PSoC Creator 4.2

Connection:
1, use Type-C cable to connect CY8CKIT-062-BLE board to PC.
2, click CY8C6347BZI.cywrk to open the project
3, build and program it into the PSoC6 MCU device.
4, open a serial port communication program, Configure the terminal with baud rate of 115200, data bits of 8, stop bits of 1, and with parity and flow control set to none.
5, Press the SW1 switch on the kit.

Run Result:

 \ | /
- RT -     Thread Operating System
 / | \     4.0.2 build Oct 29 2019
 2006 - 2019 Copyright by rt-thread team
thread1 created ok
thread1 count: 0
thread2 created ok
msh >thread1 count: 1
thread1 count: 2
thread1 count: 3