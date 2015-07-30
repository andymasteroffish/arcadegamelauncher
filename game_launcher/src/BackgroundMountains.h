//
//  BackgroundMountains.h
//  game_launcher
//
//  Created by Andy Wallace on 7/29/15.
//
//

#ifndef __game_launcher__BackgroundMountains__
#define __game_launcher__BackgroundMountains__

#include "Background.h"

class BackgroundMountains : public Background{
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

#endif /* defined(__game_launcher__BackgroundMountains__) */
