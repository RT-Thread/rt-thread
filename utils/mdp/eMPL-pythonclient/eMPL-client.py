#!/usr/bin/python

# eMPL_client.py
# A PC application for use with Embedded MotionApps.
# Copyright 2012 InvenSense, Inc. All Rights Reserved.

import serial, sys, time, string, pygame
from ponycube import *

class eMPL_packet_reader:
    def __init__(self, port, quat_delegate=None, debug_delegate=None, data_delegate=None ):
        self.s = serial.Serial(port,115200)
        self.s.setTimeout(0.1)
        self.s.setWriteTimeout(0.2)
# TODO: Will this break anything?
            ##Client attempts to write to eMPL.
            #try:
            #self.s.write("\n")
            #except serial.serialutil.SerialTimeoutException:
            #pass # write will timeout if umpl app is already started.

        if quat_delegate:
            self.quat_delegate = quat_delegate
        else:
            self.quat_delegate = empty_packet_delegate()

        if debug_delegate:
            self.debug_delegate = debug_delegate
        else:
            self.debug_delegate = empty_packet_delegate()

        if data_delegate:
            self.data_delegate = data_delegate
        else:
            self.data_delegate = empty_packet_delegate()

        self.packets = []
        self.length = 0
        self.previous = None

    def read(self):
        NUM_BYTES = 23
        p = None
        while self.s.inWaiting() >= NUM_BYTES:
            rs = self.s.read(NUM_BYTES)
            if ord(rs[0]) == ord('$'):
                pkt_code = ord(rs[1])
                if pkt_code == 1:
                    d = debug_packet(rs)
                    self.debug_delegate.dispatch(d)
                elif pkt_code == 2:
                    p = quat_packet(rs)
                    self.quat_delegate.dispatch(p) 
                elif pkt_code == 3:
                    d = data_packet(rs)
                    self.data_delegate.dispatch(d)
                else:
                    print "no handler for pkt_code",pkt_code
            else:
                c = ' '
                print "serial misaligned!"
                while not ord(c) == ord('$'):
                    c = self.s.read(1)
                self.s.read(NUM_BYTES-1)

    def write(self,a):
        self.s.write(a)

    def close(self):
        self.s.close()

    def write_log(self,fname):
        f = open(fname,'w')
        for p in self.packets:
            f.write(p.logfile_line())
        f.close()

# ===========  PACKET DELEGATES  ==========

class packet_delegate(object):
    def loop(self,event):
        print "generic packet_delegate loop w/event",event
    def dispatch(self,p):
        print "generic packet_delegate dispatched",p

class empty_packet_delegate(packet_delegate):
    def loop(self,event):
        pass
    def dispatch(self,p):
        pass

class cube_packet_viewer (packet_delegate):
    def __init__(self):
        self.screen = Screen(480,400,scale=1.5)
        self.cube = Cube(30,60,10)
        self.q = Quaternion(1,0,0,0)
        self.previous = None  # previous quaternion
        self.latest = None    # latest packet (get in dispatch, use in loop)

    def loop(self,event):
        packet = self.latest
        if packet:
            q = packet.to_q().normalized()
            self.cube.erase(self.screen)
            self.cube.draw(self.screen,q)
            pygame.display.flip()
            self.latest = None

    def dispatch(self,p):
        if isinstance(p,quat_packet):
            self.latest = p

class debug_packet_viewer (packet_delegate):
    def loop(self,event):
        pass
    def dispatch(self,p):
        assert isinstance(p,debug_packet);
        p.display()

class data_packet_viewer (packet_delegate):
    def loop(self,event):
        pass
    def dispatch(self,p):
        assert isinstance(p,data_packet);
        p.display()

# =============== PACKETS ================= 

# For 16-bit signed integers.
def two_bytes(d1,d2):
    d = ord(d1)*256 + ord(d2)
    if d > 32767:
        d -= 65536
    return d

# For 32-bit signed integers.
def four_bytes(d1, d2, d3, d4):
    d = ord(d1)*(1<<24) + ord(d2)*(1<<16) + ord(d3)*(1<<8) + ord(d4)
    if d > 2147483648:
        d-= 4294967296
    return d

class debug_packet (object):
    # body of packet is a debug string
    def __init__(self,l):
        sss = []
        for c in l[3:21]:
            if ord(c) != 0:
                sss.append(c)
        self.s = "".join(sss)

    def display(self):
        sys.stdout.write(self.s)

class data_packet (object):
    def __init__(self, l):
        self.data = [0,0,0,0,0,0,0,0,0]
        self.type = ord(l[2])
        if self.type == 0:   # accel
            self.data[0] = four_bytes(l[3],l[4],l[5],l[6]) * 1.0 / (1<<16)
            self.data[1] = four_bytes(l[7],l[8],l[9],l[10]) * 1.0 / (1<<16)
            self.data[2] = four_bytes(l[11],l[12],l[13],l[14]) * 1.0 / (1<<16)
        elif self.type == 1:   # gyro
            self.data[0] = four_bytes(l[3],l[4],l[5],l[6]) * 1.0 / (1<<16)
            self.data[1] = four_bytes(l[7],l[8],l[9],l[10]) * 1.0 / (1<<16)
            self.data[2] = four_bytes(l[11],l[12],l[13],l[14]) * 1.0 / (1<<16)
        elif self.type == 2:   # compass
            self.data[0] = four_bytes(l[3],l[4],l[5],l[6]) * 1.0 / (1<<16)
            self.data[1] = four_bytes(l[7],l[8],l[9],l[10]) * 1.0 / (1<<16)
            self.data[2] = four_bytes(l[11],l[12],l[13],l[14]) * 1.0 / (1<<16)
        elif self.type == 3:   # quat
            self.data[0] = four_bytes(l[3],l[4],l[5],l[6]) * 1.0 / (1<<30)
            self.data[1] = four_bytes(l[7],l[8],l[9],l[10]) * 1.0 / (1<<30)
            self.data[2] = four_bytes(l[11],l[12],l[13],l[14]) * 1.0 / (1<<30)
            self.data[3] = four_bytes(l[15],l[16],l[17],l[18]) * 1.0 / (1<<30)
        elif self.type == 4:   # euler
            self.data[0] = four_bytes(l[3],l[4],l[5],l[6]) * 1.0 / (1<<16)
            self.data[1] = four_bytes(l[7],l[8],l[9],l[10]) * 1.0 / (1<<16)
            self.data[2] = four_bytes(l[11],l[12],l[13],l[14]) * 1.0 / (1<<16)
        elif self.type == 5:   # rot
            self.data[0] = two_bytes(l[3],l[4]) * 1.0 / (1<<14)
            self.data[1] = two_bytes(l[5],l[6]) * 1.0 / (1<<14)
            self.data[2] = two_bytes(l[7],l[8]) * 1.0 / (1<<14)
            self.data[3] = two_bytes(l[9],l[10]) * 1.0 / (1<<14)
            self.data[4] = two_bytes(l[11],l[12]) * 1.0 / (1<<14)
            self.data[5] = two_bytes(l[13],l[14]) * 1.0 / (1<<14)
            self.data[6] = two_bytes(l[15],l[16]) * 1.0 / (1<<14)
            self.data[7] = two_bytes(l[17],l[18]) * 1.0 / (1<<14)
            self.data[8] = two_bytes(l[19],l[20]) * 1.0 / (1<<14)
        elif self.type == 6:   # heading
            self.data[0] = four_bytes(l[3],l[4],l[5],l[6]) * 1.0 / (1<<16)
        else:   # unsupported

            pass

    def display(self):
        if self.type == 0:
            print 'accel: %7.3f %7.3f %7.3f' % \
                (self.data[0], self.data[1], self.data[2])
        elif self.type == 1:
            print 'gyro: %9.5f %9.5f %9.5f' % \
                (self.data[0], self.data[1], self.data[2])
        elif self.type == 2:
            print 'compass: %7.4f %7.4f %7.4f' % \
                (self.data[0], self.data[1], self.data[2])
        elif self.type == 3:
            print 'quat: %7.4f %7.4f %7.4f %7.4f' % \
                (self.data[0], self.data[1], self.data[2], self.data[3])
        elif self.type == 4:
            print 'euler: %7.4f %7.4f %7.4f' % \
                (self.data[0], self.data[1], self.data[2])
        elif self.type == 5:
            print 'rotation matrix: \n%7.3f %7.3f %7.3f\n%7.3f %7.3f %7.3f\n%7.3f %7.3f %7.3f' % \
                (self.data[0], self.data[1], self.data[2], self.data[3], \
                 self.data[4], self.data[5], self.data[6], self.data[7], \
                 self.data[8])
        elif self.type == 6:
            print 'heading: %7.4f' % self.data[0]
        else:
            print 'what?'

class quat_packet (object):
    def __init__(self, l):
        self.l = l
        self.q0 = four_bytes(l[3],l[4],l[5],l[6]) * 1.0 / (1<<30)
        self.q1 = four_bytes(l[7],l[8],l[9],l[10]) * 1.0 / (1<<30)
        self.q2 = four_bytes(l[11],l[12],l[13],l[14]) * 1.0 / (1<<30)
        self.q3 = four_bytes(l[15],l[16],l[17],l[18]) * 1.0 / (1<<30)
    def display_raw(self):
        l = self.l
        print "".join(
            [ str(ord(l[0])), " "] + \
            [ str(ord(l[1])), " "] + \
            [ str(ord(a)).ljust(4) for a in 
                                [ l[2], l[3], l[4], l[5], l[6], l[7], l[8], l[9], l[10] ] ] + \
            [ str(ord(a)).ljust(4) for a in 
                                [ l[8], l[9], l[10] , l[11], l[12], l[13]] ]
            )

    def display(self):
        if 1:
            print "qs " + " ".join([str(s).ljust(15) for s in
                [ self.q0, self.q1, self.q2, self.q3 ]])
        if 0:
            euler0, euler1, euler2 = self.to_q().get_euler()
            print "eulers " + " ".join([str(s).ljust(15) for s in
                [ euler0, euler1, euler2 ]])
        if 0:
            euler0, euler1, euler2 = self.to_q().get_euler()
            print "eulers " + " ".join([str(s).ljust(15) for s in
                [ (euler0 * 180.0 / 3.14159) - 90 ]])

    def to_q(self):
        return Quaternion(self.q0, self.q1, self.q2, self.q3)

# =============== MAIN ======================

if __name__ == "__main__":
    if len(sys.argv) == 2:
        comport = int(sys.argv[1]) - 1
    else:
        print "usage: " + sys.argv[0] + " port"
        sys.exit(-1)

    pygame.init()
    viewer = cube_packet_viewer()
    debug  = debug_packet_viewer()
    data   = data_packet_viewer()

    reader = eMPL_packet_reader(comport, 
                quat_delegate = viewer, 
                debug_delegate = debug, 
                data_delegate = data)

    while 1:
        event = pygame.event.poll()
        # TODO: Allow exit via keystroke.
        if event.type == pygame.QUIT:
            viewer.close()
            break
        if event.type == pygame.KEYDOWN:
            reader.write(pygame.key.name(event.key))

        reader.read()
        viewer.loop(event)
        debug.loop(event)
        data.loop(event)

        # TODO: If system load is too high, increase this sleep time.
        pygame.time.delay(0)

