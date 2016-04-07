#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    //ofBackground(10, 10, 10);
    
    // turn on smooth lighting //
    smoothLighting     = true;
    ofSetSmoothLighting(true);
    
    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
    // specular color, the highlight/shininess color //
    
    pointLight.setPointLight();

    // Directional Lights emit light based on their orientation, regardless of their position //
    directionalLight.setDirectional();
    
    // set the direction of the light
    // set it pointing from left to right -> //
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess(shininess);
    // the light highlight of the material //
    material.setColors(matDiffuseColor, matAmbientColor, matSpecularColor, matEmissiveColor);
    
    ocean.setup();
    
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(filled.set("bFill", true));
    gui.add(useLights.set("Use lights", true));
    gui.add(smoothLighting.set("Smooth Lighting", true));
    gui.add(usePointLight.set("usePointLight", false));
    gui.add(useDirLight.set("useDirLight", true));
    gui.add(useMaterial.set("useMaterial", true));
    
    meshParams.setName("Ocean mesh");
    meshParams.add(meshColor.set("meshColor", ofFloatColor(1, 0.72449, 1, 1),ofFloatColor(0,0,0,0),ofColor::white));
    meshParams.add(meshSize.set("size", 10, 10,100));
    meshParams.add(meshResolution.set("resolution", 2, 1,10));
    meshParams.add(noiseAmp.set("noiseAmp", 2, 0,50));
    meshParams.add(noiseSpeed.set("noiseSpeed", 2, 0,50));
    meshParams.add(noiseHeight.set("noiseHeight", 2, 0,500));
    meshParams.add(waveAmp.set("waveAmp", 0,0,PI));
    meshParams.add(waveSpeed.set("waveSpeed", 0,0,10));
    meshParams.add(waveHeight.set("waveHeight", 0,0,500));
    meshParams.add(waveDirection.set("waveDirection", ofVec3f(0),ofVec3f(-1),ofVec3f(1)));
    meshParams.add(waveAmp2.set("waveAmp2", 0,0,PI));
    meshParams.add(waveSpeed2.set("waveSpeed2", 0,0,10));
    meshParams.add(waveHeight2.set("waveHeight2", 0,0,500));
    meshParams.add(waveDirection2.set("waveDirection2", ofVec3f(0),ofVec3f(-1),ofVec3f(1)));

    gui.add(meshParams);
    
    lightParams.setName("Lights");
    lightParams.add(dirLightOrientation.set("Orientation (x,z,y angles)", ofVec3f(180, -42.2449, 117.551), ofVec3f(-180), ofVec3f(180)));
    lightParams.add(diffuseColor.set("diffuseColor", ofFloatColor(1, 1, 1, 1),ofFloatColor(0,0,0,0),ofColor::white));
    lightParams.add(specularColor.set("specularColor", ofFloatColor(1, 1, 1, 1), ofFloatColor(0,0,0,0),ofColor::white));
    lightParams.add(ambientColor.set("ambientColor", ofFloatColor(0, 0.00510204, 1, 1), ofFloatColor(0,0,0,0),ofColor::white));
    gui.add(lightParams);
    
    materialParams.setName("Material");
    materialParams.add(shininess.set("shininess", 128, 0, 128));
    materialParams.add(matDiffuseColor.set("matDiffuseColor", ofFloatColor(0, 0.204082, 1, 1), ofFloatColor(0,0,0,0),ofColor::white));
    materialParams.add(matSpecularColor.set("matSpecularColor", ofFloatColor(1, 1, 1, 1), ofFloatColor(0,0,0,0),ofColor::white));
    materialParams.add(matEmissiveColor.set("matEmissiveColor", ofFloatColor(0, 0.540816, 1, 1), ofFloatColor(0,0,0,0),ofColor::white));
    materialParams.add(matAmbientColor.set("matAmbientColor", ofFloatColor(0, 0.55102, 1, 1), ofFloatColor(0,0,0,0),ofColor::white));
    gui.add(materialParams);
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
    
    ocean.updateMesh(meshSize*100, meshSize*100, MAX(1, (int)meshResolution)*10);
    ocean.noiseAmp = noiseAmp;
    ocean.noiseHeight = noiseHeight;
    ocean.noiseSpeed = noiseSpeed;
    ocean.waveSpeed = waveSpeed;
    ocean.waveHeight = waveHeight;
    ocean.waveDirection = ((ofVec3f)waveDirection).normalize();
    ocean.waveAmplitude = waveAmp;
    ocean.waveSpeed2 = waveSpeed2;
    ocean.waveHeight2 = waveHeight2;
    ocean.waveDirection2 = ((ofVec3f)waveDirection2).normalize();
    ocean.waveAmplitude2 = waveAmp2;

    ocean.update();
    
    directionalLight.setDiffuseColor(diffuseColor);
    directionalLight.setSpecularColor(specularColor);
    directionalLight.setAmbientColor(ambientColor);
    
    pointLight.setDiffuseColor(diffuseColor);
    pointLight.setSpecularColor(specularColor);
    pointLight.setAmbientColor(ambientColor);

    directionalLight.setDirectional();
    directionalLight.setOrientation((ofVec3f)dirLightOrientation);
    
    material.setShininess(shininess);
    material.setColors(matDiffuseColor, matAmbientColor, matSpecularColor, matEmissiveColor);
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    
    cam.begin();
    cam.setFarClip(100000);
    
    // enable the material, so that it applies to all 3D objects before material.end() call //
    if (useMaterial) {
        material.begin();
    }
    
    if (useLights) {
        ofEnableLighting();
        ofSetSmoothLighting(smoothLighting);
        // activate the lights //
        if (usePointLight && useLights) pointLight.enable();
        if (useDirLight && useLights) directionalLight.enable();
    } else {
        ofDisableLighting();
    }
    
  
    ocean.draw();
    //ofDrawAxis(1000);
    
    if (useLights) {
        // activate the lights //
        if (!usePointLight) pointLight.disable();
        if (!useDirLight) directionalLight.disable();
    }

   
    // turn off lighting //
    ofDisableLighting();
    material.end();


    cam.end();

    if (bShowGui) {
        ofDisableDepthTest();
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
    if(key == 'f') {
        ofToggleFullscreen();
    }
    if(key == OF_KEY_LEFT) {
        cam.move(0,-10,0);
    }
    if(key == OF_KEY_RIGHT) {
        cam.move(0,10,0);
    }
    if(key == OF_KEY_DOWN) {
        cam.move(0,0,-10);
    }
    if(key == OF_KEY_UP) {
        cam.move(0,0,10);
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
