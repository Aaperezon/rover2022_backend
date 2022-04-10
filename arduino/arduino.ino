// Giroscopio
const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;
double x;
double y;
double z;

// Funciones a utilizar
// Funciones:
long vibration(int sensor){
  long measurement = pulseIn (sensor, HIGH, 100);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}

// Datos del sensor de presión atmosférica:
#include <Wire.h>
#include <SparkFunBME280.h>
BME280 mySensor; //Global sensor object
const int sensorMin = 0; // sensor minimum
const int sensorMax = 1024; // sensor maximum
// Pines de comunicación:
int RELAY1 = 20;
int RELAY2 = 21;
int delayValue=3000;
long count=0;


// Archivo para el sensor de CO2:
#define RZERO 62.88
#include "MQ135.h"
const int ANALOGPIN=0;
MQ135 gasSensor = MQ135(ANALOGPIN);

// Pines de los sensores de vibración:
int sens1 = 46; // Sensor de vibración
int sens2 = 48;
int sens3 = 50;
int sens4 = 52;

// Archivo para el sesor de peso
#include "HX711.h"
// Pin de datos y de reloj del sensor de peso
byte pinData = A5;
byte pinClk = A4;
HX711 bascula;
// Parámetro para calibrar el peso y el sensor
float factor_calibracion = 79.0; //Este valor del factor de calibración funciona para mi. El tuyo probablemente será diferente.


void setup() {
  // Giroscopio
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);

  
  // Sensores de vibración:
  pinMode(sens1, INPUT);
  pinMode(sens2, INPUT); 
  pinMode(sens3, INPUT); 
  pinMode(sens4, INPUT);  

   // Sensor de presión atmosférica:
   //For I2C, enable the following and disable the SPI section

mySensor.settings.commInterface = I2C_MODE;
mySensor.settings.I2CAddress = 0x76;

pinMode(RELAY1,OUTPUT);
pinMode(RELAY2,OUTPUT);
digitalWrite(RELAY1,HIGH);
digitalWrite(RELAY2,HIGH);
while(!Serial);
//Serial.println("Reading basic values from BME280");
//Serial.println("");

Wire.begin();

if (mySensor.beginI2C() == false) //Begin communication over I2C
{
//Serial.println("The chip did not respond. Please check wiring.");
while(1); //Freeze
}

// Setup del sensor de peso
// Iniciar sensor
  bascula.begin(pinData, pinClk);

  // Aplicar la calibración
  bascula.set_scale();
  // Iniciar la tara
  // No tiene que haber nada sobre el peso
  bascula.tare();

  // Obtener una lectura de referencia
  long zero_factor = bascula.read_average();
  // Mostrar la primera desviación
  //Serial.print("Zero factor: ");
  //Serial.println(zero_factor);
}

void loop() {
  // Giroscopio
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
  x = RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  
  
  // Código de los sensores de vibración:
  long measurement1 = vibration(sens1);
  String measurement_result1;
  if (measurement1 == 0){
    measurement_result1 = "NULL";
    //Serial.print();
  }
  else if (measurement1 > 0 && measurement1 <= 400){
    measurement_result1 = "LOW";
    //Serial.print("\nSensor 1: Vibración BAJA");
  }  
  else if (measurement1 >= 401 && measurement1 <= 1000){
    measurement_result1 = "MEDIUM";
    //Serial.print("\nSensor 1:Vibración MEDIA");
  }
  else
    measurement_result1 = "HIGH";
    //Serial.print("\nSensor 1: Vibración ALTA. ¡PRECAUCIÓN!"); 
  //delay(50);

  
  long measurement2 = vibration(sens2);
  String measurement_result2;
  if (measurement2 == 0){
    measurement_result2 = "NULL";
    //Serial.print("\nSensor 2: Vibración NULA");
  }    
  else if (measurement2 > 0 &&  measurement2 <= 400){
    measurement_result2 = "LOW";
    //Serial.print("\nSensor 2: Vibración BAJA"); 
  } 
  else if (measurement2 >= 401 && measurement2 <= 1000){
    measurement_result2 = "MEDIUM";
    //Serial.print("\nSensor 2: Vibración MEDIA");
  } 
  else
    measurement_result2 = "ALTA"; 
    //Serial.print("\nSensor 2: Vibración ALTA. ¡PRECAUCIÓN!");
  //delay(50);

  
  long measurement3 = vibration(sens3);
  String measurement_result3;
  if (measurement3 == 0){
    measurement_result3 = "NULL";
    //Serial.print("\nSensor 3: Vibración NULA");
  } 
  else if (measurement3 > 0 && measurement3 <= 400){
    measurement_result3 = "LOW";
    //Serial.print("\nSensor 3: Vibración BAJA"); 
  } 
  else if (measurement3 >= 401 && measurement3 <= 1000){
    measurement_result3 = "MEDIUM";
    //Serial.print("\nSensor 3: Vibración MEDIA");
  }
  else 
    measurement_result3 = "HIGH";
    //Serial.print("\nSensor 3: Vibración ALTA. ¡PRECAUCIÓN!");
  //delay(50);


  long measurement4 = vibration(sens4);
  String measurement_result4;
  if (measurement4 == 0){
    measurement_result4 = "NULL";
    //Serial.print("\nSensor 4: Vibración NULA");
  }
  else if (measurement4 > 0 && measurement4 <= 400){
    measurement_result4 = "LOW";
    //Serial.print("\nSensor 4: Vibración BAJA");
  }   
  else if (measurement4 >= 401 && measurement4 <= 1000){
    measurement_result4 = "MEDIUM";
    //Serial.print("\nSensor 4: Vibración MEDIA");
  }
  else
    measurement_result4 = "HIGH";
    //Serial.print("\nSensor 4: Vibración ALTA. ¡PRECAUCIÓN!");
  //delay(50);
  //Serial.print("\n");

  
  // Código del sensor MQ135:
  //delay(500);
  float ppm = gasSensor.getPPM();                                       //UNCOMMENT THIS
  //Serial.print("\n");
  //Serial.print("ppm de CO2: ");
  //Serial.print(ppm);
  //Serial.println("    ");
  //Serial.println("    ");
  //delay(500);


  // Código del sensor de presión atmosférica:
  //delay(delayValue);

int sensorReading = analogRead(A0);                                   //UNCOMMENT THIS
//Serial.print("Humedad(%): ");
//Serial.print(mySensor.readFloatHumidity(), 0);
//Serial.println("");

//Serial.print("Presión Atm. Bar.(PA): ");
//Serial.print(mySensor.readFloatPressure(), 0);
//Serial.println("");

//Serial.print("Altitud(m.s.n.m): ");
//Serial.print(mySensor.readFloatAltitudeMeters(), 1);
//Serial.println("");
//Serial.print(mySensor.readFloatAltitudeFeet(), 1);

//Serial.print("Temperatura(°C): ");
//Serial.print(mySensor.readTempC(), 2);
//Serial.println("");
//Serial.print(mySensor.readTempF(), 2);

//Serial.println();

// Loop del sensor de peso
// Aplicar calibración
  bascula.set_scale(20000);

  // Mostrar la información para ajustar el factor de calibración
  //Serial.print("Información del par 1: ");
  //Serial.print(bascula.get_units(), 1);
  //Serial.print(" kgs");
  //Serial.print(" factor_calibracion: ");
  //Serial.print(factor_calibracion);
  //Serial.println();

  // Obtener información desde el monitor serie
  //if (Serial.available())
  //{
  //  char temp = Serial.read();
  //  if (temp == '+')
  //    factor_calibracion += 1;
  //  else if (temp == '-')
  //    factor_calibracion -= 1;
  //}
  Serial.println(measurement_result1+" "+measurement_result2+" "+measurement_result3+" "+measurement_result4+" "+ppm+" "+mySensor.readFloatHumidity()+" "+mySensor.readFloatPressure()+" "+mySensor.readFloatAltitudeMeters()+" "+mySensor.readTempC()+" "+bascula.get_units() + " " + x + " " + y + " " + z);


}










 
