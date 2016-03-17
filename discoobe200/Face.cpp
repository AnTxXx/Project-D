#include "Face.h"

Face::Face(char inpCubePosition, Adafruit_NeoPixel &inpArea){
	setCubePosition(inpCubePosition);
	_area = &inpArea;
}

Face::Face(){
	
}

void Face::setCubePosition (char inpCubePosition) {
	_cubePosition = inpCubePosition;
}
