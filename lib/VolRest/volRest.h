#ifndef VOREST_H_
#define VOREST_H_

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>



class VolRest{
    public:
        VolRest(); 
        String get(String str);
        int getDuration();
        String getHour();


    private:
        HTTPClient http;

        //JSON document
        
        //String for storing server response
        String response = "";
        int duration = 0;
};

#endif