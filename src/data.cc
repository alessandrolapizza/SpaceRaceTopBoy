#include "data.h"
#include "constants.h"

bool Data::init()
{
    // Init. SD card and BMP280 and imu(add)
    if (sensors_.init())
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
        for (int i = FIFO_ALTITUDE_MEASURES_NUMBER - 1; i > 0; i--)
        {
            fifoAltitudeMeasures_[i].value = fifoAltitudeMeasures_[i - 1].value;
            fifoAltitudeMeasures_[i].time = fifoAltitudeMeasures_[i - 1].time;
        }
        fifoAltitudeMeasures_[0].value = altitude_.value;
        fifoAltitudeMeasures_[0].time = altitude_.time;

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
        Serial.println(altitude_.value);
        Serial.println(altitude_.time);
    }

    delay(BMP_MEASURES_DELAY);
}

bool Data::postApogee()
{
    for (int i = 0; i < FIFO_ALTITUDE_MEASURES_NUMBER; i++)
    {
        if (altitude_.value >= fifoAltitudeMeasures_[i].value)
        {
            return false;
        }
    }
    return true;
}

AltitudeMeasure Data::altitude()
{
    return altitude_;
}