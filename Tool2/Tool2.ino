#include <MPU9250.h>
#include <math.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


MPU9250 IMU (Wire , 0x69);      // MPU9250 is a class and "IMU" is a object, we need to pass parameter to the object "IMU". wire is used for I2C communication, 
                                // second parameter is for I2C address, we left the ADO pin unconnected so its set to low, 0x68 is address,  
                                // if it was high then the address is 0x69

void setup() {                  // put your setup code here, to run once:
  Serial.begin(9600);           // Initialise the serial monitor 
  IMU.begin();                  // Initialise the IMU object
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(2.5);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("Hello Diane!"); // text to display
  oled.display();               // show on OLED
}

void loop() {
                                // put your main code here, to run repeatedly:
  IMU.readSensor();
  //Accelerometer data code
  Serial.print("Acelerómetro (eje 'X'): ");   
  Serial.print(IMU.getAccelX_mss(), 3);     // to get the accelerometer value from the data buffer in the X direction, these values are in meter per second square
  Serial.print("               Acelerómetro (eje 'Y'): ");
  Serial.print(IMU.getAccelY_mss(), 3);
  Serial.print("               Acelerómetro (eje 'Z'): ");
  Serial.println(IMU.getAccelZ_mss(), 3);

  
  //Gyroscope data code (Mide la velocidad angular en grados/seg)
  Serial.print("Giroscopio eje 'x' (°/s): ");
  Serial.print(IMU.getGyroX_rads(), 3)*(180/PI);        // gets the gyroscope value from the data buffer in the X direction, these vavlues are in degrees per second
  Serial.print("           Giroscopio eje 'y' (°/s): ");
  Serial.print(IMU.getGyroY_rads(), 3)*(180/PI);
  Serial.print("           Giroscopio eje 'z' (°/s): ");
  Serial.println(IMU.getGyroZ_rads(), 3)*(180/PI);

  
  //Magnetometer data code
  Serial.print("Magnometro eje 'x' (MicroTesla): ");
  Serial.print(IMU.getMagX_uT(), 3);                //gets the magnetometer value from the data buffer in the X direction, these are in microtesla
  Serial.print("    Magnometro eje 'y' (MicroTesla): ");
  Serial.print(IMU.getMagY_uT(), 3);
  Serial.print("    Magnometro eje 'z' (MicroTesla): ");
  Serial.println(IMU.getMagZ_uT(), 3);

  
  //Temperature reading
  Serial.print("Temperatura en °C: ");
  Serial.println(IMU.getTemperature_C(), 2);         // gets the temperature value from the data buffer and returns it in units of C
  Serial.print("*********** Siguiente paquete de datos *****************");
  Serial.println("    ");
  Serial.println("    ");
  Serial.println("    ");
  Serial.println("    ");
  delay(750);
 
}
