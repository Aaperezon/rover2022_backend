import serial 
import time
import requests

lopy = serial.Serial(port='COM9', baudrate=115200)
def getPayload(message):
    message = message.split()
    variables = {
        "heart_rate1": message[0], 
        "heart_rate2": message[1],
        "temperature": message[2],
        "humidity":    message[3],
        "speed":       message[4],
        "roll":        message[5],
        "pitch":       message[6],
        "yaw":         message[7],
        "latitude":    message[8],
        "longitude":   message[9]
    }
    # for i,key in enumerate(variables.keys()):
    #     variables[key] = message[i]
    return variables     
        
def run():
    try:
        message = (lopy.readline()).decode('utf-8')
        print( message)
        
        # payload = getPayload(message)
        #requests.post("http://localhost:81/rover2022/service/createsensor.php", json=payload, timeout=.1)
    except Exception as e:
        print(e)
   


if __name__ == '__main__':
    while True:
        run()
        # time.sleep(1)
