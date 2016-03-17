/*
  Patch.h
*/
#ifndef Patch_h
#define Patch_h

#include "Arduino.h"
#include "Face.h"

class Patch {
    
	public:
		Patch(Face &inpFace, int inpPosition);
		
		void setFace(Face &inpFace){_face = &inpFace;}
		Face *getFace(){return _face;}
		int getPosition(){return _position;}
		
		Patch *getLeft(){return _left;}
		Patch *getRight() {return _right;}
		Patch *getUp(){return _up;}
		Patch *getDown(){return _down;}
		
		void setLeft(Patch &inpLeft){_left = &inpLeft; if(_left->getRight()==NULL) _left->setRight(*this);}
		void setRight(Patch &inpRight) {_right = &inpRight; if(_right->getLeft()==NULL) _right->setLeft(*this);}
		void setUp(Patch &inpUp) {_up = &inpUp; if(_up->getDown()==NULL) _up->setDown(*this);}
		void setDown(Patch &inpDown) {_down = &inpDown; if(_down->getUp()==NULL) _down->setUp(*this);}
		void setPosition(int inpPosition) {_position = inpPosition;}
		void setRGB(byte inpR, byte inpG, byte inpB, bool active = true) {_r = inpR; _g = inpG; _b = inpB; setActive(active);}
		void setActive(bool inpActive);
	private:
		Face *_face;
		Patch *_left, *_right, *_up, *_down;
		int _position;
		byte _r,_g,_b;
		bool _active;

  };
  
#endif