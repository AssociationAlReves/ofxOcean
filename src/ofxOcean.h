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
    void update(ofFloatColor const color);
    void draw();
    
    bool filled;


private:
    void setupMesh(float W, float H, int size);
    
    ofVboMesh mesh;
    int width;
    int height;
    int gridSize;
    
    //Universal function which sets normals for the triangle mesh
    void setNormals( ofMesh &mesh );
    
};
