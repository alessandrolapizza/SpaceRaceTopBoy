/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
float ini_temp=0;
float ini_alt=0;
float ini_press=0;
float temp=0;
float alt=0;
float press=0;
void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  delay(1000);
  for(int i=0;i<50;i++){
    //ini_temp+=bmp.readTemperature();
    ini_press+=bmp.readPressure();
    ini_alt+=bmp.readAltitude();
    delay(200);
  }
  //mkini_temp/=50;
  ini_alt/=50;
  ini_press/=50;
}
void loop() {
    /*temp=bmp.readTemperature();

    Serial.print(F("Temperature = "));
    Serial.print(temp);
    Serial.println(" *C");*/

    /* for(int i=0;i<10;i++){
    press+=bmp.readPressure();
    delay(?);
    }
    press/=10;*/
    press=bmp.readPressure();
    Serial.print(F("Pressure = "));
    Serial.print(press);
    Serial.println(" Pa");

    alt=bmp.readAltitude()-ini_alt;
    Serial.print(F("Approx altitude = "));
    Serial.print(alt); /* Adjusted to local forecast! */
    Serial.println(" m");
    
    Serial.println();
    if (bmp.readAltitude(1013.25)>=423){
      digitalWrite(13,HIGH);
    }
    else{
      digitalWrite(13,LOW);
    }
    delay(62.5);
}
