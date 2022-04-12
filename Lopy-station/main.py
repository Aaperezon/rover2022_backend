import serial 
import time
import requests
import random
from decimal import Decimal
try:
    lopy = serial.Serial(port='COM8', baudrate=115200)
except:
    pass  
def getPayLoad(message):  
    message = message.split()
    N=2
    variables = {
        "vibration1":         message[0], 
        "vibration2":         message[1],
        "vibration3":         message[2],
        "vibration4":         message[3],
        "gasCO2":       float(message[4]),
        "humidity":     21,
        "pressure":     float(message[6]),
        "altitude":     float(message[7]),
        "temperature":  float(message[8]),
        "roll":         float(message[9]),
        "pitch":        float(message[10]),
        "yaw":          float(message[11]),
        "speed":       float( message[12]),
       "gravity1_x":    round(random.uniform(15,18), N),
        "gravity1_y":    round(random.uniform(15,18), N),
        "gravity1_z":    round(random.uniform(15,18), N),
        "light1":    int(random.uniform(20000,22000)),
        "heart_rate1":    int( random.uniform(110,115) ),
    }
    return variables
def getPayLoadSim():  
    N = 2
    variables = {
        "vibration1": "LOW", 
        "vibration2": "MODERATE",
        "vibration3":"HIGH",
        "vibration4":   "NULL",
        "gasCO2":      round(random.uniform(1,2), N),
        "humidity":        round(random.uniform(20,100), N),
        "pressure":       round(random.uniform(1,2), N),
        "altitude":        round(random.uniform(1,2), N),
        "temperature":   round(random.uniform(20,40), N),
        "roll":    round(random.uniform(1,2), N),
        "pitch":    round(random.uniform(1,2), N),
        "yaw":    round(random.uniform(1,2), N),
        "speed":    round(random.uniform(15,18), N),
        "gravity1_x":    round(random.uniform(15,18), N),
        "gravity1_y":    round(random.uniform(15,18), N),
        "gravity1_z":    round(random.uniform(15,18), N),
        "light1":    round(random.uniform(15,18), N),
        "heart_rate1":    200
    }
    return variables

def run():
    global lopy
    try:
        message = (lopy.readline()).decode('utf-8')
        print( message )
        payload = getPayLoad(message)
        requests.post("http://localhost:81/rover2022/service/createsensor.php", json=payload, timeout=.1)
    except Exception as e:
        # print(e)
        if lopy.isOpen():
                lopy.close()
        else:
            try:
                lopy = serial.Serial(port='COM8', baudrate=115200)
            except:
                pass
   
def simulate():
        payload = getPayLoadSim()
        print(payload)
        requests.post("http://localhost:81/rover2022/service/createsensor.php", json=payload, timeout=.1)
        time.sleep(.5)

if __name__ == '__main__':
    while True:
        run()
        # time.sleep(.05)
