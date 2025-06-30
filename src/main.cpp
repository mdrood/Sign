
/**
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: k_suwatchai@hotmail.com
 *
 * Github: https://github.com/mobizt/Firebase-ESP32
 *
 * Copyright (c) 2023 mobizt
 *
 */

 /////////////to get file off of volumio pi3 http://192.168.1.58:8082/3_5_23_24_wapp.json /////

#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <HTTPClient.h>

#include <SPIFFS.h>


#include "ESPAsyncWebServer.h"
#include "ESPAsyncWiFiManager.h"  

#include "firebdb.h"
#include "utility.h"
#include "wappSign.h"
#include "volRest.h"
#include "localdb.h"


DynamicJsonDocument doc(65536);

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

AsyncWebServer server(80);
DNSServer dns;
void configModeCallback (AsyncWiFiManager *myWiFiManager);

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>



// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyA9Tb-xbeCJzh9pAVq64kFP_mcwA4sbp-g"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://esp32-firebase-example-852b0-default-rtdb.firebaseio.com/" 

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "mmkkrood@aol.com"
#define USER_PASSWORD "Skippy"

        FirebaseData fbdo;

        FirebaseAuth auth;
        FirebaseConfig config;
Firebdb *fbdb;
String response = "";



Utility *util;

VolRest *volRest;
WappSign *sign;
bool pinOn = false;
String oldRet = "";
Localdb *localdb;
Firebdb *fire;

IPAddress serverIP;
bool internet = false;

File file;

bool start = true;
long startTime = 0;
int now = 0;
String ret = "";
String finalStr = "";
int len = 0;
int dur = 0;

//String newSTr = "Homeland Refugee The Flatlanders : ? : 2009";
#define FORMAT_LITTLEFS_IF_FAILED true

bool onbardPinOn = false;
    long hash = 0;
    String name = " ";

    

void setup()
{

  Serial.begin(115200);

    ///////////////////Start WiFi ///////////////////////////////////////
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  AsyncWiFiManager wifiManager(&server, &dns);
  //reset settings - for testing
  //wifiManager.resetSettings();
  //wifiManager.setSTAStaticIPConfig(IPAddress(192,168,1,175), IPAddress(192,168,1,1), IPAddress(255,255,255,0), IPAddress(192,168,1,1), IPAddress(192,168,1,1));
  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("Wapp_Sign")) {
    Serial.println("failed to connect and hit timeout");
    Serial.println("restarting esp");
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();
    delay(1000);
  }
  delay(50);
  //Serial.print("FreeHeap is :");
  //Serial.println(ESP.getFreeHeap());
  delay(50);
  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");

  Serial.println("local ip");
  Serial.println(WiFi.localIP());

  server.begin();
///        Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

   pinMode(2,OUTPUT);
 digitalWrite(2,HIGH);
 localdb = new Localdb();
  fire = new Firebdb();


 sign = new WappSign();
 util = new Utility(sign);
 volRest = new VolRest();

 int intHour = util->getHour();
 String strHour = String(intHour);
 //util->writeFile(LittleFS,"/hour.txt",strHour.c_str());

/////////////////////////   THIS IS WHERE I CHECK IF WE HAVE INTERNET OR JUST WIFI  ///////////

if (WiFi.status() == WL_CONNECTED) {
  if (WiFi.hostByName("google.com", serverIP) != _NULL) {
    internet = true;
      Serial.println("Google.com resolved!");
        // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
      Firebase.reconnectNetwork(true);

    // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
    // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
      fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

    // Or use legacy authenticate method
    // config.database_url = DATABASE_URL;
    // config.signer.tokens.legacy_token = "<database secret>";

    // To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
    // otherwise the SSL connection will fail.
    //////////////////////////////////////////////////////////////////////////////////////////////

      Firebase.begin(&config, &auth);

      Firebase.setDoubleDigits(5);
      Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    // You can use TCP KeepAlive in FirebaseData object and tracking the server connection status, please read this for detail.
    // https://github.com/mobizt/Firebase-ESP32#about-firebasedata-object
    // fbdo.keepAlive(5, 5, 1);

    /** Timeout options.

    //Network reconnect timeout (interval) in ms (10 sec - 5 min) when network or WiFi disconnected.
    config.timeout.networkReconnect = 10 * 1000;

    //Socket connection and SSL handshake timeout in ms (1 sec - 1 min).
    config.timeout.socketConnection = 10 * 1000;

    //Server response read timeout in ms (1 sec - 1 min).
    config.timeout.serverResponse = 10 * 1000;

    //RTDB Stream keep-alive timeout in ms (20 sec - 2 min) when no server's keep-alive event data received.
    config.timeout.rtdbKeepAlive = 45 * 1000;

    //RTDB Stream reconnect timeout (interval) in ms (1 sec - 1 min) when RTDB Stream closed and want to resume.
    config.timeout.rtdbStreamReconnect = 1 * 1000;

    //RTDB Stream error notification timeout (interval) in ms (3 sec - 30 sec). It determines how often the readStream
    //will return false (error) when it called repeatedly in loop.
    config.timeout.rtdbStreamError = 3 * 1000;

    Note:
    The function that starting the new TCP session i.e. first time server connection or previous session was closed, the function won't exit until the
    time of config.timeout.socketConnection.

    You can also set the TCP data sending retry with
    config.tcp_data_sending_retry = 1;

    */
    ///String colo =  fire->getColors(); 
    ///String sunset = fire->getSunset();
    Serial.print("Sunset is ");
     //&&&&&&&&&&&&&&&&&&&sign->setColors();  //calls db to get the color
   // Serial.println(sunset);
  } else{
    internet = false;
     if (!SPIFFS.begin(false)) {  // 'true' will auto-format if mount fails
    Serial.println("SPIFFS Mount Failed");
    return;
  }else{
    Serial.println("SPIFFS mounted successfully");
  }

    file = SPIFFS.open("/3_5_23_24_wapp.json");
    if (!file) {
      Serial.println("Failed to open wapp.json");
      return;
    }else{
      Serial.print("Spiffs size is ");
      Serial.println(file.size());
    }
      Serial.println("Could not resolve google.com");
  }
}




 //LittleFS.format();  // ⚠️ Only run once to wipe flash!


 




 //fbdb->addFB(&fbdo);
 //fbdb->getKeys();

}

void loop()
{
  // put your main code here, to run repeatedly:
  if(onbardPinOn){
    digitalWrite(2,LOW);
    onbardPinOn = false;
    Serial.print("");
  }else{
    digitalWrite(2,HIGH);
    onbardPinOn = true;
     Serial.print("");
 }
  
  ////////////////////test get volumio rest stuff ////////
        if(start){
            startTime = millis();
            
            ret = volRest->get("http://crankit.local/api/v1/getState");
            //ret = volRest->get("http://192.168.1.65/api/v1/getState");
            //Serial.println("called start rest");
            if(ret.equals("")){
              ret = oldRet;
            }
            start = false;
            
        }else{

            if(millis() - startTime >= dur){
              ret = volRest->get("http://crankit.local/api/v1/getState");
              //ret = volRest->get("http://192.168.1.65/api/v1/getState");
              //Serial.println("Called dur rest");
            if(ret.equals("")){
              ret = oldRet;
            }
               start = true;
               
            }


        }
    
  
  //Serial.println(ret);
  if(!ret.equals(oldRet) ){
    oldRet = ret;
    String strSunset = fire->getSunset();
    int sunset = strSunset.toInt();
    ///util->checkSunset(sunset);
      //Firebase.begin(&config, &auth);
   // }
   // Serial.println("got here");
    //dur = volRest->getDuration(); //don't want to call until songs
    //dur = dur*1000;
    dur = 2000;
   
      

    ////////////////////////////////////////////
    //  Testing title number
    Serial.println("internet is "+internet);
      Serial.println(ret);
      //String  mystr = "After the Gold Rush (Live from Calgary, AL. 2023)";
//Serial.println("got here2");
        
        //int key = util->generateHash(ret);this was the old hash
        String key = util->generateUniqueKey(&ret,1);
        Serial.println(key); 
        //name = util->buildDisplayString(key);
       // String strKey = String(key); old way
       Serial.println("internet is "+internet);
       if(internet==true){
        Serial.println("in internet true");
        name = fire->getName(key);
       }else{
        Serial.println("in internet false");
        ///do off line stuff name = local->getName(key)
        name = localdb->findKeyAndExtractField(key, file);
       }
        Serial.print("name is ");
        Serial.println(name);
        if(name.equals("")){
          ESP.restart();
        }
        //String keyStr = String(key);

        //Serial.print(",");
        
        //ret.concat(name);
       // Serial.println("got here3");
        finalStr = ret+" : "+name;
        //Serial.println(ret);
        len = finalStr.length();
        len = len*6;
        len = len-1;
        //Serial.println("got here3");


        String lenStr = String (len);
        //Serial.println(lenStr);
       // Serial.println(finalStr);
        
       // for(int j=0;j<10;j++){
        //hash = util->generateHash(ret);
        //Serial.print("Hash is : ");
        
          //Serial.println(hash);
        //  delay(1000);
        //}
       // fire->writeKeyToDb(String(key), name);

  }    
  

  //Serial.print("STring lenghth is ");
  //Serial.println(len);
 // Serial.println("should be displaying :"+finalStr);
  sign->display(finalStr);
  //sign->display(newSTr,myLen);

///  if (Firebase.isTokenExpired()){
///    Firebase.refreshToken(&config);
///    Serial.println("Refresh token");
///  }

    delay(40);

//sign->display("Howdy",36);

}


/////////////////////////////////////////////////////////////
void configModeCallback (AsyncWiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  //myWiFiManager->startConfigPortal("ATOAWC");addDailyDoseAmt
  //myWiFiManager->autoConnect("DOSER");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());

}