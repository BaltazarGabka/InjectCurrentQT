#include "InjCur.h"
#include <memory.h>


bool VisaSession::Visa_Init(void){

    string      msg, temp_string;
    char        buffor[256],desc[256];
    ViStatus    status;
    ViFindList  list;
    ViUInt32	itemCnt = 0;

    status = viOpenDefaultRM(&rm);
    if (status < VI_SUCCESS) {
        PrintMsg("Could not connect to Visa check Visa");
        return false;
    }

    PrintMsg("Visa Session opened");

    //temp_string = "USB?*INSTR";
    temp_string = "?*INSTR";
    memset(buffor, 0, sizeof(buffor));
    temp_string.copy(buffor,temp_string.size());

    status = viFindRsrc(rm, buffor, &list, &itemCnt, desc);
    if (status < VI_SUCCESS) {
        PrintMsg("Could not find any devices");
        return false;
    }

    /*
    temp_string.str(buffor,)

    while (itemCnt > 0){
        Add_device(rm, )
    }
    */

    return true;
}

void VisaSession::PrintMsg(string msg){
    for(auto loger: log){
        loger->put(msg);
    }
}

void  VisaSession::registerLogger(ILogger& logger)
{
    log.push_back(&logger);
}

ViStatus VisaDevice::connect_ToDevice(ViSession&rm, string& desc){
    ViStatus temp_status;
    char desc_buffer[256];

    desc.copy(desc_buffer,desc.size()-1);

    temp_status = viOpen(rm, desc_buffer, VI_NULL, VI_NULL, &vi);

    if (temp_status <  VI_SUCCESS) {
        status = disconnected;
    }
    else{
        status = connected;
    }

        return temp_status;
}

VisaSession::~VisaSession(){
        viClose(rm);
}
