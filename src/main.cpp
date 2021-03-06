#include "ofMain.h"
#include "ofApp.h"
//import the new-style renderer
#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){
    
    //set up the new renderer
    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    
    ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
//    ofSetupOpenGL(1680,1050,OF_WINDOW);			// <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
    
}
