//
//  SortingButtonToggle.cpp
//  game_launcher
//
//  Created by Andy Wallace on 7/26/15.
//
//

#include "SortingButtonToggle.h"


void SortingButtonToggle::setup(string _displayName, string _xmlName, int startingVal, bool _canBeNeutral){
    
    displayName = _displayName;
    xmlName = _xmlName;
    
    canBeNeutral = _canBeNeutral;
    
    value = startingVal;
    
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
            statusText = "NO";
            break;
        case 1:
            statusText = "YES";
            break;
        case 2:
            statusText = "ANY";
            break;
    }
    
    string tempDisplayText = displayName + "   " + statusText;
    ofDrawBitmapString(tempDisplayText, 0, 0);
    
}

void SortingButtonToggle::buttonPressed(BUTTON_TYPE button){
    
    int maxVal = canBeNeutral ? 3 : 2;
    //just shift it between 1 and 0
    if (button == BUTTON_LEFT || button == BUTTON_RIGHT || button == BUTTON_A){
        
        value = (value+1)%maxVal;
        
    }
    
}


bool SortingButtonToggle::checkGame(ofxXmlSettings gameXML){
    
    //if it is set to neutral, always let the game pass
    if (canBeNeutral && value == 2){
        return true;
    }
    
    //otherwise chekc the value
    //int thisVal =  gameXML.getValue(xmlName, 0);
    bool gameVal = gameXML.getValue(xmlName, "FALSE") == "TRUE";
    
    if (gameVal && value == 1){
        return true;
    }
    if (!gameVal && value == 0){
        return true;
    }
    
    
    return false;
}

