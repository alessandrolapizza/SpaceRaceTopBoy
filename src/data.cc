#include "data.h"
#include "constants.h"

bool Data::init()
{
    // Init. SD card and BMP280 and imu(add)
    if (sensors_.init())
    {
        return ERROR;
    }
    return OK;

    setReferenceAltitude_();
}

void Data::setReferenceAltitude_()
{
    for (int i = 0; i < ALTITUDE_MEASURES_NUMBER; i++)
    {
        altitudeMeasures_[i].value = sensors_.altitude();
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
    altitudeMeasures_[measuredAltitudes_].value = sensors_.altitude();
    altitudeMeasures_[measuredAltitudes_].time = millis();
    measuredAltitudes_++;

    if (measuredAltitudes_ == ALTITUDE_MEASURES_NUMBER)
    {
        updateAltitude_();
    }
}