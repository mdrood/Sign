#ifndef WAPPSIGN_H_
#define WAPPSIGN_H_

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include "globalVar.h"
#include "firebdb.h"

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 5
                //ERIC 54 x 10
                //Jeff 47 x 9
                //Mark 55 x 10

 static Adafruit_NeoMatrix matrixx = Adafruit_NeoMatrix(48, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);






class WappSign{
    public:
        WappSign(Firebdb *fire);
        void display(String str, int length, bool interner);
        void setColors();
        bool checkIfCharIsInt(String str);
        void setBrightness(int bright);

    private:
      Firebdb *fdb;
      int xxxx = 0;
        int piss = 0;
        uint16_t colors[3];
        uint16_t allColors[20];
        int intHowmany = 3;
        int brightness = 40;

};

#endif