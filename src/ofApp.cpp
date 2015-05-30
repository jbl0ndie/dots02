#include "ofApp.h"

void ofApp::setup(){
    width = ofGetWindowWidth(); height = ofGetWindowHeight();
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;
    
    ofSetWindowShape(width, height);
    masker.setup(width, height);
    
    //Init a new layer / mask combo
    masker.newLayer();
    
    ofSetCircleResolution(60);
    circleRadius = 15;
    numberOfCircles = 300;
    rotationAngle = 0.0;
    rotationSpeed = 1.1;

    // lets try drawing the dots in an fbo and seeing if we can call that in the draw method

    backFbo.allocate(width, height, GL_RGBA); // allocate the fbo with alpha, 8 bits rgb

    
    backFbo.begin(); // begin the fbo
        ofClear(0, 0, 0, 255); // clear it (good practice)
        
        ofSetColor(255, 255, 255, 255);
        for (int i = 0; i < numberOfCircles; i++) {
            ofCircle(ofRandom(width - circleRadius), ofRandom(height - circleRadius), circleRadius);
        }
    
    backFbo.end(); // end the fbo
}

void ofApp::update(){
   
    rotationAngle += rotationSpeed;
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
        ofRotate(rotationAngle, 0, 0, 1); // rotate about origin
        backFbo.draw(0, 5); // draw the fbo again, with an offset
            ofPushMatrix(); // reset the origin
            ofTranslate(-width / 2, -height / 2);
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