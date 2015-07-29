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
    
    void setup();
    
    void update(float deltaTime);
    void draw(float scrollPos);
    
    void drawSection(float yPos, int sectionID);
    
    
    int spaceBetweenSections;
    
    int numPoints;
    float sectionHeight;
    
    float horzNoiseSpeed;
    float vertNoiseSpeed;
    

    
    
};

#endif /* defined(__game_launcher__Background__) */
