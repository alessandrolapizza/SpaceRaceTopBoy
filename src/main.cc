#include <Arduino.h>
// #include <Time.h>

#include "constants.h"
#include "control.h"

static Control control;

void setup()
{
  delay(500); // Ensure sensors are correctly powered up.

  // Init. sensors
  // Init pin. buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // Init. barometer (and imu) and sd card and set ref. altitude

  control.init();
  // Serial.begin(9600);
}

void loop()
{
  control.update();
}