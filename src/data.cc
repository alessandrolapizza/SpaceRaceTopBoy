#include <SD.h>
#include "data.h"
#include "constants.h"

bool Data::init()
{
    if (!(sensors_.init() && initSD_()))
    {
        return ERROR;
    }
    log("Devices initialized.");

    setReferenceAltitude_();
    log("Reference altitude set to " + String(referenceAltitude_) + "m.");

    return OK;
}

void Data::logConfig(){
    log("Reference altitude: " + String(referenceAltitude_) + "m");
    log("Altitude security treshold: " + String(ALTITUDE_SECURITY_TRESHOLD) + "m");
    log("Second event altitude: " + String(SECOND_EVENT_ALTITUDE) + "m");
    log("Altitude measures number: " + String(ALTITUDE_MEASURES_NUMBER));
    log("Fifo altitude measures number: " + String(FIFO_ALTITUDE_MEASURES_NUMBER));
    log("BMP measures delay: " + String(BMP_MEASURES_DELAY) + "ms");
    log("Setup delay: " + String(SETUP_WAIT_DELAY) + "ms");
}

void Data::log(String log){
    File myFile;
    myFile = SD.open(logFile_.c_str(), FILE_WRITE);
    myFile.println((("[" + String(millis()) + "] " + log)));
    myFile.close();
}

bool Data::initSD_()
{
    if (!SD.begin(BUILTIN_SDCARD))
    {
        return ERROR;
    }

    dataFile_ = createFileName_().c_str();
    logFile_ = createFileName_(false).c_str();

    File myFile;
    myFile = SD.open(dataFile_.c_str(), FILE_WRITE);
    myFile.println("Time [ms], Raw Altitude [m], Filtered Altitude [m]");
    myFile.close();
    myFile = SD.open(logFile_.c_str(), FILE_WRITE);
    myFile.println((("[" + String(millis()) + "]" + " Log file created.")));
    myFile.close();

    return OK;
}

String Data::createFileName_(bool isData)
{
    int fileNumber = 0;
    String fileName;

    do
    {
        if (isData)
        {
            fileName = "data" + String(fileNumber++) + ".csv";
        }
        else
        {
            fileName = "logs" + String(fileNumber++) + ".txt";
        }
    } while (SD.exists(fileName.c_str()));

    return fileName;
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

void Data::updateAltitude_(bool referenceAltitude)
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
    logData_();
    measuredAltitudes_++;

    if (measuredAltitudes_ == ALTITUDE_MEASURES_NUMBER)
    {
        updateAltitude_();
        Serial.println(altitude_.value);
        Serial.println(altitude_.time);
    }

    delay(BMP_MEASURES_DELAY);
}

void Data::logData_()
{
    File myFile;
    myFile = SD.open(dataFile_.c_str(), FILE_WRITE);
    myFile.println(altitudeMeasures_[measuredAltitudes_].time + ", " + String(altitudeMeasures_[measuredAltitudes_].value) + ", " + String(altitude_.value));
    myFile.close();
}

bool Data::postApogee()
{
    AltitudeMeasure apogee;
    apogee.value = 0;
    apogee.time = 0;

    for (int i = 0; i < FIFO_ALTITUDE_MEASURES_NUMBER; i++)
    {
        if (altitude_.value >= fifoAltitudeMeasures_[i].value)
        {
            return false;
        }
        if (fifoAltitudeMeasures_[i].value > apogee.value)
        {
            apogee.value = fifoAltitudeMeasures_[i].value;
            apogee.time = fifoAltitudeMeasures_[i].time;
        }
    }

    log("Apogee reached at " + String(apogee.time) + "ms with an altitude of " + String(apogee.value) + "m.");
    return true;
}

AltitudeMeasure Data::altitude()
{
    return altitude_;
}