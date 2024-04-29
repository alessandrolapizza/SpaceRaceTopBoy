#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Adafruit_BMP280.h>

enum Status
{
    OK = 0,
    ERROR = 1,
};

#define BMP_ADDRESS 0x77 // Changer
#define BMP_MEASURE_DELAY 1 // Changer
#define BMP_FILTER FILTER_OFF // Changer
#define BMP_STANDBY_MS STANDBY_MS_1 // Changer Meme cgose que measure delay ???

#define ALTITUDE_MEASURES_NUMBER 500 // Changer

#define BUZZER_PIN 8 // Changer

#endif // CONSTANTS_H