#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Adafruit_BMP280.h>

enum States
{
    FIRST = 0,
    SECOND = 1,
    THIRD = 2,
};

enum Status
{
    ERROR = false,
    OK = true,
};

// Pins Setup //

#define BUZZER_PIN 2
#define SECOND_EVENT_PIN 13

// Data //

#define FIFO_ALTITUDE_MEASURES_NUMBER 3
#define SECOND_EVENT_ALTITUDE 2

// Sensors //

#define SETUP_WAIT_DELAY 500

// BMP280 //

#define BMP_ADDRESS 0x76
#define BMP_FILTER FILTER_X8
#define BMP_STANDBY_MS STANDBY_MS_1
#define BMP_SAMPLING SAMPLING_X16
#define SEA_LEVEL_HPA 1013.25
#define ALTITUDE_MEASURES_NUMBER 25
#define BMP_MEASURES_DELAY 40

#endif // CONSTANTS_H