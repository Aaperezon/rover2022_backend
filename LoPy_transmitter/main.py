from network import LoRa
import socket
import pycom
import machine
from time import sleep
uart = machine.UART(0, 9600)
os.dupterm(uart)

# Please pick the region that matches where you are using the device:
# United States or Mexico = LoRa.US915
lora = LoRa(mode=LoRa.LORA, region=LoRa.US915)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setblocking(False)
pycom.heartbeat(False)

while True:
    try:
        all_message = uart.readline()
        s.send(all_message)
        pycom.rgbled(0x00FF00)
    except:
        # print("Error with transmitter",e)
        pycom.rgbled(0xFF0000)
    sleep(.5)
