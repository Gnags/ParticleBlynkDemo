/*
    Use a auth token connected to a Blynk App with
    4 LCD widgets using Vpins 10, 11, 12 & 13 in advanced mode
    and two value object connected to vPin 14 & 15.
    
    This example show different way of arranging Blynk code in an project build using the Particle Build portal.
    
    The important part is in the widgets_alt.h by "replacing" 
    
        Blynk.virtualWrite(mPin, cmd);
    
    with
    
        bl->virtualWrite(mPin, cmd);
    
    This is not a strong implemenation bc we know have to diffrent widget classes for each widget, and bc 
    the widgets_alt.h is not maintained/supported through the Blynk organisation. 

*/

#include "blynk/blynk.h"
#include "widgets_alt.h"
#include "myBlynkLib.h"
#include "fakeSensor.h"

char auth[] = "df9d2c622f3d42b0bf3eb63e2bd85c48";

WidgetLCD lcd0(V10); // normal Blynk LCD
WidgetLCD_alt lcd1(&Blynk, V11); // alternative widgets class, not depending on knowing blynkObject
WidgetLCD_alt lcd2(&Blynk, V12); // lcd2 will be "operated" by my custom class

/*
    Declaration of lcd1 & lcd2 is parsing Blynk and vPin to construtor, but could be
    declared without arguments and using 'setBlynk' and 'setVpin'.
    Se exemple in myBlynkLib.
    
*/


BlynkParticleClass ParticleBlynk(&Blynk); // my own Blynk class, keeps a pointer to the Blynk object

fakeSensorClass fakeSensor(&ParticleBlynk);

void setup() {
    
    Blynk.begin(auth);

    while (Blynk.connect() == false) { 
       delay(10);
    }

    // parse pointer to LCD, so ParticleBlynk can handle blynk stuff 
    ParticleBlynk.begin(&lcd2);

}

// stuff so we to something to send to Blynk
uint32_t lastBlynkMillis=0;
uint32_t counter[] = {0,0,0,0};
uint8_t stateCount = 0;
 
void loop() {

    Blynk.run();

    ParticleBlynk.updateStuff();
        
    fakeSensor.checkSensor();
  
    if(millis() - lastBlynkMillis > 1000) {

        char txt[16]; 
        
        uint8_t state = stateCount % 4;
        
        switch(state % 4) {
        
            case 0: // update the normal LCD widget connected to pin V10
                lcd0.print(1, 0, "Normal LCD");
                sprintf(txt,"%06lu",counter[0]++);
                lcd0.print(5,1,(char*)txt);
                break;
        
            case 1: // update the alternative LCD widget connected to pin V11
                lcd1.print(1, 0, "alternative LCD");
                sprintf(txt,"%06lu",counter[1]++);
                lcd1.print(5,1,(char*)txt);
                break;
        
            case 2: // let ParticleBlynk do what ever Blynk stuff is needed
            case 3:
                ParticleBlynk.update(state);

        }

        lastBlynkMillis = millis();
        stateCount++;
    }
  
}
