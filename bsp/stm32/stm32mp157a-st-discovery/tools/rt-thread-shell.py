import os
import time

def main():
    if (os.path.exists("/tmp/RT-Thread-STM32MP1_CM4.elf")):
        os.system("mv /tmp/RT-Thread-STM32MP1_CM4.elf /lib/firmware/")
    os.system("echo stop > /sys/class/remoteproc/remoteproc0/state")
    os.system("echo RT-Thread-STM32MP1_CM4.elf > /sys/class/remoteproc/remoteproc0/firmware")
    os.system("echo start > /sys/class/remoteproc/remoteproc0/state")
    os.system("stty -onlcr -echo -F /dev/ttyRPMSG0")
    os.system("cat /dev/ttyRPMSG0 &")
    time.sleep(1)
    print("\nYou can input \"exit\" to quit rt-thread shell!\n")
    os.system("echo version >/dev/ttyRPMSG0")

    while True:
        a = input()
        if a == "exit":
           os.system("echo stop > /sys/class/remoteproc/remoteproc0/state")
           return

        os.system("echo {0} >/dev/ttyRPMSG0".format(a))


if __name__ == "__main__":
    main()
