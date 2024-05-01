#ifndef SENSORS_H
#define SENSORS_H
#include <Adafruit_BMP280.h>

class Sensors
{
public:
    bool init();
    double altitude();

private:
    Adafruit_BMP280 bmp_;
    bool initBMP280_();
};

#endif