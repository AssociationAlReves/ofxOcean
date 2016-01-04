#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    //ofBackground(10, 10, 10);
    //ofEnableDepthTest();
    
    // turn on smooth lighting //
    smoothLighting     = true;
    ofSetSmoothLighting(true);
    
    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
    pointLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));
    
    // specular color, the highlight/shininess color //
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
    pointLight.setPointLight();

    // Directional Lights emit light based on their orientation, regardless of their position //
    directionalLight.setDiffuseColor(ofColor(255.f, 255.f, 255.f));
    directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    directionalLight.setAmbientColor(ofColor(255.f, 255.f, 255.f));
    directionalLight.setDirectional();
    
    // set the direction of the light
    // set it pointing from left to right -> //
    directionalLight.setOrientation( ofVec3f(0, 90, 0) );
    
    
    shiny = true;
    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 120 );
    // the light highlight of the material //
    material.setSpecularColor(ofColor(42, 141, 255, 128));
    
    
    ocean.setup();
    
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(filled.set("bFill", true));
    gui.add(useLights.set("Use lights", false));
    gui.add(smoothLighting.set("Smooth Lighting", true));
    gui.add(shiny.set("Shiny", true));
    gui.add(usePointLight.set("usePointLight", false));
    gui.add(useDirLight.set("useDirLight", false));
    gui.add(dirLightOrientation.set("Orientation (x,z,y angles)", ofVec3f(0), ofVec3f(-180), ofVec3f(180)));
    bShowGui = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    float radius = 500;
    ofVec3f center = ofVec3f(0,0,-500);
    pointLight.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
                           sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y,
                           -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
    
    ocean.filled = filled;
    if (shiny) material.setShininess( 120 );
    else material.setShininess( 30 );

    ocean.update();
    
    directionalLight.setOrientation((ofVec3f)dirLightOrientation);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    cam.begin();
    // enable lighting //
    if (useLights) {
        ofEnableLighting();
        ofSetSmoothLighting(smoothLighting);
        // enable the material, so that it applies to all 3D objects before material.end() call //
        material.begin();
        // activate the lights //
        if (usePointLight && useLights) pointLight.enable();
        if (useDirLight && useLights) directionalLight.enable();
    } else {
        ofDisableLighting();
    }
    
    

    ocean.draw();
    //ofDrawAxis(10);
    
    if (useLights) {
        // enable the material, so that it applies to all 3D objects before material.end() call //
        material.end();
        // activate the lights //
        if (!usePointLight) pointLight.disable();
        if (!useDirLight) directionalLight.disable();
    }
    
    // turn off lighting //
    ofDisableLighting();
    
    cam.end();

    if (bShowGui) {
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'h' ){
        bShowGui = !bShowGui;
    }
    if(key == 's') {
        gui.saveToFile("settings.xml");
    }
    if(key == 'l') {
        gui.loadFromFile("settings.xml");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
