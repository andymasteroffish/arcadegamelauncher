#pragma once

#include "ofMain.h"
#include "GameIcon.h"


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    //void dragEvent(ofDragInfo dragInfo);
    
    void moveCursor(int xDir, int yDir);
    
    void setIconScale(float prc);
    void setSpacing();
    void setScrollTarget();
    
    void checkForGames();
    void makeIcon(string path);
    
    
    vector<GameIcon> icons;
    int cursorPos;
    
    //spacing it
    int baseIconWidth, baseIconHeight;
    float iconScale;
    int iconWidth, iconHeight;
    
    int minSideSpacing, iconSpacing;
    
    int cols, rows;
    
    //moving around;
    float scrollPos, targetScrollPos;
    float scrollXeno;
    float targetScrollOffset;
    float scrollMaxPadding;
};
