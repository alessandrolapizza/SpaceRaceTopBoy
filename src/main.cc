#include <Arduino.h>
#include <Adafruit_BMP280.h>
// #include <Time.h>

#include "constants.h"
#include "data.h"

void setupFailed();  // Changer pattern
void setupSuccess(); // Changer pattern

// Instance du bmp280 et de l'accéléromètre
Adafruit_BMP280 bmp;
//...
Data data(bmp); // Ajouter le deucieme sensor ici

void setup()
{
  // Init. sensors
  // Init pin. buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // Init. barometer (and imu) and sd card and set ref. altitude
  if (data.init())
  {
    setupSuccess();
  }
  else
  {
    setupFailed();
  }

  // Serial.begin(9600);
}

void loop()
{
  // Update sensors
  data.update();

  // Write to SD Data

  // Check conditions to update state and do actions of states

  delay(BMP_MEASURES_DELAY);
}

void setupFailed() // Changer pattern
{
  tone(BUZZER_PIN, 3000, 1000);
}

void setupSuccess() // Changer pattern
{
  tone(BUZZER_PIN, 3000, 1000);
  delay(1500);
  tone(BUZZER_PIN, 3000, 1000);
}