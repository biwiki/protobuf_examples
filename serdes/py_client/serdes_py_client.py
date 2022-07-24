#!/usr/bin/env python3

import message_pb2 as proto
import socket
import time
import os

import threading

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("127.0.0.1", 1234))
except:
    sys.exit("Failed to connect to server")

def readThread():
    while True:
        buff = s.recv(1024)
        print("readThread received data")
        pl = proto.PbMessage()
        pl.ParseFromString(buff)
        print(pl)

t = threading.Thread(target = readThread, daemon = True)
t.start()

msg = proto.PbMessage()
msg.type=proto.PbMessage.COMMAND
msg.msg="Hello"
s.send(msg.SerializeToString())
time.sleep(1)

msg.type=proto.PbMessage.USER
msg.msg="Eva"
s.send(msg.SerializeToString())
time.sleep(1)

msg.type=proto.PbMessage.COMMAND
msg.msg="Hello"
s.send(msg.SerializeToString())
time.sleep(1)

msg.type=proto.PbMessage.END
msg.msg="Eva"
s.send(msg.SerializeToString())
time.sleep(1)

s.close()
