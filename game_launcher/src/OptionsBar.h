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
#include "ofxXmlSettings.h"
#include "GameIcon.h"

#include "SortingButtonBase.h"
#include "SortingButtonToggle.h"
#include "SortingButtonNumber.h"

class OptionsBar{
public:
    
    void setup(ControllerManager * _controllerManager);
    void reset(GameIcon * _gameSelectedWhenOpened);
    void update(float deltaTime);
    void draw();
    
    void scrollSelection(int dir);
    
    bool checkGame(ofxXmlSettings gameXML);
    
    
    bool isActive;
    
    float timer;
    
    int curSelection;
    
    ControllerManager * controllerManager;
    
    bool isDone;
    
    
    GameIcon * gameSelectedWhenOpened;
    
    
    vector<SortingButtonBase *> sortingButtons;
    float sortingButtonSpacingY;
    
    ofVec2f sortingButtonPadding;
    
    bool sortGamesFlag;
    
    
    
};

#endif /* defined(__game_launcher__OptionsBar__) */
