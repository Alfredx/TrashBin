#include "calendarunittest.h"

CalendarUnitTest::CalendarUnitTest()
{
}

void CalendarUnitTest::Test()
{
    Calendar *calendar = new Calendar();
    Excel *excel = new Excel();
    excel->Open("D:/data.xls");
    int yy =0,mm = 0, dd = 0;
    for(int i = 2; i < 62; ++i)
    {
        yy = excel->GetCellValueAt(i,"B").toInt();
        mm = excel->GetCellValueAt(i,"C").toInt();
        dd = excel->GetCellValueAt(i,"D").toInt();
        QString result = calendar->Input(yy,mm,dd);
        excel->SetCellValueAt(result,i,"F");
        if(result.compare(excel->GetCellValueAt(i,"E")))
            excel->SetCellValueAt("True",i,"G");
        else
            excel->SetCellValueAt("False",i,"G");
    }
    excel->Save("D:/dataout.xls");
    excel->Close();
}
