board: PIC32 Ethernet Starter Kit
http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1406&dDocName=en545713

Warning:
Because PIC32 Ethernet Starter Kit have no uart or other.
so,console print use DBPRINTF.
if you want to use DBPRINTF in PIC32 Ethernet Starter Kit,
you project must globl define PIC32_STARTER_KIT and debug in MPLAB.
but,if you want run app without debug mode,you must remove this features.
if not,the app can't run(loop in DBPRINTF).
