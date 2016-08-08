#include "myBlynkLib.h"

BlynkParticleClass::BlynkParticleClass(BlynkParticle *_BlynkPrt) {
    Blynk = _BlynkPrt;   
    millisCounter = millis();
    
}
        

void BlynkParticleClass::begin(WidgetLCD_alt *_lcd) {
    lcd = _lcd;
    myOwnlcd.setBlynk(Blynk);
    myOwnlcd.setVPin(myOwnlcdPin);
} 

void BlynkParticleClass::update(uint8_t state) {
 
 char txt[16]; 

 switch(state) {
        
        case 2:
            lcd->print(1, 0, "Particle *LCD");
            sprintf(txt,"%06lu",counter[0]++);
            lcd->print(5,1,(char*)txt);
            break;
        
        case 3:
            myOwnlcd.print(1, 0, "Particle #LCD");
            sprintf(txt,"%06lu",counter[1]++);
            myOwnlcd.print(5,1,(char*)txt);
            break;
        }
    
}

void BlynkParticleClass::updateStuff() {
 
    if(millis() - millisCounter > 1000) {
 
        char txt[16]; 
        sprintf(txt,"Millis: %06lu",millisCounter);
    
        Blynk->virtualWrite(stuffPin,txt);
        millisCounter = millis(); 
 
    } 

}


void BlynkParticleClass::updateSensor(uint32_t ms, uint16_t value) {
        
        char txt[16]; 
        sprintf(txt,"Sensor: %6lu",value);
    
        Blynk->virtualWrite(sensorPin,txt);
   
}