/**
 * @file       BlynkSimpleParticle.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 *
 */

#ifndef bl_h
#define bl_h

#include "blynk/BlynkParticle.h"
#include "blynk/BlynkApi.h"

// BlynkParticle Blynk(_blynkTransport);

// static BlynkTransportParticle _blynkTransport;
// BlynkParticle Blynk(_blynkTransport);

//#include "blynk/BlynkWidgets.h"


#endif

/**
 * @file       WidgetTerminal.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jan 2015
 * @brief
 */

#ifndef WidgetTerminal_h
#define WidgetTerminal_h

#if !(defined(LINUX) || defined(MBED_LIBRARY_VERSION))
    #define BLYNK_USE_PRINT_CLASS
#endif


#ifdef BLYNK_USE_PRINT_CLASS
    #if !(defined(SPARK) || defined(PARTICLE) || (PLATFORM_ID==88) || defined(ARDUINO_RedBear_Duo)) // 88 -> RBL Duo
        // On Particle this is auto-included
        #include <Print.h>
    #endif
#endif

class WidgetTerminal
#ifdef BLYNK_USE_PRINT_CLASS
    : public Print
#endif
{
public:
    BlynkParticle *bl;
    
    WidgetTerminal() : mOutQty(0) {};
    
    WidgetTerminal(int vPin)
        : mPin(vPin), mOutQty(0) {};

    WidgetTerminal(BlynkParticle *_useBlynkObj, int vPin)
        : mPin(vPin), mOutQty(0) {bl = _useBlynkObj;}

    void setBlynk(BlynkParticle *_useThisBlynk) {bl=_useThisBlynk;}
    void setVPin(int vPin) { mPin = vPin; }


    virtual size_t write(uint8_t byte) {
        mOutBuf[mOutQty++] = byte;
        if (mOutQty >= sizeof(mOutBuf)) {
            flush();
        }
        return 1;
    }

    void flush() {
        if (mOutQty) {
            bl->virtualWriteBinary(mPin, mOutBuf, mOutQty);
            mOutQty = 0;
        }
    }

#ifdef BLYNK_USE_PRINT_CLASS

    using Print::write;

    size_t write(const void* buff, size_t len) {
        return write((char*)buff, len);
    }

#else

    size_t write(const void* buff, size_t len) {
        uint8_t* buf = (uint8_t*)buff;
        while (len--) {
            write(*buf++);
        }
        return len;
    }

    size_t write(const char* str) {
        return write(str, strlen(str));
    }

#endif

private:
    uint8_t mPin;
    uint8_t mOutBuf[32];
    uint8_t mOutQty;
};

#endif



/**
 * @file       WidgetLED.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Apr 2015
 * @brief
 */

#ifndef WidgetLED_h
#define WidgetLED_h

class WidgetLED
{
public:
    BlynkParticle *bl;
    
	WidgetLED(BlynkParticle *_useThisBlynk, uint8_t pin) : mPin(pin) {bl=_useThisBlynk;}
    void setVPin(int vPin) { mPin = vPin; }

#ifdef BLYNK_EXPERIMENTAL

    void setRGB(uint8_t r, uint8_t g, uint8_t b) {
        char mem[64] = "";
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("rgb");
        cmd.add(r);
        cmd.add(g);
        cmd.add(b);
        bl->.virtualWrite(mPin, cmd);
    }

    void setHSV(uint8_t h, uint8_t s, uint8_t v) {
        char mem[64] = "";
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("hsv");
        cmd.add(h);
        cmd.add(s);
        cmd.add(v);
        bl->virtualWrite(mPin, cmd);
    }

#endif

    uint8_t getValue() const {
        return mValue;
    }

    void setValue(uint8_t value) {
    	mValue = value;
        bl->virtualWrite(mPin, value);
    }

    void on() {
    	setValue(255);
    }

    void off() {
    	setValue(0);
    }

private:
    uint8_t mPin;
    uint8_t mValue;
};

#endif


/**
 * @file       WidgetLCD.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Mar 2015
 * @brief
 */

#ifndef WidgetLCD_ALT_h
#define WidgetLCD_ALT_h

class WidgetLCD_alt
{
public:

    BlynkParticle *bl;
    
    WidgetLCD_alt(BlynkParticle *_useThisBlynk, uint8_t pin) : mPin(pin) {bl=_useThisBlynk;}
    WidgetLCD_alt() {};

    void setBlynk(BlynkParticle *_useThisBlynk) {bl=_useThisBlynk;}
    void setVPin(int vPin) { mPin = vPin; }

    void clear() {
        bl->virtualWrite(mPin, "clr");
    }

    template<typename T>
    void print(int x, int y, const T& str) {
        char mem[64] = "";
        BlynkParam cmd(mem, 0, sizeof(mem));
        cmd.add("p");
        cmd.add(x);
        cmd.add(y);
        cmd.add(str);
        bl->virtualWrite(mPin, cmd);
    }

private:
    uint8_t mPin;
};

#endif