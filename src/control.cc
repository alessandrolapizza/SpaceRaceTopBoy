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
        setupFailed_(); // Code will continue to run, but the user will be notified of the error. Restart teensy.
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

    switch (state_)
    {
    case FIRST:
        if (data_.postApogee())
        {
            state_ = SECOND;
        }
        break;
    case SECOND:
        if (data_.altitude().value <= SECOND_EVENT_ALTITUDE)
        {
            secondEvent_();
            state_ = THIRD;
        }
        break;
    case THIRD:
        break;
    default:
        break;
    }
}

void Control::secondEvent_()
{
    digitalWrite(SECOND_EVENT_PIN, HIGH);
}