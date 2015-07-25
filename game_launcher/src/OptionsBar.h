//
//  OptionsBar.h
//  game_launcher
//
//  Created by Andy Wallace on 7/25/15.
//
//

#ifndef __game_launcher__OptionsBar__
#define __game_launcher__OptionsBar__

#include "ofMain.h"
#include "ControllerManager.h"

class OptionsBar{
public:
    
    void setup(ControllerManager * _controllerManager);
    void reset();
    void update(float deltaTime);
    void draw();
    
    
    bool isActive;
    
    float timer;
    
    int curSelection;
    
    ControllerManager * controllerManager;
    
    bool isDone;
    
    
};

#endif /* defined(__game_launcher__OptionsBar__) */
