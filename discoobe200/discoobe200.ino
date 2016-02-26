
#include <Adafruit_NeoPixel.h>
#include <stdio.h>

//............................................NrOfPixel, Pin, Std.
Adafruit_NeoPixel areaTop    = Adafruit_NeoPixel(9, 13, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaNorth  = Adafruit_NeoPixel(9, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaEast   = Adafruit_NeoPixel(9, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaSouth   = Adafruit_NeoPixel(9, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaWest   = Adafruit_NeoPixel(9, 10, NEO_GRB + NEO_KHZ800);


long previousMillis = 0;
long onTime = 250;
long offTime = 750;

int nrOfSteps = 15; 
int waitMilliSeconds = 10;

//srand(time(NULL));

int r0 = rand() % 255;
int g0 = rand() % 255;
int b0 = rand() % 255;
int r1 = rand() % 255;
int g1 = rand() % 255;
int b1 = rand() % 255;
int r2 = rand() % 255;
int g2 = rand() % 255;
int b2 = rand() % 255;
int r3 = rand() % 255;
int g3 = rand() % 255;
int b3 = rand() % 255;



// the setup function runs once when you press reset or power the board
void setup() {
  areaTop.begin();
  areaNorth.begin();
  areaEast.begin();
  areaSouth.begin();
  areaWest.begin();
  Serial.begin(9600);
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for native USB port only
  //}
  Serial.println("Discoobe is up and running");

  //
}

// the loop function runs over and over again forever
void loop() {

  Serial.println("blink on");
  r0 = rand() % 255;
  g0 = rand() % 255;
  b0 = rand() % 255;

  int r = rand() % 10;
  if (r < 5) {    
      int row = rand() % 3;
      paintRow (row, r0, g0, b0);
  }

  if (r == 5)
    paintFace ('T', r0, g0, b0);
  if (r == 6)
    paintFace ('N', r0, g0, b0);
  if (r == 7)
    paintFace ('S', r0, g0, b0);
  if (r == 8)
    paintFace ('W', r0, g0, b0);            
  if (r == 9)
    paintFace ('E', r0, g0, b0);                

  setCubeColors ();
  
  waitMilliSeconds = 450 + rand() % 455;  
  delay (waitMilliSeconds);
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




