#ifndef UTILITY_H_
#define UTILITY_H_

#include <Arduino.h>
#include <time.h>
#include <LittleFS.h>
#include "wappSign.h"
#include "mbedtls/sha256.h"



class Utility{
    public:
        Utility(WappSign *si); 
        //int getKey(String str);
        //int alphabitPos(String str);
        //String buildDisplayString(int key);
        long generateHash(String str);
        int getHour();
        String readFile(fs::FS &fs, const char * path);
        void writeFile(fs::FS &fs, const char * path, const char * message);
        bool checkSunset(int sunset);
        String generateUniqueKey(const String* strings, size_t count);
        String** getJason(String payload);
    private:
        WappSign *sign;
        const char* ntpServer = "pool.ntp.org";
        const long gmtOffset_sec = -25200;
        struct tm timeinfo;
        int k = 0;
        bool setDaytime = false;
        bool setNightime = false;
        bool daytime = false;
        bool nightime = false;
        const char* scriptURL = "https://script.google.com/macros/s/AKfycbwDg3VKdvr4zorMlNWHOI-wjuPs30x7zNIJpTJfRCmjm_rYLfD6vLKVBnCLhap0d7dm/exec";
   
};

#endif