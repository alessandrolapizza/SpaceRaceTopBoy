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
                     Adafruit_BMP280::FILTER_OFF,
                     Adafruit_BMP280::STANDBY_MS_1);
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

}

void Data::update()
{
    
}