#include <driver/cmos.h>
#include <kernel/iocommand.h>
#include <kernel/printer.h>

using namespace driver;

#define CURRENT_YEAR        2022                                                               
#define CURRENT_MONTH       01

void readDateTime(DateTime &dateTime)
{
    while (CMOS::getUpdateInProgressFlag());                // Make sure an update isn't in progress
    dateTime.second = CMOS::getRtcRegister(0x00);
    dateTime.minute = CMOS::getRtcRegister(0x02);
    dateTime.hour = CMOS::getRtcRegister(0x04);
    dateTime.day = CMOS::getRtcRegister(0x07);
    dateTime.month = CMOS::getRtcRegister(0x08);
    dateTime.year = CMOS::getRtcRegister(0x09);

    uint8 registerB = CMOS::getRtcRegister(0x0B);
    
    // Convert BCD to binary values
    if (!(registerB & 0x04)) {
        dateTime.second = (dateTime.second & 0x0F) + ((dateTime.second / 16) * 10);
        dateTime.minute = (dateTime.minute & 0x0F) + ((dateTime.minute / 16) * 10);
        dateTime.hour = ( (dateTime.hour & 0x0F) + (((dateTime.hour & 0x70) / 16) * 10) ) | (dateTime.hour & 0x80);
        dateTime.day = (dateTime.day & 0x0F) + ((dateTime.day / 16) * 10);
        dateTime.month = (dateTime.month & 0x0F) + ((dateTime.month / 16) * 10);
        dateTime.year = (dateTime.year & 0x0F) + ((dateTime.year / 16) * 10);
    }
    
    // Convert 12 hour clock to 24 hour clock
    if (!(registerB & 0x02) && (dateTime.hour & 0x80)) {
        dateTime.hour = ((dateTime.hour & 0x7F) + 12) % 24;
    }
 
    // Calculate the full (4-digit) year
    dateTime.year += (CURRENT_YEAR / 100) * 100;
    if(dateTime.year < CURRENT_YEAR)
        dateTime.year += 100;
}

IMPL_MODULE_INSTANCE(CMOS)

CMOS::CMOS()
{
    CMOS::instance = this;
}

CMOS::~CMOS()
{

}

void CMOS::active()
{
    readDateTime(dateTime);
}

void CMOS::deactive()
{
}

void CMOS::handleInterrupt()
{
}

void CMOS::updateDateTime()
{
    DateTime currentDateTime;
    uint8 registerB;
 
    // Note: This uses the "read registers until you get the same values twice in a row" technique
    //       to avoid getting dodgy/inconsistent values due to RTC updates   
    do {
        readDateTime(currentDateTime);
    } while(currentDateTime == dateTime);

    dateTime = currentDateTime;
    printf("\n Time: %d/%d/%d %d:%d:%d", dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.minute, dateTime.second);
}

uint8 CMOS::getUpdateInProgressFlag()
{
    outb(0x70, 0x0A);
    return (inb(0x71) & 0x80);
}
    
uint8 CMOS::getRtcRegister(uint8 reg)
{
    outb(0x70, reg);
    return inb(0x71);
}