//
//  BackgroundTiles.cpp
//  game_launcher
//
//  Created by Andy Wallace on 7/29/15.
//
//

#include "BackgroundTiles.h"


void BackgroundTiles::setup(){
    
    tilePic.loadImage("bg_tile.png");
    
    cols = ofGetScreenWidth()/tilePic.width + 1;
    rows = ofGetScreenHeight()/tilePic.height + 7;
    
    for (int x=0; x<cols; x++){
        vector<BackgroundTile> thisRow;
        for (int y=0; y<rows; y++){
            BackgroundTile thisTile;
            thisTile.setup(&tilePic);
            thisRow.push_back(thisTile);
        }
        tiles.push_back(thisRow);
    }
    
}

void BackgroundTiles::update(float deltaTime){
    ofBackground(250, 255, 240);
    for (int x=0; x<cols; x++){
        for (int y=0; y<rows; y++){
            tiles[x][y].update(deltaTime);
        }
    }
}

void BackgroundTiles::draw(float scrollPos){
    int spacing = tilePic.width;
    int offset = -tilePic.width*0.4;
    
    float scrollPrc = ofMap(scrollPos, minScroll, maxScroll, 0, 1);
    float paddingY = tilePic.height * 5;
    float yPos = -scrollPrc * paddingY;
    
    
    ofPushMatrix();
    ofTranslate(0, yPos);
    
    ofSetColor(255);
    //draw normies
    for (int x=0; x<cols; x++){
        for (int y=0; y<rows; y++){
            if (!tiles[x][y].isSpinning){
                ofPushMatrix();
                ofTranslate(x*spacing + offset, y*spacing + offset);
                tiles[x][y].draw();
                ofPopMatrix();
            }
        }
    }
    
    //then spinners
    for (int x=0; x<cols; x++){
        for (int y=0; y<rows; y++){
            if (tiles[x][y].isSpinning){
                ofPushMatrix();
                ofTranslate(x*spacing + offset, y*spacing + offset);
                tiles[x][y].draw();
                ofPopMatrix();
            }
        }
    }
    
    ofPopMatrix();
    
    //fade it
    ofSetColor(250, 255, 240, 180);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
}
