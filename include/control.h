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
    void setupFailed_();
    void setupSuccess_();
};

#endif