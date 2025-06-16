#include <firebdb.h>
#include <Arduino.h>

String Firebdb::getName(String key){
    FirebaseData fd;
    String person = "";
    String year = "";
      String parentPath = "Songs/"+ key+"/Person"; 

  Firebase.getString(fd, parentPath);
  Serial.println(fd.errorReason());
  /*while(!fd.dataAvailable() ){
    Firebase.getString(fd, parentPath);
    Serial.print("@");
    delay(100);
  }*/
  
  person = fd.stringData();
  parentPath = "Songs/"+ key+"/Year"; 
  delay(10);
  //Serial.println(parentPath);
  Firebase.getString(fd, parentPath);
  year = fd.stringData();
  delay(100);
  String retStr = person+" : "+year;
  fd.closeFile();
  fd.clear();
  return retStr;
}

String Firebdb::getSunset(){
    FirebaseData fd;
    String sunset = "";
    String parentPath = "WappSongs/Sunset"; 


  Firebase.getString(fd, parentPath);
  sunset = fd.stringData();

  delay(100);
  fd.closeFile();
  fd.clear();
  return sunset;
}



void Firebdb::addFB(FirebaseData *fbo){
    fbdo =  fbo;

}

void Firebdb::writeKeyToDb(String key, String name){  
  FirebaseData fd;
      String parentPath = "WappSongs/"+ key; 
  FirebaseJson json;
  json.toString(Serial, true);
  json.set("Year", "2003");
  json.set("Person", "Jeff");
  Firebase.setJSON(fd,parentPath,json);
    fd.closeFile();
  fd.clear();
  delay(100);
}

String Firebdb::getColors(){
  String colors[] = {"Aqua","Blue","Green","Orange","Purple","Red","Yellow"};
 // Serial.println("got to half");
    query.limitToLast(50);


for (int i = 0; i < 7; i++){
String myStr = String(colors[i]);
  String path = "WappSongs/Color";
  //Serial.println(path);    
    if (Firebase.ready()) //
    {
      //Serial.println("oh danny");
      //taskComplete = true;
      FirebaseData fdd;
  Firebase.getJSON(fdd,path , query);
//Serial.println("got to 1");
      // Success, then try to read the JSON payload value
      /////////////////////////////////////////////////////////
      //FirebaseJson *json = data.to<FirebaseJson *>();
      //Print all object data
      //Serial.println((const char *)FPSTR("Pretty printed JSON data:"));
      FirebaseJson &json = fdd.jsonObject();
      json.toString(Serial, true);

      size_t len = json.iteratorBegin();
      //Serial.print("size of json is ");
     // Serial.println(len);
     
      currentLen = len;
      FirebaseJson::IteratorValue value;
      FirebaseJsonData fjd;
      
      if(colors[i].equals("Aqua") ){
        for (size_t j = 0; j < len; j++)
        {
          if(j==0){
            json.get(fjd,"Aqua/One");
            int val = fjd.intValue;
            color1_1 = val;
            Serial.println(val);
          }else if(j==1){
             json.get(fjd,"Aqua/Two");
            int val = fjd.intValue;
            color1_2 = val;
            Serial.println(val);
          }else if(j==2){
             json.get(fjd,"Aqua/Three");
            int val = fjd.intValue;
            color1_3 = val;
            Serial.println(val);
          }
        }
      }else if (colors[i].equals( "Blue")){
        for (size_t j = 0; j < len; j++)
        {
          if(j==0){
             json.get(fjd,"Blue/One");
            int val = fjd.intValue;
            color2_1 = val;
            Serial.println(val);
          }else if(j==1){
             json.get(fjd,"Blue/Two");
            int val = fjd.intValue;
            color2_2 = val;
            Serial.println(val);
          }else if(j==2){
             json.get(fjd,"Blue/Three");
            int val = fjd.intValue;
            color2_3 = val;
            Serial.println(val);
          }
        }
      }else if (colors[i].equals("Green")){
        for (size_t j = 0; j < len; j++)
        {
          if(j==0){
             json.get(fjd,"Green/One");
            int val = fjd.intValue;
            color3_1 = val;
            Serial.println(val);
          }else if(j==1){
             json.get(fjd,"Green/Two");
            int val = fjd.intValue;
            color3_2 = val;
            Serial.println(val);
          }else if(j==2){
             json.get(fjd,"Green/Three");
            int val = fjd.intValue;
            color3_3 = val;
            Serial.println(val);
          }
        }
      }else if (colors[i].equals("Orange")){
        for (size_t j = 0; j < len; j++)
        {
          if(j==0){
             json.get(fjd,"Orange/One");
            int val = fjd.intValue;
            color4_1 = val;
            Serial.println(val);
          }else if(j==1){
             json.get(fjd,"Orange/Two");
            int val = fjd.intValue;
            color4_2 = val;
            Serial.println(val);
          }else if(j==2){
             json.get(fjd,"Orange/Three");
            int val = fjd.intValue;
            color4_3 = val;
            Serial.println(val);
          }
      }
    }else if (colors[i].equals("Purple")){
        for (size_t j = 0; j < len; j++)
        {
          if(j==0){
             json.get(fjd,"Purple/One");
            int val = fjd.intValue;
            color5_1 = val;
            Serial.println(val);
          }else if(j==1){
             json.get(fjd,"Purple/Two");
            int val = fjd.intValue;
            color5_2 = val;
            Serial.println(val);
          }else if(j==2){
             json.get(fjd,"Purple/Three");
            int val = fjd.intValue;
            color5_3 = val;
            Serial.println(val);
          }
        }
      }else if (colors[i].equals("Red")){
        for (size_t j = 0; j < len; j++)
        {
          if(j==0){
             json.get(fjd,"Red/One");
            int val = fjd.intValue;
            color6_1 = val;
            Serial.println(val);
          }else if(j==1){
             json.get(fjd,"Red/Two");
            int val = fjd.intValue;
            color6_2 = val;
            Serial.println(val);
          }else if(j==2){
             json.get(fjd,"Red/Three");
            int val = fjd.intValue;
            color6_3 = val;
            Serial.println(val);
          }
        }
      } else if (colors[i].equals("Yellow")){
        for (size_t j = 0; j < len; j++)
        {
          if(j==0){
             json.get(fjd,"Yello/One");
            int val = fjd.intValue;
            color7_1 = val;
            Serial.println(val);
          }else if(j==1){
             json.get(fjd,"Yellow/Two");
            int val = fjd.intValue;
            color7_2 = val;
            Serial.println(val);
          }else if(j==2){
             json.get(fjd,"Yellow/Three");
            int val = fjd.intValue;
            color7_3 = val;
            Serial.println(val);
          }
        }
      }
      fdd.closeFile();
      fdd.clear();
    }
}

return "";
}

//mine is just Color Howmany, Jeff's is jColor, jHowmany, Eric's is eColor, eHowmany

String Firebdb::getLetterColor(){
    FirebaseData fd;
    String color = "";
    
      String parentPath = "WappSongs/LetterColor/Settings/eColor";


  Firebase.getString(fd, parentPath);
  color = fd.stringData();

  //Serial.println(parentPath);
  Firebase.getString(fd, parentPath);
  color = fd.stringData();
  delay(100);
  fd.closeFile();
  fd.clear();
  return color;
}

String Firebdb::getLetterHowmany(){
    FirebaseData fd;
    String howmany = "";
    
      String parentPath = "WappSongs/LetterColor/Settings/eHowmany";


  Firebase.getString(fd, parentPath);
  howmany = fd.stringData();

  //Serial.println(parentPath);
  Firebase.getString(fd, parentPath);
  howmany = fd.stringData();
  delay(100);
  fd.closeFile();
  fd.clear();
  return howmany;  
}