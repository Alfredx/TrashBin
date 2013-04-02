#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calendarunittest.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    CalendarUnitTest cut;
    cut.Test();
}

void MainWindow::on_pushButton_clicked()
{
    Calendar c;
    ui->textEdit_4->clear();
    ui->textEdit_4->append(c.Input(ui->textEdit->toPlainText().toInt(),
                                   ui->textEdit_2->toPlainText().toInt(),
                                   ui->textEdit_3->toPlainText().toInt()));
}
