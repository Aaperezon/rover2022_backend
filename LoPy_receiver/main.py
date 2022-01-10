from network import LoRa
import socket
import time
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
        incomming_message = s.recv(64).decode("utf-8")  #Received through LoRa 
        print(incomming_message)
        # m = uart.writeline()
        pycom.rgbled(0x00FF00) # Green
    except:
        # uart1.write('Hello')        Send to Arduino
        pycom.rgbled(0xFF0000) #Red
        print("Error client...")
    time.sleep(1)
    



