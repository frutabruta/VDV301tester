#ifndef UI_DRUHEOKNO_H
#define UI_DRUHEOKNO_H

#include <QMainWindow>



namespace Ui {
class ui_druheokno;
}

class ui_druheokno : public QMainWindow
{
    Q_OBJECT

public:
    explicit ui_druheokno(QWidget *parent = 0);
    ~ui_druheokno();
    vytvor();


private slots:
    void on_pushButton_clicked();

private:
    Ui::ui_druheokno *ui;
};

#endif // UI_DRUHEOKNO_H
