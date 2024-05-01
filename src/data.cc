#include <SD.h>
#include "data.h"
#include "constants.h"

Data::Data(Adafruit_BMP280 &bmp) : bmp_(bmp)
{
}

int Data::init()
{
    delay(1000); // Ensure sensors are ready and powered up correctly
    // Init. SD card and BMP280 and imu(add)
    if (SD.begin() && initBMP280_())
    {
        return ERROR;
    }

    setReferenceAltitude_();

    return OK;
}

void Data::setReferenceAltitude_()
{
    for (int i = 0; i < ALTITUDE_MEASURES_NUMBER; i++)
    {
        altitudeMeasures_[i].value = getAltitude_();
        altitudeMeasures_[i].time = millis();
        delay(BMP_MEASURES_DELAY);
    }

    updateAltitude_(true);
}

void Data::updateAltitude_(bool referenceAltitude = false)
{
    double altitudeValue = 0;
    for (int i = 0; i < ALTITUDE_MEASURES_NUMBER; i++)
    {
        altitudeValue += altitudeMeasures_[i].value;
    }
    altitudeValue /= ALTITUDE_MEASURES_NUMBER;

    if (referenceAltitude)
    {
        referenceAltitude_ = altitudeValue;
    }
    else
    {
        altitude_.value = altitudeValue - referenceAltitude_;
        altitude_.time = millis();
    }

    measuredAltitudes_ = 0;
}

void Data::update()
{
    altitudeMeasures_[measuredAltitudes_].value = getAltitude_();
    altitudeMeasures_[measuredAltitudes_].time = millis();
    measuredAltitudes_++;

    if (measuredAltitudes_ == ALTITUDE_MEASURES_NUMBER)
    {
        updateAltitude_();
    }
}

double Data::getAltitude_()
{
    return bmp_.readAltitude(SEA_LEVEL_HPA);
}

int Data::initBMP280_()
{
    // Ini. BMP280
    if (!bmp_.begin(BMP_ADDRESS))
    {
        return ERROR;
    }

    delay(1000); // Valeur grande pour etre sur. (avant 2ms)

    bmp_.setSampling(Adafruit_BMP280::MODE_NORMAL,
                     Adafruit_BMP280::SAMPLING_X2,
                     Adafruit_BMP280::BMP_SAMPLING,
                     Adafruit_BMP280::BMP_FILTER,
                     Adafruit_BMP280::BMP_STANDBY_MS);
    delay(1000); // Délai pour stabiliser le capteur (?) --- Valeur grande pour etre sur (avant 50)
    return OK;
}