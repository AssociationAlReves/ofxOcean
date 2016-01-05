#pragma once

#include "ofMain.h"
#include "ofxOcean.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
private:
    ofxOcean ocean;
		
    ofEasyCam cam;
    
    ofxPanel gui;
    ofParameter<bool> useLights;
    ofParameter<bool> filled;
    ofParameter<bool> smoothLighting;
    ofParameter<bool> usePointLight;
    ofParameter<bool> useDirLight;
    ofParameter<bool> useMaterial;
    ofParameter<float> shininess;
    ofParameter<ofVec3f> dirLightOrientation;
    ofParameter<ofFloatColor> diffuseColor;
    ofParameter<ofFloatColor> specularColor;
    ofParameter<ofFloatColor> ambientColor;
    ofParameter<ofFloatColor> matAmbientColor;
    ofParameter<ofFloatColor> matDiffuseColor;
    ofParameter<ofFloatColor> matSpecularColor;
    ofParameter<ofFloatColor> matEmissiveColor;
    ofParameter<ofFloatColor> meshColor;
    
    bool bShowGui;
    
    
    ofLight directionalLight;
    ofLight pointLight;
    
    ofMaterial material;
};
