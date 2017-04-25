#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cmath"
#include "qtimer.h"
#include <vector>
#include "visa.h"

using std::vector;

typedef void (MainWindow::*pMemberFunction) (const char *);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer_freq = new QTimer(this);
    connect(timer_freq, SIGNAL(timeout()), this, SLOT(update_Freq_Change()));

    static QtILogger dupa;

    VSes.registerLogger(dupa);
    VSes.registerLogger(*this);
    VSes.Visa_Init();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ButtonExit_clicked()
{
    QCoreApplication::quit();
}


void MainWindow::on_ButtonTestStart_clicked()
{

    /*load all test settings*/


    /*test*/
    //QString message;
    std::string message;
    int temp_val;

    this->Get_FreqValueIn_kHz(temp_val,StartFreq);
    message = "Starting Frequency ";
    message += std::to_string(temp_val);
    message += "kHz";
    ui->plainTextEdit_Message->appendPlainText(QString::fromStdString(message));

    temp_val = ui->spinBox_Time->value();
    timer_freq->start(temp_val*1000);
}


void MainWindow::on_SpinBox_StartFreq_valueChanged(int arg1)
{
    (void)arg1;

    MainWindow::Check_FreqValues(StartFreq);

}

void MainWindow::on_comboBox_FreqStart_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "kHz")
        {
        ui->SpinBox_StartFreq->setMinimum(1);
        ui->SpinBox_StartFreq->setMaximum(230000);
        }
    else if (arg1 == "MHz")
        {
        ui->SpinBox_StartFreq->setMinimum(1);
        ui->SpinBox_StartFreq->setMaximum(230);
        }
    MainWindow::Check_FreqValues(StartFreq);
}


void MainWindow::on_SpinBox_StopFreq_valueChanged(int arg1)
{
    (void)arg1;

    MainWindow::Check_FreqValues(StopFreq);

}

void MainWindow::on_comboBox_FreqStop_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "kHz")
        {
        ui->SpinBox_StartFreq->setMinimum(1);
        ui->SpinBox_StartFreq->setMaximum(230000);
        }
    else if (arg1 == "MHz")
        {
        ui->SpinBox_StartFreq->setMinimum(1);
        ui->SpinBox_StartFreq->setMaximum(230);
        }
    MainWindow::Check_FreqValues(StopFreq);
}

void MainWindow::Check_FreqValues(RangeEdge range)
{
    int temp_StopFreq;
    this->Get_FreqValueIn_kHz(temp_StopFreq,StopFreq);

    int temp_StartFreq;
    this->Get_FreqValueIn_kHz(temp_StartFreq,StartFreq);

    if (temp_StopFreq <= temp_StartFreq)
        {
        if (range == StartFreq){
            this->Put_FreqValueFro_kHz(temp_StopFreq-1,StartFreq);
        }
        else{
            this->Put_FreqValueFro_kHz(temp_StartFreq+1,StopFreq);
        }
        }
    else{
        if (range == StartFreq){
            this->Put_FreqValueFro_kHz(temp_StartFreq,StartFreq);
        }
        else{
            this->Put_FreqValueFro_kHz(temp_StopFreq,StopFreq);
        }
    }
}

void MainWindow::Get_FreqValueIn_kHz(int& val, RangeEdge range)
{
    int temp_unit;

    switch (range){
        case StartFreq:{
            temp_unit = ui->comboBox_FreqStart->currentIndex();
            val = ui->SpinBox_StartFreq->value();
            val *= pow(1000,temp_unit);
            break;
        }
        case StopFreq:{
            temp_unit = ui->comboBox_FreqStop->currentIndex();
            val = ui->SpinBox_StopFreq->value();
            val *= pow(1000,temp_unit);
            break;
        }
        default:{
            break;
        }
    }
}

void MainWindow::Put_FreqValueFro_kHz(const int& val, RangeEdge range)
{
    int temp_unit;
    int temp_val = val;

    switch (range){
        case StartFreq:{
            temp_unit = ui->comboBox_FreqStart->currentIndex();
            temp_val /= pow(1000,temp_unit);
            ui->SpinBox_StartFreq->setValue(temp_val);
            break;
        }
        case StopFreq:{
            temp_unit = ui->comboBox_FreqStop->currentIndex();
            temp_val /= pow(1000,temp_unit);
            ui->SpinBox_StopFreq->setValue(temp_val);
            break;
        }
        default:{
            break;
        }
    }
}

void MainWindow::on_checkBox_ModulOn_stateChanged(int arg1)
{
    ui->groupBox_ModulDetails->setEnabled(arg1?true:false);

}

void MainWindow::update_Freq_Change(void){
    /*test*/
    //QString message;
    std::string message;
    static int temp_val;

    message = "Countup ";
    message += std::to_string(temp_val++);

    ui->plainTextEdit_Message->appendPlainText(QString::fromStdString(message));
}

void MainWindow::put(const std::string& data)
{
    ui->plainTextEdit_Message->appendPlainText(QString::fromStdString(data));
}

void MainWindow::on_ButtonTestStop_clicked()
{
    timer_freq->stop();
}
