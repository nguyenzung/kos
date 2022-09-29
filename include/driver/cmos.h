#ifndef CMOS_H
#define CMOS_H

#include <kernel/basedriver.h>
#include <kernel/type.h>
#include <kernel/utils.h>

using namespace kernel;

namespace driver
{

typedef struct DateTime 
{
    uint8 second;
    uint8 minute;
    uint8 hour;
    uint8 day;
    uint8 month;
    uint32 year;
    uint8 century;

    DateTime& operator=(DateTime &datetime)
    {
        this->second = datetime.second;
        this->minute = datetime.minute;
        this->hour = datetime.hour;
        this->day = datetime.day;
        this->month = datetime.month;
        this->year = datetime.year;
        return *this;
    }

    bool operator!=(DateTime &datetime)
    {
        return this->second != datetime.second ||
                this->minute != datetime.minute ||
                this->hour != datetime.hour ||
                this->day != datetime.day ||
                this->month != datetime.month ||
                this->year != datetime.year;   
    }

    bool operator==(DateTime &datetime)
    {
        return this->second == datetime.second &&
                this->minute == datetime.minute &&
                this->hour == datetime.hour &&
                this->day == datetime.day &&
                this->month == datetime.month &&
                this->year == datetime.year;   
    }

} DateTime;

class CMOS: public BaseDriver
{
public:
    DateTime dateTime;
    uint8 centuryRegister;

    CMOS();
    ~CMOS();

    void active();
    void deactive();
    void handleInterrupt();

    void updateDateTime();

    static uint8 getUpdateInProgressFlag();
    static uint8 getRtcRegister(uint8 reg);
};

}

#endif