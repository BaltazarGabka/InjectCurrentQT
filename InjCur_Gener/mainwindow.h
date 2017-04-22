#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
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

    void Check_FreqValues(RangeEdge range);
    void Get_FreqValueIn_kHz(int& val, RangeEdge range);
    void Put_FreqValueFro_kHz(const int& val, RangeEdge range);


};

#endif // MAINWINDOW_H
