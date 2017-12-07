#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void makeWhite();
    void makeDark();
    void write(QByteArray data);
    QString message;
public slots:
private slots:


    void on_connect_clicked();

    void on_white_clicked();

    void on_dark_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *transmitter;
};

#endif // MAINWINDOW_H
