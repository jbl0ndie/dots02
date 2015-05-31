#include "ofApp.h"

void ofApp::setup(){
    width = ofGetWindowWidth(); height = ofGetWindowHeight();
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;
    
    ofSetWindowShape(width, height);
    masker.setup(width, height);
    
    //Init a new layer / mask combo
    masker.newLayer();
    
    // initialise all the constants to avoid using literals as much as possible
    stretchFactor = 1.5;
    ofSetCircleResolution(60);
    circleRadius = 15;
    numberOfCircles = 200;
    rotationAngle = 0.0;
    rotationSpeed = 0.2;
    offsetX = 5.8;
    offsetY = 5.8;

    // draw the dots in an fbo which we'll call later in the draw method
    // nb the fbo needs to be bigger than the window to accommodate the rotation
    // allocate the fbo with alpha, 8 bits rgb, 4 determines the glut anti-aliasing
    backFbo.allocate(width * stretchFactor, height * stretchFactor, GL_RGBA,4);

    backFbo.begin(); // begin the fbo
        ofClear(0, 0, 0, 255); // clear it (good practice)
        
        ofSetColor(255, 255, 255, 255);
        for (int i = 0; i < numberOfCircles; i++) {
            ofCircle(ofRandom(width * stretchFactor), ofRandom(height * stretchFactor), circleRadius);
        }
    
    backFbo.end(); // end the fbo
}

void ofApp::update(){
   
    // it's a bit cavalier to have this just increase for ever
    // so reset it to zero after each rotation
    rotationAngle += rotationSpeed; // increment the fbo's rotation angle based on the rotation speed
    if (rotationAngle > (360 - rotationSpeed)) {
        rotationAngle = 0;
    }
    
    //    rotationAngle = ofGetMouseX(); // for rotation debug testing
//    rotationAngle = 0;
}

void ofApp::draw(){
    
    //Draw a background
    ofBackground(ofColor::black);

    //Draw the layer with the fixed position background dots
    masker.beginLayer();
    ofClear(0, 0, 0, 255); // clear the fbo
    ofSetColor(ofColor::white);
    backFbo.draw(0, 0); // draw the fbo with the dots in
    masker.endLayer();

    //Draw the mask of holes
    masker.beginMask();
    ofClear(0, 0, 0, 0);
    ofSetColor(ofColor::white);

    // set the rotation centre to mid-screen by translating the origin
    ofPushMatrix();
    {
        ofTranslate(width / 2, height / 2); // translate origin
        ofRotate(rotationAngle, 0, 0, 1); // rotate about origin Z-axis
//        ofRotate(180, 1, 0, 0); // flip the fbo so it never completely aligns
            ofPushMatrix(); // drop down a level to reset the origin
            ofTranslate(-width / 2, -height / 2); // reset the origin
            backFbo.draw(0 + offsetX, 0 + offsetY); // draw the fbo again, with an offset
            ofPopMatrix();
    }
    ofPopMatrix();
    
    masker.endMask();

    //Draw the combined result
    masker.draw();
    
    //Print fps at top right of window
    ofDrawBitmapString(ofToString(ofGetFrameRate())+ "fps" + " " + ofToString(rotationAngle), ofGetWindowWidth()-150, 15);
}

// definintition of his function to draw a grid of rectangles
void ofApp::drawGrid(int _width, int _height, float increment, float blockSize){
    for(int i = 0; i < _width; i+=increment) {
        for(int j = 0; j < _height; j+=increment) {
            ofRect(i, j, blockSize, blockSize);
        }
    }
}

// definition of his function to draw the text labels
void ofApp::drawText(string text, int x, int marginY, int _height){
    for(int i = marginY; i < _height; i+=marginY) {
        ofDrawBitmapString(text, x, i);
    }
}

// definition of his function to animate the circle size in his example
float ofApp::animate(float from, float to){
    return ofMap(sin(ofGetFrameNum() * 0.02), -1, 1, from, to);
}

void ofApp::keyPressed(int key){
    
}

void ofApp::keyReleased(int key){
    
}

void ofApp::mouseMoved(int x, int y ){
    
}

void ofApp::mouseDragged(int x, int y, int button){
    
}

void ofApp::mousePressed(int x, int y, int button){
    
}

void ofApp::mouseReleased(int x, int y, int button){
    
}

void ofApp::windowResized(int w, int h){
    
}

void ofApp::gotMessage(ofMessage msg){
    
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    
}