#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "InjCur.h"
#include "ILogger.hpp"
#include <QDebug>

using std::vector;

namespace Ui {
class MainWindow;
}

class QtILogger : public ILogger{
    virtual void put(const std::string& data)
    {
        qDebug() << QString::fromStdString(data);
    }
};

class MainWindow : public QMainWindow , public ILogger
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    typedef enum
    {
        StartFreq =0,
        StopFreq
    }RangeEdge;

    virtual void put(const std::string& data);

private slots:

    void on_ButtonExit_clicked();


    void on_ButtonTestStart_clicked();
    void on_SpinBox_StartFreq_valueChanged(int arg1);

    void on_comboBox_FreqStart_currentIndexChanged(const QString &arg1);

    void on_SpinBox_StopFreq_valueChanged(int arg1);

    void on_comboBox_FreqStop_currentIndexChanged(const QString &arg1);

    void on_checkBox_ModulOn_stateChanged(int arg1);

    void update_Freq_Change(void);

    void on_ButtonTestStop_clicked();

private:

    Ui::MainWindow *ui;

    QTimer *timer_freq;

    VisaSession VSes;

    void Check_FreqValues(RangeEdge range);
    void Get_FreqValueIn_kHz(int& val, RangeEdge range);
    void Put_FreqValueFro_kHz(const int& val, RangeEdge range);


};

#endif // MAINWINDOW_H
