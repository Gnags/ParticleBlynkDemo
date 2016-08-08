
#ifndef MYBLYNKLIB_H
#define MYBLYNKLIB_H


#include "blynk/BlynkParticle.h"
#include "widgets_alt.h"

#define myOwnlcdPin 13
#define stuffPin 14
#define sensorPin 15

class BlynkParticleClass {
    
    public:
        BlynkParticle *Blynk;
        WidgetLCD_alt *lcd;
        WidgetLCD_alt myOwnlcd;
        uint32_t counter[2];
        uint32_t millisCounter;
        
        BlynkParticleClass(BlynkParticle *_BlynkPrt);
        
        void begin(WidgetLCD_alt *_lcd);
        
        void update(uint8_t state);
        
        void updateStuff();
        
        void updateSensor(uint32_t ms, uint16_t value);
        
};

#endif