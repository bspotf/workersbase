#ifndef DATETIMEHELPER_H
#define DATETIMEHELPER_H

#include <inttypes.h>

static int getYears(int64_t time)
{
    return time/(60*60*24*365);
}
#endif // DATETIMEHELPER_H
