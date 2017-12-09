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

    QByteArray data;
    QString message;
    void setColor(qint8 color);
    void info(QString text);
    void error(QString text);
    void playEffect();
    bool playing;
public slots:
private slots:

    void setColor(qint8 color1, qint8 color2, qint8 color3);

    void write();

    void on_white_clicked();

    void on_dark_clicked();

    void on_disconnect_clicked();

    void on_connect_clicked();

    void on_pushButton_clicked();

    void on_gold_clicked();

    void on_red_clicked();

    void on_green_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *transmitter;
};

#endif // MAINWINDOW_H
