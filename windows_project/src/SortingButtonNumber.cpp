//
//  SortingButtonNumber.cpp
//  game_launcher
//
//  Created by Andy Wallace on 7/26/15.
//
//

#include "SortingButtonNumber.h"


void SortingButtonNumber::setup(string _displayName, string _xmlNameMin, string _xmlNameMax, int _highVal){
    
    displayName = _displayName;
    xmlNameMin = _xmlNameMin;
    xmlNameMax = _xmlNameMax;
    
    highVal = _highVal;
    
    value = 0;
    
    buttonType = SORTING_BUTTON_TOGGLE;
    
    generalSetup();
    
}


void SortingButtonNumber::typeUpdate(){
    
}

void SortingButtonNumber::typeDraw(bool isSelected){
    
    ofSetColor( isSelected ? selectedColor : normalColor);
    
    string statusText = ofToString(value);
    if (value == 0){
        statusText = "ANY";
    }
    
    string tempDisplayText = displayName + "   " + statusText;
    ofDrawBitmapString(tempDisplayText, 0, 0);
    
}

void SortingButtonNumber::buttonPressed(BUTTON_TYPE button){
    
    if (button == BUTTON_LEFT){
        value --;
    }
    
    if (button == BUTTON_RIGHT || button == BUTTON_A){
        value ++;
    }
    
    if (value < 0){
        value = highVal;
    }
    if (value > highVal){
        value = 0;
    }
    
}


bool SortingButtonNumber::checkGame(ofxXmlSettings gameXML){
    
    //when set to "anything" just let it through
    if (value == 0){
        return true;
    }
    
    //otherwise check the value
    int gameValMin = gameXML.getValue(xmlNameMin, 1);
    int gameValMax = gameXML.getValue(xmlNameMax, 1);
    
    if (value >= gameValMin && value <= gameValMax){
        return true;
    }
    
    return false;
    
}