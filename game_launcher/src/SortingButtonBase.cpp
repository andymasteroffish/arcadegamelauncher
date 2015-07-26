//
//  SortingButtonBase.cpp
//  game_launcher
//
//  Created by Andy Wallace on 7/26/15.
//
//

#include "SortingButtonBase.h"

void SortingButtonBase::generalSetup(){
    
    selectedColor = ofColor::gray;
    normalColor = ofColor::black;
    
}


void SortingButtonBase::update(float _deltaTime){
    deltaTime = _deltaTime;
    typeUpdate();
}

void SortingButtonBase::draw(bool isSelected, float x, float y){
    ofPushMatrix();
    ofTranslate(x, y);
    
    typeDraw(isSelected);
    
    ofPopMatrix();
}

int SortingButtonBase::getValue(){
    return value;
}