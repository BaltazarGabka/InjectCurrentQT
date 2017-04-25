#ifndef INJCUR_H
#define INJCUR_H

#include <string>
#include <vector>
#include "visa.h"
#include <stdlib.h>
#include "ILogger.hpp"

using std::vector;
using std::string;

class VisaDevice{
public:
    typedef enum{
        disconnected = 0,
        connected,
        error
    }Device_Status;

private:
    Device_Status status;
    ViSession   vi;
public:
    VisaDevice(void){status = disconnected;vi = VI_NULL;}
    ViStatus connect_ToDevice(ViSession &rm, std::string &desc);
};

class InjCur : public VisaDevice{
private:
    int         Start_Freq;         /*in Hz*/
    int         Stop_Freq;          /*in Hz*/
    double      Change_Freq;        /*for example 1% is 1.01*/
    int         Time_Freq;          /*in miliseconds*/
    bool        AM_Mod_State;       /*AM modulcation state true-> on, false -> off*/
    int         Mod_Freq;           /*AM modulation frequency in Hz*/
    int         Mod_Depth;          /* in % */
    int         Ampl_Voltage;       /* in mV*/

public:
    explicit InjCur(int Start = 0,int Stop = 0){
        Start_Freq = Start;
        Stop_Freq = Stop;
        Change_Freq = 1.01;             /*default 1%*/
        Time_Freq = 2000;               /*default 2000 miliseconds*/
        AM_Mod_State = true;            /*AM modulcation default state on*/
        Mod_Freq = 1000;                /*AM modulation frequency default 1kHz*/
        Mod_Depth = 80;                 /* default 80 % */
        Ampl_Voltage = 3000;            /* default 1000 mV*/
    }

    void set_StartFreq(int Start_Hz){Start_Freq = Start_Hz;}
    int get_StartFreq(void){return Start_Freq;}
    void set_StopFreq(int Stop_Hz){Stop_Freq = Stop_Hz;}
    int get_StopFreq(void){return Stop_Freq;}

    void set_ChageFreq(int perChange);
    double get_ChangeFreq(void){return Change_Freq;}

    void set_TimeFreq(int milisec){Time_Freq = milisec;}
    int get_TimeFreq(void){return Time_Freq;}

    void set_AMModState(bool state){AM_Mod_State = state;}
    bool get_AMModState(void){return AM_Mod_State;}

    void set_ModFreq(int ModFreq){Mod_Freq = ModFreq;}
    int get_ModFreq(void){return Mod_Freq;}

    void set_ModDepth(int ModDepth){Mod_Depth = ModDepth;}
    int get_ModDepth(void){return Mod_Depth;}

    void set_Amplitude(int Amp){Ampl_Voltage = Amp;}
    int get_Amplitude(void){return Ampl_Voltage;}



};

class VisaSession{

private:
    std::vector <InjCur> TestDev;
    ViSession	rm;               /*uniqe session ID got from Visa*/
    std::vector<ILogger*>     log;

public:
    VisaSession(void){rm = VI_NULL;}
    ~VisaSession(void);
    bool Visa_Init(void);
    void registerLogger(ILogger& logger);
    void PrintMsg(string msg);
    ViSession Add_device(ViSession &rm, std::string &desc){TestDev.push_back(InjCur());return (TestDev.back().connect_ToDevice(rm,desc));}
    /*bind for functor, design pattern delegate*/
};

#endif // InjCur.h
