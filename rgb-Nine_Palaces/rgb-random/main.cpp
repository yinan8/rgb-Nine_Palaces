﻿#include "link.h"

int main()
{
    Link run;
    Serial_Port::serialSet(1);
    for(;;)
    {
        run.Run();
        if(run.is_exit())
                {
                    break;
                }
    }
    return 1;
}
