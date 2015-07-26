//
//  SortingButtonToggle.h
//  game_launcher
//
//  Created by Andy Wallace on 7/26/15.
//
//

#ifndef __game_launcher__SortingButtonToggle__
#define __game_launcher__SortingButtonToggle__

#include "SortingButtonBase.h"

class SortingButtonToggle : public SortingButtonBase{
public:
    
    void setup(string _displayName, string _xmlName);
    
    void typeUpdate();
    
    void typeDraw(bool isSelected);
    
    void buttonPressed(BUTTON_TYPE button);
    
    bool checkGame(ofxXmlSettings gameXML);
    
    
};

#endif /* defined(__game_launcher__SortingButtonToggle__) */
