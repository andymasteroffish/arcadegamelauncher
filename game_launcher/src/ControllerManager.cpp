//
//  ControllerManager.cpp
//  game_launcher
//
//  Created by Andy Wallace on 7/25/15.
//
//

#include "ControllerManager.h"


void ControllerManager::setup(){

}


void ControllerManager::update(){
        //this is where you check what the analog sticks are doing
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