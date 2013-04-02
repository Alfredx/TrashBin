#ifndef EXCEL_H
#define EXCEL_H

#include <QAxObject>
#include <QAxSelect>
#include <QAxWidget>
#include <qt_windows.h>

class Excel
{
public:
    explicit Excel();
    ~Excel();
    void Create();
    void Open(QString path);
    void OpenSheetAt(int i);
    QString GetCellValueAt(int x, QString y);
    void SetCellValueAt(const QString &str, int x, QString y);
    void Save(const QString &name);
    void Close();
private:
    QAxObject *excel_;
    QAxObject *workbooks_;
    QAxObject *workbook_;
    QAxObject *worksheets_;
    QAxObject *worksheet_;
    QAxObject *used_range_;
    QAxObject *used_row_;
    QAxObject *used_col_;
    int row_start_;
    int col_start_;
    int rows_;
    int cols_;

};

#endif // EXCEL_H
