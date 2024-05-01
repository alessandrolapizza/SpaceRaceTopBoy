#ifndef CONTROL_H
#define CONTROL_H

#include "data.h"

class Control
{
public:
    void init();
    void update();

private:
    Data data_;
    int state_ = FIRST;
    void setupFailed_();
    void setupSuccess_();
    void secondEvent_();
};

#endif