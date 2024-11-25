import socket
import time
import threading

UDP_IP = "192.168.4.1"
UDP_PORT = 1234
message = "Hello, World!"
messageBytearray = bytearray()
messageBytearray.extend(map(ord, message))

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

def send_udp():
    while True:
        sock.sendto(messageBytearray, (UDP_IP, UDP_PORT))
        print("message sent")
        time.sleep(1)

def receive_udp():
    while True:
        data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
        print("received message: %s" % data)



t1 = threading.Thread(target=send_udp)
t2 = threading.Thread(target=receive_udp)

t1.start()
t2.start()

while True:
    message = input()
    messageBytearray = bytearray()
    messageBytearray.extend(map(ord, message))
    print("UDP target IP: %s" % UDP_IP)
    print("UDP target port: %s" % UDP_PORT)
    print("message: %s" % messageBytearray)



