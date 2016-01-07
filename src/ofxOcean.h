//
//  ofxOcean.h
//  ofxOcean
//
//  Created by Xavier Fischer on 28/12/2015.
//
//

#pragma once

#include "ofMain.h"
#include "ofxTween.h"

class ofxOcean {
    
public:
    void setup();
    void update();
    void updateMesh(float W, float H, int size);
    void draw();
    
    bool filled;
    ofFloatColor color;
    float noiseAmp;
    float noiseSpeed;
    float noiseHeight;
    
    ofVec3f waveDirection;
    float waveHeight;
    float waveAmplitude;
    float waveSpeed;
    
    ofVec3f waveDirection2;
    float waveHeight2;
    float waveAmplitude2;
    float waveSpeed2;


private:
    void setupMesh(float W, float H, int res);
    
    ofVboMesh mesh;
    int width;
    int height;
    int gridSize;
    int resolution;
    
    //Universal function which sets normals for the triangle mesh
    void setNormals( ofMesh &mesh );
    
};
