#include "calendar.h"
#include <QVariant>
Calendar::Calendar()
{
}

QString Calendar::Input(int yy, int mm, int dd)
{
    if(yy < 1800 || yy > 2100)
        return "Invalid year. Out of range.";
    if(mm < 1 || mm > 12)
        return "Invalid month. Out of range.";
    if(dd < 1 || dd > 31)
        return "Invalid day. Out of range.";
    if(dd == 31 && (mm == 2 || mm == 4 || mm == 6 || mm == 9 || mm == 11))
        return "No day 31 on small month.";
    if(mm == 2 && dd > 29)
        return "No such day in Feb.";
    if((yy % 4 != 0 || yy % 100 == 0) && (yy % 400 != 0) && mm == 2 && dd > 28)
        return "No such day in Feb this year.";
    return Output(yy,mm,dd);
}

QString Calendar::Output(int yy, int mm, int dd)
{
    if(dd == 31)
    {
        if(mm == 12)
            return QVariant(yy+1).toString()+"-"+"1-1";
        else
            return QVariant(yy).toString()+"-"+QVariant(mm+1).toString()+"-1";
    }
    if(dd == 30)
    {
        if(mm == 4 || mm == 6 || mm == 9|| mm == 11)
            return QVariant(yy).toString()+"-"+QVariant(mm+1).toString()+"-1";
        else
            return QVariant(yy).toString()+"-"+QVariant(mm).toString()+"-"+QVariant(dd+1).toString();
    }
    if(mm == 2)
    {
        if(yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0) )
            if(dd == 29)
                return QVariant(yy).toString()+"-"+QVariant(mm+1).toString()+"-1";
            else if(dd == 28)
                return QVariant(yy).toString()+"-"+QVariant(mm).toString()+"-"+QVariant(dd+1).toString();
    }
    return QVariant(yy).toString()+"-"+QVariant(mm+1).toString()+"-1";
}
