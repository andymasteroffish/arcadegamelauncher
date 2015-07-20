//
//  GameIcon.cpp
//  game_launcher
//
//  Created by Andy Wallace on 7/19/15.
//
//

#include "GameIcon.h"


bool GameIcon::setup(string imagePath, string infoPath, int _wdith, int _height){
    
    width = _wdith;
    height = _height;
    
    thumbnail.loadImage(imagePath);
    scale = 1;
    
    return parseInfo(infoPath);
}

void GameIcon::draw(bool isSelected){
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofScale(scale, scale);
    
    //show the cursor if selected
    if (isSelected){
        ofSetColor( ofColor::yellow );
        ofFill();
        float padding = 10 + abs(sin(ofGetElapsedTimef()))*10;
        ofRect(-padding, -padding, width+padding*2, height+padding*2);
    }
    
    //draw the pic
    ofSetColor(255);
    thumbnail.draw(0, 0, width, height);
    
    //draw the name
    ofSetColor(255, 200);
    ofRect(0, height-17, width, 17);
    ofSetColor(0);
    ofDrawBitmapString(name, 3, height-2);
    
    ofPopMatrix();
}


void GameIcon::launch(){
    cout<<"launch "<<gamePath<<endl;
    
#ifdef USING_MAC
    string command = "open " + gamePath;
    system(command.c_str());
#endif
}

bool GameIcon::parseInfo(string infoPath){
    
    ofxXmlSettings xml;
    if (xml.load(infoPath)){
        name = xml.getValue("NAME", "UNKNOWN");
        gamePath = "\""+ xml.getValue("PATH", "") + "\"";
        minNumPlayers = xml.getValue("MIN_PLAYERS", 0);
        maxNumPlayers = xml.getValue("MAX_PLAYERS", 0);
    }else{
        cout<<"we got a big fucking issue"<<endl;
        return false;
    }
    
    if (gamePath == ""){
        return false;
    }
    
    cout<<"----------"<<endl;
    cout<<name<<endl<<gamePath<<endl;
    cout<<minNumPlayers<<" - "<<maxNumPlayers<<" players"<<endl;
    
    //if it got here, there were no issues
    return true;
    
}




ofColor GameIcon::getAvgCol(){
    
    
    float hue = 0;
    float sat = 0;
    float bri = 0;
    
    for (int i=0; i<20; i++){
        int x = ofRandom(thumbnail.width);
        int y = ofRandom(thumbnail.height);
        ofColor col = thumbnail.getColor(x, y);
        hue += col.getHue();
        sat += col.getSaturation();
        bri += col.getBrightness();
    }
    
    hue /= 20;
    sat /= 20;
    bri /= 20;
    
    ofColor thisCol;
    thisCol.setHsb(hue, sat, bri);
    
    return thisCol;
    
}





