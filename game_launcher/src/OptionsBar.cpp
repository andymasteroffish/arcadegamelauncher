//
//  OptionsBar.cpp
//  game_launcher
//
//  Created by Andy Wallace on 7/25/15.
//
//

#include "OptionsBar.h"


void OptionsBar::setup(ControllerManager * _controllerManager){
    controllerManager = _controllerManager;
    curSelection = 0;
}

void OptionsBar::reset(){
    isActive = true;
    isDone = false;
    timer = 0;
}

void OptionsBar::update(float deltaTime){
    timer += deltaTime;
    
    bool tryingToCancel = controllerManager->isButtonPressed(BUTTON_B) || controllerManager->isButtonPressed(BUTTON_Y);
    if ( tryingToCancel && timer >= MIN_TIME_BEFORE_CANCEL){
        isDone = true;
        isActive = false;
    }
}

void OptionsBar::draw(){
    
    if (isActive){
        
        ofSetColor(0, 45, 250);
        ofRect(ofGetWidth()-200, 0, 200, 600);
        
    }
    
}