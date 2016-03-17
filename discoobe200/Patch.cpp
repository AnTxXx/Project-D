#include "Patch.h";

Patch::Patch(Face &inpFace, int inpPosition){
	_face = &inpFace;
	setPosition(inpPosition);
	_left = NULL;
	_right = NULL;
	_up = NULL;
	_down = NULL;
}

void Patch::setActive(bool inpActive){
	_active = inpActive;
	if(_active) _face->getNeoPixelArea()->setPixelColor(_position,_r,_g,_b);
	else _face->getNeoPixelArea()->setPixelColor(_position,0,0,0);
	_face->getNeoPixelArea()->show();
}
