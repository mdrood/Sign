#ifndef FIREBDB_H_
#define FIREBDB_H_

#include <Arduino.h>
#include <FirebaseESP32.h>

// Provide the token generation process info.
//#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#//include "addons/RTDBHelper.h"

#include "globalVar.h"

class Firebdb{
    public:
        void addFB(FirebaseData *fbo);
        //void getKeys();
        String getName(String key);
        String getColors();
        String getLetterColor();
        String getLetterHowmany();
        void writeKeyToDb(String key, String name);
        String getSunset();
    private:
        FirebaseData *fbdo;
        bool taskCompleted = false;
        //const char* folks[16] = {"MarkDane", "MarkMckay", "MarkJeff", "CaseyKyle", "DaneJeffMckay", "DaneJeff", "JeffKyle", "Casey", "Chris", "Dane", "Eric", "Jeff", "Kyle", "Mark", "McKay", "Nat"};
        int currentLen = 0;
        QueryFilter query;

};

#endif