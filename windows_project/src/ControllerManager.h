//
//  ControllerManager.h
//  game_launcher
//
//  Created by Andy Wallace on 7/25/15.
//
//

#ifndef __game_launcher__ControllerManager__
#define __game_launcher__ControllerManager__

#include "ofMain.h"
#include "BasicInfo.h"
#include "ofxGamepadHandler.h"

class ControllerManager{
public:

    //just dummy for now
    
    void setup();
    void update();
    
	void drawDebug();

    bool isButtonPressed(BUTTON_TYPE button);
    
    
    void keyPressed(int key);
    void keyReleased(int key);

	void axisChanged(ofxGamepadAxisEvent &e);
    void buttonPressed(ofxGamepadButtonEvent &e);
    
    
    bool justTapped[NUM_BUTTONS];

	//this needs to be expaded to take multiple gamepads into account. Just for testing right now
	bool axisCanTapLeft, axisCanTapRight, axisCanTapUp, axisCanTapDown;
    
};

#endif /* defined(__game_launcher__ControllerManager__) */
