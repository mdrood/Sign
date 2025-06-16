#include "wappSign.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>




WappSign::WappSign(Firebdb *fire){
  fdb = fire;
  colors[0] = matrixx.Color(color7_1, color7_2, color7_3);
  colors[1] = matrixx.Color(249, 169, 8);
  colors[3] = matrixx.Color(249, 8, 8);
  matrixx.begin();
  matrixx.setTextWrap(false);
  matrixx.setBrightness(brightness);
  matrixx.setTextColor(colors[1]);
  xxxx  = matrixx.width();

}

void WappSign::setBrightness(int bright){
  brightness = bright;
}

void WappSign::display(String str, int length, bool internet){
  //length = (length+5)* -1;
  //Serial.println(length);

 //Serial.print("Howmany colors are : ");
 //Serial.println(intHowmany);

  matrixx.fillScreen(0);
  matrixx.setCursor(xxxx, 0);
  matrixx.setBrightness(brightness);
    matrixx.print(str);
  if(internet){
    if(--xxxx < length ) {
        xxxx = matrixx.width();
        if(++piss >= intHowmany) piss = 0;
       matrixx.setTextColor(colors[piss]);
    }
  }else{
    matrixx.setTextColor(colors[1]);
  }
    //Serial.println("got in sign almost doen");
  matrixx.show();

}

void WappSign::setColors(){
  String strColor = fdb->getLetterColor();
  //Serial.print("Color of text is : ");
  delay(100);
  //Serial.print(strColor);
   String strHowmany =  fdb->getLetterHowmany();
   //if(checkIfCharIsInt(strHowmany)){
  intHowmany = strHowmany.toInt();
  // }else{
   // intHowmany = 3;
  // }
  int color = 1;
  //if(checkIfCharIsInt(strColor)){
    color = strColor.toInt();
  //}else{
  //  color = 1;
  //}
 switch(color){    
      case 1 :  //aqua
        colors[0] = matrixx.Color(color1_1, color1_2, color1_3);
        colors[1] = matrixx.Color(color1_1, color1_2, color1_3);
        colors[2] = matrixx.Color(color1_1, color1_2, color1_3);

         break;
      case 2:  //blue
        colors[0] = matrixx.Color(color2_1, color2_2, color2_3);
        colors[1] = matrixx.Color(color2_1, color2_2, color2_3);
        colors[2] = matrixx.Color(color2_1, color2_2, color2_3);
         break;
      case 3:  //green
         colors[0] = matrixx.Color(color3_1, color3_2, color3_3);
         colors[1] = matrixx.Color(color3_1, color3_2, color3_3);
         colors[2] = matrixx.Color(color3_1, color3_2, color3_3);
        break;
      case 4:  //orange
        colors[0] = matrixx.Color(color4_1, color4_2, color4_3);
        colors[0] = matrixx.Color(color4_1, color4_2, color4_3);
        colors[0] = matrixx.Color(color4_1, color4_2, color4_3);
         break;
      case 5:  //purple
        colors[0] = matrixx.Color(color5_1, color5_2, color5_3);
        colors[1] = matrixx.Color(color5_1, color5_2, color5_3);
        colors[2] = matrixx.Color(color5_1, color5_2, color5_3);
         break;
      case 6:  //red
        colors[0] = matrixx.Color(color6_1, color6_2, color6_3);
        colors[1] = matrixx.Color(color6_1, color6_2, color6_3);
        colors[2] = matrixx.Color(color6_1, color6_2, color6_3);
         break;
      case 7:  //yellow
        colors[0] = matrixx.Color(color7_1, color7_2, color7_3);
        colors[1] = matrixx.Color(color7_1, color7_2, color7_3);
       colors[2] = matrixx.Color(color7_1, color7_2, color7_3);
         break;
      case 8:  //aqua,blue, green
        colors[0] = matrixx.Color(color1_1, color1_2, color1_3);
        colors[1] = matrixx.Color(color2_1, color2_2, color2_3);
        colors[2] = matrixx.Color(color3_1, color3_2, color3_3);
         break;
      case 9:  //orange,purple, red
        colors[0] = matrixx.Color(color4_1, color4_2, color4_3);
        colors[1] = matrixx.Color(color5_1, color5_2, color6_3);
        colors[2] = matrixx.Color(color6_1, color6_2, color6_3);
         break;
      case 10:  //yellow,orange, purple
        colors[0] = matrixx.Color(color7_1, color7_2, color7_3);
        colors[1] = matrixx.Color(color4_1, color4_2, color4_3);
        colors[2] = matrixx.Color(color5_1, color5_2, color5_3);
         break;
      case 11:  //aqua, yellow, orange
        colors[0] = matrixx.Color(color1_1, color1_2, color1_3);
        colors[1] = matrixx.Color(color7_1, color7_2, color7_3);
        colors[2] = matrixx.Color(color4_1, color4_2, color4_3);
         break;
      case 12:  //blue, aqua, yellow
        colors[0] = matrixx.Color(color2_1, color2_2, color2_3);
        colors[1] = matrixx.Color(color1_1, color1_2, color1_3);
        colors[2] = matrixx.Color(color7_1, color7_2, color7_3);
         break;
      case 13:  //green, blue, aqua
        colors[0] = matrixx.Color(color3_1, color3_2, color3_3);
        colors[1] = matrixx.Color(color2_1, color2_2, color2_3);
        colors[2] = matrixx.Color(color1_1, color1_2, color1_3);
         break;
      case 14:  //orange, green blue
        colors[0] = matrixx.Color(color4_1, color4_2, color4_3);
        colors[1] = matrixx.Color(color3_1, color3_2, color3_3);
        colors[2] = matrixx.Color(color2_1, color2_2, color2_3);
         break;
      case 15:  //purple, oragen, green
        colors[0] = matrixx.Color(color5_1, color5_2, color5_3);
        colors[1] = matrixx.Color(color4_1, color4_2, color4_3);
        colors[2] = matrixx.Color(color3_1, color3_2, color3_3);
         break;
      case 16:  //red, purpele, orange
        colors[0] = matrixx.Color(color6_1, color6_2, color6_3);
        colors[1] = matrixx.Color(color5_1, color5_2, color5_3);
        colors[2] = matrixx.Color(color4_1, color4_2, color4_3);
         break;
      case 17:  //yellow, red, purple
        colors[0] = matrixx.Color(color7_1, color7_2, color7_3);
        colors[1] = matrixx.Color(color6_1, color6_2, color6_3);
        colors[2] = matrixx.Color(color5_1, color5_2, color5_3);
         break;
      case 18:  //aqua, yellow, red
        colors[0] = matrixx.Color(color1_1, color1_2, color1_3);
        colors[2] = matrixx.Color(color7_1, color7_2, color7_3);
        colors[2] = matrixx.Color(color6_1, color6_2, color6_3);
         break;
      case 19:  //blue, aqua, yellow
        colors[0] = matrixx.Color(color2_1, color2_2, color2_3);
        colors[1] = matrixx.Color(color1_1, color1_2, color1_3);
        colors[2] = matrixx.Color(color7_1, color7_2, color7_3);
         break;
      case 20:  //green, blue, aqua
        colors[0] = matrixx.Color(color3_1, color3_2, color3_3);
        colors[1] = matrixx.Color(color2_1, color2_2, color2_3);
        colors[2] = matrixx.Color(color1_1, color1_2, color1_3);
         break;
      case 21:  //all colors
        allColors[0] = matrixx.Color(color3_1, color3_2, color3_3);
        allColors[1] = matrixx.Color(color2_1, color2_2, color2_3);
        allColors[2] = matrixx.Color(color1_1, color1_2, color1_3);
        allColors[3] = matrixx.Color(color3_1, color3_2, color3_3);
        allColors[4] = matrixx.Color(color2_1, color2_2, color2_3);
        allColors[5] = matrixx.Color(color1_1, color1_2, color1_3);
        allColors[6] = matrixx.Color(color3_1, color3_2, color3_3);
        allColors[7] = matrixx.Color(color2_1, color2_2, color2_3);
        allColors[8] = matrixx.Color(color1_1, color1_2, color1_3);
        allColors[9] = matrixx.Color(color3_1, color3_2, color3_3);
        allColors[10] = matrixx.Color(color2_1, color2_2, color2_3);
        allColors[11] = matrixx.Color(color1_1, color1_2, color1_3);
        allColors[12] = matrixx.Color(color3_1, color3_2, color3_3);
        allColors[13] = matrixx.Color(color2_1, color2_2, color2_3);
        allColors[14] = matrixx.Color(color1_1, color1_2, color1_3);
        allColors[15] = matrixx.Color(color3_1, color3_2, color3_3);
        allColors[16] = matrixx.Color(color2_1, color2_2, color2_3);
        allColors[17] = matrixx.Color(color1_1, color1_2, color1_3);
        allColors[18] = matrixx.Color(color3_1, color3_2, color3_3);
        allColors[19] = matrixx.Color(color2_1, color2_2, color2_3);
        allColors[20] = matrixx.Color(color1_1, color1_2, color1_3);
         break;
      case 22:  //green, red, aqua
        colors[0] = matrixx.Color(color3_1, color3_2, color3_3);
        colors[1] = matrixx.Color(color6_1, color6_2, color6_3);
        colors[2] = matrixx.Color(color1_1, color1_2, color1_3);
         break;
    default :
        colors[0] = matrixx.Color(color3_1, color3_2, color3_3);
        colors[1] = matrixx.Color(color2_1, color2_2, color2_3);
        colors[2] = matrixx.Color(color1_1, color1_2, color1_3);
   }
}


 bool WappSign::checkIfCharIsInt(String str){
  //bool retVal = false;
  char *buff[5];
  str.toCharArray(*buff,str.length(),0);
 for (int x = 0; x < strlen(*buff); ++x)
    {
        if (!isdigit(*buff[x])) return true;
    }
    return false;
}