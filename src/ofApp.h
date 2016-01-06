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

    // lights params
    ofParameter<ofVec3f> dirLightOrientation;
    ofParameter<ofFloatColor> diffuseColor;
    ofParameter<ofFloatColor> specularColor;
    ofParameter<ofFloatColor> ambientColor;
    ofParameterGroup lightParams;

    // material params
    ofParameter<ofFloatColor> matAmbientColor;
    ofParameter<ofFloatColor> matDiffuseColor;
    ofParameter<ofFloatColor> matSpecularColor;
    ofParameter<ofFloatColor> matEmissiveColor;
    ofParameterGroup materialParams;

    // mesh params
    ofParameter<ofFloatColor> meshColor;
    ofParameter<int> meshSize;
    ofParameter<int> meshResolution;
    ofParameter<float> noiseAmp;
    ofParameter<float> noiseSpeed;
    ofParameter<float> noiseHeight;
    
    ofParameter<float> waveAmp;
    ofParameter<float> waveSpeed;
    ofParameter<float> waveHeight;
    ofParameter<ofVec3f> waveDirection;
    ofParameterGroup  meshParams;
    
    bool bShowGui;
    
    
    ofLight directionalLight;
    ofLight pointLight;
    
    ofMaterial material;
};
