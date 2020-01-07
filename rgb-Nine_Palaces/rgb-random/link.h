#ifndef LINK_H
#define LINK_H

#include "configure.h"
#include "_Random.h"
#include "serial_port.h"

class Link
{
public:
    Link();
    void Run();
    bool is_exit();
private:
    Color_Random color_random;
    bool run;
};

#endif // LINK_H
