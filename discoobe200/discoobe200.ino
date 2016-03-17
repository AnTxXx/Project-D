#include <RGBConverter.h>
#include <Adafruit_NeoPixel.h>
#include "Face.h"
#include "Patch.h"

#include <stdio.h>

//............................................NrOfPixel, Pin, Std.
Adafruit_NeoPixel areaTop    = Adafruit_NeoPixel(9, 13, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaNorth  = Adafruit_NeoPixel(9, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaEast   = Adafruit_NeoPixel(9, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaSouth   = Adafruit_NeoPixel(9, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaWest   = Adafruit_NeoPixel(9, 10, NEO_GRB + NEO_KHZ800);

RGBConverter colorConv;

Face fT('T',areaTop), fN('N', areaNorth), fS('S', areaSouth), fE('E', areaEast), fW('W', areaWest);
Patch pT0(fT,0), pT1(fT,1), pT2(fT,2), pT3(fT,3), pT4(fT,4), pT5(fT,5), pT6(fT,6), pT7(fT,7), pT8(fT,8);
Patch pN0(fN,0), pN1(fN,1), pN2(fN,2), pN3(fN,3), pN4(fN,4), pN5(fN,5), pN6(fN,6), pN7(fN,7), pN8(fN,8);
Patch pE0(fE,0), pE1(fE,1), pE2(fE,2), pE3(fE,3), pE4(fE,4), pE5(fE,5), pE6(fE,6), pE7(fE,7), pE8(fE,8);
Patch pS0(fS,0), pS1(fS,1), pS2(fS,2), pS3(fS,3), pS4(fS,4), pS5(fS,5), pS6(fS,6), pS7(fS,7), pS8(fS,8);
Patch pW0(fW,0), pW1(fW,1), pW2(fW,2), pW3(fW,3), pW4(fW,4), pW5(fW,5), pW6(fW,6), pW7(fW,7), pW8(fW,8);

int r,g,b;
double v = 0.0; //Helligkeit
double vSteps = 0.05; //Helligskeitsschritte

int nrOfSteps = 15; 
int waitMilliSeconds = 10;

int r0, g0, b0;
Patch *lastPatch=NULL, *nextPatch=NULL, *save=NULL;

// the setup function runs once when you press reset or power the board
void setup() {
  areaTop.begin();
  areaNorth.begin();
  areaEast.begin();
  areaSouth.begin();
  areaWest.begin();

  r = 255;
  g = 0;
  b = 0;
  Serial.begin(9600);
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for native USB port only
  //}

  // Zuweisung
  // TOP
  pT4.setUp(pT7);
  pT4.setDown(pT1);
  pT4.setLeft(pT5);
  pT4.setRight(pT3);
  pT6.setRight(pT7);
  pT6.setDown(pT5);
  pT6.setUp(pW8);
  pT6.setLeft(pS6);
  pT8.setLeft(pT7);
  pT8.setDown(pT3);
  pT8.setRight(pN8);
  pT8.setUp(pW6);
  pT0.setUp(pT5);
  pT0.setRight(pT1);
  pT0.setLeft(pS8);
  pT0.setDown(pE6);
  pT2.setUp(pT3);
  pT2.setLeft(pT1);
  pT2.setRight(pN6);
  pT2.setDown(pE8);
  pT7.setUp(pW7);
  
  // NORTH
  pN4.setLeft(pN7);
  pN4.setRight(pN1);
  pN4.setUp(pN3);
  pN4.setDown(pN5);
  pN6.setDown(pN8);
  pN6.setRight(pN5);
  pN6.setUp(pN7);
  pN8.setDown(pN7);
  pN8.setRight(pN3);
  pN0.setRight(pS2);
  pN0.setUp(pN1);
  pN0.setLeft(pN5);
  pN0.setDown(pN2);
  pN2.setRight(pS0);
  pN2.setDown(pN1);
  pN2.setLeft(pN3);
  pN1.setRight(pS1);
  pN5.setDown(pN3);

  // EAST
  pE4.setLeft(pE5);
  pE4.setUp(pE7);
  pE4.setRight(pE3);
  pE4.setDown(pE1);
  pE6.setLeft(pE8);
  pE6.setDown(pE5);
  pE6.setRight(pE7);
  pE8.setLeft(pE7);
  pE8.setDown(pE3);
  pE0.setLeft(pE2);
  pE0.setDown(pW2);
  pE0.setUp(pE5);
  pE2.setLeft(pE1);
  pE2.setDown(pW0);
  pE1.setDown(pW1);
  pN5.setLeft(pN3);

  // SOUTH
  pS4.setLeft(pS1);
  pS4.setUp(pS5);
  pS4.setRight(pS7);
  pS4.setDown(pS3);
  pS6.setLeft(pS5);
  pS6.setUp(pS8);
  pS6.setDown(pS7);
  pS8.setLeft(pS3);
  pS8.setUp(pS7);
  pS0.setDown(pS1);
  pS0.setRight(pS5);
  pS0.setUp(pS2);
  pS2.setRight(pS3);
  pS2.setUp(pS1);
  pS5.setUp(pS3);

  // WEST
  pW4.setLeft(pW3);
  pW4.setDown(pW7);
  pW4.setRight(pW5);
  pW4.setUp(pW1);
  pW6.setRight(pW8);
  pW6.setUp(pW5);
  pW6.setLeft(pW7);
  pW8.setUp(pW3);
  pW8.setRight(pW7);
  pW0.setLeft(pW1);
  pW0.setRight(pW2);
  pW0.setDown(pW5);
  pW2.setDown(pW3);
  pW2.setRight(pW1);
  pW5.setRight(pW3);

  lastPatch = &pT1;
  Serial.println("Discoobe is up and running");
}

unsigned long lastChange = 0.0;
bool pulseOn = false;
int pulseColorR = 0, pulseColorG = 0, pulseColorB = 0;
// the loop function runs over and over again forever

void loop() {
  //HERE IS THE PROBLEM
  //*save = *lastPatch;
  *nextPatch = *lastPatch->getUp();
  lastPatch->setActive(false);
  nextPatch->setRGB(255,0,0);
  *lastPatch = *nextPatch;
  delay(1200);
 /*
  int randi = rand() % 42;
  
  if(randi >39 && !pulseOn){
    pulseOn = true;
    lastChange = millis();
    pulseColorR = rand() % 255;
    pulseColorG = rand() % 255;
    pulseColorB = rand() % 255;
  }

  // 10 Sekunden pulsieren
  if(lastChange + 10000 < millis()){
    pulseOn = false;
  }

  // Beim Pulsieren muss die Farbe immer wieder gesetzt werden, sonst verändert sie sich
  if(pulseOn){
    r = pulseColorR;
    g = pulseColorG;
    b = pulseColorB;
    v = (v + vSteps);
    if(v > 0.95 || v < 0.05){
      vSteps = vSteps * (-1.0);
    }

    pulseColor(r, g, b, v);
    paintFace ('T', r, g, b);
    paintFace ('N', r, g, b);
    paintFace ('S', r, g, b);
    paintFace ('W', r, g, b);            
    paintFace ('E', r, g, b);    
    
    setCubeColors ();
    waitMilliSeconds = 100;  
    delay (waitMilliSeconds);
  } else {
    // Andere Muster außer Pulsieren
    r0 = rand() % 255;
    g0 = rand() % 255;
    b0 = rand() % 255;
  
    if (randi < 20) {    
        int row = rand() % 3;
        paintRow (row, r0, g0, b0);
    }
  
    if (randi>20)
      paintFace ('T', r0, g0, b0); else
    if (randi >23)
      paintFace ('N', r0, g0, b0); else
    if (randi >26)
      paintFace ('S', r0, g0, b0); else
    if (randi >29)
      paintFace ('W', r0, g0, b0); else   
    if (randi >32)
      paintFace ('E', r0, g0, b0); else
    setCubeColors ();
    
    if (randi >35){
      sequenceCarousel (166, r0, g0, b0);
      paintFace ('T', r0, g0, b0);
      paintFace ('N', r0, g0, b0);
      paintFace ('S', r0, g0, b0);
      paintFace ('W', r0, g0, b0);  
      paintFace ('E', r0, g0, b0);
      //setCubeColors();
    }

    waitMilliSeconds = 200 + rand() % 380;
    delay (waitMilliSeconds);
  }
  */
}

//
// 0...lowest row, 1...middle row, 2...top row
//
void paintRow (int row, int r, int g, int b)
{
  int ledBegin, ledEnd;
  if (row == 0) {
    ledBegin = 0;
    ledEnd = 2;
  } else if (row == 1) {
    ledBegin = 3;
    ledEnd = 5;
  } else if (row == 2) {
    ledBegin = 6;
    ledEnd = 8;
  }
  for (int i=ledBegin; i<=ledEnd; i++) {
      areaNorth.setPixelColor(i, r, g, b);
      areaEast.setPixelColor(i, r, g, b);
      areaSouth.setPixelColor(i, r, g, b);          
      areaWest.setPixelColor(i, r, g, b);                
  }
}

//
// T = Top, N = North, E = East, S = Sout, W = West
//
void paintFace (char c, int r, int g, int b)
{
  //
  int i;
  for (i=0; i<=8; i++) {
    if (c == 'T') 
      areaTop.setPixelColor(i, r, g, b);
    else if (c == 'N')
      areaNorth.setPixelColor(i, r, g, b);
    else if (c == 'E')
      areaEast.setPixelColor(i, r, g, b);
    else if (c == 'S')
      areaSouth.setPixelColor(i, r, g, b);            
    else if (c == 'W')
      areaWest.setPixelColor(i, r, g, b);                  
  }
}


void sequenceCarousel (int waitMs, int r0, int g0, int b0) {

  paintCarousel ('A', r0,g0,b0);
  setCubeColors ();
  delay (waitMs);

  paintCarousel ('A', 0,0,0);  
  paintCarousel ('B', r0,g0,b0);
  setCubeColors ();
  delay (waitMs);
  
  paintCarousel ('B', 0,0,0);  
  paintCarousel ('C', r0,g0,b0);
  setCubeColors ();
  delay (waitMs);

  paintCarousel ('C', 0,0,0);  
  paintCarousel ('D', r0,g0,b0);
  setCubeColors ();
  delay (waitMs);

  for (int i=0; i<2; i++) {
    paintCarousel ('D', 0,0,0);  
    paintCarousel ('A', r0,g0,b0);
    setCubeColors ();
    delay (waitMs);
  
    paintCarousel ('A', 0,0,0);  
    paintCarousel ('B', r0,g0,b0);
    setCubeColors ();
    delay (waitMs);
  
    paintCarousel ('B', 0,0,0);  
    paintCarousel ('C', r0,g0,b0);
    setCubeColors ();
    delay (waitMs);
  
    paintCarousel ('C', 0,0,0);  
    paintCarousel ('D', r0,g0,b0);
    setCubeColors ();
    delay (waitMs);
  }

  areaWest.setPixelColor(1, 0, 0, 0);
  setCubeColors ();
  delay (waitMs/7);
  areaWest.setPixelColor(4,  0, 0, 0);
  setCubeColors ();
  delay (waitMs/7);
  areaWest.setPixelColor(7,  0, 0, 0);     
  setCubeColors ();
  delay (waitMs/7);

  areaEast.setPixelColor(1,  0, 0, 0);    
  setCubeColors ();
  delay (waitMs/7);
  areaEast.setPixelColor(4,  0, 0, 0);    
  setCubeColors ();
  delay (waitMs/7);
  areaEast.setPixelColor(7,  0, 0, 0);     
  setCubeColors ();
  delay (waitMs/7);

  areaTop.setPixelColor(1,  0, 0, 0);
  setCubeColors ();
  delay (waitMs/7);
  areaTop.setPixelColor(4,  0, 0, 0);
  setCubeColors ();
  delay (waitMs/7);
  areaTop.setPixelColor(7, 0, 0, 0);
  setCubeColors ();
  delay (waitMs/7);
  
}
//
//
//
void paintCarousel (char c, int r, int g, int b)
{
    Serial.println("-paint");
    Serial.println(r);
    Serial.println(g);
    Serial.println(b); 
    if (c == 'A')
    {
      areaSouth.setPixelColor(0, r, g, b);
      areaSouth.setPixelColor(5, r, g, b);
      areaSouth.setPixelColor(6, r, g, b);      

      areaNorth.setPixelColor(0, r, g, b);     
      areaNorth.setPixelColor(5, r, g, b);     
      areaNorth.setPixelColor(6, r, g, b);     

      areaEast.setPixelColor(2, r, g, b);
      areaEast.setPixelColor(3, r, g, b);
      areaEast.setPixelColor(8, r, g, b);

      areaWest.setPixelColor(2, r, g, b);     
      areaWest.setPixelColor(3, r, g, b);     
      areaWest.setPixelColor(8, r, g, b);     

      areaTop.setPixelColor(2, r, g, b);
      areaTop.setPixelColor(4, r, g, b);
      areaTop.setPixelColor(6, r, g, b);
    }
    
    if (c == 'C')
    {
      areaSouth.setPixelColor(2, r, g, b);
      areaSouth.setPixelColor(3, r, g, b);
      areaSouth.setPixelColor(8, r, g, b);      

      areaNorth.setPixelColor(2, r, g, b);     
      areaNorth.setPixelColor(3, r, g, b);     
      areaNorth.setPixelColor(8, r, g, b);     

      areaEast.setPixelColor(0, r, g, b);
      areaEast.setPixelColor(5, r, g, b);
      areaEast.setPixelColor(6, r, g, b);

      areaWest.setPixelColor(0, r, g, b);     
      areaWest.setPixelColor(5, r, g, b);     
      areaWest.setPixelColor(6, r, g, b);     

      areaTop.setPixelColor(0, r, g, b);
      areaTop.setPixelColor(4, r, g, b);
      areaTop.setPixelColor(8, r, g, b);
    }

    if (c == 'B')
    {
      areaSouth.setPixelColor(1, r, g, b);
      areaSouth.setPixelColor(4, r, g, b);
      areaSouth.setPixelColor(7, r, g, b);      

      areaNorth.setPixelColor(1, r, g, b);     
      areaNorth.setPixelColor(4, r, g, b);     
      areaNorth.setPixelColor(7, r, g, b);     

      areaTop.setPixelColor(5, r, g, b);
      areaTop.setPixelColor(4, r, g, b);
      areaTop.setPixelColor(3, r, g, b);
    }

    if (c == 'D')
    {
      areaWest.setPixelColor(1, r, g, b);
      areaWest.setPixelColor(4, r, g, b);
      areaWest.setPixelColor(7, r, g, b);      

      areaEast.setPixelColor(1, r, g, b);     
      areaEast.setPixelColor(4, r, g, b);     
      areaEast.setPixelColor(7, r, g, b);     

      areaTop.setPixelColor(1, r, g, b);
      areaTop.setPixelColor(4, r, g, b);
      areaTop.setPixelColor(7, r, g, b);
    }

}

void paintArch (char c, int r, int g, int b)
{
    areaTop.setPixelColor(0, 0, 0, 0);
    areaTop.show();
}

//
//
//
void setCubeColors ()
{
    areaTop.show();
    areaNorth.show();
    areaEast.show();   
    areaSouth.show();   
    areaWest.show();   
}

//
//
//
void pulseColor (int &r, int &g, int &b, double v) // pulsateAColor
{
  double hsv[3];
  byte rgb[3];
  
  byte rB = r;
  byte gB = g;
  byte bB = b;
  
  colorConv.rgbToHsv(rB, gB, bB, hsv);
  //Serial.print(hsv[2]);
  colorConv.hsvToRgb(hsv[0], hsv[1], v, rgb);

  r = rgb[0];
  g = rgb[1];
  b = rgb[2];
}

//
//
//
int getImColor (int colorBegin, int colorEnd, int nrOfSteps, int i) // getIntermediateColor
{
  double diff = 0.0; 
  double step = 0.0; 
  int currentColor = 0;
  if (colorEnd > colorBegin) 
  {
    diff = colorEnd - colorBegin; // potentialle probleme.
    step = diff / nrOfSteps;
    currentColor = colorBegin + step * i;
  } 
  else 
  {
    diff = colorBegin - colorEnd;
    step = diff / nrOfSteps;
    currentColor = colorBegin - step * i;
  }
  Serial.print("diff = ");
  Serial.println(diff);
  Serial.print("step = ");
  Serial.println(step);
  Serial.print("currentColor = ");
  Serial.println(currentColor);

  return currentColor;
}




