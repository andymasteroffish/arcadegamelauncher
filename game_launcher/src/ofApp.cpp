#include "ofApp.h"


// sorting icons
bool iconSortAlphabetical(  GameIcon * a, GameIcon * b ) {
    
    if (!a->isHidden && b->isHidden){
        return true;
    }
    
    if (a->isHidden == b->isHidden){
        return a->name.compare(b->name) < 0;
    }
    
    return false;
}


//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    ofBackground( 250, 230, 255);
    
    debugHideIcons = false;
    
    controllerManager.setup();
    
    optionsBar.setup(&controllerManager);
    
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
    
    background.setup();
    
    bgCol = bgTargetCol;
    
    prevFrameTime = ofGetElapsedTimef();
    deltaTime = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    deltaTime = ofGetElapsedTimef() - prevFrameTime;
    prevFrameTime = ofGetElapsedTimef();
    
    //update the controllers and see what the user has done
    controllerManager.update();
    
    //move our scroll
    scrollPos = (1-scrollXeno) * scrollPos + scrollXeno * targetScrollPos;
    
    //update everything that gets updted no matter what
    background.update(deltaTime);
    
    for (int i=0; i<icons.size(); i++){
        icons[i]->update(deltaTime);
    }
    
    if (icons[cursorPos]->doingNewPosMove){
        setScrollTarget();
    }
    
    //and the state specific ones
    if (curState == STATE_HOME){
        checkControl();
    }
    else if (curState == STATE_OPTIONS){
        optionsBar.update(deltaTime);
        if (optionsBar.sortGamesFlag){
            optionsBar.sortGamesFlag = false;
            sortGames();
        }
        if (optionsBar.isDone){
            closeOptionsBar();
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::checkControl(){
    
    if (controllerManager.isButtonPressed(BUTTON_UP)){
        moveCursor(0, -1);
    }
    if (controllerManager.isButtonPressed(BUTTON_DOWN)){
        moveCursor(0, 1);
    }
    if (controllerManager.isButtonPressed(BUTTON_LEFT)){
        moveCursor(-1, 0);
    }
    if (controllerManager.isButtonPressed(BUTTON_RIGHT)){
        moveCursor(1, 0);
    }
    if (controllerManager.isButtonPressed(BUTTON_A)){
        icons[cursorPos]->launch();
    }
    
    //did they launch the options bar?
    if (controllerManager.isButtonPressed(BUTTON_Y)){
        openOptionsBar();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    background.draw(scrollPos);
    
    ofPushMatrix();
    ofTranslate(0, -scrollPos);
    
    if (!debugHideIcons){
        for (int i=0; i<icons.size(); i++){
            icons[i]->draw( i==cursorPos );
        }
    }
    
    ofPopMatrix();
    
    optionsBar.draw();
    
    string debugInfo = "";
    debugInfo += "scale: "+ofToString(iconScale)+"\n";
    debugInfo += "cols: "+ofToString(cols)+"\n";
    debugInfo += "rows: "+ofToString(rows)+"\n";
    ofSetColor(0);
    ofDrawBitmapString(debugInfo, 8,15);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    controllerManager.keyPressed(key);
    
    if (key == 'f' || key == 'F'){
        ofToggleFullscreen();
    }
    
    if (key == '-'){
        setIconScale( MAX(0, iconScale-0.1));
    }
    if (key == '='){
        setIconScale( iconScale+0.1);
    }
    
    
    
    
    if (key == 'i'){
        debugHideIcons = !debugHideIcons;
    }
    
    
    //cout<<key<<endl;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    controllerManager.keyReleased(key);
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
    
}

//--------------------------------------------------------------
void ofApp::openOptionsBar(){
    curState = STATE_OPTIONS;
    optionsBar.reset(icons[cursorPos]);
}

//--------------------------------------------------------------
void ofApp::closeOptionsBar(){
    curState = STATE_HOME;
}

//--------------------------------------------------------------
void ofApp::setIconScale(float prc){
    iconScale = prc;
    
    iconWidth = baseIconWidth * prc;
    iconHeight = baseIconHeight * prc;
    
    //set the icons
    for (int i=0; i<icons.size(); i++){
        icons[i]->scale = iconScale;
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
        
        ofVec2f newPos;
        
        newPos.x = startX + thisCol*iconWidth + thisCol*iconSpacing;
        newPos.y = thisRow*iconHeight + thisRow*iconSpacing;
        
        bool doAnimation = ofGetFrameNum() > 2;
        icons[i]->setNewPos(newPos, doAnimation);
    }
    
}


//--------------------------------------------------------------
void ofApp::setScrollTarget(){
    targetScrollPos = icons[cursorPos]->pos.y - targetScrollOffset + iconHeight/2;
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
        GameIcon * newIcon = new GameIcon();
        //try to set it up, and if it has all necessary components, add it to the vector
        if(newIcon->setup(imagePath, infoPath, baseIconWidth, baseIconHeight)){
            icons.push_back(newIcon);
        }
    }
    
}



//--------------------------------------------------------------
void ofApp::sortGames(){
    //cout<<"sort it"<<endl;
    
    for (int i=0; i<icons.size(); i++){
        ofxXmlSettings gameXML;
        gameXML.loadFile(icons[i]->infoPath);
        
        icons[i]->isHidden = optionsBar.checkGame(gameXML) == false;
    }
    
    //sort it all
    sort(icons.begin(), icons.end(), iconSortAlphabetical);
    
    
    //let's see if we can have the cursor still on this game
    //if it is hidden, find the last non-hidden game
    if (optionsBar.gameSelectedWhenOpened->isHidden){
        for (int i=icons.size()-1; i>=0; i--){
            if (!icons[i]->isHidden){
                cursorPos = i;
                break;
            }
        }
    }
    //if it is not hidden, find it and select it
    else{
        for (int i=0; i<icons.size(); i++){
            if (optionsBar.gameSelectedWhenOpened == icons[i]){
                cursorPos = i;
            }
        }
    }
    
    
    //move them around
    setSpacing();
    
}









