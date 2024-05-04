#include "sensors.h"
#include "constants.h"

bool Sensors::init()
{
    if (initBMP280_())
    {
        return OK;
    }
    return ERROR;
}

bool Sensors::initBMP280_()
{
    // Init. BMP280
    if (!bmp_.begin(BMP_ADDRESS))
    {
        return ERROR;
    }
    delay(SETUP_WAIT_DELAY); // Valeur grande pour etre sur. (avant 2ms)

    bmp_.setSampling(Adafruit_BMP280::MODE_NORMAL,
                     Adafruit_BMP280::SAMPLING_X2,
                     Adafruit_BMP280::BMP_SAMPLING,
                     Adafruit_BMP280::BMP_FILTER,
                     Adafruit_BMP280::BMP_STANDBY_MS);
    delay(SETUP_WAIT_DELAY); // Délai pour stabiliser le capteur (?) --- Valeur grande pour etre sur (avant 50)

    return OK;
}

double Sensors::altitude()
{
    return bmp_.readAltitude(SEA_LEVEL_HPA);
}