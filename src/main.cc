#include <Arduino.h>
#include <Adafruit_BMP280.h>

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

  // Init. barometer and imu and sd card
  if (data.init() == ERROR)
  {
    setupFailed();
  }
  else
  {
    setupSuccess();
  }

  // Setup altitude ref.
  data.setReferenceAltitude();

  // Init clock ?

  // Buzzer setup complete
}

void loop()
{
  // Update sensors

  // Write to SD Data

  // Check conditions to update state and do actions of states
}

void setupFailed() // Changer pattern
{
  while (true)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

void setupSuccess() // Changer pattern
{
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
}