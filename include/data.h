#ifndef DATA_H
#define DATA_H

#include <Adafruit_BMP280.h>
#include "constants.h"

struct AltitudeMeasure
{
    double altitude;
    time_t time;
};

class Data
{
public:
    Data(Adafruit_BMP280 &bmp);
    int init();
    void setReferenceAltitude();
    void update();

private:
    Adafruit_BMP280 &bmp_;
    double referenceAltitude_;
    double getAltitude_();
    double altitudeMeasures_[ALTITUDE_MEASURES_NUMBER];
};

#endif // DATA_H