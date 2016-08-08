#include "fakeSensor.h"

fakeSensorClass::fakeSensorClass(BlynkParticleClass *_guiStuff) {
    gui=_guiStuff;   
}
    
    
void fakeSensorClass::checkSensor() {
    if(random(100)>80 && (millis() - millisCounter > 250)) {
        millisCounter = millis();
        gui->updateSensor(millisCounter,random(10000));
    }        
}
    