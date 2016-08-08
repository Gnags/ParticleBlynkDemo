
#ifndef FAKESENSOR_H
#define FAKESENSOR_H

#include "myBlynkLib.h"




class fakeSensorClass {
    
    public:
        
        BlynkParticleClass *gui;
        
        uint32_t millisCounter;
        
        
        fakeSensorClass(BlynkParticleClass *_guiStuff);
        
        
        
        void checkSensor();
        
        
};

#endif