#include <localdb.h>
#include "globalVar.h"
#include <ArduinoJson.h>
String Localdb::findKeyAndExtractField(String key,File &file){
 
    String ret = "";
  //String person = "";
  //String yr = "";
  Serial.println("1");
 // Serial.print("doc is ");
  //Serial.println(doc.isNull());
  Serial.print("file is ");
  Serial.println(file.name());
  file.seek(0);  // ✅ rewind file before second read
 DeserializationError error = deserializeJson(doc, file);
  Serial.println("2");
  Serial.println(file.size());
  if (error) {
    Serial.print("JSON parse error: ");
    Serial.println(error.c_str());
    return "?";
  }

  // 🎯 Key to search
  
  // 🔍 Access "Songs" object
  JsonObject songs = doc["Songs"];

  if (!songs.containsKey(key)) {
    Serial.println("Key not found in Songs");
    return "?";
  }

  const char* person =  songs[key]["Person"];  // or .as<const char*>()
  const char* yr   = songs[key]["Year"];


  Serial.print("Person: ");
  Serial.println(person);
  Serial.print("Year: ");
  Serial.println(yr);
  ret = String(person) + ":" + yr;

    return ret;
}



