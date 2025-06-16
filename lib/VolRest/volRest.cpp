#include "volRest.h"
#include <HTTPClient.h>
#include <iostream>
#include "globalVar.h"

VolRest::VolRest(){

}

String VolRest::get(String request){
      //The API URL
  //String request;
  //Start the request
  
  http.begin(request);
  //Use HTTP GET request
  http.GET();
  //Response from server
  response = http.getString();
  //Serial.println(response);
  delay(10);
  if(response.equals(""))return "";
    //Parse JSON, read error if any
  DeserializationError error = deserializeJson(doc, response);
  delay(10);
// Test if parsing succeeds.
int z = 0;
while(error && z <= 10){
      z++;
      error = deserializeJson(doc, response);
      delay(10);
      if(error && z == 10){
        std::cerr << "deserializeJson() failed: " << error.c_str() << std::endl;
        return "";
      }
  }
  const char* title = doc["title"];
  const char* artist = doc["artist"];
  duration  = doc["duration"];
  
   String strTitle = String(title);
  String strArtist = String(artist);

  //const char space = ' ';
  //Print parsed value on Serial Monitor
  // Print values.
  //char result[1000];   // array to hold the result.

  //strcpy(result,title); // copy string one into the result.
  //strcat(result,space);
  //strcat(result,artist); // append string two to the result.
  //Serial.println(result);
  String result = strTitle+" "+strArtist;

  
  http.end();
  
    return result;

}

int VolRest::getDuration(){
  return duration;
}

//https://www.timeapi.io/api/Time/current/zone?timeZone=America/Chicago

/*String VolRest::getHour(){
      //The API URL
  //String request;
  //Start the request
  
  http.begin("https://www.timeapi.io/api/Time/current/zone?timeZone=America/Chicago");
  //Use HTTP GET request
  http.GET();
  //Response from server
  response = http.getString();
  Serial.println(response);
  delay(10);
  if(response.equals(""))return "";
    //Parse JSON, read error if any
  DeserializationError error = deserializeJson(doc, response);
  delay(10);
// Test if parsing succeeds.
int z = 0;
while(error && z <= 10){
      z++;
      error = deserializeJson(doc, response);
      delay(10);
      if(error && z == 10){
        Serial.println("herrrrrrrrrrrrrrrr");
        std::cerr << "deserializeJson() failed: " << error.c_str() << std::endl;
        return "";
      }
  }
  const char* hour = doc["hour"];
  
  
  
   String strHour = String(hour);
  

  //const char space = ' ';
  //Print parsed value on Serial Monitor
  // Print values.
  //char result[1000];   // array to hold the result.

  //strcpy(result,title); // copy string one into the result.
  //strcat(result,space);
  //strcat(result,artist); // append string two to the result.
  //Serial.println(result);
 

  
  http.end();
  
    return hour;

}*/

