import serial 
import time
import requests

lopy = serial.Serial(port='COM8', baudrate=115200)
  
def getPayLoad2(message):  
    message = message.split()
    variables = {
        "vibration1": message[0], 
        "vibration2": message[1],
        "vibration3": message[2],
        "vibration4":    message[3],
        "gasCO2":       message[4],
        "humidity":        message[5],
        "pressure":       message[6],
        "altitude":         message[7],
        "temperature":    message[8],
        "weight1":    message[9],
        "weight2":    message[10],
        "gyrox":    message[11],
        "gyroy":    message[12],
        "gyroz":    message[13],
        "encoder":    message[14],
    }
    return variables
def run():
    try:
        message = (lopy.readline()).decode('utf-8')
        print( message )
        # payload = getPayload(message)
        # requests.post("http://localhost:81/rover2022/service/createsensor.php", json=payload, timeout=.1)
    except Exception as e:
        print(e)
   


if __name__ == '__main__':
    while True:
        run()
        # time.sleep(1)
