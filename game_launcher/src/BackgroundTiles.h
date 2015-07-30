//
//  BackgroundTiles.h
//  game_launcher
//
//  Created by Andy Wallace on 7/29/15.
//
//

#ifndef __game_launcher__BackgroundTiles__
#define __game_launcher__BackgroundTiles__

#include "Background.h"


class BackgroundTile{
public:
    ofImage * pic;
    float curAngle, curScale;
    
    bool isSpinning;
    float spinTimer;
    int spinPhase;
    
    float growTime;
    float normScale;
    float growMaxScale;
    
    float spinTime;
    float spinCurve;
    float startingAngle;
    float targetAngle;
    
    int maxNumSteps;
    
    float maxTimeBetweenSpins;
    float minTimeBetweenSpins;
    float nextSpinTimer;
    
    void setup(ofImage * _pic){
        pic = _pic;
        
        maxTimeBetweenSpins = 200;
        minTimeBetweenSpins = 4;
        nextSpinTimer = ofRandom(0, maxTimeBetweenSpins);   //we start it at 0 to simulate the tiles running before the user started
        
        
        //uncomment this shit to make it look cool
//        maxTimeBetweenSpins = 1;
//        minTimeBetweenSpins = 1;
//        nextSpinTimer = 1;
        
        isSpinning = false;
        spinTimer = 0;
        
        maxNumSteps = 4;
        curAngle = (int)ofRandom(maxNumSteps) * 90;
        
        normScale = 1;
        curScale = normScale;
        
        growTime = 1.2;
        growMaxScale = 1.25;
        
        spinTime = 1.5;
        spinCurve = 2;
        targetAngle = curAngle;
        startingAngle = curAngle;
        spinPhase = 0;
    }
    
    void update(float deltaTime){
        //are they spinning?
        if (isSpinning){
            spinTimer += deltaTime;
            
            //growing
            if (spinPhase == 0){
                float prc = spinTimer / growTime;
                if (prc < 1){
                    curScale = (1-prc)*normScale + prc*growMaxScale;
                }else{
                    curScale = growMaxScale;
                    spinTimer = 0;
                    spinPhase = 1;
                }
            }
            
            //spinning
            if (spinPhase == 1){
                float prc = spinTimer / spinTime;
                prc = powf(prc, spinCurve);
                if (prc < 1){
                    curAngle = (1-prc)*startingAngle + prc*targetAngle;
                }else{
                    curAngle = targetAngle;
                    spinTimer = 0;
                    spinPhase = 2;
                }
            }
            
            //shrinking
            if (spinPhase == 2){
                float prc = spinTimer / growTime;
                if (prc < 1){
                    curScale = (1-prc)*growMaxScale + prc*normScale;
                }else{
                    curScale = normScale;
                    isSpinning = false;
                }
            }
        }
        
        //is it time to spin?
        else{
            nextSpinTimer -= deltaTime;
            if (nextSpinTimer < 0){
                startSpinning();
            }
        }
    }
    
    void draw(){
        ofPushMatrix();
        ofRotate(curAngle);
        ofScale(curScale, curScale);
        pic->draw(-pic->width/2, -pic->height/2);
        
        ofPopMatrix();
    }
    
    void startSpinning(){
        isSpinning = true;
        int numSteps = ofRandom(1, maxNumSteps);
        if (ofRandom(1) < 0.5){
            numSteps *= -1;
        }
        startingAngle = curAngle;
        targetAngle = curAngle + numSteps * 90;
        spinPhase = 0;
        
        spinTimer = 0;
        
        nextSpinTimer = ofRandom(minTimeBetweenSpins, maxTimeBetweenSpins);
    }
};

class BackgroundTiles : public Background{
public:
    
    void setup();
    
    void update(float deltaTime);
    void draw(float scrollPos);
    
    ofImage tilePic;
    
    vector< vector<BackgroundTile> > tiles;
    int cols, rows;
    
    
    
};

#endif /* defined(__game_launcher__BackgroundTiles__) */
