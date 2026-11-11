import serial
import time
try:
    from serial.tools.list_ports import comports
except ImportError:
    raise serial.serialutil.SerialException


test_comx = 'COM66'
test_baudrate = 2000000
test_maxsize = 10*1024*1024

test_data = '0xAA' * 4096

test_serial = serial.Serial(test_comx, test_baudrate, timeout = 1)

def test_cdc_out():
    send_count = 0
    begin = time.time()

    while True:
            if send_count < test_maxsize:
                txdatalen = test_serial.write(test_data.encode("utf-8"))
                send_count += txdatalen
            else:
                print("cdc out speed %f MB/s" %(send_count//1024//1024/(time.time() - begin)))
                break

def test_cdc_in():
    read_count = 0
    begin = time.time()

    while True:
            if read_count < test_maxsize:
                data = test_serial.read(test_maxsize).decode(encoding='utf-8',errors='ignore')
                read_count += len(data)
            else:
                print("cdc in speed %f MB/s" %(read_count//1024//1024/(time.time() - begin)))
                break

if __name__ == '__main__':
    print('test cdc out speed')

    test_serial.setDTR(0)
    test_cdc_out()

    print('test cdc in speed')
    test_serial.setDTR(1)
    test_cdc_in()