#pragma once

#include "ofMain.h"
#include "BasicInfo.h"

#include "GameIcon.h"
#include "OptionsBar.h"

#include "Background.h"
#include "BackgroundMountains.h"
#include "BackgroundTiles.h"

#include "ControllerManager.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void checkControl();
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
    
    void openOptionsBar();
    void closeOptionsBar();
    
    void setIconScale(float prc);
    void setSpacing();
    void setScrollTarget();
    
    void checkForGames();
    void makeIcon(string path);
    
    void sortGames();
    
    void scrollBackground(int dir);
    
    //what we're doing right now
    GAME_STATE curState;
    
    //timing
    float prevFrameTime, deltaTime;
    
    //sorting
    OptionsBar optionsBar;
    
    //icons
    vector<GameIcon *> icons;
    int cursorPos;
    
    //spacing it
    int baseIconWidth, baseIconHeight;
    float iconScale;
    int iconWidth, iconHeight;
    
    int minSideSpacing, iconSpacing;
    
    int cols, rows;
    
    //moving around;
    float scrollPos, targetScrollPos;
    float maxScroll;
    float scrollXeno;
    float targetScrollOffset;
    float scrollMaxPadding;
    
    //controllers
    ControllerManager controllerManager;
    
    
    //background
    vector<Background *> backgrounds;
    int curBackground;
    
    
    //debug
    bool debugHideIcons;
};
