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

    QString message;
    void setColor(qint8 color);
    void info(QString text);
    void error(QString text);
public slots:
private slots:


    void write(QByteArray data);

    void on_white_clicked();

    void on_dark_clicked();

    void on_disconnect_clicked();

    void on_connect_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *transmitter;
};

#endif // MAINWINDOW_H
