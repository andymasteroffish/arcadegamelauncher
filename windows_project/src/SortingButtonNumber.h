//
//  SortingButtonNumber.h
//  game_launcher
//
//  Created by Andy Wallace on 7/26/15.
//
//

#ifndef __game_launcher__SortingButtonNumber__
#define __game_launcher__SortingButtonNumber__

#include "SortingButtonBase.h"

class SortingButtonNumber : public SortingButtonBase{
public:
    
    void setup(string _displayName, string _xmlNameMin, string _xmlNameMax, int _highVal);
    
    void typeUpdate();
    
    void typeDraw(bool isSelected);
    
    void buttonPressed(BUTTON_TYPE button);
    
    bool checkGame(ofxXmlSettings gameXML);
    
    int highVal;
    bool isMax;
    
    string xmlNameMin, xmlNameMax;
    
};

#endif /* defined(__game_launcher__SortingButtonNumber__) */
