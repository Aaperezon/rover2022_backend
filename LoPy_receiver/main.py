from network import LoRa
import socket
from time import sleep
import machine
import pycom


# Please pick the region that matches where you are using the device:
# United States = LoRa.US915
lora = LoRa(mode=LoRa.LORA, region=LoRa.US915)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setblocking(False)

pycom.heartbeat(False)

while True:
    try:
        incomming_message = s.recv(128).decode("utf-8")  #Received through LoRa 
        if len(incomming_message) > 0:
            print(incomming_message)
            pycom.rgbled(0x00FF00) # Green
        else:
            pycom.rgbled(0xFF0000) #Red
    except:
        pycom.rgbled(0xFF0000) #Red
    
    sleep(.5)


