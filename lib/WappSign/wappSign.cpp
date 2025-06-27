#include "wappSign.h"

#define WIDTH 48 //old mark sign 55x10, Eric 54x10, Jeff 47x9, new mark sign 48x8
#define HEIGHT 8
#define PIN 5
#define NUMPIXELS (WIDTH * HEIGHT)

Adafruit_NeoPixel lightStrip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t colors[] = {
  lightStrip.Color(255, 0, 0),    // red
  lightStrip.Color(0, 255, 0),    // green
  lightStrip.Color(0, 0, 255),    // blue
  lightStrip.Color(255, 255, 0),  // yellow
  lightStrip.Color(0, 255, 255),  // cyan
  lightStrip.Color(255, 0, 255),  // magenta
  lightStrip.Color(255, 255, 255) // white
};

uint32_t textColor = lightStrip.Color(255, 255, 255);  // white

int scrollX = WIDTH;


void WappSign::brightness(int val){
    lightStrip.setBrightness(val);
}

void WappSign::display(String text){
    lightStrip.clear();
  
  drawMessage(text.c_str(), scrollX);
  lightStrip.show();
    int len = text.length();
  scrollX--;
if (scrollX < -(len * 6)) {
  scrollX = WIDTH;

  // rotate to next color
  colorIndex = (colorIndex + 1) % (sizeof(colors) / sizeof(colors[0]));
  textColor = colors[colorIndex];
  
}
}


WappSign::WappSign(){
    
  lightStrip.begin();
  lightStrip.clear();
  lightStrip.setBrightness(40);
  lightStrip.show();
}

int WappSign::getCharIndex(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A';          // uppercase A-Z (0-25)
  if (c >= '0' && c <= '9') return 26 + (c - '0');   // digits 0-9 (26-35)
  if (c == ' ') return 36;                            // space
  if (c == '!') return 37;                            // exclamation
  if (c >= 'a' && c <= 'z') return 39 + (c - 'a');   // lowercase a-z (39-64)
  return 38; // fallback blank (38)
}
// XY function for top-right origin, zigzag wiring:
// row0 left->right, row1 right->left, etc.
int WappSign::XY(int x, int y) {
  if (y % 2 == 0) {
    // even rows left to right
    return y * WIDTH + x;
  } else {
    // odd rows right to left
    return y * WIDTH + (WIDTH - 1 - x);
  }
}

uint8_t WappSign::flipVertical7(uint8_t b) {
  uint8_t r = 0;
  for (int i = 0; i < 7; i++) {
    if (b & (1 << i)) r |= (1 << (6 - i));
  }
  return r;
}

void WappSign::drawChar(char c, int xOffset) {
  int index = getCharIndex(c);
  if (index < 0) return;

  for (int x = 0; x < 5; x++) {
    int screenX = xOffset + x;
    if (screenX < 0 || screenX >= WIDTH) continue;

    uint8_t col = font5x7[index][x];

    // Flip exclamation mark vertically
   // if (index == 37) {
    //  col = flipVertical7(col);
    //}

    for (int y = 0; y < 7; y++) {
      if (col & (1 << y)) {
        lightStrip.setPixelColor(XY(screenX, y), textColor);
      } else {
        lightStrip.setPixelColor(XY(screenX, y), 0);
      }
    }
  }
}

void WappSign::drawMessage(const char *msg, int xOffset) {
  int len = strlen(msg);
  for (int i = 0; i < len; i++) {
    drawChar(msg[i], xOffset + i * 6);
  }
}