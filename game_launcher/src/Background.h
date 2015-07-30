//
//  Background.h
//  game_launcher
//
//  Created by Andy Wallace on 7/21/15.
//
//

#ifndef __game_launcher__Background__
#define __game_launcher__Background__

#include "ofMain.h"

class Background{
public:
    
    virtual void setup(){}
    
    virtual void update(float deltaTime){}
    virtual  void draw(float scrollPos){}
    

    void setScrollExtremes(int _maxScroll, int _minScroll);
    
    int maxScroll, minScroll;
    
    
};

#endif /* defined(__game_launcher__Background__) */
