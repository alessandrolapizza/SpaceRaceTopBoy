#include <SD.h>
#include "data.h"
#include "constants.h"

Data::Data(Adafruit_BMP280 &bmp) : bmp_(bmp)
{
}

int Data::init()
{
    if (!bmp_.begin(BMP_ADDRESS))
    {
        return ERROR;
    }
    delay(2); // Wait for sensor to stabilize (?)

    bmp_.setSampling(Adafruit_BMP280::MODE_NORMAL,
                     Adafruit_BMP280::SAMPLING_NONE,
                     Adafruit_BMP280::SAMPLING_X16,
                     Adafruit_BMP280::BMP_FILTER,
                     Adafruit_BMP280::BMP_STANDBY_MS);
    delay(50); // Délai pour stabiliser le capteur (?)
    return OK;

    // Init. imu

    // Init. SD card
    if (!SD.begin())
    {
        return ERROR;
    }
}

void Data::setReferenceAltitude()
{
    for (int i = 0; i < ALTITUDE_MEASURES_NUMBER; i++)
    {
        altitudeMeasures_[i] = getAltitude_();
        delay(BMP_MEASURE_DELAY);
    }

}

void Data::update()
{
}