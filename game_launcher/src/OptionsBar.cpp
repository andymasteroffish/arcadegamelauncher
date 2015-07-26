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
    
    sortingButtonSpacingY = 30;
    sortingButtonPadding.set(30, 50);
    
    //make our buttons
    {
        SortingButtonToggle * newButton = new SortingButtonToggle();
        newButton->setup("Co-op", "COOP");
        sortingButtons.push_back(newButton);
    }
    {
        SortingButtonToggle * newButton = new SortingButtonToggle();
        newButton->setup("Competitive", "COMPETITIVE");
        sortingButtons.push_back(newButton);
    }
    {
        SortingButtonNumber * newButton = new SortingButtonNumber();
        newButton->setup("Num Players", "MIN_PLAYERS", "MAX_PLAYERS", 16);
        sortingButtons.push_back(newButton);
    }
}

void OptionsBar::reset(GameIcon * _gameSelectedWhenOpened){
    isActive = true;
    isDone = false;
    timer = 0;
    sortGamesFlag = false;
    gameSelectedWhenOpened = _gameSelectedWhenOpened;
}

void OptionsBar::update(float deltaTime){
    timer += deltaTime;
    
    //are they cancelling?
    bool tryingToCancel = controllerManager->isButtonPressed(BUTTON_B) || controllerManager->isButtonPressed(BUTTON_Y);
    if ( tryingToCancel && timer >= MIN_TIME_BEFORE_CANCEL){
        isDone = true;
        isActive = false;
    }
    
    //maybe changing an option?
    if (controllerManager->isButtonPressed(BUTTON_LEFT)){
        sortingButtons[curSelection]->buttonPressed(BUTTON_LEFT);
        sortGamesFlag = true;
    }
    if (controllerManager->isButtonPressed(BUTTON_RIGHT)){
        sortingButtons[curSelection]->buttonPressed(BUTTON_RIGHT);
        sortGamesFlag = true;
    }
    if (controllerManager->isButtonPressed(BUTTON_A)){
        sortingButtons[curSelection]->buttonPressed(BUTTON_A);
        sortGamesFlag = true;
    }
    
    //maybe moving up and down
    if (controllerManager->isButtonPressed(BUTTON_UP)){
        scrollSelection(-1);
    }
    if (controllerManager->isButtonPressed(BUTTON_DOWN)){
        scrollSelection(1);
    }
    
    for (int i=0; i<sortingButtons.size(); i++){
        sortingButtons[i]->update(deltaTime);
    }
}

void OptionsBar::scrollSelection(int dir){
    curSelection += dir;
    if (curSelection < 0){
        curSelection += sortingButtons.size();
    }
    if (curSelection >= sortingButtons.size()){
        curSelection -= sortingButtons.size();
    }
}

void OptionsBar::draw(){
    
    float width = 200;
    ofVec2f pos(ofGetWidth()-width, 30);
    
    float leftPadding = 30;
    
    if (isActive){
        
        ofSetColor(0, 45, 250);
        ofRect(pos.x, pos.y, width, 600);
        
        for (int i=0; i<sortingButtons.size(); i++){
            sortingButtons[i]->draw( curSelection==i, pos.x+sortingButtonPadding.x, pos.y+sortingButtonPadding.y + sortingButtonSpacingY * i);
        }
        
    }
    
}


bool OptionsBar::checkGame(ofxXmlSettings gameXML){
    
    for (int i=0; i<sortingButtons.size(); i++){
        if (sortingButtons[i]->checkGame(gameXML) == false){
            return false;
        }
    }
    
    return true;
    
}


