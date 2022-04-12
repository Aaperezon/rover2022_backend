import serial 
import time
import requests


lopy = serial.Serial(port='/dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_DO0037UU-if00-port0', baudrate=9600)
arduino = serial.Serial(port='/dev/serial/by-id/usb-Arduino__www.arduino.cc__0042_758303338373514130F0-if00', baudrate=9600)

        
def run():
    global lopy, arduino
    try:
        message = (arduino.readline()).decode('utf-8')
        lopy.write(message.encode('utf-8'))
        # print( message)
        requests.get("http://localhost:81/rover2022/service/createsensor.php", json=payload, timeout=.1)
        
    except KeyboardInterrupt:
        exit()
    except:
        if lopy.isOpen():
            lopy.close()
        else:
            try:
                lopy = serial.Serial(port='/dev/serial/by-id/usb-FTDI_FT230X_Basic_UART_DO0037UU-if00-port0', baudrate=9600)
            except:
                pass
        if arduino.isOpen():
            arduino.close()
        else:
            try:
                arduino = serial.Serial(port='/dev/serial/by-id/usb-Arduino__www.arduino.cc__0042_758303338373514130F0-if00', baudrate=9600)
            except:
                pass
if __name__ == '__main__':
    while True:
        run()
        # time.sleep(1)
