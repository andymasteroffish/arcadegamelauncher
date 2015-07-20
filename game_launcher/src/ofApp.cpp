#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    
    baseIconWidth = 315;
    baseIconHeight = 250;
    
    minSideSpacing = 40;
    iconSpacing = 35;
    
    scrollPos = 0;
    scrollXeno = 0.06;
    targetScrollOffset = ofGetHeight()/2;
    scrollMaxPadding = 100;
    
    //make our icons
    checkForGames();
    
    //testing
//    for (int i=0; i<25; i++){
//        GameIcon newIcon;
//        newIcon.setup(baseIconWidth, baseIconHeight);
//        icons.push_back(newIcon);
//    }
    
    setIconScale(0.8);
    
    cursorPos = 0;
    
    bgCol = bgTargetCol;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    scrollPos = (1-scrollXeno) * scrollPos + scrollXeno * targetScrollPos;
    
    //xeno the background color
    for (int i=0; i<3; i++){
        bgCol[i] = (1-scrollXeno) * bgCol[i] + scrollXeno * bgTargetCol[i];
    }
    ofColor thisBackground;
    thisBackground.setHsb(bgCol[0], bgCol[1], bgCol[2]);
    ofBackground(thisBackground);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofTranslate(0, -scrollPos);
    
    for (int i=0; i<icons.size(); i++){
        icons[i].draw( i==cursorPos );
    }
    
    ofPopMatrix();
    
    string debugInfo = "";
    debugInfo += "scale: "+ofToString(iconScale)+"\n";
    debugInfo += "cols: "+ofToString(cols)+"\n";
    debugInfo += "rows: "+ofToString(rows)+"\n";
    ofSetColor(0);
    ofDrawBitmapString(debugInfo, 8,15);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f' || key == 'F'){
        ofToggleFullscreen();
    }
    
    if (key == '-'){
        setIconScale( MAX(0, iconScale-0.1));
    }
    if (key == '='){
        setIconScale( iconScale+0.1);
    }
    
    
    if (key == 357){
        moveCursor(0, -1);
    }
    if (key == 359){
        moveCursor(0, 1);
    }
    if (key == 356){
        moveCursor(-1, 0);
    }
    if (key == 358){
        moveCursor(1, 0);
    }
    
    if (key == ' ' || key == 13){
        icons[cursorPos].launch();
    }
    
    //cout<<key<<endl;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    setSpacing();
}

//--------------------------------------------------------------
void ofApp::moveCursor(int xDir, int yDir){
    
    int curCol = cursorPos%cols;
    int curRow = cursorPos/cols;
    
    //int lastRow = (icons.size()-1)/cols;
    int lastCol = (icons.size()-1)%cols;
    
    //when the cursor is moving off the edge, we need to be careful
    if (curCol == 0 && xDir == -1){
        cursorPos += cols-1;
        if (cursorPos >= icons.size()){
            cursorPos = icons.size()-1;
        }
    }
    else if (curCol == cols-1 && xDir == 1){
        cursorPos -= cols-1;
    }
    else if (cursorPos == icons.size()-1 && xDir == 1){
        cursorPos -= curCol;
    }
    else if (curRow == 0 && yDir == -1){
        cursorPos = rows * cols + curCol;
        if (cursorPos >= icons.size()){
            cursorPos -= cols;
        }
    }
    else if ( ( curRow == rows || (curRow == rows-1 && curCol > lastCol) ) && yDir == 1){
        cursorPos = curCol;
    }
    
    //anything else can just get the standard move
    else{
        cursorPos += xDir + yDir * cols;
    }
    
    //set us scrolling
    setScrollTarget();
    
    ofColor newBGColor = icons[cursorPos].getAvgCol() ;
    bgTargetCol[0] = newBGColor.getHue();
    bgTargetCol[1] = newBGColor.getSaturation();
    bgTargetCol[2] = newBGColor.getBrightness();
}

//--------------------------------------------------------------
void ofApp::setIconScale(float prc){
    iconScale = prc;
    
    iconWidth = baseIconWidth * prc;
    iconHeight = baseIconHeight * prc;
    
    //set the icons
    for (int i=0; i<icons.size(); i++){
        icons[i].scale = iconScale;
    }
    
    //cout<<"scale now "<<iconScale<<endl;
    
    //update the spacing
    setSpacing();
}

//--------------------------------------------------------------
void ofApp::setSpacing(){
    
    float availableSpace = ofGetWidth() - minSideSpacing*2;
    
    cols = MAX(1, availableSpace/(iconWidth+iconSpacing) );
    rows = (icons.size()-1)/cols;
    
    float startX = ofGetWidth()/2 - ( (float)cols * (iconWidth+iconSpacing)) /2 + iconSpacing/2 +1;
    //not sure why I need the plus one but whatever
    
    //put them all in place
    for (int i=0; i<icons.size(); i++){
        int thisCol = i%cols;
        int thisRow = i/cols;
        
        icons[i].pos.x = startX + thisCol*iconWidth + thisCol*iconSpacing;
        icons[i].pos.y = thisRow*iconHeight + thisRow*iconSpacing;
    }
    
    
    //set us scrolling
    setScrollTarget();
    
}


//--------------------------------------------------------------
void ofApp::setScrollTarget(){
    targetScrollPos = icons[cursorPos].pos.y - targetScrollOffset + iconHeight/2;
    if (targetScrollPos < -scrollMaxPadding){
        targetScrollPos = -scrollMaxPadding;
    }
    float bottomVal = rows * (iconHeight+iconSpacing) + iconHeight  + scrollMaxPadding - ofGetHeight();
    //cout<<"the limit "<<bottomVal<<endl;
    if (targetScrollPos > bottomVal){
        targetScrollPos = bottomVal;
    }
    //cout<<"target "<<targetScrollPos<<endl;
}





//--------------------------------------------------------------
void ofApp::checkForGames(){
    ofDirectory dir;
    
    dir.listDir("games");
    vector<ofFile> files = dir.getFiles();
    for(int i = 0; i < files.size(); i++){
        if (files[i].isDirectory()){
            makeIcon( files[i].path() );// dir.getPath(i) );
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::makeIcon(string path){
    ofDirectory dir;
    dir.listDir(path);
    vector<ofFile> files = dir.getFiles();
    
    string imagePath = "";
    string infoPath = "";
    
    //cout<<"GAME: "<<endl;
    for(int i = 0; i < files.size(); i++){
        //cout<<i<<":"<<files[i].path()<<endl;
        string extension = files[i].getExtension();
        //cout<<"livin:"<<extension<<endl;
        if (extension == "png" || extension == "gif" || extension == "jpg" || extension == "jpeg"){
            imagePath = files[i].path();
        }
        if (extension == "xml"){
            infoPath = files[i].path();
        }
    }
    
    if (imagePath == ""){
        imagePath = "default_thumb.png";
    }
    
    //only make it if we have the necessary info
    if (infoPath != ""){
        GameIcon newIcon;
        //try to set it up, and if it has all necessary components, add it to the vector
        if(newIcon.setup(imagePath, infoPath, baseIconWidth, baseIconHeight)){
            icons.push_back(newIcon);
        }
    }
    
}










