//
//  ofxOcean.cpp
//  ofxOcean
//
//  Created by Xavier Fischer on 28/12/2015.
//
//

#include "ofxOcean.h"

//--------------------------------------------------------------
void ofxOcean::setup(){
    
    width = 1000;
    height = 1000;
    resolution = 100;
    gridSize = width / resolution;
    
    setupMesh(width,height,gridSize);
    
}

//--------------------------------------------------------------
void ofxOcean::updateMesh(float W, float H, int res){
    if (width != W || height != H || resolution != res) {
        width = W; height = H; resolution = res; gridSize = W / res;
        setupMesh(W, H, gridSize);
    }
}

//--------------------------------------------------------------
void ofxOcean::setupMesh(float W, float H, int gridSize){
    
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.clear();
    mesh.enableColors();
    mesh.enableIndices();
    mesh.enableNormals();
    mesh.disableTextures();
    
    //Set up vertices and colors
    bool odd = true;
    float offset = 0;
    for (int y=0; y<H; y+=gridSize) {
        for (int x=0; x<W; x+=gridSize) {
            
            if (odd) {
                if (x == 0) {
                    //mesh.addVertex(ofPoint(0, y, 0));
                    //mesh.addColor( ofColor( 0, 0, 0 ) );
                }
                offset = gridSize/2.0;
            } else {
                offset = 0;
            }
            mesh.addVertex(ofPoint(x+offset, y, 0));
            mesh.addColor( ofColor(255.f, 255.f, 255.f, 64.f) );
        }
        if (!odd){
            //mesh.addVertex(ofPoint(W-gridSize/2, y, 0));
            //mesh.addColor( ofColor( 0, 0, 0 ) );
        }
        odd = !odd;
    }
    
    //Set up triangles' indices
    odd = true;
    int numRows = H/gridSize;
    int numCols = W/gridSize;

    for (int y=0; y<numRows-1; y++) {
        for (int x=0; x<numCols-1; x++) {
            int i1 = x + numCols * y;
            int i2 = x+1 + numCols * y;
            int i3 = x + numCols * (y+1);
            int i4 = x+1 + numCols * (y+1);
            
            if (odd) {
                mesh.addTriangle( i1, i4, i3 );
                mesh.addTriangle( i1, i2, i4 );
            } else {
                mesh.addTriangle( i1, i2, i3 );
                mesh.addTriangle( i2, i4, i3 );
            }
        }
        odd = !odd;
    }
    setNormals( mesh );  //Set normals
    
}

//--------------------------------------------------------------
void ofxOcean::update(){

    // z = sin(y)
    
    int W = width/gridSize;
    int H = height/gridSize;
    float time = ofGetElapsedTimef();
    //Change vertices
    for (int y=0; y<H; y++) {
        
        float waveZ = sin(y * waveAmplitude + time * waveSpeed) * waveHeight;
        
        for (int x=0; x<W; x++) {
            int i = x + W * y;       //Vertex index
            ofPoint p = mesh.getVertex( i );
            //Get Perlin noise value
            float value =
            ofNoise( x * gridSize * noiseAmp * 0.001, y * gridSize * noiseAmp * 0.001, time * noiseSpeed * 0.2 ); // 0.2
            //Change z-coordinate of vertex
            p.z = value * noiseHeight; //25
        
            p.z += waveZ;
            
            mesh.setVertex( i, p );
            //Change color of vertex
            mesh.setColor( i, color);
                    }
        
    }
    setNormals( mesh );  //Update the normals
    
    
}

//--------------------------------------------------------------
void ofxOcean::draw(){
    
    ofPushMatrix();
    ofTranslate(-width/2, -height/2, -500);
    ofTranslate(0,1000);
    
//    mesh.setMode( OF_PRIMITIVE_TRIANGLES );
//    vector<ofMeshFace> triangles = mesh.getUniqueFaces();
//    mesh.setFromTriangles(triangles, false);

    if (filled) {
        mesh.drawFaces();
        //mesh.draw();
    } else {
        mesh.drawWireframe();
    }
    
    ofPopMatrix();
}


//--------------------------------------------------------------

//Universal function which sets normals for the triangle mesh
void ofxOcean::setNormals( ofMesh &mesh ){
    //The number of the vertices
    int nV = mesh.getNumVertices();
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    vector<ofPoint> norm( nV ); //Array for the normals
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).getCrossed( v3 - v1 ) ).getNormalized();
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}
