/*
  Face.h
*/
#ifndef Face_h
#define Face_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

class Face {
	public:
		Face();
		Face(char inpCubePosition, Adafruit_NeoPixel &inpArea);
		
		char getCubePosition(){return _cubePosition;}
		
		void setCubePosition(char inpCubePosition);
		//void setNeoPixelArea(Adafruit_NeoPixel &inpArea){_area = inpArea;}
		Adafruit_NeoPixel* getNeoPixelArea(){return _area;}
	private:
		char _cubePosition;
		Adafruit_NeoPixel* _area;
  };

#endif