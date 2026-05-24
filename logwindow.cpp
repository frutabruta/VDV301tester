#include "logwindow.h"
#include "ui_logwindow.h"

LogWindow::LogWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogWindow)
{
    ui->setupUi(this);
}

LogWindow::~LogWindow()
{
    delete ui;
}



void LogWindow::slotLogWindowAppend(const QString &text)
{
    if(text.contains("{Critical}"))
    {
        ui->textEdit_logContent->setTextColor(Qt::red);
    }
    if(text.contains("{Warning}"))
    {
        ui->textEdit_logContent->setTextColor(QColor(255,165,0));
    }
    else if(text.contains("{Info}"))
    {
        ui->textEdit_logContent->setTextColor(QColor(34,139,34));
    }
    else
    {
        ui->textEdit_logContent->setTextColor(Qt::black);
    }
    ui->textEdit_logContent->append(text);
}

void LogWindow::on_pushButton_windowClose_clicked()
{
    this->close();
}


void LogWindow::on_pushButton_logClear_clicked()
{
     ui->textEdit_logContent->clear();
}

