#ifndef DATA_H
#define DATA_H

#include <Adafruit_BMP280.h>
#include "constants.h"

struct AltitudeMeasure
{
    unsigned long time;
    double value;
};

class Data
{
public:
    Data(Adafruit_BMP280 &bmp);
    int init();
    void update();

private:
    Adafruit_BMP280 &bmp_;
    double referenceAltitude_;
    AltitudeMeasure altitudeMeasures_[ALTITUDE_MEASURES_NUMBER];
    AltitudeMeasure altitude_;
    int measuredAltitudes_;
    double getAltitude_();
    void setReferenceAltitude_();
    int initBMP280_();
    void updateAltitude_(bool referenceAltitude = false);
};

#endif // DATA_H