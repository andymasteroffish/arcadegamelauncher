//
//  BackgroundMountains.cpp
//  game_launcher
//
//  Created by Andy Wallace on 7/29/15.
//
//

#include "BackgroundMountains.h"

void BackgroundMountains::setup(){
    
    spaceBetweenSections = 310;
    
    numPoints = 11;
    sectionHeight = 300;
    
    horzNoiseSpeed = 1;
    vertNoiseSpeed = 0.3;
}

void BackgroundMountains::update(float deltaTime){
    
}

void BackgroundMountains::draw(float scrollPos){
    
    //cout<<"scroll "<<scrollPos<<endl;
    
    ofSetColor(255,0,0);
    
    
    float parallax = 0.7;
    
    int startPos = -scrollPos * parallax;
    
    
    int endLimit = MAX(5, scrollPos/150);
    
    for (int i=endLimit; i>=0; i--){
        
        int thisY = startPos + i*spaceBetweenSections;
        
        if (thisY > -spaceBetweenSections && thisY < ofGetHeight()+spaceBetweenSections*2){
            drawSection( thisY, i);
        }
        
    }
    
    
}

void BackgroundMountains::drawSection(float yPos, int sectionID){
    //cout<<"draw "<<sectionID<<endl;
    
    int hue = (sectionID*33)%256;
    
    ofColor myCol;
    myCol.setHsb(hue, 100, 200);
    ofSetColor(myCol);
    
    float roughSpacing = ofGetWidth()/(numPoints-2);
    float horizontalRange = roughSpacing * 0.2;
    
    vector<ofVec2f> points;
    
    for (int i=0; i<numPoints; i++){
        ofVec2f point;
        point.x = roughSpacing*i + ofNoise(ofGetElapsedTimef()*horzNoiseSpeed, i, 100, sectionID) * horizontalRange - roughSpacing/2;
        point.y = yPos + ofNoise(ofGetElapsedTimef()*vertNoiseSpeed, i, 200, sectionID) * sectionHeight;
        points.push_back(point);
    }
    
    ofBeginShape();
    ofVertex(-roughSpacing/2, yPos - spaceBetweenSections);
    for (int i=0; i<numPoints; i++){
        ofVertex(points[i].x, points[i].y);
    }
    ofVertex(ofGetWidth()+roughSpacing/2, yPos - spaceBetweenSections);
    ofEndShape();
    
    
}