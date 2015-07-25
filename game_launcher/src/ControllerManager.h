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


class ControllerManager{
public:

    //just dummy for now
    
    void setup();
    void update();
    
    bool isButtonPressed(BUTTON_TYPE button);
    
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    
    bool justTapped[NUM_BUTTONS];
    
};

#endif /* defined(__game_launcher__ControllerManager__) */
