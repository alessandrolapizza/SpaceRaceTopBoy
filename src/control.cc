#include "control.h"
#include "constants.h"

void Control::init()
{
    if (data_.init())
    {
        setupSuccess_();
        data_.log("Setup successful with following parameters:");
        data_.logConfig();
    }
    else
    {
        setupFailed_();
        data_.log("Setup failed.");
        while (true)
        {
        }
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
        if (data_.altitude().value >= ALTITUDE_SECURITY_TRESHOLD)
        {
            state_ = SECOND;
            data_.log("Altitude security treshold passed.");
        }
        break;
    case SECOND:
        if (data_.postApogee())
        {
            state_ = THIRD;
        }
        break;
    case THIRD:
        if (data_.altitude().value <= SECOND_EVENT_ALTITUDE)
        {
            secondEvent_();
            state_ = FOURTH;
        }
        break;
    case FOURTH:
        break;
    default:
        break;
    }
}

void Control::secondEvent_()
{
    digitalWrite(SECOND_EVENT_PIN, HIGH);
    data_.log("Second event triggered.");
}