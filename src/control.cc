#include "control.h"
#include "constants.h"

void Control::init()
{
    if (data_.init())
    {
        setupSuccess_();
    }
    else
    {
        setupFailed_(); //Code will continue to run, but the user will be notified of the error. Restart teensy.
    }
}

void Control::setupFailed_() // Changer pattern
{
    tone(BUZZER_PIN, 3000, 1000);
}

void Control::setupSuccess_() // Changer pattern
{
    tone(BUZZER_PIN, 3000, 1000);
    delay(1500);
    tone(BUZZER_PIN, 3000, 1000);
}

void Control::update()
{
    data_.update();
}