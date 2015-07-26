//
//  SortingButtonToggle.cpp
//  game_launcher
//
//  Created by Andy Wallace on 7/26/15.
//
//

#include "SortingButtonToggle.h"


void SortingButtonToggle::setup(string _displayName, string _xmlName){
    
    displayName = _displayName;
    xmlName = _xmlName;
    
    value = 0;
    
    buttonType = SORTING_BUTTON_TOGGLE;
    
    generalSetup();
    
}


void SortingButtonToggle::typeUpdate(){
    
}

void SortingButtonToggle::typeDraw(bool isSelected){
    
    ofSetColor( isSelected ? selectedColor : normalColor);
    
    string statusText = "";
    switch (value) {
        case 0:
            statusText = "DON'T CARE";
            break;
        case 1:
            statusText = "YES";
            break;
    }
    
    string tempDisplayText = displayName + "   " + statusText;
    ofDrawBitmapString(tempDisplayText, 0, 0);
    
}

void SortingButtonToggle::buttonPressed(BUTTON_TYPE button){
    
    //just shift it between 1 and 0
    if (button == BUTTON_LEFT || button == BUTTON_RIGHT || button == BUTTON_A){
        
        value = (value+1)%2;
        
    }
    
}


bool SortingButtonToggle::checkGame(ofxXmlSettings gameXML){
    
    //when unchecked, just let the game through
    if (value == 0){
        return true;
    }
    
    //otherwise check the value
    bool gameVal = gameXML.getValue(xmlName, "FALSE") == "TRUE";
    return gameVal;
    
}

