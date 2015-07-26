//
//  GameIcon.h
//  game_launcher
//
//  Created by Andy Wallace on 7/19/15.
//
//

#ifndef __game_launcher__GameIcon__
#define __game_launcher__GameIcon__

#include "ofMain.h"
#include "ofxXmlSettings.h"

#define USING_MAC


class GameIcon{
public:
    
    bool setup(string imagePath, string _infoPath, int _wdith, int _height);
    void update(float delta);
    void draw(bool isSelected);
    void launch();
    
    void setNewPos(ofVec2f _newPos, bool doAnimation);
    
    bool parseInfo();
    
    ofColor getAvgCol();
    
    //displaying
    ofImage thumbnail;
    float scale;
    
    int width, height;
    ofVec2f pos;
    
    string infoPath;
    
    //game info
    string name;
    string gamePath;
    int minNumPlayers, maxNumPlayers;
    
    bool isHidden;  //when a search would exclude this game
    
    //animation for setting new positions
    bool doingNewPosMove;
    float newPosMoveTime, newPosMoveTimer;
    ofVec2f newPosMoveStart, newPosMoveTarget;
    
    
    
};

#endif /* defined(__game_launcher__GameIcon__) */
