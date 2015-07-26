//
//  SortingButtonBase.h
//  game_launcher
//
//  Created by Andy Wallace on 7/26/15.
//
//

#ifndef __game_launcher__SortingButtonBase__
#define __game_launcher__SortingButtonBase__

#include "ofMain.h"
#include "basicInfo.h"
#include "ofxXmlSettings.h"

enum SORTING_BUTTON_TYPE { SORTING_BUTTON_TOGGLE, SORTING_BUTTON_INT };

class SortingButtonBase{
public:
    
    void generalSetup();
    
    void update(float _deltaTime);
    virtual void typeUpdate(){}
    
    void draw(bool isSelected, float x, float y);
    virtual void typeDraw(bool isSelected){}
    
    int getValue(); //maybe kill this
    virtual bool checkGame(ofxXmlSettings gameXML){return true;}
    
    virtual void buttonPressed(BUTTON_TYPE button){}
    
    
    SORTING_BUTTON_TYPE buttonType;
    
    int value;
    
    string displayName;
    string xmlName; //what field it referrs to
    
    float deltaTime; //might be used for animations or something
    
    ofColor normalColor, selectedColor;
    
    
};

#endif /* defined(__game_launcher__SortingButtonBase__) */
