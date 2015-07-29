//
//  ControllerManager.cpp
//  game_launcher
//
//  Created by Andy Wallace on 7/25/15.
//
//

#include "ControllerManager.h"


void ControllerManager::setup(){
#ifdef USING_WIN
	ofxGamepadHandler::get()->enableHotplug();
    
	 if(ofxGamepadHandler::get()->getNumPads()>0){
			ofxGamepad* pad = ofxGamepadHandler::get()->getGamepad(0);
            
			ofAddListener(pad->onAxisChanged, this, &ControllerManager::axisChanged);
			ofAddListener(pad->onButtonPressed, this, &ControllerManager::buttonPressed);
	 }
#endif

	 for (int i=0; i<NUM_BUTTONS; i++){
		 justTapped[i] = false;
	 }

	 axisCanTapUp = false;
	 axisCanTapDown = false;
	 axisCanTapLeft = false;
	 axisCanTapRight = false;
}


void ControllerManager::update(){
        //this is where you check what the analog sticks are doing
}

void ControllerManager::drawDebug(){
#ifdef USING_WIN
    ofxGamepadHandler::get()->draw(10,10);
#endif
}


bool ControllerManager::isButtonPressed(BUTTON_TYPE button){
    if (justTapped[button]){
        justTapped[button] = false; //turn it off before we leave
        return true;
    }
    return false;
}


void ControllerManager::keyPressed(int key){
    if (key == 357){
        justTapped[BUTTON_UP] = true;
    }
    if (key == 359){
        justTapped[BUTTON_DOWN] = true;
    }
    if (key == 356){
        justTapped[BUTTON_LEFT] = true;
    }
    if (key == 358){
        justTapped[BUTTON_RIGHT] = true;
    }
    
    if (key == ' ' || key == 13){
        justTapped[BUTTON_A] = true;
    }
    
    if (key == 'y'){
        justTapped[BUTTON_Y] = true;
    }
    if (key == 127){    //del
        justTapped[BUTTON_B] = true;
    }
    
    //cout<<"key "<<key<<endl;
}

void ControllerManager::keyReleased(int key){
    
}


#ifdef USING_WIN
//--------------------------------------------------------------
void ControllerManager::axisChanged(ofxGamepadAxisEvent& e)
{
	float restVal = 0.1f;
	float tapVal = 0.9f;
	
	if (e.axis == 0){
		if ( abs(e.value) < restVal ){
			axisCanTapUp = true;
			axisCanTapDown = true;
		}
		if (e.value > tapVal && axisCanTapUp){
			axisCanTapDown = false;
			justTapped[BUTTON_DOWN] = true;
		}
		if (e.value < tapVal && axisCanTapUp){
			axisCanTapUp = false;
			justTapped[BUTTON_UP] = true;
		}
	}
	
	if (e.axis == 1){
		if ( abs(e.value) < restVal ){
			axisCanTapLeft = true;
			axisCanTapRight = true;
		}
		if (e.value > tapVal && axisCanTapRight){
			axisCanTapRight = false;
			justTapped[BUTTON_RIGHT] = true;
		}
		if (e.value < tapVal && axisCanTapLeft){
			axisCanTapLeft = false;
			justTapped[BUTTON_LEFT] = true;
		}
	}
}

void ControllerManager::buttonPressed(ofxGamepadButtonEvent& e)
{
	if (e.button == 0){
		justTapped[BUTTON_A] = true;
	}
	if (e.button == 1){
		justTapped[BUTTON_A] = true;
	}
	if (e.button == 2){
		justTapped[BUTTON_X] = true;
	}
	if (e.button == 3){
		justTapped[BUTTON_Y] = true;
	}
}

#endif
