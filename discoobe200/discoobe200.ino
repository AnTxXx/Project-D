
#include <Adafruit_NeoPixel.h>
#include <stdio.h>

//............................................NrOfPixel, Pin, Std.
Adafruit_NeoPixel areaTop    = Adafruit_NeoPixel(9, 13, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaNorth  = Adafruit_NeoPixel(9, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaEast   = Adafruit_NeoPixel(9, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaSouth   = Adafruit_NeoPixel(9, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel areaWest   = Adafruit_NeoPixel(9, 10, NEO_GRB + NEO_KHZ800);

int nrOfSteps = 15; 
int waitMilliSeconds = 10;
int r0, g0, b0;

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
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("blink on");
  
  r0 = rand() % 255;
  g0 = rand() % 255;
  b0 = rand() % 255;

  int r = rand() % 12;
  Serial.println(r);
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

  if (r == 10)
    sequenceCarousel (166, r0, g0, b0);
 
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




