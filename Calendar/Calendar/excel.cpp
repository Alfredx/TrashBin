#include "excel.h"

Excel::Excel()
{
    HRESULT r;
       r = OleInitialize(0);
       if (r != S_OK && r != S_FALSE) {
          qWarning("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
       }
    excel_ = new QAxObject("ET.Application");
    excel_->setProperty("Visible",false);
    OleUninitialize();
}

Excel::~Excel()
{
    delete used_col_;
    delete used_row_;
    delete used_range_;
    delete worksheet_;
    delete worksheets_;
    delete workbook_;
    delete workbooks_;
    delete excel_;
}

void Excel::Create()
{
    workbooks_ = excel_->querySubObject("WorkBooks");
    workbooks_->dynamicCall("Add");
    workbook_ = excel_->querySubObject("ActiveWorkBook");
    worksheets_ = workbook_->querySubObject("WorkSheets");
    OpenSheetAt(1);
}

void Excel::Open(QString path)
{
    workbooks_ = excel_->querySubObject("WorkBooks");
    workbooks_->dynamicCall("Open(const QString&)", path);
    workbook_ = excel_->querySubObject("ActiveWorkBook");
    worksheets_ = workbook_->querySubObject("WorkSheets");
    OpenSheetAt(1);
}

void Excel::Save(const QString &name)
{
    excel_->setProperty("DisplayAlerts",0);
    workbook_->dynamicCall("SaveAs(const QString&)",name);
    excel_->setProperty("DisplayAlerts",1);
}

void Excel::Close()
{

    workbook_->dynamicCall("Close (Boolean)",false);
    excel_->dynamicCall("Quit (void)");
}

void Excel::OpenSheetAt(int i)
{
    if(workbook_->isNull())
        return;
    worksheet_ = workbook_->querySubObject("Worksheets(int)",i);
    used_range_ = worksheet_->querySubObject("UsedRange");
    used_row_ = used_range_->querySubObject("Rows");
    used_col_ = used_range_->querySubObject("Columns");
    row_start_ = used_range_->property("Row").toInt();
    col_start_ = used_range_->property("Column").toInt();
    rows_ = used_row_->property("Count").toInt();
    cols_ = used_col_->property("Count").toInt();
}

QString Excel::GetCellValueAt(int x, QString y)
{
    if(x >= row_start_ && x <= rows_ /*&&
            y.toInt() >= col_start_ && y.toInt() <= cols_*/)
    {
        y += QVariant(x).toString();
        QAxObject *cell = worksheet_->querySubObject("Range(QVariant, QVariant)",y);
        QString a = cell->dynamicCall(("Value(void)")).toString();
        return cell->dynamicCall("Value(void)").toString();
    }
    else return "";
}

void Excel::SetCellValueAt(const QString &str, int x, QString y)
{
    if(x >= row_start_ && x <= rows_ /*&&
            y.toInt() >= col_start_ && y.toInt() <= cols_*/)
    {
        y += QVariant(x).toString();
        QAxObject *cell = worksheet_->querySubObject("Range(QVariant, QVariant)",y);
        cell->dynamicCall("setValue(QVariant)",QVariant(str));
    }
    else return;
}
