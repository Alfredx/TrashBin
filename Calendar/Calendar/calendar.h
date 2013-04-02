#ifndef CALENDAR_H
#define CALENDAR_H

#include <QString>

/*
 *this class outputs the day after inputed time
 *range: year 1800 - 2100
 */

class Calendar
{
public:
    Calendar();
    QString Input(int yy, int mm, int dd);
    QString Output(int yy, int mm, int dd);
};

#endif // CALANDER_H
