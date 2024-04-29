#ifndef DATA_H
#define DATA_H

#include <Adafruit_BMP280.h>

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
};

#endif // DATA_H