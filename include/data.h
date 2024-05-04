#ifndef DATA_H
#define DATA_H

#include <Adafruit_BMP280.h>
#include "constants.h"
#include "sensors.h"

struct AltitudeMeasure
{
    unsigned long time;
    double value;
};

class Data
{
public:
    bool init();
    void update();
    bool postApogee();
    AltitudeMeasure altitude();
    void log(String log);
    void logConfig();

private:
    double referenceAltitude_;
    AltitudeMeasure altitudeMeasures_[ALTITUDE_MEASURES_NUMBER];
    AltitudeMeasure altitude_; // Derniere altitude moyennée
    int measuredAltitudes_;    // Nombre d'altitudes mesurées dans le tableau altitudeMeasures_
    Sensors sensors_;
    AltitudeMeasure fifoAltitudeMeasures_[FIFO_ALTITUDE_MEASURES_NUMBER];
    String dataFile_;
    String logFile_;
    bool initSD_();
    void setReferenceAltitude_();
    void updateAltitude_(bool referenceAltitude = false);
    String createFileName_(bool isData = true);
    void logData_();
};

#endif // DATA_H